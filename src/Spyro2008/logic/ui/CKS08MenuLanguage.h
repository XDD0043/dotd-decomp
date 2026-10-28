// CKS08MenuLanguage.h - the "Menu Language" screen (key 0x81cc, vtable 0xb2c868, size 0xbc from 0x556e28 CKS08MenuLanguage_Create). DotD only.
// Original unit: CKS08MenuLanguage.cpp (0x556840-0x5572b8).
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKMenuBase114c.h"
#include "k2000/core/Layout.h"

class CKS08MenuLanguage : public CKMenuBase114c {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x207)
    DOTD_DECLARE_FACTORIES(CKS08MenuLanguage)

    CKS08MenuLanguage() {}  // 0x556e28 CKS08MenuLanguage_Create: the CKMenuBase114c part only
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c9b98
        return key == 0x81cc || key == 0x114c || key == 0x730c || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;                                   // vt+0x2c 0x556a58 CKS08MenuLanguage_Load
    const char* GetMenuName() override { return "Menu Language"; }                       // vt+0xb8 0x9c9be8
    uint8_t VfBC() override { return 1; }                                                // vt+0xbc 0x9c9c20
    IKSerializable** VfC0() override { return m_apMessageOuts; }                         // vt+0xc0 0x9c9c28
    uint8_t VfC4() override { return 6; }                                                // vt+0xc4 0x9c9bf8
    IKSerializable** VfC8() override { return m_apMessageIns; }                          // vt+0xc8 0x9c9c00
    uint8_t* VfCC() override { return m_abMessageInFlags; }                              // vt+0xcc 0x9c9c10
    // vt+0xdc 0x00556970 CKS08MenuLanguage_OnMenuState_maybe: leaving reverts the options (a language not
    // confirmed is undone); +0xb8 cleared on enter and on input activity.
    uint8_t OnMenuState(int32_t phase, uint8_t other) override;
    int32_t GetMenuId() override { return 0x8; }                                         // vt+0xe0 0x9c9bf0
    uint8_t GetSelection(uint8_t /*player*/) override { return 1; }                      // vt+0xe4 0x9c9c38
    // vt+0xe8 0x00556938 CKS08MenuLanguage_vfE8: item 1 (back) leaving its validated state: the game
    // manager's +0xafc bit 0 (the language confirmed_maybe).
    void OnItemState(uint8_t item, uint8_t state, uint8_t phase) override;

    IKSerializable* m_apMessageIns[6];           // +0x94
    uint8_t m_abMessageInFlags[6];               // +0xac MessageProc sets one per VfC8 entry
    uint8_t m_padb2[2];
    IKSerializable* m_apMessageOuts[1];          // +0xb4
    uint32_t m_unkb8;                            // +0xb8 OnMenuState clears it (enter, input activity)
};
DOTD_ASSERT_SIZE(CKS08MenuLanguage, 0xbc);
DOTD_ASSERT_OFFSET(CKS08MenuLanguage, m_apMessageIns, 0x94);
DOTD_ASSERT_OFFSET(CKS08MenuLanguage, m_abMessageInFlags, 0xac);
DOTD_ASSERT_OFFSET(CKS08MenuLanguage, m_apMessageOuts, 0xb4);
