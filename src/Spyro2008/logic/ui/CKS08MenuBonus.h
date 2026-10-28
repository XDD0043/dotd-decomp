// CKS08MenuBonus.h - the "Menu Bonus" screen (key 0x830c, vtable 0xb2d9f0, size 0xd0 from 0x56e0f0 CKS08MenuBonus_Create). DotD only.
// Original unit: CKS08MenuBonus.cpp (0x56d6b8-0x56eb18).
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKMenuBase114c.h"

class IKVideo;
#include "k2000/core/Layout.h"

class CKS08MenuBonus : public CKMenuBase114c {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x20c)
    DOTD_DECLARE_FACTORIES(CKS08MenuBonus)

    CKS08MenuBonus() {}  // 0x56e0f0 CKS08MenuBonus_Create: the CKMenuBase114c part only
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ca830
        return key == 0x830c || key == 0x114c || key == 0x730c || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;                                   // vt+0x2c 0x56dd20 CKS08MenuBonus_Load
    uint32_t GetWidgetSlotCount() override { return 2; }                                 // vt+0x68 0x9ca8d0
    WidgetSlot* GetWidgetSlots() override { return m_aWidgetSlots; }                     // vt+0x6c 0x9ca8d8
    const char* GetMenuName() override { return "Menu Bonus"; }                          // vt+0xb8 0x9ca880
    uint8_t VfBC() override { return 1; }                                                // vt+0xbc 0x9ca8b8
    IKSerializable** VfC0() override { return m_apMessageOuts; }                         // vt+0xc0 0x9ca8c0
    uint8_t VfC4() override { return 6; }                                                // vt+0xc4 0x9ca890
    IKSerializable** VfC8() override { return m_apMessageIns; }                          // vt+0xc8 0x9ca898
    uint8_t* VfCC() override { return m_abMessageInFlags; }                              // vt+0xcc 0x9ca8a8
    // vt+0xdc 0x0056e1d8 CKS08MenuBonus_OnMenuState_maybe: enter: the eight bonus items enabled from the game
    // structure's unlock bytes (+0x24b..+0x250; items 4 and 5 always); update: a bonus video one of the items
    // started (state 4's first video playing) takes over, the menu's input blocked (flags bit 4).
    uint8_t OnMenuState(int32_t phase, uint8_t other) override;
    int32_t GetMenuId() override { return 0x2; }                                         // vt+0xe0 0x9ca888
    void OnItemState(uint8_t /*item*/, uint8_t /*state*/, uint8_t /*phase*/) override {}  // vt+0xe8 0x56d7b0 (empty)

    // 0x0056daa8 CKS08MenuBonus_UpdateVideoPlayback_maybe: the bonus video ended or skipped (vt+0x1e4: then
    // stopped), the interface video replayed and the input given back.
    void UpdateVideoPlayback();

    WidgetSlot m_aWidgetSlots[2];                // +0x94
    IKSerializable* m_apMessageIns[6];           // +0xa4
    uint8_t m_abMessageInFlags[6];               // +0xbc MessageProc sets one per VfC8 entry
    uint8_t m_padc2[2];
    IKSerializable* m_apMessageOuts[1];          // +0xc4
    uint8_t m_bVideoPlaying;                     // +0xc8 a bonus video plays
    uint8_t m_padc9[3];
    IKVideo* m_pVideo;                           // +0xcc the bonus video
};
DOTD_ASSERT_SIZE(CKS08MenuBonus, 0xd0);
DOTD_ASSERT_OFFSET(CKS08MenuBonus, m_aWidgetSlots, 0x94);
DOTD_ASSERT_OFFSET(CKS08MenuBonus, m_apMessageIns, 0xa4);
DOTD_ASSERT_OFFSET(CKS08MenuBonus, m_abMessageInFlags, 0xbc);
DOTD_ASSERT_OFFSET(CKS08MenuBonus, m_apMessageOuts, 0xc4);
DOTD_ASSERT_OFFSET(CKS08MenuBonus, m_bVideoPlaying, 0xc8);
DOTD_ASSERT_OFFSET(CKS08MenuBonus, m_pVideo, 0xcc);
