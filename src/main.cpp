// main.cpp - process entry: sets up the platform (the part of the PS3 the game expects to exist),
// registers the classes (the original does it from static constructors), then runs the game's own
// main (0x253870, k2000/system/CellSysutilCallback.cpp).
//
//   dotd [--usrdir PATH]          boot the game (checkpoint C1.1: boot skeleton, stand-in subsystems)
//   dotd --frames N               stop after N frames through the game's exit path, log the frame rate
//   dotd --frame-rate N           pace to N fps instead of 60 (0 = uncapped; experiments only: per-update systems speed up)
//   F2 (while it runs)            the frame rate between 60 and no cap (the same switch as --fps 0)
//   dotd --fps N                  run at N fps (0 = no cap) with the 60 Hz timing calculation (platform/fps.h), so the
//                                 game's timings stay those of 60 fps; dotd.ini: fps = N
//   dotd --headless               no window (boot logic only)
//   dotd --no-shader-list         no shader variant list (platform/gfx/cg_program.h): every program built at its first draw
//   dotd --test-pattern           the C1.0 window/input test pattern instead of the game
//   dotd --selftest-fs            read GAME.KP3 and list USRDIR through the cellFs shim, then exit
//   dotd --check-game             check the configured USRDIR (game files, the shader sources from EBOOT.elf or the
//                                 disc's EBOOT.BIN) and that this build plays videos, then exit (0 = ready; setup.ps1)
#include <SDL3/SDL_main.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "k2000/misc/ClassRegistry.h"
#include "k2000/system/CellSysutilCallback.h"
#include "platform/cell/cell_errors.h"
#include "platform/cell/fs.h"
#include "platform/cell/pad.h"
#include "platform/cell/sysutil.h"
#include "platform/config.h"
#include "platform/gfx/cg_program.h"
#include "platform/gfx/device.h"
#include "platform/log.h"
#include "platform/sdl/app.h"
#include "platform/video/bink.h"
#ifdef __EMSCRIPTEN__
#include "platform/web/web.h"
#endif

