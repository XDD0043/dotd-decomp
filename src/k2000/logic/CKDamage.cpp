// CKDamage.cpp - reconstructed original translation unit 0x253a00-0x253e70 (GAME_TOC1, main_toc1), 19 functions, 16 live.
// Primary class: CKDamage  key 0x96cc  category Logic  size 0x10  vtable 0xb21160
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x253a00  CKDamage_Delete
//   [ ] 0x253a50  CKDamage_Construct_2  [dead]
//   [ ] 0x253a60  CKDamage_CopyConstruct  [dead]
//   [ ] 0x253a88  CKDamage_Assign
//   [ ] 0x253ab8  RegisterCKDamageClass
//   [ ] 0x253b30  _GLOBAL__I_253b30
//   [ ] 0x253b40  CKDamage_Destructor
//   [x] 0x253b58  CKDamage_DeleteArray
//   [x] 0x253bf8  CKDamage_Construct
//   [ ] 0x253c08  CKDamage_CopyConstruct_2  [dead]
//   [x] 0x253c30  CKDamage_CreateArray
//   [x] 0x253cc0  CKDamage_Create
//   [x] 0x253cf8  CKDamage_Load
//   [ ] 0x253df8  CKDamage_Save
//   [ ] 0x253e00  CKDamage_RecursiveRegistration
//   [ ] 0x253e08  CKDamage_PostLoad
//   [ ] 0x253e10  CKDamage_Destroy
//   [ ] 0x253e18  CKDamage_BaseDestructor
//   [ ] 0x253e30  CKDamage_DeletingDestructor
//
//   [ ] 0x9ba6d0  CKDamage_GetClassType  [inline]
//   [ ] 0x9ba6d8  CKDamage_GetClassID  [inline]
//   [ ] 0x9ba6e0  CKDamage_IsKindOfClass  [inline]
#include "k2000/logic/CKDamage.h"

#include "k2000/io/IKFile.h"

// 0x00253cf8 CKDamage_Load: a float, a word and a byte, whatever the type.
int32_t CKDamage::Load(IKFile* file, int32_t /*type*/) {
    ReadF32LE(file, &m_unk04);
    ReadS32LE(file, &m_unk08);
    ReadU8(file, &m_unk0c);
    return 1;
}
