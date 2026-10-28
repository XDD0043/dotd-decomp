// CKS08InGameInterfaceBoss.cpp - reconstructed original translation unit 0x533848-0x5349a8 (GAME_TOC1, main_toc1), 28 functions, 23 live.
// Primary class: CKS08InGameInterfaceBoss  key 0xa3cc  category Logic  size 0x100  vtable 0xb2bc08
// Other owners: CKS08InGameInterfaceCenter (4)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x533848  CKS08InGameInterfaceBoss_Delete
//   [ ] 0x533898  CKS08InGameInterfaceBoss_Construct  [dead]
//   [ ] 0x533940  CKS08InGameInterfaceBoss_RefreshGaugeMarker_maybe
//   [ ] 0x533978  CKS08InGameInterfaceBoss_RefreshGaugeValue_maybe
//   [ ] 0x5339b0  CKS08InGameInterfaceBoss_ResetWidgets_maybe
//   [ ] 0x5339e8  CKS08InGameInterfaceBoss_Save
//   [ ] 0x533a10  CKS08InGameInterfaceBoss_RecursiveRegistration
//   [ ] 0x533a38  CKS08InGameInterfaceBoss_Destroy
//   [x] 0x533a60  CKS08InGameInterfaceBoss_DeleteArray
//   [ ] 0x533b00  RegisterCKS08InGameInterfaceBossType
//   [ ] 0x533b88  _GLOBAL__D_533b88
//   [ ] 0x533b98  _GLOBAL__I_533b98
//   [ ] 0x533ba8  CKS08InGameInterfaceBoss_Construct_2  [dead]
//   [x] 0x533c50  CKS08InGameInterfaceBoss_CreateArray
//   [x] 0x533d90  CKS08InGameInterfaceBoss_Create
//   [ ] 0x533e78  CKS08InGameInterfaceBoss_RefreshGauge_maybe
//   [ ] 0x533ed8  CKS08InGameInterfaceBoss_Update_maybe
//   [x] 0x5341f0  CKS08InGameInterfaceBoss_Load
//   [ ] 0x534398  CKS08InGameInterfaceBoss_Destructor_2
//   [ ] 0x5344d0  CKS08InGameInterfaceBoss_DeletingDestructor
//   [ ] 0x534608  CKS08InGameInterfaceBoss_Destructor
//   [ ] 0x534740  CKS08InGameInterfaceCenter_Delete
//   [ ] 0x534790  CKS08InGameInterfaceCenter_vf8C
//   [ ] 0x5347d0  CKS08InGameInterfaceCenter_vf90
//   [ ] 0x534810  CKS08InGameInterfaceCenter_RefreshTextElementsB8C0_maybe
//   [ ] 0x534958  FUN_00534958  [dead]
//   [ ] 0x534970  FUN_00534970  [dead]
//   [ ] 0x534988  FUN_00534988  [dead]
//
//   [x] 0x9c9240  CKS08InGameInterfaceBoss_IsKindOfClass  [inline]
//   [x] 0x9c9280  CKS08InGameInterfaceBoss_GetClassType  [inline]
//   [x] 0x9c9288  CKS08InGameInterfaceBoss_GetClassID  [inline]
//   [x] 0x9c9290  CKS08InGameInterfaceBoss_vfB8  [inline]
//   [x] 0x9c9298  CKS08InGameInterfaceBoss_vfE0  [inline]
//   [x] 0x9c92a0  CKS08InGameInterfaceBoss_vfBC  [inline]
//   [x] 0x9c92a8  CKS08InGameInterfaceBoss_vfC0  [inline]
//   [x] 0x9c92b8  CKS08InGameInterfaceBoss_vfC4  [inline]
//   [x] 0x9c92c0  CKS08InGameInterfaceBoss_vfC8  [inline]
//   [x] 0x9c92d0  CKS08InGameInterfaceBoss_vfCC  [inline]
//   [x] 0x9c92e0  CKS08InGameInterfaceBoss_GetWidgetSlotCount  [inline]
//   [x] 0x9c92e8  CKS08InGameInterfaceBoss_GetWidgetSlots  [inline]
//   [x] 0x9c92f8  CKS08InGameInterfaceBoss_vf84  [inline]
#include "Spyro2008/logic/CKS08InGameInterfaceBoss.h"

#include "k2000/io/IKFile.h"

// 0x005341f0 CKS08InGameInterfaceBoss_Load: no type test of its own, so its fields are read whatever the type.
int32_t CKS08InGameInterfaceBoss::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    ReadF32LE(file, &m_fUnkec);
    m_fUnkfc = 0x1.4p+3f;  // 10.0 (lfs TOC1+0x7988)
    m_fUnkf4 = 0x1.4p+2f;  // 5.0 (TOC1+0x7980)
    m_fUnkf8 = 0x1p+3f;    // 8.0 (TOC1+0x7984)
    IKFile_ReadRef(file, &m_pGauge);
    IKFile_ReadRef(file, &m_pGaugeUpdater);
    return 1;
}
