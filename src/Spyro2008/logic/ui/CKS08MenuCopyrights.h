// CKS08MenuCopyrights.h - the "Menu Copyrights" screen (key 0xaacc, vtable 0xb2c448, size 0xf8 from 0x54a5f8 CKS08MenuCopyrights_Create). DotD only.
// Original unit: CKS08MenuCopyrights.cpp (0x549bb0-0x54ad98).
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKMenuBase114c.h"
#include "k2000/core/Layout.h"

class CKS08MenuCopyrights : public CKMenuBase114c {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2ab)
    DOTD_DECLARE_FACTORIES(CKS08MenuCopyrights)

    CKS08MenuCopyrights() {}  // 0x54a5f8 CKS08MenuCopyrights_Create: the CKMenuBase114c part only
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c9890
        return key == 0xaacc || key == 0x114c || key == 0x730c || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;                                   // vt+0x2c 0x54a6e0 CKS08MenuCopyrights_Load
    void RecursiveRegistration(int32_t type) override;                                  // vt+0x24 0x549cd0 CKS08MenuCopyrights_RecursiveRegistration
    uint32_t GetWidgetSlotCount() override { return 1; }                                 // vt+0x68 0x9c9908
    WidgetSlot* GetWidgetSlots() override { return m_aWidgetSlots; }                     // vt+0x6c 0x9c9910
    const char* GetMenuName() override { return "Menu Copyrights"; }                     // vt+0xb8 0x9c98e0
    uint8_t VfBC() override { return 3; }                                                // vt+0xbc 0x9c98f0
    IKSerializable** VfC0() override { return m_apMessageOuts; }                         // vt+0xc0 0x9c98f8
    uint8_t VfC4() override { return 9; }                                                // vt+0xc4 0x9c9920
    IKSerializable** VfC8() override { return m_apMessageIns; }                          // vt+0xc8 0x9c9928
    uint8_t* VfCC() override { return m_abMessageInFlags; }                              // vt+0xcc 0x9c9938
    // vt+0xdc 0x00549fd0 CKS08MenuCopyrights_OnMenuState_maybe: the copyrights screen: its video looped,
    // shown for m_fDuration (skippable when m_unked), faded in and out through m_pColorizedFx.
    uint8_t OnMenuState(int32_t phase, uint8_t other) override;
    int32_t GetMenuId() override { return 0x4; }                                         // vt+0xe0 0x9c98e8

    WidgetSlot m_aWidgetSlots[1];                // +0x94
    IKSerializable* m_apMessageIns[9];           // +0x9c
    uint8_t m_abMessageInFlags[9];               // +0xc0 MessageProc sets one per VfC8 entry
    uint8_t m_unkc9[3];
    IKSerializable* m_apMessageOuts[3];          // +0xcc
    IKSerializable* m_pText;                     // +0xd8 CKLocTextAccessor (file key 0xe46)
    IKSerializable* m_pUnkdc;                    // +0xdc a reference (by UUID in LVL000)
    IKSerializable* m_pColorizedFx;              // +0xe0 CColorizedScreenFx (file key 0xccd)
    IKSerializable* m_pColorizedData0;           // +0xe4 CColorizedScreenData (file key 0x110c)
    IKSerializable* m_pColorizedData1;           // +0xe8 CColorizedScreenData
    uint8_t m_unkec;                             // +0xec CKS08MenuCopyrights_OnMenuState_maybe 0x549fd0 clears it, sets it when m_fTimer runs out
    uint8_t m_unked;                             // +0xed read by the Load (1 byte)
    uint8_t m_unkee[2];
    float m_fDuration;                           // +0xf0 read by the Load (4.0 in LVL000); OnMenuState_maybe copies it to m_fTimer
    float m_fTimer;                              // +0xf4 run time (OnMenuState_maybe counts it down)
};
DOTD_ASSERT_SIZE(CKS08MenuCopyrights, 0xf8);
DOTD_ASSERT_OFFSET(CKS08MenuCopyrights, m_aWidgetSlots, 0x94);
DOTD_ASSERT_OFFSET(CKS08MenuCopyrights, m_apMessageIns, 0x9c);
DOTD_ASSERT_OFFSET(CKS08MenuCopyrights, m_abMessageInFlags, 0xc0);
DOTD_ASSERT_OFFSET(CKS08MenuCopyrights, m_apMessageOuts, 0xcc);
DOTD_ASSERT_OFFSET(CKS08MenuCopyrights, m_pText, 0xd8);
DOTD_ASSERT_OFFSET(CKS08MenuCopyrights, m_pUnkdc, 0xdc);
DOTD_ASSERT_OFFSET(CKS08MenuCopyrights, m_pColorizedFx, 0xe0);
DOTD_ASSERT_OFFSET(CKS08MenuCopyrights, m_pColorizedData0, 0xe4);
DOTD_ASSERT_OFFSET(CKS08MenuCopyrights, m_pColorizedData1, 0xe8);
DOTD_ASSERT_OFFSET(CKS08MenuCopyrights, m_unkec, 0xec);
DOTD_ASSERT_OFFSET(CKS08MenuCopyrights, m_unked, 0xed);
DOTD_ASSERT_OFFSET(CKS08MenuCopyrights, m_fDuration, 0xf0);
DOTD_ASSERT_OFFSET(CKS08MenuCopyrights, m_fTimer, 0xf4);
