// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#ifndef EELBOT_FRAMEWORK_JSON_DISCORD_BOT_H
#define EELBOT_FRAMEWORK_JSON_DISCORD_BOT_H

#include "eelbot_framework/discord_bot/codes.hpp"
#include "eelbot_framework/discord_bot/structs.hpp"
#include "eelbot_framework/json/common.hpp"
#include "nlohmann/json.hpp"

namespace eelbot_framework {

namespace discord_bot {

inline void to_json(nlohmann::json &j, const session_start_limit &ssl) {
	j = {
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
	j = {
	    {"url", gr.url},
	};
}

inline void from_json(const nlohmann::json &j, gateway_response &gr) {
	j.at("url").get_to(gr.url);
}

inline void to_json(nlohmann::json &j, const gateway_bot_response &gbr) {
	j = {
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

inline void to_json(nlohmann::json &j, const shard_info &si) {
	j = {si.shard_id, si.num_shards};
}

inline void from_json(const nlohmann::json &j, shard_info &si) {
	auto shard    = j.get<std::array<int, 2>>();
	si.shard_id   = shard[0];
	si.num_shards = shard[1];
}

inline void to_json(nlohmann::json &j, const party_size_info &psi) {
	j = {psi.current_size, psi.max_size};
}

inline void from_json(const nlohmann::json &j, party_size_info &psi) {
	auto party_size  = j.get<std::array<int, 2>>();
	psi.current_size = party_size[0];
	psi.max_size     = party_size[1];
}

inline void to_json(nlohmann::json &j, const activity_timestamps &at) {
	j = {
	    {"start", at.start},
	    {"end", at.end},
	};
}

inline void from_json(const nlohmann::json &j, activity_timestamps &at) {
	get_optional(j, "start").get_to(at.start);
	get_optional(j, "end").get_to(at.end);
}

inline void to_json(nlohmann::json &j, const activity_emoji &ae) {
	j = {
	    {"name", ae.name},
	    {"id", ae.id},
	    {"animated", ae.animated},
	};
}

inline void from_json(const nlohmann::json &j, activity_emoji &ae) {
	j.at("name").get_to(ae.name);
	get_optional(j, "id").get_to(ae.id);
	get_optional(j, "animated").get_to(ae.animated);
}

inline void to_json(nlohmann::json &j, const activity_party &ap) {
	j = {
	    {"id", ap.id},
	    {"size", ap.size},
	};
}

inline void from_json(const nlohmann::json &j, activity_party &ap) {
	get_optional(j, "id").get_to(ap.id);
	get_optional(j, "size").get_to(ap.size);
}

inline void to_json(nlohmann::json &j, const activity_assets &aa) {
	j = {
	    {"large_image", aa.large_image},
	    {"large_text", aa.large_text},
	    {"small_image", aa.small_image},
	    {"small_text", aa.small_text},
	};
}

inline void from_json(const nlohmann::json &j, activity_assets &aa) {
	get_optional(j, "large_image").get_to(aa.large_image);
	get_optional(j, "large_text").get_to(aa.large_text);
	get_optional(j, "small_image").get_to(aa.small_image);
	get_optional(j, "small_text").get_to(aa.small_text);
}

inline void to_json(nlohmann::json &j, const activity_secrets &as) {
	j = {
	    {"join", as.join},
	    {"spectate", as.spectate},
	    {"match", as.match},
	};
}

inline void from_json(const nlohmann::json &j, activity_secrets &as) {
	get_optional(j, "join").get_to(as.join);
	get_optional(j, "spectate").get_to(as.spectate);
	get_optional(j, "match").get_to(as.match);
}

inline void to_json(nlohmann::json &j, const activity &a) {
	j = {
	    {"name", a.name},
	    {"type", a.type},
	    {"url", a.url},
	    {"created_at", a.created_at},
	    {"timestamps", a.timestamps},
	    {"application_id", a.application_id},
	    {"details", a.details},
	    {"state", a.state},
	    {"emoji", a.emoji},
	    {"party", a.party},
	    {"assets", a.assets},
	    {"secrets", a.secrets},
	    {"instance", a.instance},
	    {"flags", a.flags},
	};
}

inline void from_json(const nlohmann::json &j, activity &a) {
	j.at("name").get_to(a.name);
	j.at("type").get_to(a.type);
	get_optional(j, "url").get_to(a.url);
	j.at("created_at").get_to(a.created_at);
	get_optional(j, "timestamps").get_to(a.timestamps);
	get_optional(j, "application_id").get_to(a.application_id);
	get_optional(j, "details").get_to(a.details);
	get_optional(j, "state").get_to(a.state);
	get_optional(j, "emoji").get_to(a.emoji);
	get_optional(j, "party").get_to(a.party);
	get_optional(j, "assets").get_to(a.assets);
	get_optional(j, "secrets").get_to(a.secrets);
	get_optional(j, "instance").get_to(a.instance);
	get_optional(j, "flags").get_to(a.flags);
}

inline void to_json(nlohmann::json &j, const status_type &st) {
	switch (st) {
	case status_type::online:
		j = "online";
		break;
	case status_type::dnd:
		j = "dnd";
		break;
	case status_type::idle:
		j = "idle";
		break;
	case status_type::invisible:
		j = "invisible";
		break;
	case status_type::offline:
		j = "offline";
		break;
	default:
		throw std::out_of_range("status type out of range");
	}
}

inline void from_json(const nlohmann::json &j, status_type &st) {
	auto status = j.get<std::string>();
	if (status == "online") {
		st = status_type::online;
	} else if (status == "dnd") {
		st = status_type::dnd;
	} else if (status == "idle") {
		st = status_type::idle;
	} else if (status == "invisible") {
		st = status_type::invisible;
	} else if (status == "offline") {
		st = status_type::offline;
	} else {
		throw std::out_of_range("status type '+ status +' is invalid");
	}
}

inline void to_json(nlohmann::json &j, const status_update &su) {
	j = {
	    {"since", su.since},
	    {"status", su.status},
	    {"afk", su.afk},
	};

	if (!su.activities.empty()) {
		j["activities"] = su.activities;
	}
}

inline void from_json(const nlohmann::json &j, status_update &su) {
	get_optional(j, "since").get_to(su.since);
	j.at("status").get_to(su.status);
	j.at("afk").get_to(su.afk);

	if (!get_optional(j, "activities").is_null()) {
		j.at("activities").get_to(su.activities);
	}
}

inline void to_json(nlohmann::json &j, const user &u) {
	j = {
	    {"id", u.id},
	    {"username", u.username},
	    {"discriminator", u.discriminator},
	    {"avatar", u.avatar},
	    {"bot", u.bot},
	    {"system", u.system},
	    {"mfa_enabled", u.mfa_enabled},
	    {"locale", u.locale},
	    {"verified", u.verified},
	    {"email", u.email},
	    {"flags", u.flags},
	    {"premium_type", u.premium_type},
	    {"public_flags", u.public_flags},
	};
}

inline void from_json(const nlohmann::json &j, user &u) {
	j.at("id").get_to(u.id);
	j.at("username").get_to(u.username);
	j.at("discriminator").get_to(u.discriminator);
	get_optional(j, "avatar").get_to(u.avatar);
	get_optional(j, "bot").get_to(u.bot);
	get_optional(j, "system").get_to(u.system);
	get_optional(j, "mfa_enabled").get_to(u.mfa_enabled);
	get_optional(j, "locale").get_to(u.locale);
	get_optional(j, "verified").get_to(u.verified);
	get_optional(j, "email").get_to(u.email);
	get_optional(j, "flags").get_to(u.flags);
	get_optional(j, "premium_type").get_to(u.premium_type);
	get_optional(j, "public_flags").get_to(u.public_flags);
}

inline void to_json(nlohmann::json &j, const unavailable_guild &ug) {
	j = {
	    {"id", ug.id},
	    {"unavailable", ug.unavailable},
	};
}

inline void from_json(const nlohmann::json &j, unavailable_guild &ug) {
	j.at("id").get_to(ug.id);
	get_optional(j, "unavailable").get_to(ug.unavailable);
}

inline void to_json(nlohmann::json &j, const partial_application &pa) {
	j = {
	    {"id", pa.id},
	    {"flags", pa.flags},
	};
}

inline void from_json(const nlohmann::json &j, partial_application &pa) {
	j.at("id").get_to(pa.id);
	j.at("flags").get_to(pa.flags);
}

inline void to_json(nlohmann::json &j, const identify_connection_properties &icp) {
	j = {
	    {"$os", icp.os},
	    {"$browser", icp.browser},
	    {"$device", icp.device},
	};
}

inline void from_json(const nlohmann::json &j, identify_connection_properties &icp) {
	j.at("$os").get_to(icp.os);
	j.at("$browser").get_to(icp.browser);
	j.at("$device").get_to(icp.device);
}

inline void to_json(nlohmann::json &j, const identify &i) {
	j = {
	    {"token", i.token},
	    {"properties", i.properties},
	    {"compress", i.compress},
	    {"large_treshold", i.large_treshold},
	    {"shard", i.shard},
	    {"presence", i.presence},
	    {"guild_subscriptions", i.guild_subscriptions},
	    {"intents", i.intents},
	};
}

inline void from_json(const nlohmann::json &j, identify &i) {
	j.at("token").get_to(i.token);
	j.at("properties").get_to(i.properties);
	get_optional(j, "compress").get_to(i.compress);
	get_optional(j, "large_treshold").get_to(i.large_treshold);
	get_optional(j, "shard").get_to(i.shard);
	get_optional(j, "presence").get_to(i.presence);
	get_optional(j, "guild_subscriptions").get_to(i.guild_subscriptions);
	j.at("intents").get_to(i.intents);
}

inline void to_json(nlohmann::json &j, const resume &r) {
	j = {
	    {"token", r.token},
	    {"session_id", r.session_id},
	    {"seq", r.seq},
	};
}

inline void from_json(const nlohmann::json &j, resume &r) {
	j.at("token").get_to(r.token);
	j.at("session_id").get_to(r.session_id);
	j.at("seq").get_to(r.seq);
}

inline void to_json(nlohmann::json &j, const hello &h) {
	j = {
	    {"heartbeat_interval", h.heartbeat_interval},
	};
}

inline void from_json(const nlohmann::json &j, hello &h) {
	j.at("heartbeat_interval").get_to(h.heartbeat_interval);
}

inline void to_json(nlohmann::json &j, const ready &r) {
	j = {
	    {"v", r.v},
	    {"user", r.user_info},
	    {"private_channels", r.private_channels},
	    {"guilds", r.guilds},
	    {"session_id", r.session_id},
	    {"shard", r.shard},
	    {"application", r.application},
	};
}

inline void from_json(const nlohmann::json &j, ready &r) {
	j.at("v").get_to(r.v);
	j.at("user").get_to(r.user_info);
	j.at("private_channels").get_to(r.private_channels);
	j.at("guilds").get_to(r.guilds);
	j.at("session_id").get_to(r.session_id);
	get_optional(j, "shard").get_to(r.shard);
	j.at("application").get_to(r.application);
}

inline void to_json(nlohmann::json &j, const payload &p) {
	j = {
	    {"op", p.op},
	    {"s", p.s},
	    {"t", p.t},
	};

	switch (p.op) {
	case opcode::dispatch: {
		if (p.t.has_value()) {
			if (p.t.value() == event::ready) {
				j["d"] = std::get<ready>(p.d);
			}
		}
		break;
	}
	case opcode::heartbeat: {
		int seq = std::get<int>(p.d);
		if (seq < 0) {
			j["d"] = seq;
		} else {
			j["d"] = nullptr;
		}
		break;
	}
	case opcode::identify: {
		j["d"] = std::get<identify>(p.d);
		break;
	}
	case opcode::hello: {
		j["d"] = std::get<hello>(p.d);
		break;
	}
	case opcode::resume: {
		j["d"] = std::get<resume>(p.d);
		break;
	}
	}
}

inline void from_json(const nlohmann::json &j, payload &p) {
	j.at("op").get_to(p.op);
	get_optional(j, "s").get_to(p.s);
	get_optional(j, "t").get_to(p.t);

	switch (p.op) {
	case opcode::dispatch: {
		if (p.t.has_value()) {
			if (p.t.value() == event::ready) {
				ready event_data;
				j.at("d").get_to(event_data);
				p.d = event_data;
			}
		}
		break;
	}
	case opcode::heartbeat: {
		int seq = -1;
		if (!get_optional(j, "d").is_null()) {
			j.at("d").get_to(seq);
		}
		p.d = seq;
		break;
	}
	case opcode::identify: {
		identify event_data;
		j.at("d").get_to(event_data);
		p.d = event_data;
		break;
	}
	case opcode::hello: {
		hello event_data;
		j.at("d").get_to(event_data);
		p.d = event_data;
		break;
	}
	case opcode::resume: {
		resume event_data;
		j.at("d").get_to(event_data);
		p.d = event_data;
		break;
	}
	}
}

} // namespace discord_bot

} // namespace eelbot_framework

#endif
