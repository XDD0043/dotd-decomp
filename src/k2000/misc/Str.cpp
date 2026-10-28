// Str.cpp - reconstructed original translation unit 0x10b68-0x12158 (GAME_TOC1, main_toc1), 40 functions, 27 live.
// Primary owner: Str (not a registered class)
// Other owners: Mem (6), ClassRegistry (6), Bezier2D (2), Path (2), KeyValueStr (2), WStr (2), Bezier (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x10b68  Bezier_SampleCurvePoints
//   [ ] 0x10d20  Bezier2D_SampleCurvePoints  [dead]
//   [x] 0x10eb0  Bezier2D_EvaluateDeCasteljau_maybe
//   [x] 0x10fc0  Vec3_CubicBezier
//   [ ] 0x11080  Bits_ReverseLow  [dead]
//   [ ] 0x110d8  Char_ToLower  [dead]
//   [ ] 0x11100  Mem_FreeAlignedAndNull
//   [ ] 0x11148  Mem_FreeAlignedAndNull_2  [dead]
//   [ ] 0x11190  Mem_FreeAligned16_Callback_maybe
//   [ ] 0x111b8  Mem_AllocAligned16_Callback_maybe
//   [ ] 0x111e0  Str_VFormatBounded
//   [ ] 0x11248  Str_CopyBounded
//   [ ] 0x112f8  Path_GetFileNamePtr_2  [dead]
//   [x] 0x11368  ClassRegistry_GetClassDebugNameByKey
//   [x] 0x113a8  ClassRegistry_GetClassDebugName
//   [x] 0x113e8  ClassRegistry_GetObjectDebugName
//   [x] 0x11420  ClassRegistry_DestroyObject
//   [x] 0x11458  ClassRegistry_CreateObject
//   [x] 0x11498  ClassRegistry_CreateObjectByKey
//   [ ] 0x114d8  Math_InvSqrtf
//   [x] 0x11500  Rand_Int
//   [ ] 0x11528  Mem_ReallocAligned16_Callback_maybe
//   [ ] 0x11550  Mem_CallocAligned16_Callback_maybe
//   [ ] 0x11578  StaticInitAndDestruction_11578
//   [ ] 0x11710  _GLOBAL__D_11710
//   [ ] 0x11720  _GLOBAL__I_11720
//   [x] 0x11730  KStub_Nop_11730
//   [ ] 0x11738  KeyValueStr_KeyEqualsNoCase_maybe  [dead]
//   [ ] 0x117d8  KeyValueStr_HashKeyNoCase_maybe  [dead]
//   [ ] 0x11860  Crc16_Compute  [dead]
//   [ ] 0x119b0  Crc32_Compute_maybe  [dead]
//   [ ] 0x11c10  WStr_CatReturnEnd
//   [ ] 0x11c88  WStr_Sprintf
//   [ ] 0x11d38  Str_VFormatAlloc
//   [ ] 0x11f00  Str_VFormatAllocTo  [dead]
//   [ ] 0x11f48  Str_VFormatAllocTo_2  [dead]
//   [ ] 0x11f90  Str_FormatAllocTo
//   [ ] 0x11ff8  Str_FormatAllocTo_2  [dead]
//   [ ] 0x12060  Str_FormatBounded  [dead]
//   [ ] 0x120e8  Path_GetFileNamePtr
//
//   [ ] 0x990ca8  CKObjectRoot_DeletingDestructor  [inline]
//   [ ] 0x990cd8  CKObjectRoot_Destructor  [inline]
//   [ ] 0x990ce8  KStub_Nop_990ce8  [inline]
//   [ ] 0x995c18  Str_EqualsPredicate_maybe  [inline]
#include "k2000/misc/ClassRegistry.h"

#include "crt/rand.h"
#include "crt/ppc_ops.h"
#include "k2000/math/Vec3.h"
#include "k2000/misc/ClassManager.h"
#include "k2000/misc/Engine.h"

// 0x00011368 ClassRegistry_GetClassDebugNameByKey
const char* ClassRegistry_GetClassDebugNameByKey(uint32_t key) {
    return g_pEngine->m_classManager->GetClassDebugName(key & 0x3f, (key >> 6) & 0x7ff);
}

