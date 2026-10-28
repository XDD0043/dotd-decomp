// CKCombo.h - one input sequence (XXL2: K/KModules/KIL/KCombo/CKCombo.h; Ghidra: InputSequence). CKInput's
// Load allocates them (CKInput::m_aCombo, size 0x14, vtable 0xb193a0) and sets them up. Code in
// input/InputSequence.cpp (0x101c48-0x102010). DotD has a byte at +0x05 that XXL2 does not; the other
// members are XXL2's in the same order (InitializeData stores them the same way).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"

class CKComboTransition;

class CKCombo {
public:
    CKCombo();  // 0x00101c88 InputSequence_Construct_maybe
    virtual ~CKCombo() {}  // vt+0x00 / +0x04 0x101f20 / 0x101ef0 STUB(C1.6)

    // 0x00101cc8 InputSequence_Setup_maybe; XXL2 InitializeData(UInt8, CKComboTransition*, Float32, Bool).
    int32_t InitializeData(uint8_t nbState, CKComboTransition* transitions, float comboTime, uint8_t active);
    // 0x00101d38 InputSequence_Reset_maybe (XXL2 CKCombo::Reset): back to state 0, every command cleared.
    void Reset();

    uint8_t m_bActive;                    // +0x04 constructor 1
    uint8_t m_unk05;                      // +0x05 constructor 0 (DotD)
    uint8_t m_ui8NbState;                 // +0x06
    uint8_t m_ui8CurrentState;            // +0x07
    CKComboTransition* m_aTransitions;    // +0x08
    float m_fComboTime;                   // +0x0c constructor 1.0f
    float m_fStopComboTime;               // +0x10 constructor 0 (integer store)
};
DOTD_ASSERT_SIZE(CKCombo, 0x14);
DOTD_ASSERT_OFFSET(CKCombo, m_bActive, 0x04);
DOTD_ASSERT_OFFSET(CKCombo, m_unk05, 0x05);
DOTD_ASSERT_OFFSET(CKCombo, m_ui8NbState, 0x06);
DOTD_ASSERT_OFFSET(CKCombo, m_ui8CurrentState, 0x07);
DOTD_ASSERT_OFFSET(CKCombo, m_aTransitions, 0x08);
DOTD_ASSERT_OFFSET(CKCombo, m_fComboTime, 0x0c);
DOTD_ASSERT_OFFSET(CKCombo, m_fStopComboTime, 0x10);
