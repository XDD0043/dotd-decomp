// Mat4.h - the game's matrix helpers (original unit Mat4.cpp, 0x23f048-0x241c78) over CMatrix34, the
// RwMatrix layout. The RwMatrix* thunks are how game code reaches RenderWare's matrix functions
// (Renderware/rwcore/RwMatrix.h); they hand the matrix over as a CMatrix34.
#pragma once
#include <cstdint>

#include "k2000/math/CMatrix34.h"

struct CLine2D;
struct CVector2;

// 0x0023f968 RwMatrixDestroy_Thunk: RwMatrixDestroy (0x758890), its result returned.
int32_t RwMatrixDestroy_Thunk(CMatrix34* matrix);
// 0x0023fa68 RwMatrixCreate_Thunk: RwMatrixCreate (0x7588f0): a new identity matrix from RW's free list.
CMatrix34* RwMatrixCreate_Thunk();
// 0x0023f648 Mat4_OrthoNormalizeInPlace: RwMatrixOrthoNormalize (0x758d48) of the matrix into itself.
void Mat4_OrthoNormalizeInPlace(CMatrix34* matrix);
// 0x00240498 Mat4_RotateInPlace: rotates the matrix by `angle` degrees about `axis` (post-concatenated), keeping
// its position, and clears the internal-identity flag (0x20000).
void Mat4_RotateInPlace(CMatrix34* matrix, const CVector3* axis, float angle);
// 0x0023fd30 Mat4_SetBasisFromAtUp: right = normalised (up x at) when its squared length is at least
// 0.0175f, then up = right x at, at copied, flags = 3; otherwise the matrix is left alone. Returns whether
// it wrote.
int32_t Mat4_SetBasisFromAtUp(CMatrix34* m, const CVector3* at, const CVector3* up);
// 0x0023fe58 Mat4_SetBasisFromAtRight (step 6 CLIMB): up = normalised (at x right) when its squared length is at
// least 0.0175f, then right = up x at, at copied, flags = 3; otherwise the matrix is left alone. Returns whether it wrote.
int32_t Mat4_SetBasisFromAtRight(CMatrix34* m, const CVector3* at, const CVector3* right);
// 0x0023fa90 Mat4_SetBasisFromRightUp: at = normalised right x up when its squared length is at least 0.0175f, right
// copied, up = at x right, flags = 3; otherwise the matrix is left alone. Returns whether it wrote.
int32_t Mat4_SetBasisFromRightUp(CMatrix34* m, const CVector3* right, const CVector3* up);
// 0x00241688 Mat4_SetRotationAboutAxis_maybe: the rotation of `angle` radians about axis 0 (z), 1 (y) or 2
// (x) in the 3x3 part of `m`, flags = 3.
void Mat4_SetRotationAboutAxis(float angle, CMatrix34* m, int32_t axis);
// 0x0023f7b0 Mat4_TransformVectors: RwV3dTransformVectors (0x75e910) of `count` vectors through `m` (no position).
void Mat4_TransformVectors(const CMatrix34* m, CVector3* out, const CVector3* in, int32_t count);
// 0x0023f7e8 Mat4_TransformPoints: RwV3dTransformPoints (0x75e850) of `count` points through `m`.
void Mat4_TransformPoints(const CMatrix34* m, CVector3* out, const CVector3* in, int32_t count);
// 0x0023f878 Mat4_Invert_maybe: RwMatrixInvert (0x7586d8) of `in` into `out`.
void Mat4_Invert(CMatrix34* out, const CMatrix34* in);
// 0x0023f788 Mat4_Multiply: RwMatrixMultiply (through its TocBridge) of a by b into out (step 5).
void Mat4_Multiply(CMatrix34* out, const CMatrix34* a, const CMatrix34* b);
// 0x0023f048 Seg2D_IntersectCircle (XXL2 CLine2D::FindCircleIntersections): the times (0..1, within 1e-5) where the
// segment meets the circle of `radius` around `center`, smaller first: 0, 1 (in t0) or 2 hits. A zero segment: none.
uint8_t Seg2D_IntersectCircle(float radius, const CLine2D* segment, const CVector2* center, float* t0, float* t1);
// 0x0023f238 Seg2D_IntersectSegment (XXL2 CLine2D::FindLineIntersection): the times on both segments where they cross
// (each within -1e-5..1.00001); both are written before they are checked. Parallel: no crossing.
uint8_t Seg2D_IntersectSegment(const CLine2D* a, const CLine2D* b, float* ta, float* tb);
// 0x0023ff80 Mat4_BuildFromUpAndForward: right = normalised up x forward, up, at = right x up (flags 3) unless the cross
// product is too short (squared length below 0.0175f): then nothing is written and 0 returned.
int32_t Mat4_BuildFromUpAndForward(CMatrix34* m, const CVector3* up, const CVector3* forward);
// 0x002400a8 Mat4_SetBasisFromUpAt: at = normalised at x up, right = up x at, up (flags 3), or 0 as above.
int32_t Mat4_SetBasisFromUpAt(CMatrix34* m, const CVector3* up, const CVector3* at);
// 0x00241118 Mat4_RotateLocalXDeg / 0x002413d0 Mat4_RotateLocalYDeg: the matrix turned by `degrees` about its own x / y
// axis (the other two rows rotated, flag 0x20000 cleared).
void Mat4_RotateLocalXDeg(float degrees, CMatrix34* m);
void Mat4_RotateLocalYDeg(float degrees, CMatrix34* m);
// 0x002419c0 Mat4_RotateLocalZDeg: the same about the local z axis (right and up rotated; step 6).
void Mat4_RotateLocalZDeg(float degrees, CMatrix34* m);
