// Reconstructed original translation unit: 0x78280-0x786f0 (GAME_TOC1, main_toc1), 15 functions, 15 live.
// Primary class: CKFlashStartEventEvent  key 0x2dcc  category Logic  size 0x10  vtable 0xb16470
// Other owners: IKFlashGenericEvent (3)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x78280  CKFlashStartEventEvent_Delete  (DOTD_DECLARE_FACTORIES Delete)
//   [x] 0x782d0  CKFlashStartEventEvent_PostLoad  (IKSerializable's default (1))
//   [ ] 0x782d8  RegisterCKFlashStartEventEventClass
//   [ ] 0x78350  _GLOBAL__I_78350
//   [x] 0x78360  CKFlashStartEventEvent_Load
//   [ ] 0x783d8  CKFlashStartEventEvent_Save
//   [x] 0x78400  CKFlashStartEventEvent_RecursiveRegistration
//   [x] 0x784a8  CKFlashStartEventEvent_FireEvent
//   [x] 0x784e0  CKFlashStartEventEvent_DeleteArray  (DOTD_DECLARE_FACTORIES DeleteArray)
//   [x] 0x78580  CKFlashStartEventEvent_CreateArray  (DOTD_DECLARE_FACTORIES CreateArray)
//   [x] 0x78610  CKFlashStartEventEvent_Create  (DOTD_DECLARE_FACTORIES Create)
//   [x] 0x78648  CKFlashStartEventEvent_GetInfo  (IKSerializable's default (1))
//   [x] 0x78650  IKFlashGenericEvent_Load  (IKFlashGenericEvent.h)
//   [x] 0x786e0  IKFlashGenericEvent_vf28  (IKFlashGenericEvent's Save (1): the default)
//   [x] 0x786e8  IKFlashGenericEvent_vf24  (IKFlashGenericEvent's RecursiveRegistration (1): the default)
//
//   [ ] 0x999560  CKFlashStartEventEvent_IsKindOfClass  [inline]
//   [ ] 0x999588  CKFlashStartEventEvent_Destroy  [inline]
//   [ ] 0x999590  CKFlashStartEventEvent_GetClassType  [inline]
//   [ ] 0x999598  CKFlashStartEventEvent_GetClassID  [inline]
//   [ ] 0x9995a0  CKFlashStartEventEvent_DeletingDestructor  [inline]
//   [ ] 0x9995e8  CKFlashStartEventEvent_Destructor  [inline]
//   [ ] 0x999608  IKFlashGenericEvent_vf14  [inline]
//   [ ] 0x999610  IKFlashGenericEvent_vf18  [inline]
//   [ ] 0x999618  IKFlashGenericEvent_vf30  [inline]
//   [ ] 0x999620  IKFlashGenericEvent_vf10  [inline]
//   [ ] 0x999628  IKFlashGenericEvent_vf8  [inline]
//   [ ] 0x999648  IKFlashGenericEvent_vf0  [inline]
//   [ ] 0x999660  IKFlashGenericEvent_DeletingDestructor  [inline]
#include "k2000/logic/ui/CKFlashStartEventEvent.h"

#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"

// 0x00078360 CKFlashStartEventEvent_Load
int32_t CKFlashStartEventEvent::Load(IKFile* file, int32_t type) {
    IKFlashGenericEvent::Load(file, type);  // 0x00078650
    if (type == K_LEVEL_PLATEFORMS) m_tsStart.Load(file, K_LEVEL_PLATEFORMS);  // 0x002361c0
    return 1;
}

// 0x00078400 CKFlashStartEventEvent_RecursiveRegistration (the base's 0x786e8 returns 1)
void CKFlashStartEventEvent::RecursiveRegistration(int32_t type) {
    if (type != 0) return;
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}

// 0x000784a8 CKFlashStartEventEvent_FireEvent
void CKFlashStartEventEvent::Vf50() { QueueTriggerSignals(&m_tsStart); }  // 0x00236338
