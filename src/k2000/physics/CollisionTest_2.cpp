// CollisionTest_2.cpp - reconstructed original translation unit: 0x19fcf8-0x1a14e8 (GAME_TOC1, main_toc1), 5 functions, 5 live.
// Primary owner: CollisionTest (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x19fcf8  CollisionTest_BoxVsSphere_maybe
//   [x] 0x1a0238  CollisionTest_BoxVsSweptSphere_maybe
//   [x] 0x1a0868  CollisionTest_SphereVsSweptSphere_maybe
//   [x] 0x1a0d40  CollisionTest_SphereVsSphere
//   [x] 0x1a0f90  CollisionTest_SweptSphereVsSweptSphere_maybe  (port-final F05)
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
// The box's local vector (lx, ly, lz) in the world (the rows right / up / at), scaled by `inverse`.
void BoxNormal(const RwMatrix& m, float lx, float ly, float lz, float inverse, CVector3* out) {
    const float ux = ly * m.up.x, uy = ly * m.up.y, uz = ly * m.up.z;
    const float x = ppc::fmadds(lz, m.at.x, ppc::fmadds(lx, m.right.x, ux));
    const float y = ppc::fmadds(lz, m.at.y, ppc::fmadds(lx, m.right.y, uy));
    const float z = ppc::fmadds(lz, m.at.z, ppc::fmadds(lx, m.right.z, uz));
    out->x = inverse * x;
    out->y = inverse * y;
    out->z = inverse * z;
}
}  // namespace

// 0x0019fcf8 CollisionTest_BoxVsSphere_maybe: an oriented box (its frame's LTM: rows right / up / at, the extent +0x2c)
// against a sphere. The centres within the sum of the radii on each axis first (x, z, y), then the sphere's centre in
// the box's axes and the squared distance outside the box, per axis (x, y, z), against the sphere's radius squared.
// Outside the box: response 0xe, the interpenetration (radius - distance), the normal from the box to the centre and
// the contact point on the sphere pushed back by half the interpenetration. Inside: the nearest face (strictly nearer
// than the earlier axes): response 6, the depth + radius, its normal (no contact point); at the centre exactly:
// response 2 and the radius.
uint8_t BoxVsSphere(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set) {
    const RwMatrix& ltm = Ltm(a);
    const CVector3* pa = Position(a);
    const CVector3* pb = Position(b);
    const float radii = a->m_fRadius + b->m_fRadius;
    if (!(radii >= std::fabs(pa->x - pb->x))) return 0;
    if (!(radii >= std::fabs(pa->z - pb->z))) return 0;
    if (!(radii >= std::fabs(pa->y - pb->y))) return 0;
    const IKBoundingBox* box = static_cast<const IKBoundingBox*>(a);
    const float dy = pb->y - pa->y;
    const float dz = pb->z - pa->z;
    const float dx = pb->x - pa->x;
    float lx = 0.0f, ly = 0.0f, lz = 0.0f;  // the outside part per axis (stack -0x1c / -0x18 / -0x14)
    const float r2 = b->m_fRadius * b->m_fRadius;
    const float ex = box->m_Extent.x, ey = box->m_Extent.y, ez = box->m_Extent.z;
    const float p0 = ppc::fmadds(dz, ltm.right.z, ppc::fmadds(dx, ltm.right.x, dy * ltm.right.y));
    const float p1 = ppc::fmadds(dz, ltm.up.z, ppc::fmadds(dx, ltm.up.x, dy * ltm.up.y));
    const float p2 = ppc::fmadds(dz, ltm.at.z, ppc::fmadds(dx, ltm.at.x, dy * ltm.at.y));
    float sum = 0.0f;
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
        BoxNormal(ltm, lx, ly, lz, inverse, &set->m_Normale12);
        const float along = ppc::fnmadds(set->m_fdInterpenetration, -0.5f, b->m_fRadius);
        const float cx = pb->x, cy = pb->y, cz = pb->z;
        set->m_WorldContactPoint.x = cx;
        set->m_WorldContactPoint.y = cy;
        set->m_WorldContactPoint.z = cz;
        set->m_WorldContactPoint.x = ppc::fmadds(along, set->m_Normale12.x, cx);
        set->m_WorldContactPoint.z = ppc::fmadds(along, set->m_Normale12.z, cz);
        set->m_WorldContactPoint.y = ppc::fmadds(along, set->m_Normale12.y, cy);
        return 1;
    }
    // The centre is inside: the nearest face.
    float best = 3.4028235e+38f;  // 0x00c4acb8 +0x28 (FLT_MAX)
    {
        const float c = p0 < 0.0f ? -(p0 + ex) : -(p0 - ex);
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
    BoxNormal(ltm, lx, ly, lz, inverse, &set->m_Normale12);
    return 1;
}

