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

// The frames presented per second, measured over the last half second (what the window title shows); 0 before
// the first measurement and without a window.
float PresentedFps();

}  // namespace dotd::platform
