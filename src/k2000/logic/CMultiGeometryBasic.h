// CMultiGeometryBasic.h - a simple detection shape (key 0x314c, vtable 0xb20c80, size 0x20). Original unit:
// CMultiGeometryBasic.cpp. XXL2: K/KUL/CMultiGeometryBasic/CMultiGeometryBasic.h (an anonymous union of
// shapes, then CBitArray8 m_baData whose bits 0-1 are the shape type).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CMultiGeometryBasic : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xc5)
    DOTD_DECLARE_FACTORIES(CMultiGeometryBasic)

    CMultiGeometryBasic() {}  // 0x00245210 CMultiGeometryBasic_Create: only the vtable
    ~CMultiGeometryBasic() override {}

    // vt+0x2c 0x002455c8 CMultiGeometryBasic_Load: the type byte, then the shape.
    int32_t Load(IKFile* file, int32_t type) override;
    // 0x002452e0 CMultiGeometryBasic_LoadShape: by m_baData & 3: 0 six floats, 1 five floats, 2 five floats
    // and a byte (+0x18), 3 nothing.
    void LoadShape(IKFile* file);

    // +0x04 the shape (XXL2's union): six words; type 2 keeps a byte in the last one (+0x18, read raw).
    union {
        float m_afShape[6];
        struct {
            float m_afShape5[5];
            uint8_t m_ui8ShapeByte;  // +0x18 type 2
            uint8_t m_pad19[3];
        };
    };
    uint8_t m_baData;  // +0x1c CBitArray8: bits 0-1 the shape type
    uint8_t m_pad1d[3];
};
static_assert(CMultiGeometryBasic::kClassKey == 0x314c, "key");
DOTD_ASSERT_SIZE(CMultiGeometryBasic, 0x20);
DOTD_ASSERT_OFFSET(CMultiGeometryBasic, m_afShape, 0x04);
DOTD_ASSERT_OFFSET(CMultiGeometryBasic, m_ui8ShapeByte, 0x18);
DOTD_ASSERT_OFFSET(CMultiGeometryBasic, m_baData, 0x1c);
