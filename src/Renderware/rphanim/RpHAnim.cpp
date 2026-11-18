// RpHAnim.cpp - see RpHAnim.h.
#include "Renderware/rphanim/RpHAnim.h"

#include <cstdint>
#include <cstring>
#include <limits>

#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwFrameList.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "Renderware/rwcore/RwSList.h"
#include "Renderware/rwcore/RwStream.h"
#include "crt/ppc_ops.h"
#include "k2000/core/Stub.h"

namespace {
// RwStreamReadInt32 for one word: the little-endian stream word to native. 0 on a short read.
int32_t ReadInt32(RwStream* stream, void* out) {
    uint8_t b[4];
    if (RwStreamRead(stream, b, 4) != 4) return 0;
    const uint32_t v = static_cast<uint32_t>(b[0]) | (static_cast<uint32_t>(b[1]) << 8) |
                       (static_cast<uint32_t>(b[2]) << 16) | (static_cast<uint32_t>(b[3]) << 24);
    *static_cast<uint32_t*>(out) = v;
    return 1;
}
}  // namespace

// 0x006e7d20 HAnimStreamRead_maybe
RwStream* HAnimStreamRead(RwStream* stream, RwInt32 /*length*/, RwFrame* frame) {
    RwInt32 version = 0;
    if (ReadInt32(stream, &version) == 0 || version != 0x100) return nullptr;
    if (ReadInt32(stream, &frame->hanimID) == 0) return nullptr;
    RwInt32 numNodes = 0;
    if (ReadInt32(stream, &numNodes) == 0) return nullptr;
    if (numNodes < 1) return stream;
    RwInt32 flags = 0, maxKeyFrameSize = 0;
    if (ReadInt32(stream, &flags) == 0 || ReadInt32(stream, &maxKeyFrameSize) == 0) return nullptr;
    // RwFreeListAlloc(hierarchy free list, 0x3011e), cleared.
    RpHAnimHierarchy* hierarchy = static_cast<RpHAnimHierarchy*>(RwMalloc(sizeof(RpHAnimHierarchy), 0x3011e));
    *hierarchy = RpHAnimHierarchy{};
    hierarchy->currentAnim = RtAnimInterpolatorCreate(numNodes, maxKeyFrameSize);
    hierarchy->parentFrame = frame;
    hierarchy->flags = flags;
    hierarchy->parentHierarchy = hierarchy;
    hierarchy->numNodes = numNodes;
    if ((flags & 2) == 0) {
        uint8_t* raw = static_cast<uint8_t*>(RwMalloc(numNodes * sizeof(RwMatrix) + 0xf, 0x3011e));
        hierarchy->pMatrixArrayUnaligned = raw;
        hierarchy->pMatrixArray = reinterpret_cast<RwMatrix*>((reinterpret_cast<uintptr_t>(raw) + 0xf) & ~uintptr_t(0xf));
    } else {
        hierarchy->pMatrixArrayUnaligned = nullptr;
        hierarchy->pMatrixArray = nullptr;
    }
    RpHAnimNodeInfo* nodes = static_cast<RpHAnimNodeInfo*>(RwMalloc(numNodes * sizeof(RpHAnimNodeInfo), 0x3011e));
    hierarchy->pNodeInfo = nodes;
    for (RwInt32 i = 0; i < hierarchy->numNodes; ++i) {
        if (ReadInt32(stream, &nodes[i].nodeID) == 0) return nullptr;
        if (ReadInt32(stream, &nodes[i].nodeIndex) == 0) return nullptr;
        if (ReadInt32(stream, &nodes[i].flags) == 0) return nullptr;
        nodes[i].pFrame = nullptr;
    }
    frame->hanimHierarchy = hierarchy;
    return stream;
}

// 0x006e8330 HAnimFrameDestructor_maybe
void HAnimFrameDestructor(RwFrame* frame) {
    RpHAnimHierarchy* hierarchy = frame->hanimHierarchy;
    if (hierarchy != nullptr) {
        for (RwInt32 i = 0; i < hierarchy->numNodes; ++i) hierarchy->pNodeInfo[i].pFrame = nullptr;
        RwFrame* parent = hierarchy->parentFrame;
        if (parent == frame) {
            if ((hierarchy->flags & 1) == 0) {  // not a sub-hierarchy (rpHANIMHIERARCHYSUBHIERARCHY)
                if ((hierarchy->flags & 2) == 0) RwFree(hierarchy->pMatrixArrayUnaligned);  // rpHANIMHIERARCHYNOMATRICES
                RwFree(hierarchy->pNodeInfo);
            }
            hierarchy->pMatrixArrayUnaligned = nullptr;
            hierarchy->pMatrixArray = nullptr;
            hierarchy->pNodeInfo = nullptr;
            RtAnimInterpolatorDestroy(hierarchy->currentAnim);
            RwFree(hierarchy);  // RwFreeListFree (the hierarchy free list: the host heap here)
            if (parent != nullptr) parent->hanimHierarchy = nullptr;
        }
        frame->hanimHierarchy = nullptr;
    }
    frame->hanimID = -1;
}

// 0x006e62f8 RpHAnimFrameGetHierarchy
RpHAnimHierarchy* RpHAnimFrameGetHierarchy(RwFrame* frame) { return frame->hanimHierarchy; }

// 0x006e6330 RpHAnimFrameGetID
RwInt32 RpHAnimFrameGetID(RwFrame* frame) { return frame->hanimID; }

