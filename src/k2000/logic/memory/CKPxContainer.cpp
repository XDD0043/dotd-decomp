// CKPxContainer.cpp - reconstructed original translation unit 0x21cb38-0x21d108 (GAME_TOC1, main_toc1), 15 functions, 15 live.
// Primary class: CKPxContainer  key 0x46cc  category Logic  size 0x28  vtable 0xb1ff18
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x21cb38  CKPxContainer_Delete
//   [ ] 0x21cb88  RegisterCKPxContainerClass
//   [ ] 0x21cc00  _GLOBAL__I_21cc00
//   [ ] 0x21cc10  CKPxContainer_Save
//   [ ] 0x21cc38  CKPxContainer_RecursiveRegistration
//   [ ] 0x21cc60  CKPxContainer_Destroy
//   [ ] 0x21cc88  CKPxContainer_DeletingDestructor
//   [ ] 0x21ccd0  CKPxContainer_Destructor
//   [ ] 0x21cd00  CKPxContainer_DestructBody
//   [x] 0x21cd30  CKPxContainer_Construct
//   [ ] 0x21cd68  CKPxContainer_Construct_2
//   [x] 0x21cda0  CKPxContainer_DeleteArray
//   [x] 0x21ce48  CKPxContainer_Create
//   [x] 0x21cea0  CKPxContainer_CreateArray
//   [x] 0x21cf58  CKPxContainer_Load
//
//   [ ] 0x9b3f88  CKPxContainer_IsKindOfClass  [inline]
//   [ ] 0x9b3fb0  CKPxContainer_GetClassType  [inline]
//   [ ] 0x9b3fb8  CKPxContainer_GetClassID  [inline]
#include "k2000/logic/memory/CKPxContainer.h"

#include "k2000/io/IKFile.h"

// 0x0021cf58 CKPxContainer_Load
int32_t CKPxContainer::Load(IKFile* file, int32_t type) {
    KBase468C::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_unk18);
    IKFile_ReadRef(file, &m_unk1c);
    IKFile_ReadRef(file, &m_unk20);
    ReadU16LE(file, &m_unk24);
    return 1;
}
