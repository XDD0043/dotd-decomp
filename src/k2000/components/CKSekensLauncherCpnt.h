// CKSekensLauncherCpnt.h - the sequences an object can start (key 0xd46, vtable 0xb1ead8, size 0x10).
// Original unit: CKSekensLauncherCpnt.cpp. No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class CKSekensLauncherCpnt : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x35)
    DOTD_DECLARE_FACTORIES(CKSekensLauncherCpnt)

    // 0x001f7c10 CKSekensLauncherCpnt_Create (the constructor 0x1f7668 inlined): null, 10, 0.
    CKSekensLauncherCpnt() {
        m_vSekens.m_pBlock = nullptr;
        m_vSekens.m_ui32NbElt = 10;
        m_vSekens.m_ui32NbUsedElt = 0;
    }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001f7d20 CKSekensLauncherCpnt_Load

    TVector<IKSerializable*, 10> m_vSekens;  // +0x04 references (_maybe CKSekens, from the class name)
};
DOTD_ASSERT_SIZE(CKSekensLauncherCpnt, 0x10);
DOTD_ASSERT_OFFSET(CKSekensLauncherCpnt, m_vSekens, 0x04);
