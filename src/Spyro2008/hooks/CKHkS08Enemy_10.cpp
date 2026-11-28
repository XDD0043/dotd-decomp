// Reconstructed original translation unit: 0x29d290-0x29dd38 (GAME_TOC1, main_toc1), 9 functions, 9 live.
// Primary class: CKHkS08Enemy  key 0x26c2  category Hook  size 0x8f8  vtable 0xb22078
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x29d290  CKHkS08Enemy_AuxSM00_PlayStartAnim_maybe
//   [x] 0x29d340  StaticInitAndDestruction_29d340  (the two file statics at the end)
//   [ ] 0x29d370  _GLOBAL__D_29d370
//   [ ] 0x29d380  _GLOBAL__I_29d380
//   [x] 0x29d390  CKHkS08Enemy_DropWeaponOrShield_maybe
//   [x] 0x29d548  CKHkS08Enemy_AuxSM01_SeekWeapon_maybe
//   [x] 0x29d760  CKHkS08Enemy_AuxSM02_ClaimWeapon_maybe
//   [x] 0x29d818  CKHkS08Enemy_AuxSM04_PickUpWeapon_maybe
//   [x] 0x29db70  CKHkS08Enemy_vf23C
//
// The auxiliary state machine (+0x5e8, rows m_pAuxStates) of an enemy without a weapon (State01 starts it at 1 when
// the kind can hold one): 0 the start animation, 1 seek (back off from the target until a free weapon is claimed),
// 2 claim, 3 walk to the claimed weapon, 4 pick it up; 0xff ends it.
#include "Spyro2008/hooks/CKHkS08Enemy.h"

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/components/CKS08EnemyCpnt.h"
#include "Spyro2008/groups/CKGrpS08Enemy.h"
#include "Spyro2008/hooks/CKHkS08EnemyShared.h"
#include "Spyro2008/hooks/CKHkS08Weapon.h"
#include "crt/ppc_ops.h"
#include "k2000/groups/IKBaseGroup.h"
#include "k2000/logic/animation/CKAnimationMarkContainer.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/system/IKTime.h"

namespace {
const RwFrame* HookFrame(IKHook* hook) { return static_cast<CSGMovable*>(hook->m_pKGLObject)->m_pRwFrame; }
}  // namespace

// 0x0029d290 CKHkS08Enemy_AuxSM00_PlayStartAnim_maybe (vt+0x230): enter: the animation 0x2e requested (blend 0.1); run:
// the animation's end over this frame (the dt +0x1fc x the anim speed +0x774) is the next state (1 at its end, else 0).
uint8_t CKHkS08Enemy::AuxState00_PlayStartAnim(IKTime* /*clock*/, int32_t phase, uint8_t /*other*/) {
    if (phase == 0) return IsAnimEndReached(m_fScaledDt * m_unk774, 0, 0) ? 1 : 0;  // 0x00285558
    if (phase == 1) RequestAnim(0x2e, 0, 0, 0, 0.1f, 0.0f);  // 0x00285340; TOC +0x113c / +0x1140
    return 0;
}

// 0x0029d548 CKHkS08Enemy_AuxSM01_SeekWeapon_maybe (vt+0x234): enter: the timer +0x7d0 restarts, the weapon claimed
// before (+0x674, when it is still ours) let go and a free one claimed (FindFreeWeapon). Run: the timer counts to 1 s;
// then 2 once the target (+0x344, a distance) is at least the kind's +0x1ac away (squared); else with a target the move
// direction (+0x388) points away from it and the destination (+0x37c) is 5 units that way.
uint8_t CKHkS08Enemy::AuxState01_SeekWeapon(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    if (phase == 0) {
        const float timer = m_unk7d0;
        if (timer < 1.0f) {  // TOC +0x1150
            m_unk7d0 = timer + clock->m_afDeltaTime[0];
            return 1;
        }
        if (m_unk344 * m_unk344 >= Cfg()->m_unk1ac) return 2;
        if (m_pTarget == nullptr) return 1;
        const RwV3d& target = FrameLtm(HookFrame(m_pTarget))->pos;
        float dx = m_v3Position.x - target.x;
        float dy = m_v3Position.y - target.y;
        float dz = m_v3Position.z - target.z;
        m_unk388 = dx;
        m_unk38c = dy;
        m_unk390 = dz;
        const float length = static_cast<float>(enemy::MathSqrtf(
            static_cast<double>(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)))));  // 0x00010690
        if (length != 0.0f) {  // TOC +0x1140
            const float inv = 1.0f / length;
            dz = inv * m_unk390;
            dx = inv * m_unk388;
            dy = inv * m_unk38c;
            m_unk390 = dz;
            m_unk388 = dx;
            m_unk38c = dy;
        } else {
            dz = m_unk390;
            dx = m_unk388;
            dy = m_unk38c;
        }
        m_unk37c = ppc::fmadds(dx, 5.0f, m_v3Position.x);  // TOC +0x1154
        m_unk384 = ppc::fmadds(dz, 5.0f, m_v3Position.z);
        m_unk380 = ppc::fmadds(dy, 5.0f, m_v3Position.y);
        return 1;
    }
    if (phase == 1) {
        CKHkS08Weapon* claimed = m_pClaimedWeapon;
        m_unk7d0 = 0.0f;
        if (claimed != nullptr && claimed->m_pOwnerB4 == this) claimed->m_pOwnerB4 = nullptr;
        CKHkS08Weapon* weapon = FindFreeWeapon();  // 0x0029d078
        m_pClaimedWeapon = weapon;
        if (weapon != nullptr) weapon->m_pOwnerB4 = this;
    }
    return 1;
}

