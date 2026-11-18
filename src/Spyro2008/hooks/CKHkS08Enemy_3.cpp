// Reconstructed original translation unit: 0x2866d0-0x288688 (GAME_TOC1, main_toc1), 13 functions, 13 live.
// Primary class: CKHkS08Enemy  key 0x26c2  category Hook  size 0x8f8  vtable 0xb22078
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2866d0  CKHkS08Enemy_AdvanceAnimation_maybe
//   [x] 0x2867b8  CKHkS08Enemy_MoveForwardByAnimMarks_maybe
//   [x] 0x286bb8  StaticInitAndDestruction_286bb8 (static init: nothing to port)
//   [x] 0x286be8  _GLOBAL__D_286be8
//   [x] 0x286bf8  _GLOBAL__I_286bf8
//   [x] 0x286c08  CKHkS08Enemy_PlayAnimMarkSounds_maybe
//   [x] 0x286ee0  CKHkS08Enemy_SnapToGround_maybe
//   [x] 0x2871f0  CKHkS08Enemy_UpdateAttackHitWindow_maybe (the projectile launch is a STUB)
//   [x] 0x2878f0  CKHkS08Enemy_HandleAnimMarkEvents_maybe (the FX calls are STUBs / fork calls)
//   [x] 0x288420  CKHkS08Enemy_ProcessAnimMarks_maybe
//   [x] 0x2884b0  CKHkS08Enemy_vf1E8
//   [x] 0x2884b8  CKHkS08Enemy_InitAwarenessStateMachine_maybe
//   [x] 0x2885c8  CKHkS08Enemy_AwareSM01_PlayAlertAnim_maybe
#include "Spyro2008/hooks/CKHkS08Enemy.h"
#include "Spyro2008/misc/CKS08EnemyAbilityHost.h"
#include "k2000/logic/CKAbilityElement.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "k2000/misc/OnNewHit.h"

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/components/CKS08EnemyCpnt.h"
#include "Spyro2008/hooks/CKHkS08Weapon.h"
#include "Spyro2008/logic/CKS08EnemyAttack.h"
#include "Spyro2008/hooks/CKHkS08EnemyShared.h"
#include "k2000/logic/CKProjectileAccessor.h"
#include "k2000/logic/CKProjectileTypeBallisticPFX.h"
#include "crt/ppc_ops.h"
#include "k2000/components/CKEnemySectorCpnt.h"
#include "k2000/core/Stub.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/graphical/CKAnmKeyFrameController.h"
#include "k2000/graphical/animation/CAnimationManager.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/animation/CKAnimationMarkContainer.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/ICollisionMesh.h"

