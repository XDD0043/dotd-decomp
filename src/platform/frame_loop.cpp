#include "platform/frame_loop.h"

#include "platform/config.h"
#include "platform/fps.h"
#include "platform/log.h"
#include "platform/sdl/app.h"
#ifdef __EMSCRIPTEN__
#include <emscripten.h>

#include "platform/gfx/device.h"
#include "platform/gfx/gpuprof.h"
#include "platform/gfx/perf.h"
#include "platform/web/web.h"
#endif

namespace dotd::platform {

namespace {
void SetPacing(int fps);  // the platform's part of SetFps
}

void SetFps(int fps) {
    if (fps < 0) fps = 60;
    Config& config = MutableConfig();
    if (config.fps == fps && config.frameRate == fps) return;
    config.fps = fps;
    config.frameRate = fps;
    fps::SetUnlocked(fps != 60);
    SetPacing(fps);
    DOTD_LOG("fps: %d%s", fps, fps == 60 ? " (the original's pacing)" : fps == 0 ? " (no cap)" : "");
}

#ifndef __EMSCRIPTEN__

namespace {
void SetPacing(int fps) { sdl::SetFrameRate(fps); }
}  // namespace

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
    web::NoteMainThreadTask();  // (the main thread was back in the browser: its next wait is a new one)
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

void SetPacing(int fps) {
    g_period = fps > 0 ? 1000.0 / fps : 0.0;
    g_nextSlot = 0.0;
}
}  // namespace

// ---- what the page calls (web/index.html; the game runs on the page's thread) ------------------------------
extern "C" {
// The "60 fps cap" check box: 0 = every animation frame (the page's default), 60 = the original's pacing.
EMSCRIPTEN_KEEPALIVE void dotd_web_set_fps(int fps) { SetFps(fps); }
EMSCRIPTEN_KEEPALIVE int dotd_web_get_fps() { return GetConfig().fps; }
// The page's GPU test (?diag, index.html): the render stages switched off (bit n = stage n), one measured frame every
// `measureEvery` frames (0: none; platform/gfx/gpuprof.h), the resolution scale in percent (device.h).
EMSCRIPTEN_KEEPALIVE void dotd_web_gpu_test(int skipMask, int measureEvery, int scalePercent) {
    gfx::gpuprof::SetSkipMask(static_cast<uint32_t>(skipMask));
    gfx::gpuprof::SetMeasureEvery(measureEvery);
    gfx::SetResolutionScale(static_cast<float>(scalePercent) / 100.0f);
}
// The GPU test's second round: the items [from, to) of `stage` not drawn; after each stage a flush (1) or a finish (2);
// the items of `describe` listed in the measured frames' reports (-1: none).
EMSCRIPTEN_KEEPALIVE void dotd_web_gpu_test2(int stage, int from, int to, int sync, int describe) {
    gfx::gpuprof::SetSkipItems(stage, static_cast<uint32_t>(from), static_cast<uint32_t>(to));
    gfx::gpuprof::SetStageSync(sync);
    gfx::gpuprof::SetDescribedStage(describe);
}
// The fix test: the opaque queues near to far (bit 0) and / or with a depth pre-pass (bit 1) (gpuprof.h OpaqueMode).
EMSCRIPTEN_KEEPALIVE void dotd_web_gpu_opaque(int mode) { gfx::gpuprof::SetOpaqueMode(mode); }
// A render stage's item count at its last execution (the GPU test only switches off stages that draw something).
EMSCRIPTEN_KEEPALIVE int dotd_web_stage_items(int stage) { return static_cast<int>(gfx::gpuprof::StageItems(stage)); }
// The touch controls: a pad drawn on the screen, as CellPadData's digital words (button[2], button[3]) and stick
// bytes (0..255, centre 128, up = 0). It is merged into port 0 like the keyboard (sdl::SetTouchPad).
EMSCRIPTEN_KEEPALIVE void dotd_web_touch(int digital1, int digital2, int leftX, int leftY, int rightX, int rightY) {
    sdl::SetTouchPad(static_cast<uint16_t>(digital1), static_cast<uint16_t>(digital2), static_cast<uint8_t>(leftX),
                     static_cast<uint8_t>(leftY), static_cast<uint8_t>(rightX), static_cast<uint8_t>(rightY));
}
}

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
