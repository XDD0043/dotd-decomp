#include "platform/cell/pad.h"

#include <cstring>
#include <mutex>

#include "platform/cell/cell_errors.h"
#include "platform/sdl/app.h"

namespace {
std::mutex g_mutex;
bool g_initialised = false;
uint32_t g_maxConnect = 0;
uint32_t g_setting[CELL_PAD_MAX_PORT_NUM] = {};
uint16_t g_lastReported[CELL_PAD_MAX_PORT_NUM][24] = {};
bool g_reportedOnce[CELL_PAD_MAX_PORT_NUM] = {};
dotd::platform::PadSource g_source = nullptr;

bool ReadSource(int port, uint16_t words[24]) {
    return g_source ? g_source(port, words) : dotd::platform::sdl::ReadPad(port, words);
}
}  // namespace

namespace dotd::platform {
void SetPadSource(PadSource source) {
    std::lock_guard<std::mutex> lock(g_mutex);
    g_source = source;
}

bool ReadPadWords(int port, uint16_t words[24]) {
    std::lock_guard<std::mutex> lock(g_mutex);
    return ReadSource(port, words);
}
}  // namespace dotd::platform

int32_t cellPadInit(uint32_t max_connect) {
    std::lock_guard<std::mutex> lock(g_mutex);
    if (g_initialised) return CellError(CELL_PAD_ERROR_ALREADY_INITIALIZED);
    if (max_connect == 0) return CellError(CELL_PAD_ERROR_INVALID_PARAMETER);
    g_initialised = true;
    g_maxConnect = max_connect > CELL_PAD_MAX_PORT_NUM ? CELL_PAD_MAX_PORT_NUM : max_connect;
    std::memset(g_setting, 0, sizeof(g_setting));
    std::memset(g_reportedOnce, 0, sizeof(g_reportedOnce));
    return CELL_OK;
}

int32_t cellPadEnd() {
    std::lock_guard<std::mutex> lock(g_mutex);
    if (!g_initialised) return CellError(CELL_PAD_ERROR_UNINITIALIZED);
    g_initialised = false;
    return CELL_OK;
}

int32_t cellPadGetInfo2(CellPadInfo2* info) {
    std::lock_guard<std::mutex> lock(g_mutex);
    if (!g_initialised) return CellError(CELL_PAD_ERROR_UNINITIALIZED);
    if (!info) return CellError(CELL_PAD_ERROR_INVALID_PARAMETER);
    std::memset(info, 0, sizeof(*info));
    info->max_connect = g_maxConnect;
    info->system_info = 0;  // bit 0: input intercepted by the system (never on the host)
    uint16_t words[24];
    for (uint32_t p = 0; p < g_maxConnect; ++p) {
        if (!ReadSource(static_cast<int>(p), words)) continue;
        info->now_connect++;
        info->port_status[p] = CELL_PAD_STATUS_CONNECTED;
        info->port_setting[p] = g_setting[p];
        info->device_capability[p] = CELL_PAD_CAPABILITY_PS3_CONFORMITY | CELL_PAD_CAPABILITY_PRESS_MODE |
                                     CELL_PAD_CAPABILITY_SENSOR_MODE | CELL_PAD_CAPABILITY_ACTUATOR;
        info->device_type[p] = CELL_PAD_DEV_TYPE_STANDARD;
    }
    return CELL_OK;
}

int32_t cellPadGetData(uint32_t port_no, CellPadData* data) {
    std::lock_guard<std::mutex> lock(g_mutex);
    if (!g_initialised) return CellError(CELL_PAD_ERROR_UNINITIALIZED);
    if (!data || port_no >= g_maxConnect) return CellError(CELL_PAD_ERROR_INVALID_PARAMETER);
    uint16_t words[24];
    if (!ReadSource(static_cast<int>(port_no), words)) return CellError(CELL_PAD_ERROR_NO_DEVICE);

    const uint32_t setting = g_setting[port_no];
    const bool press = (setting & CELL_PAD_SETTING_PRESS_ON) != 0;
    const bool sensor = (setting & CELL_PAD_SETTING_SENSOR_ON) != 0;
    const int reported = sensor ? CELL_PAD_LEN_CHANGE_SENSOR_ON : (press ? CELL_PAD_LEN_CHANGE_PRESS_ON : CELL_PAD_LEN_CHANGE_DEFAULT);
    // A change is any difference in the words the current setting reports. With sensors on, the PS3
    // reports every ~10 ms; the game polls once per 60 Hz frame, so that is every call.
    bool changed = sensor || !g_reportedOnce[port_no];
    for (int i = CELL_PAD_BTN_OFFSET_DIGITAL1; i < reported && !changed; ++i) {
        if (words[i] != g_lastReported[port_no][i]) changed = true;
    }
    if (!changed) {
        data->len = CELL_PAD_LEN_NO_CHANGE;
        return CELL_OK;
    }
    data->len = reported;
    data->button[0] = 0;
    data->button[1] = static_cast<uint16_t>((0x7 << 4) | (reported / 2 > 15 ? 15 : reported / 2));
    for (int i = CELL_PAD_BTN_OFFSET_DIGITAL1; i < CELL_PAD_LEN_CHANGE_DEFAULT; ++i) data->button[i] = words[i];
    for (int i = CELL_PAD_LEN_CHANGE_DEFAULT; i < CELL_PAD_LEN_CHANGE_PRESS_ON; ++i) data->button[i] = press ? words[i] : 0;
    if (sensor) {
        for (int i = CELL_PAD_BTN_OFFSET_SENSOR_X; i < CELL_PAD_LEN_CHANGE_SENSOR_ON; ++i) data->button[i] = words[i];
    }
    std::memcpy(g_lastReported[port_no], words, sizeof(words));
    g_reportedOnce[port_no] = true;
    return CELL_OK;
}

int32_t cellPadSetPressMode(uint32_t port_no, uint32_t mode) {
    std::lock_guard<std::mutex> lock(g_mutex);
    if (!g_initialised) return CellError(CELL_PAD_ERROR_UNINITIALIZED);
    if (port_no >= CELL_PAD_MAX_PORT_NUM) return CellError(CELL_PAD_ERROR_INVALID_PARAMETER);
    if (mode) g_setting[port_no] |= CELL_PAD_SETTING_PRESS_ON;
    else g_setting[port_no] &= ~static_cast<uint32_t>(CELL_PAD_SETTING_PRESS_ON);
    return CELL_OK;
}

int32_t cellPadSetSensorMode(uint32_t port_no, uint32_t mode) {
    std::lock_guard<std::mutex> lock(g_mutex);
    if (!g_initialised) return CellError(CELL_PAD_ERROR_UNINITIALIZED);
    if (port_no >= CELL_PAD_MAX_PORT_NUM) return CellError(CELL_PAD_ERROR_INVALID_PARAMETER);
    if (mode) g_setting[port_no] |= CELL_PAD_SETTING_SENSOR_ON;
    else g_setting[port_no] &= ~static_cast<uint32_t>(CELL_PAD_SETTING_SENSOR_ON);
    return CELL_OK;
}

int32_t cellPadSetActDirect(uint32_t port_no, CellPadActParam* param) {
    {
        std::lock_guard<std::mutex> lock(g_mutex);
        if (!g_initialised) return CellError(CELL_PAD_ERROR_UNINITIALIZED);
        if (!param || port_no >= g_maxConnect) return CellError(CELL_PAD_ERROR_INVALID_PARAMETER);
    }
    dotd::platform::sdl::Rumble(static_cast<int>(port_no), param->motor[0], param->motor[1]);
    return CELL_OK;
}
