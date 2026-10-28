// CKSurfaceParticlesRendable.cpp - reconstructed original translation unit 0xc2bf8-0xc4048 (GAME_TOC1, main_toc1), 27 functions, 20 live.
// Primary class: CKSurfaceParticlesRendable  key 0xe0d  category Graphical  size 0x24  vtable 0xb17b58
// Other owners: CMaterialEffectData (2), DrawSurfaceParticleGeometry (1), SurfaceParticles (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xc2bf8  CKSurfaceParticlesRendable_Delete
//   [ ] 0xc2c48  CKSurfaceParticlesRendable_vf58
//   [ ] 0xc2ca0  RegisterCKSurfaceParticlesRendableClass
//   [ ] 0xc2d18  _GLOBAL__I_c2d18
//   [ ] 0xc2d28  CKSurfaceParticlesRendable_RecursiveRegistration
//   [ ] 0xc2d50  CKSurfaceParticlesRendable_Destroy
//   [x] 0xc2d78  CKSurfaceParticlesRendable_DeleteArray
//   [x] 0xc2e20  CKSurfaceParticlesRendable_Create
//   [ ] 0xc2e78  DrawSurfaceParticleGeometry
//   [x] 0xc3398  CKSurfaceParticlesRendable_CreateArray
//   [ ] 0xc3450  CKSurfaceParticlesRendable_PostLoad
//   [x] 0xc3478  CKSurfaceParticlesRendable_Load
//   [ ] 0xc3570  CKSurfaceParticlesRendable_Save
//   [ ] 0xc3678  KStub_Nop_c3678
//   [ ] 0xc3680  CMaterialEffectData_LevelReset_maybe
//   [ ] 0xc3728  KStub_Nop_c3728
//   [ ] 0xc3730  CKSurfaceParticlesRendable_GetFadeInAlpha_maybe
//   [ ] 0xc3788  CKSurfaceParticlesRendable_GetFadeOutAlpha_maybe
//   [ ] 0xc37e0  SurfaceParticles_ComputeDistanceFade_maybe
//   [ ] 0xc3878  KStub_Nop_c3878  [dead]
//   [ ] 0xc3880  CKSurfaceParticlesRendable_SetFadeStart_maybe  [dead]
//   [ ] 0xc38a8  CKSurfaceParticlesRendable_SetFadeEnd_maybe  [dead]
//   [ ] 0xc38d0  FUN_000c38d0  [dead]
//   [ ] 0xc3a70  FUN_000c3a70  [dead]
//   [ ] 0xc3b28  CMaterialEffectData_Load_maybe
//   [ ] 0xc3d70  FUN_000c3d70  [dead]
//   [ ] 0xc3e38  FUN_000c3e38  [dead]
//
//   [ ] 0x9a1bc0  CKSurfaceParticlesRendable_GetClassType  [inline]
//   [ ] 0x9a1bc8  CKSurfaceParticlesRendable_GetClassID  [inline]
//   [ ] 0x9a1bd0  CKSurfaceParticlesRendable_IsKindOfClass  [inline]
//   [ ] 0x9a1bf8  CKSurfaceParticlesRendable_DeletingDestructor  [inline]
//   [ ] 0x9a1c40  CKSurfaceParticlesRendable_Destructor  [inline]
#include "k2000/graphical/fx/CKSurfaceParticlesRendable.h"

#include "k2000/io/IKFile.h"

// 0x000c3478 CKSurfaceParticlesRendable_Load
int32_t CKSurfaceParticlesRendable::Load(IKFile* file, int32_t type) {
    IRendableObject::Load(file, type);  // 0xa7258
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pOwner);
        ReadRaw(file, m_unk20, 4);  // not swapped
    }
    return 1;
}