namespace {

bool g_windowOpen = false;

// --check-game: what a player's install needs, checked without opening a window. The lines start with "ok" or "error".
int CheckGame(const dotd::platform::Config& cfg) {
    int problems = 0;
    if (cfg.usrdir.empty()) {
        std::printf("error: no usrdir configured (dotd.ini usrdir=... or --usrdir PATH)\n");
        return 1;
    }
    std::printf("usrdir: %s\n", cfg.usrdir.c_str());
    for (const char* name : {"GAME.KP3", "00GLC.KP3", "LVL000", "MOVIE"}) {
        CellFsStat st;
        const std::string path = std::string("/dev_bdvd/PS3_GAME/USRDIR/") + name;
        if (cellFsStat(path.c_str(), &st) == CELL_OK) continue;
        std::printf("error: %s is missing from the game folder\n", name);
        ++problems;
    }
    const std::string eboot = dotd::gfx::cg::GameExecutablePath(cfg.usrdir);
    std::string error;
    if (dotd::gfx::cg::InitSources(eboot.c_str(), &error)) {
        std::printf("ok: shader sources read from %s\n", eboot.substr(eboot.find_last_of('/') + 1).c_str());
    } else {
        std::printf("error: shader sources: %s\n", error.c_str());
        ++problems;
    }
    if (dotd::video::HasBinkDecoder()) {
        std::printf("ok: video decoder built in\n");
    } else {
        std::printf("error: this build has no video decoder (FFmpeg source missing at configure time)\n");
        ++problems;
    }
    if (problems == 0) std::printf("ok: ready to play\n");
    std::fflush(stdout);
    return problems == 0 ? 0 : 1;
}

int SelfTestFs() {
    const char* path = "/dev_bdvd/PS3_GAME/USRDIR/GAME.KP3";
    CellFsStat st;
    if (cellFsStat(path, &st) != CELL_OK) {
        DOTD_LOG("selftest: cellFsStat(%s) failed; set --usrdir or DOTD_USRDIR", path);
        return 77;  // ctest: skipped
    }
    int32_t fd = -1;
    if (cellFsOpen(path, CELL_FS_O_RDONLY, &fd, nullptr, 0) != CELL_OK) {
        DOTD_LOG("selftest: cellFsOpen failed");
        return 1;
    }
    uint8_t head[16] = {};
    uint64_t got = 0;
    cellFsRead(fd, head, sizeof(head), &got);
    uint64_t end = 0;
    cellFsLseek(fd, 0, CELL_FS_SEEK_END, &end);
    cellFsClose(fd);
    DOTD_LOG("selftest: GAME.KP3 %llu bytes (stat %llu), first bytes %02x %02x %02x %02x %02x %02x %02x %02x",
             static_cast<unsigned long long>(end), static_cast<unsigned long long>(st.size), head[0], head[1], head[2],
             head[3], head[4], head[5], head[6], head[7]);
    if (got != sizeof(head) || end != st.size) return 1;

    int32_t dir = -1;
    if (cellFsOpendir("/dev_bdvd/PS3_GAME/USRDIR", &dir) != CELL_OK) return 1;
    CellFsDirectoryEntry entries[32];
    uint32_t count = 0;
    int total = 0;
    do {
        cellFsGetDirectoryEntries(dir, entries, sizeof(entries), &count);
        for (uint32_t i = 0; i < count; ++i) {
            if (total < 12) DOTD_LOG("selftest:   %s%s", entries[i].entry_name.d_name,
                                     entries[i].entry_name.d_type == CELL_FS_TYPE_DIRECTORY ? "/" : "");
            ++total;
        }
    } while (count > 0);
    cellFsClosedir(dir);
    DOTD_LOG("selftest: USRDIR has %d entries (including . and ..)", total);
    return total > 2 ? 0 : 1;
}

// ---- C1.0 test pattern -------------------------------------------------------------------------
bool g_testExit = false;

void OnTestSysutil(uint64_t status, uint64_t, void*) {
    if (status == CELL_SYSUTIL_REQUEST_EXITGAME) g_testExit = true;
}

void DescribePad(const CellPadData& d, char* out, size_t size) {
    static const char* kD1[8] = {"SELECT", "L3", "R3", "START", "UP", "RIGHT", "DOWN", "LEFT"};
    static const char* kD2[8] = {"L2", "R2", "L1", "R1", "TRIANGLE", "CIRCLE", "CROSS", "SQUARE"};
    out[0] = 0;
    for (int b = 0; b < 8; ++b) {
        if (d.button[2] & (1 << b)) { std::strncat(out, kD1[b], size - std::strlen(out) - 1); std::strncat(out, " ", size - std::strlen(out) - 1); }
        if (d.button[3] & (1 << b)) { std::strncat(out, kD2[b], size - std::strlen(out) - 1); std::strncat(out, " ", size - std::strlen(out) - 1); }
    }
}

int RunTestPattern() {
    cellSysutilRegisterCallback(1, OnTestSysutil, nullptr);
    cellPadInit(7);
    std::vector<uint32_t> checker(64 * 64);
    for (int y = 0; y < 64; ++y) {
        for (int x = 0; x < 64; ++x) checker[y * 64 + x] = ((x / 8 + y / 8) & 1) ? 0xff3a2a20u : 0xff6a4a30u;
    }
    const uint32_t checkerTex = dotd::gfx::CreateTextureRGBA8(64, 64, checker.data(), false);
    float px = 640.0f, py = 360.0f;
    uint16_t last[24] = {};
    while (!g_testExit) {
        cellSysutilCheckCallback();
        CellPadData pad;
        std::memset(&pad, 0, sizeof(pad));
        if (cellPadGetData(0, &pad) == CELL_OK && pad.len > 0) {
            if (pad.button[2] != last[2] || pad.button[3] != last[3]) {
                char names[256];
                DescribePad(pad, names, sizeof(names));
                DOTD_LOG("pad0: d1 %02x d2 %02x  %s", pad.button[2], pad.button[3], names);
            }
            std::memcpy(last, pad.button, sizeof(last));
        }
        const float lx = (static_cast<int>(last[6]) - 128) / 128.0f;
        const float ly = (static_cast<int>(last[7]) - 128) / 128.0f;
        px += (lx > 0.15f || lx < -0.15f) ? lx * 8.0f : 0.0f;
        py += (ly > 0.15f || ly < -0.15f) ? ly * 8.0f : 0.0f;
        dotd::gfx::BeginFrame();
        dotd::gfx::Clear(0.05f, 0.03f, 0.10f, 1.0f);
        dotd::gfx::DrawQuad(checkerTex, 160.0f, 90.0f, 1120.0f, 630.0f, 0xffffffffu);
        const bool cross = (last[3] & CELL_PAD_CTRL_CROSS) != 0;
        dotd::gfx::DrawQuad(0, px - 40.0f, py - 40.0f, px + 40.0f, py + 40.0f, cross ? 0x40ff60ffu : 0xffb020ffu);
        dotd::gfx::EndFrame();
    }
    dotd::gfx::DestroyTexture(checkerTex);
    cellPadEnd();
    return 0;
}

// Runs at normal return and at the game's exit(0) (CKGameLoop_ShutdownAndExit).
void OnProcessExit() {
    if (!g_windowOpen) return;
    dotd::platform::sdl::LogFrameStats();
    dotd::gfx::Shutdown();
    dotd::platform::sdl::Shutdown();
    g_windowOpen = false;
}

}  // namespace

