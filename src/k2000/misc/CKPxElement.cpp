// CKPxElement.cpp - reconstructed original translation unit 0x218040-0x2182d0 (GAME_TOC1, main_toc1), 9 functions, 8 live.
// Primary owner: CKPxElement (not a registered class)
// Other owners: CKPxObject (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x218040  CKPxElement_468c_maybe_ConstructBase
//   [ ] 0x218050  CKPxElement_468c_maybe_ConstructBase_2  [dead]
//   [ ] 0x218060  CKPxElement_468c_maybe_vf28
//   [ ] 0x218068  CKPxElement_468c_maybe_vf24
//   [ ] 0x218070  CKPxObject_ClearReferences_BaseNop_maybe
//   [x] 0x218078  CKPxElement_468c_maybe_Load
//   [ ] 0x218260  CKPxElement_468c_maybe_DeletingDestructor
//   [ ] 0x2182a0  CKPxElement_468c_maybe_vf0
//   [ ] 0x2182b8  CKPxElement_468c_maybe_BaseDestructor
//
//   [ ] 0x9b2b30  CKPxElement_468c_maybe_vf14  [inline]
//   [ ] 0x9b2b38  CKPxElement_468c_maybe_vf18  [inline]
//   [ ] 0x9b2b40  CKPxElement_468c_maybe_vf8  [inline]
#include "k2000/misc/KBase468C.h"

#include "k2000/io/IKFile.h"

// 0x00218078 CKPxElement_468c_maybe_Load
int32_t KBase468C::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_unk04);
    IKFile_ReadRef(file, &m_unk08);
    IKFile_ReadRef(file, &m_unk0c);
    IKFile_ReadRef(file, &m_unk10);
    ReadU32LE(file, &m_unk14);
    return 1;
}
