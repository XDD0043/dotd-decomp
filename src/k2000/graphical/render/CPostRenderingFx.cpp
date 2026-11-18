// CPostRenderingFx.cpp - reconstructed original translation unit 0xb4808-0xb5c70 (GAME_TOC1, main_toc1), 17 functions, 16 live.
// Primary class: CPostRenderingFx  key 0x38d  category Graphical  size 0x64  vtable 0xb17780
// Other owners: CBlurData (1), CHDRData (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xb4808  CPostRenderingFx_Delete
//   [x] 0xb4858  CPostRenderingFx_RecursiveRegistration  (CPostRenderingFx::RecursiveRegistration)
//   [ ] 0xb48f0  CPostRenderingFx_Save
//   [x] 0xb48f8  CPostRenderingFx_vf78  (CPostRenderingFx::Vf78, empty in the header)
//   [ ] 0xb4900  RegisterCPostRenderingFxClass
//   [ ] 0xb4978  _GLOBAL__I_b4978
//   [ ] 0xb4988  CPostRenderingFx_RegisterRenderTargets_maybe  [dead]
//   [x] 0xb49d8  CPostRenderingFx_DeleteArray
//   [x] 0xb4a78  CPostRenderingFx_Create
//   [x] 0xb4ad0  CPostRenderingFx_Enqueue  (UpdateAndExtract)
//   [x] 0xb4c78  CPostRenderingFx_CreateArray
//   [x] 0xb4d28  CPostRenderingFx_Draw  (Render)
//   [x] 0xb57a0  CPostRenderingFx_Destroy  (inherited: IRendableObject_Destroy)
//   [x] 0xb57c8  CPostRenderingFx_PostLoad
//   [x] 0xb58c0  CPostRenderingFx_Load
//   [x] 0xb5bd0  CBlurData_Delete  (the registry factory: DOTD_DECLARE_FACTORIES(CBlurData))
//   [x] 0xb5c20  CHDRData_Delete  (the registry factory: DOTD_DECLARE_FACTORIES(CHDRData))
//
//   [x] 0x9a0c58  CPostRenderingFx_GetClassType  [inline]
//   [x] 0x9a0c60  CPostRenderingFx_GetClassID  [inline]
//   [x] 0x9a0c68  CPostRenderingFx_GetSerializationFlags  [inline]
//   [x] 0x9a0c70  CPostRenderingFx_IsKindOfClass  [inline]
//   [x] 0x9a0ca8  CPostRenderingFx_DeletingDestructor  [inline]
//   [x] 0x9a0cf0  CPostRenderingFx_Destructor  [inline]
#include "k2000/graphical/render/CPostRenderingFx.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwDevice.h"
#include "Renderware/rwcore/RwTexture.h"
#include "crt/ppc_ops.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/core/Stub.h"
#include "k2000/graphical/CBlurData.h"
#include "k2000/graphical/CDistortionScreenFx.h"
#include "k2000/graphical/CHDRData.h"
#include "k2000/graphical/memory/CKPBuffer.h"
#include "k2000/io/IKFile.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/misc/Engine.h"
#include "k2000/render/CRenderer.h"
#include "k2000/render/CShaderManagerPSGL.h"
#include "k2000/render/MeshShaderPassState.h"
#include "k2000/system/IKTime.h"
#include "platform/gfx/mesh.h"

namespace {
const uint8_t kColorWhite[4] = {0xff, 0xff, 0xff, 0xff};  // 0x00c50dfc
const CVector3 kVectorZero = {0.0f, 0.0f, 0.0f};          // 0x00c50d64
const CVector3 kAxisZ = {0.0f, 0.0f, 1.0f};               // 0x00c50d4c
CameraContext* Context() { return static_cast<CameraContext*>(g_pEngine->m_cameraContext); }
// The depth of field path's condition (graphic caps 0x200, the shader pipelines on the RSX profiles, the object's 0x400).
bool DepthOfFieldPath(uint32_t flags) {
    return (g_pEngine->m_graphic->m_baHardwareCaps & 0x200) != 0 && g_pShaderManager->m_bShadersEnabled != 0 &&
           g_pShaderManager->m_i32ProfileMode == 6 && (flags & 0x400) != 0;
}
// The main camera's frame (0x00c5c9cc +4): its modelling matrix's direction (+0x30) and position (+0x40).
const RwMatrix& MainCameraFrameMatrix() { return RwCameraGetFrame(Context()->m_pMainCamera)->modelling; }
}  // namespace

