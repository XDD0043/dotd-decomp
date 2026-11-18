// CKHkS08Enemy_9.cpp - reconstructed original translation unit 0x294b68-0x29d290 (GAME_TOC1, main_toc1), 31 functions, 31 live.
// Primary class: CKHkS08Enemy  key 0x26c2  category Hook  size 0x8f8  vtable 0xb22078
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x294b68  CKHkS08Enemy_MessageProc
//   [ ] 0x294d20  CKHkS08Enemy_Save
//   [x] 0x2951a0  CKHkS08Enemy_Load
//   [x] 0x2962b8  CKHkS08Enemy_Update
//   [x] 0x297160  CKHkS08Enemy_vf210
//   [x] 0x297168  CKHkS08Enemy_vf214
//   [x] 0x297170  CKHkS08Enemy_PendingDamageCausesHitReaction_maybe
//   [x] 0x297250  CKHkS08Enemy_InitHitReactionStateMachine_maybe
//   [x] 0x297408  StaticInitAndDestruction_297408  (the two file statics at the end)
//   [ ] 0x297438  _GLOBAL__D_297438
//   [ ] 0x297448  _GLOBAL__I_297448
//   [x] 0x297458  CKHkS08Enemy_vf21C
//   [x] 0x297568  CKHkS08Enemy_ReactSM0B_GetUp_maybe
//   [x] 0x2977c0  CKHkS08Enemy_ReactSM01_Burning_maybe
//   [x] 0x297950  CKHkS08Enemy_PlayDirectionalHurtAnim_maybe
//   [x] 0x298430  CKHkS08Enemy_UpdateHurtAnimPlayback_maybe
//   [x] 0x2987c8  CKHkS08Enemy_IntegrateKnockbackMotion_maybe
//   [x] 0x298d68  CKHkS08Enemy_ReactSM10_KnockbackAnim_maybe
//   [x] 0x298e08  CKHkS08Enemy_ReactSM00_DispatchHit_maybe
//   [x] 0x298ff0  CKHkS08Enemy_ReactSM05_Stunned_maybe
//   [x] 0x299188  CKHkS08Enemy_ReactSM04_StunGaugeDrain_maybe
//   [x] 0x2993e8  CKHkS08Enemy_ReactSM06_Airborne_maybe
//   [x] 0x299708  CKHkS08Enemy_ReactSM03_HurtCheckStun_maybe
//   [x] 0x2998d0  CKHkS08Enemy_ReactSM02_Hurt_maybe
//   [x] 0x299f30  CKHkS08Enemy_ApplyPendingDamage
//   [x] 0x29bd40  CKHkS08Enemy_ReactSM0F_DeathAnim_maybe
//   [x] 0x29c018  CKHkS08Enemy_ReactSM0D_maybe
//   [x] 0x29c148  CKHkS08Enemy_ReactSM0E_FallUntilGrounded_maybe
//   [x] 0x29c350  CKHkS08Enemy_ReactSM08_Launched_maybe
//   [x] 0x29c998  CKHkS08Enemy_ReactSM07_Knockdown_maybe
//   [x] 0x29d078  CKHkS08Enemy_FindFreeWeapon
#include "k2000/graphical/CKAnmKeyFrameController.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/logic/animation/CKAnimationMarkContainer.h"
#include "k2000/ai/CKSrvPathFinding.h"
#include "Spyro2008/groups/CKGrpS08Enemy.h"
#include "Spyro2008/hooks/CKHkS08EnemyShared.h"
#include "Spyro2008/hooks/CKHkS08Enemy.h"
#include "Spyro2008/misc/CKS08EnemyAbilityHost.h"
#include "k2000/logic/CKAbilityElement.h"
#include "Spyro2008/hooks/CKHkS08Weapon.h"
#include "k2000/groups/IKBaseGroup.h"
#include "Renderware/rpprtstd/RpPrtStd.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"

#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "Spyro2008/components/CKS08EnemyCpnt.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "Spyro2008/logic/CKS08ElementDamage.h"
#include "k2000/misc/ClassRegistry.h"
#include "crt/ppc_ops.h"
#include "k2000/components/CKEnemySectorCpnt.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CollisionDatas.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/groups/CKGrpSquad.h"
#include "k2000/services/ICollisionMesh.h"
#include "k2000/system/IKTime.h"

#include "k2000/core/Stub.h"
#include "platform/log.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

namespace {
// 0x00a701d8 (TOC +0x105c): the reference count per enemy kind (IKHkEnemy::m_ui8EnemyClassType), read only
// by CKHkS08Enemy_Load. 16 bytes before the next object (0xa701e8); nine kinds_maybe.
const uint8_t kEnemyRefCount[16] = {3, 1, 5, 4, 5, 7, 9, 0, 4, 0, 0, 0, 0, 0, 0, 0};

// The inlined TVector reserve: a vector without a block gets one element (capacity 1).
template <class T>
void EnsureBlock(TVector<T, 1>& vector) {
    if (vector.m_pBlock == nullptr) {
        vector.m_ui32NbElt = 1;
        vector.m_pBlock = static_cast<T*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(T))));
    }
}

// The inlined resize to count elements: the block grows to count + 1 when the capacity is below count.
template <class T>
void Resize(TVector<T, 1>& vector, uint32_t count) {
    EnsureBlock(vector);
    if (vector.m_ui32NbElt < count) {
        uint32_t capacity = count + 1;
        if (capacity == 0) capacity = 1;
        vector.m_pBlock = static_cast<T*>(
            Mem_ReallocAligned16(vector.m_pBlock, capacity * static_cast<uint32_t>(sizeof(T))));
        vector.m_ui32NbElt = capacity;
    }
    vector.m_ui32NbUsedElt = count;
}

// The inlined push of a null element (growth step 1).
void PushNull(TVector<void*, 1>& vector) {
    if (vector.m_ui32NbElt == vector.m_ui32NbUsedElt) {
        uint32_t capacity = vector.m_ui32NbUsedElt + 1;
        if (capacity == 0) capacity = 1;
        vector.m_pBlock = static_cast<void**>(
            Mem_ReallocAligned16(vector.m_pBlock, capacity * static_cast<uint32_t>(sizeof(void*))));
        vector.m_ui32NbElt = capacity;
    }
    vector.m_pBlock[vector.m_ui32NbUsedElt] = nullptr;
    vector.m_ui32NbUsedElt++;
}

// One reference vector: the file's count, the vector sized by the kind's count. The first min of the two
// references go into the vector; extra file references are read and dropped; missing ones are nulls.
// With `nulls`, every element (read, dropped or nulled) also pushes a null into it.
void ReadRefVector(IKFile* file, TVector<IKSerializable*, 1>& vector, uint32_t kindCount,
                   TVector<void*, 1>* nulls) {
    uint32_t count = 0;
    ReadU32LE(file, &count);
    Resize(vector, kindCount);
    if (kindCount < count) {
        for (uint32_t i = 0; i < kindCount; ++i) {
            IKFile_ReadRef(file, &vector.m_pBlock[i]);
            if (nulls != nullptr) PushNull(*nulls);
        }
        for (uint32_t i = kindCount; i < count; ++i) {
            IKSerializable* dropped = nullptr;
            IKFile_ReadRef(file, &dropped);
            if (nulls != nullptr) PushNull(*nulls);
        }
    } else {
        for (uint32_t i = 0; i < count; ++i) {
            IKFile_ReadRef(file, &vector.m_pBlock[i]);
            if (nulls != nullptr) PushNull(*nulls);
        }
        for (uint32_t i = count; i < kindCount; ++i) {
            vector.m_pBlock[i] = nullptr;
            if (nulls != nullptr) PushNull(*nulls);
        }
    }
}
}  // namespace

// 0x002951a0 CKHkS08Enemy_Load. No branch on the type after IKHkEnemy's part.
int32_t CKHkS08Enemy::Load(IKFile* file, int32_t type) {
    IKHkEnemy::Load(file, type);
    EnsureBlock(m_unk4E4);
    EnsureBlock(m_unk4F0);
    EnsureBlock(m_unk4FC);
    EnsureBlock(m_unk508);
    EnsureBlock(m_unk514);
    ReadRefVector(file, m_unk4E4, kEnemyRefCount[m_ui8EnemyClassType], &m_unk514);
    ReadU8(file, &m_unk730);
    IKFile_ReadRef(file, &m_unk734);
    IKFile_ReadRef(file, &m_unk784);
    ReadRefVector(file, m_unk4F0, kEnemyRefCount[m_ui8EnemyClassType], nullptr);
    ReadRefVector(file, m_unk4FC, kEnemyRefCount[m_ui8EnemyClassType], nullptr);
    ReadRefVector(file, m_unk508, kEnemyRefCount[m_ui8EnemyClassType], nullptr);
    IKFile_ReadRef(file, &m_unk88C);
    return 1;
}

