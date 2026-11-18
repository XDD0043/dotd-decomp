// CKHkS08CrumblyZoneMultiState.cpp - reconstructed original translation unit 0x413fe8-0x4140f0 (GAME_TOC1, main_toc1),
// 3 functions, 3 live.
// Primary class: CKHkS08CrumblyZoneMultiState  key 0x3582  category Hook  size 0xd4  vtable 0xb25bf8
// Other owners: CKHkCrumblyZoneMultiState (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x413fe8  CKHkS08CrumblyZoneMultiState_GetTotalHealth_maybe
//   [x] 0x414040  CKHkCrumblyZoneMultiState_CurrentStateHasPieces_maybe
//   [x] 0x414098  CKHkS08CrumblyZoneMultiState_GetTotalMaxHealth_maybe
#include "Spyro2008/hooks/CKHkS08CrumblyZoneMultiState.h"

#include "k2000/logic/CKCrumblyZoneState.h"

// 0x00413fe8 CKHkS08CrumblyZoneMultiState_GetTotalHealth_maybe (0 from TOC 0x4ac4, fadds from the last state)
float CKHkS08CrumblyZoneMultiState::GetTotalHealth() const {
    float total = 0.0f;
    for (uint32_t i = m_vUnk38.m_ui32NbUsedElt; i != 0; --i) {
        total = total + static_cast<const CKCrumblyZoneState*>(m_vUnk38.m_pBlock[i - 1])->m_unk08;
    }
    return total;
}

// 0x00414098 CKHkS08CrumblyZoneMultiState_GetTotalMaxHealth_maybe
float CKHkS08CrumblyZoneMultiState::GetTotalMaxHealth() const {
    float total = 0.0f;
    for (uint32_t i = m_vUnk38.m_ui32NbUsedElt; i != 0; --i) {
        total = total + static_cast<const CKCrumblyZoneState*>(m_vUnk38.m_pBlock[i - 1])->m_unk0c;
    }
    return total;
}
