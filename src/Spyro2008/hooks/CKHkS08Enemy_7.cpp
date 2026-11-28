// Reconstructed original translation unit: 0x28b960-0x291478 (GAME_TOC1, main_toc1), 33 functions, 26 live.
// Primary class: CKHkS08Enemy  key 0x26c2  category Hook  size 0x8f8  vtable 0xb22078
// Other owners: EnemyGroup (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x28b960  CKHkS08Enemy_SetAttackTrailActive_maybe
//   [x] 0x28bfc0  CKHkS08Enemy_UpdateShadowAndAuraFx_maybe
//   [x] 0x28c0a0  CKHkS08Enemy_SpawnHitFx
//   [x] 0x28c590  CKHkS08Enemy_SpawnHitFx_maybe  (in CKHkS08Enemy_12.cpp: SpawnHitFxAt)
//   [x] 0x28c838  CKHkS08Enemy_SetMeshPopFxActive_maybe
//   [x] 0x28cb88  CKHkS08Enemy_SetFreezeFxActive_maybe
//   [x] 0x28cec0  CKHkS08Enemy_SpawnShieldDropFx_maybe
//   [x] 0x28d1b8  CKHkS08Enemy_SetStunFxActive_maybe
//   [x] 0x28d4a8  CKHkS08Enemy_PlayFxAtHotspot1_maybe
//   [x] 0x28da80  CKHkS08Enemy_PlayFxOnAllHotspots_maybe
//   [ ] 0x28ddd0  KStub_Nop_28ddd0  [dead]
//   [ ] 0x28ddd8  CKHkS08Enemy_ScoreAttackTimingWindow_maybe  [dead]
//   [ ] 0x28dea8  CKHkS08Enemy_ScoreAttackTypeFlag_maybe  [dead]
//   [ ] 0x28df08  CKHkS08Enemy_ScoreAttackCooldown_maybe  [dead]
//   [ ] 0x28df68  CKHkS08Enemy_ScoreTargetCarryingKey_maybe  [dead: no pointer to its descriptor 0xb8e258, no call]
//   [ ] 0x28dfd8  CKHkS08Enemy_ScoreTargetOnMeca_maybe  [dead: no pointer to its descriptor 0xb8e260, no call]
//   [x] 0x28e048  CKHkS08Enemy_ScoreTargetCrowding_maybe
//   [ ] 0x28e1a8  CKHkS08Enemy_ScoreTargetIsPlayer_maybe  [dead: no pointer to its descriptor 0xb8e270, no call]
//   [ ] 0x28e218  CKHkS08Enemy_ScoreTargetProximity_maybe  [dead: no pointer to its descriptor 0xb8e278, no call]
//   [ ] 0x28e2d0  EnemyGroup_CountEngagedWithRole_maybe  [dead: no pointer to its descriptor 0xb8e280, no call]
//   [ ] 0x28e3a8  CKHkS08Enemy_ScoreAttackGroundProbeKind3_maybe  [dead]
//   [ ] 0x28e4c0  CKHkS08Enemy_ScoreAttackGroundProbeKind2_maybe  [dead]
//   [ ] 0x28e5f0  CKHkS08Enemy_ScoreAttackGroundProbeKind1_maybe  [dead]
//   [x] 0x28e708  StaticInitAndDestruction_28e708  (the two file statics at the end)
//   [ ] 0x28e738  _GLOBAL__D_28e738
//   [ ] 0x28e748  _GLOBAL__I_28e748
//   [x] 0x28e758  CKHkS08Enemy_ScoreAttack
//   [x] 0x28ed10  CKHkS08Enemy_SelectAttack
//   [x] 0x28f090  CKHkS08Enemy_ScoreHeroTarget_maybe
//   [x] 0x28f290  CKHkS08Enemy_SelectTarget
//   [x] 0x28f928  CKHkS08Enemy_UpdateBehaviourMode
//   [x] 0x28fcd0  CKHkS08Enemy_UpdateTargetingAndAwareness_maybe
//   [x] 0x290338  CKHkS08Enemy_UpdateMoveDestination_maybe
#include "Spyro2008/hooks/CKHkS08Enemy.h"

#include "k2000/core/Stub.h"

#include <cmath>
#include <cstdint>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/components/CKS08EnemyCpnt.h"
#include "Spyro2008/components/CKS08FightZoneCpnt.h"
#include "Spyro2008/groups/CKGrpS08Enemy.h"
#include "Spyro2008/hooks/CKHkS08EnemyShared.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "k2000/groups/CKGrpFightZone.h"
#include "k2000/groups/CKGrpSquad.h"
#include "crt/ppc_ops.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/hooks/CKHkS08CrumblyZoneMultiState.h"
#include "Spyro2008/logic/CKS08EnemyAttack.h"
#include "k2000/components/CKEnemySectorCpnt.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/render/CRenderer.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/ICollisionMesh.h"
#include "k2000/ai/CKSrvPathFinding.h"
#include "k2000/math/Math.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/misc/Mat4.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/render/CKMeshPopFxData.h"
#include "k2000/logic/render/CKMeshPopNodeFx.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/fx/CKSparkFxData.h"
#include "k2000/fx/IKFx.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/logic/fx/CKSparkNodeFx.h"
#include "k2000/misc/Engine.h"
#include "Spyro2008/components/CKS08EnemyCpnt.h"
#include "k2000/components/CKEnemySectorCpnt.h"

// 0x0028bfc0 CKHkS08Enemy_UpdateShadowAndAuraFx_maybe (vt+0x140): the shadow caster updated (vt+0xe4) unless grabbed, or
// hidden (+0x7c4 clear in states 0 / 0x17 / 0x18 / 0x16): then unregistered; kind 7's hot spot particles while shown.
void CKHkS08Enemy::UpdateShadowAndAuraFx() {
    bool unregister = m_pGrabbingHero != 0;
    if (!unregister && m_unk7c4 == 0) {
        const uint8_t state = m_mainState;
        unregister = state == 0 || state == 0x17 || state == 0x18 || state == 0x16;
    }
    if (unregister) {
        UnregisterShadowCaster();  // 0x002773e0
    } else {
        UpdateShadowCaster();  // vt+0xe4
    }
    if (m_ui8EnemyClassType == 7 && (static_cast<CSGLeaf*>(m_pKGLObject)->m_sgProperties & 4u) == 0) {
        EmitKind7HotspotParticles();  // 0x0028b500 (tail call)
    }
}

