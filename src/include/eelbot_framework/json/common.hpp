// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#ifndef EELBOT_FRAMEWORK_JSON_COMMON_H
#define EELBOT_FRAMEWORK_JSON_COMMON_H

#include "nlohmann/json.hpp"

#include <optional>
#include <string>

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

#endif
