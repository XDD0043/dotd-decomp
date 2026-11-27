#include "platform/sdl/app.h"

#include <SDL3/SDL.h>

#include <algorithm>
#include <atomic>
#include <cstdio>
#include <cstring>
#include <mutex>
#include <string>
#include <vector>

#include "platform/cell/sysutil.h"
#include "platform/config.h"
#include "platform/frame_loop.h"
#include "platform/gfx/device.h"
#include "platform/log.h"
#include "platform/sdl/freecam.h"

namespace dotd::platform {
namespace {
float g_presentedFps = 0.0f;  // UpdateTitleFps's last measurement
}
float PresentedFps() { return g_presentedFps; }
}  // namespace dotd::platform

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

// Keyboard on port 0 (merged into port 0's words; a pressed key overrides the gamepad's value). The keys of each pad
// button and stick direction are dotd.ini's key_<action> lines (key_cross = X, several keys comma-separated, SDL's key
// names; the launcher's Controls dialog writes them); an action without a line keeps its default below. The defaults
// are RPCS3's default keyboard pad (the user plays the original that way; 2026-11-14: R / T were R3 / the right stick
// here, so the dragon switch L2 and the abilities R2 could not be pressed), plus a few extra keys:
//   left stick (move)    W / A / S / D            right stick (camera)  Home / Delete / End / Page Down (up / left /
//                                                                       down / right), or numpad 8 / 4 / 5 / 6
//   d-pad (elements)     arrows                   L3 / R3               F / G (also Tab / numpad 0)
//   cross (jump)         X (also K)               circle                C (also Escape, L)
//   square               Z (also J)               triangle              V (also I)
//   L1 / R1              Q / E                    L2 / R2               R / T (also 1 / 3; pressure 255)
//   start / select       Enter / Space (also Backspace)
// Sticks are full deflection (0 / 255, centre 128; up = 0 as the DS3's CellPadData). The front end reads cross as
// validate and circle as back (the "Flash Manager" input project, entries 4 and 5). With the debug free camera on
// (F1) WASD fly it and the left stick's keys are not read.
// An SDL gamepad on port n is read as a DualShock 3 (ReadGamepad): positional face buttons (south = cross, east =
// circle, west = square, north = triangle), shoulders L1 / R1, triggers L2 / R2 (analog 0..255 into the pressure
// words 18 / 19, digital above 64), stick clicks L3 / R3, back = select, start, the d-pad, both sticks (0..255, centre
// 128, up = 0), the pressure words 8..17 at 255 while pressed; rumble: Rumble() below.
struct KeyAction {
    const char* name;      // dotd.ini key_<name>
    int word;              // 2 / 3: the digital words; 4..7: right stick x, y, left stick x, y
    uint16_t bit;          // a digital word's bit
    uint8_t axis;          // a stick direction: the axis value while held (0 left / up, 255 right / down)
    int pressure;          // the pressure word set to 255 while held (-1: none)
    const char* defaults;  // SDL key names
};
// (Within a stick axis a later action wins when both are held: right over left, down over up, as before.)
const KeyAction kKeyActions[] = {
    {"dpad_up", 2, kUp, 0, 10, "Up"},
    {"dpad_down", 2, kDown, 0, 11, "Down"},
    {"dpad_left", 2, kLeft, 0, 9, "Left"},
    {"dpad_right", 2, kRight, 0, 8, "Right"},
    {"cross", 3, kCross, 0, 14, "X, K"},
    {"circle", 3, kCircle, 0, 13, "C, Escape, L"},
    {"square", 3, kSquare, 0, 15, "Z, J"},
    {"triangle", 3, kTriangle, 0, 12, "V, I"},
    {"l1", 3, kL1, 0, 16, "Q"},
    {"l2", 3, kL2, 0, 18, "R, 1"},
    {"l3", 2, kL3, 0, -1, "F, Tab"},
    {"r1", 3, kR1, 0, 17, "E"},
    {"r2", 3, kR2, 0, 19, "T, 3"},
    {"r3", 2, kR3, 0, -1, "G, Keypad 0"},
    {"start", 2, kStart, 0, -1, "Return"},
    {"select", 2, kSelect, 0, -1, "Space, Backspace"},
    {"lstick_left", 6, 0, 0, -1, "A"},
    {"lstick_right", 6, 0, 255, -1, "D"},
    {"lstick_up", 7, 0, 0, -1, "W"},
    {"lstick_down", 7, 0, 255, -1, "S"},
    {"rstick_left", 4, 0, 0, -1, "Delete, Keypad 4"},
    {"rstick_right", 4, 0, 255, -1, "PageDown, Keypad 6"},
    {"rstick_up", 5, 0, 0, -1, "Home, Keypad 8"},
    {"rstick_down", 5, 0, 255, -1, "End, Keypad 5, Keypad 2"},
};
constexpr size_t kKeyActionCount = sizeof(kKeyActions) / sizeof(kKeyActions[0]);
struct KeyBinding {
    SDL_Scancode scancode;
    uint8_t action;  // index into kKeyActions
};
std::vector<KeyBinding> g_keyBindings;  // made by Init (BuildKeyBindings), only read afterwards (the pad reads)

