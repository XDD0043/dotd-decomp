// CKAttackMoveElement.cpp - reconstructed original translation unit 0x374d50-0x3798b8 (GAME_TOC1, main_toc1), 29 functions, 28 live.
// Primary class: CKAttackMoveElement  key 0x9a0c  category Logic  size 0x1a8  vtable 0xb23340
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x374d50  CKAttackMoveElement_Delete
//   [x] 0x374da0  CKAttackMoveElement_Construct
//   [ ] 0x374db0  CKAttackMoveElement_Construct_2  [dead]
//   [x] 0x374dc0  CKAttackMoveElement_GetAbilityId
//   [x] 0x374dc8  CKAttackMoveElement_GetFamilyId
//   [x] 0x374dd0  CKAttackMoveElement_Stop
//   [x] 0x374e60  CKAttackMoveElement_StopFxAndAttack
//   [x] 0x374ee0  CKAttackMoveElement_End
//   [x] 0x374ff8  CKAttackMoveElement_ApplyHeroControl
//   [x] 0x3756d0  CKAttackMoveElement_ResetRuntime
//   [x] 0x375720  CKAttackMoveElement_DeleteArray
//   [x] 0x3757c0  CKAttackMoveElement_StartEmitterFx
//   [ ] 0x375a88  RegisterCKAttackMoveElementClass
//   [ ] 0x375b10  _GLOBAL__D_375b10
//   [ ] 0x375b20  _GLOBAL__I_375b20
//   [x] 0x375b30  CKAttackMoveElement_ApplyDamageParams
//   [x] 0x3760b0  CKAttackMoveElement_Start
//   [x] 0x376238  CKAttackMoveElement_Update
//   [x] 0x376d90  CKAttackMoveElement_CreateArray
//   [x] 0x376e20  CKAttackMoveElement_Create
//   [x] 0x376e58  CKAttackMoveElement_RecursiveRegistration  (returns 1: the root's empty slot)
//   [x] 0x376e60  CKAttackMoveElement_PostLoad
//   [x] 0x376ea8  CKAttackMoveElement_Destroy  (empty)
//   [x] 0x376eb0  CKAttackMoveElement_SteerTowardsTarget_maybe
//   [x] 0x3774f0  CKAttackMoveElement_DestructBody  (C++ destructor chain: vtable stores only)
//   [x] 0x377510  CKAttackMoveElement_DeletingDestructor  (C++ deleting destructor)
//   [x] 0x377558  CKAttackMoveElement_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x377578  CKAttackMoveElement_Load
//   [ ] 0x378800  CKAttackMoveElement_Save
//
//   [ ] 0x9bf838  CKAttackMoveElement_GetClassType  [inline]
//   [ ] 0x9bf840  CKAttackMoveElement_GetClassID  [inline]
//   [x] 0x9bf848  CKAttackMoveElement_SetFxActive  [inline]
//   [x] 0x9bf850  CKAttackMoveElement_vf74  [inline]
//   [x] 0x9bf858  CKAttackMoveElement_UpdateAttack_maybe  [inline]
//   [x] 0x9bf860  CKAttackMoveElement_UpdateMovement_maybe  [inline]
//   [x] 0x9bf868  CKAttackMoveElement_vf8C  [inline]
//   [x] 0x9bf870  CKAttackMoveElement_IsKindOfClass  [inline]
//   [ ] 0x9bf8a8  KBase90CC_DeletingDestructor  [inline]
//   [ ] 0x9bf8e8  CKAbilityElement_maybe_Destructor  [inline]
#include "k2000/logic/CKAttackMoveElement.h"

#include <cmath>
#include <cstring>

#include "Spyro2008/logic/CKS08ElementDamage.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "Spyro2008/misc/CKS08AbilityHostBase.h"
#include "crt/ppc_ops.h"
#include "crt/xsinf.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"