// 0x006e88c0 RpHAnimStdKeyFrameStreamRead
RtAnimAnimation* RpHAnimStdKeyFrameStreamRead(RwStream* stream, RtAnimAnimation* animation) {
    RpHAnimStdKeyFrame* frames = static_cast<RpHAnimStdKeyFrame*>(animation->pFrames);
    for (RwInt32 i = 0; i < animation->numFrames; ++i) {
        RpHAnimStdKeyFrame* frame = &frames[i];
        // RwStreamReadReal(stream, &frame->time, 0x20): time, the quaternion (imag xyz, real), the translation.
        if (RwStreamRead(stream, &frame->time, 0x20) == 0) return nullptr;
        uint32_t previous = 0;  // RwStreamReadInt32: the previous frame's byte offset in the stream's 0x24-byte frames
        if (RwStreamRead(stream, &previous, 4) == 0) return nullptr;
        frame->prevFrame = frames + previous / 0x24;
    }
    return animation;
}

namespace {
// The scheme 2 StreamRead stand-in (0x71f7e8): reads nothing. STUB(C2.9): no level has scheme 2 animations.
RtAnimAnimation* CompressedKeyFrameStreamRead(RwStream* /*stream*/, RtAnimAnimation* /*animation*/) {
    DOTD_STUB_ONCE("RtCompressedKeyFrameStreamRead 0x71f7e8 (C2.9): scheme 2 animations are not read");
    return nullptr;
}
}  // namespace

