// CKS08MenuSelectSlot.h - the "Menu Select Slot" screen (key 0x824c, vtable 0xb2d2b8, size 0x120 from 0x563c40 CKS08MenuSelectSlot_Create). DotD only.
// Original unit: CKS08MenuSelectSlot.cpp (0x5625a0-0x564680).
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKMenuBase114c.h"
#include "k2000/core/Layout.h"

class CKS08MenuSelectSlot : public CKMenuBase114c {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x209)
    DOTD_DECLARE_FACTORIES(CKS08MenuSelectSlot)

    CKS08MenuSelectSlot() {}  // 0x563c40 CKS08MenuSelectSlot_Create: the CKMenuBase114c part only
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ca2d8
        return key == 0x824c || key == 0x114c || key == 0x730c || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;                                   // vt+0x2c 0x563d28 CKS08MenuSelectSlot_Load
    // vt+0x24 0x5637f0 CKS08MenuSelectSlot_RecursiveRegistration: the reference +0x11c first (no null test), then CKMenuBase114c's
    // (0x513c38: KBase730C's, nothing).
    void RecursiveRegistration(int32_t type) override {
        m_pText->RecursiveRegistration(type);
        CKMenuBase114c::RecursiveRegistration(type);
    }
    uint32_t GetWidgetSlotCount() override { return 11; }                                // vt+0x68 0x9ca338
    WidgetSlot* GetWidgetSlots() override { return m_aWidgetSlots; }                     // vt+0x6c 0x9ca340
    const char* GetMenuName() override { return "Menu Select Slot"; }                    // vt+0xb8 0x9ca328
    uint8_t VfBC() override { return 1; }                                                // vt+0xbc 0x9ca378
    IKSerializable** VfC0() override { return m_apMessageOuts; }                         // vt+0xc0 0x9ca380
    uint8_t VfC4() override { return 6; }                                                // vt+0xc4 0x9ca350
    IKSerializable** VfC8() override { return m_apMessageIns; }                          // vt+0xc8 0x9ca358
    uint8_t* VfCC() override { return m_abMessageInFlags; }                              // vt+0xcc 0x9ca368
    int32_t GetMenuId() override { return 0x12; }                                        // vt+0xe0 0x9ca330
    uint8_t GetSelection(uint8_t /*player*/) override { return 0; }                      // vt+0xe4 0x9ca3a0
    // vt+0xdc 0x00563e08 CKS08MenuSelectSlot_OnMenuState_maybe. Update (0): outside the save flow (+0xafc bit 3) the
    // "Flash Manager" button 0x10 pressed on a used slot (+0x110) picks it (+0x115, the game manager's +0xe98); the third
    // message in, once received, sets the next menu (as QueueNextStateAfterSave). Enter (1): the run state cleared, the
    // video resumed, the save / load widgets (slots 8..10) shown and titled, the buttons and the slot info refreshed.
    uint8_t OnMenuState(int32_t phase, uint8_t other) override;
    // vt+0xe8 0x005639d8 CKS08MenuSelectSlot_vfE8: with arg 1, a validated slot item (state 4) is picked (+0x110, the
    // game manager's +0xe98; the back item: +0x116 set, none), a focused one (states 2, 3) shown (RefreshSlotInfo).
    void OnItemState(uint8_t item, uint8_t state, uint8_t arg) override;
    // 0x00562798 CKS08MenuSelectSlot_UpdateSlotButtonStates_maybe: the five slot buttons disabled by the players' save
    // flags (+0xafc bit 2: used, then the +0x09 byte; bit 3: a damaged or unused slot; bit 4: none).
    void UpdateSlotButtonStates();
    // 0x00562be8 CKS08MenuSelectSlot_RefreshSlotInfo_maybe: the selected slot's (+0x110) texts: a damaged save (+0x09)
    // the game manager's vt+0x214 text everywhere, a used one its level, spawn point, completion ("%i/100") and play
    // time ("%d h %d min %d s"), else "---".
    void RefreshSlotInfo();
    uint8_t VfF0() override { return 1; }                                                // vt+0xf0 0x9ca390
    uint8_t VfF4() override { return 5; }                                                // vt+0xf4 0x9ca398 the back item

    WidgetSlot m_aWidgetSlots[11];               // +0x94
    IKSerializable* m_apMessageIns[6];           // +0xec
    uint8_t m_abMessageInFlags[6];               // +0x104 MessageProc sets one per VfC8 entry
    uint8_t m_pad10a[2];
    IKSerializable* m_apMessageOuts[1];          // +0x10c
    uint32_t m_unk110;                           // +0x110
    uint8_t m_unk114;                            // +0x114 CKS08GameManager::VfCC: set, the save-check slot[1] = 2
    uint8_t m_unk115;                            // +0x115 CKS08GameManager::VfCC: set, the save-check slot[1] = 1
    uint8_t m_unk116;                            // +0x116 QueueNextStateAfterSave: set, the main menu (vt+0x2f8) follows
    uint8_t m_unk117;                            // +0x117
    uint8_t m_unk118;                            // +0x118 OnSaveGameDone in game: 1
    uint8_t m_pad119[3];

    // C2.8 save-menu. 0x00563720 CKS08MenuSelectSlot_OnSaveGameDone_maybe: in game (state 7) +0x118 = 1; elsewhere the
    // menu's message out (vt+0xc0 entry 0), when there is one, posted.
    void OnSaveGameDone();
    // 0x00562698 CKS08MenuSelectSlot_QueueNextStateAfterSave_maybe: the game manager's next menu (stack depth 1): none
    // (0x24) in game, else the main menu (+0x116, vt+0x2f8) or menu 6.
    void QueueNextStateAfterSave();
    IKSerializable* m_pText;                     // +0x11c CKLocTextAccessor (file key 0xe46)
};
DOTD_ASSERT_SIZE(CKS08MenuSelectSlot, 0x120);
DOTD_ASSERT_OFFSET(CKS08MenuSelectSlot, m_aWidgetSlots, 0x94);
DOTD_ASSERT_OFFSET(CKS08MenuSelectSlot, m_apMessageIns, 0xec);
DOTD_ASSERT_OFFSET(CKS08MenuSelectSlot, m_abMessageInFlags, 0x104);
DOTD_ASSERT_OFFSET(CKS08MenuSelectSlot, m_apMessageOuts, 0x10c);
DOTD_ASSERT_OFFSET(CKS08MenuSelectSlot, m_pText, 0x11c);
