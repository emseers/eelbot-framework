// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#ifndef EELBOT_FRAMEWORK_LOG_STDOUT_LOGGER_H
#define EELBOT_FRAMEWORK_LOG_STDOUT_LOGGER_H

#include "eelbot_framework/log/logger.hpp"

#include <memory>
#include <string>

namespace eelbot_framework {

namespace log {

/**
 * @brief A singleton implementation of the Eelbot Framework logger interface that logs to stdout.
 */
class stdout_logger final : public logger {
private:
	stdout_logger() {}

public:
	stdout_logger(stdout_logger const &) = delete;
	void operator=(stdout_logger const &) = delete;

	static std::shared_ptr<stdout_logger> get() {
		static std::shared_ptr<stdout_logger> instance(new stdout_logger);
		return instance;
	}

	void log(const level lvl, const std::string &msg);
};

} // namespace log

} // namespace eelbot_framework

#endif
