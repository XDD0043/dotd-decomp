// CKBreathElement.cpp - reconstructed original translation unit 0x380ed0-0x385a78 (GAME_TOC1, main_toc1), 30 functions, 29 live.
// Primary class: CKBreathElement  key 0x914c  category Logic  size 0x178  vtable 0xb23588
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x380ed0  CKBreathElement_Delete
//   [ ] 0x380f20  CKBreathElement_Construct_2  [dead]
//   [x] 0x380f40  CKBreathElement_GetAbilityId
//   [x] 0x380f48  CKBreathElement_GetFamilyId
//   [x] 0x380f50  CKBreathElement_Start
//   [x] 0x381190  CKBreathElement_Stop
//   [x] 0x381220  CKBreathElement_End
//   [x] 0x381330  CKBreathElement_ApplyHeroControl
//   [x] 0x381928  CKBreathElement_StopBreathing
//   [x] 0x381980  CKBreathElement_ApplyDamageParams
//   [x] 0x381eb8  CKBreathElement_Construct
//   [x] 0x381ed8  CKBreathElement_ResetRuntime
//   [x] 0x381f88  CKBreathElement_DeleteArray
//   [x] 0x382028  CKBreathElement_StartEmitterFx
//   [ ] 0x3822f0  RegisterCKBreathElementClass
//   [ ] 0x382378  _GLOBAL__D_382378
//   [ ] 0x382388  _GLOBAL__I_382388
//   [x] 0x382398  CKBreathElement_GetEmitterPosition
//   [x] 0x382430  CKBreathElement_Update
//   [x] 0x382c80  CKBreathElement_CreateArray
//   [x] 0x382d40  CKBreathElement_Create
//   [x] 0x382d90  CKBreathElement_RecursiveRegistration  (returns 1: the root's empty slot)
//   [x] 0x382d98  CKBreathElement_PostLoad
//   [x] 0x382de0  CKBreathElement_Destroy  (empty)
//   [x] 0x382de8  CKBreathElement_Destructor  (~CKBreathElement in the header)
//   [x] 0x382e68  CKBreathElement_UpdateDamageSpheres
//   [x] 0x383bb0  CKBreathElement_DestructBody  (~CKBreathElement in the header)
//   [x] 0x383c30  CKBreathElement_Load
//   [x] 0x384ba8  CKBreathElement_DeletingDestructor  (C++ deleting destructor)
//   [ ] 0x384c30  CKBreathElement_Save
//
//   [ ] 0x9bfa10  CKBreathElement_GetClassType  [inline]
//   [ ] 0x9bfa18  CKBreathElement_GetClassID  [inline]
//   [x] 0x9bfa20  CKBreathElement_SetFxActive  [inline]
//   [x] 0x9bfa28  CKBreathElement_UpdateFx  [inline]
//   [ ] 0x9bfa30  CKBreathElement_IsKindOfClass  [inline]
#include "k2000/logic/CKBreathElement.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/logic/CKS08ElementDamage.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "Spyro2008/misc/CKS08HeroAbilityHost.h"
#include "crt/ppc_ops.h"
#include "crt/xatan.h"
#include "crt/xsinf.h"
#include "crt/xtanf.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CKDynamicBoundingSphere.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/services/ICollisionMesh.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"

namespace {
float GameClockNow() { return g_pEngine->m_timeManager->m_pTime->m_afCurrentTime[0]; }  // TOC +0x3304 -> +0x48 -> +0x04 -> +0x04
CKSrvCollision* Collision() { return static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision); }

// 0x00a708cc (TOC +0x330c): the damage type of each ability id (the breath base's id 21 reads the zero after them).
constexpr uint32_t kAbilityDamageTypes[26] = {0, 0, 1, 1, 2, 2, 3, 3, 8, 8, 4, 4, 5, 5, 5, 6, 9, 7, 7, 9, 6, 0, 0, 0, 0, 0};
// 0x00a70934 (the same TOC word + 0x68): the element of each ability's ground scorch (0 fire, 1 ice; 3 none).
constexpr uint32_t kAbilityGroundElements[26] = {0, 0, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0};

