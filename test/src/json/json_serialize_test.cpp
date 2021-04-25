// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#include "catch2/catch_test_macros.hpp"
#include "eelbot_framework/discord_bot/structs.hpp"
#include "eelbot_framework/json.hpp"

TEST_CASE("discord_bot::session_start_limit can be serialized to JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::session_start_limit session_start_limit;
	session_start_limit.total       = 1;
	session_start_limit.remaining   = -2;
	session_start_limit.reset_after = 0;

	REQUIRE(eelbot_framework::to_json_str(session_start_limit) == "{\"remaining\":-2,\"reset_after\":0,\"total\":1}");
}

TEST_CASE("discord_bot::gateway_response can be serialized to JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::gateway_response gateway_response;
	gateway_response.url = "https://github.com/Emseers/eelbot-framework";

	REQUIRE(
	    eelbot_framework::to_json_str(gateway_response) == "{\"url\":\"https://github.com/Emseers/eelbot-framework\"}");
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

	REQUIRE(eelbot_framework::to_json_str(gateway_bot_response) ==
	        "{\"session_start_limit\":{\"remaining\":-2,\"reset_after\":0,\"total\":1},"
	        "\"shards\":99,\"url\":\"https://github.com/Emseers/eelbot-framework\"}");
}

TEST_CASE("discord_bot::shard_info can be serialized to JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::shard_info shard_info;
	shard_info.shard_id   = 1;
	shard_info.num_shards = 2;

	REQUIRE(eelbot_framework::to_json_str(shard_info) == "[1,2]");
}

TEST_CASE("discord_bot::party_size_info can be serialized to JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::party_size_info party_size_info;
	party_size_info.current_size = 3;
	party_size_info.max_size     = 5;

	REQUIRE(eelbot_framework::to_json_str(party_size_info) == "[3,5]");
}

TEST_CASE("discord_bot::activity_timestamps can be serialized to JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::activity_timestamps activity_timestamps;

	SECTION("serialize all optional fields being null") {
		REQUIRE(eelbot_framework::to_json_str(activity_timestamps) == "{\"end\":null,\"start\":null}");
	}

	SECTION("serialize some optional fields being null") {
		activity_timestamps.start = 500;

		REQUIRE(eelbot_framework::to_json_str(activity_timestamps) == "{\"end\":null,\"start\":500}");
	}

	SECTION("serialize no optional fields being null") {
		activity_timestamps.start = 500;
		activity_timestamps.end   = 1000;

		REQUIRE(eelbot_framework::to_json_str(activity_timestamps) == "{\"end\":1000,\"start\":500}");
	}
}

TEST_CASE("discord_bot::activity_emoji can be serialized to JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::activity_emoji activity_emoji;
	activity_emoji.name = "eel";

	SECTION("serialize all optional fields being null") {
		REQUIRE(eelbot_framework::to_json_str(activity_emoji) == "{\"animated\":null,\"id\":null,\"name\":\"eel\"}");
	}

	SECTION("serialize some optional fields being null") {
		activity_emoji.id = "123456789";

		REQUIRE(eelbot_framework::to_json_str(activity_emoji) ==
		        "{\"animated\":null,\"id\":\"123456789\",\"name\":\"eel\"}");
	}

	SECTION("serialize no optional fields being null") {
		activity_emoji.id       = "123456789";
		activity_emoji.animated = false;

		REQUIRE(eelbot_framework::to_json_str(activity_emoji) ==
		        "{\"animated\":false,\"id\":\"123456789\",\"name\":\"eel\"}");
	}
}

