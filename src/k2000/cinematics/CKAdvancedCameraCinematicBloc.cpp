// CKAdvancedCameraCinematicBloc.cpp - reconstructed original translation unit 0x1702f8-0x172ba8 (GAME_TOC1, main_toc1), 19 functions, 17 live.
// Primary class: CKAdvancedCameraCinematicBloc  key 0x208  category CinematicNode  size 0xb0  vtable 0xb1af70
// Other owners: Math (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1702f8  CKAdvancedCameraCinematicBloc_Delete
//   [ ] 0x170348  CKAdvancedCameraCinematicBloc_EvaluateEase_maybe  [dead]
//   [ ] 0x1703a0  CKAdvancedCameraCinematicBloc_Abort
//   [ ] 0x170440  RegisterCKAdvancedCameraCinematicBlocClass
//   [ ] 0x1704b8  _GLOBAL__I_1704b8
//   [ ] 0x1704c8  CKAdvancedCameraCinematicBloc_Stop
//   [ ] 0x1706a8  Math_GetYawPitchToPoint_maybe
//   [ ] 0x1707b8  CKAdvancedCameraCinematicBloc_Save
//   [ ] 0x1707e0  CKAdvancedCameraCinematicBloc_RecursiveRegistration
//   [x] 0x170ab8  CKAdvancedCameraCinematicBloc_DeleteArray
//   [x] 0x170b58  CKAdvancedCameraCinematicBloc_Create
//   [ ] 0x170bb0  CKAdvancedCameraCinematicBloc_Destroy
//   [x] 0x170bb8  CKAdvancedCameraCinematicBloc_CreateArray
//   [ ] 0x170c68  CKAdvancedCameraCinematicBloc_FindEaseTimeForValue_maybe  [dead]
//   [ ] 0x170da8  CKAdvancedCameraCinematicBloc_ComputeOrbitPoint_maybe
//   [ ] 0x171350  CKAdvancedCameraCinematicBloc_Complete
//   [ ] 0x171570  CKAdvancedCameraCinematicBloc_Update
//   [ ] 0x171d40  CKAdvancedCameraCinematicBloc_Start
//   [x] 0x172560  CKAdvancedCameraCinematicBloc_Load
//
//   [ ] 0x9a9250  CKAdvancedCameraCinematicBloc_IsKindOfClass  [inline]
//   [ ] 0x9a9288  CKAdvancedCameraCinematicBloc_GetClassType  [inline]
//   [ ] 0x9a9290  CKAdvancedCameraCinematicBloc_GetClassID  [inline]
//   [ ] 0x9a9298  CKAdvancedCameraCinematicBloc_PreActivate  [inline]
//   [ ] 0x9a92a0  CKAdvancedCameraCinematicBloc_Destructor  [inline]
//   [ ] 0x9a92c0  CKAdvancedCameraCinematicBloc_DeletingDestructor  [inline]
#include "k2000/cinematics/CKAdvancedCameraCinematicBloc.h"

#include "k2000/io/IKFile.h"

// 0x00172560 CKAdvancedCameraCinematicBloc_Load
int32_t CKAdvancedCameraCinematicBloc::Load(IKFile* file, int32_t type) {
    BasicLoadCinematicElement(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        for (IKSerializable*& ref : m_apUnk38) IKFile_ReadRef(file, &ref);
        ReadU8(file, &m_unk60);
        ReadF32LE(file, &m_unk64);
        ReadU32LE(file, &m_unk68);
        ReadU32LE(file, &m_unk6c);
    }
    return 1;
}
