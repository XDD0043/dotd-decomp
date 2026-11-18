// IKGameStructure.cpp - reconstructed original translation unit 0x415f8-0x41714 (GAME_TOC1, main_toc1), 4 functions, 3 live.
// Primary owner: IKGameStructure (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x415f8  IKGameStructure_Construct
//   [ ] 0x41658  IKGameStructure_Construct_2  [dead]
//   [x] 0x416b8  IKGameStructure_vf28
//   [x] 0x416c0  IKGameStructure_vf24
#include "k2000/misc/IKGameStructure.h"

#include "k2000/logic/CKGameLevel.h"
#include "k2000/logic/CKGameModule.h"
#include "k2000/logic/CKGameState.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"

// 0x000415f8 IKGameStructure_Construct. +0x44..+0x47 are left as they are.
IKGameStructure::IKGameStructure() {
    m_pGameManager = nullptr;
    m_pCurrentSpawnPoint = nullptr;
    m_vpStages.m_ui32NbElt = 8;
    m_vpStages.m_pBlock = nullptr;
    m_vpStages.m_ui32NbUsedElt = 0;
    m_vpStates.m_ui32NbElt = 8;
    m_vpStates.m_pBlock = nullptr;
    m_vpStates.m_ui32NbUsedElt = 0;
    m_vpUnk24.m_ui32NbElt = 8;
    m_vpUnk24.m_pBlock = nullptr;
    m_vpUnk24.m_ui32NbUsedElt = 0;
    m_pStartGameState = nullptr;
    m_ui32NbGlobalStages = 0;
    m_ui32NbLocalStages = 0;
    m_ui32NbGlobalStates = 0;
    m_ui32NbLocalStates = 0;
}

// 0x000416c0 IKGameStructure_vf24 (XXL2 RecursiveRegistration)
void IKGameStructure::RecursiveRegistration(int32_t type) {
    if (static_cast<uint32_t>(type) < 2) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
    for (uint32_t i = 0; i < m_vpStages.m_ui32NbUsedElt; ++i) m_vpStages.m_pBlock[i]->RecursiveRegistration(type);
    for (uint32_t i = 0; i < m_vpStates.m_ui32NbUsedElt; ++i) m_vpStates.m_pBlock[i]->RecursiveRegistration(type);
    if (type != 0) return;
    // The +0x24 entries are CKTriggerSynchros (CKDefaultGameStructure_PostLoad), declared as modules.
    for (uint32_t i = 0; i < m_vpUnk24.m_ui32NbUsedElt; ++i)
        reinterpret_cast<IKSerializable*>(m_vpUnk24.m_pBlock[i])->RecursiveRegistration(0);
}
