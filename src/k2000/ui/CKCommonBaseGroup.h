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
};
DOTD_ASSERT_SIZE(CKCommonBaseGroup, 0x2c);
