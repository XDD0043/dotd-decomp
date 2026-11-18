// CKPBuffer.cpp - reconstructed original translation unit 0x94eb0-0x97e50 (GAME_TOC1, main_toc1), 30 functions, 28 live.
// Primary class: CKPBuffer  key 0x34d  category Graphical  size 0x1c  vtable 0xb16e68
// Other owners: RwRaster (1), RenderBlurPassChainNoShader_maybe (1), RenderMultiTapScreenBlur (1), DrawFullscreenRasterQuadEx (1), DrawFullscreenRasterQuad (1), DownSampleAndBlurRaster_maybe (1), CopySceneColorToRaster (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x94eb0  CKPBuffer_Delete
//   [x] 0x94f00  CKPBuffer_AddInstanceRef_maybe  (inlined in Load)
//   [x] 0x94f30  CKPBuffer_RegisterRenderTarget_maybe
//   [x] 0x94f78  CKPBuffer_UpdateRenderTargetDesc_maybe
//   [x] 0x94fa0  CKPBuffer_AddFrameRequest_maybe
//   [x] 0x94fb8  CKPBuffer_vf74  (ComputeSortingCoef)
//   [ ] 0x94fe0  RwRaster_GetSubRectUVBounds_maybe  [dead]
//   [ ] 0x950e0  RegisterCKPBufferClass
//   [ ] 0x951c0  _GLOBAL__I_951c0
//   [x] 0x951d0  CKPBuffer_BindSharedRasterToTexture_maybe
//   [ ] 0x95210  RenderBlurPassChainNoShader_maybe  (only without the shader pipelines, which the PS3 always has: not ported)  [platform]  (the fixed-function blur, only without the shader pipelines, which the PS3 build always has (ConstructShaderManagerPSGL); CPostRenderingFx::Render keeps the shader path)
//   [ ] 0x95ba8  CKPBuffer_Save
//   [x] 0x95bd0  CKPBuffer_RecursiveRegistration  (CKPBuffer::RecursiveRegistration)
//   [x] 0x95c50  CKPBuffer_ReleaseSharedRasters_maybe
//   [x] 0x95e08  CKPBuffer_Destroy
//   [x] 0x95e40  CKPBuffer_DeleteArray
//   [x] 0x95ee8  CKPBuffer_Create
//   [x] 0x95f40  RenderMultiTapScreenBlur
//   [x] 0x96670  CKPBuffer_CreateArray
//   [x] 0x96728  CKPBuffer_Enqueue  (UpdateAndExtract)
//   [x] 0x967a0  CKPBuffer_Load
//   [x] 0x96880  CKPBuffer_EnsureRenderTargets_maybe
//   [ ] 0x96c50  DrawFullscreenRasterQuadEx_maybe  [dead]
//   [x] 0x97288  DrawFullscreenRasterQuad
//   [x] 0x97830  CKPBuffer_CopyDofDepthToAlpha_maybe
//   [x] 0x97a20  DownSampleAndBlurRaster_maybe
//   [x] 0x97b68  CopySceneColorToRaster
//   [x] 0x97c28  CKPBuffer_Draw  (Render)
//   [x] 0x97db0  CLightManager_Delete  (the registry factory: DOTD_DECLARE_FACTORIES(CLightManager))
//   [x] 0x97e00  CLightSet_Delete  (the registry factory: DOTD_DECLARE_FACTORIES(CLightSet))
//
//   [x] 0x99c948  CKPBuffer_IsKindOfClass  [inline]
//   [x] 0x99c970  CKPBuffer_GetClassType  [inline]
//   [x] 0x99c978  CKPBuffer_GetClassID  [inline]
//   [x] 0x99c980  CKPBuffer_vf70  [inline]  (CanBeUpdated)
//   [x] 0x99c988  CKPBuffer_Destructor  [inline]
//   [x] 0x99c9a8  CKPBuffer_DeletingDestructor  [inline]
#include "k2000/graphical/memory/CKPBuffer.h"

#include <cstring>

#include "crt/ppc_ops.h"

#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwDevice.h"
#include "Renderware/rwcore/RwIm2D.h"
#include "Renderware/rwcore/RwIm3D.h"
#include "Renderware/rwcore/RwTexture.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/graphical/render/CPostRenderingFx.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKCoreManager.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/misc/Engine.h"
#include "k2000/render/CRenderer.h"
#include "k2000/render/CShaderManagerPSGL.h"

