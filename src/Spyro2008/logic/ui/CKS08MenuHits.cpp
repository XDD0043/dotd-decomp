// CKS08MenuHits.cpp - reconstructed original translation unit 0x5554c8-0x556840 (GAME_TOC1, main_toc1), 20 functions, 18 live.
// Primary class: CKS08MenuHits  key 0xa74c  category Logic  size 0xf0  vtable 0xb2c760
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5554c8  CKS08MenuHits_Delete
//   [ ] 0x555518  CKS08MenuHits_Construct  [dead]
//   [ ] 0x5555c0  CKS08MenuHits_RefreshPageTexts
//   [ ] 0x555800  CKS08MenuHits_OnItemEvent
//   [ ] 0x555888  CKS08MenuHits_HandlePagingButtons
//   [ ] 0x555a70  CKS08MenuHits_OnStatePhase
//   [ ] 0x555b78  CKS08MenuHits_RecursiveRegistration
//   [ ] 0x555c40  CKS08MenuHits_Destroy
//   [x] 0x555c68  CKS08MenuHits_DeleteArray
//   [ ] 0x555d10  RegisterCKS08MenuHitsClass
//   [ ] 0x555d98  _GLOBAL__D_555d98
//   [ ] 0x555da8  _GLOBAL__I_555da8
//   [ ] 0x555db8  CKS08MenuHits_Construct_2  [dead]
//   [x] 0x555e60  CKS08MenuHits_CreateArray
//   [x] 0x555fa8  CKS08MenuHits_Create
//   [x] 0x556090  CKS08MenuHits_Load
//   [ ] 0x556290  CKS08MenuHits_Save
//   [ ] 0x556498  CKS08MenuHits_Destructor
//   [ ] 0x5565d0  CKS08MenuHits_Destructor_2
//   [ ] 0x556708  CKS08MenuHits_DeletingDestructor
//
//   [x] 0x9c9ac8  CKS08MenuHits_IsKindOfClass  [inline]
//   [x] 0x9c9b08  CKS08MenuHits_GetClassType  [inline]
//   [x] 0x9c9b10  CKS08MenuHits_GetClassID  [inline]
//   [x] 0x9c9b18  CKS08MenuHits_vfB8  [inline]
//   [x] 0x9c9b20  CKS08MenuHits_vfE0  [inline]
//   [x] 0x9c9b28  CKS08MenuHits_vfC4  [inline]
//   [x] 0x9c9b30  CKS08MenuHits_vfC8  [inline]
//   [x] 0x9c9b40  CKS08MenuHits_vfCC  [inline]
//   [x] 0x9c9b50  CKS08MenuHits_vfBC  [inline]
//   [x] 0x9c9b58  CKS08MenuHits_vfC0  [inline]
//   [x] 0x9c9b68  CKS08MenuHits_GetWidgetSlotCount  [inline]
//   [x] 0x9c9b70  CKS08MenuHits_GetWidgetSlots  [inline]
//   [ ] 0x9c9b80  CKS08MenuHits_vfF0  [inline]
//   [ ] 0x9c9b88  CKS08MenuHits_vfF4  [inline]
//   [ ] 0x9c9b90  CKS08MenuHits_vfE4  [inline]
#include "Spyro2008/logic/ui/CKS08MenuHits.h"

#include "k2000/io/IKFile.h"

// 0x00556090 CKS08MenuHits_Load: no type test of its own, so its fields are read whatever the type.
int32_t CKS08MenuHits::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    IKFile_ReadRef(file, &m_pTextE0);
    IKFile_ReadRef(file, &m_pTextE4);
    IKFile_ReadRef(file, &m_pTextE8);
    return 1;
}
