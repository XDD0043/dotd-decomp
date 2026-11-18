// CKPxCylinderShape.h - a physics cylinder shape (key 0x524c, vtable 0xb204d0, size 0xb4). Original unit: CKPxCylinderShape.cpp
// (0x22e760-0x22ecf8). Base: KBase474C (the physics shapes). No game file holds one (outputs/remake/kp3-class-usage.json). Names
// ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/KBase474C.h"

class CKPxCylinderShape : public KBase474C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x149)
    int32_t IsKindOfClass(uint32_t key) override {
        return key == 0x524c || key == 0x474c || key == 0x468c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKPxCylinderShape)

    CKPxCylinderShape() {}  // 0x0022e958 CKPxCylinderShape_Construct: the base, then the vtable
    ~CKPxCylinderShape() override {}
    // vt+0x2c 0x0022eb70 CKPxCylinderShape_Load: the base's, then (level data only) four words.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x10 0x0022e888 CKPxCylinderShape_Destroy: the base's (the two matrices destroyed).
    // vt+0x24 0x0022e860 CKPxCylinderShape_RecursiveRegistration: the base's vf24 (returns 1, registers nothing).

    uint32_t m_unka4;  // +0xa4
    uint32_t m_unka8;  // +0xa8
    uint32_t m_unkac;  // +0xac
    uint32_t m_unkb0;  // +0xb0
};
DOTD_ASSERT_SIZE(CKPxCylinderShape, 0xb4);
DOTD_ASSERT_OFFSET(CKPxCylinderShape, m_unka4, 0xa4);
