// CKCameraBeacon.cpp - reconstructed original translation unit 0x1512e0-0x152960 (GAME_TOC1, main_toc1), 23 functions, 23 live.
// Primary class: CKCameraBeacon  key 0x582  category Hook  size 0x54  vtable 0xb1a858
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x1512e0  RegisterCKCameraBeaconClass
//   [ ] 0x151358  _GLOBAL__I_151358
//   [x] 0x151368  CKCameraBeacon_QueueEnterLeaveSignals
//   [ ] 0x1513b0  CKCameraBeacon_RecursiveRegistration
//   [ ] 0x151470  CKCameraBeacon_Destroy
//   [x] 0x1514d0  CKCameraBeacon_Construct
//   [x] 0x151508  CKCameraBeacon_DeleteArray
//   [ ] 0x1515a8  CKCameraBeacon_BaseDestructor
//   [ ] 0x1515d8  CKCameraBeacon_DeletingDestructor
//   [ ] 0x151620  CKCameraBeacon_Destructor
//   [ ] 0x151650  CKCameraBeacon_Construct_2
//   [ ] 0x151688  CKCameraBeacon_IsActiveBeaconPredicate_maybe
//   [ ] 0x1516c8  CKCameraBeacon_GetInfo
//   [ ] 0x151740  CKCameraBeacon_vfC0
//   [x] 0x151c38  CKCameraBeacon_CreateArray
//   [x] 0x151ce8  CKCameraBeacon_Create
//   [x] 0x151d40  CKCameraBeacon_Load
//   [~] 0x152040  CKCameraBeacon_vfC4  (STUB(C2.8))
//   [ ] 0x1522e8  CKCameraBeacon_Save
//   [ ] 0x152628  CKCameraBeacon_MessageProc
//   [ ] 0x152800  CKCameraBeacon_SetGameState
//   [ ] 0x152858  CKCameraBeacon_PostLoad
//   [ ] 0x152920  CKCameraBeacon_SetDefaultState
//
//   [ ] 0x9a7ad0  CKCameraBeacon_IsKindOfClass  [inline]
//   [ ] 0x9a7b28  CKCameraBeacon_GetClassType  [inline]
//   [ ] 0x9a7b30  CKCameraBeacon_GetClassID  [inline]
//   [ ] 0x9a7b38  CKCameraBeacon_IsNodePriority22Greater_maybe  [inline]
#include "k2000/hooks/CKCameraBeacon.h"

#include <cstring>

#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"

// 0x00151d40 CKCameraBeacon_Load
int32_t CKCameraBeacon::Load(IKFile* file, int32_t type) {
    KBase4C2::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU8(file, &m_unk21);
    ReadU8(file, &m_unk22);
    IKFile_ReadRef(file, &m_unk24);
    uint32_t w[3];
    ReadU32LEWords(file, w, 3);  // one 12-byte read, each word swapped
    std::memcpy(&m_unk28, w, sizeof(w));
    ReadF32LE(file, &m_unk34);
    ReadU8(file, &m_unk23);
    ReadF32LE(file, &m_unk3C);
    m_unk44.Load(file, K_LEVEL_PLATEFORMS);
    m_unk4C.Load(file, K_LEVEL_PLATEFORMS);
    ReadF32LE(file, &m_unk38);
    return 1;
}

// 0x00151368 CKCameraBeacon_QueueEnterLeaveSignals (the beacon is passed on as the signals' sender, r4; the native
// QueueTriggerSignals takes the starter only).
void CKCameraBeacon_FireEnterLeaveSignals(CKCameraBeacon* beacon, int32_t enter) {
    QueueTriggerSignals(enter != 0 ? &beacon->m_unk44 : &beacon->m_unk4C);
}

// 0x00152040 CKCameraBeacon_vfC4. STUB(C2.8): not ported (see the header); never in view.
uint8_t CKCameraBeacon::IsInView(const void* /*frustum*/) {
    DOTD_STUB_ONCE("CKCameraBeacon_vfC4 0x152040: the camera beacon's view test (C2.8)");
    return 0;
}
