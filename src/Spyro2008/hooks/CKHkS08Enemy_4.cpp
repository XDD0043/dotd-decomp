// Reconstructed original translation unit: 0x288688-0x288ac8 (GAME_TOC1, main_toc1), 5 functions, 5 live.
// Primary class: CKHkS08Enemy  key 0x26c2  category Hook  size 0x8f8  vtable 0xb22078
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x288688  StaticInitAndDestruction_288688 (static init: nothing to port)
//   [x] 0x2886b8  _GLOBAL__D_2886b8
//   [x] 0x2886c8  _GLOBAL__I_2886c8
//   [x] 0x2886d8  CKHkS08Enemy_AwareSM00_WatchForTarget_maybe
//   [x] 0x288a38  CKHkS08Enemy_UpdateStatusEffects
#include "Spyro2008/hooks/CKHkS08Enemy.h"

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/components/CKS08EnemyCpnt.h"
#include "Spyro2008/groups/CKGrpS08Enemy.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "crt/ppc_ops.h"
#include "k2000/groups/CKGrpSquad.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGMovable.h"

namespace {
// 0x00276f58 GetEnemyGroup: the game manager's +0x04.
CKGrpS08Enemy* EnemyGroup() { return static_cast<CKGrpS08Enemy*>(g_pEngine->m_gameManager->m_unk04[0]); }
}  // namespace

// DOTD: 0x00276f70 GetHeroGroup (+0x08 of the game manager), 0x002ca080 GetHeroByDragonIndex (its +0x30 array) and
// 0x0032a3d0 CKHkS08Hero_GetStatusDecayRate_maybe: the hero's +0xe7c when its +0xed0 bit 7 is set, else 1.0 (TOC 0x2688).
float CKHkS08Enemy::HeroStatusDecayRate(uint32_t dragon) {
    IKGrpHero* group = static_cast<IKGrpHero*>(g_pEngine->m_gameManager->m_unk04[1]);
    const CKHkS08Hero* hero = static_cast<const CKHkS08Hero*>(group->m_apHeros[dragon]);
    if ((hero->m_unked0 & 0x80u) != 0) return hero->m_unke7c;
    return 1.0f;
}

// 0x002886d8 CKHkS08Enemy_AwareSM00_WatchForTarget_maybe: running (phase 0), an enemy of a squad whose fight zone (the
// squad's parent group) is alerted-capable (+0x0c bit 9) and while the enemy group is not alerted (+0x1bc): the target
// (+0x330) within the config's +0x190 (squared, xz) and within +0x194 of the node's facing (Vec3_AngleBetween_maybe,
// asked twice) alerts the group (+0x1bc, SignalAlert_maybe, +0x1e8's high byte), the squad's pending choreography and the
// main state 0x20 (clock null): 2. Else 2 when the group is alerted, 0 otherwise; 0 for the other phases.
uint8_t CKHkS08Enemy::AwareState00_WatchForTarget(IKTime* /*clock*/, int32_t phase, uint8_t /*other*/) {
    if (phase != 0) return 0;
    CKGrpSquad* squad = static_cast<CKGrpSquad*>(m_pGroupSquad);
    if (squad != nullptr && (static_cast<IKLife*>(squad->m_pParent)->m_bitArray & 0x200u) != 0 &&  // CKGrpSquad_GetFightZone 0x25ab50
        EnemyGroup()->m_unk1bc == 0 && m_unk330 != nullptr) {
        const RwFrame* target = static_cast<const CSGMovable*>(m_unk330->m_pKGLObject)->m_pRwFrame;
        const float x = m_v3Position.x;
        const float z = m_v3Position.z;
        const float tx = FrameLtm(target)->pos.x;
        const float tz = FrameLtm(target)->pos.z;
        const float dz = z - tz;
        const float dx = x - tx;
        const float d2 = ppc::fmadds(dx, dx, dz * dz);
        if (d2 <= m_unk884->m_unk190) {
            const float toX = tx - x;
            const float toZ = tz - z;
            const float toY = FrameLtm(target)->pos.y - m_v3Position.y;
            const RwFrame* own = static_cast<const CSGMovable*>(m_pKGLObject)->m_pRwFrame;
            CVector3 facing{FrameLtm(own)->at.x, FrameLtm(own)->at.y, FrameLtm(own)->at.z};
            CVector3 to{toX, toY, toZ};
            if (m_unk884->m_unk194 >= AngleBetween(&facing, &to)) {  // 0x0027eb88
                CVector3 facing2{FrameLtm(own)->at.x, FrameLtm(own)->at.y, FrameLtm(own)->at.z};
                CVector3 to2{toX, toY, toZ};
                if (-m_unk884->m_unk194 <= AngleBetween(&facing2, &to2)) {
                    EnemyGroup()->m_unk1bc = 1;
                    SignalEnemyGroupAlert();  // 0x00268178
                    // stb 1 at +0x1e8: the high byte of the PS3 word.
                    EnemyGroup()->m_unk1e8 = (EnemyGroup()->m_unk1e8 & 0x00ffffffu) | 0x01000000u;
                    ApplySquadPendingChoreography();  // 0x0025ca10
                    SwitchMainState(0x20, nullptr);
                    return 2;
                }
            }
        }
    }
    return EnemyGroup()->m_unk1bc != 0 ? 2 : 0;
}

// 0x00288a38 CKHkS08Enemy_UpdateStatusEffects: burning, poison, freeze, wind, shadow, stun (in that order).
void CKHkS08Enemy::UpdateStatusEffects(IKTime* clock) {
    UpdateStatus0Dot(clock);    // 0x002aeec8
    UpdatePoisonStatus(clock);  // 0x002b0170
    UpdateFreezeStatus(clock);  // 0x002af780
    UpdateWindStatus(clock);    // 0x002b0a20
    UpdateShadowStatus(clock);  // 0x002ae718
    UpdateStunStatus(clock);    // 0x002ae370
}
