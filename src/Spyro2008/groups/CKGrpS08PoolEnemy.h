// CKGrpS08PoolEnemy.h - Spyro's enemy pool (key 0xb44, vtable 0xb21988, size 0x48). Original unit:
// CKGrpS08PoolEnemy.cpp. A CKGrpPoolSquad with a list of squad pools (Ghidra ppSquadPools).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/groups/CKGrpPoolSquad.h"
#include "k2000/util/TVector.h"

class CKGrpS08PoolEnemy : public CKGrpPoolSquad {
public:
    DOTD_CLASS_KEY(kCategoryGroup, 0x2d)
    DOTD_DECLARE_FACTORIES(CKGrpS08PoolEnemy)

    // 0x0026af00 CKGrpS08PoolEnemy_Create (inlined constructor): the base, then the list null, 1, 0.
    CKGrpS08PoolEnemy() { m_vSquadPools = {nullptr, 1, 0}; }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0026b168 CKGrpS08PoolEnemy_Load

    TVector<IKSerializable*, 1> m_vSquadPools;  // +0x3c Ghidra ppSquadPools / dwSquadPoolsCapacity / dwSquadPoolCount
};
DOTD_ASSERT_SIZE(CKGrpS08PoolEnemy, 0x48);
DOTD_ASSERT_OFFSET(CKGrpS08PoolEnemy, m_vSquadPools, 0x3c);
