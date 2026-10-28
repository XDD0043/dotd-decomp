//
// Reconstructed original translation unit: 0x241c78-0x2436e8 (GAME_TOC1, main_toc1), 22 functions, 13 live.
// Primary owner: Quat (not a registered class)
// Other owners: RtQuatRotate (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x241c78  Quat_Add  [dead]
//   [ ] 0x241cc0  Quat_Multiply
//   [ ] 0x241d78  Quat_ToMatrixNormalizing_maybe
//   [x] 0x241e48  Quat_ToMatrix
//   [ ] 0x241f18  Quat_Conjugate  [dead]
//   [ ] 0x241f48  Quat_LengthSquared  [dead]
//   [ ] 0x241f70  Quat_Inverse  [dead]
//   [ ] 0x241fd0  Quat_ToAxisAngle_maybe
//   [ ] 0x241ff8  Quat_Modulus_maybe  [dead]
//   [ ] 0x242020  Quat_Exp_maybe  [dead]
//   [x] 0x2420f8  Quat_FromMatrix
//   [ ] 0x242130  Quat_Rotate_maybe
//   [ ] 0x242158  RtQuatRotate_Thunk
//   [ ] 0x242180  Quat_Normalize
//   [ ] 0x242240  Quat_ToMatrixKeepPosition_maybe  [dead]
//   [ ] 0x242300  Quat_ToMatrixNormalizingKeepPosition_maybe  [dead]
//   [ ] 0x2423c8  Quat_Log_maybe
//   [ ] 0x2424a0  Quat_ToEulerAngles_maybe
//   [ ] 0x242648  Quat_FromMatrixNormalized_maybe
//   [x] 0x242728  Quat_Slerp
//   [ ] 0x242b40  Quat_FromTwoAxisAngles_maybe  [dead]
//   [ ] 0x243058  Quat_FromEulerDeg
#include "k2000/math/Quat.h"

#include <cstring>

#include "Renderware/rwcore/RwMatrix.h"
#include "crt/ppc_ops.h"
#include "crt/xatan.h"
#include "crt/xsinf.h"

// 0x00241e48 Quat_ToMatrix: the rotation part of `m` from the quaternion q = (x, y, z, w); flags = 3 (the
// identity bits cleared, orthonormal) and the position (0x30..0x38) zeroed. The pad at +0x3c stays.
// The diagonal is 1 - 2 * (the sum of two squares) through fmadds; the off-diagonals are (a -+ b) doubled.
void Quat_ToMatrix(const float* q, CMatrix34* m) {
    const float x = q[0];
    const float y = q[1];
    const float z = q[2];
    const float w = q[3];
    m->m_pos.x = 0.0f;
    m->m_pos.y = 0.0f;
    m->m_pos.z = 0.0f;
    m->m_ui32Flags = 3;
    const float xx = x * x;
    const float yy = y * y;
    const float zz = z * z;
    const float zw = z * w;
    const float xw = x * w;
    const float yw = y * w;
    const float yz = y * z;
    const float xz = x * z;
    const float xy = x * y;
    const float xxyy = xx + yy;
    const float xxzz = xx + zz;
    const float yyzz = yy + zz;
    const float a = yz - xw;
    const float b = xz + yw;
    const float c = xy - zw;
    const float d = yz + xw;
    const float e = xy + zw;
    const float f = xz - yw;
    m->m_at.z = ppc::fmadds(xxyy, -2.0f, 1.0f);   // +0x28
    m->m_up.y = ppc::fmadds(xxzz, -2.0f, 1.0f);   // +0x14
    m->m_right.x = ppc::fmadds(yyzz, -2.0f, 1.0f);  // +0x00
    m->m_at.y = a + a;     // +0x24
    m->m_at.x = b + b;     // +0x20
    m->m_up.x = c + c;     // +0x10
    m->m_up.z = d + d;     // +0x18
    m->m_right.y = e + e;  // +0x04
    m->m_right.z = f + f;  // +0x08
}

