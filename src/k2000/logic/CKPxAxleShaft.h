// CKPxAxleShaft.h - a physics axle shaft (key 0x490c, vtable 0xb20638, size 0x2c). Original unit: CKPxAxleShaft.cpp
// (0x22f6c8-0x22fc48). Base: KBase468C (the physics elements). No game file holds one
// (outputs/remake/kp3-class-usage.json: of the CKPx classes only CKPxContainer and CKPxContactJoint occur). Names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/KBase468C.h"

class CKPxAxleShaft : public KBase468C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x124)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x490c || key == 0x468c || key == 0xc; }
    DOTD_DECLARE_FACTORIES(CKPxAxleShaft)

    CKPxAxleShaft() {}  // 0x0022f818 CKPxAxleShaft_Construct: the base, then the vtable
    ~CKPxAxleShaft() override {}
    // vt+0x2c 0x0022f9d0 CKPxAxleShaft_Load: the base's, then (level data only) a reference, three words (one read) and
    // a word.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x24 0x0022f7c8 CKPxAxleShaft_RecursiveRegistration: the base's vf24 0x218068 (returns 1, registers nothing).
    // vt+0x10 0x0022f7f0 CKPxAxleShaft_Destroy: the base's CKPxObject_ClearReferences_BaseNop_maybe (empty).

    IKSerializable* m_unk18;  // +0x18 a reference
    uint32_t m_unk1c[3];      // +0x1c one 12-byte read, each word swapped
    uint32_t m_unk28;         // +0x28
};
DOTD_ASSERT_SIZE(CKPxAxleShaft, 0x2c);
DOTD_ASSERT_OFFSET(CKPxAxleShaft, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CKPxAxleShaft, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKPxAxleShaft, m_unk28, 0x28);
