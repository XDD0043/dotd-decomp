// CKGrpSquad.cpp - reconstructed original translation unit 0x25a9c0-0x263df8 (GAME_TOC1, main_toc1), 86 functions, 71 live.
// Primary class: CKGrpSquad  key 0x604  category Group  size 0xd0  vtable 0xb212b0
// Other owners: GetEnemyGroup (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x25a9c0  CKGrpSquad_Delete
//   [ ] 0x25aa10  CKGrpSquad_Construct  [dead]
//   [x] 0x25ab38  GetEnemyGroup_2
//   [x] 0x25ab50  CKGrpSquad_GetFightZone
//   [ ] 0x25ab58  CKGrpSquad_ClearMemberFormationSlots_maybe  [dead]
//   [ ] 0x25ac00  CKGrpSquad_SetMemberField29_maybe  [dead]
//   [x] 0x25aca8  CKGrpSquad_SetStoredPhase_maybe
//   [ ] 0x25acc0  CKGrpSquad_HasNoMembers_maybe  [dead]
//   [ ] 0x25ad30  CKGrpSquad_GetPhaseFlagB4_maybe  [dead]
//   [ ] 0x25ad60  RegisterCKGrpSquadClass
//   [ ] 0x25add8  _GLOBAL__I_25add8
//   [x] 0x25ade8  CKGrpSquad_DeleteArray
//   [ ] 0x25ae88  CKGrpSquad_Construct_2  [dead]
//   [ ] 0x25afb0  CKGrpSquad_GetPhaseFlagC0_maybe  [dead]
//   [x] 0x25afe0  CKGrpSquad_ResetMemberSlots_maybe
//   [x] 0x25b160  CKGrpSquad_ActivateSpawnCamera_maybe
//   [x] 0x25b328  CKGrpSquad_CreateArray
//   [x] 0x25b4c0  CKGrpSquad_Create
//   [x] 0x25b600  CKGrpSquad_UpdateChoreography_maybe
//   [ ] 0x25b810  CKGrpSquad_OrientTowardHero_maybe  [dead: no pointer to its descriptor 0xb84ea8, no call]
//   [ ] 0x25b958  CKGrpSquad_OrientTowardPhaseTarget_maybe  [dead: no pointer to its descriptor 0xb84eb0, no call]
//   [ ] 0x25bab0  CKGrpSquad_OrientTowardPhasePoint_maybe  [dead: no pointer to its descriptor 0xb84eb8, no call]
//   [ ] 0x25bbf8  CKGrpSquad_OrientTowardControlledHero_maybe  [dead]
//   [x] 0x25bd50  CKGrpSquad_AssignFormationSlot_maybe
//   [x] 0x25c278  CKGrpSquad_SetPhase_maybe
//   [x] 0x25ca10  CKGrpSquad_ApplyPendingChoreography_maybe
//   [x] 0x25caa0  CKGrpSquad_AssignFormationSlotsRecursive_maybe
//   [x] 0x25cc48  CKGrpSquad_AssignAllFormationSlots_maybe
//   [x] 0x25ccd8  CKGrpSquad_FaceNearestHero_maybe
//   [x] 0x25ceb8  CKGrpSquad_UpdateAnchorFromPhase_maybe
//   [ ] 0x25d638  CKGrpSquad_Save
//   [ ] 0x25d640  CKGrpSquad_vfB8  [dead: vt+0xb8 (returns 1), called only by the dead CKCoreManager 0x1c330 / 0x1d460 (raw ELF scan of the vt+0xb8 calls)]
//   [x] 0x25d648  CKGrpSquad_Stop  (empty: the IKBaseGroup default)
//   [x] 0x25d650  CKGrpSquad_SetDefaultState  (header)
//   [x] 0x25d660  CKGrpSquad_SetGameState  (header)
//   [x] 0x25d698  CKGrpSquad_Restart  (header)
//   [x] 0x25d6c8  CKGrpSquad_Start
//   [x] 0x25d718  CKGrpSquad_vfA8
//   [x] 0x25d7b0  CKGrpSquad_vf94
//   [x] 0x25d8a8  CKGrpSquad_vfAC
//   [x] 0x25d940  UpdateCKGrpSquad
//   [x] 0x25ddf0  CKGrpSquad_StopFight_maybe
//   [x] 0x25de60  CKGrpSquad_MessageProc
//   [x] 0x25e008  CKGrpSquad_PostLoad
//   [x] 0x25e2b0  CKGrpSquad_RecursiveRegistration
//   [x] 0x25e430  CKGrpSquad_Destroy
//   [x] 0x25e4f0  CKGrpSquad_Load
//   [x] 0x25fb38  CKGrpSquad_GetCurrentPhaseObjByte8Property_maybe
//   [x] 0x25fb58  CKGrpSquad_IsInPhaseProperty_maybe
//   [x] 0x25fb90  CKGrpSquad_GetMinHeroDistance_maybe
//   [x] 0x25fc88  CKGrpSquad_GetTypeCountProperty_maybe
//   [x] 0x25fcd0  CKGrpSquad_GetChoreoTypeSlotCountProperty_maybe
//   [x] 0x25fd18  CKGrpSquad_GetTotalCountProperty_maybe
//   [x] 0x25fda0  CKGrpSquad_GetInfo
//   [x] 0x25ff58  CKGrpSquad_GetDistanceToFightZonePoint_maybe
//   [x] 0x260008  CKGrpSquad_GetTypeCountTotal_maybe
//   [ ] 0x260040  CKGrpSquad_CountFreeChoreoSlotsOfType_maybe  [dead]
//   [x] 0x2600f0  CKGrpSquad_CountChoreoSlotsOfType_maybe
//   [ ] 0x260198  CKGrpSquad_PlaceMemberAtFormationSlot_maybe  [dead]
//   [ ] 0x260280  CKGrpSquad_TakeOverMember_maybe  [dead: no pointer to its descriptor 0xb85c38, no call]
//   [x] 0x2604c0  CKGrpSquad_HasSpawnRequest_maybe
//   [x] 0x260568  CKGrpSquad_ClearSpawnCountsAndRespawnQueue_maybe
//   [x] 0x260668  CKGrpSquad_ReturnEnemyToFightZonePool_maybe
//   [x] 0x260748  CKGrpSquad_ReleaseMember_maybe
//   [x] 0x2608c8  CKGrpSquad_TakeEnemyFromFightZonePool_maybe
//   [x] 0x260a88  CKGrpSquad_ProcessDeadMembers_maybe
//   [x] 0x260db0  CKGrpSquad_ReleaseAllMembers_maybe
//   [x] 0x260f38  CKGrpSquad_SpawnMember_maybe
//   [ ] 0x261180  CKGrpSquad_QueueSpawnForType_maybe  [dead]
//   [x] 0x261280  CKGrpSquad_QueueSpawnsToFillFormation_maybe
//   [ ] 0x261478  CKGrpSquad_SpawnMemberAt_maybe  [dead: no pointer to its descriptor 0xb85ce8, no call]
//   [ ] 0x261708  CKGrpSquad_QueueSpawnsForType_maybe  [dead]
//   [x] 0x261818  CKGrpSquad_GetMissingSpawnCountForType_maybe
//   [x] 0x261928  CKGrpSquad_SpawnPendingMembers_maybe
//   [x] 0x261e00  CKGrpSquad_SpawnFullFormation_maybe
//   [x] 0x2620e8  CKGrpSquad_SpawnFullFormation_maybe
//   [x] 0x2620f0  CKGrpSquad_ProcessRespawnTimers_maybe
//   [x] 0x2623d8  CKGrpSquad_ScheduleRespawns_maybe
//   [ ] 0x2634d8  CKGrpSquad_Phase_Release_2  [dead]
//   [ ] 0x263510  CKGrpSquad_Phase_Init_2  [dead]
//   [x] 0x263530  CKGrpSquad_Phase_Init
//   [ ] 0x263550  CKGrpSquad_Phase_InitAtPosition_maybe  [dead: no pointer to its descriptor 0xb85eb8, no call]
//   [ ] 0x263688  CKGrpSquad_Phase_CopyConstruct_maybe  [dead: no pointer to its descriptor 0xb85ec0, no call]
//   [x] 0x2638e8  CKGrpSquad_Phase_Release  (header: SState::Release)
//   [ ] 0x263920  CKGrpSquad_Phase_Assign_maybe  [dead]
//   [ ] 0x263b98  CKGrpSquad_Phase_CopyConstruct_2_maybe  [dead: no pointer to its descriptor 0xb85ee0, no call]
//
//   [x] 0x9ba998  CKGrpSquad_GetClassType  [inline]
//   [x] 0x9ba9a0  CKGrpSquad_GetClassID  [inline]
//   [ ] 0x9ba9a8  CKGrpSquad_vfCC  [inline]
//   [ ] 0x9ba9b0  CKGrpSquad_Pause  [inline]
//   [ ] 0x9ba9b8  CKGrpSquad_Resume  [inline]
//   [ ] 0x9ba9c0  CKGrpSquad_IsKindOfClass  [inline]
//   [ ] 0x9baa18  CKGrpSquad_Destructor  [inline]
//   [ ] 0x9bace0  CKGrpSquad_DeletingDestructor  [inline]
//   [x] 0x9bafb0  CKGrpSquad_SpawnEntryCompareByByte4_maybe  [inline]
#include "k2000/groups/CKGrpSquad.h"
#include "k2000/core/IKInfo.h"
#include "Spyro2008/components/CKS08EnemyCpnt.h"

#include <new>

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "Spyro2008/groups/CKChoreoKey.h"
#include "Spyro2008/groups/CKGrpS08Enemy.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "Spyro2008/hooks/CKHkS08Enemy.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/hooks/IKHkEnemy.h"
#include "Spyro2008/hooks/IKHkHero.h"
#include "crt/Ps3Qsort.h"
#include "crt/ppc_ops.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/cameras/IKCamera.h"
#include "k2000/groups/CKGrpFightZone.h"
#include "k2000/groups/CKGrpPoolSquad.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKBundle.h"
#include "k2000/logic/CKChoreography.h"
#include "k2000/logic/CKCoreManager.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/system/IKTime.h"
#include "k2000/core/Stub.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/IKGrpEnemy.h"
#include "k2000/misc/Engine.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/services/CKSrvTrigger.h"

namespace {
// The inlined "resize to count" of the squad's vectors: a new block (the old one is not freed) with the
// capacity set to the count first, so the reserve that follows never grows it; without elements the
// capacity is 1, a one-element block is allocated and the used count is left alone.
template <class T>
void ResizeBlock(TVector<T, 1>& vector, uint32_t count) {
    if (count == 0) {
        vector.m_ui32NbElt = 1;
        vector.m_pBlock = static_cast<T*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(T))));
        return;
    }
    vector.m_ui32NbElt = count;
    vector.m_pBlock = static_cast<T*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(T))));
    if (vector.m_ui32NbElt < count) {
        uint32_t capacity = count + 1u;
        if (capacity == 0) capacity = 1;
        vector.m_pBlock =
            static_cast<T*>(Mem_ReallocAligned16(vector.m_pBlock, capacity * static_cast<uint32_t>(sizeof(T))));
        vector.m_ui32NbElt = capacity;
    }
}