TEST_CASE("discord_bot::activity_party can be serialized to JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::activity_party activity_party;

	SECTION("serialize all optional fields being null") {
		REQUIRE(eelbot_framework::to_json_str(activity_party) == "{\"id\":null,\"size\":null}");
	}

	SECTION("serialize some optional fields being null") {
		activity_party.id = "123456789";

		REQUIRE(eelbot_framework::to_json_str(activity_party) == "{\"id\":\"123456789\",\"size\":null}");
	}

	SECTION("serialize no optional fields being null") {
		eelbot_framework::discord_bot::party_size_info party_size_info;
		party_size_info.current_size = 3;
		party_size_info.max_size     = 5;

		activity_party.id   = "123456789";
		activity_party.size = party_size_info;

		REQUIRE(eelbot_framework::to_json_str(activity_party) == "{\"id\":\"123456789\",\"size\":[3,5]}");
	}
}

TEST_CASE("discord_bot::activity_assets can be serialized to JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::activity_assets activity_assets;

	SECTION("serialize all optional fields being null") {
		REQUIRE(eelbot_framework::to_json_str(activity_assets) ==
		        "{\"large_image\":null,\"large_text\":null,\"small_image\":null,\"small_text\":null}");
	}

	SECTION("serialize some optional fields being null") {
		activity_assets.large_image = "123456789";
		activity_assets.small_text  = "tooltip";

		REQUIRE(eelbot_framework::to_json_str(activity_assets) ==
		        "{\"large_image\":\"123456789\",\"large_text\":null,\"small_image\":null,"
		        "\"small_text\":\"tooltip\"}");
	}

	SECTION("serialize no optional fields being null") {
		activity_assets.large_image = "123456789";
		activity_assets.large_text  = "tooltip";
		activity_assets.small_image = "123456789";
		activity_assets.small_text  = "tooltip";

		REQUIRE(eelbot_framework::to_json_str(activity_assets) ==
		        "{\"large_image\":\"123456789\",\"large_text\":\"tooltip\",\"small_image\":\"123456789\","
		        "\"small_text\":\"tooltip\"}");
	}
}

TEST_CASE("discord_bot::activity_secrets can be serialized to JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::activity_secrets activity_secrets;

	SECTION("serialize all optional fields being null") {
		REQUIRE(eelbot_framework::to_json_str(activity_secrets) == "{\"join\":null,\"match\":null,\"spectate\":null}");
	}

	SECTION("serialize some optional fields being null") {
		activity_secrets.join = "secret one";

		REQUIRE(eelbot_framework::to_json_str(activity_secrets) ==
		        "{\"join\":\"secret one\",\"match\":null,\"spectate\":null}");
	}

	SECTION("serialize no optional fields being null") {
		activity_secrets.join     = "secret one";
		activity_secrets.spectate = "secret two";
		activity_secrets.match    = "secret three";

		REQUIRE(eelbot_framework::to_json_str(activity_secrets) ==
		        "{\"join\":\"secret one\",\"match\":\"secret three\",\"spectate\":\"secret two\"}");
	}
}

