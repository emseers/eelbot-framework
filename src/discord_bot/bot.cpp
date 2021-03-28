// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#include "eelbot_framework/discord_bot/bot.hpp"

#include "eelbot_framework/compression.hpp"
#include "eelbot_framework/discord_bot/endpoints.hpp"
#include "eelbot_framework/discord_bot/rest_api.hpp"
#include "eelbot_framework/json.hpp"
#include "eelbot_framework/websocket.hpp"
#include "fmt/core.h"

#include <stdexcept>
namespace eelbot_framework {

namespace discord_bot {

http_request_settings bot::get_http_request_settings() {
	http_request_settings request_settings;
	request_settings.tls_ver      = this->tls_ver;
	request_settings.ca_directory = this->ca_directory;
	request_settings.proxy        = this->http_proxy;
	return request_settings;
}

void bot::handle_message(const std::string &message) try {
	this->logger->log(log::level::TRACE, "Received message.");

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
	// TODO: Process message.
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
	try {
		gateway_bot_response response = get_gateway_bot(this->token, this->get_http_request_settings());
		if (response.sess_start_limit.remaining <= 0) {
			throw std::runtime_error("no sessions remaining; please regenerate a new token");
		}

		this->ws_url = response.url;
	} catch (std::exception &e) {
		this->logger->log(log::level::ERROR, fmt::format("Error getting websocket URL: {}.", e.what()));
		throw;
	}

	if (this->ws_url.back() != '/') {
		this->ws_url += "/";
	}
	this->ws_url += "?v=" + gateway_version + "&encoding=json&compress=zlib-stream";

	this->logger->log(log::level::DEBUG, "Setting up websocket client.");
	websocket_endpoint_context ws_context;
	ws_context.logger       = this->logger;
	ws_context.tls_ver      = this->tls_ver;
	ws_context.ca_directory = this->ca_directory;
	ws_context.http_proxy   = this->http_proxy;
	this->ws_client         = std::make_shared<websocket_client>(ws_context);

	this->logger->log(log::level::DEBUG, "Setting up zlib stream inflator.");
	zlib_inflate_context z_context;
	this->z_inflator = std::make_shared<zlib_inflate>(z_context);

	this->logger->log(log::level::INFO, "Initialized bot successfully.");
}

bot::~bot() {}

void bot::run() try {
	if (this->gateway_active) {
		throw std::runtime_error("bot is already running");
	}

	this->ws_client->set_message_handler(std::bind(&bot::handle_message, this, std::placeholders::_1));
	this->ws_client->connect_and_run(this->ws_url);
} catch (std::exception &e) {
	this->logger->log(log::level::ERROR, fmt::format("Error running bot: {}.", e.what()));
	throw;
}

} // namespace discord_bot

} // namespace eelbot_framework
