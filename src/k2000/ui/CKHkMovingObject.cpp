// CKHkMovingObject.cpp - reconstructed original translation unit 0x5c58e8-0x5c79e0 (GAME_TOC2, main_toc2), 37 functions, 34 live.
// Primary owner: CKHkMovingObject (not a registered class)
// Other owners: RegisterCKHkMovingObjectClass (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5c58e8  CKHkMovingObject_Destroy
//   [x] 0x5c5938  CKHkMovingObject_Construct  [dead]
//   [ ] 0x5c59a0  CKHkMovingObject_vf50
//   [ ] 0x5c59a8  CKHkMovingObject_vf68
//   [ ] 0x5c59b0  CKHkMovingObject_vf70
//   [ ] 0x5c59b8  CKHkMovingObject_vf78
//   [ ] 0x5c59c0  CKHkMovingObject_SyncTrackStateFromMover_maybe  [dead]
//   [ ] 0x5c5a10  CKHkMovingObject_IsTrackAtStart_maybe
//   [ ] 0x5c5a48  CKHkMovingObject_IsTrackAtEnd_maybe
//   [ ] 0x5c5a88  CKHkMovingObject_Construct_2  [dead]
//   [ ] 0x5c5af0  RegisterCKHkMovingObjectClass
//   [ ] 0x5c5b68  _GLOBAL__I_5c5b68
//   [ ] 0x5c5b78  CKHkMovingObject_StopMover_maybe
//   [ ] 0x5c5c38  CKHkMovingObject_StartMove_maybe
//   [ ] 0x5c5e00  CKHkMovingObject_Save
//   [ ] 0x5c5e28  CKHkMovingObject_LevelReset
//   [x] 0x5c5e50  CKHkMovingObject_DestroyArray
//   [ ] 0x5c5ef8  CKHkMovingObject_ClearReferences
//   [ ] 0x5c5fd8  CKHkMovingObject_IsVisible_maybe
//   [ ] 0x5c5ff0  CKHkMovingObject_OnDeactivate
//   [ ] 0x5c6190  CKHkMovingObject_vf40
//   [x] 0x5c6278  CKHkMovingObject_RestoreCheckpointState_maybe
//   [x] 0x5c6360  CKHkMovingObject_ResetToInitialState_maybe
//   [ ] 0x5c63c8  CKHkMovingObject_IsTrackBetweenEnds_maybe
//   [x] 0x5c6420  CKHkMovingObject_CreateArray
//   [x] 0x5c6508  CKHkMovingObject_Create
//   [ ] 0x5c6588  CKHkMovingObject_SetMoveProgress_maybe
//   [ ] 0x5c6688  CKHkMovingObject_Update
//   [ ] 0x5c6c60  CKHkMovingObject_PostLoad
//   [ ] 0x5c6df0  CKHkMovingObject_Destructor
//   [x] 0x5c6e58  CKHkMovingObject_Load
//   [ ] 0x5c7498  CKHkMovingObject_Destructor_2
//   [ ] 0x5c7500  CKHkMovingObject_DeletingDestructor
//   [ ] 0x5c7570  CKHkMovingObject_RestoreState_maybe
//   [ ] 0x5c7738  CKHkMovingObject_RestoreState_maybe
//   [ ] 0x5c7740  CKHkMovingObject_ReinitRuntime
//   [ ] 0x5c7758  CKHkMovingObject_HandleMessage
//
//   [ ] 0x9cd508  CKHkMovingObject_IsKindOf  [inline]
//   [ ] 0x9cd550  CKHkMovingObject_GetClassGroup  [inline]
//   [ ] 0x9cd558  CKHkMovingObject_GetClassId  [inline]
#include "k2000/ui/CKHkMovingObject.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Mat4.h"

// 0x005c6e58 CKHkMovingObject_Load
int32_t CKHkMovingObject::Load(IKFile* file, int32_t type) {
    IKHook::Load(file, type);  // through TocBridge_CKHook_Load
    if (type != K_LEVEL_PLATEFORMS) return 1;
    m_pMatrix = RwMatrixCreate_Thunk();
    CMatrix34_LoadMatrix(m_pMatrix, file);
    IKFile_ReadRef(file, &m_pUnk24);
    ReadU8(file, &m_unk28);
    ReadU8(file, &m_unk29);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    // The vector reserve the Load inlines: capacity = count, then the block; the grow branch after it
    // cannot run (kept as in the original).
    m_vpSteps.m_ui32NbElt = count;
    m_vpSteps.m_pBlock = static_cast<Step**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(Step*))));
    if (m_vpSteps.m_ui32NbElt < count) {
        uint32_t capacity = count + 1;
        if (capacity == 0) capacity = 1;
        m_vpSteps.m_pBlock = static_cast<Step**>(
            Mem_ReallocAligned16(m_vpSteps.m_pBlock, capacity * static_cast<uint32_t>(sizeof(Step*))));
        m_vpSteps.m_ui32NbElt = capacity;
    }
    m_vpSteps.m_ui32NbUsedElt = count;
    for (uint32_t i = 0; i < count; ++i) {
        Step* step = new Step;  // OperatorNew(0x44), no constructor
        m_vpSteps.m_pBlock[i] = step;
        IKFile_ReadRef(file, &step->m_pUnk4);
        IKFile_ReadRef(file, &step->m_pUnk0);
        ReadU8(file, &step->m_unk8);
        ReadU32LE(file, &step->m_unkC);
        ReadU8(file, &step->m_unk10);
        ReadU32LE(file, &step->m_unk14);
        IKFile_ReadRef(file, &step->m_pUnk18);
        ReadU32LE(file, &step->m_unk1C);
        ReadU32LE(file, &step->m_unk20);
        uint32_t dropped = 0;  // read and swapped into a stack word, never stored
        ReadU32LE(file, &dropped);
        step->m_tsUnk28.Load(file, 0);
        step->m_tsUnk30.Load(file, 0);
        IKFile_ReadRef(file, &step->m_pUnk38);
    }
    return 1;
}

// 0x005c6360 CKHkMovingObject_SetDefaultState (the flag is not used)
void CKHkMovingObject::SetDefaultState(int32_t /*flag*/) {
    m_unk2A = m_unk28;
    for (uint32_t i = 0; i < m_vpSteps.m_ui32NbUsedElt; ++i) {
        Step* step = m_vpSteps.m_pBlock[i];
        step->m_unk3C = step->m_unk8;
        step->m_unk40 = step->m_unkC;
    }
}

// 0x005c6278 CKHkMovingObject_RestoreCheckpointState_maybe
int32_t CKHkMovingObject::RestoreCheckpointState(uint32_t stateIdForLeft) {
    if (stateIdForLeft == 0) {
        m_unk2A = m_unk28;
        for (uint32_t i = 0; i < m_vpSteps.m_ui32NbUsedElt; ++i) {
            Step* step = m_vpSteps.m_pBlock[i];
            step->m_unk3C = step->m_unk8;
            step->m_unk40 = step->m_unkC;
        }
    } else {
        m_unk2A = m_unk29;
        for (uint32_t i = 0; i < m_vpSteps.m_ui32NbUsedElt; ++i) {
            Step* step = m_vpSteps.m_pBlock[i];
            step->m_unk3C = step->m_unk10;
            step->m_unk40 = step->m_unk14;
        }
    }
    return 1;
}
