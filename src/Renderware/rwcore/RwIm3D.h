// RwIm3D.h - RenderWare's immediate-mode 3D API and render states, as the 2D code (Rt2d, the K 2D
// widgets) uses them. PS3: RwIm3DTransform 0x761400, RwIm3DRenderIndexedPrimitive 0x761220,
// RwIm3DRenderPrimitive 0x761028, RwIm3DEnd 0x760a90; the pipelines are PSGL's "OpenGLImmInstance.csl"
// (transform: keeps the pool, always succeeds) and "OpenGLSubmitNoLight.csl" (DrawPSGLImmediateGeometry
// 0x76b610: glDrawArrays / glDrawRangeElements, always returns TRUE). RwRenderStateSet/Get go through
// RWEngine +0x20 / +0x24 = RwPSGL_RenderStateSet 0x73c410 / RwPSGL_RenderStateGet 0x73c478.
//
// Every primitive is drawn through the device layer (rwcore/RwDevice.h, platform/gfx; nothing without a
// window) and recorded, with the render states in force and the transform, in the frame's immediate draw
// list, which the tests read.
#pragma once
#include <cstdint>
#include <vector>

#include "Renderware/rwcore/RwTypes.h"

// The render states the PSGL driver keeps (its state block at 0xcefb98 and texture stage 0 at 0xcefba4),
// with the values RwPSGL_SetupDefaultRenderStates_maybe (0x73cba0) gives them at device start.
struct RwIm3DRenderStates {
    void* textureRaster = nullptr;      // 1  (stage +0x00)
    RwInt32 textureFilter = 2;          // 9  (stage +0x04) rwFILTERLINEAR
    RwInt32 textureAddressU = 1;        // 3  (stage +0x08) rwTEXTUREADDRESSWRAP
    RwInt32 textureAddressV = 1;        // 4  (stage +0x0c)
    RwInt32 shadeMode = 2;              // 7  (+0x04) rwSHADEMODEGOURAUD
    RwInt32 zTestEnable = 1;            // 6  (+0xb0)
    RwInt32 zWriteEnable = 1;           // 8  (+0xb4)
    RwInt32 srcBlend = 5;               // 10 (+0xb8) rwBLENDSRCALPHA
    RwInt32 destBlend = 6;              // 11 (+0xbc) rwBLENDINVSRCALPHA
    RwInt32 vertexAlphaEnable = 0;      // 12 (+0xc0) stored as 0/1
    RwInt32 srcBlendAlpha = 5;          // 30 (+0xc4)
    RwInt32 destBlendAlpha = 6;         // 31 (+0xc8)
    RwInt32 fogColor = 0;               // 15 (+0xcc)
    RwInt32 fogType = 1;                // 16 (+0xd0) rwFOGTYPELINEAR
    RwReal fogDensity = 1.0f;           // 17 (+0xd4) a float; Get returns it truncated (fctidz)
    RwInt32 stencilFunction = 8;        // 25 (+0xe0) rwSTENCILFUNCTIONALWAYS
    RwInt32 stencilFunctionRef = 0;     // 26 (+0xe4)
    RwInt32 stencilFunctionMask = -1;   // 27 (+0xe8)
    RwInt32 stencilWriteMask = -1;      // 28 (+0xec)
    RwInt32 stencilFail = 1;            // 22 (+0xf0) rwSTENCILOPERATIONKEEP
    RwInt32 stencilZFail = 1;           // 23 (+0xf4)
    RwInt32 stencilPass = 1;            // 24 (+0xf8)
    RwInt32 cullEnabled = 1;            // 20 (+0x100) GL_CULL_FACE on
    RwInt32 cullFace = 2;               // 20 (+0x104) rwCULLMODECULLBACK; Get gives 1 when culling is off
    RwInt32 alphaTestFunction = 5;      // 29 (+0x108) rwALPHATESTFUNCTIONGREATER
    RwUInt8 alphaTestFunctionRef = 0;   // 32 (+0x10c, a byte; the GL ref is byte / 255 at +0x110)
    RwInt32 stencilEnable = 0;          // 21 (+0x234)
    RwInt32 fogEnable = 0;              // 14 (+0x1d4) stored as 0/1
};

// One recorded primitive: what DrawPSGLImmediateGeometry would draw. The vertices and the LTM are read
// at the Render call (the PS3 reads them through the pool's pointers when it draws).
struct RwIm3DDraw {
    RwPrimitiveType primType;
    RwUInt32 transformFlags;              // the RwIm3DTransform flags | rwIM3D_VERTEXXYZ | rwIM3D_VERTEXRGBA
    bool hasLtm;                          // false: the LTM pointer was null (identity)
    RwMatrix ltm;
    // The primitive's geometry is copied into the record only when nothing draws it (no GL device: the headless tests
    // read it). With a device the draw reads the caller's arrays directly, as the PS3 does, and the two arrays stay
    // empty (perf: the copies were 2% of a frame); numVertices / numIndices are always the primitive's counts.
    std::vector<RwIm3DVertex> vertices;   // the pool's numElements vertices
    bool indexed;                         // glDrawRangeElements (indices non-null) vs glDrawArrays
    std::vector<RwImVertexIndex> indices; // numIndices entries (after the line/triangle list rounding)
    RwUInt32 numVertices = 0;
    RwUInt32 numIndices = 0;
    RwIm3DRenderStates states;
};

// 0x00761400 RwIm3DTransform: opens the pool on pVerts and returns pVerts; null (E_RW 0x32) when
// numVerts > 0x10000. The vertex count is kept as 16 bits.
void* RwIm3DTransform(RwIm3DVertex* pVerts, RwUInt32 numVerts, RwMatrix* ltm, RwUInt32 flags);
// 0x00760a90 RwIm3DEnd: clears the pool; 0 when none was open.
RwBool RwIm3DEnd();
// 0x00761028 RwIm3DRenderPrimitive: draws the pool's numElements vertices; 0 without an open pool.
RwBool RwIm3DRenderPrimitive(RwPrimitiveType primType);
// 0x00761220 RwIm3DRenderIndexedPrimitive: line lists round numIndices down to a multiple of 2,
// triangle lists to a multiple of 3; 0 without an open pool.
RwBool RwIm3DRenderIndexedPrimitive(RwPrimitiveType primType, RwImVertexIndex* indices, RwInt32 numIndices);
// RwRenderStateSet / RwRenderStateGet (RWEngine +0x20 / +0x24). The value is the state's word, or the
// pointer for rwRENDERSTATETEXTURERASTER. 0 for the states the PSGL driver does not handle and for the
// values its setters reject.
RwBool RwRenderStateSet(RwRenderState state, void* value);
RwBool RwRenderStateGet(RwRenderState state, void* value);

// The current frame's recorded primitives (no PS3 counterpart). Cleared by RwIm3DBeginFrame.
const std::vector<RwIm3DDraw>& RwIm3DFrameDraws();
void RwIm3DBeginFrame();
// The render states in force now.
const RwIm3DRenderStates& RwIm3DCurrentStates();
// Back to the device-start state (no PS3 counterpart; for tests): default render states, no open pool,
// no recorded draws.
void RwIm3DResetForTest();
