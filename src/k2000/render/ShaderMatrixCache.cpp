// ShaderMatrixCache.cpp - reconstructed original translation unit 0x247988-0x248e28 (GAME_TOC1, main_toc1), 20 functions, 16 live.
// Primary owner: ShaderMatrixCache (not a registered class)
// Other owners: ConstructShaderMatrixCache (2), GetTransposedWorldViewProjectionMatrix (2), SetShaderObjectWorldMatrix (1), BeginCameraUpdateAndCacheShaderMatrices (1), SetShaderObjectWorldMatrix4x4 (1), GetShaderViewProjectionMatrix (1), GetShaderInverseWorldMatrix (1)
//
// C2.4 step 3 ports the cache's contract with the device's matrices (see the header): the original's own object
// (validity bits at +0x260, the cached products) is a plain state here.
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x247988  ShaderMatrixCache_ClearValidityFlags_maybe  [dead]
//   [~] 0x247998  ShaderMatrixCache_CopyProjectionFromPSGL_maybe  (BeginCamera)
//   [~] 0x2479c8  ShaderMatrixCache_CopyViewFromPSGL_maybe  (BeginCamera)
//   [ ] 0x2479f8  ShaderMatrixCache_DebugPrintMatrices_maybe  [dead]
//   [ ] 0x247a40  ShaderMatrixCache_DeletingDestructor
//   [ ] 0x247b28  ShaderMatrixCache_Destructor
//   [ ] 0x247bf8  ShaderMatrixCache_Destructor_2
//   [ ] 0x247cc8  ConstructShaderMatrixCache
//   [ ] 0x247da8  ConstructShaderMatrixCache_2
//   [x] 0x247e88  SetShaderObjectWorldMatrix
//   [x] 0x247ff8  BeginCameraUpdateAndCacheShaderMatrices  (the matrix part)
//   [ ] 0x2480b8  SetShaderObjectWorldMatrix4x4
//   [ ] 0x248240  GetShaderViewProjectionMatrix
//   [ ] 0x248300  GetShaderInverseWorldMatrix_maybe
//   [ ] 0x2483b8  ShaderMatrixCache_GetWorldMatrix_maybe  [dead]
//   [ ] 0x248400  GetTransposedWorldViewProjectionMatrix_CustomProjection_maybe  [dead]
//   [x] 0x2485f8  GetTransposedWorldViewMatrix
//   [x] 0x248710  GetTransposedWorldViewProjectionMatrix
//   [x] 0x248878  ShaderMatrixCache_WorldPointToObject
//   [x] 0x248ae0  ShaderMatrixCache_WorldDirToObject
#include "k2000/render/ShaderMatrixCache.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwDevice.h"
#include "Renderware/rwcore/RwTypes.h"

namespace {
// Column-major 4x4 for column vectors: element (r, c) at [c * 4 + r].
struct Mat {
    double m[16];
};

Mat Identity() {
    Mat r = {};
    r.m[0] = r.m[5] = r.m[10] = r.m[15] = 1.0;
    return r;
}

Mat FromFloats(const float* f) {
    Mat r;
    for (int i = 0; i < 16; ++i) r.m[i] = f[i];
    return r;
}

Mat Multiply(const Mat& a, const Mat& b) {  // a * b
    Mat r = {};
    for (int c = 0; c < 4; ++c) {
        for (int row = 0; row < 4; ++row) {
            double sum = 0.0;
            for (int k = 0; k < 4; ++k) sum += a.m[k * 4 + row] * b.m[c * 4 + k];
            r.m[c * 4 + row] = sum;
        }
    }
    return r;
}

// An RW matrix (rows right, up, at, pos for row vectors) as a column-vector matrix.
Mat FromRw(const RwMatrix& w) {
    Mat r = Identity();
    r.m[0] = w.right.x; r.m[1] = w.right.y; r.m[2] = w.right.z;
    r.m[4] = w.up.x;    r.m[5] = w.up.y;    r.m[6] = w.up.z;
    r.m[8] = w.at.x;    r.m[9] = w.at.y;    r.m[10] = w.at.z;
    r.m[12] = w.pos.x;  r.m[13] = w.pos.y;  r.m[14] = w.pos.z;
    return r;
}

// Inverse of an affine matrix (last row 0 0 0 1): the inverse 3x3 and the translation it maps back.
Mat InvertAffine(const Mat& a) {
    const double a00 = a.m[0], a10 = a.m[1], a20 = a.m[2];
    const double a01 = a.m[4], a11 = a.m[5], a21 = a.m[6];
    const double a02 = a.m[8], a12 = a.m[9], a22 = a.m[10];
    const double det = a00 * (a11 * a22 - a12 * a21) - a01 * (a10 * a22 - a12 * a20) + a02 * (a10 * a21 - a11 * a20);
    Mat r = Identity();
    if (det == 0.0) return r;
    const double inv = 1.0 / det;
    r.m[0] = (a11 * a22 - a12 * a21) * inv;
    r.m[1] = (a12 * a20 - a10 * a22) * inv;
    r.m[2] = (a10 * a21 - a11 * a20) * inv;
    r.m[4] = (a02 * a21 - a01 * a22) * inv;
    r.m[5] = (a00 * a22 - a02 * a20) * inv;
    r.m[6] = (a01 * a20 - a00 * a21) * inv;
    r.m[8] = (a01 * a12 - a02 * a11) * inv;
    r.m[9] = (a02 * a10 - a00 * a12) * inv;
    r.m[10] = (a00 * a11 - a01 * a10) * inv;
    const double tx = a.m[12], ty = a.m[13], tz = a.m[14];
    r.m[12] = -(r.m[0] * tx + r.m[4] * ty + r.m[8] * tz);
    r.m[13] = -(r.m[1] * tx + r.m[5] * ty + r.m[9] * tz);
    r.m[14] = -(r.m[2] * tx + r.m[6] * ty + r.m[10] * tz);
    return r;
}

// The constant-register layout of a column-vector matrix: the rows.
void ToRegisters(const Mat& a, float out[16]) {
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) out[r * 4 + c] = static_cast<float>(a.m[c * 4 + r]);
    }
}

