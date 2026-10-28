// CKSekensorCinematicBloc.cpp - reconstructed original translation unit 0x189578-0x18a2a8 (GAME_TOC1, main_toc1), 16 functions, 16 live.
// Primary class: CKSekensorCinematicBloc  key 0x508  category CinematicNode  size 0x3c  vtable 0xb1b9a0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x189578  CKSekensorCinematicBloc_Delete
//   [ ] 0x1895c8  RegisterCKSekensorCinematicBlocClass
//   [ ] 0x189640  _GLOBAL__I_189640
//   [x] 0x189650  CKSekensorCinematicBloc_Complete
//   [ ] 0x189828  CKSekensorCinematicBloc_PostLoad
//   [x] 0x189850  CKSekensorCinematicBloc_Load
//   [ ] 0x189930  CKSekensorCinematicBloc_Save
//   [ ] 0x189958  CKSekensorCinematicBloc_RecursiveRegistration
//   [x] 0x1899e8  CKSekensorCinematicBloc_DeleteArray
//   [x] 0x189a90  CKSekensorCinematicBloc_Create
//   [x] 0x189ae8  CKSekensorCinematicBloc_Abort
//   [x] 0x189b70  CKSekensorCinematicBloc_Update
//   [ ] 0x189ca8  CKSekensorCinematicBloc_Destroy
//   [x] 0x189cb0  CKSekensorCinematicBloc_CreateArray
//   [x] 0x189d68  CKSekensorCinematicBloc_Start
//   [x] 0x18a0a8  CKSekensorCinematicBloc_Stop
//
//   [ ] 0x9aa0c0  CKSekensorCinematicBloc_IsKindOfClass  [inline]
//   [ ] 0x9aa0f8  CKSekensorCinematicBloc_GetClassType  [inline]
//   [ ] 0x9aa100  CKSekensorCinematicBloc_GetClassID  [inline]
//   [ ] 0x9aa108  CKSekensorCinematicBloc_PreActivate  [inline]
//   [ ] 0x9aa110  CKSekensorCinematicBloc_Destructor  [inline]
//   [ ] 0x9aa130  CKSekensorCinematicBloc_DeletingDestructor  [inline]
#include "k2000/cinematics/CKSekensorCinematicBloc.h"

#include "k2000/logic/CKSekens.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvSekensor.h"

#include "k2000/io/IKFile.h"

// 0x00189850 CKSekensorCinematicBloc_Load
int32_t CKSekensorCinematicBloc::Load(IKFile* file, int32_t type) {
    BasicLoadCinematicElement(file, type);
    // BUG(original): the reference is read whatever the type (the other blocs test for K_LEVEL_PLATEFORMS).
    IKFile_ReadRef(file, &m_pSekens);
    return 1;
}

namespace {
CKSrvSekensor* Sekensor() { return static_cast<CKSrvSekensor*>(g_pEngine->m_srvSekensor); }
}  // namespace

// 0x00189d68 CKSekensorCinematicBloc_Start. The sekens is requested; bit 7 of the flags says it still has to run.
void CKSekensorCinematicBloc::Start() {
    StartCommon();
    if (m_pSekens != nullptr) {
        CKSekens* sekens = static_cast<CKSekens*>(m_pSekens);
        Sekensor()->RequestSekens(sekens);
        m_DataFlags = (m_DataFlags & 0xffffff7fu) | (static_cast<uint32_t>(Sekensor()->IsSekensDone(sekens) ^ 1) << 7);
        return;
    }
    Complete();  // vt+0x64
}

// 0x00189b70 CKSekensorCinematicBloc_Update. Until the request was taken the bloc asks again; then it waits for the sekens to
// be over.
void CKSekensorCinematicBloc::Update(IKTime* /*time*/) {
    if (CheckSekensStop() == 0 || m_pSekens == nullptr) return;
    CKSekens* sekens = static_cast<CKSekens*>(m_pSekens);
    if ((m_DataFlags & 0x80) == 0) {
        Sekensor()->RequestSekens(sekens);
        m_DataFlags = (m_DataFlags & 0xffffff7fu) | (static_cast<uint32_t>(Sekensor()->IsSekensDone(sekens) ^ 1) << 7);
        return;
    }
    if (Sekensor()->IsSekensDone(sekens) != 0) Complete();  // vt+0x64
}

// 0x00189650 CKSekensorCinematicBloc_Complete
void CKSekensorCinematicBloc::Complete() { CompleteBloc(); }

// 0x0018a0a8 CKSekensorCinematicBloc_Stop: the completion (when running), then the sekens cancelled and the bloc completed.
void CKSekensorCinematicBloc::Stop() {
    if ((m_DataFlags & 1) != 0) CompleteBloc();
    if (m_pSekens != nullptr) {
        Sekensor()->CancelSekens(static_cast<CKSekens*>(m_pSekens));
        Complete();  // vt+0x64
    }
}

// 0x00189ae8 CKSekensorCinematicBloc_Abort: the sekens stopped (0x1f41e0 UsesSpeechStream is asked and ignored).
void CKSekensorCinematicBloc::Abort() {
    m_DataFlags &= 0xfffffffeu;
    if (m_pSekens != nullptr) {
        CKSekens* sekens = static_cast<CKSekens*>(m_pSekens);
        if (Sekensor()->IsSekensDone(sekens) == 0) sekens->UsesSpeechStream();
        Sekensor()->StopSekens(sekens);
    }
}
