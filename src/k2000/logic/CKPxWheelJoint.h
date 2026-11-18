// CKPxWheelJoint.h - a physics joint (key 0x534c, vtable 0xb20298, size 0xb8). Original unit: CKPxWheelJoint.cpp (0x22afd8-0x22c4b8).
// Base: KBase488C (the physics joints). No game file holds one (outputs/remake/kp3-class-usage.json). Names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/KBase488C.h"

class CKPxWheelJoint : public KBase488C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x14d)
    int32_t IsKindOfClass(uint32_t key) override {
        return key == 0x534c || key == 0x488c || key == 0x468c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKPxWheelJoint)

    CKPxWheelJoint() {}  // 0x0022b128 CKPxWheelJoint_Construct: the base, then the vtable
    ~CKPxWheelJoint() override {}
    // vt+0x2c 0x0022c198 CKPxWheelJoint_Load: the base's, then (level data only) six times three words
    // (one read each) and a word.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x10 0x0022b100 CKPxWheelJoint_Destroy: the base's.
    // vt+0x24 0x0022b0d8 CKPxWheelJoint_RecursiveRegistration: the base's vf24 (returns 1, registers nothing).

    // vt+0x60 0x0022b3e8 CKPxWheelJoint_vf60 (C2.8 port-last Z7)
    void Solve() override;

    CVector3 m_unk58;    // +0x58 one 12-byte read (the first anchor)
    CVector3 m_unk64;    // +0x64 one 12-byte read (the second anchor)
    CVector3 m_unk70;    // +0x70 one 12-byte read (the suspension axis in the first body)
    CVector3 m_unk7c;    // +0x7c one 12-byte read (the suspension axis in the second body)
    CVector3 m_unk88;    // +0x88 one 12-byte read (the axle in the first body)
    CVector3 m_unk94;    // +0x94 one 12-byte read (the axle in the second body)
    float m_fUnka0;      // +0xa0 (not loaded) the suspension's rest length
    float m_fUnka4;      // +0xa4 (not loaded) its slack
    float m_fUnka8;      // +0xa8 (not loaded) its stiffness
    float m_fUnkac;      // +0xac (not loaded) its damping while closing
    float m_fUnkb0;      // +0xb0 (not loaded) its damping while opening
    float m_fUnkb4;      // +0xb4 the axle row's reach
};
DOTD_ASSERT_SIZE(CKPxWheelJoint, 0xb8);
DOTD_ASSERT_OFFSET(CKPxWheelJoint, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKPxWheelJoint, m_unk64, 0x64);
DOTD_ASSERT_OFFSET(CKPxWheelJoint, m_unk70, 0x70);
DOTD_ASSERT_OFFSET(CKPxWheelJoint, m_unk7c, 0x7c);
DOTD_ASSERT_OFFSET(CKPxWheelJoint, m_unk88, 0x88);
DOTD_ASSERT_OFFSET(CKPxWheelJoint, m_unk94, 0x94);
DOTD_ASSERT_OFFSET(CKPxWheelJoint, m_fUnkb4, 0xb4);
