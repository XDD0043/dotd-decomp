// InputAction.cpp - reconstructed original translation unit 0x1014a8-0x101c48 (GAME_TOC1, main_toc1), 13 functions, 7 live.
// Primary owner: InputAction (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x1014a8  InputAction_Construct_2_maybe  [dead]
//   [x] 0x1014f0  InputAction_Construct_maybe
//   [ ] 0x101538  InputAction_ClearBinding_maybe
//   [x] 0x101550  InputAction_SetFilter_maybe
//   [ ] 0x1015f0  InputAction_InitFilter_maybe  [dead]
//   [ ] 0x101670  InputAction_SetSourceFromBytes_maybe  [dead]
//   [x] 0x101708  InputAction_SelectMappingSet_maybe
//   [ ] 0x101788  InputAction_CopyMappingSet_maybe  [dead]
//   [ ] 0x101850  InputAction_SaveSourceState_maybe  [dead]
//   [ ] 0x101888  InputAction_RestoreSourceState_maybe  [dead]
//   [x] 0x1018d0  InputAction_ResetState_maybe
//   [x] 0x1018f8  InputAction_UpdateState_maybe
//   [x] 0x101bb0  InputAction_SetSource_maybe
#include "k2000/input/CKAction.h"

#include "k2000/input/CKMapping.h"
#include "k2000/input/IKFilter.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/IKTime.h"

// 0x001014f0 InputAction_Construct_maybe, in the original's store order.
CKAction::CKAction() {
    m_unk1d = 0;
    m_fStartAction = 0.0f;
    m_bActionValidate = 0;
    m_bLockedForChangeConfig = 1;
    m_bActive = 1;
    m_ui8Value = 0;
    m_ui8OldValue = 0;
    m_fActionTimePressed = 0.0f;
    m_bRepeat = 0;
    m_pFilter = nullptr;
    m_pMapping = nullptr;
}

// 0x00101550 InputAction_SetFilter_maybe: takes the filter (unless it already has this one) and
// initializes it.
int32_t CKAction::InitializeFilter(IKFilter* filter, uint8_t nbState, const uint8_t* threshold,
                                   const uint8_t* returnState, uint8_t bRepeat, uint8_t bUp) {
    IKFilter* current = m_pFilter;
    if (current == nullptr || current != filter) {
        current = filter;
        m_pFilter = filter;
    }
    if (current != nullptr) current->InitializeData(nbState, threshold, returnState, bUp);
    m_bRepeat = bRepeat;
    return 1;
}

// 0x00101bb0 InputAction_SetSource_maybe: takes the mapping (unless it already has this one) and binds
// its slot on the engine's input manager.
int32_t CKAction::InitializeMapping(IKMapping* mapping, uint8_t numController, uint8_t command, int32_t type,
                                    uint32_t slot) {
    IKMapping* current = m_pMapping;
    if (current == nullptr || current != mapping) {
        current = mapping;
        m_pMapping = mapping;
    }
    if (current != nullptr) current->InitializeData(numController, command, g_pEngine->m_input, type, slot);
    return 1;
}

// 0x001018d0 InputAction_ResetState_maybe
void CKAction::Reset() {
    m_fStartAction = 0.0f;
    m_bLockedForChangeConfig = 1;
    m_bActionValidate = 0;
    m_ui8Value = 0;
    m_ui8OldValue = 0;
    m_fActionTimePressed = 0.0f;
}

// 0x001018f8 InputAction_UpdateState_maybe. Times are the system clock (IKTime +0x0c,
// m_afCurrentTime[SYSTEM_TIME]).
int32_t CKAction::Update(uint8_t* filtered, IKTime* frameClock) {
    IKMapping* mapping = m_pMapping;
    m_ui8OldValue = *filtered;
    if (mapping == nullptr) {
        *filtered = 0;
        return 1;
    }
    m_ui8Value = 0;
    uint8_t value = mapping->m_aui8MappingActions[2] != nullptr ? *mapping->m_aui8MappingActions[2] : 0;
    m_ui8Value = value;
    const uint8_t slot0 = mapping->m_aui8MappingActions[0] != nullptr ? *mapping->m_aui8MappingActions[0] : 0;
    if (slot0 >= value) value = slot0;
    m_ui8Value = value;
    const uint8_t slot3 = mapping->m_aui8MappingActions[3] != nullptr ? *mapping->m_aui8MappingActions[3] : 0;
    if (value <= slot3) value = slot3;
    m_ui8Value = value;
    if (m_pFilter != nullptr) value = m_pFilter->Filter(value);
    const float now = frameClock->m_afCurrentTime[IKTime::SYSTEM_TIME];
    if (m_bLockedForChangeConfig != 0) {
        const uint8_t old4 = mapping->m_aui8OldMappingActions[4] != nullptr ? *mapping->m_aui8OldMappingActions[4] : 0;
        if (value == old4) {
            *filtered = 0;
            m_fStartAction = now;
            m_fActionTimePressed = 0.0f;
            return 1;
        }
        m_bLockedForChangeConfig = 0;
    }
    if (m_bRepeat == 0) {
        if (m_bActionValidate != 0) {
            *filtered = 0;
            if (value != 0) {
                m_fActionTimePressed = now - m_fStartAction;
                return 1;
            }
            m_bActionValidate = 0;
            m_fStartAction = now;
            m_fActionTimePressed = 0.0f;
            return 1;
        }
        if (m_ui8OldValue != value) {
            *filtered = value;
            m_bActionValidate = 1;
            if (value == 0) {
                m_fStartAction = now;
                m_fActionTimePressed = 0.0f;
                return 1;
            }
            m_fActionTimePressed = now - m_fStartAction;
            return 1;
        }
        *filtered = 0;
    } else {
        *filtered = value;
    }
    if (value != 0) {
        m_fActionTimePressed = now - m_fStartAction;
        return 1;
    }
    m_fStartAction = now;
    m_fActionTimePressed = 0.0f;
    return 1;
}

// 0x00101708 InputAction_SelectMappingSet_maybe
void CKAction::SelectMappingSet(int32_t set) {
    CKMapping* mapping = static_cast<CKMapping*>(m_pMapping);
    if (mapping == nullptr) return;
    uint8_t* current = mapping->m_aui8MappingActions[set];
    if (current == nullptr) return;
    uint8_t* old = mapping->m_aui8OldMappingActions[set];
    const int32_t type = mapping->m_aMappingType[set];
    const uint8_t controller = mapping->m_aui8NumController[set];
    const uint8_t command = mapping->m_aui8Command[set];
    mapping->m_aui8MappingActions[4] = current;
    mapping->m_aui8Command[4] = command;
    mapping->m_aui8OldMappingActions[4] = old;
    mapping->m_aMappingType[4] = type;
    mapping->m_aui8NumController[4] = controller;
}
