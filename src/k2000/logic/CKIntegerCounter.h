// CKIntegerCounter.h - an integer counter firing trigger starters (key 0x220c, vtable 0xb1ee58, size
// 0x34). Original unit: CKIntegerCounter.cpp. XXL2: K/KServices/KServiceCounter/CKIntegerCounter.h, the
// same members in the same order and the same Load.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKCounter.h"
#include "k2000/services/CTriggerStarter.h"

class CKIntegerCounter : public IKCounter {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x88)
    DOTD_DECLARE_FACTORIES(CKIntegerCounter)

    CKIntegerCounter() {}  // inlined in 0x001fffb8 CKIntegerCounter_Create: only the vtable
    ~CKIntegerCounter() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00200478 CKIntegerCounter_Load

    int32_t m_i32CurrentValue;            // +0x04 not loaded
    int32_t m_i32MinValue;                // +0x08
    int32_t m_i32MaxValue;                // +0x0c
    int32_t m_i32StartValue;              // +0x10 read first
    uint32_t m_ui32CurrentLoop;           // +0x14 not loaded
    uint32_t m_ui32MaxLoop;               // +0x18
    CTriggerStarter m_tsMaxValueReached;  // +0x1c
    CTriggerStarter m_tsMinValueReached;  // +0x24
    CTriggerStarter m_tsMaxLoopReached;   // +0x2c
};
DOTD_ASSERT_SIZE(CKIntegerCounter, 0x34);
DOTD_ASSERT_OFFSET(CKIntegerCounter, m_i32MinValue, 0x08);
DOTD_ASSERT_OFFSET(CKIntegerCounter, m_i32StartValue, 0x10);
DOTD_ASSERT_OFFSET(CKIntegerCounter, m_ui32MaxLoop, 0x18);
DOTD_ASSERT_OFFSET(CKIntegerCounter, m_tsMaxValueReached, 0x1c);
DOTD_ASSERT_OFFSET(CKIntegerCounter, m_tsMaxLoopReached, 0x2c);