namespace {
// The TOC constants of the scheme 1 callbacks (lib TOC 0xc25974 - 0x3e7c ..): the slerp's acosf / sinf (inlined
// Dinkumware polynomials, the same in 0x6e8e48 and 0x6e89c0) and the near-equal threshold.
inline RwReal Word(uint32_t bits) {
    RwReal value;
    std::memcpy(&value, &bits, 4);
    return value;
}
const RwReal kNearOne = Word(0x3f7fbe77);       // 0.999f [c21b04]: at or above it the quaternions are lerped
const RwReal kPi = Word(0x40490fdb);            // [c21b08]
const RwReal kInvSinPi = Word(0x476a0ea1);      // [c21b0c] 1 / sin(kPi)
const RwReal kHalfPi = Word(0x3fc90fdb);        // [c21b10]
const RwReal kInvSinHalfPi = Word(0x3f800001);  // [c21b14]
const RwReal kAcosP1 = Word(0x3811ef08);        // [c21b18]
const RwReal kAcosP0 = Word(0x3a4f7f04);        // [c21b1c]
const RwReal kAcosP2 = Word(0x3d241146);        // [c21b20]
const RwReal kAcosP3 = Word(0x3e4e0aa8);        // [c21b24]
const RwReal kAcosP4 = Word(0x3ea6b090);        // [c21b28]
const RwReal kSixth = Word(0x3e2aaaab);         // [c21b2c] 1/6 (acos p5 and sin s1)
const RwReal kAcosQ1 = Word(0x3d9dc62e);        // [c21b30]
const RwReal kAcosQ0 = Word(0x3f303361);        // [c21b34]
const RwReal kAcosQ2 = Word(0x4001572d);        // [c21b38]
const RwReal kAcosQ3 = Word(0x4019d139);        // [c21b3c]
const RwReal kPio2Lo = Word(0x33a22168);        // [c21b40]
const RwReal kPio2Hi = Word(0x3fc90fda);        // [c21b44]
const RwReal kSinS6 = Word(0x2f2ec9d3);         // [c21b48]
const RwReal kSinS5 = Word(0x32d72f34);         // [c21b4c]
const RwReal kSinS4 = Word(0x3638ef1b);         // [c21b50]
const RwReal kSinS3 = Word(0x39500d01);         // [c21b54]
const RwReal kSinS2 = Word(0x3c088889);         // [c21b58]
const RwReal kPiHi = Word(0x40490fda);          // [c21b60]

// The acos polynomial p(z) (0x6e8f94..0x6e900c order: one chain) and q(z) (the other).
RwReal AcosP(RwReal z) {
    RwReal p = ppc::fmadds(z, kAcosP1, kAcosP0);
    p = ppc::fmsubs(z, p, kAcosP2);
    p = ppc::fmadds(z, p, kAcosP3);
    p = ppc::fmsubs(z, p, kAcosP4);
    return ppc::fmadds(z, p, kSixth);
}
RwReal AcosQ(RwReal z) {
    RwReal q = ppc::fmsubs(z, kAcosQ1, kAcosQ0);
    q = ppc::fmadds(z, q, kAcosQ2);
    q = ppc::fmsubs(z, q, kAcosQ3);
    return ppc::fmadds(z, q, 1.0f);
}
// The sin polynomial (0x6e9028 / 0x6e9078).
RwReal SinPoly(RwReal x) {
    const RwReal z = x * x;
    RwReal s = ppc::fmsubs(z, kSinS6, kSinS5);
    const RwReal v = z * x;
    s = ppc::fmadds(z, s, kSinS4);
    s = ppc::fmsubs(z, s, kSinS3);
    s = ppc::fmadds(z, s, kSinS2);
    s = ppc::fmsubs(z, s, kSixth);
    return ppc::fmadds(v, s, x);
}

// The angle between the quaternions (acosf of dot, inlined, branching on the bits like Dinkumware's) and 1 / its sine.
void SlerpAngle(RwReal dot, RwReal* thetaOut, RwReal* invSinOut) {
    uint32_t bits;
    std::memcpy(&bits, &dot, 4);
    const int32_t sbits = static_cast<int32_t>(bits);
    const int32_t ax = static_cast<int32_t>(bits & 0x7fffffffu);
    RwReal theta;
    if (ax > 0x3f7fffff) {
        // |dot| >= 1 (or NaN): no polynomial.
        if (sbits <= 0) {
            *thetaOut = kPi;
            *invSinOut = kInvSinPi;
        } else {
            *thetaOut = 0.0f;
            *invSinOut = std::numeric_limits<RwReal>::infinity();  // fdivs 1.0f / 0.0f
        }
        return;
    }
    if (ax <= 0x3effffff) {
        if (ax <= 0x23000000) {
            *thetaOut = kHalfPi;
            *invSinOut = kInvSinHalfPi;
            return;
        }
        // |dot| < 0.5: pi/2 - (dot + dot * r(dot^2)).
        const RwReal z = dot * dot;
        const RwReal p = AcosP(z);
        const RwReal q = AcosQ(z);
        RwReal r = z * p;
        r = r / q;
        r = dot * r;
        RwReal w = kPio2Lo - r;
        w = dot - w;
        theta = kPio2Hi - w;
    } else if (sbits < 0) {
        // dot <= -0.5: pi - 2 * (s + s * r), s = sqrt((1 + dot) / 2).
        const RwReal z = ppc::fmadds(dot, 0.5f, 0.5f);
        const RwReal s = rwSqrt(z);
        const RwReal p = AcosP(z);
        const RwReal q = AcosQ(z);
        RwReal r = z * p;
        r = r / q;
        const RwReal w = ppc::fmsubs(s, r, kPio2Lo);
        theta = ppc::fmadds(s + w, -2.0f, kPiHi);
    } else {
        // dot >= 0.5: 2 * (df + (c + s * r)), s = sqrt((1 - dot) / 2), df = s with the low 12 bits cleared.
        RwReal z = 1.0f - dot;
        z = z * 0.5f;
        const RwReal s = rwSqrt(z);
        uint32_t sBits;
        std::memcpy(&sBits, &s, 4);
        const RwReal df = Word(sBits & 0xfffff000u);
        const RwReal p = AcosP(z);
        const RwReal q = AcosQ(z);
        const RwReal c = (z - df * df) / (s + df);
        RwReal r = z * p;
        r = r / q;
        const RwReal w = ppc::fmadds(s, r, c);
        theta = df + w;
        theta = theta + theta;
    }
    *thetaOut = theta;
    *invSinOut = 1.0f / SinPoly(theta);
}

// The shared body of RpHAnimKeyFrameInterpolate 0x6e8e48 and RpHAnimKeyFrameBlend 0x6e89c0 (identical after the
// blend factor): every input is read first, the translation lerped and stored, the second quaternion negated in place
// when the dot product is negative (the key frame itself changes, as in RW), then slerp (lerp at or above kNearOne).
void BlendQuatTrans(RtQuat* outQ, RwV3d* outT, const RtQuat* q1, const RwV3d* t1, RtQuat* q2, const RwV3d* t2,
                    RwReal alpha) {
    const RwReal yy = q1->imag.y * q2->imag.y;
    const RwReal x1 = q1->imag.x, x2 = q2->imag.x;
    const RwReal y2 = q2->imag.y;
    const RwReal z1 = q1->imag.z, z2 = q2->imag.z;
    const RwReal w1 = q1->real, w2 = q2->real;
    const RwReal t1x = t1->x, t1y = t1->y, t1z = t1->z;
    const RwReal dx = t2->x - t1x, dy = t2->y - t1y, dz = t2->z - t1z;
    RwReal dot = ppc::fmadds(x1, x2, yy);
    dot = ppc::fmadds(z1, z2, dot);
    dot = ppc::fmadds(w1, w2, dot);
    outT->z = ppc::fmadds(alpha, dz, t1z);
    outT->x = ppc::fmadds(alpha, dx, t1x);
    outT->y = ppc::fmadds(alpha, dy, t1y);
    if (dot < 0.0f) {
        q2->imag.x = -x2;
        q2->imag.y = -y2;
        q2->imag.z = -z2;
        q2->real = -w2;
        dot = -dot;
    }
    RwReal scale1 = 1.0f - alpha;
    RwReal scale2 = alpha;
    if (!(dot >= kNearOne)) {
        RwReal theta, invSin;
        SlerpAngle(dot, &theta, &invSin);
        const RwReal a2 = theta * scale2;
        const RwReal a1 = theta * scale1;
        scale2 = SinPoly(a2) * invSin;
        scale1 = SinPoly(a1) * invSin;
    }
    const RwReal w = scale2 * q2->real;
    const RwReal x = scale2 * q2->imag.x;
    const RwReal y = scale2 * q2->imag.y;
    const RwReal z = scale2 * q2->imag.z;
    const RwReal rw = ppc::fmadds(scale1, q1->real, w);
    const RwReal rx = ppc::fmadds(scale1, q1->imag.x, x);
    const RwReal ry = ppc::fmadds(scale1, q1->imag.y, y);
    const RwReal rz = ppc::fmadds(scale1, q1->imag.z, z);
    outQ->real = rw;
    outQ->imag.x = rx;
    outQ->imag.y = ry;
    outQ->imag.z = rz;
}
}  // namespace

