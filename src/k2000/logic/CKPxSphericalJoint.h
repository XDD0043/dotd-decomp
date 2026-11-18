// CKPxSphericalJoint.h - a physics joint (key 0x4d8c, vtable 0xb20130, size 0x78). Original unit: CKPxSphericalJoint.cpp (0x226a38-0x227528).
// Base: KBase488C (the physics joints). No game file holds one (outputs/remake/kp3-class-usage.json). Names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/KBase488C.h"

class CKPxSphericalJoint : public KBase488C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x136)
    int32_t IsKindOfClass(uint32_t key) override {
        return key == 0x4d8c || key == 0x488c || key == 0x468c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKPxSphericalJoint)

    CKPxSphericalJoint() {}  // 0x00226b88 CKPxSphericalJoint_Construct: the base, then the vtable
    ~CKPxSphericalJoint() override {}
    // vt+0x2c 0x00227240 CKPxSphericalJoint_Load: the base's, then (level data
    // only) two times three words (one read each) and two words.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x10 0x00226b60 CKPxSphericalJoint_Destroy: the base's.
    // vt+0x24 0x00226b38 CKPxSphericalJoint_RecursiveRegistration: the base's vf24 (returns 1, registers nothing).

    // vt+0x60 0x00226d48 CKPxSphericalJoint_vf60 (C2.8 port-last Z7)
    void Solve() override;

    CVector3 m_unk58;    // +0x58 one 12-byte read (the first body's anchor)
    CVector3 m_unk64;    // +0x64 one 12-byte read (the second body's anchor)
    float m_fUnk70;      // +0x70 the rest length
    float m_fUnk74;      // +0x74 the slack
};
DOTD_ASSERT_SIZE(CKPxSphericalJoint, 0x78);
DOTD_ASSERT_OFFSET(CKPxSphericalJoint, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKPxSphericalJoint, m_unk64, 0x64);
DOTD_ASSERT_OFFSET(CKPxSphericalJoint, m_fUnk70, 0x70);
DOTD_ASSERT_OFFSET(CKPxSphericalJoint, m_fUnk74, 0x74);
