//
// Reconstructed original translation unit: 0x2c5e00-0x2c6d50 (GAME_TOC1, main_toc1), 69 functions, 68 live.
// Primary owner: CKS08EnemyAbilityHost (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2c5e00  CKS08EnemyAbilityHost_maybe_Construct_2 (the constructor's twin)
//   [x] 0x2c5e78  CKS08EnemyAbilityHost_maybe_GetOwner
//   [x] 0x2c5e80  CKS08EnemyAbilityHost_maybe_GetOwnerPosition
//   [x] 0x2c5eb0  CKS08EnemyAbilityHost_maybe_vf20
//   [x] 0x2c5ed0  CKS08EnemyAbilityHost_maybe_vf24
//   [x] 0x2c5f28  CKS08EnemyAbilityHost_maybe_vf38
//   [x] 0x2c5f30  CKS08EnemyAbilityHost_maybe_vf3C
//   [x] 0x2c5f38  CKS08EnemyAbilityHost_maybe_vf40
//   [x] 0x2c5f40  CKS08EnemyAbilityHost_maybe_vf44
//   [x] 0x2c5f48  CKS08EnemyAbilityHost_maybe_vf50
//   [x] 0x2c5f50  CKS08EnemyAbilityHost_maybe_vf54
//   [x] 0x2c5f58  CKS08EnemyAbilityHost_maybe_vf5C
//   [x] 0x2c5f60  CKS08EnemyAbilityHost_maybe_vf60
//   [x] 0x2c5f68  CKS08EnemyAbilityHost_maybe_vf48
//   [x] 0x2c5f70  CKS08EnemyAbilityHost_maybe_vf64
//   [x] 0x2c5f78  CKS08EnemyAbilityHost_maybe_vf68
//   [x] 0x2c5f80  CKS08EnemyAbilityHost_maybe_vf70
//   [x] 0x2c5f88  CKS08EnemyAbilityHost_maybe_GetOwnerConfigValue1D4_maybe
//   [x] 0x2c5f98  CKS08EnemyAbilityHost_maybe_vf6C
//   [x] 0x2c5fa0  CKS08EnemyAbilityHost_maybe_vf78
//   [x] 0x2c5fa8  CKS08EnemyAbilityHost_maybe_vf84
//   [x] 0x2c5fb0  CKS08EnemyAbilityHost_maybe_vf88
//   [x] 0x2c5fb8  CKS08EnemyAbilityHost_maybe_vf90
//   [x] 0x2c5fc0  CKS08EnemyAbilityHost_maybe_vf9C
//   [x] 0x2c5fc8  CKS08EnemyAbilityHost_maybe_vfA0
//   [x] 0x2c5fd0  CKS08EnemyAbilityHost_maybe_vfA4
//   [x] 0x2c5fd8  CKS08EnemyAbilityHost_maybe_vfA8
//   [x] 0x2c5fe0  CKS08EnemyAbilityHost_maybe_vfAC
//   [x] 0x2c5fe8  CKS08EnemyAbilityHost_maybe_GetCollisionGroup
//   [x] 0x2c5ff0  CKS08EnemyAbilityHost_maybe_GetCollisionMask
//   [x] 0x2c5ff8  CKS08EnemyAbilityHost_maybe_GetAbilityMana
//   [x] 0x2c6008  CKS08EnemyAbilityHost_maybe_GetDamageScale
//   [x] 0x2c6010  CKS08EnemyAbilityHost_maybe_GetEffectScale
//   [x] 0x2c6018  CKS08EnemyAbilityHost_maybe_AimAtTarget_maybe
//   [x] 0x2c6060  CKS08EnemyAbilityHost_maybe_vfE8
//   [x] 0x2c6068  CKS08EnemyAbilityHost_maybe_vfF0
//   [x] 0x2c6070  CKS08EnemyAbilityHost_maybe_GetAbilityLevelIndex
//   [x] 0x2c6078  CKS08EnemyAbilityHost_maybe_vfF8
//   [x] 0x2c6080  CKS08EnemyAbilityHost_maybe_vfFC
//   [x] 0x2c6088  CKS08EnemyAbilityHost_maybe_vf104
//   [x] 0x2c6090  CKS08EnemyAbilityHost_maybe_Destructor
//   [x] 0x2c60a0  CKS08EnemyAbilityHost_maybe_GetOwnerGroundPoint_maybe
//   [x] 0x2c60e0  CKS08EnemyAbilityHost_maybe_IsOnGround_maybe
//   [x] 0x2c6110  CKS08EnemyAbilityHost_maybe_SetOwnerPosition
//   [x] 0x2c6138  CKS08EnemyAbilityHost_maybe_CanGrab_maybe
//   [x] 0x2c6160  CKS08EnemyAbilityHost_maybe_GetGrabHotspot_maybe
//   [x] 0x2c61f8  CKS08EnemyAbilityHost_maybe_GetLockedTarget
//   [x] 0x2c6238  CKS08EnemyAbilityHost_maybe_ConsumeAbilityMana
//   [x] 0x2c6250  CKS08EnemyAbilityHost_maybe_vf4C
//   [x] 0x2c6278  CKS08EnemyAbilityHost_maybe_vf58
//   [x] 0x2c62a0  CKS08EnemyAbilityHost_maybe_GetOwnerForward_maybe
//   [x] 0x2c62d8  StaticInitAndDestruction_2c62d8  (the two file statics in the namespace below)
//   [ ] 0x2c6308  _GLOBAL__D_2c6308
//   [ ] 0x2c6318  _GLOBAL__I_2c6318
//   [x] 0x2c6328  CKS08EnemyAbilityHost_maybe_GetAbilityButtonHoldTime_maybe
//   [x] 0x2c63a0  CKS08EnemyAbilityHost_maybe_GetTargetPoint_maybe
//   [x] 0x2c6420  CKS08EnemyAbilityHost_maybe_GetOwnerUp_maybe
//   [x] 0x2c6458  CKS08EnemyAbilityHost_maybe_GetOwnerRight_maybe
//   [x] 0x2c6490  CKS08EnemyAbilityHost_maybe_GetHotspot
//   [x] 0x2c65f8  CKS08EnemyAbilityHost_maybe_IsAbilityButtonDown_maybe
//   [x] 0x2c6690  CKS08EnemyAbilityHost_maybe_IsProjectileChargeHeld_maybe
//   [x] 0x2c6758  CKS08EnemyAbilityHost_maybe_GetTargetAimPoint_maybe
//   [x] 0x2c67c8  CKS08EnemyAbilityHost_maybe_GetOwnerFlatForward_maybe
//   [x] 0x2c6878  CKS08EnemyAbilityHost_maybe_Construct
//   [x] 0x2c68f0  CKS08EnemyAbilityHost_maybe_PlayAbilityAnim
//   [x] 0x2c6978  CKS08EnemyAbilityHost_maybe_IsAbilityAnimPhaseDone_maybe
//   [ ] 0x2c6a40  CKS08EnemyAbilityHost_maybe_Destructor_2  [dead]
//   [x] 0x2c6a50  CKS08EnemyAbilityHost_maybe_DeletingDestructor
//   [x] 0x2c6a80  CKS08EnemyAbilityHost_maybe_GetHotspotPosition
//
//   [x] 0x9bd050  KStub_ReturnFloat1_9bd050  [inline] (CKS08AbilityHostBase.h)
//   [x] 0x9bd058  KStub_ReturnFloat1_9bd058  [inline] (CKS08AbilityHostBase.h)
//   [x] 0x9bd060  KStub_Return1_9bd060  [inline] (CKS08AbilityHostBase.h)
//   [x] 0x9bd068  CKS08AbilityHostBase_maybe_DeletingDestructor  [inline] (CKS08AbilityHostBase.h)
//   [x] 0x9bd098  CKS08AbilityHostBase_maybe_Destructor  [inline] (CKS08AbilityHostBase.h)
#include "Spyro2008/misc/CKS08EnemyAbilityHost.h"

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/components/CKS08EnemyCpnt.h"
#include "Spyro2008/hooks/CKHkS08Enemy.h"
#include "Spyro2008/hooks/CKHkS08EnemyShared.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/hooks/CKHkS08Weapon.h"
#include "Spyro2008/logic/CKS08EnemyAttack.h"
#include "crt/ppc_ops.h"
#include "k2000/components/CKEnemySectorCpnt.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/scenegraph/CSGMovable.h"

