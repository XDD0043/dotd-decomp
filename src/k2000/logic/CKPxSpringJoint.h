// CKPxSpringJoint.h - a physics joint (key 0x4dcc, vtable 0xb201a8, size 0x88). Original unit: CKPxSpringJoint.cpp (0x227528-0x2296d0).
// Base: KBase488C (the physics joints). No game file holds one (outputs/remake/kp3-class-usage.json). Names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/KBase488C.h"

class CKPxSpringJoint : public KBase488C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x137)
    int32_t IsKindOfClass(uint32_t key) override {
        return key == 0x4dcc || key == 0x488c || key == 0x468c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKPxSpringJoint)

    CKPxSpringJoint() {}  // 0x00227678 CKPxSpringJoint_Construct: the base, then the vtable
    ~CKPxSpringJoint() override {}
    // vt+0x2c 0x00228058 CKPxSpringJoint_Load: the base's, then (level data only) a word,
    // two times three words (one read each) and five words.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x10 0x00227650 CKPxSpringJoint_Destroy: the base's.
    // vt+0x24 0x00227628 CKPxSpringJoint_RecursiveRegistration: the base's vf24 (returns 1, registers nothing).

    // vt+0x5c 0x00228340 CKPxSpringJoint_vf5C (C2.8 port-last Z7): the base's without the island merge.
    CKPxBody* WakeAndPickBody() override;
    // vt+0x60 0x00227948 CKPxSpringJoint_vf60 (C2.8 port-last Z7)
    void Solve() override;

    uint32_t m_unk58;    // +0x58 the mode: 0 linear, 1 angular
    CVector3 m_unk5c;    // +0x5c one 12-byte read (the first anchor / axis)
    CVector3 m_unk68;    // +0x68 one 12-byte read (the second anchor / axis)
    float m_fUnk74;      // +0x74 the rest length / angle
    float m_fUnk78;      // +0x78 the slack
    float m_fUnk7c;      // +0x7c the stiffness
    float m_fUnk80;      // +0x80 the damping while closing
    float m_fUnk84;      // +0x84 the damping while opening
};
DOTD_ASSERT_SIZE(CKPxSpringJoint, 0x88);
DOTD_ASSERT_OFFSET(CKPxSpringJoint, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKPxSpringJoint, m_unk5c, 0x5c);
DOTD_ASSERT_OFFSET(CKPxSpringJoint, m_unk68, 0x68);
DOTD_ASSERT_OFFSET(CKPxSpringJoint, m_fUnk74, 0x74);
DOTD_ASSERT_OFFSET(CKPxSpringJoint, m_fUnk78, 0x78);
DOTD_ASSERT_OFFSET(CKPxSpringJoint, m_fUnk7c, 0x7c);
DOTD_ASSERT_OFFSET(CKPxSpringJoint, m_fUnk80, 0x80);
DOTD_ASSERT_OFFSET(CKPxSpringJoint, m_fUnk84, 0x84);
