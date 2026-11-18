// CKGrpS08ShieldPool.h - the pool of enemy shields (key 0xd04, vtable 0xb21798, size 0x2c). Original unit:
// CKGrpS08ShieldPool.cpp. The Load is GroupBasicLoad only.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/groups/IKBaseGroup.h"

class CKGrpS08ShieldPool : public IKGroup<IKHook> {
public:
    DOTD_CLASS_KEY(kCategoryGroup, 0x34)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9bb950
        return key == 0xd04 || key == 0x17e || key == 0x4 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKGrpS08ShieldPool)

    CKGrpS08ShieldPool() {}  // 0x0026a360 CKGrpS08ShieldPool_Create: the bases only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0026a530 CKGrpS08ShieldPool_Load
    // vt+0x30 0x0026a210 CKGrpS08ShieldPool_PostLoad: IKLife_PostLoad 0x19f68, then 1.
    int32_t PostLoad(int32_t type) override {
        PostLoadLife(type);
        return 1;
    }
    // vt+0x24 0x0026a4a8 CKGrpS08ShieldPool_RecursiveRegistration: IKGroup's (0x12a68), then with type 0 the group registered with the
    // saving manager.
    void RecursiveRegistration(int32_t type) override;
    // vt+0x10 0x0026a580 CKGrpS08ShieldPool_Destroy: no child groups (+0x18), no members (vt+0xb0's head).
    void Destroy() override { DestroyGroupLists(); }
    // vt+0xb8 0x0026a208 CKGrpS08ShieldPool_vfB8 returns 99: IKBaseGroup models no slot there and no ported code calls it.
};
DOTD_ASSERT_SIZE(CKGrpS08ShieldPool, 0x2c);
