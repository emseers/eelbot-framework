// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#include "catch2/catch_test_macros.hpp"
#include "eelbot_framework/discord_bot/structs.hpp"
#include "eelbot_framework/json.hpp"

TEST_CASE("discord_bot::session_start_limit can be deserialized from JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::session_start_limit session_start_limit;
	std::string                                        json = "{\"remaining\":-2,\"reset_after\":0,\"total\":1}";

	REQUIRE_NOTHROW(session_start_limit =
	                    eelbot_framework::parse_from_json<eelbot_framework::discord_bot::session_start_limit>(json));

	CHECK(session_start_limit.total == 1);
	CHECK(session_start_limit.remaining == -2);
	CHECK(session_start_limit.reset_after == 0);
}

TEST_CASE("discord_bot::gateway_response can be deserialized from JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::gateway_response gateway_response;
	std::string                                     json = "{\"url\":\"https://github.com/Emseers/eelbot-framework\"}";

	REQUIRE_NOTHROW(
	    gateway_response = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::gateway_response>(json));

	CHECK(gateway_response.url == "https://github.com/Emseers/eelbot-framework");
}

TEST_CASE("discord_bot::gateway_bot_response can be deserialized from JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::gateway_bot_response gateway_bot_response;
	std::string json = "{\"session_start_limit\":{\"remaining\":-2,\"reset_after\":0,\"total\":1},"
	                   "\"shards\":99,\"url\":\"https://github.com/Emseers/eelbot-framework\"}";

	REQUIRE_NOTHROW(gateway_bot_response =
	                    eelbot_framework::parse_from_json<eelbot_framework::discord_bot::gateway_bot_response>(json));

	CHECK(gateway_bot_response.url == "https://github.com/Emseers/eelbot-framework");
	CHECK(gateway_bot_response.shards == 99);
	CHECK(gateway_bot_response.sess_start_limit.total == 1);
	CHECK(gateway_bot_response.sess_start_limit.remaining == -2);
	CHECK(gateway_bot_response.sess_start_limit.reset_after == 0);
}

TEST_CASE("discord_bot::shard_info can be deserialized from JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::shard_info shard_info;
	std::string                               json = "[1,2]";

	REQUIRE_NOTHROW(shard_info = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::shard_info>(json));

	CHECK(shard_info.shard_id == 1);
	CHECK(shard_info.num_shards == 2);
}

TEST_CASE("discord_bot::party_size_info can be deserialized from JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::party_size_info party_size_info;
	std::string                                    json = "[3,5]";

	REQUIRE_NOTHROW(
	    party_size_info = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::party_size_info>(json));

	CHECK(party_size_info.current_size == 3);
	CHECK(party_size_info.max_size == 5);
}

TEST_CASE("discord_bot::activity_timestamps can be deserialized from JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::activity_timestamps activity_timestamps;

	SECTION("deserialize all optional fields being null") {
		std::string json = "{}";

		REQUIRE_NOTHROW(
		    activity_timestamps =
		        eelbot_framework::parse_from_json<eelbot_framework::discord_bot::activity_timestamps>(json));

		CHECK_FALSE(activity_timestamps.start.has_value());
		CHECK_FALSE(activity_timestamps.end.has_value());
	}

	SECTION("deserialize some optional fields being null") {
		std::string json = "{\"end\":null,\"start\":500}";

		REQUIRE_NOTHROW(
		    activity_timestamps =
		        eelbot_framework::parse_from_json<eelbot_framework::discord_bot::activity_timestamps>(json));

		CHECK(activity_timestamps.start.value() == 500);
		CHECK_FALSE(activity_timestamps.end.has_value());
	}

	SECTION("deserialize no optional fields being null") {
		std::string json = "{\"end\":1000,\"start\":500}";

		REQUIRE_NOTHROW(
		    activity_timestamps =
		        eelbot_framework::parse_from_json<eelbot_framework::discord_bot::activity_timestamps>(json));

		CHECK(activity_timestamps.start.value() == 500);
		CHECK(activity_timestamps.end.value() == 1000);
	}
}

TEST_CASE("discord_bot::activity_emoji can be deserialized from JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::activity_emoji activity_emoji;

	SECTION("deserialize all optional fields being null") {
		std::string json = "{\"name\":\"eel\"}";

		REQUIRE_NOTHROW(
		    activity_emoji = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::activity_emoji>(json));

		CHECK(activity_emoji.name == "eel");
		CHECK_FALSE(activity_emoji.id.has_value());
		CHECK_FALSE(activity_emoji.animated.has_value());
	}

	SECTION("deserialize some optional fields being null") {
		std::string json = "{\"animated\":null,\"id\":\"123456789\",\"name\":\"eel\"}";

		REQUIRE_NOTHROW(
		    activity_emoji = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::activity_emoji>(json));

		CHECK(activity_emoji.name == "eel");
		CHECK(activity_emoji.id.value() == "123456789");
		CHECK_FALSE(activity_emoji.animated.has_value());
	}

	SECTION("deserialize no optional fields being null") {
		std::string json = "{\"animated\":false,\"id\":\"123456789\",\"name\":\"eel\"}";

		REQUIRE_NOTHROW(
		    activity_emoji = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::activity_emoji>(json));

		CHECK(activity_emoji.name == "eel");
		CHECK(activity_emoji.id.value() == "123456789");
		CHECK(activity_emoji.animated.value() == false);
	}
}

