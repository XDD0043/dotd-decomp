// Stub.cpp - the boot trace (see Stub.h).
#include "k2000/core/Stub.h"

#include <cstdio>
#include <mutex>

namespace dotd::trace {

namespace {
std::mutex g_mutex;
std::vector<std::string> g_bootTrace;
}  // namespace

void Boot(const char* event) {
    DOTD_LOG("boot: %s", event);
    std::lock_guard<std::mutex> lock(g_mutex);
    g_bootTrace.emplace_back(event);
}

const std::vector<std::string>& BootTrace() { return g_bootTrace; }

void ModeChange(int oldMode, int newMode) {
    char event[32];
    std::snprintf(event, sizeof(event), "mode %d -> %d", oldMode, newMode);
    Boot(event);
}

void ClearBootTrace() {
    std::lock_guard<std::mutex> lock(g_mutex);
    g_bootTrace.clear();
}

}  // namespace dotd::trace
