// CKS08MenuStatsHeroes.cpp - reconstructed original translation unit 0x567768-0x568f08 (GAME_TOC2, main_toc2), 21 functions, 18 live.
// Primary class: CKS08MenuStatsHeroes  key 0xa98c  category Logic  size ?  vtable 0xb2d5d0
// Other owners: Time (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x567768  CKS08MenuStatsHeroes_Delete
//   [ ] 0x5677b8  CKS08MenuStatsHeroes_Construct  [dead]
//   [ ] 0x567860  Time_SplitSecondsToHMS_2  [dead]
//   [ ] 0x5678b8  CKS08MenuStatsHeroes_HandlePageInput_maybe
//   [ ] 0x567b00  CKS08MenuStatsHeroes_OnItemEvent
//   [x] 0x567b48  CKS08MenuStatsHeroes_Load
//   [ ] 0x567b70  CKS08MenuStatsHeroes_Save
//   [ ] 0x567b98  CKS08MenuStatsHeroes_RecursiveRegistration
//   [ ] 0x567bc0  CKS08MenuStatsHeroes_Destroy
//   [x] 0x567be8  CKS08MenuStatsHeroes_DeleteArray
//   [ ] 0x567c88  RegisterCKS08MenuStatsHeroesClass
//   [ ] 0x567d10  _GLOBAL__D_567d10
//   [ ] 0x567d20  _GLOBAL__I_567d20
//   [ ] 0x567d30  CKS08MenuStatsHeroes_Construct_2  [dead]
//   [x] 0x567dd8  CKS08MenuStatsHeroes_CreateArray
//   [x] 0x567f18  CKS08MenuStatsHeroes_Create
//   [ ] 0x568000  CKS08MenuStatsHeroes_Destructor_2
//   [ ] 0x568138  CKS08MenuStatsHeroes_DeletingDestructor
//   [ ] 0x568270  CKS08MenuStatsHeroes_Destructor
//   [ ] 0x5683a8  CKS08MenuStatsHeroes_RefreshStatTexts_maybe
//   [ ] 0x568cc0  CKS08MenuStatsHeroes_OnMenuState_maybe
//
//   [x] 0x9ca518  CKS08MenuStatsHeroes_IsKindOfClass  [inline]
//   [x] 0x9ca558  CKS08MenuStatsHeroes_GetClassType  [inline]
//   [x] 0x9ca560  CKS08MenuStatsHeroes_GetClassID  [inline]
//   [x] 0x9ca568  CKS08MenuStatsHeroes_vfB8  [inline]
//   [x] 0x9ca570  CKS08MenuStatsHeroes_vfE0  [inline]
//   [x] 0x9ca578  CKS08MenuStatsHeroes_vfC4  [inline]
//   [x] 0x9ca580  CKS08MenuStatsHeroes_vfC8  [inline]
//   [x] 0x9ca590  CKS08MenuStatsHeroes_vfCC  [inline]
//   [x] 0x9ca5a0  CKS08MenuStatsHeroes_vfBC  [inline]
//   [x] 0x9ca5a8  CKS08MenuStatsHeroes_vfC0  [inline]
//   [x] 0x9ca5b8  CKS08MenuStatsHeroes_GetWidgetSlotCount  [inline]
//   [x] 0x9ca5c0  CKS08MenuStatsHeroes_GetWidgetSlots  [inline]
//   [ ] 0x9ca5d0  CKS08MenuStatsHeroes_vfF0  [inline]
//   [ ] 0x9ca5d8  CKS08MenuStatsHeroes_vfF4  [inline]
//   [ ] 0x9ca5e0  CKS08MenuStatsHeroes_vfE4  [inline]
#include "Spyro2008/logic/ui/CKS08MenuStatsHeroes.h"

// 0x00567b48 CKS08MenuStatsHeroes_Load (through TocBridge_CKMenuBase_114c_maybe_Load 0x98f720)
int32_t CKS08MenuStatsHeroes::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    return 1;
}
