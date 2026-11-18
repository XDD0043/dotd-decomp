// CKGameVideo.cpp - reconstructed original translation unit 0x426b8-0x42da0 (GAME_TOC1, main_toc1), 21 functions, 20 live.
// Primary class: CKGameVideo  key 0x1bcc  category Logic  size 0x24  vtable 0xb14ae0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x426b8  CKGameVideo_Delete
//   [x] 0x42708  CKGameVideo_IsCurrentLevel
//   [ ] 0x42770  RegisterCKGameVideoClass
//   [ ] 0x427e8  _GLOBAL__I_427e8
//   [x] 0x427f8  CKGameVideo_vf68  (IKGameObject's vt+0x68 0x42d98, inherited)
//   [x] 0x42820  CKGameVideo_ClearGameData_maybe  (IKGameObject's DestroyGameData, inherited)
//   [x] 0x42848  CKGameVideo_vf60  (IKGameObject's DestroyLevelData 0x42d90, inherited)
//   [x] 0x42870  CKGameVideo_InitLevelData_maybe  (IKGameObject's InitializeLevelData 0x42d88, inherited)
//   [x] 0x42898  CKGameVideo_vf58
//   [x] 0x428f8  CKGameVideo_PostLoad  (IKGameObject's PostLoad 0x42e40, inherited)
//   [ ] 0x42920  CKGameVideo_Save
//   [x] 0x42948  CKGameVideo_RecursiveRegistration  (IKGameObject's 0x42e38 (returns 1), inherited)
//   [x] 0x42970  CKGameVideo_Destroy  (IKGameObject's Destroy, inherited)
//   [x] 0x42998  CKGameVideo_DeleteArray
//   [x] 0x42a40  CKGameVideo_Create
//   [x] 0x42a98  CKGameVideo_CreateArray
//   [x] 0x42b50  CKGameVideo_Load
//   [ ] 0x42cd0  FUN_00042cd0  [dead]
//   [x] 0x42d88  KStub_Nop_42d88  (IKGameObject::InitializeLevelData, inline in IKGameObject.h)
//   [x] 0x42d90  KStub_Nop_42d90  (IKGameObject::DestroyLevelData, inline in IKGameObject.h)
//   [x] 0x42d98  KStub_Nop_42d98  (IKGameObject::ApplyGameStateToLevel, inline in IKGameObject.h)
//
//   [ ] 0x9955f8  CKGameVideo_IsKindOfClass  [inline]
//   [ ] 0x995620  CKGameVideo_GetClassType  [inline]
//   [ ] 0x995628  CKGameVideo_GetClassID  [inline]
//   [ ] 0x995630  CKGameVideo_Destructor  [inline]
//   [ ] 0x995650  CKGameVideo_DeletingDestructor  [inline]
#include "k2000/logic/system/CKGameVideo.h"

#include "k2000/io/IKFile.h"

// 0x00042708 CKGameVideo_IsCurrentLevel
uint8_t CKGameVideo::GetMatchesThisLevel() {
    if (m_unk18 == nullptr) return 0;
    return static_cast<IKGameObject*>(m_unk18)->GetMatchesThisLevel() != 0 ? 1 : 0;  // vt+0x54
}

// 0x00042898 CKGameVideo_vf58
void CKGameVideo::InitializeGameData() {
    IKGameObject::InitializeGameData();  // 0x00042db0
    m_unk1c = nullptr;
    m_unk20 = 0xffffffffu;
    m_baFlags &= 0xfffffffdu;
}

// 0x00042b50 CKGameVideo_Load
int32_t CKGameVideo::Load(IKFile* file, int32_t type) {
    IKGameObject::Load(file, type);
    if (type != kGameStructureBlock) return 1;
    IKFile_ReadRef(file, &m_unk1c);
    IKFile_ReadRef(file, &m_unk18);
    ReadU32LE(file, &m_unk20);
    return 1;
}