TEST_CASE("discord_bot::activity can be serialized to JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::activity activity;
	activity.name       = "activity";
	activity.type       = 1;
	activity.created_at = 500;

	SECTION("serialize all optional fields being null") {
		REQUIRE(eelbot_framework::to_json_str(activity) ==
		        "{\"application_id\":null,\"assets\":null,\"created_at\":500,\"details\":null,"
		        "\"emoji\":null,\"flags\":null,\"instance\":null,\"name\":\"activity\",\"party\":null,"
		        "\"secrets\":null,\"state\":null,\"timestamps\":null,\"type\":1,\"url\":null}");
	}

	SECTION("serialize some optional fields being null") {
		eelbot_framework::discord_bot::activity_timestamps activity_timestamps;
		activity_timestamps.start = 500;

		eelbot_framework::discord_bot::activity_secrets activity_secrets;

		activity.url        = "https://github.com/Emseers/eelbot-framework";
		activity.timestamps = activity_timestamps;
		activity.secrets    = activity_secrets;

		REQUIRE(eelbot_framework::to_json_str(activity) ==
		        "{\"application_id\":null,\"assets\":null,\"created_at\":500,\"details\":null,"
		        "\"emoji\":null,\"flags\":null,\"instance\":null,\"name\":\"activity\",\"party\":null,"
		        "\"secrets\":{\"join\":null,\"match\":null,\"spectate\":null},\"state\":null,"
		        "\"timestamps\":{\"end\":null,\"start\":500},\"type\":1,\"url\":\"https://github.com/"
		        "Emseers/eelbot-framework\"}");
	}

	SECTION("serialize no optional fields being null") {
		eelbot_framework::discord_bot::activity_timestamps activity_timestamps;
		activity_timestamps.start = 500;

		eelbot_framework::discord_bot::activity_emoji activity_emoji;
		activity_emoji.name = "eel";

		eelbot_framework::discord_bot::activity_party activity_party;

		eelbot_framework::discord_bot::activity_assets activity_assets;

		eelbot_framework::discord_bot::activity_secrets activity_secrets;

		activity.url            = "https://github.com/Emseers/eelbot-framework";
		activity.timestamps     = activity_timestamps;
		activity.application_id = "123456789";
		activity.details        = "something";
		activity.state          = "in a match";
		activity.emoji          = activity_emoji;
		activity.party          = activity_party;
		activity.assets         = activity_assets;
		activity.secrets        = activity_secrets;
		activity.instance       = true;
		activity.flags          = 512;

		REQUIRE(eelbot_framework::to_json_str(activity) ==
		        "{\"application_id\":\"123456789\",\"assets\":{\"large_image\":null,\"large_text\":"
		        "null,\"small_image\":null,\"small_text\":null},\"created_at\":500,\"details\":"
		        "\"something\",\"emoji\":{\"animated\":null,\"id\":null,\"name\":\"eel\"},\"flags\":512,"
		        "\"instance\":true,\"name\":\"activity\",\"party\":{\"id\":null,\"size\":null},\"secrets\":"
		        "{\"join\":null,\"match\":null,\"spectate\":null},\"state\":\"in a match\",\"timestamps\":"
		        "{\"end\":null,\"start\":500},\"type\":1,\"url\":\"https://github.com/Emseers/eelbot-"
		        "framework\"}");
	}
}

TEST_CASE("discord_bot::status_type can be serialized to JSON", "[unit-test][json]") {
	SECTION("serialize status_type = online") {
		REQUIRE(eelbot_framework::to_json_str(eelbot_framework::discord_bot::status_type::online) == "\"online\"");
	}

	SECTION("serialize status_type = dnd") {
		REQUIRE(eelbot_framework::to_json_str(eelbot_framework::discord_bot::status_type::dnd) == "\"dnd\"");
	}

	SECTION("serialize status_type = idle") {
		REQUIRE(eelbot_framework::to_json_str(eelbot_framework::discord_bot::status_type::idle) == "\"idle\"");
	}

	SECTION("serialize status_type = invisible") {
		REQUIRE(
		    eelbot_framework::to_json_str(eelbot_framework::discord_bot::status_type::invisible) == "\"invisible\"");
	}

	SECTION("serialize status_type = offline") {
		REQUIRE(eelbot_framework::to_json_str(eelbot_framework::discord_bot::status_type::offline) == "\"offline\"");
	}
}

