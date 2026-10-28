// Mat4.cpp - reconstructed original translation unit 0x23f048-0x241c78 (GAME_TOC1, main_toc1), 45 functions, 42 live.
// Primary owner: Mat4 (not a registered class)
// Other owners: Matrix (6), Seg2D (3), Line2D (2), RwMatrixScalePreConcat (1), RwMatrixRotate (1), RwMatrixRotateOneMinusCosineSine (1), RwMatrixQueryRotate (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x23f048  Seg2D_IntersectCircle
//   [x] 0x23f238  Seg2D_IntersectSegment
//   [ ] 0x23f2e8  Line2D_ProjectPoint
//   [ ] 0x23f3a8  Seg2D_DistanceSqToPoint_maybe  [dead]
//   [ ] 0x23f440  Line2D_GetNormal
//   [x] 0x23f4c0  CMatrix34_LoadMatrix
//   [x] 0x23f648  Mat4_OrthoNormalizeInPlace
//   [ ] 0x23f670  RwMatrixScalePreConcat_Thunk
//   [ ] 0x23f698  Matrix_SetRotationKeepPosition
//   [ ] 0x23f708  RwMatrixRotate_Thunk
//   [ ] 0x23f738  Mat4_TransformPreConcat
//   [ ] 0x23f760  Mat4_TransformPostConcat
//   [x] 0x23f788  Mat4_Multiply
//   [x] 0x23f7b0  Mat4_TransformVectors
//   [x] 0x23f7e8  Mat4_TransformPoints
//   [ ] 0x23f820  RwMatrixRotateOneMinusCosineSine_Thunk
//   [ ] 0x23f850  RwMatrixQueryRotate_Thunk
//   [x] 0x23f878  Mat4_Invert_maybe
//   [ ] 0x23f8a0  Mat4_Save
//   [x] 0x23f968  RwMatrixDestroy_Thunk
//   [ ] 0x23f990  Matrix_CreateCopy
//   [x] 0x23fa68  RwMatrixCreate_Thunk
//   [x] 0x23fa90  Mat4_SetBasisFromRightUp
//   [ ] 0x23fba8  Mat4_RotateAboutPoint_maybe
//   [ ] 0x23fc68  Mat4_SetAxisRotationCosSin_maybe  [dead]
//   [x] 0x23fd30  Mat4_SetBasisFromAtUp
//   [x] 0x23fe58  Mat4_SetBasisFromAtRight
//   [x] 0x23ff80  Mat4_BuildFromUpAndForward
//   [x] 0x2400a8  Mat4_SetBasisFromUpAt
//   [ ] 0x2401d0  Matrix_OrthonormalFromTwoAxes_maybe
//   [ ] 0x2402e8  Mat4_Add_maybe
//   [ ] 0x2403e0  Mat4_TransformVec4Array_VMX_maybe
//   [x] 0x240498  Mat4_RotateInPlace
//   [ ] 0x240520  Mat4_TransformVectorsInline
//   [ ] 0x2405b0  Mat4_InverseTransformPoints
//   [ ] 0x240660  Matrix_SetRotationKeepPosition_2
//   [ ] 0x2406d0  Mat4_TransformPointsStrided
//   [ ] 0x2407a8  V3d_TransformVectorsStrided
//   [ ] 0x240880  Matrix_CreateCopyClearFlags
//   [ ] 0x240938  Matrix_LookAt
//   [ ] 0x240b48  Mat4_RotateFromTo_maybe  [dead]
//   [x] 0x241118  Mat4_RotateLocalXDeg
//   [x] 0x2413d0  Mat4_RotateLocalYDeg
//   [x] 0x241688  Mat4_SetRotationAboutAxis_maybe
//   [x] 0x2419c0  Mat4_RotateLocalZDeg
#include "k2000/misc/Mat4.h"

#include "Renderware/rwcore/RwMatrix.h"
#include <cstring>

#include "crt/ppc_ops.h"
#include "crt/xsinf.h"
#include "k2000/io/IKFile.h"
#include "k2000/services/CollisionDatas.h"

// 0x0023f4c0 CMatrix34_LoadMatrix
void CMatrix34_LoadMatrix(CMatrix34* matrix, IKFile* file) {
    uint8_t bytes[0x40];
    file->Read(bytes, 0x40);
    uint32_t* words = reinterpret_cast<uint32_t*>(matrix);
    for (int i = 0; i < 16; ++i) {  // lwbrx on the PS3: the file is little-endian
        const uint8_t* b = bytes + 4 * i;
        words[i] = static_cast<uint32_t>(b[0]) | (static_cast<uint32_t>(b[1]) << 8) |
                   (static_cast<uint32_t>(b[2]) << 16) | (static_cast<uint32_t>(b[3]) << 24);
    }
}

