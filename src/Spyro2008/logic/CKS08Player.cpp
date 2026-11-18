// CKS08Player.cpp - reconstructed original translation unit 0x4f5830-0x4f5d48 (GAME_TOC1, main_toc1), 20 functions, 16 live.
// Primary class: CKS08Player  key 0x780c  category Logic  size 0x14  vtable 0xb2ae70
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4f5830  CKS08Player_Delete
//   [ ] 0x4f5880  CKS08Player_Construct  [dead]
//   [ ] 0x4f58a8  CKS08Player_Construct_2  [dead]
//   [ ] 0x4f58d0  KStub_Nop_4f58d0  [dead]
//   [x] 0x4f58d8  CKS08Player_vf60
//   [x] 0x4f58e0  CKS08Player_vf58
//   [x] 0x4f5908  CKS08Player_vf50
//   [x] 0x4f5930  CKS08Player_Load
//   [x] 0x4f5958  CKS08Player_Save
//   [x] 0x4f5980  CKS08Player_RecursiveRegistration
//   [x] 0x4f5a38  CKS08Player_DeleteArray
//   [ ] 0x4f5ae0  RegisterCKS08PlayerClass
//   [ ] 0x4f5b68  _GLOBAL__D_4f5b68
//   [ ] 0x4f5b78  _GLOBAL__I_4f5b78
//   [x] 0x4f5b88  CKS08Player_CreateArray
//   [x] 0x4f5c40  CKS08Player_Create
//   [x] 0x4f5c98  CKS08Player_vf54
//   [x] 0x4f5cc0  CKS08Player_Destructor  (~CKS08Player, CKS08Player.h)
//   [ ] 0x4f5ce0  CKS08Player_Destructor_2  [dead]
//   [x] 0x4f5d00  CKS08Player_DeletingDestructor  (~CKS08Player, CKS08Player.h)
//
//   [ ] 0x9c6bb8  CKS08Player_IsKindOfClass  [inline]
//   [x] 0x9c6be0  CKS08Player_GetClassType  [inline]
//   [x] 0x9c6be8  CKS08Player_GetClassID  [inline]
#include "Spyro2008/logic/CKS08Player.h"

// 0x004f5930 CKS08Player_Load
int32_t CKS08Player::Load(IKFile* file, int32_t type) {
    IKPlayer::Load(file, type);
    return 1;
}

// 0x004f5908 CKS08Player_vf50: CKDefaultPlayer_vf50Impl.
void CKS08Player::CopyPlayerGameData(IKPlayer* other) { CopyPlayerGameDataImpl(other); }

// 0x004f5c98 CKS08Player_vf54: CKDefaultPlayer_vf54Impl.
void CKS08Player::InitializeNewGame() { InitializeNewGameImpl(); }

// 0x004f58e0 CKS08Player_vf58: IKPlayer's (0x1a0d8).
void CKS08Player::CopyGameStructure() { IKPlayer::CopyGameStructure(); }

// 0x004f5980 CKS08Player_RecursiveRegistration (C2.8 save-menu)
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"
void CKS08Player::RecursiveRegistration(int32_t type) {
    if (type == K_OPTIONS_MEMCARD) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
    LevelResetImpl(type);
}
