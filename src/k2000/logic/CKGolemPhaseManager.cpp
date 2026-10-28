// CKGolemPhaseManager.cpp - reconstructed original translation unit 0x4bcf30-0x4bddd8 (GAME_TOC1, main_toc1), 25 functions, 20 live.
// Primary class: CKGolemPhaseManager  key 0x974c  category Logic  size 0x28  vtable 0xb29160
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4bcf30  CKGolemPhaseManager_Delete
//   [x] 0x4bcf80  CKGolemPhaseManager_Construct  [dead]
//   [ ] 0x4bcfb8  CKGolemPhaseManager_PostLoad
//   [ ] 0x4bcfd0  CKGolemPhaseManager_Construct_2  [dead]
//   [ ] 0x4bd008  RegisterCKGolemPhaseManagerClass
//   [ ] 0x4bd080  _GLOBAL__I_4bd080
//   [x] 0x4bd090  CKGolemPhaseManager_DeleteArray
//   [ ] 0x4bd138  CKGolemPhaseManager_UpdateCurrentPhase
//   [ ] 0x4bd1a8  CKGolemPhaseManager_SwitchToPhase_maybe
//   [ ] 0x4bd330  CKGolemPhaseManager_GetCurrentPhase_maybe
//   [ ] 0x4bd368  CKGolemPhaseManager_GetPhaseByIndex_maybe  [dead]
//   [ ] 0x4bd398  CKGolemPhaseManager_SetCurrentPhase_maybe  [dead]
//   [ ] 0x4bd470  CKGolemPhaseManager_vf60
//   [ ] 0x4bd4f8  CKGolemPhaseManager_ResetAllPhases_maybe
//   [ ] 0x4bd598  CKGolemPhaseManager_StopCurrentPhase
//   [ ] 0x4bd618  CKGolemPhaseManager_vf54
//   [ ] 0x4bd698  CKGolemPhaseManager_Save
//   [ ] 0x4bd6a0  CKGolemPhaseManager_RecursiveRegistration
//   [ ] 0x4bd6a8  CKGolemPhaseManager_Destroy
//   [x] 0x4bd6b0  CKGolemPhaseManager_CreateArray
//   [x] 0x4bd778  CKGolemPhaseManager_Create
//   [x] 0x4bd7d8  CKGolemPhaseManager_Load
//   [ ] 0x4bdbf8  CKGolemPhaseManager_DeletingDestructor
//   [ ] 0x4bdca8  CKGolemPhaseManager_Destructor
//   [ ] 0x4bdd40  CKGolemPhaseManager_Destructor_2  [dead]
//
//   [ ] 0x9c5668  CKGolemPhaseManager_GetClassType  [inline]
//   [ ] 0x9c5670  CKGolemPhaseManager_GetClassID  [inline]
//   [ ] 0x9c5678  CKGolemPhaseManager_IsKindOfClass  [inline]
#include "k2000/logic/CKGolemPhaseManager.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/GameVector.h"

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