// 0x0023f648 Mat4_OrthoNormalizeInPlace
void Mat4_OrthoNormalizeInPlace(CMatrix34* matrix) {
    RwMatrixOrthoNormalize(reinterpret_cast<RwMatrix*>(matrix), reinterpret_cast<RwMatrix*>(matrix));
}

// 0x0023f968 RwMatrixDestroy_Thunk
int32_t RwMatrixDestroy_Thunk(CMatrix34* matrix) {
    return RwMatrixDestroy(reinterpret_cast<RwMatrix*>(matrix));
}

// 0x0023fa68 RwMatrixCreate_Thunk
CMatrix34* RwMatrixCreate_Thunk() {
    return reinterpret_cast<CMatrix34*>(RwMatrixCreate());
}

// 0x00240498 Mat4_RotateInPlace (through TocBridge_RwMatrixRotate): RwMatrixRotate(m, axis, angle degrees,
// rwCOMBINEPOSTCONCAT); the position (+0x30..+0x38) is kept and rwMATRIXINTERNALIDENTITY cleared.
void Mat4_RotateInPlace(CMatrix34* m, const CVector3* axis, float angle) {
    const float x = m->m_pos.x;
    const float y = m->m_pos.y;
    const float z = m->m_pos.z;
    RwMatrixRotate(reinterpret_cast<RwMatrix*>(m), reinterpret_cast<const RwV3d*>(axis), angle, rwCOMBINEPOSTCONCAT);
    m->m_pos.z = z;
    m->m_pos.x = x;
    m->m_pos.y = y;
    m->m_ui32Flags = m->m_ui32Flags & 0xfffdffffu;
}

// 0x0023fa90 Mat4_SetBasisFromRightUp (step 5: the camera path track's mode 3)
int32_t Mat4_SetBasisFromRightUp(CMatrix34* m, const CVector3* right, const CVector3* up) {
    const float t0 = up->z * right->x;
    const float cy = ppc::fmsubs(right->z, up->x, t0);
    const float t1 = right->z * up->y;
    const float t2 = right->y * up->x;
    const float cx = ppc::fmsubs(right->y, up->z, t1);
    float len2 = cy * cy;
    const float cz = ppc::fmsubs(up->y, right->x, t2);
    len2 = ppc::fmadds(cx, cx, len2);
    len2 = ppc::fmadds(cz, cz, len2);
    if (len2 < 1.75e-2f) return 0;
    const float inv = rwInvSqrt(len2);  // RW_InvSqrt 0x75e790 (through Math_InvSqrtf 0x114d8)
    const float ry = right->y, rx = right->x, rz = right->z;
    const float az = cz * inv;
    const float ax = cx * inv;
    const float ay = cy * inv;
    m->m_right.z = rz;
    m->m_right.x = rx;
    m->m_right.y = ry;
    const float u0 = az * ry;
    const float u1 = ax * rz;
    const float u2 = ay * rx;
    m->m_at.x = ax;
    m->m_up.x = ppc::fmsubs(ay, rz, u0);
    m->m_up.y = ppc::fmsubs(az, rx, u1);
    m->m_up.z = ppc::fmsubs(ax, ry, u2);
    m->m_at.y = ay;
    m->m_at.z = az;
    m->m_ui32Flags = 3;
    return 1;
}

// 0x0023fd30 Mat4_SetBasisFromAtUp
int32_t Mat4_SetBasisFromAtUp(CMatrix34* m, const CVector3* at, const CVector3* up) {
    const float zx = at->z * up->x;
    const float yz = up->z * at->y;
    const float xy = up->y * at->x;
    const float cy = ppc::fmsubs(up->z, at->x, zx);
    const float cx = ppc::fmsubs(up->y, at->z, yz);
    const float cz = ppc::fmsubs(at->y, up->x, xy);
    float len2 = cy * cy;
    len2 = ppc::fmadds(cx, cx, len2);
    len2 = ppc::fmadds(cz, cz, len2);
    if (len2 < 1.75e-2f) return 0;
    const float inv = rwInvSqrt(len2);  // RW_InvSqrt 0x75e790 (through Math_InvSqrtf 0x114d8)
    const float ry = cy * inv;
    const float rz = cz * inv;
    const float rx = cx * inv;
    m->m_right.y = ry;
    m->m_right.z = rz;
    m->m_right.x = rx;
    const float t0 = ry * at->z;
    const float t1 = rz * at->x;
    const float t2 = rx * at->y;
    m->m_up.x = ppc::fmsubs(rz, at->y, t0);
    m->m_up.y = ppc::fmsubs(rx, at->z, t1);
    m->m_up.z = ppc::fmsubs(ry, at->x, t2);
    m->m_at.x = at->x;
    m->m_at.z = at->z;
    m->m_at.y = at->y;
    m->m_ui32Flags = 3;
    return 1;
}

