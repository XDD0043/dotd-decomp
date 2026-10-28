// CKCrumblyZoneElement.h - one element of a crumbly zone (key 0xa30c, vtable 0xb25700, size 0x30).
// Original unit: CKCrumblyZoneElement.cpp. DotD only (no XXL2 class); the names are ours, the reference
// types from the files (struct draft).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"

class CKCrumblyZoneElement : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x28c)
    DOTD_DECLARE_FACTORIES(CKCrumblyZoneElement)

    CKCrumblyZoneElement() {}  // 0x00402480 CKCrumblyZoneElement_Construct: only the vtable
    ~CKCrumblyZoneElement() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00403358 CKCrumblyZoneElement_Load

    IKSerializable* m_pZone;      // +0x04 CKHkS08CrumblyZoneMultiState in the files
    uint32_t m_unk08;             // +0x08 not loaded; PostLoad clears its first (high) byte
    IKSerializable* m_pNode;      // +0x0c a scene node (CNode) in the files
    IKSerializable* m_unk10;      // +0x10 a reference (null in the samples)
    float m_unk14;                // +0x14
    uint32_t m_unk18;             // +0x18
    IKSerializable* m_unk1c;      // +0x1c a reference (null in the samples)
    IKSerializable* m_unk20;      // +0x20 a reference (null in the samples)
    uint32_t m_unk24;             // +0x24 not loaded; PostLoad sets 0
    CMatrix34* m_pMatrix28;       // +0x28 RwMatrixCreate, then loaded
    CMatrix34* m_pMatrix2c;       // +0x2c RwMatrixCreate, then loaded
};
DOTD_ASSERT_SIZE(CKCrumblyZoneElement, 0x30);
DOTD_ASSERT_OFFSET(CKCrumblyZoneElement, m_pZone, 0x04);
DOTD_ASSERT_OFFSET(CKCrumblyZoneElement, m_pNode, 0x0c);
DOTD_ASSERT_OFFSET(CKCrumblyZoneElement, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(CKCrumblyZoneElement, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKCrumblyZoneElement, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CKCrumblyZoneElement, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKCrumblyZoneElement, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKCrumblyZoneElement, m_pMatrix28, 0x28);
DOTD_ASSERT_OFFSET(CKCrumblyZoneElement, m_pMatrix2c, 0x2c);
