// RwCamera.cpp - the root-frame calls and the UI camera stand-in. See RwCamera.h.
#include "Renderware/rwcore/RwCamera.h"

#include <cmath>
#include <cstring>
#include <new>

#include "Renderware/rwcore/RwDevice.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "Renderware/rwcore/RwSList.h"
#include "platform/gfx/device.h"

// 0x0074b470 RwFrameCreate. STUB(C1.4): RW's frame free list and plugin data; the frame is a root.
RwFrame* RwFrameCreate() {
    void* memory = RwMalloc(sizeof(RwFrame), 0x30000);
    std::memset(memory, 0, sizeof(RwFrame));
    RwFrame* frame = new (memory) RwFrame();
    frame->object.type = 0;  // rwFRAME
    RwMatrixSetIdentity(&frame->modelling);
    RwMatrixSetIdentity(&frame->ltm);
    frame->root = frame;
    frame->hanimID = -1;  // 0x006e6190 HAnimFrameConstructor_maybe (the plugin constructor)
    frame->hanimHierarchy = nullptr;
    return frame;
}

// 0x0074c958 RwFrameDestroy. STUB(C1.4): children and attached objects (none here).
RwBool RwFrameDestroy(RwFrame* frame) {
    RwFree(frame);
    return 1;
}

// 0x0074ac40 RwFrameTransform. STUB(C1.4): RwFrameUpdateObjects (the dirty list); the LTM follows at
// RwFrameGetLTM.
RwFrame* RwFrameTransform(RwFrame* frame, const RwMatrix* matrix, RwOpCombineType combine) {
    RwMatrix result;
    switch (combine) {
        case rwCOMBINEREPLACE: result = *matrix; break;
        case rwCOMBINEPRECONCAT: RwMatrixMultiply(&result, matrix, &frame->modelling); break;
        case rwCOMBINEPOSTCONCAT: RwMatrixMultiply(&result, &frame->modelling, matrix); break;
        default: return nullptr;
    }
    frame->modelling = result;
    return frame;
}

// 0x0074a6f0 RwFrameGetLTM (RW 3.7 core/src/baframe.c + basync.c _rwFrameSyncHierarchyLTM): the LTM of a
// root is its modelling matrix (RwMatrixCopy), a child's its modelling matrix times its parent's LTM
// (RwMatrixMultiply(&ltm, &modelling, &parent->ltm)). STUB: RW syncs the whole hierarchy only when the root
// is marked dirty (rwFRAMEPRIVATEHIERARCHYSYNCLTM, set by RwFrameUpdateObjects); here the chain from the
// root is recomputed on every call, which gives the same matrices.
RwMatrix* RwFrameGetLTM(RwFrame* frame) {
    RwFrame* parent = static_cast<RwFrame*>(frame->object.parent);
    if (parent == nullptr) {
        // A root whose owner wrote its LTM (bone attachments) and that was not marked changed since (bit 4 clear).
        if (frame->dotdLtmOwned != 0 && (frame->object.privateFlags & 4) == 0) return &frame->ltm;
        frame->ltm = frame->modelling;
    } else {
        RwMatrixMultiply(&frame->ltm, &frame->modelling, RwFrameGetLTM(parent));
    }
    return &frame->ltm;
}

RwCamera* RwShim_CreateUICamera() {
    void* memory = RwMalloc(sizeof(RwCamera), 0x30000);
    std::memset(memory, 0, sizeof(RwCamera));
    RwCamera* camera = new (memory) RwCamera();
    RwFrame* frame = RwFrameCreate();
    frame->modelling.pos.x = 0.5f;
    frame->modelling.pos.y = 0.5f;
    frame->modelling.pos.z = -1.0f;
    frame->modelling.flags = rwMATRIXTYPEORTHONORMAL;  // the live value (identity flag cleared)
    frame->ltm = frame->modelling;
    camera->object.type = 4;  // rwCAMERA
    camera->object.parent = frame;
    camera->projectionType = rwPERSPECTIVE;
    RwRaster* raster = static_cast<RwRaster*>(RwMalloc(sizeof(RwRaster), 0x30000));
    std::memset(raster, 0, sizeof(RwRaster));
    raster->parent = raster;
    raster->width = 1280;
    raster->height = 720;
    raster->depth = 32;
    raster->stride = 0x1400;
    raster->cType = 2;  // rwRASTERTYPECAMERA (the live word +0x20 is 0x02000005)
    camera->frameBuffer = raster;
    camera->viewWindow = RwV2d{0.5f, 0.5f};
    camera->recipViewWindow = RwV2d{2.0f, 2.0f};
    camera->nearPlane = 1.0e-2f;  // 0x3c23d70a
    camera->farPlane = 1000.0f;
    camera->fogPlane = 5.0f;
    return camera;
}

