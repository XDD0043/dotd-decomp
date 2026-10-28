// CKGrpLevelManager.h - the level-manager group (key 0x1644, size 0x2c; XXL2 CKGrpLevelManager:
// IKGrpLevelManager -> IKGroup<IKHook>, no members). Original unit: CKGrpLevelManager.cpp
// (0x5a8260-0x5a8910, TOC2). The Load is GroupBasicLoad.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/groups/IKBaseGroup.h"

class CKGrpLevelManager : public IKGroup<IKHook> {
public:
    DOTD_CLASS_KEY(kCategoryGroup, 0x59)
    DOTD_DECLARE_FACTORIES(CKGrpLevelManager)

    // 0x005a87d8 CKGrpLevelManager_Create (inlined constructor): the bases, then the priority word 0x80000026.
    CKGrpLevelManager() { m_ui32Priority = 0x80000026u; }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005a8500 CKGrpLevelManager_Load
};
DOTD_ASSERT_SIZE(CKGrpLevelManager, 0x2c);