namespace {
// 0x00a70080 (TOC 0xc90): per enemy kind (IKHkEnemy::m_ui8EnemyClassType, 9 kinds): the dynamic hit spheres' count (bytes),
// then three word tables of sector hot spots: +0x0c the projectile muzzle, +0x30 / +0x54 the left / right foot (_maybe:
// the step marks 0x17 / 0x18 use them).
const uint8_t kEnemyDynSphereCount[9] = {2, 3, 3, 2, 3, 3, 3, 3, 2};
const uint32_t kEnemyMuzzleHotSpot[9] = {0, 0, 4, 4, 0, 0, 0, 0, 0};
const uint32_t kEnemyStepHotSpotA[9] = {0, 0, 7, 7, 6, 7, 9, 0, 0};
const uint32_t kEnemyStepHotSpotB[9] = {0, 0, 8, 8, 7, 8, 10, 0, 0};

// The mark's vt+0x1c read as a float (f1), as MoveForwardByAnimMarks does whatever the mark's type (see the note in
// CKAnimationMarkContainer.h): type 0 its constant (0x999980); type 1 an integer slot (0x999950) leaves f1 = t0; type 2
// (0x99a1b8) leaves the wrapped t0; type 3 (0x999e10) the largest key value crossed from t0 to t1 (the float form of
// AnimMarkKeys2_CrossedValue); type 4 (0x999d38 -> vt+0x14 0x99a6b8) the same over the linear interpolation, values at
// t0 and t1 included.
float AnimMark_CrossedValueF1(AnimMark* mark, float t0, float t1) {
    const uint32_t type = mark->GetType();
    if (type == 0) return AnimMark_WordAsFloat(static_cast<AnimMarkConst0*>(mark)->m_value);
    if (type == 1) return t0;
    const AnimMarkKeys* keys = static_cast<const AnimMarkKeys*>(mark);
    t0 = AnimMarkKeys_WrapTime(keys, t0);
    if (type == 2) return t0;
    t1 = AnimMarkKeys_WrapTime(keys, t1);
    const uint32_t count = keys->m_count;
    if (count <= 1) return 0.0f;  // TOC1 -0x6a20
    float previousTime = keys->m_aKeys[0].m_fTime;
    float previousValue = AnimMark_WordAsFloat(keys->m_aKeys[0].m_value);
    if (type == 3) {
        float result = 0.0f;
        for (uint32_t i = 1; i < count; ++i) {
            const float time = keys->m_aKeys[i].m_fTime;
            const float value = AnimMark_WordAsFloat(keys->m_aKeys[i].m_value);
            if (t0 <= time) {
                if (previousTime == t0) {
                    result = previousValue;
                } else if (previousTime <= t0 && t1 >= time) {
                    result = value;
                }
                if (t1 < time) return result;
                if (result < value) result = value;
            }
            previousValue = value;
            previousTime = time;
        }
        return 0.0f;
    }
    // BUG(original): f7 (the result) is not set before the loop; the first crossing sets it in every LVL010 case (the
    // keys start at 0). dotd starts at 0.
    float result = 0.0f;
    for (uint32_t i = 1; i < count; ++i) {
        const float time = keys->m_aKeys[i].m_fTime;
        if (time >= t0) {
            const float value = AnimMark_WordAsFloat(keys->m_aKeys[i].m_value);
            if (previousTime <= t0) {
                const float f = (t0 - previousTime) / (time - previousTime);
                result = ppc::fmadds(f, value - previousValue, previousValue);
            }
            if (time > t1) {
                const float f = (t1 - previousTime) / (time - previousTime);
                const float atEnd = ppc::fmadds(f, value - previousValue, previousValue);
                return result >= atEnd ? result : atEnd;
            }
            if (!(result >= value)) result = value;
        }
        previousTime = time;
        previousValue = AnimMark_WordAsFloat(keys->m_aKeys[i].m_value);
    }
    return 0.0f;
}

}  // namespace

// The mark's vt+0x14 read as an integer (r3), the largest value over [t0, t1]: type 1 its constant (0x999940); type 2
// (0x99a430) the value at t0 (the key before it), the keys crossed and the value before t1 (unsigned); the float types
// leave a pointer in r3 (1).
uint32_t AnimMark_RangeValueR3(AnimMark* mark, float t0, float t1) {
    const uint32_t type = mark->GetType();
    if (type == 1) return static_cast<AnimMarkConst1*>(mark)->m_value;
    if (type != 2) return 1;
    const AnimMarkKeys* keys = static_cast<const AnimMarkKeys*>(mark);
    t0 = AnimMarkKeys_WrapTime(keys, t0);
    t1 = AnimMarkKeys_WrapTime(keys, t1);
    const uint32_t count = keys->m_count;
    if (count <= 1) return 0;
    float previousTime = keys->m_aKeys[0].m_fTime;
    uint32_t previousValue = keys->m_aKeys[0].m_value;
    // BUG(original): the running maximum starts as the key count (the register still holds it) when the first key
    // after t0 has no key at or before t0.
    uint32_t result = count;
    for (uint32_t i = 1; i < count; ++i) {
        const float time = keys->m_aKeys[i].m_fTime;
        if (t0 <= time) {
            const uint32_t value = keys->m_aKeys[i].m_value;
            if (previousTime <= t0) result = previousValue;
            if (t1 < time) return previousValue >= result ? previousValue : result;
            if (result < value) result = value;
        }
        previousTime = time;
        previousValue = keys->m_aKeys[i].m_value;
    }
    return 0;
}

// DOTD: the animation of layer 0's dictionary (current sector) row `GetCurrentAnim(0, 0)` (the original's entry pointer,
// null when the row has none): the anim-mark functions' first lines.
RtAnimAnimation* CKHkS08Enemy::CurrentLayer0Animation() {
    CAnimationDictionary* dictionary = AnimDictionary(GetSectorIndex(), 0);
    return CAnimationManager_GetAnimation(static_cast<uint32_t>(dictionary->m_apAnimations[GetCurrentAnim(0, 0)]));
}

