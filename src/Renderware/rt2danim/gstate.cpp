// gstate.cpp - RW 3.7 tool/2danim/gstate.c (0x6f7c08-0x6f7f40): the toolkit's free lists and globals,
// ported from the PS3 library code. See Rt2dAnim.h.
#include "Renderware/rt2danim/Rt2dAnimPrivate.h"

RwFreeList* g_rt2dAnimFreeLists[kRt2dAnimFreeListCount] = {};
RwBool g_rt2dAnimOpenCalled = 0;
Rt2dAnimOnEndReachedCallBack g_rt2dAnimOnEndReachedCallBack = nullptr;
RwInt32 g_rt2dMessageQueueDefaultSize = 0x40;

namespace {
// 0x00c458a8 / 0x00c458ac: the free-list block size and preallocated block count (EBOOT data 0x14, 1).
RwInt32 g_freeListBlockSize = 0x14;
RwInt32 g_freeListPreallocBlocks = 1;

struct FreeListSpec {
    RwInt32 entrySize;  // native sizeof (the PS3 size is in Rt2dAnimPrivate.h)
    RwUInt32 hint;
};
}  // namespace

// 0x006f7c08 Rt2dAnimSetFreeListCreateParams_maybe
void Rt2dAnimSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
    g_freeListBlockSize = blockSize;
    g_freeListPreallocBlocks = numBlocksToPrealloc;
}

// 0x006f7c18 _rt2dFreeListsDestroy_maybe (Rt2dAnimClose). The PS3 keeps _rt2dAnimOpenCalled set.
RwBool Rt2dAnimClose() {
    for (RwFreeList*& freeList : g_rt2dAnimFreeLists) {
        if (freeList != nullptr) RwFreeListDestroy(freeList);
        freeList = nullptr;
    }
    return 1;
}

// 0x006f7cf0 _rt2dFreeListsCreate_maybe (Rt2dAnimOpen): RwFreeListCreateAndPreallocateSpace(size,
// blockSize, 4, preallocBlocks, &list, 0x40000 | hint) for the eleven lists, then _rt2dAnimOpenCalled = 1.
// The PS3 lists live in place in the globals block; here each is its own RwFreeList (RwFreeListDestroy
// frees the struct), which the toolkit cannot tell apart. The PS3 returns the last list's address in r3
// (never checked); here TRUE.
RwBool Rt2dAnimOpen() {
    const FreeListSpec specs[kRt2dAnimFreeListCount] = {
        {static_cast<RwInt32>(sizeof(Rt2dAnim)), 0x401a9},
        {static_cast<RwInt32>(sizeof(Rt2dButton)), 0x401a9},
        {static_cast<RwInt32>(sizeof(Rt2dMaestro)), 0x401b1},
        {static_cast<RwInt32>(sizeof(Rt2dStringLabel)), 0x401a9},
        {static_cast<RwInt32>(sizeof(Rt2dMessage)), 0x401a9},
        {static_cast<RwInt32>(sizeof(Rt2dMessageQueue)), 0x401a9},
        {static_cast<RwInt32>(sizeof(Rt2dAnimObjectUpdate)), 0x401a9},
        {static_cast<RwInt32>(sizeof(Rt2dKeyFrameList)), 0x401b0},
        {static_cast<RwInt32>(sizeof(Rt2dAnimProps)), 0x401a9},
        {static_cast<RwInt32>(sizeof(Rt2dCelList)), 0x401a9},
        {static_cast<RwInt32>(sizeof(Rt2dCel)), 0x401a9},
    };
    for (int32_t i = 0; i < kRt2dAnimFreeListCount; ++i) {
        g_rt2dAnimFreeLists[i] = RwFreeListCreateAndPreallocateSpace(
            specs[i].entrySize, g_freeListBlockSize, 4, g_freeListPreallocBlocks, nullptr, specs[i].hint);
    }
    g_rt2dAnimOpenCalled = 1;
    return 1;
}

// 0x006f7f40 KStub_Nop_6f7f40 (_rt2dApplyMouseState): the PS3 build's body is empty.
void _rt2dApplyMouseState(Rt2dMaestro* /*maestro*/, Rt2dMaestroMouseState* /*mouseState*/) {}