namespace {
float GameClockNow() { return g_pEngine->m_timeManager->m_pTime->m_afCurrentTime[0]; }  // TOC +0x3134 -> +0x48 -> +0x04 -> +0x04

// 0x00a70810 (TOC +0x3158): the damage type of each ability id; +0x68 (0x00a70878) the element of each ability's ground
// trail (0 fire, 1 ice; 3 none). The same values as CKBreathElement's copies (0x00a708cc / 0x00a70934).
constexpr uint32_t kAbilityDamageTypes[26] = {0, 0, 1, 1, 2, 2, 3, 3, 8, 8, 4, 4, 5, 5, 5, 6, 9, 7, 7, 9, 6, 0, 0, 0, 0, 0};
constexpr uint32_t kAbilityGroundElements[26] = {0, 0, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 1, 1, 2};

// 0x00c50d64 (TOC +0x3178) the null vector, 0x00c50d40 (TOC +0x3174) the y axis.
constexpr CVector3 kNullVector = {0.0f, 0.0f, 0.0f};
constexpr CVector3 kAxisY = {0.0f, 1.0f, 0.0f};

constexpr float kDegToRad = 0x1.1df468p-6f;    // TOC +0x3168 (0x3c8efa34)
constexpr float kRandMax = 65535.0f;           // TOC +0x3160 (0x477fff00)
constexpr float kRandScale = -0x1.000100p-15f;  // TOC +0x316c (0xb8000080)

bool SignBitSet(float x) {
    int32_t bits;
    std::memcpy(&bits, &x, sizeof(bits));
    return bits < 0;
}
// The inlined cosf: the single-precision polynomial for a non-negative argument (by its sign bit), the library's cosf
// 0x009a11d8 of the magnitude otherwise.
float GameCosf(float x) { return SignBitSet(x) ? crt::LibCosf(-x) : crt::InlineCosf(x); }
// The sign bit cleared through memory (the original's stfs / rlwinm / lwz).
float ClearSign(float x) {
    uint32_t bits;
    std::memcpy(&bits, &x, sizeof(bits));
    bits &= 0x7fffffffu;
    std::memcpy(&x, &bits, sizeof(bits));
    return x;
}
// 0x00010690 Math_Sqrtf
float Sqrtf(float x) { return static_cast<float>(std::sqrt(static_cast<double>(x))); }
float RandUnit16() { return static_cast<float>(static_cast<double>(static_cast<uint32_t>(Rand_Int()) & 0xffffu)); }
// The mana cost of the level: fctidz of the host's scale times the cost (its low word).
uint32_t ManaCost(float scale, int32_t cost) {
    return static_cast<uint32_t>(ppc::fctidz(scale * static_cast<float>(static_cast<double>(cost))));
}
}  // namespace

