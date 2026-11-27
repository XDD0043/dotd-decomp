// CameraContext.cpp - reconstructed original translation unit 0xa2cc0-0xa54c0 (GAME_TOC1, main_toc1), 35 functions, 20 live.
// Primary owner: CameraContext (not a registered class)
// Other owners: ConstructRendererCameraContext (2), WriteRasterImageToFile (1), ProjectWorldPointToScreen (1), DrawScreenColorQuad (1), DrawUIFontTextRotatedScaled (1), CaptureScreenshotToFile (1), ClearRendererCamera (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0xa2cc0  CameraContext_ResetReferenceAspect_maybe  [dead]
//   [ ] 0xa2cd8  CameraContext_UpdateAspectRatio_maybe  [dead]
//   [ ] 0xa2d48  CameraContext_UpdateInverseAspect_maybe  [dead]
//   [x] 0xa2dc8  CameraContext_GetViewWindow_maybe
//   [ ] 0xa2de0  KStub_Nop_a2de0  [dead]
//   [ ] 0xa2de8  KStub_Nop_a2de8  [dead]
//   [ ] 0xa2df0  KStub_Nop_a2df0  [dead]
//   [ ] 0xa2df8  KStub_Nop_a2df8  [dead]
//   [ ] 0xa2e00  KStub_Nop_a2e00  [dead]
//   [ ] 0xa2e08  KStub_Return0_a2e08  [dead]
//   [x] 0xa2e10  KStub_Return1_a2e10  (the camera context's RecursiveRegistration: returns 1, registers nothing (CRenderer::RecursiveRegistration's note))
//   [ ] 0xa2e18  KStub_Return1_a2e18  [dead]
//   [ ] 0xa2e20  KStub_Return1_a2e20  [dead]
//   [ ] 0xa2e28  WriteRasterImageToFile  [dead: no pointer to its descriptor; its only calls are from the dead 0xa3ff0 CaptureScreenshotToFile]  [platform] (the screenshot export: RwImageWrite through the registered image-file writers, a PS3 debug tool writing files; no caller but the dead CaptureScreenshotToFile)
//   [x] 0xa2fa8  CameraContext_SetClipPlanes_maybe
//   [x] 0xa30c0  ProjectWorldPointToScreen
//   [x] 0xa31e8  DrawScreenColorQuad
//   [x] 0xa39a8  CameraContext_Destructor
//   [x] 0xa3a78  DrawUIFontTextRotatedScaled_maybe  [dead: no pointer to its descriptor 0xb48dd0, no call]  (DrawUIFontTextRotatedScaled, CameraContext.h)
//   [ ] 0xa3c28  ConstructRendererCameraContext_2  [dead]
//   [ ] 0xa3ce8  CameraContext_TransformPointToView_maybe  [dead]
//   [x] 0xa3d40  CameraContext_ScreenPointToWorldRay_maybe  (CameraContext::ScreenPointToWorldRay)
//   [ ] 0xa3ff0  CaptureScreenshotToFile  [dead: no pointer to its descriptor 0xb48e08, no call]  [platform] (the screenshot capture to a file: temporary rasters, one GameLoop pass and WriteRasterImageToFile; a debug tool with no caller)
//   [x] 0xa4278  ClearRendererCamera
//   [x] 0xa4350  CameraContext_DestroyCamerasAndRasters_maybe
//   [ ] 0xa4578  CameraContext_ClearScreen_maybe  [platform]  (two cleared frames presented and a 21 ms sleep (CameraContext_Init's end, the heap's out-of-memory paths): the platform window presents its own frames, see CameraContext::Init's STUB(M2) note)
//   [x] 0xa4668  ConstructRendererCameraContext
//   [ ] 0xa4728  CameraContext_UpdateAspectFromRaster_maybe  [dead]
//   [ ] 0xa4818  CameraContext_Destructor_2  [dead]
//   [x] 0xa48e8  CameraContext_DeletingDestructor
//   [x] 0xa49e0  CameraContext_SetFieldOfView_maybe
//   [x] 0xa4be8  Camera_SetFovAndAspectFromRaster_maybe
//   [x] 0xa4d18  CameraContext_RecreateFrameBuffers_maybe
//   [x] 0xa5160  CameraContext_RefreshFrameBuffersIfResized_maybe  [dead: no pointer to its descriptor; its only call is from the dead 0x59f08 CKGraphic_RefreshFrameBuffersIfResized_maybe]  (CameraContext::RefreshFrameBuffersIfResized)
//   [~] 0xa5270  CameraContext_Init_maybe (the UI camera, rasters and aspects; the 3D cameras' setup STUB)
#include "k2000/cameras/CameraContext.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwIm2D.h"
#include "Renderware/rwcore/RwIm3D.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "crt/ppc_ops.h"
#include "crt/xtanf.h"
#include "Renderware/rwcore/RwRaster.h"
#include "Renderware/rt2d/Rt2d.h"
#include "k2000/graphical/ui/CManager2d.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/misc/CoreSingletons.h"
#include "k2000/misc/Engine.h"
#include "k2000/render/CRenderer.h"
#include "platform/gfx/device.h"

