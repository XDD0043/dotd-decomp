// Reconstructed original translation unit: 0x2aeb48-0x2af730 (GAME_TOC1, main_toc1), 6 functions, 6 live.
// Primary class: CKHkS08Enemy  key 0x26c2  category Hook  size 0x8f8  vtable 0xb22078
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2aeb48  CKHkS08Enemy_SetFireLoopSoundActive_maybe
//   [x] 0x2aebe0  StaticInitAndDestruction_2aebe0  (the two file statics at the end)
//   [ ] 0x2aec10  _GLOBAL__D_2aec10
//   [ ] 0x2aec20  _GLOBAL__I_2aec20
//   [x] 0x2aec30  CKHkS08Enemy_SetBurning
//   [x] 0x2aeec8  CKHkS08Enemy_UpdateStatus0Dot_maybe
#include "Spyro2008/hooks/CKHkS08Enemy.h"

#include "Spyro2008/components/CKS08EnemyCpnt.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "crt/ppc_ops.h"
#include "k2000/ai/CKSrvPathFinding.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/IKGrpEnemy.h"
#include "k2000/misc/OnNewHit.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/system/IKTime.h"

namespace {
// 0x00a703c0 (TOC 0x14c4): per enemy kind, the hot spots the status particles use.
const uint8_t kFireHotSpotCount[9] = {7, 10, 14, 13, 14, 17, 25, 17, 12};
}  // namespace

// 0x002aeec8 CKHkS08Enemy_UpdateStatus0Dot_maybe: nothing while the burning gauge (+0x6b8) is empty. The health burns
// ((1 - the kind's +0x268 / 100) x +0x288 x the time scale +0x1fc); the gauge capped at the kind's +0x244; the fire loop
// sound on. A full gauge sets the enemy burning (SetBurning) when its point is walkable in its nav node and its ground
// is not more than 0.2 below. The gauge drains by dt x the first dragon's status decay rate unless a fire (element 0)
// damage is pending; empty: 0, +0x7b7 cleared, the loop sound and the burning stopped. Else the fire particles (0 and
// 0xe, and 1 while burning) at the kind's hot spots; a spreading fire (+0x7b7) feeds the active enemies within the
// kind's +0x26c (squared, flat) and marks them spreading too; every +0x538 seconds (+0x84c) a hit is counted for the
// last attacking dragon (+0x694; dragon 0 without one) at hot spot 1.
void CKHkS08Enemy::UpdateStatus0Dot(IKTime* clock) {
    const float zero = 0.0f;  // TOC 0x14c8
    if (m_fFireGauge <= zero) return;
    const CKS08EnemyCpnt* kind = m_pEnemyCpnt;
    float burn = kind->m_unk268 / -100.0f;  // TOC 0x14b8
    burn = burn + 1.0f;                      // TOC 0x1490
    burn = burn * kind->m_unk288;
    burn = burn * m_fScaledDt;
    m_fHealth = m_fHealth - burn;
    if (m_fFireGauge > kind->m_unk244) m_fFireGauge = kind->m_unk244;
    if ((m_bitArray & 0x800u) == 0 && !(m_fFireGauge <= zero)) {
        m_bitArray = (m_bitArray & 0xfffff7ffu) | 0x800u;
        PlaySound(0x14, 1, m_pKGLObject);  // 0x002795c0
    }
    if ((m_bitArray & 0x2000000u) == 0 && m_fFireGauge >= m_pEnemyCpnt->m_unk244) {  // fcmpu + cror gt|eq
        CKSrvPathFinding* pathFinding = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);  // TOC 0x14bc
        CPFPoint point;
        point.m_i16GraphNodeIndex = 0xffff;
        point.m_position = m_v3Position;
        point.m_i16GraphNodeIndex = m_PFCpnt.m_Destination.m_i16GraphNodeIndex;
        pathFinding->FindSectorForPoint(&point);  // 0x001e5ca0
        uint8_t walkable = 0;
        if (PointInNodeBox(pathFinding, &point)) {
            walkable = static_cast<uint8_t>(pathFinding->IsPointWalkable(&point, &m_PFCpnt.m_CharacterType));  // 0x001e42d0
        }
        CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
        collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &m_v3Position.x, 1);  // 0x00196540
        const bool high = m_GrdContDatasInOut.m_eContactStatus == 0 && m_GrdContDatasInOut.m_fdH > 0.2f;  // TOC 0x14c0
        if (!high && walkable != 0) SetBurning(1);  // 0x002aec30
    }
    if (!PendingElementDamageIs(0)) {
        const float dt = clock->m_afDeltaTime[0];
        const float gauge = m_fFireGauge;
        m_fFireGauge = gauge - dt * HeroStatusDecayRate(0);  // 0x0032a3d0
    }
    if (m_fFireGauge <= zero) {
        m_fFireGauge = zero;
        m_unk7b7 = 0;
        if ((m_bitArray & 0x800u) != 0) {
            m_bitArray &= 0xfffff7ffu;
            StopSound(0x14);  // 0x002794f0
        }
        if ((m_bitArray & 0x2000000u) != 0) SetBurning(0);
        return;
    }
    CVector3 unused;
    GetHotSpot(1)->GetWorldPosition(&unused);  // 0x002892e8, 0x000ce790 (not read)
    const bool burning = (m_bitArray & 0x2000000u) != 0;
    const uint8_t count = kFireHotSpotCount[m_ui8EnemyClassType];
    for (uint32_t i = 0; i < count; ++i) {
        if (m_ui8EnemyClassType == 1 && i - 6u <= 3u) continue;
        CVector3 hotSpot;
        GetHotSpot(static_cast<int32_t>(i))->GetWorldPosition(&hotSpot);
        const CVector3 a = hotSpot;
        EmitParticleAt(0, &a, nullptr, 0);  // 0x00278028
        if (burning) {
            const CVector3 b = hotSpot;
            EmitParticleAt(1, &b, nullptr, 0);
        }
        const CVector3 c = hotSpot;
        EmitParticleAt(0xe, &c, nullptr, 0);
    }
    if (m_unk7b7 != 0) {
        IKGrpEnemy* group = static_cast<IKGrpEnemy*>(g_pEngine->m_gameManager->m_unk04[0]);  // GetEnemyGroup 0x276f58
        const uint32_t active = group->m_ui32NbActiveEnemies;
        for (uint32_t i = 0; i < active; ++i) {
            CKHkS08Enemy* other = static_cast<CKHkS08Enemy*>(group->m_apActiveEnemies[i]);
            if (other == this) continue;
            const float dz = m_v3Position.z - other->m_v3Position.z;
            const float dx = m_v3Position.x - other->m_v3Position.x;
            if (ppc::fmadds(dx, dx, dz * dz) <= m_pEnemyCpnt->m_unk26c) {  // cror lt|eq
                other->AddBurnGauge(m_fFireGauge * m_pEnemyCpnt->m_unk270 * m_fScaledDt);  // 0x0027ce90
                other->m_unk7b7 = 1;
            }
        }
    }
    m_unk84c = m_unk84c + clock->m_afDeltaTime[0];
    if (m_pEnemyCpnt->m_unk538 <= m_unk84c) {  // cror lt|eq
        m_unk84c = 0.0f;
        CVector3 at;
        GetHotSpot(1)->GetWorldPosition(&at);
        IKSerializable* attacker = static_cast<IKSerializable*>(m_pLastAttacker);
        CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);  // TOC 0x14bc -> +0x8c
        if (attacker != nullptr && attacker->IsKindOfClass(0x25c2) != 0) {
            const uint8_t dragon = static_cast<CKHkS08Hero*>(attacker)->GetDragonIndex();  // 0x00361960
            OnNewHitW(manager, dragon, &at);  // 0x004fe568
        } else {
            OnNewHitW(manager, 0, &at);
        }
    }
}

