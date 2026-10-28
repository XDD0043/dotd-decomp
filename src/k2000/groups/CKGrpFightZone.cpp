// CKGrpFightZone.cpp - reconstructed original translation unit 0x26df60-0x274b00 (GAME_TOC1, main_toc1), 89 functions, 76 live.
// Primary class: CKGrpFightZone  key 0x17c4  category Group  size 0x114  vtable 0xb21d30
// Other owners: KBaseDC6 (4), GetEnemyGroup (1), CKS08FightZoneCpnt (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x26df60  CKGrpFightZone_Delete
//   [ ] 0x26dfb0  CKGrpFightZone_Construct  [dead]
//   [ ] 0x26e0d0  CKGrpFightZone_vfB8
//   [ ] 0x26e0d8  CKGrpFightZone_vf94
//   [ ] 0x26e0e0  CKGrpFightZone_Stop
//   [ ] 0x26e0e8  GetEnemyGroup_3
//   [ ] 0x26e100  CKGrpFightZone_SetFlagBit6_maybe  [dead]
//   [ ] 0x26e120  CKGrpFightZone_IsSpawningAllowed_maybe
//   [ ] 0x26e148  CKGrpFightZone_SetDefaultState
//   [ ] 0x26e158  CKGrpFightZone_SetGameState
//   [ ] 0x26e1a0  CKGrpFightZone_RemoveFighter
//   [ ] 0x26e2c0  RegisterCKGrpFightZoneClass
//   [ ] 0x26e338  _GLOBAL__I_26e338
//   [ ] 0x26e348  CKGrpFightZone_SetCompleted_maybe
//   [ ] 0x26e398  CKGrpFightZone_ForceEndFight_maybe
//   [ ] 0x26e4e8  CKGrpFightZone_PostLoad
//   [ ] 0x26e558  CKGrpFightZone_StartFight_maybe
//   [x] 0x26e610  CKGrpFightZone_DeleteArray
//   [ ] 0x26e6b0  CKGrpFightZone_Construct_2  [dead]
//   [ ] 0x26e7d0  CKGrpFightZone_EnableMembers
//   [ ] 0x26e840  CKGrpFightZone_IsSpawningFinishedAndSquadsEmpty_maybe  [dead]
//   [ ] 0x26e968  CKGrpFightZone_DisableMembers
//   [ ] 0x26e9d8  CKGrpFightZone_AddFighter
//   [ ] 0x26eab8  CKGrpFightZone_RecursiveRegistration
//   [ ] 0x26ec80  CKGrpFightZone_Save
//   [ ] 0x26eca8  CKGrpFightZone_Destroy
//   [x] 0x26ed08  CKGrpFightZone_Start
//   [ ] 0x26eda8  CKGrpFightZone_Restart
//   [x] 0x26ee48  CKGrpFightZone_CreateArray
//   [x] 0x26efd0  CKGrpFightZone_Create
//   [x] 0x26f108  CKGrpFightZone_Load
//   [ ] 0x270268  CKGrpFightZone_EndFightIfActive_maybe
//   [ ] 0x2703d8  CKGrpFightZone_UpdateZoneTriggers_maybe
//   [ ] 0x270c18  UpdateCKGrpFightZone
//   [ ] 0x270d80  CKGrpFightZone_StopFight
//   [ ] 0x270ef0  CKGrpFightZone_MessageProc
//   [ ] 0x271648  CKGrpFightZone_GetFlagBit6Property_maybe
//   [ ] 0x271658  CKGrpFightZone_CallRef30Vf0C0Property_maybe
//   [ ] 0x2716b8  CKGrpFightZone_AnySquadHasField50Property_maybe
//   [ ] 0x271720  CKGrpFightZone_CallRef34Vf0C0Property_maybe
//   [ ] 0x271780  CKGrpFightZone_CallRef38Vf0C0IfRef30Property_maybe
//   [ ] 0x2717e0  CKGrpFightZone_CallRef30Vf0C0IfRef38Property_maybe
//   [ ] 0x271840  CKGrpFightZone_CallRef2CVf6CProperty_maybe
//   [ ] 0x271888  FUN_00271888  [dead]
//   [ ] 0x2718d0  CKGrpFightZone_GetMinHeroDistanceToPoint_maybe
//   [ ] 0x2719e8  CKGrpFightZone_GetTotalSquadCount_maybe
//   [ ] 0x271a90  CKGrpFightZone_GetTypeKilledCount_maybe
//   [ ] 0x271ab0  CKGrpFightZone_ResetKilledCounts_maybe
//   [ ] 0x271af0  CKGrpFightZone_GetTypeSpawnCap_maybe
//   [ ] 0x271b38  CKGrpFightZone_GetTotalSpawnCap_maybe
//   [ ] 0x271bb8  CKGrpFightZone_GetTotalKilledCount_maybe
//   [ ] 0x271c08  CKGrpFightZone_GetTotalSpawnedCount_maybe
//   [ ] 0x271c58  CKGrpFightZone_GetTypeSpawnedCount_maybe
//   [ ] 0x271c88  CKGrpFightZone_GetTotalRemainingEnemies_maybe
//   [ ] 0x271d38  CKGrpFightZone_GetTypeSquadCount_maybe
//   [ ] 0x271de0  CKGrpFightZone_GetTypeRemainingEnemies_maybe
//   [ ] 0x271e68  CKGrpFightZone_GetInfo
//   [ ] 0x272290  CKGrpFightZone_IsCleared_maybe
//   [ ] 0x2723c8  CKGrpFightZone_IsSpawnCapReached_maybe
//   [ ] 0x272430  CKGrpFightZone_GetFirstSquadExcluding_maybe  [dead]
//   [ ] 0x272478  CKGrpFightZone_AddSpawnedCount_maybe
//   [ ] 0x272500  CKGrpFightZone_FindSquadWithTypeCount_maybe  [dead]
//   [ ] 0x272600  CKGrpFightZone_FindSquadMissingSpawnsOfType_maybe  [dead]
//   [ ] 0x272708  CKGrpFightZone_TransferEnemyToSquad_maybe
//   [ ] 0x272978  CKGrpFightZone_TransferEnemiesBetweenSquads_maybe  [dead]
//   [ ] 0x272ac0  CKGrpFightZone_TickSpawnPointCooldowns_maybe
//   [ ] 0x272b40  CKGrpFightZone_SpawnAllSquadsFullFormation_maybe
//   [ ] 0x272b90  CKGrpFightZone_QueueSpawnsForAllSquads_maybe
//   [ ] 0x272bf0  CKGrpFightZone_AnySquadWantsSpawn_maybe
//   [ ] 0x272c80  CKGrpFightZone_ScheduleSquadRespawns_maybe
//   [ ] 0x272cd0  CKGrpFightZone_ClearTriggerStates_maybe
//   [ ] 0x272d10  CKGrpFightZone_ResetEnemyTypeCounts_maybe
//   [ ] 0x272d70  CKGrpFightZone_GetLastSquadExcluding_maybe  [dead]
//   [ ] 0x272dd8  CKGrpFightZone_SpawnAtSpawnPoint_maybe
//   [ ] 0x272ff8  CKGrpFightZone_TrySpawnRequest_maybe
//   [ ] 0x2732a8  CKGrpFightZone_ProcessSpawnRequests_maybe
//   [ ] 0x273398  CKGrpFightZone_SelectSpawnPoints_maybe
//   [ ] 0x2739a0  CKGrpFightZone_ProcessSquadTransfers_maybe
//   [ ] 0x273b68  CKGrpFightZone_QueueTransfersForRequest_maybe
//   [ ] 0x274698  CKGrpFightZone_QueueEntrySpawns_maybe
//   [x] 0x274a70  KBaseDC6_Load
//   [ ] 0x274a78  KBaseDC6_Save
//   [ ] 0x274a80  KBaseDC6_LevelReset
//   [ ] 0x274a88  KBaseDC6_ClearReferences
//   [ ] 0x274a90  CKS08FightZoneCpnt_Delete
//   [ ] 0x274ae0  KStub_Return0_274ae0
//   [ ] 0x274ae8  KStub_Return0_274ae8  [dead]
//   [ ] 0x274af0  KStub_Nop_274af0  [dead]
//   [ ] 0x274af8  KStub_Nop_274af8  [dead]
//
//   [x] 0x9bbfc0  CKGrpFightZone_GetClassType  [inline]
//   [x] 0x9bbfc8  CKGrpFightZone_GetClassID  [inline]
//   [ ] 0x9bbfd0  CKGrpFightZone_vfCC  [inline]
//   [ ] 0x9bbfd8  CKGrpFightZone_Pause  [inline]
//   [ ] 0x9bbfe0  CKGrpFightZone_Resume  [inline]
//   [ ] 0x9bbfe8  CKGrpFightZone_IsKindOfClass  [inline]
//   [ ] 0x9bc040  CKGrpFightZone_Destructor  [inline]
//   [ ] 0x9bc210  CKGrpFightZone_DeletingDestructor  [inline]
//   [ ] 0x9bc3f0  KBaseDC6_GetClassGroup  [inline]
//   [ ] 0x9bc3f8  KBaseDC6_GetClassId  [inline]
//   [ ] 0x9bc400  KBaseDC6_vf58  [inline]
//   [ ] 0x9bc408  KBaseDC6_vf5C  [inline]
//   [ ] 0x9bc410  KBaseDC6_vf60  [inline]
//   [ ] 0x9bc420  KBaseDC6_vf68  [inline]
//   [ ] 0x9bc428  KBaseDC6_vf6C  [inline]
//   [ ] 0x9bc430  KBaseDC6_vf70  [inline]
//   [ ] 0x9bc438  KBaseDC6_vf74  [inline]
//   [ ] 0x9bc440  KBaseDC6_vf78  [inline]
//   [ ] 0x9bc448  KBaseDC6_vf7C  [inline]
//   [ ] 0x9bc450  KBaseDC6_DeletingDestructor  [inline]
//   [ ] 0x9bc490  KBaseDC6_IsKindOf  [inline]
//   [ ] 0x9bc4b0  KBaseDC6_Destructor  [inline]
#include "k2000/groups/CKGrpFightZone.h"

