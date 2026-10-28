// CKInputDico.h - one input configuration's action table (XXL2: K/KModules/KIL/KInputDico/CKInputDico.h,
// the same members in the same order; Ghidra: InputMapping). CKInput's Load allocates m_ui8NbInputConfig
// of them per input project (CKInput::m_aaInputDico, size 0x10, vtable 0xb195c0) and calls their Load.
// Code in input/InputMapping.cpp (0x10e380-0x10eba0).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"

class CKAction;
class CKInput;
class IKFile;

class CKInputDico {
public:
    CKInputDico();  // 0x0010e3a8 InputMapping_Construct_maybe
    virtual ~CKInputDico() {}                        // vt+0x00 / +0x04 0x10e730 / 0x10e6c8 STUB(C1.6)
    virtual int32_t Vf08() { return 9; }             // vt+0x08 0x9a66f0
    virtual int32_t Vf0C() { return 5; }             // vt+0x0c 0x9a66f8
    virtual void Destroy() {}                        // vt+0x10 0x10e3d0
    virtual void Save() {}                           // vt+0x14 0x10ea68 STUB(C1.6) (not on the load path)
    // vt+0x18 0x0010e898 InputMapping_Load_maybe; XXL2 Load(IKFile*, UInt8, UInt8*, UInt8*).
    virtual int32_t Load(IKFile* file, uint8_t nbActionTotal, uint8_t* actionBase, uint8_t* comboBase);

    // 0x0010e4e8 InputMapping_GetActionEntry (XXL2 GetActionPointer): the action of entry `index`, or null.
    CKAction* GetActionPointer(int32_t index) const;
    // 0x0010e498 InputMapping_SetActionEnabled_maybe: the action's +0x1d byte (CKAction::m_unk1d).
    void SetActionEnabled(int32_t index, uint8_t enabled);
    // 0x0010e7d0 InputMapping_GetButtonState: the filtered state of entry index (0 beyond the entries).
    uint8_t GetButtonState(int32_t index) const;
    // 0x0010e408 CKInputDico_GetActionTimePressed (XXL2 name): how long entry index's action has been held
    // (CKAction::m_fActionTimePressed); no range check.
    float GetActionTimePressed(int32_t index) const;

    uint8_t m_ui8NbAction;   // +0x04
    uint8_t m_ui8NbCombo;    // +0x05
    uint8_t m_pad06[2];
    uint8_t* m_aNumAction;   // +0x08 new[m_ui8NbAction + m_ui8NbCombo]: indices into CKInput::m_aActions
    CKInput* m_pInput;       // +0x0c g_pEngine->m_input at Load
};
DOTD_ASSERT_SIZE(CKInputDico, 0x10);
DOTD_ASSERT_OFFSET(CKInputDico, m_ui8NbAction, 0x04);
DOTD_ASSERT_OFFSET(CKInputDico, m_ui8NbCombo, 0x05);
DOTD_ASSERT_OFFSET(CKInputDico, m_aNumAction, 0x08);
DOTD_ASSERT_OFFSET(CKInputDico, m_pInput, 0x0c);