// 0x002aeb48 CKHkS08Enemy_SetFireLoopSoundActive_maybe: flag 0x800 of +0x0c follows `on` (the whole word compared with
// the bit); on a change the looping sound 0x14 starts (at the enemy's node) or stops.
void CKHkS08Enemy::SetFireLoopSoundActive(uint32_t on) {
    if (on == ((m_bitArray >> 11) & 1u)) return;
    m_bitArray = (m_bitArray & 0xfffff7ffu) | (on << 11);
    if (on != 0) {
        PlaySound(0x14, 1, m_pKGLObject);  // 0x002795c0
    } else {
        StopSound(0x14);  // 0x002794f0
    }
}

// 0x002aec30 CKHkS08Enemy_SetBurning: except for the flying kind's enemies (+0x7b4), flag 0x2000000 of +0x0c follows
// `on`; set on: the FX 4 at hot spot 1 and, unless dying (0x15) or in the death reaction (0xf), the main state 0x26
// (the kind's +0x28c clear) or 0x1a (no clock), the animation speed +0x774 back to 1.
void CKHkS08Enemy::SetBurning(uint8_t on) {
    if (m_unk7b4 != 0) return;
    if (static_cast<uint32_t>(on) == ((m_bitArray >> 25) & 1u)) return;
    m_bitArray = (m_bitArray & 0xfdffffffu) | (static_cast<uint32_t>(on) << 25);
    if (on == 0) return;
    PlayFxAtHotspot1(4);  // 0x0028d4a8
    if (m_mainState == 0x15 || m_reactState == 0xf) return;
    SwitchMainState(m_pEnemyCpnt->m_unk28c == 0 ? 0x26 : 0x1a, nullptr);
    m_unk774 = 1.0f;  // TOC +0x1490
}

// 0x002aebe0 StaticInitAndDestruction_2aebe0: two file statics (0x00cead54, 0x00cead58) set to -1.0f. Nothing in the game
// reads them (their only references are the initialiser's TOC entries).
namespace {
[[maybe_unused]] float s_unkcead54 = -1.0f;
[[maybe_unused]] float s_unkcead58 = -1.0f;
}  // namespace