// 0x000b57c8 CPostRenderingFx_PostLoad (type 0): the blur and HDR targets (the sizes of the shared rasters of their pass
// counts), the previous camera at the null vector looking along z, the CKPBuffer registered with the renderer
// (CRenderer_RegisterPostRenderingFx_maybe 0x9eaa0), the flags cleared.
int32_t CPostRenderingFx::PostLoad(int32_t type) {
    if (type == 0) {
        m_tBlurExternalRaster = static_cast<uint32_t>(CKPBuffer::RegisterRenderTarget(static_cast<int32_t>(m_ui32NbBlurGaussienPasses), 0));
        m_tHDRExternalRaster = static_cast<uint32_t>(CKPBuffer::RegisterRenderTarget(static_cast<int32_t>(m_ui32NbHDRGaussienPasses), 0));
        m_v3PreviousCameraPos = kVectorZero;
        m_v3PreviousCameraAt = kAxisZ;
        if (m_pPBuffer != nullptr) {
            g_pEngine->m_graphic->m_renderer->RegisterPostRenderingFx(m_pPBuffer);
            m_BitProperties = 0;
            return 1;
        }
    }
    m_BitProperties = 0;
    return 1;
}

// 0x000b4ad0 CPostRenderingFx_Enqueue (vt+0x58)
void CPostRenderingFx::UpdateAndExtract(float, RenderQueue** stages, IKTime* frameClock, RwCamera* camera, int32_t) {
    const uint32_t flags = m_BitProperties;
    if ((flags & 0x100) == 0 && (flags & 0x200) == 0 && !DepthOfFieldPath(flags) && (m_pDistortionFx->m_BitProperties & 0x100) == 0) {
        const RwMatrix& frame = MainCameraFrameMatrix();
        m_v3PreviousCameraPos.x = frame.pos.x;
        m_v3PreviousCameraPos.z = frame.pos.z;
        m_v3PreviousCameraPos.y = frame.pos.y;
        m_v3PreviousCameraAt.x = frame.at.x;
        m_v3PreviousCameraAt.z = frame.at.z;
        m_v3PreviousCameraAt.y = frame.at.y;
        return;
    }
    m_pPBuffer->UpdateAndExtract(0.0f, stages, frameClock, camera, 0);  // vt+0x58
    stages[16]->Add(this);
}