namespace {
// The enemy's node frame (+0x1c, its +0x04).
RwFrame* NodeFrame(const IKSerializable* hook) {
    return static_cast<CSGMovable*>(static_cast<const IKHook*>(hook)->m_pKGLObject)->m_pRwFrame;
}
// The weapon's (+0x520) first reference (+0xac, its +0x04: the muzzle hot spot of kinds 4 / 5).
CSGHotSpot* WeaponHotSpot(CKHkS08Enemy* enemy) {
    return static_cast<CSGHotSpot*>(static_cast<CKHkS08Weapon*>(enemy->m_unk520)->m_apUnkAC[1]);
}

// 0x002c62d8 StaticInitAndDestruction_2c62d8 (_GLOBAL__I_2c6318): two file statics (0x00cead9c, 0x00ceada0) set to
// -1.0f. Nothing in the game reads them.
[[maybe_unused]] float s_unkcead9c = -1.0f;
[[maybe_unused]] float s_unkceada0 = -1.0f;
}  // namespace

// 0x002c6878 CKS08EnemyAbilityHost_maybe_Construct
CKS08EnemyAbilityHost::CKS08EnemyAbilityHost(IKSerializable* enemy) {
    if (enemy->IsKindOfClass(0x26c2) != 0) m_pEnemy = static_cast<CKHkS08Enemy*>(enemy);  // vt+0x08
}

