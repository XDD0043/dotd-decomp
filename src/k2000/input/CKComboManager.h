// CKComboManager.h - the input sequence tracker and the data of its sequences (XXL2: K/KModules/KIL/KCombo,
// CKComboManager, CKComboTransition and CKCommand, the same members in the same order; Ghidra:
// InputSequenceTracker, InputSequenceStep). Code in input/InputSequenceTracker.cpp (0x102010-0x102d70).
//   CKComboManager     size 0x0c, vtable 0xb193b0: CKInput::m_pComboManager, made by InitializeModule
//   CKComboTransition  size 0x10, vtable 0xb195b0: CKInput::m_aComboTransition (constructor inlined in the Load)
//   CKCommand          size 0x10, no vtable:       CKInput::m_aComboCommand (constructor inlined in the Load)
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"

class CKAction;
class CKCombo;

struct CKCommand {
    uint8_t m_ui8Command;      // +0x00 0xff when not set
    uint8_t m_ui8Value;        // +0x01
    uint8_t m_pad02[2];
    float m_fTimePressed;      // +0x04
    float m_fEndTimePressed;   // +0x08
    uint8_t m_bValidate;       // +0x0c
    uint8_t m_pad0d[3];
};
DOTD_ASSERT_SIZE(CKCommand, 0x10);
DOTD_ASSERT_OFFSET(CKCommand, m_fTimePressed, 0x04);
DOTD_ASSERT_OFFSET(CKCommand, m_fEndTimePressed, 0x08);
DOTD_ASSERT_OFFSET(CKCommand, m_bValidate, 0x0c);

class CKComboTransition {
public:
    // The constructor CKInput_LoadInputConfig_maybe inlines (0x10c250).
    CKComboTransition() {
        m_aBreakCommand = nullptr;
        m_ui8NbValidCommand = 0;
        m_ui8NbBreakCommand = 0;
        m_aValidCommand = nullptr;
    }
    virtual ~CKComboTransition() {}  // vt+0x00 / +0x04 0x9a6440 / 0x9a6410

    // 0x00102730 InputSequenceStep_Init_maybe; XXL2 InitializeData(UInt8, UInt8, CKCommand*, CKCommand*).
    void InitializeData(uint8_t nbValid, uint8_t nbBreak, CKCommand* valid, CKCommand* breaks);

    uint8_t m_ui8NbValidCommand;  // +0x04
    uint8_t m_ui8NbBreakCommand;  // +0x05
    uint8_t m_pad06[2];
    CKCommand* m_aValidCommand;   // +0x08 null when there is none
    CKCommand* m_aBreakCommand;   // +0x0c null when there is none
};
DOTD_ASSERT_SIZE(CKComboTransition, 0x10);
DOTD_ASSERT_OFFSET(CKComboTransition, m_ui8NbValidCommand, 0x04);
DOTD_ASSERT_OFFSET(CKComboTransition, m_ui8NbBreakCommand, 0x05);
DOTD_ASSERT_OFFSET(CKComboTransition, m_aValidCommand, 0x08);
DOTD_ASSERT_OFFSET(CKComboTransition, m_aBreakCommand, 0x0c);

class CKComboManager {
public:
    CKComboManager();  // 0x00102030 InputSequenceTracker_Construct_maybe
    virtual ~CKComboManager() {}  // vt+0x00 / +0x04 0x9a6308 / 0x9a62d8

    // 0x00102050 InputSequenceTracker_SetSequence_maybe; XXL2 Initialize(UInt8, CKCombo*).
    int32_t Initialize(uint8_t nbCombo, CKCombo* combos);
    // 0x00102070 InputSequenceTracker_SetEnabled_maybe; XXL2 ActiveComboManager(Bool).
    void ActiveComboManager(uint8_t active);
    // 0x001021d0 InputSequenceTracker_SetSequenceEnabled_maybe (XXL2 ActiveCombo): the combo's active flag,
    // then its Reset.
    void SetComboActive(uint32_t combo, uint8_t active);
    // 0x00102220 InputSequenceTracker_Update_maybe (XXL2 Update(UInt8*, CKAction*)): every combo checked
    // against the filtered actions; its progress in filtered[m_ui8NbAction + combo]. Returns 1.
    int32_t Update(uint8_t* filtered, CKAction* actions);
    // 0x00102068 KStub_Return1_102068 (CKInput_Shutdown_maybe calls it on the combo manager): 1, nothing else.
    int32_t Shutdown() { return 1; }

    uint8_t m_bActive;      // +0x04
    uint8_t m_ui8NbCombo;   // +0x05
    uint8_t m_pad06[2];
    CKCombo* m_aCombos;     // +0x08
};
DOTD_ASSERT_SIZE(CKComboManager, 0x0c);
DOTD_ASSERT_OFFSET(CKComboManager, m_bActive, 0x04);
DOTD_ASSERT_OFFSET(CKComboManager, m_ui8NbCombo, 0x05);
DOTD_ASSERT_OFFSET(CKComboManager, m_aCombos, 0x08);
