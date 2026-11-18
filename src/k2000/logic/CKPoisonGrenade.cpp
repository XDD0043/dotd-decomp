// CKPoisonGrenade.cpp - reconstructed original translation unit 0x3b47b8-0x3b8bd8 (GAME_TOC1, main_toc1), 24 functions, 24 live.
// Primary class: CKPoisonGrenade  key 0x948c  category Logic  size 0x30c  vtable 0xb23ca8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3b47b8  CKPoisonGrenade_Delete
//   [x] 0x3b4808  CKPoisonGrenade_GetAbilityId
//   [x] 0x3b4810  CKPoisonGrenade_IsChargeDisabled_maybe
//   [x] 0x3b4830  CKPoisonGrenade_End
//   [x] 0x3b4920  CKPoisonGrenade_ResetRuntime
//   [x] 0x3b4990  CKPoisonGrenade_Start
//   [x] 0x3b49d8  CKPoisonGrenade_PostLoad
//   [x] 0x3b4a40  CKPoisonGrenade_RecursiveRegistration  (inherited: CKProjectileElement_RecursiveRegistration)
//   [x] 0x3b4a68  CKPoisonGrenade_Destroy
//   [x] 0x3b4aa8  CKPoisonGrenade_Construct
//   [x] 0x3b4ae0  CKPoisonGrenade_DeleteArray
//   [x] 0x3b4b80  CKPoisonGrenade_DeletingDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x3b4bc8  CKPoisonGrenade_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x3b4bf8  CKPoisonGrenade_DestructBody  (C++ destructor chain: vtable stores only)
//   [x] 0x3b4c28  CKPoisonGrenade_Construct_2  (the same as 0x3b4aa8 CKPoisonGrenade_Construct)
//   [ ] 0x3b4c60  RegisterCKPoisonGrenadeClass
//   [ ] 0x3b4ce8  _GLOBAL__D_3b4ce8
//   [ ] 0x3b4cf8  _GLOBAL__I_3b4cf8
//   [x] 0x3b4d08  CKPoisonGrenade_Fire
//   [x] 0x3b6040  CKPoisonGrenade_CreateArray
//   [x] 0x3b60f0  CKPoisonGrenade_Create
//   [x] 0x3b6148  CKPoisonGrenade_UpdateCharge
//   [ ] 0x3b6d50  CKPoisonGrenade_Save
//   [x] 0x3b7ce0  CKPoisonGrenade_Load
//
//   [ ] 0x9c0048  CKPoisonGrenade_IsKindOfClass  [inline]
//   [ ] 0x9c0098  CKPoisonGrenade_GetClassType  [inline]
//   [ ] 0x9c00a0  CKPoisonGrenade_GetClassID  [inline]
//   [x] 0x9c00a8  CKPoisonGrenade_StartEmitterFx  [inline]
#include "k2000/logic/CKPoisonGrenade.h"

#include <cmath>
#include <cstdint>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "Spyro2008/misc/CKS08AbilityHostBase.h"
#include "crt/ppc_ops.h"
#include "k2000/core/Stub.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/logic/CKProjectileAccessor.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/cameras/CKAimCamembert.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/math/Math.h"
#include "k2000/scenegraph/CSGLeaf.h"

namespace {
// SceneNode_SetVisibleInLayer_maybe 0x005832a8 (and its TOC bridge) on a node reference.
void ShowUnderSector0(IKSerializable* node) { SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(node), 1, 0, 0); }

// Both sounds of the dictionary stopped (CKSoundDictionaryID_GetSound 0x00112bc0, Sound_Stop 0x001111b0).
void StopSounds(IKSerializable* dictionary) {
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(dictionary);
    for (uint32_t i = 0; i < 2; ++i) {
        if (sounds->GetSound(i) != nullptr) sounds->GetSound(i)->Stop(0);
    }
}
}  // namespace

// 0x003b4a68 CKPoisonGrenade_Destroy (CKProjectileElement_Destroy 0x3bf2d0 is empty). DOTD: only a matrix that was
// created (the original destroys whatever the word holds).
void CKPoisonGrenade::Destroy() {
    if (m_pUnk308 != nullptr) RwMatrixDestroy(m_pUnk308);
}

