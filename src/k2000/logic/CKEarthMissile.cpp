// CKEarthMissile.cpp - reconstructed original translation unit 0x3928a0-0x395018 (GAME_TOC1, main_toc1), 25 functions, 25 live.
// Primary class: CKEarthMissile  key 0x938c  category Logic  size 0x27c  vtable 0xb23758
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3928a0  CKEarthMissile_Delete
//   [x] 0x3928f0  CKEarthMissile_GetAbilityId
//   [x] 0x3928f8  CKEarthMissile_IsChargeDisabled_maybe
//   [x] 0x392918  CKEarthMissile_ResetRuntime
//   [x] 0x392960  CKEarthMissile_Update
//   [x] 0x3929c8  CKEarthMissile_Start
//   [x] 0x392a10  CKEarthMissile_PostLoad
//   [x] 0x392a78  CKEarthMissile_RecursiveRegistration  (inherited: CKProjectileElement_RecursiveRegistration)
//   [x] 0x392aa0  CKEarthMissile_Destroy  (inherited: CKProjectileElement_Destroy)
//   [x] 0x392ac8  CKEarthMissile_Construct
//   [x] 0x392b00  CKEarthMissile_DeleteArray
//   [x] 0x392ba0  CKEarthMissile_DeletingDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x392be8  CKEarthMissile_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x392c18  CKEarthMissile_DestructBody  (C++ destructor chain: vtable stores only)
//   [ ] 0x392c48  RegisterCKEarthMissileClass
//   [ ] 0x392cd0  _GLOBAL__D_392cd0
//   [ ] 0x392ce0  _GLOBAL__I_392ce0
//   [x] 0x392cf0  CKEarthMissile_Construct_2  (the same as 0x392ac8 CKEarthMissile_Construct)
//   [x] 0x392d28  CKEarthMissile_End
//   [x] 0x392e40  CKEarthMissile_Create
//   [x] 0x392e98  CKEarthMissile_CreateArray
//   [x] 0x392f48  CKEarthMissile_Fire
//   [x] 0x393538  CKEarthMissile_UpdateCharge
//   [ ] 0x393fc8  CKEarthMissile_Save
//   [x] 0x394778  CKEarthMissile_Load
//
//   [ ] 0x9bfb78  CKEarthMissile_IsKindOfClass  [inline]
//   [ ] 0x9bfbc8  CKEarthMissile_GetClassType  [inline]
//   [ ] 0x9bfbd0  CKEarthMissile_GetClassID  [inline]
//   [ ] 0x9bfbd8  CKEarthMissile_StartEmitterFx  [inline]
#include "k2000/logic/CKEarthMissile.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/misc/CKS08AbilityHostBase.h"
#include "crt/ppc_ops.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKProjectileAccessor.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKAnimatedFxCollection.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/services/CKSrvFx.h"

// 0x00394778 CKEarthMissile_Load: CKProjectileElement's data, then (level data only) 96 bytes: object
// references and floats (the original's reads are unrolled; the loops keep its order).
int32_t CKEarthMissile::Load(IKFile* file, int32_t type) {
    CKProjectileElement::Load(file, type);
    if (type != 0) return 1;
    for (int32_t i = 0; i < 3; ++i) {
        IKFile_ReadRef(file, &m_unk22c[i]);
        IKFile_ReadRef(file, &m_unk238[i]);
    }
    for (int32_t i = 0; i < 3; ++i) {
        ReadF32LE(file, &m_unk214[i]);
        ReadF32LE(file, &m_unk220[i]);
    }
    IKFile_ReadRef(file, &m_unk244);
    IKFile_ReadRef(file, &m_unk248);
    IKFile_ReadRef(file, &m_unk24c);
    ReadU32LE(file, &m_unk250);
    ReadF32LE(file, &m_unk254);
    ReadU32LE(file, &m_unk258);
    IKFile_ReadRef(file, &m_unk26c);
    ReadF32LE(file, &m_unk270);
    IKFile_ReadRef(file, &m_unk25c);
    ReadF32LE(file, &m_unk260);
    ReadF32LE(file, &m_unk264);
    ReadU32LE(file, &m_unk268);
    return 1;
}

namespace {
// SceneNode_SetVisibleInLayer_maybe 0x005832a8 (and its TOC bridge 0x0098f340) on a node reference.
void PutUnderSector0(IKSerializable* node) { SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(node), 1, 0, 0); }

