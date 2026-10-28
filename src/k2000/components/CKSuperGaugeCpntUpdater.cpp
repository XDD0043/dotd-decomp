// CKSuperGaugeCpntUpdater.cpp - reconstructed original translation unit 0x250b38-0x251628 (GAME_TOC1, main_toc1), 21 functions, 16 live.
// Primary class: CKSuperGaugeCpntUpdater  key 0x14c6  category Component  size 0x14  vtable 0xb21058
// Other owners: CKSuperGaugeCpnt (4), GaugeSamples (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x250b38  CKSuperGaugeCpntUpdater_GetCpnt_maybe  [dead]
//   [ ] 0x250b40  RegisterCKSuperGaugeCpntUpdaterClass
//   [ ] 0x250bb8  _GLOBAL__I_250bb8
//   [ ] 0x250bc8  GaugeSamples_ApplyToElements2d_maybe
//   [ ] 0x250c88  GaugeSamples_ApplyToElements2dPtr_maybe  [dead]
//   [ ] 0x250d30  CKSuperGaugeCpntUpdater_ResetRecords_maybe  [dead]
//   [x] 0x250d80  CKSuperGaugeCpnt_SetFullFlag_maybe
//   [x] 0x250da8  CKSuperGaugeCpnt_SetMarkerValue_maybe
//   [x] 0x250dd8  CKSuperGaugeCpnt_SetValue
//   [x] 0x250e38  CKSuperGaugeCpntUpdater_DeleteArray
//   [x] 0x250ee0  CKSuperGaugeCpntUpdater_Create
//   [ ] 0x250f18  CKSuperGaugeCpnt_GetMarkerValue_maybe
//   [x] 0x250f28  CKSuperGaugeCpntUpdater_CreateArray
//   [ ] 0x250fc0  CKSuperGaugeCpntUpdater_Save
//   [ ] 0x250fc8  CKSuperGaugeCpntUpdater_RecursiveRegistration
//   [ ] 0x250fd0  CKSuperGaugeCpntUpdater_Destroy
//   [ ] 0x250fd8  CKSuperGaugeCpntUpdater_Tick
//   [ ] 0x251198  CKSuperGaugeCpntUpdater_Evaluate_maybe  [dead]
//   [x] 0x251358  CKSuperGaugeCpntUpdater_Load
//   [ ] 0x251580  CKSuperGaugeCpntUpdater_PostLoad
//   [ ] 0x2515d8  CKSuperGaugeCpntUpdater_SetCpntAndReset_maybe  [dead]
//
//   [ ] 0x9ba478  CKSuperGaugeCpntUpdater_IsKindOfClass  [inline]
//   [x] 0x9ba4a0  CKSuperGaugeCpntUpdater_GetClassType  [inline]
//   [x] 0x9ba4a8  CKSuperGaugeCpntUpdater_GetClassID  [inline]
//   [ ] 0x9ba4b0  CKSuperGaugeCpntUpdater_DeletingDestructor  [inline]
//   [ ] 0x9ba4f8  CKSuperGaugeCpntUpdater_Destructor  [inline]
#include "k2000/components/CKSuperGaugeCpntUpdater.h"

#include "k2000/io/IKFile.h"
#include "k2000/components/CKGaugeCpntUpdater.h"

// 0x00251358 CKSuperGaugeCpntUpdater_Load
int32_t CKSuperGaugeCpntUpdater::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pSuperGauge);
    IKFile_ReadRef(file, &m_apUpdaters[0]);
    IKFile_ReadRef(file, &m_apUpdaters[1]);
    IKFile_ReadRef(file, &m_apUpdaters[2]);
    return 1;
}

// 0x00250d80 CKSuperGaugeCpnt_SetFullFlag_maybe
void CKSuperGaugeCpntUpdater::SetFullFlag(uint32_t value) { SuperGaugeRecord_SetFullFlag(m_apUpdaters[0], value); }

// 0x00250da8 CKSuperGaugeCpnt_SetMarkerValue_maybe
void CKSuperGaugeCpntUpdater::SetMarkerValue(float value) { SetGaugeValue(m_apUpdaters[2], value, 1); }

// 0x00250dd8 CKSuperGaugeCpnt_SetValue
void CKSuperGaugeCpntUpdater::SetValue(float value, int32_t resetAux) {
    SetGaugeValue(m_apUpdaters[0], value, resetAux);
    SetGaugeValue(m_apUpdaters[1], value, resetAux);
}