// 0x00294b68 CKHkS08Enemy_MessageProc: IKHkEnemy's (0x278020 IKHkEnemy_HandleMessage: 1), then the messages 0x0400
// (data: hot spot 1's world position into +0x04..+0x0c) and 0x0402 (data: one byte, IsValidCombatTarget_maybe). The
// answers combine: 3 wins, then 2 (handled without data), then the base's 0, else 0 when handled and 1 when not.
int32_t CKHkS08Enemy::MessageProc(uint16_t message, void* data) {
    const int32_t base = IKHkEnemy::MessageProc(message, data);
    int32_t own = 1;
    if (((message >> 8) & 0xffu) == 4) {
        const uint32_t low = message & 0xffu;
        if (low == 0) {
            if (data == nullptr) {
                own = 2;
            } else {
                CVector3 position;
                static_cast<CSGHotSpot*>(GetHotSpot(1))->GetWorldPosition(&position);
                float* out = reinterpret_cast<float*>(static_cast<uint8_t*>(data) + 4);
                out[0] = position.x;
                out[2] = position.z;
                out[1] = position.y;
                own = 0;
            }
        } else if (low == 2) {
            if (data == nullptr) {
                own = 2;
            } else {
                *static_cast<uint8_t*>(data) = IsValidCombatTarget() != 0 ? 1 : 0;
                own = 0;
            }
        }
    }
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    if (base == 0) return 0;
    return own == 0 ? 0 : 1;  // ((own - 1) >> 31) ^ 1
}

// DOTD: the inlined test of the pending damage (+0x27c) in the status updates and Update: +0x239 (a hit this frame) set
// when `requireHit`, the damage a CKS08ElementDamage (key 0x99cc, vt+0x08) and its element (+0x20) `element`.
bool CKHkS08Enemy::PendingElementDamageIs(int32_t element) {
    if (m_unk239 == 0) return false;
    if (m_unk27c->IsKindOfClass(0x99cc) == 0) return false;
    return static_cast<int32_t>(m_unk27c->m_unk20) == element;
}

// 0x002962b8 CKHkS08Enemy_Update (vt+0x7c). Nothing for a frame without time. The object at vt+0xec (this + 0x1c4) whose
// +0x24 is -1 sends the enemy to the main state 0x16 (unless in it, without a state or grabbed) and clears the update skip
// bit 3; with bit 3 set nothing more. Then: dt x the time scale (+0x200) into +0x1fc, +0x710 set; the electric grapple
// (+0x780) released outside the attack states; for the kind 1 its +0x7a8 point moved towards +0x79c by at most +0x4b0 x dt
// (outside the state 1) and the sector's animated node placed there; IKHkEnemy_Update, the contacts (vt+0x134), the burn
// sound 0x1c while a fire element damage (+0x38 13) is pending, the status effects, the damage transitions (vt+0x128) and,
// when they did not take over, the targeting (vt+0x12c, every +0xc0 seconds of +0x1f4); the main state machine; the
// shadow and aura FX (vt+0x140), the animation (vt+0x144: not in the states 0x17 with +0x7e4 set, 0x27, nor with +0x6fc /
// +0x750), the off-nav flag, the attackers' hit cooldowns (vt+0x138), the anim marks, the carrier (vt+0x74); a living,
// grounded enemy with a status gauge (or a stun / freeze element damage, or in state 1) goes to the hit reaction 0x0f and
// the main state 2 (kinds 5 / 6 not from 0x15 or 2), the others to the main state 0x15; the node placed (state 0: the
// position and the yaw +0x154; else vt+0x13c); +0x899 / +0x239 cleared; the boss gauge.
void CKHkS08Enemy::Update(IKTime* clock) {
    const float dt = clock->m_afDeltaTime[0];  // +0x1c
    if (dt <= 0.0f) return;                    // TOC 0x1068 0.0f
    // vt+0xec: this + 0x1c4; its word +0x24 (+0x1e8, kept as four bytes here) is -1.
    if (m_unk1e8 == 0xff && m_unk1e9 == 0xff && m_unk1ea == 0xff && m_unk1eb == 0xff) {
        const uint8_t state = m_mainState;
        if (state != 0x16 && state != 0xff && m_unk294 == 0) SwitchMainState(0x16, clock);
        m_bitArray &= 0xfffffff7u;  // rlwinm 28 / rotlwi 4
    }
    if ((m_bitArray & 8u) != 0) return;
    m_unk1fc = clock->m_afDeltaTime[0] * m_unk200;
    m_unk710 = 1;
    if (m_unk780 != nullptr) {
        const uint8_t state = m_mainState;
        if (state != 0xd && state != 0xe && state != 0xf) {
            // 0x2963b4: out of the attack states the ability is stopped and the host deleted.
            if (m_unk784 != nullptr) {
                m_unk819 = 0;
                m_unk818 = 0;
                static_cast<CKAbilityElement*>(m_unk784)->Stop(0);  // vt+0x5c
            }
            delete m_unk780;  // vt+0x04
            m_unk780 = nullptr;
        }
    }
    if (m_ui8EnemyClassType == 1) {
        float x = m_unk7a8;
        float y = m_unk7ac;
        float z = m_unk7b0;
        const bool zero = x == 0.0f && y == 0.0f && z == 0.0f;  // the zero vector 0xc50d64 (TOC 0x1058)
        if (!zero && m_mainState != 1) {
            const float tx = m_unk79c;
            const float ty = m_unk7a0;
            const float tz = m_unk7a4;
            if (!(tx == x && y == ty && z == tz)) {
                const float dy = ty - y;
                const float dx = tx - x;
                const float maxStep = m_unk884->m_unk4b0 * clock->m_afDeltaTime[0];
                const float dz = tz - z;
                const float d2 = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
                if (maxStep * maxStep > d2) {
                    x = tx;
                    z = tz;
                    y = ty;
                } else {
                    const float k = maxStep * rwInvSqrt(d2);  // 0x000114d8 Math_InvSqrtf
                    z = ppc::fmadds(dz, k, z);
                    x = ppc::fmadds(dx, k, x);
                    y = ppc::fmadds(dy, k, y);
                }
            }
            m_unk7b0 = z;
            m_unk7a8 = x;
            m_unk7ac = y;
            // CKEnemySectorCpnt_GetAnimatedNode 0x2b3110: the current sector component's +0x04 entry 0.
            CKEnemySectorCpnt* cpnt = static_cast<CKEnemySectorCpnt*>(m_unk18C[GetSectorIndex()]);
            RwFrame* frame = static_cast<CSGMovable*>(cpnt->m_apUnk04[0])->m_pRwFrame;
            frame->modelling.pos.z = m_unk7b0;
            frame->modelling.pos.x = m_unk7a8;
            frame->modelling.pos.y = m_unk7ac;
            frame->modelling.flags &= 0xfffdffffu;
            RwFrame_MarkDirty(frame);  // 0x00010698
        }
    }
    IKHkEnemyUpdate(clock);   // 0x00277650
    ProcessContacts(clock);   // vt+0x134
    if (m_unk874 == 0) {
        if (m_unk239 != 0 && m_unk27c != nullptr && m_unk27c->IsKindOfClass(0x99cc) != 0 &&
            static_cast<CKS08ElementDamage*>(m_unk27c)->m_unk38 == 0xd) {
            m_unk874 = 1;
            PlaySound(0x1c, 1, m_pKGLObject);  // TOC 0x1060
        }
    } else {
        const bool burning = m_unk27c != nullptr && m_unk239 != 0 && m_unk27c->IsKindOfClass(0x99cc) != 0 &&
                             static_cast<CKS08ElementDamage*>(m_unk27c)->m_unk38 == 0xd;
        if (!burning) {
            m_unk874 = 0;
            StopSound(0x1c);  // 0x002794f0
        }
    }
    UpdateStatusEffects(clock);  // 0x00288a38
    uint8_t busy;
    if (ProcessDamageStateTransitions(clock) != 0) {  // vt+0x128
        busy = m_unk6fc;
    } else {
        busy = m_unk6fc;
        if (busy == 0 && (static_cast<uint32_t>(m_PFCpnt.m_unk3c) & 0x40u) == 0 && m_unk1f4 <= 0.0f) {
            if (IsInDeathStates() == 0) {
                UpdateTargetAndDestination(clock);  // vt+0x12c
                busy = m_unk6fc;
                m_unk1f4 = m_unk1f4 + m_unk884->m_unkc0;
            } else {
                busy = m_unk6fc;
            }
        }
    }
    if (busy == 0) {
        const uint8_t state = m_mainState;
        if (state != 0xff) {
            const uint8_t next = CallMainState(state, clock, 0, state);
            const uint8_t now = m_mainState;
            if (next != now) {
                if (now != 0xff) CallMainState(now, clock, 2, next);
                m_mainState = next;
                if (next != 0xff) CallMainState(next, clock, 1, now);
            }
        }
    }
    UpdateShadowAndAuraFx();  // vt+0x140
    if (m_unk6fc == 0 && m_unk750 == 0) {
        const uint8_t state = m_mainState;
        if (state == 0x17) {
            if (m_unk7e4 == 0.0f) AdvanceAnimation(clock);  // vt+0x144
        } else if (state != 0x27) {
            AdvanceAnimation(clock);
        }
    }
    UpdateOffNavFlag();                  // 0x00280ca0
    UpdateAttackerHitCooldowns(clock);   // vt+0x138
    ProcessAnimMarks();                  // 0x00288420
    CallCarrierUpdate(clock);            // the carrier (+0x734) vt+0x74
    uint8_t state = m_mainState;
    bool react = false;
    bool dying = false;
    if (state != 0xff && state != 0x15 && m_reactState != 0xf) {
        bool eligible;
        if (!(m_unk258 <= 0.0f) || m_unk294 != 0) {
            const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(m_GrdContDatasInOut.m_pGround);
            eligible = m_unk7b4 == 0 && ground != nullptr && (ground->m_ui16PropertiesFlags & 0x200u) != 0 &&
                       m_GrdContDatasInOut.m_eContactStatus != 0;
        } else {
            eligible = true;
        }
        if (eligible && state != 0x27) {
            bool gauged = m_unk6c8 > 0.0f || m_unk6b8 > 0.0f || m_unk6c0 > 0.0f;
            if (!gauged && m_unk27c != nullptr && m_unk27c->IsKindOfClass(0x99cc) != 0) {
                const int32_t element = static_cast<int32_t>(m_unk27c->m_unk20);
                if (element == 5 || element == 7) gauged = true;
            }
            state = m_mainState;
            if (gauged) {
                if (static_cast<uint8_t>(m_ui8EnemyClassType - 5) <= 1) {
                    react = state != 0x15 && state != 2;
                } else {
                    dying = state != 0x15;
                }
            } else {
                react = state == 1;
            }
        }
    }
    if (react) {
        const uint8_t old = m_reactState;
        if (old != 0xff) CallReactState(old, nullptr, 2, 0xf);
        m_reactState = 0xf;
        CallReactState(0xf, nullptr, 1, old);
        SwitchMainState(2, nullptr);
    } else if (dying) {
        SwitchMainState(0x15, nullptr);
    }
    state = m_mainState;
    if (state != 0x15) {
        if (state == 0) {
            RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
            frame->modelling.pos.z = m_v3Position.z;
            frame->modelling.pos.x = m_v3Position.x;
            frame->modelling.pos.y = m_v3Position.y;
            frame->modelling.flags &= 0xfffdffffu;
            RwFrame_MarkDirty(frame);
            float yaw;  // +0x154 the yaw
            yaw = m_unk154;
            RwFrame* frame2 = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
            Mat4_SetRotationAboutAxis(yaw, reinterpret_cast<CMatrix34*>(&frame2->modelling), 1);  // 0x00241688
            RwFrame_MarkDirty(frame2);
        } else {
            ResolveGroundAndApplyTransform(clock);  // vt+0x13c
        }
    }
    m_unk899 = 0;
    m_unk239 = 0;
    if (m_unk898 != 0 && m_awareState == 2) {
        // A boss enemy (+0x898) in combat: the boss gauge (the kind's +0xcc as both maxima, the health +0x258).
        CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
        manager->SetEnemyGaugeMaxHealth(m_unk884->m_unkcc);   // 0x004fea60
        manager->SetEnemyGaugeMaxHealth2(m_unk884->m_unkcc);  // 0x004fe9c0
        manager->SetBossGaugeHealth(m_unk258);                // 0x004feb00
        manager->RefreshBossGauge();                          // 0x00501ea0
    }
}