// 0x0023fe58 Mat4_SetBasisFromAtRight (step 6 CLIMB)
int32_t Mat4_SetBasisFromAtRight(CMatrix34* m, const CVector3* at, const CVector3* right) {
    const float uy = ppc::fmsubs(at->z, right->x, right->z * at->x);
    const float ux = ppc::fmsubs(at->y, right->z, at->z * right->y);
    const float uz = ppc::fmsubs(right->y, at->x, at->y * right->x);
    float len2 = uy * uy;
    len2 = ppc::fmadds(ux, ux, len2);
    len2 = ppc::fmadds(uz, uz, len2);
    if (len2 < 1.75e-2f) return 0;
    const float inv = rwInvSqrt(len2);  // RW_InvSqrt 0x75e790 (through Math_InvSqrtf 0x114d8)
    const float nz = uz * inv;
    const float nx = ux * inv;
    const float ny = uy * inv;
    m->m_up.x = nx;
    m->m_right.x = ppc::fmsubs(ny, at->z, nz * at->y);
    m->m_right.y = ppc::fmsubs(nz, at->x, nx * at->z);
    m->m_right.z = ppc::fmsubs(nx, at->y, ny * at->x);
    m->m_up.y = ny;
    m->m_up.z = nz;
    m->m_at.x = at->x;
    m->m_at.z = at->z;
    m->m_at.y = at->y;
    m->m_ui32Flags = 3;
    return 1;
}

// 0x00241688 Mat4_SetRotationAboutAxis_maybe: the rotation matrix of `angle` radians about axis 0 (z), 1 (y)
// or 2 (x) written into the 3x3 part of `m` (the other fields keep their values) with flags = 3. A
// non-negative angle uses the inlined single-precision sine and cosine; a negative one (sign bit set,
// -0.0 included) the library's cosf / sinf of its magnitude. Any other axis writes only the flags.
void Mat4_SetRotationAboutAxis(float angle, CMatrix34* m, int32_t axis) {
    int32_t angleBits;
    std::memcpy(&angleBits, &angle, 4);
    float c;
    float s;
    if (angleBits >= 0) {
        c = crt::InlineCosf(angle);
        s = crt::InlineSinf(angle);
    } else {
        c = crt::LibCosf(-angle);
        s = -crt::LibSinf(-angle);
    }
    if (axis == 1) {
        m->m_at.y = 0.0f;     // +0x24
        m->m_right.y = 0.0f;  // +0x04
        m->m_up.x = 0.0f;     // +0x10
        m->m_up.z = 0.0f;     // +0x18
        m->m_up.y = 1.0f;     // +0x14
        m->m_at.x = s;        // +0x20
        m->m_at.z = c;        // +0x28
        m->m_right.x = c;     // +0x00
        m->m_right.z = -s;    // +0x08
    } else if (axis == 2) {
        m->m_at.x = 0.0f;     // +0x20
        m->m_right.y = 0.0f;  // +0x04
        m->m_right.z = 0.0f;  // +0x08
        m->m_up.x = 0.0f;     // +0x10
        m->m_right.x = 1.0f;  // +0x00
        m->m_at.z = c;        // +0x28
        m->m_up.y = c;        // +0x14
        m->m_up.z = s;        // +0x18
        m->m_at.y = -s;       // +0x24
    } else if (axis == 0) {
        m->m_up.y = c;        // +0x14
        m->m_at.y = 0.0f;     // +0x24
        m->m_at.z = 1.0f;     // +0x28
        m->m_right.x = c;     // +0x00
        m->m_right.y = s;     // +0x04
        m->m_right.z = 0.0f;  // +0x08
        m->m_up.z = 0.0f;     // +0x18
        m->m_at.x = 0.0f;     // +0x20
        m->m_up.x = -s;       // +0x10
    }
    m->m_ui32Flags = 3;
}

