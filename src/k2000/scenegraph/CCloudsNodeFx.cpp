// CCloudsNodeFx.cpp - reconstructed original translation unit 0xd8078-0xda260 (GAME_TOC1, main_toc1), 21 functions, 19 live.
// Primary class: CCloudsNodeFx  key 0x84b  category SceneNode  size 0x6678  vtable 0xb18910
// Other owners: CFogBoxNodeFx (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xd8078  CCloudsNodeFx_Delete
//   [ ] 0xd80c8  CCloudsNodeFx_ReduceCloudCount_maybe  [dead]
//   [ ] 0xd80f0  RegisterCCloudsNodeFxClass
//   [ ] 0xd8168  _GLOBAL__I_d8168
//   [ ] 0xd8178  CCloudsNodeFx_InitCloud_maybe
//   [ ] 0xd8478  CCloudsNodeFx_PostLoad
//   [ ] 0xd84a0  CCloudsNodeFx_Save
//   [ ] 0xd84c8  CCloudsNodeFx_RecursiveRegistration
//   [ ] 0xd84f0  CCloudsNodeFx_Destroy
//   [x] 0xd8518  CCloudsNodeFx_DeleteArray
//   [x] 0xd85b8  CCloudsNodeFx_CreateArray
//   [ ] 0xd8688  CCloudsNodeFx_BeginParamTransition_maybe
//   [ ] 0xd8728  CCloudsNodeFx_SetTargetParams_maybe
//   [ ] 0xd8818  CCloudsNodeFx_ApplyPendingParams_maybe
//   [x] 0xd8968  CCloudsNodeFx_Create
//   [x] 0xd89c8  CCloudsNodeFx_Load
//   [ ] 0xd8d90  CCloudsNodeFx_WritePTankVertices_maybe
//   [ ] 0xd94e0  CCloudsNodeFx_UpdateClouds_maybe
//   [ ] 0xda088  CCloudsNodeFx_vf58
//   [ ] 0xda1d0  CFogBoxNodeFx_Delete
//   [ ] 0xda220  FUN_000da220  [dead]
//
//   [ ] 0x9a4ca0  CCloudsNodeFx_IsKindOfClass  [inline]
//   [ ] 0x9a4d00  CCloudsNodeFx_GetClassType  [inline]
//   [ ] 0x9a4d08  CCloudsNodeFx_GetClassID  [inline]
//   [ ] 0x9a4d10  CCloudsNodeFx_Destructor  [inline]
//   [ ] 0x9a4d50  CCloudsNodeFx_DeletingDestructor  [inline]
#include "k2000/scenegraph/CCloudsNodeFx.h"

#include "k2000/io/IKFile.h"

// 0x000d89c8 CCloudsNodeFx_Load
int32_t CCloudsNodeFx::Load(IKFile* file, int32_t type) {
    INodeFx::Load(file, type);  // 0xeccd8
    m_ba8Infos = 0;
    m_pCloudTank = nullptr;
    ReadF32LE(file, &m_fFarLimit);
    ReadF32LE(file, &m_fShowSpeed);
    SCloudsWeatherPreset& preset = m_asWeather[1];
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&preset.m_fMedHeight), 8);           // one 0x20 read
    ReadU32LEWords(file, &preset.m_ui32ExternNbClusters, 3);                               // one 0xc read
    ReadRaw(file, preset.m_acColor, 8);                                                    // not swapped
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pCloudTank);
    m_asWeather[0] = preset;  // the original copies word by word, first and last presets interleaved
    m_asWeather[2] = preset;
    m_fSpeedInterpolation = 0.0f;
    m_fStateInterpolation = 1.0f;  // TOC -0x50e4
    return 1;
}
