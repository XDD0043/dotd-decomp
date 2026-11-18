// Quat.h - the game's quaternion helpers (original unit Quat.cpp, 0x241c78-0x2436e8). A quaternion is
// four floats (x, y, z, w).
#pragma once
#include <cstdint>

#include "k2000/math/CMatrix34.h"
struct RwV3d;

// 0x00241d78 Quat_ToMatrixNormalizing_maybe: Quat_ToMatrix with the quaternion scaled by 2 / |q|^2 (not unit).
void Quat_ToMatrixNormalizing(const float* q, CMatrix34* m);
// 0x00241e48 Quat_ToMatrix: rotation part of `m` from q, position zeroed, flags 3.
void Quat_ToMatrix(const float* q, CMatrix34* m);
// 0x002420f8 Quat_FromMatrix (RtQuatConvertFromMatrix 0x007213b0): q = (x, y, z, w) from the rotation of the 16-float
// RwMatrix `m`; 0 when either pointer is null.
int32_t Quat_FromMatrix(float* q, const float* m);
// 0x00242728 Quat_Slerp: out = the spherical interpolation from a to b at t (b negated for the short way; linear
// above a dot of 0.9999). step 5, the shared helpers.
void Quat_Slerp(float t, float* out, const float* a, const float* b);
// 0x00242180 Quat_Normalize: q made unit length; (0, 0, 0, 1) when |q|^2 is not above 0.001.
void Quat_Normalize(float* q);
// 0x00243058 Quat_FromEulerDeg: q from three angles in degrees (the game's inlined cosf / sinf of the halves).
void Quat_FromEulerDeg(float* q, const float* degrees);
// 0x00241cc0 Quat_Multiply: out = a * b (the Hamilton product of (x, y, z, w) quaternions), with the original's
// stores and reloads (out may alias a or b).
void Quat_Multiply(float* out, const float* a, const float* b);
// 0x00242130 Quat_Rotate_maybe: RtQuatRotate (0x007216c8 through TocBridge 0x98e200) with rwCOMBINEPRECONCAT: q
// times the rotation of `angleDegrees` about `axis` (normalised first). Null when q or axis is null.
float* Quat_Rotate(float* q, const RwV3d* axis, float angleDegrees);
// The rest of the unit (C2.8 port-rest R01).
// 0x00241fd0 Quat_ToAxisAngle_maybe (RtQuatConvertToAxisAngle 0x00721510): the unit axis and the angle in degrees of q;
// returns q (null when a pointer is null).
const float* Quat_ToAxisAngle(const float* q, float* axis, float* angleDegrees);
// 0x00242158 RtQuatRotate_Thunk: RtQuatRotate with rwCOMBINEREPLACE: q = the rotation of `angleDegrees` about `axis`.
float* Quat_RotateReplace(float* q, const RwV3d* axis, float angleDegrees);
// 0x002423c8 Quat_Log_maybe: the quaternion logarithm (vector part times atan2f(|v|, w) / |v|, w = 0.5 ln |q|^2).
void Quat_Log(float* out, const float* q);
// 0x002424a0 Quat_ToEulerAngles_maybe: three angles in degrees from the unit quaternion (see Quat.cpp).
void Quat_ToEulerAngles(const float* q, float* out);
// 0x00242648 Quat_FromMatrixNormalized_maybe: Quat_FromMatrix, then made unit length ((0, 0, 0, 1) below |q|^2 0.001).
float* Quat_FromMatrixNormalized(float* q, const float* m);
