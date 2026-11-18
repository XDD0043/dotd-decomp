// Reconstructed original translation unit: 0x43480-0x43948 (GAME_TOC1, main_toc1), 15 functions, 12 live.
// Primary class: CKBsptree  key 0x770c  category Logic  size 0x24  vtable 0xb14c50
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x43480  CKBsptree_Delete  (registry factory: DOTD_DECLARE_FACTORIES)
//   [ ] 0x434d0  CKBsptree_Construct  [dead]
//   [ ] 0x434e0  CKBsptree_Construct_2  [dead]
//   [ ] 0x434f0  RegisterCKBsptreeClass
//   [ ] 0x43568  _GLOBAL__I_43568
//   [x] 0x43578  CKBsptree_DeleteArray  (registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x43620  CKBsptree_CreateArray  (registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x436b8  CKBsptree_Create  (registry factory: DOTD_DECLARE_FACTORIES)
//   [ ] 0x436f0  CKBsptree_Save
//   [x] 0x436f8  CKBsptree_RecursiveRegistration  (returns 1: the root's empty slot)
//   [x] 0x43700  CKBsptree_Destroy  (empty)
//   [x] 0x43708  CKBsptree_Load
//   [x] 0x438d8  CKBsptree_DeletingDestructor  (C++ deleting destructor)
//   [x] 0x43918  CKBsptree_Destructor  (C++ destructor chain: vtable stores only)
//   [ ] 0x43930  CKBsptree_Destructor_2  [dead]
//
//   [ ] 0x9957c0  CKBsptree_GetClassType  [inline]
//   [ ] 0x9957c8  CKBsptree_GetClassID  [inline]
//   [ ] 0x9957d0  CKBsptree_IsKindOfClass  [inline]
#include "k2000/logic/CKBsptree.h"

#include "k2000/io/IKFile.h"

// 0x00043708 CKBsptree_Load
int32_t CKBsptree::Load(IKFile* file, int32_t type) {
    if (type != 0) return 1;
    IKFile_ReadRef(file, &m_unk04);
    ReadU32LE(file, &m_unk08);
    ReadU32LE(file, &m_unk0c);
    ReadU32LE(file, &m_unk1c);
    ReadU32LE(file, &m_unk20);
    return 1;
}
