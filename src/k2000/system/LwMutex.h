// LwMutex.h - the engine's lightweight-mutex wrappers (original unit LwMutex.cpp, COMDAT 0x9962e8..).
// Created with protocol SYS_SYNC_PRIORITY (2), not recursive (0x20).
#pragma once
#include "platform/cell/sys_sync.h"

void LwMutex_Create(sys_lwmutex_t* mutex);   // 0x00996648
void LwMutex_Destroy(sys_lwmutex_t* mutex);  // 0x009964e8
void LwMutex_Lock(sys_lwmutex_t* mutex);     // 0x009963f0 (no timeout)
void LwMutex_Unlock(sys_lwmutex_t* mutex);   // 0x00996310
