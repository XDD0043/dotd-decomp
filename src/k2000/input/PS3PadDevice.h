// PS3PadDevice.h - the pad devices CKInput's Load creates (CKInput::m_aPads, m_ui8NbPads of them).
// IKPad (Ghidra: PadDeviceBase, vtable 0xb19700) is XXL2's K/KModules/KIL/KPad/IKPad.h with DotD's 44
// buttons; PS3PadDevice (vtable 0xb19678, size 0x21c) is the PS3 platform pad (XXL2's Mac one is O_CKPad,
// whose vtable has the same first slots; the PS3 class name is unknown). Code in input/PS3PadDevice.cpp
// (0x10f2b0-0x110038).
// Reading the pads (vt+0x28 RefreshPadInfo, +0x2c PollPs3ControllerState) is ported (C1.4, the menus'
// START/skip); The vibration and the sensor/press mode slots are ported in C1.6.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "platform/cell/pad.h"

class IKPad {
public:
    virtual ~IKPad() {}                                  // vt+0x00 / +0x04 0x9a6890 / 0x9a6860
    virtual int32_t InitializeData(void* params) = 0;    // vt+0x08 XXL2 InitializeData(CKParams*)
    virtual int32_t Destroy() = 0;                       // vt+0x0c
    // vt+0x10 XXL2 InitPad(UInt8, UInt8, UInt32, Bool, Bool)
    virtual int32_t InitPad(uint8_t index, uint8_t arg2, uint32_t arg3, uint8_t useAnalog, uint8_t forceAnalog) = 0;

    uint8_t m_bActive;                       // +0x04 InitPad clears it
    uint8_t m_bLockByTRC;                    // +0x05 InitPad clears it
    uint8_t m_bVibrationEnabled;             // +0x06 constructor 0 (CKInput_GetVibrationEnabled reads it)
    uint8_t m_ui8Index;                      // +0x07 InitPad's first argument, the pad index
    uint8_t m_ui8VirtualPadValue[44];        // +0x08 current button values (vt+0x30 returns it)
    uint8_t m_ui8OldVirtualPadValue[44];     // +0x34 previous button values (vt+0x34 returns it)
    int32_t m_i32VirtualPadButtonNames[44];  // +0x60 the Load copies the configured names here (vt+0x58)
};

class PS3PadDevice : public IKPad {
public:
    PS3PadDevice();  // 0x0010ffd8 PS3PadDevice_Construct_maybe
    ~PS3PadDevice() override {}  // vt+0x00 / +0x04 0x110028 / 0x10fff8

