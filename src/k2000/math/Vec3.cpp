//
// Reconstructed original translation unit: 0x243ff0-0x244a08 (GAME_TOC1, main_toc1), 16 functions, 15 live.
// Primary owner: Vec3 (not a registered class)
// Other owners: FreeListPool (3)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x243ff0  Vec3_CrossNormalized  [dead: no pointer to its descriptor 0xb82458, no call]
//   [x] 0x2440a8  Vec3_CrossNormalized_2  [dead: no pointer to its descriptor 0xb82460, no call]
//   [ ] 0x244160  Vec3_IsWithinXZRadiusSq_maybe  [dead]
//   [x] 0x2441e8  Vec3_IsWithinRadius_maybe
//   [x] 0x244298  Vec3_IsWithinXZRadius_maybe
//   [x] 0x244320  Vec3_IsWithinDistance
//   [x] 0x2443d8  Vec3_GetAngleInXYPlane
//   [x] 0x244528  Vec3_GetYawAngleFromZ
//   [x] 0x244638  Vec3_GetYawAngleFromX
//   [x] 0x244748  Vec3_GetAngleInYZPlane
//   [x] 0x244878  FreeListPool_RebuildFreeList_maybe  [dead: no pointer to its descriptor 0xb824a8, no call]
//   [x] 0x2448e0  StaticInitAndDestruction_2448e0  (empty: the unit's static init / destruction has nothing to do; no code needed)
//   [ ] 0x2448e8  _GLOBAL__I_2448e8
//   [ ] 0x2448f8  _GLOBAL__D_2448f8
//   [x] 0x244908  FreeListPool_Grow  (FreeListPool_Grow, Vec3.h: the contact-history pool (Math.cpp) grows through it; the other pools' users allocate with new / delete by design)
//   [x] 0x2449a0  FreeListPool_FreeChunks  [dead: no pointer to its descriptor 0xb824d0, no call]
#include "k2000/math/Vec3.h"

#include <cmath>

#include "crt/ppc_ops.h"
#include "crt/xatan.h"
#include "k2000/memory/Mem.h"
#include "Renderware/rwcore/RwMatrix.h"
#include <cstring>

// 0x002441e8 Vec3_IsWithinRadius_maybe. The absolute values go through memory (the sign bit cleared, clrlwi), as
// std::fabs. The axis tests are bgt / blt: a NaN difference does not fail them.
int32_t Vec3_IsWithinRadius(float extent, float radiusSquared, const float* center, const float* point) {
    const float dx = std::fabs(center[0] - point[0]);
    if (dx > extent) return 0;
    const float dz = std::fabs(center[2] - point[2]);
    if (extent < dz) return 0;
    const float dy = std::fabs(center[1] - point[1]);
    if (extent < dy) return 0;
    return ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)) <= radiusSquared ? 1 : 0;
}

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

// 0x00244298 Vec3_IsWithinXZRadius_maybe
uint8_t Vec3_IsWithinXZRadius(float radius, const CVector3* a, const CVector3* b) {
    const float dx = std::fabs(a->x - b->x);  // the sign bit cleared through memory
    if (dx > radius) return 0;
    const float dz = std::fabs(a->z - b->z);
    if (radius < dz) return 0;
    return ppc::fmadds(dx, dx, dz * dz) <= radius * radius ? 1 : 0;
}

namespace {
// The cross product as Vec3_CrossNormalized computes it: each component stored before the next one reads a and b
// again (TOC -0x1fc: 0; beq: a NaN squared length normalises).
void CrossNormalized(CVector3* out, const CVector3* a, const CVector3* b) {
    const float az = a->z;
    const float byz = b->y;
    const float bz = b->z;
    out->x = ppc::fmsubs(a->y, bz, az * byz);
    const float ax = a->x;
    const float bx = b->x;
    out->y = ppc::fmsubs(az, bx, ax * bz);
    const float yy = out->y * out->y;
    const float ayBx = a->y * bx;
    const float by = b->y;
    float squared = ppc::fmadds(out->x, out->x, yy);
    const float z = ppc::fmsubs(ax, by, ayBx);
    squared = ppc::fmadds(z, z, squared);
    out->z = z;
    if (squared == 0.0f) return;
    const float inverse = rwInvSqrt(squared);  // Math_InvSqrtf 0x114d8 -> RW_InvSqrt 0x0075e790
    const float x = inverse * out->x;
    const float zz = inverse * out->z;
    const float yv = inverse * out->y;
    out->x = x;
    out->z = zz;
    out->y = yv;
}

void* NodeLink(void* node) {
    void* next;
    std::memcpy(&next, node, sizeof(next));
    return next;
}
void SetNodeLink(void* node, void* next) { std::memcpy(node, &next, sizeof(next)); }
}  // namespace

