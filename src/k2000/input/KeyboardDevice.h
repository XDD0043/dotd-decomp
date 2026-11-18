// KeyboardDevice.h - the keyboard devices CKInput's Load creates (CKInput::m_aKeyboards,
// m_ui8NbKeyboards of them; GAME has none). The members are XXL2's IKKeyboard
// (K/KModules/KIL/KKeyboard/IKKeyboard.h) and the slots match O_CKKeyboard's; the PS3 class (vtable
// 0xb19618, size 0x3f8) has no separate base vtable. Code in input/KeyboardDevice.cpp (0x10f1f8-0x10f2b0).
// The PS3 build reads no keyboard: ReadKeyboard returns 1 and leaves the values as they are (no cell call).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"

class KeyboardDevice {
public:
    KeyboardDevice() {}  // 0x0010f1f8 KeyboardDevice_Construct_maybe: the vtable only
    virtual ~KeyboardDevice() {}                       // vt+0x00 / +0x04 0x10f2a0 / 0x10f270
    virtual int32_t InitializeData(void* params);      // vt+0x08 0x0010f208 KeyboardDevice_Init_maybe
    virtual int32_t Destroy() { return 1; }            // vt+0x0c 0x10f238
    virtual int32_t InitKeyboard() { return 1; }       // vt+0x10 0x10f240
    virtual int32_t ReadKeyboard() { return 1; }       // vt+0x14 0x10f248 KStub_Return1_10f248
    // vt+0x18 0x9a6750 KStub_Nop_9a6750 (XXL2 IKKeyboard::FillKeyInfo(UInt32, UInt32, Bool)).
    virtual void FillKeyInfo(uint32_t /*key*/, uint32_t /*info*/, uint8_t /*down*/) {}
    // vt+0x1c 0x9a6758 KStub_ReturnM1_9a6758 (DotD): the glyph index of key `key` (CKInput_GetActionButtonGlyph_maybe).
    virtual int32_t Vf1c(uint8_t /*key*/) { return -1; }
    virtual int32_t Vf20() { return -1; }              // vt+0x20 0x9a6768 KStub_ReturnM1_9a6768 (DotD)

    uint8_t m_bActive;                              // +0x004
    uint8_t m_ui8InternKeyboardValue[144];          // +0x005
    uint8_t m_ui8VirtualKeyboardValue[144];         // +0x095
    uint8_t m_ui8OldVirtualKeyboardValue[144];      // +0x125
    uint8_t m_pad1b5[3];
    int32_t m_i32VirtualKeyboardButtonNames[144];   // +0x1b8 InitializeData sets -1; the Load copies the names here
};
DOTD_ASSERT_SIZE(KeyboardDevice, 0x3f8);
DOTD_ASSERT_OFFSET(KeyboardDevice, m_ui8VirtualKeyboardValue, 0x95);
DOTD_ASSERT_OFFSET(KeyboardDevice, m_ui8OldVirtualKeyboardValue, 0x125);
DOTD_ASSERT_OFFSET(KeyboardDevice, m_i32VirtualKeyboardButtonNames, 0x1b8);
