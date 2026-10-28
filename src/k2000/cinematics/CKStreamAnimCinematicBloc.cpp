// CKStreamAnimCinematicBloc.cpp - reconstructed original translation unit 0x18ba50-0x18c830 (GAME_TOC1, main_toc1), 20 functions, 20 live.
// Primary class: CKStreamAnimCinematicBloc  key 0x288  category CinematicNode  size 0x3c  vtable 0xb1bb68
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x18ba50  CKStreamAnimCinematicBloc_Delete
//   [ ] 0x18baa0  CKStreamAnimCinematicBloc_Abort
//   [ ] 0x18baf8  RegisterCKStreamAnimCinematicBlocClass
//   [ ] 0x18bb70  _GLOBAL__I_18bb70
//   [ ] 0x18bb80  CKStreamAnimCinematicBloc_OnSceneStopped
//   [ ] 0x18bbd8  CKStreamAnimCinematicBloc_Stop
//   [x] 0x18bdc0  CKStreamAnimCinematicBloc_vf54
//   [x] 0x18bde8  CKStreamAnimCinematicBloc_ResetRuntime
//   [ ] 0x18be30  CKStreamAnimCinematicBloc_PostLoad
//   [x] 0x18be90  CKStreamAnimCinematicBloc_Load
//   [ ] 0x18bf50  CKStreamAnimCinematicBloc_Save
//   [ ] 0x18bf78  CKStreamAnimCinematicBloc_RecursiveRegistration
//   [x] 0x18c040  CKStreamAnimCinematicBloc_Construct
//   [ ] 0x18c080  CKStreamAnimCinematicBloc_Construct_2
//   [x] 0x18c0c0  CKStreamAnimCinematicBloc_DeleteArray
//   [ ] 0x18c168  CKStreamAnimCinematicBloc_Update
//   [ ] 0x18c288  CKStreamAnimCinematicBloc_Start
//   [x] 0x18c520  CKStreamAnimCinematicBloc_Create
//   [x] 0x18c580  CKStreamAnimCinematicBloc_CreateArray
//   [ ] 0x18c648  CKStreamAnimCinematicBloc_Complete
//
//   [ ] 0x9aa2f0  CKStreamAnimCinematicBloc_IsKindOfClass  [inline]
//   [ ] 0x9aa328  CKStreamAnimCinematicBloc_GetClassType  [inline]
//   [ ] 0x9aa330  CKStreamAnimCinematicBloc_GetClassID  [inline]
//   [ ] 0x9aa338  CKStreamAnimCinematicBloc_DeletingDestructor  [inline]
//   [ ] 0x9aa380  CKStreamAnimCinematicBloc_Destructor  [inline]
#include "k2000/cinematics/CKStreamAnimCinematicBloc.h"

#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"
#include "k2000/components/CKCinematicStreamCpnt.h"
#include "k2000/logic/CKCinematicScene.h"

// 0x0018c520 CKStreamAnimCinematicBloc_Create
CKStreamAnimCinematicBloc::CKStreamAnimCinematicBloc() { m_pStreamCpnt = nullptr; }

// 0x0018be90 CKStreamAnimCinematicBloc_Load
int32_t CKStreamAnimCinematicBloc::Load(IKFile* file, int32_t type) {
    BasicLoadCinematicElement(file, type);
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pStreamCpnt);
    return 1;
}

// 0x0018bdc0 CKStreamAnimCinematicBloc_vf54: CKCinematicStreamCpnt_InitChannels_maybe(+0x38): every channel's
// slot of its type's table is reset and its init handler called.
// STUB(C2.2): the channel-type slots (CKCinematicStreamCpnt, 0x81ca0) are the hooks family's; a stream bloc
// needs a scene that plays, and none does before the opening cutscene (C2.3).
void CKStreamAnimCinematicBloc::Vf54() {
    DOTD_STUB_ONCE("CKStreamAnimCinematicBloc_vf54 0x18bdc0: CKCinematicStreamCpnt_InitChannels_maybe (C2.2)");
}

// 0x0018bde8 CKStreamAnimCinematicBloc_ResetRuntime
void CKStreamAnimCinematicBloc::PreStart() {
    m_pRelatedScene->SetChainedScenesFlag88(1);
    static_cast<CKCinematicStreamCpnt*>(m_pStreamCpnt)->ResetChannels();
}
