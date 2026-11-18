// CKStartDoor.cpp - reconstructed original translation unit 0x16fe28-0x1702f8 (GAME_TOC1, main_toc1), 13 functions, 13 live.
// Primary class: CKStartDoor  key 0x448  category CinematicNode  size 0x28  vtable 0xb1aee8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x16fe28  CKStartDoor_Delete
//   [x] 0x16fe78  CKStartDoor_Complete
//   [x] 0x16fe80  CKStartDoor_Update
//   [ ] 0x16fe88  RegisterCKStartDoorClass
//   [ ] 0x16ff00  _GLOBAL__I_16ff00
//   [x] 0x16ff10  CKStartDoor_Start
//   [x] 0x170030  CKStartDoor_Load
//   [ ] 0x170058  CKStartDoor_Save
//   [x] 0x170080  CKStartDoor_RecursiveRegistration
//   [x] 0x170110  CKStartDoor_DeleteArray
//   [x] 0x1701b8  CKStartDoor_Create
//   [x] 0x170218  CKStartDoor_Destroy  (empty: the default)
//   [x] 0x170220  CKStartDoor_CreateArray
//
//   [ ] 0x9a9178  CKStartDoor_GetClassType  [inline]
//   [ ] 0x9a9180  CKStartDoor_GetClassID  [inline]
//   [x] 0x9a9188  CKStartDoor_Abort  [inline]
//   [ ] 0x9a9190  CKStartDoor_IsKindOfClass  [inline]
//   [ ] 0x9a91c8  CKStartDoor_Destructor  [inline]
//   [ ] 0x9a91e8  CKStartDoor_DeletingDestructor  [inline]
//   [ ] 0x9a9230  KStub_Return0_9a9230  [inline]
//   [ ] 0x9a9238  KStub_Return0_9a9238  [inline]
//   [ ] 0x9a9240  KStub_Return0_9a9240  [inline]
//   [ ] 0x9a9248  KStub_Return-1_9a9248  [inline]
#include "k2000/cinematics/CKStartDoor.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"

#include "k2000/logic/CKCinematicScene.h"

// 0x00170030 CKStartDoor_Load
int32_t CKStartDoor::Load(IKFile* file, int32_t type) { return BasicLoadCinematicElement(file, type); }

// 0x0016ff10 CKStartDoor_Start
void CKStartDoor::Start() {
    uint32_t count = 0;
    IKCinematicElement** outputs = m_pRelatedScene->GetNodeOutputs(&count, 1, this);
    for (uint32_t i = 0; i < count; ++i) {
        outputs[i]->PreActivate();   // vt+0x58
        outputs[i]->Activate(this);  // vt+0x60
    }
    Complete();  // vt+0x64
}

// 0x00170080 CKStartDoor_RecursiveRegistration
void CKStartDoor::RecursiveRegistration(int32_t type) {
    if (static_cast<uint32_t>(type - 4) > 3u) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
    IKLogicalDoor::RecursiveRegistration(type);  // 0x0018fc20
}
