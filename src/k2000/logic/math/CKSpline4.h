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
    DOTD_DECLARE_FACTORIES(CKSpline4)

    CKSpline4();  // inlined in 0x000c5c70 CKSpline4_Create (CKSpline4_Construct 0xc51a0)
    ~CKSpline4() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000c5d20 CKSpline4_Load

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
