// config.h - user settings for the platform layer.
// Read from dotd.ini (current directory, then next to the executable); command-line options override.
// The game data path is never part of the repository: the user points --usrdir at their own copy of
// PS3_GAME/USRDIR, which is only ever read.
#pragma once
#include <string>
#include <utility>
#include <vector>

namespace dotd::platform {

struct Config {
    std::string usrdir;       // local copy of the disc's PS3_GAME/USRDIR (read-only)
    std::string saveDir;      // where saves will go (later); empty = SDL pref path
    int language = 1;         // CELL_SYSUTIL_SYSTEMPARAM_ID_LANG: 1 = English (US)
    int enterButton = 1;      // CELL_SYSUTIL_SYSTEMPARAM_ID_ENTER_BUTTON_ASSIGN: 1 = cross, 0 = circle
    int padRumble = 1;        // CELL_SYSUTIL_SYSTEMPARAM_ID_PAD_RUMBLE
    int windowWidth = 1280;
    int windowHeight = 720;
    // window_width / window_height in dotd.ini or --window WxH: the window's size was given. Without it the window
    // takes the render resolution's size (made smaller to fit the display).
    bool windowSizeSet = false;
    // --resolution WxH / resolution = WxH: the pixels the game is rendered at (0 x 0 = the PS3's 1280x720). The game
    // itself keeps seeing 1280x720 for any picture of 16:9 (its logic and layout are the original's; only the pixel
    // count changes); another aspect is shown as the original would on a frame buffer of that aspect: 720 rows and the
    // width of the aspect (platform/gfx/device.h ScreenSizeFor). The window shows the picture letterboxed.
    int renderWidth = 0;
    int renderHeight = 0;
    // fullscreen = 1 / --fullscreen: start full screen; --windowed: start in a window whatever dotd.ini says.
    // F11 (or Alt+Enter) switches it while the game runs, Shift+F11 switches the kind.
    bool fullscreen = false;
    // fullscreen_mode = borderless | exclusive, --fullscreen-mode KIND (or --fullscreen KIND, which also starts full
    // screen): the kind of full screen. Borderless (the default): a window covering the display in the desktop's mode;
    // other windows, overlays and notifications can show over it and Alt+Tab is instant. Exclusive: SDL's display
    // mode full screen: the display is set to the render resolution's mode when it has one (--resolution), the
    // desktop's mode otherwise; the window stays on top of everything and is minimised when it loses the focus.
    bool exclusiveFullscreen = false;
    // Anti-aliasing (platform/gfx/device.h SetAntialiasing; the original has none, the default here neither):
    // msaa = N / --msaa N: multisampling with N samples (2, 4, 8, 16; brought down to what the driver has);
    // fxaa = 1 / --fxaa [0|1]: FXAA on the 3D picture (not on the HUD). DOTD_MSAA / DOTD_FXAA set them too (tests).
    // F3 steps MSAA through off / 2x / 4x / 8x / 16x while the game runs, Shift+F3 switches FXAA.
    int msaa = 0;
    bool fxaa = false;
    // alpha_to_coverage = 0 / --alpha-to-coverage 0 (DOTD_ALPHA_TO_COVERAGE=0): the cut-out textures (leaves, grass)
    // keep the alpha test's hard edges under MSAA. On by default (it does nothing without MSAA); Ctrl+F3 switches it.
    bool alphaToCoverage = true;
    bool vsync = true;
    bool hiddenWindow = false;  // the window is created hidden (offscreen rendering for tests and screenshots)
    int frameRate = 60;       // game frames per second (the PS3 runs at 60); 0 = uncapped (experiments only)
    // --fps N / fps = N: run at N frames per second with the 60 Hz timing calculation (platform/fps.h), so the
    // menu animations, physics and the other per-update systems keep their 60 fps speed. N is the target display
    // frame rate and replaces frame_rate; 0 = no cap (with vsync on: the display's refresh; with --novsync: as fast
    // as the machine goes). 60 (the default) = off: the original timing, bit-identical. When N is not a divisor of
    // the display's refresh the pacer runs by timer with vsync off (tearing is possible; a variable-refresh display
    // avoids it).
    int fps = 60;
    // --show-fps [0|1] / show_fps = 1: the presented frame rate in the top right corner of the picture, drawn with
    // the game's own debug text (CManager2d.cpp, DrawFpsCounter). Off by default natively, on in the web build
    // (?show-fps=0 turns it off).
    bool showFps = false;
    // dotd.ini key_<action> = Key[, Key...]: the keyboard pad's keys for a button or stick direction (SDL key names:
    // X, Return, Space, PageDown, Keypad 0, ...; the actions and their defaults are sdl/app.cpp kKeyActions). The
    // launcher's Controls dialog writes them. In dotd.ini order: action (without "key_"), keys.
    std::vector<std::pair<std::string, std::string>> keyBindings;
};

// Loads dotd.ini and applies argv options (--usrdir PATH, --lang N, --fullscreen [KIND], --fullscreen-mode KIND,
// --windowed, --msaa N, --fxaa [0|1], --novsync, --frame-rate N, --fps N, --resolution WxH, --window WxH).
// Every word of the command line is checked against dotd's options (config.cpp kOptions, main.cpp's included): an
// unknown option, a word that is not one, a missing or malformed value gets a warning in the log ("config: WARNING:")
// and is ignored; main.cpp reads its own options itself. Returns true.
bool LoadConfig(int argc, char** argv, Config& out);

// The configuration in use (set by LoadConfig).
const Config& GetConfig();
Config& MutableConfig();

}  // namespace dotd::platform