int32_t CKPBuffer::m_si32RefCount = 0;
void* CKPBuffer::m_spBackBufferTexture = nullptr;
int32_t CKPBuffer::m_si32OriginalScreenWidth = -1;
int32_t CKPBuffer::m_si32OriginalScreenHeight = -1;
uint32_t CKPBuffer::m_sui32NbRenderTargets = 0;
uint8_t CKPBuffer::m_sbRenderTargetsDirty = 0;
CKPBuffer::SRenderTarget CKPBuffer::m_saRenderTargets[4] = {};
uint16_t CKPBuffer::m_sui16FrameRequests = 0;
RwRaster* CKPBuffer::m_spaSharedRasters[4] = {nullptr, nullptr, nullptr, nullptr};
RwRaster* CKPBuffer::m_spUnk64 = nullptr;
RwRaster* CKPBuffer::m_spSceneCopy = nullptr;
uint16_t CKPBuffer::m_sui16LastFrame = 0;

namespace {
void* StateWord(intptr_t value) { return reinterpret_cast<void*>(value); }
const uint8_t kColorWhite[4] = {0xff, 0xff, 0xff, 0xff};  // 0x00c50dfc
// The camera context the passes draw with (its UI camera is 0x00c5c9c4, its main camera 0x00c5c9cc: CameraContext_Init
// stores them at +0xb4 / +0xbc of 0x00c5c910).
CameraContext* Context() { return static_cast<CameraContext*>(g_pEngine->m_cameraContext); }
// The renderer's scene colour raster (graphic +4 -> renderer +0x28 -> camera context +0x1c).
RwRaster* SceneColorRaster() { return g_pEngine->m_graphic->m_renderer->m_cameraContext->m_pSceneColorRaster; }
// RwTextureSetRaster (TocBridge 0x98e220): a camera raster's colour target is what the device samples
// (RwDevice_GetRasterTexture).
void TextureSetRaster(RwTexture* texture, RwRaster* raster) { RwTextureSetRaster(texture, raster); }
}  // namespace

// 0x00095c50 CKPBuffer_ReleaseSharedRasters_maybe: one object fewer; the last one destroys the shared rasters, the
// registered targets (from the last; the count back to 0), +0x64 / +0x68 and releases the "backbuffer" texture, and the
// remembered screen size is forgotten (-1).
void CKPBuffer::ReleaseSharedRasters() {
    --m_si32RefCount;
    if (m_si32RefCount != 0) return;
    for (RwRaster*& raster : m_spaSharedRasters) {
        if (raster != nullptr) {
            RwRasterDestroy(raster);
            raster = nullptr;
        }
    }
    while (m_sui32NbRenderTargets != 0) {
        --m_sui32NbRenderTargets;
        SRenderTarget& target = m_saRenderTargets[m_sui32NbRenderTargets];
        if (target.m_pRaster != nullptr) {
            RwRasterDestroy(target.m_pRaster);
            target.m_pRaster = nullptr;
        }
    }
    if (m_spUnk64 != nullptr) {
        RwRasterDestroy(m_spUnk64);
        m_spUnk64 = nullptr;
    }
    if (m_spSceneCopy != nullptr) {
        RwRasterDestroy(m_spSceneCopy);
        m_spSceneCopy = nullptr;
    }
    if (m_spBackBufferTexture != nullptr) {
        TextureSetRaster(static_cast<RwTexture*>(m_spBackBufferTexture), nullptr);  // RwTextureSetRaster(texture, 0)
        TextureRef_Release(m_spBackBufferTexture);                                 // RwTextureDestroy
        m_spBackBufferTexture = nullptr;
    }
    if (m_si32RefCount != 0) return;
    m_si32OriginalScreenHeight = -1;
    m_si32OriginalScreenWidth = -1;
}

// 0x00095e08 CKPBuffer_Destroy (vt+0x10): the shared rasters released, then IRendableObject_Destroy.
void CKPBuffer::Destroy() {
    ReleaseSharedRasters();
    IRendableObject::Destroy();
}

