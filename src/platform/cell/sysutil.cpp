#include "platform/cell/sysutil.h"

#include <cstring>
#include <deque>
#include <mutex>
#include <utility>

#include "platform/cell/cell_errors.h"
#include "platform/cell/msgdialog.h"
#include "platform/config.h"
#include "platform/log.h"

namespace {
struct Slot {
    CellSysutilCallback func = nullptr;
    void* userdata = nullptr;
};
std::mutex g_mutex;
Slot g_slots[4];
std::deque<std::pair<uint64_t, uint64_t>> g_events;
bool g_bgmEnabled = true;
long g_frameLimit = 0;  // SetFrameLimit: post EXITGAME on this cellSysutilCheckCallback call (0 = never)
long g_checkCount = 0;
}  // namespace

namespace dotd::platform {
void PostSysutilEvent(uint64_t status, uint64_t param) {
    std::lock_guard<std::mutex> lock(g_mutex);
    g_events.emplace_back(status, param);
}

void SetFrameLimit(long frames) {
    std::lock_guard<std::mutex> lock(g_mutex);
    g_frameLimit = frames;
    g_checkCount = 0;
}

long SysutilCheckCount() {
    std::lock_guard<std::mutex> lock(g_mutex);
    return g_checkCount;
}
}  // namespace dotd::platform

int32_t cellSysutilRegisterCallback(int32_t slot, CellSysutilCallback func, void* userdata) {
    if (slot < 0 || slot > 3) return CellError(CELL_SYSUTIL_ERROR_VALUE);
    std::lock_guard<std::mutex> lock(g_mutex);
    g_slots[slot].func = func;
    g_slots[slot].userdata = userdata;
    return CELL_OK;
}

int32_t cellSysutilUnregisterCallback(int32_t slot) {
    if (slot < 0 || slot > 3) return CellError(CELL_SYSUTIL_ERROR_VALUE);
    std::lock_guard<std::mutex> lock(g_mutex);
    g_slots[slot] = Slot();
    return CELL_OK;
}

int32_t cellSysutilCheckCallback() {
    {
        // The game calls this once per frame, which makes it the frame boundary for --frames.
        std::lock_guard<std::mutex> lock(g_mutex);
        ++g_checkCount;
        if (g_frameLimit > 0 && g_checkCount == g_frameLimit) {
            g_events.emplace_back(CELL_SYSUTIL_REQUEST_EXITGAME, 0);
            DOTD_LOG("sysutil: frame limit %ld reached, requesting exit", g_frameLimit);
        }
    }
    // Deliver every queued event to every registered slot, outside the lock (callbacks may post).
    for (;;) {
        std::pair<uint64_t, uint64_t> ev;
        Slot slots[4];
        {
            std::lock_guard<std::mutex> lock(g_mutex);
            if (g_events.empty()) break;
            ev = g_events.front();
            g_events.pop_front();
            for (int i = 0; i < 4; ++i) slots[i] = g_slots[i];
        }
        for (int i = 0; i < 4; ++i) {
            if (slots[i].func) slots[i].func(ev.first, ev.second, slots[i].userdata);
        }
    }
    dotd::platform::MsgDialogPoll();  // the system dialogs answer through this call too
    return CELL_OK;
}

int32_t cellSysutilGetSystemParamInt(int32_t id, int32_t* value) {
    if (!value) return CellError(CELL_SYSUTIL_ERROR_VALUE);
    const dotd::platform::Config& cfg = dotd::platform::GetConfig();
    switch (id) {
    case CELL_SYSUTIL_SYSTEMPARAM_ID_LANG: *value = cfg.language; return CELL_OK;
    case CELL_SYSUTIL_SYSTEMPARAM_ID_ENTER_BUTTON_ASSIGN: *value = cfg.enterButton; return CELL_OK;
    case CELL_SYSUTIL_SYSTEMPARAM_ID_PAD_RUMBLE: *value = cfg.padRumble; return CELL_OK;
    default:
        DOTD_LOG("sysutil: GetSystemParamInt(0x%x) not implemented", static_cast<unsigned>(id));
        return CellError(CELL_SYSUTIL_ERROR_VALUE);
    }
}

int32_t cellSysutilEnableBgmPlayback() {
    g_bgmEnabled = true;
    return CELL_OK;
}

int32_t cellSysutilDisableBgmPlayback() {
    g_bgmEnabled = false;
    return CELL_OK;
}

int32_t cellSysutilGetBgmPlaybackStatus(CellSysutilBgmPlaybackStatus* status) {
    if (!status) return CellError(CELL_SYSUTIL_ERROR_VALUE);
    std::memset(status, 0, sizeof(*status));
    status->playerState = CELL_SYSUTIL_BGMPLAYBACK_STATUS_STOP;  // no XMB background music on the host
    status->enableState = g_bgmEnabled ? CELL_SYSUTIL_BGMPLAYBACK_STATUS_ENABLE : CELL_SYSUTIL_BGMPLAYBACK_STATUS_DISABLE;
    return CELL_OK;
}