TEST_CASE("discord_bot::activity_party can be deserialized from JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::activity_party activity_party;

	SECTION("deserialize all optional fields being null") {
		std::string json = "{}";

		REQUIRE_NOTHROW(
		    activity_party = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::activity_party>(json));

		CHECK_FALSE(activity_party.id.has_value());
		CHECK_FALSE(activity_party.size.has_value());
	}

	SECTION("deserialize some optional fields being null") {
		std::string json = "{\"id\":\"123456789\",\"size\":null}";

		REQUIRE_NOTHROW(
		    activity_party = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::activity_party>(json));

		CHECK(activity_party.id.value() == "123456789");
		CHECK_FALSE(activity_party.size.has_value());
	}

	SECTION("deserialize no optional fields being null") {
		std::string json = "{\"id\":\"123456789\",\"size\":[3,5]}";

		REQUIRE_NOTHROW(
		    activity_party = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::activity_party>(json));

		CHECK(activity_party.id.value() == "123456789");
		CHECK(activity_party.size.value().current_size == 3);
		CHECK(activity_party.size.value().max_size == 5);
	}
}

TEST_CASE("discord_bot::activity_assets can be deserialized from JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::activity_assets activity_assets;

	SECTION("deserialize all optional fields being null") {
		std::string json = "{}";

		REQUIRE_NOTHROW(
		    activity_assets = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::activity_assets>(json));

		CHECK_FALSE(activity_assets.large_image.has_value());
		CHECK_FALSE(activity_assets.large_text.has_value());
		CHECK_FALSE(activity_assets.small_image.has_value());
		CHECK_FALSE(activity_assets.small_text.has_value());
	}

	SECTION("deserialize some optional fields being null") {
		std::string json = "{\"large_image\":\"123456789\",\"large_text\":null,\"small_image\":null,"
		                   "\"small_text\":\"tooltip\"}";

		REQUIRE_NOTHROW(
		    activity_assets = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::activity_assets>(json));

		CHECK(activity_assets.large_image.value() == "123456789");
		CHECK_FALSE(activity_assets.large_text.has_value());
		CHECK_FALSE(activity_assets.small_image.has_value());
		CHECK(activity_assets.small_text.value() == "tooltip");
	}

	SECTION("deserialize no optional fields being null") {
		std::string json = "{\"large_image\":\"123456789\",\"large_text\":\"tooltip\",\"small_image\":\"123456789\","
		                   "\"small_text\":\"tooltip\"}";

		REQUIRE_NOTHROW(
		    activity_assets = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::activity_assets>(json));

		CHECK(activity_assets.large_image.value() == "123456789");
		CHECK(activity_assets.large_text.value() == "tooltip");
		CHECK(activity_assets.small_image.value() == "123456789");
		CHECK(activity_assets.small_text.value() == "tooltip");
	}
}

TEST_CASE("discord_bot::activity_secrets can be deserialized from JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::activity_secrets activity_secrets;

	SECTION("deserialize all optional fields being null") {
		std::string json = "{}";

		REQUIRE_NOTHROW(activity_secrets =
		                    eelbot_framework::parse_from_json<eelbot_framework::discord_bot::activity_secrets>(json));

		CHECK_FALSE(activity_secrets.join.has_value());
		CHECK_FALSE(activity_secrets.spectate.has_value());
		CHECK_FALSE(activity_secrets.match.has_value());
	}

	SECTION("deserialize some optional fields being null") {
		std::string json = "{\"join\":\"secret one\",\"match\":null,\"spectate\":null}";

		REQUIRE_NOTHROW(activity_secrets =
		                    eelbot_framework::parse_from_json<eelbot_framework::discord_bot::activity_secrets>(json));

		CHECK(activity_secrets.join.value() == "secret one");
		CHECK_FALSE(activity_secrets.spectate.has_value());
		CHECK_FALSE(activity_secrets.match.has_value());
	}

	SECTION("deserialize no optional fields being null") {
		std::string json = "{\"join\":\"secret one\",\"match\":\"secret three\",\"spectate\":\"secret two\"}";

		REQUIRE_NOTHROW(activity_secrets =
		                    eelbot_framework::parse_from_json<eelbot_framework::discord_bot::activity_secrets>(json));

		CHECK(activity_secrets.join.value() == "secret one");
		CHECK(activity_secrets.spectate.value() == "secret two");
		CHECK(activity_secrets.match.value() == "secret three");
	}
}

