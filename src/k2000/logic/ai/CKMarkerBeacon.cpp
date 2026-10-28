// CKMarkerBeacon.cpp - reconstructed original translation unit 0x125e70-0x126268 (GAME_TOC1, main_toc1), 14 functions, 14 live.
// Primary class: CKMarkerBeacon  key 0x358c  category Logic  size 0x20  vtable 0xb19c80
// Other owners: CKSrvBonus (2), KBase201 (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x125e70  CKMarkerBeacon_Delete
//   [ ] 0x125ec0  CKMarkerBeacon_Destroy
//   [ ] 0x125ec8  CKMarkerBeacon_RecursiveRegistration
//   [ ] 0x125f28  CKMarkerBeacon_Save
//   [ ] 0x125f30  CKMarkerBeacon_PostLoad
//   [ ] 0x125f38  RegisterCKMarkerBeaconClass
//   [ ] 0x125fb0  _GLOBAL__I_125fb0
//   [x] 0x125fc0  CKMarkerBeacon_DeleteArray
//   [x] 0x126060  CKMarkerBeacon_Create
//   [x] 0x126098  CKMarkerBeacon_CreateArray
//   [x] 0x126128  CKMarkerBeacon_Load
//   [ ] 0x126248  KBase201_vf50
//   [ ] 0x126258  CKSrvBonus_BasePause_maybe
//   [ ] 0x126260  CKSrvBonus_BaseResume_maybe
//
//   [ ] 0x9a6f70  CKMarkerBeacon_GetClassType  [inline]
//   [ ] 0x9a6f78  CKMarkerBeacon_GetClassID  [inline]
//   [ ] 0x9a6f80  CKMarkerBeacon_Destructor  [inline]
//   [ ] 0x9a6f98  CKMarkerBeacon_IsKindOfClass  [inline]
//   [ ] 0x9a6fb8  CKMarkerBeacon_DeletingDestructor  [inline]
#include "k2000/logic/ai/CKMarkerBeacon.h"

#include "k2000/io/IKFile.h"

// 0x00126128 CKMarkerBeacon_Load: no type test; a 12-byte and a 16-byte read, each word then swapped.
int32_t CKMarkerBeacon::Load(IKFile* file, int32_t /*type*/) {
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_v3Position), 3);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_qOrientation), 4);
    return 1;
}
