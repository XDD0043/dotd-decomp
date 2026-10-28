// CKBlackBandBloc.cpp - reconstructed original translation unit 0x174a58-0x175918 (GAME_TOC1, main_toc1), 18 functions, 17 live.
// Primary class: CKBlackBandBloc  key 0x2c8  category CinematicNode  size 0x3c  vtable 0xb1b0a0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x174a58  CKBlackBandBloc_Delete
//   [ ] 0x174aa8  CKBlackBandBloc_Abort
//   [ ] 0x174ab8  CKBlackBandBloc_DisableBands_maybe  [dead]
//   [ ] 0x174b00  RegisterCKBlackBandBlocClass
//   [ ] 0x174b78  _GLOBAL__I_174b78
//   [ ] 0x174b88  CKBlackBandBloc_StartSceneExitTransitions_maybe
//   [ ] 0x174c70  CKBlackBandBloc_StartSceneEntryTransitions_maybe
//   [ ] 0x174d58  CKBlackBandBloc_Stop
//   [ ] 0x174f38  CKBlackBandBloc_Update
//   [x] 0x174fa0  CKBlackBandBloc_Load
//   [ ] 0x175048  CKBlackBandBloc_Save
//   [ ] 0x175070  CKBlackBandBloc_RecursiveRegistration
//   [x] 0x175100  CKBlackBandBloc_DeleteArray
//   [x] 0x1751a8  CKBlackBandBloc_Create
//   [ ] 0x175200  CKBlackBandBloc_Destroy
//   [x] 0x175208  CKBlackBandBloc_CreateArray
//   [ ] 0x1752c0  CKBlackBandBloc_Start
//   [ ] 0x175740  CKBlackBandBloc_Complete
//
//   [ ] 0x9a93b8  CKBlackBandBloc_IsKindOfClass  [inline]
//   [ ] 0x9a93f0  CKBlackBandBloc_GetClassType  [inline]
//   [ ] 0x9a93f8  CKBlackBandBloc_GetClassID  [inline]
//   [ ] 0x9a9400  CKBlackBandBloc_vf58  [inline]
//   [ ] 0x9a9408  CKBlackBandBloc_DeletingDestructor  [inline]
//   [ ] 0x9a9450  CKBlackBandBloc_Destructor  [inline]
#include "k2000/cinematics/CKBlackBandBloc.h"

#include "k2000/io/IKFile.h"

// 0x00174fa0 CKBlackBandBloc_Load
int32_t CKBlackBandBloc::Load(IKFile* file, int32_t type) {
    BasicLoadCinematicElement(file, type);
    if (type == K_LEVEL_PLATEFORMS) ReadU32LE(file, &m_unk38);
    return 1;
}
