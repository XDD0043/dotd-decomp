// CKGrpFightZone.cpp - reconstructed original translation unit 0x26df60-0x274b00 (GAME_TOC1, main_toc1), 89 functions, 76 live.
// Primary class: CKGrpFightZone  key 0x17c4  category Group  size 0x114  vtable 0xb21d30
// Other owners: KBaseDC6 (4), GetEnemyGroup (1), CKS08FightZoneCpnt (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x26df60  CKGrpFightZone_Delete
//   [ ] 0x26dfb0  CKGrpFightZone_Construct  [dead]
//   [ ] 0x26e0d0  CKGrpFightZone_vfB8  [dead: vt+0xb8 (returns 1), called only by the dead CKCoreManager 0x1c330 / 0x1d460 (raw ELF scan of the vt+0xb8 calls)]
//   [x] 0x26e0d8  CKGrpFightZone_vf94  (empty: the IKBaseGroup default)
//   [x] 0x26e0e0  CKGrpFightZone_Stop  (empty: the IKBaseGroup default)
//   [x] 0x26e0e8  GetEnemyGroup_3
//   [ ] 0x26e100  CKGrpFightZone_SetFlagBit6_maybe  [dead]
//   [x] 0x26e120  CKGrpFightZone_IsSpawningAllowed_maybe
//   [x] 0x26e148  CKGrpFightZone_SetDefaultState
//   [x] 0x26e158  CKGrpFightZone_SetGameState
//   [ ] 0x26e1a0  CKGrpFightZone_RemoveFighter  [dead: vt+0xc8, called only by the dead Group_RemoveHook_maybe 0x12860 (raw ELF scan of the vt+0xc8 calls)]
//   [ ] 0x26e2c0  RegisterCKGrpFightZoneClass
//   [ ] 0x26e338  _GLOBAL__I_26e338
//   [x] 0x26e348  CKGrpFightZone_SetCompleted_maybe
//   [x] 0x26e398  CKGrpFightZone_ForceEndFight_maybe
//   [x] 0x26e4e8  CKGrpFightZone_PostLoad
//   [ ] 0x26e558  CKGrpFightZone_StartFight_maybe  [dead: no pointer to its descriptor 0xb89658, no call]
//   [x] 0x26e610  CKGrpFightZone_DeleteArray
//   [ ] 0x26e6b0  CKGrpFightZone_Construct_2  [dead]
//   [x] 0x26e7d0  CKGrpFightZone_EnableMembers
//   [ ] 0x26e840  CKGrpFightZone_IsSpawningFinishedAndSquadsEmpty_maybe  [dead]
//   [x] 0x26e968  CKGrpFightZone_DisableMembers
//   [ ] 0x26e9d8  CKGrpFightZone_AddFighter  [dead: vt+0xc4, called only by the dead Group_AddHook_maybe 0x12ba0 (raw ELF scan of the vt+0xc4 calls)]
//   [x] 0x26eab8  CKGrpFightZone_RecursiveRegistration
//   [ ] 0x26ec80  CKGrpFightZone_Save
//   [x] 0x26eca8  CKGrpFightZone_Destroy  (header)
//   [x] 0x26ed08  CKGrpFightZone_Start
//   [x] 0x26eda8  CKGrpFightZone_Restart
//   [x] 0x26ee48  CKGrpFightZone_CreateArray
//   [x] 0x26efd0  CKGrpFightZone_Create
//   [x] 0x26f108  CKGrpFightZone_Load
//   [ ] 0x270268  CKGrpFightZone_EndFightIfActive_maybe  [dead: no pointer to its descriptor 0xb897b0, no call]
//   [x] 0x2703d8  CKGrpFightZone_UpdateZoneTriggers_maybe
//   [x] 0x270c18  UpdateCKGrpFightZone
//   [x] 0x270d80  CKGrpFightZone_StopFight
//   [x] 0x270ef0  CKGrpFightZone_MessageProc
//   [x] 0x271648  CKGrpFightZone_GetFlagBit6Property_maybe
//   [x] 0x271658  CKGrpFightZone_CallRef30Vf0C0Property_maybe
//   [x] 0x2716b8  CKGrpFightZone_AnySquadHasField50Property_maybe
//   [x] 0x271720  CKGrpFightZone_CallRef34Vf0C0Property_maybe
//   [x] 0x271780  CKGrpFightZone_CallRef38Vf0C0IfRef30Property_maybe
//   [x] 0x2717e0  CKGrpFightZone_CallRef30Vf0C0IfRef38Property_maybe
//   [x] 0x271840  CKGrpFightZone_CallRef2CVf6CProperty_maybe
//   [ ] 0x271888  FUN_00271888  [dead]
//   [x] 0x2718d0  CKGrpFightZone_GetMinHeroDistanceToPoint_maybe
//   [x] 0x2719e8  CKGrpFightZone_GetTotalSquadCount_maybe
//   [x] 0x271a90  CKGrpFightZone_GetTypeKilledCount_maybe
//   [ ] 0x271ab0  CKGrpFightZone_ResetKilledCounts_maybe  [dead: no pointer to its descriptor 0xb89ae8, no call]
//   [x] 0x271af0  CKGrpFightZone_GetTypeSpawnCap_maybe
//   [x] 0x271b38  CKGrpFightZone_GetTotalSpawnCap_maybe
//   [x] 0x271bb8  CKGrpFightZone_GetTotalKilledCount_maybe
//   [x] 0x271c08  CKGrpFightZone_GetTotalSpawnedCount_maybe
//   [x] 0x271c58  CKGrpFightZone_GetTypeSpawnedCount_maybe
//   [x] 0x271c88  CKGrpFightZone_GetTotalRemainingEnemies_maybe
//   [x] 0x271d38  CKGrpFightZone_GetTypeSquadCount_maybe
//   [x] 0x271de0  CKGrpFightZone_GetTypeRemainingEnemies_maybe
//   [x] 0x271e68  CKGrpFightZone_GetInfo
//   [x] 0x272290  CKGrpFightZone_IsCleared_maybe
//   [x] 0x2723c8  CKGrpFightZone_IsSpawnCapReached_maybe
//   [ ] 0x272430  CKGrpFightZone_GetFirstSquadExcluding_maybe  [dead]
//   [x] 0x272478  CKGrpFightZone_AddSpawnedCount_maybe
//   [ ] 0x272500  CKGrpFightZone_FindSquadWithTypeCount_maybe  [dead]
//   [ ] 0x272600  CKGrpFightZone_FindSquadMissingSpawnsOfType_maybe  [dead]
//   [x] 0x272708  CKGrpFightZone_TransferEnemyToSquad_maybe
//   [ ] 0x272978  CKGrpFightZone_TransferEnemiesBetweenSquads_maybe  [dead]
//   [x] 0x272ac0  CKGrpFightZone_TickSpawnPointCooldowns_maybe
//   [x] 0x272b40  CKGrpFightZone_SpawnAllSquadsFullFormation_maybe
//   [x] 0x272b90  CKGrpFightZone_QueueSpawnsForAllSquads_maybe
//   [x] 0x272bf0  CKGrpFightZone_AnySquadWantsSpawn_maybe
//   [x] 0x272c80  CKGrpFightZone_ScheduleSquadRespawns_maybe
//   [x] 0x272cd0  CKGrpFightZone_ClearTriggerStates_maybe
//   [x] 0x272d10  CKGrpFightZone_ResetEnemyTypeCounts_maybe
//   [ ] 0x272d70  CKGrpFightZone_GetLastSquadExcluding_maybe  [dead]
//   [x] 0x272dd8  CKGrpFightZone_SpawnAtSpawnPoint_maybe
//   [x] 0x272ff8  CKGrpFightZone_TrySpawnRequest_maybe
//   [x] 0x2732a8  CKGrpFightZone_ProcessSpawnRequests_maybe
//   [x] 0x273398  CKGrpFightZone_SelectSpawnPoints_maybe
//   [x] 0x2739a0  CKGrpFightZone_ProcessSquadTransfers_maybe
//   [x] 0x273b68  CKGrpFightZone_QueueTransfersForRequest_maybe
//   [x] 0x274698  CKGrpFightZone_QueueEntrySpawns_maybe
//   [x] 0x274a70  KBaseDC6_Load
//   [ ] 0x274a78  KBaseDC6_Save
//   [x] 0x274a80  KBaseDC6_LevelReset  (KBaseDC6's RecursiveRegistration: returns 1, registers nothing: the default)
//   [x] 0x274a88  KBaseDC6_ClearReferences  (empty)
//   [x] 0x274a90  CKS08FightZoneCpnt_Delete  (the Delete factory: DOTD_DECLARE_FACTORIES(CKS08FightZoneCpnt))
//   [x] 0x274ae0  KStub_Return0_274ae0  (CKGrpS08Enemy.h ReleaseAttackSlotOf: nothing)
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

