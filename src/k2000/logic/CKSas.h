// CKSas.h - a sector's area of space: two sector numbers and two boxes (key 0x44c, vtable 0xb141a0, size
// 0x3c). Original unit: CKSas.cpp (0x326b8-0x32cb0). The sector keeps them in its +0x10 array (CKSector_Load);
// CKSector_FindSectorAtPoint_maybe walks them to tell which sector a point is in. Name ours (the XXL2 sources
// have no CKSas).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKSas : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x11)
    DOTD_DECLARE_FACTORIES(CKSas)

    CKSas() {}  // 0x00032898 CKSas_Create: only the vtable is set
    ~CKSas() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00032970 CKSas_Load

    // A box as the file stores it: maximum corner first (x, y, z), then minimum corner.
    struct SBox {
        float m_vMax[3];
        float m_vMin[3];
    };

    uint32_t m_ui32SectorA;  // +0x04 the sector a point in m_boxA belongs to
    uint32_t m_ui32SectorB;  // +0x08 the sector for m_boxB
    SBox m_boxA;             // +0x0c
    SBox m_boxB;             // +0x24
};
DOTD_ASSERT_SIZE(CKSas, 0x3c);
DOTD_ASSERT_OFFSET(CKSas, m_ui32SectorA, 0x04);
DOTD_ASSERT_OFFSET(CKSas, m_boxA, 0x0c);
DOTD_ASSERT_OFFSET(CKSas, m_boxB, 0x24);