// A word vector read: the count, the resize (its used count set even for 0), then count words read as one
// block and byte-swapped.
void LoadWords(TVector<uint32_t, 1>& vector, IKFile* file) {
    uint32_t count = 0;
    ReadU32LE(file, &count);
    ResizeBlock(vector, count);
    vector.m_ui32NbUsedElt = count;
    for (uint32_t i = 0; i < count; ++i) ReadU32LE(file, &vector.m_pBlock[i]);
}
}  // namespace

// 0x0025e4f0 CKGrpSquad_Load
int32_t CKGrpSquad::Load(IKFile* file, int32_t type) {
    GroupBasicLoad(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;

    // The states.
    uint32_t stateCount = 0;
    ReadU32LE(file, &stateCount);
    ResizeBlock(m_vStates, stateCount);
    if (stateCount != 0) {
        for (uint32_t i = m_vStates.m_ui32NbUsedElt; i < stateCount; ++i) new (&m_vStates.m_pBlock[i]) SState;
        // The states beyond the count are released (CKGrpSquad_Phase_Release 0x2638e8: their vector's block freed);
        // the vector is empty when the Load runs (the constructor's count is 0).
        for (uint32_t i = stateCount; i < m_vStates.m_ui32NbUsedElt; ++i) {
            m_vStates.m_pBlock[i].Release();  // 0x002638e8
        }
        m_vStates.m_ui32NbUsedElt = stateCount;
    }
    for (uint32_t i = 0; i < stateCount; ++i) {
        SState& state = m_vStates.m_pBlock[i];
        state.m_pMatrix = reinterpret_cast<CMatrix34*>(RwMatrixCreate());  // RwMatrixCreate_Thunk
        CMatrix34_LoadMatrix(state.m_pMatrix, file);
        ReadU8(file, &state.m_unk04);
        IKFile_ReadRef(file, &state.m_pUnk08);
        ReadU8(file, &state.m_unk0c);
        ReadU8(file, &state.m_unk38);
        ReadU8(file, &state.m_unk1c);
        ReadU8(file, &state.m_unk39);
        IKFile_ReadRef(file, &state.m_pUnk3c);
        ReadU8(file, &state.m_unk3a);
        for (float& w : state.m_unk40) ReadF32LE(file, &w);
        ReadU32LE(file, reinterpret_cast<uint32_t*>(&state.m_unk58));
        int32_t count = 0;
        ReadS32LE(file, &count);
        if (state.m_vUnk5c.m_pBlock == nullptr) {
            state.m_vUnk5c.m_ui32NbElt = 1;
            state.m_vUnk5c.m_pBlock = static_cast<uint32_t*>(Mem_AllocAligned16(4));
        }
        for (int32_t k = 0; k < count; ++k) {
            uint32_t value = 0;
            ReadU32LE(file, &value);
            TVector<uint32_t, 1>& v = state.m_vUnk5c;
            if (v.m_ui32NbElt == v.m_ui32NbUsedElt) {  // push_back, grows by 1
                uint32_t capacity = v.m_ui32NbElt + 1u;
                if (capacity == 0) capacity = 1;
                v.m_pBlock = static_cast<uint32_t*>(Mem_ReallocAligned16(v.m_pBlock, capacity * 4u));
                v.m_ui32NbElt = capacity;
            }
            v.m_pBlock[v.m_ui32NbUsedElt++] = value;
        }
        ReadU8(file, &state.m_unk68);
        ReadU8(file, &state.m_unk69);
        ReadU8(file, &state.m_unk6a);
        ReadU32LE(file, &state.m_unk10);
        for (float& f : state.m_unk20) ReadF32LE(file, &f);
        IKFile_ReadRef(file, &state.m_pUnk2c);
        ReadU8(file, &state.m_unk30);
        IKFile_ReadRef(file, &state.m_pUnk34);
        ReadU8(file, &state.m_unk14);
        ReadF32LE(file, &state.m_unk18);
    }
    m_unk55 = 0;

    // The member lists: per list, entries of two bytes, two word vectors and a word.
    uint32_t listCount = 0;
    ReadU32LE(file, &listCount);
    ResizeBlock(m_vUnk44, listCount);
    if (listCount != 0) {
        for (uint32_t i = m_vUnk44.m_ui32NbUsedElt; i < listCount; ++i) {
            m_vUnk44.m_pBlock[i].m_ui32NbElt = 1;
            m_vUnk44.m_pBlock[i].m_pBlock = nullptr;
            m_vUnk44.m_pBlock[i].m_ui32NbUsedElt = 0;
        }
        // The lists beyond the count would be freed here (none: the vector is empty when the Load runs).
        m_vUnk44.m_ui32NbUsedElt = listCount;
    }
    for (uint32_t i = 0; i < listCount; ++i) {
        TVector<SMemberEntry, 1>& list = m_vUnk44.m_pBlock[i];
        uint32_t entryCount = 0;
        ReadU32LE(file, &entryCount);
        ResizeBlock(list, entryCount);
        if (entryCount != 0) {
            for (uint32_t k = list.m_ui32NbUsedElt; k < entryCount; ++k) {
                SMemberEntry& e = list.m_pBlock[k];
                e.m_vUnk04.m_ui32NbElt = 1;
                e.m_vUnk04.m_pBlock = nullptr;
                e.m_vUnk04.m_ui32NbUsedElt = 0;
                e.m_vUnk10.m_ui32NbElt = 1;
                e.m_vUnk10.m_pBlock = nullptr;
                e.m_vUnk10.m_ui32NbUsedElt = 0;
            }
            // The entries beyond the count would be freed here (none: a fresh list).
            list.m_ui32NbUsedElt = entryCount;
        }
        for (uint32_t k = 0; k < entryCount; ++k) {
            SMemberEntry& e = list.m_pBlock[k];
            ReadU8(file, &e.m_unk00);
            ReadU8(file, &e.m_unk01);
            LoadWords(e.m_vUnk04, file);
            LoadWords(e.m_vUnk10, file);
            ReadU32LE(file, &e.m_unk1c);
        }
    }

    // A byte vector.
    uint32_t byteCount = 0;
    ReadU32LE(file, &byteCount);
    ResizeBlock(m_vUnk38, byteCount);
    if (byteCount != 0) m_vUnk38.m_ui32NbUsedElt = byteCount;
    for (uint32_t i = 0; i < byteCount; ++i) ReadU8(file, &m_vUnk38.m_pBlock[i]);

    // A vector of flag pairs, cleared (no file data).
    uint32_t flagCount = 0;
    ReadU32LE(file, &flagCount);
    ResizeBlock(m_vUnk2c, flagCount);
    if (flagCount != 0) m_vUnk2c.m_ui32NbUsedElt = flagCount;
    for (uint32_t i = 0; i < flagCount; ++i) {
        m_vUnk2c.m_pBlock[i].m_unk00 = 0;
        m_vUnk2c.m_pBlock[i].m_unk01 = 0;
    }

    // BUG(original): with no states the first state's matrix pointer is read from the uninitialised block.
    m_pCurrentMatrix = reinterpret_cast<CMatrix34*>(RwMatrixCreate());
    *m_pCurrentMatrix = *m_vStates.m_pBlock[0].m_pMatrix;  // 16 words copied
    m_tsUnk68.Load(file, K_LEVEL_PLATEFORMS);
    m_tsUnk70.Load(file, K_LEVEL_PLATEFORMS);
    m_tsUnk78.Load(file, K_LEVEL_PLATEFORMS);
    m_tsUnk80.Load(file, K_LEVEL_PLATEFORMS);
    m_tsUnk88.Load(file, K_LEVEL_PLATEFORMS);
    int32_t start = 0;
    ReadS32LE(file, &start);
    m_pStartState = start < 1 ? nullptr : &m_vStates.m_pBlock[start];
    ReadU8(file, &m_unka0);
    return 1;
}

// 0x0025d6c8 CKGrpSquad_Start: the current state (index m_unk55) takes its +0x50 word into +0x54; the two
// run-time bytes cleared; the member slots reset.
void CKGrpSquad::Start() {
    const uint8_t current = m_unk55;
    m_unk94 = 0;
    SState& state = m_vStates.m_pBlock[current];
    state.m_unk54 = state.m_unk40[4];
    m_unkcc = 0;
    ResetMemberSlots();
}

// 0x0025afe0 CKGrpSquad_ResetMemberSlots_maybe. The target is the low byte of the parent enemy group's word at
// +0x54 (its m_vUnk4c count). A first call allocates a one-slot block; the slots are zeroed, then slots are
// appended (zero) while the count is below the target, growing the block one slot at a time.
void CKGrpSquad::ResetMemberSlots() {
    m_unka4 = 0;
    const uint32_t target = static_cast<uint8_t>(static_cast<IKGrpEnemy*>(m_pParent)->m_vUnk4c.m_ui32NbUsedElt);
    if (m_vUnka8.m_pBlock == nullptr) {
        m_vUnka8.m_ui32NbElt = 1;
        m_vUnka8.m_pBlock = static_cast<uint32_t*>(Mem_AllocAligned16(4));
    }
    uint32_t count = m_vUnka8.m_ui32NbUsedElt;
    for (uint32_t i = 0; i < count; ++i) m_vUnka8.m_pBlock[i] = 0;
    uint32_t added = count;
    while (added < target) {
        const uint32_t used = m_vUnka8.m_ui32NbUsedElt;
        ++added;
        if (m_vUnka8.m_ui32NbElt == used) {
            uint32_t capacity = used + 1;
            uint32_t bytes = capacity * 4;
            if (capacity == 0) {
                capacity = 1;
                bytes = 4;
            }
            m_vUnka8.m_pBlock = static_cast<uint32_t*>(Mem_ReallocAligned16(m_vUnka8.m_pBlock, bytes));
            m_vUnka8.m_ui32NbElt = capacity;
        }
        m_vUnka8.m_pBlock[used] = 0;
        m_vUnka8.m_ui32NbUsedElt = used + 1;
    }
}

SEnemyFormation* FormationOf(IKSerializable* enemy) {
    return static_cast<SEnemyFormation*>(static_cast<IKHkEnemy*>(enemy)->VfEC());  // vt+0xec
}

namespace {
// 0x0025ab38 GetEnemyGroup_2: the game manager's enemy group (+0x04).
IKGrpEnemy* SquadEnemyGroup() { return static_cast<IKGrpEnemy*>(g_pEngine->m_gameManager->m_unk04[0]); }

// 0x002ca268 CKGrpS08Hero_SetInputBlocked_maybe (the hero group's +0xf8 bit 3; IKGrpHero.cpp, local copy).
void SetHeroInputBlocked(uint32_t blocked) {
    CKGrpS08Hero* heroes = static_cast<CKGrpS08Hero*>(g_pEngine->m_gameManager->m_unk04[1]);
    heroes->m_baWorkFlags = (heroes->m_baWorkFlags & ~8u) | (blocked << 3);
}

// 0x00363c78 IKHkHero_GetTargetingPositionPtr_maybe (IKHkHero_2.cpp, local copy): the hero's +0x570 unless its bit 1 is
// set, then its scene node's frame's LTM position (natively RwFrameGetLTM makes it current, as CKHkDetectorGroup's copy).
const CVector3* HeroTargetingPosition(IKSerializable* hero) {
    IKHkHero* h = static_cast<IKHkHero*>(hero);
    if ((h->m_bitArray & 2u) == 0) return reinterpret_cast<const CVector3*>(&h->m_unk570);
    return reinterpret_cast<const CVector3*>(&FrameLtm(static_cast<CSGMovable*>(h->m_pKGLObject)->m_pRwFrame)->pos);
}

// 0x00010690 Math_Sqrtf: the double square root rounded to float.
float MathSqrtfSquad(float x) { return static_cast<float>(std::sqrt(static_cast<double>(x))); }

// 0x00361968 CKHkS08Hero_GetPositionPtr (local copy, as CKHkDetectorGroup.cpp's): the hero's +0x54c unless its bit 1 is
// set and its +0xed4 bit 4 clear, then its scene node's frame's LTM position.
const float* HeroPositionOfSquad(CKHkS08Hero* hero) {
    if ((hero->m_bitArray & 2u) == 0 || ((hero->m_ui32StatusFlagsED4 >> 4) & 1u) != 0) return &hero->m_unk54c;
    return &FrameLtm(static_cast<CSGMovable*>(hero->m_pKGLObject)->m_pRwFrame)->pos.x;
}

// The scene node's frame (a hook's m_pKGLObject +4, an RwFrame) and its modelling position (frame +0x40).
RwFrame* FrameOf(IKSerializable* hook) { return static_cast<CSGMovable*>(static_cast<IKHook*>(hook)->m_pKGLObject)->m_pRwFrame; }

// The squad's members (its hook list, linked by m_pNextHook).
IKHook* FirstMember(CKGrpSquad* squad) { return *reinterpret_cast<IKHook**>(squad->GetMemberListHead()); }  // vt+0xb0

// The key positions of `type` (all, or the free ones): the loop the squad functions inline, from the last position.
int8_t CountKeySlots(const CKChoreoKey* key, uint8_t type, bool freeOnly) {
    if (key == nullptr) return 0;
    uint32_t count = 0;
    for (uint32_t i = key->m_asPos.m_ui32NbUsedElt; i != 0; --i) {
        const CKChoreoKey::SChoreoPos& pos = key->m_asPos.m_pBlock[i - 1];
        if (pos.m_ui8Type == type && (!freeOnly || pos.m_bUsed == 0)) ++count;
    }
    return static_cast<int8_t>(count);
}

// The four per-type counters summed, as the original's signed byte.
int8_t TypeTotal(const CKGrpSquad::SFlags& flags) {
    return static_cast<int8_t>(flags.m_unk00 + flags.m_unk01 + flags.m_unk02 + flags.m_unk03);
}

// The camera switch both spawn camera starts inline: the camera becomes the next one (unless current) and, unless the
// camera service blocks switches (+0x46c bit 4), a cut (the camera's y within 1 of the real one's, or below) or a blend
// of the phase's +0x44 seconds is requested.
void StartSpawnCameraSwitch(IKCamera* camera, float switchTime) {
    CKSrvCamera* service = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);
    const bool cut = service->m_v3RealPos.y <= camera->m_WorldPosition.y - 1.0f;  // TOC 0x27c
    if (service->m_pCurrentCamera == camera) return;
    service->m_pNextCamera = camera;
    if ((service->m_baTemporaryFlags & 0x10u) != 0) return;
    service->m_fSwitchTimer = cut ? 0.0f : switchTime;
    service->m_ui8TransitionMode = 0;
    service->m_baTemporaryFlags |= 0x400000u;
}

// The squad put in (if absent) the camera service's camera owners (+0xe14, count +0xe24).
void AddCameraOwner(IKSerializable* squad) {
    CKSrvCamera* service = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);
    for (uint32_t i = 0; i < service->m_unke24; ++i) {
        if (service->m_apCinematicOwner[i] == squad) return;
    }
    service->m_apCinematicOwner[service->m_unke24++] = squad;
}

