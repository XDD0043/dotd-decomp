// RpHAnim.h - RenderWare 3.7 RpHAnim (hierarchical animation): the frame plugin (an id and a hierarchy per frame),
// the hierarchy the plugin's stream reader builds, the standard key frame scheme and the hierarchy API. PS3 library
// code (TOC 0xc25974): _rpHAnimOpen_maybe 0x6e8070, HAnimStreamRead_maybe 0x6e7d20, RpHAnimFrameGetHierarchy
// 0x6e62f8, RpHAnimFrameGetID 0x6e6330, HAnimFrameConstructor_maybe 0x6e6190 and the functions below. Layouts are
// RW 3.7's rphanim.h ones (PS3 offsets in the comments; the x64 build has 8-byte pointers).
// Animation checkpoint, step 2: the scheme 1 callbacks (apply 0x6e84d8, interpolate 0x6e8e48, blend 0x6e89c0, add 0x6e86c8, mulrecip
// 0x6e85d8) and RpHAnimHierarchyUpdateMatrices 0x6e63b8.
#pragma once
#include "Renderware/rtanim/RtAnim.h"
#include "Renderware/rwcore/RwTypes.h"

struct RwFrame;
struct RwStream;

// RpHAnimHierarchyFlag (rphanim.h): the stream's flags word and RpHAnimHierarchyCreate's `flags`.
enum : RwInt32 {
    rpHANIMHIERARCHYSUBHIERARCHY = 0x01,
    rpHANIMHIERARCHYNOMATRICES = 0x02,
    rpHANIMHIERARCHYUPDATEMODELLINGMATRICES = 0x1000,
    rpHANIMHIERARCHYUPDATELTMS = 0x2000,
    rpHANIMHIERARCHYLOCALSPACEMATRICES = 0x4000,
};
// RpHAnimNodeInfo flags.
enum : RwInt32 {
    rpHANIMPOPPARENTMATRIX = 0x01,
    rpHANIMPUSHPARENTMATRIX = 0x02,
};

// RpHAnimNodeInfo (PS3 0x10 bytes).
struct RpHAnimNodeInfo {
    RwInt32 nodeID;     // +0x00
    RwInt32 nodeIndex;  // +0x04
    RwInt32 flags;      // +0x08 rpHANIMPUSHPARENTMATRIX 2, rpHANIMPOPPARENTMATRIX 1
    RwFrame* pFrame;    // +0x0c set when the hierarchy is attached (RpHAnimHierarchyAttach); the stream leaves it null
};
DOTD_ASSERT_SIZE(RpHAnimNodeInfo, 0x10);

// RpHAnimHierarchy (PS3 0x24 bytes, from RW's hierarchy free list).
struct RpHAnimHierarchy {
    RwInt32 flags;                       // +0x00 rpHANIMHIERARCHYNOMATRICES 2, ...
    RwInt32 numNodes;                    // +0x04
    RwMatrix* pMatrixArray;              // +0x08 numNodes matrices, 16-byte aligned (none with NOMATRICES)
    void* pMatrixArrayUnaligned;         // +0x0c the allocation
    RpHAnimNodeInfo* pNodeInfo;          // +0x10
    RwFrame* parentFrame;                // +0x14 the frame whose plugin data streamed it
    RpHAnimHierarchy* parentHierarchy;   // +0x18 itself
    RwInt32 rootParentOffset;            // +0x1c
    RtAnimInterpolator* currentAnim;     // +0x20 RtAnimInterpolatorCreate(numNodes, maxKeyFrameSize)
};
DOTD_ASSERT_SIZE(RpHAnimHierarchy, 0x24);
DOTD_ASSERT_OFFSET(RpHAnimHierarchy, pNodeInfo, 0x10);
DOTD_ASSERT_OFFSET(RpHAnimHierarchy, currentAnim, 0x20);

// RtQuat (rtquat.h): imaginary part, then the real part.
struct RtQuat {
    RwV3d imag;
    RwReal real;
};

