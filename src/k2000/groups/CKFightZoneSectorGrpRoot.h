// CKFightZoneSectorGrpRoot.h - the root of a sector's fight-zone groups (key 0x1904, vtable 0xb21c38,
// size 0x2c). Original unit: CKFightZoneSectorGrpRoot.cpp. XXL2: K/KSquad/CKFightZoneSectorGrpRoot.h
// (its Load is GroupBasicLoad, as here).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/groups/IKBaseGroup.h"

class CKFightZoneSectorGrpRoot : public IKGroup<IKHook> {
public:
    DOTD_CLASS_KEY(kCategoryGroup, 0x64)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9bbf68
        return key == 0x1904 || key == 0x17e || key == 0x4 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKFightZoneSectorGrpRoot)

    // 0x0026dd70 CKFightZoneSectorGrpRoot_Create (inlined constructor): the bases, then the priority word
    // 0x80000015.
    CKFightZoneSectorGrpRoot() { m_ui32Priority = 0x80000015u; }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0026de48 CKFightZoneSectorGrpRoot_Load
    // vt+0x30 0x0026d818 CKFightZoneSectorGrpRoot_PostLoad: IKLife_PostLoad 0x19f68, then 1.
    int32_t PostLoad(int32_t type) override {
        PostLoadLife(type);
        return 1;
    }
    // vt+0xa0 0x0026dad0 CKFightZoneSectorGrpRoot_OnActivate: every child group (the fight zones) woken in its own bundle
    // (SetObjectActive_maybe 0x1d1c0).
    void VfA0() override;
    // vt+0xa4 0x0026dbb0 CKFightZoneSectorGrpRoot_OnDeactivate: every child group put to sleep (SetObjectActive_maybe),
    // the enemy group unlocked first while it is locked.
    void VfA4() override;
    void Restart() override;  // vt+0x54 0x0026d968 CKFightZoneSectorGrpRoot_Restart
    // vt+0x10 0x0026de70 CKFightZoneSectorGrpRoot_Destroy: no child groups (+0x18), no members (vt+0xb0's head).
    void Destroy() override { DestroyGroupLists(); }
    // vt+0xa8 0x0026da60 CKFightZoneSectorGrpRoot_EnableMembers / vt+0xac 0x0026db40 DisableMembers (OnLock / OnUnlock): every child group
    // locked / unlocked (SetObjectLocked 0x1c250).
    void OnLock() override;
    void OnUnlock() override;
};
DOTD_ASSERT_SIZE(CKFightZoneSectorGrpRoot, 0x2c);