// 0x0023f7b0 Mat4_TransformVectors
void Mat4_TransformVectors(const CMatrix34* m, CVector3* out, const CVector3* in, int32_t count) {
    RwV3dTransformVectors(reinterpret_cast<RwV3d*>(out), reinterpret_cast<const RwV3d*>(in), count,
                          reinterpret_cast<const RwMatrix*>(m));
}

// 0x0023f7e8 Mat4_TransformPoints
void Mat4_TransformPoints(const CMatrix34* m, CVector3* out, const CVector3* in, int32_t count) {
    RwV3dTransformPoints(reinterpret_cast<RwV3d*>(out), reinterpret_cast<const RwV3d*>(in), count,
                         reinterpret_cast<const RwMatrix*>(m));
}

// 0x0023f788 Mat4_Multiply: RwMatrixMultiply (through its TocBridge).
void Mat4_Multiply(CMatrix34* out, const CMatrix34* a, const CMatrix34* b) {
    RwMatrixMultiply(reinterpret_cast<RwMatrix*>(out), reinterpret_cast<const RwMatrix*>(a), reinterpret_cast<const RwMatrix*>(b));
}

// 0x0023f878 Mat4_Invert_maybe
void Mat4_Invert(CMatrix34* out, const CMatrix34* in) {
    RwMatrixInvert(reinterpret_cast<RwMatrix*>(out), reinterpret_cast<const RwMatrix*>(in));
}

// 0x0023f048 Seg2D_IntersectCircle
uint8_t Seg2D_IntersectCircle(float radius, const CLine2D* segment, const CVector2* center, float* t0, float* t1) {
    const float dx = segment->m_VectDir.m_fX;
    const float dy = segment->m_VectDir.m_fY;
    if (dx == 0.0f && dy == 0.0f) return 0;
    const float oy = segment->m_start.m_fY - center->m_fY;
    const float ox = segment->m_start.m_fX - center->m_fX;
    const float r2 = radius * radius;
    const float a = ppc::fmadds(dx, dx, dy * dy);
    const float halfB = ppc::fmadds(ox, dx, oy * dy);
    const float o2 = ppc::fmadds(ox, ox, oy * oy);
    const float b = halfB + halfB;
    const float c = o2 - r2;
    if (a == 0.0f) {
        if (b != 0.0f) {
            const float t = -c / b;
            *t0 = t;
            *t1 = t;
        } else {
            if (c != 0.0f) return 0;
            *t0 = 0.0f;
            *t1 = 0.0f;
        }
    } else {
        const float discriminant = ppc::fmadds(b, b, c * (a * -4.0f));
        if (discriminant < 0.0f) return 0;
        const float root = std::sqrt(discriminant);  // Math_Sqrtf
        const float half = 0.5f / a;
        *t0 = half * (root - b);
        *t1 = half * (-b - root);
    }
    constexpr float kLow = -9.99999975e-06f;  // 0xb727c5ac
    constexpr float kHigh = 1.00001001f;      // 0x3f800054
    const float first = *t0;
    if (first < kLow || first > kHigh) {
        const float second = *t1;
        if (second < kLow || second > kHigh) return 0;
        *t0 = second;
        return 1;
    }
    const float second = *t1;
    if (second < kLow || second > kHigh) return 1;
    if (first > second) {
        *t1 = first;
        *t0 = second;
    }
    return 2;
}

// 0x0023f238 Seg2D_IntersectSegment
uint8_t Seg2D_IntersectSegment(const CLine2D* a, const CLine2D* b, float* ta, float* tb) {
    const float det = ppc::fmsubs(b->m_VectDir.m_fY, a->m_VectDir.m_fX, b->m_VectDir.m_fX * a->m_VectDir.m_fY);
    if (det == 0.0f) return 0;
    constexpr float kLow = -9.99999975e-06f;
    constexpr float kHigh = 1.00001001f;
    const float dy = b->m_start.m_fY - a->m_start.m_fY;
    const float dx = b->m_start.m_fX - a->m_start.m_fX;
    const float inverse = 1.0f / det;
    const float first = inverse * ppc::fmsubs(dx, b->m_VectDir.m_fY, dy * b->m_VectDir.m_fX);
    *ta = first;
    if (first < kLow || first > kHigh) return 0;
    const float second = inverse * ppc::fmsubs(dx, a->m_VectDir.m_fY, dy * a->m_VectDir.m_fX);
    *tb = second;
    if (second < kLow) return 0;
    return second > kHigh ? 0 : 1;
}

