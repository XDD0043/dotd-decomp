// CKTransformElement.cpp - reconstructed original translation unit 0x3dc3d8-0x3e0248 (GAME_TOC1, main_toc1), 32 functions, 30 live.
// Primary class: CKTransformElement  key 0x954c  category Logic  size 0x154  vtable 0xb24888
// Other owners: CKWindBeam (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3dc3d8  CKTransformElement_Delete
//   [x] 0x3dc428  CKTransformElement_Construct
//   [ ] 0x3dc438  CKTransformElement_Construct_2  [dead]
//   [x] 0x3dc448  CKTransformElement_GetAbilityId
//   [x] 0x3dc450  CKTransformElement_GetFamilyId
//   [x] 0x3dc458  CKTransformElement_Start
//   [x] 0x3dc690  CKTransformElement_Stop
//   [x] 0x3dc720  CKTransformElement_End
//   [x] 0x3dc800  CKTransformElement_ApplyHeroControl
//   [x] 0x3dcea0  CKTransformElement_ResetRuntime
//   [x] 0x3dcee8  CKTransformElement_StopFx
//   [x] 0x3dcf40  CKTransformElement_SwitchLoopAnim_maybe
//   [x] 0x3dcfc8  CKTransformElement_DeleteArray
//   [x] 0x3dd068  CKTransformElement_StartEmitterFx
//   [ ] 0x3dd330  RegisterCKTransformElementClass
//   [ ] 0x3dd3b8  _GLOBAL__D_3dd3b8
//   [ ] 0x3dd3c8  _GLOBAL__I_3dd3c8
//   [x] 0x3dd3d8  CKTransformElement_ApplyDamageParams
//   [x] 0x3dd958  CKTransformElement_Update
//   [x] 0x3de3b8  CKTransformElement_CreateArray
//   [x] 0x3de448  CKTransformElement_Create
//   [x] 0x3de480  CKTransformElement_RecursiveRegistration  (returns 1: the default slot)
//   [x] 0x3de488  CKTransformElement_PostLoad
//   [x] 0x3de4d0  CKTransformElement_Destroy  (empty)
//   [x] 0x3de4d8  CKTransformElement_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x3de4f8  CKTransformElement_Load
//   [x] 0x3df3a0  CKTransformElement_DeletingDestructor  (the destructor; delete)
//   [x] 0x3df3e8  CKTransformElement_Destructor  (C++ destructor chain: vtable stores only)
//   [ ] 0x3df408  CKTransformElement_Save
//   [x] 0x3e01e8  CKWindBeam_Delete
//   [x] 0x3e0238  CKWindBeam_GetAbilityId
//   [ ] 0x3e0240  KStub_Nop_3e0240  [dead]
//
//   [ ] 0x9c08d0  CKTransformElement_GetClassType  [inline]
//   [ ] 0x9c08d8  CKTransformElement_GetClassID  [inline]
//   [x] 0x9c08e0  CKTransformElement_SetFxActive  [inline]
//   [x] 0x9c08e8  CKTransformElement_vf74  [inline]
//   [x] 0x9c08f0  CKTransformElement_UpdateAttack_maybe  [inline]
//   [ ] 0x9c08f8  CKTransformElement_IsKindOfClass  [inline]
#include "k2000/logic/CKTransformElement.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/logic/CKS08ElementDamage.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "Spyro2008/misc/CKS08AbilityHostBase.h"
#include "crt/ppc_ops.h"
#include "k2000/fx/IKFx.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKAnimatedFx.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/logic/fx/CKSparkNodeFx.h"
#include "k2000/logic/render/CKMeshPopNodeFx.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"

