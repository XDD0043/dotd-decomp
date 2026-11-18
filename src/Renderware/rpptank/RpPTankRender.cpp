// RpPTankRender.cpp - the PTank atomic's render path (RpPTankAtomicRender, rpworld/RpAtomic.h): the
// PS3's RW_RenderParticleTankAtomic 0x7799a0 with the callbacks the PS3 build installs, the per-quad
// vertex instancers, and the PSGL quad draw, rewritten to draw through RwIm3D.
//
// The callbacks (from the asm, not the decompile's labels):
//   - RpPTankAtomicCreate passes the callback block at 0xcf07a4 (RpPTank_InitCallbacks_maybe 0x77ada8 fills
//     it): +0 storage 0 (default), +4 create = 0x77b500 RpPTank_CreateEmptyQuadGeometry_maybe, +8 prepare =
//     the game's 0x8bb78 PTank_InstanceAtomic_maybe (InitCallbacks' argument), +0xc draw = 0x77aea8
//     DrawPSGLParticleQuadBatch, +0x10.. the PSGL ring vertex buffer (GL name, offset, used size, capacity,
//     mapped flag, mapped pointer).
//   - 0x77b500 calls the format hook at 0xcfbbc4 = the game's 0x8b918 PTank_SetupInstanceFormat_maybe, which
//     stores the instancer indices (+0x28/+0x2c/+0x30/+0x34) and +0x24 = 0x779020 / +0x38 = 0x7781f8, then
//     0x77b500 OVERWRITES +0x38 = 0 and +0x24 = 0x77b6b8 RwPSGLPTank_PrepareQuadVertexBuffer_maybe. So on the
//     PS3 the setup callback is 0x77b6b8 (the PSGL ring buffer, interleaved vertices), never 0x779020 (the
//     generic geometry-lock version: RpGeometryLock, the -666 clear of unused vertices, 12-byte strides, with
//     which the VMX instancers would write every vertex to the buffer start), and there is no unlock.
//   - The draw returns 1 always, so 0x7799a0 always calls the saved default render too (+0x10: the
//     atomic's original render callback, RpAtomicCreate's default, on the empty quad geometry: it draws nothing).
//
// Ported (exact float ops from the asm; VMX vmaddfp = fused, ppc::fmadds per lane; vnmsubfp = ppc::fnmsubs):
//   0x007799a0 RW_RenderParticleTankAtomic, 0x0008bb78 PTank_InstanceAtomic_maybe, 0x0008b918
//   PTank_SetupInstanceFormat_maybe (the selection), 0x0077b6b8 RwPSGLPTank_PrepareQuadVertexBuffer_maybe,
//   0x0077aea8 DrawPSGLParticleQuadBatch;
//   positions (table 0xb16af8): 1 0x77bc98, 2 0x77bea8, 3 0x77d7d8 (VMX), 4 0x77c128, 5 0x77dd10 (VMX),
//   6 0x77d388 (scalar, roundf 0x77f4c0), 7 0x77c380, 8 0x77e2b8 (scalar), 9 0x77c660, 10 0x77c838;
//   tex coords (0xb16b24): 1 0x77cc58, 2 0x77cd48, 3 0x77ce20, 4 0x77ced0;
//   colours (0xb16b38): 1 0x77c9d0, 2 0x77ca78, 3 0x77cb40, 4 0x77cbe0; the combined 0x77d070;
//   normals 0x777fa0 RpPTankInstanceNormals_PerParticle_maybe.
// The lighting (geometry flag 0x20, set only with rpPTANKDFLAGNORMAL: RwPSGL_AtomicLightingCallback_maybe 0x6b9730,
//   RwPSGL_ApplyMaterialLighting_maybe 0x6ba440, rpworld/RpPSGLLighting.cpp) is GL fixed-function state; with lighting
//   on the draw lights each vertex through platform/gfx/fixed_lighting (the device has no fixed-function pipeline).
//   No PTank of the game data has normals (every level's CParticleGeometry PTanks are 0x10080023, RpPrtStd never
//   asks for them): the game only takes the unlit path.
// The PTank's geometry (RpPTankAtomicCreate, rpworld/RpAtomic.cpp) is an empty quad geometry with one material: the
//   geometry flags say which attributes the vertices have, the material holds the texture (RpMaterialSetTexture by
//   CParticleGeometry_Load, the glow, RpPrtStd and CMaterial::SetTexture through CMaterial_Load's reference).
//
// Native shape: the PS3 instancers write 16-byte positions (w = 1.0f), then tex coords and the colour into
// one interleaved vertex of the mapped ring buffer (stride 16 + 8 textured + 4 prelit, 16-aligned, + 12
// normals, 16-aligned). Here a QuadVertex array holds the same values per vertex (the stride does not
// matter), and the draw turns each GL_QUADS quad (v0, v1, v2, v3) into the triangles (v0, v1, v2) and
// (v0, v2, v3) of an indexed RwIm3D triangle list, world space (null LTM).
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rpworld/RpGeometry.h"
#include "Renderware/rpworld/RpPSGLLighting.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwDevice.h"
#include "Renderware/rwcore/RwIm3D.h"
#include "Renderware/rwcore/RwTexture.h"
#include "Renderware/rwcore/RwTypes.h"
#include "crt/ppc_ops.h"
#include "crt/xlround.h"
#include "crt/xsin.h"
#include "platform/gfx/fixed_lighting.h"

#if defined(_MSC_VER) && (defined(_M_X64) || defined(_M_IX86))
#include <immintrin.h>
#include <intrin.h>
#define PTANK_X86 1
#define PTANK_INLINE __forceinline
#else
#define PTANK_X86 0
#define PTANK_INLINE inline
#endif

