#include "platform/frame_loop.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>

#include "platform/config.h"
#include "platform/gfx/perf.h"
#include "platform/log.h"
#include "platform/web/web.h"
#endif

namespace dotd::platform {

#ifndef __EMSCRIPTEN__

void RunFrames(bool (*frame)(), void (*done)()) {
    while (frame()) {
    }
    done();
}

#else

namespace {
bool (*g_frame)() = nullptr;
void (*g_done)() = nullptr;
double g_period = 0.0;    // ms per game frame; 0 = every animation frame
double g_nextSlot = 0.0;  // ms (emscripten_get_now): the next game frame is due at this time

// One browser animation frame. The display's refresh need not be the game's frame rate (60): a game frame runs
// on the first animation frame at or after its slot on a fixed grid, so the average rate is exact whatever the
// refresh (165 Hz: every second or third animation frame; 60 Hz: every one). The tolerance keeps a display a
// little faster than the grid from skipping a frame every few seconds for no reason; a slot missed by more
// than a frame (a long frame, a hidden tab) restarts the grid instead of running frames back to back.
void Tick() {
    if (g_period > 0.0) {
        const double now = emscripten_get_now();
        if (g_nextSlot == 0.0) g_nextSlot = now;
        if (now < g_nextSlot - 1.0) return;
        g_nextSlot += g_period;
        if (now > g_nextSlot) g_nextSlot = now + g_period;
    }
    const double start = gfx::perf::g_enabled ? emscripten_get_now() : 0.0;
    const bool more = g_frame();
    if (gfx::perf::g_enabled) {
        // With DOTD_GFX_STATS: the game's own time in a long frame (the rest of a hitch is the browser's).
        const double took = emscripten_get_now() - start;
        double readMs = 0.0, readMb = 0.0;
        int reads = 0;
        web::TakeMainThreadReadWait(&readMs, &reads, &readMb);
        if (took > 12.0) {
            DOTD_LOG("web: the game frame took %.1f ms, of which %.1f ms waiting for %d file read(s), %.2f MB", took,
                     readMs, reads, readMb);
        }
    }
    if (!more) {
        emscripten_cancel_main_loop();
        g_done();
        DOTD_LOG("web: the game's main loop ended");
    }
}
}  // namespace

void RunFrames(bool (*frame)(), void (*done)()) {
    g_frame = frame;
    g_done = done;
    const int rate = GetConfig().frameRate;
    g_period = rate > 0 ? 1000.0 / rate : 0.0;
    DOTD_LOG("web: frames by requestAnimationFrame, %d fps%s", rate, rate > 0 ? "" : " (every animation frame)");
    // fps 0 = requestAnimationFrame; simulate_infinite_loop: this call does not return.
    emscripten_set_main_loop(&Tick, 0, true);
}

#endif

}  // namespace dotd::platform
