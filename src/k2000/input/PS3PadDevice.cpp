// PS3PadDevice.cpp - reconstructed original translation unit 0x10f2b0-0x110038 (GAME_TOC1, main_toc1), 28 functions, 24 live.
// Primary owner: PS3PadDevice (not a registered class)
// Other owners: PS3Pad (2), PadDevice (1), PollPs3ControllerState (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x10f2b0  PS3PadDevice_Construct_2_maybe  [dead]
//   [x] 0x10f2d0  KStub_Return1_10f2d0
//   [x] 0x10f2d8  PS3PadDevice_ClearConnected_maybe
//   [x] 0x10f2e8  PS3PadDevice_vf18_ForwardToStopVibration_maybe
//   [x] 0x10f330  PS3PadDevice_vf1C_ForwardToStopVibration_maybe
//   [x] 0x10f378  KStub_Nop_10f378
//   [x] 0x10f380  PS3PadDevice_vf20_ForwardToStopVibration_maybe
//   [ ] 0x10f3c8  FUN_0010f3c8  [dead]
//   [ ] 0x10f3e0  FUN_0010f3e0  [dead]
//   [x] 0x10f3f0  PS3PadDevice_SetButtonStates_maybe
//   [x] 0x10f428  PS3PadDevice_ResetButtonMap_maybe
//   [x] 0x10f450  PS3PadDevice_Init_maybe
//   [x] 0x10f498  KStub_Return1_10f498
//   [x] 0x10f4a0  KStub_Nop_10f4a0
//   [ ] 0x10f4a8  PS3PadDevice_Destructor_2_maybe  [dead]
//   [x] 0x10f4b8  PS3PadDevice_Setup_maybe
//   [x] 0x10f540  PS3PadDevice_SetSensorMode
//   [x] 0x10f5c8  PS3PadDevice_SetPressMode
//   [x] 0x10f650  PS3PadDevice_StopActuator_maybe
//   [x] 0x10f6d0  PS3PadDevice_StopVibration
//   [x] 0x10f740  PS3Pad_ClearActuator_maybe
//   [x] 0x10f7c0  PadDevice_SetActuator_maybe
//   [x] 0x10f868  PS3Pad_SetActuator_maybe
//   [x] 0x10f910  PS3PadDevice_RefreshPadInfo_maybe
//   [x] 0x10f948  PollPs3ControllerState
//   [x] 0x10ffd8  PS3PadDevice_Construct_maybe
//   [x] 0x10fff8  PS3PadDevice_DeletingDestructor_maybe  (~PS3PadDevice, PS3PadDevice.h: delete)
//   [x] 0x110028  PS3PadDevice_Destructor_maybe  (~PS3PadDevice, PS3PadDevice.h (vtable store only))
//
//   [x] 0x9a6820  PS3PadDevice_GetCurrentState  [inline]
//   [x] 0x9a6830  PS3PadDevice_GetPreviousState  [inline]
//   [x] 0x9a6840  PS3PadDevice_GetStatusByte_maybe  [inline]
//   [x] 0x9a6850  PS3PadDevice_GetStateBlockPtr60_maybe  [inline]
//   [ ] 0x9a6860  PadDeviceBase_DeletingDestructor_maybe  [inline]
//   [ ] 0x9a6890  PadDeviceBase_Destructor_maybe  [inline]
//   [x] 0x9a68a0  PS3PadDevice_ClearStates  [inline]
#include "k2000/input/PS3PadDevice.h"

#include <cstring>

#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/CellSysutilCallback.h"

// 0x0010ffd8 PS3PadDevice_Construct_maybe: the vibration flag (the IKPad vtable store is immediately replaced).
PS3PadDevice::PS3PadDevice() { m_bVibrationEnabled = 0; }

// 0x0010f450 PS3PadDevice_Init_maybe (XXL2 InitializeData(CKParams*)): the parameters are not used.
int32_t PS3PadDevice::InitializeData(void* /*params*/) {
    ResetButtonMap();
    return 1;
}

// 0x0010f4b8 PS3PadDevice_Setup_maybe (XXL2 InitPad): the index, the button values cleared; only the first
// argument is used.
int32_t PS3PadDevice::InitPad(uint8_t index, uint8_t /*arg2*/, uint32_t /*arg3*/, uint8_t /*useAnalog*/,
                              uint8_t /*forceAnalog*/) {
    m_ui8Index = index;
    m_bLockByTRC = 0;
    std::memset(m_ui8OldVirtualPadValue, 0, sizeof(m_ui8OldVirtualPadValue));
    std::memset(m_ui8VirtualPadValue, 0, sizeof(m_ui8VirtualPadValue));
    m_bActuator = 0;
    m_bActive = 0;
    m_bPressMode = 0;
    m_bSensorMode = 0;
    return 1;
}