namespace {

// 0x00c5c910: DrawScreenColorQuad's five Im2D vertices; then (0x00c5c9c4..0x00c5c9d0) the UI, scene and
// main cameras and the IKCamera as Init stores them (only read by the debug tools).
RwIm2DVertex s_screenQuad[5];
RwCamera* s_uiCamera = nullptr;      // 0x00c5c9c4
RwCamera* s_sceneCamera = nullptr;   // 0x00c5c9c8
RwCamera* s_mainCamera = nullptr;    // 0x00c5c9cc
IKSerializable* s_camera = nullptr;  // 0x00c5c9d0
// 0x00c29718: the quad's triangle-strip indices, then the centred fan's.
RwImVertexIndex s_quadIndices[10] = {1, 0, 2, 3, 4, 1, 0, 3, 2, 1};

RwRGBA ColorOfWord(uint32_t word) {
    return RwRGBA{static_cast<RwUInt8>(word >> 24), static_cast<RwUInt8>(word >> 16), static_cast<RwUInt8>(word >> 8),
                  static_cast<RwUInt8>(word)};
}

}  // namespace

CameraContext* Engine_GetCameraContext() { return static_cast<CameraContext*>(g_pEngine->m_cameraContext); }

// 0x000a2dc8 CameraContext_GetViewWindow_maybe
void CameraContext_GetViewWindow(const CameraContext* context, RwV2d* viewWindow) {
    const RwCamera* camera = context->m_pMainCamera;
    viewWindow->x = camera->viewWindow.x;
    viewWindow->y = camera->viewWindow.y;
}

// 0x000a3d40 CameraContext_ScreenPointToWorldRay_maybe (P21). The frustum corners: near 0-3, far 4-7 (top right,
// top left, bottom left, bottom right); u = x / width, v = y / height (fcfid + frsp); each lerp fused (fmadds).
void CameraContext::ScreenPointToWorldRay(const float* point, float* ray) const {
    if (m_pFinalColorRaster == nullptr || m_pDepthRaster == nullptr) {
        ray[0] = 0.0f;  // 0x00c50d64 (TOC -0x6124): the null vector
        ray[1] = 0.0f;
        ray[2] = 0.0f;
        ray[3] = 0.0f;  // 0x00c50d4c (TOC -0x6120): the z axis (a static initialiser fills it)
        ray[4] = 0.0f;
        ray[5] = 1.0f;
        return;
    }
    const RwCamera* camera = m_pMainCamera;
    const RwV3d* c = camera->frustumCorners;
    const float u = point[0] / static_cast<float>(static_cast<double>(camera->frameBuffer->width));
    const float v = point[1] / static_cast<float>(static_cast<double>(camera->frameBuffer->height));
    auto lerp = [](float t, float a, float b) { return ppc::fmadds(t, b - a, a); };  // a + t (b - a)
    const float nx = lerp(v, lerp(u, c[0].x, c[1].x), lerp(u, c[3].x, c[2].x));
    const float ny = lerp(v, lerp(u, c[0].y, c[1].y), lerp(u, c[3].y, c[2].y));
    const float nz = lerp(v, lerp(u, c[0].z, c[1].z), lerp(u, c[3].z, c[2].z));
    const float fx = lerp(v, lerp(u, c[4].x, c[5].x), lerp(u, c[7].x, c[6].x));
    const float fy = lerp(v, lerp(u, c[4].y, c[5].y), lerp(u, c[7].y, c[6].y));
    const float fz = lerp(v, lerp(u, c[4].z, c[5].z), lerp(u, c[7].z, c[6].z));
    ray[0] = nx;
    ray[2] = nz;
    ray[3] = fx - nx;
    ray[5] = fz - nz;
    ray[1] = ny;
    ray[4] = fy - ny;
}

