// CKAimCone.h - an aiming cone (key 0x9c0c, vtable 0xb2f9f0, size 0x3c). Original unit: CKAimCone.cpp
// (0x5bed60-0x5bf8d8). A sibling of CKAimCamembert under the unregistered aiming base 0x9b0c (vtable 0xb2f988). No XXL2
// class of this name; no level of DotD holds one (level-class-keys.json). The members keep placeholder names.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"

struct RwMatrix;

class CKAimCone : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x270)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x9c0c || key == 0xc || key == 0x9b0c; }
    DOTD_DECLARE_FACTORIES(CKAimCone)

    // 0x005bf1c8 CKAimCone_Create / 0x005bf130 CreateArray: the vtable only.
    CKAimCone() {}
    // 0x005bf4e0 CKAimCone_Destructor / 0x005bf498 DeletingDestructor: vtable stores only (operator delete).
    ~CKAimCone() override {}
    // vt+0x2c 0x005bf500 CKAimCone_Load: for type 0 the six floats. (vt+0x24 0x005bf200 RecursiveRegistration returns 1;
    // vt+0x10 0x005bf250 Destroy is empty.)
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x30 0x005bf208 CKAimCone_PostLoad: ResetAim (vt+0x60). 1.
    int32_t PostLoad(int32_t type) override;

    // vt+0x50 0x005bf258 CKAimCone_ScoreTarget_maybe: 1 with *score when `point` lies in the cone, else 0 (*score -1).
    virtual uint8_t ScoreTarget(const CVector3* point, float* score);
    // vt+0x54 0x005bedc0 CKAimCone_vf54: the better score of two points (vt+0x50 each; the second only when the first
    // misses). 0 when neither is in the cone.
    virtual uint8_t ScoreBestOfTwo(const CVector3* first, const CVector3* second, float* score);
    // vt+0x58 0x005beea0 CKAimCone_vf58: ResetAim, then the cone follows `matrix` (its at and position) (+0x38 set).
    virtual void FollowMatrix(const RwMatrix* matrix);
    // vt+0x5c 0x005bf080 CKAimCone_vf5C: ResetAim, then the origin and the direction.
    virtual void SetOriginAndDirection(const CVector3* origin, const CVector3* direction);
    // vt+0x60 0x005bf030 CKAimCone_vf60: no matrix, the origin the null vector, the direction the X axis (0x00c50d34),
    // +0x38 clear.
    virtual void ResetAim();

    // The six loaded floats: [0] the opening angle (half of it is compared with the point's angle from the aim, in
    // radians), [2] / [3] the nearest / farthest distance, [4] / [5] the distance and the angle weights; [1] not read.
    float m_afUnk04[6];        // +0x04
    const RwMatrix* m_pMatrix;  // +0x1c the matrix whose at (+0x20) and position (+0x30) replace the cone's while +0x38
    CVector3 m_vOrigin;        // +0x20
    CVector3 m_vDirection;     // +0x2c
    uint8_t m_unk38;           // +0x38
    uint8_t m_pad39[3];
};
DOTD_ASSERT_SIZE(CKAimCone, 0x3c);
DOTD_ASSERT_OFFSET(CKAimCone, m_pMatrix, 0x1c);
DOTD_ASSERT_OFFSET(CKAimCone, m_vOrigin, 0x20);
DOTD_ASSERT_OFFSET(CKAimCone, m_unk38, 0x38);
