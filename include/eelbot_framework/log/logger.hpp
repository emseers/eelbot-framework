// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#ifndef EELBOT_FRAMEWORK_LOG_LOGGER_H
#define EELBOT_FRAMEWORK_LOG_LOGGER_H

#include <string>

namespace eelbot_framework {

namespace log {

enum class level { FATAL, ERROR, WARN, INFO, DEBUG, TRACE };

/**
 * @brief Converts a log level to a string.
 *
 * @param lvl The log level.
 * @return The log level as a string.
 */
std::string level_string(const level lvl);

/**
 * @brief The Eelbot Framework logger interface.
 *
 * You will need to have an implementation of this interface to specify a custom logging sink.
 */
class logger {
public:
	virtual ~logger() {}

	/**
	 * @brief Logs a message with the specified log level.
	 *
	 * Note that this needs to be thread safe.
	 *
	 * @param lvl The log level.
	 * @param msg The message.
	 */
	virtual void log(const level lvl, const std::string &msg) = 0;
};

} // namespace log

} // namespace eelbot_framework

#endif