// 0x001a0238 CollisionTest_BoxVsSweptSphere_maybe: an oriented box against a moving sphere (its start and move as in
// SphereVsSweptSphere). The world-axis reach first (x, z, y: the box's centre minus the start against the move and the
// sum of the radii), then the slabs of the box's axes (right, up, at; each widened by the sphere's radius): the entry
// time is the latest slab entry (its axis, against the move, the normal), the exit the earliest exit. Entered after
// 1.0000010: none; before -1e-6 (touching at the start): BoxVsSphere's answer. Else response 0xd, the time, the normal
// and the contact point: the sphere's centre then, moved back by its radius along the normal and pulled into the box's
// extent along each world axis.
uint8_t BoxVsSweptSphere(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set) {
    constexpr float kMax = 3.4028235e+38f;          // 0x00c4acb8 +0x28 (FLT_MAX)
    constexpr float kLatest = 0x1.00001p+0f;        // 1.0000010 (0x3f800008)
    constexpr float kEarliest = -0x1.0c6f7ap-20f;   // -1e-6 (0xb58637bd)
    const CKDynamicBoundingSphere* moving = static_cast<const CKDynamicBoundingSphere*>(b);
    const CVector3* start = ((b->m_ba8Infos >> 4) & 1) != 0 ? &moving->m_v3OldPos : Position(b);
    const IKBoundingBox* box = static_cast<const IKBoundingBox*>(a);
    const RwMatrix& ltm = Ltm(a);
    float tmin = -kMax;
    float tmax;
    const float r = b->m_fRadius;
    const float radii = r + a->m_fRadius;
    const float vx = moving->m_v3WorldMove.x, vz = moving->m_v3WorldMove.z, vy = moving->m_v3WorldMove.y;
    const float dx = ltm.pos.x - start->x;
    if (!(vx > 0.0f)) {
        if (radii < dx) return 0;
        if (!(vx - radii <= dx)) return 0;
    } else {
        if (vx + radii < dx) return 0;
        if (-radii > dx) return 0;
    }
    const float dz = ltm.pos.z - start->z;
    if (!(vz > 0.0f)) {
        if (radii < dz) return 0;
        if (!(vz - radii <= dz)) return 0;
    } else {
        if (vz + radii < dz) return 0;
        if (-radii > dz) return 0;
    }
    const float dy = ltm.pos.y - start->y;
    if (!(vy > 0.0f)) {
        if (radii < dy) return 0;
        if (!(vy - radii <= dy)) return 0;
    } else {
        if (vy + radii < dy) return 0;
        if (-radii > dy) return 0;
    }
    float nx = 0.0f, ny = 0.0f, nz = 0.0f;  // f29 / f28 / f27 (set with the entry time)
    // The slab of `axis` with half width r + extent: the parallel move must start inside, else the entry / exit times.
    struct Slab {
        bool parallel;
        float lo, hi, sign, inside;
    };
    auto slab = [&](const RwV3d& axis, float extent) {
        Slab s;
        const float va = ppc::fmadds(vz, axis.z, ppc::fmadds(vx, axis.x, vy * axis.y));
        const float width = r + extent;
        s.parallel = va == 0.0f;
        if (s.parallel) {
            s.inside = ppc::fnmadds(dz, axis.z, ppc::fmadds(dx, axis.x, dy * axis.y));
            s.lo = s.hi = s.sign = 0.0f;
        } else {
            const float inverse = 1.0f / va;
            const float da = ppc::fmadds(dz, axis.z, ppc::fmadds(dx, axis.x, dy * axis.y));
            s.hi = inverse * (width + da);
            s.lo = inverse * (da - width);
            s.sign = -1.0f;
            if (s.lo > s.hi) {
                const float swap = s.lo;
                s.lo = s.hi;
                s.hi = swap;
                s.sign = 1.0f;
            }
            s.inside = 0.0f;
        }
        return s;
    };
    {  // right
        const float width = r + box->m_Extent.x;
        const Slab s = slab(ltm.right, box->m_Extent.x);
        if (s.parallel) {
            if (-width > s.inside) return 0;
            tmax = kMax;
            if (width < s.inside) return 0;
        } else {
            if (tmin < s.lo) {
                tmin = s.lo;
                nz = s.sign * ltm.right.z;
                nx = s.sign * ltm.right.x;
                ny = s.sign * ltm.right.y;
            }
            tmax = kMax > s.hi ? s.hi : kMax;
            if (tmin > tmax) return 0;
            if (!(tmax >= 0.0f)) return 0;
        }
    }
    {  // up
        const float width = r + box->m_Extent.y;
        const Slab s = slab(ltm.up, box->m_Extent.y);
        if (s.parallel) {
            if (-width > s.inside) return 0;
            if (width < s.inside) return 0;
        } else {
            if (tmin < s.lo) {
                tmin = s.lo;
                nz = s.sign * ltm.up.z;
                nx = s.sign * ltm.up.x;
                ny = s.sign * ltm.up.y;
            }
            if (tmax > s.hi) tmax = s.hi;
            if (tmin > tmax) return 0;
            if (tmax < 0.0f) return 0;
        }
    }
    {  // at
        const float width = r + box->m_Extent.z;
        const Slab s = slab(ltm.at, box->m_Extent.z);
        if (s.parallel) {
            if (-width > s.inside) return 0;
            if (!(width >= s.inside)) return 0;
        } else {
            if (s.lo > tmin) {
                tmin = s.lo;
                nz = s.sign * ltm.at.z;
                nx = s.sign * ltm.at.x;
                ny = s.sign * ltm.at.y;
            }
            const float exit = s.hi < tmax ? s.hi : tmax;
            if (tmin > exit) return 0;
            if (exit < 0.0f) return 0;
        }
    }
    if (tmin > kLatest) return 0;
    if (tmin < kEarliest) return BoxVsSphere(a, b, set);  // touching at the start
    set->m_Infos = (set->m_Infos & 0xfffffff0u) | 0xdu;
    set->m_fUDeltaTime = tmin;
    set->m_Normale12.x = nx;
    set->m_Normale12.z = nz;
    set->m_Normale12.y = ny;
    const float back = -r;
    float px = ppc::fmadds(back, nx, ppc::fmadds(tmin, vx, start->x));
    float pz = ppc::fmadds(back, nz, ppc::fmadds(tmin, vz, start->z));
    float py = ppc::fmadds(back, ny, ppc::fmadds(tmin, vy, start->y));
    const float ox = ltm.pos.x - px;
    const float oz = ltm.pos.z - pz;
    const float oy = ltm.pos.y - py;
    if (std::fabs(ox) > box->m_Extent.x) {
        const float sign = ox < 0.0f ? -1.0f : 1.0f;
        px = ppc::fmadds(sign, (ox < 0.0f ? -ox : ox) - box->m_Extent.x, px);
    }
    if (std::fabs(oy) > box->m_Extent.y) {
        const float sign = oy < 0.0f ? -1.0f : 1.0f;
        py = ppc::fmadds((oy < 0.0f ? -oy : oy) - box->m_Extent.y, sign, py);
    }
    if (std::fabs(oz) > box->m_Extent.z) {
        const float sign = oz < 0.0f ? -1.0f : 1.0f;
        pz = ppc::fmadds((oz < 0.0f ? -oz : oz) - box->m_Extent.z, sign, pz);
    }
    set->m_WorldContactPoint.x = px;
    set->m_WorldContactPoint.z = pz;
    set->m_WorldContactPoint.y = py;
    return 1;
}