// The shared axes and the null vector (0x00c50d34 x, 0x00c50d40 y, 0x00c50d64; zero in the EBOOT's BSS, filled by static
// initialisers).
constexpr CVector3 kAxisX = {1.0f, 0.0f, 0.0f};
constexpr CVector3 kAxisY = {0.0f, 1.0f, 0.0f};
constexpr CVector3 kNullVector = {0.0f, 0.0f, 0.0f};

constexpr float kDegToRad = 0x1.1df468p-6f;   // TOC +0x337c (0x3c8efa34)
constexpr float kMinRadius = 0x1.0624dep-10f;  // TOC +0x3384 (0x3a83126f, 0.001)
constexpr float kRandMax = 65535.0f;           // TOC +0x3388 (0x477fff00)
constexpr float kRandScale = -0x1.000100p-15f;  // TOC +0x3390 (0xb8000080)

bool SignBitSet(float x) {
    int32_t bits;
    std::memcpy(&bits, &x, sizeof(bits));
    return bits < 0;
}
// The inlined sinf: the single-precision polynomial for a non-negative argument (by its sign bit), the library's sinf
// 0x009a1390 of the magnitude, negated, otherwise.
float GameSinf(float x) { return SignBitSet(x) ? -crt::LibSinf(-x) : crt::InlineSinf(x); }
// 0x00010690 Math_Sqrtf
float Sqrtf(float x) { return static_cast<float>(std::sqrt(static_cast<double>(x))); }
float RandUnit16() { return static_cast<float>(static_cast<double>(static_cast<uint32_t>(Rand_Int()) & 0xffffu)); }
}  // namespace

// 0x00381eb8 CKBreathElement_Construct: the vtable, then three runtime words (CKBreathElement_Create inlines the same).
CKBreathElement::CKBreathElement() {
    m_pSegments = nullptr;
    m_ui32SegmentCapacity = 1;
    m_ui32SegmentCount = 0;
}

// 0x00383c30 CKBreathElement_Load: level data only (type 0, K_LEVEL_PLATEFORMS); 0x133 bytes. Three rows of
// fourteen words and two bytes, then the scalars and two references; every word byte-swapped.
int32_t CKBreathElement::Load(IKFile* file, int32_t type) {
    if (type == 0) {
        for (int32_t i = 0; i < 3; ++i) {
            ReadS32LE(file, &m_unk08[i]);
            ReadF32LE(file, &m_unk20[i]);
            ReadS32LE(file, &m_unk38[i]);
            ReadF32LE(file, &m_unk44[i]);
            ReadF32LE(file, &m_unk50[i]);
            ReadF32LE(file, &m_unk5c[i]);
            ReadF32LE(file, &m_unk68[i]);
            ReadF32LE(file, &m_unk74[i]);
            ReadF32LE(file, &m_unk80[i]);
            ReadF32LE(file, &m_unk8c[i]);
            ReadF32LE(file, &m_unk98[i]);
            ReadF32LE(file, &m_unkA4[i]);
            ReadF32LE(file, &m_unkB0[i]);
            ReadF32LE(file, &m_unkBc[i]);
            ReadU8(file, &m_unkD4[i]);
            ReadU8(file, &m_unkD7[i]);
        }
        ReadU8(file, &m_unkDa);
        ReadU8(file, &m_unkDb);
        ReadU8(file, &m_unkDc);
        ReadF32LE(file, &m_unkE0);
        ReadF32LE(file, &m_unkE4);
        ReadF32LE(file, &m_unkF4);
        ReadU8(file, &m_unkE8);
        ReadU8(file, &m_unkE9);
        ReadU8(file, &m_unkEa);
        ReadF32LE(file, &m_unkEc);
        ReadF32LE(file, &m_unkF0);
        ReadF32LE(file, &m_unkF8);
        ReadF32LE(file, &m_unk130);
        ReadF32LE(file, &m_unk134);
        ReadF32LE(file, &m_unk138);
        ReadU8(file, &m_unkFc);
        ReadU8(file, &m_unkFd);
        ReadF32LE(file, &m_unk100);
        ReadF32LE(file, &m_unk104);
        ReadF32LE(file, &m_unkC8[0]);
        ReadF32LE(file, &m_unkC8[1]);
        ReadF32LE(file, &m_unkC8[2]);
        IKFile_ReadRef(file, &m_unk170);
        ReadU8(file, &m_unk108);
        ReadU8(file, &m_unk109);
        ReadU8(file, &m_unk10a);
        ReadF32LE(file, &m_unk10c);
        ReadF32LE(file, &m_unk110);
        ReadF32LE(file, &m_unk114);
        ReadU8(file, &m_unk118);
        ReadF32LE(file, &m_unk11c);
        ReadF32LE(file, &m_unk13c);
        ReadF32LE(file, &m_unk140);
        ReadF32LE(file, &m_unk144);
        ReadF32LE(file, &m_unk148);
        ReadF32LE(file, &m_unk2c[0]);
        ReadF32LE(file, &m_unk2c[1]);
        ReadF32LE(file, &m_unk2c[2]);
        IKFile_ReadRef(file, &m_unk120);
        ReadF32LE(file, &m_unk14[0]);
        ReadF32LE(file, &m_unk14[1]);
        ReadF32LE(file, &m_unk14[2]);
        ReadU8(file, &m_unk14c);
    }
    return 1;
}

