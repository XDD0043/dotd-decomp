// CKS08MenuStatsUpgrades.h - the "Menu Stats Upgrades" screen (key 0xad0c, vtable 0xb2d7e0, size 0x26c from 0x56bc60 CKS08MenuStatsUpgrades_Create). DotD only.
// Original unit: CKS08MenuStatsUpgrades.cpp (0x56aee8-0x56cd80).
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKMenuBase114c.h"
#include "k2000/core/Layout.h"

class CKS08MenuStatsUpgrades : public CKMenuBase114c {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2b4)
    DOTD_DECLARE_FACTORIES(CKS08MenuStatsUpgrades)

    CKS08MenuStatsUpgrades() {}  // 0x56bc60 CKS08MenuStatsUpgrades_Create: the CKMenuBase114c part only
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ca6a8
        return key == 0xad0c || key == 0x114c || key == 0x730c || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;                                   // vt+0x2c 0x56ba30 CKS08MenuStatsUpgrades_Load
    // vt+0x24 0x56b5b8 CKS08MenuStatsUpgrades_RecursiveRegistration: the reference +0x268 first (no null test), then CKMenuBase114c's
    // (0x513c38: KBase730C's, nothing).
    void RecursiveRegistration(int32_t type) override {
        m_pUnk268->RecursiveRegistration(type);
        CKMenuBase114c::RecursiveRegistration(type);
    }
    uint32_t GetWidgetSlotCount() override { return 22; }                                // vt+0x68 0x9ca748
    WidgetSlot* GetWidgetSlots() override { return m_aWidgetSlots; }                     // vt+0x6c 0x9ca750
    uint8_t Vf84() override { return 1; }                                                // vt+0x84 0x9ca778
    RefGroup* Vf88() override { return m_aRefGroups; }                                   // vt+0x88 0x9ca780
    IKSerializable** Vf8C(uint32_t group) override { return group == 0 ? m_apGroupRefs : nullptr; }  // vt+0x8c 0x56af38
    GroupState* Vf90(uint32_t group) override { return group == 0 ? m_aGroupStates : nullptr; }  // vt+0x90 0x56af50
    const char* GetMenuName() override { return "Menu Stats Upgrades"; }                 // vt+0xb8 0x9ca6f8
    uint8_t VfBC() override { return 5; }                                                // vt+0xbc 0x9ca730
    IKSerializable** VfC0() override { return m_apMessageOuts; }                         // vt+0xc0 0x9ca738
    uint8_t VfC4() override { return 6; }                                                // vt+0xc4 0x9ca708
    IKSerializable** VfC8() override { return m_apMessageIns; }                          // vt+0xc8 0x9ca710
    uint8_t* VfCC() override { return m_abMessageInFlags; }                              // vt+0xcc 0x9ca720
    int32_t GetMenuId() override { return 0x18; }                                        // vt+0xe0 0x9ca700
    uint8_t GetSelection(uint8_t /*player*/) override { return 0xff; }                   // vt+0xe4 0x9ca770
    uint8_t VfF0() override { return 1; }                                                // vt+0xf0 0x9ca760
    uint8_t VfF4() override { return 0; }                                                // vt+0xf4 0x9ca768 the back item

    // vt+0xdc 0x0056cb20 CKS08MenuStatsUpgrades_OnMenuState_maybe: enter (1) / leave (2) the group's dynamic references
    // and states cleared (enter then the rows and counters refreshed); update (0) the page inputs.
    uint8_t OnMenuState(int32_t phase, uint8_t other) override;
    void OnItemState(uint8_t item, uint8_t state, uint8_t arg) override;  // vt+0xe8 0x0056b570 (Ghidra OnItemEvent)
    // 0x0056b328 CKS08MenuStatsUpgrades_HandlePageInput_maybe: for each active player, action 10 (player 2: + 0x14) goes to
    // menu 10, action 11 to menu 0x15, each with the objectives menu's confirm sound (menu table entry 10).
    void HandlePageInput();
    // 0x0056af68 CKS08MenuStatsUpgrades_RefreshUpgradeRowGroup_maybe: the `count` widget slots from `first`; for each of the
    // first `lit` the row's message (VfC0 entry 1..4 for the rows 0, 4, 9, 14) placed in the group's first free (or its
    // own) reference, its state the slot's element offset (x, y).
    void RefreshUpgradeRowGroup(uint32_t first, uint32_t lit, uint32_t count);
    // 0x0056c230 CKS08MenuStatsUpgrades_RefreshUpgradeTexts_maybe: the four rows (health / mana of each dragon: the items
    // toward the next upgrade lit out of the divisor), then the upgrades earned / possible into the variables 40..47 and
    // the counts (slots 18..21) coloured +0x17c when complete, else white.
    void RefreshUpgradeTexts();

    WidgetSlot m_aWidgetSlots[22];               // +0x94
    IKSerializable* m_apMessageIns[6];           // +0x144
    uint8_t m_abMessageInFlags[6];               // +0x15c MessageProc sets one per VfC8 entry
    uint8_t m_unk162[2];
    IKSerializable* m_apMessageOuts[5];          // +0x164
    uint32_t m_unk178;                           // +0x178 read raw (no swap): a word load sees the file bytes big-endian
    uint32_t m_unk17c;                           // +0x17c read raw, like +0x178
    RefGroup m_aRefGroups[1];                    // +0x180
    IKSerializable* m_apGroupRefs[18];           // +0x190 Vf8C(0); the Load clears [m_unk04, m_unk08)
    GroupState m_aGroupStates[18];               // +0x1d8 Vf90(0); the Load clears the first m_unk08
    IKSerializable* m_pUnk268;                   // +0x268 a reference
};
DOTD_ASSERT_SIZE(CKS08MenuStatsUpgrades, 0x26c);
DOTD_ASSERT_OFFSET(CKS08MenuStatsUpgrades, m_aWidgetSlots, 0x94);
DOTD_ASSERT_OFFSET(CKS08MenuStatsUpgrades, m_apMessageIns, 0x144);
DOTD_ASSERT_OFFSET(CKS08MenuStatsUpgrades, m_abMessageInFlags, 0x15c);
DOTD_ASSERT_OFFSET(CKS08MenuStatsUpgrades, m_apMessageOuts, 0x164);
DOTD_ASSERT_OFFSET(CKS08MenuStatsUpgrades, m_unk178, 0x178);
DOTD_ASSERT_OFFSET(CKS08MenuStatsUpgrades, m_unk17c, 0x17c);
DOTD_ASSERT_OFFSET(CKS08MenuStatsUpgrades, m_aRefGroups, 0x180);
DOTD_ASSERT_OFFSET(CKS08MenuStatsUpgrades, m_apGroupRefs, 0x190);
DOTD_ASSERT_OFFSET(CKS08MenuStatsUpgrades, m_aGroupStates, 0x1d8);
DOTD_ASSERT_OFFSET(CKS08MenuStatsUpgrades, m_pUnk268, 0x268);
