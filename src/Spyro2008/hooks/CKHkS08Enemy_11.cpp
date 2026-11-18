// Reconstructed original translation unit: 0x29dd38-0x2ac320 (GAME_TOC1, main_toc1), 44 functions, 44 live.
// Primary class: CKHkS08Enemy  key 0x26c2  category Hook  size 0x8f8  vtable 0xb22078
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x29dd38  CKHkS08Enemy_InitAuxStateMachine_maybe
//   [x] 0x29dd98  CKHkS08Enemy_vf158
//   [x] 0x29dda0  CKHkS08Enemy_vf15C
//   [x] 0x29dda8  CKHkS08Enemy_vf168
//   [x] 0x29ddb0  CKHkS08Enemy_vf16C
//   [x] 0x29ddb8  CKHkS08Enemy_vf17C
//   [x] 0x29ddc0  CKHkS08Enemy_vf180
//   [x] 0x29ddc8  CKHkS08Enemy_vf184
//   [x] 0x29ddd0  CKHkS08Enemy_vf1A0
//   [x] 0x29ddd8  CKHkS08Enemy_vf1CC
//   [x] 0x29dde0  CKHkS08Enemy_State0x26_OnFireWait_maybe
//   [x] 0x29df18  CKHkS08Enemy_State19_OneShotAnim_maybe
//   [x] 0x29dfd8  CKHkS08Enemy_UpdateTargetAndDestination
//   [x] 0x29e028  CKHkS08Enemy_UpdateTimers_maybe
//   [x] 0x29e2c8  CKHkS08Enemy_State0x20_Alerted_maybe
//   [x] 0x29e470  CKHkS08Enemy_vf1D4
//   [x] 0x29e698  StaticInitAndDestruction_29e698  (the two file statics at the end)
//   [ ] 0x29e6c8  _GLOBAL__D_29e6c8
//   [ ] 0x29e6d8  _GLOBAL__I_29e6d8
//   [x] 0x29e6e8  CKHkS08Enemy_State0x21_DropEquipment_maybe
//   [x] 0x29e988  CKHkS08Enemy_vf18C
//   [x] 0x29ec08  CKHkS08Enemy_State06_Dodge_maybe
//   [x] 0x29f0a0  CKHkS08Enemy_State0x22_BlockAndCounter_maybe
//   [x] 0x29f3c0  CKHkS08Enemy_State21_Dying
//   [x] 0x29fba0  CKHkS08Enemy_State26_Burning
//   [x] 0x2a0260  CKHkS08Enemy_State18
//   [x] 0x2a0810  CKHkS08Enemy_State00_Spawn_maybe
//   [x] 0x2a14a0  CKHkS08Enemy_State17
//   [x] 0x2a1db8  CKHkS08Enemy_State05_Guard_maybe
//   [x] 0x2a2530  CKHkS08Enemy_State0E_AttackStrike_maybe
//   [x] 0x2a3278  CKHkS08Enemy_State0D_AttackWindup_maybe
//   [x] 0x2a4190  CKHkS08Enemy_State01
//   [x] 0x2a6d40  CKHkS08Enemy_ProcessDamageStateTransitions_maybe
//   [x] 0x2a7820  CKHkS08Enemy_vf1B0
//   [x] 0x2a7eb0  CKHkS08Enemy_State27_Fall_maybe
//   [x] 0x2a81f0  CKHkS08Enemy_State0x24_Feared_maybe
//   [x] 0x2a8748  CKHkS08Enemy_State1F_Stunned_maybe
//   [x] 0x2a8fa8  CKHkS08Enemy_State1E_WaitWindGaugeEmpty_maybe
//   [x] 0x2a91a0  CKHkS08Enemy_State1D_WindCaught_maybe
//   [x] 0x2a9bc0  CKHkS08Enemy_State0A_HitReaction_maybe
//   [x] 0x2aa410  CKHkS08Enemy_State07_Grabbed
//   [x] 0x2aab10  CKHkS08Enemy_State0F_AttackRecover_maybe
//   [x] 0x2ab050  CKHkS08Enemy_vf1AC
//   [x] 0x2aba20  CKHkS08Enemy_State02_Combat_maybe
#include "Spyro2008/hooks/CKHkS08EnemyShared.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/scenegraph/CTrailNodeFx.h"
#include "Spyro2008/logic/CKS08GameStructure.h"
#include "Spyro2008/logic/CKS08CarrierEnemy.h"
#include "Spyro2008/misc/CKHkS08TransportableBase.h"
#include "k2000/components/CKBonusData.h"
#include "Spyro2008/hooks/CKHkS08Enemy.h"
#include "Spyro2008/misc/CKS08EnemyAbilityHost.h"
#include "k2000/logic/CKAbilityElement.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/logic/animation/CKAnimationMarkContainer.h"

#include "k2000/core/Stub.h"

#include <cmath>

#include "Spyro2008/components/CKS08EnemyCpnt.h"
#include "Spyro2008/components/CKS08FightZoneCpnt.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/CKGrpS08Enemy.h"
#include "Spyro2008/hooks/CKHkS08Egg.h"
#include "Spyro2008/hooks/CKHkS08Weapon.h"
#include "crt/ppc_ops.h"
#include "k2000/components/CKEnemySectorCpnt.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/render/CRenderer.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/services/ICollisionMesh.h"
#include "k2000/fx/IKFx.h"
#include "k2000/groups/CKGrpFightZone.h"
#include "k2000/groups/CKGrpSquad.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/ai/CKSrvPathFinding.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/system/IKTime.h"
#include "Spyro2008/logic/CKS08ElementDamage.h"
#include "k2000/misc/Mat4.h"
#include "Spyro2008/logic/CKS08Damage.h"
#include "Spyro2008/logic/CKS08GolemDamage.h"
#include "Spyro2008/logic/CKS08StunDamage.h"
#include "Spyro2008/logic/CKS08EnemyAttack.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "Spyro2008/hooks/CKHkS08CrumblyZoneMultiState.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "k2000/ai/CKHkDetectorGroup.h"
#include "k2000/math/Math.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/fx/CKParticlesEffectNodeFx.h"
#include "k2000/math/Vec3.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/misc/FloatApproach.h"
#include "crt/xatan.h"
#include <cstring>
#include "platform/fps.h"

namespace {
// 0x00a7030c (TOC +0x11ec +0xc4): per enemy kind, the first of its three stun animations.
const uint32_t kStunAnimBase[9] = {0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0, 0, 0, 0};

// 0x0025ab50 CKGrpSquad_GetFightZone: the squad's parent group (+0x1c).
CKGrpFightZone* SquadFightZone(IKSerializable* squad) {
    return static_cast<CKGrpFightZone*>(static_cast<CKGrpSquad*>(squad)->m_pParent);
}
}  // namespace

// 0x002a6d40 CKHkS08Enemy_ProcessDamageStateTransitions_maybe (vt+0x128): the timers first (vt+0x130), then the main
// state forced by the damage taken: 7 when +0x290 asks for it (clock passed); with a pending hit (+0x239, not in the
// states 0xc / 0x15 / 5 / 0x22 / 0x24, nor in the reactions 0xa / 7; state 6 only once its gauge +0x6c8 and the frame
// fraction past +0x6f8 allow it) the damage applied, then: kinds 5 / 6 killed (health <= 0) go to 2 with the reaction
// 0xf; an element damage that causes no hit reaction ends the hit (+0x239 cleared unless element 0x11) and, at zero
// health, kills (kinds 5 / 6: reaction 0xf and state 2; the others: state 0x15), both without a clock; else the status
// gauge +0x6d4 stuns (0x1f) or the hit sends the enemy to 2 (from the attack states 0xd..0xf only when the attack
// +0x73c is not uninterruptible (+0x6c), the hit kills, or the element is 0 / 0xa / 0xe). Returns 1 in the state 0xc,
// or when the state was 7 on entry or became 7 here.
uint8_t CKHkS08Enemy::ProcessDamageStateTransitions(IKTime* clock) {
    UpdateTimers(clock);  // vt+0x130
    const uint8_t entry = m_mainState;
    if (entry == 0xc) return 1;
    uint8_t busy = 0;
    if (m_unk290 != 0) {
        m_unk290 = 0;
        // GetHeroByDragonIndex(GetHeroGroup(this), 1) 0x2ca080: called, its result unused.
        SwitchMainState(7, clock);
        busy = 1;
    }
    if (entry == 7) busy = 1;
    if (m_unk239 == 0) return busy;
    if (m_reactState == 0xa || m_reactState == 7) return busy;
    uint8_t state = m_mainState;
    if (state == 0x15 || state == 5 || state == 0x22 || state == 0x24) return busy;
    if (state == 6) {
        if (m_unk6c8 <= 0.0f) return busy;  // TOC +0x11ac 0.0f
        const float dt = clock->m_afDeltaTime[0];
        if (!((dt - m_unk6f8) / dt >= m_unk884->m_unk2c8)) return busy;
    }
    if (clock != nullptr) {
        ApplyPendingDamage(clock);  // 0x00299f30
        state = m_mainState;
    }
    if (state == 7) return busy;
    const bool bigKind = static_cast<uint8_t>(m_ui8EnemyClassType - 5) <= 1;
    if (bigKind) {
        // 0x2a7190: a kind 5 / 6 killed.
        if (!(m_unk258 <= 0.0f)) return busy;
        if (state == 0x15 || state == 2 || m_reactState == 0xf) return busy;
        SwitchMainState(2, clock);
        SwitchReactState(0xf, clock);
        return busy;
    }
    if (m_unk27c->IsKindOfClass(0x99cc) != 0 && PendingDamageCausesHitReaction() == 0) {
        // 0x2a7344: an element damage without a hit reaction.
        if (static_cast<CKS08ElementDamage*>(m_unk27c)->m_unk38 != 0x11) m_unk239 = 0;
        if (m_unk258 != 0.0f) return busy;
        if (static_cast<uint8_t>(m_ui8EnemyClassType - 5) <= 1) {
            state = m_mainState;
            if (state == 0x15 || state == 2) return busy;
            SwitchReactState(0xf, nullptr);
            SwitchMainState(2, nullptr);
            return busy;
        }
        if (m_mainState == 0x15) return busy;
        SwitchMainState(0x15, nullptr);
        return busy;
    }
    if (!(m_unk6d4 <= 0.0f)) {
        // The stun gauge: state 0x1f.
        state = m_mainState;
        if (state == 0x1f || state == 0x15 || state == 0xff || m_reactState == 0xf) return busy;
        SwitchMainState(0x1f, clock);
        return busy;
    }
    // 0x2a7578: the hit.
    state = m_mainState;
    if (state == 2) return busy;
    if (state == 0xd || state == 0xe || state == 0xf) {
        const CKS08EnemyAttack* attack = m_unk73c;
        bool hit = false;
        if (attack != nullptr && attack->m_unk6c == 0) {
            if (m_unk27c->IsKindOfClass(0x99cc) != 0) {
                const int32_t element = static_cast<int32_t>(static_cast<CKS08ElementDamage*>(m_unk27c)->m_unk38);
                hit = element == 0 || element == 0xa || element == 0xe;
            }
        } else if (attack != nullptr && m_unk27c != nullptr) {
            hit = true;
        }
        if (!hit && !(m_unk258 <= 0.0f)) return busy;
    }
    SwitchMainState(2, clock);
    return busy;
}

// DOTD: the inlined reaction state change (+0x554: leave the current row with phase 2, enter `next` with phase 1).
void CKHkS08Enemy::SwitchReactState(uint8_t next, IKTime* clock) {
    const uint8_t old = m_reactState;
    if (old != 0xff) CallReactState(old, clock, 2, next);
    m_reactState = next;
    CallReactState(next, clock, 1, old);
}

// 0x00299f30 CKHkS08Enemy_ApplyPendingDamage: the pending damage (+0x27c). The health (+0x258) loses its amount (an
// element damage's after the resistance; a held damage +0x0c per second; the kind 5's shield +0x724 takes one hit for
// it), the killing blow playing a death cry (0xe + a random 0..3) and the FX 0x1e at every hot spot; not below 0. A stun
// damage fills the stun (+0x25c) and disarm (+0x278) gauges up to the kind's limits. The knockback direction (+0x248):
// away from the golem damage's point (or the volume +0x89c), else from the attacker (an element damage of type 0 takes
// the attacker's facing), flattened, normalised, turned by the damage's yaw (+0x1c) and pitch (+0x18) in degrees x
// -57.3; the speed and lift (+0x270, +0x274) from the damage; the kinds 5 / 6 keep their speed (+0x158). A full disarm
// gauge throws the weapon (state 0x21). An element damage feeds its status gauges; then the hit sounds, the gauges
// capped, the block counter reset, the enemy group alerted, the hit counted for the hero's combo, the hit explosion,
// the bonus damage and the group's hit trigger.
void CKHkS08Enemy::ApplyPendingDamage(IKTime* clock) {
    CKS08Damage* damage = m_unk27c;
    float amount = damage->m_unk04;
    const bool element = damage->IsKindOfClass(0x99cc) != 0;  // vt+0x08
    if (element) amount = ApplyElementResistance(amount);  // 0x00288b18
    float health = m_unk258;
    if (m_ui8EnemyClassType == 5 && m_unk724 != 0) {
        m_unk724 = 0;  // the shield took it
    } else if (damage->m_unk0c == 0) {
        if (health > 0.0f && amount >= health) {  // TOC +0x1098
            const int32_t r = Rand_Int();  // 0x00011500
            PlaySound(static_cast<uint8_t>(0xe + ((static_cast<uint32_t>(r) >> 14) & 3u)), 0, m_pKGLObject);  // 0x002795c0
            PlayFxOnAllHotspots(0x1e);  // 0x0028da80
            health = m_unk258;
        }
        health = health - amount;
        m_unk258 = health;
    } else {
        const float dt = clock->m_afDeltaTime[0];
        if (!(health <= 0.0f) && amount * dt >= health) {
            const int32_t r = Rand_Int();
            PlaySound(static_cast<uint8_t>(0xe + ((static_cast<uint32_t>(r) >> 14) & 3u)), 0, m_pKGLObject);
            PlayFxOnAllHotspots(0x1e);
            health = m_unk258;
        }
        health = health - amount * clock->m_afDeltaTime[0];
        m_unk258 = health;
    }
    if (health < 0.0f) m_unk258 = 0.0f;
    // 0x0029a014: the stun and disarm gauges.
    if (damage->IsKindOfClass(0x9acc) != 0) {
        const CKS08StunDamage* stun = static_cast<const CKS08StunDamage*>(damage);
        const CKS08EnemyCpnt* cfg = m_unk884;
        float stunAmount;
        std::memcpy(&stunAmount, &stun->m_unk28, sizeof stunAmount);
        const float stunGauge = ppc::fmadds(stunAmount, cfg->m_unkd8, m_unk25c);
        m_unk25c = stunGauge;
        const float disarm = ppc::fmadds(stun->m_unk2c, cfg->m_unke0, m_unk278);
        m_unk278 = disarm;
        if (!(stunGauge <= cfg->m_unkd4)) m_unk25c = cfg->m_unkd4;
        if (!(disarm <= cfg->m_unkdc)) m_unk278 = cfg->m_unkdc;
    }
    // The knockback direction.
    if (m_unk27c->IsKindOfClass(0xad4c) != 0) {
        const CKS08GolemDamage* golem = static_cast<const CKS08GolemDamage*>(m_unk27c);
        if (golem->m_unk28 != nullptr) {
            // STUB(C2.8: golems): the point at the golem damage's +0x28 object (+0x04); LVL010's are null.
            DOTD_STUB_ONCE("CKHkS08Enemy_ApplyPendingDamage 0x299f30: the golem damage's point (C2.8)");
        } else {
            const RwFrame* frame = static_cast<CSGMovable*>(m_unk89c)->m_pRwFrame;
            m_unk248 = m_v3Position.x - frame->ltm.pos.x;
            m_unk250 = m_v3Position.z - frame->ltm.pos.z;
            m_unk24c = m_v3Position.y - frame->ltm.pos.y;
        }
    } else if (m_unk694 != nullptr) {
        IKHook* attacker = static_cast<IKHook*>(static_cast<IKSerializable*>(m_unk694));
        const RwFrame* frame = static_cast<CSGMovable*>(attacker->m_pKGLObject)->m_pRwFrame;
        const CKS08ElementDamage* elemental =
            m_unk27c != nullptr && m_unk27c->IsKindOfClass(0x99cc) != 0 ? static_cast<const CKS08ElementDamage*>(m_unk27c)
                                                                       : nullptr;
        if (elemental != nullptr && elemental->m_unk38 == 0) {
            m_unk248 = frame->ltm.at.x;
            m_unk24c = frame->ltm.at.y;
            m_unk250 = frame->ltm.at.z;
        } else {
            m_unk248 = m_v3Position.x - frame->ltm.pos.x;
            m_unk250 = m_v3Position.z - frame->ltm.pos.z;
            m_unk24c = m_v3Position.y - frame->ltm.pos.y;
        }
    }
    // 0x0029a130
    m_unk24c = 0.0f;
    float length = std::sqrt(ppc::fmadds(m_unk250, m_unk250, ppc::fmadds(m_unk248, m_unk248, m_unk24c * m_unk24c)));
    float dx = m_unk248;
    float dz = m_unk250;
    if (length != 0.0f) {
        const float inverse = 1.0f / length;  // TOC +0x1094
        dz = inverse * m_unk250;
        dx = inverse * m_unk248;
        m_unk250 = dz;
        m_unk248 = dx;
        m_unk24c = inverse * m_unk24c;
    }
    alignas(16) CMatrix34 basis{};
    basis.m_right = CVector3{-dz, 0.0f, dx};
    basis.m_ui32Flags &= 0xfffdfffcu;
    basis.m_up = CVector3{0.0f, 1.0f, 0.0f};  // 0x00c50d40 (TOC +0x10b4)
    basis.m_at = CVector3{m_unk248, m_unk24c, m_unk250};
    float pitch;
    std::memcpy(&pitch, &m_unk27c->m_unk18, sizeof pitch);
    Mat4_RotateLocalYDeg(m_unk27c->m_unk1c * -57.2957802f, &basis);  // 0x002413d0, TOC +0x1104
    Mat4_RotateLocalXDeg(pitch * -57.2957802f, &basis);              // 0x00241118
    m_unk248 = basis.m_at.x;
    m_unk24c = basis.m_at.y;
    m_unk250 = basis.m_at.z;
    length = std::sqrt(ppc::fmadds(m_unk250, m_unk250, ppc::fmadds(m_unk248, m_unk248, m_unk24c * m_unk24c)));
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        m_unk250 = inverse * m_unk250;
        m_unk248 = inverse * m_unk248;
        m_unk24c = inverse * m_unk24c;
    }
    m_unk270 = m_unk27c->m_unk10;
    m_unk274 = m_unk27c->m_unk14;
    if (static_cast<uint8_t>(m_ui8EnemyClassType - 5) > 1) {
        m_unk158.x = 0.0f;
        m_unk158.z = 0.0f;
        m_unk158.y = 0.0f;
    }
    // 0x0029a2c0: the weapon thrown.
    if (m_unk520 != nullptr && m_unk278 >= m_unk884->m_unkdc &&
        (m_ui8EnemyClassType != 2 || m_unk524 != nullptr) && m_mainState != 7) {
        m_unk278 = 0.0f;
        m_unk520->m_fPushTime = m_unk274;  // the weapon's +0x68
        const RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
        CVector3 eject{frame->ltm.at.x, 0.0f, frame->ltm.at.z};
        const float span = std::sqrt(ppc::fmadds(eject.z, eject.z, ppc::fmadds(eject.x, eject.x, 0.0f)));
        if (span != 0.0f) {
            const float inverse = 1.0f / span;
            eject.z = eject.z * inverse;
            eject.x = eject.x * inverse;
            eject.y = eject.y * inverse;
        }
        m_unk520->SetEjectVelocity(&eject);  // 0x002b2218
        SwitchMainState(0x21, nullptr);
    }
    if (m_unk27c->IsKindOfClass(0x99cc) != 0) ApplyElementGauges(clock);
    // --fps N (not in the original): a held (per-second) damage is pending every update, so its sounds and voice
    // rolls run once per 60 Hz frame, as at 60 fps, not once per displayed frame.
    if (!dotd::fps::Unlocked() || m_unk27c->m_unk0c == 0 || dotd::fps::Ticks() > 0) PlayHitSounds();
    // 0x0029a6d8: the gauges capped.
    const CKS08EnemyCpnt* cfg = m_unk884;
    if (!(m_unk6b8 <= cfg->m_unk244)) m_unk6b8 = cfg->m_unk244;
    if (!(m_unk6c0 <= cfg->m_unk24c)) m_unk6c0 = cfg->m_unk24c;
    if (!(m_unk6c8 <= cfg->m_unk254)) m_unk6c8 = cfg->m_unk254;
    if (!(m_unk6d0 <= cfg->m_unk25c)) m_unk6d0 = cfg->m_unk25c;
    if (!(m_unk6cc <= cfg->m_unk258)) m_unk6cc = cfg->m_unk258;
    if (!(m_unk6c4 <= cfg->m_unk250)) m_unk6c4 = cfg->m_unk250;
    if (!(m_unk6d4 <= cfg->m_unk260)) m_unk6d4 = cfg->m_unk260;
    if (cfg->m_unke8 != 0 && m_mainState != 5 && m_mainState != 0x22) {
        m_unk72c = 0;
        m_unk714 = cfg->m_unkec;
    }
    CKGrpS08Enemy* group = static_cast<CKGrpS08Enemy*>(enemy::EnemyGroup());  // 0x00276f58
    if (group->m_unk1bc == 0) {
        group->m_unk1bc = 1;
        group->SignalAlert();  // 0x00268178
        group->m_unk1e8 = 1;
    }
    CountHitStats();
    // 0x0029a84c: the hit explosion.
    if (m_mainState != 7 && m_unk694 != nullptr && m_unk27c->m_unk0c == 0) SpawnHitFx();  // 0x0028c0a0
    if (m_unk27c->m_unk08 == 0) AccumulateBonusDamage();
    // 0x0029a888: an element damage held on the enemy pushes it.
    CKS08Damage* now = m_unk27c;
    if (now->IsKindOfClass(0x99cc) != 0 && now->m_unk0c != 0 && m_unk694 != nullptr && m_mainState != 0x1d &&
        m_reactState != 8 && static_cast<CKS08ElementDamage*>(now)->m_unk38 != 0x12) {
        // The push away from the attacker's node, normalised, turned by the damage's +0x18 radians about X and its
        // +0x1c about Y (TocBridge_Vec3_RotateTowardByAngle_maybe 0x98f300 -> 0x005841a8), normalised again, moves the
        // position (+0x134) by +0x10 x dt / the kind's +0x1d0.
        const RwFrame* frame =
            static_cast<CSGMovable*>(static_cast<IKHook*>(static_cast<IKSerializable*>(m_unk694))->m_pKGLObject)->m_pRwFrame;
        float dy = m_v3Position.y - frame->ltm.pos.y;
        float dx = m_v3Position.x - frame->ltm.pos.x;
        float dz = m_v3Position.z - frame->ltm.pos.z;
        float length = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));  // 0x00010690
        if (length != 0.0f) {  // TOC +0x1098
            const float inverse = 1.0f / length;  // TOC +0x1094
            dz = dz * inverse;
            dx = dx * inverse;
            dy = dy * inverse;
        }
        CVector3 direction{dx, dy, dz};
        CVector3 axisX{1.0f, 0.0f, 0.0f};  // 0x00c50d34 (TOC +0x111c)
        float pitch;
        std::memcpy(&pitch, &now->m_unk18, sizeof pitch);
        CVector3 pitched;
        Vec3_RotateTowardByAngle(&pitched, &direction, &axisX, pitch);
        CVector3 axisY{0.0f, 1.0f, 0.0f};  // 0x00c50d40 (TOC +0x10b4)
        CVector3 turned;
        Vec3_RotateTowardByAngle(&turned, &pitched, &axisY, now->m_unk1c);
        dy = turned.y;
        dx = turned.x;
        dz = turned.z;
        length = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            dz = dz * inverse;
            dx = dx * inverse;
            dy = dy * inverse;
        }
        const float step = now->m_unk10 * clock->m_afDeltaTime[0] / m_unk884->m_unk1d0;
        m_v3Position.z = ppc::fmadds(step, dz, m_v3Position.z);
        m_v3Position.x = ppc::fmadds(dx, step, m_v3Position.x);
        m_v3Position.y = ppc::fmadds(step, dy, m_v3Position.y);
    }
    static_cast<CKGrpS08Enemy*>(enemy::EnemyGroup())->SignalEnemyHit();  // 0x00267090
}

// 0x0029dfd8 CKHkS08Enemy_UpdateTargetAndDestination (vt+0x12c)
void CKHkS08Enemy::UpdateTargetAndDestination(IKTime* clock) {
    UpdateTargetingAndAwareness(clock);  // 0x0028fcd0
    UpdateMoveDestination(clock);        // 0x00290338
}

