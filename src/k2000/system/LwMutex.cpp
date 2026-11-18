// LwMutex.cpp - reconstructed original translation unit 0x992908-0x9bf0a8 (GAME_TOC1, comdat_toc1), 52 functions, 45 live.
// Primary owner: LwMutex (not a registered class)
// Other owners: HashTableU32 (8), KBase1 (3), HashTableStr (3), KBase808 (3), AnimMarkKeys2 (1), BreathSegmentChain (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x992908  IKService_IsKindOf  (IKService.h IsKindOfClass)
//   [x] 0x992930  IKService_DeletingDestructor  (IKService.h: the implicit destructor)
//   [x] 0x992978  IKService_Destructor  (IKService.h: the implicit destructor)
//   [ ] 0x993890  HashTableU32_InitNode  [dead: its vtable 0xb13da8 (TOC1 -0x7b48) is installed only by the dead 0x270f8 / 0x276b8 and its own destructors]
//   [x] 0x994658  HashTableU32_InitNode_2  (CLocManager.h HashTableU32::InitNode)
//   [ ] 0x995aa0  KStub_Nop_995aa0  [platform]  (the KHostFS u32 hash table (vtable 0xb15378): the PS3 file stack, KFileStream.h by design)
//   [ ] 0x995aa8  HashTableU32_HashKey_3  [platform]  (the KHostFS u32 hash table (vtable 0xb15378): the PS3 file stack, KFileStream.h by design)
//   [ ] 0x995ac0  HashTableU32_KeysEqual_3  [platform]  (the KHostFS u32 hash table (vtable 0xb15378): the PS3 file stack, KFileStream.h by design)
//   [ ] 0x995ae0  HashTableU32_InitNode_3  [platform]  (the KHostFS u32 hash table (vtable 0xb15378): the PS3 file stack, KFileStream.h by design)
//   [ ] 0x995b00  HashTableStr_HashKey  [platform]  (the KHostFS string hash table (vtable 0xb15358): the PS3 file stack, KFileStream.h by design)
//   [ ] 0x995b50  HashTableStr_FreeNodeKey  [platform]  (the KHostFS string hash table (vtable 0xb15358): the PS3 file stack, KFileStream.h by design)
//   [ ] 0x995b88  HashTableStr_InitNode  [platform]  (the KHostFS string hash table (vtable 0xb15358): the PS3 file stack, KFileStream.h by design)
//   [ ] 0x9962e8  LwMutex_Unlock_Wrapper  [platform]  (sys_lwmutex_unlock of the KFileSystem / CRenderer lwmutex, a PS3 system object those ports do not model (KFileSystem.h, CRenderer.cpp))
//   [x] 0x996310  LwMutex_Unlock
//   [ ] 0x996338  LwMutex_LockTimeout  [dead]
//   [ ] 0x996380  LwMutex_Lock_Wrapper  [platform]  (sys_lwmutex_lock of the KFileSystem lwmutex, a PS3 system object the port does not model (KFileSystem.h))
//   [ ] 0x9963a8  LwMutex_LockTimeout_2  [dead]
//   [x] 0x9963f0  LwMutex_Lock
//   [ ] 0x996418  LwMutex_TryLock  [dead]
//   [ ] 0x996458  LwMutex_TryLock_2  [dead]
//   [ ] 0x996498  LwMutex_Destroy_Wrapper  [platform]  (sys_lwmutex_destroy of the KFileSystem / KFileStream / CRenderer lwmutex, a PS3 system object those ports do not model)
//   [ ] 0x9964c0  LwMutex_Destroy_3  [dead]
//   [x] 0x9964e8  LwMutex_Destroy
//   [ ] 0x996510  LwMutex_Destroy_2  [dead: no pointer to its descriptor 0xb3f180, no call]
//   [ ] 0x996538  LwMutex_Create_2  [platform]  (sys_lwmutex_create (attr 2 / 0x10) of the KFileSystem / KFileStream / CRenderer lwmutex, a PS3 system object those ports do not model)
//   [ ] 0x9965c0  LwMutex_Create_3  [dead]
//   [x] 0x996648  LwMutex_Create
//   [ ] 0x9966d0  LwMutex_Create_4  [dead]
//   [x] 0x998cf8  HashTableU32_HashKey_5  (CKFlashUI.h CKFlashUI_ObjectInfosMap::KeyToHashIndex)
//   [x] 0x998d10  HashTableU32_KeysEqual_5  (CKFlashUI.h CKFlashUI_ObjectInfosMap::IsKeysEqual)
//   [x] 0x998d30  HashTableU32_InitNode_5  (CKFlashUI.h CKFlashUI_ObjectInfosMap::SetValue)
//   [x] 0x999a88  AnimMarkKeys2_GetKeyValue  (CKAnimationMarkContainer.h AnimMark_GetKeyValueR3: vt+0x20 of the type-2 mark)
//   [ ] 0x9a6248  KStub_Nop_9a6248  [platform]  (a CShaderManagerPSGL / ShaderProgram vtable stub (0xb19234 / 0xb19258): the PSGL / Cg shader layer, replaced by the platform renderer by design)
//   [ ] 0x9a6250  KStub_Nop_9a6250  [platform]  (a CShaderManagerPSGL / ShaderProgram vtable stub (0xb19234 / 0xb19258): the PSGL / Cg shader layer, replaced by the platform renderer by design)
//   [ ] 0x9a6258  KStub_Nop_9a6258  [platform]  (a CShaderManagerPSGL / ShaderProgram vtable stub (0xb19234 / 0xb19258): the PSGL / Cg shader layer, replaced by the platform renderer by design)
//   [ ] 0x9a67b8  KStub_Return1_9a67b8  [platform]  (a PS3PadDevice vtable stub (0xb19700): the PS3 pad device, platform/cell/pad by design)
//   [ ] 0x9a67c0  KStub_Nop_9a67c0  [platform]  (a PS3PadDevice vtable stub (0xb19700): the PS3 pad device, platform/cell/pad by design)
//   [ ] 0x9a67c8  KStub_Nop_9a67c8  [platform]  (a PS3PadDevice vtable stub (0xb19700): the PS3 pad device, platform/cell/pad by design)
//   [ ] 0x9a67d0  KStub_Nop_9a67d0  [platform]  (a PS3PadDevice vtable stub (0xb19700): the PS3 pad device, platform/cell/pad by design)
//   [ ] 0x9a67d8  KStub_Nop_9a67d8  [platform]  (a PS3PadDevice vtable stub (0xb19700): the PS3 pad device, platform/cell/pad by design)
//   [ ] 0x9a67e0  KStub_Nop_9a67e0  [platform]  (a PS3PadDevice vtable stub (0xb19700): the PS3 pad device, platform/cell/pad by design)
//   [ ] 0x9a67e8  KStub_Nop_9a67e8  [platform]  (a PS3PadDevice / pad-device base vtable stub (0xb196c0 / 0xb19760): the PS3 pad device, platform/cell/pad by design)
//   [ ] 0x9a67f0  KStub_Nop_9a67f0  [platform]  (a PS3PadDevice / pad-device base vtable stub (0xb196c0 / 0xb19760): the PS3 pad device, platform/cell/pad by design)
//   [ ] 0x9a67f8  KStub_Nop_9a67f8  [platform]  (a PS3PadDevice / pad-device base vtable stub (0xb196c0 / 0xb19760): the PS3 pad device, platform/cell/pad by design)
//   [ ] 0x9a6800  KStub_Nop_9a6800  [platform]  (a PS3PadDevice / pad-device base vtable stub (0xb196c0 / 0xb19760): the PS3 pad device, platform/cell/pad by design)
//   [ ] 0x9a6808  KStub_Nop_9a6808  [platform]  (a PS3PadDevice / pad-device base vtable stub (0xb196c0 / 0xb19760): the PS3 pad device, platform/cell/pad by design)
//   [ ] 0x9a6810  KStub_Return0_9a6810  [platform]  (a PS3PadDevice / pad-device base vtable stub (0xb196c0 / 0xb19760): the PS3 pad device, platform/cell/pad by design)
//   [ ] 0x9a6818  KStub_Return44_9a6818  [platform]  (a PS3PadDevice / pad-device base vtable stub (0xb196c0 / 0xb19760): the PS3 pad device, platform/cell/pad by design)
//   [x] 0x9aa5c8  IKCinematicElement_vf14  (IKCinematicElement.h GetClassType (8; vt+0x14 of the vtable 0xb1bdc8))
//   [x] 0x9aa5d0  IKCinematicElement_vf18  (IKCinematicElement.h GetClassID (0x20; vt+0x18))
//   [x] 0x9aa5d8  IKCinematicElement_vf8  (IKCinematicElement.h IsKindOfClass (0x808, 0xc; vt+0x08))
//   [x] 0x9bef38  BreathSegmentChain_Free_maybe  (BreathSegmentChain.h BreathSegmentChain_Free: a template on the node type; its only live caller is 0x371608 KBaseC_vf80, R10's CKS08HeroElement.cpp)
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
