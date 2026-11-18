// CKTextBase.cpp - reconstructed original translation unit 0x2cc38-0x2ccb8 (GAME_TOC1, main_toc1), 4 functions, 4 live.
// Primary owner: CKTextBase (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2cc38  CKTextBase_700c_maybe_vf24  (RecursiveRegistration: returns 1, registers nothing: the default)
//   [x] 0x2cc40  CKTextBase_700c_maybe_PostLoad  (PostLoad: IKGameObject's (0x42e40, returns 1): the default)
//   [x] 0x2cc68  CKTextBase_700c_maybe_Load
//   [x] 0x2cc90  CKTextBase_700c_maybe_vf28  (Save: IKGameObject's (0x42e30, returns 1): the default)
//
//   [ ] 0x993d90  CKTextBase_700c_maybe_vf8  [inline]
//   [x] 0x993db8  CKTextBase_700c_maybe_vf14  [inline]
//   [x] 0x993dc0  CKTextBase_700c_maybe_vf18  [inline]
#include "k2000/ui/KBase700C.h"

// 0x0002cc68 CKTextBase_700c_maybe_Load
int32_t KBase700C::Load(IKFile* file, int32_t type) {
    IKGameObject::Load(file, type);
    return 1;
}
