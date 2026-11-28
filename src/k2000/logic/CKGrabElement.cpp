// CKGrabElement.cpp - reconstructed original translation unit 0x3a5e60-0x3a9c50 (GAME_TOC1, main_toc1), 29 functions, 28 live.
// Primary class: CKGrabElement  key 0x9fcc  category Logic  size 0x140  vtable 0xb23ae0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3a5e60  CKGrabElement_Delete
//   [x] 0x3a5eb0  CKGrabElement_Construct
//   [ ] 0x3a5ec0  CKGrabElement_Construct_2  [dead]
//   [x] 0x3a5ed0  CKGrabElement_GetAbilityId
//   [x] 0x3a5ed8  CKGrabElement_GetFamilyId
//   [x] 0x3a5ee0  CKGrabElement_Stop
//   [x] 0x3a5f70  CKGrabElement_End
//   [x] 0x3a6058  CKGrabElement_ApplyHeroControl
//   [x] 0x3a6650  CKGrabElement_ResetRuntime
//   [x] 0x3a66a0  CKGrabElement_ApplyDamageParams
//   [x] 0x3a6ba0  CKGrabElement_DeleteArray
//   [x] 0x3a6c48  CKGrabElement_StartEmitterFx
//   [ ] 0x3a6f10  RegisterCKGrabElementClass
//   [ ] 0x3a6f98  _GLOBAL__D_3a6f98
//   [ ] 0x3a6fa8  _GLOBAL__I_3a6fa8
//   [x] 0x3a6fb8  CKGrabElement_ReleaseAndStopFx_maybe
//   [x] 0x3a7070  CKGrabElement_Update
//   [x] 0x3a7c80  CKGrabElement_Start
//   [x] 0x3a7eb8  CKGrabElement_GrabTarget_maybe
//   [x] 0x3a8298  CKGrabElement_CreateArray
//   [x] 0x3a8330  CKGrabElement_Create
//   [x] 0x3a8368  CKGrabElement_RecursiveRegistration  (returns 1: the inherited default)
//   [x] 0x3a8370  CKGrabElement_PostLoad
//   [x] 0x3a83b8  CKGrabElement_Destroy  (empty)
//   [x] 0x3a83c0  CKGrabElement_Load
//   [ ] 0x3a9018  CKGrabElement_Save
//   [x] 0x3a9bc8  CKGrabElement_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x3a9be8  CKGrabElement_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x3a9c08  CKGrabElement_DeletingDestructor  (C++ destructor chain: vtable stores only)
//
//   [ ] 0x9bfec0  CKGrabElement_GetClassType  [inline]
//   [ ] 0x9bfec8  CKGrabElement_GetClassID  [inline]
//   [x] 0x9bfed0  CKGrabElement_SetFxActive  [inline]
//   [x] 0x9bfee0  CKGrabElement_vf80  [inline]
//   [x] 0x9bfee8  CKGrabElement_vf84  [inline]
//   [ ] 0x9bfef8  CKGrabElement_IsKindOfClass  [inline]
#include "k2000/logic/CKGrabElement.h"

#include "Spyro2008/logic/CKS08ElementDamage.h"
#include "Spyro2008/misc/CKS08AbilityHostBase.h"
#include "crt/ppc_ops.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"
#include "Renderware/rwcore/RwCamera.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/scenegraph/CSGMovable.h"