#include "Spyro2008/components/CKS08FightZoneCpnt.h"
#include "k2000/groups/TVectorPush.h"
#include "k2000/core/Stub.h"

namespace {
void ReadVector3(IKFile* file, CVector3& v) {  // one 0xc-byte read, three swaps
    ReadF32LE(file, &v.x);
    ReadF32LE(file, &v.y);
    ReadF32LE(file, &v.z);
}
}  // namespace

// 0x0026f108 CKGrpFightZone_Load
int32_t CKGrpFightZone::Load(IKFile* file, int32_t type) {
    GroupBasicLoad(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_unk3c);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    TVector_ResizeForLoad(m_vUnk40, count);
    for (uint32_t i = 0; i < count; ++i) IKFile_ReadRef(file, &m_vUnk40.m_pBlock[i]);

    ReadU32LE(file, &count);
    TVector_ResizeForLoad(m_vUnk4c, count);
    for (uint32_t i = 0; i < count; ++i) {
        SEntry4c& e = m_vUnk4c.m_pBlock[i];
        IKFile_ReadRef(file, &e.m_pRef);
        ReadU8(file, &e.m_unk04);
        ReadU16LE(file, &e.m_unk06);
    }
    ReadU32LE(file, &m_unk58);
    ReadU32LE(file, &m_unk5c);

    ReadU32LE(file, &count);
    TVector_ResizeForLoad(m_vUnk64, count);
    for (uint32_t i = 0; i < count; ++i) {
        SEntry64& e = m_vUnk64.m_pBlock[i];
        ReadVector3(file, e.m_v00);
        ReadVector3(file, e.m_v0c);
        ReadU8(file, &e.m_unk18);
        e.m_unk1c = 0;
    }

    ReadU32LE(file, &count);
    TVector_ResizeForLoad(m_vUnk70, count);
    for (uint32_t i = 0; i < count; ++i) {
        SEntry70& e = m_vUnk70.m_pBlock[i];
        ReadVector3(file, e.m_v00);
        ReadVector3(file, e.m_v0c);
        ReadU8(file, &e.m_unk18);
        ReadU8(file, &e.m_unk19);
        ReadU8(file, &e.m_unk1a);
        ReadU8(file, &e.m_unk20);
        IKFile_ReadRef(file, &e.m_pRef);
    }
    ReadU32LE(file, &m_unk84);

    ReadU32LE(file, &count);
    TVector_ResizeForLoad(m_vUnk8c, count);
    for (uint32_t i = 0; i < count; ++i) {
        SEntry8c& e = m_vUnk8c.m_pBlock[i];
        ReadU8(file, &e.m_unk00);
        ReadU8(file, &e.m_unk01);
        ReadU8(file, &e.m_unk02);
        IKFile_ReadRef(file, &e.m_pRef04);
        IKFile_ReadRef(file, &e.m_pRef08);
    }

    ReadU32LE(file, &count);
    TVector_ResizeForLoad(m_vUnk9c, count);
    for (uint32_t i = 0; i < count; ++i) ReadVector3(file, m_vUnk9c.m_pBlock[i]);
    ReadU8(file, &m_unka8);

    // CTriggerStarter_Load (0x2361c0) on +0xac..+0xdc and +0xf4..+0x104 (indices 0..6, 9..11).
    static const int kFirst[] = {0, 1, 2, 3, 4, 5, 6, 9, 10, 11};
    for (int i : kFirst) m_aTriggers[i].Load(file, K_LEVEL_PLATEFORMS);
    IKFile_ReadRef(file, &m_pFightZoneCpnt);
    m_pFightZoneCpnt->SetFightZone(this);  // vt+0x64 of the component (0x9bc418)
    m_aTriggers[7].Load(file, K_LEVEL_PLATEFORMS);  // +0xe4
    m_aTriggers[8].Load(file, K_LEVEL_PLATEFORMS);  // +0xec
    IKFile_ReadRef(file, &m_pUnk30);
    IKFile_ReadRef(file, &m_pUnk34);
    IKFile_ReadRef(file, &m_pUnk38);
    ReadU8(file, &m_unk10f);
    return 1;
}