// 0x0028fcd0 CKHkS08Enemy_UpdateTargetingAndAwareness_maybe: the stance target (+0x37c: the spawn place, or the position
// while the enemy group's +0x1bc is set) and direction (+0x388) reset, the target chosen (SelectTarget; a dying enemy
// keeps its target and only measures it), an enemy with +0x709 locks on the nearest other active enemy, the direction to
// the target flattened, the awareness machine ticked (not in states 0 / 0x16), and an enemy with an attack slot (+0x891)
// on a hero moves the slot's first holder of that hero to the back.
void CKHkS08Enemy::UpdateTargetingAndAwareness(IKTime* clock) {
    CKGrpS08Enemy* group = static_cast<CKGrpS08Enemy*>(g_pEngine->m_gameManager->m_unk04[0]);  // GetEnemyGroup 0x276f58
    if (group->m_bAlerted == 0) {
        m_unk37c = m_unk1c4;
        m_unk380 = m_unk1c8;
        m_unk384 = m_unk1cc;
    } else {
        m_unk37c = m_v3Position.x;
        m_unk384 = m_v3Position.z;
        m_unk380 = m_v3Position.y;
    }
    m_unk388 = m_unk1d0;
    m_unk390 = m_unk1d8;
    m_unk38c = m_unk1d4;
    uint32_t bits1f0;  // +0x1f0 read as a word (lwz)
    std::memcpy(&bits1f0, &m_unk1f0, sizeof(bits1f0));
    // The original stores a word at +0x394 (stw): its three high bytes 0, the low one (+0x397, the move mode
    // SteerGround passes) the value.
    m_unk394 = 0;
    m_unk395 = 0;
    m_unk396 = 0;
    m_unk397 = static_cast<uint8_t>(bits1f0 & 3u);
    m_unk398 = m_unk1ed;
    const float kFar = 3.40282347e+38f;  // 0x00c4ace0 (TOC +0xf2c, +0x28): FLT_MAX
    float best = kFar;
    if ((IsInDeathStates() & 0xffu) != 0) {  // 0x0027ce50
        const RwV3d& hero = FrameLtm(static_cast<CSGMovable*>(static_cast<IKHook*>(m_pTarget)->m_pKGLObject)->m_pRwFrame)->pos;
        const float dz = m_v3Position.z - hero.z;
        const float dx = m_v3Position.x - hero.x;
        m_unk344 = std::sqrt(ppc::fmadds(dx, dx, dz * dz));
    } else {
        SelectTarget();  // 0x0028f290
    }
    if (m_unk709 != 0) {
        const uint32_t active = group->m_ui32NbActiveEnemies;
        for (uint32_t i = 0; i < active; ++i) {
            CKHkS08Enemy* other = static_cast<CKHkS08Enemy*>(group->m_apActiveEnemies[i]);  // +0x58 the active enemies
            if (other != this) {
                const float dz = m_v3Position.z - other->m_v3Position.z;
                const float dx = m_v3Position.x - other->m_v3Position.x;
                const float d = ppc::fmadds(dx, dx, dz * dz);
                if (d < best) {
                    best = d;
                    m_pTarget = other;
                }
            }
            m_unk344 = best == kFar ? best : std::sqrt(best);
        }
    }
    if (m_pTarget != nullptr) {
        const RwV3d& target = FrameLtm(static_cast<CSGMovable*>(static_cast<IKHook*>(m_pTarget)->m_pKGLObject)->m_pRwFrame)->pos;
        const float dx = target.x - m_v3Position.x;
        const float dz = target.z - m_v3Position.z;
        m_unk38c = target.y - m_v3Position.y;
        m_unk38c = 0.0f;  // TOC +0xee8
        m_unk388 = dx;
        m_unk390 = dz;
        const float length = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, m_unk38c * m_unk38c)));
        if (length != 0.0f) {
            const float k = 1.0f / length;  // TOC +0xee4
            m_unk390 = k * m_unk390;
            m_unk388 = k * m_unk388;
            m_unk38c = k * m_unk38c;
        }
    }
    if (m_mainState != 0 && m_mainState != 0x16) {
        const uint8_t state = m_awareState;
        if (state != 0xff) {
            const uint8_t next = CallAwareState(state, clock, 0, state);
            const uint8_t old = m_awareState;
            if (next != old) {
                if (old != 0xff) CallAwareState(old, clock, 2, next);
                m_awareState = next;
                if (next != 0xff) CallAwareState(next, clock, 1, old);
            }
        }
    }
    if (m_unk891 != 0 && m_pTarget != nullptr && m_pTarget->IsKindOfClass(0x25c2) != 0) {
        // The attack slots (+0x154 the count, +0x164 the holders): the first holder targeting the same dragon is this
        // enemy, not in state 1 -> it goes to the back of the holders and gets the life flag 0x20000.
        const uint8_t dragon = static_cast<CKHkS08Hero*>(m_pTarget)->GetDragonIndex();  // 0x00361960
        CKGrpS08Enemy* group = static_cast<CKGrpS08Enemy*>(enemy::EnemyGroup());
        const uint32_t count = group->m_ui32ReservedAttackSlotsTotal;
        for (uint32_t i = 0; i < count; ++i) {
            const TVector<IKSerializable*, 1>& holders = static_cast<CKGrpS08Enemy*>(enemy::EnemyGroup())->m_vUnk164;
            CKHkS08Enemy* holder = i < holders.m_ui32NbUsedElt ? static_cast<CKHkS08Enemy*>(holders.m_pBlock[i]) : nullptr;
            if (holder == nullptr || holder->GetTargetHero() == nullptr) continue;  // DOTD: the original reads through null
            if (static_cast<CKHkS08Hero*>(holder->GetTargetHero())->GetDragonIndex() != dragon) continue;  // 0x00289060
            const TVector<IKSerializable*, 1>& again = static_cast<CKGrpS08Enemy*>(enemy::EnemyGroup())->m_vUnk164;
            IKSerializable* first = i < again.m_ui32NbUsedElt ? again.m_pBlock[i] : nullptr;
            if (first != this) return;
            if (m_mainState == 1) return;  // DOTD: the +0x39c machine's state (the enemy-fighting branch reuses the register)
            static_cast<CKGrpS08Enemy*>(enemy::EnemyGroup())->MoveAttackerToBack(first);  // vt+0x180
            m_bitArray = (m_bitArray & ~0x20000u) | 0x20000u;
            return;
        }
    }
}

// 0x0028f290 CKHkS08Enemy_SelectTarget: an enemy that fights enemies (+0x709) takes the nearest other active enemy (its
// node's modelling position, xz) and is done; otherwise the heroes are scored (ScoreHeroTarget, from the last index
// down: a higher score wins, a tie keeps the current target) with the attack slots' counts per dragon, the distance to
// the winner kept (+0x344, FLT_MAX for none) and the previous target in +0x830; a mode 5 fight zone's crumbly zones may
// take over (the least targeted live one); a hero target after a 0x3582 one clears the slot reservation (+0x7d8).
void CKHkS08Enemy::SelectTarget() {
    CKGrpS08Enemy* group = static_cast<CKGrpS08Enemy*>(g_pEngine->m_gameManager->m_unk04[0]);  // GetEnemyGroup 0x276f58
    const float kFar = 3.40282347e+38f;  // 0x00c4ace0 (TOC +0xf2c, +0x28): FLT_MAX
    if (m_unk709 != 0) {
        if (m_unk891 != 0) {
            static_cast<CKGrpS08Enemy*>(enemy::EnemyGroup())->ReleaseAttackSlot(m_unk7d8, this);  // 0x00267138
            m_unk7d8 = -1;
            m_unk891 = 0;
        }
        const uint32_t count = group->m_ui32NbActiveEnemies;
        float best = kFar;
        m_pTarget = nullptr;
        for (uint32_t i = 0; i < count; ++i) {
            IKHook* other = static_cast<IKHook*>(group->m_apActiveEnemies[i]);
            const RwFrame* frame = static_cast<const CSGMovable*>(other->m_pKGLObject)->m_pRwFrame;
            if (other == this) continue;
            const float dz = frame->modelling.pos.z - m_v3Position.z;
            const float dx = frame->modelling.pos.x - m_v3Position.x;
            const float d = ppc::fmadds(dx, dx, dz * dz);
            if (best > d) {
                best = d;
                m_pTarget = other;
            }
        }
        if (m_pTarget != nullptr) return;
    }
    // The attack slots' holders that target a hero, per dragon (r18: dragon 0, r19: the others).
    uint32_t dragon0 = 0;
    uint32_t dragon1 = 0;
    const uint32_t slots = group->m_ui32ReservedAttackSlotsTotal;
    for (uint32_t i = 0; i < slots; ++i) {
        IKSerializable* holder = i < group->m_vUnk164.m_ui32NbUsedElt ? group->m_vUnk164.m_pBlock[i] : nullptr;
        if (holder == this) continue;
        CKHkS08Enemy* enemy = static_cast<CKHkS08Enemy*>(holder);
        if (enemy->GetTargetHero() == nullptr) continue;  // 0x00289060
        if (static_cast<CKHkS08Hero*>(enemy->GetTargetHero())->GetDragonIndex() == 0) {
            ++dragon0;
        } else {
            ++dragon1;
        }
    }
    CKS08FightZoneCpnt* zone = static_cast<CKGrpFightZone*>(static_cast<CKGrpSquad*>(m_pGroupSquad)->m_pParent)->m_pFightZoneCpnt;
    // Fight zone mode 5: per crumbly zone of the component (+0x98), the other active enemies that target it (a stack
    // array of 66 words; BUG(original): more zones overrun it, none of DotD's zones has that many).
    const uint32_t crumblies = zone->m_vUnk98.m_ui32NbUsedElt;
    uint32_t targeting[66];
    if (zone->m_unk04 == 5) {
        for (uint32_t i = 0; i < crumblies; ++i) targeting[i] = 0;
        CKGrpS08Enemy* enemies = static_cast<CKGrpS08Enemy*>(enemy::EnemyGroup());
        for (uint32_t e = 0; e < enemies->m_ui32NbActiveEnemies; ++e) {
            const CKHkS08Enemy* other = static_cast<const CKHkS08Enemy*>(enemies->m_apActiveEnemies[e]);
            if (other == this || crumblies == 0) continue;
            for (uint32_t i = 0; i < crumblies; ++i) {
                if (zone->m_vUnk98.m_pBlock[i] == other->GetTargetRaw()) ++targeting[i];  // 0x002890f0
            }
        }
    }
    IKGrpHero* heroes = static_cast<IKGrpHero*>(g_pEngine->m_gameManager->m_unk04[1]);  // GetHeroGroup 0x276f70
    float best = -1.0f;  // TOC +0xf0c
    IKSerializable* pick = nullptr;
    for (int32_t i = static_cast<int32_t>(heroes->GetHeroCount()) - 1; i != -1; --i) {  // 0x002ca038
        IKSerializable* hero = heroes->m_apHeros[i];  // GetHeroByDragonIndex 0x002ca080
        const float score = ScoreHeroTarget(static_cast<uint32_t>(i), dragon0, dragon1);
        if (best != score) {
            if (best >= score) continue;
        } else if (m_pTarget == nullptr || m_pTarget != hero) {
            continue;
        }
        best = score;
        pick = hero;
    }
    IKSerializable* previous = m_pTarget;
    if (pick == nullptr) {
        m_unk344 = kFar;
    } else {
        const float* position = static_cast<CKHkS08Hero*>(pick)->GetPositionPtr();  // 0x00361968
        const float dx = m_v3Position.x - position[0];
        const float dz = m_v3Position.z - position[2];
        m_unk344 = std::sqrt(ppc::fmadds(dx, dx, dz * dz));  // Math_Sqrtf 0x10690
    }
    m_pTarget = static_cast<IKHook*>(pick);
    m_unk830 = previous;
    if (zone->m_unk04 == 5 && crumblies != 0) {
        // The last live crumbly zone (health above 0, its current state's +0xc0 byte set) whose targeting count is at most
        // the larger hero count, and then at most the count of the previous such zone, becomes the target.
        uint32_t limit = dragon1 < dragon0 ? dragon0 : dragon1;
        int32_t chosen = -1;
        for (uint32_t i = 0; i < crumblies; ++i) {
            if (targeting[i] > limit) continue;
            const CKHkS08CrumblyZoneMultiState* crumbly = static_cast<CKHkS08CrumblyZoneMultiState*>(zone->m_vUnk98.m_pBlock[i]);
            if (crumbly->GetTotalHealth() <= 0.0f) continue;  // 0x00413fe8, TOC +0xee8 (ble: a NaN is taken)
            if (crumbly->m_vUnkC0.m_pBlock[crumbly->m_ui32CurrentState] == 0) continue;
            chosen = static_cast<int32_t>(i);
            limit = targeting[i];
        }
        if (chosen >= 0) {
            if (m_unk891 != 0) {
                static_cast<CKGrpS08Enemy*>(enemy::EnemyGroup())->ReleaseAttackSlot(m_unk7d8, this);  // 0x00267138
                m_unk891 = 0;
            }
            IKHook* crumbly = static_cast<IKHook*>(zone->m_vUnk98.m_pBlock[chosen]);
            m_pTarget = crumbly;
            const RwV3d& at = FrameLtm(static_cast<CSGMovable*>(crumbly->m_pKGLObject)->m_pRwFrame)->pos;
            const float dz = m_v3Position.z - at.z;
            const float dx = m_v3Position.x - at.x;
            m_unk344 = std::sqrt(ppc::fmadds(dx, dx, dz * dz));  // Math_Sqrtf 0x10690
        }
    }
    if (m_unk830 != nullptr && m_unk830->IsKindOfClass(0x3582) != 0 && m_pTarget != nullptr &&
        m_pTarget->IsKindOfClass(0x25c2) != 0) {
        m_unk7d8 = -1;
    }
}

