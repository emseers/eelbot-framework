// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#include "eelbot_framework/discord_bot/bot.hpp"

#include "eelbot_framework/discord_bot/rest_api.hpp"
#include "eelbot_framework/json.hpp"
#include "fmt/core.h"

#include <stdexcept>

#define _EELBOT_FRAMEWORK_DISCORD_BOT_HTTP_REQUEST_SETTINGS                                                            \
	{ convert_to_eelbot_framework_tls_ver(this->tls_ver), this->ca_directory, this->http_proxy }
namespace eelbot_framework {

tls_version convert_to_eelbot_framework_tls_ver(discord_bot::tls_version ver) {
	switch (ver) {
	case discord_bot::tls_version::v1:
		return tls_version::v1;
	case discord_bot::tls_version::v11:
		return tls_version::v11;
	case discord_bot::tls_version::v12:
		return tls_version::v12;
	case discord_bot::tls_version::v13:
		return tls_version::v13;
	default:
		throw std::out_of_range("The given TLS version is invalid.");
	}
}

namespace discord_bot {

bot::bot(const bot_context &context)
    : logger(context.logger), token("Bot " + context.bot_token), tls_ver(context.tls_ver),
      ca_directory(context.ca_directory), http_proxy(context.http_proxy) {
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