// 0x0029d760 CKHkS08Enemy_AuxSM02_ClaimWeapon_maybe (vt+0x238): run: the weapon claimed before let go, a free one
// claimed: 3 (walk to it), or none: +0x7f9 = 1 and 0xff (the machine ends). Enter / leave: 2.
uint8_t CKHkS08Enemy::AuxState02_ClaimWeapon(IKTime* /*clock*/, int32_t phase, uint8_t /*other*/) {
    if (phase != 0) return 2;
    CKHkS08Weapon* claimed = m_pClaimedWeapon;
    if (claimed != nullptr && claimed->m_pOwnerB4 == this) claimed->m_pOwnerB4 = nullptr;
    CKHkS08Weapon* weapon = FindFreeWeapon();  // 0x0029d078
    m_pClaimedWeapon = weapon;
    if (weapon != nullptr) {
        weapon->m_pOwnerB4 = this;
        if (m_pClaimedWeapon != nullptr) return 3;
    }
    m_unk7f9 = 1;
    return 0xff;
}

// 0x0029db70 CKHkS08Enemy_vf23C (vt+0x23c, aux state 3): walk to the claimed weapon. Run: 2 when the claim is lost
// (+0x674 null or its +0xb4 not this), the weapon is in a hand (+0xa8), or neither landed (+0xab) nor ejected (+0xaa);
// else the destination is the weapon node's modelling position and the move direction points at it (normalised);
// 4 once the weapon (its LTM) is within the kind's +0x1b0 (squared, in xz), else 3. Enter / leave: 3.
uint8_t CKHkS08Enemy::AuxState03(IKTime* /*clock*/, int32_t phase, uint8_t /*other*/) {
    if (phase != 0) return 3;
    CKHkS08Weapon* weapon = m_pClaimedWeapon;
    if (weapon == nullptr || weapon->m_pOwnerB4 != this || weapon->m_inHandA8 != 0 ||
        (weapon->m_landedAB == 0 && weapon->m_ejectedAA == 0)) {
        return 2;
    }
    const RwV3d& at = HookFrame(weapon)->modelling.pos;
    m_unk37c = at.x;
    m_unk380 = at.y;
    m_unk384 = at.z;
    const RwV3d& again = HookFrame(m_pClaimedWeapon)->modelling.pos;
    const float dy = again.y - m_v3Position.y;
    const float dx = again.x - m_v3Position.x;
    const float dz = again.z - m_v3Position.z;
    m_unk388 = dx;
    m_unk390 = dz;
    m_unk38c = dy;
    const float length = static_cast<float>(enemy::MathSqrtf(
        static_cast<double>(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)))));  // 0x00010690
    if (length != 0.0f) {  // TOC +0x1140
        const float inv = 1.0f / length;  // TOC +0x1150
        m_unk390 = inv * m_unk390;
        m_unk388 = inv * m_unk388;
        m_unk38c = inv * m_unk38c;
    }
    const RwV3d& ltm = FrameLtm(HookFrame(m_pClaimedWeapon))->pos;
    const float ez = m_v3Position.z - ltm.z;
    const float ex = m_v3Position.x - ltm.x;
    if (ppc::fmadds(ex, ex, ez * ez) <= Cfg()->m_unk1b0) return 4;
    return 3;
}

