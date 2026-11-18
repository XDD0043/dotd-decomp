// CKOutputAnchor.h - an output anchor of a logic block (key 0x618c, vtable 0xb1f150, size 0x18).
// Original unit: CKOutputAnchor.cpp. The same layout and Load as CKInputAnchor; no XXL2 class.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/KBase610C.h"

class CKOutputAnchor : public KBase610C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x186)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9b16e8
        return key == 0x618c || key == 0x610c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKOutputAnchor)

    CKOutputAnchor();  // 0x00204880 CKOutputAnchor_Construct (0x002048e0 CKOutputAnchor_Construct_2: the same)
    // 0x00204bf8 CKOutputAnchor_Destructor (0x00204b80 DeletingDestructor and 0x00204810 Destructor_2_maybe: the
    // same): the link block freed, the count and block cleared.
    ~CKOutputAnchor() override;

    // vt+0x24 0x00204788 CKOutputAnchor_RecursiveRegistration: the base's (0x205210, nothing).
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x002045a8 CKOutputAnchor_Load
    void Destroy() override;                            // vt+0x10 0x002047b0 CKOutputAnchor_Destroy
    TVector<IKSerializable*, 1>* GetLinks() override { return &m_vLinks; }  // vt+0x50 0x002044f0 CKOutputAnchor_vf50
    void DisconnectAll() override;                      // vt+0x54 0x00204a88 CKOutputAnchor_DisconnectAll_maybe
    void PropagateValue() override;                     // vt+0x5c 0x002049e8 CKOutputAnchor_PropagateValue_maybe
    uint8_t Connect(KBase610C* other) override;         // vt+0x60 0x00204e00 CKOutputAnchor_ConnectInput
    uint8_t Disconnect(KBase610C* other) override;      // vt+0x64 0x00204c68 CKOutputAnchor_DisconnectInput

    TVector<IKSerializable*, 1> m_vLinks;  // +0x0c references (CKInputAnchor in the samples _maybe)
};
DOTD_ASSERT_SIZE(CKOutputAnchor, 0x18);
DOTD_ASSERT_OFFSET(CKOutputAnchor, m_vLinks, 0x0c);