// 0x00094f30 CKPBuffer_RegisterRenderTarget_maybe. BUG(original): no bound check (a fifth target writes over +0x4c).
int32_t CKPBuffer::RegisterRenderTarget(int32_t sizeIndex, uint8_t alpha8) {
    m_sbRenderTargetsDirty = 1;
    const uint32_t index = m_sui32NbRenderTargets;
    m_saRenderTargets[index].m_i32SizeIndex = sizeIndex;
    m_saRenderTargets[index].m_bDirty = 1;
    m_saRenderTargets[index].m_i32RefCount = 0;
    m_saRenderTargets[index].m_bAlpha8 = alpha8;
    m_saRenderTargets[index].m_pRaster = nullptr;
    m_sui32NbRenderTargets = index + 1;
    return static_cast<int32_t>(index);
}

// 0x00094f78 CKPBuffer_UpdateRenderTargetDesc_maybe
void CKPBuffer::UpdateRenderTargetDesc(int32_t index, int32_t sizeIndex) {
    m_sbRenderTargetsDirty = 1;
    m_saRenderTargets[index].m_bDirty = 1;
    m_saRenderTargets[index].m_i32SizeIndex = sizeIndex;
}

// 0x00094fa0 CKPBuffer_AddFrameRequest_maybe
void CKPBuffer::AddFrameRequest() { m_sui16FrameRequests = static_cast<uint16_t>(m_sui16FrameRequests + 1); }

// 0x00094fb8 CKPBuffer_vf74 (ComputeSortingCoef): 10000 for the far-to-near order (1), else 0: drawn first in its stage.
void CKPBuffer::ComputeSortingCoef(int32_t sortingOrder) { m_fSortingCoef = sortingOrder != 1 ? 0.0f : 10000.0f; }

// 0x00096728 CKPBuffer_Enqueue (vt+0x58): once per render frame (the frame counter 0x00c29694) into stage 16 (+0x40 of
// the stage array), then a frame request.
void CKPBuffer::UpdateAndExtract(float, RenderQueue** stages, IKTime*, RwCamera*, int32_t) {
    if (m_ui16LastPushedFrame != g_ui16RenderFrameCounter) {
        m_ui16LastPushedFrame = g_ui16RenderFrameCounter;
        stages[16]->Add(this);
    }
    m_sui16FrameRequests = static_cast<uint16_t>(m_sui16FrameRequests + 1);
}

// 0x00096880 CKPBuffer_EnsureRenderTargets_maybe
RwRaster* CKPBuffer::EnsureRenderTargets() {
    const RwRaster* frameBuffer = Context()->m_pMainCamera->frameBuffer;
    const int32_t height = frameBuffer->height;
    const int32_t width = frameBuffer->width;
    int32_t depth = 0x18;
    int32_t flags = 0x605;  // rwRASTERTYPECAMERATEXTURE | rwRASTERFORMAT888
    if ((g_pEngine->m_graphic->m_baHardwareCaps & 0x200) != 0 && g_pShaderManager->m_bShadersEnabled != 0 &&
        g_pShaderManager->m_i32ProfileMode == 6) {
        depth = 0x20;
        flags = 0x505;  // rwRASTERTYPECAMERATEXTURE | rwRASTERFORMAT8888
    }
    if (width != m_si32OriginalScreenWidth || height != m_si32OriginalScreenHeight) {
        for (RwRaster*& raster : m_spaSharedRasters) {
            if (raster != nullptr) {
                RwRasterDestroy(raster);
                raster = nullptr;
            }
        }
        for (uint32_t i = 0; i < m_sui32NbRenderTargets; ++i) {
            if (m_saRenderTargets[i].m_pRaster != nullptr) {
                RwRasterDestroy(m_saRenderTargets[i].m_pRaster);
                m_saRenderTargets[i].m_pRaster = nullptr;
            }
            m_saRenderTargets[i].m_bDirty = 1;
        }
        m_sbRenderTargetsDirty = 1;
        if (m_spUnk64 != nullptr) {
            RwRasterDestroy(m_spUnk64);
            m_spUnk64 = nullptr;
        }
        if (m_spSceneCopy != nullptr) RwRasterDestroy(m_spSceneCopy);
        m_spSceneCopy = nullptr;
        m_si32OriginalScreenWidth = width;
        m_si32OriginalScreenHeight = height;
        m_spaSharedRasters[0] = RwRasterCreate(width, height, depth, flags);
        m_spaSharedRasters[1] = RwRasterCreate(width >> 1, height >> 1, depth, flags);
        m_spaSharedRasters[2] = RwRasterCreate(width >> 2, height >> 2, depth, flags);
        m_spaSharedRasters[3] = RwRasterCreate(width >> 3, height >> 3, depth, flags);
        if (m_spBackBufferTexture != nullptr) TextureSetRaster(static_cast<RwTexture*>(m_spBackBufferTexture), m_spaSharedRasters[0]);
    }
    if (m_sbRenderTargetsDirty != 0) {
        m_sbRenderTargetsDirty = 0;
        for (uint32_t i = 0; i < m_sui32NbRenderTargets; ++i) {
            SRenderTarget& target = m_saRenderTargets[i];
            if (target.m_bDirty == 0) continue;
            if (target.m_pRaster != nullptr) RwRasterDestroy(target.m_pRaster);
            int32_t targetHeight = 8, targetWidth = 8;
            if (target.m_i32SizeIndex != -1) {
                const RwRaster* size = m_spaSharedRasters[target.m_i32SizeIndex];
                targetHeight = size->height;
                targetWidth = size->width;
            }
            int32_t targetDepth = depth, targetFlags = flags;
            if (target.m_bAlpha8 != 0) {
                targetDepth = 8;
                targetFlags = 0x2504;
            }
            target.m_pRaster = RwRasterCreate(targetWidth, targetHeight, targetDepth, targetFlags);
            target.m_bDirty = 0;
        }
    }
    return m_spUnk64;
}

