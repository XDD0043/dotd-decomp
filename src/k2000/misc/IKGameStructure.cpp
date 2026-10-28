// IKGameStructure.cpp - reconstructed original translation unit 0x415f8-0x41714 (GAME_TOC1, main_toc1), 4 functions, 3 live.
// Primary owner: IKGameStructure (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x415f8  IKGameStructure_Construct
//   [ ] 0x41658  IKGameStructure_Construct_2  [dead]
//   [ ] 0x416b8  IKGameStructure_vf28
//   [ ] 0x416c0  IKGameStructure_vf24
#include "k2000/misc/IKGameStructure.h"

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
