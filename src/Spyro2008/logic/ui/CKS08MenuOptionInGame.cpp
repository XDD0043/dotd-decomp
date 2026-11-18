// CKS08MenuOptionInGame.cpp - reconstructed original translation unit 0x55aec0-0x55b9e8 (GAME_TOC2, main_toc2), 18 functions, 16 live.
// Primary class: CKS08MenuOptionInGame  key 0xaccc  category Logic  size ?  vtable 0xb2cb80
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x55aec0  CKS08MenuOptionInGame_Delete
//   [ ] 0x55af10  CKS08MenuOptionInGame_Construct  [dead]
//   [x] 0x55afb8  CKS08MenuOptionInGame_OnStatePhase
//   [x] 0x55b070  CKS08MenuOptionInGame_Load
//   [ ] 0x55b098  CKS08MenuOptionInGame_Save
//   [x] 0x55b0c0  CKS08MenuOptionInGame_RecursiveRegistration  (inherited: CKMenuBase114c::RecursiveRegistration)
//   [x] 0x55b0e8  CKS08MenuOptionInGame_Destroy  (inherited: TocBridge_CKMenuBase_114c_maybe_Destroy)
//   [x] 0x55b110  CKS08MenuOptionInGame_DeleteArray
//   [ ] 0x55b1b0  RegisterCKS08MenuOptionInGameClass
//   [ ] 0x55b238  _GLOBAL__D_55b238
//   [ ] 0x55b248  _GLOBAL__I_55b248
//   [x] 0x55b258  CKS08MenuOptionInGame_OnItemEvent
//   [ ] 0x55b370  CKS08MenuOptionInGame_Construct_2  [dead]
//   [x] 0x55b418  CKS08MenuOptionInGame_CreateArray
//   [x] 0x55b558  CKS08MenuOptionInGame_Create
//   [x] 0x55b640  CKS08MenuOptionInGame_Destructor_2  (implicit destructor: CKMenuBase114c's inlined)
//   [x] 0x55b778  CKS08MenuOptionInGame_DeletingDestructor  (implicit destructor: CKMenuBase114c's inlined)
//   [x] 0x55b8b0  CKS08MenuOptionInGame_Destructor  (~CKMenuBase114c inlined (the same frees, checked against 0x556498))
//
//   [x] 0x9c9dd0  CKS08MenuOptionInGame_IsKindOfClass  [inline]
//   [x] 0x9c9e10  CKS08MenuOptionInGame_GetClassType  [inline]
//   [x] 0x9c9e18  CKS08MenuOptionInGame_GetClassID  [inline]
//   [x] 0x9c9e20  CKS08MenuOptionInGame_vfB8  [inline]
//   [x] 0x9c9e28  CKS08MenuOptionInGame_vfE0  [inline]
//   [x] 0x9c9e30  CKS08MenuOptionInGame_vfC4  [inline]
//   [x] 0x9c9e38  CKS08MenuOptionInGame_vfC8  [inline]
//   [x] 0x9c9e48  CKS08MenuOptionInGame_vfCC  [inline]
//   [x] 0x9c9e58  CKS08MenuOptionInGame_vfBC  [inline]
//   [x] 0x9c9e60  CKS08MenuOptionInGame_vfC0  [inline]
//   [x] 0x9c9e70  CKS08MenuOptionInGame_vfE4  [inline]
//   [x] 0x9c9e78  CKS08MenuOptionInGame_vfF0  [inline]
//   [x] 0x9c9e80  CKS08MenuOptionInGame_vfF4  [inline]
#include "Spyro2008/logic/ui/CKS08MenuOptionInGame.h"

#include "Spyro2008/logic/CKS08GameManager.h"

// 0x0055b070 CKS08MenuOptionInGame_Load (through TocBridge_CKMenuBase_114c_maybe_Load 0x98f720)
int32_t CKS08MenuOptionInGame::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    return 1;
}

// 0x0055afb8 CKS08MenuOptionInGame_OnStatePhase
uint8_t CKS08MenuOptionInGame::OnMenuState(int32_t phase, uint8_t /*other*/) {
    if (phase == 1) RefreshOptionWidgets();  // 0x513df8 (bridge 0x98f880)
    return static_cast<uint8_t>(GetMenuId());
}

// 0x0055b258 CKS08MenuOptionInGame_OnItemEvent
void CKS08MenuOptionInGame::OnItemState(uint8_t item, uint8_t state, uint8_t phase) {
    if (item == 9) {
        if (state == 4 && phase == 1) MenuGm_RequestMenu(static_cast<CKS08GameManager*>(m_pGameManager), 0x1c);
    } else if (item == 10) {
        if (state == 4 && phase == 1) {
            static_cast<CDefaultGameManager*>(m_pGameManager)->ResetEditedOptions();  // vt+0x1d4
            RefreshOptionWidgets();
        }
    } else if (item == 12) {
        if (state == 4 && phase == 1) static_cast<CDefaultGameManager*>(m_pGameManager)->RevertOptions();  // 0x16480
    }
}
