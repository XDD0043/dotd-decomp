// CKGolemPhaseBase.cpp - reconstructed original translation unit 0x4c75f8-0x4c7730 (GAME_TOC1, main_toc1), 9 functions, 8 live.
// Primary owner: CKGolemPhaseBase (not a registered class)
// Other owners: KBase978C (4)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x4c75f8  CKGolemPhaseBase_maybe_Construct_2  [dead]
//   [ ] 0x4c7608  KBase978C_vf0
//   [x] 0x4c7620  CKGolemPhaseBase_maybe_Construct
//   [x] 0x4c7630  CKGolemPhaseBase_maybe_Load
//   [ ] 0x4c76c0  KBase978C_vf28
//   [ ] 0x4c76c8  KBase978C_vf24
//   [ ] 0x4c76d0  KStub_Nop_4c76d0
//   [ ] 0x4c76d8  CKGolemPhaseBase_maybe_BaseDestructor
//   [ ] 0x4c76f0  KBase978C_DeletingDestructor
//
//   [ ] 0x9c59c8  KBase978C_vf14  [inline]
//   [ ] 0x9c59d0  KBase978C_vf18  [inline]
//   [ ] 0x9c59d8  KBase978C_vf8  [inline]
#include "k2000/misc/CKGolemPhaseBase.h"

#include "k2000/io/IKFile.h"

// 0x004c7630 CKGolemPhaseBase_maybe_Load: one object reference, for K_LEVEL_PLATEFORMS only.
int32_t CKGolemPhaseBase::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_unk04);
    }
    return 1;
}
