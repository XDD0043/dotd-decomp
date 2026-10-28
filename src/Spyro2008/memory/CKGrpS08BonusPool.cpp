// CKGrpS08BonusPool.cpp - reconstructed original translation unit 0x5af6a8-0x5b0c58 (GAME_TOC2, main_toc2), 37 functions, 31 live.
// Primary owner: CKGrpS08BonusPool (not a registered class)
// Other owners: CKGrpBonus (6), CKGrpBonusPool (1), RegisterCKGrpS08BonusPoolClass (1), UpdateCKGrpS08BonusPool (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x5af6a8  CKGrpS08BonusPool_Destroy
//   [ ] 0x5af6f8  CKGrpS08BonusPool_Construct  [dead]
//   [ ] 0x5af760  CKGrpS08BonusPool_Construct_2  [dead]
//   [ ] 0x5af7c8  CKGrpS08BonusPool_vfB8
//   [ ] 0x5af7d0  CKGrpS08BonusPool_vf120
//   [ ] 0x5af7f8  CKGrpS08BonusPool_vf128
//   [ ] 0x5af800  CKGrpBonusPool_PlayCollectFx_maybe
//   [ ] 0x5afa90  CKGrpS08BonusPool_UpdateBonuses_maybe
//   [ ] 0x5afab8  CKGrpS08BonusPool_vf1C
//   [ ] 0x5afb10  CKGrpS08BonusPool_PostLoad
//   [ ] 0x5afb38  CKGrpS08BonusPool_LevelReset
//   [ ] 0x5afc00  CKGrpS08BonusPool_ClearReferences
//   [ ] 0x5afc28  CKGrpS08BonusPool_DestroyArray
//   [ ] 0x5afcd0  RegisterCKGrpS08BonusPoolClass
//   [ ] 0x5afd58  _GLOBAL__D_5afd58
//   [ ] 0x5afd68  _GLOBAL__I_5afd68
//   [ ] 0x5afd78  CKGrpS08BonusPool_CanHeroCollect_maybe
//   [ ] 0x5affd0  CKGrpS08BonusPool_ApplyBonusToHero_maybe
//   [ ] 0x5b0540  UpdateCKGrpS08BonusPool
//   [ ] 0x5b0548  CKGrpS08BonusPool_vf78
//   [ ] 0x5b0550  CKGrpS08BonusPool_vf68
//   [ ] 0x5b0558  CKGrpS08BonusPool_vf70
//   [ ] 0x5b0560  CKGrpS08BonusPool_vf50
//   [x] 0x5b0568  CKGrpS08BonusPool_CreateArray
//   [x] 0x5b0640  CKGrpS08BonusPool_Create
//   [ ] 0x5b06c0  CKGrpS08BonusPool_LaunchBonusProjectile_maybe  [dead]
//   [x] 0x5b08b0  CKGrpS08BonusPool_Load
//   [ ] 0x5b0970  CKGrpS08BonusPool_Save
//   [ ] 0x5b0a30  CKGrpS08BonusPool_Destructor_2  [dead]
//   [ ] 0x5b0a58  CKGrpS08BonusPool_DeletingDestructor
//   [ ] 0x5b0ab0  CKGrpS08BonusPool_Destructor
//   [ ] 0x5b0ad8  CKGrpBonus_Destroy
//   [ ] 0x5b0b28  CKGrpBonus_vfB8
//   [ ] 0x5b0b30  CKGrpBonus_FindChildByKey2C_maybe  [dead]
//   [ ] 0x5b0b88  CKGrpBonus_SetChildrenFlag80_maybe  [dead]
//   [x] 0x5b0bc8  CKGrpBonus_ResetRuntime
//   [ ] 0x5b0c30  CKGrpBonus_PostLoad
//
//   [ ] 0x9cc010  CKGrpS08BonusPool_IsKindOf  [inline]
//   [x] 0x9cc070  CKGrpS08BonusPool_GetClassGroup  [inline]
//   [x] 0x9cc078  CKGrpS08BonusPool_GetClassId  [inline]
//   [ ] 0x9cc080  CKGrpS08BonusPool_vfCC  [inline]
#include "Spyro2008/memory/CKGrpS08BonusPool.h"

// 0x005b08b0 CKGrpS08BonusPool_Load
int32_t CKGrpS08BonusPool::Load(IKFile* file, int32_t type) {
    CKGrpBonusPool::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pUnk6c);
    return 1;
}

// 0x005b0bc8 CKGrpBonus_ResetRuntime: calls vt+0xec of every child group and drops the result. Those slots are
// getters in every group class (CKGrpS08Enemy 0x9bb648, the pools 0x9bb948 / 0x9bbbd8 / 0x9bbe80 return a
// constant, KBaseBCC 0x9912a8 returns 0), so nothing changes state: the walk is not reproduced.
void CKGrpS08BonusPool::ResetRuntime() {}
