// CKPxAxleShaft.cpp - reconstructed original translation unit 0x22f6c8-0x22fc48 (GAME_TOC1, main_toc1), 15 functions, 15 live.
// Primary class: CKPxAxleShaft  key 0x490c  category Logic  size 0x2c  vtable 0xb20638
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x22f6c8  CKPxAxleShaft_Delete
//   [ ] 0x22f718  RegisterCKPxAxleShaftClass
//   [ ] 0x22f790  _GLOBAL__I_22f790
//   [ ] 0x22f7a0  CKPxAxleShaft_Save
//   [x] 0x22f7c8  CKPxAxleShaft_RecursiveRegistration  (the base's vf24: returns 1, registers nothing)
//   [x] 0x22f7f0  CKPxAxleShaft_Destroy  (the base's: empty)
//   [x] 0x22f818  CKPxAxleShaft_Construct  (header)
//   [x] 0x22f850  CKPxAxleShaft_Construct_2  (the constructor's second C++ variant)
//   [x] 0x22f888  CKPxAxleShaft_DeleteArray
//   [x] 0x22f928  CKPxAxleShaft_DeletingDestructor  (the destructor; delete)
//   [x] 0x22f970  CKPxAxleShaft_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x22f9a0  CKPxAxleShaft_DestructBody  (C++ destructor chain: vtable stores only)
//   [x] 0x22f9d0  CKPxAxleShaft_Load
//   [x] 0x22fb40  CKPxAxleShaft_CreateArray
//   [x] 0x22fbf0  CKPxAxleShaft_Create
//
//   [ ] 0x9b7200  CKPxAxleShaft_IsKindOfClass  [inline]
//   [ ] 0x9b7228  CKPxAxleShaft_GetClassType  [inline]
//   [ ] 0x9b7230  CKPxAxleShaft_GetClassID  [inline]
#include "k2000/logic/CKPxAxleShaft.h"

#include "k2000/io/IKFile.h"

// 0x0022f9d0 CKPxAxleShaft_Load
int32_t CKPxAxleShaft::Load(IKFile* file, int32_t type) {
    KBase468C::Load(file, type);  // 0x00218078
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_unk18);
    ReadU32LEWords(file, m_unk1c, 3);
    ReadU32LE(file, &m_unk28);
    return 1;
}
