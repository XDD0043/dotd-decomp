// RwCamera.h - the RenderWare 3.7 camera, raster and frame fields the 2D toolkit reads (Rt2dOpen,
// Rt2dDeviceSetCamera, the composite CTM) and the frame calls the Rt2d shapes make, in the PS3 layout.
//
// Only what Rt2d touches is modelled: the camera's projection type, frame buffer raster, view window and
// planes, the raster's size, and a root frame's modelling/LTM matrices. The frame hierarchy (parents,
// children, the dirty list and RwFrameUpdateObjects) is not ported: every frame here is a root, so its
// LTM is its modelling matrix. STUB(C1.4): the camera's own update (view matrix, frustum) and the
// rasters' pixels.
//
// The UI camera of the front end (render context +0x20, read live in RPCS3 at the main menu): projection
// type 1 (rwPERSPECTIVE), view window (0.5, 0.5), near 0.01, far 1000, a 1280x720 frame buffer, and a
// frame whose LTM is right (1,0,0), up (0,1,0), at (0,0,1), pos (0.5, 0.5, -1) with flags 3.
#pragma once
#include "Renderware/rwcore/RwTypes.h"

// RwObject (8 bytes on the PS3).
struct RwObject {
    RwUInt8 type;          // +0x00
    RwUInt8 subType;       // +0x01
    RwUInt8 flags;         // +0x02
    RwUInt8 privateFlags;  // +0x03
    void* parent;          // +0x04 (a camera's or atomic's RwFrame)
};
DOTD_ASSERT_SIZE(RwObject, 0x8);

struct RwLLLink {
    RwLLLink* next;
    RwLLLink* prev;
};
DOTD_ASSERT_SIZE(RwLLLink, 0x8);

// RwRaster (PS3 0x34).
struct RwRaster {
    RwRaster* parent;          // +0x00
    RwUInt8* cpPixels;         // +0x04
    RwUInt8* palette;          // +0x08
    RwInt32 width;             // +0x0c
    RwInt32 height;            // +0x10
    RwInt32 depth;             // +0x14
    RwInt32 stride;            // +0x18
    RwInt16 nOffsetX;          // +0x1c
    RwInt16 nOffsetY;          // +0x1e
    RwUInt8 cType;             // +0x20
    RwUInt8 cFlags;            // +0x21
    RwUInt8 privateFlags;      // +0x22
    RwUInt8 cFormat;           // +0x23
    RwUInt8* originalPixels;   // +0x24
    RwInt32 originalWidth;     // +0x28
    RwInt32 originalHeight;    // +0x2c
    RwInt32 originalStride;    // +0x30
};
DOTD_ASSERT_SIZE(RwRaster, 0x34);
DOTD_ASSERT_OFFSET(RwRaster, width, 0xc);
DOTD_ASSERT_OFFSET(RwRaster, height, 0x10);

// RwFrame (PS3 0xb0, the matrices 16-byte aligned). Root frames only (see above).
struct alignas(16) RwFrame {
    RwObject object;            // +0x00
    RwLLLink inDirtyListLink;   // +0x08
    RwMatrix modelling;         // +0x10
    RwMatrix ltm;               // +0x50
    RwLLLink objectList;        // +0x90
    RwFrame* child;             // +0x98
    RwFrame* next;              // +0x9c
    RwFrame* root;              // +0xa0
    // The RpHAnim frame plugin (PS3: frame + [0xcf9e00], registered by RpHAnimPluginAttach_maybe;
    // HAnimFrameConstructor_maybe 0x6e6190 sets -1 / null). Renderware/rphanim/RpHAnim.h.
    RwInt32 hanimID;
    struct RpHAnimHierarchy* hanimHierarchy;
    // DOTD (not in the original): the LTM was written by its owner (a child frame hanging under a bone of an animated
    // node: UpdateAnimatedNodePoseAndCull 0xcabc8, CAnimatedNode_UpdateChildWorldMatrix_maybe 0xc9b88), which also
    // clears the frame's own sync bit 4. RW's sync then leaves such a root's LTM alone; RwFrameGetLTM below, which
    // recomputes instead of syncing, keeps it while bit 4 stays clear.
    RwUInt8 dotdLtmOwned;
};
DOTD_ASSERT_OFFSET(RwFrame, modelling, 0x10);
DOTD_ASSERT_OFFSET(RwFrame, ltm, 0x50);
DOTD_ASSERT_OFFSET(RwFrame, root, 0xa0);

enum RwCameraProjection : RwInt32 {
    rwNACAMERAPROJECTION = 0,
    rwPERSPECTIVE = 1,
    rwPARALLEL = 2,
};

// RwCamera as far as Rt2d reads it (RW 3.7 order; PS3 offsets).
struct alignas(16) RwCamera {
    RwObject object;                  // +0x00 (object.parent: the camera's RwFrame)
    RwLLLink lFrame;                  // +0x08
    void* syncCallBack;               // +0x10
    RwInt32 projectionType;           // +0x14 RwCameraProjection
    void* beginUpdate;                // +0x18
    void* endUpdate;                  // +0x1c
    RwMatrix viewMatrix;              // +0x20
    RwRaster* frameBuffer;            // +0x60
    RwRaster* zBuffer;                // +0x64
    RwV2d viewWindow;                 // +0x68
    RwV2d recipViewWindow;            // +0x70
    RwV2d viewOffset;                 // +0x78
    RwReal nearPlane;                 // +0x80
    RwReal farPlane;                  // +0x84
    RwReal fogPlane;                  // +0x88
    RwReal zScale;                    // +0x8c
    RwReal zShift;                    // +0x90
};
DOTD_ASSERT_OFFSET(RwCamera, projectionType, 0x14);
DOTD_ASSERT_OFFSET(RwCamera, frameBuffer, 0x60);
DOTD_ASSERT_OFFSET(RwCamera, viewWindow, 0x68);
DOTD_ASSERT_OFFSET(RwCamera, nearPlane, 0x80);
DOTD_ASSERT_OFFSET(RwCamera, farPlane, 0x84);

