// InputSequenceTracker.cpp - reconstructed original translation unit 0x102010-0x102d70 (GAME_TOC1, main_toc1), 14 functions, 7 live.
// Primary owner: InputSequenceTracker (not a registered class)
// Other owners: InputSequenceStep (3)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x102010  InputSequenceTracker_Construct_2_maybe  [dead]
//   [x] 0x102030  InputSequenceTracker_Construct_maybe
//   [x] 0x102050  InputSequenceTracker_SetSequence_maybe
//   [ ] 0x102068  KStub_Return1_102068
//   [x] 0x102070  InputSequenceTracker_SetEnabled_maybe
//   [ ] 0x102078  InputSequenceTracker_ResetAll_maybe  [dead]
//   [ ] 0x1020f8  InputSequenceTracker_ResetSequence_maybe  [dead]
//   [ ] 0x102138  InputSequenceTracker_SetAllSequencesEnabled_maybe  [dead]
//   [x] 0x1021d0  InputSequenceTracker_SetSequenceEnabled_maybe
//   [ ] 0x102220  InputSequenceTracker_Update_maybe
//   [ ] 0x1026e0  InputSequenceTracker_SetSequenceBlocked_maybe  [dead]
//   [x] 0x102730  InputSequenceStep_Init_maybe
//   [ ] 0x102770  InputSequenceStep_Load_maybe  [dead]
//   [ ] 0x102ae0  InputSequenceStep_Save_maybe  [dead]
#include "k2000/input/CKComboManager.h"

#include "k2000/input/CKCombo.h"

// 0x00102030 InputSequenceTracker_Construct_maybe, in the original's store order.
CKComboManager::CKComboManager() {
    m_aCombos = nullptr;
    m_ui8NbCombo = 0;
    m_bActive = 0;
}

// 0x00102050 InputSequenceTracker_SetSequence_maybe
int32_t CKComboManager::Initialize(uint8_t nbCombo, CKCombo* combos) {
    m_aCombos = combos;
    m_ui8NbCombo = nbCombo;
    return 1;
}

// 0x00102070 InputSequenceTracker_SetEnabled_maybe
void CKComboManager::ActiveComboManager(uint8_t active) { m_bActive = active; }

// 0x00102730 InputSequenceStep_Init_maybe: a list is null when its count is 0.
void CKComboTransition::InitializeData(uint8_t nbValid, uint8_t nbBreak, CKCommand* valid, CKCommand* breaks) {
    m_ui8NbBreakCommand = nbBreak;
    m_ui8NbValidCommand = nbValid;
    m_aValidCommand = nbValid != 0 ? valid : nullptr;
    m_aBreakCommand = m_ui8NbBreakCommand != 0 ? breaks : nullptr;
}

// 0x001021d0 InputSequenceTracker_SetSequenceEnabled_maybe
void CKComboManager::SetComboActive(uint32_t combo, uint8_t active) {
    m_aCombos[combo].m_bActive = active;
    m_aCombos[combo].Reset();
}
