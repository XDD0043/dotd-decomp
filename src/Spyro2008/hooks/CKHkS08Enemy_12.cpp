// Reconstructed original translation unit: 0x2ae370-0x2aeaf8 (GAME_TOC1, main_toc1), 3 functions, 3 live.
// Primary class: CKHkS08Enemy  key 0x26c2  category Hook  size 0x8f8  vtable 0xb22078
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2ae370  CKHkS08Enemy_UpdateStunStatus
//   [x] 0x2ae5e8  CKHkS08Enemy_SpreadStunToNearby
//   [x] 0x2ae718  CKHkS08Enemy_UpdateShadowStatus
#include <cmath>
#include "k2000/services/CKSrvCollision.h"
#include "Renderware/rwcore/RwCamera.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/animation/AnimBlendSlot.h"
#include "k2000/graphical/CKAnmKeyFrameController.h"
#include "k2000/components/CKEnemySectorCpnt.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/math/Math.h"
#include "Spyro2008/hooks/CKHkS08EnemyShared.h"
#include <cstring>
#include "k2000/core/Stub.h"
#include "crt/ppc_ops.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/fx/IKFx.h"
#include "k2000/services/CKSrvFx.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/groups/CKGrpS08Enemy.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/logic/CKS08ElementDamage.h"
#include "Spyro2008/logic/CKS08HeroDamage.h"
#include "k2000/components/CKBonusData.h"
#include "k2000/misc/OnNewHit.h"
#include "Spyro2008/hooks/CKHkS08Enemy.h"

#include "Spyro2008/components/CKS08EnemyCpnt.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/system/IKTime.h"

namespace {
// 0x00a703b0 (TOC 0x1430): per enemy kind, the hot spots the status particles use.
const uint8_t kEnemyStatusHotSpotCount[9] = {7, 10, 14, 13, 14, 17, 25, 17, 12};
}  // namespace

// 0x002ae370 CKHkS08Enemy_UpdateStunStatus: nothing while the stun gauge (+0x6d4) is empty. Else the enemy is sent to the
// stunned main state 0x1f (unless in it, dying 0x15, without a state, or in the hit reaction 0x0f), and the gauge drains
// by dt x the first dragon's status decay rate unless an electric (element 3) damage is pending; empty: 0 and +0x7b6
// cleared.
void CKHkS08Enemy::UpdateStunStatus(IKTime* clock) {
    if (m_unk6d4 <= 0.0f) return;  // TOC 0x13e0
    const uint8_t state = m_mainState;
    if (state != 0x1f && state != 0x15 && state != 0xff && m_reactState != 0xf) SwitchMainState(0x1f, clock);
    if (!PendingElementDamageIs(3)) {
        const float dt = clock->m_afDeltaTime[0];
        const float gauge = m_unk6d4;
        const float drain = dt * HeroStatusDecayRate(0);
        m_unk6d4 = gauge - drain;
    }
    if (m_unk6d4 <= 0.0f) {
        m_unk6d4 = 0.0f;
        m_unk7b6 = 0;
    }
}

// 0x002ae718 CKHkS08Enemy_UpdateShadowStatus: the shadow gauge (+0x6c4). Reaching the config's +0x250 the first time
// starts the shadow FX (hot spot 1, FX 0x11) and sets +0x709; the gauge drains by dt x the second dragon's decay rate
// unless a shadow (element 5) damage is pending; empty: 0, +0x709 cleared and nothing more; while +0x709 the status
// particles 8 at the kind's hot spots (the kind 1 skips 6..9). An empty gauge without +0x709 skips to the end: with the
// fear gauge (+0x6cc) up in the main state 1, the main state 0x24.
void CKHkS08Enemy::UpdateShadowStatus(IKTime* clock) {
    const float gauge = m_unk6c4;
    bool drain = true;
    if (gauge > 0.0f) {  // TOC 0x1434
        if (m_unk709 == 0 && m_unk884->m_unk250 <= gauge) {
            PlayFxAtHotspot1(0x11);  // 0x0028d4a8
            m_unk709 = 1;
        }
    } else if (m_unk709 == 0) {
        drain = false;
    }
    if (drain) {
        if (!PendingElementDamageIs(5)) {
            const float dt = clock->m_afDeltaTime[0];
            const float now = m_unk6c4;
            m_unk6c4 = now - dt * HeroStatusDecayRate(1);
        }
        if (m_unk6c4 <= 0.0f) {
            m_unk6c4 = 0.0f;
            m_unk709 = 0;
            return;
        }
        if (m_unk709 != 0) {
            const uint8_t count = kEnemyStatusHotSpotCount[m_ui8EnemyClassType];
            for (uint32_t i = 0; i < count; ++i) {
                if (m_ui8EnemyClassType == 1 && i - 6u <= 3u) continue;
                CVector3 hotSpot;
                static_cast<CSGHotSpot*>(GetHotSpot(i))->GetWorldPosition(&hotSpot);
                const CVector3 at = hotSpot;
                EmitParticleAt(8, &at, nullptr, 0);  // 0x00278028
            }
        }
    }
    if (m_unk6cc > 0.0f && m_mainState == 1) SwitchMainState(0x24, clock);
}

// 0x00288b18 CKHkS08Enemy_ApplyElementResistance: the pending element damage's amount less the kind's resistances in
// percent (x (1 + r / -100), TOC +0xd54 -100, +0xd58 1): element value 0 (+0x268), 4 (+0x294), 1 (+0x2b8), the
// ability id 4 / 5 (+0x2d0), value 7 (+0x2e8), value 6 (+0x2f4) and the damage type 3 (+0x314). The value tests are
// `ble` without cror (a NaN value counts as above 0).
float CKHkS08Enemy::ApplyElementResistance(float amount) {
    const CKS08ElementDamage* damage = static_cast<const CKS08ElementDamage*>(m_unk27c);
    const float* v = damage->m_afValues;
    auto resist = [](float value, float percent) { return value * (percent / -100.0f + 1.0f); };
    if (!(v[0] <= 0.0f)) amount = resist(amount, m_unk884->m_unk268);
    if (!(v[4] <= 0.0f)) amount = resist(amount, m_unk884->m_unk294);
    if (!(v[1] <= 0.0f)) amount = resist(amount, m_unk884->m_unk2b8);
    if (damage->m_unk38 == 4 || damage->m_unk38 == 5) amount = resist(amount, m_unk884->m_unk2d0);
    if (!(v[7] <= 0.0f)) amount = resist(amount, m_unk884->m_unk2e8);
    if (!(v[6] <= 0.0f)) amount = resist(amount, m_unk884->m_unk2f4);
    if (damage->m_unk20 == 3) amount = resist(amount, m_unk884->m_unk314);
    return amount;
}

