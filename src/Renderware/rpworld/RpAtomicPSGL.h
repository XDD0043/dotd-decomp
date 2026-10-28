// RpAtomicPSGL.h - drawing a streamed atomic through the PSGL atomic pipeline (C2.4 step 3). The PS3 runs
// RW_ExecutePipeline over the atomic's RxPipeline (RxPS3AllInOne node): the node instances the geometry into a
// resource entry (RwPSGL_CreateMeshInstanceData_maybe 0x6bb940: one 0x78-byte record per mesh with its GL buffers),
// then DispatchPSGLPipelineMeshes 0x6bafc8 calls, per mesh, the shader manager's PreparePSGLAtomicMeshShaders 0xff778
// and DrawPSGLMeshPasses 0xffe78 (installed by InstallPSGLMeshCallbacks 0xff960). The pipeline objects are not
// ported; the chain from the render callback to the two callbacks is.
#pragma once

struct RpAtomic;
struct RpGeometry;

// 0x0069d180 RW_RenderAtomicThroughPipeline for the geometries that come from the level files (a bin mesh or native
// data): instances the geometry on first use and draws its meshes. False (nothing done) for any other atomic and
// without a device; the caller then takes the immediate path.
bool RpAtomicPSGL_Render(RpAtomic* atomic);

// 0x006bb940 RwPSGL_CreateMeshInstanceData_maybe (and the PS3 AllInOne node's instance step for generic geometry):
// the device meshes of a geometry. False when the geometry has nothing to draw. Idempotent.
bool RpAtomicPSGL_InstanceGeometry(RpGeometry* geometry);
