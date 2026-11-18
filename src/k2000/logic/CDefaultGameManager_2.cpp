// CDefaultGameManager_2.cpp - reconstructed original translation unit 0x1a5c0-0x1aca0 (GAME_TOC1, main_toc1), 19 functions, 19 live.
// Primary class: CDefaultGameManager  key 0xc4c  category Logic  size 0x298  vtable 0xb13550
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1a5c0  CDefaultGameManager_Delete  (DOTD_DECLARE_FACTORIES(CDefaultGameManager))
//   [x] 0x1a610  CDefaultGameManager_vfB0
//   [x] 0x1a618  CDefaultGameManager_vf194
//   [ ] 0x1a620  RegisterCDefaultGameManagerClass
//   [ ] 0x1a698  _GLOBAL__I_1a698
//   [x] 0x1a6a8  CDefaultGameManager_ResetProgress_maybe
//   [x] 0x1a6d0  CDefaultGameManager_vfB4
//   [x] 0x1a6f8  CDefaultGameManager_vfAC  (CDefaultGameManager::VfAC, CDefaultGameManager.cpp)
//   [x] 0x1a738  CDefaultGameManager_Update
//   [x] 0x1a760  CDefaultGameManager_Resume  (the header's empty Resume (CGameManager_BaseResume_maybe 0x134e8))
//   [x] 0x1a788  CDefaultGameManager_Stop  (CDefaultGameManager::Stop (IKGameManager_Stop 0x13e08))
//   [x] 0x1a7b0  CDefaultGameManager_Pause  (the header's empty Pause (CGameManager_BasePause_maybe 0x134e0))
//   [x] 0x1a7d8  CDefaultGameManager_Start
//   [x] 0x1a818  CDefaultGameManager_Destroy
//   [x] 0x1a840  CDefaultGameManager_vfA8
//   [x] 0x1a868  CDefaultGameManager_Init
//   [x] 0x1a890  CDefaultGameManager_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x1a930  CDefaultGameManager_Create  (DOTD_DECLARE_FACTORIES: the constructor, BootStubs.cpp)
//   [x] 0x1aaa8  CDefaultGameManager_CreateArray  (DOTD_DECLARE_FACTORIES)

#include "k2000/logic/CDefaultGameManager.h"

#include "k2000/managers/CKInput.h"
#include "k2000/misc/Engine.h"

// 0x0001a738 CDefaultGameManager_Update
void CDefaultGameManager::Update(IKTime* frameClock) { IKGameManager_UpdateLevel(this, frameClock); }

// 0x0001a6a8 CDefaultGameManager_ResetProgress_maybe (XXL2 NewGame)
void CDefaultGameManager::NewGame() { BasicNewGame(); }

// 0x0001a6d0 CDefaultGameManager_vfB4 (XXL2 ExitGame)
void CDefaultGameManager::ExitGame() { RequestGameExit(); }

// 0x0001a840 CDefaultGameManager_vfA8
void CDefaultGameManager::ReleaseManager() { ReleaseGameData(); }

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