// 0x00380f50 CKBreathElement_Start
void CKBreathElement::Start(CKS08AbilityHostBase* host) {
    if (m_bRunning != 0 || host == nullptr) return;
    m_pHost = host;
    m_unk155 = 0;
    m_unk156 = 0;
    m_unk157 = 0;
    m_unk174 = 0;
    m_bRunning = 1;
    m_unk04 = host->GetAbilityLevelIndex(this);  // vt+0xf4
    ApplyHeroControl(1);                          // vt+0x68
    m_unk15e = m_pHost->CanUseAltLoopAnim();      // vt+0x38
    m_unk168 = 0;
    m_unk16c = 0.0f;
    m_unk158 = 0.0f;
    m_unk164 = 0.0f;
    if (m_pHost->PlayAbilityAnim(this, 0) != 0) {  // vt+0x7c
        m_unk156 = 1;
    } else {
        if (m_unk15e == 0 || m_pHost->PlayAbilityAnim(this, 2) == 0) m_pHost->PlayAbilityAnim(this, 1);
        m_unk155 = 1;
        if (m_pHost->GetAbilityMana() != 0) SetFxActive(1);  // vt+0xbc, vt+0x70
    }
    m_fStartTime = GameClockNow();
}

// 0x00381190 CKBreathElement_Stop
void CKBreathElement::Stop(int32_t forced) {
    if (m_bRunning == 0) return;
    StopBreathing();  // vt+0x7c
    End(forced);      // vt+0x64
}

// 0x00381220 CKBreathElement_End
void CKBreathElement::End(int32_t forced) {
    UpdateDamageSpheres(0.0f, 1);  // vt+0x80 (TOC +0x3308)
    ApplyHeroControl(0);           // vt+0x68
    m_bRunning = 0;
    const float cooldown = forced != 0 ? m_unk2c[m_unk04] : m_unk20[m_unk04];
    m_pHost->SetAbilityCooldown(cooldown, this, static_cast<uint8_t>(forced ^ 1));  // vt+0x9c
    m_pHost = nullptr;
}