// 0x000951d0 CKPBuffer_BindSharedRasterToTexture_maybe: the "backbuffer" texture shows the full-size shared raster.
void CKPBuffer_BindSharedRasterToTexture() {
    if (CKPBuffer::m_spBackBufferTexture != nullptr)
        TextureSetRaster(static_cast<RwTexture*>(CKPBuffer::m_spBackBufferTexture), CKPBuffer::m_spaSharedRasters[0]);
}

// 0x00097288 DrawFullscreenRasterQuad (see CKPBuffer.h). The quad covers the current camera's frame buffer in pixels
// (0, 0) - (w, h) at the Im2D near z with the reciprocal z 1 / far; vertex order (0, 0), (0, h), (w, 0), (w, h).
void DrawFullscreenRasterQuad(RwRaster* raster, int32_t srcBlend, int32_t destBlend, const uint8_t* color, uint8_t filter,
                              uint8_t flipV) {
    const float one = 1.0f;   // TOC -0x63b8
    const float zero = 0.0f;  // TOC -0x6384
    RwCamera* camera = RwDevice_GetCurrentCamera();
    const float nearZ = RwIm2DGetNearScreenZ();  // RWEngine +0x18
    const float recipZ = one / camera->farPlane;
    const RwRaster* target = camera->frameBuffer;
    float u0 = zero, u1 = one, v0 = zero, v1 = one;
    float rasterWidth = one, rasterHeight = one;
    const float targetWidth = static_cast<float>(target->width);
    const float targetHeight = static_cast<float>(target->height);
    if (raster != nullptr) {
        rasterWidth = static_cast<float>(raster->width);
        rasterHeight = static_cast<float>(raster->height);
        if (raster != raster->parent) {
            // A sub-raster: its rectangle in the parent.
            const RwRaster* parent = raster->parent;
            const float invParentHeight = one / static_cast<float>(parent->height);
            const float invParentWidth = one / static_cast<float>(parent->width);
            const float offsetX = static_cast<float>(raster->nOffsetX);
            const float offsetY = static_cast<float>(raster->nOffsetY);
            u1 = invParentWidth * (offsetX + rasterWidth);
            u0 = offsetX * invParentWidth;
            v0 = offsetY * invParentHeight;
            v1 = invParentHeight * (offsetY + rasterHeight);
        }
    } else {
        rasterWidth = one;  // BUG(original)-like: without a raster the sizes compared below are 1 and the target's
        rasterHeight = one;
    }
    if (flipV != 0) {
        const float swap = v1;
        v1 = v0;
        v0 = swap;
    }
    float du, dv;
    if (rasterWidth > targetWidth) {
        du = ((rasterWidth / targetWidth + zero) - one) / rasterWidth;
        dv = ((rasterHeight / targetHeight + zero) - one) / rasterHeight;
    } else if (rasterWidth == targetWidth) {
        dv = zero / rasterHeight;
        du = zero / rasterWidth;
    } else {
        du = (rasterWidth / (targetWidth + targetWidth) + zero) / rasterWidth;
        dv = (rasterHeight / (targetHeight + targetHeight) + zero) / rasterHeight;
    }
    const float t1 = v1 + dv, s1 = u1 + du, s0 = u0 + du, t0 = v0 + dv;
    RwIm2DVertex vertices[4];
    const float x[4] = {0.0f, 0.0f, targetWidth, targetWidth};
    const float y[4] = {0.0f, targetHeight, 0.0f, targetHeight};
    const float s[4] = {s0, s0, s1, s1};
    const float t[4] = {t0, t1, t0, t1};
    for (int i = 0; i < 4; ++i) {
        vertices[i].x = x[i];
        vertices[i].y = y[i];
        vertices[i].z = nearZ;
        vertices[i].emissiveColor = RwRGBA{color[0], color[1], color[2], color[3]};
        vertices[i].s = s[i];
        vertices[i].t = t[i];
        vertices[i].r = 0.0f;
        vertices[i].q = one;
        vertices[i].recipZ = recipZ;
    }
    RwRenderStateSet(rwRENDERSTATESRCBLEND, StateWord(srcBlend));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, StateWord(destBlend));
    // Vertex alpha: on unless the blend is ONE / ZERO with an opaque colour.
    const intptr_t vertexAlpha = (srcBlend == 2 && destBlend == 1) ? (color[3] != 0xff ? 1 : 0) : 1;
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, StateWord(vertexAlpha));
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, StateWord(0));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, StateWord(0));
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, StateWord(0));
    RwRenderStateSet(rwRENDERSTATECULLMODE, StateWord(1));
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, StateWord(filter != 0 ? 2 : 1));  // 2 - ((filter - 1) >> 31)
    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS, StateWord(3));                   // clamp
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION, StateWord(8));
    RwRenderStateSet(rwRENDERSTATESHADEMODE, StateWord(1));
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, raster != nullptr ? static_cast<void*>(raster->parent) : nullptr);
    RwIm2DRenderPrimitive(rwPRIMTYPETRISTRIP, vertices, 4);  // RWEngine +0x30
}