namespace {
// The element damages (+0x38 of a CKS08ElementDamage) that make a plain hit reaction (DispatchHit 0x298e08,
// PendingDamageCausesHitReaction 0x297170): 0, 3, 4, 5, 6, 0x0a, 0x0b, 0x0c, 0x0e, 0x0f.
bool IsPlainHitElement(int32_t element) {
    return element == 0 || element == 3 || element == 4 || element == 5 || element == 6 || element == 0xb ||
           element == 0xa || element == 0xf || element == 0xc || element == 0xe;
}
}  // namespace

// 0x00297170 CKHkS08Enemy_PendingDamageCausesHitReaction_maybe: 1 unless the pending damage is a CKS08ElementDamage of
// another element.
uint8_t CKHkS08Enemy::PendingDamageCausesHitReaction() {
    if (m_unk27c->IsKindOfClass(0x99cc) == 0) return 1;
    return IsPlainHitElement(static_cast<CKS08ElementDamage*>(m_unk27c)->m_unk38) ? 1 : 0;
}

// 0x00298e08 CKHkS08Enemy_ReactSM00_DispatchHit_maybe: the idle hit-reaction state. Running with a hit this frame
// (+0x239): the update flag 0x10000 and +0x354 cleared (not kinds 5 / 6); a plain hit: the kind 5 to the death reaction 7
// once its health is gone (else stays), the kind 6 stays, the others probe the ground: in the air above 0.3 the airborne
// reaction 6, else the hurt reaction 2; another element: only the kind 5 (7 when dead). Leaving it, the kind 1 stops its
// sounds 0x2a / 0x2b. 0 otherwise.
uint8_t CKHkS08Enemy::ReactState00_DispatchHit(IKTime* /*clock*/, int32_t phase, uint8_t /*other*/) {
    if (phase == 2) {
        if (m_ui8EnemyClassType == 1) {
            StopSound(0x2a);  // 0x002794f0
            StopSound(0x2b);
        }
        return 0;
    }
    if (phase != 0 || m_unk239 == 0) return 0;
    if (static_cast<uint8_t>(m_ui8EnemyClassType - 5) > 1) {
        m_bitArray &= 0xfffeffffu;  // rlwinm 15 / rotlwi 17
        m_unk354 = 0;               // stb r5 (the phase, 0)
    }
    const bool plain = m_unk27c->IsKindOfClass(0x99cc) == 0 ||
                       IsPlainHitElement(static_cast<CKS08ElementDamage*>(m_unk27c)->m_unk38);
    const uint8_t kind = m_ui8EnemyClassType;
    if (!plain && kind != 5) return 0;
    if (kind == 5) return m_unk258 <= 0.0f ? 7 : 0;  // TOC 0x1098
    if (kind == 6) return 0;
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)
        ->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &m_v3Position.x, 1);
    if (m_GrdContDatasInOut.m_eContactStatus == 0 && m_GrdContDatasInOut.m_fdH > 3.0e-1f) return 6;  // TOC 0x10dc
    return 2;
}

// 0x002977c0 CKHkS08Enemy_ReactSM01_Burning_maybe (vt+0x1f0): enter: with the burning gauge (+0x6b8) at least the kind's
// +0x244, animation 0 requested (blend 0.1) and the first particle node (+0x54[0]) lit: its properties gain 0x400 and
// lose 0x80000, its emission speed adjustment 0, its emitter's flags | 0xa. Run: 1 while the gauge is above 0 (NaN
// too), else 0. Leave: the gauge 0, the node's 0x400 / 0x80000 cleared and its emitter stops (flag 8 cleared). 1.
uint8_t CKHkS08Enemy::ReactState01_Burning(IKTime* /*clock*/, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        if (m_unk6b8 >= Cfg()->m_unk244) {
            RequestAnim(0, 0, 0, 0, 0.1f, 0.0f);  // 0x00285340; TOC +0x109c / +0x1098
            CParticlesNodeFx* particles = static_cast<CParticlesNodeFx*>(m_apParticleNodeFx[0]);
            particles->m_sgProperties = (particles->m_sgProperties | 0x400u) & ~0x80000u;
            particles->m_fEmissionSpeedAdjustment = 0.0f;
            particles->m_pRpPrtStdEmitter->flag |= 0xau;
        }
        return 1;
    }
    if (phase == 2) {
        m_unk6b8 = 0.0f;
        CParticlesNodeFx* particles = static_cast<CParticlesNodeFx*>(m_apParticleNodeFx[0]);
        particles->m_sgProperties &= 0xfff7fbffu;
        particles->m_pRpPrtStdEmitter->flag &= ~0x8u;  // rpPRTSTDEMITTERFLAGEMIT
        return 1;
    }
    if (phase == 0) return (m_unk6b8 <= 0.0f) ? 0 : 1;  // TOC +0x1098
    return 1;
}

