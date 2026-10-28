// CKHkS08Bonus.cpp - reconstructed original translation unit 0x5b7098-0x5b9f08 (GAME_TOC2, main_toc2), 31 functions, 30 live.
// Primary owner: CKHkS08Bonus (not a registered class)
// Other owners: RegisterCKHkS08BonusClass (1), BonusGem (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x5b7098  CKHkS08Bonus_SeekNearestHero_maybe
//   [ ] 0x5b7278  CKHkS08Bonus_UpdateTrailEndpoints_maybe
//   [ ] 0x5b72c0  CKHkS08Bonus_SetRotationDeg_maybe
//   [ ] 0x5b7390  CKHkS08Bonus_GetSplineLockLaunchData_maybe  [dead]
//   [ ] 0x5b73c0  CKHkS08Bonus_PlayCollectFx_maybe
//   [ ] 0x5b7418  CKHkS08Bonus_TriggerCollectExplosion_maybe
//   [ ] 0x5b7470  CKHkS08Bonus_ReturnToPool_maybe
//   [x] 0x5b74d8  CKHkS08Bonus_DestroyArray
//   [x] 0x5b7580  CKHkS08Bonus_Create
//   [ ] 0x5b7628  RegisterCKHkS08BonusClass
//   [ ] 0x5b76b0  _GLOBAL__D_5b76b0
//   [ ] 0x5b76c0  _GLOBAL__I_5b76c0
//   [ ] 0x5b76d0  CKHkS08Bonus_vfE4
//   [ ] 0x5b7758  CKHkS08Bonus_SetLaunchVelocity_maybe
//   [ ] 0x5b7890  CKHkS08Bonus_DisableAndReleaseFx_maybe
//   [ ] 0x5b78f8  CKHkS08Bonus_SetVisible
//   [ ] 0x5b7a58  CKHkS08Bonus_ClearReferences
//   [x] 0x5b7a60  CKHkS08Bonus_CreateArray
//   [ ] 0x5b7b60  CKHkS08Bonus_LevelReset
//   [x] 0x5b7bf0  CKHkS08Bonus_Load
//   [ ] 0x5b7db0  CKHkS08Bonus_Save
//   [ ] 0x5b7f88  CKHkS08Bonus_SpawnAtPosition_maybe
//   [ ] 0x5b8178  CKHkS08Bonus_SpawnAt_maybe
//   [ ] 0x5b8448  CKHkS08Bonus_JitterDirection_maybe
//   [ ] 0x5b8590  CKHkS08Bonus_InitFlyToHeroCurve_maybe
//   [ ] 0x5b8900  BonusGem_Collect
//   [ ] 0x5b8ba0  CKHkS08Bonus_UpdateSpin_maybe
//   [ ] 0x5b8cf8  CKHkS08Bonus_UpdateFlyToHero_maybe
//   [ ] 0x5b9428  CKHkS08Bonus_ResolveBounceCollision_maybe
//   [ ] 0x5b9988  CKHkS08Bonus_UpdateBouncePhysics_maybe
//   [ ] 0x5b9c28  CKHkS08Bonus_Update
//
//   [ ] 0x9cc850  CKHkS08Bonus_GetClassGroup  [inline]
//   [ ] 0x9cc858  CKHkS08Bonus_GetClassId  [inline]
//   [ ] 0x9cc860  CKHkS08Bonus_vfCC  [inline]
//   [ ] 0x9cc880  CKHkS08Bonus_IsKindOf  [inline]
//   [ ] 0x9cc8d8  CKHkS08Bonus_Destructor  [inline]
//   [ ] 0x9cc8f8  CKHkS08Bonus_DeletingDestructor  [inline]
//   [ ] 0x9cc948  KBase606_vf8  [inline]
//   [ ] 0x9cc970  KBase606_vf14  [inline]
//   [ ] 0x9cc978  KBase606_vf18  [inline]
//   [ ] 0x9cc980  KBase606_vf10  [inline]
#include "Spyro2008/ui/CKHkS08Bonus.h"

#include "k2000/io/IKFile.h"

// 0x005b7bf0 CKHkS08Bonus_Load
int32_t CKHkS08Bonus::Load(IKFile* file, int32_t type) {
    IKHook::Load(file, type);  // through TocBridge_CKHook_Load
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pUnk20);
    IKFile_ReadRef(file, &m_pUnk28);
    IKFile_ReadRef(file, &m_pUnk2C);
    return 1;
}
