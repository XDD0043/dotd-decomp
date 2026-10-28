// CKGroupBlocCinematicBloc.cpp - reconstructed original translation unit 0x17c080-0x17d0f0 (GAME_TOC1, main_toc1), 15 functions, 15 live.
// Primary class: CKGroupBlocCinematicBloc  key 0x1c8  category CinematicNode  size 0x48  vtable 0xb1b3b0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x17c080  RegisterCKGroupBlocCinematicBlocClass
//   [ ] 0x17c0f8  _GLOBAL__I_17c0f8
//   [ ] 0x17c108  CKGroupBlocCinematicBloc_MessageProc
//   [ ] 0x17c1b8  CKGroupBlocCinematicBloc_Update
//   [ ] 0x17c260  CKGroupBlocCinematicBloc_Save
//   [ ] 0x17c288  CKGroupBlocCinematicBloc_RecursiveRegistration
//   [x] 0x17c388  CKGroupBlocCinematicBloc_DeleteArray
//   [x] 0x17c430  CKGroupBlocCinematicBloc_Create
//   [ ] 0x17c488  CKGroupBlocCinematicBloc_Abort
//   [ ] 0x17c598  CKGroupBlocCinematicBloc_Stop
//   [ ] 0x17c818  CKGroupBlocCinematicBloc_Destroy
//   [x] 0x17c850  CKGroupBlocCinematicBloc_CreateArray
//   [ ] 0x17c908  CKGroupBlocCinematicBloc_Start
//   [x] 0x17cc38  CKGroupBlocCinematicBloc_Load
//   [ ] 0x17ce68  CKGroupBlocCinematicBloc_Complete
//
//   [ ] 0x9a9790  CKGroupBlocCinematicBloc_IsKindOfClass  [inline]
//   [ ] 0x9a97c8  CKGroupBlocCinematicBloc_GetClassType  [inline]
//   [ ] 0x9a97d0  CKGroupBlocCinematicBloc_GetClassID  [inline]
//   [ ] 0x9a97d8  CKGroupBlocCinematicBloc_Destructor  [inline]
//   [ ] 0x9a97f8  CKGroupBlocCinematicBloc_DeletingDestructor  [inline]
#include "k2000/cinematics/CKGroupBlocCinematicBloc.h"

#include "k2000/io/IKFile.h"

// 0x0017cc38 CKGroupBlocCinematicBloc_Load
int32_t CKGroupBlocCinematicBloc::Load(IKFile* file, int32_t type) {
    BasicLoadCinematicElement(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_ui32EltNumber);
    if (m_ui32EltNumber != 0) {
        m_pEltPointer = new IKSerializable*[m_ui32EltNumber];
        IKFile_ReadObjectRefArray(file, m_pEltPointer, m_ui32EltNumber);
    }
    IKFile_ReadRef(file, &m_pBegin);
    IKFile_ReadRef(file, &m_pEnd);
    return 1;
}