namespace {
// 0x00a6f480 / 0x00a6f498 (TOC -0x638c + 0x60 / + 0x78): the index lists of the blur's fans: the centre and the first
// ring, then the centre and every further ring (copied onto the stack, memcpy 0xb8 bytes).
const RwImVertexIndex kBlurFirstRing[6] = {0, 1, 2, 3, 4, 1};
const RwImVertexIndex kBlurOuterRings[46] = {0,    5,    6,    7,    8,    5,    9,    0xa,  0xb,  0xc,  9,    0xd,
                                             0xe,  0xf,  0x10, 0xd,  0x11, 0x12, 0x13, 0x14, 0x11, 0x15, 0x16, 0x17,
                                             0x18, 0x15, 0x19, 0x1a, 0x1b, 0x1c, 0x19, 0x1d, 0x1e, 0x1f, 0x20, 0x1d,
                                             0x21, 0x22, 0x23, 0x24, 0x21, 0x25, 0x26, 0x27, 0x28, 0x25};
}  // namespace

// 0x00095f40 RenderMultiTapScreenBlur: `source` drawn into `destination` (the UI camera on it, no depth buffer) as
// concentric full-screen rectangles: a centre vertex at `center` (0..1 of the destination; the colour white with the
// centre intensity's alpha) and `rings` rings of four corners whose texture rectangle grows by `start` + k `step` texels
// (the vertical by the destination's aspect), their alpha the border intensity's falling by 1 / (rings + 1) per ring;
// the texture coordinates flipped vertically with `flipV`. The first ring's fan is drawn ONE / ZERO without vertex
// alpha, the others' (with more than one ring) SRCALPHA / INVSRCALPHA with it; no Z, fog or culling, filtered, clamped,
// alpha test always, Gouraud. The camera's rasters put back.
void RenderMultiTapScreenBlur(RwRaster* source, RwRaster* destination, uint32_t rings, const float* center, float start,
                              float step, float borderIntensity, float centerIntensity, uint8_t flipV) {
    RwCamera* camera = Context()->m_pUICamera;  // 0x00c5c9c4
    const float kFull = 255.0f;                // TOC -0x6370
    const float one = 1.0f;                    // TOC -0x63b8
    const float zero = 0.0f;                   // TOC -0x6384
    const float width = static_cast<float>(static_cast<double>(static_cast<int32_t>(destination->width)));
    const float height = static_cast<float>(static_cast<double>(static_cast<int32_t>(destination->height)));
    const float sourceWidth = static_cast<float>(static_cast<double>(static_cast<int32_t>(source->width)));
    const float sourceHeight = static_cast<float>(static_cast<double>(static_cast<int32_t>(source->height)));
    RwRaster* savedFrameBuffer = camera->frameBuffer;
    RwRaster* savedZBuffer = camera->zBuffer;
    uint8_t color[4] = {kColorWhite[0], kColorWhite[1], kColorWhite[2], kColorWhite[3]};
    color[3] = static_cast<uint8_t>(ppc::fctiwz(borderIntensity * kFull));  // the low byte
    const float texelU = one / sourceWidth;
    const float texelV = one / sourceHeight;
    RwImVertexIndex outerIndices[46];
    std::memcpy(outerIndices, kBlurOuterRings, sizeof outerIndices);
    const float nearZ = RwIm2DGetNearScreenZ();  // RWEngine +0x18
    const float recipZ = one / camera->nearPlane;
    const float stepV = step * (height / width);
    float flipBase = zero;
    float flipScale = one;
    if (flipV != 0) {
        flipBase = one;
        flipScale = -1.0f;  // TOC -0x636c
    }
    // The centre (vertex 0) and four corners per ring.
    // BUG(original): the stack holds the centre and ten rings (the index lists too); more rings run past it.
    RwIm2DVertex vertices[1 + 4 * 10];
    {
        RwIm2DVertex& c = vertices[0];
        const float v = ppc::fmadds(texelV, zero, center[1]);
        const float u = ppc::fmadds(texelU, zero, center[0]);
        c.x = width * center[0];
        c.y = height * center[1];
        c.z = nearZ;
        c.emissiveColor.red = color[0];
        c.emissiveColor.green = color[1];
        c.emissiveColor.blue = color[2];
        c.emissiveColor.alpha = static_cast<uint8_t>(ppc::fctiwz(centerIntensity * kFull));
        c.s = u;
        c.t = v;
        c.r = zero;
        c.q = one;
        c.recipZ = recipZ;
    }
    if (rings != 0) {
        const float fall = static_cast<float>(static_cast<double>(color[3])) /
                           static_cast<float>(static_cast<double>(static_cast<uint64_t>(rings + 1)));
        const uint8_t fallByte = static_cast<uint8_t>(ppc::fctiwz(fall));
        float offsetV = start;  // f1, growing by the aspect-scaled step
        float offsetU = start;  // f9, growing by the step
        for (uint32_t ring = 0; ring < rings; ++ring) {
            float top = ppc::fmadds(texelV, offsetV + zero, zero);
            float bottom = ppc::fmadds(texelV, zero - offsetV, one);
            const float left = ppc::fmadds(texelU, offsetU + zero, zero);
            const float right = ppc::fmadds(texelU, zero - offsetU, one);
            offsetV = offsetV + stepV;
            offsetU = offsetU + step;
            top = ppc::fmadds(flipScale, top, flipBase);
            bottom = ppc::fmadds(flipScale, bottom, flipBase);
            const float x[4] = {zero, width, width, zero};
            const float y[4] = {zero, zero, height, height};
            const float s[4] = {left, right, right, left};
            const float t[4] = {top, top, bottom, bottom};
            for (uint32_t k = 0; k < 4; ++k) {
                RwIm2DVertex& v = vertices[1 + ring * 4 + k];
                v.x = x[k];
                v.y = y[k];
                v.z = nearZ;
                v.emissiveColor.red = color[0];
                v.emissiveColor.green = color[1];
                v.emissiveColor.blue = color[2];
                v.emissiveColor.alpha = color[3];
                v.s = s[k];
                v.t = t[k];
                v.r = zero;
                v.q = one;
                v.recipZ = recipZ;
            }
            color[3] = static_cast<uint8_t>(color[3] - fallByte);
        }
    }
    camera->frameBuffer = destination;
    camera->zBuffer = nullptr;
    if (BeginRenderCameraUpdate(camera) != nullptr) {
        const int32_t passes = rings > 1 ? 2 : 1;
        for (int32_t pass = 0; pass < passes; ++pass) {
            if (pass == 0) {
                RwRenderStateSet(rwRENDERSTATEZTESTENABLE, StateWord(0));
                RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, StateWord(0));
                RwRenderStateSet(rwRENDERSTATEFOGENABLE, StateWord(0));
                RwRenderStateSet(rwRENDERSTATECULLMODE, StateWord(1));
                RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, StateWord(2));
                RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS, StateWord(3));
                RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION, StateWord(8));
                RwRenderStateSet(rwRENDERSTATESHADEMODE, StateWord(2));
                RwRenderStateSet(rwRENDERSTATETEXTURERASTER, source);
                RwRenderStateSet(rwRENDERSTATESRCBLEND, StateWord(2));
                RwRenderStateSet(rwRENDERSTATEDESTBLEND, StateWord(1));
                RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, StateWord(0));
                RwImVertexIndex firstIndices[6];
                std::memcpy(firstIndices, kBlurFirstRing, sizeof firstIndices);
                RwIm2DRenderIndexedPrimitive(rwPRIMTYPETRIFAN, vertices, 5, firstIndices, 6);  // RWEngine +0x34
            } else {
                RwRenderStateSet(rwRENDERSTATESRCBLEND, StateWord(5));
                RwRenderStateSet(rwRENDERSTATEDESTBLEND, StateWord(6));
                RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, StateWord(1));
                RwIm2DRenderIndexedPrimitive(rwPRIMTYPETRIFAN, vertices, static_cast<RwInt32>(rings * 4 + 1), outerIndices,
                                             static_cast<RwInt32>(rings * 5 - 4));
            }
        }
    }
    RwCameraEndUpdate(camera);
    camera->frameBuffer = savedFrameBuffer;
    camera->zBuffer = savedZBuffer;
}

