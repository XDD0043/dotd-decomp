// CKGroupRoot.h - the root of a level's group tree (key 0x44, vtable 0xb13990, size 0x2c). Original
// unit: CKGroupRoot.cpp (0x228b8-0x22cd0). XXL2: K/KCore/Main/CKGroupRoot.h (no members of its own).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/groups/IKBaseGroup.h"

class CKGroupRoot : public IKGroup<IKHook> {
public:
    DOTD_CLASS_KEY(kCategoryGroup, 0x1)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x992f30
        return key == 0x44 || key == 0x17e || key == 0x4 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKGroupRoot)

    CKGroupRoot() {}  // inlined in 0x00022a58 CKGroupRoot_Create (the base parts only)
    ~CKGroupRoot() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00022ba0 CKGroupRoot_Load
    // vt+0x10 0x00022c70 CKGroupRoot_Destroy: no child groups (+0x18), no members (vt+0xb0's head).
    void Destroy() override { DestroyGroupLists(); }
    // vt+0x24 0x00022bc8 CKGroupRoot_RecursiveRegistration: registered with the saving manager whatever the type (no
    // 4..7 test), then IKGroup_LevelReset 0x12a68 (the children and the members).
    void RecursiveRegistration(int32_t type) override;
    // vt+0x30 0x00022908 CKGroupRoot_PostLoad: IKLife_PostLoad 0x19f68, then 1.
    int32_t PostLoad(int32_t type) override {
        PostLoadLife(type);
        return 1;
    }
};
DOTD_ASSERT_SIZE(CKGroupRoot, 0x2c);
DOTD_ASSERT_OFFSET(CKGroupRoot, m_lHooks, 0x28);
