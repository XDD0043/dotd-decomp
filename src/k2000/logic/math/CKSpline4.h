// CKSpline4.h - a spline path (key 0x2cc, vtable 0xb17c30, size 0x50). Original unit: CKSpline4.cpp.
// XXL2: K/KModules/KGL/Path/CKSpline4.h (m_ui8NumberOfSegment, m_fTotalLenght, m_fPrecision, m_bSplineOk,
// CtrlPointsList, SegmentLenghtList, SplineSegmentRef, SplineUniformSamples, SplineSegmentTransition);
// the PS3 packs the two bytes at +0x08/+0x09.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/math/IKPath.h"
#include "k2000/math/CMatrix34.h"

class CKSpline4 : public IKPath {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xb)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9a1db8
        return key == 0x2cc || key == 0x70c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKSpline4)

    CKSpline4();  // inlined in 0x000c5c70 CKSpline4_Create (CKSpline4_Construct 0xc51a0)
    ~CKSpline4() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000c5d20 CKSpline4_Load
    // vt+0x24 0x000c5190 CKSpline4_RecursiveRegistration: returns 1, registers nothing (IKSerializable's).
    // vt+0x10 0x000c5b40 CKSpline4_Destroy: empty (IKSerializable's).
    // vt+0x50 0x000c5220 CKSpline4_vf50: IKPath::GetPointAt (CKLine.cpp), the same body.

    // vt+0x54 0x000c5800 CKSpline4_GetPointAtDistance_maybe: the uniform samples (+0x38) map the distance to a segment
    // (+0x2c) and its parameter (the segment transitions +0x44 at a segment change); the cubic Bezier point, and the
    // unit tangent with `direction`.
    void GetPointAtDistance(float distance, CVector3* point, CVector3* direction) override;
    float GetClosestDistanceAlong(const CVector3* /*point*/, uint8_t /*squared*/) override { return 0.0f; }  // vt+0x58 0x9a1d98
    float GetLength() override { return m_fTotalLenght; }  // vt+0x5c 0x009a1db0 CKSpline4_GetLength

    // 0x000c5278 CKSpline4_EvaluateSegment_maybe: the cubic Bezier point of segment `segment` (control points 4 x
    // segment .. + 3) at `t`, the weights from s = 1 - t and u = 1 - s.
    void EvaluateSegment(float t, uint32_t segment, CVector3* out) const;
    // 0x000c5488 CKSpline4_EvaluateSegmentTangent_maybe: the de Casteljau tangent there, normalised unless 0.
    void EvaluateSegmentTangent(float t, uint32_t segment, CVector3* out) const;

    uint8_t m_bSplineOk;                              // +0x08 XXL2 m_bSplineOk (read fourth)
    uint8_t m_ui8NumberOfSegment;                     // +0x09 XXL2 m_ui8NumberOfSegment (read first)
    uint8_t m_pad0a[2];
    float m_fTotalLenght;                             // +0x0c
    float m_fPrecision;                               // +0x10
    TVector<CVector3, 4> CtrlPointsList;              // +0x14
    TVector<float, 1> SegmentLenghtList;              // +0x20
    TVector<uint8_t, 16> SplineSegmentRef;            // +0x2c
    TVector<float, 16> SplineUniformSamples;          // +0x38
    TVector<float, 16> SplineSegmentTransition;       // +0x44
};
DOTD_ASSERT_SIZE(CKSpline4, 0x50);
DOTD_ASSERT_OFFSET(CKSpline4, m_bSplineOk, 0x08);
DOTD_ASSERT_OFFSET(CKSpline4, m_ui8NumberOfSegment, 0x09);
DOTD_ASSERT_OFFSET(CKSpline4, m_fTotalLenght, 0x0c);
DOTD_ASSERT_OFFSET(CKSpline4, m_fPrecision, 0x10);
DOTD_ASSERT_OFFSET(CKSpline4, CtrlPointsList, 0x14);
DOTD_ASSERT_OFFSET(CKSpline4, SegmentLenghtList, 0x20);
DOTD_ASSERT_OFFSET(CKSpline4, SplineSegmentRef, 0x2c);
DOTD_ASSERT_OFFSET(CKSpline4, SplineUniformSamples, 0x38);
DOTD_ASSERT_OFFSET(CKSpline4, SplineSegmentTransition, 0x44);
