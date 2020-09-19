// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#include "catch2/catch.hpp"
#include "eelbot_framework/discord_bot/structs.hpp"
#include "eelbot_framework/json.hpp"

TEST_CASE("discord_bot::session_start_limit can be serialized to JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::session_start_limit session_start_limit;
	session_start_limit.total       = 1;
	session_start_limit.remaining   = -2;
	session_start_limit.reset_after = 0;

	REQUIRE(eelbot_framework::to_json_string<eelbot_framework::discord_bot::session_start_limit>(session_start_limit) ==
	        "{\"remaining\":-2,\"reset_after\":0,\"total\":1}");
}

TEST_CASE("discord_bot::gateway_response can be serialized to JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::gateway_response gateway_response;
	gateway_response.url = "https://github.com/Emseers/eelbot-framework";

	REQUIRE(eelbot_framework::to_json_string<eelbot_framework::discord_bot::gateway_response>(gateway_response) ==
	        "{\"url\":\"https://github.com/Emseers/eelbot-framework\"}");
}

TEST_CASE("discord_bot::gateway_bot_response can be serialized to JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::session_start_limit session_start_limit;
	session_start_limit.total       = 1;
	session_start_limit.remaining   = -2;
	session_start_limit.reset_after = 0;

	eelbot_framework::discord_bot::gateway_bot_response gateway_bot_response;
	gateway_bot_response.url              = "https://github.com/Emseers/eelbot-framework";
	gateway_bot_response.shards           = 99;
	gateway_bot_response.sess_start_limit = session_start_limit;

	REQUIRE(eelbot_framework::to_json_string<eelbot_framework::discord_bot::gateway_bot_response>(
	            gateway_bot_response) == "{\"session_start_limit\":{\"remaining\":-2,\"reset_after\":0,\"total\":1},"
	                                     "\"shards\":99,\"url\":\"https://github.com/Emseers/eelbot-framework\"}");
}

TEST_CASE("discord_bot::session_start_limit can be deserialized from JSON", "[unit-test][json]") {
	std::string                                        json;
	eelbot_framework::discord_bot::session_start_limit session_start_limit;

	// Invalid JSON.
	json = "{\"invalid_entry\":0}";

	REQUIRE_THROWS(
	    session_start_limit =
	        eelbot_framework::parse_from_json_string<eelbot_framework::discord_bot::session_start_limit>(json));

	// Valid JSON.
	json = "{\"remaining\":-2,\"reset_after\":0,\"total\":1}";

	REQUIRE_NOTHROW(
	    session_start_limit =
	        eelbot_framework::parse_from_json_string<eelbot_framework::discord_bot::session_start_limit>(json));

	CHECK(session_start_limit.total == 1);
	CHECK(session_start_limit.remaining == -2);
	CHECK(session_start_limit.reset_after == 0);
}

TEST_CASE("discord_bot::gateway_response can be deserialized from JSON", "[unit-test][json]") {
	std::string                                     json;
	eelbot_framework::discord_bot::gateway_response gateway_response;

	// Invalid JSON.
	json = "{\"invalid_entry\":0}";

	REQUIRE_THROWS(gateway_response =
	                   eelbot_framework::parse_from_json_string<eelbot_framework::discord_bot::gateway_response>(json));

	// Valid JSON.
	json = "{\"url\":\"https://github.com/Emseers/eelbot-framework\"}";

	REQUIRE_NOTHROW(
	    gateway_response =
	        eelbot_framework::parse_from_json_string<eelbot_framework::discord_bot::gateway_response>(json));

	CHECK(gateway_response.url == "https://github.com/Emseers/eelbot-framework");
}

TEST_CASE("discord_bot::gateway_bot_response can be deserialized from JSON", "[unit-test][json]") {
	std::string                                         json;
	eelbot_framework::discord_bot::gateway_bot_response gateway_bot_response;

	// Invalid JSON.
	json = "{\"invalid_entry\":0}";

	REQUIRE_THROWS(
	    gateway_bot_response =
	        eelbot_framework::parse_from_json_string<eelbot_framework::discord_bot::gateway_bot_response>(json));

	// Valid JSON.
	json = "{\"session_start_limit\":{\"remaining\":-2,\"reset_after\":0,\"total\":1},\"shards\":99,\"url\":\"https://"
	       "github.com/Emseers/eelbot-framework\"}";

	REQUIRE_NOTHROW(
	    gateway_bot_response =
	        eelbot_framework::parse_from_json_string<eelbot_framework::discord_bot::gateway_bot_response>(json));

	CHECK(gateway_bot_response.url == "https://github.com/Emseers/eelbot-framework");
	CHECK(gateway_bot_response.shards == 99);
	CHECK(gateway_bot_response.sess_start_limit.total == 1);
	CHECK(gateway_bot_response.sess_start_limit.remaining == -2);
	CHECK(gateway_bot_response.sess_start_limit.reset_after == 0);
}
