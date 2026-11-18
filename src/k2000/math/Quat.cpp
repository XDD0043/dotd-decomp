//
// Reconstructed original translation unit: 0x241c78-0x2436e8 (GAME_TOC1, main_toc1), 22 functions, 13 live.
// Primary owner: Quat (not a registered class)
// Other owners: RtQuatRotate (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x241c78  Quat_Add  [dead]
//   [x] 0x241cc0  Quat_Multiply
//   [x] 0x241d78  Quat_ToMatrixNormalizing_maybe
//   [x] 0x241e48  Quat_ToMatrix
//   [ ] 0x241f18  Quat_Conjugate  [dead]
//   [ ] 0x241f48  Quat_LengthSquared  [dead]
//   [ ] 0x241f70  Quat_Inverse  [dead]
//   [x] 0x241fd0  Quat_ToAxisAngle_maybe  (Quat_ToAxisAngle, Quat.h; R06's CKPxKinematic calls it)
//   [ ] 0x241ff8  Quat_Modulus_maybe  [dead]
//   [ ] 0x242020  Quat_Exp_maybe  [dead]
//   [x] 0x2420f8  Quat_FromMatrix
//   [x] 0x242130  Quat_Rotate_maybe  (the RtQuatRotate preconcat path inlined here)
//   [x] 0x242158  RtQuatRotate_Thunk  [dead: no pointer to its descriptor 0xb823c8, no call]  (Quat_RotateReplace)
//   [x] 0x242180  Quat_Normalize
//   [ ] 0x242240  Quat_ToMatrixKeepPosition_maybe  [dead]
//   [ ] 0x242300  Quat_ToMatrixNormalizingKeepPosition_maybe  [dead]
//   [x] 0x2423c8  Quat_Log_maybe  [dead: no pointer to its descriptor 0xb823e8, no call]
//   [x] 0x2424a0  Quat_ToEulerAngles_maybe  (Quat_ToEulerAngles; R02's CKIKChain calls it)
//   [x] 0x242648  Quat_FromMatrixNormalized_maybe  (Quat_FromMatrixNormalized; R06's CKPxKinematic calls it)
//   [x] 0x242728  Quat_Slerp
//   [ ] 0x242b40  Quat_FromTwoAxisAngles_maybe  [dead]
//   [x] 0x243058  Quat_FromEulerDeg
#include "k2000/math/Quat.h"

#include <cstring>

#include "Renderware/rwcore/RwMatrix.h"
#include "Renderware/rwcore/RwTypes.h"
#include "crt/xsin.h"
#include "crt/ppc_ops.h"
#include "crt/xatan.h"
#include "crt/xatan2.h"
#include <cmath>
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

// 0x00241d78 Quat_ToMatrixNormalizing_maybe: s = 2 / |q|^2 (the squares summed y, x, z, w with fmadds); the products
// with the scaled x, y, z; the diagonal 1 - (two products), the off-diagonals sums / differences; flags 3, the position 0.
void Quat_ToMatrixNormalizing(const float* q, CMatrix34* m) {
    const float x = q[0];
    const float y = q[1];
    const float z = q[2];
    const float w = q[3];
    m->m_pos.z = 0.0f;
    m->m_ui32Flags = 3;
    m->m_pos.x = 0.0f;
    m->m_pos.y = 0.0f;
    const float n = ppc::fmadds(w, w, ppc::fmadds(z, z, ppc::fmadds(x, x, y * y)));
    const float s = 2.0f / n;  // TOC1 -0x268
    const float zs = z * s;
    const float xs = x * s;
    const float ys = y * s;
    const float zz = z * zs;
    const float xx = x * xs;
    const float yy = y * ys;
    const float xz = z * xs;
    const float yz = y * zs;
    const float wx = w * xs;
    const float wz = w * zs;
    const float xy = x * ys;
    const float wy = w * ys;
    const float xxzz = xx + zz;
    const float xxyy = xx + yy;
    const float yyzz = yy + zz;
    m->m_at.y = yz - wx;
    m->m_up.z = wx + yz;
    m->m_up.x = xy - wz;
    m->m_at.x = wy + xz;
    m->m_right.y = wz + xy;
    m->m_right.z = xz - wy;
    m->m_up.y = 1.0f - xxzz;  // TOC1 -0x264
    m->m_at.z = 1.0f - xxyy;
    m->m_right.x = 1.0f - yyzz;
}

