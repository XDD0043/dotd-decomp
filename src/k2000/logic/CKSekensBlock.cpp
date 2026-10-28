// CKSekensBlock.cpp - reconstructed original translation unit 0x1f7018-0x1f7618 (GAME_TOC1, main_toc1), 18 functions, 18 live.
// Primary class: CKSekensBlock  key 0x65cc  category Logic  size 0x1c  vtable 0xb1ea70
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1f7018  CKSekensBlock_Delete
//   [ ] 0x1f7068  CKSekensBlock_IsInterruptible_maybe
//   [ ] 0x1f7070  CKSekensBlock_vf54
//   [ ] 0x1f7078  RegisterCKSekensBlockClass
//   [ ] 0x1f70f0  _GLOBAL__I_1f70f0
//   [ ] 0x1f7100  CKSekensBlock_PostLoad
//   [ ] 0x1f7128  CKSekensBlock_Save
//   [ ] 0x1f7150  CKSekensBlock_RecursiveRegistration
//   [ ] 0x1f7178  CKSekensBlock_Destroy
//   [ ] 0x1f71a0  CKSekensBlock_Destructor
//   [x] 0x1f71d8  CKSekensBlock_Construct
//   [ ] 0x1f7218  CKSekensBlock_Construct_2
//   [x] 0x1f7258  CKSekensBlock_DeleteArray
//   [ ] 0x1f7300  CKSekensBlock_DestructBody
//   [ ] 0x1f7338  CKSekensBlock_DeletingDestructor
//   [x] 0x1f7388  CKSekensBlock_Load
//   [x] 0x1f74f0  CKSekensBlock_CreateArray
//   [x] 0x1f75b8  CKSekensBlock_Create
//
//   [ ] 0x9b0e40  CKSekensBlock_IsKindOfClass  [inline]
//   [ ] 0x9b0e68  CKSekensBlock_GetClassType  [inline]
//   [ ] 0x9b0e70  CKSekensBlock_GetClassID  [inline]
//   [ ] 0x9b0e78  CKSekensBlock_vf58  [inline]
//   [ ] 0x9b0e80  CKSekensBlock_vf5C  [inline]
#include "k2000/logic/CKSekensBlock.h"

#include "k2000/io/IKFile.h"

// 0x001f7388 CKSekensBlock_Load
int32_t CKSekensBlock::Load(IKFile* file, int32_t type) {
    CKSekensElement::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pText);
        ReadF32LE(file, &m_unk14);
        ReadU8(file, &m_unk18);
        ReadU8(file, &m_unk19);
    }
    return 1;
}