// 0x00243ff0 Vec3_CrossNormalized (dead: no pointer to its descriptor 0xb82458, no call)
void Vec3_CrossNormalized(CVector3* out, const CVector3* a, const CVector3* b) { CrossNormalized(out, a, b); }
// 0x002440a8 Vec3_CrossNormalized_2 (dead: no pointer to its descriptor 0xb82460, no call)
void Vec3_CrossNormalized_2(CVector3* out, const CVector3* a, const CVector3* b) { CrossNormalized(out, a, b); }

// 0x00244878 FreeListPool_RebuildFreeList_maybe: BUG(original): the code branches back to its node loop after each
// pass (the first chunk's nodes, last to first, each linked to the one after it) and never reaches its exit when there
// is a chunk; a count of 0 spins too. Kept as compiled (dead in the original: no pointer to its descriptor 0xb824a8).
void FreeListPool_RebuildFreeList(FreeListPool* pool) {
    uint8_t* chunk = static_cast<uint8_t*>(pool->m_pChunks);
    if (chunk == nullptr) {
        pool->m_pFree = nullptr;
        return;
    }
    uint8_t* nodes = chunk + sizeof(void*);
    void* next = nullptr;
    for (;;) {
        const uint32_t count = pool->m_ui32Count;
        if (count == 0) continue;
        for (uint32_t index = count; index-- > 0;) {
            uint8_t* node = nodes + static_cast<size_t>(index) * pool->m_ui32NodeSize;
            SetNodeLink(node, next);
            next = node;
        }
    }
}

// 0x00244908 FreeListPool_Grow
void FreeListPool_Grow(FreeListPool* pool) {
    uint8_t* chunk = static_cast<uint8_t*>(
        Mem_AllocAligned16(pool->m_ui32NodeSize * pool->m_ui32Count + static_cast<uint32_t>(sizeof(void*))));
    SetNodeLink(chunk, pool->m_pChunks);
    const uint32_t count = pool->m_ui32Count;
    uint8_t* node = chunk + sizeof(void*);
    pool->m_pChunks = chunk;
    pool->m_pFree = node;
    if (count != 1) {
        for (uint32_t i = count - 1; i != 0; --i) {  // ctr = count - 1 (count 0: 0xffffffff passes in the original)
            uint8_t* next = node + pool->m_ui32NodeSize;
            SetNodeLink(node, next);
            node = next;
        }
    }
    SetNodeLink(node, nullptr);
}

// 0x002449a0 FreeListPool_FreeChunks (dead: no pointer to its descriptor 0xb824d0, no call)
void FreeListPool_FreeChunks(FreeListPool* pool) {
    void* chunk = pool->m_pChunks;
    while (chunk != nullptr) {
        void* next = NodeLink(chunk);
        Mem_FreeAligned16(chunk);
        chunk = next;
    }
    pool->m_pFree = nullptr;
    pool->m_pChunks = nullptr;
}

void* FreeListPool_Alloc(FreeListPool* pool) {
    void* node = pool->m_pFree;
    if (node == nullptr) {
        FreeListPool_Grow(pool);
        node = pool->m_pFree;
    }
    pool->m_pFree = NodeLink(node);
    return node;
}

void FreeListPool_Free(FreeListPool* pool, void* node) {
    SetNodeLink(node, pool->m_pFree);
    pool->m_pFree = node;
}
