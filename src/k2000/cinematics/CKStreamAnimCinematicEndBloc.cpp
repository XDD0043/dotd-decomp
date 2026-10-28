// CKStreamAnimCinematicEndBloc.cpp - reconstructed original translation unit 0x18c830-0x18d470 (GAME_TOC1, main_toc1), 16 functions, 16 live.
// Primary class: CKStreamAnimCinematicEndBloc  key 0x3c8  category CinematicNode  size 0x3c  vtable 0xb1bc00
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x18c830  CKStreamAnimCinematicEndBloc_Delete
//   [ ] 0x18c880  CKStreamAnimCinematicEndBloc_Abort
//   [ ] 0x18c8d8  RegisterCKStreamAnimCinematicEndBlocClass
//   [ ] 0x18c950  _GLOBAL__I_18c950
//   [ ] 0x18c960  CKStreamAnimCinematicEndBloc_Stop
//   [ ] 0x18cb40  CKStreamAnimCinematicEndBloc_Update
//   [x] 0x18cbc8  CKStreamAnimCinematicEndBloc_Load
//   [ ] 0x18cc88  CKStreamAnimCinematicEndBloc_Save
//   [ ] 0x18ccb0  CKStreamAnimCinematicEndBloc_RecursiveRegistration
//   [x] 0x18cdb0  CKStreamAnimCinematicEndBloc_Construct
//   [ ] 0x18cdf0  CKStreamAnimCinematicEndBloc_Construct_2
//   [x] 0x18ce30  CKStreamAnimCinematicEndBloc_DeleteArray
//   [ ] 0x18ced8  CKStreamAnimCinematicEndBloc_Start
//   [x] 0x18d170  CKStreamAnimCinematicEndBloc_Create
//   [x] 0x18d1d0  CKStreamAnimCinematicEndBloc_CreateArray
//   [ ] 0x18d298  CKStreamAnimCinematicEndBloc_Complete
//
//   [ ] 0x9aa3a0  CKStreamAnimCinematicEndBloc_IsKindOfClass  [inline]
//   [ ] 0x9aa3d8  CKStreamAnimCinematicEndBloc_GetClassType  [inline]
//   [ ] 0x9aa3e0  CKStreamAnimCinematicEndBloc_GetClassID  [inline]
//   [ ] 0x9aa3e8  CKStreamAnimCinematicEndBloc_Destructor  [inline]
//   [ ] 0x9aa408  CKStreamAnimCinematicEndBloc_DeletingDestructor  [inline]
#include "k2000/cinematics/CKStreamAnimCinematicEndBloc.h"

#include "k2000/io/IKFile.h"

// 0x0018d170 CKStreamAnimCinematicEndBloc_Create
CKStreamAnimCinematicEndBloc::CKStreamAnimCinematicEndBloc() { m_pStreamCpnt = nullptr; }

// 0x0018cbc8 CKStreamAnimCinematicEndBloc_Load
int32_t CKStreamAnimCinematicEndBloc::Load(IKFile* file, int32_t type) {
    BasicLoadCinematicElement(file, type);
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pStreamCpnt);
    return 1;
}