// 0x003a83c0 CKGrabElement_Load: level data only (type 0, K_LEVEL_PLATEFORMS); 0x10e bytes. Three rows of
// fifteen words and two bytes, then the scalars and three references; every word byte-swapped.
int32_t CKGrabElement::Load(IKFile* file, int32_t type) {
    if (type == 0) {
        for (int32_t i = 0; i < 3; ++i) {
            ReadS32LE(file, &m_ai32Damage[i]);
            ReadF32LE(file, &m_afCooldown[i]);
            ReadS32LE(file, &m_ai32ManaPerSecond[i]);
            ReadF32LE(file, &m_unk38[i]);
            ReadF32LE(file, &m_unk44[i]);
            ReadF32LE(file, &m_afDisarmAmount[i]);
            ReadF32LE(file, &m_afStunAmount[i]);
            ReadF32LE(file, &m_afElementEffect0[i]);
            ReadF32LE(file, &m_afElementEffect1[i]);
            ReadF32LE(file, &m_afElementEffect2[i]);
            ReadF32LE(file, &m_afElementEffect4[i]);
            ReadF32LE(file, &m_afElementEffect6[i]);
            ReadF32LE(file, &m_afElementEffect5[i]);
            ReadF32LE(file, &m_afElementEffect7[i]);
            ReadF32LE(file, &m_afElementEffect3[i]);
            ReadU8(file, &m_abDamageFlag34[i]);
            ReadU8(file, &m_abDamageFlag35[i]);
        }
        ReadU8(file, &m_unkD8);
        ReadU8(file, &m_unkD9);
        ReadU8(file, &m_unkDa);
        ReadF32LE(file, &m_unkDc);
        ReadF32LE(file, &m_unkE0);
        ReadF32LE(file, &m_fGroundMoveSpeed);
        ReadU8(file, &m_unkE4);
        ReadU8(file, &m_unkE5);
        ReadU8(file, &m_unkE6);
        ReadF32LE(file, &m_unkE8);
        ReadF32LE(file, &m_unkEc);
        ReadF32LE(file, &m_fFlyMoveSpeed);
        ReadU8(file, &m_unkF8);
        ReadU8(file, &m_unkF9);
        ReadF32LE(file, &m_unkFc);
        ReadF32LE(file, &m_unk100);
        IKFile_ReadRef(file, &m_pElementDamage);
        ReadU8(file, &m_unk104);
        ReadU8(file, &m_unk105);
        ReadU8(file, &m_unk106);
        ReadF32LE(file, &m_unk108);
        ReadF32LE(file, &m_unk10c);
        ReadF32LE(file, &m_fAirMoveSpeed);
        ReadU8(file, &m_bAirParam11f8Enable);
        ReadF32LE(file, &m_fAirParam11f8);
        IKFile_ReadRef(file, &m_pAimCone);
        ReadF32LE(file, &m_unk20);
        ReadF32LE(file, &m_unk24);
        ReadF32LE(file, &m_unk28);
        IKFile_ReadRef(file, &m_pFizzleExplosionFxData);
    }
    return 1;
}

namespace {
float GameClockNow() { return g_pEngine->m_timeManager->m_pTime->m_afCurrentTime[0]; }  // TOC +0x38a8 -> +0x48 -> +0x04 -> +0x04
// 0x00a70988 (this unit's copy of the ability ids' damage types: the same 26 words as CKProjectileElement's 0x00a70a58).
const uint32_t kAbilityDamageTypes[26] = {0, 0, 1, 1, 2, 2, 3, 3, 8, 8, 4, 4, 5, 5, 5, 6, 9, 7, 7, 9, 6, 0, 0, 0, 0, 0};
// A null `direction` (all three equal to 0x00c50d64's) becomes the target's node position (its stored LTM) minus the
// user's (host vt+0x10), in place.
void DirectionToTarget(CKS08AbilityHostBase* host, IKSerializable* target, CVector3* direction) {
    if (direction->x != 0.0f || direction->y != 0.0f || direction->z != 0.0f) return;
    const RwV3d& pos = FrameLtm(static_cast<CSGMovable*>(static_cast<IKHook*>(target)->m_pKGLObject)->m_pRwFrame)->pos;
    const CVector3 user = host->GetOwnerPosition();
    direction->x = pos.x - user.x;
    direction->y = pos.y - user.y;
    direction->z = pos.z - user.z;
}
// The mana units the accumulator holds: fctidz, the low word (clrldi 32).
uint32_t WholeMana(float value) { return static_cast<uint32_t>(static_cast<uint64_t>(ppc::fctidz(value))); }
}  // namespace

// 0x003a7c80 CKGrabElement_Start
void CKGrabElement::Start(CKS08AbilityHostBase* host) {
    if (m_bRunning != 0 || host == nullptr) return;
    m_pHost = host;
    m_pTarget = nullptr;
    m_bInLoop = 0;
    m_bInStartAnim = 0;
    m_bInEndAnim = 0;
    m_bTargetHeld = 0;
    m_bForcedEnd = 0;
    m_bRunning = 1;
    m_dwLevelIndex = host->GetAbilityLevelIndex(this);  // vt+0xf4
    ApplyHeroControl(1);                          // vt+0x68
    m_fMana = 0.0f;
    m_bAltLoopAnim = m_pHost->CanUseAltLoopAnim();  // vt+0x38
    if (m_pHost->PlayAbilityAnim(this, 0) != 0) {  // vt+0x7c
        m_bInStartAnim = 1;
    } else {
        if (m_bAltLoopAnim == 0 || m_pHost->PlayAbilityAnim(this, 2) == 0) m_pHost->PlayAbilityAnim(this, 1);
        m_bInLoop = 1;
        if (Vf90() != 0) SetFxActive(1);  // vt+0x90 / vt+0x70
    }
    m_fStartTime = GameClockNow();
}

