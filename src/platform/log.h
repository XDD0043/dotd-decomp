// log.h - minimal logging for the platform layer and tools (stderr, with milliseconds since start).
#pragma once

namespace dotd {
void Log(const char* fmt, ...);
}

#define DOTD_LOG(...) ::dotd::Log(__VA_ARGS__)