// 0x002c5e78 CKS08EnemyAbilityHost_maybe_GetOwner
IKSerializable* CKS08EnemyAbilityHost::GetOwner() { return m_pEnemy; }

// 0x002c6110 CKS08EnemyAbilityHost_maybe_SetOwnerPosition
void CKS08EnemyAbilityHost::SetOwnerPosition(const CVector3* position) { m_pEnemy->SetPosition(position); }  // 0x00289718

// 0x002c5e80 CKS08EnemyAbilityHost_maybe_GetOwnerPosition
CVector3 CKS08EnemyAbilityHost::GetOwnerPosition() { return m_pEnemy->m_v3Position; }

// 0x002c60a0 CKS08EnemyAbilityHost_maybe_GetOwnerGroundPoint_maybe
CVector3 CKS08EnemyAbilityHost::GetOwnerGroundPoint() { return m_pEnemy->ComputeGroundPoint(); }  // 0x00289e60

// 0x002c62a0 CKS08EnemyAbilityHost_maybe_GetOwnerForward_maybe: the stored LTM's at row.
CVector3 CKS08EnemyAbilityHost::GetHeroForward() {
    const RwV3d& at = FrameLtm(NodeFrame(m_pEnemy))->at;
    return CVector3{at.x, at.y, at.z};
}

// 0x002c67c8 CKS08EnemyAbilityHost_maybe_GetOwnerFlatForward_maybe: the LTM's at with y 0, unit length (fmadds from
// 0.0; Math_Sqrtf; TOC +0x1964 1.0 / length).
CVector3 CKS08EnemyAbilityHost::GetHeroVec135c() {
    const RwV3d& at = FrameLtm(NodeFrame(m_pEnemy))->at;
    CVector3 out{at.x, 0.0f, at.z};
    const float length =
        static_cast<float>(enemy::MathSqrtf(ppc::fmadds(out.z, out.z, ppc::fmadds(out.x, out.x, 0.0f))));  // 0x00010690
    if (length != 0.0f) {
        const float k = 1.0f / length;
        const float z = k * out.z;
        const float x = k * out.x;
        const float y = k * out.y;
        out = CVector3{x, y, z};
    }
    return out;
}

// 0x002c5ed0 CKS08EnemyAbilityHost_maybe_vf24: the forward (vt+0x18).
CVector3 CKS08EnemyAbilityHost::GetAimDirection(int32_t /*raw*/) { return GetHeroForward(); }

