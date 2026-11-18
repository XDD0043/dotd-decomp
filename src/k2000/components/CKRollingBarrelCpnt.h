// CKRollingBarrelCpnt.h - the rolling barrels' references (key 0xd86, vtable 0xb265f8, size 0x10; an IKMecaCpnt).
// Original unit: CKRollingBarrelCpnt.cpp. XXL2's class of this name is a larger, different one (barrel pool, bounce
// particles); DotD's keeps only a reference vector. No LVL file of DotD holds one.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKMecaCpntBase.h"
#include "k2000/util/TVector.h"

class CKRollingBarrelCpnt : public IKMecaCpnt {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x36)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c34c8
        return key == 0xd86 || key == 0xa06 || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKRollingBarrelCpnt)

    // 0x00441ef0 CKRollingBarrelCpnt_Create: operator new(0x10), the base (0x3f7a08), the vtable, the vector null, 1, 0.
    CKRollingBarrelCpnt() {
        m_vUnk04.m_pBlock = nullptr;
        m_vUnk04.m_ui32NbElt = 1;
        m_vUnk04.m_ui32NbUsedElt = 0;
    }
    // 0x00441db8 CKRollingBarrelCpnt_Destructor (0x441d58 the deleting one): the block freed (the fields left as they
    // are), then the base's destructor.
    ~CKRollingBarrelCpnt() override;
    // vt+0x10 0x00441b78 CKRollingBarrelCpnt_Destroy: the base's (vt+0x54) only, the block kept; inherited.
    // vt+0x24 0x00441b50 RecursiveRegistration: the base's (nothing); inherited.
    // vt+0x30 0x00441938 CKRollingBarrelCpnt_PostLoad: the base's (vt+0x50), 1; inherited.

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00441960 CKRollingBarrelCpnt_Load

    TVector<IKSerializable*, 1> m_vUnk04;  // +0x04 references (target class unknown)
};
DOTD_ASSERT_SIZE(CKRollingBarrelCpnt, 0x10);
DOTD_ASSERT_OFFSET(CKRollingBarrelCpnt, m_vUnk04, 0x04);