void RwShim_DestroyUICamera(RwCamera* camera) {
    if (camera == nullptr) return;
    RwFree(camera->frameBuffer);
    RwFrameDestroy(RwCameraGetFrame(camera));
    RwFree(camera);
}

// ---- C1.4: the camera and raster calls of the camera context ----------------------------------------
// RW 3.7's camera module (rwcore camera.c) as far as the front end needs it; the PSGL driver's begin/end,
// clear and show are the device's (rwcore/RwDevice.h, platform/gfx).

RwCamera* RwCameraCreate() {
    void* memory = RwMalloc(sizeof(RwCamera), 0x30000);
    std::memset(memory, 0, sizeof(RwCamera));
    RwCamera* camera = new (memory) RwCamera();
    camera->object.type = 4;  // rwCAMERA
    camera->projectionType = rwPERSPECTIVE;
    camera->viewWindow = RwV2d{1.0f, 1.0f};
    camera->recipViewWindow = RwV2d{1.0f, 1.0f};
    camera->nearPlane = 0.05f;
    camera->farPlane = 10.0f;
    camera->fogPlane = 5.0f;
    return camera;
}

RwCamera* RwCameraSetViewWindow(RwCamera* camera, const RwV2d* viewWindow) {
    camera->viewWindow = *viewWindow;
    camera->recipViewWindow.x = 1.0f / viewWindow->x;
    camera->recipViewWindow.y = 1.0f / viewWindow->y;
    return camera;
}

RwCamera* RwCameraSetViewOffset(RwCamera* camera, const RwV2d* offset) {
    camera->viewOffset = *offset;
    return camera;
}

RwCamera* RwCameraSetNearClipPlane(RwCamera* camera, RwReal nearPlane) {
    camera->nearPlane = nearPlane;
    return camera;
}

RwCamera* RwCameraSetFarClipPlane(RwCamera* camera, RwReal farPlane) {
    camera->farPlane = farPlane;
    return camera;
}

RwCamera* RwCameraSetProjection(RwCamera* camera, RwCameraProjection projection) {
    camera->projectionType = projection;
    return camera;
}

void RwCameraSetFrame(RwCamera* camera, RwFrame* frame) { camera->object.parent = frame; }

namespace {
RwUInt16 g_renderFrame = 1;  // RWSRCGLOBAL(renderFrame), 1 after the world plugin's open
}  // namespace

RwUInt16 RwEngineRenderFrame() { return g_renderFrame; }

RwCamera* RwCameraBeginUpdate(RwCamera* camera) {
    ++g_renderFrame;  // WorldCameraBeginUpdate, before the chained begin update
    if (camera == nullptr || camera->frameBuffer == nullptr) return nullptr;
    RwDevice_BeginCameraUpdate(camera);  // 0x00738a68 BeginPSGLCameraUpdate (frame buffer, view, projection)
    return camera;
}

RwCamera* RwCameraEndUpdate(RwCamera* camera) {
    if (camera != nullptr) RwDevice_EndCameraUpdate(camera);  // 0x00738988 EndPSGLCameraUpdate
    return camera;
}

