// CKLine.h - a polyline path (key 0x78c, vtable 0xb17d68, size 0x28). Original unit: CKLine.cpp.
// XXL2: K/KModules/KGL/Path/CKLine.h (m_ui8NumberOfSegment, m_fTotalLenght, PointsList,
// SegmentLenghtList).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/math/IKPath.h"
#include "k2000/math/CMatrix34.h"

class CKLine : public IKPath {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x1e)
    DOTD_DECLARE_FACTORIES(CKLine)

    CKLine();  // inlined in 0x000c7c20 CKLine_Create (CKLine_Construct 0xc76a8)
    ~CKLine() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000c7d70 CKLine_Load
    // vt+0x54 0x000c8050 CKLine_GetPointAtDistance: the point at `distance` (cut to the length; not clamped below
    // 0) on the segment whose cumulated length reaches it, and with `direction` that segment's normalised direction.
    void GetPointAtDistance(float distance, CVector3* point, CVector3* direction) override;
    // vt+0x58 0x000c7a30 CKLine_GetClosestDistanceAlong: per segment the projection of `point` (clamped to the
    // segment), the nearest one by the |d| sum or the squared length; its distance along the line.
    float GetClosestDistanceAlong(const CVector3* point, uint8_t squared) override;
    float GetLength() override { return m_fTotalLenght; }  // vt+0x5c 0x009a2230 CKLine_GetLength

    uint8_t m_ui8NumberOfSegment;           // +0x08
    uint8_t m_pad09[3];
    float m_fTotalLenght;                   // +0x0c
    TVector<CVector3, 4> PointsList;        // +0x10 m_ui8NumberOfSegment + 1 points
    TVector<float, 1> SegmentLenghtList;    // +0x1c
};
DOTD_ASSERT_SIZE(CKLine, 0x28);
DOTD_ASSERT_OFFSET(CKLine, m_ui8NumberOfSegment, 0x08);
DOTD_ASSERT_OFFSET(CKLine, m_fTotalLenght, 0x0c);
DOTD_ASSERT_OFFSET(CKLine, PointsList, 0x10);
DOTD_ASSERT_OFFSET(CKLine, SegmentLenghtList, 0x1c);
