// RwCamera.h - the RenderWare 3.7 camera, raster and frame fields the 2D toolkit reads (Rt2dOpen,
// Rt2dDeviceSetCamera, the composite CTM) and the frame calls the Rt2d shapes make, in the PS3 layout.
//
// The frame (RwFrameCreate / RwFrameDestroy here; the hierarchy, the dirty list and the syncs in RwFrameList.cpp) and
// the camera fields the game and the toolkits read. The camera's projection is the device's (RwDevice.cpp:
// RwCameraBeginUpdate hands the camera to platform/gfx, which builds the view and projection from the frame's LTM, the
// view window and the planes, as the PSGL driver's camera begin-update does); the view matrix, the frustum planes,
// corners and box are the camera's own (_rwCameraSync), which RwCameraFrustumTestSphere reads. The rasters: RwRaster.h.
//
// The UI camera of the front end (render context +0x20, read live in RPCS3 at the main menu): projection
// type 1 (rwPERSPECTIVE), view window (0.5, 0.5), near 0.01, far 1000, a 1280x720 frame buffer, and a
// frame whose LTM is right (1,0,0), up (0,1,0), at (0,0,1), pos (0.5, 0.5, -1) with flags 3.
#pragma once
#include "Renderware/rwcore/RwRaster.h"
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
    // clears the frame's own sync bit 4, so RW's sync leaves that LTM alone. (RwFrameGetLTM follows RW's marks and no
    // longer reads this flag.)
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

// RwFrustumPlane (RW 3.7 bacamera.h: RwPlane {normal, distance}, then the closest-corner bytes).
struct RwFrustumPlane {
    RwV3d normal;      // +0x00
    RwReal distance;   // +0x0c
    RwUInt8 closestX;  // +0x10 normal.x >= 0
    RwUInt8 closestY;  // +0x11
    RwUInt8 closestZ;  // +0x12
    RwUInt8 pad;       // +0x13
};
DOTD_ASSERT_SIZE(RwFrustumPlane, 0x14);

// RwCamera (RW 3.7 order; PS3 offsets).
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
    // _rwCameraSync's frustum: far, near, left, top, right, bottom (normals pointing out of the frustum).
    RwFrustumPlane frustumPlanes[6];  // +0x94
    RwBBox frustumBoundBox;           // +0x10c
    RwV3d frustumCorners[8];          // +0x124 near 0-3, far 4-7 (top right, top left, bottom left, bottom right)
    // The world plugin's camera extension (RpWorldCameraExt: the world the camera was added to, RpWorldAddCamera;
    // RpWorld.h), in the camera's plugin data.
    struct RpWorld* worldExt;
};
DOTD_ASSERT_OFFSET(RwCamera, projectionType, 0x14);
DOTD_ASSERT_OFFSET(RwCamera, frameBuffer, 0x60);
DOTD_ASSERT_OFFSET(RwCamera, viewWindow, 0x68);
DOTD_ASSERT_OFFSET(RwCamera, nearPlane, 0x80);
DOTD_ASSERT_OFFSET(RwCamera, farPlane, 0x84);
DOTD_ASSERT_OFFSET(RwCamera, frustumPlanes, 0x94);
DOTD_ASSERT_OFFSET(RwCamera, frustumBoundBox, 0x10c);
DOTD_ASSERT_OFFSET(RwCamera, frustumCorners, 0x124);

// The camera's frame (RwCameraGetFrame: object.parent).
inline RwFrame* RwCameraGetFrame(RwCamera* camera) { return static_cast<RwFrame*>(camera->object.parent); }

// 0x0074b470 RwFrameCreate: identity modelling and LTM.
RwFrame* RwFrameCreate();
// 0x0074c958 RwFrameDestroy (RW 3.7 baframe.c, _rwFrameInternalDeInit): the plugins' destructors, a child taken out of
// its parent (RwFrameRemoveChild inlined: it becomes a marked root), off the dirty list when it is marked, its children
// left as roots without a parent (their root pointers still name this frame), the frame freed.
RwBool RwFrameDestroy(RwFrame* frame);
// FrameDestroyRecurseDeInitLeaf + the free (RW 3.7 baframe.c; inlined in RwFrameDestroyHierarchy 0x74bc80 and
// RwFrameDestroyRecurse_maybe 0x74b5b0): the plugins' destructors, off the dirty list when marked, freed; the parent and
// the children are not touched.
void _rwFrameDestroyLeaf(RwFrame* frame);
// 0x0074ac40 RwFrameTransform: combines matrix into the modelling matrix (replace / pre / post).
RwFrame* RwFrameTransform(RwFrame* frame, const RwMatrix* matrix, RwOpCombineType combine);
// 0x0074a6f0 RwFrameGetLTM (Ghidra RW_GetFrameLocalToWorldMatrix): the LTM, the hierarchy synced first when its root is
// marked (RwCamera.cpp).
RwMatrix* RwFrameGetLTM(RwFrame* frame);
// The frame's stored LTM (RwFrame +0x80) as it is, without RwFrameGetLTM's hierarchy sync: how the game code reads it
// everywhere except the eleven render-side calls of BridgeRwGetFrameLocalToWorldMatrix 0x98e2f0 (the scene cameras'
// sync, the frame renders, the animated nodes' pose and cull, the skin palette, the surface particles, the mesh pass
// matrix). A sync from game code makes a frame current before the original's render does: the camera service's stack
// read this frame's LTM where the original reads last frame's (C2.7, fight capture 2, +832).
inline const RwMatrix* FrameLtm(const RwFrame* frame) { return &frame->ltm; }
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
// 0x00748368 RwCameraDestroy: the frame released and the camera freed (its rasters and frame are the caller's).
RwBool RwCameraDestroy(RwCamera* camera);
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
// 0x007471c8 _rwCameraSync_maybe (RW 3.7 bacamera.c CameraSync, the camera's frame-object sync): the view matrix from
// the frame's stored LTM, the reciprocal view window and the view offset (CameraBuildPerspViewMatrix /
// CameraBuildParallelViewMatrix: x and y scaled into [0, 1] with y flipped, z along `at`), then RwMatrixOptimize; the
// frustum planes and corners (CameraBuildPerspClipPlanes / CameraBuildParallelClipPlanes) and the corners' box
// (RwBBoxCalculate).
void _rwCameraSync(RwCamera* camera);
// 0x00748720 RwCameraFrustumTestSphere (RW 3.7 bacamera.c, the PS3 build's AltiVec code): a world-space sphere (x, y, z,
// radius) against the six planes _rwCameraSync stored. rwSPHEREOUTSIDE 0, rwSPHEREBOUNDARY 1, rwSPHEREINSIDE 2.
enum : RwInt32 { rwSPHEREOUTSIDE = 0, rwSPHEREBOUNDARY = 1, rwSPHEREINSIDE = 2 };
RwInt32 RwCameraFrustumTestSphere(const RwCamera* camera, const RwReal* sphere);
// RwCameraClear: rwCAMERACLEARIMAGE 1 (with colour), rwCAMERACLEARZ 2 (and stencil 4) of the device target.
enum : RwInt32 { rwCAMERACLEARIMAGE = 1, rwCAMERACLEARZ = 2, rwCAMERACLEARSTENCIL = 4 };
RwCamera* RwCameraClear(RwCamera* camera, const RwRGBA* color, RwInt32 clearMode);
// RwCameraShowRaster: presents the frame (platform/gfx EndFrame).
RwCamera* RwCameraShowRaster(RwCamera* camera, void* device, RwUInt32 flags);
// RwRasterCreate / RwRasterDestroy: Renderware/rwcore/RwRaster.h.