// 0x002866d0 CKHkS08Enemy_AdvanceAnimation_maybe (vt+0x144): with the update flag 0x200 only layer 0 slot 0's crossfade
// steps (dt x +0x774); else the layer update of layer 0 slot 0 (the main state, the current sector) and the flag 0x100
// cleared.
void CKHkS08Enemy::AdvanceAnimation(IKTime* /*clock*/) {
    if ((m_bitArray & 0x200u) != 0) {
        m_unk164[0][0].m_blendSlot.AdvanceInactiveTrack(static_cast<double>(m_unk1fc * m_unk774));
        return;
    }
    const uint8_t state = m_mainState;
    AdvanceAnimLayer(state, GetSectorIndex(), 0, 0);
    m_bitArray &= 0xfffffeffu;  // rlwinm 23 / rotlwi 9
}

// 0x002867b8 CKHkS08Enemy_MoveForwardByAnimMarks_maybe (f1 = t0, f2 = t1): the forward push of the marks 0x0d..0x12 (a
// ramp up to 0x0d, held for 0x0e, down over 0x0f, from the speed 0x10 (taken into +0x350 while it is 0) with the slopes
// 0x11 / 0x12; EvalRampHoldRampDown_maybe 0x27cda8 on the time +0x34c): while it gives a speed, +0x34c advances by dt and
// the enemy moves along its node's facing (at) by speed x dt (+0x158.. the step), the path finding told the position.
void CKHkS08Enemy::MoveForwardByAnimMarks(float t0, float t1) {
    RtAnimAnimation* animation = CurrentLayer0Animation();
    if (animation == nullptr || m_mainState == 0x27) return;
    AnimMark* m0d = Anim_GetMarkById(animation, 0xd);
    AnimMark* m0e = Anim_GetMarkById(animation, 0xe);
    AnimMark* m0f = Anim_GetMarkById(animation, 0xf);
    AnimMark* m10 = Anim_GetMarkById(animation, 0x10);
    AnimMark* m11 = Anim_GetMarkById(animation, 0x11);
    AnimMark* m12 = Anim_GetMarkById(animation, 0x12);
    const float rampEnd = m0d != nullptr ? AnimMark_CrossedValueF1(m0d, t0, t1) : 0.0f;  // TOC 0xc74
    const float hold = m0e != nullptr ? AnimMark_CrossedValueF1(m0e, t0, t1) : 0.0f;
    const float down = m0f != nullptr ? AnimMark_CrossedValueF1(m0f, t0, t1) : 0.0f;
    float base = 0.0f;
    if (m10 != nullptr) {
        base = AnimMark_CrossedValueF1(m10, t0, t1);
        if (m_unk350 == 0.0f) m_unk350 = base;
    }
    const float slope = m11 != nullptr ? AnimMark_CrossedValueF1(m11, t0, t1) : 0.0f;
    const float downSlope = m12 != nullptr ? AnimMark_CrossedValueF1(m12, t0, t1) : 0.0f;
    if (EvalRampHoldRampDown(m_unk34c, rampEnd, hold, down, base, slope, downSlope, &m_unk350) == 0) return;
    m_unk34c = m_unk34c + m_unk1fc;
    const RwFrame* frame = static_cast<const CSGMovable*>(m_pKGLObject)->m_pRwFrame;
    const float ax = frame->modelling.at.x;
    const float ay = frame->modelling.at.y;
    const float az = frame->modelling.at.z;
    m_unk158.x = ax;
    m_unk158.z = az;
    m_unk158.y = ay;
    const float step = m_unk350 * m_unk1fc;
    const float dx = step * ax;
    const float dz = step * az;
    const float dy = step * ay;
    m_unk158.x = dx;
    m_unk158.z = dz;
    m_unk158.y = dy;
    m_v3Position.x = m_v3Position.x + dx;
    m_v3Position.y = m_v3Position.y + dy;
    m_v3Position.z = m_v3Position.z + dz;
    m_PFCpnt.SetDestination(&m_v3Position);  // 0x001e3a40 CKPathFindingCpnt_ResetCurrentPosition
}

