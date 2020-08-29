// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#ifndef EELBOT_FRAMEWORK_DISCORD_BOT_STRUCTS_H
#define EELBOT_FRAMEWORK_DISCORD_BOT_STRUCTS_H

#include <optional>
#include <string>

namespace eelbot_framework {

namespace discord_bot {

struct session_start_limit {
	int total       = 0;
	int remaining   = 0;
	int reset_after = 0;
};

struct gateway_response {
	std::string url;
};

struct gateway_bot_response {
	std::string         url;
	int                 shards = 0;
	session_start_limit sess_start_limit;
};

// TODO: Update type of d.
struct payload {
	int                        op = 0;
	std::optional<std::string> d;
	std::optional<int>         s;
	std::optional<std::string> t;
};

} // namespace discord_bot

} // namespace eelbot_framework

#endif
