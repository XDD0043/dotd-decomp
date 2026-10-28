// CKPlaySoundCinematicBloc.cpp - reconstructed original translation unit 0x186430-0x1871b8 (GAME_TOC1, main_toc1), 14 functions, 14 live.
// Primary class: CKPlaySoundCinematicBloc  key 0x708  category CinematicNode  size 0x44  vtable 0xb1b870
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x186430  CKPlaySoundCinematicBloc_Delete
//   [ ] 0x186480  RegisterCKPlaySoundCinematicBlocClass
//   [ ] 0x1864f8  _GLOBAL__I_1864f8
//   [ ] 0x186508  CKPlaySoundCinematicBloc_Stop
//   [ ] 0x1866e8  CKPlaySoundCinematicBloc_Update
//   [ ] 0x1867c0  CKPlaySoundCinematicBloc_RecursiveRegistration
//   [x] 0x186840  CKPlaySoundCinematicBloc_DeleteArray
//   [x] 0x1868e8  CKPlaySoundCinematicBloc_Create
//   [ ] 0x186940  CKPlaySoundCinematicBloc_Destroy
//   [x] 0x186948  CKPlaySoundCinematicBloc_CreateArray
//   [x] 0x186a00  CKPlaySoundCinematicBloc_Load
//   [ ] 0x186b40  CKPlaySoundCinematicBloc_Save
//   [ ] 0x186c68  CKPlaySoundCinematicBloc_Start
//   [ ] 0x186fd0  CKPlaySoundCinematicBloc_Complete
//
//   [ ] 0x9a9e00  CKPlaySoundCinematicBloc_IsKindOfClass  [inline]
//   [ ] 0x9a9e38  CKPlaySoundCinematicBloc_GetClassType  [inline]
//   [ ] 0x9a9e40  CKPlaySoundCinematicBloc_GetClassID  [inline]
//   [ ] 0x9a9e48  CKPlaySoundCinematicBloc_PreActivate  [inline]
//   [ ] 0x9a9e50  CKPlaySoundCinematicBloc_Abort  [inline]
//   [ ] 0x9a9e60  CKPlaySoundCinematicBloc_Destructor  [inline]
//   [ ] 0x9a9e80  CKPlaySoundCinematicBloc_DeletingDestructor  [inline]
#include "k2000/cinematics/CKPlaySoundCinematicBloc.h"

#include "k2000/io/IKFile.h"

// 0x00186a00 CKPlaySoundCinematicBloc_Load
int32_t CKPlaySoundCinematicBloc::Load(IKFile* file, int32_t type) {
    BasicLoadCinematicElement(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        ReadS32LE(file, &m_i32SoundIndex);
        ReadF32LE(file, &m_fVolume);
        ReadF32LE(file, &m_fPitch);
    }
    return 1;
}