namespace {
// 0x00a70130: the number of hot spots of each enemy kind PlayFxOnAllHotspots covers.
constexpr uint8_t kKindFxHotSpots[9] = {7, 10, 14, 13, 14, 17, 25, 17, 12};
}  // namespace

// 0x0028da80 CKHkS08Enemy_PlayFxOnAllHotspots_maybe: one explosion of the kind's FX `fx` (+0x128) from the pool at each
// of the kind's hot spots but hot spot 3 (it still counts).
void CKHkS08Enemy::PlayFxOnAllHotspots(uint32_t fx) {
    const uint32_t count = kKindFxHotSpots[m_ui8EnemyClassType];
    for (uint32_t i = 0; i < count; ++i) {
        if (i == 3) continue;
        CVector3 at;
        GetHotSpot(static_cast<int32_t>(i))->GetWorldPosition(&at);  // 0x002892e8, 0x000ce790
        SpawnHitFxAt(fx, &at);
    }
}

// 0x0028c590 CKHkS08Enemy_SpawnHitFx_maybe: one explosion of the kind's FX `fx` (+0x128) from the FX pool set off at
// `at`.
void CKHkS08Enemy::SpawnHitFxAt(uint32_t fx, const CVector3* at) {
    IKFxData* data = static_cast<IKFxData*>(m_unk884->m_vUnk128.m_pBlock[fx]);
    IKFx* effect = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(data, this);
    if (effect == nullptr) return;
    CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(effect);
    explosion->SetTranslation(at, this);  // 0x001b66e8
    explosion->Trigger(this, 0);          // 0x001b82a8
    explosion->ReleaseReservation(this);  // vt+0x54
}

// DOTD: ApplyPendingDamage's element gauges (0x0029a4c4): the first hit of an element starts its FX / sound (fire +0x6c0
// with value 4: FX 5 at hot spot 1, +0x84c cleared, the looping sound 0x20; burn +0x6b8 with value 0: +0x84c cleared;
// ice +0x6c8 with value 1: FX 7; poison +0x6d0 with value 7: +0x704 cleared); the element's level (+0x34) kept by type
// (4 +0x7b5, 3 +0x7b6, 0 +0x7b7, 7 +0x7b8); any other element on a burning enemy puts the fire out (+0x7b5, the sound
// 0x20 stopped). Then the first element value above 0 (in the order 0, 4, 1, 6, 7, 3, 5) feeds its gauge by the value
// x the kind's factor (x dt for a held damage) and clears the others (ice also its FX; the kinds 5 / 6 take the shadow
// value as it is).
void CKHkS08Enemy::ApplyElementGauges(IKTime* clock) {
    CKS08ElementDamage* e = static_cast<CKS08ElementDamage*>(m_unk27c);
    const float* v = e->m_afValues;
    if (m_unk6c0 == 0.0f && v[4] > 0.0f) {
        PlayFxAtHotspot1(5);  // 0x0028d4a8
        m_unk84c = 0.0f;
        PlaySound(0x20, 1, m_pKGLObject);  // 0x002795c0
    }
    if (m_unk6b8 == 0.0f && v[0] > 0.0f) m_unk84c = 0.0f;
    if (m_unk6c8 == 0.0f && v[1] > 0.0f) PlayFxAtHotspot1(7);
    if (m_unk6d0 == 0.0f && v[7] > 0.0f) m_unk704 = 0.0f;
    if (e->m_unk20 == 4) m_unk7b5 = e->m_unk34;
    if (e->m_unk20 == 3) m_unk7b6 = e->m_unk34;
    if (e->m_unk20 == 0) m_unk7b7 = e->m_unk34;
    if (e->m_unk20 == 7) m_unk7b8 = e->m_unk34;
    if (m_unk6c0 > 0.0f &&
        (v[0] > 0.0f || v[1] > 0.0f || v[6] > 0.0f || v[7] > 0.0f || v[3] > 0.0f || v[5] > 0.0f)) {
        m_unk7b5 = 0;
        StopSound(0x20);  // 0x002794f0
    }
    const float scale = e->m_unk0c != 0 ? clock->m_afDeltaTime[0] : 1.0f;  // TOC +0x1094
    const CKS08EnemyCpnt* cfg = m_unk884;
    if (v[0] > 0.0f) {
        const float add = v[0] * cfg->m_unk264;
        m_unk6d4 = 0.0f;
        m_unk6c0 = 0.0f;
        m_unk6c4 = 0.0f;
        m_unk6c8 = 0.0f;
        m_unk6cc = 0.0f;
        m_unk6d0 = 0.0f;
        m_unk6b8 = ppc::fmadds(scale, add, m_unk6b8);
    } else if (v[4] > 0.0f) {
        m_unk6b8 = 0.0f;
        const float add = v[4] * cfg->m_unk290;
        m_unk6d4 = 0.0f;
        m_unk6c4 = 0.0f;
        m_unk6c8 = 0.0f;
        m_unk6cc = 0.0f;
        m_unk6d0 = 0.0f;
        m_unk6c0 = ppc::fmadds(scale, add, m_unk6c0);
    } else if (v[1] > 0.0f) {
        m_unk6b8 = 0.0f;
        m_unk6c0 = 0.0f;
        m_unk6c4 = 0.0f;
        const float add = v[1] * cfg->m_unk2b0;
        m_unk6d4 = 0.0f;
        m_unk6cc = 0.0f;
        m_unk6d0 = 0.0f;
        m_unk6c8 = ppc::fmadds(scale, add, m_unk6c8);
        // 0x0029ba34: the freeze FX off, then (none held) on at the kind's hot spot nearest the hit point (+0x23c; hot
        // spot 3 skipped, the count from 0x00a70210 = TOC +0x10e4 +0x28; -1, i.e. hot spot 1, when none is nearer than
        // FLT_MAX).
        SetFreezeFxActive(0, -1);  // 0x0028cb88
        if (m_unk878 == nullptr) {
            const uint32_t count = kKindFxHotSpots[m_ui8EnemyClassType];
            float best = 3.4028235e+38f;  // 0x00c4acb8 +0x28 (TOC +0x1108)
            int32_t nearest = -1;
            for (uint32_t i = 0; i < count; ++i) {
                CSGHotSpot* hotSpot = GetHotSpot(static_cast<int32_t>(i));  // 0x002892e8
                if (i == 3 || hotSpot == nullptr) continue;
                CVector3 at;
                hotSpot->GetWorldPosition(&at);  // 0x000ce790
                const float dx = at.x - m_unk23c[0];
                const float dy = at.y - m_unk23c[1];
                const float dz = at.z - m_unk23c[2];
                const float distance = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
                if (!(best <= distance)) {  // ble
                    best = distance;
                    nearest = static_cast<int32_t>(i);
                }
            }
            SetFreezeFxActive(1, nearest);
        }
    } else if (v[6] > 0.0f) {
        m_unk6b8 = 0.0f;
        m_unk6c0 = 0.0f;
        m_unk6c4 = 0.0f;
        m_unk6c8 = 0.0f;
        if (static_cast<uint8_t>(m_ui8EnemyClassType - 5) <= 1) {
            m_unk6cc = ppc::fmadds(scale, v[6] * 0.0f, m_unk6cc);  // TOC +0x1098 (f11, 0)
        } else {
            m_unk6cc = ppc::fmadds(scale, v[6] * cfg->m_unk2f0, m_unk6cc);
        }
        m_unk6d4 = 0.0f;
        m_unk6d0 = 0.0f;
    } else if (v[7] > 0.0f) {
        m_unk6b8 = 0.0f;
        m_unk6c0 = 0.0f;
        m_unk6c4 = 0.0f;
        m_unk6c8 = 0.0f;
        m_unk6cc = 0.0f;
        const float add = v[7] * cfg->m_unk2e4;
        m_unk6d4 = 0.0f;
        m_unk6d0 = ppc::fmadds(scale, add, m_unk6d0);
    } else if (v[3] > 0.0f) {
        m_unk6d0 = 0.0f;
        m_unk6b8 = 0.0f;
        m_unk6c0 = 0.0f;
        m_unk6c4 = 0.0f;
        m_unk6c8 = 0.0f;
        m_unk6cc = 0.0f;
        m_unk6d4 = ppc::fmadds(scale, v[3] * cfg->m_unk320, m_unk6d4);
    } else if (v[5] > 0.0f) {
        m_unk6b8 = 0.0f;
        m_unk6c0 = 0.0f;
        const float add = v[5] * cfg->m_unk2f0;
        m_unk6d4 = 0.0f;
        m_unk6c8 = 0.0f;
        m_unk6cc = 0.0f;
        m_unk6d0 = 0.0f;
        m_unk6c4 = ppc::fmadds(scale, add, m_unk6c4);
    }
}