TEST_CASE("discord_bot::status_update can be serialized to JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::status_update status_update;
	status_update.status = eelbot_framework::discord_bot::status_type::online;
	status_update.afk    = false;

	SECTION("serialize all optional fields being null") {
		REQUIRE(eelbot_framework::to_json_str(status_update) ==
		        "{\"activities\":null,\"afk\":false,\"since\":null,\"status\":\"online\"}");
	}

	SECTION("serialize some optional fields being null") {
		status_update.since = 500;

		REQUIRE(eelbot_framework::to_json_str(status_update) ==
		        "{\"activities\":null,\"afk\":false,\"since\":500,\"status\":\"online\"}");
	}

	SECTION("serialize no optional fields being null") {
		eelbot_framework::discord_bot::activity activity_one;
		activity_one.name       = "activity one";
		activity_one.type       = 1;
		activity_one.created_at = 500;

		eelbot_framework::discord_bot::activity activity_two;
		activity_two.name       = "activity two";
		activity_two.type       = 0;
		activity_two.created_at = 1000;

		status_update.since = 500;
		status_update.activities.push_back(activity_one);
		status_update.activities.push_back(activity_two);

		REQUIRE(eelbot_framework::to_json_str(status_update) ==
		        "{\"activities\":[{\"application_id\":null,\"assets\":null,\"created_at\":500,"
		        "\"details\":null,\"emoji\":null,\"flags\":null,\"instance\":null,\"name\":\"activity "
		        "one\",\"party\":null,\"secrets\":null,\"state\":null,\"timestamps\":null,\"type\":1,"
		        "\"url\":null},{\"application_id\":null,\"assets\":null,\"created_at\":1000,\"details\":"
		        "null,\"emoji\":null,\"flags\":null,\"instance\":null,\"name\":\"activity two\",\"party\":"
		        "null,\"secrets\":null,\"state\":null,\"timestamps\":null,\"type\":0,\"url\":null}],"
		        "\"afk\":false,\"since\":500,\"status\":\"online\"}");
	}
}

TEST_CASE("discord_bot::user can be serialized to JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::user user;
	user.id            = "123456789";
	user.username      = "eel";
	user.discriminator = "1337";

	SECTION("serialize all optional fields being null") {
		REQUIRE(eelbot_framework::to_json_str(user) ==
		        "{\"avatar\":null,\"bot\":null,\"discriminator\":\"1337\",\"email\":null,\"flags\":null,"
		        "\"id\":\"123456789\",\"locale\":null,\"mfa_enabled\":null,\"premium_type\":null,"
		        "\"public_flags\":null,\"system\":null,\"username\":\"eel\",\"verified\":null}");
	}

	SECTION("serialize some optional fields being null") {
		user.avatar = "avatar";
		user.bot    = true;
		user.email  = "eel@emseers.com";
		user.flags  = 64;

		REQUIRE(eelbot_framework::to_json_str(user) ==
		        "{\"avatar\":\"avatar\",\"bot\":true,\"discriminator\":\"1337\",\"email\":\"eel@emseers."
		        "com\",\"flags\":64,\"id\":\"123456789\",\"locale\":null,\"mfa_enabled\":null,"
		        "\"premium_type\":null,\"public_flags\":null,\"system\":null,\"username\":\"eel\","
		        "\"verified\":null}");
	}

	SECTION("serialize no optional fields being null") {
		user.avatar       = "avatar";
		user.bot          = true;
		user.system       = false;
		user.mfa_enabled  = false;
		user.locale       = "en";
		user.verified     = false;
		user.email        = "eel@emseers.com";
		user.flags        = 64;
		user.premium_type = 1;
		user.public_flags = 64;

		REQUIRE(eelbot_framework::to_json_str(user) ==
		        "{\"avatar\":\"avatar\",\"bot\":true,\"discriminator\":\"1337\",\"email\":\"eel@emseers."
		        "com\",\"flags\":64,\"id\":\"123456789\",\"locale\":\"en\",\"mfa_enabled\":false,"
		        "\"premium_type\":1,\"public_flags\":64,\"system\":false,\"username\":\"eel\","
		        "\"verified\":false}");
	}
}

TEST_CASE("discord_bot::unavailable_guild can be serialized to JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::unavailable_guild unavailable_guild;
	unavailable_guild.id          = "123456789";
	unavailable_guild.unavailable = true;

	REQUIRE(eelbot_framework::to_json_str(unavailable_guild) == "{\"id\":\"123456789\",\"unavailable\":true}");
}

TEST_CASE("discord_bot::partial_application can be serialized to JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::partial_application partial_application;
	partial_application.id    = "123456789";
	partial_application.flags = 64;

	REQUIRE(eelbot_framework::to_json_str(partial_application) == "{\"flags\":64,\"id\":\"123456789\"}");
}

