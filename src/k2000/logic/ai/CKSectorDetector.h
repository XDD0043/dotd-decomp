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
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x274c || key == 0xc; }  // vt+0x08 0x9aaec0
    DOTD_DECLARE_FACTORIES(CKSectorDetector)

    CKSectorDetector() {}  // 0x001a8428 CKSectorDetector_Create sets the vtable only
    ~CKSectorDetector() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001a81f8 CKSectorDetector_Load
    void Destroy() override;  // vt+0x10 0x001a81b0 CKSectorDetector_Destroy: the detector block freed
    // vt+0x24 0x001a7fd0 CKSectorDetector_RecursiveRegistration (unit CKSrvDetect.cpp): type 4: every detector gets
    // RecursiveRegistration(4).
    void RecursiveRegistration(int32_t type) override;
    // 0x001a8460 CKSrvDetect_RunDetectors_maybe: every detector enabled (+0x04 bit 4) and not bit 8 detects (vt+0x50).
    void RunDetectors();
    // 0x001a8518 DetectorList_ClearDetectionFlags_maybe (CKSrvDetect_UpdateInitialize): bits 1-3 of every detector's
    // +0x04 (entered, inside, left) cleared.
    void ClearDetectionFlags();

    IKSerializable** m_apDetector;  // +0x04 CKDetectorBase* (Mem_AllocAligned16)
    uint32_t m_ui32NbDetector;      // +0x08
};
DOTD_ASSERT_SIZE(CKSectorDetector, 0xc);
DOTD_ASSERT_OFFSET(CKSectorDetector, m_apDetector, 0x04);
DOTD_ASSERT_OFFSET(CKSectorDetector, m_ui32NbDetector, 0x08);