// 0x006e84d8 RpHAnimKeyFrameApply (RpHAnimKeyFrameApply)
void RpHAnimKeyFrameApply(void* voidMatrix, void* voidIFrame) {
    RwMatrix* matrix = static_cast<RwMatrix*>(voidMatrix);
    const RpHAnimInterpFrame* frame = static_cast<const RpHAnimInterpFrame*>(voidIFrame);
    const RwReal qw = frame->q.real, qy = frame->q.imag.y, qx = frame->q.imag.x, qz = frame->q.imag.z;
    const RwReal yy = qy * qy;
    const RwReal xx = qx * qx;
    const RwReal zw = qz * qw;
    const RwReal zz = qz * qz;
    const RwReal xw = qx * qw;
    const RwReal yw = qy * qw;
    matrix->flags = 3;  // rwMATRIXTYPEORTHONORMAL; the pads are not written
    matrix->pos.z = 0.0f;
    matrix->pos.x = 0.0f;
    matrix->pos.y = 0.0f;
    const RwReal yz = qy * qz;
    const RwReal xz = qx * qz;
    const RwReal xy = qx * qy;
    RwReal atZ = xx + yy;
    RwReal upY = xx + zz;
    RwReal rightX = yy + zz;
    RwReal atY = yz - xw;
    RwReal atX = xz + yw;
    RwReal upX = xy - zw;
    RwReal upZ = yz + xw;
    RwReal rightY = xy + zw;
    RwReal rightZ = xz - yw;
    atZ = ppc::fmadds(atZ, -2.0f, 1.0f);
    upY = ppc::fmadds(upY, -2.0f, 1.0f);
    rightX = ppc::fmadds(rightX, -2.0f, 1.0f);
    matrix->at.z = atZ;
    matrix->up.y = upY;
    matrix->right.x = rightX;
    matrix->at.y = atY + atY;
    matrix->at.x = atX + atX;
    matrix->up.x = upX + upX;
    matrix->up.z = upZ + upZ;
    matrix->right.y = rightY + rightY;
    matrix->right.z = rightZ + rightZ;
    matrix->pos.z = frame->t.z;
    matrix->pos.x = frame->t.x;
    matrix->pos.y = frame->t.y;
}

// 0x006e8e48 RpHAnimKeyFrameInterpolate
void RpHAnimKeyFrameInterpolate(void* voidOut, void* voidIn1, void* voidIn2, RwReal time, void* /*customData*/,
                                RwInt32 /*nodeIndex*/) {
    RpHAnimInterpFrame* out = static_cast<RpHAnimInterpFrame*>(voidOut);
    RpHAnimStdKeyFrame* in1 = static_cast<RpHAnimStdKeyFrame*>(voidIn1);
    RpHAnimStdKeyFrame* in2 = static_cast<RpHAnimStdKeyFrame*>(voidIn2);
    const RwReal start = in1->time;
    const RwReal alpha = (time - start) / (in2->time - start);
    BlendQuatTrans(&out->q, &out->t, &in1->q, &in1->t, &in2->q, &in2->t, alpha);
}

// 0x006e89c0 RpHAnimKeyFrameBlend
void RpHAnimKeyFrameBlend(void* voidOut, void* voidIn1, void* voidIn2, RwReal alpha) {
    RpHAnimInterpFrame* out = static_cast<RpHAnimInterpFrame*>(voidOut);
    RpHAnimInterpFrame* in1 = static_cast<RpHAnimInterpFrame*>(voidIn1);
    RpHAnimInterpFrame* in2 = static_cast<RpHAnimInterpFrame*>(voidIn2);
    BlendQuatTrans(&out->q, &out->t, &in1->q, &in1->t, &in2->q, &in2->t, alpha);
}

// 0x006e86c8 RpHAnimKeyFrameAdd (RpHAnimKeyFrameAdd): out = in1 (x) in2 and the translations summed. The PS3 code
// stores partial products into out and reads in1 again afterwards, so an out that is in1 sees them: the loads and
// stores are in the original's order.
void RpHAnimKeyFrameAdd(void* voidOut, void* voidIn1, void* voidIn2) {
    RpHAnimInterpFrame* out = static_cast<RpHAnimInterpFrame*>(voidOut);
    RpHAnimInterpFrame* in1 = static_cast<RpHAnimInterpFrame*>(voidIn1);
    RpHAnimInterpFrame* in2 = static_cast<RpHAnimInterpFrame*>(voidIn2);
    RwReal f13 = in1->q.imag.z;
    RwReal f12 = in2->q.imag.y;
    RwReal f8 = f13 * f12;
    RwReal f9 = in2->q.imag.z;
    RwReal f6 = in1->q.imag.y;
    f12 = f6 * f12;
    RwReal f7 = in1->q.imag.x;
    RwReal f3 = in2->q.imag.x;
    RwReal f0 = in2->t.y;
    RwReal f4 = in1->t.y;
    f4 = f4 + f0;
    RwReal f11 = in2->t.x;
    RwReal f10 = in1->t.x;
    f10 = f10 + f11;
    RwReal f5 = in1->q.real;
    RwReal f2 = in2->q.real;
    f6 = ppc::fmsubs(f6, f9, f8);
    f7 = ppc::fmadds(f7, f3, f12);
    out->t.x = f10;
    out->q.imag.x = f6;
    f8 = in1->q.imag.x;
    f0 = f8 * f9;
    f11 = in2->q.imag.x;
    f9 = ppc::fmadds(f13, f9, f7);
    f13 = ppc::fmsubs(f13, f11, f0);
    f5 = ppc::fmsubs(f5, f2, f9);
    out->q.imag.y = f13;
    f0 = in1->q.imag.y;
    f0 = f0 * f11;
    out->q.real = f5;
    f12 = in2->q.imag.y;
    f10 = in1->q.real;
    f13 = ppc::fmadds(f12, f10, f13);
    f9 = in2->q.real;
    f11 = ppc::fmadds(f11, f10, f6);
    f8 = ppc::fmsubs(f8, f12, f0);
    out->q.imag.y = f13;
    f12 = in1->q.imag.y;
    out->q.imag.x = f11;
    f12 = ppc::fmadds(f12, f9, f13);
    f0 = in1->q.imag.x;
    f0 = ppc::fmadds(f0, f9, f11);
    out->q.imag.z = f8;
    f13 = in2->q.imag.z;
    f13 = ppc::fmadds(f13, f10, f8);
    out->q.imag.y = f12;
    out->q.imag.x = f0;
    out->q.imag.z = f13;
    f0 = in1->q.imag.z;
    f0 = ppc::fmadds(f0, f9, f13);
    out->q.imag.z = f0;
    out->t.y = f4;
    f0 = in1->t.z;
    f13 = in2->t.z;
    out->t.z = f0 + f13;
}