// 0x0028f090 CKHkS08Enemy_ScoreHeroTarget_maybe: (player-controlled: +0x4c0) + (within +0x4d8: (1 - d2 / r2) x
// +0x4c4) + the crowding score, then + (attached to a meca: +0x4cc), then + (carrying the key: +0x4d0).
float CKHkS08Enemy::ScoreHeroTarget(uint32_t dragon, uint32_t dragon0, uint32_t dragon1) {
    IKGrpHero* heroes = static_cast<IKGrpHero*>(g_pEngine->m_gameManager->m_unk04[1]);
    const uint8_t index = static_cast<uint8_t>(dragon);
    CKS08EnemyCpnt* cfg = m_pActiveEnemyCpnt;
    CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(heroes->m_apHeros[index]);  // 0x002ca080
    const float player = hero->IsPlayerControlled() != 0 ? cfg->m_unk4c0 : 0.0f;  // TOC +0xee8 0.0f
    const float* position = hero->GetPositionPtr();
    const float dx = m_v3Position.x - position[0];
    const float dz = m_v3Position.z - position[2];
    const float range = cfg->m_unk4d8 * cfg->m_unk4d8;
    const float d2 = ppc::fmadds(dx, dx, dz * dz);
    float near = 0.0f;
    if (d2 <= range) near = (1.0f - d2 / range) * cfg->m_unk4c4;  // TOC +0xee4 1.0f
    const float crowd = ScoreTargetCrowding(dragon, dragon0, dragon1);
    const float meca = hero->IsAttachedToContextualMeca() != 0 ? cfg->m_unk4cc : 0.0f;
    const float key = hero->IsCarryingTransportableKey() != 0 ? cfg->m_unk4d0 : 0.0f;
    float score = player + near;
    score = score + crowd;
    score = meca + score;
    return key + score;
}

// 0x0028e048 CKHkS08Enemy_ScoreTargetCrowding_maybe: (1 - holders / +0x4dc) x +0x4c8 for the hero's dragon's count of
// attack slot holders (dragon 0: `dragon0`, else `dragon1`); 0 x +0x4c8 above the limit or with no limit.
float CKHkS08Enemy::ScoreTargetCrowding(uint32_t dragon, uint32_t dragon0, uint32_t dragon1) {
    IKGrpHero* heroes = static_cast<IKGrpHero*>(g_pEngine->m_gameManager->m_unk04[1]);
    CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(heroes->m_apHeros[static_cast<uint8_t>(dragon)]);  // 0x002ca080
    CKS08EnemyCpnt* cfg = m_pActiveEnemyCpnt;
    const uint32_t count = hero->GetDragonIndex() == 0 ? dragon0 : dragon1;
    const uint32_t limit = cfg->m_unk4dc;
    float value = 0.0f;  // TOC +0xee8
    if (count <= limit && limit != 0) {
        value = 1.0f - static_cast<float>(static_cast<double>(count)) / static_cast<float>(static_cast<double>(limit));
    }
    return value * cfg->m_unk4c8;
}

// 0x00290338 CKHkS08Enemy_UpdateMoveDestination_maybe: the move target +0x37c, its direction +0x388 and the attack
// choice of an enemy. Idle or without a fight: the spawn point's target and direction (+0x1c4 / +0x1d0), the ground
// test of +0x7b4. Alerted (+0x538 == 2): the behaviour mode, the attack selection (SelectAttack), the attack's range
// test (+0x344 within [+0x10, +0x14], or a rand draw against the kind's +0x558), the approach point, the target hero's
// ground, the flying kinds' spot near the hero, the attack's facing test (+0x60) that sets +0xc bit 16. The labels
// are the original's addresses (work/scratch-c27/umd-notes.md).
void CKHkS08Enemy::UpdateMoveDestination(IKTime* clock) {
    if ((m_bitArray & 0x400u) != 0) return;
    if (GetCurrentAnim(0, 0) == 0x3a) return;  // 0x00285408
    CKS08FightZoneCpnt* zone = static_cast<CKGrpSquad*>(m_pGroupSquad)->GetFightZone()->m_pFightZoneCpnt;  // 0x0025ab50
    CKGrpS08Enemy* group = nullptr;
    CKS08EnemyCpnt* cfg = nullptr;
    CKS08EnemyAttack* attack = nullptr;
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);  // TOC +0xf00 -> +0x58
    const CVector3 kNull{0.0f, 0.0f, 0.0f};  // TOC +0xf40: 0x00c50d64
    CVector3 targetPoint;  // sp+0x94: the target hero's frame position
    uint8_t picked = 0;    // r27
    auto isHero = [this]() { return m_pTarget != nullptr && m_pTarget->IsKindOfClass(CKHkS08Hero::kClassKey) != 0; };
    auto isCrumbly = [this]() {
        return m_pTarget != nullptr && m_pTarget->IsKindOfClass(CKHkS08CrumblyZoneMultiState::kClassKey) != 0;
    };
    auto heroGroupBlocked = []() {
        const CKGrpS08Hero* heroes = static_cast<const CKGrpS08Hero*>(g_pEngine->m_gameManager->m_unk04[1]);  // gm +8
        return ((heroes->m_baWorkFlags >> 3) & 1u) != 0;  // 0x002ca258 CKGrpS08Hero_IsInputBlocked_maybe
    };
    auto probe = [this, collision](CVector3* point) {
        collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &point->x, 1);  // 0x00196540
    };
    auto groundFlag200 = [this]() {
        const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(m_GrdContDatasInOut.m_pGround);
        return ground != nullptr && (ground->m_ui16PropertiesFlags & 0x200u) != 0;
    };
    auto normalise = [](float& x, float& y, float& z) {
        const float length = std::sqrt(ppc::fmadds(z, z, ppc::fmadds(x, x, y * y)));  // Math_Sqrtf
        if (length == 0.0f) return false;  // TOC +0xee8
        const float inverse = 1.0f / length;  // TOC +0xee4
        z = inverse * z;
        x = inverse * x;
        y = inverse * y;
        return true;
    };
    auto spawnTarget = [this]() {
        m_unk37c = m_unk1c4;
        m_unk380 = m_unk1c8;
        m_unk384 = m_unk1cc;
        m_unk388 = m_unk1d0;
        m_unk38c = m_unk1d4;
        m_unk390 = m_unk1d8;
        uint32_t word;
        std::memcpy(&word, &m_unk1f0, 4);
        // The original stores a word at +0x394: its three high bytes 0, the low one the spawn word's two bits.
        m_unk394 = 0;
        m_unk395 = 0;
        m_unk396 = 0;
        m_unk397 = static_cast<uint8_t>(word & 3u);
        m_unk398 = m_unk1ed;
    };
    auto ownFrame = [this]() { return static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame; };
    auto targetFrame = [this]() { return static_cast<CSGMovable*>(m_pTarget->m_pKGLObject)->m_pRwFrame; };

    if (isHero()) goto L6d0;
    m_unk8b0 = 0;