// 0x0029e028 CKHkS08Enemy_UpdateTimers_maybe: the enemy's timers by the frame's delta (each against the kind's limit),
// +0x870 (time unseen: back to 0 while the node is drawn this frame), +0x1f4 down by the scaled delta (+0x1fc).
void CKHkS08Enemy::UpdateTimers(IKTime* clock) {
    CKS08EnemyCpnt* cfg = Cfg();
    if (cfg->m_unk1c0 > m_unk67c) m_unk67c = m_unk67c + clock->m_afDeltaTime[0];
    if (cfg->m_unk1a8 > m_unk530) m_unk530 = m_unk530 + clock->m_afDeltaTime[0];
    if ((cfg->m_unk1f8 != 0 || cfg->m_unk1f9 != 0) && cfg->m_unk220 > m_unk6b0) {
        m_unk6b0 = m_unk6b0 + clock->m_afDeltaTime[0];
    }
    if (cfg->m_unke8 != 0) {
        if (cfg->m_unkf4 > m_unk718) m_unk718 = m_unk718 + clock->m_afDeltaTime[0];
        if (m_unk714 > 0.0f) {
            m_unk714 = m_unk714 - clock->m_afDeltaTime[0];
        } else if (m_unk72c != 0 && m_mainState != 5 && m_mainState != 0x22) {
            m_unk72c = 0;
        }
    }
    m_unk278 = m_unk278 - clock->m_afDeltaTime[0];
    if (m_unk278 < 0.0f) m_unk278 = 0.0f;
    if (m_unk7e0 <= 1000.0f) m_unk7e0 = m_unk7e0 + clock->m_afDeltaTime[0];  // TOC +0x11b4
    if (m_unk8b4 <= 1000.0f) m_unk8b4 = m_unk8b4 + clock->m_afDeltaTime[0];
    CKEnemySectorCpnt* sector = static_cast<CKEnemySectorCpnt*>(m_unk18C[GetSectorIndex()]);
    CSGLeaf* node = static_cast<CSGLeaf*>(sector->m_apUnk04[0]);  // 0x002b3110
    if (node->m_ui16LastRenderedFrame == g_ui16RenderFrameCounter) {
        m_unk870 = 0.0f;
    } else if (Cfg()->m_unk550 >= m_unk870) {
        m_unk870 = m_unk870 + clock->m_afDeltaTime[0];
    }
    if (m_unk8a4 > 0.0f) {
        m_unk8a4 = m_unk8a4 - clock->m_afDeltaTime[0];
        if (m_unk8a4 <= 0.0f) m_unk8a0 = 0;
    }
    if (m_unk8b8 > 0.0f) m_unk8b8 = m_unk8b8 - clock->m_afDeltaTime[0];
    if (m_unk1f4 > 0.0f) m_unk1f4 = m_unk1f4 - m_unk1fc;
}

// 0x002a0810 CKHkS08Enemy_State00_Spawn_maybe: the spawn. Enter: the spawn animation (9, or 0x3d out of an egg: life
// flags bits 26-27 = 3), parts of category 2 hidden, on the ground (not kind 8), a random wait (+0x7fc, one rand draw
// between the kind's +0x4e8 and +0x4ec), the node hidden. Tick: after the wait the spawn explosion (an FX node of the
// kind's +0x128 [32] data) and the node shown with the volume groups on; when the animation ends, state 1. A squad state
// with +0x68 skips it all (state 1 at once). Leave: parts of category 2 back, kind 1 a random roar (one draw), kind 7 its
// roar.
uint8_t CKHkS08Enemy::MainState00_Spawn(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        const uint32_t mode = (m_bitArray >> 26) & 3u;  // lbz +0xc, >> 2 & 3
        if (mode == 1 || mode != 3) {
            RequestAnim(9, 0, 0, 0, 2.0e-2f, 0.0f);  // TOC +0x11e0 / +0x11ac
        } else {
            RequestAnim(0x3d, 0, 0, 0, 2.0e-2f, 0.0f);
            m_unk684 = 0.0f;
        }
        ClearPartsFlagForCategory(2);  // 0x0027d018
        m_unk7c4 = 0;
        if (((m_bitArray >> 26) & 3u) == 3) {
            m_unk7fc = 0.0f;
            RequestAnim(0x3d, 0, 0, 0, 2.0e-2f, 0.0f);
        } else {
            if (m_ui8EnemyClassType != 8) {
                CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
                collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &m_v3Position.x, 1);  // 0x00196540
                if (m_GrdContDatasInOut.m_eContactStatus == 0) m_v3Position.y = m_v3Position.y - m_GrdContDatasInOut.m_fdH;
            }
            const float r = static_cast<float>(static_cast<double>(static_cast<uint32_t>(Rand_Int()) & 0xffffu));
            CKS08EnemyCpnt* cfg = Cfg();
            const float low = cfg->m_unk4e8;
            const float range = cfg->m_unk4ec - low;
            m_unk1fc = 0.0f;
            m_unk774 = 0.0f;
            m_unk7fc = ppc::fmadds(r / 65535.0f, range, low);  // TOC +0x11c4
        }
        CSGLeaf* node = static_cast<CSGLeaf*>(m_pKGLObject);
        node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;  // hidden
        if (m_unk680 != nullptr) {
            static_cast<CKHkS08Egg*>(m_unk680)->AssignEnemy(this);  // 0x00473630
            m_unk848 = 0.0f;
        }
        m_unk86c = 0;
        CKS08FightZoneCpnt* zone = SquadFightZone(m_pGroupSquad)->m_pFightZoneCpnt;
        if (zone->m_unk94 != 0) {
            // STUB(C2.8: transportables): the zone's transportable (+0x94) offered to the carrier (vt+0xf4, vt+0xf0),
            // CKS08CarrierEnemy_ResetStateMachine_maybe 0x4c95e8, its node shown, kept in +0x738, the zone's cleared.
            DOTD_STUB_ONCE("CKHkS08Enemy_State00_Spawn_maybe: the zone's transportable (C2.8)");
        }
        m_unk888 = 0;
        return 0;
    }
    if (phase == 2) {
        SetPartsFlagForCategory(2);  // 0x0027cf30
        m_unk774 = 1.0f;  // TOC +0x11bc
        if (m_ui8EnemyClassType == 1) {
            const uint32_t r = static_cast<uint32_t>(Rand_Int());
            PlaySound(((r >> 15) & 1u) + 0x2a, 1, m_pKGLObject);  // 0x002795c0
        }
        if (m_ui8EnemyClassType == 7) PlaySound(0x2a, 1, m_pKGLObject);
        return 0;
    }
    if (phase != 0) return 0;

    CKGrpSquad* squad = static_cast<CKGrpSquad*>(m_pGroupSquad);
    if (squad->m_vStates.m_pBlock[squad->m_unk55].m_unk68 != 0 && ((m_bitArray >> 26) & 3u) != 3) {
        EnableVolumeGroup(0);  // vt+0xf8
        EnableVolumeGroup(1);
        EnableVolumeGroup(2);
        static_cast<CSGLeaf*>(m_pKGLObject)->m_sgProperties &= 0xfffffffbu;
        return 1;
    }
    if (m_unk7fc > 0.0f && ((m_bitArray >> 26) & 3u) != 3) {
        m_unk774 = 0.0f;
        m_unk7fc = m_unk7fc - clock->m_afDeltaTime[0];
        return 0;
    }
    uint32_t mode = (m_bitArray >> 26) & 3u;
    if (mode == 3 && m_unk680 != nullptr) {
        CKHkS08Egg* egg = static_cast<CKHkS08Egg*>(m_unk680);
        if (egg->m_fUnk48 >= m_unk848) {
            const float elapsed = clock->m_afDeltaTime[0] + m_unk848;
            m_unk774 = 0.0f;
            m_unk848 = elapsed;
            if (elapsed > egg->m_fUnk48) {
                egg->AssignEnemy(this);                                     // 0x00473630
                static_cast<CKHkS08Egg*>(m_unk680)->ReleaseNextEnemy();     // 0x00473398
            }
            RequestAnim(0x3d, 0, 0, 0, 2.0e-2f, 0.0f);
            return 0;
        }
        if (m_unk894 > 0.0f) {
            m_unk894 = m_unk894 - clock->m_afDeltaTime[0];
            return 0;
        }
    }
    bool showNow = false;  // the shown-and-enabled block (0x2a0cf4)
    bool tail = false;     // straight to the mark sounds and the end test (0x2a0d9c)
    IKFx* explosion = static_cast<IKFx*>(m_unk868);
    if (explosion != nullptr) {
        if ((explosion->m_baFxData & 1) == 0) {
            if (m_unk86c != 0) {
                tail = mode != 3;
                showNow = mode == 3;
            } else if (mode == 3) {
                showNow = true;
            } else {
                m_unk774 = 0.0f;
                return 0;
            }
        } else if (m_unk86c != 0) {
            tail = mode != 3;
            showNow = mode == 3;
        } else {
            showNow = true;
        }
    } else if (m_unk86c != 0) {
        tail = mode != 3;
        showNow = mode == 3;
    } else if (mode == 3) {
        showNow = true;
    } else {
        // The spawn explosion started (0x2a0f4c).
        m_unk774 = 0.0f;
        EnableVolumeGroup(0);  // vt+0xf8
        EnableVolumeGroup(1);
        EnableVolumeGroup(2);
        IKFxData* data = static_cast<IKFxData*>(Cfg()->m_vUnk128.m_pBlock[0x20]);  // +0x128 [32]
        CKSrvFx* service = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
        IKFx* started = nullptr;
        if (m_ui8EnemyClassType != 8) {
            const uint32_t nodeClass = data->GetAssociatedFxClassIdentifier();  // vt+0x54
            const uint32_t type = data->GetAssociatedFxClassType();             // vt+0x58
            const CKSrvFx::CUnderMappingindex* under = nullptr;
            for (uint32_t i = 0; i < service->m_ui32EltNb && under == nullptr; ++i) {
                const CKSrvFx::CMappingindex& mapping = service->m_apMappingIndexTable[i];
                if (mapping.m_ui32ClassId != nodeClass || mapping.m_ui32NbTypeFx == 0) continue;
                for (uint32_t j = 0; j < mapping.m_ui32NbTypeFx; ++j) {
                    if (static_cast<uint32_t>(mapping.m_aUnderMapping[j].m_i32FxTypeId) == type) {
                        under = &mapping.m_aUnderMapping[j];
                        break;
                    }
                }
            }
            if (under != nullptr) {
                for (uint32_t k = 0; k < under->m_ui32MaxSize; ++k) {
                    IKFx* node = static_cast<IKFx*>(under->m_apFxArrayForTypeId[k]);
                    if ((node->m_baFxData & 1) == 0 || (node->m_baFxData & 2) != 0) continue;
                    node->SetFxData(data);  // vt+0x84
                    node->m_baFxData = static_cast<uint8_t>((node->m_baFxData & 0xfd) | 2);  // reserved
                    node->SetOwner(this);   // vt+0x88
                    node->Vf64();           // vt+0x64 start
                    started = node;
                    m_unk868 = node;
                    CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(node);
                    explosion->SetTranslation(&m_v3Position, this);  // 0x001b66e8
                    explosion->Trigger(this, 0);                     // 0x001b82a8
                    node->ReleaseReservation(this);                  // vt+0x54
                    break;
                }
            }
        }
        if (started != nullptr && m_unk868 != nullptr) return 0;
        m_unk868 = nullptr;
        m_unk774 = 1.0f;
        m_unk86c = 1;
        static_cast<CSGLeaf*>(m_pKGLObject)->m_sgProperties &= 0xfffffffbu;
        return 0;
    }
    if (showNow) {
        m_unk774 = 1.0f;
        m_unk86c = 1;
        static_cast<CSGLeaf*>(m_pKGLObject)->m_sgProperties &= 0xfffffffbu;
        EnableVolumeGroup(0);  // vt+0xf8
        EnableVolumeGroup(1);
        EnableVolumeGroup(2);
        tail = true;
    }
    if (tail) {
        mode = (m_bitArray >> 26) & 3u;
        if (mode != 3) {
            const float time = LayerSlotAnimTime(0, 0);
            PlayAnimMarkSounds(time, time + clock->m_afDeltaTime[0]);  // 0x00286c08
            mode = (m_bitArray >> 26) & 3u;
        }
        if (mode == 3) {
            // The egg's Bezier rise (0x2a129c): +0x684 advances by +0x1fc; past the egg's +0x3c, state 1.
            m_unk684 = m_unk684 + m_unk1fc;
            CKHkS08Egg* egg = static_cast<CKHkS08Egg*>(m_unk680);
            if (!(egg->m_fUnk3C >= m_unk684)) return 1;
            // From the egg's node (p0) to its spawn point +0x688 (p3; the node when the point is the null vector), the
            // two inner points raised by the egg's +0x38 and pulled a quarter of the flat distance toward each other.
            const RwV3d& node = FrameLtm(static_cast<CSGMovable*>(egg->m_pKGLObject)->m_pRwFrame)->pos;
            const CVector3 p0 = {node.x, node.y, node.z};
            CVector3 p1 = p0;
            CVector3 p3 = egg->GetSpawnPoint(m_unk688);  // 0x004736d0
            CVector3 p2 = p3;
            if (p3.x == 0.0f && p3.y == 0.0f && p3.z == 0.0f) {  // TOC +0x1234: 0x00c50d64
                p2 = p0;
                p3 = p0;
            }
            float dx = p2.x - p1.x;
            const float raised = p1.y + egg->m_fUnk38;
            float dz = p2.z - p1.z;
            float dy = raised - raised;
            p1.y = raised;
            p2.y = raised;
            const float squared = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
            const float length = std::sqrt(squared);  // Math_Sqrtf 0x10690
            const float again = std::sqrt(squared);
            if (again != 0.0f) {                    // TOC +0x11ac
                const float k = 1.0f / again;       // TOC +0x11bc
                dz = dz * k;
                dx = dx * k;
                dy = dy * k;
            }
            const float back = length * -0.25f;  // TOC +0x1248
            const float ahead = length * 0.25f;  // TOC +0x1244
            p2.z = ppc::fmadds(dz, back, p2.z);
            p2.x = ppc::fmadds(dx, back, p2.x);
            p2.y = ppc::fmadds(back, dy, p2.y);
            p1.z = ppc::fmadds(dz, ahead, p1.z);
            p1.x = ppc::fmadds(dx, ahead, p1.x);
            p1.y = ppc::fmadds(ahead, dy, p1.y);
            Vec3_CubicBezier(m_unk684 / egg->m_fUnk3C, &m_v3Position, &p0, &p1, &p2, &p3);  // 0x00010fc0
            return 0;
        }
        return IsAnimEndReached(m_unk1fc * m_unk774, 0, 0);  // 0x00285558
    }
    return 0;
}

// 0x002a4190 CKHkS08Enemy_State01: the awake stance (the squad's idle around its place, the alert, the moves toward a
// target). Enter: +0x398 = 1, the idle animation (0, or 1 when the squad state's +0x30 is not 1; kind 8 with +0x7b4:
// 0x3e) at a random start time (one rand draw times the animation's length), the volume groups on, parts 1 and 2 shown,
// the weapon in hand under hot spot 2. Leave: the path request cancelled, +0x79c zeroed. Tick (see the steps below):
// the equipment machine, a move target (state 0x17), the stance movement, the update skip bit (state 0x16).
uint8_t CKHkS08Enemy::MainState01(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        m_unk398 = 1;
        if (m_ui8EnemyClassType == 8 && m_unk7b4 != 0) {
            const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
            const float length = GetAnimDuration(0x3e, 0, 0);  // 0x00285638
            RequestAnim(0x3e, 0, 0, 0, 0.5f, (static_cast<float>(static_cast<double>(r)) / 65535.0f) * length);
            m_unk80c = 0.0f;
            m_unk808 = 0.0f;
            m_unk750 = 1;
            // 0x2a4d40: the layer 0 dictionary's words 0x3f / 0x3e / 0x40 (+0xfc / +0xf8 / +0x100) as the blend pair at
            // +0x808 / +0x80c.
            const CAnimationDictionary* dictionary = GetSectorCpnt()->GetAnimDictionary(0);  // 0x002771c0, 0x002b3128
            const uint32_t* words = reinterpret_cast<const uint32_t*>(dictionary->m_apAnimations);
            SetSignedBlendAnimPair(m_unk808, m_unk80c, words[0xfc / 4], words[0xf8 / 4], words[0x100 / 4]);  // 0x00285c10
        } else {
            CKGrpSquad* squad = static_cast<CKGrpSquad*>(m_pGroupSquad);
            const uint8_t anim = squad->m_vStates.m_pBlock[squad->m_unk55].m_unk30 == 1 ? 0 : 1;
            const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
            const float length = GetAnimDuration(anim, 0, 0);  // 0x00285638
            RequestAnim(anim, 0, 0, 0, 0.5f, (static_cast<float>(static_cast<double>(r)) / 65535.0f) * length);  // TOC +0x11a4
            m_unk750 = 0;
        }
        m_unk798 = Cfg()->m_unk4a8;
        EnableVolumeGroup(0);  // vt+0xf8
        EnableVolumeGroup(1);
        EnableVolumeGroup(2);
        SetPartsFlagForCategory(1);  // 0x0027cf30
        SetPartsFlagForCategory(2);
        CKHkS08Weapon* weapon = static_cast<CKHkS08Weapon*>(m_unk520);
        if (weapon == nullptr) return 1;
        CSGLeaf* node = static_cast<CSGLeaf*>(weapon->m_pKGLObject);
        node->m_sgProperties &= 0xfffffffbu;
        if (node->m_pParent != nullptr) {
            node->m_pParent->RemoveChild(node);  // vt+0x78
            RwFrame* frame = node->m_pRwFrame;
            frame->modelling.pos.z = 0.0f;
            frame->modelling.pos.x = 0.0f;
            frame->modelling.pos.y = 0.0f;
            frame->modelling.flags &= 0xfffdffffu;
            RwFrame_MarkDirty(frame);  // 0x00010698
        }
        CKEnemySectorCpnt* sector = static_cast<CKEnemySectorCpnt*>(m_unk18C[GetSectorIndex()]);
        static_cast<CSGHotSpot*>(sector->m_apUnk14[2])->AttachVolume(node);  // 0x002b31e0, 0x000ce2b8
        static_cast<CKHkS08Weapon*>(m_unk520)->m_unkA9 = 0;
        static_cast<CKHkS08Weapon*>(m_unk520)->SetEjected(0);  // 0x002b2bc0
        static_cast<CKHkS08Weapon*>(m_unk520)->SetLanded(0);   // 0x002b2a70
        static_cast<CKHkS08Weapon*>(m_unk520)->m_inHandA8 = 1;
        static_cast<CKHkS08Weapon*>(m_unk520)->m_pOwnerB4 = this;
        return 1;
    }
    if (phase == 2) {
        m_PFCpnt.CancelPathRequest();  // 0x001e2820
        m_unk750 = 0;
        m_unk79c = 0.0f;  // the zero vector (TOC +0x1234)
        m_unk7a0 = 0.0f;
        m_unk7a4 = 0.0f;
        return 1;
    }
    if (phase != 0) return 1;

    // An enemy that needs equipment and has none starts the equipment machine (aux state 1).
    if (m_unk520 == nullptr && m_unk730 != 0 && m_auxState == 0xff) {
        const uint8_t old = m_auxState;
        if (old != 0xff) CallAuxState(old, clock, 2, 1);
        m_auxState = 1;
        CallAuxState(1, clock, 1, old);
    }
    if (m_ui8EnemyClassType == 8) {
        // STUB(C2.9: later levels; LVL010's ten CKHkS08Enemy are all kind 0, census lvl010_ingame): 0x2a4948..0x2a4b24
        // and its branches 0x2a4d98 / 0x2a5164 / 0x2a57c0 / 0x2a5a88 (the flying kind's hover: the dictionary blend pair
        // toward +0x37c (FloatApproach_Step 0x2436e8, SetSignedBlendAnimPair 0x285c10), at the animation's end a random
        // sound 0x40..0x42 (one rand draw)); then the equipment machine as below.
        DOTD_STUB_ONCE("CKHkS08Enemy_State01: kind 8 (C2.9, no LVL010 enemy)");
    }
    // The equipment machine's tick (the aux rows).
    {
        const uint8_t state = m_auxState;
        if (state != 0xff) {
            const uint8_t next = CallAuxState(state, clock, 0, state);
            const uint8_t old = m_auxState;
            if (next != old) {
                if (old != 0xff) CallAuxState(old, clock, 2, next);
                m_auxState = next;
                if (next != 0xff) CallAuxState(next, clock, 1, old);
            }
        }
    }
    CVector3 target;
    if (m_unk7f9 != 0) {
        target = ChooseMoveTarget();  // 0x002808e8
        m_unk85c = target.x;
        m_unk864 = target.z;
        m_unk860 = target.y;
        if (target.x != 0.0f || target.y != 0.0f || target.z != 0.0f) return 0x17;  // the zero vector (TOC +0x1234)
    }
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &m_unk140, 1);  // 0x00196540 (the previous position)
    if (m_unk870 >= Cfg()->m_unk550) {
        CKEnemySectorCpnt* sector = static_cast<CKEnemySectorCpnt*>(m_unk18C[GetSectorIndex()]);
        CSGLeaf* node = static_cast<CSGLeaf*>(sector->m_apUnk04[0]);  // 0x002b3110
        CKGrpFightZone* zone = static_cast<CKGrpFightZone*>(static_cast<CKGrpSquad*>(m_pGroupSquad)->m_pParent);
        if (node->m_ui16LastRenderedFrame == g_ui16RenderFrameCounter && zone->m_pFightZoneCpnt->m_unk04 != 5 &&
            m_unk6c0 <= 0.0f) {
            bool blocked = false;
            if (Cfg()->m_unk338 != 0) {
                // 0x2a60a8: a target hero (+0x330, key 0x25c2) not within the zone component's +0x48 (squared, xz) of
                // its first reference keeps the enemy in place.
                CKS08FightZoneCpnt* zoneCpnt = static_cast<CKS08FightZoneCpnt*>(SquadFightZone(m_pGroupSquad)->m_pFightZoneCpnt);
                IKSerializable* ref = zoneCpnt->GetFirstNonNullRef4C();  // 0x0025ab50, 0x00274b18
                if (ref != nullptr && m_unk330->IsKindOfClass(0x25c2) != 0) {  // vt+0x08
                    const float* hero = static_cast<CKHkS08Hero*>(static_cast<IKSerializable*>(m_unk330))->GetPositionPtr();  // 0x00361968
                    IKHook* first = static_cast<IKHook*>(
                        static_cast<CKS08FightZoneCpnt*>(SquadFightZone(m_pGroupSquad)->m_pFightZoneCpnt)->GetFirstNonNullRef4C());
                    const RwV3d& at = FrameLtm(static_cast<CSGMovable*>(first->m_pKGLObject)->m_pRwFrame)->pos;
                    const float dz = hero[2] - at.z;
                    const float dx = hero[0] - at.x;
                    const float limit = static_cast<CKS08FightZoneCpnt*>(SquadFightZone(m_pGroupSquad)->m_pFightZoneCpnt)->m_unk48;
                    if (!(ppc::fmadds(dx, dx, dz * dz) < limit)) blocked = true;
                }
            }
            if (!blocked) {
                const uint16_t groundFlags = static_cast<const ICollisionMesh*>(m_GrdContDatasInOut.m_pGround)->m_ui16PropertiesFlags;
                if ((groundFlags & 0x400u) == 0) {
                    target = ChooseMoveTarget();  // 0x002808e8
                    m_unk85c = target.x;
                    m_unk864 = target.z;
                    m_unk860 = target.y;
                    if (target.x != 0.0f || target.y != 0.0f || target.z != 0.0f) return 0x17;
                }
            }
        }
    }
    if (m_unk708 != 0 && GetCurrentAnim(0, 0) != 0x33) {  // 0x00285408
        RequestAnim(0x33, 0, 0, 0, 0.1f, 0.0f);  // TOC +0x11a8 / +0x11ac
    }
    if ((m_bitArray & 8u) != 0 && m_mainState != 0x16 && m_mainState != 0xff) {
        m_bitArray &= 0xfffffff7u;
        return 0x16;
    }
    bool steer = false;
    if (m_awareState == 2 && !(m_unk730 != 0 && m_unk520 == nullptr)) {
        // 0x2a5028: the alerted stance (AlertedStance below); -1 goes on to the tail.
        const int32_t next = AlertedStance(clock);
        if (next >= 0) return static_cast<uint8_t>(next);
        goto tail;
    } else if (m_unk674 != 0 && m_auxState != 4) {
        steer = true;
    } else if (m_unk520 == nullptr && m_auxState == 1) {
        steer = true;
    } else {
        steer = static_cast<CKGrpS08Enemy*>(g_pEngine->m_gameManager->m_unk04[0])->m_unk1bc == 0;  // GetEnemyGroup 0x276f58, +0x1bc
    }
    if (steer) {
        // The stance movement toward +0x37c along +0x388 (its y zeroed, normalised).
        m_unk38c = 0.0f;
        const float length = std::sqrt(ppc::fmadds(m_unk390, m_unk390, ppc::fmadds(m_unk388, m_unk388, m_unk38c * m_unk38c)));
        if (length != 0.0f) {
            const float k = 1.0f / length;  // TOC +0x11bc
            m_unk390 = k * m_unk390;
            m_unk388 = k * m_unk388;
            m_unk38c = k * m_unk38c;
        }
        float yaw;
        yaw = m_unk154;  // +0x154 the yaw
        CVector3 target{m_unk37c, m_unk380, m_unk384};
        CVector3 direction{m_unk388, m_unk38c, m_unk390};
        SteerGround(&m_v3Position, &yaw, &m_unk158, &target, &direction, m_unk398);  // 0x2a4bf8
        m_unk154 = yaw;
    }
tail:
    // The tail (0x2a4c00): parts 1 and 2 shown unless the path finding's result has 0x40 and its flags not 0x400.
    if ((static_cast<uint32_t>(m_PFCpnt.m_unk3c) & 0x40u) == 0 || (m_PFCpnt.m_bits70 & 0x400u) != 0) {
        SetPartsFlagForCategory(1);  // 0x0027cf30
        SetPartsFlagForCategory(2);
    } else {
        ClearPartsFlagForCategory(1);  // 0x0027d018
        ClearPartsFlagForCategory(2);
    }
    if (m_auxState != 4 && GetCurrentAnim(0, 0) != 0x2e) ResetLayer0Slot0StateByMode();  // 0x00285408, 0x002857b8
    TickAttackCooldowns();  // vt+0x148
    return 1;
}