#include "k2000/core/IKInfo.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/components/CKS08FightZoneCpnt.h"
#include "Spyro2008/groups/CKChoreoKey.h"
#include "Spyro2008/groups/CKGrpS08Enemy.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "Spyro2008/hooks/IKHkHero.h"
#include "Spyro2008/hooks/IKHkEnemy.h"
#include "crt/ppc_ops.h"
#include "crt/xsinf.h"
#include "k2000/ai/CKHkDetectorGroup.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/core/Stub.h"
#include "k2000/groups/CKGrpSquad.h"
#include "k2000/groups/TVectorPush.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKCoreManager.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/IKGrpEnemy.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CKSrvTrigger.h"
#include "k2000/system/IKTime.h"

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
        ReadU16LE(file, reinterpret_cast<uint16_t*>(&e.m_unk06));
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
        e.m_fCooldown = 0.0f;
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
    ReadU32LE(file, reinterpret_cast<uint32_t*>(&m_unk84));

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

// 0x0026e148 CKGrpFightZone_SetDefaultState
void CKGrpFightZone::SetDefaultState(int32_t /*flag*/) { m_unk10e = 1; }

// 0x0026e158 CKGrpFightZone_SetGameState: the byte is the sign bit of |state| - 1 (srawi / xor / subf / subi /
// rlwinm 1,31,31), so 1 for state 0 only (INT_MIN gives 0 too: its |x| - 1 wraps to INT_MAX).
int32_t CKGrpFightZone::SetGameState(const SApplyGameState* state) {
    if (state->m_ui32InfoId != 0x2a && state->m_ui32InfoId != 0x2c) return 0;
    const uint32_t value = state->m_ui32GameStateId;
    const uint32_t sign = static_cast<uint32_t>(static_cast<int32_t>(value) >> 31);
    m_unk10e = static_cast<uint8_t>((((value ^ sign) - sign) - 1u) >> 31);
    return 1;
}

// 0x0026ed08 CKGrpFightZone_Start: bits 5-6 and 8-10 of the flags cleared, the run-time bytes cleared, the trigger
// states and enemy counts reset, then the zone component's vt+0x60.
void CKGrpFightZone::Start() {
    m_bitArray &= 0xfffff89fu;
    m_unk110 = 0;
    m_unk10c = 0;
    m_unk10d = 0;
    ClearTriggerStates();
    ResetEnemyTypeCounts();
    m_pFightZoneCpnt->Vf60();  // vt+0x60 0x274dd8
}

// 0x0026eda8 CKGrpFightZone_Restart (vt+0x54): the same body as Start.
void CKGrpFightZone::Restart() {
    m_bitArray &= 0xfffff89fu;  // and -0x221, and -0x541
    m_unk110 = 0;
    m_unk10c = 0;
    m_unk10d = 0;
    ClearTriggerStates();
    ResetEnemyTypeCounts();
    m_pFightZoneCpnt->Vf60();  // vt+0x60 0x274dd8
}

// 0x00272cd0 CKGrpFightZone_ClearTriggerStates_maybe
void CKGrpFightZone::ClearTriggerStates() {
    for (uint32_t i = 0; i < m_vUnk64.m_ui32NbUsedElt; ++i) m_vUnk64.m_pBlock[i].m_fCooldown = 0.0f;
}

// 0x00272d10 CKGrpFightZone_ResetEnemyTypeCounts_maybe
void CKGrpFightZone::ResetEnemyTypeCounts() {
    for (uint32_t i = 0; i < m_vUnk4c.m_ui32NbUsedElt; ++i) {
        m_vUnk4c.m_pBlock[i].m_unk08 = 0;
        m_vUnk4c.m_pBlock[i].m_unk0c = 0;
    }
    m_unk88 = 0;
}

namespace {
// DOTD: the FreeListPool 0x00ceaa20 nodes of the zone's lists (the 8-, 12- and 16-byte pools): a free list per node
// type. A freed node's first word links the free list, as on the PS3; FreeListPool_Grow becomes a new node.
template <class T>
struct NodePool {
    static T* s_pFree;
    static T* Take() {
        if (s_pFree == nullptr) return new T();
        T* node = s_pFree;
        std::memcpy(&s_pFree, node, sizeof(T*));
        return node;
    }
    static void Give(T* node) {
        std::memcpy(node, &s_pFree, sizeof(T*));
        s_pFree = node;
    }
};
template <class T>
T* NodePool<T>::s_pFree = nullptr;

// 0x0026e0e8 GetEnemyGroup_3: the game manager's enemy group (+0x04).
IKGrpEnemy* GetEnemyGroup() { return static_cast<IKGrpEnemy*>(g_pEngine->m_gameManager->m_unk04[0]); }

// vt+0xc0 of the zone's detector groups (CKHkDetectorGroup 0x9ccff0: the word +0x4c's bit 0, set by its update).
uint8_t DetectorHolds(IKSerializable* detector) {
    if (detector == nullptr) return 0;
    return static_cast<uint8_t>(static_cast<CKHkDetectorGroup*>(detector)->m_unk4C[0] & 1u);
}

// 0x00010690 Math_Sqrtf: the double square root rounded to float.
float MathSqrtf(float x) { return static_cast<float>(std::sqrt(static_cast<double>(x))); }

// 0x00363c78 IKHkHero_GetTargetingPositionPtr_maybe (IKHkHero_2.cpp, local copy as CKGrpSquad.cpp's): the hero's +0x570
// unless its bit 1 is set, then its scene node's frame's LTM position.
const CVector3* ZoneHeroTargetingPosition(IKSerializable* hero) {
    IKHkHero* h = static_cast<IKHkHero*>(hero);
    if ((h->m_bitArray & 2u) == 0) return reinterpret_cast<const CVector3*>(&h->m_unk570);
    return reinterpret_cast<const CVector3*>(&FrameLtm(static_cast<CSGMovable*>(h->m_pKGLObject)->m_pRwFrame)->pos);
}

// The game's inlined cosf: the inline polynomial for a non-negative argument (by its bits), the library cosf of -x
// otherwise.
float GameCosf(float x) {
    int32_t bits;
    std::memcpy(&bits, &x, 4);
    return bits < 0 ? crt::LibCosf(-x) : crt::InlineCosf(x);
}
}  // namespace

// The inlined block: every squad (the child groups) put to sleep, then the transfer and request lists emptied.
void CKGrpFightZone::SleepSquadsAndClearQueues() {
    CKCoreManager* core = g_pEngine->m_coreManager;
    for (IKBaseGroup* squad = m_lChilds; squad != nullptr; squad = squad->m_pNextGroup) SetObjectActive(core, squad, 0);
    for (STransferNode* node = m_unk98; node != nullptr;) {
        STransferNode* next = node->m_pNext;
        NodePool<STransferNode>::Give(node);
        node = next;
    }
    m_unk98 = nullptr;
    for (SSpawnRequest* node = m_unk80; node != nullptr;) {
        SSpawnRequest* next = node->m_pNext;
        NodePool<SSpawnRequest>::Give(node);
        node = next;
    }
    m_unk80 = nullptr;
}

// 0x0026e398 CKGrpFightZone_ForceEndFight_maybe (CKFightZoneSectorGrpRoot_Restart): the squads asleep and the queues
// emptied, the zone no longer the enemy group's current one (vt+0x160), the "fight ended" starter (+0xbc) fired; the
// same block the fight's end runs in UpdateZoneTriggers.
void CKGrpFightZone::ForceEndFight() {
    SleepSquadsAndClearQueues();
    GetEnemyGroup()->ClearCurrentFightZone(this);  // vt+0x160
    QueueTriggerSignals(&m_aTriggers[2]);         // +0xbc
}

// 0x00270d80 CKGrpFightZone_StopFight
void CKGrpFightZone::Vf98() {
    if ((m_bitArray & 0x20u) == 0) return;
    m_bitArray &= ~0x20u;
    SleepSquadsAndClearQueues();
    GetEnemyGroup()->ClearCurrentFightZone(this);  // vt+0x160
    QueueTriggerSignals(&m_aTriggers[2]);         // +0xbc
}

// 0x00270c18 UpdateCKGrpFightZone: the component's frame while bit 6 is set; the triggers when no zone (or this one)
// is the enemy group's current one; while bit 5 (the fight) is set, the spawn point cooldowns, the spawn requests, the
// transfers, the respawns (when the detectors hold and +0x10d is clear), and a new set of spawn points when a squad
// wants to spawn.
void CKGrpFightZone::Update(IKTime* clock) {
    if ((m_bitArray & 0x40u) != 0) m_pFightZoneCpnt->Update(clock);  // vt+0x5c 0x275058
    CKGrpFightZone* current = GetEnemyGroup()->m_pCurrentFightZone;
    if (current == nullptr || current == this) UpdateZoneTriggers();
    if ((m_bitArray & 0x20u) == 0) return;
    TickSpawnPointCooldowns(clock);
    ProcessSpawnRequests();
    ProcessSquadTransfers();
    if (m_unk10c != 0 && m_unk10d == 0) ScheduleSquadRespawns();
    if (AnySquadWantsSpawn() != 0) SelectSpawnPoints();
}

