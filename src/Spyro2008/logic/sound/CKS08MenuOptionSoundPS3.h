// CKS08MenuOptionSoundPS3.h - the "Menu Option Sound PS3" screen (key 0xaf0c, vtable 0xb2cd90, size 0xb8 from 0x55ca50 CKS08MenuOptionSoundPS3_Create). DotD only.
// Original unit: CKS08MenuOptionSoundPS3.cpp (0x55c5b0-0x55d020).
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKMenuBase114c.h"
#include "k2000/core/Layout.h"

class CKS08MenuOptionSoundPS3 : public CKMenuBase114c {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2bc)
    DOTD_DECLARE_FACTORIES(CKS08MenuOptionSoundPS3)

    CKS08MenuOptionSoundPS3() {}  // 0x55ca50 CKS08MenuOptionSoundPS3_Create: the CKMenuBase114c part only
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c9f40
        return key == 0xaf0c || key == 0x114c || key == 0x730c || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;                                   // vt+0x2c 0x55c718 CKS08MenuOptionSoundPS3_Load
    const char* GetMenuName() override { return "Menu Option Sound PS3"; }               // vt+0xb8 0x9c9f90
    uint8_t VfBC() override { return 1; }                                                // vt+0xbc 0x9c9fc8
    IKSerializable** VfC0() override { return m_apMessageOuts; }                         // vt+0xc0 0x9c9fd0
    uint8_t VfC4() override { return 6; }                                                // vt+0xc4 0x9c9fa0
    IKSerializable** VfC8() override { return m_apMessageIns; }                          // vt+0xc8 0x9c9fa8
    uint8_t* VfCC() override { return m_abMessageInFlags; }                              // vt+0xcc 0x9c9fb8
    void Reset() override { CKMenuBase114c::Reset(); }                                   // vt+0x9c 0x0055c6f0 CKS08MenuOptionSoundPS3_vf9C
    uint8_t OnMenuState(int32_t phase, uint8_t other) override;                          // vt+0xdc 0x0055c6a8 CKS08MenuOptionSoundPS3_vfDC
    int32_t GetMenuId() override { return 0x1c; }                                        // vt+0xe0 0x9c9f98
    // vt+0xe8 0x0055c900 CKS08MenuOptionSoundPS3_vfE8: item 3 (back) validated: back to the options.
    void OnItemState(uint8_t item, uint8_t state, uint8_t phase) override;
    uint8_t VfF0() override { return 1; }                                                // vt+0xf0 0x9c9fe0
    uint8_t VfF4() override { return 3; }                                                // vt+0xf4 0x9c9fe8 the back item

    IKSerializable* m_apMessageIns[6];           // +0x94
    uint8_t m_abMessageInFlags[6];               // +0xac MessageProc sets one per VfC8 entry
    uint8_t m_padb2[2];
    IKSerializable* m_apMessageOuts[1];          // +0xb4
};
DOTD_ASSERT_SIZE(CKS08MenuOptionSoundPS3, 0xb8);
DOTD_ASSERT_OFFSET(CKS08MenuOptionSoundPS3, m_apMessageIns, 0x94);
DOTD_ASSERT_OFFSET(CKS08MenuOptionSoundPS3, m_abMessageInFlags, 0xac);
DOTD_ASSERT_OFFSET(CKS08MenuOptionSoundPS3, m_apMessageOuts, 0xb4);
