// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#include "eelbot_framework/websocket.hpp"

#include "eelbot_framework/discord_bot/endpoints.hpp"
#include "fmt/core.h"

#include <stdexcept>

namespace eelbot_framework {

std::shared_ptr<asio::ssl::context> get_asio_ssl_ctx(tls_version tls_ver) {
	switch (tls_ver) {
	case tls_version::v1:
		return std::make_shared<asio::ssl::context>(asio::ssl::context::tlsv1);
	case tls_version::v11:
		return std::make_shared<asio::ssl::context>(asio::ssl::context::tlsv11);
	case tls_version::v12:
		return std::make_shared<asio::ssl::context>(asio::ssl::context::tlsv12);
	case tls_version::v13:
		return std::make_shared<asio::ssl::context>(asio::ssl::context::tlsv13);
	default:
		throw std::out_of_range("the given TLS version is invalid");
	}
}

websocket_client::websocket_client(const websocket_endpoint_context &context)
    : logger(context.logger), http_proxy(context.http_proxy) {
	if (!this->logger) {
		throw std::logic_error("invalid logger");
	}

	// Set logger.
	this->ws_client.get_alog().set_logger(this->logger);
	this->ws_client.get_elog().set_logger(this->logger);

	// Set logging policy to be informative but not too chatty.
	this->ws_client.clear_access_channels(websocketpp::log::alevel::all);
	this->ws_client.set_access_channels(websocketpp::log::alevel::connect);
	this->ws_client.set_access_channels(websocketpp::log::alevel::disconnect);
	this->ws_client.set_access_channels(websocketpp::log::alevel::app);
	this->ws_client.set_error_channels(websocketpp::log::elevel::all);

	// Initialize ASIO client.
	std::unique_ptr<asio::io_service> service = std::make_unique<asio::io_service>();
	this->ws_client.init_asio(service.get());
	service.release();

	// Set TLS handler.
	std::shared_ptr<asio::ssl::context> ssl_ctx = get_asio_ssl_ctx(context.tls_ver);
	if (context.ca_directory.has_value()) {
		ssl_ctx->add_verify_path(context.ca_directory.value());
	}
	this->ws_client.set_tls_init_handler([ssl_ctx](websocketpp::connection_hdl hdl) {
		return ssl_ctx;
	});
}

websocket_client::~websocket_client() {}

void websocket_client::set_open_handler(std::function<void()> handler) {
	this->ws_client.set_open_handler([handler](websocketpp::connection_hdl hdl) {
		handler();
	});
}

void websocket_client::set_fail_handler(std::function<void()> handler) {
	this->ws_client.set_fail_handler([handler](websocketpp::connection_hdl hdl) {
		handler();
	});
}

void websocket_client::set_close_handler(std::function<void()> handler) {
	this->ws_client.set_close_handler([handler](websocketpp::connection_hdl hdl) {
		handler();
	});
}

void websocket_client::set_message_handler(std::function<void(const std::string &)> handler) {
	this->ws_client.set_message_handler(
	    [handler](websocketpp::connection_hdl hdl, websocketpp::config::asio_client::message_type::ptr msg) {
		    handler(msg->get_payload());
	    });
}

void websocket_client::connect_and_run(const std::string &endpoint) {
	std::error_code ec;
	this->conn = ws_client.get_connection(endpoint, ec);
	if (ec) {
		throw std::runtime_error(ec.message());
	}

	if (this->http_proxy.has_value()) {
		this->conn->set_proxy(this->http_proxy.value(), ec);
		if (ec) {
			throw std::runtime_error(ec.message());
		}
	}

	this->conn = this->ws_client.connect(conn);
	this->ws_client.run();
}

void websocket_client::send(const std::string &msg) {
	std::error_code ec;
	this->ws_client.send(this->conn->get_handle(), msg, websocketpp::frame::opcode::text, ec);
	if (ec) {
		throw std::runtime_error(ec.message());
	}
}

void websocket_client::close(const unsigned short status_code, const std::string &status_message) {
	std::error_code ec;
	this->ws_client.close(this->conn->get_handle(), status_code, status_message, ec);
	if (ec) {
		throw std::runtime_error(ec.message());
	}
}

websocket_status websocket_client::get_close_status() {
	if (!this->conn) {
		throw std::runtime_error("no connection initialized");
	}

	websocket_status status;
	status.code    = this->conn->get_remote_close_code();
	status.message = this->conn->get_remote_close_reason();
	return status;
}

} // namespace eelbot_framework