// 0x000a30c0 ProjectWorldPointToScreen
void ProjectWorldPointToScreen(const CameraContext* context, const RwV3d* point, float* screen, int32_t inPixels) {
    if (context->m_pFinalColorRaster == nullptr || context->m_pDepthRaster == nullptr) return;
    RwV3d view;
    RwV3dTransformPoints(&view, point, 1, &context->m_pMainCamera->viewMatrix);  // Mat4_TransformPoints 0x23f7e8
    float recipZ;
    if (view.z == 0.0f) {
        // BUG(original): blt after the equality test (cr7 still says "equal"): always +1e-6 (TOC -0x6158; -0x615c unused).
        view.z = 1.0e-6f + view.z;
        recipZ = 1.0f / view.z;
    } else {
        recipZ = 1.0f / view.z;
    }
    float scaleX = 1.0f;
    float scaleY = 1.0f;
    if (inPixels != 0) {
        scaleX = 0.0f;
        scaleY = 0.0f;
        const RwRaster* raster = context->m_pFinalColorRaster;
        if (raster != nullptr) {
            // lwz + fcfid: the words as unsigned 32-bit values.
            scaleY = static_cast<float>(static_cast<int64_t>(static_cast<uint32_t>(raster->height)));
            scaleX = static_cast<float>(static_cast<int64_t>(static_cast<uint32_t>(raster->width)));
        }
    }
    screen[0] = scaleX * (recipZ * view.x);
    screen[1] = scaleY * (recipZ * view.y);
}

// 0x000a4668 ConstructRendererCameraContext. The TOC constants: 4/3 (0x3faaaaab), 1.0, 0.75, 70.0.
CameraContext::CameraContext() {
    m_unk54 = 0;
    std::memset(m_mutex58, 0, sizeof(m_mutex58));  // LwMutex_Create(+0x58)
    m_unk50 = 0;
    g_pEngine->m_cameraContext = this;
    m_fPixelAspect = 0x1p+0f;
    m_pCamera = nullptr;
    m_fHeightOverWidth = 0x1.8p-1f;
    m_fFieldOfView = 70.0f;
    m_fReferenceAspect78 = 0x1.555556p+0f;
    m_pMainCamera = nullptr;
    m_pFinalColorRaster = nullptr;
    m_pDepthRaster = nullptr;
    m_unk10 = nullptr;
    m_unk14 = nullptr;
    m_unk18 = nullptr;
    m_pSceneColorRaster = nullptr;
    m_fInvHeightOverWidth = 0x1.555556p+0f;
    m_fMetricWidth = 0x1.555556p+0f;
    m_fDisplayAspect = 0x1.555556p+0f;
    m_fReferenceAspect = 0x1.555556p+0f;
    m_fPixelAspect84 = 0x1p+0f;
    // Not written by the constructor (operator new memory); cleared here.
    m_pUICamera = nullptr;
    m_pSceneCamera = nullptr;
    m_pConfig = nullptr;
    m_fFarPlane = 0.0f;
    m_unk38 = 0;
    m_unk3c = 0;
    m_fAppliedFieldOfView = 0.0f;
    m_clearColor = 0;
    m_unk4c = 0;
    m_unk94 = 0;
}

// 0x000a5270 CameraContext_Init_maybe
int32_t CameraContext::Init(AppConfig* config) {
    m_pConfig = config;
    const uint32_t clear = config->backColor & 0xffffff00u;
    if (m_clearColor != clear) m_clearColor = clear;
    // ClassRegistry_CreateObjectByKey(0x14b): the CSGMovable whose frame (+4) the main and scene cameras share
    // (also stored at 0x00c5c9d0). CKSrvCamera moves the cameras through it.
    m_pCamera = static_cast<IKSerializable*>(ClassRegistry_CreateObjectByKey(0x14b));
    s_camera = m_pCamera;
    m_unk38 = 1;
    m_unk3c = 0;
    m_fAppliedFieldOfView = 0.0f;
    m_pMainCamera = RwCameraCreate();
    s_mainCamera = m_pMainCamera;
    RwCameraSetFrame(m_pMainCamera, static_cast<CSGMovable*>(m_pCamera)->m_pRwFrame);
    // The UI camera: its own frame at (0.5, 0.5, -1) (flags 3), view window and offset from the stack pair
    // (0.5, 0.5) / (0, 0), far 1000 (TOC 0x447a0000), near 0.01 (0x3c23d70a), perspective.
    RwFrame* frame = RwFrameCreate();
    m_pUICamera = RwCameraCreate();
    s_uiCamera = m_pUICamera;
    RwCameraSetFrame(m_pUICamera, frame);
    frame->modelling.flags = 3;
    frame->modelling.pos.z = -0x1p+0f;
    frame->modelling.pos.x = 0x1p-1f;
    frame->modelling.pos.y = 0x1p-1f;
    RwV2d window = {0x1p-1f, 0x1p-1f};
    RwCameraSetViewWindow(m_pUICamera, &window);
    RwV2d offset = {0.0f, 0.0f};
    RwCameraSetViewOffset(m_pUICamera, &offset);
    RwCameraSetFarClipPlane(m_pUICamera, 1000.0f);
    RwCameraSetNearClipPlane(m_pUICamera, 0x1.47ae14p-7f);
    RwCameraSetProjection(m_pUICamera, rwPERSPECTIVE);
    // The scene camera on the main camera's frame: far 0.001 (0x3a83126f), near 1e-6 (0x358637be).
    m_pSceneCamera = RwCameraCreate();
    s_sceneCamera = m_pSceneCamera;
    RwCameraSetFrame(m_pSceneCamera, RwCameraGetFrame(m_pMainCamera));
    RwCameraSetFarClipPlane(m_pSceneCamera, 0x1.0624dep-10f);
    RwCameraSetNearClipPlane(m_pSceneCamera, 0x1.0c6f7ap-20f);
    RwCameraSetProjection(m_pSceneCamera, rwPERSPECTIVE);
    RecreateFrameBuffers();
    // The main camera: near 0.1 (0x3dcccccd), far 100 (0x42c80000), kept at +0x34.
    RwCameraSetNearClipPlane(m_pMainCamera, 0x1.99999ap-4f);
    RwCameraSetFarClipPlane(m_pMainCamera, 100.0f);
    m_fFarPlane = 100.0f;
    SetFieldOfView(m_fFieldOfView, 0, 1, 1);
    // STUB(M2): CameraContext_ClearScreen_maybe 0xa4578 (two cleared and presented frames, then a 21 ms
    // sleep).
    return 1;
}

