// CKPauseCinematicBloc.cpp - reconstructed original translation unit 0x1840f8-0x184ca0 (GAME_TOC1, main_toc1), 15 functions, 15 live.
// Primary class: CKPauseCinematicBloc  key 0x748  category CinematicNode  size 0x40  vtable 0xb1b740
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1840f8  CKPauseCinematicBloc_Delete
//   [x] 0x184148  CKPauseCinematicBloc_Abort
//   [ ] 0x184158  RegisterCKPauseCinematicBlocClass
//   [ ] 0x1841d0  _GLOBAL__I_1841d0
//   [x] 0x1841e0  CKPauseCinematicBloc_Stop
//   [x] 0x1843c0  CKPauseCinematicBloc_Update
//   [x] 0x184460  CKPauseCinematicBloc_Load
//   [ ] 0x184508  CKPauseCinematicBloc_Save
//   [ ] 0x1845b0  CKPauseCinematicBloc_RecursiveRegistration
//   [x] 0x184640  CKPauseCinematicBloc_DeleteArray
//   [x] 0x1846e0  CKPauseCinematicBloc_Create
//   [ ] 0x184738  CKPauseCinematicBloc_Destroy
//   [x] 0x184740  CKPauseCinematicBloc_CreateArray
//   [x] 0x1847f0  CKPauseCinematicBloc_Start
//   [x] 0x184ab0  CKPauseCinematicBloc_Complete
//
//   [ ] 0x9a9c78  CKPauseCinematicBloc_IsKindOfClass  [inline]
//   [ ] 0x9a9cb0  CKPauseCinematicBloc_GetClassType  [inline]
//   [ ] 0x9a9cb8  CKPauseCinematicBloc_GetClassID  [inline]
//   [ ] 0x9a9cc0  CKPauseCinematicBloc_Destructor  [inline]
//   [ ] 0x9a9ce0  CKPauseCinematicBloc_DeletingDestructor  [inline]
#include "k2000/cinematics/CKPauseCinematicBloc.h"

#include "k2000/system/IKTime.h"

#include "k2000/io/IKFile.h"

// 0x00184460 CKPauseCinematicBloc_Load
int32_t CKPauseCinematicBloc::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        BasicLoadCinematicElement(file, K_LEVEL_PLATEFORMS);
        ReadF32LE(file, &m_fPauseTime);
    }
    return 1;
}

// 0x001847f0 CKPauseCinematicBloc_Start: the pause counter loaded.
void CKPauseCinematicBloc::Start() {
    StartCommon();
    m_fCurrentTime = m_fPauseTime;
}

// 0x001843c0 CKPauseCinematicBloc_Update: the bloc completes once the counter (game time) has run out.
void CKPauseCinematicBloc::Update(IKTime* time) {
    if (CheckSekensStop() == 0) return;
    if (m_fCurrentTime <= 0.0f) {
        Complete();  // vt+0x64
    } else {
        m_fCurrentTime = m_fCurrentTime - time->m_afDeltaTime[0];
    }
}

// 0x00184ab0 CKPauseCinematicBloc_Complete: the completion inlined, then the counter reloaded.
void CKPauseCinematicBloc::Complete() {
    CompleteBloc();
    m_fCurrentTime = m_fPauseTime;
}

// 0x001841e0 CKPauseCinematicBloc_Stop
void CKPauseCinematicBloc::Stop() {
    CompleteBloc();
    Complete();  // vt+0x64
}

// 0x00184148 CKPauseCinematicBloc_Abort
void CKPauseCinematicBloc::Abort() { m_DataFlags &= 0xfffffffeu; }
