// CKSrvAvoidance.cpp - reconstructed original translation unit 0x122a50-0x123350 (GAME_TOC1, main_toc1), 21 functions, 19 live.
// Primary class: CKSrvAvoidance  key 0x241  category Service  size 0xd8  vtable 0xb19b20
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x122a50  CKSrvAvoidance_Delete
//   [ ] 0x122aa0  CKSrvAvoidance_Construct  [dead]
//   [x] 0x122ad8  CKSrvAvoidance_DestroyService
//   [ ] 0x122ae0  CKSrvAvoidance_RecursiveRegistration
//   [ ] 0x122b40  CKSrvAvoidance_Start
//   [ ] 0x122b48  CKSrvAvoidance_Stop
//   [ ] 0x122b50  CKSrvAvoidance_Pause
//   [ ] 0x122b58  CKSrvAvoidance_Resume
//   [ ] 0x122b60  CKSrvAvoidance_AddAgent_maybe
//   [ ] 0x122bb0  CKSrvAvoidance_RemoveAgent_maybe
//   [ ] 0x122c48  CKSrvAvoidance_Construct_2  [dead]
//   [ ] 0x122c80  RegisterCKSrvAvoidanceClass
//   [ ] 0x122cf8  _GLOBAL__I_122cf8
//   [ ] 0x122d08  CKSrvAvoidance_InitializeService
//   [ ] 0x122d30  CKSrvAvoidance_Destroy
//   [x] 0x122d58  CKSrvAvoidance_DeleteArray
//   [ ] 0x122df8  UpdateCKSrvAvoidance
//   [x] 0x1231d8  CKSrvAvoidance_Load
//   [ ] 0x123218  CKSrvAvoidance_Save
//   [x] 0x123220  CKSrvAvoidance_CreateArray
//   [x] 0x1232e8  CKSrvAvoidance_Create
//
//   [ ] 0x9a6e78  CKSrvAvoidance_IsKindOfClass  [inline]
//   [ ] 0x9a6eb0  CKSrvAvoidance_GetClassType  [inline]
//   [ ] 0x9a6eb8  CKSrvAvoidance_GetClassID  [inline]
//   [ ] 0x9a6ec0  CKSrvAvoidance_DeletingDestructor  [inline]
//   [ ] 0x9a6f08  CKSrvAvoidance_Destructor  [inline]
#include "k2000/services/CKSrvAvoidance.h"

// Inlined in 0x001232e8 CKSrvAvoidance_Create (0x122aa0 CKSrvAvoidance_Construct is an unreferenced
// copy): only the IKService part and the priority.
CKSrvAvoidance::CKSrvAvoidance() { m_ui32Priority = 0xaa; }

// 0x001231d8 CKSrvAvoidance_Load: for a level, the count first, then the 50 slots.
int32_t CKSrvAvoidance::Load(IKFile* /*file*/, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        m_ui32NbSubscriber = 0;
        for (uint32_t i = 0; i < kMaxSubscribers; ++i) m_apSubscriber[i] = nullptr;
    }
    return 1;
}