TEST_CASE("discord_bot::activity can be deserialized from JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::activity activity;

	SECTION("deserialize all optional fields being null") {
		std::string json = "{\"created_at\":500,\"name\":\"activity\",\"type\":1}";

		REQUIRE_NOTHROW(activity = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::activity>(json));

		CHECK(activity.name == "activity");
		CHECK(activity.type == 1);
		CHECK(activity.created_at == 500);
		CHECK_FALSE(activity.url.has_value());
		CHECK_FALSE(activity.timestamps.has_value());
		CHECK_FALSE(activity.application_id.has_value());
		CHECK_FALSE(activity.details.has_value());
		CHECK_FALSE(activity.state.has_value());
		CHECK_FALSE(activity.emoji.has_value());
		CHECK_FALSE(activity.party.has_value());
		CHECK_FALSE(activity.assets.has_value());
		CHECK_FALSE(activity.secrets.has_value());
		CHECK_FALSE(activity.instance.has_value());
		CHECK_FALSE(activity.flags.has_value());
	}

	SECTION("deserialize some optional fields being null") {
		std::string json = "{\"application_id\":null,\"assets\":null,\"created_at\":500,\"details\":null,"
		                   "\"emoji\":null,\"flags\":null,\"instance\":null,\"name\":\"activity\",\"party\":null,"
		                   "\"secrets\":{\"join\":null,\"match\":null,\"spectate\":null},\"state\":null,"
		                   "\"timestamps\":{\"end\":null,\"start\":500},\"type\":1,\"url\":\"https://github.com/"
		                   "Emseers/eelbot-framework\"}";

		REQUIRE_NOTHROW(activity = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::activity>(json));

		CHECK(activity.name == "activity");
		CHECK(activity.type == 1);
		CHECK(activity.created_at == 500);
		CHECK(activity.url.value() == "https://github.com/Emseers/eelbot-framework");
		CHECK(activity.timestamps.value().start == 500);
		CHECK_FALSE(activity.timestamps.value().end.has_value());
		CHECK_FALSE(activity.application_id.has_value());
		CHECK_FALSE(activity.details.has_value());
		CHECK_FALSE(activity.state.has_value());
		CHECK_FALSE(activity.emoji.has_value());
		CHECK_FALSE(activity.party.has_value());
		CHECK_FALSE(activity.assets.has_value());
		CHECK_FALSE(activity.secrets.value().join.has_value());
		CHECK_FALSE(activity.secrets.value().spectate.has_value());
		CHECK_FALSE(activity.secrets.value().match.has_value());
		CHECK_FALSE(activity.instance.has_value());
		CHECK_FALSE(activity.flags.has_value());
	}

	SECTION("deserialize no optional fields being null") {
		std::string json = "{\"application_id\":\"123456789\",\"assets\":{\"large_image\":null,\"large_text\":"
		                   "null,\"small_image\":null,\"small_text\":null},\"created_at\":500,\"details\":"
		                   "\"something\",\"emoji\":{\"animated\":null,\"id\":null,\"name\":\"eel\"},\"flags\":512,"
		                   "\"instance\":true,\"name\":\"activity\",\"party\":{\"id\":null,\"size\":null},\"secrets\":"
		                   "{\"join\":null,\"match\":null,\"spectate\":null},\"state\":\"in a match\",\"timestamps\":"
		                   "{\"end\":null,\"start\":500},\"type\":1,\"url\":\"https://github.com/Emseers/eelbot-"
		                   "framework\"}";

		REQUIRE_NOTHROW(activity = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::activity>(json));

		CHECK(activity.name == "activity");
		CHECK(activity.type == 1);
		CHECK(activity.created_at == 500);
		CHECK(activity.url.value() == "https://github.com/Emseers/eelbot-framework");
		CHECK(activity.timestamps.value().start == 500);
		CHECK_FALSE(activity.timestamps.value().end.has_value());
		CHECK(activity.application_id.value() == "123456789");
		CHECK(activity.details.value() == "something");
		CHECK(activity.state.value() == "in a match");
		CHECK(activity.emoji.value().name == "eel");
		CHECK_FALSE(activity.emoji.value().id.has_value());
		CHECK_FALSE(activity.emoji.value().animated.has_value());
		CHECK_FALSE(activity.party.value().id.has_value());
		CHECK_FALSE(activity.party.value().size.has_value());
		CHECK_FALSE(activity.assets.value().large_image.has_value());
		CHECK_FALSE(activity.assets.value().large_text.has_value());
		CHECK_FALSE(activity.assets.value().small_image.has_value());
		CHECK_FALSE(activity.assets.value().small_text.has_value());
		CHECK_FALSE(activity.secrets.value().join.has_value());
		CHECK_FALSE(activity.secrets.value().spectate.has_value());
		CHECK_FALSE(activity.secrets.value().match.has_value());
		CHECK(activity.instance.value() == true);
		CHECK(activity.flags.value() == 512);
	}
}