// 0x00377578 CKAttackMoveElement_Load: only for type 0 (K_LEVEL_PLATEFORMS); 366 bytes: three passes over
// eighteen per-index fields, then single fields and two object references. No base Load is called.
int32_t CKAttackMoveElement::Load(IKFile* file, int32_t type) {
    if (type == 0) {
        for (int32_t i = 0; i < 3; ++i) {
            ReadS32LE(file, &m_ai32Damage[i]);
            ReadF32LE(file, &m_afCooldown[i]);
            ReadS32LE(file, &m_ai32ManaCost[i]);
            ReadF32LE(file, &m_afAttackDuration[i]);
            ReadF32LE(file, &m_afDisarmAmount[i]);
            ReadF32LE(file, &m_afStunAmount[i]);
            ReadF32LE(file, &m_afElementEffect0[i]);
            ReadF32LE(file, &m_afElementEffect1[i]);
            ReadF32LE(file, &m_afElementEffect2[i]);
            ReadF32LE(file, &m_afElementEffect4[i]);
            ReadF32LE(file, &m_afElementEffect6[i]);
            ReadF32LE(file, &m_afElementEffect5[i]);
            ReadF32LE(file, &m_afElementEffect7[i]);
            ReadU8(file, &m_abDamageFlag34[i]);
            ReadU8(file, &m_abDamageFlag35[i]);
            ReadF32LE(file, &m_afSteerImpulseStrength[i]);
            ReadF32LE(file, &m_afImpulseDuration[i]);
            ReadF32LE(file, &m_afImpulseStrength[i]);
        }
        ReadU8(file, &m_bGroundPerm1);
        ReadU8(file, &m_bGroundPerm0);
        ReadU8(file, &m_bGroundTurnEnable);
        ReadF32LE(file, &m_fGroundTurnA);
        ReadF32LE(file, &m_fGroundTurnB);
        ReadF32LE(file, &m_fGroundMoveSpeed);
        ReadU8(file, &m_bFlyPerm1);
        ReadU8(file, &m_bFlyPerm0);
        ReadU8(file, &m_bFlyTurnEnable);
        ReadF32LE(file, &m_fFlyTurnA);
        ReadF32LE(file, &m_fFlyTurnB);
        ReadF32LE(file, &m_fFlyMoveSpeed);
        ReadU8(file, &m_bGroundParam11f8Enable);
        ReadU8(file, &m_bFlyParam11f8Enable);
        ReadF32LE(file, &m_fGroundParam11f8);
        ReadF32LE(file, &m_fFlyParam11f8);
        ReadF32LE(file, &m_afElementEffect3[0]);
        ReadF32LE(file, &m_afElementEffect3[1]);
        ReadF32LE(file, &m_afElementEffect3[2]);
        ReadF32LE(file, &m_afImpulseDelay[0]);
        ReadF32LE(file, &m_afImpulseDelay[1]);
        ReadF32LE(file, &m_afImpulseDelay[2]);
        ReadF32LE(file, &m_fWindUpDuration);
        IKFile_ReadRef(file, &m_pElementDamage);
        ReadU8(file, &m_bAirPerm1);
        ReadU8(file, &m_bAirPerm0);
        ReadU8(file, &m_bAirTurnEnable);
        ReadF32LE(file, &m_fAirTurnA);
        ReadF32LE(file, &m_fAirTurnB);
        ReadF32LE(file, &m_fAirMoveSpeed);
        ReadU8(file, &m_bAirParam11f8Enable);
        ReadF32LE(file, &m_fAirParam11f8);
        ReadF32LE(file, &m_fGroundTrailPeriod);
        ReadF32LE(file, &m_fGroundTrailPeriodSpread);
        ReadF32LE(file, &m_fGroundTrailScatterRadius);
        ReadF32LE(file, &m_fGroundTrailHeight);
        ReadF32LE(file, &m_fGroundTrailHeightSpread);
        ReadF32LE(file, &m_afCooldownForced[0]);
        ReadF32LE(file, &m_afCooldownForced[1]);
        ReadF32LE(file, &m_afCooldownForced[2]);
        IKFile_ReadRef(file, &m_pFizzleExplosionFxData);
        ReadF32LE(file, &m_afSteerPitchDeg[0]);
        ReadF32LE(file, &m_afSteerPitchDeg[1]);
        ReadF32LE(file, &m_afSteerPitchDeg[2]);
        ReadF32LE(file, &m_afKnockbackImpulse[0]);
        ReadF32LE(file, &m_afKnockbackImpulse[1]);
        ReadF32LE(file, &m_afKnockbackImpulse[2]);
        ReadF32LE(file, &m_fKnockbackPitchDeg);
        ReadF32LE(file, &m_fKnockbackPitchSpread);
        ReadF32LE(file, &m_fPitchLimitMinHeight);
        ReadF32LE(file, &m_fPitchLimitMaxHeight);
    }
    return 1;
}

// 0x003756d0 CKAttackMoveElement_ResetRuntime
void CKAttackMoveElement::ResetRuntime(int32_t /*type*/) {
    m_fStartTime = -1.0f;  // 0xbf800000
    m_bImpulseStarted = 0;
    m_ui8HotSpotIndex = 0xff;
    m_fGroundTrailTimer = 0.0f;
    m_pHost = nullptr;
    m_ui32LevelIndex = 0;
    m_bRunning = 0;
    m_bInLoop = 0;
    m_bInStartAnim = 0;
    m_bInEndAnim = 0;
    m_fElapsedTime = 0.0f;
    m_fImpulseStartTime = 0.0f;
    m_unk187 = 0;
    m_bSteered = 0;
}

