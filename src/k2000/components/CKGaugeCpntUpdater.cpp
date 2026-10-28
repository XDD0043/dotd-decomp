// CKGaugeCpntUpdater.cpp - reconstructed original translation unit 0x24b2e0-0x24bc70 (GAME_TOC1, main_toc1), 15 functions, 13 live.
// Primary class: CKGaugeCpntUpdater  key 0x1486  category Component  size 0x20  vtable 0xb20d98
// Other owners: GaugeSample (2), SuperGaugeRecord (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x24b2e0  RegisterCKGaugeCpntUpdaterClass
//   [ ] 0x24b358  _GLOBAL__I_24b358
//   [ ] 0x24b368  CKGaugeCpntUpdater_Update_maybe
//   [x] 0x24b438  CKGaugeCpntUpdater_DeleteArray
//   [x] 0x24b4d8  CKGaugeCpntUpdater_Create
//   [ ] 0x24b510  GaugeSample_ApplyToElement2dPtr_maybe  [dead]
//   [ ] 0x24b600  GaugeSample_ApplyToElement2d_maybe
//   [x] 0x24ba10  CKGaugeCpntUpdater_CreateArray
//   [ ] 0x24baa0  SuperGaugeRecord_Init_maybe  [dead]
//   [ ] 0x24bac8  CKGaugeCpntUpdater_Save
//   [x] 0x24bad0  CKGaugeCpntUpdater_Load
//   [x] 0x24bb60  CKGaugeCpntUpdater_PostLoad
//   [ ] 0x24bb90  CKGaugeCpntUpdater_RecursiveRegistration
//   [ ] 0x24bb98  CKGaugeCpntUpdater_Destroy
//   [ ] 0x24bba0  CKGaugeCpntUpdater_EvaluateSample_maybe
//
//   [ ] 0x9b9f18  CKGaugeCpntUpdater_IsKindOfClass  [inline]
//   [x] 0x9b9f40  CKGaugeCpntUpdater_GetClassType  [inline]
//   [x] 0x9b9f48  CKGaugeCpntUpdater_GetClassID  [inline]
//   [ ] 0x9b9f50  CKGaugeCpntUpdater_DeletingDestructor  [inline]
//   [ ] 0x9b9f98  CKGaugeCpntUpdater_Destructor  [inline]
#include "k2000/components/CKGaugeCpntUpdater.h"

#include "k2000/io/IKFile.h"

// 0x0024bb60 CKGaugeCpntUpdater_PostLoad: only for type 0 (the level load).
int32_t CKGaugeCpntUpdater::PostLoad(int32_t type) {
    if (type != 0) return 1;
    m_unk1c = 0;
    m_unk18 = 0;
    m_unk08 = 0.0f;
    m_unk0c = 0.0f;
    m_unk10 = 0.0f;
    m_unk14 = 0;
    return 1;
}

// 0x0024bad0 CKGaugeCpntUpdater_Load
int32_t CKGaugeCpntUpdater::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pGauge);
    return 1;
}