namespace {
// A random chance: the next draw's low 16 bits over 65535 below `p` (TOC +0x110c).
bool RandomBelow(float p) {
    const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;  // 0x00011500
    return static_cast<float>(static_cast<double>(r)) / 65535.0f < p;
}
}  // namespace

// DOTD: ApplyPendingDamage's hit sounds (0x0029a60c). A plain damage: a hurt sound (2 + a random 0..3) and, at 20%, a
// voice (7 + a random 0..3). An element damage by its type: 1 the sound 0x15 and the same voice chance, 0 a voice at
// 1%, 3 at 20%, the others none. Then the element's impact by its +0x38: 10 the sound 0x29, 14 0x28, 0 0x1d.
void CKHkS08Enemy::PlayHitSounds() {
    CKS08Damage* damage = m_unk27c;
    if (damage->IsKindOfClass(0x99cc) == 0) {
        const int32_t r = Rand_Int();
        PlaySound(static_cast<uint8_t>(2 + ((static_cast<uint32_t>(r) >> 14) & 3u)), 0, m_pKGLObject);  // 0x002795c0
        if (RandomBelow(0.2f)) {  // TOC +0x1110
            const int32_t v = Rand_Int();
            PlaySound(static_cast<uint8_t>(7 + ((static_cast<uint32_t>(v) >> 14) & 3u)), 0, m_pKGLObject);
        }
    } else {
        const int32_t type = damage->m_unk20;
        if (type == 1) {
            PlaySound(0x15, 0, m_pKGLObject);
            if (RandomBelow(0.2f)) {
                const int32_t v = Rand_Int();
                PlaySound(static_cast<uint8_t>(7 + ((static_cast<uint32_t>(v) >> 14) & 3u)), 0, m_pKGLObject);
            }
        } else if (type == 0 || type == 3) {
            if (RandomBelow(type == 0 ? 0.00999999977648258f : 0.2f)) {  // TOC +0x10d4 / +0x1110
                const int32_t v = Rand_Int();
                PlaySound(static_cast<uint8_t>(7 + ((static_cast<uint32_t>(v) >> 14) & 3u)), 0, m_pKGLObject);
            }
        }
    }
    damage = m_unk27c;
    if (damage->IsKindOfClass(0x99cc) != 0) {
        const int32_t impact = static_cast<CKS08ElementDamage*>(damage)->m_unk38;
        if (impact == 10) {
            PlaySound(0x29, 0, m_pKGLObject);
        } else if (impact == 14) {
            PlaySound(0x28, 0, m_pKGLObject);
        } else if (impact == 0) {
            PlaySound(0x1d, 0, m_pKGLObject);
        }
    }
}

