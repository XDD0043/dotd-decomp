// CKPxContactJoint.h - (key 0x4d0c, vtable 0xb1ffe8, size 0x4c). Original unit: CKPxContactJoint.cpp.
// No XXL2 class; the names are ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/KBase468C.h"

class CKPxContactJoint : public KBase468C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x134)
    DOTD_DECLARE_FACTORIES(CKPxContactJoint)

    CKPxContactJoint() {}  // 0x00220170 CKPxContactJoint_Construct: the base, then the vtable
    ~CKPxContactJoint() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x002202f0 CKPxContactJoint_Load

    uint32_t m_unk18;   // +0x18 the Load sets 0
    uint32_t m_unk1c;   // +0x1c the Load sets 0
    void* m_unk20;      // +0x20 set at run time (a heap pointer in the samples)
    uint32_t m_unk24;   // +0x24 the Load sets 0
    void* m_unk28;      // +0x28 set at run time (a heap pointer in the samples)
    CVector3 m_unk2c;   // +0x2c the Load copies the vector at 0xc50d64, (0, 0, 0)
    CVector3 m_unk38;   // +0x38 the Load copies the vector at 0xc50d40, (0, 1, 0)
    uint32_t m_unk44;   // +0x44 the Load sets 0
    uint32_t m_unk48;   // +0x48 the Load sets 0
};
DOTD_ASSERT_SIZE(CKPxContactJoint, 0x4c);
DOTD_ASSERT_OFFSET(CKPxContactJoint, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CKPxContactJoint, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKPxContactJoint, m_unk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKPxContactJoint, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKPxContactJoint, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(CKPxContactJoint, m_unk48, 0x48);