// 0x0029d818 CKHkS08Enemy_AuxSM04_PickUpWeapon_maybe (vt+0x240): enter: the pick-up animation 0x2f (blend 0.1), +0x678
// cleared: 4. Run: without a weapon in hand the claimed one must still be in the weapon group's list (else 2) and not in
// a hand (else 2); the layer 0 animation's mark 0x15 crossed over this frame (its vt+0x1c from max(time - dt, 0) to the
// time) picks it up once (EquipWeapon, the claim cleared, +0x678 = 1, the destination the position, the move
// direction the node's facing, the disarm gauge +0x278 = 0); at the animation's end 0xff with a weapon in hand, else 2.
uint8_t CKHkS08Enemy::AuxState04_PickUpWeapon(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        RequestAnim(0x2f, 0, 0, 0, 0.1f, 0.0f);  // 0x00285340; the original passes phase / other in the unused r5 / r6
        m_unk678 = 0;
        return 4;
    }
    if (phase != 0) return 4;
    if (m_pHeldWeapon == nullptr) {
        if (m_pClaimedWeapon == nullptr) return 2;
        CKGrpS08Enemy* group = static_cast<CKGrpS08Enemy*>(enemy::EnemyGroup());  // 0x00276f58
        IKBaseGroup* weapons = static_cast<IKBaseGroup*>(group->m_pWeaponPool);
        IKHook* hook = *reinterpret_cast<IKHook**>(weapons->GetMemberListHead());  // vt+0xb0
        while (hook != nullptr && hook != m_pClaimedWeapon) hook = hook->m_pNextHook;
        if (hook == nullptr) return 2;
        if (m_pClaimedWeapon->m_inHandA8 != 0) return 2;
    }
    RtAnimAnimation* animation = CurrentLayer0Animation();  // 0x002771c0, 0x002b3128, 0x00285408
    float t0 = GetAnimLayerTime(0, 0) - clock->m_afDeltaTime[0];  // 0x00285388
    if (t0 < 0.0f) t0 = 0.0f;  // TOC +0x1140
    AnimMark* mark = Anim_GetMarkById(animation, 0x15);  // 0x00078830
    if (mark != nullptr && AnimMark_CrossedValueR3(mark, t0, GetAnimLayerTime(0, 0)) != 0 && m_unk678 == 0) {  // vt+0x1c
        EquipWeapon(m_pClaimedWeapon);  // 0x00292a10
        m_pClaimedWeapon = nullptr;
        m_unk678 = 1;
        m_unk37c = m_v3Position.x;
        m_unk380 = m_v3Position.y;
        m_unk384 = m_v3Position.z;
        const RwV3d& at = FrameLtm(static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame)->at;
        m_unk388 = at.x;
        m_unk38c = at.y;
        m_unk390 = at.z;
        m_fDisarmGauge = 0.0f;
    }
    if (!IsAnimEndReached(clock->m_afDeltaTime[0], 0, 0)) return 4;  // 0x00285558
    return m_pHeldWeapon != nullptr ? 0xff : 2;
}

// 0x0029d390 CKHkS08Enemy_DropWeaponOrShield_maybe: with a shield, DropShield; else a held weapon is detached
// (DetachWeapon), the auxiliary machine goes to 1 (seek; no clock), the weapon is ejected (SetEjected(1)) and unowned.
void CKHkS08Enemy::DropWeaponOrShield() {
    if (m_pHeldShield != nullptr) {
        DropShield();  // 0x002915e8
        return;
    }
    CKHkS08Weapon* weapon = m_pHeldWeapon;
    if (weapon == nullptr) return;
    DetachWeapon();  // 0x002916f0
    const uint8_t old = m_auxState;
    if (old != 0xff) CallAuxState(old, nullptr, 2, 1);
    m_auxState = 1;
    CallAuxState(1, nullptr, 1, old);
    weapon->SetEjected(1);  // 0x002b2bc0
    weapon->m_pOwnerB4 = nullptr;
}

// 0x0029d340 StaticInitAndDestruction_29d340: two file statics (0x00cead10, 0x00cead14) set to -1.0f. Nothing in the game
// reads them (their only references are the initialiser's TOC entries).
namespace {
[[maybe_unused]] float s_unkcead10 = -1.0f;
[[maybe_unused]] float s_unkcead14 = -1.0f;
}  // namespace
