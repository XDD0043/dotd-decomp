// Str.cpp - reconstructed original translation unit 0x10b68-0x12158 (GAME_TOC1, main_toc1), 40 functions, 27 live.
// Primary owner: Str (not a registered class)
// Other owners: Mem (6), ClassRegistry (6), Bezier2D (2), Path (2), KeyValueStr (2), WStr (2), Bezier (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x10b68  Bezier_SampleCurvePoints
//   [ ] 0x10d20  Bezier2D_SampleCurvePoints  [dead]
//   [x] 0x10eb0  Bezier2D_EvaluateDeCasteljau_maybe
//   [x] 0x10fc0  Vec3_CubicBezier
//   [ ] 0x11080  Bits_ReverseLow  [dead]
//   [ ] 0x110d8  Char_ToLower  [dead]
//   [x] 0x11100  Mem_FreeAlignedAndNull  (keCThreadPool's constructor frees the workers' names with it)
//   [ ] 0x11148  Mem_FreeAlignedAndNull_2  [dead]
//   [ ] 0x11190  Mem_FreeAligned16_Callback_maybe  [platform]  (RenderWare's / the audio library's memory callback (CKGraphic_InitializeModule, CKSoundManager_InitializeModule): both use the host heap natively)
//   [ ] 0x111b8  Mem_AllocAligned16_Callback_maybe  [platform]  (RenderWare's / the audio library's memory callback: the host heap natively)
//   [x] 0x111e0  Str_VFormatBounded
//   [x] 0x11248  Str_CopyBounded  (its caller CKSoundStreamManager_FindOrCreateType_maybe is not ported yet)
//   [ ] 0x112f8  Path_GetFileNamePtr_2  [dead]
//   [x] 0x11368  ClassRegistry_GetClassDebugNameByKey
//   [x] 0x113a8  ClassRegistry_GetClassDebugName
//   [x] 0x113e8  ClassRegistry_GetObjectDebugName
//   [x] 0x11420  ClassRegistry_DestroyObject
//   [x] 0x11458  ClassRegistry_CreateObject
//   [x] 0x11498  ClassRegistry_CreateObjectByKey
//   [x] 0x114d8  Math_InvSqrtf  (rwInvSqrt (Renderware/rwcore/RwMatrix.h): the callers call it directly)
//   [x] 0x11500  Rand_Int
//   [ ] 0x11528  Mem_ReallocAligned16_Callback_maybe  [platform]  (RenderWare's / the audio library's memory callback: the host heap natively)
//   [ ] 0x11550  Mem_CallocAligned16_Callback_maybe  [platform]  (RenderWare's / the audio library's memory callback: the host heap natively)
//   [x] 0x11578  StaticInitAndDestruction_11578  (the math constants it builds (1.0 vectors, FLT_MAX vectors, the unit axes) are constants in their users (CLightManager.cpp, CLightComponent.cpp, IKCinematicBloc.cpp, SpawnInstance.cpp, CKHkTransportableObjectSpawner.cpp))
//   [ ] 0x11710  _GLOBAL__D_11710
//   [ ] 0x11720  _GLOBAL__I_11720
//   [x] 0x11730  KStub_Nop_11730
//   [ ] 0x11738  KeyValueStr_KeyEqualsNoCase_maybe  [dead]
//   [ ] 0x117d8  KeyValueStr_HashKeyNoCase_maybe  [dead]
//   [ ] 0x11860  Crc16_Compute  [dead]
//   [ ] 0x119b0  Crc32_Compute_maybe  [dead]
//   [x] 0x11c10  WStr_CatReturnEnd  (local copy)
//   [x] 0x11c88  WStr_Sprintf  (local copy)
//   [x] 0x11d38  Str_VFormatAlloc
//   [ ] 0x11f00  Str_VFormatAllocTo  [dead]
//   [ ] 0x11f48  Str_VFormatAllocTo_2  [dead]
//   [x] 0x11f90  Str_FormatAllocTo  (keCThreadPool's constructor names its workers with it)
//   [ ] 0x11ff8  Str_FormatAllocTo_2  [dead]
//   [ ] 0x12060  Str_FormatBounded  [dead]
//   [x] 0x120e8  Path_GetFileNamePtr  (local copy)
//
//   [ ] 0x990ca8  CKObjectRoot_DeletingDestructor  [inline]
//   [ ] 0x990cd8  CKObjectRoot_Destructor  [inline]
//   [ ] 0x990ce8  KStub_Nop_990ce8  [inline]
//   [x] 0x995c18  Str_EqualsPredicate_maybe  [inline]
#include "k2000/misc/ClassRegistry.h"

#include <cstdint>
#include <cstdio>
#include <cstring>

#include "crt/rand.h"
#include "crt/ppc_ops.h"
#include "k2000/math/Vec3.h"
#include "k2000/misc/ClassManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Str.h"

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

