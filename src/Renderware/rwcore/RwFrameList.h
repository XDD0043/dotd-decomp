// RwFrameList.h - RenderWare 3.7 frame lists (core/src/babinfrm.c) and the frame plugin chunks, as the
// PS3 library reads them: _rwFrameListStreamRead 0x745280, _rwPluginRegistryReadDataChunks 0x75d660 (for
// the frame registry), RwFrameAddChildNoUpdate 0x74c300. Frame plugins with a stream reader: RpHAnim
// (0x11e); every other plugin chunk is skipped by its length, as RW does for unregistered ones.
#pragma once
#include "Renderware/rwcore/RwTypes.h"

struct RwFrame;
struct RwStream;

// rwFrameList (babinfrm.h).
struct rwFrameList {
    RwFrame** frames;   // +0x00 RwMalloc(numFrames * 4)
    RwInt32 numFrames;  // +0x04
};

// 0x00745280 _rwFrameListStreamRead, after the caller's RwStreamFindChunk(rwID_FRAMELIST): the struct
// chunk (count, then 0x38 bytes per frame: right, up, at, pos, parent index, flags), a frame each with its
// matrix, linked to its parent, then each frame's extension chunk. Null on failure.
rwFrameList* _rwFrameListStreamRead(RwStream* stream, rwFrameList* frameList);
// _rwFrameListDeinitialize: frees the array (not the frames).
rwFrameList* _rwFrameListDeinitialize(rwFrameList* frameList);
// 0x0074c300 RwFrameAddChildNoUpdate: child at the head of parent's children, its root parent's. A child
// that has a parent leaves it first (RwFrameRemoveChild).
RwFrame* RwFrameAddChildNoUpdate(RwFrame* parent, RwFrame* child);
// RwFrameRemoveChild (inlined where the game uses it, e.g. CSGBranch_RemoveChild_maybe 0xcdb30; baframe.c):
// the frame leaves its parent's child list, becomes the root of its own subtree and is marked dirty.
RwFrame* RwFrameRemoveChild(RwFrame* child);
// 0x0074c6a0 RwFrameAddChild: RwFrameAddChildNoUpdate, then the child's hierarchy is marked dirty
// (RwFrameUpdateObjects). A frame that already had a parent is removed from it first.
RwFrame* RwFrameAddChild(RwFrame* parent, RwFrame* child);
// 0x0074a438 RwFrameUpdateObjects: the root's private flags |= 3 (hierarchy needs an LTM and object sync),
// the frame's |= 0xc (its subtree does). By design (not a stub): the PS3 also puts the root on the engine's dirty frame
// list (RWEngineInstance + 0xbc) when it was clean; its only reader is the camera update (RwCameraBeginUpdate
// syncs the LTMs), and natively RwFrameGetLTM computes them on demand, so the list is not kept.
RwFrame* RwFrameUpdateObjects(RwFrame* frame);
// 0x0074bc80 RwFrameDestroyHierarchy: every descendant destroyed (RwFrameDestroyRecurse_maybe 0x74b5b0 is the same walk
// unrolled), then the frame; the frame is not taken out of its parent's child list (the PS3 does not).
RwBool RwFrameDestroyHierarchy(RwFrame* frame);
