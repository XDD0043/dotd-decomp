// CKS08EnemyElement.cpp - reconstructed original translation unit 0x26b348-0x26c918 (GAME_TOC1, main_toc1), 18 functions, 18 live.
// Primary class: CKS08EnemyElement  key 0x7a0c  category Logic  size 0x64  vtable 0xb21a80
// Other owners: CKS08Accessory (3), EnemyArmorPart (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x26b348  CKS08EnemyElement_Delete
//   [ ] 0x26b398  CKS08EnemyElement_BreakOff_maybe
//   [x] 0x26b738  CKS08EnemyElement_DeleteArray
//   [x] 0x26b7d8  CKS08EnemyElement_Create
//   [ ] 0x26b810  RegisterCKS08EnemyElementClass
//   [ ] 0x26b898  _GLOBAL__D_26b898
//   [ ] 0x26b8a8  _GLOBAL__I_26b8a8
//   [ ] 0x26b8b8  CKS08Accessory_AttachToOwner_maybe
//   [ ] 0x26b9a8  EnemyArmorPart_ApplyDamage
//   [ ] 0x26bb58  CKS08Accessory_UpdateMotion_maybe
//   [ ] 0x26c158  CKS08EnemyElement_vf50
//   [x] 0x26c258  CKS08EnemyElement_CreateArray
//   [ ] 0x26c2e8  CKS08EnemyElement_Save
//   [ ] 0x26c2f0  CKS08EnemyElement_PostLoad
//   [ ] 0x26c3f8  CKS08EnemyElement_RecursiveRegistration
//   [ ] 0x26c400  CKS08EnemyElement_Destroy
//   [ ] 0x26c408  CKS08Accessory_LaunchFromHit_maybe
//   [x] 0x26c7b8  CKS08EnemyElement_Load
//
//   [ ] 0x9bbce8  CKS08EnemyElement_GetClassType  [inline]
//   [ ] 0x9bbcf0  CKS08EnemyElement_GetClassID  [inline]
//   [ ] 0x9bbcf8  CKS08EnemyElement_vf54  [inline]
//   [ ] 0x9bbd00  CKS08EnemyElement_IsKindOfClass  [inline]
//   [ ] 0x9bbd20  CKS08EnemyElement_DeletingDestructor  [inline]
//   [ ] 0x9bbd60  CKS08EnemyElement_Destructor  [inline]
#include "Spyro2008/logic/CKS08EnemyElement.h"

#include "k2000/io/IKFile.h"

// 0x0026c7b8 CKS08EnemyElement_Load: two references, whatever the type.
int32_t CKS08EnemyElement::Load(IKFile* file, int32_t /*type*/) {
    IKFile_ReadRef(file, &m_pNode);
    IKFile_ReadRef(file, &m_pGlow);
    return 1;
}