// 0x002703d8 CKGrpFightZone_UpdateZoneTriggers_maybe: the three detector groups (+0x34 inside, +0x30 entry, +0x38 exit)
// drive the flags 0x100 (inside), 0x400 (exit; cleared: the enemies get vt+0x124), 0x200 (entered), 0x40 (armed) and
// 0x20 (the fight), firing the matching trigger starters. The entry detector only counts while the exit one holds too.
// The fight starts (0x20 set, the zone made current) while inside and armed, and stops (the squads put to sleep, the
// queues emptied) when no longer armed.
void CKGrpFightZone::UpdateZoneTriggers() {
    // GetControlledHeroArray 0x2ca0e0 of the hero group (+0x08) is called first for nothing (a getter).
    const uint8_t inside = DetectorHolds(m_pUnk34);
    const uint8_t enter = DetectorHolds(m_pUnk30);
    const uint8_t exit = DetectorHolds(m_pUnk38);
    m_unk10c = 0;
    uint32_t flags = m_bitArray;
    if (inside != 0) {
        if ((flags & 0x100u) == 0 && (flags & 0x40u) != 0) {  // 0x270b44
            QueueTriggerSignals(&m_aTriggers[3]);               // +0xc4
            m_bitArray = (m_bitArray & ~0x100u) | 0x100u;
            if (m_unk10d == 0 && m_unk10e != 0) m_pFightZoneCpnt->Vf58();  // vt+0x58 0x274e08
            flags = m_bitArray;
        }
    } else if ((flags & 0x100u) != 0) {  // 0x270960
        QueueTriggerSignals(&m_aTriggers[4]);  // +0xcc
        m_bitArray &= ~0x100u;
        flags = m_bitArray;
    }
    bool entered = false;
    if (inside != 0 && exit != 0) {  // 0x2706b8
        if ((flags & 0x400u) == 0 && GetEnemyGroup()->m_ui32NbActiveEnemies == 0 && (flags & 0x40u) != 0) {
            QueueTriggerSignals(&m_aTriggers[7]);  // +0xe4
            m_bitArray = (m_bitArray & ~0x400u) | 0x400u;
            CKCoreManager* core = g_pEngine->m_coreManager;
            SleepSquadsAndClearQueues();
            if (m_unk10f != 0 || m_unk110 == 0) {
                ClearTriggerStates();
                ResetEnemyTypeCounts();
            }
            m_unk60 = m_unk5c;
            for (IKBaseGroup* squad = m_lChilds; squad != nullptr; squad = squad->m_pNextGroup) {
                SetObjectActive(core, squad, 1);
                if (m_unk10f != 0 || m_unk110 == 0) static_cast<CKGrpSquad*>(squad)->ResetMemberSlots();  // 0x25afe0
            }
            const uint32_t squads = m_vUnk40.m_ui32NbUsedElt;
            for (uint32_t i = 0; i != squads; ++i) static_cast<CKGrpSquad*>(m_vUnk40.m_pBlock[i])->ActivateSpawnCamera();
            flags = m_bitArray;
            m_unk110 = 1;
        }
        m_unk10c = 1;
        if (enter != 0) {  // 0x2708bc
            if ((flags & 0x200u) == 0 && (flags & 0x40u) != 0) {
                QueueTriggerSignals(&m_aTriggers[5]);  // +0xd4
                m_bitArray = (m_bitArray & ~0x200u) | 0x200u;
                flags = m_bitArray;
            }
            m_unk10c = 1;
            entered = true;
        }
    } else if ((flags & 0x400u) != 0) {  // 0x270998
        QueueTriggerSignals(&m_aTriggers[8]);  // +0xec
        m_bitArray &= ~0x400u;
        const uint32_t count = GetEnemyGroup()->m_ui32NbActiveEnemies;
        for (uint32_t i = 0; i != count; ++i) {
            static_cast<IKHkEnemy*>(GetEnemyGroup()->m_apActiveEnemies[i])->ForceState16();  // vt+0x124
        }
        flags = m_bitArray;
    }
    if (!entered && (flags & 0x200u) != 0) {  // 0x270a50
        QueueTriggerSignals(&m_aTriggers[6]);  // +0xdc
        m_bitArray &= ~0x200u;
        flags = m_bitArray;
    }
    if (inside != 0) {
        if (m_unka8 != 0 && (flags & 0x40u) == 0 && m_unk10e != 0) {  // 0x27090c
            m_bitArray = (m_bitArray & ~0x40u) | 0x40u;
            flags = m_bitArray;
        }
        if ((flags & 0x40u) != 0) {  // 0x270a80
            if ((flags & 0x20u) != 0) return;
            m_bitArray = (m_bitArray & ~0x20u) | 0x20u;
            if (m_unk10f != 0) {
                ClearTriggerStates();
                ResetEnemyTypeCounts();
            }
            m_unk60 = m_unk5c;
            GetEnemyGroup()->SetCurrentFightZone(this);  // vt+0x15c
            QueueTriggerSignals(&m_aTriggers[0]);       // +0xac
            return;
        }
    } else if ((flags & 0x40u) != 0) {  // 0x270bc8
        m_bitArray &= ~0x40u;
        flags = m_bitArray;
    }
    if ((flags & 0x20u) == 0) return;  // 0x27055c
    m_bitArray &= ~0x20u;              // 0x270568
    SleepSquadsAndClearQueues();
    GetEnemyGroup()->ClearCurrentFightZone(this);  // vt+0x160
    QueueTriggerSignals(&m_aTriggers[2]);         // +0xbc
}

// 0x00270ef0 CKGrpFightZone_MessageProc: the messages 0xd01..0xd15 (0 when handled, 1 otherwise, as the original's
// xori). `data` points to the message's argument (a byte at +0 or +3 of the big-endian word: TriggerParamByte0 /
// TriggerParamByte3, or the word).
int32_t CKGrpFightZone::MessageProc(uint16_t message, void* data) {
    uint32_t word = 0;
    switch (static_cast<uint16_t>(message - 0xd01)) {
        case 0x0:  // 0xd01: entry spawns, while fighting
            if ((m_bitArray & 0x20u) != 0) QueueEntrySpawns(TriggerParamByte3(data));
            return 0;
        case 0x1:  // 0xd02: every squad queues spawns to fill its formation, while fighting
            if ((m_bitArray & 0x20u) != 0) {
                std::memcpy(&word, data, 4);
                QueueSpawnsForAllSquads(word);
            }
            return 0;
        case 0x2:  // 0xd03
            if ((m_bitArray & 0x20u) != 0) SpawnAllSquadsFullFormation();
            return 0;
        case 0x3:  // 0xd04: the zone put to sleep
            SetObjectActive(g_pEngine->m_coreManager, this, 0);
            return 0;
        case 0x4:  // 0xd05: disarmed; the fight stops if it ran
            m_bitArray &= ~0x40u;
            if ((m_bitArray & 0x20u) != 0) {
                m_bitArray &= ~0x20u;
                SleepSquadsAndClearQueues();
                GetEnemyGroup()->ClearCurrentFightZone(this);  // vt+0x160
                QueueTriggerSignals(&m_aTriggers[2]);         // +0xbc
            }
            m_unk110 = 0;
            return 0;
        case 0x5:  // 0xd06
            if ((m_bitArray & 0x20u) != 0) QueueTransfersForRequest(TriggerParamByte3(data));
            return 0;
        case 0x7: {  // 0xd08: +0x60 raised, at most +0x58 - 1 (unsigned)
            std::memcpy(&word, data, 4);
            uint32_t limit = m_unk58 - 1;
            const uint32_t raised = m_unk60 + word;
            if (limit > raised) limit = raised;
            m_unk60 = limit;
            return 0;
        }
        case 0x8:  // 0xd09: +0x60 lowered, not below 0
            std::memcpy(&word, data, 4);
            m_unk60 = word >= m_unk60 ? 0 : m_unk60 - word;
            return 0;
        case 0x9:  // 0xd0a
            m_unk60 = m_unk5c;
            return 0;
        case 0xa:  // 0xd0b
            m_unk60 = 0;
            return 0;
        case 0xb:  // 0xd0c
            m_unk60 = m_unk58 - 1;
            return 0;
        case 0xc: {  // 0xd0d: armed (bit 6) from the byte (lbz 0(r5)); the fight starts (or, disarmed, stops)
            const uint8_t armed = TriggerParamByte0(data);
            m_bitArray = (m_bitArray & ~0x40u) | (static_cast<uint32_t>(armed) << 6);
            if (armed == 0) {
                if ((m_bitArray & 0x20u) == 0) return 0;
                m_bitArray &= ~0x20u;
                SleepSquadsAndClearQueues();
                GetEnemyGroup()->ClearCurrentFightZone(this);  // vt+0x160
                QueueTriggerSignals(&m_aTriggers[2]);         // +0xbc
                return 0;
            }
            if ((m_bitArray & 1u) != 0) SetObjectActive(g_pEngine->m_coreManager, this, 1);
            if ((m_bitArray & 0x20u) != 0) return 0;
            m_bitArray = (m_bitArray & ~0x20u) | 0x20u;
            if (m_unk10f != 0) {
                ClearTriggerStates();
                ResetEnemyTypeCounts();
            }
            m_unk60 = m_unk5c;
            GetEnemyGroup()->SetCurrentFightZone(this);  // vt+0x15c
            QueueTriggerSignals(&m_aTriggers[0]);       // +0xac
            return 0;
        }
        case 0xd:  // 0xd0e: the fight stops (bits 5, 6, 8 and 9 cleared)
            if ((m_bitArray & 0x20u) == 0) return 0;
            m_bitArray &= 0xfffffc9fu;
            SleepSquadsAndClearQueues();
            GetEnemyGroup()->ClearCurrentFightZone(this);  // vt+0x160
            QueueTriggerSignals(&m_aTriggers[2]);         // +0xbc
            return 0;
        case 0x10:  // 0xd11
            m_unk10e = 1;
            return 0;
        case 0x11:  // 0xd12
            m_unk10e = 0;
            return 0;
        case 0x12:  // 0xd13
            m_unk10d = 1;
            QueueTriggerSignals(&m_aTriggers[10]);  // +0xfc
            return 0;
        case 0x13:  // 0xd14: the component's vt+0x78 with vt+0x74 + 1
            m_pFightZoneCpnt->SetCountA8(m_pFightZoneCpnt->GetCountA8() + 1);
            return 0;
        case 0x14:  // 0xd15: the component's vt+0x7c with 1
            m_pFightZoneCpnt->Vf7C(1);
            return 0;
        default:  // 0xd07, 0xd0f, 0xd10 and the others
            return 1;
    }
}

