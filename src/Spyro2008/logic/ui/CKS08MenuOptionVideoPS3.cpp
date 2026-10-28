// CKS08MenuOptionVideoPS3.cpp - reconstructed original translation unit 0x55d020-0x55da70 (GAME_TOC2, main_toc2), 18 functions, 16 live.
// Primary class: CKS08MenuOptionVideoPS3  key 0x868c  category Logic  size ?  vtable 0xb2ce98
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x55d020  CKS08MenuOptionVideoPS3_Delete
//   [ ] 0x55d070  CKS08MenuOptionVideoPS3_Construct  [dead]
//   [x] 0x55d118  CKS08MenuOptionVideoPS3_vfDC
//   [x] 0x55d160  CKS08MenuOptionVideoPS3_Load
//   [ ] 0x55d188  CKS08MenuOptionVideoPS3_Save
//   [ ] 0x55d1b0  CKS08MenuOptionVideoPS3_RecursiveRegistration
//   [ ] 0x55d1d8  CKS08MenuOptionVideoPS3_Destroy
//   [x] 0x55d200  CKS08MenuOptionVideoPS3_DeleteArray
//   [ ] 0x55d2a0  RegisterCKS08MenuOptionVideoPS3Class
//   [ ] 0x55d328  _GLOBAL__D_55d328
//   [ ] 0x55d338  _GLOBAL__I_55d338
//   [x] 0x55d348  CKS08MenuOptionVideoPS3_vfE8
//   [ ] 0x55d3f8  CKS08MenuOptionVideoPS3_Construct_2  [dead]
//   [x] 0x55d4a0  CKS08MenuOptionVideoPS3_Create
//   [x] 0x55d588  CKS08MenuOptionVideoPS3_CreateArray
//   [ ] 0x55d6c8  CKS08MenuOptionVideoPS3_Destructor_2
//   [ ] 0x55d800  CKS08MenuOptionVideoPS3_DeletingDestructor
//   [ ] 0x55d938  CKS08MenuOptionVideoPS3_Destructor
//
//   [x] 0x9c9ff0  CKS08MenuOptionVideoPS3_IsKindOfClass  [inline]
//   [x] 0x9ca030  CKS08MenuOptionVideoPS3_GetClassType  [inline]
//   [x] 0x9ca038  CKS08MenuOptionVideoPS3_GetClassID  [inline]
//   [x] 0x9ca040  CKS08MenuOptionVideoPS3_vfB8  [inline]
//   [x] 0x9ca048  CKS08MenuOptionVideoPS3_vfE0  [inline]
//   [x] 0x9ca050  CKS08MenuOptionVideoPS3_vfC4  [inline]
//   [x] 0x9ca058  CKS08MenuOptionVideoPS3_vfC8  [inline]
//   [x] 0x9ca068  CKS08MenuOptionVideoPS3_vfCC  [inline]
//   [x] 0x9ca078  CKS08MenuOptionVideoPS3_vfBC  [inline]
//   [x] 0x9ca080  CKS08MenuOptionVideoPS3_vfC0  [inline]
//   [x] 0x9ca090  CKS08MenuOptionVideoPS3_vfF0  [inline]
//   [x] 0x9ca098  CKS08MenuOptionVideoPS3_vfF4  [inline]
#include "Spyro2008/logic/ui/CKS08MenuOptionVideoPS3.h"

#include "Spyro2008/logic/CKS08GameManager.h"

// 0x0055d160 CKS08MenuOptionVideoPS3_Load (through TocBridge_CKMenuBase_114c_maybe_Load 0x98f720)
int32_t CKS08MenuOptionVideoPS3::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    return 1;
}

// The back item's request (both PS3 option screens): the options menu (0x19) from the main menu's state 6,
// else the in-game options (0x17).
static void RequestOptionsMenu(CKS08GameManager* manager) {
    MenuGm_RequestMenu(manager, manager->m_gameState.m_ui8Current == 6 ? 0x19 : 0x17);
}

// 0x0055d118 CKS08MenuOptionVideoPS3_vfDC
uint8_t CKS08MenuOptionVideoPS3::OnMenuState(int32_t /*phase*/, uint8_t /*other*/) { return static_cast<uint8_t>(GetMenuId()); }

// 0x0055d348 CKS08MenuOptionVideoPS3_vfE8
void CKS08MenuOptionVideoPS3::OnItemState(uint8_t item, uint8_t state, uint8_t phase) {
    if (phase == 1 && state == 4 && item == 1) RequestOptionsMenu(static_cast<CKS08GameManager*>(m_pGameManager));
}