namespace {

// dotd perf: the per-particle helpers are inlined (RelWithDebInfo's /Ob1 inlines only functions marked inline), and the
// fused multiply-adds of the instancers use the CPU's FMA instruction when it has one (the C library's fmaf is a call
// per operation). Both give the same bits as std::fmaf: one rounding of the exact a * b + c (checked bit for bit).
#if PTANK_X86
bool DetectFma() {
    int r[4];
    __cpuid(r, 1);
    const bool sse41 = (r[2] & (1 << 19)) != 0;
    const bool fma = (r[2] & (1 << 12)) != 0;
    const bool osxsave = (r[2] & (1 << 27)) != 0;
    const bool avx = (r[2] & (1 << 28)) != 0;
    if (!(sse41 && fma && osxsave && avx)) return false;
    return (_xgetbv(0) & 6u) == 6u;  // the OS saves the SSE and AVX state (VEX-encoded instructions)
}
const bool g_hasFma = DetectFma();
#endif

// ppc::fmadds (std::fmaf). A NaN result is computed again by the library (its payload can depend on the operand order of
// the VFMADD form the compiler picks); every other result is the same bits.
PTANK_INLINE float Fmadds(float a, float b, float c) {
#if PTANK_X86
    if (g_hasFma) {
        const float r = _mm_cvtss_f32(_mm_fmadd_ss(_mm_set_ss(a), _mm_set_ss(b), _mm_set_ss(c)));
        if (r == r) return r;
    }
#endif
    return std::fmaf(a, b, c);
}
// ppc::fnmsubs: -fmaf(a, b, -c), as written there (the sign of an exact zero result included).
PTANK_INLINE float Fnmsubs(float a, float b, float c) { return -Fmadds(a, b, -c); }
// std::nearbyint (the current rounding mode, no inexact exception): SSE4.1 roundss with the same mode.
PTANK_INLINE float NearbyInt(float x) {
#if PTANK_X86
    if (g_hasFma) {
        const __m128 v = _mm_set_ss(x);
        return _mm_cvtss_f32(_mm_round_ss(v, v, _MM_FROUND_CUR_DIRECTION | _MM_FROUND_NO_EXC));
    }
#endif
    return std::nearbyint(x);
}

PTANK_INLINE float WordF(uint32_t w) {
    float f;
    std::memcpy(&f, &w, 4);
    return f;
}
PTANK_INLINE float LoadF(const uint8_t* p) {
    float f;
    std::memcpy(&f, p, 4);
    return f;
}

// Library TOC constants (0xc25974 - offset).
const float kHalf = WordF(0x3f000000u);  // -0x2f34 (scalar instancers), and the VMX vectors 0xad18d0 / 0xad17c0
const float kOne = WordF(0x3f800000u);   // -0x2f30: the position's w (also the VMX vectors 0xad18e0 / 0xad1840)
// The VMX sine/cosine vectors (0x77dd10: 0xad1850.. ; 0x77d7d8: 0xad17d0..; the same words).
const float kInv2Pi = WordF(0x3e22f983u);    // 1/(2 pi)
const float kMinus2Pi = WordF(0xc0c90fdbu);  // -2 pi
const float kHalfPi = WordF(0x3fc90fdbu);
const float kPi = WordF(0x40490fdbu);
const float kSinA = WordF(0x3fa2f983u);      // 4/pi
const float kSinB = WordF(0x3ecf817bu);      // 4/pi^2
const float kSinBNeg = WordF(0xbecf817bu);   // -4/pi^2

// The per-particle arrays (rpPTANKDFLAG 1 << index).
enum : int { kArrPosition = 0, kArrColor = 1, kArrSize = 2, kArrMatrix = 3, kArrNormal = 4, kArrRotate = 5,
             kArrVtxColor = 6, kArrTex2 = 7, kArrTex4 = 8 };

// One quad vertex as the PS3 instancers leave it in the PSGL buffer.
struct QuadVertex {
    float pos[4];      // +0x00: x, y, z, w (1.0f)
    float uv[2];       // +0x10 when textured
    uint8_t color[4];  // after the tex coords (+0x18, or +0x10 untextured): the RwRGBA bytes
    float normal[3];   // the normal (RpPTankInstanceNormals_PerParticle_maybe), geometry flag 0x10
};

// PTank_InstanceAtomic_maybe's instance block (0x40 bytes at sp+0x70, zeroed before the setup callback).
// The PS3 attribute pointers (+0x10 positions / +0x18 tex coords / +0x20 colours / +0x28 normals, each with
// the buffer stride) are set exactly when the matching flag is: here the flags and one vertex array.
struct InstanceData {
    int32_t positions;  // +0x00 always 1
    int32_t texCoords;  // +0x04 the material has a texture (geometry flag 4)
    int32_t colors;     // +0x08 prelit (geometry flag 8)
    int32_t normals;    // +0x0c geometry flag 0x10
    QuadVertex* vertices;
    float right[3];     // +0x30 the billboard's right axis
    float up[3];        // +0x3c the billboard's up axis
};

// The instancer indices 0x8b918 stores at PTank +0x28 / +0x2c / +0x30 / +0x34.
struct InstanceFormat {
    int32_t position;
    int32_t texCoords;
    int32_t color;
    bool normals;  // +0x34 = RpPTankInstanceNormals_PerParticle_maybe, else 0
};

// The PS3 ring buffer the prepare callback fills and the draw reads (natively: this frame's vertices).
thread_local std::vector<QuadVertex> g_quadVertices;
thread_local std::vector<RwIm3DVertex> g_imVertices;
thread_local std::vector<RwImVertexIndex> g_imIndices;

PTANK_INLINE const uint8_t* Elem(const RpPTankData* tank, int arr, int32_t i, int32_t stride) {
    return tank->data[arr] + static_cast<intptr_t>(i) * stride;
}

// ---- the instance format -----------------------------------------------------------------------------

// 0x0008b918 PTank_SetupInstanceFormat_maybe (called once at creation through 0x77b500; the indices only
// depend on the data flags, so they are computed here). Its +0x24 / +0x38 stores are overwritten by 0x77b500
// (see the top).
InstanceFormat SetupInstanceFormat(uint32_t flags) {
    InstanceFormat f{};
    const bool center = (flags & 0x1000000u) != 0;  // rpPTANKDFLAGUSECENTER
    if ((flags & 0x8u) != 0) {
        f.position = center ? 10 : 9;   // per-particle matrix
    } else if ((flags & 0x8000u) == 0 && (flags & 0x20u) != 0) {
        if ((flags & 0x4u) != 0) f.position = center ? 8 : 5;  // per-particle size + 2D rotation
        else f.position = center ? 6 : 3;                      // 2D rotation, constant size
    } else if ((flags & 0x8000u) == 0 && (flags & 0x4u) != 0) {
        f.position = center ? 7 : 4;    // per-particle size
    } else {
        f.position = center ? 2 : 1;    // constant size (also with a constant matrix 0x8000)
    }
    if ((flags & 0x80u) != 0) f.texCoords = 1;
    else if ((flags & 0x100u) != 0) f.texCoords = 2;
    else if ((flags & 0x80000u) != 0) f.texCoords = 3;
    else if ((flags & 0x100000u) != 0) f.texCoords = 4;
    else f.texCoords = 0;
    if ((flags & 0x2u) != 0) f.color = 1;
    else if ((flags & 0x40u) != 0) f.color = 2;
    else if ((flags & 0x40000u) != 0) f.color = 3;
    else f.color = 4;
    f.normals = (flags & 0x10u) != 0;
    return f;
}

// ---- position instancers (table 0xb16af8) -------------------------------------------------------------
// Every instancer gives the quad's vertices in the same order: v0 = P - B - A, v1 = P + B - A,
// v2 = P + B + A, v3 = P - B + A, B the half width along the right axis, A the half height along the up axis.
// With the setup's right = -camera right (RW's camera x points to the screen's left) and up = camera up:
// v0 bottom left, v1 bottom right, v2 top right, v3 top left on screen (counter-clockwise).

PTANK_INLINE void SetW(QuadVertex* v) {
    for (int k = 0; k < 4; ++k) v[k].pos[3] = kOne;
}

// The four offsets of a quad with half extents B (right) and A (up), as the scalar instancers form them.
PTANK_INLINE void QuadOffsets(float o[4][3], const float* B, const float* A) {
    for (int k = 0; k < 3; ++k) {
        o[0][k] = -B[k] - A[k];  // fneg + fsubs
        o[1][k] = B[k] - A[k];
        o[2][k] = B[k] + A[k];
        o[3][k] = A[k] - B[k];
    }
}

// 0x0077bc98 RpPTankInstanceBillboardPosB_GlobalSize_maybe (index 1): the constant size (PS3 +0xc0).
void InstancePosGlobalSize(InstanceData* inst, int32_t count, const RpPTankData* tank) {
    const float hw = WordF(tank->renderC0[0]) * kHalf;
    const float hh = WordF(tank->renderC0[1]) * kHalf;
    float B[3], A[3], o[4][3];
    for (int k = 0; k < 3; ++k) {
        B[k] = hw * inst->right[k];
        A[k] = hh * inst->up[k];
    }
    QuadOffsets(o, B, A);
    const int32_t stride = tank->stride[kArrPosition];
    for (int32_t i = 0; i < count; ++i) {
        const uint8_t* p = Elem(tank, kArrPosition, i, stride);
        QuadVertex* v = &inst->vertices[i * 4];
        for (int q = 0; q < 4; ++q)
            for (int k = 0; k < 3; ++k) v[q].pos[k] = o[q][k] + LoadF(p + 4 * k);
        SetW(v);
    }
}

// The constant center (PS3 +0xb8 / +0xbc, RwV2d) in billboard space: cx * right + cy * up (fmuls, fmadds).
void CenterOffset(float* C, const InstanceData* inst, const RpPTankData* tank) {
    const float cx = WordF(tank->wordB8);
    const float cy = WordF(tank->wordBC);
    for (int k = 0; k < 3; ++k) C[k] = Fmadds(cx, inst->right[k], cy * inst->up[k]);
}

// 0x0077bea8 RpPTankInstanceBillboardPosB_GlobalSizeCenter_maybe (index 2): the constant size moved by the
// center. BUG(original): only the constant width is read (+0xc0); it is the half extent of both axes (the
// height +0xc4 is ignored), so the quads are square.
void InstancePosGlobalSizeCenter(InstanceData* inst, int32_t count, const RpPTankData* tank) {
    const float hw = WordF(tank->renderC0[0]) * kHalf;
    float B[3], A[3], C[3], o[4][3];
    for (int k = 0; k < 3; ++k) {
        B[k] = inst->right[k] * hw;
        A[k] = inst->up[k] * hw;
    }
    CenterOffset(C, inst, tank);
    QuadOffsets(o, B, A);
    for (int q = 0; q < 4; ++q)
        for (int k = 0; k < 3; ++k) o[q][k] = C[k] + o[q][k];
    const int32_t stride = tank->stride[kArrPosition];
    for (int32_t i = 0; i < count; ++i) {
        const uint8_t* p = Elem(tank, kArrPosition, i, stride);
        QuadVertex* v = &inst->vertices[i * 4];
        for (int q = 0; q < 4; ++q)
            for (int k = 0; k < 3; ++k) v[q].pos[k] = o[q][k] + LoadF(p + 4 * k);
        SetW(v);
    }
}

// 0x0077c128 RpPTankInstanceBillboardPosB_PerParticleSize_maybe (index 4).
void InstancePosPerParticleSize(InstanceData* inst, int32_t count, const RpPTankData* tank) {
    const int32_t posStride = tank->stride[kArrPosition];
    const int32_t sizeStride = tank->stride[kArrSize];
    for (int32_t i = 0; i < count; ++i) {
        const uint8_t* p = Elem(tank, kArrPosition, i, posStride);
        const uint8_t* s = Elem(tank, kArrSize, i, sizeStride);
        const float hw = LoadF(s) * kHalf;
        const float hh = LoadF(s + 4) * kHalf;
        float B[3], A[3], o[4][3];
        for (int k = 0; k < 3; ++k) {
            B[k] = hw * inst->right[k];
            A[k] = hh * inst->up[k];
        }
        QuadOffsets(o, B, A);
        QuadVertex* v = &inst->vertices[i * 4];
        for (int q = 0; q < 4; ++q)
            for (int k = 0; k < 3; ++k) v[q].pos[k] = LoadF(p + 4 * k) + o[q][k];
        SetW(v);
    }
}

// 0x0077c380 RpPTankInstanceBillboardPosB_PerParticleSizeCenter_maybe (index 7): (center + P) + offset.
void InstancePosPerParticleSizeCenter(InstanceData* inst, int32_t count, const RpPTankData* tank) {
    float C[3];
    CenterOffset(C, inst, tank);
    const int32_t posStride = tank->stride[kArrPosition];
    const int32_t sizeStride = tank->stride[kArrSize];
    for (int32_t i = 0; i < count; ++i) {
        const uint8_t* p = Elem(tank, kArrPosition, i, posStride);
        const uint8_t* s = Elem(tank, kArrSize, i, sizeStride);
        const float hw = LoadF(s) * kHalf;
        const float hh = LoadF(s + 4) * kHalf;
        float B[3], A[3], o[4][3];
        for (int k = 0; k < 3; ++k) {
            B[k] = hw * inst->right[k];
            A[k] = hh * inst->up[k];
        }
        QuadOffsets(o, B, A);
        QuadVertex* v = &inst->vertices[i * 4];
        for (int q = 0; q < 4; ++q)
            for (int k = 0; k < 3; ++k) v[q].pos[k] = (C[k] + LoadF(p + 4 * k)) + o[q][k];
        SetW(v);
    }
}

// 0x0077c660 RpPTankInstanceBillboardPosB_PerParticleMatrix_maybe (index 9): the particle's matrix gives the
// axes (right +0, up +0x10, halved) and the position (+0x30); no camera axes.
void InstancePosPerParticleMatrix(InstanceData* inst, int32_t count, const RpPTankData* tank) {
    const int32_t stride = tank->stride[kArrMatrix];
    for (int32_t i = 0; i < count; ++i) {
        const uint8_t* m = Elem(tank, kArrMatrix, i, stride);
        QuadVertex* v = &inst->vertices[i * 4];
        for (int k = 0; k < 3; ++k) {
            const float hr = LoadF(m + 4 * k) * kHalf;
            const float hu = LoadF(m + 0x10 + 4 * k) * kHalf;
            const float p = LoadF(m + 0x30 + 4 * k);
            const float d = hr - hu;
            const float s = hr + hu;
            v[0].pos[k] = d + p;
            v[1].pos[k] = p - s;
            v[2].pos[k] = p - d;
            v[3].pos[k] = s + p;
        }
        SetW(v);
    }
}

// 0x0077c838 RpPTankInstanceBillboardPosB_PerParticleMatrixCenter_maybe (index 10): as index 9, the axes
// summed before halving, the position moved by the center along the matrix axes.
void InstancePosPerParticleMatrixCenter(InstanceData* inst, int32_t count, const RpPTankData* tank) {
    const float cx = WordF(tank->wordB8);
    const float cy = WordF(tank->wordBC);
    const int32_t stride = tank->stride[kArrMatrix];
    for (int32_t i = 0; i < count; ++i) {
        const uint8_t* m = Elem(tank, kArrMatrix, i, stride);
        QuadVertex* v = &inst->vertices[i * 4];
        for (int k = 0; k < 3; ++k) {
            const float r = LoadF(m + 4 * k);
            const float u = LoadF(m + 0x10 + 4 * k);
            const float p = LoadF(m + 0x30 + 4 * k);
            const float s = (r + u) * kHalf;
            const float d = (r - u) * kHalf;
            const float q = Fmadds(cy, u, Fmadds(cx, r, p));
            v[0].pos[k] = d + q;
            v[1].pos[k] = q - s;
            v[2].pos[k] = q - d;
            v[3].pos[k] = s + q;
        }
        SetW(v);
    }
}

// One lane of the VMX sine and cosine (0x77dd10 and 0x77d7d8): the angle reduced to [-pi, pi] (vrfin of
// angle / 2 pi: round to nearest even), then the parabola 4/pi x -+ 4/pi^2 x|x| picked by the sign (vsel on
// vcmpgefp 0 >= x); the cosine is the sine of x + pi/2, wrapped by -2 pi at pi and above. Not bit-exact
// where the PS3's VMX (non-Java mode) flushes denormals to zero.
struct VmxSinCos {
    float s;
    float c;
};
PTANK_INLINE VmxSinCos VmxSinCosLane(float rot) {
    const float n = NearbyInt(Fmadds(rot, kInv2Pi, 0.0f));
    const float x = Fmadds(n, kMinus2Pi, rot);
    float cx = x + kHalfPi;
    const float wrapped = cx + kMinus2Pi;
    const float sNeg = Fmadds(x, Fmadds(x, kSinB, kSinA), 0.0f);
    const float sPos = Fmadds(x, Fmadds(x, kSinBNeg, kSinA), 0.0f);
    VmxSinCos r;
    r.s = (0.0f >= x) ? sNeg : sPos;
    if (cx >= kPi) cx = wrapped;
    const float cNeg = Fmadds(cx, Fmadds(cx, kSinB, kSinA), 0.0f);
    const float cPos = Fmadds(cx, Fmadds(cx, kSinBNeg, kSinA), 0.0f);
    r.c = (0.0f >= cx) ? cNeg : cPos;
    return r;
}

// The VMX quad of one particle: the axes rotated by the angle, scaled by the half extents (vmaddfp with a
// zero addend), and the four vertices from P (vaddfp / vsubfp), w = 1.0f (vsel with the xyz mask).
PTANK_INLINE void VmxRotatedQuad(QuadVertex* v, const uint8_t* p, const InstanceData* inst, VmxSinCos sc, float hw,
                                 float hh) {
    for (int k = 0; k < 3; ++k) {
        const float sR = Fmadds(sc.s, inst->right[k], 0.0f);
        const float nsU = Fnmsubs(sc.s, inst->up[k], 0.0f);
        const float t1 = Fmadds(sc.c, inst->up[k], sR);     // c up + s right
        const float t2 = Fmadds(sc.c, inst->right[k], nsU); // c right - s up
        const float A = Fmadds(t1, hh, 0.0f);
        const float B = Fmadds(t2, hw, 0.0f);
        const float ba = B + A;
        const float amb = A - B;
        const float bma = B - A;
        const float P = LoadF(p + 4 * k);
        v[0].pos[k] = P - ba;
        v[1].pos[k] = P + bma;
        v[2].pos[k] = P + ba;
        v[3].pos[k] = P + amb;
    }
    SetW(v);
}

#if PTANK_X86
// dotd perf: four particles of the VMX instancers (index 3 / 5) at once, as the PS3 does them: VmxSinCosLane and
// VmxRotatedQuad lane by lane (vfmadd = the fused multiply-add, roundps = nearbyint, blendv = the selects; the same
// operations in the same order, so the same bits), the positions (stride 16) transposed in, the vertices (x, y, z, 1.0f)
// transposed out. hw / hh: the four particles' half extents. Returns false, having written nothing, when a vertex would
// be NaN: the caller then makes the four particles with the scalar code (a NaN's payload is the library's there).
// Needs g_hasFma (FMA3 and SSE4.1).
PTANK_INLINE bool VmxRotatedQuads4(QuadVertex* v, const uint8_t* positions, const uint8_t* rotations, __m128 hw, __m128 hh,
                                   const InstanceData* inst) {
    const __m128 zero = _mm_setzero_ps();
    const __m128 negZero = _mm_set1_ps(-0.0f);
    const __m128 sinA = _mm_set1_ps(kSinA);
    const __m128 sinB = _mm_set1_ps(kSinB);
    const __m128 sinBNeg = _mm_set1_ps(kSinBNeg);
    // VmxSinCosLane
    const __m128 rot = _mm_loadu_ps(reinterpret_cast<const float*>(rotations));
    const __m128 n = _mm_round_ps(_mm_fmadd_ps(rot, _mm_set1_ps(kInv2Pi), zero), _MM_FROUND_CUR_DIRECTION | _MM_FROUND_NO_EXC);
    const __m128 x = _mm_fmadd_ps(n, _mm_set1_ps(kMinus2Pi), rot);
    __m128 cx = _mm_add_ps(x, _mm_set1_ps(kHalfPi));
    const __m128 wrapped = _mm_add_ps(cx, _mm_set1_ps(kMinus2Pi));
    const __m128 sNeg = _mm_fmadd_ps(x, _mm_fmadd_ps(x, sinB, sinA), zero);
    const __m128 sPos = _mm_fmadd_ps(x, _mm_fmadd_ps(x, sinBNeg, sinA), zero);
    const __m128 sn = _mm_blendv_ps(sPos, sNeg, _mm_cmpge_ps(zero, x));             // (0.0f >= x) ? sNeg : sPos
    cx = _mm_blendv_ps(cx, wrapped, _mm_cmpge_ps(cx, _mm_set1_ps(kPi)));          // if (cx >= kPi) cx = wrapped
    const __m128 cNeg = _mm_fmadd_ps(cx, _mm_fmadd_ps(cx, sinB, sinA), zero);
    const __m128 cPos = _mm_fmadd_ps(cx, _mm_fmadd_ps(cx, sinBNeg, sinA), zero);
    const __m128 cs = _mm_blendv_ps(cPos, cNeg, _mm_cmpge_ps(zero, cx));            // (0.0f >= cx) ? cNeg : cPos
    // The positions of the four particles as x, y, z vectors.
    __m128 p0 = _mm_loadu_ps(reinterpret_cast<const float*>(positions));
    __m128 p1 = _mm_loadu_ps(reinterpret_cast<const float*>(positions + 16));
    __m128 p2 = _mm_loadu_ps(reinterpret_cast<const float*>(positions + 32));
    __m128 p3 = _mm_loadu_ps(reinterpret_cast<const float*>(positions + 48));
    _MM_TRANSPOSE4_PS(p0, p1, p2, p3);
    const __m128 P[3] = {p0, p1, p2};
    // VmxRotatedQuad
    __m128 out[4][3];
    __m128 nan = zero;
    for (int k = 0; k < 3; ++k) {
        const __m128 right = _mm_set1_ps(inst->right[k]);
        const __m128 up = _mm_set1_ps(inst->up[k]);
        const __m128 sR = _mm_fmadd_ps(sn, right, zero);
        const __m128 nsU = _mm_xor_ps(_mm_fmadd_ps(sn, up, negZero), negZero);  // Fnmsubs(s, up, 0.0f) = -fma(s, up, -0.0f)
        const __m128 t1 = _mm_fmadd_ps(cs, up, sR);
        const __m128 t2 = _mm_fmadd_ps(cs, right, nsU);
        const __m128 A = _mm_fmadd_ps(t1, hh, zero);
        const __m128 B = _mm_fmadd_ps(t2, hw, zero);
        const __m128 ba = _mm_add_ps(B, A);
        const __m128 amb = _mm_sub_ps(A, B);
        const __m128 bma = _mm_sub_ps(B, A);
        out[0][k] = _mm_sub_ps(P[k], ba);
        out[1][k] = _mm_add_ps(P[k], bma);
        out[2][k] = _mm_add_ps(P[k], ba);
        out[3][k] = _mm_add_ps(P[k], amb);
        for (int q = 0; q < 4; ++q) nan = _mm_or_ps(nan, _mm_cmpunord_ps(out[q][k], out[q][k]));
    }
    if (_mm_movemask_ps(nan) != 0) return false;
    const __m128 one = _mm_set1_ps(kOne);
    for (int q = 0; q < 4; ++q) {
        __m128 a = out[q][0], b = out[q][1], c = out[q][2], w = one;
        _MM_TRANSPOSE4_PS(a, b, c, w);  // a = (x, y, z, 1) of particle 0, b of particle 1, ...
        _mm_storeu_ps(v[0 * 4 + q].pos, a);
        _mm_storeu_ps(v[1 * 4 + q].pos, b);
        _mm_storeu_ps(v[2 * 4 + q].pos, c);
        _mm_storeu_ps(v[3 * 4 + q].pos, w);
    }
    return true;
}
#endif

// 0x0077d7d8 RpPTankInstanceBillboardPosB_GlobalSizeRotate_Vmx_maybe (index 3): the constant size (+0xc0,
// x 0.5 by vmaddfp), the per-particle 2D rotation (fixed stride 4), positions at a fixed stride 16. The PS3
// works in groups of 4 particles (the arrays' 4 spare entries and the buffer's 16 spare vertices take the
// excess, which is never drawn); only count particles are made here.
void InstancePosGlobalSizeRotateVmx(InstanceData* inst, int32_t count, const RpPTankData* tank) {
    const float hw = Fmadds(WordF(tank->renderC0[0]), kHalf, 0.0f);
    const float hh = Fmadds(WordF(tank->renderC0[1]), kHalf, 0.0f);
    int32_t i = 0;
#if PTANK_X86
    if (g_hasFma) {
        const __m128 hw4 = _mm_set1_ps(hw);
        const __m128 hh4 = _mm_set1_ps(hh);
        for (; i + 4 <= count; i += 4) {
            if (VmxRotatedQuads4(&inst->vertices[i * 4], Elem(tank, kArrPosition, i, 16), Elem(tank, kArrRotate, i, 4), hw4,
                                 hh4, inst)) {
                continue;
            }
            for (int32_t j = i; j < i + 4; ++j) {
                const VmxSinCos sc = VmxSinCosLane(LoadF(Elem(tank, kArrRotate, j, 4)));
                VmxRotatedQuad(&inst->vertices[j * 4], Elem(tank, kArrPosition, j, 16), inst, sc, hw, hh);
            }
        }
    }
#endif
    for (; i < count; ++i) {
        const VmxSinCos sc = VmxSinCosLane(LoadF(Elem(tank, kArrRotate, i, 4)));
        VmxRotatedQuad(&inst->vertices[i * 4], Elem(tank, kArrPosition, i, 16), inst, sc, hw, hh);
    }
}

// 0x0077dd10 RpPTankInstanceBillboardPosB_PerParticleSizeRotate_Vmx_maybe (index 5): per-particle size
// (fixed stride 8, x 0.5 by vmaddfp) and 2D rotation (stride 4), positions at stride 16. Groups of 4 as
// index 3. (The buffer offsets are the stride / 16 (srawi 4) times 16..256: right for the PSGL strides, all
// multiples of 16.)
PTANK_INLINE void PerParticleSizeRotateVmxOne(InstanceData* inst, int32_t i, const RpPTankData* tank) {
    const uint8_t* s = Elem(tank, kArrSize, i, 8);
    const float hw = Fmadds(kHalf, LoadF(s), 0.0f);
    const float hh = Fmadds(kHalf, LoadF(s + 4), 0.0f);
    const VmxSinCos sc = VmxSinCosLane(LoadF(Elem(tank, kArrRotate, i, 4)));
    VmxRotatedQuad(&inst->vertices[i * 4], Elem(tank, kArrPosition, i, 16), inst, sc, hw, hh);
}
void InstancePosPerParticleSizeRotateVmx(InstanceData* inst, int32_t count, const RpPTankData* tank) {
    int32_t i = 0;
#if PTANK_X86
    if (g_hasFma) {
        const __m128 zero = _mm_setzero_ps();
        const __m128 half = _mm_set1_ps(kHalf);
        for (; i + 4 <= count; i += 4) {
            // The sizes (w, h) of the four particles (stride 8) as w and h vectors, halved: fma(kHalf, size, 0) per lane.
            const uint8_t* s = Elem(tank, kArrSize, i, 8);
            const __m128 s01 = _mm_loadu_ps(reinterpret_cast<const float*>(s));
            const __m128 s23 = _mm_loadu_ps(reinterpret_cast<const float*>(s + 16));
            const __m128 hw4 = _mm_fmadd_ps(half, _mm_shuffle_ps(s01, s23, _MM_SHUFFLE(2, 0, 2, 0)), zero);
            const __m128 hh4 = _mm_fmadd_ps(half, _mm_shuffle_ps(s01, s23, _MM_SHUFFLE(3, 1, 3, 1)), zero);
            if (VmxRotatedQuads4(&inst->vertices[i * 4], Elem(tank, kArrPosition, i, 16), Elem(tank, kArrRotate, i, 4), hw4,
                                 hh4, inst)) {
                continue;
            }
            for (int32_t j = i; j < i + 4; ++j) PerParticleSizeRotateVmxOne(inst, j, tank);
        }
    }
#endif
    for (; i < count; ++i) PerParticleSizeRotateVmxOne(inst, i, tank);
}

// The scalar sine and cosine of the rotating center instancers (0x77d388, 0x77e2b8): the angle reduced by
// roundf (0x77f4c0) of angle / 2 pi (float), then the parabola 4/pi x -+ 4/pi^2 x * x in double (the x * x
// term's sign by the sign of x, fmadd) rounded to float; the cosine is the sine of x + pi/2 (double add),
// wrapped by 2 pi above pi (double constants, TOC -0x2f1c / -0x2f14 / -0x2f0c / -0x2f04 / -0x2efc / -0x2ef4).
struct ScalarSinCos {
    float s;
    float c;
};
float ScalarParabola(float x) {
    constexpr double kA = 0x1.45f306c8462a6p+0;      // 0x3ff45f306c8462a6: 1.27323954 (8-digit 4 / pi)
    constexpr double kBPos = 0x1.9f02f62992759p-2;  // 0x3fd9f02f62992759: 0.405284735 (4 / pi^2)
    const double b = !(x < 0.0f) ? -kBPos : kBPos;  // bge / blt against 0.0f
    const double dx = static_cast<double>(x);
    return ppc::frsp(ppc::fmadd(dx, kA, dx * (dx * b)));
}
PTANK_INLINE ScalarSinCos ScalarSinCosOf(float rotation) {
    constexpr double kHalfPiD = 0x1.921fb52713c02p+0;  // 0x3ff921fb52713c02: 1.57079632
    constexpr double kPiD = 0x1.921fb53c8d4f1p+1;      // 0x400921fb53c8d4f1: 3.14159265
    constexpr double kTwoPiD = 0x1.921fb5474a168p+2;   // 0x401921fb5474a168: 6.28318531
    ScalarSinCos r;
    const float x = Fmadds(crt::roundf(rotation * kInv2Pi), kMinus2Pi, rotation);
    r.s = ScalarParabola(x);
    float cx = ppc::frsp(static_cast<double>(x) + kHalfPiD);
    if (cx > kPiD) cx = ppc::frsp(static_cast<double>(cx) - kTwoPiD);
    r.c = ScalarParabola(cx);
    return r;
}

// One rotating center quad (0x77d388 / 0x77e2b8): the axes rotated by the angle (up' = right s + up c,
// right' = right c - up s, fused), the center (cx right' + cy up', fused) moved to the particle, the half
// extents along the rotated axes, then the four corners as the other instancers order them, w = 1.0f.
PTANK_INLINE void RotatedCenterQuad(QuadVertex* v, const float* p, const InstanceData* inst, ScalarSinCos sc, float hw,
                                    float hh, float cx, float cy) {
    for (int k = 0; k < 3; ++k) {
        const float upRot = Fmadds(inst->right[k], sc.s, inst->up[k] * sc.c);
        const float rightRot = Fmadds(inst->right[k], sc.c, -sc.s * inst->up[k]);
        const float A = upRot * hh;
        const float B = rightRot * hw;
        const float center = Fmadds(rightRot, cx, upRot * cy);
        const float base = center + p[k];
        v[0].pos[k] = base + (-B - A);
        v[1].pos[k] = base + (B - A);
        v[2].pos[k] = base + (B + A);
        v[3].pos[k] = base + (A - B);
    }
    SetW(v);
}

// 0x0077d388 RpPTankInstanceBillboardPosB_GlobalSizeRotate_maybe (index 6: the constant size (+0xc0, halved),
// the per-particle 2D rotation, the constant center (+0xb8 / +0xbc), scalar code).
void InstancePosGlobalSizeRotateCenter(InstanceData* inst, int32_t count, const RpPTankData* tank) {
    const float hw = WordF(tank->renderC0[0]) * kHalf;
    const float hh = WordF(tank->renderC0[1]) * kHalf;
    const float cx = WordF(tank->wordB8);
    const float cy = WordF(tank->wordBC);
    for (int32_t i = 0; i < count; ++i) {
        const ScalarSinCos sc = ScalarSinCosOf(LoadF(Elem(tank, kArrRotate, i, tank->stride[kArrRotate])));
        const float* p = reinterpret_cast<const float*>(Elem(tank, kArrPosition, i, tank->stride[kArrPosition]));
        RotatedCenterQuad(&inst->vertices[i * 4], p, inst, sc, hw, hh, cx, cy);
    }
}

// 0x0077e2b8 RpPTankInstanceBillboardPosB_PerParticleSizeRotate_maybe (index 8: index 6 with the per-particle
// size, halved).
void InstancePosPerParticleSizeRotateCenter(InstanceData* inst, int32_t count, const RpPTankData* tank) {
    const float cx = WordF(tank->wordB8);
    const float cy = WordF(tank->wordBC);
    for (int32_t i = 0; i < count; ++i) {
        const ScalarSinCos sc = ScalarSinCosOf(LoadF(Elem(tank, kArrRotate, i, tank->stride[kArrRotate])));
        const uint8_t* s = Elem(tank, kArrSize, i, tank->stride[kArrSize]);
        const float hw = LoadF(s) * kHalf;
        const float hh = LoadF(s + 4) * kHalf;
        const float* p = reinterpret_cast<const float*>(Elem(tank, kArrPosition, i, tank->stride[kArrPosition]));
        RotatedCenterQuad(&inst->vertices[i * 4], p, inst, sc, hw, hh, cx, cy);
    }
}

// The position instancers by index (the table at 0xb16af8; 0 is null and never selected).
void InstancePositions(int32_t index, InstanceData* inst, int32_t count, const RpPTankData* tank) {
    switch (index) {
        case 1: InstancePosGlobalSize(inst, count, tank); break;
        case 2: InstancePosGlobalSizeCenter(inst, count, tank); break;
        case 3: InstancePosGlobalSizeRotateVmx(inst, count, tank); break;
        case 4: InstancePosPerParticleSize(inst, count, tank); break;
        case 5: InstancePosPerParticleSizeRotateVmx(inst, count, tank); break;
        case 6: InstancePosGlobalSizeRotateCenter(inst, count, tank); break;
        case 7: InstancePosPerParticleSizeCenter(inst, count, tank); break;
        case 8: InstancePosPerParticleSizeRotateCenter(inst, count, tank); break;
        case 9: InstancePosPerParticleMatrix(inst, count, tank); break;
        case 10: InstancePosPerParticleMatrixCenter(inst, count, tank); break;
        default: break;
    }
}

// ---- tex coord instancers (table 0xb16b24) ------------------------------------------------------------

PTANK_INLINE void SetUV(QuadVertex* v, float u, float w) {
    v->uv[0] = u;
    v->uv[1] = w;
}

// 0x0077cc58 RpPTankInstanceTexCoords_PerParticleA_maybe_2 (index 1, rpPTANKDFLAGVTX2TEXCOORDS 0x80): the
// particle's (u0, v0, u1, v1) as (u0, v1) (u1, v1) (u1, v0) (u0, v0).
void InstanceTexPerParticle2(InstanceData* inst, int32_t count, const RpPTankData* tank) {
    const int32_t stride = tank->stride[kArrTex2];
    for (int32_t i = 0; i < count; ++i) {
        const uint8_t* t = Elem(tank, kArrTex2, i, stride);
        QuadVertex* v = &inst->vertices[i * 4];
        SetUV(&v[0], LoadF(t), LoadF(t + 0xc));
        SetUV(&v[1], LoadF(t + 8), LoadF(t + 0xc));
        SetUV(&v[2], LoadF(t + 8), LoadF(t + 4));
        SetUV(&v[3], LoadF(t), LoadF(t + 4));
    }
}

// 0x0077cd48 RpPTankInstanceTexCoords_PerParticleB_maybe_2 (index 2, rpPTANKDFLAGVTX4TEXCOORDS 0x100): the
// particle's four (u, v) pairs in order.
void InstanceTexPerParticle4(InstanceData* inst, int32_t count, const RpPTankData* tank) {
    const int32_t stride = tank->stride[kArrTex4];
    for (int32_t i = 0; i < count; ++i) {
        const uint8_t* t = Elem(tank, kArrTex4, i, stride);
        QuadVertex* v = &inst->vertices[i * 4];
        for (int q = 0; q < 4; ++q) SetUV(&v[q], LoadF(t + 8 * q), LoadF(t + 8 * q + 4));
    }
}

// 0x0077ce20 RpPTankInstanceTexCoords_GlobalA_maybe_2 (index 3, rpPTANKDFLAGCNSVTX2TEXCOORDS 0x80000): the
// constant (u0, v0, u1, v1) (PS3 +0xe0) as index 1.
void InstanceTexGlobal2(InstanceData* inst, int32_t count, const RpPTankData* tank) {
    const float u0 = WordF(tank->texCoordsE0[0]);
    const float v0 = WordF(tank->texCoordsE0[1]);
    const float u1 = WordF(tank->texCoordsE0[2]);
    const float v1 = WordF(tank->texCoordsE0[3]);
    for (int32_t i = 0; i < count; ++i) {
        QuadVertex* v = &inst->vertices[i * 4];
        SetUV(&v[0], u0, v1);
        SetUV(&v[1], u1, v1);
        SetUV(&v[2], u1, v0);
        SetUV(&v[3], u0, v0);
    }
}

// 0x0077ced0 RpPTankInstanceTexCoords_GlobalB_maybe_2 (index 4, rpPTANKDFLAGCNSVTX4TEXCOORDS 0x100000): the
// four constant pairs (PS3 +0xe0..+0xfc) in order.
void InstanceTexGlobal4(InstanceData* inst, int32_t count, const RpPTankData* tank) {
    for (int32_t i = 0; i < count; ++i) {
        QuadVertex* v = &inst->vertices[i * 4];
        for (int q = 0; q < 4; ++q)
            SetUV(&v[q], WordF(tank->texCoordsE0[2 * q]), WordF(tank->texCoordsE0[2 * q + 1]));
    }
}

void InstanceTexCoords(int32_t index, InstanceData* inst, int32_t count, const RpPTankData* tank) {
    switch (index) {
        case 1: InstanceTexPerParticle2(inst, count, tank); break;
        case 2: InstanceTexPerParticle4(inst, count, tank); break;
        case 3: InstanceTexGlobal2(inst, count, tank); break;
        case 4: InstanceTexGlobal4(inst, count, tank); break;
        default: break;
    }
}

// ---- colour instancers (table 0xb16b38): raw RwRGBA words -------------------------------------------

PTANK_INLINE void SetColor(QuadVertex* v, const uint8_t* rgba) { std::memcpy(v->color, rgba, 4); }

// 0x0077c9d0 RpPTankInstanceColorB_PerParticle_maybe (index 1, rpPTANKDFLAGCOLOR 0x2): the particle's
// colour on its 4 vertices.
void InstanceColorPerParticle(InstanceData* inst, int32_t count, const RpPTankData* tank) {
    const int32_t stride = tank->stride[kArrColor];
    for (int32_t i = 0; i < count; ++i) {
        const uint8_t* c = Elem(tank, kArrColor, i, stride);
        for (int q = 0; q < 4; ++q) SetColor(&inst->vertices[i * 4 + q], c);
    }
}

// 0x0077ca78 RpPTankInstanceVec4B_PerParticle_maybe (index 2, rpPTANKDFLAGVTXCOLOR 0x40): the particle's
// four vertex colours.
void InstanceColorPerParticleVertex(InstanceData* inst, int32_t count, const RpPTankData* tank) {
    const int32_t stride = tank->stride[kArrVtxColor];
    for (int32_t i = 0; i < count; ++i) {
        const uint8_t* c = Elem(tank, kArrVtxColor, i, stride);
        for (int q = 0; q < 4; ++q) SetColor(&inst->vertices[i * 4 + q], c + 4 * q);
    }
}

// 0x0077cb40 RpPTankInstanceColorB_GlobalPerCorner_maybe (index 3, rpPTANKDFLAGCNSVTXCOLOR 0x40000): the
// constant vertex colours (PS3 +0xd0).
void InstanceColorGlobalVertex(InstanceData* inst, int32_t count, const RpPTankData* tank) {
    for (int32_t i = 0; i < count; ++i)
        for (int q = 0; q < 4; ++q) SetColor(&inst->vertices[i * 4 + q], tank->vtxColorD0 + 4 * q);
}

// 0x0077cbe0 RpPTankInstanceColor_Global_maybe_2 (index 4): the constant colour (PS3 +0xcc). Never reached:
// index 4 means none of 0x40042, and then the geometry is not prelit and no colours are instanced.
void InstanceColorGlobal(InstanceData* inst, int32_t count, const RpPTankData* tank) {
    for (int32_t i = 0; i < count; ++i)
        for (int q = 0; q < 4; ++q) SetColor(&inst->vertices[i * 4 + q], tank->colorCC);
}

void InstanceColors(int32_t index, InstanceData* inst, int32_t count, const RpPTankData* tank) {
    switch (index) {
        case 1: InstanceColorPerParticle(inst, count, tank); break;
        case 2: InstanceColorPerParticleVertex(inst, count, tank); break;
        case 3: InstanceColorGlobalVertex(inst, count, tank); break;
        case 4: InstanceColorGlobal(inst, count, tank); break;
        default: break;
    }
}

// 0x0077d070 RpPTankInstanceTexCoordsGlobalA_ColorPerParticle_Vmx_maybe: tex index 3 and colour index 1 in
// one VMX pass (16-byte stores of (u, v, colour, colour) at the tex coords: the colour lands at +0x18, its
// place in a textured vertex). The constant pairs as index 3, the colour words at a fixed stride 4. Groups
// of 4 as the position VMX instancers.
void InstanceTexGlobal2ColorPerParticleVmx(InstanceData* inst, int32_t count, const RpPTankData* tank) {
    const float u0 = WordF(tank->texCoordsE0[0]);
    const float v0 = WordF(tank->texCoordsE0[1]);
    const float u1 = WordF(tank->texCoordsE0[2]);
    const float v1 = WordF(tank->texCoordsE0[3]);
    for (int32_t i = 0; i < count; ++i) {
        const uint8_t* c = Elem(tank, kArrColor, i, 4);
        QuadVertex* v = &inst->vertices[i * 4];
        SetUV(&v[0], u0, v1);
        SetUV(&v[1], u1, v1);
        SetUV(&v[2], u1, v0);
        SetUV(&v[3], u0, v0);
        for (int q = 0; q < 4; ++q) SetColor(&v[q], c);
    }
}

// ---- normal instancer (PTank +0x34) -------------------------------------------------------------------

// 0x00777fa0 RpPTankInstanceNormals_PerParticle_maybe (rpPTANKDFLAGNORMAL 0x10): the particle's normal (PS3
// +0x64 array, its stride) on its 4 vertices.
void InstanceNormalsPerParticle(InstanceData* inst, int32_t count, const RpPTankData* tank) {
    const int32_t stride = tank->stride[kArrNormal];
    for (int32_t i = 0; i < count; ++i) {
        const uint8_t* n = Elem(tank, kArrNormal, i, stride);
        for (int q = 0; q < 4; ++q) {
            QuadVertex& v = inst->vertices[i * 4 + q];
            v.normal[0] = LoadF(n);
            v.normal[2] = LoadF(n + 8);
            v.normal[1] = LoadF(n + 4);
        }
    }
}

// ---- the setup callback and the prepare ---------------------------------------------------------------

// The PTank's geometry flags as the PS3 keeps them: 0x77b500 makes the quad geometry with 0x06
// (positions, textured) or 0x76 (with normals 0x10: + light 0x20, modulate 0x40), | 8 (prelit) when the
// PTank has colours (0x40042); 0x77b6b8 then keeps flag 4 equal to "the material has a texture".
struct GeometryFlags {
    bool textured;
    bool prelit;
    bool normals;
    bool lit;  // the draw's lighting state after the lighting callback (the driver's GL_LIGHTING cache)
};
GeometryFlags PTankGeometryFlags(const RpAtomic* atomic) {
    const uint32_t flags = atomic->geometry->flags;
    GeometryFlags g;
    g.textured = (flags & rpGEOMETRYTEXTURED) != 0;
    g.prelit = (flags & rpGEOMETRYPRELIT) != 0;
    g.normals = (flags & rpGEOMETRYNORMALS) != 0;
    g.lit = false;
    return g;
}

// 0x0077b6b8 RwPSGLPTank_PrepareQuadVertexBuffer_maybe (PTank +0x24, installed by 0x77b500): the attributes
// from the geometry flags, the billboard axes from the current camera's frame LTM (RWSRCGLOBAL(curCamera)
// -> object.parent; natively the camera of RwCameraBeginUpdate, RwDevice_GetCamera), and the vertex buffer
// (the PS3 maps stride * (count * 4 + 16) bytes of the ring buffer under its lightweight mutex; natively
// count * 4 vertices, zeroed: the PS3's unwritten attributes are the buffer's stale bytes). dotd perf: `written` is the
// number of particles the instancers will make, with every attribute the draw reads; then only the vertices past them
// are zeroed (the draw reads no other attribute of a vertex: the stale values of the others never reach a vertex).
void PrepareQuadVertexBuffer(InstanceData* inst, RpAtomic* atomic, const RpPTankData* tank, int32_t count,
                             int32_t written) {
    // The geometry's texture flag (4) follows the material's texture (0x77b714..: set with one, cleared without).
    RpGeometry* geometry = atomic->geometry;
    if (geometry->matList.materials[0]->texture != nullptr) {
        geometry->flags |= rpGEOMETRYTEXTURED;
    } else {
        geometry->flags &= ~static_cast<RwUInt32>(rpGEOMETRYTEXTURED);
    }
    const GeometryFlags g = PTankGeometryFlags(atomic);
    inst->positions = 1;
    inst->texCoords = g.textured ? 1 : 0;
    inst->colors = g.prelit ? 1 : 0;
    inst->normals = g.normals ? 1 : 0;

    RwMatrix identity{};
    identity.right.x = 1.0f;
    identity.up.y = 1.0f;
    identity.at.z = 1.0f;
    const RwMatrix* ltm = &identity;
    RwCamera* camera = RwDevice_GetCamera();
    // Native: no camera outside a camera update (headless tests); the PS3 always renders inside one.
    if (camera != nullptr && RwCameraGetFrame(camera) != nullptr) ltm = RwFrameGetLTM(RwCameraGetFrame(camera));

    const uint32_t flags = tank->dataFlags;  // PS3 +0xa8 (the instancers' +0x58)
    if ((flags & 0x8000u) != 0) {
        // rpPTANKDFLAGCNSMATRIX: the constant matrix's right and up (PS3 +0x100 / +0x110).
        for (int k = 0; k < 3; ++k) {
            inst->right[k] = WordF(tank->matrix100[k]);
            inst->up[k] = WordF(tank->matrix100[4 + k]);
        }
    } else if ((flags & 0x20000u) != 0) {
        // rpPTANKDFLAGCNS2DROTATE: the camera axes rotated by the constant angle (PS3 +0xc8): _Sin in
        // double, each result rounded to float (frsp).
        const double angle = static_cast<double>(WordF(tank->renderC8));
        const float s = ppc::frsp(crt::Sin(angle, 0));
        const float c = ppc::frsp(crt::Sin(angle, 1));
        const float ns = -s;
        const float r[3] = {-ltm->right.x, -ltm->right.y, -ltm->right.z};
        const float u[3] = {ltm->up.x, ltm->up.y, ltm->up.z};
        for (int k = 0; k < 3; ++k) {
            inst->up[k] = Fmadds(r[k], s, u[k] * c);
            inst->right[k] = Fmadds(r[k], c, u[k] * ns);
        }
    } else {
        // The camera's axes: right negated (RW's camera x points to the screen's left), up as it is.
        inst->right[0] = -ltm->right.x;
        inst->right[1] = -ltm->right.y;
        inst->right[2] = -ltm->right.z;
        inst->up[0] = ltm->up.x;
        inst->up[1] = ltm->up.y;
        inst->up[2] = ltm->up.z;
    }

    const size_t total = static_cast<size_t>(count) * 4;
    const size_t made = static_cast<size_t>(written) * 4;
    g_quadVertices.resize(total);  // value-initialises (zeroes) any new vertices
    if (made < total) std::memset(g_quadVertices.data() + made, 0, (total - made) * sizeof(QuadVertex));
    inst->vertices = g_quadVertices.data();
}

// 0x0008bb78 PTank_InstanceAtomic_maybe (the PTank's prepare callback +0x1c; args atomic, PTank + 0x50,
// count, the changed flags +0x40): after a constant changed (0x1e8000: constant matrix, 2D rotation,
// vertex colours, 2 or 4 tex coords) every particle up to the capacity is instanced; then the setup
// callback, the position instancer, the tex coord instancer (with tex index 3 and colour index 1 the
// combined 0x77d070 does both), the colour and normal instancers, and the unlock callback (+0x38: 0 on the
// PS3, see the top).
void PTankInstanceAtomic(RpAtomic* atomic, RpPTankData* tank, int32_t count, uint32_t changedFlags) {
    if ((changedFlags & 0x1e8000u) != 0) count = static_cast<int32_t>(tank->maxParticles);
    // Native: the arrays hold maxParticles + 4 entries; the PS3 has no guard for a count beyond them.
    const int32_t capacity = static_cast<int32_t>(tank->maxParticles) + 4;
    if (count > capacity) count = capacity;
    if (count < 0) count = 0;
    // The draw reads numPrt * 4 vertices: keep that many (zeroed past the instanced ones).
    const int32_t buffer = static_cast<int32_t>(tank->numPrt) > count ? static_cast<int32_t>(tank->numPrt) : count;

    const InstanceFormat format = SetupInstanceFormat(tank->dataFlags);
    // The particles below count get every attribute the draw reads from the instancers (positions always; tex coords when
    // the geometry is textured, unless no tex coord instancer is selected; colours when prelit, an instancer always is;
    // normals with the geometry's normal flag when the normal instancer is selected), so only the vertices past them need
    // the zeroes; else all are zeroed. The geometry flags are those PrepareQuadVertexBuffer leaves (texture flag = the
    // material has a texture).
    const RpGeometry* geometry = atomic->geometry;
    const bool textured = geometry->matList.materials[0]->texture != nullptr;
    const bool normals = (geometry->flags & rpGEOMETRYNORMALS) != 0;
    const bool complete = !(textured && format.texCoords == 0) && !(normals && !format.normals);
    InstanceData inst{};
    PrepareQuadVertexBuffer(&inst, atomic, tank, buffer, complete ? count : 0);  // PTank +0x24
    if (format.position != 0 && inst.positions != 0) InstancePositions(format.position, &inst, count, tank);
    bool colorsDone = false;
    if (format.texCoords == 3) {
        if (inst.texCoords != 0) {
            if (format.color == 1 && inst.colors != 0) {
                InstanceTexGlobal2ColorPerParticleVmx(&inst, count, tank);
                colorsDone = true;
            } else {
                InstanceTexCoords(format.texCoords, &inst, count, tank);
            }
        }
    } else if (format.texCoords != 0 && inst.texCoords != 0) {
        InstanceTexCoords(format.texCoords, &inst, count, tank);
    }
    if (!colorsDone && format.color != 0 && inst.colors != 0) InstanceColors(format.color, &inst, count, tank);
    if (format.normals && inst.normals != 0) InstanceNormalsPerParticle(&inst, count, tank);  // +0x34
    // +0x38 unlock: 0 (0x77b500).
}

// ---- the draw ---------------------------------------------------------------------------------------

// The quads' triangle indices (0, 1, 2) (0, 2, 3) from vertex 4k, the same for every chunk: dotd perf, made once for the
// largest chunk so far and kept (g_imIndices holds g_quadIndexCount quads).
thread_local size_t g_quadIndexCount = 0;
void EnsureQuadIndices(int32_t quads) {
    if (static_cast<size_t>(quads) <= g_quadIndexCount) return;
    g_imIndices.resize(static_cast<size_t>(quads) * 6);
    for (int32_t k = static_cast<int32_t>(g_quadIndexCount); k < quads; ++k) {
        RwImVertexIndex* idx = &g_imIndices[static_cast<size_t>(k) * 6];
        const RwImVertexIndex b = static_cast<RwImVertexIndex>(k * 4);
        idx[0] = b;
        idx[1] = b + 1;
        idx[2] = b + 2;
        idx[3] = b;
        idx[4] = b + 2;
        idx[5] = b + 3;
    }
    g_quadIndexCount = static_cast<size_t>(quads);
}

// The unlit vertices of a chunk (dotd perf: the attribute choices taken out of the loop). Normals with the geometry's
// normal flag (glNormalPointer), the colour array when prelit (glColorPointer(vertex alpha ? 4 : 3, GL_UNSIGNED_BYTE):
// with 3 components alpha is 1.0), else glColor4ub of the constant colour (PS3 +0xcc), the tex coords when textured.
template <bool kNormals, bool kPrelit, bool kTextured>
void ConvertUnlitVertices(RwIm3DVertex* out, const QuadVertex* in, int32_t numVerts, bool vertexAlpha,
                          const RpPTankData* tank) {
    const uint8_t* cc = tank->colorCC;
    for (int32_t i = 0; i < numVerts; ++i) {
        const QuadVertex& q = in[i];
        RwIm3DVertex& v = out[i];
        v.objVertex.x = q.pos[0];
        v.objVertex.y = q.pos[1];
        v.objVertex.z = q.pos[2];
        v.objNormal.x = kNormals ? q.normal[0] : 0.0f;
        v.objNormal.y = kNormals ? q.normal[1] : 0.0f;
        v.objNormal.z = kNormals ? q.normal[2] : 0.0f;
        if (kPrelit) {
            v.color.red = q.color[0];
            v.color.green = q.color[1];
            v.color.blue = q.color[2];
            v.color.alpha = vertexAlpha ? q.color[3] : static_cast<RwUInt8>(0xff);
        } else {
            v.color.red = cc[0];
            v.color.green = cc[1];
            v.color.blue = cc[2];
            v.color.alpha = cc[3];
        }
        v.u = kTextured ? q.uv[0] : 0.0f;
        v.v = kTextured ? q.uv[1] : 0.0f;
    }
}

// One glDrawArrays(GL_QUADS, first, n): n / 4 quads from vertex first (GL drops the n % 4 left over), each
// as the triangles (0, 1, 2) and (0, 2, 3) of an indexed RwIm3D triangle list over the chunk's vertices.
void DrawQuadChunk(const QuadVertex* vertices, int32_t first, int32_t n, const RpPTankData* tank,
                   const GeometryFlags& g) {
    const int32_t quads = n / 4;
    if (quads <= 0) return;
    const int32_t numVerts = quads * 4;
    g_imVertices.resize(static_cast<size_t>(numVerts));
    EnsureQuadIndices(quads);
    const bool vertexAlpha = tank->renderB4 != 0;
    const QuadVertex* in = vertices + first;
    RwIm3DVertex* out = g_imVertices.data();
    if (g.lit) {
        for (int32_t i = 0; i < numVerts; ++i) {
            const QuadVertex& q = in[i];
            RwIm3DVertex& v = out[i];
            v.objVertex.x = q.pos[0];
            v.objVertex.y = q.pos[1];
            v.objVertex.z = q.pos[2];
            // glNormalPointer when the geometry has normals (flag 0x10).
            v.objNormal.x = g.normals ? q.normal[0] : 0.0f;
            v.objNormal.y = g.normals ? q.normal[1] : 0.0f;
            v.objNormal.z = g.normals ? q.normal[2] : 0.0f;
            // Lighting on: GL's lit colour of the vertex (the colour array, when prelit, feeds the colour material;
            // without a normal array GL's current normal (0, 0, 1)).
            const uint8_t color[4] = {q.color[0], q.color[1], q.color[2], vertexAlpha ? q.color[3] : static_cast<uint8_t>(0xff)};
            const float defaultNormal[3] = {0.0f, 0.0f, 1.0f};
            uint8_t lit[4];
            dotd::gfx::FixedLightVertex(q.pos, g.normals ? q.normal : defaultNormal, g.prelit ? color : nullptr, lit);
            v.color.red = lit[0];
            v.color.green = lit[1];
            v.color.blue = lit[2];
            v.color.alpha = lit[3];
            v.u = g.textured ? q.uv[0] : 0.0f;
            v.v = g.textured ? q.uv[1] : 0.0f;
        }
    } else {
        const int key = (g.normals ? 4 : 0) | (g.prelit ? 2 : 0) | (g.textured ? 1 : 0);
        switch (key) {
            case 0: ConvertUnlitVertices<false, false, false>(out, in, numVerts, vertexAlpha, tank); break;
            case 1: ConvertUnlitVertices<false, false, true>(out, in, numVerts, vertexAlpha, tank); break;
            case 2: ConvertUnlitVertices<false, true, false>(out, in, numVerts, vertexAlpha, tank); break;
            case 3: ConvertUnlitVertices<false, true, true>(out, in, numVerts, vertexAlpha, tank); break;
            case 4: ConvertUnlitVertices<true, false, false>(out, in, numVerts, vertexAlpha, tank); break;
            case 5: ConvertUnlitVertices<true, false, true>(out, in, numVerts, vertexAlpha, tank); break;
            case 6: ConvertUnlitVertices<true, true, false>(out, in, numVerts, vertexAlpha, tank); break;
            default: ConvertUnlitVertices<true, true, true>(out, in, numVerts, vertexAlpha, tank); break;
        }
    }
    const RwUInt32 flags = g.textured ? static_cast<RwUInt32>(rwIM3D_VERTEXUV) : 0u;
    if (RwIm3DTransform(g_imVertices.data(), static_cast<RwUInt32>(numVerts), nullptr, flags) != nullptr) {
        RwIm3DRenderIndexedPrimitive(rwPRIMTYPETRILIST, g_imIndices.data(), quads * 6);
        RwIm3DEnd();
    }
}

void* StateWord(RwInt32 w) { return reinterpret_cast<void*>(static_cast<intptr_t>(w)); }

// 0x0077adf8 _rpPTankDefaultLightingCB_maybe: the PTank's default shader hook, RwPSGL_AtomicLightingCallback of the atomic.
void DefaultLightingCB(void* /*meshData*/, RpAtomic* atomic) { RwPSGL_AtomicLightingCallback(atomic); }

// 0x00c4d708 the PTank's shader hook (RpPTank_SetShaderBindCallBack_maybe 0x77add8; the shader manager replaces the default
// with PreparePSGLAtomicMeshShaders, which binds the programs of the PTank's mesh pass state).
RpPTankShaderBindCallBack g_shaderBindCallBack = &DefaultLightingCB;

// 0x0077aea8 DrawPSGLParticleQuadBatch (the PTank's draw callback +0x20; args atomic, PTank + 0x50, count):
// the vertex layout from the geometry flags; the PTank's shader hook (0xc4d708) with (0, atomic) and
// RwPSGL_AtomicLightingCallback_maybe (lighting off without the geometry's light flag); with lighting on the
// material's GL colours (RwPSGL_ApplyMaterialLighting_maybe), without lighting the colour material off and without
// colours glColor4ub(+0xcc); the material's texture
// (raster, U and V addressing, filter) or none; with vertex alpha (+0xb4) vertex alpha on and the PTank's blend modes
// (+0xac / +0xb0) over the saved ones, else vertex alpha off; glDrawArrays(GL_QUADS) of count * 4
// vertices in chunks of 0xfffb; the ring offset advanced; the blend modes restored. Z test/write, culling
// and alpha test are left as they are. Returns 1 always.
// BUG(original): the chunks of 0xfffb vertices are not whole quads (0xfffb = 4 * 16382 + 3), so above 16382
// particles the 3 vertices left of each chunk are dropped and the next chunk's quads are misaligned.
int32_t DrawPSGLParticleQuadBatch(RpAtomic* atomic, RpPTankData* tank, int32_t count) {
    GeometryFlags g = PTankGeometryFlags(atomic);
    const RpMaterial* material = atomic->geometry->matList.materials[0];
    // The PTank's shader hook (TOC -0x2f74 -> 0xc4d708: the default 0x77adf8 _rpPTankDefaultLightingCB_maybe, or with the
    // shader pipelines PreparePSGLAtomicMeshShaders, which binds the programs the quads draw with) with (0, atomic);
    // then the draw calls the lighting callback itself.
    g_shaderBindCallBack(nullptr, atomic);
    RwPSGL_AtomicLightingCallback(atomic);
    if (!RwPSGL_LightingEnabled()) {
        RwPSGL_DisableColorMaterial();
        // glColor4ub(+0xcc) without colours: DrawQuadChunk gives the vertices the constant colour.
    } else {
        RwPSGL_ApplyMaterialLighting(material, atomic->geometry->flags);
        g.lit = true;
    }
    if (!g.textured) {
        RwRenderStateSet(rwRENDERSTATETEXTURERASTER, nullptr);  // RwPSGL_SetTexture_maybe(0)
    } else {
        // RwPSGL_SetTexture_maybe(material->texture) 0x73fbe0: the raster, then U, V (filterAddressing bits 8-11,
        // 12-15) and the filter (bits 0-7); then, when the device has anisotropic filtering, GL_TEXTURE_MAX_ANISOTROPY
        // from the texture's RpAnisot plugin byte (1 without the plugin) clamped to the device's maximum, only when it
        // differs from the bound unit's: dotd's textures have no RpAnisot data, so it is 1, GL's default.
        const RwTexture* texture = material->texture;
        const uint32_t fa = texture->filterAddressing;
        RwRenderStateSet(rwRENDERSTATETEXTURERASTER, texture->raster);
        RwRenderStateSet(rwRENDERSTATETEXTUREADDRESSU, StateWord(static_cast<RwInt32>((fa >> 8) & 0xf)));
        RwRenderStateSet(rwRENDERSTATETEXTUREADDRESSV, StateWord(static_cast<RwInt32>((fa >> 12) & 0xf)));
        RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, StateWord(static_cast<RwInt32>(fa & 0xff)));
    }
    RwInt32 savedSrc = 0;
    RwInt32 savedDst = 0;
    const bool vertexAlpha = tank->renderB4 != 0;
    if (vertexAlpha) {
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, StateWord(1));
        RwRenderStateGet(rwRENDERSTATESRCBLEND, &savedSrc);
        RwRenderStateSet(rwRENDERSTATESRCBLEND, StateWord(static_cast<RwInt32>(tank->renderAC)));
        RwRenderStateGet(rwRENDERSTATEDESTBLEND, &savedDst);
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, StateWord(static_cast<RwInt32>(tank->renderB0)));
    } else {
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, StateWord(0));
    }

    int32_t numVerts = static_cast<int32_t>(static_cast<uint32_t>(count) << 2);  // slwi 2
    const int32_t available = static_cast<int32_t>(g_quadVertices.size());
    if (numVerts > available) numVerts = available;  // native: the prepare made numPrt * 4 vertices
    int32_t first = 0;
    if (numVerts > 0xfffb) {
        do {
            DrawQuadChunk(g_quadVertices.data(), first, 0xfffb, tank, g);
            numVerts -= 0xfffb;
            first += 0xfffb;
        } while (numVerts > 0xfffb);
    }
    DrawQuadChunk(g_quadVertices.data(), first, numVerts, tank, g);

    if (vertexAlpha) {
        RwRenderStateSet(rwRENDERSTATESRCBLEND, StateWord(savedSrc));
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, StateWord(savedDst));
    }
    // dotd: the quads went through RwIm3D with the hook's programs (RwDevice_SetIm3DShaderBindOverride); the next Im3D
    // draws bind through the immediate pipeline's callback again, as on the PS3.
    RwDevice_SetIm3DShaderBindOverride(nullptr);
    return 1;
}

}  // namespace

void RpPTankSetShaderBindCallBack(RpPTankShaderBindCallBack callback) { g_shaderBindCallBack = callback; }

// 0x007799a0 RW_RenderParticleTankAtomic: nothing without particles (count < 1, signed); the prepare
// callback with the changed flags, which are then cleared; the draw callback (with the count read again);
// when it returns 1 (always) the saved default render (RpAtomicCreate's, on the empty quad geometry).
RpAtomic* RpPTankAtomicRender(RpAtomic* atomic) {
    RpPTankData* tank = atomic->ptank;
    if (tank == nullptr) return atomic;  // native: the callback is only installed on PTank atomics
    if (static_cast<int32_t>(tank->numPrt) < 1) return atomic;
    PTankInstanceAtomic(atomic, tank, static_cast<int32_t>(tank->numPrt), tank->flags40);  // +0x1c
    tank->flags40 = 0;
    if (DrawPSGLParticleQuadBatch(atomic, tank, static_cast<int32_t>(tank->numPrt)) != 1) return atomic;  // +0x20
    if (tank->defaultRenderCallBack != nullptr) tank->defaultRenderCallBack(atomic);  // +0x10 the saved render
    return atomic;
}
