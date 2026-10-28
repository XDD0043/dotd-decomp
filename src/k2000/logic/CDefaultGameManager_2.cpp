// CDefaultGameManager_2.cpp - reconstructed original translation unit 0x1a5c0-0x1aca0 (GAME_TOC1, main_toc1), 19 functions, 19 live.
// Primary class: CDefaultGameManager  key 0xc4c  category Logic  size 0x298  vtable 0xb13550
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x1a5c0  CDefaultGameManager_Delete
//   [ ] 0x1a610  CDefaultGameManager_vfB0
//   [ ] 0x1a618  CDefaultGameManager_vf194
//   [ ] 0x1a620  RegisterCDefaultGameManagerClass
//   [ ] 0x1a698  _GLOBAL__I_1a698
//   [x] 0x1a6a8  CDefaultGameManager_ResetProgress_maybe
//   [x] 0x1a6d0  CDefaultGameManager_vfB4
//   [ ] 0x1a6f8  CDefaultGameManager_vfAC
//   [x] 0x1a738  CDefaultGameManager_Update
//   [ ] 0x1a760  CDefaultGameManager_Resume
//   [ ] 0x1a788  CDefaultGameManager_Stop
//   [ ] 0x1a7b0  CDefaultGameManager_Pause
//   [x] 0x1a7d8  CDefaultGameManager_Start
//   [ ] 0x1a818  CDefaultGameManager_Destroy
//   [ ] 0x1a840  CDefaultGameManager_vfA8
//   [ ] 0x1a868  CDefaultGameManager_Init
//   [ ] 0x1a890  CDefaultGameManager_DeleteArray
//   [ ] 0x1a930  CDefaultGameManager_Create
//   [ ] 0x1aaa8  CDefaultGameManager_CreateArray

#include "k2000/logic/CDefaultGameManager.h"

#include "k2000/managers/CKInput.h"
#include "k2000/misc/Engine.h"

// 0x0001a738 CDefaultGameManager_Update
void CDefaultGameManager::Update(IKTime* frameClock) { IKGameManager_UpdateLevel(this, frameClock); }

// 0x0001a6a8 CDefaultGameManager_ResetProgress_maybe (XXL2 NewGame)
void CDefaultGameManager::NewGame() { BasicNewGame(); }

// 0x0001a6d0 CDefaultGameManager_vfB4 (XXL2 ExitGame)
void CDefaultGameManager::ExitGame() { RequestGameExit(); }

// 0x00013e08 IKGameManager_Stop: KStub_Nop_40cc8 on the game structure (an empty virtual-less stub), the render
// gate closed.
void CDefaultGameManager::Stop() {
    m_unk294 = 0;
}

// 0x0001a7d8 CDefaultGameManager_Start
void CDefaultGameManager::Start() {
    ResetRuntimeImpl();
    g_pEngine->m_input->SelectMappingSet(0);
}
