// CKS08StunDamage.cpp - reconstructed original translation unit 0x3d1550-0x3d1c38 (GAME_TOC1, main_toc1), 19 functions, 16 live.
// Primary class: CKS08StunDamage  key 0x9acc  category Logic  size 0x30  vtable 0xb24670
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3d1550  CKS08StunDamage_Delete
//   [ ] 0x3d15a0  RegisterCKS08StunDamageClass
//   [ ] 0x3d1618  _GLOBAL__I_3d1618
//   [x] 0x3d1628  CKS08StunDamage_Destroy  (inherited: CKS08Damage_Destroy)
//   [x] 0x3d1650  CKS08StunDamage_PostLoad  (= the inherited slot)
//   [x] 0x3d1678  CKS08StunDamage_RecursiveRegistration  (inherited: CKS08Damage's RecursiveRegistration slot)
//   [x] 0x3d16a0  CKS08StunDamage_Assign
//   [x] 0x3d1710  CKS08StunDamage_DeletingDestructor  (~CKS08StunDamage, C++ destructor chain)
//   [x] 0x3d1758  CKS08StunDamage_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x3d1788  CKS08StunDamage_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [ ] 0x3d17b8  CKS08StunDamage_CopyConstruct_maybe  [dead]
//   [ ] 0x3d1810  CKS08StunDamage_CopyConstruct_2_maybe  [dead]
//   [ ] 0x3d1868  CKS08StunDamage_Construct_2  [dead]
//   [x] 0x3d18a0  CKS08StunDamage_Construct
//   [x] 0x3d18d8  CKS08StunDamage_DeleteArray
//   [x] 0x3d1980  CKS08StunDamage_Load
//   [ ] 0x3d1a58  CKS08StunDamage_Save
//   [x] 0x3d1b28  CKS08StunDamage_CreateArray
//   [x] 0x3d1be0  CKS08StunDamage_Create
//
//   [ ] 0x9c06d8  CKS08StunDamage_IsKindOfClass  [inline]
//   [ ] 0x9c0728  CKS08StunDamage_GetClassType  [inline]
//   [ ] 0x9c0730  CKS08StunDamage_GetClassID  [inline]
#include "Spyro2008/logic/CKS08StunDamage.h"

#include "k2000/io/IKFile.h"

// 0x003d1980 CKS08StunDamage_Load: CKS08Damage's data, then two words.
int32_t CKS08StunDamage::Load(IKFile* file, int32_t type) {
    CKS08Damage::Load(file, type);
    ReadU32LE(file, &m_fStunAmount);
    ReadF32LE(file, &m_fDisarmAmount);
    return 1;
}