// 0x0023ff80 Mat4_BuildFromUpAndForward: right = normalised (up x forward) when its squared length is at least 0.0175f
// (TOC1 -0x2b0), then up copied and at = right x up, flags = 3; otherwise the matrix is left alone. Returns whether it
// wrote. `forward` may be the matrix's own at row (read before the writes).
int32_t Mat4_BuildFromUpAndForward(CMatrix34* m, const CVector3* up, const CVector3* forward) {
    const float zx = forward->z * up->x;
    const float cy = ppc::fmsubs(up->z, forward->x, zx);
    const float zy = up->z * forward->y;
    const float yx = up->y * forward->x;
    const float cx = ppc::fmsubs(up->y, forward->z, zy);
    float len2 = cy * cy;
    const float cz = ppc::fmsubs(forward->y, up->x, yx);
    len2 = ppc::fmadds(cx, cx, len2);
    len2 = ppc::fmadds(cz, cz, len2);
    if (len2 < 0.0175f) return 0;
    const float inv = rwInvSqrt(len2);  // RW_InvSqrt 0x75e790 (through Math_InvSqrtf 0x114d8)
    const float uy = up->y, uz = up->z, ux = up->x;
    const float rz = cz * inv;
    const float rx = cx * inv;
    const float ry = cy * inv;
    const float a = rz * uy;
    const float b = rx * uz;
    const float c = ry * ux;
    m->m_right.z = rz;
    m->m_right.x = rx;
    m->m_right.y = ry;
    m->m_up.x = up->x;
    m->m_up.z = up->z;
    m->m_up.y = up->y;
    m->m_at.x = ppc::fmsubs(ry, uz, a);
    m->m_at.y = ppc::fmsubs(rz, ux, b);
    m->m_at.z = ppc::fmsubs(rx, uy, c);
    m->m_ui32Flags = 3;
    return 1;
}

// 0x002400a8 Mat4_SetBasisFromUpAt: at = normalised (at x up) when its squared length is at least 0.0175f, right =
// up x at, up copied, flags = 3; otherwise the matrix is left alone. Returns whether it wrote. `at` may be the
// matrix's own at row (read before the writes).
int32_t Mat4_SetBasisFromUpAt(CMatrix34* m, const CVector3* up, const CVector3* at) {
    const float zx = up->z * at->x;
    const float zy = at->z * up->y;
    const float yx = at->y * up->x;
    const float cy = ppc::fmsubs(at->z, up->x, zx);
    const float cx = ppc::fmsubs(at->y, up->z, zy);
    const float cz = ppc::fmsubs(up->y, at->x, yx);
    float len2 = cy * cy;
    len2 = ppc::fmadds(cx, cx, len2);
    len2 = ppc::fmadds(cz, cz, len2);
    if (len2 < 0.0175f) return 0;
    const float inv = rwInvSqrt(len2);  // RW_InvSqrt 0x75e790 (through Math_InvSqrtf 0x114d8)
    const float uz = up->z, uy = up->y, ux = up->x;
    const float ny = cy * inv;
    const float nz = cz * inv;
    const float nx = cx * inv;
    const float a = ny * uz;
    const float b = nz * ux;
    const float c = nx * uy;
    m->m_right.x = ppc::fmsubs(nz, uy, a);
    m->m_right.y = ppc::fmsubs(nx, uz, b);
    m->m_right.z = ppc::fmsubs(ny, ux, c);
    const float upX = up->x, upZ = up->z;
    m->m_at.x = nx;
    const float upY = up->y;
    m->m_up.x = upX;
    m->m_up.z = upZ;
    m->m_up.y = upY;
    m->m_at.z = nz;
    m->m_at.y = ny;
    m->m_ui32Flags = 3;
    return 1;
}

namespace {
// The sine and cosine of `degrees` (times 0.0174532905f, TOC1 -0x26c) the local rotations use: the inlined octant
// polynomials for a non-negative angle, the library's of its magnitude for a negative one (sign bit set).
void DegreesCosSin(float degrees, float* c, float* s) {
    const float angle = degrees * 0.01745329052209854f;
    int32_t angleBits;
    std::memcpy(&angleBits, &angle, 4);
    if (angleBits >= 0) {
        *c = crt::InlineCosf(angle);
        *s = crt::InlineSinf(angle);
    } else {
        *c = crt::LibCosf(-angle);
        *s = -crt::LibSinf(-angle);
    }
}
}  // namespace