// 0x0026ed08 CKGrpFightZone_Start: bits 5-6 and 8-10 of the flags cleared, the run-time bytes cleared, the trigger
// states and enemy counts reset, then the zone component's vt+0x60.
void CKGrpFightZone::Start() {
    m_bitArray &= 0xfffff89fu;
    m_unk110 = 0;
    m_unk10c[0] = 0;
    m_unk10c[1] = 0;
    ClearTriggerStates();
    ResetEnemyTypeCounts();
    m_pFightZoneCpnt->Vf60();  // vt+0x60 0x274dd8
}

// 0x00272cd0 CKGrpFightZone_ClearTriggerStates_maybe
void CKGrpFightZone::ClearTriggerStates() {
    for (uint32_t i = 0; i < m_vUnk64.m_ui32NbUsedElt; ++i) m_vUnk64.m_pBlock[i].m_unk1c = 0;
}

// 0x00272d10 CKGrpFightZone_ResetEnemyTypeCounts_maybe
void CKGrpFightZone::ResetEnemyTypeCounts() {
    for (uint32_t i = 0; i < m_vUnk4c.m_ui32NbUsedElt; ++i) {
        m_vUnk4c.m_pBlock[i].m_unk08 &= 0xffffu;  // the halfword at +0x08 (the BE high half of m_unk08)
        m_vUnk4c.m_pBlock[i].m_unk0c = 0;
    }
    m_unk88 = 0;
}