// 0x00097a20 DownSampleAndBlurRaster_maybe
void DownSampleAndBlurRaster_maybe(RwRaster* source, RwRaster* destination) {
    CameraContext* context = Context();
    RwCamera* camera = context->m_pUICamera;
    RwRaster* savedFrameBuffer = camera->frameBuffer;
    camera->frameBuffer = context->m_unk14;
    RwRaster* savedZBuffer = camera->zBuffer;
    camera->zBuffer = nullptr;
    if (BeginRenderCameraUpdate(camera) != nullptr) {
        g_pShaderManager->m_ui32Immediate2DMode = 4;  // down-sample 4x4
        DrawFullscreenRasterQuad(source, kBlendTableSrc[0], kBlendTableDest[0], kColorWhite, 1, 1);
    }
    RwCameraEndUpdate(camera);
    camera->frameBuffer = destination;
    if (BeginRenderCameraUpdate(camera) != nullptr) {
        g_pShaderManager->m_ui32Immediate2DMode = 2;  // Gaussian blur 5x5
        DrawFullscreenRasterQuad(context->m_unk14, kBlendTableSrc[0], kBlendTableDest[0], kColorWhite, 1, 1);
    }
    RwCameraEndUpdate(camera);
    camera->frameBuffer = savedFrameBuffer;
    camera->zBuffer = savedZBuffer;
}