namespace {
// 0x00a701e8 (TOC +0x10e4): per enemy kind, the death animation of the death reaction (0xf); 0: the kind has none (a
// kill on flat ground plays the reaction only when it is non-zero).
constexpr uint32_t kKindDeathOnGround[9] = {0x41, 0, 0x43, 0x41, 0x41, 0x3e, 0x3e, 0, 0x42};
}  // namespace

// 0x002998d0 CKHkS08Enemy_ReactSM02_Hurt_maybe. Enter: the directional hurt animation, the ground height kept (+0x728),
// the trail on (not kind 7), +0x778 the rate, the pending hit taken; a hero target with no attack slot (+0x7d8 -1, not
// +0x891) and attacks in the kind takes slot 0 (its old holder of that category released first). Leave: the rate 1,
// +0x750 cleared, the animation 0x11 at 0.1. Tick: the animation played; a new hit (not an element one of the hit
// types 1, 2, 7..9, 0xd, 0x10, 0x11) restarts the animation; else the knockback moves the enemy and, once the animation
// ends: in the air (3) or without ground (0) 8 with the sound 6 (0 on a slide while alive); on a slide 10; dead 0xf on
// flat ground for the kinds that have it, else 7; alive off the nav mesh asks for a move (+0x7f8), the trail on, then the
// stun gauge: full 5 (capped), some 4, none 0. Until then 2 (the trail updated).
uint8_t CKHkS08Enemy::ReactState02_Hurt(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        PlayDirectionalHurtAnim();  // 0x00297950
        CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
        collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &m_v3Position.x, 1);  // 0x00196540
        m_unk728 = m_GrdContDatasInOut.m_eContactStatus == 0 ? m_v3Position.y - m_GrdContDatasInOut.m_fdH
                                                             : m_v3Position.y;
        if (m_ui8EnemyClassType != 7) SetAttackTrailActive(1, 1, 0);  // 0x0028b960
        m_unk778 = m_unk774;
        m_unk239 = 0;
        IKSerializable* target = m_unk330;
        if (target == nullptr || target->IsKindOfClass(0x25c2) == 0) return 2;
        if (m_unk7d8 != -1 || m_unk891 != 0) return 2;
        if (m_unk884->m_vUnk11c.m_ui32NbUsedElt == 0) return 2;
        m_unk7d8 = 0;
        CKGrpS08Enemy* group = static_cast<CKGrpS08Enemy*>(enemy::EnemyGroup());
        group->ReleaseAttackSlotOfType(m_unk7d8);  // 0x00268a60
        static_cast<CKGrpS08Enemy*>(enemy::EnemyGroup())->ReserveAttackSlot(m_unk7d8, this);  // 0x00267260
        m_unk891 = 1;
        return 2;
    }
    if (phase == 2) {
        m_unk774 = 1.0f;
        m_unk750 = 0;
        RequestAnim(0x11, 0, 0, 0, 0.1f, 0.0f);  // 0x00285340
        return 2;
    }
    if (phase != 0) return 2;
    UpdateHurtAnimPlayback(clock);  // 0x00298430
    if (m_unk239 != 0) {
        bool restart = true;
        if (m_unk27c->IsKindOfClass(0x99cc) != 0) {
            const int32_t type = static_cast<CKS08ElementDamage*>(m_unk27c)->m_unk38;
            restart = type == 0 || type == 3 || type == 4 || type == 5 || type == 6 || type == 0xb || type == 0xa ||
                      type == 0xf || type == 0xc || type == 0xe;
        }
        if (restart) {
            PlayDirectionalHurtAnim();
            m_unk778 = m_unk774;
            return 2;
        }
    }
    IntegrateKnockbackMotion(clock);  // 0x002987c8
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &m_v3Position.x, 1);
    bool ended;
    if (m_unk768 == 0) {
        ended = m_unk764 >= CKAnmKeyFrameController::GetDurationOf(m_unk75c);
    } else {
        ended = m_unk768 == 1 && m_unk76c == 0;
    }
    if (!ended) {
        if (m_ui8EnemyClassType != 7) SetAttackTrailActive(1, 1, 1);
        return 2;
    }
    const int32_t status = static_cast<int32_t>(m_GrdContDatasInOut.m_eContactStatus);
    const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(m_GrdContDatasInOut.m_pGround);
    if (status == 0 || status == 3) {
        if (m_unk258 > 0.0f && ground != nullptr && (ground->m_ui16PropertiesFlags & 0x200u) != 0) return 0;
        PlaySound(6, 0, m_pKGLObject);  // 0x002795c0
        return 8;
    }
    if (status < 0 || status > 3) {
        if (m_ui8EnemyClassType != 7) SetAttackTrailActive(1, 1, 1);
        return 2;
    }
    if (ground != nullptr && (ground->m_ui16PropertiesFlags & 0x200u) != 0) return 10;
    if (m_unk258 <= 0.0f) {
        if (kKindDeathOnGround[m_ui8EnemyClassType] != 0 && ground != nullptr &&
            (ground->m_ui16PropertiesFlags & 0x200u) == 0) {
            return 0xf;
        }
        return 7;
    }
    CKSrvPathFinding* pathFinding = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);
    CPFPoint point;
    point.m_position = m_v3Position;
    point.m_unk0c = m_PFCpnt.m_Destination.m_unk0c;
    if (!(PointInNodeBox(pathFinding, &point) &&
          (pathFinding->IsPointWalkable(&point, &m_PFCpnt.m_CharacterType) & 0xffu) != 0)) {  // 0x001e42d0
        m_unk7f8 = 1;
    }
    if (m_ui8EnemyClassType != 7) SetAttackTrailActive(1, 0, 0);
    if (m_unk25c >= m_unk884->m_unkd4) {
        m_unk25c = m_unk884->m_unkd4;
        return 5;
    }
    return m_unk25c > 0.0f ? 4 : 0;
}

// 0x00299708 CKHkS08Enemy_ReactSM03_HurtCheckStun_maybe (vt+0x1f8): enter: the hurt animation 0x25 (blend 0.1). Run:
// a pending hit (+0x239) that is no element damage (0x99cc), or one of the elements 0, 3, 4, 5, 6, 0xa, 0xb, 0xc, 0xe,
// 0xf, restarts the hurt (2); at the animation's end (dt +0x1fc x +0x774) a stun gauge (+0x25c) at the kind's
// maximum (+0xd4) or above is capped there and stuns (5), below it the gauge drains (4). Else 3.
uint8_t CKHkS08Enemy::ReactState03_HurtCheckStun(IKTime* /*clock*/, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        RequestAnim(0x25, 0, 0, 0, 0.1f, 0.0f);  // 0x00285340
        return 3;
    }
    if (phase != 0) return 3;
    if (m_unk239 != 0) {
        if (m_unk27c->IsKindOfClass(0x99cc) == 0) return 2;  // vt+0x08
        const int32_t element = static_cast<CKS08ElementDamage*>(m_unk27c)->m_unk38;
        switch (element) {
            case 0x0: case 0x3: case 0x4: case 0x5: case 0x6: case 0xb: case 0xa: case 0xf: case 0xc: case 0xe:
                return 2;
            default:
                break;
        }
    }
    if (!IsAnimEndReached(m_unk1fc * m_unk774, 0, 0)) return 3;  // 0x00285558
    const float limit = Cfg()->m_unkd4;
    if (m_unk25c >= limit) {
        m_unk25c = limit;
        return 5;
    }
    return 4;
}