// 0x002aba20 CKHkS08Enemy_State02_Combat_maybe: the hit state runs the reaction machine (+0x554, its state +0x558).
// Enter: the current reaction ticked once and its answer switched to. Leave: back to reaction 0. Tick (+0x7f8 cleared
// first): the reaction ticked and switched; a reaction asking for a move (+0x7f8) with a move target (+0x85c) goes back
// to reaction 0 and the main state 0x17; reaction 0 ends the hit: 0x26 for an enemy off the nav mesh (life flag
// 0x2000000) whose kind does not recover (+0x28c), 0x1a when it does and stands in its graph node walkable, else 1;
// reaction 10 (clock null) goes back to 0 and the state 0x15. Otherwise 2.
uint8_t CKHkS08Enemy::MainState02_Combat(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        const uint8_t current = m_reactState;
        if (current == 0xff) return 2;
        const uint8_t next = CallReactState(current, clock, 0, current);
        const uint8_t old = m_reactState;
        if (next == old) return 2;
        if (old != 0xff) CallReactState(old, clock, 2, next);
        m_reactState = next;
        if (next == 0xff) return 2;
        CallReactState(next, clock, 1, old);
        return 2;
    }
    if (phase == 2) {
        const uint8_t old = m_reactState;
        if (old == 0) return 2;
        if (old != 0xff) CallReactState(old, clock, 2, 0);
        m_reactState = 0;
        CallReactState(0, clock, 1, old);
        return 2;
    }
    if (phase != 0) return 2;
    m_unk7f8 = 0;
    const uint8_t current = m_reactState;
    if (current != 0xff) {
        const uint8_t next = CallReactState(current, clock, 0, current);
        const uint8_t old = m_reactState;
        if (next != old) {
            if (old != 0xff) CallReactState(old, clock, 2, next);
            m_reactState = next;
            if (next != 0xff) CallReactState(next, clock, 1, old);
        }
        if (m_unk7f8 != 0) {
            const CVector3 target = ChooseMoveTarget();  // 0x002808e8
            m_unk85c = target.x;
            m_unk864 = target.z;
            m_unk860 = target.y;
            if (!(target.x == 0.0f && target.y == 0.0f && target.z == 0.0f)) {  // the zero vector (TOC +0x1234)
                const uint8_t from = m_reactState;
                if (from != 0xff) CallReactState(from, clock, 2, 0);
                m_reactState = 0;
                CallReactState(0, clock, 1, from);
                return 0x17;
            }
        }
        const uint8_t now = m_reactState;
        if (now == 0) {
            if ((m_bitArray & 0x2000000u) == 0) return 1;
            if (m_unk884->m_unk28c == 0) return 0x26;
            CKSrvPathFinding* pathFinding = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);  // TOC +0x11cc
            CPFPoint point;
            point.m_position = m_v3Position;
            point.m_unk0c = m_PFCpnt.m_Destination.m_unk0c;
            pathFinding->FindSectorForPoint(&point);  // 0x001e5ca0
            if (PointInNodeBox(pathFinding, &point) &&
                (pathFinding->IsPointWalkable(&point, &m_PFCpnt.m_CharacterType) & 0xffu) != 0) {  // 0x001e42d0
                return 0x1a;
            }
            return 1;
        }
        if (now != 0xa) return 2;
        CallReactState(0xa, nullptr, 2, 0);
        m_reactState = 0;
        CallReactState(0, nullptr, 1, 0xa);
        return 0x15;
    }
    return 2;
}

// 0x0029dd98 CKHkS08Enemy_vf158: returns 3.
uint8_t CKHkS08Enemy::MainState03(IKTime* /*clock*/, int32_t /*phase*/, uint8_t /*other*/) {
    return 3;
}

// 0x0029dda0 CKHkS08Enemy_vf15C: returns 4.
uint8_t CKHkS08Enemy::MainState04(IKTime* /*clock*/, int32_t /*phase*/, uint8_t /*other*/) {
    return 4;
}

namespace {
// The guard's facing (inlined twice in 0x2a1db8): the yaw of the flat unit direction (x, z) away from the target:
// acos(-z), mirrored (2 pi - a) when x > 0; outside [-1, 1] pi (-z below 0) or 0 (the original's own range test:
// blt / ble on -z, so a NaN takes the acos).
float GuardYaw(float x, float z) {
    const float nz = -z;
    bool outside;
    if (nz < 0.0f) {
        outside = nz < -1.0f;  // TOC +0x11d8
    } else {
        outside = nz > 1.0f;   // ble: not greater (a NaN is inside)
    }
    if (!outside) {
        const float a = crt::Acosf(nz);  // 0x0098e1a0 Math_Acosf
        if (!(x > 0.0f)) return a;
        return 6.28318548f - a;  // TOC +0x1250 (0x40c90fdb)
    }
    if (nz < 0.0f) return 3.14159274f;  // TOC +0x124c (0x40490fdb)
    return 0.0f;
}
}  // namespace

// The guard's direction (+0x248): from the target's node (its modelling position) to the enemy, level (y 0), unit
// length; the facing (+0x154) from it.
void CKHkS08Enemy::GuardFaceAwayFromTarget() {
    const RwV3d& target = static_cast<CSGMovable*>(m_unk330->m_pKGLObject)->m_pRwFrame->modelling.pos;
    float dx = m_v3Position.x - target.x;
    const float dy = m_v3Position.y - target.y;
    float dz = m_v3Position.z - target.z;
    m_unk248 = dx;
    m_unk24c = dy;
    m_unk24c = 0.0f;  // stfs of the zero over the y just stored
    m_unk250 = dz;
    const float length =
        static_cast<float>(enemy::MathSqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, m_unk24c * m_unk24c))));
    if (length != 0.0f) {
        const float k = 1.0f / length;  // TOC +0x11bc
        dz = k * m_unk250;
        dx = k * m_unk248;
        m_unk250 = dz;
        m_unk248 = dx;
        m_unk24c = k * m_unk24c;
    }
    m_unk154 = GuardYaw(dx, dz);
}

// The weapon knocked out of the hand by the hit's stun (the gauge +0x278 reached the kind's +0xdc): the gauge
// cleared, the weapon's push time the knockback lift (+0x274), its eject velocity along the enemy's flat facing (the
// node's LTM at, y 0, unit length); returns whether it was ejected (main state 0x21 then).
bool CKHkS08Enemy::GuardEjectWeapon() {
    CKHkS08Weapon* weapon = static_cast<CKHkS08Weapon*>(m_unk520);
    if (weapon == nullptr || !(m_unk278 >= m_unk884->m_unkdc) || m_mainState == 7) return false;  // cror gt|eq
    m_unk278 = 0.0f;
    weapon->m_fPushTime = m_unk274;
    const RwV3d& at = FrameLtm(static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame)->at;
    CVector3 eject{at.x, 0.0f, at.z};
    const float span = static_cast<float>(enemy::MathSqrtf(ppc::fmadds(eject.z, eject.z, ppc::fmadds(eject.x, eject.x, 0.0f))));
    if (span != 0.0f) {
        const float k = 1.0f / span;  // TOC +0x11bc
        eject.z = eject.z * k;
        eject.x = eject.x * k;
        eject.y = eject.y * k;
    }
    weapon->SetEjectVelocity(&eject);  // 0x002b2218
    return true;
}

// 0x002a1db8 CKHkS08Enemy_State05_Guard_maybe (main row 5, ported from the instructions: Ghidra's decompile drops the
// acos branches). Enter: the guard animation (0x3f for a kind 5 with a shield, else 0x30; restart, blend 0.02), facing
// away from the target, the guard sound 0xb; a pending hit then: a hero damage (0x998c) adds its +0x2c x the kind's
// +0xe0 to the stun gauge +0x278 and may knock the weapon out (state 0x21); else the hit counter +0x72c and the guard
// impact FX 0x16 at the hit. Leave: life bit 0x10000 cleared, +0x354 cleared, +0x714 = the kind's +0xec. Tick: a
// pending hit: a stun damage (0x9acc) adds to the gauge the same way and may knock the weapon out; below the kind's
// guard count (+0x33c) the guard restarts (the hit counted, the animation, the FX) unless an element damage (0x99cc);
// at the count a non-element damage ends the guard (0x22: block and counter); then facing away, state 1 at the
// animation's end.
uint8_t CKHkS08Enemy::MainState05_Guard(IKTime* /*clock*/, int32_t phase, uint8_t /*other*/) {
    const uint8_t guardAnim = static_cast<uint8_t>(m_unk524 != nullptr && m_ui8EnemyClassType == 5 ? 0x3f : 0x30);
    if (phase == 1) {
        RequestAnim(guardAnim, 1, 0, 0, 0.02f, 0.0f);  // 0x00285340; TOC +0x11e0 / +0x11ac
        GuardFaceAwayFromTarget();
        PlaySound(0xb, 0, m_pKGLObject);  // 0x002795c0
        if (m_unk239 != 0) {
            CKS08Damage* damage = m_unk27c;
            if (damage->IsKindOfClass(0x998c) != 0) {  // CKS08HeroDamage
                m_unk278 = ppc::fmadds(static_cast<CKS08StunDamage*>(damage)->m_unk2c, m_unk884->m_unke0, m_unk278);
            }
            if (GuardEjectWeapon()) return 0x21;
        }
        m_unk72c = m_unk72c + 1;
        SpawnHitFxAt(0x16, reinterpret_cast<const CVector3*>(m_unk23c));  // 0x0028c590
        return 5;
    }
    if (phase == 2) {
        m_bitArray &= 0xfffeffffu;  // rlwinm 15 / rotlwi 17
        m_unk354 = 0;
        m_unk714 = m_unk884->m_unkec;
        return 5;
    }
    if (phase != 0) return 5;
    if (m_unk239 != 0) {
        CKS08Damage* damage = m_unk27c;
        if (damage->IsKindOfClass(0x9acc) != 0) {  // CKS08StunDamage
            m_unk278 = ppc::fmadds(static_cast<CKS08StunDamage*>(damage)->m_unk2c, m_unk884->m_unke0, m_unk278);
        }
        if (GuardEjectWeapon()) return 0x21;
        // 0x2a2414: the guard holds.
        const uint32_t hits = m_unk72c + 1;
        bool restart = hits < static_cast<uint32_t>(m_unk884->m_unk33c);
        if (!restart) {
            // BUG(original): a pending hit without a damage object calls through a null pointer here (0x2a2480).
            if (m_unk27c->IsKindOfClass(0x99cc) == 0) return 0x22;  // CKS08ElementDamage
        } else {
            restart = m_unk27c->IsKindOfClass(0x99cc) == 0;
        }
        if (restart) {
            m_unk72c = m_unk72c + 1;
            RequestAnim(guardAnim, 1, 0, 0, 0.02f, 0.0f);
            SpawnHitFxAt(0x16, reinterpret_cast<const CVector3*>(m_unk23c));
        }
    }
    // 0x2a1e10
    GuardFaceAwayFromTarget();
    if (IsAnimEndReached(m_unk1fc, 0, 0)) return 1;  // 0x00285558
    return 5;
}

// 0x0029ec08 CKHkS08Enemy_State06_Dodge_maybe (vt+0x164): enter: the dodge animation (0x41 for a flying kind 8, else
// 0x31; blend 0.1), +0x6a8 / +0x6a4 cleared, +0x6ac (straight back) set; with both of the kind's +0x1f8 / +0x1f9 set
// +0x6ac is drawn, with +0x1f9 alone it is cleared; then +0x6ad (the side) is drawn (each draw (r & 0xffff) / 65535 <
// 0.5); the trail 2 on, the sound 0x17. Run: +0x6a4 += dt; the step (+0x158) is the
// node's backward axis (-modelling at), or it turned about Y by the kind's +0x1fc degrees (left with +0x6ad, right
// without), times +0x6a8 x dt; the position moves by it; the trail updated; at the animation's end (dt) 1, else 6.
// Leave: the trail 2 off, +0x6b0 cleared.
uint8_t CKHkS08Enemy::MainState06_Dodge(IKTime* /*clock*/, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        const uint8_t anim = (m_ui8EnemyClassType == 8 && m_unk7b4 != 0) ? 0x41 : 0x31;
        RequestAnim(anim, 0, 0, 0, 0.1f, 0.0f);  // 0x00285340; TOC +0x11a8 / +0x11ac
        const CKS08EnemyCpnt* cfg = m_unk884;
        m_unk6a8 = 0.0f;
        m_unk6ac = 1;
        m_unk6a4 = 0.0f;
        if (cfg->m_unk1f8 != 0) {
            if (cfg->m_unk1f9 != 0) {
                const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;  // 0x00011500
                m_unk6ac = (static_cast<float>(static_cast<double>(r)) / 65535.0f < 0.5f) ? 1 : 0;  // TOC +0x11c4 / +0x11a4
            }
        } else if (cfg->m_unk1f9 != 0) {
            m_unk6ac = 0;
        }
        const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
        m_unk6ad = (static_cast<float>(static_cast<double>(r)) / 65535.0f < 0.5f) ? 1 : 0;
        SetAttackTrailActive(2, 1, 0);  // 0x0028b960
        PlaySound(0x17, 0, m_pKGLObject);  // 0x002795c0
        return 6;
    }
    if (phase == 2) {
        SetAttackTrailActive(2, 0, 0);
        m_unk6b0 = 0.0f;
        return 6;
    }
    if (phase != 0) return 6;
    m_unk6a4 = m_unk6a4 + m_unk1fc;
    const RwV3d& at = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame->modelling.at;
    float vx;
    float vy;
    float vz;
    if (m_unk6ac != 0) {
        vx = -at.x;
        vy = -at.y;
        vz = -at.z;
    } else {
        const CVector3 back{-at.x, -at.y, -at.z};
        const float angle = m_unk884->m_unk1fc * (m_unk6ad != 0 ? 0.01745329f : -0.01745329f);  // TOC +0x11e4 / +0x11e8
        const CVector3 turned = enemy::Vec3_RotateAboutY(angle, &back);  // 0x0027d460
        vx = turned.x;
        vy = turned.y;
        vz = turned.z;
    }
    const float s = m_unk6a8 * m_unk1fc;
    vz = s * vz;
    vx = s * vx;
    vy = s * vy;
    m_unk158 = CVector3{vx, vy, vz};
    m_v3Position.x = m_v3Position.x + vx;
    m_v3Position.y = m_v3Position.y + vy;
    m_v3Position.z = m_v3Position.z + vz;
    SetAttackTrailActive(2, 1, 1);
    return IsAnimEndReached(m_unk1fc, 0, 0) ? 1 : 6;  // 0x00285558
}

// 0x0029dda8 CKHkS08Enemy_vf168: returns 11.
uint8_t CKHkS08Enemy::MainState0B(IKTime* /*clock*/, int32_t /*phase*/, uint8_t /*other*/) {
    return 11;
}

// 0x0029ddb0 CKHkS08Enemy_vf16C: returns 12.
uint8_t CKHkS08Enemy::MainState0C(IKTime* /*clock*/, int32_t /*phase*/, uint8_t /*other*/) {
    return 12;
}

namespace {
// 0x00a70248 (TOC +0x11ec): per enemy kind, the first of the attack volumes in +0x2c; the kind's volume count is byte 3
// of its four bytes at +0x24 (the same data as CKS08EnemyCpnt's type table); +0x6c / +0x90 the kind's first attack
// sound and their count. Constant data.
const uint32_t kAttackVolumeFirst[9] = {3, 3, 8, 8, 8, 0xb, 0xe, 3, 7};
const uint8_t kAttackVolumeCount[9] = {1, 2, 2, 1, 2, 3, 2, 2, 2};
const uint32_t kAttackSoundFirst[9] = {42, 44, 44, 42, 42, 44, 42, 43, 42};
const uint32_t kAttackSoundCount[9] = {4, 6, 5, 8, 6, 5, 5, 4, 11};

// 0x002b3ec0 CKS08EnemyCpnt_GetAttackAnimTableEntryPtr_maybe: the attack's animation row base: the TOC +0x17e8 word of
// the kind's type (+0xb8) plus four rows per attack index (+0x24) of the selected attack (+0x11c[index]).
uint32_t AttackAnimBase(const CKS08EnemyCpnt* cfg, uint32_t index) {
    static const uint32_t kTypeAnimBase[9] = {0x56, 0x55, 0x4f, 0x4d, 0x4d, 0x41, 0x3f, 0x55, 0x43};  // 0x00a70400
    const CKS08EnemyAttack* attack = static_cast<const CKS08EnemyAttack*>(cfg->m_vUnk11c.m_pBlock[index]);
    return kTypeAnimBase[cfg->m_unkb8] + static_cast<uint32_t>(attack->m_unk24) * 4u;
}
}  // namespace

// The kind 5's weapon sparks (0x2a3e80 / 0x2a40d4): particles 0xb and 0xc at the weapon's hot spot (+0xac[1]) during
// the animations 0x52 / 0x53.
void CKHkS08Enemy::EmitWeaponSparks(uint8_t anim) {
    CVector3 at;
    static_cast<CSGHotSpot*>(static_cast<CKHkS08Weapon*>(m_unk520)->m_apUnkAC[1])->GetWorldPosition(&at);  // 0x000ce790
    if (static_cast<uint8_t>(anim - 0x52) > 1u) return;
    CVector3 a = at;
    EmitParticleAt(0xb, &a, nullptr, 0);  // 0x00278028
    CVector3 b = at;
    EmitParticleAt(0xc, &b, nullptr, 0);
}

// 0x002a3278 CKHkS08Enemy_State0D_AttackWindup_maybe: the attack's windup. Enter: the attack's animation (row base + 1),
// the approach point, +0x2a0 / +0x2a4 = its length, +0x2a8 = the kind's +0xfc, life bits 0x30000 cleared, the attack's
// damage put on its volumes, an attack sound (one rand draw), the hero's attack cooldown started (vt+0x17c), the
// weapon back in hand. Tick: out of the attack's range -> state 1 (life bit 0x20000); else the approach point, the
// steering toward it facing the hero (2D, or 3D for the flying attacks), the walk / stand animation; at the animation's
// end the strike (0xe) when facing the hero within the attack's angle, else 1; while it plays the marks' sounds.
uint8_t CKHkS08Enemy::MainState0D_AttackWindup(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    CKS08EnemyCpnt* cfg = m_unk884;
    if (phase == 1) {
        const uint8_t anim = static_cast<uint8_t>(AttackAnimBase(cfg, m_unk32c) + 1);  // 0x002b3ec0
        RequestAnim(anim, 0, 0, 0, 0.1f, 0.0f);  // TOC +0x11a8 / +0x11ac
        ComputeAttackApproachPoint();             // 0x00280e30
        const float length = GetAnimDuration(anim, 0, 0);  // 0x00285638
        m_unk2a4 = length;
        m_unk2a0 = length;
        m_unk2a8 = m_unk884->m_unkfc;
        m_bitArray &= 0xfffcffffu;
        const uint8_t kind = m_ui8EnemyClassType;
        CKS08EnemyAttack* attack = m_unk73c;
        if (attack->m_unk08 != 2) {
            for (uint32_t i = 0; i < kAttackVolumeCount[kind]; ++i) {
                if (m_unk73c->m_array48.m_data[i] != 0) {
                    static_cast<IKBoundingVolume*>(m_unk2C[kAttackVolumeFirst[kind] + i])->m_unk1c = attack->m_pDamage;
                }
            }
        }
        if (m_ui8EnemyClassType == 5) EmitWeaponSparks(anim);
        {
            const uint8_t k = m_ui8EnemyClassType;
            const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;  // 0x00011500
            const uint32_t sound = kAttackSoundFirst[k] + ((r * kAttackSoundCount[k]) >> 16);
            PlaySound(static_cast<uint8_t>(sound), 0, m_pKGLObject);  // 0x002795c0
        }
        if (m_unk891 != 0 && m_unk330 != nullptr && m_unk330->IsKindOfClass(CKHkS08Hero::kClassKey) != 0) {
            CKGrpS08Enemy* group = static_cast<CKGrpS08Enemy*>(g_pEngine->m_gameManager->m_unk04[0]);  // GetEnemyGroup
            group->StartAttackCooldown(static_cast<CKHkS08Hero*>(static_cast<IKSerializable*>(m_unk330))->GetDragonIndex(),
                                       this);  // vt+0x17c
        }
        const uint8_t kind2 = m_ui8EnemyClassType;
        if (static_cast<uint32_t>(m_unk73c->m_unk24) == kAttackSoundCount[kind2] - 1 && kind2 != 5) {
            // 0x2a3b78: the kind's last attack runs its ability (+0x784) through a new host.
            m_unk780 = new CKS08EnemyAbilityHost(this);  // OperatorNew(8) + 0x002c6878
            if (m_unk784 != nullptr) {
                m_unk819 = 0;
                m_unk818 = 0;
                static_cast<CKAbilityElement*>(m_unk784)->Start(m_unk780);  // vt+0x58
            }
        }
        m_unk354 = 1;
        if (m_ui8EnemyClassType == 1 || m_ui8EnemyClassType == 8) ComputeAttackApproachPoint();
        m_unk890 = 0;
        CKHkS08Weapon* weapon = static_cast<CKHkS08Weapon*>(m_unk520);
        if (weapon == nullptr) return 0xd;
        CSGLeaf* node = static_cast<CSGLeaf*>(weapon->m_pKGLObject);
        node->m_sgProperties &= 0xfffffffbu;
        if (node->m_pParent != nullptr) {
            node->m_pParent->RemoveChild(node);  // vt+0x78
            RwFrame* frame = node->m_pRwFrame;
            frame->modelling.pos.z = 0.0f;
            frame->modelling.pos.x = 0.0f;
            frame->modelling.pos.y = 0.0f;
            frame->modelling.flags &= 0xfffdffffu;
            RwFrame_MarkDirty(frame);  // 0x00010698
        }
        CKEnemySectorCpnt* sector = static_cast<CKEnemySectorCpnt*>(m_unk18C[GetSectorIndex()]);
        static_cast<CSGHotSpot*>(sector->m_apUnk14[2])->AttachVolume(node);  // 0x002b31e0, 0x000ce2b8
        static_cast<CKHkS08Weapon*>(m_unk520)->m_unkA9 = 0;
        static_cast<CKHkS08Weapon*>(m_unk520)->SetEjected(0);  // 0x002b2bc0
        static_cast<CKHkS08Weapon*>(m_unk520)->SetLanded(0);   // 0x002b2a70
        static_cast<CKHkS08Weapon*>(m_unk520)->m_inHandA8 = 1;
        static_cast<CKHkS08Weapon*>(m_unk520)->m_pOwnerB4 = this;
        return 0xd;
    }
    if (phase == 2) {
        m_unk2a4 = 0.0f;
        return 0xd;
    }
    if (phase != 0) return 0xd;

    m_unk7dc = 1;
    CKS08EnemyAttack* attack = m_unk73c;
    if (attack == nullptr ||
        (attack->m_unk18 != 0 && (attack->m_unk14 < m_unk344 || attack->m_unk10 > m_unk344))) {
        m_bitArray = (m_bitArray & ~0x20000u) | 0x20000u;
        return 1;
    }
    ComputeAttackApproachPoint();  // 0x00280e30
    // The direction to the hero (flat unless the attack is of type 2 / 3).
    const RwV3d& hero = FrameLtm(static_cast<CSGMovable*>(m_unk330->m_pKGLObject)->m_pRwFrame)->pos;
    CVector3 direction{hero.x - m_v3Position.x, hero.y - m_v3Position.y, hero.z - m_v3Position.z};
    const float rise = direction.y;
    const bool flyingAttack = m_unk73c->m_unk64 == 3 || m_unk73c->m_unk64 == 2;
    if (!flyingAttack) direction.y = 0.0f;
    {
        const float length = std::sqrt(ppc::fmadds(direction.z, direction.z,
                                                   ppc::fmadds(direction.x, direction.x, direction.y * direction.y)));
        if (length != 0.0f) {
            const float k = 1.0f / length;  // TOC +0x11bc
            direction.z = direction.z * k;
            direction.x = direction.x * k;
            direction.y = direction.y * k;
        }
    }
    float yaw;
    yaw = m_unk154;  // +0x154 the yaw
    if (flyingAttack) {
        if (m_unk7b4 != 0) {
            // 0x2a3c9c: the model's at turned toward the direction by at most the frame's dt.
            RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
            const float limit = clock->m_afDeltaTime[0];
            CVector3 at{frame->modelling.at.x, frame->modelling.at.y, frame->modelling.at.z};
            if (!(at.x == direction.x && at.y == direction.y && at.z == direction.z)) {
                const float dy = direction.y - at.y;
                const float dx = direction.x - at.x;
                const float dz = direction.z - at.z;
                const float squared = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
                if (limit * limit <= squared) {
                    const float k = limit * rwInvSqrt(squared);  // Math_InvSqrtf 0x000114d8
                    at.z = ppc::fmadds(dz, k, at.z);
                    at.x = ppc::fmadds(dx, k, at.x);
                    at.y = ppc::fmadds(dy, k, at.y);
                } else {
                    at = direction;
                }
            }
            const float length = std::sqrt(ppc::fmadds(at.z, at.z, ppc::fmadds(at.x, at.x, at.y * at.y)));
            if (length != 0.0f) {
                const float k = 1.0f / length;
                at.z = at.z * k;
                at.x = at.x * k;
                at.y = at.y * k;
            }
            const CVector3 up{0.0f, 1.0f, 0.0f};  // TOC +0x11f0: 0x00c50d40
            static_cast<CSGMovable*>(m_pKGLObject)->SetOrientationFromAtUp(&at, &up);  // 0x000d0918
        }
        SteerFlying(&m_v3Position, &yaw, &m_unk158, &m_unk338, &direction, 0, 0, 0);  // 0x002c1180 (mode 0, no path flags)
    } else {
        bool lift = false;  // a flying kind above a low hero ground: the 3D steering at the kind's speed
        if (m_unk7b4 != 0 && (m_ui8EnemyClassType == 1 || m_ui8EnemyClassType == 8) &&
            (m_unk73c->m_unk08 == 0 || m_unk73c->m_unk08 == 3) && m_unk330->IsKindOfClass(CKHkS08Hero::kClassKey) != 0) {
            CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
            collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut,
                                         &static_cast<CSGMovable*>(m_unk330->m_pKGLObject)->m_pRwFrame->modelling.pos.x,
                                         1);  // 0x00196540
            lift = m_GrdContDatasInOut.m_eContactStatus != 0 || m_GrdContDatasInOut.m_fdH < 0.2f;  // TOC +0x11c0
        }
        if (lift) {
            m_unk158.y = rise;
            const float length = std::sqrt(ppc::fmadds(m_unk158.z, m_unk158.z,
                                                       ppc::fmadds(m_unk158.x, m_unk158.x, m_unk158.y * m_unk158.y)));
            float vx = m_unk158.x, vy = m_unk158.y, vz = m_unk158.z;
            if (length != 0.0f) {
                const float k = 1.0f / length;
                vz = k * vz;
                vx = k * vx;
                vy = k * vy;
                m_unk158 = CVector3{vx, vy, vz};
            }
            const float speed = m_unk884->m_unk49c;
            m_unk158 = CVector3{speed * vx, speed * vy, speed * vz};
            SteerFlying(&m_v3Position, &yaw, &m_unk158, &m_unk338, &direction, 0, 0, 0);  // 0x002c1180
        } else {
            m_unk884->m_MoveCpnt.Move(&m_v3Position, &yaw, &m_unk158, &m_unk338, &direction, &m_unk1fc, &m_GrdContDatasIn,
                                      &m_avoidance, &m_PFCpnt, 0, nullptr, 0, 0);  // 0x002c4d38
        }
    }
    m_unk154 = yaw;

    // 0x2a3a68
    if (m_unk784 != nullptr && m_unk780 != nullptr && m_ui8EnemyClassType != 5) {
        // The ability (+0x784) stepped (vt+0x60); once it is over the host is deleted (vt+0x04).
        const uint8_t running = static_cast<CKAbilityElement*>(m_unk784)->Update(clock->m_afDeltaTime[0]);
        if (running == 0) {
            delete m_unk780;
            m_unk780 = nullptr;
        }
    }
    {
        // The walk (move animation +0x7c set) or stand row of the attack, at the current time.
        CKS08EnemyCpnt* kindCfg = m_unk884;
        const uint32_t base = AttackAnimBase(kindCfg, m_unk32c);
        const uint8_t anim = static_cast<uint8_t>(kindCfg->m_MoveCpnt.m_eMvtAnim == 0 ? base + 1 : base + 2);
        const float time = GetAnimLayerTime(0, 0);  // 0x00285388
        RequestAnim(anim, 0, 0, 0, 0.0f, time);   // 0x00285340
    }
    if ((m_bitArray & 0x20000u) != 0) return 1;
    if (IsAnimEndReached(m_unk1fc * m_unk774, 0, 0)) {  // 0x00285558
        const int32_t type = m_unk73c->m_unk64;
        if (type == 3 || type == 2) return 0xe;
        CVector3 to{direction.x, direction.y, direction.z};
        const RwV3d& facingAt = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame->modelling.at;
        CVector3 facing{facingAt.x, facingAt.y, facingAt.z};
        const float angle = AngleBetween(&to, &facing);  // 0x0027eb88
        return m_unk73c->m_unk60 > angle ? 0xe : 1;
    }
    const CKGrpS08Hero* heroes = static_cast<const CKGrpS08Hero*>(g_pEngine->m_gameManager->m_unk04[1]);  // gm +8
    if (((heroes->m_unkf8 >> 3) & 1u) == 0 &&  // 0x002ca258 CKGrpS08Hero_IsInputBlocked_maybe
        static_cast<CKGrpSquad*>(m_pGroupSquad)->m_unk94 == 0) {
        if (m_ui8EnemyClassType == 5) EmitWeaponSparks(GetCurrentAnim(0, 0));  // 0x00285408
        const float time = LayerSlotAnimTime(0, 0);
        PlayAnimMarkSounds(time, time + clock->m_afDeltaTime[0]);  // 0x00286c08
        return 0xd;
    }
    // The heroes' input is blocked (or the squad's spawn camera runs): the reactions back to row 0, state 1.
    SwitchReactState(0, nullptr);
    return 1;
}