// 0x000a39a8 CameraContext_Destructor (0x000a48e8 CameraContext_DeletingDestructor: the same, then the delete): the engine's
// camera context cleared, the mutex destroyed (a PS3 system object: nothing here), the reference-counted object +0x54
// released (the constructor's 0; nothing stores another).
CameraContext::~CameraContext() { g_pEngine->m_cameraContext = nullptr; }

// 0x000a4350 CameraContext_DestroyCamerasAndRasters_maybe (CRenderer_Shutdown_maybe): the UI camera (its own frame
// destroyed), the scene and main cameras (their frame is the IKCamera's) without rasters and frames destroyed, the six
// rasters destroyed, the IKCamera destroyed (vt+0x10, then the class manager).
void CameraContext::DestroyCamerasAndRasters() {
    if (m_pUICamera != nullptr) {
        m_pUICamera->frameBuffer = nullptr;
        m_pUICamera->zBuffer = nullptr;
        RwFrameDestroy(RwCameraGetFrame(m_pUICamera));
        RwCameraSetFrame(m_pUICamera, nullptr);  // RwObjectHasFrameSetFrame
        RwCameraDestroy(m_pUICamera);
        m_pUICamera = nullptr;
        s_uiCamera = nullptr;  // g_AuxiliaryRenderCamera
    }
    if (m_pSceneCamera != nullptr) {
        m_pSceneCamera->frameBuffer = nullptr;
        m_pSceneCamera->zBuffer = nullptr;
        RwCameraSetFrame(m_pSceneCamera, nullptr);
        RwCameraDestroy(m_pSceneCamera);
        m_pSceneCamera = nullptr;
        s_sceneCamera = nullptr;
    }
    if (m_pMainCamera != nullptr) {
        m_pMainCamera->frameBuffer = nullptr;
        m_pMainCamera->zBuffer = nullptr;
        RwCameraSetFrame(m_pMainCamera, nullptr);
        RwCameraDestroy(m_pMainCamera);
        s_mainCamera = nullptr;
        m_pMainCamera = nullptr;
    }
    if (m_unk10 != nullptr) {
        RwRasterDestroy(m_unk10);
        m_unk10 = nullptr;
    }
    if (m_unk14 != nullptr) {
        RwRasterDestroy(m_unk14);
        m_unk14 = nullptr;
    }
    if (m_unk18 != nullptr) {
        RwRasterDestroy(m_unk18);
        m_unk18 = nullptr;
    }
    if (m_pSceneColorRaster != nullptr) {
        RwRasterDestroy(m_pSceneColorRaster);
        m_pSceneColorRaster = nullptr;
    }
    if (m_pFinalColorRaster != nullptr) {
        RwRasterDestroy(m_pFinalColorRaster);
        m_pFinalColorRaster = nullptr;
    }
    if (m_pDepthRaster != nullptr) {
        RwRasterDestroy(m_pDepthRaster);
        m_pDepthRaster = nullptr;
    }
    if (m_pCamera != nullptr) {
        m_pCamera->Destroy();  // vt+0x10
        ClassRegistry_DestroyObject(m_pCamera);
        s_camera = nullptr;
        m_pCamera = nullptr;
    }
}