Mat g_view = Identity();
Mat g_viewProj = Identity();
Mat g_world = Identity();
bool g_hasWorld = false;
}  // namespace

// 0x00247e88 SetShaderObjectWorldMatrix
void ShaderMatrixCache_SetWorld(const RwMatrix* world) {
    if (world != nullptr) {
        g_world = FromRw(*world);
        g_hasWorld = true;
    } else {
        g_world = Identity();
        g_hasWorld = false;
    }
}

// 0x00247ff8 BeginCameraUpdateAndCacheShaderMatrices (after RwCameraBeginUpdate): the view and projection copied from
// the backend, the world matrix cleared (its validity bit is not set again until SetShaderObjectWorldMatrix).
void ShaderMatrixCache_BeginCamera() {
    float view[16], viewProj[16];
    RwDevice_GetViewMatrix(view);
    RwDevice_GetViewProjection(viewProj);
    g_view = FromFloats(view);
    g_viewProj = FromFloats(viewProj);
    ShaderMatrixCache_SetWorld(nullptr);
}

// 0x00248710 GetTransposedWorldViewProjectionMatrix: with a world matrix world * VP (row vectors), else VP.
void GetTransposedWorldViewProjectionMatrix(float out[16]) {
    ToRegisters(g_hasWorld ? Multiply(g_viewProj, g_world) : g_viewProj, out);
}

// 0x002485f8 GetTransposedWorldViewMatrix
void GetTransposedWorldViewMatrix(float out[16]) {
    ToRegisters(g_hasWorld ? Multiply(g_view, g_world) : g_view, out);
}

// 0x00248878 ShaderMatrixCache_WorldPointToObject
void ShaderMatrixCache_WorldPointToObject(const float world[3], float object[3]) {
    const Mat inv = g_hasWorld ? InvertAffine(g_world) : Identity();
    for (int r = 0; r < 3; ++r) {
        object[r] = static_cast<float>(inv.m[r] * world[0] + inv.m[4 + r] * world[1] + inv.m[8 + r] * world[2] + inv.m[12 + r]);
    }
}

// 0x00248ae0 ShaderMatrixCache_WorldDirToObject
void ShaderMatrixCache_WorldDirToObject(const float world[3], float object[3]) {
    const Mat inv = g_hasWorld ? InvertAffine(g_world) : Identity();
    for (int r = 0; r < 3; ++r) {
        object[r] = static_cast<float>(inv.m[r] * world[0] + inv.m[4 + r] * world[1] + inv.m[8 + r] * world[2]);
    }
}

void ShaderMatrixCache_GetEyeWorld(float eye[3]) {
    const Mat inv = InvertAffine(g_view);
    eye[0] = static_cast<float>(inv.m[12]);
    eye[1] = static_cast<float>(inv.m[13]);
    eye[2] = static_cast<float>(inv.m[14]);
}
