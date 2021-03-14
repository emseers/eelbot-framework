// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#include "eelbot_framework/discord_bot/bot.hpp"

#include "eelbot_framework/discord_bot/rest_api.hpp"
#include "eelbot_framework/json.hpp"
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
			throw std::runtime_error("no sessions remaining; please regenerate a new token.");
		}

		this->ws_url = response.url;
	} catch (std::exception &e) {
		this->logger->log(log::level::ERROR, fmt::format("Error getting websocket URL: {}.", e.what()));
		throw;
	}

	this->logger->log(log::level::INFO, "Initialized bot successfully.");
}

bot::~bot() {}

} // namespace discord_bot

} // namespace eelbot_framework