// The camera's frame (RwCameraGetFrame: object.parent).
inline RwFrame* RwCameraGetFrame(RwCamera* camera) { return static_cast<RwFrame*>(camera->object.parent); }

// 0x0074b470 RwFrameCreate: identity modelling and LTM.
RwFrame* RwFrameCreate();
// 0x0074c958 RwFrameDestroy
RwBool RwFrameDestroy(RwFrame* frame);
// 0x0074ac40 RwFrameTransform: combines matrix into the modelling matrix (replace / pre / post).
RwFrame* RwFrameTransform(RwFrame* frame, const RwMatrix* matrix, RwOpCombineType combine);
// 0x0074a6f0 RwFrameGetLTM (Ghidra RW_GetFrameLocalToWorldMatrix): the modelling matrix times the parent's
// LTM (object.parent), a root's its modelling matrix.
RwMatrix* RwFrameGetLTM(RwFrame* frame);
// 0x00010698 RwFrame_MarkDirty (game code, unit Wcs.cpp): RwFrameUpdateObjects without the dirty list: the
// root frame's private flags |= 3, the frame's |= 0xc.
inline void RwFrame_MarkDirty(RwFrame* frame) {
    frame->root->object.privateFlags |= 0x3;
    frame->object.privateFlags |= 0xc;
}

// DEV: a camera with the front end's UI camera values (above): its frame, a 1280x720 frame-buffer raster
// and no z buffer. No PS3 counterpart; the tests' stand-in (the engine's UI camera is CameraContext's).
RwCamera* RwShim_CreateUICamera();
void RwShim_DestroyUICamera(RwCamera* camera);

// ---- C1.4: the RW 3.7 camera and raster calls the camera context makes (RwCamera / RwRaster API) -----
// RwCameraCreate: perspective, view window (1, 1), no offset, near 0.05, far 10, fog 5, no rasters, no frame.
RwCamera* RwCameraCreate();
RwCamera* RwCameraSetViewWindow(RwCamera* camera, const RwV2d* viewWindow);
RwCamera* RwCameraSetViewOffset(RwCamera* camera, const RwV2d* offset);
RwCamera* RwCameraSetNearClipPlane(RwCamera* camera, RwReal nearPlane);
RwCamera* RwCameraSetFarClipPlane(RwCamera* camera, RwReal farPlane);
RwCamera* RwCameraSetProjection(RwCamera* camera, RwCameraProjection projection);
// RwObjectHasFrameSetFrame on a camera: object.parent.
void RwCameraSetFrame(RwCamera* camera, RwFrame* frame);
// RwCameraBeginUpdate: the camera's view becomes the device's (rwcore/RwDevice.h); the camera, or null
// without a frame buffer.
// The world plugin's WorldCameraBeginUpdate (RW 3.7 baworobj.c, which chains it) also counts the camera updates:
// RWSRCGLOBAL(renderFrame)++ (every camera here draws a world).
RwCamera* RwCameraBeginUpdate(RwCamera* camera);
RwCamera* RwCameraEndUpdate(RwCamera* camera);
// RWSRCGLOBAL(renderFrame) (RWEngineInstance +8, a 16-bit count of camera updates; RpWorldPluginAttach sets it to 1).
RwUInt16 RwEngineRenderFrame();
// RwCameraFrustumTestSphere (the library's, TocBridge 0x98xxxx; RW 3.7 bacamera.c): a world-space sphere (x, y, z, radius)
// against the camera's view frustum (near and far planes and the four sides of the view window at the camera frame's
// current pose). rwSPHEREOUTSIDE 0, rwSPHEREBOUNDARY 1, rwSPHEREINSIDE 2.
enum : RwInt32 { rwSPHEREOUTSIDE = 0, rwSPHEREBOUNDARY = 1, rwSPHEREINSIDE = 2 };
RwInt32 RwCameraFrustumTestSphere(const RwCamera* camera, const RwReal* sphere);
// RwCameraClear: rwCAMERACLEARIMAGE 1 (with colour), rwCAMERACLEARZ 2 (and stencil 4) of the device target.
enum : RwInt32 { rwCAMERACLEARIMAGE = 1, rwCAMERACLEARZ = 2, rwCAMERACLEARSTENCIL = 4 };
RwCamera* RwCameraClear(RwCamera* camera, const RwRGBA* color, RwInt32 clearMode);
// RwCameraShowRaster: presents the frame (platform/gfx EndFrame).
RwCamera* RwCameraShowRaster(RwCamera* camera, void* device, RwUInt32 flags);
// RwRasterCreate: a raster record of that size (the device target stands for the camera rasters).
enum : RwInt32 { rwRASTERTYPENORMAL = 0, rwRASTERTYPEZBUFFER = 1, rwRASTERTYPECAMERA = 2, rwRASTERTYPETEXTURE = 4,
                 rwRASTERTYPECAMERATEXTURE = 5 };
RwRaster* RwRasterCreate(RwInt32 width, RwInt32 height, RwInt32 depth, RwInt32 flags);
RwBool RwRasterDestroy(RwRaster* raster);