// 0x003b49d8 CKPoisonGrenade_PostLoad
int32_t CKPoisonGrenade::PostLoad(int32_t type) {
    CKProjectileElement::PostLoad(type);
    ShowUnderSector0(m_unk2a8);
    ShowUnderSector0(m_unk2e8);
    return 1;
}

// 0x003b4990 CKPoisonGrenade_Start
void CKPoisonGrenade::Start(CKS08AbilityHostBase* host) {
    CKProjectileElement::Start(host);
    if (m_pHost != nullptr) m_unk300 = 0;
}

// 0x003b4830 CKPoisonGrenade_End
void CKPoisonGrenade::End(int32_t forced) {
    ShowUnderSector0(m_unk2a8);
    ShowUnderSector0(m_unk2e8);
    StopSounds(m_unk2f8);
    CKProjectileElement::End(forced);
}

namespace {
constexpr float kChargedFadeTime = 0x1.333334p-2f;  // TOC +0x3ad0 (0x3e99999a, 0.3)
constexpr float kAlphaScale = 254.0f;               // TOC +0x3ad4

float WordF32(uint32_t bits) {
    float value;
    std::memcpy(&value, &bits, sizeof(value));
    return value;
}

// The five vectors +0x2ac..+0x2e7 as the original indexes them (+0x2ac + 12 x i): +0x2ac (read as three words, always
// 0), +0x2b8, +0x2c4, +0x2d0, +0x2dc.
CVector3 VectorAt(const CKPoisonGrenade* g, uint32_t i) {
    switch (i) {
    case 0: return CVector3{WordF32(g->m_unk2ac[0]), WordF32(g->m_unk2ac[1]), WordF32(g->m_unk2ac[2])};
    case 1: return CVector3{g->m_unk2b8[0][0], g->m_unk2b8[0][1], g->m_unk2b8[0][2]};
    case 2: return CVector3{g->m_unk2b8[1][0], g->m_unk2b8[1][1], g->m_unk2b8[1][2]};
    case 3: return CVector3{g->m_unk2d0[0][0], g->m_unk2d0[0][1], g->m_unk2d0[0][2]};
    default: return CVector3{g->m_unk2d0[1][0], g->m_unk2d0[1][1], g->m_unk2d0[1][2]};
    }
}

// The inlined geometry alpha walk (CKBeamBreath.cpp's): every geometry takes `alpha` (CGeometry colour byte +0x23) and
// the "alpha blended" property bit 11 (vt+0x60 when it changes); 0xff clears it everywhere, and a geometry with property
// bit 12 and a material of mode 1..6 keeps 0xff without blending.
void SetMeshAlpha(CNode* node, uint8_t alpha) {
    for (CGeometry* geometry = static_cast<CGeometry*>(node->m_lGeometryList); geometry != nullptr;
         geometry = geometry->m_pNext) {
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
}

// The sound attached to the user's node (the frame moves below: the matrix no longer the identity, flags bit 17 cleared,
// RwFrame_MarkDirty 0x00010698).
void PlayOnOwner(CKSound* sound, CKS08AbilityHostBase* host) {
    sound->SetAttachObject(static_cast<IKHook*>(host->GetOwner())->m_pKGLObject);  // vt+0x08, +0x1c; 0x00111350
}
}  // namespace

// 0x003b6148 CKPoisonGrenade_UpdateCharge. The float tests keep the original's senses (ble / blt plain, the clamps with
// cror). Only called above level index 0 (IsChargeDisabled).
void CKPoisonGrenade::UpdateCharge(float dt) {
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_unk2f8);
    const uint32_t level = m_unk04;
    if (m_unk200 > m_unk68[level] && m_unk300 == 0) {
        // Full: the burst at the hot spot (the inlined CKSrvFx::AcquireFx), the charge sound stopped, the charged one.
        m_unk300 = 1;
        CKSrvFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
        CKExplosionNodeFx* burst =
            static_cast<CKExplosionNodeFx*>(fx->AcquireFx(reinterpret_cast<IKFxData*>(m_unk2a4), this));
        if (burst != nullptr) {
            const CVector3 position = m_pHost->GetHotspotPosition(m_unk208);  // vt+0xd0
            burst->SetTranslation(&position, this);  // 0x001b66e8
            burst->Trigger(this, 0);                 // 0x001b82a8
            burst->ReleaseReservation(this);         // vt+0x54
        }
        m_unk304 = kChargedFadeTime;
        if (sounds->GetSound(0) != nullptr) Sound_Stop(sounds->GetSound(0), 0);  // 0x00112bc0, 0x001111b0
        CKSound* charged = sounds->GetSound(1);
        if (charged != nullptr) {
            PlayOnOwner(charged, m_pHost);
            charged->Play(0.0f);  // 0x00111230 (TOC +0x3ac0)
        }
    }
    CNode* ball = static_cast<CNode*>(m_unk2a8);
    if (ball != nullptr) {
        if (m_unk300 != 0) {
            // Charged: the fade-out over 0.3 s, then hidden.
            if ((ball->m_sgProperties & 4u) == 0) {
                const float left = m_unk304 - dt;
                m_unk304 = left;
                if (left < 0.0f) {
                    ball->m_sgProperties = (ball->m_sgProperties & 0xfffffffbu) | 4u;
                } else if (ball->m_lGeometryList != nullptr) {
                    SetMeshAlpha(ball, static_cast<uint8_t>(ppc::fctiwz(left / kChargedFadeTime * kAlphaScale)));
                }
            }
        } else if ((ball->m_sgProperties & 4u) != 0) {
            // The first charging frame: shown transparent under the hot spot, at the level's start scale, the charge
            // sound at pitch 1.
            ball->m_sgProperties &= 0xfffffffbu;
            SetMeshAlpha(ball, 0);
            if (ball->m_pParent != nullptr) ball->m_pParent->RemoveChild(ball);  // vt+0x78
            static_cast<CSGHotSpot*>(m_pHost->GetHotspot(m_unk208))->AttachVolume(ball);  // vt+0xcc, 0x000ce2b8
            RwFrame* frame = ball->m_pRwFrame;
            const CVector3 offset = VectorAt(this, 0);
            frame->modelling.pos.x = frame->modelling.pos.x + offset.x;
            frame->modelling.pos.y = frame->modelling.pos.y + offset.y;
            frame->modelling.pos.z = frame->modelling.pos.z + offset.z;
            frame->modelling.flags &= ~0x20000u;
            RwFrame_MarkDirty(frame);
            *m_pUnk308 = ball->m_pRwFrame->modelling;  // the 0x40 bytes, flags and pads included
            const CVector3 from = VectorAt(this, level);
            ball->ScaleXYZ(from.x, from.y, from.z);  // 0x000d0d28
            CKSound* charge = sounds->GetSound(0);
            if (charge != nullptr) {
                PlayOnOwner(charge, m_pHost);
                charge->SetPitch(1.0f);  // 0x00110ea0 (TOC +0x3aac)
                charge->Play(0.0f);
            }
        } else {
            // Charging: alpha, scale and pitch follow the charge (clamped to 0..1).
            float ratio = m_unk200 / m_unk68[level];
            if (ratio <= 0.0f) {
                ratio = 0.0f;
            } else if (ratio >= 1.0f) {
                ratio = 1.0f;
            }
            if (ball->m_lGeometryList != nullptr) {
                SetMeshAlpha(ball, static_cast<uint8_t>(ppc::fctiwz(ratio * kAlphaScale)));
            }
            ball->SetLocalMatrix(m_pUnk308);  // 0x000d0be8
            const CVector3 from = VectorAt(this, level);
            const CVector3 to = VectorAt(this, level + 2);
            ball->ScaleXYZ(ppc::fmadds(ratio, to.x - from.x, from.x), ppc::fmadds(ratio, to.y - from.y, from.y),
                           ppc::fmadds(ratio, to.z - from.z, from.z));
            const float pitch = m_unk2fc;
            if (sounds->GetSound(0) != nullptr) {
                sounds->GetSound(0)->SetPitch(ppc::fmadds(ratio, pitch - 1.0f, 1.0f));
            }
        }
    }
    // The second node under the hot spot once charged, moved by +0x2ec.
    CNode* glow = static_cast<CNode*>(m_unk2e8);
    if (glow != nullptr && m_unk300 != 0 && (glow->m_sgProperties & 4u) != 0) {
        glow->m_sgProperties &= 0xfffffffbu;
        if (glow->m_pParent != nullptr) glow->m_pParent->RemoveChild(glow);  // vt+0x78
        static_cast<CSGHotSpot*>(m_pHost->GetHotspot(m_unk208))->AttachVolume(glow);
        RwFrame* frame = glow->m_pRwFrame;
        frame->modelling.pos.x = frame->modelling.pos.x + m_unk2ec;
        frame->modelling.pos.y = frame->modelling.pos.y + m_unk2f0;
        frame->modelling.pos.z = frame->modelling.pos.z + WordF32(m_unk2f4);
        frame->modelling.flags &= ~0x20000u;
        RwFrame_MarkDirty(frame);
    }
}

