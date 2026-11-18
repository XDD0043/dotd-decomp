// CKPxD6Joint.h - a physics joint (key 0x4b4c, vtable 0xb20040, size 0x68). Original unit: CKPxD6Joint.cpp (0x222068-0x225828).
// Base: KBase488C (the physics joints). No game file holds one (outputs/remake/kp3-class-usage.json). Names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/KBase488C.h"

class CKPxD6Joint : public KBase488C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x12d)
    int32_t IsKindOfClass(uint32_t key) override {
        return key == 0x4b4c || key == 0x488c || key == 0x468c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKPxD6Joint)

    CKPxD6Joint() {}  // 0x002223c8 CKPxD6Joint_Construct: the base, then the vtable
    ~CKPxD6Joint() override {}
    // vt+0x2c 0x00222140 CKPxD6Joint_Load: the base's, then (level data only) two
    // matrices, a 16-bit word and a word.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x10 0x002222d0 CKPxD6Joint_Destroy: the two matrices destroyed (the pointers kept), then the base's.
    void Destroy() override;
    // vt+0x24 0x002222a8 CKPxD6Joint_RecursiveRegistration: the base's vf24 (returns 1, registers nothing).
    // vt+0x58 0x002224d8 CKPxD6Joint_vf58 (C2.8 port-last Z7): the base's, then an enabled joint snaps the other body onto
    // the joint frame (vt+0x5c SetWorldMatrix).
    void SetDisabled(int32_t disabled) override;
    // vt+0x60 0x00222860 CKPxD6Joint_vf60 (C2.8 port-last Z9): the point row and the angular rows.
    void Solve() override;

    CMatrix34* m_unk58;  // +0x58 the Load: RwMatrixCreate, read from the file (the first body's joint frame)
    CMatrix34* m_unk5c;  // +0x5c the Load: RwMatrixCreate, read from the file (the second body's joint frame)
    uint16_t m_unk60;    // +0x60 the Solve: bits 0-2 the locked axes of the point row, 3-5 the locked rotations,
                         // 0x40 / 0x80 / 0x100 pick the twist row's axes (one locked rotation)
    uint8_t m_pad62[2];
    float m_fUnk64;      // +0x64 the angular rows' arm length (the Load reads the word)
};
DOTD_ASSERT_SIZE(CKPxD6Joint, 0x68);
DOTD_ASSERT_OFFSET(CKPxD6Joint, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKPxD6Joint, m_unk5c, 0x5c);
DOTD_ASSERT_OFFSET(CKPxD6Joint, m_unk60, 0x60);
DOTD_ASSERT_OFFSET(CKPxD6Joint, m_fUnk64, 0x64);
