// pad.h - cellPad (sys_io) as the game uses it. Layouts and values match the PS3 SDK.
// cellPadGetData reports len = 0 when nothing changed since the last call for that port, like the
// PS3 (game input code relies on it); the data words are then left untouched.
#pragma once
#include <cstdint>

enum : uint32_t {
    CELL_PAD_MAX_PORT_NUM = 7,
    CELL_PAD_MAX_CODES = 64,
    CELL_PAD_ACTUATOR_MAX = 2,
};

enum : int32_t {
    CELL_PAD_LEN_NO_CHANGE = 0,
    CELL_PAD_LEN_CHANGE_DEFAULT = 8,
    CELL_PAD_LEN_CHANGE_PRESS_ON = 20,
    CELL_PAD_LEN_CHANGE_SENSOR_ON = 24,
};

enum : uint32_t {
    CELL_PAD_STATUS_DISCONNECTED = 0x0,
    CELL_PAD_STATUS_CONNECTED = 0x1,
    CELL_PAD_STATUS_ASSIGN_CHANGES = 0x2,
    CELL_PAD_SETTING_PRESS_ON = 0x2,
    CELL_PAD_SETTING_SENSOR_ON = 0x4,
    CELL_PAD_CAPABILITY_PS3_CONFORMITY = 0x1,
    CELL_PAD_CAPABILITY_PRESS_MODE = 0x2,
    CELL_PAD_CAPABILITY_SENSOR_MODE = 0x4,
    CELL_PAD_CAPABILITY_ACTUATOR = 0x10,
    CELL_PAD_DEV_TYPE_STANDARD = 0,
    CELL_PAD_PRESS_MODE_ON = 1,
    CELL_PAD_SENSOR_MODE_ON = 1,
};

// CellPadData.button[] offsets
enum {
    CELL_PAD_BTN_OFFSET_DIGITAL1 = 2,
    CELL_PAD_BTN_OFFSET_DIGITAL2 = 3,
    CELL_PAD_BTN_OFFSET_ANALOG_RIGHT_X = 4,
    CELL_PAD_BTN_OFFSET_ANALOG_RIGHT_Y = 5,
    CELL_PAD_BTN_OFFSET_ANALOG_LEFT_X = 6,
    CELL_PAD_BTN_OFFSET_ANALOG_LEFT_Y = 7,
    CELL_PAD_BTN_OFFSET_PRESS_RIGHT = 8,
    CELL_PAD_BTN_OFFSET_SENSOR_X = 20,
};

// digital1 / digital2 bits
enum : uint16_t {
    CELL_PAD_CTRL_SELECT = 0x0001, CELL_PAD_CTRL_L3 = 0x0002, CELL_PAD_CTRL_R3 = 0x0004, CELL_PAD_CTRL_START = 0x0008,
    CELL_PAD_CTRL_UP = 0x0010, CELL_PAD_CTRL_RIGHT = 0x0020, CELL_PAD_CTRL_DOWN = 0x0040, CELL_PAD_CTRL_LEFT = 0x0080,
    CELL_PAD_CTRL_L2 = 0x0001, CELL_PAD_CTRL_R2 = 0x0002, CELL_PAD_CTRL_L1 = 0x0004, CELL_PAD_CTRL_R1 = 0x0008,
    CELL_PAD_CTRL_TRIANGLE = 0x0010, CELL_PAD_CTRL_CIRCLE = 0x0020, CELL_PAD_CTRL_CROSS = 0x0040, CELL_PAD_CTRL_SQUARE = 0x0080,
};

struct CellPadData {
    int32_t len;
    uint16_t button[CELL_PAD_MAX_CODES];
};
static_assert(sizeof(CellPadData) == 132, "PS3 layout");

struct CellPadInfo2 {
    uint32_t max_connect;
    uint32_t now_connect;
    uint32_t system_info;
    uint32_t port_status[CELL_PAD_MAX_PORT_NUM];
    uint32_t port_setting[CELL_PAD_MAX_PORT_NUM];
    uint32_t device_capability[CELL_PAD_MAX_PORT_NUM];
    uint32_t device_type[CELL_PAD_MAX_PORT_NUM];
};
static_assert(sizeof(CellPadInfo2) == 124, "PS3 layout");

struct CellPadActParam {
    uint8_t motor[CELL_PAD_ACTUATOR_MAX];
    uint8_t reserved[6];
};

int32_t cellPadInit(uint32_t max_connect);
int32_t cellPadEnd();
int32_t cellPadGetInfo2(CellPadInfo2* info);
int32_t cellPadGetData(uint32_t port_no, CellPadData* data);
int32_t cellPadSetPressMode(uint32_t port_no, uint32_t mode);
int32_t cellPadSetSensorMode(uint32_t port_no, uint32_t mode);
int32_t cellPadSetActDirect(uint32_t port_no, CellPadActParam* param);

namespace dotd::platform {
// Source of raw pad words (CellPadData.button layout, [2..23]); the SDL layer by default. Replays
// replace it with recorded input. Returns false when nothing is connected on the port.
typedef bool (*PadSource)(int port, uint16_t words[24]);
void SetPadSource(PadSource source);  // nullptr = SDL
// The raw words of a port from the current source (no change tracking; the system dialogs read it).
bool ReadPadWords(int port, uint16_t words[24]);
}
