// CKS08MenuPressStart.h - the "Menu PressStart" screen (key 0x814c, vtable 0xb2d1b0, size 0x104 from 0x561e10 CKS08MenuPressStart_Create). DotD only.
// Original unit: CKS08MenuPressStart.cpp (0x560f38-0x5625a0).
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKMenuBase114c.h"
#include "k2000/core/Layout.h"

class CKS08MenuPressStart : public CKMenuBase114c {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x205)
    DOTD_DECLARE_FACTORIES(CKS08MenuPressStart)

    CKS08MenuPressStart() {}  // 0x561e10 CKS08MenuPressStart_Create: the CKMenuBase114c part only
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ca220
        return key == 0x814c || key == 0x114c || key == 0x730c || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;                                   // vt+0x2c 0x561ef8 CKS08MenuPressStart_Load
    uint32_t GetWidgetSlotCount() override { return 1; }                                 // vt+0x68 0x9ca298
    WidgetSlot* GetWidgetSlots() override { return m_aWidgetSlots; }                     // vt+0x6c 0x9ca2a0
    const char* GetMenuName() override { return "Menu PressStart"; }                     // vt+0xb8 0x9ca270
    uint8_t VfBC() override { return 4; }                                                // vt+0xbc 0x9ca280
    IKSerializable** VfC0() override { return m_apMessageOuts; }                         // vt+0xc0 0x9ca288
    uint8_t VfC4() override { return 9; }                                                // vt+0xc4 0x9ca2b0
    IKSerializable** VfC8() override { return m_apMessageIns; }                          // vt+0xc8 0x9ca2b8
    uint8_t* VfCC() override { return m_abMessageInFlags; }                              // vt+0xcc 0x9ca2c8
    // vt+0xdc 0x005613b8 CKS08MenuPressStart_OnMenuState_maybe: the press-start screen (its video looped,
    // START or the movie's message-in 3 leaves it with the fade-out; 30 s idle plays the demo video).
    uint8_t OnMenuState(int32_t phase, uint8_t other) override;
    int32_t GetMenuId() override { return 0x11; }                                        // vt+0xe0 0x9ca278

    WidgetSlot m_aWidgetSlots[1];                // +0x94
    IKSerializable* m_apMessageIns[9];           // +0x9c
    uint8_t m_abMessageInFlags[9];               // +0xc0 MessageProc sets one per VfC8 entry
    uint8_t m_unkc9[3];
    IKSerializable* m_apMessageOuts[4];          // +0xcc
    IKSerializable* m_pText;                     // +0xdc CKLocTextAccessor (file key 0xe46)
    IKSerializable* m_pUnke0;                    // +0xe0 a reference (by UUID in LVL000)
    IKSerializable* m_pColorizedFx;              // +0xe4 CColorizedScreenFx (file key 0xccd)
    IKSerializable* m_pColorizedData0;           // +0xe8 CColorizedScreenData (file key 0x110c)
    IKSerializable* m_pColorizedData1;           // +0xec CColorizedScreenData
    float m_fUnkf0;                              // +0xf0 read by the Load (6.0 in LVL000)
    float m_fIdleTimer;                          // +0xf4 OnMenuState: 30 s on enter, 10 s after the demo; <= 0: the demo plays
    uint8_t m_bStarted;                          // +0xf8 START accepted: the fade-out runs
    uint8_t m_padf9[3];
    float m_fTextTimer;                          // +0xfc set when the demo starts (184 or 173); at 0 the text slot's vt+0x88
    IKSerializable* m_pSound;                    // +0x100 CKSoundDictionaryID (file key 0x109); read whatever the type
};
DOTD_ASSERT_SIZE(CKS08MenuPressStart, 0x104);
DOTD_ASSERT_OFFSET(CKS08MenuPressStart, m_aWidgetSlots, 0x94);
DOTD_ASSERT_OFFSET(CKS08MenuPressStart, m_apMessageIns, 0x9c);
DOTD_ASSERT_OFFSET(CKS08MenuPressStart, m_abMessageInFlags, 0xc0);
DOTD_ASSERT_OFFSET(CKS08MenuPressStart, m_apMessageOuts, 0xcc);
DOTD_ASSERT_OFFSET(CKS08MenuPressStart, m_pText, 0xdc);
DOTD_ASSERT_OFFSET(CKS08MenuPressStart, m_pUnke0, 0xe0);
DOTD_ASSERT_OFFSET(CKS08MenuPressStart, m_pColorizedFx, 0xe4);
DOTD_ASSERT_OFFSET(CKS08MenuPressStart, m_pColorizedData0, 0xe8);
DOTD_ASSERT_OFFSET(CKS08MenuPressStart, m_pColorizedData1, 0xec);
DOTD_ASSERT_OFFSET(CKS08MenuPressStart, m_fUnkf0, 0xf0);
DOTD_ASSERT_OFFSET(CKS08MenuPressStart, m_fIdleTimer, 0xf4);
DOTD_ASSERT_OFFSET(CKS08MenuPressStart, m_bStarted, 0xf8);
DOTD_ASSERT_OFFSET(CKS08MenuPressStart, m_fTextTimer, 0xfc);
DOTD_ASSERT_OFFSET(CKS08MenuPressStart, m_pSound, 0x100);