// The squad taken out of the camera owners (the last one takes its place).
void RemoveCameraOwner(IKSerializable* squad) {
    CKSrvCamera* service = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);
    const uint32_t count = service->m_unke24;
    for (uint32_t i = 0; i < count; ++i) {
        if (service->m_apCinematicOwner[i] != squad) continue;
        service->m_unke24 = count - 1;
        if (i != count - 1) service->m_apCinematicOwner[i] = service->m_apCinematicOwner[count - 1];
        return;
    }
}

// IKGroup_AddMember 0x992e30 / IKGroup_RemoveMember 0x992e70 (the pools' and squads' vt+0xd8 / vt+0xdc: the hook list
// +0x28 linked by +0x14, and the group's bundle).
void GroupAddMember(IKBaseGroup* group, IKHook* hook) {
    IKHook** head = reinterpret_cast<IKHook**>(group->GetMemberListHead());
    hook->m_pNextHook = *head;
    *head = hook;
    static_cast<CKBundle*>(group->m_pKBundle)->AddHook(hook);  // 0x1dd6d8
}
void GroupRemoveMember(IKBaseGroup* group, IKHook* hook) {
    IKHook** head = reinterpret_cast<IKHook**>(group->GetMemberListHead());
    if (*head != nullptr) {
        if (*head == hook) {
            *head = hook->m_pNextHook;
            hook->m_pNextHook = nullptr;
        } else {
            IKHook* prev = *head;
            while (prev->m_pNextHook != nullptr && prev->m_pNextHook != hook) prev = prev->m_pNextHook;
            if (prev->m_pNextHook == hook) {
                prev->m_pNextHook = hook->m_pNextHook;
                hook->m_pNextHook = nullptr;
            }
        }
    }
    static_cast<CKBundle*>(group->m_pKBundle)->RemoveHook(hook);  // 0x1dd8c0
}

// DOTD: the respawn nodes' free list (FreeListPool 0x00ceaa20's 16-byte pool in the original).
CKGrpSquad::SRespawnNode* s_pFreeRespawnNodes = nullptr;
CKGrpSquad::SRespawnNode* TakeRespawnNode() {
    if (s_pFreeRespawnNodes == nullptr) return new CKGrpSquad::SRespawnNode();
    CKGrpSquad::SRespawnNode* node = s_pFreeRespawnNodes;
    s_pFreeRespawnNodes = node->m_pNext;
    return node;
}
void GiveRespawnNode(CKGrpSquad::SRespawnNode* node) {
    node->m_pNext = s_pFreeRespawnNodes;
    s_pFreeRespawnNodes = node;
}

// A matrix's 16 words copied (the original copies the rows with their fourth words).
void CopyMatrix(CMatrix34* to, const CMatrix34* from) { std::memcpy(to, from, sizeof(CMatrix34)); }
}  // namespace

// 0x0001d5c0 Group_TransferHook_maybe for the groups whose vt+0xd8 / vt+0xdc are IKGroup_AddMember / RemoveMember (the
// pools, the squads, the weapon pools; their vt+0xe0 / vt+0xe4 are empty): nothing when `from` is null or locked (+0xc
// bit 4); out of `from`; into `to` unless it is in a sleeping state (+0xc bit 3), else back into `from` unless that one
// is. Group_CanAcceptHookRecursive 0x124b0 accepts every hook in these chains (vt+0xbc: IsKindOfClass(2) and vt+0xc0
// returns 1; no vt+0xcc returns 1 before the root), so it is not tested. 1 when the hook reached `to`.
int32_t Group_TransferHook(IKHook* hook, IKBaseGroup* to, IKBaseGroup* from) {
    if (from == nullptr || (from->m_bitArray & 0x10u) != 0) return 0;
    GroupRemoveMember(from, hook);
    if ((to->m_bitArray & 8u) == 0) {
        GroupAddMember(to, hook);
        return 1;
    }
    if ((from->m_bitArray & 8u) != 0) return 0;
    GroupAddMember(from, hook);
    return 0;
}

CKGrpFightZone* CKGrpSquad::GetFightZone() { return static_cast<CKGrpFightZone*>(static_cast<IKBaseGroup*>(m_pParent)); }

CKChoreoKey* CKGrpSquad::CurrentKey() { return static_cast<CKChoreography*>(m_vStates.m_pBlock[m_unk55].m_pUnk34)->GetCurrentKey(); }

// 0x0025d940 UpdateCKGrpSquad: the phase's spawn delay and time, the spawn camera's end, the dead members, the
// choreography and anchor (while spawns are wanted or members exist), the pending spawns and respawns, the formation
// slots, then the next phase when the kill counts are reached.
void CKGrpSquad::Update(IKTime* clock) {
    SState* state = &m_vStates.m_pBlock[m_unk55];
    if (state->m_unk40[3] > m_unk98) m_unk98 = m_unk98 + clock->m_afDeltaTime[0];
    if (m_unk94 != 0) {
        m_unk90 = m_unk90 + clock->m_afDeltaTime[0];
        state = &m_vStates.m_pBlock[m_unk55];
        if (state->m_unk40[0] <= m_unk90) {  // the spawn camera's time is over
            if (state->m_pUnk3c != nullptr) RemoveCameraOwner(this);
            SetHeroInputBlocked(0);  // 0x2ca268
            m_unk94 = 0;
        }
    }
    state = &m_vStates.m_pBlock[m_unk55];
    if (state->m_unk54 >= 0.0f) {
        SquadEnemyGroup();  // GetEnemyGroup_2, its result unused
        state = &m_vStates.m_pBlock[m_unk55];
        state->m_unk54 = state->m_unk54 - clock->m_afDeltaTime[0];
        const uint8_t phase = m_unk55;
        if (m_vStates.m_pBlock[phase].m_unk54 <= 0.0f && m_vStates.m_ui32NbUsedElt - 1 > phase) {
            SetPhase(static_cast<uint8_t>(phase + 1));
        }
    }
    ProcessDeadMembers();
    if (HasSpawnRequest() != 0 || FirstMember(this) != nullptr) {
        UpdateChoreography(clock);
        UpdateAnchorFromPhase(clock);
    }
    SpawnPendingMembers();
    ProcessRespawnTimers(clock);
    if (FirstMember(this) != nullptr) AssignAllFormationSlots();
    const uint8_t phase = m_unk55;
    state = &m_vStates.m_pBlock[phase];
    const int32_t kills = state->m_unk58;
    if (kills > 0 && m_unka4 >= kills) {
        if (m_vStates.m_ui32NbUsedElt > phase && state->m_unk69 == 0) {
            SetPhase(static_cast<uint8_t>(phase + 1));
            return;
        }
        if (m_vStates.m_ui32NbUsedElt > phase && state->m_unk69 != 0) {
            // falls to the per-type test below (the original's 0x25db80)
        } else if (state->m_unk69 != 0) {
            return;
        }
    } else if (state->m_unk69 != 0) {
        return;
    }
    const uint32_t types = state->m_vUnk5c.m_ui32NbUsedElt;
    if (state->m_unk6a == 0) {  // any type's count reached
        for (uint32_t i = 0; i < types; ++i) {
            const int32_t need = static_cast<int32_t>(state->m_vUnk5c.m_pBlock[i]);
            if (need > 0 && static_cast<int32_t>(m_vUnka8.m_pBlock[i]) >= need) {
                SetPhase(static_cast<uint8_t>(phase + 1));
                return;
            }
        }
        return;
    }
    for (uint32_t i = 0; i < types; ++i) {  // every type's count reached
        const int32_t need = static_cast<int32_t>(state->m_vUnk5c.m_pBlock[i]);
        if (need > 0 && static_cast<int32_t>(m_vUnka8.m_pBlock[i]) < need) return;
    }
    SetPhase(static_cast<uint8_t>(phase + 1));
}

