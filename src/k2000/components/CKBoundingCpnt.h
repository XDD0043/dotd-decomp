// CKBoundingCpnt.h - the collision volumes of an object (key 0x1386, vtable 0xb1be80, size 0x1c).
// Original unit: CKBoundingCpnt.cpp (0x190128-0x190d50). No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class CSGHotSpot;

class CKBoundingCpnt : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x4e)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9aa658
        return key == 0x1386 || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKBoundingCpnt)

    // 0x00190b20 CKBoundingCpnt_Create (inlined constructor; 0x190178 Construct is a dead copy): null, 3, 0.
    CKBoundingCpnt() {
        m_vVolumes.m_pBlock = nullptr;
        m_vVolumes.m_ui32NbElt = 3;
        m_vVolumes.m_ui32NbUsedElt = 0;
    }
    // 0x00190c40 CKBoundingCpnt_Destructor (0x190be0 deleting, 0x1902a8 the same code): the volume block freed, then
    // the component base (vtable only).
    ~CKBoundingCpnt() override;
    // vt+0x10 0x00190b90 CKBoundingCpnt_Destroy: the volume block freed, its length and block cleared.
    void Destroy() override;
    // vt+0x1c 0x00190b70 MessageProc, vt+0x24 0x00190b80 RecursiveRegistration, vt+0x30 0x00190b88 PostLoad: 1, the
    // defaults.

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00190c98 CKBoundingCpnt_Load
    // 0x001903c0 VolumeArray_SetDamage_maybe: every volume's +0x1c word (its damage, IKBoundingVolume::m_unk1c)
    // becomes `damage`, last volume first.
    void SetVolumesDamage(IKSerializable* damage);
    // 0x001903a8 VolumeArray_GetAt: volume `index` (unchecked).
    IKSerializable* GetVolumeAt(uint32_t index) const { return m_vVolumes.m_pBlock[index]; }
    // 0x00190408 VolumeArray_GetCount: the volumes in use.
    uint32_t GetVolumeCount() const { return m_vVolumes.m_ui32NbUsedElt; }
    // 0x001905e0 VolumeArray_DisableCollision / 0x00190680 VolumeArray_EnableCollision: every volume (last first) switched
    // off / on in the collision service (CKSrvCollision_DisableVolume 0x1920e8 / _EnableVolume 0x192090).
    void DisableCollision();
    void EnableCollision();
    // 0x00190860 VolumeArray_ReparentTo_maybe / 0x00190960 VolumeArray_ReparentToEngineRoot_maybe: every volume (last
    // first) taken off its parent (vt+0x78) and hung under `node` / the dynamic scene root (vt+0x70).
    void ReparentTo(IKSerializable* node);
    void ReparentToEngineRoot();
    // 0x00190260 VolumeArray_EnableVolumeAt / 0x00190740 VolumeArray_DisableVolumeAt: volume `index` (unchecked)
    // switched on / off in the collision service. No caller in the original.
    void EnableVolumeAt(uint32_t index);
    void DisableVolumeAt(uint32_t index);
    // 0x00190788 VolumeArray_AttachToHotSpot_maybe: every volume (last first) taken off its parent (vt+0x78) and hung
    // under the hot spot (CSGHotSpot_AttachVolume 0xce2b8). No caller in the original.
    void AttachToHotSpot(CSGHotSpot* hotSpot);

    // +0x04 volume references (VolumeArray_GetAt 0x1903a8 / _EnableVolumeAt 0x190260 index it).
    TVector<IKSerializable*, 3> m_vVolumes;
    // The contact observer (+0x10..+0x1b; not set by the constructor or the Load): the owner and a PS3 member-function
    // pointer {function word, this adjustment} that CollisionContactObserver_DispatchActiveContacts_maybe 0x190410 (the
    // crumbly multi-state's UpdateState 0x403ec8, C2.8) calls with (owner + adjustment, volume, contact). Natively the
    // function word is a plain function taking the adjusted owner.
    using ContactCallback = void (*)(void* owner, IKSerializable* volume, IKSerializable* contact);
    // 0x00190198 CollisionContactObserver_SetContactCallback_maybe: the owner (+0x10) and the callback (+0x14 / +0x18).
    void SetContactCallback(void* owner, ContactCallback callback, int32_t adjust) {
        m_pContactOwner = owner;
        m_pfnContact = callback;
        m_i32ContactAdjust = adjust;
    }

    // 0x00190410 CollisionContactObserver_DispatchActiveContacts_maybe: for every volume (last first), every collision of
    // its list (+0x28) that has a contact set (vt+0x08): the callback with (owner + adjustment, the other volume, the
    // collision).
    void DispatchActiveContacts();

    void* m_pContactOwner;            // +0x10
    ContactCallback m_pfnContact;     // +0x14 the member-function pointer's function word
    int32_t m_i32ContactAdjust;       // +0x18 its this adjustment
};
DOTD_ASSERT_SIZE(CKBoundingCpnt, 0x1c);
DOTD_ASSERT_OFFSET(CKBoundingCpnt, m_vVolumes, 0x04);
DOTD_ASSERT_OFFSET(CKBoundingCpnt, m_pContactOwner, 0x10);
DOTD_ASSERT_OFFSET(CKBoundingCpnt, m_pfnContact, 0x14);
DOTD_ASSERT_OFFSET(CKBoundingCpnt, m_i32ContactAdjust, 0x18);
