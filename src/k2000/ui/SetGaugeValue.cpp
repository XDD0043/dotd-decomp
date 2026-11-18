//
// Reconstructed original translation unit: 0x24b248-0x24b2e0 (GAME_TOC1, main_toc1), 2 functions, 2 live.
// Primary owner: SetGaugeValue (not a registered class)
// Other owners: SuperGaugeRecord (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x24b248  SetGaugeValue
//   [x] 0x24b2a0  SuperGaugeRecord_SetFullFlag_maybe
#include "k2000/components/CKGaugeCpntUpdater.h"

#include "k2000/logic/ui/CKGaugeCpnt.h"

// 0x0024b248 SetGaugeValue
void SetGaugeValue(CKGaugeCpntUpdater* gauge, float value, int32_t resetAux) {
    if (value < 0.0f) return;
    const float maximum = gauge->m_pGauge->m_unk04;
    if (value <= maximum) {
        gauge->m_unk0c = gauge->m_unk08;
        gauge->m_unk10 = value;
    } else {
        gauge->m_unk10 = maximum;
        gauge->m_unk0c = gauge->m_unk08;
    }
    if (resetAux != 0) gauge->m_unk14 = 0.0f;
}

// 0x0024b2a0 SuperGaugeRecord_SetFullFlag_maybe
void SuperGaugeRecord_SetFullFlag(CKGaugeCpntUpdater* gauge, uint32_t value) {
    if (gauge->m_unk18 != value) {
        gauge->m_unk18 = static_cast<uint8_t>(value);
        gauge->m_fFlashTime = 0.0f;
        return;
    }
    if (gauge->m_pGauge->m_unk21 != 0) return;
    gauge->m_unk18 = static_cast<uint8_t>(value);
    gauge->m_fFlashTime = 0.0f;
}