// 0x003a5ee0 CKGrabElement_Stop
void CKGrabElement::Stop(int32_t forced) {
    if (m_bRunning == 0) return;
    ReleaseAndStopFx();  // vt+0x88
    End(forced);         // vt+0x64
}

// 0x003a5f70 CKGrabElement_End
void CKGrabElement::End(int32_t forced) {
    ApplyHeroControl(0);  // vt+0x68
    m_bRunning = 0;
    const float forcedCooldown[3] = {m_unk20, m_unk24, m_unk28};
    const float cooldown = forced != 0 ? forcedCooldown[m_dwLevelIndex] : m_afCooldown[m_dwLevelIndex];
    m_pHost->SetAbilityCooldown(cooldown, this, static_cast<uint8_t>((forced ^ 1) & 0xff));  // vt+0x9c
    m_pHost = nullptr;
}

// 0x003a6058 CKGrabElement_ApplyHeroControl. The gates of +0x68 (SetAbilityParam11f8): a context's own byte when its
// permission 0 byte (+0xd9 / +0xe5 / +0x105) is clear.
void CKGrabElement::ApplyHeroControl(uint8_t on) {
    CKS08AbilityHostBase* host = m_pHost;
    if (on != 0) {
        host->SetHeroActionPermission(0, m_unkD9, m_unkE5, m_unk105);  // vt+0x44
        host->SetHeroActionPermission(1, m_unkD8, m_unkE4, m_unk104);
        host->SetHeroActionPermission(3, 1, 1, 1);
        host->SetHeroActionPermission(4, 1, 1, 1);
        host->SetHeroActionPermission(5, 0, 0, 0);
        host->SetHeroActionPermission(8, 1, 1, 1);
        host->SetAbilityTurnParams(m_unkDc, m_unkE0, m_unkE8, m_unkEc, m_unk108, m_unk10c, m_unkDa, m_unkE6,
                                   m_unk106);  // vt+0x64
        const uint8_t gateAir = m_unkD9 == 0 ? static_cast<uint8_t>(m_unkF8 != 0) : 0;
        const uint8_t gateFly = m_unkE5 == 0 ? static_cast<uint8_t>(m_unkF9 != 0) : 0;
        const uint8_t gateGround = m_unk105 == 0 ? static_cast<uint8_t>(m_bAirParam11f8Enable != 0) : 0;
        host->SetAbilityParam11f8(m_unkFc, m_unk100, m_fAirParam11f8, gateAir, gateFly, gateGround);  // vt+0x68
        host->SetAbilityMoveSpeed(m_fGroundMoveSpeed, m_fFlyMoveSpeed, m_fAirMoveSpeed);                                // vt+0x50
        host->SetAbilityMoveSpeedEnabled(1);                                                  // vt+0x54
        const uint8_t inAir = static_cast<uint8_t>(host->IsOnGround() ^ 1);                // vt+0x30
        m_bInAir = inAir;
        host->SetAbilityHeroMode(this, inAir);  // vt+0x70
        return;
    }
    host->SetHeroActionPermission(0, 0, 0, 0);
    host->SetHeroActionPermission(1, 0, 0, 0);
    host->SetHeroActionPermission(3, 0, 0, 0);
    host->SetHeroActionPermission(4, 0, 0, 0);
    host->SetHeroActionPermission(5, 0, 0, 0);
    host->SetHeroActionPermission(8, 0, 0, 0);
    host->SetHeroActionPermission(9, 0, 0, 0);
    host->SetAbilityTurnParams(m_unkDc, m_unkE0, m_unkE8, m_unkEc, m_unk108, m_unk10c, 0, 0, 0);
    host->SetAbilityParam11f8(m_unkFc, m_unk100, m_fAirParam11f8, 0, 0, 0);
    host->SetAbilityMoveSpeedEnabled(0);
    host->SetAbilityHeroMode(this, 0);
}

