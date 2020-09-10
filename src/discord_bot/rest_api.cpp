// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#include "eelbot_framework/discord_bot/rest_api.hpp"

#include "eelbot_framework/cpprestsdk_helpers.hpp"
#include "eelbot_framework/discord_bot/endpoints.hpp"
#include "eelbot_framework/json.hpp"
#include "fmt/core.h"

#include <map>
#include <stdexcept>

namespace eelbot_framework {

namespace discord_bot {

void check_response_status(
    const std::string &endpoint, const http_response &response, const unsigned short &expected_status_code = 200) {
	if (response.status_code != expected_status_code) {
		throw std::runtime_error(fmt::format(
		    "Got unexpected status code for HTTP request to endpoint {}. Expected code: {}. Received code: {}. "
		    "Received message: {}.",
		    endpoint, expected_status_code, response.status_code, response.body));
	}
}

gateway_response get_gateway(const http_request_settings &request_settings) {
	http_request request;
	request.endpoint = endpoints::gateway;
	request.method   = http_method::GET;
	request.proxy    = request_settings.proxy;

	http_response response = perform_http_request(request);
	check_response_status(request.endpoint, response);
	return parse_from_json_string<gateway_response>(response.body);
}

gateway_bot_response get_gateway_bot(const std::string &token, const http_request_settings &request_settings) {
	http_request request;
	request.endpoint = endpoints::gateway_bot;
	request.method   = http_method::GET;
	request.proxy    = request_settings.proxy;
	request.header_entries.insert({"Authorization", token});

	http_response response = perform_http_request(request);
	check_response_status(request.endpoint, response);
	return parse_from_json_string<gateway_bot_response>(response.body);
}

} // namespace discord_bot

} // namespace eelbot_framework
