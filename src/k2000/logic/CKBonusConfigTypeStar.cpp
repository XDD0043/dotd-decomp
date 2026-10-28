// CKBonusConfigTypeStar.cpp - reconstructed original translation unit 0x1275b0-0x128258 (GAME_TOC1, main_toc1), 16 functions, 16 live.
// Primary class: CKBonusConfigTypeStar  key 0x2f8c  category Logic  size 0x1c  vtable 0xb19e48
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1275b0  CKBonusConfigTypeStar_Delete
//   [ ] 0x127600  RegisterCKBonusConfigTypeStarClass
//   [ ] 0x127678  _GLOBAL__I_127678
//   [ ] 0x127688  CKBonusConfigTypeStar_Save
//   [ ] 0x1276b0  CKBonusConfigTypeStar_RecursiveRegistration
//   [ ] 0x1276d8  CKBonusConfigTypeStar_Destroy
//   [ ] 0x127700  CKBonusConfigTypeStar_DeletingDestructor
//   [ ] 0x127748  CKBonusConfigTypeStar_Destructor
//   [ ] 0x127778  CKBonusConfigTypeStar_DestructBody
//   [x] 0x1277a8  CKBonusConfigTypeStar_Construct
//   [ ] 0x1277e0  CKBonusConfigTypeStar_Construct_2
//   [x] 0x127818  CKBonusConfigTypeStar_DeleteArray
//   [x] 0x1278c0  CKBonusConfigTypeStar_Create
//   [x] 0x127918  CKBonusConfigTypeStar_CreateArray
//   [x] 0x1279d0  CKBonusConfigTypeStar_Load
//   [ ] 0x127b78  CKBonusConfigTypeStar_GenerateSpawns_maybe
//
//   [ ] 0x9a70a8  CKBonusConfigTypeStar_IsKindOfClass  [inline]
//   [x] 0x9a70d0  CKBonusConfigTypeStar_GetClassType  [inline]
//   [x] 0x9a70d8  CKBonusConfigTypeStar_GetClassID  [inline]
//   [x] 0x9a70e0  CKBonusConfigTypeStar_GetLayoutType_maybe  [inline]
#include "k2000/logic/CKBonusConfigTypeStar.h"

#include "k2000/io/IKFile.h"

// 0x001279d0 CKBonusConfigTypeStar_Load: the same for every type.
int32_t CKBonusConfigTypeStar::Load(IKFile* file, int32_t type) {
    CKBonusConfigType::Load(file, type);
    ReadF32LE(file, &m_unk08);
    ReadF32LE(file, &m_unk0c);
    ReadF32LE(file, &m_unk10);
    ReadU8(file, &m_unk14);
    ReadF32LE(file, &m_unk18);
    return 1;
}