// 0x006e85d8 RpHAnimKeyFrameMulRecip (RpHAnimKeyFrameMulRecip): frame = start^-1 (x) frame (the quaternion by the
// start's reciprocal), the translation minus the start's.
void RpHAnimKeyFrameMulRecip(void* voidFrame, void* voidStart) {
    RpHAnimInterpFrame* frame = static_cast<RpHAnimInterpFrame*>(voidFrame);
    const RpHAnimInterpFrame* start = static_cast<const RpHAnimInterpFrame*>(voidStart);
    const RwReal sy = start->q.imag.y;
    const RwReal sx = start->q.imag.x;
    const RwReal sz = start->q.imag.z;
    const RwReal sw = start->q.real;
    RwReal norm = sy * sy;
    norm = ppc::fmadds(sx, sx, norm);
    norm = ppc::fmadds(sz, sz, norm);
    norm = ppc::fmadds(sw, sw, norm);
    // BUG(original): with a zero start quaternion the reciprocal is whatever the FPU registers f1, f2, f30, f31 held
    // (never set on that path); here 0.
    RwReal rw = 0.0f, rz = 0.0f, rx = 0.0f, ry = 0.0f;
    if (norm > 0.0f) {
        const RwReal inv = 1.0f / norm;
        const RwReal neg = -inv;
        rw = sw * inv;
        rz = sz * neg;
        rx = sx * neg;
        ry = sy * neg;
    }
    const RwReal fz = frame->q.imag.z;
    const RwReal fy = frame->q.imag.y;
    RwReal f6 = fz * rx;
    const RwReal fx = frame->q.imag.x;
    RwReal f7 = fy * rz;
    const RwReal tx = frame->t.x - start->t.x;
    const RwReal ty = frame->t.y - start->t.y;
    const RwReal fw = frame->q.real;
    RwReal f10 = fy * ry;
    RwReal f0 = fx * ry;
    const RwReal tz = frame->t.z - start->t.z;
    f6 = ppc::fmsubs(fx, rz, f6);
    f7 = ppc::fmsubs(fz, ry, f7);
    frame->t.x = tx;
    frame->t.y = ty;
    f10 = ppc::fmadds(fx, rx, f10);
    f0 = ppc::fmsubs(fy, rx, f0);
    frame->t.z = tz;
    RwReal f4 = ppc::fmadds(fy, rw, f6);
    RwReal f13 = ppc::fmadds(fx, rw, f7);
    f0 = ppc::fmadds(fz, rw, f0);
    RwReal f12 = ppc::fmadds(fz, rz, f10);
    f13 = ppc::fmadds(fw, rx, f13);
    f0 = ppc::fmadds(fw, rz, f0);
    f12 = ppc::fmsubs(fw, rw, f12);
    const RwReal f5 = ppc::fmadds(fw, ry, f4);
    frame->q.imag.x = f13;
    frame->q.imag.z = f0;
    frame->q.real = f12;
    frame->q.imag.y = f5;
}

