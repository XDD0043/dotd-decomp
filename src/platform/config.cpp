#include "platform/config.h"

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>

#include "platform/fps.h"
#include "platform/log.h"

namespace dotd::platform {

namespace {
Config g_config;

// A configuration problem (an unknown option, a missing or malformed value): logged as a warning and counted, for the
// summary at the end of LoadConfig. Nothing on the command line is dropped without one.
int g_warnings = 0;
#define CONFIG_WARN(...) (++g_warnings, DOTD_LOG(__VA_ARGS__))

std::string Trim(const std::string& s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    size_t b = s.find_last_not_of(" \t\r\n");
    if (a == std::string::npos) return std::string();
    return s.substr(a, b - a + 1);
}

// "WxH" (also "W*H" or "W,H"; 0x0 = the default) into its two numbers, each 0 or in 64..16384. False when malformed.
bool ParseSize(const char* text, int* width, int* height) {
    if (text == nullptr) return false;
    char* end = nullptr;
    const long w = std::strtol(text, &end, 10);
    if (end == text || (*end != 'x' && *end != 'X' && *end != '*' && *end != ',')) return false;
    const char* rest = end + 1;
    const long h = std::strtol(rest, &end, 10);
    if (end == rest || *end != 0) return false;
    if (w == 0 && h == 0) {
        *width = *height = 0;
        return true;
    }
    if (w < 64 || h < 64 || w > 16384 || h > 16384) return false;
    *width = static_cast<int>(w);
    *height = static_cast<int>(h);
    return true;
}

bool ApplySize(const char* option, const char* text, int* width, int* height) {
    if (ParseSize(text, width, height)) return true;
    CONFIG_WARN("config: WARNING: %s '%s': expected WxH (64..16384 each, e.g. 1920x1080); ignored", option,
                text != nullptr ? text : "");
    return false;
}

// A full screen kind: "borderless" or "exclusive" (Config::exclusiveFullscreen). Anything else is logged and ignored.
bool ApplyFullscreenKind(const char* option, const std::string& text, bool* exclusive) {
    if (text == "borderless" || text == "exclusive") {
        *exclusive = text == "exclusive";
        return true;
    }
    CONFIG_WARN("config: WARNING: %s '%s': expected borderless or exclusive; ignored", option, text.c_str());
    return false;
}

// A whole number (an optional sign, digits, nothing after). False, with a warning, when it is not one.
bool ParseInt(const char* option, const char* text, int* out) {
    char* end = nullptr;
    const long v = std::strtol(text, &end, 10);
    if (end == text || *end != 0) {
        CONFIG_WARN("config: WARNING: %s '%s': expected a whole number; ignored", option, text);
        return false;
    }
    *out = static_cast<int>(v);
    return true;
}

// MSAA samples as the device takes them: 0 (off) or 2, 4, 8, 16; another number becomes the next lower one (a warning).
int NormalizeMsaa(const char* source, int samples) {
    int use = 0;
    if (samples >= 2) {
        use = 2;
        while (use * 2 <= samples && use < 16) use *= 2;
    }
    if (use != samples) CONFIG_WARN("config: WARNING: %s %d: expected 0, 2, 4, 8 or 16 (%d is used)", source, samples, use);
    return use;
}

void Apply(Config& c, const std::string& key, const std::string& value) {
    if (key == "usrdir") c.usrdir = value;
    else if (key == "savedir") c.saveDir = value;
    else if (key == "language") c.language = std::atoi(value.c_str());
    else if (key == "enter_button") c.enterButton = std::atoi(value.c_str());
    else if (key == "pad_rumble") c.padRumble = std::atoi(value.c_str());
    else if (key == "window_width") c.windowWidth = std::atoi(value.c_str()), c.windowSizeSet = true;
    else if (key == "window_height") c.windowHeight = std::atoi(value.c_str()), c.windowSizeSet = true;
    else if (key == "resolution") ApplySize("resolution", value.c_str(), &c.renderWidth, &c.renderHeight);
    else if (key == "fullscreen") {
        // 0 / 1, or a kind (which also turns it on): fullscreen = exclusive.
        if (value == "borderless" || value == "exclusive") c.fullscreen = ApplyFullscreenKind("fullscreen", value, &c.exclusiveFullscreen);
        else c.fullscreen = std::atoi(value.c_str()) != 0;
    }
    else if (key == "fullscreen_mode") ApplyFullscreenKind("fullscreen_mode", value, &c.exclusiveFullscreen);
    else if (key == "msaa") c.msaa = NormalizeMsaa("dotd.ini msaa =", std::atoi(value.c_str()));
    else if (key == "fxaa") c.fxaa = std::atoi(value.c_str()) != 0;
    else if (key == "alpha_to_coverage") c.alphaToCoverage = std::atoi(value.c_str()) != 0;
    else if (key == "vsync") c.vsync = std::atoi(value.c_str()) != 0;
    else if (key == "frame_rate") c.frameRate = std::atoi(value.c_str());
    else if (key == "fps") c.fps = std::atoi(value.c_str());
    else if (key == "show_fps") c.showFps = std::atoi(value.c_str()) != 0;
    else if (key.compare(0, 4, "key_") == 0) c.keyBindings.emplace_back(key.substr(4), value);  // (sdl/app.cpp checks them)
    else CONFIG_WARN("config: WARNING: dotd.ini: unknown key '%s'; ignored", key.c_str());
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

// ---- the command line --------------------------------------------------------------------------------------------
// Every option dotd takes and what follows it. LoadConfig applies its own; the ones main.cpp reads (`main`) are only
// checked here. Anything else (an unknown option, a word that is not an option, a missing or malformed value) gets a
// warning and is ignored. A new option goes into this table too, or it is reported as unknown.
enum class Value : uint8_t {
    kNone,
    kText,          // any word (a path)
    kInt,           // a whole number
    kSize,          // WxH
    kKind,          // borderless | exclusive
    kOptional01,    // 0 or 1 may follow (the web page writes ?fxaa=0 as "--fxaa 0")
    kOptionalKind,  // borderless | exclusive may follow
};
struct Option {
    const char* name;
    Value value;
    bool main;  // read by main.cpp
};
const Option kOptions[] = {
    {"--usrdir", Value::kText, false},
    {"--lang", Value::kInt, false},
    {"--fullscreen", Value::kOptionalKind, false},
    {"--fullscreen-mode", Value::kKind, false},
    {"--windowed", Value::kNone, false},
    {"--msaa", Value::kInt, false},
    {"--fxaa", Value::kOptional01, false},
    {"--alpha-to-coverage", Value::kOptional01, false},
    {"--novsync", Value::kNone, false},
    {"--frame-rate", Value::kInt, false},
    {"--fps", Value::kInt, false},
    {"--resolution", Value::kSize, false},
    {"--window", Value::kSize, false},
    {"--show-fps", Value::kOptional01, false},
    // main.cpp
    {"--frames", Value::kInt, true},
    {"--headless", Value::kNone, true},
    {"--test-pattern", Value::kNone, true},
    {"--no-shader-list", Value::kNone, true},
    {"--selftest-fs", Value::kNone, true},
    {"--check-game", Value::kNone, true},
};

const Option* FindOption(const char* name) {
    for (const Option& o : kOptions) {
        if (std::strcmp(o.name, name) == 0) return &o;
    }
    return nullptr;
}

const char* ValueHint(Value value) {
    switch (value) {
        case Value::kText: return "a path";
        case Value::kInt: return "a whole number";
        case Value::kSize: return "WxH, e.g. 1920x1080";
        case Value::kKind: return "borderless or exclusive";
        default: return "a value";
    }
}

// Edit distance (insertions, deletions, substitutions), for the "did you mean" of an unknown option.
size_t Distance(const std::string& a, const std::string& b) {
    std::vector<size_t> row(b.size() + 1);
    for (size_t j = 0; j <= b.size(); ++j) row[j] = j;
    for (size_t i = 1; i <= a.size(); ++i) {
        size_t diagonal = row[0];
        row[0] = i;
        for (size_t j = 1; j <= b.size(); ++j) {
            const size_t above = row[j];
            row[j] = std::min({row[j] + 1, row[j - 1] + 1, diagonal + (a[i - 1] == b[j - 1] ? 0 : 1)});
            diagonal = above;
        }
    }
    return row[b.size()];
}

// A word of the command line that is no option of the table (with `value`, the word after an unknown option that is no
// option itself: taken as its value, one warning for both): the warning, with the option meant when one is close
// (dashes, case and an "=value" set aside: "-msaa", "MSAA", "--msaa=8" and "--mssa" all point at --msaa).
void WarnUnknown(const char* word, const char* value) {
    const std::string text(word);
    const size_t equals = text.find('=');
    std::string bare = text.substr(0, equals);
    bare.erase(0, std::min(bare.find_first_not_of('-'), bare.size()));
    for (char& ch : bare) ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    const Option* exact = bare.empty() ? nullptr : FindOption(("--" + bare).c_str());
    if (exact != nullptr && equals != std::string::npos) {
        CONFIG_WARN("config: WARNING: '%s': write it as %s %s (a space, not '='); ignored", word, exact->name,
                    text.substr(equals + 1).c_str());
        return;
    }
    const Option* closest = exact;
    if (closest == nullptr && bare.size() >= 3) {
        size_t best = bare.size() >= 6 ? 3 : 2;  // (at most 2 edits away, 1 for a short word)
        for (const Option& o : kOptions) {
            const size_t d = Distance(bare, o.name + 2);
            if (d < best) {
                best = d;
                closest = &o;
            }
        }
    }
    std::string hint;
    if (closest != nullptr) hint = std::string(" (did you mean ") + closest->name + "?)";
    if (word[0] == '-' && value != nullptr) {
        CONFIG_WARN("config: WARNING: unknown option '%s %s'; ignored%s", word, value, hint.c_str());
    } else if (word[0] == '-') {
        CONFIG_WARN("config: WARNING: unknown option '%s'; ignored%s", word, hint.c_str());
    }
    else {
        CONFIG_WARN("config: WARNING: '%s' is not an option (they start with --); ignored%s", word, hint.c_str());
    }
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
    g_warnings = 0;
#ifdef __EMSCRIPTEN__
    c.showFps = true;
#endif
    if (!ReadIni("dotd.ini", c) && argc > 0) {
        ReadIni(ExeDirectory(argv[0]) + "dotd.ini", c);
    }
    if (const char* env = std::getenv("DOTD_USRDIR")) {
        if (c.usrdir.empty()) c.usrdir = env;
    }
    // DOTD_RESOLUTION=WxH: over dotd.ini's resolution, under --resolution (the test programs, the web page's address).
    if (const char* env = std::getenv("DOTD_RESOLUTION")) ApplySize("DOTD_RESOLUTION", env, &c.renderWidth, &c.renderHeight);
    if (const char* env = std::getenv("DOTD_MSAA")) c.msaa = NormalizeMsaa("DOTD_MSAA", std::atoi(env));  // (under the command line)
    if (const char* env = std::getenv("DOTD_FXAA")) c.fxaa = std::atoi(env) != 0;
    if (const char* env = std::getenv("DOTD_ALPHA_TO_COVERAGE")) c.alphaToCoverage = std::atoi(env) != 0;
    for (int i = 1; i < argc; ++i) {
        const char* a = argv[i];
        const Option* option = FindOption(a);
        if (option == nullptr) {
            // (an unknown option's value goes with it: "--mssa 4", the web page's "?foo=1" as "--foo 1")
            const bool withValue = a[0] == '-' && i + 1 < argc && argv[i + 1][0] != '-';
            WarnUnknown(a, withValue ? argv[++i] : nullptr);
            continue;
        }
        // Its value: the next word, unless that is the next option (a value never starts with "--").
        const char* next = i + 1 < argc ? argv[i + 1] : nullptr;
        const char* value = nullptr;
        if (option->value == Value::kOptional01) {
            if (next != nullptr && (std::strcmp(next, "0") == 0 || std::strcmp(next, "1") == 0)) value = argv[++i];
        } else if (option->value == Value::kOptionalKind) {
            if (next != nullptr && (std::strcmp(next, "borderless") == 0 || std::strcmp(next, "exclusive") == 0)) value = argv[++i];
        } else if (option->value != Value::kNone) {
            if (next == nullptr || std::strncmp(next, "--", 2) == 0) {
                CONFIG_WARN("config: WARNING: %s needs a value after it (%s); ignored", a, ValueHint(option->value));
                continue;
            }
            value = argv[++i];
        }
        int number = 0;
        if (option->main) {  // (main.cpp reads it; only its number is checked here)
            if (option->value == Value::kInt) ParseInt(a, value, &number);
            continue;
        }
        if (std::strcmp(a, "--usrdir") == 0) c.usrdir = value;
        else if (std::strcmp(a, "--lang") == 0) {
            if (ParseInt(a, value, &number)) c.language = number;
        } else if (std::strcmp(a, "--fullscreen") == 0) {
            c.fullscreen = true;  // (an optional kind after it: --fullscreen exclusive)
            if (value != nullptr) ApplyFullscreenKind(a, value, &c.exclusiveFullscreen);
        } else if (std::strcmp(a, "--fullscreen-mode") == 0) {
            ApplyFullscreenKind(a, value, &c.exclusiveFullscreen);
        } else if (std::strcmp(a, "--windowed") == 0) {
            c.fullscreen = false;
        } else if (std::strcmp(a, "--msaa") == 0) {
            if (ParseInt(a, value, &number)) c.msaa = NormalizeMsaa(a, number);
        } else if (std::strcmp(a, "--fxaa") == 0) {
            c.fxaa = value == nullptr || value[0] == '1';
        } else if (std::strcmp(a, "--alpha-to-coverage") == 0) {
            c.alphaToCoverage = value == nullptr || value[0] == '1';
        } else if (std::strcmp(a, "--novsync") == 0) {
            c.vsync = false;
        } else if (std::strcmp(a, "--frame-rate") == 0) {
            if (ParseInt(a, value, &number)) c.frameRate = number;
        } else if (std::strcmp(a, "--fps") == 0) {
            if (ParseInt(a, value, &number)) c.fps = number;
        } else if (std::strcmp(a, "--resolution") == 0) {
            ApplySize(a, value, &c.renderWidth, &c.renderHeight);
        } else if (std::strcmp(a, "--window") == 0) {
            int w = 0, h = 0;
            if (ApplySize(a, value, &w, &h) && w != 0) {
                c.windowWidth = w;
                c.windowHeight = h;
                c.windowSizeSet = true;
            }
        } else if (std::strcmp(a, "--show-fps") == 0) {
            c.showFps = value == nullptr || value[0] == '1';
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
    // --resolution without a window size: the window has the picture's size (sdl::Init makes it fit the display).
    if (c.renderWidth != 0 && !c.windowSizeSet) {
        c.windowWidth = c.renderWidth;
        c.windowHeight = c.renderHeight;
    }
    if (c.renderWidth != 0) DOTD_LOG("config: resolution %dx%d", c.renderWidth, c.renderHeight);
#ifdef __EMSCRIPTEN__
    if (c.msaa != 0 || c.fxaa) DOTD_LOG("config: MSAA %d, FXAA %d", c.msaa, c.fxaa ? 1 : 0);
#else
    if (c.msaa != 0 || c.fxaa) DOTD_LOG("config: MSAA %d, FXAA %d (F3 / Shift+F3 switch them)", c.msaa, c.fxaa ? 1 : 0);
#endif
    if (c.fullscreen || c.exclusiveFullscreen) {
        DOTD_LOG("config: %s, %s full screen (F11 switches it, Shift+F11 the kind)", c.fullscreen ? "full screen" : "windowed",
                 c.exclusiveFullscreen ? "exclusive" : "borderless");
    }
    // normalise: forward slashes, no trailing separator
    for (char& ch : c.usrdir) {
        if (ch == '\\') ch = '/';
    }
    while (!c.usrdir.empty() && c.usrdir.back() == '/') c.usrdir.pop_back();
    if (g_warnings > 0) {
        DOTD_LOG("config: WARNING: %d configuration warning(s) above", g_warnings);
    }
    g_config = c;
    out = c;
    return true;
}

const Config& GetConfig() { return g_config; }
Config& MutableConfig() { return g_config; }

}  // namespace dotd::platform
