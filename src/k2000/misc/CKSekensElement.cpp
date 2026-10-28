// CKSekensElement.cpp - reconstructed original translation unit 0x1fa758-0x1fa938 (GAME_TOC1, main_toc1), 10 functions, 9 live.
// Primary owner: CKSekensElement (not a registered class)
// Other owners: CKSekensEntry (1), CKSekensMarker (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1fa758  CKSekensElement_658c_maybe_Construct
//   [ ] 0x1fa770  KStub_Nop_1fa770
//   [ ] 0x1fa778  CKSekensElement_658c_maybe_vf24
//   [ ] 0x1fa780  CKSekensElement_658c_maybe_vf28
//   [x] 0x1fa788  CKSekensEntry_Load
//   [ ] 0x1fa8a0  CKSekensMarker_PostLoad
//   [ ] 0x1fa8b0  CKSekensElement_658c_maybe_Construct_2  [dead]
//   [ ] 0x1fa8c8  CKSekensElement_658c_maybe_DeletingDestructor
//   [ ] 0x1fa908  CKSekensElement_658c_maybe_vf0
//   [ ] 0x1fa920  CKSekensElement_658c_maybe_BaseDestructor
//
//   [ ] 0x9b10c0  CKSekensElement_658c_maybe_vf14  [inline]
//   [ ] 0x9b10c8  CKSekensElement_658c_maybe_vf18  [inline]
//   [ ] 0x9b10d0  CKSekensElement_658c_maybe_vf8  [inline]
//   [ ] 0x9b10f0  KStub_Nop_9b10f0  [inline]
#include "k2000/misc/CKSekensElement.h"

#include "k2000/io/IKFile.h"

// 0x001fa758 CKSekensElement_658c_maybe_Construct
CKSekensElement::CKSekensElement() {
    m_pSekens = nullptr;
    m_unk08 = 0;
}

// 0x001fa788 CKSekensEntry_Load
int32_t CKSekensElement::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_fTime);
    IKFile_ReadRef(file, &m_pSekens);
    return 1;
}