TEST_CASE("discord_bot::status_type can be deserialized from JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::status_type status_type;

	SECTION("deserialize status_type = online") {
		std::string json = "\"online\"";

		REQUIRE_NOTHROW(
		    status_type = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::status_type>(json));

		CHECK(status_type == eelbot_framework::discord_bot::status_type::online);
	}

	SECTION("deserialize status_type = dnd") {
		std::string json = "\"dnd\"";

		REQUIRE_NOTHROW(
		    status_type = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::status_type>(json));

		CHECK(status_type == eelbot_framework::discord_bot::status_type::dnd);
	}

	SECTION("deserialize status_type = idle") {
		std::string json = "\"idle\"";

		REQUIRE_NOTHROW(
		    status_type = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::status_type>(json));

		CHECK(status_type == eelbot_framework::discord_bot::status_type::idle);
	}

	SECTION("deserialize status_type = invisible") {
		std::string json = "\"invisible\"";

		REQUIRE_NOTHROW(
		    status_type = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::status_type>(json));

		CHECK(status_type == eelbot_framework::discord_bot::status_type::invisible);
	}

	SECTION("deserialize status_type = offline") {
		std::string json = "\"offline\"";

		REQUIRE_NOTHROW(
		    status_type = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::status_type>(json));

		CHECK(status_type == eelbot_framework::discord_bot::status_type::offline);
	}

	SECTION("deserialize status_type = invalid") {
		std::string json = "\"invalid\"";

		REQUIRE_THROWS(
		    status_type = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::status_type>(json));
	}
}

TEST_CASE("discord_bot::status_update can be deserialized from JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::status_update status_update;

	SECTION("deserialize all optional fields being null") {
		std::string json = "{\"afk\":false,\"status\":\"online\"}";

		REQUIRE_NOTHROW(
		    status_update = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::status_update>(json));

		CHECK(status_update.status == eelbot_framework::discord_bot::status_type::online);
		CHECK(status_update.afk == false);
		CHECK_FALSE(status_update.since.has_value());
		CHECK(status_update.activities.empty());
	}

	SECTION("deserialize some optional fields being null") {
		std::string json = "{\"activities\":null,\"afk\":false,\"since\":500,\"status\":\"online\"}";

		REQUIRE_NOTHROW(
		    status_update = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::status_update>(json));

		CHECK(status_update.status == eelbot_framework::discord_bot::status_type::online);
		CHECK(status_update.afk == false);
		CHECK(status_update.since.value() == 500);
		CHECK(status_update.activities.empty());
	}

	SECTION("deserialize no optional fields being null") {
		std::string json = "{\"activities\":[{\"application_id\":null,\"assets\":null,\"created_at\":500,"
		                   "\"details\":null,\"emoji\":null,\"flags\":null,\"instance\":null,\"name\":\"activity "
		                   "one\",\"party\":null,\"secrets\":null,\"state\":null,\"timestamps\":null,\"type\":1,"
		                   "\"url\":null},{\"application_id\":null,\"assets\":null,\"created_at\":1000,\"details\":"
		                   "null,\"emoji\":null,\"flags\":null,\"instance\":null,\"name\":\"activity two\",\"party\":"
		                   "null,\"secrets\":null,\"state\":null,\"timestamps\":null,\"type\":0,\"url\":null}],"
		                   "\"afk\":false,\"since\":500,\"status\":\"online\"}";

		REQUIRE_NOTHROW(
		    status_update = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::status_update>(json));

		CHECK(status_update.status == eelbot_framework::discord_bot::status_type::online);
		CHECK(status_update.afk == false);
		CHECK(status_update.since.value() == 500);
		CHECK(status_update.activities.size() == 2);
		CHECK(status_update.activities.at(0).name == "activity one");
		CHECK(status_update.activities.at(0).type == 1);
		CHECK(status_update.activities.at(0).created_at == 500);
		CHECK(status_update.activities.at(1).name == "activity two");
		CHECK(status_update.activities.at(1).type == 0);
		CHECK(status_update.activities.at(1).created_at == 1000);
	}
}