L46c:
    group = static_cast<CKGrpS08Enemy*>(g_pEngine->m_gameManager->m_unk04[0]);  // GetEnemyGroup 0x276f58
    if (group->m_bAlerted == 0 || m_unk708 != 0) {
        // L490: the spawn target, the direction flattened.
        spawnTarget();
        m_unk38c = 0.0f;
        normalise(m_unk388, m_unk38c, m_unk390);
        goto L550;
    }
    // L5cc
    if ((group->m_pCurrentFightZone->m_bitArray & 0x200u) == 0) goto L89c;
    cfg = m_pActiveEnemyCpnt;
    if (cfg->m_unk338 != 0 && zone->GetFirstNonNullRef4C() != nullptr && (zone->m_unk04 == 2 || zone->m_unk04 == 5)) {
        goto L80c;
    }
L628:
    cfg = m_pActiveEnemyCpnt;
    if (!heroGroupBlocked() && static_cast<CKGrpSquad*>(m_pGroupSquad)->m_unk94 == 0 && m_unk710 != 0 &&
        cfg->m_vUnk11c.m_ui32NbUsedElt != 0) {
        goto L964;
    }
    // L678: stand: the position, facing the node's modelling at.
    m_unk37c = m_v3Position.x;
    m_unk380 = m_v3Position.y;
    m_unk384 = m_v3Position.z;
    m_unk388 = ownFrame()->modelling.at.x;
    m_unk390 = ownFrame()->modelling.at.z;
    m_unk38c = ownFrame()->modelling.at.y;
    goto L550;

L6d0: {
    CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(static_cast<IKSerializable*>(m_pTarget));
    if (hero->m_unk1dd1 != 0 || hero->IsAttachedToContextualMeca() != 0) {  // 0x0032a420, 0x0032a010
        m_unk8b0 = 1;
    } else {
        m_unk8b0 = 0;
    }
    goto L46c;
}

L80c: {
    if (!isHero()) goto L628;
    const float* heroPosition = static_cast<CKHkS08Hero*>(static_cast<IKSerializable*>(m_pTarget))->GetPositionPtr();
    IKHook* reference = static_cast<IKHook*>(zone->GetFirstNonNullRef4C());  // 0x00274b18
    const RwV3d& at = FrameLtm(static_cast<CSGMovable*>(reference->m_pKGLObject)->m_pRwFrame)->pos;
    const float dz = heroPosition[2] - at.z;
    const float dx = heroPosition[0] - at.x;
    const float distance = ppc::fmadds(dx, dx, dz * dz);
    if (!(distance > zone->m_unk48)) goto L628;  // ble: unordered too
}
L89c:
    spawnTarget();
    goto L550;

L550:
    if (m_ui8EnemyClassType == 1 || m_ui8EnemyClassType == 8) goto L6f8;
    probe(&m_v3Position);
    if (m_ui8EnemyClassType == 8) return;
    if (m_GrdContDatasInOut.m_pGround == nullptr || groundFlag200()) return;
    m_unk7b4 = 0;
    return;

L6f8: {
    const uint8_t state = m_mainState;
    if (m_unk7b4 != 0 || state == 2 || state == 0xd || state == 0xe || state == 0xf || state == 0x1a) goto L7c0;
    if (isHero()) {
        // L928: the hero's height above the ground between 1 and the kind's +0x494.
        const float height = static_cast<CKHkS08Hero*>(static_cast<IKSerializable*>(m_pTarget))->GetHeightAboveGround();
        uint8_t high = 0;
        if (height > 1.0f) high = height < m_pActiveEnemyCpnt->m_unk494 ? 1 : 0;
        m_unk7b4 = high;
    }
    // L778
    if (m_unk7b4 == 0) {
        probe(&m_v3Position);
        m_unk7b4 = m_GrdContDatasInOut.m_fdH > 0.5f ? 1 : 0;  // TOC +0xf28
    }
}
L7c0:
    probe(&m_v3Position);
    if (m_GrdContDatasInOut.m_pGround == nullptr || !groundFlag200()) return;
    m_unk7b4 = 1;
    return;

L964:
    m_bitArray &= ~0x70000u;
    if (m_awareState == 2) goto L9f8;
L99c:
    if (heroGroupBlocked() || static_cast<CKGrpSquad*>(m_pGroupSquad)->m_unk94 != 0) {
        m_unk37c = m_v3Position.x;
        m_unk384 = m_v3Position.z;
        m_unk380 = m_v3Position.y;
        const RwV3d& at = FrameLtm(ownFrame())->at;  // +0x70
        m_unk388 = at.x;
        m_unk390 = at.z;
        m_unk38c = at.y;
    }
    goto L550;

L9f8:
    UpdateBehaviourMode(clock);  // 0x0028f928
    if (IsInDeathStates() == 0 && (m_bitArray & 0x10000u) == 0) {
        m_unk328 = 0;
        if (m_unk528 <= 7u) SelectAttack();  // 0x0028ed10 (the switch's eight cases)
    }
    // La80
    cfg = m_pActiveEnemyCpnt;
    attack = m_pCurrentAttack;
    if (attack != nullptr && (m_unk740 >= cfg->m_unk36c || m_unk744 == 0)) {
        // Lab0
        if (m_unk7dc == 0) goto Lb40;
        const CKS08EnemyAttack* selected = static_cast<CKS08EnemyAttack*>(cfg->m_vUnk11c.m_pBlock[m_unk32c]);
        const RwV3d& at = FrameLtm(targetFrame())->pos;
        const float k = -selected->m_unk0c;
        m_unk37c = ppc::fmadds(k, m_unk388, at.x);
        m_unk384 = ppc::fmadds(k, m_unk390, at.z);
        m_unk380 = ppc::fmadds(k, m_unk38c, at.y);
        attack = m_pCurrentAttack;
    }
    // Lb2c
    if (m_unk7dc != 0) goto Lb6c;
    if (attack == nullptr) goto Lbf4;
Lb40:
    if (!(attack->m_unk10 > m_unk344) && !(attack->m_unk14 < m_unk344)) goto L1424;  // bgt / bge
    m_unk7dc = 1;
Lb6c:
    cfg = m_pActiveEnemyCpnt;
    if (attack == nullptr) goto Lc00;
    if (m_unk740 >= cfg->m_unk36c && m_unk7dc != 0) {
        if (m_unk83c == kNull.x && m_unk840 == kNull.y && m_unk844 == kNull.z) {
            ComputeAttackApproachPoint();  // 0x00280e30
            m_bitArray = (m_bitArray & ~0x40000u) | 0x40000u;
            attack = m_pCurrentAttack;
        }
    }
Lbf4:
    if (attack != nullptr) goto Lc5c;
    cfg = m_pActiveEnemyCpnt;
Lc00:
    if (!(m_unk344 < cfg->m_unk4e0)) goto Lc5c;
    if (m_pTarget == nullptr) goto Lc5c;
    if (isHero()) {
        // L13cc: in front of the hero by the kind's +0x4e0 along the direction.
        const float* heroPosition = static_cast<CKHkS08Hero*>(static_cast<IKSerializable*>(m_pTarget))->GetPositionPtr();
        const float k = -m_pActiveEnemyCpnt->m_unk4e0;
        m_unk37c = ppc::fmadds(k, m_unk388, heroPosition[0]);
        m_unk384 = ppc::fmadds(k, m_unk390, heroPosition[2]);
        m_unk380 = ppc::fmadds(k, m_unk38c, heroPosition[1]);
    }
    attack = m_pCurrentAttack;