// RwCameraFrustumTestSphere: the sphere centre into camera space (the camera frame's LTM inverted, rows right / up /
// at; RW's camera x points to the left of the screen, the frustum is symmetric about it) and its signed distance to the
// six planes: the view window's half extents at z = 1 (perspective) or its constant half size (parallel), the near and
// the far plane. The view offset shifts the window.
RwInt32 RwCameraFrustumTestSphere(const RwCamera* camera, const RwReal* sphere) {
    const RwMatrix pose = RwDevice_CameraPose(camera);
    const RwMatrix* m = &pose;
    double px = sphere[0], py = sphere[1], pz = sphere[2];
    if (m != nullptr) {
        // c = (p - pos) . M^-1; for the rows of an orthonormal M the inverse is its transpose (the common case: a camera
        // has no scale), so the camera coordinates are the dot products with right, up and at.
        const double dx = px - m->pos.x, dy = py - m->pos.y, dz = pz - m->pos.z;
        px = dx * m->right.x + dy * m->right.y + dz * m->right.z;
        py = dx * m->up.x + dy * m->up.y + dz * m->up.z;
        pz = dx * m->at.x + dy * m->at.y + dz * m->at.z;
    }
    const double radius = sphere[3];
    double distance[6];
    int count = 0;
    distance[count++] = pz - camera->nearPlane;
    distance[count++] = camera->farPlane - pz;
    if (camera->projectionType == rwPARALLEL) {
        distance[count++] = camera->viewWindow.x - camera->viewOffset.x - px;
        distance[count++] = camera->viewWindow.x + camera->viewOffset.x + px;
        distance[count++] = camera->viewWindow.y - camera->viewOffset.y - py;
        distance[count++] = camera->viewWindow.y + camera->viewOffset.y + py;
    } else {
        const double wx = camera->viewWindow.x, wy = camera->viewWindow.y;
        const double nx = 1.0 / std::sqrt(1.0 + wx * wx), ny = 1.0 / std::sqrt(1.0 + wy * wy);
        distance[count++] = ((wx - camera->viewOffset.x) * pz - px) * nx;
        distance[count++] = ((wx + camera->viewOffset.x) * pz + px) * nx;
        distance[count++] = ((wy - camera->viewOffset.y) * pz - py) * ny;
        distance[count++] = ((wy + camera->viewOffset.y) * pz + py) * ny;
    }
    bool inside = true;
    for (int i = 0; i < count; ++i) {
        if (distance[i] < -radius) return rwSPHEREOUTSIDE;
        if (distance[i] < radius) inside = false;
    }
    return inside ? rwSPHEREINSIDE : rwSPHEREBOUNDARY;
}

RwCamera* RwCameraClear(RwCamera* camera, const RwRGBA* color, RwInt32 clearMode) {
    if (camera == nullptr) return nullptr;
    const bool image = (clearMode & rwCAMERACLEARIMAGE) != 0;
    const bool depth = (clearMode & (rwCAMERACLEARZ | rwCAMERACLEARSTENCIL)) != 0;
    float rgba[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    if (image && color != nullptr) {
        rgba[0] = color->red / 255.0f;
        rgba[1] = color->green / 255.0f;
        rgba[2] = color->blue / 255.0f;
        rgba[3] = color->alpha / 255.0f;
    }
    dotd::gfx::ClearTarget(image, depth, rgba[0], rgba[1], rgba[2], rgba[3]);
    return camera;
}

RwCamera* RwCameraShowRaster(RwCamera* camera, void* /*device*/, RwUInt32 /*flags*/) {
    dotd::gfx::EndFrame();
    return camera;
}

RwRaster* RwRasterCreate(RwInt32 width, RwInt32 height, RwInt32 depth, RwInt32 flags) {
    RwRaster* raster = static_cast<RwRaster*>(RwMalloc(sizeof(RwRaster), 0x30000));
    std::memset(raster, 0, sizeof(RwRaster));
    raster->parent = raster;
    raster->width = width;
    raster->height = height;
    raster->depth = depth != 0 ? depth : 32;
    raster->stride = raster->width * (raster->depth / 8);
    raster->cType = static_cast<RwUInt8>(flags & 7);
    raster->cFlags = static_cast<RwUInt8>(flags & 0xf8);
    return raster;
}

RwBool RwRasterDestroy(RwRaster* raster) {
    RwDevice_ReleaseRaster(raster);  // a camera texture's frame buffer object
    RwFree(raster);
    return 1;
}