TEST_CASE("discord_bot::user can be deserialized from JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::user user;

	SECTION("deserialize all optional fields being null") {
		std::string json = "{\"discriminator\":\"1337\",\"id\":\"123456789\",\"username\":\"eel\"}";

		REQUIRE_NOTHROW(user = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::user>(json));

		CHECK(user.id == "123456789");
		CHECK(user.username == "eel");
		CHECK(user.discriminator == "1337");
		CHECK_FALSE(user.avatar.has_value());
		CHECK_FALSE(user.bot.has_value());
		CHECK_FALSE(user.system.has_value());
		CHECK_FALSE(user.mfa_enabled.has_value());
		CHECK_FALSE(user.locale.has_value());
		CHECK_FALSE(user.verified.has_value());
		CHECK_FALSE(user.email.has_value());
		CHECK_FALSE(user.flags.has_value());
		CHECK_FALSE(user.premium_type.has_value());
		CHECK_FALSE(user.public_flags.has_value());
	}

	SECTION("deserialize some optional fields being null") {
		std::string json = "{\"avatar\":\"avatar\",\"bot\":true,\"discriminator\":\"1337\",\"email\":\"eel@emseers."
		                   "com\",\"flags\":64,\"id\":\"123456789\",\"locale\":null,\"mfa_enabled\":null,"
		                   "\"premium_type\":null,\"public_flags\":null,\"system\":null,\"username\":\"eel\","
		                   "\"verified\":null}";

		REQUIRE_NOTHROW(user = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::user>(json));

		CHECK(user.id == "123456789");
		CHECK(user.username == "eel");
		CHECK(user.discriminator == "1337");
		CHECK(user.avatar.value() == "avatar");
		CHECK(user.bot.value() == true);
		CHECK_FALSE(user.system.has_value());
		CHECK_FALSE(user.mfa_enabled.has_value());
		CHECK_FALSE(user.locale.has_value());
		CHECK_FALSE(user.verified.has_value());
		CHECK(user.email.value() == "eel@emseers.com");
		CHECK(user.flags.value() == 64);
		CHECK_FALSE(user.premium_type.has_value());
		CHECK_FALSE(user.public_flags.has_value());
	}

	SECTION("deserialize no optional fields being null") {
		std::string json = "{\"avatar\":\"avatar\",\"bot\":true,\"discriminator\":\"1337\",\"email\":\"eel@emseers."
		                   "com\",\"flags\":64,\"id\":\"123456789\",\"locale\":\"en\",\"mfa_enabled\":false,"
		                   "\"premium_type\":1,\"public_flags\":64,\"system\":false,\"username\":\"eel\","
		                   "\"verified\":false}";

		REQUIRE_NOTHROW(user = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::user>(json));

		CHECK(user.id == "123456789");
		CHECK(user.username == "eel");
		CHECK(user.discriminator == "1337");
		CHECK(user.avatar.value() == "avatar");
		CHECK(user.bot.value() == true);
		CHECK(user.system.value() == false);
		CHECK(user.mfa_enabled.value() == false);
		CHECK(user.locale.value() == "en");
		CHECK(user.verified.value() == false);
		CHECK(user.email.value() == "eel@emseers.com");
		CHECK(user.flags.value() == 64);
		CHECK(user.premium_type.value() == 1);
		CHECK(user.public_flags.value() == 64);
	}
}

TEST_CASE("discord_bot::unavailable_guild can be deserialized from JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::unavailable_guild unavailable_guild;
	std::string                                      json = "{\"id\":\"123456789\",\"unavailable\":true}";

	REQUIRE_NOTHROW(
	    unavailable_guild = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::unavailable_guild>(json));

	CHECK(unavailable_guild.id == "123456789");
	CHECK(unavailable_guild.unavailable.value() == true);
}

TEST_CASE("discord_bot::partial_application can be deserialized from JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::partial_application partial_application;
	std::string                                        json = "{\"flags\":64,\"id\":\"123456789\"}";

	REQUIRE_NOTHROW(partial_application =
	                    eelbot_framework::parse_from_json<eelbot_framework::discord_bot::partial_application>(json));

	CHECK(partial_application.id == "123456789");
	CHECK(partial_application.flags == 64);
}

TEST_CASE("discord_bot::identify_connection_properties can be deserialized from JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::identify_connection_properties identify_connection_properties;
	std::string json = "{\"$browser\":\"eelbot_framework\",\"$device\":\"eelbot_framework\",\"$os\":\"linux\"}";

	REQUIRE_NOTHROW(
	    identify_connection_properties =
	        eelbot_framework::parse_from_json<eelbot_framework::discord_bot::identify_connection_properties>(json));

	CHECK(identify_connection_properties.os == "linux");
	CHECK(identify_connection_properties.browser == "eelbot_framework");
	CHECK(identify_connection_properties.device == "eelbot_framework");
}

