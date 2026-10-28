// sysutil.h - cellSysutil as the game uses it: system callbacks, system parameters, BGM status.
// Callbacks run on the thread that calls cellSysutilCheckCallback, as on the PS3.
#pragma once
#include <cstdint>

enum : uint64_t {
    CELL_SYSUTIL_REQUEST_EXITGAME = 0x0101,
    CELL_SYSUTIL_DRAWING_BEGIN = 0x0121,
    CELL_SYSUTIL_DRAWING_END = 0x0122,
    CELL_SYSUTIL_SYSTEM_MENU_OPEN = 0x0131,
    CELL_SYSUTIL_SYSTEM_MENU_CLOSE = 0x0132,
    CELL_SYSUTIL_BGMPLAYBACK_PLAY = 0x0141,
    CELL_SYSUTIL_BGMPLAYBACK_STOP = 0x0142,
};

enum : int32_t {
    CELL_SYSUTIL_SYSTEMPARAM_ID_LANG = 0x0111,
    CELL_SYSUTIL_SYSTEMPARAM_ID_ENTER_BUTTON_ASSIGN = 0x0112,
    CELL_SYSUTIL_SYSTEMPARAM_ID_NICKNAME = 0x0113,
    CELL_SYSUTIL_SYSTEMPARAM_ID_PAD_RUMBLE = 0x0152,
};

enum : uint8_t {
    CELL_SYSUTIL_BGMPLAYBACK_STATUS_PLAY = 0,
    CELL_SYSUTIL_BGMPLAYBACK_STATUS_STOP = 1,
    CELL_SYSUTIL_BGMPLAYBACK_STATUS_ENABLE = 0,
    CELL_SYSUTIL_BGMPLAYBACK_STATUS_DISABLE = 1,
};

typedef void (*CellSysutilCallback)(uint64_t status, uint64_t param, void* userdata);

struct CellSysutilBgmPlaybackStatus {
    uint8_t playerState;
    uint8_t enableState;
    char contentId[16];
    uint8_t currentFadeRatio;
    char reserved[13];
};
static_assert(sizeof(CellSysutilBgmPlaybackStatus) == 32, "PS3 layout");

int32_t cellSysutilRegisterCallback(int32_t slot, CellSysutilCallback func, void* userdata);
int32_t cellSysutilUnregisterCallback(int32_t slot);
int32_t cellSysutilCheckCallback();
int32_t cellSysutilGetSystemParamInt(int32_t id, int32_t* value);
int32_t cellSysutilEnableBgmPlayback();
int32_t cellSysutilDisableBgmPlayback();
int32_t cellSysutilGetBgmPlaybackStatus(CellSysutilBgmPlaybackStatus* status);

namespace dotd::platform {
// Thread-safe: queue a system event for the next cellSysutilCheckCallback (used by the SDL layer).
void PostSysutilEvent(uint64_t status, uint64_t param);
// Post CELL_SYSUTIL_REQUEST_EXITGAME on the n-th cellSysutilCheckCallback (the game polls once per
// frame), so a run can stop by itself through the game's own exit path. 0 = no limit.
void SetFrameLimit(long frames);
long SysutilCheckCount();
}
