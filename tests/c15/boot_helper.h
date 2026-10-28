// boot_helper.h - checkpoint C1.5 tests: boot the native build to the loaded front end (GAME, 00GLC,
// LVL000, 00LLC000 loaded, mode 5), then step frames at exactly 1/60 s. Headless; no window.
#pragma once
#include <cstdint>
#include <cstdio>

namespace c15 {

extern int g_failures;

// Boots (the boot_test sequence) and runs frames until mode 5. False when no game data is configured
// (the test then exits 77, skipped).
bool BootToFrontEnd();
// The C1.5 harnesses that drive the Flash movies and the videos themselves: the game manager's game state
// machine (the front-end sequence of C1.4: auto-load, copyrights, logos, press start, main menu) is parked
// on no state (0xff), so it opens no menu and plays no video of its own.
void ParkFrontEndSequence();
// One game frame (Run()) after advancing the fake system clock by 1/60 s.
void RunFrame();
// Frames run since BootToFrontEnd started stepping in mode 5.
uint32_t FrameCount();
// The game's Cleanup().
void Shutdown();

}  // namespace c15

#define C15_CHECK(cond)                                                      \
    do {                                                                     \
        if (!(cond)) {                                                       \
            std::printf("FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond);     \
            ++c15::g_failures;                                               \
        }                                                                    \
    } while (0)