// 0x000a4d18 CameraContext_RecreateFrameBuffers_maybe. The raster sizes: the config's when its +0x14 byte
// is 0, else the current video mode's (RwEngineGetCurrentVideoMode, RwEngineGetVideoModeInfo: width, height,
// depth written back into the config). The device's mode is its internal target as the game knows it
// (1280x720x32 as on the PS3, or the game's size for --resolution: platform/gfx/device.h ScreenSize).
int32_t CameraContext::RecreateFrameBuffers() {
    if (m_pFinalColorRaster != nullptr) {
        RwRasterDestroy(m_pFinalColorRaster);
        m_pFinalColorRaster = nullptr;
        m_pMainCamera->frameBuffer = nullptr;
        m_pUICamera->frameBuffer = nullptr;
        m_pSceneCamera->frameBuffer = nullptr;
    }
    if (m_pDepthRaster != nullptr) {
        RwRasterDestroy(m_pDepthRaster);
        m_pDepthRaster = nullptr;
        m_pMainCamera->zBuffer = nullptr;
        m_pUICamera->zBuffer = nullptr;
        m_pSceneCamera->zBuffer = nullptr;
    }
    if (m_unk10 != nullptr) {
        RwRasterDestroy(m_unk10);
        m_unk10 = nullptr;
    }
    if (m_unk14 != nullptr) {
        RwRasterDestroy(m_unk14);
        m_unk14 = nullptr;
    }
    int32_t width, height, depth;
    if (m_pConfig->flag14 == 0) {
        width = m_pConfig->width;
        height = m_pConfig->height;
        depth = m_pConfig->bitsPerPixel;
    } else {
        RwVideoMode mode = {};
        RwEngineGetVideoModeInfo(&mode, RwEngineGetCurrentVideoMode());
        width = mode.width;
        height = mode.height;
        depth = mode.depth;
        m_pConfig->width = width;
        m_pConfig->height = height;
        m_pConfig->bitsPerPixel = depth;
    }
    if (width != 0 && height != 0) {
        m_unk14 = RwRasterCreate(width / 4, height / 4, depth, rwRASTERTYPECAMERATEXTURE);
        m_unk18 = RwRasterCreate(width, height, depth, rwRASTERTYPECAMERATEXTURE);
        m_pSceneColorRaster = RwRasterCreate(width, height, depth, rwRASTERTYPECAMERATEXTURE);
        // With the graphic caps' 0x200 the alternative scene raster (+0x10). STUB(C2.9, depth of field: no game file has a CKDOFFxData): its frame buffer's two colour
        // attachments (RwPSGL_SetColorAttachmentTexture_maybe: 0 the scene colour raster, 1 itself), which only the
        // depth of field path (CPostRenderingFx 0x400, set by the DOF node of the FX service) draws through.
        if ((g_pEngine->m_graphic->m_baHardwareCaps & 0x200) != 0) {
            m_unk10 = RwRasterCreate(width, height, depth, rwRASTERTYPECAMERATEXTURE);
        }
        m_pFinalColorRaster = RwRasterCreate(width, height, depth, rwRASTERTYPECAMERA);
        m_pDepthRaster = RwRasterCreate(width, height, 0, rwRASTERTYPEZBUFFER);
    }
    m_pMainCamera->frameBuffer = m_pFinalColorRaster;
    m_pMainCamera->zBuffer = m_pDepthRaster;
    m_pUICamera->frameBuffer = m_pFinalColorRaster;
    m_pUICamera->zBuffer = m_pDepthRaster;
    m_pSceneCamera->frameBuffer = m_pFinalColorRaster;
    m_pSceneCamera->zBuffer = m_pDepthRaster;
    // The aspects (0.0 = TOC 0x0: a raster of size 0 keeps the 4:3 defaults).
    float heightOverWidth = 0x1.8p-1f;         // 0.75
    float invHeightOverWidth = 0x1.555556p+0f; // 4/3
    const float pixelAspect = 0x1p+0f;
    const float reference = 0x1.555556p+0f;
    float displayAspect = reference;
    RwRaster* raster = m_pFinalColorRaster;
    if (raster != nullptr &&
        (static_cast<float>(static_cast<uint32_t>(raster->width)) != 0.0f ||
         static_cast<float>(static_cast<uint32_t>(raster->height)) != 0.0f)) {
        heightOverWidth = static_cast<float>(static_cast<uint32_t>(raster->height)) /
                          static_cast<float>(static_cast<uint32_t>(raster->width));
        invHeightOverWidth = pixelAspect / heightOverWidth;
        displayAspect = static_cast<float>(static_cast<uint32_t>(raster->width)) /
                        static_cast<float>(static_cast<uint32_t>(raster->height));
    }
    m_fHeightOverWidth = heightOverWidth;
    m_fInvHeightOverWidth = invHeightOverWidth;
    m_fPixelAspect = pixelAspect;
    m_fReferenceAspect = reference;
    m_fMetricWidth = displayAspect;
    m_fDisplayAspect = displayAspect;
    return 1;
}

