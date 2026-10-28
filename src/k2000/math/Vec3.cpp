//
// Reconstructed original translation unit: 0x243ff0-0x244a08 (GAME_TOC1, main_toc1), 16 functions, 15 live.
// Primary owner: Vec3 (not a registered class)
// Other owners: FreeListPool (3)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x243ff0  Vec3_CrossNormalized
//   [ ] 0x2440a8  Vec3_CrossNormalized_2
//   [ ] 0x244160  Vec3_IsWithinXZRadiusSq_maybe  [dead]
//   [ ] 0x2441e8  Vec3_IsWithinRadius_maybe
//   [ ] 0x244298  Vec3_IsWithinXZRadius_maybe
//   [x] 0x244320  Vec3_IsWithinDistance
//   [x] 0x2443d8  Vec3_GetAngleInXYPlane
//   [x] 0x244528  Vec3_GetYawAngleFromZ
//   [x] 0x244638  Vec3_GetYawAngleFromX
//   [x] 0x244748  Vec3_GetAngleInYZPlane
//   [ ] 0x244878  FreeListPool_RebuildFreeList_maybe
//   [ ] 0x2448e0  StaticInitAndDestruction_2448e0
//   [ ] 0x2448e8  _GLOBAL__I_2448e8
//   [ ] 0x2448f8  _GLOBAL__D_2448f8
//   [ ] 0x244908  FreeListPool_Grow
//   [ ] 0x2449a0  FreeListPool_FreeChunks
#include "k2000/math/Vec3.h"

#include <cmath>

#include "crt/ppc_ops.h"
#include "crt/xatan.h"

// 0x00244638 Vec3_GetYawAngleFromX: acos of the normalised x component, mirrored to 2*pi - acos when z is
// negative; 0 for the zero vector and when x reaches 1, pi when it reaches -1. Single precision throughout
// (Math_Sqrtf = fsqrts, Math_Acosf through crt::Acosf).
float Vec3_GetYawAngleFromX(const CVector3* v) {
    float x = v->x;
    if (x == 0.0f && v->y == 0.0f) {
        if (v->z == 0.0f) return 0.0f;
    }
    float z = v->z;
    const float length = std::sqrt(ppc::fmadds(z, z, ppc::fmadds(x, x, 0.0f)));  // Math_Sqrtf 0x10690
    if (length == 0.0f) {
        if (x >= 1.0f) return 0.0f;
    } else {
        const float inv = 1.0f / length;
        x = x * inv;
        z = z * inv;
        if (x >= 1.0f) return 0.0f;
    }
    if (x <= -1.0f) return 3.14159274101257324f;  // TOC1 -0x1f0 (0x40490fdb)
    const float angle = crt::Acosf(x);
    if (z >= 0.0f) return angle;
    return 6.28318548202514648f - angle;  // TOC1 -0x1ec (0x40c90fdb)
}

// 0x00244528 Vec3_GetYawAngleFromZ: the same as Vec3_GetYawAngleFromX with x and z swapped: acos of the
// normalised z component (the (x, z) length; y only takes part in the zero-vector test), mirrored to 2*pi - acos
// when x is negative; 0 for the zero vector and when z reaches 1, pi when it reaches -1. The last test is
// `bge` (a NaN x keeps the acos).
float Vec3_GetYawAngleFromZ(const CVector3* v) {
    float x = v->x;
    if (x == 0.0f && v->y == 0.0f) {
        if (v->z == 0.0f) return 0.0f;
    }
    float z = v->z;
    const float length = std::sqrt(ppc::fmadds(z, z, ppc::fmadds(x, x, 0.0f)));  // Math_Sqrtf 0x10690
    if (length == 0.0f) {
        if (z >= 1.0f) return 0.0f;
    } else {
        const float inv = 1.0f / length;
        z = z * inv;
        x = x * inv;
        if (z >= 1.0f) return 0.0f;
    }
    if (z <= -1.0f) return 3.14159274101257324f;  // TOC1 -0x1f0 (0x40490fdb)
    const float angle = crt::Acosf(z);            // TocBridge_Math_Acosf 0x98e1a0
    if (!(x < 0.0f)) return angle;
    return 6.28318548202514648f - angle;  // TOC1 -0x1ec (0x40c90fdb)
}

// 0x00244320 Vec3_IsWithinDistance (the absolute values by clearing the sign bit in memory)
uint8_t Vec3_IsWithinDistance(float distance, const CVector3* a, const CVector3* b) {
    const float dx = std::fabs(a->x - b->x);
    if (dx > distance) return 0;
    const float dz = std::fabs(a->z - b->z);
    if (distance < dz) return 0;
    const float dy = std::fabs(a->y - b->y);
    if (distance < dy) return 0;
    float sum = dy * dy;
    sum = ppc::fmadds(dx, dx, sum);
    sum = ppc::fmadds(dz, dz, sum);
    return sum <= distance * distance ? 1 : 0;
}

namespace {
// The tail Vec3_GetYawAngleFromX's siblings share: the angle of the unit vector (a, b) from +a, in [0, 2*pi]; `length`
// is the length of (a, b) (a and b are normalised by it unless it is 0).
float AngleFromFirstAxis(float a, float b, float length) {
    if (length != 0.0f) {
        const float inv = 1.0f / length;
        a = a * inv;
        b = b * inv;
    }
    if (a >= 1.0f) return 0.0f;
    if (a <= -1.0f) return 3.14159274101257324f;  // TOC1 -0x1f0
    const float angle = crt::Acosf(a);
    if (b >= 0.0f) return angle;
    return 6.28318548202514648f - angle;  // TOC1 -0x1ec
}
}  // namespace

// 0x002443d8 Vec3_GetAngleInXYPlane: the angle of the (x, y) part from +x (2*pi - acos when y is negative); 0 for the
// zero vector. The squared length is y*y, then x fused, then + 0.
float Vec3_GetAngleInXYPlane(const CVector3* v) {
    const float x = v->x;
    const float y = v->y;
    if (x == 0.0f && y == 0.0f && v->z == 0.0f) return 0.0f;
    const float length = std::sqrt(ppc::fmadds(x, x, y * y) + 0.0f);  // Math_Sqrtf 0x10690
    return AngleFromFirstAxis(x, y, length);
}

// 0x00244748 Vec3_GetAngleInYZPlane: the angle of the (y, z) part from +y (2*pi - acos when z is negative); 0 for the
// zero vector. The squared length is fmadds(z, z, fmadds(y, y, 0)).
float Vec3_GetAngleInYZPlane(const CVector3* v) {
    const float y = v->y;
    const float z = v->z;
    if (v->x == 0.0f && y == 0.0f && z == 0.0f) return 0.0f;
    const float length = std::sqrt(ppc::fmadds(z, z, ppc::fmadds(y, y, 0.0f)));  // Math_Sqrtf 0x10690
    return AngleFromFirstAxis(y, z, length);
}
