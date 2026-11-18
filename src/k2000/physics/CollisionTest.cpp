// CollisionTest.cpp - reconstructed original translation unit: 0x19d020-0x19f3e8 (GAME_TOC1, main_toc1), 8 functions, 8 live.
// Primary owner: CollisionTest (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x19d020  CollisionTest_AABoxVsAABox_maybe  (collision_test::AABoxVsAABox)
//   [x] 0x19d268  CollisionTest_SweptAABoxVsSweptAABox_maybe  (port-final F05: SweptBoxesContact with the relative move)
//   [x] 0x19d938  CollisionTest_AABoxVsSweptAABox_maybe  (port-final F05: SweptBoxesContact)
//   [x] 0x19dff0  CollisionTest_AABoxVsSphere_maybe
//   [x] 0x19e450  CollisionTest_AABoxVsSweptSphere_maybe
//   [x] 0x19e950  CollisionTest_CylinderVsCylinder_maybe  (collision_test::CylinderVsCylinder)
//   [x] 0x19eaa0  CollisionTest_CylinderVsSphere_maybe
//   [x] 0x19ee08  CollisionTest_OBBVsAABox_maybe  (port-final F05)
//
//   [x] 0x9aa710  CollisionTest_SweptAABoxVsAABoxSwapped_maybe  [inline]
//   [x] 0x9aa790  CollisionTest_SphereVsCylinder_maybe  [inline]
//   [x] 0x9aa810  CollisionTest_SweptSphereVsSphere_maybe  [inline]
//   [x] 0x9aa890  CollisionTest_SweptSphereVsBox_maybe  [inline]
//   [x] 0x9aa910  CollisionTest_SphereVsBox_maybe  [inline]
//   [x] 0x9aa990  CollisionTest_AABoxVsOBB_maybe  [inline]
//   [x] 0x9aaa10  CollisionTest_SweptSphereVsAABox_maybe  [inline]
//   [x] 0x9aaa90  CollisionTest_SphereVsAABox_maybe  [inline]
//   [ ] 0x9aab10  KStub_Return1_9aab10  [inline]
#include "k2000/physics/CollisionTest.h"

#include <cmath>

#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "k2000/core/Stub.h"
#include "k2000/math/Vec3.h"
#include "k2000/scenegraph/CKAACylinder.h"
#include "k2000/scenegraph/CKDynamicAABB.h"
#include "k2000/scenegraph/CKDynamicBoundingSphere.h"
#include "k2000/scenegraph/IKBoundingBox.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/services/CKSrvCollision.h"

