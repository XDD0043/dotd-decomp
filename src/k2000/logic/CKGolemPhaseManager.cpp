// CKGolemPhaseManager.cpp - reconstructed original translation unit 0x4bcf30-0x4bddd8 (GAME_TOC1, main_toc1), 25 functions, 20 live.
// Primary class: CKGolemPhaseManager  key 0x974c  category Logic  size 0x28  vtable 0xb29160
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4bcf30  CKGolemPhaseManager_Delete
//   [x] 0x4bcf80  CKGolemPhaseManager_Construct  [dead]
//   [x] 0x4bcfb8  CKGolemPhaseManager_PostLoad  (CKGolemPhaseManager.h)
//   [ ] 0x4bcfd0  CKGolemPhaseManager_Construct_2  [dead]
//   [ ] 0x4bd008  RegisterCKGolemPhaseManagerClass
//   [ ] 0x4bd080  _GLOBAL__I_4bd080
//   [x] 0x4bd090  CKGolemPhaseManager_DeleteArray
//   [x] 0x4bd138  CKGolemPhaseManager_UpdateCurrentPhase
//   [x] 0x4bd1a8  CKGolemPhaseManager_SwitchToPhase_maybe
//   [x] 0x4bd330  CKGolemPhaseManager_GetCurrentPhase_maybe  (CKGolemPhaseManager.h)
//   [ ] 0x4bd368  CKGolemPhaseManager_GetPhaseByIndex_maybe  [dead]
//   [ ] 0x4bd398  CKGolemPhaseManager_SetCurrentPhase_maybe  [dead]
//   [x] 0x4bd470  CKGolemPhaseManager_vf60
//   [x] 0x4bd4f8  CKGolemPhaseManager_ResetAllPhases_maybe
//   [x] 0x4bd598  CKGolemPhaseManager_StopCurrentPhase
//   [x] 0x4bd618  CKGolemPhaseManager_vf54
//   [ ] 0x4bd698  CKGolemPhaseManager_Save
//   [x] 0x4bd6a0  CKGolemPhaseManager_RecursiveRegistration  (returns 1: the inherited default)
//   [x] 0x4bd6a8  CKGolemPhaseManager_Destroy  (empty: the inherited default)
//   [x] 0x4bd6b0  CKGolemPhaseManager_CreateArray
//   [x] 0x4bd778  CKGolemPhaseManager_Create
//   [x] 0x4bd7d8  CKGolemPhaseManager_Load
//   [x] 0x4bdbf8  CKGolemPhaseManager_DeletingDestructor  (the same as 0x4bdca8 CKGolemPhaseManager_Destructor)
//   [x] 0x4bdca8  CKGolemPhaseManager_Destructor
//   [ ] 0x4bdd40  CKGolemPhaseManager_Destructor_2  [dead]
//
//   [ ] 0x9c5668  CKGolemPhaseManager_GetClassType  [inline]
//   [ ] 0x9c5670  CKGolemPhaseManager_GetClassID  [inline]
//   [ ] 0x9c5678  CKGolemPhaseManager_IsKindOfClass  [inline]
#include "k2000/logic/CKGolemPhaseManager.h"

#include "k2000/io/IKFile.h"
#include "k2000/hooks/CKHkGolem.h"
#include "k2000/logic/GameVector.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/CKGolemPhaseBase.h"

// 0x004bcf80 CKGolemPhaseManager_Construct
CKGolemPhaseManager::CKGolemPhaseManager() {
    m_phases.m_pBlock = nullptr;
    m_phases.m_ui32NbElt = 1;
    m_phases.m_ui32NbUsedElt = 0;
    m_unk14.m_ui32NbElt = 1;
    m_unk14.m_ui32NbUsedElt = 0;
    m_unk14.m_pBlock = nullptr;
}

// 0x004bd7d8 CKGolemPhaseManager_Load: for K_LEVEL_PLATEFORMS only, two counted reference lists, a reference
// and a word. Each list gets a fresh one-entry block first (capacity 1, the length kept) and grows by one.
// BUG(original): the old blocks are not freed and the lengths are not reset (a second Load appends).
int32_t CKGolemPhaseManager::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;

    uint32_t count = 0;
    ReadU32LE(file, &count);
    GameVector_Allocate(&m_phases, 1);
    for (uint32_t i = 0; i < count; ++i) {
        IKSerializable* phase = nullptr;
        IKFile_ReadRef(file, &phase);
        GameVector_Add(&m_phases, phase);
    }

    count = 0;
    ReadU32LE(file, &count);
    GameVector_Allocate(&m_unk14, 1);
    for (uint32_t i = 0; i < count; ++i) {
        IKSerializable* attack = nullptr;
        IKFile_ReadRef(file, &attack);
        GameVector_Add(&m_unk14, attack);
    }

    IKFile_ReadRef(file, &m_unk04);
    ReadS32LE(file, &m_unk24);
    return 1;
}

