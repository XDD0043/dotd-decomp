// CKBoundingCpnt.cpp - reconstructed original translation unit 0x190128-0x190e40 (GAME_TOC1, main_toc1), 30 functions, 27 live.
// Primary class: CKBoundingCpnt  key 0x1386  category Component  size 0x1c  vtable 0xb1be80
// Other owners: VolumeArray (11), CollisionContactObserver (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x190128  CKBoundingCpnt_Delete
//   [ ] 0x190178  CKBoundingCpnt_Construct  [dead]
//   [ ] 0x190198  CollisionContactObserver_SetContactCallback_maybe
//   [ ] 0x1901b8  CKBoundingCpnt_Construct_2  [dead]
//   [ ] 0x1901d8  RegisterCKBoundingCpntClass
//   [ ] 0x190250  _GLOBAL__I_190250
//   [ ] 0x190260  VolumeArray_EnableVolumeAt
//   [ ] 0x1902a8  CKBoundingCpnt_Destructor_2
//   [x] 0x190300  CKBoundingCpnt_DeleteArray
//   [ ] 0x1903a8  VolumeArray_GetAt
//   [x] 0x1903c0  VolumeArray_SetDamage_maybe
//   [ ] 0x190408  VolumeArray_GetCount
//   [ ] 0x190410  CollisionContactObserver_DispatchActiveContacts_maybe
//   [ ] 0x1905e0  VolumeArray_DisableCollision
//   [ ] 0x190680  VolumeArray_EnableCollision
//   [ ] 0x190720  VolumeArray_IsVolumeEnabledAt_maybe  [dead]
//   [ ] 0x190740  VolumeArray_DisableVolumeAt
//   [ ] 0x190788  VolumeArray_AttachToHotSpot_maybe
//   [ ] 0x190860  VolumeArray_ReparentTo_maybe
//   [ ] 0x190960  VolumeArray_ReparentToEngineRoot_maybe
//   [x] 0x190a58  CKBoundingCpnt_CreateArray
//   [x] 0x190b20  CKBoundingCpnt_Create
//   [ ] 0x190b70  CKBoundingCpnt_MessageProc
//   [ ] 0x190b78  CKBoundingCpnt_Save
//   [ ] 0x190b80  CKBoundingCpnt_RecursiveRegistration
//   [ ] 0x190b88  CKBoundingCpnt_PostLoad
//   [ ] 0x190b90  CKBoundingCpnt_Destroy
//   [ ] 0x190be0  CKBoundingCpnt_DeletingDestructor
//   [ ] 0x190c40  CKBoundingCpnt_Destructor
//   [x] 0x190c98  CKBoundingCpnt_Load
//
//   [ ] 0x9aa658  CKBoundingCpnt_IsKindOfClass  [inline]
//   [x] 0x9aa680  CKBoundingCpnt_GetClassType  [inline]
//   [x] 0x9aa688  CKBoundingCpnt_GetClassID  [inline]
#include "k2000/components/CKBoundingCpnt.h"

#include "k2000/components/TVectorLoad.h"
#include "k2000/scenegraph/IKBoundingVolume.h"

// 0x00190c98 CKBoundingCpnt_Load
int32_t CKBoundingCpnt::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) TVector_LoadRefs(m_vVolumes, file);
    return 1;
}

// 0x001903c0 VolumeArray_SetDamage_maybe
void CKBoundingCpnt::SetVolumesDamage(IKSerializable* damage) {
    for (uint32_t i = m_vVolumes.m_ui32NbUsedElt; i != 0; --i) {
        static_cast<IKBoundingVolume*>(m_vVolumes.m_pBlock[i - 1])->m_unk1c = damage;
    }
}
