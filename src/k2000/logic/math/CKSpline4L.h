// CKSpline4L.h - a sampled spline path (key 0x7cc, vtable 0xb17d00, size 0x2c). Original unit:
// CKSpline4L.cpp. XXL2: K/KModules/KGL/Path/CKSpline4L.h (m_ui8NumberOfSegment, m_fTotalLenght,
// m_fPrecision, m_bSplineOk, CtrlPointsList, SamplePointsList; the same Load order).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/math/IKPath.h"
#include "k2000/math/CMatrix34.h"

class CKSpline4L : public IKPath {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x1f)
    DOTD_DECLARE_FACTORIES(CKSpline4L)

    CKSpline4L();  // inlined in CKSpline4L_Create
    ~CKSpline4L() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000c6f40 CKSpline4L_Load
    // vt+0x54 0x000c7420 CKSpline4L_GetPointAtDistance_maybe: the sample points are equally spaced (length / (count - 1));
    // the point on the segment the distance falls in (fmadds), the last point from the length on; a negative distance
    // counts as 0. With `direction`, that segment's direction (GetSegmentDirection).
    void GetPointAtDistance(float distance, CVector3* point, CVector3* direction) override;
    // vt+0x58 0x000c66a8 CKSpline4L_GetClosestDistanceAlong: the sample nearest to `point` (|d| sum or squared
    // length), then the projection on its segment towards the next sample (or the previous one), in units of the
    // sample spacing length / (count - 1).
    float GetClosestDistanceAlong(const CVector3* point, uint8_t squared) override;
    float GetLength() override { return m_fTotalLenght; }  // vt+0x5c 0x009a2090 CKSpline4L_GetLength
    // 0x000c7318 CKSpline4L_GetSegmentDirection: the normalised vector from sample `index` to the next one (from the one
    // before for the last sample); not normalised when its length is 0.
    void GetSegmentDirection(uint32_t index, CVector3* direction) const;

    uint8_t m_bSplineOk;                     // +0x08 XXL2 m_bSplineOk (read fourth)
    uint8_t m_ui8NumberOfSegment;            // +0x09 XXL2 m_ui8NumberOfSegment (read first)
    uint8_t m_pad0a[2];
    float m_fTotalLenght;                    // +0x0c
    float m_fPrecision;                      // +0x10
    TVector<CVector3, 4> CtrlPointsList;     // +0x14
    TVector<CVector3, 16> SamplePointsList;  // +0x20
};
DOTD_ASSERT_SIZE(CKSpline4L, 0x2c);
DOTD_ASSERT_OFFSET(CKSpline4L, m_bSplineOk, 0x08);
DOTD_ASSERT_OFFSET(CKSpline4L, m_ui8NumberOfSegment, 0x09);
DOTD_ASSERT_OFFSET(CKSpline4L, m_fTotalLenght, 0x0c);
DOTD_ASSERT_OFFSET(CKSpline4L, m_fPrecision, 0x10);
DOTD_ASSERT_OFFSET(CKSpline4L, CtrlPointsList, 0x14);
DOTD_ASSERT_OFFSET(CKSpline4L, SamplePointsList, 0x20);
