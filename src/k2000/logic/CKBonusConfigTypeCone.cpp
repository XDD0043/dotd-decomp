// CKBonusConfigTypeCone.cpp - reconstructed original translation unit 0x128258-0x128e18 (GAME_TOC1, main_toc1), 16 functions, 16 live.
// Primary class: CKBonusConfigTypeCone  key 0x2d0c  category Logic  size 0x18  vtable 0xb19ea8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x128258  CKBonusConfigTypeCone_Delete
//   [ ] 0x1282a8  RegisterCKBonusConfigTypeConeClass
//   [ ] 0x128320  _GLOBAL__I_128320
//   [ ] 0x128330  CKBonusConfigTypeCone_Save
//   [ ] 0x128358  CKBonusConfigTypeCone_RecursiveRegistration
//   [ ] 0x128380  CKBonusConfigTypeCone_Destroy
//   [ ] 0x1283a8  CKBonusConfigTypeCone_DeletingDestructor
//   [ ] 0x1283f0  CKBonusConfigTypeCone_Destructor
//   [ ] 0x128420  CKBonusConfigTypeCone_DestructBody
//   [x] 0x128450  CKBonusConfigTypeCone_Construct
//   [ ] 0x128488  CKBonusConfigTypeCone_Construct_2
//   [x] 0x1284c0  CKBonusConfigTypeCone_DeleteArray
//   [x] 0x128568  CKBonusConfigTypeCone_CreateArray
//   [x] 0x128620  CKBonusConfigTypeCone_Create
//   [x] 0x128678  CKBonusConfigTypeCone_Load
//   [ ] 0x1287e8  CKBonusConfigTypeCone_GenerateSpawns_maybe
//
//   [ ] 0x9a70e8  CKBonusConfigTypeCone_IsKindOfClass  [inline]
//   [x] 0x9a7110  CKBonusConfigTypeCone_GetClassType  [inline]
//   [x] 0x9a7118  CKBonusConfigTypeCone_GetClassID  [inline]
//   [x] 0x9a7120  CKBonusConfigTypeCone_GetLayoutType_maybe  [inline]
#include "k2000/logic/CKBonusConfigTypeCone.h"

#include "k2000/io/IKFile.h"

// 0x00128678 CKBonusConfigTypeCone_Load: the same for every type.
int32_t CKBonusConfigTypeCone::Load(IKFile* file, int32_t type) {
    CKBonusConfigType::Load(file, type);
    ReadF32LE(file, &m_unk08);
    ReadF32LE(file, &m_unk0c);
    ReadF32LE(file, &m_unk10);
    ReadF32LE(file, &m_unk14);
    return 1;
}
