// CKStreamAnimCinematicBeginBloc.cpp - reconstructed original translation unit 0x18ad68-0x18ba50 (GAME_TOC1, main_toc1), 16 functions, 16 live.
// Primary class: CKStreamAnimCinematicBeginBloc  key 0x388  category CinematicNode  size 0x3c  vtable 0xb1bad0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x18ad68  CKStreamAnimCinematicBeginBloc_Delete
//   [x] 0x18adb8  CKStreamAnimCinematicBeginBloc_Abort
//   [ ] 0x18ae10  RegisterCKStreamAnimCinematicBeginBlocClass
//   [ ] 0x18ae88  _GLOBAL__I_18ae88
//   [x] 0x18ae98  CKStreamAnimCinematicBeginBloc_Stop
//   [x] 0x18b078  CKStreamAnimCinematicBeginBloc_Load
//   [ ] 0x18b138  CKStreamAnimCinematicBeginBloc_Save
//   [x] 0x18b160  CKStreamAnimCinematicBeginBloc_RecursiveRegistration
//   [x] 0x18b260  CKStreamAnimCinematicBeginBloc_Construct
//   [x] 0x18b2a0  CKStreamAnimCinematicBeginBloc_Construct_2  [dead: no pointer to its descriptor 0xb67898, no call]  (the constructor: the same stores as 0x18b260 CKStreamAnimCinematicBeginBloc_Construct)
//   [x] 0x18b2e0  CKStreamAnimCinematicBeginBloc_DeleteArray
//   [x] 0x18b388  CKStreamAnimCinematicBeginBloc_Update
//   [x] 0x18b4a0  CKStreamAnimCinematicBeginBloc_Start
//   [x] 0x18b750  CKStreamAnimCinematicBeginBloc_CreateArray
//   [x] 0x18b818  CKStreamAnimCinematicBeginBloc_Create
//   [x] 0x18b878  CKStreamAnimCinematicBeginBloc_Complete
//
//   [ ] 0x9aa240  CKStreamAnimCinematicBeginBloc_IsKindOfClass  [inline]
//   [ ] 0x9aa278  CKStreamAnimCinematicBeginBloc_GetClassType  [inline]
//   [ ] 0x9aa280  CKStreamAnimCinematicBeginBloc_GetClassID  [inline]
//   [ ] 0x9aa288  CKStreamAnimCinematicBeginBloc_DeletingDestructor  [inline]
//   [ ] 0x9aa2d0  CKStreamAnimCinematicBeginBloc_Destructor  [inline]
#include "k2000/cinematics/CKStreamAnimCinematicBeginBloc.h"
#include "k2000/logic/CKSavingManager.h"

#include "k2000/components/CKCinematicStreamCpnt.h"
#include "k2000/io/IKFile.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvCinematic.h"

// 0x0018b818 CKStreamAnimCinematicBeginBloc_Create
CKStreamAnimCinematicBeginBloc::CKStreamAnimCinematicBeginBloc() { m_pStreamCpnt = nullptr; }

// 0x0018b078 CKStreamAnimCinematicBeginBloc_Load
int32_t CKStreamAnimCinematicBeginBloc::Load(IKFile* file, int32_t type) {
    BasicLoadCinematicElement(file, type);
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pStreamCpnt);
    return 1;
}

// 0x0018b4a0 CKStreamAnimCinematicBeginBloc_Start
void CKStreamAnimCinematicBeginBloc::Start() {
    StartCommon();
    if (m_pStreamCpnt != nullptr) static_cast<CKCinematicStreamCpnt*>(m_pStreamCpnt)->StartStream(1);  // 0x00084ca8
}

// 0x0018b388 CKStreamAnimCinematicBeginBloc_Update: a stream that timed out has the cinematic service skip the scene.
void CKStreamAnimCinematicBeginBloc::Update(IKTime* time) {
    if (CheckSekensStop() == 0 || m_pStreamCpnt == nullptr) return;
    CKCinematicStreamCpnt* stream = static_cast<CKCinematicStreamCpnt*>(m_pStreamCpnt);
    if (stream->UpdateStream(time) == 0) {
        if ((stream->m_unkfc & 0x20) == 0) {
            Complete();  // vt+0x64
            return;
        }
    } else if ((stream->m_unkfc & 0x20) == 0) {
        if ((stream->m_unkfc & 0x400) != 0) Complete();
        return;
    }
    CKSrvCinematic* service = static_cast<CKSrvCinematic*>(g_pEngine->m_srvCinematic);
    service->m_baData = static_cast<uint8_t>((service->m_baData & 0xf0) | 8);
}

// 0x0018ae98 CKStreamAnimCinematicBeginBloc_Stop
void CKStreamAnimCinematicBeginBloc::Stop() {
    CompleteBloc();
    Complete();  // vt+0x64
}

// 0x0018b878 CKStreamAnimCinematicBeginBloc_Complete
void CKStreamAnimCinematicBeginBloc::Complete() { CompleteBloc(); }

// 0x0018adb8 CKStreamAnimCinematicBeginBloc_Abort
void CKStreamAnimCinematicBeginBloc::Abort() {
    m_DataFlags &= 0xfffffffeu;
    Complete();  // vt+0x64
}

// 0x0018b160 CKStreamAnimCinematicBeginBloc_RecursiveRegistration
void CKStreamAnimCinematicBeginBloc::RecursiveRegistration(int32_t type) {
    IKCinematicBloc::RecursiveRegistration(type);  // 0x0018e8d8
    if (static_cast<uint32_t>(type - 4) <= 3u) return;
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
    if (m_pStreamCpnt != nullptr) m_pStreamCpnt->RecursiveRegistration(type);  // vt+0x24
}
