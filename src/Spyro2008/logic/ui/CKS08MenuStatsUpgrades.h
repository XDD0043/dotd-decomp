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