// 0x00097b68 CopySceneColorToRaster
void CopySceneColorToRaster(RwRaster* destination) {
    CameraContext* context = Context();
    RwCamera* camera = context->m_pUICamera;
    RwRaster* savedFrameBuffer = camera->frameBuffer;
    RwRaster* savedZBuffer = camera->zBuffer;
    RwRaster* sceneColor = SceneColorRaster();
    camera->frameBuffer = destination;
    camera->zBuffer = nullptr;
    if (BeginRenderCameraUpdate(camera) != nullptr) DrawFullscreenRasterQuad(sceneColor, 2, 1, kColorWhite, 1, 0);
    RwCameraEndUpdate(camera);
    camera->frameBuffer = savedFrameBuffer;
    camera->zBuffer = savedZBuffer;
}

// 0x00097830 CKPBuffer_CopyDofDepthToAlpha_maybe (render states 0x1e / 0x1f: the alpha channel's blend, set to ONE /
// ZERO for the draw and to the colour blend afterwards).
void CKPBuffer_DrawAltSceneComposite() {
    const CPostRenderingFx* postFx = static_cast<const CPostRenderingFx*>(g_pEngine->m_coreManager->GetObjectByClassKey(0x38d));
    if ((g_pEngine->m_graphic->m_baHardwareCaps & 0x200) == 0) return;
    if (postFx == nullptr) return;  // DEV guard: the original reads the object without a test (every level has one)
    if (g_pShaderManager->m_bShadersEnabled == 0 || g_pShaderManager->m_i32ProfileMode != 6 || (postFx->m_BitProperties & 0x400) == 0) return;
    RwRaster* alternative = Context()->m_unk10;
    RwRenderStateSet(rwRENDERSTATESRCBLENDALPHA, StateWord(2));
    RwRenderStateSet(rwRENDERSTATEDESTBLENDALPHA, StateWord(1));
    g_pShaderManager->m_ui32Immediate2DMode = 3;  // copy to alpha
    DrawFullscreenRasterQuad(alternative, 1, 2, kColorWhite, 1, 1);
    int32_t src = 0, dest = 0;
    RwRenderStateGet(rwRENDERSTATESRCBLEND, &src);
    RwRenderStateGet(rwRENDERSTATEDESTBLEND, &dest);
    RwRenderStateSet(rwRENDERSTATESRCBLENDALPHA, StateWord(src));
    RwRenderStateSet(rwRENDERSTATEDESTBLENDALPHA, StateWord(dest));
}