// Both sounds of the dictionary stopped (CKSoundDictionaryID_GetSound 0x00112bc0, each asked twice; Sound_Stop
// 0x001111b0).
void StopSounds(IKSerializable* dictionary) {
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(dictionary);
    for (uint32_t i = 0; i < 2; ++i) {
        if (sounds->GetSound(i) != nullptr) Sound_Stop(sounds->GetSound(i), 0);
    }
}

float WordF32(uint32_t bits) {
    float value;
    std::memcpy(&value, &bits, sizeof(value));
    return value;
}

const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};    // 0x00c50d64 (TOC +0x3528)
constexpr float kFireAimCone = 0x1.921fb6p+1f;      // TOC +0x352c (0x40490fdb, pi)
constexpr float kOne = 1.0f;                        // TOC +0x3530
constexpr float kZero = 0.0f;                       // TOC +0x3534
constexpr float kChargedFadeTime = 0x1.333334p-2f;  // TOC +0x3544 (0x3e99999a, 0.3)
constexpr float kAlphaScale = 254.0f;               // TOC +0x3548

// The inlined geometry alpha walk (CKPoisonGrenade.cpp's): every geometry takes `alpha` (colour byte +0x23) and the
// "alpha blended" property bit 11 (vt+0x60 when it changes); 0xff clears it everywhere, and a geometry with property
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

// A charge node shown under the hot spot `spot`, moved by (x, y, z): its parent's vt+0x78 RemoveChild first,
// CSGHotSpot_AttachVolume 0x000ce2b8, the frame no longer the identity (flags bit 17 cleared), RwFrame_MarkDirty.
void ShowAtHotspot(CNode* node, CKS08AbilityHostBase* host, uint8_t spot, float x, float y, float z) {
    if (node->m_pParent != nullptr) node->m_pParent->RemoveChild(node);  // vt+0x78
    static_cast<CSGHotSpot*>(host->GetHotspot(spot))->AttachVolume(node);  // vt+0xcc
    RwFrame* frame = node->m_pRwFrame;
    frame->modelling.pos.x = frame->modelling.pos.x + x;
    frame->modelling.pos.y = frame->modelling.pos.y + y;
    frame->modelling.pos.z = frame->modelling.pos.z + z;
    frame->modelling.flags &= ~0x20000u;
    RwFrame_MarkDirty(frame);
}

// The sound attached to the user's node (vt+0x08, +0x1c; CKSound_SetAttachObject 0x00111350).
void AttachToOwner(CKSound* sound, CKS08AbilityHostBase* host) {
    sound->SetAttachObject(static_cast<IKHook*>(host->GetOwner())->m_pKGLObject);
}

// vt+0x104 (the hero host's GetHeroAttachmentSets 0x3ee6a0: the hero's +0x1070), as CKTransformElement.cpp reads it.
SAnimatedFxRig* AttachmentSets(CKS08AbilityHostBase* host) {
    IKSerializable* owner = host->GetOwner();
    if (owner != nullptr && owner->IsKindOfClass(CKHkS08Hero::kClassKey) != 0) {
        return reinterpret_cast<SAnimatedFxRig*>(&static_cast<CKHkS08Hero*>(owner)->m_apUnk1070[0][0]);
    }
    return reinterpret_cast<SAnimatedFxRig*>(host->GetAttachmentSets());
}
}  // namespace

// 0x00392a10 CKEarthMissile_PostLoad
int32_t CKEarthMissile::PostLoad(int32_t type) {
    CKProjectileElement::PostLoad(type);
    PutUnderSector0(m_unk24c);
    PutUnderSector0(m_unk25c);
    return 1;
}

// 0x003929c8 CKEarthMissile_Start
void CKEarthMissile::Start(CKS08AbilityHostBase* host) {
    CKProjectileElement::Start(host);
    if (m_pHost != nullptr) m_unk274 = 0;
}

// 0x00392960 CKEarthMissile_Update (CKAnimatedFxCollection_Update_maybe through its TOC bridge)
uint8_t CKEarthMissile::Update(float dt) {
    CKAnimatedFxCollection* collection = static_cast<CKAnimatedFxCollection*>(m_unk244);
    if (collection->m_bPlaying != 0) collection->Update(dt);
    return CKProjectileElement::Update(dt);
}

