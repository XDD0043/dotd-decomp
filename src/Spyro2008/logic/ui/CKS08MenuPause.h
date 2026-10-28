// CKS08MenuPause.h - the "Menu Pause" screen (key 0x838c, vtable 0xb2cfa0, size 0xfc from 0x55e9a0 CKS08MenuPause_Create). DotD only.
// Original unit: CKS08MenuPause.cpp (0x55da70-0x55f7a0).
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKMenuBase114c.h"
#include "k2000/core/Layout.h"

class CKS08MenuPause : public CKMenuBase114c {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x20e)
    DOTD_DECLARE_FACTORIES(CKS08MenuPause)

    CKS08MenuPause() {}  // 0x55e9a0 CKS08MenuPause_Create: the CKMenuBase114c part only
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ca0a0
        return key == 0x838c || key == 0x114c || key == 0x730c || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;                                   // vt+0x2c 0x55e208 CKS08MenuPause_Load
    uint32_t GetWidgetSlotCount() override { return 6; }                                 // vt+0x68 0x9ca140
    WidgetSlot* GetWidgetSlots() override { return m_aWidgetSlots; }                     // vt+0x6c 0x9ca148
    const char* GetMenuName() override { return "Menu Pause"; }                          // vt+0xb8 0x9ca0f0
    uint8_t VfBC() override { return 1; }                                                // vt+0xbc 0x9ca128
    IKSerializable** VfC0() override { return m_apMessageOuts; }                         // vt+0xc0 0x9ca130
    uint8_t VfC4() override { return 6; }                                                // vt+0xc4 0x9ca100
    IKSerializable** VfC8() override { return m_apMessageIns; }                          // vt+0xc8 0x9ca108
    uint8_t* VfCC() override { return m_abMessageInFlags; }                              // vt+0xcc 0x9ca118
    int32_t GetMenuId() override { return 0xf; }                                         // vt+0xe0 0x9ca0f8

    WidgetSlot m_aWidgetSlots[6];                // +0x94
    IKSerializable* m_apMessageIns[6];           // +0xc4
    uint8_t m_abMessageInFlags[6];               // +0xdc MessageProc sets one per VfC8 entry
    uint8_t m_pade2[2];
    IKSerializable* m_apMessageOuts[1];          // +0xe4
    uint32_t m_unke8[4];                         // +0xe8
    IKSerializable* m_pSound;                    // +0xf8 CKSoundDictionaryID (file key 0x109)
};
DOTD_ASSERT_SIZE(CKS08MenuPause, 0xfc);
DOTD_ASSERT_OFFSET(CKS08MenuPause, m_aWidgetSlots, 0x94);
DOTD_ASSERT_OFFSET(CKS08MenuPause, m_apMessageIns, 0xc4);
DOTD_ASSERT_OFFSET(CKS08MenuPause, m_abMessageInFlags, 0xdc);
DOTD_ASSERT_OFFSET(CKS08MenuPause, m_apMessageOuts, 0xe4);
DOTD_ASSERT_OFFSET(CKS08MenuPause, m_pSound, 0xf8);
