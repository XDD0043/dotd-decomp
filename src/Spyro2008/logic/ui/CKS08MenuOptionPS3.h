// CKS08MenuOptionPS3.h - the "Menu Option PS3" screen (key 0xae0c, vtable 0xb2cc88, size 0xb8 from 0x55c120 CKS08MenuOptionPS3_Create). DotD only.
// Original unit: CKS08MenuOptionPS3.cpp (0x55b9e8-0x55c5b0).
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKMenuBase114c.h"
#include "k2000/core/Layout.h"

class CKS08MenuOptionPS3 : public CKMenuBase114c {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2b8)
    DOTD_DECLARE_FACTORIES(CKS08MenuOptionPS3)

    CKS08MenuOptionPS3() {}  // 0x55c120 CKS08MenuOptionPS3_Create: the CKMenuBase114c part only
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c9e88
        return key == 0xae0c || key == 0x114c || key == 0x730c || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;                                   // vt+0x2c 0x55bd50 CKS08MenuOptionPS3_Load
    const char* GetMenuName() override { return "Menu Option PS3"; }                     // vt+0xb8 0x9c9ed8
    uint8_t VfBC() override { return 1; }                                                // vt+0xbc 0x9c9f10
    IKSerializable** VfC0() override { return m_apMessageOuts; }                         // vt+0xc0 0x9c9f18
    uint8_t VfC4() override { return 6; }                                                // vt+0xc4 0x9c9ee8
    IKSerializable** VfC8() override { return m_apMessageIns; }                          // vt+0xc8 0x9c9ef0
    uint8_t* VfCC() override { return m_abMessageInFlags; }                              // vt+0xcc 0x9c9f00
    // vt+0xdc 0x0055bb90 CKS08MenuOptionPS3_OnMenuState_maybe: every frame the first item shown; on enter
    // the video, the main menu's enter sounds and the items' values reloaded.
    uint8_t OnMenuState(int32_t phase, uint8_t other) override;
    int32_t GetMenuId() override { return 0x19; }                                        // vt+0xe0 0x9c9ee0
    uint8_t GetSelection(uint8_t /*player*/) override { return 0; }                      // vt+0xe4 0x9c9f28
    // vt+0xe8 0x0055bae0 CKS08MenuOptionPS3_OnItemEvent: item 10 validated: the manager's vt+0x1d4 and the
    // values reloaded; item 15 (back): the options-changed flag, then the game menu (6).
    void OnItemState(uint8_t item, uint8_t state, uint8_t phase) override;
    uint8_t VfF0() override { return 1; }                                                // vt+0xf0 0x9c9f30
    uint8_t VfF4() override { return 0xf; }                                              // vt+0xf4 0x9c9f38 the back item

    IKSerializable* m_apMessageIns[6];           // +0x94
    uint8_t m_abMessageInFlags[6];               // +0xac MessageProc sets one per VfC8 entry
    uint8_t m_padb2[2];
    IKSerializable* m_apMessageOuts[1];          // +0xb4
};
DOTD_ASSERT_SIZE(CKS08MenuOptionPS3, 0xb8);
DOTD_ASSERT_OFFSET(CKS08MenuOptionPS3, m_apMessageIns, 0x94);
DOTD_ASSERT_OFFSET(CKS08MenuOptionPS3, m_abMessageInFlags, 0xac);
DOTD_ASSERT_OFFSET(CKS08MenuOptionPS3, m_apMessageOuts, 0xb4);