namespace {
CKGolemPhaseBase* PhaseAt(const TVector<IKSerializable*, 1>& phases, uint32_t index) {
    return static_cast<CKGolemPhaseBase*>(phases.m_pBlock[index]);
}
}  // namespace

// 0x004bd138 CKGolemPhaseManager_UpdateCurrentPhase: the current phase's vt+0x50 (none past the count).
void CKGolemPhaseManager::UpdateCurrentPhase(IKTime* clock) {
    const uint32_t index = static_cast<uint32_t>(m_unk20);
    if (index < m_phases.m_ui32NbUsedElt) PhaseAt(m_phases, index)->Update(clock);
}

// 0x004bd1a8 CKGolemPhaseManager_SwitchToPhase_maybe: inside the count, the current phase switches step (vt+0x64), or
// the current phase stops (vt+0x58), the new one takes its first step (vt+0x68), becomes current and starts (vt+0x54);
// either way the golem releases its effects (vt+0x114). BUG(original): with no current phase (-1) the stop reads the
// word before the phase block (the callers always have one: the attacks run inside a phase).
void CKGolemPhaseManager::SwitchToPhase(uint32_t phase, uint32_t step, float blend) {
    if (phase >= m_phases.m_ui32NbUsedElt) return;
    if (static_cast<int32_t>(phase) == m_unk20) {
        PhaseAt(m_phases, phase)->SwitchToStep(step, blend);
    } else {
        PhaseAt(m_phases, static_cast<uint32_t>(m_unk20))->Stop();
        PhaseAt(m_phases, phase)->StartStepNoStop(step, blend);
        m_unk20 = static_cast<int32_t>(phase);
        PhaseAt(m_phases, phase)->Start();
    }
    static_cast<CKHkGolem*>(m_unk04)->ReleaseAllEntryObjects();
}

// 0x004bd470 CKGolemPhaseManager_vf60: every phase's vt+0x60.
void CKGolemPhaseManager::Vf60() {
    for (uint32_t i = 0; i < m_phases.m_ui32NbUsedElt; ++i) PhaseAt(m_phases, i)->Vf60();
}

// 0x004bd4f8 CKGolemPhaseManager_ResetAllPhases_maybe: every phase's vt+0x5c, then no current phase.
void CKGolemPhaseManager::ResetAllPhases() {
    for (uint32_t i = 0; i < m_phases.m_ui32NbUsedElt; ++i) PhaseAt(m_phases, i)->ResetPhases();
    m_unk20 = -1;
}

// 0x004bd598 CKGolemPhaseManager_StopCurrentPhase: the current phase stops (vt+0x58); no current phase.
void CKGolemPhaseManager::StopCurrentPhase() {
    const uint32_t index = static_cast<uint32_t>(m_unk20);
    if (index < m_phases.m_ui32NbUsedElt) {
        PhaseAt(m_phases, index)->Stop();
        m_unk20 = -1;
    }
}

// 0x004bd618 CKGolemPhaseManager_vf54: without a current phase the first one (+0x24) becomes current; it starts
// (vt+0x54) when inside the count.
void CKGolemPhaseManager::StartCurrentPhase() {
    if (m_unk20 == -1) m_unk20 = m_unk24;
    const uint32_t index = static_cast<uint32_t>(m_unk20);
    if (index < m_phases.m_ui32NbUsedElt) PhaseAt(m_phases, index)->Start();
}

// 0x004bdca8 CKGolemPhaseManager_Destructor: the two reference blocks freed.
CKGolemPhaseManager::~CKGolemPhaseManager() {
    if (m_unk14.m_pBlock != nullptr) Mem_FreeAligned16(m_unk14.m_pBlock);
    m_unk14.m_ui32NbUsedElt = 0;
    m_unk14.m_pBlock = nullptr;
    if (m_phases.m_pBlock != nullptr) Mem_FreeAligned16(m_phases.m_pBlock);
    m_phases.m_ui32NbUsedElt = 0;
    m_phases.m_pBlock = nullptr;
}