// DOTD: ApplyPendingDamage's held element hits (0x0029af40, the jump table 0x0029af6c on the ability id +0x38). The
// ability gives the hit FX interval and the sound interval: fire breath 1 (the kind's +0x520 over the group's level
// value of list 0 for dragon 0's level of the ability; the sound interval a draw between the group's +0x238 and
// +0x248), 9 (+0x52c, list 2, dragon 0, +0x240..+0x250), 13 (+0x524, list 1, dragon 1, +0x23c..+0x24c), 16 (+0x528,
// list 3, dragon 1, +0x244..+0x254); 7 (+0x534) and 17 / 18 (+0x530) a fixed FX interval with a 0.1 s sound interval;
// the others 0.5 s / 0.1 s (TOC +0x1118 / +0x109c). Past the FX interval (+0x7e0) the hit counts in the attacker's
// combo (OnNewHitW) and the hit FX plays; past the sound interval (+0x8b4) the ability's sound (1 0x26, 9 0x25, 13
// 0x27, 16 0x24).
void CKHkS08Enemy::CountHeldElementHit(CKS08GameManager* manager, const CVector3* point) {
    const CKS08ElementDamage* damage = static_cast<const CKS08ElementDamage*>(m_unk27c);
    const uint32_t id = static_cast<uint32_t>(damage->m_unk38);
    const CKS08EnemyCpnt* cfg = m_unk884;
    float soundInterval = 0.100000001f;  // TOC +0x109c
    float fxInterval = 0.5f;             // TOC +0x1118
    // The levelled cases: the kind's interval over the group's value (vt+0x184..+0x190) of the element level of the
    // ability for the dragon, then a random sound interval in [low, high] (Rand_Int's low 16 bits over 65535).
    auto levelled = [&](float interval, uint32_t list, uint32_t dragon, uint32_t low, uint32_t high) {
        CKGrpS08Enemy* group = static_cast<CKGrpS08Enemy*>(enemy::EnemyGroup());  // 0x00276f58
        CKGrpS08Hero* heroes = static_cast<CKGrpS08Hero*>(g_pEngine->m_gameManager->m_unk04[1]);  // +0x8c -> +0x08
        CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(heroes->m_apHeros[dragon]);  // GetHeroByDragonIndex 0x002ca080
        const uint8_t level = hero->GetAbilityElementLevel(static_cast<uint8_t>(id));  // 0x0032a8d0 (+0x3b, the low byte)
        fxInterval = interval / group->GetElementLevelValue(list, level);
        const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;  // 0x00011500
        const float range = group->m_unk238[high] - group->m_unk238[low];
        const float u = static_cast<float>(static_cast<double>(r)) / 65535.0f;  // TOC +0x110c
        soundInterval = u * range + group->m_unk238[low];
    };
    switch (id) {
    case 1: levelled(cfg->m_unk520, 0, 0, 0, 4); break;
    case 7: fxInterval = cfg->m_unk534; break;
    case 9: levelled(cfg->m_unk52c, 2, 0, 2, 6); break;
    case 13: levelled(cfg->m_unk524, 1, 1, 1, 5); break;
    case 16: levelled(cfg->m_unk528, 3, 1, 3, 7); break;
    case 17:
    case 18: fxInterval = cfg->m_unk530; break;
    default: break;
    }
    if (m_unk7e0 > fxInterval) {  // bgt
        OnNewHitW(manager, static_cast<CKHkS08Hero*>(static_cast<IKSerializable*>(m_unk694))->GetDragonIndex(),
                  point);  // 0x00361960, 0x004fe568
        m_unk7e0 = 0.0f;
        SpawnHitFx();  // 0x0028c0a0
    }
    if (!(m_unk8b4 <= soundInterval)) {  // ble
        m_unk8b4 = 0.0f;
        if (id == 9) {
            PlaySound(0x25, 0, m_pKGLObject);  // 0x002795c0
        } else if (id == 0xd) {
            PlaySound(0x27, 0, m_pKGLObject);
        } else if (id == 0x10) {
            PlaySound(0x24, 0, m_pKGLObject);
        } else if (id == 1) {
            PlaySound(0x26, 0, m_pKGLObject);
        }
    }
}

// DOTD: ApplyPendingDamage's hit stats (0x0029a7b0): a hero's hit (unless the damage's +0x24) counts in its dragon's
// combo (OnNewHitW at the hit point +0x23c); a held element damage counts by its ability (CountHeldElementHit). An
// enemy's hit: one held by a hero (+0x8f4) counts for that hero, else one with the shadow (+0x709) for dragon 1.
void CKHkS08Enemy::CountHitStats() {
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);  // TOC +0x10a0 -> +0x8c
    IKSerializable* attacker = static_cast<IKSerializable*>(m_unk694);
    const CVector3 point{m_unk23c[0], m_unk23c[1], m_unk23c[2]};
    if (attacker != nullptr && attacker->IsKindOfClass(0x25c2) != 0 && m_unk27c->m_unk24 == 0) {
        if (m_unk27c->m_unk0c != 0 && m_unk27c->IsKindOfClass(0x99cc) != 0) {
            CountHeldElementHit(manager, &point);
        } else {
            OnNewHitW(manager, static_cast<CKHkS08Hero*>(attacker)->GetDragonIndex(), &point);  // 0x004fe568
        }
    }
    attacker = static_cast<IKSerializable*>(m_unk694);
    if (attacker == nullptr || attacker->IsKindOfClass(0x26c2) == 0) return;
    CKHkS08Enemy* enemy = static_cast<CKHkS08Enemy*>(attacker);
    if (enemy->IsGrabbedState() != 0 && enemy->GetGrabbingHero() != nullptr) {  // 0x002896b8, 0x00288fd0
        IKSerializable* holder = enemy->GetGrabbingHero();
        if (holder->IsKindOfClass(0x25c2) != 0 && enemy->m_unk8f4 != 0) {
            OnNewHitW(manager, static_cast<CKHkS08Hero*>(enemy->GetGrabbingHero())->GetDragonIndex(), &point);
            return;
        }
    }
    if (enemy->m_unk709 != 0) OnNewHitW(manager, 1, &point);
}