// The bindings: each action's keys from its dotd.ini line or its defaults. An unknown key name or action is reported
// (a config warning) and skipped; an empty line unbinds the action.
void BuildKeyBindings(const Config& cfg) {
    g_keyBindings.clear();
    std::vector<bool> used(cfg.keyBindings.size(), false);
    for (size_t a = 0; a < kKeyActionCount; ++a) {
        std::string keys = kKeyActions[a].defaults;
        for (size_t i = 0; i < cfg.keyBindings.size(); ++i) {
            if (cfg.keyBindings[i].first == kKeyActions[a].name) {
                keys = cfg.keyBindings[i].second;
                used[i] = true;
            }
        }
        size_t at = 0;
        while (at <= keys.size()) {
            size_t comma = keys.find(',', at);
            if (comma == std::string::npos) comma = keys.size();
            std::string key = keys.substr(at, comma - at);
            at = comma + 1;
            const size_t first = key.find_first_not_of(" \t"), last = key.find_last_not_of(" \t");
            if (first == std::string::npos) continue;
            key = key.substr(first, last - first + 1);
            const SDL_Scancode scancode = SDL_GetScancodeFromName(key.c_str());
            if (scancode == SDL_SCANCODE_UNKNOWN) {
                DOTD_LOG("config: WARNING: key_%s: unknown key '%s'; ignored", kKeyActions[a].name, key.c_str());
                continue;
            }
            g_keyBindings.push_back({scancode, static_cast<uint8_t>(a)});
        }
    }
    for (size_t i = 0; i < cfg.keyBindings.size(); ++i) {
        if (!used[i]) DOTD_LOG("config: WARNING: dotd.ini key_%s: no such pad button; ignored", cfg.keyBindings[i].first.c_str());
    }
    if (!cfg.keyBindings.empty()) {
        DOTD_LOG("sdl: keyboard pad: %d key(s), %d action(s) set by dotd.ini", static_cast<int>(g_keyBindings.size()),
                 static_cast<int>(cfg.keyBindings.size()));
    }
}

void ReadKeyboard(uint16_t w[24]) {
    int count = 0;
    const bool* k = SDL_GetKeyboardState(&count);
    if (!k) return;
#ifndef __EMSCRIPTEN__
    const bool alt = (SDL_GetModState() & SDL_KMOD_ALT) != 0;  // (Alt+Enter is the full screen key, not START)
#else
    const bool alt = false;
#endif
    const bool freecamOn = freecam::Enabled();  // (WASD fly the debug camera: the left stick's keys are not read)
    for (const KeyBinding& b : g_keyBindings) {
        if (b.scancode >= count || !k[b.scancode]) continue;
        if (alt && b.scancode == SDL_SCANCODE_RETURN) continue;
        const KeyAction& a = kKeyActions[b.action];
        if (a.word >= 4) {
            if (!(freecamOn && a.word >= 6)) w[a.word] = a.axis;
            continue;
        }
        w[a.word] |= a.bit;
        if (a.pressure >= 0) w[a.pressure] = 255;
    }
}

// The touch pad (SetTouchPad): word 2 | word 3 << 16, and the sticks left x | left y << 8 | right x << 16 |
// right y << 24. A pressed button also sets its pressure word, a stick off its centre replaces the pad's.
std::atomic<uint32_t> g_touchButtons{0};
std::atomic<uint32_t> g_touchSticks{0x80808080u};

