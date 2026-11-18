// InputMapping.cpp - reconstructed original translation unit 0x10e380-0x10eba0 (GAME_TOC1, main_toc1), 20 functions, 11 live.
// Primary owner: InputMapping (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x10e380  InputMapping_Construct_2_maybe  [dead]
//   [x] 0x10e3a8  InputMapping_Construct_maybe
//   [x] 0x10e3d0  KStub_Nop_10e3d0
//   [ ] 0x10e3d8  InputMapping_GetActionIndex_maybe  [dead]
//   [x] 0x10e408  InputMapping_GetAnalogValue
//   [ ] 0x10e438  FUN_0010e438  [dead]
//   [x] 0x10e498  InputMapping_SetActionEnabled_maybe
//   [x] 0x10e4e8  InputMapping_GetActionEntry
//   [ ] 0x10e540  InputMapping_SetSequenceBlocked_maybe  [dead]
//   [ ] 0x10e580  InputMapping_SelectMappingSet_maybe  [dead]
//   [ ] 0x10e608  InputMapping_GetBoundButtonCode_maybe  [dead]
//   [ ] 0x10e660  FUN_0010e660  [dead]
//   [x] 0x10e6c8  InputMapping_DeletingDestructor_maybe
//   [x] 0x10e730  InputMapping_Destructor_maybe
//   [ ] 0x10e780  InputMapping_Destructor_2_maybe  [dead]
//   [x] 0x10e7d0  InputMapping_GetButtonState
//   [ ] 0x10e818  FUN_0010e818  [dead]
//   [x] 0x10e898  InputMapping_Load_maybe
//   [x] 0x10ea68  InputMapping_Save_maybe
//   [x] 0x10eb00  InputMapping_QueryActionSourceVf14_maybe  (CKInputDico::GetFilterThreshold)
#include "k2000/input/CKInputDico.h"

#include "k2000/input/CKAction.h"
#include "k2000/input/IKFilter.h"
#include "k2000/io/IKFile.h"
#include "k2000/managers/CKInput.h"
#include "k2000/misc/Engine.h"

// 0x0010e3a8 InputMapping_Construct_maybe, in the original's store order.
CKInputDico::CKInputDico() {
    m_pInput = nullptr;
    m_ui8NbCombo = 0;
    m_ui8NbAction = 0;
    m_aNumAction = nullptr;
}

// 0x0010eb00 InputMapping_QueryActionSourceVf14_maybe
uint8_t CKInputDico::GetFilterThreshold(int32_t index) const {
    CKAction* action = nullptr;
    if (index < static_cast<int32_t>(m_ui8NbAction) + static_cast<int32_t>(m_ui8NbCombo)) {
        action = m_pInput->GetAction(m_aNumAction[index]);  // 0x00105240
    }
    // BUG(original): beyond the entries the original reads the filter at address 8 (the null action's +0x08); the
    // callers (CKS08GameManager_vf168) stay in range.
    if (action == nullptr) return 0;
    IKFilter* filter = action->m_pFilter;
    return filter != nullptr ? filter->GetFilterThreshold() : 0;  // vt+0x14
}

// 0x0010e4e8 InputMapping_GetActionEntry
CKAction* CKInputDico::GetActionPointer(int32_t index) const {
    if (index >= static_cast<int32_t>(m_ui8NbAction) + static_cast<int32_t>(m_ui8NbCombo)) return nullptr;
    return m_pInput->GetAction(m_aNumAction[index]);
}

// 0x0010e898 InputMapping_Load_maybe (XXL2 CKInputDico::Load): the two counts, then the action indices:
// this configuration's actions follow the previous configurations' (*actionBase), its sequences come after
// all the actions (nbActionTotal + *comboBase). Both bases advance by this configuration's counts.
int32_t CKInputDico::Load(IKFile* file, uint8_t nbActionTotal, uint8_t* actionBase, uint8_t* comboBase) {
    m_pInput = g_pEngine->m_input;
    ReadU8(file, &m_ui8NbAction);
    ReadU8(file, &m_ui8NbCombo);
    if (m_ui8NbAction != 0 || m_ui8NbCombo != 0) {
        if (m_aNumAction != nullptr) delete[] m_aNumAction;
        m_aNumAction = new uint8_t[static_cast<uint32_t>(m_ui8NbAction) + m_ui8NbCombo];
        for (uint8_t i = 0; i < m_ui8NbAction; ++i) m_aNumAction[i] = static_cast<uint8_t>(*actionBase + i);
        for (uint8_t i = 0; i < m_ui8NbCombo; ++i) {
            m_aNumAction[m_ui8NbAction + i] = static_cast<uint8_t>(nbActionTotal + *comboBase + i);
        }
    }
    *actionBase = static_cast<uint8_t>(*actionBase + m_ui8NbAction);
    *comboBase = static_cast<uint8_t>(*comboBase + m_ui8NbCombo);
    return 1;
}

// 0x0010e498 InputMapping_SetActionEnabled_maybe
void CKInputDico::SetActionEnabled(int32_t index, uint8_t enabled) {
    m_pInput->GetAction(m_aNumAction[index])->m_unk1d = enabled;
}

// 0x0010e7d0 InputMapping_GetButtonState: entries past the actions and combos read 0.
uint8_t CKInputDico::GetButtonState(int32_t index) const {
    if (index >= static_cast<int32_t>(static_cast<uint32_t>(m_ui8NbAction) + m_ui8NbCombo)) return 0;
    return m_pInput->m_aFiltredActions[m_aNumAction[index]];
}

// 0x0010e408 CKInputDico_GetActionTimePressed (XXL2 CKInputDico::GetActionTimePressed)
float CKInputDico::GetActionTimePressed(int32_t index) const {
    return m_pInput->m_aActions[m_aNumAction[index]].m_fActionTimePressed;
}

// 0x0010ea68 InputMapping_Save_maybe (XXL2 CKInputDico::Save(IKFile*, ESerializationType)): the two counts
// (IKFile vt+0x20); the type is not used and the action indices are not written. Returns 1.
int32_t CKInputDico::Save(IKFile* file, int32_t /*type*/) {
    file->Write(&m_ui8NbAction, 1);
    file->Write(&m_ui8NbCombo, 1);
    return 1;
}