// 0x003b4920 CKPoisonGrenade_ResetRuntime
void CKPoisonGrenade::ResetRuntime(int32_t type) {
    CKProjectileElement::ResetRuntime(type);
    m_unk208 = 2;
    m_unk209 = 1;
    m_unk300 = 0;
    if (type == 0) m_pUnk308 = RwMatrixCreate();  // RwMatrixCreate_Thunk
}

namespace {
// 0x00010690 Math_Sqrtf (fsqrts).
inline float MathSqrtf(float x) { return std::sqrt(x); }

const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC +0x3aa4)
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};       // 0x00c50d40 (TOC +0x3ab4)
constexpr float kFireAimCone = 0x1.921fb6p+1f;    // TOC +0x3aa8 (0x40490fdb, pi)
constexpr float kOne = 1.0f;                      // TOC +0x3aac
constexpr float kMinusHalf = -0.5f;               // TOC +0x3ab0
constexpr float kDegToRad = 0.0174532905f;        // TOC +0x3ab8 (0x3c8efa34)
constexpr float kHalf = 0.5f;                     // TOC +0x3abc
constexpr float kZero = 0.0f;                     // TOC +0x3ac0

// One shot: the level's speed plus the hero's (host vt+0x48), the damage object +0x20c, the owner (host vt+0x08), in
// the original's order. CKProjectileAccessor_LaunchAtPointEx 0x001f2c50 (its f2 argument, 1.0, is read by nothing).
void LaunchShot(CKPoisonGrenade* g, IKSerializable* accessor, float speed, const CVector3* pos,
                const CVector3* target) {
    const float heroSpeed = g->m_pHost->GetHeroSpeedForAbility();  // vt+0x48
    IKSerializable* damage = g->m_unk20c;
    IKSerializable* owner = g->m_pHost->GetOwner();  // vt+0x08
    static_cast<CKProjectileAccessor*>(accessor)->LaunchAtPointEx(pos, target, speed + heroSpeed, damage, owner);
}

