// InputSequence.cpp - reconstructed original translation unit 0x101c48-0x102010 (GAME_TOC1, main_toc1), 9 functions, 6 live.
// Primary owner: InputSequence (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x101c48  InputSequence_Construct_2_maybe  [dead]
//   [x] 0x101c88  InputSequence_Construct_maybe
//   [x] 0x101cc8  InputSequence_Setup_maybe
//   [x] 0x101d38  InputSequence_Reset_maybe
//   [x] 0x101e00  InputSequence_AdvanceStep_maybe
//   [x] 0x101ef0  InputSequence_DeletingDestructor_maybe
//   [x] 0x101f20  InputSequence_Destructor_maybe
//   [ ] 0x101f30  InputSequence_Destructor_2_maybe  [dead]
//   [ ] 0x101f40  InputSequence_SetBlocked_maybe  [dead]
#include "k2000/input/CKCombo.h"
#include "k2000/input/CKComboManager.h"

#include "crt/ppc_ops.h"

// 0x00101c88 InputSequence_Construct_maybe, in the original's store order.
CKCombo::CKCombo() {
    m_fComboTime = 1.0f;
    m_bActive = 1;
    m_unk05 = 0;
    m_ui8CurrentState = 0;
    m_fStopComboTime = 0.0f;
    m_ui8NbState = 0;
    m_aTransitions = nullptr;
}

// 0x00101cc8 InputSequence_Setup_maybe (XXL2 CKCombo::InitializeData). A combo without states is cleared
// and inactive.
int32_t CKCombo::InitializeData(uint8_t nbState, CKComboTransition* transitions, float comboTime, uint8_t active) {
    if (nbState != 0) {
        m_fComboTime = comboTime;
        m_bActive = active;
        m_ui8NbState = nbState;
        m_aTransitions = transitions;
        m_unk05 = 0;
        m_fStopComboTime = 0.0f;
        m_ui8CurrentState = 0;
        return 1;
    }
    m_ui8NbState = 0;
    m_fComboTime = 0.0f;
    m_aTransitions = nullptr;
    m_bActive = 0;
    m_unk05 = 0;
    m_fStopComboTime = 0.0f;
    m_ui8CurrentState = 0;
    return 1;
}

// 0x00101d38 InputSequence_Reset_maybe
void CKCombo::Reset() {
    m_ui8CurrentState = 0;
    m_fStopComboTime = 0.0f;
    if (m_ui8NbState == 0) return;
    uint32_t i = 0;
    do {
        CKComboTransition* transition = &m_aTransitions[i];
        if (transition->m_ui8NbBreakCommand != 0) {
            uint8_t n = 0;
            CKCommand* command = transition->m_aBreakCommand;
            do {
                ++n;
                command->m_bValidate = 0;
                ++command;
            } while (transition->m_ui8NbBreakCommand != n);
        }
        if (transition->m_ui8NbValidCommand != 0) {
            uint8_t n = 0;
            CKCommand* command = transition->m_aValidCommand;
            do {
                ++n;
                command->m_bValidate = 0;
                ++command;
            } while (transition->m_ui8NbValidCommand != n);
        }
        i = (i + 1) & 0xff;
    } while (i < m_ui8NbState);
}

// 0x00101e00 InputSequence_AdvanceStep_maybe (XXL2 CKCombo::NextState): the current transition's valid and
// break commands cleared, the state advanced up to m_ui8NbState, then the progress state x 255 / m_ui8NbState
// (0 without states).
uint8_t CKCombo::NextState() {
    CKComboTransition* transition = &m_aTransitions[m_ui8CurrentState];
    if (transition->m_ui8NbValidCommand != 0) {
        uint32_t n = 0;
        do {
            transition->m_aValidCommand[n].m_bValidate = 0;
            n = (n + 1) & 0xff;
        } while (transition->m_ui8NbValidCommand != n);
    }
    transition = &m_aTransitions[m_ui8CurrentState];
    if (transition->m_ui8NbBreakCommand != 0) {
        uint32_t n = 0;
        do {
            transition->m_aBreakCommand[n].m_bValidate = 0;
            n = (n + 1) & 0xff;
        } while (transition->m_ui8NbBreakCommand != n);
    }
    const uint8_t nbState = m_ui8NbState;
    if (m_ui8CurrentState < nbState) m_ui8CurrentState = static_cast<uint8_t>(m_ui8CurrentState + 1);
    if (nbState == 0) return 0;
    const int32_t state = m_ui8CurrentState;
    return static_cast<uint8_t>(ppc::divw(state * 0x100 - state, nbState));
}
