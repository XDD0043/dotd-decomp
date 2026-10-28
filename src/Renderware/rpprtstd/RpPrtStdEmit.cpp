// RpPrtStdEmit.cpp - the standard emitter's emit callback (emitter class callback slot 0), ported from the PS3
// library code (TOC 0xc25974, 0x732c58-0x734184).
//
//   [x] 0x732c58  RpPrtStdEmitterStd_Emit_maybe
//
// How many particles: n = fctiwz(rand(-1..1) * (float)emtPrtEmitBias) + emtPrtEmit, clamped to the PTank's
// room (maxPrt - emitter->prtActive). Every pass appends n particles to the active batch (or a new batch);
// while the standard property's word +0xb0 is set, passes repeat once per emit gap (max(emtEmitGap, 0.001))
// that fits in currTime - emtPrevEmitTime, each pass's particles moved further along their velocity by
// pass * gap.
//
// Random numbers: the emitter's LCG (rpprtstd::NextSeed); a value u as fcfid + frsp (the exact (double)u
// rounded to float) times 2^-32 (TOC 0x2f800000), mostly doubled minus 1 (-1..1).
//
// Particle layouts (PS3 byte layouts, floats unless noted), as this callback writes them:
//   standard (0, 0x10): +0x00 flag (not written here), +0x04 currTime = 0, +0x08 endTime (the life:
//       prtLife + r * prtLifeBias), +0x0c invEndTime (1 / endTime, 0 when endTime is 0). Written at the
//       particle's start: the callback assumes the standard property is at offset 0 (it never reads
//       g_offsets.prtStd).
//   position (1, 0xc): RwV3d.
//   velocity (6, 0xc): RwV3d, the normalised (prtInitDir + r * prtInitDirBias) direction (through the LTM's
//       rotation when there is one) times (prtInitVel + r * prtInitVelBias).
//   colour (2, 0x20): +0x00 start colour RwRGBAReal (r, g, b, a), +0x10 delta colour (end - start).
//   size (5, 0x20): +0x00 start size RwV2d, +0x08 delta size (end - start), +0x10 current size (= start);
//       +0x18..0x1f not written.
//   tex coords (3, 0x20): +0x00 start UV0, +0x08 start UV1, +0x10 delta UV0, +0x18 delta UV1 (RwTexCoords).
//   2D rotate (4, 8): +0x00 start angle, +0x04 delta angle (end - start), both wrapped into [-pi, pi].
//   matrix (7, 0x40): an RwMatrix set to the identity, flags |= 0x20003 (rwMATRIXTYPEORTHONORMAL |
//       rwMATRIXINTERNALIDENTITY).
//
// Emitter property layouts read (floats): colour (2): start RGBA +0x00, start bias +0x10, end +0x20, end bias
// +0x30 (the start colour = r * start + (1 - r) * startBias with r in -1..1; the end colour = t * end +
// (1 - t) * endBias with t in 0..1). Size (5): start, start bias, end, end bias (RwV2d each). Tex coords (3):
// start UV0, start UV0 bias, end UV0, end UV0 bias, start UV1, start UV1 bias, end UV1, end UV1 bias. 2D
// rotate (4): start, start bias, end, end bias. Matrix (8): +0x40 at, +0x4c at bias, +0x58 up, +0x64 up bias
// (RwV3d each; only for the PTank matrix array).
#include <cstdint>
#include <cstring>

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rpprtstd/RpPrtStdRuntime.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "crt/ppc_ops.h"