// The aspect fields from the colour raster, as SetFieldOfView and Camera_SetFovAndAspectFromRaster inline
// them (RecreateFrameBuffers has its own copy): h/w (+0x48) and its inverse (+0x90), the pixel aspect 1.0
// (+0x7c) and the 4:3 reference (+0x80), then w/h (+0x88, +0x8c); a raster of size 0 (or none) keeps
// 0.75 and 4/3. The sizes are unsigned words converted to float (fcfid, frsp).
void CameraContext::UpdateAspectsFromRaster() {
    const float zero = 0.0f;                    // TOC 0x00c0f860
    const float one = 0x1p+0f;                  // TOC 0x00c0f85c
    const float reference = 0x1.555556p+0f;     // TOC 0x00c0f858 (4/3)
    RwRaster* raster = m_pFinalColorRaster;
    float heightOverWidth = 0x1.8p-1f;          // TOC 0x00c0f864 (0.75)
    float invHeightOverWidth = reference;
    if (raster != nullptr) {
        const float width = static_cast<float>(static_cast<uint32_t>(raster->width));
        const float height = static_cast<float>(static_cast<uint32_t>(raster->height));
        if (width != zero || height != zero) {
            heightOverWidth = height / width;              // fdivs
            invHeightOverWidth = one / heightOverWidth;    // fdivs
        }
    }
    m_fHeightOverWidth = heightOverWidth;
    m_fInvHeightOverWidth = invHeightOverWidth;
    m_fPixelAspect = one;
    m_fReferenceAspect = reference;
    float displayAspect = reference;
    if (raster != nullptr) {
        const float width = static_cast<float>(static_cast<uint32_t>(raster->width));
        const float height = static_cast<float>(static_cast<uint32_t>(raster->height));
        if (width != zero || height != zero) displayAspect = width / height;  // fdivs
    }
    m_fMetricWidth = displayAspect;
    m_fDisplayAspect = displayAspect;
}

// 0x000a49e0 CameraContext_SetFieldOfView_maybe. TOC: 0.001 (0x00c0f870), pi/180 (0x3c8efa34), 0.5,
// 0.75, 4/3. The half angle is two single multiplies (fov * pi/180, then * 0.5).
void CameraContext::SetFieldOfView(float fov, int32_t index, int32_t force, int32_t referenceWindow) {
    if (force == 0) {
        float delta = m_fAppliedFieldOfView - fov;  // fsubs, then the sign bit cleared
        if (std::fabs(delta) < 0x1.0624dep-10f) return;
    }
    if (m_pFinalColorRaster == nullptr || m_pDepthRaster == nullptr) return;
    float halfAngle = fov * 0x1.1df468p-6f;  // fmuls
    m_fAppliedFieldOfView = fov;
    (&m_fFieldOfView)[index * 4] = fov;      // +0x30 + 16 * index (the callers pass 0)
    halfAngle = halfAngle * 0x1p-1f;         // fmuls
    // tanf (0x0098e410 TocBridge_tanf -> 0x00780a90, the PS3 libm; step 5: the replays compare the view window).
    const float tangent = crt::Tanf(halfAngle);
    UpdateAspectsFromRaster();
    RwV2d window;
    if (referenceWindow != 0) {
        const float scale = m_fHeightOverWidth * 0x1.555556p+0f;  // fmuls (h/w * 4/3)
        window.y = tangent * 0x1.8p-1f;                           // fmuls (* 0.75)
        window.x = tangent / scale;                               // fdivs
    } else {
        window.y = tangent * m_fHeightOverWidth;                  // fmuls
        window.x = tangent;
    }
    RwCameraSetViewWindow(m_pMainCamera, &window);
}

// 0x000a2fa8 CameraContext_SetClipPlanes_maybe. TOC: 1.0, 0.001 (0x3a83126f) and 0.99 (0x3f7d70a4).
void CameraContext::SetClipPlanes(float farPlane, float nearPlane, int32_t autoNear, int32_t index) {
    if (!(farPlane > 1.0f)) farPlane = 1.0f;
    if (m_pMainCamera->farPlane == farPlane) return;
    RwCameraSetFarClipPlane(m_pMainCamera, farPlane);
    if (autoNear != 0) nearPlane = farPlane * 0x1.0624dep-10f;
    if (nearPlane > 0x1.fae148p-1f) nearPlane = 0x1.fae148p-1f;
    if (m_pMainCamera->nearPlane != nearPlane) RwCameraSetNearClipPlane(m_pMainCamera, nearPlane);
    (&m_fFarPlane)[index * 4] = farPlane;  // +0x34 + 16 * index
}

// 0x000a4be8 Camera_SetFovAndAspectFromRaster_maybe
void Camera_SetFovAndAspectFromRaster(float aspect, CameraContext* context) {
    context->m_fReferenceAspect78 = aspect;
    context->UpdateAspectsFromRaster();
    context->SetFieldOfView(context->m_fFieldOfView, 0, 1, 1);
    g_pEngine->m_manager2d->m_bUpdateScreen = 1;
}

