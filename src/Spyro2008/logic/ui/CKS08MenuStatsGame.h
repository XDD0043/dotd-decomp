// CKS08MenuStatsGame.h - the "Menu Stats Game" screen (key 0xaa0c, vtable 0xb2d4c8, size 0x144 from 0x565ac0 CKS08MenuStatsGame_Create). DotD only.
// Original unit: CKS08MenuStatsGame.cpp (0x565218-0x567768).
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKMenuBase114c.h"
#include "k2000/core/Layout.h"

class CKS08MenuStatsGame : public CKMenuBase114c {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2a8)
    DOTD_DECLARE_FACTORIES(CKS08MenuStatsGame)

    CKS08MenuStatsGame() {}  // 0x565ac0 CKS08MenuStatsGame_Create: the CKMenuBase114c part only
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ca458
        return key == 0xaa0c || key == 0x114c || key == 0x730c || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;                                   // vt+0x2c 0x565ce8 CKS08MenuStatsGame_Load
    uint32_t GetWidgetSlotCount() override { return 16; }                                // vt+0x68 0x9ca4f8
    WidgetSlot* GetWidgetSlots() override { return m_aWidgetSlots; }                     // vt+0x6c 0x9ca500
    const char* GetMenuName() override { return "Menu Stats Game"; }                     // vt+0xb8 0x9ca4a8
    uint8_t VfBC() override { return 1; }                                                // vt+0xbc 0x9ca4e0
    IKSerializable** VfC0() override { return m_apMessageOuts; }                         // vt+0xc0 0x9ca4e8
    uint8_t VfC4() override { return 6; }                                                // vt+0xc4 0x9ca4b8
    IKSerializable** VfC8() override { return m_apMessageIns; }                          // vt+0xc8 0x9ca4c0
    uint8_t* VfCC() override { return m_abMessageInFlags; }                              // vt+0xcc 0x9ca4d0
    int32_t GetMenuId() override { return 0x13; }                                        // vt+0xe0 0x9ca4b0

    WidgetSlot m_aWidgetSlots[16];               // +0x94
    IKSerializable* m_apMessageIns[6];           // +0x114
    uint8_t m_abMessageInFlags[6];               // +0x12c MessageProc sets one per VfC8 entry
    uint8_t m_pad132[2];
    IKSerializable* m_apMessageOuts[1];          // +0x134
    uint32_t m_unk138;                           // +0x138 read raw (no swap): the file bytes, e.g. 8b 57 52 9b; a word load sees them big-endian (RGBA colour_maybe)
    uint32_t m_unk13c;                           // +0x13c read raw, like +0x138
    IKSerializable* m_pText;                     // +0x140 CKLocTextAccessor (file key 0xe46)
};
DOTD_ASSERT_SIZE(CKS08MenuStatsGame, 0x144);
DOTD_ASSERT_OFFSET(CKS08MenuStatsGame, m_aWidgetSlots, 0x94);
DOTD_ASSERT_OFFSET(CKS08MenuStatsGame, m_apMessageIns, 0x114);
DOTD_ASSERT_OFFSET(CKS08MenuStatsGame, m_abMessageInFlags, 0x12c);
DOTD_ASSERT_OFFSET(CKS08MenuStatsGame, m_apMessageOuts, 0x134);
DOTD_ASSERT_OFFSET(CKS08MenuStatsGame, m_unk138, 0x138);
DOTD_ASSERT_OFFSET(CKS08MenuStatsGame, m_unk13c, 0x13c);
DOTD_ASSERT_OFFSET(CKS08MenuStatsGame, m_pText, 0x140);
