// CKBoundingCpnt.h - the collision volumes of an object (key 0x1386, vtable 0xb1be80, size 0x1c).
// Original unit: CKBoundingCpnt.cpp (0x190128-0x190d50). No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class CKBoundingCpnt : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x4e)
    DOTD_DECLARE_FACTORIES(CKBoundingCpnt)

    // 0x00190b20 CKBoundingCpnt_Create (inlined constructor; 0x190178 Construct is a dead copy): null, 3, 0.
    CKBoundingCpnt() {
        m_vVolumes.m_pBlock = nullptr;
        m_vVolumes.m_ui32NbElt = 3;
        m_vVolumes.m_ui32NbUsedElt = 0;
    }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00190c98 CKBoundingCpnt_Load
    // 0x001903c0 VolumeArray_SetDamage_maybe: every volume's +0x1c word (its damage, IKBoundingVolume::m_unk1c)
    // becomes `damage`, last volume first.
    void SetVolumesDamage(IKSerializable* damage);

    // +0x04 volume references (VolumeArray_GetAt 0x1903a8 / _EnableVolumeAt 0x190260 index it).
    TVector<IKSerializable*, 3> m_vVolumes;
    uint32_t m_unk10;  // +0x10..+0x1b runtime (CollisionContactObserver_*_maybe); not set by the
    uint32_t m_unk14;  //   constructor or the Load
    uint32_t m_unk18;
};
DOTD_ASSERT_SIZE(CKBoundingCpnt, 0x1c);
DOTD_ASSERT_OFFSET(CKBoundingCpnt, m_vVolumes, 0x04);
