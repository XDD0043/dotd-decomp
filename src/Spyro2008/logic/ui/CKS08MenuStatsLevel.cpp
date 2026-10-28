// CKS08MenuStatsLevel.cpp - reconstructed original translation unit 0x568f08-0x56aee8 (GAME_TOC2, main_toc2), 22 functions, 19 live.
// Primary class: CKS08MenuStatsLevel  key 0xa9cc  category Logic  size ?  vtable 0xb2d6d8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x568f08  CKS08MenuStatsLevel_Delete
//   [ ] 0x568f58  CKS08MenuStatsLevel_SetTitleTextByIndex_maybe  [dead]
//   [ ] 0x568fd8  CKS08MenuStatsLevel_PollBackButton_maybe
//   [ ] 0x569138  CKS08MenuStatsLevel_HandleInput_maybe
//   [ ] 0x5693c0  CKS08MenuStatsLevel_RecursiveRegistration
//   [ ] 0x569430  CKS08MenuStatsLevel_Destroy
//   [x] 0x569458  CKS08MenuStatsLevel_DeleteArray
//   [ ] 0x5694f8  RegisterCKS08MenuStatsLevelClass
//   [ ] 0x569580  _GLOBAL__D_569580
//   [ ] 0x569590  _GLOBAL__I_569590
//   [ ] 0x5695a0  CKS08MenuStatsLevel_OnItemEvent
//   [ ] 0x5695e8  CKS08MenuStatsLevel_Construct  [dead]
//   [ ] 0x569690  CKS08MenuStatsLevel_Construct_2  [dead]
//   [x] 0x569738  CKS08MenuStatsLevel_CreateArray
//   [x] 0x569878  CKS08MenuStatsLevel_Create
//   [x] 0x569960  CKS08MenuStatsLevel_Load
//   [ ] 0x569aa0  CKS08MenuStatsLevel_Save
//   [ ] 0x569be8  CKS08MenuStatsLevel_DeletingDestructor
//   [ ] 0x569d20  CKS08MenuStatsLevel_Destructor
//   [ ] 0x569e58  CKS08MenuStatsLevel_Destructor_2
//   [ ] 0x569f90  CKS08MenuStatsLevel_RefreshStatTexts_maybe
//   [ ] 0x56ab38  CKS08MenuStatsLevel_OnMenuState_maybe
//
//   [x] 0x9ca5e8  CKS08MenuStatsLevel_IsKindOfClass  [inline]
//   [x] 0x9ca628  CKS08MenuStatsLevel_GetClassType  [inline]
//   [x] 0x9ca630  CKS08MenuStatsLevel_GetClassID  [inline]
//   [x] 0x9ca638  CKS08MenuStatsLevel_vfB8  [inline]
//   [x] 0x9ca640  CKS08MenuStatsLevel_vfE0  [inline]
//   [x] 0x9ca648  CKS08MenuStatsLevel_vfC4  [inline]
//   [x] 0x9ca650  CKS08MenuStatsLevel_vfC8  [inline]
//   [x] 0x9ca660  CKS08MenuStatsLevel_vfCC  [inline]
//   [x] 0x9ca670  CKS08MenuStatsLevel_vfBC  [inline]
//   [x] 0x9ca678  CKS08MenuStatsLevel_vfC0  [inline]
//   [x] 0x9ca688  CKS08MenuStatsLevel_GetWidgetSlotCount  [inline]
//   [x] 0x9ca690  CKS08MenuStatsLevel_GetWidgetSlots  [inline]
//   [ ] 0x9ca6a0  CKS08MenuStatsLevel_vfE4  [inline]
#include "Spyro2008/logic/ui/CKS08MenuStatsLevel.h"

#include "k2000/io/IKFile.h"

// 0x00569960 CKS08MenuStatsLevel_Load: no type test of its own, so its fields are read whatever the type.
int32_t CKS08MenuStatsLevel::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    ReadRaw(file, &m_unk120, 4);
    ReadRaw(file, &m_unk124, 4);
    IKFile_ReadRef(file, &m_pText);
    return 1;
}