namespace collision_test {

namespace {
// The volume's centre and frame matrix: its frame's LTM (RwFrame +0x50, the position +0x80; read as stored).
const CVector3* Position(const IKBoundingVolume* volume) {
    return reinterpret_cast<const CVector3*>(&volume->m_pRwFrame->ltm.pos);
}
const RwMatrix& Ltm(const IKBoundingVolume* volume) { return volume->m_pRwFrame->ltm; }
}  // namespace

// 0x0019d020 CollisionTest_AABoxVsAABox_maybe (P21): two axis-aligned boxes (half sizes +0x2c). Per axis (x, y, z)
// the overlap: with d = b - a above 0 (fcmpu + ble: NaN takes the other side) the extents' sum minus d, else d plus it;
// an overlap below or equal to 0 is no contact (NaN goes on). The contact point on that axis is the middle of the
// overlap: fmadds(overlap, -0.5, a + extent) or fmadds(overlap, 0.5, a - extent). Response 8; no normal.
uint8_t AABoxVsAABox(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set) {
    const IKBoundingBox* ba = static_cast<const IKBoundingBox*>(a);
    const IKBoundingBox* bb = static_cast<const IKBoundingBox*>(b);
    const CVector3* pa = Position(a);
    const CVector3* pb = Position(b);
    const float d[3] = {pb->x - pa->x, pb->y - pa->y, pb->z - pa->z};
    const float ea[3] = {ba->m_Extent.x, ba->m_Extent.y, ba->m_Extent.z};
    const float eb[3] = {bb->m_Extent.x, bb->m_Extent.y, bb->m_Extent.z};
    const float p[3] = {pa->x, pa->y, pa->z};
    float contact[3];
    for (int axis = 0; axis < 3; ++axis) {
        float overlap;
        if (d[axis] > 0.0f) {  // TOC -0x2920
            overlap = (ea[axis] + eb[axis]) - d[axis];
            if (overlap < 0.0f || overlap == 0.0f) return 0;
            contact[axis] = ppc::fmadds(overlap, -0.5f, ea[axis] + p[axis]);  // TOC -0x2924
        } else {
            overlap = d[axis] + (ea[axis] + eb[axis]);
            if (overlap < 0.0f || overlap == 0.0f) return 0;
            contact[axis] = ppc::fmadds(overlap, 0.5f, p[axis] - ea[axis]);  // TOC -0x2928
        }
    }
    set->m_Infos = (set->m_Infos & 0xfffffff0u) | 8u;
    set->m_WorldContactPoint.x = contact[0];
    set->m_WorldContactPoint.z = contact[2];
    set->m_WorldContactPoint.y = contact[1];
    return 1;
}

/// 0x0019d938 CollisionTest_AABoxVsSweptAABox_maybe (C2.8 port-final F05): a box (a) against a moving box (b, a
// CKDynamicAABB moving by its +0x38 vector v this frame). Per axis (x, y, z: the boxes' frame positions, the half sizes
// +0x2c) the entry time (0 when overlapping, else the gap over v: none when v does not close it or the time is past 1)
// and the exit time (1, or when v carries b out of a); the compares follow the original's branches axis by axis (their
// NaN sides differ: x and y take the overlap side on an unordered start test, z the gap side; some time tests let an
// unordered time through, others not). The latest entry (the larger of y / z picked first, then x when later) against the
// earliest exit; a contact needs entry <= exit and entry above 0. The time goes to the set; the axis whose gap at that
// time (|d + v t| - the extents' sum, fused) is within 1e-6 gives response 5 and the unit normal along it (sign of the
// gap), x first; none: response 1 without a normal.
namespace {
// The body of 0x19d938 and 0x19d268 (the same instructions; the second takes v as the difference of the moves): a's and
// b's frame positions and half sizes, b's motion relative to a.
uint8_t SweptBoxesContact(IKBoundingVolume* a, IKBoundingVolume* b, const CVector3 v, CContactSet* set) {
    const IKBoundingBox* ba = static_cast<const IKBoundingBox*>(a);
    const IKBoundingBox* bb = static_cast<const IKBoundingBox*>(b);
    float enter[3] = {0.0f, 0.0f, 0.0f};  // TOC1 -0x2920
    float exit[3] = {1.0f, 1.0f, 1.0f};   // TOC1 -0x291c
    const CVector3* pb = Position(b);
    const CVector3* pa = Position(a);
    const CVector3& ea = ba->m_Extent;
    const CVector3& eb = bb->m_Extent;
    // x
    {
        const float aMax = ea.x + pa->x;
        const float bMin = pb->x - eb.x;
        if (aMax < bMin) {
            if (!(v.x < 0.0f)) return 0;  // bge
            const float t = (aMax - bMin) / v.x;
            if (t > 1.0f) return 0;
            enter[0] = t;
        } else {
            const float bMax = eb.x + pb->x;
            const float aMin = pa->x - ea.x;
            if (!(bMax >= aMin)) {
                if (!(v.x > 0.0f)) return 0;  // ble
                const float t = (aMin - bMax) / v.x;
                if (t > 1.0f) return 0;
                enter[0] = t;
            }
        }
        const float bMax = eb.x + pb->x;
        const float aMin = pa->x - ea.x;
        if (bMax > aMin && (v.x < 0.0f || v.x == 0.0f)) {
            if (v.x < 0.0f) exit[0] = (aMin - bMax) / v.x;
        } else {
            const float aMax2 = ea.x + pa->x;
            const float bMin2 = pb->x - eb.x;
            if (!(aMax2 > bMin2)) return 0;
            if (!(v.x > 0.0f || v.x == 0.0f)) return 0;
            if (v.x > 0.0f) exit[0] = (aMax2 - bMin2) / v.x;
        }
    }
    // y
    {
        const float aMax = ea.y + pa->y;
        const float bMin = pb->y - eb.y;
        if (aMax < bMin) {
            if (!(v.y < 0.0f)) return 0;
            const float t = (aMax - bMin) / v.y;
            if (!(t <= 1.0f)) return 0;  // ble+: an unordered time stops here
            enter[1] = t;
        } else {
            const float bMax = eb.y + pb->y;
            const float aMinY = pa->y - ea.y;
            if (!(bMax >= aMinY)) {
                if (!(v.y > 0.0f)) return 0;
                const float t = (aMinY - bMax) / v.y;
                if (t > 1.0f) return 0;
                enter[1] = t;
            }
        }
        const float bMax = eb.y + pb->y;
        const float aMin = pa->y - ea.y;
        if (bMax > aMin && (v.y < 0.0f || v.y == 0.0f)) {
            if (v.y < 0.0f) exit[1] = (aMin - bMax) / v.y;
        } else {
            const float aMax2 = ea.y + pa->y;
            const float bMin2 = pb->y - eb.y;
            if (!(aMax2 > bMin2)) return 0;
            if (!(v.y > 0.0f || v.y == 0.0f)) return 0;
            if (v.y > 0.0f) exit[1] = (aMax2 - bMin2) / v.y;
        }
    }
    // z
    {
        const float aMax = ea.z + pa->z;
        const float bMin = pb->z - eb.z;
        if (!(aMax >= bMin)) {  // bge to the overlap side: an unordered compare takes the gap side
            if (!(v.z < 0.0f)) return 0;
            const float t = (aMax - bMin) / v.z;
            if (t > 1.0f) return 0;
            enter[2] = t;
        } else {
            const float bMax = eb.z + pb->z;
            const float aMin = pa->z - ea.z;
            if (!(bMax >= aMin)) {
                if (!(v.z > 0.0f)) return 0;
                const float t = (aMin - bMax) / v.z;
                if (!(t <= 1.0f)) return 0;  // ble+
                enter[2] = t;
            }
        }
        const float bMax = eb.z + pb->z;
        const float aMin = pa->z - ea.z;
        if (bMax > aMin && (v.z < 0.0f || v.z == 0.0f)) {
            if (v.z < 0.0f) exit[2] = (aMin - bMax) / v.z;
        } else {
            const float aMax2 = ea.z + pa->z;
            const float bMin2 = pb->z - eb.z;
            if (!(aMax2 > bMin2)) return 0;
            if (!(v.z > 0.0f || v.z == 0.0f)) return 0;
            if (v.z > 0.0f) exit[2] = (aMax2 - bMin2) / v.z;
        }
    }
    const float laterYZ = enter[1] > enter[2] ? enter[1] : enter[2];
    const float tEnter = laterYZ < enter[0] ? enter[0] : laterYZ;
    const float earlierYZ = exit[1] > exit[2] ? exit[2] : exit[1];
    const float tExit = earlierYZ < exit[0] ? earlierYZ : exit[0];
    if (!(tEnter <= tExit)) return 0;
    if (!(tEnter > 0.0f)) return 0;
    set->m_fUDeltaTime = tEnter;
    const CVector3* qb = Position(b);
    const CVector3* qa = Position(a);
    constexpr float kTolerance = 0x1.0c6f7ap-20f;  // TOC1 -0x2918 1e-6 (0x358637bd); -0x2914 its negative
    const float hx = ppc::fmadds(tEnter, v.x, qb->x - qa->x);
    const float gx = std::fabs(hx) - (ea.x + eb.x);
    if (!(gx >= kTolerance) && !(gx <= -kTolerance)) {
        set->m_Infos = (set->m_Infos & 0xfffffff0u) | 5u;
        set->m_Normale12.x = hx < 0.0f ? -1.0f : 1.0f;
        set->m_Normale12.z = 0.0f;
        set->m_Normale12.y = 0.0f;
        return 1;
    }
    const float hy = ppc::fmadds(tEnter, v.y, qb->y - qa->y);
    const float gy = std::fabs(hy) - (ea.y + eb.y);
    if (!(gy >= kTolerance) && !(gy <= -kTolerance)) {
        set->m_Infos = (set->m_Infos & 0xfffffff0u) | 5u;
        set->m_Normale12.x = 0.0f;
        set->m_Normale12.z = 0.0f;
        set->m_Normale12.y = hy < 0.0f ? -1.0f : 1.0f;
        return 1;
    }
    const float hz = ppc::fmadds(tEnter, v.z, qb->z - qa->z);
    const float gz = std::fabs(hz) - (ea.z + eb.z);
    if (!(gz >= kTolerance) && !(gz <= -kTolerance)) {
        set->m_Infos = (set->m_Infos & 0xfffffff0u) | 5u;
        set->m_Normale12.x = 0.0f;
        set->m_Normale12.z = hz < 0.0f ? -1.0f : 1.0f;
        set->m_Normale12.y = 0.0f;
        return 1;
    }
    set->m_Infos = (set->m_Infos & 0xfffffff0u) | 1u;
    return 1;
}
}  // namespace

uint8_t AABoxVsSweptAABox(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set) {
    return SweptBoxesContact(a, b, static_cast<const CKDynamicAABB*>(b)->m_v3Unk38, set);
}

// 0x0019d268 CollisionTest_SweptAABoxVsSweptAABox_maybe (C2.8 port-final F05): two moving boxes (CKDynamicAABB):
// AABoxVsSweptAABox's test with b's motion relative to a's (b's +0x38 minus a's; x, z, y subtractions).
uint8_t SweptAABoxVsSweptAABox(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set) {
    const CVector3& va = static_cast<const CKDynamicAABB*>(a)->m_v3Unk38;
    const CVector3& vb = static_cast<const CKDynamicAABB*>(b)->m_v3Unk38;
    CVector3 v;
    v.x = vb.x - va.x;
    v.z = vb.z - va.z;
    v.y = vb.y - va.y;
    return SweptBoxesContact(a, b, v, set);
}

// 0x0019dff0 CollisionTest_AABoxVsSphere_maybe: BoxVsSphere's test with the box's axes the world's (the centre's
// offset is the local point; the normal is the scaled outside part).
uint8_t AABoxVsSphere(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set) {
    const CVector3* pa = Position(a);
    const CVector3* pb = Position(b);
    const float radii = a->m_fRadius + b->m_fRadius;
    if (!(radii >= std::fabs(pa->x - pb->x))) return 0;
    if (!(radii >= std::fabs(pa->z - pb->z))) return 0;
    if (!(radii >= std::fabs(pa->y - pb->y))) return 0;
    const IKBoundingBox* box = static_cast<const IKBoundingBox*>(a);
    float lx = 0.0f, ly = 0.0f, lz = 0.0f;
    const float ex = box->m_Extent.x, ey = box->m_Extent.y, ez = box->m_Extent.z;
    const float r2 = b->m_fRadius * b->m_fRadius;
    float sum = 0.0f;
    const float p0 = pb->x - pa->x;
    if (-ex > p0) {
        const float c = p0 + ex;
        sum = ppc::fmadds(c, c, 0.0f);
        if (r2 <= sum) return 0;
        lx = c;
    } else if (p0 > ex) {
        const float c = p0 - ex;
        sum = ppc::fmadds(c, c, 0.0f);
        if (r2 <= sum) return 0;
        lx = c;
    }
    const float p1 = pb->y - pa->y;
    if (-ey > p1) {
        const float c = p1 + ey;
        sum = ppc::fmadds(c, c, sum);
        if (r2 <= sum) return 0;
        ly = c;
    } else if (p1 > ey) {
        const float c = p1 - ey;
        sum = ppc::fmadds(c, c, sum);
        if (r2 <= sum) return 0;
        ly = c;
    }
    const float p2 = pb->z - pa->z;
    if (-ez > p2) {
        const float c = p2 + ez;
        sum = ppc::fmadds(c, c, sum);
        if (r2 <= sum) return 0;
        lz = c;
    } else if (p2 > ez) {
        const float c = p2 - ez;
        sum = ppc::fmadds(c, c, sum);
        if (r2 <= sum) return 0;
        lz = c;
    }
    if (sum != 0.0f) {
        set->m_Infos = (set->m_Infos & 0xfffffff0u) | 0xeu;
        const float distance = std::sqrt(sum);  // fsqrts
        const float inverse = 1.0f / distance;
        set->m_fdInterpenetration = b->m_fRadius - distance;
        set->m_Normale12.x = inverse * lx;
        set->m_Normale12.y = inverse * ly;
        set->m_Normale12.z = inverse * lz;
        const float along = ppc::fnmadds(set->m_fdInterpenetration, -0.5f, b->m_fRadius);
        const float cx = pb->x, cy = pb->y, cz = pb->z;
        set->m_WorldContactPoint.x = cx;
        set->m_WorldContactPoint.y = cy;
        set->m_WorldContactPoint.z = cz;
        set->m_WorldContactPoint.z = ppc::fmadds(along, set->m_Normale12.z, cz);
        set->m_WorldContactPoint.x = ppc::fmadds(along, set->m_Normale12.x, cx);
        set->m_WorldContactPoint.y = ppc::fmadds(along, set->m_Normale12.y, cy);
        return 1;
    }
    float best = 3.4028235e+38f;  // 0x00c4acb8 +0x28 (FLT_MAX)
    {
        const float c = p0 < 0.0f ? -(ex + p0) : -(p0 - ex);
        const float sq = c * c;
        if (best > sq) {
            sum = sq;
            lz = 0.0f;
            best = sq;
            lx = c;
            ly = 0.0f;
        }
    }
    {
        const float c = p1 < 0.0f ? -(ey + p1) : -(p1 - ey);
        const float sq = c * c;
        if (best > sq) {
            sum = sq;
            lz = 0.0f;
            best = sq;
            ly = c;
            lx = 0.0f;
        }
    }
    {
        const float c = p2 < 0.0f ? -(p2 + ez) : -(p2 - ez);
        const float sq = c * c;
        if (sq < best) {
            sum = sq;
            ly = 0.0f;
            lz = c;
            lx = 0.0f;
        }
    }
    if (sum == 0.0f) {
        set->m_Infos = (set->m_Infos & 0xfffffff0u) | 2u;
        set->m_fdInterpenetration = b->m_fRadius;
        return 1;
    }
    set->m_Infos = (set->m_Infos & 0xfffffff0u) | 6u;
    const float depth = std::sqrt(sum);  // fsqrts
    const float inverse = 1.0f / depth;
    set->m_fdInterpenetration = depth + b->m_fRadius;
    set->m_Normale12.x = inverse * lx;
    set->m_Normale12.y = inverse * ly;
    set->m_Normale12.z = inverse * lz;
    return 1;
}

// 0x0019e450 CollisionTest_AABoxVsSweptSphere_maybe: an axis-aligned box against a moving sphere: the slabs of the world
// axes x, y, z (the box's extent widened by the sphere's radius), BoxVsSweptSphere's way. The normal is the axis that
// gave the entry time with the sign of the last axis that was not parallel to the move.
// BUG(original): that sign comes from the last non-parallel axis, not from the entry axis (f11 is reloaded for every
// axis); the entry axis is not set when no slab is entered (then the sphere test answers and it is not read).
uint8_t AABoxVsSweptSphere(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set) {
    constexpr float kMax = 3.4028235e+38f;          // 0x00c4acb8 +0x28 (FLT_MAX)
    constexpr float kLatest = 0x1.00001p+0f;        // 1.0000010 (0x3f800008)
    constexpr float kEarliest = -0x1.0c6f7ap-20f;   // -1e-6 (0xb58637bd)
    const CKDynamicBoundingSphere* moving = static_cast<const CKDynamicBoundingSphere*>(b);
    const CVector3* start = ((b->m_ba8Infos >> 4) & 1) != 0 ? &moving->m_v3OldPos : Position(b);
    const IKBoundingBox* box = static_cast<const IKBoundingBox*>(a);
    const CVector3* pos = Position(a);
    const float r = b->m_fRadius;
    const float v[3] = {moving->m_v3WorldMove.x, moving->m_v3WorldMove.y, moving->m_v3WorldMove.z};
    const float s[3] = {start->x, start->y, start->z};
    const float p[3] = {pos->x, pos->y, pos->z};
    const float e[3] = {box->m_Extent.x, box->m_Extent.y, box->m_Extent.z};
    float tmin = -kMax;
    float tmax = kMax;
    float sign = 0.0f;  // f11
    int axis = 0;       // r31
    for (int i = 0; i < 3; ++i) {
        const float width = r + e[i];
        if (v[i] == 0.0f) {
            if (p[i] - width > s[i]) return 0;
            if (width + p[i] < s[i]) return 0;
            continue;
        }
        const float inverse = 1.0f / v[i];
        const float d = p[i] - s[i];
        float hi = inverse * (width + d);
        float lo = inverse * (d - width);
        if (hi < lo) {
            const float swap = lo;
            lo = hi;
            hi = swap;
            sign = 1.0f;
        } else {
            sign = -1.0f;
        }
        if (i < 2) {
            if (tmin < lo) {
                tmin = lo;
                axis = i;
            }
            if (tmax > hi) tmax = hi;
            if (tmin > tmax) return 0;
            if (tmax < 0.0f) return 0;
        } else {
            if (lo > tmin) {
                tmin = lo;
                axis = i;
            }
            const float exit = hi < tmax ? hi : tmax;
            if (tmin > exit) return 0;
            if (exit < 0.0f) return 0;
        }
    }
    if (tmin > kLatest) return 0;
    if (tmin < kEarliest) return AABoxVsSphere(a, b, set);  // touching at the start
    set->m_Infos = (set->m_Infos & 0xfffffff0u) | 0xdu;
    set->m_fUDeltaTime = tmin;
    set->m_Normale12.x = 0.0f;  // g_nullVector 0x00c50d64
    set->m_Normale12.y = 0.0f;
    set->m_Normale12.z = 0.0f;
    (&set->m_Normale12.x)[axis] = sign;
    const float back = -r;
    const float cx = ppc::fmadds(tmin, v[0], s[0]);
    const float cz = ppc::fmadds(tmin, v[2], s[2]);
    const float cy = ppc::fmadds(tmin, v[1], s[1]);
    set->m_WorldContactPoint.x = ppc::fmadds(back, set->m_Normale12.x, cx);
    set->m_WorldContactPoint.z = ppc::fmadds(back, set->m_Normale12.z, cz);
    set->m_WorldContactPoint.y = ppc::fmadds(back, set->m_Normale12.y, cy);
    return 1;
}

// 0x0019e950 CollisionTest_CylinderVsCylinder_maybe (P21): two vertical cylinders (radius +0x2c, half height +0x30).
// |dy| above the half heights' sum, |dx| or |dz| above the radii's sum, or the horizontal distance squared above the
// sum squared: no contact (fcmpu + blt: NaN goes on). Else at a horizontal distance above 0 response 6, the horizontal
// normal (the y part 0 x the inverse) and the interpenetration (radii - distance); at 0 (or NaN) response 2 and the
// interpenetration the radii's sum.
uint8_t CylinderVsCylinder(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set) {
    const CKAACylinder* ca = static_cast<const CKAACylinder*>(a);
    const CKAACylinder* cb = static_cast<const CKAACylinder*>(b);
    const CVector3* pa = Position(a);
    const CVector3* pb = Position(b);
    if (ca->m_fCylinderHalfHeight + cb->m_fCylinderHalfHeight < std::fabs(pb->y - pa->y)) return 0;
    const float radii = ca->m_fCylinderRadius + cb->m_fCylinderRadius;
    const float dx = pb->x - pa->x;
    if (radii < std::fabs(dx)) return 0;
    const float dz = pb->z - pa->z;
    if (radii < std::fabs(dz)) return 0;
    const float squared = ppc::fmadds(dx, dx, dz * dz);
    if (radii * radii < squared) return 0;
    const float distance = std::sqrt(squared);  // fsqrts
    const float zero = 0.0f;                    // TOC -0x2894
    if (distance > zero) {
        const float inverse = 1.0f / distance;  // TOC -0x2898
        set->m_Infos = (set->m_Infos & 0xfffffff0u) | 6u;
        set->m_Normale12.x = inverse * dx;
        set->m_Normale12.z = inverse * dz;
        set->m_Normale12.y = inverse * zero;
        set->m_fdInterpenetration = radii - distance;
        return 1;
    }
    set->m_Infos = (set->m_Infos & 0xfffffff0u) | 2u;
    set->m_fdInterpenetration = radii;
    return 1;
}

// 0x0019eaa0 CollisionTest_CylinderVsSphere_maybe: a vertical cylinder (radius +0x2c, half height +0x30) against a
// sphere. The centres within the sum of the radii on each axis (x, z, y), then the sphere's centre against the caps
// (the vertical part outside) and the side (the horizontal part outside the radius). Outside: response 0xe, the
// interpenetration (radius - distance), the normal from the cylinder and the contact point pushed back by half of it.
// Inside: response 0xe, the depth to the nearer cap and to the side summed (squared), depth + radius, the contact
// point the sphere's centre.
uint8_t CylinderVsSphere(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set) {
    const CVector3* pa = Position(a);
    const CVector3* pb = Position(b);
    const float radii = a->m_fRadius + b->m_fRadius;
    if (!(radii >= std::fabs(pa->x - pb->x))) return 0;
    if (!(radii >= std::fabs(pa->z - pb->z))) return 0;
    if (!(radii >= std::fabs(pa->y - pb->y))) return 0;
    const CKAACylinder* cylinder = static_cast<const CKAACylinder*>(a);
    const float half = cylinder->m_fCylinderHalfHeight;
    const float dy = pb->y - pa->y;
    float vertical = 0.0f;  // the part outside the caps (stack -0x10)
    float vertical2;        // its square
    if (-half > dy) {
        const float c = dy + half;
        if (-b->m_fRadius >= c) return 0;
        vertical = c;
        vertical2 = c * c;
    } else {
        vertical2 = 0.0f;
        if (dy > half) {
            const float c = dy - half;
            if (b->m_fRadius <= c) return 0;
            vertical = c;
            vertical2 = c * c;
        }
    }
    const float dz = pb->z - pa->z;
    const float radius = cylinder->m_fCylinderRadius;
    const float dx = pb->x - pa->x;
    const float reach = radius + b->m_fRadius;
    float horizontal2 = ppc::fmadds(dx, dx, dz * dz);
    if (reach * reach <= horizontal2) return 0;
    const float radius2 = radius * radius;
    float sideX, sideZ;  // the horizontal part outside the radius (f2 / f4)
    if (horizontal2 > radius2) {
        const float distance = std::sqrt(horizontal2);  // fsqrts
        const float out = distance - radius;
        vertical2 = ppc::fmadds(out, out, vertical2);
        if (b->m_fRadius * b->m_fRadius <= vertical2) return 0;
        const float scale = 1.0f - radius * (1.0f / distance);
        sideZ = dz * scale;
        sideX = dx * scale;
    } else {
        sideZ = 0.0f;
        sideX = 0.0f;
    }
    if (vertical2 != 0.0f) {
        set->m_Infos = (set->m_Infos & 0xfffffff0u) | 0xeu;
        const float distance = std::sqrt(vertical2);  // fsqrts
        set->m_fdInterpenetration = b->m_fRadius - distance;
        const float inverse = 1.0f / distance;
        set->m_Normale12.x = inverse * sideX;
        set->m_Normale12.z = inverse * sideZ;
        set->m_Normale12.y = vertical * inverse;
        const float along = ppc::fnmadds(set->m_fdInterpenetration, -0.5f, b->m_fRadius);
        const float cx = pb->x, cy = pb->y, cz = pb->z;
        set->m_WorldContactPoint.x = cx;
        set->m_WorldContactPoint.y = cy;
        set->m_WorldContactPoint.z = cz;
        set->m_WorldContactPoint.z = ppc::fmadds(along, set->m_Normale12.z, cz);
        set->m_WorldContactPoint.x = ppc::fmadds(along, set->m_Normale12.x, cx);
        set->m_WorldContactPoint.y = ppc::fmadds(along, set->m_Normale12.y, cy);
        return 1;
    }
    // Inside: the depth to the nearer cap, then to the side.
    const float cap = dy < 0.0f ? -(dy + half) : -(dy - half);
    const float cap2 = ppc::fmadds(cap, cap, vertical2);
    float total;
    float nx, nz;
    if (!(horizontal2 > 0.0f)) {
        total = cap2 + radius2;
        nz = 0.0f;
        nx = 1.0f;
    } else {
        const float distance = std::sqrt(horizontal2);  // fsqrts
        const float in = radius - distance;
        const float scale = ppc::fmsubs(radius, 1.0f / distance, 1.0f);
        total = ppc::fmadds(in, in, cap2);
        nz = dz * scale;
        nx = dx * scale;
    }
    set->m_Infos = (set->m_Infos & 0xfffffff0u) | 0xeu;
    const float depth = std::sqrt(total);  // fsqrts
    set->m_fdInterpenetration = depth + b->m_fRadius;
    const float inverse = 1.0f / depth;
    set->m_Normale12.x = inverse * nx;
    set->m_Normale12.z = nz * inverse;
    set->m_Normale12.y = cap * inverse;
    set->m_WorldContactPoint.x = pb->x;
    set->m_WorldContactPoint.z = pb->z;
    set->m_WorldContactPoint.y = pb->y;
    return 1;
}

/// 0x0019ee08 CollisionTest_OBBVsAABox_maybe (C2.8 port-final F05): an oriented box (a: its frame's LTM rows right / up /
// at as its axes, the half sizes +0x2c) against an axis-aligned box (b). First the frame positions within the sum of the
// radii (+0x20) on each axis (x, z, y; cror gt|eq: an unordered distance fails). Then the 15 separating axes of the
// box pair in the original's order (a's three axes, the world's three, the nine cross products), each a projected
// distance against the projected extents (fused as the original: fmadds chains, the cross terms fmsubs); an axis where
// the distance is above the extent or below its negative separates them (bgt: unordered values do not). Touching:
// response 0, no time, normal or point.
uint8_t OBBVsAABox(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set) {
    const IKBoundingBox* oa = static_cast<const IKBoundingBox*>(a);
    const IKBoundingBox* bb = static_cast<const IKBoundingBox*>(b);
    {
        const CVector3* pa = Position(a);
        const CVector3* pb = Position(b);
        const float radii = a->m_fRadius + b->m_fRadius;
        if (!(radii >= std::fabs(pa->x - pb->x))) return 0;
        if (!(radii >= std::fabs(pa->z - pb->z))) return 0;
        if (!(radii >= std::fabs(pa->y - pb->y))) return 0;
    }
    const CVector3* pb = Position(b);
    const CVector3* pa = Position(a);
    const RwMatrix& m = Ltm(a);
    const float dx = pb->x - pa->x;
    const float dy = pb->y - pa->y;
    const float dz = pb->z - pa->z;
    const CVector3& ea = oa->m_Extent;
    const CVector3& eb = bb->m_Extent;
    // a's right axis
    const float a00 = std::fabs(m.right.x), a01 = std::fabs(m.right.y), a02 = std::fabs(m.right.z);
    const float p0 = ppc::fmadds(dz, m.right.z, ppc::fmadds(dx, m.right.x, dy * m.right.y));
    float limit = ppc::fmadds(a02, eb.z, ppc::fmadds(a00, eb.x, a01 * eb.y)) + ea.x;
    if (p0 > limit || -limit > p0) return 0;
    // a's up axis
    const float a10 = std::fabs(m.up.x), a11 = std::fabs(m.up.y), a12 = std::fabs(m.up.z);
    const float p1 = ppc::fmadds(dz, m.up.z, ppc::fmadds(dx, m.up.x, dy * m.up.y));
    limit = ppc::fmadds(a12, eb.z, ppc::fmadds(a10, eb.x, a11 * eb.y)) + ea.y;
    if (p1 > limit || -limit > p1) return 0;
    // a's at axis
    const float a20 = std::fabs(m.at.x), a21 = std::fabs(m.at.y), a22 = std::fabs(m.at.z);
    const float p2 = ppc::fmadds(dz, m.at.z, ppc::fmadds(dx, m.at.x, dy * m.at.y));
    limit = ppc::fmadds(a22, eb.z, ppc::fmadds(a20, eb.x, a21 * eb.y)) + ea.z;
    if (p2 > limit || -limit > p2) return 0;
    // the world axes
    limit = eb.x + ppc::fmadds(a20, ea.z, ppc::fmadds(a00, ea.x, a10 * ea.y));
    if (dx > limit || -limit > dx) return 0;
    limit = eb.y + ppc::fmadds(a21, ea.z, ppc::fmadds(a01, ea.x, a11 * ea.y));
    if (dy > limit || -limit > dy) return 0;
    limit = eb.z + ppc::fmadds(a22, ea.z, ppc::fmadds(a02, ea.x, a12 * ea.y));
    if (dz > limit || -limit > dz) return 0;
    // the cross products
    float s;
    limit = ppc::fmadds(a20, ea.y, a10 * ea.z) + ppc::fmadds(a02, eb.y, a01 * eb.z);
    s = ppc::fmsubs(p2, m.up.x, p1 * m.at.x);
    if (s > limit || -limit > s) return 0;
    limit = ppc::fmadds(a21, ea.y, a11 * ea.z) + ppc::fmadds(a02, eb.x, a00 * eb.z);
    s = ppc::fmsubs(p2, m.up.y, p1 * m.at.y);
    if (s > limit || -limit > s) return 0;
    limit = ppc::fmadds(a22, ea.y, a12 * ea.z) + ppc::fmadds(a01, eb.x, a00 * eb.y);
    s = ppc::fmsubs(p2, m.up.z, p1 * m.at.z);
    if (s > limit || -limit > s) return 0;
    limit = ppc::fmadds(a20, ea.x, a00 * ea.z) + ppc::fmadds(a12, eb.y, a11 * eb.z);
    s = ppc::fmsubs(p0, m.at.x, p2 * m.right.x);
    if (s > limit || -limit > s) return 0;
    limit = ppc::fmadds(a21, ea.x, a01 * ea.z) + ppc::fmadds(a12, eb.x, a10 * eb.z);
    s = ppc::fmsubs(p0, m.at.y, p2 * m.right.y);
    if (s > limit || -limit > s) return 0;
    limit = ppc::fmadds(a22, ea.x, a02 * ea.z) + ppc::fmadds(a11, eb.x, a10 * eb.y);
    s = ppc::fmsubs(p0, m.at.z, p2 * m.right.z);
    if (s > limit || -limit > s) return 0;
    limit = ppc::fmadds(a10, ea.x, a00 * ea.y) + ppc::fmadds(a22, eb.y, a21 * eb.z);
    s = ppc::fmsubs(p1, m.right.x, p0 * m.up.x);
    if (s > limit || -limit > s) return 0;
    limit = ppc::fmadds(a11, ea.x, a01 * ea.y) + ppc::fmadds(a22, eb.x, a20 * eb.z);
    s = ppc::fmsubs(p1, m.right.y, p0 * m.up.y);
    if (s > limit || -limit > s) return 0;
    limit = ppc::fmadds(a12, ea.x, a02 * ea.y) + ppc::fmadds(a21, eb.x, a20 * eb.y);
    s = ppc::fmsubs(p1, m.right.z, p0 * m.up.z);
    if (s > limit || -limit > s) return 0;
    set->m_Infos &= 0xfffffff0u;
    return 1;
}

// 0x009aa710 CollisionTest_SweptAABoxVsAABoxSwapped_maybe: AABoxVsSweptAABox with the volumes exchanged, the normal negated when they touch.
uint8_t SweptAABoxVsAABoxSwapped(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set) {
    const uint8_t hit = AABoxVsSweptAABox(b, a, set);
    if (hit == 0) return 0;
    set->m_Normale12.x = -set->m_Normale12.x;
    set->m_Normale12.y = -set->m_Normale12.y;
    set->m_Normale12.z = -set->m_Normale12.z;
    return 1;
}

// 0x009aa790 CollisionTest_SphereVsCylinder_maybe: CylinderVsSphere with the volumes exchanged, the normal negated when they touch.
uint8_t SphereVsCylinder(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set) {
    const uint8_t hit = CylinderVsSphere(b, a, set);
    if (hit == 0) return 0;
    set->m_Normale12.x = -set->m_Normale12.x;
    set->m_Normale12.y = -set->m_Normale12.y;
    set->m_Normale12.z = -set->m_Normale12.z;
    return 1;
}

// 0x009aa810 CollisionTest_SweptSphereVsSphere_maybe: SphereVsSweptSphere with the volumes exchanged, the normal negated when they touch.
uint8_t SweptSphereVsSphere(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set) {
    const uint8_t hit = SphereVsSweptSphere(b, a, set);
    if (hit == 0) return 0;
    set->m_Normale12.x = -set->m_Normale12.x;
    set->m_Normale12.y = -set->m_Normale12.y;
    set->m_Normale12.z = -set->m_Normale12.z;
    return 1;
}

// 0x009aa890 CollisionTest_SweptSphereVsBox_maybe: BoxVsSweptSphere with the volumes exchanged, the normal negated when they touch.
uint8_t SweptSphereVsBox(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set) {
    const uint8_t hit = BoxVsSweptSphere(b, a, set);
    if (hit == 0) return 0;
    set->m_Normale12.x = -set->m_Normale12.x;
    set->m_Normale12.y = -set->m_Normale12.y;
    set->m_Normale12.z = -set->m_Normale12.z;
    return 1;
}

// 0x009aa910 CollisionTest_SphereVsBox_maybe: BoxVsSphere with the volumes exchanged, the normal negated when they touch.
uint8_t SphereVsBox(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set) {
    const uint8_t hit = BoxVsSphere(b, a, set);
    if (hit == 0) return 0;
    set->m_Normale12.x = -set->m_Normale12.x;
    set->m_Normale12.y = -set->m_Normale12.y;
    set->m_Normale12.z = -set->m_Normale12.z;
    return 1;
}

// 0x009aa990 CollisionTest_AABoxVsOBB_maybe: OBBVsAABox with the volumes exchanged, the normal negated when they touch.
uint8_t AABoxVsOBB(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set) {
    const uint8_t hit = OBBVsAABox(b, a, set);
    if (hit == 0) return 0;
    set->m_Normale12.x = -set->m_Normale12.x;
    set->m_Normale12.y = -set->m_Normale12.y;
    set->m_Normale12.z = -set->m_Normale12.z;
    return 1;
}

// 0x009aaa10 CollisionTest_SweptSphereVsAABox_maybe: AABoxVsSweptSphere with the volumes exchanged, the normal negated when they touch.
uint8_t SweptSphereVsAABox(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set) {
    const uint8_t hit = AABoxVsSweptSphere(b, a, set);
    if (hit == 0) return 0;
    set->m_Normale12.x = -set->m_Normale12.x;
    set->m_Normale12.y = -set->m_Normale12.y;
    set->m_Normale12.z = -set->m_Normale12.z;
    return 1;
}

// 0x009aaa90 CollisionTest_SphereVsAABox_maybe: AABoxVsSphere with the volumes exchanged, the normal negated when they touch.
uint8_t SphereVsAABox(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set) {
    const uint8_t hit = AABoxVsSphere(b, a, set);
    if (hit == 0) return 0;
    set->m_Normale12.x = -set->m_Normale12.x;
    set->m_Normale12.y = -set->m_Normale12.y;
    set->m_Normale12.z = -set->m_Normale12.z;
    return 1;
}


}  // namespace collision_test
