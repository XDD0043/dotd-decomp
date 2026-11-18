// CKGolemDamage.h - a damage description of the golem's (key 0x9bcc, vtable 0xb29070, size 0x24). Original unit:
// CKGolemDamage.cpp (0x4ba5a0-0x4baab0). A CKDamage with its own key: every slot calls CKDamage's; the 0x14 bytes
// past CKDamage are never touched by its code. No XXL2 class of this name. LVL010's golem uses CKS08GolemDamage.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKDamage.h"

class CKGolemDamage : public CKDamage {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x26f)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c55d8
        return key == 0x9bcc || key == 0x96cc || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKGolemDamage)

    // 0x004baa58 CKGolemDamage_Create / 0x004ba9a0 CreateArray inline the constructor: CKDamage_Construct, the vtable.
    CKGolemDamage() {}
    // 0x004ba770 CKGolemDamage_Destructor (0x004ba8b8 BaseDestructor, 0x004ba958 DeletingDestructor): CKDamage's.
    ~CKGolemDamage() override {}

    // vt+0x2c 0x004ba6f8 CKGolemDamage_Load: CKDamage's, 1. vt+0x30 0x004ba6d0 PostLoad, vt+0x24 0x004ba748
    // RecursiveRegistration and vt+0x10 0x004ba6a8 Destroy: CKDamage's (inherited).
    int32_t Load(IKFile* file, int32_t type) override {
        CKDamage::Load(file, type);
        return 1;
    }

    uint8_t m_pad10[0x14];  // +0x10..+0x23 not read or written by the class's code
};
DOTD_ASSERT_SIZE(CKGolemDamage, 0x24);