// 0x001a0868 CollisionTest_SphereVsSweptSphere_maybe: a sphere against a moving sphere (CKDynamicBoundingSphere: from
// its old position +0x38 while it follows its frame (infos bit 4), else its frame's, along its move +0x2c). Per axis
// (x, z, y) the swept range against the sum of the radii; already touching at the start: SphereVsSphere's answer
// (response 0xe, or 0xa at the same point); else the first time t in [-1e-6, 1.0000010] the distance is the sum
// (the quadratic's smaller root, the larger one when the smaller is before the start): response 0xd, the time, the
// normal at that time and the contact point on the first sphere's surface.
uint8_t SphereVsSweptSphere(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set) {
    const CKDynamicBoundingSphere* moving = static_cast<const CKDynamicBoundingSphere*>(b);
    const CVector3* start = ((b->m_ba8Infos >> 4) & 1) != 0 ? &moving->m_v3OldPos : Position(b);
    const CVector3* pa = Position(a);
    const float vx = moving->m_v3WorldMove.x;
    const float vz = moving->m_v3WorldMove.z;
    const float vy = moving->m_v3WorldMove.y;
    const float radii = b->m_fRadius + a->m_fRadius;
    const float dx = start->x - pa->x;
    const float minus = -radii;
    if (vx < 0.0f) {
        if (radii - vx < dx) return 0;
        if (!(minus <= dx)) return 0;
    } else {
        if (radii < dx) return 0;
        if (minus - vx > dx) return 0;
    }
    const float dz = start->z - pa->z;
    if (vz < 0.0f) {
        if (radii - vz < dz) return 0;
        if (!(minus <= dz)) return 0;
    } else {
        if (radii < dz) return 0;
        if (minus - vz > dz) return 0;
    }
    const float dy = start->y - pa->y;
    if (vy < 0.0f) {
        if (radii - vy < dy) return 0;
        if (!(minus <= dy)) return 0;
    } else {
        if (radii < dy) return 0;
        if (minus - vy > dy) return 0;
    }
    float distance2 = ppc::fmadds(dx, dx, dy * dy);
    distance2 = ppc::fmadds(dz, dz, distance2);
    const float c = distance2 - radii * radii;
    if (c <= 0.0f) {
        // Already touching at the start.
        const float distance = std::sqrt(distance2);  // fsqrts
        if (!(distance > 0.0f)) {
            set->m_Infos = (set->m_Infos & 0xfffffff0u) | 0xau;
            set->m_WorldContactPoint.x = pa->x;
            set->m_WorldContactPoint.z = pa->z;
            set->m_WorldContactPoint.y = pa->y;
            set->m_fdInterpenetration = radii;
            return 1;
        }
        const float inverse = 1.0f / distance;
        const float penetration = radii - distance;
        set->m_Infos = (set->m_Infos & 0xfffffff0u) | 0xeu;
        const float nx = start->x - pa->x;
        const float ny = start->y - pa->y;
        const float nz = start->z - pa->z;
        set->m_Normale12.x = nx;
        set->m_Normale12.x = inverse * nx;
        set->m_Normale12.y = inverse * ny;
        set->m_Normale12.z = inverse * nz;
        set->m_fdInterpenetration = penetration;
        const float along = ppc::fmadds(penetration, -0.5f, a->m_fRadius);
        const float cx = pa->x, cz = pa->z, cy = pa->y;
        set->m_WorldContactPoint.x = cx;
        set->m_WorldContactPoint.y = cy;
        set->m_WorldContactPoint.z = cz;
        set->m_WorldContactPoint.z = ppc::fmadds(along, set->m_Normale12.z, cz);
        set->m_WorldContactPoint.x = ppc::fmadds(along, set->m_Normale12.x, cx);
        set->m_WorldContactPoint.y = ppc::fmadds(along, set->m_Normale12.y, cy);
        return 1;
    }
    float speed2 = ppc::fmadds(vx, vx, vy * vy);
    speed2 = ppc::fmadds(vz, vz, speed2);
    float half = ppc::fmadds(vx, dx, vy * dy);
    half = ppc::fmadds(vz, dz, half);
    const float twice = half + half;
    constexpr float kEarliest = -0x1.0c6f7ap-20f;  // -1e-6 (0xb58637bd)
    constexpr float kLatest = 0x1.00001p+0f;       // 1.0000010 (0x3f800008)
    float t;
    bool valid;
    bool first = false;
    float t1 = 0.0f;
    if (speed2 != 0.0f) {
        const float discriminant = ppc::fmadds(twice, twice, c * (speed2 * -4.0f));
        if (discriminant < 0.0f) return 0;
        const float root = std::sqrt(discriminant);  // Math_Sqrtf 0x10690
        const float scale = 0.5f / speed2;
        t1 = scale * (-twice - root);
        const float t2 = scale * (root - twice);
        t = t2;
        if (!(t2 <= t1) && t1 >= kEarliest) {
            first = true;
            valid = true;
        } else {
            valid = t2 >= kEarliest;
        }
    } else if (twice != 0.0f) {
        t = -c / twice;
        valid = t >= kEarliest;
    } else {
        if (c != 0.0f) return 0;
        t = 0.0f;
        valid = true;
    }
    if (first) t = t1;
    if (!valid) return 0;
    if (!(t <= kLatest)) return 0;
    const float hz = ppc::fmadds(vz, t, dz);
    const float hx = ppc::fmadds(vx, t, dx);
    set->m_Infos = (set->m_Infos & 0xfffffff0u) | 0xdu;
    const float hy = ppc::fmadds(vy, t, dy);
    const float inverse = 1.0f / radii;
    set->m_fUDeltaTime = t;
    set->m_Normale12.x = hx;
    set->m_Normale12.z = inverse * hz;
    set->m_Normale12.x = inverse * hx;
    set->m_Normale12.y = inverse * hy;
    const float cx = pa->x, cz = pa->z, cy = pa->y;
    set->m_WorldContactPoint.x = cx;
    set->m_WorldContactPoint.y = cy;
    set->m_WorldContactPoint.z = cz;
    const float r = a->m_fRadius;
    set->m_WorldContactPoint.z = ppc::fmadds(r, set->m_Normale12.z, cz);
    set->m_WorldContactPoint.x = ppc::fmadds(r, set->m_Normale12.x, cx);
    set->m_WorldContactPoint.y = ppc::fmadds(r, set->m_Normale12.y, cy);
    return 1;
}