// 0x003a6650 CKGrabElement_ResetRuntime
void CKGrabElement::ResetRuntime() {
    m_fStartTime = -1.0f;  // 0xbf800000
    m_fMana = 0.0f;
    m_pTarget = nullptr;
    m_bHotspotIndex = 0xff;
    m_bButtonIndex = 1;
    m_pHost = nullptr;
    m_dwLevelIndex = 0;
    m_bRunning = 0;
    m_bInLoop = 0;
    m_bInStartAnim = 0;
    m_bInEndAnim = 0;
    m_bTargetHeld = 0;
    m_bAltLoopAnim = 0;
}

// 0x003a66a0 CKGrabElement_ApplyDamageParams
void CKGrabElement::ApplyDamageParams(uint8_t continuous) {
    const float damageScale = m_pHost->GetDamageScale();  // vt+0xc0
    const float effectScale = m_pHost->GetEffectScale();  // vt+0xc4
    const uint32_t level = m_dwLevelIndex;
    CKS08ElementDamage* damage = static_cast<CKS08ElementDamage*>(m_pElementDamage);
    damage->SetAmount(damageScale * static_cast<float>(static_cast<double>(m_ai32Damage[level])));  // vt+0x50 (fcfid, frsp)
    damage->SetStun(m_afStunAmount[level]);                           // vt+0x5c
    damage->SetDisarmAmount(m_afDisarmAmount[level]);                   // vt+0x60
    damage->SetElementValue(effectScale * m_afElementEffect0[level], 0);  // vt+0x58
    damage->SetElementValue(effectScale * m_afElementEffect1[level], 1);
    damage->SetElementValue(effectScale * m_afElementEffect2[level], 2);
    damage->SetElementValue(effectScale * m_afElementEffect6[level], 6);
    damage->SetElementValue(effectScale * m_afElementEffect4[level], 4);
    damage->SetElementValue(effectScale * m_afElementEffect7[level], 7);
    damage->SetElementValue(effectScale * m_afElementEffect3[level], 3);
    damage->SetElementValue(effectScale * m_afElementEffect5[level], 5);
    damage->SetUnk34(m_abDamageFlag34[level]);  // vt+0x6c
    damage->SetUnk35(m_abDamageFlag35[level]);  // vt+0x70
    damage->SetDamageType(kAbilityDamageTypes[GetAbilityId() & 0xffu]);  // vt+0x64; TOC 0x00a70988
    damage->SetAbilityId(GetAbilityId());                                 // vt+0x68
    damage->SetContinuous(continuous);                                    // vt+0x54
}

// 0x003a6c48 CKGrabElement_StartEmitterFx: the inlined pooled lookup (CKSrvFx::AcquireFx) of the explosion data's
// effect, owned by this element.
void CKGrabElement::StartEmitterFx() {
    IKFxData* data = reinterpret_cast<IKFxData*>(m_pFizzleExplosionFxData);
    CKSrvFx* fxService = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
    if (fxService->m_ui32EltNb == 0) return;
    CKExplosionNodeFx* fx = static_cast<CKExplosionNodeFx*>(fxService->AcquireFx(data, this));
    if (fx == nullptr) return;
    const CVector3 position = m_pHost->GetHotspotPosition(m_bHotspotIndex);  // vt+0xd0
    fx->SetTranslation(&position, this);  // 0x001b66e8
    fx->Trigger(this, 0);                 // 0x001b82a8
    fx->ReleaseReservation(this);         // vt+0x54
}

// 0x003a6fb8 CKGrabElement_ReleaseAndStopFx_maybe
void CKGrabElement::ReleaseAndStopFx() {
    if (m_bTargetHeld != 0) {
        // BUG(original): the direction (r1+0x70) is passed without being set; GrabTarget takes it for null (and puts
        // the direction to the target in it) only when the stack happens to hold three zeros. DOTD: the null vector
        // (the enemy host ignores it; the hero host's grab is not ported).
        CVector3 direction{0.0f, 0.0f, 0.0f};
        GrabTarget(0, 1, &direction);  // vt+0x7c
    }
    SetFxActive(0);  // vt+0x70
    m_bInLoop = 0;
}

