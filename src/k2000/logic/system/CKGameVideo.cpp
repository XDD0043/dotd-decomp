// CKGameVideo.cpp - reconstructed original translation unit 0x426b8-0x42da0 (GAME_TOC1, main_toc1), 21 functions, 20 live.
// Primary class: CKGameVideo  key 0x1bcc  category Logic  size 0x24  vtable 0xb14ae0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x426b8  CKGameVideo_Delete
//   [ ] 0x42708  CKGameVideo_IsCurrentLevel
//   [ ] 0x42770  RegisterCKGameVideoClass
//   [ ] 0x427e8  _GLOBAL__I_427e8
//   [ ] 0x427f8  CKGameVideo_vf68
//   [ ] 0x42820  CKGameVideo_ClearGameData_maybe
//   [ ] 0x42848  CKGameVideo_vf60
//   [ ] 0x42870  CKGameVideo_InitLevelData_maybe
//   [ ] 0x42898  CKGameVideo_vf58
//   [ ] 0x428f8  CKGameVideo_PostLoad
//   [ ] 0x42920  CKGameVideo_Save
//   [ ] 0x42948  CKGameVideo_RecursiveRegistration
//   [ ] 0x42970  CKGameVideo_Destroy
//   [x] 0x42998  CKGameVideo_DeleteArray
//   [x] 0x42a40  CKGameVideo_Create
//   [x] 0x42a98  CKGameVideo_CreateArray
//   [x] 0x42b50  CKGameVideo_Load
//   [ ] 0x42cd0  FUN_00042cd0  [dead]
//   [ ] 0x42d88  KStub_Nop_42d88
//   [ ] 0x42d90  KStub_Nop_42d90
//   [ ] 0x42d98  KStub_Nop_42d98
//
//   [ ] 0x9955f8  CKGameVideo_IsKindOfClass  [inline]
//   [ ] 0x995620  CKGameVideo_GetClassType  [inline]
//   [ ] 0x995628  CKGameVideo_GetClassID  [inline]
//   [ ] 0x995630  CKGameVideo_Destructor  [inline]
//   [ ] 0x995650  CKGameVideo_DeletingDestructor  [inline]
#include "k2000/logic/system/CKGameVideo.h"

#include "k2000/io/IKFile.h"

// 0x00042b50 CKGameVideo_Load
int32_t CKGameVideo::Load(IKFile* file, int32_t type) {
    IKGameObject::Load(file, type);
    if (type != kGameStructureBlock) return 1;
    IKFile_ReadRef(file, &m_unk1c);
    IKFile_ReadRef(file, &m_unk18);
    ReadU32LE(file, &m_unk20);
    return 1;
}
