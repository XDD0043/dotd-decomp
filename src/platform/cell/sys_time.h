// sys_time.h - the PS3 system-time call the game uses (sys_time_get_system_time, microseconds).
// Game code calls it exactly where the original did (CKTime). The platform decides the source:
// the host's monotonic clock by default ("Free" timing), or a scripted source for the Console timing
// mode, replays and tests (SetSystemTimeSource).
#pragma once
#include <cstdint>

int64_t sys_time_get_system_time();

namespace dotd::platform {
using SystemTimeSource = int64_t (*)();
// nullptr restores the host monotonic clock.
void SetSystemTimeSource(SystemTimeSource source);

// Replays (debug, off by default; step 1): when a source is set and answers true, CKTime::KGetExactTime returns its
// value (seconds) instead of the system-time difference: the original's frame clock as recorded in RPCS3.
using ExactTimeSource = bool (*)(double* seconds);
void SetExactTimeSource(ExactTimeSource source);  // nullptr = off
bool ReadExactTimeOverride(double* seconds);
}  // namespace dotd::platform