// 0x002993e8 CKHkS08Enemy_ReactSM06_Airborne_maybe (reaction 6): thrown into the air by a hit.
// Enter: the directional hurt animation, the pending hit consumed, +0x254 cleared. Leave: the rate +0x774 back to 1,
// +0x750 cleared, +0x254 back to the kind's +0x1f0.
// Tick: the hurt animation advanced; a pending hit (not an element damage, or of the element types 0, 3-6, 0xa-0xc,
// 0xe, 0xf) restarts the hurt animation. Otherwise the knockback moves it on the ground probe: landed (status 1 / 2)
// raises it by dH and gives reaction 10 on a slide (0x200), else 7 (knockdown); in the air, the hurt animation over
// (its time past the duration, or the rate mode 1 with no loops left) gives reaction 0 for a living enemy with +0x7b4
// over a slide or of the kind 8, else 8; otherwise the attack trail stays on.
uint8_t CKHkS08Enemy::ReactState06_Airborne(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        PlayDirectionalHurtAnim();  // 0x00297950
        m_unk239 = 0;
        m_unk254 = 0.0f;
        return 6;
    }
    if (phase == 2) {
        m_unk774 = 1.0f;
        m_unk750 = 0;
        m_unk254 = m_unk884->m_unk1f0;
        return 6;
    }
    if (phase != 0) return 6;
    UpdateHurtAnimPlayback(clock);  // 0x00298430
    if (m_unk239 != 0) {
        bool restart = true;
        if (m_unk27c->IsKindOfClass(0x99cc) != 0) {
            const int32_t type = static_cast<CKS08ElementDamage*>(m_unk27c)->m_unk38;
            restart = type == 0 || type == 3 || type == 4 || type == 5 || type == 6 || type == 0xb || type == 0xa ||
                      type == 0xf || type == 0xc || type == 0xe;
        }
        if (restart) {
            PlayDirectionalHurtAnim();
            m_unk778 = m_unk774;
            return 6;
        }
    }
    IntegrateKnockbackMotion(clock);  // 0x002987c8
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &m_v3Position.x, 1);  // 0x00196540
    const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(m_GrdContDatasInOut.m_pGround);
    if (m_GrdContDatasInOut.m_eContactStatus - 1u <= 1u) {
        m_v3Position.y = m_v3Position.y + m_GrdContDatasInOut.m_fdH;
        if (ground != nullptr && (ground->m_ui16PropertiesFlags & 0x200u) != 0) return 10;
        return 7;
    }
    bool ended;
    if (m_unk768 == 0) {
        ended = m_unk764 >= CKAnmKeyFrameController::GetDurationOf(m_unk75c);
    } else {
        ended = m_unk768 == 1 && m_unk76c == 0;
    }
    if (!ended) {
        SetAttackTrailActive(1, 1, 1);  // 0x0028b960
        return 6;
    }
    if (m_unk258 > 0.0f) {
        if (m_unk7b4 != 0 && ground != nullptr && (ground->m_ui16PropertiesFlags & 0x200u) != 0) return 0;
        if (m_ui8EnemyClassType == 8) return 0;
    }
    return 8;
}

// 0x0029c998 CKHkS08Enemy_ReactSM07_Knockdown_maybe (reaction 7): knocked down, animation 0x2a.
// Enter: animation 0x2a (restarted, blend 0.1), volume group 1 on (vt+0xf8), +0x254 cleared, the moving spheres off, the
// slide (+0x698) from the velocity flattened and damped by the kind's +0x23c, the stun gauge cleared.
// Leave: the trail off, +0x254 back to the kind's +0x1f0, +0x834 cleared.
// Tick: animation 0x2a kept; a pending hit is applied and, while the enemy lives (not the kinds 5 / 6), mark 0x15 of the
// animation not reached over the frame gives reaction 2. The knockback moves it; the ground under the position: landed
// (status 1 / 2) raises it by dH; in the air the ground is probed again with the object height +0x74 set to the drop
// since the last position: landed raises it by dH, still in the air sweeps the move against the walls (a wall puts it
// back and kills it, main state 0x15; a slide moves it on; a free sweep puts it back on x / z), the speed's x / z cleared
// on a stop; the height restored. The trail updated; at the end of animation 0x2a: dead (health not above 0) gives 0xa
// (+0x1fc / +0x200 cleared), else 0xb.
uint8_t CKHkS08Enemy::ReactState07_Knockdown(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        RequestAnim(0x2a, 1, 0, 0, 0.1f, 0.0f);  // TOC +0x109c / +0x1098
        EnableVolumeGroup(1);                      // vt+0xf8
        m_unk254 = 0.0f;
        SetAttackSpheresActive(0, nullptr);        // 0x00288e08
        m_unk698 = m_unk158.x;
        m_unk69c = m_unk158.y;
        float z = m_unk158.z;
        m_unk69c = 0.0f;
        const float damp = -Cfg()->m_unk23c;
        const float y = m_unk69c;
        z = ppc::fmadds(damp, z, z);
        const float x = ppc::fmadds(damp, m_unk698, m_unk698);
        std::memcpy(&m_unk6a0, &z, sizeof z);
        m_unk698 = x;
        m_unk69c = ppc::fmadds(damp, y, y);
        m_unk25c = 0.0f;
        return 7;
    }
    if (phase == 2) {
        SetAttackTrailActive(1, 0, 0);  // 0x0028b960
        m_unk254 = Cfg()->m_unk1f0;
        m_unk834 = 0;
        return 7;
    }
    if (phase != 0) return 7;
    if (GetCurrentAnim(0, 0) != 0x2a) RequestAnim(0x2a, 1, 0, 0, 0.1f, 0.0f);  // 0x00285408
    if (m_unk239 != 0) {
        if (clock != nullptr) ApplyPendingDamage(clock);  // 0x00299f30
        if (static_cast<uint8_t>(m_ui8EnemyClassType - 5) > 1 && m_unk258 > 0.0f) {
            RtAnimAnimation* animation = CurrentLayer0Animation();  // the dictionary row (0x002b3128, 0x00285408)
            float t0 = GetAnimLayerTime(0, 0) - clock->m_afDeltaTime[0];  // 0x00285388
            if (t0 < 0.0f) t0 = 0.0f;
            AnimMark* mark = Anim_GetMarkById(animation, 0x15);  // 0x00078830
            if (mark != nullptr && AnimMark_RangeValueR3(mark, t0, GetAnimLayerTime(0, 0)) == 0) return 2;  // vt+0x14
        }
    }
    IntegrateKnockbackMotion(clock);  // 0x002987c8
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &m_v3Position.x, 1);  // 0x00196540
    const int32_t status = static_cast<int32_t>(m_GrdContDatasInOut.m_eContactStatus);
    if (status >= 1 && status <= 2) {
        m_v3Position.y = m_v3Position.y + m_GrdContDatasInOut.m_fdH;
    } else if (status == 3) {
        const float height = m_GrdContDatasIn.m_fObjectHeight;
        m_GrdContDatasIn.m_fObjectHeight = m_unk144 - m_v3Position.y;
        collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &m_v3Position.x, 1);
        const int32_t again = static_cast<int32_t>(m_GrdContDatasInOut.m_eContactStatus);
        if (again >= 1 && again <= 2) {
            m_v3Position.y = m_v3Position.y + m_GrdContDatasInOut.m_fdH;
        } else if (again == 3) {
            CLine line;
            line.m_start = CVector3{m_unk140, m_unk144, m_unk148};
            line.m_VectDir = CVector3{m_v3Position.x - m_unk140, m_v3Position.y - m_unk144, m_v3Position.z - m_unk148};
            CSlideGroundEdgeDatasOut slide;
            const int32_t result = static_cast<int32_t>(collision->ResolveSweptCylinderWalls(
                &line, m_unk884->m_MoveCpnt.m_afParams[0], ComponentHeight(), &slide, nullptr, nullptr, 1));  // 0x0019aa68
            if (result == 1) {
                m_v3Position.z = m_unk148;
                m_v3Position.x = m_unk140;
                m_v3Position.y = m_unk144;
                SwitchMainState(0x15, nullptr);  // the original passes no clock
            } else if (result == 0) {
                m_v3Position.x = m_unk140;
                m_v3Position.z = m_unk148;
                m_unk158.z = 0.0f;
                m_unk158.x = 0.0f;
            } else if (result >= 2 && result <= 3) {
                const float x = slide.m_v3BouncingVector.x + m_v3Position.x;
                const float z = slide.m_v3BouncingVector.z + m_v3Position.z;
                const float y = slide.m_v3BouncingVector.y + m_v3Position.y;
                m_v3Position.x = x;
                m_unk158.x = 0.0f;
                m_v3Position.z = z;
                m_v3Position.y = y;
                m_unk158.z = 0.0f;
            }
        }
        m_GrdContDatasIn.m_fObjectHeight = height;
    }
    SetAttackTrailActive(1, 1, 1);
    if (IsAnimEndReached(m_unk1fc * m_unk774, 0, 0) == 0) return 7;  // 0x00285558
    if (GetCurrentAnim(0, 0) != 0x2a) return 7;
    if (!(m_unk258 <= 0.0f)) return 0xb;
    m_unk1fc = 0.0f;
    m_unk200 = 0.0f;
    return 0xa;
}

namespace {
// The stun reactions' test of a pending hit: anything but an element damage (CKS08ElementDamage 0x99cc) of a type other
// than 0, 3..6, 10..12, 14, 15 ends them (reaction 2).
bool BreaksStun(CKS08Damage* damage) {
    if (damage->IsKindOfClass(0x99cc) == 0) return true;  // vt+0x08
    switch (static_cast<CKS08ElementDamage*>(damage)->m_unk38) {
        case 0: case 3: case 4: case 5: case 6: case 0xa: case 0xb: case 0xc: case 0xe: case 0xf:
            return true;
        default:
            return false;
    }
}
}  // namespace