// 0x00381330 CKBreathElement_ApplyHeroControl. The 11f8 gates (vt+0x68): a context's own byte when its permission 0
// byte (+0xdb / +0xe9 / +0x109) is clear.
void CKBreathElement::ApplyHeroControl(uint8_t on) {
    CKS08AbilityHostBase* host = m_pHost;
    if (on != 0) {
        host->SetHeroActionPermission(0, m_unkDb, m_unkE9, m_unk109);  // vt+0x44
        host->SetHeroActionPermission(1, m_unkDa, m_unkE8, m_unk108);
        host->SetHeroActionPermission(3, 0, 1, 1);
        host->SetHeroActionPermission(4, 1, 1, 1);
        host->SetHeroActionPermission(5, 0, 0, 0);
        host->SetHeroActionPermission(8, 1, 1, 1);
        host->SetAbilityTurnParams(m_unkE0, m_unkE4, m_unkEc, m_unkF0, m_unk10c, m_unk110, m_unkDc, m_unkEa,
                                   m_unk10a);  // vt+0x64
        const uint8_t gateAir = m_unkDb == 0 ? static_cast<uint8_t>(m_unkFc != 0) : 0;
        const uint8_t gateFly = m_unkE9 == 0 ? static_cast<uint8_t>(m_unkFd != 0) : 0;
        const uint8_t gateGround = m_unk109 == 0 ? static_cast<uint8_t>(m_unk118 != 0) : 0;
        host->SetAbilityParam11f8(m_unk100, m_unk104, m_unk11c, gateAir, gateFly, gateGround);  // vt+0x68
        host->SetAbilityMoveSpeed(m_unkF4, m_unkF8, m_unk114);                                 // vt+0x50
        host->SetAbilityMoveSpeedEnabled(1);                                                   // vt+0x54
        const uint8_t grounded = static_cast<uint8_t>(host->IsAirborne() ^ 1);                 // vt+0x30
        m_unk15f = grounded;
        host->SetAbilityHeroMode(this, grounded);  // vt+0x70
        return;
    }
    host->SetHeroActionPermission(0, 0, 0, 0);
    host->SetHeroActionPermission(1, 0, 0, 0);
    host->SetHeroActionPermission(3, 0, 0, 0);
    host->SetHeroActionPermission(4, 0, 0, 0);
    host->SetHeroActionPermission(5, 0, 0, 0);
    host->SetHeroActionPermission(8, 0, 0, 0);
    host->SetHeroActionPermission(9, 0, 0, 0);
    host->SetAbilityTurnParams(m_unkE0, m_unkE4, m_unkEc, m_unkF0, m_unk10c, m_unk110, 0, 0, 0);
    host->SetAbilityParam11f8(m_unk100, m_unk104, m_unk11c, 0, 0, 0);
    host->SetAbilityMoveSpeedEnabled(0);
    host->SetAbilityHeroMode(this, 0);
}

// 0x00381928 CKBreathElement_StopBreathing
void CKBreathElement::StopBreathing() {
    SetFxActive(0);  // vt+0x70
    m_unk155 = 0;
}

// 0x00381980 CKBreathElement_ApplyDamageParams
void CKBreathElement::ApplyDamageParams(uint8_t continuous) {
    const float damageScale = m_pHost->GetDamageScale();  // vt+0xc0
    const float effectScale = m_pHost->GetEffectScale();  // vt+0xc4
    const uint32_t level = m_unk04;
    CKS08ElementDamage* damage = static_cast<CKS08ElementDamage*>(m_unk170);
    damage->SetAmount(damageScale * static_cast<float>(static_cast<double>(m_unk08[level])));  // vt+0x50
    damage->SetStun(m_unk68[level]);                    // vt+0x5c
    damage->SetStunDuration(m_unk5c[level]);            // vt+0x60
    damage->SetElementValue(effectScale * m_unk74[level], 0);  // vt+0x58
    damage->SetElementValue(effectScale * m_unk80[level], 1);
    damage->SetElementValue(effectScale * m_unk8c[level], 2);
    damage->SetElementValue(effectScale * m_unkA4[level], 6);
    damage->SetElementValue(effectScale * m_unk98[level], 4);
    damage->SetElementValue(effectScale * m_unkBc[level], 7);
    damage->SetElementValue(effectScale * m_unkC8[level], 3);
    damage->SetElementValue(effectScale * m_unkB0[level], 5);
    damage->SetUnk34(m_unkD4[level]);  // vt+0x6c
    damage->SetUnk35(m_unkD7[level]);  // vt+0x70
    damage->SetDamageType(kAbilityDamageTypes[GetAbilityId() & 0xffu]);  // vt+0x64 (TOC +0x330c)
    damage->SetAbilityId(GetAbilityId());                                 // vt+0x68
    damage->m_unk10 = m_unk14[level] / 0.2f;  // TOC +0x3310
    damage->m_unk14 = 0.2f;
    damage->SetContinuous(continuous);  // vt+0x54
}