// The kinds' strike effects (State0E, enter and tick): kind 5 particle 0xa at the weapon's hot spot for the animations
// 0x41 / 0x49 / 0x4d, 0xb and 0xc for 0x51; kind 6 particle 0x15 at hot spots 2 and 0xf for 0x4b.
void CKHkS08Enemy::EmitStrikeEffects(uint8_t anim) {
    if (m_ui8EnemyClassType == 5) {
        CVector3 at;
        static_cast<CSGHotSpot*>(static_cast<CKHkS08Weapon*>(m_unk520)->m_apUnkAC[1])->GetWorldPosition(&at);  // 0x000ce790
        if (anim == 0x41 || anim == 0x49 || anim == 0x4d) {
            CVector3 a = at;
            EmitParticleAt(10, &a, nullptr, 0);  // 0x00278028
        } else if (anim == 0x51) {
            CVector3 a = at;
            EmitParticleAt(0xb, &a, nullptr, 0);
            CVector3 b = at;
            EmitParticleAt(0xc, &b, nullptr, 0);
        }
    }
    if (m_ui8EnemyClassType == 6) {
        CVector3 left;
        GetHotSpot(2)->GetWorldPosition(&left);  // 0x002892e8
        CVector3 right;
        GetHotSpot(0xf)->GetWorldPosition(&right);
        if (anim == 0x4b) {
            EmitParticleAt(0x15, &left, nullptr, 0);
            EmitParticleAt(0x15, &right, nullptr, 0);
        }
    }
}

// 0x0028b960 CKHkS08Enemy_SetAttackTrailActive_maybe: attack trail `trail` (the kind 1 also runs trails 3 and 4).
// Off: its ribbon stopped (vt+0x11c; the kind 1 stops `trail` three times). On: the ribbon's two ends from the weapon's
// first two hot spots (trail 0), the enemy's hot spots 0 and 1 (trails 1 and 2; the kind 1's extra trails 6 / 7 and
// 8 / 9), or hot spot 6's matrix (trail 5: its position moved along its up by the group's +0x27c, the ends +-0.5 x the
// group's +0x284 along its right); started (vt+0x118; trail 5 resets the fade +0x8f0 to the group's +0x280) or, with
// `update`, moved (vt+0x120; trail 5's fade loses +0x1fc). Trail 1 takes the attacking hero's element colour (+0x7c8,
// picked when it starts) with the ribbon's colour flag.
void CKHkS08Enemy::SetAttackTrailActive(uint32_t trail, uint8_t active, uint8_t update) {
    if (active == 0) {
        StopTrailRibbon(static_cast<uint8_t>(trail));  // vt+0x11c
        if (m_ui8EnemyClassType == 1) {
            StopTrailRibbon(static_cast<uint8_t>(trail));
            StopTrailRibbon(static_cast<uint8_t>(trail));
        }
        return;
    }
    // DOTD: the original leaves these uninitialised where no branch fills them (trails 3, 4, 6.., the kind 1's extra
    // ends outside trails 1 / 2).
    CVector3 a{}, b{}, a3{}, b3{}, a4{}, b4{};
    const uint8_t t = static_cast<uint8_t>(trail);
    if (t <= 2) {
        if (t < 1) {
            IKSerializable** spots = m_unk520->m_apUnkAC;
            static_cast<CSGHotSpot*>(spots[0])->GetWorldPosition(&a);  // 0x000ce790
            static_cast<CSGHotSpot*>(spots[1])->GetWorldPosition(&b);
        } else {
            GetHotSpot(0)->GetWorldPosition(&a);  // 0x002892e8
            GetHotSpot(1)->GetWorldPosition(&b);
            if (m_ui8EnemyClassType == 1) {
                GetHotSpot(6)->GetWorldPosition(&a3);
                GetHotSpot(7)->GetWorldPosition(&b3);
                GetHotSpot(8)->GetWorldPosition(&a4);
                GetHotSpot(9)->GetWorldPosition(&b4);
            }
        }
    } else if (t == 5) {
        alignas(16) CMatrix34 m;
        GetHotSpot(6)->GetWorldMatrix(&m);  // 0x000ce970
        a = m.m_pos;
        const float lift = static_cast<CKGrpS08Enemy*>(enemy::EnemyGroup())->m_unk268[5];  // +0x27c
        a.z = ppc::fmadds(lift, m.m_up.z, a.z);
        a.x = ppc::fmadds(lift, m.m_up.x, a.x);
        a.y = ppc::fmadds(lift, m.m_up.y, a.y);
        const float half = static_cast<CKGrpS08Enemy*>(enemy::EnemyGroup())->m_unk268[7] * 0.5f;  // +0x284, TOC +0xe90
        b.z = ppc::fmadds(half, m.m_right.z, a.z);
        b.x = ppc::fmadds(half, m.m_right.x, a.x);
        b.y = ppc::fmadds(half, m.m_right.y, a.y);
        const float back = static_cast<CKGrpS08Enemy*>(enemy::EnemyGroup())->m_unk268[7] * -0.5f;  // TOC +0xe94
        const float az = ppc::fmadds(back, m.m_right.z, a.z);
        const float ax = ppc::fmadds(back, m.m_right.x, a.x);
        const float ay = ppc::fmadds(back, m.m_right.y, a.y);
        a = CVector3{ax, ay, az};
    }
    if (update == 0) {
        if (t == 5) m_unk8f0 = static_cast<CKGrpS08Enemy*>(enemy::EnemyGroup())->m_unk268[6];  // +0x280
        StartTrailRibbon(t, &a, &b);  // vt+0x118
        if (m_ui8EnemyClassType == 1) {
            StartTrailRibbon(3, &a3, &b3);
            StartTrailRibbon(4, &a4, &b4);
        }
        if (t != 1) return;
        if (m_unk60[1] == 0xff) return;
        IKSerializable* attacker = static_cast<IKSerializable*>(m_unk694);
        if (attacker == nullptr || attacker->IsKindOfClass(0x25c2) == 0) return;  // vt+0x08 CKHkS08Hero
        m_unk7c8 = static_cast<CKHkS08Hero*>(attacker)->GetElementColor(0);  // 0x0032ac08
    } else {
        SetTrailRibbonEndpoints(t, &a, &b);  // vt+0x120
        if (m_ui8EnemyClassType == 1) {
            SetTrailRibbonEndpoints(3, &a3, &b3);
            SetTrailRibbonEndpoints(4, &a4, &b4);
        }
        if (t == 5) {
            m_unk8f0 = m_unk8f0 - m_unk1fc;
            return;
        }
        if (t != 1) return;
        if (m_unk60[1] == 0xff) return;
    }
    STrailNodeData* data = static_cast<CTrailNodeFx*>(m_apTrailNodeFx[1])->m_apTrailData[m_unk60[1]];
    std::memcpy(data->m_cColor, &m_unk7c8, sizeof m_unk7c8);
    data->m_ba8Properties = static_cast<uint8_t>(data->m_ba8Properties | 2u);
}

// 0x002a2530 CKHkS08Enemy_State0E_AttackStrike_maybe: the attack's strike. Enter: the attack's animation row base, the
// attack's cooldown into +0x2b0[index] (+0x1c) and the kind's +0x118 into +0x2ac, the kinds' effects, the strike sound
// (the 0xa70248 table's +0x48 base + the attack index; kind 7's attack 3: the looped 0x32). Leave: kind 7's loop
// stopped, the trails off. Tick: turned toward the hero in place (2D steering of a copy at no speed; the flying attacks
// move by the 3D steering at the kind's +0x4fc), at the animation's end the recovery (0xf); heroes' input blocked (or
// the squad's spawn camera): reactions to row 0, state 1; else the effects and the marks' sounds.
uint8_t CKHkS08Enemy::MainState0E_AttackStrike(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        CKS08EnemyCpnt* cfg = m_unk884;
        const uint8_t anim = static_cast<uint8_t>(AttackAnimBase(cfg, m_unk32c));  // 0x002b3ec0
        RequestAnim(anim, 0, 0, 0, 0.02f, 0.0f);  // TOC +0x11e0 / +0x11ac
        m_unk2b0[m_unk32c] = m_unk73c->m_unk1c;
        m_unk2ac = cfg->m_unk118;
        if (m_ui8EnemyClassType == 5) SetAttackTrailActive(0, 1, 0);  // 0x0028b960
        EmitStrikeEffects(anim);
        const uint8_t kind = m_ui8EnemyClassType;
        if (kind == 7 && m_unk73c->m_unk24 == 3) {
            PlaySound(0x32, 1, m_pKGLObject);  // 0x002795c0
        } else {
            static const uint32_t kStrikeSoundFirst[9] = {46, 50, 49, 50, 48, 49, 47, 47, 53};  // 0x00a70248 + 0x48
            PlaySound(static_cast<uint8_t>(kStrikeSoundFirst[kind] + static_cast<uint32_t>(m_unk73c->m_unk24)), 0,
                      m_pKGLObject);
        }
        if (m_ui8EnemyClassType == 8 && m_unk73c->m_unk24 == 4) SetAttackTrailActive(5, 1, 0);
        return 0xe;
    }
    if (phase == 2) {
        uint8_t kind = m_ui8EnemyClassType;
        if (kind == 8) {
            if (m_unk73c->m_unk24 != 4) return 0xe;
            SetAttackTrailActive(5, 0, 0);
            kind = m_ui8EnemyClassType;
        }
        if (kind == 7) {
            if (m_unk73c->m_unk24 != 3) return 0xe;
            StopSound(0x32);  // 0x002794f0
            kind = m_ui8EnemyClassType;
        }
        if (kind == 5) SetAttackTrailActive(0, 0, 0);
        return 0xe;
    }
    if (phase != 0) return 0xe;

    // The direction to the hero (flat unless the attack is of type 2 / 3), as State0D.
    const RwV3d& heroAt = FrameLtm(static_cast<CSGMovable*>(m_unk330->m_pKGLObject)->m_pRwFrame)->pos;
    CVector3 hero{heroAt.x, heroAt.y, heroAt.z};
    CVector3 direction{hero.x - m_v3Position.x, hero.y - m_v3Position.y, hero.z - m_v3Position.z};
    const bool flyingAttack = m_unk73c->m_unk64 == 3 || m_unk73c->m_unk64 == 2;
    if (!flyingAttack) direction.y = 0.0f;
    {
        const float length = std::sqrt(ppc::fmadds(direction.z, direction.z,
                                                   ppc::fmadds(direction.x, direction.x, direction.y * direction.y)));
        if (length != 0.0f) {
            const float k = 1.0f / length;  // TOC +0x11bc
            direction.z = direction.z * k;
            direction.x = direction.x * k;
            direction.y = direction.y * k;
        }
    }
    float yaw;
    yaw = m_unk154;  // +0x154 the yaw
    if (flyingAttack) {
        if (m_unk7b4 != 0) {
            // 0x2a2ab0: the model's at turned toward the direction by at most the frame's dt (as State0D).
            RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
            const float limit = clock->m_afDeltaTime[0];
            CVector3 at{frame->modelling.at.x, frame->modelling.at.y, frame->modelling.at.z};
            if (!(at.x == direction.x && at.y == direction.y && at.z == direction.z)) {
                const float dy = direction.y - at.y;
                const float dx = direction.x - at.x;
                const float dz = direction.z - at.z;
                const float squared = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
                if (limit * limit <= squared) {
                    const float k = limit * rwInvSqrt(squared);  // Math_InvSqrtf 0x000114d8
                    at.z = ppc::fmadds(dz, k, at.z);
                    at.x = ppc::fmadds(dx, k, at.x);
                    at.y = ppc::fmadds(dy, k, at.y);
                } else {
                    at = direction;
                }
            }
            const float length = std::sqrt(ppc::fmadds(at.z, at.z, ppc::fmadds(at.x, at.x, at.y * at.y)));
            if (length != 0.0f) {
                const float k = 1.0f / length;
                at.z = at.z * k;
                at.x = at.x * k;
                at.y = at.y * k;
            }
            const CVector3 up{0.0f, 1.0f, 0.0f};  // TOC +0x11f0: 0x00c50d40
            static_cast<CSGMovable*>(m_pKGLObject)->SetOrientationFromAtUp(&at, &up);  // 0x000d0918
        }
        // 0x2a2bd0: the velocity normalised to the kind's +0x4fc, the 3D steering of copies; the height kept.
        {
            const float length = std::sqrt(ppc::fmadds(m_unk158.z, m_unk158.z,
                                                       ppc::fmadds(m_unk158.x, m_unk158.x, m_unk158.y * m_unk158.y)));
            float vx = m_unk158.x, vy = m_unk158.y, vz = m_unk158.z;
            if (length != 0.0f) {
                const float k = 1.0f / length;
                vz = k * vz;
                vx = k * vx;
                vy = k * vy;
                m_unk158 = CVector3{vx, vy, vz};
            }
            const float speed = m_unk884->m_unk4fc;
            m_unk158 = CVector3{speed * vx, speed * vy, speed * vz};
        }
        CVector3 position = m_v3Position;
        CVector3 velocity = m_unk158;
        SteerFlying(&position, &yaw, &velocity, &hero, &direction, 0, 0, 0);  // 0x002c1180 (mode 0, no path flags)
        m_v3Position.y = position.y;
    } else {
        // 0x2a26b0: turned in place.
        CVector3 position = m_v3Position;
        CVector3 velocity{0.0f, 0.0f, 0.0f};
        m_unk884->m_MoveCpnt.Move(&position, &yaw, &velocity, &hero, &direction, &m_unk1fc, &m_GrdContDatasIn,
                                  &m_avoidance, &m_PFCpnt, 0, nullptr, 0, 0);  // 0x002c4d38
    }
    m_unk154 = yaw;
    // 0x2a2744
    if (m_unk784 != nullptr && m_unk780 != nullptr) {
        // The ability (+0x784) stepped (vt+0x60); once it is over the host is deleted (vt+0x04).
        const uint8_t running = static_cast<CKAbilityElement*>(m_unk784)->Update(clock->m_afDeltaTime[0]);
        if (running == 0) {
            delete m_unk780;
            m_unk780 = nullptr;
        }
    }
    if (IsAnimEndReached(m_unk1fc * m_unk774, 0, 0)) return 0xf;  // 0x00285558
    const CKGrpS08Hero* heroes = static_cast<const CKGrpS08Hero*>(g_pEngine->m_gameManager->m_unk04[1]);  // gm +8
    if (((heroes->m_unkf8 >> 3) & 1u) != 0 ||  // 0x002ca258 CKGrpS08Hero_IsInputBlocked_maybe
        static_cast<CKGrpSquad*>(m_pGroupSquad)->m_unk94 != 0) {
        SwitchReactState(0, nullptr);
        return 1;
    }
    if (m_ui8EnemyClassType == 5) SetAttackTrailActive(0, 1, 1);
    if (m_ui8EnemyClassType == 5 || m_ui8EnemyClassType == 6) EmitStrikeEffects(GetCurrentAnim(0, 0));  // 0x00285408
    const float time = LayerSlotAnimTime(0, 0);
    PlayAnimMarkSounds(time, time + clock->m_afDeltaTime[0]);  // 0x00286c08
    if (m_ui8EnemyClassType != 8 || m_unk73c->m_unk24 != 4) return 0xe;
    if (m_unk8f0 <= 0.0f) {
        SetAttackTrailActive(5, 0, 0);
    } else {
        SetAttackTrailActive(5, 1, 1);
    }
    return 0xe;
}

// 0x002aab10 CKHkS08Enemy_State0F_AttackRecover_maybe: the attack's recovery. Enter: the attack's recovery animation
// (the attack row + 3). Leave: +0x354 cleared, the ability host released (STUB, see Update). Update: a flying attack
// (type 2 / 3) with +0x7b4 turns the model's at back to level by at most twice the frame's dt; the animation's end
// goes to state 1, as do blocked input or a squad that holds its members (the reaction reset to 0); else the
// animation marks' sounds.
uint8_t CKHkS08Enemy::MainState0F_AttackRecover(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        const uint32_t base = AttackAnimBase(m_unk884, m_unk32c);  // 0x002b3ec0
        RequestAnim(static_cast<uint8_t>(base + 3), 0, 0, 0, 0.02f, 0.0f);  // TOC +0x11e0 / +0x11ac
        return 0xf;
    }
    if (phase == 2) {
        m_unk354 = 0;
        if (m_unk780 == nullptr) return 0xf;
        // 0x2aad6c: the ability stopped, the host deleted.
        if (m_unk784 != nullptr) {
            m_unk819 = 0;
            m_unk818 = 0;
            static_cast<CKAbilityElement*>(m_unk784)->Stop(0);  // vt+0x5c
        }
        delete m_unk780;  // vt+0x04
        m_unk780 = nullptr;
        return 0xf;
    }
    if (phase != 0) return 0xf;
    const int32_t type = m_unk73c->m_unk64;
    if ((type == 3 || type == 2) && m_unk7b4 != 0) {
        // 0x2aadfc: the model's at toward its level direction (y 0), by at most 2 * dt.
        RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
        CVector3 at{frame->modelling.at.x, frame->modelling.at.y, frame->modelling.at.z};
        float levelX = at.x, levelZ = at.z, levelY = 0.0f;
        const float flat = std::sqrt(ppc::fmadds(levelZ, levelZ, ppc::fmadds(levelX, levelX, 0.0f)));  // Math_Sqrtf
        if (flat != 0.0f) {
            const float k = 1.0f / flat;  // TOC +0x11bc
            levelZ = levelZ * k;
            levelX = levelX * k;
            levelY = k * 0.0f;
        }
        const float dt = clock->m_afDeltaTime[0];
        if (!(at.x == levelX && at.y == levelY && at.z == levelZ)) {
            const float dy = levelY - at.y;
            const float dx = levelX - at.x;
            const float limit = dt + dt;
            const float dz = levelZ - at.z;
            const float squared = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
            if (limit * limit <= squared) {
                const float k = limit * rwInvSqrt(squared);  // Math_InvSqrtf 0x000114d8
                at.z = ppc::fmadds(dz, k, at.z);
                at.x = ppc::fmadds(dx, k, at.x);
                at.y = ppc::fmadds(dy, k, at.y);
            } else {
                at = CVector3{levelX, levelY, levelZ};
            }
        }
        const float length = std::sqrt(ppc::fmadds(at.z, at.z, ppc::fmadds(at.x, at.x, at.y * at.y)));
        if (length != 0.0f) {
            const float k = 1.0f / length;
            at.z = at.z * k;
            at.x = at.x * k;
            at.y = at.y * k;
        }
        const CVector3 up{0.0f, 1.0f, 0.0f};  // TOC +0x11f0: 0x00c50d40
        static_cast<CSGMovable*>(m_pKGLObject)->SetOrientationFromAtUp(&at, &up);  // 0x000d0918
    }
    // 0x2aabd8
    if (m_unk784 != nullptr && m_unk780 != nullptr) {
        // The ability (+0x784) stepped (vt+0x60); once it is over the host is deleted (vt+0x04).
        const uint8_t running = static_cast<CKAbilityElement*>(m_unk784)->Update(clock->m_afDeltaTime[0]);
        if (running == 0) {
            delete m_unk780;
            m_unk780 = nullptr;
        }
    }
    if (IsAnimEndReached(m_unk1fc * m_unk774, 0, 0)) return 1;  // 0x00285558
    const CKGrpS08Hero* heroes = static_cast<const CKGrpS08Hero*>(g_pEngine->m_gameManager->m_unk04[1]);  // gm +8
    if (((heroes->m_unkf8 >> 3) & 1u) != 0 ||  // 0x002ca258 CKGrpS08Hero_IsInputBlocked_maybe
        static_cast<CKGrpSquad*>(m_pGroupSquad)->m_unk94 != 0) {
        SwitchReactState(0, nullptr);
        return 1;
    }
    const float time = LayerSlotAnimTime(0, 0);
    PlayAnimMarkSounds(time, time + clock->m_afDeltaTime[0]);  // 0x00286c08
    return 0xf;
}

// 0x0029ddb8 CKHkS08Enemy_vf17C: returns 18.
uint8_t CKHkS08Enemy::MainState12(IKTime* /*clock*/, int32_t /*phase*/, uint8_t /*other*/) {
    return 18;
}

// 0x0029ddc0 CKHkS08Enemy_vf180: returns 19.
uint8_t CKHkS08Enemy::MainState13(IKTime* /*clock*/, int32_t /*phase*/, uint8_t /*other*/) {
    return 19;
}

// 0x0029ddc8 CKHkS08Enemy_vf184: returns 20.
uint8_t CKHkS08Enemy::MainState14(IKTime* /*clock*/, int32_t /*phase*/, uint8_t /*other*/) {
    return 20;
}