// 0x00272ac0 CKGrpFightZone_TickSpawnPointCooldowns_maybe
void CKGrpFightZone::TickSpawnPointCooldowns(IKTime* clock) {
    for (uint32_t i = 0; m_vUnk64.m_ui32NbUsedElt > i; ++i) {
        SEntry64& point = m_vUnk64.m_pBlock[i];
        point.m_fCooldown = point.m_fCooldown - clock->m_afDeltaTime[0];
        if (point.m_fCooldown < 0.0f) point.m_fCooldown = 0.0f;  // TOC 0x94c
    }
}

// 0x00272b40 CKGrpFightZone_SpawnAllSquadsFullFormation_maybe
void CKGrpFightZone::SpawnAllSquadsFullFormation() {
    for (IKBaseGroup* squad = m_lChilds; squad != nullptr; squad = squad->m_pNextGroup) {
        static_cast<CKGrpSquad*>(squad)->SpawnFullFormation();
    }
}

// 0x00272b90 CKGrpFightZone_QueueSpawnsForAllSquads_maybe
void CKGrpFightZone::QueueSpawnsForAllSquads(uint32_t count) {
    for (IKBaseGroup* squad = m_lChilds; squad != nullptr; squad = squad->m_pNextGroup) {
        static_cast<CKGrpSquad*>(squad)->QueueSpawnsToFillFormation(count);
    }
}

// 0x00272bf0 CKGrpFightZone_AnySquadWantsSpawn_maybe
uint8_t CKGrpFightZone::AnySquadWantsSpawn() {
    for (IKBaseGroup* squad = m_lChilds; squad != nullptr; squad = squad->m_pNextGroup) {
        if (static_cast<CKGrpSquad*>(squad)->HasSpawnRequest() != 0) return 1;
    }
    return 0;
}

// 0x00272c80 CKGrpFightZone_ScheduleSquadRespawns_maybe
void CKGrpFightZone::ScheduleSquadRespawns() {
    for (IKBaseGroup* squad = m_lChilds; squad != nullptr; squad = squad->m_pNextGroup) {
        static_cast<CKGrpSquad*>(squad)->ScheduleRespawns();
    }
}

// 0x00272dd8 CKGrpFightZone_SpawnAtSpawnPoint_maybe: among the candidates (+0x7c), the first one the enemy's squad allows
// (its +0x38 byte per spawn point) and then any allowed one with a lower cooldown; while none is allowed, the one with
// the lowest cooldown (below FLT_MAX, the float at 0x00c4ace0). The enemy is placed there (vt+0xdc, with the point's flag
// bits above 3 masked by the enemy group's vt+0x158) and the point's cooldown raised by 3.
// BUG(original): when no candidate qualifies (all allowed ones absent and every cooldown at FLT_MAX), the index is a
// stale register; here it stays 0.
int32_t CKGrpFightZone::SpawnAtSpawnPoint(IKSerializable* enemy) {
    float best = 0x1.fffffep+127f;  // 0x00c4ace0 (0x7f7fffff)
    if (m_unk7c == nullptr) return 0;
    const uint8_t* allowed = static_cast<const uint8_t*>(static_cast<CKGrpSquad*>(static_cast<IKHkEnemy*>(enemy)->m_pGroupSquad)->m_vUnk38.m_pBlock);
    bool found = false;
    uint32_t index = 0;
    for (SSpawnPointNode* node = m_unk7c; node != nullptr; node = node->m_pNext) {
        const uint32_t candidate = node->m_index;
        const float cooldown = m_vUnk64.m_pBlock[candidate].m_fCooldown;
        if (allowed[candidate] != 0) {
            if (!found || cooldown < best) {
                best = cooldown;
                index = candidate;
                found = true;
            }
        } else if (!found && cooldown < best) {
            best = cooldown;
            index = candidate;
        }
    }
    SEntry64& point = m_vUnk64.m_pBlock[index];
    const uint32_t bits = GetEnemyGroup()->GetSpawnFlagBits();  // vt+0x158
    const uint32_t flags = (static_cast<uint32_t>(point.m_unk18) >> 3) & ~ppc::slw(0xffu, bits) & 0x1fu;
    CVector3 position = point.m_v00;
    CVector3 direction = point.m_v0c;
    static_cast<IKHkEnemy*>(enemy)->SpawnAtPosition(&position, &direction, flags);  // vt+0xdc
    m_vUnk64.m_pBlock[index].m_fCooldown = m_vUnk64.m_pBlock[index].m_fCooldown + 3.0f;  // TOC 0x958
    return 1;
}

// 0x00272ff8 CKGrpFightZone_TrySpawnRequest_maybe: spawns the request's enemies one by one at its +0x70 entry until its
// count runs out (1), the zone's or the type's cap stops it (1; the squad's pending count of the type cleared), or the
// squad has no enemy to give (0).
uint8_t CKGrpFightZone::TrySpawnRequest(SSpawnRequest* request) {
    uint8_t left = request->m_count;
    for (;;) {
        --left;
        if (left == 0xff) return 1;
        for (;;) {
            const uint8_t type = request->m_type;
            SEntry4c& kind = m_vUnk4c.m_pBlock[type];
            bool typeFull = false;
            if (kind.m_unk06 >= 0) typeFull = static_cast<int32_t>(kind.m_unk08) >= kind.m_unk06;
            CKGrpSquad* squad = static_cast<CKGrpSquad*>(request->m_pSquad);
            if ((m_unk84 >= 0 && m_unk88 >= m_unk84) || typeFull) {
                squad->m_vUnk2c.m_pBlock[type].m_unk02 = 0;
                return 1;
            }
            IKSerializable* enemy = squad->SpawnMember(type);  // 0x260f38
            if (enemy == nullptr) return 0;
            SEntry70& entry = m_vUnk70.m_pBlock[request->m_entry];
            CVector3 position = entry.m_v00;
            CVector3 direction = entry.m_v0c;
            static_cast<IKHkEnemy*>(enemy)->SpawnAtPosition(&position, &direction, entry.m_unk18);  // vt+0xdc
            request->m_count = static_cast<uint8_t>(request->m_count - 1);
            CKGrpSquad::SFlags& counts = static_cast<CKGrpSquad*>(request->m_pSquad)->m_vUnk2c.m_pBlock[request->m_type];
            counts.m_unk00 = static_cast<uint8_t>(counts.m_unk00 + 1);
            counts.m_unk02 = static_cast<uint8_t>(counts.m_unk02 - 1);
            ++m_unk88;
            if (m_unk84 != -1 && m_unk88 >= m_unk84) m_unk88 = m_unk84;
            SEntry4c& spawned = m_vUnk4c.m_pBlock[request->m_type];
            const int16_t cap = spawned.m_unk06;
            spawned.m_unk08 = static_cast<uint16_t>(spawned.m_unk08 + 1);
            if (cap == -1 || static_cast<int32_t>(spawned.m_unk08) < cap) break;
            --left;
            spawned.m_unk08 = static_cast<uint16_t>(cap);
            if (left == 0xff) return 1;
        }
    }
}