// 0x00286c08 CKHkS08Enemy_PlayAnimMarkSounds_maybe (f1 = t0, f2 = t1): when the mark 0x19 is crossed: in the states 0x16,
// 0, 0x17, 0x18 the FX 0 at the position (not kind 8) and the sound 0x12 (0x16 / 0x17) or 0x13 (0 / 0x18) once (+0x888),
// +0x7c4 = 0 / 1; in the attack states (IsEnemyInDeathStates_maybe: 0x0d..0x0f) the sound 0 the first time (+0x890),
// then 1.
void CKHkS08Enemy::PlayAnimMarkSounds(float t0, float t1) {
    RtAnimAnimation* animation = CurrentLayer0Animation();
    if (animation == nullptr) return;
    AnimMark* mark = Anim_GetMarkById(animation, 0x19);
    if (mark == nullptr || AnimMark_CrossedValueR3(mark, t0, t1) == 0) return;
    const uint8_t state = m_mainState;
    if (state == 0x16 || state == 0 || state == 0x17 || state == 0x18) {
        if (m_ui8EnemyClassType != 8) SpawnHitFxAt(0, &m_v3Position);
        const uint8_t now = m_mainState;
        if (now == 0x16 || now == 0x17) {
            if (m_unk888 == 0) {
                PlaySound(0x12, 0, m_pKGLObject);  // TOC 0xc88
                m_unk888 = 1;
            }
            m_unk7c4 = 0;
        } else {
            if (m_unk888 == 0) {
                PlaySound(0x13, 0, m_pKGLObject);
                m_unk888 = 1;
            }
            m_unk7c4 = 1;
        }
        return;
    }
    if (IsInDeathStates() == 0) return;
    if (m_unk890 != 0) {
        PlaySound(1, 0, m_pKGLObject);
        return;
    }
    PlaySound(0, 0, m_pKGLObject);
    m_unk890 = 1;
}

// 0x00286ee0 CKHkS08Enemy_SnapToGround_maybe: the height offset of the mark 0x16 (its value at layer 0's time), the
// ground under the position (the enemy's contact pair, GroundProbePoints_maybe): none (status 0) in a fall / hurt state
// drops the offset; standing (+0x7b4 / +0x744 clear) the position goes down by the distance; else (in the air) back to
// +0x794 (not in the states 1, 0x23, 0x27) and probed again: within reach (status 1 or 2) up by the distance. A ground
// within reach that is not a slide (flag 0x200) lifts the position and clears +0x744 / +0x7b4 (not kind 8). The offset is
// added outside the attack states, or in them when the attack's +0x64 is not 3.
void CKHkS08Enemy::SnapToGround() {
    RtAnimAnimation* animation = CurrentLayer0Animation();
    if (animation == nullptr) return;
    if (m_mainState == 0xe) {
        if ((m_ui8EnemyClassType == 1 || m_ui8EnemyClassType == 8) && m_unk7b4 != 0) return;
    } else if (m_mainState == 0x27) {
        return;
    }
    float offset = 0.0f;  // TOC 0xc74
    AnimMark* mark = Anim_GetMarkById(animation, 0x16);
    if (mark != nullptr) offset = AnimMark_ValueAtF1(mark, GetAnimLayerTime(0, 0));  // vt+0x10
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &m_v3Position.x, 1);
    const uint32_t status = m_GrdContDatasInOut.m_eContactStatus;
    if (status == 0) {
        const uint8_t react = m_reactState;
        const uint8_t state = m_mainState;
        if (react == 8 || react == 6 || react == 2 || state == 0x25 || state == 7 || state == 0x1d) {
            offset = 0.0f;
        } else if (m_unk7b4 == 0 && m_unk744 == 0) {
            m_v3Position.y = m_v3Position.y - m_GrdContDatasInOut.m_fdH;
        } else {
            if (state != 1 && state != 0x23 && state != 0x27) m_v3Position.y = m_unk794;
            collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &m_v3Position.x, 1);
            const uint32_t again = m_GrdContDatasInOut.m_eContactStatus;
            if (again == 1 || again == 2) m_v3Position.y = m_v3Position.y + m_GrdContDatasInOut.m_fdH;
        }
    } else if (static_cast<int32_t>(status) >= 0 && static_cast<int32_t>(status) <= 2) {
        const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(m_GrdContDatasInOut.m_pGround);
        if (ground != nullptr && (ground->m_ui16PropertiesFlags & 0x200u) == 0) {
            m_v3Position.y = m_v3Position.y + m_GrdContDatasInOut.m_fdH;
            if (m_ui8EnemyClassType != 8) {
                m_unk744 = 0;
                m_unk7b4 = 0;
            }
        }
    }
    if (IsInDeathStates() != 0) {
        if (m_unk73c == nullptr || m_unk73c->m_unk64 == 3) return;
    }
    m_v3Position.y = offset + m_v3Position.y;
}

