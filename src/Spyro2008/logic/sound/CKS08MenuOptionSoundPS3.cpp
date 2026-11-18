// CKS08MenuOptionSoundPS3.cpp - reconstructed original translation unit 0x55c5b0-0x55d020 (GAME_TOC2, main_toc2), 19 functions, 17 live.
// Primary class: CKS08MenuOptionSoundPS3  key 0xaf0c  category Logic  size ?  vtable 0xb2cd90
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x55c5b0  CKS08MenuOptionSoundPS3_Delete
//   [ ] 0x55c600  CKS08MenuOptionSoundPS3_Construct  [dead]
//   [x] 0x55c6a8  CKS08MenuOptionSoundPS3_vfDC
//   [x] 0x55c6f0  CKS08MenuOptionSoundPS3_vf9C
//   [x] 0x55c718  CKS08MenuOptionSoundPS3_Load
//   [ ] 0x55c740  CKS08MenuOptionSoundPS3_Save
//   [x] 0x55c768  CKS08MenuOptionSoundPS3_RecursiveRegistration  (inherited: CKMenuBase114c::RecursiveRegistration)
//   [x] 0x55c790  CKS08MenuOptionSoundPS3_Destroy  (inherited: TocBridge_CKMenuBase_114c_maybe_Destroy)
//   [x] 0x55c7b8  CKS08MenuOptionSoundPS3_DeleteArray
//   [ ] 0x55c858  RegisterCKS08MenuOptionSoundPS3Class
//   [ ] 0x55c8e0  _GLOBAL__D_55c8e0
//   [ ] 0x55c8f0  _GLOBAL__I_55c8f0
//   [x] 0x55c900  CKS08MenuOptionSoundPS3_vfE8
//   [ ] 0x55c9a8  CKS08MenuOptionSoundPS3_Construct_2  [dead]
//   [x] 0x55ca50  CKS08MenuOptionSoundPS3_Create
//   [x] 0x55cb38  CKS08MenuOptionSoundPS3_CreateArray
//   [x] 0x55cc78  CKS08MenuOptionSoundPS3_Destructor_2  (implicit destructor: CKMenuBase114c's inlined)
//   [x] 0x55cdb0  CKS08MenuOptionSoundPS3_DeletingDestructor  (implicit destructor: CKMenuBase114c's inlined)
//   [x] 0x55cee8  CKS08MenuOptionSoundPS3_Destructor  (~CKMenuBase114c inlined (the same frees, checked against 0x556498))
//
//   [x] 0x9c9f40  CKS08MenuOptionSoundPS3_IsKindOfClass  [inline]
//   [x] 0x9c9f80  CKS08MenuOptionSoundPS3_GetClassType  [inline]
//   [x] 0x9c9f88  CKS08MenuOptionSoundPS3_GetClassID  [inline]
//   [x] 0x9c9f90  CKS08MenuOptionSoundPS3_vfB8  [inline]
//   [x] 0x9c9f98  CKS08MenuOptionSoundPS3_vfE0  [inline]
//   [x] 0x9c9fa0  CKS08MenuOptionSoundPS3_vfC4  [inline]
//   [x] 0x9c9fa8  CKS08MenuOptionSoundPS3_vfC8  [inline]
//   [x] 0x9c9fb8  CKS08MenuOptionSoundPS3_vfCC  [inline]
//   [x] 0x9c9fc8  CKS08MenuOptionSoundPS3_vfBC  [inline]
//   [x] 0x9c9fd0  CKS08MenuOptionSoundPS3_vfC0  [inline]
//   [x] 0x9c9fe0  CKS08MenuOptionSoundPS3_vfF0  [inline]
//   [x] 0x9c9fe8  CKS08MenuOptionSoundPS3_vfF4  [inline]
#include "Spyro2008/logic/sound/CKS08MenuOptionSoundPS3.h"

#include "Spyro2008/logic/CKS08GameManager.h"

// 0x0055c718 CKS08MenuOptionSoundPS3_Load (through TocBridge_CKMenuBase_114c_maybe_Load 0x98f720)
int32_t CKS08MenuOptionSoundPS3::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    return 1;
}

// The back item's request (both PS3 option screens): the options menu (0x19) from the main menu's state 6,
// else the in-game options (0x17).
static void RequestOptionsMenu(CKS08GameManager* manager) {
    MenuGm_RequestMenu(manager, manager->m_gameState.m_ui8Current == 6 ? 0x19 : 0x17);
}

// 0x0055c6a8 CKS08MenuOptionSoundPS3_vfDC
uint8_t CKS08MenuOptionSoundPS3::OnMenuState(int32_t /*phase*/, uint8_t /*other*/) { return static_cast<uint8_t>(GetMenuId()); }

// 0x0055c900 CKS08MenuOptionSoundPS3_vfE8
void CKS08MenuOptionSoundPS3::OnItemState(uint8_t item, uint8_t state, uint8_t phase) {
    if (phase == 1 && state == 4 && item == 3) RequestOptionsMenu(static_cast<CKS08GameManager*>(m_pGameManager));
}