TEST_CASE("discord_bot::identify can be deserialized from JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::identify identify;

	SECTION("deserialize all optional fields being null") {
		std::string json = "{\"intents\":7,\"properties\":{\"$browser\":\"eelbot_framework\",\"$device\":"
		                   "\"eelbot_framework\",\"$os\":\"linux\"},\"token\":\"token\"}";

		REQUIRE_NOTHROW(identify = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::identify>(json));

		CHECK(identify.token == "token");
		CHECK(identify.properties.os == "linux");
		CHECK(identify.properties.browser == "eelbot_framework");
		CHECK(identify.properties.device == "eelbot_framework");
		CHECK(identify.intents == 7);
		CHECK_FALSE(identify.compress.has_value());
		CHECK_FALSE(identify.large_treshold.has_value());
		CHECK_FALSE(identify.shard.has_value());
		CHECK_FALSE(identify.presence.has_value());
		CHECK_FALSE(identify.guild_subscriptions.has_value());
	}

	SECTION("deserialize some optional fields being null") {
		std::string json = "{\"compress\":false,\"guild_subscriptions\":null,\"intents\":7,\"large_treshold\":"
		                   "null,\"presence\":{\"activities\":null,\"afk\":false,\"since\":null,\"status\":"
		                   "\"online\"},\"properties\":{\"$browser\":\"eelbot_framework\",\"$device\":"
		                   "\"eelbot_framework\",\"$os\":\"linux\"},\"shard\":null,\"token\":\"token\"}";

		REQUIRE_NOTHROW(identify = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::identify>(json));

		CHECK(identify.token == "token");
		CHECK(identify.properties.os == "linux");
		CHECK(identify.properties.browser == "eelbot_framework");
		CHECK(identify.properties.device == "eelbot_framework");
		CHECK(identify.intents == 7);
		CHECK(identify.compress.value() == false);
		CHECK_FALSE(identify.large_treshold.has_value());
		CHECK_FALSE(identify.shard.has_value());
		CHECK(identify.presence.value().status == eelbot_framework::discord_bot::status_type::online);
		CHECK(identify.presence.value().afk == false);
		CHECK_FALSE(identify.presence.value().since.has_value());
		CHECK(identify.presence.value().activities.empty());
		CHECK_FALSE(identify.guild_subscriptions.has_value());
	}

	SECTION("deserialize no optional fields being null") {
		std::string json = "{\"compress\":false,\"guild_subscriptions\":false,\"intents\":7,\"large_treshold\":"
		                   "250,\"presence\":{\"activities\":null,\"afk\":false,\"since\":null,\"status\":\"online\"}"
		                   ",\"properties\":{\"$browser\":\"eelbot_framework\",\"$device\":\"eelbot_framework\","
		                   "\"$os\":\"linux\"},\"shard\":[1,2],\"token\":\"token\"}";

		REQUIRE_NOTHROW(identify = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::identify>(json));

		CHECK(identify.token == "token");
		CHECK(identify.properties.os == "linux");
		CHECK(identify.properties.browser == "eelbot_framework");
		CHECK(identify.properties.device == "eelbot_framework");
		CHECK(identify.intents == 7);
		CHECK(identify.compress.value() == false);
		CHECK(identify.large_treshold.value() == 250);
		CHECK(identify.shard.value().shard_id == 1);
		CHECK(identify.shard.value().num_shards == 2);
		CHECK(identify.presence.value().status == eelbot_framework::discord_bot::status_type::online);
		CHECK(identify.presence.value().afk == false);
		CHECK_FALSE(identify.presence.value().since.has_value());
		CHECK(identify.presence.value().activities.empty());
		CHECK(identify.guild_subscriptions.value() == false);
	}
}

TEST_CASE("discord_bot::resume can be deserialized from JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::resume resume;
	std::string                           json = "{\"seq\":5,\"session_id\":\"123456789\",\"token\":\"token\"}";

	REQUIRE_NOTHROW(resume = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::resume>(json));

	CHECK(resume.token == "token");
	CHECK(resume.session_id == "123456789");
	CHECK(resume.seq == 5);
}

TEST_CASE("discord_bot::hello can be deserialized from JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::hello hello;
	std::string                          json = "{\"heartbeat_interval\":45000}";

	REQUIRE_NOTHROW(hello = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::hello>(json));

	CHECK(hello.heartbeat_interval == 45000);
}

