// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#ifndef EELBOT_FRAMEWORK_DISCORD_BOT_CODES_H
#define EELBOT_FRAMEWORK_DISCORD_BOT_CODES_H

#include <string>

namespace eelbot_framework {

namespace discord_bot {

namespace opcode {

static constexpr int dispatch        = 0;
static constexpr int heartbeat       = 1;
static constexpr int identify        = 2;
static constexpr int resume          = 6;
static constexpr int reconnect       = 7;
static constexpr int invalid_session = 9;
static constexpr int hello           = 10;
static constexpr int heartbeat_ack   = 11;

} // namespace opcode

namespace event {

static const std::string ready = "READY";

}

namespace close_event_code {

static constexpr unsigned short abnormal_closure = 1006;

static constexpr unsigned short unknown_error         = 4000;
static constexpr unsigned short unknown_opcode        = 4001;
static constexpr unsigned short decode_error          = 4002;
static constexpr unsigned short not_authenticated     = 4003;
static constexpr unsigned short authentication_failed = 4004;
static constexpr unsigned short already_authenticated = 4005;
static constexpr unsigned short invalid_seq           = 4007;
static constexpr unsigned short rate_limited          = 4008;
static constexpr unsigned short session_timed_out     = 4009;
static constexpr unsigned short invalid_shard         = 4010;
static constexpr unsigned short sharding_required     = 4011;
static constexpr unsigned short invalid_api_version   = 4012;
static constexpr unsigned short invalid_intents       = 4013;
static constexpr unsigned short disallowed_intents    = 4014;

static constexpr unsigned short internal_retry_and_identify = 4100;
static constexpr unsigned short internal_retry_and_resume   = 4101;

} // namespace close_event_code

} // namespace discord_bot

} // namespace eelbot_framework

#endif