// 0x002732a8 CKGrpFightZone_ProcessSpawnRequests_maybe: the requests that are done are unlinked and freed.
void CKGrpFightZone::ProcessSpawnRequests() {
    SSpawnRequest* prev = nullptr;
    SSpawnRequest* node = m_unk80;
    while (node != nullptr) {
        if (TrySpawnRequest(node) == 0) {
            prev = node;
            node = node->m_pNext;
        } else if (m_unk80 == node) {
            SSpawnRequest* next = node->m_pNext;
            NodePool<SSpawnRequest>::Give(node);
            m_unk80 = next;
            prev = nullptr;
            node = next;
        } else {
            SSpawnRequest* next = node->m_pNext;
            prev->m_pNext = next;
            NodePool<SSpawnRequest>::Give(node);
            node = next;
        }
    }
}

// 0x00273398 CKGrpFightZone_SelectSpawnPoints_maybe: the candidate list (+0x7c) rebuilt. From a random first index
// (Rand_Int), every spawn point is tested once against the camera (its position and look direction, the view cone at
// 1.5 x half the field of view) by its mode (+0x18 bits 0-2: 0 always, 1 out of view, 2 in view and facing away from the
// camera (its direction +0x0c, farther than 2.5), 3 out of view or facing away, 4 in view; other modes loop forever
// in the original and are never in the data). Without any candidate, every point is listed from a second random index.
void CKGrpFightZone::SelectSpawnPoints() {
    for (SSpawnPointNode* node = m_unk7c; node != nullptr;) {
        SSpawnPointNode* next = node->m_pNext;
        NodePool<SSpawnPointNode>::Give(node);
        node = next;
    }
    m_unk7c = nullptr;
    const uint32_t count = m_vUnk64.m_ui32NbUsedElt;
    if (count == 0) return;
    const uint32_t first = static_cast<uint32_t>(Rand_Int());  // 0x00011500
    CKSrvCamera* camera = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);
    const float camY = camera->m_v3RealPos.y;
    const float camX = camera->m_v3RealPos.x;
    const float camZ = camera->m_v3RealPos.z;
    float lookY = camera->m_v3RealTarget.y - camY;
    float lookX = camera->m_v3RealTarget.x - camX;
    float lookZ = camera->m_v3RealTarget.z - camZ;
    float length = lookY * lookY;
    length = ppc::fmadds(lookX, lookX, length);
    length = ppc::fmadds(lookZ, lookZ, length);
    length = MathSqrtf(length);
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        lookZ = lookZ * inverse;
        lookX = lookX * inverse;
        lookY = lookY * inverse;
    }
    float halfAngle = camera->m_fRealFov * 1.5f;  // TOC 0x990
    halfAngle = halfAngle * 0x1.1df468p-6f;       // TOC 0x994 (0x3c8efa34, pi/180)
    halfAngle = halfAngle * 0.5f;                 // TOC 0x998
    const float cosHalf = GameCosf(halfAngle);
    uint32_t index = (count * (first & 0xffffu)) >> 16;
    for (uint32_t left = count; left != 0;) {
        const SEntry64& point = m_vUnk64.m_pBlock[index];
        float dy = point.m_v00.y - camY;
        float dx = point.m_v00.x - camX;
        float dz = point.m_v00.z - camZ;
        float distance = dy * dy;
        distance = ppc::fmadds(dx, dx, distance);
        distance = ppc::fmadds(dz, dz, distance);
        distance = MathSqrtf(distance);
        if (distance == 0.0f) {
            distance = 0.0f;
        } else {
            const float inverse = 1.0f / distance;
            dz = dz * inverse;
            dx = dx * inverse;
            dy = dy * inverse;
        }
        GetEnemyGroup()->GetSpawnFlagBits();  // vt+0x158, its result unused
        const uint32_t mode = m_vUnk64.m_pBlock[index].m_unk18 & 7u;
        if (mode > 4) continue;  // BUG(original): neither the index nor the count moves (an endless loop)
        float view = dy * lookY;
        view = ppc::fmadds(lookX, dx, view);
        view = ppc::fmadds(lookZ, dz, view);
        bool facesAway = false;
        if ((mode == 2 || mode == 3) && distance > 2.5f) {  // TOC 0x9a4
            float facing = dy * point.m_v0c.y;
            facing = ppc::fmadds(dx, point.m_v0c.x, facing);
            facing = ppc::fmadds(dz, point.m_v0c.z, facing);
            facesAway = facing < -0.7f;  // TOC 0x9a8 (0xbf333333)
        }
        bool add;
        switch (mode) {
            case 0: add = true; break;
            case 1: add = view < cosHalf; break;
            case 2: add = facesAway && view >= cosHalf; break;
            case 3: add = cosHalf > view || (facesAway && cosHalf <= view); break;
            default: add = view > cosHalf; break;
        }
        if (add) {
            SSpawnPointNode* node = NodePool<SSpawnPointNode>::Take();
            node->m_pNext = nullptr;
            node->m_index = static_cast<uint8_t>(index);
            node->m_pNext = m_unk7c;
            m_unk7c = node;
        }
        --left;
        ++index;
        if (count <= index) index = 0;
    }
    if (m_unk7c != nullptr) return;
    // No candidate: every point from a second random index.
    const uint32_t second = static_cast<uint32_t>(Rand_Int()) & 0xffffu;  // 0x00011500
    float scaled = static_cast<float>(static_cast<double>(second)) / 65535.0f;  // TOC 0x9ac
    scaled = scaled * static_cast<float>(static_cast<double>(count));
    uint32_t next = static_cast<uint32_t>(ppc::fctidz(scaled));
    for (uint32_t left = count; left != 0; --left) {
        SSpawnPointNode* node = NodePool<SSpawnPointNode>::Take();
        node->m_index = static_cast<uint8_t>(next);
        ++next;
        node->m_pNext = nullptr;
        node->m_pNext = m_unk7c;
        m_unk7c = node;
        if (count <= next) next = 0;
    }
}

// 0x002739a0 CKGrpFightZone_ProcessSquadTransfers_maybe: each transfer moves its enemies one by one
// (TransferEnemyToSquad) and keeps both squads' per-type counters (bytes 0 and 3) in step; a finished transfer is
// unlinked and freed, a stalled one stays.
void CKGrpFightZone::ProcessSquadTransfers() {
    STransferNode* prev = nullptr;
    STransferNode* node = m_unk98;
    while (node != nullptr) {
        uint8_t left = static_cast<uint8_t>(node->m_count - 1);
        bool finished = left == 0xff;
        while (!finished) {
            left = static_cast<uint8_t>(left - 1);
            const uint8_t ok = TransferEnemyToSquad(node->m_pFrom, node->m_pTo, node->m_type);
            if (ok == 0) break;
            node->m_count = static_cast<uint8_t>(node->m_count - 1);
            CKGrpSquad::SFlags& from = static_cast<CKGrpSquad*>(node->m_pFrom)->m_vUnk2c.m_pBlock[node->m_type];
            from.m_unk00 = static_cast<uint8_t>(from.m_unk00 - 1);
            from.m_unk03 = static_cast<uint8_t>(from.m_unk03 + 1);
            CKGrpSquad::SFlags& to = static_cast<CKGrpSquad*>(node->m_pTo)->m_vUnk2c.m_pBlock[node->m_type];
            to.m_unk00 = static_cast<uint8_t>(to.m_unk00 + 1);
            to.m_unk03 = static_cast<uint8_t>(to.m_unk03 - 1);
            finished = left == 0xff;
        }
        if (!finished) {
            prev = node;
            node = node->m_pNext;
        } else if (m_unk98 == node) {
            STransferNode* next = node->m_pNext;
            NodePool<STransferNode>::Give(node);
            m_unk98 = next;
            prev = nullptr;
            node = next;
        } else {
            STransferNode* next = node->m_pNext;
            prev->m_pNext = next;
            NodePool<STransferNode>::Give(node);
            node = next;
        }
    }
}

// 0x00272478 CKGrpFightZone_AddSpawnedCount_maybe
uint32_t CKGrpFightZone::AddSpawnedCount(uint8_t type, uint32_t count) {
    uint32_t fitted = count;
    m_unk88 = static_cast<int32_t>(count + static_cast<uint32_t>(m_unk88));
    if (m_unk84 != -1 && m_unk88 >= m_unk84) {
        fitted = count + static_cast<uint32_t>(m_unk84 - m_unk88);
        m_unk88 = m_unk84;
    }
    SEntry4c& kind = m_vUnk4c.m_pBlock[type];
    const int16_t cap = kind.m_unk06;
    kind.m_unk08 = static_cast<uint16_t>(count + kind.m_unk08);
    if (cap != -1 && static_cast<int32_t>(kind.m_unk08) >= cap) {
        fitted = count + static_cast<uint32_t>(cap - static_cast<int32_t>(kind.m_unk08));
        kind.m_unk08 = static_cast<uint16_t>(cap);
    }
    return fitted;
}

// 0x0026e348 CKGrpFightZone_SetCompleted_maybe: the trigger starter +0xfc fired, +0x10d = `completed`.
void CKGrpFightZone::SetCompleted(uint8_t completed) {
    QueueTriggerSignals(&m_aTriggers[10]);  // +0xfc
    m_unk10d = completed;
}