// 0x0029f3c0 CKHkS08Enemy_State21_Dying (state 0x15). Enter: every active enemy's +0x52c counts the death; the hero
// group's kill bonus (CKGrpS08Hero_OnEnemyKilled_maybe 0x2d4cb8); the game structure's kill counter: the killing
// dragon's (a hero attacker, +0x694), else 0 while burning (+0x6b8), frozen (+0x6c8) or under status 3 (+0x6d4), else 1
// under status 4, 6, 5 or 7 (+0x6c0, +0x6cc, +0x6c4, +0x6d0); the death FX by the first status (burn 9, status 4 6 with
// the poison spread, frozen 8, status 3 0x12, else FX 3 at hot spot 1); kind 1 stops its sounds 0x2a / 0x2b; flags
// +0x0c (bit 4 set, bit 3 cleared), the timer +0x7e8 at 0, the node hidden, volume groups 2 and 1 off; the carried
// object (+0x738) and the carrier (+0x734) let go; the health (+0x258) at 0 and, with +0x898, the boss gauge. Update:
// after the kind's +0x4e4 the bonus weights reset (1, 0 for kind 2 entries), the bonus and gem drops at hot spot 1, flags
// +0x0c bits 4 and 3 set, state 0xff.
uint8_t CKHkS08Enemy::MainState15_Dying(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    if (phase == 0) {
        const CKS08EnemyCpnt* cfg = m_unk884;
        if (cfg->m_unk4e4 > m_unk7e8) {
            m_unk7e8 = m_unk7e8 + clock->m_afDeltaTime[0];
            return 0x15;
        }
        CKBonusData* bonus = static_cast<CKBonusData*>(cfg->m_pUnk4b4);
        for (uint32_t i = 0; i < bonus->m_count; ++i) {
            CKBonusData::Entry& entry = bonus->m_pEntries[i];
            const float weight = entry.m_unk00 == 2 ? 0.0f : 1.0f;  // TOC +0x11bc
            std::memcpy(&entry.m_unk1c, &weight, sizeof weight);
        }
        CVector3 at;
        GetHotSpot(1)->GetWorldPosition(&at);  // 0x002892e8, 0x000ce790
        // The bonuses (TOC +0x11f0: the shared y axis) and the kind's gems (+0x310).
        const CVector3 up = enemy::kAxisY;
        SpawnBonusDrop(&at, &up, 0);  // 0x0027d1b8
        static_cast<CKS08GameManager*>(g_pEngine->m_gameManager)
            ->SpawnGemReward(static_cast<uint32_t>(ppc::fctidz(cfg->m_unk310)), &at, &enemy::kAxisY);  // 0x004f8618
        m_bitArray = (m_bitArray & ~0x10u) | 0x10u;
        m_bitArray = (m_bitArray & ~0x8u) | 0x8u;
        return 0xff;
    }
    if (phase != 1) return 0x15;
    CKGrpS08Enemy* group = static_cast<CKGrpS08Enemy*>(enemy::EnemyGroup());  // 0x00276f58
    const uint32_t active = group->m_ui32NbActiveEnemies;
    for (uint32_t i = 0; i < active; ++i) {
        CKHkS08Enemy* other = static_cast<CKHkS08Enemy*>(group->m_apActiveEnemies[i]);
        other->m_unk52c = other->m_unk52c + 1;
    }
    if (enemy::HeroGroup() != nullptr) {  // 0x00276f70
        static_cast<CKGrpS08Hero*>(enemy::HeroGroup())->OnEnemyKilled(this);  // 0x002d4cb8
    }
    CKS08GameStructure* stats =
        static_cast<CKS08GameStructure*>(g_pEngine->m_gameManager->m_gameStructure);  // TOC +0x11cc -> +0x8c -> +0x6c
    IKSerializable* killer = static_cast<IKSerializable*>(m_unk694);
    if (killer != nullptr && killer->IsKindOfClass(0x25c2) != 0) {
        stats->AddEnemyKill(static_cast<CKHkS08Hero*>(killer)->GetDragonIndex());  // 0x00361960, 0x0050f218
    } else if (m_unk6b8 > 0.0f || m_unk6c8 > 0.0f || m_unk6d4 > 0.0f) {
        stats->AddEnemyKill(0);
    } else if (m_unk6c0 > 0.0f || m_unk6cc > 0.0f || m_unk6c4 > 0.0f || m_unk6d0 > 0.0f) {
        stats->AddEnemyKill(1);
    }
    if (m_unk6b8 > 0.0f) {
        PlayFxOnAllHotspots(9);  // 0x0028da80
    } else if (m_unk6c0 > 0.0f) {
        PlayFxOnAllHotspots(6);
        SpreadPoisonToNearby(m_unk884->m_unk2a8, m_unk884->m_unk2a4);  // 0x002afff0
    } else if (m_unk6c8 > 0.0f) {
        PlayFxOnAllHotspots(8);
    } else if (m_unk6d4 > 0.0f) {
        PlayFxOnAllHotspots(0x12);
    } else {
        CVector3 at;
        GetHotSpot(1)->GetWorldPosition(&at);
        SpawnHitFxAt(3, &at);  // 0x0028c590
    }
    if (m_ui8EnemyClassType == 1) {
        StopSound(0x2a);  // 0x002794f0
        StopSound(0x2b);
    }
    m_bitArray = ((m_bitArray & ~0x10u) | 0x10u) & ~0x8u;
    m_unk7e8 = 0.0f;
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pKGLObject);
    node->m_sgProperties = (node->m_sgProperties & ~4u) | 4u;
    DisableVolumeGroup(2);  // vt+0xfc
    DisableVolumeGroup(1);
    bool carrying = false;
    if (m_unk738 != nullptr) {
        static_cast<CKHkS08TransportableBase*>(m_unk738)->Vf138(0);  // vt+0x138
        carrying = static_cast<CKS08CarrierEnemy*>(m_unk734)->IsCarrying() != 0;  // 0x004c7c48
    }
    if (carrying) DropCarriedTransportableAtHand();  // 0x0029f928 (Enemy_8.cpp; then the carrier's drop too)
    static_cast<CKS08CarrierEnemy*>(m_unk734)->DropCarriedObject();  // vt+0x6c 0x004c82d0
    m_unk258 = 0.0f;
    if (m_unk898 != 0) {
        // A boss enemy (+0x898): the boss gauge (the kind's +0xcc as both maxima, the health 0).
        CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
        manager->SetEnemyGaugeMaxHealth(m_unk884->m_unkcc);   // 0x004fea60
        manager->SetEnemyGaugeMaxHealth2(m_unk884->m_unkcc);  // 0x004fe9c0
        manager->SetBossGaugeHealth(m_unk258);                // 0x004feb00
        manager->RefreshBossGauge();                          // 0x00501ea0
    }
    return 0x15;
}

// 0x0029e988 CKHkS08Enemy_vf18C (main state 0x16, the fight zone's end: CKGrpFightZone sends the active enemies here,
// ForceState16 0x2820e8). Enter: animation 10 (blend 0.02, not restarted), the parts' category 2 cleared, +0x7c4 set,
// +0x888 cleared, the speed scale 1, the kind's sounds 0x2a / 0x2b stopped. Tick: a kind 1 (flying) more than 0.05
// above the ground goes to 0x25; animation 10 (restarted when another plays), its marks' sounds, and at its end the
// enemy is done (+0x1fc / +0x200 cleared, the parts' category 2 set, life bit 3: 0xff).
uint8_t CKHkS08Enemy::MainState16(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        RequestAnim(10, 0, 0, 0, 2.0e-2f, 0.0f);  // 0x00285340, TOC +0x11e0 / +0x11ac
        ClearPartsFlagForCategory(2);              // 0x0027d018
        m_unk7c4 = 1;
        m_unk888 = 0;
        m_unk774 = 1.0f;  // TOC +0x11bc
        if (m_ui8EnemyClassType == 1) {
            StopSound(0x2a);  // 0x002794f0
            StopSound(0x2b);
        } else if (m_ui8EnemyClassType == 7) {
            StopSound(0x2a);
        }
        return 0x16;
    }
    if (phase != 0) return 0x16;
    m_unk774 = 1.0f;
    if (m_ui8EnemyClassType == 1) {
        CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
        collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &m_v3Position.x, 1);  // 0x00196540
        if (m_GrdContDatasInOut.m_fdH > 0.05f) return 0x25;  // TOC +0x11d0 (ble: a NaN stays)
    }
    if (GetCurrentAnim(0, 0) != 10) RequestAnim(10, 1, 0, 0, 2.0e-2f, 0.0f);  // 0x00285408, 0x00285340
    const float time = LayerSlotAnimTime(0, 0);
    PlayAnimMarkSounds(time, time + clock->m_afDeltaTime[0]);  // 0x00286c08
    if (!IsAnimEndReached(m_unk1fc * m_unk774, 0, 0)) return 0x16;  // 0x00285558
    m_unk1fc = 0.0f;
    m_unk200 = 0.0f;
    SetPartsFlagForCategory(2);  // 0x0027cf30
    m_bitArray = (m_bitArray & ~0x8u) | 0x8u;
    return 0xff;
}

// 0x002a14a0 CKHkS08Enemy_State17 (the burrow): enter plays animation 10 (blend 0.02), clears the parts' category 2,
// keeps the start (+0x850 from the position), a kind 8 burrows without the mesh pop (+0x86d), the mesh pop on unless
// +0x7dd / +0x86d, the kind's dig sounds stopped. The tick (dead: state 0x15) waits for the animation's end (or the
// travel already begun, +0x7e4 > 0), hides the body and, without the mesh pop, only waits +0x1cc then resurfaces;
// otherwise the dust trail (the kind's +0x548 particles, sound 0x1e) starts once, the hidden point +0x850 travels
// toward +0x85c at the kind's +0x540 per second on the ground, the mesh pop shown on walkable ground (its position
// following) and off elsewhere, and the point arriving (no nearer than before, or within 0.2^0.5) resurfaces (0x18).
// Leave: the body shown, +0x254 from the kind's +0x1f0, a pending weapon (+0x7f9) attached, the mesh pop and the
// dust trail released, the sound 0x1e stopped.
uint8_t CKHkS08Enemy::MainState17(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        RequestAnim(10, 0, 0, 0, 2.0e-2f, 0.0f);  // TOC +0x11e0 / +0x11ac
        ClearPartsFlagForCategory(2);              // 0x0027d018
        m_unk7e4 = 0.0f;
        m_unk254 = 0.0f;
        m_unk7c4 = 1;
        m_unk850 = m_v3Position.x;
        m_unk854 = m_v3Position.y;
        m_unk858 = m_v3Position.z;
        if (m_ui8EnemyClassType == 8) m_unk86d = 1;
        if (m_unk7dd == 0 && m_unk86d == 0) SetMeshPopFxActive(1, 0);  // 0x0028c838
        if (m_ui8EnemyClassType == 1) {
            StopSound(0x2a);  // 0x002794f0
            StopSound(0x2b);
        }
        if (m_ui8EnemyClassType == 7) StopSound(0x2a);
        m_unk888 = 0;
        return 0x17;
    }
    if (phase == 2) {
        CSGLeaf* body = static_cast<CSGLeaf*>(m_pKGLObject);
        body->m_sgProperties = body->m_sgProperties & 0xfffffffbu;
        m_unk254 = Cfg()->m_unk1f0;
        if (m_unk7f9 != 0) {
            AttachRandomWeapon();  // 0x00292b40
            if (m_unk520 == nullptr) m_bitArray = (m_bitArray & ~0x8u) | 0x8u;
            m_unk7f9 = 0;
        }
        SetMeshPopFxActive(0, 0);
        m_unk774 = 1.0f;  // TOC +0x11bc
        m_unk1fc = 1.0f;
        if (m_unk880 != nullptr) {
            StopOwnedParticleEffect(m_unk880, this);  // 0x001cdde8
            m_unk880->ReleaseReservation(this);       // vt+0x54
            m_unk880 = nullptr;
        }
        m_unk7f9 = 0;
        m_unk7f8 = 0;
        StopSound(0x1e);
        return 0x17;
    }
    if (phase != 0) return 0x17;
    if (m_unk258 <= 0.0f) return 0x15;
    const float time = LayerSlotAnimTime(0, 0);
    const float dt = clock->m_afDeltaTime[0];
    PlayAnimMarkSounds(time, time + dt);  // 0x00286c08
    if (!IsAnimEndReached(m_unk1fc * m_unk774, 0, 0) && m_unk7e4 <= 0.0f) return 0x17;  // 0x00285558
    CSGLeaf* body = static_cast<CSGLeaf*>(m_pKGLObject);
    body->m_sgProperties = (body->m_sgProperties & 0xfffffffbu) | 4u;
    if (m_unk7dd != 0 || m_unk86d != 0) {
        m_unk7e4 = m_unk7e4 + dt;
        if (Cfg()->m_unk1cc <= m_unk7e4) return 0x18;
        m_unk1fc = 0.0f;
        return 0x17;
    }
    if (m_unk880 == nullptr) {
        PlaySound(0x1e, 1, m_pKGLObject);  // 0x002795c0
        CKParticlesEffectFxData* trail = static_cast<CKParticlesEffectFxData*>(Cfg()->m_pUnk548);
        trail->m_pAttachOwner = nullptr;
        trail->m_pAttachHotSpot = nullptr;
        m_unk880 = static_cast<CKParticlesEffectNodeFx*>(
            static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(reinterpret_cast<IKFxData*>(trail), this));  // inlined
    }
    float dx = m_unk85c - m_unk850;
    float dy = m_unk860 - m_unk854;
    float dz = m_unk864 - m_unk858;
    const float length = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));  // 0x00010690 Math_Sqrtf
    if (length != 0.0f) {
        const float inv = 1.0f / length;
        dz = dz * inv;
        dx = dx * inv;
        dy = dy * inv;
    }
    const float oldX = m_unk850;
    const float oldZ = m_unk858;
    const float step = Cfg()->m_unk540 * dt;
    m_unk854 = ppc::fmadds(dy, step, m_unk854);
    m_unk858 = ppc::fmadds(dz, step, m_unk858);
    m_unk850 = ppc::fmadds(dx, step, m_unk850);
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &m_unk850, 1);  // 0x00196540
    const int32_t status = m_GrdContDatasInOut.m_eContactStatus;
    if (status == 0) {
        m_unk854 = m_unk854 - m_GrdContDatasInOut.m_fdH;
    } else if (status > 0 && status <= 2) {
        m_unk854 = m_unk854 + m_GrdContDatasInOut.m_fdH;
    }
    CPFPoint point;
    point.m_unk0c = 0xffff;
    point.m_position = {m_unk850, m_unk854, m_unk858};
    point.m_unk0c = m_PFCpnt.m_Destination.m_unk0c;
    const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(m_GrdContDatasInOut.m_pGround);
    CKSrvPathFinding* pathFinding = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);
    if (ground == nullptr || (ground->m_ui16PropertiesFlags & 0x200u) != 0 || !PointInNodeBox(pathFinding, &point) ||
        (pathFinding->IsPointWalkable(&point, &m_PFCpnt.m_CharacterType) & 0xffu) == 0) {  // 0x001e42d0
        SetMeshPopFxActive(0, 0);
    } else {
        SetMeshPopFxActive(1, 0);
        SetMeshPopFxActive(1, 1);
    }
    const CVector3 at = {m_unk850, m_unk854, m_unk858};
    if (m_unk880 != nullptr) SetOwnedParticleEffectPosition(m_unk880, &at, this);  // 0x001cdce0
    const float oldDz = oldZ - m_unk864;
    const float newDz = m_unk858 - m_unk864;
    const float oldDx = oldX - m_unk85c;
    const float newDx = m_unk850 - m_unk85c;
    const float before = ppc::fmadds(oldDx, oldDx, oldDz * oldDz);
    const float after = ppc::fmadds(newDx, newDx, newDz * newDz);
    if (before <= after || after <= 0.2f) return 0x18;  // TOC +0x11c0
    m_unk7e4 = 0.1f;                                     // TOC +0x11a8
    m_unk1fc = 0.0f;
    return 0x17;
}

// 0x002a0260 CKHkS08Enemy_State18 (resurfacing): enter clears the update flag 0x400, puts the enemy at the burrow's
// end (+0x85c; the null vector: the spawn point +0x1c4), turns it toward its target's node (the stored LTM), on the
// ground, plays animation 9 (blend 0.02) and refreshes its path-finding sector. The tick (dead: 0x15) waits for the
// animation's end (state 1). Leave: the attack timers cleared, +0x254 from the kind's +0x1f0, the parts' category 2
// set, the kind 1 / 7 growl.
uint8_t CKHkS08Enemy::MainState18(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        m_bitArray = m_bitArray & ~0x400u;
        m_v3Position.x = m_unk85c;
        m_v3Position.y = m_unk860;
        m_v3Position.z = m_unk864;
        m_unk86d = 0;
        m_unk7dd = 0;
        CKSrvPathFinding* pathFinding = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);
        const CVector3 kNull = {0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC +0x1234)
        if (m_v3Position.x == kNull.x && m_v3Position.y == kNull.y && m_v3Position.z == kNull.z) {
            m_v3Position = {m_unk1c4, m_unk1c8, m_unk1cc};
            CPFPoint spawn;
            spawn.m_unk0c = 0xffff;
            spawn.m_position = m_v3Position;
            spawn.m_unk0c = m_PFCpnt.m_Destination.m_unk0c;
            pathFinding->FindSectorForPoint(&spawn);  // 0x001e5ca0
            if (!PointInNodeBox(pathFinding, &spawn) ||
                (pathFinding->IsPointWalkable(&spawn, &m_PFCpnt.m_CharacterType) & 0xffu) == 0) {  // 0x001e42d0
                m_v3Position = {m_unk1c4, m_unk1c8, m_unk1cc};
            }
        }
        const CSGMovable* target = static_cast<const CSGMovable*>(m_unk330->m_pKGLObject);
        const RwMatrix* ltm = FrameLtm(target->m_pRwFrame);  // the stored LTM (+0x80)
        CVector3 toward = {ltm->pos.x - m_v3Position.x, ltm->pos.y - m_v3Position.y, ltm->pos.z - m_v3Position.z};
        const float length =
            std::sqrt(ppc::fmadds(toward.z, toward.z, ppc::fmadds(toward.x, toward.x, toward.y * toward.y)));  // Math_Sqrtf
        if (length != 0.0f) {
            const float inv = 1.0f / length;
            toward.z = toward.z * inv;
            toward.x = toward.x * inv;
            toward.y = toward.y * inv;
        }
        m_unk154 = Vec3_GetYawAngleFromZ(&toward);  // 0x00244528
        CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
        collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &m_v3Position.x, 1);  // 0x00196540
        const int32_t status = m_GrdContDatasInOut.m_eContactStatus;
        if (status == 0) {
            m_v3Position.y = m_v3Position.y - m_GrdContDatasInOut.m_fdH;
        } else if (status > 0 && status <= 2) {
            m_v3Position.y = m_v3Position.y + m_GrdContDatasInOut.m_fdH;
        }
        RequestAnim(9, 0, 0, 0, 2.0e-2f, 0.0f);  // TOC +0x11e0 / +0x11ac
        m_unk7c4 = 0;
        CPFPoint here;
        here.m_unk0c = 0xffff;
        here.m_position = m_v3Position;
        here.m_unk0c = m_PFCpnt.m_Destination.m_unk0c;
        pathFinding->FindSectorForPoint(&here);  // 0x001e5ca0
        m_PFCpnt.m_Destination.m_unk0c = here.m_unk0c;
        m_unk888 = 0;
        return 0x18;
    }
    if (phase == 2) {
        m_unk72c = 0;
        m_unk86f = 0;
        m_unk718 = 0.0f;
        m_unk86e = 0;
        m_unk67c = 0.0f;
        m_unk714 = 0.0f;
        m_unk254 = Cfg()->m_unk1f0;
        SetPartsFlagForCategory(2);  // 0x0027cf30
        if (m_ui8EnemyClassType == 1) {
            const uint32_t r = static_cast<uint32_t>(Rand_Int());
            PlaySound(((r >> 15) & 1u) + 0x2a, 1, m_pKGLObject);  // 0x002795c0
        }
        if (m_ui8EnemyClassType == 7) PlaySound(0x2a, 1, m_pKGLObject);
        return 0x18;
    }
    if (phase != 0) return 0x18;
    if (m_unk258 <= 0.0f) return 0x15;
    const float time = LayerSlotAnimTime(0, 0);
    PlayAnimMarkSounds(time, time + clock->m_afDeltaTime[0]);  // 0x00286c08
    if (IsAnimEndReached(m_unk1fc * m_unk774, 0, 0)) return 1;  // 0x00285558
    return 0x18;
}

// 0x0029df18 CKHkS08Enemy_State19_OneShotAnim_maybe (main row 0x19): enter plays animation 0x35 (blend 0.04); the
// tick waits for its end, then state 1.
uint8_t CKHkS08Enemy::MainState19_OneShotAnim(IKTime* /*clock*/, int32_t phase, uint8_t /*other*/) {
    if (phase == 0) {
        if (IsAnimEndReached(m_unk1fc * m_unk774, 0, 0) != 0) return 1;  // 0x00285558
        return 0x19;
    }
    if (phase == 1) RequestAnim(0x35, 0, 0, 0, 4.0e-2f, 0.0f);  // TOC +0x11b0 / +0x11ac
    return 0x19;
}

// 0x002aa410 CKHkS08Enemy_State07_Grabbed (main row 7): held by a hero (+0x294).
// Enter: the parts of categories 1 and 2 lose their flag, reaction 8, the attack trail on when the holder's blow has its
// flag 0x61, the kind 1's breathing sounds (0x2a, 0x2b) stopped, the hold timer (+0x7c0) reset, an attack slot given
// back, and while hero 1 holds it with the wind beam animation 0x33 (blend 0.1).
// Tick: the ground probed under the node, the trail updated, the anim marks, the hold timer; once the gauge +0x6d0
// reaches the kind's +0x25c under the wind beam, animation 0x3c (once, +0x8f4); then the enemy spins about y at the
// kind's +0x514 radians per second.
// Leave: the node keeps its world matrix and goes back under the dynamic scene root, the trail off, the part flags
// back, the kind 1 breathes again (0x2a or 0x2b at random), the gauge +0x6d0 cleared.
uint8_t CKHkS08Enemy::MainState07_Grabbed(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        ClearPartsFlagForCategory(1);  // 0x0027d018
        ClearPartsFlagForCategory(2);
        SwitchReactState(8, nullptr);  // the original passes no clock
        if (static_cast<CKHkS08Hero*>(m_unk294)->GetCurrentBlowFlag61() != 0) SetAttackTrailActive(1, 1, 0);  // 0x0028b960
        if (m_ui8EnemyClassType == 1) {
            StopSound(0x2a);  // 0x002794f0
            StopSound(0x2b);
        }
        m_unk7c0 = 0.0f;
        if (m_ui8EnemyClassType == 1) {
            StopSound(0x2a);
            StopSound(0x2b);
        }
        if (m_unk891 != 0) {
            static_cast<CKGrpS08Enemy*>(enemy::EnemyGroup())->ReleaseAttackSlot(m_unk7d8, this);  // 0x00267138
            m_unk7d8 = -1;
            m_unk891 = 0;
        }
        CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(static_cast<IKGrpHero*>(enemy::HeroGroup())->m_apHeros[1]);  // 0x002ca080
        if (hero->GetGrabTarget() == this && hero->IsUsingWindBeam() != 0) {
            RequestAnim(0x33, 0, 0, 0, 0.1f, 0.0f);  // TOC +0x11a8
        }
        m_unk8f4 = 0;
        return 7;
    }
    if (phase == 2) {
        CSGLeaf* node = static_cast<CSGLeaf*>(m_pKGLObject);
        node->SetLocalMatrix(&node->m_pRwFrame->ltm);  // 0x000d0be8
        const RwV3d& at = node->m_pRwFrame->modelling.pos;
        m_v3Position.x = at.x;
        m_v3Position.z = at.z;
        m_v3Position.y = at.y;
        if (node->m_pParent != nullptr) node->m_pParent->RemoveChild(node);  // vt+0x78
        static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot)->AddChild(node);  // vt+0x70
        SetAttackTrailActive(1, 0, 0);
        m_unk7c0 = 0.0f;
        SetPartsFlagForCategory(1);  // 0x0027cf30
        SetPartsFlagForCategory(2);
        if (m_ui8EnemyClassType == 1) {
            const uint32_t r = static_cast<uint32_t>(Rand_Int());  // 0x00011500
            PlaySound(static_cast<uint8_t>(((r >> 15) & 1u) + 0x2a), 1, m_pKGLObject);  // 0x002795c0
        }
        m_unk6d0 = 0.0f;
        return 7;
    }
    if (phase != 0) return 7;
    const RwV3d& at = static_cast<CSGLeaf*>(m_pKGLObject)->m_pRwFrame->ltm.pos;
    CVector3 pos{at.x, at.y, at.z};
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut,
                                                                              &pos.x, 1);  // 0x00196540
    if (m_GrdContDatasInOut.m_eContactStatus != 3) GroundContact_GetWorldPoint(&m_GrdContDatasInOut, &pos);  // 0x001a70e0
    if (m_unk294 != nullptr && static_cast<CKHkS08Hero*>(m_unk294)->GetCurrentBlowFlag61() != 0) SetAttackTrailActive(1, 1, 1);
    ProcessAnimMarks();  // 0x00288420
    m_unk7c0 = m_unk7c0 + clock->m_afDeltaTime[0];
    CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(static_cast<IKGrpHero*>(enemy::HeroGroup())->m_apHeros[1]);  // 0x002ca080
    if (m_unk8f4 == 0 && hero->GetGrabTarget() == this && hero->IsUsingWindBeam() != 0 && m_unk6d0 >= Cfg()->m_unk25c) {
        m_unk8f4 = 1;
        RequestAnim(0x3c, 0, 0, 0, 0.1f, 0.0f);  // TOC +0x11a8 / +0x11ac
    }
    if (m_unk8f4 != 0 && hero->GetGrabTarget() == this && hero->IsUsingWindBeam() != 0) {
        float yaw = ppc::fmadds(Cfg()->m_unk514, clock->m_afDeltaTime[0], m_unk154);
        m_unk154 = yaw;
        if (yaw >= 6.2831855f) {  // TOC +0x1250
            yaw = yaw - 6.2831855f;
            m_unk154 = yaw;
        }
        RwFrame* frame = static_cast<CSGLeaf*>(m_pKGLObject)->m_pRwFrame;
        Mat4_SetRotationAboutAxis(yaw, reinterpret_cast<CMatrix34*>(&frame->modelling), 1);  // 0x00241688
        RwFrame_MarkDirty(static_cast<CSGLeaf*>(m_pKGLObject)->m_pRwFrame);  // 0x00010698
    }
    return 7;
}

// 0x0029ddd0 CKHkS08Enemy_vf1A0: returns 8.
uint8_t CKHkS08Enemy::MainState08(IKTime* /*clock*/, int32_t /*phase*/, uint8_t /*other*/) {
    return 8;
}

