// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#include "eelbot_framework/cpprestsdk_helpers.hpp"

#include "cpprest/http_client.h"
#include "cpprest/producerconsumerstream.h"
#include "eelbot_framework/discord_bot/endpoints.hpp"

#include <stdexcept>

namespace eelbot_framework {

web::http::method get_cpprestsdk_http_method(const http_method &method) {
	switch (method) {
	case http_method::GET:
		return web::http::methods::GET;
		break;
	case http_method::HEAD:
		return web::http::methods::HEAD;
		break;
	case http_method::POST:
		return web::http::methods::POST;
		break;
	case http_method::PUT:
		return web::http::methods::PUT;
		break;
	case http_method::DELETE:
		return web::http::methods::DEL;
		break;
	case http_method::CONNECT:
		return web::http::methods::CONNECT;
		break;
	case http_method::OPTIONS:
		return web::http::methods::OPTIONS;
		break;
	case http_method::TRACE:
		return web::http::methods::TRCE;
		break;
	case http_method::PATCH:
		return web::http::methods::PATCH;
	default:
		throw std::out_of_range("The requested HTTP method is invalid.");
	}
}

http_response perform_http_request(const http_request &request) {
	web::http::client::http_client_config client_config;
	if (request.proxy.has_value()) {
		web::web_proxy proxy(request.proxy.value());
		client_config.set_proxy(proxy);
	}

	web::http::client::http_client                          client(request.endpoint, client_config);
	web::http::http_request                                 http_request(get_cpprestsdk_http_method(request.method));
	http_response                                           response;
	concurrency::streams::producer_consumer_buffer<uint8_t> response_buf;

	for (auto const &[key, value] : request.header_entries) {
		http_request.headers().add(key, value);
	}

	pplx::task<void> do_http_request =
	    client.request(http_request)
	        .then([&request, &response, &response_buf](web::http::http_response http_response) {
		        response.status_code = http_response.status_code();

		        for (auto header_entry : http_response.headers()) {
			        response.header_entries.insert(header_entry);
		        }

		        return http_response.body().read_to_end(response_buf);
	        })
	        .then([&request, &response, &response_buf](size_t length) {
		        uint8_t *data;

		        if (!response_buf.acquire(data, length)) {
			        throw std::runtime_error(
			            "Failed to read response body for HTTP request to endpoint " + request.endpoint + ".");
		        }
		        std::string resp((char *)data, length);

		        response.body = resp;
	        });

	do_http_request.wait();

	return response;
}

} // namespace eelbot_framework
