// CKS08MenuStatsLevel.h - the "Menu Stats Level" screen (key 0xa9cc, vtable 0xb2d6d8, size 0x12c from 0x569878 CKS08MenuStatsLevel_Create). DotD only.
// Original unit: CKS08MenuStatsLevel.cpp (0x568f08-0x56aee8).
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKMenuBase114c.h"
#include "k2000/core/Layout.h"

class CKS08MenuStatsLevel : public CKMenuBase114c {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2a7)
    DOTD_DECLARE_FACTORIES(CKS08MenuStatsLevel)

    CKS08MenuStatsLevel() {}  // 0x569878 CKS08MenuStatsLevel_Create: the CKMenuBase114c part only
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ca5e8
        return key == 0xa9cc || key == 0x114c || key == 0x730c || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;                                   // vt+0x2c 0x569960 CKS08MenuStatsLevel_Load
    uint32_t GetWidgetSlotCount() override { return 13; }                                // vt+0x68 0x9ca688
    WidgetSlot* GetWidgetSlots() override { return m_aWidgetSlots; }                     // vt+0x6c 0x9ca690
    const char* GetMenuName() override { return "Menu Stats Level"; }                    // vt+0xb8 0x9ca638
    uint8_t VfBC() override { return 1; }                                                // vt+0xbc 0x9ca670
    IKSerializable** VfC0() override { return m_apMessageOuts; }                         // vt+0xc0 0x9ca678
    uint8_t VfC4() override { return 6; }                                                // vt+0xc4 0x9ca648
    IKSerializable** VfC8() override { return m_apMessageIns; }                          // vt+0xc8 0x9ca650
    uint8_t* VfCC() override { return m_abMessageInFlags; }                              // vt+0xcc 0x9ca660
    int32_t GetMenuId() override { return 0x15; }                                        // vt+0xe0 0x9ca640

    WidgetSlot m_aWidgetSlots[13];               // +0x94
    IKSerializable* m_apMessageIns[6];           // +0xfc
    uint8_t m_abMessageInFlags[6];               // +0x114 MessageProc sets one per VfC8 entry
    uint8_t m_pad11a[2];
    IKSerializable* m_apMessageOuts[1];          // +0x11c
    uint32_t m_unk120;                           // +0x120 read raw (no swap): the file bytes, e.g. 8b 57 52 9b; a word load sees them big-endian (RGBA colour_maybe)
    uint32_t m_unk124;                           // +0x124 read raw, like +0x120
    IKSerializable* m_pText;                     // +0x128 CKLocTextAccessor (file key 0xe46)
};
DOTD_ASSERT_SIZE(CKS08MenuStatsLevel, 0x12c);
DOTD_ASSERT_OFFSET(CKS08MenuStatsLevel, m_aWidgetSlots, 0x94);
DOTD_ASSERT_OFFSET(CKS08MenuStatsLevel, m_apMessageIns, 0xfc);
DOTD_ASSERT_OFFSET(CKS08MenuStatsLevel, m_abMessageInFlags, 0x114);
DOTD_ASSERT_OFFSET(CKS08MenuStatsLevel, m_apMessageOuts, 0x11c);
DOTD_ASSERT_OFFSET(CKS08MenuStatsLevel, m_unk120, 0x120);
DOTD_ASSERT_OFFSET(CKS08MenuStatsLevel, m_unk124, 0x124);
DOTD_ASSERT_OFFSET(CKS08MenuStatsLevel, m_pText, 0x128);
