#include "platform/sdl/app.h"

#include <SDL3/SDL.h>

#include <cstdio>
#include <cstring>
#include <mutex>
#include <string>
#include <vector>

#include "platform/cell/sysutil.h"
#include "platform/config.h"
#include "platform/log.h"
#include "platform/sdl/freecam.h"

namespace dotd::platform::sdl {

namespace {
SDL_Window* g_window = nullptr;
SDL_GLContext g_context = nullptr;
std::string g_baseTitle = "The Legend of Spyro: Dawn of the Dragon (dotd)";
std::mutex g_padMutex;
std::vector<SDL_Gamepad*> g_gamepads;  // in connection order; index = PS3 port

// PS3 bit layout (CellPadData digital words)
enum : uint16_t {
    kSelect = 0x0001, kL3 = 0x0002, kR3 = 0x0004, kStart = 0x0008,
    kUp = 0x0010, kRight = 0x0020, kDown = 0x0040, kLeft = 0x0080,
    kL2 = 0x0001, kR2 = 0x0002, kL1 = 0x0004, kR1 = 0x0008,
    kTriangle = 0x0010, kCircle = 0x0020, kCross = 0x0040, kSquare = 0x0080,
};

uint16_t AxisToByte(int16_t v) { return static_cast<uint16_t>((static_cast<int>(v) + 32768) >> 8); }
uint16_t TriggerToByte(int16_t v) { return static_cast<uint16_t>(v <= 0 ? 0 : (static_cast<int>(v) * 255) / 32767); }

void OpenGamepad(SDL_JoystickID id) {
    SDL_Gamepad* gp = SDL_OpenGamepad(id);
    if (!gp) return;
    std::lock_guard<std::mutex> lock(g_padMutex);
    g_gamepads.push_back(gp);
    DOTD_LOG("pad: connected '%s' as port %d", SDL_GetGamepadName(gp), static_cast<int>(g_gamepads.size() - 1));
}

void CloseGamepad(SDL_JoystickID id) {
    std::lock_guard<std::mutex> lock(g_padMutex);
    for (size_t i = 0; i < g_gamepads.size(); ++i) {
        if (SDL_GetGamepadID(g_gamepads[i]) == id) {
            DOTD_LOG("pad: port %d disconnected", static_cast<int>(i));
            SDL_CloseGamepad(g_gamepads[i]);
            g_gamepads.erase(g_gamepads.begin() + static_cast<long>(i));
            return;
        }
    }
}

void ReadGamepad(SDL_Gamepad* gp, uint16_t w[24]) {
    struct Map { SDL_GamepadButton b; int word; uint16_t bit; int pressure; };
    static const Map kMap[] = {
        {SDL_GAMEPAD_BUTTON_BACK, 2, kSelect, -1},       {SDL_GAMEPAD_BUTTON_LEFT_STICK, 2, kL3, -1},
        {SDL_GAMEPAD_BUTTON_RIGHT_STICK, 2, kR3, -1},    {SDL_GAMEPAD_BUTTON_START, 2, kStart, -1},
        {SDL_GAMEPAD_BUTTON_DPAD_UP, 2, kUp, 10},        {SDL_GAMEPAD_BUTTON_DPAD_RIGHT, 2, kRight, 8},
        {SDL_GAMEPAD_BUTTON_DPAD_DOWN, 2, kDown, 11},    {SDL_GAMEPAD_BUTTON_DPAD_LEFT, 2, kLeft, 9},
        {SDL_GAMEPAD_BUTTON_LEFT_SHOULDER, 3, kL1, 16},  {SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER, 3, kR1, 17},
        {SDL_GAMEPAD_BUTTON_NORTH, 3, kTriangle, 12},    {SDL_GAMEPAD_BUTTON_EAST, 3, kCircle, 13},
        {SDL_GAMEPAD_BUTTON_SOUTH, 3, kCross, 14},       {SDL_GAMEPAD_BUTTON_WEST, 3, kSquare, 15},
    };
    for (const Map& m : kMap) {
        if (SDL_GetGamepadButton(gp, m.b)) {
            w[m.word] |= m.bit;
            if (m.pressure >= 0) w[m.pressure] = 255;
        }
    }
    const uint16_t l2 = TriggerToByte(SDL_GetGamepadAxis(gp, SDL_GAMEPAD_AXIS_LEFT_TRIGGER));
    const uint16_t r2 = TriggerToByte(SDL_GetGamepadAxis(gp, SDL_GAMEPAD_AXIS_RIGHT_TRIGGER));
    if (l2 > 64) w[3] |= kL2;
    if (r2 > 64) w[3] |= kR2;
    w[18] = l2;
    w[19] = r2;
    w[4] = AxisToByte(SDL_GetGamepadAxis(gp, SDL_GAMEPAD_AXIS_RIGHTX));
    w[5] = AxisToByte(SDL_GetGamepadAxis(gp, SDL_GAMEPAD_AXIS_RIGHTY));
    w[6] = AxisToByte(SDL_GetGamepadAxis(gp, SDL_GAMEPAD_AXIS_LEFTX));
    w[7] = AxisToByte(SDL_GetGamepadAxis(gp, SDL_GAMEPAD_AXIS_LEFTY));
}

// Keyboard on port 0 (merged into port 0's words; a pressed key overrides the gamepad's value):
//   left stick (move)    W / A / S / D            right stick (camera)  T / F / G / H, or numpad 8 / 4 / 5 / 6
//   d-pad (elements)     arrows                   L3 / R3               Tab / R (numpad 0 = R3 too)
//   cross (jump)         Space, K, X              circle                Escape, L, C
//   square               J, Z                     triangle              I, V
//   L1 / R1              Q / E                    L2 / R2               1 / 3 (pressure 255)
//   start / select       Enter / Backspace
// Sticks are full deflection (0 / 255, centre 128; up = 0 as the DS3's CellPadData). The front end reads cross as
// validate and circle as back (the "Flash Manager" input project, entries 4 and 5). With the debug free camera on
// (F1) WASD fly it and do not move the left stick.
// An SDL gamepad on port n is read as a DualShock 3 (ReadGamepad): positional face buttons (south = cross, east =
// circle, west = square, north = triangle), shoulders L1 / R1, triggers L2 / R2 (analog 0..255 into the pressure
// words 18 / 19, digital above 64), stick clicks L3 / R3, back = select, start, the d-pad, both sticks (0..255, centre
// 128, up = 0), the pressure words 8..17 at 255 while pressed; rumble: Rumble() below.
void ReadKeyboard(uint16_t w[24]) {
    int count = 0;
    const bool* k = SDL_GetKeyboardState(&count);
    if (!k) return;
    struct Map { SDL_Scancode s; int word; uint16_t bit; int pressure; };
    static const Map kMap[] = {
        {SDL_SCANCODE_UP, 2, kUp, 10},          {SDL_SCANCODE_RIGHT, 2, kRight, 8},
        {SDL_SCANCODE_DOWN, 2, kDown, 11},      {SDL_SCANCODE_LEFT, 2, kLeft, 9},
        {SDL_SCANCODE_RETURN, 2, kStart, -1},   {SDL_SCANCODE_BACKSPACE, 2, kSelect, -1},
        {SDL_SCANCODE_SPACE, 3, kCross, 14},    {SDL_SCANCODE_K, 3, kCross, 14},
        {SDL_SCANCODE_ESCAPE, 3, kCircle, 13},
        // RPCS3's default keyboard pad: Z square, X cross, C circle, V triangle.
        {SDL_SCANCODE_X, 3, kCross, 14},        {SDL_SCANCODE_C, 3, kCircle, 13},
        {SDL_SCANCODE_Z, 3, kSquare, 15},       {SDL_SCANCODE_V, 3, kTriangle, 12},
        {SDL_SCANCODE_L, 3, kCircle, 13},       {SDL_SCANCODE_J, 3, kSquare, 15},
        {SDL_SCANCODE_I, 3, kTriangle, 12},     {SDL_SCANCODE_Q, 3, kL1, 16},
        {SDL_SCANCODE_E, 3, kR1, 17},           {SDL_SCANCODE_1, 3, kL2, 18},
        {SDL_SCANCODE_3, 3, kR2, 19},           {SDL_SCANCODE_TAB, 2, kL3, -1},
        {SDL_SCANCODE_R, 2, kR3, -1},           {SDL_SCANCODE_KP_0, 2, kR3, -1},
    };
    for (const Map& m : kMap) {
        if (m.s < count && k[m.s]) {
            w[m.word] |= m.bit;
            if (m.pressure >= 0) w[m.pressure] = 255;
        }
    }
    // The right stick (words 4 / 5: x, y).
    if (k[SDL_SCANCODE_F] || k[SDL_SCANCODE_KP_4]) w[4] = 0;
    if (k[SDL_SCANCODE_H] || k[SDL_SCANCODE_KP_6]) w[4] = 255;
    if (k[SDL_SCANCODE_T] || k[SDL_SCANCODE_KP_8]) w[5] = 0;
    if (k[SDL_SCANCODE_G] || k[SDL_SCANCODE_KP_5] || k[SDL_SCANCODE_KP_2]) w[5] = 255;
    if (freecam::Enabled()) return;  // WASD fly the debug camera instead
    if (k[SDL_SCANCODE_A]) w[6] = 0;
    if (k[SDL_SCANCODE_D]) w[6] = 255;
    if (k[SDL_SCANCODE_W]) w[7] = 0;
    if (k[SDL_SCANCODE_S]) w[7] = 255;
}

// ---- frame pacing --------------------------------------------------------------------------------
// The game must see exactly frameRate frames per second: gameplay uses the measured dt, but the
// menu animations advance one step per frame (docs/DECOMP_IMPL-1.md, "Frame rate").
//   kVsync:    the display refresh is a whole multiple of frameRate; swap interval does the pacing.
//              Checked over the first frames, because drivers can force vsync off.
//   kTimer:    present, then wait for the next frame slot, so the next frame starts on a fixed grid
//              and the game's clock sees a steady dt (the presentation time may vary by the render
//              time; the game's dt matters more). A late frame waits for the slot after it, the way a
//              vsynced flip does, so the game sees the same 2-frame dt a missed vblank gives.
//              Swap interval 0: with vsync on a 165 Hz display the swap blocked for varying times and
//              frame starts spread to 8.8..24.5 ms (16.66..16.67 ms with it off). Tearing is possible;
//              a 60/120 Hz display mode or a variable-refresh display avoids it.
//   kUncapped: frameRate 0, for experiments.
enum PaceMode { kUncapped, kVsync, kTimer };
PaceMode g_paceMode = kUncapped;
int g_frameRate = 60;
bool g_vsyncWanted = true;
Uint64 g_period = 0;       // ns per frame
Uint64 g_nextSlot = 0;     // kTimer: next presentation time, ns
Uint64 g_checkStart = 0;   // kVsync: start of the check window
int g_checkFrames = -1;    // kVsync: frames counted in the check window; -1 = check done

constexpr int kVsyncCheckSkip = 10;     // frames ignored after a mode change
constexpr int kVsyncCheckFrames = 120;  // frames measured

float DisplayRefreshRate() {
    const SDL_DisplayID display = SDL_GetDisplayForWindow(g_window);
    const SDL_DisplayMode* mode = display ? SDL_GetCurrentDisplayMode(display) : nullptr;
    if (!mode) return 0.0f;
    if (mode->refresh_rate_numerator > 0 && mode->refresh_rate_denominator > 0) {
        return static_cast<float>(static_cast<double>(mode->refresh_rate_numerator) / mode->refresh_rate_denominator);
    }
    return mode->refresh_rate;
}

void SetTimerPacing(const char* why) {
    SDL_GL_SetSwapInterval(0);
    g_paceMode = kTimer;
    g_nextSlot = 0;
    g_checkFrames = -1;
    DOTD_LOG("sdl: pacing %d fps by timer (%s)", g_frameRate, why);
}

void ChoosePacing() {
    g_period = g_frameRate > 0 ? 1000000000ull / static_cast<Uint64>(g_frameRate) : 0;
    if (g_frameRate <= 0) {
        SDL_GL_SetSwapInterval(g_vsyncWanted ? 1 : 0);
        g_paceMode = kUncapped;
        DOTD_LOG("sdl: pacing off (frame_rate 0), vsync %d", g_vsyncWanted ? 1 : 0);
        return;
    }
    if (!g_vsyncWanted) {
        SetTimerPacing("vsync off");
        return;
    }
    const float refresh = DisplayRefreshRate();
    const int multiple = static_cast<int>(refresh / static_cast<float>(g_frameRate) + 0.5f);
    const float perFrame = multiple > 0 ? refresh / static_cast<float>(multiple) : 0.0f;
    if (multiple >= 1 && perFrame > g_frameRate - 0.6f && perFrame < g_frameRate + 0.6f &&
        SDL_GL_SetSwapInterval(multiple)) {
        g_paceMode = kVsync;
        g_checkFrames = 0;
        DOTD_LOG("sdl: pacing by vsync, display %.3f Hz, swap interval %d", refresh, multiple);
        return;
    }
    char why[64];
    SDL_snprintf(why, sizeof(why), "display %.3f Hz", refresh);
    SetTimerPacing(why);
}

// kTimer: called after the swap. Sleeps until the next slot on the frame grid.
void WaitForSlot() {
    const Uint64 now = SDL_GetTicksNS();
    if (g_nextSlot == 0) {
        g_nextSlot = now;  // first frame: start the grid here
        return;
    }
    g_nextSlot += g_period;
    if (g_nextSlot < now) g_nextSlot += ((now - g_nextSlot) / g_period + 1) * g_period;
    SDL_DelayPrecise(g_nextSlot - now);
}

// kVsync: called after the swap. Falls back to the timer when vsync does not hold the rate.
void CheckVsync() {
    if (g_checkFrames < 0) return;
    const Uint64 now = SDL_GetTicksNS();
    ++g_checkFrames;
    if (g_checkFrames == kVsyncCheckSkip) g_checkStart = now;
    if (g_checkFrames == kVsyncCheckSkip + kVsyncCheckFrames) {
        const Uint64 average = (now - g_checkStart) / kVsyncCheckFrames;
        g_checkFrames = -1;
        if (average < g_period - g_period / 20) {
            char why[64];
            SDL_snprintf(why, sizeof(why), "vsync measured at %.1f fps", 1e9 / static_cast<double>(average));
            SetTimerPacing(why);
        }
    }
}
}  // namespace

bool Init(const Config& cfg) {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD | SDL_INIT_EVENTS)) {
        DOTD_LOG("sdl: SDL_Init failed: %s", SDL_GetError());
        return false;
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_WindowFlags flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY;
    if (cfg.fullscreen) flags |= SDL_WINDOW_FULLSCREEN;
    if (cfg.hiddenWindow) flags |= SDL_WINDOW_HIDDEN;
    g_window = SDL_CreateWindow(g_baseTitle.c_str(), cfg.windowWidth, cfg.windowHeight, flags);
    if (!g_window) {
        DOTD_LOG("sdl: SDL_CreateWindow failed: %s", SDL_GetError());
        return false;
    }
    g_context = SDL_GL_CreateContext(g_window);
    if (!g_context) {
        DOTD_LOG("sdl: SDL_GL_CreateContext failed: %s", SDL_GetError());
        return false;
    }
    SDL_GL_MakeCurrent(g_window, g_context);
    g_frameRate = cfg.frameRate;
    g_vsyncWanted = cfg.vsync;
    ChoosePacing();
    int count = 0;
    SDL_JoystickID* ids = SDL_GetGamepads(&count);
    for (int i = 0; i < count; ++i) OpenGamepad(ids[i]);
    SDL_free(ids);
    DOTD_LOG("sdl: window %dx%d, vsync %d, %d gamepad(s)", cfg.windowWidth, cfg.windowHeight, cfg.vsync ? 1 : 0, count);
    return true;
}

