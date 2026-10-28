// Collision.cpp - reconstructed original translation unit: 0x19f3e8-0x19fcf8 (GAME_TOC1, main_toc1), 1 functions, 1 live.
// Primary owner: Collision (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x19f3e8  Collision_TestOBBvsOBB_maybe
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

namespace {
// The separating-axis tests of OBBVsOBB: a projection within +-1e-14 (a double) never separates; else it must lie in
// [-r, r] (a NaN passes, as the original's bgt tests).
bool Small(float x) { return !(static_cast<double>(x) > 1e-14) && !(static_cast<double>(x) < -1e-14); }
bool Separated(float x, float r) { return !Small(x) && (x > r || -r > x); }
}  // namespace

// 0x0019f3e8 Collision_TestOBBvsOBB_maybe: two oriented boxes (their frames' LTM rows, the extents +0x2c): the centres
// within the sum of the radii on each world axis (x, z, y), then the fifteen separating axes (the three of each box and
// the nine cross products). No separation: 1, the response bits cleared (no normal or point).
uint8_t OBBVsOBB(IKBoundingVolume* a, IKBoundingVolume* b, CContactSet* set) {
    const CVector3* pa = Position(a);
    const CVector3* pb = Position(b);
    const float radii = a->m_fRadius + b->m_fRadius;
    if (!(radii >= std::fabs(pa->x - pb->x))) return 0;
    if (!(radii >= std::fabs(pa->z - pb->z))) return 0;
    if (!(radii >= std::fabs(pa->y - pb->y))) return 0;
    const RwMatrix& ma = Ltm(a);
    const RwMatrix& mb = Ltm(b);
    const CVector3& ea = static_cast<const IKBoundingBox*>(a)->m_Extent;
    const CVector3& eb = static_cast<const IKBoundingBox*>(b)->m_Extent;
    const float ty = mb.pos.y - ma.pos.y;
    const float tx = mb.pos.x - ma.pos.x;
    const float tz = mb.pos.z - ma.pos.z;
    // The rows' dot products R_ij = A_i . B_j (y first, then x, then z fused) and T . A_i.
    auto dot = [](const RwV3d& u, const RwV3d& w) { return ppc::fmadds(u.z, w.z, ppc::fmadds(u.x, w.x, u.y * w.y)); };
    auto along = [&](const RwV3d& u) { return ppc::fmadds(tz, u.z, ppc::fmadds(tx, u.x, ty * u.y)); };
    // a's right
    const float r00 = dot(ma.right, mb.right), r01 = dot(ma.right, mb.up), r02 = dot(ma.right, mb.at);
    const float t0 = along(ma.right);
    const float a00 = std::fabs(r00), a01 = std::fabs(r01), a02 = std::fabs(r02);
    if (Separated(t0, ppc::fmadds(a02, eb.z, ppc::fmadds(a00, eb.x, a01 * eb.y)) + ea.x)) return 0;
    // a's up
    const float r10 = dot(ma.up, mb.right), r11 = dot(ma.up, mb.up), r12 = dot(ma.up, mb.at);
    const float t1 = along(ma.up);
    const float a10 = std::fabs(r10), a11 = std::fabs(r11), a12 = std::fabs(r12);
    if (Separated(t1, ppc::fmadds(a12, eb.z, ppc::fmadds(a10, eb.x, a11 * eb.y)) + ea.y)) return 0;
    // a's at
    const float r20 = dot(ma.at, mb.right), r21 = dot(ma.at, mb.up), r22 = dot(ma.at, mb.at);
    const float t2 = along(ma.at);
    const float a20 = std::fabs(r20), a21 = std::fabs(r21), a22 = std::fabs(r22);
    if (Separated(t2, ppc::fmadds(a22, eb.z, ppc::fmadds(a20, eb.x, a21 * eb.y)) + ea.z)) return 0;
    // b's right, up, at
    const float s0 = along(mb.right);
    if (Separated(s0, eb.x + ppc::fmadds(a20, ea.z, ppc::fmadds(a00, ea.x, a10 * ea.y)))) return 0;
    const float s1 = along(mb.up);
    if (Separated(s1, eb.y + ppc::fmadds(a21, ea.z, ppc::fmadds(a01, ea.x, a11 * ea.y)))) return 0;
    const float s2 = along(mb.at);
    if (Separated(s2, eb.z + ppc::fmadds(a22, ea.z, ppc::fmadds(a02, ea.x, a12 * ea.y)))) return 0;
    // The cross products: A_i x B_j.
    auto cross = [](float r1, float u, float r2, float w) { return ppc::fmsubs(r1, u, r2 * w); };
    auto reach = [](float p1, float q1, float p2, float q2, float p3, float q3, float p4, float q4) {
        return ppc::fmadds(p2, q2, p1 * q1) + ppc::fmadds(p4, q4, p3 * q3);
    };
    if (Separated(cross(r10, t2, t1, r20), reach(a10, ea.z, a20, ea.y, a01, eb.z, a02, eb.y))) return 0;
    if (Separated(cross(r11, t2, t1, r21), reach(a11, ea.z, a21, ea.y, a00, eb.z, a02, eb.x))) return 0;
    if (Separated(cross(r12, t2, t1, r22), reach(a12, ea.z, a22, ea.y, a00, eb.y, a01, eb.x))) return 0;
    if (Separated(cross(t0, r20, r00, t2), reach(a00, ea.z, a20, ea.x, a11, eb.z, a12, eb.y))) return 0;
    if (Separated(cross(t0, r21, r01, t2), reach(a01, ea.z, a21, ea.x, a10, eb.z, a12, eb.x))) return 0;
    if (Separated(cross(t0, r22, r02, t2), reach(a02, ea.z, a22, ea.x, a10, eb.y, a11, eb.x))) return 0;
    if (Separated(cross(r00, t1, t0, r10), reach(a00, ea.y, a10, ea.x, a21, eb.z, a22, eb.y))) return 0;
    if (Separated(cross(r01, t1, t0, r11), reach(a01, ea.y, a11, ea.x, a20, eb.z, a22, eb.x))) return 0;
    if (Separated(cross(r02, t1, t0, r12), reach(a02, ea.y, a12, ea.x, a20, eb.y, a21, eb.x))) return 0;
    set->m_Infos = set->m_Infos & 0xfffffff0u;
    return 1;
}

}  // namespace collision_test
