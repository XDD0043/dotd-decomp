// CKGroundCpnt.h - the collision meshes (grounds) of an object (key 0x1206, vtable 0xb1bed8, size 0x10).
// Original unit: CKGroundCpnt.cpp (0x190e40-0x191530). No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class CKGroundCpnt : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x48)
    DOTD_DECLARE_FACTORIES(CKGroundCpnt)

    // 0x00191210 CKGroundCpnt_Create (inlined constructor; 0x190e90 Construct is a dead copy): null, 3, 0.
    CKGroundCpnt() {
        m_vGrounds.m_pBlock = nullptr;
        m_vGrounds.m_ui32NbElt = 3;
        m_vGrounds.m_ui32NbUsedElt = 0;
    }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00191268 CKGroundCpnt_Load

    // +0x04 ground references (CollisionMeshArray_GetAt 0x191090 / _SetActiveAt 0x190f58 index it).
    TVector<IKSerializable*, 3> m_vGrounds;
};
DOTD_ASSERT_SIZE(CKGroundCpnt, 0x10);
DOTD_ASSERT_OFFSET(CKGroundCpnt, m_vGrounds, 0x04);