// 0x0025b160 CKGrpSquad_ActivateSpawnCamera_maybe: once (+0xcc), the phase's camera (+0x3c) is started for the squad's
// spawn: the squad owns the camera, the switch is requested, the timer +0x90 starts and the heroes' input is blocked.
void CKGrpSquad::ActivateSpawnCamera() {
    SState& state = m_vStates.m_pBlock[m_unk55];
    if (state.m_pUnk3c == nullptr || m_unkcc != 0) return;
    AddCameraOwner(this);
    SState& current = m_vStates.m_pBlock[m_unk55];
    StartSpawnCameraSwitch(static_cast<IKCamera*>(current.m_pUnk3c), current.m_unk40[1]);
    m_unk94 = 1;
    m_unk90 = 0.0f;
    SetHeroInputBlocked(1);  // 0x2ca268
    m_unkcc = 1;
}

// 0x002604c0 CKGrpSquad_HasSpawnRequest_maybe: a type with pending spawns (byte 1).
uint8_t CKGrpSquad::HasSpawnRequest() {
    for (uint32_t i = 0; GetFightZone()->m_vUnk4c.m_ui32NbUsedElt > i; ++i) {
        if (m_vUnk2c.m_pBlock[i].m_unk01 != 0) return 1;
    }
    return 0;
}

// 0x00260568 CKGrpSquad_ClearSpawnCountsAndRespawnQueue_maybe
void CKGrpSquad::ClearSpawnCountsAndRespawnQueue() {
    for (uint32_t i = 0; GetFightZone()->m_vUnk4c.m_ui32NbUsedElt > i; ++i) {
        SFlags& flags = m_vUnk2c.m_pBlock[i];
        flags.m_unk00 = 0;
        flags.m_unk01 = 0;
        flags.m_unk02 = 0;
        flags.m_unk03 = 0;
    }
    for (SRespawnNode* node = m_unk50; node != nullptr;) {
        SRespawnNode* next = node->m_pNext;
        GiveRespawnNode(node);
        node = next;
    }
    m_unk50 = nullptr;
}

// 0x00260668 CKGrpSquad_ReturnEnemyToFightZonePool_maybe: the enemy deactivated (vt+0xd0), moved back to its type's pool
// and put to sleep there.
void CKGrpSquad::ReturnEnemyToFightZonePool(uint8_t type, IKSerializable* enemy) {
    CKCoreManager* core = g_pEngine->m_coreManager;
    static_cast<IKHkEnemy*>(enemy)->Deactivate();  // vt+0xd0
    IKBaseGroup* pool = static_cast<IKBaseGroup*>(GetFightZone()->m_vUnk4c.m_pBlock[type].m_pRef);
    Group_TransferHook(static_cast<IKHook*>(enemy), pool, this);  // Group_TransferHook_maybe 0x1d5c0
    SetObjectActiveInContext(core, static_cast<IKLife*>(enemy), 0, pool);  // 0x1cb10
}

// 0x00260748 CKGrpSquad_ReleaseMember_maybe: the member's key slot freed, the enemy back to its pool, its squad (+0x168)
// and +0x188 cleared, its flags +0xc bit 4 set, its scene node hidden (+0x10 bit 2), then its vt+0xd4.
void CKGrpSquad::ReleaseMember(IKSerializable* member) {
    IKHkEnemy* enemy = static_cast<IKHkEnemy*>(member);
    const uint8_t type = FormationOf(member)->m_type;
    const int32_t slot = FormationOf(member)->m_slot;
    if (slot >= 0) CurrentKey()->m_asPos.m_pBlock[slot].m_bUsed = 0;
    ReturnEnemyToFightZonePool(type, member);
    enemy->m_pGroupSquad = nullptr;
    enemy->m_pEnemyCpnt = nullptr;
    enemy->m_bitArray |= 0x10u;
    static_cast<CSGLeaf*>(enemy->m_pKGLObject)->m_sgProperties |= 4u;
    enemy->VfD4();  // vt+0xd4
}

// 0x002608c8 CKGrpSquad_TakeEnemyFromFightZonePool_maybe: from the type's pool (when the zone allows spawning), the first
// enemy (following the pool links +0xb8) that accepts the squad (vt+0xd8) gets vt+0xc8, moves into the squad, is woken
// there and remembers the type (+0x1b4).
IKSerializable* CKGrpSquad::TakeEnemyFromFightZonePool(uint8_t type) {
    IKBaseGroup* pool = static_cast<IKBaseGroup*>(GetFightZone()->m_vUnk4c.m_pBlock[type].m_pRef);
    if (pool == nullptr) return nullptr;
    CKCoreManager* core = g_pEngine->m_coreManager;
    if (GetFightZone()->IsSpawningAllowed() == 0) return nullptr;  // 0x26e120
    pool = static_cast<IKBaseGroup*>(GetFightZone()->m_vUnk4c.m_pBlock[type].m_pRef);
    for (IKHook* hook = *reinterpret_cast<IKHook**>(pool->GetMemberListHead()); hook != nullptr;
         hook = static_cast<IKHook*>(static_cast<IKHkEnemy*>(hook)->m_unkB8)) {
        IKHkEnemy* enemy = static_cast<IKHkEnemy*>(hook);
        if (enemy->CanSpawnFromSquad(this) == 0) continue;  // vt+0xd8
        enemy->VfC8();                                      // vt+0xc8
        IKBaseGroup* from = static_cast<IKBaseGroup*>(GetFightZone()->m_vUnk4c.m_pBlock[type].m_pRef);
        Group_TransferHook(hook, this, from);                  // Group_TransferHook_maybe 0x1d5c0
        SetObjectActiveInContext(core, enemy, 1, this);     // 0x1cb10
        static_cast<CKHkS08Enemy*>(enemy)->m_unk1b4 = type;
        return enemy;
    }
    return nullptr;
}

// 0x00260a88 CKGrpSquad_ProcessDeadMembers_maybe: members whose bit 3 is set are done: bit 5 set: only released; bit 4
// clear: removed (the zone's counts lowered, bit 4 set); bit 4 set: killed (the squad's and zone's trigger starters
// fired, the kill counts raised). Then the enemy group's vt+0x164, bit 5 set, the node hidden, the type's member count
// lowered and the member released.
void CKGrpSquad::ProcessDeadMembers() {
    IKHook* member = FirstMember(this);
    while (member != nullptr) {
        IKHook* next = member->m_pNextHook;
        const uint32_t flags = member->m_bitArray;
        if ((flags & 8u) == 0) {
            member = next;
            continue;
        }
        if ((flags & 0x20u) != 0) {
            ReleaseMember(member);
            member = next;
            continue;
        }
        if ((flags & 0x10u) == 0) {
            const uint8_t type = FormationOf(member)->m_type;
            CKGrpFightZone::SEntry4c& kind = GetFightZone()->m_vUnk4c.m_pBlock[type];
            kind.m_unk08 = static_cast<uint16_t>(kind.m_unk08 - 1);
            member->m_bitArray |= 0x10u;
            --GetFightZone()->m_unk88;
        } else {
            QueueTriggerSignals(&m_tsUnk68);
            QueueTriggerSignals(&GetFightZone()->m_aTriggers[1]);  // +0xb4
            CKGrpFightZone* zone = GetFightZone();
            ++zone->m_vUnk4c.m_pBlock[FormationOf(member)->m_type].m_unk0c;
            ++m_unka4;
            ++m_vUnka8.m_pBlock[FormationOf(member)->m_type];
        }
        static_cast<CKGrpS08Enemy*>(SquadEnemyGroup())->ReleaseAttackSlotOf(member);  // vt+0x164 0x267220
        member->m_bitArray |= 0x20u;
        static_cast<CSGLeaf*>(member->m_pKGLObject)->m_sgProperties |= 4u;
        SFlags& counts = m_vUnk2c.m_pBlock[FormationOf(member)->m_type];
        counts.m_unk00 = static_cast<uint8_t>(counts.m_unk00 - 1);
        ReleaseMember(member);
        member = next;
    }
}

// 0x00260db0 CKGrpSquad_ReleaseAllMembers_maybe
void CKGrpSquad::ReleaseAllMembers() {
    IKHook* member = FirstMember(this);
    while (member != nullptr) {
        IKHook* next = member->m_pNextHook;
        if ((member->m_bitArray & 0x20u) == 0) {
            SFlags& counts = m_vUnk2c.m_pBlock[FormationOf(member)->m_type];
            counts.m_unk00 = static_cast<uint8_t>(counts.m_unk00 - 1);
            CKGrpFightZone::SEntry4c& kind = GetFightZone()->m_vUnk4c.m_pBlock[FormationOf(member)->m_type];
            kind.m_unk08 = static_cast<uint16_t>(kind.m_unk08 - 1);
            --GetFightZone()->m_unk88;
        }
        ReleaseMember(member);
        member = next;
    }
}

// 0x00260f38 CKGrpSquad_SpawnMember_maybe: an enemy of `type` from the pool, its +0x188 from the pool's +0x30 list (by the
// zone's type entry's byte +0x04), its formation block at the squad's anchor (slot -1, flags 1), the squad as its squad,
// its node shown, then its vt+0xcc (Activate).
IKSerializable* CKGrpSquad::SpawnMember(uint8_t type) {
    IKSerializable* spawned = TakeEnemyFromFightZonePool(type);
    if (spawned == nullptr) return nullptr;
    IKHkEnemy* enemy = static_cast<IKHkEnemy*>(spawned);
    CKGrpFightZone::SEntry4c& kind = GetFightZone()->m_vUnk4c.m_pBlock[type];
    CKGrpPoolSquad* pool = static_cast<CKGrpPoolSquad*>(GetFightZone()->m_vUnk4c.m_pBlock[type].m_pRef);
    enemy->m_pEnemyCpnt = static_cast<CKS08EnemyCpnt*>(pool->m_vUnk30.m_pBlock[kind.m_unk04]);  // the pool's +0x30 list (LVL010: CKS08EnemyCpnt)
    SEnemyFormation* formation = FormationOf(spawned);
    formation->m_type = type;
    formation->m_slot = -1;
    formation->m_flags = (formation->m_flags & ~3u) | 1u;
    formation->m_vPos = m_pCurrentMatrix->m_pos;
    formation->m_vDir = m_pCurrentMatrix->m_at;
    enemy->m_pGroupSquad = this;
    static_cast<CSGLeaf*>(enemy->m_pKGLObject)->m_sgProperties &= ~4u;
    enemy->Activate();  // vt+0xcc
    return spawned;
}

