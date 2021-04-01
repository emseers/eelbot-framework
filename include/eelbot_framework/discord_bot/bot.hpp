// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#ifndef EELBOT_FRAMEWORK_DISCORD_BOT_BOT_H
#define EELBOT_FRAMEWORK_DISCORD_BOT_BOT_H

#include "eelbot_framework/log/logger.hpp"
#include "eelbot_framework/log/stdout_logger.hpp"
#include "eelbot_framework/tls.hpp"

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <optional>
#include <string>

namespace eelbot_framework {

struct http_request_settings;
class websocket_client;
class zlib_inflate;

namespace discord_bot {

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

	mutable std::mutex                gateway_mutex;
	mutable bool                      started        = false;
	mutable bool                      gateway_active = false;
	mutable bool                      stopping       = false;
	mutable std::mutex                heartbeat_mutex;
	mutable std::condition_variable   stop_heartbeating;
	mutable std::atomic_int           sequence_num = -1;
	mutable std::atomic_bool          ack_received = false;
	std::shared_ptr<websocket_client> ws_client;
	std::shared_ptr<zlib_inflate>     z_inflator;

	http_request_settings get_http_request_settings() noexcept;

	void send_heartbeat();
	void send_identify();

	void handle_message(const std::string &message) noexcept;

public:
	bot(const bot_context &context);
	~bot();

	void run();
	void stop();
};

} // namespace discord_bot

} // namespace eelbot_framework

#endif