// 0x003a7eb8 CKGrabElement_GrabTarget_maybe
void CKGrabElement::GrabTarget(uint8_t grab, uint8_t mode, CVector3* direction) {
    if (grab == 0) {
        IKSerializable* target = m_pTarget;
        m_bTargetHeld = 0;
        if (target != nullptr) {
            DirectionToTarget(m_pHost, target, direction);
            const CVector3 copy = *direction;
            m_bTargetHeld = static_cast<uint8_t>(m_pHost->GrabEnemy(this, 0, mode, &copy, m_pElementDamage, m_pTarget) ^ 1);  // vt+0xec
        }
        m_pTarget = nullptr;
        return;
    }
    if (m_bTargetHeld != 0 && m_pTarget != nullptr) {
        DirectionToTarget(m_pHost, m_pTarget, direction);
        const CVector3 copy = *direction;
        m_pHost->GrabEnemy(this, 0, 1, &copy, m_pElementDamage, m_pTarget);  // vt+0xec (mode 1)
    }
    CKS08AbilityHostBase* host = m_pHost;
    float weight;
    const CVector3 point = host->GetTargetPoint(&weight);                            // vt+0x98
    const uint8_t held = host->GrabEnemy(this, 1, mode, &point, m_pElementDamage, nullptr);  // vt+0xec
    m_bTargetHeld = held;
    if (held != 0) m_pTarget = m_pHost->GetLockedTarget();  // vt+0xd4
}

