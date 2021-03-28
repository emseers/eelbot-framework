// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#ifndef EELBOT_FRAMEWORK_JSON_DISCORD_BOT_H
#define EELBOT_FRAMEWORK_JSON_DISCORD_BOT_H

#include "eelbot_framework/discord_bot/structs.hpp"
#include "eelbot_framework/json/common.hpp"
#include "nlohmann/json.hpp"

namespace eelbot_framework {

namespace discord_bot {

inline void to_json(nlohmann::json &j, const session_start_limit &ssl) {
	j = nlohmann::json{
	    {"total", ssl.total},
	    {"remaining", ssl.remaining},
	    {"reset_after", ssl.reset_after},
	};
}

inline void from_json(const nlohmann::json &j, session_start_limit &ssl) {
	j.at("total").get_to(ssl.total);
	j.at("remaining").get_to(ssl.remaining);
	j.at("reset_after").get_to(ssl.reset_after);
}

inline void to_json(nlohmann::json &j, const gateway_response &gr) {
	j = nlohmann::json{
	    {"url", gr.url},
	};
}

inline void from_json(const nlohmann::json &j, gateway_response &gr) {
	j.at("url").get_to(gr.url);
}

inline void to_json(nlohmann::json &j, const gateway_bot_response &gbr) {
	j = nlohmann::json{
	    {"url", gbr.url},
	    {"shards", gbr.shards},
	    {"session_start_limit", gbr.sess_start_limit},
	};
}

inline void from_json(const nlohmann::json &j, gateway_bot_response &gbr) {
	j.at("url").get_to(gbr.url);
	j.at("shards").get_to(gbr.shards);
	j.at("session_start_limit").get_to(gbr.sess_start_limit);
}

inline void to_json(nlohmann::json &j, const event_hello &eh) {
	j = nlohmann::json{
	    {"heartbeat_interval", eh.heartbeat_interval},
	};
}

inline void from_json(const nlohmann::json &j, event_hello &eh) {
	j.at("heartbeat_interval").get_to(eh.heartbeat_interval);
}

inline void to_json(nlohmann::json &j, const payload &p) {
	j = nlohmann::json{
	    {"op", p.op},
	    {"s", p.s},
	    {"t", p.t},
	};

	switch (p.op) {
	case 10:
		j["d"] = std::get<event_hello>(p.d);
		break;
	}
}

inline void from_json(const nlohmann::json &j, payload &p) {
	j.at("op").get_to(p.op);

	switch (p.op) {
	case 10:
		event_hello event_data;
		j.at("d").get_to(event_data);
		p.d = event_data;
		break;
	}

	if (j.find("s") != j.end()) {
		j.at("s").get_to(p.s);
	}

	if (j.find("t") != j.end()) {
		j.at("t").get_to(p.t);
	}
}

} // namespace discord_bot

} // namespace eelbot_framework

#endif