// 0x000a4278 ClearRendererCamera
void ClearRendererCamera(CameraContext* context, int32_t depthOnly) {
    if (context->m_pFinalColorRaster == nullptr || context->m_pDepthRaster == nullptr) return;
    if (depthOnly == 0) {
        const RwRGBA color = ColorOfWord(context->m_clearColor);
        RwCameraClear(context->m_pMainCamera, &color, rwCAMERACLEARIMAGE | rwCAMERACLEARZ);
    } else {
        RwCameraClear(context->m_pMainCamera, nullptr, rwCAMERACLEARZ);
    }
    // STUB(M2): in video mode 2 (engine graphics +4 -> +0x30 == 2) the clear colour follows the config's
    // colour with the alpha cleared. The front end runs in mode 0.
}

// 0x000a31e8 DrawScreenColorQuad (CColorizedScreenFx_Render; its other callers are the in-game fades).
// The vertices are written into the static quad (0x00c5c910), then drawn as an Im2D strip (or a fan
// around the centre) under pushed render states: no Z, no culling, no fog, clamp, alpha test always,
// linear filtering, the raster, vertex alpha unless the blend is ONE/ZERO, the blend, flat shading.
void DrawScreenColorQuad(float centerX, float centerY, int32_t centered, int32_t srcBlend, int32_t destBlend,
                         const uint8_t* color, const uint8_t* centerColor, RwRaster* raster) {
    CameraContext* context = Engine_GetCameraContext();
    uint32_t vertexAlpha = 1;
    if (srcBlend == 2) vertexAlpha = destBlend != 1 ? 1u : 0u;
    RwCamera* current = context->m_pUICamera;  // RWEngine's current camera (the 2D group's)
    const RwRaster* target = current != nullptr ? current->frameBuffer : nullptr;
    const float targetW = target != nullptr ? static_cast<float>(target->width) : 1280.0f;
    const float targetH = target != nullptr ? static_cast<float>(target->height) : 720.0f;
    // Texture extents: without a raster the target's, with no offset.
    float u0 = 0.0f, v0 = 0.0f, uExtent = 0.0f, vExtent = 0.0f;
    float texW = targetW, texH = targetH;
    if (raster != nullptr) {
        // STUB: textured quads (sub-rasters and RwRasterGetOffset) are not used by the front end.
        texW = static_cast<float>(raster->width);
        texH = static_cast<float>(raster->height);
    }
    RwIm2DVertex* v = s_screenQuad;
    const float nearZ = RwIm2DGetNearScreenZ();
    if (v[0].z != nearZ) {
        const float recipZ = 0x1p+0f / context->m_pMainCamera->nearPlane;
        v[4].z = nearZ;
        v[0].z = nearZ;
        v[1].z = nearZ;
        v[2].z = nearZ;
        v[3].z = nearZ;
        v[4].recipZ = recipZ;
    }
    const float one = 0x1p+0f;
    v[0].recipZ = one;
    v[0].x = 0.0f;
    v[0].y = 0.0f;
    v[1].x = targetW;
    v[1].y = 0.0f;
    v[1].recipZ = one;
    v[2].x = targetW;
    v[2].y = targetH;
    v[2].recipZ = one;
    v[3].x = 0.0f;
    v[3].y = targetH;
    v[3].recipZ = one;
    v[4].x = centerX;
    v[4].y = centerY;
    for (int i = 0; i < 4; ++i) std::memcpy(&v[i].emissiveColor, color, 4);
    std::memcpy(&v[4].emissiveColor, centerColor, 4);
    // Half-texel offsets: u0/v0 + 0.5 / size (the target is never wider than itself: the first branch).
    float qU, qV, uStart, vStart;
    if (texW <= targetW) {
        uStart = u0 + 0x1p-1f / texW;
        vStart = v0 + 0x1p-1f / texH;
        qU = one / uStart;
        qV = one / vStart;
    } else {
        vStart = v0;
        uStart = u0;
        qU = qV = 1.0f;  // STUB: the PS3 reads a constant at 0x00c4acb8 +0x28 here (never reached)
    }
    const float vEnd = vExtent + vStart;
    const float uEnd = uExtent + uStart;
    const float qEnd = one / uEnd;
    const float tEnd = vEnd * (one / vEnd);
    v[2].q = qEnd;
    v[3].q = qU;
    v[0].q = qU;
    v[1].q = qEnd;
    v[3].t = tEnd;
    v[1].t = vStart * qV;
    v[3].s = uStart * qU;
    v[2].s = uEnd * qEnd;
    v[0].s = uStart * qU;
    v[0].t = vStart * qV;
    v[1].s = uEnd * qEnd;
    v[2].t = tEnd;
    v[0].r = 0.0f;
    v[1].r = 0.0f;
    v[2].r = 0.0f;
    v[3].r = 0.0f;
    CRenderer* renderer = g_pRenderStateRenderer;
    PushRenderStates(renderer);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, reinterpret_cast<void*>(0));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, reinterpret_cast<void*>(0));
    RwRenderStateSet(rwRENDERSTATECULLMODE, reinterpret_cast<void*>(1));
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, reinterpret_cast<void*>(0));
    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS, reinterpret_cast<void*>(3));
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION, reinterpret_cast<void*>(8));
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, reinterpret_cast<void*>(2));
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, raster);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void*>(static_cast<uintptr_t>(vertexAlpha)));
    RwRenderStateSet(rwRENDERSTATESRCBLEND, reinterpret_cast<void*>(static_cast<intptr_t>(srcBlend)));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, reinterpret_cast<void*>(static_cast<intptr_t>(destBlend)));
    if (centered == 0) {
        RwRenderStateSet(rwRENDERSTATESHADEMODE, reinterpret_cast<void*>(1));
        RwIm2DRenderIndexedPrimitive(rwPRIMTYPETRISTRIP, v, 4, s_quadIndices, 4);
    } else {
        // The centre vertex's texture coordinates from its position.
        v[4].r = 0.0f;
        const float su = (centerX / targetW) * (uEnd - uStart);
        const float tv = (centerY / targetH) * (vEnd - vStart);
        const float q = one / su;
        v[4].q = q;
        v[4].s = su * q;
        v[4].t = tv * (one / tv);
        RwRenderStateSet(rwRENDERSTATESHADEMODE, reinterpret_cast<void*>(2));
        RwIm2DRenderIndexedPrimitive(rwPRIMTYPETRIFAN, v, 5, s_quadIndices + 4, 6);
    }
    PopRenderStates(renderer);
}