TEST_CASE("discord_bot::identify_connection_properties can be serialized to JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::identify_connection_properties identify_connection_properties;
	identify_connection_properties.os      = "linux";
	identify_connection_properties.browser = "eelbot_framework";
	identify_connection_properties.device  = "eelbot_framework";

	REQUIRE(eelbot_framework::to_json_str(identify_connection_properties) ==
	        "{\"$browser\":\"eelbot_framework\",\"$device\":\"eelbot_framework\",\"$os\":\"linux\"}");
}

TEST_CASE("discord_bot::identify can be serialized to JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::identify_connection_properties identify_connection_properties;
	identify_connection_properties.os      = "linux";
	identify_connection_properties.browser = "eelbot_framework";
	identify_connection_properties.device  = "eelbot_framework";

	eelbot_framework::discord_bot::identify identify;
	identify.token      = "token";
	identify.properties = identify_connection_properties;
	identify.intents    = 7;

	SECTION("serialize all optional fields being null") {
		REQUIRE(eelbot_framework::to_json_str(identify) ==
		        "{\"compress\":null,\"guild_subscriptions\":null,\"intents\":7,\"large_treshold\":"
		        "null,\"presence\":null,\"properties\":{\"$browser\":\"eelbot_framework\",\"$device\":"
		        "\"eelbot_framework\",\"$os\":\"linux\"},\"shard\":null,\"token\":\"token\"}");
	}

	SECTION("serialize some optional fields being null") {
		eelbot_framework::discord_bot::status_update status_update;
		status_update.status = eelbot_framework::discord_bot::status_type::online;
		status_update.afk    = false;

		identify.compress = false;
		identify.presence = status_update;

		REQUIRE(eelbot_framework::to_json_str(identify) ==
		        "{\"compress\":false,\"guild_subscriptions\":null,\"intents\":7,\"large_treshold\":"
		        "null,\"presence\":{\"activities\":null,\"afk\":false,\"since\":null,\"status\":"
		        "\"online\"},\"properties\":{\"$browser\":\"eelbot_framework\",\"$device\":"
		        "\"eelbot_framework\",\"$os\":\"linux\"},\"shard\":null,\"token\":\"token\"}");
	}

	SECTION("serialize no optional fields being null") {
		eelbot_framework::discord_bot::shard_info shard_info;
		shard_info.shard_id   = 1;
		shard_info.num_shards = 2;

		eelbot_framework::discord_bot::status_update status_update;
		status_update.status = eelbot_framework::discord_bot::status_type::online;
		status_update.afk    = false;

		identify.compress            = false;
		identify.large_treshold      = 250;
		identify.shard               = shard_info;
		identify.presence            = status_update;
		identify.guild_subscriptions = false;

		REQUIRE(eelbot_framework::to_json_str(identify) ==
		        "{\"compress\":false,\"guild_subscriptions\":false,\"intents\":7,\"large_treshold\":"
		        "250,\"presence\":{\"activities\":null,\"afk\":false,\"since\":null,\"status\":\"online\"}"
		        ",\"properties\":{\"$browser\":\"eelbot_framework\",\"$device\":\"eelbot_framework\","
		        "\"$os\":\"linux\"},\"shard\":[1,2],\"token\":\"token\"}");
	}
}

TEST_CASE("discord_bot::resume can be serialized to JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::resume resume;
	resume.token      = "token";
	resume.session_id = "123456789";
	resume.seq        = 5;

	REQUIRE(eelbot_framework::to_json_str(resume) == "{\"seq\":5,\"session_id\":\"123456789\",\"token\":\"token\"}");
}

TEST_CASE("discord_bot::hello can be serialized to JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::hello hello;
	hello.heartbeat_interval = 45000;

	REQUIRE(eelbot_framework::to_json_str(hello) == "{\"heartbeat_interval\":45000}");
}