// 0x00261280 CKGrpSquad_QueueSpawnsToFillFormation_maybe: the type's pending spawns raised to fill the key's positions of
// the type, unless the zone's type or total cap is reached.
void CKGrpSquad::QueueSpawnsToFillFormation(uint32_t type) {
    const int8_t wanted = CountKeySlots(CurrentKey(), static_cast<uint8_t>(type), false);
    SFlags& flags = m_vUnk2c.m_pBlock[type];
    if (TypeTotal(flags) >= wanted) return;
    const CKGrpFightZone::SEntry4c& kind = GetFightZone()->m_vUnk4c.m_pBlock[type];
    if (kind.m_unk06 != -1 && static_cast<int16_t>(kind.m_unk08) >= kind.m_unk06) return;
    if (GetFightZone()->m_unk84 != -1 && GetFightZone()->m_unk84 <= GetFightZone()->m_unk88) return;
    SFlags& counts = m_vUnk2c.m_pBlock[type];
    counts.m_unk01 = static_cast<uint8_t>(wanted - TypeTotal(counts) + counts.m_unk01);
}

namespace {
struct SSpawnEntry {         // 8 bytes (the original's qsort elements)
    uint32_t m_index;        // +0x00 the key position
    uint8_t m_priority;      // +0x04 its priority
    uint8_t m_pad05[3];
};
static_assert(sizeof(SSpawnEntry) == 8, "qsort element");
// 0x009bafb0 CKGrpSquad_SpawnEntryCompareByByte4_maybe
int CompareSpawnEntries(const void* a, const void* b) {
    return static_cast<int>(static_cast<const SSpawnEntry*>(a)->m_priority) - static_cast<const SSpawnEntry*>(b)->m_priority;
}
}  // namespace

// 0x00261928 CKGrpSquad_SpawnPendingMembers_maybe: once the phase's spawn delay is over, the key's free positions, by
// priority (qsort), spawn the pending enemies of their type: at a spawn point of the zone, else at the position itself.
void CKGrpSquad::SpawnPendingMembers() {
    SState& state = m_vStates.m_pBlock[m_unk55];
    if (!(m_unk98 >= state.m_unk40[3])) return;
    const uint32_t count = CurrentKey()->m_asPos.m_ui32NbUsedElt;
    SSpawnEntry* entries = static_cast<SSpawnEntry*>(Mem_AllocAligned16(8));
    uint32_t capacity = 1;
    for (uint32_t i = 0; i < count; ++i) {
        const uint8_t priority = CurrentKey()->m_asPos.m_pBlock[i].m_ui8Priority;
        if (i == capacity) {
            capacity = i + 1;
            entries = static_cast<SSpawnEntry*>(Mem_ReallocAligned16(entries, (capacity * 8u) & ~7u));
        }
        entries[i].m_index = i;
        entries[i].m_priority = priority;
    }
    Ps3Qsort(entries, count, 8, CompareSpawnEntries);  // 0x95eab0 through TocBridge_qsort
    for (uint32_t k = 0; k < count; ++k) {
        CKChoreoKey::SChoreoPos& pos = CurrentKey()->m_asPos.m_pBlock[entries[k].m_index];
        if (pos.m_bUsed != 0 || m_vUnk2c.m_ui32NbUsedElt <= pos.m_ui8Type) continue;
        if (m_vUnk2c.m_pBlock[pos.m_ui8Type].m_unk01 == 0) continue;
        const uint8_t capped = GetFightZone()->IsSpawnCapReached(pos.m_ui8Type);  // 0x2723c8
        if (capped != 0) continue;
        IKSerializable* enemy = SpawnMember(pos.m_ui8Type);
        if (enemy == nullptr) continue;
        pos.m_bUsed = 1;
        FormationOf(enemy)->m_slot = static_cast<int32_t>(entries[k].m_index);
        if (GetFightZone()->SpawnAtSpawnPoint(enemy) == 0) {
            AssignFormationSlot(enemy);
            CVector3 position = FormationOf(enemy)->m_vPos;
            CVector3 direction = FormationOf(enemy)->m_vDir;
            static_cast<IKHkEnemy*>(enemy)->SpawnAtPosition(&position, &direction, 0);  // vt+0xdc
        }
        GetFightZone()->AddSpawnedCount(pos.m_ui8Type, 1);
        SFlags& flags = m_vUnk2c.m_pBlock[pos.m_ui8Type];
        flags.m_unk01 = static_cast<uint8_t>(flags.m_unk01 - 1);
        flags.m_unk00 = static_cast<uint8_t>(flags.m_unk00 + 1);
        m_vUnkb4.m_pBlock[pos.m_ui8Type] = capped;
        if (m_vUnk2c.m_pBlock[pos.m_ui8Type].m_unk01 == 0) m_vUnkc0.m_pBlock[pos.m_ui8Type] = 1;
    }
    if (entries != nullptr) Mem_FreeAligned16(entries);
}

// 0x00261e00 CKGrpSquad_SpawnFullFormation_maybe (0x2620e8 jumps here): every type's key positions filled at once, at the
// positions themselves; the spawns the pool cannot give are left pending, a capped type's pending spawns cleared.
void CKGrpSquad::SpawnFullFormation() {
    for (uint32_t type = 0; GetFightZone()->m_vUnk4c.m_ui32NbUsedElt > type; ++type) {
        int32_t left = CountKeySlots(CurrentKey(), static_cast<uint8_t>(type), false);
        if (left == 0) continue;
        for (;;) {
            if (GetFightZone()->IsSpawnCapReached(static_cast<uint8_t>(type)) != 0) {
                m_vUnk2c.m_pBlock[type].m_unk01 = 0;
                break;
            }
            IKSerializable* enemy = SpawnMember(static_cast<uint8_t>(type));
            if (enemy == nullptr) {
                SFlags& flags = m_vUnk2c.m_pBlock[type];
                flags.m_unk01 = static_cast<uint8_t>(flags.m_unk01 + left);
                break;
            }
            AssignFormationSlot(enemy);
            --left;
            CVector3 position = FormationOf(enemy)->m_vPos;
            CVector3 direction = FormationOf(enemy)->m_vDir;
            static_cast<IKHkEnemy*>(enemy)->SpawnAtPosition(&position, &direction, 0);  // vt+0xdc
            GetFightZone()->AddSpawnedCount(static_cast<uint8_t>(type), 1);
            SFlags& flags = m_vUnk2c.m_pBlock[type];
            flags.m_unk00 = static_cast<uint8_t>(flags.m_unk00 + 1);
            if (left == 0) break;
        }
    }
}

// 0x002620f0 CKGrpSquad_ProcessRespawnTimers_maybe: the queued respawns count down; a due one queues its spawns (kind 1),
// adds one (kind 2) or its count (kind 3) to the type's pending spawns while the key wants more, and is freed.
void CKGrpSquad::ProcessRespawnTimers(IKTime* clock) {
    SRespawnNode* prev = nullptr;
    SRespawnNode* node = m_unk50;
    while (node != nullptr) {
        node->m_fTimer = node->m_fTimer - clock->m_afDeltaTime[0];
        if (!(node->m_fTimer <= 0.0f)) {
            prev = node;
            node = node->m_pNext;
            continue;
        }
        const uint8_t type = node->m_type;
        if (node->m_kind == 2 || node->m_kind == 3) {
            const int8_t wanted = CountKeySlots(CurrentKey(), type, false);
            SFlags& flags = m_vUnk2c.m_pBlock[type];
            if (TypeTotal(flags) < wanted) {
                flags.m_unk01 = static_cast<uint8_t>(flags.m_unk01 + (node->m_kind == 2 ? 1u : node->m_count));
            }
        } else if (node->m_kind == 1) {
            QueueSpawnsToFillFormation(type);
        }
        SRespawnNode* next = node->m_pNext;
        if (m_unk50 == node) {
            m_unk50 = next;
            prev = nullptr;
        } else {
            prev->m_pNext = next;
        }
        GiveRespawnNode(node);
        node = next;
    }
}

namespace {
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};    // 0x00c50d40 (filled by a static initialiser in the original)
const CVector3 kNull = {0.0f, 0.0f, 0.0f};     // 0x00c50d64
const CVector3 kAxisZ = {0.0f, 0.0f, 1.0f};    // 0x00c50d4c

// The direction toward `target` in the horizontal plane (y 0), normalised, set as the matrix's look direction (with the
// world up) unless it is the null vector: the block UpdateAnchorFromPhase inlines for its modes 1 to 4.
void FaceTowards(CMatrix34* matrix, const CVector3& target) {
    CVector3 dir;
    dir.x = target.x - matrix->m_pos.x;
    dir.y = 0.0f;
    dir.z = target.z - matrix->m_pos.z;
    if (kNull.x == dir.x && kNull.y == 0.0f && kNull.z == dir.z) return;
    const float length = MathSqrtfSquad(ppc::fmadds(dir.z, dir.z, ppc::fmadds(dir.x, dir.x, 0.0f)));
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        dir.z = dir.z * inverse;
        dir.x = dir.x * inverse;
        dir.y = dir.y * inverse;
    }
    Mat4_SetBasisFromAtUp(matrix, &dir, &kAxisY);  // 0x0023fd30
}
}  // namespace

