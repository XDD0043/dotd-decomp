// Vec3.h - the game's 3-vector helpers (original unit Vec3.cpp, 0x243ff0-0x244a08) over CVector3.
#pragma once
#include <cstdint>

#include "k2000/math/CMatrix34.h"

// 0x00244638 Vec3_GetYawAngleFromX: the yaw of the vector's (x, z) part measured from +x, in [0, 2*pi].
float Vec3_GetYawAngleFromX(const CVector3* v);
// 0x00244528 Vec3_GetYawAngleFromZ: the yaw of the vector's (x, z) part measured from +z (step 5, the shared helpers).
float Vec3_GetYawAngleFromZ(const CVector3* v);
// 0x002441e8 Vec3_IsWithinRadius_maybe: `point` within `extent` of `center` on each axis (x, z, y; the absolute
// differences, a NaN passes), then its squared distance (y first, fused) at most `radiusSquared`. 1 or 0.
int32_t Vec3_IsWithinRadius(float extent, float radiusSquared, const float* center, const float* point);
// 0x00244298 Vec3_IsWithinXZRadius_maybe: `a` and `b` within `radius` on x and on z (the absolute differences; a NaN passes
// x, fails z), then the flat squared distance (z first, fused) at most radius squared (cror lt|eq). 1 or 0.
uint8_t Vec3_IsWithinXZRadius(float radius, const CVector3* a, const CVector3* b);
// 0x00244320 Vec3_IsWithinDistance: the points are at most `distance` apart (the x, z and y differences against it
// first, then the squared length, y first, fused, against distance squared).
uint8_t Vec3_IsWithinDistance(float distance, const CVector3* a, const CVector3* b);
// 0x002443d8 Vec3_GetAngleInXYPlane / 0x00244748 Vec3_GetAngleInYZPlane: the angle of the (x, y) part from +x / of the
// (y, z) part from +y, in [0, 2*pi].
float Vec3_GetAngleInXYPlane(const CVector3* v);
float Vec3_GetAngleInYZPlane(const CVector3* v);
// 0x00010fc0 Vec3_CubicBezier (k2000/misc/Str.cpp): the cubic Bezier curve through p0 .. p3 at t, as the original's
// fused sums: (1-t)^3 p0 + 3(1-t)^2 t p1, then + 3(1-t) t^2 p2, then + t^3 p3.
void Vec3_CubicBezier(float t, CVector3* out, const CVector3* p0, const CVector3* p1, const CVector3* p2,
                      const CVector3* p3);
// 0x00010eb0 Bezier2D_EvaluateDeCasteljau_maybe (k2000/misc/Str.cpp): the point at `t` of the Bezier curve with
// `count` control points (x, y float pairs) into out[0..1].
void Bezier2D_EvaluateDeCasteljau(int32_t count, const float* points, float t, float* out);
// 0x00010b68 Bezier_SampleCurvePoints (k2000/misc/Str.cpp; the trails' strips): `samples` points of the Bezier curve
// with `count` control points, at t = 0, then t summed by 1 / (samples - 1), by de Casteljau's levels in the shared
// work buffer.
void Bezier_SampleCurvePoints(int32_t count, const CVector3* points, int32_t samples, CVector3* out);
// 0x00243ff0 Vec3_CrossNormalized / 0x002440a8 Vec3_CrossNormalized_2 (the same code; both dead in the original):
// out = a x b, written component by component (out may alias a or b: the later components read them again), then
// normalised by rwInvSqrt (Math_InvSqrtf 0x114d8) unless its squared length is 0.
void Vec3_CrossNormalized(CVector3* out, const CVector3* a, const CVector3* b);
void Vec3_CrossNormalized_2(CVector3* out, const CVector3* a, const CVector3* b);

// The engine's node pool (FreeListPool; the ten global pools at 0x00ceaa20, set up by FreeListPools_InitGlobal_maybe
// 0x244a08 with each node size and count). Nodes are linked through their first word while free; a chunk (count nodes
// behind a link word, the next chunk) is allocated when the free list is empty. The port's node users allocate with
// new / delete by design, except the contact histories (k2000/math/Math.cpp, the pool 0x00ceaa70: 0x18-byte nodes,
// 0x200 per chunk), which use this pool. The link word is a pointer here (sizeof(void*), the PS3's 4).
struct FreeListPool {
    void* m_pChunks;          // +0x00 the chunk list (each chunk's first word: the chunk allocated before it)
    void* m_pFree;            // +0x04 the free nodes (each one's first word: the next)
    uint32_t m_ui32NodeSize;  // +0x08
    uint32_t m_ui32Count;     // +0x0c nodes per chunk
};
// 0x00244908 FreeListPool_Grow: a chunk of count nodes (Mem_AllocAligned16 of count * size + the link word) put in
// front of the chunk list; the free list becomes its nodes in address order, the last one's link 0.
void FreeListPool_Grow(FreeListPool* pool);
// 0x00244878 FreeListPool_RebuildFreeList_maybe (dead in the original): BUG(original): as compiled it never returns once
// there is a chunk (the first chunk's nodes are relinked over and over); with no chunk the free list is cleared.
void FreeListPool_RebuildFreeList(FreeListPool* pool);
// 0x002449a0 FreeListPool_FreeChunks (dead in the original): every chunk freed (Mem_FreeAligned16), both lists cleared.
void FreeListPool_FreeChunks(FreeListPool* pool);
// The pool's two inlined operations (ContactHistory: CKCrumblyZoneState 0x403c20 / 0x404050): a node taken from the free
// list (FreeListPool_Grow when it is empty) / given back in front of it.
void* FreeListPool_Alloc(FreeListPool* pool);
void FreeListPool_Free(FreeListPool* pool, void* node);
// 0x00264140 Vec3_RotateTowardClamped_maybe (k2000/math/Vec3_2.cpp; dead in the original): `v` turned toward `target`
// by at most `maxAngle` radians; 1 when it reached it.
int32_t Vec3_RotateTowardClamped(CVector3* v, const CVector3* target, float maxAngle);
