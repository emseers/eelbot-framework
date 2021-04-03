// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#ifndef EELBOT_FRAMEWORK_DISCORD_BOT_STRUCTS_H
#define EELBOT_FRAMEWORK_DISCORD_BOT_STRUCTS_H

#include <optional>
#include <string>
#include <variant>
#include <vector>

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

struct shard_info {
	int shard_id   = 0;
	int num_shards = 0;
};

struct party_size_info {
	int current_size = 0;
	int max_size     = 0;
};

struct activity_timestamps {
	std::optional<int> start;
	std::optional<int> end;
};

struct activity_emoji {
	std::string                name;
	std::optional<std::string> id;
	std::optional<bool>        animated;
};

struct activity_party {
	std::optional<std::string>     id;
	std::optional<party_size_info> size;
};

struct activity_assets {
	std::optional<std::string> large_image;
	std::optional<std::string> large_text;
	std::optional<std::string> small_image;
	std::optional<std::string> small_text;
};

struct activity_secrets {
	std::optional<std::string> join;
	std::optional<std::string> spectate;
	std::optional<std::string> match;
};

struct activity {
	std::string                        name;
	int                                type = 0;
	std::optional<std::string>         url;
	int                                created_at = 0;
	std::optional<activity_timestamps> timestamps;
	std::optional<std::string>         application_id;
	std::optional<std::string>         details;
	std::optional<std::string>         state;
	std::optional<activity_emoji>      emoji;
	std::optional<activity_party>      party;
	std::optional<activity_assets>     assets;
	std::optional<activity_secrets>    secrets;
	std::optional<bool>                instance;
	std::optional<int>                 flags;
};

enum class status_type { online, dnd, idle, invisible, offline };

struct status_update {
	std::optional<int>    since;
	std::vector<activity> activities;
	status_type           status;
	bool                  afk;
};

struct user {
	std::string                id;
	std::string                username;
	std::string                discriminator;
	std::optional<std::string> avatar;
	std::optional<bool>        bot;
	std::optional<bool>        system;
	std::optional<bool>        mfa_enabled;
	std::optional<std::string> locale;
	std::optional<bool>        verified;
	std::optional<std::string> email;
	std::optional<int>         flags;
	std::optional<int>         premium_type;
	std::optional<int>         public_flags;
};

struct unavailable_guild {
	std::string         id;
	std::optional<bool> unavailable;
};

struct partial_application {
	std::string id;
	int         flags = 0;
};

struct identify_connection_properties {
	std::string os;
	std::string browser;
	std::string device;
};

struct identify {
	std::string                    token;
	identify_connection_properties properties;
	std::optional<bool>            compress;
	std::optional<int>             large_treshold;
	std::optional<shard_info>      shard;
	std::optional<status_update>   presence;
	std::optional<bool>            guild_subscriptions;
	int                            intents = 0;
};

struct resume {
	std::string token;
	std::string session_id;
	int         seq = 0;
};

struct hello {
	int heartbeat_interval = 0;
};

struct ready {
	int                            v = 0;
	user                           user_info;
	std::vector<std::string>       private_channels;
	std::vector<unavailable_guild> guilds;
	std::string                    session_id;
	std::optional<shard_info>      shard;
	partial_application            application;
};

struct payload {
	int                                                     op = 0;
	std::variant<bool, int, identify, resume, hello, ready> d;
	std::optional<int>                                      s;
	std::optional<std::string>                              t;
};

} // namespace discord_bot

} // namespace eelbot_framework

#endif