// 0x002c6458 CKS08EnemyAbilityHost_maybe_GetOwnerRight_maybe
CVector3 CKS08EnemyAbilityHost::GetOwnerRight() {
    const RwV3d& right = FrameLtm(NodeFrame(m_pEnemy))->right;
    return CVector3{right.x, right.y, right.z};
}

// 0x002c6420 CKS08EnemyAbilityHost_maybe_GetOwnerUp_maybe
CVector3 CKS08EnemyAbilityHost::GetOwnerUp() {
    const RwV3d& up = FrameLtm(NodeFrame(m_pEnemy))->up;
    return CVector3{up.x, up.y, up.z};
}

// 0x002c60e0 CKS08EnemyAbilityHost_maybe_IsOnGround_maybe
uint8_t CKS08EnemyAbilityHost::IsAirborne() { return m_pEnemy->IsOnGround(); }  // 0x00289a98

// 0x002c6250 CKS08EnemyAbilityHost_maybe_vf4C: the null vector (TOC +0x1984 0x00c50d64).
CVector3 CKS08EnemyAbilityHost::GetOwnerVelocity() { return CVector3{0.0f, 0.0f, 0.0f}; }

// 0x002c6278 CKS08EnemyAbilityHost_maybe_vf58: the null vector.
CVector3 CKS08EnemyAbilityHost::ComputeAimDirection(float /*cone*/, CKAbilityElement* /*ability*/,
                                                    IKSerializable* /*aimCone*/) {
    return CVector3{0.0f, 0.0f, 0.0f};
}

// 0x002c5f88 CKS08EnemyAbilityHost_maybe_GetOwnerConfigValue1D4_maybe: IKHkEnemy's kind component (+0x188), its +0x1d4.
float CKS08EnemyAbilityHost::GetOwnerConfig74() { return m_pEnemy->m_unk188->m_unk1d4; }

// 0x002c68f0 CKS08EnemyAbilityHost_maybe_PlayAbilityAnim (a jump table on the phase, unsigned: above 4 answers 1)
uint8_t CKS08EnemyAbilityHost::PlayAbilityAnim(CKAbilityElement* /*ability*/, uint32_t phase) {
    const uint8_t state = m_pEnemy->m_mainState;
    switch (phase) {
        case 0:
        case 3:
            return state == 0xd ? 1 : 0;
        case 1:
        case 2:
        case 4:
            if (state == 0xe) return 1;
            return state == 0xf ? 1 : 0;
        default:
            return 1;
    }
}

// 0x002c6978 CKS08EnemyAbilityHost_maybe_IsAbilityAnimPhaseDone_maybe (a jump table; above 4 answers 0)
uint8_t CKS08EnemyAbilityHost::IsAbilityAnimPhaseDone(CKAbilityElement* /*ability*/, uint32_t phase) {
    switch (phase) {
        case 0: {
            const uint8_t kind = m_pEnemy->m_ui8EnemyClassType;
            if (kind != 7 && kind != 0) return 1;
            return m_pEnemy->m_mainState != 0xd ? 1 : 0;
        }
        case 1:
        case 2:
        case 4: {
            const uint8_t state = m_pEnemy->m_mainState;
            if (state == 0xe) return 0;
            return state != 0xf ? 1 : 0;
        }
        case 3:
            return m_pEnemy->m_mainState != 0xd ? 1 : 0;
        default:
            return 0;
    }
}

// 0x002c65f8 CKS08EnemyAbilityHost_maybe_IsAbilityButtonDown_maybe
uint8_t CKS08EnemyAbilityHost::IsAbilityButtonDown(int32_t /*button*/) {
    CKHkS08Enemy* enemy = m_pEnemy;
    const uint8_t kind = enemy->m_ui8EnemyClassType;
    if (kind == 5 || kind == 2 || enemy->m_unk73c == nullptr) return 1;
    if (enemy->m_unk73c->m_unk08 == 2 && (kind == 3 || kind == 8)) return enemy->m_unk7cc;
    if (kind != 4) return 1;
    // srawi / xor / subf / srwi 31: the flags are not zero.
    return enemy->GetAbilityInputFlags() != 0 ? 1 : 0;  // 0x00288fc8
}