void ReadTouch(uint16_t w[24]) {
    const uint32_t buttons = g_touchButtons.load(std::memory_order_relaxed);
    const uint32_t sticks = g_touchSticks.load(std::memory_order_relaxed);
    if (buttons == 0 && sticks == 0x80808080u) return;
    struct Map { int word; uint16_t bit; int pressure; };
    static const Map kMap[] = {
        {2, kUp, 10},       {2, kRight, 8},   {2, kDown, 11},  {2, kLeft, 9},
        {3, kTriangle, 12}, {3, kCircle, 13}, {3, kCross, 14}, {3, kSquare, 15},
        {3, kL1, 16},       {3, kR1, 17},     {3, kL2, 18},    {3, kR2, 19},
    };
    w[2] |= static_cast<uint16_t>(buttons & 0xffffu);
    w[3] |= static_cast<uint16_t>(buttons >> 16);
    for (const Map& m : kMap) {
        if (((m.word == 2 ? buttons : buttons >> 16) & m.bit) != 0) w[m.pressure] = 255;
    }
    const uint16_t lx = sticks & 0xffu, ly = (sticks >> 8) & 0xffu, rx = (sticks >> 16) & 0xffu, ry = sticks >> 24;
    if (lx != 0x80 || ly != 0x80) {
        w[6] = lx;
        w[7] = ly;
    }
    if (rx != 0x80 || ry != 0x80) {
        w[4] = rx;
        w[5] = ry;
    }
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
//   kUncapped: frameRate 0: swap interval 1 with vsync on (the display's refresh), 0 with --novsync.
// frameRate is 60 by default. --frame-rate N changes it alone (experiments: the per-update systems then run at
// N/60 speed). --fps N sets it to N and turns on the 60 Hz timing calculation (platform/fps.h), which keeps
// the menu animations, physics and the other per-update systems at their 60 fps speed; --fps 0 = kUncapped.
// Above the display's refresh, or at a rate that does not divide it, the timer paces with vsync off.
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
#ifdef __EMSCRIPTEN__
    // The web build: the browser presents when the frame callback returns and the callback does the pacing
    // (platform/frame_loop.cpp); nothing may wait here.
    g_paceMode = kUncapped;
    return;
#endif
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

#ifndef __EMSCRIPTEN__
// ---- full screen (native) ------------------------------------------------------------------------
// Two kinds (Config::exclusiveFullscreen). Borderless: SDL's desktop full screen, a window covering the display in
// the desktop's mode; anything may show over it. Exclusive: SDL's display mode full screen: the display is set to
// the mode below and the window is kept on top of everything; SDL minimises it when it loses the focus (its
// SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS "auto"). (Windows has no exclusive ownership of the display for OpenGL as
// for Direct3D; a window covering the display is presented directly by the driver either way.)
// F11 / Alt+Enter switch full screen on and off, Shift+F11 the kind (at once when full screen).
bool g_exclusiveFullscreen = false;

// The display mode of exclusive full screen: the render resolution's (--resolution) when the window's display has a
// mode at least that large (SDL picks the closest), at the desktop's refresh rate; otherwise the desktop's mode.
bool ExclusiveMode(SDL_DisplayMode* mode) {
    const SDL_DisplayID display = SDL_GetDisplayForWindow(g_window);
    if (display == 0) return false;
    const Config& cfg = GetConfig();
    if (cfg.renderWidth > 0 &&
        SDL_GetClosestFullscreenDisplayMode(display, cfg.renderWidth, cfg.renderHeight, 0.0f, false, mode)) {
        return true;
    }
    const SDL_DisplayMode* desktop = SDL_GetDesktopDisplayMode(display);
    if (desktop == nullptr) return false;
    *mode = *desktop;
    return true;
}

// The kind of full screen the window takes (now, when it is full screen).
void ApplyFullscreenKind() {
    SDL_DisplayMode mode;
    if (g_exclusiveFullscreen && ExclusiveMode(&mode)) {
        if (SDL_SetWindowFullscreenMode(g_window, &mode)) {
            DOTD_LOG("sdl: exclusive full screen, %dx%d at %.2f Hz", mode.w, mode.h, mode.refresh_rate);
            return;
        }
        DOTD_LOG("sdl: exclusive full screen %dx%d refused (%s): borderless", mode.w, mode.h, SDL_GetError());
    }
    SDL_SetWindowFullscreenMode(g_window, nullptr);
    DOTD_LOG("sdl: borderless full screen");
}

bool IsFullscreen() { return g_window != nullptr && (SDL_GetWindowFlags(g_window) & SDL_WINDOW_FULLSCREEN) != 0; }

void SetFullscreen(bool on) {
    if (on) ApplyFullscreenKind();
    if (!SDL_SetWindowFullscreen(g_window, on)) {
        DOTD_LOG("sdl: SDL_SetWindowFullscreen(%d) failed: %s", on ? 1 : 0, SDL_GetError());
        return;
    }
    if (!on) DOTD_LOG("sdl: windowed");
}

// F11 / Alt+Enter and Shift+F11 (PumpEvents).
void OnFullscreenKey(const SDL_KeyboardEvent& key) {
    if (key.repeat) return;
    const bool f11 = key.scancode == SDL_SCANCODE_F11;
    const bool altEnter = (key.scancode == SDL_SCANCODE_RETURN || key.scancode == SDL_SCANCODE_KP_ENTER) &&
                          (key.mod & SDL_KMOD_ALT) != 0;
    if (f11 && (key.mod & SDL_KMOD_SHIFT) != 0) {
        g_exclusiveFullscreen = !g_exclusiveFullscreen;
        if (IsFullscreen()) ApplyFullscreenKind();
        else DOTD_LOG("sdl: full screen kind: %s (F11 turns it on)", g_exclusiveFullscreen ? "exclusive" : "borderless");
    } else if (f11 || altEnter) {
        SetFullscreen(!IsFullscreen());
    }
}

// F3: MSAA off -> 2x -> 4x -> 8x -> 16x -> off (a step past what the driver has goes back to off); Shift+F3: FXAA on / off;
// Ctrl+F3: alpha-to-coverage on / off (platform/gfx/device.h). The window's title shows the setting.
void OnAntialiasingKey(const SDL_KeyboardEvent& key) {
    if (key.repeat || key.scancode != SDL_SCANCODE_F3) return;
    const int now = gfx::MsaaSamples();
    if ((key.mod & SDL_KMOD_CTRL) != 0) {
        gfx::SetAlphaToCoverage(!gfx::AlphaToCoverageEnabled());
        return;
    }
    if ((key.mod & SDL_KMOD_SHIFT) != 0) {
        gfx::SetAntialiasing(now, !gfx::FxaaEnabled());
        return;
    }
    const int next = now == 0 ? 2 : now * 2;
    if (next > 16 || gfx::SetAntialiasing(next, gfx::FxaaEnabled()) <= now) gfx::SetAntialiasing(0, gfx::FxaaEnabled());
}
#endif

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
#ifdef __EMSCRIPTEN__
    // WebGL2 = OpenGL ES 3.0 (platform/gfx/gl.h lists only entry points both have), on the page's canvas.
    SDL_SetHint(SDL_HINT_EMSCRIPTEN_CANVAS_SELECTOR, "#canvas");
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
#else
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#endif
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
#ifdef __EMSCRIPTEN__
    SDL_WindowFlags flags = SDL_WINDOW_OPENGL;  // the canvas keeps the size asked for; the page scales it
#else
    SDL_WindowFlags flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY;
#endif
    if (cfg.fullscreen) flags |= SDL_WINDOW_FULLSCREEN;
    if (cfg.hiddenWindow) flags |= SDL_WINDOW_HIDDEN;
    int windowWidth = cfg.windowWidth, windowHeight = cfg.windowHeight;
#ifndef __EMSCRIPTEN__
    // Exclusive full screen from the start: the window is shown once its display mode is set (below).
    const bool showLater = cfg.fullscreen && cfg.exclusiveFullscreen && !cfg.hiddenWindow;
    if (showLater) flags |= SDL_WINDOW_HIDDEN;
    // A window sized after --resolution (no window size given) shrinks to 90 % of the display's usable area, keeping
    // its aspect (a 4K picture on a smaller display: the present scales it down). Also when it starts full screen:
    // it is the window F11 goes back to.
    if (!cfg.windowSizeSet && cfg.renderWidth != 0) {
        SDL_Rect usable;
        if (SDL_GetDisplayUsableBounds(SDL_GetPrimaryDisplay(), &usable) && usable.w > 0 && usable.h > 0) {
            const double fit = std::min({1.0, 0.9 * usable.w / windowWidth, 0.9 * usable.h / windowHeight});
            if (fit < 1.0) {
                windowWidth = std::max(1, static_cast<int>(windowWidth * fit));
                windowHeight = std::max(1, static_cast<int>(windowHeight * fit));
            }
        }
    }
#endif
    g_window = SDL_CreateWindow(g_baseTitle.c_str(), windowWidth, windowHeight, flags);
    if (!g_window) {
        DOTD_LOG("sdl: SDL_CreateWindow failed: %s", SDL_GetError());
        return false;
    }
#ifndef __EMSCRIPTEN__
    g_exclusiveFullscreen = cfg.exclusiveFullscreen;
    if (cfg.fullscreen) ApplyFullscreenKind();
    if (showLater) SDL_ShowWindow(g_window);
#endif
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
    DOTD_LOG("sdl: window %dx%d, vsync %d, %d gamepad(s)", windowWidth, windowHeight, cfg.vsync ? 1 : 0, count);
    BuildKeyBindings(cfg);
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
            // F2: the frame rate between 60 and no cap (--fps 0), while the game runs.
            if (e.type == SDL_EVENT_KEY_DOWN && !e.key.repeat && e.key.scancode == SDL_SCANCODE_F2) {
                SetFps(GetConfig().fps == 60 ? 0 : 60);
            }
#ifndef __EMSCRIPTEN__
            if (e.type == SDL_EVENT_KEY_DOWN) OnFullscreenKey(e.key);  // F11 / Alt+Enter, Shift+F11
            if (e.type == SDL_EVENT_KEY_DOWN) OnAntialiasingKey(e.key);  // F3, Shift+F3
#endif
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
// (like RPCS3's "FPS: 59.94" title). Host-side only: the game never sees it. The web build only measures (for
// the counter on the screen): the page keeps its title.
void UpdateTitleFps() {
    static Uint64 s_windowStart = 0;
    static long s_windowFrames = 0;
    const Uint64 now = SDL_GetTicksNS();
    if (s_windowStart == 0) s_windowStart = now;
    ++s_windowFrames;
    const Uint64 elapsed = now - s_windowStart;
    if (elapsed < 500000000ull) return;
    const double fps = s_windowFrames * 1e9 / static_cast<double>(elapsed);
    dotd::platform::g_presentedFps = static_cast<float>(fps);
#ifndef __EMSCRIPTEN__
    char title[256];
    const char* aa = gfx::AntialiasingName();  // (F3 / Shift+F3: shown while not off)
    std::snprintf(title, sizeof(title), "%s | FPS: %.2f | %.2f ms%s%s", g_baseTitle.c_str(), fps, 1000.0 / fps,
                  std::strcmp(aa, "off") != 0 ? " | " : "", std::strcmp(aa, "off") != 0 ? aa : "");
    SDL_SetWindowTitle(g_window, title);
#endif
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

void SetFrameRate(int frameRate) {
    g_frameRate = frameRate;
    if (g_window != nullptr) ChoosePacing();
}

void GetDrawableSize(int* width, int* height) { SDL_GetWindowSizeInPixels(g_window, width, height); }

void SetWindowSize(int width, int height) {
    if (g_window != nullptr && !SDL_SetWindowSize(g_window, width, height)) {
        DOTD_LOG("sdl: SDL_SetWindowSize %dx%d failed: %s", width, height, SDL_GetError());
    }
}

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
        ReadTouch(words);
        present = true;
    }
    return present;
}

void SetTouchPad(uint16_t digital1, uint16_t digital2, uint8_t leftX, uint8_t leftY, uint8_t rightX, uint8_t rightY) {
    g_touchButtons.store(static_cast<uint32_t>(digital1) | static_cast<uint32_t>(digital2) << 16,
                         std::memory_order_relaxed);
    g_touchSticks.store(static_cast<uint32_t>(leftX) | static_cast<uint32_t>(leftY) << 8 |
                            static_cast<uint32_t>(rightX) << 16 | static_cast<uint32_t>(rightY) << 24,
                        std::memory_order_relaxed);
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