// 0x00392d28 CKEarthMissile_End
void CKEarthMissile::End(int32_t forced) {
    CKAnimatedFxCollection* collection = static_cast<CKAnimatedFxCollection*>(m_unk244);
    if (collection->m_bPlaying != 0) collection->Stop();  // TocBridge -> 0x005cc990
    StopSounds(m_unk26c);
    PutUnderSector0(m_unk24c);
    PutUnderSector0(m_unk25c);
    CKProjectileElement::End(static_cast<uint8_t>(forced));
}

// 0x00392918 CKEarthMissile_ResetRuntime
void CKEarthMissile::ResetRuntime(int32_t type) {
    CKProjectileElement::ResetRuntime(type);
    m_unk274 = 0;
    m_unk208 = 2;
    m_unk209 = 0;
}

// 0x00393538 CKEarthMissile_UpdateCharge. The float tests keep the original's senses: no burst while the charge time is
// not greater than the full time (ble: a NaN skips it), the ratio clamps with cror (a NaN stays), the fade with blt.
void CKEarthMissile::UpdateCharge(float dt) {
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_unk26c);
    if (m_unk200 > m_unk68[m_unk04] && m_unk274 == 0) {
        // Full: the burst at the hot spot (the inlined CKSrvFx::AcquireFx), the charge sound stopped, the charged one.
        m_unk274 = 1;
        CKSrvFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
        CKExplosionNodeFx* burst =
            static_cast<CKExplosionNodeFx*>(fx->AcquireFx(reinterpret_cast<IKFxData*>(m_unk248), this));
        if (burst != nullptr) {
            const CVector3 position = m_pHost->GetHotspotPosition(m_unk208);  // vt+0xd0
            burst->SetTranslation(&position, this);  // 0x001b66e8
            burst->Trigger(this, 0);                 // 0x001b82a8
            burst->ReleaseReservation(this);         // vt+0x54
        }
        m_unk278 = kChargedFadeTime;
        if (sounds->GetSound(0) != nullptr) Sound_Stop(sounds->GetSound(0), 0);
        CKSound* charged = sounds->GetSound(1);
        if (charged != nullptr) {
            AttachToOwner(charged, m_pHost);
            charged->Play(kZero);  // 0x00111230
        }
    }
    CNode* rock = static_cast<CNode*>(m_unk24c);
    if (rock != nullptr) {
        if (m_unk274 != 0) {
            // Charged: the fade-out over 0.3 s, then hidden.
            if ((rock->m_sgProperties & 4u) == 0) {
                const float left = m_unk278 - dt;
                m_unk278 = left;
                if (left < kZero) {
                    rock->m_sgProperties = (rock->m_sgProperties & 0xfffffffbu) | 4u;
                } else if (rock->m_lGeometryList != nullptr) {
                    SetMeshAlpha(rock, static_cast<uint8_t>(ppc::fctiwz(left / kChargedFadeTime * kAlphaScale)));
                }
            }
        } else if ((rock->m_sgProperties & 4u) != 0) {
            // The first charging frame: shown transparent under the hot spot, moved by +0x250 (words read as floats),
            // the charge sound at pitch 1.
            rock->m_sgProperties &= 0xfffffffbu;
            SetMeshAlpha(rock, 0);
            ShowAtHotspot(rock, m_pHost, m_unk208, WordF32(m_unk250), m_unk254, WordF32(m_unk258));
            CKSound* charge = sounds->GetSound(0);
            if (charge != nullptr) {
                AttachToOwner(charge, m_pHost);
                charge->SetPitch(kOne);  // 0x00110ea0
                charge->Play(kZero);
            }
        } else {
            // Charging: alpha and pitch follow the charge (clamped to 0..1).
            float ratio = m_unk200 / m_unk68[m_unk04];
            if (ratio <= kZero) {
                ratio = kZero;
            } else if (ratio >= kOne) {
                ratio = kOne;
            }
            if (rock->m_lGeometryList != nullptr) {
                SetMeshAlpha(rock, static_cast<uint8_t>(ppc::fctiwz(ratio * kAlphaScale)));
            }
            const float pitch = m_unk270;
            if (sounds->GetSound(0) != nullptr) {
                sounds->GetSound(0)->SetPitch(ppc::fmadds(ratio, pitch - kOne, kOne));
            }
        }
    }
    // The second node under the hot spot once charged, moved by +0x260.
    CNode* glow = static_cast<CNode*>(m_unk25c);
    if (glow != nullptr && m_unk274 != 0 && (glow->m_sgProperties & 4u) != 0) {
        glow->m_sgProperties &= 0xfffffffbu;
        ShowAtHotspot(glow, m_pHost, m_unk208, m_unk260, m_unk264, WordF32(m_unk268));
    }
}

