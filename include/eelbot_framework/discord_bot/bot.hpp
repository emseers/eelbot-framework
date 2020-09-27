// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#ifndef EELBOT_FRAMEWORK_DISCORD_BOT_BOT_H
#define EELBOT_FRAMEWORK_DISCORD_BOT_BOT_H

#include "eelbot_framework/log/logger.hpp"
#include "eelbot_framework/log/stdout_logger.hpp"

#include <optional>
#include <string>

namespace eelbot_framework {

namespace discord_bot {

/**
 * @brief An emum of all the supported TLS versions.
 */
enum class tls_version { v1, v11, v12, v13 };

/**
 * @brief The context for a bot object.
 */
struct bot_context {
	std::shared_ptr<log::logger> logger = log::stdout_logger::get();
	std::string                  bot_token;

	tls_version                tls_ver = tls_version::v12;
	std::optional<std::string> ca_directory; // The directory must be prepared using the openssl `c_rehash` utility.
	std::optional<std::string> http_proxy;
};

class bot {
private:
	std::shared_ptr<log::logger> logger;
	const std::string            token;
	std::string                  ws_url;

	tls_version                tls_ver;
	std::optional<std::string> ca_directory;
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
