// CBBox.h - an axis-aligned box (XXL2: K/KUL/CBBox/CBBox.h: m_sup, m_inf; 0x18 bytes).
#pragma once
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"

struct CBBox {
    CVector3 m_sup;  // +0x00 the maximum corner
    CVector3 m_inf;  // +0x0c the minimum corner
};
DOTD_ASSERT_SIZE(CBBox, 0x18);

// 0x0023bce0 BBox_TransformByMatrix: the box that holds `in` through `m` (per axis: the position, then for each of the
// matrix's three rows the smaller of row * in.inf and row * in.sup added to the minimum, the larger to the maximum).
void BBox_TransformByMatrix(CBBox* out, const CBBox* in, const CMatrix34* m);
// 0x0023c4b8 AABB_ClampPoint: the point clamped into the box, axis by axis (each axis reads the point before writing
// it, so `out` may be `point`).
void AABB_ClampPoint(const CBBox* box, const CVector3* point, CVector3* out);
// 0x0023c280 AABB_ContainsAABB: `inner` lies inside `outer` (inner.sup <= outer.sup and outer.inf <= inner.inf on every
// axis; an unordered compare gives false).
bool AABB_ContainsAABB(const CBBox* inner, const CBBox* outer);
// 0x0023d550 BBox_SetFromCenterExtents_maybe (misc/BBox_2.cpp): the box around `center` with the half extents `half`
// (the two corners centre +- half folded into an empty box).
void BBox_SetFromCenterExtents(CBBox* box, const CVector3* center, const CVector3* half);

struct CLine;
// 0x0023ccb8 AABB_OverlapsSegmentBounds_maybe: the segment (a CLine) can touch the box: its bounds overlap the box's on
// x, z and y, and no separating axis of the cross products (the segment's direction with the three box axes) splits
// them.
uint8_t AABB_OverlapsSegmentBounds(const CBBox* box, const CLine* line);