// 0x000111e0 Str_VFormatBounded (vsnprintf through TocBridge_vsnprintf: the host's, as the remake's other formatting).
// The bound passed is size - 1 as an unsigned word (size 0 gives 0xffffffff, as on the PS3).
int32_t Str_VFormatBounded(char* dst, int32_t size, const char* format, va_list args) {
    const int32_t result = std::vsnprintf(dst, static_cast<uint32_t>(size - 1), format, args);
    if (result < 0) dst[size - 1] = 0;
    return result;
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

// 0x00010b68 Bezier_SampleCurvePoints (C2.7: the trails' strips, CTrailNodeFx_UpdateTrailGeometry_maybe): for each
// sample the curve point by de Casteljau's levels in the shared work buffer (the pointer at 0x00c50d30; PORT: a static
// buffer here, as Bezier2D_EvaluateDeCasteljau's), t from 0 summed by 1 / (samples - 1). One control point:
// BUG(original): the buffer's first point as it is.
namespace {
// One sample of Bezier_SampleCurvePoints: de Casteljau's levels at `t` in the work buffer; the point is buffer[0].
void BezierSampleLevels(int32_t count, const CVector3* points, float t, CVector3* buffer) {
    int32_t first = count - 1;
    if (first > 1365) first = 1365;  // PORT: the original's block holds 1365 points
    for (int32_t j = 0; j < first; ++j) {
        const CVector3& a = points[j];
        const CVector3& b = points[j + 1];
        buffer[j].z = ppc::fmadds(b.z - a.z, t, a.z);
        buffer[j].x = ppc::fmadds(b.x - a.x, t, a.x);
        buffer[j].y = ppc::fmadds(b.y - a.y, t, a.y);
    }
    for (int32_t n = count - 2; n != -1 && n >= -1; --n) {
        for (int32_t j = 0; j < n && j < 1364; ++j) {
            const CVector3 a = buffer[j];
            buffer[j].z = ppc::fmadds(buffer[j + 1].z - a.z, t, a.z);
            buffer[j].x = ppc::fmadds(buffer[j + 1].x - a.x, t, a.x);
            buffer[j].y = ppc::fmadds(buffer[j + 1].y - a.y, t, a.y);
        }
    }
}

#if DOTD_PPC_HW_FMA
// PERF: eight samples at a time, one per lane (the trails' strips were the largest single function of a frame). Every
// lane runs the operations of BezierSampleLevels in their order on its own t: a float subtraction, then one fused
// multiply-add (VFMADD: IEEE fusedMultiplyAdd, as ppc::fmadds), so each sample's point has the same bits. Only a NaN's
// payload could differ from the library's: a sample with a NaN coordinate is left to the scalar code (a NaN anywhere in
// a coordinate's levels reaches its result, every level's value being a sum that includes it).
constexpr int32_t kBezierLanePoints = 64;  // more control points than this: the scalar code

// The points of the samples [first, first + 8) at the t values `ts`, into px / py / pz.
void BezierSampleLanes(int32_t count, const CVector3* points, const float* ts, float* px, float* py, float* pz) {
    __m256 bx[kBezierLanePoints], by[kBezierLanePoints], bz[kBezierLanePoints];
    const __m256 t = _mm256_loadu_ps(ts);
    for (int32_t j = 0; j < count - 1; ++j) {
        const CVector3& a = points[j];
        const CVector3& b = points[j + 1];
        bz[j] = _mm256_fmadd_ps(_mm256_set1_ps(b.z - a.z), t, _mm256_set1_ps(a.z));
        bx[j] = _mm256_fmadd_ps(_mm256_set1_ps(b.x - a.x), t, _mm256_set1_ps(a.x));
        by[j] = _mm256_fmadd_ps(_mm256_set1_ps(b.y - a.y), t, _mm256_set1_ps(a.y));
    }
    for (int32_t n = count - 2; n >= 1; --n) {
        for (int32_t j = 0; j < n; ++j) {
            bz[j] = _mm256_fmadd_ps(_mm256_sub_ps(bz[j + 1], bz[j]), t, bz[j]);
            bx[j] = _mm256_fmadd_ps(_mm256_sub_ps(bx[j + 1], bx[j]), t, bx[j]);
            by[j] = _mm256_fmadd_ps(_mm256_sub_ps(by[j + 1], by[j]), t, by[j]);
        }
    }
    _mm256_storeu_ps(px, bx[0]);
    _mm256_storeu_ps(py, by[0]);
    _mm256_storeu_ps(pz, bz[0]);
    _mm256_zeroupper();  // (the code around this is not VEX-encoded)
}
#endif
}  // namespace

void Bezier_SampleCurvePoints(int32_t count, const CVector3* points, int32_t samples, CVector3* out) {
    static CVector3 buffer[1365];  // the 16 KB block in 12-byte points
    const float step = 1.0f / static_cast<float>(static_cast<double>(samples - 1));  // TOC -0x7fb0
    if (samples - 1 == -1) return;
    float t = 0.0f;  // TOC -0x7fa8
#if DOTD_PPC_HW_FMA
    // PERF (BezierSampleLanes): 2 .. kBezierLanePoints control points, the output not overlapping the control points
    // (the loop below reads them again for every sample) and an FMA3 CPU; else the loop below.
    const uintptr_t pointsBegin = reinterpret_cast<uintptr_t>(points), pointsEnd = reinterpret_cast<uintptr_t>(points + (count > 0 ? count : 0));
    const uintptr_t outBegin = reinterpret_cast<uintptr_t>(out), outEnd = reinterpret_cast<uintptr_t>(out + (samples > 0 ? samples : 0));
    if (ppc::detail::g_hardwareFma && count >= 2 && count <= kBezierLanePoints && samples >= 1 &&
        (outEnd <= pointsBegin || pointsEnd <= outBegin)) {
        for (int32_t i = 0; i < samples;) {
            const int32_t lanes = samples - i < 8 ? samples - i : 8;
            float ts[8] = {};  // (an unused lane computes the curve at 0)
            for (int32_t k = 0; k < lanes; ++k) {
                ts[k] = t;
                t = t + step;  // the running sum of the loop below (one more sum after the last sample, unused)
            }
            float px[8], py[8], pz[8];
            BezierSampleLanes(count, points, ts, px, py, pz);
            for (int32_t k = 0; k < lanes; ++k) {
                CVector3& o = out[i + k];
                if (px[k] == px[k] && py[k] == py[k] && pz[k] == pz[k]) {
                    o.x = px[k];
                    o.y = py[k];
                    o.z = pz[k];
                } else {  // a NaN: the scalar code's bits
                    BezierSampleLevels(count, points, ts[k], buffer);
                    o.x = buffer[0].x;
                    o.y = buffer[0].y;
                    o.z = buffer[0].z;
                }
            }
            i += lanes;
        }
        // The work buffer's first point is the last sample's, as the loop below leaves it (a later call with one control
        // point returns it: the original's bug). The other entries are written before they are read by every call.
        buffer[0].x = out[samples - 1].x;
        buffer[0].y = out[samples - 1].y;
        buffer[0].z = out[samples - 1].z;
        return;
    }
#endif
    for (int32_t i = 0;; ++out) {
        BezierSampleLevels(count, points, t, buffer);
        out->x = buffer[0].x;
        out->y = buffer[0].y;
        out->z = buffer[0].z;
        if (++i == samples) break;
        t = t + step;
    }
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

// 0x00011100 Mem_FreeAlignedAndNull
void Mem_FreeAlignedAndNull(char** block) {
    if (*block != nullptr) {
        Mem_FreeAligned16(*block);
        *block = nullptr;
    }
}

// 0x00011248 Str_CopyBounded (strlen inline, strncpy / strcpy through their TocBridges)
void Str_CopyBounded(char* dst, const char* src, uint32_t size) {
    const uint32_t length = static_cast<uint32_t>(std::strlen(src));
    if (size <= length) {
        std::strncpy(dst, src, size);
        dst[size - 1] = 0;
        return;
    }
    std::strcpy(dst, src);
}

// 0x00011d38 Str_VFormatAlloc (vsnprintf through its TocBridge: the host's). The PS3 va_list is passed by value to each
// vsnprintf; natively each attempt takes a copy.
char* Str_VFormatAlloc(const char* format, va_list args, char* buffer, int32_t size, uint32_t* allocated) {
    if (buffer != nullptr) {
        va_list copy;
        va_copy(copy, args);
        const int32_t result = std::vsnprintf(buffer, static_cast<uint32_t>(size - 1), format, copy);
        va_end(copy);
        if (result >= 0) return buffer;
        buffer[size - 1] = 0;
    }
    uint32_t capacity = static_cast<uint32_t>(std::strlen(format));
    if (capacity < 0x400) capacity = 0x400;
    char* text = static_cast<char*>(Mem_AllocAligned16(capacity));
    for (;;) {
        va_list copy;
        va_copy(copy, args);
        const int32_t result = std::vsnprintf(text, capacity - 1, format, copy);
        va_end(copy);
        if (result >= 0) break;
        text[capacity - 1] = 0;
        if (text != nullptr) Mem_FreeAligned16(text);
        capacity = capacity << 1;
        text = static_cast<char*>(Mem_AllocAligned16(capacity));
    }
    if (allocated != nullptr) *allocated = capacity;
    return text;
}

// 0x00011f90 Str_FormatAllocTo (the size word goes to a stack slot nobody reads)
void Str_FormatAllocTo(char** out, const char* format, ...) {
    va_list args;
    va_start(args, format);
    uint32_t allocated = 0;
    *out = Str_VFormatAlloc(format, args, nullptr, 0, &allocated);
    va_end(args);
}
