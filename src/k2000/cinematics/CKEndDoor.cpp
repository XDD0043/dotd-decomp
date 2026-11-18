// CKEndDoor.cpp - reconstructed original translation unit 0x16e7b8-0x16edf8 (GAME_TOC1, main_toc1), 14 functions, 14 live.
// Primary class: CKEndDoor  key 0x7c8  category CinematicNode  size 0x28  vtable 0xb1acc8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x16e7b8  CKEndDoor_Delete
//   [x] 0x16e808  CKEndDoor_Update
//   [x] 0x16e848  CKEndDoor_Abort
//   [ ] 0x16e868  RegisterCKEndDoorClass
//   [ ] 0x16e8e0  _GLOBAL__I_16e8e0
//   [x] 0x16e8f0  CKEndDoor_Complete
//   [x] 0x16eac0  CKEndDoor_Start
//   [x] 0x16eb30  CKEndDoor_Load
//   [ ] 0x16eb58  CKEndDoor_Save
//   [x] 0x16eb80  CKEndDoor_RecursiveRegistration
//   [x] 0x16ec10  CKEndDoor_DeleteArray
//   [x] 0x16ecb8  CKEndDoor_Create
//   [x] 0x16ed18  CKEndDoor_Destroy  (empty: the default)
//   [x] 0x16ed20  CKEndDoor_CreateArray
//
//   [ ] 0x9a8e60  CKEndDoor_GetClassType  [inline]
//   [ ] 0x9a8e68  CKEndDoor_GetClassID  [inline]
//   [ ] 0x9a8e70  CKEndDoor_IsKindOfClass  [inline]
//   [ ] 0x9a8ec8  CKEndDoor_Destructor  [inline]
//   [ ] 0x9a8ee8  CKEndDoor_DeletingDestructor  [inline]
#include "k2000/cinematics/CKEndDoor.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"

// 0x0016eb30 CKEndDoor_Load
int32_t CKEndDoor::Load(IKFile* file, int32_t type) { return BasicLoadCinematicElement(file, type); }

// 0x0016e848 CKEndDoor_Abort
void CKEndDoor::Abort() {
    m_DataFlags &= 0xfffffffeu;
    m_ui32CurrentIncomingNumber = 0;
}

// 0x0016eb80 CKEndDoor_RecursiveRegistration
void CKEndDoor::RecursiveRegistration(int32_t type) {
    if (static_cast<uint32_t>(type - 4) > 3u) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
    IKLogicalDoor::RecursiveRegistration(type);  // 0x0018fc20
}