// 0x000b4d28 CPostRenderingFx_Draw (vt+0x5c), with the post effects on (graphic caps 0x400). The shared rasters hold the
// scene colour (CKPBuffer_Draw ran first in stage 16: its sorting coefficient is 10000). With the shader pipelines every
// effect's pass count is 2: the scene colour down-sampled 4x4 into the quarter raster and blurred 5x5 into the quarter
// shared raster (DownSampleAndBlurRaster_maybe); the HDR effect (0x200) then adds that blurred image over the frame
// `intensity` times (whole passes at full alpha, the remainder at its fraction of 255) in the HDR data's blend mode with
// its colour, in the shader mode that keeps the vertex alpha (5). The blur (0x100, motion blur from the camera's motion)
// is a blur node's (its radial blur, RenderMultiTapScreenBlur, drawn over the frame); the distortion grid (CDistortionScreenFx_Draw, with the queue's frame clock) is drawn
// while a distortion node runs; the depth of field (0x400) draws the alternative scene raster.
void CPostRenderingFx::Render(IKTime* frameClock) {
    if ((g_pEngine->m_graphic->m_baHardwareCaps & 0x400) == 0) return;
    const CHDRData* hdr = static_cast<const CHDRData*>(m_pHDRData);
    PushRenderStates(g_pRenderStateRenderer);
    RwCamera* camera = RwDevice_GetCurrentCamera();
    RwCameraEndUpdate(camera);
    RwRaster* sceneCopy = CKPBuffer::m_spSceneCopy;  // never created in DotD (CKPBuffer +0x68)
    if (sceneCopy != nullptr) CopySceneColorToRaster(sceneCopy);
    uint32_t flags = m_BitProperties;
    uint32_t passes = 0;
    uint32_t blurPasses = m_ui32NbBlurGaussienPasses;
    if ((flags & 0x100) != 0) passes = blurPasses;
    uint32_t hdrPasses = m_ui32NbHDRGaussienPasses;
    if ((flags & 0x200) != 0 && passes < hdrPasses) passes = hdrPasses;
    uint32_t dofPasses = m_unk54;
    if (DepthOfFieldPath(flags) && passes < dofPasses) passes = dofPasses;
    if (g_pShaderManager->m_bShadersEnabled == 0) {
        // RenderBlurPassChainNoShader_maybe 0x95210 (the fixed-function blur of the shared rasters): not ported, the shader pipelines
        // are always on (ConstructShaderManagerPSGL).
        if (passes != 0) DOTD_STUB_ONCE("CPostRenderingFx_Draw: RenderBlurPassChainNoShader_maybe without the shader pipelines");
    } else {
        blurPasses = 2;
        hdrPasses = 2;
        dofPasses = 2;
        if (passes != 0) {
            DownSampleAndBlurRaster_maybe(CKPBuffer::m_spaSharedRasters[0], CKPBuffer::m_spaSharedRasters[2]);
            flags = m_BitProperties;
        }
    }
    float blurStrength = 1.0f;     // f31: the blur's strength (1 without the motion settings)
    RwRaster* blurRaster = nullptr;  // r29: the blur target (set when the blur runs)
    if ((flags & 0x100) == 0) {
        const RwMatrix& frame = MainCameraFrameMatrix();
        m_v3PreviousCameraPos.x = frame.pos.x;
        m_v3PreviousCameraPos.z = frame.pos.z;
        m_v3PreviousCameraPos.y = frame.pos.y;
        m_v3PreviousCameraAt.x = frame.at.x;
        m_v3PreviousCameraAt.z = frame.at.z;
        m_v3PreviousCameraAt.y = frame.at.y;
    } else {
        // The blur (a blur node's CBlurData): with the motion settings the camera's turn since the last frame (its at
        // axis' change along its right / up axes, per second: at most 100 per second) moves the blur's centre off the
        // middle and, with the forward speed over the data's maximum, sets the strength (at most 1) and scales the
        // ring step; the radial blur of the shared raster into the blur target (RenderMultiTapScreenBlur), the camera
        // kept for the next frame.
        const CBlurData* blur = static_cast<const CBlurData*>(m_pBlurData);
        const RwMatrix& frame = MainCameraFrameMatrix();
        float center[2] = {0.5f, 0.5f};  // TOC -0x5c7c
        const float start = blur->m_fBlurStartOffset;
        float step = blur->m_fBlurIncOffset;
        blurStrength = 1.0f;  // TOC -0x5c78
        if (blur->m_bActivateMotionSettings != 0) {
            const float dt = frameClock->m_afDeltaTime[0];
            const float atX = frame.at.x - m_v3PreviousCameraAt.x;
            const float atY = frame.at.y - m_v3PreviousCameraAt.y;
            const float atZ = frame.at.z - m_v3PreviousCameraAt.z;
            const float moveX = frame.pos.x - m_v3PreviousCameraPos.x;
            const float moveY = frame.pos.y - m_v3PreviousCameraPos.y;
            const float moveZ = frame.pos.z - m_v3PreviousCameraPos.z;
            float perSecond = 9.99999924e+01f;  // TOC -0x5c70
            if (dt > 0.01f || dt == 0.01f) perSecond = 1.0f / dt;  // bge; TOC -0x5c74
            const float side = perSecond * ppc::fmadds(atZ, frame.right.z, ppc::fmadds(atX, frame.right.x, atY * frame.right.y));
            center[0] = 0.5f - side * blur->m_fCenterCoefficient;
            float strength = std::fabs(side * blur->m_fRotationSpeedCoefficient);
            const float lift = perSecond * ppc::fmadds(atZ, frame.up.z, ppc::fmadds(atX, frame.up.x, atY * frame.up.y));
            center[1] = 0.5f - lift * blur->m_fCenterCoefficient;
            const float turn = std::fabs(lift * blur->m_fRotationSpeedCoefficient);
            if (strength < turn) strength = turn;  // bge
            const float forward = ppc::fmadds(moveZ, frame.at.z, ppc::fmadds(moveX, frame.at.x, moveY * frame.at.y)) *
                                  (perSecond * blur->m_fSpeedCoefficient);
            float scale = strength;
            if (strength < std::fabs(forward)) scale = std::fabs(forward);  // bge
            step = step * scale;
            const float speed = std::fabs(forward / blur->m_fMaxEffectSpeed);
            if (strength < speed) strength = speed;  // bge
            if (!(strength < 1.0f)) strength = 1.0f;  // blt
            blurStrength = strength;
        }
        m_v3PreviousCameraPos.z = frame.pos.z;
        m_v3PreviousCameraPos.x = frame.pos.x;
        m_v3PreviousCameraPos.y = frame.pos.y;
        m_v3PreviousCameraAt.z = frame.at.z;
        m_v3PreviousCameraAt.x = frame.at.x;
        m_v3PreviousCameraAt.y = frame.at.y;
        CKPBuffer::SRenderTarget& target = CKPBuffer::m_saRenderTargets[m_tBlurExternalRaster];
        ++target.m_i32RefCount;
        blurRaster = target.m_pRaster;
        RenderMultiTapScreenBlur(CKPBuffer::m_spaSharedRasters[blurPasses], blurRaster, blur->m_ui8NbRadialPasses, center,
                                 start, step, blur->m_fBlurBorderIntensity, blur->m_fBlurCenterIntensity, 1);  // 0x00095f40
    }
    RwRaster* hdrRaster = nullptr;
    if ((m_BitProperties & 0x200) != 0) {
        if (hdr->m_bExtractLuminance == 0) {
            hdrRaster = CKPBuffer::m_spaSharedRasters[hdrPasses];
        } else {
            // The luminance: the blurred image times itself (SRCCOLOR / ZERO) into the HDR target.
            CKPBuffer::SRenderTarget& target = CKPBuffer::m_saRenderTargets[m_tHDRExternalRaster];
            hdrRaster = target.m_pRaster;
            ++target.m_i32RefCount;
            RwCamera* ui = Context()->m_pUICamera;
            RwRaster* savedFrameBuffer = ui->frameBuffer;
            ui->frameBuffer = hdrRaster;
            RwRaster* savedZBuffer = ui->zBuffer;
            ui->zBuffer = nullptr;
            if (BeginRenderCameraUpdate(ui) != nullptr)
                DrawFullscreenRasterQuad(CKPBuffer::m_spaSharedRasters[hdrPasses], 3, 1, kColorWhite, 1, 1);
            RwCameraEndUpdate(ui);
            ui->frameBuffer = savedFrameBuffer;
            ui->zBuffer = savedZBuffer;
        }
    }
    BeginRenderCameraUpdate(camera);
    if (sceneCopy != nullptr) DrawFullscreenRasterQuad(sceneCopy, 2, 1, kColorWhite, 1, 0);
    if ((m_BitProperties & 0x100) != 0) {
        // The blur target over the frame in the shader mode that keeps the vertex alpha (5): the data's colour, its alpha
        // the strength times 255 times the global intensity (+0x1c), the data's blend; its use count back.
        const CBlurData* blur = static_cast<const CBlurData*>(m_pBlurData);
        uint8_t color[4];
        std::memcpy(color, blur->m_cBlurColor, 4);
        color[3] = static_cast<uint8_t>(ppc::fctiwz(blurStrength * 255.0f * blur->m_fBlurGlobalIntensity));  // TOC -0x5c60
        g_pShaderManager->m_ui32Immediate2DMode = 5;
        DrawFullscreenRasterQuad(blurRaster, kBlendTableSrc[blur->m_eBlendMode], kBlendTableDest[blur->m_eBlendMode], color, 1, 1);
        --CKPBuffer::m_saRenderTargets[m_tBlurExternalRaster].m_i32RefCount;
    }
    CDistortionScreenFx* distortion = m_pDistortionFx;
    if ((distortion->m_BitProperties & 0x100) != 0) distortion->Render(frameClock);  // vt+0x5c (the distortion grid)
    if (DepthOfFieldPath(m_BitProperties)) {
        // The blurred image on texture unit 1 (RwPSGL_SetActiveTextureUnit / SetTextureRasterInternal), the main camera
        // back on the final colour, the alternative scene raster's full-size copy through the post depth of field shader
        // (mode 1), units 1 and 2 cleared.
        RwRaster* blurred = CKPBuffer::m_spaSharedRasters[dofPasses];
        dotd::gfx::DrawState sampler;
        sampler.linear = true;
        sampler.addressU = sampler.addressV = dotd::gfx::Address::kClamp;
        const uint32_t blurredTexture = RwDevice_GetRasterTexture(blurred);
        const int activeUnit = dotd::gfx::ActiveTextureUnit();  // RwPSGL_GetActiveTextureUnit_maybe, set back after the bind
        dotd::gfx::BindTextureUnit(1, blurredTexture, sampler);
        dotd::gfx::SetActiveTextureUnit(activeUnit);
        CameraContext* context = Context();
        RwCameraEndUpdate(context->m_pMainCamera);
        context->m_pMainCamera->frameBuffer = context->m_pFinalColorRaster;
        BeginRenderCameraUpdate(context->m_pMainCamera);
        g_pShaderManager->m_ui32Immediate2DMode = 1;
        DrawFullscreenRasterQuad(CKPBuffer::m_spaSharedRasters[0], kBlendTableSrc[0], kBlendTableDest[0], kColorWhite, 1, 1);
        BindTextureOnUnit(nullptr, 1);
        BindTextureOnUnit(nullptr, 2);
    }
    if ((m_BitProperties & 0x200) != 0) {
        uint8_t color[4];
        std::memcpy(color, hdr->m_cHDRColor, 4);
        float intensity = hdr->m_fHDRIntensity;
        const float zero = 0.0f;  // TOC -0x5c94
        const float one = 1.0f;   // TOC -0x5c78
        while (zero < intensity) {
            if (intensity <= zero) {
                color[3] = 0;
                intensity = intensity - one;
            } else if (one <= intensity) {
                color[3] = 0xff;
                intensity = intensity - one;
            } else {
                color[3] = static_cast<uint8_t>(ppc::fctiwz(intensity * 255.0f));  // TOC -0x5c60
                intensity = intensity - one;
            }
            g_pShaderManager->m_ui32Immediate2DMode = 5;
            DrawFullscreenRasterQuad(hdrRaster, kBlendTableSrc[hdr->m_eBlendMode], kBlendTableDest[hdr->m_eBlendMode], color, 1, 1);
        }
        if (hdr->m_bExtractLuminance != 0) {
            --CKPBuffer::m_saRenderTargets[m_tHDRExternalRaster].m_i32RefCount;
        }
    }
    CKPBuffer::m_sui16FrameRequests = static_cast<uint16_t>(CKPBuffer::m_sui16FrameRequests - 1);
    PopRenderStates(g_pRenderStateRenderer);
}

