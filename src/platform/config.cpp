#include "platform/config.h"

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>

#include "platform/fps.h"
#include "platform/log.h"

namespace dotd::platform {

namespace {
Config g_config;

std::string Trim(const std::string& s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    size_t b = s.find_last_not_of(" \t\r\n");
    if (a == std::string::npos) return std::string();
    return s.substr(a, b - a + 1);
}

void Apply(Config& c, const std::string& key, const std::string& value) {
    if (key == "usrdir") c.usrdir = value;
    else if (key == "savedir") c.saveDir = value;
    else if (key == "language") c.language = std::atoi(value.c_str());
    else if (key == "enter_button") c.enterButton = std::atoi(value.c_str());
    else if (key == "pad_rumble") c.padRumble = std::atoi(value.c_str());
    else if (key == "window_width") c.windowWidth = std::atoi(value.c_str());
    else if (key == "window_height") c.windowHeight = std::atoi(value.c_str());
    else if (key == "fullscreen") c.fullscreen = std::atoi(value.c_str()) != 0;
    else if (key == "vsync") c.vsync = std::atoi(value.c_str()) != 0;
    else if (key == "frame_rate") c.frameRate = std::atoi(value.c_str());
    else if (key == "fps") c.fps = std::atoi(value.c_str());
    else if (key == "show_fps") c.showFps = std::atoi(value.c_str()) != 0;
    else DOTD_LOG("config: unknown key '%s'", key.c_str());
}

bool ReadIni(const std::string& path, Config& c) {
    std::ifstream in(path);
    if (!in) return false;
    std::string line;
    while (std::getline(in, line)) {
        line = Trim(line);
        if (line.empty() || line[0] == '#' || line[0] == ';' || line[0] == '[') continue;
        size_t eq = line.find('=');
        if (eq == std::string::npos) continue;
        Apply(c, Trim(line.substr(0, eq)), Trim(line.substr(eq + 1)));
    }
    DOTD_LOG("config: read %s", path.c_str());
    return true;
}

std::string ExeDirectory(const char* argv0) {
    if (!argv0) return std::string();
    std::string p(argv0);
    size_t slash = p.find_last_of("/\\");
    return slash == std::string::npos ? std::string() : p.substr(0, slash + 1);
}
}  // namespace

bool LoadConfig(int argc, char** argv, Config& out) {
    Config c;
#ifdef __EMSCRIPTEN__
    c.showFps = true;
#endif
    if (!ReadIni("dotd.ini", c) && argc > 0) {
        ReadIni(ExeDirectory(argv[0]) + "dotd.ini", c);
    }
    if (const char* env = std::getenv("DOTD_USRDIR")) {
        if (c.usrdir.empty()) c.usrdir = env;
    }
    for (int i = 1; i < argc; ++i) {
        const char* a = argv[i];
        if (std::strcmp(a, "--usrdir") == 0 && i + 1 < argc) c.usrdir = argv[++i];
        else if (std::strcmp(a, "--lang") == 0 && i + 1 < argc) c.language = std::atoi(argv[++i]);
        else if (std::strcmp(a, "--fullscreen") == 0) c.fullscreen = true;
        else if (std::strcmp(a, "--novsync") == 0) c.vsync = false;
        else if (std::strcmp(a, "--frame-rate") == 0 && i + 1 < argc) c.frameRate = std::atoi(argv[++i]);
        else if (std::strcmp(a, "--fps") == 0 && i + 1 < argc) c.fps = std::atoi(argv[++i]);
        else if (std::strcmp(a, "--show-fps") == 0) {
            // An optional 0 / 1 after it (the web page writes ?show-fps=0 as "--show-fps 0").
            c.showFps = true;
            if (i + 1 < argc && (std::strcmp(argv[i + 1], "0") == 0 || std::strcmp(argv[i + 1], "1") == 0)) {
                c.showFps = argv[++i][0] == '1';
            }
        }
    }
    // --fps N (any N but 60; negative = 60): the pacer's target and the 60 Hz timing calculation (platform/fps.h).
    if (c.fps < 0) c.fps = 60;
    const bool unlocked = c.fps != 60;
    if (unlocked) {
        c.frameRate = c.fps;
        DOTD_LOG("config: fps %d with the 60 Hz timing calculation", c.fps);
    }
    fps::Configure(unlocked);
    // normalise: forward slashes, no trailing separator
    for (char& ch : c.usrdir) {
        if (ch == '\\') ch = '/';
    }
    while (!c.usrdir.empty() && c.usrdir.back() == '/') c.usrdir.pop_back();
    g_config = c;
    out = c;
    return true;
}

const Config& GetConfig() { return g_config; }
Config& MutableConfig() { return g_config; }

}  // namespace dotd::platform