// 0x00271bb8 CKGrpFightZone_GetTotalKilledCount_maybe: the +0x0c words of the +0x4c entries summed.
int32_t CKGrpFightZone::GetTotalKilledCount() {
    uint32_t total = 0;
    for (uint32_t i = 0; i < m_vUnk4c.m_ui32NbUsedElt; ++i) total += m_vUnk4c.m_pBlock[i].m_unk0c;
    return static_cast<int32_t>(total);
}

// 0x00272708 CKGrpFightZone_TransferEnemyToSquad_maybe: the first member of `from` of `type` the enemy group lets go
// (vt+0x150) leaves its key slot, moves into `to` (Group_TransferHook_maybe), loses its slot, gets the formation flags 1
// and `to` as its squad (+0x168). 0 when none.
uint8_t CKGrpFightZone::TransferEnemyToSquad(IKSerializable* from, IKSerializable* to, uint8_t type) {
    CKGrpSquad* source = static_cast<CKGrpSquad*>(from);
    for (IKHook* enemy = *reinterpret_cast<IKHook**>(source->GetMemberListHead()); enemy != nullptr;  // vt+0xb0
         enemy = enemy->m_pNextHook) {
        if (FormationOf(enemy)->m_type != type) continue;
        if (static_cast<CKGrpS08Enemy*>(GetEnemyGroup())->CanTransferEnemy(enemy) == 0) continue;  // vt+0x150
        const int32_t slot = FormationOf(enemy)->m_slot;
        if (slot >= 0) source->CurrentKey()->m_asPos.m_pBlock[slot].m_bUsed = 0;  // 0x2649e8
        Group_TransferHook(enemy, static_cast<IKBaseGroup*>(to), source);         // 0x1d5c0
        FormationOf(enemy)->m_slot = -1;
        SEnemyFormation* formation = FormationOf(enemy);
        formation->m_flags = (formation->m_flags & ~3u) | 1u;
        static_cast<IKHkEnemy*>(enemy)->m_pGroupSquad = to;
        return 1;
    }
    return 0;
}

namespace {
// A transfer node pushed at the head of the zone's list (+0x98), as the original's inlined pool take.
void PushTransfer(CKGrpFightZone* zone, uint8_t type, uint8_t count, IKSerializable* from, IKSerializable* to) {
    CKGrpFightZone::STransferNode* node = NodePool<CKGrpFightZone::STransferNode>::Take();
    node->m_pNext = nullptr;
    node->m_pTo = to;
    node->m_pFrom = from;
    node->m_count = count;
    node->m_type = type;
    node->m_pNext = zone->m_unk98;
    zone->m_unk98 = node;
}

// The zone's squads (+0x40), from the last one: the first other than `except` with members of `type`; null when none.
CKGrpSquad* LastSquadWithMembers(CKGrpFightZone* zone, IKSerializable* except, uint8_t type) {
    for (uint32_t i = zone->m_vUnk40.m_ui32NbUsedElt; i != 0; --i) {
        CKGrpSquad* squad = static_cast<CKGrpSquad*>(zone->m_vUnk40.m_pBlock[i - 1]);
        if (squad == except) continue;
        if (squad->GetTypeCountTotal(type) > 0) return squad;
    }
    return nullptr;
}

// The zone's squads (+0x40), from the first one: the first other than `except` missing spawns of `type`; null when none.
CKGrpSquad* FirstSquadMissingSpawns(CKGrpFightZone* zone, IKSerializable* except, uint8_t type) {
    for (uint32_t i = 0; i < zone->m_vUnk40.m_ui32NbUsedElt; ++i) {
        CKGrpSquad* squad = static_cast<CKGrpSquad*>(zone->m_vUnk40.m_pBlock[i]);
        if (squad == except) continue;
        if (squad->GetMissingSpawnCountForType(type) != 0) return squad;
    }
    return nullptr;
}

// One transfer per member, into `to` from the other squads that have members of `type` (consecutive ones from the same
// squad share a node). The pending transfer counters (+0x03) follow.
void QueueTransfersInto(CKGrpFightZone* zone, CKGrpSquad* to, uint8_t type, int8_t count) {
    CKGrpSquad* previous = nullptr;
    while (count = static_cast<int8_t>(count - 1), count != -1) {
        CKGrpSquad* from = LastSquadWithMembers(zone, to, type);
        if (from == nullptr) {
            count = 0;
            continue;
        }
        if (from == previous) {
            zone->m_unk98->m_count = static_cast<uint8_t>(zone->m_unk98->m_count + 1);
        } else {
            PushTransfer(zone, type, 1, from, to);
        }
        from->m_vUnk2c.m_pBlock[type].m_unk03 = static_cast<uint8_t>(from->m_vUnk2c.m_pBlock[type].m_unk03 - 1);
        to->m_vUnk2c.m_pBlock[type].m_unk03 = static_cast<uint8_t>(to->m_vUnk2c.m_pBlock[type].m_unk03 + 1);
        previous = from;
    }
}

// One transfer per member, out of `from` into the other squads that miss spawns of `type`.
void QueueTransfersOutOf(CKGrpFightZone* zone, CKGrpSquad* from, uint8_t type, int8_t count) {
    CKGrpSquad* previous = nullptr;
    while (count = static_cast<int8_t>(count - 1), count != -1) {
        CKGrpSquad* to = FirstSquadMissingSpawns(zone, from, type);
        if (to == nullptr) {
            count = 0;
            continue;
        }
        if (to == previous) {
            zone->m_unk98->m_count = static_cast<uint8_t>(zone->m_unk98->m_count + 1);
        } else {
            PushTransfer(zone, type, 1, from, to);
        }
        from->m_vUnk2c.m_pBlock[type].m_unk03 = static_cast<uint8_t>(from->m_vUnk2c.m_pBlock[type].m_unk03 - 1);
        to->m_vUnk2c.m_pBlock[type].m_unk03 = static_cast<uint8_t>(to->m_vUnk2c.m_pBlock[type].m_unk03 + 1);
        previous = to;
    }
}

// The members of `type` moved from `from` to `to` in one node: as many as `to` misses and `from` has (signed), at most
// `limit` when one is given; nothing when that is not positive.
void QueueTransferBetween(CKGrpFightZone* zone, CKGrpSquad* from, CKGrpSquad* to, uint8_t type, const uint8_t* limit) {
    const int8_t members = from->GetTypeCountTotal(type);
    int8_t count = static_cast<int32_t>(to->GetMissingSpawnCountForType(type)) < members
                       ? static_cast<int8_t>(to->GetMissingSpawnCountForType(type))
                       : from->GetTypeCountTotal(type);
    if (limit != nullptr && static_cast<int32_t>(*limit) < count) count = static_cast<int8_t>(*limit);
    if (count <= 0) return;
    PushTransfer(zone, type, static_cast<uint8_t>(count), from, to);
    from->m_vUnk2c.m_pBlock[type].m_unk03 = static_cast<uint8_t>(from->m_vUnk2c.m_pBlock[type].m_unk03 - count);
    to->m_vUnk2c.m_pBlock[type].m_unk03 = static_cast<uint8_t>(to->m_vUnk2c.m_pBlock[type].m_unk03 + count);
}
}  // namespace

// 0x00273b68 CKGrpFightZone_QueueTransfersForRequest_maybe: the transfer request `index` (+0x8c: mode, type, count, from,
// to). Mode 0 moves up to `count` members of one type, mode 1 every type with no count; a null `from` takes members from
// the other squads into `to` (as many as `to` misses), a null `to` gives `from`'s members to the squads that miss some.
void CKGrpFightZone::QueueTransfersForRequest(uint8_t index) {
    const SEntry8c& request = m_vUnk8c.m_pBlock[index];
    CKGrpSquad* from = static_cast<CKGrpSquad*>(request.m_pRef04);
    CKGrpSquad* to = static_cast<CKGrpSquad*>(request.m_pRef08);
    if (request.m_unk00 == 0) {
        const uint8_t type = request.m_unk01;
        const uint8_t limit = request.m_unk02;
        if (from == nullptr) {
            const uint8_t missing = to->GetMissingSpawnCountForType(type);
            const int8_t count = limit > missing ? static_cast<int8_t>(to->GetMissingSpawnCountForType(type))
                                                 : static_cast<int8_t>(m_vUnk8c.m_pBlock[index].m_unk02);
            QueueTransfersInto(this, to, type, count);
        } else if (to == nullptr) {
            const int8_t members = from->GetTypeCountTotal(type);
            const int8_t count = members < static_cast<int32_t>(limit) ? from->GetTypeCountTotal(type)
                                                                       : static_cast<int8_t>(m_vUnk8c.m_pBlock[index].m_unk02);
            QueueTransfersOutOf(this, from, type, count);
        } else {
            QueueTransferBetween(this, from, to, type, &m_vUnk8c.m_pBlock[index].m_unk02);
        }
        return;
    }
    if (request.m_unk00 != 1) return;
    for (uint32_t type = 0; type < m_vUnk4c.m_ui32NbUsedElt; ++type) {
        if (from == nullptr) {
            QueueTransfersInto(this, to, static_cast<uint8_t>(type), static_cast<int8_t>(to->GetMissingSpawnCountForType(type)));
        } else if (to == nullptr) {
            QueueTransfersOutOf(this, from, static_cast<uint8_t>(type), from->GetTypeCountTotal(type));
        } else {
            QueueTransferBetween(this, from, to, static_cast<uint8_t>(type), nullptr);
        }
    }
}

