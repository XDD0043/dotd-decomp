// HudGaugeOps.h - the gauge operations the HUD panels (CKS08InGameInterfaceLeft / Right) call, ported with
// them: the original keeps them in the component units (k2000/components/CKGaugeCpntUpdater.cpp, CKSuperGaugeCpnt
// files), which the hooks family ports. Same behaviour, so the two copies can be merged.
#pragma once
#include <cstdint>

#include "k2000/components/CKGaugeCpntUpdater.h"
#include "k2000/components/CKSuperGaugeCpntUpdater.h"

namespace hudgauge {

// 0x0024b248 SetGaugeValue: a negative value is ignored, a value above the gauge's maximum (the gauge
// component's +0x04) is capped; the previous value is kept (+0x0c = +0x08), and with `reset` the auxiliary
// value (+0x14) is cleared.
inline void SetGaugeValue(double requested, CKGaugeCpntUpdater* updater, int32_t reset) {
    if (!(requested >= 0.0)) return;
    const float maximum = updater->m_pGauge->m_unk04;
    if (requested <= static_cast<double>(maximum)) {
        updater->m_unk0c = updater->m_unk08;
        updater->m_unk10 = static_cast<float>(requested);
    } else {
        updater->m_unk10 = maximum;
        updater->m_unk0c = updater->m_unk08;
    }
    if (reset != 0) updater->m_unk14 = 0.0f;
}

// 0x00250dd8 CKSuperGaugeCpnt_SetValue: the value on the first two gauge updaters.
inline void SuperGaugeSetValue(double requested, CKSuperGaugeCpntUpdater* super, int32_t reset) {
    SetGaugeValue(requested, super->m_apUpdaters[0], reset);
    SetGaugeValue(requested, super->m_apUpdaters[1], reset);
}

// 0x00250b28 GetGaugeValue: the first updater's value.
inline double GetGaugeValue(CKSuperGaugeCpntUpdater* super) { return static_cast<double>(super->m_apUpdaters[0]->m_unk10); }

// The HUD setters: a value above the current one clears the auxiliary value only when it decreases.
inline void SetHudGaugeValue(double requested, IKSerializable* updater) {
    CKSuperGaugeCpntUpdater* super = static_cast<CKSuperGaugeCpntUpdater*>(updater);
    const double previous = GetGaugeValue(super);
    SuperGaugeSetValue(requested, super, previous < requested ? 0 : 1);
}


// 0x00250f18 CKSuperGaugeCpnt_GetMarkerValue_maybe: the third updater's value (CKSuperGaugeCpntUpdater::GetMarkerValue).
inline double SuperGaugeGetMarker(CKSuperGaugeCpntUpdater* super) { return static_cast<double>(super->GetMarkerValue()); }

// 0x00250da8 CKSuperGaugeCpnt_SetMarkerValue_maybe: the capacity marker is the third updater's value.
inline void SuperGaugeSetMarker(double ratio, CKSuperGaugeCpntUpdater* super) {
    SetGaugeValue(ratio, super->m_apUpdaters[2], 1);
}

// 0x00250d80 CKSuperGaugeCpnt_SetFullFlag_maybe -> 0x0024b2a0 SuperGaugeRecord_SetFullFlag_maybe: the first
// updater's "full" byte (+0x18); a new value restarts its timer (+0x1c), the same value only when the gauge
// component (+0x21) allows.
inline void SuperGaugeSetFullFlag(CKSuperGaugeCpntUpdater* super, uint32_t flag) {
    CKGaugeCpntUpdater* record = super->m_apUpdaters[0];
    if (record->m_unk18 != flag) {
        record->m_unk18 = static_cast<uint8_t>(flag);
        record->m_fFlashTime = 0.0f;
        return;
    }
    if (record->m_pGauge->m_unk21 != 0) return;
    record->m_unk18 = static_cast<uint8_t>(flag);
    record->m_fFlashTime = 0.0f;
}

}  // namespace hudgauge
