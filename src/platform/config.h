// config.h - user settings for the platform layer.
// Read from dotd.ini (current directory, then next to the executable); command-line options override.
// The game data path is never part of the repository: the user points --usrdir at their own copy of
// PS3_GAME/USRDIR, which is only ever read.
#pragma once
#include <string>

namespace dotd::platform {

struct Config {
    std::string usrdir;       // local copy of the disc's PS3_GAME/USRDIR (read-only)
    std::string saveDir;      // where saves will go (later); empty = SDL pref path
    int language = 1;         // CELL_SYSUTIL_SYSTEMPARAM_ID_LANG: 1 = English (US)
    int enterButton = 1;      // CELL_SYSUTIL_SYSTEMPARAM_ID_ENTER_BUTTON_ASSIGN: 1 = cross, 0 = circle
    int padRumble = 1;        // CELL_SYSUTIL_SYSTEMPARAM_ID_PAD_RUMBLE
    int windowWidth = 1280;
    int windowHeight = 720;
    bool fullscreen = false;
    bool vsync = true;
    bool hiddenWindow = false;  // the window is created hidden (offscreen rendering for tests and screenshots)
    int frameRate = 60;       // game frames per second (the PS3 runs at 60); 0 = uncapped (experiments only)
};

// Loads dotd.ini and applies argv options (--usrdir PATH, --lang N, --fullscreen, --novsync, --frame-rate N).
// Unknown options are left for the caller. Returns false only on malformed options.
bool LoadConfig(int argc, char** argv, Config& out);

// The configuration in use (set by LoadConfig).
const Config& GetConfig();
Config& MutableConfig();

}  // namespace dotd::platform
