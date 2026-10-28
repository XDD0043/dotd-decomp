// CKGrpBonusPool_2.cpp - reconstructed original translation unit 0x5b1668-0x5b4840 (GAME_TOC2, main_toc2), 30 functions, 25 live.
// Primary owner: CKGrpBonusPool (not a registered class)
// Other owners: CKHkBasicBonus (2), Bonus (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x5b1668  CKGrpBonusPool_ReleaseBonusFx_maybe
//   [ ] 0x5b16e8  CKGrpBonusPool_DestroyArray
//   [x] 0x5b1788  CKGrpBonusPool_Create
//   [ ] 0x5b1800  CKGrpBonusPool_SpawnBonus_maybe
//   [ ] 0x5b1918  CKGrpBonusPool_BonusList_Remove_maybe  [dead]
//   [ ] 0x5b1990  CKGrpBonusPool_vf10C
//   [ ] 0x5b1b58  CKGrpBonusPool_vf108
//   [ ] 0x5b1c50  CKGrpBonusPool_ReleaseAllActive_maybe
//   [ ] 0x5b1db8  CKGrpBonusPool_vf118
//   [ ] 0x5b1e48  CKGrpBonusPool_vf114
//   [ ] 0x5b1eb0  CKGrpBonusPool_vfF8
//   [x] 0x5b1f10  CKGrpBonusPool_ResetPool_maybe
//   [ ] 0x5b1fe0  CKGrpBonusPool_vf40
//   [ ] 0x5b1fe8  CKGrpBonusPool_vf1C
//   [x] 0x5b23f8  CKGrpBonusPool_CreateArray
//   [ ] 0x5b24c8  CKGrpBonusPool_LevelReset
//   [ ] 0x5b25e8  CKGrpBonusPool_Save
//   [ ] 0x5b2610  CKGrpBonusPool_ClearReferences
//   [ ] 0x5b2670  CKGrpBonusPool_CountActiveBonuses_maybe
//   [ ] 0x5b2728  CKGrpBonusPool_ClearBeaconBitsOfType_maybe  [dead]
//   [ ] 0x5b28e8  CKGrpBonusPool_UpdateBonuses_maybe
//   [x] 0x5b3240  CKGrpBonusPool_Load
//   [ ] 0x5b3630  CKGrpBonusPool_TriggerCollectEffects_maybe  [dead]
//   [ ] 0x5b3958  CKGrpBonusPool_AcquireBonusFx_maybe
//   [ ] 0x5b3bc0  Bonus_TriggerCollectExplosion_maybe
//   [ ] 0x5b3e50  CKGrpBonusPool_StopBonusTrail_maybe
//   [ ] 0x5b3ea8  CKGrpBonusPool_ResetBonusTrail_maybe
//   [ ] 0x5b4778  CKHkBasicBonus_Destroy
//   [ ] 0x5b47c8  CKHkBasicBonus_SetFlagBitfields_maybe  [dead]
//   [ ] 0x5b4828  FUN_005b4828  [dead]
//
//   [ ] 0x9cc008  CKGrpBonusPool_vf11C  [inline]
//   [x] 0x9cc408  CKGrpBonusPool_GetClassGroup  [inline]
//   [x] 0x9cc410  CKGrpBonusPool_GetClassId  [inline]
//   [ ] 0x9cc418  CKGrpBonusPool_vfCC  [inline]
//   [ ] 0x9cc420  CKGrpBonusPool_vf120  [inline]
//   [ ] 0x9cc438  CKGrpBonusPool_vf124  [inline]
//   [ ] 0x9cc440  CKGrpBonusPool_vf128  [inline]
//   [ ] 0x9cc448  CKGrpBonusPool_vf12C  [inline]
//   [ ] 0x9cc450  CKGrpBonusPool_IsKindOf  [inline]
//   [ ] 0x9cc4a8  CKGrpBonusPool_DeletingDestructor  [inline]
//   [ ] 0x9cc4f8  CKGrpBonusPool_Destructor  [inline]
//   [ ] 0x9cc518  KBase1C42_IsKindOf  [inline]
//   [ ] 0x9cc560  KBase1C42_GetClassGroup  [inline]
//   [ ] 0x9cc568  KBase1C42_GetClassId  [inline]
#include "k2000/memory/CKGrpBonusPool.h"
#include "Spyro2008/ui/CKHkS08Bonus.h"

// 0x005b3240 CKGrpBonusPool_Load. The original tests "type not 4..7" and then type 0.
int32_t CKGrpBonusPool::Load(IKFile* file, int32_t type) {
    GroupBasicLoad(file, type);
    if (static_cast<uint32_t>(type) - 4u <= 3u || type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_ui32BonusType);
    ReadU32LE(file, &m_ui32BonusBeaconID);
    ReadU32LE(file, &m_ui32MaxSimultaneousBonusOnBeacon);
    ReadF32LE(file, &m_fFarDistance);
    ReadU8(file, &m_unk3c);
    IKFile_ReadObjectRefArray(file, &m_pFirstUsed, 4);  // +0x40..+0x4c
    IKFile_ReadRef(file, &m_pStaticParticles);
    IKFile_ReadRef(file, &m_pCatchedParticles);
    IKFile_ReadRef(file, &m_pUnk58);
    ReadU32LE(file, &m_unk5c);
    ReadU8(file, &m_unk60);
    return 1;
}

// 0x005b1f10 CKGrpBonusPool_ResetPool_maybe. The pool's hooks are bonus hooks (CKHkS08Bonus here: +0x20 and
// +0x24 are its free-list link and index).
void CKGrpBonusPool::ResetPool() {
    m_pFirstUsed = nullptr;
    m_pFirstBeaconed = nullptr;
    IKHook* hook = *reinterpret_cast<IKHook**>(GetMemberListHead());  // vt+0xb0
    m_pFirstFree = hook;
    uint32_t index = 0;
    while (hook != nullptr) {
        CKHkS08Bonus* bonus = static_cast<CKHkS08Bonus*>(hook);
        bonus->m_unk24 = index;
        bonus->m_pUnk20 = bonus->m_pNextHook;
        hook = bonus->m_pNextHook;
        ++index;
    }
    m_bitArray &= 0xfffffe7fu;
    m_unk68 = 0;
    m_unk64 = 0;
}