// 0x003760b0 CKAttackMoveElement_Start
void CKAttackMoveElement::Start(CKS08AbilityHostBase* host) {
    if (m_bRunning != 0 || host == nullptr) return;
    m_bImpulseStarted = 0;
    m_pHost = host;
    m_bInLoop = 0;
    m_bInStartAnim = 0;
    m_bInEndAnim = 0;
    m_bManaPending = 0;
    m_bForcedEnd = 0;
    m_bSteered = 0;
    m_fElapsedTime = 0.0f;
    m_fImpulseStartTime = 0.0f;
    m_bRunning = 1;
    m_ui32LevelIndex = host->GetAbilityLevelIndex(this);  // vt+0xf4
    ApplyHeroControl(1);                          // vt+0x68
    m_fGroundTrailTimer = 0.0f;
    if (m_pHost->PlayAbilityAnim(this, 0) != 0) {  // vt+0x7c
        m_bInStartAnim = 1;
    } else if (m_pHost->PlayAbilityAnim(this, 1) != 0) {
        m_bManaPending = 1;
        m_bInLoop = 1;
    }
    m_fStartTime = GameClockNow();
}

// 0x00374dd0 CKAttackMoveElement_Stop
void CKAttackMoveElement::Stop(int32_t forced) {
    if (m_bRunning == 0) return;
    StopFxAndAttack();  // vt+0x84
    End(forced);        // vt+0x64
}

// 0x00374e60 CKAttackMoveElement_StopFxAndAttack
void CKAttackMoveElement::StopFxAndAttack() {
    SetFxActive(0);      // vt+0x70
    SetAttackActive(0);  // vt+0x74
    m_bInLoop = 0;
}

// 0x00374ee0 CKAttackMoveElement_End
void CKAttackMoveElement::End(int32_t forced) {
    ApplyHeroControl(0);                // vt+0x68
    m_pHost->ClearAbilityImpulse(this);  // vt+0x60
    m_bRunning = 0;
    const float cooldown = forced != 0 ? m_afCooldownForced[m_ui32LevelIndex] : m_afCooldown[m_ui32LevelIndex];
    m_pHost->SetAbilityCooldown(cooldown, this, static_cast<uint8_t>((forced ^ 1) & 0xff));  // vt+0x9c
    m_pHost = nullptr;
}

