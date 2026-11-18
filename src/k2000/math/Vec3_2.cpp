// Vec3_2.cpp - reconstructed original translation unit 0x263df8-0x264590 (GAME_TOC1, main_toc1), 4 functions, 1 live.
// Primary owner: Vec3 (not a registered class)
// Other owners: Mat4 (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x263df8  FUN_00263df8  [dead]
//   [ ] 0x263e80  Mat4_SetBasisFromAtAndWorldUp_maybe  [dead]
//   [x] 0x264140  Vec3_RotateTowardClamped_maybe  [dead: its only caller Vec3_RotateTowardFlatNormalized_maybe 0x2644c0 is dead]
//   [ ] 0x2644c0  Vec3_RotateTowardFlatNormalized_maybe  [dead]
#include "k2000/math/Vec3.h"

#include <cmath>
#include <cstring>

#include "crt/ppc_ops.h"
#include "crt/xsinf.h"

namespace {
bool SignBit(float angle) {
    uint32_t bits;
    std::memcpy(&bits, &angle, 4);
    return (bits >> 31) != 0;
}
}  // namespace

// 0x00264140 Vec3_RotateTowardClamped_maybe: `v` turned toward `target` by at most `maxAngle` radians about n = v x
// target (normalised): when the two are within the angle (dot >= cos, cror gt|eq) v becomes the target and 1 is returned;
// else v = v cos + (v x n) sin (fused, with fmadds of 0 for the cosine terms), 0. A zero (or NaN) cross product length
// (ble): v unchanged, 0. The game's inlined sine / cosine (the library's 0x9a1390 / 0x9a11d8 for a negative angle). TOC
// 0x3f0 (0), 0x3fc (1). Dead in the original (its only caller Vec3_RotateTowardFlatNormalized_maybe 0x2644c0 is dead).
int32_t Vec3_RotateTowardClamped(CVector3* v, const CVector3* target, float maxAngle) {
    const float vz = v->z;
    const float tx = target->x;
    const float vy = v->y;
    const float vx = v->x;
    const float tz = target->z;
    const float ty = target->y;
    const float ny = ppc::fmsubs(tz, vx, vz * tx);
    const float nx = ppc::fmsubs(ty, vz, tz * vy);
    const float nz = ppc::fmsubs(vy, tx, ty * vx);
    const float length = std::sqrt(ppc::fmadds(nz, nz, ppc::fmadds(nx, nx, ny * ny)));  // Math_Sqrtf 0x10690
    if (!(length > 0.0f)) return 0;
    const float s = SignBit(maxAngle) ? -crt::LibSinf(-maxAngle) : crt::InlineSinf(maxAngle);
    const float c = SignBit(maxAngle) ? crt::LibCosf(-maxAngle) : crt::InlineCosf(maxAngle);
    const float y3 = v->y;
    const float y12 = target->y;
    const float x13 = target->x;
    const float x4 = v->x;
    const float z5 = v->z;
    const float z6 = target->z;
    const float dot = ppc::fmadds(z5, z6, ppc::fmadds(x13, x4, y3 * y12));
    if (dot >= c) {
        v->z = z6;
        v->x = x13;
        v->y = y12;
        return 1;
    }
    const float inverse = 1.0f / length;
    const float unitZ = nz * inverse;
    const float unitX = nx * inverse;
    const float unitY = ny * inverse;
    const float cz = ppc::fmadds(c, z5, 0.0f);
    const float cx = ppc::fmadds(c, x4, 0.0f);
    const float cy = ppc::fmadds(c, y3, 0.0f);
    const float crossY = ppc::fmsubs(z5, unitX, x4 * unitZ);
    const float crossZ = ppc::fmsubs(x4, unitY, y3 * unitX);
    const float crossX = ppc::fmsubs(y3, unitZ, z5 * unitY);
    v->y = ppc::fmadds(s, crossY, cy);
    v->z = ppc::fmadds(s, crossZ, cz);
    v->x = ppc::fmadds(s, crossX, cx);
    return 0;
}
