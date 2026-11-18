// CKCameraBeacon_2.cpp - reconstructed original translation unit 0x1dfb50-0x1dfd28 (GAME_TOC1, main_toc1), 17 functions, 16 live.
// Primary class: CKCameraBeacon  key 0x582  category Hook  size 0x54  vtable 0xb1a858
// Other owners: KBase4C2 (8)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1dfb50  CKCameraBeacon_ConstructBase_maybe
//   [x] 0x1dfb98  KBase4C2_ClearReferences  (Destroy: empty, the default)
//   [x] 0x1dfba0  CKCameraBeacon_Start  (empty: IKHook's)
//   [x] 0x1dfba8  CKCameraBeacon_Stop  (empty: IKHook's)
//   [x] 0x1dfbb0  CKCameraBeacon_Pause  (empty: IKHook's)
//   [x] 0x1dfbb8  CKCameraBeacon_Resume  (empty: IKHook's)
//   [x] 0x1dfbc0  CKCameraBeacon_Update  (empty: IKHook's)
//   [x] 0x1dfbc8  KBase4C2_vfC0  (empty; only CKCameraBeacon_vfC0 0x151740 calls it, left)
//   [x] 0x1dfbd0  CKCameraBeacon_vfB4  (empty: IKHook::KGLObjectAttached)
//   [x] 0x1dfbd8  CKCameraBeacon_vfB8  (empty: IKHook::KGLObjectDetached)
//   [x] 0x1dfbe0  KBase4C2_Load
//   [ ] 0x1dfc08  KBase4C2_Save
//   [x] 0x1dfc30  KBase4C2_LevelReset  (RecursiveRegistration: IKHook's, inherited)
//   [ ] 0x1dfc58  CKCameraBeacon_ConstructBase_2_maybe  [dead]
//   [x] 0x1dfca0  KBase4C2_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x1dfcc0  KBase4C2_BaseDestructor  (C++ destructor chain)
//   [x] 0x1dfce0  KBase4C2_DeletingDestructor  (C++ deleting destructor)
//
//   [ ] 0x9adcf8  KBase4C2_IsKindOf  [inline]
//   [ ] 0x9add40  KBase4C2_GetClassGroup  [inline]
//   [ ] 0x9add48  KBase4C2_GetClassId  [inline]
#include "k2000/hooks/KBase4C2.h"

// 0x001dfbe0 KBase4C2_Load: IKHook's part only.
int32_t KBase4C2::Load(IKFile* file, int32_t type) {
    IKHook::Load(file, type);
    return 1;
}
