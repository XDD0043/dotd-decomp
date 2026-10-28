// CKElectricalGrapple.h - the electric grab (key 0xa00c, vtable 0xb237e8, size 0x158). Original unit:
// CKElectricalGrapple.cpp (0x395018-0x396748). Derives from CKGrabElement (its constructor and Load run first).
// No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKGrabElement.h"

class CKElectricalGrapple : public CKGrabElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x280)
    DOTD_DECLARE_FACTORIES(CKElectricalGrapple)

    CKElectricalGrapple() {}  // 0x003953f8 CKElectricalGrapple_Construct: CKGrabElement's constructor, then the vtable only
    ~CKElectricalGrapple() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00395c90 CKElectricalGrapple_Load

    IKSerializable* m_unk140[3];  // +0x140 references (live: CKLightningBoltFxData)
    uint32_t m_unk14c;            // +0x14c (not loaded)
    IKSerializable* m_unk150;     // +0x150 reference (live: CKSoundDictionaryID)
    uint32_t m_unk154;            // +0x154 (not loaded)
};
DOTD_ASSERT_SIZE(CKElectricalGrapple, 0x158);
DOTD_ASSERT_OFFSET(CKElectricalGrapple, m_unk140, 0x140);
DOTD_ASSERT_OFFSET(CKElectricalGrapple, m_unk150, 0x150);
