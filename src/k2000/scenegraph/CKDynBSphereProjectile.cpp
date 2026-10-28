// CKDynBSphereProjectile.cpp - reconstructed original translation unit 0xd7878-0xd7d68 (GAME_TOC1, main_toc1), 8 functions, 8 live.
// Primary class: CKDynBSphereProjectile  key 0x18b  category SceneNode  size 0x50  vtable 0xb18810
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xd7878  CKDynBSphereProjectile_Delete
//   [ ] 0xd78c8  RegisterCKDynBSphereProjectileClass
//   [ ] 0xd7940  _GLOBAL__I_d7940
//   [x] 0xd7950  CKDynBSphereProjectile_DeleteArray
//   [x] 0xd79f8  CKDynBSphereProjectile_CreateArray
//   [x] 0xd7ae8  CKDynBSphereProjectile_Create
//   [ ] 0xd7b58  CKDynBSphereProjectile_Destroy
//   [x] 0xd7b80  CKDynBSphereProjectile_Load
//
//   [x] 0x9a44a0  CKDynBSphereProjectile_GetClassType  [inline]
//   [x] 0x9a44a8  CKDynBSphereProjectile_GetClassID  [inline]
//   [ ] 0x9a44b0  CKDynBSphereProjectile_GetSerializationFlags  [inline]
//   [ ] 0x9a44b8  CKDynBSphereProjectile_vf74  [inline]
//   [ ] 0x9a44c0  CKDynBSphereProjectile_IsKindOfClass  [inline]
//   [ ] 0x9a4520  CKDynBSphereProjectile_DeletingDestructor  [inline]
//   [ ] 0x9a4580  CKDynBSphereProjectile_Destructor  [inline]
#include "k2000/scenegraph/CKDynBSphereProjectile.h"

// 0x000d7b80 CKDynBSphereProjectile_Load: CKDynamicBoundingSphere's Load, inlined.
int32_t CKDynBSphereProjectile::Load(IKFile* file, int32_t type) {
    CKDynamicBoundingSphere::Load(file, type);
    return 1;
}