// 0x002871f0 CKHkS08Enemy_UpdateAttackHitWindow_maybe (f1 = t0, f2 = t1): the attack volumes by the mark 0x13 (+0x7cc
// cleared first). Without an attack or with an attack of type 2 (+0x08): the mark crossed (vt+0x1c), the volume group 3 off
// and every hit sphere released; then with an attack and the mark crossed, +0x7cc set and the attack's projectile launched
// from the kind's muzzle hot spot towards the target (+0x330). With another attack: the mark's value now (vt+0x14) 0: group
// 3 off and the spheres released unless in a hurt / grab / wind state; non-zero: the attack volumes on and the spheres the
// attack flags (+0x54) given the attack's damage (+0x20) — all of them while +0x709 is set in an attack state.
void CKHkS08Enemy::UpdateAttackHitWindow(float t0, float t1) {
    RtAnimAnimation* animation = CurrentLayer0Animation();
    m_unk7cc = 0;
    if (animation == nullptr || m_mainState == 7) return;
    AnimMark* mark = Anim_GetMarkById(animation, 0x13);
    uint32_t value = 0;
    if (mark != nullptr) value = AnimMark_RangeValueR3(mark, t0, t1);  // vt+0x14
    const uint8_t kind = m_ui8EnemyClassType;
    if (m_unk73c != nullptr && m_unk73c->m_unk08 != 2) {
        if (value == 0) {
            DisableVolumeGroup(3);  // vt+0xfc
            const uint8_t react = m_reactState;
            const uint8_t state = m_mainState;
            if (react == 8 || react == 6 || state == 8 || state == 7 || state == 0x1d) return;
            const uint8_t count = kEnemyDynSphereCount[kind];
            for (uint32_t i = 0; i != count; ++i) ReleaseDynSphere(static_cast<uint8_t>(i));  // vt+0x10c
            return;
        }
        EnableAttackVolumes();  // 0x0027d708
        const uint8_t count = kEnemyDynSphereCount[kind];
        for (uint32_t i = 0; i < count; ++i) {
            if (m_unk73c->m_array54.m_data[i] == 0) continue;
            EnableCollisionSphere(i);  // vt+0x108
            if (m_unk73c != nullptr) static_cast<IKBoundingVolume*>(m_apBVProj[i])->m_unk1c = m_unk73c->m_pDamage;
        }
        if (m_unk709 != 0 && IsInDeathStates() != 0) {
            for (uint32_t i = 0; i < count; ++i) {
                EnableCollisionSphere(i);
                if (m_unk73c != nullptr) static_cast<IKBoundingVolume*>(m_apBVProj[i])->m_unk1c = m_unk73c->m_pDamage;
            }
        }
        return;
    }
    if (mark != nullptr) value = AnimMark_CrossedValueR3(mark, t0, t1);  // vt+0x1c
    DisableVolumeGroup(3);
    const uint8_t count = kEnemyDynSphereCount[kind];
    for (uint32_t i = 0; i != count; ++i) ReleaseDynSphere(static_cast<uint8_t>(i));
    if (m_unk73c == nullptr || value == 0) return;
    m_unk7cc = 1;
    // 0x2874ec: the attack's projectile (its accessor +0x40; a type of class 0x140c, CKProjectileTypeBallisticPFX) from
    // the kind's muzzle hot spot toward the target's hot spot (a hero's 4, an enemy's sector hot spot 1). LVL010: the
    // eight CKS08EnemyAttack accessors have no type (census objects-lvl010_ingame), so it ends here.
    CKProjectileAccessor* accessor = m_unk73c->m_pProjectile;
    if (accessor == nullptr) return;  // DOTD: CKS08EnemyAttack_Load keeps only an accessor (the original reads +0x04 of it)
    IKProjectileType* type = static_cast<IKProjectileType*>(accessor->m_pProjectileType);
    if (type == nullptr) return;
    CVector3 muzzle{};
    static_cast<CSGHotSpot*>(m_unk18C[GetSectorIndex()]->GetHotSpot(kEnemyMuzzleHotSpot[m_ui8EnemyClassType]))
        ->GetWorldPosition(&muzzle);  // 0x002b31e0, 0x000ce790
    if (type->IsKindOfClass(0x140c) == 0) return;  // vt+0x08
    CVector3 target{0.0f, 0.0f, 0.0f};  // TOC +0xc94 0x00c50d64
    if (m_unk330->IsKindOfClass(CKHkS08Hero::kClassKey) != 0) {
        CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(static_cast<IKSerializable*>(m_unk330));
        hero->GetDragonIndex();  // 0x00361960 (its result unused)
        static_cast<CSGHotSpot*>(hero->GetHotSpot(4))->GetWorldPosition(&target);  // 0x00361b70
    } else if (m_unk330->IsKindOfClass(0x26c2) != 0) {
        static_cast<CSGHotSpot*>(static_cast<CKHkS08Enemy*>(static_cast<IKSerializable*>(m_unk330))->GetSectorHotSpot(1))
            ->GetWorldPosition(&target);  // 0x0028a160
    }
    if (target.x != 0.0f || target.y != 0.0f || target.z != 0.0f) {
        CVector3 dir{target.x - muzzle.x, target.y - muzzle.y, target.z - muzzle.z};
        const float length =
            static_cast<float>(enemy::MathSqrtf(ppc::fmadds(dir.z, dir.z, ppc::fmadds(dir.x, dir.x, dir.y * dir.y))));
        if (length != 0.0f) {
            const float k = 1.0f / length;  // TOC +0xc88
            dir.z = dir.z * k;
            dir.x = dir.x * k;
            dir.y = dir.y * k;
        }
        accessor->LaunchEx(&muzzle, &dir, m_unk73c->m_unk44, m_unk73c->m_pDamage, this, nullptr);  // 0x001f2988
    }
    // 0x2876c8: the projectile at the active count (the type's list +0x04) carries the attack's damage on its volume.
    if (type->m_ui8NbOfActiveProjectiles >= type->m_ui8MaxProjectiles) return;
    auto* projectile =
        static_cast<CKProjectileTypeBallisticPFX::Projectile*>(type->m_apProjectileList[type->m_ui8NbOfActiveProjectiles]);
    if (projectile == nullptr || projectile->m_pVolume == nullptr) return;
    static_cast<IKBoundingVolume*>(projectile->m_pVolume)->m_unk1c = m_unk73c->m_pDamage;
}