namespace {
// 0x00a70248 (TOC +0x11ec) +0xe8 / +0x10c: per enemy kind the hit reaction's animation in the air (+0x7d4 set) and on the
// ground (the words' low bytes).
constexpr uint32_t kHitReactAnimHeld[9] = {0x44, 0x43, 0, 0, 0, 0, 0, 0x43, 0};
constexpr uint32_t kHitReactAnim[9] = {0x4d, 0x4c, 0x46, 0x44, 0x44, 0, 0, 0x4c, 0};
}  // namespace

// 0x002a9bc0 CKHkS08Enemy_State0A_HitReaction_maybe (main row 0xa). Enter: reaction 0, the kind's hit animation (held
// +0x7d4: the first table) restarted (blend 0.04). Leave: the volume groups 0, 2 and 1 on, the part flags of categories 1
// and 2 back, the kind 1 breathes again (0x2a or 0x2b at random). Tick: not held, the knockback moves the enemy; an
// animation other than either of the two is replaced by the kind's; at its end, an enemy off its graph node's box or on
// a closed cell takes a move target (+0x85c): with one, reaction 0 and state 0x17; else (or on the nav mesh) a held
// enemy goes to state 1, the others take reaction 8 and state 2.
uint8_t CKHkS08Enemy::MainState0A_HitReaction(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        SwitchReactState(0, nullptr);
        const uint32_t anim = m_unk7d4 != 0 ? kHitReactAnimHeld[m_ui8EnemyClassType] : kHitReactAnim[m_ui8EnemyClassType];
        RequestAnim(static_cast<uint8_t>(anim), 1, 0, 0, 4.0e-2f, 0.0f);  // 0x00285340, TOC +0x11b0 / +0x11ac
        return 0xa;
    }
    if (phase == 2) {
        EnableVolumeGroup(0);  // vt+0xf8
        EnableVolumeGroup(2);
        EnableVolumeGroup(1);
        SetPartsFlagForCategory(1);  // 0x0027cf30
        SetPartsFlagForCategory(2);
        if (m_ui8EnemyClassType == 1) {
            const uint32_t r = static_cast<uint32_t>(Rand_Int());  // 0x00011500
            PlaySound(static_cast<uint8_t>(((r >> 15) & 1u) + 0x2a), 1, m_pKGLObject);  // 0x002795c0
        }
        return 0xa;
    }
    if (phase != 0) return 0xa;
    if (m_unk7d4 == 0) IntegrateKnockbackMotion(clock);  // 0x002987c8
    const uint32_t held = kHitReactAnimHeld[m_ui8EnemyClassType];
    const uint32_t ground = kHitReactAnim[m_ui8EnemyClassType];
    if (GetCurrentAnim(0, 0) != held && GetCurrentAnim(0, 0) != ground) {  // 0x00285408
        RequestAnim(static_cast<uint8_t>(m_unk7d4 != 0 ? held : ground), 1, 0, 0, 4.0e-2f, 0.0f);
        return 0xa;
    }
    if (IsAnimEndReached(m_unk1fc * m_unk774, 0, 0) == 0) return 0xa;  // 0x00285558
    CKSrvPathFinding* pathFinding = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);
    CPFPoint own;
    own.m_unk0c = 0xffff;
    own.m_position = m_v3Position;
    own.m_unk0c = m_PFCpnt.m_Destination.m_unk0c;
    const bool onNav = PointInNodeBox(pathFinding, &own) &&
                       (pathFinding->IsPointWalkable(&own, &m_PFCpnt.m_CharacterType) & 0xffu) != 0;  // 0x001e42d0
    if (!onNav) {
        const CVector3 target = ChooseMoveTarget();  // 0x002808e8
        m_unk85c = target.x;
        m_unk864 = target.z;
        m_unk860 = target.y;
        const CVector3 kNull = {0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC +0x1234)
        if (kNull.x != target.x || kNull.y != target.y || kNull.z != target.z) {
            SwitchReactState(0, clock);
            return 0x17;
        }
    }
    if (m_unk7d4 != 0) return 1;
    SwitchReactState(8, clock);
    return 2;
}

namespace {
// State26_Burning's and vf1AC's new run point (+0x6dc): the flat direction (+0x6e8) toward the picked point normalised
// and the speed (+0x158) pushed along it by the kind's +0x278 (on entry the speed itself, while running the null vector;
// a new point while running restarts the timer +0x6d8). A null point (none reachable) turns the yaw by a quarter
// (Burning) or a quarter per second (vf1AC: `turnPerSecond`) and runs toward +0x140 along the z axis turned by the yaw.
void BurningAimAt(CKHkS08Enemy* self, const CVector3& picked, bool entering, bool turnPerSecond) {
    const CVector3 kNull = {0.0f, 0.0f, 0.0f};   // 0x00c50d64 (TOC +0x1234)
    const CVector3 kAxisZ = {0.0f, 0.0f, 1.0f};  // 0x00c50d4c (TOC +0x1240)
    self->m_unk6dc = picked;
    CVector3& dir = self->m_unk6e8;
    dir = CVector3{picked.x - self->m_v3Position.x, picked.y - self->m_v3Position.y, picked.z - self->m_v3Position.z};
    // BUG(original): on entry the test is on +0x37c (the spawn point copy), not on the picked point as while running.
    const CVector3& tested = entering ? CVector3{self->m_unk37c, self->m_unk380, self->m_unk384} : self->m_unk6dc;
    if (kNull.x == tested.x && kNull.y == tested.y && kNull.z == tested.z) {
        if (turnPerSecond) {
            self->m_unk154 = ppc::fmadds(self->m_unk1fc, 1.5707961f, self->m_unk154);  // TOC +0x123c (0x3fc90fd9)
        } else {
            self->m_unk154 = self->m_unk154 + 1.5707961f;
        }
        self->m_unk6dc = CVector3{self->m_unk140, self->m_unk144, self->m_unk148};
        dir = kAxisZ;
        const CVector3 axis = kAxisZ;
        dir = enemy::Vec3_RotateAboutY(self->m_unk154, &axis);  // 0x0027d460
    } else if (!entering) {
        self->m_unk6d8 = 0.0f;
    }
    dir.y = 0.0f;  // TOC +0x11ac
    const float length = std::sqrt(ppc::fmadds(dir.z, dir.z, ppc::fmadds(dir.x, dir.x, dir.y * dir.y)));  // 0x00010690
    if (length != 0.0f) {
        const float k = 1.0f / length;  // TOC +0x11bc
        dir.z = k * dir.z;
        dir.x = k * dir.x;
        dir.y = k * dir.y;
    }
    CVector3& speed = self->m_unk158;
    if (!entering) speed = kNull;
    const float push = self->m_unk884->m_unk278;
    speed.x = ppc::fmadds(push, dir.x, speed.x);
    speed.z = ppc::fmadds(push, dir.z, speed.z);
    speed.y = ppc::fmadds(push, dir.y, speed.y);
}
}  // namespace

// 0x0029fba0 CKHkS08Enemy_State26_Burning (vt+0x1a8; SetBurning sends a kind with +0x28c here): the enemy runs about
// on fire. Enter: the animation 0x32 (blend 0.4), the timer +0x6d8 at the kind's +0x27c (so the first run picks a new
// point), the yaw the camera's flat view (+0x5c8), a random reachable point to run to (BurningAimAt), +0x254 = 1;
// not kind 8: +0x7b4 cleared; kind 1 stops its voices 0x2a / 0x2b. Run: no health: 0x15 (health 0); an empty burn gauge
// (+0x6b8): SetBurning(0), 1. Else the timer runs; past the kind's +0x27c, or within 1 (flat, squared) of the point, a
// new point; then the no-turn steering toward it (the kind's move component, the avoidance agent, the path finding,
// +0x397 / +0x398). Leave: +0x254 = the kind's +0x1f0; kind 1 plays the voice 0x2a or 0x2b (bit 15 of a draw) looped.
uint8_t CKHkS08Enemy::MainState1A_Burning(IKTime* /*clock*/, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        RequestAnim(0x32, 0, 0, 0, 0.4f, 0.0f);  // 0x00285340; TOC +0x1238 / +0x11ac (r5 / r6: phase and other, unread)
        m_unk6d8 = m_unk884->m_unk27c;
        const CKSrvCamera* camera = static_cast<const CKSrvCamera*>(g_pEngine->m_srvCamera);  // TOC +0x11cc -> +0x70
        m_unk154 = Vec3_GetYawAngleFromZ(&camera->m_v3RealAxisZ);  // 0x00244528
        const CVector3 picked = PickRandomReachablePoint();  // 0x0027fce8
        BurningAimAt(this, picked, true, false);
        m_unk254 = 1.0f;  // TOC +0x11bc
        if (m_ui8EnemyClassType != 8) m_unk7b4 = 0;
        if (m_ui8EnemyClassType == 1) {
            StopSound(0x2a);  // 0x002794f0
            StopSound(0x2b);
        }
        return 0x1a;
    }
    if (phase == 2) {
        m_unk254 = m_unk884->m_unk1f0;
        if (m_ui8EnemyClassType == 1) {
            const uint32_t r = static_cast<uint32_t>(Rand_Int());  // 0x00011500
            PlaySound(static_cast<uint8_t>(((r >> 15) & 1u) + 0x2a), 1, m_pKGLObject);  // 0x002795c0
        }
        return 0x1a;
    }
    if (phase != 0) return 0x1a;
    if (m_unk258 <= 0.0f) {  // TOC +0x11ac
        m_unk258 = 0.0f;
        return 0x15;
    }
    if (m_unk6b8 <= 0.0f) {
        m_unk6b8 = 0.0f;
        SetBurning(0);  // 0x002aec30
        return 1;
    }
    const float timer = m_unk6d8 + m_unk1fc;
    m_unk6d8 = timer;
    bool repick = m_unk884->m_unk27c <= timer;
    if (!repick) {
        const float dx = m_v3Position.x - m_unk6dc.x;
        const float dz = m_v3Position.z - m_unk6dc.z;
        repick = ppc::fmadds(dx, dx, dz * dz) <= 1.0f;  // TOC +0x11bc
    }
    if (repick) {
        const CVector3 picked = PickRandomReachablePoint();  // 0x0027fce8
        BurningAimAt(this, picked, false, false);
    }
    // 0x002c4430 with the kind's move component (+0x884 + 8), no jump.
    m_unk884->m_MoveCpnt.MoveNoTurnSmoothing(&m_v3Position, &m_unk154, &m_unk158, &m_unk6dc, &m_unk6e8, &m_unk1fc,
                                             &m_GrdContDatasIn, &m_avoidance, &m_PFCpnt, m_unk397, nullptr, m_unk398);
    return 0x1a;
}

// 0x002ab050 CKHkS08Enemy_vf1AC (vt+0x1ac, main state 0x1b): Burning's run with the reaction machine (+0x554) ticked
// beside it. Enter: the animation 0x33 (blend 0.4), the timer at the kind's +0x27c, the yaw the camera's flat view
// (+0x5c8) turned by a random angle within 0.349 either way (one draw), a random reachable point (BurningAimAt; a null
// point turns a quarter per second), +0x254 = 1, the reaction ticked once and its answer switched to. Run: the timer
// runs; past the kind's +0x27c, or within 1 (flat, squared) of the path finding's target (+0xbc +0x60), a new point;
// the no-turn steering, the reaction ticked and switched; with the status gauge 6 (+0x6cc) at 0: 2 while a reaction other
// than 0 runs, else 1. Leave: +0x254 = the kind's +0x1f0. Else 0x1b.
uint8_t CKHkS08Enemy::MainState1B(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    auto tickReaction = [&]() {
        const uint8_t current = m_reactState;
        if (current == 0xff) return;
        const uint8_t next = CallReactState(current, clock, 0, current);
        const uint8_t old = m_reactState;
        if (next == old) return;
        if (old != 0xff) CallReactState(old, clock, 2, next);
        m_reactState = next;
        if (next != 0xff) CallReactState(next, clock, 1, old);
    };
    if (phase == 1) {
        RequestAnim(0x33, 0, 0, 0, 0.4f, 0.0f);  // 0x00285340; TOC +0x1238 / +0x11ac (r5 / r6: phase and other, unread)
        m_unk6d8 = m_unk884->m_unk27c;
        const CKSrvCamera* camera = static_cast<const CKSrvCamera*>(g_pEngine->m_srvCamera);  // TOC +0x11cc -> +0x70
        const float view = Vec3_GetYawAngleFromZ(&camera->m_v3RealAxisZ);  // 0x00244528
        const float r = static_cast<float>(static_cast<double>(static_cast<uint32_t>(Rand_Int()) & 0xffffu));  // 0x00011500
        const float base = view + 0.34906581f;  // TOC +0x1278 (0x3eb2b8c1)
        const float unit = r / 65535.0f;          // TOC +0x11c4
        m_unk154 = ppc::fmadds(unit + unit, -0.34906581f, base);  // TOC +0x127c
        const CVector3 picked = PickRandomReachablePoint();  // 0x0027fce8
        BurningAimAt(this, picked, true, true);
        m_unk254 = 1.0f;  // TOC +0x11bc
        tickReaction();
        return 0x1b;
    }
    if (phase == 2) {
        m_unk254 = m_unk884->m_unk1f0;
        return 0x1b;
    }
    if (phase != 0) return 0x1b;
    const float timer = m_unk6d8 + m_unk1fc;
    m_unk6d8 = timer;
    bool repick = m_unk884->m_unk27c <= timer;
    if (!repick) {
        const CVector3& goal = m_PFCpnt.m_ptTargetPosition.m_position;  // +0x11c
        const float dx = m_v3Position.x - goal.x;
        const float dz = m_v3Position.z - goal.z;
        repick = ppc::fmadds(dx, dx, dz * dz) <= 1.0f;  // TOC +0x11bc
    }
    if (repick) {
        const CVector3 picked = PickRandomReachablePoint();  // 0x0027fce8
        BurningAimAt(this, picked, false, true);
    }
    // 0x002c4430 with the kind's move component (+0x884 + 8), no jump.
    m_unk884->m_MoveCpnt.MoveNoTurnSmoothing(&m_v3Position, &m_unk154, &m_unk158, &m_unk6dc, &m_unk6e8, &m_unk1fc,
                                             &m_GrdContDatasIn, &m_avoidance, &m_PFCpnt, m_unk397, nullptr, m_unk398);
    tickReaction();
    const uint8_t now = m_reactState;
    if (m_unk6cc != 0.0f) return 0x1b;  // TOC +0x11ac
    return now != 0 ? 2 : 1;
}

// 0x002a7820 CKHkS08Enemy_vf1B0 (vt+0x1b0, main state 0x1c; Ghidra gives no decompile: ported from the instructions).
// The enemy wanders in circles. Enter: the timer +0x6d8 cleared, a random turn speed (+0x6f4, -60..60 degrees per
// second, one draw), with a target (+0x330) the yaw set to the dot product of (position - the target node's position)
// with the z axis, +0x254 = 1, the reaction (+0x554) ticked once and its answer switched to. Run: past the kind's +0x27c
// the timer restarts with a new turn speed (one draw); an enemy nearer (flat, squared) the active enemies' centroid than
// the farthest active enemy is from it faces away from the centroid; the yaw turns by the turn speed, the position moves
// 5 per second along it (a position equal to the last one, +0x140, turns the yaw by a further eighth); with the status
// gauge 5 (+0x6c4) at 0: 2 while a reaction other than 0 runs, else 1. Leave: +0x254 = the kind's +0x1f0. Else 0x1c.
uint8_t CKHkS08Enemy::MainState1C(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    const CVector3 kAxisZ = {0.0f, 0.0f, 1.0f};  // 0x00c50d4c (TOC +0x1240)
    auto randomTurnSpeed = [&]() {
        const float r = static_cast<float>(static_cast<double>(static_cast<uint32_t>(Rand_Int()) & 0xffffu));  // 0x00011500
        m_unk6f4 = ppc::fmsubs(r / 65535.0f, 120.0f, 60.0f) * 0.017453290f;  // TOC +0x11c4, +0x1264, +0x1268, +0x11e4
    };
    if (phase == 1) {
        m_unk6d8 = 0.0f;
        randomTurnSpeed();
        if (m_unk330 != nullptr) {
            const RwV3d& at = static_cast<CSGMovable*>(m_unk330->m_pKGLObject)->m_pRwFrame->modelling.pos;
            // BUG(original) _maybe: a dot product with the z axis stored as the yaw.
            const float dy = m_v3Position.y - at.y;
            const float dx = m_v3Position.x - at.x;
            const float dz = m_v3Position.z - at.z;
            m_unk154 = ppc::fmadds(dz, kAxisZ.z, ppc::fmadds(dx, kAxisZ.x, dy * kAxisZ.y));
        }
        m_unk254 = 1.0f;  // TOC +0x11bc
        const uint8_t current = m_reactState;
        if (current == 0xff) return 0x1c;
        const uint8_t next = CallReactState(current, clock, 0, current);
        const uint8_t old = m_reactState;
        if (next == old) return 0x1c;
        if (old != 0xff) CallReactState(old, clock, 2, next);
        m_reactState = next;
        if (next != 0xff) CallReactState(next, clock, 1, old);
        return 0x1c;
    }
    if (phase == 2) {
        m_unk254 = m_unk884->m_unk1f0;
        return 0x1c;
    }
    if (phase != 0) return 0x1c;
    const float timer = m_unk6d8 + m_unk1fc;
    m_unk6d8 = timer;
    if (m_unk884->m_unk27c <= timer) {  // 0x2a7df8
        m_unk6d8 = 0.0f;
        randomTurnSpeed();
    }
    // 0x2a78dc: the farthest active enemy from this one (flat, squared) against the centroid's distance.
    const CVector3 centroid = GetActiveEnemyCentroid();  // 0x0027df10
    const IKGrpEnemy* group = static_cast<const IKGrpEnemy*>(enemy::EnemyGroup());  // 0x00276f58
    const uint32_t active = group->m_ui32NbActiveEnemies;
    float farthest = 0.0f;  // TOC +0x11ac
    for (uint32_t i = 0; i < active; ++i) {
        const IKGrpEnemy* g = static_cast<const IKGrpEnemy*>(enemy::EnemyGroup());
        const CKHkS08Enemy* other = static_cast<const CKHkS08Enemy*>(g->m_apActiveEnemies[i]);
        const float dz = m_v3Position.z - other->m_v3Position.z;
        const float dx = m_v3Position.x - other->m_v3Position.x;
        const float squared = ppc::fmadds(dx, dx, dz * dz);
        if (squared > farthest) farthest = squared;  // ble
    }
    float awayX = m_v3Position.x - centroid.x;
    float awayZ = m_v3Position.z - centroid.z;
    const float x2 = awayX * awayX;
    const float z2 = awayZ * awayZ;
    if (x2 + z2 < farthest) {  // 0x2a7da4: face away from the centroid
        const float length = std::sqrt(z2 + (x2 + 0.0f));  // 0x00010690
        if (length != 0.0f) {
            const float k = 1.0f / length;  // TOC +0x11bc
            awayZ = awayZ * k;
            awayX = awayX * k;
        }
        const bool outside = awayZ < 0.0f ? awayZ < -1.0f : awayZ > 1.0f;  // TOC +0x11d8 / +0x11bc
        if (outside) {
            m_unk154 = awayZ < 0.0f ? 3.14159274f : 0.0f;  // TOC +0x124c
        } else {
            const float angle = crt::Acosf(awayZ);  // TocBridge_Math_Acosf 0x98e1a0
            m_unk154 = awayX < 0.0f ? 6.28318548f - angle : angle;  // TOC +0x1250
        }
    }
    // 0x2a79a8
    m_unk154 = ppc::fmadds(m_unk6f4, m_unk1fc, m_unk154);
    const CVector3 forward = enemy::Vec3_RotateAboutY(m_unk154, &kAxisZ);  // 0x0027d460
    const float step = m_unk1fc * 5.0f;  // TOC +0x126c
    m_v3Position.x = ppc::fmadds(step, forward.x, m_v3Position.x);
    m_v3Position.z = ppc::fmadds(forward.z, step, m_v3Position.z);
    m_v3Position.y = ppc::fmadds(forward.y, step, m_v3Position.y);
    if (m_unk140 == m_v3Position.x && m_unk144 == m_v3Position.y && m_unk148 == m_v3Position.z) {
        m_unk154 = m_unk154 + 0.785398066f;  // TOC +0x1270 (0x3f490fd9)
    }
    if (m_unk6c4 != 0.0f) return 0x1c;  // TOC +0x11ac
    return m_reactState != 0 ? 2 : 1;
}

// 0x002a91a0 CKHkS08Enemy_State1D_WindCaught_maybe (vt+0x1b4): a wind whirls the enemy up and about a point (+0x824).
// Enter: the animation 0x3c (blend 0.4), the FX 0x1d at hot spot 1, the angle +0x820 cleared, the height +0x81c drawn
// around the kind's +0x500 (+-+0x504, one draw); the point: the hero 1's hot spot 0 for an element damage 0x11 pending,
// kept for another element damage that is not 0x12, else the enemy's position; the looping sound 0x1f, kind 1 stops its
// voices 0x2a / 0x2b, the attack spheres on. Run: with +0x899 and an element damage pending the point follows (8 per
// second) the hero 1's hot spot 0 (damage 0x11 not continuous, +0x0c) or the hero 1's grab target's node (0x12); the
// ground probed; a height equal to +0x81c draws a new one; the height approaches it (the kind's +0x508 per second);
// outside the kind's +0x50c (flat, squared) from the point the angle turns (+0x510 per second, below 2 pi); the target
// on the circle of radius +0x50c at that angle (the x axis turned about y): inside, x and z approach it (1 per second),
// outside they jump to it; the yaw turns (+0x514 per second); with +0x7b8 the wind spreads to the active enemies
// within the kind's +0x518 (the gauge x +0x51c x dt, their +0x7b8 set); an empty wind gauge (+0x6d0) switches the
// reaction to 8 (with the clock): 2. Leave: the gauge and +0x7b8 cleared, the sound 0x1f stops, kind 1 plays the voice
// 0x2a or 0x2b (bit 15 of a draw) looped, the attack spheres off. Else 0x1d.
uint8_t CKHkS08Enemy::MainState1D_WindCaught(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        RequestAnim(0x3c, 0, 0, 0, 0.4f, 0.0f);  // 0x00285340; TOC +0x1238 / +0x11ac
        PlayFxAtHotspot1(0x1d);                  // 0x0028d4a8
        const float spread = m_unk884->m_unk504;
        const float middle = m_unk884->m_unk500;
        const float r = static_cast<float>(static_cast<double>(static_cast<uint32_t>(Rand_Int()) & 0xffffu));  // 0x00011500
        const float again = m_unk884->m_unk504;
        m_unk820 = 0.0f;
        float offset = spread * (r / 65535.0f);  // TOC +0x11c4
        offset = offset + offset;
        offset = offset - again;
        m_unk81c = middle + offset;
        bool keep = false;
        if (m_unk27c != nullptr && m_unk27c->IsKindOfClass(0x99cc) != 0) {  // vt+0x08
            const int32_t element = static_cast<CKS08ElementDamage*>(m_unk27c)->m_unk38;
            if (element == 0x11) {
                CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(static_cast<IKGrpHero*>(enemy::HeroGroup())->m_apHeros[1]);  // 0x002ca080
                static_cast<CSGHotSpot*>(hero->GetHotSpot(0))->GetWorldPosition(&m_unk824);  // 0x00361b70, 0x000ce790
                keep = true;
            } else if (element != 0x12) {
                keep = true;
            }
        }
        if (!keep) m_unk824 = m_v3Position;
        PlaySound(0x1f, 1, m_pKGLObject);  // 0x002795c0
        if (m_ui8EnemyClassType == 1) {
            StopSound(0x2a);  // 0x002794f0
            StopSound(0x2b);
        }
        SetAttackSpheresActive(1, nullptr);  // 0x00288e08
        return 0x1d;
    }
    if (phase == 2) {
        m_unk6d0 = 0.0f;
        m_unk7b8 = 0;
        StopSound(0x1f);
        if (m_ui8EnemyClassType == 1) {
            const uint32_t r = static_cast<uint32_t>(Rand_Int());
            PlaySound(static_cast<uint8_t>(((r >> 15) & 1u) + 0x2a), 1, m_pKGLObject);
        }
        SetAttackSpheresActive(0, nullptr);
        return 0x1d;
    }
    if (phase != 0) return 0x1d;
    const CKS08EnemyCpnt* cfg = m_unk884;
    const float dt = clock->m_afDeltaTime[0];
    // The point follows `target` by 8 per second (Math_InvSqrtf 0x114d8: RW's table inverse square root).
    auto follow = [&](const CVector3& target) {
        CVector3 p = m_unk824;
        if (p.x != target.x || p.y != target.y || p.z != target.z) {
            const float dy = target.y - p.y;
            const float dx = target.x - p.x;
            const float step = dt * 8.0f;  // TOC +0x1274
            const float dz = target.z - p.z;
            const float distance2 = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
            if (step * step > distance2) {
                p = target;
            } else {
                const float k = step * rwInvSqrt(distance2);
                p.z = ppc::fmadds(dz, k, p.z);
                p.x = ppc::fmadds(dx, k, p.x);
                p.y = ppc::fmadds(dy, k, p.y);
            }
        }
        m_unk824 = p;
    };
    if (m_unk27c != nullptr && m_unk899 != 0 && m_unk27c->IsKindOfClass(0x99cc) != 0) {
        const int32_t element = static_cast<CKS08ElementDamage*>(m_unk27c)->m_unk38;
        if (element == 0x11) {
            if (m_unk27c->m_unk0c == 0) {
                CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(static_cast<IKGrpHero*>(enemy::HeroGroup())->m_apHeros[1]);  // 0x002ca080
                CVector3 at;
                static_cast<CSGHotSpot*>(hero->GetHotSpot(0))->GetWorldPosition(&at);  // 0x00361b70, 0x000ce790
                follow(at);
            }
        } else if (element == 0x12) {
            const CKHkS08Hero* hero = static_cast<const CKHkS08Hero*>(static_cast<IKGrpHero*>(enemy::HeroGroup())->m_apHeros[1]);
            if (hero->GetGrabTarget() != nullptr) {  // 0x00329df8
                const IKHook* held = static_cast<const IKHook*>(hero->GetGrabTarget());
                const RwV3d& at = FrameLtm(static_cast<CSGMovable*>(held->m_pKGLObject)->m_pRwFrame)->pos;
                follow(CVector3{at.x, at.y, at.z});
            }
        }
    }
    // 0x2a923c: the ground under the enemy.
    float ground = m_v3Position.y;
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &m_v3Position.x, 1);  // 0x00196540
    const int32_t status = static_cast<int32_t>(m_GrdContDatasInOut.m_eContactStatus);
    if (status == 0) {
        ground = m_v3Position.y - m_GrdContDatasInOut.m_fdH;
    } else if (status >= 0 && status <= 2) {
        ground = m_v3Position.y + m_GrdContDatasInOut.m_fdH;
    }
    if (m_unk81c == m_v3Position.y - ground) {
        const float middle = cfg->m_unk500;
        const float spread = cfg->m_unk504;
        const float r = static_cast<float>(static_cast<double>(static_cast<uint32_t>(Rand_Int()) & 0xffffu));
        float offset = spread * (r / 65535.0f);
        offset = offset + offset;
        offset = offset - cfg->m_unk504;
        m_unk81c = middle + offset;
    }
    float lift[3] = {m_unk81c, cfg->m_unk508, m_v3Position.y - ground};
    m_v3Position.y = FloatApproach_Step(dt, lift) + ground;  // 0x002436e8
    const float pz = m_v3Position.z - m_unk824.z;
    const float px = m_v3Position.x - m_unk824.x;
    const float away = ppc::fmadds(px, px, pz * pz);
    float angle = m_unk820;
    if (m_unk884->m_unk50c < away) {
        angle = ppc::fmadds(cfg->m_unk510, dt, angle);
        m_unk820 = angle;
    }
    const float kTwoPi = 6.28318548f;  // TOC +0x1250
    if (angle >= kTwoPi) {
        angle = angle - kTwoPi;
        m_unk820 = angle;
    }
    CVector3 out;
    CVector3 axisX = {1.0f, 0.0f, 0.0f};  // 0x00c50d34 (TOC +0x1258)
    CVector3 axisY = {0.0f, 1.0f, 0.0f};  // 0x00c50d40 (TOC +0x11f0)
    const float centreZ = m_unk824.z;
    const float centreX = m_unk824.x;
    Vec3_RotateTowardByAngle(&out, &axisX, &axisY, angle);  // TocBridge 0x0098f300 -> 0x005841a8
    float ox = out.x;
    float oz = out.z;
    const float length = std::sqrt(ppc::fmadds(oz, oz, ppc::fmadds(ox, ox, out.y * out.y)));  // 0x00010690
    if (length != 0.0f) {
        const float k = 1.0f / length;  // TOC +0x11bc
        oz = oz * k;
        ox = ox * k;
    }
    const float tz = ppc::fmadds(cfg->m_unk50c, oz, centreZ);
    const float tx = ppc::fmadds(cfg->m_unk50c, ox, centreX);
    if (m_unk884->m_unk50c >= away) {
        float stepX[3] = {tx, 1.0f, m_v3Position.x};  // TOC +0x11bc
        m_v3Position.x = FloatApproach_Step(dt, stepX);
        float stepZ[3] = {tz, 1.0f, m_v3Position.z};
        m_v3Position.z = FloatApproach_Step(dt, stepZ);
    } else {
        m_v3Position.x = tx;
        m_v3Position.z = tz;
    }
    const float yaw = ppc::fmadds(cfg->m_unk514, dt, m_unk154);
    m_unk154 = yaw;
    if (yaw >= kTwoPi) m_unk154 = yaw - kTwoPi;
    if (m_unk7b8 != 0) {
        const uint32_t active = static_cast<const IKGrpEnemy*>(enemy::EnemyGroup())->m_ui32NbActiveEnemies;  // 0x00276f58
        for (uint32_t i = 0; i < active; ++i) {
            CKHkS08Enemy* other =
                static_cast<CKHkS08Enemy*>(static_cast<const IKGrpEnemy*>(enemy::EnemyGroup())->m_apActiveEnemies[i]);
            if (other == this) continue;
            const float dz = m_v3Position.z - other->m_v3Position.z;
            const float dx = m_v3Position.x - other->m_v3Position.x;
            if (ppc::fmadds(dx, dx, dz * dz) <= m_unk884->m_unk518) {
                other->AddWindGauge(m_unk6d0 * m_unk884->m_unk51c * m_unk1fc);  // 0x0027cf08
                other->m_unk7b8 = 1;
            }
        }
    }
    if (!(m_unk6d0 <= 0.0f)) return 0x1d;  // TOC +0x11ac
    SwitchReactState(8, clock);
    return 2;
}