void Shutdown() {
    {
        std::lock_guard<std::mutex> lock(g_padMutex);
        for (SDL_Gamepad* gp : g_gamepads) SDL_CloseGamepad(gp);
        g_gamepads.clear();
    }
    if (g_context) SDL_GL_DestroyContext(g_context);
    if (g_window) SDL_DestroyWindow(g_window);
    g_context = nullptr;
    g_window = nullptr;
    SDL_Quit();
}

void PumpEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
        case SDL_EVENT_QUIT:
            PostSysutilEvent(CELL_SYSUTIL_REQUEST_EXITGAME, 0);
            break;
        case SDL_EVENT_GAMEPAD_ADDED:
            OpenGamepad(e.gdevice.which);
            break;
        case SDL_EVENT_GAMEPAD_REMOVED:
            CloseGamepad(e.gdevice.which);
            break;
        case SDL_EVENT_KEY_DOWN:
        case SDL_EVENT_KEY_UP:
            freecam::OnKey(static_cast<int>(e.key.scancode), e.type == SDL_EVENT_KEY_DOWN);
            break;
        case SDL_EVENT_MOUSE_MOTION:
            freecam::OnMouseMotion(e.motion.xrel, e.motion.yrel, (e.motion.state & SDL_BUTTON_RMASK) != 0);
            break;
        case SDL_EVENT_MOUSE_WHEEL:
            freecam::OnMouseWheel(e.wheel.y);
            break;
        case SDL_EVENT_WINDOW_DISPLAY_CHANGED:
        case SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED:
            ChoosePacing();
            break;
        default:
            break;
        }
    }
}

