// CKS08GameModule.cpp - reconstructed original translation unit 0x507d58-0x508720 (GAME_TOC1, main_toc1), 23 functions, 22 live.
// Primary class: CKS08GameModule  key 0x78cc  category Logic  size 0x34  vtable 0xb2b3c8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x507d58  CKS08GameModule_Delete
//   [x] 0x507da8  CKS08GameModule_vf74
//   [ ] 0x507db8  CKS08GameModule_QueryGameManagerVfC4_maybe  [dead]
//   [x] 0x507e08  CKS08GameModule_vf98
//   [x] 0x507e30  CKS08GameModule_Load
//   [ ] 0x507ef0  CKS08GameModule_Save
//   [x] 0x507f18  CKS08GameModule_Construct_2  (the constructor's second C++ variant)
//   [x] 0x507f80  CKS08GameModule_DeleteArray
//   [ ] 0x508020  RegisterCKS08GameModuleClass
//   [ ] 0x5080a8  _GLOBAL__D_5080a8
//   [ ] 0x5080b8  _GLOBAL__I_5080b8
//   [x] 0x5080c8  CKS08GameModule_SetActivated_maybe
//   [x] 0x508170  CKS08GameModule_Construct
//   [x] 0x5081d8  CKS08GameModule_CreateArray
//   [x] 0x5082d8  CKS08GameModule_Create
//   [x] 0x508358  CKS08GameModule_vf90
//   [x] 0x5083d8  CKS08GameModule_vf88
//   [x] 0x508430  CKS08GameModule_vf78
//   [x] 0x5084b0  CKS08GameModule_vf8C
//   [x] 0x508530  CKS08GameModule_vf7C
//   [x] 0x5085b0  CKS08GameModule_Destructor  (C++ destructor chain: the vtable, then ~CKGameModule (CKGameModule.cpp))
//   [x] 0x508628  CKS08GameModule_Destructor_2  (= 0x5085b0)
//   [x] 0x5086a0  CKS08GameModule_DeletingDestructor  (the destructor; delete)
//
//   [ ] 0x9c70b8  CKS08GameModule_IsKindOfClass  [inline]
//   [x] 0x9c70f0  CKS08GameModule_GetClassType  [inline]
//   [x] 0x9c70f8  CKS08GameModule_GetClassID  [inline]
#include "Spyro2008/logic/CKS08GameModule.h"

#include "Spyro2008/logic/CKS08GameStructure.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/misc/Engine.h"

// 0x00507e30 CKS08GameModule_Load
int32_t CKS08GameModule::Load(IKFile* file, int32_t type) {
    CKGameModule::Load(file, type);
    if (type != kGameStructureBlock) return 1;
    ReadU8(file, &m_unk30);
    return 1;
}

// 0x005080c8 CKS08GameModule_SetActivated_maybe
void CKS08GameModule::SetActivated(uint8_t activated) {
    CKGameModule::SetActivated(activated);  // 0x3bb08
    if (activated == 0) return;
    // Every module that counts for the progress done: the centre message 3, once.
    CKS08GameStructure* structure = static_cast<CKS08GameStructure*>(g_pEngine->m_gameManager->m_gameStructure);
    if (structure->CountTrackedModules() == 0) return;  // 0x40f58
    const uint32_t active = structure->CountTrackedActiveModules();  // 0x40dd0
    if (active != structure->CountTrackedModules()) return;
    structure->ShowCenterMessageOnce(3, 1);  // 0x50f590
}

// 0x00508358 CKS08GameModule_vf90
uint8_t CKS08GameModule::CanSetFlag2() {
    if (m_unk30 != 0) return 1;
    // The game manager's vt+0xc4 (CKS08GameManager_vfC4 0x9c7028: bit 5 of its +0xafc).
    return g_pEngine->m_gameManager->VfC4() == 0 ? 1 : 0;
}

// 0x00507da8 CKS08GameModule_vf74: the activated bit (bit 1 of the flags).
uint32_t CKS08GameModule::IsActivated() { return (m_baFlags >> 1) & 1u; }

// 0x00508430 CKS08GameModule_vf78: 1 when +0x30 is set, else whether the game manager's vt+0xc4 is 0.
uint8_t CKS08GameModule::CanSaveActivated() {
    if (m_unk30 != 0) return 1;
    return g_pEngine->m_gameManager->VfC4() == 0 ? 1 : 0;
}

// 0x00508530 CKS08GameModule_vf7C: 1 when +0x30 is clear, else whether the game manager's vt+0xc4 is 0.
uint8_t CKS08GameModule::CanRestoreActivated() {
    if (m_unk30 == 0) return 1;
    return g_pEngine->m_gameManager->VfC4() == 0 ? 1 : 0;
}

// 0x005083d8 CKS08GameModule_vf88: whether the game manager's vt+0xc4 is 0.
uint8_t CKS08GameModule::CanRestoreFlag2() { return g_pEngine->m_gameManager->VfC4() == 0 ? 1 : 0; }

// 0x005084b0 CKS08GameModule_vf8C: 1 when +0x30 is set, else whether the game manager's vt+0xc4 is 0.
uint8_t CKS08GameModule::CanSaveFlag2() {
    if (m_unk30 != 0) return 1;
    return g_pEngine->m_gameManager->VfC4() == 0 ? 1 : 0;
}

// 0x00507e08 CKS08GameModule_vf98: CKGameModule's (0x3ba58).
void CKS08GameModule::ApplyDone() { CKGameModule::ApplyDone(); }
