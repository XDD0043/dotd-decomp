// CKHkMoveCpnt.cpp - reconstructed original translation unit 0x2bc640-0x2c5e00 (GAME_TOC1, main_toc1), 20 functions, 17 live.
// Primary class: CKHkMoveCpnt  key 0x300c  category Logic  size 0xac  vtable 0xb22630
// Other owners: Steering (4), NavSteering (3), NavSector (1), NavSectors (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2bc640  CKHkMoveCpnt_Delete
//   [ ] 0x2bc690  CKHkMoveCpnt_Destroy
//   [ ] 0x2bc698  FUN_002bc698  [dead]
//   [ ] 0x2bc738  RegisterCKHkMoveCpntClass
//   [ ] 0x2bc7b0  _GLOBAL__I_2bc7b0
//   [ ] 0x2bc7c0  NavSector_ContainsWalkablePoint_maybe
//   [x] 0x2bc920  CKHkMoveCpnt_DeleteArray
//   [x] 0x2bc9c0  CKHkMoveCpnt_Create
//   [x] 0x2bca10  CKHkMoveCpnt_CreateArray
//   [ ] 0x2bcac0  NavSectors_IsPointInAllowedSector_2_maybe  [dead]
//   [x] 0x2bcc98  CKHkMoveCpnt_Load
//   [ ] 0x2bd590  CKHkMoveCpnt_Save
//   [ ] 0x2bdcf8  Steering_StepSpecialTraversal_maybe
//   [ ] 0x2be438  FUN_002be438  [dead]
//   [ ] 0x2bea90  NavSteering_TestCellEdgeByNeighborFlags_maybe
//   [ ] 0x2bf0d0  NavSteering_ComputeWallAvoidance3D_maybe
//   [ ] 0x2c1180  Steering_ComputeDesiredVelocity3D_maybe
//   [ ] 0x2c2390  NavSteering_ComputeWallAvoidance_maybe
//   [ ] 0x2c4430  Steering_ComputeDesiredVelocityNoTurnSmoothing_maybe
//   [ ] 0x2c4d38  Steering_ComputeDesiredVelocity_maybe
//
//   [ ] 0x990b48  CKHkMoveCpnt_RecursiveRegistration  [inline]
//   [ ] 0x990b50  KStub_Return1_990b50  [inline]
//   [ ] 0x990b58  KStub_Return1_990b58  [inline]
//   [ ] 0x990b60  KStub_Return1_990b60  [inline]
//   [ ] 0x990b68  KStub_Return1_990b68  [inline]
//   [ ] 0x990b70  KStub_Nop_990b70  [inline]
//   [ ] 0x990b78  KStub_Return1_990b78  [inline]
//   [ ] 0x990b80  KStub_Return1_990b80  [inline]
//   [ ] 0x990b88  KStub_Return0_990b88  [inline]
//   [ ] 0x990b90  IKUpdatable_IsKindOf  [inline]
//   [ ] 0x990bb0  KStub_Nop_990bb0  [inline]
//   [ ] 0x990bb8  KStub_Return1_990bb8  [inline]
//   [ ] 0x990bc0  KStub_Nop_990bc0  [inline]
//   [ ] 0x990bc8  KStub_Nop_990bc8  [inline]
//   [ ] 0x990bd0  KStub_Nop_990bd0  [inline]
//   [ ] 0x990bd8  KStub_Return1_990bd8  [inline]
//   [ ] 0x990be0  KStub_Return1_990be0  [inline]
//   [ ] 0x990be8  KStub_Nop_990be8  [inline]
//   [ ] 0x990bf0  KStub_Nop_990bf0  [inline]
//   [ ] 0x990bf8  KStub_Nop_990bf8  [inline]
//   [ ] 0x990c00  KStub_Nop_990c00  [inline]
//   [ ] 0x990c08  KStub_Nop_990c08  [inline]
//   [ ] 0x990c10  KStub_Return1_990c10  [inline]
//   [ ] 0x990c18  KStub_Nop_990c18  [inline]
//   [ ] 0x9bcfc8  CKHkMoveCpnt_GetClassType  [inline]
//   [ ] 0x9bcfd0  CKHkMoveCpnt_GetClassID  [inline]
//   [ ] 0x9bcfd8  CKHkMoveCpnt_IsKindOfClass  [inline]
//   [ ] 0x9bcff8  CKHkMoveCpnt_DeletingDestructor  [inline]
//   [ ] 0x9bd038  CKHkMoveCpnt_Destructor  [inline]
#include "k2000/logic/CKHkMoveCpnt.h"

#include "k2000/io/IKFile.h"

// 0x002bcc98 CKHkMoveCpnt_Load
int32_t CKHkMoveCpnt::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        for (float& value : m_afParams) ReadF32LE(file, &value);
        m_fAnimScaleRatio = 0x1p+0f;  // TOC 0x18f8
        m_eMvtAnim = 0;
    }
    return 1;
}
