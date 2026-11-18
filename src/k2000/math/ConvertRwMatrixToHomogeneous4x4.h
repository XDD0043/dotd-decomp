// ConvertRwMatrixToHomogeneous4x4.h - the K engine's 16-byte aligned 4x4 (row vectors: rows right, up, at, pos) made
// from an RW matrix (ConvertRwMatrixToHomogeneous4x4.cpp).
#pragma once

struct RwMatrix;

struct alignas(16) Homogeneous4x4 {
    float m[4][4];
};

// 0x002472f0 ConvertRwMatrixToHomogeneous4x4
void ConvertRwMatrixToHomogeneous4x4(Homogeneous4x4* out, const RwMatrix* matrix);
// 0x002473e0 KStub_Nop_2473e0 (the constructor; the destructor KStub_Nop_2471d0 is empty too)
void Homogeneous4x4_Construct(Homogeneous4x4* matrix);
// 0x002474b8 CopyMatrix4x4: the 16 floats of `in` copied to `out` column by column (no transpose); a null `in` copies
// nothing. (ShaderMatrixCache_CopyProjectionFromPSGL / CopyViewFromPSGL and BeginCameraUpdateAndCacheShaderMatrices call it.)
void CopyMatrix4x4(float* out, const float* in);
