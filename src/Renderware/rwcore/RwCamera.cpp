// RwCamera.cpp - the root-frame calls and the UI camera stand-in. See RwCamera.h.
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwFrameList.h"

#include <cmath>
#include <cstring>
#include <new>

#include "Renderware/rphanim/RpHAnim.h"
#include "Renderware/rwcore/RwDevice.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "Renderware/rwcore/RwSList.h"
#include "crt/ppc_ops.h"
#include "crt/vmx_ops.h"
#include "platform/sdl/freecam.h"
#include "platform/gfx/device.h"

namespace {
// RWFRAMEGLOBAL(frames) (RWEngineInstance + [0xcf00b0]): the frame free list (_rwFrameOpen; the host heap here, RwSList.h).
RwFreeList* FrameFreeList() {
    static RwFreeList* s_frames = RwFreeListCreateAndPreallocateSpace(static_cast<RwInt32>(sizeof(RwFrame)), 0x32, 16, 1,
                                                                      nullptr, 0x3000e);
    return s_frames;
}
}  // namespace

// 0x0074b470 RwFrameCreate (RW 3.7 baframe.c, rwFrameInternalInit): a frame from the free list, an unparented root with
// an empty object list and identity modelling and LTM matrices (flags rwMATRIXTYPEORTHONORMAL | rwMATRIXINTERNALIDENTITY),
// then the plugins' constructors (_rwPluginRegistryInitObject: RpHAnim's HAnimFrameConstructor_maybe 0x6e6190, id -1
// and no hierarchy). RW leaves the dirty-list link as the free list's memory holds it; DOTD: it is cleared, because the
// port's dirty list tests the link for membership (RwFrameList.cpp), and the DOTD field too.
RwFrame* RwFrameCreate() {
    void* memory = RwFreeListAlloc(FrameFreeList(), 0x3000e);  // rwMEMHINTDUR_EVENT | rwID_FRAMELIST
    if (memory == nullptr) return nullptr;
    RwFrame* frame = new (memory) RwFrame;
    frame->object.privateFlags = 0;
    frame->objectList.prev = &frame->objectList;
    frame->ltm.right.x = 1.0f;
    frame->object.type = 0;  // rwFRAME
    frame->object.subType = 0;
    frame->object.flags = 0;
    frame->object.parent = nullptr;
    frame->objectList.next = &frame->objectList;
    frame->modelling.at.z = 1.0f;
    frame->modelling.up.y = 1.0f;
    frame->modelling.right.x = 1.0f;
    frame->modelling.up.x = 0.0f;
    frame->modelling.right.z = 0.0f;
    frame->modelling.right.y = 0.0f;
    frame->modelling.at.y = 0.0f;
    frame->modelling.at.x = 0.0f;
    frame->modelling.up.z = 0.0f;
    frame->modelling.pos.z = 0.0f;
    frame->modelling.pos.y = 0.0f;
    frame->modelling.pos.x = 0.0f;
    frame->modelling.flags = rwMATRIXTYPEORTHONORMAL | rwMATRIXINTERNALIDENTITY;  // 0x20003
    frame->ltm.at.z = 1.0f;
    frame->ltm.up.y = 1.0f;
    frame->ltm.up.x = 0.0f;
    frame->ltm.right.z = 0.0f;
    frame->ltm.right.y = 0.0f;
    frame->ltm.at.y = 0.0f;
    frame->ltm.at.x = 0.0f;
    frame->ltm.up.z = 0.0f;
    frame->ltm.pos.z = 0.0f;
    frame->ltm.pos.y = 0.0f;
    frame->ltm.pos.x = 0.0f;
    frame->ltm.flags = rwMATRIXTYPEORTHONORMAL | rwMATRIXINTERNALIDENTITY;
    frame->next = nullptr;
    frame->root = frame;
    frame->child = nullptr;
    frame->hanimID = -1;  // 0x006e6190 HAnimFrameConstructor_maybe
    frame->hanimHierarchy = nullptr;
    frame->inDirtyListLink.next = nullptr;  // DOTD (see above)
    frame->inDirtyListLink.prev = nullptr;
    frame->dotdLtmOwned = 0;
    return frame;
}

namespace {
// _rwPluginRegistryDeInitObject(&frameTKList, frame): the frame plugins' destructors. The one registered with a
// destructor is RpHAnim's (0x6e8330).
void FramePluginsDeInit(RwFrame* frame) { HAnimFrameDestructor(frame); }
}  // namespace

