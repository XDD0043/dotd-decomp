// RwDevice.h - the RenderWare device layer on top of platform/gfx: what the PS3's PSGL driver does with
// RW's rasters, cameras, render states and immediate/atomic geometry (RwPSGL_* in the library range
// 0x73c000-0x76c000), rewritten for the GL 3.3 backend. Not a port: the driver's output is a GPU command
// stream; here the same inputs become platform/gfx calls. Everything is a no-op without a device
// (headless tests): the draws are still recorded by RwIm3D / RpGeometry.
#pragma once
#include <cstdint>

#include "Renderware/rwcore/RwTypes.h"
#include "platform/gfx/device.h"

struct RwCamera;
struct RwIm3DDraw;
struct RwShim_DdsRaster;
struct RpAtomicDraw;
struct RwIm3DRenderStates;
struct RwIm2DVertex;

// The device texture of a raster (a DDS file or an RW Image's pixels), created on first use; 0 when the
// raster cannot be shown (unknown format) or without a device.
uint32_t RwDevice_GetRasterTexture(RwShim_DdsRaster* raster);

// ---- camera rasters (C2.4 step 8) ------------------------------------------------------------------------------
// The PSGL driver keeps a frame buffer object per camera-texture raster (rwRASTERTYPECAMERATEXTURE, 5); the camera
// raster (rwRASTERTYPECAMERA, 2) is the display, here the device's internal target. RwDevice_RasterTarget gives the
// device render target of a raster (0: the internal target; a camera texture's is created on first use).
uint32_t RwDevice_RasterTarget(const struct RwRaster* raster);
// RwRasterDestroy: the raster's device target goes too.
void RwDevice_ReleaseRaster(const struct RwRaster* raster);
// 0x00738758 PSGL_BindRasterRenderTarget_maybe: a camera texture's frame buffer bound (clears go there); and
// PSGL_UnbindRenderTarget_maybe: the display again.
void RwDevice_BindRasterRenderTarget(const struct RwRaster* raster);
void RwDevice_UnbindRenderTarget();
// 0x00738a68 BeginPSGLCameraUpdate / 0x00738988 EndPSGLCameraUpdate (the device's camera begin / end): the camera's
// frame buffer bound (a camera texture's frame buffer object; the display otherwise), the view and projection (a
// camera texture's projection is flipped vertically and the front faces turn clockwise, glScalef(1, -1, 1) /
// glFrontFace(GL_CW)), and without a z buffer the z test and z write states off until the end.
void RwDevice_BeginCameraUpdate(RwCamera* camera);
void RwDevice_EndCameraUpdate(RwCamera* camera);
// The shader bind callback of the Im2D pipeline (0x00735968 PSGLIm2D_SetShaderBindCallBack_maybe; the shader manager
// installs ShaderManagerPSGL_BindImmediate2DShaders_maybe). Called before every Im2D draw; when it returns a GL
// program it has bound that program and filled its uniforms, and the draw goes through it (vertices in clip space
// at the shader's input slots, the raster on unit 0 with the render states' sampler state); 0: the device's own 2D
// program.
typedef uint32_t (*RwDeviceIm2DShaderBind)();
void RwDevice_SetIm2DShaderBindCallBack(RwDeviceIm2DShaderBind callback);

// RwCameraBeginUpdate as far as drawing goes: the camera's view and projection become the device's
// (RW's camera space: x to the left, y up, z forward; the view window gives the half extents at z = 1).
void RwDevice_SetCamera(RwCamera* camera);
// The camera RwCameraBeginUpdate made current (RW: the engine's first field, curCamera); null before the first one.
RwCamera* RwDevice_GetCurrentCamera();
// The pose (an LTM) the camera is drawn and culled with: its frame's, or the debug free-fly camera's for the world cameras.
RwMatrix RwDevice_CameraPose(const RwCamera* camera);
RwCamera* RwDevice_GetCamera();
// The two cameras the debug free-fly camera replaces (the renderer's main and far cameras).
void RwDevice_RegisterWorldCameras(RwCamera* main, RwCamera* far);
// The matrices RwDevice_SetCamera made (column-major, column vectors: p_clip = viewProjection * p_world).
void RwDevice_GetViewMatrix(float out[16]);
void RwDevice_GetViewProjection(float out[16]);
// Replaces them (the debug free-fly camera and the tests: the draws use these until the next SetCamera).
void RwDevice_OverrideView(const float view[16], const float viewProj[16]);
// The blend / depth / cull part of the render states in force as a device state, and the alpha test function
// (RW rwALPHATESTFUNCTION*, 8 = always) and reference (0..1) that go to the shader.
struct RwTexture;
dotd::gfx::DrawState RwDevice_CurrentMeshState(int* alphaFunc, float* alphaRef);
// The sampler state (filter, addressing) of a texture, and its device texture in `texture` (0: none).
dotd::gfx::DrawState RwDevice_TextureState(const RwTexture* texture);

// Draws one recorded Im3D primitive / one atomic render (the PSGL immediate and atomic pipelines).
void RwDevice_DrawIm3D(const RwIm3DDraw& draw);
void RwDevice_DrawAtomic(const RpAtomicDraw& draw);
// Draws Im2D vertices (pixels of the current camera's raster, y down) with the render states in force.
void RwDevice_DrawIm2D(RwPrimitiveType primType, const RwIm2DVertex* vertices, RwInt32 numVertices,
                       const RwImVertexIndex* indices, RwInt32 numIndices);
