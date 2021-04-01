// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#ifndef EELBOT_FRAMEWORK_DISCORD_BOT_OPCODES_H
#define EELBOT_FRAMEWORK_DISCORD_BOT_OPCODES_H

#include <string>

namespace eelbot_framework {

namespace discord_bot {

namespace opcode {

static constexpr int heartbeat     = 1;
static constexpr int identify      = 2;
static constexpr int hello         = 10;
static constexpr int heartbeat_ack = 11;

} // namespace opcode

} // namespace discord_bot

} // namespace eelbot_framework

#endif
