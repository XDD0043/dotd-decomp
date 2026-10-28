// RwSList.cpp - _rwSList* and the engine memory functions. See RwSList.h.
#include "Renderware/rwcore/RwSList.h"

#include <cstdlib>
#if defined(_MSC_VER)
#include <malloc.h>
#endif

// The PS3's RW heap returns 16-byte aligned blocks (RwMatrix and the Rt2d objects holding one rely on
// it); the host heap is made to do the same.
#if defined(_MSC_VER)
void* RwMalloc(RwUInt32 size, RwUInt32 /*hint*/) { return _aligned_malloc(size == 0 ? 1 : size, 16); }

void RwFree(void* memory) { _aligned_free(memory); }

void* RwRealloc(void* memory, RwUInt32 size, RwUInt32 /*hint*/) {
    return _aligned_realloc(memory, size == 0 ? 1 : size, 16);
}
#else
void* RwMalloc(RwUInt32 size, RwUInt32 /*hint*/) { return std::malloc(size == 0 ? 1 : size); }  // 16-aligned (glibc x64, emscripten)

void RwFree(void* memory) { std::free(memory); }

void* RwRealloc(void* memory, RwUInt32 size, RwUInt32 /*hint*/) { return std::realloc(memory, size == 0 ? 1 : size); }
#endif

RwFreeList* RwFreeListCreateAndPreallocateSpace(RwInt32 entrySize, RwInt32 /*entriesPerBlock*/, RwInt32 alignment,
                                                RwInt32 /*numBlocksToPreallocate*/, RwFreeList* inPlace,
                                                RwUInt32 /*hint*/) {
    RwFreeList* freelist = inPlace != nullptr ? inPlace : new RwFreeList();
    freelist->entrySize = static_cast<RwUInt32>(entrySize);
    freelist->alignment = static_cast<RwUInt32>(alignment);
    return freelist;
}

RwBool RwFreeListDestroy(RwFreeList* freelist) {
    delete freelist;
    return 1;
}

void* RwFreeListAlloc(RwFreeList* freelist, RwUInt32 hint) { return RwMalloc(freelist->entrySize, hint); }

RwFreeList* RwFreeListFree(RwFreeList* freelist, void* entry) {
    RwFree(entry);
    return freelist;
}

// 0x00758000 _rwSListCreate
RwSList* _rwSListCreate(RwInt32 entrySize, RwUInt32 /*hint*/) {
    RwSList* sList = static_cast<RwSList*>(RwMalloc(sizeof(RwSList), 0x30000));  // the RwSList free list
    sList->entrySize = entrySize;
    sList->listElements = nullptr;
    sList->numElementsFilled = 0;
    sList->numElementsAlloced = 0;
    return sList;
}

// 0x00757ea8 _rwSListCreatePreallocated
RwSList* _rwSListCreatePreallocated(RwInt32 entrySize, RwInt32 numElements, RwUInt32 hint) {
    RwSList* sList = static_cast<RwSList*>(RwMalloc(sizeof(RwSList), 0x30000));
    sList->numElementsFilled = 0;
    sList->numElementsAlloced = numElements;
    sList->entrySize = entrySize;
    if (numElements != 0) {
        sList->listElements = static_cast<RwUInt8*>(
            RwMalloc(static_cast<RwUInt32>(entrySize * numElements), hint | 0x1000000));
        return sList;
    }
    sList->listElements = nullptr;
    return sList;
}

// 0x007579a8 _rwSListDestroy
RwBool _rwSListDestroy(RwSList* sList) {
    if (sList->listElements != nullptr && sList->numElementsAlloced != 0) {
        RwFree(sList->listElements);
        sList->numElementsAlloced = 0;
        sList->listElements = nullptr;
    }
    RwFree(sList);
    return 1;
}

// 0x00757ac8 _rwSListToArray
void* _rwSListToArray(RwSList* sList) {
    void* array;
    if (sList->numElementsFilled == 0) {
        array = nullptr;
        if (sList->listElements != nullptr) {
            RwFree(sList->listElements);
            sList->listElements = nullptr;
        }
    } else {
        array = sList->listElements;
    }
    RwFree(sList);
    return array;
}

// 0x00757980 _rwSListGetArray
void* _rwSListGetArray(RwSList* sList) {
    return sList->numElementsFilled != 0 ? sList->listElements : nullptr;
}

// 0x00757ab8 _rwSListGetNumEntries
RwInt32 _rwSListGetNumEntries(const RwSList* sList) { return sList->numElementsFilled; }

// 0x00757ba8 _rwSListGetEntry
void* _rwSListGetEntry(RwSList* sList, RwInt32 index) {
    return sList->listElements + index * sList->entrySize;
}

// 0x00757bc8 _rwSListGetEnd
void* _rwSListGetEnd(RwSList* sList) {
    return sList->listElements + sList->entrySize * sList->numElementsFilled;
}

// 0x00757da0 _rwSListGetNewEntry
void* _rwSListGetNewEntry(RwSList* sList, RwUInt32 hint) {
    RwInt32 alloced = sList->numElementsAlloced;
    RwInt32 filled = sList->numElementsFilled;
    RwInt32 newAlloced = alloced + 1;
    if (alloced <= filled) {
        if (3 < alloced) newAlloced = alloced + (alloced >> 2);
        void* grown = RwRealloc(sList->listElements, static_cast<RwUInt32>(newAlloced * sList->entrySize), hint);
        if (grown == nullptr) return nullptr;  // _rwerror(0x80000013) + RwErrorSet
        filled = sList->numElementsFilled;
        sList->numElementsAlloced = newAlloced;
        sList->listElements = static_cast<RwUInt8*>(grown);
    }
    sList->numElementsFilled = filled + 1;
    return sList->listElements + filled * sList->entrySize;
}

// 0x00757c88 _rwSListGetNewEntries
void* _rwSListGetNewEntries(RwSList* sList, RwInt32 num, RwUInt32 hint) {
    const RwInt32 alloced = sList->numElementsAlloced;
    RwInt32 filled = sList->numElementsFilled;
    const RwInt32 newAlloced = num + alloced + alloced / 4;  // srawi + addze: rounds toward zero
    if (alloced < num + filled) {
        void* grown = RwRealloc(sList->listElements, static_cast<RwUInt32>(newAlloced * sList->entrySize), hint);
        if (grown == nullptr) return nullptr;  // _rwerror(0x80000013) + RwErrorSet
        filled = sList->numElementsFilled;
        sList->numElementsAlloced = newAlloced;
        sList->listElements = static_cast<RwUInt8*>(grown);
    }
    sList->numElementsFilled = num + filled;
    return sList->listElements + filled * sList->entrySize;
}