// 0x0010f428 PS3PadDevice_ResetButtonMap_maybe: no name for any button.
void PS3PadDevice::ResetButtonMap() {
    for (uint32_t i = 0; i < 0x2c; ++i) m_i32VirtualPadButtonNames[i] = -1;
}

// 0x0010f2d8 PS3PadDevice_ClearConnected_maybe (XXL2 ReInitPad)
int32_t PS3PadDevice::ReInitPad() {
    m_bActive = 0;
    return 1;
}

// 0x0010f2e8 PS3PadDevice_vf18_ForwardToStopVibration_maybe (XXL2 Restart)
void PS3PadDevice::Restart() { StopAllVibration(); }
// 0x0010f330 PS3PadDevice_vf1C_ForwardToStopVibration_maybe (XXL2 Pause)
void PS3PadDevice::Pause() { StopAllVibration(); }
// 0x0010f380 PS3PadDevice_vf20_ForwardToStopVibration_maybe (XXL2 Stop)
void PS3PadDevice::Stop() { StopAllVibration(); }

// 0x0010f3f0 PS3PadDevice_SetButtonStates_maybe: the 44 current values, byte by byte.
void PS3PadDevice::SetButtonStates(const uint8_t* values) {
    for (uint32_t i = 0; i < 0x2c; ++i) m_ui8VirtualPadValue[i] = values[i];
}

namespace {
// The actuator parameter the vibration slots build on the stack: the two motor values, the rest zero.
void SendActuators(const PS3PadDevice* pad) {
    CellPadActParam param;
    std::memset(param.reserved, 0, sizeof(param.reserved));
    param.motor[0] = pad->m_aui8Motor[0];
    param.motor[1] = pad->m_aui8Motor[1];
    cellPadSetActDirect(pad->m_ui8Index, &param);
}
}  // namespace

// 0x0010f868 PS3Pad_SetActuator_maybe (XXL2 StartVibration): motor 0 (the small one) is only on or off.
int32_t PS3PadDevice::StartVibration(int32_t motor, int32_t value) {
    if (motor == 0) m_aui8Motor[0] = value != 0 ? 1 : 0;
    else m_aui8Motor[motor] = static_cast<uint8_t>(value);
    if (m_bActuator != 0) SendActuators(this);
    return 1;
}

// 0x0010f7c0 PadDevice_SetActuator_maybe (XXL2 UpdateVibrationValue): StartVibration's body.
int32_t PS3PadDevice::UpdateVibrationValue(int32_t motor, int32_t value) {
    if (motor == 0) m_aui8Motor[0] = value != 0 ? 1 : 0;
    else m_aui8Motor[motor] = static_cast<uint8_t>(value);
    if (m_bActuator != 0) SendActuators(this);
    return 1;
}

// 0x0010f740 PS3Pad_ClearActuator_maybe (XXL2 StopVibration)
int32_t PS3PadDevice::StopVibration(int32_t motor) {
    m_aui8Motor[motor] = 0;
    if (m_bActuator != 0) SendActuators(this);
    return 1;
}

// 0x0010f6d0 PS3PadDevice_StopVibration (XXL2 StopAllVibration): both motors off; the parameter is sent
// all zero.
int32_t PS3PadDevice::StopAllVibration() {
    m_aui8Motor[0] = 0;
    m_aui8Motor[1] = 0;
    if (m_bActuator != 0) {
        CellPadActParam param;
        std::memset(&param, 0, sizeof(param));
        cellPadSetActDirect(m_ui8Index, &param);
    }
    return 1;
}

// 0x0010f650 PS3PadDevice_StopActuator_maybe (XXL2 StopHardVibration): StopVibration's body.
int32_t PS3PadDevice::StopHardVibration(int32_t motor) {
    m_aui8Motor[motor] = 0;
    if (m_bActuator != 0) SendActuators(this);
    return 1;
}

// 0x009a68a0 PS3PadDevice_ClearStates: the current and the previous values.
void PS3PadDevice::ClearStates() {
    std::memset(m_ui8VirtualPadValue, 0, 0x2c);
    std::memset(m_ui8OldVirtualPadValue, 0, 0x2c);
}

