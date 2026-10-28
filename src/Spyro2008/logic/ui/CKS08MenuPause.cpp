// CKS08MenuPause.cpp - reconstructed original translation unit 0x55da70-0x55f7a0 (GAME_TOC2, main_toc2), 24 functions, 20 live.
// Primary class: CKS08MenuPause  key 0x838c  category Logic  size ?  vtable 0xb2cfa0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x55da70  CKS08MenuPause_Delete
//   [ ] 0x55dac0  CKS08MenuPause_Construct  [dead]
//   [ ] 0x55db68  CKS08MenuPause_ClearInputStateFields_maybe  [dead]
//   [ ] 0x55db98  CKS08MenuPause_CheckButtonPairPressed_maybe  [dead]
//   [ ] 0x55dd18  CKS08MenuPause_ApplyCheatCode_maybe
//   [ ] 0x55e028  CKS08MenuPause_MessageProc
//   [x] 0x55e208  CKS08MenuPause_Load
//   [ ] 0x55e2e8  CKS08MenuPause_Save
//   [ ] 0x55e3c8  CKS08MenuPause_RecursiveRegistration
//   [ ] 0x55e438  CKS08MenuPause_Destroy
//   [x] 0x55e460  CKS08MenuPause_DeleteArray
//   [ ] 0x55e508  RegisterCKS08MenuPauseClass
//   [ ] 0x55e590  _GLOBAL__D_55e590
//   [ ] 0x55e5a0  _GLOBAL__I_55e5a0
//   [ ] 0x55e5b0  CKS08MenuPause_vfEC
//   [ ] 0x55e6b0  CKS08MenuPause_OnItemEvent
//   [ ] 0x55e8f8  CKS08MenuPause_Construct_2  [dead]
//   [x] 0x55e9a0  CKS08MenuPause_Create
//   [x] 0x55ea88  CKS08MenuPause_CreateArray
//   [ ] 0x55ebd0  CKS08MenuPause_UpdateCheatInput_maybe
//   [ ] 0x55ef18  CKS08MenuPause_Destructor
//   [ ] 0x55f050  CKS08MenuPause_Destructor_2
//   [ ] 0x55f188  CKS08MenuPause_DeletingDestructor
//   [ ] 0x55f2c0  CKS08MenuPause_OnStatePhase
//
//   [x] 0x9ca0a0  CKS08MenuPause_IsKindOfClass  [inline]
//   [x] 0x9ca0e0  CKS08MenuPause_GetClassType  [inline]
//   [x] 0x9ca0e8  CKS08MenuPause_GetClassID  [inline]
//   [x] 0x9ca0f0  CKS08MenuPause_vfB8  [inline]
//   [x] 0x9ca0f8  CKS08MenuPause_GetMenuId  [inline]
//   [x] 0x9ca100  CKS08MenuPause_GetWatchedMessageCount  [inline]
//   [x] 0x9ca108  CKS08MenuPause_GetWatchedMessageIds  [inline]
//   [x] 0x9ca118  CKS08MenuPause_GetMessageFlags  [inline]
//   [x] 0x9ca128  CKS08MenuPause_vfBC  [inline]
//   [x] 0x9ca130  CKS08MenuPause_vfC0  [inline]
//   [x] 0x9ca140  CKS08MenuPause_GetWidgetSlotCount  [inline]
//   [x] 0x9ca148  CKS08MenuPause_GetWidgetSlots  [inline]
//   [ ] 0x9ca158  CKS08MenuPause_HasBackItem  [inline]
//   [ ] 0x9ca160  CKS08MenuPause_GetBackItemIndex  [inline]
#include "Spyro2008/logic/ui/CKS08MenuPause.h"

#include "k2000/io/IKFile.h"

// 0x0055e208 CKS08MenuPause_Load: no type test of its own, so its fields are read whatever the type.
int32_t CKS08MenuPause::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    IKFile_ReadRef(file, &m_pSound);
    return 1;
}
