// Reconstructed original translation unit: 0x2af780-0x2b0120 (GAME_TOC1, main_toc1), 6 functions, 5 live.
// Primary class: CKHkS08Enemy  key 0x26c2  category Hook  size 0x8f8  vtable 0xb22078
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2af780  CKHkS08Enemy_UpdateFreezeStatus
//   [ ] 0x2aff98  KStub_Nop_2aff98  [dead]
//   [x] 0x2affa0  StaticInitAndDestruction_2affa0  (the two file statics at the end)
//   [ ] 0x2affd0  _GLOBAL__D_2affd0
//   [ ] 0x2affe0  _GLOBAL__I_2affe0
//   [x] 0x2afff0  CKHkS08Enemy_SpreadPoisonToNearby
#include "Spyro2008/hooks/CKHkS08Enemy.h"

#include "Spyro2008/components/CKS08EnemyCpnt.h"
#include "Spyro2008/hooks/CKHkS08EnemyShared.h"
#include "Spyro2008/logic/CKS08ElementDamage.h"
#include "crt/ppc_ops.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/system/IKTime.h"

#include <cmath>

namespace {
// 0x00a703d0 (TOC 0x1514): per enemy kind, the hot spots the status particles use.
const uint8_t kFreezeHotSpotCount[9] = {7, 10, 14, 13, 14, 17, 25, 17, 12};

// The frozen slowdown per second (fdivs / fadds / fmuls; Math_Sqrtf 0x10690 below the kind's +0x2bc): the kind's
// +0x2b4 / -100 (TOC 0x1518) plus 1 (TOC 0x151c), scaled by the root of gauge / +0x2bc, times dt.
float FrozenStep(const CKS08EnemyCpnt* kind, float gauge, float dt) {
    if (gauge >= kind->m_unk2bc) return (kind->m_unk2b4 / -100.0f + 1.0f) * dt;
    const float ratio = gauge / kind->m_unk2bc;
    const float slow = kind->m_unk2b4 / -100.0f;
    return dt * ppc::fmadds(slow, std::sqrt(ratio), 1.0f);
}
}  // namespace