// DOTD: ApplyPendingDamage's bonus damage (0x0029ac8c): a hero damage that is not an element one adds its amount to
// +0x800; reaching +0x804 each bonus entry of the kind (+0x4b4) gets its count and value from the damage (x the enemy
// group's +0x288 / +0x28c in a hero's grab combo kinds 1 / 5, else 1) over the kind's +0xcc, the bonuses spawn at hot
// spot 1 and +0x800 restarts.
void CKHkS08Enemy::AccumulateBonusDamage() {
    if (m_unk27c->IsKindOfClass(0x998c) == 0 || m_unk27c->IsKindOfClass(0x99cc) != 0) return;
    const float total = m_unk800 + m_unk27c->m_unk04;
    m_unk800 = total;
    if (!(m_unk804 <= total)) return;
    float factor = 1.0f;  // TOC +0x1094
    if (m_mainState == 7 && m_unk294 != nullptr && m_unk294->IsKindOfClass(0x25c2) != 0) {
        CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(m_unk294);
        if (hero->GetGrabTarget() == this && hero->IsUsingWindBeam() == 0) {
            CKGrpS08Enemy* group = static_cast<CKGrpS08Enemy*>(enemy::EnemyGroup());
            if (hero->m_unk1abd != 0) {
                factor = group->m_unk268[8];  // +0x288
            } else if (hero->m_unk1ac3 != 0) {
                factor = group->m_unk268[9];  // +0x28c
            }
        }
    }
    CKBonusData* bonus = static_cast<CKBonusData*>(m_unk884->m_pUnk4b4);
    for (uint32_t i = 0; i < bonus->m_count; ++i) {
        CKBonusData::Entry& entry = bonus->m_pEntries[i];
        if (entry.m_unk18 == 0) {
            const float count = factor * (static_cast<float>(entry.m_unk14) * m_unk800) / m_unk884->m_unkcc;
            entry.m_unk18 = static_cast<uint32_t>(static_cast<int32_t>(count));  // fctiwz
        }
        const float value = factor * m_unk800 / m_unk884->m_unkcc;
        std::memcpy(&entry.m_unk1c, &value, sizeof value);
    }
    // The damage's share of the bonuses (count mode 1) at hot spot 1, along the shared y axis (TOC +0x10b4).
    {
        CVector3 at;
        GetHotSpot(1)->GetWorldPosition(&at);  // 0x002892e8, 0x000ce790
        const CVector3 up = enemy::kAxisY;
        SpawnBonusDrop(&at, &up, 1);  // 0x0027d1b8
    }
    m_unk800 = 0.0f;
}

// 0x0028c0a0 CKHkS08Enemy_SpawnHitFx: the kind's hit FX (+0x128) for the pending damage: an element damage of type 0
// its entry 26; else the first active status (burn 9, ice 10, fire 15, element 3 14, element 6 12, shadow 13, poison
// 16); else a hero damage's +0x25 entry 33, type 1 entry 1, the rest entry 2. One explosion of it from the FX pool is
// set off at the hit point (+0x23c) along the knockback (+0x248; Y when null).
void CKHkS08Enemy::SpawnHitFx() {
    CKS08Damage* damage = m_unk27c;
    uint32_t index;
    if (damage->IsKindOfClass(0x99cc) != 0 && static_cast<CKS08ElementDamage*>(damage)->m_unk38 == 0) {
        index = 26;
    } else if (m_unk6b8 > 0.0f) {
        index = 9;
    } else if (m_unk6c8 > 0.0f) {
        index = 10;
    } else if (m_unk6c0 > 0.0f) {
        index = 15;
    } else if (m_unk6d4 > 0.0f) {
        index = 14;
    } else if (m_unk6cc > 0.0f) {
        index = 12;
    } else if (m_unk6c4 > 0.0f) {
        index = 13;
    } else if (m_unk6d0 > 0.0f) {
        index = 16;
    } else if (damage->IsKindOfClass(0x998c) != 0 && static_cast<CKS08HeroDamage*>(damage)->m_unk25 != 0) {
        index = 33;
    } else if (m_unk27c->IsKindOfClass(0x998c) != 0 && m_unk27c->m_unk20 == 1) {
        index = 1;
    } else {
        index = 2;
    }
    IKFxData* data = static_cast<IKFxData*>(m_unk884->m_vUnk128.m_pBlock[index]);
    if (data == nullptr) return;
    IKFx* effect = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(data, this);  // TOC +0xed4 -> +0x60
    if (effect == nullptr) return;
    CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(effect);
    const CVector3 direction{m_unk248, m_unk24c, m_unk250};
    if (direction.x == 0.0f && direction.y == 0.0f && direction.z == 0.0f) {  // 0x00c50d64 (TOC +0xed0)
        const CVector3 up{0.0f, 1.0f, 0.0f};  // 0x00c50d40 (TOC +0xed8)
        explosion->SetDirection(&up, this);  // 0x001b5e20
    } else {
        explosion->SetDirection(&direction, this);
    }
    const CVector3 at{m_unk23c[0], m_unk23c[1], m_unk23c[2]};
    explosion->SetTranslation(&at, this);  // 0x001b66e8
    explosion->Trigger(this, 0);           // 0x001b82a8
    explosion->ReleaseReservation(this);   // vt+0x54
}

namespace {
// The hit's direction against the node (PlayDirectionalHurtAnim): its LTM at row (x, z), the side turned a quarter
// round about Y (Vec3_RotateTowardByAngle_maybe 0x5841a8, TOC +0x10b8 pi/2), the signed angles of the knockback
// direction (+0x248, flattened) against the facing about that side, and of (0, y, z) against the at row's (0, y, z) about
// the up row (Vec3_SignedAngleBetween_maybe 0x27efc0).
constexpr float kQ1 = 0.785398185f;  // TOC +0x10bc pi/4
constexpr float kQ3 = 2.3561945f;    // TOC +0x10c0 3pi/4
constexpr float kQ5 = 3.92699099f;   // TOC +0x10c4 5pi/4
constexpr float kQ7 = 5.49778748f;   // TOC +0x10c8 7pi/4
}  // namespace

