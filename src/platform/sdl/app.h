// app.h - SDL3 host: window, OpenGL context, event pump, gamepads.
// Only the platform layer includes this; game code talks to the PS3-named shims in platform/cell/.
#pragma once
#include <cstdint>

namespace dotd::platform {
struct Config;
}

namespace dotd::platform::sdl {

// Creates the window and an OpenGL 3.3 core context, and picks how frames are paced to
// cfg.frameRate: vsync when the display refresh is a whole multiple of it, a timer otherwise.
bool Init(const Config& cfg);
void Shutdown();

// Main thread only. Drains SDL events: quit becomes CELL_SYSUTIL_REQUEST_EXITGAME on the sysutil
// queue, gamepads are opened/closed as they come and go, pacing is re-chosen when the window moves
// to another display or the display mode changes.
void PumpEvents();

// Presents and holds the frame rate: returns at the start of the next frame slot. Then pumps events,
// so the frame's system callbacks see a window close at once.
void SwapWindow();
// Frame timing measured at SwapWindow, after a 60-frame warm-up; LogFrameStats prints it.
void LogFrameStats();
// The frame rate while the game runs (platform SetFps): the pacing is chosen again.
void SetFrameRate(int frameRate);
void GetDrawableSize(int* width, int* height);
// The window's size while the game runs (the web page: the canvas's pixels, which the page then scales).
void SetWindowSize(int width, int height);
void SetWindowTitle(const char* title);
void* GetGLProcAddress(const char* name);

// PS3 pad words for a port, laid out like CellPadData.button[2..23]:
//   words[2] digital1, [3] digital2, [4..7] analog RX, RY, LX, LY, [8..19] pressure, [20..23] sensors.
// Port 0 combines the first gamepad and the keyboard. Returns false when nothing is on that port.
bool ReadPad(int port, uint16_t words[24]);
// A pad drawn on a touch screen (the web page's controls): the digital words and the stick bytes (centre 128),
// merged into port 0 like the keyboard. Any thread.
void SetTouchPad(uint16_t digital1, uint16_t digital2, uint8_t leftX, uint8_t leftY, uint8_t rightX, uint8_t rightY);
int ConnectedPadCount();
void Rumble(int port, uint8_t smallMotor, uint8_t largeMotor);

}  // namespace dotd::platform::sdl