// 0x002a8fa8 CKHkS08Enemy_State1E_WaitWindGaugeEmpty_maybe (vt+0x1b8): enter: the animation 0x32 (blend 0.1). Run: once
// the wind gauge (+0x6d0) is 0 or less the reaction machine goes to 8 (with the clock) and the state to 2. Else 0x1e.
uint8_t CKHkS08Enemy::MainState1E_WaitWindGaugeEmpty(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    if (phase == 0) {
        if (!(m_unk6d0 <= 0.0f)) return 0x1e;
        SwitchReactState(8, clock);
        return 2;
    }
    if (phase == 1) RequestAnim(0x32, 0, 0, 0, 0.1f, 0.0f);  // 0x00285340
    return 0x1e;
}

// 0x002a8748 CKHkS08Enemy_State1F_Stunned_maybe (vt+0x1bc): enter: one of the kind's three stun animations (base
// 0x00a7030c[kind] + (r & 0xffff) x 3 >> 16; blend 0.1), the stun sparks on, the timer +0x71c cleared and the next
// variation time +0x720 drawn between the kind's +0x318 and +0x31c, the looping sound 0x16; kind 1 stops its voices
// 0x2a / 0x2b. Run: a pending hit (+0x239, not applied here): at 0 health the kinds 5 / 6 enter the death reaction (0xf,
// no clock) and the state 2, the others 0x15; a hit that is not the element damage 3 (+0x20) clears the stun gauge
// (+0x6d4) and, but for the kinds 5 / 6 (1), starts the hurt reaction (2, with the clock): 2. Then an empty stun gauge
// ends it (1); else the timer runs and past +0x720 a new time is drawn and the next of the three animations (the current
// one's index plus the rand's bit 15, modulo 3) requested; every hot spot emits the particle nodes 9 and 0x11, and with
// +0x7b6 the stun spreads to the enemies within the kind's +0x324 (gauge x dt). Leave: the sparks off, the sound 0x16
// stops, the gauge 0; kind 1 plays the voice 0x2a or 0x2b (bit 15 of a rand draw) looped. Else 0x1f.
uint8_t CKHkS08Enemy::MainState1F_Stunned(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        const uint32_t base = kStunAnimBase[m_ui8EnemyClassType];
        const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;  // 0x00011500
        RequestAnim(static_cast<uint8_t>(base + ((r * 3u) >> 16)), 0, 0, 0, 0.1f, 0.0f);  // 0x00285340
        SetStunFxActive(1);  // 0x0028d1b8
        m_unk71c = 0.0f;
        const uint32_t r2 = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
        const CKS08EnemyCpnt* cfg = m_unk884;
        m_unk720 = ppc::fmadds(static_cast<float>(static_cast<double>(r2)) / 65535.0f, cfg->m_unk31c - cfg->m_unk318,
                               cfg->m_unk318);  // TOC +0x11c4
        PlaySound(0x16, 1, m_pKGLObject);  // 0x002795c0
        if (m_ui8EnemyClassType == 1) {
            StopSound(0x2a);  // 0x002794f0
            StopSound(0x2b);
        }
        return 0x1f;
    }
    if (phase == 2) {
        SetStunFxActive(0);
        StopSound(0x16);
        m_unk6d4 = 0.0f;
        if (m_ui8EnemyClassType != 1) return 0x1f;
        const uint32_t r = static_cast<uint32_t>(Rand_Int());
        PlaySound(static_cast<uint8_t>(((r >> 15) & 1u) + 0x2a), 1, m_pKGLObject);
        return 0x1f;
    }
    if (phase != 0) return 0x1f;
    if (m_unk239 != 0) {
        if (m_unk258 <= 0.0f) {  // TOC +0x11ac
            if (static_cast<uint8_t>(m_ui8EnemyClassType - 5) > 1) return 0x15;
            SwitchReactState(0xf, nullptr);
            return 2;
        }
        if (m_unk27c->IsKindOfClass(0x99cc) == 0 || m_unk27c->m_unk20 != 3) {  // vt+0x08
            m_unk6d4 = 0.0f;
            if (static_cast<uint8_t>(m_ui8EnemyClassType - 5) <= 1) return 1;
            SwitchReactState(2, clock);
            return 2;
        }
    }
    if (m_unk6d4 <= 0.0f) return 1;
    const float timer = m_unk71c + m_unk1fc;
    m_unk71c = timer;
    if (m_unk720 <= timer) {
        m_unk71c = 0.0f;
        const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
        const CKS08EnemyCpnt* cfg = m_unk884;
        m_unk720 = ppc::fmadds(static_cast<float>(static_cast<double>(r)) / 65535.0f, cfg->m_unk31c - cfg->m_unk318,
                               cfg->m_unk318);
        const uint32_t base = kStunAnimBase[m_ui8EnemyClassType];
        uint32_t index = static_cast<uint32_t>(GetCurrentAnim(0, 0)) - base;  // 0x00285408
        index = index + ((static_cast<uint32_t>(Rand_Int()) >> 15) & 1u);
        RequestAnim(static_cast<uint8_t>(index % 3u + kStunAnimBase[m_ui8EnemyClassType]), 0, 0, 0, 0.1f, 0.0f);
    }
    const uint32_t count = enemy::kHotSpotCount[m_ui8EnemyClassType];  // TOC +0x11ec +0xb8 (0x00a70300)
    for (uint32_t i = 0; i < count; ++i) {
        CVector3 at;
        GetHotSpot(static_cast<int32_t>(i))->GetWorldPosition(&at);  // 0x002892e8, 0x000ce790
        const CVector3 a = at;
        EmitParticleAt(9, &a, nullptr, 0);  // 0x00278028
        const CVector3 b = at;
        EmitParticleAt(0x11, &b, nullptr, 0);
    }
    if (m_unk7b6 != 0) SpreadStunToNearby(m_unk6d4 * m_unk1fc, m_unk884->m_unk324);  // 0x002ae5e8
    return 0x1f;
}

// 0x0029e2c8 CKHkS08Enemy_State0x20_Alerted_maybe: the alert's animation 0x34 and sound 0x23 (kind 1 stops its sounds
// 0x2a / 0x2b); at its end state 1; leaving it, kind 1 plays 0x2a or 0x2b (a rand draw's bit 15) looped.
uint8_t CKHkS08Enemy::MainState20_Alerted(IKTime* clock, int32_t phase, uint8_t other) {
    (void)clock;
    (void)other;
    if (phase == 1) {
        RequestAnim(0x34, 0, 0, 0, 0.1f, 0.0f);  // TOC +0x11a8 / +0x11ac
        PlaySound(0x23, 0, m_pKGLObject);
        if (m_ui8EnemyClassType == 1) {
            StopSound(0x2a);  // 0x002794f0
            StopSound(0x2b);
        }
        return 0x20;
    }
    if (phase == 2) {
        if (m_ui8EnemyClassType != 1) return 0x20;
        const uint32_t r = static_cast<uint32_t>(Rand_Int());  // 0x00011500
        PlaySound(static_cast<uint8_t>(((r >> 15) & 1u) + 0x2a), 1, m_pKGLObject);
        return 0x20;
    }
    if (phase != 0) return 0x20;
    if (IsAnimEndReached(m_unk1fc * m_unk774, 0, 0)) return 1;  // 0x00285558
    return 0x20;
}

// 0x0029e6e8 CKHkS08Enemy_State0x21_DropEquipment_maybe (vt+0x1c4): enter: without a shield the animation 0x2e, with
// one 0x40 for kind 5 only (blend 0.1); the weapon held is kept in +0x838, +0x7ce cleared. Run: the layer 0 animation's
// mark 0x15 crossed over this frame drops the weapon or shield (DropWeaponOrShield, +0x7ce = 1); at the animation's
// end (dt +0x1fc x +0x774) 1. Leave: when nothing was dropped yet, it is dropped now. Else 0x21.
uint8_t CKHkS08Enemy::MainState21_DropEquipment(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        if (m_unk524 == nullptr) {
            RequestAnim(0x2e, 0, 0, 0, 0.1f, 0.0f);  // 0x00285340; TOC +0x11a8 / +0x11ac
        } else if (m_ui8EnemyClassType == 5) {
            RequestAnim(0x40, 0, 0, 0, 0.1f, 0.0f);
        }
        m_unk838 = m_unk520;
        m_unk7ce = 0;
        return 0x21;
    }
    if (phase == 2) {
        if (m_unk7ce == 0) DropWeaponOrShield();  // 0x0029d390
        return 0x21;
    }
    if (phase != 0) return 0x21;
    RtAnimAnimation* animation = CurrentLayer0Animation();  // 0x002771c0, 0x002b3128, 0x00285408
    float t0 = GetAnimLayerTime(0, 0) - clock->m_afDeltaTime[0];  // 0x00285388
    if (t0 < 0.0f) t0 = 0.0f;  // TOC +0x11ac
    AnimMark* mark = Anim_GetMarkById(animation, 0x15);  // 0x00078830
    if (mark != nullptr && AnimMark_CrossedValueR3(mark, t0, GetAnimLayerTime(0, 0)) != 0) {  // vt+0x1c
        DropWeaponOrShield();  // 0x0029d390
        m_unk7ce = 1;
    }
    if (IsAnimEndReached(m_unk1fc * m_unk774, 0, 0)) return 1;  // 0x00285558
    return 0x21;
}

// 0x0029f0a0 CKHkS08Enemy_State0x22_BlockAndCounter_maybe (vt+0x1c8): enter: the block animation 0x36 (blend 0.1);
// the kind's attack volumes (bounding type 3) its +0x348 flags get the kind's damage (+0x344) as their +0x1c; kind 5
// shows its weapon trail and emits particle node 10 at the weapon's hot spot (+0xac[0]); the block count (+0x72c) grows
// and the FX 0x16 is set off at the hit position (+0x23c). Run: at the animation's end (dt +0x1fc x +0x774) 1; kind 5
// updates the trail and its particles. Leave: kind 5's trail off; +0x718 and the block count cleared. Else 0x22.
uint8_t CKHkS08Enemy::MainState22_BlockAndCounter(IKTime* /*clock*/, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        RequestAnim(0x36, 0, 0, 0, 0.1f, 0.0f);  // 0x00285340; TOC +0x11a8 / +0x11ac
        // TOC +0x11ec (0x00a70248): kAttackVolumeFirst / kAttackVolumeCount.
        const uint32_t kind = m_ui8EnemyClassType;
        uint32_t index = kAttackVolumeFirst[kind];
        IKSerializable* damage = m_unk884->m_pUnk344;
        const uint32_t count = kAttackVolumeCount[kind];
        for (uint32_t i = 0; i < count; ++i) {
            if (m_unk884->m_vUnk348.m_pBlock[i] != 0) static_cast<IKBoundingVolume*>(m_unk2C[index])->m_unk1c = damage;
            ++index;
        }
        if (m_ui8EnemyClassType == 5) {
            SetAttackTrailActive(0, 1, 0);  // 0x0028b960
            if (m_ui8EnemyClassType == 5) {
                CVector3 at;
                static_cast<CSGHotSpot*>(m_unk520->m_apUnkAC[0])->GetWorldPosition(&at);  // 0x000ce790
                const CVector3 point = at;
                EmitParticleAt(10, &point, nullptr, 0);  // 0x00278028
            }
        }
        m_unk72c = m_unk72c + 1;
        SpawnHitFxAt(0x16, reinterpret_cast<const CVector3*>(m_unk23c));  // 0x0028c590
        return 0x22;
    }
    if (phase == 2) {
        if (m_ui8EnemyClassType == 5) SetAttackTrailActive(0, 0, 0);
        m_unk718 = 0.0f;
        m_unk72c = 0;
        return 0x22;
    }
    if (phase != 0) return 0x22;
    if (IsAnimEndReached(m_unk1fc * m_unk774, 0, 0)) return 1;  // 0x00285558
    if (m_ui8EnemyClassType != 5) return 0x22;
    SetAttackTrailActive(0, 1, 1);
    if (m_ui8EnemyClassType != 5) return 0x22;
    CVector3 at;
    static_cast<CSGHotSpot*>(m_unk520->m_apUnkAC[0])->GetWorldPosition(&at);
    const CVector3 point = at;
    EmitParticleAt(10, &point, nullptr, 0);
    return 0x22;
}

// 0x0029ddd8 CKHkS08Enemy_vf1CC: returns 35.
uint8_t CKHkS08Enemy::MainState23(IKTime* /*clock*/, int32_t /*phase*/, uint8_t /*other*/) {
    return 35;
}

// 0x002a81f0 CKHkS08Enemy_State0x24_Feared_maybe (vt+0x1d0): enter: +0x708 = 1, the animation 0x33 (blend 0.1), the
// looping sound 0x21; kind 1 stops its voices 0x2a / 0x2b. Run: a pending hit (+0x239) is applied (with a clock); at 0
// health the kinds 5 / 6 enter the death reaction (0xf, no clock) and the state 2, the others 0x15; a hit that is not
// the element damage 6 (+0x20) starts the hurt reaction (2, with the clock): 2. Otherwise the fear gauge (+0x6cc) loses
// dt, every hot spot of the kind emits the particle nodes 7 and 0x10, and below 0 the gauge is 0, +0x708 cleared: 1.
// Leave: the sound 0x21 stops; kind 1 plays the voice 0x2a or 0x2b (one rand draw, bit 15) looped. Else 0x24.
uint8_t CKHkS08Enemy::MainState24_Feared(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        m_unk708 = 1;
        RequestAnim(0x33, 0, 0, 0, 0.1f, 0.0f);  // 0x00285340; TOC +0x11a8 / +0x11ac
        PlaySound(0x21, 1, m_pKGLObject);  // 0x002795c0
        if (m_ui8EnemyClassType == 1) {
            StopSound(0x2a);  // 0x002794f0
            StopSound(0x2b);
        }
        return 0x24;
    }
    if (phase == 2) {
        StopSound(0x21);
        if (m_ui8EnemyClassType == 1) {
            const uint32_t r = static_cast<uint32_t>(Rand_Int());  // 0x00011500
            PlaySound(static_cast<uint8_t>(((r >> 15) & 1u) + 0x2a), 1, m_pKGLObject);
        }
        return 0x24;
    }
    if (phase != 0) return 0x24;
    if (m_unk239 != 0) {
        if (clock != nullptr) ApplyPendingDamage(clock);  // 0x00299f30
        if (m_unk258 <= 0.0f) {  // TOC +0x11ac
            if (static_cast<uint8_t>(m_ui8EnemyClassType - 5) > 1) return 0x15;
            SwitchReactState(0xf, nullptr);
            return 2;
        }
        if (m_unk27c->IsKindOfClass(0x99cc) == 0 || m_unk27c->m_unk20 != 6) {  // vt+0x08
            SwitchReactState(2, clock);
            return 2;
        }
    }
    float gauge = m_unk6cc - clock->m_afDeltaTime[0];
    const uint32_t count = enemy::kHotSpotCount[m_ui8EnemyClassType];  // TOC +0x11ec +0xb8 (0x00a70300)
    m_unk6cc = gauge;
    if (count != 0) {
        for (uint32_t i = 0; i < count; ++i) {
            CVector3 at;
            GetHotSpot(static_cast<int32_t>(i))->GetWorldPosition(&at);  // 0x002892e8, 0x000ce790
            const CVector3 a = at;
            EmitParticleAt(7, &a, nullptr, 0);  // 0x00278028
            const CVector3 b = at;
            EmitParticleAt(0x10, &b, nullptr, 0);
        }
        gauge = m_unk6cc;
    }
    if (gauge < 0.0f) {
        m_unk6cc = 0.0f;
        m_unk708 = 0;
        return 1;
    }
    return 0x24;
}

// 0x0029e470 CKHkS08Enemy_vf1D4 (vt+0x1d4, main state 0x25: sinking into the ground): enter: animation 0 from a random
// time of its length (one rand draw: (r & 0xffff) / 65535 x the duration), blend 0.2. Run: the enemy sinks by 3 units
// a second; the ground probe: no contact (status other than 0) or a depth below 0.05 ends it (0x16). Leave: the ground
// probe again; status 0 moves all three coordinates by -dH, status 1..2 by +dH (BUG(original): x and z too). Else 0x25.
uint8_t CKHkS08Enemy::MainState25(IKTime* /*clock*/, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;  // 0x00011500
        const float duration = GetAnimDuration(0, 0, 0);  // 0x00285638
        const float start = (static_cast<float>(static_cast<double>(r)) / 65535.0f) * duration;  // TOC +0x11c4
        RequestAnim(0, 0, 0, 0, 0.2f, start);  // 0x00285340; TOC +0x11c0
        return 0x25;
    }
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);  // TOC +0x11cc -> +0x58
    if (phase == 2) {
        collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &m_v3Position.x, 1);  // 0x00196540
        const int32_t status = static_cast<int32_t>(m_GrdContDatasInOut.m_eContactStatus);
        const float dH = m_GrdContDatasInOut.m_fdH;
        if (status == 0) {
            m_v3Position.x = m_v3Position.x - dH;
            m_v3Position.y = m_v3Position.y - dH;
            m_v3Position.z = m_v3Position.z - dH;
        } else if (status > 0 && status <= 2) {
            m_v3Position.x = dH + m_v3Position.x;
            m_v3Position.z = dH + m_v3Position.z;
            m_v3Position.y = dH + m_v3Position.y;
        }
        return 0x25;
    }
    if (phase != 0) return 0x25;
    m_v3Position.y = ppc::fmadds(m_unk1fc, -3.0f, m_v3Position.y);  // TOC +0x11c8
    collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &m_v3Position.x, 1);
    if (m_GrdContDatasInOut.m_eContactStatus != 0) return 0x16;
    if (!(m_GrdContDatasInOut.m_fdH < 0.05f)) return 0x25;  // TOC +0x11d0
    return 0x16;
}

// 0x0029dde0 CKHkS08Enemy_State0x26_OnFireWait_maybe (vt+0x1d8): enter: the animation 0x32 (blend 0.5 for kind 6, else
// 0.1). Run: once the burning gauge (+0x6b8) is 0 or less it is zeroed, the burning ends (SetBurning(0)) and the state
// goes to 1. Leave: the gauge zeroed, the fire loop sound and the burning off. Else 0x26.
uint8_t CKHkS08Enemy::MainState26_OnFireWait(IKTime* /*clock*/, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        if (m_ui8EnemyClassType != 6) {
            RequestAnim(0x32, 0, 0, 0, 0.1f, 0.0f);  // 0x00285340; TOC +0x11a8 / +0x11ac
        } else {
            RequestAnim(0x32, 0, 0, 0, 0.5f, 0.0f);  // TOC +0x11a4
        }
        return 0x26;
    }
    if (phase == 2) {
        m_unk6b8 = 0.0f;
        SetFireLoopSoundActive(0);  // 0x002aeb48
        SetBurning(0);              // 0x002aec30
        return 0x26;
    }
    if (phase == 0 && m_unk6b8 <= 0.0f) {
        m_unk6b8 = 0.0f;
        SetBurning(0);  // 0x002aec30
        return 1;
    }
    return 0x26;
}

// 0x002a7eb0 CKHkS08Enemy_State27_Fall_maybe (vt+0x1dc): enter / leave: the velocity (+0x158) the zero vector. Run: the
// velocity gains the kind's gravity (dt / +0x1d0 of -(+0x1d0 x +0x1d4) in y; x and z add dt / +0x1d0 x 0), the
// position moves by dt x the velocity, then the ground probe: on the ground (1 / 2) the health loses the enemy group's
// fall damage (+0x274) and the position follows the ground; still alive on a ground without flag 0x200, or for the
// kinds 1 / 8: 1. Dead, or flagged ground, or fallen off (3): the health is 0, the kinds 5 / 6 enter the death reaction
// (0xf, no clock) and the state 2, the others 0x15. Else 0x27.
uint8_t CKHkS08Enemy::MainState27_Fall(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    if (phase == 1 || phase == 2) {
        m_unk158 = CVector3{0.0f, 0.0f, 0.0f};  // 0xc50d64 (TOC +0x1234)
        return 0x27;
    }
    if (phase != 0) return 0x27;
    const CKS08EnemyCpnt* cfg = m_unk884;
    const float g = cfg->m_unk1d0;
    const float t = clock->m_afDeltaTime[0] / g;
    const float side = t * 0.0f;  // TOC +0x11ac
    const float vx = m_unk158.x + side;
    const float vy = ppc::fmadds(-g * cfg->m_unk1d4, t, m_unk158.y);
    const float vz = side + m_unk158.z;
    m_unk158.x = vx;
    m_unk158.z = vz;
    m_unk158.y = vy;
    const float dt = clock->m_afDeltaTime[0];
    m_v3Position.x = ppc::fmadds(dt, vx, m_v3Position.x);
    m_v3Position.z = ppc::fmadds(dt, vz, m_v3Position.z);
    m_v3Position.y = ppc::fmadds(dt, vy, m_v3Position.y);
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);  // TOC +0x11cc -> +0x58
    collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &m_v3Position.x, 1);  // 0x00196540
    const int32_t status = static_cast<int32_t>(m_GrdContDatasInOut.m_eContactStatus);
    if (status < 1) return 0x27;
    if (status <= 2) {
        const float health = m_unk258 - static_cast<CKGrpS08Enemy*>(enemy::EnemyGroup())->m_unk268[3];  // 0x00276f58, +0x274
        m_unk258 = health;
        m_v3Position.y = m_v3Position.y + m_GrdContDatasInOut.m_fdH;
        if (!(health <= 0.0f)) {
            const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(m_GrdContDatasInOut.m_pGround);
            if ((ground->m_ui16PropertiesFlags & 0x200u) == 0 || m_ui8EnemyClassType == 1 || m_ui8EnemyClassType == 8) {
                return 1;
            }
        }
    } else if (status != 3) {
        return 0x27;
    }
    m_unk258 = 0.0f;
    if (static_cast<uint8_t>(m_ui8EnemyClassType - 5) > 1) return 0x15;
    SwitchReactState(0xf, nullptr);
    return 2;
}

