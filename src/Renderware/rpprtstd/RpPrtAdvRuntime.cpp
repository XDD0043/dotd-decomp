// RpPrtAdvRuntime.cpp - the running side of the advanced particle properties (RpPrtAdv): RpPrtAdv's own
// property offset cache, the point list emit, the multi colour / texcoords / size emit and the keyframe
// update of the particles, ported from the PS3 library code (TOC 0xc25974; RpPrtAdv globals at 0x00cf9e08,
// the TOC word -0x3be8 / -0x3bc0 / -0x3ce8).
//
//   [x] 0x6f00d8  RW_CacheParticlePropertyOffsets2_maybe
//   [x] 0x6f26c8  PrtStdEmitterProp1000006_Emit_maybe
//   [x] 0x6f41b0  PrtStdEmitterProp1000002_3_5_Emit_maybe
//   [x] 0x6f50e0  PrtStdParticleKeyFrames_Update_maybe
//   [x] 0x6f5df0  PrtStdParticleTexCoordKeyFrames_Update_maybe
//
// Emitter side (RpPrtAdv.cpp MultiInit; rpprtadv.h RpPrtAdvEmtPrtMultiColor / ...TexCoords / ...Size):
//   +0x00 count (numCol / numTex / numSize)
//   +0x04 list: the PS3 self pointer to the keys. Natively only 32-bit builds store it (StoreSelfPointer);
//         every reader here uses the fixed position of the keys instead (+0x14 colour and size, +0x1c
//         texcoords), which is where the create callback points it on the PS3 too.
//   +0x08 offsetTime (4), then the byte offsets of the particle-side arrays (below): colour and size
//         +0x0c start, +0x10 delta; texcoords +0x0c startUV0, +0x10 deltaUV0, +0x14 startUV1, +0x18 deltaUV1.
//   keys: colour 0x28 {time, timeBias, midCol rgba, midColBias rgba}; texcoords 0x28 {time, timeBias,
//         midUV0, midUV0Bias, midUV1, midUV1Bias}; size 0x18 {time, timeBias, midSize, midSizeBias}.
//
// Particle side (the particle properties 0x1000002 / 0x1000003 / 0x1000005; n = the emitter's count; no
// pointers, plain PS3 words and floats):
//   +0x00         int32 index: the next key to switch to (MultiEmit sets 0, KeyFramesUpdate counts up)
//   +0x04         float times[n]: key j's time times the particle's end time (the last entry is the last key)
//   colour  0x1000002: +4+4n  RwRGBAReal start[n], then +4+20n RwRGBAReal delta[n]   (4 + 36n bytes)
//   texcoords 0x1000003: +4+4n RwTexCoords startUV0[n], +4+12n deltaUV0[n], +4+20n startUV1[n],
//                        +4+28n deltaUV1[n]                                          (4 + 36n bytes)
//   size    0x1000005: +4+4n  RwV2d start[n], then +4+12n RwV2d delta[n]            (4 + 20n bytes)
//   Segment j (j < n-1) runs from key j to key j+1, segment n-1 from the last key to the particle's end
//   value (the standard property's start + delta at time 1); start[j] is the value extrapolated back to
//   time 0, so value(t) = start[j] + t * delta[j] with t the particle's (unscaled) life fraction. The
//   segment before key 0 is written into the standard particle colour / texcoords / size property itself.
//   KeyFramesUpdate copies segment `index` into that standard property once the particle's time reaches
//   times[index].
#include <cstdint>
#include <cstring>

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rpprtstd/RpPrtStdInternal.h"
#include "Renderware/rpprtstd/RpPrtStdRuntime.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "crt/ppc_ops.h"

