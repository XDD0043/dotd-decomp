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
//   [ ] 0x247a40  ShaderMatrixCache_DeletingDestructor  [platform]  (the cache object (its RW matrix and nine 4x4s): the plain state of ShaderMatrixCache.cpp (C2.4 step 3))
//   [ ] 0x247b28  ShaderMatrixCache_Destructor  [platform]  (the cache object: the plain state of ShaderMatrixCache.cpp (C2.4 step 3))
//   [ ] 0x247bf8  ShaderMatrixCache_Destructor_2  [dead: no pointer to its descriptor 0xb82ab0, no call]
//   [ ] 0x247cc8  ConstructShaderMatrixCache  [platform]  (the cache object: the plain state of ShaderMatrixCache.cpp (C2.4 step 3))
//   [ ] 0x247da8  ConstructShaderMatrixCache_2  [dead: no pointer to its descriptor 0xb82ae8, no call]
//   [x] 0x247e88  SetShaderObjectWorldMatrix
//   [x] 0x247ff8  BeginCameraUpdateAndCacheShaderMatrices  (the matrix part)
//   [x] 0x2480b8  SetShaderObjectWorldMatrix4x4
//   [ ] 0x248240  GetShaderViewProjectionMatrix  [dead: no pointer to its descriptor 0xb82b38, no call]
//   [ ] 0x248300  GetShaderInverseWorldMatrix_maybe  [dead: no pointer to its descriptor 0xb82b40, no call]
//   [ ] 0x2483b8  ShaderMatrixCache_GetWorldMatrix_maybe  [dead]
//   [ ] 0x248400  GetTransposedWorldViewProjectionMatrix_CustomProjection_maybe  [dead]
//   [x] 0x2485f8  GetTransposedWorldViewMatrix
//   [x] 0x248710  GetTransposedWorldViewProjectionMatrix
//   [x] 0x248878  ShaderMatrixCache_WorldPointToObject
//   [x] 0x248ae0  ShaderMatrixCache_WorldDirToObject
#include "k2000/render/ShaderMatrixCache.h"

#include <cmath>
#include <cstdint>
#include <cstring>

#include "Renderware/rwcore/RwDevice.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "Renderware/rwcore/RwTypes.h"
#include "k2000/math/ConvertRwMatrixToHomogeneous4x4.h"

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

// PERF: the products and inverses, computed when first asked for and kept while their inputs stay (the original's cache
// does the same with its validity bits at +0x260: bit 0 the world, bits 2-6 the products). They were computed again by
// every getter: a draw's uniforms ask for world * view, world * view * projection, the eye in object space and one
// object-space direction or position per light, each of the last ones inverting the world matrix again. The values are
// the same expressions on the same inputs, so the same bits.
enum : uint32_t {
    kValidInverseWorld = 1u << 0,
    kValidWorldView = 1u << 1,
    kValidWorldViewProj = 1u << 2,
    kValidInverseView = 1u << 3,  // of the camera: survives a world change
    kValidDirMatrix = 1u << 4,    // g_dirMatrix (the original's +0x1a0, validity bit 0x10)
};
uint32_t g_valid = 0;
Mat g_inverseWorld = Identity();
Mat g_inverseView = Identity();
float g_worldViewRegisters[16];
float g_worldViewProjRegisters[16];
// What the world matrix was set from (the twelve floats of the RW matrix; g_worldSourceKnown false for the 4x4 setter
// and after a camera change): setting the same matrix again keeps the products.
float g_worldSource[12];
bool g_worldSourceKnown = false;
// The cache's RwMatrix copy of the world (+0x50): its axes, position and flags word (+0x0c: rwMATRIXTYPENORMAL 1,
// rwMATRIXTYPEORTHOGONAL 2, the identity bits 0x20000). WorldDirToObject / WorldPointToObject choose their path by the
// flags, not by what the matrix holds (the game writes scaled matrices under any of the flag values).
RwMatrix g_worldRw = {};
uint32_t g_worldFlags = 0;
RwMatrix g_dirMatrix = {};  // +0x1a0 for a world without type flags: the orthonormalised inverse

