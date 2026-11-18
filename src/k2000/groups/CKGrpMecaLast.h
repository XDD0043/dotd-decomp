// CKGrpMecaLast.h - the last mechanism group (key 0x1884, vtable 0xb25078, size 0x2c). Original unit:
// CKGrpMecaLast.cpp (0x3f8ba8-0x3f9128). XXL2: K/KMeca/Group/CKGrpMecaLast.h (an IKGroup<IKHook>, no members of
// its own). No level file holds one (work/level-class-keys.json); C2.8 port-rest R03 ported it from the code.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/groups/IKBaseGroup.h"

class CKGrpMecaLast : public IKGroup<IKHook> {
public:
    DOTD_CLASS_KEY(kCategoryGroup, 0x62)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c0de8
        return key == 0x1884 || key == 0x17e || key == 0x4 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKGrpMecaLast)

    // 0x003f8f38 CKGrpMecaLast_Create (the dead 0x3f8bf8 / 0x3f8c98 _Construct copies): the bases, priority 0x80000009.
    CKGrpMecaLast() { m_ui32Priority = 0x80000009u; }
    // 0x003f9108 CKGrpMecaLast_Destructor (= 0x3f9098 _DeletingDestructor, 0x3f90e8 dead copy): the vtables only.
    ~CKGrpMecaLast() override {}

    // vt+0x2c 0x003f8fe8 CKGrpMecaLast_Load: GroupBasicLoad 0x12ce8, then 1.
    int32_t Load(IKFile* file, int32_t type) override {
        GroupBasicLoad(file, type);
        return 1;
    }
    // vt+0x30 0x003f8d08 CKGrpMecaLast_PostLoad: IKLife_PostLoad 0x19f68, then 1.
    int32_t PostLoad(int32_t type) override {
        PostLoadLife(type);
        return 1;
    }
    // vt+0x24 0x003f8fc0 CKGrpMecaLast_RecursiveRegistration: IKGroup's (0x12a68) only, inherited.
    // vt+0x10 0x003f9038 CKGrpMecaLast_Destroy: no child groups (+0x18), no members (vt+0xb0's head).
    void Destroy() override { DestroyGroupLists(); }
    // vt+0x50 / +0x68 / +0x70 / +0x78 / +0x7c 0x3f8c68 / 0x3f8c70 / 0x3f8c78 / 0x3f8c80 / 0x3f8c88 CKGrpMecaLast_Start /
    // Stop / Pause / Resume / Update: empty (IKBaseGroup's, inherited).
    // vt+0xb8 0x003f8c90 CKGrpMecaLast_vfB8 returns 0xb: IKBaseGroup models no slot there and no ported code calls it.
};
DOTD_ASSERT_SIZE(CKGrpMecaLast, 0x2c);
