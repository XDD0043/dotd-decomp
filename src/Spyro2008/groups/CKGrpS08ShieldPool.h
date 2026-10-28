// CKGrpS08ShieldPool.h - the pool of enemy shields (key 0xd04, vtable 0xb21798, size 0x2c). Original unit:
// CKGrpS08ShieldPool.cpp. The Load is GroupBasicLoad only.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/groups/IKBaseGroup.h"

class CKGrpS08ShieldPool : public IKGroup<IKHook> {
public:
    DOTD_CLASS_KEY(kCategoryGroup, 0x34)
    DOTD_DECLARE_FACTORIES(CKGrpS08ShieldPool)

    CKGrpS08ShieldPool() {}  // 0x0026a360 CKGrpS08ShieldPool_Create: the bases only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0026a530 CKGrpS08ShieldPool_Load
};
DOTD_ASSERT_SIZE(CKGrpS08ShieldPool, 0x2c);
