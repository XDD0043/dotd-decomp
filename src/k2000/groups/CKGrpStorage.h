// CKGrpStorage.h - a storage group (key 0x204, vtable 0xb1e058, size 0x2c). Original unit:
// CKGrpStorage.cpp. No XXL2 class of this name. The Load is GroupBasicLoad only.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/groups/IKBaseGroup.h"

class CKGrpStorage : public IKGroup<IKHook> {
public:
    DOTD_CLASS_KEY(kCategoryGroup, 0x8)
    DOTD_DECLARE_FACTORIES(CKGrpStorage)

    CKGrpStorage() {}  // 0x001dea20 CKGrpStorage_Create: the bases only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001deac0 CKGrpStorage_Load
};
DOTD_ASSERT_SIZE(CKGrpStorage, 0x2c);
