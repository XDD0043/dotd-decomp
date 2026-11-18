// CKS08MenuMain.h - the "Menu Main" screen (key 0x818c, vtable 0xb2c970, size 0xcc from 0x557a98 CKS08MenuMain_Create). DotD only.
// Original unit: CKS08MenuMain.cpp (0x5572b8-0x5582b8).
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKMenuBase114c.h"
#include "k2000/core/Layout.h"

class CKS08MenuMain : public CKMenuBase114c {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x206)
    DOTD_DECLARE_FACTORIES(CKS08MenuMain)

    CKS08MenuMain() {}  // 0x557a98 CKS08MenuMain_Create: the CKMenuBase114c part only
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c9c40
        return key == 0x818c || key == 0x114c || key == 0x730c || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;                                   // vt+0x2c 0x557b80 CKS08MenuMain_Load
    void RecursiveRegistration(int32_t type) override;                                  // vt+0x24 0x557528 CKS08MenuMain_RecursiveRegistration
    uint32_t GetWidgetSlotCount() override { return 2; }                                 // vt+0x68 0x9c9ce0
    WidgetSlot* GetWidgetSlots() override { return m_aWidgetSlots; }                     // vt+0x6c 0x9c9ce8
    const char* GetMenuName() override { return "Menu Main"; }                           // vt+0xb8 0x9c9c90
    uint8_t VfBC() override { return 1; }                                                // vt+0xbc 0x9c9cc8
    IKSerializable** VfC0() override { return m_apMessageOuts; }                         // vt+0xc0 0x9c9cd0
    uint8_t VfC4() override { return 6; }                                                // vt+0xc4 0x9c9ca0
    IKSerializable** VfC8() override { return m_apMessageIns; }                          // vt+0xc8 0x9c9ca8
    uint8_t* VfCC() override { return m_abMessageInFlags; }                              // vt+0xcc 0x9c9cb8
    // vt+0xdc 0x00557d40 CKS08MenuMain_OnMenuState_maybe: on enter, the interface video's segment from its
    // start, the menu sounds, one player.
    uint8_t OnMenuState(int32_t phase, uint8_t other) override;
    int32_t GetMenuId() override { return 0x9; }                                         // vt+0xe0 0x9c9c98
    uint8_t GetSelection(uint8_t /*player*/) override { return 0; }                      // vt+0xe4 0x9c9cf8
    // vt+0xe8 0x00557708 CKS08MenuMain_vfE8: item 0 validated (state 4, after): the game reset and the
    // flags +0xafc bit 2; item 1: bits 1 and 3 and the manager's +0x64 bit 2 (a load request_maybe).
    void OnItemState(uint8_t item, uint8_t state, uint8_t phase) override;

    // 0x005573b0 CKS08Menu_PlayLoopSounds_maybe: sounds 0 and 1 of m_pSound looped unless playing (the other
    // menus call it on the main menu, the menu table's entry 9).
    void PlayLoopSounds();
    // 0x005574a8 CKS08Menu_PlayEnterSounds_maybe: sounds 2 and 3 of m_pSound played.
    void PlayEnterSounds();

    WidgetSlot m_aWidgetSlots[2];                // +0x94
    IKSerializable* m_apMessageIns[6];           // +0xa4
    uint8_t m_abMessageInFlags[6];               // +0xbc MessageProc sets one per VfC8 entry
    uint8_t m_padc2[2];
    IKSerializable* m_apMessageOuts[1];          // +0xc4
    IKSerializable* m_pSound;                    // +0xc8 CKSoundDictionaryID (file key 0x109)
};
DOTD_ASSERT_SIZE(CKS08MenuMain, 0xcc);
DOTD_ASSERT_OFFSET(CKS08MenuMain, m_aWidgetSlots, 0x94);
DOTD_ASSERT_OFFSET(CKS08MenuMain, m_apMessageIns, 0xa4);
DOTD_ASSERT_OFFSET(CKS08MenuMain, m_abMessageInFlags, 0xbc);
DOTD_ASSERT_OFFSET(CKS08MenuMain, m_apMessageOuts, 0xc4);
DOTD_ASSERT_OFFSET(CKS08MenuMain, m_pSound, 0xc8);