// 0x00299188 CKHkS08Enemy_ReactSM04_StunGaugeDrain_maybe: the stun gauge (+0x25c) drains. Enter: the gauge clamped to
// the kind's maximum (+0xd4), animation 0x2c restarted at the drained part (maximum - gauge). Update: a pending hit
// (+0x239) that breaks the stun (BreaksStun) goes to reaction 2, any other holds the gauge; else the gauge drains by the
// frame's dt; an empty gauge ends the reaction (0; kind 1 plays sound 0x2a or 0x2b). Leave: the velocity +0x158 cleared
// and the attack cooldowns reset.
uint8_t CKHkS08Enemy::ReactState04_StunGaugeDrain(IKTime* /*clock*/, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        const CKS08EnemyCpnt* cfg = m_unk884;
        float gauge = m_unk25c;
        if (gauge > cfg->m_unkd4) {
            gauge = cfg->m_unkd4;
            m_unk25c = gauge;
        }
        RequestAnim(0x2c, 1, 0, 0, 0.4f, cfg->m_unkd4 - gauge);  // 0x00285340, TOC +0x10e0
        return 4;
    }
    if (phase == 2) {
        m_unk158 = CVector3{0.0f, 0.0f, 0.0f};  // TOC +0x1098
        ResetAttackCooldowns();                 // 0x0027ce18
        return 4;
    }
    if (phase != 0) return 4;
    float gauge;
    if (m_unk239 != 0) {
        if (BreaksStun(m_unk27c)) return 2;
        gauge = m_unk25c;
    } else {
        gauge = m_unk25c - m_unk1fc;
        m_unk25c = gauge;
    }
    if (!(gauge <= 0.0f)) return 4;  // cror lt / eq
    m_unk25c = 0.0f;
    if (m_ui8EnemyClassType == 1) {
        const uint32_t r = static_cast<uint32_t>(Rand_Int());
        PlaySound(static_cast<uint8_t>(((r >> 15) & 1u) + 0x2a), 1, m_pKGLObject);  // 0x002795c0
    }
    return 0;
}

// 0x00298ff0 CKHkS08Enemy_ReactSM05_Stunned_maybe: stunned for the kind's +0xd0 (the timer +0x260, animation 0x2d
// restarted). Update: the timer runs down (also under a hit); a pending hit that breaks the stun (BreaksStun) goes to
// reaction 2; the timer's end goes to reaction 4 (the gauge drain).
uint8_t CKHkS08Enemy::ReactState05_Stunned(IKTime* /*clock*/, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        RequestAnim(0x2d, 1, 0, 0, 0.4f, 0.0f);  // 0x00285340, TOC +0x10e0 / +0x1098
        m_unk260 = m_unk884->m_unkd0;
        return 5;
    }
    if (phase != 0) return 5;
    const float timer = m_unk260 - m_unk1fc;
    m_unk260 = timer;
    if (m_unk239 != 0 && BreaksStun(m_unk27c)) return 2;
    if (!(timer <= 0.0f)) return 5;  // cror lt / eq
    return 4;
}

// 0x0029c350 CKHkS08Enemy_ReactSM08_Launched_maybe (reaction 8): in the air.
// Enter: animation 0x28 (blend 0.1 / +0x204), +0x254 and the fall flag (+0x68c) cleared, the kind 1's breathing stopped.
// Leave: +0x254 back to the kind's +0x1f0.
// Tick: a pending hit leaves for 0xe (+0x6bc at the kind's +0x2d4) or 6. Otherwise the knockback moves the enemy (with
// a clock), falling (vertical speed not above 0) plays animation 0x29 once (blend 0.4); the ground under the position
// decides: landed (status 1 / 2) gives 7, raised by the ground's dH, or 0xa on a ground with flag 0x200; in the air
// (status 3) the move since the last position (+0x140) is swept against the walls: a wall puts it back and kills it
// (main state 0x15), a slide moves it on (the x / z speed cleared), a free sweep re-probes the old position (landed:
// 7 at its height +- dH; still in the air: back there, the x / z speed cleared); still in the air afterwards kills it
// too. The attack trail is updated and the reaction stays 8.
uint8_t CKHkS08Enemy::ReactState08_Launched(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        RequestAnim(0x28, 0, 0, 0, 0.1f / m_unk204, 0.0f);  // TOC +0x109c / +0x1098
        m_unk254 = 0.0f;
        m_unk68c = 0;
        if (m_ui8EnemyClassType == 1) {
            StopSound(0x2a);  // 0x002794f0
            StopSound(0x2b);
        }
        return 8;
    }
    if (phase == 2) {
        if (m_unk884 != nullptr) m_unk254 = Cfg()->m_unk1f0;
        return 8;
    }
    if (phase != 0) return 8;
    if (m_unk239 != 0) return m_unk6bc >= Cfg()->m_unk2d4 ? 0xe : 6;
    if (clock != nullptr) IntegrateKnockbackMotion(clock);  // 0x002987c8
    if (m_unk68c == 0 && m_unk158.y <= 0.0f) {
        m_unk68c = 1;
        RequestAnim(0x29, 0, 0, 0, 0.4f, 0.0f);  // TOC +0x10e0 / +0x1098
    }
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &m_v3Position.x, 1);  // 0x00196540
    const uint32_t status = m_GrdContDatasInOut.m_eContactStatus;
    if (static_cast<int32_t>(status) >= 1) {
        if (static_cast<int32_t>(status) <= 2) {
            const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(m_GrdContDatasInOut.m_pGround);
            if (ground != nullptr && (ground->m_ui16PropertiesFlags & 0x200u) != 0) return 0xa;
            m_v3Position.y = m_v3Position.y + m_GrdContDatasInOut.m_fdH;
            return 7;
        }
        if (status == 3) {
            CLine line;
            line.m_start = CVector3{m_unk140, m_unk144, m_unk148};
            line.m_VectDir = CVector3{m_v3Position.x - m_unk140, m_v3Position.y - m_unk144, m_v3Position.z - m_unk148};
            CSlideGroundEdgeDatasOut slide;
            const int32_t result = static_cast<int32_t>(collision->ResolveSweptCylinderWalls(
                &line, m_unk884->m_MoveCpnt.m_afParams[0], ComponentHeight(), &slide, nullptr, nullptr, 1));  // 0x0019aa68
            if (result == 1) {
                m_v3Position.z = m_unk148;
                m_v3Position.x = m_unk140;
                m_v3Position.y = m_unk144;
                SwitchMainState(0x15, nullptr);  // the original passes no clock
            } else if (result == 0) {
                collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &m_unk140, 1);
                const uint32_t back = m_GrdContDatasInOut.m_eContactStatus;
                if (back == 2 || back == 1) {
                    m_v3Position.y = m_unk144 + m_GrdContDatasInOut.m_fdH;
                    return 7;
                }
                if (back == 0) {
                    m_v3Position.y = m_unk144 - m_GrdContDatasInOut.m_fdH;
                    return 7;
                }
                m_unk158.z = 0.0f;
                m_v3Position.x = m_unk140;
                m_v3Position.z = m_unk148;
                m_unk158.x = 0.0f;
            } else if (result >= 2 && result <= 3) {
                const float x = slide.m_v3BouncingVector.x + m_v3Position.x;
                const float z = slide.m_v3BouncingVector.z + m_v3Position.z;
                const float y = slide.m_v3BouncingVector.y + m_v3Position.y;
                m_v3Position.x = x;
                m_unk158.x = 0.0f;
                m_v3Position.z = z;
                m_v3Position.y = y;
                m_unk158.z = 0.0f;
            }
            collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &m_v3Position.x, 1);
            if (m_GrdContDatasInOut.m_eContactStatus == 3) SwitchMainState(0x15, nullptr);
        }
    }
    SetAttackTrailActive(1, 1, 1);  // 0x0028b960
    return 8;
}

// 0x00297160 CKHkS08Enemy_vf210: returns 9.
uint8_t CKHkS08Enemy::ReactState09(IKTime* /*clock*/, int32_t /*phase*/, uint8_t /*other*/) {
    return 9;
}

// 0x00297168 CKHkS08Enemy_vf214: returns 10.
uint8_t CKHkS08Enemy::ReactState0A(IKTime* /*clock*/, int32_t /*phase*/, uint8_t /*other*/) {
    return 10;
}

