// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#include "eelbot_framework/log/logger.hpp"

#include <stdexcept>

namespace eelbot_framework {

namespace log {

std::string level_string(const level lvl) {
	switch (lvl) {
	case level::FATAL:
		return "FATAL";
	case level::ERROR:
		return "ERROR";
	case level::WARN:
		return "WARN";
	case level::INFO:
		return "INFO";
	case level::DEBUG:
		return "DEBUG";
	case level::TRACE:
		return "TRACE";
	default:
		throw std::out_of_range("log level out of range");
	}
}

} // namespace log

} // namespace eelbot_framework