// 0x002878f0 CKHkS08Enemy_HandleAnimMarkEvents_maybe (f1 = t0, f2 = t1): the animation's event marks. Grabbed (main or
// hit-reaction state 7, the animation then the active track's evaluated one): the mark 0x14 crossed (+0x77c) gives the
// grab impact FX (and the hero's hit counter). Otherwise the steps (marks 0x17 / 0x18): the surface FX at the foot hot spot
// and a footstep sound 0x18 + (rand >> 14) & 3 (one Rand_Int per crossing for the kinds 0..4, 7, 8; for the kinds 5 and 6
// only outside the attack strike 0x0d, with a landing FX, the ground probed and the sound 0x2a first); then the mark 0x14:
// the kind 5's weapon impact (and its electric grapple), the kind 6's two impacts (+0x818 set), the kind 4's +0x819 set.
void CKHkS08Enemy::HandleAnimMarkEvents(float t0, float t1) {
    CAnimationDictionary* dictionary = AnimDictionary(GetSectorIndex(), 0);
    RtAnimAnimation* animation;
    if (m_mainState == 7) {
        animation = ActiveTrack(m_unk164[0][0])->m_unk5c;
    } else {
        animation = CAnimationManager_GetAnimation(static_cast<uint32_t>(dictionary->m_apAnimations[GetCurrentAnim(0, 0)]));
    }
    if (animation == nullptr) return;
    if (m_mainState == 7 || m_reactState == 7) {
        AnimMark* grab = Anim_GetMarkById(animation, 0x14);
        if (grab == nullptr) {
            m_unk77c = 0;
            return;
        }
        const uint32_t crossed = AnimMark_CrossedValueR3(grab, t0, t1);
        m_unk77c = crossed;
        if (crossed == 0) return;
        if (m_mainState == 7) {
            CVector3 point;
            static_cast<CSGHotSpot*>(GetHotSpot(1))->GetWorldPosition(&point);
            static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)
                ->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &point.x, 1);
            point.y = point.y - m_GrdContDatasInOut.m_fdH;
            SpawnHitFxAt(0x19, &point);
            return;
        }
        if (m_unk834 == 0) {
            SpawnHitFxAt(0x18, &m_v3Position);
            return;
        }
        // The last attacker (+0x694) when it is a hero (key 0x25c2): the game manager's hit counter at the position.
        IKSerializable* attacker = static_cast<IKSerializable*>(m_unk694);
        if (attacker != nullptr && attacker->IsKindOfClass(0x25c2) != 0) {  // vt+0x08
            const CVector3 at = m_v3Position;
            OnNewHitW(static_cast<CKS08GameManager*>(g_pEngine->m_gameManager),
                      static_cast<CKHkS08Hero*>(attacker)->GetDragonIndex(), &at);  // 0x00361960, 0x004fe568
        }
        SpawnHitFxAt(0x1f, &m_v3Position);
        return;
    }
    AnimMark* stepA = Anim_GetMarkById(animation, 0x17);
    AnimMark* stepB = Anim_GetMarkById(animation, 0x18);
    AnimMark* impact = Anim_GetMarkById(animation, 0x14);
    uint32_t a = 0;
    if (stepA != nullptr) a = AnimMark_CrossedValueR3(stepA, t0, t1);
    uint32_t b = 0;
    if (stepB != nullptr) b = AnimMark_CrossedValueR3(stepB, t0, t1);
    uint32_t c = 0;
    if (impact != nullptr) c = AnimMark_CrossedValueR3(impact, t0, t1);
    const uint8_t kind = m_ui8EnemyClassType;
    if (a + b != 0 && kind <= 8) {
        const uint64_t bit = 1ull << kind;
        const uint32_t hotSpot = a != 0 ? kEnemyStepHotSpotA[kind] : kEnemyStepHotSpotB[kind];
        bool step = false;
        uint32_t surfaceMode = 0;
        if ((bit & 0x83u) != 0) {
            step = true;
            surfaceMode = 0;
        } else if ((bit & 0x11cu) != 0) {
            step = true;
            surfaceMode = 1;
        } else if ((bit & 0x60u) != 0 && (kind == 6 || m_mainState != 0xd)) {
            CVector3 point;
            static_cast<CSGHotSpot*>(static_cast<CKEnemySectorCpnt*>(m_unk18C[GetSectorIndex()])->m_apUnk14[hotSpot])
                ->GetWorldPosition(&point);
            static_cast<CKS08GameManager*>(g_pEngine->m_gameManager)->SpawnSurfaceFx(1.0f, this, GetGroundSurfaceType(), 2, &point.x);  // 0x004f9628; TOC 0xc88
            static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)
                ->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &point.x, 1);
            point.y = point.y - m_GrdContDatasInOut.m_fdH;
            SpawnHitFxAt(0x13, &point);
            PlaySound(0x2a, 0, m_pKGLObject);  // TOC 0xc88
            const uint32_t r = static_cast<uint32_t>(Rand_Int());
            PlaySound(static_cast<uint8_t>(((r >> 14) & 3u) + 0x18), 0, m_pKGLObject);
        }
        if (step) {
            CVector3 point;
            static_cast<CSGHotSpot*>(static_cast<CKEnemySectorCpnt*>(m_unk18C[GetSectorIndex()])->m_apUnk14[hotSpot])
                ->GetWorldPosition(&point);
            static_cast<CKS08GameManager*>(g_pEngine->m_gameManager)->SpawnSurfaceFx(1.0f, this, GetGroundSurfaceType(), surfaceMode, &point.x);  // 0x004f9628
            const uint32_t r = static_cast<uint32_t>(Rand_Int());
            PlaySound(static_cast<uint8_t>(((r >> 14) & 3u) + 0x18), 0, m_pKGLObject);
        }
    }
    if (c == 0) return;
    uint8_t now = m_ui8EnemyClassType;
    if (now == 5) {
        if (m_unk520 == nullptr) return;
        CVector3 point;
        // the weapon (+0x520)'s hot spot: the second entry of its +0xac array
        static_cast<CSGHotSpot*>(m_unk520->m_apUnkAC[1])->GetWorldPosition(&point);
        static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)
            ->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &point.x, 1);
        point.y = point.y - m_GrdContDatasInOut.m_fdH;
        SpawnHitFxAt(0x14, &point);
        if (m_ui8EnemyClassType == 5 && m_unk73c != nullptr && m_unk73c->m_unk24 == 4) {
            SpawnHitFxAt(0x17, &point);
            if (m_unk780 == nullptr && IsInDeathStates() != 0) {
                // 0x288074: the kind 5 starts its ability (+0x784) through a new host.
                m_unk780 = new CKS08EnemyAbilityHost(this);  // OperatorNew(8) + 0x002c6878
                if (m_unk784 != nullptr) {
                    m_unk819 = 0;
                    m_unk818 = 0;
                    static_cast<CKAbilityElement*>(m_unk784)->Start(m_unk780);  // vt+0x58
                }
            }
        }
        PlaySound(0x2b, 0, m_pKGLObject);
        now = m_ui8EnemyClassType;
    }
    if (now == 6) {
        CVector3 left;
        CVector3 right;
        static_cast<CSGHotSpot*>(GetHotSpot(2))->GetWorldPosition(&left);
        static_cast<CSGHotSpot*>(GetHotSpot(0xf))->GetWorldPosition(&right);
        CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
        collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &left.x, 1);
        left.y = left.y - m_GrdContDatasInOut.m_fdH;
        collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &right.x, 1);
        right.y = right.y - m_GrdContDatasInOut.m_fdH;
        SpawnHitFxAt(0x14, &left);
        SpawnHitFxAt(0x14, &right);
        PlaySound(0x2b, 0, m_pKGLObject);
        now = m_ui8EnemyClassType;
        m_unk818 = 1;
    }
    if (now == 4) m_unk819 = 1;
}