TEST_CASE("discord_bot::ready can be deserialized from JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::ready ready;

	SECTION("deserialize all optional fields being null") {
		std::string json = "{\"application\":{\"flags\":64,\"id\":\"123456789\"},\"guilds\":[{\"id\":\"123456789\","
		                   "\"unavailable\":true},{\"id\":\"987654321\",\"unavailable\":true}],"
		                   "\"private_channels\":[],\"session_id\":\"123456789\",\"user\":{\"avatar\":"
		                   "null,\"bot\":null,\"discriminator\":\"1337\",\"email\":null,\"flags\":null,\"id\":"
		                   "\"123456789\",\"locale\":null,\"mfa_enabled\":null,\"premium_type\":null,"
		                   "\"public_flags\":null,\"system\":null,\"username\":\"eel\",\"verified\":null},\"v\":8}";

		REQUIRE_NOTHROW(ready = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::ready>(json));

		CHECK(ready.v == 8);
		CHECK(ready.user_info.id == "123456789");
		CHECK(ready.user_info.username == "eel");
		CHECK(ready.user_info.discriminator == "1337");
		CHECK_FALSE(ready.user_info.avatar.has_value());
		CHECK_FALSE(ready.user_info.bot.has_value());
		CHECK_FALSE(ready.user_info.system.has_value());
		CHECK_FALSE(ready.user_info.mfa_enabled.has_value());
		CHECK_FALSE(ready.user_info.locale.has_value());
		CHECK_FALSE(ready.user_info.verified.has_value());
		CHECK_FALSE(ready.user_info.email.has_value());
		CHECK_FALSE(ready.user_info.flags.has_value());
		CHECK_FALSE(ready.user_info.premium_type.has_value());
		CHECK_FALSE(ready.user_info.public_flags.has_value());
		CHECK(ready.guilds.size() == 2);
		CHECK(ready.guilds.at(0).id == "123456789");
		CHECK(ready.guilds.at(0).unavailable.value() == true);
		CHECK(ready.guilds.at(1).id == "987654321");
		CHECK(ready.guilds.at(1).unavailable.value() == true);
		CHECK(ready.session_id == "123456789");
		CHECK(ready.application.id == "123456789");
		CHECK(ready.application.flags == 64);
		CHECK_FALSE(ready.shard.has_value());
	}

	SECTION("deserialize no optional fields being null") {
		std::string json = "{\"application\":{\"flags\":64,\"id\":\"123456789\"},\"guilds\":[{\"id\":\"123456789\","
		                   "\"unavailable\":true},{\"id\":\"987654321\",\"unavailable\":true}],"
		                   "\"private_channels\":[],\"session_id\":\"123456789\",\"shard\":[1,2],\"user\":"
		                   "{\"avatar\":null,\"bot\":null,\"discriminator\":\"1337\",\"email\":null,\"flags\":null,"
		                   "\"id\":\"123456789\",\"locale\":null,\"mfa_enabled\":null,\"premium_type\":null,"
		                   "\"public_flags\":null,\"system\":null,\"username\":\"eel\",\"verified\":null},\"v\":8}";

		REQUIRE_NOTHROW(ready = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::ready>(json));

		CHECK(ready.v == 8);
		CHECK(ready.user_info.id == "123456789");
		CHECK(ready.user_info.username == "eel");
		CHECK(ready.user_info.discriminator == "1337");
		CHECK_FALSE(ready.user_info.avatar.has_value());
		CHECK_FALSE(ready.user_info.bot.has_value());
		CHECK_FALSE(ready.user_info.system.has_value());
		CHECK_FALSE(ready.user_info.mfa_enabled.has_value());
		CHECK_FALSE(ready.user_info.locale.has_value());
		CHECK_FALSE(ready.user_info.verified.has_value());
		CHECK_FALSE(ready.user_info.email.has_value());
		CHECK_FALSE(ready.user_info.flags.has_value());
		CHECK_FALSE(ready.user_info.premium_type.has_value());
		CHECK_FALSE(ready.user_info.public_flags.has_value());
		CHECK(ready.guilds.size() == 2);
		CHECK(ready.guilds.at(0).id == "123456789");
		CHECK(ready.guilds.at(0).unavailable.value() == true);
		CHECK(ready.guilds.at(1).id == "987654321");
		CHECK(ready.guilds.at(1).unavailable.value() == true);
		CHECK(ready.session_id == "123456789");
		CHECK(ready.application.id == "123456789");
		CHECK(ready.application.flags == 64);
		CHECK(ready.shard.value().shard_id == 1);
		CHECK(ready.shard.value().num_shards == 2);
	}
}

