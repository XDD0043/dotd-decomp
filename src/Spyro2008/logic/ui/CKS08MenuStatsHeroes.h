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
    uint8_t GetSelection(uint8_t /*player*/) override { return 0xff; }                   // vt+0xe4 0x9ca5e0
    uint8_t VfF0() override { return 1; }                                                // vt+0xf0 0x9ca5d0
    uint8_t VfF4() override { return 0; }                                                // vt+0xf4 0x9ca5d8 the back item

    // vt+0xdc 0x00568cc0 CKS08MenuStatsHeroes_OnMenuState_maybe: update (0) the page inputs; enter (1) the two dragons'
    // play time variables (31..33, 37..39 of the counter table) set to 2, then the statistics refreshed.
    uint8_t OnMenuState(int32_t phase, uint8_t other) override;
    void OnItemState(uint8_t item, uint8_t state, uint8_t arg) override;  // vt+0xe8 0x00567b00 (Ghidra OnItemEvent)
    // 0x005678b8 CKS08MenuStatsHeroes_HandlePageInput_maybe: for each active player, action 10 (player 2: + 0x14) goes to
    // menu 0x13, action 11 to menu 10, each with the objectives menu's confirm sound (menu table entry 10).
    void HandlePageInput();
    // 0x005683a8 CKS08MenuStatsHeroes_RefreshStatTexts_maybe: per dragon the upgrade points, the best combo, the kills, the
    // most used element's name (slots 0 and 1: the game manager's +0xf04 texts, dragon 1 from entry 5) and the play time
    // (hours, minutes, seconds) into the counter table's variables 28.. / 34.. (each set only when changed).
    void RefreshStatTexts();

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