// 0x00374ff8 CKAttackMoveElement_ApplyHeroControl. The 11f8 gates (vt+0x68): a context's own byte when its permission 0
// byte (+0x135 / +0x141 / +0x161) is clear.
void CKAttackMoveElement::ApplyHeroControl(uint8_t on) {
    CKS08AbilityHostBase* host = m_pHost;
    if (on != 0) {
        host->SetHeroActionPermission(0, m_bGroundPerm0, m_bFlyPerm0, m_bAirPerm0);  // vt+0x44
        host->SetHeroActionPermission(1, m_bGroundPerm1, m_bFlyPerm1, m_bAirPerm1);
        host->SetHeroActionPermission(3, 1, 1, 1);
        host->SetHeroActionPermission(4, 1, 1, 1);
        host->SetHeroActionPermission(2, 1, 1, 1);
        host->SetHeroActionPermission(5, 0, 0, 0);
        host->SetHeroActionPermission(6, 1, 1, 1);
        host->SetHeroActionPermission(8, 1, 1, 1);
        host->SetAbilityTurnParams(m_fGroundTurnA, m_fGroundTurnB, m_fFlyTurnA, m_fFlyTurnB, m_fAirTurnA, m_fAirTurnB, m_bGroundTurnEnable, m_bFlyTurnEnable,
                                   m_bAirTurnEnable);  // vt+0x64
        const uint8_t gateAir = m_bGroundPerm0 == 0 ? static_cast<uint8_t>(m_bGroundParam11f8Enable != 0) : 0;
        const uint8_t gateFly = m_bFlyPerm0 == 0 ? static_cast<uint8_t>(m_bFlyParam11f8Enable != 0) : 0;
        const uint8_t gateGround = m_bAirPerm0 == 0 ? static_cast<uint8_t>(m_bAirParam11f8Enable != 0) : 0;
        host->SetAbilityParam11f8(m_fGroundParam11f8, m_fFlyParam11f8, m_fAirParam11f8, gateAir, gateFly, gateGround);  // vt+0x68
        host->SetAbilityMoveSpeed(m_fGroundMoveSpeed, m_fFlyMoveSpeed, m_fAirMoveSpeed);                               // vt+0x50
        host->SetAbilityMoveSpeedEnabled(1);                                                   // vt+0x54
        const uint8_t inAir = static_cast<uint8_t>(host->IsOnGround() ^ 1);                 // vt+0x30
        m_bInAir = inAir;
        host->SetAbilityHeroMode(this, inAir);  // vt+0x70
        return;
    }
    host->SetHeroActionPermission(0, 0, 0, 0);
    host->SetHeroActionPermission(1, 0, 0, 0);
    host->SetHeroActionPermission(2, 0, 0, 0);
    host->SetHeroActionPermission(3, 0, 0, 0);
    host->SetHeroActionPermission(4, 0, 0, 0);
    host->SetHeroActionPermission(5, 0, 0, 0);
    host->SetHeroActionPermission(6, 0, 0, 0);
    host->SetHeroActionPermission(8, 0, 0, 0);
    host->SetHeroActionPermission(9, 0, 0, 0);
    host->SetAbilityTurnParams(m_fGroundTurnA, m_fGroundTurnB, m_fFlyTurnA, m_fFlyTurnB, m_fAirTurnA, m_fAirTurnB, 0, 0, 0);
    host->SetAbilityParam11f8(m_fGroundParam11f8, m_fFlyParam11f8, m_fAirParam11f8, 0, 0, 0);
    host->SetAbilityMoveSpeedEnabled(0);
    host->SetAbilityHeroMode(this, 0);
}

// 0x003757c0 CKAttackMoveElement_StartEmitterFx: the inlined pooled lookup (CKSrvFx::AcquireFx) of the explosion data's
// effect, owned by this element.
void CKAttackMoveElement::StartEmitterFx() {
    IKFxData* data = reinterpret_cast<IKFxData*>(m_pFizzleExplosionFxData);
    CKSrvFx* fxService = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
    CKExplosionNodeFx* fx = static_cast<CKExplosionNodeFx*>(fxService->AcquireFx(data, this));
    if (fx == nullptr) return;
    const CVector3 position = m_pHost->GetHotspotPosition(m_ui8HotSpotIndex);  // vt+0xd0
    fx->SetTranslation(&position, this);  // 0x001b66e8
    fx->Trigger(this, 0);                 // 0x001b82a8
    fx->ReleaseReservation(this);         // vt+0x54
}

// 0x00375b30 CKAttackMoveElement_ApplyDamageParams: one Rand_Int draw (the knock angle +0x18).
void CKAttackMoveElement::ApplyDamageParams(uint8_t continuous) {
    const float damageScale = m_pHost->GetDamageScale();  // vt+0xc0
    const float effectScale = m_pHost->GetEffectScale();  // vt+0xc4
    const uint32_t level = m_ui32LevelIndex;
    CKS08ElementDamage* damage = static_cast<CKS08ElementDamage*>(m_pElementDamage);
    damage->SetAmount(damageScale * static_cast<float>(static_cast<double>(m_ai32Damage[level])));  // vt+0x50
    damage->SetStun(m_afStunAmount[level]);                    // vt+0x5c
    damage->SetDisarmAmount(m_afDisarmAmount[level]);            // vt+0x60
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
    damage->SetDamageType(kAbilityDamageTypes[GetAbilityId() & 0xffu]);  // vt+0x64 (TOC +0x3158)
    damage->SetAbilityId(GetAbilityId());                                 // vt+0x68
    damage->m_fKnockbackForce = m_afKnockbackImpulse[level] / 0.2f;  // TOC +0x315c
    damage->m_fKnockbackTime = 0.2f;
    const float base = m_fKnockbackPitchDeg + m_fKnockbackPitchSpread;
    const float t = RandUnit16() / kRandMax * -2.0f;  // 0x00011500; TOC +0x3164
    const float angle = ppc::fmadds(t, m_fKnockbackPitchSpread, base) * kDegToRad;
    std::memcpy(&damage->m_unk18, &angle, sizeof(angle));
    damage->SetContinuous(continuous);  // vt+0x54
}