// RpHAnimStdKeyFrame (rphanim.h; the scheme 1 key frame): PS3 0x24 bytes. The stream stores `time, quaternion,
// translation` and the previous key frame as a byte offset into the array.
struct RpHAnimStdKeyFrame {
    RpHAnimStdKeyFrame* prevFrame;  // +0x00 the previous key frame of the same node (earlier in the array)
    RwReal time;                    // +0x04
    RtQuat q;                       // +0x08
    RwV3d t;                        // +0x18
};
DOTD_ASSERT_SIZE(RpHAnimStdKeyFrame, 0x24);

// RpHAnimInterpFrame: what the interpolator keeps per node (the header RtAnimInterpFrameHeader is the pair of key
// frames the node is between).
struct RpHAnimInterpFrame {
    RpHAnimStdKeyFrame* keyFrame1;  // +0x00
    RpHAnimStdKeyFrame* keyFrame2;  // +0x04
    RtQuat q;                       // +0x08
    RwV3d t;                        // +0x18
};
DOTD_ASSERT_SIZE(RpHAnimInterpFrame, 0x24);

// 0x006e8070 _rpHAnimOpen_maybe: registers the standard scheme (type 1: key frame and interpolated frame 0x24, custom
// data 0, the callbacks below and StreamRead 0x6e88c0). The hierarchy free list is the host heap.
RwBool RpHAnimPluginOpen();
// 0x0071f5c0 RtCompressedKeyFrameRegister_maybe: scheme 2 (key frame 0x18, custom data 0x18). Not read by any level
// (c25_anim_scan.py over all levels: every animation is scheme 1). STUB(C2.9): all callbacks are null and StreamRead
// is a stub that does nothing.
RwBool RtCompressedKeyFrameRegister();

// The scheme 1 callbacks (rphanim.h names), ported operation for operation (the slerp inlines Dinkumware's acosf / sinf).
// 0x006e84d8 RpHAnimKeyFrameApply (RpHAnimKeyFrameApply): the interpolated frame's quaternion and translation into
// the matrix (flags 3, the pads untouched).
void RpHAnimKeyFrameApply(void* matrix, void* voidIFrame);
// 0x006e8e48 RpHAnimKeyFrameInterpolate: between two key frames at `time` (slerp, a lerp at dot >= 0.999; the second
// key frame's quaternion is negated in place when the dot product is negative).
void RpHAnimKeyFrameInterpolate(void* voidOut, void* voidIn1, void* voidIn2, RwReal time, void* customData,
                                RwInt32 nodeIndex);
// 0x006e89c0 RpHAnimKeyFrameBlend: the same between two interpolated frames by alpha.
void RpHAnimKeyFrameBlend(void* voidOut, void* voidIn1, void* voidIn2, RwReal alpha);
// 0x006e86c8 RpHAnimKeyFrameAdd (RpHAnimKeyFrameAdd)
void RpHAnimKeyFrameAdd(void* voidOut, void* voidIn1, void* voidIn2);
// 0x006e85d8 RpHAnimKeyFrameMulRecip (RpHAnimKeyFrameMulRecip)
void RpHAnimKeyFrameMulRecip(void* voidFrame, void* voidStart);

// 0x006e63b8 RpHAnimHierarchyUpdateMatrices: every node's interpolated frame through the apply callback, times its
// parent (the push/pop stack of the node flags) into the matrix array; the root's parent is the identity (local space),
// the parent frame's LTM, or the parent hierarchy's matrix (sub-hierarchy). Attached frames get the modelling matrix /
// LTM as the flags say. STUB(C2.9): the NOMATRICES variant (no hierarchy of the game files has the flag). 1.
RwBool RpHAnimHierarchyUpdateMatrices(RpHAnimHierarchy* hierarchy);

// 0x006e88c0 RpHAnimStdKeyFrameStreamRead: for every key frame the time, quaternion and translation (8 reals) and the
// previous frame as a byte offset, which becomes a pointer (pFrames + offset / 0x24 * 0x24). Null on a short read, else
// the animation.
RtAnimAnimation* RpHAnimStdKeyFrameStreamRead(RwStream* stream, RtAnimAnimation* animation);

