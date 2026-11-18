// CKPBuffer.h - the shared off-screen render targets (key 0x34d, vtable 0xb16e68, size 0x1c). Original
// unit: CKPBuffer.cpp (0x94eb0-0x97e50). XXL2: K/KModules/KGL/Main/CKPBuffer.h, where everything but the
// IRendableObject part is static (m_si32RefCount, m_si32OriginalScreenWidth/Height, the rasters).
// DotD keeps a halfword per object (+0x18) and its statics in .bss/.data next to each other.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/graphical/IRendableObject.h"

struct RwRaster;
struct RwTexture;

class CKPBuffer : public IRendableObject {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0xd)
    DOTD_DECLARE_FACTORIES(CKPBuffer)

    CKPBuffer();                   // 0x00095ee8 CKPBuffer_Create (inlined)
    ~CKPBuffer() override {}       // 0x0099c988 / 0x0099c9a8 CKPBuffer_Destructor / _DeletingDestructor: the vtables only
    // vt+0x08 0x99c948
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x34d || key == 0xa8d || key == 0xc; }
    void Destroy() override;                            // vt+0x10 0x00095e08 CKPBuffer_Destroy
    // vt+0x24 0x00095bd0 CKPBuffer_RecursiveRegistration: type 0 only, IRendableObject's, then itself registered.
    void RecursiveRegistration(int32_t type) override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000967a0 CKPBuffer_Load
    // vt+0x58 0x00096728 CKPBuffer_UpdateAndExtract: once per render frame into stage 16 (the post stage), and a frame
    // request counted.
    void UpdateAndExtract(float maxDistanceSquared, RenderQueue** stages, IKTime* frameClock, RwCamera* camera, int32_t distanceCull) override;
    // vt+0x5c 0x00097c28 CKPBuffer_Render: the scene colour raster copied into the full-size shared raster.
    void Render(IKTime* frameClock) override;
    int32_t CanBeUpdated() override { return 0; }       // vt+0x70 0x99c980 (the owners enqueue it)
    void ComputeSortingCoef(int32_t sortingOrder) override;  // vt+0x74 0x00094fb8

    // One registered render target (0x10 bytes; CKPBuffer_RegisterRenderTarget_maybe).
    struct SRenderTarget {
        RwRaster* m_pRaster;     // +0x00 created by EnsureRenderTargets
        int32_t m_i32SizeIndex;  // +0x04 the shared raster whose size it takes (-1: 8 x 8)
        int32_t m_i32RefCount;   // +0x08 the users drawing with it this frame
        uint8_t m_bAlpha8;       // +0x0c an 8-bit raster (format 0x2504) instead of the colour format
        uint8_t m_bDirty;        // +0x0d to be (re)created
        uint8_t m_pad0e[2];
    };

    // Statics (XXL2 names where XXL2's Load does the same).
    static int32_t m_si32RefCount;               // 0x00c5c87c Load counts the objects
    static void* m_spBackBufferTexture;          // 0x00c5c8cc the "backbuffer texture_00" texture (ours); RwTexture*
    static int32_t m_si32OriginalScreenWidth;    // 0x00c296b0 (.data, -1) CKPBuffer_EnsureRenderTargets_maybe compares the raster width
    static int32_t m_si32OriginalScreenHeight;   // 0x00c296b4 (.data, -1) ... and height
    // The rest of the shared block 0x00c5c87c (+0x04 .. +0x6c).
    static uint32_t m_sui32NbRenderTargets;      // 0x00c5c880
    static uint8_t m_sbRenderTargetsDirty;       // 0x00c5c884
    static SRenderTarget m_saRenderTargets[4];   // 0x00c5c888 (no bound check in RegisterRenderTarget)
    static uint16_t m_sui16FrameRequests;        // 0x00c5c8c8 (+0x4c) frame requests (UpdateAndExtract, AddFrameRequest)
    static RwRaster* m_spaSharedRasters[4];      // 0x00c5c8d0 (+0x54) the frame-buffer size, a half, a quarter, an eighth
    static RwRaster* m_spUnk64;                  // 0x00c5c8e0 (+0x64) destroyed by EnsureRenderTargets, never created
    static RwRaster* m_spSceneCopy;              // 0x00c5c8e4 (+0x68) CPostRenderingFx's copy raster: never created
    static uint16_t m_sui16LastFrame;            // 0x00c5c8e8 (+0x6c) the render frame of the last Render

    // 0x00094f30 CKPBuffer_RegisterRenderTarget_maybe: a target of the size of shared raster `sizeIndex`; its index.
    static int32_t RegisterRenderTarget(int32_t sizeIndex, uint8_t alpha8);
    // 0x00094f78 CKPBuffer_UpdateRenderTargetDesc_maybe
    static void UpdateRenderTargetDesc(int32_t index, int32_t sizeIndex);
    // 0x00094fa0 CKPBuffer_AddFrameRequest_maybe
    static void AddFrameRequest();
    // 0x00096880 CKPBuffer_EnsureRenderTargets_maybe: the shared rasters (re)created at the main camera's frame-buffer
    // size when it changed (32-bit camera textures with the shader pipelines, else 24-bit), the dirty registered targets
    // (re)created; returns +0x64.
    static RwRaster* EnsureRenderTargets();
    // 0x00095c50 CKPBuffer_ReleaseSharedRasters_maybe
    static void ReleaseSharedRasters();

    uint16_t m_ui16LastPushedFrame;  // +0x18 Load sets 0 (XXL2 has m_sui16LastPushedFrame, static) _maybe
    uint8_t m_pad1a[2];              // +0x1a never written
};
DOTD_ASSERT_SIZE(CKPBuffer, 0x1c);
DOTD_ASSERT_OFFSET(CKPBuffer, m_ui16LastPushedFrame, 0x18);