// 0x000b4a78 CPostRenderingFx_Create: the inlined IRendableObject part, in the original's store order.
CPostRenderingFx::CPostRenderingFx() {
    m_pLightSet = nullptr;
    m_pNextAccumulatedObject = nullptr;
    m_BitProperties = 0;
    m_pPriorityParent = 0;
}

// 0x000b58c0 CPostRenderingFx_Load
int32_t CPostRenderingFx::Load(IKFile* file, int32_t type) {
    IScreenFx::Load(file, type);  // the original calls IRendableObject_Load
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pPBuffer);
        IKFile_ReadRef(file, &m_pDistortionFx);
        ReadU32LE(file, &m_ui32NbBlurGaussienPasses);
        ReadU32LE(file, &m_ui32NbHDRGaussienPasses);
        ReadU32LE(file, &m_unk54);
        m_ui32NbHDRGaussienPasses = 3;
        ReadF32LE(file, &m_unk58);
        ReadF32LE(file, &m_unk5c);
        ReadF32LE(file, &m_unk60);
    }
    m_pDOFData = nullptr;
    m_pBlurData = nullptr;
    m_pHDRData = nullptr;
    return 1;
}

#include "k2000/logic/CKSavingManager.h"

// 0x000b4858 CPostRenderingFx_RecursiveRegistration
void CPostRenderingFx::RecursiveRegistration(int32_t type) {
    if (type != 0) return;
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
    m_pPBuffer->RecursiveRegistration(0);
}
