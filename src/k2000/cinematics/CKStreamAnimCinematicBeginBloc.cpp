// CKStreamAnimCinematicBeginBloc.cpp - reconstructed original translation unit 0x18ad68-0x18ba50 (GAME_TOC1, main_toc1), 16 functions, 16 live.
// Primary class: CKStreamAnimCinematicBeginBloc  key 0x388  category CinematicNode  size 0x3c  vtable 0xb1bad0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x18ad68  CKStreamAnimCinematicBeginBloc_Delete
//   [ ] 0x18adb8  CKStreamAnimCinematicBeginBloc_Abort
//   [ ] 0x18ae10  RegisterCKStreamAnimCinematicBeginBlocClass
//   [ ] 0x18ae88  _GLOBAL__I_18ae88
//   [ ] 0x18ae98  CKStreamAnimCinematicBeginBloc_Stop
//   [x] 0x18b078  CKStreamAnimCinematicBeginBloc_Load
//   [ ] 0x18b138  CKStreamAnimCinematicBeginBloc_Save
//   [ ] 0x18b160  CKStreamAnimCinematicBeginBloc_RecursiveRegistration
//   [x] 0x18b260  CKStreamAnimCinematicBeginBloc_Construct
//   [ ] 0x18b2a0  CKStreamAnimCinematicBeginBloc_Construct_2
//   [x] 0x18b2e0  CKStreamAnimCinematicBeginBloc_DeleteArray
//   [ ] 0x18b388  CKStreamAnimCinematicBeginBloc_Update
//   [ ] 0x18b4a0  CKStreamAnimCinematicBeginBloc_Start
//   [x] 0x18b750  CKStreamAnimCinematicBeginBloc_CreateArray
//   [x] 0x18b818  CKStreamAnimCinematicBeginBloc_Create
//   [ ] 0x18b878  CKStreamAnimCinematicBeginBloc_Complete
//
//   [ ] 0x9aa240  CKStreamAnimCinematicBeginBloc_IsKindOfClass  [inline]
//   [ ] 0x9aa278  CKStreamAnimCinematicBeginBloc_GetClassType  [inline]
//   [ ] 0x9aa280  CKStreamAnimCinematicBeginBloc_GetClassID  [inline]
//   [ ] 0x9aa288  CKStreamAnimCinematicBeginBloc_DeletingDestructor  [inline]
//   [ ] 0x9aa2d0  CKStreamAnimCinematicBeginBloc_Destructor  [inline]
#include "k2000/cinematics/CKStreamAnimCinematicBeginBloc.h"

#include "k2000/io/IKFile.h"

// 0x0018b818 CKStreamAnimCinematicBeginBloc_Create
CKStreamAnimCinematicBeginBloc::CKStreamAnimCinematicBeginBloc() { m_pStreamCpnt = nullptr; }

// 0x0018b078 CKStreamAnimCinematicBeginBloc_Load
int32_t CKStreamAnimCinematicBeginBloc::Load(IKFile* file, int32_t type) {
    BasicLoadCinematicElement(file, type);
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pStreamCpnt);
    return 1;
}
