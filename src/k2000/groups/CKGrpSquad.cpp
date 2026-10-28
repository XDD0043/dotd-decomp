// CKGrpSquad.cpp - reconstructed original translation unit 0x25a9c0-0x263df8 (GAME_TOC1, main_toc1), 86 functions, 71 live.
// Primary class: CKGrpSquad  key 0x604  category Group  size 0xd0  vtable 0xb212b0
// Other owners: GetEnemyGroup (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x25a9c0  CKGrpSquad_Delete
//   [ ] 0x25aa10  CKGrpSquad_Construct  [dead]
//   [ ] 0x25ab38  GetEnemyGroup_2
//   [ ] 0x25ab50  CKGrpSquad_GetFightZone
//   [ ] 0x25ab58  CKGrpSquad_ClearMemberFormationSlots_maybe  [dead]
//   [ ] 0x25ac00  CKGrpSquad_SetMemberField29_maybe  [dead]
//   [ ] 0x25aca8  CKGrpSquad_SetStoredPhase_maybe
//   [ ] 0x25acc0  CKGrpSquad_HasNoMembers_maybe  [dead]
//   [ ] 0x25ad30  CKGrpSquad_GetPhaseFlagB4_maybe  [dead]
//   [ ] 0x25ad60  RegisterCKGrpSquadClass
//   [ ] 0x25add8  _GLOBAL__I_25add8
//   [x] 0x25ade8  CKGrpSquad_DeleteArray
//   [ ] 0x25ae88  CKGrpSquad_Construct_2  [dead]
//   [ ] 0x25afb0  CKGrpSquad_GetPhaseFlagC0_maybe  [dead]
//   [x] 0x25afe0  CKGrpSquad_ResetMemberSlots_maybe
//   [ ] 0x25b160  CKGrpSquad_ActivateSpawnCamera_maybe
//   [x] 0x25b328  CKGrpSquad_CreateArray
//   [x] 0x25b4c0  CKGrpSquad_Create
//   [ ] 0x25b600  CKGrpSquad_UpdateChoreography_maybe
//   [ ] 0x25b810  CKGrpSquad_OrientTowardHero_maybe
//   [ ] 0x25b958  CKGrpSquad_OrientTowardPhaseTarget_maybe
//   [ ] 0x25bab0  CKGrpSquad_OrientTowardPhasePoint_maybe
//   [ ] 0x25bbf8  CKGrpSquad_OrientTowardControlledHero_maybe  [dead]
//   [ ] 0x25bd50  CKGrpSquad_AssignFormationSlot_maybe
//   [ ] 0x25c278  CKGrpSquad_SetPhase_maybe
//   [ ] 0x25ca10  CKGrpSquad_ApplyPendingChoreography_maybe
//   [ ] 0x25caa0  CKGrpSquad_AssignFormationSlotsRecursive_maybe
//   [ ] 0x25cc48  CKGrpSquad_AssignAllFormationSlots_maybe
//   [ ] 0x25ccd8  CKGrpSquad_FaceNearestHero_maybe
//   [ ] 0x25ceb8  CKGrpSquad_UpdateAnchorFromPhase_maybe
//   [ ] 0x25d638  CKGrpSquad_Save
//   [ ] 0x25d640  CKGrpSquad_vfB8
//   [ ] 0x25d648  CKGrpSquad_Stop
//   [ ] 0x25d650  CKGrpSquad_SetDefaultState
//   [ ] 0x25d660  CKGrpSquad_SetGameState
//   [ ] 0x25d698  CKGrpSquad_Restart
//   [x] 0x25d6c8  CKGrpSquad_Start
//   [ ] 0x25d718  CKGrpSquad_vfA8
//   [ ] 0x25d7b0  CKGrpSquad_vf94
//   [ ] 0x25d8a8  CKGrpSquad_vfAC
//   [ ] 0x25d940  UpdateCKGrpSquad
//   [ ] 0x25ddf0  CKGrpSquad_StopFight_maybe
//   [ ] 0x25de60  CKGrpSquad_MessageProc
//   [ ] 0x25e008  CKGrpSquad_PostLoad
//   [ ] 0x25e2b0  CKGrpSquad_RecursiveRegistration
//   [ ] 0x25e430  CKGrpSquad_Destroy
//   [x] 0x25e4f0  CKGrpSquad_Load
//   [ ] 0x25fb38  CKGrpSquad_GetCurrentPhaseObjByte8Property_maybe
//   [ ] 0x25fb58  CKGrpSquad_IsInPhaseProperty_maybe
//   [ ] 0x25fb90  CKGrpSquad_GetMinHeroDistance_maybe
//   [ ] 0x25fc88  CKGrpSquad_GetTypeCountProperty_maybe
//   [ ] 0x25fcd0  CKGrpSquad_GetChoreoTypeSlotCountProperty_maybe
//   [ ] 0x25fd18  CKGrpSquad_GetTotalCountProperty_maybe
//   [ ] 0x25fda0  CKGrpSquad_GetInfo
//   [ ] 0x25ff58  CKGrpSquad_GetDistanceToFightZonePoint_maybe
//   [ ] 0x260008  CKGrpSquad_GetTypeCountTotal_maybe
//   [ ] 0x260040  CKGrpSquad_CountFreeChoreoSlotsOfType_maybe  [dead]
//   [ ] 0x2600f0  CKGrpSquad_CountChoreoSlotsOfType_maybe
//   [ ] 0x260198  CKGrpSquad_PlaceMemberAtFormationSlot_maybe  [dead]
//   [ ] 0x260280  CKGrpSquad_TakeOverMember_maybe
//   [ ] 0x2604c0  CKGrpSquad_HasSpawnRequest_maybe
//   [ ] 0x260568  CKGrpSquad_ClearSpawnCountsAndRespawnQueue_maybe
//   [ ] 0x260668  CKGrpSquad_ReturnEnemyToFightZonePool_maybe
//   [ ] 0x260748  CKGrpSquad_ReleaseMember_maybe
//   [ ] 0x2608c8  CKGrpSquad_TakeEnemyFromFightZonePool_maybe
//   [ ] 0x260a88  CKGrpSquad_ProcessDeadMembers_maybe
//   [ ] 0x260db0  CKGrpSquad_ReleaseAllMembers_maybe
//   [ ] 0x260f38  CKGrpSquad_SpawnMember_maybe
//   [ ] 0x261180  CKGrpSquad_QueueSpawnForType_maybe  [dead]
//   [ ] 0x261280  CKGrpSquad_QueueSpawnsToFillFormation_maybe
//   [ ] 0x261478  CKGrpSquad_SpawnMemberAt_maybe
//   [ ] 0x261708  CKGrpSquad_QueueSpawnsForType_maybe  [dead]
//   [ ] 0x261818  CKGrpSquad_GetMissingSpawnCountForType_maybe
//   [ ] 0x261928  CKGrpSquad_SpawnPendingMembers_maybe
//   [ ] 0x261e00  CKGrpSquad_SpawnFullFormation_maybe
//   [ ] 0x2620e8  CKGrpSquad_SpawnFullFormation_maybe
//   [ ] 0x2620f0  CKGrpSquad_ProcessRespawnTimers_maybe
//   [ ] 0x2623d8  CKGrpSquad_ScheduleRespawns_maybe
//   [ ] 0x2634d8  CKGrpSquad_Phase_Release_2  [dead]
//   [ ] 0x263510  CKGrpSquad_Phase_Init_2  [dead]
//   [x] 0x263530  CKGrpSquad_Phase_Init
//   [ ] 0x263550  CKGrpSquad_Phase_InitAtPosition_maybe
//   [ ] 0x263688  CKGrpSquad_Phase_CopyConstruct_maybe
//   [ ] 0x2638e8  CKGrpSquad_Phase_Release
//   [ ] 0x263920  CKGrpSquad_Phase_Assign_maybe  [dead]
//   [ ] 0x263b98  CKGrpSquad_Phase_CopyConstruct_2_maybe
//
//   [x] 0x9ba998  CKGrpSquad_GetClassType  [inline]
//   [x] 0x9ba9a0  CKGrpSquad_GetClassID  [inline]
//   [ ] 0x9ba9a8  CKGrpSquad_vfCC  [inline]
//   [ ] 0x9ba9b0  CKGrpSquad_Pause  [inline]
//   [ ] 0x9ba9b8  CKGrpSquad_Resume  [inline]
//   [ ] 0x9ba9c0  CKGrpSquad_IsKindOfClass  [inline]
//   [ ] 0x9baa18  CKGrpSquad_Destructor  [inline]
//   [ ] 0x9bace0  CKGrpSquad_DeletingDestructor  [inline]
//   [ ] 0x9bafb0  CKGrpSquad_SpawnEntryCompareByByte4_maybe  [inline]
#include "k2000/groups/CKGrpSquad.h"

#include <new>

#include "Renderware/rwcore/RwMatrix.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/IKGrpEnemy.h"
#include "k2000/misc/Engine.h"

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
            if (m_vStates.m_pBlock[i].m_vUnk5c.m_pBlock != nullptr) Mem_FreeAligned16(m_vStates.m_pBlock[i].m_vUnk5c.m_pBlock);
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
        for (uint32_t& w : state.m_unk40) ReadU32LE(file, &w);
        ReadU32LE(file, &state.m_unk58);
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
        ReadU32LE(file, &state.m_unk18);
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
