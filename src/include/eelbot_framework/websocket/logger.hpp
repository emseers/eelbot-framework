// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#ifndef EELBOT_FRAMEWORK_WEBSOCKET_LOGGER_H
#define EELBOT_FRAMEWORK_WEBSOCKET_LOGGER_H

#include "eelbot_framework/log/logger.hpp"
#include "websocketpp/logger/basic.hpp"
#include "websocketpp/logger/levels.hpp"

#include <stdexcept>
#include <string>

namespace eelbot_framework {

namespace websocket {

template <typename concurrency, typename names>
class logger : public websocketpp::log::basic<concurrency, names> {
private:
	std::shared_ptr<log::logger>               ws_logger;
	websocketpp::log::channel_type_hint::value channel_type_hint;

public:
	logger(websocketpp::log::channel_type_hint::value hint = websocketpp::log::channel_type_hint::access)
	    : websocketpp::log::basic<concurrency, names>(hint), channel_type_hint(hint) {}

	logger(websocketpp::log::level                 channels,
	    websocketpp::log::channel_type_hint::value hint = websocketpp::log::channel_type_hint::access)
	    : websocketpp::log::basic<concurrency, names>(channels, hint), channel_type_hint(hint) {}

	void set_logger(std::shared_ptr<log::logger> ws_logger) {
		if (!ws_logger) {
			throw std::logic_error("invalid logger");
		}

		this->ws_logger = ws_logger;
	}

	void write(websocketpp::log::level channel, const char *msg) {
		std::string str(msg);
		write(channel, str);
	}

	void write(websocketpp::log::level channel, const std::string &msg) {
		if (!this->dynamic_test(channel)) {
			return;
		}

		if (this->channel_type_hint == websocketpp::log::channel_type_hint::access) {
			this->ws_logger->log(log::level::DEBUG, msg);
			return;
		}

		switch (channel) {
		case websocketpp::log::elevel::devel:
		case websocketpp::log::elevel::library:
			this->ws_logger->log(log::level::DEBUG, msg);
			break;
		case websocketpp::log::elevel::warn:
			this->ws_logger->log(log::level::WARN, msg);
			break;
		case websocketpp::log::elevel::rerror:
			this->ws_logger->log(log::level::ERROR, msg);
			break;
		case websocketpp::log::elevel::fatal:
			this->ws_logger->log(log::level::FATAL, msg);
			break;
		default:
			this->ws_logger->log(log::level::INFO, msg);
			break;
		}
	}
};

} // namespace websocket

} // namespace eelbot_framework

#endif
