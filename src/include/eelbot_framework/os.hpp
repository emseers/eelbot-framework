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
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
	return "Windows";
#elif defined(__APPLE__) || defined(__MACH__)
	return "macOS";
#elif defined(__ANDROID__)
	return "Android";
#elif defined(__linux__)
	return "Linux";
#elif defined(__FreeBSD__)
	return "FreeBSD";
#elif defined(unix) || defined(__unix) || defined(__unix__)
	return "Unix";
#else
	return "Unknown";
#endif
}

} // namespace eelbot_framework

#endif
