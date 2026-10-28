// CKDetectorEvent.h - a detector that fires trigger starters (key 0x280c, vtable 0xb1c410, size 0x2c).
// Original unit: CKDetectorEvent.cpp. XXL2: K/KServices/KServiceDetect/CKDetectorEvent.h
// (m_tsDetectTrigger[3]; DotD loads them from the last to the first).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/ai/CKDetectorBase.h"
#include "k2000/services/CTriggerStarter.h"

class CKDetectorEvent : public CKDetectorBase {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xa0)
    DOTD_DECLARE_FACTORIES(CKDetectorEvent)

    CKDetectorEvent() {}  // inlined in 0x001a9fb8 CKDetectorEvent_Create: only the vtable
    ~CKDetectorEvent() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001a9ca8 CKDetectorEvent_Load
    void Detect() override {}  // vt+0x50 0x1a99b0 CKDetectorEvent_FireDetectionEvents_maybe  STUB(C2.2)

    CTriggerStarter m_tsDetectTrigger[3];  // +0x14 XXL2 m_tsDetectTrigger
};
DOTD_ASSERT_SIZE(CKDetectorEvent, 0x2c);
DOTD_ASSERT_OFFSET(CKDetectorEvent, m_tsDetectTrigger, 0x14);