namespace rpprtstd {

namespace {

constexpr float kMinEmitGap = 1.0e-3f;        // TOC -0x3698 0x3a83126f
constexpr float kTwoPowMinus32 = 0x1p-32f;    // TOC -0x36cc 0x2f800000
constexpr float kOne = 1.0f;                  // TOC -0x36c8
constexpr float kZero = 0.0f;                 // TOC -0x3694
constexpr float kPi = 0x1.921fb6p+1f;         // TOC -0x36d8 0x40490fdb
constexpr float kMinusPi = -0x1.921fb6p+1f;   // TOC -0x36d0 0xc0490fdb
constexpr float kTwoPi = 0x1.921fb6p+2f;      // TOC -0x36d4 0x40c90fdb

// u * 2^-32 (fcfid of the zero-extended word, frsp, fmuls): 0..1.
inline float Rand01(uint32_t u) { return ppc::frsp(static_cast<double>(u)) * kTwoPowMinus32; }
// (x + x) - 1 (fadds, fsubs): -1..1.
inline float RandSigned(uint32_t u) {
    const float x = Rand01(u);
    return (x + x) - kOne;
}

// The particle count of one pass from `seed` (the seed itself is not advanced: the caller keeps the result).
inline int32_t PassCount(const RpPrtStdEmitterStandard* std, uint32_t next) {
    const float bias = ppc::frsp(static_cast<double>(std->emtPrtEmitBias));  // extsw, fcfid, frsp
    return ppc::fctiwz(RandSigned(next) * bias) + std->emtPrtEmit;
}

// The angle wrap of the 2D rotation (0x733794 / 0x733808, the tails at 0x733ca0 / 0x733cb8).
inline float WrapAngle(float x) {
    if (x > kPi) {
        x = x - kTwoPi;
        if (x >= kMinusPi) return x;
        return x + kTwoPi;
    }
    if (x >= kMinusPi) return x;
    return x + kTwoPi;  // also NaN
}

inline float* FloatsAt(uint8_t* base, int32_t offset) { return reinterpret_cast<float*>(base + offset); }
inline void StoreWord(float* slot, uint32_t word) { std::memcpy(slot, &word, 4); }
inline uint32_t LoadWord(const float* slot) {
    uint32_t word;
    std::memcpy(&word, slot, 4);
    return word;
}

}  // namespace

// 0x00732c58 RpPrtStdEmitterStd_Emit_maybe
RpPrtStdEmitter* StdEmit(RpAtomic* /*atomic*/, RpPrtStdEmitter* emitter, void* /*data*/) {
    uint8_t* const base = reinterpret_cast<uint8_t*>(emitter);
    RpPrtStdEmitterStandard* const stdProp =
        reinterpret_cast<RpPrtStdEmitterStandard*>(base + g_offsets.emtStd);  // no check in the original
    const float* const emtColor = g_offsets.emtPrtColor >= 0 ? FloatsAt(base, g_offsets.emtPrtColor) : nullptr;
    const float* const emtTex =
        g_offsets.emtPrtTexCoords >= 0 ? FloatsAt(base, g_offsets.emtPrtTexCoords) : nullptr;
    RpPrtStdEmitterPTank* const ptank =
        g_offsets.emtPTank >= 0 ? reinterpret_cast<RpPrtStdEmitterPTank*>(base + g_offsets.emtPTank) : nullptr;
    const float* const emtMatrix = g_offsets.emtPrtMatrix >= 0 ? FloatsAt(base, g_offsets.emtPrtMatrix) : nullptr;
    const float* const emtSize = g_offsets.emtPrtSize >= 0 ? FloatsAt(base, g_offsets.emtPrtSize) : nullptr;
    const float* const emtRotate =
        g_offsets.emtPrt2DRotate >= 0 ? FloatsAt(base, g_offsets.emtPrt2DRotate) : nullptr;

    float gap = stdProp->emtEmitGap;
    if (!(gap >= kMinEmitGap)) gap = kMinEmitGap;
    if (stdProp->currTime < stdProp->emtEmitTime) return emitter;

    // The first pass's count once more (the same seed), only to decide the batch's newPrt at the end: the
    // active batch's particle count when it gets particles, else 0.
    int32_t savedNewPrt = 0;
    {
        int32_t count = PassCount(stdProp, static_cast<uint32_t>(stdProp->seed) * 0xbb38435u + 0x3619636bu);
        if (ptank != nullptr && count + emitter->prtActive > ptank->maxPrt) count = ptank->maxPrt - emitter->prtActive;
        RpPrtStdParticleBatch* const active = static_cast<RpPrtStdParticleBatch*>(emitter->activeBatch);
        savedNewPrt = (count > 0 && active != nullptr) ? active->numPrt : 0;
    }

    // State the original keeps in callee-saved registers and stack slots across particles and passes.
    // BUG(original): the world position (stack 0x88) is only computed inside the velocity branch and only
    // written by RwV3dTransformPoint when the standard property has an LTM; otherwise the position property /
    // PTank position get the previous particle's (or uninitialised stack) values. The colour (f17..f20) and
    // tex coords (f21..f24) the PTank arrays get are likewise stale (the caller's registers at first) when the
    // emitter has no colour / tex coords property. Zero here where the original reads garbage.
    RwV3d pos = {0.0f, 0.0f, 0.0f};
    float colR = 0.0f, colG = 0.0f, colB = 0.0f, colA = 0.0f;
    float texU0 = 0.0f, texV0 = 0.0f, texU1 = 0.0f, texV1 = 0.0f;
    uint8_t* posOut = nullptr;   // also the matrix array (the original shares the slot)
    int32_t posStride = 0;
    uint8_t* colOut = nullptr;
    int32_t colStride = 0;
    uint8_t* sizeOut = nullptr;
    int32_t sizeStride = 0;
    uint8_t* rotOut = nullptr;
    int32_t rotStride = 0;
    uint8_t* texOut = nullptr;
    int32_t texStride = 0;

    float pass = 0.0f;   // f15: the pass index, the velocity offset's time factor
    float elapsed = 0.0f;  // stack 0xac: the passes' gaps so far
    RpPrtStdEmitter* result = nullptr;  // r29: null until a pass completed
    RpPrtStdParticleBatch* batch = nullptr;

    bool more = !(stdProp->currTime - stdProp->emtPrevEmitTime <= elapsed);
    while (more) {
        int32_t seed = stdProp->seed;
        int32_t count = PassCount(stdProp, NextSeed(&seed));
        if (ptank != nullptr && count + emitter->prtActive > ptank->maxPrt) count = ptank->maxPrt - emitter->prtActive;
        if (count <= 0) return emitter;

        batch = static_cast<RpPrtStdParticleBatch*>(emitter->activeBatch);
        int32_t emitCount = count;
        if (batch == nullptr || count + batch->numPrt > batch->maxPrt) {
            batch = EmitterNewParticleBatch(emitter);
            if (batch == nullptr) {
                // BUG(original): the next try uses the same seed and time; it retries for as long as the
                // allocation fails and time remains.
                more = !(stdProp->currTime - stdProp->emtPrevEmitTime <= elapsed);
                continue;
            }
            const int32_t maxPrt = batch->maxPrt;
            batch->numPrt = 0;
            batch->newPrt = 0;
            if (count > maxPrt) {
                if (maxPrt <= 0) return emitter;
                emitCount = maxPrt;
            }
        }

        // The PTank's output pointers, in data-flag order. BUG(original): 0x10 (normals) and 0x40 (vertex
        // colours) take no index, so the arrays after them would be misread; the matrix array (0x8) shares
        // the position pointer.
        if (ptank != nullptr) {
            const uint32_t flags = ptank->dataFlags;
            int32_t index = 0;
            posOut = nullptr;
            posStride = 0;
            if ((flags & 0x1u) != 0) {
                posOut = ptank->dataOutPtrs[0];
                posStride = ptank->dataStride[0];
                index = 1;
            }
            colOut = nullptr;
            colStride = 0;
            if ((flags & 0x2u) != 0) {
                colOut = ptank->dataOutPtrs[index];
                colStride = ptank->dataStride[index];
                ++index;
            }
            sizeOut = nullptr;
            sizeStride = 0;
            if ((flags & 0x4u) != 0) {
                sizeOut = ptank->dataOutPtrs[index];
                sizeStride = ptank->dataStride[index];
                ++index;
            }
            if ((flags & 0x8u) != 0) {
                posOut = ptank->dataOutPtrs[index];
                posStride = ptank->dataStride[index];
                ++index;
            }
            rotOut = nullptr;
            rotStride = 0;
            if ((flags & 0x20u) != 0) {
                rotOut = ptank->dataOutPtrs[index];
                rotStride = ptank->dataStride[index];
                ++index;
            }
            texOut = nullptr;
            texStride = 0;
            if ((flags & 0x80u) != 0) {
                texOut = ptank->dataOutPtrs[index];
                texStride = ptank->dataStride[index];
            }
        }

        const int32_t objSize = emitter->prtClass->objSize;
        const RwMatrix* const ltm = stdProp->ltm;
        uint8_t* particle = RpPrtStdBatchParticles(batch) + objSize * batch->numPrt;
        for (int32_t i = 0;;) {
            float* const prtStd = reinterpret_cast<float*>(particle);
            prtStd[1] = kZero;
            const float life = ppc::fmadds(RandSigned(NextSeed(&seed)), stdProp->prtLifeBias, stdProp->prtLife);
            prtStd[2] = life;
            prtStd[3] = life == kZero ? kZero : kOne / life;

            if (g_offsets.prtVelocity >= 0) {
                float* const vel = FloatsAt(particle, g_offsets.prtVelocity);
                const float r1 = RandSigned(NextSeed(&seed));
                const float r2 = RandSigned(NextSeed(&seed));
                const float r3 = RandSigned(NextSeed(&seed));
                RwV3d dir;
                dir.x = ppc::fmadds(r1, stdProp->prtInitDirBias.x, stdProp->prtInitDir.x);
                dir.y = ppc::fmadds(r2, stdProp->prtInitDirBias.y, stdProp->prtInitDir.y);
                dir.z = ppc::fmadds(r3, stdProp->prtInitDirBias.z, stdProp->prtInitDir.z);
                RwV3dNormalize(&dir, &dir);
                if (ltm != nullptr) RwV3dTransformVector(&dir, &dir, ltm);
                const float rSpeed = RandSigned(NextSeed(&seed));
                const float r5 = RandSigned(NextSeed(&seed));
                const float r6 = RandSigned(NextSeed(&seed));
                const float r7 = RandSigned(NextSeed(&seed));
                vel[0] = dir.x * ppc::fmadds(rSpeed, stdProp->prtInitVelBias, stdProp->prtInitVel);
                vel[1] = dir.y * ppc::fmadds(rSpeed, stdProp->prtInitVelBias, stdProp->prtInitVel);
                vel[2] = dir.z * ppc::fmadds(rSpeed, stdProp->prtInitVelBias, stdProp->prtInitVel);
                RwV3d local;  // the same stack vector as the direction
                local.x = ppc::fmadds(r5, stdProp->emtSize.x, stdProp->emtPos.x);
                local.y = ppc::fmadds(r6, stdProp->emtSize.y, stdProp->emtPos.y);
                local.z = ppc::fmadds(r7, stdProp->emtSize.z, stdProp->emtPos.z);
                if (ltm != nullptr) RwV3dTransformPoint(&pos, &local, ltm);
                pos.x = ppc::fmadds(gap, pass * vel[0], pos.x);
                pos.z = ppc::fmadds(gap, pass * vel[2], pos.z);
                pos.y = ppc::fmadds(gap, pass * vel[1], pos.y);
            }

            if (g_offsets.prtPosition >= 0) {
                float* const p = FloatsAt(particle, g_offsets.prtPosition);
                p[2] = pos.z;
                p[0] = pos.x;
                p[1] = pos.y;
            }

            if (g_offsets.prtMatrix >= 0) {
                float* const m = FloatsAt(particle, g_offsets.prtMatrix);
                m[10] = kOne;
                m[5] = kOne;
                m[0] = kOne;
                m[4] = kZero;
                m[2] = kZero;
                StoreWord(&m[3], LoadWord(&m[3]) | 0x20003u);
                m[1] = kZero;
                m[9] = kZero;
                m[8] = kZero;
                m[6] = kZero;
                m[14] = kZero;
                m[13] = kZero;
                m[12] = kZero;
            }

            float sizeX;  // f27
            float sizeY;  // f26
            if (g_offsets.emtPrtSize >= 0) {
                const float r = RandSigned(NextSeed(&seed));
                sizeY = ppc::fmadds(r, emtSize[3], emtSize[1]);
                sizeX = ppc::fmadds(r, emtSize[2], emtSize[0]);
                if (g_offsets.prtSize >= 0) {
                    float* const s = FloatsAt(particle, g_offsets.prtSize);
                    const float rEnd = RandSigned(NextSeed(&seed));
                    s[0] = sizeX;
                    s[1] = sizeY;
                    s[4] = sizeX;
                    s[5] = sizeY;
                    s[3] = ppc::fmadds(rEnd, emtSize[7], emtSize[5]) - sizeY;
                    s[2] = ppc::fmadds(rEnd, emtSize[6], emtSize[4]) - sizeX;
                }
            } else {
                sizeX = stdProp->prtSize.x;
                sizeY = stdProp->prtSize.y;
            }

            if (g_offsets.emtPrtColor >= 0) {
                // The start colour's random number is the current seed again (the last one drawn: r28).
                const float r = RandSigned(static_cast<uint32_t>(seed));
                const float inv = kOne - r;
                colA = ppc::fmadds(r, emtColor[3], inv * emtColor[7]);
                colR = ppc::fmadds(r, emtColor[0], inv * emtColor[4]);
                colG = ppc::fmadds(r, emtColor[1], inv * emtColor[5]);
                colB = ppc::fmadds(r, emtColor[2], inv * emtColor[6]);
                if (g_offsets.prtColor >= 0) {
                    float* const c = FloatsAt(particle, g_offsets.prtColor);
                    const float t = Rand01(NextSeed(&seed));  // 0..1 here (not doubled)
                    c[0] = colR;
                    c[1] = colG;
                    c[2] = colB;
                    c[3] = colA;
                    const float invT = kOne - t;
                    const float wA = invT * emtColor[15];
                    const float wR = invT * emtColor[12];
                    const float wG = invT * emtColor[13];
                    const float wB = invT * emtColor[14];
                    c[7] = ppc::fmadds(t, emtColor[11], wA) - colA;
                    c[4] = ppc::fmadds(t, emtColor[8], wR) - colR;
                    c[5] = ppc::fmadds(t, emtColor[9], wG) - colG;
                    c[6] = ppc::fmadds(t, emtColor[10], wB) - colB;
                }
            }

            float rotation = kZero;  // f30
            if (g_offsets.emtPrt2DRotate >= 0) {
                rotation = WrapAngle(ppc::fmadds(RandSigned(NextSeed(&seed)), emtRotate[1], emtRotate[0]));
                if (g_offsets.prt2DRotate >= 0) {
                    float* const rot = FloatsAt(particle, g_offsets.prt2DRotate);
                    rot[0] = rotation;
                    const float end = ppc::fmadds(RandSigned(NextSeed(&seed)), emtRotate[3], emtRotate[2]);
                    // BUG(original)? f30 now holds the delta, which is also what the PTank's 2D rotation
                    // array gets below (the start angle when the particle has no 2D rotate property).
                    rotation = WrapAngle(end - rotation);
                    rot[1] = rotation;
                }
            }

            if (g_offsets.emtPrtTexCoords >= 0) {
                const float ra = RandSigned(NextSeed(&seed));
                const float rb = RandSigned(NextSeed(&seed));
                const float rc = RandSigned(NextSeed(&seed));
                const float rd = RandSigned(NextSeed(&seed));
                texU0 = ppc::fmadds(ra, emtTex[2], emtTex[0]);
                texV0 = ppc::fmadds(rb, emtTex[3], emtTex[1]);
                texU1 = ppc::fmadds(rc, emtTex[10], emtTex[8]);
                texV1 = ppc::fmadds(rd, emtTex[11], emtTex[9]);
                if (g_offsets.prtTexCoords >= 0) {
                    float* const uv = FloatsAt(particle, g_offsets.prtTexCoords);
                    const float re = RandSigned(NextSeed(&seed));
                    const float rf = RandSigned(NextSeed(&seed));
                    const float rg = RandSigned(NextSeed(&seed));
                    const float rh = RandSigned(NextSeed(&seed));
                    uv[0] = texU0;
                    uv[1] = texV0;
                    uv[2] = texU1;
                    uv[3] = texV1;
                    uv[4] = ppc::fmadds(re, emtTex[6], emtTex[4]) - texU0;
                    uv[5] = ppc::fmadds(rf, emtTex[7], emtTex[5]) - texV0;
                    uv[6] = ppc::fmadds(rg, emtTex[14], emtTex[12]) - texU1;
                    uv[7] = ppc::fmadds(rh, emtTex[15], emtTex[13]) - texV1;
                }
            }

            if (ptank != nullptr) {
                if ((ptank->emitFlags & ptank->dataFlags & 0x1u) != 0) {
                    float* const out = reinterpret_cast<float*>(posOut);
                    posOut += posStride;
                    out[2] = pos.z;
                    out[0] = pos.x;
                    out[1] = pos.y;
                }
                if ((ptank->emitFlags & ptank->dataFlags & 0x8u) != 0) {
                    // The matrix from the emitter's matrix property: at and up (each randomised and
                    // normalised), right = at x up, up = right x at, right and up scaled by the size.
                    // BUG(original): no check that the emitter has the matrix property.
                    RwV3d at;
                    const float ra = RandSigned(NextSeed(&seed));
                    const float rb = RandSigned(NextSeed(&seed));
                    const float rc = RandSigned(NextSeed(&seed));
                    at.x = ppc::fmadds(ra, emtMatrix[0x4c / 4], emtMatrix[0x40 / 4]);
                    at.y = ppc::fmadds(rb, emtMatrix[0x50 / 4], emtMatrix[0x44 / 4]);
                    at.z = ppc::fmadds(rc, emtMatrix[0x54 / 4], emtMatrix[0x48 / 4]);
                    RwV3dNormalize(&at, &at);
                    RwV3d up;
                    const float rd = RandSigned(NextSeed(&seed));
                    const float re = RandSigned(NextSeed(&seed));
                    const float rf = RandSigned(NextSeed(&seed));
                    up.x = ppc::fmadds(rd, emtMatrix[0x64 / 4], emtMatrix[0x58 / 4]);
                    up.y = ppc::fmadds(re, emtMatrix[0x68 / 4], emtMatrix[0x5c / 4]);
                    up.z = ppc::fmadds(rf, emtMatrix[0x6c / 4], emtMatrix[0x60 / 4]);
                    RwV3dNormalize(&up, &up);

                    float* const m = reinterpret_cast<float*>(posOut);
                    m[8] = at.x;
                    m[9] = at.y;
                    m[10] = at.z;
                    RwV3d right;  // stored over the up vector's stack slot
                    right.x = ppc::fmsubs(at.y, up.z, at.z * up.y);
                    m[0] = right.x;
                    right.y = ppc::fmsubs(at.z, up.x, at.x * up.z);
                    m[1] = right.y;
                    right.z = ppc::fmsubs(at.x, up.y, at.y * up.x);
                    m[2] = right.z;
                    m[4] = ppc::fmsubs(right.y, at.z, right.z * at.y);
                    m[0] = m[0] * sizeX;
                    m[5] = ppc::fmsubs(right.z, at.x, right.x * at.z);
                    m[6] = ppc::fmsubs(right.x, at.y, right.y * at.x);
                    m[1] = m[1] * sizeX;
                    m[5] = m[5] * sizeY;
                    m[4] = m[4] * sizeY;
                    m[2] = m[2] * sizeX;
                    m[6] = m[6] * sizeY;
                    const float dot = ppc::fmadds(at.z, right.z, ppc::fmadds(at.x, right.x, at.y * right.y));
                    StoreWord(&m[3], dot == kZero ? 2u : 0u);  // flags: rwMATRIXTYPEORTHOGONAL when at . right is 0
                    posOut += posStride;
                    m[14] = pos.z;
                    m[12] = pos.x;
                    m[13] = pos.y;
                }
                if ((ptank->emitFlags & ptank->dataFlags & 0x4u) != 0) {
                    float* const out = reinterpret_cast<float*>(sizeOut);
                    sizeOut += sizeStride;
                    out[1] = sizeY;
                    out[0] = sizeX;
                }
                if ((ptank->emitFlags & ptank->dataFlags & 0x2u) != 0) {
                    uint8_t* const out = colOut;
                    colOut += colStride;
                    out[0] = static_cast<uint8_t>(ppc::fctiwz(colR));
                    out[1] = static_cast<uint8_t>(ppc::fctiwz(colG));
                    out[2] = static_cast<uint8_t>(ppc::fctiwz(colB));
                    out[3] = static_cast<uint8_t>(ppc::fctiwz(colA));
                }
                if ((ptank->emitFlags & ptank->dataFlags & 0x80u) != 0) {
                    float* const out = reinterpret_cast<float*>(texOut);
                    texOut += texStride;
                    out[1] = texV0;
                    out[0] = texU0;
                    out[3] = texV1;
                    out[2] = texU1;
                }
                if ((ptank->emitFlags & ptank->dataFlags & 0x20u) != 0) {
                    float* const out = reinterpret_cast<float*>(rotOut);
                    rotOut += rotStride;
                    out[0] = rotation;
                }
            }

            ++i;
            if (i >= emitCount) break;
            particle += objSize;
        }

        // The PTank's output pointers back, in the same order.
        if (ptank != nullptr) {
            ptank->numPrt += emitCount;
            int32_t index = 0;
            if ((ptank->dataFlags & 0x1u) != 0) {
                ptank->dataOutPtrs[0] = posOut;
                index = 1;
            }
            if ((ptank->dataFlags & 0x2u) != 0) ptank->dataOutPtrs[index++] = colOut;
            if ((ptank->dataFlags & 0x4u) != 0) ptank->dataOutPtrs[index++] = sizeOut;
            if ((ptank->dataFlags & 0x8u) != 0) ptank->dataOutPtrs[index++] = posOut;
            if ((ptank->dataFlags & 0x20u) != 0) ptank->dataOutPtrs[index++] = rotOut;
            if ((ptank->dataFlags & 0x80u) != 0) ptank->dataOutPtrs[index] = texOut;
        }

        batch->newPrt = batch->numPrt;
        batch->numPrt = batch->numPrt + emitCount;
        emitter->prtActive += emitCount;
        stdProp->seed = seed;
        // BUG(original)?: the batch's newPrt is overwritten with the first count's choice (the active batch's
        // count before the emit), also when the particles went into a new batch.
        if (stdProp->unkB0 == 0) {
            batch->newPrt = savedNewPrt;
            return emitter;
        }
        pass = pass + kOne;
        elapsed = elapsed + gap;
        result = emitter;
        more = stdProp->currTime - stdProp->emtPrevEmitTime > elapsed;
    }

    if (batch != nullptr) batch->newPrt = savedNewPrt;
    return result;  // null when no pass ran (no time since the previous emit)
}

}  // namespace rpprtstd
