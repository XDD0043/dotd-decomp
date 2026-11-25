// CKS08MenuGame.h - the "Menu Game" screen (key 0x82cc, vtable 0xb2c658, size 0xec from 0x5547a8 CKS08MenuGame_Create). DotD only.
// Original unit: CKS08MenuGame.cpp (0x553bc8-0x5554c8).
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKMenuBase114c.h"
#include "k2000/core/Layout.h"

class CKS08MenuGame : public CKMenuBase114c {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x20b)
    DOTD_DECLARE_FACTORIES(CKS08MenuGame)

    CKS08MenuGame() {}  // 0x5547a8 CKS08MenuGame_Create: the CKMenuBase114c part only
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c9a10
        return key == 0x82cc || key == 0x114c || key == 0x730c || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;                                   // vt+0x2c 0x5549d0 CKS08MenuGame_Load
    void RecursiveRegistration(int32_t type) override;                                  // vt+0x24 0x554148 CKS08MenuGame_RecursiveRegistration
    uint32_t GetWidgetSlotCount() override { return 5; }                                 // vt+0x68 0x9c9ab0
    WidgetSlot* GetWidgetSlots() override { return m_aWidgetSlots; }                     // vt+0x6c 0x9c9ab8
    const char* GetMenuName() override { return "Menu Game"; }                           // vt+0xb8 0x9c9a60
    uint8_t VfBC() override { return 1; }                                                // vt+0xbc 0x9c9a98
    IKSerializable** VfC0() override { return m_apMessageOuts; }                         // vt+0xc0 0x9c9aa0
    uint8_t VfC4() override { return 6; }                                                // vt+0xc4 0x9c9a70
    IKSerializable** VfC8() override { return m_apMessageIns; }                          // vt+0xc8 0x9c9a78
    uint8_t* VfCC() override { return m_abMessageInFlags; }                              // vt+0xcc 0x9c9a88
    // vt+0xdc 0x00554328 CKS08MenuGame_OnMenuState_maybe: on enter, the main menu's sounds, the video
    // (when the interface video is not playing), items 0 and 1 disabled from the game structure's
    // +0x24a / +0x23f, the players.
    uint8_t OnMenuState(int32_t phase, uint8_t other) override;
    int32_t GetMenuId() override { return 0x6; }                                         // vt+0xe0 0x9c9a68
    // vt+0xe8 0x005545b0 CKS08MenuGame_OnItemEvent: item 0 validated: the start-player menu (0x23); item 3:
    // the options (0x19), the options backed up first.
    void OnItemState(uint8_t item, uint8_t state, uint8_t phase) override;
    // vt+0xec 0x00554b90 CKS08MenuGame_vfEC (from CKInterfaceButton_Open): for its first button, the text of
    // states 0, 2 and 4 chosen from m_pText: entry 2 with the game structure's +0x24a, else entry 1 when
    // a dragon's play time (+0x144 / +0x148) reached 1.0, else entry 0 (New / Continue game_maybe).
    void VfEC(IKSerializable* button) override;
    // 0x00554de8 CKS08MenuGame_UpdateSecretCodeInput_maybe: dead in the original (no call, no descriptor reference;
    // OnMenuState still clears its state). dotd calls it from OnMenuState's update phase, the way CKS08MenuPause's
    // live copy runs (outputs/hidden-debug-features.md section 3). One code, pad 0: hold kSecretFirst (L1), then
    // the five kSecretSteps (left stick left, right, right, up, up), no other of the actions 0..0x17 pressed,
    // 0.3 s between steps; the fifth calls SetAllUnlockFlags(0).
    void UpdateSecretCodeInput();
    // 0x00553ee0 CKS08MenuGame_SetAllUnlockFlags_maybe (dead in the original, reached only from the above): with
    // `which` 0 the game structure's twelve unlock bytes (+0x23f..+0x24a) set, items 0 and 1 enabled (vt+0x84),
    // the game manager's sound 0xb (dictionary +0xbdc) played centred. Other values do nothing.
    void SetAllUnlockFlags(int32_t which);

    WidgetSlot m_aWidgetSlots[5];                // +0x94
    IKSerializable* m_apMessageIns[6];           // +0xbc
    uint8_t m_abMessageInFlags[6];               // +0xd4 MessageProc sets one per VfC8 entry
    uint8_t m_padda[2];
    IKSerializable* m_apMessageOuts[1];          // +0xdc
    IKSerializable* m_pText;                     // +0xe0 CKLocTextAccessor (file key 0xe46)
    uint8_t m_ui8SecretStep;                     // +0xe4 the secret code's progress (0..4); OnMenuState (enter) clears it
    uint8_t m_pade5[3];
    float m_fSecretTimer;                        // +0xe8 the delay after a step (0.3 s); OnMenuState (enter) clears it
};
DOTD_ASSERT_SIZE(CKS08MenuGame, 0xec);
DOTD_ASSERT_OFFSET(CKS08MenuGame, m_aWidgetSlots, 0x94);
DOTD_ASSERT_OFFSET(CKS08MenuGame, m_apMessageIns, 0xbc);
DOTD_ASSERT_OFFSET(CKS08MenuGame, m_abMessageInFlags, 0xd4);
DOTD_ASSERT_OFFSET(CKS08MenuGame, m_apMessageOuts, 0xdc);
DOTD_ASSERT_OFFSET(CKS08MenuGame, m_pText, 0xe0);