// 0x00242180 Quat_Normalize: q scaled to unit length (Math_InvSqrtf 0x114d8 = rwInvSqrt); the identity
// (0, 0, 0, 1) when |q|^2 is not above 0.001 (TOC1 -0x258; bgt, so also when it is NaN).
void Quat_Normalize(float* q) {
    const float lengthSq = ppc::fmadds(q[3], q[3], ppc::fmadds(q[2], q[2], ppc::fmadds(q[0], q[0], q[1] * q[1])));
    if (!(lengthSq > 0x1.0624dep-10f)) {  // 0x3a83126f
        q[2] = 0.0f;
        q[1] = 0.0f;
        q[3] = 1.0f;
        q[0] = 0.0f;
        return;
    }
    const float inv = rwInvSqrt(lengthSq);
    const float x = inv * q[0];
    const float y = inv * q[1];
    const float w = inv * q[3];
    const float z = inv * q[2];
    q[0] = x;
    q[1] = y;
    q[3] = w;
    q[2] = z;
}

namespace {

// The inlined cosf / sinf of the game code with the library calls for a negative argument (the sign bit
// tested on the stored float): cosf(-a) through 0x9a11d8, -sinf(-a) through 0x9a1390.
float EulerCos(float a) {
    uint32_t bits;
    std::memcpy(&bits, &a, 4);
    if ((bits & 0x80000000u) != 0) return crt::LibCosf(-a);
    return crt::InlineCosf(a);
}
float EulerSin(float a) {
    uint32_t bits;
    std::memcpy(&bits, &a, 4);
    if ((bits & 0x80000000u) != 0) return -crt::LibSinf(-a);
    return crt::InlineSinf(a);
}

}  // namespace

// 0x00243058 Quat_FromEulerDeg: q from the angles in degrees (x, y, z), each halved after the conversion to
// radians (x * 0.0174533 (TOC1 -0x21c), then * 0.5): w = cy cx cz + sy sx sz, x = cy cz sx - sy cx sz,
// y = cy sx sz + sy cx cz, z = cy cx sz - sy cz sx.
void Quat_FromEulerDeg(float* q, const float* degrees) {
    const float kDegToRad = 0x1.1df468p-6f;  // 0x3c8efa34
    const float hx = (degrees[0] * kDegToRad) * 0.5f;
    const float hz = (degrees[2] * kDegToRad) * 0.5f;
    const float hy = (degrees[1] * kDegToRad) * 0.5f;
    const float cx = EulerCos(hx);
    const float cy = EulerCos(hy);
    const float cz = EulerCos(hz);
    const float sx = EulerSin(hx);
    const float sy = EulerSin(hy);
    const float sz = EulerSin(hz);
    const float sxsz = sx * sz;
    const float cxsz = cx * sz;
    const float czsx = cz * sx;
    const float cxcz = cx * cz;
    const float a = sy * sxsz;
    const float b = sy * cxsz;
    const float c = sy * czsx;
    const float d = sy * cxcz;
    q[3] = ppc::fmadds(cy, cxcz, a);
    q[0] = ppc::fmsubs(cy, czsx, b);
    q[2] = ppc::fmsubs(cy, cxsz, c);
    q[1] = ppc::fmadds(cy, sxsz, d);
}

