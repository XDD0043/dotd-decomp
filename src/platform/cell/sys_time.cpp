#include "platform/cell/sys_time.h"

#include <chrono>

namespace {
dotd::platform::SystemTimeSource g_source = nullptr;

int64_t HostMicroseconds() {
    using namespace std::chrono;
    static const steady_clock::time_point s_boot = steady_clock::now();
    return duration_cast<microseconds>(steady_clock::now() - s_boot).count();
}
}  // namespace

int64_t sys_time_get_system_time() { return g_source ? g_source() : HostMicroseconds(); }

namespace dotd::platform {
void SetSystemTimeSource(SystemTimeSource source) { g_source = source; }

namespace {
ExactTimeSource g_exactSource = nullptr;
}  // namespace
void SetExactTimeSource(ExactTimeSource source) { g_exactSource = source; }
bool ReadExactTimeOverride(double* seconds) { return g_exactSource != nullptr && g_exactSource(seconds); }
}  // namespace dotd::platform
