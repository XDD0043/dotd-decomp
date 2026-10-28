// Unit tests for the platform shims that need no game data and no window.
#include <cstdio>
#include <cstring>
#include <string>

#include "platform/cell/cell_errors.h"
#include "platform/cell/fs.h"
#include "platform/cell/l10n.h"
#include "platform/cell/pad.h"
#include "platform/cell/sys_sync.h"
#include "platform/cell/sysutil.h"
#include "platform/config.h"

static int g_failures = 0;
#define CHECK(cond)                                                              \
    do {                                                                         \
        if (!(cond)) {                                                           \
            std::printf("FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond);         \
            ++g_failures;                                                        \
        }                                                                        \
    } while (0)

static uint16_t g_fakeWords[24];
static bool FakePad(int port, uint16_t words[24]) {
    if (port != 0) return false;
    std::memcpy(words, g_fakeWords, sizeof(g_fakeWords));
    return true;
}

static int g_exitEvents = 0;
static void OnSysutil(uint64_t status, uint64_t, void*) {
    if (status == CELL_SYSUTIL_REQUEST_EXITGAME) ++g_exitEvents;
}

int main() {
    // path mapping
    dotd::platform::MutableConfig().usrdir = "D:/games/dotd/USRDIR";
    std::string host;
    bool writable = true;
    CHECK(dotd::platform::MapPs3Path("/dev_bdvd/PS3_GAME/USRDIR/GAME.KP3", &host, &writable));
    CHECK(host == "D:/games/dotd/USRDIR/GAME.KP3");
    CHECK(!writable);
    CHECK(dotd::platform::MapPs3Path("/app_home\\LVL000\\LVL000.KP3", &host, &writable));
    CHECK(host == "D:/games/dotd/USRDIR/LVL000/LVL000.KP3");
    CHECK(dotd::platform::MapPs3Path("/dev_bdvd/PS3_GAME/USRDIR", &host, &writable));
    CHECK(host == "D:/games/dotd/USRDIR");
    CHECK(!dotd::platform::MapPs3Path("/dev_bdvd/PS3_GAME/USRDIRX/a", &host, &writable));
    CHECK(!dotd::platform::MapPs3Path("/dev_hdd0/game/x", &host, &writable));
    CHECK(sizeof(CellFsStat) == 52);

    // UCS-2 -> UTF-8
    const uint16_t text[] = {'S', 'p', 0x00e9, 0x20ac};  // "Spé€"
    uint8_t out[16];
    size_t srcLen = 4, dstLen = sizeof(out);
    CHECK(UCS2stoUTF8s(text, &srcLen, out, &dstLen) == ConversionOK);
    CHECK(dstLen == 7 && out[2] == 0xC3 && out[3] == 0xA9 && out[4] == 0xE2 && out[5] == 0x82 && out[6] == 0xAC);
    srcLen = 4;
    dstLen = 3;
    CHECK(UCS2stoUTF8s(text, &srcLen, out, &dstLen) == DSTExhausted);
    CHECK(srcLen == 2 && dstLen == 2);

    // lwmutex: recursive lock on the owning thread, unlock balance
    sys_lwmutex_t m;
    sys_lwmutex_attribute_t attr = {0, 0x20, {'t', 'e', 's', 't'}};
    CHECK(sys_lwmutex_create(&m, &attr) == CELL_OK);
    CHECK(sys_lwmutex_lock(&m, 0) == CELL_OK);
    CHECK(sys_lwmutex_trylock(&m) == CELL_OK);
    CHECK(sys_lwmutex_unlock(&m) == CELL_OK);
    CHECK(sys_lwmutex_unlock(&m) == CELL_OK);
    CHECK(sys_lwmutex_unlock(&m) == CellError(CELL_EPERM));
    CHECK(sys_lwmutex_destroy(&m) == CELL_OK);

    // semaphore: max, trywait, timeout
    sys_semaphore_t s = 0;
    CHECK(sys_semaphore_create(&s, nullptr, 2, 3) == CELL_OK);
    CHECK(sys_semaphore_trywait(s) == CELL_OK);
    CHECK(sys_semaphore_trywait(s) == CELL_OK);
    CHECK(sys_semaphore_trywait(s) == CellError(CELL_EBUSY));
    CHECK(sys_semaphore_wait(s, 1000) == CellError(CELL_ETIMEDOUT));
    CHECK(sys_semaphore_post(s, 3) == CELL_OK);
    CHECK(sys_semaphore_post(s, 1) == CellError(CELL_EBUSY));  // above max
    CHECK(sys_semaphore_destroy(s) == CELL_OK);

    // pad: len = 0 when nothing changed, header word, press-mode area cleared
    dotd::platform::SetPadSource(&FakePad);
    std::memset(g_fakeWords, 0, sizeof(g_fakeWords));
    g_fakeWords[4] = g_fakeWords[5] = g_fakeWords[6] = g_fakeWords[7] = 0x80;
    CHECK(cellPadInit(7) == CELL_OK);
    CHECK(cellPadInit(7) == CellError(CELL_PAD_ERROR_ALREADY_INITIALIZED));
    CellPadData d;
    std::memset(&d, 0xcd, sizeof(d));
    CHECK(cellPadGetData(0, &d) == CELL_OK);
    CHECK(d.len == CELL_PAD_LEN_CHANGE_DEFAULT && d.button[0] == 0 && d.button[1] == 0x74);
    CHECK(d.button[8] == 0);  // pressure area cleared when press mode is off
    CHECK(cellPadGetData(0, &d) == CELL_OK && d.len == CELL_PAD_LEN_NO_CHANGE);
    g_fakeWords[3] = CELL_PAD_CTRL_CROSS;
    CHECK(cellPadGetData(0, &d) == CELL_OK && d.len == CELL_PAD_LEN_CHANGE_DEFAULT && d.button[3] == CELL_PAD_CTRL_CROSS);
    g_fakeWords[14] = 200;  // pressure only: not reported without press mode
    CHECK(cellPadGetData(0, &d) == CELL_OK && d.len == CELL_PAD_LEN_NO_CHANGE);
    CHECK(cellPadSetPressMode(0, CELL_PAD_PRESS_MODE_ON) == CELL_OK);
    CHECK(cellPadGetData(0, &d) == CELL_OK && d.len == CELL_PAD_LEN_CHANGE_PRESS_ON && d.button[14] == 200);
    CHECK(cellPadGetData(1, &d) == CellError(CELL_PAD_ERROR_NO_DEVICE));
    CellPadInfo2 info;
    CHECK(cellPadGetInfo2(&info) == CELL_OK && info.now_connect == 1 && info.port_status[0] == CELL_PAD_STATUS_CONNECTED);
    CHECK(cellPadEnd() == CELL_OK);

    // sysutil: queued events reach registered callbacks on CheckCallback
    CHECK(cellSysutilRegisterCallback(0, OnSysutil, nullptr) == CELL_OK);
    dotd::platform::PostSysutilEvent(CELL_SYSUTIL_REQUEST_EXITGAME, 0);
    CHECK(g_exitEvents == 0);
    CHECK(cellSysutilCheckCallback() == CELL_OK);
    CHECK(g_exitEvents == 1);
    int32_t lang = -1;
    CHECK(cellSysutilGetSystemParamInt(CELL_SYSUTIL_SYSTEMPARAM_ID_LANG, &lang) == CELL_OK && lang == 1);

    if (g_failures == 0) std::printf("platform: all tests passed\n");
    return g_failures == 0 ? 0 : 1;
}
