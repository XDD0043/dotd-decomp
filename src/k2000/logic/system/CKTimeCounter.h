// CKTimeCounter.h - a timer firing trigger starters (key 0x21cc, vtable 0xb1eeb0, size 0x30). Original
// unit: CKTimeCounter.cpp. XXL2: K/KServices/KServiceCounter/CKTimeCounter.h (m_fCurrentValue,
// m_fMaxValue, m_ui32CurrentLoop, m_ui32MaxLoop, m_baFlags, m_tsMaxValueReached, m_tsMaxLoopReached);
// DotD has a second float after m_fMaxValue and two more words, so the middle names are _maybe.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKCounter.h"
#include "k2000/services/CTriggerStarter.h"

class CKTimeCounter : public IKCounter {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x87)
    DOTD_DECLARE_FACTORIES(CKTimeCounter)

    CKTimeCounter() {}  // inlined in 0x00200be0 CKTimeCounter_Create: only the vtable
    ~CKTimeCounter() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00200e10 CKTimeCounter_Load
    // 0x00200988 CKTimeCounter_Reset (not virtual): the counter restarts: current value 0, loop 0, a new random
    // maximum between m_fMaxValue and m_unk0c (rand() & 0xffff over 65535), flag bit 0 cleared.
    void Reset();

    float m_fCurrentValue;                // +0x04 XXL2 m_fCurrentValue _maybe; not loaded
    float m_fMaxValue;                    // +0x08 XXL2 m_fMaxValue
    float m_unk0c;                        // +0x0c a second time (equal to +0x08 in the samples)
    float m_fDrawnMaxValue;               // +0x10 not loaded; Reset draws it between m_fMaxValue and m_unk0c _maybe
    uint32_t m_ui32CurrentLoop;           // +0x14 _maybe; not loaded
    uint32_t m_ui32MaxLoop;               // +0x18 XXL2 m_ui32MaxLoop
    uint32_t m_baFlags;                   // +0x1c XXL2 m_baFlags _maybe; not loaded
    CTriggerStarter m_tsMaxValueReached;  // +0x20 XXL2 m_tsMaxValueReached
    CTriggerStarter m_tsMaxLoopReached;   // +0x28 XXL2 m_tsMaxLoopReached
};
DOTD_ASSERT_SIZE(CKTimeCounter, 0x30);
DOTD_ASSERT_OFFSET(CKTimeCounter, m_fMaxValue, 0x08);
DOTD_ASSERT_OFFSET(CKTimeCounter, m_unk0c, 0x0c);
DOTD_ASSERT_OFFSET(CKTimeCounter, m_ui32MaxLoop, 0x18);
DOTD_ASSERT_OFFSET(CKTimeCounter, m_tsMaxValueReached, 0x20);
DOTD_ASSERT_OFFSET(CKTimeCounter, m_tsMaxLoopReached, 0x28);