namespace {
// The squad an entry spawn goes to: the first of the zone's squads (+0x40) missing spawns of `type`; else the first
// squad, or the second when the first is null (null without squads: BUG(original), the caller writes through it).
CKGrpSquad* EntrySpawnSquad(CKGrpFightZone* zone, uint8_t type) {
    const uint32_t count = zone->m_vUnk40.m_ui32NbUsedElt;
    for (uint32_t i = 0; i < count; ++i) {
        CKGrpSquad* squad = static_cast<CKGrpSquad*>(zone->m_vUnk40.m_pBlock[i]);
        if (squad != nullptr && squad->GetMissingSpawnCountForType(type) != 0) return squad;
    }
    if (count == 0) return nullptr;
    CKGrpSquad* squad = static_cast<CKGrpSquad*>(zone->m_vUnk40.m_pBlock[0]);
    if (squad == nullptr && count > 1) squad = static_cast<CKGrpSquad*>(zone->m_vUnk40.m_pBlock[1]);
    return squad;
}
}  // namespace

// 0x00274698 CKGrpFightZone_QueueEntrySpawns_maybe: the entry `index` (+0x70: type +0x19, count +0x1a, squad +0x1c,
// mode +0x20). Mode 0 only raises the squads' wanted counters (+0x01: the squad's own spawning places them), one by one
// over the squads missing spawns without a squad; another mode queues spawn requests at the entry (+0x80) and raises the
// pending counters (+0x02), consecutive ones for the same squad sharing a request.
void CKGrpFightZone::QueueEntrySpawns(uint8_t index) {
    const SEntry70& entry = m_vUnk70.m_pBlock[index];
    const uint8_t count = entry.m_unk1a;
    const uint8_t type = entry.m_unk19;
    CKGrpSquad* squad = static_cast<CKGrpSquad*>(entry.m_pRef);
    if (entry.m_unk20 == 0) {
        if (squad != nullptr) {
            squad->m_vUnk2c.m_pBlock[type].m_unk01 = static_cast<uint8_t>(squad->m_vUnk2c.m_pBlock[type].m_unk01 + count);
            return;
        }
        for (uint32_t left = count; left != 0; --left) {
            CKGrpSquad* target = EntrySpawnSquad(this, type);
            target->m_vUnk2c.m_pBlock[type].m_unk01 = static_cast<uint8_t>(target->m_vUnk2c.m_pBlock[type].m_unk01 + 1);
        }
        return;
    }
    if (squad != nullptr) {
        SSpawnRequest* request = NodePool<SSpawnRequest>::Take();
        request->m_pNext = nullptr;
        request->m_entry = index;
        request->m_count = count;
        request->m_type = type;
        request->m_pSquad = squad;
        request->m_pNext = m_unk80;
        m_unk80 = request;
        squad->m_vUnk2c.m_pBlock[type].m_unk02 = static_cast<uint8_t>(squad->m_vUnk2c.m_pBlock[type].m_unk02 + count);
        return;
    }
    CKGrpSquad* previous = nullptr;
    for (uint32_t left = count; left != 0; --left) {
        CKGrpSquad* target = EntrySpawnSquad(this, type);
        if (target == previous) {
            m_unk80->m_count = static_cast<uint8_t>(m_unk80->m_count + 1);
        } else {
            SSpawnRequest* request = NodePool<SSpawnRequest>::Take();
            request->m_pNext = nullptr;
            request->m_count = 1;
            request->m_type = type;
            request->m_entry = index;
            request->m_pSquad = target;
            request->m_pNext = m_unk80;
            m_unk80 = request;
        }
        target->m_vUnk2c.m_pBlock[type].m_unk02 = static_cast<uint8_t>(target->m_vUnk2c.m_pBlock[type].m_unk02 + 1);
        previous = target;
    }
}

// 0x0026e4e8 CKGrpFightZone_PostLoad: IKLife's, the zone put to sleep (a script wakes it), bit 5 (the fight) cleared.
int32_t CKGrpFightZone::PostLoad(int32_t type) {
    PostLoadLife(type);  // 0x19f68
    SetObjectActive(g_pEngine->m_coreManager, this, 0);  // 0x1d1c0
    m_bitArray &= ~0x20u;
    return 1;
}

