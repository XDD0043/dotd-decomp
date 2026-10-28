// CKGrpPoolSquad.h - a pool of squads (key 0xb04, vtable 0xb21890, size 0x3c). Original unit:
// CKGrpPoolSquad.cpp. The base of CKGrpS08PoolEnemy. No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/groups/IKBaseGroup.h"
#include "k2000/util/TVector.h"

class CKGrpPoolSquad : public IKGroup<IKHook> {
public:
    DOTD_CLASS_KEY(kCategoryGroup, 0x2c)
    DOTD_DECLARE_FACTORIES(CKGrpPoolSquad)

    // 0x0026a790 CKGrpPoolSquad_Create (inlined constructor): the vector null, 5, 0.
    CKGrpPoolSquad() { m_vUnk30 = {nullptr, 5, 0}; }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0026a940 CKGrpPoolSquad_Load

    uint8_t m_unk2c;                         // +0x2c read last
    uint8_t m_pad2d[3];
    TVector<IKSerializable*, 5> m_vUnk30;   // +0x30 references (LVL010: CKS08EnemyCpnt, key 0x906)
};
DOTD_ASSERT_SIZE(CKGrpPoolSquad, 0x3c);
DOTD_ASSERT_OFFSET(CKGrpPoolSquad, m_unk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKGrpPoolSquad, m_vUnk30, 0x30);
