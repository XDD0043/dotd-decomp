// Stub.h - markers for code that is not ported yet, and the boot trace.
//
// STUB(Cx.y) comments mark functions that only stand in for the original until checkpoint Cx.y ports
// them; work/count_stubs.py lists them. DOTD_STUB_ONCE logs the first call of a stub.
//
// The boot trace records the order in which the boot creates and initialises subsystems, so a test
// can compare it with the order measured in the original (outputs/remake/research/boot-and-platform.md
// section 1.5). It is diagnostics only: nothing in the game reads it.
#pragma once
#include <string>
#include <vector>

#include "platform/log.h"

#define DOTD_STUB_ONCE(name)                                                   \
    do {                                                                       \
        static bool s_stubLogged = false;                                      \
        if (!s_stubLogged) {                                                   \
            s_stubLogged = true;                                               \
            DOTD_LOG("stub: %s (not ported yet)", name);                       \
        }                                                                      \
    } while (0)

namespace dotd::trace {

// Logs "boot: <event>" and appends it to the boot trace.
void Boot(const char* event);
const std::vector<std::string>& BootTrace();
// Records "mode A -> B" in the boot trace (GameLoop's mode state machine).
void ModeChange(int oldMode, int newMode);
void ClearBootTrace();

}  // namespace dotd::trace
