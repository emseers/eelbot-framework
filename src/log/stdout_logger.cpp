// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#include "eelbot_framework/log/stdout_logger.hpp"

#include "fmt/core.h"

namespace eelbot_framework {

namespace log {

void stdout_logger::log(const level lvl, const std::string &msg) {
	fmt::print("[{}] {}\n", level_string(lvl), msg);
}

} // namespace log

} // namespace eelbot_framework
