// BBox.cpp - reconstructed original translation unit: 0x23bce0-0x23ccb8 (GAME_TOC1, main_toc1), 17 functions, 3 live.
// Primary owner: BBox (not a registered class)
// Other owners: AABB (6)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x23bce0  BBox_TransformByMatrix
//   [ ] 0x23be68  BBox_ExtendByXYZ_maybe  [dead]
//   [ ] 0x23bed0  BBox_ExtendByPoint_maybe  [dead]
//   [ ] 0x23bf58  BBox_ExtendByPoints_maybe  [dead]
//   [ ] 0x23c008  BBox_ScaleAboutCenterInPlace_maybe  [dead]
//   [ ] 0x23c098  BBox_ScaleAboutCenter_maybe  [dead]
//   [ ] 0x23c130  BBox_Inflate_maybe  [dead]
//   [ ] 0x23c180  BBox_GetCornersStrided_maybe  [dead]
//   [ ] 0x23c280  AABB_ContainsAABB
//   [ ] 0x23c310  BBox_ExtendByPoints_2_maybe  [dead]
//   [ ] 0x23c3c8  BBox_SplitIntoSlabsAlongAxis_maybe  [dead]
//   [x] 0x23c4b8  AABB_ClampPoint
//   [ ] 0x23c538  AABB_ComputeIntersection_maybe  [dead]
//   [ ] 0x23c640  AABB_OverlapsSegmentEndpoints_maybe  [dead]
//   [ ] 0x23c858  AABB_OverlapsSegmentEndpoints_2_maybe  [dead]
//   [ ] 0x23ca70  AABB_StepEntersBox_maybe  [dead]
//   [ ] 0x23cb28  FUN_0023cb28  [dead]
#include "k2000/math/CBBox.h"

// 0x0023bce0 BBox_TransformByMatrix. Per axis i the three products are compared and added in row order (right, up,
// at); unordered products take the second branch, as the original's ble / bgt.
void BBox_TransformByMatrix(CBBox* out, const CBBox* in, const CMatrix34* m) {
    const float* const sup = &in->m_sup.x;
    const float* const inf = &in->m_inf.x;
    const CVector3* const rows[3] = {&m->m_right, &m->m_up, &m->m_at};
    for (int i = 0; i < 3; ++i) {
        float* const outSup = &out->m_sup.x + i;
        float* const outInf = &out->m_inf.x + i;
        const float pos = (&m->m_pos.x)[i];
        *outInf = pos;
        *outSup = pos;
        for (int j = 0; j < 3; ++j) {
            const float e = (&rows[j]->x)[i];
            const float a = e * inf[j];
            const float b = e * sup[j];
            if (a > b) {
                *outInf = b + *outInf;
                *outSup = a + *outSup;
            } else {
                *outInf = a + *outInf;
                *outSup = b + *outSup;
            }
        }
    }
}

// 0x0023c4b8 AABB_ClampPoint. x and y: above the maximum gives the maximum, else at least the minimum gives the point,
// else (also unordered) the minimum. z: above the maximum the maximum, below the minimum the minimum, else (also
// unordered) the point.
void AABB_ClampPoint(const CBBox* box, const CVector3* point, CVector3* out) {
    if (point->x > box->m_sup.x) {
        out->x = box->m_sup.x;
    } else {
        out->x = point->x >= box->m_inf.x ? point->x : box->m_inf.x;
    }
    if (point->y > box->m_sup.y) {
        out->y = box->m_sup.y;
    } else {
        out->y = point->y >= box->m_inf.y ? point->y : box->m_inf.y;
    }
    if (point->z > box->m_sup.z) {
        out->z = box->m_sup.z;
    } else if (point->z < box->m_inf.z) {
        out->z = box->m_inf.z;
    } else {
        out->z = point->z;
    }
}
