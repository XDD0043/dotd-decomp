// RpPrtStdUpdate.cpp - the standard particle class's update callback (particle callback slot 0), ported from
// the PS3 library code (TOC 0xc25974): RpPrtStdParticleStd_Update_maybe 0x734188.
//
//   [x] 0x734188  RpPrtStdParticleStd_Update_maybe
//
// The RW loop (RW_UpdateParticleEmitter) fills g_offsets (CacheParticlePropertyOffsets) before the call; the
// globals block the original reads is 0x00cfba74 (TOC -0x36e0): +0x98 emtStd, +0xa8 emtPTank, +0xac
// emtPrtMatrix, +0xb4 prtPosition, +0xbc prtColor, +0xc0 prtTexCoords, +0xc4 prtSize, +0xc8 prtVelocity,
// +0xcc prtMatrix, +0xd0 prt2DRotate. g_offsets.prtStd (+0xb8) is never read: the standard particle
// property is assumed at offset 0 of each particle.
//
// Particle-side property layouts (PS3 byte layouts inside the batch, floats; sizes as the table rounds them):
//   0 standard   0x10  +0x0 flag (not read here), +0x4 currTime, +0x8 endTime, +0xc invEndTime (1 / life)
//   1 position   0x10  RwV3d (+0x0 x, +0x4 y, +0x8 z)
//   2 colour     0x20  +0x00 start RGBA (4 floats, 0..255), +0x10 delta RGBA (4 floats)
//   3 texcoords  0x20  +0x00 start (u0, v0, u1, v1), +0x10 delta (u0, v0, u1, v1)
//   4 2D rotate  0x08  +0x0 start angle, +0x4 delta angle
//   5 size       0x20  +0x00 start (w, h), +0x08 delta (w, h), +0x10 current (w, h) (0x18 used)
//   6 velocity   0x0c  RwV3d
//   7 matrix     0x40  RwMatrix (the particle's own matrix)
// The interpolation factor is t = min(currTime * invEndTime, 1); every interpolated value is
// start + t * delta (one fmadds), computed from the particle each frame.
//
// Emitter property 8 (rpprtstd.h RpPrtStdEmitterPrtMatrix): +0x00 prtCnsMtx (RwMatrix), +0x40 prtPosMtxAt,
// +0x4c prtPosMtxAtBias, +0x58 prtPosMtxUp, +0x64 prtPosMtxUpBias, +0x70 flags; the update uses prtCnsMtx
// only when the flags are non-zero.
//
// PTank arrays: the PTank property's dataInPtrs / dataOutPtrs / dataStride hold one entry per locked array.
// The update indexes them counting only the flags 0x1 position, 0x2 colour, 0x4 size, 0x8 matrix, 0x20
// 2D rotation and 0x80 2 tex coords, in that order (normal 0x10, vertex colours 0x40 and 4 tex coords 0x100
// take no index here: BUG(original)? with one of them locked the later indices would be off; the lock is
// believed never to set them for these emitters). Position and matrix share one set of in/out/stride
// variables (the original's), the matrix's overriding the position's when both are locked. A stride is 0
// unless the array is in updateFlags too, so the update rewrites the same output element then. The input
// pointers advance by their stride for every particle (live or dead), the outputs only for the particles
// written; the advanced pointers are stored back into the arrays at the end.
#include <cstdint>
#include <cstring>

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rpprtstd/RpPrtStdRuntime.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "crt/ppc_ops.h"