// 0x0025bd50 CKGrpSquad_AssignFormationSlot_maybe: the member's key slot freed, then the free position of its type with a
// priority not above the old one's (any with flag +0x2a: priority 0 only) nearest to its node (horizontally) taken; the
// member's formation block gets the slot, the position and direction through the squad's anchor (or the anchor itself
// without a slot), facing the first controlled hero when the phase says so (+0x38), and the key's flags.
void CKGrpSquad::AssignFormationSlot(IKSerializable* member) {
    CKChoreoKey* key = CurrentKey();
    SEnemyFormation* formation = FormationOf(member);
    int32_t slot = formation->m_slot;
    const uint8_t type = FormationOf(member)->m_type;
    float best = 0x1.fffffep+127f;  // 0x00c4ace0 (FLT_MAX)
    uint8_t priority = 0xff;
    if (slot >= 0) {
        if (key->m_asPos.m_ui32NbUsedElt <= static_cast<uint32_t>(slot)) {
            slot = -1;
        } else {
            priority = key->m_asPos.m_pBlock[slot].m_ui8Priority;
            key->m_asPos.m_pBlock[slot].m_bUsed = 0;
        }
    }
    if (FormationOf(member)->m_unk2a != 0) {
        slot = -1;
        priority = 0;
    }
    const RwFrame* frame = FrameOf(member);
    for (uint32_t i = key->m_asPos.m_ui32NbUsedElt; i != 0; --i) {
        const CKChoreoKey::SChoreoPos& pos = key->m_asPos.m_pBlock[i - 1];
        if (pos.m_bUsed != 0 || pos.m_ui8Type != type || priority < pos.m_ui8Priority) continue;
        CVector3 world;
        Mat4_TransformPoints(m_pCurrentMatrix, &world, &pos.m_vPos, 1);  // 0x0023f7e8
        const float dz = world.z - frame->modelling.pos.z;
        const float dx = world.x - frame->modelling.pos.x;
        const float distance = ppc::fmadds(dx, dx, dz * dz);
        if (best <= distance) continue;
        best = distance;
        slot = static_cast<int32_t>(i - 1);
        priority = pos.m_ui8Priority;
    }
    CVector3 position;
    CVector3 direction;
    if (slot < 0) {
        position = m_pCurrentMatrix->m_pos;
        direction = m_pCurrentMatrix->m_at;
    } else {
        CKChoreoKey::SChoreoPos& pos = key->m_asPos.m_pBlock[slot];
        pos.m_bUsed = 1;
        Mat4_TransformPoints(m_pCurrentMatrix, &position, &pos.m_vPos, 1);  // 0x0023f7e8
        if (m_vStates.m_pBlock[m_unk55].m_unk38 == 0) {
            Mat4_TransformVectors(m_pCurrentMatrix, &direction, &key->m_asPos.m_pBlock[slot].m_vDir, 1);  // 0x0023f7b0
        }
    }
    if (m_vStates.m_pBlock[m_unk55].m_unk38 != 0) {  // face the first controlled hero
        CKGrpS08Hero* heroes = static_cast<CKGrpS08Hero*>(g_pEngine->m_gameManager->m_unk04[1]);
        const float* hero = HeroPositionOfSquad(static_cast<CKHkS08Hero*>(heroes->m_apControlledHeroes[0]));
        direction.x = hero[0] - position.x;
        direction.z = hero[2] - position.z;
        direction.y = 0.0f;
        if (direction.x == 0.0f && direction.z == 0.0f) {
            direction = kAxisZ;  // 0x00c50d4c
        } else {
            const float length = MathSqrtfSquad(ppc::fmadds(direction.z, direction.z, ppc::fmadds(direction.x, direction.x, 0.0f)));
            if (length != 0.0f) {
                const float inverse = 1.0f / length;
                direction.z = direction.z * inverse;
                direction.x = direction.x * inverse;
                direction.y = direction.y * inverse;
            }
        }
    }
    formation = FormationOf(member);
    formation->m_slot = slot;
    FormationOf(member)->m_vPos = position;
    FormationOf(member)->m_vDir = direction;
    SEnemyFormation* flags = FormationOf(member);
    flags->m_flags = (flags->m_flags & ~3u) | (key->m_baFlags & 3u);
}

namespace {
// 0x0025caa0 CKGrpSquad_AssignFormationSlotsRecursive_maybe: the members from the last one to `member`.
void AssignFormationSlotsFrom(CKGrpSquad* squad, IKHook* member) {
    if (member == nullptr) return;
    AssignFormationSlotsFrom(squad, member->m_pNextHook);
    squad->AssignFormationSlot(member);
}
}  // namespace

// 0x0025cc48 CKGrpSquad_AssignAllFormationSlots_maybe: every member, from the last one.
void CKGrpSquad::AssignAllFormationSlots() {
    IKHook* first = FirstMember(this);
    if (first == nullptr) return;
    AssignFormationSlotsFrom(this, first->m_pNextHook);
    AssignFormationSlot(first);
}

// 0x0025b600 CKGrpSquad_UpdateChoreography_maybe: when the choreography's key changes, every member's formation block
// says so (+0x29) and the trigger starters +0x70 (and +0x78 on the first key) fire; otherwise the flags are cleared.
void CKGrpSquad::UpdateChoreography(IKTime* clock) {
    CKChoreography* choreography = static_cast<CKChoreography*>(m_vStates.m_pBlock[m_unk55].m_pUnk34);
    if (choreography->Update(clock) == 0) {  // 0x264818
        for (IKHook* member = FirstMember(this); member != nullptr; member = member->m_pNextHook) FormationOf(member)->m_bMoving = 0;
        return;
    }
    for (IKHook* member = FirstMember(this); member != nullptr; member = member->m_pNextHook) FormationOf(member)->m_bMoving = 1;
    QueueTriggerSignals(&m_tsUnk70);
    if (static_cast<CKChoreography*>(m_vStates.m_pBlock[m_unk55].m_pUnk34)->m_ui8CurrentKey == 0) QueueTriggerSignals(&m_tsUnk78);
}

// 0x0025ccd8 CKGrpSquad_FaceNearestHero_maybe: the anchor looks at the nearest companion hero (horizontally; searched
// from the last one, nearer than 100000).
void CKGrpSquad::FaceNearestHero() {
    CKGrpS08Hero* heroes = static_cast<CKGrpS08Hero*>(g_pEngine->m_gameManager->m_unk04[1]);
    const uint32_t count = heroes->m_ui8CompanionHeroCount;  // GetCompanionHeroCount 0x2ca290
    bool found = false;
    float best = 100000.0f;  // TOC 0x29c
    CVector3 dir = {0.0f, 0.0f, 0.0f};
    for (uint32_t i = count; i != 0; --i) {
        IKSerializable* hero = heroes->m_apCompanionHeroes[i - 1];  // GetCompanionHeroArray 0x2ca0e8
        if (hero == nullptr) continue;
        const CVector3* target = HeroTargetingPosition(hero);
        float dx = target->x - m_pCurrentMatrix->m_pos.x;
        float dz = target->z - m_pCurrentMatrix->m_pos.z;
        if (kNull.x == dx && kNull.y == 0.0f && kNull.z == dz) continue;
        float length = MathSqrtfSquad(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, 0.0f)));
        float dy;
        if (length == 0.0f) {
            length = 0.0f;
            dy = 0.0f;
        } else {
            const float inverse = 1.0f / length;
            dz = dz * inverse;
            dx = dx * inverse;
            dy = inverse * 0.0f;
        }
        if (found && length >= best) continue;
        best = length;
        dir.x = dx;
        dir.y = dy;
        dir.z = dz;
        found = true;
    }
    if (found) Mat4_SetBasisFromAtUp(m_pCurrentMatrix, &dir, &kAxisY);  // 0x0023fd30
}

// 0x0025ceb8 CKGrpSquad_UpdateAnchorFromPhase_maybe: the anchor (+0x64) is the phase's matrix (fixed phases) turned by
// the phase's mode (1: toward the first controlled hero, 2: toward the phase's point +0x20, 3: toward its object +0x2c,
// 4: toward the camera, 6: toward the nearest companion hero); a following phase (+0x04) takes the position (mode 5:
// the whole matrix) of its object (+0x08) or of a hero (the enemy group's GetHeroMatrix), within the threshold +0x18 when
// +0x14 is set.
void CKGrpSquad::UpdateAnchorFromPhase(IKTime* /*clock*/) {
    SState* state = &m_vStates.m_pBlock[m_unk55];
    if (state->m_unk04 == 0) CopyMatrix(m_pCurrentMatrix, state->m_pMatrix);
    state = &m_vStates.m_pBlock[m_unk55];
    switch (state->m_unk10) {
        case 1: {
            CKGrpS08Hero* heroes = static_cast<CKGrpS08Hero*>(g_pEngine->m_gameManager->m_unk04[1]);
            FaceTowards(m_pCurrentMatrix, *HeroTargetingPosition(heroes->m_apControlledHeroes[0]));
            break;
        }
        case 2: {
            CVector3 point = {state->m_unk20[0], state->m_unk20[1], state->m_unk20[2]};
            FaceTowards(m_pCurrentMatrix, point);
            break;
        }
        case 3:
            if (state->m_pUnk2c != nullptr) FaceTowards(m_pCurrentMatrix, *reinterpret_cast<const CVector3*>(&FrameOf(state->m_pUnk2c)->modelling.pos));
            break;
        case 4:
            FaceTowards(m_pCurrentMatrix, static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera)->m_v3RealPos);
            break;
        case 6:
            FaceNearestHero();
            break;
        default:
            break;
    }
    state = &m_vStates.m_pBlock[m_unk55];
    if (state->m_unk04 == 0) return;
    CKGrpS08Enemy* enemies = static_cast<CKGrpS08Enemy*>(g_pEngine->m_gameManager->m_unk04[0]);
    if (state->m_unk10 == 5) {
        const CVector3 old = m_pCurrentMatrix->m_pos;
        if (state->m_pUnk08 != nullptr) {
            std::memcpy(m_pCurrentMatrix, &FrameOf(state->m_pUnk08)->modelling, sizeof(CMatrix34));
        } else {
            enemies->GetHeroMatrix(state->m_unk0c, m_pCurrentMatrix);  // vt+0x14c
        }
        const SState& now = m_vStates.m_pBlock[m_unk55];
        if (now.m_unk14 == 0) return;
        const float dy = m_pCurrentMatrix->m_pos.y - old.y;
        const float dx = m_pCurrentMatrix->m_pos.x - old.x;
        const float dz = m_pCurrentMatrix->m_pos.z - old.z;
        const float distance = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
        if (distance >= now.m_unk18) return;
        m_pCurrentMatrix->m_pos = old;
        m_pCurrentMatrix->m_ui32Flags &= ~0x20000u;
        return;
    }
    CVector3 target;
    if (state->m_pUnk08 != nullptr) {
        target = *reinterpret_cast<const CVector3*>(&FrameLtm(FrameOf(state->m_pUnk08))->pos);
    } else {
        CMatrix34 hero;
        enemies->GetHeroMatrix(state->m_unk0c, &hero);  // vt+0x14c
        target = hero.m_pos;
    }
    state = &m_vStates.m_pBlock[m_unk55];
    if (state->m_unk14 != 0) {
        const float dy = m_pCurrentMatrix->m_pos.y - target.y;
        const float dx = m_pCurrentMatrix->m_pos.x - target.x;
        const float dz = m_pCurrentMatrix->m_pos.z - target.z;
        const float distance = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
        if (distance <= state->m_unk18) return;
    }
    m_pCurrentMatrix->m_pos = target;
    m_pCurrentMatrix->m_ui32Flags &= ~0x20000u;
}

// 0x0025ca10 CKGrpSquad_ApplyPendingChoreography_maybe: with +0x55 equal to +0x54, +0xa0 set and a start state, the
// phase of that state (its index; the loop also tests the slot one past the last, as the original) is set.
void CKGrpSquad::ApplyPendingChoreography() {
    if (m_unk55 != m_unk54) return;
    if (m_unka0 == 0) return;
    const SState* start = m_pStartState;
    if (start == nullptr) return;
    const uint32_t count = m_vStates.m_ui32NbUsedElt;
    if (count == 0) return;
    for (uint32_t i = 0; i <= count; ++i) {
        if (start == m_vStates.m_pBlock + i) {
            SetPhase(static_cast<uint8_t>(i));
            return;
        }
    }
}