// 0x002c6328 CKS08EnemyAbilityHost_maybe_GetAbilityButtonHoldTime_maybe (TOC +0x1964 1.0)
uint8_t CKS08EnemyAbilityHost::GetAbilityButtonHoldTime(int32_t /*button*/, float* held) {
    const CKHkS08Enemy* enemy = m_pEnemy;
    const uint8_t kind = enemy->m_ui8EnemyClassType;
    if (kind == 5) return 1;
    if (kind == 2) {
        *held = 1.0f;
        return 1;
    }
    if (kind == 7 || kind == 0) {
        if (enemy->m_mainState == 0xd) return 0;
    } else if (enemy->m_mainState != 0xd) {
        return 0;
    }
    *held = 1.0f;
    return 1;
}

// 0x002c63a0 CKS08EnemyAbilityHost_maybe_GetTargetPoint_maybe: kind 5 the node frame's modelling at (+0x30).
CVector3 CKS08EnemyAbilityHost::GetTargetPoint(float* weight) {
    if (m_pEnemy->m_ui8EnemyClassType != 5) {
        *weight = 0.0f;
        return CVector3{0.0f, 0.0f, 0.0f};
    }
    *weight = 1.0f;
    const RwV3d& at = NodeFrame(m_pEnemy)->modelling.at;
    return CVector3{at.x, at.y, at.z};
}

// 0x002c6238 CKS08EnemyAbilityHost_maybe_ConsumeAbilityMana: ((kind ^ 1) - 1) >> 63.
uint32_t CKS08EnemyAbilityHost::ConsumeAbilityMana(CKAbilityElement* /*ability*/, uint32_t /*amount*/) {
    return m_pEnemy->m_ui8EnemyClassType == 1 ? 1u : 0u;
}

// 0x002c6490 CKS08EnemyAbilityHost_maybe_GetHotspot (a switch on the logical hot spot; above 6: none)
IKSerializable* CKS08EnemyAbilityHost::GetHotspot(uint32_t index) {
    CKHkS08Enemy* enemy = m_pEnemy;
    switch (index) {
        case 0:
            if (enemy->m_ui8EnemyClassType == 1) enemy->GetHotSpot(5);  // its result unused (0x2c64d0)
            return m_pEnemy->GetHotSpot(1);
        case 1:
        case 3:
            return enemy->GetHotSpot(1);
        case 2: {
            const uint8_t kind = enemy->m_ui8EnemyClassType;
            if (kind == 3) return enemy->GetHotSpot(4);
            if (kind == 4 || kind == 5) return WeaponHotSpot(enemy);
            if (kind != 0) return enemy->GetHotSpot(0);
            return enemy->GetHotSpot(2);
        }
        case 4:
            return enemy->GetHotSpot(2);
        case 5:
        case 6:
            return enemy->GetHotSpot(0);
        default:
            return nullptr;
    }
}

// 0x002c6a80 CKS08EnemyAbilityHost_maybe_GetHotspotPosition (TOC +0x19a0 0.5, +0x19a4 0.3)
CVector3 CKS08EnemyAbilityHost::GetHotspotPosition(uint32_t index) {
    CKHkS08Enemy* enemy = m_pEnemy;
    const uint8_t kind = enemy->m_ui8EnemyClassType;
    if (kind == 6) {
        CVector3 a{};
        CVector3 b{};
        static_cast<CSGHotSpot*>(enemy->m_unk18C[enemy->GetSectorIndex()]->GetHotSpot(9))->GetWorldPosition(&a);
        static_cast<CSGHotSpot*>(m_pEnemy->m_unk18C[m_pEnemy->GetSectorIndex()]->GetHotSpot(10))->GetWorldPosition(&b);
        const float x = (a.x + b.x) * 0.5f;
        const float z = (a.z + b.z) * 0.5f;
        const CVector3 ground = m_pEnemy->ComputeGroundPoint();  // 0x00289e60
        return CVector3{x, ground.y + 0.3f, z};
    }
    if (kind == 4) {
        CVector3 at{};
        WeaponHotSpot(enemy)->GetWorldPosition(&at);
        const CVector3 ground = m_pEnemy->ComputeGroundPoint();
        return CVector3{at.x, ground.y + 0.3f, at.z};
    }
    if (kind == 5) {
        CVector3 at{};
        WeaponHotSpot(enemy)->GetWorldPosition(&at);
        return at;
    }
    CSGHotSpot* spot = static_cast<CSGHotSpot*>(GetHotspot(static_cast<uint8_t>(index)));  // vt+0xcc (clrldi 0x38)
    if (spot == nullptr) return CVector3{0.0f, 0.0f, 0.0f};
    CVector3 at{};
    spot->GetWorldPosition(&at);  // 0x000ce790
    return at;
}

