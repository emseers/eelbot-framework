// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#ifndef EELBOT_FRAMEWORK_DISCORD_BOT_ENDPOINTS_H
#define EELBOT_FRAMEWORK_DISCORD_BOT_ENDPOINTS_H

#include <string>

namespace eelbot_framework {

namespace discord_bot {

static const std::string gateway_version = "8";

namespace endpoints {

static const std::string discord     = "https://discord.com/";
static const std::string api         = discord + "api/v" + gateway_version + "/";
static const std::string gateway     = api + "gateway";
static const std::string gateway_bot = gateway + "/bot";

} // namespace endpoints

} // namespace discord_bot

} // namespace eelbot_framework

#endif
