// CKS08HeroElementShadow.cpp - C2.8 port-final F08 (class in CKS08HeroElementShadow.h).
//
// Reconstructed original translation unit: 0x3d0f88-0x3d1298 (GAME_TOC1, main_toc1), 12 functions, 11 live.
// Primary class: CKS08HeroElementShadow  key 0x8a8c  category Logic  size 0x2cc  vtable 0xb243e0
// Other owners: CKS08HeroElementWind (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x3d0f88  RegisterCKS08HeroElementShadowClass
//   [ ] 0x3d1000  _GLOBAL__I_3d1000
//   [x] 0x3d1010  CKS08HeroElementShadow_Load
//   [ ] 0x3d1038  CKS08HeroElementShadow_Save
//   [x] 0x3d1060  CKS08HeroElementShadow_RecursiveRegistration
//   [x] 0x3d1088  CKS08HeroElementShadow_Destroy
//   [x] 0x3d10b0  CKS08HeroElementShadow_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x3d1150  CKS08HeroElementShadow_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x3d11e0  CKS08HeroElementShadow_Create  (DOTD_DECLARE_FACTORIES)
//   [x] 0x3d1218  CKS08HeroElementShadow_PostLoad
//   [x] 0x3d1240  CKS08HeroElementWind_Delete  (C++ delete: DOTD_DECLARE_FACTORIES(CKS08HeroElementWind))
//   [ ] 0x3d1290  KStub_Nop_3d1290  [dead]
//
//   [x] 0x9c0578  CKS08HeroElementShadow_IsKindOfClass  (CKS08HeroElementShadow.h)
//   [x] 0x9c05b0  CKS08HeroElementShadow_GetClassType  (DOTD_CLASS_KEY)
//   [x] 0x9c05b8  CKS08HeroElementShadow_GetClassID  (DOTD_CLASS_KEY)
//   [x] 0x9c05c0  CKS08HeroElementShadow_Destructor  (~CKS08HeroElementShadow)
//   [x] 0x9c05e0  CKS08HeroElementShadow_DeletingDestructor  (~CKS08HeroElementShadow)
#include "Spyro2008/logic/render/CKS08HeroElementShadow.h"

// 0x003d1088 CKS08HeroElementShadow_Destroy (vt+0x10)
void CKS08HeroElementShadow::Destroy() { CKS08HeroElement::Destroy(); }  // 0x00371580

// 0x003d1060 CKS08HeroElementShadow_RecursiveRegistration (vt+0x24)
void CKS08HeroElementShadow::RecursiveRegistration(int32_t type) { CKS08HeroElement::RecursiveRegistration(type); }  // 0x00371578

// 0x003d1010 CKS08HeroElementShadow_Load (vt+0x2c)
int32_t CKS08HeroElementShadow::Load(IKFile* file, int32_t type) {
    CKS08HeroElement::Load(file, type);  // 0x00372158
    return 1;
}

// 0x003d1218 CKS08HeroElementShadow_PostLoad (vt+0x30)
int32_t CKS08HeroElementShadow::PostLoad(int32_t type) {
    CKS08HeroElement::PostLoad(type);  // 0x003715d8
    return 1;
}