// 0x002af780 CKHkS08Enemy_UpdateFreezeStatus: nothing while the freeze gauge (+0x6c8) is empty. A gauge at the kind's
// +0x254 (or a spent frozen time +0x6f8) on the ground (status 0, the ground probe's dH at least 0.5) sends the enemy
// to the main state 0x27 (unless in it, dying or without a state); the gauge drains by dt x the first dragon's status
// decay rate unless an ice (element 1) damage is pending. Empty: the freeze FX off, 0. Else the ice particles (4, 5,
// 0x12) at the kind's hot spots, and in the moving / attacking states the frozen time step (+0x6f8 / the time scale
// +0x1fc, the lift +0x274 and +0x76c when it stops); in the reaction 2 the same step (a full gauge at 100 x slowdown
// shattered by an ice hit: the health lowered by the kind's +0x2c0); in the main state 7 the gauge ends (a full gauge
// at 100 x slowdown: the health lowered, FX 0xb). A non-element pending damage plays the sound 0x22.
void CKHkS08Enemy::UpdateFreezeStatus(IKTime* clock) {
    const float zero = 0.0f;  // TOC 0x1524
    if (m_fIceGauge <= zero) return;
    const uint8_t state = m_mainState;
    if (state != 0x27 && state != 0x15 && state != 0xff && (m_pActiveEnemyCpnt->m_unk254 <= m_fIceGauge || m_unk6f8 <= zero)) {
        CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
        collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &m_v3Position.x, 1);  // 0x00196540
        if (m_GrdContDatasInOut.m_eContactStatus == 0 && m_GrdContDatasInOut.m_fdH >= 0.5f) {  // TOC 0x1510
            // BUG(original): the state's leave / enter rows get the ground contact block (+0x80) as their clock.
            SwitchMainState(0x27, reinterpret_cast<IKTime*>(&m_GrdContDatasInOut));
        }
    }
    if (!PendingElementDamageIs(1)) {
        const float dt = clock->m_afDeltaTime[0];
        const float gauge = m_fIceGauge;
        m_fIceGauge = gauge - dt * HeroStatusDecayRate(0);  // 0x0032a3d0
    }
    if (m_fIceGauge <= zero) {
        SetFreezeFxActive(0, -1);  // 0x0028cb88
        m_fIceGauge = zero;
    } else {
        CVector3 unused;
        GetHotSpot(1)->GetWorldPosition(&unused);  // 0x002892e8, 0x000ce790 (not read)
        const uint8_t count = kFreezeHotSpotCount[m_ui8EnemyClassType];
        for (uint32_t i = 0; i < count; ++i) {
            if (m_ui8EnemyClassType == 1 && i - 6u <= 3u) continue;
            CVector3 hotSpot;
            GetHotSpot(static_cast<int32_t>(i))->GetWorldPosition(&hotSpot);
            const CVector3 a = hotSpot;
            EmitParticleAt(4, &a, nullptr, 0);  // 0x00278028
            const CVector3 b = hotSpot;
            EmitParticleAt(5, &b, nullptr, 0);
            const CVector3 c = hotSpot;
            EmitParticleAt(0x12, &c, nullptr, 0);
        }
        const uint8_t main = m_mainState;
        const uint8_t react = m_reactState;
        const float dt = clock->m_afDeltaTime[0];
        bool stopped = false;
        if (main == 1 || react == 4 || react == 5 || main == 6 || main == 0x17 || main == 0x18 || main == 0xd ||
            main == 0xe || main == 0xf) {
            const float step = FrozenStep(m_pEnemyCpnt, m_fIceGauge, dt);
            const float left = m_unk6f8;
            float scale;
            if (step >= left) {  // fcmpu + cror gt|eq
                m_unk6f8 = step;
                scale = step;
                m_fScaledDt = scale;
                stopped = scale <= zero;
            } else {
                const float spent = left - m_pEnemyCpnt->m_unk2c4 * dt;
                m_unk6f8 = spent;
                scale = step <= spent ? step : spent;  // cror lt|eq
                m_unk6f8 = scale;
                if (!(scale < zero)) {  // bge
                    m_fScaledDt = scale;
                    stopped = scale <= zero;
                } else {
                    m_fScaledDt = zero;
                    m_unk6f8 = zero;
                    stopped = true;
                }
            }
            if (stopped) {
                m_fKnockbackTime = 0.0f;
                m_unk76c = 1;
            }
        }
        if (m_reactState == 2) {
            const CKS08EnemyCpnt* kind = m_pEnemyCpnt;
            bool shattered = false;
            if (m_fIceGauge >= kind->m_unk2bc && kind->m_unk2b4 == 100.0f && m_pPendingDamage != nullptr &&  // TOC 0x1520
                m_pPendingDamage->IsKindOfClass(0x99cc) != 0 &&
                static_cast<CKS08ElementDamage*>(m_pPendingDamage)->m_afValues[1] == zero) {
                shattered = true;
            }
            if (shattered) {
                m_fHealth = m_fHealth - m_pEnemyCpnt->m_unk2c0;
                SetFreezeFxActive(0, -1);
                m_fIceGauge = zero;
            } else {
                const float step = FrozenStep(m_pEnemyCpnt, m_fIceGauge, dt);
                m_fScaledDt = step;
                if (step <= zero) {
                    m_fKnockbackTime = zero;
                    m_unk76c = 1;
                }
            }
        } else if (m_mainState == 7) {
            const CKS08EnemyCpnt* kind = m_pEnemyCpnt;
            if (m_fIceGauge >= kind->m_unk2bc && kind->m_unk2b4 == 100.0f) {
                m_fHealth = m_fHealth - kind->m_unk2c0;
                PlayFxAtHotspot1(0xb);  // 0x0028d4a8
            }
            SetFreezeFxActive(0, -1);
            m_fIceGauge = zero;
        }
    }
    if (m_bPendingHit != 0 && m_pPendingDamage->IsKindOfClass(0x99cc) == 0) PlaySound(0x22, 0, m_pKGLObject);  // 0x002795c0
}

// 0x002afff0 CKHkS08Enemy_SpreadPoisonToNearby: every other active enemy of the enemy group (the count read once, the
// list again for each) within `radiusSquared` (xz) gets `amount` of poison (AddPoisonGauge) and +0x7b5 = 1.
void CKHkS08Enemy::SpreadPoisonToNearby(float amount, float radiusSquared) {
    const uint32_t count = enemy::EnemyGroup()->m_ui32NbActiveEnemies;  // 0x00276f58
    for (uint32_t i = 0; i < count; ++i) {
        CKHkS08Enemy* other = static_cast<CKHkS08Enemy*>(enemy::EnemyGroup()->m_apActiveEnemies[i]);
        if (other == this) continue;
        const float dz = m_v3Position.z - other->m_v3Position.z;
        const float dx = m_v3Position.x - other->m_v3Position.x;
        if (!(ppc::fmadds(dx, dx, dz * dz) <= radiusSquared)) continue;
        other->AddPoisonGauge(amount);  // 0x0027ceb8
        other->m_unk7b5 = 1;
    }
}

// 0x002affa0 StaticInitAndDestruction_2affa0: two file statics (0x00cead64, 0x00cead68) set to -1.0f. Nothing in the game
// reads them (their only references are the initialiser's TOC entries).
namespace {
[[maybe_unused]] float s_unkcead64 = -1.0f;
[[maybe_unused]] float s_unkcead68 = -1.0f;
}  // namespace
