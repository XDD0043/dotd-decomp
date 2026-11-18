// CKInputAnchor.h - an input anchor of a logic block (key 0x614c, vtable 0xb1f0e0, size 0x18). Original
// unit: CKInputAnchor.cpp. No XXL2 class; the names are ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/KBase610C.h"

class CKInputAnchor : public KBase610C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x185)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9b16b0
        return key == 0x614c || key == 0x610c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKInputAnchor)

    CKInputAnchor();  // 0x00203ba0 CKInputAnchor_Construct (0x00203c00 CKInputAnchor_Construct_2: the same)
    // 0x00203f68 CKInputAnchor_Destructor (0x00203b28 DeletingDestructor and 0x00203fd8 Destructor_2_maybe: the same):
    // the link block freed, the count and block cleared.
    ~CKInputAnchor() override;

    // vt+0x24 0x00203aa0 CKInputAnchor_RecursiveRegistration: the base's (0x205210, nothing).
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x002038c0 CKInputAnchor_Load
    void Destroy() override;                            // vt+0x10 0x00203ac8 CKInputAnchor_Destroy
    TVector<IKSerializable*, 1>* GetLinks() override { return &m_vLinks; }  // vt+0x50 0x002037b0 CKInputAnchor_vf50
    void DisconnectAll() override;                      // vt+0x54 0x00203d08 CKInputAnchor_DisconnectAll_maybe
    void PropagateValue() override;                     // vt+0x5c 0x002037c0 CKInputAnchor_PropagateValue_maybe
    uint8_t Connect(KBase610C* other) override;         // vt+0x60 0x002041e0 CKInputAnchor_ConnectOutput
    uint8_t Disconnect(KBase610C* other) override;      // vt+0x64 0x00204048 CKInputAnchor_DisconnectOutput

    // 0x00203e00 CKInputAnchor_UpdateFromSource_maybe: `source` (one of the linked output anchors) now
    // holds `value`; this anchor becomes 1 when a linked anchor is set (the source itself counts when
    // value is 1, otherwise only the others), else 0.
    void UpdateFromSource(KBase610C* source, uint8_t value);

    TVector<IKSerializable*, 1> m_vLinks;  // +0x0c references (CKOutputAnchor in the samples _maybe)
};
DOTD_ASSERT_SIZE(CKInputAnchor, 0x18);
DOTD_ASSERT_OFFSET(CKInputAnchor, m_vLinks, 0x0c);