// 0x0074c958 RwFrameDestroy
RwBool RwFrameDestroy(RwFrame* frame) {
    FramePluginsDeInit(frame);
    if (frame->object.parent != nullptr) RwFrameRemoveChild(frame);
    // rwFRAMEPRIVATEHIERARCHYSYNC*. DOTD: also a frame still linked with its marks cleared (CSGLeaf_PostLoad clears them,
    // the port's link stays: RwFrameList.cpp); a freed frame left on the list broke it once its memory was reused.
    if ((frame->object.privateFlags & 3) != 0 || frame->inDirtyListLink.next != nullptr) RwFrameDirtyListRemove(frame);
    for (RwFrame* child = frame->child; child != nullptr; child = child->next) child->object.parent = nullptr;
    RwFreeListFree(FrameFreeList(), frame);
    return 1;
}

// FrameDestroyRecurseDeInitLeaf (inlined in 0x74bc80 / 0x74b5b0)
void _rwFrameDestroyLeaf(RwFrame* frame) {
    FramePluginsDeInit(frame);
    if ((frame->object.privateFlags & 3) != 0 || frame->inDirtyListLink.next != nullptr) RwFrameDirtyListRemove(frame);  // DOTD: as above
    RwFreeListFree(FrameFreeList(), frame);
}

// 0x0074ac40 RwFrameTransform: the matrix combined into the modelling matrix, then RwFrameUpdateObjects.
RwFrame* RwFrameTransform(RwFrame* frame, const RwMatrix* matrix, RwOpCombineType combine) {
    RwMatrix result;
    switch (combine) {
        case rwCOMBINEREPLACE: result = *matrix; break;
        case rwCOMBINEPRECONCAT: RwMatrixMultiply(&result, matrix, &frame->modelling); break;
        case rwCOMBINEPOSTCONCAT: RwMatrixMultiply(&result, &frame->modelling, matrix); break;
        default: return nullptr;
    }
    frame->modelling = result;
    RwFrameUpdateObjects(frame);
    return frame;
}