// 0x0029dd38 CKHkS08Enemy_InitAuxStateMachine_maybe: 5 rows, no state.
void CKHkS08Enemy::InitAuxStateMachine() {
    m_aAuxStates[0][0] = 0x231;
    m_aAuxStates[1][0] = 0x235;
    m_aAuxStates[2][0] = 0x239;
    m_aAuxStates[3][0] = 0x23d;
    m_aAuxStates[4][0] = 0x241;
    m_aAuxStates[4][1] = 0;
    m_aAuxStates[0][1] = 0;
    m_aAuxStates[1][1] = 0;
    m_aAuxStates[2][1] = 0;
    m_aAuxStates[3][1] = 0;
    m_auxState = 0xff;
    m_auxStateCount = 5;
    m_pAuxStates = &m_aAuxStates[0][0];
}

// ---- State01's alerted stance (0x2a5028..0x2a6d3b, m_awareState == 2; notes: work/scratch-c27/st01-notes.md) ----

namespace {
const CVector3 kStanceNull{0.0f, 0.0f, 0.0f};   // 0x00c50d64 (TOC +0x1234)
const CVector3 kStanceAxisX{1.0f, 0.0f, 0.0f};  // 0x00c50d34 (TOC +0x1258)
const CVector3 kStanceAxisY{0.0f, 1.0f, 0.0f};  // 0x00c50d40 (TOC +0x11f0)
const CVector3 kStanceAxisZ{0.0f, 0.0f, 1.0f};  // 0x00c50d4c (TOC +0x1240)

// The original's inline normalise: 1 / length times each part, nothing for a null vector.
bool StanceNormalise(float& x, float& y, float& z) {
    const float length = std::sqrt(ppc::fmadds(z, z, ppc::fmadds(x, x, y * y)));  // Math_Sqrtf
    if (length == 0.0f) return false;  // TOC +0x11ac
    const float inverse = 1.0f / length;  // TOC +0x11bc
    z = inverse * z;
    x = inverse * x;
    y = inverse * y;
    return true;
}

float StanceRandUnit(uint32_t r) { return static_cast<float>(static_cast<double>(r & 0xffffu)); }
}  // namespace

// Steering_ComputeDesiredVelocity_maybe 0x2c4d38 (the ground kinds) and Steering_ComputeDesiredVelocity3D_maybe 0x2c1180
// (kinds 1 / 8): the yaw (+0x154) and velocity toward `target` along `direction` with the move component (cfg + 8), the
// ground (+0x70), the avoidance agent (+0x16c), the path finding (+0xbc), +0x397 and +0x398 (the 3D steering is not
// reached in the first fight: calls.jsonl has no call of 0x2c1180 / 0x2bf0d0 in fight / fight2 / fight3 / idle1500).
void CKHkS08Enemy::SteerGround(CVector3* position, float* yaw, CVector3* velocity, const CVector3* target,
                               const CVector3* direction, uint8_t keepPath) {
    // 0x002c4d38 with the kind's move component (+0x884 + 8), dt +0x1fc, the ground +0x70, the avoidance agent +0x16c,
    // the path finding +0xbc, the mode +0x397, no jump, and the static force on.
    m_unk884->m_MoveCpnt.Move(position, yaw, velocity, target, direction, &m_unk1fc, &m_GrdContDatasIn, &m_avoidance,
                              &m_PFCpnt, m_unk397, nullptr, keepPath, 1);
}
void CKHkS08Enemy::SteerFlying(CVector3* position, float* yaw, CVector3* velocity, const CVector3* target,
                               const CVector3* direction, uint8_t mode, uint8_t keepPath, uint8_t staticForce) {
    // 0x002c1180 with the kind's move component (+0x884 + 8), dt +0x1fc, the ground +0x70, the avoidance agent +0x16c,
    // the path finding +0xbc and no jump. State01 passes the mode +0x397 and the static force (keepPath 0, or +0x398
    // toward +0x37c), the attack states 0D / 0E mode 0 and nothing else.
    m_unk884->m_MoveCpnt.Move3D(position, yaw, velocity, target, direction, &m_unk1fc, &m_GrdContDatasIn, &m_avoidance,
                                &m_PFCpnt, mode, nullptr, keepPath, staticForce);
}

// The kind 1 wander (0x2a62d0 / 0x2a65a4): its timer (+0x798) counts down; at 0 a new heading (+0x79c: the Z axis turned
// about X by up to -pi and about Y by up to 2 pi, the two summed, normalised and scaled by the kind's +0x4a0 / +0x4a4)
// and a new time (+0x4a8 / +0x4ac), four rand draws; the smoothed point +0x7a8 approaches it (+0x4b0 per second) and
// moves the sector's animated node.
void CKHkS08Enemy::UpdateKind1Wander(IKTime* clock) {
    const float left = m_unk798 - clock->m_afDeltaTime[0];
    m_unk798 = left;
    if (left <= 0.0f) {
        m_unk79c = kStanceAxisZ.x;
        m_unk7a0 = kStanceAxisZ.y;
        m_unk7a4 = kStanceAxisZ.z;
        CVector3 v1 = kStanceAxisZ;
        CVector3 axis1 = kStanceAxisX;
        const float a1 = (StanceRandUnit(static_cast<uint32_t>(Rand_Int())) / -65535.0f) * 3.14159274f;  // TOC +0x125c, +0x124c
        CVector3 out1;
        Vec3_RotateTowardByAngle(&out1, &v1, &axis1, a1);  // 0x005841a8
        CVector3 v2{m_unk79c, m_unk7a0, m_unk7a4};
        CVector3 axis2 = kStanceAxisY;
        float f = StanceRandUnit(static_cast<uint32_t>(Rand_Int())) / 65535.0f;  // TOC +0x11c4
        CVector3 out2;
        Vec3_RotateTowardByAngle(&out2, &v2, &axis2, (f + f) * 3.14159274f);
        m_unk7a0 = out1.y + out2.y;
        m_unk79c = out1.x + out2.x;
        m_unk7a4 = out1.z + out2.z;
        StanceNormalise(m_unk79c, m_unk7a0, m_unk7a4);
        CKS08EnemyCpnt* cfg = m_unk884;
        const float base = cfg->m_unk4a0;
        float s = static_cast<float>(StanceRandUnit(static_cast<uint32_t>(Rand_Int())));
        cfg = m_unk884;
        const float k = -3.05180438e-05f;  // TOC +0x1260
        s = ppc::fmadds(ppc::fmadds(s, k, 1.0f), cfg->m_unk4a4, base);
        m_unk7a4 = s * m_unk7a4;
        m_unk79c = s * m_unk79c;
        m_unk7a0 = s * m_unk7a0;
        const float timeBase = m_unk884->m_unk4a8;
        const float t = StanceRandUnit(static_cast<uint32_t>(Rand_Int()));
        m_unk798 = ppc::fmadds(ppc::fmadds(t, k, 1.0f), m_unk884->m_unk4ac, timeBase);
    }
    // 0x2a62f4: +0x7a8 toward +0x79c.
    float x = m_unk7a8, y = m_unk7ac, z = m_unk7b0;
    if (x != m_unk79c || y != m_unk7a0 || z != m_unk7a4) {
        const float dy = m_unk7a0 - y;
        const float dx = m_unk79c - x;
        const float step = m_unk884->m_unk4b0 * m_unk1fc;
        const float dz = m_unk7a4 - z;
        const float length2 = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
        if (step * step > length2) {
            x = m_unk79c;
            y = m_unk7a0;
            z = m_unk7a4;
        } else {
            const float k = step * rwInvSqrt(length2);  // Math_InvSqrtf 0x114d8 (_rwInvSqrt)
            z = ppc::fmadds(dz, k, z);
            x = ppc::fmadds(dx, k, x);
            y = ppc::fmadds(dy, k, y);
        }
    }
    m_unk7a8 = x;
    m_unk7ac = y;
    m_unk7b0 = z;
    RwFrame* frame = static_cast<CSGMovable*>(m_unk18C[GetSectorIndex()]->GetAnimatedNode(0))->m_pRwFrame;  // 0x002b3110
    frame->modelling.pos.z = z;
    frame->modelling.pos.x = x;
    frame->modelling.pos.y = y;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);  // 0x00010698
}

// 0x00413fe8 CKHkS08CrumblyZoneMultiState_GetTotalHealth_maybe: the parts' health summed (the +0x38 references' +0x08).
float CrumblyZoneTotalHealth(IKSerializable* zone) {
    return static_cast<CKHkS08CrumblyZoneMultiState*>(zone)->GetTotalHealth();
}

// The alerted stance. Returns the next state, or -1 for the stance's tail.
int32_t CKHkS08Enemy::AlertedStance(IKTime* clock) {
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);  // TOC +0x11cc -> +0x58
    auto probe = [this, collision](float* point) {
        collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, point, 1);  // 0x00196540
    };
    auto group = []() { return static_cast<CKGrpS08Enemy*>(g_pEngine->m_gameManager->m_unk04[0]); };  // GetEnemyGroup
    auto zoneCpnt = [this]() { return static_cast<CKGrpSquad*>(m_pGroupSquad)->GetFightZone()->m_pFightZoneCpnt; };
    auto isKind = [this](uint32_t key) { return m_unk330 != nullptr && m_unk330->IsKindOfClass(key) != 0; };
    auto targetLtm = [this]() -> const RwV3d& { return FrameLtm(static_cast<CSGMovable*>(m_unk330->m_pKGLObject)->m_pRwFrame)->pos; };
    auto ownAt = [this]() -> const RwV3d& { return static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame->modelling.at; };
    auto drawnThisFrame = [this]() {
        const CSGLeaf* node = static_cast<const CSGLeaf*>(m_unk18C[GetSectorIndex()]->GetAnimatedNode(0));  // 0x002b3110
        return node->m_ui16LastRenderedFrame == g_ui16RenderFrameCounter;  // TOC +0x11b8: 0x00c29694
    };
    auto groundFlags = [this]() -> uint16_t {
        return static_cast<const ICollisionMesh*>(m_GrdContDatasInOut.m_pGround)->m_ui16PropertiesFlags;
    };
    float yaw;
    yaw = m_unk154;  // +0x154 the yaw

    probe(&m_v3Position.x);
    // The pre-check for a move to a target (0x2a506c .. 0x2a5180).
    {
        bool evaluate = true;  // L50d0
        if (m_unk7b4 == 0) {
            CKS08EnemyCpnt* cfg = m_unk884;
            bool skip = false;
            if (m_unk344 < cfg->m_unk1b8 && (drawnThisFrame() || zoneCpnt()->m_unk04 == 5)) skip = true;
            if (!skip) {
                cfg = m_unk884;
                if (zoneCpnt()->m_unk04 == 5 || !(m_unk67c >= cfg->m_unk1c0) || m_GrdContDatasInOut.m_pGround == nullptr ||
                    (groundFlags() & 0x400u) != 0 || !(m_unk6c8 <= 0.0f) || m_unk7d8 < 0 ||
                    !(group()->m_unk1f0 >= 0.3f) || m_unk81a == 0 || (groundFlags() & 0x200u) != 0 ||  // TOC +0x1254
                    isKind(CKHkS08CrumblyZoneMultiState::kClassKey) || !(m_unk6c0 <= 0.0f)) {
                    skip = true;
                } else if (m_unk884->m_unk338 != 0 && zoneCpnt()->GetFirstNonNullRef4C() != nullptr &&
                           isKind(CKHkS08Hero::kClassKey)) {
                    const float* heroPosition = static_cast<CKHkS08Hero*>(static_cast<IKSerializable*>(m_unk330))->GetPositionPtr();
                    IKHook* reference = static_cast<IKHook*>(zoneCpnt()->GetFirstNonNullRef4C());
                    const RwV3d& at = FrameLtm(static_cast<CSGMovable*>(reference->m_pKGLObject)->m_pRwFrame)->pos;
                    const float dz = heroPosition[2] - at.z;
                    const float dx = heroPosition[0] - at.x;
                    if (!(ppc::fmadds(dx, dx, dz * dz) < zoneCpnt()->m_unk48)) skip = true;
                }
                if (!skip) evaluate = false;  // L50f8 directly
            }
        }
        bool move = !evaluate;
        if (evaluate) {
            const CKHkDetectorGroup* detectors = static_cast<const CKHkDetectorGroup*>(
                static_cast<CKGrpFightZone*>(static_cast<CKGrpSquad*>(m_pGroupSquad)->m_pParent)->m_pUnk30);  // squad +0x1c -> +0x30
            move = detectors->EvaluateConditions(&m_v3Position.x, 0) == 0;  // 0x005bda08
        }
        if (move) {
            const CVector3 target = ChooseMoveTarget();  // 0x002808e8
            m_unk85c = target.x;
            m_unk864 = target.z;
            m_unk860 = target.y;
            if (target.x != kStanceNull.x || target.y != kStanceNull.y || target.z != kStanceNull.z) {
                m_unk67c = m_unk67c - m_unk884->m_unk1c0;
                group()->m_unk1f0 = 0.0f;
                return 0x17;
            }
        }
    }

    // The attack on the target hero (0x2a54b0): only by the enemy that holds the hero's attack slot.
    bool otherTarget = true;  // L51cc's test applies
    if (isKind(CKHkS08Hero::kClassKey)) {
        CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(static_cast<IKSerializable*>(m_unk330));
        const uint32_t count = group()->m_unk154;
        for (uint32_t i = 0; i < count; ++i) {
            auto holderAt = [&group, i]() -> CKHkS08Enemy* {
                CKGrpS08Enemy* g = group();
                return i < g->m_vUnk164.m_ui32NbUsedElt ? static_cast<CKHkS08Enemy*>(g->m_vUnk164.m_pBlock[i]) : nullptr;
            };
            const CKHkS08Hero* held = static_cast<const CKHkS08Hero*>(holderAt()->GetTargetHero());  // 0x00289060
            if (held->GetDragonIndex() != hero->GetDragonIndex()) continue;  // 0x00361960
            CKHkS08Enemy* holder = holderAt();
            if (holder == this) {
                if (m_unk330 == nullptr) {
                    otherTarget = false;
                    goto L51cc;
                }
                if (isKind(CKHkS08Hero::kClassKey) &&
                    (group()->IsAttackCooldownOver(hero->GetDragonIndex()) != 0 || m_unk8b0 != 0)) {  // vt+0x178
                    const RwV3d& at = targetLtm();
                    const float dy = at.y - m_v3Position.y;
                    float dx = at.x - m_v3Position.x;
                    float dz = at.z - m_v3Position.z;
                    const float length = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
                    if (length != 0.0f) {
                        const float inverse = 1.0f / length;
                        dz = dz * inverse;
                        dx = dx * inverse;
                    }
                    CKS08EnemyAttack* attack = m_unk73c;
                    if (attack != nullptr && attack->m_unk10 <= m_unk344 && attack->m_unk14 >= m_unk344 &&
                        (m_bitArray & 0x10000u) != 0 &&
                        ((attack->m_unk08 != 2 && attack->m_unk08 != 1) || drawnThisFrame())) {
                        CVector3 direction{dx, 0.0f, dz};
                        CVector3 facing{ownAt().x, ownAt().y, ownAt().z};
                        const float angle = AngleBetween(&direction, &facing);  // 0x0027eb88
                        if (angle < m_unk73c->m_unk60 && isKind(CKHkS08Hero::kClassKey)) {
                            CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
                            if (static_cast<double>(manager->GetDragonHealth(0)) > 0.0 &&
                                static_cast<double>(manager->GetDragonHealth(1)) > 0.0) {  // 0x004fd9c8
                                return 0xd;  // the attack windup
                            }
                        }
                    }
                    // L5750: to the back of the attackers.
                    group()->MoveAttackerToBack(this);  // vt+0x180
                    holder->m_bitArray = (holder->m_bitArray & ~0x20000u) | 0x20000u;
                    goto L51cc;
                }
            }
            break;
        }
    }
L51cc:
    if (otherTarget && m_unk330 != nullptr && m_unk330->IsKindOfClass(CKHkS08Hero::kClassKey) == 0) {
        // A crumbly zone (0x3582) or another enemy (0x26c2) as the target.
        const RwV3d& at = targetLtm();
        const float dy = at.y - m_v3Position.y;
        float dx = at.x - m_v3Position.x;
        float dz = at.z - m_v3Position.z;
        const float length = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            dz = dz * inverse;
            dx = dx * inverse;
        }
        auto inRange = [this]() {
            const CKS08EnemyAttack* attack = m_unk73c;
            return attack != nullptr && attack->m_unk10 <= m_unk344 && attack->m_unk14 >= m_unk344;
        };
        if (m_unk330->IsKindOfClass(CKHkS08CrumblyZoneMultiState::kClassKey) != 0 && inRange() &&
            (m_bitArray & 0x10000u) != 0) {
            CVector3 direction{dx, 0.0f, dz};
            CVector3 facing{ownAt().x, ownAt().y, ownAt().z};
            const float angle = AngleBetween(&direction, &facing);
            if (angle < m_unk73c->m_unk60 && 0.0f < CrumblyZoneTotalHealth(m_unk330)) return 0xd;  // 0x00413fe8
        }
        if (m_unk330->IsKindOfClass(CKHkS08Enemy::kClassKey) != 0 && inRange()) {
            CVector3 direction{dx, 0.0f, dz};
            CVector3 facing{ownAt().x, ownAt().y, ownAt().z};
            const float angle = AngleBetween(&direction, &facing);
            if (angle < m_unk73c->m_unk60 && 0.0f < static_cast<CKHkS08Enemy*>(static_cast<IKSerializable*>(m_unk330))->m_unk258 &&
                (m_bitArray & 0x10000u) != 0) {
                return 0xd;
            }
        }
        m_bitArray = (m_bitArray & ~0x20000u) | 0x20000u;
    }
    // The dodge (0x2a520c): the hero attacking in a combo, the enemy facing the move direction, a hero hit sphere close.
    {
        CKS08EnemyCpnt* cfg = m_unk884;
        if ((cfg->m_unk1f8 != 0 || cfg->m_unk1f9 != 0) && cfg->m_unk220 <= m_unk6b0 && isKind(CKHkS08Hero::kClassKey) &&
            static_cast<CKHkS08Hero*>(static_cast<IKSerializable*>(m_unk330))->IsInCombo() != 0) {  // 0x0032a698
            CVector3 direction{m_unk388, m_unk38c, m_unk390};
            CVector3 facing{ownAt().x, ownAt().y, ownAt().z};
            const float angle = AngleBetween(&direction, &facing);
            if (angle <= m_unk884->m_unk200) {
                CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(static_cast<IKSerializable*>(m_unk330));
                uint32_t count = hero->m_unk1bac;  // 0x00329de0 CKHkS08Hero_GetActiveHitSpheres: +0x1b9c, the count +0x1bac
                if (count > 4) count = 4;
                IKSerializable* const* spheres = reinterpret_cast<IKSerializable* const*>(hero->m_apActiveHitSpheres);
                const float reach = m_unk884->m_unk204;
                for (uint32_t i = 0; i < count; ++i) {
                    const RwV3d& at = FrameLtm(static_cast<CSGMovable*>(spheres[i])->m_pRwFrame)->pos;  // +4 -> +0x80
                    const float dz = at.z - m_v3Position.z;
                    const float dx = at.x - m_v3Position.x;
                    if (ppc::fmadds(dx, dx, dz * dz) <= reach) return 6;  // the dodge
                }
            }
        }
    }
    // The carried transportable (0x2a5280): the carrier's vt+0x58 accepts it -> go to it.
    if (m_unk738 != nullptr && CarrierAcceptsTransportable(m_unk738) != 0) {
        const RwV3d& at = FrameLtm(static_cast<CSGMovable*>(static_cast<IKHook*>(m_unk738)->m_pKGLObject)->m_pRwFrame)->pos;
        m_unk380 = at.y;
        m_unk384 = at.z;
        m_unk37c = at.x;
        m_unk390 = at.z - m_v3Position.z;
        m_unk388 = at.x - m_v3Position.x;
        m_unk38c = 0.0f;
        StanceNormalise(m_unk388, m_unk38c, m_unk390);
        CVector3 target{m_unk37c, m_unk380, m_unk384};
        CVector3 direction{m_unk388, m_unk38c, m_unk390};
        SteerGround(&m_v3Position, &yaw, &m_unk158, &target, &direction, m_unk398);
        m_unk154 = yaw;
        return -1;
    }
    if ((m_bitArray & 0x40000u) != 0) {
        // The approach of the attack target (0x2a52d4).
        if (m_ui8EnemyClassType != 1 && m_ui8EnemyClassType != 8) {
            const RwV3d& at = targetLtm();
            float x = at.x - m_v3Position.x;
            float y = 0.0f;
            float z = at.z - m_v3Position.z;
            StanceNormalise(x, y, z);
            CVector3 direction{x, y, z};
            CVector3 target = m_unk338;
            if (m_unk6d0 <= 0.0f) {
                SteerGround(&m_v3Position, &yaw, &m_unk158, &target, &direction, 0);  // 0x2a6574
            } else {
                float yawCopy = yaw;
                const float f = 1.0f - m_unk6d0 / m_unk884->m_unk25c;
                CVector3 scaled{m_unk158.x * f, m_unk158.y * f, m_unk158.z * f};
                CVector3 positionCopy = m_v3Position;
                SteerGround(&m_v3Position, &yaw, &scaled, &target, &direction, 0);  // 0x2a5458
                SteerGround(&positionCopy, &yawCopy, &m_unk158, &target, &direction, 0);  // 0x2a54a4
            }
            m_unk154 = yaw;
            return -1;
        }
        const RwV3d& at = targetLtm();
        float y = at.y - m_v3Position.y;
        float x = at.x - m_v3Position.x;
        float z = at.z - m_v3Position.z;
        StanceNormalise(x, y, z);
        if (m_ui8EnemyClassType == 1) UpdateKind1Wander(clock);
        CVector3 direction{x, y, z};
        CVector3 target = m_unk338;
        SteerFlying(&m_v3Position, &yaw, &m_unk158, &target, &direction, m_unk397, 0, 1);  // 0x002c1180 (0x2a5df0)
        m_unk154 = yaw;
    } else {
        // The stance movement (0x2a5a90).
        if (m_reactState != 0 || m_unk239 != 0) return -1;
        if (m_ui8EnemyClassType != 1 && m_ui8EnemyClassType != 8) {
            m_unk38c = 0.0f;
            StanceNormalise(m_unk388, m_unk38c, m_unk390);
            CVector3 velocity = m_unk158;
            if (m_unk6d0 > 0.0f) {
                const float f = 1.0f - m_unk6d0 / m_unk884->m_unk25c;
                velocity.z = velocity.z * f;
                velocity.x = velocity.x * f;
                velocity.y = velocity.y * f;
            }
            CVector3 target{m_unk37c, m_unk380, m_unk384};
            CVector3 direction{m_unk388, m_unk38c, m_unk390};
            SteerGround(&m_v3Position, &yaw, &velocity, &target, &direction, m_unk398);  // 0x2a5be4
            m_unk154 = yaw;
            // The approach point is dropped once within 1 of it.
            if (!(m_unk83c == kStanceNull.x && m_unk840 == kStanceNull.y && m_unk844 == kStanceNull.z)) {
                const float dz = m_v3Position.z - m_unk844;
                const float dx = m_v3Position.x - m_unk83c;
                if (ppc::fmadds(dx, dx, dz * dz) <= 1.0f) {
                    m_unk83c = kStanceNull.x;
                    m_unk840 = kStanceNull.y;
                    m_unk844 = kStanceNull.z;
                }
            }
            if (m_unk6d0 <= 0.0f) m_unk158 = velocity;
            return -1;
        }
        StanceNormalise(m_unk388, m_unk38c, m_unk390);
        if (m_ui8EnemyClassType == 1) UpdateKind1Wander(clock);
        CVector3 target{m_unk37c, m_unk380, m_unk384};
        CVector3 direction{m_unk388, m_unk38c, m_unk390};
        SteerFlying(&m_v3Position, &yaw, &m_unk158, &target, &direction, m_unk397, m_unk398, 1);  // 0x002c1180 (0x2a64c4)
        m_unk154 = yaw;
    }
    // The flying kinds' ground (0x2a5df8): on a ground at least 0.2 below, +0x7b4 set.
    if (m_unk7b4 != 0) return -1;
    probe(&m_v3Position.x);
    if (m_GrdContDatasInOut.m_eContactStatus == 0 && m_GrdContDatasInOut.m_fdH > 0.2f) m_unk7b4 = 1;  // TOC +0x11c0
    return -1;
}

// CKS08CarrierEnemy_vf58 0x4c7780 (the carrier +0x734's vt+0x58 with the carried transportable).
uint8_t CKHkS08Enemy::CarrierAcceptsTransportable(IKSerializable* transportable) {
    return static_cast<CKS08CarrierEnemy*>(m_unk734)->CanPickUp(transportable);
}

// 0x0029e698 StaticInitAndDestruction_29e698: two file statics (0x00cead1c, 0x00cead20) set to -1.0f. Nothing in the game
// reads them (their only references are the initialiser's TOC entries).
namespace {
[[maybe_unused]] float s_unkcead1c = -1.0f;
[[maybe_unused]] float s_unkcead20 = -1.0f;
}  // namespace
