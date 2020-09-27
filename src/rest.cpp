// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#include "eelbot_framework/rest.hpp"

#include "cpr/cpr.h"
#include "eelbot_framework/discord_bot/endpoints.hpp"

#include <stdexcept>

namespace eelbot_framework {

cpr::SslOptions get_cpr_ssl_opts(tls_version tls_ver) {
	switch (tls_ver) {
	case tls_version::v1:
		return cpr::Ssl(cpr::ssl::TLSv1{});
	case tls_version::v11:
		return cpr::Ssl(cpr::ssl::TLSv1_1{});
	case tls_version::v12:
		return cpr::Ssl(cpr::ssl::TLSv1_2{});
	case tls_version::v13:
		return cpr::Ssl(cpr::ssl::TLSv1_3{});
	default:
		throw std::out_of_range("The given TLS version is invalid.");
	}
}

template <typename... Ts>
cpr::Response perform_cpr_http_request(const http_method &method, Ts &&... ts) {
	switch (method) {
	case http_method::GET:
		return cpr::Get(std::move(ts)...);
	case http_method::HEAD:
		return cpr::Head(std::move(ts)...);
	case http_method::POST:
		return cpr::Post(std::move(ts)...);
	case http_method::PUT:
		return cpr::Put(std::move(ts)...);
	case http_method::DELETE:
		return cpr::Delete(std::move(ts)...);
	case http_method::OPTIONS:
		return cpr::Options(std::move(ts)...);
	case http_method::PATCH:
		return cpr::Patch(std::move(ts)...);
	default:
		throw std::out_of_range("The requested HTTP method is invalid.");
	}
}

http_response perform_http_request(const http_request &request) {
	// Set endpoint.
	cpr::Url endpoint(request.endpoint);

	// Set header entries.
	cpr::Header header(request.header.begin(), request.header.end());

	// Set parameters.
	cpr::Parameters parameters;
	for (auto const &[key, value] : request.parameter) {
		parameters.Add({key, value});
	}

	// Set body.
	cpr::Body body(request.body);

	// Set SSL options.
	cpr::SslOptions ssl_opts = get_cpr_ssl_opts(request.settings.tls_ver);
	if (request.settings.ca_directory.has_value()) {
		std::string ca_path = request.settings.ca_directory.value();
		ssl_opts.SetOption(cpr::ssl::CaPath(std::move(ca_path)));
	}

	// Set proxy.
	cpr::Proxies proxy;
	if (request.settings.proxy.has_value()) {
		proxy = {{"http", request.settings.proxy.value()}, {"https", request.settings.proxy.value()}};
	}

	// Perform request.
	http_response response;
	cpr::Response cpr_response =
	    perform_cpr_http_request(request.method, endpoint, header, parameters, body, ssl_opts, proxy);

	if (cpr_response.error.code != cpr::ErrorCode::OK) {
		throw std::runtime_error("Failed to perform HTTP request to endpoint " + request.endpoint +
		                         ". Error: " + cpr_response.error.message + ".");
	}

	response.status_code = cpr_response.status_code;
	response.header      = http_header(cpr_response.header.begin(), cpr_response.header.end());
	response.body        = cpr_response.text;
	response.time_taken  = cpr_response.elapsed;

	return response;
}

} // namespace eelbot_framework
