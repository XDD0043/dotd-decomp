// CKMeshPopFxData.cpp - the FX data classes' registry factories (Create / CreateArray: new / new[] plus the inlined
// constructor). Each is the class's DOTD_DECLARE_FACTORIES (its header); no code of its own here.
//
// Reconstructed original translation unit: 0x1adc70-0x1ae9a0 (GAME_TOC1, main_toc1), 28 functions, 28 live.
// Primary class: CKMeshPopFxData  key 0xa28c  category Logic  size 0x64  vtable 0xb1d360
// Other owners: CKFireBallFxData (2), CKExplosionFxData (2), CKDistortionFxData (2), CKLensFlareFxData (2), CKHedgeHopTrailFxData (2), CKFilterFxData (2), CKLightningObjectFxData (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1adc70  CKMeshPopFxData_CreateArray  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x1add10  CKFireBallFxData_CreateArray  (the registry factory: DOTD_DECLARE_FACTORIES (CKFireBallFxData.h); port-rest R07)
//   [x] 0x1addb0  CKExplosionFxData_CreateArray  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x1ade78  CKDistortionFxData_Create  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x1adec0  CKLensFlareFxData_Create  (the registry factory: DOTD_DECLARE_FACTORIES (CKLensFlareFxData.h); port-final F04)
//   [x] 0x1adf08  CKHedgeHopTrailFxData_Create  (the registry factory: DOTD_DECLARE_FACTORIES (CKHedgeHopTrailFxData.h); port-final F04)
//   [x] 0x1adf50  CKFilterFxData_Create  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x1adf98  CKLightningObjectFxData_Create  (the registry factory: DOTD_DECLARE_FACTORIES (CKLightningObjectFxData.h); port-final F04)
//   [x] 0x1adfe0  CKQuadFxData_Create  (the registry factory: DOTD_DECLARE_FACTORIES (CKQuadFxData.h); port-rest R07)
//   [x] 0x1ae028  CKElectricArcFxData_Create  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x1ae070  CKFlashFxData_Create  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x1ae0b8  CKSparkFxData_CreateArray  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x1ae160  CKSparkFxData_Create  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x1ae1a8  CreateParticleEffectFxDataArray  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x1ae250  CreateParticleEffectFxData  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x1ae298  CKShockWaveFxData_CreateArray  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x1ae340  CKShockWaveFxData_Create  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x1ae388  CKMeshPopFxData_Create  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x1ae3d0  CKFlashFxData_CreateArray  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x1ae470  CKFireBallFxData_Create  (the registry factory: DOTD_DECLARE_FACTORIES (CKFireBallFxData.h); port-rest R07)
//   [x] 0x1ae4b8  CKLensFlareFxData_CreateArray  (the registry factory: DOTD_DECLARE_FACTORIES (CKLensFlareFxData.h); port-final F04)
//   [x] 0x1ae558  CKDistortionFxData_CreateArray  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x1ae600  CKElectricArcFxData_CreateArray  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x1ae6a8  CKQuadFxData_CreateArray  (the registry factory: DOTD_DECLARE_FACTORIES (CKQuadFxData.h); port-rest R07)
//   [x] 0x1ae750  CKLightningObjectFxData_CreateArray  (the registry factory: DOTD_DECLARE_FACTORIES (CKLightningObjectFxData.h); port-final F04)
//   [x] 0x1ae7f8  CKFilterFxData_CreateArray  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x1ae8a0  CKHedgeHopTrailFxData_CreateArray  (the registry factory: DOTD_DECLARE_FACTORIES (CKHedgeHopTrailFxData.h); port-final F04)
//   [x] 0x1ae948  CKExplosionFxData_Create  (the registry factory: DOTD_DECLARE_FACTORIES)
