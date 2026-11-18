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
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ab008
        return key == 0x280c || key == 0x270c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKDetectorEvent)

    CKDetectorEvent() {}  // inlined in 0x001a9fb8 CKDetectorEvent_Create: only the vtable
    ~CKDetectorEvent() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001a9ca8 CKDetectorEvent_Load
    // vt+0x50 0x001a99b0 CKDetectorEvent_FireDetectionEvents_maybe: the base's detection (called directly), then the
    // trigger starters of what happened: [0] entered (GetDetectionType(0)), [1] inside (1), [2] left (2). 0 when the
    // base did not detect.
    int32_t Detect() override;
    // vt+0x40 0x001a9b20 CKDetectorEvent_GetInfo: the base's values, then 100 (GetDetectionType(1), a byte: accessor
    // 0x1a98e0 CKDetectorEvent_QueryVf54Mode1_maybe); the answers merged (2 wins, then the base's 0).
    int32_t GetInfo(IKInfo* info, int32_t request) override;

    CTriggerStarter m_tsDetectTrigger[3];  // +0x14 XXL2 m_tsDetectTrigger
};
DOTD_ASSERT_SIZE(CKDetectorEvent, 0x2c);
DOTD_ASSERT_OFFSET(CKDetectorEvent, m_tsDetectTrigger, 0x14);
