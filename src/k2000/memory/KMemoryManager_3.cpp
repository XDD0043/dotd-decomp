// KMemoryManager_3.cpp - reconstructed original translation unit: 0x52970-0x534f0 (GAME_TOC1, main_toc1), 28 functions, 16 live.
// Primary owner: KMemoryManager (not a registered class)
// Other owners: Mem (5), MemHeap (2), Sysutil (2), Thread (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x52970  KMemoryManager_DumpBlockMapToFile_maybe
//   [ ] 0x52a18  KMemoryManager_FreeFromPool_maybe  [dead]
//   [ ] 0x52a58  MemHeap_AllocFromPoolWithFallback_maybe
//   [ ] 0x52b58  FUN_00052b58  [dead]
//   [ ] 0x52b88  KMemoryManager_InitHeap_maybe  [dead]
//   [ ] 0x52c10  KMemoryManager_ReleaseHeap_maybe  [dead]
//   [ ] 0x52c50  KMemoryManager_Destructor_2_maybe  [dead]
//   [ ] 0x52cc0  KMemoryManager_Construct_maybe  [dead]
//   [ ] 0x52d30  FUN_00052d30  [dead]
//   [ ] 0x52d50  KMemoryManager_Construct_2_maybe  [dead]
//   [ ] 0x52dc0  KMemoryManager_DeletingDestructor_maybe
//   [ ] 0x52e48  KMemoryManager_Destructor_maybe
//   [ ] 0x52eb8  KMemoryManager_GetLargestFreeBlockSize_maybe
//   [ ] 0x52f20  FUN_00052f20  [dead]
//   [ ] 0x52f28  FUN_00052f28  [dead]
//   [ ] 0x52f30  KMemoryManager_LinearAlloc_maybe
//   [x] 0x52fb8  Mem_FreeAligned16
//   [ ] 0x52ff0  KMemoryManager_FreeLinearBuffer_maybe
//   [ ] 0x53040  KMemoryManager_FreeBlock_maybe  [dead]
//   [x] 0x53098  Mem_ReallocateAligned
//   [x] 0x53190  Mem_ReallocAligned16
//   [x] 0x53198  Mem_AllocAligned16
//   [x] 0x531f8  Mem_CallocAligned16
//   [ ] 0x53280  KMemoryManager_InitLinearBuffer_maybe  [dead]
//   [ ] 0x53300  MemHeap_Realloc_maybe
//   [x] 0x53460  Thread_SleepMs_maybe
//   [x] 0x53498  Sysutil_PollCallbacks
//   [x] 0x534c8  Thread_YieldDuringLoad
#include "k2000/memory/Mem.h"

#include <cstdlib>
#include <cstring>

#include "platform/cell/sys_thread.h"
#include "platform/cell/sysutil.h"

// Block layout. The original keeps {u32 total size, u32 alignment} at the malloc'd start and the raw
// pointer in the 4 bytes below the aligned pointer. Host pointers can be 8 bytes, so the header here
// is {size_t total, size_t alignment} and the back pointer is pointer-sized; the behaviour is the same.
namespace {
struct BlockHeader {
    size_t total;      // bytes malloc'd, header included
    size_t alignment;  // requested alignment
};

void* PlaceAligned(void* raw, size_t total, size_t alignment) {
    const uintptr_t base = reinterpret_cast<uintptr_t>(raw) + sizeof(BlockHeader) + sizeof(void*);
    const uintptr_t aligned = (base + (alignment - 1)) & ~static_cast<uintptr_t>(alignment - 1);
    BlockHeader* header = static_cast<BlockHeader*>(raw);
    header->total = total;
    header->alignment = alignment;
    std::memcpy(reinterpret_cast<void*>(aligned - sizeof(void*)), &raw, sizeof(void*));
    return reinterpret_cast<void*>(aligned);
}

void* RawOf(void* block) {
    void* raw;
    std::memcpy(&raw, static_cast<char*>(block) - sizeof(void*), sizeof(void*));
    return raw;
}
}  // namespace

// 0x00053198 Mem_AllocAligned16
void* Mem_AllocAligned16(uint32_t size) {
    const size_t total = size + sizeof(BlockHeader) + sizeof(void*) + 15;
    void* raw = std::malloc(total);
    return PlaceAligned(raw, total, 16);
}

// 0x000531f8 Mem_CallocAligned16
void* Mem_CallocAligned16(uint32_t count, uint32_t size) {
    const uint32_t bytes = count * size;  // 32-bit product, as on the PS3
    void* block = Mem_AllocAligned16(bytes);
    std::memset(block, 0, bytes);
    return block;
}

// 0x00053098 Mem_ReallocateAligned
void* Mem_ReallocateAligned(void* block, uint32_t size, uint32_t alignment) {
    const size_t align = (alignment + 3u) & ~3u;
    const size_t total = size + sizeof(BlockHeader) + sizeof(void*) + align;
    void* raw = std::malloc(total);
    void* moved = PlaceAligned(raw, total, align);
    if (block != nullptr) {
        void* oldRaw = RawOf(block);
        // The original copies min(size, bytes from the old pointer to the end of the old malloc block),
        // so it can copy a little past the old requested size (still inside the old block).
        const size_t available = static_cast<BlockHeader*>(oldRaw)->total -
                                 static_cast<size_t>(static_cast<char*>(block) - static_cast<char*>(oldRaw));
        std::memcpy(moved, block, available < size ? available : size);
        std::free(oldRaw);
    }
    return moved;
}

// 0x00053190 Mem_ReallocAligned16
void* Mem_ReallocAligned16(void* block, uint32_t size) { return Mem_ReallocateAligned(block, size, 16); }

// 0x00052fb8 Mem_FreeAligned16
void Mem_FreeAligned16(void* block) {
    if (block != nullptr) std::free(RawOf(block));
}

// 0x00053460 Thread_SleepMs_maybe
void Thread_SleepMs(int32_t ms) {
    if (ms != 0) Sys_UsleepMs(ms);
}

// 0x00053498 Sysutil_PollCallbacks
void Sysutil_PollCallbacks(int32_t /*notInGameplay*/) {
    cellSysutilCheckCallback();
    sys_ppu_thread_yield();
}

// 0x000534c8 Thread_YieldDuringLoad (was Sysutil_PollDuringLoad_maybe; it only yields)
void Thread_YieldDuringLoad(int32_t /*unused*/) { sys_ppu_thread_yield(); }
