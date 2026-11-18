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
    // vt+0xdc 0x00548180 CKS08MenuChapter_OnMenuState_maybe: update: the texts of the focused chapter's level (m_unk6c[0]
    // mapped to the main level index); enter: the main menu's loop and enter sounds, the eleven chapters' buttons disabled
    // from the game structure's unlock bytes (+0x23f..+0x24a, from the last).
    uint8_t OnMenuState(int32_t phase, uint8_t other) override;
    int32_t GetMenuId() override { return 0x3; }                                         // vt+0xe0 0x9c9750
    // vt+0xe8 0x00547398 CKS08MenuChapter_vfE8: a chapter validated (state 4, after; not the back item 11): the game state
    // whose spawn point (+0x1c) is the button's state-4 reference made current (vt+0x70, the manager's +0xafc bit 5), then
    // menu 0x20 requested.
    void OnItemState(uint8_t item, uint8_t state, uint8_t phase) override;
    // 0x00547950 CKS08MenuChapter_RefreshChapterTexts_maybe: per collectible type 1, 2, 3, 0, 4 the remaining count in main
    // level `level` into its text variable (GetCounterTextVarTable +0x38..+0x58); widget k's billboard (0..4) and text
    // (5..9) coloured m_unk108 / m_unk10c when none is left, else white (the text's variable colour too).
    void RefreshChapterTexts(uint8_t level);
    uint8_t GetSelection(uint8_t /*player*/) override { return 0; }                      // vt+0xe4 0x9c97c0
    uint8_t VfF0() override { return 1; }                                                // vt+0xf0 0x9c97b0
    uint8_t VfF4() override { return 11; }                                               // vt+0xf4 0x9c97b8 the back item

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
