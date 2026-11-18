// CKPxFixedJoint.h - a physics joint (key 0x508c, vtable 0xb200b8, size 0x64). Original unit: CKPxFixedJoint.cpp (0x225828-0x226a38).
// Base: KBase488C (the physics joints). No game file holds one (outputs/remake/kp3-class-usage.json). Names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/KBase488C.h"

class CKPxFixedJoint : public KBase488C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x142)
    int32_t IsKindOfClass(uint32_t key) override {
        return key == 0x508c || key == 0x488c || key == 0x468c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKPxFixedJoint)

    CKPxFixedJoint() {}  // 0x00225b38 CKPxFixedJoint_Construct: the base, then the vtable
    ~CKPxFixedJoint() override {}
    // vt+0x2c 0x00225900 CKPxFixedJoint_Load: the base's, then (level data only) a matrix, a matrix, a word.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x10 0x00225a40 CKPxFixedJoint_Destroy: the two matrices destroyed (the pointers kept), then the base's.
    void Destroy() override;
    // vt+0x24 0x00225a18 CKPxFixedJoint_RecursiveRegistration: the base's vf24 (returns 1, registers nothing).

    CMatrix34* m_unk58;  // +0x58 the Load: RwMatrixCreate, read from the file
    CMatrix34* m_unk5c;  // +0x5c the Load: RwMatrixCreate, read from the file
    float m_fUnk60;      // +0x60 the angular rows' arm length

    // vt+0x60 0x00225d50 CKPxFixedJoint_vf60 (C2.8 port-last Z7)
    void Solve() override;
};
DOTD_ASSERT_SIZE(CKPxFixedJoint, 0x64);
DOTD_ASSERT_OFFSET(CKPxFixedJoint, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKPxFixedJoint, m_unk5c, 0x5c);
DOTD_ASSERT_OFFSET(CKPxFixedJoint, m_fUnk60, 0x60);