// 0x000113a8 ClassRegistry_GetClassDebugName
const char* ClassRegistry_GetClassDebugName(uint32_t category, uint32_t id) {
    return g_pEngine->m_classManager->GetClassDebugName(category, id);
}

// 0x000113e8 ClassRegistry_GetObjectDebugName
const char* ClassRegistry_GetObjectDebugName(IKBaseClass* object) {
    return g_pEngine->m_classManager->GetObjectDebugName(object);
}

// 0x00011420 ClassRegistry_DestroyObject
void ClassRegistry_DestroyObject(IKBaseClass* object) { g_pEngine->m_classManager->DestroyObject(object); }

// 0x00011458 ClassRegistry_CreateObject
IKBaseClass* ClassRegistry_CreateObject(int32_t category, uint32_t id) {
    return g_pEngine->m_classManager->CreateObject(category, id);
}

// 0x00011498 ClassRegistry_CreateObjectByKey
IKBaseClass* ClassRegistry_CreateObjectByKey(uint32_t key) {
    return g_pEngine->m_classManager->CreateObject(static_cast<int32_t>(key & 0x3f), (key >> 6) & 0x7ff);
}

// 0x00011500 Rand_Int
int32_t Rand_Int() { return crt::rand(); }

// 0x00011730 KStub_Nop_11730: called at the end of Main_InitGame_maybe (an empty debug hook).
void KStub_Nop_11730() {}

// 0x00010fc0 Vec3_CubicBezier (step 4 AI: the partner's catch-up warp)
void Vec3_CubicBezier(float t, CVector3* out, const CVector3* p0, const CVector3* p1, const CVector3* p2,
                      const CVector3* p3) {
    const float s = 1.0f - t;
    const float t3 = t * (t * t);
    const float s3x = s * 3.0f;
    const float s2 = s * s;
    const float a = s * s3x;
    const float s3 = s * s2;
    const float b = t * s3x;
    const float c1 = t * a;  // 3 s^2 t
    const float c2 = t * b;  // 3 s t^2
    const float z = ppc::fmadds(s3, p0->z, c1 * p1->z);
    const float x = ppc::fmadds(s3, p0->x, c1 * p1->x);
    const float y = ppc::fmadds(s3, p0->y, c1 * p1->y);
    const float z2 = ppc::fmadds(c2, p2->z, z);
    const float x2 = ppc::fmadds(c2, p2->x, x);
    const float y2 = ppc::fmadds(c2, p2->y, y);
    out->z = ppc::fmadds(t3, p3->z, z2);
    out->x = ppc::fmadds(t3, p3->x, x2);
    out->y = ppc::fmadds(t3, p3->y, y2);
}

// 0x00010eb0 Bezier2D_EvaluateDeCasteljau_maybe (step 6 FLY: CKCurve_Evaluate_maybe's kind 1): the point at `t` of
// the Bezier curve with `count` control points (x, y pairs), by de Casteljau's levels in the shared work buffer (the
// pointer at 0x00c50d30; PORT: a static buffer here). One point: BUG(original): the buffer's first point as it is.
void Bezier2D_EvaluateDeCasteljau(int32_t count, const float* points, float t, float* out) {
    static float buffer[2 * 256];
    int32_t level = count - 1;
    if (level > 256) level = 256;  // PORT: the original's buffer size is not known; LVL010's curves are short
    for (int32_t i = 0; i < level; ++i) {
        const float y0 = points[2 * i + 1];
        const float x0 = points[2 * i];
        buffer[2 * i + 1] = ppc::fmadds(t, points[2 * i + 3] - y0, y0);
        buffer[2 * i] = ppc::fmadds(t, points[2 * i + 2] - x0, x0);
    }
    for (int32_t n = count - 2; n != -1; --n) {
        for (int32_t j = 0; j < n; ++j) {
            const float x0 = buffer[2 * j];
            const float y0 = buffer[2 * j + 1];
            buffer[2 * j + 1] = ppc::fmadds(t, buffer[2 * j + 3] - y0, y0);
            buffer[2 * j] = ppc::fmadds(buffer[2 * j + 2] - x0, t, x0);
        }
    }
    out[0] = buffer[0];
    out[1] = buffer[1];
}
