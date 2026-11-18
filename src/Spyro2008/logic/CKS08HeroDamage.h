// CKS08HeroDamage.h - a damage dealt by the hero (key 0x998c, vtable 0xb23fa0, size 0x30). Original unit:
// CKS08HeroDamage.cpp (0x3c9a68-0x3c9f90). Derives from CKS08StunDamage and adds no data. Referenced by
// CKS08HeroBlow +0x64. No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKS08StunDamage.h"
#include "k2000/core/Layout.h"

class CKS08HeroDamage : public CKS08StunDamage {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x266)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c02c0
        return key == 0x998c || key == 0xc || key == 0x9acc || key == 0x970c || key == 0x96cc;
    }
    DOTD_DECLARE_FACTORIES(CKS08HeroDamage)

    CKS08HeroDamage() {}  // 0x003c9cf8 CKS08HeroDamage_Construct: CKS08StunDamage_Construct, then the vtable
    ~CKS08HeroDamage() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003c9b90 CKS08HeroDamage_Load
};
DOTD_ASSERT_SIZE(CKS08HeroDamage, 0x30);
