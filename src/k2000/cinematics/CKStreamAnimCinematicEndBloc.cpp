// CKStreamAnimCinematicEndBloc.cpp - reconstructed original translation unit 0x18c830-0x18d470 (GAME_TOC1, main_toc1), 16 functions, 16 live.
// Primary class: CKStreamAnimCinematicEndBloc  key 0x3c8  category CinematicNode  size 0x3c  vtable 0xb1bc00
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x18c830  CKStreamAnimCinematicEndBloc_Delete
//   [x] 0x18c880  CKStreamAnimCinematicEndBloc_Abort
//   [ ] 0x18c8d8  RegisterCKStreamAnimCinematicEndBlocClass
//   [ ] 0x18c950  _GLOBAL__I_18c950
//   [x] 0x18c960  CKStreamAnimCinematicEndBloc_Stop
//   [x] 0x18cb40  CKStreamAnimCinematicEndBloc_Update
//   [x] 0x18cbc8  CKStreamAnimCinematicEndBloc_Load
//   [ ] 0x18cc88  CKStreamAnimCinematicEndBloc_Save
//   [x] 0x18ccb0  CKStreamAnimCinematicEndBloc_RecursiveRegistration
//   [x] 0x18cdb0  CKStreamAnimCinematicEndBloc_Construct
//   [ ] 0x18cdf0  CKStreamAnimCinematicEndBloc_Construct_2  [dead: no pointer to its descriptor 0xb68020, no call]
//   [x] 0x18ce30  CKStreamAnimCinematicEndBloc_DeleteArray
//   [x] 0x18ced8  CKStreamAnimCinematicEndBloc_Start
//   [x] 0x18d170  CKStreamAnimCinematicEndBloc_Create
//   [x] 0x18d1d0  CKStreamAnimCinematicEndBloc_CreateArray
//   [x] 0x18d298  CKStreamAnimCinematicEndBloc_Complete
//
//   [ ] 0x9aa3a0  CKStreamAnimCinematicEndBloc_IsKindOfClass  [inline]
//   [ ] 0x9aa3d8  CKStreamAnimCinematicEndBloc_GetClassType  [inline]
//   [ ] 0x9aa3e0  CKStreamAnimCinematicEndBloc_GetClassID  [inline]
//   [ ] 0x9aa3e8  CKStreamAnimCinematicEndBloc_Destructor  [inline]
//   [ ] 0x9aa408  CKStreamAnimCinematicEndBloc_DeletingDestructor  [inline]
#include "k2000/cinematics/CKStreamAnimCinematicEndBloc.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"

#include "k2000/components/CKCinematicStreamCpnt.h"
#include "k2000/io/IKFile.h"

// 0x0018d170 CKStreamAnimCinematicEndBloc_Create
CKStreamAnimCinematicEndBloc::CKStreamAnimCinematicEndBloc() { m_pStreamCpnt = nullptr; }

// 0x0018cbc8 CKStreamAnimCinematicEndBloc_Load
int32_t CKStreamAnimCinematicEndBloc::Load(IKFile* file, int32_t type) {
    BasicLoadCinematicElement(file, type);
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pStreamCpnt);
    return 1;
}

// 0x0018ced8 CKStreamAnimCinematicEndBloc_Start
void CKStreamAnimCinematicEndBloc::Start() { StartCommon(); }

// 0x0018cb40 CKStreamAnimCinematicEndBloc_Update
void CKStreamAnimCinematicEndBloc::Update(IKTime* /*time*/) {
    if (CheckSekensStop() == 0) return;
    if (m_pStreamCpnt != nullptr) static_cast<CKCinematicStreamCpnt*>(m_pStreamCpnt)->Stop();  // 0x00082008
    Complete();  // vt+0x64
}

// 0x0018c960 CKStreamAnimCinematicEndBloc_Stop
void CKStreamAnimCinematicEndBloc::Stop() {
    CompleteBloc();
    Complete();  // vt+0x64
}

// 0x0018d298 CKStreamAnimCinematicEndBloc_Complete
void CKStreamAnimCinematicEndBloc::Complete() { CompleteBloc(); }

// 0x0018c880 CKStreamAnimCinematicEndBloc_Abort
void CKStreamAnimCinematicEndBloc::Abort() {
    m_DataFlags &= 0xfffffffeu;
    Complete();  // vt+0x64
}

// 0x0018ccb0 CKStreamAnimCinematicEndBloc_RecursiveRegistration
void CKStreamAnimCinematicEndBloc::RecursiveRegistration(int32_t type) {
    IKCinematicBloc::RecursiveRegistration(type);  // 0x0018e8d8
    if (static_cast<uint32_t>(type - 4) <= 3u) return;
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
    if (m_pStreamCpnt != nullptr) m_pStreamCpnt->RecursiveRegistration(type);  // vt+0x24
}