// 0x006e63b8 RpHAnimHierarchyUpdateMatrices
RwBool RpHAnimHierarchyUpdateMatrices(RpHAnimHierarchy* hierarchy) {
    const RwInt32 flags = hierarchy->flags;
    if ((flags & rpHANIMHIERARCHYNOMATRICES) != 0) {
        // STUB(C2.9): 0x6e6430..0x6e672c, the hierarchy without a matrix array (the frames' modelling matrices and LTMs
        // are written instead). No hierarchy of LVL010 or its STR files has the flag (all 0x4000).
        DOTD_STUB_ONCE("RpHAnimHierarchyUpdateMatrices 0x6e63b8: rpHANIMHIERARCHYNOMATRICES hierarchy (C2.9)");
        return 1;
    }
    // The stack matrices (sp+0x70 the root LTM, sp+0x130 the local-space identity); their pads hold stack bytes in the
    // original (only the matrices' w lanes see them).
    RwMatrix rootLTM = {};
    RwMatrix identity = {};
    RwMatrix* parent = &rootLTM;
    RwFrame* chainFrame = nullptr;
    bool ltms = (flags & rpHANIMHIERARCHYUPDATELTMS) != 0;
    bool chain = true;  // the root LTM from the parent frame's ancestors (0x6e6754)
    if ((flags & rpHANIMHIERARCHYSUBHIERARCHY) != 0 && hierarchy->rootParentOffset != -1) {
        RpHAnimHierarchy* parentHierarchy = hierarchy->parentHierarchy;
        parent = parentHierarchy->pMatrixArray + hierarchy->rootParentOffset;
        if ((flags & 0x6000) != 0x6000) {
            chain = false;
        } else {
            chainFrame = parentHierarchy->parentFrame;
        }
    } else if ((flags & rpHANIMHIERARCHYLOCALSPACEMATRICES) != 0) {
        RwMatrixSetIdentity(&identity);
        parent = &identity;
        chain = ltms;
        chainFrame = hierarchy->parentFrame;
    } else {
        chainFrame = hierarchy->parentFrame;
    }
    if (chain) {
        RwFrame* above = chainFrame != nullptr ? static_cast<RwFrame*>(chainFrame->object.parent) : nullptr;
        if (above == nullptr) {
            RwMatrixSetIdentity(&rootLTM);
        } else if ((above->root->object.privateFlags & 3) == 0) {  // RwFrameDirty 0x74a428: clean
            rootLTM = *RwFrameGetLTM(above);
        } else {
            // The LTM from the modelling matrices up the hierarchy.
            rootLTM = above->modelling;
            for (RwFrame* frame = static_cast<RwFrame*>(above->object.parent); frame != nullptr;
                 frame = static_cast<RwFrame*>(frame->object.parent)) {
                const RwMatrix copy = rootLTM;
                RwMatrixMultiply(&rootLTM, &copy, &frame->modelling);
            }
        }
    }
    if (ltms) {
        // RwFrameUpdateObjects on the hierarchy's frame, inlined (0x6e6864): the root goes on the dirty list (natively
        // no list, see RwFrameUpdateObjects) and gets bit 2 when it was clean. PS3: only when the list is enabled
        // (0xc45c80).
        RwFrame* root = hierarchy->parentFrame->root;
        if ((root->object.privateFlags & 3) == 0) root->object.privateFlags |= 2;
    }
    RtAnimInterpolator* interpolator = hierarchy->currentAnim;
    RpHAnimNodeInfo* node = hierarchy->pNodeInfo;
    RwMatrix* matrix = hierarchy->pMatrixArray;
    const RwInt32 frameSize = interpolator->currentInterpKeyFrameSize;
    const RtAnimKeyFrameApplyCallBack apply = interpolator->keyFrameApplyCB;
    if (hierarchy->numNodes <= 0) return 1;
    const bool localSpace = (flags & rpHANIMHIERARCHYLOCALSPACEMATRICES) != 0;
    const bool modelling = (flags & rpHANIMHIERARCHYUPDATEMODELLINGMATRICES) != 0;
    uint8_t* frame = static_cast<uint8_t*>(RtAnimInterpolatorGetInterpFrame(interpolator, 0));
    RwMatrix* stack[543];  // sp+0x1b4 .. sp+0xa30
    RwMatrix** top = stack;
    RwMatrix local = {};  // sp+0xf0
    for (RwInt32 i = 0;;) {
        // The scheme 1 apply is inlined when the callback is RpHAnimKeyFrameApply (OPD 0xbfcb60): the same operations.
        apply(&local, frame);
        RwMatrixMultiply(matrix, &local, parent);
        RwFrame* nodeFrame = node->pFrame;
        if (nodeFrame != nullptr) {
            bool sync = false;
            if (modelling) {
                nodeFrame->modelling = local;
                if (!ltms) {
                    RwFrameUpdateObjects(nodeFrame);
                } else {
                    sync = true;
                }
            } else {
                sync = ltms;
            }
            if (sync) {
                if (localSpace) {
                    RwMatrixMultiply(&nodeFrame->ltm, matrix, &rootLTM);
                } else {
                    nodeFrame->ltm = *matrix;
                }
                nodeFrame->object.privateFlags = static_cast<RwUInt8>(((nodeFrame->object.privateFlags >> 3) << 3) | 8);
            }
        }
        switch (node->flags & 3) {
            case rpHANIMPOPPARENTMATRIX:
                parent = *--top;
                break;
            case rpHANIMPUSHPARENTMATRIX:
                *top++ = parent;
                parent = matrix;
                break;
            case 0:
                parent = matrix;
                break;
            default:  // push and pop: the parent stays
                break;
        }
        ++i;
        if (hierarchy->numNodes <= i) return 1;
        frame += frameSize;
        ++matrix;
        ++node;
    }
}

