// KBase984C.cpp - reconstructed original translation unit 0x4c7410-0x4c75f8 (GAME_TOC1, main_toc1), 11 functions, 10 live.
// Primary owner: KBase984C (not a registered class)
// Other owners: CKGolemAttackCommon (2), IKSerializable (2), CKGolemAttackBase (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4c7410  CKGolemAttackCommon_ConstructBase_maybe
//   [ ] 0x4c7420  KBaseC_vf68_3
//   [ ] 0x4c7478  KBaseC_vf6C_4
//   [ ] 0x4c74d0  CKGolemAttackCommon_ConstructBase_2_maybe  [dead]
//   [ ] 0x4c74e0  KBase984C_vf28
//   [x] 0x4c74e8  CKGolemAttackBase_maybe_Load
//   [ ] 0x4c7578  KBase984C_vf24
//   [ ] 0x4c7580  KStub_Nop_4c7580
//   [ ] 0x4c7588  KBase984C_DeletingDestructor
//   [ ] 0x4c75c8  KBase984C_vf0
//   [ ] 0x4c75e0  CKGolemAttackBase_maybe_BaseDestructor
//
//   [ ] 0x9c5988  KBase984C_vf14  [inline]
//   [ ] 0x9c5990  KBase984C_vf18  [inline]
//   [ ] 0x9c5998  KBase984C_vf78  [inline]
//   [ ] 0x9c59a0  KBase984C_vf8  [inline]
#include "k2000/logic/KBase984C.h"

#include "k2000/io/IKFile.h"

// 0x004c74e8 CKGolemAttackBase_maybe_Load: one object reference, for K_LEVEL_PLATEFORMS only.
int32_t KBase984C::Load(IKFile* file, int32_t type) {
    if (type == 0) {
        IKFile_ReadRef(file, &m_unk04);
    }
    return 1;
}