// 0x00376eb0 CKAttackMoveElement_SteerTowardsTarget_maybe. The pitch: below the speed +0x12c (or at an angle of 180 and
// more) the full 360 - angle; from +0x130 on: 180 (angle 90 and more) or 360, the impulse scaled by |cos angle|; between
// them the angle is held inside 90 +- 90 x the speed's fraction, the impulse scaled by |cos angle / cos bound|.
void CKAttackMoveElement::SteerTowardsTarget(const CVector3* direction) {
    CVector3 at = *direction;
    if (at.x == kNullVector.x && at.y == kNullVector.y && at.z == kNullVector.z) at = m_pHost->GetHeroForward();  // vt+0x18
    const CVector3 up = m_pHost->GetOwnerUp();  // vt+0x2c GetHeroUp
    CMatrix34 basis{};
    Mat4_SetBasisFromAtUp(&basis, &at, &up);  // 0x0023fd30
    const float angle = m_afSteerPitchDeg[m_ui32LevelIndex];               // f30
    const float speed = m_pHost->Vf34();  // vt+0x34 (the hero: GetHeightAboveGround)
    float degrees;
    float scale;
    if (!(speed >= m_fPitchLimitMaxHeight)) {
        bool held = false;
        float upper = 0.0f;  // f27
        float lower = 0.0f;  // f28
        if (speed > m_fPitchLimitMinHeight) {
            const float range = m_fPitchLimitMaxHeight - m_fPitchLimitMinHeight;
            const float fraction = (speed - m_fPitchLimitMinHeight) / range;
            const float spread = fraction * 90.0f;  // TOC +0x31c0
            upper = spread + 90.0f;
            if (angle < upper) {  // bge: a NaN angle takes the default
                lower = 90.0f - spread;
                held = angle > lower;
            }
        }
        if (!held) {
            degrees = 360.0f - angle;  // TOC +0x31bc
            scale = 1.0f;
        } else if (angle == 90.0f) {
            degrees = 360.0f - upper;
            scale = 0.0f;
        } else {
            const float cosine = GameCosf(angle * kDegToRad);
            const float bound = GameCosf(lower * kDegToRad);
            scale = ClearSign(cosine / bound);
            degrees = angle >= 90.0f ? 360.0f - upper : 360.0f - lower;
        }
    } else if (!(angle < 180.0f)) {  // TOC +0x31b8; bge
        degrees = 360.0f - angle;
        scale = 1.0f;
    } else {
        scale = ClearSign(GameCosf(angle * kDegToRad));
        degrees = angle >= 90.0f ? 180.0f : 360.0f;
    }
    Mat4_RotateLocalXDeg(degrees, &basis);  // 0x00241118
    const CVector3 aim = basis.m_at;
    m_pHost->SetAbilityImpulse(this, (scale * m_afSteerImpulseStrength[m_ui32LevelIndex]) / 0.001f, 0.001f, &aim);  // vt+0x5c; TOC +0x31c4
    m_bImpulseStarted = 0;
    m_bSteered = 1;
    m_fImpulseStartTime = m_fElapsedTime + m_afImpulseDelay[m_ui32LevelIndex];
}

