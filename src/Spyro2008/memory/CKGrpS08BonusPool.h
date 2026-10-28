// CKGrpS08BonusPool.h - Spyro's bonus pool (key 0x7c4, size 0x70). Original unit: CKGrpS08BonusPool.cpp
// (0x5af6a8-0x5b0c58, TOC2). A CKGrpBonusPool with one more reference.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/memory/CKGrpBonusPool.h"

class CKGrpS08BonusPool : public CKGrpBonusPool {
public:
    DOTD_CLASS_KEY(kCategoryGroup, 0x1f)
    DOTD_DECLARE_FACTORIES(CKGrpS08BonusPool)

    CKGrpS08BonusPool() {}  // 0x005b0640 CKGrpS08BonusPool_Create: the bases only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005b08b0 CKGrpS08BonusPool_Load
    // vt+0x280 0x005b0bc8 CKGrpBonus_ResetRuntime (C2.2): asks every child group for its vt+0xec value.
    void ResetRuntime();

    IKSerializable* m_pUnk6c;  // +0x6c reference
};
DOTD_ASSERT_SIZE(CKGrpS08BonusPool, 0x70);
DOTD_ASSERT_OFFSET(CKGrpS08BonusPool, m_pUnk6c, 0x6c);
