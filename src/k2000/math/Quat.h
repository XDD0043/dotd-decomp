// Quat.h - the game's quaternion helpers (original unit Quat.cpp, 0x241c78-0x2436e8). A quaternion is
// four floats (x, y, z, w).
#pragma once
#include <cstdint>

#include "k2000/math/CMatrix34.h"

// 0x00241e48 Quat_ToMatrix: rotation part of `m` from q, position zeroed, flags 3.
void Quat_ToMatrix(const float* q, CMatrix34* m);
// 0x002420f8 Quat_FromMatrix (RtQuatConvertFromMatrix 0x007213b0): q = (x, y, z, w) from the rotation of the 16-float
// RwMatrix `m`; 0 when either pointer is null.
int32_t Quat_FromMatrix(float* q, const float* m);
// 0x00242728 Quat_Slerp: out = the spherical interpolation from a to b at t (b negated for the short way; linear
// above a dot of 0.9999). step 5, the shared helpers.
void Quat_Slerp(float t, float* out, const float* a, const float* b);
