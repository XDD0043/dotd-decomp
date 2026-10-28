// CKProjectileAccessor.cpp - reconstructed original translation unit 0x1f2868-0x1f32e0 (GAME_TOC1, main_toc1), 28 functions, 28 live.
// Primary class: CKProjectileAccessor  key 0x1e0c  category Logic  size 0xc  vtable 0xb1e858
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1f2868  CKProjectileAccessor_Delete
//   [x] 0x1f28b8  CKProjectileAccessor_vf50
//   [x] 0x1f28c0  CKProjectileAccessor_vf54
//   [ ] 0x1f28c8  CKProjectileAccessor_GetMaxCount
//   [ ] 0x1f28e8  CKProjectileAccessor_GetActiveCount
//   [ ] 0x1f2908  CKProjectileAccessor_Launch
//   [ ] 0x1f2988  CKProjectileAccessor_Launch
//   [ ] 0x1f2a10  CKProjectileAccessor_Launch8C
//   [ ] 0x1f2a98  CKProjectileAccessor_Launch90
//   [ ] 0x1f2b28  CKProjectileAccessor_Launch94
//   [ ] 0x1f2bb0  CKProjectileAccessor_LaunchA0
//   [ ] 0x1f2c50  CKProjectileAccessor_LaunchAtPointEx
//   [ ] 0x1f2cd8  CKProjectileAccessor_LaunchAtPoint
//   [ ] 0x1f2d58  RegisterCKProjectileAccessorClass
//   [ ] 0x1f2dd0  _GLOBAL__I_1f2dd0
//   [ ] 0x1f2de0  CKProjectileAccessor_RecursiveRegistration
//   [ ] 0x1f2e08  CKProjectileAccessor_Save
//   [ ] 0x1f2e30  CKProjectileAccessor_Destroy
//   [ ] 0x1f2e68  CKProjectileAccessor_DeletingDestructor
//   [ ] 0x1f2eb0  CKProjectileAccessor_Destructor
//   [ ] 0x1f2ee0  CKProjectileAccessor_BaseDestructor
//   [x] 0x1f2f10  CKProjectileAccessor_Construct
//   [ ] 0x1f2f50  CKProjectileAccessor_Construct_2
//   [x] 0x1f2f90  CKProjectileAccessor_DeleteArray
//   [ ] 0x1f3038  CKProjectileAccessor_GetFreeSlots
//   [x] 0x1f3068  CKProjectileAccessor_CreateArray
//   [x] 0x1f3130  CKProjectileAccessor_Create
//   [x] 0x1f3190  CKProjectileAccessor_Load
//
//   [x] 0x9b07a0  CKProjectileAccessor_IsKindOfClass  [inline]
//   [ ] 0x9b07c8  CKProjectileAccessor_GetClassType  [inline]
//   [ ] 0x9b07d0  CKProjectileAccessor_GetClassID  [inline]
#include "k2000/logic/CKProjectileAccessor.h"

#include "k2000/io/IKFile.h"

// 0x001f3190 CKProjectileAccessor_Load: KBase1DCC's Load, then (level data only) the two references.
int32_t CKProjectileAccessor::Load(IKFile* file, int32_t type) {
    KBase1DCC::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pProjectileType);
        IKFile_ReadRef(file, &m_pProjectileData);
    }
    return 1;
}