// 0x0074a6f0 RwFrameGetLTM (RW 3.7 core/src/baframe.c): the whole hierarchy synced first when its root is marked
// (rwFRAMEPRIVATEHIERARCHYSYNCLTM: _rwFrameSyncHierarchyLTM), else the LTM as stored. A frame whose hierarchy was never
// marked after its modelling matrix changed keeps its old LTM, as on the PS3 (the collision tests read the stored LTMs:
// loaded frames only carry their own subtree mark from CSGMovable_Load until the first sync of their hierarchy).
RwMatrix* RwFrameGetLTM(RwFrame* frame) {
    if ((frame->root->object.privateFlags & 1) != 0) _rwFrameSyncHierarchyLTM(frame->root);
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

// 0x00748368 RwCameraDestroy (RW 3.7 bacamera.c): the plugins' destructors (_rwPluginRegistryDeInitObject: the world's
// WorldDeInitCameraExt frees the sectors-in-frustum list and restores the camera's begin / end / sync callbacks, the
// clump's ClumpDeInitCameraExt only asserts; the remake's camera has neither list nor overloads), the frame released
// (_rwObjectHasFrameReleaseFrame), the camera back to its free list.
RwBool RwCameraDestroy(RwCamera* camera) {
    camera->object.parent = nullptr;
    RwFree(camera);
    return 1;
}

namespace {
// RW 3.7 bacamera.c: the setters end with RwFrameUpdateObjects on the camera's frame when it has one (the frustum
// follows at the next sync).
void MarkCameraFrame(RwCamera* camera) {
    RwFrame* frame = static_cast<RwFrame*>(camera->object.parent);
    if (frame != nullptr) RwFrameUpdateObjects(frame);
}
}  // namespace

RwCamera* RwCameraSetViewWindow(RwCamera* camera, const RwV2d* viewWindow) {
    camera->viewWindow = *viewWindow;
    camera->recipViewWindow.x = 1.0f / viewWindow->x;
    camera->recipViewWindow.y = 1.0f / viewWindow->y;
    MarkCameraFrame(camera);
    return camera;
}

RwCamera* RwCameraSetViewOffset(RwCamera* camera, const RwV2d* offset) {
    camera->viewOffset = *offset;
    MarkCameraFrame(camera);
    return camera;
}

RwCamera* RwCameraSetNearClipPlane(RwCamera* camera, RwReal nearPlane) {
    camera->nearPlane = nearPlane;
    MarkCameraFrame(camera);
    return camera;
}

RwCamera* RwCameraSetFarClipPlane(RwCamera* camera, RwReal farPlane) {
    camera->farPlane = farPlane;
    MarkCameraFrame(camera);
    return camera;
}

RwCamera* RwCameraSetProjection(RwCamera* camera, RwCameraProjection projection) {
    camera->projectionType = projection;
    MarkCameraFrame(camera);
    return camera;
}

// RwCameraSetFrame (_rwObjectHasFrameSetFrame, batypehf.c): the frame attached, then RwFrameUpdateObjects on it.
void RwCameraSetFrame(RwCamera* camera, RwFrame* frame) {
    camera->object.parent = frame;
    if (frame != nullptr) RwFrameUpdateObjects(frame);
}

namespace {
RwUInt16 g_renderFrame = 1;  // RWSRCGLOBAL(renderFrame), 1 after the world plugin's open
}  // namespace

RwUInt16 RwEngineRenderFrame() { return g_renderFrame; }

RwCamera* RwCameraBeginUpdate(RwCamera* camera) {
    ++g_renderFrame;  // WorldCameraBeginUpdate, before the chained begin update
    _rwFrameSyncDirty();
    if (camera == nullptr || camera->frameBuffer == nullptr) return nullptr;
    RwDevice_BeginCameraUpdate(camera);  // 0x00738a68 BeginPSGLCameraUpdate (frame buffer, view, projection)
    return camera;
}

RwCamera* RwCameraEndUpdate(RwCamera* camera) {
    if (camera != nullptr) RwDevice_EndCameraUpdate(camera);  // 0x00738988 EndPSGLCameraUpdate
    return camera;
}

namespace {
// The frustum part of 0x007471c8 _rwCameraSync_maybe for rwPERSPECTIVE (CameraBuildPerspClipPlanes, RW 3.7 bacamera.c):
// the centre of projection (-offset.x right + offset.y up), the view window's corners at z = 1 walked from the top one,
// moved to the near and far planes from the position, then the far and near planes (the at axis and its negation)
// and the four sides (normalised crosses of the longest edges, rwInvSqrt), each with the signs of its normal
// (closestX / Y / Z: component >= 0, fcmpu + cror). The PS3 code's own order of the scalar operations, from the
// disassembly (fmadds / fmsubs where it fuses).
void CameraBuildPerspClipPlanes(RwCamera* camera, const RwMatrix* ltm) {
    RwFrustumPlane* planes = camera->frustumPlanes;
    RwV3d* corners = camera->frustumCorners;
    const float t31 = -camera->viewOffset.x;
    const float t32 = ltm->right.x * camera->viewWindow.x;
    const float t33 = ltm->right.z * camera->viewWindow.x;
    const float t34 = ltm->right.y * camera->viewWindow.x;
    const float t35 = ltm->up.x * camera->viewWindow.y;
    const float t36 = ltm->up.z * camera->viewWindow.y;
    const float t37 = ltm->up.y * camera->viewWindow.y;
    const float t38 = camera->viewOffset.y * ltm->up.z;
    const float t39 = ltm->up.x * camera->viewOffset.y;
    const float t40 = camera->viewOffset.y * ltm->up.y;
    const float t41 = t32 + ltm->at.x;
    const float t42 = t32 + t32;
    const float t43 = t33 + ltm->at.z;
    const float t44 = t34 + ltm->at.y;
    const float t45 = t34 + t34;
    const float t46 = t33 + t33;
    const float t47 = t36 + t36;
    const float t48 = t35 + t35;
    const float t49 = t37 + t37;
    const float t50 = ppc::fmadds(t31, ltm->right.z, t38);
    const float t51 = t41 + t35;
    const float t52 = ppc::fmadds(t31, ltm->right.x, t39);
    const float t53 = t43 + t36;
    const float t54 = t44 + t37;
    const float t55 = ppc::fmadds(t31, ltm->right.y, t40);
    const float t56 = t51 - t42;
    corners[0].x = t51;
    const float t57 = t53 - t46;
    corners[0].z = t53;
    const float t58 = t54 - t45;
    corners[0].y = t54;
    const float t59 = t56 - t48;
    corners[1].x = t56;
    const float t60 = t57 - t47;
    corners[1].z = t57;
    const float t61 = t58 - t49;
    corners[1].y = t58;
    const float t62 = t42 + t59;
    corners[2].x = t59;
    const float t63 = t46 + t60;
    corners[2].z = t60;
    const float t64 = t45 + t61;
    corners[2].y = t61;
    corners[3].x = t62;
    corners[3].z = t63;
    const float t65 = t52 + ltm->pos.x;
    corners[3].y = t64;
    const float t66 = t55 + ltm->pos.y;
    const float t67 = t50 + ltm->pos.z;
    const float t68 = t51 - t52;
    const float t69 = t54 - t55;
    const float t70 = t53 - t50;
    corners[0].x = t65;
    corners[0].y = t66;
    corners[0].z = t67;
    const float t71 = ppc::fmadds(t68, camera->nearPlane, t65);
    corners[0].x = t71;
    const float t72 = ppc::fmadds(t69, camera->nearPlane, t66);
    const float t73 = t52 + ltm->pos.x;
    corners[0].y = t72;
    const float t74 = ppc::fmadds(t70, camera->nearPlane, t67);
    const float t75 = t55 + ltm->pos.y;
    corners[4].x = t73;
    corners[0].z = t74;
    const float t76 = t50 + ltm->pos.z;
    corners[4].y = t75;
    corners[4].z = t76;
    const float t77 = ppc::fmadds(t68, camera->farPlane, t73);
    corners[4].x = t77;
    const float t78 = ppc::fmadds(t69, camera->farPlane, t75);
    const float t79 = t52 + ltm->pos.x;
    const float t80 = t56 - t52;
    corners[4].y = t78;
    const float t81 = ppc::fmadds(t70, camera->farPlane, t76);
    const float t82 = t55 + ltm->pos.y;
    corners[1].x = t79;
    const float t83 = t58 - t55;
    corners[4].z = t81;
    const float t84 = t50 + ltm->pos.z;
    corners[1].y = t82;
    const float t85 = t57 - t50;
    corners[1].z = t84;
    const float t86 = ppc::fmadds(t80, camera->nearPlane, t79);
    corners[1].x = t86;
    const float t87 = ppc::fmadds(t83, camera->nearPlane, t82);
    const float t88 = t52 + ltm->pos.x;
    corners[1].y = t87;
    const float t89 = ppc::fmadds(t85, camera->nearPlane, t84);
    corners[1].z = t89;
    const float t90 = t55 + ltm->pos.y;
    const float t91 = t50 + ltm->pos.z;
    corners[5].x = t88;
    corners[5].y = t90;
    corners[5].z = t91;
    const float t92 = ppc::fmadds(t80, camera->farPlane, t88);
    corners[5].x = t92;
    const float t93 = ppc::fmadds(t83, camera->farPlane, t90);
    const float t94 = t52 + ltm->pos.x;
    const float t95 = t59 - t52;
    corners[5].y = t93;
    const float t96 = ppc::fmadds(t85, camera->farPlane, t91);
    const float t97 = t55 + ltm->pos.y;
    corners[2].x = t94;
    const float t98 = t61 - t55;
    corners[5].z = t96;
    const float t99 = t50 + ltm->pos.z;
    corners[2].y = t97;
    const float t100 = t60 - t50;
    corners[2].z = t99;
    const float t101 = ppc::fmadds(t95, camera->nearPlane, t94);
    corners[2].x = t101;
    const float t102 = ppc::fmadds(t98, camera->nearPlane, t97);
    const float t103 = t52 + ltm->pos.x;
    corners[2].y = t102;
    const float t104 = ppc::fmadds(t100, camera->nearPlane, t99);
    const float t105 = t55 + ltm->pos.y;
    corners[6].x = t103;
    corners[2].z = t104;
    const float t106 = t50 + ltm->pos.z;
    corners[6].y = t105;
    corners[6].z = t106;
    const float t107 = ppc::fmadds(t95, camera->farPlane, t103);
    corners[6].x = t107;
    const float t108 = ppc::fmadds(t98, camera->farPlane, t105);
    const float t109 = t52 + ltm->pos.x;
    corners[6].y = t108;
    const float t110 = ppc::fmadds(t100, camera->farPlane, t106);
    const float t111 = t55 + ltm->pos.y;
    const float t112 = t62 - t52;
    corners[3].x = t109;
    const float t113 = t64 - t55;
    corners[6].z = t110;
    const float t114 = t50 + ltm->pos.z;
    corners[3].y = t111;
    const float t115 = t63 - t50;
    corners[3].z = t114;
    const float t116 = ppc::fmadds(t112, camera->nearPlane, t109);
    corners[3].x = t116;
    const float t117 = ppc::fmadds(t113, camera->nearPlane, t111);
    const float t118 = t52 + ltm->pos.x;
    corners[3].y = t117;
    const float t119 = ppc::fmadds(t115, camera->nearPlane, t114);
    const float t120 = t55 + ltm->pos.y;
    corners[7].x = t118;
    corners[3].z = t119;
    const float t121 = t50 + ltm->pos.z;
    corners[7].y = t120;
    corners[7].z = t121;
    const float t122 = ppc::fmadds(t112, camera->farPlane, t118);
    corners[7].x = t122;
    const float t123 = ppc::fmadds(t113, camera->farPlane, t120);
    corners[7].y = t123;
    const float t124 = ppc::fmadds(t115, camera->farPlane, t121);
    corners[7].z = t124;
    planes[0].normal.x = ltm->at.x;
    planes[0].normal.y = ltm->at.y;
    planes[0].normal.z = ltm->at.z;
    const float t125 = t78 * ltm->at.y;
    const float t126 = ppc::fmadds(t77, ltm->at.x, t125);
    const float t127 = ppc::fmadds(t81, ltm->at.z, t126);
    planes[0].distance = t127;
    planes[0].closestX = (ltm->at.x >= 0.0f) ? 1 : 0;
    planes[0].closestY = (ltm->at.y >= 0.0f) ? 1 : 0;
    const float t128 = -ltm->at.y;
    planes[0].closestZ = (ltm->at.z >= 0.0f) ? 1 : 0;
    const float t129 = -ltm->at.x;
    const float t130 = -ltm->at.z;
    planes[1].normal.y = t128;
    const float t131 = t72 * t128;
    planes[1].normal.x = t129;
    planes[1].normal.z = t130;
    const float t132 = ppc::fmadds(t71, t129, t131);
    const float t133 = ppc::fmadds(t130, t74, t132);
    planes[1].distance = t133;
    planes[1].closestX = (t129 >= 0.0f) ? 1 : 0;
    planes[1].closestY = (t128 >= 0.0f) ? 1 : 0;
    planes[1].closestZ = (t130 >= 0.0f) ? 1 : 0;
    const float t134 = t86 - t92;
    const float t135 = t110 - t96;
    const float t136 = t89 - t96;
    const float t137 = t107 - t92;
    const float t138 = t108 - t93;
    const float t139 = t87 - t93;
    const float t140 = t134 * t135;
    const float t141 = t136 * t138;
    const float t142 = ppc::fmsubs(t136, t137, t140);
    const float t143 = t139 * t137;
    const float t144 = ppc::fmsubs(t139, t135, t141);
    const float t145 = t142 * t142;
    planes[2].normal.y = t142;
    const float t146 = ppc::fmsubs(t134, t138, t143);
    planes[2].normal.x = t144;
    const float t147 = ppc::fmadds(t144, t144, t145);
    planes[2].normal.z = t146;
    const float t148 = ppc::fmadds(t146, t146, t147);
    const float t149 = rwInvSqrt(t148);
    const float t150 = t149 * t142;
    const float t151 = t149 * t144;
    const float t152 = t149 * t146;
    planes[2].normal.y = t150;
    const float t153 = t87 * t150;
    planes[2].normal.x = t151;
    planes[2].normal.z = t152;
    const float t154 = ppc::fmadds(t86, t151, t153);
    const float t155 = ppc::fmadds(t152, t89, t154);
    planes[2].distance = t155;
    planes[2].closestX = (t151 >= 0.0f) ? 1 : 0;
    planes[2].closestY = (t150 >= 0.0f) ? 1 : 0;
    planes[2].closestZ = (t152 >= 0.0f) ? 1 : 0;
    const float t156 = t77 - t92;
    const float t157 = t81 - t96;
    const float t158 = t78 - t93;
    const float t159 = t136 * t156;
    const float t160 = t139 * t157;
    const float t161 = t134 * t158;
    const float t162 = ppc::fmsubs(t134, t157, t159);
    const float t163 = ppc::fmsubs(t136, t158, t160);
    const float t164 = ppc::fmsubs(t139, t156, t161);
    const float t165 = t162 * t162;
    planes[3].normal.y = t162;
    planes[3].normal.x = t163;
    planes[3].normal.z = t164;
    const float t166 = ppc::fmadds(t163, t163, t165);
    const float t167 = ppc::fmadds(t164, t164, t166);
    const float t168 = rwInvSqrt(t167);
    const float t169 = t168 * t162;
    const float t170 = t168 * t163;
    const float t171 = t168 * t164;
    planes[3].normal.y = t169;
    const float t172 = t87 * t169;
    planes[3].normal.x = t170;
    planes[3].normal.z = t171;
    const float t173 = ppc::fmadds(t86, t170, t172);
    const float t174 = ppc::fmadds(t171, t89, t173);
    planes[3].distance = t174;
    planes[3].closestX = (t170 >= 0.0f) ? 1 : 0;
    planes[3].closestY = (t169 >= 0.0f) ? 1 : 0;
    planes[3].closestZ = (t171 >= 0.0f) ? 1 : 0;
    const float t175 = t116 - t122;
    const float t176 = t81 - t124;
    const float t177 = t77 - t122;
    const float t178 = t78 - t123;
    const float t179 = t119 - t124;
    const float t180 = t117 - t123;
    const float t181 = t175 * t176;
    const float t182 = t179 * t178;
    const float t183 = t180 * t177;
    const float t184 = ppc::fmsubs(t179, t177, t181);
    const float t185 = ppc::fmsubs(t180, t176, t182);
    const float t186 = ppc::fmsubs(t175, t178, t183);
    const float t187 = t184 * t184;
    planes[4].normal.y = t184;
    planes[4].normal.x = t185;
    planes[4].normal.z = t186;
    const float t188 = ppc::fmadds(t185, t185, t187);
    const float t189 = ppc::fmadds(t186, t186, t188);
    const float t190 = rwInvSqrt(t189);
    const float t191 = t190 * t184;
    const float t192 = t190 * t185;
    const float t193 = t190 * t186;
    planes[4].normal.y = t191;
    const float t194 = t117 * t191;
    planes[4].normal.x = t192;
    planes[4].normal.z = t193;
    const float t195 = ppc::fmadds(t116, t192, t194);
    const float t196 = ppc::fmadds(t193, t119, t195);
    planes[4].distance = t196;
    planes[4].closestX = (t192 >= 0.0f) ? 1 : 0;
    planes[4].closestY = (t191 >= 0.0f) ? 1 : 0;
    planes[4].closestZ = (t193 >= 0.0f) ? 1 : 0;
    const float t197 = t107 - t122;
    const float t198 = t110 - t124;
    const float t199 = t108 - t123;
    const float t200 = t179 * t197;
    const float t201 = t180 * t198;
    const float t202 = t175 * t199;
    const float t203 = ppc::fmsubs(t175, t198, t200);
    const float t204 = ppc::fmsubs(t179, t199, t201);
    const float t205 = ppc::fmsubs(t180, t197, t202);
    const float t206 = t203 * t203;
    planes[5].normal.y = t203;
    planes[5].normal.x = t204;
    planes[5].normal.z = t205;
    const float t207 = ppc::fmadds(t204, t204, t206);
    const float t208 = ppc::fmadds(t205, t205, t207);
    const float t209 = rwInvSqrt(t208);
    const float t210 = t209 * t203;
    const float t211 = t209 * t204;
    const float t212 = t209 * t205;
    planes[5].normal.y = t210;
    const float t213 = t117 * t210;
    planes[5].normal.x = t211;
    planes[5].normal.z = t212;
    const float t214 = ppc::fmadds(t116, t211, t213);
    const float t215 = ppc::fmadds(t212, t119, t214);
    planes[5].distance = t215;
    planes[5].closestX = (t211 >= 0.0f) ? 1 : 0;
    planes[5].closestY = (t210 >= 0.0f) ? 1 : 0;
    planes[5].closestZ = (t212 >= 0.0f) ? 1 : 0;
}

// The frustum part of 0x007471c8 _rwCameraSync_maybe for rwPARALLEL (CameraBuildParallelClipPlanes): the corners in
// camera space (the window sheared by the view offset at the near and far planes), RwV3dTransformPoints 0x75e850 into
// world space, then the planes as above, the right and bottom ones the left and top ones negated.
void CameraBuildParallelClipPlanes(RwCamera* camera, const RwMatrix* ltm) {
    RwFrustumPlane* planes = camera->frustumPlanes;
    RwV3d* corners = camera->frustumCorners;
    const float t31 = -camera->viewOffset.x;
    const float t32 = 1.0f - camera->farPlane;
    const float t33 = 1.0f - camera->nearPlane;
    const float t34 = camera->viewOffset.y * t32;
    const float t35 = t31 * t32;
    const float t36 = camera->viewOffset.y * t33;
    const float t37 = t31 * t33;
    corners[3].z = camera->nearPlane;
    corners[2].z = camera->nearPlane;
    corners[1].z = camera->nearPlane;
    corners[0].z = camera->nearPlane;
    corners[7].z = camera->farPlane;
    const float t38 = t34 - camera->viewWindow.y;
    const float t39 = t35 - camera->viewWindow.x;
    corners[6].z = camera->farPlane;
    const float t40 = t36 - camera->viewWindow.y;
    corners[5].z = camera->farPlane;
    const float t41 = t37 - camera->viewWindow.x;
    corners[4].z = camera->farPlane;
    const float t42 = camera->viewWindow.x + t37;
    const float t43 = camera->viewWindow.y + t36;
    const float t44 = camera->viewWindow.x + t35;
    const float t45 = camera->viewWindow.y + t34;
    corners[3].x = t42;
    corners[1].y = t43;
    corners[0].x = t42;
    corners[0].y = t43;
    corners[2].x = t41;
    corners[3].y = t40;
    corners[1].x = t41;
    corners[2].y = t40;
    corners[7].x = t44;
    corners[5].y = t45;
    corners[4].x = t44;
    corners[4].y = t45;
    corners[6].x = t39;
    corners[7].y = t38;
    corners[5].x = t39;
    corners[6].y = t38;
    RwV3dTransformPoints(corners, corners, 8, ltm);
    planes[0].normal.x = ltm->at.x;
    planes[0].normal.y = ltm->at.y;
    planes[0].normal.z = ltm->at.z;
    const float t46 = corners[4].y * ltm->at.y;
    const float t47 = ppc::fmadds(corners[4].x, ltm->at.x, t46);
    const float t48 = ppc::fmadds(corners[4].z, ltm->at.z, t47);
    planes[0].distance = t48;
    planes[0].closestX = (ltm->at.x >= 0.0f) ? 1 : 0;
    planes[0].closestY = (ltm->at.y >= 0.0f) ? 1 : 0;
    const float t49 = -ltm->at.y;
    planes[0].closestZ = (ltm->at.z >= 0.0f) ? 1 : 0;
    const float t50 = -ltm->at.x;
    const float t51 = -ltm->at.z;
    planes[1].normal.y = t49;
    const float t52 = corners[0].y * t49;
    planes[1].normal.x = t50;
    planes[1].normal.z = t51;
    const float t53 = ppc::fmadds(corners[0].x, t50, t52);
    const float t54 = ppc::fmadds(t51, corners[0].z, t53);
    planes[1].distance = t54;
    planes[1].closestX = (t50 >= 0.0f) ? 1 : 0;
    planes[1].closestY = (t49 >= 0.0f) ? 1 : 0;
    planes[1].closestZ = (t51 >= 0.0f) ? 1 : 0;
    const float t55 = corners[1].x - corners[5].x;
    const float t56 = corners[6].z - corners[5].z;
    const float t57 = corners[1].z - corners[5].z;
    const float t58 = corners[6].x - corners[5].x;
    const float t59 = corners[6].y - corners[5].y;
    const float t60 = corners[1].y - corners[5].y;
    const float t61 = t55 * t56;
    const float t62 = t57 * t59;
    const float t63 = ppc::fmsubs(t57, t58, t61);
    const float t64 = t60 * t58;
    const float t65 = ppc::fmsubs(t60, t56, t62);
    const float t66 = t63 * t63;
    planes[2].normal.y = t63;
    const float t67 = ppc::fmsubs(t55, t59, t64);
    planes[2].normal.x = t65;
    const float t68 = ppc::fmadds(t65, t65, t66);
    planes[2].normal.z = t67;
    const float t69 = ppc::fmadds(t67, t67, t68);
    const float t70 = rwInvSqrt(t69);
    const float t71 = t70 * t63;
    const float t72 = t70 * t65;
    const float t73 = t70 * t67;
    planes[2].normal.y = t71;
    const float t74 = corners[1].y * t71;
    planes[2].normal.x = t72;
    planes[2].normal.z = t73;
    const float t75 = ppc::fmadds(corners[1].x, t72, t74);
    const float t76 = ppc::fmadds(t73, corners[1].z, t75);
    planes[2].distance = t76;
    planes[2].closestX = (t72 >= 0.0f) ? 1 : 0;
    planes[2].closestY = (t71 >= 0.0f) ? 1 : 0;
    planes[2].closestZ = (t73 >= 0.0f) ? 1 : 0;
    const float t77 = corners[4].x - corners[5].x;
    const float t78 = corners[4].z - corners[5].z;
    const float t79 = corners[4].y - corners[5].y;
    const float t80 = t57 * t77;
    const float t81 = t60 * t78;
    const float t82 = t55 * t79;
    const float t83 = ppc::fmsubs(t55, t78, t80);
    const float t84 = ppc::fmsubs(t57, t79, t81);
    const float t85 = ppc::fmsubs(t60, t77, t82);
    const float t86 = t83 * t83;
    planes[3].normal.y = t83;
    planes[3].normal.x = t84;
    planes[3].normal.z = t85;
    const float t87 = ppc::fmadds(t84, t84, t86);
    const float t88 = ppc::fmadds(t85, t85, t87);
    const float t89 = rwInvSqrt(t88);
    const float t90 = t89 * t83;
    const float t91 = t89 * t84;
    const float t92 = t89 * t85;
    planes[3].normal.y = t90;
    const float t93 = corners[1].y * t90;
    planes[3].normal.x = t91;
    planes[3].normal.z = t92;
    const float t94 = ppc::fmadds(corners[1].x, t91, t93);
    const float t95 = ppc::fmadds(t92, corners[1].z, t94);
    planes[3].distance = t95;
    planes[3].closestX = (t91 >= 0.0f) ? 1 : 0;
    planes[3].closestY = (t90 >= 0.0f) ? 1 : 0;
    const float t96 = -t71;
    const float t97 = -t72;
    planes[3].closestZ = (t92 >= 0.0f) ? 1 : 0;
    const float t98 = -t73;
    planes[4].normal.y = t96;
    const float t99 = corners[3].y * t96;
    planes[4].normal.x = t97;
    planes[4].normal.z = t98;
    const float t100 = ppc::fmadds(corners[3].x, t97, t99);
    const float t101 = ppc::fmadds(t98, corners[3].z, t100);
    planes[4].distance = t101;
    planes[4].closestX = (t97 >= 0.0f) ? 1 : 0;
    planes[4].closestY = (t96 >= 0.0f) ? 1 : 0;
    const float t102 = -t90;
    const float t103 = -t91;
    planes[4].closestZ = (t98 >= 0.0f) ? 1 : 0;
    const float t104 = -t92;
    planes[5].normal.y = t102;
    const float t105 = corners[3].y * t102;
    planes[5].normal.x = t103;
    planes[5].normal.z = t104;
    const float t106 = ppc::fmadds(corners[3].x, t103, t105);
    const float t107 = ppc::fmadds(t104, corners[3].z, t106);
    planes[5].distance = t107;
    planes[5].closestX = (t103 >= 0.0f) ? 1 : 0;
    planes[5].closestY = (t102 >= 0.0f) ? 1 : 0;
    planes[5].closestZ = (t104 >= 0.0f) ? 1 : 0;
}
}  // namespace

// 0x007471c8 _rwCameraSync_maybe (the perspective branch at 0x747938, the parallel one at 0x747234). DOTD: with the
// debug free-fly camera on (platform/sdl/freecam.h) a world camera's frustum follows the free camera's pose (the view
// matrix stays the game camera's: the device builds its own view from the pose).
void _rwCameraSync(RwCamera* camera) {
    const RwMatrix* ltm = FrameLtm(RwCameraGetFrame(camera));
    RwMatrix* view = &camera->viewMatrix;
    const bool perspective = camera->projectionType == rwPERSPECTIVE;
    // x: the right axis scaled by -0.5 / view window, the at axis by 0.5 - that times the offset (perspective) or minus
    // it (parallel).
    float scale = camera->recipViewWindow.x * -0.5f;  // TOC2 -0x341c
    float atScale = scale * camera->viewOffset.x;
    atScale = perspective ? 0.5f - atScale : -atScale;  // TOC2 -0x3418 0.5
    float vy = ppc::fmadds(scale, ltm->right.y, atScale * ltm->at.y);
    float vx = ppc::fmadds(scale, ltm->right.x, atScale * ltm->at.x);
    float vz = ppc::fmadds(scale, ltm->right.z, atScale * ltm->at.z);
    view->right.x = vx;
    view->at.x = vz;
    view->up.x = vy;
    view->pos.x = 0.5f - (atScale + ppc::fmadds(vz, ltm->pos.z, ppc::fmadds(vx, ltm->pos.x, vy * ltm->pos.y)));
    view->right.z = ltm->at.x;
    // y: the up axis, the at axis by 0.5 + scale * offset (perspective) or scale * offset (parallel).
    scale = camera->recipViewWindow.y * -0.5f;
    atScale = perspective ? ppc::fmadds(scale, camera->viewOffset.y, 0.5f) : scale * camera->viewOffset.y;
    vy = ppc::fmadds(scale, ltm->up.y, atScale * ltm->at.y);
    vz = ppc::fmadds(scale, ltm->up.z, atScale * ltm->at.z);
    vx = ppc::fmadds(scale, ltm->up.x, atScale * ltm->at.x);
    view->up.y = vy;
    view->at.y = vz;
    view->right.y = vx;
    view->pos.y = 0.5f - (atScale + ppc::fmadds(vz, ltm->pos.z, ppc::fmadds(vx, ltm->pos.x, vy * ltm->pos.y)));
    // z: the at axis.
    view->up.z = ltm->at.y;
    view->at.z = ltm->at.z;
    view->pos.z = ppc::fnmadds(ltm->pos.z, ltm->at.z, ppc::fmadds(ltm->pos.x, ltm->at.x, ltm->pos.y * ltm->at.y));
    RwMatrixOptimize(view, nullptr);
    RwMatrix freePose;
    if (dotd::platform::freecam::Enabled()) {
        freePose = RwDevice_CameraPose(camera);
        ltm = &freePose;
    }
    if (perspective) {
        CameraBuildPerspClipPlanes(camera, ltm);
    } else {
        CameraBuildParallelClipPlanes(camera, ltm);
    }
    RwBBoxCalculate(&camera->frustumBoundBox, camera->frustumCorners, 8);
}

// 0x00748720 RwCameraFrustumTestSphere. One lane of the AltiVec code (every operation is a splat, crt/vmx_ops.h): the
// sphere centre as (x, y, z, -1.0f) (vsel with the constant 0xa72710 / 0xa72720 mask), per plane the distance
// x nx + (y ny + (z nz + (d x -1 + 0))) by four vmaddfp; outside (0) when a distance is not <= the radius (vcmpgefp
// r >= dist, so a NaN distance is outside too), else boundary (1) when one is >= -radius (0 - r by vsubfp), else
// inside (2) (the constants 0xa72730 / 0xa72750, vand / vsel, stvewx of lane 0).
RwInt32 RwCameraFrustumTestSphere(const RwCamera* camera, const RwReal* sphere) {
    const float x = sphere[0];
    const float y = sphere[1];
    const float z = sphere[2];
    const float radius = sphere[3];
    const float minusOne = -1.0f;
    const float negRadius = vmx::Sub(0.0f, radius);
    uint32_t within = 0xffffffffu;
    uint32_t result = 2;  // 0xa72730
    for (const RwFrustumPlane& plane : camera->frustumPlanes) {
        const float distance = vmx::Madd(
            x, plane.normal.x,
            vmx::Madd(y, plane.normal.y, vmx::Madd(z, plane.normal.z, vmx::Madd(plane.distance, minusOne, 0.0f))));
        if (!vmx::CmpGe(radius, distance)) within = 0;
        if (vmx::CmpGe(distance, negRadius)) result = 1;  // 0xa72750
    }
    return static_cast<RwInt32>(within & result);
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

