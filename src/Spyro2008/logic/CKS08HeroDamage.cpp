// CKS08HeroDamage.cpp - reconstructed original translation unit 0x3c9a68-0x3c9f90 (GAME_TOC1, main_toc1), 19 functions, 15 live.
// Primary class: CKS08HeroDamage  key 0x998c  category Logic  size 0x30  vtable 0xb23fa0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3c9a68  CKS08HeroDamage_Delete
//   [ ] 0x3c9ab8  RegisterCKS08HeroDamageClass
//   [ ] 0x3c9b30  _GLOBAL__I_3c9b30
//   [x] 0x3c9b40  CKS08HeroDamage_Destroy  (inherited: CKS08StunDamage_Destroy)
//   [x] 0x3c9b68  CKS08HeroDamage_PostLoad  (= the inherited slot)
//   [x] 0x3c9b90  CKS08HeroDamage_Load
//   [ ] 0x3c9bb8  CKS08HeroDamage_Save
//   [x] 0x3c9be0  CKS08HeroDamage_RecursiveRegistration  (CKS08StunDamage's (nothing registered), then 1)
//   [x] 0x3c9c08  CKS08HeroDamage_Assign
//   [x] 0x3c9c50  CKS08HeroDamage_DeletingDestructor  (the destructor; delete)
//   [x] 0x3c9c98  CKS08HeroDamage_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x3c9cc8  CKS08HeroDamage_DestructBody  (C++ destructor chain: vtable stores, then CKS08StunDamage_BaseDestructor)
//   [x] 0x3c9cf8  CKS08HeroDamage_Construct  [dead]
//   [ ] 0x3c9d30  CKS08HeroDamage_Construct_2  [dead]
//   [ ] 0x3c9d68  CKS08HeroDamage_Construct_3  [dead]
//   [ ] 0x3c9da0  CKS08HeroDamage_Construct_4  [dead]
//   [x] 0x3c9dd8  CKS08HeroDamage_DeleteArray
//   [x] 0x3c9e80  CKS08HeroDamage_CreateArray
//   [x] 0x3c9f38  CKS08HeroDamage_Create
//
//   [ ] 0x9c02c0  CKS08HeroDamage_IsKindOfClass  [inline]
//   [ ] 0x9c0328  CKS08HeroDamage_GetClassType  [inline]
//   [ ] 0x9c0330  CKS08HeroDamage_GetClassID  [inline]
//   [ ] 0x9c0338  CKS08HeroDamage_SetKnockbackSpeed  [inline]
//   [ ] 0x9c0340  CKS08HeroDamage_SetKnockbackLift_maybe  [inline]
//   [ ] 0x9c0348  CKS08HeroDamage_vf58  [inline]
#include "Spyro2008/logic/CKS08HeroDamage.h"

// 0x003c9b90 CKS08HeroDamage_Load: CKS08StunDamage's data only.
int32_t CKS08HeroDamage::Load(IKFile* file, int32_t type) {
    CKS08StunDamage::Load(file, type);
    return 1;
}
