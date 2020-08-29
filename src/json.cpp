// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#include "eelbot_framework/json.hpp"

#include "eelbot_framework/discord_bot/structs.hpp"
#include "nlohmann/json.hpp"

#include <optional>

namespace nlohmann {

// JSON specialization for std::optional.

template <typename T>
struct adl_serializer<std::optional<T>> {
	static void to_json(json &j, const std::optional<T> &opt) {
		if (opt.has_value()) {
			j = opt.value();
		} else {
			j = nullptr;
		}
	}

	static void from_json(const json &j, std::optional<T> &opt) {
		if (j.is_null()) {
			opt = std::nullopt;
		} else {
			opt = j.get<T>();
		}
	}
};

} // namespace nlohmann

namespace eelbot_framework {

// JSON specialization for Eelbot Framework objects.

namespace discord_bot {

void to_json(nlohmann::json &j, const session_start_limit &ssl) {
	j = nlohmann::json{{"total", ssl.total}, {"remaining", ssl.remaining}, {"reset_after", ssl.reset_after}};
}

void from_json(const nlohmann::json &j, session_start_limit &ssl) {
	j.at("total").get_to(ssl.total);
	j.at("remaining").get_to(ssl.remaining);
	j.at("reset_after").get_to(ssl.reset_after);
}

void to_json(nlohmann::json &j, const gateway_response &gr) {
	j = nlohmann::json{{"url", gr.url}};
}

void from_json(const nlohmann::json &j, gateway_response &gr) {
	j.at("url").get_to(gr.url);
}

void to_json(nlohmann::json &j, const gateway_bot_response &gbr) {
	j = nlohmann::json{{"url", gbr.url}, {"shards", gbr.shards}, {"session_start_limit", gbr.sess_start_limit}};
}

void from_json(const nlohmann::json &j, gateway_bot_response &gbr) {
	j.at("url").get_to(gbr.url);
	j.at("shards").get_to(gbr.shards);
	j.at("session_start_limit").get_to(gbr.sess_start_limit);
}

void to_json(nlohmann::json &j, const payload &p) {
	j = nlohmann::json{{"op", p.op}, {"d", p.d}, {"s", p.s}, {"t", p.t}};
}

void from_json(const nlohmann::json &j, payload &p) {
	j.at("op").get_to(p.op);
	j.at("d").get_to(p.d);

	if (j.find("s") != j.end()) {
		j.at("s").get_to(p.s);
	}

	if (j.find("t") != j.end()) {
		j.at("t").get_to(p.t);
	}
}

} // namespace discord_bot

template <typename T>
std::string to_json_string(const T &object, const int indent, const char indent_char) {
	nlohmann::json json = object;
	return json.dump(indent, indent_char);
}

template <typename T>
T parse_from_json_string(const std::string &json_string) {
	nlohmann::json json = nlohmann::json::parse(json_string);
	return json.get<T>();
}

// Serialization definitions (to_json needs to be defined for each type).

template std::string to_json_string<discord_bot::session_start_limit>(
    const discord_bot::session_start_limit &t, const int indent, const char indent_char);
template std::string to_json_string<discord_bot::gateway_response>(
    const discord_bot::gateway_response &t, const int indent, const char indent_char);
template std::string to_json_string<discord_bot::gateway_bot_response>(
    const discord_bot::gateway_bot_response &t, const int indent, const char indent_char);
template std::string to_json_string<discord_bot::payload>(
    const discord_bot::payload &t, const int indent, const char indent_char);

// Deserialization definitions (from_json needs to be defined for each type).

template discord_bot::session_start_limit parse_from_json_string<discord_bot::session_start_limit>(
    const std::string &json_string);
template discord_bot::gateway_response parse_from_json_string<discord_bot::gateway_response>(
    const std::string &json_string);
template discord_bot::gateway_bot_response parse_from_json_string<discord_bot::gateway_bot_response>(
    const std::string &json_string);
template discord_bot::payload parse_from_json_string<discord_bot::payload>(const std::string &json_string);

} // namespace eelbot_framework
