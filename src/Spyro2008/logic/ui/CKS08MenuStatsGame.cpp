// CKS08MenuStatsGame.cpp - reconstructed original translation unit 0x565218-0x567768 (GAME_TOC2, main_toc2), 21 functions, 19 live.
// Primary class: CKS08MenuStatsGame  key 0xaa0c  category Logic  size ?  vtable 0xb2d4c8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x565218  CKS08MenuStatsGame_PollBackButton_maybe
//   [ ] 0x565378  CKS08MenuStatsGame_HandleInput_maybe
//   [ ] 0x565600  CKS08MenuStatsGame_OnItemEvent
//   [ ] 0x565648  CKS08MenuStatsGame_RecursiveRegistration
//   [ ] 0x5656b8  CKS08MenuStatsGame_Destroy
//   [x] 0x5656e0  CKS08MenuStatsGame_DeleteArray
//   [ ] 0x565780  RegisterCKS08MenuStatsGameClass
//   [ ] 0x565808  _GLOBAL__D_565808
//   [ ] 0x565818  _GLOBAL__I_565818
//   [ ] 0x565828  CKS08MenuStatsGame_Construct  [dead]
//   [ ] 0x5658d0  CKS08MenuStatsGame_Save
//   [ ] 0x565a18  CKS08MenuStatsGame_Construct_2  [dead]
//   [x] 0x565ac0  CKS08MenuStatsGame_Create
//   [x] 0x565ba8  CKS08MenuStatsGame_CreateArray
//   [x] 0x565ce8  CKS08MenuStatsGame_Load
//   [ ] 0x565e28  CKS08MenuStatsGame_Destructor
//   [ ] 0x565f60  CKS08MenuStatsGame_Destructor_2
//   [ ] 0x566098  CKS08MenuStatsGame_DeletingDestructor
//   [ ] 0x5661d0  CKS08MenuStatsGame_RefreshCollectibleCounters_maybe
//   [ ] 0x567048  CKS08MenuStatsGame_BuildSaveDetailText_maybe
//   [ ] 0x5671e8  CKS08MenuStatsGame_OnMenuState_maybe
//
//   [x] 0x9ca458  CKS08MenuStatsGame_IsKindOfClass  [inline]
//   [x] 0x9ca498  CKS08MenuStatsGame_GetClassType  [inline]
//   [x] 0x9ca4a0  CKS08MenuStatsGame_GetClassID  [inline]
//   [x] 0x9ca4a8  CKS08MenuStatsGame_vfB8  [inline]
//   [x] 0x9ca4b0  CKS08MenuStatsGame_vfE0  [inline]
//   [x] 0x9ca4b8  CKS08MenuStatsGame_vfC4  [inline]
//   [x] 0x9ca4c0  CKS08MenuStatsGame_vfC8  [inline]
//   [x] 0x9ca4d0  CKS08MenuStatsGame_vfCC  [inline]
//   [x] 0x9ca4e0  CKS08MenuStatsGame_vfBC  [inline]
//   [x] 0x9ca4e8  CKS08MenuStatsGame_vfC0  [inline]
//   [x] 0x9ca4f8  CKS08MenuStatsGame_GetWidgetSlotCount  [inline]
//   [x] 0x9ca500  CKS08MenuStatsGame_GetWidgetSlots  [inline]
//   [ ] 0x9ca510  CKS08MenuStatsGame_vfE4  [inline]
#include "Spyro2008/logic/ui/CKS08MenuStatsGame.h"

#include "k2000/io/IKFile.h"

// 0x00565ce8 CKS08MenuStatsGame_Load: no type test of its own, so its fields are read whatever the type.
int32_t CKS08MenuStatsGame::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    ReadRaw(file, &m_unk138, 4);
    ReadRaw(file, &m_unk13c, 4);
    IKFile_ReadRef(file, &m_pText);
    return 1;
}