// 0x006e8070 _rpHAnimOpen_maybe
RwBool RpHAnimPluginOpen() {
    RtAnimInterpolatorInfo info = {};
    info.typeID = 1;
    info.interpKeyFrameSize = static_cast<RwInt32>(sizeof(RpHAnimInterpFrame));
    info.animKeyFrameSize = static_cast<RwInt32>(sizeof(RpHAnimStdKeyFrame));
    info.animKeyFrameSize2 = static_cast<RwInt32>(sizeof(RpHAnimStdKeyFrame));
    info.keyFrameApplyCB = RpHAnimKeyFrameApply;              // 0x6e84d8
    info.keyFrameBlendCB = RpHAnimKeyFrameBlend;              // 0x6e89c0
    info.keyFrameInterpolateCB = RpHAnimKeyFrameInterpolate;  // 0x6e8e48
    info.keyFrameAddCB = RpHAnimKeyFrameAdd;                  // 0x6e86c8
    info.keyFrameMulRecipCB = RpHAnimKeyFrameMulRecip;        // 0x6e85d8
    info.keyFrameStreamReadCB = RpHAnimStdKeyFrameStreamRead;  // 0x6e88c0
    info.keyFrameStreamWriteCB = nullptr;    // 0x6e87b0 RpHAnimStdKeyFrameStreamWrite: tooling only, never called
    info.keyFrameStreamGetSizeCB = nullptr;  // 0x6e85c0 RpHAnimStdKeyFrameStreamGetSize: tooling only, never called
    info.customDataSize = 0;
    RtAnimRegisterInterpolationScheme(&info);
    return 1;
}

// 0x0071f5c0 RtCompressedKeyFrameRegister_maybe
RwBool RtCompressedKeyFrameRegister() {
    RtAnimInterpolatorInfo info = {};
    info.typeID = 2;
    info.interpKeyFrameSize = static_cast<RwInt32>(sizeof(RpHAnimInterpFrame));  // 0x24
    info.animKeyFrameSize = 0x18;
    info.animKeyFrameSize2 = 0x18;
    // 0x71f3d8 apply, 0x71f968 blend, 0x71fdf0 interpolate, 0x71f4d8 add, 0x720580 mulrecip: STUB(C2.9) (no level has
    // scheme 2 animations: c25_anim_scan.py).
    info.keyFrameStreamReadCB = CompressedKeyFrameStreamRead;  // 0x71f7e8
    info.customDataSize = 0x18;
    return RtAnimRegisterInterpolationScheme(&info) != 0;
}

// 0x006e7510 RpHAnimHierarchyCreate
RpHAnimHierarchy* RpHAnimHierarchyCreate(RwInt32 numNodes, const RwInt32* nodeFlags, const RwInt32* nodeIDs, RwInt32 flags,
                                         RwInt32 maxKeyFrameSize) {
    // RWEngineInstance +0x118: the hierarchy free list (0x3011e), not cleared.
    RpHAnimHierarchy* hierarchy = static_cast<RpHAnimHierarchy*>(RwMalloc(sizeof(RpHAnimHierarchy), 0x3011e));
    *hierarchy = RpHAnimHierarchy{};
    hierarchy->currentAnim = RtAnimInterpolatorCreate(numNodes, maxKeyFrameSize);
    hierarchy->flags = flags;
    hierarchy->numNodes = numNodes;
    hierarchy->parentFrame = nullptr;
    if ((flags & rpHANIMHIERARCHYNOMATRICES) == 0) {
        uint8_t* raw = static_cast<uint8_t*>(RwMalloc((static_cast<RwUInt32>(numNodes) & 0x3ffffff) * 0x40 + 0xf, 0x3011e));
        hierarchy->pMatrixArrayUnaligned = raw;
        hierarchy->pMatrixArray = reinterpret_cast<RwMatrix*>((reinterpret_cast<uintptr_t>(raw) + 0xf) & ~uintptr_t(0xf));
    } else {
        hierarchy->pMatrixArrayUnaligned = nullptr;
        hierarchy->pMatrixArray = nullptr;
    }
    hierarchy->pNodeInfo = static_cast<RpHAnimNodeInfo*>(
        RwMalloc((static_cast<RwUInt32>(numNodes) & 0xfffffff) * static_cast<RwUInt32>(sizeof(RpHAnimNodeInfo)), 0x3011e));
    for (RwInt32 i = 0; i < numNodes; ++i) {
        RpHAnimNodeInfo* node = &hierarchy->pNodeInfo[i];
        node->pFrame = nullptr;
        if (nodeIDs != nullptr) node->nodeID = nodeIDs[i];
        node->nodeIndex = i;
        if (nodeFlags != nullptr) node->flags = nodeFlags[i];
    }
    hierarchy->parentHierarchy = hierarchy;
    return hierarchy;
}

// 0x006e7840 RpHAnimHierarchyCreateFromHierarchy
RpHAnimHierarchy* RpHAnimHierarchyCreateFromHierarchy(const RpHAnimHierarchy* hierarchy, RwInt32 flags,
                                                      RwInt32 maxKeyFrameSize) {
    RpHAnimHierarchy* created = RpHAnimHierarchyCreate(hierarchy->numNodes, nullptr, nullptr, flags, maxKeyFrameSize);
    for (RwInt32 i = 0; i < created->numNodes; ++i) {
        created->pNodeInfo[i].pFrame = nullptr;
        created->pNodeInfo[i].flags = hierarchy->pNodeInfo[i].flags;
        created->pNodeInfo[i].nodeIndex = hierarchy->pNodeInfo[i].nodeIndex;
        created->pNodeInfo[i].nodeID = hierarchy->pNodeInfo[i].nodeID;
    }
    return created;
}