// 0x00381ed8 CKBreathElement_ResetRuntime
void CKBreathElement::ResetRuntime(int32_t type) {
    m_unk15c = 0xff;
    m_unk15d = 1;
    m_pHost = nullptr;
    m_unk04 = 0;
    m_bRunning = 0;
    m_unk155 = 0;
    m_unk156 = 0;
    m_unk157 = 0;
    m_unk15e = 0;
    m_unk158 = 0.0f;
    if (type == 0) {
        m_ui32SegmentCapacity = 1;
        m_pSegments = static_cast<Segment*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(Segment))));  // 0x00053198
    }
    m_unk16c = 0.0f;
    m_unk168 = 0;
    m_unk164 = 0.0f;
    m_fStartTime = -1.0f;  // TOC +0x3320 (0xbf800000)
}

// 0x00382028 CKBreathElement_StartEmitterFx: the inlined pooled lookup (CKSrvFx::AcquireFx) of the explosion data's
// effect, owned by this element.
void CKBreathElement::StartEmitterFx() {
    IKFxData* data = reinterpret_cast<IKFxData*>(m_unk120);
    CKSrvFx* fxService = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
    if (fxService->m_ui32EltNb == 0) return;
    CKExplosionNodeFx* fx = static_cast<CKExplosionNodeFx*>(fxService->AcquireFx(data, this));
    if (fx == nullptr) return;
    const CVector3 position = m_pHost->GetHotspotPosition(m_unk15c);  // vt+0xd0
    fx->SetTranslation(&position, this);  // 0x001b66e8
    fx->Trigger(this, 0);                 // 0x001b82a8
    fx->ReleaseReservation(this);         // vt+0x54
}

// 0x00382398 CKBreathElement_GetEmitterPosition
CVector3 CKBreathElement::GetEmitterPosition(uint8_t raw) {
    if (raw != 0) return kAxisX;
    return m_pHost->GetAimDirection(0);  // vt+0x24
}

// 0x00382430 CKBreathElement_Update. The mana: the level's mana per second (scaled, host vt+0xc8) accumulates in +0x158;
// whole points are taken (vt+0xb8, the fraction kept); the dragon's mana (vt+0xbc, unsigned; -1 infinite) not above the
// accumulated fraction is the fizzle.
uint8_t CKBreathElement::Update(float dt) {
    if (m_bRunning == 0) return 0;
    if (m_fStartTime == GameClockNow()) return 1;
    if (m_unk157 != 0) {
        UpdateDamageSpheres(dt, 0);  // vt+0x80
        if (m_pHost->IsAbilityAnimPhaseDone(this, 4) == 0) return 1;  // vt+0x80
        End(m_unk174);
        return 0;
    }
    float held = 0.0f;
    if (m_pHost->IsAbilityButtonDown(m_unk15d) == 0 && m_pHost->GetAbilityButtonHoldTime(m_unk15d, &held) == 0) {  // vt+0x8c / +0x94
        StopBreathing();  // vt+0x7c
        if (m_unk156 == 0 && m_pHost->PlayAbilityAnim(this, 4) != 0) {
            m_unk157 = 1;
            return 1;
        }
        End(0);
        return 0;
    }
    if (m_unk156 != 0) {
        // The start animation.
        if (m_pHost->IsAbilityAnimPhaseDone(this, 0) == 0) return 1;
        m_unk15e = m_pHost->CanUseAltLoopAnim();  // vt+0x38
        if (m_unk15e == 0 || m_pHost->PlayAbilityAnim(this, 2) == 0) m_pHost->PlayAbilityAnim(this, 1);
        m_unk156 = 0;
        m_unk155 = 1;
        if (m_pHost->GetAbilityMana() != 0) SetFxActive(1);  // vt+0xbc, vt+0x70
        return 1;
    }
    if (m_unk155 == 0) return 0;

    m_unk16c = m_unk16c + dt;
    const float spent = m_unk158;
    const float scale = m_pHost->GetManaCostScale();  // vt+0xc8
    const float perSecond = scale * static_cast<float>(static_cast<double>(m_unk38[m_unk04]));
    m_unk158 = ppc::fmadds(dt, perSecond, spent);
    if (m_unk158 >= 1.0f) {  // TOC +0x3348 (cror gt|eq)
        const uint32_t whole = static_cast<uint32_t>(ppc::fctidz(m_unk158));
        m_pHost->ConsumeAbilityMana(this, whole);  // vt+0xb8
        const uint32_t taken = static_cast<uint32_t>(ppc::fctidz(m_unk158));
        m_unk158 = m_unk158 - static_cast<float>(static_cast<double>(taken));
    }
    const uint32_t mana = static_cast<uint32_t>(m_pHost->GetAbilityMana());  // vt+0xbc
    if (!(static_cast<float>(static_cast<double>(mana)) > m_unk158)) {
        // Out of mana: the fizzle and the end animation.
        StopBreathing();   // vt+0x7c
        StartEmitterFx();  // vt+0x74
        m_unk174 = 1;
        if (m_pHost->PlayAbilityAnim(this, 4) != 0) {
            m_unk157 = 1;
            return 1;
        }
        End(m_unk174);
        return 0;
    }
    UpdateDamageSpheres(dt, 0);  // vt+0x80
    UpdateFx(dt);                // vt+0x78
    // The hero control follows the grounded state.
    const bool wasGrounded = m_unk15f != 0;
    const uint8_t airborne = m_pHost->IsAirborne();  // vt+0x30
    if (wasGrounded == (airborne != 0)) {
        m_unk15f = wasGrounded ? 0 : 1;
        m_unk15e = m_pHost->CanUseAltLoopAnim();
        ApplyHeroControl(1);
        if (m_unk15e == 0 || m_pHost->PlayAbilityAnim(this, 2) == 0) m_pHost->PlayAbilityAnim(this, 1);
    }
    // The loop's animation follows the alternative loop's test.
    if (m_unk15e != 0) {
        if (m_pHost->CanUseAltLoopAnim() == 0) {
            m_pHost->PlayAbilityAnim(this, 1);
            m_unk15e = 0;
        } else if (m_unk15e != 0) {
            return 1;
        }
    }
    if (m_pHost->CanUseAltLoopAnim() != 0 && m_pHost->PlayAbilityAnim(this, 2) != 0) m_unk15e = 1;
    return 1;
}