// 0x00288420 CKHkS08Enemy_ProcessAnimMarks_maybe: layer 0 slot 0's active track: the marks crossed from its evaluated
// time (+0x54, last frame's) to its time now (+0x50): events, attack window, forward push.
void CKHkS08Enemy::ProcessAnimMarks() {
    CKAnmKeyFrameController* track = ActiveTrack(m_unk164[0][0]);
    const float now = track->m_unk50;
    const float before = track->m_unk54;
    HandleAnimMarkEvents(before, now);
    UpdateAttackHitWindow(before, now);
    MoveForwardByAnimMarks(before, now);
}

// 0x002885c8 CKHkS08Enemy_AwareSM01_PlayAlertAnim_maybe: entering requests the row 0x34 (crossfade 0.1 from 0); running:
// the state 2 once its end is reached (dt x +0x774), else 1.
uint8_t CKHkS08Enemy::AwareState01_PlayAlertAnim(IKTime* /*clock*/, int32_t phase, uint8_t /*other*/) {
    if (phase == 0) return IsAnimEndReached(m_unk1fc * m_unk774, 0, 0) ? 2 : 1;
    if (phase == 1) RequestAnim(0x34, 0, 0, 0, 1.0e-1f, 0.0f);  // TOC 0xce8 / 0xcec
    return 1;
}

// 0x002884b0 CKHkS08Enemy_vf1E8: returns 2.
uint8_t CKHkS08Enemy::AwareState02(IKTime* /*clock*/, int32_t /*phase*/, uint8_t /*other*/) {
    return 2;
}

// 0x002884b8 CKHkS08Enemy_InitAwarenessStateMachine_maybe: 3 rows, state 0 entered at once (clock null, from 0xff).
void CKHkS08Enemy::InitAwarenessStateMachine() {
    m_aAwareStates[0][0] = 0x1e1;
    m_aAwareStates[2][0] = 0x1e9;
    m_aAwareStates[1][0] = 0x1e5;
    m_aAwareStates[0][1] = 0;
    m_aAwareStates[1][1] = 0;
    m_aAwareStates[2][1] = 0;
    m_awareStateCount = 3;
    m_pAwareStates = &m_aAwareStates[0][0];
    m_awareState = 0;
    CallAwareState(0, nullptr, 1, 0xff);
}
