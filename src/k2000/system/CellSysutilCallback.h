// CellSysutilCallback.h - the process entry of the game (original unit CellSysutilCallback.cpp,
// 0x253790-0x253a00): the system-utility callback and main.
#pragma once
#include <cstdint>

// 0x00253870 main. Returns 0. The host's main (src/main.cpp) sets up the platform and then calls it.
int32_t GameMain(int32_t argc, const char* const* argv);

// 0x00253790 CellSysutilCallback (renamed: the SDK already uses the name for the callback type).
void GameSysutilCallback(uint64_t status, uint64_t param, void* userdata);

// Flags the callback sets (0x00ceac58..0x00ceac5a).
extern uint8_t g_exitGameRequested;  // 0x00ceac58 CELL_SYSUTIL_REQUEST_EXITGAME
extern uint8_t g_systemMenuOpen;     // 0x00ceac59 between SYSTEM_MENU_OPEN and _CLOSE
extern uint8_t g_bgmPlaybackActive;  // 0x00ceac5a between BGMPLAYBACK_PLAY and _STOP
// 0x00c4026c (.data, initial 1): CELL_SYSUTIL_SYSTEMPARAM_ID_ENTER_BUTTON_ASSIGN (1 = cross)
extern int32_t g_enterButtonAssign;
// 0x00cea850: CELL_SYSUTIL_SYSTEMPARAM_ID_PAD_RUMBLE (re-read when the system menu closes)
extern int32_t g_padRumbleEnabled;
