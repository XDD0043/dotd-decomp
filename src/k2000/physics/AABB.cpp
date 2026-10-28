// AABB.cpp - reconstructed original translation unit: 0x23ccb8-0x23d138 (GAME_TOC1, main_toc1), 2 functions, 1 live.
// Primary owner: AABB (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x23ccb8  AABB_OverlapsSegmentBounds_maybe
//   [ ] 0x23cee0  AABB_OverlapsSegmentBoundsWithMargin_maybe  [dead]
#include <cmath>

#include "crt/ppc_ops.h"
#include "k2000/math/CBBox.h"
#include "k2000/services/CollisionDatas.h"

// 0x0023ccb8 AABB_OverlapsSegmentBounds_maybe. The bounds per axis in the order x, z, y (an end is the start, the other
// start + direction; a direction that is not >= 0 swaps them), then three separating-axis tests on twice the
// segment's middle against the box's centre (sums of the box's extents and |direction|, the absolute values of the
// cross products as the original takes them: the sign bit cleared through memory).
uint8_t AABB_OverlapsSegmentBounds(const CBBox* box, const CLine* line) {
    const CVector3& s = line->m_start;
    const CVector3& d = line->m_VectDir;
    float lo, hi;
    if (d.x >= 0.0f) {
        lo = s.x;
        hi = d.x + s.x;
    } else {
        hi = s.x;
        lo = d.x + s.x;
    }
    if (box->m_inf.x > hi || box->m_sup.x < lo) return 0;
    if (d.z >= 0.0f) {
        lo = s.z;
        hi = d.z + s.z;
    } else {
        hi = s.z;
        lo = d.z + s.z;
    }
    if (box->m_inf.z > hi || box->m_sup.z < lo) return 0;
    if (d.y >= 0.0f) {
        lo = s.y;
        hi = d.y + s.y;
    } else {
        hi = s.y;
        lo = d.y + s.y;
    }
    if (box->m_inf.y > hi || box->m_sup.y < lo) return 0;
    const float extentZ = box->m_sup.z - box->m_inf.z;
    const float extentY = box->m_sup.y - box->m_inf.y;
    const float absDy = std::fabs(d.y);
    const float absDz = std::fabs(d.z);
    const float cy = (d.y + (s.y + s.y)) - (box->m_inf.y + box->m_sup.y);
    const float cz = (d.z + (s.z + s.z)) - (box->m_inf.z + box->m_sup.z);
    const float radiusX = ppc::fmadds(absDz, extentY, absDy * extentZ);
    if (radiusX < std::fabs(ppc::fmsubs(d.y, cz, d.z * cy))) return 0;
    const float extentX = box->m_sup.x - box->m_inf.x;
    const float absDx = std::fabs(d.x);
    const float cx = (d.x + (s.x + s.x)) - (box->m_inf.x + box->m_sup.x);
    const float radiusY = ppc::fmadds(absDz, extentX, extentZ * absDx);
    if (radiusY < std::fabs(ppc::fmsubs(d.z, cx, cz * d.x))) return 0;
    const float radiusZ = ppc::fmadds(absDy, extentX, extentY * absDx);
    return std::fabs(ppc::fmsubs(cy, d.x, d.y * cx)) > radiusZ ? 0 : 1;
}