// 0x00297568 CKHkS08Enemy_ReactSM0B_GetUp_maybe (reaction 0xb): animation 0x2b (blend 0.1). A pending hit gives 2; at the
// animation's end the enemy stands up (reaction 4, the stun gauge at the kind's +0xd4) when its position is inside its
// path-finding node's box (+0x108) and walkable for its character (+0xc4), else it is lost (+0x7f8, reaction 0).
// Leave: +0x254 back to the kind's +0x1f0, the parts of category 1 flagged.
uint8_t CKHkS08Enemy::ReactState0B_GetUp(IKTime* /*clock*/, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        RequestAnim(0x2b, 0, 0, 0, 0.1f, 0.0f);  // TOC +0x109c / +0x1098
        return 0xb;
    }
    if (phase == 2) {
        m_unk254 = Cfg()->m_unk1f0;
        SetPartsFlagForCategory(1);  // 0x0027cf30
        return 0xb;
    }
    if (phase != 0) return 0xb;
    if (m_unk239 != 0) return 2;
    if (IsAnimEndReached(m_unk1fc * m_unk774, 0, 0) == 0) return 0xb;  // 0x00285558
    CPFPoint point;
    point.m_unk0c = 0xffff;
    point.m_position = m_v3Position;
    point.m_unk0c = m_PFCpnt.m_Destination.m_unk0c;
    CKSrvPathFinding* pathFinding = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);
    if (PointInNodeBox(pathFinding, &point) &&
        (pathFinding->IsPointWalkable(&point, &m_PFCpnt.m_CharacterType) & 0xffu) != 0) {  // 0x001e42d0
        m_unk25c = Cfg()->m_unkd4;
        return 4;
    }
    m_unk7f8 = 1;
    return 0;
}

// 0x00297458 CKHkS08Enemy_vf21C (reaction 0xc): lying down for the kind's +0xd0 seconds (+0x260). Enter: +0x200 cleared,
// the parts of category 2 flagged. Leave: +0x200 = 1. Tick: a pending hit gives 0xd (+0x200 = 1, +0x1fc the frame time);
// dead (health not above 0) 0xa; the time up 0xb (get up); else 0xc.
uint8_t CKHkS08Enemy::ReactState0C(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        m_unk200 = 0.0f;
        m_unk260 = Cfg()->m_unkd0;
        SetPartsFlagForCategory(2);  // 0x0027cf30
        return 0xc;
    }
    if (phase == 2) {
        m_unk200 = 1.0f;  // TOC +0x1094
        return 0xc;
    }
    if (phase != 0) return 0xc;
    if (m_unk239 != 0) {
        m_unk200 = 1.0f;
        m_unk1fc = clock->m_afDeltaTime[0];
        return 0xd;
    }
    if (m_unk258 <= 0.0f) return 0xa;
    m_unk260 = m_unk260 - clock->m_afDeltaTime[0];
    return m_unk260 <= 0.0f ? 0xb : 0xc;
}

// 0x0029c018 CKHkS08Enemy_ReactSM0D_maybe (vt+0x220): enter: the animation 0x27 restarted (blend 0.1). Run: a pending
// hit (+0x239) is applied (with a clock) and restarts it; at its end (dt +0x1fc x +0x774), still playing 0x27, the time
// scale +0x200 and the dt +0x1fc are zeroed: 0xa when the health (+0x258) is 0 or less, else 0xc. Else 0xd.
uint8_t CKHkS08Enemy::ReactState0D(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    if (phase == 0) {
        if (m_unk239 != 0) {
            if (clock != nullptr) ApplyPendingDamage(clock);  // 0x00299f30
        } else {
            if (!IsAnimEndReached(m_unk1fc * m_unk774, 0, 0)) return 0xd;  // 0x00285558
            if (GetCurrentAnim(0, 0) != 0x27) return 0xd;                 // 0x00285408
            m_unk200 = 0.0f;  // TOC +0x1098
            m_unk1fc = 0.0f;
            return (m_unk258 <= 0.0f) ? 0xa : 0xc;
        }
    } else if (phase != 1) {
        return 0xd;
    }
    RequestAnim(0x27, 1, 0, 0, 0.1f, 0.0f);  // 0x00285340; TOC +0x109c / +0x1098
    return 0xd;
}

// 0x0029c148 CKHkS08Enemy_ReactSM0E_FallUntilGrounded_maybe (vt+0x224): enter: the velocity (+0x158) the zero vector
// (0xc50d64, TOC +0x1120). Run: the knockback motion, then the ground probe: on the ground (contact 1 / 2) 0; contact
// 3 (fell off) sends the main state to 0x15 (no clock); else 0xe.
uint8_t CKHkS08Enemy::ReactState0E_FallUntilGrounded(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        m_unk158 = CVector3{0.0f, 0.0f, 0.0f};
        return 0xe;
    }
    if (phase != 0) return 0xe;
    IntegrateKnockbackMotion(clock);  // 0x002987c8
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);  // TOC +0x10a0 -> +0x58
    collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &m_v3Position.x, 1);  // 0x00196540
    const int32_t status = static_cast<int32_t>(m_GrdContDatasInOut.m_eContactStatus);
    if (status < 1) return 0xe;
    if (status <= 2) return 0;
    if (status != 3) return 0xe;
    SwitchMainState(0x15, nullptr);
    return 0xe;
}

// 0x0029bd40 CKHkS08Enemy_ReactSM0F_DeathAnim_maybe: the death animation. Enter: the kind's death animation restarted,
// the push share +0x254 at 0 and the squad's trigger +0x88 signalled. Leave: the push share back to the kind's +0x1f0.
// Update: the walls swept (radius 1, the component's height) from the last position +0x140 to hot spot 0; a slide (2 /
// 3) moves the enemy by the bounce; the death animation's end stops the clock scale (+0x1fc / +0x200 at 0) and goes to
// reaction 0xa; else a pending hit is applied.
uint8_t CKHkS08Enemy::ReactState0F_DeathAnim(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        RequestAnim(static_cast<uint8_t>(kKindDeathOnGround[m_ui8EnemyClassType]), 1, 0, 0, 0.1f, 0.0f);  // TOC +0x109c
        m_unk254 = 0.0f;                                                                                   // TOC +0x1098
        CKGrpSquad* squad = static_cast<CKGrpSquad*>(m_pGroupSquad);
        QueueTriggerSignals(&squad->m_tsUnk88);  // 0x00236338
        return 0xf;
    }
    if (phase == 2) {
        m_unk254 = m_unk884->m_unk1f0;
        return 0xf;
    }
    if (phase != 0) return 0xf;
    CVector3 hotSpot;
    GetHotSpot(0)->GetWorldPosition(&hotSpot);  // 0x002892e8, 0x000ce790
    CLine line;
    line.m_start = CVector3{m_unk140, m_unk144, m_unk148};
    line.m_VectDir = CVector3{hotSpot.x - m_unk140, hotSpot.y - m_unk144, hotSpot.z - m_unk148};
    CSlideGroundEdgeDatasOut slide;
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    const uint8_t result = collision->ResolveSweptCylinderWalls(&line, 1.0f, ComponentHeight(), &slide, nullptr, nullptr,
                                                                1);  // 0x0019aa68, TOC +0x1094
    if (static_cast<uint32_t>(result) - 2u <= 1u) {
        m_v3Position.x = slide.m_v3BouncingVector.x + m_v3Position.x;
        m_v3Position.y = slide.m_v3BouncingVector.y + m_v3Position.y;
        m_v3Position.z = slide.m_v3BouncingVector.z + m_v3Position.z;
    }
    if (IsAnimEndReached(m_unk1fc * m_unk774, 0, 0) &&  // 0x00285558
        GetCurrentAnim(0, 0) == kKindDeathOnGround[m_ui8EnemyClassType]) {  // 0x00285408
        m_unk1fc = 0.0f;
        m_unk200 = 0.0f;
        return 0xa;
    }
    if (m_unk239 != 0 && clock != nullptr) ApplyPendingDamage(clock);  // 0x00299f30
    return 0xf;
}

// 0x00298d68 CKHkS08Enemy_ReactSM10_KnockbackAnim_maybe (vt+0x22c): run: the knockback motion; at the animation's end
// (dt +0x1fc x +0x774) 8, else 0x10. Enter / leave: 0x10.
uint8_t CKHkS08Enemy::ReactState10_KnockbackAnim(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    if (phase != 0) return 0x10;
    IntegrateKnockbackMotion(clock);  // 0x002987c8
    return IsAnimEndReached(m_unk1fc * m_unk774, 0, 0) ? 8 : 0x10;  // 0x00285558
}