Lc5c:
    m_unk81a = 1;
    if (attack == nullptr || m_pTarget == nullptr) goto Ldf4;
    if (!(m_unk740 >= m_pActiveEnemyCpnt->m_unk36c)) goto Ldf4;
    if (m_ui8EnemyClassType == 1 || m_ui8EnemyClassType == 8) goto Le08;
    {
        const RwV3d& at = targetFrame()->modelling.pos;  // +0x40
        targetPoint = CVector3{at.x, at.y, at.z};
        probe(&targetPoint);
        if (m_GrdContDatasInOut.m_eContactStatus != 0) goto Ldf4;
        if (!(m_GrdContDatasInOut.m_fdH >= m_pActiveEnemyCpnt->m_unk4f8)) goto Ldf4;
        m_unk81a = 0;
        if (m_unk344 <= m_pActiveEnemyCpnt->m_unk4f4) {
            // Close: stay, facing the hero.
            m_unk37c = m_v3Position.x;
            m_unk380 = m_v3Position.y;
            const float dy = targetPoint.y - m_v3Position.y;
            const float dx = targetPoint.x - m_v3Position.x;
            m_unk384 = m_v3Position.z;
            const float dz = targetPoint.z - m_v3Position.z;
            m_unk388 = dx;
            m_unk38c = dy;
            m_unk390 = dz;
            normalise(m_unk388, m_unk38c, m_unk390);
            m_unk338 = m_v3Position;
        } else {
            // L1020: at the kind's +0x4f4 from the hero, along the line to it.
            float dx = targetPoint.x - m_v3Position.x;
            float dy = targetPoint.y - m_v3Position.y;
            float dz = targetPoint.z - m_v3Position.z;
            m_unk388 = dx;
            m_unk38c = dy;
            m_unk390 = dz;
            if (normalise(dx, dy, dz)) {
                m_unk390 = dz;
                m_unk388 = dx;
                m_unk38c = dy;
            }
            const float k = -m_pActiveEnemyCpnt->m_unk4f4;
            m_unk37c = ppc::fmadds(k, dx, targetPoint.x);
            m_unk384 = ppc::fmadds(k, dz, targetPoint.z);
            m_unk380 = ppc::fmadds(k, dy, targetPoint.y);
        }
    }
Ldf4:
    if (static_cast<uint8_t>(m_ui8EnemyClassType - 5) <= 1u) goto L1100;
Le08:
    picked = 0;
Le0c:
    if (IsInDeathStates() != 0) goto L99c;
    attack = m_pCurrentAttack;
    if (attack == nullptr) goto L99c;
    if (!(m_unk2ac <= 0.0f) && m_unk709 == 0 && m_unk8b0 == 0 && !isCrumbly()) goto L99c;
    if (m_fIceGauge != 0.0f) goto L99c;
    if (picked != 0) goto L99c;
    {
        // The flat direction to the target hero.
        const RwV3d& at = FrameLtm(targetFrame())->pos;
        float x = at.x - m_v3Position.x;
        float z = at.z - m_v3Position.z;
        float y = 0.0f;
        const float length = std::sqrt(ppc::fmadds(z, z, ppc::fmadds(x, x, 0.0f)));
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            z = z * inverse;
            x = x * inverse;
            y = inverse * 0.0f;
        }
        if (!(m_afAttackCooldowns[m_unk32c] <= 0.0f) && m_unk709 == 0 && m_unk8b0 == 0 && !isCrumbly()) goto L99c;
        const RwV3d& facingAt = ownFrame()->modelling.at;  // +0x30
        CVector3 facing{facingAt.x, facingAt.y, facingAt.z};
        CVector3 direction{x, y, z};
        const float angle = AngleBetween(&direction, &facing);  // 0x0027eb88
        attack = m_pCurrentAttack;
        if (!(attack->m_unk60 > angle)) goto L99c;
        if (attack->m_unk08 == 2) {
            // L1174: only while the sector's animated node was drawn this frame.
            const CSGLeaf* node = static_cast<const CSGLeaf*>(m_apEnemySectorCpnt[GetSectorIndex()]->GetAnimatedNode(0));  // 0x002b3110
            if (node->m_ui16LastRenderedFrame != g_ui16RenderFrameCounter) goto L99c;  // 0x00c29694
        }
        m_bitArray = (m_bitArray & ~0x10000u) | 0x10000u;  // Lffc
    }
    goto L99c;

L1100:
    if (!(m_unk83c == kNull.x && m_unk840 == kNull.y && m_unk844 == kNull.z)) {
        // L1138
        if (IsWithinHeroRangeOfCameraFocus(4.0f) != 0) {  // TOC +0xf4c, 0x0027dc70
            // L12dc
            const float dz = m_unk844 - m_v3Position.z;
            const float dx = m_unk83c - m_v3Position.x;
            if (ppc::fmadds(dx, dx, dz * dz) < 0.2f) goto L1154;  // TOC +0xf04
            if (IsWithinHeroRangeOfCameraFocus(6.0f) == 0) goto Le08;  // TOC +0xf50
            m_unk37c = m_unk83c;
            m_unk380 = m_unk840;
            m_unk384 = m_unk844;
            m_unk388 = m_unk83c - m_v3Position.x;
            m_unk38c = m_unk840 - m_v3Position.y;
            m_unk390 = m_unk844 - m_v3Position.z;
            if (!normalise(m_unk388, m_unk38c, m_unk390)) goto Le08;
            picked = 0;
            goto Le0c;
        }
    L1154:
        picked = 0;
        m_unk83c = kNull.x;
        m_unk840 = kNull.y;
        m_unk844 = kNull.z;
        goto Le0c;
    }
    // L11b8
    if (IsWithinHeroRangeOfCameraFocus(2.0f) == 0) goto Le08;  // TOC +0xf44
    {
        const CVector3 spot = PickAttackSpotNearHero();  // 0x00280190 (the null vector's parts are never NaN)
        if (spot.x == kNull.x && spot.y == kNull.y && spot.z == kNull.z) goto Le08;
        m_unk37c = spot.x;
        m_unk380 = spot.y;
        m_unk384 = spot.z;
        m_unk388 = spot.x - m_v3Position.x;
        m_unk38c = spot.y - m_v3Position.y;
        m_unk390 = spot.z - m_v3Position.z;
        normalise(m_unk388, m_unk38c, m_unk390);
        picked = 1;
        m_unk83c = m_unk37c;
        m_unk840 = m_unk380;
        m_unk844 = m_unk384;
    }
    goto Le0c;

L1424: {
    const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;  // 0x00011500
    const float roll = static_cast<float>(static_cast<double>(r)) / 65535.0f;  // TOC +0xf24
    if (roll < m_pActiveEnemyCpnt->m_unk558) {
        m_unk8a8 = 1;
        m_unk7dc = 1;
    }
    attack = m_pCurrentAttack;
    goto Lb6c;
}
}

namespace {
// The enemy group's attack-slot holders (+0x164, as many as the reserved total +0x154) whose byte +0x328 is `value`.
// BUG(original): a holder past the vector's length is read through null.
uint32_t CountHoldersWith(const CKGrpS08Enemy* group, uint8_t value) {
    uint32_t count = 0;
    const uint32_t total = group->m_ui32ReservedAttackSlotsTotal;
    for (uint32_t i = 0; i < total; ++i) {
        const auto* holder = static_cast<const CKHkS08Enemy*>(
            static_cast<int32_t>(i) < static_cast<int32_t>(group->m_vUnk164.m_ui32NbUsedElt) ? group->m_vUnk164.m_pBlock[i]
                                                                                            : nullptr);
        if (holder->m_unk328 == value) ++count;
    }
    return count;
}
}  // namespace

// 0x0028f928 CKHkS08Enemy_UpdateBehaviourMode: the behaviour mode +0x528 by the kind's behaviour (+0x198). 0: mode 1 once
// the health (+0x258) is at most the kind's +0x19c. 1: between 0 and 1 by the group's slot holders, mode 1 while fewer
// hold +0x328 = 1 than 0. 3: mode 3 becomes 2 while the fight zone has spawned fewer than the kind's +0x1a0. 4: mode 0
// goes to 4 (the count +0x52c reset) once +0x530 reaches the kind's +0x1a8; mode 4 back to 0 (+0x530 reset) once the
// count reaches the kind's +0x1a4.
void CKHkS08Enemy::UpdateBehaviourMode(IKTime* /*clock*/) {
    const CKS08EnemyCpnt* cfg = m_pActiveEnemyCpnt;
    const int32_t behaviour = cfg->m_unk198;
    if (behaviour == 1) {
        if (m_unk528 != 1 && m_unk528 != 0) return;
        const auto* group = static_cast<const CKGrpS08Enemy*>(enemy::EnemyGroup());  // 0x00276f58
        const int32_t free = static_cast<int32_t>(CountHoldersWith(group, 0));
        const int32_t held = static_cast<int32_t>(CountHoldersWith(group, 1));
        if (m_unk528 == 1) {
            if (held > free) m_unk528 = 0;
        } else if (held < free) {
            m_unk528 = 1;
        }
        return;
    }
    if (static_cast<uint32_t>(behaviour) < 1) {
        if (m_unk528 != 0) return;
        const float threshold = static_cast<float>(static_cast<double>(static_cast<uint32_t>(cfg->m_unk19c)));  // fcfid
        if (m_fHealth <= threshold) m_unk528 = 1;  // cror lt / eq
        return;
    }
    if (behaviour == 3) {
        if (m_unk528 != 3) return;
        const CKGrpFightZone* zone = static_cast<CKGrpSquad*>(m_pGroupSquad)->GetFightZone();  // 0x0025ab50
        if (zone->m_unk88 < cfg->m_unk1a0) m_unk528 = 2;
        return;
    }
    if (behaviour != 4) return;
    if (m_unk528 == 4) {
        if (m_unk52c >= static_cast<uint32_t>(cfg->m_unk1a4)) {  // cmplw
            m_unk528 = 0;
            m_unk530 = 0.0f;
        }
        return;
    }
    if (m_unk528 != 0) return;
    if (m_unk530 >= cfg->m_unk1a8) {  // cror gt / eq
        m_unk52c = 0;
        m_unk528 = 4;
    }
}

