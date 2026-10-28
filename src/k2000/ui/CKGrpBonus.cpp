// CKGrpBonus.cpp - reconstructed original translation unit 0x5b0ce0-0x5b1348 (GAME_TOC2, main_toc2), 14 functions, 13 live.
// Primary owner: CKGrpBonus (not a registered class)
// Other owners: BonusPool (1), UpdateCKGrpBonus (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x5b0ce0  CKGrpBonus_DestroyArray
//   [x] 0x5b0d80  CKGrpBonus_Create
//   [ ] 0x5b0df8  BonusPool_SpawnBonusObject
//   [ ] 0x5b0e90  CKGrpBonus_ReinitRuntime
//   [ ] 0x5b0ef8  UpdateCKGrpBonus
//   [ ] 0x5b0f70  CKGrpBonus_OnLevelExit_maybe
//   [ ] 0x5b0fd8  CKGrpBonus_vf40
//   [x] 0x5b0fe0  CKGrpBonus_CreateArray
//   [ ] 0x5b10b0  CKGrpBonus_vf1C
//   [ ] 0x5b1188  CKGrpBonus_TriggerChildCollectEffects_maybe  [dead]
//   [ ] 0x5b1210  CKGrpBonus_LevelReset
//   [x] 0x5b1298  CKGrpBonus_Load
//   [ ] 0x5b12c0  CKGrpBonus_Save
//   [ ] 0x5b12e8  CKGrpBonus_ClearReferences
//
//   [x] 0x9cc318  CKGrpBonus_GetClassGroup  [inline]
//   [x] 0x9cc320  CKGrpBonus_GetClassId  [inline]
//   [ ] 0x9cc328  CKGrpBonus_vfCC  [inline]
//   [ ] 0x9cc330  CKGrpBonus_vf70  [inline]
//   [ ] 0x9cc338  CKGrpBonus_vf78  [inline]
//   [ ] 0x9cc340  CKGrpBonus_IsKindOf  [inline]
//   [ ] 0x9cc398  CKGrpBonus_DeletingDestructor  [inline]
//   [ ] 0x9cc3e8  CKGrpBonus_Destructor  [inline]
#include "k2000/ui/CKGrpBonus.h"

// 0x005b1298 CKGrpBonus_Load: GroupBasicLoad only (through its TOC bridge).
int32_t CKGrpBonus::Load(IKFile* file, int32_t type) {
    GroupBasicLoad(file, type);
    return 1;
}
