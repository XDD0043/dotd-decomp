// CKS08ElementDamage.h - a damage with per-element values (key 0x99cc, vtable 0xb24b68, size 0x3c).
// Original unit: CKS08ElementDamage.cpp (0x3f2ff0-0x3f4108). Derives from CKS08StunDamage. No XXL2 class of this name.
#pragma once
#include <cstdint>
#include <cstring>

#include "Spyro2008/logic/CKS08StunDamage.h"
#include "k2000/core/Layout.h"

class CKS08ElementDamage : public CKS08StunDamage {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x267)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c0a48
        return key == 0x99cc || key == 0xc || key == 0x9acc || key == 0x970c || key == 0x96cc;
    }
    DOTD_DECLARE_FACTORIES(CKS08ElementDamage)

    // 0x003f3698 CKS08ElementDamage_Construct: CKS08StunDamage's constructor, the vtable, +0x30 = null.
    CKS08ElementDamage() { m_afValues = nullptr; }
    CKS08ElementDamage(const CKS08ElementDamage& other);             // 0x003f3488 _CopyConstruct_2_maybe
    CKS08ElementDamage& operator=(const CKS08ElementDamage& other);  // 0x003f31e8 _Assign_maybe
    ~CKS08ElementDamage() override;                                  // 0x003f33b8 _Destructor
    void Destroy() override;                                         // vt+0x10 0x003f30c8 _Destroy
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003f3ad0 CKS08ElementDamage_Load

    // The setters the abilities call (vt+0x50..+0x70, 0x9c0ac0..0x9c0b10; not virtual here: CKS08ElementDamage is the
    // only class the abilities hold).
    void SetAmount(float amount) { m_fAmount = amount; }                // vt+0x50 0x009c0ac0
    void SetContinuous(uint8_t on) { m_bContinuous = on; }                  // vt+0x54 0x009c0ac8 SetContinuous_maybe
    void SetElementValue(float value, uint32_t i) { m_afValues[i] = value; }  // vt+0x58 0x009c0ad0
    void SetStun(float value) { std::memcpy(&m_fStunAmount, &value, sizeof(value)); }  // vt+0x5c 0x009c0ae8 (+0x28 a float)
    void SetDisarmAmount(float value) { m_fDisarmAmount = value; }            // vt+0x60 0x009c0af0 (+0x2c)
    void SetDamageType(uint32_t type) { m_ui32DamageType = type; }             // vt+0x64 0x009c0af8
    void SetAbilityId(int32_t id) { m_i32AbilityId = id; }                   // vt+0x68 0x009c0b00 SetAbilityId_maybe
    void SetUnk34(uint8_t value) { m_unk34 = value; }                 // vt+0x6c 0x009c0b08
    void SetUnk35(uint8_t value) { m_unk35 = value; }                 // vt+0x70 0x009c0b10

    float* m_afValues;   // +0x30 OperatorNewArray(0x28): 10 values (file: floats), _maybe one per element
    uint8_t m_unk34;     // +0x34
    uint8_t m_unk35;     // +0x35 (+0x36..+0x37 padding)
    int32_t m_i32AbilityId;     // +0x38 (file: 10, 11, 14)
};
DOTD_ASSERT_SIZE(CKS08ElementDamage, 0x3c);
DOTD_ASSERT_OFFSET(CKS08ElementDamage, m_afValues, 0x30);
DOTD_ASSERT_OFFSET(CKS08ElementDamage, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKS08ElementDamage, m_unk35, 0x35);
DOTD_ASSERT_OFFSET(CKS08ElementDamage, m_i32AbilityId, 0x38);
