// CKDetectorMusic.h - a detector that drives the music (key 0x2f4c, vtable 0xb1c478, size 0x20).
// Original unit: CKDetectorMusic.cpp. XXL2: K/KServices/KServiceDetect/Detector/DetectorMusic/
// CKDetectorMusic.h (m_eActionType, m_ui32Index, m_bClear; the same Load).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/ai/CKDetectorBase.h"

class CKDetectorMusic : public CKDetectorBase {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xbd)
    DOTD_DECLARE_FACTORIES(CKDetectorMusic)

    CKDetectorMusic() {}  // inlined in 0x001aa3e0 CKDetectorMusic_Create: only the vtable
    ~CKDetectorMusic() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001aa418 CKDetectorMusic_Load
    void Detect() override {}  // vt+0x50 0x1aa0f0 CKDetectorMusic_CheckAndTriggerMusic_maybe  STUB(C2.2)

    uint32_t m_eActionType;  // +0x14 XXL2 CKDetectorMusic::eActionType m_eActionType
    uint32_t m_ui32Index;    // +0x18 XXL2 m_ui32Index
    uint8_t m_bClear;        // +0x1c XXL2 m_bClear (one byte, read raw)
    uint8_t m_pad1d[3];
};
static_assert(CKDetectorMusic::kClassKey == 0x2f4c, "key");
DOTD_ASSERT_SIZE(CKDetectorMusic, 0x20);
DOTD_ASSERT_OFFSET(CKDetectorMusic, m_eActionType, 0x14);
DOTD_ASSERT_OFFSET(CKDetectorMusic, m_ui32Index, 0x18);
DOTD_ASSERT_OFFSET(CKDetectorMusic, m_bClear, 0x1c);
