// CKS08MenuSelectSlot.cpp - reconstructed original translation unit 0x5625a0-0x564680 (GAME_TOC2, main_toc2), 23 functions, 20 live.
// Primary class: CKS08MenuSelectSlot  key 0x824c  category Logic  size ?  vtable 0xb2d2b8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5625a0  CKS08MenuSelectSlot_Delete
//   [ ] 0x5625f0  CKS08MenuSelectSlot_Construct  [dead]
//   [ ] 0x562698  CKS08MenuSelectSlot_QueueNextStateAfterSave_maybe
//   [ ] 0x562778  CKS08MenuSelectSlot_ResetSelectionState_maybe  [dead]
//   [ ] 0x562798  CKS08MenuSelectSlot_UpdateSlotButtonStates_maybe
//   [ ] 0x562be8  CKS08MenuSelectSlot_RefreshSlotInfo_maybe
//   [ ] 0x563720  CKS08MenuSelectSlot_OnSaveGameDone_maybe
//   [ ] 0x5637f0  CKS08MenuSelectSlot_RecursiveRegistration
//   [ ] 0x563860  CKS08MenuSelectSlot_Destroy
//   [x] 0x563888  CKS08MenuSelectSlot_DeleteArray
//   [ ] 0x563930  RegisterCKS08MenuSelectSlotClass
//   [ ] 0x5639b8  _GLOBAL__D_5639b8
//   [ ] 0x5639c8  _GLOBAL__I_5639c8
//   [ ] 0x5639d8  CKS08MenuSelectSlot_vfE8
//   [ ] 0x563a50  CKS08MenuSelectSlot_Construct_2  [dead]
//   [x] 0x563af8  CKS08MenuSelectSlot_CreateArray
//   [x] 0x563c40  CKS08MenuSelectSlot_Create
//   [x] 0x563d28  CKS08MenuSelectSlot_Load
//   [ ] 0x563e08  CKS08MenuSelectSlot_OnMenuState_maybe
//   [ ] 0x5641f8  CKS08MenuSelectSlot_Save
//   [ ] 0x5642d8  CKS08MenuSelectSlot_Destructor
//   [ ] 0x564410  CKS08MenuSelectSlot_Destructor_2
//   [ ] 0x564548  CKS08MenuSelectSlot_DeletingDestructor
//
//   [x] 0x9ca2d8  CKS08MenuSelectSlot_IsKindOfClass  [inline]
//   [x] 0x9ca318  CKS08MenuSelectSlot_GetClassType  [inline]
//   [x] 0x9ca320  CKS08MenuSelectSlot_GetClassID  [inline]
//   [x] 0x9ca328  CKS08MenuSelectSlot_vfB8  [inline]
//   [x] 0x9ca330  CKS08MenuSelectSlot_vfE0  [inline]
//   [x] 0x9ca338  CKS08MenuSelectSlot_GetWidgetSlotCount  [inline]
//   [x] 0x9ca340  CKS08MenuSelectSlot_GetWidgetSlots  [inline]
//   [x] 0x9ca350  CKS08MenuSelectSlot_vfC4  [inline]
//   [x] 0x9ca358  CKS08MenuSelectSlot_vfC8  [inline]
//   [x] 0x9ca368  CKS08MenuSelectSlot_vfCC  [inline]
//   [x] 0x9ca378  CKS08MenuSelectSlot_vfBC  [inline]
//   [x] 0x9ca380  CKS08MenuSelectSlot_vfC0  [inline]
//   [ ] 0x9ca390  CKS08MenuSelectSlot_vfF0  [inline]
//   [ ] 0x9ca398  CKS08MenuSelectSlot_vfF4  [inline]
//   [ ] 0x9ca3a0  CKS08MenuSelectSlot_vfE4  [inline]
#include "Spyro2008/logic/ui/CKS08MenuSelectSlot.h"

#include "k2000/io/IKFile.h"

// 0x00563d28 CKS08MenuSelectSlot_Load: no type test of its own, so its fields are read whatever the type.
int32_t CKS08MenuSelectSlot::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    IKFile_ReadRef(file, &m_pText);
    return 1;
}
