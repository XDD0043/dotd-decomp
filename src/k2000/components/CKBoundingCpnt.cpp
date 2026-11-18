// CKBoundingCpnt.cpp - reconstructed original translation unit 0x190128-0x190e40 (GAME_TOC1, main_toc1), 30 functions, 27 live.
// Primary class: CKBoundingCpnt  key 0x1386  category Component  size 0x1c  vtable 0xb1be80
// Other owners: VolumeArray (11), CollisionContactObserver (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x190128  CKBoundingCpnt_Delete
//   [ ] 0x190178  CKBoundingCpnt_Construct  [dead]
//   [x] 0x190198  CollisionContactObserver_SetContactCallback_maybe  (inline in the header)
//   [ ] 0x1901b8  CKBoundingCpnt_Construct_2  [dead]
//   [ ] 0x1901d8  RegisterCKBoundingCpntClass
//   [ ] 0x190250  _GLOBAL__I_190250
//   [x] 0x190260  VolumeArray_EnableVolumeAt  (EnableVolumeAt; no caller in the original either)
//   [x] 0x1902a8  CKBoundingCpnt_Destructor_2  (the same code as 0x190c40 CKBoundingCpnt_Destructor)
//   [x] 0x190300  CKBoundingCpnt_DeleteArray
//   [x] 0x1903a8  VolumeArray_GetAt
//   [x] 0x1903c0  VolumeArray_SetDamage_maybe
//   [x] 0x190408  VolumeArray_GetCount
//   [x] 0x190410  CollisionContactObserver_DispatchActiveContacts_maybe
//   [x] 0x1905e0  VolumeArray_DisableCollision
//   [x] 0x190680  VolumeArray_EnableCollision
//   [ ] 0x190720  VolumeArray_IsVolumeEnabledAt_maybe  [dead]
//   [x] 0x190740  VolumeArray_DisableVolumeAt  (DisableVolumeAt; no caller in the original either)
//   [x] 0x190788  VolumeArray_AttachToHotSpot_maybe  (AttachToHotSpot; no caller in the original either)
//   [x] 0x190860  VolumeArray_ReparentTo_maybe
//   [x] 0x190960  VolumeArray_ReparentToEngineRoot_maybe
//   [x] 0x190a58  CKBoundingCpnt_CreateArray
//   [x] 0x190b20  CKBoundingCpnt_Create
//   [x] 0x190b70  CKBoundingCpnt_MessageProc  (IKBaseClass's default (1))
//   [ ] 0x190b78  CKBoundingCpnt_Save
//   [x] 0x190b80  CKBoundingCpnt_RecursiveRegistration  (returns 1, registers nothing: the default)
//   [x] 0x190b88  CKBoundingCpnt_PostLoad  (returns 1: the default)
//   [x] 0x190b90  CKBoundingCpnt_Destroy
//   [x] 0x190be0  CKBoundingCpnt_DeletingDestructor  (the deleting form of the destructor)
//   [x] 0x190c40  CKBoundingCpnt_Destructor
//   [x] 0x190c98  CKBoundingCpnt_Load
//
//   [ ] 0x9aa658  CKBoundingCpnt_IsKindOfClass  [inline]
//   [x] 0x9aa680  CKBoundingCpnt_GetClassType  [inline]
//   [x] 0x9aa688  CKBoundingCpnt_GetClassID  [inline]
#include "k2000/components/CKBoundingCpnt.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/misc/Engine.h"

#include "k2000/components/TVectorLoad.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/memory/Mem.h"
#include "k2000/scenegraph/IKBoundingVolume.h"

// 0x00190c40 CKBoundingCpnt_Destructor (0x190be0 CKBoundingCpnt_DeletingDestructor, 0x1902a8 CKBoundingCpnt_Destructor_2)
CKBoundingCpnt::~CKBoundingCpnt() {
    if (m_vVolumes.m_pBlock != nullptr) Mem_FreeAligned16(m_vVolumes.m_pBlock);
}

// 0x00190b90 CKBoundingCpnt_Destroy
void CKBoundingCpnt::Destroy() {
    if (m_vVolumes.m_pBlock != nullptr) Mem_FreeAligned16(m_vVolumes.m_pBlock);
    m_vVolumes.m_ui32NbUsedElt = 0;
    m_vVolumes.m_pBlock = nullptr;
}

