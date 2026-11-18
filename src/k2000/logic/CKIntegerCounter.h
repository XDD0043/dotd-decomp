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
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9b12f8
        return key == 0x220c || key == 0x218c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKIntegerCounter)

    CKIntegerCounter() {}  // inlined in 0x001fffb8 CKIntegerCounter_Create: only the vtable
    ~CKIntegerCounter() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00200478 CKIntegerCounter_Load
    // vt+0x40 0x00200080 CKIntegerCounter_GetInfo: the trigger values 1 the value, 2 the loop count (integers), 3 at the
    // minimum, 4 at the maximum, 5 at the start value, 6 the loop limit reached, 7 no loop yet, 8 looped at least
    // `arg` times (bytes).
    int32_t GetInfo(IKInfo* info, int32_t request) override;
    // vt+0x1c 0x00200230 CKIntegerCounter_MessageProc: the trigger messages 0x2100..0x2104, 0x210b add, 0x210c take
    // away (see the .cpp).
    int32_t MessageProc(uint16_t message, void* data) override;
    int32_t PostLoad(int32_t /*type*/) override { return 1; }  // vt+0x30 0x00200470 CKIntegerCounter_PostLoad
    // 0x001ffcc0 CKIntegerCounter_Reset_maybe (not virtual; CKSrvCounter_Start): the start value, loop 0.
    void Reset() {
        m_i32CurrentValue = m_i32StartValue;
        m_ui32CurrentLoop = 0;
    }

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