namespace {
constexpr long kStatsWarmup = 60;
long g_presented = 0;
Uint64 g_statsStart = 0, g_lastPresent = 0, g_minInterval = ~0ull, g_maxInterval = 0;
long g_late = 0;

void RecordFrame() {
    const Uint64 now = SDL_GetTicksNS();
    ++g_presented;
    if (g_presented == kStatsWarmup) g_statsStart = now;
    if (g_presented > kStatsWarmup) {
        const Uint64 interval = now - g_lastPresent;
        if (interval < g_minInterval) g_minInterval = interval;
        if (interval > g_maxInterval) g_maxInterval = interval;
        if (g_period > 0 && interval > g_period + g_period / 2) ++g_late;
    }
    g_lastPresent = now;
}

// The window title shows the presented frame rate and the average frame time, refreshed every half second
// (like RPCS3's "FPS: 59.94" title). Host-side only: the game never sees it.
void UpdateTitleFps() {
    static Uint64 s_windowStart = 0;
    static long s_windowFrames = 0;
    const Uint64 now = SDL_GetTicksNS();
    if (s_windowStart == 0) s_windowStart = now;
    ++s_windowFrames;
    const Uint64 elapsed = now - s_windowStart;
    if (elapsed < 500000000ull) return;
    const double fps = s_windowFrames * 1e9 / static_cast<double>(elapsed);
    char title[256];
    std::snprintf(title, sizeof(title), "%s | FPS: %.2f | %.2f ms", g_baseTitle.c_str(), fps, 1000.0 / fps);
    SDL_SetWindowTitle(g_window, title);
    s_windowStart = now;
    s_windowFrames = 0;
}
}  // namespace

