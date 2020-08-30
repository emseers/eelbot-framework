// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#ifndef EELBOT_FRAMEWORK_DISCORD_BOT_REST_API_H
#define EELBOT_FRAMEWORK_DISCORD_BOT_REST_API_H

#include "eelbot_framework/discord_bot/structs.hpp"

#include <string>

namespace eelbot_framework {

namespace discord_bot {

/**
 * @brief The context for a HTTP request's settings.
 */
struct http_request_settings {
	std::optional<std::string> proxy;
};

/**
 * @brief Returns a valid websocket endpoint that can be used to connect to a Discord Gateway.
 *
 * @return The gateway response object.
 */
gateway_response get_gateway(const http_request_settings &request_settings = {});

/**
 * @brief Returns a valid websocket endpoint that can be used to connect to a Discord Gateway for a bot.
 *
 * @param bot_token The Discord token.
 * @return The bot gateway response object.
 */
gateway_bot_response get_gateway_bot(const std::string &token, const http_request_settings &request_settings = {});

} // namespace discord_bot

} // namespace eelbot_framework

#endif
