// CKHkActorBase.cpp - reconstructed original translation unit: 0x3f6dc0-0x3f7430 (GAME_TOC1, main_toc1), 22 functions, 21 live.
// Primary owner: CKHkActorBase (not a registered class)
// Other owners: KBaseD82 (2), WorldObjectBase (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3f6dc0  CKHkActorBase_d82_maybe_Construct
//   [ ] 0x3f6e08  CKHkActorBase_d82_maybe_ClearReferences
//   [x] 0x3f6e48  CKHkActorBase_d82_maybe_ResetRuntime
//   [ ] 0x3f6e50  CKHkActorBase_d82_maybe_Stop
//   [ ] 0x3f6e58  KStub_Nop_3f6e58
//   [ ] 0x3f6e60  KStub_Nop_3f6e60
//   [ ] 0x3f6e68  WorldObjectBase_Update_Nop
//   [ ] 0x3f6e70  CKHkActorBase_d82_maybe_PostLoad
//   [x] 0x3f6e98  CKHkActorBase_d82_maybe_Load
//   [ ] 0x3f6ec0  CKHkActorBase_d82_maybe_Save
//   [ ] 0x3f6ee8  CKHkActorBase_d82_maybe_LevelReset
//   [ ] 0x3f6f10  KBaseD82_vfC4
//   [ ] 0x3f70f8  CKHkActorBase_d82_maybe_Construct_2  [dead]
//   [ ] 0x3f7140  KStub_Return1_3f7140
//   [ ] 0x3f7148  CKHkActorBase_d82_maybe_MessageProc
//   [x] 0x3f72a0  KStub_Nop_3f72a0
//   [ ] 0x3f72a8  KBaseD82_SetGameState
//   [ ] 0x3f7338  CKHkActorBase_d82_maybe_OnActivate
//   [ ] 0x3f7370  CKHkActorBase_d82_maybe_OnDeactivate
//   [ ] 0x3f73a8  CKHkActorBase_d82_maybe_DeletingDestructor
//   [ ] 0x3f73f0  CKHkActorBase_d82_maybe_BaseDestructor
//   [ ] 0x3f7410  CKHkActorBase_d82_maybe_Destructor
//
//   [ ] 0x9c0b70  CKHkActorBase_d82_maybe_IsKindOf  [inline]
//   [ ] 0x9c0bb8  CKHkActorBase_d82_maybe_GetClassGroup  [inline]
//   [ ] 0x9c0bc0  CKHkActorBase_d82_maybe_GetClassId  [inline]
//   [ ] 0x9c0bc8  KStub_Nop_9c0bc8  [inline]
//   [ ] 0x9c0bd0  KStub_Nop_9c0bd0  [inline]
//   [ ] 0x9c0bd8  KStub_Nop_9c0bd8  [inline]
//   [ ] 0x9c0be0  KStub_Nop_9c0be0  [inline]
//   [ ] 0x9c0be8  KStub_Return0_9c0be8  [inline]
//   [ ] 0x9c0bf0  KStub_Return0_9c0bf0  [inline]
//   [ ] 0x9c0bf8  KStub_Return0_9c0bf8  [inline]
//   [ ] 0x9c0c00  KStub_Return0_9c0c00  [inline]
//   [ ] 0x9c0c08  KStub_Return0_9c0c08  [inline]
//   [ ] 0x9c0c10  KStub_Return0_9c0c10  [inline]
//   [ ] 0x9c0c18  CKHkActorBase_d82_maybe_SetVisible  [inline]
#include "k2000/misc/CKHkActorBase.h"

// 0x003f6e98 CKHkActorBase_d82_maybe_Load: IKHook's part only.
int32_t CKHkActorBase::Load(IKFile* file, int32_t type) {
    IKHook::Load(file, type);
    return 1;
}