// 0x0025c278 CKGrpSquad_SetPhase_maybe: the trigger starter +0x80; a running spawn camera stopped; while awake the
// kill counts reset (one per zone type); the per-type flags +0xb4 set and +0xc0 cleared; the phase becomes current with
// its matrix as the anchor; its choreography reset; the members' slots and the respawn queue cleared; the phase's time
// restarted; a new phase's spawn camera started; then every active enemy of the enemy group gets a formation slot.
void CKGrpSquad::SetPhase(uint8_t phase) {
    if (m_vStates.m_ui32NbUsedElt <= phase) return;
    QueueTriggerSignals(&m_tsUnk80);
    if (m_unk94 != 0) {
        const uint8_t current = m_unk55;
        if (m_vStates.m_ui32NbUsedElt > current && m_vStates.m_pBlock[current].m_pUnk3c != nullptr) RemoveCameraOwner(this);
        SetHeroInputBlocked(0);  // 0x2ca268
        m_unk94 = 0;
    }
    const uint32_t types = static_cast<uint8_t>(GetFightZone()->m_vUnk4c.m_ui32NbUsedElt);  // the zone's byte +0x57
    if ((m_bitArray & 1u) == 0) {
        m_unka4 = 0;
        if (m_vUnka8.m_pBlock == nullptr) {
            m_vUnka8.m_ui32NbElt = 1;
            m_vUnka8.m_pBlock = static_cast<uint32_t*>(Mem_AllocAligned16(4));
        }
        for (uint32_t i = 0; i < m_vUnka8.m_ui32NbUsedElt; ++i) m_vUnka8.m_pBlock[i] = 0;
        for (uint32_t have = m_vUnka8.m_ui32NbUsedElt; types > have; ++have) {
            const uint32_t used = m_vUnka8.m_ui32NbUsedElt;
            if (m_vUnka8.m_ui32NbElt == used) {
                uint32_t capacity = used + 1;
                uint32_t bytes = capacity * 4;
                if (capacity == 0) {
                    capacity = 1;
                    bytes = 4;
                }
                m_vUnka8.m_pBlock = static_cast<uint32_t*>(Mem_ReallocAligned16(m_vUnka8.m_pBlock, bytes & ~3u));
                m_vUnka8.m_ui32NbElt = capacity;
            }
            m_vUnka8.m_pBlock[used] = 0;
            m_vUnka8.m_ui32NbUsedElt = used + 1;
        }
    }
    for (TVector<uint8_t, 1>* vector : {&m_vUnkb4, &m_vUnkc0}) {
        if (vector->m_ui32NbElt < types) {
            uint32_t capacity = types + 1;
            if (capacity == 0) capacity = 1;
            vector->m_pBlock = static_cast<uint8_t*>(Mem_ReallocAligned16(vector->m_pBlock, capacity & 0x1ffu));
            vector->m_ui32NbElt = capacity;
        }
        vector->m_ui32NbUsedElt = types;
    }
    for (uint32_t i = 0; i < types; ++i) {
        m_vUnkb4.m_pBlock[i] = 1;
        m_vUnkc0.m_pBlock[i] = 0;
    }
    m_unk55 = phase;
    CopyMatrix(m_pCurrentMatrix, m_vStates.m_pBlock[phase].m_pMatrix);
    static_cast<CKChoreography*>(m_vStates.m_pBlock[m_unk55].m_pUnk34)->Reset();  // 0x2647d8
    for (IKHook* member = FirstMember(this); member != nullptr; member = member->m_pNextHook) FormationOf(member)->m_slot = -1;
    for (SRespawnNode* node = m_unk50; node != nullptr;) {
        SRespawnNode* next = node->m_pNext;
        GiveRespawnNode(node);
        node = next;
    }
    m_unk50 = nullptr;
    m_unk98 = 0.0f;
    SState& state = m_vStates.m_pBlock[m_unk55];
    state.m_unk54 = state.m_unk40[4];
    m_unkcc = 0;
    if (m_unk54 != m_unk55 && m_vStates.m_pBlock[m_unk55].m_pUnk3c != nullptr) {
        AddCameraOwner(this);
        SState& current = m_vStates.m_pBlock[m_unk55];
        StartSpawnCameraSwitch(static_cast<IKCamera*>(current.m_pUnk3c), current.m_unk40[1]);
        m_unk94 = 1;
        m_unk90 = 0.0f;
        SetHeroInputBlocked(1);  // 0x2ca268
        m_unkcc = 1;
    }
    IKGrpEnemy* enemies = SquadEnemyGroup();
    const uint32_t active = enemies->m_ui32NbActiveEnemies;
    for (uint32_t i = 0; i != active; ++i) AssignFormationSlot(SquadEnemyGroup()->m_apActiveEnemies[i]);
}

// 0x0025aca8 CKGrpSquad_SetStoredPhase_maybe
void CKGrpSquad::SetStoredPhase(uint8_t phase) {
    if (m_vStates.m_ui32NbUsedElt > phase) m_unk54 = phase;
}

namespace {
// The respawn delays of a member-list entry for the zone's current wave (+0x60): +0x04 (the first spawn) or +0x10.
float RespawnDelay(const TVector<uint32_t, 1>& delays, uint32_t wave) {
    float value;
    std::memcpy(&value, &delays.m_pBlock[wave], 4);
    return value;
}
}  // namespace

// 0x002623d8 CKGrpSquad_ScheduleRespawns_maybe: per zone type, the phase's member list entry (+0x1c of the state into
// +0x44) says how the type refills (kind 1: whole formation while at most +0x01 members, 2: one at a time, 3: +0x1c at a
// time, while the key wants more) and after which delay (the first spawn's +0x04, later ones' +0x10, by the zone's wave):
// at once (a delay of 0 or less, or 3600 and more but exactly 3600 and -1 mean never) or queued (one node per type).
void CKGrpSquad::ScheduleRespawns() {
    const int8_t list = static_cast<int8_t>(m_vStates.m_pBlock[m_unk55].m_unk1c);
    if (list == -1) return;
    for (uint32_t t = 0; GetFightZone()->m_vUnk4c.m_ui32NbUsedElt > t; ++t) {
        const uint8_t type = static_cast<uint8_t>(t);
        const SMemberEntry& entry = m_vUnk44.m_pBlock[list].m_pBlock[t];
        const uint8_t kind = entry.m_unk00;
        if (kind != 1 && kind != 2 && kind != 3) continue;
        const SFlags& flags = m_vUnk2c.m_pBlock[t];
        if (kind == 1) {
            if (TypeTotal(flags) > static_cast<int32_t>(entry.m_unk01)) continue;
        } else {
            const int8_t wanted = CountKeySlots(CurrentKey(), type, false);
            const int8_t have = TypeTotal(flags);
            if (have > wanted || static_cast<uint8_t>(wanted) == static_cast<uint8_t>(have)) continue;
        }
        const uint32_t wave = GetFightZone()->m_unk60;
        const bool first = m_vUnkb4.m_pBlock[t] != 0;
        const float delay = first ? RespawnDelay(entry.m_vUnk04, wave) : RespawnDelay(entry.m_vUnk10, wave);
        if (!(delay > 0.0f) || delay >= 3600.0f) {  // TOC 0x3a4
            if (delay == 3600.0f || delay == -1.0f) continue;  // TOC 0x3a4 / 0x3ac: never
            // at once
            if (kind == 1) {
                QueueSpawnsToFillFormation(t);
            } else {
                const int8_t wanted = CountKeySlots(CurrentKey(), type, false);
                SFlags& counts = m_vUnk2c.m_pBlock[t];
                if (TypeTotal(counts) < wanted) {
                    counts.m_unk01 = static_cast<uint8_t>(counts.m_unk01 + (kind == 2 ? 1u : entry.m_unk1c));
                }
            }
            m_vUnkb4.m_pBlock[t] = 0;
            continue;
        }
        // queued, unless the type already has a node
        bool queued = false;
        for (SRespawnNode* node = m_unk50; node != nullptr; node = node->m_pNext) {
            if (node->m_type == t) queued = true;
        }
        if (queued) continue;
        const CKGrpFightZone::SEntry4c& zoneKind = GetFightZone()->m_vUnk4c.m_pBlock[t];
        const bool typeFull = zoneKind.m_unk06 != -1 && static_cast<int16_t>(zoneKind.m_unk08) >= zoneKind.m_unk06;
        const bool zoneFull = GetFightZone()->m_unk84 != -1 && GetFightZone()->m_unk84 <= GetFightZone()->m_unk88;
        const CKChoreoKey* key = (typeFull || zoneFull) ? nullptr : CurrentKey();
        const int8_t free = key == nullptr ? 0 : CountKeySlots(key, type, true);
        if (typeFull || zoneFull || key == nullptr || free == 0) {
            if (kind == 3) m_vUnkb4.m_pBlock[t] = 0;  // only kind 3 clears the flag when it cannot queue
            continue;
        }
        SRespawnNode* node = TakeRespawnNode();
        node->m_fTimer = delay;
        node->m_pNext = nullptr;
        node->m_type = type;
        node->m_kind = kind;
        node->m_count = kind == 3 ? entry.m_unk1c : 0;  // kinds 1 and 2 store the squad's address (unread)
        node->m_pNext = m_unk50;
        m_unk50 = node;
        m_vUnkb4.m_pBlock[t] = 0;
    }
}

// vt+0x94 0x0025d7b0 CKGrpSquad_vf94 (woken): a fresh fight (the zone's +0x10f set or +0x110 clear) restarts in the stored
// phase with no pending spawns; otherwise every type is flagged (+0xb4, +0xc0).
void CKGrpSquad::Vf94() {
    if (GetFightZone()->m_unk10f != 0 || GetFightZone()->m_unk110 == 0) {
        SetPhase(m_unk54);
        ClearSpawnCountsAndRespawnQueue();
        return;
    }
    for (uint32_t i = 0; i < m_vUnkb4.m_ui32NbUsedElt; ++i) {
        m_vUnkb4.m_pBlock[i] = 1;
        m_vUnkc0.m_pBlock[i] = 1;
    }
}

// vt+0x98 0x0025ddf0 CKGrpSquad_StopFight_maybe (put to sleep): the members released; with the zone's +0x10f, back to
// the stored phase with no pending spawns.
void CKGrpSquad::Vf98() {
    ReleaseAllMembers();
    if (GetFightZone()->m_unk10f == 0) return;
    SetPhase(m_unk54);
    ClearSpawnCountsAndRespawnQueue();
}

// vt+0xa8 0x0025d718 CKGrpSquad_vfA8 / vt+0xac 0x0025d8a8 CKGrpSquad_vfAC: the members locked / unlocked.
void CKGrpSquad::OnLock() {
    CKCoreManager* core = g_pEngine->m_coreManager;
    for (IKHook* member = FirstMember(this); member != nullptr; member = member->m_pNextHook) SetObjectLocked(core, member, 1);
}
void CKGrpSquad::OnUnlock() {
    CKCoreManager* core = g_pEngine->m_coreManager;
    for (IKHook* member = FirstMember(this); member != nullptr; member = member->m_pNextHook) SetObjectLocked(core, member, 0);
}