TEST_CASE("discord_bot::ready can be serialized to JSON", "[unit-test][json]") {
	eelbot_framework::discord_bot::user user;
	user.id            = "123456789";
	user.username      = "eel";
	user.discriminator = "1337";

	eelbot_framework::discord_bot::unavailable_guild unavailable_guild_1;
	unavailable_guild_1.id          = "123456789";
	unavailable_guild_1.unavailable = true;

	eelbot_framework::discord_bot::unavailable_guild unavailable_guild_2;
	unavailable_guild_2.id          = "987654321";
	unavailable_guild_2.unavailable = true;

	eelbot_framework::discord_bot::partial_application partial_application;
	partial_application.id    = "123456789";
	partial_application.flags = 64;

	eelbot_framework::discord_bot::ready ready;
	ready.v         = 8;
	ready.user_info = user;
	ready.guilds.push_back(unavailable_guild_1);
	ready.guilds.push_back(unavailable_guild_2);
	ready.session_id  = "123456789";
	ready.application = partial_application;

	SECTION("serialize all optional fields being null") {
		REQUIRE(eelbot_framework::to_json_str(ready) ==
		        "{\"application\":{\"flags\":64,\"id\":\"123456789\"},\"guilds\":[{\"id\":\"123456789\","
		        "\"unavailable\":true},{\"id\":\"987654321\",\"unavailable\":true}],"
		        "\"private_channels\":[],\"session_id\":\"123456789\",\"shard\":null,\"user\":{\"avatar\":"
		        "null,\"bot\":null,\"discriminator\":\"1337\",\"email\":null,\"flags\":null,\"id\":"
		        "\"123456789\",\"locale\":null,\"mfa_enabled\":null,\"premium_type\":null,"
		        "\"public_flags\":null,\"system\":null,\"username\":\"eel\",\"verified\":null},\"v\":8}");
	}

	SECTION("serialize no optional fields being null") {
		eelbot_framework::discord_bot::shard_info shard_info;
		shard_info.shard_id   = 1;
		shard_info.num_shards = 2;

		ready.shard = shard_info;

		REQUIRE(eelbot_framework::to_json_str(ready) ==
		        "{\"application\":{\"flags\":64,\"id\":\"123456789\"},\"guilds\":[{\"id\":\"123456789\","
		        "\"unavailable\":true},{\"id\":\"987654321\",\"unavailable\":true}],"
		        "\"private_channels\":[],\"session_id\":\"123456789\",\"shard\":[1,2],\"user\":"
		        "{\"avatar\":null,\"bot\":null,\"discriminator\":\"1337\",\"email\":null,\"flags\":null,"
		        "\"id\":\"123456789\",\"locale\":null,\"mfa_enabled\":null,\"premium_type\":null,"
		        "\"public_flags\":null,\"system\":null,\"username\":\"eel\",\"verified\":null},\"v\":8}");
	}
}

