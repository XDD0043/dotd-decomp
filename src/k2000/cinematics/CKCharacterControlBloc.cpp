// CKCharacterControlBloc.cpp - reconstructed original translation unit 0x175918-0x1766f0 (GAME_TOC1, main_toc1), 15 functions, 15 live.
// Primary class: CKCharacterControlBloc  key 0x348  category CinematicNode  size 0x40  vtable 0xb1b138
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x175918  CKCharacterControlBloc_Delete
//   [ ] 0x175968  CKCharacterControlBloc_Abort
//   [ ] 0x1759c0  RegisterCKCharacterControlBlocClass
//   [ ] 0x175a38  _GLOBAL__I_175a38
//   [ ] 0x175a48  CKCharacterControlBloc_Stop
//   [ ] 0x175c28  CKCharacterControlBloc_Update
//   [ ] 0x175d00  CKCharacterControlBloc_Save
//   [ ] 0x175d28  CKCharacterControlBloc_RecursiveRegistration
//   [x] 0x175e40  CKCharacterControlBloc_DeleteArray
//   [x] 0x175ee0  CKCharacterControlBloc_CreateArray
//   [ ] 0x175f90  CKCharacterControlBloc_Destroy
//   [x] 0x175f98  CKCharacterControlBloc_Create
//   [ ] 0x175ff0  CKCharacterControlBloc_Start
//   [x] 0x1763b0  CKCharacterControlBloc_Load
//   [ ] 0x176500  CKCharacterControlBloc_Complete
//
//   [ ] 0x9a9470  CKCharacterControlBloc_IsKindOfClass  [inline]
//   [ ] 0x9a94a8  CKCharacterControlBloc_GetClassType  [inline]
//   [ ] 0x9a94b0  CKCharacterControlBloc_GetClassID  [inline]
//   [ ] 0x9a94b8  CKCharacterControlBloc_PreActivate  [inline]
//   [ ] 0x9a94c0  CKCharacterControlBloc_Destructor  [inline]
//   [ ] 0x9a94e0  CKCharacterControlBloc_DeletingDestructor  [inline]
#include "k2000/cinematics/CKCharacterControlBloc.h"

#include "k2000/io/IKFile.h"

// 0x001763b0 CKCharacterControlBloc_Load
int32_t CKCharacterControlBloc::Load(IKFile* file, int32_t type) {
    BasicLoadCinematicElement(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_unk38);
        IKFile_ReadRef(file, &m_unk3c);
    }
    return 1;
}
