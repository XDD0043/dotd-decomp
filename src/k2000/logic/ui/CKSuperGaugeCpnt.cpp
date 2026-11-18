// CKSuperGaugeCpnt.cpp - reconstructed original translation unit 0x2503e8-0x250b38 (GAME_TOC1, main_toc1), 16 functions, 15 live.
// Primary class: CKSuperGaugeCpnt  key 0xa94c  category Logic  size 0x10  vtable 0xb21000
// Other owners: CKSuperGaugeCpntUpdater (1), CKGaugeCpnt (1), GetGaugeValue (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2503e8  CKSuperGaugeCpnt_Delete
//   [x] 0x250438  RegisterCKSuperGaugeCpntType  (the class registry: ClassTable.inc 0xa94c / Kp3Ported.inc (gen_kp3_stubs.py); port-rest R07)
//   [ ] 0x2504b0  _GLOBAL__I_2504b0
//   [x] 0x2504c0  CKSuperGaugeCpnt_TickChannels
//   [x] 0x250558  CKSuperGaugeCpnt_DeleteArray
//   [x] 0x2505f8  CKSuperGaugeCpnt_CreateArray
//   [ ] 0x250688  CKSuperGaugeCpnt_EvaluateChannels_maybe  [dead]
//   [x] 0x250720  CKSuperGaugeCpnt_Create
//   [x] 0x250758  CKSuperGaugeCpnt_RecursiveRegistration  (IKSerializable's empty default)
//   [x] 0x250760  CKSuperGaugeCpnt_PostLoad  (IKSerializable's default (1))
//   [x] 0x250768  CKSuperGaugeCpnt_Destroy  (IKBaseClass's empty default)
//   [x] 0x250770  CKSuperGaugeCpnt_Load
//   [ ] 0x250918  CKSuperGaugeCpnt_Save
//   [x] 0x250ac8  CKSuperGaugeCpntUpdater_Delete  (CKSuperGaugeCpntUpdater::Delete, DOTD_DECLARE_FACTORIES)
//   [x] 0x250b18  CKGaugeCpnt_GetDisplayedValue_maybe  (inline at its caller, CKS08InGameInterfaceCenter.cpp (the first updater's +0x08))
//   [x] 0x250b28  GetGaugeValue  (Spyro2008/logic/HudGaugeOps.h GetGaugeValue)
//
//   [ ] 0x9ba3c0  CKSuperGaugeCpnt_IsKindOfClass  [inline]
//   [x] 0x9ba3f0  CKSuperGaugeCpnt_GetClassType  [inline]
//   [x] 0x9ba3f8  CKSuperGaugeCpnt_GetClassID  [inline]
//   [ ] 0x9ba400  CKSuperGaugeCpnt_DeletingDestructor  [inline]
//   [ ] 0x9ba448  CKSuperGaugeCpnt_Destructor  [inline]
#include "k2000/logic/ui/CKSuperGaugeCpnt.h"

#include "k2000/components/CKSuperGaugeCpntUpdater.h"
#include "k2000/io/IKFile.h"

// 0x00250770 CKSuperGaugeCpnt_Load
int32_t CKSuperGaugeCpnt::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_apGauges[0]);
    IKFile_ReadRef(file, &m_apGauges[1]);
    IKFile_ReadRef(file, &m_apGauges[2]);
    return 1;
}

// 0x002504c0 CKSuperGaugeCpnt_TickChannels
void CKSuperGaugeCpnt::TickChannels(float dt, GaugeSample samples[3], CKSuperGaugeCpntUpdater* updater) const {
    m_apGauges[0]->UpdateDisplayedValue(dt, &samples[0], updater->m_apUpdaters[0]);
    m_apGauges[1]->UpdateDisplayedValue(dt, &samples[1], updater->m_apUpdaters[1]);
    m_apGauges[2]->UpdateDisplayedValue(dt, &samples[2], updater->m_apUpdaters[2]);
}
