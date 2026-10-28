// CKS08MenuOptionInGame.h - the "Menu Option In Game" screen (key 0xaccc, vtable 0xb2cb80, size 0xb8 from 0x55b558 CKS08MenuOptionInGame_Create). DotD only.
// Original unit: CKS08MenuOptionInGame.cpp (0x55aec0-0x55b9e8).
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKMenuBase114c.h"
#include "k2000/core/Layout.h"

class CKS08MenuOptionInGame : public CKMenuBase114c {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2b3)
    DOTD_DECLARE_FACTORIES(CKS08MenuOptionInGame)

    CKS08MenuOptionInGame() {}  // 0x55b558 CKS08MenuOptionInGame_Create: the CKMenuBase114c part only
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c9dd0
        return key == 0xaccc || key == 0x114c || key == 0x730c || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;                                   // vt+0x2c 0x55b070 CKS08MenuOptionInGame_Load
    const char* GetMenuName() override { return "Menu Option In Game"; }                 // vt+0xb8 0x9c9e20
    uint8_t VfBC() override { return 1; }                                                // vt+0xbc 0x9c9e58
    IKSerializable** VfC0() override { return m_apMessageOuts; }                         // vt+0xc0 0x9c9e60
    uint8_t VfC4() override { return 6; }                                                // vt+0xc4 0x9c9e30
    IKSerializable** VfC8() override { return m_apMessageIns; }                          // vt+0xc8 0x9c9e38
    uint8_t* VfCC() override { return m_abMessageInFlags; }                              // vt+0xcc 0x9c9e48
    int32_t GetMenuId() override { return 0x17; }                                        // vt+0xe0 0x9c9e28

    IKSerializable* m_apMessageIns[6];           // +0x94
    uint8_t m_abMessageInFlags[6];               // +0xac MessageProc sets one per VfC8 entry
    uint8_t m_padb2[2];
    IKSerializable* m_apMessageOuts[1];          // +0xb4
};
DOTD_ASSERT_SIZE(CKS08MenuOptionInGame, 0xb8);
DOTD_ASSERT_OFFSET(CKS08MenuOptionInGame, m_apMessageIns, 0x94);
DOTD_ASSERT_OFFSET(CKS08MenuOptionInGame, m_abMessageInFlags, 0xac);
DOTD_ASSERT_OFFSET(CKS08MenuOptionInGame, m_apMessageOuts, 0xb4);
