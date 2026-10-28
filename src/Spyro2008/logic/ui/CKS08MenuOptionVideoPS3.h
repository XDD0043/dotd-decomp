// CKS08MenuOptionVideoPS3.h - the "Menu Option Video PS3" screen (key 0x868c, vtable 0xb2ce98, size 0xb8 from 0x55d4a0 CKS08MenuOptionVideoPS3_Create). DotD only.
// Original unit: CKS08MenuOptionVideoPS3.cpp (0x55d020-0x55da70).
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKMenuBase114c.h"
#include "k2000/core/Layout.h"

class CKS08MenuOptionVideoPS3 : public CKMenuBase114c {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x21a)
    DOTD_DECLARE_FACTORIES(CKS08MenuOptionVideoPS3)

    CKS08MenuOptionVideoPS3() {}  // 0x55d4a0 CKS08MenuOptionVideoPS3_Create: the CKMenuBase114c part only
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c9ff0
        return key == 0x868c || key == 0x114c || key == 0x730c || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;                                   // vt+0x2c 0x55d160 CKS08MenuOptionVideoPS3_Load
    const char* GetMenuName() override { return "Menu Option Video PS3"; }               // vt+0xb8 0x9ca040
    uint8_t VfBC() override { return 1; }                                                // vt+0xbc 0x9ca078
    IKSerializable** VfC0() override { return m_apMessageOuts; }                         // vt+0xc0 0x9ca080
    uint8_t VfC4() override { return 6; }                                                // vt+0xc4 0x9ca050
    IKSerializable** VfC8() override { return m_apMessageIns; }                          // vt+0xc8 0x9ca058
    uint8_t* VfCC() override { return m_abMessageInFlags; }                              // vt+0xcc 0x9ca068
    uint8_t OnMenuState(int32_t phase, uint8_t other) override;                          // vt+0xdc 0x0055d118 CKS08MenuOptionVideoPS3_vfDC
    int32_t GetMenuId() override { return 0xe; }                                         // vt+0xe0 0x9ca048
    // vt+0xe8 0x0055d348 CKS08MenuOptionVideoPS3_vfE8: item 1 (back) validated: back to the options.
    void OnItemState(uint8_t item, uint8_t state, uint8_t phase) override;
    uint8_t VfF0() override { return 1; }                                                // vt+0xf0 0x9ca090
    uint8_t VfF4() override { return 1; }                                                // vt+0xf4 0x9ca098 the back item

    IKSerializable* m_apMessageIns[6];           // +0x94
    uint8_t m_abMessageInFlags[6];               // +0xac MessageProc sets one per VfC8 entry
    uint8_t m_padb2[2];
    IKSerializable* m_apMessageOuts[1];          // +0xb4
};
DOTD_ASSERT_SIZE(CKS08MenuOptionVideoPS3, 0xb8);
DOTD_ASSERT_OFFSET(CKS08MenuOptionVideoPS3, m_apMessageIns, 0x94);
DOTD_ASSERT_OFFSET(CKS08MenuOptionVideoPS3, m_abMessageInFlags, 0xac);
DOTD_ASSERT_OFFSET(CKS08MenuOptionVideoPS3, m_apMessageOuts, 0xb4);
