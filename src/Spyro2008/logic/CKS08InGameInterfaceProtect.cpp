// CKS08InGameInterfaceProtect.cpp - reconstructed original translation unit 0x53c360-0x53d330 (GAME_TOC1, main_toc1), 21 functions, 19 live.
// Primary class: CKS08InGameInterfaceProtect  key 0xa38c  category Logic  size 0x100  vtable 0xb2bf20
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x53c360  CKS08InGameInterfaceProtect_Delete
//   [ ] 0x53c3b0  CKS08InGameInterfaceProtect_Construct  [dead]
//   [ ] 0x53c458  CKS08InGameInterfaceProtect_SyncGaugeMarker_maybe
//   [ ] 0x53c4b8  CKS08InGameInterfaceProtect_SyncGaugeValue_maybe
//   [ ] 0x53c520  CKS08InGameInterfaceProtect_ResetWidgets_maybe
//   [ ] 0x53c558  CKS08InGameInterfaceProtect_Save
//   [ ] 0x53c580  CKS08InGameInterfaceProtect_RecursiveRegistration
//   [ ] 0x53c5a8  CKS08InGameInterfaceProtect_Destroy
//   [x] 0x53c5d0  CKS08InGameInterfaceProtect_DeleteArray
//   [ ] 0x53c670  RegisterCKS08InGameInterfaceProtectClass
//   [ ] 0x53c6f8  _GLOBAL__D_53c6f8
//   [ ] 0x53c708  _GLOBAL__I_53c708
//   [ ] 0x53c718  CKS08InGameInterfaceProtect_Construct_2  [dead]
//   [x] 0x53c7c0  CKS08InGameInterfaceProtect_CreateArray
//   [x] 0x53c900  CKS08InGameInterfaceProtect_Create
//   [x] 0x53c9e8  CKS08InGameInterfaceProtect_Load
//   [ ] 0x53cb90  CKS08InGameInterfaceProtect_UpdateGauge_maybe
//   [ ] 0x53cc28  CKS08InGameInterfaceProtect_OnMenuState_maybe
//   [ ] 0x53cf88  CKS08InGameInterfaceProtect_Destructor_2
//   [ ] 0x53d0c0  CKS08InGameInterfaceProtect_DeletingDestructor
//   [ ] 0x53d1f8  CKS08InGameInterfaceProtect_Destructor
//
//   [x] 0x9c9490  CKS08InGameInterfaceProtect_IsKindOfClass  [inline]
//   [x] 0x9c94d0  CKS08InGameInterfaceProtect_GetClassType  [inline]
//   [x] 0x9c94d8  CKS08InGameInterfaceProtect_GetClassID  [inline]
//   [x] 0x9c94e0  CKS08InGameInterfaceProtect_vfB8  [inline]
//   [x] 0x9c94e8  CKS08InGameInterfaceProtect_vfE0  [inline]
//   [x] 0x9c94f0  CKS08InGameInterfaceProtect_vfBC  [inline]
//   [x] 0x9c94f8  CKS08InGameInterfaceProtect_vfC0  [inline]
//   [x] 0x9c9508  CKS08InGameInterfaceProtect_vfC4  [inline]
//   [x] 0x9c9510  CKS08InGameInterfaceProtect_vfC8  [inline]
//   [x] 0x9c9520  CKS08InGameInterfaceProtect_vfCC  [inline]
//   [x] 0x9c9530  CKS08InGameInterfaceProtect_GetWidgetSlotCount  [inline]
//   [x] 0x9c9538  CKS08InGameInterfaceProtect_GetWidgetSlots  [inline]
//   [x] 0x9c9548  CKS08InGameInterfaceProtect_vf84  [inline]
#include "Spyro2008/logic/CKS08InGameInterfaceProtect.h"

#include "k2000/io/IKFile.h"

// 0x0053c9e8 CKS08InGameInterfaceProtect_Load: no type test of its own, so its fields are read whatever the type.
int32_t CKS08InGameInterfaceProtect::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    ReadF32LE(file, &m_fUnkec);
    m_fUnkfc = 0x1.4p+3f;  // 10.0 (lfs TOC1+0x7b20)
    m_fUnkf4 = 0x1.4p+2f;  // 5.0 (TOC1+0x7b18)
    m_fUnkf8 = 0x1p+3f;    // 8.0 (TOC1+0x7b1c)
    IKFile_ReadRef(file, &m_pGauge);
    IKFile_ReadRef(file, &m_pGaugeUpdater);
    return 1;
}