const Mat& InverseWorld() {
    if ((g_valid & kValidInverseWorld) == 0) {
        g_inverseWorld = g_hasWorld ? InvertAffine(g_world) : Identity();
        g_valid |= kValidInverseWorld;
    }
    return g_inverseWorld;
}

const Mat& InverseView() {
    if ((g_valid & kValidInverseView) == 0) {
        g_inverseView = InvertAffine(g_view);
        g_valid |= kValidInverseView;
    }
    return g_inverseView;
}
}  // namespace

// 0x00247e88 SetShaderObjectWorldMatrix
void ShaderMatrixCache_SetWorld(const RwMatrix* world) {
    if (world != nullptr) {
        const float source[12] = {world->right.x, world->right.y, world->right.z, world->up.x,  world->up.y,  world->up.z,
                                  world->at.x,    world->at.y,    world->at.z,    world->pos.x, world->pos.y, world->pos.z};
        // The same matrix as the one in the cache (bit for bit): the world and its products stay.
        if (g_hasWorld && g_worldSourceKnown && world->flags == g_worldFlags &&
            std::memcmp(source, g_worldSource, sizeof source) == 0) {
            return;
        }
        std::memcpy(g_worldSource, source, sizeof source);
        g_worldSourceKnown = true;
        g_world = FromRw(*world);
        g_worldRw = *world;
        g_worldFlags = world->flags;
        g_hasWorld = true;
    } else {
        if (!g_hasWorld) return;  // already without a world (the identity): its products stay
        g_world = Identity();
        g_hasWorld = false;
        g_worldSourceKnown = false;
    }
    g_valid &= kValidInverseView;
}

// 0x002480b8 SetShaderObjectWorldMatrix4x4: the 4x4 copied into the cache's RW matrix (its flags word cleared of the
// identity bits 0x20003) and its four rows (+0x10..+0x40), the world valid (+0x260 bit 0) and the products' validity
// bits (2-6) cleared; null: the world invalid and the products' bits cleared.
void ShaderMatrixCache_SetWorld4x4(const Homogeneous4x4* world) {
    g_valid &= kValidInverseView;
    g_worldSourceKnown = false;
    if (world == nullptr) {
        g_world = Identity();
        g_hasWorld = false;
        return;
    }
    Mat r = Identity();
    for (int row = 0; row < 4; ++row)
        for (int c = 0; c < 4; ++c) r.m[row * 4 + c] = world->m[row][c];  // row vectors: (r, c) = column-vector (c, r)
    g_world = r;
    g_worldRw.right = {world->m[0][0], world->m[0][1], world->m[0][2]};
    g_worldRw.up = {world->m[1][0], world->m[1][1], world->m[1][2]};
    g_worldRw.at = {world->m[2][0], world->m[2][1], world->m[2][2]};
    g_worldRw.pos = {world->m[3][0], world->m[3][1], world->m[3][2]};
    g_worldFlags &= ~0x20003u;  // (no type flags: the general inverse, the orthonormalised one for directions)
    g_worldRw.flags = g_worldFlags;
    g_hasWorld = true;
}

