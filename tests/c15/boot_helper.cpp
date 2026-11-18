// boot_helper.cpp - see boot_helper.h. The setup is boot_test's (GameMain without its loop).
#include "boot_helper.h"

#include <cstdlib>
#include <filesystem>
#include <string>
#include <system_error>
#ifdef _WIN32
#include <process.h>
#define DOTD_GETPID _getpid
#else
#include <unistd.h>
#define DOTD_GETPID getpid
#endif

#include "Spyro2008/logic/CKS08GameManager.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/CoreSingletons.h"
#include "k2000/misc/Engine.h"
#include "k2000/io/KFileSystem.h"
#include "platform/cell/savedata.h"
#include "platform/cell/sys_thread.h"
#include "platform/cell/sys_time.h"
#include "platform/config.h"
#include "platform/debug_symbols.h"
#include "platform/fps.h"

namespace c15 {

int g_failures = 0;

namespace {
int64_t g_now = 1000000;  // microseconds
uint32_t g_frames = 0;
int64_t FakeTime() { return g_now; }

// DOTD_TEST_FPS=N (frame-rate measurements, never in ctest): after the boot the fake clock steps 1/N s per frame
// (the fraction carried, so N frames are exactly one second) and the 60 Hz timing calculation of --fps N is on;
// N = 0 stands for an uncapped run: irregular frames of 1..7 ms (a fixed pseudo-random sequence, about 250 fps).
// DOTD_TEST_FPS_RAW=1 leaves the calculation off (what --frame-rate N alone does).
int g_testFps = 60;
uint32_t g_jitter = 12345;
int64_t g_stepStart = 0;
uint64_t g_stepFrames = 0;
void AdvanceClock() {
    if (g_testFps == 60) {
        g_now += 16667;
        return;
    }
    ++g_stepFrames;
    if (g_testFps == 0) {
        g_jitter = g_jitter * 1103515245u + 12345u;
        g_now += 1000 + static_cast<int64_t>((g_jitter >> 8) % 6001u);
        return;
    }
    g_now = g_stepStart + static_cast<int64_t>((g_stepFrames * 1000000ull + static_cast<uint64_t>(g_testFps) / 2) /
                                               static_cast<uint64_t>(g_testFps));
}
}  // namespace

int TestFps() { return g_testFps; }
int64_t NowMicros() { return g_now; }

bool BootToFrontEnd() {
    dotd::platform::debugsym::InstallCrashReport();
    dotd::platform::Config config;
    dotd::platform::LoadConfig(0, nullptr, config);
    if (config.usrdir.empty()) return false;
    dotd::platform::SetSystemTimeSource(&FakeTime);
    // A load is seen finished at the same frame in every run (the frame clock above is the frame count, so the
    // absolute times and the float frame dt after a load depend on it).
    // DOTD_ASYNC_REQUESTS=1 keeps the asynchronous loads of dotd.exe (to reproduce timing-dependent bugs).
    dotd::platform::SetDeterministicRequests(std::getenv("DOTD_ASYNC_REQUESTS") == nullptr);
    // Tests and replays never save into the user's profile: the save data goes to a fresh temporary folder of this
    // process unless DOTD_SAVEDATA_DIR names one.
    if (std::getenv("DOTD_SAVEDATA_DIR") == nullptr) {
        const std::filesystem::path root = std::filesystem::temp_directory_path() /
                                           ("dotd-test-savedata-" + std::to_string(static_cast<long long>(DOTD_GETPID())));
        std::error_code ec;
        std::filesystem::remove_all(root, ec);
        dotd::platform::SetSaveDataRoot(root.string().c_str());
    }
    RegisterAllClasses();
    CoreSingletons_EnsureCreated();
    g_pEngine->m_fileSystem->SetExecutablePath("/dev_bdvd/PS3_GAME/USRDIR/EBOOT.BIN");
    const char* const argv[] = {"/dev_bdvd/PS3_GAME/USRDIR/EBOOT.BIN"};
    HandleParameters(1, argv);
    // GameMain's start-up config (0x253870): the renderer sizes its rasters from the video mode.
    AppConfig* appConfig = Engine_GetBootConfigStruct();
    appConfig->width = 640;
    appConfig->unk20 = 0;
    appConfig->height = 480;
    appConfig->flag14 = 1;
    appConfig->bitsPerPixel = 0;
    appConfig->unk18 = 0;
    if (Main_InitGame() != 1) return false;
    for (int i = 0; i < 600 && g_pCKGameLoop->m_mode != CKGameLoop::kModeLevel; ++i) {
        g_now += 16667;
        Run();
    }
    g_frames = 0;
    if (const char* fps = std::getenv("DOTD_TEST_FPS"); fps != nullptr && std::atoi(fps) >= 0 && std::atoi(fps) != 60) {
        g_testFps = std::atoi(fps);
        g_stepStart = g_now;
        g_stepFrames = 0;
        dotd::fps::Configure(std::getenv("DOTD_TEST_FPS_RAW") == nullptr);
        std::printf("boot_helper: fake clock at %d fps, 60 Hz timing calculation %s\n", g_testFps,
                    dotd::fps::Unlocked() ? "on" : "off");
    }
    return g_pCKGameLoop->m_mode == CKGameLoop::kModeLevel;
}

void ParkFrontEndSequence() {
    static_cast<CKS08GameManager*>(g_pEngine->m_gameManager)->m_gameState.Switch(0xff);
}

void RunFrame() {
    AdvanceClock();
    Run();
    ++g_frames;
}

uint32_t FrameCount() { return g_frames; }

// The game reaches Cleanup only from the quit mode (10), which mode 9 enters after CKGameLoop_StopAll_maybe (every
// module stopped: the sound voices released from their instances); ShutdownSubsystems relies on it (the sound
// manager's DestroyModule releases the voices still attached, whose sounds UnloadGameObjects has freed). The tests stop
// the loop the same way before the Cleanup.
void Shutdown() {
    g_pCKGameLoop->Stop();  // vt+0x68
    Cleanup();
}

}  // namespace c15