// 0x00382e68 CKBreathElement_UpdateDamageSpheres. All float tests are the original's (cror: ordered).
void CKBreathElement::UpdateDamageSpheres(float dt, uint8_t releaseAll) {
    CKSrvCollision* collision = Collision();
    if (releaseAll != 0) {
        // Every sphere freed: the first one each time, the last moved into its place.
        const uint32_t count = m_ui32SegmentCount;
        for (uint32_t n = 0; n != count; ++n) {
            CKDynamicBoundingSphere* sphere = m_pSegments[0].m_pSphere;
            if (sphere->m_pParent != nullptr) sphere->m_pParent->RemoveChild(sphere);  // vt+0x78
            collision->ReleaseDynSphere(sphere);  // 0x00191a38
            const uint32_t left = m_ui32SegmentCount - 1;
            m_ui32SegmentCount = left;
            if (left != 0) m_pSegments[0] = m_pSegments[left];
        }
        return;
    }

    m_unk164 = m_unk164 - dt;
    CGroundContactDatasIn in;  // the masks 1 / 8 once
    CGroundContactDatasInOut contact;
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    uint32_t count = m_ui32SegmentCount;
    uint32_t i = 0;
    while (i < count) {
        Segment* segment = &m_pSegments[i];
        if (m_unk130 <= segment->m_fTime) {
            // Its life is over: the sphere freed and the later ones moved down.
            CKDynamicBoundingSphere* sphere = segment->m_pSphere;
            if (sphere->m_pParent != nullptr) sphere->m_pParent->RemoveChild(sphere);  // vt+0x78
            --count;
            collision->ReleaseDynSphere(sphere);
            const uint32_t after = (m_ui32SegmentCount - 1) - i;
            m_ui32SegmentCount = m_ui32SegmentCount - 1;
            std::memmove(&m_pSegments[i], &m_pSegments[i + 1], after * sizeof(Segment));  // TocBridge_memmove
            continue;
        }
        float time = dt + segment->m_fTime;
        segment->m_fTime = time;
        float step = dt;
        if (time >= m_unk130) {
            const float before = time - dt;
            segment->m_fTime = m_unk130;
            step = m_unk130 - before;
        }
        const uint32_t level = m_unk04;
        const float speed = segment->m_fSpeed;
        step = step * speed;
        const float distance = speed * segment->m_fTime;
        RwFrame* frame = segment->m_pSphere->m_pRwFrame;
        const float z = ppc::fmadds(step, segment->m_v3Direction.z, frame->modelling.pos.z);
        const float x = ppc::fmadds(step, segment->m_v3Direction.x, frame->modelling.pos.x);
        const float y = ppc::fmadds(step, segment->m_v3Direction.y, frame->modelling.pos.y);
        const float tangent = crt::Tanf(m_unk44[level] * kDegToRad * 0.5f);  // TOC +0x3380
        const float radius = ppc::fmadds(distance, std::fabs(tangent), m_unk50[level]);
        frame->modelling.pos.z = z;
        frame->modelling.pos.x = x;
        frame->modelling.pos.y = y;
        frame->modelling.flags &= 0xfffdffffu;
        RwFrame_MarkDirty(frame);  // 0x00010698
        segment->m_pSphere->m_fRadius = radius > 0.0f ? radius : kMinRadius;
        ++i;
        if (m_unk14c == 0) continue;
        // The ground scorch of the fire / ice elements, at most once per sphere index until the timer runs out.
        const uint32_t element = kAbilityGroundElements[GetAbilityId() & 0xffu];  // vt+0x50
        if (element > 1) continue;
        if (!(m_unk164 <= 0.0f)) continue;
        in.m_fDeltaMax = 0.0f;
        in.m_fObjectHeight = radius + radius;
        contact.m_eContactStatus = 3;
        contact.m_i32FaceIndex = -1;
        contact.m_pGround = nullptr;
        contact.m_ui8SectorNumber = 0;
        const float point[3] = {x, y - radius, z};
        collision->GroundProbePoints(&in, &contact, point, 1);  // 0x00196540
        if (contact.m_pGround == nullptr || contact.m_eContactStatus != 2) continue;
        const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(contact.m_pGround);
        if (((ground->m_ui16PropertiesFlags >> 9) & 1u) != 0 || ((ground->m_ba16EngineFlags >> 1) & 1u) != 0) continue;
        if (m_unk168 > i - 1) continue;
        m_unk168 = i;
        const float period = m_unk13c + m_unk140;
        m_unk164 = ppc::fmadds(RandUnit16() / kRandMax * -2.0f, m_unk140, period);  // 0x00011500; TOC +0x338c
        CVector3 world;
        GroundContact_GetWorldPoint(&contact, &world);  // 0x001a70e0
        float cosine = std::fabs(world.y - y) / radius;
        if (cosine <= 0.0f) {
            cosine = 0.0f;
        } else if (cosine >= 1.0f) {
            cosine = 1.0f;
        }
        const float sine = GameSinf(crt::Acosf(cosine));  // TocBridge_Math_Acosf; the inlined sinf
        // A random horizontal direction.
        float dx = ppc::fmadds(RandUnit16(), kRandScale, 1.0f);
        float dz = ppc::fmadds(RandUnit16(), kRandScale, 1.0f);
        const float length = Sqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, 0.0f)));  // 0x00010690
        float dy = 0.0f;
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            dz = dz * inverse;
            dx = dx * inverse;
            dy = inverse * 0.0f;
        }
        const float scatter = sine * radius * (RandUnit16() / kRandMax);
        const float height = m_unk144 + m_unk148;
        CVector3 at;
        // BUG(original): the scattered point is overwritten by the next one (both from the world point); the draws stay.
        at.z = ppc::fmadds(dz, scatter, world.z);
        at.x = ppc::fmadds(dx, scatter, world.x);
        at.y = ppc::fmadds(dy, scatter, world.y);
        const float lift = ppc::fmadds(RandUnit16() / kRandMax * -2.0f, m_unk148, height);
        at.z = ppc::fmadds(lift, kAxisY.z, world.z);
        at.x = ppc::fmadds(lift, kAxisY.x, world.x);
        at.y = ppc::fmadds(lift, kAxisY.y, world.y);
        manager->SpawnElementGroundFx(this, element, &at);  // 0x004fb848
    }

    if (m_unk164 <= 0.0f) m_unk168 = 0;
    if (m_unk155 == 0) return;
    if (m_ui32SegmentCount == 0) {
        if (!(m_unk130 > 0.0f)) return;
    } else if (!(m_pSegments[0].m_fTime * m_pSegments[0].m_fSpeed > m_unk134)) {
        return;
    }
    // A new sphere leaves the hot spot 2.
    CKDynamicBoundingSphere* sphere = static_cast<CKDynamicBoundingSphere*>(collision->AcquireDynSphere());  // 0x00192a70
    if (sphere == nullptr) return;
    if (sphere->m_pParent != nullptr) sphere->m_pParent->RemoveChild(sphere);  // vt+0x78
    static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot)->AddChild(sphere);  // vt+0x70
    const CVector3 start = m_pHost->GetHotspotPosition(2);  // vt+0xd0
    RwFrame* frame = sphere->m_pRwFrame;
    frame->modelling.pos.z = start.z;
    frame->modelling.pos.x = start.x;
    frame->modelling.pos.y = start.y;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);
    const float radius = m_unk50[m_unk04] + kMinRadius;
    sphere->m_fRadius = radius > 0.0f ? radius : kMinRadius;
    sphere->m_ba8Infos = static_cast<uint8_t>(sphere->m_ba8Infos | 0x08);  // three bit inserts in turn
    sphere->m_ba8Infos = static_cast<uint8_t>(sphere->m_ba8Infos | 0x20);
    sphere->m_ba8Infos = static_cast<uint8_t>(sphere->m_ba8Infos | 0x04);
    const CVector3 heroPosition = m_pHost->GetOwnerPosition();  // vt+0x10
    sphere->m_v3WorldMove = kNullVector;  // 0x00c50d64
    sphere->m_v3OldPos = heroPosition;
    sphere->m_v3LastWorldPos = heroPosition;
    sphere->m_pOwner = m_pHost->GetOwner();  // vt+0x08
    sphere->m_ui8OwnerType = 0;
    sphere->m_ui16PropertiesFlags = 0;
    sphere->m_ui8OwnerType = m_pHost->GetCollisionGroup();  // vt+0xb0
    sphere->m_ui16PropertiesFlags = static_cast<uint16_t>(m_pHost->GetCollisionMask() | sphere->m_ui16PropertiesFlags);  // vt+0xb4
    ApplyDamageParams(1);  // vt+0x88
    sphere->m_unk1c = m_unk170;
    sphere->m_ba8Infos = static_cast<uint8_t>((sphere->m_ba8Infos & 0x7f) | 0x80);
    const float speed = m_pHost->GetHeroSpeedForAbility() + m_unk138;  // vt+0x48
    const CVector3 direction = GetEmitterPosition(0);                  // vt+0x84
    // The new sphere goes first (the K array grows by one).
    uint32_t used = m_ui32SegmentCount;
    if (used == 0) {
        if (m_ui32SegmentCapacity == 0) {
            m_pSegments = static_cast<Segment*>(Mem_ReallocAligned16(m_pSegments, static_cast<uint32_t>(sizeof(Segment))));  // 0x00053190
            used = m_ui32SegmentCount;
            m_ui32SegmentCapacity = 1;
        }
        Segment& slot = m_pSegments[used];
        slot.m_pSphere = sphere;
        slot.m_v3Direction = direction;
        slot.m_fSpeed = speed;
        slot.m_fTime = 0.0f;
        m_ui32SegmentCount = m_ui32SegmentCount + 1;
        return;
    }
    if (m_ui32SegmentCapacity == used) {
        uint32_t capacity = used + 1;
        uint32_t bytes = capacity * static_cast<uint32_t>(sizeof(Segment));
        if (capacity == 0) {
            capacity = 1;
            bytes = static_cast<uint32_t>(sizeof(Segment));
        }
        m_pSegments = static_cast<Segment*>(Mem_ReallocAligned16(m_pSegments, bytes & ~7u));
        used = m_ui32SegmentCount;
        m_ui32SegmentCapacity = capacity;
    }
    std::memmove(&m_pSegments[1], &m_pSegments[0], (used * sizeof(Segment)) & ~static_cast<size_t>(7));  // TocBridge_memmove
    Segment& slot = m_pSegments[0];
    slot.m_pSphere = sphere;
    slot.m_v3Direction = direction;
    slot.m_fSpeed = speed;
    slot.m_fTime = 0.0f;
    m_ui32SegmentCount = m_ui32SegmentCount + 1;
}
