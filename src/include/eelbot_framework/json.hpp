// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#ifndef EELBOT_FRAMEWORK_JSON_H
#define EELBOT_FRAMEWORK_JSON_H

#include <string>

namespace eelbot_framework {

/**
 * @brief Serializes a JSONifiable object to a JSON string.
 *
 * @param object The object to serialize.
 * @param indent The indentation to use for the JSON string. A negative value results in a single line string with no
 *        indentation.
 * @param indent_char The character to use for indentation.
 * @return The serialized JSON string.
 */
template <typename T>
std::string to_json_string(const T &object, const int indent = -1, const char indent_char = ' ');

/**
 * @brief Deserializes a JSON string to a JSONifiable object.
 *
 * @param json_string The string to deserialize.
 * @return The deserialized object.
 */
template <typename T>
T parse_from_json_string(const std::string &json_string);

} // namespace eelbot_framework

#endif
