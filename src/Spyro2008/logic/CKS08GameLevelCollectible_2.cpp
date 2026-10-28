// CKS08GameLevelCollectible_2.cpp - reconstructed original translation unit 0x4f5d48-0x4f6648 (GAME_TOC1, main_toc1), 21 functions, 21 live.
// Primary class: CKS08GameLevelCollectible  key 0xa8cc  category Logic  size 0x24  vtable 0xb2aef8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4f5d48  CKS08GameLevelCollectible_Delete
//   [ ] 0x4f5d98  CKS08GameLevelCollectible_SetDefaultState
//   [ ] 0x4f5da8  CKS08GameLevelCollectible_vf68
//   [ ] 0x4f5db0  CKS08GameLevelCollectible_ApplyCollect_maybe
//   [ ] 0x4f5fa8  CKS08GameLevelCollectible_ClearGameData_maybe
//   [ ] 0x4f5fd0  CKS08GameLevelCollectible_ClearLevelData
//   [x] 0x4f5ff8  CKS08GameLevelCollectible_InitLevelData
//   [ ] 0x4f6020  CKS08GameLevelCollectible_PostLoad
//   [ ] 0x4f6048  CKS08GameLevelCollectible_Save
//   [ ] 0x4f6070  CKS08GameLevelCollectible_RecursiveRegistration
//   [ ] 0x4f6098  CKS08GameLevelCollectible_Destroy
//   [x] 0x4f60c0  CKS08GameLevelCollectible_DeleteArray
//   [x] 0x4f6168  CKS08GameLevelCollectible_Create
//   [ ] 0x4f61c0  RegisterCKS08GameLevelCollectibleClass
//   [ ] 0x4f6248  _GLOBAL__D_4f6248
//   [ ] 0x4f6258  _GLOBAL__I_4f6258
//   [ ] 0x4f6268  CKS08GameLevelCollectible_MessageProc
//   [x] 0x4f6398  CKS08GameLevelCollectible_InitGameData
//   [ ] 0x4f63e8  CKS08GameLevelCollectible_GetInfo
//   [x] 0x4f6440  CKS08GameLevelCollectible_CreateArray
//   [x] 0x4f64f8  CKS08GameLevelCollectible_Load
//
//   [ ] 0x9c6bf0  CKS08GameLevelCollectible_IsKindOfClass  [inline]
//   [x] 0x9c6c30  CKS08GameLevelCollectible_GetClassType  [inline]
//   [x] 0x9c6c38  CKS08GameLevelCollectible_GetClassID  [inline]
//   [ ] 0x9c6c40  CKS08GameLevelCollectible_GetTriggerProp14  [inline]
//   [ ] 0x9c6c48  CKS08GameLevelCollectible_Destructor  [inline]
//   [ ] 0x9c6c68  CKS08GameLevelCollectible_DeletingDestructor  [inline]
#include "Spyro2008/logic/CKS08GameLevelCollectible.h"

#include "k2000/io/IKFile.h"

// 0x004f6398 CKS08GameLevelCollectible_InitGameData
void CKS08GameLevelCollectible::InitializeGameData() {
    KBase1D0C::InitializeGameData();
    m_unk20 = 0;
    m_unk1d = 1;
    m_unk1c = 0;
    m_unk1e = 0;
    m_unk1f = 0;
}

// 0x004f64f8 CKS08GameLevelCollectible_Load
int32_t CKS08GameLevelCollectible::Load(IKFile* file, int32_t type) {
    KBase1D0C::Load(file, type);
    if (type != kGameStructureBlock) return 1;
    ReadU8(file, &m_unk1d);
    ReadU8(file, &m_unk1e);
    ReadU8(file, &m_unk1f);
    ReadU8(file, &m_unk20);
    return 1;
}