// 0x00190260 VolumeArray_EnableVolumeAt
void CKBoundingCpnt::EnableVolumeAt(uint32_t index) {
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)
        ->EnableVolume(static_cast<IKBoundingVolume*>(m_vVolumes.m_pBlock[index]));  // 0x00192090
}

// 0x00190740 VolumeArray_DisableVolumeAt
void CKBoundingCpnt::DisableVolumeAt(uint32_t index) {
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)
        ->DisableVolume(static_cast<IKBoundingVolume*>(m_vVolumes.m_pBlock[index]));  // 0x001920e8
}

// 0x00190788 VolumeArray_AttachToHotSpot_maybe
void CKBoundingCpnt::AttachToHotSpot(CSGHotSpot* hotSpot) {
    const uint32_t count = m_vVolumes.m_ui32NbUsedElt;
    for (uint32_t i = count; i != 0; --i) {
        IKBoundingVolume* volume = static_cast<IKBoundingVolume*>(m_vVolumes.m_pBlock[i - 1]);
        if (volume->m_pParent != nullptr) volume->m_pParent->RemoveChild(volume);  // vt+0x78
        hotSpot->AttachVolume(static_cast<IKBoundingVolume*>(m_vVolumes.m_pBlock[i - 1]));  // 0x000ce2b8
    }
}

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

// 0x001905e0 VolumeArray_DisableCollision
void CKBoundingCpnt::DisableCollision() {
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    for (uint32_t i = m_vVolumes.m_ui32NbUsedElt; i != 0; --i) {
        collision->DisableVolume(static_cast<IKBoundingVolume*>(m_vVolumes.m_pBlock[i - 1]));  // 0x001920e8
    }
}

// 0x00190680 VolumeArray_EnableCollision
void CKBoundingCpnt::EnableCollision() {
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    for (uint32_t i = m_vVolumes.m_ui32NbUsedElt; i != 0; --i) {
        collision->EnableVolume(static_cast<IKBoundingVolume*>(m_vVolumes.m_pBlock[i - 1]));  // 0x00192090
    }
}

// 0x00190860 VolumeArray_ReparentTo_maybe
void CKBoundingCpnt::ReparentTo(IKSerializable* node) {
    for (uint32_t i = m_vVolumes.m_ui32NbUsedElt; i != 0; --i) {
        IKBoundingVolume* volume = static_cast<IKBoundingVolume*>(m_vVolumes.m_pBlock[i - 1]);
        if (volume->m_pParent != nullptr) volume->m_pParent->RemoveChild(volume);  // vt+0x78
        static_cast<CSGBranch*>(node)->AddChild(static_cast<IKBoundingVolume*>(m_vVolumes.m_pBlock[i - 1]));  // vt+0x70
    }
}

// 0x00190960 VolumeArray_ReparentToEngineRoot_maybe
void CKBoundingCpnt::ReparentToEngineRoot() {
    for (uint32_t i = m_vVolumes.m_ui32NbUsedElt; i != 0; --i) {
        IKBoundingVolume* volume = static_cast<IKBoundingVolume*>(m_vVolumes.m_pBlock[i - 1]);
        if (volume->m_pParent != nullptr) volume->m_pParent->RemoveChild(volume);  // vt+0x78
        static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot)
            ->AddChild(static_cast<IKBoundingVolume*>(m_vVolumes.m_pBlock[i - 1]));  // vt+0x70
    }
}

// 0x00190410 CollisionContactObserver_DispatchActiveContacts_maybe (the clock argument is not used)
void CKBoundingCpnt::DispatchActiveContacts() {
    for (uint32_t i = m_vVolumes.m_ui32NbUsedElt; i != 0; --i) {
        for (ICollision* collision = static_cast<ICollision*>(static_cast<IKBoundingVolume*>(m_vVolumes.m_pBlock[i - 1])->m_CollisionResList);
             collision != nullptr; collision = collision->m_pNext) {
            if (collision->HasContactSet() == 0) continue;  // vt+0x08
            IKSerializable* volume = m_vVolumes.m_pBlock[i - 1];
            IKSerializable* other = volume == collision->GetBoundingVolume1() ? collision->GetBoundingVolume2()   // vt+0x00 / +0x04
                                                                              : collision->GetBoundingVolume1();
            // The PS3 member-function pointer: an odd function word is a virtual slot of the adjusted owner (not used
            // here: the crumbly states register a plain function).
            m_pfnContact(static_cast<uint8_t*>(m_pContactOwner) + m_i32ContactAdjust, other,
                         reinterpret_cast<IKSerializable*>(collision));
        }
    }
}