// 0x001a0d40 CollisionTest_SphereVsSphere: the centres (the frames' LTM positions) within the sum of the radii, and
// not exactly that far apart. Centres within 0 of each other (the same point): response 0xa, the interpenetration
// the sum of the radii, the contact point the first centre (the normal is left). Else response 0xe, the normal the
// unit vector from the first centre to the second, the interpenetration (sum - distance) and the contact point on
// the first sphere's surface pushed back by half the interpenetration: centre1 + normal * fmadds(pen, -0.5, r1).
uint8_t SphereVsSphere(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set) {
    const float radii = a->m_fRadius + b->m_fRadius;
    const CVector3* pa = Position(a);
    const CVector3* pb = Position(b);
    if (Vec3_IsWithinDistance(radii, pa, pb) == 0) return 0;
    const float dy = pa->y - pb->y;
    const float dx = pa->x - pb->x;
    const float dz = pa->z - pb->z;
    const float distance = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));  // Math_Sqrtf 0x10690
    if (radii == distance) return 0;
    if (!(distance > 0.0f)) {  // ble: NaN too
        set->m_Infos = (set->m_Infos & 0xfffffff0u) | 0xau;
        set->m_WorldContactPoint.x = pa->x;
        set->m_WorldContactPoint.z = pa->z;
        set->m_WorldContactPoint.y = pa->y;
        set->m_fdInterpenetration = radii;
        return 1;
    }
    const float penetration = radii - distance;
    const float inverse = 1.0f / distance;
    set->m_Infos = (set->m_Infos & 0xfffffff0u) | 0xeu;
    const float nx = pb->x - pa->x;
    const float ny = pb->y - pa->y;
    const float nz = pb->z - pa->z;
    set->m_Normale12.x = nx;
    set->m_Normale12.x = inverse * nx;
    set->m_Normale12.y = inverse * ny;
    set->m_Normale12.z = inverse * nz;
    set->m_fdInterpenetration = penetration;
    const float along = ppc::fmadds(penetration, -0.5f, a->m_fRadius);
    const float cx = pa->x, cz = pa->z, cy = pa->y;
    set->m_WorldContactPoint.x = cx;
    set->m_WorldContactPoint.y = cy;
    set->m_WorldContactPoint.z = cz;
    set->m_WorldContactPoint.z = ppc::fmadds(along, set->m_Normale12.z, cz);
    set->m_WorldContactPoint.x = ppc::fmadds(along, set->m_Normale12.x, cx);
    set->m_WorldContactPoint.y = ppc::fmadds(along, set->m_Normale12.y, cy);
    return 1;
}