// 0x00297950 CKHkS08Enemy_PlayDirectionalHurtAnim_maybe: the hurt animation by the hit's side (front / back by the
// vertical angle, else left / right / behind / front by the horizontal one), for the hurt reaction (2) or the other
// reactions: the kind's single animation when it has one (+0x428..+0x454: 0x12..0x15 or 0x1f..0x22, +0x768 = 1),
// else the pair of directional animations of the dictionary (+0x754 / +0x75c) blended by the hit's strength (+0x768 0,
// the animation 0x11). A blended hurt: layer 0 slot 0 (a copy) crossfades to row 17 (+0x758 row 17, or 30 for the other
// reactions; empty rows take row 0), the time +0x764 restarts, +0x750 set and the blend weight +0x760 from the damage
// (+0x458..+0x45c mapped onto +0x460..+0x464). A single one: +0x774 1, +0x750 cleared, the repeat count +0x76c grows by
// +0x47c..+0x480 and the play rate +0x774 by +0x468..+0x46c along the damage's place in +0x484..+0x488 (not below
// +0x470).
void CKHkS08Enemy::PlayDirectionalHurtAnim() {
    (void)m_unk27c->IsKindOfClass(0xad4c);  // vt+0x08 (the answer is not used)
    const RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
    CVector3 facing{frame->ltm.at.x, 0.0f, frame->ltm.at.z};
    CVector3 axisY{0.0f, 1.0f, 0.0f};  // 0x00c50d40 (TOC +0x10b4)
    CVector3 side;
    Vec3_RotateTowardByAngle(&side, &facing, &axisY, 1.57079637f);  // 0x005841a8
    CVector3 hit{m_unk248, 0.0f, m_unk250};
    CVector3 front{frame->ltm.at.x, 0.0f, frame->ltm.at.z};
    CVector3 sideCopy = side;
    const float horizontal = enemy::Vec3_SignedAngleBetween(&hit, &front, &sideCopy);  // 0x0027efc0
    const RwFrame* again = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
    CVector3 hitUp{0.0f, m_unk24c, m_unk250};
    CVector3 atUp{0.0f, again->ltm.at.y, again->ltm.at.z};
    CVector3 up{again->ltm.up.x, again->ltm.up.y, again->ltm.up.z};
    const float vertical = enemy::Vec3_SignedAngleBetween(&hitUp, &atUp, &up);
    CAnimationDictionary* dictionary = GetSectorCpnt()->GetAnimDictionary(0);  // 0x002b3128
    const uint32_t* rows = reinterpret_cast<const uint32_t*>(dictionary->m_apAnimations);
    m_unk768 = 0;
    const bool hurt = m_reactState == 2;
    const CKS08EnemyCpnt* cfg = m_unk884;
    // The side: 0 vertical front, 1 vertical back, 2 left (pi/4..3pi/4), 3 right (5pi/4..7pi/4), 4 behind
    // (3pi/4..5pi/4), 5 front.
    uint32_t direction;
    if (vertical >= kQ1 && vertical <= kQ3) {
        direction = 0;
    } else if (vertical >= kQ5 && vertical <= kQ7) {
        direction = 1;
    } else if (horizontal >= kQ1 && horizontal <= kQ3) {
        direction = 2;
    } else if (horizontal >= kQ5 && horizontal <= kQ7) {
        direction = 3;
    } else if (horizontal >= kQ3 && horizontal <= kQ5) {
        direction = 4;
    } else {
        direction = 5;
    }
    // Per side: the kind's single animation flag and its row for the hurt reaction / the others, then the dictionary
    // rows of the pair (+0x754, +0x75c) for both.
    struct Choice {
        int32_t singleHurt, singleOther;  // the kind's +0x428.. words
        uint8_t animHurt, animOther;
        uint32_t pairHurtA, pairHurtB, pairOtherA, pairOtherB;
    };
    const Choice choices[6] = {
        {(int32_t)cfg->m_aUnk428[4], (int32_t)cfg->m_aUnk428[10], 0x13, 0x20, 16, 15, 29, 28},
        {(int32_t)cfg->m_aUnk428[5], (int32_t)cfg->m_aUnk428[11], 0x12, 0x1f, 15, 16, 28, 29},
        {(int32_t)cfg->m_aUnk428[2], (int32_t)cfg->m_aUnk428[8], 0x15, 0x22, 12, 13, 25, 26},
        {(int32_t)cfg->m_aUnk428[1], (int32_t)cfg->m_aUnk428[7], 0x14, 0x21, 13, 12, 26, 25},
        {(int32_t)cfg->m_aUnk428[3], (int32_t)cfg->m_aUnk428[9], 0x13, 0x20, 11, 14, 24, 27},
        {(int32_t)cfg->m_aUnk428[0], (int32_t)cfg->m_aUnk428[6], 0x12, 0x1f, 14, 11, 27, 24},
    };
    const Choice& c = choices[direction];
    if ((hurt ? c.singleHurt : c.singleOther) != 0) {
        m_unk768 = 1;
        RequestAnim(hurt ? c.animHurt : c.animOther, 0, 0, 0, 0.1f, 0.0f);  // 0x00285340, TOC +0x109c
    } else {
        m_unk754 = rows[hurt ? c.pairHurtA : c.pairOtherA];
        m_unk75c = rows[hurt ? c.pairHurtB : c.pairOtherB];
        RequestAnim(0x11, 1, 0, 0, 0.1f, 0.0f);
    }
    if (m_unk768 == 0) {
        AnimBlendSlot copy = m_unk164[0][0].m_blendSlot;  // the slot copied (TOC +0x1070..+0x1078 vtables)
        copy.CrossfadeToAnim(0.0, 0.0, rows[17], 1);      // 0x00079ea0
        m_unk758 = hurt ? rows[17] : rows[30];
        if (m_unk754 == 0) m_unk754 = rows[0];
        if (m_unk758 == 0) m_unk758 = rows[0];
        if (m_unk75c == 0) m_unk75c = rows[0];
        m_unk764 = 0.0f;
        m_unk750 = 1;
        const float amount = m_unk27c->m_unk04;
        const CKS08EnemyCpnt* k = m_unk884;
        if (amount <= k->m_unk458) {
            m_unk760 = k->m_unk460;
        } else if (amount >= k->m_unk45c) {
            m_unk760 = k->m_unk464;
        } else {
            float w = (amount - k->m_unk458) / (k->m_unk45c - k->m_unk458);
            m_unk760 = w;
            w = w * (k->m_unk464 - k->m_unk460);
            m_unk760 = w;
            m_unk760 = w + k->m_unk460;
        }
        return;
    }
    if (m_unk768 != 1) return;
    const CKS08EnemyCpnt* k = m_unk884;
    m_unk774 = 1.0f;  // TOC +0x1094
    m_unk750 = 0;
    const float amount = m_unk27c->m_unk04;
    float t = 0.0f;  // TOC +0x1098
    if (!(amount <= k->m_unk484)) {
        t = 1.0f;
        if (!(amount >= k->m_unk488)) t = (amount - k->m_unk484) / (k->m_unk488 - k->m_unk484);
    }
    const float base = static_cast<float>(static_cast<double>(static_cast<uint32_t>(k->m_unk47c)));
    const float span = static_cast<float>(static_cast<double>(static_cast<uint32_t>(k->m_unk480 - k->m_unk47c)));
    const int64_t repeats = static_cast<int64_t>(t * span + base);  // fctidz
    const uint32_t total = static_cast<uint32_t>(repeats) + m_unk76c;
    m_unk770 = total;
    m_unk76c = total;
    const float rate = ppc::fmadds(t, k->m_unk46c - k->m_unk468, k->m_unk468);
    m_unk774 = m_unk774 == 1.0f ? rate : m_unk774 + rate;
    if (m_unk774 < k->m_unk470) m_unk774 = k->m_unk470;
}

