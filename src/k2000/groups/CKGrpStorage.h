// CKGrpStorage.h - a storage group (key 0x204, vtable 0xb1e058, size 0x2c). Original unit:
// CKGrpStorage.cpp. No XXL2 class of this name. The Load is GroupBasicLoad only.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/groups/IKBaseGroup.h"

class CKGrpStorage : public IKGroup<IKHook> {
public:
    DOTD_CLASS_KEY(kCategoryGroup, 0x8)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9adc58
        return key == 0x204 || key == 0x4 || key == 0x17e || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKGrpStorage)

    CKGrpStorage() {}  // 0x001dea20 CKGrpStorage_Create: the bases only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001deac0 CKGrpStorage_Load
    // vt+0x10 0x001deb10 CKGrpStorage_Destroy: no child groups (+0x18), no members (vt+0xb0's head).
    void Destroy() override { DestroyGroupLists(); }
};
DOTD_ASSERT_SIZE(CKGrpStorage, 0x2c);