/// 0x001a0f90 CollisionTest_SweptSphereVsSweptSphere_maybe (C2.8 port-final F05): two moving spheres
// (CKDynamicBoundingSphere: each from its old position +0x38 while it follows its frame (infos bit 4), else its frame's).
// Relative to the first: the move v = move2 - move1 (+0x2c) and the start offset d = start2 - start1. Per axis (x, z, y)
// the swept range against the sum of the radii (r2 + r1; blt / bgt / ble: an unordered compare goes on). Already
// touching at the start (|d|^2 - radii^2 <= 0, fused y, x, z): response 0xa at the first start when the distance (fsqrts)
// is not above 0, else 0xe with the unit normal from the first start to the second, the interpenetration and the contact
// point on the first sphere's surface pushed back by half of it. Else the first time t in [-1e-6, 1.0000010] the
// distance is the sum (the quadratic's smaller root unless the larger is not above it or the smaller is before the
// start): response 0xd, the time, the normal (d + v t) / radii and the contact point on the first sphere at that time
// (start1 + move1 t + r1 n).
uint8_t SweptSphereVsSweptSphere(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set) {
    const CKDynamicBoundingSphere* sa = static_cast<const CKDynamicBoundingSphere*>(a);
    const CKDynamicBoundingSphere* sb = static_cast<const CKDynamicBoundingSphere*>(b);
    const CVector3* pa = ((a->m_ba8Infos >> 4) & 1) != 0 ? &sa->m_v3OldPos : Position(a);
    const CVector3* pb = ((b->m_ba8Infos >> 4) & 1) != 0 ? &sb->m_v3OldPos : Position(b);
    const float vx = sb->m_v3WorldMove.x - sa->m_v3WorldMove.x;
    const float dx = pb->x - pa->x;
    const float radii = b->m_fRadius + a->m_fRadius;
    const float minus = -radii;
    if (vx < 0.0f) {
        if (radii - vx < dx) return 0;
        if (minus > dx) return 0;
    } else {
        if (radii < dx) return 0;
        if (minus - vx > dx) return 0;
    }
    const float vz = sb->m_v3WorldMove.z - sa->m_v3WorldMove.z;
    const float dz = pb->z - pa->z;
    if (vz < 0.0f) {
        if (radii - vz < dz) return 0;
        if (minus > dz) return 0;
    } else {
        if (radii < dz) return 0;
        if (minus - vz > dz) return 0;
    }
    const float vy = sb->m_v3WorldMove.y - sa->m_v3WorldMove.y;
    const float dy = pb->y - pa->y;
    if (vy < 0.0f) {
        if (radii - vy < dy) return 0;
        if (minus > dy) return 0;
    } else {
        if (radii < dy) return 0;
        if (minus - vy > dy) return 0;
    }
    const float distance2 = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
    const float c = distance2 - radii * radii;
    if (c <= 0.0f) {
        const float distance = std::sqrt(distance2);  // fsqrts
        if (!(distance > 0.0f)) {
            set->m_Infos = (set->m_Infos & 0xfffffff0u) | 0xau;
            set->m_WorldContactPoint.x = pa->x;
            set->m_WorldContactPoint.z = pa->z;
            set->m_WorldContactPoint.y = pa->y;
            set->m_fdInterpenetration = radii;
            return 1;
        }
        const float inverse = 1.0f / distance;
        set->m_Infos = (set->m_Infos & 0xfffffff0u) | 0xeu;
        const float ax = pa->x, ay = pa->y, az = pa->z;
        const float ny = pb->y - ay;
        const float nx = pb->x - ax;
        const float nz = pb->z - az;
        const float penetration = radii - distance;
        set->m_Normale12.x = nx;
        set->m_Normale12.x = inverse * nx;
        set->m_Normale12.z = inverse * nz;
        set->m_Normale12.y = inverse * ny;
        set->m_fdInterpenetration = penetration;
        const float along = ppc::fmadds(penetration, -0.5f, a->m_fRadius);
        const float cx = pa->x, cy = pa->y, cz = pa->z;
        set->m_WorldContactPoint.x = cx;
        set->m_WorldContactPoint.y = cy;
        set->m_WorldContactPoint.z = cz;
        set->m_WorldContactPoint.z = ppc::fmadds(along, set->m_Normale12.z, cz);
        set->m_WorldContactPoint.x = ppc::fmadds(along, set->m_Normale12.x, cx);
        set->m_WorldContactPoint.y = ppc::fmadds(along, set->m_Normale12.y, cy);
        return 1;
    }
    const float speed2 = ppc::fmadds(vz, vz, ppc::fmadds(vx, vx, vy * vy));
    const float half = ppc::fmadds(dz, vz, ppc::fmadds(dx, vx, dy * vy));
    const float twice = half + half;
    constexpr float kEarliest = -0x1.0c6f7ap-20f;  // TOC1 -0x27d8 -1e-6 (0xb58637bd)
    constexpr float kLatest = 0x1.00001p+0f;       // TOC1 -0x27cc 1.0000010 (0x3f800008)
    float t;
    bool valid;
    if (speed2 != 0.0f) {
        const float discriminant = ppc::fmadds(twice, twice, c * (speed2 * -4.0f));  // TOC1 -0x27d4
        if (discriminant < 0.0f) return 0;
        const float root = std::sqrt(discriminant);  // Math_Sqrtf 0x10690
        const float scale = 0.5f / speed2;           // TOC1 -0x27d0
        const float t1 = scale * (-twice - root);
        const float t2 = scale * (root - twice);
        if (!(t2 <= t1) && t1 >= kEarliest) {
            t = t1;
            valid = true;
        } else {
            t = t2;
            valid = t2 >= kEarliest;
        }
    } else if (twice != 0.0f) {
        t = -c / twice;
        valid = t >= kEarliest;
    } else {
        return 0;  // c > 0 here (bne cr6)
    }
    if (!valid) return 0;
    if (!(t <= kLatest)) return 0;
    const float hx = ppc::fmadds(vx, t, dx);
    const float hy = ppc::fmadds(vy, t, dy);
    const float hz = ppc::fmadds(vz, t, dz);
    set->m_Infos = (set->m_Infos & 0xfffffff0u) | 0xdu;
    const float inverse = 1.0f / radii;  // TOC1 -0x27e0
    set->m_fUDeltaTime = t;
    set->m_Normale12.x = hx;
    set->m_Normale12.x = inverse * hx;
    set->m_Normale12.z = inverse * hz;
    set->m_Normale12.y = inverse * hy;
    const float ax = pa->x, az = pa->z, ay = pa->y;
    set->m_WorldContactPoint.x = ax;
    set->m_WorldContactPoint.y = ay;
    set->m_WorldContactPoint.z = az;
    const float mx = ppc::fmadds(t, sa->m_v3WorldMove.x, ax);
    const float mz = ppc::fmadds(t, sa->m_v3WorldMove.z, az);
    const float my = ppc::fmadds(t, sa->m_v3WorldMove.y, ay);
    set->m_WorldContactPoint.z = mz;
    set->m_WorldContactPoint.x = mx;
    set->m_WorldContactPoint.y = my;
    const float r = a->m_fRadius;
    set->m_WorldContactPoint.z = ppc::fmadds(r, set->m_Normale12.z, mz);
    set->m_WorldContactPoint.x = ppc::fmadds(r, set->m_Normale12.x, mx);
    set->m_WorldContactPoint.y = ppc::fmadds(r, set->m_Normale12.y, my);
    return 1;
}

}  // namespace collision_test