// 0x00241cc0 Quat_Multiply (the register allocation of the original kept: a and b are read again after each store).
void Quat_Multiply(float* out, const float* a, const float* b) {
    float f13 = a[2];
    float f0 = b[1];
    float f7 = f13 * f0;
    float f12 = b[2];
    float f9 = a[1];
    f0 = f9 * f0;
    float f11 = b[0];
    float f10 = a[0];
    float f8 = a[3];
    const float f6 = b[3];
    f9 = ppc::fmsubs(f9, f12, f7);  // a1 b2 - a2 b1
    f10 = ppc::fmadds(f10, f11, f0);
    out[0] = f9;
    f7 = a[0];
    f0 = f7 * f12;
    f11 = b[0];
    f12 = ppc::fmadds(f13, f12, f10);
    f13 = ppc::fmsubs(f13, f11, f0);  // a2 b0 - a0 b2
    f8 = ppc::fmsubs(f8, f6, f12);    // a3 b3 - a.b
    out[1] = f13;
    f0 = a[1];
    f0 = f0 * f11;
    out[3] = f8;
    f12 = b[1];
    f10 = a[3];
    f13 = ppc::fmadds(f12, f10, f13);
    f8 = b[3];
    f11 = ppc::fmadds(f11, f10, f9);
    f7 = ppc::fmsubs(f7, f12, f0);  // a0 b1 - a1 b0
    out[1] = f13;
    f12 = a[1];
    out[0] = f11;
    f12 = ppc::fmadds(f12, f8, f13);
    f0 = a[0];
    f0 = ppc::fmadds(f0, f8, f11);
    out[2] = f7;
    f13 = b[2];
    f13 = ppc::fmadds(f13, f10, f7);
    out[1] = f12;
    out[0] = f0;
    out[2] = f13;
    f0 = a[2];
    f0 = ppc::fmadds(f0, f8, f13);
    out[2] = f0;
}

// 0x00242130 Quat_Rotate_maybe -> 0x007216c8 RtQuatRotate (RenderWare rtquat), its rwCOMBINEPRECONCAT path (r6 = 1, the
// only one this caller takes). The half angle is angle * pi/360 (library TOC -0x3818, 0.008726646f); sine and cosine are
// the double Dinkumware _Sin 0x00780880 rounded to float.
float* Quat_Rotate(float* q, const RwV3d* axis, float angleDegrees) {
    if (q == nullptr || axis == nullptr) return nullptr;  // _rwerror(E_RW_NULLP): not reached in the game
    const float half = angleDegrees * 0x1.1df46ap-7f;  // 0x3c0efa35
    const float q2 = q[2];
    const float q1 = q[1];
    const float q0 = q[0];
    const float q3 = q[3];
    const float s = static_cast<float>(crt::Sin(half, 0));
    const float c = static_cast<float>(crt::Sin(half, 1));
    RwV3d v;
    RwV3dNormalize(&v, axis);  // 0x0075f018
    const float vy = v.y * s;
    const float vz = s * v.z;
    const float vx = v.x * s;
    float f11 = q2 * vy;
    float f10 = q1 * vy;
    float f8 = q0 * vz;
    f11 = ppc::fmsubs(q1, vz, f11);
    float f12 = ppc::fmadds(q0, vx, f10);
    q[0] = f11;
    float f0 = ppc::fmadds(q2, vz, f12);
    f8 = ppc::fmsubs(q2, vx, f8);
    float f9 = q1 * vx;
    f10 = ppc::fmadds(q3, vx, f11);
    f12 = ppc::fmsubs(q3, c, f0);
    q[1] = f8;
    f9 = ppc::fmsubs(q0, vy, f9);
    const float f13 = ppc::fmadds(q3, vy, f8);
    q[3] = f12;
    const float r0 = ppc::fmadds(q0, c, f10);
    q[2] = f9;
    const float r1 = ppc::fmadds(q1, c, f13);
    const float f28 = ppc::fmadds(q3, vz, f9);
    q[0] = r0;
    q[1] = r1;
    q[2] = ppc::fmadds(q2, c, f28);
    return q;
}