// 0x0010f5c8 PS3PadDevice_SetPressMode
void PS3PadDevice::SetPressMode(int32_t enabled) {
    if (enabled != 0) {
        cellPadSetPressMode(m_ui8Index, 1);
        m_bPressMode = 1;
        return;
    }
    cellPadSetPressMode(m_ui8Index, 0);
    m_bPressMode = 0;
}

// 0x0010f540 PS3PadDevice_SetSensorMode
void PS3PadDevice::SetSensorMode(int32_t enabled) {
    if (enabled != 0) {
        cellPadSetSensorMode(m_ui8Index, 1);
        m_bSensorMode = 1;
        return;
    }
    cellPadSetSensorMode(m_ui8Index, 0);
    m_bSensorMode = 0;
}

CellPadInfo2 g_padInfo2;            // 0x00cea7d4
uint8_t g_padInputIntercepted = 0;  // 0x00c40250

// 0x0010f910 PS3PadDevice_RefreshPadInfo_maybe: pad 0 refreshes the shared info.
void PS3PadDevice::RefreshPadInfo() {
    if (m_ui8Index == 0) cellPadGetInfo2(&g_padInfo2);
}

namespace {
// A stick axis (0..0xff, centre 0x80) split into its two directions, as the PS3 code stores them: below
// the centre the negative side gets ~(v << 1), otherwise the positive side gets v * 2 + 1.
inline void SplitAxis(uint16_t raw, uint8_t* negative, uint8_t* positive) {
    const uint8_t v = static_cast<uint8_t>(raw);
    if (raw < 0x80) *negative = static_cast<uint8_t>(~(v << 1));
    else *positive = static_cast<uint8_t>(v * 2 + 1);
}
}  // namespace

