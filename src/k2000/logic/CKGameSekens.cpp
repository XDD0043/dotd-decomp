// CKGameSekens.cpp - reconstructed original translation unit 0x3c4f0-0x3cb70 (GAME_TOC1, main_toc1), 19 functions, 18 live.
// Primary class: CKGameSekens  key 0x504c  category Logic  size 0x20  vtable 0xb14890
// Other owners: CKGameSpawnPoint (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3c4f0  CKGameSekens_Delete  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x3c540  CKGameSekens_IsCurrentLevel
//   [ ] 0x3c5a8  RegisterCKGameSekensClass
//   [ ] 0x3c620  _GLOBAL__I_3c620
//   [x] 0x3c630  CKGameSekens_vf68
//   [x] 0x3c698  CKGameSekens_ClearGameData_maybe
//   [x] 0x3c6c0  CKGameSekens_vf60
//   [x] 0x3c6f8  CKGameSekens_InitLevelData_maybe
//   [x] 0x3c720  CKGameSekens_vf58
//   [x] 0x3c778  CKGameSekens_PostLoad
//   [ ] 0x3c7a0  CKGameSekens_Save
//   [x] 0x3c7c8  CKGameSekens_RecursiveRegistration  (inherited: IKGameObject_vf24)
//   [x] 0x3c7f0  CKGameSekens_Destroy  (inherited: IKGameObject_Destroy)
//   [x] 0x3c818  CKGameSekens_DeleteArray  (the registry factories: DOTD_DECLARE_FACTORIES)
//   [x] 0x3c8b8  CKGameSekens_Create  (the registry factories: DOTD_DECLARE_FACTORIES)
//   [x] 0x3c910  CKGameSekens_CreateArray  (the registry factories: DOTD_DECLARE_FACTORIES)
//   [x] 0x3c9c0  CKGameSekens_Load
//   [x] 0x3caf0  CKGameSpawnPoint_Delete  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [ ] 0x3cb40  FUN_0003cb40  [dead]
//
//   [ ] 0x994eb8  CKGameSekens_IsKindOfClass  [inline]
//   [ ] 0x994ee0  CKGameSekens_GetClassType  [inline]
//   [ ] 0x994ee8  CKGameSekens_GetClassID  [inline]
//   [ ] 0x994ef0  CKGameSekens_Destructor  [inline]
//   [ ] 0x994f10  CKGameSekens_DeletingDestructor  [inline]
#include "k2000/logic/CKGameSekens.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSekens.h"

// 0x0003c9c0 CKGameSekens_Load
int32_t CKGameSekens::Load(IKFile* file, int32_t type) {
    IKGameObject::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_unk1c);
    } else if (type == kGameStructureBlock) {
        IKFile_ReadRef(file, &m_unk18);
    }
    return 1;
}

// 0x0003c540 CKGameSekens_IsCurrentLevel (neg + rldicl of the byte: 1 when non-zero)
uint8_t CKGameSekens::GetMatchesThisLevel() {
    if (m_unk18 == nullptr) return 0;
    return static_cast<IKGameObject*>(m_unk18)->GetMatchesThisLevel() != 0 ? 1 : 0;  // vt+0x54
}

// 0x0003c720 CKGameSekens_vf58
void CKGameSekens::InitializeGameData() {
    IKGameObject::InitializeGameData();
    m_unk1c = nullptr;
    m_baFlags &= 0xfffffffdu;
}

// 0x0003c630 CKGameSekens_vf68
void CKGameSekens::ApplyGameStateToLevel() {
    IKGameObject::ApplyGameStateToLevel();  // 0x42d98 (empty)
    if (m_unk1c == nullptr) return;
    CKSekens* sekens = static_cast<CKSekens*>(m_unk1c);
    sekens->m_flags = (sekens->m_flags & 0xfffffeffu) | (((m_baFlags >> 1) & 1u) << 8);
}