// 0x003a7070 CKGrabElement_Update. The mana: the cost scale (host vt+0xc8) x the level's cost per second (+0x2c) x dt
// accumulates (fmadds) in +0x128; whole points (fctidz, at 1 or more) go to the host (vt+0xb8). Out of mana (the
// host's mana, vt+0xbc as an unsigned float, not above the accumulator; -1 is infinite): the end, forced. While no
// target is held the host aims (vt+0x58) and a locked target (vt+0xd4) is grabbed; none: the miss (vt+0x74) spends
// the level's cost x +0x14 at once and the ability ends.
uint8_t CKGrabElement::Update(float dt) {
    if (m_bRunning == 0) return 0;
    if (m_fStartTime == GameClockNow()) return 1;
    if (m_bInEndAnim != 0) {
        // The end animation.
        if (m_pHost->IsAbilityAnimPhaseDone(this, 4) == 0) return 1;  // vt+0x80
        End(m_bForcedEnd);
        return 0;
    }
    float held;
    if (m_pHost->IsAbilityButtonDown(m_bButtonIndex) == 0 && m_pHost->GetAbilityButtonHoldTime(m_bButtonIndex, &held) == 0) {  // vt+0x8c / +0x94
        // Let go: the end animation, else the end.
        ReleaseAndStopFx();  // vt+0x88
        if (m_bInStartAnim == 0 && m_pHost->PlayAbilityAnim(this, 4) != 0) {
            m_bInEndAnim = 1;
            return 1;
        }
        End(0);
        return 0;
    }
    if (m_bInStartAnim != 0) {
        // The start animation, then the loop.
        if (m_pHost->IsAbilityAnimPhaseDone(this, 0) == 0) return 1;
        m_bAltLoopAnim = m_pHost->CanUseAltLoopAnim();  // vt+0x38
        if (m_bAltLoopAnim == 0 || m_pHost->PlayAbilityAnim(this, 2) == 0) m_pHost->PlayAbilityAnim(this, 1);
        m_bInStartAnim = 0;
        m_bInLoop = 1;
        if (Vf90() == 0) return 1;
        SetFxActive(1);  // vt+0x70
        return 1;
    }
    if (m_bInLoop == 0) return 0;

    // The mana.
    {
        const float before = m_fMana;
        const float rate = m_pHost->GetManaCostScale() * static_cast<float>(static_cast<double>(m_ai32ManaPerSecond[m_dwLevelIndex]));  // vt+0xc8
        m_fMana = ppc::fmadds(rate, dt, before);
        if (m_fMana >= 1.0f) {  // TOC +0x38d0 (cror gt|eq: a NaN does not spend)
            m_pHost->ConsumeAbilityMana(this, WholeMana(m_fMana));  // vt+0xb8
            const float mana = m_fMana;
            m_fMana = mana - static_cast<float>(static_cast<double>(WholeMana(mana)));
        }
        const uint32_t left = static_cast<uint32_t>(m_pHost->GetAbilityMana());  // vt+0xbc (clrldi: unsigned)
        if (!(static_cast<float>(static_cast<double>(left)) > m_fMana)) {           // ble
            // 0x3a764c: out of mana.
            ReleaseAndStopFx();  // vt+0x88
            StartEmitterFx();    // vt+0x78
            m_bForcedEnd = 1;
            if (m_pHost->PlayAbilityAnim(this, 4) != 0) {
                m_bInEndAnim = 1;
                return 1;
            }
            End(m_bForcedEnd);
            return 0;
        }
    }

    bool hold = true;  // 0x3a7380: the hold step (vt+0x84) runs
    if (m_bTargetHeld == 0) {
        // 0x3a7718: nothing held: aim and grab the locked target.
        m_pHost->ComputeAimDirection(0x1.921fb2p+0f, this, m_pAimCone);  // vt+0x58; TOC +0x38d4 (0x3fc90fd9)
        if (m_pHost->GetLockedTarget() != nullptr) {          // vt+0xd4
            CVector3 direction{0.0f, 0.0f, 0.0f};             // 0x00c50d64
            GrabTarget(1, 0, &direction);                     // vt+0x7c
            if (Vf90() == 0) SetFxActive(1);
            hold = false;  // to 0x3a73a8
        } else if (Vf90() == 0) {
            // 0x3a7868: the miss: the level's full cost at once, then the end.
            UpdateGrab();  // vt+0x74
            m_pHost->ConsumeAbilityMana(
                this, WholeMana(static_cast<float>(static_cast<double>(m_ai32ManaPerSecond[m_dwLevelIndex])) * m_afCooldown[m_dwLevelIndex]));  // vt+0xb8
            ReleaseAndStopFx();  // 0x3a7908
            if (m_pHost->PlayAbilityAnim(this, 4) != 0) {
                m_bInEndAnim = 1;
                return 1;
            }
            End(0);
            return 0;
        }
    } else {
        // 0x3a731c: held.
        if (Vf94() != 0) {
            // 0x3a7afc: the target followed: another locked target is grabbed and the effects restarted.
            m_pHost->ComputeAimDirection(0x1.921fb2p+0f, this, m_pAimCone);
            if (m_pTarget != m_pHost->GetLockedTarget() && m_pHost->GetLockedTarget() != nullptr) {
                CVector3 direction{0.0f, 0.0f, 0.0f};
                GrabTarget(1, 0, &direction);
                SetFxActive(0);
                SetFxActive(1);
            }
        }
        if (Vf80(dt) == 0) {
            // 0x3a7908: the hold is lost.
            ReleaseAndStopFx();
            if (m_pHost->PlayAbilityAnim(this, 4) != 0) {
                m_bInEndAnim = 1;
                return 1;
            }
            End(0);
            return 0;
        }
    }
    if (hold) Vf84(dt);  // vt+0x84

    // 0x3a73a8: the in-air state follows the host (vt+0x30); a change re-applies the control and the loop.
    bool changed = false;
    if (m_bInAir != 0) {
        if (m_pHost->IsOnGround() != 0) {
            m_bInAir = 0;
            changed = true;
        }
    } else if (m_pHost->IsOnGround() == 0) {
        m_bInAir = 1;
        changed = true;
    }
    if (changed) {
        // 0x3a7a30
        m_bAltLoopAnim = m_pHost->CanUseAltLoopAnim();  // vt+0x38
        ApplyHeroControl(1);
        if (m_bAltLoopAnim == 0 || m_pHost->PlayAbilityAnim(this, 2) == 0) m_pHost->PlayAbilityAnim(this, 1);
    }
    // 0x3a73e8: the alternative loop while the host allows it.
    if (m_bAltLoopAnim != 0) {
        if (m_pHost->CanUseAltLoopAnim() != 0) return 1;
        m_pHost->PlayAbilityAnim(this, 1);
        m_bAltLoopAnim = 0;
    }
    if (m_pHost->CanUseAltLoopAnim() == 0) return 1;
    if (m_pHost->PlayAbilityAnim(this, 2) == 0) return 1;
    m_bAltLoopAnim = 1;
    return 1;
}