// 0x00298430 CKHkS08Enemy_UpdateHurtAnimPlayback_maybe: a blended hurt advances its time (+0x764 by the frame dt x
// +0x774) and, before the second animation's end, sets the blended pair (SetSignedBlendAnimPair). A single one: without
// the kind's slowdown flag (+0x474) the rate +0x774 decays by +0x478 per second (not below +0x470); with it the last
// repeat (+0x76c 1) eases the rate from +0x778 down to +0x470 over the animation; each end of the animation (at the rate)
// counts a repeat down (the last but one keeps the rate in +0x778).
void CKHkS08Enemy::UpdateHurtAnimPlayback(IKTime* clock) {
    if (m_unk768 == 0) {
        const float t = ppc::fmadds(m_unk1fc, m_unk774, m_unk764);
        m_unk764 = t;
        if (CKAnmKeyFrameController::GetDurationOf(m_unk75c) > t) {
            SetSignedBlendAnimPair(t, m_unk760, m_unk754, m_unk758, m_unk75c);  // 0x00285c10
        }
        return;
    }
    if (m_unk768 != 1) return;
    const CKS08EnemyCpnt* cfg = m_unk884;
    if (cfg->m_unk474 == 0) {
        (void)GetLayerSlotAnimDuration(0, 0);  // 0x002854f8 (twice; the answers are not used)
        (void)GetLayerSlotAnimDuration(0, 0);
        float rate = m_unk774 - (m_unk774 * cfg->m_unk478) * clock->m_afDeltaTime[0];
        m_unk774 = rate;
        if (rate < cfg->m_unk470) m_unk774 = cfg->m_unk470;
    } else if (m_unk76c == 1) {
        CKAnmKeyFrameController* track = ActiveTrack(m_unk164[0][0]);
        const float time = track->m_unk54;
        const float duration = track->GetDuration();  // 0x0007ab60
        if (time > duration) {
            m_unk774 = m_unk884->m_unk470;
        } else {
            const float from = m_unk778 - m_unk884->m_unk470;
            CKAnmKeyFrameController* again = ActiveTrack(m_unk164[0][0]);
            const float fraction = again->m_unk54 / again->GetDuration();
            m_unk774 = ppc::fmadds(from, 1.0f - fraction, m_unk884->m_unk470);
        }
    }
    if (!IsAnimEndReached(m_unk1fc * m_unk774, 0, 0)) return;  // 0x00285558
    m_unk76c = m_unk76c - 1;
    if (m_unk884->m_unk474 != 0 && m_unk76c == 1) m_unk778 = m_unk774;
}

