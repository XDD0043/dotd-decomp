// LwMutex.cpp - reconstructed original translation unit 0x992908-0x9bf0a8 (GAME_TOC1, comdat_toc1), 52 functions, 45 live.
// Primary owner: LwMutex (not a registered class)
// Other owners: HashTableU32 (8), KBase1 (3), HashTableStr (3), KBase808 (3), AnimMarkKeys2 (1), BreathSegmentChain (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x992908  IKService_IsKindOf
//   [ ] 0x992930  IKService_DeletingDestructor
//   [ ] 0x992978  IKService_Destructor
//   [ ] 0x993890  HashTableU32_InitNode
//   [ ] 0x994658  HashTableU32_InitNode_2
//   [ ] 0x995aa0  KStub_Nop_995aa0
//   [ ] 0x995aa8  HashTableU32_HashKey_3
//   [ ] 0x995ac0  HashTableU32_KeysEqual_3
//   [ ] 0x995ae0  HashTableU32_InitNode_3
//   [ ] 0x995b00  HashTableStr_HashKey
//   [ ] 0x995b50  HashTableStr_FreeNodeKey
//   [ ] 0x995b88  HashTableStr_InitNode
//   [ ] 0x9962e8  LwMutex_Unlock_Wrapper
//   [x] 0x996310  LwMutex_Unlock
//   [ ] 0x996338  LwMutex_LockTimeout  [dead]
//   [ ] 0x996380  LwMutex_Lock_Wrapper
//   [ ] 0x9963a8  LwMutex_LockTimeout_2  [dead]
//   [x] 0x9963f0  LwMutex_Lock
//   [ ] 0x996418  LwMutex_TryLock  [dead]
//   [ ] 0x996458  LwMutex_TryLock_2  [dead]
//   [ ] 0x996498  LwMutex_Destroy_Wrapper
//   [ ] 0x9964c0  LwMutex_Destroy_3  [dead]
//   [x] 0x9964e8  LwMutex_Destroy
//   [ ] 0x996510  LwMutex_Destroy_2
//   [ ] 0x996538  LwMutex_Create_2
//   [ ] 0x9965c0  LwMutex_Create_3  [dead]
//   [x] 0x996648  LwMutex_Create
//   [ ] 0x9966d0  LwMutex_Create_4  [dead]
//   [ ] 0x998cf8  HashTableU32_HashKey_5
//   [ ] 0x998d10  HashTableU32_KeysEqual_5
//   [ ] 0x998d30  HashTableU32_InitNode_5
//   [ ] 0x999a88  AnimMarkKeys2_GetKeyValue
//   [ ] 0x9a6248  KStub_Nop_9a6248
//   [ ] 0x9a6250  KStub_Nop_9a6250
//   [ ] 0x9a6258  KStub_Nop_9a6258
//   [ ] 0x9a67b8  KStub_Return1_9a67b8
//   [ ] 0x9a67c0  KStub_Nop_9a67c0
//   [ ] 0x9a67c8  KStub_Nop_9a67c8
//   [ ] 0x9a67d0  KStub_Nop_9a67d0
//   [ ] 0x9a67d8  KStub_Nop_9a67d8
//   [ ] 0x9a67e0  KStub_Nop_9a67e0
//   [ ] 0x9a67e8  KStub_Nop_9a67e8
//   [ ] 0x9a67f0  KStub_Nop_9a67f0
//   [ ] 0x9a67f8  KStub_Nop_9a67f8
//   [ ] 0x9a6800  KStub_Nop_9a6800
//   [ ] 0x9a6808  KStub_Nop_9a6808
//   [ ] 0x9a6810  KStub_Return0_9a6810
//   [ ] 0x9a6818  KStub_Return44_9a6818
//   [ ] 0x9aa5c8  IKCinematicElement_vf14
//   [ ] 0x9aa5d0  IKCinematicElement_vf18
//   [ ] 0x9aa5d8  IKCinematicElement_vf8
//   [ ] 0x9bef38  BreathSegmentChain_Free_maybe
#include "k2000/system/LwMutex.h"

// 0x00996648 LwMutex_Create
void LwMutex_Create(sys_lwmutex_t* mutex) {
    const sys_lwmutex_attribute_t attr = {2u, 0x20u, {'k', 'e', 'M', 'u', 't', 'e', 'x', 0}};  // "keMutex" (0xac3dd8)
    sys_lwmutex_create(mutex, &attr);
}

// 0x009964e8 LwMutex_Destroy
void LwMutex_Destroy(sys_lwmutex_t* mutex) { sys_lwmutex_destroy(mutex); }

// 0x009963f0 LwMutex_Lock
void LwMutex_Lock(sys_lwmutex_t* mutex) { sys_lwmutex_lock(mutex, 0); }

// 0x00996310 LwMutex_Unlock
void LwMutex_Unlock(sys_lwmutex_t* mutex) { sys_lwmutex_unlock(mutex); }
