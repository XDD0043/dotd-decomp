// CKS08MenuPause.h - the "Menu Pause" screen (key 0x838c, vtable 0xb2cfa0, size 0xfc from 0x55e9a0 CKS08MenuPause_Create). DotD only.
// Original unit: CKS08MenuPause.cpp (0x55da70-0x55f7a0).
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKMenuBase114c.h"
#include "k2000/core/Layout.h"

class CKS08MenuPause : public CKMenuBase114c {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x20e)
    DOTD_DECLARE_FACTORIES(CKS08MenuPause)

    CKS08MenuPause() {}  // 0x55e9a0 CKS08MenuPause_Create: the CKMenuBase114c part only
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ca0a0
        return key == 0x838c || key == 0x114c || key == 0x730c || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;                                   // vt+0x2c 0x55e208 CKS08MenuPause_Load
    void RecursiveRegistration(int32_t type) override;                                  // vt+0x24 0x55e3c8 CKS08MenuPause_RecursiveRegistration
    uint32_t GetWidgetSlotCount() override { return 6; }                                 // vt+0x68 0x9ca140
    WidgetSlot* GetWidgetSlots() override { return m_aWidgetSlots; }                     // vt+0x6c 0x9ca148
    const char* GetMenuName() override { return "Menu Pause"; }                          // vt+0xb8 0x9ca0f0
    uint8_t VfBC() override { return 1; }                                                // vt+0xbc 0x9ca128
    IKSerializable** VfC0() override { return m_apMessageOuts; }                         // vt+0xc0 0x9ca130
    uint8_t VfC4() override { return 6; }                                                // vt+0xc4 0x9ca100
    IKSerializable** VfC8() override { return m_apMessageIns; }                          // vt+0xc8 0x9ca108
    uint8_t* VfCC() override { return m_abMessageInFlags; }                              // vt+0xcc 0x9ca118
    int32_t GetMenuId() override { return 0xf; }                                         // vt+0xe0 0x9ca0f8
    uint8_t VfF0() override { return 1; }                                                // vt+0xf0 0x9ca158 HasBackItem
    uint8_t VfF4() override { return 6; }                                                // vt+0xf4 0x9ca160 GetBackItemIndex
    // vt+0x1c 0x0055e028 CKS08MenuPause_MessageProc: the base's (KBase730C_MessageProc), then the message box's answer
    // (0x2d00): yes (5) to the quit question either quits (the game manager's vt+0x2ec, game state 7 requested) or, when
    // the game manager's VfC4 (+0xafc bit 5) is set, goes to menu 0x15 with +0xafc bit 9 (the save the pause state makes
    // when it ends). Returns 3 or 2 when the base did, 0 when the base did not handle it, else whether it was not 0x2d00.
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0xdc 0x0055f2c0 CKS08MenuPause_OnStatePhase: enter (1): both players' input on (the second with two players),
    // the cheat codes' progress and timer cleared, the menu's sounds 0 and 1 started unless playing. Tick (0): the cheat
    // codes (UpdateCheatInput_maybe, inlined there). Returns the menu id.
    uint8_t OnMenuState(int32_t phase, uint8_t other) override;
    // vt+0xe8 0x0055e6b0 CKS08MenuPause_OnItemEvent: item 0 (the resume item, a CKInterfaceButtonDouble) validated
    // (state 5): the game manager's +0x270 = its entry + 1 (the player count to switch to) and game state 7 requested;
    // item 4 validated: the options kept (BackupOptions) and menu 0x17 (the options); item 5 once its validation delay
    // ends (state 4, arg 2): the quit question (text 14, or 15 with the game manager's VfC4, of its text accessor
    // +0x144) in a yes / no message box that answers this menu (MessageProc); item 6 validated (the back item, circle):
    // the menu's sounds 0 and 1 stopped and game state 7 requested.
    void OnItemState(uint8_t item, uint8_t state, uint8_t arg) override;
    // vt+0xec 0x0055e5b0 CKS08MenuPause_vfEC: the first button (item 0) opening shows the game manager's +0x270 - 1
    // (else the player count - 1; 0xff without players).
    void VfEC(IKSerializable* button) override;
    // 0x0055ebd0 CKS08MenuPause_UpdateCheatInput_maybe (the original's out-of-line copy; OnStatePhase has it inlined):
    // while the timer runs it counts down; otherwise each of the seven codes (hold kCheatFirst[i], then press the five
    // kCheatSteps[i] in turn, no other of the actions 0..0x17 pressed) moves on one step per press with a 0.3 s timer,
    // the fifth applies it (ApplyCheatCode); a wrong press restarts the code (step 1 when it is the first step).
    void UpdateCheatInput();
    // 0x0055dd18 CKS08MenuPause_ApplyCheatCode_maybe: code 0 toggles the game manager's flags +0x64 bit 8, 1 bit 23,
    // 2 gives the upgrade points (CheatMaxUpgradePoints_maybe), 3 toggles +0xafc bit 8, 4 +0x64 bit 26, 5 bit 25 (the
    // dragons' health and mana restored, with the bit set their armour slots 0..2 set to armour 0), 6 bit 24 (the fury
    // gauge filled for both dragons); then the game manager's sound 0xb (dictionary +0xbdc) played centred.
    void ApplyCheatCode(uint8_t code);

    WidgetSlot m_aWidgetSlots[6];                // +0x94
    IKSerializable* m_apMessageIns[6];           // +0xc4
    uint8_t m_abMessageInFlags[6];               // +0xdc MessageProc sets one per VfC8 entry
    uint8_t m_pade2[2];
    IKSerializable* m_apMessageOuts[1];          // +0xe4
    uint32_t m_unke8;                            // +0xe8 (not written by this unit)
    uint8_t m_abCheatSteps[7];                   // +0xec each cheat code's progress (0..4); OnStatePhase clears them
    uint8_t m_padf3;
    float m_fCheatTimer;                         // +0xf4 the delay after a code's step (0.3 s); OnStatePhase clears it
    IKSerializable* m_pSound;                    // +0xf8 CKSoundDictionaryID (file key 0x109)
};
DOTD_ASSERT_SIZE(CKS08MenuPause, 0xfc);
DOTD_ASSERT_OFFSET(CKS08MenuPause, m_aWidgetSlots, 0x94);
DOTD_ASSERT_OFFSET(CKS08MenuPause, m_apMessageIns, 0xc4);
DOTD_ASSERT_OFFSET(CKS08MenuPause, m_abMessageInFlags, 0xdc);
DOTD_ASSERT_OFFSET(CKS08MenuPause, m_apMessageOuts, 0xe4);
DOTD_ASSERT_OFFSET(CKS08MenuPause, m_abCheatSteps, 0xec);
DOTD_ASSERT_OFFSET(CKS08MenuPause, m_fCheatTimer, 0xf4);
DOTD_ASSERT_OFFSET(CKS08MenuPause, m_pSound, 0xf8);
