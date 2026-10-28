// CKGrpBonus.h - the group of the bonus pools (key 0x1704, size 0x2c; XXL2 CKGrpBonus: IKGroup<IKHkBonus>,
// no members). Original unit: CKGrpBonus.cpp (0x5b0ce0-0x5b1348, TOC2). The Load is GroupBasicLoad.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/groups/IKBaseGroup.h"

class CKGrpBonus : public IKGroup<IKHook> {
public:
    DOTD_CLASS_KEY(kCategoryGroup, 0x5c)
    DOTD_DECLARE_FACTORIES(CKGrpBonus)

    CKGrpBonus() {}  // 0x005b0d80 CKGrpBonus_Create: the bases only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005b1298 CKGrpBonus_Load
};
DOTD_ASSERT_SIZE(CKGrpBonus, 0x2c);