// 0x00097c28 CKPBuffer_Draw (vt+0x5c), with the post effects on (graphic caps 0x400): the render states pushed, the
// depth of field composite, the current camera's update ended, the shared rasters made, the frame noted (+0x6c), the
// scene colour raster copied into the full-size shared raster with the UI camera (no z buffer), the camera's update begun
// again, the states popped.
void CKPBuffer::Render(IKTime* /*frameClock*/) {
    if ((g_pEngine->m_graphic->m_baHardwareCaps & 0x400) == 0) return;
    PushRenderStates(g_pRenderStateRenderer);
    CKPBuffer_DrawAltSceneComposite();
    RwCamera* current = RwDevice_GetCurrentCamera();
    RwCameraEndUpdate(current);
    EnsureRenderTargets();
    if (m_sui16LastFrame != g_ui16RenderFrameCounter) m_sui16LastFrame = g_ui16RenderFrameCounter;
    RwCamera* camera = Context()->m_pUICamera;
    RwRaster* sceneColor = SceneColorRaster();
    RwRaster* savedFrameBuffer = camera->frameBuffer;
    camera->frameBuffer = m_spaSharedRasters[0];
    RwRaster* savedZBuffer = camera->zBuffer;
    camera->zBuffer = nullptr;
    if (BeginRenderCameraUpdate(camera) != nullptr) DrawFullscreenRasterQuad(sceneColor, 2, 1, kColorWhite, 1, 0);
    RwCameraEndUpdate(camera);
    camera->frameBuffer = savedFrameBuffer;
    camera->zBuffer = savedZBuffer;
    BeginRenderCameraUpdate(current);
    PopRenderStates(g_pRenderStateRenderer);
}

// 0x00095ee8 CKPBuffer_Create: the inlined IRendableObject part, in the original's store order; +0x0c
// and +0x18 are left as they are.
CKPBuffer::CKPBuffer() {
    m_pLightSet = nullptr;
    m_pNextAccumulatedObject = nullptr;
    m_BitProperties = 0;
    m_pPriorityParent = 0;
}

// 0x000967a0 CKPBuffer_Load. Every object reads the same texture reference into the static slot (LVL000:
// two objects, both "backbuffer texture_00").
int32_t CKPBuffer::Load(IKFile* file, int32_t type) {
    IRendableObject::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) {
        m_ui16LastPushedFrame = 0;
        return 1;
    }
    IKFile_ReadTextureRef(file, &m_spBackBufferTexture, 0);
    if (m_spBackBufferTexture != nullptr) TextureRef_AddRef(m_spBackBufferTexture);  // RwTexture +0x54 refCount + 1
    const int32_t count = m_si32RefCount;
    if (count == 0) {
        m_si32OriginalScreenHeight = -1;
        m_si32OriginalScreenWidth = -1;
    }
    m_si32RefCount = count + 1;
    m_ui16LastPushedFrame = 0;
    return 1;
}

#include "k2000/logic/CKSavingManager.h"

// 0x00095bd0 CKPBuffer_RecursiveRegistration
void CKPBuffer::RecursiveRegistration(int32_t type) {
    if (type != 0) return;
    IRendableObject::RecursiveRegistration(0);
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}
