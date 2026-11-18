// PS3_CKSrvNetwork.cpp - reconstructed original translation unit 0x1dfd28-0x1e09e8 (GAME_TOC1, main_toc1), 38 functions, 28 live.
// Primary class: PS3_CKSrvNetwork  key 0x601  category Service  size 0x2c  vtable 0xb1e2e0
// Other owners: Vt (12)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x1dfd28  Vt_b1e2d0_Construct_maybe  [dead]
//   [ ] 0x1dfd98  Vt_b1e2d0_CopyEntry0ToBuffer_maybe  [dead]
//   [ ] 0x1dfe48  Vt_b1e2d0_CopyBufferToEntry_maybe  [dead]
//   [ ] 0x1dff20  Vt_b1e2d0_GetEntryByteSize_maybe  [dead]
//   [ ] 0x1dff88  Vt_b1e2d0_Construct_2_maybe  [dead]
//   [ ] 0x1dfff8  Vt_b1e2d0_AddZeroedSegment_maybe  [dead]
//   [ ] 0x1e01c0  Vt_b1e2d0_Destructor_2_maybe  [dead]
//   [ ] 0x1e0278  Vt_b1e2d0_ConstructWithCount_maybe  [dead]
//   [ ] 0x1e0428  Vt_b1e2d0_DeletingDestructor_maybe  [dead: its vtable 0xb1e2d0 (TOC1 -0x16c0) is installed only by the dead constructors above]
//   [ ] 0x1e04f8  Vt_b1e2d0_Destructor_maybe  [dead: its vtable 0xb1e2d0 (TOC1 -0x16c0) is installed only by the dead constructors above]
//   [ ] 0x1e05b0  Vt_b1e2d0_SetEntryCount_maybe  [dead]
//   [ ] 0x1e0720  Vt_b1e2d0_ConstructWithCount_2_maybe  [dead]
//   [x] 0x1e08d0  PS3_CKSrvNetwork_Delete
//   [x] 0x1e0920  PS3_CKSrvNetwork_InitializeService
//   [x] 0x1e0928  PS3_CKSrvNetwork_DestroyService
//   [x] 0x1e0930  PS3_CKSrvNetwork_Destroy  (empty: the root's default)
//   [x] 0x1e0938  PS3_CKSrvNetwork_RecursiveRegistration  (returns 1: the root's empty slot)
//   [ ] 0x1e0940  PS3_CKSrvNetwork_Save
//   [x] 0x1e0948  PS3_CKSrvNetwork_Load
//   [x] 0x1e0950  PS3_CKSrvNetwork_Start
//   [x] 0x1e0958  PS3_CKSrvNetwork_Stop
//   [x] 0x1e0960  PS3_CKSrvNetwork_Pause
//   [x] 0x1e0968  PS3_CKSrvNetwork_Resume
//   [x] 0x1e0970  PS3_CKSrvNetwork_Update
//   [x] 0x1e0978  PS3_CKSrvNetwork_vfA8  (PS3_CKSrvNetwork.h)
//   [x] 0x1e0980  PS3_CKSrvNetwork_vfAC  (PS3_CKSrvNetwork.h)
//   [x] 0x1e0988  PS3_CKSrvNetwork_vfB0  (PS3_CKSrvNetwork.h)
//   [x] 0x1e0990  PS3_CKSrvNetwork_vfB4  (PS3_CKSrvNetwork.h)
//   [x] 0x1e0998  PS3_CKSrvNetwork_vfB8  (PS3_CKSrvNetwork.h)
//   [x] 0x1e09a0  PS3_CKSrvNetwork_vfBC  (PS3_CKSrvNetwork.h)
//   [x] 0x1e09a8  PS3_CKSrvNetwork_vfC0  (PS3_CKSrvNetwork.h)
//   [x] 0x1e09b0  PS3_CKSrvNetwork_vfC4  (PS3_CKSrvNetwork.h)
//   [x] 0x1e09b8  PS3_CKSrvNetwork_vfE8  (PS3_CKSrvNetwork.h)
//   [x] 0x1e09c0  PS3_CKSrvNetwork_vfEC  (PS3_CKSrvNetwork.h)
//   [x] 0x1e09c8  PS3_CKSrvNetwork_vfFC  (PS3_CKSrvNetwork.h)
//   [x] 0x1e09d0  PS3_CKSrvNetwork_vfF0  (PS3_CKSrvNetwork.h)
//   [x] 0x1e09d8  PS3_CKSrvNetwork_vfF4  (PS3_CKSrvNetwork.h)
//   [x] 0x1e09e0  PS3_CKSrvNetwork_vfF8  (PS3_CKSrvNetwork.h)
//
//   [ ] 0x9add50  PS3_CKSrvNetwork_IsKindOfClass  [inline]
//   [ ] 0x9add88  KStub_Return1_9add88  [inline]
//   [ ] 0x9add90  KStub_Return24_9add90  [inline]
//   [ ] 0x9add98  PS3_CKSrvNetwork_GetClassType  [inline]
//   [ ] 0x9adda0  PS3_CKSrvNetwork_GetClassID  [inline]
//   [ ] 0x9adda8  PS3_CKSrvNetwork_vfC8  [inline]
//   [ ] 0x9addb0  PS3_CKSrvNetwork_vfCC  [inline]
//   [ ] 0x9addb8  PS3_CKSrvNetwork_vfD0  [inline]
//   [ ] 0x9addc8  PS3_CKSrvNetwork_vfD4  [inline]
//   [ ] 0x9addd8  PS3_CKSrvNetwork_vfD8  [inline]
//   [ ] 0x9adde0  PS3_CKSrvNetwork_vfDC  [inline]
//   [ ] 0x9adde8  PS3_CKSrvNetwork_vfE0  [inline]
//   [ ] 0x9addf0  PS3_CKSrvNetwork_vfE4  [inline]
#include "k2000/services/PS3_CKSrvNetwork.h"

// 0x001e0948 PS3_CKSrvNetwork_Load: reads nothing.
int32_t PS3_CKSrvNetwork::Load(IKFile* /*file*/, int32_t /*type*/) { return 1; }
