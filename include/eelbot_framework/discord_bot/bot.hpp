// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#ifndef EELBOT_FRAMEWORK_DISCORD_BOT_BOT_H
#define EELBOT_FRAMEWORK_DISCORD_BOT_BOT_H

#include <optional>
#include <string>

namespace eelbot_framework {

namespace discord_bot {

/**
 * @brief The context for a bot object.
 */
struct bot_context {
	std::string                bot_token;
	std::optional<std::string> http_proxy;
};

class bot {
private:
	const std::string          token;
	std::string                ws_url;
	std::optional<std::string> http_proxy;

	bool        gateway_active = false;
	std::string session_id;

public:
	bot(const bot_context &context);
	~bot();
};

} // namespace discord_bot

} // namespace eelbot_framework

#endif
