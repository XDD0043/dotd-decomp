// CameraContext.h - the renderer's camera context (not a registered class, size 0x98, vtable 0xb17188):
// the final colour and depth rasters, the main/UI/scene cameras, the clear colour and the screen aspects.
// Created by InitializeRendererStages (renderer +0x28; the constructor also stores it at engine +0x08).
// Original unit: CameraContext.cpp (0xa2cc0-0xa54c0). Names are ours (no XXL2 counterpart found).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"

struct RwCamera;
struct RwRaster;
struct AppConfig;
class IKSerializable;

class CameraContext {
public:
    // 0x000a4668 ConstructRendererCameraContext
    CameraContext();
    virtual ~CameraContext() {}  // STUB: 0xa39a8 CameraContext_Destructor (cameras and rasters)

    // 0x000a5270 CameraContext_Init_maybe: the clear colour from the start-up config, the main camera on
    // the IKCamera's frame, the UI camera (+0x20) and the scene camera (+0x24), the frame buffers, the
    // clip planes and the field of view, then a cleared screen. 1 when done.
    int32_t Init(AppConfig* config);
    // 0x000a4d18 CameraContext_RecreateFrameBuffers_maybe: the rasters at the video mode's size (the
    // config's when its +0x14 byte is 0), handed to the three cameras, then the aspect fields.
    int32_t RecreateFrameBuffers();
    // 0x000a49e0 CameraContext_SetFieldOfView_maybe: unless `force`, nothing when |fov - +0x40| < 0.001;
    // with both rasters, fov kept (+0x40 and the slot +0x30 + 16 * index), the aspect fields from the colour
    // raster, then the main camera's view window from tan(fov / 2): (t / (h/w * 4/3), t * 0.75) with
    // `referenceWindow`, else (t, t * h/w).
    void SetFieldOfView(float fov, int32_t index, int32_t force, int32_t referenceWindow);
    // The aspect fields from the colour raster (inlined in 0xa49e0 and 0xa4be8).
    void UpdateAspectsFromRaster();
    // 0x000a2fa8 CameraContext_SetClipPlanes_maybe: the main camera's far plane (at least 1; nothing more when
    // it already is `farPlane`), its near plane (`nearPlane`, or 0.001 of the far plane when `autoNear`, at most
    // 0.99) and the far plane kept at +0x34 + 16 * index.
    void SetClipPlanes(float farPlane, float nearPlane, int32_t autoNear, int32_t index);

    // void* m_vtable;              // +0x00 0xb17188
    RwRaster* m_pFinalColorRaster;  // +0x04 (rwRASTERTYPECAMERA)
    RwRaster* m_pDepthRaster;       // +0x08 (rwRASTERTYPEZBUFFER)
    RwCamera* m_pMainCamera;        // +0x0c on the IKCamera's frame; presents the frame
    RwRaster* m_unk10;              // +0x10 the alternative scene colour raster (engine graphics flag 0x200)
    RwRaster* m_unk14;              // +0x14 a quarter-size raster
    RwRaster* m_unk18;              // +0x18
    RwRaster* m_pSceneColorRaster;  // +0x1c
    RwCamera* m_pUICamera;          // +0x20 the 2D camera (Rt2d, the render-stage group 17-22)
    RwCamera* m_pSceneCamera;       // +0x24 on the main camera's frame (the far group)
    AppConfig* m_pConfig;           // +0x28 the start-up config (size, depth, clear colour)
    IKSerializable* m_pCamera;      // +0x2c the IKCamera (key 0x14b) whose frame the main camera uses
    float m_fFieldOfView;           // +0x30 70.0 (degrees)
    float m_fFarPlane;              // +0x34 the main camera's far plane
    uint8_t m_unk38;                // +0x38 Init sets 1
    uint32_t m_unk3c;               // +0x3c
    // +0x40 the field of view last applied (SetFieldOfView; it skips a change below 0.001 unless forced).
    float m_fAppliedFieldOfView;
    uint32_t m_clearColor;          // +0x44 RwRGBA as the PS3 word (R << 24 | G << 16 | B << 8 | A)
    float m_fHeightOverWidth;       // +0x48 0.75, then raster height / width
    uint32_t m_unk4c;               // +0x4c
    uint8_t m_unk50;                // +0x50 the constructor clears it
    uint32_t m_unk54;               // +0x54
    uint8_t m_mutex58[0x20];        // +0x58 a sys_lwmutex (LwMutex_Create)
    float m_fReferenceAspect78;     // +0x78 4:3
    float m_fPixelAspect;           // +0x7c 1.0
    float m_fReferenceAspect;       // +0x80 4:3 (CameraContext_GetReferenceAspect_maybe)
    float m_fPixelAspect84;         // +0x84 1.0 (the 2D widgets' ScaleMatrix(+0x84, 1))
    float m_fDisplayAspect;         // +0x88 raster width / height
    float m_fMetricWidth;           // +0x8c raster width / height (Rt2d's metric width)
    float m_fInvHeightOverWidth;    // +0x90 1 / +0x48
    uint32_t m_unk94;               // +0x94
};

// The rasters' clear (0x000a4278 ClearRendererCamera): with both rasters, the main camera cleared
// (colour + z with the clear colour, or z only when depthOnly); then, in video mode 2 (engine graphics
// +4 -> +0x30), the clear colour follows the config's colour (alpha cleared).
void ClearRendererCamera(CameraContext* context, int32_t depthOnly);

// 0x000a31e8 DrawScreenColorQuad: a full-screen RwIm2D quad (4 vertices, triangle strip) in `color`
// with the blend (src, dest), optionally textured by `raster` (null here); with `centered` a 5-vertex
// fan around (centerX, centerY) in `centerColor` (unused by the front end). The render states are pushed
// and popped around it.
void DrawScreenColorQuad(float centerX, float centerY, int32_t centered, int32_t srcBlend, int32_t destBlend,
                         const uint8_t* color, const uint8_t* centerColor, RwRaster* raster);

// The engine's camera context (engine +0x08), or null before the renderer exists.
CameraContext* Engine_GetCameraContext();

// 0x000a4be8 Camera_SetFovAndAspectFromRaster_maybe (the options' aspect ratio): the reference aspect into
// +0x78, the aspect fields from the colour raster, the field of view reapplied (index 0, forced, reference
// window), the 2D screen marked changed (CManager2d +0xa7c).
void Camera_SetFovAndAspectFromRaster(float aspect, CameraContext* context);
