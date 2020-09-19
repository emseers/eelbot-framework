// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#include "eelbot_framework/discord_bot/bot.hpp"

#include "eelbot_framework/discord_bot/rest_api.hpp"
#include "eelbot_framework/json.hpp"
#include "fmt/core.h"

#include <stdexcept>

#define _EELBOT_FRAMEWORK_DISCORD_BOT_HTTP_REQUEST_SETTINGS                                                            \
	{ this->ca_info, this->ca_path, this->http_proxy }
namespace eelbot_framework {

namespace discord_bot {

bot::bot(const bot_context &context)
    : logger(context.logger), token("Bot " + context.bot_token), ca_info(context.ca_info), ca_path(context.ca_path),
      http_proxy(context.http_proxy) {
	if (!this->logger) {
		throw std::logic_error("Invalid logger.");
	}

	this->logger->log(log::level::TRACE, "Getting websocket URL.");
	try {
		gateway_bot_response response =
		    get_gateway_bot(this->token, _EELBOT_FRAMEWORK_DISCORD_BOT_HTTP_REQUEST_SETTINGS);
		if (response.sess_start_limit.remaining <= 0) {
			throw std::runtime_error("No sessions remaining. Please regenerate a new token.");
		}

		this->ws_url = response.url;
	} catch (std::exception &e) {
		this->logger->log(log::level::ERROR, fmt::format("Error getting websocket URL: {}", e.what()));
		throw;
	}

	this->logger->log(log::level::INFO, "Initialized bot.");
}

bot::~bot() {}

} // namespace discord_bot

} // namespace eelbot_framework