// 0x00721510 RtQuatConvertToAxisAngle (RenderWare rtquat, through TocBridge 0x98f260): the unit axis (the vector part
// times 1 / its length, 0 for a zero length; ble: a NaN length too) and the angle in degrees, 2 atan2(|v|, w) (the double
// atan2 0x0077e868, rounded to float); above pi/2 the axis is negated and the angle is 2 (pi - a) (the angle kept
// at most 180 degrees). TOC2 -0x3828 (0), -0x383c (1), -0x3824 (pi/2), -0x3820
// (pi), -0x381c (360/pi 0x42e52ee0). A null pointer: the RenderWare error (not reached), null.
static const float* RtQuatConvertToAxisAngle(const float* q, float* axis, float* angle) {
    if (q == nullptr || axis == nullptr || angle == nullptr) return nullptr;  // _rwerror(E_RW_NULLP) + RwErrorSet
    const float length = rwSqrt(ppc::fmadds(q[2], q[2], ppc::fmadds(q[0], q[0], q[1] * q[1])));  // _rwSqrt 0x75e738
    float inverse = 0.0f;
    if (length > 0.0f) inverse = 1.0f / length;
    const float a = static_cast<float>(crt::Atan2(length, q[3]));
    const float toDegrees2 = 0x1.ca5dcp+6f;  // 0x42e52ee0 = 114.591552734375
    if (a > 0x1.921fb6p+0f) {  // ble 0x721620: not greater (a NaN included) takes the plain branch
        const float rest = 0x1.921fb6p+1f - a;
        const float minus = -inverse;
        const float z = minus * q[2];
        const float x = minus * q[0];
        const float degrees = rest * toDegrees2;
        const float y = minus * q[1];
        axis[2] = z;
        axis[0] = x;
        axis[1] = y;
        *angle = degrees;
        return q;
    }
    const float z = inverse * q[2];
    const float x = inverse * q[0];
    const float y = inverse * q[1];
    const float degrees = a * toDegrees2;
    axis[2] = z;
    axis[0] = x;
    axis[1] = y;
    *angle = degrees;
    return q;
}

// 0x00241fd0 Quat_ToAxisAngle_maybe: RtQuatConvertToAxisAngle (CKPxKinematic_ComputeDriveVelocities_maybe 0x21c568
// calls it: R06's CKPxKinematic.cpp).
const float* Quat_ToAxisAngle(const float* q, float* axis, float* angleDegrees) {
    return RtQuatConvertToAxisAngle(q, axis, angleDegrees);
}

// 0x00242158 RtQuatRotate_Thunk: RtQuatRotate (0x007216c8, TocBridge 0x98e200) with rwCOMBINEREPLACE (r6 = 0): q becomes
// the rotation of `angleDegrees` about `axis`: w = cos(half) first, the vector part RwV3dNormalize(axis) (written into q)
// times sin(half) (stores x, z, y). The half angle and the double _Sin as in Quat_Rotate. Dead in the original (no
// pointer to its descriptor 0xb823c8, no call).
float* Quat_RotateReplace(float* q, const RwV3d* axis, float angleDegrees) {
    if (q == nullptr || axis == nullptr) return nullptr;  // _rwerror(E_RW_NULLP): not reached
    const float half = angleDegrees * 0x1.1df46ap-7f;  // 0x3c0efa35
    const float s = static_cast<float>(crt::Sin(half, 0));
    const float c = static_cast<float>(crt::Sin(half, 1));
    q[3] = c;
    RwV3dNormalize(reinterpret_cast<RwV3d*>(q), axis);  // 0x0075f018
    const float x = s * q[0];
    const float z = s * q[2];
    const float y = s * q[1];
    q[0] = x;
    q[2] = z;
    q[1] = y;
    return q;
}

// 0x002423c8 Quat_Log_maybe: out = (v * atan2f(|v|, w) / |v|, 0.5 ln |q|^2); the vector part 0 when |v| is not above 0
// (ble). |v| through _rwSqrt, the logarithm _FLog_maybe base 0. TOC -0x25c (0), -0x254 (0.5). Dead in the original (no
// pointer to its descriptor 0xb823e8, no call).
void Quat_Log(float* out, const float* q) {
    const float vv = ppc::fmadds(q[2], q[2], ppc::fmadds(q[0], q[0], q[1] * q[1]));
    const float w = q[3];
    const float length = rwSqrt(vv);  // TocBridge__rwSqrt 0x98f290
    const float angle = crt::Atan2f(length, q[3]);
    const float squared = ppc::fmadds(w, w, vv);
    float scale = 0.0f;
    if (length > 0.0f) scale = angle / length;
    const float z = scale * q[2];
    const float x = scale * q[0];
    const float y = scale * q[1];
    out[2] = z;
    out[0] = x;
    out[1] = y;
    out[3] = crt::FLog(squared, 0) * 0.5f;
}

