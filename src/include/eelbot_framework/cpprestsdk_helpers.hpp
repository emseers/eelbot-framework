// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#ifndef EELBOT_FRAMEWORK_CPPRESTSDK_HELPERS_H
#define EELBOT_FRAMEWORK_CPPRESTSDK_HELPERS_H

#include <map>
#include <optional>
#include <string>

namespace eelbot_framework {

/**
 * @brief An emum of all the supported HTTP methods.
 */
enum class http_method { GET, HEAD, POST, PUT, DELETE, CONNECT, OPTIONS, TRACE, PATCH };

/**
 * @brief The context for a HTTP request.
 */
struct http_request {
	std::string                        endpoint;
	http_method                        method;
	std::map<std::string, std::string> header_entries;
	std::string                        body;
	std::optional<std::string>         proxy;
};

/**
 * @brief The context for an HTTP response.
 */
struct http_response {
	unsigned short                     status_code;
	std::map<std::string, std::string> header_entries;
	std::string                        body;
};

/**
 * @brief Performs a HTTP request and returns the response. Throws an exception if an error occurs.
 *
 * @param request The HTTP request.
 * @return The HTTP response.
 */
http_response perform_http_request(const http_request &request);

} // namespace eelbot_framework

#endif
