// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#include "eelbot_framework/discord_bot/bot.hpp"

#include "eelbot_framework/compression.hpp"
#include "eelbot_framework/discord_bot/endpoints.hpp"
#include "eelbot_framework/discord_bot/rest_api.hpp"
#include "eelbot_framework/json.hpp"
#include "eelbot_framework/os.hpp"
#include "eelbot_framework/websocket.hpp"
#include "fmt/core.h"

#include <stdexcept>
#include <thread>
namespace eelbot_framework {

namespace discord_bot {

http_request_settings bot::get_http_request_settings() noexcept {
	http_request_settings request_settings;
	request_settings.tls_ver      = this->tls_ver;
	request_settings.ca_directory = this->ca_directory;
	request_settings.proxy        = this->http_proxy;
	return request_settings;
}

void bot::send_heartbeat() {
	payload pl;
	pl.op = opcode::heartbeat;
	pl.d  = this->sequence_num;
	this->ws_client->send(to_json_str(pl));
}

void bot::send_identify() {
	// TODO: Make shard info configurable down the line.
	shard_info sh_info;
	sh_info.shard_id   = 0;
	sh_info.num_shards = 1;

	identify_connection_properties id_conn_props;
	id_conn_props.os      = get_platform_name();
	id_conn_props.browser = "Eelbot Framework";
	id_conn_props.device  = "Eelbot Framework";

	identify id;
	id.token      = this->token;
	id.intents    = 513; // TODO: Determine this dynamically.
	id.shard      = sh_info;
	id.properties = id_conn_props;
	id.compress   = false;

	this->logger->log(log::level::DEBUG, "Sending identify.");
	payload pl;
	pl.op = opcode::identify;
	pl.d  = id;
	this->ws_client->send(to_json_str(pl));
}

void bot::send_resume() {
	resume rs;
	rs.token = this->token;
	rs.seq   = this->sequence_num;

	{
		std::scoped_lock lock(this->session_mutex);
		rs.session_id = this->session_id;
	}

	this->logger->log(log::level::DEBUG, "Sending resume.");
	payload pl;
	pl.op = opcode::resume;
	pl.d  = rs;
	this->ws_client->send(to_json_str(pl));
}

void bot::handle_message(const std::string &message) noexcept try {
	bool flush = false;
	if (message.size() >= 4) {
		flush = message[message.size() - 4] == '\x00' && message[message.size() - 3] == '\x00' &&
		        message[message.size() - 2] == '\xFF' && message[message.size() - 1] == '\xFF';
	}

	this->z_inflator->push(message);
	if (!flush) {
		this->logger->log(log::level::TRACE, "Zlib suffix not received; returning without parsing.");
		return;
	}

	payload pl = parse_from_json<payload>(this->z_inflator->get_result());

	// If the gateway sent a sequence number, update the cached sequence value.
	if (pl.s.has_value()) {
		this->sequence_num = pl.s.value();
		this->logger->log(log::level::TRACE, fmt::format("Sequence updated to {}.", this->sequence_num));
	}

	switch (pl.op) {
	case opcode::dispatch: {
		this->logger->log(log::level::TRACE, fmt::format("Received event {}.", pl.t.value_or("NULL")));

		if (pl.t.has_value()) {
			if (pl.t.value() == event::ready) {
				ready event_data = std::get<ready>(pl.d);

				std::scoped_lock lock(this->session_mutex);
				this->session_id = event_data.session_id;
				this->logger->log(log::level::DEBUG, fmt::format("Session ID updated to {}.", this->session_id));
			}
		}
		break;
	}
	case opcode::reconnect: {
		this->logger->log(log::level::DEBUG, "Received reconnect.");

		this->ws_client->close(close_event_code::internal_retry_and_resume);
		break;
	}
	case opcode::invalid_session: {
		this->logger->log(log::level::DEBUG, "Received invalid session.");

		this->ws_client->close(close_event_code::internal_retry_and_identify);
		break;
	}
	case opcode::hello: {
		this->logger->log(log::level::DEBUG, "Received hello.");

		hello event_data         = std::get<hello>(pl.d);
		int   heartbeat_interval = event_data.heartbeat_interval;
		this->ack_received       = true;

		// Launch thread to perform heartbeats at the given interval.
		std::thread([this, heartbeat_interval]() {
			this->logger->log(log::level::TRACE, "Starting heartbeats.");
			std::unique_lock lock(this->heartbeat_mutex);

			do {
				if (!this->ack_received) {
					// TODO: Close connection and create a new one to resume.
					break;
				}

				this->ack_received = false;
				this->send_heartbeat();
			} while (this->stop_heartbeating.wait_for(lock, std::chrono::milliseconds(heartbeat_interval)) ==
			         std::cv_status::timeout);

			this->logger->log(log::level::TRACE, "Stopping heartbeats.");
		}).detach();

		// Determine whether to identify or resume.
		bool resume = false;
		{
			std::scoped_lock lock(this->session_mutex);
			resume = this->sequence_num >= 0 && !this->session_id.empty();
		}

		if (resume) {
			this->send_resume();
		} else {
			this->send_identify();
		}
		break;
	}
	case opcode::heartbeat_ack: {
		this->logger->log(log::level::TRACE, "Received heartbeat ack.");

		this->ack_received = true;
		break;
	}
	}
} catch (std::exception &e) {
	this->logger->log(log::level::ERROR, fmt::format("Error receiving/processing message: {}.", e.what()));
}

bot::bot(const bot_context &context)
    : logger(context.logger), token("Bot " + context.bot_token), tls_ver(context.tls_ver),
      ca_directory(context.ca_directory), http_proxy(context.http_proxy) {
	if (!this->logger) {
		throw std::logic_error("invalid logger");
	}

	this->logger->log(log::level::DEBUG, "Getting websocket URL.");
	gateway_bot_response response = get_gateway_bot(this->token, this->get_http_request_settings());
	this->logger->log(log::level::DEBUG, fmt::format("Sessions remaining = {}.", response.sess_start_limit.remaining));
	if (response.sess_start_limit.remaining <= 0) {
		throw std::runtime_error("no sessions remaining; please regenerate a new token");
	}

	this->ws_url = response.url;

	if (this->ws_url.back() != '/') {
		this->ws_url += "/";
	}
	this->ws_url += "?v=" + gateway_version + "&encoding=json&compress=zlib-stream";

	this->logger->log(log::level::INFO, "Initialized bot successfully.");
}

bot::~bot() {
	std::scoped_lock lock(this->gateway_mutex);
	if (!this->started) {
		return;
	}

	if (this->stopping) {
		return;
	}

	if (this->gateway_active) {
		this->ws_client->close();
	}
}

void bot::run() {
	{
		std::scoped_lock lock(this->gateway_mutex);
		if (this->started) {
			throw std::runtime_error("bot is already running");
		}
	}

	this->logger->log(log::level::INFO, "Starting up bot.");

	bool retry;
	do {
		std::unique_lock lock(this->gateway_mutex);
		if (this->stopping) {
			break;
		}

		this->logger->log(log::level::DEBUG, "Setting up zlib stream inflator.");
		zlib_inflate_context z_context;
		this->z_inflator = std::make_shared<zlib_inflate>(z_context);

		this->logger->log(log::level::DEBUG, "Setting up websocket client.");
		websocket_endpoint_context ws_context;
		ws_context.logger       = this->logger;
		ws_context.tls_ver      = this->tls_ver;
		ws_context.ca_directory = this->ca_directory;
		ws_context.http_proxy   = this->http_proxy;
		this->ws_client         = std::make_shared<websocket_client>(ws_context);

		this->ws_client->set_open_handler([this, &lock]() {
			this->started        = true;
			this->gateway_active = true;
			lock.unlock();
		});

		this->ws_client->set_fail_handler([this, &lock]() {
			this->started = true;
			lock.unlock();
		});

		this->ws_client->set_close_handler([this, &lock]() {
			lock.lock();
			this->gateway_active = false;
			lock.unlock();
		});

		this->ws_client->set_message_handler(std::bind(&bot::handle_message, this, std::placeholders::_1));

		// This will block until either the client or server terminates the connection.
		this->ws_client->connect_and_run(this->ws_url);

		{
			// Stop heartbeating.
			std::scoped_lock lock(this->heartbeat_mutex);
			this->stop_heartbeating.notify_one();
		}

		websocket_status status;
		try {
			status = this->ws_client->get_close_status();
			this->logger->log(log::level::DEBUG,
			    fmt::format("Websocket connection closed with code={}; message={}", status.code, status.message));
		} catch (std::exception &e) {
			this->logger->log(log::level::ERROR, fmt::format("Error closing connection: {}.", e.what()));
		}

		// Determine whether to retry or not.
		switch (status.code) {
		case close_event_code::unknown_opcode:
		case close_event_code::decode_error:
		case close_event_code::not_authenticated:
		case close_event_code::already_authenticated:
		case close_event_code::invalid_api_version:
		case close_event_code::invalid_intents:
		case close_event_code::disallowed_intents: {
			// This may be a problem with the library, so don't retry to be safe.
			this->logger->log(log::level::ERROR, "Logic error; Eelbot Framework library version may be out of date.");
			retry = false;
			break;
		}
		case close_event_code::authentication_failed:
		case close_event_code::invalid_shard:
		case close_event_code::sharding_required: {
			// Unrecoverable error; don't retry.
			retry = false;
			break;
		}
		case close_event_code::invalid_seq:
		case close_event_code::internal_retry_and_identify: {
			// Retry but don't try to resume.
			std::scoped_lock lock(this->session_mutex);
			this->sequence_num = -1;
			this->session_id.clear();
			retry = true;
			break;
		}
		case close_event_code::abnormal_closure:
		case close_event_code::unknown_error:
		case close_event_code::rate_limited:
		case close_event_code::session_timed_out:
		case close_event_code::internal_retry_and_resume: {
			// Retry and try to resume.
			retry = true;
			break;
		}
		default: {
			// Unrecognized error; don't retry to be safe.
			retry = false;
			break;
		}
		}
	} while (retry);

	this->logger->log(log::level::INFO, "Bot has been shut down.");
}

void bot::stop() {
	std::scoped_lock lock(this->gateway_mutex);
	if (!this->started) {
		throw std::runtime_error("bot is not running");
	}

	if (this->stopping) {
		throw std::runtime_error("bot is already stopping");
	}

	if (this->gateway_active) {
		this->ws_client->close();
	}

	this->stopping = true;
	this->logger->log(log::level::INFO, "Shutting down bot.");
}

} // namespace discord_bot

} // namespace eelbot_framework