// 0x0010f948 PollPs3ControllerState: the previous values saved, then (when the port is connected and the
// pad not locked) the new data decoded into the 44 values (index = object offset - 8): 0..3 left stick
// (y-, y+, x-, x+), 4..7 up, down, left, right, 8..0xb right stick, 0xc..0x13 cross, square, circle,
// triangle, L1, L2, R1, R2, 0x14..0x17 start, select, L3, R3, 0x18..0x23 the pressure values, 0x24..0x2b
// the sensors.
int32_t PS3PadDevice::Update() {
    CDefaultGameManager* gameManager = g_pEngine->m_gameManager;
    uint8_t port = m_ui8Index;
    if (port == 0) {
        cellPadGetInfo2(&g_padInfo2);
        g_padInputIntercepted = static_cast<uint8_t>(g_padInfo2.system_info & 1);
        port = m_ui8Index;
    }
    const uint32_t capability = g_padInfo2.device_capability[port];
    m_bActuator = static_cast<uint8_t>((capability >> 4) & 1);                         // CELL_PAD_CAPABILITY_ACTUATOR
    m_bActuator = static_cast<uint8_t>(m_bActuator & (g_padRumbleEnabled == 1 ? 1 : 0));  // and rumble on in the system
    m_bPressMode = static_cast<uint8_t>((capability >> 1) & 1);                         // PRESS_MODE
    m_bSensorMode = static_cast<uint8_t>((capability >> 2) & 1);                         // SENSOR_MODE
    std::memcpy(m_ui8OldVirtualPadValue, m_ui8VirtualPadValue, sizeof(m_ui8OldVirtualPadValue));
    uint8_t* values = m_ui8VirtualPadValue;
    if (m_bLockByTRC == 0) {
        if (g_padInfo2.port_status[port] == 1) {
            if (cellPadGetData(port, &m_padData) != 0) return 1;
            const int32_t len = m_padData.len;
            m_bActive = 1;
            if (len != 0) {
                std::memset(values, 0, 0x2c);
                uint16_t digital1 = 0;
                if (len > 1) digital1 = m_padData.button[CELL_PAD_BTN_OFFSET_DIGITAL1];
                uint16_t digital2 = 0;
                if (len >= 3) digital2 = m_padData.button[CELL_PAD_BTN_OFFSET_DIGITAL2];
                if (digital1 & CELL_PAD_CTRL_LEFT) values[0x06] = 0xff;
                if (digital1 & CELL_PAD_CTRL_DOWN) values[0x05] = 0xff;
                if (digital1 & CELL_PAD_CTRL_RIGHT) values[0x07] = 0xff;
                if (digital1 & CELL_PAD_CTRL_UP) values[0x04] = 0xff;
                if (digital1 & CELL_PAD_CTRL_START) values[0x14] = 0xff;
                if (digital1 & CELL_PAD_CTRL_SELECT) values[0x15] = 0xff;
                if (digital1 & CELL_PAD_CTRL_L3) values[0x16] = 0xff;
                if (digital1 & CELL_PAD_CTRL_R3) values[0x17] = 0xff;
                if (digital2 & CELL_PAD_CTRL_SQUARE) values[0x0d] = 0xff;
                if (digital2 & CELL_PAD_CTRL_CROSS) values[0x0c] = 0xff;
                if (digital2 & CELL_PAD_CTRL_CIRCLE) values[0x0e] = 0xff;
                if (digital2 & CELL_PAD_CTRL_TRIANGLE) values[0x0f] = 0xff;
                if (digital2 & CELL_PAD_CTRL_L1) values[0x10] = 0xff;
                if (digital2 & CELL_PAD_CTRL_L2) values[0x11] = 0xff;
                if (digital2 & CELL_PAD_CTRL_R1) values[0x12] = 0xff;
                if (digital2 & CELL_PAD_CTRL_R2) values[0x13] = 0xff;
            }
            // The sticks are decoded from the buffer even when nothing changed (len 0: the old data).
            SplitAxis(m_padData.button[CELL_PAD_BTN_OFFSET_ANALOG_LEFT_X], &values[0x02], &values[0x03]);
            SplitAxis(m_padData.button[CELL_PAD_BTN_OFFSET_ANALOG_LEFT_Y], &values[0x00], &values[0x01]);
            SplitAxis(m_padData.button[CELL_PAD_BTN_OFFSET_ANALOG_RIGHT_X], &values[0x0a], &values[0x0b]);
            SplitAxis(m_padData.button[CELL_PAD_BTN_OFFSET_ANALOG_RIGHT_Y], &values[0x08], &values[0x09]);
            if (m_bPressMode != 0) {
                // The pressure words (button[8..19]) in the order the PS3 code stores them.
                values[0x18] = static_cast<uint8_t>(m_padData.button[10]);
                values[0x19] = static_cast<uint8_t>(m_padData.button[11]);
                values[0x1a] = static_cast<uint8_t>(m_padData.button[9]);
                values[0x1b] = static_cast<uint8_t>(m_padData.button[8]);
                values[0x1d] = static_cast<uint8_t>(m_padData.button[15]);
                values[0x1c] = static_cast<uint8_t>(m_padData.button[14]);
                values[0x1e] = static_cast<uint8_t>(m_padData.button[13]);
                values[0x1f] = static_cast<uint8_t>(m_padData.button[12]);
                values[0x21] = static_cast<uint8_t>(m_padData.button[17]);
                values[0x20] = static_cast<uint8_t>(m_padData.button[16]);
                values[0x23] = static_cast<uint8_t>(m_padData.button[19]);
                values[0x22] = static_cast<uint8_t>(m_padData.button[18]);
            }
            if (m_bSensorMode == 0) return 1;
            const uint16_t sensorX = m_padData.button[CELL_PAD_BTN_OFFSET_SENSOR_X];
            const uint16_t sensorZ = m_padData.button[CELL_PAD_BTN_OFFSET_SENSOR_X + 2];
            values[0x24] = static_cast<uint8_t>(sensorX >> 2);
            values[0x25] = static_cast<uint8_t>(m_padData.button[CELL_PAD_BTN_OFFSET_SENSOR_X + 1] >> 2);
            values[0x26] = static_cast<uint8_t>(sensorZ >> 2);
            values[0x27] = static_cast<uint8_t>(m_padData.button[CELL_PAD_BTN_OFFSET_SENSOR_X + 3] >> 2);
            if (sensorX < 0x200) values[0x2a] = static_cast<uint8_t>(~static_cast<uint8_t>(sensorX >> 1));
            else values[0x2b] = static_cast<uint8_t>(static_cast<uint8_t>(sensorX >> 1) + 1);
            if (sensorZ < 0x200) {
                values[0x28] = static_cast<uint8_t>(~static_cast<uint8_t>(sensorZ >> 1));
                return 1;
            }
            values[0x29] = static_cast<uint8_t>(static_cast<uint8_t>(sensorZ >> 1) + 1);
            return 1;
        }
        m_bActive = 0;
        // vt+0x134 GetControlledHeroCount, then vt+0xc8 HandleControllerDisconnect_maybe on the engine's.
        if (port < gameManager->GetControlledHeroCount()) g_pEngine->m_gameManager->HandleControllerDisconnect(m_ui8Index);
    }
    std::memset(values, 0, 0x2c);
    return 1;
}
