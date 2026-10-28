// CollisionTest.cpp - reconstructed original translation unit: 0x19d020-0x19f3e8 (GAME_TOC1, main_toc1), 8 functions, 8 live.
// Primary owner: CollisionTest (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x19d020  CollisionTest_AABoxVsAABox_maybe
//   [ ] 0x19d268  CollisionTest_SweptAABoxVsSweptAABox_maybe
//   [ ] 0x19d938  CollisionTest_AABoxVsSweptAABox_maybe
//   [x] 0x19dff0  CollisionTest_AABoxVsSphere_maybe
//   [x] 0x19e450  CollisionTest_AABoxVsSweptSphere_maybe
//   [ ] 0x19e950  CollisionTest_CylinderVsCylinder_maybe
//   [x] 0x19eaa0  CollisionTest_CylinderVsSphere_maybe
//   [ ] 0x19ee08  CollisionTest_OBBVsAABox_maybe
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

// 0x0019d020 CollisionTest_AABoxVsAABox_maybe. STUB(C2.9): two axis-aligned boxes.
uint8_t AABoxVsAABox(IKBoundingVolume*, IKBoundingVolume*, CContactSet*) {
    DOTD_STUB_ONCE("CollisionTest_AABoxVsAABox_maybe 0x19d020 (C2.9: no volume pair of LVL010 has these shapes)");
    return 0;
}

// 0x0019d268 CollisionTest_SweptAABoxVsSweptAABox_maybe. STUB(C2.9): two moving axis-aligned boxes.
uint8_t SweptAABoxVsSweptAABox(IKBoundingVolume*, IKBoundingVolume*, CContactSet*) {
    DOTD_STUB_ONCE("CollisionTest_SweptAABoxVsSweptAABox_maybe 0x19d268 (C2.9: no volume pair of LVL010 has these shapes)");
    return 0;
}

// 0x0019d938 CollisionTest_AABoxVsSweptAABox_maybe. STUB(C2.9): a moving axis-aligned box.
uint8_t AABoxVsSweptAABox(IKBoundingVolume*, IKBoundingVolume*, CContactSet*) {
    DOTD_STUB_ONCE("CollisionTest_AABoxVsSweptAABox_maybe 0x19d938 (C2.9: no volume pair of LVL010 has these shapes)");
    return 0;
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

// 0x0019e950 CollisionTest_CylinderVsCylinder_maybe. STUB(C2.9): two cylinders.
uint8_t CylinderVsCylinder(IKBoundingVolume*, IKBoundingVolume*, CContactSet*) {
    DOTD_STUB_ONCE("CollisionTest_CylinderVsCylinder_maybe 0x19e950 (C2.9: no volume pair of LVL010 has these shapes)");
    return 0;
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

// 0x0019ee08 CollisionTest_OBBVsAABox_maybe. STUB(C2.9): an oriented and an axis-aligned box.
uint8_t OBBVsAABox(IKBoundingVolume*, IKBoundingVolume*, CContactSet*) {
    DOTD_STUB_ONCE("CollisionTest_OBBVsAABox_maybe 0x19ee08 (C2.9: no volume pair of LVL010 has these shapes)");
    return 0;
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
