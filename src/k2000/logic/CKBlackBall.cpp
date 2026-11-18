// CKBlackBall.cpp - reconstructed original translation unit 0x3798b8-0x37d2e0 (GAME_TOC1, main_toc1), 24 functions, 24 live.
// Primary class: CKBlackBall  key 0x94cc  category Logic  size 0x30c  vtable 0xb23458
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3798b8  CKBlackBall_Delete
//   [x] 0x379908  CKBlackBall_GetAbilityId
//   [x] 0x379910  CKBlackBall_IsChargeDisabled_maybe
//   [x] 0x379930  CKBlackBall_End
//   [x] 0x379a20  CKBlackBall_ResetRuntime
//   [x] 0x379a88  CKBlackBall_Start
//   [x] 0x379ad0  CKBlackBall_PostLoad
//   [x] 0x379b38  CKBlackBall_RecursiveRegistration  (the base's only: CKProjectileElement_RecursiveRegistration returns 1)
//   [x] 0x379b60  CKBlackBall_Destroy
//   [x] 0x379ba0  CKBlackBall_Construct
//   [x] 0x379bd8  CKBlackBall_DeleteArray
//   [x] 0x379c78  CKBlackBall_DeletingDestructor  (C++ deleting destructor)
//   [x] 0x379cc0  CKBlackBall_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x379cf0  CKBlackBall_DestructBody  (C++ destructor chain: vtable stores only)
//   [x] 0x379d20  CKBlackBall_Construct_2  (the constructor)
//   [ ] 0x379d58  RegisterCKBlackBallClass
//   [ ] 0x379de0  _GLOBAL__D_379de0
//   [ ] 0x379df0  _GLOBAL__I_379df0
//   [x] 0x379e00  CKBlackBall_CreateArray
//   [x] 0x379eb0  CKBlackBall_Create
//   [x] 0x379f08  CKBlackBall_UpdateCharge
//   [x] 0x37ab10  CKBlackBall_Fire
//   [ ] 0x37bd88  CKBlackBall_Save
//   [x] 0x37c8a8  CKBlackBall_Load
//
//   [ ] 0x9bf900  CKBlackBall_IsKindOfClass  [inline]
//   [ ] 0x9bf950  CKBlackBall_GetClassType  [inline]
//   [ ] 0x9bf958  CKBlackBall_GetClassID  [inline]
//   [ ] 0x9bf960  CKBlackBall_StartEmitterFx  [inline]
#include "k2000/logic/CKBlackBall.h"

#include <cmath>
#include <cstdint>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "Spyro2008/misc/CKS08AbilityHostBase.h"
#include "crt/ppc_ops.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKProjectileAccessor.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/cameras/CKAimCamembert.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/math/Math.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/services/CKSrvFx.h"

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

// 0x00379b60 CKBlackBall_Destroy (CKProjectileElement_Destroy 0x3bf2d0 is empty). DOTD: only a matrix that was created
// (the original destroys whatever the word holds).
void CKBlackBall::Destroy() {
    if (m_pUnk308 != nullptr) RwMatrixDestroy(m_pUnk308);
}

// 0x00379ad0 CKBlackBall_PostLoad
int32_t CKBlackBall::PostLoad(int32_t type) {
    CKProjectileElement::PostLoad(type);
    ShowUnderSector0(m_unk2a8);
    ShowUnderSector0(m_unk2e8);
    return 1;
}

// 0x00379a88 CKBlackBall_Start
void CKBlackBall::Start(CKS08AbilityHostBase* host) {
    CKProjectileElement::Start(host);
    if (m_pHost != nullptr) m_unk300 = 0;
}

// 0x00379930 CKBlackBall_End
void CKBlackBall::End(int32_t forced) {
    ShowUnderSector0(m_unk2a8);
    ShowUnderSector0(m_unk2e8);
    StopSounds(m_unk2f8);
    CKProjectileElement::End(forced);
}

// 0x00379a20 CKBlackBall_ResetRuntime (CKPoisonGrenade's sets the button to 1; this one 0).
void CKBlackBall::ResetRuntime(int32_t type) {
    CKProjectileElement::ResetRuntime(type);
    m_unk300 = 0;
    m_unk208 = 2;
    m_unk209 = 0;
    if (type == 0) m_pUnk308 = RwMatrixCreate();  // RwMatrixCreate_Thunk
}