// 0x002424a0 Quat_ToEulerAngles_maybe (CKIKChain 0x8c608 / 0x8e0a8 call it: R02's CKIKChain.cpp): the three angles in
// degrees (57.29578 0x42652ee1) of the unit quaternion, out[1] = asin(2 (wy - xz)) as atan2f(s, sqrtf(1 - s^2)).
// Within 0.9999 (0x3f7ff972) of +-1 (bge: s >= 0.9999 or not above -0.9999, a NaN included): out[0] = atan2f(2 (xw -
// yz), 1 - 2 (x^2 + z^2)), out[2] = atan2f(0, 1), out[1] = 90 (BUG(original): +90 for -1 too). TOC -0x260 (-2),
// -0x250, -0x24c, -0x264 (1), -0x248, -0x25c (0), -0x244 (90).
void Quat_ToEulerAngles(const float* q, float* out) {
    const float minusTwo = -2.0f;
    const float w = q[3];
    const float wm2 = w * minusTwo;
    const float y = q[1];
    const float x = q[0];
    const float y2 = y + y;
    const float x2 = x + x;
    const float xm2 = x * minusTwo;
    const float z = q[2];
    const float zm2 = z * minusTwo;
    const float ywm2 = y * wm2;
    const float one = 1.0f;
    const float zy2 = z * y2;
    const float oneMinus2xx = ppc::fmadds(x, xm2, one);
    const float minus2zz = z * zm2;
    const float s = ppc::fnmadds(z, x2, ywm2);
    const float toDegrees = 0x1.ca5dc2p+5f;  // 0x42652ee1
    if (s >= 0.9998999834060669f || !(s > -0.9998999834060669f)) {
        const float a = crt::Atan2f(ppc::fnmadds(x, wm2, zy2), minus2zz + oneMinus2xx);
        out[0] = a * toDegrees;
        const float b = crt::Atan2f(0.0f, one);
        out[1] = 90.0f;
        out[2] = b * toDegrees;
        return;
    }
    float minus2yy = y * minusTwo;
    const float w2 = w + w;
    minus2yy = y * minus2yy;
    const float c = std::sqrt(one - s * s);  // Math_Sqrtf 0x10690 (fsqrts)
    const float pitch = crt::Atan2f(s, c);
    const float numerator0 = ppc::fmadds(x, w2, zy2);
    const float denominator0 = minus2yy + oneMinus2xx;
    out[1] = pitch * toDegrees;
    float zw2 = z * w2;
    float oneMinus2yy = minus2yy + one;
    zw2 = ppc::fmadds(y, x2, zw2);
    oneMinus2yy = oneMinus2yy + minus2zz;
    const float a = crt::Atan2f(numerator0 / c, denominator0 / c);
    out[0] = a * toDegrees;
    const float b = crt::Atan2f(zw2 / c, oneMinus2yy / c);
    out[2] = b * toDegrees;
}

// 0x00242648 Quat_FromMatrixNormalized_maybe (CKPxKinematic_ComputeDriveVelocities_maybe 0x21c568: R06's file): q from
// the matrix (RtQuatConvertFromMatrix), then unit length by rwInvSqrt (Math_InvSqrtf 0x114d8 -> 0x0075e790); (0, 0, 0, 1)
// when |q|^2 is not above 0.001 (TOC -0x258; ble, a NaN included). Returns q.
float* Quat_FromMatrixNormalized(float* q, const float* m) {
    Quat_FromMatrix(q, m);  // TocBridge_RtQuatConvertFromMatrix 0x98f2b0
    const float squared = ppc::fmadds(q[3], q[3], ppc::fmadds(q[2], q[2], ppc::fmadds(q[0], q[0], q[1] * q[1])));
    if (!(squared > 0.0010000000474974513f)) {  // 0x3a83126f
        q[2] = 0.0f;  // stw 0
        q[3] = 1.0f;
        q[0] = 0.0f;
        q[1] = 0.0f;
        return q;
    }
    const float inverse = rwInvSqrt(squared);
    const float x = inverse * q[0];
    const float y = inverse * q[1];
    const float w = inverse * q[3];
    const float z = inverse * q[2];
    q[0] = x;
    q[1] = y;
    q[3] = w;
    q[2] = z;
    return q;
}