// 0x00247ff8 BeginCameraUpdateAndCacheShaderMatrices (after RwCameraBeginUpdate): the view and projection copied from
// the backend, the world matrix cleared (its validity bit is not set again until SetShaderObjectWorldMatrix).
void ShaderMatrixCache_BeginCamera() {
    float view[16], viewProj[16];
    RwDevice_GetViewMatrix(view);
    RwDevice_GetViewProjection(viewProj);
    // PERF: the device's matrices as last copied (every atomic's render calls this): unchanged ones keep the view, the
    // projection and the eye's inverse; only the world is cleared, as before.
    static float s_view[16], s_viewProj[16];
    static bool s_known = false;
    if (!s_known || std::memcmp(view, s_view, sizeof view) != 0 || std::memcmp(viewProj, s_viewProj, sizeof viewProj) != 0) {
        std::memcpy(s_view, view, sizeof view);
        std::memcpy(s_viewProj, viewProj, sizeof viewProj);
        s_known = true;
        g_view = FromFloats(view);
        // The cache's view is the PSGL model-view matrix (0x00cf9d60), which BeginPSGLCameraUpdate 0x738a68 builds from the
        // inverse of the camera frame's LTM with the x and the z rows negated (0x738c88..0x738cec: -right.x, right.y,
        // -right.z, the same for up and at; x to the right of the screen, the camera looking down -z, as OpenGL has it).
        // The device's view is the plain inverse (RW's camera x points to the left, z forward; its projection undoes the
        // x), so the two rows are negated here. What reads them: u_f44WorldView[0] (the camera's right axis of every
        // environment map lookup: GetCameraEnvTexCoord / GetCameraEnvTexCoordLS / GetRwCameraEnvTexCoord) and the depth of
        // field's camera z (mul(u_f44WorldView, position).z). The eye position (the inverse's translation) is the same.
        for (int c = 0; c < 4; ++c) {
            g_view.m[c * 4 + 0] = -g_view.m[c * 4 + 0];
            g_view.m[c * 4 + 2] = -g_view.m[c * 4 + 2];
        }
        g_viewProj = FromFloats(viewProj);
        g_valid = 0;
    }
    g_world = Identity();
    g_hasWorld = false;
    g_worldSourceKnown = false;
    g_valid &= kValidInverseView;
}

// 0x00248710 GetTransposedWorldViewProjectionMatrix: with a world matrix world * VP (row vectors), else VP.
void GetTransposedWorldViewProjectionMatrix(float out[16]) {
    if ((g_valid & kValidWorldViewProj) == 0) {
        ToRegisters(g_hasWorld ? Multiply(g_viewProj, g_world) : g_viewProj, g_worldViewProjRegisters);
        g_valid |= kValidWorldViewProj;
    }
    std::memcpy(out, g_worldViewProjRegisters, sizeof g_worldViewProjRegisters);
}

// 0x002485f8 GetTransposedWorldViewMatrix
void GetTransposedWorldViewMatrix(float out[16]) {
    if ((g_valid & kValidWorldView) == 0) {
        ToRegisters(g_hasWorld ? Multiply(g_view, g_world) : g_view, g_worldViewRegisters);
        g_valid |= kValidWorldView;
    }
    std::memcpy(out, g_worldViewRegisters, sizeof g_worldViewRegisters);
}

// 0x00248878 ShaderMatrixCache_WorldPointToObject / 0x00248ae0 ShaderMatrixCache_WorldDirToObject. The original picks
// the transform by the flags word of the world's RwMatrix (+0x50 -> +0x0c), whatever the matrix holds:
//   - no world, or one flagged identity (0x20003): the input as it is;
//   - rwMATRIXTYPENORMAL (bit 0): the matrix is taken for orthonormal and its transpose is used: a point is
//     ((p - pos) . right, . up, . at) (Mat4_InverseTransformPoints 0x2405b0), a direction (d . right, d . up, d . at)
//     (Mat4_TransformVectorsInline 0x240520). A scaled matrix under this flag gives the direction times the scale (and
//     the point times its square), not the inverse's;
//   - else a point goes through the general inverse (Mat4_InvertGeneral 0x247548 into +0x160);
//   - else a direction: with rwMATRIXTYPEORTHOGONAL (bit 1) through +0x160 as it stands, without it through the
//     orthonormalised inverse (RwMatrixOrthoNormalize of +0x160 into +0x1a0: a unit direction whatever the scale).
// +0x160 "as it stands": the inverse is built on first use after a world set (validity bit 8), and with bit 1 the
// direction path would build the 4x4 TRANSPOSE there if it came first. It never does: every uniform list
// (ShaderGen_CollectVertexUniforms 0xf44c0) asks for a point before a direction (VSC_VIEW_POMHEIGHT with specular, which
// the special light needs, or VSC_WORLD_VIEWMATRIX, which precedes VSC_DIRLIGHT_DIR), so +0x160 holds the general inverse
// and the bit-1 direction is the inverse's, 1 / scale long. Until 2026-11-18 every path here was the true inverse: the
// same for an unscaled matrix; a scaled one without type flags (the collectable crystals, part of the vegetation) was
// lit 1 / scale times as strongly by the directional lights as on the PS3.
// NOT PORTED: without a world the original's direction path still goes by the flags of the last world set (a stale
// matrix that is not flagged identity rotates the direction); only lit draws without a frame (PTank) could see it.
void ShaderMatrixCache_WorldPointToObject(const float world[3], float object[3]) {
    if (!g_hasWorld || (g_worldFlags & 0x20003u) == 0x20003u) {
        object[0] = world[0];
        object[1] = world[1];
        object[2] = world[2];
        return;
    }
    if ((g_worldFlags & 1u) != 0) {
        const float x = world[0] - g_worldRw.pos.x, y = world[1] - g_worldRw.pos.y, z = world[2] - g_worldRw.pos.z;
        object[0] = z * g_worldRw.right.z + x * g_worldRw.right.x + y * g_worldRw.right.y;
        object[1] = z * g_worldRw.up.z + x * g_worldRw.up.x + y * g_worldRw.up.y;
        object[2] = z * g_worldRw.at.z + x * g_worldRw.at.x + y * g_worldRw.at.y;
        return;
    }
    const Mat& inv = InverseWorld();
    for (int r = 0; r < 3; ++r) {
        object[r] = static_cast<float>(inv.m[r] * world[0] + inv.m[4 + r] * world[1] + inv.m[8 + r] * world[2] + inv.m[12 + r]);
    }
}