// 0x00376238 CKAttackMoveElement_Update. Rand_Int: one draw per frame while attacking (the damage's knock angle), and five
// per ground trail (fire attack moves, IsGroundTrailActive). The float tests keep the original's senses.
uint8_t CKAttackMoveElement::Update(float dt) {
    if (m_bRunning == 0) return 0;
    if (m_fStartTime == GameClockNow()) return 1;
    m_fElapsedTime = dt + m_fElapsedTime;
    if (m_bSteered == 0) {
        // The wind-up, then the steer (the mana checked first when the move started in the loop).
        if (m_fWindUpDuration <= m_fElapsedTime) {
            bool steer = true;
            if (m_bManaPending != 0) {
                const uint32_t mana = static_cast<uint32_t>(m_pHost->GetAbilityMana());  // vt+0xbc
                const float costScale = m_pHost->GetManaCostScale();                     // vt+0xc8
                if (ManaCost(costScale, m_ai32ManaCost[m_ui32LevelIndex]) > mana) {
                    // Out of mana: the fizzle and the end animation.
                    steer = false;
                    StartEmitterFx();  // vt+0x80
                    m_bForcedEnd = 1;
                    if (m_pHost->PlayAbilityAnim(this, 4) == 0) {
                        End(m_bForcedEnd);  // vt+0x64
                        return 0;
                    }
                    m_bInLoop = 0;
                    m_bInEndAnim = 1;
                    m_bInStartAnim = 0;
                    m_bSteered = 1;
                    if (m_pHost->IsAbilityAnimPhaseDone(this, 4) == 0) return 1;  // vt+0x80
                    End(m_bForcedEnd);
                    return 0;
                }
            }
            if (steer) {
                const CVector3 none = kNullVector;
                SteerTowardsTarget(&none);  // vt+0x90
                SetFxActive(1);             // vt+0x70
            }
        }
    } else {
        // Steered: the attack runs, the damage's knock angle is drawn, the impulse starts at its time.
        UpdateAttack(dt);  // vt+0x78
        const float base = m_fKnockbackPitchDeg + m_fKnockbackPitchSpread;
        CKS08ElementDamage* damage = static_cast<CKS08ElementDamage*>(m_pElementDamage);
        const float t = RandUnit16() / kRandMax * -2.0f;  // 0x00011500
        const float angle = ppc::fmadds(t, m_fKnockbackPitchSpread, base) * kDegToRad;
        std::memcpy(&damage->m_unk18, &angle, sizeof(angle));
        if (m_bImpulseStarted == 0 && m_fElapsedTime >= m_fImpulseStartTime) {
            CKS08AbilityHostBase* host = m_pHost;
            const float first = -m_afImpulseStrength[m_ui32LevelIndex];
            const float second = m_afImpulseDuration[m_ui32LevelIndex];
            const CVector3 forward = host->GetHeroForward();  // vt+0x18
            host->SetAbilityImpulse(this, first, second, &forward);  // vt+0x5c
            m_bImpulseStarted = 1;
        }
    }
    if (m_bInEndAnim != 0) {
        // The end animation.
        if (m_pHost->IsAbilityAnimPhaseDone(this, 4) == 0) return 1;  // vt+0x80
        End(m_bForcedEnd);
        return 0;
    }
    if (m_bInStartAnim != 0) {
        // The start animation; then the mana taken and the loop, or the fizzle.
        if (m_pHost->IsAbilityAnimPhaseDone(this, 0) == 0) return 1;
        const float costScale = m_pHost->GetManaCostScale();
        const uint32_t cost = ManaCost(costScale, m_ai32ManaCost[m_ui32LevelIndex]);
        if (cost > static_cast<uint32_t>(m_pHost->GetAbilityMana())) {
            StartEmitterFx();
            m_bForcedEnd = 1;
            if (m_pHost->PlayAbilityAnim(this, 4) == 0) {
                End(m_bForcedEnd);
                return 0;
            }
            m_bInEndAnim = 1;
            m_bInStartAnim = 0;
            return 1;
        }
        m_pHost->ConsumeAbilityMana(this, cost);  // vt+0xb8
        m_pHost->PlayAbilityAnim(this, 1);
        m_bInLoop = 1;
        m_bInStartAnim = 0;
        return 1;
    }
    if (m_bInLoop == 0) return 0;
    if (m_bManaPending != 0) {
        // Started in the loop: the mana taken now, or the fizzle.
        m_bManaPending = 0;
        const float costScale = m_pHost->GetManaCostScale();
        const uint32_t cost = ManaCost(costScale, m_ai32ManaCost[m_ui32LevelIndex]);
        if (cost > static_cast<uint32_t>(m_pHost->GetAbilityMana())) {
            StartEmitterFx();
            m_bForcedEnd = 1;
            if (m_pHost->PlayAbilityAnim(this, 4) == 0) {
                End(m_bForcedEnd);
                return 0;
            }
            m_bInEndAnim = 1;
            m_bInLoop = 0;
            return 1;
        }
        m_pHost->ConsumeAbilityMana(this, cost);
        return 1;
    }
    // The loop: the attack for +0x44[level] seconds, then the end animation.
    m_fElapsedTime = dt + m_fElapsedTime;
    if (m_afAttackDuration[m_ui32LevelIndex] < m_fElapsedTime) {
        StopFxAndAttack();  // vt+0x84
        if (m_pHost->PlayAbilityAnim(this, 4) != 0) {
            m_bInEndAnim = 1;
            m_bInLoop = 0;
            return 1;
        }
        End(0);
        return 0;
    }
    if (IsGroundTrailActive() != 0) {  // vt+0x8c
        // The ground trail of the fire element: a scorch at the hot spot 0 every +0x5c (+- +0x60) seconds.
        m_fGroundTrailTimer = m_fGroundTrailTimer - dt;
        const uint32_t element = kAbilityGroundElements[GetAbilityId() & 0xffu];  // TOC +0x3158 -> +0x68
        if (element <= 1 && m_fGroundTrailTimer <= 0.0f) {
            const float period = m_fGroundTrailPeriod + m_fGroundTrailPeriodSpread;
            m_fGroundTrailTimer = ppc::fmadds(RandUnit16() / kRandMax * -2.0f, m_fGroundTrailPeriodSpread, period);
            const CVector3 spot = m_pHost->GetHotspotPosition(0);  // vt+0xd0
            // A random horizontal direction.
            float dx = ppc::fmadds(RandUnit16(), kRandScale, 1.0f);
            float dz = ppc::fmadds(RandUnit16(), kRandScale, 1.0f);
            float dy = 0.0f;
            const float length = Sqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, 0.0f)));  // 0x00010690
            if (length != 0.0f) {
                const float inverse = 1.0f / length;
                dz = dz * inverse;
                dx = dx * inverse;
                dy = inverse * 0.0f;
            }
            const float scatter = RandUnit16() / kRandMax * m_fGroundTrailScatterRadius;
            const float height = m_fGroundTrailHeight + m_fGroundTrailHeightSpread;
            CVector3 at;
            // BUG(original): the scattered point is overwritten by the next one (both from the hot spot); the draws stay.
            at.z = ppc::fmadds(scatter, dz, spot.z);
            at.x = ppc::fmadds(dx, scatter, spot.x);
            at.y = ppc::fmadds(scatter, dy, spot.y);
            const float lift = ppc::fmadds(RandUnit16() / kRandMax * -2.0f, m_fGroundTrailHeightSpread, height);
            at.z = ppc::fmadds(lift, kAxisY.z, spot.z);
            at.x = ppc::fmadds(lift, kAxisY.x, spot.x);
            at.y = ppc::fmadds(lift, kAxisY.y, spot.y);
            CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
            manager->SpawnElementGroundFx(this, element, &at);  // 0x004fb848
        }
    }
    UpdateMovement(dt);  // vt+0x7c
    // The hero control follows the in-air state (vt+0x30).
    if (m_bInAir != 0) {
        if (m_pHost->IsOnGround() != 0) {
            m_bInAir = 0;
            ApplyHeroControl(1);
            return 1;
        }
        if (m_bInAir != 0) return 1;
    }
    if (m_pHost->IsOnGround() != 0) return 1;
    m_bInAir = 1;
    ApplyHeroControl(1);
    return 1;
}