namespace {
// 0x007211a0 / 0x00721250 / 0x00721300: RtQuatConvertFromMatrix's helpers for a matrix whose trace is not positive;
// the largest diagonal element picks the axis (z, y or x) the quaternion is built around. `m` is the 16 floats of
// an RwMatrix (right 0-2, up 4-6, at 8-10).
void QuatFromMatrixZMajor(float* q, const float* m) {
    const float diagonal = m[0] + m[5];
    const float s = rwSqrt((m[10] - diagonal) + 1.0f);
    q[2] = s * 0.5f;
    const float inverse = 0.5f / s;
    q[3] = inverse * (m[1] - m[4]);
    q[1] = inverse * (m[9] + m[6]);
    q[0] = inverse * (m[8] + m[2]);
}
void QuatFromMatrixYMajor(float* q, const float* m) {
    const float diagonal = m[10] + m[0];
    const float s = rwSqrt((m[5] - diagonal) + 1.0f);
    q[1] = s * 0.5f;
    const float inverse = 0.5f / s;
    q[3] = inverse * (m[8] - m[2]);
    q[0] = inverse * (m[4] + m[1]);
    q[2] = inverse * (m[6] + m[9]);
}
void QuatFromMatrixXMajor(float* q, const float* m) {
    const float diagonal = m[5] + m[10];
    const float s = rwSqrt((m[0] - diagonal) + 1.0f);
    q[0] = s * 0.5f;
    const float inverse = 0.5f / s;
    q[3] = inverse * (m[6] - m[9]);
    q[2] = inverse * (m[2] + m[8]);
    q[1] = inverse * (m[1] + m[4]);
}
}  // namespace

// 0x002420f8 Quat_FromMatrix = TocBridge_RtQuatConvertFromMatrix -> 0x007213b0 RtQuatConvertFromMatrix (RenderWare's
// rtquat, no source in the sdk): q = (x, y, z, w) from the rotation of `m`.
int32_t Quat_FromMatrix(float* q, const float* m) {
    if (q == nullptr || m == nullptr) return 0;
    const float trace = (m[0] + m[5]) + m[10];
    if (0.0f < trace) {
        const float s = rwSqrt(trace + 1.0f);
        q[3] = s * 0.5f;
        const float inverse = 0.5f / s;
        q[0] = inverse * (m[6] - m[9]);
        q[1] = inverse * (m[8] - m[2]);
        q[2] = inverse * (m[1] - m[4]);
        return 1;
    }
    if (m[0] <= m[5]) {
        if (m[10] < m[5])
            QuatFromMatrixYMajor(q, m);
        else
            QuatFromMatrixZMajor(q, m);
    } else if (m[10] < m[0]) {
        QuatFromMatrixXMajor(q, m);
    } else {
        QuatFromMatrixZMajor(q, m);
    }
    return 1;
}

namespace {
bool SlerpSignBit(float x) {
    int32_t bits;
    std::memcpy(&bits, &x, 4);
    return bits < 0;
}

// The sine Quat_Slerp inlines three times: the sign bit tested through memory; a non-negative argument uses the
// inlined octant polynomials (x * 4/pi in single precision, TOC1 -0x240..-0x220), a negative one the library's sinf
// 0x009a1390 of its magnitude, negated.
float SlerpSine(float x) { return SlerpSignBit(x) ? -crt::LibSinf(-x) : crt::InlineSinf(x); }
}  // namespace

// 0x00242728 Quat_Slerp: r3 = out, r4 = a, r5 = b, f1 = t. The dot product (b * a, fused from y: y, x, z, w); a
// negative dot negates it and b (the short way round). Above 0.9999 (TOC1 -0x250) the weights are (1 - t, t);
// otherwise theta = acosf(dot) and the weights are sin((1 - t) theta) / sin theta and sin(t theta) / sin theta.
// out = fmadds(weightA, a, weightB * b), written w, x, y, z.
void Quat_Slerp(float t, float* out, const float* a, const float* b) {
    float bx = b[0];
    float by = b[1];
    float bz = b[2];
    float bw = b[3];
    float dot = by * a[1];
    dot = ppc::fmadds(bx, a[0], dot);
    dot = ppc::fmadds(bz, a[2], dot);
    dot = ppc::fmadds(bw, a[3], dot);
    if (dot < 0.0f) {  // TOC1 -0x25c
        dot = -dot;
        bx = -bx;
        by = -by;
        bz = -bz;
        bw = -bw;
    }
    float weightA;
    float weightB;
    if (dot < 0.99989998340606689f) {  // TOC1 -0x250 (0x3f7ff972)
        const float theta = crt::Acosf(dot);  // TocBridge_Math_Acosf 0x98e1a0
        const float sinTheta = SlerpSine(theta);
        const float sinA = SlerpSine(theta * (1.0f - t));
        const float sinB = SlerpSine(t * theta);
        weightB = sinB / sinTheta;
        weightA = sinA / sinTheta;
    } else {
        weightA = 1.0f - t;  // TOC1 -0x264
        weightB = t;
    }
    const float ax = a[0];
    const float ay = a[1];
    const float az = a[2];
    const float aw = a[3];
    const float w = ppc::fmadds(weightA, aw, weightB * bw);
    const float x = ppc::fmadds(weightA, ax, weightB * bx);
    const float y = ppc::fmadds(weightA, ay, by * weightB);
    const float z = ppc::fmadds(weightA, az, bz * weightB);
    out[3] = w;
    out[0] = x;
    out[1] = y;
    out[2] = z;
}
