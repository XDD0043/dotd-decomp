// Mem.h - the engine's aligned heap helpers (KMemoryManager_3.cpp, 0x52970-0x534f0).
// All of them sit on libc malloc/free (the PS3's dlmalloc). KMemoryManager itself is never
// constructed in the PS3 build (live global 0xc5b844 = 0), so only these wrappers are used.
#pragma once
#include <cstddef>
#include <cstdint>

// 0x00053198 Mem_AllocAligned16: 16-byte aligned block, freed with Mem_FreeAligned16.
void* Mem_AllocAligned16(uint32_t size);
// 0x000531f8 Mem_CallocAligned16: count * size bytes, zeroed.
void* Mem_CallocAligned16(uint32_t count, uint32_t size);
// 0x00053098 Mem_ReallocateAligned: always moves; copies min(new size, bytes after the old pointer).
void* Mem_ReallocateAligned(void* block, uint32_t size, uint32_t alignment);
// 0x00053190 Mem_ReallocAligned16
void* Mem_ReallocAligned16(void* block, uint32_t size);
// 0x00052fb8 Mem_FreeAligned16
void Mem_FreeAligned16(void* block);

// 0x00053460 Thread_SleepMs_maybe: sleeps unless ms is 0.
void Thread_SleepMs(int32_t ms);
// 0x00058d40 Sys_UsleepMs_maybe: sys_timer_usleep(ms * 1000).
void Sys_UsleepMs(int32_t ms);
// 0x00053498 Sysutil_PollCallbacks: cellSysutilCheckCallback, then a thread yield. The argument
// (GameLoop passes "not in gameplay") is unused.
void Sysutil_PollCallbacks(int32_t notInGameplay);