void SwapWindow() {
    SDL_GL_SwapWindow(g_window);
    if (g_paceMode == kTimer) WaitForSlot();
    if (g_paceMode == kVsync) CheckVsync();
    RecordFrame();
    UpdateTitleFps();
    PumpEvents();
    static Uint64 s_lastFreecam = 0;
    const Uint64 now = SDL_GetTicksNS();
    if (s_lastFreecam != 0) freecam::Update(static_cast<float>(now - s_lastFreecam) * 1e-9f);
    s_lastFreecam = now;
}

void LogFrameStats() {
    if (g_presented <= kStatsWarmup) {
        DOTD_LOG("frames: %ld presented (too few to measure)", g_presented);
        return;
    }
    const long measured = g_presented - kStatsWarmup;
    DOTD_LOG("frames: %ld presented, %ld measured, %.3f fps average, frame time %.2f..%.2f ms, %ld late (over 1.5 frames)",
             g_presented, measured, measured * 1e9 / static_cast<double>(g_lastPresent - g_statsStart),
             g_minInterval / 1e6, g_maxInterval / 1e6, g_late);
}

void GetDrawableSize(int* width, int* height) { SDL_GetWindowSizeInPixels(g_window, width, height); }

// The FPS counter is appended to `title` at the next refresh.
void SetWindowTitle(const char* title) {
    g_baseTitle = title;
    SDL_SetWindowTitle(g_window, title);
}