namespace {
constexpr float kChargedFadeTime = 0x1.333334p-2f;  // TOC +0x322c (0x3e99999a, 0.3)
constexpr float kAlphaScale = 254.0f;               // TOC +0x3234

float WordF32(uint32_t bits) {
    float value;
    std::memcpy(&value, &bits, sizeof(value));
    return value;
}

// The five vectors +0x2ac..+0x2e7 as the original indexes them (+0x2ac + 12 x i): +0x2ac (read as three words, always
// 0), +0x2b8, +0x2c4, +0x2d0, +0x2dc.
CVector3 VectorAt(const CKBlackBall* g, uint32_t i) {
    switch (i) {
    case 0: return CVector3{WordF32(g->m_unk2ac[0]), WordF32(g->m_unk2ac[1]), WordF32(g->m_unk2ac[2])};
    case 1: return CVector3{g->m_unk2b8[0][0], g->m_unk2b8[0][1], g->m_unk2b8[0][2]};
    case 2: return CVector3{g->m_unk2b8[1][0], g->m_unk2b8[1][1], g->m_unk2b8[1][2]};
    case 3: return CVector3{g->m_unk2d0[0][0], g->m_unk2d0[0][1], g->m_unk2d0[0][2]};
    default: return CVector3{g->m_unk2d0[1][0], g->m_unk2d0[1][1], g->m_unk2d0[1][2]};
    }
}

// The inlined geometry alpha walk (CKPoisonGrenade.cpp's, CKBeamBreath.cpp's): every geometry takes `alpha` (CGeometry
// colour byte +0x23) and the "alpha blended" property bit 11 (vt+0x60 when it changes); 0xff clears it everywhere, and a
// geometry with property bit 12 and a material of mode 1..6 keeps 0xff without blending.
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

// The sound attached to the user's node (vt+0x08, +0x1c; 0x00111350).
void PlayOnOwner(CKSound* sound, CKS08AbilityHostBase* host) {
    sound->SetAttachObject(static_cast<IKHook*>(host->GetOwner())->m_pKGLObject);
}
}  // namespace

// 0x00379f08 CKBlackBall_UpdateCharge: the same instructions as CKPoisonGrenade_UpdateCharge 0x3b6148 (only the TOC
// offsets differ, their values are the same). The float tests keep the original's senses (ble / blt plain, the clamps
// with cror). Only called above level index 0 (IsChargeDisabled).
void CKBlackBall::UpdateCharge(float dt) {
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
            charged->Play(0.0f);  // 0x00111230 (TOC +0x3238)
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
                charge->SetPitch(1.0f);  // 0x00110ea0 (TOC +0x3230)
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

namespace {
// 0x00010690 Math_Sqrtf (fsqrts).
inline float MathSqrtf(float x) { return std::sqrt(x); }

const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC +0x323c)
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};       // 0x00c50d40 (TOC +0x3248)
constexpr float kFireAimCone = 0x1.921fb6p+1f;    // TOC +0x3240 (0x40490fdb, pi)
constexpr float kOne = 1.0f;                      // TOC +0x3230
constexpr float kMinusHalf = -0.5f;               // TOC +0x3244
constexpr float kDegToRad = 0.0174532905f;        // TOC +0x324c (0x3c8efa34)
constexpr float kZero = 0.0f;                     // TOC +0x3238

// The shot count: the level's count word, or the free projectiles when fewer (GetFreeSlots 0x001f3038 asked again then);
// a byte either way (the word's low byte).
uint32_t ShotCount(IKSerializable* accessor, int32_t countWord) {
    CKProjectileAccessor* a = static_cast<CKProjectileAccessor*>(accessor);
    if (static_cast<uint32_t>(a->GetFreeSlots() & 0xff) < static_cast<uint32_t>(countWord)) {
        return static_cast<uint32_t>(a->GetFreeSlots()) & 0xffu;
    }
    return static_cast<uint32_t>(countWord) & 0xffu;
}

// `v` normalised in place when its length (fsqrts of z*z + (x*x + y*y), fused) is not 0 (one reciprocal, three products).
void NormalizeAim(CVector3* v) {
    const float length = MathSqrtf(ppc::fmadds(v->z, v->z, ppc::fmadds(v->x, v->x, v->y * v->y)));
    if (length != kZero) {
        const float inv = kOne / length;
        v->z = v->z * inv;
        v->x = v->x * inv;
        v->y = v->y * inv;
    }
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

// One shot along `dir`: the level's speed plus the hero's (host vt+0x48), the damage object +0x20c, the owner (host
// vt+0x08), in the original's order; CKProjectileAccessor_Launch 0x001f2988 (vt+0x88) without a matrix, or, for the
// charged shots at a locked target, CKProjectileAccessor_Launch90 0x001f2a98 with the target (host vt+0xd4 asked again).
void LaunchShot(CKBlackBall* g, IKSerializable* accessor, float speed, const CVector3* pos, const CVector3* dir,
                bool targeted) {
    const float heroSpeed = g->m_pHost->GetHeroSpeedForAbility();  // vt+0x48
    IKSerializable* damage = g->m_unk20c;
    IKSerializable* owner = g->m_pHost->GetOwner();  // vt+0x08
    CKProjectileAccessor* a = static_cast<CKProjectileAccessor*>(accessor);
    if (targeted) {
        IKSerializable* target = g->m_pHost->GetLockedTarget();  // vt+0xd4
        a->Launch90(pos, dir, speed + heroSpeed, damage, owner, target, nullptr);
    } else {
        a->LaunchEx(pos, dir, speed + heroSpeed, damage, owner, nullptr);
    }
}
}  // namespace

