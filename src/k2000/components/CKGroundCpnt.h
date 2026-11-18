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
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9aa690
        return key == 0x1206 || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKGroundCpnt)

    // 0x00191210 CKGroundCpnt_Create (inlined constructor; 0x190e90 Construct is a dead copy): null, 3, 0.
    CKGroundCpnt() {
        m_vGrounds.m_pBlock = nullptr;
        m_vGrounds.m_ui32NbElt = 3;
        m_vGrounds.m_ui32NbUsedElt = 0;
    }
    // 0x001914d8 CKGroundCpnt_Destructor (0x191478 deleting, 0x190f98 the same code): the ground block freed, then the
    // component base (vtable only).
    ~CKGroundCpnt() override;
    // vt+0x10 0x00191428 CKGroundCpnt_Destroy: the ground block freed, its length and block cleared.
    void Destroy() override;
    // vt+0x1c 0x00191410 MessageProc, vt+0x24 0x00191418 RecursiveRegistration, vt+0x30 0x00191420 PostLoad: 1, the
    // defaults.

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00191268 CKGroundCpnt_Load

    // 0x001910a8 CollisionMeshArray_SetActive_maybe (not virtual): every ground's ICollisionMesh_SetActive.
    void SetActive(uint8_t active);
    // 0x00190f58 CollisionMeshArray_SetActiveAt: ground `index` (unchecked) through ICollisionMesh_SetActive. No caller
    // in the original.
    void SetActiveAt(uint32_t index, uint8_t active);
    // 0x00191090 CollisionMeshArray_GetAt: ground `index` (unchecked). CKCrumblyZoneState::UpdateNavBlocking reads the
    // vector inline.
    IKSerializable* GetGroundAt(uint32_t index) const { return m_vGrounds.m_pBlock[index]; }
    // 0x00191148 CollisionMeshArray_GetCount_maybe: the count's low byte (lbz +0x0f).
    uint8_t GetGroundCount() const { return static_cast<uint8_t>(m_vGrounds.m_ui32NbUsedElt); }

    // +0x04 ground references (CollisionMeshArray_GetAt 0x191090 / _SetActiveAt 0x190f58 index it).
    TVector<IKSerializable*, 3> m_vGrounds;
};
DOTD_ASSERT_SIZE(CKGroundCpnt, 0x10);
DOTD_ASSERT_OFFSET(CKGroundCpnt, m_vGrounds, 0x04);
