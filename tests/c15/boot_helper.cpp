// boot_helper.cpp - see boot_helper.h. The setup is boot_test's (GameMain without its loop).
#include "boot_helper.h"

#include <cstdlib>

#include "Spyro2008/logic/CKS08GameManager.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/CoreSingletons.h"
#include "k2000/misc/Engine.h"
#include "k2000/io/KFileSystem.h"
#include "platform/cell/sys_thread.h"
#include "platform/cell/sys_time.h"
#include "platform/config.h"

namespace c15 {

int g_failures = 0;

namespace {
int64_t g_now = 1000000;  // microseconds
uint32_t g_frames = 0;
int64_t FakeTime() { return g_now; }
}  // namespace

bool BootToFrontEnd() {
    dotd::platform::Config config;
    dotd::platform::LoadConfig(0, nullptr, config);
    if (config.usrdir.empty()) return false;
    dotd::platform::SetSystemTimeSource(&FakeTime);
    // A load is seen finished at the same frame in every run (the frame clock above is the frame count, so the
    // absolute times and the float frame dt after a load depend on it).
    // DOTD_ASYNC_REQUESTS=1 keeps the asynchronous loads of dotd.exe (to reproduce timing-dependent bugs).
    dotd::platform::SetDeterministicRequests(std::getenv("DOTD_ASYNC_REQUESTS") == nullptr);
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
    return g_pCKGameLoop->m_mode == CKGameLoop::kModeLevel;
}

void ParkFrontEndSequence() {
    static_cast<CKS08GameManager*>(g_pEngine->m_gameManager)->m_gameState.Switch(0xff);
}

void RunFrame() {
    g_now += 16667;
    Run();
    ++g_frames;
}

uint32_t FrameCount() { return g_frames; }

void Shutdown() { Cleanup(); }

}  // namespace c15