// ---- the full-screen passes of CKPBuffer.cpp ------------------------------------------------------------------
// 0x00097288 DrawFullscreenRasterQuad: `raster` over the current camera's frame buffer as an Im2D triangle strip, with
// the blend (rwBLEND* src / dest), `color` (RGBA bytes) as the vertex colour, linear (`filter`) or nearest filtering,
// clamped, no z, no fog, no culling, flat shading, and the texture coordinates flipped vertically with `flipV`.
// A raster larger than the target is sampled with an offset of (raster / target - 1) / raster, a smaller one with half
// a target texel.
void DrawFullscreenRasterQuad(RwRaster* raster, int32_t srcBlend, int32_t destBlend, const uint8_t* color, uint8_t filter,
                              uint8_t flipV);
// 0x00095f40 RenderMultiTapScreenBlur (CKPBuffer.cpp): the radial blur of `source` into `destination`: concentric
// rectangles (`rings`, their texture rectangles `start` + k `step` texels in) around `center` faded from the border
// intensity to the centre intensity (see the definition).
void RenderMultiTapScreenBlur(RwRaster* source, RwRaster* destination, uint32_t rings, const float* center, float start,
                              float step, float borderIntensity, float centerIntensity, uint8_t flipV);
// 0x00097a20 DownSampleAndBlurRaster_maybe: `source` down-sampled 4x4 into the camera context's quarter raster (+0x14,
// shader mode 4), then blurred 5x5 into `destination` (mode 2), both with the UI camera.
void DownSampleAndBlurRaster_maybe(RwRaster* source, RwRaster* destination);
// 0x00097b68 CopySceneColorToRaster: the scene colour raster copied into `destination` with the UI camera.
void CopySceneColorToRaster(RwRaster* destination);
// 0x00097830 CKPBuffer_CopyDofDepthToAlpha_maybe: with the depth of field path (graphic caps 0x200, the RSX profiles,
// the post object's bit 10) the alternative scene raster (+0x10) drawn in copy-alpha mode (3) with the blend ONE / ZERO.
void CKPBuffer_DrawAltSceneComposite();
