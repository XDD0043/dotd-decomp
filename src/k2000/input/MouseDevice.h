// MouseDevice.h - the mouse devices CKInput's Load creates (CKInput::m_aMouses, m_ui8NbMouses of them;
// GAME has none). The members are XXL2's IKMouse (K/KModules/KIL/KMouse/IKMouse.h) and the slots match
// O_CKMouse's; the PS3 class (vtable 0xb19788, size 0x64) has no separate base vtable. Code in
// input/MouseDevice.cpp (0x110038-0x110108). The PS3 build reads no mouse: ReadMouse returns 1 and leaves the
// values as they are (no cell call).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"

class MouseDevice {
public:
    MouseDevice() {}  // 0x00110038 MouseDevice_Construct_maybe: the vtable only
    virtual ~MouseDevice() {}                         // vt+0x00 / +0x04 0x1100f8 / 0x1100c8
    virtual int32_t InitializeData(void* params);     // vt+0x08 0x00110048 MouseDevice_Init_maybe
    virtual int32_t Destroy() { return 1; }           // vt+0x0c 0x110090
    virtual int32_t InitMouse() { return 1; }         // vt+0x10 0x110098
    virtual int32_t ReadMouse() { return 1; }         // vt+0x14 0x1100a0 KStub_Return1_1100a0

    uint8_t m_bActive;                        // +0x04
    uint8_t m_ui8VirtualMouseValue[14];       // +0x05
    uint8_t m_ui8OldVirtualMouseValue[14];    // +0x13
    uint8_t m_pad21[3];
    int32_t m_i32VirtualMouseButtonNames[14]; // +0x24 InitializeData sets -1; the Load copies the names here
    uint8_t m_unk5c[8];                       // +0x5c
};
DOTD_ASSERT_SIZE(MouseDevice, 0x64);
DOTD_ASSERT_OFFSET(MouseDevice, m_ui8VirtualMouseValue, 0x05);
DOTD_ASSERT_OFFSET(MouseDevice, m_ui8OldVirtualMouseValue, 0x13);
DOTD_ASSERT_OFFSET(MouseDevice, m_i32VirtualMouseButtonNames, 0x24);
