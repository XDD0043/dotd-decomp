// CKWaterWaveNodeFx.cpp - reconstructed original translation unit 0x56ff60-0x5710f0 (GAME_TOC2, main_toc2), 25 functions, 25 live.
// Primary class: CKWaterWaveNodeFx  key 0x3bcc  category Logic  size ?  vtable 0xb2dba0
// Other owners: CKWaterSplashFxData (9)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x56ff60  CKWaterWaveNodeFx_Delete
//   [ ] 0x56ffb0  CKWaterWaveNodeFx_Destroy
//   [ ] 0x56ffb8  CKWaterWaveNodeFx_RecursiveRegistration
//   [ ] 0x570060  CKWaterWaveNodeFx_PostLoad
//   [ ] 0x570068  CKWaterWaveNodeFx_SetPositionIfOwner_maybe
//   [ ] 0x5700c0  RegisterCKWaterWaveNodeFxClass
//   [ ] 0x570138  _GLOBAL__I_570138
//   [ ] 0x570148  CKWaterWaveNodeFx_Load
//   [ ] 0x570240  CKWaterWaveNodeFx_Save
//   [ ] 0x570268  CKWaterWaveNodeFx_DeleteArray
//   [ ] 0x570310  CKWaterWaveNodeFx_Create
//   [ ] 0x570368  CKWaterWaveNodeFx_Update
//   [ ] 0x570498  CKWaterWaveNodeFx_StopIfLinkedTo_maybe
//   [ ] 0x5704d0  CKWaterWaveNodeFx_Stop
//   [ ] 0x5704f0  CKWaterWaveNodeFx_Start
//   [ ] 0x570548  CKWaterWaveNodeFx_CreateArray
//   [x] 0x570600  CKWaterSplashFxData_GetNodeClassKey
//   [ ] 0x570608  CKWaterSplashFxData_EvalMesh1HeightScale_maybe
//   [ ] 0x5706a8  CKWaterSplashFxData_EvalMesh2HeightScale_maybe
//   [ ] 0x570748  CKWaterSplashFxData_EvalWidthScale_maybe
//   [ ] 0x5707e8  CKWaterSplashFxData_EvalAlpha_maybe
//   [ ] 0x570888  CKWaterSplashFxData_RecursiveRegistration
//   [ ] 0x5708b0  CKWaterSplashFxData_Destroy
//   [x] 0x570948  CKWaterSplashFxData_Load
//   [ ] 0x570d68  CKWaterSplashFxData_Save
//
//   [ ] 0x9ca9a8  CKWaterWaveNodeFx_IsKindOfClass  [inline]
//   [ ] 0x9ca9e0  CKWaterWaveNodeFx_GetClassType  [inline]
//   [ ] 0x9ca9e8  CKWaterWaveNodeFx_GetClassID  [inline]
//   [ ] 0x9ca9f0  CKWaterWaveNodeFx_GetFxData  [inline]
//   [ ] 0x9ca9f8  CKWaterWaveNodeFx_SetFxData  [inline]
//   [ ] 0x9caa00  CKWaterWaveNodeFx_DeletingDestruct  [inline]
//   [ ] 0x9caa48  CKWaterWaveNodeFx_Destruct  [inline]
//   [ ] 0x9caa68  CKWaterSplashFxData_IsKindOfClass  [inline]
//   [x] 0x9caaa0  CKWaterSplashFxData_GetClassType  [inline]
//   [x] 0x9caaa8  CKWaterSplashFxData_GetClassID  [inline]
//   [ ] 0x9caab0  CKWaterSplashFxData_Destructor  [inline]
//   [ ] 0x9caaf0  CKWaterSplashFxData_DeletingDestructor  [inline]
#include "k2000/logic/fx/CKWaterSplashFxData.h"

#include "k2000/io/IKFile.h"

namespace {
// new[] of count keys read in one block and byte-swapped word by word.
CKWaterSplashFxData::Key* ReadSplashKeys(IKFile* file, uint32_t count) {
    CKWaterSplashFxData::Key* keys = new CKWaterSplashFxData::Key[count];
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(keys), count * 2);
    return keys;
}
}  // namespace

// 0x00570948 CKWaterSplashFxData_Load
int32_t CKWaterSplashFxData::Load(IKFile* file, int32_t type) {
    IKFxData::Load(file, type);  // through TocBridge_IKFxData_Load
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_unk08);
    ReadU32LE(file, &m_unk1c);
    m_unk20 = ReadSplashKeys(file, m_unk1c);
    ReadU32LE(file, &m_unk14);
    m_unk18 = ReadSplashKeys(file, m_unk14);
    ReadU32LE(file, &m_unk0c);
    m_unk10 = ReadSplashKeys(file, m_unk0c);
    ReadU32LE(file, &m_unk24);
    m_unk28 = ReadSplashKeys(file, m_unk24);
    return 1;
}
