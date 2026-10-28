// CKS08MenuChapter.h - the "Menu Chapter" screen (key 0x8b0c, vtable 0xb2c238, size 0x110 from 0x547868 CKS08MenuChapter_Create). DotD only.
// Original unit: CKS08MenuChapter.cpp (0x547150-0x548a88).
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKMenuBase114c.h"
#include "k2000/core/Layout.h"

class CKS08MenuChapter : public CKMenuBase114c {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x22c)
    DOTD_DECLARE_FACTORIES(CKS08MenuChapter)

    CKS08MenuChapter() {}  // 0x547868 CKS08MenuChapter_Create: the CKMenuBase114c part only
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c96f8
        return key == 0x8b0c || key == 0x114c || key == 0x730c || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;                                   // vt+0x2c 0x5475d0 CKS08MenuChapter_Load
    uint32_t GetWidgetSlotCount() override { return 10; }                                // vt+0x68 0x9c9758
    WidgetSlot* GetWidgetSlots() override { return m_aWidgetSlots; }                     // vt+0x6c 0x9c9760
    const char* GetMenuName() override { return "Menu Chapter"; }                        // vt+0xb8 0x9c9748
    uint8_t VfBC() override { return 1; }                                                // vt+0xbc 0x9c9798
    IKSerializable** VfC0() override { return m_apMessageOuts; }                         // vt+0xc0 0x9c97a0
    uint8_t VfC4() override { return 6; }                                                // vt+0xc4 0x9c9770
    IKSerializable** VfC8() override { return m_apMessageIns; }                          // vt+0xc8 0x9c9778
    uint8_t* VfCC() override { return m_abMessageInFlags; }                              // vt+0xcc 0x9c9788
    int32_t GetMenuId() override { return 0x3; }                                         // vt+0xe0 0x9c9750

    WidgetSlot m_aWidgetSlots[10];               // +0x94
    IKSerializable* m_apMessageIns[6];           // +0xe4
    uint8_t m_abMessageInFlags[6];               // +0xfc MessageProc sets one per VfC8 entry
    uint8_t m_pad102[2];
    IKSerializable* m_apMessageOuts[1];          // +0x104
    uint32_t m_unk108;                           // +0x108 read raw (no swap): the file bytes, e.g. 8b 57 52 9b; a word load sees them big-endian (RGBA colour_maybe)
    uint32_t m_unk10c;                           // +0x10c read raw, like +0x108 (ff ff ff 9b)
};
DOTD_ASSERT_SIZE(CKS08MenuChapter, 0x110);
DOTD_ASSERT_OFFSET(CKS08MenuChapter, m_aWidgetSlots, 0x94);
DOTD_ASSERT_OFFSET(CKS08MenuChapter, m_apMessageIns, 0xe4);
DOTD_ASSERT_OFFSET(CKS08MenuChapter, m_abMessageInFlags, 0xfc);
DOTD_ASSERT_OFFSET(CKS08MenuChapter, m_apMessageOuts, 0x104);
DOTD_ASSERT_OFFSET(CKS08MenuChapter, m_unk108, 0x108);
DOTD_ASSERT_OFFSET(CKS08MenuChapter, m_unk10c, 0x10c);
