// CKPxPrismaticJoint.h - a physics joint (key 0x52cc, vtable 0xb20220, size 0xa4). Original unit: CKPxPrismaticJoint.cpp (0x2296d0-0x22afd8).
// Base: KBase488C (the physics joints). No game file holds one (outputs/remake/kp3-class-usage.json). Names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/KBase488C.h"

class CKPxPrismaticJoint : public KBase488C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x14b)
    int32_t IsKindOfClass(uint32_t key) override {
        return key == 0x52cc || key == 0x488c || key == 0x468c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKPxPrismaticJoint)

    CKPxPrismaticJoint() {}  // 0x00229820 CKPxPrismaticJoint_Construct: the base, then the vtable
    ~CKPxPrismaticJoint() override {}
    // vt+0x2c 0x00229ae0 CKPxPrismaticJoint_Load: the base's, then (level data only) six times three words
    // (one read each) and a word.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x10 0x002297f8 CKPxPrismaticJoint_Destroy: the base's.
    // vt+0x24 0x002297d0 CKPxPrismaticJoint_RecursiveRegistration: the base's vf24 (returns 1, registers nothing).

    // vt+0x60 0x00229e00 CKPxPrismaticJoint_vf60 (C2.8 port-last Z7)
    void Solve() override;

    CVector3 m_unk58;    // +0x58 one 12-byte read (the first anchor)
    CVector3 m_unk64;    // +0x64 one 12-byte read (the second anchor)
    CVector3 m_unk70;    // +0x70 one 12-byte read (the slide axis in the first body)
    CVector3 m_unk7c;    // +0x7c one 12-byte read (the slide axis in the second body)
    CVector3 m_unk88;    // +0x88 one 12-byte read (the second direction in the first body)
    CVector3 m_unk94;    // +0x94 one 12-byte read (the second direction in the second body)
    float m_fUnka0;      // +0xa0 the lock rows' reach
};
DOTD_ASSERT_SIZE(CKPxPrismaticJoint, 0xa4);
DOTD_ASSERT_OFFSET(CKPxPrismaticJoint, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKPxPrismaticJoint, m_unk64, 0x64);
DOTD_ASSERT_OFFSET(CKPxPrismaticJoint, m_unk70, 0x70);
DOTD_ASSERT_OFFSET(CKPxPrismaticJoint, m_unk7c, 0x7c);
DOTD_ASSERT_OFFSET(CKPxPrismaticJoint, m_unk88, 0x88);
DOTD_ASSERT_OFFSET(CKPxPrismaticJoint, m_unk94, 0x94);
DOTD_ASSERT_OFFSET(CKPxPrismaticJoint, m_fUnka0, 0xa0);
