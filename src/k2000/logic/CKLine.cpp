// CKLine.cpp - reconstructed original translation unit 0xc7648-0xc8278 (GAME_TOC1, main_toc1), 17 functions, 13 live.
// Primary class: CKLine  key 0x78c  category Logic  size 0x28  vtable 0xb17d68
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xc7648  CKLine_Delete
//   [ ] 0xc7698  CKLine_RecursiveRegistration
//   [ ] 0xc76a0  CKLine_Save
//   [ ] 0xc76a8  CKLine_Construct  [dead]
//   [ ] 0xc76f0  CKLine_Construct_2  [dead]
//   [ ] 0xc7738  RegisterCKLineClass
//   [ ] 0xc77b0  _GLOBAL__I_c77b0
//   [ ] 0xc77c0  CKLine_GetSegmentDirection_maybe  [dead]
//   [x] 0xc7898  CKLine_DeleteArray
//   [ ] 0xc7940  CKLine_vf50
//   [ ] 0xc7998  CKLine_GetSegmentLength_maybe  [dead]
//   [x] 0xc7a30  CKLine_GetClosestDistanceAlong
//   [ ] 0xc7c18  CKLine_Destroy
//   [x] 0xc7c20  CKLine_Create
//   [x] 0xc7c90  CKLine_CreateArray
//   [x] 0xc7d70  CKLine_Load
//   [x] 0xc8050  CKLine_GetPointAtDistance
//
//   [ ] 0x9a2220  CKLine_GetClassType  [inline]
//   [ ] 0x9a2228  CKLine_GetClassID  [inline]
//   [x] 0x9a2230  CKLine_GetLength  [inline]
//   [ ] 0x9a2238  CKLine_IsKindOfClass  [inline]
//   [ ] 0x9a2260  CKLine_Destructor  [inline]
//   [ ] 0x9a2308  CKLine_DeletingDestructor  [inline]
#include "k2000/logic/CKLine.h"

#include <cmath>

#include "crt/ppc_ops.h"

// 0x000c7a30 CKLine_GetClosestDistanceAlong. Per segment i (points i, i + 1, length SegmentLenghtList[i]):
// t = (e.P - e.A) / len^2 (fmuls / fmadds as below), t <= 0 gives 0 and t >= 1 gives 1 (a NaN stays), the point
// A + t e; a measure below the best (FLT_MAX at first, 0x00c4ace0; "best <= d" keeps the old one) gives the result
// t len + the segments' lengths before. No segment: 0.
float CKLine::GetClosestDistanceAlong(const CVector3* point, uint8_t squared) {
    float result = 0.0f;  // TOC -0x56d8
    if (m_ui8NumberOfSegment == 0) return result;
    float best = 3.40282347e+38f;  // *(TOC -0x56a8) + 0x28
    float before = 0.0f;
    for (int32_t i = 0;; ++i) {
        const CVector3& a = PointsList.m_pBlock[i];
        const CVector3& b = PointsList.m_pBlock[i + 1];
        const float ey = b.y - a.y;  // f7
        const float ex = b.x - a.x;  // f9
        const float ez = b.z - a.z;  // f10
        const float length = SegmentLenghtList.m_pBlock[i];
        const float onPoint = ppc::fmadds(ez, point->z, ppc::fmadds(ex, point->x, ey * point->y));
        const float onA = ppc::fmadds(a.z, ez, ppc::fmadds(a.x, ex, a.y * ey));
        float t = (onPoint - onA) / (length * length);
        if (t <= 0.0f) {  // cror lt|eq
            t = 0.0f;
        } else if (t >= 1.0f) {  // cror gt|eq; TOC -0x56ac
            t = 1.0f;
        }
        const float cx = ppc::fmadds(t, ex, a.x);
        const float cz = ppc::fmadds(t, ez, a.z);
        const float cy = ppc::fmadds(t, ey, a.y);
        float d;
        if (squared != 0) {
            const float dy = cy - point->y;
            const float dx = cx - point->x;
            const float dz = cz - point->z;
            d = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
        } else {
            d = (std::fabs(cx - point->x) + std::fabs(cy - point->y)) + std::fabs(cz - point->z);
        }
        if (!(d >= best)) {  // bge skips
            best = d;
            result = ppc::fmadds(t, length, before);
        }
        if (static_cast<int32_t>(m_ui8NumberOfSegment) <= i + 1) break;
        before = before + length;
    }
    return result;
}

// 0x000c8050 CKLine_GetPointAtDistance. The segment: the first whose cumulated length (from 0.0 + the first
// length) is not below the distance, else the last; t = (distance - (cumulated - its length)) / its length.
void CKLine::GetPointAtDistance(float distance, CVector3* point, CVector3* direction) {
    float d = distance;
    if (m_fTotalLenght < distance) d = m_fTotalLenght;  // blt keeps the length; a NaN distance stays
    const float* lengths = SegmentLenghtList.m_pBlock;
    float cumulated = lengths[0] + 0.0f;  // TOC -0x56d8
    uint32_t index = 0;
    if (!(d <= cumulated) && m_ui8NumberOfSegment > 1) {
        uint32_t i = 1;
        for (uint32_t n = static_cast<uint32_t>(m_ui8NumberOfSegment) - 1; n != 0; --n) {  // CTR count - 1
            cumulated = cumulated + lengths[i];
            index = i;
            if (!(d > cumulated)) break;  // bgt continues
            ++i;
        }
    }
    const float length = lengths[index];
    const float t = (d - (cumulated - length)) / length;
    const CVector3& a = PointsList.m_pBlock[index];
    const CVector3& b = PointsList.m_pBlock[index + 1];
    if (direction != nullptr) {
        const float dy = b.y - a.y;
        const float dx = b.x - a.x;
        const float dz = b.z - a.z;
        direction->y = dy;
        direction->x = dx;
        direction->z = dz;
        const float norm = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));  // 0x00010690 Math_Sqrtf
        if (norm != 0.0f) {
            const float inverse = 1.0f / norm;  // TOC -0x56ac
            const float z = inverse * direction->z;
            const float x = inverse * direction->x;
            const float y = inverse * direction->y;
            direction->z = z;
            direction->x = x;
            direction->y = y;
        }
    }
    point->x = ppc::fmadds(t, b.x - a.x, a.x);
    point->y = ppc::fmadds(t, b.y - a.y, a.y);
    point->z = ppc::fmadds(t, b.z - a.z, a.z);
}

// 0x000c76a8 CKLine_Construct (inlined in 0x000c7c20 CKLine_Create).
CKLine::CKLine() {
    InitPathVector(PointsList);
    InitPathVector(SegmentLenghtList);
}

// 0x000c7d70 CKLine_Load: no type test; the counts come from m_ui8NumberOfSegment.
int32_t CKLine::Load(IKFile* file, int32_t /*type*/) {
    m_pPathOwner = nullptr;
    ReadU8(file, &m_ui8NumberOfSegment);
    ReadF32LE(file, &m_fTotalLenght);
    LoadPathVector(file, PointsList, static_cast<uint32_t>(m_ui8NumberOfSegment) + 1, true);
    LoadPathVector(file, SegmentLenghtList, m_ui8NumberOfSegment, true);
    return 1;
}
