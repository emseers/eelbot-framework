// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#ifndef EELBOT_FRAMEWORK_WEBSOCKET_H
#define EELBOT_FRAMEWORK_WEBSOCKET_H

#include "eelbot_framework/log/logger.hpp"
#include "eelbot_framework/log/stdout_logger.hpp"
#include "eelbot_framework/tls.hpp"
#include "eelbot_framework/websocket/logger.hpp"
#include "websocketpp/client.hpp"
#include "websocketpp/config/asio_client.hpp"
#include "websocketpp/extensions/permessage_deflate/enabled.hpp"

#include <functional>
#include <memory>
#include <optional>
#include <string>

namespace eelbot_framework {

/**
 * @brief The custom websocketpp client config that supports compression and the eelbot framework logging interface.
 */
struct client_config : public websocketpp::config::asio_tls_client {
	typedef eelbot_framework::websocket::logger<concurrency_type, websocketpp::log::alevel> alog_type;
	typedef eelbot_framework::websocket::logger<concurrency_type, websocketpp::log::elevel> elog_type;

	struct transport_config : public websocketpp::config::asio_tls_client::transport_config {
		typedef eelbot_framework::websocket::logger<concurrency_type, websocketpp::log::alevel> alog_type;
		typedef eelbot_framework::websocket::logger<concurrency_type, websocketpp::log::elevel> elog_type;
	};

	typedef websocketpp::transport::asio::endpoint<transport_config> transport_type;

	struct permessage_deflate_config {};

	typedef websocketpp::extensions::permessage_deflate::enabled<permessage_deflate_config> permessage_deflate_type;
};

/**
 * @brief The context for a websocket_endpoint object.
 */
struct websocket_endpoint_context {
	std::shared_ptr<log::logger> logger = log::stdout_logger::get();

	tls_version                tls_ver = tls_version::v12;
	std::optional<std::string> ca_directory; // The directory must be prepared using the openssl `c_rehash` utility.
	std::optional<std::string> http_proxy;
};

/**
 * @brief An object to store a websocket close status.
 */
struct websocket_status {
	unsigned short code = 0;
	std::string    message;
};

/**
 * @brief An object to connect to a websocket endpoint.
 *
 * Note that this object is meant to be used for a single connection only and should be discarded after the connection
 * is closed.
 */
class websocket_client {
private:
	std::shared_ptr<log::logger> logger;

	websocketpp::client<client_config>                      ws_client;
	std::shared_ptr<websocketpp::connection<client_config>> conn;
	std::optional<std::string>                              http_proxy;

public:
	websocket_client(const websocket_endpoint_context &context);
	~websocket_client();

	/**
	 * @brief Sets the handler to be called on a successful connection.
	 *
	 * @param handler The handler to set.
	 */
	void set_open_handler(std::function<void()> handler);

	/**
	 * @brief Sets the handler to be called on a failure to open a successful connection.
	 *
	 * @param handler The handler to set.
	 */
	void set_fail_handler(std::function<void()> handler);

	/**
	 * @brief Sets the handler to be called after the closure of the connection.
	 *
	 * @param handler The handler to set.
	 */
	void set_close_handler(std::function<void()> handler);

	/**
	 * @brief Sets the handler to be called after receiving a message.
	 *
	 * @param handler The handler to set.
	 */
	void set_message_handler(std::function<void(const std::string &)> handler);

	/**
	 * @brief Connects to the endpoint and starts the websocket client loop.
	 *
	 * Note that this blocks until either the server closes the connection or close is called.
	 *
	 * @param endpoint The endpoint to connect to.
	 */
	void connect_and_run(const std::string &endpoint);

	/**
	 * @brief Sends a message to the connected endpoint.
	 *
	 * @param msg The message to send.
	 */
	void send(const std::string &msg);

	/**
	 * @brief Closes the connection to the endpoint and stops the client loop.
	 *
	 * @param status_code The status code to close the connection with.
	 * @param status_message The status message to close the connection with.
	 */
	void close(const unsigned short status_code = 1000, const std::string &status_message = "");

	/**
	 * @brief Gets the status the websocket connection was closed with.
	 *
	 * @return The status.
	 */
	websocket_status get_close_status();
};

} // namespace eelbot_framework

#endif