// 0x0028ed10 CKHkS08Enemy_SelectAttack: the kind's attacks scored (ScoreAttack; 0 for the typed ones while the target
// is not a crumbly zone and +0x709 is clear); the highest wins, a tie with a better score than the current attack's
// (+0x73c) is a coin toss (a rand draw), the current attack wins its ties. The winner into +0x32c / +0x73c with its
// score +0x740; a new slot category (+0x7d8) is reserved in the enemy group for a hero target (released first when
// one is held, +0x891), else just noted. No attacks: +0x73c null.
void CKHkS08Enemy::SelectAttack() {
    CKS08EnemyCpnt* cfg = m_pActiveEnemyCpnt;
    const uint32_t count = cfg->m_vUnk11c.m_ui32NbUsedElt;  // +0x124
    uint32_t best = 0;
    float bestScore = 0.0f;     // TOC +0xee8
    float currentScore = 0.0f;  // the current attack's score
    for (uint32_t i = 0; i < count; ++i) {
        cfg = m_pActiveEnemyCpnt;
        CKS08EnemyAttack* attack = static_cast<CKS08EnemyAttack*>(cfg->m_vUnk11c.m_pBlock[i]);
        const bool crumbly = m_pTarget != nullptr && m_pTarget->IsKindOfClass(CKHkS08CrumblyZoneMultiState::kClassKey) != 0;
        float score;
        if ((crumbly || m_unk709 != 0) && attack->m_unk08 != 0) {
            score = 0.0f;
        } else {
            score = ScoreAttack(i);  // 0x0028e758
        }
        const bool isCurrent = attack == m_pCurrentAttack;
        if (isCurrent) currentScore = score;
        bool pick;
        if (score == bestScore) {
            if (isCurrent) {
                pick = true;
            } else if (score > currentScore) {
                const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;  // 0x00011500
                pick = static_cast<float>(static_cast<double>(r)) / 65535.0f >= 0.5f;  // TOC +0xf24 / +0xf28
            } else {
                pick = false;
            }
        } else {
            pick = score > bestScore;
        }
        if (pick) {
            best = i;
            bestScore = score;
        }
    }
    cfg = m_pActiveEnemyCpnt;
    m_pCurrentAttack = nullptr;
    if (cfg->m_vUnk11c.m_ui32NbUsedElt == 0) return;
    CKS08EnemyAttack* chosen = static_cast<CKS08EnemyAttack*>(cfg->m_vUnk11c.m_pBlock[best]);
    m_unk32c = best;
    m_unk740 = bestScore;
    m_pCurrentAttack = chosen;
    const int32_t category = GetAttackSlotCategory(chosen->m_unk08);  // 0x0027d100
    if (m_unk7d8 == category) {
        if (category == -1) m_pCurrentAttack = nullptr;
        return;
    }
    if (m_pTarget->IsKindOfClass(CKHkS08Hero::kClassKey) == 0 || m_unk709 != 0) {
        m_unk7d8 = category;
        return;
    }
    CKGrpS08Enemy* group = static_cast<CKGrpS08Enemy*>(g_pEngine->m_gameManager->m_unk04[0]);  // GetEnemyGroup 0x276f58
    if (group->CanReserveAttackSlot(category) == 0) return;  // 0x00267848
    if (m_unk891 != 0) group->ReleaseAttackSlot(m_unk7d8, this);  // 0x00267138
    group->ReserveAttackSlot(category, this);  // 0x00267260
    m_unk7d8 = category;
    m_unk891 = 1;
}

// 0x0028e758 CKHkS08Enemy_ScoreAttack: attack `index`'s score. A hero target needs a free slot of the attack's category
// (when the enemy holds another). The parts, weighted by the kind's +0x354 .. +0x368: how well the distance +0x344
// fits [+0x10, +0x14] (1 inside, falling to 0 over the move component's +0x28 outside), the type flag (+0x370 by
// +0x08: 1; 10 for type 0 while +0x709), the cooldown left (+0x2b0, 1 when ready), and the target hero's ground for the
// attacks of +0x64 1 / 2 / 3 (the ground's height above +0x68, the hero above the ground by 0.2, over the ground).
float CKHkS08Enemy::ScoreAttack(uint32_t index) {
    CKS08EnemyCpnt* cfg = m_pActiveEnemyCpnt;
    CKS08EnemyAttack* attack = static_cast<CKS08EnemyAttack*>(cfg->m_vUnk11c.m_pBlock[index]);
    const int32_t category = attack->m_unk08 == 1 ? 1 : (attack->m_unk08 == 2 ? 2 : 0);
    if (m_unk7d8 != category && m_pTarget != nullptr && m_pTarget->IsKindOfClass(CKHkS08Hero::kClassKey) != 0) {
        CKGrpS08Enemy* group = static_cast<CKGrpS08Enemy*>(g_pEngine->m_gameManager->m_unk04[0]);  // GetEnemyGroup
        if (group->CanReserveAttackSlot(category & 3) == 0) return 0.0f;  // 0x00267848
        cfg = m_pActiveEnemyCpnt;
        attack = static_cast<CKS08EnemyAttack*>(cfg->m_vUnk11c.m_pBlock[index]);
    }
    const float distance = m_unk344;
    const float falloff = cfg->m_MoveCpnt.m_afParams[7];  // +0x28
    const float nearest = attack->m_unk10;
    const float farthest = attack->m_unk14;
    float rangeScore;
    if (nearest <= distance && farthest >= distance) {
        rangeScore = 1.0f;  // TOC +0xee4
    } else if (farthest < distance && !(distance >= farthest + falloff)) {
        rangeScore = ((farthest + falloff) - distance) / falloff;
    } else if (nearest > distance) {
        const float start = nearest - falloff;
        if (!(distance > start)) {
            rangeScore = 0.0f;
        } else if (start <= 0.0f) {
            rangeScore = distance / nearest;
        } else {
            rangeScore = (falloff - (nearest - distance)) / falloff;
        }
    } else {
        rangeScore = 0.0f;
    }
    const int32_t type = attack->m_unk08;
    float typeScore = cfg->m_vUnk370.m_pBlock[type] != 0 ? 1.0f : 0.0f;
    if (m_unk709 != 0 && type == 0) typeScore = 10.0f;  // TOC +0xeec
    const float timer = m_afAttackCooldowns[index];
    const float readiness = timer >= 0.0f ? (attack->m_unk1c - timer) / attack->m_unk1c : 1.0f;
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);  // TOC +0xf00 -> +0x58
    auto probeTarget = [this, collision]() {
        const RwV3d& at = static_cast<CSGMovable*>(m_pTarget->m_pKGLObject)->m_pRwFrame->modelling.pos;  // +0x40
        CVector3 point{at.x, at.y, at.z};
        collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &point.x, 1);  // 0x00196540
    };
    float groundA = 0.0f;  // the +0x360 term
    float groundB = 0.0f;  // the +0x364 term
    float groundC = 0.0f;  // the +0x368 term
    if (m_unk7b4 == 0) {
        if (m_pTarget != nullptr && attack->m_unk64 == 1) {
            probeTarget();
            const float flag = m_GrdContDatasInOut.m_eContactStatus == 0 && m_GrdContDatasInOut.m_fdH >= attack->m_unk68 ? 1.0f : 0.0f;
            cfg = m_pActiveEnemyCpnt;
            groundA = flag * cfg->m_unk360;
            attack = static_cast<CKS08EnemyAttack*>(cfg->m_vUnk11c.m_pBlock[index]);
            if (m_unk7b4 != 0) goto withHeight;
        } else {
            groundA = cfg->m_unk360 * 0.0f;
        }
        groundB = cfg->m_unk364 * 0.0f;
        groundC = 0.0f;
        goto sum;
    }
    groundA = cfg->m_unk360 * 0.0f;
withHeight:
    if (m_pTarget != nullptr && attack->m_unk64 == 2) {
        probeTarget();
        const float flag = m_GrdContDatasInOut.m_eContactStatus != 0 || m_GrdContDatasInOut.m_fdH < 0.2f ? 1.0f : 0.0f;  // TOC +0xf04 (bge)
        cfg = m_pActiveEnemyCpnt;
        groundB = flag * cfg->m_unk364;
        attack = static_cast<CKS08EnemyAttack*>(cfg->m_vUnk11c.m_pBlock[index]);
        if (m_unk7b4 == 0) goto sum;
    } else {
        cfg = m_pActiveEnemyCpnt;
        groundB = cfg->m_unk364 * 0.0f;
        attack = static_cast<CKS08EnemyAttack*>(cfg->m_vUnk11c.m_pBlock[index]);
    }
    if (m_pTarget != nullptr && attack->m_unk64 == 3) {
        probeTarget();
        groundC = m_GrdContDatasInOut.m_eContactStatus == 0 && m_GrdContDatasInOut.m_fdH >= attack->m_unk68 ? 1.0f : 0.0f;
        cfg = m_pActiveEnemyCpnt;
    }
