// CKStartEventCinematicBloc.cpp - reconstructed original translation unit 0x18a2a8-0x18ad68 (GAME_TOC1, main_toc1), 14 functions, 14 live.
// Primary class: CKStartEventCinematicBloc  key 0x648  category CinematicNode  size 0x40  vtable 0xb1ba38
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x18a2a8  CKStartEventCinematicBloc_Delete
//   [ ] 0x18a2f8  RegisterCKStartEventCinematicBlocClass
//   [ ] 0x18a370  _GLOBAL__I_18a370
//   [x] 0x18a380  CKStartEventCinematicBloc_Stop
//   [x] 0x18a560  CKStartEventCinematicBloc_Update
//   [x] 0x18a588  CKStartEventCinematicBloc_Load
//   [ ] 0x18a5f0  CKStartEventCinematicBloc_Save
//   [ ] 0x18a658  CKStartEventCinematicBloc_RecursiveRegistration
//   [x] 0x18a700  CKStartEventCinematicBloc_DeleteArray
//   [x] 0x18a7a0  CKStartEventCinematicBloc_Create
//   [ ] 0x18a7f8  CKStartEventCinematicBloc_Destroy
//   [x] 0x18a800  CKStartEventCinematicBloc_CreateArray
//   [x] 0x18a8b0  CKStartEventCinematicBloc_Start
//   [x] 0x18ab90  CKStartEventCinematicBloc_Complete
//
//   [ ] 0x9aa178  CKStartEventCinematicBloc_IsKindOfClass  [inline]
//   [ ] 0x9aa1b0  CKStartEventCinematicBloc_GetClassType  [inline]
//   [ ] 0x9aa1b8  CKStartEventCinematicBloc_GetClassID  [inline]
//   [ ] 0x9aa1c0  CKStartEventCinematicBloc_PreActivate  [inline]
//   [x] 0x9aa1c8  CKStartEventCinematicBloc_Abort  [inline]
//   [ ] 0x9aa1d8  CKStartEventCinematicBloc_Destructor  [inline]
//   [ ] 0x9aa1f8  CKStartEventCinematicBloc_DeletingDestructor  [inline]
#include "k2000/cinematics/CKStartEventCinematicBloc.h"

#include "k2000/services/CTriggerStarter.h"

// 0x0018a588 CKStartEventCinematicBloc_Load
int32_t CKStartEventCinematicBloc::Load(IKFile* file, int32_t type) {
    BasicLoadCinematicElement(file, type);
    m_Starter.Load(file, type);
    return 1;
}

// 0x0018a8b0 CKStartEventCinematicBloc_Start: the event's trigger signals queued, then the bloc completes.
void CKStartEventCinematicBloc::Start() {
    StartCommon();
    QueueTriggerSignals(&m_Starter);
    Complete();  // vt+0x64
}

// 0x0018a560 CKStartEventCinematicBloc_Update
void CKStartEventCinematicBloc::Update(IKTime* /*time*/) { CheckSekensStop(); }

// 0x0018ab90 CKStartEventCinematicBloc_Complete
void CKStartEventCinematicBloc::Complete() { CompleteBloc(); }

// 0x0018a380 CKStartEventCinematicBloc_Stop
void CKStartEventCinematicBloc::Stop() {
    CompleteBloc();
    Complete();  // vt+0x64
}

// 0x009aa1c8 CKStartEventCinematicBloc_Abort
void CKStartEventCinematicBloc::Abort() { m_DataFlags &= 0xfffffffeu; }
