// CKLogicalOr.cpp - reconstructed original translation unit 0x16f6e8-0x16fe28 (GAME_TOC1, main_toc1), 15 functions, 14 live.
// Primary class: CKLogicalOr  key 0x88  category CinematicNode  size 0x28  vtable 0xb1ae60
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x16f6e8  CKLogicalOr_Delete
//   [x] 0x16f738  CKLogicalOr_Abort
//   [ ] 0x16f758  CKLogicalOr_Update_2  [dead]
//   [ ] 0x16f7b8  RegisterCKLogicalOrClass
//   [ ] 0x16f830  _GLOBAL__I_16f830
//   [x] 0x16f840  CKLogicalOr_Complete
//   [x] 0x16fa10  CKLogicalOr_Load
//   [ ] 0x16fa38  CKLogicalOr_Save
//   [x] 0x16fa60  CKLogicalOr_RecursiveRegistration
//   [x] 0x16faf0  CKLogicalOr_DeleteArray
//   [x] 0x16fb98  CKLogicalOr_CreateArray
//   [x] 0x16fc70  CKLogicalOr_Destroy  (empty: the default)
//   [x] 0x16fc78  CKLogicalOr_Create
//   [x] 0x16fcd8  CKLogicalOr_Start
//   [x] 0x16fdc8  CKLogicalOr_Update
//
//   [ ] 0x9a90c8  CKLogicalOr_GetClassType  [inline]
//   [ ] 0x9a90d0  CKLogicalOr_GetClassID  [inline]
//   [ ] 0x9a90d8  CKLogicalOr_IsKindOfClass  [inline]
//   [ ] 0x9a9110  CKLogicalOr_DeletingDestructor  [inline]
//   [ ] 0x9a9158  CKLogicalOr_Destructor  [inline]
#include "k2000/cinematics/CKLogicalOr.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"

#include "k2000/logic/CKCinematicScene.h"

// 0x0016fa10 CKLogicalOr_Load
int32_t CKLogicalOr::Load(IKFile* file, int32_t type) { return BasicLoadCinematicElement(file, type); }

// 0x0016fcd8 CKLogicalOr_Start: the first input activates the door and completes it at once.
void CKLogicalOr::Start() {
    if (m_ui32CurrentIncomingNumber == 0) {
        m_pRelatedScene->AddActiveNode(this);
        m_DataFlags = (m_DataFlags & 0xfffffff8u) | (m_DataFlags & 2) | 1;
    }
    ++m_ui32CurrentIncomingNumber;
    if (m_ui32CurrentIncomingNumber != 1) return;
    Complete();  // vt+0x64
}

// 0x0016fdc8 CKLogicalOr_Update
void CKLogicalOr::Update(IKTime*) {
    if (m_ui32CurrentIncomingNumber != 1) return;
    Complete();
}

// 0x0016f738 CKLogicalOr_Abort
void CKLogicalOr::Abort() {
    m_DataFlags &= 0xfffffffeu;
    m_ui32CurrentIncomingNumber = 0;
}

// 0x0016fa60 CKLogicalOr_RecursiveRegistration
void CKLogicalOr::RecursiveRegistration(int32_t type) {
    if (static_cast<uint32_t>(type - 4) > 3u) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
    IKLogicalDoor::RecursiveRegistration(type);  // 0x0018fc20
}
