// CKS08StunDamage.h - a damage that stuns (key 0x9acc, vtable 0xb24670, size 0x30). Original unit:
// CKS08StunDamage.cpp (0x3d1550-0x3d1c38). Derives from CKS08Damage; base of CKS08HeroDamage.
// No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKS08Damage.h"
#include "k2000/core/Layout.h"

class CKS08StunDamage : public CKS08Damage {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x26b)
    DOTD_DECLARE_FACTORIES(CKS08StunDamage)

    // 0x003d18a0 CKS08StunDamage_Construct: CKS08Damage_Construct_2 (CKS08Damage's constructor), then the
    // vtable; its own two words are left as they are.
    CKS08StunDamage() {}
    ~CKS08StunDamage() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003d1980 CKS08StunDamage_Load

    uint32_t m_unk28;  // +0x28 (live: always 0)
    float m_unk2c;     // +0x2c _maybe the stun duration (live: floats)
};
DOTD_ASSERT_SIZE(CKS08StunDamage, 0x30);
DOTD_ASSERT_OFFSET(CKS08StunDamage, m_unk28, 0x28);
DOTD_ASSERT_OFFSET(CKS08StunDamage, m_unk2c, 0x2c);
