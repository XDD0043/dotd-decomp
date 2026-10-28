// CKComponent.cpp - reconstructed original translation unit 0x12f40-0x130f8 (GAME_TOC1, main_toc1), 16 functions, 11 live.
// Primary owner: CKComponent (not a registered class)
// Other owners: CDefaultGameManager (2), KBaseBCC (2), CKS08GameManager (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x12f40  CKComponent_DeletingDestructor
//   [ ] 0x12f80  CKComponent_Destructor
//   [ ] 0x12f98  CKComponent_BaseDestructor
//   [ ] 0x12fb0  CDefaultGameManager_DestroyGame
//   [ ] 0x12fb8  KStub_Nop_12fb8
//   [x] 0x12fc0  IKGameManager_RestoreDefaultOptionsThenVfAC_IfFlag_maybe
//   [x] 0x13048  CKS08GameManager_ClearRequestedSector_maybe
//   [ ] 0x13058  KStub_Nop_13058  [dead]
//   [ ] 0x13060  KStub_Return0_13060  [dead]
//   [ ] 0x13068  KStub_Nop_13068  [dead]
//   [ ] 0x13070  KStub_Nop_13070
//   [ ] 0x13078  KStub_Nop_13078  [dead]
//   [ ] 0x13080  CDefaultGameManager_HandlePauseInput_maybe
//   [x] 0x13088  IKGameManager_UpdateLevelIfCtx30Zero_maybe
//   [ ] 0x130e0  CKS08GameManager_SetRequestedLevelClearSector_maybe
//   [ ] 0x130f0  KStub_Return1_130f0  [dead]
#include "k2000/logic/CDefaultGameManager.h"

// 0x00012fc0 IKGameManager_RestoreDefaultOptionsThenVfAC_IfFlag_maybe
void IKGameManager_RestoreDefaultOptionsThenVfAC_IfFlag(CDefaultGameManager* manager, int32_t flag) {
    if (flag != 0) {
        manager->RestoreDefaultOptions(1);
        manager->VfAC();
    }
}

// 0x00013048 CKS08GameManager_ClearRequestedSector_maybe
void CDefaultGameManager::ClearRequestedSector() { m_requestedSector = -2; }

#include "k2000/logic/CKLevel.h"
#include "k2000/system/IKTime.h"

// 0x00013088 IKGameManager_UpdateLevelIfCtx30Zero_maybe
void IKGameManager_UpdateLevel(CDefaultGameManager* manager, IKTime* frameClock) {
    if (frameClock->m_eCurrentState == IKTime::RUNNING) manager->m_level->Update(frameClock);  // vt+0x7c
}
