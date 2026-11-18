// CKS08MenuStartPlayer.cpp - reconstructed original translation unit 0x564680-0x565218 (GAME_TOC2, main_toc2), 20 functions, 17 live.
// Primary class: CKS08MenuStartPlayer  key 0xb0cc  category Logic  size ?  vtable 0xb2d3c0
// Other owners: CKS08MenuStatsGame (1), Time (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x564680  CKS08MenuStartPlayer_Delete
//   [ ] 0x5646d0  CKS08MenuStartPlayer_Construct  [dead]
//   [x] 0x564778  CKS08MenuStartPlayer_vfDC
//   [x] 0x5647c0  CKS08MenuStartPlayer_Load
//   [ ] 0x5647e8  CKS08MenuStartPlayer_Save
//   [x] 0x564810  CKS08MenuStartPlayer_RecursiveRegistration  (inherited: CKMenuBase114c's (0x513c38, KBase730C's))
//   [x] 0x564838  CKS08MenuStartPlayer_Destroy  (inherited: TocBridge_CKMenuBase_114c_maybe_Destroy)
//   [x] 0x564860  CKS08MenuStartPlayer_DeleteArray
//   [ ] 0x564900  RegisterCKS08MenuStartPlayerClass
//   [ ] 0x564988  _GLOBAL__D_564988
//   [ ] 0x564998  _GLOBAL__I_564998
//   [x] 0x5649a8  CKS08MenuStartPlayer_vfE8
//   [ ] 0x564af8  CKS08MenuStartPlayer_Construct_2  [dead]
//   [x] 0x564ba0  CKS08MenuStartPlayer_CreateArray
//   [x] 0x564ce0  CKS08MenuStartPlayer_Create
//   [x] 0x564dc8  CKS08MenuStartPlayer_Destructor_2  (the same as 0x565038 CKS08MenuStartPlayer_Destructor)
//   [x] 0x564f00  CKS08MenuStartPlayer_DeletingDestructor  (the deleting form of 0x565038 CKS08MenuStartPlayer_Destructor)
//   [x] 0x565038  CKS08MenuStartPlayer_Destructor  (~CKMenuBase114c inlined (the same frees as 0x5642d8, checked))
//   [x] 0x565170  CKS08MenuStatsGame_Delete  (DOTD_DECLARE_FACTORIES(CKS08MenuStatsGame))
//   [ ] 0x5651c0  Time_SplitSecondsToHMS  [dead]
//
//   [x] 0x9ca3a8  CKS08MenuStartPlayer_IsKindOfClass  [inline]
//   [x] 0x9ca3e8  CKS08MenuStartPlayer_GetClassType  [inline]
//   [x] 0x9ca3f0  CKS08MenuStartPlayer_GetClassID  [inline]
//   [x] 0x9ca3f8  CKS08MenuStartPlayer_vfB8  [inline]
//   [x] 0x9ca400  CKS08MenuStartPlayer_vfE0  [inline]
//   [x] 0x9ca408  CKS08MenuStartPlayer_vfC4  [inline]
//   [x] 0x9ca410  CKS08MenuStartPlayer_vfC8  [inline]
//   [x] 0x9ca420  CKS08MenuStartPlayer_vfCC  [inline]
//   [x] 0x9ca430  CKS08MenuStartPlayer_vfBC  [inline]
//   [x] 0x9ca438  CKS08MenuStartPlayer_vfC0  [inline]
//   [x] 0x9ca448  CKS08MenuStartPlayer_vfF0  [inline]
//   [x] 0x9ca450  CKS08MenuStartPlayer_vfF4  [inline]
#include "Spyro2008/logic/ui/CKS08MenuStartPlayer.h"

#include "Spyro2008/logic/CKS08GameManager.h"

// 0x005647c0 CKS08MenuStartPlayer_Load (through TocBridge_CKMenuBase_114c_maybe_Load 0x98f720)
int32_t CKS08MenuStartPlayer::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    return 1;
}

// 0x00564778 CKS08MenuStartPlayer_vfDC
uint8_t CKS08MenuStartPlayer::OnMenuState(int32_t /*phase*/, uint8_t /*other*/) { return static_cast<uint8_t>(GetMenuId()); }

// 0x005649a8 CKS08MenuStartPlayer_vfE8
void CKS08MenuStartPlayer::OnItemState(uint8_t item, uint8_t state, uint8_t phase) {
    if (state != 4 || phase != 1) return;
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(m_pGameManager);
    if (item == 1) {
        manager->m_unk270 = 2;
    } else if (item == 0) {
        manager->m_unk270 = 1;
    } else {
        if (item == 2) MenuGm_RequestMenu(manager, manager->VfC4() != 0 ? 3 : 6);
        return;
    }
    manager->RequestSpawnPointLevel();  // vt+0x2e8
}