// 0x006e7510 RpHAnimHierarchyCreate: numNodes nodes (the ids, and the flags if given, from the arrays; the index the
// position), the matrix array unless NOMATRICES, the interpolator, no frame attached.
RpHAnimHierarchy* RpHAnimHierarchyCreate(RwInt32 numNodes, const RwInt32* nodeFlags, const RwInt32* nodeIDs,
                                         RwInt32 flags, RwInt32 maxKeyFrameSize);
// 0x006e7840 RpHAnimHierarchyCreateFromHierarchy: a hierarchy with the same nodes (id, index, flags), none attached.
RpHAnimHierarchy* RpHAnimHierarchyCreateFromHierarchy(const RpHAnimHierarchy* hierarchy, RwInt32 flags,
                                                      RwInt32 maxKeyFrameSize);
// 0x006e8170 RpHAnimHierarchyAttach: every node whose id equals a frame's hanim id (the hierarchy's parent frame, then
// all its descendants) gets that frame in pFrame; the frames' objects are updated.
RpHAnimHierarchy* RpHAnimHierarchyAttach(RpHAnimHierarchy* hierarchy);
// 0x006e8248 RpHAnimHierarchyAttachFrameIndex: the same for the one node `nodeIndex`'s id, only when it is the parent
// frame's id first (then in the descendants).
RpHAnimHierarchy* RpHAnimHierarchyAttachFrameIndex(RpHAnimHierarchy* hierarchy, RwInt32 nodeIndex);
// 0x006e6240 RpHAnimHierarchyDetach: every node's pFrame cleared.
RpHAnimHierarchy* RpHAnimHierarchyDetach(RpHAnimHierarchy* hierarchy);
// 0x006e62b0 RpHAnimFrameSetHierarchy: the frame's plugin hierarchy replaced (the old one loses its parent frame, the
// new one gets this frame). 1.
RwBool RpHAnimFrameSetHierarchy(RwFrame* frame, RpHAnimHierarchy* hierarchy);
// 0x006e6350 RpHAnimIDGetIndex: the index of the node with `id`, or -1.
RwInt32 RpHAnimIDGetIndex(const RpHAnimHierarchy* hierarchy, RwInt32 id);
// 0x006e7920 HAnimFrameCopyCB_maybe (the frame plugin's copy callback, RwFrameClone / RpClumpClone): the id copied; a
// hierarchy that is not a sub-hierarchy is recreated (same nodes, none attached, the interpolator's max key frame size).
void HAnimFrameCopy(RwFrame* dstFrame, const RwFrame* srcFrame);

// 0x006e7d20 HAnimStreamRead_maybe (the frame plugin's stream reader, plugin id 0x11e): version 0x100, the
// frame's id, the node count; with nodes, the flags, the key frame size and the nodes (id, index, flags)
// into a new hierarchy owned by the frame. Null on a short read or another version.
RwStream* HAnimStreamRead(RwStream* stream, RwInt32 length, RwFrame* frame);
// 0x006e8330 HAnimFrameDestructor_maybe (the frame plugin's destructor, run by the frame's _rwPluginRegistryDeInitObject):
// a hierarchy on the frame has every node's frame cleared; the frame that streamed it (parentFrame) destroys it (the
// matrix array unless rpHANIMHIERARCHYNOMATRICES and the node array, unless a sub-hierarchy; the interpolator; the
// hierarchy) and clears the hierarchy pointer of that frame. Then the frame's hierarchy is null and its id -1.
void HAnimFrameDestructor(RwFrame* frame);
// 0x006e62f8 RpHAnimFrameGetHierarchy
RpHAnimHierarchy* RpHAnimFrameGetHierarchy(RwFrame* frame);
// 0x006e6330 RpHAnimFrameGetID
RwInt32 RpHAnimFrameGetID(RwFrame* frame);
