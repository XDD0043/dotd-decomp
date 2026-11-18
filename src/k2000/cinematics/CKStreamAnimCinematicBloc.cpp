// CKStreamAnimCinematicBloc.cpp - reconstructed original translation unit 0x18ba50-0x18c830 (GAME_TOC1, main_toc1), 20 functions, 20 live.
// Primary class: CKStreamAnimCinematicBloc  key 0x288  category CinematicNode  size 0x3c  vtable 0xb1bb68
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x18ba50  CKStreamAnimCinematicBloc_Delete
//   [x] 0x18baa0  CKStreamAnimCinematicBloc_Abort
//   [ ] 0x18baf8  RegisterCKStreamAnimCinematicBlocClass
//   [ ] 0x18bb70  _GLOBAL__I_18bb70
//   [x] 0x18bb80  CKStreamAnimCinematicBloc_OnSceneStopped
//   [x] 0x18bbd8  CKStreamAnimCinematicBloc_Stop
//   [x] 0x18bdc0  CKStreamAnimCinematicBloc_vf54
//   [x] 0x18bde8  CKStreamAnimCinematicBloc_ResetRuntime
//   [x] 0x18be30  CKStreamAnimCinematicBloc_PostLoad
//   [x] 0x18be90  CKStreamAnimCinematicBloc_Load
//   [ ] 0x18bf50  CKStreamAnimCinematicBloc_Save
//   [x] 0x18bf78  CKStreamAnimCinematicBloc_RecursiveRegistration
//   [x] 0x18c040  CKStreamAnimCinematicBloc_Construct
//   [x] 0x18c080  CKStreamAnimCinematicBloc_Construct_2  [dead: no pointer to its descriptor 0xb67c60, no call]  (the constructor: the same stores as 0x18c040 CKStreamAnimCinematicBloc_Construct)
//   [x] 0x18c0c0  CKStreamAnimCinematicBloc_DeleteArray
//   [x] 0x18c168  CKStreamAnimCinematicBloc_Update
//   [x] 0x18c288  CKStreamAnimCinematicBloc_Start
//   [x] 0x18c520  CKStreamAnimCinematicBloc_Create
//   [x] 0x18c580  CKStreamAnimCinematicBloc_CreateArray
//   [x] 0x18c648  CKStreamAnimCinematicBloc_Complete
//
//   [ ] 0x9aa2f0  CKStreamAnimCinematicBloc_IsKindOfClass  [inline]
//   [ ] 0x9aa328  CKStreamAnimCinematicBloc_GetClassType  [inline]
//   [ ] 0x9aa330  CKStreamAnimCinematicBloc_GetClassID  [inline]
//   [ ] 0x9aa338  CKStreamAnimCinematicBloc_DeletingDestructor  [inline]
//   [ ] 0x9aa380  CKStreamAnimCinematicBloc_Destructor  [inline]
#include "k2000/cinematics/CKStreamAnimCinematicBloc.h"
#include "k2000/logic/CKSavingManager.h"

#include "k2000/io/IKFile.h"
#include "k2000/components/CKCinematicStreamCpnt.h"
#include "k2000/logic/CKCinematicScene.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvCinematic.h"

// 0x0018c520 CKStreamAnimCinematicBloc_Create
CKStreamAnimCinematicBloc::CKStreamAnimCinematicBloc() { m_pStreamCpnt = nullptr; }

// 0x0018be90 CKStreamAnimCinematicBloc_Load
int32_t CKStreamAnimCinematicBloc::Load(IKFile* file, int32_t type) {
    BasicLoadCinematicElement(file, type);
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pStreamCpnt);
    return 1;
}

// 0x0018bdc0 CKStreamAnimCinematicBloc_vf54: CKCinematicStreamCpnt_InitChannels_maybe(+0x38).
void CKStreamAnimCinematicBloc::Vf54() { static_cast<CKCinematicStreamCpnt*>(m_pStreamCpnt)->InitChannels(); }

// 0x0018bde8 CKStreamAnimCinematicBloc_ResetRuntime
void CKStreamAnimCinematicBloc::PreStart() {
    m_pRelatedScene->SetChainedScenesFlag88(1);
    static_cast<CKCinematicStreamCpnt*>(m_pStreamCpnt)->ResetChannels();
}

// 0x0018be30 CKStreamAnimCinematicBloc_PostLoad (IKCinematicBloc_PostLoad 0x18eac0: KStub_Return1_18fc18, 1)
int32_t CKStreamAnimCinematicBloc::PostLoad(int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) m_pRelatedScene->SetChainedScenesFlag88(1);
    return 1;
}

// 0x0018c288 CKStreamAnimCinematicBloc_Start
void CKStreamAnimCinematicBloc::Start() { StartCommon(); }

// 0x0018c168 CKStreamAnimCinematicBloc_Update: a stream that timed out (+0xfc bit 5) has the cinematic service skip the
// scene (+0x0c: the low bits cleared, bit 3 set).
void CKStreamAnimCinematicBloc::Update(IKTime* time) {
    if (CheckSekensStop() == 0) return;  // 0x0018e9e0
    CKCinematicStreamCpnt* stream = static_cast<CKCinematicStreamCpnt*>(m_pStreamCpnt);
    if (stream->UpdateStream(time) == 0) {
        if ((stream->m_unkfc & 0x20) == 0) {
            Complete();  // vt+0x64
            return;
        }
    } else if ((stream->m_unkfc & 0x20) == 0) {
        if ((stream->m_unkfc & 0x400) != 0) stream->Update(time);
        return;
    }
    CKSrvCinematic* service = static_cast<CKSrvCinematic*>(g_pEngine->m_srvCinematic);
    service->m_baData = static_cast<uint8_t>((service->m_baData & 0xf0) | 8);
}

// 0x0018bbd8 CKStreamAnimCinematicBloc_Stop
void CKStreamAnimCinematicBloc::Stop() {
    CompleteBloc();
    Complete();  // vt+0x64
    static_cast<CKCinematicStreamCpnt*>(m_pStreamCpnt)->Stop();
}

// 0x0018c648 CKStreamAnimCinematicBloc_Complete
void CKStreamAnimCinematicBloc::Complete() {
    static_cast<CKCinematicStreamCpnt*>(m_pStreamCpnt)->Finish();
    CompleteBloc();
}

// 0x0018baa0 CKStreamAnimCinematicBloc_Abort
void CKStreamAnimCinematicBloc::Abort() {
    m_DataFlags &= 0xfffffffeu;
    Complete();  // vt+0x64
}

// 0x0018bb80 CKStreamAnimCinematicBloc_OnSceneStopped
void CKStreamAnimCinematicBloc::OnSceneStopped() {
    CKCinematicStreamCpnt* stream = static_cast<CKCinematicStreamCpnt*>(m_pStreamCpnt);
    if ((stream->m_unkfc & 0x40) == 0) return;
    stream->Finish();
    stream->Stop();
}

// 0x0018bf78 CKStreamAnimCinematicBloc_RecursiveRegistration
void CKStreamAnimCinematicBloc::RecursiveRegistration(int32_t type) {
    IKCinematicBloc::RecursiveRegistration(type);  // 0x0018e8d8
    if (static_cast<uint32_t>(type - 4) <= 3u) return;
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
    m_pStreamCpnt->RecursiveRegistration(type);  // vt+0x24
}
