// CKHkCrumblyZoneMultiState.cpp - reconstructed original translation unit 0x411100-0x413fe8 (GAME_TOC1, main_toc1), 38 functions, 34 live.
// Primary class: CKHkCrumblyZoneMultiState  key 0x34c2  category Hook  size 0x8c  vtable 0xb259d0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x411100  CKHkCrumblyZoneMultiState_Delete
//   [ ] 0x411150  CKHkCrumblyZoneMultiState_SetDefaultState
//   [ ] 0x411160  CKHkCrumblyZoneMultiState_SetGameState
//   [ ] 0x411190  CKHkCrumblyZoneMultiState_CallVfF0ForCurrentState_maybe  [dead]
//   [ ] 0x4111e0  CKHkCrumblyZoneMultiState_ResetStateHitPoints_maybe  [dead]
//   [ ] 0x411250  CKHkCrumblyZoneMultiState_AdvanceToNextState_maybe
//   [ ] 0x411338  CKHkCrumblyZoneMultiState_GoToPreviousState
//   [ ] 0x411410  CKHkCrumblyZoneMultiState_GetHitDamage_maybe
//   [ ] 0x4114b8  CKHkCrumblyZoneMultiState_vf104
//   [ ] 0x4114c0  CKHkCrumblyZoneMultiState_IsInStateProperty_maybe
//   [ ] 0x4114e8  RegisterCKHkCrumblyZoneMultiStateClass
//   [ ] 0x411560  _GLOBAL__I_411560
//   [ ] 0x411570  CKHkCrumblyZoneMultiState_GetTotalHealthProperty_maybe
//   [ ] 0x411598  CKHkCrumblyZoneMultiState_UpdateShakes_maybe
//   [ ] 0x4117e0  CKHkCrumblyZoneMultiState_ResetPiecesFlag2AndShake74_maybe  [dead]
//   [ ] 0x411900  CKHkCrumblyZoneMultiState_ResetPiecesFlag1AndShake6C_maybe  [dead]
//   [ ] 0x411a20  CKHkCrumblyZoneMultiState_DisableAllStates_maybe
//   [ ] 0x411ac8  CKHkCrumblyZoneMultiState_Stop
//   [ ] 0x411af0  CKHkCrumblyZoneMultiState_GetInfo
//   [ ] 0x411c20  CKHkCrumblyZoneMultiState_PostLoad
//   [ ] 0x411cc0  CKHkCrumblyZoneMultiState_Save
//   [ ] 0x411ce8  CKHkCrumblyZoneMultiState_RecursiveRegistration
//   [ ] 0x411d58  CKHkCrumblyZoneMultiState_DeleteArray
//   [x] 0x411df8  CKHkCrumblyZoneMultiState_Create
//   [ ] 0x411e78  CKHkCrumblyZoneMultiState_Update
//   [ ] 0x411f88  CKHkCrumblyZoneMultiState_Destroy
//   [ ] 0x412020  CKHkCrumblyZoneMultiState_SetVisible_maybe
//   [ ] 0x4120a0  CKHkCrumblyZoneMultiState_SetState_maybe
//   [x] 0x4122b8  CKHkCrumblyZoneMultiState_Start
//   [ ] 0x412368  CKHkCrumblyZoneMultiState_CreateArray
//   [ ] 0x412458  CKHkCrumblyZoneMultiState_MessageProc
//   [ ] 0x4128c8  CKHkCrumblyZoneMultiState_Restart
//   [ ] 0x4129c8  CKHkCrumblyZoneMultiState_OnDeactivate
//   [ ] 0x412a78  CKHkCrumblyZoneMultiState_OnActivate
//   [ ] 0x412bd8  CKHkCrumblyZoneMultiState_PlayBreakFx_maybe
//   [x] 0x412f98  CKHkCrumblyZoneMultiState_Load
//   [ ] 0x413740  CKHkCrumblyZoneMultiState_PlayCrumbleFx_maybe
//   [ ] 0x413c78  CKHkCrumblyZoneMultiState_PlayHitFxAt_maybe
//
//   [ ] 0x9c25c0  CKHkCrumblyZoneMultiState_IsKindOfClass  [inline]
//   [ ] 0x9c2618  CKHkCrumblyZoneMultiState_GetClassType  [inline]
//   [ ] 0x9c2620  CKHkCrumblyZoneMultiState_GetClassID  [inline]
//   [ ] 0x9c2628  CKHkCrumblyZoneMultiState_Destructor  [inline]
//   [ ] 0x9c26c8  CKHkCrumblyZoneMultiState_DeletingDestructor  [inline]
#include "k2000/hooks/CKHkCrumblyZoneMultiState.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/logic/CKCrumblyZoneState.h"

namespace {

// The inlined TVector<IKSerializable*, 1> load: capacity = count (1 when 0), a block for it, the grow
// branch (unreachable: the capacity was just set to the count), the length, then one reference per
// element (vt+0x24 each, not one array read).
void LoadRefVector(IKFile* file, TVector<IKSerializable*, 1>& v) {
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count == 0) {
        v.m_ui32NbElt = 1;
        v.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(sizeof(IKSerializable*)));
    } else {
        v.m_ui32NbElt = count;
        v.m_pBlock = static_cast<IKSerializable**>(
            Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(IKSerializable*))));
    }
    if (v.m_ui32NbElt < count) {
        uint32_t capacity = count + 1;
        v.m_pBlock = static_cast<IKSerializable**>(
            Mem_ReallocAligned16(v.m_pBlock, capacity * static_cast<uint32_t>(sizeof(IKSerializable*))));
        v.m_ui32NbElt = capacity;
    }
    v.m_ui32NbUsedElt = count;
    for (uint32_t i = 0; i < count; ++i) IKFile_ReadRef(file, &v.m_pBlock[i]);
}

}  // namespace

// 0x00412f98 CKHkCrumblyZoneMultiState_Load
int32_t CKHkCrumblyZoneMultiState::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_unk20);
    ReadU32LE(file, &m_unk24);
    LoadRefVector(file, m_vUnk2C);
    LoadRefVector(file, m_vUnk38);
    IKFile_ReadRef(file, &m_pUnk44);
    IKFile_ReadRef(file, &m_pUnk48);
    IKFile_ReadRef(file, &m_pUnk4C);
    IKFile_ReadRef(file, &m_pUnk68);
    IKFile_ReadRef(file, &m_pUnk6C);
    ReadU16LE(file, &m_unk78);
    m_tsUnk7C.Load(file, K_LEVEL_PLATEFORMS);
    m_tsUnk84.Load(file, K_LEVEL_PLATEFORMS);
    for (float& f : m_afUnk50) ReadF32LE(file, &f);
    for (float& f : m_afUnk5C) ReadF32LE(file, &f);
    IKFile_ReadRef(file, &m_pUnk70);
    IKFile_ReadRef(file, &m_pUnk74);
    return 1;
}

// 0x004122b8 CKHkCrumblyZoneMultiState_Start: every state before the current one (+0x28) gets its +0x08 word
// 0, the others the word of +0x0c (last state first).
void CKHkCrumblyZoneMultiState::Start() {
    CKHkActorBase::Start();
    for (uint32_t i = m_vUnk38.m_ui32NbUsedElt; i != 0; --i) {
        CKCrumblyZoneState* state = static_cast<CKCrumblyZoneState*>(m_vUnk38.m_pBlock[i - 1]);
        state->m_unk08 = (i - 1) < m_unk28 ? 0.0f : state->m_unk0c;
    }
}
