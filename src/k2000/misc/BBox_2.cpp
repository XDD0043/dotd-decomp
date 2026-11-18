// BBox_2.cpp - reconstructed original translation unit: 0x23d138-0x23dd68 (GAME_TOC1, main_toc1), 4 functions, 1 live.
// Primary owner: BBox (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x23d138  BBox_ExtendByAxisRectCorners_maybe  [dead]
//   [x] 0x23d550  BBox_SetFromCenterExtents_maybe
//   [ ] 0x23d670  BBox_ExtendByTransformedBBox_maybe  [dead]
//   [ ] 0x23d9e8  BBox_ExtendBySphere_maybe  [dead]
#include "k2000/math/CBBox.h"

// 0x0023d550 BBox_SetFromCenterExtents_maybe (from the assembly). The box starts empty (sup -FLT_MAX, inf FLT_MAX: the
// word 0x7f7fffff at 0x00c4ace0), then takes the two corners centre + half and centre - half (fadds / fsubs, stored in
// that order on the stack), each axis folded with the original's tests: the minimum is replaced unless it is already
// <= the corner (ble), the maximum unless it is already >= it (bge), so an unordered (NaN) corner is stored in both.
void BBox_SetFromCenterExtents(CBBox* box, const CVector3* center, const CVector3* half) {
    constexpr float kMax = 3.40282346638528859812e+38f;  // 0x7f7fffff
    float* const sup = &box->m_sup.x;
    float* const inf = &box->m_inf.x;
    inf[0] = kMax;
    inf[2] = kMax;
    inf[1] = kMax;
    sup[2] = -kMax;
    sup[1] = -kMax;
    sup[0] = -kMax;
    const float corners[6] = {center->x + half->x, center->y + half->y, center->z + half->z,
                              center->x - half->x, center->y - half->y, center->z - half->z};
    for (int c = 0; c < 2; ++c) {
        for (int axis = 0; axis < 3; ++axis) {
            const float v = corners[c * 3 + axis];
            if (!(inf[axis] <= v)) inf[axis] = v;
            if (!(sup[axis] >= v)) sup[axis] = v;
        }
    }
}