// 0x000a3a78 DrawUIFontTextRotatedScaled_maybe: `text` in the UI manager's font `fontId` (nothing without the font)
// at `position` (x times the manager's aspect +0x18), the matrix scaled by `scale`, the brush coloured `color` (all four
// corners), turned `angleDeg` and squeezed by aspect * 0.75 in x; the character height the font's height / 512 (TOC
// -0x6130 0x3b000000), the anchor the zero vector 0x00c50dc4. Dead in the original (no pointer to its descriptor
// 0xb48dd0, no call).
void DrawUIFontTextRotatedScaled(float angleDeg, const char* text, uint32_t fontId, RwRGBA* color, const float* position,
                                 const float* scale) {
    CManager2d* manager = g_pEngine->m_manager2d;
    Rt2dFont* font = manager->GetFont(fontId);                       // 0x00061bf8
    Rt2dBrush* brush = g_pEngine->m_manager2d->GetOrCreateBrush();   // 0x00062008
    if (font == nullptr) return;
    const float height = font->height * 0.001953125f;
    const float squeeze = manager->m_fAspect * 0.75f;  // TOC -0x6174
    RwV2d anchor = {0.0f, 0.0f};                       // 0x00c50dc4
    const float x = position[0] * manager->m_fAspect;
    const float y = position[1];
    Rt2dCTMPush();
    Rt2dCTMScale(scale[0], scale[1]);
    Rt2dCTMTranslate(x, y);
    Rt2dBrushSetRGBA(brush, color, color, color, color);
    Rt2dCTMPush();
    Rt2dCTMRotate(angleDeg);
    Rt2dCTMScale(squeeze, 1.0f);
    Rt2dFontShow(font, text, height, &anchor, brush);  // 0x00a3ce28 BridgeDispatchUIFontRenderCallback
    Rt2dCTMPop();
    Rt2dCTMPop();
}

// 0x000a5160 CameraContext_RefreshFrameBuffersIfResized_maybe: 1 when both rasters exist at the config's width, height
// and depth; else the buffers made again (RecreateFrameBuffers) and, when that gives 1, the field of view applied again
// (forced, reference window) and the UI manager moved to the main camera (ChangeCam); RecreateFrameBuffers' result. Dead
// in the original (its only call is from the dead 0x59f08 CKGraphic_RefreshFrameBuffersIfResized_maybe).
int32_t CameraContext::RefreshFrameBuffersIfResized() {
    RwRaster* color = m_pFinalColorRaster;
    if (color != nullptr && m_pDepthRaster != nullptr && color->width == m_pConfig->width &&
        color->height == m_pConfig->height && color->depth == m_pConfig->bitsPerPixel) {
        return 1;
    }
    const int32_t result = RecreateFrameBuffers();  // 0x000a4d18
    if (result != 1) return result;
    SetFieldOfView(m_fFieldOfView, 0, 1, 1);  // 0x000a49e0
    CManager2d* manager = g_pEngine->m_manager2d;
    if (manager == nullptr) return result;
    manager->ChangeCam(m_pMainCamera);  // 0x00062b98
    return result;
}
