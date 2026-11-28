// CKDamage.h - a damage description (key 0x96cc, vtable 0xb21160, size 0x10). Original unit: CKDamage.cpp
// (0x253a00-0x253e70). No XXL2 class of this name: the members keep placeholder names. Base of
// CKS08Damage (Spyro2008/logic).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKDamage : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x25b)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x96cc || key == 0xc; }  // vt+0x08 0x9ba6e0
    DOTD_DECLARE_FACTORIES(CKDamage)

    CKDamage() {}  // 0x00253bf8 CKDamage_Construct: stores the vtable only
    ~CKDamage() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00253cf8 CKDamage_Load

    float m_fAmount;    // +0x04 (live: floats)
    int32_t m_i32DamageKind;  // _maybe: +0x08 (file: small integers, e.g. 3)
    uint8_t m_bContinuous;  // +0x0c (+0x0d..+0x0f padding)
};
DOTD_ASSERT_SIZE(CKDamage, 0x10);
DOTD_ASSERT_OFFSET(CKDamage, m_fAmount, 0x04);
DOTD_ASSERT_OFFSET(CKDamage, m_i32DamageKind, 0x08);
DOTD_ASSERT_OFFSET(CKDamage, m_bContinuous, 0x0c);
