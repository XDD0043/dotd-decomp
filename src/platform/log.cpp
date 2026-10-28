#include "platform/log.h"

#include <chrono>
#include <cstdarg>
#include <cstdio>
#include <mutex>

namespace dotd {

void Log(const char* fmt, ...) {
    static const std::chrono::steady_clock::time_point s_start = std::chrono::steady_clock::now();
    static std::mutex s_mutex;
    const long long ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - s_start).count();
    std::lock_guard<std::mutex> lock(s_mutex);
    std::fprintf(stderr, "[%7lld] ", ms);
    va_list args;
    va_start(args, fmt);
    std::vfprintf(stderr, fmt, args);
    va_end(args);
    std::fputc('\n', stderr);
    std::fflush(stderr);
}

}  // namespace dotd
