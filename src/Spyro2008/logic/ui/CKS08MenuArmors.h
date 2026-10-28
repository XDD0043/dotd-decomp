// CKS08MenuArmors.h - the "Menu Armors" screen (key 0xab8c, vtable 0xb2c130, size 0x1c4 from 0x542980 CKS08MenuArmors_Create). DotD only.
// Original unit: CKS08MenuArmors.cpp (0x541ff8-0x547150).
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKMenuBase114c.h"
#include "k2000/core/Layout.h"

class CKS08MenuArmors : public CKMenuBase114c {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2ae)
    DOTD_DECLARE_FACTORIES(CKS08MenuArmors)

    CKS08MenuArmors() {}  // 0x542980 CKS08MenuArmors_Create: the CKMenuBase114c part only
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c9618
        return key == 0xab8c || key == 0x114c || key == 0x730c || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;                                   // vt+0x2c 0x542a68 CKS08MenuArmors_Load
    uint32_t GetWidgetSlotCount() override { return 8; }                                 // vt+0x68 0x9c9678
    WidgetSlot* GetWidgetSlots() override { return m_aWidgetSlots; }                     // vt+0x6c 0x9c9680
    uint8_t Vf84() override { return 1; }                                                // vt+0x84 0x9c96e0
    RefGroup* Vf88() override { return m_aRefGroups; }                                   // vt+0x88 0x9c96e8
    IKSerializable** Vf8C(uint32_t group) override { return group == 0 ? m_apGroupRefs : nullptr; }  // vt+0x8c 0x541d18
    GroupState* Vf90(uint32_t group) override { return group == 0 ? m_aGroupStates : nullptr; }  // vt+0x90 0x541d30
    const char* GetMenuName() override { return "Menu Armors"; }                         // vt+0xb8 0x9c9668
    uint8_t VfBC() override { return 25; }                                               // vt+0xbc 0x9c96b8
    IKSerializable** VfC0() override { return m_apMessageOuts; }                         // vt+0xc0 0x9c96c0
    uint8_t VfC4() override { return 8; }                                                // vt+0xc4 0x9c9690
    IKSerializable** VfC8() override { return m_apMessageIns; }                          // vt+0xc8 0x9c9698
    uint8_t* VfCC() override { return m_abMessageInFlags; }                              // vt+0xcc 0x9c96a8
    int32_t GetMenuId() override { return 0x0; }                                         // vt+0xe0 0x9c9670

    WidgetSlot m_aWidgetSlots[8];                // +0x94
    IKSerializable* m_apMessageIns[8];           // +0xd4
    uint8_t m_abMessageInFlags[8];               // +0xf4 MessageProc sets one per VfC8 entry
    IKSerializable* m_apMessageOuts[25];         // +0xfc
    uint8_t m_unk160[3];                         // +0x160 the Load clears them
    uint8_t m_unk163[1];
    uint32_t m_unk164[4];                        // +0x164
    float m_fUnk174;                             // +0x174 read by the Load
    uint32_t m_unk178[2];                        // +0x178
    RefGroup m_aRefGroups[1];                    // +0x180
    IKSerializable* m_apGroupRefs[3];            // +0x190 Vf8C(0); the Load clears [m_unk04, m_unk08)
    GroupState m_aGroupStates[3];                // +0x19c Vf90(0); the Load clears the first m_unk08
    void* m_pTexture1b4;                         // +0x1b4 IKFile_ReadTextureRef
    void* m_pTexture1b8;                         // +0x1b8 IKFile_ReadTextureRef (read before +0x1b4)
    IKSerializable* m_pText;                     // +0x1bc CKLocTextAccessor (struct draft)
    IKSerializable* m_pSound;                    // +0x1c0 CKSoundDictionaryID (struct draft)
};
DOTD_ASSERT_SIZE(CKS08MenuArmors, 0x1c4);
DOTD_ASSERT_OFFSET(CKS08MenuArmors, m_aWidgetSlots, 0x94);
DOTD_ASSERT_OFFSET(CKS08MenuArmors, m_apMessageIns, 0xd4);
DOTD_ASSERT_OFFSET(CKS08MenuArmors, m_abMessageInFlags, 0xf4);
DOTD_ASSERT_OFFSET(CKS08MenuArmors, m_apMessageOuts, 0xfc);
DOTD_ASSERT_OFFSET(CKS08MenuArmors, m_unk160, 0x160);
DOTD_ASSERT_OFFSET(CKS08MenuArmors, m_fUnk174, 0x174);
DOTD_ASSERT_OFFSET(CKS08MenuArmors, m_aRefGroups, 0x180);
DOTD_ASSERT_OFFSET(CKS08MenuArmors, m_apGroupRefs, 0x190);
DOTD_ASSERT_OFFSET(CKS08MenuArmors, m_aGroupStates, 0x19c);
DOTD_ASSERT_OFFSET(CKS08MenuArmors, m_pTexture1b4, 0x1b4);
DOTD_ASSERT_OFFSET(CKS08MenuArmors, m_pTexture1b8, 0x1b8);
DOTD_ASSERT_OFFSET(CKS08MenuArmors, m_pText, 0x1bc);
DOTD_ASSERT_OFFSET(CKS08MenuArmors, m_pSound, 0x1c0);