sum:
    float total = typeScore * cfg->m_unk358;
    total = ppc::fmadds(rangeScore, cfg->m_unk354, total);
    total = ppc::fmadds(readiness, cfg->m_unk35c, total);
    total = groundA + total;
    total = total + groundB;
    return ppc::fmadds(groundC, cfg->m_unk368, total);
}

// 0x00280e30 CKHkS08Enemy_ComputeAttackApproachPoint_maybe: the point +0x338 at the selected attack's range (+0x0c)
// from the target hero: on the hero's side of us (turned by a random angle of the kind's [+0x55c, +0x560] once
// +0x8a8 asks for it, outside the attack states 0xd..0xf), else beyond the hero, then that direction turned by
// +-90, 45, 135, -45, -135 degrees about y, then the hero itself: the first one inside its nav node's box and walkable
// for our character; else our own position. The flying kinds 1 / 8 over a low ground take the height of the hero
// (in the windup of a type 0 / 3 attack) or +0x498 higher. +0x7dc (moving to the point) cleared within 0.05 of it in
// x / z; the flying kinds following an actor approach its height instead (+0x7dc set).
void CKHkS08Enemy::ComputeAttackApproachPoint() {
    auto targetFrame = [this]() { return static_cast<CSGMovable*>(m_pTarget->m_pKGLObject)->m_pRwFrame; };
    CKSrvPathFinding* pathFinding = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);
    const CVector3 kAxisY{0.0f, 1.0f, 0.0f};  // TOC +0xb10: 0x00c50d40
    // The inlined test after each candidate: the point found in a node (FindSectorForPoint's result unused), inside
    // that node's box and walkable.
    auto accepted = [this, pathFinding]() {
        CPFPoint point;
        point.m_position = m_unk338;
        point.m_i16GraphNodeIndex = m_PFCpnt.m_Destination.m_i16GraphNodeIndex;  // +0x108
        pathFinding->FindSectorForPoint(&point);  // 0x001e5ca0
        return PointInNodeBox(pathFinding, &point) &&
               (pathFinding->IsPointWalkable(&point, &m_PFCpnt.m_CharacterType) & 0xffu) != 0;  // 0x001e42d0
    };
    const bool flyingKind = m_ui8EnemyClassType == 1 || m_ui8EnemyClassType == 8;

    // The flat direction from the hero to us.
    float x;
    float y = 0.0f;
    float z;
    {
        const RwV3d& hero = FrameLtm(targetFrame())->pos;
        x = m_v3Position.x - hero.x;
        z = m_v3Position.z - hero.z;
        const float length = std::sqrt(ppc::fmadds(z, z, ppc::fmadds(x, x, 0.0f)));  // Math_Sqrtf
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            z = z * inverse;
            x = x * inverse;
            y = inverse * 0.0f;
        }
    }
    if (m_mainState != 0xd && m_mainState != 0xe && m_mainState != 0xf && m_unk8a8 != 0) {
        // 0x00281fa8: turned about y by a random angle of the kind's range, either way.
        const CKS08EnemyCpnt* cfg = m_pActiveEnemyCpnt;
        const uint32_t r0 = static_cast<uint32_t>(Rand_Int()) & 0xffffu;  // 0x00011500
        float angle = ppc::fmadds(static_cast<float>(static_cast<double>(r0)) / 65535.0f, cfg->m_unk560 - cfg->m_unk55c,
                                  cfg->m_unk55c);  // TOC +0xb64
        const uint32_t r1 = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
        if (static_cast<float>(static_cast<double>(r1)) / 65535.0f < 0.5f) angle = -angle;  // TOC +0xb68
        CMatrix34 turn{};
        turn.m_at = CVector3{x, y, z};
        Mat4_RotateInPlace(&turn, &kAxisY, angle * 57.29578f);  // 0x00240498, TOC +0xb14
        x = turn.m_at.x;
        y = turn.m_at.y;
        z = turn.m_at.z;
        const float length = std::sqrt(ppc::fmadds(z, z, ppc::fmadds(x, x, y * y)));
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            z = z * inverse;
            x = x * inverse;
            y = y * inverse;
        }
        m_unk8a8 = 0;
    }
    {
        const float range = m_pCurrentAttack->m_unk0c;
        const RwV3d& hero = FrameLtm(targetFrame())->pos;
        m_unk338.x = ppc::fmadds(range, x, hero.x);
        m_unk338.z = ppc::fmadds(range, z, hero.z);
        m_unk338.y = ppc::fmadds(y, range, hero.y);
    }
    if (flyingKind && m_pTarget->IsKindOfClass(CKHkS08Hero::kClassKey) != 0) {
        // 0x00281e58: over a ground 0.2 or more below the hero (or none), the height of the hero (the windup of a type
        // 0 / 3 attack) or the kind's +0x498 above the candidate.
        CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
        collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &targetFrame()->modelling.pos.x, 1);  // 0x00196540
        if (m_GrdContDatasInOut.m_eContactStatus != 0 || m_GrdContDatasInOut.m_fdH < 0.2f) {  // bge: NaN keeps the point
            const CKS08EnemyAttack* attack = m_pCurrentAttack;
            if (attack != nullptr && (attack->m_unk08 == 0 || attack->m_unk08 == 3) && m_mainState == 0xd) {
                m_unk338.y = targetFrame()->modelling.pos.y;
            } else {
                m_unk338.y = m_unk338.y + m_pActiveEnemyCpnt->m_unk498;
            }
        }
    }
    if (m_pCurrentAttack != nullptr && !accepted()) {
        // 0x00280ff0: beyond the hero, then turned.
        const RwV3d& heroPos = FrameLtm(targetFrame())->pos;
        const float hx = heroPos.x;
        const float hz = heroPos.z;
        const float hy = heroPos.y;
        auto towardHero = [this, hx, hz](float& dx, float& dy, float& dz) {
            dx = hx - m_v3Position.x;
            dz = hz - m_v3Position.z;
            dy = 0.0f;
            const float length = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, 0.0f)));
            if (length != 0.0f) {
                const float inverse = 1.0f / length;
                dx = dx * inverse;
                dz = dz * inverse;
                dy = inverse * 0.0f;
            }
        };
        auto place = [this, hx, hy, hz](const CVector3& d) {
            const float range = m_pCurrentAttack->m_unk0c;
            m_unk338.z = ppc::fmadds(range, d.z, hz);
            m_unk338.x = ppc::fmadds(d.x, range, hx);
            m_unk338.y = ppc::fmadds(range, d.y, hy);
        };
        CVector3 d;
        towardHero(d.x, d.y, d.z);
        place(d);
        bool found = accepted();
        static const float kTurns[6] = {1.5707964f, -1.5707964f, 0.7853982f, 2.3561945f, -0.7853982f, -2.3561945f};  // TOC +0xbcc..+0xbe0
        for (int32_t i = 0; i < 6 && !found; ++i) {
            towardHero(d.x, d.y, d.z);
            CVector3 axis = kAxisY;
            CVector3 turned;
            Vec3_RotateTowardByAngle(&turned, &d, &axis, kTurns[i]);  // TocBridge 0x98f300
            place(turned);
            found = accepted();
        }
        if (!found) {
            m_unk338 = CVector3{hx, hy, hz};
            if (!accepted()) {
                const RwV3d& own = FrameLtm(static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame)->pos;
                m_unk338 = CVector3{own.x, own.y, own.z};
            }
        }
    }
    // 0x002816e8
    if (flyingKind && m_pTarget->IsKindOfClass(CKHkActorBase::kClassKey) != 0) {
        const float heroY = FrameLtm(targetFrame())->pos.y;
        m_unk338.y = heroY;
        float approach[3] = {heroY, 1.0f, m_v3Position.y};  // TOC +0xb44
        m_v3Position.y = FloatApproach_Step(m_fScaledDt, approach);  // 0x002436e8
        m_unk7dc = 1;
        return;
    }
    const float dz = m_unk338.z - m_v3Position.z;
    const float dx = m_unk338.x - m_v3Position.x;
    if (ppc::fmadds(dx, dx, dz * dz) <= 0.05f) m_unk7dc = 0;  // TOC +0xbb4
}

