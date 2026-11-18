// CKCommonBaseGroup.h - a plain group (key 0x18c4, size 0x2c; XXL2 CKCommonBaseGroup: IKGroup<IKHook>, no
// members). Original unit: CKCommonBaseGroup.cpp (0x5a7d20-0x5a8260, TOC2). The Load is GroupBasicLoad.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/groups/IKBaseGroup.h"

class CKCommonBaseGroup : public IKGroup<IKHook> {
public:
    DOTD_CLASS_KEY(kCategoryGroup, 0x63)
    DOTD_DECLARE_FACTORIES(CKCommonBaseGroup)

    CKCommonBaseGroup() {}  // 0x005a8080 CKCommonBaseGroup_Create: the bases only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005a8120 CKCommonBaseGroup_Load
    // vt+0x30 0x005a7e60 CKCommonBaseGroup_PostLoad: IKLife_PostLoad 0x19f68, then 1.
    int32_t PostLoad(int32_t type) override {
        PostLoadLife(type);
        return 1;
    }
    // vt+0x10 0x005a8170 CKCommonBaseGroup_Destroy: no child groups (+0x18), no members (vt+0xb0's head).
    void Destroy() override {
        m_lChilds = nullptr;
        *GetMemberListHead() = nullptr;
    }
    // vt+0x24 0x005a80f8: IKGroup's RecursiveRegistration (IKGroup_LevelReset 0x12a68), then 1: inherited.
    // vt+0x50 / +0x68 / +0x70 / +0x78 / +0x7c 0x5a7dd0 / 0x5a7dd8 / 0x5a7de0 / 0x5a7de8 / 0x5a7df0: empty (IKBaseGroup's).
    // vt+0xb8 0x005a7df8 CKCommonBaseGroup_vfB8 returns 1 (XXL2 IKBaseGroup slot GetParentClassID_maybe, shifted by
    // DotD's 0xc): IKBaseGroup models no slot there and no ported code calls it.
};
DOTD_ASSERT_SIZE(CKCommonBaseGroup, 0x2c);