    int32_t InitializeData(void* params) override;  // vt+0x08 0x0010f450 PS3PadDevice_Init_maybe
    int32_t Destroy() override { return 1; }        // vt+0x0c 0x10f2d0
    int32_t InitPad(uint8_t index, uint8_t arg2, uint32_t arg3, uint8_t useAnalog,
                    uint8_t forceAnalog) override;  // vt+0x10 0x0010f4b8 PS3PadDevice_Setup_maybe
    // vt+0x14..+0x4c: XXL2 O_CKPad's slot names where the bodies match (ReInitPad .. Resume, the
    // vibration slots); DotD inserts the state accessors at +0x30..+0x38.
    virtual int32_t ReInitPad();    // vt+0x14 0x0010f2d8 PS3PadDevice_ClearConnected_maybe
    virtual void Restart();         // vt+0x18 0x0010f2e8 (vt+0x48)
    virtual void Pause();           // vt+0x1c 0x0010f330 (vt+0x48)
    virtual void Stop();            // vt+0x20 0x0010f380 (vt+0x48)
    virtual void Resume() {}        // vt+0x24 0x10f378 KStub_Nop_10f378
    virtual void RefreshPadInfo();  // vt+0x28 0x0010f910 PS3PadDevice_RefreshPadInfo_maybe
    virtual int32_t Update();       // vt+0x2c 0x0010f948 PollPs3ControllerState (XXL2 IKPad::Update)
    virtual uint8_t* GetCurrentState() { return m_ui8VirtualPadValue; }       // vt+0x30 0x9a6820
    virtual uint8_t* GetPreviousState() { return m_ui8OldVirtualPadValue; }   // vt+0x34 0x9a6830
    virtual void SetButtonStates(const uint8_t* values);  // vt+0x38 0x0010f3f0 PS3PadDevice_SetButtonStates_maybe
    // vt+0x3c 0x0010f868 PS3Pad_SetActuator_maybe (XXL2 StartVibration(motor, value)); motor 0 is on/off.
    virtual int32_t StartVibration(int32_t motor, int32_t value);
    // vt+0x40 0x0010f7c0 PadDevice_SetActuator_maybe (XXL2 UpdateVibrationValue): the same body.
    virtual int32_t UpdateVibrationValue(int32_t motor, int32_t value);
    virtual int32_t StopVibration(int32_t motor);      // vt+0x44 0x0010f740 PS3Pad_ClearActuator_maybe
    virtual int32_t StopAllVibration();                // vt+0x48 0x0010f6d0 PS3PadDevice_StopVibration
    virtual int32_t StopHardVibration(int32_t motor);  // vt+0x4c 0x0010f650 PS3PadDevice_StopActuator_maybe
    virtual int32_t Vf50() { return 0; }               // vt+0x50 0x9a6810 KStub_Return0_9a6810
    virtual int32_t Vf54() { return 1; }               // vt+0x54 0x10f498 KStub_Return1_10f498
    virtual int32_t* GetButtonNames() { return m_i32VirtualPadButtonNames; }  // vt+0x58 0x9a6850
    // vt+0x5c 0x9a6840 PS3PadDevice_GetStatusByte_maybe: a motor's value.
    virtual uint8_t GetVibrationValue(int32_t motor) { return m_aui8Motor[motor]; }
    virtual void ClearStates();                        // vt+0x60 0x9a68a0 PS3PadDevice_ClearStates
    virtual void Vf64() {}                             // vt+0x64 0x9a67e8 KStub_Nop_9a67e8
    virtual int32_t GetButtonCount() { return 0x2c; }  // vt+0x68 0x9a6818
    virtual void Vf6C() {}                             // vt+0x6c 0x9a67f0 KStub_Nop_9a67f0
    virtual void SetPressMode(int32_t enabled);        // vt+0x70 0x0010f5c8 PS3PadDevice_SetPressMode
    virtual void SetSensorMode(int32_t enabled);       // vt+0x74 0x0010f540 PS3PadDevice_SetSensorMode
    virtual void Vf78() {}                             // vt+0x78 0x10f4a0 KStub_Nop_10f4a0
    virtual void ResetButtonMap();  // vt+0x7c 0x0010f428 PS3PadDevice_ResetButtonMap_maybe

    uint8_t m_aui8Motor[2];  // +0x110 the two actuator values sent with cellPadSetActDirect
    uint8_t m_bActuator;     // +0x112 the pad has an actuator and rumble is on in the system (Update)
    uint8_t m_bPressMode;    // +0x113 the pad reports pressure (Update; SetPressMode)
    uint8_t m_bSensorMode;   // +0x114 the pad reports its sensors (Update; SetSensorMode)
    uint8_t m_pad115[3];
    CellPadData m_padData;  // +0x118 cellPadGetData's buffer (len, then the button words)
    uint8_t m_unk19c[0x80];
};
DOTD_ASSERT_SIZE(PS3PadDevice, 0x21c);
DOTD_ASSERT_OFFSET(PS3PadDevice, m_bActive, 0x04);
DOTD_ASSERT_OFFSET(PS3PadDevice, m_bVibrationEnabled, 0x06);
DOTD_ASSERT_OFFSET(PS3PadDevice, m_ui8Index, 0x07);
DOTD_ASSERT_OFFSET(PS3PadDevice, m_ui8VirtualPadValue, 0x08);
DOTD_ASSERT_OFFSET(PS3PadDevice, m_ui8OldVirtualPadValue, 0x34);
DOTD_ASSERT_OFFSET(PS3PadDevice, m_i32VirtualPadButtonNames, 0x60);
DOTD_ASSERT_OFFSET(PS3PadDevice, m_aui8Motor, 0x110);
DOTD_ASSERT_OFFSET(PS3PadDevice, m_bActuator, 0x112);
DOTD_ASSERT_OFFSET(PS3PadDevice, m_bSensorMode, 0x114);
DOTD_ASSERT_OFFSET(PS3PadDevice, m_padData, 0x118);

// 0x00cea7d4: the pads' info, refreshed by pad 0 (PS3PadDevice::RefreshPadInfo / Update).
extern CellPadInfo2 g_padInfo2;
// 0x00c40250: system_info bit 0 (CELL_PAD_INFO_INTERCEPTED) of the last cellPadGetInfo2.
extern uint8_t g_padInputIntercepted;