// 0x0027dc70 CKHkS08Enemy_IsWithinHeroRangeOfCameraFocus_maybe: the camera service's real position (+0x598, xz) is
// farther (squared, fcmpu + cror lt|eq) from the enemy than `range` plus a player-controlled dragon's own distance to
// it: dragon 0 (when it is player-controlled) must fail that test for a 1, and a player-controlled dragon 1 passing it
// makes the answer 0.
uint8_t CKHkS08Enemy::IsWithinHeroRangeOfCameraFocus(float range) {
    const CKSrvCamera* camera = static_cast<const CKSrvCamera*>(g_pEngine->m_srvCamera);  // TOC +0xb08 -> +0x70
    const float focusZ = camera->m_v3RealPos.z;
    const float focusX = camera->m_v3RealPos.x;
    const float ez = focusZ - m_v3Position.z;
    const float ex = focusX - m_v3Position.x;
    const float enemy = ppc::fmadds(ex, ex, ez * ez);
    IKGrpHero* heroes = static_cast<IKGrpHero*>(g_pEngine->m_gameManager->m_unk04[1]);  // GetHeroGroup 0x276f70
    // A player-controlled dragon whose distance to the focus plus `range`, squared, is at most the enemy's.
    auto nearer = [&](uint32_t dragon) {
        CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(heroes->m_apHeros[dragon]);  // GetHeroByDragonIndex 0x2ca080
        if (hero->IsPlayerControlled() == 0) return false;                        // 0x00362af0
        const float* position = hero->GetPositionPtr();                           // 0x00361968
        const float hz = focusZ - position[2];
        const float hx = focusX - position[0];
        float reach = std::sqrt(ppc::fmadds(hx, hx, hz * hz)) + range;  // Math_Sqrtf 0x10690
        reach = reach * reach;
        return reach <= enemy;
    };
    const uint8_t result = nearer(0) ? 0 : 1;
    if (nearer(1)) return 0;
    return result;
}

// 0x0028c838 CKHkS08Enemy_SetMeshPopFxActive_maybe: the burrow's mesh pop (+0x87c, the kind's +0x544 data). Off: the
// pop told off and stopped (vt+0x58), dropped. `positionOnly`: the held pop moved to +0x850. On: without a held pop,
// the data's placement cleared, a pooled pop acquired (the inlined lookup), placed at +0x850 and turned on.
void CKHkS08Enemy::SetMeshPopFxActive(int32_t active, int32_t positionOnly) {
    CKMeshPopFxData* data = static_cast<CKMeshPopFxData*>(Cfg()->m_pUnk544);
    const CVector3 at = {m_unk850, m_unk854, m_unk858};
    if (active == 0) {
        if (m_pBurrowMeshPopFx == nullptr) return;
        m_pBurrowMeshPopFx->SetActive(this, 0);       // 0x001cb568
        m_pBurrowMeshPopFx->StopAndRelease(this);     // vt+0x58
        m_pBurrowMeshPopFx = nullptr;
        return;
    }
    if (positionOnly != 0) {
        if (m_pBurrowMeshPopFx == nullptr) return;
        m_pBurrowMeshPopFx->SetPositionForOwner(this, &at);  // 0x001c9c08
        return;
    }
    if (m_pBurrowMeshPopFx != nullptr) return;
    data->m_unk08 = nullptr;
    data->m_unk0c = nullptr;
    m_pBurrowMeshPopFx = static_cast<CKMeshPopNodeFx*>(
        static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(reinterpret_cast<IKFxData*>(data), this));
    if (m_pBurrowMeshPopFx == nullptr) return;
    m_pBurrowMeshPopFx->SetPositionForOwner(this, &at);
    m_pBurrowMeshPopFx->SetActive(this, 1);
}

// 0x0028cb88 CKHkS08Enemy_SetFreezeFxActive_maybe (the pooled lookup inlined, as CKSrvFx::AcquireFx)
void CKHkS08Enemy::SetFreezeFxActive(int32_t active, int32_t hotSpot) {
    CKMeshPopFxData* data = static_cast<CKMeshPopFxData*>(m_pActiveEnemyCpnt->m_pUnk4f0);
    if (active == 0) {
        if (m_pFreezeMeshPopFx == nullptr) return;
        m_pFreezeMeshPopFx->StopAndRelease(this);  // vt+0x58
        m_pFreezeMeshPopFx = nullptr;
        return;
    }
    if (m_pFreezeMeshPopFx != nullptr) return;
    data->m_unk0c = GetHotSpot(hotSpot < 0 ? 1 : hotSpot);  // 0x002892e8
    data->m_unk08 = nullptr;
    m_pFreezeMeshPopFx = static_cast<CKMeshPopNodeFx*>(
        static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(reinterpret_cast<IKFxData*>(data), this));
    if (m_pFreezeMeshPopFx == nullptr) return;
    m_pFreezeMeshPopFx->TriggerPop(this, 0);  // 0x001caf50
}

namespace {
// One explosion of FX data `data` from the FX pool (the inlined CKSrvFx_AcquireFx) set off at `at` for `owner`, then
// let go (vt+0x54).
void TriggerExplosionAt(IKFxData* data, const CVector3* at, CKHkS08Enemy* owner) {
    IKFx* effect = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(data, owner);
    if (effect == nullptr) return;
    CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(effect);
    explosion->SetTranslation(at, owner);  // 0x001b66e8
    explosion->Trigger(owner, 0);          // 0x001b82a8
    explosion->ReleaseReservation(owner);  // vt+0x54
}
}  // namespace

// 0x0028cec0 CKHkS08Enemy_SpawnShieldDropFx_maybe: the kind's FX 0x15 (+0x128) set off at the sector component's hot
// spot 4.
void CKHkS08Enemy::SpawnShieldDropFx() {
    IKFxData* data = static_cast<IKFxData*>(m_pActiveEnemyCpnt->m_vUnk128.m_pBlock[0x15]);
    IKFx* effect = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(data, this);
    if (effect == nullptr) return;
    CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(effect);
    CVector3 at;
    static_cast<CSGHotSpot*>(GetSectorCpnt()->GetHotSpot(4))->GetWorldPosition(&at);  // 0x002771c0, 0x002b31e0, 0x000ce790
    explosion->SetTranslation(&at, this);  // 0x001b66e8
    explosion->Trigger(this, 0);           // 0x001b82a8
    explosion->ReleaseReservation(this);   // vt+0x54
}

// 0x0028d1b8 CKHkS08Enemy_SetStunFxActive_maybe: the kind's spark FX data (+0x32c) follows the sector hot spot 1 (its
// +0x10, +0x0c = 0). Off: the spark held in the kind (+0x330) stops (StopOwnedSparkEffect), is let go (vt+0x54) and
// forgotten. On: only while a spark is held, a new one is taken from the pool into +0x330 (null when none is free).
// BUG(original)?: the test is the other way round from the off branch's (a spark is taken only when one is held); the
// kind's +0x330 is shared by every enemy of the kind.
void CKHkS08Enemy::SetStunFxActive(uint8_t on) {
    CKSparkFxData* data = static_cast<CKSparkFxData*>(m_pActiveEnemyCpnt->m_pUnk32c);
    data->m_unk10 = GetSectorHotSpot(1);  // 0x0028a160
    data->m_unk0c = nullptr;
    if (on == 0) {
        if (m_pActiveEnemyCpnt->m_unk330 == nullptr) return;
        StopOwnedSparkEffect(static_cast<CKSparkNodeFx*>(m_pActiveEnemyCpnt->m_unk330), this);  // 0x001d4698
        m_pActiveEnemyCpnt->m_unk330->ReleaseReservation(this);  // vt+0x54
        m_pActiveEnemyCpnt->m_unk330 = nullptr;
        return;
    }
    CKS08EnemyCpnt* kind = m_pActiveEnemyCpnt;
    if (kind->m_unk330 == nullptr) return;
    kind->m_unk330 = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(static_cast<IKFxData*>(kind->m_pUnk32c), this);
}

// 0x0028d4a8 CKHkS08Enemy_PlayFxAtHotspot1_maybe: the kind's FX `fx` (+0x128) set off at hot spot 1; the kinds 5 / 6 at
// each of their hot spots but the fourth (index 3).
void CKHkS08Enemy::PlayFxAtHotspot1(uint32_t fx) {
    if (static_cast<uint8_t>(m_ui8EnemyClassType - 5) > 1) {
        CVector3 at;
        GetHotSpot(1)->GetWorldPosition(&at);  // 0x002892e8, 0x000ce790
        TriggerExplosionAt(static_cast<IKFxData*>(m_pActiveEnemyCpnt->m_vUnk128.m_pBlock[fx]), &at, this);
        return;
    }
    const uint32_t count = enemy::kHotSpotCount[m_ui8EnemyClassType];  // TOC +0xee0 (0x00a70130)
    for (uint32_t i = 0; i < count; ++i) {
        if (i == 3) continue;
        CVector3 at;
        GetHotSpot(static_cast<int32_t>(i))->GetWorldPosition(&at);
        TriggerExplosionAt(static_cast<IKFxData*>(m_pActiveEnemyCpnt->m_vUnk128.m_pBlock[fx]), &at, this);
    }
}

// 0x0028e708 StaticInitAndDestruction_28e708: two file statics (0x00ceace8, 0x00ceacec) set to -1.0f. Nothing in the game
// reads them (their only references are the initialiser's TOC entries).
namespace {
[[maybe_unused]] float s_unkceace8 = -1.0f;
[[maybe_unused]] float s_unkceacec = -1.0f;
}  // namespace
