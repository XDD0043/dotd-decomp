// CKS08HeroElementWind.cpp - C2.8 port-final F08 (class in CKS08HeroElementWind.h).
//
// Reconstructed original translation unit: 0x3d1298-0x3d1550 (GAME_TOC1, main_toc1), 10 functions, 10 live.
// Primary class: CKS08HeroElementWind  key 0x8acc  category Logic  size 0x2cc  vtable 0xb24528
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x3d1298  RegisterCKS08HeroElementWindClass
//   [ ] 0x3d1310  _GLOBAL__I_3d1310
//   [x] 0x3d1320  CKS08HeroElementWind_Load
//   [ ] 0x3d1348  CKS08HeroElementWind_Save
//   [x] 0x3d1370  CKS08HeroElementWind_RecursiveRegistration
//   [x] 0x3d1398  CKS08HeroElementWind_Destroy
//   [x] 0x3d13c0  CKS08HeroElementWind_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x3d1460  CKS08HeroElementWind_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x3d14f0  CKS08HeroElementWind_Create  (DOTD_DECLARE_FACTORIES)
//   [x] 0x3d1528  CKS08HeroElementWind_PostLoad
//
//   [x] 0x9c0628  CKS08HeroElementWind_IsKindOfClass  (CKS08HeroElementWind.h)
//   [x] 0x9c0660  CKS08HeroElementWind_GetClassType  (DOTD_CLASS_KEY)
//   [x] 0x9c0668  CKS08HeroElementWind_GetClassID  (DOTD_CLASS_KEY)
//   [x] 0x9c0670  CKS08HeroElementWind_Destructor  (~CKS08HeroElementWind)
//   [x] 0x9c0690  CKS08HeroElementWind_DeletingDestructor  (~CKS08HeroElementWind)
#include "Spyro2008/logic/CKS08HeroElementWind.h"

// 0x003d1398 CKS08HeroElementWind_Destroy (vt+0x10)
void CKS08HeroElementWind::Destroy() { CKS08HeroElement::Destroy(); }  // 0x00371580

// 0x003d1370 CKS08HeroElementWind_RecursiveRegistration (vt+0x24)
void CKS08HeroElementWind::RecursiveRegistration(int32_t type) { CKS08HeroElement::RecursiveRegistration(type); }  // 0x00371578

// 0x003d1320 CKS08HeroElementWind_Load (vt+0x2c)
int32_t CKS08HeroElementWind::Load(IKFile* file, int32_t type) {
    CKS08HeroElement::Load(file, type);  // 0x00372158
    return 1;
}

// 0x003d1528 CKS08HeroElementWind_PostLoad (vt+0x30)
int32_t CKS08HeroElementWind::PostLoad(int32_t type) {
    CKS08HeroElement::PostLoad(type);  // 0x003715d8
    return 1;
}