// 0x002c61f8 CKS08EnemyAbilityHost_maybe_GetLockedTarget
IKSerializable* CKS08EnemyAbilityHost::GetLockedTarget() {
    const uint8_t kind = m_pEnemy->m_ui8EnemyClassType;
    if (kind == 4 || kind == 3 || kind == 7 || kind == 0) return m_pEnemy->m_unk330;
    return nullptr;
}

// 0x002c6758 CKS08EnemyAbilityHost_maybe_GetTargetAimPoint_maybe: the target's node frame, its stored LTM position.
CVector3 CKS08EnemyAbilityHost::GetTargetAimPoint(int32_t /*fromHotSpot*/, uint8_t /*clampHeight*/) {
    if (m_pEnemy->m_unk330 == nullptr) return CVector3{0.0f, 0.0f, 0.0f};
    const RwV3d& pos = FrameLtm(NodeFrame(m_pEnemy->m_unk330))->pos;
    return CVector3{pos.x, pos.y, pos.z};
}

// 0x002c6160 CKS08EnemyAbilityHost_maybe_GetGrabHotspot_maybe
IKSerializable* CKS08EnemyAbilityHost::GetGrabHotspot(CKAbilityElement* /*ability*/) {
    const uint8_t kind = m_pEnemy->m_ui8EnemyClassType;
    if ((kind == 7 || kind == 0) && m_pEnemy->GetTargetHero() != nullptr) {  // 0x00289060
        return static_cast<CKHkS08Hero*>(m_pEnemy->GetTargetHero())->GetHotSpot(5);  // 0x00361b70
    }
    return nullptr;
}

// 0x002c6138 CKS08EnemyAbilityHost_maybe_CanGrab_maybe
uint8_t CKS08EnemyAbilityHost::GrabEnemy(CKAbilityElement* /*ability*/, uint8_t /*grab*/, uint8_t /*mode*/,
                                         const CVector3* /*direction*/, IKSerializable* /*damage*/,
                                         IKSerializable* /*target*/) {
    const uint8_t kind = m_pEnemy->m_ui8EnemyClassType;
    return (kind == 7 || kind == 0) ? 1 : 0;
}

// 0x002c6690 CKS08EnemyAbilityHost_maybe_IsProjectileChargeHeld_maybe: a bit table on the kind (below 9).
uint8_t CKS08EnemyAbilityHost::IsProjectileChargeHeld(CKAbilityElement* /*ability*/) {
    const CKHkS08Enemy* enemy = m_pEnemy;
    const uint8_t kind = enemy->m_ui8EnemyClassType;
    if (kind >= 9) return 1;
    const uint32_t bit = 1u << kind;
    if ((bit & 0x150u) != 0) {  // kinds 4, 6, 8
        if (enemy->m_mainState == 0xd) return 1;
        if (kind == 4) return enemy->m_unk819;
        if (kind != 8) return enemy->m_unk818;
        return enemy->m_unk7cc;
    }
    if ((bit & 0x81u) != 0) return enemy->m_mainState != 0xd ? 1 : 0;  // kinds 0, 7
    if ((bit & 8u) == 0) return 1;                                     // kinds 1, 2, 5
    if (enemy->m_mainState == 0xd) return 0;                           // kind 3
    return enemy->m_unk7cc;
}
