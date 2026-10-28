// CameraContextUi.h - the renderer camera context fields the 2D/Flash code reads (CameraContext: renderer
// +0x28, the same object as engine +0x08; ConstructRendererCameraContext 0xa4668, k2000/cameras/
// CameraContext.h). Every caller names the field it reads.
#pragma once
#include <cstdint>

#include "Renderware/rwcore/RwCamera.h"
#include "k2000/cameras/CameraContext.h"

// +0x04 / +0x08: the camera rasters; the 2D pre-render pass runs only when both exist.
inline bool CameraContext_HasRasters() {
    const CameraContext* context = Engine_GetCameraContext();
    return context != nullptr && context->m_pFinalColorRaster != nullptr && context->m_pDepthRaster != nullptr;
}
// +0x04 -> raster +0x0c / +0x10: the frame buffer size in pixels.
inline uint32_t CameraContext_GetRasterWidth() {
    return static_cast<uint32_t>(Engine_GetCameraContext()->m_pFinalColorRaster->width);
}
inline uint32_t CameraContext_GetRasterHeight() {
    return static_cast<uint32_t>(Engine_GetCameraContext()->m_pFinalColorRaster->height);
}
// +0x20: the UI (2D) camera given to Rt2dOpen / Rt2dDeviceSetCamera.
inline RwCamera* CameraContext_GetUICamera() { return Engine_GetCameraContext()->m_pUICamera; }
// +0x48: screen height / width (0x3f100000 at 1280x720).
inline float CameraContext_GetHeightOverWidth() { return Engine_GetCameraContext()->m_fHeightOverWidth; }
// +0x7c: the pixel aspect (1.0).
inline float CameraContext_GetPixelAspect() { return Engine_GetCameraContext()->m_fPixelAspect; }
// +0x80: the reference aspect, 4:3 (0x3faaaaab). Read through 0x6e500 CameraContext_GetReferenceAspect_maybe.
inline float CameraContext_GetReferenceAspectValue() { return Engine_GetCameraContext()->m_fReferenceAspect; }
// +0x84: the 2D widgets' height scale (1.0).
inline float CameraContext_GetPixelAspect84() { return Engine_GetCameraContext()->m_fPixelAspect84; }
// +0x88: the display aspect, 16:9 (0x3fe38e39).
inline float CameraContext_GetDisplayAspect() { return Engine_GetCameraContext()->m_fDisplayAspect; }
// +0x8c: the Rt2d metric width (16:9, 0x3fe38e39).
inline float CameraContext_GetMetricWidth() { return Engine_GetCameraContext()->m_fMetricWidth; }
