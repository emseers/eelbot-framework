// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#ifndef EELBOT_FRAMEWORK_OS_H
#define EELBOT_FRAMEWORK_OS_H

#include <string>

namespace eelbot_framework {

/**
 * @brief Returns the platform name.
 *
 * @return The platform name.
 */
inline std::string get_platform_name() noexcept {
	using namespace std::string_literals;

#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
	return "Windows"s;
#elif defined(__APPLE__) || defined(__MACH__)
	return "macOS"s;
#elif defined(__ANDROID__)
	return "Android"s;
#elif defined(__linux__)
	return "Linux"s;
#elif defined(__FreeBSD__)
	return "FreeBSD"s;
#elif defined(unix) || defined(__unix) || defined(__unix__)
	return "Unix"s;
#else
	return "Unknown"s;
#endif
}

} // namespace eelbot_framework

#endif
