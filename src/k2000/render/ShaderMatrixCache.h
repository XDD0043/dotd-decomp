// ShaderMatrixCache.h - the matrices the shader uniforms are built from (C2.4 step 3). Original unit:
// ShaderMatrixCache.cpp (0x247988-0x248e28): an object at g_ShaderManagerPSGL +0x60 holding the PSGL view and
// projection matrices (copied at the camera update, 0x247ff8), the object's world matrix (0x247e88 / 0x2480b8) and
// the products the uniforms ask for, each computed on first use.
//
// The original keeps the matrices as row-vector 4x4s (RW: p' = p * M) and hands the shader the transposed products
// (the Cg uniform tables are in constant registers: `mul(M, v)` with M the register rows). Here the view and the
// view-projection come from RwDevice (the matrices the GL backend draws with, column-major and for column vectors),
// and the register layout is produced by transposing: `out[r * 4 + c]` is element (r, c) of the column-vector matrix.
#pragma once
#include <cstdint>

struct RwMatrix;

// 0x00247e88 SetShaderObjectWorldMatrix: the object's world matrix (an RW matrix); null clears it (the products then
// fall back to the view / view-projection alone).
void ShaderMatrixCache_SetWorld(const RwMatrix* world);
// 0x00247ff8 BeginCameraUpdateAndCacheShaderMatrices: takes the current camera's view and view-projection from the
// device; the world matrix is cleared.
void ShaderMatrixCache_BeginCamera();
// 0x00248710 GetTransposedWorldViewProjectionMatrix: transpose(world * view * projection) as constant registers.
void GetTransposedWorldViewProjectionMatrix(float out[16]);
// 0x002485f8 GetTransposedWorldViewMatrix: transpose(world * view) as constant registers.
void GetTransposedWorldViewMatrix(float out[16]);
// 0x00248878 ShaderMatrixCache_WorldPointToObject / 0x00248ae0 ShaderMatrixCache_WorldDirToObject: a world point /
// direction in the object's space (the inverse of the world matrix).
void ShaderMatrixCache_WorldPointToObject(const float world[3], float object[3]);
void ShaderMatrixCache_WorldDirToObject(const float world[3], float object[3]);
// The camera's position in world space (the inverse view's translation).
void ShaderMatrixCache_GetEyeWorld(float eye[3]);
