// CKPxSphereShape.h - a physics sphere shape (key 0x47cc, vtable 0xb205c0, size 0xac). Original unit: CKPxSphereShape.cpp
// (0x22f1c8-0x22f6c8). Base: KBase474C (the physics shapes). No game file holds one (outputs/remake/kp3-class-usage.json).
// Names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/KBase474C.h"

class CKPxSphereShape : public KBase474C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x11f)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9b6b80
        return key == 0x47cc || key == 0x474c || key == 0x468c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKPxSphereShape)

    CKPxSphereShape() {}  // 0x0022f3c0 CKPxSphereShape_Construct: the base, then the vtable
    ~CKPxSphereShape() override {}
    // vt+0x2c 0x0022f4d0 CKPxSphereShape_Load: the base's, then (level data only) two words.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x10 0x0022f2f0 CKPxSphereShape_Destroy: the base's (the two matrices destroyed).
    // vt+0x24 0x0022f2c8 CKPxSphereShape_RecursiveRegistration: the base's vf24 (returns 1, registers nothing).
    // The solver slots vt+0x58.. (inline, 0x9b6dc0..) are not declared: only CKSrvPhysics's CKPxBody steps use them.

    uint32_t m_unka4;  // +0xa4
    uint32_t m_unka8;  // +0xa8
};
DOTD_ASSERT_SIZE(CKPxSphereShape, 0xac);
DOTD_ASSERT_OFFSET(CKPxSphereShape, m_unka4, 0xa4);