int main(int argc, char** argv) {
    dotd::platform::Config cfg;
    dotd::platform::LoadConfig(argc, argv, cfg);
    long frameLimit = 0;
    bool headless = false;
    bool testPattern = false;
    bool noShaderList = false;
    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "--selftest-fs") == 0) return SelfTestFs();
        if (std::strcmp(argv[i], "--check-game") == 0) return CheckGame(cfg);
        if (std::strcmp(argv[i], "--frames") == 0 && i + 1 < argc) frameLimit = std::atol(argv[++i]);
        if (std::strcmp(argv[i], "--headless") == 0) headless = true;
        if (std::strcmp(argv[i], "--test-pattern") == 0) testPattern = true;
        if (std::strcmp(argv[i], "--no-shader-list") == 0) noShaderList = true;
    }
#ifdef __EMSCRIPTEN__
    // The web build: the game's files are served from the user's USRDIR by web/serve.py and appear under
    // /usrdir (platform/web/hostfs_web.cpp).
    if (cfg.usrdir.empty()) {
        cfg.usrdir = "/usrdir";
        dotd::platform::MutableConfig().usrdir = cfg.usrdir;
    }
    if (!dotd::platform::web::InitHostFs(cfg.usrdir)) {
        DOTD_LOG("main: the server lists no game files (start web/serve.py with --usrdir PATH)");
        return 1;
    }
#endif
    if (cfg.usrdir.empty()) DOTD_LOG("main: no usrdir configured (dotd.ini usrdir=... or --usrdir PATH)");

    if (!headless) {
        if (!dotd::platform::sdl::Init(cfg)) return 1;
        if (!dotd::gfx::Init(1280, 720)) return 1;
        g_windowOpen = true;
        // The shader variant list (platform/gfx/cg_program.h): the programs a level used before are built while it
        // loads. --no-shader-list or DOTD_SHADER_LIST=off: every program at its first draw, as without the list.
        if (!noShaderList) dotd::gfx::cg::EnableVariantList(nullptr);
    }
    std::atexit(OnProcessExit);
    dotd::platform::SetFrameLimit(frameLimit);
    if (testPattern) return RunTestPattern();

    RegisterAllClasses();
    // RPCS3 passes the EBOOT's path as argv[0]; the game stores it and parses the rest (none here).
    const char* const gameArgv[] = {"/dev_bdvd/PS3_GAME/USRDIR/EBOOT.BIN"};
    return GameMain(1, gameArgv);
}
