// CKBonusConfigType.cpp - reconstructed original translation unit 0x127470-0x1275b0 (GAME_TOC1, main_toc1), 10 functions, 8 live.
// Primary owner: CKBonusConfigType (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x127470  CKBonusConfigType_2c8c_maybe_Construct_2  [dead]
//   [ ] 0x127480  CKBonusConfigType_ClassKeyForKind_maybe  [dead]
//   [x] 0x1274a8  CKBonusConfigType_2c8c_maybe_Construct
//   [x] 0x1274b8  CKBonusConfigType_2c8c_maybe_Load
//   [ ] 0x127528  CKBonusConfigType_2c8c_maybe_vf28
//   [ ] 0x127530  CKBonusConfigType_2c8c_maybe_vf24
//   [ ] 0x127538  CKBonusConfigType_2c8c_maybe_vf10
//   [ ] 0x127540  CKBonusConfigType_2c8c_maybe_vf0
//   [ ] 0x127558  CKBonusConfigType_2c8c_maybe_BaseDestructor
//   [ ] 0x127570  CKBonusConfigType_2c8c_maybe_DeletingDestructor
//
//   [ ] 0x9a7078  CKBonusConfigType_2c8c_maybe_vf14  [inline]
//   [ ] 0x9a7080  CKBonusConfigType_2c8c_maybe_vf18  [inline]
//   [x] 0x9a7088  CKBonusConfigType_2c8c_maybe_vf8  [inline]
#include "k2000/misc/CKBonusConfigType.h"

#include "k2000/io/IKFile.h"

// 0x001274b8 CKBonusConfigType_2c8c_maybe_Load: the same for every type.
int32_t CKBonusConfigType::Load(IKFile* file, int32_t /*type*/) {
    ReadU32LE(file, &m_unk04);
    return 1;
}
