// CKAimCamembert.cpp - reconstructed original translation unit 0x5bdfd8-0x5bed60 (GAME_TOC2, main_toc2), 21 functions, 18 live.
// Primary class: CKAimCamembert  key 0x9b4c  category Logic  size ?  vtable 0xb2f918
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5bdfd8  CKAimCamembert_Delete
//   [ ] 0x5be028  CKAimCamembert_Construct  [dead]
//   [ ] 0x5be038  CKAimCamembert_vf54
//   [ ] 0x5be118  CKAimCamembert_vf58
//   [ ] 0x5be178  RegisterCKAimCamembertClass
//   [ ] 0x5be1f0  _GLOBAL__I_5be1f0
//   [x] 0x5be200  CKAimCamembert_DeleteArray
//   [ ] 0x5be2a0  CKAimCamembert_vf60
//   [ ] 0x5be2f0  CKAimCamembert_SetOriginAndDirection_maybe
//   [ ] 0x5be3d0  CKAimCamembert_Construct_2  [dead]
//   [ ] 0x5be3e0  CKAimCamembert_ScoreTarget_maybe
//   [x] 0x5be760  CKAimCamembert_CreateArray
//   [x] 0x5be7f0  CKAimCamembert_Create
//   [ ] 0x5be828  CKAimCamembert_RecursiveRegistration
//   [ ] 0x5be830  CKAimCamembert_PostLoad
//   [ ] 0x5be878  CKAimCamembert_Destroy
//   [ ] 0x5be880  CKAimCamembert_Destructor
//   [ ] 0x5be8a0  CKAimCamembert_Destructor_2  [dead]
//   [x] 0x5be8c0  CKAimCamembert_Load
//   [ ] 0x5beb18  CKAimCamembert_Save
//   [ ] 0x5bed18  CKAimCamembert_DeletingDestructor
//
//   [ ] 0x9cd148  CKAimCamembert_GetClassType  [inline]
//   [ ] 0x9cd150  CKAimCamembert_GetClassID  [inline]
//   [ ] 0x9cd158  CKAimCamembert_IsKindOfClass  [inline]
//   [ ] 0x9cd190  KBase9B0C_DeletingDestructor  [inline]
//   [ ] 0x9cd1d0  KBase9B0C_vf0  [inline]
#include "k2000/logic/cameras/CKAimCamembert.h"

#include "k2000/io/IKFile.h"

// 0x005be8c0 CKAimCamembert_Load
int32_t CKAimCamembert::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        for (float& v : m_afUnk04) ReadF32LE(file, &v);
    }
    return 1;
}
