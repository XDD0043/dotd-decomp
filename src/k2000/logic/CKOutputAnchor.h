// CKOutputAnchor.h - an output anchor of a logic block (key 0x618c, vtable 0xb1f150, size 0x18).
// Original unit: CKOutputAnchor.cpp. The same layout and Load as CKInputAnchor; no XXL2 class.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/KBase610C.h"

class CKOutputAnchor : public KBase610C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x186)
    DOTD_DECLARE_FACTORIES(CKOutputAnchor)

    CKOutputAnchor();  // 0x00204880 CKOutputAnchor_Construct
    ~CKOutputAnchor() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x002045a8 CKOutputAnchor_Load
    void PropagateValue() override;                     // vt+0x5c 0x002049e8 CKOutputAnchor_PropagateValue_maybe

    TVector<IKSerializable*, 1> m_vLinks;  // +0x0c references (CKInputAnchor in the samples _maybe)
};
DOTD_ASSERT_SIZE(CKOutputAnchor, 0x18);
DOTD_ASSERT_OFFSET(CKOutputAnchor, m_vLinks, 0x0c);
