// CKHkS08Enemy_xforkD.cpp - DOTD (C2.7 enemy, fork D): bodies of the functions fork D calls that forks B and C own
// (CKHkS08Enemy.cpp, _5.cpp, _7.cpp). The merge keeps the owner's port and drops this file. Where the function is a
// few instructions, the body here is a port; the rest are STUBs.
#include "Spyro2008/hooks/CKHkS08Enemy.h"

#include "Spyro2008/groups/CKGrpS08Enemy.h"
#include "Spyro2008/hooks/CKHkS08EnemyShared.h"
#include "Spyro2008/logic/CKS08CarrierEnemy.h"
#include "Spyro2008/logic/CKS08EnemyAttack.h"
#include "crt/ppc_ops.h"
#include "k2000/components/CKEnemySectorCpnt.h"
#include "k2000/core/Stub.h"
#include "k2000/groups/CKGrpFightZone.h"
#include "k2000/groups/CKGrpSquad.h"
#include "k2000/logic/CSGHotSpot.h"
#include "Spyro2008/components/CKS08EnemyCpnt.h"
#include "k2000/fx/IKFx.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvFx.h"

// 0x0027cda8 EvalRampHoldRampDown_maybe (xfork C): before `rampEnd` the ramp (base + t x slope), through the hold the
// ramp's end value, then down by (t - hold end) x downSlope until `down` after the hold (0: over).
uint8_t CKHkS08Enemy::EvalRampHoldRampDown(float t, float rampEnd, float hold, float down, float base, float slope,
                                           float downSlope, float* out) {
    if (t < rampEnd) {
        *out = ppc::fmadds(t, slope, base);
        return 1;
    }
    const float holdEnd = rampEnd + hold;
    if (t < holdEnd) {
        *out = ppc::fmadds(rampEnd, slope, base);
        return 1;
    }
    if (holdEnd + down <= t) return 0;
    const float top = ppc::fmadds(rampEnd, slope, base);
    *out = top - (t - holdEnd) * downSlope;
    return 1;
}

namespace {
// 0x00a70038 (TOC +0xb20): per enemy kind (4 bytes each) the first volume index of each bounding type, then (+0x24) the
// counts.
const uint8_t kEnemyBoundingTable[0x48] = {
    0x00, 0x01, 0x01, 0x03, 0x00, 0x01, 0x01, 0x03, 0x00, 0x01, 0x01, 0x08, 0x00, 0x01, 0x01, 0x08,
    0x00, 0x01, 0x01, 0x08, 0x00, 0x01, 0x01, 0x0b, 0x00, 0x01, 0x01, 0x0e, 0x00, 0x01, 0x01, 0x03,
    0x00, 0x01, 0x01, 0x07, 0x01, 0x02, 0x02, 0x01, 0x01, 0x02, 0x02, 0x02, 0x01, 0x07, 0x07, 0x02,
    0x01, 0x07, 0x07, 0x01, 0x01, 0x07, 0x07, 0x02, 0x01, 0x0a, 0x0a, 0x03, 0x01, 0x0d, 0x0d, 0x02,
    0x01, 0x02, 0x02, 0x02, 0x01, 0x06, 0x06, 0x02,
};
}  // namespace

// 0x0027d708 CKHkS08Enemy_EnableAttackVolumes_maybe: the kind's attack volumes (bounding type 3: the first index and
// the count from the per-kind table) switched on (vt+0xf0): in state 0x22 the ones the kind's +0x348 flags, then the
// ones the current attack (+0x73c) flags in its +0x48 bytes.
void CKHkS08Enemy::EnableAttackVolumes() {
    const uint32_t slot = static_cast<uint32_t>(m_ui8EnemyClassType) * 4 + 3;
    const uint8_t first = kEnemyBoundingTable[slot];
    const uint8_t count = kEnemyBoundingTable[slot + 0x24];
    if (m_mainState == 0x22) {
        for (uint32_t i = 0; i < count; ++i) {
            if (m_pActiveEnemyCpnt->m_vUnk348.m_pBlock[i] != 0) EnableVolume(static_cast<uint8_t>(first + i));  // vt+0xf0
        }
    }
    if (m_pCurrentAttack == nullptr) return;
    for (uint32_t i = 0; i < count; ++i) {
        if (m_pCurrentAttack->m_array48.m_data[i] != 0) EnableVolume(static_cast<uint8_t>(first + i));  // vt+0xf0
    }
}

// 0x0027eb88 Vec3_AngleBetween_maybe (both vectors normalised in place; CKHkS08Enemy.cpp).
float CKHkS08Enemy::AngleBetween(CVector3* a, CVector3* b) {
    return enemy::Vec3_AngleBetween(a, b);
}

// 0x00277650 IKHkEnemy_Update (xfork C): the position kept as the previous one (+0x140).
void CKHkS08Enemy::IKHkEnemyUpdate(IKTime* /*clock*/) {
    m_unk140 = m_v3Position.x;
    m_unk148 = m_v3Position.z;
    m_unk144 = m_v3Position.y;
}


// The carrier's vt+0x74 (CKS08CarrierEnemy_UpdateStateMachine_maybe 0x4c93e8, through +0x734; no null test).
void CKHkS08Enemy::CallCarrierUpdate(IKTime* clock) {
    static_cast<CKS08CarrierEnemy*>(m_pCarrierEnemy)->UpdateStateMachine(clock);
}

// 0x00268178 CKGrpS08Enemy_SignalAlert_maybe of the enemy group (the game manager's first group, GetEnemyGroup).
void CKHkS08Enemy::SignalEnemyGroupAlert() {
    static_cast<CKGrpS08Enemy*>(g_pEngine->m_gameManager->m_unk04[0])->SignalAlert();
}

// 0x0025ca10 CKGrpSquad_ApplyPendingChoreography_maybe of the squad (+0x168).
void CKHkS08Enemy::ApplySquadPendingChoreography() {
    static_cast<CKGrpSquad*>(m_pGroupSquad)->ApplyPendingChoreography();
}

