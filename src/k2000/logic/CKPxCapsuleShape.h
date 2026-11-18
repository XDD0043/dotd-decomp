// CKPxCapsuleShape.h - a physics capsule shape (key 0x480c, vtable 0xb20458, size 0xb4). Original unit: CKPxCapsuleShape.cpp
// (0x22e1c8-0x22e760). Base: KBase474C (the physics shapes). No game file holds one (outputs/remake/kp3-class-usage.json). Names
// ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/KBase474C.h"

class CKPxCapsuleShape : public KBase474C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x120)
    int32_t IsKindOfClass(uint32_t key) override {
        return key == 0x480c || key == 0x474c || key == 0x468c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKPxCapsuleShape)

    CKPxCapsuleShape() {}  // 0x0022e3c0 CKPxCapsuleShape_Construct: the base, then the vtable
    ~CKPxCapsuleShape() override {}
    // vt+0x2c 0x0022e5d8 CKPxCapsuleShape_Load: the base's, then (level data only) four words.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x10 0x0022e2f0 CKPxCapsuleShape_Destroy: the base's (the two matrices destroyed).
    // vt+0x24 0x0022e2c8 CKPxCapsuleShape_RecursiveRegistration: the base's vf24 (returns 1, registers nothing).

    uint32_t m_unka4;  // +0xa4
    uint32_t m_unka8;  // +0xa8
    uint32_t m_unkac;  // +0xac
    uint32_t m_unkb0;  // +0xb0
};
DOTD_ASSERT_SIZE(CKPxCapsuleShape, 0xb4);
DOTD_ASSERT_OFFSET(CKPxCapsuleShape, m_unka4, 0xa4);
