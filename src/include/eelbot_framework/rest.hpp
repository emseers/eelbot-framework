// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#ifndef EELBOT_FRAMEWORK_REST_H
#define EELBOT_FRAMEWORK_REST_H

#include "cpr/cpr.h"
#include "eelbot_framework/tls.hpp"

#include <map>
#include <optional>
#include <string>

namespace eelbot_framework {

using http_header = cpr::Header;

/**
 * @brief An emum of all the supported HTTP methods.
 */
enum class http_method { GET, HEAD, POST, PUT, DELETE, OPTIONS, PATCH };

/**
 * @brief The context for a HTTP request's settings.
 */
struct http_request_settings {
	tls_version                tls_ver = tls_version::v12;
	std::optional<std::string> ca_directory; // The directory must be prepared using the openssl `c_rehash` utility.
	std::optional<std::string> proxy;
};

/**
 * @brief The context for a HTTP request.
 */
struct http_request {
	std::string                        endpoint;
	http_method                        method;
	http_header                        header;
	std::map<std::string, std::string> parameter;
	std::string                        body;
	http_request_settings              settings;
};

/**
 * @brief The context for an HTTP response.
 */
struct http_response {
	unsigned short status_code;
	http_header    header;
	std::string    body;
	double         time_taken; // In seconds.
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
