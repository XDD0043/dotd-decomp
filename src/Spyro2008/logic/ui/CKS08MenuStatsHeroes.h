// CKS08MenuStatsHeroes.h - the "Menu Stats Heroes" screen (key 0xa98c, vtable 0xb2d5d0, size 0xc8 from 0x567f18 CKS08MenuStatsHeroes_Create). DotD only.
// Original unit: CKS08MenuStatsHeroes.cpp (0x567768-0x568f08).
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKMenuBase114c.h"
#include "k2000/core/Layout.h"

class CKS08MenuStatsHeroes : public CKMenuBase114c {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2a6)
    DOTD_DECLARE_FACTORIES(CKS08MenuStatsHeroes)

    CKS08MenuStatsHeroes() {}  // 0x567f18 CKS08MenuStatsHeroes_Create: the CKMenuBase114c part only
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ca518
        return key == 0xa98c || key == 0x114c || key == 0x730c || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;                                   // vt+0x2c 0x567b48 CKS08MenuStatsHeroes_Load
    uint32_t GetWidgetSlotCount() override { return 2; }                                 // vt+0x68 0x9ca5b8
    WidgetSlot* GetWidgetSlots() override { return m_aWidgetSlots; }                     // vt+0x6c 0x9ca5c0
    const char* GetMenuName() override { return "Menu Stats Heroes"; }                   // vt+0xb8 0x9ca568
    uint8_t VfBC() override { return 1; }                                                // vt+0xbc 0x9ca5a0
    IKSerializable** VfC0() override { return m_apMessageOuts; }                         // vt+0xc0 0x9ca5a8
    uint8_t VfC4() override { return 6; }                                                // vt+0xc4 0x9ca578
    IKSerializable** VfC8() override { return m_apMessageIns; }                          // vt+0xc8 0x9ca580
    uint8_t* VfCC() override { return m_abMessageInFlags; }                              // vt+0xcc 0x9ca590
    int32_t GetMenuId() override { return 0x14; }                                        // vt+0xe0 0x9ca570

    WidgetSlot m_aWidgetSlots[2];                // +0x94
    IKSerializable* m_apMessageIns[6];           // +0xa4
    uint8_t m_abMessageInFlags[6];               // +0xbc MessageProc sets one per VfC8 entry
    uint8_t m_padc2[2];
    IKSerializable* m_apMessageOuts[1];          // +0xc4
};
DOTD_ASSERT_SIZE(CKS08MenuStatsHeroes, 0xc8);
DOTD_ASSERT_OFFSET(CKS08MenuStatsHeroes, m_aWidgetSlots, 0x94);
DOTD_ASSERT_OFFSET(CKS08MenuStatsHeroes, m_apMessageIns, 0xa4);
DOTD_ASSERT_OFFSET(CKS08MenuStatsHeroes, m_abMessageInFlags, 0xbc);
DOTD_ASSERT_OFFSET(CKS08MenuStatsHeroes, m_apMessageOuts, 0xc4);