void ShaderMatrixCache_WorldDirToObject(const float world[3], float object[3]) {
    if (!g_hasWorld || (g_worldFlags & 0x20003u) == 0x20003u) {
        object[0] = world[0];
        object[1] = world[1];
        object[2] = world[2];
        return;
    }
    if ((g_worldFlags & 1u) != 0) {
        const float x = world[0], y = world[1], z = world[2];
        object[0] = z * g_worldRw.right.z + x * g_worldRw.right.x + y * g_worldRw.right.y;
        object[1] = z * g_worldRw.up.z + x * g_worldRw.up.x + y * g_worldRw.up.y;
        object[2] = z * g_worldRw.at.z + x * g_worldRw.at.x + y * g_worldRw.at.y;
        return;
    }
    const Mat& inv = InverseWorld();
    if ((g_worldFlags & 2u) != 0) {
        for (int r = 0; r < 3; ++r) {
            object[r] = static_cast<float>(inv.m[r] * world[0] + inv.m[4 + r] * world[1] + inv.m[8 + r] * world[2]);
        }
        return;
    }
    if ((g_valid & kValidDirMatrix) == 0) {
        RwMatrix inverse = {};
        inverse.right = {static_cast<float>(inv.m[0]), static_cast<float>(inv.m[1]), static_cast<float>(inv.m[2])};
        inverse.up = {static_cast<float>(inv.m[4]), static_cast<float>(inv.m[5]), static_cast<float>(inv.m[6])};
        inverse.at = {static_cast<float>(inv.m[8]), static_cast<float>(inv.m[9]), static_cast<float>(inv.m[10])};
        inverse.pos = {static_cast<float>(inv.m[12]), static_cast<float>(inv.m[13]), static_cast<float>(inv.m[14])};
        inverse.flags = 0;
        RwMatrixOrthoNormalize(&g_dirMatrix, &inverse);
        g_valid |= kValidDirMatrix;
    }
    // Mat4_TransformVector 0x247228 (RwV3dTransformVectors): d.x * right + d.y * up + d.z * at
    object[0] = world[0] * g_dirMatrix.right.x + world[1] * g_dirMatrix.up.x + world[2] * g_dirMatrix.at.x;
    object[1] = world[0] * g_dirMatrix.right.y + world[1] * g_dirMatrix.up.y + world[2] * g_dirMatrix.at.y;
    object[2] = world[0] * g_dirMatrix.right.z + world[1] * g_dirMatrix.up.z + world[2] * g_dirMatrix.at.z;
}

void ShaderMatrixCache_GetEyeWorld(float eye[3]) {
    const Mat& inv = InverseView();
    eye[0] = static_cast<float>(inv.m[12]);
    eye[1] = static_cast<float>(inv.m[13]);
    eye[2] = static_cast<float>(inv.m[14]);
}