namespace {
using StateFn = uint8_t (CKHkS08Enemy::*)(IKTime*, int32_t, uint8_t);
// DOTD: the state slots vt+0x14c..+0x240 in vtable order (index = (offset - 0x14c) / 4).
const StateFn kStateSlots[] = {
    &CKHkS08Enemy::MainState00_Spawn,  // vt+0x14c
    &CKHkS08Enemy::MainState01,  // vt+0x150
    &CKHkS08Enemy::MainState02_Combat,  // vt+0x154
    &CKHkS08Enemy::MainState03,  // vt+0x158
    &CKHkS08Enemy::MainState04,  // vt+0x15c
    &CKHkS08Enemy::MainState05_Guard,  // vt+0x160
    &CKHkS08Enemy::MainState06_Dodge,  // vt+0x164
    &CKHkS08Enemy::MainState0B,  // vt+0x168
    &CKHkS08Enemy::MainState0C,  // vt+0x16c
    &CKHkS08Enemy::MainState0D_AttackWindup,  // vt+0x170
    &CKHkS08Enemy::MainState0E_AttackStrike,  // vt+0x174
    &CKHkS08Enemy::MainState0F_AttackRecover,  // vt+0x178
    &CKHkS08Enemy::MainState12,  // vt+0x17c
    &CKHkS08Enemy::MainState13,  // vt+0x180
    &CKHkS08Enemy::MainState14,  // vt+0x184
    &CKHkS08Enemy::MainState15_Dying,  // vt+0x188
    &CKHkS08Enemy::MainState16,  // vt+0x18c
    &CKHkS08Enemy::MainState17,  // vt+0x190
    &CKHkS08Enemy::MainState18,  // vt+0x194
    &CKHkS08Enemy::MainState19_OneShotAnim,  // vt+0x198
    &CKHkS08Enemy::MainState07_Grabbed,  // vt+0x19c
    &CKHkS08Enemy::MainState08,  // vt+0x1a0
    &CKHkS08Enemy::MainState0A_HitReaction,  // vt+0x1a4
    &CKHkS08Enemy::MainState1A_Burning,  // vt+0x1a8
    &CKHkS08Enemy::MainState1B,  // vt+0x1ac
    &CKHkS08Enemy::MainState1C,  // vt+0x1b0
    &CKHkS08Enemy::MainState1D_WindCaught,  // vt+0x1b4
    &CKHkS08Enemy::MainState1E_WaitWindGaugeEmpty,  // vt+0x1b8
    &CKHkS08Enemy::MainState1F_Stunned,  // vt+0x1bc
    &CKHkS08Enemy::MainState20_Alerted,  // vt+0x1c0
    &CKHkS08Enemy::MainState21_DropEquipment,  // vt+0x1c4
    &CKHkS08Enemy::MainState22_BlockAndCounter,  // vt+0x1c8
    &CKHkS08Enemy::MainState23,  // vt+0x1cc
    &CKHkS08Enemy::MainState24_Feared,  // vt+0x1d0
    &CKHkS08Enemy::MainState25,  // vt+0x1d4
    &CKHkS08Enemy::MainState26_OnFireWait,  // vt+0x1d8
    &CKHkS08Enemy::MainState27_Fall,  // vt+0x1dc
    &CKHkS08Enemy::AwareState00_WatchForTarget,  // vt+0x1e0
    &CKHkS08Enemy::AwareState01_PlayAlertAnim,  // vt+0x1e4
    &CKHkS08Enemy::AwareState02,  // vt+0x1e8
    &CKHkS08Enemy::ReactState00_DispatchHit,  // vt+0x1ec
    &CKHkS08Enemy::ReactState01_Burning,  // vt+0x1f0
    &CKHkS08Enemy::ReactState02_Hurt,  // vt+0x1f4
    &CKHkS08Enemy::ReactState03_HurtCheckStun,  // vt+0x1f8
    &CKHkS08Enemy::ReactState06_Airborne,  // vt+0x1fc
    &CKHkS08Enemy::ReactState07_Knockdown,  // vt+0x200
    &CKHkS08Enemy::ReactState04_StunGaugeDrain,  // vt+0x204
    &CKHkS08Enemy::ReactState05_Stunned,  // vt+0x208
    &CKHkS08Enemy::ReactState08_Launched,  // vt+0x20c
    &CKHkS08Enemy::ReactState09,  // vt+0x210
    &CKHkS08Enemy::ReactState0A,  // vt+0x214
    &CKHkS08Enemy::ReactState0B_GetUp,  // vt+0x218
    &CKHkS08Enemy::ReactState0C,  // vt+0x21c
    &CKHkS08Enemy::ReactState0D,  // vt+0x220
    &CKHkS08Enemy::ReactState0E_FallUntilGrounded,  // vt+0x224
    &CKHkS08Enemy::ReactState0F_DeathAnim,  // vt+0x228
    &CKHkS08Enemy::ReactState10_KnockbackAnim,  // vt+0x22c
    &CKHkS08Enemy::AuxState00_PlayStartAnim,  // vt+0x230
    &CKHkS08Enemy::AuxState01_SeekWeapon,  // vt+0x234
    &CKHkS08Enemy::AuxState02_ClaimWeapon,  // vt+0x238
    &CKHkS08Enemy::AuxState03,  // vt+0x23c
    &CKHkS08Enemy::AuxState04_PickUpWeapon,  // vt+0x240
};
}  // namespace

// DOTD: the original's inlined pointer-to-member call of a state row: a virtual descriptor (bit 0 set: vtable offset + 1)
// with the row's this-adjust (always 0 here) calls that slot through the vtable (the native virtual call does the same).
// A row the original never fills (main rows 9, 16, 17, 20) would jump through a null descriptor there; here it logs and
// returns `other`... unreachable in practice.
uint8_t CKHkS08Enemy::CallStateRow(const uint32_t pair[2], IKTime* clock, int32_t phase, uint8_t other) {
    const uint32_t offset = pair[0] - 1;
    if ((pair[0] & 1u) == 0 || pair[1] != 0 || offset < 0x14c || offset > 0x240) {
        static bool s_logged = false;
        if (!s_logged) {
            s_logged = true;
            DOTD_LOG("CKHkS08Enemy: state row %08x/%08x not supported", pair[0], pair[1]);
        }
        return other;
    }
    return (this->*kStateSlots[(offset - 0x14c) / 4])(clock, phase, other);
}

// 0x00297250 CKHkS08Enemy_InitHitReactionStateMachine_maybe: 17 rows, state 0 entered at once (clock null, from 0xff).
void CKHkS08Enemy::InitHitReactionStateMachine() {
    static const uint32_t kSlots[17] = {0x1ec, 0x1f0, 0x1f4, 0x1f8, 0x204, 0x208, 0x1fc, 0x200, 0x20c,
                                        0x210, 0x214, 0x218, 0x21c, 0x220, 0x224, 0x228, 0x22c};
    for (uint32_t i = 0; i < 17; ++i) {
        m_aReactStates[i][0] = kSlots[i] + 1;
        m_aReactStates[i][1] = 0;
    }
    m_reactStateCount = 0x11;
    m_pReactStates = &m_aReactStates[0][0];
    m_reactState = 0;
    CallReactState(0, nullptr, 1, 0xff);
}

// 0x0029d078 CKHkS08Enemy_FindFreeWeapon: the first weapon of the enemy group's weapon group (+0x190, walked by index
// from the head each time) that is in no hand (+0xa8), unclaimed or claimed by this enemy (+0xb4), and of a weapon kind
// (+0x20) this enemy's kind can hold; null when none.
CKHkS08Weapon* CKHkS08Enemy::FindFreeWeapon() {
    auto head = []() {
        IKBaseGroup* weapons = static_cast<IKBaseGroup*>(static_cast<CKGrpS08Enemy*>(enemy::EnemyGroup())->m_pUnk190);
        return *reinterpret_cast<IKHook**>(weapons->GetMemberListHead());  // 0x00276f58, vt+0xb0
    };
    uint32_t count = 0;
    for (IKHook* hook = head(); hook != nullptr; hook = hook->m_pNextHook) ++count;
    for (uint32_t i = 0; i < count; ++i) {
        IKHook* hook = head();
        for (uint32_t k = 0; k < i; ++k) hook = hook->m_pNextHook;
        CKHkS08Weapon* weapon = static_cast<CKHkS08Weapon*>(hook);
        if (weapon->m_inHandA8 != 0) continue;
        if (weapon->m_pOwnerB4 != nullptr && weapon->m_pOwnerB4 != this) continue;
        const uint32_t kinds = enemy::kWeaponPoolCount[m_ui8EnemyClassType];  // TOC +0x1134 (0x00a70220)
        const uint32_t* pools = enemy::kWeaponPools[m_ui8EnemyClassType];      // TOC +0x1138 (0x00b00fec)
        for (uint32_t k = 0; k < kinds; ++k) {
            if (pools[k] == weapon->m_unk20) return weapon;
        }
    }
    return nullptr;
}

// 0x00297408 StaticInitAndDestruction_297408: two file statics (0x00cead08, 0x00cead0c) set to -1.0f. Nothing in the game
// reads them (their only references are the initialiser's TOC entries).
namespace {
[[maybe_unused]] float s_unkcead08 = -1.0f;
[[maybe_unused]] float s_unkcead0c = -1.0f;
}  // namespace