namespace {
float GameClockNow() { return g_pEngine->m_timeManager->m_pTime->m_afCurrentTime[0]; }  // TOC +0x41a4 -> +0x48 -> +0x04 -> +0x04
// 0x00a70b28 (TOC +0x41dc): the ability ids' damage types (the same 26 words as CKGrabElement's 0x00a70988).
const uint32_t kAbilityDamageTypes[26] = {0, 0, 1, 1, 2, 2, 3, 3, 8, 8, 4, 4, 5, 5, 5, 6, 9, 7, 7, 9, 6, 0, 0, 0, 0, 0};
// 0x00a70b90 (TOC +0x41dc, +0x68): the ability ids' ground FX types (SpawnElementGroundFx_maybe; only 0 and 1 spawn).
const uint32_t kGroundFxTypes[21] = {0, 0, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
constexpr float kRandMax = 65535.0f;              // TOC +0x41e4 (0x477fff00)
constexpr float kRandScale = -0x1.0001p-15f;      // TOC +0x41f4 (0xb8000080)
constexpr float kDegToRad = 0x1.1df468p-6f;       // TOC +0x41ec (0x3c8efa34)
// One Rand_Int draw, its low 16 bits as a float (clrldi 48, fcfid, frsp).
float RandUnit16() { return static_cast<float>(static_cast<double>(static_cast<uint32_t>(Rand_Int()) & 0xffffu)); }
// 0x00010690 Math_Sqrtf
float Sqrtf(float x) { return static_cast<float>(std::sqrt(static_cast<double>(x))); }
// fctidz, the low word (the mana amounts: clrldi 32 / cmplw).
uint32_t WholeMana(float value) { return static_cast<uint32_t>(static_cast<uint64_t>(ppc::fctidz(value))); }
// The start cost: the cost scale (host vt+0xc8) x the level's cost +0x44 (fcfid, frsp, fmuls, fctidz).
uint32_t StartCost(CKS08AbilityHostBase* host, int32_t cost) {
    return WholeMana(host->GetManaCostScale() * static_cast<float>(static_cast<double>(cost)));
}
// The damage's knock angle (+0x18, radians): base +0x50 + +0x54, spread +0x54 x a Rand_Int draw in [-1, 1]
// (ApplyDamageParams and Update inline it; a local helper, so that the rand log names the inlining function).
void RandomizeKnockAngle(CKTransformElement* element) {
    CKS08ElementDamage* damage = static_cast<CKS08ElementDamage*>(element->m_elementDamage);
    const float base = element->m_dmgRandBase + element->m_dmgRandRange;
    const float t = RandUnit16() / kRandMax * -2.0f;  // 0x00011500; TOC +0x41e4 / +0x41e8
    const float angle = ppc::fmadds(t, element->m_dmgRandRange, base) * kDegToRad;
    std::memcpy(&damage->m_unk18, &angle, sizeof(angle));
}
}  // namespace

namespace TransformFx {
IKFx* Acquire(IKSerializable* data, const IKSerializable* owner) {
    CKSrvFx* fxService = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
    return fxService->AcquireFx(static_cast<IKFxData*>(data), owner);
}

IKFx* Start(IKSerializable* data, const IKSerializable* owner) {
    CKSrvFx* fxService = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
    return fxService->StartEffect(static_cast<IKFxData*>(data), owner);
}

void Explode(IKSerializable* data, const IKSerializable* owner, const CVector3& position) {
    CKExplosionNodeFx* fx = static_cast<CKExplosionNodeFx*>(Acquire(data, owner));
    if (fx == nullptr) return;
    fx->SetTranslation(&position, owner);  // 0x001b66e8
    fx->Trigger(owner, 0);                 // 0x001b82a8
    fx->ReleaseReservation(owner);         // vt+0x54
}

void ReleaseParticles(IKSerializable** slot, const IKSerializable* owner) {
    IKFx* fx = static_cast<IKFx*>(*slot);
    if (fx == nullptr) return;
    StopOwnedParticleEffect(fx, owner);  // 0x001cdde8
    static_cast<IKFx*>(*slot)->ReleaseReservation(owner);
    *slot = nullptr;
}

void ReleaseSpark(IKSerializable** slot, const IKSerializable* owner) {
    if (*slot == nullptr) return;
    StopOwnedSparkEffect(static_cast<CKSparkNodeFx*>(*slot), owner);  // 0x001d4698
    static_cast<IKFx*>(*slot)->ReleaseReservation(owner);
    *slot = nullptr;
}

void ReleaseMeshPop(IKSerializable** slot, const IKSerializable* owner) {
    if (*slot == nullptr) return;
    static_cast<CKMeshPopNodeFx*>(*slot)->SetActive(owner, 0);  // 0x001cb568
    static_cast<IKFx*>(*slot)->ReleaseReservation(owner);
    *slot = nullptr;
}

void SetGeometryAlpha(IKSerializable* object, uint8_t alpha) {
    CGeometry* geometry = static_cast<CGeometry*>(object);
    uint32_t blend = 0;
    uint8_t value = 0xff;
    if (alpha != 0xff) {
        blend = 1;
        value = alpha;
        if ((geometry->m_BitProperties & 0x1000u) != 0) {
            const uint32_t mode = (static_cast<CMaterial*>(geometry->m_pMaterial)->m_baProperties >> 3) & 0xfu;
            if (mode != 0 && mode <= 6) {
                blend = 0;
                value = 0xff;
            }
        }
    }
    geometry->m_cGeometryColor[3] = value;
    const uint32_t bits = geometry->m_BitProperties;
    if (((bits >> 11) & 1u) != blend) {
        geometry->m_BitProperties = (bits & 0xfffff7ffu) | (blend << 11);
        geometry->UpdateProperties();  // vt+0x60
    }
}

void SetGeometriesAlpha(IKSerializable* node, uint8_t alpha) {
    CGeometry* geometry = static_cast<CGeometry*>(static_cast<CNode*>(node)->m_lGeometryList);
    for (; geometry != nullptr; geometry = geometry->m_pNext) SetGeometryAlpha(geometry, alpha);
}

void HideNode(IKSerializable* node) { static_cast<CSGLeaf*>(node)->m_sgProperties |= 4u; }
void ShowNode(IKSerializable* node) { static_cast<CSGLeaf*>(node)->m_sgProperties &= ~4u; }
uint8_t IsNodeHidden(IKSerializable* node) {
    return static_cast<uint8_t>((static_cast<CSGLeaf*>(node)->m_sgProperties & 4u) != 0);
}

void SetNodePosition(IKSerializable* node, const CVector3& position) {
    RwFrame* frame = static_cast<CSGMovable*>(node)->m_pRwFrame;
    frame->modelling.pos.x = position.x;
    frame->modelling.pos.y = position.y;
    frame->modelling.pos.z = position.z;
    frame->modelling.flags &= ~0x20000u;
    RwFrame_MarkDirty(frame);  // 0x00010698
}

CSGLeaf* OwnerNode(CKS08AbilityHostBase* host) {
    return static_cast<CSGLeaf*>(static_cast<IKHook*>(host->GetOwner())->m_pKGLObject);  // vt+0x08, +0x1c
}

SAnimatedFxRig* AttachmentSets(CKS08AbilityHostBase* host) {
    IKSerializable* owner = host->GetOwner();
    if (owner != nullptr && owner->IsKindOfClass(CKHkS08Hero::kClassKey) != 0) {
        return reinterpret_cast<SAnimatedFxRig*>(&static_cast<CKHkS08Hero*>(owner)->m_apUnk1070[0][0]);
    }
    return reinterpret_cast<SAnimatedFxRig*>(host->GetAttachmentSets());
}

float GameClock() { return GameClockNow(); }
float FrameDelta() { return g_pEngine->m_timeManager->m_pTime->m_afDeltaTime[0]; }  // +0x48 -> +0x04 -> +0x1c
}  // namespace TransformFx

// 0x003de488 CKTransformElement_PostLoad: vt+0x6c (ResetRuntime) for every type.
int32_t CKTransformElement::PostLoad(int32_t /*type*/) {
    ResetRuntime();
    return 1;
}

// 0x003dcea0 CKTransformElement_ResetRuntime. Not written: +0x134 (m_bInAir), +0x150 (m_bForcedEnd).
void CKTransformElement::ResetRuntime() {
    m_fStartTime = -1.0f;  // TOC +0x41ac (0xbf800000)
    m_fGroundFxTimer = 0.0f;
    m_bStartCostPending = 1;
    m_ui8HotSpot = 0xff;
    m_ui8Button = 0;
    m_pHost = nullptr;
    m_levelIndex = 0;
    m_bRunning = 0;
    m_bLoop = 0;
    m_bStartAnim = 0;
    m_bEndAnim = 0;
    m_fMana = 0.0f;
}

// 0x003dc458 CKTransformElement_Start
void CKTransformElement::Start(CKS08AbilityHostBase* host) {
    if (m_bRunning != 0 || host == nullptr) return;
    m_bForcedEnd = 0;
    m_pHost = host;
    m_bLoop = 0;
    m_bStartAnim = 0;
    m_bEndAnim = 0;
    m_bStartCostPending = 1;
    m_bRunning = 1;
    m_levelIndex = host->GetAbilityLevelIndex(this);  // vt+0xf4
    ApplyHeroControl(1);                              // vt+0x68
    m_fGroundFxTimer = 0.0f;
    m_fMana = 0.0f;
    if (m_pHost->PlayAbilityAnim(this, 0) != 0) {  // vt+0x7c
        m_bStartAnim = 1;
    } else if (m_pHost->PlayAbilityAnim(this, 1) != 0) {
        m_bLoop = 1;
        const uint32_t mana = static_cast<uint32_t>(m_pHost->GetAbilityMana());  // vt+0xbc
        if (StartCost(m_pHost, m_manaRequired[m_levelIndex]) < mana) SetFxActive(1);  // cmplw / bge; vt+0x70
    }
    m_fStartTime = GameClockNow();
}

// 0x003dc690 CKTransformElement_Stop
void CKTransformElement::Stop(int32_t forced) {
    if (m_bRunning == 0) return;
    StopFx();     // vt+0x84
    End(forced);  // vt+0x64
}

// 0x003dc720 CKTransformElement_End
void CKTransformElement::End(int32_t forced) {
    ApplyHeroControl(0);  // vt+0x68
    m_bRunning = 0;
    const float cooldown = forced != 0 ? m_cooldownForced[m_levelIndex] : m_cooldown[m_levelIndex];
    m_pHost->SetAbilityCooldown(cooldown, this, static_cast<uint8_t>((forced ^ 1) & 0xff));  // vt+0x9c
    m_pHost = nullptr;
}

// 0x003dc800 CKTransformElement_ApplyHeroControl. The gates of +0x68 (SetAbilityParam11f8): a context's own byte when
// its permission 0 byte (+0xe5 / +0xf1 / +0x111) is clear. The host's vt+0x70 also gets f1 = 0.0f (TOC +0x41a8),
// which neither host reads.
void CKTransformElement::ApplyHeroControl(uint8_t on) {
    CKS08AbilityHostBase* host = m_pHost;
    if (on != 0) {
        host->SetHeroActionPermission(0, m_airPerm1Perm0TurnEnable[1], m_mode1Perm1Perm0TurnEnable[1],
                                      m_groundPerm1Perm0TurnEnable[1]);  // vt+0x44
        m_pHost->SetHeroActionPermission(1, m_airPerm1Perm0TurnEnable[0], m_mode1Perm1Perm0TurnEnable[0],
                                         m_groundPerm1Perm0TurnEnable[0]);
        m_pHost->SetHeroActionPermission(3, 0, 1, 1);
        m_pHost->SetHeroActionPermission(4, 1, 1, 1);
        m_pHost->SetHeroActionPermission(5, 0, 0, 0);
        m_pHost->SetHeroActionPermission(6, 1, 1, 1);
        m_pHost->SetHeroActionPermission(8, 1, 1, 1);
        m_pHost->SetAbilityTurnParams(m_airTurnAB[0], m_airTurnAB[1], m_mode1TurnAB[0], m_mode1TurnAB[1],
                                      m_groundTurnAB[0], m_groundTurnAB[1], m_airPerm1Perm0TurnEnable[2],
                                      m_mode1Perm1Perm0TurnEnable[2], m_groundPerm1Perm0TurnEnable[2]);  // vt+0x64
        const uint8_t gateAir = m_airPerm1Perm0TurnEnable[1] == 0 ? static_cast<uint8_t>(m_airMode1P11f8Enable[0] != 0) : 0;
        const uint8_t gateFly =
            m_mode1Perm1Perm0TurnEnable[1] == 0 ? static_cast<uint8_t>(m_airMode1P11f8Enable[1] != 0) : 0;
        const uint8_t gateGround =
            m_groundPerm1Perm0TurnEnable[1] == 0 ? static_cast<uint8_t>(m_groundP11f8Enable != 0) : 0;
        m_pHost->SetAbilityParam11f8(m_airMode1P11f8[0], m_airMode1P11f8[1], m_groundP11f8, gateAir, gateFly,
                                     gateGround);                                        // vt+0x68
        m_pHost->SetAbilityMoveSpeed(m_airMoveSpeed, m_mode1MoveSpeed, m_groundMoveSpeed);  // vt+0x50
        m_pHost->SetAbilityMoveSpeedEnabled(1);                                            // vt+0x54
        const uint8_t inAir = static_cast<uint8_t>(m_pHost->IsAirborne() ^ 1);            // vt+0x30
        m_bInAir = inAir;
        m_pHost->SetAbilityHeroMode(this, inAir);  // vt+0x70
        return;
    }
    host->SetHeroActionPermission(0, 0, 0, 0);
    m_pHost->SetHeroActionPermission(1, 0, 0, 0);
    m_pHost->SetHeroActionPermission(2, 0, 0, 0);
    m_pHost->SetHeroActionPermission(3, 0, 0, 0);
    m_pHost->SetHeroActionPermission(4, 0, 0, 0);
    m_pHost->SetHeroActionPermission(5, 0, 0, 0);
    m_pHost->SetHeroActionPermission(6, 0, 0, 0);
    m_pHost->SetHeroActionPermission(8, 0, 0, 0);
    m_pHost->SetHeroActionPermission(9, 0, 0, 0);
    m_pHost->SetAbilityTurnParams(m_airTurnAB[0], m_airTurnAB[1], m_mode1TurnAB[0], m_mode1TurnAB[1], m_groundTurnAB[0],
                                  m_groundTurnAB[1], 0, 0, 0);
    m_pHost->SetAbilityParam11f8(m_airMode1P11f8[0], m_airMode1P11f8[1], m_groundP11f8, 0, 0, 0);
    m_pHost->SetAbilityMoveSpeedEnabled(0);
    m_pHost->SetAbilityHeroMode(this, 0);
}

// 0x003dcee8 CKTransformElement_StopFx
void CKTransformElement::StopFx() {
    SetFxActive(0);  // vt+0x70
    m_bLoop = 0;
}

// 0x003dcf40 CKTransformElement_SwitchLoopAnim_maybe
void CKTransformElement::SwitchLoopAnim(uint8_t onGround) {
    m_bInAir = static_cast<uint8_t>(onGround ^ 1);
    ApplyHeroControl(1);                // vt+0x68
    m_pHost->PlayAbilityAnim(this, 1);  // vt+0x7c
}

// 0x003dd068 CKTransformElement_StartEmitterFx: the inlined pooled lookup (CKSrvFx::AcquireFx) of the emitter data's
// effect, owned by this element.
void CKTransformElement::StartEmitterFx() {
    IKFxData* data = reinterpret_cast<IKFxData*>(m_emitterFxData);
    CKSrvFx* fxService = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
    if (fxService->m_ui32EltNb == 0) return;
    CKExplosionNodeFx* fx = static_cast<CKExplosionNodeFx*>(fxService->AcquireFx(data, this));
    if (fx == nullptr) return;
    const CVector3 position = m_pHost->GetHotspotPosition(m_ui8HotSpot);  // vt+0xd0
    fx->SetTranslation(&position, this);  // 0x001b66e8
    fx->Trigger(this, 0);                 // 0x001b82a8
    fx->ReleaseReservation(this);         // vt+0x54
}


// 0x003dd3d8 CKTransformElement_ApplyDamageParams
void CKTransformElement::ApplyDamageParams(uint8_t continuous) {
    const float damageScale = m_pHost->GetDamageScale();  // vt+0xc0
    const float effectScale = m_pHost->GetEffectScale();  // vt+0xc4
    const uint32_t level = static_cast<uint32_t>(m_levelIndex);
    CKS08ElementDamage* damage = static_cast<CKS08ElementDamage*>(m_elementDamage);
    damage->SetAmount(damageScale * static_cast<float>(static_cast<double>(m_damage[level])));  // vt+0x50 (fcfid, frsp)
    damage->SetStun(m_dmgParam28[level]);                         // vt+0x5c
    damage->SetStunDuration(m_dmgParam2C[level]);                 // vt+0x60
    damage->SetElementValue(effectScale * m_dmgEffect0[level], 0);  // vt+0x58
    damage->SetElementValue(effectScale * m_dmgEffect1[level], 1);
    damage->SetElementValue(effectScale * m_dmgEffect2[level], 2);
    damage->SetElementValue(effectScale * m_dmgEffect6[level], 6);
    damage->SetElementValue(effectScale * m_dmgEffect4[level], 4);
    damage->SetElementValue(effectScale * m_dmgEffect7[level], 7);
    damage->SetElementValue(effectScale * m_dmgEffect3[level], 3);
    damage->SetElementValue(effectScale * m_dmgEffect5[level], 5);
    damage->SetUnk34(m_dmgFlag34[level]);                                 // vt+0x6c
    damage->SetUnk35(m_dmgFlag35[level]);                                 // vt+0x70
    damage->SetDamageType(kAbilityDamageTypes[GetAbilityId() & 0xffu]);  // vt+0x64
    damage->SetAbilityId(GetAbilityId());                                 // vt+0x68
    damage->m_unk10 = m_damageParam10[level] / 0.2f;                      // TOC +0x41e0
    damage->m_unk14 = 0.2f;
    RandomizeKnockAngle(this);
    damage->SetContinuous(continuous);  // vt+0x54
}

// 0x003dd958 CKTransformElement_Update
uint8_t CKTransformElement::Update(float dt) {
    if (m_bRunning == 0) return 0;
    if (m_fStartTime == GameClockNow()) return 1;
    if (m_bEndAnim != 0) {
        // The end animation.
        UpdateEffect(dt);  // vt+0x74
        RandomizeKnockAngle(this);
        if (m_pHost->IsAbilityAnimPhaseDone(this, 4) == 0) return 1;  // vt+0x80
        End(m_bForcedEnd);
        return 0;
    }
    float held;
    if (m_pHost->IsAbilityButtonDown(m_ui8Button) == 0 &&
        m_pHost->GetAbilityButtonHoldTime(m_ui8Button, &held) == 0) {  // vt+0x8c / +0x94
        // Let go: the end animation, else the end.
        StopFx();  // vt+0x84
        if (m_bStartAnim == 0 && m_pHost->PlayAbilityAnim(this, 4) != 0) {
            m_bEndAnim = 1;
            return 1;
        }
        End(0);
        return 0;
    }
    if (m_bStartAnim != 0) {
        // The start animation, then the loop.
        if (m_pHost->IsAbilityAnimPhaseDone(this, 0) == 0) return 1;
        m_pHost->PlayAbilityAnim(this, 1);
        m_bStartAnim = 0;
        m_bLoop = 1;
        const uint32_t mana = static_cast<uint32_t>(m_pHost->GetAbilityMana());  // vt+0xbc
        if (StartCost(m_pHost, m_manaRequired[m_levelIndex]) >= mana) return 1;
        SetFxActive(1);  // vt+0x70
        return 1;
    }
    if (m_bLoop == 0) return 0;

    // The start cost, at the loop's first frame: not enough mana ends the ability (forced) at once.
    if (m_bStartCostPending != 0) {
        const uint32_t cost = StartCost(m_pHost, m_manaRequired[m_levelIndex]);
        const uint32_t mana = static_cast<uint32_t>(m_pHost->GetAbilityMana());  // vt+0xbc
        if (cost > mana) {
            StartEmitterFx();  // vt+0x78
            m_bForcedEnd = 1;
            End(1);
            return 0;
        }
        m_pHost->ConsumeAbilityMana(this, cost);  // vt+0xb8
        m_bStartCostPending = 0;
    }
    // The mana per second: the cost scale x the level's +0x38 x dt accumulates (fmadds) in +0x138; whole points go to
    // the host (at 1 or more: cror gt|eq, a NaN does not spend). Out of mana (the host's mana as an unsigned float
    // not above the accumulator; -1 is infinite): the end animation, forced.
    {
        const float before = m_fMana;
        const float rate =
            m_pHost->GetManaCostScale() * static_cast<float>(static_cast<double>(m_manaPerSecond[m_levelIndex]));
        m_fMana = ppc::fmadds(rate, dt, before);
        if (m_fMana >= 1.0f) {  // TOC +0x41f0
            m_pHost->ConsumeAbilityMana(this, WholeMana(m_fMana));  // vt+0xb8
            const float mana = m_fMana;
            m_fMana = mana - static_cast<float>(static_cast<double>(WholeMana(mana)));
        }
        const uint32_t left = static_cast<uint32_t>(m_pHost->GetAbilityMana());  // vt+0xbc (clrldi: unsigned)
        if (!(static_cast<float>(static_cast<double>(left)) > m_fMana)) {           // ble
            StopFx();          // vt+0x84
            StartEmitterFx();  // vt+0x78
            m_bForcedEnd = 1;
            if (m_pHost->PlayAbilityAnim(this, 4) != 0) {
                m_bEndAnim = 1;
                return 1;
            }
            End(m_bForcedEnd);
            return 0;
        }
    }
    // The loop animation follows the user's ground state (vt+0x30): landed, or left the ground.
    if (m_bInAir != 0) {
        if (m_pHost->IsAirborne() != 0) SwitchLoopAnim(1);  // vt+0x80
    } else if (m_pHost->IsAirborne() == 0) {
        SwitchLoopAnim(0);
    }
    if (IsGroundTrailActive() != 0) {  // vt+0x8c
        // The ground trail (the ice spin's): an element ground FX near the hot spot 0 every +0xd8 (+- +0xdc) seconds.
        m_fGroundFxTimer = m_fGroundFxTimer - dt;
        const uint32_t type = kGroundFxTypes[GetAbilityId() & 0xffu];  // TOC +0x41dc -> +0x68
        if (type <= 1 && m_fGroundFxTimer <= 0.0f) {
            const float period = m_groundFxIntervalBase + m_groundFxIntervalRange;
            m_fGroundFxTimer = ppc::fmadds(RandUnit16() / kRandMax * -2.0f, m_groundFxIntervalRange, period);
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
            const float scatter = RandUnit16() / kRandMax * m_unkE0;
            CVector3 at;
            at.z = ppc::fmadds(dz, scatter, spot.z);
            at.x = ppc::fmadds(dx, scatter, spot.x);
            at.y = ppc::fmadds(dy, scatter, spot.y);
            CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
            manager->SpawnElementGroundFx(this, type, &at);  // 0x004fb848
        }
    }
    UpdateAttack(dt);  // vt+0x7c
    UpdateEffect(dt);  // vt+0x74
    RandomizeKnockAngle(this);
    return 1;
}

// 0x003de4f8 CKTransformElement_Load: level data only (type K_LEVEL_PLATEFORMS). Three per-level records
// (twelve words and two flag bytes each), then the movement/turn settings, the damage and emitter references.
// 286 bytes.
int32_t CKTransformElement::Load(IKFile* file, int32_t type) {
    if (type == 0) {
        for (int32_t i = 0; i < 3; ++i) {
            ReadS32LE(file, &m_damage[i]);
            ReadF32LE(file, &m_cooldown[i]);
            ReadS32LE(file, &m_manaPerSecond[i]);
            ReadF32LE(file, &m_dmgParam2C[i]);
            ReadF32LE(file, &m_dmgParam28[i]);
            ReadF32LE(file, &m_dmgEffect0[i]);
            ReadF32LE(file, &m_dmgEffect1[i]);
            ReadF32LE(file, &m_dmgEffect2[i]);
            ReadF32LE(file, &m_dmgEffect4[i]);
            ReadF32LE(file, &m_dmgEffect6[i]);
            ReadF32LE(file, &m_dmgEffect5[i]);
            ReadF32LE(file, &m_dmgEffect7[i]);
            ReadU8(file, &m_dmgFlag34[i]);
            ReadU8(file, &m_dmgFlag35[i]);
        }
        ReadU8(file, &m_airPerm1Perm0TurnEnable[0]);
        ReadU8(file, &m_airPerm1Perm0TurnEnable[1]);
        ReadU8(file, &m_airPerm1Perm0TurnEnable[2]);
        ReadF32LE(file, &m_airTurnAB[0]);
        ReadF32LE(file, &m_airTurnAB[1]);
        ReadF32LE(file, &m_airMoveSpeed);
        ReadU8(file, &m_mode1Perm1Perm0TurnEnable[0]);
        ReadU8(file, &m_mode1Perm1Perm0TurnEnable[1]);
        ReadU8(file, &m_mode1Perm1Perm0TurnEnable[2]);
        ReadF32LE(file, &m_mode1TurnAB[0]);
        ReadF32LE(file, &m_mode1TurnAB[1]);
        ReadF32LE(file, &m_mode1MoveSpeed);
        ReadU8(file, &m_airMode1P11f8Enable[0]);
        ReadU8(file, &m_airMode1P11f8Enable[1]);
        ReadF32LE(file, &m_airMode1P11f8[0]);
        ReadF32LE(file, &m_airMode1P11f8[1]);
        ReadF32LE(file, &m_dmgEffect3[0]);
        ReadF32LE(file, &m_dmgEffect3[1]);
        ReadF32LE(file, &m_dmgEffect3[2]);
        IKFile_ReadRef(file, &m_elementDamage);
        ReadU8(file, &m_groundPerm1Perm0TurnEnable[0]);
        ReadU8(file, &m_groundPerm1Perm0TurnEnable[1]);
        ReadU8(file, &m_groundPerm1Perm0TurnEnable[2]);
        ReadF32LE(file, &m_groundTurnAB[0]);
        ReadF32LE(file, &m_groundTurnAB[1]);
        ReadF32LE(file, &m_groundMoveSpeed);
        ReadU8(file, &m_groundP11f8Enable);
        ReadF32LE(file, &m_groundP11f8);
        ReadF32LE(file, &m_groundFxIntervalBase);
        ReadF32LE(file, &m_groundFxIntervalRange);
        ReadF32LE(file, &m_unkE0);
        ReadF32LE(file, &m_cooldownForced[0]);
        ReadF32LE(file, &m_cooldownForced[1]);
        ReadF32LE(file, &m_cooldownForced[2]);
        IKFile_ReadRef(file, &m_emitterFxData);
        ReadF32LE(file, &m_damageParam10[0]);
        ReadF32LE(file, &m_damageParam10[1]);
        ReadF32LE(file, &m_damageParam10[2]);
        ReadF32LE(file, &m_dmgRandBase);
        ReadF32LE(file, &m_dmgRandRange);
        ReadS32LE(file, &m_manaRequired[0]);
        ReadS32LE(file, &m_manaRequired[1]);
        ReadS32LE(file, &m_manaRequired[2]);
    }
    return 1;
}
