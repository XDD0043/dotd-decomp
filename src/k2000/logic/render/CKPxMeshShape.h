// CKPxMeshShape.h - a physics mesh shape (key 0x484c, vtable 0xb20548, size 0xa8). Original unit: CKPxMeshShape.cpp
// (0x22ecf8-0x22f1c8). Base: KBase474C (the physics shapes). No game file holds one (outputs/remake/kp3-class-usage.json).
// Names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/KBase474C.h"

class CKPxMeshShape : public KBase474C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x121)
    int32_t IsKindOfClass(uint32_t key) override {
        return key == 0x484c || key == 0x474c || key == 0x468c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKPxMeshShape)

    CKPxMeshShape() {}  // 0x0022efb0 CKPxMeshShape_Construct: the base, then the vtable
    ~CKPxMeshShape() override {}
    // vt+0x2c 0x0022edd0 CKPxMeshShape_Load: the base's, then (level data only) one reference (a CKPxMesh, _maybe).
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x10 0x0022eee0 CKPxMeshShape_Destroy: the base's (the two matrices destroyed).
    // vt+0x24 0x0022eeb8 CKPxMeshShape_RecursiveRegistration: the base's vf24 (returns 1, registers nothing).

    IKSerializable* m_unka4;  // +0xa4 a reference
};
DOTD_ASSERT_SIZE(CKPxMeshShape, 0xa8);
DOTD_ASSERT_OFFSET(CKPxMeshShape, m_unka4, 0xa4);
