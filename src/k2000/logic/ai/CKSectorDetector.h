// CKSectorDetector.h - a sector's detectors (key 0x274c, vtable 0xb1c350, size 0xc). Original unit:
// CKSectorDetector.cpp. XXL2: K/KServices/KServiceDetect/SectorDetector/CKSectorDetector.h, which has a
// second array (m_apGeometry) the PS3 class does not.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKSectorDetector : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x9d)
    DOTD_DECLARE_FACTORIES(CKSectorDetector)

    CKSectorDetector() {}  // 0x001a8428 CKSectorDetector_Create sets the vtable only
    ~CKSectorDetector() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001a81f8 CKSectorDetector_Load

    IKSerializable** m_apDetector;  // +0x04 CKDetectorBase* (Mem_AllocAligned16)
    uint32_t m_ui32NbDetector;      // +0x08
};
DOTD_ASSERT_SIZE(CKSectorDetector, 0xc);
DOTD_ASSERT_OFFSET(CKSectorDetector, m_apDetector, 0x04);
DOTD_ASSERT_OFFSET(CKSectorDetector, m_ui32NbDetector, 0x08);