// 0x00241118 Mat4_RotateLocalXDeg: the up and at rows turned by `degrees` about the local x axis (right untouched);
// flag 0x20000 cleared.
void Mat4_RotateLocalXDeg(float degrees, CMatrix34* m) {
    float c;
    float s;
    DegreesCosSin(degrees, &c, &s);
    const float ns = -s;
    const float ax = m->m_at.x, ay = m->m_at.y, az = m->m_at.z;
    const float cax = c * ax, cay = c * ay, caz = c * az;
    const float ux = m->m_up.x, uy = m->m_up.y;
    const float saz = s * az, sax = s * ax, say = s * ay;
    const float uz = m->m_up.z;
    const float newAtX = ppc::fmadds(ux, ns, cax);
    const float newUpZ = ppc::fmadds(c, uz, saz);
    const float newUpX = ppc::fmadds(c, ux, sax);
    const float newAtZ = ppc::fmadds(uz, ns, caz);
    const float newAtY = ppc::fmadds(uy, ns, cay);
    const float newUpY = ppc::fmadds(c, uy, say);
    m->m_up.z = newUpZ;
    m->m_up.x = newUpX;
    m->m_at.z = newAtZ;
    m->m_at.x = newAtX;
    m->m_up.y = newUpY;
    m->m_at.y = newAtY;
    m->m_ui32Flags &= ~0x20000u;
}

// 0x002413d0 Mat4_RotateLocalYDeg: the right and at rows turned by `degrees` about the local y axis (up untouched);
// flag 0x20000 cleared.
void Mat4_RotateLocalYDeg(float degrees, CMatrix34* m) {
    float c;
    float s;
    DegreesCosSin(degrees, &c, &s);
    const float ns = -s;
    const float rz = m->m_right.z, rx = m->m_right.x, ry = m->m_right.y;
    const float crz = c * rz, crx = c * rx, cry = c * ry;
    const float ax = m->m_at.x, ay = m->m_at.y, az = m->m_at.z;
    const float srz = s * rz, srx = s * rx, sry = s * ry;
    const float newRightZ = ppc::fmadds(az, ns, crz);
    const float newRightX = ppc::fmadds(ax, ns, crx);
    const float newRightY = ppc::fmadds(ay, ns, cry);
    const float newAtZ = ppc::fmadds(c, az, srz);
    const float newAtX = ppc::fmadds(c, ax, srx);
    const float newAtY = ppc::fmadds(c, ay, sry);
    m->m_at.z = newAtZ;
    m->m_at.x = newAtX;
    m->m_at.y = newAtY;
    m->m_right.z = newRightZ;
    m->m_right.x = newRightX;
    m->m_right.y = newRightY;
    m->m_ui32Flags &= ~0x20000u;
}

// 0x002419c0 Mat4_RotateLocalZDeg: the right and up rows turned by `degrees` about the local z axis (at untouched);
// flag 0x20000 cleared (step 6: the flight's roll).
void Mat4_RotateLocalZDeg(float degrees, CMatrix34* m) {
    float c;
    float s;
    DegreesCosSin(degrees, &c, &s);
    const float ns = -s;
    const float rz = m->m_right.z, rx = m->m_right.x, ry = m->m_right.y;
    const float crz = c * rz, crx = c * rx, cry = c * ry;
    const float srz = s * rz, srx = s * rx, sry = s * ry;
    const float ux = m->m_up.x, uy = m->m_up.y, uz = m->m_up.z;
    const float newRightZ = ppc::fmadds(uz, ns, crz);
    const float newRightX = ppc::fmadds(ux, ns, crx);
    const float newRightY = ppc::fmadds(uy, ns, cry);
    const float newUpZ = ppc::fmadds(c, uz, srz);
    const float newUpX = ppc::fmadds(c, ux, srx);
    const float newUpY = ppc::fmadds(c, uy, sry);
    m->m_up.z = newUpZ;
    m->m_up.x = newUpX;
    m->m_up.y = newUpY;
    m->m_right.z = newRightZ;
    m->m_right.x = newRightX;
    m->m_right.y = newRightY;
    m->m_ui32Flags &= ~0x20000u;
}
