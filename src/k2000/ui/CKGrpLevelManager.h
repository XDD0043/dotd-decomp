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
    // vt+0x10 0x005a83a0 CKGrpLevelManager_Destroy: no child groups (+0x18), no members (vt+0xb0's head).
    void Destroy() override {
        m_lChilds = nullptr;
        *GetMemberListHead() = nullptr;
    }
    // vt+0x24 0x005a8550 CKGrpLevelManager_RecursiveRegistration: registered with the saving manager (vt+0x24, every
    // type), then IKGroup's (IKGroup_LevelReset 0x12a68), then 1.
    void RecursiveRegistration(int32_t type) override;
    // vt+0xb8 0x005a8400 CKGrpLevelManager_vfB8 returns 1 (as CKCommonBaseGroup's: no IKBaseGroup slot, no caller).
};
DOTD_ASSERT_SIZE(CKGrpLevelManager, 0x2c);
