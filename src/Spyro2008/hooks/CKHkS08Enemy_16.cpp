// Reconstructed original translation unit: 0x2b0a20-0x2b0ea0 (GAME_TOC1, main_toc1), 1 functions, 1 live.
// Primary class: CKHkS08Enemy  key 0x26c2  category Hook  size 0x8f8  vtable 0xb22078
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2b0a20  CKHkS08Enemy_UpdateWindStatus
#include "Spyro2008/hooks/CKHkS08Enemy.h"

#include "Spyro2008/components/CKS08EnemyCpnt.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/system/IKTime.h"

namespace {
// 0x00a703f0 (TOC 0x1650): per enemy kind, the hot spots the status particles use.
const uint8_t kWindHotSpotCount[9] = {7, 10, 14, 13, 14, 17, 25, 17, 12};
}  // namespace

// 0x002b0a20 CKHkS08Enemy_UpdateWindStatus: nothing while the wind gauge (+0x6d0) is empty or in the main state 7. A
// gauge at the kind's +0x25c (the +0x188 component) sends the enemy to the wind-caught main state 0x1d (unless in it or
// in 0x1e); the gauge drains by dt x the second dragon's status decay rate unless a wind (element 7) damage is pending;
// empty: 0. Else the wind particles (6) at the kind's hot spots (the kind 1 skips 6..9).
void CKHkS08Enemy::UpdateWindStatus(IKTime* clock) {
    if (m_fWindGauge <= 0.0f) return;  // TOC 0x1654 (ble: a NaN goes on)
    if (m_mainState == 7) return;
    const uint8_t state = m_mainState;
    if (m_pEnemyCpnt->m_unk25c <= m_fWindGauge && state != 0x1e && state != 0x1d) {  // fcmpu + cror lt|eq
        // The original inlines the switch twice (the main state 2 with +0x558 == 8 apart); both are this one.
        SwitchMainState(0x1d, clock);
    }
    if (!PendingElementDamageIs(7)) {
        const float dt = clock->m_afDeltaTime[0];
        const float gauge = m_fWindGauge;
        m_fWindGauge = gauge - dt * HeroStatusDecayRate(1);  // 0x0032a3d0
    }
    if (m_fWindGauge <= 0.0f) {  // fcmpu + cror lt|eq
        m_fWindGauge = 0.0f;
        return;
    }
    CVector3 unused;
    static_cast<CSGHotSpot*>(GetHotSpot(1))->GetWorldPosition(&unused);  // 0x002892e8, 0x000ce790 (not read)
    const uint8_t count = kWindHotSpotCount[m_ui8EnemyClassType];
    for (uint32_t i = 0; i < count; ++i) {
        if (m_ui8EnemyClassType == 1 && i - 6u <= 3u) continue;
        CVector3 hotSpot;
        static_cast<CSGHotSpot*>(GetHotSpot(static_cast<int32_t>(i)))->GetWorldPosition(&hotSpot);
        const CVector3 at = hotSpot;
        EmitParticleAt(6, &at, nullptr, 0);  // 0x00278028
    }
}