TEST_CASE("discord_bot::payload can be deserialized from JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::payload payload;

	SECTION("deserialize ready payload") {
		std::string json = "{\"d\":{\"application\":{\"flags\":64,\"id\":\"123456789\"},\"guilds\":[{\"id\":"
		                   "\"123456789\",\"unavailable\":true},{\"id\":\"987654321\",\"unavailable\":true}],"
		                   "\"private_channels\":[],\"session_id\":\"123456789\",\"shard\":null,\"user\":{\"avatar\":"
		                   "null,\"bot\":null,\"discriminator\":\"1337\",\"email\":null,\"flags\":null,\"id\":"
		                   "\"123456789\",\"locale\":null,\"mfa_enabled\":null,\"premium_type\":null,"
		                   "\"public_flags\":null,\"system\":null,\"username\":\"eel\",\"verified\":null},\"v\":8},"
		                   "\"op\":0,\"s\":null,\"t\":\"READY\"}";

		REQUIRE_NOTHROW(payload = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::payload>(json));

		eelbot_framework::discord_bot::ready ready;
		CHECK_NOTHROW(ready = std::get<eelbot_framework::discord_bot::ready>(payload.d));

		CHECK(payload.op == eelbot_framework::discord_bot::opcode::dispatch);
		CHECK(ready.v == 8);
		CHECK(ready.user_info.id == "123456789");
		CHECK(ready.user_info.username == "eel");
		CHECK(ready.user_info.discriminator == "1337");
		CHECK_FALSE(ready.user_info.avatar.has_value());
		CHECK_FALSE(ready.user_info.bot.has_value());
		CHECK_FALSE(ready.user_info.system.has_value());
		CHECK_FALSE(ready.user_info.mfa_enabled.has_value());
		CHECK_FALSE(ready.user_info.locale.has_value());
		CHECK_FALSE(ready.user_info.verified.has_value());
		CHECK_FALSE(ready.user_info.email.has_value());
		CHECK_FALSE(ready.user_info.flags.has_value());
		CHECK_FALSE(ready.user_info.premium_type.has_value());
		CHECK_FALSE(ready.user_info.public_flags.has_value());
		CHECK(ready.guilds.size() == 2);
		CHECK(ready.guilds.at(0).id == "123456789");
		CHECK(ready.guilds.at(0).unavailable.value() == true);
		CHECK(ready.guilds.at(1).id == "987654321");
		CHECK(ready.guilds.at(1).unavailable.value() == true);
		CHECK(ready.session_id == "123456789");
		CHECK(ready.application.id == "123456789");
		CHECK(ready.application.flags == 64);
		CHECK_FALSE(ready.shard.has_value());
		CHECK_FALSE(payload.s.has_value());
		CHECK(payload.t.value() == eelbot_framework::discord_bot::event::ready);
	}

	SECTION("deserialize heartbeat payload with null seq") {
		std::string json = "{\"d\":null,\"op\":1,\"s\":null,\"t\":null}";

		REQUIRE_NOTHROW(payload = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::payload>(json));

		CHECK(payload.op == eelbot_framework::discord_bot::opcode::heartbeat);
		CHECK(std::get<int>(payload.d) == -1);
		CHECK_FALSE(payload.s.has_value());
		CHECK_FALSE(payload.t.has_value());
	}

	SECTION("deserialize heartbeat payload without null seq") {
		std::string json = "{\"d\":3,\"op\":1,\"s\":null,\"t\":null}";

		REQUIRE_NOTHROW(payload = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::payload>(json));

		CHECK(payload.op == eelbot_framework::discord_bot::opcode::heartbeat);
		CHECK(std::get<int>(payload.d) == 3);
		CHECK_FALSE(payload.s.has_value());
		CHECK_FALSE(payload.t.has_value());
	}

	SECTION("deserialize identify payload") {
		std::string json = "{\"d\":{\"compress\":null,\"guild_subscriptions\":null,\"intents\":7,"
		                   "\"large_treshold\":null,\"presence\":null,\"properties\":{\"$browser\":"
		                   "\"eelbot_framework\",\"$device\":\"eelbot_framework\",\"$os\":\"linux\"},\"shard\":null,"
		                   "\"token\":\"token\"},\"op\":2,\"s\":null,\"t\":null}";

		REQUIRE_NOTHROW(payload = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::payload>(json));

		eelbot_framework::discord_bot::identify identify;
		CHECK_NOTHROW(identify = std::get<eelbot_framework::discord_bot::identify>(payload.d));

		CHECK(payload.op == eelbot_framework::discord_bot::opcode::identify);
		CHECK(identify.token == "token");
		CHECK(identify.properties.os == "linux");
		CHECK(identify.properties.browser == "eelbot_framework");
		CHECK(identify.properties.device == "eelbot_framework");
		CHECK(identify.intents == 7);
		CHECK_FALSE(identify.compress.has_value());
		CHECK_FALSE(identify.large_treshold.has_value());
		CHECK_FALSE(identify.shard.has_value());
		CHECK_FALSE(identify.presence.has_value());
		CHECK_FALSE(identify.guild_subscriptions.has_value());
		CHECK_FALSE(payload.s.has_value());
		CHECK_FALSE(payload.t.has_value());
	}

	SECTION("deserialize hello payload") {
		std::string json = "{\"d\":{\"heartbeat_interval\":45000},\"op\":10,\"s\":null,\"t\":null}";

		REQUIRE_NOTHROW(payload = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::payload>(json));

		eelbot_framework::discord_bot::hello hello;
		CHECK_NOTHROW(hello = std::get<eelbot_framework::discord_bot::hello>(payload.d));

		CHECK(payload.op == eelbot_framework::discord_bot::opcode::hello);
		CHECK(hello.heartbeat_interval == 45000);
		CHECK_FALSE(payload.s.has_value());
		CHECK_FALSE(payload.t.has_value());
	}

	SECTION("deserialize resume payload") {
		std::string json =
		    "{\"d\":{\"seq\":5,\"session_id\":\"123456789\",\"token\":\"token\"},\"op\":6,\"s\":null,\"t\":"
		    "null}";

		REQUIRE_NOTHROW(payload = eelbot_framework::parse_from_json<eelbot_framework::discord_bot::payload>(json));

		eelbot_framework::discord_bot::resume resume;
		CHECK_NOTHROW(resume = std::get<eelbot_framework::discord_bot::resume>(payload.d));

		CHECK(payload.op == eelbot_framework::discord_bot::opcode::resume);
		CHECK(resume.token == "token");
		CHECK(resume.session_id == "123456789");
		CHECK(resume.seq == 5);
		CHECK_FALSE(payload.s.has_value());
		CHECK_FALSE(payload.t.has_value());
	}
}
