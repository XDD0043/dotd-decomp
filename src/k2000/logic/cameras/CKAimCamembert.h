// CKAimCamembert.h - an aiming sector ("camembert") of the camera (DotD) (key 0x9b4c, vtable 0xb2f918, size 0x40). Original unit: CKAimCamembert.cpp.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/core/IKSerializable.h"
#include "k2000/math/CMatrix34.h"

class IKFile;

class CKAimCamembert : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x26d)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9cd158
        return key == 0x9b4c || key == 0xc || key == 0x9b0c;
    }
    DOTD_DECLARE_FACTORIES(CKAimCamembert)

    // 0x005be7f0 CKAimCamembert_Create: the vtable only (as the dead CKAimCamembert_Construct 0x5be028).
    CKAimCamembert() {}
    ~CKAimCamembert() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005be8c0 CKAimCamembert_Load

    // vt+0x60 0x005be2a0 CKAimCamembert_vf60: no reference object, the origin the null vector, the direction the X axis
    // (0x00c50d34), +0x3c clear.
    virtual void ResetAim();
    // vt+0x5c 0x005be2f0 CKAimCamembert_SetOriginAndDirection_maybe
    virtual void SetOriginAndDirection(const CVector3* origin, const CVector3* direction);
    // vt+0x50 0x005be3e0 CKAimCamembert_ScoreTarget_maybe: 1 with *score when `point` lies in the sector, else 0 (*score -1).
    virtual uint8_t ScoreTarget(const CVector3* point, float* score);
    // vt+0x54 0x005be038 CKAimCamembert_vf54: the better score of two points (ScoreTarget on `a`, and on `b` only when `a`
    // is outside); 0 when `a` and `b` are both outside. BUG(original): with `a` inside the second score is never
    // computed and the comparison reads an unset stack word; here it starts at -1.0 (the score of a point outside), so
    // `a`'s score is kept.
    virtual uint8_t ScoreBestOfTwo(const CVector3* a, const CVector3* b, float* score);
    // vt+0x58 0x005be118 CKAimCamembert_vf58: the aim reset (vt+0x60), then the reference object set and used (+0x3c).
    virtual void SetReference(IKSerializable* object) {
        ResetAim();
        m_pReferenceObj = object;
        m_bUseReference = 1;
    }
    // vt+0x30 0x005be830 CKAimCamembert_PostLoad: the aim reset (vt+0x60), then 1.
    int32_t PostLoad(int32_t /*type*/) override {
        ResetAim();
        return 1;
    }

    // The seven loaded floats (90, 2, 28, 0, 10, 1, 1 in LVL010): the opening angle in degrees, the nearest and farthest
    // distance along the aim, the apex width, the radius around the aim line, the distance and the angle weights.
    float m_afUnk04[7];    // +0x04
    IKSerializable* m_pReferenceObj;  // +0x20 an object whose direction (+0x20) and origin (+0x30) replace the sector's while +0x3c
    CVector3 m_vOrigin;        // +0x24
    CVector3 m_vDirection;     // +0x30
    uint8_t m_bUseReference;           // +0x3c
    uint8_t m_pad3d[3];
};
DOTD_ASSERT_SIZE(CKAimCamembert, 0x40);
DOTD_ASSERT_OFFSET(CKAimCamembert, m_afUnk04, +0x04);
DOTD_ASSERT_OFFSET(CKAimCamembert, m_pReferenceObj, +0x20);
DOTD_ASSERT_OFFSET(CKAimCamembert, m_vOrigin, +0x24);
DOTD_ASSERT_OFFSET(CKAimCamembert, m_vDirection, +0x30);
DOTD_ASSERT_OFFSET(CKAimCamembert, m_bUseReference, +0x3c);
