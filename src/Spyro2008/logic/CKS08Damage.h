// CKS08Damage.h - Spyro's damage description (key 0x970c, vtable 0xb2aab0, size 0x28). Original unit:
// CKS08Damage.cpp (0x4eb8c8-0x4ec6e8). Derives from CKDamage (its Load and constructor are called first).
// No XXL2 class of this name. Bases of CKS08StunDamage -> CKS08HeroDamage.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKDamage.h"

class CKS08Damage : public CKDamage {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x25c)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c67c8
        return key == 0x970c || key == 0xc || key == 0x96cc;
    }
    DOTD_DECLARE_FACTORIES(CKS08Damage)

    CKS08Damage();  // 0x004ebc70 CKS08Damage_Construct
    CKS08Damage(const CKS08Damage& other);  // 0x004ebb60 CKS08Damage_Construct_3: the derived fields only
    CKS08Damage& operator=(const CKS08Damage& other) = default;  // 0x004eba18 CKS08Damage_Assign
    ~CKS08Damage() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004ebdf8 CKS08Damage_Load

    float m_unk10;      // +0x10 (live: floats)
    float m_unk14;      // +0x14
    uint32_t m_unk18;   // +0x18 (live: always 0)
    float m_unk1c;      // +0x1c
    uint32_t m_unk20;   // +0x20 (live: always 0)
    uint8_t m_unk24;    // +0x24
    uint8_t m_unk25;    // +0x25
    uint8_t m_unk26;    // +0x26 (+0x27 padding)
};
DOTD_ASSERT_SIZE(CKS08Damage, 0x28);
DOTD_ASSERT_OFFSET(CKS08Damage, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(CKS08Damage, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKS08Damage, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKS08Damage, m_unk26, 0x26);
