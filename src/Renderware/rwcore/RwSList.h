// RwSList.h - RenderWare's internal resizable array (_rwSList*), and the engine memory functions it and
// the toolkits allocate through. Ported from the PS3 library code (TOC 0xc25974).
//
// The PS3 reaches memory through the engine's memory function table (RWEngineInstance +0x108 malloc,
// +0x10c free, +0x110 realloc, +0x118 free-list alloc, +0x11c free-list free). Here they are the host
// heap: what the game observes is the same (fresh blocks, contents kept on growth), only the addresses
// differ. Entry sizes are the native sizeof of the element type, never the PS3 byte counts.
#pragma once
#include <cstdint>

#include "Renderware/rwcore/RwTypes.h"

// RwMalloc / RwFree / RwRealloc (the hint, a chunk id with flags, only feeds RW's memory statistics).
void* RwMalloc(RwUInt32 size, RwUInt32 hint);
void RwFree(void* memory);
void* RwRealloc(void* memory, RwUInt32 size, RwUInt32 hint);

// RwFreeList: fixed-size blocks. RwFreeListCreateAndPreallocateSpace (0x75af90) only sets up the pool;
// the toolkits' observable behaviour is alloc/free, so the pool is the host heap with the entry size.
struct RwFreeList {
    RwUInt32 entrySize;
    RwUInt32 alignment;
};
// 0x0075af90 RwFreeListCreateAndPreallocateSpace (entrySize native; entriesPerBlock/alignment/
// numBlocksToPreallocate/fileCreate/hint only shape the PS3 pool).
RwFreeList* RwFreeListCreateAndPreallocateSpace(RwInt32 entrySize, RwInt32 entriesPerBlock, RwInt32 alignment,
                                                RwInt32 numBlocksToPreallocate, RwFreeList* inPlace,
                                                RwUInt32 hint);
// 0x0075b148 RwFreeListDestroy
RwBool RwFreeListDestroy(RwFreeList* freelist);
// RWEngineInstance +0x118: a block of entrySize bytes (not cleared, like RW's free lists).
void* RwFreeListAlloc(RwFreeList* freelist, RwUInt32 hint);
// RWEngineInstance +0x11c
RwFreeList* RwFreeListFree(RwFreeList* freelist, void* entry);

// 0x00758000 _rwSListCreate: an empty list (no storage) of entries of entrySize bytes.
RwSList* _rwSListCreate(RwInt32 entrySize, RwUInt32 hint);
// 0x00757ea8 _rwSListCreatePreallocated: numElements entries allocated, none filled.
RwSList* _rwSListCreatePreallocated(RwInt32 entrySize, RwInt32 numElements, RwUInt32 hint);
// 0x007579a8 _rwSListDestroy: frees the storage and the list.
RwBool _rwSListDestroy(RwSList* sList);
// 0x00757ac8 _rwSListToArray: frees the list and returns its storage (null when empty; then freed).
void* _rwSListToArray(RwSList* sList);
// 0x00757980 _rwSListGetArray: the storage, or null when no entry is filled.
void* _rwSListGetArray(RwSList* sList);
// 0x00757ab8 _rwSListGetNumEntries
RwInt32 _rwSListGetNumEntries(const RwSList* sList);
// 0x00757ba8 _rwSListGetEntry: the address of entry index (no range check).
void* _rwSListGetEntry(RwSList* sList, RwInt32 index);
// 0x00757bc8 _rwSListGetEnd: one past the last filled entry.
void* _rwSListGetEnd(RwSList* sList);
// 0x00757da0 _rwSListGetNewEntry: appends one entry (grows by max(1, alloced/4) when full; the PS3 grows
// to alloced + 1 below 4 entries, else alloced + alloced/4); null when the reallocation fails.
void* _rwSListGetNewEntry(RwSList* sList, RwUInt32 hint);
// 0x00757c88 _rwSListGetNewEntries: appends num entries (grows to num + alloced + alloced/4 when needed)
// and returns the first new one.
void* _rwSListGetNewEntries(RwSList* sList, RwInt32 num, RwUInt32 hint);

// Typed helpers for the ports (no PS3 counterpart; they only cast).
template <typename T>
inline T* RwSListArray(RwSList* sList) {
    return static_cast<T*>(_rwSListGetArray(sList));
}
template <typename T>
inline T* RwSListEnd(RwSList* sList) {
    return static_cast<T*>(_rwSListGetEnd(sList));
}
template <typename T>
inline T* RwSListEntry(RwSList* sList, RwInt32 index) {
    return static_cast<T*>(_rwSListGetEntry(sList, index));
}