namespace rpprtstd {

// 0x00cf9e10..0x00cf9ebc. The table pointers start null, so the first call fills every offset.
AdvCachedOffsets g_advOffsets = {};

namespace {

// The emitter's random numbers as the asm converts them: the new seed zero-extended, fcfid (exact), frsp.
inline float SeedToFloat(uint32_t seed) { return ppc::frsp(static_cast<double>(seed)); }
// seed * 2^-32 (TOC 0x2f800000), fmuls: [0, 1).
inline float UnitRandom(int32_t* seed) { return SeedToFloat(NextSeed(seed)) * 0x1p-32f; }
// 2 * (seed * 2^-32) - 1: fmuls, fadds (x + x), fsubs 1.0f: [-1, 1).
inline float SignedRandom(int32_t* seed) {
    float value = SeedToFloat(NextSeed(seed)) * 0x1p-32f;
    value = value + value;
    return value - 1.0f;
}

inline float* FloatsAt(uint8_t* base, int32_t offset) { return reinterpret_cast<float*>(base + offset); }
inline const float* Key(const uint8_t* keys, uint32_t keySize, int32_t index) {
    return reinterpret_cast<const float*>(keys + keySize * static_cast<uint32_t>(index));
}
// lfs/stfs pairs: the words are copied unchanged.
inline void CopyFloats(float* dst, const uint8_t* src, uint32_t count) { std::memcpy(dst, src, count * 4u); }

// A PTank out pointer moved back over the `count` particles of this frame (the standard emit has already
// advanced it past them): mullw + subf in 32 bits.
inline uint8_t* RewindTank(uint8_t* out, int32_t count, int32_t stride) {
    const int32_t bytes = static_cast<int32_t>(static_cast<uint32_t>(count) * static_cast<uint32_t>(stride));
    return out - static_cast<intptr_t>(bytes);
}

// The emitter-side keys at their fixed positions (see the top of the file).
constexpr uint32_t kColorKeys = 0x14;
constexpr uint32_t kTexCoordsKeys = 0x1c;
constexpr uint32_t kSizeKeys = 0x14;
constexpr uint32_t kColorKeySize = 0x28;
constexpr uint32_t kTexCoordsKeySize = 0x28;
constexpr uint32_t kSizeKeySize = 0x18;

// The multi colour part of 0x6f41b0 (0x6f43dc..0x6f4800) for one new particle. `timesBytes` / `startBytes`
// are count << 2 and count << 4, taken once per call before the particle loop.
void EmitMultiColor(uint8_t* particle, uint8_t* prop, uint32_t timesBytes, uint32_t startBytes, int32_t* seed) {
    const AdvCachedOffsets& o = g_advOffsets;
    const float* const prtStd = reinterpret_cast<const float*>(particle);  // RpPrtStdParticleStandard at +0
    uint8_t* const keyed = particle + o.prtMultiColor;
    float* const times = reinterpret_cast<float*>(keyed + 4);
    uint8_t* const starts = keyed + 4 + timesBytes;
    uint8_t* const deltas = starts + startBytes;
    // The particle colour property (RpPrtStdParticleColor {startCol, deltaCol}); its offset is not checked.
    float* const color = FloatsAt(particle, o.prtColor);
    const uint8_t* const keys = prop + kColorKeys;  // PS3: lwz 0x4(prop)

    // The particle's end colour (start + delta), read before anything is written.
    float end[4];
    for (int c = 0; c < 4; ++c) end[c] = color[c] + color[4 + c];

    // Key 0: the time with a [0, 1) weight on its bias, the colour a blend midCol * r + midColBias * (1 - r)
    // clamped to 255.
    // BUG(original)?: only key 0 is blended with a [0, 1) weight and clamped; the later keys use a [-1, 1)
    // weight (so 1 - w reaches 2) and are not clamped.
    const float* key = Key(keys, kColorKeySize, 0);
    const float time0 = ppc::fmadds(UnitRandom(seed), key[1], key[0]);
    const float r = UnitRandom(seed);
    const float rInv = 1.0f - r;
    float color0[4];
    for (int c = 0; c < 4; ++c) {
        color0[c] = ppc::fmadds(r, key[2 + c], rInv * key[6 + c]);
        if (color0[c] > 255.0f) color0[c] = 255.0f;
    }

    float prevTime = time0;
    float prev[4] = {color0[0], color0[1], color0[2], color0[3]};
    int32_t last = 0;
    while (static_cast<int32_t>(WordAt(prop, 0)) - 1 > last) {
        const int32_t j = last;
        times[j] = prevTime * prtStd[2];  // endTime
        key = Key(keys, kColorKeySize, j + 1);
        const float timeWeight = SignedRandom(seed);
        const float w = SignedRandom(seed);
        const float nextTime = ppc::fmadds(timeWeight, key[1], key[0]);
        const float wInv = 1.0f - w;
        float inv = 0.0f;
        const float span = nextTime - prevTime;
        if (span > 0.0f) inv = 1.0f / span;
        float* const start = reinterpret_cast<float*>(starts + 16u * static_cast<uint32_t>(j));
        float* const delta = reinterpret_cast<float*>(deltas + 16u * static_cast<uint32_t>(j));
        for (int c = 0; c < 4; ++c) {
            const float value = ppc::fmadds(w, key[2 + c], wInv * key[6 + c]);
            const float d = inv * (value - prev[c]);
            start[c] = prev[c] - prevTime * d;
            delta[c] = d;
            prev[c] = value;
        }
        prevTime = nextTime;
        last = j + 1;
    }

    // The last segment: from the last key to the end colour at time 1.
    times[last] = prevTime * prtStd[2];
    const float rest = 1.0f - prevTime;
    float inv = 0.0f;
    if (rest > 0.0f) inv = 1.0f / rest;
    const float inv0 = 1.0f / time0;
    float* const start = reinterpret_cast<float*>(starts + 16u * static_cast<uint32_t>(last));
    float* const delta = reinterpret_cast<float*>(deltas + 16u * static_cast<uint32_t>(last));
    for (int c = 0; c < 4; ++c) {
        const float d = inv * (end[c] - prev[c]);
        start[c] = prev[c] - prevTime * d;
        delta[c] = d;
    }
    *reinterpret_cast<int32_t*>(keyed) = 0;
    // The standard property now runs from its start colour to key 0.
    for (int c = 0; c < 4; ++c) color[4 + c] = inv0 * (color0[c] - color[c]);
}

// The multi texcoords part of 0x6f41b0 (0x6f4804..0x6f4d28). `timesBytes` / `arrayBytes`: count << 2 and
// count << 3.
void EmitMultiTexCoords(uint8_t* particle, uint8_t* prop, uint32_t timesBytes, uint32_t arrayBytes, int32_t* seed) {
    const AdvCachedOffsets& o = g_advOffsets;
    const float* const prtStd = reinterpret_cast<const float*>(particle);
    uint8_t* const keyed = particle + o.prtMultiTexCoords;
    float* const times = reinterpret_cast<float*>(keyed + 4);
    uint8_t* const startUV0 = keyed + 4 + timesBytes;
    uint8_t* const deltaUV0 = startUV0 + arrayBytes;
    uint8_t* const startUV1 = deltaUV0 + arrayBytes;
    uint8_t* const deltaUV1 = startUV1 + arrayBytes;
    // RpPrtStdParticleTexCoords {startUV0, startUV1, deltaUV0, deltaUV1}; the offset is not checked.
    float* const tex = FloatsAt(particle, o.prtTexCoords);
    const uint8_t* const keys = prop + kTexCoordsKeys;  // PS3: lwz 0x4(prop)

    // The end values (start + delta) in the order u0, v0, u1, v1.
    float end[4];
    for (int c = 0; c < 4; ++c) end[c] = tex[c] + tex[4 + c];

    // Key 0: value = mid + w * midBias, five weights in [-1, 1) (time, u0, v0, u1, v1).
    const float* key = Key(keys, kTexCoordsKeySize, 0);
    const float time0 = ppc::fmadds(SignedRandom(seed), key[1], key[0]);
    float uv0[4];
    uv0[0] = ppc::fmadds(SignedRandom(seed), key[4], key[2]);
    uv0[1] = ppc::fmadds(SignedRandom(seed), key[5], key[3]);
    uv0[2] = ppc::fmadds(SignedRandom(seed), key[8], key[6]);
    uv0[3] = ppc::fmadds(SignedRandom(seed), key[9], key[7]);

    float prevTime = time0;
    float prev[4] = {uv0[0], uv0[1], uv0[2], uv0[3]};
    int32_t last = 0;
    while (static_cast<int32_t>(WordAt(prop, 0)) - 1 > last) {
        const int32_t j = last;
        times[j] = prtStd[2] * prevTime;
        key = Key(keys, kTexCoordsKeySize, j + 1);
        const float nextTime = ppc::fmadds(SignedRandom(seed), key[1], key[0]);
        float inv = 0.0f;
        const float span = nextTime - prevTime;
        if (span > 0.0f) inv = 1.0f / span;
        float value[4];
        value[0] = ppc::fmadds(SignedRandom(seed), key[4], key[2]);
        value[1] = ppc::fmadds(SignedRandom(seed), key[5], key[3]);
        value[2] = ppc::fmadds(SignedRandom(seed), key[8], key[6]);
        value[3] = ppc::fmadds(SignedRandom(seed), key[9], key[7]);
        float d[4];
        for (int c = 0; c < 4; ++c) d[c] = inv * (value[c] - prev[c]);
        const uint32_t at = 8u * static_cast<uint32_t>(j);
        float* s0 = reinterpret_cast<float*>(startUV0 + at);
        float* d0 = reinterpret_cast<float*>(deltaUV0 + at);
        float* s1 = reinterpret_cast<float*>(startUV1 + at);
        float* d1 = reinterpret_cast<float*>(deltaUV1 + at);
        s0[0] = prev[0] - prevTime * d[0];
        s0[1] = prev[1] - prevTime * d[1];
        s1[0] = prev[2] - prevTime * d[2];
        s1[1] = prev[3] - prevTime * d[3];
        d0[0] = d[0];
        d0[1] = d[1];
        d1[0] = d[2];
        d1[1] = d[3];
        for (int c = 0; c < 4; ++c) prev[c] = value[c];
        prevTime = nextTime;
        last = j + 1;
    }

    times[last] = prtStd[2] * prevTime;
    const float rest = 1.0f - prevTime;
    float inv = 0.0f;
    if (rest > 0.0f) inv = 1.0f / rest;
    const float inv0 = 1.0f / time0;
    float d[4];
    for (int c = 0; c < 4; ++c) d[c] = inv * (end[c] - prev[c]);
    const uint32_t at = 8u * static_cast<uint32_t>(last);
    float* s0 = reinterpret_cast<float*>(startUV0 + at);
    float* d0 = reinterpret_cast<float*>(deltaUV0 + at);
    float* s1 = reinterpret_cast<float*>(startUV1 + at);
    float* d1 = reinterpret_cast<float*>(deltaUV1 + at);
    s0[0] = prev[0] - d[0] * prevTime;
    s0[1] = prev[1] - d[1] * prevTime;
    s1[0] = prev[2] - d[2] * prevTime;
    s1[1] = prev[3] - d[3] * prevTime;
    d0[0] = d[0];
    d0[1] = d[1];
    d1[0] = d[2];
    d1[1] = d[3];
    *reinterpret_cast<int32_t*>(keyed) = 0;
    for (int c = 0; c < 4; ++c) tex[4 + c] = inv0 * (uv0[c] - tex[c]);
}

// The multi size part of 0x6f41b0 (0x6f4d2c..0x6f5014). `timesBytes` / `arrayBytes`: count << 2 and << 3.
void EmitMultiSize(uint8_t* particle, uint8_t* prop, uint32_t timesBytes, uint32_t arrayBytes, int32_t* seed) {
    const AdvCachedOffsets& o = g_advOffsets;
    const float* const prtStd = reinterpret_cast<const float*>(particle);
    uint8_t* const keyed = particle + o.prtMultiSize;
    float* const times = reinterpret_cast<float*>(keyed + 4);
    uint8_t* const starts = keyed + 4 + timesBytes;
    uint8_t* const deltas = starts + arrayBytes;
    // RpPrtStdParticleSize {startSize, deltaSize, currSize, invCurrSize}; the offset is not checked.
    float* const size = FloatsAt(particle, o.prtSize);
    const uint8_t* const keys = prop + kSizeKeys;  // PS3: lwz 0x4(prop)

    const float endX = size[0] + size[2];
    const float endY = size[1] + size[3];

    // Key 0: one [-1, 1) weight for the time, one shared by x and y.
    const float* key = Key(keys, kSizeKeySize, 0);
    const float time0 = ppc::fmadds(SignedRandom(seed), key[1], key[0]);
    const float w0 = SignedRandom(seed);
    const float x0 = ppc::fmadds(w0, key[4], key[2]);
    const float y0 = ppc::fmadds(w0, key[5], key[3]);

    float prevTime = time0;
    float prevX = x0;
    float prevY = y0;
    int32_t last = 0;
    while (static_cast<int32_t>(WordAt(prop, 0)) - 1 > last) {
        const int32_t j = last;
        times[j] = prtStd[2] * prevTime;
        key = Key(keys, kSizeKeySize, j + 1);
        const float timeWeight = SignedRandom(seed);
        const float w = SignedRandom(seed);
        const float nextTime = ppc::fmadds(timeWeight, key[1], key[0]);
        float inv = 0.0f;
        const float span = nextTime - prevTime;
        if (span > 0.0f) inv = 1.0f / span;
        const float x = ppc::fmadds(w, key[4], key[2]);
        const float y = ppc::fmadds(w, key[5], key[3]);
        const float dx = inv * (x - prevX);
        const float dy = inv * (y - prevY);
        float* const start = reinterpret_cast<float*>(starts + 8u * static_cast<uint32_t>(j));
        float* const delta = reinterpret_cast<float*>(deltas + 8u * static_cast<uint32_t>(j));
        start[0] = prevX - dx * prevTime;
        start[1] = prevY - dy * prevTime;
        delta[0] = dx;
        delta[1] = dy;
        prevTime = nextTime;
        prevX = x;
        prevY = y;
        last = j + 1;
    }

    times[last] = prtStd[2] * prevTime;
    const float rest = 1.0f - prevTime;
    float inv = 0.0f;
    if (rest > 0.0f) inv = 1.0f / rest;
    const float inv0 = 1.0f / time0;
    const float dx = inv * (endX - prevX);
    const float dy = inv * (endY - prevY);
    float* const start = reinterpret_cast<float*>(starts + 8u * static_cast<uint32_t>(last));
    float* const delta = reinterpret_cast<float*>(deltas + 8u * static_cast<uint32_t>(last));
    start[0] = prevX - dx * prevTime;
    start[1] = prevY - dy * prevTime;
    delta[0] = dx;
    delta[1] = dy;
    *reinterpret_cast<int32_t*>(keyed) = 0;
    size[2] = inv0 * (x0 - size[0]);
    size[3] = inv0 * (y0 - size[1]);
}

}  // namespace

// 0x006f00d8 RW_CacheParticlePropertyOffsets2_maybe: RpPrtAdv's copy of the offset cache, refilled when the
// emitter's (or the particle class's) property table differs from the last one seen.
RpPrtStdEmitter* CacheAdvPropertyOffsets(RpPrtStdEmitter* emitter) {
    AdvCachedOffsets& o = g_advOffsets;
    const RpPrtStdPropertyTable* emitterTable = emitter->emtClass->propTab;
    if (o.emitterTable != emitterTable) {
        o.emitterTable = emitterTable;
        o.emtStd = RpPrtStdPropTabGetPropOffset(emitterTable, rpPRTSTDPROPERTYCODEEMITTERSTANDARD);
        o.emtPrtColor = RpPrtStdPropTabGetPropOffset(emitterTable, rpPRTSTDPROPERTYCODEEMITTERPRTCOLOR);
        o.emtPrtTexCoords = RpPrtStdPropTabGetPropOffset(emitterTable, rpPRTSTDPROPERTYCODEEMITTERPRTTEXCOORDS);
        o.emtPrtSize = RpPrtStdPropTabGetPropOffset(emitterTable, rpPRTSTDPROPERTYCODEEMITTERPRTSIZE);
        o.emtPTank = RpPrtStdPropTabGetPropOffset(emitterTable, rpPRTSTDPROPERTYCODEEMITTERPTANK);
        o.emtAdv0 = RpPrtStdPropTabGetPropOffset(emitterTable, 0x1000000);
        o.emtPrtEmitter = RpPrtStdPropTabGetPropOffset(emitterTable, rpPRTADVPROPERTYCODEEMITTERPRTEMITTER);
        o.emtMultiColor = RpPrtStdPropTabGetPropOffset(emitterTable, rpPRTADVPROPERTYCODEEMITTERPRTMULTICOLOR);
        o.emtMultiTexCoords = RpPrtStdPropTabGetPropOffset(emitterTable, rpPRTADVPROPERTYCODEEMITTERPRTMULTITEXCOORDS);
        o.emtMultiTexCoordsStep =
            RpPrtStdPropTabGetPropOffset(emitterTable, rpPRTADVPROPERTYCODEEMITTERPRTMULTITEXCOORDSSTEP);
        o.emtMultiSize = RpPrtStdPropTabGetPropOffset(emitterTable, rpPRTADVPROPERTYCODEEMITTERPRTMULTISIZE);
        o.emtPointList = RpPrtStdPropTabGetPropOffset(emitterTable, rpPRTADVPROPERTYCODEEMITTERPOINTLIST);
        o.emtCircle = RpPrtStdPropTabGetPropOffset(emitterTable, rpPRTADVPROPERTYCODEEMITTERCIRCLE);
        o.emtSphere = RpPrtStdPropTabGetPropOffset(emitterTable, rpPRTADVPROPERTYCODEEMITTERSPHERE);
    }
    const RpPrtStdPropertyTable* particleTable = emitter->prtClass->propTab;
    if (o.particleTable != particleTable) {
        o.particleTable = particleTable;
        o.prtStd = RpPrtStdPropTabGetPropOffset(particleTable, rpPRTSTDPROPERTYCODEPARTICLESTANDARD);
        o.prtColor = RpPrtStdPropTabGetPropOffset(particleTable, rpPRTSTDPROPERTYCODEPARTICLECOLOR);
        o.prtTexCoords = RpPrtStdPropTabGetPropOffset(particleTable, rpPRTSTDPROPERTYCODEPARTICLETEXCOORDS);
        o.prtSize = RpPrtStdPropTabGetPropOffset(particleTable, rpPRTSTDPROPERTYCODEPARTICLESIZE);
        o.prtPosition = RpPrtStdPropTabGetPropOffset(particleTable, rpPRTSTDPROPERTYCODEPARTICLEPOSITION);
        o.prtVelocity = RpPrtStdPropTabGetPropOffset(particleTable, rpPRTSTDPROPERTYCODEPARTICLEVELOCITY);
        o.prtAdv0 = RpPrtStdPropTabGetPropOffset(particleTable, 0x1000000);
        o.prtPrtEmitter = RpPrtStdPropTabGetPropOffset(particleTable, rpPRTADVPROPERTYCODEEMITTERPRTEMITTER);
        o.prtMultiColor = RpPrtStdPropTabGetPropOffset(particleTable, rpPRTADVPROPERTYCODEEMITTERPRTMULTICOLOR);
        o.prtMultiTexCoords = RpPrtStdPropTabGetPropOffset(particleTable, rpPRTADVPROPERTYCODEEMITTERPRTMULTITEXCOORDS);
        o.prtMultiTexCoordsStep =
            RpPrtStdPropTabGetPropOffset(particleTable, rpPRTADVPROPERTYCODEEMITTERPRTMULTITEXCOORDSSTEP);
        o.prtMultiSize = RpPrtStdPropTabGetPropOffset(particleTable, rpPRTADVPROPERTYCODEEMITTERPRTMULTISIZE);
        o.prtStdIndex = RpPrtStdPropTabGetPropIndex(particleTable, rpPRTSTDPROPERTYCODEPARTICLESTANDARD);
        o.prtColorIndex = RpPrtStdPropTabGetPropIndex(particleTable, rpPRTSTDPROPERTYCODEPARTICLECOLOR);
        o.prtTexCoordsIndex = RpPrtStdPropTabGetPropIndex(particleTable, rpPRTSTDPROPERTYCODEPARTICLETEXCOORDS);
        o.prtSizeIndex = RpPrtStdPropTabGetPropIndex(particleTable, rpPRTSTDPROPERTYCODEPARTICLESIZE);
        o.prtPositionIndex = RpPrtStdPropTabGetPropIndex(particleTable, rpPRTSTDPROPERTYCODEPARTICLEPOSITION);
        o.prtVelocityIndex = RpPrtStdPropTabGetPropIndex(particleTable, rpPRTSTDPROPERTYCODEPARTICLEVELOCITY);
        o.prtAdv0Index = RpPrtStdPropTabGetPropIndex(particleTable, 0x1000000);
        o.prtPrtEmitterIndex = RpPrtStdPropTabGetPropIndex(particleTable, rpPRTADVPROPERTYCODEEMITTERPRTEMITTER);
        o.prtMultiColorIndex = RpPrtStdPropTabGetPropIndex(particleTable, rpPRTADVPROPERTYCODEEMITTERPRTMULTICOLOR);
        o.prtMultiTexCoordsIndex =
            RpPrtStdPropTabGetPropIndex(particleTable, rpPRTADVPROPERTYCODEEMITTERPRTMULTITEXCOORDS);
        // (no index for 0x1000004)
        o.prtMultiSizeIndex = RpPrtStdPropTabGetPropIndex(particleTable, rpPRTADVPROPERTYCODEEMITTERPRTMULTISIZE);
    }
    return emitter;
}

// 0x006f26c8 PrtStdEmitterProp1000006_Emit_maybe: after the standard emit, the particles emitted this frame
// in the head of the active ring (the batch the standard emit filled; the other batches are not visited)
// are moved onto the point list: point (next in order, or a random one) + emtSize * [-1, 1) per axis,
// through the frame LTM, then pushed along their velocity by gap * step (the step counts up every
// `count / (emitted gaps + 1)` particles when the standard property's +0xb0 is set). With useDirection, the
// velocity becomes the normalised (direction + prtInitDirBias * [-1, 1)) through the LTM, times
// prtInitVel + prtInitVelBias * [-1, 1). The position goes to the particle and to the PTank's position or
// matrix array.
RpPrtStdEmitter* PointListEmit(RpAtomic*, RpPrtStdEmitter* emitter, void*) {
    CacheAdvPropertyOffsets(emitter);
    const AdvCachedOffsets& o = g_advOffsets;
    RpPrtStdEmitterPTank* const ptank =
        o.emtPTank >= 0 ? reinterpret_cast<RpPrtStdEmitterPTank*>(PropertyAt(emitter, o.emtPTank)) : nullptr;
    RpPrtAdvEmtPointList* const list =
        o.emtPointList >= 0 ? reinterpret_cast<RpPrtAdvEmtPointList*>(PropertyAt(emitter, o.emtPointList)) : nullptr;
    RpPrtStdParticleBatch* const batch = static_cast<RpPrtStdParticleBatch*>(emitter->activeBatch);
    if (batch == nullptr) return emitter;
    const int32_t first = batch->newPrt;
    if (first == -1) return emitter;
    const int32_t count = batch->numPrt - first;

    // The PTank arrays the positions go to, moved back to this frame's first particle: the position array
    // (data flag 0x1, always the first array) and the matrix array (0x8, after the colour and size arrays).
    // BUG(original): one pointer and one stride serve both; with both arrays locked the matrix array's
    // replace the position array's, and each particle then writes its position into the matrix array's
    // right vector and the next matrix's pos, advancing two strides.
    uint8_t* tankOut = nullptr;
    int32_t tankStride = 0;
    if (ptank != nullptr) {
        const uint32_t flags = ptank->dataFlags;
        int32_t index = 0;
        if ((flags & 0x1u) != 0) {
            tankStride = ptank->dataStride[0];
            tankOut = RewindTank(ptank->dataOutPtrs[0], count, tankStride);
            index = 1;
        }
        index += static_cast<int32_t>((flags >> 1) & 1u);
        index += static_cast<int32_t>((flags >> 2) & 1u);
        if ((flags & 0x8u) != 0) {
            tankStride = ptank->dataStride[index];
            tankOut = RewindTank(ptank->dataOutPtrs[index], count, tankStride);
        }
    }

    RpPrtStdEmitterStandard* const standard = reinterpret_cast<RpPrtStdEmitterStandard*>(PropertyAt(emitter, o.emtStd));
    const int32_t prtSize = emitter->prtClass->objSize;
    float gap = standard->emtEmitGap;
    if (gap < 1.0e-3f) gap = 1.0e-3f;  // TOC 0x3a83126f
    RwMatrix* const ltm = standard->ltm;
    int32_t seed = standard->seed;
    // The particles per emitted gap: count / (the gaps since the previous emit + 1), at least 1.
    const int64_t gaps = ppc::fctidz((standard->currTime - standard->emtPrevEmitTime) / gap);
    uint32_t perStep = ppc::divwu(static_cast<uint32_t>(count), static_cast<uint32_t>(static_cast<uint64_t>(gaps) + 1u));
    if (perStep == 0) perStep = 1;

    if (count > 0) {
        float step = 0.0f;
        RwV3d offset = {0.0f, 0.0f, 0.0f};  // stack +0x70: the point before the LTM, then the direction
        // stack +0x7c: the position.
        // BUG(original): it is only written by RwV3dTransformPoint, so without an LTM (or without a velocity
        // property, where the whole block is skipped) the particles get the previous particle's position,
        // or uninitialised stack for the first one (zeros here). The update-time callback always sets the
        // LTM in practice.
        RwV3d position = {0.0f, 0.0f, 0.0f};
        uint8_t* particle = RpPrtStdBatchParticles(batch) + first * prtSize;
        int32_t i = 0;
        for (;;) {
            if (o.prtVelocity >= 0) {
                NextSeed(&seed);
                uint32_t index;
                if (list->random == 0) {
                    index = list->lastPoint;
                    list->lastPoint = index + 1;
                    if (!(list->numPoint > index + 1)) list->lastPoint = 0;
                } else {
                    // The seed sign-extended here (extsw before fcfid): (seed * 2^-32 + 0.5) * numPoint.
                    const float unit = ppc::fmadds(ppc::frsp(static_cast<double>(seed)), 0x1p-32f, 0.5f);
                    const float points = ppc::frsp(static_cast<double>(list->numPoint));
                    index = static_cast<uint32_t>(ppc::fctiwz(unit * points));
                }
                const RwV3d& point = list->pointList[index];
                offset.x = ppc::fmadds(SignedRandom(&seed), standard->emtSize.x, point.x);
                offset.y = ppc::fmadds(SignedRandom(&seed), standard->emtSize.y, point.y);
                offset.z = ppc::fmadds(SignedRandom(&seed), standard->emtSize.z, point.z);
                if (ltm != nullptr) RwV3dTransformPoint(&position, &offset, ltm);
                float* const velocity = FloatsAt(particle, o.prtVelocity);
                position.x = ppc::fmadds(gap, step * velocity[0], position.x);
                position.y = ppc::fmadds(gap, step * velocity[1], position.y);
                position.z = ppc::fmadds(gap, step * velocity[2], position.z);
                if (list->useDirection == 1) {
                    const RwV3d& direction = list->directionList[index];
                    offset.x = ppc::fmadds(SignedRandom(&seed), standard->prtInitDirBias.x, direction.x);
                    offset.y = ppc::fmadds(SignedRandom(&seed), standard->prtInitDirBias.y, direction.y);
                    offset.z = ppc::fmadds(SignedRandom(&seed), standard->prtInitDirBias.z, direction.z);
                    RwV3dNormalize(&offset, &offset);
                    if (ltm != nullptr) RwV3dTransformVector(&offset, &offset, ltm);
                    const float w = SignedRandom(&seed);
                    velocity[0] = offset.x * ppc::fmadds(w, standard->prtInitVelBias, standard->prtInitVel);
                    velocity[1] = offset.y * ppc::fmadds(w, standard->prtInitVelBias, standard->prtInitVel);
                    velocity[2] = offset.z * ppc::fmadds(w, standard->prtInitVelBias, standard->prtInitVel);
                }
            }
            if (o.prtPosition >= 0) {
                float* const out = FloatsAt(particle, o.prtPosition);
                out[0] = position.x;
                out[1] = position.y;
                out[2] = position.z;
            }
            if (ptank != nullptr) {
                if ((ptank->updateFlags & ptank->dataFlags & 0x1u) != 0) {
                    float* const out = reinterpret_cast<float*>(tankOut);
                    tankOut += tankStride;
                    out[0] = position.x;
                    out[1] = position.y;
                    out[2] = position.z;
                }
                if ((ptank->updateFlags & ptank->dataFlags & 0x8u) != 0) {
                    float* const out = reinterpret_cast<float*>(tankOut + 0x30);  // RwMatrix pos
                    tankOut += tankStride;
                    out[0] = position.x;
                    out[1] = position.y;
                    out[2] = position.z;
                }
            }
            ++i;
            if (standard->unkB0 != 0) {
                const uint32_t done = static_cast<uint32_t>(i);
                if (done == ppc::divwu(done, perStep) * perStep) step = step + 1.0f;
            }
            if (i >= count) break;
            particle += prtSize;
        }
    }
    standard->seed = seed;
    return emitter;
}

// 0x006f41b0 PrtStdEmitterProp1000002_3_5_Emit_maybe: once the emitter has emitted (currTime >= emtEmitTime),
// every new particle of the head of the active ring that has not aged yet (currTime == 0) gets its multi
// colour / texcoords / size segments from the emitter's keys (randomised by the biases), see the top of
// the file. The seed advances once per call before the particles.
RpPrtStdEmitter* MultiEmit(RpAtomic*, RpPrtStdEmitter* emitter, void*) {
    CacheAdvPropertyOffsets(emitter);
    const AdvCachedOffsets& o = g_advOffsets;
    RpPrtStdEmitterStandard* const standard = reinterpret_cast<RpPrtStdEmitterStandard*>(PropertyAt(emitter, o.emtStd));
    uint8_t* colorProp = nullptr;
    uint32_t colorTimes = 0;
    uint32_t colorStarts = 0;
    if (o.emtMultiColor >= 0) {
        colorProp = PropertyAt(emitter, o.emtMultiColor);
        colorStarts = WordAt(colorProp, 0) << 4;
        colorTimes = WordAt(colorProp, 0) << 2;
    }
    uint8_t* texProp = nullptr;
    uint32_t texArray = 0;
    uint32_t texTimes = 0;
    if (o.emtMultiTexCoords >= 0) {
        texProp = PropertyAt(emitter, o.emtMultiTexCoords);
        texArray = WordAt(texProp, 0) << 3;
        texTimes = WordAt(texProp, 0) << 2;
    }
    uint8_t* sizeProp = nullptr;
    uint32_t sizeArray = 0;
    uint32_t sizeTimes = 0;
    if (o.emtMultiSize >= 0) {
        sizeProp = PropertyAt(emitter, o.emtMultiSize);
        sizeArray = WordAt(sizeProp, 0) << 3;
        sizeTimes = WordAt(sizeProp, 0) << 2;
    }
    if (!(standard->currTime >= standard->emtEmitTime)) return emitter;
    RpPrtStdParticleBatch* const batch = static_cast<RpPrtStdParticleBatch*>(emitter->activeBatch);
    if (batch == nullptr) return emitter;
    const int32_t first = batch->newPrt;
    if (first == -1 || first < 0) return emitter;

    int32_t seed = standard->seed;
    NextSeed(&seed);
    const int32_t count = batch->numPrt - first;
    const int32_t prtSize = emitter->prtClass->objSize;
    if (count > 0) {
        uint8_t* particle = RpPrtStdBatchParticles(batch) + first * prtSize;
        int32_t i = 0;
        for (;;) {
            // RpPrtStdParticleStandard.currTime, at +4 of the particle itself (the standard property is the
            // first one; the cached offset is not used).
            if (*FloatsAt(particle, 4) == 0.0f) {
                // The emitter properties are not checked: a particle property without its emitter property
                // reads through null, as on the PS3.
                if (o.prtMultiColor >= 0) EmitMultiColor(particle, colorProp, colorTimes, colorStarts, &seed);
                if (o.prtMultiTexCoords >= 0) EmitMultiTexCoords(particle, texProp, texTimes, texArray, &seed);
                if (o.prtMultiSize >= 0) EmitMultiSize(particle, sizeProp, sizeTimes, sizeArray, &seed);
            }
            ++i;
            if (count == i) break;
            particle += prtSize;
        }
    }
    standard->seed = seed;
    return emitter;
}

// 0x006f50e0 PrtStdParticleKeyFrames_Update_maybe: for every live particle of the batch (currTime < endTime),
// each multi property whose next key time (times[index], scaled to the particle's life) is reached by
// currTime + delta copies that segment's start and delta into the standard colour / texcoords / size
// property and moves on to the next key. `data` is the delta time (float*).
RpPrtStdParticleBatch* KeyFramesUpdate(RpPrtStdEmitter* emitter, RpPrtStdParticleBatch* batch, void* data) {
    const float delta = *static_cast<const float*>(data);
    CacheAdvPropertyOffsets(emitter);
    const AdvCachedOffsets& o = g_advOffsets;
    uint8_t* const colorProp = o.emtMultiColor >= 0 ? PropertyAt(emitter, o.emtMultiColor) : nullptr;
    uint8_t* const texProp = o.emtMultiTexCoords >= 0 ? PropertyAt(emitter, o.emtMultiTexCoords) : nullptr;
    uint8_t* const sizeProp = o.emtMultiSize >= 0 ? PropertyAt(emitter, o.emtMultiSize) : nullptr;
    const int32_t prtSize = emitter->prtClass->objSize;
    const int32_t num = batch->numPrt;
    if (num <= 0) return batch;

    uint8_t* particle = RpPrtStdBatchParticles(batch);
    for (uint32_t left = static_cast<uint32_t>(num);;) {
        // RpPrtStdParticleStandard {flag, currTime, endTime, invEndTime} at +0 of the particle.
        const float* const prtStd = reinterpret_cast<const float*>(particle);
        if (prtStd[2] > prtStd[1]) {
            const float time = delta + prtStd[1];
            if (o.prtMultiColor >= 0) {
                uint8_t* const keyed = particle + o.prtMultiColor;
                const uint32_t index = WordAt(keyed, 0);
                if (WordAt(colorProp, 0) > index && reinterpret_cast<const float*>(keyed + 4)[index] <= time &&
                    o.prtColor >= 0) {
                    float* const color = FloatsAt(particle, o.prtColor);
                    CopyFloats(color, keyed + static_cast<uint32_t>(WordAt(colorProp, 0xc) + (index << 4)), 4);
                    CopyFloats(color + 4, keyed + static_cast<uint32_t>(WordAt(colorProp, 0x10) + (index << 4)), 4);
                    WordAt(keyed, 0) = index + 1;
                }
            }
            if (o.prtMultiTexCoords >= 0) {
                uint8_t* const keyed = particle + o.prtMultiTexCoords;
                const uint32_t index = WordAt(keyed, 0);
                if (WordAt(texProp, 0) > index && reinterpret_cast<const float*>(keyed + 4)[index] <= time &&
                    o.prtTexCoords >= 0) {
                    float* const tex = FloatsAt(particle, o.prtTexCoords);
                    CopyFloats(tex + 0, keyed + static_cast<uint32_t>(WordAt(texProp, 0xc) + (index << 3)), 2);
                    CopyFloats(tex + 4, keyed + static_cast<uint32_t>(WordAt(texProp, 0x10) + (index << 3)), 2);
                    CopyFloats(tex + 2, keyed + static_cast<uint32_t>(WordAt(texProp, 0x14) + (index << 3)), 2);
                    CopyFloats(tex + 6, keyed + static_cast<uint32_t>(WordAt(texProp, 0x18) + (index << 3)), 2);
                    WordAt(keyed, 0) = index + 1;
                }
            }
            if (o.prtMultiSize >= 0) {
                uint8_t* const keyed = particle + o.prtMultiSize;
                const uint32_t index = WordAt(keyed, 0);
                if (WordAt(sizeProp, 0) > index && reinterpret_cast<const float*>(keyed + 4)[index] <= time &&
                    o.prtSize >= 0) {
                    float* const size = FloatsAt(particle, o.prtSize);
                    CopyFloats(size + 0, keyed + static_cast<uint32_t>(WordAt(sizeProp, 0xc) + (index << 3)), 2);
                    CopyFloats(size + 2, keyed + static_cast<uint32_t>(WordAt(sizeProp, 0x10) + (index << 3)), 2);
                    WordAt(keyed, 0) = index + 1;
                }
            }
        }
        if (--left == 0) break;
        particle += prtSize;
    }
    return batch;
}

// 0x006f5df0 PrtStdParticleTexCoordKeyFrames_Update_maybe (multi texcoords step, 0x1000004): for every live
// particle of the batch, once currTime + delta reaches the next step's time (times[index], read as a float),
// the step's UV0 and UV1 (2 floats each, at the emitter property's +0x0c / +0x14 array offsets) replace
// the standard texcoords' start UV0 / UV1 (no deltas: the frames step), and the index moves on.
RpPrtStdParticleBatch* TexCoordStepUpdate(RpPrtStdEmitter* emitter, RpPrtStdParticleBatch* batch, void* data) {
    const float delta = *static_cast<const float*>(data);
    CacheAdvPropertyOffsets(emitter);
    const AdvCachedOffsets& o = g_advOffsets;
    uint8_t* const stepProp = o.emtMultiTexCoordsStep >= 0 ? PropertyAt(emitter, o.emtMultiTexCoordsStep) : nullptr;
    const int32_t prtSize = emitter->prtClass->objSize;
    const int32_t num = batch->numPrt;
    if (num <= 0) return batch;

    uint8_t* particle = RpPrtStdBatchParticles(batch);
    for (uint32_t left = static_cast<uint32_t>(num);;) {
        const float* const prtStd = reinterpret_cast<const float*>(particle);
        if (prtStd[1] < prtStd[2] && o.prtMultiTexCoordsStep >= 0) {
            uint8_t* const keyed = particle + o.prtMultiTexCoordsStep;
            const uint32_t index = WordAt(keyed, 0);
            if (index < WordAt(stepProp, 0) && reinterpret_cast<const float*>(keyed + 4)[index] <= delta + prtStd[1] &&
                o.prtTexCoords >= 0) {
                float* const tex = FloatsAt(particle, o.prtTexCoords);
                CopyFloats(tex + 0, keyed + static_cast<uint32_t>(WordAt(stepProp, 0xc) + (index << 3)), 2);
                CopyFloats(tex + 2, keyed + static_cast<uint32_t>(WordAt(stepProp, 0x14) + (index << 3)), 2);
                WordAt(keyed, 0) = index + 1;
            }
        }
        if (--left == 0) break;
        particle += prtSize;
    }
    return batch;
}

}  // namespace rpprtstd
