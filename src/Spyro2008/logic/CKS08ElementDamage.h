// CKS08ElementDamage.h - a damage with per-element values (key 0x99cc, vtable 0xb24b68, size 0x3c).
// Original unit: CKS08ElementDamage.cpp (0x3f2ff0-0x3f4108). Derives from CKS08StunDamage. No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKS08StunDamage.h"
#include "k2000/core/Layout.h"

class CKS08ElementDamage : public CKS08StunDamage {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x267)
    DOTD_DECLARE_FACTORIES(CKS08ElementDamage)

    // 0x003f3698 CKS08ElementDamage_Construct: CKS08StunDamage's constructor, the vtable, +0x30 = null.
    CKS08ElementDamage() { m_afValues = nullptr; }
    ~CKS08ElementDamage() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003f3ad0 CKS08ElementDamage_Load

    float* m_afValues;   // +0x30 OperatorNewArray(0x28): 10 values (file: floats), _maybe one per element
    uint8_t m_unk34;     // +0x34
    uint8_t m_unk35;     // +0x35 (+0x36..+0x37 padding)
    int32_t m_unk38;     // +0x38 (file: 10, 11, 14)
};
DOTD_ASSERT_SIZE(CKS08ElementDamage, 0x3c);
DOTD_ASSERT_OFFSET(CKS08ElementDamage, m_afValues, 0x30);
DOTD_ASSERT_OFFSET(CKS08ElementDamage, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKS08ElementDamage, m_unk35, 0x35);
DOTD_ASSERT_OFFSET(CKS08ElementDamage, m_unk38, 0x38);
