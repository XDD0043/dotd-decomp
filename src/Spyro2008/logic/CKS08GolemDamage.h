// CKS08GolemDamage.h - a damage dealt to/by the golem (key 0xad4c, vtable 0xb29390, size 0x34). Original
// unit: CKS08GolemDamage.cpp (0x4c4a00-0x4c4f58). Derives from CKS08Damage. No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKS08Damage.h"
#include "k2000/core/Layout.h"

class CKS08GolemDamage : public CKS08Damage {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2b5)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c57c0
        return key == 0xad4c || key == 0xc || key == 0x970c || key == 0x96cc;
    }
    DOTD_DECLARE_FACTORIES(CKS08GolemDamage)

    // 0x004c4d30 CKS08GolemDamage_Construct: CKS08Damage_Construct_2 (CKS08Damage's constructor), the vtable.
    CKS08GolemDamage() {}
    ~CKS08GolemDamage() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004c4ad8 CKS08GolemDamage_Load

    IKSerializable* m_unk28;  // +0x28 (file: null references in LVL010)
    uint32_t m_unk2c;         // +0x2c
    uint8_t m_unk30;          // +0x30 (+0x31..+0x33 padding)
};
DOTD_ASSERT_SIZE(CKS08GolemDamage, 0x34);
DOTD_ASSERT_OFFSET(CKS08GolemDamage, m_unk28, 0x28);
DOTD_ASSERT_OFFSET(CKS08GolemDamage, m_unk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKS08GolemDamage, m_unk30, 0x30);
