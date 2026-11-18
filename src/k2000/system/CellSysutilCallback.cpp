// CellSysutilCallback.cpp - reconstructed original translation unit 0x253790-0x253a00 (GAME_TOC1, main_toc1), 2 functions, 2 live.
// Primary owner: CellSysutilCallback (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x253790  CellSysutilCallback
//   [x] 0x253870  main
#include "k2000/system/CellSysutilCallback.h"

#include "k2000/io/KFileSystem.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/CoreSingletons.h"
#include "k2000/misc/Engine.h"
#include "platform/cell/sysmodule.h"
#include "platform/cell/sysutil.h"
#include "platform/frame_loop.h"

uint8_t g_exitGameRequested = 0;  // 0x00ceac58
uint8_t g_systemMenuOpen = 0;     // 0x00ceac59
uint8_t g_bgmPlaybackActive = 0;  // 0x00ceac5a
int32_t g_enterButtonAssign = 1;  // 0x00c4026c
int32_t g_padRumbleEnabled = 0;   // 0x00cea850

namespace {
constexpr uint16_t kModuleL10n = 0x1e;          // CELL_SYSMODULE_L10N
constexpr uint16_t kModuleAvconfExt = 0x31;     // CELL_SYSMODULE_SYSUTIL_AVCONF_EXT

// One pass of main's loop (0x253870): false when Run() says the game is over.
bool GameMain_Frame() {
    if (g_exitGameRequested != 0) g_pEngine->m_gameLoop->RequestExit();
    return (Run() & 0xff) != 0;
}

// main's tail, after the loop.
void GameMain_End() {
    Cleanup();
    cellSysmoduleUnloadModule(kModuleAvconfExt);
    cellSysmoduleUnloadModule(kModuleL10n);
    cellSysutilUnregisterCallback(0);
}
}  // namespace

// 0x00253790 CellSysutilCallback
void GameSysutilCallback(uint64_t status, uint64_t /*param*/, void* /*userdata*/) {
    switch (status) {
    case CELL_SYSUTIL_REQUEST_EXITGAME:
        g_exitGameRequested = 1;
        break;
    case CELL_SYSUTIL_SYSTEM_MENU_OPEN:
        g_systemMenuOpen = 1;
        break;
    case CELL_SYSUTIL_SYSTEM_MENU_CLOSE:
        g_systemMenuOpen = 0;
        cellSysutilGetSystemParamInt(CELL_SYSUTIL_SYSTEMPARAM_ID_PAD_RUMBLE, &g_padRumbleEnabled);
        break;
    case CELL_SYSUTIL_BGMPLAYBACK_PLAY:
        g_bgmPlaybackActive = 1;
        break;
    case CELL_SYSUTIL_BGMPLAYBACK_STOP:
        g_bgmPlaybackActive = 0;
        break;
    default:
        break;
    }
}

// 0x00253870 main
int32_t GameMain(int32_t argc, const char* const* argv) {
    cellSysutilRegisterCallback(0, &GameSysutilCallback, nullptr);
    cellSysmoduleLoadModule(kModuleL10n);
    cellSysmoduleLoadModule(kModuleAvconfExt);
    cellSysutilGetSystemParamInt(CELL_SYSUTIL_SYSTEMPARAM_ID_ENTER_BUTTON_ASSIGN, &g_enterButtonAssign);
    cellSysutilEnableBgmPlayback();
    cellSysutilGetSystemParamInt(CELL_SYSUTIL_SYSTEMPARAM_ID_PAD_RUMBLE, &g_padRumbleEnabled);
    CoreSingletons_EnsureCreated();
    g_pEngine->m_fileSystem->SetExecutablePath(argv[0]);  // CopyString4Offset(fs, argv[0])
    HandleParameters(argc, argv);
    AppConfig* config = Engine_GetBootConfigStruct();
    config->width = 640;
    config->unk20 = 0;
    config->height = 480;
    config->flag14 = 1;
    config->bitsPerPixel = 0;
    config->unk18 = 0;
    if (Main_InitGame() != 0) {
        // The original: for (;;) { if (g_exitGameRequested != 0) RequestExit(); if ((Run() & 0xff) == 0) break; }
        // The loop is the platform's (platform/frame_loop.h): a native build runs it as written, the web build
        // one pass per browser frame (there RunFrames does not return, and GameMain_End runs after the last pass).
        dotd::platform::RunFrames(&GameMain_Frame, &GameMain_End);
        return 0;
    }
    GameMain_End();
    return 0;
}
