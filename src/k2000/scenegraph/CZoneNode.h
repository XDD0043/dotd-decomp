// CZoneNode.h - a scene node with detection zones (key 0x88b, vtable 0xb18580, size 0x30). Original unit:
// CZoneNode.cpp. XXL2: K/KModules/KGL/SceneGraph/CZoneNode.h (m_apDetectZone, m_ui32NbDetectors); DotD
// keeps them as a growable array (block, capacity, size).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/scenegraph/CNode.h"

class CZoneNode : public CNode {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0x22)
    DOTD_DECLARE_FACTORIES(CZoneNode)

    CZoneNode() : m_apDetectZone(nullptr), m_ui32Capacity(2), m_ui32NbDetectors(0) {}  // 0x000d4198 CZoneNode_Create
    ~CZoneNode() override {}

    // vt+0x2c 0x000d4208 CZoneNode_Load: CNode's, then (type 0) property bit 12 and the zones.
    int32_t Load(IKFile* file, int32_t type) override;

    IKSerializable** m_apDetectZone;  // +0x24 CMultiGeometryBasic references (Mem_AllocAligned16)
    uint32_t m_ui32Capacity;          // +0x28 the block's capacity (2 when empty)
    uint32_t m_ui32NbDetectors;       // +0x2c
};
static_assert(CZoneNode::kClassKey == 0x88b, "key");
DOTD_ASSERT_SIZE(CZoneNode, 0x30);
DOTD_ASSERT_OFFSET(CZoneNode, m_apDetectZone, 0x24);
DOTD_ASSERT_OFFSET(CZoneNode, m_ui32Capacity, 0x28);
DOTD_ASSERT_OFFSET(CZoneNode, m_ui32NbDetectors, 0x2c);