namespace {
// RwFrameForAllChildren (baframe.c) with a callback that always returns its frame.
template <typename Callback>
void ForAllChildren(RwFrame* frame, Callback callback) {
    RwFrame* child = frame->child;
    while (child != nullptr) {
        RwFrame* next = child->next;
        callback(child);
        child = next;
    }
}

// 0x006e70f8 HAnimHierarchyAttachFrameCB_maybe: the nodes with this frame's id attach to it, then its children.
void AttachFrameCB(RwFrame* frame, RpHAnimHierarchy* hierarchy) {
    for (RwInt32 i = 0; i < hierarchy->numNodes; ++i) {
        RpHAnimNodeInfo* node = &hierarchy->pNodeInfo[i];
        if (frame->hanimID == node->nodeID) node->pFrame = frame;
    }
    RwFrameUpdateObjects(frame);
    ForAllChildren(frame, [&](RwFrame* child) { AttachFrameCB(child, hierarchy); });
}

// 0x006e7028 HAnimHierarchyAttachFrameIndexCB_maybe: only the nodes with the one id (data = hierarchy, id).
void AttachFrameIndexCB(RwFrame* frame, RpHAnimHierarchy* hierarchy, RwInt32 nodeID) {
    if (frame->hanimID == nodeID && 0 < hierarchy->numNodes) {
        for (RwInt32 i = 0; i < hierarchy->numNodes; ++i) {
            RpHAnimNodeInfo* node = &hierarchy->pNodeInfo[i];
            if (node->nodeID == nodeID) node->pFrame = frame;
        }
    }
    RwFrameUpdateObjects(frame);
    ForAllChildren(frame, [&](RwFrame* child) { AttachFrameIndexCB(child, hierarchy, nodeID); });
}
}  // namespace

// 0x006e8170 RpHAnimHierarchyAttach
RpHAnimHierarchy* RpHAnimHierarchyAttach(RpHAnimHierarchy* hierarchy) {
    RwFrame* frame = hierarchy->parentFrame;
    for (RwInt32 i = 0; i < hierarchy->numNodes; ++i) {
        RpHAnimNodeInfo* node = &hierarchy->pNodeInfo[i];
        if (frame->hanimID == node->nodeID) node->pFrame = frame;
    }
    RwFrameUpdateObjects(frame);
    ForAllChildren(frame, [&](RwFrame* child) { AttachFrameCB(child, hierarchy); });
    return hierarchy;
}

// 0x006e8248 RpHAnimHierarchyAttachFrameIndex
RpHAnimHierarchy* RpHAnimHierarchyAttachFrameIndex(RpHAnimHierarchy* hierarchy, RwInt32 nodeIndex) {
    RwFrame* frame = hierarchy->parentFrame;
    const RwInt32 nodeID = hierarchy->pNodeInfo[nodeIndex].nodeID;
    if (frame->hanimID == nodeID) {
        for (RwInt32 i = 0; i < hierarchy->numNodes; ++i) {
            RpHAnimNodeInfo* node = &hierarchy->pNodeInfo[i];
            if (node->nodeID == nodeID) node->pFrame = frame;
        }
    }
    RwFrameUpdateObjects(frame);
    ForAllChildren(frame, [&](RwFrame* child) { AttachFrameIndexCB(child, hierarchy, nodeID); });
    return hierarchy;
}

// 0x006e6240 RpHAnimHierarchyDetach
RpHAnimHierarchy* RpHAnimHierarchyDetach(RpHAnimHierarchy* hierarchy) {
    for (RwInt32 i = 0; i < hierarchy->numNodes; ++i) hierarchy->pNodeInfo[i].pFrame = nullptr;
    return hierarchy;
}

// 0x006e62b0 RpHAnimFrameSetHierarchy
RwBool RpHAnimFrameSetHierarchy(RwFrame* frame, RpHAnimHierarchy* hierarchy) {
    if (frame->hanimHierarchy != nullptr) frame->hanimHierarchy->parentFrame = nullptr;
    frame->hanimHierarchy = hierarchy;
    if (hierarchy == nullptr) return 1;
    hierarchy->parentFrame = frame;
    return 1;
}

// 0x006e6350 RpHAnimIDGetIndex
RwInt32 RpHAnimIDGetIndex(const RpHAnimHierarchy* hierarchy, RwInt32 id) {
    for (RwInt32 i = 0; i < hierarchy->numNodes; ++i) {
        if (hierarchy->pNodeInfo[i].nodeID == id) return i;
    }
    return -1;
}

// 0x006e7920 HAnimFrameCopyCB_maybe
void HAnimFrameCopy(RwFrame* dstFrame, const RwFrame* srcFrame) {
    const RpHAnimHierarchy* source = srcFrame->hanimHierarchy;
    dstFrame->hanimID = srcFrame->hanimID;
    if (source != nullptr && (source->flags & rpHANIMHIERARCHYSUBHIERARCHY) == 0) {
        RpHAnimHierarchy* created = RpHAnimHierarchyCreate(source->numNodes, nullptr, nullptr, source->flags,
                                                           source->currentAnim->maxInterpKeyFrameSize);
        for (RwInt32 i = 0; i < created->numNodes; ++i) {
            created->pNodeInfo[i].pFrame = nullptr;
            created->pNodeInfo[i].flags = source->pNodeInfo[i].flags;
            created->pNodeInfo[i].nodeIndex = source->pNodeInfo[i].nodeIndex;
            created->pNodeInfo[i].nodeID = source->pNodeInfo[i].nodeID;
        }
        dstFrame->hanimHierarchy = created;
        created->parentFrame = dstFrame;
    }
}
