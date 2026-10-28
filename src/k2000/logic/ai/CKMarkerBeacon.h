// CKMarkerBeacon.h - a marker: a position and an orientation (key 0x358c, vtable 0xb19c80, size 0x20).
// Original unit: CKMarkerBeacon.cpp. XXL2: K/KServices/KServiceBeacon/CKMarkerBeacon.h (m_v3Position,
// m_qOrientation; the same Load).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"

class CKMarkerBeacon : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xd6)
    DOTD_DECLARE_FACTORIES(CKMarkerBeacon)

    CKMarkerBeacon() {}  // inlined in 0x00126060 CKMarkerBeacon_Create: only the vtable
    ~CKMarkerBeacon() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00126128 CKMarkerBeacon_Load

    CVector3 m_v3Position;       // +0x04 XXL2 m_v3Position
    float m_qOrientation[4];     // +0x10 XXL2 CQuaternion m_qOrientation (x, y, z, w _maybe)
};
DOTD_ASSERT_SIZE(CKMarkerBeacon, 0x20);
DOTD_ASSERT_OFFSET(CKMarkerBeacon, m_v3Position, 0x04);
DOTD_ASSERT_OFFSET(CKMarkerBeacon, m_qOrientation, 0x10);
