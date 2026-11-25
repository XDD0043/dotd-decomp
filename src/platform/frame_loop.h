// frame_loop.h - the game's main loop, run by the platform.
// The original's main (0x253870) is "for (;;) if (!Run()) break;": one Run() is one frame. A native build runs
// exactly that loop. A browser must get control back after every frame, so the web build calls frame() once per
// animation frame instead, paced to Config::frameRate.
#pragma once

namespace dotd::platform {

// Calls frame() until it returns false, then done().
// Native: returns after done(). Web: does not return (the caller's stack is dropped; done() runs after the last
// frame, from the browser's frame callback).
void RunFrames(bool (*frame)(), void (*done)());

// The frames presented per second, measured over the last half second (what the native window's title shows); 0
// before the first measurement and without a window.
float PresentedFps();

// --fps N while the game runs: N frames per second (0 = no cap: the display's refresh in a browser), with the
// 60 Hz timing calculation (platform/fps.h) for any N but 60; 60 = the original's pacing. Main thread.
// Native: F2 switches between 60 and no cap. Web: the page's "60 fps cap" check box (dotd_web_set_fps).
void SetFps(int fps);

}  // namespace dotd::platform
