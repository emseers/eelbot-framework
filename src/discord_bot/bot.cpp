// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#include "eelbot_framework/discord_bot/bot.hpp"

#include "eelbot_framework/discord_bot/rest_api.hpp"
#include "eelbot_framework/json.hpp"

#include <stdexcept>

namespace eelbot_framework {

namespace discord_bot {

bot::bot(const bot_context &context) : token("Bot " + context.bot_token), http_proxy(context.http_proxy) {
	gateway_bot_response response = get_gateway_bot(this->token, {this->http_proxy});
	if (response.sess_start_limit.remaining <= 0) {
		throw std::runtime_error("No sessions remaining. Please regenerate a new token.");
	}

	this->ws_url = response.url;
}

bot::~bot() {}

} // namespace discord_bot

} // namespace eelbot_framework
