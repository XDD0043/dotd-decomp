// Reconstructed original translation unit: 0x2b0170-0x2b09d0 (GAME_TOC1, main_toc1), 1 functions, 1 live.
// Primary class: CKHkS08Enemy  key 0x26c2  category Hook  size 0x8f8  vtable 0xb22078
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2b0170  CKHkS08Enemy_UpdatePoisonStatus
#include "Spyro2008/hooks/CKHkS08Enemy.h"

#include <cmath>

#include "Spyro2008/components/CKS08EnemyCpnt.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "crt/ppc_ops.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/IKGrpEnemy.h"
#include "k2000/misc/OnNewHit.h"
#include "k2000/system/IKTime.h"

namespace {
// 0x00a703e0 (TOC 0x15f8): per enemy kind, the hot spots the status particles use.
const uint8_t kPoisonHotSpotCount[9] = {7, 10, 14, 13, 14, 17, 25, 17, 12};
}  // namespace

// 0x002b0170 CKHkS08Enemy_UpdatePoisonStatus: nothing while the poison gauge (+0x6c0) is empty. The speed (+0x158) is
// capped at the kind's +0x2ac (+0x394 cleared then); the gauge drains by dt x the second dragon's status decay rate
// unless a poison (element 4) damage is pending; empty: 0, +0x7b5 cleared and the poison sound (0x20) stopped. Else the
// poison particles (2, 3, 0xf) at the kind's hot spots and the health eaten (the +0x188 kind's +0x2a0 x the time scale
// +0x1fc): at 0 the kinds 5 / 6 take the reaction 0xf and the main state 2 (unless dying or in it), the others the
// main state 0x15. A spreading poison (+0x7b5) feeds the active enemies within the kind's +0x298 (squared, flat) and
// marks them spreading too. Every +0x53c seconds (+0x84c) a hit is counted for the second dragon at hot spot 1.
void CKHkS08Enemy::UpdatePoisonStatus(IKTime* clock) {
    const float zero = 0.0f;  // TOC 0x1600
    if (m_unk6c0 <= zero) return;
    CVector3& speed = m_unk158;
    const float length = std::sqrt(ppc::fmadds(speed.z, speed.z, ppc::fmadds(speed.x, speed.x, speed.y * speed.y)));
    if (m_unk884->m_unk2ac < length) {
        // The original stores a word at +0x394: the four bytes +0x394..+0x397 cleared.
        m_unk394 = 0;
        m_unk395 = 0;
        m_unk396 = 0;
        m_unk397 = 0;
        const float again = std::sqrt(ppc::fmadds(speed.z, speed.z, ppc::fmadds(speed.x, speed.x, speed.y * speed.y)));
        if (again != zero) {
            const float k = 1.0f / again;  // TOC 0x15f4
            speed.z = k * speed.z;
            speed.x = k * speed.x;
            speed.y = k * speed.y;
        }
        const float cap = m_unk884->m_unk2ac;
        speed.z = cap * speed.z;
        speed.x = cap * speed.x;
        speed.y = cap * speed.y;
    }
    if (!PendingElementDamageIs(4)) {
        const float dt = clock->m_afDeltaTime[0];
        const float gauge = m_unk6c0;
        m_unk6c0 = gauge - dt * HeroStatusDecayRate(1);  // 0x0032a3d0
    }
    if (m_unk6c0 <= zero) {
        m_unk6c0 = zero;
        m_unk7b5 = 0;
        StopSound(0x20);  // 0x002794f0
        return;
    }
    CVector3 hotSpot1;
    GetHotSpot(1)->GetWorldPosition(&hotSpot1);  // 0x002892e8, 0x000ce790
    const uint8_t count = kPoisonHotSpotCount[m_ui8EnemyClassType];
    for (uint32_t i = 0; i < count; ++i) {
        if (m_ui8EnemyClassType == 1 && i - 6u <= 3u) continue;
        CVector3 hotSpot;
        GetHotSpot(static_cast<int32_t>(i))->GetWorldPosition(&hotSpot);
        const CVector3 a = hotSpot;
        EmitParticleAt(2, &a, nullptr, 0);  // 0x00278028
        const CVector3 b = hotSpot;
        EmitParticleAt(3, &b, nullptr, 0);
        const CVector3 c = hotSpot;
        EmitParticleAt(0xf, &c, nullptr, 0);
    }
    const float health = m_unk258 - m_unk188->m_unk2a0 * m_unk1fc;
    m_unk258 = health;
    if (health <= zero) {
        m_unk258 = zero;
        if (static_cast<uint32_t>(m_ui8EnemyClassType) - 5u <= 1u) {
            if (m_mainState != 0x15 && m_mainState != 2) {
                SwitchReactState(0xf, nullptr);
                SwitchMainState(2, nullptr);
            }
        } else if (m_mainState != 0x15) {
            SwitchMainState(0x15, nullptr);
        }
    }
    if (m_unk7b5 != 0) {
        const float amount = m_unk6c0 * m_unk1fc;
        const float range = m_unk188->m_unk298;
        IKGrpEnemy* group = static_cast<IKGrpEnemy*>(g_pEngine->m_gameManager->m_unk04[0]);  // GetEnemyGroup 0x276f58
        const uint32_t active = group->m_ui32NbActiveEnemies;
        for (uint32_t i = 0; i < active; ++i) {
            CKHkS08Enemy* other = static_cast<CKHkS08Enemy*>(group->m_apActiveEnemies[i]);
            if (other == this) continue;
            const float dz = m_v3Position.z - other->m_v3Position.z;
            const float dx = m_v3Position.x - other->m_v3Position.x;
            if (ppc::fmadds(dx, dx, dz * dz) <= range) {  // cror lt|eq
                other->AddPoisonGauge(amount);  // 0x0027ceb8
                other->m_unk7b5 = 1;
            }
        }
    }
    m_unk84c = m_unk84c + clock->m_afDeltaTime[0];
    if (m_unk188->m_unk53c <= m_unk84c) {  // cror lt|eq
        m_unk84c = 0.0f;
        CVector3 at;
        GetHotSpot(1)->GetWorldPosition(&at);
        OnNewHitW(static_cast<CKS08GameManager*>(g_pEngine->m_gameManager), 1, &at);  // 0x004fe568
    }
}