TEST_CASE("discord_bot::payload can be serialized to JSON", "[unit-test][json]") {
	SECTION("serialize ready payload") {
		eelbot_framework::discord_bot::user user;
		user.id            = "123456789";
		user.username      = "eel";
		user.discriminator = "1337";

		eelbot_framework::discord_bot::unavailable_guild unavailable_guild_1;
		unavailable_guild_1.id          = "123456789";
		unavailable_guild_1.unavailable = true;

		eelbot_framework::discord_bot::unavailable_guild unavailable_guild_2;
		unavailable_guild_2.id          = "987654321";
		unavailable_guild_2.unavailable = true;

		eelbot_framework::discord_bot::partial_application partial_application;
		partial_application.id    = "123456789";
		partial_application.flags = 64;

		eelbot_framework::discord_bot::ready ready;
		ready.v         = 8;
		ready.user_info = user;
		ready.guilds.push_back(unavailable_guild_1);
		ready.guilds.push_back(unavailable_guild_2);
		ready.session_id  = "123456789";
		ready.application = partial_application;

		eelbot_framework::discord_bot::payload payload;
		payload.op = eelbot_framework::discord_bot::opcode::dispatch;
		payload.t  = eelbot_framework::discord_bot::event::ready;
		payload.d  = ready;

		REQUIRE(eelbot_framework::to_json_str(payload) ==
		        "{\"d\":{\"application\":{\"flags\":64,\"id\":\"123456789\"},\"guilds\":[{\"id\":"
		        "\"123456789\",\"unavailable\":true},{\"id\":\"987654321\",\"unavailable\":true}],"
		        "\"private_channels\":[],\"session_id\":\"123456789\",\"shard\":null,\"user\":{\"avatar\":"
		        "null,\"bot\":null,\"discriminator\":\"1337\",\"email\":null,\"flags\":null,\"id\":"
		        "\"123456789\",\"locale\":null,\"mfa_enabled\":null,\"premium_type\":null,"
		        "\"public_flags\":null,\"system\":null,\"username\":\"eel\",\"verified\":null},\"v\":8},"
		        "\"op\":0,\"s\":null,\"t\":\"READY\"}");
	}

	SECTION("serialize heartbeat payload with null seq") {
		eelbot_framework::discord_bot::payload payload;
		payload.op = eelbot_framework::discord_bot::opcode::heartbeat;
		payload.d  = -1;

		REQUIRE(eelbot_framework::to_json_str(payload) == "{\"d\":null,\"op\":1,\"s\":null,\"t\":null}");
	}

	SECTION("serialize heartbeat payload without null seq") {
		eelbot_framework::discord_bot::payload payload;
		payload.op = eelbot_framework::discord_bot::opcode::heartbeat;
		payload.d  = 3;

		REQUIRE(eelbot_framework::to_json_str(payload) == "{\"d\":3,\"op\":1,\"s\":null,\"t\":null}");
	}

	SECTION("serialize identify payload") {
		eelbot_framework::discord_bot::identify_connection_properties identify_connection_properties;
		identify_connection_properties.os      = "linux";
		identify_connection_properties.browser = "eelbot_framework";
		identify_connection_properties.device  = "eelbot_framework";

		eelbot_framework::discord_bot::identify identify;
		identify.token      = "token";
		identify.properties = identify_connection_properties;
		identify.intents    = 7;

		eelbot_framework::discord_bot::payload payload;
		payload.op = eelbot_framework::discord_bot::opcode::identify;
		payload.d  = identify;

		REQUIRE(eelbot_framework::to_json_str(payload) ==
		        "{\"d\":{\"compress\":null,\"guild_subscriptions\":null,\"intents\":7,"
		        "\"large_treshold\":null,\"presence\":null,\"properties\":{\"$browser\":"
		        "\"eelbot_framework\",\"$device\":\"eelbot_framework\",\"$os\":\"linux\"},\"shard\":null,"
		        "\"token\":\"token\"},\"op\":2,\"s\":null,\"t\":null}");
	}

	SECTION("serialize hello payload") {
		eelbot_framework::discord_bot::hello hello;
		hello.heartbeat_interval = 45000;

		eelbot_framework::discord_bot::payload payload;
		payload.op = eelbot_framework::discord_bot::opcode::hello;
		payload.d  = hello;

		REQUIRE(eelbot_framework::to_json_str(payload) ==
		        "{\"d\":{\"heartbeat_interval\":45000},\"op\":10,\"s\":null,\"t\":null}");
	}

	SECTION("serialize resume payload") {
		eelbot_framework::discord_bot::resume resume;
		resume.token      = "token";
		resume.session_id = "123456789";
		resume.seq        = 5;

		eelbot_framework::discord_bot::payload payload;
		payload.op = eelbot_framework::discord_bot::opcode::resume;
		payload.d  = resume;

		REQUIRE(eelbot_framework::to_json_str(payload) ==
		        "{\"d\":{\"seq\":5,\"session_id\":\"123456789\",\"token\":\"token\"},\"op\":6,\"s\":null,\"t\":"
		        "null}");
	}
}
