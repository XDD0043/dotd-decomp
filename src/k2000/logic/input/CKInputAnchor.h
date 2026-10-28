// CKInputAnchor.h - an input anchor of a logic block (key 0x614c, vtable 0xb1f0e0, size 0x18). Original
// unit: CKInputAnchor.cpp. No XXL2 class; the names are ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/KBase610C.h"

class CKInputAnchor : public KBase610C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x185)
    DOTD_DECLARE_FACTORIES(CKInputAnchor)

    CKInputAnchor();  // 0x00203ba0 CKInputAnchor_Construct
    ~CKInputAnchor() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x002038c0 CKInputAnchor_Load
    void PropagateValue() override;                     // vt+0x5c 0x002037c0 CKInputAnchor_PropagateValue_maybe

    // 0x00203e00 CKInputAnchor_UpdateFromSource_maybe: `source` (one of the linked output anchors) now
    // holds `value`; this anchor becomes 1 when a linked anchor is set (the source itself counts when
    // value is 1, otherwise only the others), else 0.
    void UpdateFromSource(KBase610C* source, uint8_t value);

    TVector<IKSerializable*, 1> m_vLinks;  // +0x0c references (CKOutputAnchor in the samples _maybe)
};
DOTD_ASSERT_SIZE(CKInputAnchor, 0x18);
DOTD_ASSERT_OFFSET(CKInputAnchor, m_vLinks, 0x0c);