// 0x002987c8 CKHkS08Enemy_IntegrateKnockbackMotion_maybe: the knockback's step (dt = +0x1fc x the slow-down +0x204,
// unless the life flag 0x400): +0x204 eases by the kind's +0x1e0 / +0x1e4 per second toward 1 out of the height band
// +0x1e8..+0x1ec over +0x728, inside it toward +0x1d8 (rising) or +0x1dc; the lift left (+0x274) pushes along the
// knockback direction (+0x248) with the speed (+0x270) over the kind's +0x1d0, gravity -+0x1d4 below. Hurt (2): on the
// ground (the probe within 0.01) the friction (-+0x4b8, by the speed unless +0x4bc) where it opposes the motion; the
// speed (+0x158) takes the acceleration and stops on a sign change of x (or z going positive). Knockdown (7): with the
// extra push +0x698 the same. Then the position moves by the speed.
void CKHkS08Enemy::IntegrateKnockbackMotion(IKTime* clock) {
    float dt = m_unk1fc;
    const CKS08EnemyCpnt* cfg = m_unk884;
    const float clockDt = clock->m_afDeltaTime[0];
    if ((m_bitArray & 0x400u) == 0) {
        const float height = m_v3Position.y - m_unk728;
        float scale;
        if (cfg->m_unk1e8 <= height && cfg->m_unk1ec >= height) {
            if (m_unk158.y > 0.0f) {
                scale = m_unk204 - cfg->m_unk1e0 * clockDt;
                m_unk204 = scale;
                if (scale < cfg->m_unk1d8) {
                    scale = cfg->m_unk1d8;
                    m_unk204 = scale;
                }
            } else if (cfg->m_unk1dc >= m_unk204) {
                scale = ppc::fmadds(cfg->m_unk1e4, clockDt, m_unk204);
                m_unk204 = scale;
                if (scale > cfg->m_unk1dc) {
                    scale = cfg->m_unk1dc;
                    m_unk204 = scale;
                }
            } else {
                scale = m_unk204 - cfg->m_unk1e4 * clockDt;
                m_unk204 = scale;
                if (scale < cfg->m_unk1dc) {
                    scale = cfg->m_unk1dc;
                    m_unk204 = scale;
                }
            }
        } else {
            scale = ppc::fmadds(m_unk158.y > 0.0f ? cfg->m_unk1e0 : cfg->m_unk1e4, clockDt, m_unk204);
            m_unk204 = scale;
            if (scale > 1.0f) {
                scale = 1.0f;
                m_unk204 = 1.0f;
            }
        }
        dt = dt * scale;
    }
    const float lift = m_unk274;
    float ay = -cfg->m_unk1d4;
    float ax = 0.0f, az = 0.0f;
    if (lift >= 0.0f) {
        const float used = dt <= lift ? dt : lift;
        m_unk274 = lift - dt;
        if (dt > 0.0f) {
            const float k = (used * m_unk270) / (dt * cfg->m_unk1d0);
            az = ppc::fmadds(m_unk250, k, 0.0f);
            ay = ppc::fmadds(m_unk24c, k, ay);
            ax = ppc::fmadds(m_unk248, k, 0.0f);
        }
    }
    CVector3& v = m_unk158;
    if (m_reactState == 2) {
        CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
        collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &m_v3Position.x, 1);  // 0x00196540
        if (m_GrdContDatasInOut.m_fdH < 0.00999999978f) {  // TOC +0x10d4
            float fx = v.x, fy = 0.0f, fz = v.z;
            const float length = std::sqrt(ppc::fmadds(fz, fz, ppc::fmadds(fx, fx, 0.0f)));
            if (length != 0.0f) {
                const float inverse = 1.0f / length;
                fz = fz * inverse;
                fx = fx * inverse;
                fy = inverse * 0.0f;
            }
            float k;
            if (m_unk884->m_unk4bc != 0) {
                k = -m_unk884->m_unk4b8;
            } else {
                const float speed = std::sqrt(ppc::fmadds(v.z, v.z, ppc::fmadds(v.x, v.x, v.y * v.y)));
                k = -m_unk884->m_unk4b8 * speed;
            }
            const float rz = k * fz, rx = k * fx, ry = k * fy;
            const bool opposes = (rx > 0.0f && v.x < 0.0f) || (rx < 0.0f && v.x > 0.0f) || (rz > 0.0f && v.z < 0.0f) ||
                                 (rz < 0.0f && v.z > 0.0f);
            if (opposes) {
                ax = ax + rx;
                ay = ay + ry;
                az = az + rz;
            }
        }
    }
    const uint8_t react = m_reactState;
    if (react == 7) {
        if (!(v.x == 0.0f && v.z == 0.0f)) {
            float push2;
            std::memcpy(&push2, &m_unk6a0, sizeof push2);
            const float px = m_unk698 + ax, py = m_unk69c + ay, pz = push2 + az;
            const float oldX = v.x, oldZ = v.z;
            v.x = ppc::fmadds(dt, px, oldX);
            v.y = ppc::fmadds(dt, py, v.y);
            v.z = ppc::fmadds(dt, pz, oldZ);
            bool stop = false;
            if (oldX <= 0.0f && v.x >= 0.0f) {
                stop = true;
            } else if (oldX >= 0.0f && v.x <= 0.0f) {
                stop = true;
            } else if (oldZ <= 0.0f && v.z >= 0.0f) {
                stop = true;
            }
            if (stop) {
                v.z = 0.0f;
                v.x = 0.0f;
            }
        }
    } else if (react == 2) {
        const float oldX = v.x, oldZ = v.z;
        v.x = ppc::fmadds(dt, ax, oldX);
        v.z = ppc::fmadds(dt, az, oldZ);
        v.y = ppc::fmadds(dt, ay, v.y);
        if (!(v.x == 0.0f && v.z == 0.0f)) {
            bool stop = false;
            if (oldX < 0.0f && v.x > 0.0f) {
                stop = true;
            } else if (oldX > 0.0f && v.x < 0.0f) {
                stop = true;
            } else if (oldZ < 0.0f && v.z > 0.0f) {
                stop = true;
            }
            if (stop) {
                v.z = 0.0f;
                v.x = 0.0f;
            }
        }
    } else {
        v.x = ppc::fmadds(dt, ax, v.x);
        v.y = ppc::fmadds(dt, ay, v.y);
        v.z = ppc::fmadds(dt, az, v.z);
    }
    m_v3Position.x = ppc::fmadds(dt, v.x, m_v3Position.x);
    m_v3Position.y = ppc::fmadds(dt, v.y, m_v3Position.y);
    m_v3Position.z = ppc::fmadds(dt, v.z, m_v3Position.z);
}

// 0x002ae5e8 CKHkS08Enemy_SpreadStunToNearby: as SpreadPoisonToNearby, with the stun gauge (AddStunGauge) and +0x7b6.
void CKHkS08Enemy::SpreadStunToNearby(float amount, float radiusSquared) {
    const uint32_t count = enemy::EnemyGroup()->m_ui32NbActiveEnemies;  // 0x00276f58
    for (uint32_t i = 0; i < count; ++i) {
        CKHkS08Enemy* other = static_cast<CKHkS08Enemy*>(enemy::EnemyGroup()->m_apActiveEnemies[i]);
        if (other == this) continue;
        const float dz = m_v3Position.z - other->m_v3Position.z;
        const float dx = m_v3Position.x - other->m_v3Position.x;
        if (!(ppc::fmadds(dx, dx, dz * dz) <= radiusSquared)) continue;
        other->AddStunGauge(amount);  // 0x0027cee0
        other->m_unk7b6 = 1;
    }
}