void* GetGLProcAddress(const char* name) { return reinterpret_cast<void*>(SDL_GL_GetProcAddress(name)); }

bool ReadPad(int port, uint16_t words[24]) {
    std::memset(words, 0, 24 * sizeof(uint16_t));
    words[4] = words[5] = words[6] = words[7] = 0x80;  // sticks centred
    words[20] = words[21] = words[22] = 512;           // sensors neutral
    words[23] = 512;
    bool present = false;
    {
        std::lock_guard<std::mutex> lock(g_padMutex);
        if (port >= 0 && port < static_cast<int>(g_gamepads.size())) {
            ReadGamepad(g_gamepads[static_cast<size_t>(port)], words);
            present = true;
        }
    }
    if (port == 0) {
        ReadKeyboard(words);
        present = true;
    }
    return present;
}

int ConnectedPadCount() {
    std::lock_guard<std::mutex> lock(g_padMutex);
    const int n = static_cast<int>(g_gamepads.size());
    return n > 0 ? n : 1;  // the keyboard counts as port 0
}

void Rumble(int port, uint8_t smallMotor, uint8_t largeMotor) {
    std::lock_guard<std::mutex> lock(g_padMutex);
    if (port < 0 || port >= static_cast<int>(g_gamepads.size())) return;
    const Uint16 low = static_cast<Uint16>(largeMotor * 257);
    const Uint16 high = static_cast<Uint16>(smallMotor ? 0xffff : 0);
    SDL_RumbleGamepad(g_gamepads[static_cast<size_t>(port)], low, high, 200);
}

}  // namespace dotd::platform::sdl