namespace rpprtstd {

namespace {

// Float / word access to the PS3 byte layouts (unaligned-safe; the original's lfs / stfs / lwz).
inline float LoadF(const uint8_t* base, int32_t offset) {
    float value;
    std::memcpy(&value, base + offset, 4);
    return value;
}
inline void StoreF(uint8_t* base, int32_t offset, float value) { std::memcpy(base + offset, &value, 4); }
inline int32_t LoadI(const uint8_t* base, int32_t offset) {
    int32_t value;
    std::memcpy(&value, base + offset, 4);
    return value;
}
// lfs / stfs pairs copying n floats in order (bit-exact moves).
inline void CopyWords(uint8_t* dst, const uint8_t* src, int32_t count) {
    for (int32_t i = 0; i < count; ++i) std::memcpy(dst + i * 4, src + i * 4, 4);
}

// The common end of the matrix paths (0x7346e8): the output matrix's position += (ax, ay, az), the squared
// distance from the emitter's centre into the running maximum.
inline void MatrixPositionAdd(uint8_t* out, float ax, float ay, float az, float cx, float cy, float cz,
                              float* maxDistSq) {
    const float ny = LoadF(out, 0x34) + ay;
    const float nx = LoadF(out, 0x30) + ax;
    const float nz = LoadF(out, 0x38) + az;
    const float dy = ny - cy;
    StoreF(out, 0x34, ny);
    const float dx = nx - cx;
    StoreF(out, 0x30, nx);
    const float dz = nz - cz;
    StoreF(out, 0x38, nz);
    const float d = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
    if (!(*maxDistSq > d)) *maxDistSq = d;
}

}  // namespace

// 0x00734188 RpPrtStdParticleStd_Update_maybe: every particle of the batch aged by the delta time (`data`,
// a float); the expired ones dropped (the live ones packed at the batch head with memcpy, numPrt the live
// count); velocity += dt * force - dt * damping * velocity, position += dt * velocity; colour, size, tex
// coords and 2D rotation interpolated into the PTank arrays (the arrays in updateFlags & dataFlags, the
// PTank's numPrt grown by the live count). The emitter's bounding sphere grows to the largest squared
// distance from the emitter frame's position (the RW caller takes the square root).
RpPrtStdParticleBatch* StdParticleUpdate(RpPrtStdEmitter* emitter, RpPrtStdParticleBatch* batch, void* data) {
    const float dt = *static_cast<const float*>(data);
    uint8_t* const emitterBytes = reinterpret_cast<uint8_t*>(emitter);
    RpPrtStdEmitterStandard* const stdProp = reinterpret_cast<RpPrtStdEmitterStandard*>(emitterBytes + g_offsets.emtStd);

    // The emitter's particle matrix (property 8), when present and its flags are set.
    const uint8_t* matrixProp = nullptr;
    if (g_offsets.emtPrtMatrix >= 0) {
        const uint8_t* prop = emitterBytes + g_offsets.emtPrtMatrix;
        if (LoadI(prop, 0x70) != 0) matrixProp = prop;
    }

    // The PTank arrays.
    RpPrtStdEmitterPTank* ptank = nullptr;
    if (g_offsets.emtPTank >= 0) ptank = reinterpret_cast<RpPrtStdEmitterPTank*>(emitterBytes + g_offsets.emtPTank);
    uint8_t* posIn = nullptr;   // position (0x1) or matrix (0x8)
    uint8_t* posOut = nullptr;
    int32_t posStride = 0;
    uint8_t* colIn = nullptr;   // colour (0x2)
    uint8_t* colOut = nullptr;
    int32_t colStride = 0;
    uint8_t* sizeIn = nullptr;  // size (0x4)
    uint8_t* sizeOut = nullptr;
    int32_t sizeStride = 0;
    uint8_t* rotIn = nullptr;   // 2D rotation (0x20)
    uint8_t* rotOut = nullptr;
    int32_t rotStride = 0;
    uint8_t* texIn = nullptr;   // 2 tex coords (0x80)
    uint8_t* texOut = nullptr;
    int32_t texStride = 0;
    if (ptank != nullptr) {
        const uint32_t dataFlags = ptank->dataFlags;
        int32_t index = 0;
        if ((dataFlags & 0x1) != 0) {
            posIn = ptank->dataInPtrs[0];
            posOut = ptank->dataOutPtrs[0];
            if ((ptank->updateFlags & 0x1) != 0) posStride = ptank->dataStride[0];
            index = 1;
        }
        if ((dataFlags & 0x2) != 0) {
            colIn = ptank->dataInPtrs[index];
            colOut = ptank->dataOutPtrs[index];
            if ((ptank->updateFlags & 0x2) != 0) colStride = ptank->dataStride[index];
            ++index;
        }
        if ((dataFlags & 0x4) != 0) {
            sizeIn = ptank->dataInPtrs[index];
            sizeOut = ptank->dataOutPtrs[index];
            if ((ptank->updateFlags & 0x4) != 0) sizeStride = ptank->dataStride[index];
            ++index;
        }
        if ((dataFlags & 0x8) != 0) {
            // The position's variables: its stride stays when the matrix is not in updateFlags.
            posIn = ptank->dataInPtrs[index];
            posOut = ptank->dataOutPtrs[index];
            if ((ptank->updateFlags & 0x8) != 0) posStride = ptank->dataStride[index];
            ++index;
        }
        if ((dataFlags & 0x20) != 0) {
            rotIn = ptank->dataInPtrs[index];
            rotOut = ptank->dataOutPtrs[index];
            if ((ptank->updateFlags & 0x20) != 0) rotStride = ptank->dataStride[index];
            ++index;
        }
        if ((dataFlags & 0x80) != 0) {
            texIn = ptank->dataInPtrs[index];
            texOut = ptank->dataOutPtrs[index];
            if ((ptank->updateFlags & 0x80) != 0) texStride = ptank->dataStride[index];
        }
    }

    const int32_t objSize = emitter->prtClass->objSize;
    // The bounding sphere's centre: the emitter frame's position (TOC 0.0f without one).
    float cx = 0.0f;
    float cy = 0.0f;
    float cz = 0.0f;
    if (stdProp->ltm != nullptr) {
        cx = stdProp->ltm->pos.x;
        cz = stdProp->ltm->pos.z;
        cy = stdProp->ltm->pos.y;
    }
    float maxDistSq = 0.0f;
    int32_t live = 0;
    const int32_t numPrt = batch->numPrt;
    if (numPrt > 0) {
        // The size scale of the matrix path (f26 / f25): set in the same iteration before every read
        // (the original's registers start with the caller's values; they are never read then).
        float scaleX = 0.0f;
        float scaleY = 0.0f;
        uint8_t* src = RpPrtStdBatchParticles(batch);
        uint8_t* dst = src;
        for (int32_t i = 0; i < numPrt; ++i, src += objSize) {
            const float currTime = LoadF(src, 0x4);
            const float endTime = LoadF(src, 0x8);
            if (endTime > currTime) {
                const float time = dt + currTime;
                float t = time * LoadF(src, 0xc);
                StoreF(src, 0x4, time);
                if (t > 1.0f) t = 1.0f;

                // BUG(original): the velocity is read at prtVelocity even when the class has none (offset
                // -1: the bytes before the particle) by the position and matrix paths below.
                uint8_t* const vel = src + g_offsets.prtVelocity;
                uint8_t* const size = src + g_offsets.prtSize;
                if (g_offsets.prtVelocity >= 0) {
                    const float k = dt * stdProp->unk1c;
                    const float vz = LoadF(vel, 0x8);
                    const float vx = LoadF(vel, 0x0);
                    const float vy = LoadF(vel, 0x4);
                    const float dz = ppc::fmsubs(dt, stdProp->force.z, k * vz);
                    const float dx = ppc::fmsubs(dt, stdProp->force.x, k * vx);
                    const float dy = ppc::fmsubs(dt, stdProp->force.y, k * vy);
                    StoreF(vel, 0x8, vz + dz);
                    StoreF(vel, 0x0, vx + dx);
                    StoreF(vel, 0x4, vy + dy);
                }
                if (g_offsets.prtPosition >= 0) {
                    uint8_t* const pos = src + g_offsets.prtPosition;
                    StoreF(pos, 0x0, ppc::fmadds(dt, LoadF(vel, 0x0), LoadF(pos, 0x0)));
                    StoreF(pos, 0x4, ppc::fmadds(dt, LoadF(vel, 0x4), LoadF(pos, 0x4)));
                    StoreF(pos, 0x8, ppc::fmadds(dt, LoadF(vel, 0x8), LoadF(pos, 0x8)));
                }
                if (g_offsets.prtSize >= 0) {
                    const float w = ppc::fmadds(t, LoadF(size, 0x8), LoadF(size, 0x0));
                    const float h = ppc::fmadds(t, LoadF(size, 0xc), LoadF(size, 0x4));
                    scaleX = LoadF(size, 0x10);  // the previous size, for the matrix path's scale
                    scaleY = LoadF(size, 0x14);
                    StoreF(size, 0x10, w);
                    StoreF(size, 0x14, h);
                }
                if (dst != src) std::memcpy(dst, src, static_cast<uint32_t>(objSize));

                if (ptank != nullptr) {
                    // Position (0x1): the PTank's input position + dt * velocity.
                    if ((ptank->updateFlags & ptank->dataFlags & 0x1) != 0) {
                        if (g_offsets.prtVelocity >= 0) {
                            const float ny = ppc::fmadds(dt, LoadF(vel, 0x4), LoadF(posIn, 0x4));
                            const float nx = ppc::fmadds(dt, LoadF(vel, 0x0), LoadF(posIn, 0x0));
                            const float nz = ppc::fmadds(dt, LoadF(vel, 0x8), LoadF(posIn, 0x8));
                            const float dy = ny - cy;
                            StoreF(posOut, 0x4, ny);
                            const float dx = nx - cx;
                            StoreF(posOut, 0x0, nx);
                            const float dz = nz - cz;
                            StoreF(posOut, 0x8, nz);
                            const float d = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
                            if (!(maxDistSq > d)) maxDistSq = d;
                        }
                        posOut += posStride;
                    }
                    // Matrix (0x8).
                    if ((ptank->updateFlags & ptank->dataFlags & 0x8) != 0) {
                        if (g_offsets.prtSize >= 0) {
                            // The scale this frame: new size / previous size (1 when the previous is 0).
                            if (!(scaleX == 0.0f)) scaleX = LoadF(size, 0x10) / scaleX;
                            else scaleX = 1.0f;
                            if (!(scaleY == 0.0f)) scaleY = LoadF(size, 0x14) / scaleY;
                            else scaleY = 1.0f;
                        }
                        uint8_t* const in = posIn;
                        if (g_offsets.prtMatrix >= 0 || matrixProp != nullptr) {
                            // The input matrix's position taken out and zeroed, its right / up scaled (in the
                            // input array), times the particle's matrix (or the emitter's prtCnsMtx) into the
                            // output; then the old position + dt * velocity added to the product's.
                            const float pz = LoadF(in, 0x38);
                            const float py = LoadF(in, 0x34);
                            StoreF(in, 0x38, 0.0f);
                            StoreF(in, 0x34, 0.0f);
                            const float px = LoadF(in, 0x30);
                            StoreF(in, 0x30, 0.0f);
                            if (g_offsets.prtSize >= 0) {
                                StoreF(in, 0x00, scaleX * LoadF(in, 0x00));
                                StoreF(in, 0x04, scaleX * LoadF(in, 0x04));
                                StoreF(in, 0x08, scaleX * LoadF(in, 0x08));
                                StoreF(in, 0x10, scaleY * LoadF(in, 0x10));
                                StoreF(in, 0x14, scaleY * LoadF(in, 0x14));
                                StoreF(in, 0x18, scaleY * LoadF(in, 0x18));
                            }
                            const uint8_t* mtx = g_offsets.prtMatrix >= 0 ? src + g_offsets.prtMatrix : matrixProp;
                            RwMatrix a;
                            RwMatrix b;
                            RwMatrix product;
                            std::memcpy(&a, in, sizeof(RwMatrix));
                            std::memcpy(&b, mtx, sizeof(RwMatrix));
                            RwMatrixMultiply(&product, &a, &b);
                            // The PS3 stores the product with stvx, i.e. at the output address rounded down to
                            // 16 (the PTank's matrix array is 16-byte aligned, stride 0x40); natively at posOut.
                            std::memcpy(posOut, &product, sizeof(RwMatrix));
                            const float az = ppc::fmadds(dt, LoadF(vel, 0x8), pz);
                            const float ax = ppc::fmadds(dt, LoadF(vel, 0x0), px);
                            const float ay = ppc::fmadds(dt, LoadF(vel, 0x4), py);
                            MatrixPositionAdd(posOut, ax, ay, az, cx, cy, cz, &maxDistSq);
                        } else {
                            // No particle or emitter matrix: right / flags, up and at copied (not the pads or
                            // the position) when the arrays differ.
                            // BUG(original): the size scale is applied to the input after the copy (the output
                            // keeps the unscaled axes unless in == out), and the position is not zeroed: the
                            // output's position gets the input's added (doubled when in == out).
                            if (posOut != in) {
                                std::memcpy(posOut, in, 0x1c);
                                std::memcpy(posOut + 0x20, in + 0x20, 0xc);
                            }
                            const float pz = LoadF(in, 0x38);
                            const float py = LoadF(in, 0x34);
                            const float px = LoadF(in, 0x30);
                            if (g_offsets.prtSize >= 0) {
                                StoreF(in, 0x00, scaleX * LoadF(in, 0x00));
                                StoreF(in, 0x04, scaleX * LoadF(in, 0x04));
                                StoreF(in, 0x08, scaleX * LoadF(in, 0x08));
                                StoreF(in, 0x10, scaleY * LoadF(in, 0x10));
                                StoreF(in, 0x14, scaleY * LoadF(in, 0x14));
                                StoreF(in, 0x18, scaleY * LoadF(in, 0x18));
                            }
                            const float az = ppc::fmadds(dt, LoadF(vel, 0x8), pz);
                            const float ax = ppc::fmadds(dt, LoadF(vel, 0x0), px);
                            const float ay = ppc::fmadds(dt, LoadF(vel, 0x4), py);
                            MatrixPositionAdd(posOut, ax, ay, az, cx, cy, cz, &maxDistSq);
                        }
                        posOut += posStride;
                    }
                    // Size (0x4).
                    if ((ptank->updateFlags & ptank->dataFlags & 0x4) != 0) {
                        if (g_offsets.prtSize >= 0) {
                            StoreF(sizeOut, 0x0, ppc::fmadds(t, LoadF(size, 0x8), LoadF(size, 0x0)));
                            StoreF(sizeOut, 0x4, ppc::fmadds(t, LoadF(size, 0xc), LoadF(size, 0x4)));
                        } else if (sizeOut != sizeIn) {
                            CopyWords(sizeOut, sizeIn, 2);
                        }
                        sizeOut += sizeStride;
                    }
                    // Colour (0x2): RwRGBA bytes, each fctiwz(start + t * delta) truncated to its low byte.
                    if ((ptank->updateFlags & ptank->dataFlags & 0x2) != 0) {
                        if (g_offsets.prtColor >= 0) {
                            const uint8_t* const color = src + g_offsets.prtColor;
                            for (int32_t k = 0; k < 4; ++k) {
                                const float c = ppc::fmadds(t, LoadF(color, 0x10 + k * 4), LoadF(color, k * 4));
                                colOut[k] = static_cast<uint8_t>(ppc::fctiwz(c));
                            }
                        } else if (colOut != colIn) {
                            for (int32_t k = 0; k < 4; ++k) colOut[k] = colIn[k];
                        }
                        colOut += colStride;
                    }
                    // 2 tex coords (0x80).
                    if ((ptank->updateFlags & ptank->dataFlags & 0x80) != 0) {
                        if (g_offsets.prtTexCoords >= 0) {
                            const uint8_t* const uv = src + g_offsets.prtTexCoords;
                            StoreF(texOut, 0x0, ppc::fmadds(t, LoadF(uv, 0x10), LoadF(uv, 0x0)));
                            StoreF(texOut, 0x4, ppc::fmadds(t, LoadF(uv, 0x14), LoadF(uv, 0x4)));
                            StoreF(texOut, 0x8, ppc::fmadds(t, LoadF(uv, 0x18), LoadF(uv, 0x8)));
                            StoreF(texOut, 0xc, ppc::fmadds(t, LoadF(uv, 0x1c), LoadF(uv, 0xc)));
                        } else if (texOut != texIn) {
                            CopyWords(texOut, texIn, 4);
                        }
                        texOut += texStride;
                    }
                    // 2D rotation (0x20).
                    if ((ptank->updateFlags & ptank->dataFlags & 0x20) != 0) {
                        if (g_offsets.prt2DRotate >= 0) {
                            const uint8_t* const rot = src + g_offsets.prt2DRotate;
                            StoreF(rotOut, 0x0, ppc::fmadds(t, LoadF(rot, 0x4), LoadF(rot, 0x0)));
                        } else if (rotOut != rotIn) {
                            CopyWords(rotOut, rotIn, 1);
                        }
                        rotOut += rotStride;
                    }
                }
                dst += objSize;
                ++live;
            }
            // Every particle's input elements, live or dead.
            posIn += posStride;
            colIn += colStride;
            texIn += texStride;
            sizeIn += sizeStride;
            rotIn += rotStride;
        }
    }

    batch->numPrt = live;
    if (ptank != nullptr) {
        ptank->numPrt += live;
        const uint32_t dataFlags = ptank->dataFlags;
        int32_t index = 0;
        if ((dataFlags & 0x1) != 0) {
            ptank->dataInPtrs[0] = posIn;
            ptank->dataOutPtrs[0] = posOut;
            index = 1;
        }
        if ((dataFlags & 0x2) != 0) {
            ptank->dataInPtrs[index] = colIn;
            ptank->dataOutPtrs[index] = colOut;
            ++index;
        }
        if ((dataFlags & 0x4) != 0) {
            ptank->dataInPtrs[index] = sizeIn;
            ptank->dataOutPtrs[index] = sizeOut;
            ++index;
        }
        if ((dataFlags & 0x8) != 0) {
            ptank->dataInPtrs[index] = posIn;
            ptank->dataOutPtrs[index] = posOut;
            ++index;
        }
        if ((dataFlags & 0x20) != 0) {
            ptank->dataInPtrs[index] = rotIn;
            ptank->dataOutPtrs[index] = rotOut;
            ++index;
        }
        if ((dataFlags & 0x80) != 0) {
            ptank->dataInPtrs[index] = texIn;
            ptank->dataOutPtrs[index] = texOut;
        }
    }
    if (emitter->boundingSphere < maxDistSq) emitter->boundingSphere = maxDistSq;
    return batch;
}

}  // namespace rpprtstd
