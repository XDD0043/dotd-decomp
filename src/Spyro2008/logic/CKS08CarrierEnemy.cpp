// CKS08CarrierEnemy.cpp - reconstructed original translation unit 0x4c7730-0x4c98d8 (GAME_TOC1, main_toc1), 39 functions, 35 live.
// Primary class: CKS08CarrierEnemy  key 0x958c  category Logic  size 0xa8  vtable 0xb297e0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4c7730  CKS08CarrierEnemy_Delete
//   [ ] 0x4c7780  CKS08CarrierEnemy_vf58
//   [ ] 0x4c7878  CKS08CarrierEnemy_vf5C
//   [ ] 0x4c78b0  CKS08CarrierEnemy_vf64
//   [ ] 0x4c78b8  CKS08CarrierEnemy_State0_Carry_maybe
//   [ ] 0x4c79d0  CKS08CarrierEnemy_vf78
//   [ ] 0x4c79f8  KStub_Return0_4c79f8  [dead]
//   [ ] 0x4c7a00  CKS08CarrierEnemy_State2_PickUp_maybe
//   [ ] 0x4c7c48  CKS08CarrierEnemy_IsCarrying_maybe
//   [ ] 0x4c7c58  CKS08CarrierEnemy_ClaimTransportableInReach_maybe
//   [ ] 0x4c7ef0  CKS08CarrierEnemy_ClaimTransportableInReach_Key0xC2_maybe  [dead]
//   [ ] 0x4c7f10  CKS08CarrierEnemy_Save
//   [ ] 0x4c7f38  CKS08CarrierEnemy_RecursiveRegistration
//   [ ] 0x4c7f60  CKS08CarrierEnemy_Destroy
//   [x] 0x4c7fa8  CKS08CarrierEnemy_DeleteArray
//   [x] 0x4c8048  CKS08CarrierEnemy_Construct  [dead]
//   [ ] 0x4c80a0  CKS08CarrierEnemy_CaptureCarryPose_maybe
//   [ ] 0x4c8228  RegisterCKS08CarrierEnemyClass
//   [ ] 0x4c82b0  _GLOBAL__D_4c82b0
//   [ ] 0x4c82c0  _GLOBAL__I_4c82c0
//   [ ] 0x4c82d0  CKS08CarrierEnemy_DropCarriedObject_maybe
//   [ ] 0x4c8450  CKS08CarrierEnemy_StartCarrying_maybe
//   [ ] 0x4c84d0  CKS08CarrierEnemy_Construct_2  [dead]
//   [ ] 0x4c8528  CKS08CarrierEnemy_DestructBody
//   [ ] 0x4c8558  CKS08CarrierEnemy_DeletingDestructor
//   [ ] 0x4c85a0  CKS08CarrierEnemy_Destructor
//   [ ] 0x4c85d0  CKS08CarrierEnemy_vf70
//   [ ] 0x4c8750  CKS08CarrierEnemy_MessageProc
//   [ ] 0x4c8758  CKS08CarrierEnemy_PostLoad
//   [ ] 0x4c8760  CKS08CarrierEnemy_LerpCarriedObjectToHotSpot_maybe
//   [ ] 0x4c89f0  CKS08CarrierEnemy_StopCarrying_maybe
//   [ ] 0x4c8c30  CKS08CarrierEnemy_IsTransportableInReach_maybe
//   [x] 0x4c8da0  CKS08CarrierEnemy_CreateArray
//   [x] 0x4c8e70  CKS08CarrierEnemy_Create
//   [ ] 0x4c8ed8  CKS08CarrierEnemy_IsInGrabRangeAndAngle_maybe
//   [x] 0x4c90f0  CKS08CarrierEnemy_Load
//   [ ] 0x4c93e8  CKS08CarrierEnemy_UpdateStateMachine_maybe
//   [ ] 0x4c95e8  CKS08CarrierEnemy_ResetStateMachine_maybe
//   [ ] 0x4c9720  CKS08CarrierEnemy_Reset_maybe
//
//   [ ] 0x9c5380  CKS08CarrierEnemy_vf60  [inline]
//   [ ] 0x9c5388  CKS08CarrierEnemy_vf80  [inline]
//   [ ] 0x9c5a00  CKS08CarrierEnemy_IsKindOfClass  [inline]
//   [ ] 0x9c5a38  CKS08CarrierEnemy_GetClassType  [inline]
//   [ ] 0x9c5a40  CKS08CarrierEnemy_GetClassID  [inline]
//   [ ] 0x9c5a48  CKS08CarrierEnemy_vf7C  [inline]
#include "Spyro2008/logic/CKS08CarrierEnemy.h"

#include "k2000/io/IKFile.h"

// 0x004c90f0 CKS08CarrierEnemy_Load: the base's Load, then (level data only) two floats, a counted word
// array, two references and a float.
int32_t CKS08CarrierEnemy::Load(IKFile* file, int32_t type) {
    KBase910C::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_unk2c);
    ReadF32LE(file, &m_unk28);
    ReadU32LE(file, &m_ui32NbUnk1c);
    m_aui32Unk1c = new uint32_t[m_ui32NbUnk1c];
    for (uint32_t i = 0; i < m_ui32NbUnk1c; ++i) ReadU32LE(file, &m_aui32Unk1c[i]);
    IKFile_ReadRef(file, &m_pHotSpot);
    IKFile_ReadRef(file, &m_pEnemy);
    ReadF32LE(file, &m_unk34);
    return 1;
}