// 0x0025de60 CKGrpSquad_MessageProc: 0xd00 phase, 0xd02 queue a type's spawns, 0xd03 the full formation, 0xd04 sleep,
// 0xd07 release the members, 0xd0f the stored phase, 0xd10 the choreography's key (0 when handled, 1 otherwise).
// The phase / key bytes are the original's lbz 3(r5): the parameter word's low byte (TriggerParamByte3).
int32_t CKGrpSquad::MessageProc(uint16_t message, void* data) {
    uint32_t word = 0;
    switch (static_cast<uint16_t>(message - 0xd00)) {
        case 0x0:
            SetPhase(TriggerParamByte3(data));
            return 0;
        case 0x2:
            if ((m_bitArray & 1u) != 0) return 0;
            std::memcpy(&word, data, 4);
            QueueSpawnsToFillFormation(word);
            return 0;
        case 0x3:
            if ((m_bitArray & 1u) != 0) return 0;
            SpawnFullFormation();
            return 0;
        case 0x4:
            SetObjectActive(g_pEngine->m_coreManager, this, 0);
            return 0;
        case 0x7:
            if ((m_bitArray & 1u) != 0) return 0;
            ReleaseAllMembers();
            return 0;
        case 0xf:
            SetStoredPhase(TriggerParamByte3(data));
            return 0;
        case 0x10:
            // The current phase's choreography (+0x34) switched to the key of the byte (0x25df14; no flag test).
            static_cast<CKChoreography*>(m_vStates.m_pBlock[m_unk55].m_pUnk34)->SwitchToKey(TriggerParamByte3(data));  // 0x264a20
            return 0;
        default:
            return 1;
    }
}

// 0x0025e008 CKGrpSquad_PostLoad: IKLife's, the squad put to sleep, the stored phase 0, the per-type flag vectors sized
// to the zone's types (their contents left as allocated), and every phase's per-type kill counts padded with -1.
int32_t CKGrpSquad::PostLoad(int32_t type) {
    PostLoadLife(type);  // 0x19f68
    SetObjectActive(g_pEngine->m_coreManager, this, 0);  // 0x1d1c0
    m_unk54 = 0;
    for (TVector<uint8_t, 1>* vector : {&m_vUnkb4, &m_vUnkc0}) {
        if (vector->m_pBlock == nullptr) {
            vector->m_ui32NbElt = 1;
            vector->m_pBlock = static_cast<uint8_t*>(Mem_AllocAligned16(1));
        }
    }
    for (TVector<uint8_t, 1>* vector : {&m_vUnkb4, &m_vUnkc0}) {
        const uint32_t types = static_cast<uint8_t>(GetFightZone()->m_vUnk4c.m_ui32NbUsedElt);  // the zone's byte +0x57
        if (vector->m_ui32NbElt < types) {
            uint32_t capacity = types + 1;
            if (capacity == 0) capacity = 1;
            vector->m_pBlock = static_cast<uint8_t*>(Mem_ReallocAligned16(vector->m_pBlock, capacity & 0x1ffu));
            vector->m_ui32NbElt = capacity;
        }
        vector->m_ui32NbUsedElt = types;
    }
    for (uint32_t i = 0; i < m_vStates.m_ui32NbUsedElt; ++i) {
        const uint32_t types = static_cast<uint8_t>(GetFightZone()->m_vUnk4c.m_ui32NbUsedElt);
        TVector<uint32_t, 1>& counts = m_vStates.m_pBlock[i].m_vUnk5c;
        while (types > counts.m_ui32NbUsedElt) {
            if (counts.m_ui32NbElt == counts.m_ui32NbUsedElt) {
                uint32_t capacity = counts.m_ui32NbElt + 1;
                if (capacity == 0) capacity = 1;
                counts.m_pBlock = static_cast<uint32_t*>(Mem_ReallocAligned16(counts.m_pBlock, (capacity * 4u) & ~3u));
                counts.m_ui32NbElt = capacity;
            }
            counts.m_pBlock[counts.m_ui32NbUsedElt++] = 0xffffffffu;
        }
    }
    return 1;
}

// 0x002600f0 CKGrpSquad_CountChoreoSlotsOfType_maybe
uint32_t CKGrpSquad::CountChoreoSlotsOfType(uint8_t type) {
    const CKChoreoKey* key = CurrentKey();
    if (key == nullptr) return 0;
    uint32_t count = 0;
    for (uint32_t i = key->m_asPos.m_ui32NbUsedElt; i != 0; --i) {
        if (key->m_asPos.m_pBlock[i - 1].m_ui8Type == type) ++count;
    }
    return count;
}

// 0x00261818 CKGrpSquad_GetMissingSpawnCountForType_maybe: the key's count compared as a signed byte, the difference
// taken from the full count.
uint8_t CKGrpSquad::GetMissingSpawnCountForType(uint32_t type) {
    const uint32_t slots = CountChoreoSlotsOfType(static_cast<uint8_t>(type));
    const int8_t members = GetTypeCountTotal(type);
    if (members > static_cast<int8_t>(slots)) return 0;
    return static_cast<uint8_t>(slots - static_cast<uint32_t>(static_cast<int32_t>(members)));
}

namespace {
// The trigger value accessors of GetInfo (their descriptors at 0x00b85700..0x00b857e0).
// 0x0025fb58 CKGrpSquad_IsInPhaseProperty_maybe: `phase` is the current one (and a phase index).
uint32_t SquadIsInPhase(IKSerializable* self, uint32_t phase) {
    const CKGrpSquad* squad = static_cast<CKGrpSquad*>(self);
    if (phase >= squad->m_vStates.m_ui32NbUsedElt) return 0;
    return phase == squad->m_unk55 ? 1u : 0u;
}
// 0x0025fc88 CKGrpSquad_GetTypeCountProperty_maybe
uint32_t SquadTypeCount(IKSerializable* self, uint32_t type) {
    const CKGrpSquad* squad = static_cast<CKGrpSquad*>(self);
    if (type >= squad->m_vUnk2c.m_ui32NbUsedElt) return 0;
    return static_cast<uint32_t>(static_cast<int32_t>(squad->GetTypeCountTotal(type)));
}
// 0x0025fd18 CKGrpSquad_GetTotalCountProperty_maybe
uint32_t SquadTotalCount(IKSerializable* self, uint32_t) {
    const CKGrpSquad* squad = static_cast<CKGrpSquad*>(self);
    int32_t total = 0;
    for (uint32_t i = 0; i < squad->m_vUnk2c.m_ui32NbUsedElt; ++i) total += squad->GetTypeCountTotal(i);
    return static_cast<uint32_t>(total);
}
// 0x0025fcd0 CKGrpSquad_GetChoreoTypeSlotCountProperty_maybe
uint32_t SquadChoreoTypeSlotCount(IKSerializable* self, uint32_t type) {
    CKGrpSquad* squad = static_cast<CKGrpSquad*>(self);
    if (type >= squad->m_vUnk2c.m_ui32NbUsedElt) return 0;
    return squad->CountChoreoSlotsOfType(static_cast<uint8_t>(type));
}
// 0x0025fb90 CKGrpSquad_GetMinHeroDistance_maybe: the nearest controlled hero's horizontal distance to the squad's
// current matrix; FLT_MAX (0x00c4acb8 +0x28) with heroes but none nearer, 0 (TOC 0x330) without heroes.
uint32_t SquadMinHeroDistance(IKSerializable* self, uint32_t) {
    const CKGrpSquad* squad = static_cast<CKGrpSquad*>(self);
    IKSerializable** heroes = static_cast<IKGrpHero*>(g_pEngine->m_gameManager->m_unk04[1])->m_apControlledHeroes;  // 0x2ca0e0
    float best = 0x1.fffffep+127f;
    if (*heroes == nullptr) return FloatBits(0.0f);
    for (; *heroes != nullptr; ++heroes) {
        const CVector3& at = squad->m_pCurrentMatrix->m_pos;
        const CVector3* hero = HeroTargetingPosition(*heroes);  // 0x363c78
        const float dz = at.z - hero->z;
        const float dx = at.x - hero->x;
        const float distance = MathSqrtfSquad(ppc::fmadds(dx, dx, dz * dz));
        if (distance < best) best = distance;
    }
    return FloatBits(best);
}
// 0x0025ff58 CKGrpSquad_GetDistanceToFightZonePoint_maybe: the horizontal distance from the squad's current matrix to the
// zone's point `index` (+0x9c), 0 for an index out of range.
uint32_t SquadDistanceToZonePoint(IKSerializable* self, uint32_t index) {
    CKGrpSquad* squad = static_cast<CKGrpSquad*>(self);
    if (index >= squad->GetFightZone()->m_vUnk9c.m_ui32NbUsedElt) return FloatBits(0.0f);
    const CVector3& at = squad->m_pCurrentMatrix->m_pos;
    const CVector3& point = squad->GetFightZone()->m_vUnk9c.m_pBlock[index];
    const float dz = at.z - point.z;
    const float dx = at.x - point.x;
    return FloatBits(MathSqrtfSquad(ppc::fmadds(dx, dx, dz * dz)));
}
// 0x0025fb38 CKGrpSquad_GetCurrentPhaseObjByte8Property_maybe: the current phase's choreography's key index.
uint32_t SquadCurrentKeyIndex(IKSerializable* self, uint32_t) {
    const CKGrpSquad* squad = static_cast<CKGrpSquad*>(self);
    return static_cast<CKChoreography*>(squad->m_vStates.m_pBlock[squad->m_unk55].m_pUnk34)->m_ui8CurrentKey;
}
}  // namespace

// 0x0025fda0 CKGrpSquad_GetInfo
int32_t CKGrpSquad::GetInfo(IKInfo* info, int32_t request) {
    if (request != kGetInfoValueAccessor) return 1;
    switch (info->m_ui32Id) {
        case 0x0: return AnswerInfo(info, SquadIsInPhase, 0);
        case 0x1: return AnswerInfo(info, SquadTypeCount, 1);
        case 0x2: return AnswerInfo(info, SquadTotalCount, 1);
        case 0x3: return AnswerInfo(info, SquadChoreoTypeSlotCount, 1);
        case 0x4: return AnswerInfo(info, SquadMinHeroDistance, 2);
        case 0xd: return AnswerInfo(info, SquadDistanceToZonePoint, 2);
        case 0x10: return AnswerInfo(info, SquadCurrentKeyIndex, 1);
        default: return 1;
    }
}

// 0x0025e430 CKGrpSquad_Destroy
void CKGrpSquad::Destroy() {
    m_lChilds = nullptr;
    *GetMemberListHead() = nullptr;  // vt+0xb0
    for (uint32_t i = 0; i < m_vStates.m_ui32NbUsedElt; ++i) {
        RwMatrixDestroy_Thunk(m_vStates.m_pBlock[i].m_pMatrix);  // 0x0023f968
    }
    RwMatrixDestroy_Thunk(m_pCurrentMatrix);
}

// 0x0025e2b0 CKGrpSquad_RecursiveRegistration
void CKGrpSquad::RecursiveRegistration(int32_t type) {
    IKBaseGroup::RecursiveRegistration(type);  // 0x00012a68 IKGroup_LevelReset
    if (type == 0) {
        for (uint32_t i = 0; i < m_vStates.m_ui32NbUsedElt; ++i) m_vStates.m_pBlock[i].m_pUnk34->RecursiveRegistration(0);  // vt+0x24
        g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
    }
    // KStub_Return1_2361b0 on m_tsUnk68 .. m_tsUnk88: the trigger starters register nothing.
}