// The shot count: the level's count word, or the free projectiles when fewer (GetFreeSlots 0x001f3038 asked again then);
// a byte either way (the word's low byte).
uint32_t ShotCount(IKSerializable* accessor, int32_t countWord) {
    CKProjectileAccessor* a = static_cast<CKProjectileAccessor*>(accessor);
    if (static_cast<uint32_t>(a->GetFreeSlots() & 0xff) < static_cast<uint32_t>(countWord)) {
        return static_cast<uint32_t>(a->GetFreeSlots()) & 0xffu;
    }
    return static_cast<uint32_t>(countWord) & 0xffu;
}

// The aim direction of the fan's shot i: spread across the fan, centred, in degrees, about the Y axis (the input and
// axis copies are normalised by Vec3_RotateTowardByAngle_maybe 0x005841a8 through its TOC bridge 0x0098f300).
CVector3 FanDirection(const CVector3& aim, float step, uint32_t i, float spread) {
    CVector3 in = aim;
    CVector3 axis = kAxisY;
    const float angle = ppc::fmadds(step, static_cast<float>(i), spread * kMinusHalf) * kDegToRad;
    CVector3 out;
    Vec3_RotateTowardByAngle(&out, &in, &axis, angle);
    return out;
}
}  // namespace

// 0x003b4d08 CKPoisonGrenade_Fire. The launch point is the hot spot's (GetLaunchPosDir, no extra offset). Charged (the
// charge time +0x200 reached the level's full time +0x68: cror gt|eq, a NaN is not charged) uses the second set of
// level values (+0x220 speed, +0x238 / +0x250 aim distances, +0x268 count, +0x280 spread, +0x298 accessor) and clears
// +0x300; else the first (+0x214, +0x22c / +0x244, +0x25c, +0x274, +0x28c). The aim cone (+0x184) takes the near / far
// distances before the host aims (vt+0x58, the result unused). With a locked target (vt+0xd4) the shots go to its aim
// point (vt+0xdc from the hot spot); without, to the launch point plus the aim direction (vt+0x24) normalised and
// scaled by 1 + (near + far) / 2. Several shots fan out about Y over the spread, each at the first target's distance.
// The damage parameters (vt+0x74, one rand draw) are set before the count. Above level index 0 the two charge nodes
// are hidden and both sounds stopped. Returns 1 (also when the accessor has no projectile type).
uint8_t CKPoisonGrenade::Fire() {
    const CVector3 pos = GetLaunchPosDir(&kNullVector);
    uint32_t level = m_unk04;
    CKAimCamembert* aim = static_cast<CKAimCamembert*>(m_unk184);
    const bool charged = !(m_unk200 < m_unk68[level]);  // fcmpu, cror gt|eq
    if (charged) m_unk300 = 0;
    // The two sets: the charged values are the level's entry three words further on.
    const float* nearDist = charged ? m_unk238 : m_unk22c;
    const float* farDist = charged ? m_unk250 : m_unk244;
    const float* speeds = charged ? m_unk220 : m_unk214;
    const float* spreads = charged ? m_unk280 : m_unk274;
    const int32_t* counts = charged ? m_unk268 : m_unk25c;
    IKSerializable* const* accessors = charged ? m_unk298 : m_unk28c;
    aim->m_afUnk04[1] = nearDist[level];
    aim->m_afUnk04[2] = farDist[m_unk04];
    m_pHost->ComputeAimDirection(kFireAimCone, this, aim);  // vt+0x58 (the result unused)
    if (m_pHost->GetLockedTarget() != nullptr) {             // vt+0xd4
        const CVector3 target = m_pHost->GetTargetAimPoint(1, 0);  // vt+0xdc
        if (static_cast<CKProjectileAccessor*>(accessors[level])->m_pProjectileType == nullptr) return 1;
        ApplyDamageParams(0);  // vt+0x74
        const uint32_t count = ShotCount(accessors[m_unk04], counts[m_unk04]);
        level = m_unk04;
        if (count == 1) {
            LaunchShot(this, accessors[level], speeds[level], &pos, &target);
        } else {
            const float step = spreads[level] / static_cast<float>(static_cast<int32_t>(count - 1));
            if (count != 0) {
                // The vector to the target and its squared length, once (the two sets sum the squares in another order).
                const float dx = target.x - pos.x;
                const float dy = target.y - pos.y;
                const float dz = target.z - pos.z;
                const float lengthSq = charged ? ppc::fmadds(dz, dz, ppc::fmadds(dy, dy, dx * dx))
                                               : ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
                const CVector3 toTarget = {dx, dy, dz};
                for (uint32_t i = 0; i < count; ++i) {
                    const CVector3 rotated = FanDirection(toTarget, step, i, spreads[m_unk04]);
                    const float length = MathSqrtf(lengthSq);  // 0x00010690
                    CVector3 shot;
                    shot.x = ppc::fmadds(length, rotated.x, pos.x);
                    shot.y = ppc::fmadds(length, rotated.y, pos.y);
                    shot.z = ppc::fmadds(length, rotated.z, pos.z);
                    LaunchShot(this, accessors[m_unk04], speeds[m_unk04], &pos, &shot);
                }
            }
        }
    } else {
        CVector3 dir = m_pHost->GetAimDirection(0);  // vt+0x24
        const float length = MathSqrtf(ppc::fmadds(dir.z, dir.z, ppc::fmadds(dir.x, dir.x, dir.y * dir.y)));
        if (length != kZero) {
            const float inv = kOne / length;
            dir.z = dir.z * inv;
            dir.x = dir.x * inv;
            dir.y = dir.y * inv;
        }
        const float reach = (nearDist[m_unk04] + farDist[m_unk04]) * kHalf;
        dir.z = ppc::fmadds(reach, dir.z, dir.z);
        dir.x = ppc::fmadds(reach, dir.x, dir.x);
        dir.y = ppc::fmadds(reach, dir.y, dir.y);
        const CVector3 target = {pos.x + dir.x, pos.y + dir.y, pos.z + dir.z};
        if (static_cast<CKProjectileAccessor*>(accessors[m_unk04])->m_pProjectileType == nullptr) return 1;
        ApplyDamageParams(0);  // vt+0x74
        const uint32_t count = ShotCount(accessors[m_unk04], counts[m_unk04]);
        level = m_unk04;
        if (count == 1) {
            LaunchShot(this, accessors[level], speeds[level], &pos, &target);
        } else {
            const float step = spreads[level] / static_cast<float>(static_cast<int32_t>(count - 1));
            for (uint32_t i = 0; i < count; ++i) {
                const CVector3 rotated = FanDirection(dir, step, i, spreads[m_unk04]);
                const float reachLength =
                    MathSqrtf(ppc::fmadds(dir.z, dir.z, ppc::fmadds(dir.x, dir.x, dir.y * dir.y)));
                CVector3 shot;
                shot.z = ppc::fmadds(rotated.z, reachLength, pos.z);
                shot.x = ppc::fmadds(rotated.x, reachLength, pos.x);
                shot.y = ppc::fmadds(rotated.y, reachLength, pos.y);
                LaunchShot(this, accessors[m_unk04], speeds[m_unk04], &pos, &shot);
            }
        }
    }
    if (m_unk04 != 0) {
        CNode* ball = static_cast<CNode*>(m_unk2a8);
        if (ball != nullptr) ball->m_sgProperties = (ball->m_sgProperties & 0xfffffffbu) | 4u;
        CNode* glow = static_cast<CNode*>(m_unk2e8);
        if (glow != nullptr) glow->m_sgProperties = (glow->m_sgProperties & 0xfffffffbu) | 4u;
        StopSounds(m_unk2f8);  // 0x00112bc0 / 0x001111b0, sounds 0 and 1
    }
    return 1;
}

