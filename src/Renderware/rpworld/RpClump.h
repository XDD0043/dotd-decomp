// RpClump.h - RenderWare 3.7 clumps as RpTeamStreamRead reads them (the team players' hierarchy frames): the frame
// list, the geometry list and the extension. PS3 library code (TOC 0xc25974): RpClumpStreamRead 0x69f4a0,
// RpClumpDestroy 0x69d748, RwFrameDestroyHierarchy 0x74bc80. RW 3.7 source: baclump.c.
//
// Every clump in the game files has no atomics, lights or cameras (the team players' clumps: two frames and an empty
// geometry list); the readers of those lists (ClumpAtomicStreamRead 0x69f0d8 with a frame list, RpLightStreamRead,
// RwCameraStreamRead) are STUB(C2.9): a clump that has one fails to read, as a short read would.
#pragma once
#include <cstdint>

struct RwFrame;
struct RwStream;

struct RpClump {
    // +0x04 the frame list's first frame (the clump's root frame), or null.
    RwFrame* frame = nullptr;
};

// 0x0069f4a0 RpClumpStreamRead after RwStreamFindChunk(0x10): the struct chunk (three counts), the frame list (the
// first frame is the clump's), the geometry list, the atomics, lights and cameras, then the extension. Null on failure.
RpClump* RpClumpStreamRead(RwStream* stream);

// 0x0069d748 RpClumpDestroy: the clump's frame hierarchy (RwFrameDestroyHierarchy) unless it was taken away
// (RpTeamStreamRead sets the frame to null first), then the clump.
int32_t RpClumpDestroy(RpClump* clump);