// 0x00392f48 CKEarthMissile_Fire. The launch point is the hot spot's (GetLaunchPosDir, no extra offset); the aim cone
// (+0x184) goes to the host's aim (vt+0x58, the result unused). With a locked target (vt+0xd4) the missile flies
// towards its aim point (vt+0xdc from hot spot 1), else along the host's aim direction (vt+0x24); either normalised
// unless of length 0. Charged (the charge time +0x200 not less than the level's full time +0x68: cror gt|eq, a NaN is
// not charged) clears +0x274 and uses the second accessor and speed (+0x238, +0x220), else the first (+0x22c,
// +0x214). Without a projectile type nothing more happens; else the damage parameters (vt+0x74), the launch
// (CKProjectileAccessor_Launch 0x001f2988 at the level's speed plus the hero's, the damage object, the owner, no
// matrix) and, above level index 0, the effect collection plays, the charge nodes hide and both sounds stop.
uint8_t CKEarthMissile::Fire() {
    const CVector3 pos = GetLaunchPosDir(&kNullVector);
    m_pHost->ComputeAimDirection(kFireAimCone, this, m_unk184);  // vt+0x58
    IKSerializable* locked = m_pHost->GetLockedTarget();         // vt+0xd4
    CVector3 dir;
    if (locked != nullptr) {
        const CVector3 target = m_pHost->GetTargetAimPoint(1, 0);  // vt+0xdc
        dir.y = target.y - pos.y;
        dir.x = target.x - pos.x;
        dir.z = target.z - pos.z;
    } else {
        dir = m_pHost->GetAimDirection(0);  // vt+0x24
    }
    const float length = std::sqrt(ppc::fmadds(dir.z, dir.z, ppc::fmadds(dir.x, dir.x, dir.y * dir.y)));  // 0x00010690
    if (length != kZero) {
        const float inv = kOne / length;
        dir.y = dir.y * inv;
        dir.z = dir.z * inv;
        dir.x = dir.x * inv;
    }
    const uint32_t level = m_unk04;
    const bool charged = m_unk200 > m_unk68[level] || m_unk200 == m_unk68[level];  // cror gt|eq
    if (charged) m_unk274 = 0;
    IKSerializable* const* accessors = charged ? m_unk238 : m_unk22c;
    if (static_cast<CKProjectileAccessor*>(accessors[level])->m_pProjectileType == nullptr) return 1;
    ApplyDamageParams(0);  // vt+0x74
    const float speed = charged ? m_unk220[m_unk04] : m_unk214[m_unk04];
    CKProjectileAccessor* accessor = static_cast<CKProjectileAccessor*>(accessors[m_unk04]);
    const float heroSpeed = m_pHost->GetHeroSpeedForAbility();  // vt+0x48
    IKSerializable* damage = m_unk20c;
    IKSerializable* owner = m_pHost->GetOwner();  // vt+0x08
    accessor->LaunchEx(&pos, &dir, speed + heroSpeed, damage, owner, nullptr);
    if (m_unk04 != 0) {
        CKAnimatedFxCollection* collection = static_cast<CKAnimatedFxCollection*>(m_unk244);
        CSGLeaf* node = static_cast<CSGLeaf*>(static_cast<IKHook*>(m_pHost->GetOwner())->m_pKGLObject);  // +0x1c
        SAnimatedFxRig* rigs = AttachmentSets(m_pHost);                                  // vt+0x104
        CSGHotSpot* spot = static_cast<CSGHotSpot*>(m_pHost->GetHotspot(m_unk208));      // vt+0xcc
        collection->Play(node, rigs, spot);  // TocBridge 0x0098f4d0
        CNode* rock = static_cast<CNode*>(m_unk24c);
        if (rock != nullptr) rock->m_sgProperties = (rock->m_sgProperties & 0xfffffffbu) | 4u;
        CNode* glow = static_cast<CNode*>(m_unk25c);
        if (glow != nullptr) glow->m_sgProperties = (glow->m_sgProperties & 0xfffffffbu) | 4u;
        StopSounds(m_unk26c);
    }
    return 1;
}