// 0x0037ab10 CKBlackBall_Fire. The launch point is the hot spot's (GetLaunchPosDir, the null offset). Charged (the
// charge time +0x200 not below the level's full time +0x68: fcmpu, cror gt|eq, so a NaN is not charged) uses the second
// set of level values (+0x220 speed, +0x238 / +0x250 aim distances, +0x268 count, +0x280 spread, +0x298 accessor) and
// clears +0x300; else the first (+0x214, +0x22c / +0x244, +0x25c, +0x274, +0x28c). The aim cone (+0x184) takes the near /
// far distances before the host aims (vt+0x58, the result unused). With a locked target (vt+0xd4) the shots go along the
// normalised vector to its aim point (vt+0xdc from the hot spot), without along the aim direction (vt+0x24) normalised.
// Several shots fan out about Y over the spread. The damage parameters (vt+0x74, one rand draw) are set before the
// count. Unlike CKPoisonGrenade_Fire (shots at a point), the shots are directions; the charged shots at a locked target
// go through Launch90 with the target. Above level index 0 the two charge nodes are hidden and both sounds stopped.
// Returns 1 (also when the accessor has no projectile type).
uint8_t CKBlackBall::Fire() {
    const CVector3 offset = kNullVector;
    const CVector3 pos = GetLaunchPosDir(&offset);
    const uint32_t level = m_unk04;
    CKAimCamembert* aim = static_cast<CKAimCamembert*>(m_unk184);
    const float charge = m_unk200;
    const float full = m_unk68[level];
    const bool charged = charge > full || charge == full;  // cror gt|eq
    if (charged) m_unk300 = 0;
    const float* nearDist = charged ? m_unk238 : m_unk22c;
    const float* farDist = charged ? m_unk250 : m_unk244;
    const float* speeds = charged ? m_unk220 : m_unk214;
    const float* spreads = charged ? m_unk280 : m_unk274;
    const int32_t* counts = charged ? m_unk268 : m_unk25c;
    IKSerializable* const* accessors = charged ? m_unk298 : m_unk28c;
    aim->m_afUnk04[1] = nearDist[level];
    aim->m_afUnk04[2] = farDist[m_unk04];
    m_pHost->ComputeAimDirection(kFireAimCone, this, aim);  // vt+0x58 (the result unused)
    CVector3 dir;
    bool targeted = false;
    if (m_pHost->GetLockedTarget() != nullptr) {  // vt+0xd4
        const CVector3 target = m_pHost->GetTargetAimPoint(1, 0);  // vt+0xdc
        dir.y = target.y - pos.y;
        dir.x = target.x - pos.x;
        dir.z = target.z - pos.z;
        targeted = charged;
    } else {
        dir = m_pHost->GetAimDirection(0);  // vt+0x24
    }
    NormalizeAim(&dir);
    if (static_cast<CKProjectileAccessor*>(accessors[m_unk04])->m_pProjectileType != nullptr) {
        ApplyDamageParams(0);  // vt+0x74
        const uint32_t count = ShotCount(accessors[m_unk04], counts[m_unk04]);
        const uint32_t at = m_unk04;
        if (count == 1) {
            LaunchShot(this, accessors[at], speeds[at], &pos, &dir, targeted);
        } else {
            const float step = spreads[at] / static_cast<float>(static_cast<int32_t>(count - 1));
            for (uint32_t i = 0; i < count; ++i) {
                const CVector3 rotated = FanDirection(dir, step, i, spreads[m_unk04]);
                LaunchShot(this, accessors[m_unk04], speeds[m_unk04], &pos, &rotated, targeted);
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

// 0x0037c8a8 CKBlackBall_Load: CKProjectileElement's data, then (level data only) 236 bytes: six accessor
// references, three levels of ten parameters (a 3-iteration loop), references, and two pairs of 12-byte
// vectors (a 2-iteration loop).
int32_t CKBlackBall::Load(IKFile* file, int32_t type) {
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
        ReadS32LE(file, &m_unk25c[i]);
        ReadF32LE(file, &m_unk274[i]);
        ReadF32LE(file, &m_unk220[i]);
        ReadF32LE(file, &m_unk238[i]);
        ReadF32LE(file, &m_unk250[i]);
        ReadS32LE(file, &m_unk268[i]);
        ReadF32LE(file, &m_unk280[i]);
    }
    IKFile_ReadRef(file, &m_unk2a4);
    IKFile_ReadRef(file, &m_unk2a8);
    ReadU32LEWords(file, m_unk2ac, 3);
    IKFile_ReadRef(file, &m_unk2e8);
    IKFile_ReadRef(file, &m_unk2f8);
    ReadF32LE(file, &m_unk2ec);
    ReadF32LE(file, &m_unk2f0);
    ReadU32LE(file, &m_unk2f4);
    ReadF32LE(file, &m_unk2fc);
    for (int32_t i = 0; i < 2; ++i) {
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_unk2b8[i]), 3);
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_unk2d0[i]), 3);
    }
    return 1;
}