// 0x003b7ce0 CKPoisonGrenade_Load: CKProjectileElement's data, then (level data only) 236 bytes, the same
// fields as CKBlackBall_Load in another order (the original unrolls the per-level reads; the loops keep its
// order), and two pairs of 12-byte vectors (a 2-iteration loop).
int32_t CKPoisonGrenade::Load(IKFile* file, int32_t type) {
    CKProjectileElement::Load(file, type);
    if (type != 0) return 1;
    for (int32_t i = 0; i < 3; ++i) {
        IKFile_ReadRef(file, &m_unk28c[i]);
        IKFile_ReadRef(file, &m_unk298[i]);
    }
    for (int32_t i = 0; i < 3; ++i) {
        ReadF32LE(file, &m_unk214[i]);
        ReadF32LE(file, &m_unk22c[i]);
        ReadF32LE(file, &m_unk244[i]);
        ReadF32LE(file, &m_unk220[i]);
        ReadF32LE(file, &m_unk238[i]);
        ReadF32LE(file, &m_unk250[i]);
    }
    IKFile_ReadRef(file, &m_unk2a4);
    IKFile_ReadRef(file, &m_unk2a8);
    ReadU32LEWords(file, m_unk2ac, 3);
    IKFile_ReadRef(file, &m_unk2f8);
    ReadF32LE(file, &m_unk2fc);
    for (int32_t i = 0; i < 3; ++i) {
        ReadS32LE(file, &m_unk25c[i]);
        ReadF32LE(file, &m_unk274[i]);
        ReadS32LE(file, &m_unk268[i]);
        ReadF32LE(file, &m_unk280[i]);
    }
    IKFile_ReadRef(file, &m_unk2e8);
    ReadF32LE(file, &m_unk2ec);
    ReadF32LE(file, &m_unk2f0);
    ReadU32LE(file, &m_unk2f4);
    for (int32_t i = 0; i < 2; ++i) {
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_unk2b8[i]), 3);
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_unk2d0[i]), 3);
    }
    return 1;
}