namespace {
// The trigger value accessors of GetInfo (their descriptors at 0x00b89a30..0x00b89b88).
CKGrpFightZone* Zone(IKSerializable* self) { return static_cast<CKGrpFightZone*>(self); }
// The squads (the child groups, linked by +0x14).
CKGrpSquad* FirstSquad(CKGrpFightZone* zone) { return static_cast<CKGrpSquad*>(zone->m_lChilds); }
CKGrpSquad* NextSquad(CKGrpSquad* squad) { return static_cast<CKGrpSquad*>(squad->m_pNextGroup); }
// The detector groups' vt+0xc0 (DetectorHolds) of a reference the original calls without a null test.
uint32_t DetectorBit(IKSerializable* detector) {
    return static_cast<uint32_t>(static_cast<CKHkDetectorGroup*>(detector)->m_unk4C[0] & 1u);
}

// 0x00271648 CKGrpFightZone_GetFlagBit6Property_maybe: armed (+0xc bit 6).
uint32_t ZoneArmed(IKSerializable* self, uint32_t) { return (Zone(self)->m_bitArray >> 6) & 1u; }
// 0x00271658 CKGrpFightZone_CallRef30Vf0C0Property_maybe: the entry detector holds.
uint32_t ZoneEntryHolds(IKSerializable* self, uint32_t) { return DetectorHolds(Zone(self)->m_pUnk30); }
// 0x002716b8 CKGrpFightZone_AnySquadHasField50Property_maybe: a squad has queued respawns (+0x50).
uint32_t ZoneAnyRespawnQueued(IKSerializable* self, uint32_t) {
    for (CKGrpSquad* squad = FirstSquad(Zone(self)); squad != nullptr; squad = NextSquad(squad)) {
        if (squad->m_unk50 != nullptr) return 1;
    }
    return 0;
}
// 0x00271720 CKGrpFightZone_CallRef34Vf0C0Property_maybe: the inside detector holds.
uint32_t ZoneInsideHolds(IKSerializable* self, uint32_t) { return DetectorHolds(Zone(self)->m_pUnk34); }
// 0x00271780 CKGrpFightZone_CallRef38Vf0C0IfRef30Property_maybe: with an entry detector, the exit detector holds.
uint32_t ZoneExitHoldsIfEntry(IKSerializable* self, uint32_t) {
    return Zone(self)->m_pUnk30 != nullptr ? DetectorBit(Zone(self)->m_pUnk38) : 0;
}
// 0x002717e0 CKGrpFightZone_CallRef30Vf0C0IfRef38Property_maybe: with an exit detector, the entry detector holds.
uint32_t ZoneEntryHoldsIfExit(IKSerializable* self, uint32_t) {
    return Zone(self)->m_pUnk38 != nullptr ? DetectorBit(Zone(self)->m_pUnk30) : 0;
}
// 0x00271840 CKGrpFightZone_CallRef2CVf6CProperty_maybe: the component's vt+0x6c.
uint32_t ZoneComponentValue(IKSerializable* self, uint32_t) {
    return static_cast<uint32_t>(Zone(self)->m_pFightZoneCpnt->CountActiveObjectives());  // vt+0x6c
}
// 0x002718d0 CKGrpFightZone_GetMinHeroDistanceToPoint_maybe: the nearest controlled hero's horizontal distance to the
// point `index` (+0x9c, not range-checked); FLT_MAX (0x00c4acb8 +0x28) with heroes, 0 (TOC 0x8c0) without.
uint32_t ZoneMinHeroDistanceToPoint(IKSerializable* self, uint32_t index) {
    IKSerializable** heroes = static_cast<IKGrpHero*>(g_pEngine->m_gameManager->m_unk04[1])->m_apControlledHeroes;  // 0x2ca0e0
    float best = 0x1.fffffep+127f;
    if (*heroes == nullptr) return FloatBits(0.0f);
    for (; *heroes != nullptr; ++heroes) {
        const CVector3& point = Zone(self)->m_vUnk9c.m_pBlock[index];
        const CVector3* hero = ZoneHeroTargetingPosition(*heroes);  // 0x363c78
        const float dz = point.z - hero->z;
        const float dx = point.x - hero->x;
        const float distance = MathSqrtf(ppc::fmadds(dx, dx, dz * dz));
        if (distance < best) best = distance;
    }
    return FloatBits(best);
}
// 0x002719e8 CKGrpFightZone_GetTotalSquadCount_maybe: every type's members over every squad.
uint32_t ZoneTotalSquadCount(IKSerializable* self, uint32_t) {
    int32_t total = 0;
    for (uint32_t type = 0; type < Zone(self)->m_vUnk4c.m_ui32NbUsedElt; ++type) {
        for (CKGrpSquad* squad = FirstSquad(Zone(self)); squad != nullptr; squad = NextSquad(squad)) {
            total += squad->GetTypeCountTotal(type);
        }
    }
    return static_cast<uint32_t>(total);
}
// 0x00271a90 CKGrpFightZone_GetTypeKilledCount_maybe (no range test)
uint32_t ZoneTypeKilledCount(IKSerializable* self, uint32_t type) { return Zone(self)->m_vUnk4c.m_pBlock[type].m_unk0c; }
// 0x00271af0 CKGrpFightZone_GetTypeSpawnCap_maybe: a positive cap, else 0.
uint32_t ZoneTypeSpawnCap(IKSerializable* self, uint32_t type) {
    if (type >= Zone(self)->m_vUnk4c.m_ui32NbUsedElt) return 0;
    const int16_t cap = Zone(self)->m_vUnk4c.m_pBlock[type].m_unk06;
    return cap > 0 ? static_cast<uint32_t>(static_cast<int32_t>(cap)) : 0u;
}
// 0x00271b38 CKGrpFightZone_GetTotalSpawnCap_maybe: the caps summed, 0 as soon as one is not positive.
uint32_t ZoneTotalSpawnCap(IKSerializable* self, uint32_t) {
    int32_t total = 0;
    for (uint32_t type = 0; type < Zone(self)->m_vUnk4c.m_ui32NbUsedElt; ++type) {
        const int16_t cap = Zone(self)->m_vUnk4c.m_pBlock[type].m_unk06;
        if (cap < 1) return 0;
        total += cap;
    }
    return static_cast<uint32_t>(total);
}
// 0x00271bb8 CKGrpFightZone_GetTotalKilledCount_maybe
uint32_t ZoneTotalKilledCount(IKSerializable* self, uint32_t) { return static_cast<uint32_t>(Zone(self)->GetTotalKilledCount()); }
// 0x00271c08 CKGrpFightZone_GetTotalSpawnedCount_maybe
uint32_t ZoneTotalSpawnedCount(IKSerializable* self, uint32_t) {
    uint32_t total = 0;
    for (uint32_t type = 0; type < Zone(self)->m_vUnk4c.m_ui32NbUsedElt; ++type) total += Zone(self)->m_vUnk4c.m_pBlock[type].m_unk08;
    return total;
}
// 0x00271c58 CKGrpFightZone_GetTypeSpawnedCount_maybe (a halfword, zero-extended)
uint32_t ZoneTypeSpawnedCount(IKSerializable* self, uint32_t type) {
    if (type >= Zone(self)->m_vUnk4c.m_ui32NbUsedElt) return 0;
    return Zone(self)->m_vUnk4c.m_pBlock[type].m_unk08;
}
// 0x00271de0 CKGrpFightZone_GetTypeRemainingEnemies_maybe: with a positive cap, the cap minus the spawned count plus every
// squad's members of the type (+0x00 only).
uint32_t ZoneTypeRemaining(IKSerializable* self, uint32_t type) {
    if (type >= Zone(self)->m_vUnk4c.m_ui32NbUsedElt) return 0;
    const CKGrpFightZone::SEntry4c& kind = Zone(self)->m_vUnk4c.m_pBlock[type];
    if (kind.m_unk06 < 1) return 0;
    int32_t left = static_cast<int32_t>(kind.m_unk06) - static_cast<int32_t>(kind.m_unk08);
    for (CKGrpSquad* squad = FirstSquad(Zone(self)); squad != nullptr; squad = NextSquad(squad)) {
        left += squad->m_vUnk2c.m_pBlock[type].m_unk00;
    }
    return static_cast<uint32_t>(left);
}
// 0x00271c88 CKGrpFightZone_GetTotalRemainingEnemies_maybe: the same over every type, 0 as soon as a cap is not positive.
uint32_t ZoneTotalRemaining(IKSerializable* self, uint32_t) {
    int32_t left = 0;
    for (uint32_t type = 0; type < Zone(self)->m_vUnk4c.m_ui32NbUsedElt; ++type) {
        const CKGrpFightZone::SEntry4c& kind = Zone(self)->m_vUnk4c.m_pBlock[type];
        if (kind.m_unk06 < 1) return 0;
        left += static_cast<int32_t>(kind.m_unk06) - static_cast<int32_t>(kind.m_unk08);
        for (CKGrpSquad* squad = FirstSquad(Zone(self)); squad != nullptr; squad = NextSquad(squad)) {
            left += squad->m_vUnk2c.m_pBlock[type].m_unk00;
        }
    }
    return static_cast<uint32_t>(left);
}
// 0x00271d38 CKGrpFightZone_GetTypeSquadCount_maybe: the type's members over every squad.
uint32_t ZoneTypeSquadCount(IKSerializable* self, uint32_t type) {
    if (type >= Zone(self)->m_vUnk4c.m_ui32NbUsedElt) return 0;
    int32_t total = 0;
    for (CKGrpSquad* squad = FirstSquad(Zone(self)); squad != nullptr; squad = NextSquad(squad)) total += squad->GetTypeCountTotal(type);
    return static_cast<uint32_t>(total);
}
// 0x00272290 CKGrpFightZone_IsCleared_maybe: no squad has queued respawns and no squad has members of any type.
uint32_t ZoneIsCleared(IKSerializable* self, uint32_t) {
    for (CKGrpSquad* squad = FirstSquad(Zone(self)); squad != nullptr; squad = NextSquad(squad)) {
        if (squad->m_unk50 != nullptr) return 0;
    }
    if (Zone(self)->m_vUnk4c.m_ui32NbUsedElt == 0) return 1;
    return ZoneTotalSquadCount(self, 0) == 0 ? 1u : 0u;
}
}  // namespace

// 0x00271e68 CKGrpFightZone_GetInfo
int32_t CKGrpFightZone::GetInfo(IKInfo* info, int32_t request) {
    if (request != kGetInfoValueAccessor) return 1;
    switch (info->m_ui32Id) {
        case 0x1: return AnswerInfo(info, ZoneArmed, 0);
        case 0x2: return AnswerInfo(info, ZoneEntryHolds, 0);
        case 0x3: return AnswerInfo(info, ZoneTypeSquadCount, 1);
        case 0x4: return AnswerInfo(info, ZoneTotalSquadCount, 1);
        case 0x5: return AnswerInfo(info, ZoneTypeSpawnedCount, 1);
        case 0x6: return AnswerInfo(info, ZoneTotalSpawnedCount, 1);
        case 0x7: return AnswerInfo(info, ZoneTypeRemaining, 1);
        case 0x8: return AnswerInfo(info, ZoneTotalRemaining, 1);
        case 0x9: return AnswerInfo(info, ZoneTypeSpawnCap, 1);
        case 0xa: return AnswerInfo(info, ZoneTotalSpawnCap, 1);
        case 0xb: return AnswerInfo(info, ZoneMinHeroDistanceToPoint, 2);
        case 0x1b: return AnswerInfo(info, ZoneAnyRespawnQueued, 0);
        case 0x1c: return AnswerInfo(info, ZoneIsCleared, 0);
        case 0x1f: return AnswerInfo(info, ZoneTypeKilledCount, 1);
        case 0x20: return AnswerInfo(info, ZoneTotalKilledCount, 1);
        case 0x27: return AnswerInfo(info, ZoneInsideHolds, 0);
        case 0x28: return AnswerInfo(info, ZoneExitHoldsIfEntry, 0);
        case 0x29: return AnswerInfo(info, ZoneEntryHoldsIfExit, 0);
        case 0x2e: return AnswerInfo(info, ZoneComponentValue, 1);
        default: return 1;
    }
}

// 0x0026e7d0 CKGrpFightZone_EnableMembers (vt+0xa8)
void CKGrpFightZone::OnLock() {
    CKCoreManager* core = g_pEngine->m_coreManager;
    for (IKBaseGroup* child = m_lChilds; child != nullptr; child = child->m_pNextGroup) SetObjectLocked(core, child, 1);
}

// 0x0026e968 CKGrpFightZone_DisableMembers (vt+0xac)
void CKGrpFightZone::OnUnlock() {
    CKCoreManager* core = g_pEngine->m_coreManager;
    for (IKBaseGroup* child = m_lChilds; child != nullptr; child = child->m_pNextGroup) SetObjectLocked(core, child, 0);
}

// 0x0026eab8 CKGrpFightZone_RecursiveRegistration
void CKGrpFightZone::RecursiveRegistration(int32_t type) {
    IKBaseGroup::RecursiveRegistration(type);  // 0x00012a68 IKGroup_LevelReset
    if (type == 0) {
        g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
        m_pFightZoneCpnt->RecursiveRegistration(0);  // vt+0x24: KBaseDC6_LevelReset 0x274a80 (nothing)
    }
    // KStub_Return1_2361b0 on each of m_aTriggers[0..11]: the trigger starters register nothing.
}
