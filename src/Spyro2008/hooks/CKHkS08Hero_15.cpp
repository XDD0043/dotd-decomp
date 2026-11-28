// Reconstructed original translation unit: 0x333618-0x33ca98 (GAME_TOC1, main_toc1), 30 functions, 28 live.
// Primary class: CKHkS08Hero  key 0x25c2  category Hook  size 0x1e00  vtable 0xb22c98
// Other owners: Math (1), ComputeSoundPitchFromAnimSpeed (1), Vec3 (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x333618  Math_RemapClamped
//   [x] 0x333688  ComputeSoundPitchFromAnimSpeed_maybe
//   [ ] 0x3336b8  KStub_Nop_3336b8  [dead]
//   [x] 0x3336c0  CKHkS08Hero_GetFootstepSurfaceType
//   [ ] 0x3337c0  CKHkS08Hero_UpdateSecondaryShadowPositions_maybe  [dead: no pointer to its descriptor 0xb9e970, no call]
//   [ ] 0x333b00  CKHkS08Hero_SetSecondaryShadowsActive  [dead: no pointer to its descriptor 0xb9e978, no call]
//   [ ] 0x333ea8  FUN_00333ea8  [dead]
//   [x] 0x333fc8  CKHkS08Hero_PlaySoundIfIdle
//   [x] 0x334108  CKHkS08Hero_PlaySoundIfIdleThunk
//   [x] 0x334110  CKHkS08Hero_PlayFootstepSoundsThunk  (thunk: target called directly)
//   [x] 0x334138  StaticInitAndDestruction_334138  (the two file statics at the end)
//   [ ] 0x334168  _GLOBAL__D_334168
//   [ ] 0x334178  _GLOBAL__I_334178
//   [x] 0x334188  CKHkS08Hero_PlaySound_maybe
//   [x] 0x3342c0  Vec3_LerpByRangeClamped_maybe  (the local copy in CKHkS08Hero_11.cpp; inline in CKHkS08Hero_2.cpp)
//   [x] 0x3343d8  CKHkS08Hero_StopSound
//   [x] 0x334450  CKHkS08Hero_SpawnHitExplosionFx
//   [x] 0x3346d8  CKHkS08Hero_UpdateModelFade_maybe
//   [x] 0x3349a8  CKHkS08Hero_ReleaseOwnedFx
//   [x] 0x334e20  CKHkS08Hero_DisableSwingTrails_maybe
//   [x] 0x335158  CKHkS08Hero_UpdateSwingTrails
//   [x] 0x336598  CKHkS08Hero_UpdateTrailAndFootstepFx  (the active swing trail filter data stubbed)
//   [x] 0x2ce4f8  CKGrpS08Hero_vf178  (local copy SecondaryShadowHotSpot: the group file is not this unit's)
//   [x] 0x337898  CKHkS08Hero_UpdatePartnerLinkBolt_maybe
//   [x] 0x338130  CKHkS08Hero_SetSwitchFeedbackFxActive_maybe
//   [x] 0x338458  CKHkS08Hero_UpdateTriggeredExplosionFxAndVibration_maybe
//   [x] 0x339050  CKHkS08Hero_UpdatePartnerLinkFx_maybe
//   [x] 0x33a050  CKHkS08Hero_UpdateShadowsAndFlightFx_maybe
//   [x] 0x33bbe0  CKHkS08Hero_SpawnFuryReleaseFx_maybe
//   [x] 0x33bf58  CKHkS08Hero_SpawnFuryChargeFx_maybe
//   [x] 0x33c688  CKHkS08Hero_SpawnShockwave
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "k2000/logic/fx/CKTargetCursorFxData.h"
#include "k2000/logic/fx/CKTargetCursorNodeFx.h"
#include "Spyro2008/logic/CKS08HeroBlow.h"
#include "Spyro2008/logic/CKS08HeroCombo.h"
#include "crt/ppc_ops.h"
#include "crt/xsinf.h"
#include "k2000/misc/Mat4.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/services/ICollisionMesh.h"
#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rpprtstd/RpPrtStdRuntime.h"
#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rpworld/RpGeometry.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/core/Stub.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/scenegraph/CTrailNodeFx.h"
#include "k2000/system/CTimeManager.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/fx/CKParticlesEffectNodeFx.h"
#include "k2000/managers/CKInput.h"
#include "k2000/managers/CKVibrationData.h"
#include "k2000/services/ICollisionMesh.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/cameras/IKCamera.h"
#include "k2000/fx/IKFx.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/cameras/CKCameraConstraint.h"
#include "k2000/logic/fx/CKExplosionFxData.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/logic/render/CKLightningBoltFxData.h"
#include "k2000/logic/render/CKLightningBoltNodeFx.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/components/CKMoveCpntUpdater.h"
#include "k2000/logic/render/CKMeshPopFxData.h"
#include "k2000/logic/render/CKMeshPopNodeFx.h"
#include "k2000/math/Math.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/services/CKSrvFx.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rtanim/RtAnim.h"
#include "k2000/animation/AnimBlendSlot.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/fx/CKSparkFxData.h"
#include "k2000/graphical/CKAnmKeyFrameController.h"
#include "k2000/graphical/animation/CAnimationManager.h"
#include "k2000/graphical/animation/CKBlenderController.h"
#include "k2000/logic/fx/CKSparkNodeFx.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/services/CKSrvShadow.h"

#include <cmath>
#include <cstring>
#include "platform/fps.h"

namespace {
// 0x00a70800 / 0x00a70808: the number of swing trails and of particle nodes of each hero.
const uint8_t kNbSwingTrails[2] = {13, 13};
const uint8_t kNbSwingParticles[2] = {17, 17};
}  // namespace

// 0x00334e20 CKHkS08Hero_DisableSwingTrails_maybe: every ribbon of the swing trails off, the particle nodes of the
// attacks stopped, the attack effect objects released, and the time scale back to 1.0.
void CKHkS08Hero::DisableSwingTrails() {
    for (uint32_t t = 0; t < kNbSwingTrails[m_ui8Hero]; ++t) {
        CTrailNodeFx* trail = static_cast<CTrailNodeFx*>(m_apTrails[t]);
        const uint32_t ribbons = trail->m_ui32NbTrail & 0xffu;
        for (uint32_t r = 0; r < ribbons; ++r) trail->SetRibbonActive(r, 0, 0);  // 0x009bdfb8
    }
    for (uint32_t p = 0; p < kNbSwingParticles[m_ui8Hero]; ++p) {
        CParticlesNodeFx* node = static_cast<CParticlesNodeFx*>(m_apParticles[p]);
        if (node != nullptr) {
            node->m_sgProperties = node->m_sgProperties & 0xfff7fbffu;  // bits 10 and 19
            node->m_pRpPrtStdEmitter->flag = node->m_pRpPrtStdEmitter->flag & 0xfffffff7u;
            node->StopEmitting();  // 0x000e6938
        }
    }
    // The attack and link effects: each one stopped and released by the hero (vt+0x58), then forgotten.
    IKSerializable** effects[6] = {&m_unk1dcc, &m_unk1cf4, &m_unk19b8, &m_unk19c0, &m_unk19c8, &m_unk19d0};
    for (IKSerializable** effect : effects) {
        if (*effect != nullptr) {
            static_cast<IKFx*>(*effect)->StopAndRelease(this);  // vt+0x58
            *effect = nullptr;
        }
    }
    g_pEngine->m_timeManager->m_fTimeScale = 1.0f;  // TOC1 +0x2854
}

// 0x00333618 Math_RemapClamped: `value` in [from0, from1] mapped linearly onto [to0, to1]; from1 below it: to1; from0
// at or below it (otherwise): 0; else to0. A degenerate range gives the middle of [to0, to1].
float Math_RemapClamped(float from0, float from1, float value, float to0, float to1) {
    if (from1 == from0) return (to0 + to1) * 0.5f;  // TOC1 +0x2810
    if (from1 >= value && from0 <= value) {
        const float t = value - from0;
        const float span = to1 - to0;
        const float range = from1 - from0;
        return to0 + span * t / range;
    }
    if (from1 < value) return to1;
    if (from0 <= value) return 0.0f;  // TOC1 +0x2814
    return to0;
}

// 0x003336c0 CKHkS08Hero_GetFootstepSurfaceType: 4 while climbing; else from the ground (the grab contact +0x11fc in the
// ground sub-state 11 outside 0x26 / 0x27, else the current ground): engine flag 2 -> 3, property 0x800 -> 0, 0x1000
// -> 1, 0x2000 -> 2, else (or no ground) 0.
uint8_t CKHkS08Hero::GetFootstepSurfaceType() {
    if (IsClimbingMovementMode2() != 0) return 4;  // 0x003401a0
    const ICollisionMesh* ground;
    const int16_t animation = static_cast<int16_t>(m_i16CurAnimIndex);
    if (m_ui8GroundAnimState == 0xb && animation != 0x27 && animation != 0x26) {
        ground = static_cast<const ICollisionMesh*>(m_gcContact11FC.m_pGround);
    } else {
        ground = static_cast<const ICollisionMesh*>(GetGroundInfo());  // 0x00361b68
    }
    if (ground == nullptr) return 0;
    if (((ground->m_ba16EngineFlags >> 1) & 1u) != 0) return 3;
    const uint16_t properties = ground->m_ui16PropertiesFlags;
    if ((properties & 0x800u) != 0) return 0;
    if ((properties & 0x1000u) != 0) return 1;
    if ((properties & 0x2000u) != 0) return 2;
    return 0;
}

namespace {
// The pitch clamp of PlaySoundIfIdle / PlaySound: below 0.5 (or NaN) 0.5, above 2 2 (TOC +0x2810 / +0x2818).
float ClampSoundPitch(float pitch) {
    if (!(pitch >= 0.5f)) return 0.5f;  // bge
    if (pitch > 2.0f) return 2.0f;      // ble
    return pitch;
}

// The volume of PlaySoundIfIdle / PlaySound: times the group's +0x204 for a hero that is not the tracked leader.
float HeroSoundVolume(const CKHkS08Hero* hero, float volume, uint32_t scaled) {
    if (scaled != 0 && hero->m_ui8Hero != hero->m_ui8TrackedLeader) {
        return volume * static_cast<const CKGrpS08Hero*>(hero->m_pGrpHero)->m_unk204;
    }
    return volume;
}
}  // namespace

// 0x00333fc8 CKHkS08Hero_PlaySoundIfIdle
void CKHkS08Hero::PlaySoundIfIdle(float volume, float pitch, uint32_t index, uint32_t scaled, uint32_t restart) {
    CKSound* sound = static_cast<CKSoundDictionaryID*>(m_pSoundDico)->GetSound(index);  // 0x00112bc0
    if (sound == nullptr) return;
    sound->SetPitch(ClampSoundPitch(pitch));               // 0x00110ea0
    sound->SetVolume(HeroSoundVolume(this, volume, scaled));  // 0x00110f10
    if (sound->CountInstances() != 0 && restart == 0) return;
    sound->Play(0.0f);  // 0x00111230; TOC +0x2814
}

// 0x00334108 CKHkS08Hero_PlaySoundIfIdleThunk: PlaySoundIfIdle with `restart` 1.
void CKHkS08Hero::PlaySoundIfIdleThunk(float volume, float pitch, uint32_t index, uint32_t scaled) {
    PlaySoundIfIdle(volume, pitch, index, scaled, 1);
}

// 0x00334188 CKHkS08Hero_PlaySound_maybe: the same, a playing sound stopped first.
void CKHkS08Hero::PlaySound(float volume, float pitch, uint32_t index, uint32_t scaled) {
    CKSound* sound = static_cast<CKSoundDictionaryID*>(m_pSoundDico)->GetSound(index);
    if (sound == nullptr) return;
    sound->SetPitch(ClampSoundPitch(pitch));
    sound->SetVolume(HeroSoundVolume(this, volume, scaled));
    if (sound->CountInstances() != 0) sound->Stop(0);  // 0x001111b0
    sound->Play(0.0f);
}

// 0x003343d8 CKHkS08Hero_StopSound: sound `index` stopped when it plays.
void CKHkS08Hero::StopSound(uint32_t index) {
    CKSound* sound = static_cast<CKSoundDictionaryID*>(m_pSoundDico)->GetSound(index);
    if (sound != nullptr && sound->CountInstances() != 0) sound->Stop(0);
}

namespace {
float GroupWordAsFloat(uint32_t word) {
    float value;
    std::memcpy(&value, &word, sizeof value);
    return value;
}
// The group's distance from hero `index` to the tether's middle (+0x314 / +0x318; 0 for another index).
float PartnerLinkDistance(const CKGrpS08Hero* group, uint8_t index) {
    if (index == 0) return GroupWordAsFloat(group->m_unk2d4[16]);  // +0x314
    if (index == 1) return GroupWordAsFloat(group->m_fHero1ToMidDist);
    return 0.0f;  // TOC1 +0x2814
}
// The lightning bolt of `data` taken from the FX pool for `hero`, its source the hero's hot spot 19 (no node). The
// inline pool lookup of UpdateShadowsAndFlightFx; null when none is free.
IKSerializable* AcquirePartnerLinkBolt(CKHkS08Hero* hero, IKSerializable* data) {
    CKLightningBoltFxData* bolt = static_cast<CKLightningBoltFxData*>(data);
    bolt->m_pSourceNode = nullptr;
    bolt->m_pSourceHotSpot = hero->m_apHotSpots[19];  // +0x4c
    return static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(bolt, hero);
}
// The geometry walk UpdatePartnerLinkFx and UpdateShadowsAndFlightFx inline: every geometry of `node` takes `alpha`
// (+0x23) and the translucent bit 11 of its properties (vt+0x60 when it changes); below 255 a geometry with property
// bit 12 and a material mode (+0x08 bits 3..6) of 1..6 stays opaque. The original runs a separate loop for 255 (every
// geometry opaque), which this gives too.
void SetNodeGeometryAlpha(CNode* node, uint8_t alpha) {
    for (CGeometry* geometry = static_cast<CGeometry*>(node->m_lGeometryList); geometry != nullptr;
         geometry = geometry->m_pNext) {
        uint8_t value = alpha;
        uint32_t translucent = alpha != 0xff ? 1u : 0u;
        if (alpha != 0xff && (geometry->m_BitProperties & 0x1000u) != 0) {
            const uint32_t mode = (static_cast<CMaterial*>(geometry->m_pMaterial)->m_baProperties >> 3) & 0xfu;
            if (mode != 0 && mode <= 6) {
                value = 0xff;
                translucent = 0;
            }
        }
        geometry->m_cGeometryColor[3] = value;
        const uint32_t bits = geometry->m_BitProperties;
        if (((bits >> 11) & 1u) != translucent) {
            geometry->m_BitProperties = (bits & 0xfffff7ffu) | (translucent << 11);
            geometry->UpdateProperties();  // vt+0x60
        }
    }
}
// The spark node of `spark` (+0x10) turned so that its at axis points along the world direction `direction`: the
// modelling matrix reset (CSGMovable_SetIdentity 0xd08f0), the world matrix updated (vt+0x50), the direction brought
// into the node's space by the inverse of its LTM (Mat4_Invert 0x23f878, Mat4_TransformVectors 0x23f7b0) and the
// basis built from it and the X axis (CSGMovable_SetBasisFromAtRight 0xd09d8, 0x00c50d34). Returns the basis' answer.
uint8_t PointSparkNodeAlong(CKSparkNodeFx* spark, CVector3* direction) {
    static const CVector3 kAxisX = {1.0f, 0.0f, 0.0f};  // 0x00c50d34 (a static initialiser's)
    CSGMovable* node = static_cast<CSGMovable*>(spark->m_pNode);
    node->SetIdentity();
    node->ForceWorldMatrixUpdate();  // vt+0x50
    CMatrix34 inverse;
    Mat4_Invert(&inverse, reinterpret_cast<const CMatrix34*>(&node->m_pRwFrame->ltm));
    Mat4_TransformVectors(&inverse, direction, direction, 1);
    return node->SetBasisFromAtRight(direction, &kAxisX);
}
// A spark node's frame placed at `position` in its parent's space (the modelling position, flag 0x20000 cleared,
// RwFrame_MarkDirty 0x10698).
void PlaceSparkNode(IKSerializable* spark, float x, float y, float z) {
    RwFrame* frame = static_cast<CSGMovable*>(static_cast<CKSparkNodeFx*>(spark)->m_pNode)->m_pRwFrame;
    frame->modelling.pos.z = z;
    frame->modelling.pos.x = x;
    frame->modelling.pos.y = y;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);
}
// A held spark stopped bursting (StopOwnedSparkEffect 0x1d4698), let go (vt+0x54) and forgotten.
void ReleaseSpark(IKSerializable*& slot, CKHkS08Hero* owner) {
    if (slot == nullptr) return;
    StopOwnedSparkEffect(static_cast<CKSparkNodeFx*>(slot), owner);
    static_cast<IKFx*>(slot)->ReleaseReservation(owner);
    slot = nullptr;
}
// A fade fraction as the alpha byte both fades write: 0 at or below 0, 255 at or above 1, else the truncated
// fraction x 255 (TOC1 +0x2880; fctiwz, the low byte).
uint8_t FadeAlphaByte(float t) {
    if (t <= 0.0f) return 0;     // cror lt|eq
    if (t >= 1.0f) return 0xff;  // cror gt|eq
    return static_cast<uint8_t>(ppc::fctiwz(t * 255.0f));
}
float FadeFloatFromBits(uint32_t bits) {
    float value;
    std::memcpy(&value, &bits, sizeof value);
    return value;
}
}  // namespace

// 0x003346d8 CKHkS08Hero_UpdateModelFade_maybe: the model's alpha (+0x1180) from the fade timer +0x1178 of the length
// +0x117c (messages 0xc20..0xc23): fading in (+0x1174 set) or out; a flickering fade (+0x1175) draws a rand: above
// 0.66 the next alpha starts from a second draw, else from the current alpha, and goes on by dt / length. Without a
// running timer the model is shown (fading in) or hidden (alpha 0). The model node (heroes 0 / 1: object 1) is hidden at
// alpha 0 and its geometries take the alpha.
void CKHkS08Hero::UpdateModelFade(float dt) {
    uint8_t alpha;
    if (m_unk1178 <= 0.0f) {  // ble (TOC1 +0x2814 = 0.0): a NaN timer runs
        alpha = m_unk1174 != 0 ? 0xff : 0;
    } else {
        float t;
        // BUG(original)_maybe: the test reads the link bolt's length +0x1188, the fraction the fade's own +0x117c.
        if (m_unk1188 <= 0.0f) {  // ble
            t = 1.0f;  // TOC1 +0x2854
        } else {
            float elapsed = m_unk117c - m_unk1178;
            if (elapsed < 0.0f) elapsed = 0.0f;
            t = elapsed / m_unk117c;
        }
        if (m_unk1175 == 1 && dotd::fps::Unlocked()) {
            // --fps N (not in the original): one flicker roll and byte step per 60 Hz frame, as at 60 fps (per
            // displayed frame the flicker would be faster and the byte-cut fade would stall).
            alpha = m_unk1180;
            const float kRandRange = 65535.0f;  // TOC1 +0x2878
            const float step = dotd::fps::Dt60(dt);
            for (int32_t i = 0; i < dotd::fps::Ticks(); ++i) {
                const float draw = static_cast<float>(static_cast<uint16_t>(Rand_Int())) / kRandRange;
                float from;
                if (draw > 0.66f) {
                    from = static_cast<float>(static_cast<uint16_t>(Rand_Int())) / kRandRange;
                } else {
                    from = static_cast<float>(alpha) / 255.0f;
                }
                float ft = ppc::fmadds(1.0f / m_unk117c, step, from);
                if (m_unk1174 == 0) ft = 1.0f - ft;
                alpha = FadeAlphaByte(ft);
            }
        } else {
        if (m_unk1175 == 1) {
            const uint8_t previous = m_unk1180;
            const float kRandRange = 65535.0f;  // TOC1 +0x2878
            const float draw = static_cast<float>(static_cast<uint16_t>(Rand_Int())) / kRandRange;
            float from;
            if (draw > 0.66f) {  // TOC1 +0x287c (0x3f28f5c3)
                from = static_cast<float>(static_cast<uint16_t>(Rand_Int())) / kRandRange;
            } else {
                from = static_cast<float>(previous) / 255.0f;  // TOC1 +0x2880
            }
            t = ppc::fmadds(1.0f / m_unk117c, dt, from);
        }
        if (m_unk1174 == 0) t = 1.0f - t;
        alpha = FadeAlphaByte(t);
        }
    }
    m_unk1180 = alpha;
    // BUG(original): another dragon index takes a stale register for the node; the heroes are 0 and 1.
    if (m_ui8Hero <= 1) {
        CNode* model = static_cast<CNode*>(m_apObjects[1]);
        model->m_sgProperties = (model->m_sgProperties & 0xfffffffbu) | (alpha == 0 ? 4u : 0u);
        SetNodeGeometryAlpha(model, m_unk1180);
    }
}

// 0x00337898 CKHkS08Hero_UpdatePartnerLinkBolt_maybe: the link bolts' intensity (+0x118c) from the timer +0x1184 of the
// length +0x1188 (messages 0xc24 / 0xc25: +0x1181 set fades in); at 0 both bolts are switched off. Otherwise the two
// bolts (+0x19c8 / +0x19d0, taken from the pool for the data +0x19c4 / +0x19cc when missing) are on, aimed at the
// middle of the two heroes' hot spots 19, at that intensity, their width scale growing from 0.33 to 1 as the camera
// (CKSrvCamera +0x598) is 2 to 5 away from the middle.
void CKHkS08Hero::UpdatePartnerLinkBolt() {
    uint8_t intensity;
    if (m_unk1184 <= 0.0f) {  // ble: a NaN timer runs
        intensity = m_unk1181 != 0 ? 0xff : 0;  // neg + srawi 31
    } else {
        float t;
        if (m_unk1188 <= 0.0f) {  // ble
            t = 1.0f;
        } else {
            float elapsed = m_unk1188 - m_unk1184;
            if (elapsed < 0.0f) elapsed = 0.0f;
            t = elapsed / m_unk1188;
        }
        if (m_unk1181 == 0) t = 1.0f - t;
        intensity = FadeAlphaByte(t);
    }
    m_unk118c = intensity;
    CKHkS08Hero* partner = GetPartnerHero();  // 0x002f85f8
    CVector3 own;
    CVector3 other;
    static_cast<CSGHotSpot*>(m_apHotSpots[19])->GetWorldPosition(&own);             // 0x000ce790 (+0x4c)
    static_cast<CSGHotSpot*>(partner->m_apHotSpots[19])->GetWorldPosition(&other);
    const float y = (own.y + other.y) * 0.5f;  // TOC1 +0x2810
    const float x = (own.x + other.x) * 0.5f;
    const float z = (own.z + other.z) * 0.5f;
    const CVector3& eye = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera)->m_v3RealPos;  // engine +0x70, +0x598
    const float dy = eye.y - y;
    const float dx = eye.x - x;
    const float dz = eye.z - z;
    const float distance = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));  // Math_Sqrtf 0x10690
    // The distance clamped to [2, 5] (TOC1 +0x2818 / +0x28b8) mapped to (d - 2) x 0.67 / 3 + 0.33 (+0x28bc / +0x28c0 /
    // +0x28c4); a NaN distance takes 0.33.
    const float kNear = 2.0f;
    const float kFar = 5.0f;
    const float kMin = 0.33f;
    float width;
    if (distance != distance) {
        width = kMin;
    } else {
        const float clamped = distance <= kNear ? kNear : (distance >= kFar ? kFar : distance);
        width = (clamped - kNear) * FadeFloatFromBits(0x3f2b851eu) / 3.0f + kMin;  // 0.67 one ulp low
    }
    CKLightningBoltNodeFx* bolts[2];
    if (m_unk118c == 0) {
        bolts[0] = static_cast<CKLightningBoltNodeFx*>(m_unk19c8);
        bolts[1] = static_cast<CKLightningBoltNodeFx*>(m_unk19d0);
        for (CKLightningBoltNodeFx* bolt : bolts) {
            if (bolt != nullptr && ((bolt->m_baFxData >> 3) & 1u) != 0) bolt->SetActiveForOwner(this, 0);  // 0x00581380
        }
        return;
    }
    if (m_unk19c8 == nullptr) m_unk19c8 = AcquirePartnerLinkBolt(this, m_unk19c4);  // the inline pool lookup
    if (m_unk19d0 == nullptr) m_unk19d0 = AcquirePartnerLinkBolt(this, m_unk19cc);
    bolts[0] = static_cast<CKLightningBoltNodeFx*>(m_unk19c8);
    bolts[1] = static_cast<CKLightningBoltNodeFx*>(m_unk19d0);
    const CVector3 middle = {x, y, z};
    for (CKLightningBoltNodeFx* bolt : bolts) {
        if (bolt == nullptr) continue;
        if ((bolt->m_baFxData & 8u) == 0) bolt->SetActiveForOwner(this, 1);
        bolt->SetTargetPoint(&middle, this);         // 0x0057a9d0
        bolt->SetStartIntensity(m_unk118c, this);    // 0x0057aad8
        bolt->SetEndIntensity(m_unk118c, this);      // 0x0057b990
        bolt->SetField20C(width, this);              // 0x0057b968
    }
}

// 0x00339050 CKHkS08Hero_UpdatePartnerLinkFx_maybe: the link between the two heroes. Its alphas grow with the hero's
// distance to the tether's middle (`active`; 255 when inactive), the hero's own two (+0x1194 / +0x1195) approach them,
// and while the group asks for the link (+0x2c8 bit 10) the four bolts (the hero's and the partner's +0x19c8 /
// +0x19d0) are on, aimed at the middle, with those alphas as their intensities (and, on a new link, new fades).
void CKHkS08Hero::UpdatePartnerLinkFx(uint32_t active) {
    static_cast<CSGMovable*>(m_pKGLObject)->ForceWorldMatrixUpdate();  // vt+0x50
    static_cast<CSGMovable*>(GetPartnerHero()->m_pKGLObject)->ForceWorldMatrixUpdate();  // 0x002f85f8
    CVector3 own;
    static_cast<CSGHotSpot*>(m_apHotSpots[19])->GetWorldPosition(&own);  // 0x000ce790
    CVector3 other;
    static_cast<CSGHotSpot*>(GetPartnerHero()->m_apHotSpots[19])->GetWorldPosition(&other);
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
    const float kHalf = 0.5f;  // TOC1 +0x2810
    CVector3 middle;
    if ((group->m_ui32PairStateFlags & 1u) == 0) {
        middle = {(own.x + other.x) * kHalf, (own.y + other.y) * kHalf, (own.z + other.z) * kHalf};
    } else {
        middle = {GroupWordAsFloat(group->m_unk2d4[7]), GroupWordAsFloat(group->m_unk2d4[8]),
                  GroupWordAsFloat(group->m_unk2d4[9])};  // +0x2f0
    }
    // The electric arcs (+0x19b8 / +0x19c0: CKElectricArcNodeFx_SetStartAndEndPoints 0x1b1fc0, SetStartAlpha
    // 0x1b1f18, SetEndAlpha 0x1b1ef0) are never taken from the pool in DotD (only ever cleared): skipped.
    uint8_t startAlpha = 0xff;
    uint8_t endAlpha = 0xff;
    if (active != 0) {
        float startNear = group->m_unk14c * kHalf;
        float endNear = group->m_unk150 * kHalf;
        float far = group->m_unk154 * kHalf;
        const float scale = group->m_unk108 / group->m_unk10c;  // CKGrpS08Hero_GetMaxPartnerDistance_maybe 0x2ce518
        if (scale != 1.0f) {  // TOC1 +0x2854
            far = far * scale;
            startNear = startNear * scale;
            endNear = endNear * scale;
        }
        const float distance = PartnerLinkDistance(group, m_ui8Hero);
        const float nearest = startNear > endNear ? endNear : startNear;
        if (nearest <= distance) {
            if (!(distance >= far)) {
                startAlpha = 0;
                if (distance > startNear) {
                    startAlpha = static_cast<uint8_t>(static_cast<int32_t>((distance - startNear) * 255.0f / (far - startNear)));  // TOC1 +0x2880
                }
                endAlpha = 0;
                if (distance > endNear) {
                    endAlpha = static_cast<uint8_t>(static_cast<int32_t>((distance - endNear) * 255.0f / (far - endNear)));
                }
            }
        } else {
            startAlpha = 0;
            endAlpha = 0;
            m_unk177c = 0.0f;
        }
        if ((group->m_ui32PairStateFlags & 2u) != 0) {
            startAlpha = 0;
            endAlpha = 0;
        }
    }
    // The far spark: past half the group's +0x158 (and without +0x2c8 bit 1) the spark of +0x19d4's data hangs under
    // hot spot 19 (taken from the pool into +0x19d8 when none is held) and points along the group's direction for the
    // hero (+0x2fc hero 0, +0x308 hero 1, else the null vector), in the node's own space; otherwise a held spark stops
    // bursting, is let go (vt+0x54) and forgotten.
    if (group->m_unk158 * kHalf < PartnerLinkDistance(group, m_ui8Hero) && (group->m_ui32PairStateFlags & 2u) == 0) {
        CKSparkFxData* data = static_cast<CKSparkFxData*>(m_unk19d4);
        data->m_unk0c = nullptr;
        data->m_unk10 = m_apHotSpots[19];  // +0x4c
        if (m_unk19d8 == nullptr) m_unk19d8 = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(data, this);
        if (m_unk19d8 != nullptr) {
            CVector3 direction = kHeroZeroVector;  // 0x00c50d64 (TOC1 +0x283c)
            if (m_ui8Hero == 0) {
                direction = {GroupWordAsFloat(group->m_unk2d4[10]), GroupWordAsFloat(group->m_unk2d4[11]),
                             GroupWordAsFloat(group->m_unk2d4[12])};  // +0x2fc
            } else if (m_ui8Hero == 1) {
                direction = {GroupWordAsFloat(group->m_unk2d4[13]), GroupWordAsFloat(group->m_unk2d4[14]),
                             GroupWordAsFloat(group->m_unk2d4[15])};  // +0x308
            }
            PointSparkNodeAlong(static_cast<CKSparkNodeFx*>(m_unk19d8), &direction);
        }
    } else {
        ReleaseSpark(m_unk19d8, this);
    }
    // The model (heroes 0 / 1: object 1) hidden when startAlpha is 0, its geometries at startAlpha.
    // BUG(original): another dragon index takes a stale register for the node; the heroes are 0 and 1.
    if (m_ui8Hero <= 1) {
        CNode* model = static_cast<CNode*>(m_apObjects[1]);
        model->m_sgProperties = (model->m_sgProperties & 0xfffffffbu) | (startAlpha == 0 ? 4u : 0u);
        SetNodeGeometryAlpha(model, startAlpha);
    }
    if (dotd::fps::Unlocked()) {
        // --fps N (not in the original): one step per 60 Hz frame, each cut to a byte as at 60 fps (per displayed
        // frame the cut stalls the rise and turns the 5/s fall into 1 per frame).
        const float step = dotd::fps::Dt60(m_unk88c);
        for (int32_t i = 0; i < dotd::fps::Ticks(); ++i) {
            float s[3] = {static_cast<float>(startAlpha), m_unk1194 < startAlpha ? 200.0f : 5.0f, static_cast<float>(m_unk1194)};
            m_unk1194 = static_cast<uint8_t>(static_cast<int32_t>(FloatApproach_Step(step, s)));
            float e[3] = {static_cast<float>(endAlpha), m_unk1195 < endAlpha ? 200.0f : 5.0f, static_cast<float>(m_unk1195)};
            m_unk1195 = static_cast<uint8_t>(static_cast<int32_t>(FloatApproach_Step(step, e)));
        }
    } else {
    float startApproach[3] = {static_cast<float>(startAlpha), m_unk1194 < startAlpha ? 200.0f : 5.0f,
                              static_cast<float>(m_unk1194)};  // TOC1 +0x28d4 / +0x28b8
    m_unk1194 = static_cast<uint8_t>(static_cast<int32_t>(FloatApproach_Step(m_unk88c, startApproach)));  // 0x002436e8
    float endApproach[3] = {static_cast<float>(endAlpha), m_unk1195 < endAlpha ? 200.0f : 5.0f,
                            static_cast<float>(m_unk1195)};
    m_unk1195 = static_cast<uint8_t>(static_cast<int32_t>(FloatApproach_Step(m_unk88c, endApproach)));
    }
    const uint8_t startIntensity = m_unk1194;
    const uint8_t endIntensity = m_unk1195;
    if ((group->m_ui32PairStateFlags & 0x400u) == 0) return;
    CKHkS08Hero* partner = GetPartnerHero();
    IKSerializable** slots[4] = {&m_unk19c8, &m_unk19d0, &partner->m_unk19c8, &partner->m_unk19d0};
    CKHkS08Hero* owners[4] = {this, this, partner, partner};
    const uint32_t flags = group->m_ui32PairStateFlags;
    if ((flags & 2u) != 0 && (flags & 4u) == 0) {
        for (int i = 0; i < 4; ++i) {
            CKLightningBoltNodeFx* bolt = static_cast<CKLightningBoltNodeFx*>(*slots[i]);
            if (bolt != nullptr && ((bolt->m_baFxData >> 3) & 1u) != 0) bolt->SetActiveForOwner(owners[i], 0);  // 0x581380
        }
        return;
    }
    const float kFadeRate = 10.0f;  // TOC1 +0x28d8
    uint32_t linked = 1;
    if ((m_ui32StatusFlagsED4 & 0x20u) == 0) linked = (partner->m_ui32StatusFlagsED4 >> 5) & 1u;
    bool fade = true;
    float startTarget = 1.0f;  // TOC1 +0x2854
    float timer = 1.0f;
    float endTarget = 1.0f;
    if (!(m_unk177c > 0.0f) && m_unk19d8 != 0) {
        m_unk177c = kFadeRate;
        if (linked != 0) {
            timer = group->m_unk164;
            startTarget = group->m_unk15c;
            endTarget = group->m_unk160;
        } else {
            timer = group->m_unk170;
            startTarget = group->m_unk168;
            endTarget = group->m_unk16c;
        }
    } else if (linked != 0) {
        m_unk177c = kFadeRate;
        timer = group->m_unk164;
        startTarget = group->m_unk15c;
        endTarget = group->m_unk160;
    } else {
        fade = false;
    }
    for (int i = 0; i < 4; ++i) {
        CKLightningBoltNodeFx* bolt = static_cast<CKLightningBoltNodeFx*>(*slots[i]);
        if (bolt == nullptr) continue;
        if ((bolt->m_baFxData & 8u) == 0) {
            bolt->SetActiveForOwner(owners[i], 1);
            bolt = static_cast<CKLightningBoltNodeFx*>(*slots[i]);
        }
        const CVector3 target = middle;
        bolt->SetTargetPoint(&target, owners[i]);                // 0x0057a9d0
        bolt->SetStartIntensity(startIntensity, owners[i]);      // 0x0057aad8
        bolt->SetEndIntensity(endIntensity, owners[i]);          // 0x0057b990
        if (fade) {
            bolt->SetStartSmoothParams(startTarget, timer, kFadeRate, kFadeRate, 0.0f, kFadeRate, owners[i]);  // 0x0057a890
            bolt->SetEndSmoothParams(endTarget, timer, kFadeRate, kFadeRate, 0.0f, kFadeRate, owners[i]);      // 0x0057a8d0
        }
    }
}

namespace {
// A particle node told to emit (bit 10 on, the pending bit 19 off, the speed adjustment 0, its emitter active and
// emitting) when it does not yet; or to stop (bits 10 and 19 off, the emitter's emit flag off) when it does.
void EmitParticleNode(IKSerializable* object, bool on) {
    CParticlesNodeFx* node = static_cast<CParticlesNodeFx*>(object);
    if (node == nullptr) return;
    if (on) {
        if ((node->m_sgProperties & 0x400u) != 0) return;
        node->m_sgProperties = (node->m_sgProperties | 0x400u) & ~0x80000u;
        node->m_fEmissionSpeedAdjustment = 0.0f;
        node->m_pRpPrtStdEmitter->flag |= 0xau;
    } else {
        if ((node->m_sgProperties & 0x400u) == 0) return;
        node->m_sgProperties &= 0xfff7fbffu;
        node->m_pRpPrtStdEmitter->flag &= 0xfffffff7u;
    }
}
// The game's inlined cosf (the library's of the magnitude for a negative argument by its sign bit).
float HeroCosf(float x) {
    int32_t bits;
    std::memcpy(&bits, &x, 4);
    return bits < 0 ? crt::LibCosf(-x) : crt::InlineCosf(x);
}
}  // namespace

// 0x00338458 CKHkS08Hero_UpdateTriggeredExplosionFxAndVibration_maybe: particles 16 emit while +0xecc bit 11 is set
// without +0xec4 bit 19; with +0xecc bit 12 the explosion +0x1a00 goes off at hot spot 4 along +0x12a0; particles 12
// and 13 emit while +0xec4 bit 19 is set. While +0x13cc is set: when the camera's view axis is within +0xe38 degrees of
// the model's at row the flash +0x19f8 starts (it keeps its reservation) and the explosion +0x19fc goes off as above;
// then the pad vibration +0x1170 for the tracked leader.
void CKHkS08Hero::UpdateTriggeredExplosionFxAndVibration() {
    if ((m_unkecc & 0x800u) == 0 || (m_unkec4 & 0x80000u) != 0) {
        EmitParticleNode(m_apParticles[16], false);  // +0x40
    } else {
        EmitParticleNode(m_apParticles[16], true);
    }
    CKSrvFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);  // TOC +0x282c
    // The explosion's matrix: along +0x12a0 with the Y axis up (0x00c50d40, TOC +0x28c8), at hot spot 4.
    auto explode = [this, fx](IKSerializable* data) {
        CVector3 position;
        static_cast<CSGHotSpot*>(m_apHotSpots[4])->GetWorldPosition(&position);  // 0x000ce790
        RwMatrix matrix;
        const CVector3 up = {0.0f, 1.0f, 0.0f};
        const CVector3 at = {m_unk12a0, m_unk12a4, m_unk12a8};
        Mat4_SetBasisFromAtUp(reinterpret_cast<CMatrix34*>(&matrix), &at, &up);  // 0x0023fd30
        matrix.pos.x = position.x;
        matrix.pos.y = position.y;
        matrix.pos.z = position.z;
        matrix.flags &= 0xfffdffffu;
        IKFx* effect = fx->AcquireFx(static_cast<IKFxData*>(data), this);  // the inline pool lookup
        if (effect == nullptr) return;
        CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(effect);
        explosion->SetMatrix(&matrix, this);  // 0x001b6368
        explosion->Trigger(this, 0);          // 0x001b82a8
        explosion->ReleaseReservation(this);  // vt+0x54
    };
    if ((m_unkecc & 0x1000u) != 0) explode(m_unk1a00);
    const bool on = (m_unkec4 & 0x80000u) != 0;
    EmitParticleNode(m_apParticles[12], on);  // +0x30
    EmitParticleNode(m_apParticles[13], on);  // +0x34
    if (m_unk13cc == 0) return;
    const float angle = m_unke38 * 1.74532905e-02f;  // TOC +0x28cc (pi / 180)
    const RwFrame* model = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
    const CKSrvCamera* camera = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);
    const float c = HeroCosf(angle);
    const CVector3& view = camera->m_v3RealAxisZ;  // +0x5c8
    const float dot = ppc::fmadds(view.z, model->modelling.at.z,
                                  ppc::fmadds(view.x, model->modelling.at.x, view.y * model->modelling.at.y));
    if (dot > c && fx != nullptr) {
        fx->AcquireFx(static_cast<IKFxData*>(m_unk19f8), this);  // the flash: started, never released here
        explode(m_unk19fc);
    }
    if (m_unk1170 != nullptr && m_ui8Hero == m_ui8TrackedLeader) {
        CKVibrationData* data = static_cast<CKVibrationData*>(m_unk1170);
        data->m_pOwner = this;
        data->m_ui8NumPad = m_ui8Leader;
        data->m_ui8OwnerIndex = 2;
        static_cast<CKInput*>(g_pEngine->m_input)->PlayVibration(data);  // 0x00107d38
    }
}

namespace {
float HeroWordAsFloat(uint32_t word) { return GroupWordAsFloat(word); }
// 0x00303368-style read of the inner blender's active key-frame controller (vt+0x194 GetAnimBlendSlot, its controller
// +4, the +0x50 array at the slot's +0x10); its +0x54 is the animation time.
CKAnmKeyFrameController* FlightActiveController(CKHkS08Hero* hero) {
    AnimBlendSlot* slot = hero->GetAnimBlendSlot();
    CKBlenderController* blender = static_cast<CKBlenderController*>(slot->m_pController);
    return static_cast<CKAnmKeyFrameController*>(blender->m_apControllers[slot->m_unk10]);
}
// 0x002ce4f8 CKGrpS08Hero_vf178 (local copy; the hero calls it through the group's vtable): the hot spot of secondary
// shadow `index` of `hero` (tables 0x00c40958 / 0x00c40960 through 0x00b01010, TOC1 +0x1c0c; signed, -1 none).
// BUG(original): no bound checks (the heroes are 0 and 1, the shadows 0..4).
int8_t SecondaryShadowHotSpot(uint8_t hero, uint32_t index) {
    static const int8_t kHotSpots[2][8] = {{4, 0x0e, 0x16, 0x17, 5, 0, 0, 0}, {4, 0x0e, 0x15, 0x16, 5, 0, 0, 0}};
    return kHotSpots[hero][index];
}
}  // namespace

// 0x0033a050 CKHkS08Hero_UpdateShadowsAndFlightFx_maybe (vt+0x11c). The flight animation 0x40's wings and field of
// view (else the field of view put back and the wings hidden), the partner link, the triggered explosions, the five
// secondary shadows, the two flight sparks and the air current's pad vibration, the queued explosion (+0xecc bit 4),
// the glow node and the two partner-link bolts taken from the pool.
void CKHkS08Hero::UpdateShadowsAndFlightFx() {
    CKSrvCamera* camera = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);
    // BUG(original): another dragon index takes a stale register for the wings' node; the heroes are 0 and 1.
    CNode* wings = static_cast<CNode*>(m_apObjects[0]);
    bool flight = false;
    if (m_i16CurAnimIndex == 0x40 && IsFlyingMovementMode1() != 0) {  // 0x00340188
        // The animation's length (its dictionary entry's +0x10), at most +0xe0c when +0xe08 is set.
        const RtAnimAnimation* animation = CAnimationManager_GetAnimation(
            static_cast<uint32_t>(static_cast<CAnimationDictionary*>(m_pAnimDico)->m_apAnimations[0x40]));
        float duration = animation->duration;
        if (m_unke08 != 0 && duration > m_unke0c) duration = m_unke0c;  // ble
        const float time = FlightActiveController(this)->m_unk54;
        // The wings' opacity +0xde4 fades in over the first +0xddc seconds and out over the last +0xde0.
        float opacity = m_unkde4;
        if (time < m_unkddc) {  // bge
            opacity = opacity * (time / m_unkddc);
        } else if (duration - m_unkde0 < time) {  // bge
            opacity = opacity * ((duration - time) / m_unkde0);
        }
        flight = duration >= time;  // cror (unordered: not past it)
        if (flight) {
            const float ratio = time / duration;
            const RwFrame* model = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
            const CVector3& view = camera->m_v3RealAxisZ;  // +0x5c8
            float facing = ppc::fmadds(view.z, model->modelling.at.z,
                                       ppc::fmadds(view.x, model->modelling.at.x, view.y * model->modelling.at.y));
            float facingSquared;
            if (facing < 0.0f || facing == 0.0f) {  // cror lt / eq
                facingSquared = 0.0f;
                facing = 0.0f;
            } else if (!(facing >= 1.0f)) {  // cror gt / eq, TOC1 +0x2854
                facingSquared = facing * facing;
            } else {
                facing = 1.0f;
                facingSquared = 1.0f;
            }
            const float rest = 1.0f - ratio;
            wings->m_sgProperties &= 0xfffffffbu;  // shown
            // The wings' scale blended from +0xdf0 to +0xdfc by the animation's progress.
            const float sx = ppc::fmadds(ratio, HeroWordAsFloat(m_unkdfc), rest * m_unkdf0);
            const float sy = ppc::fmadds(ratio, HeroWordAsFloat(m_unke00), rest * m_unkdf4);
            const float sz = ppc::fmadds(ratio, m_unke04, rest * m_unkdf8);
            const RwV3d position = wings->m_pRwFrame->modelling.pos;
            wings->SetIdentity();          // 0x000d08f0
            wings->ScaleXYZ(sx, sy, sz);  // 0x000d0d28
            RwFrame* frame = wings->m_pRwFrame;
            frame->modelling.pos.z = position.z;
            frame->modelling.pos.x = position.x;
            frame->modelling.pos.y = position.y;
            frame->modelling.flags &= 0xfffdffffu;
            RwFrame_MarkDirty(frame);  // 0x00010698
            if (wings->m_lGeometryList != nullptr) {
                const float alpha = opacity * facingSquared * 255.0f;  // TOC1 +0x2880
                SetNodeGeometryAlpha(wings, static_cast<uint8_t>(ppc::fctiwz(alpha)));  // the low byte (stfiwx, lbz +3)
            }
            // The field of view: from the one kept in +0xeec (the camera's, the first time) towards it plus
            // facing^2 * +0xe10 over the first +0xe14 of the progress, and back over the rest.
            float base = m_unkeec;
            if (base == -1.0f) {  // TOC1 +0x2834
                base = camera->m_pCurrentCamera->m_unk18;
                m_unkeec = base;
            }
            const float target = ppc::fmadds(facing, facing * m_unke10, base);
            float fov;
            if (!(ratio < m_unke14)) {  // bge
                fov = ppc::fmadds(rest / (1.0f - m_unke14), target - base, base);
            } else {
                fov = ppc::fmadds(ratio / m_unke14, target - base, base);
            }
            static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera)->m_pCurrentCamera->m_unk18 = fov;  // +0x474 +0x18
        }
    }
    if (!flight) {
        if (m_unkeec != -1.0f) {  // TOC1 +0x2834
            camera->m_pCurrentCamera->m_unk18 = m_unkeec;
            m_unkeec = -1.0f;
        }
        wings->m_sgProperties = (wings->m_sgProperties & 0xfffffffbu) | 4u;  // hidden
    }
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
    uint32_t active = ((group->m_ui32PairStateFlags >> 2) & 1u) ^ 1u;
    CKCameraConstraint* zone = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera)->m_pActiveConstraint;
    if (zone != nullptr) {
        uint32_t zoneFlags;
        std::memcpy(&zoneFlags, &zone->m_unk20, sizeof zoneFlags);
        if ((zoneFlags & 0x400000u) != 0 && group->m_ui8ControlledHeroCount == 2) active = 0;  // GetControlledHeroCount 0x2ca288
    }
    UpdatePartnerLinkFx(active);  // 0x00339050
    UpdateTriggeredExplosionFxAndVibration();  // 0x00338458
    // The five secondary shadows (+0xfd0 + 0x20 x i, their components +0xfbc[i]): with +0x358 bit 23 or +0x35c bit 3
    // the registered ones leave the shadow service; else the missing ones whose hot spot exists join it, the main
    // shadow's ground point is updated (0x365c00) and each one with a hot spot takes that hot spot's x / z, the main
    // point's height, normal and +0x18.
    CKSrvShadow* shadows = static_cast<CKSrvShadow*>(g_pEngine->m_srvShadow);  // engine +0x88
    CKShadowGround* grounds[5] = {
        reinterpret_cast<CKShadowGround*>(&m_unkfd0), reinterpret_cast<CKShadowGround*>(&m_unkff0),
        reinterpret_cast<CKShadowGround*>(&m_unk1010), reinterpret_cast<CKShadowGround*>(&m_unk1030),
        reinterpret_cast<CKShadowGround*>(&m_unk1050)};
    if ((m_ui32HeroFlags358 & 0x800000u) != 0 || (m_ui32HeroFlags35C & 8u) != 0) {
        for (uint32_t i = 0; i < 5; ++i) {
            if (grounds[i]->m_bUsed_maybe != 0) shadows->UnregisterCaster(grounds[i], m_apUnkfbc[i]);  // 0x001fd6f0
        }
    } else {
        for (uint32_t i = 0; i < 5; ++i) {
            if (grounds[i]->m_bUsed_maybe == 0 && SecondaryShadowHotSpot(m_ui8Hero, i) != -1) {  // vt+0x178
                shadows->RegisterCaster(m_apUnkfbc[i], m_pKGLObject, grounds[i], 0, nullptr, 0);  // 0x001fb6f8
            }
        }
        UpdateShadowGroundPoint();  // 0x00365c00
        const CKShadowGround main = *reinterpret_cast<const CKShadowGround*>(&m_unk64);
        for (uint32_t i = 0; i < 5; ++i) {
            const int8_t spot = SecondaryShadowHotSpot(m_ui8Hero, i);  // vt+0x178
            if (spot == -1) continue;
            CVector3 at;
            static_cast<CSGHotSpot*>(m_apHotSpots[spot])->GetWorldPosition(&at);  // 0x000ce790
            grounds[i]->m_v3Position = {at.x, main.m_v3Position.y, at.z};
            grounds[i]->m_v3Normal = main.m_v3Normal;
            grounds[i]->m_fUnk18 = main.m_fUnk18;
        }
    }
    // The flight spark (+0x19dc's data under hot spot 0) while flying faster than +0xe34 (+0x12d0), placed at
    // +0xe28..+0xe30; otherwise let go.
    CKSrvFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
    if (IsFlyingMovementMode1() != 0 && m_unk12d0 > m_unke34) {  // ble
        CKSparkFxData* data = static_cast<CKSparkFxData*>(m_unk19dc);
        data->m_unk0c = nullptr;
        data->m_unk10 = m_apHotSpots[0];
        if (m_unk19e0 == nullptr) m_unk19e0 = fx->AcquireFx(data, this);  // the inline pool lookup
        if (m_unk19e0 != nullptr) PlaceSparkNode(m_unk19e0, HeroWordAsFloat(m_unke28), HeroWordAsFloat(m_unke2c), m_unke30);
    } else {
        ReleaseSpark(m_unk19e0, this);
    }
    // The air current's spark (+0x19e4's data under hot spot 0) while the game manager's record of the hero says it is
    // in an air current (+0xe11) with a pull (+0xdf8, not the null vector), flying faster than +0xe50: placed at
    // +0xe44..+0xe4c and pointed along the pull; the pad vibration +0x1164 for the tracked leader when it starts.
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    uint32_t* record = &manager->m_unkDF4[1 + static_cast<uint32_t>(m_ui8Hero) * 8u];  // +0xdf8 + hero x 0x20
    const uint8_t inCurrent = reinterpret_cast<const uint8_t*>(&record[6])[1];  // +0xe11, byte-addressed as AirCurrent
    auto pull = [record]() {
        CVector3 v;
        std::memcpy(&v.x, &record[0], 4);
        std::memcpy(&v.y, &record[1], 4);
        std::memcpy(&v.z, &record[2], 4);
        return v;
    };
    auto isNull = [](const CVector3& v) {  // 0x00c50d64 (TOC1 +0x283c)
        return v.x == kHeroZeroVector.x && kHeroZeroVector.y == v.y && kHeroZeroVector.z == v.z;
    };
    if (inCurrent != 0 && IsFlyingMovementMode1() != 0 && m_unk12d0 > m_unke50 && !isNull(pull())) {
        CKSparkFxData* data = static_cast<CKSparkFxData*>(m_unk19e4);
        data->m_unk0c = nullptr;
        data->m_unk10 = m_apHotSpots[0];
        if (m_unk19e8 == nullptr) m_unk19e8 = fx->AcquireFx(data, this);  // the inline pool lookup
        if (m_unk19e8 != nullptr) {
            CVector3 direction = pull();
            if (!isNull(direction)) {
                const float length = std::sqrt(
                    ppc::fmadds(direction.z, direction.z, ppc::fmadds(direction.x, direction.x, direction.y * direction.y)));  // Math_Sqrtf 0x10690
                if (length != 0.0f) {
                    const float inverse = 1.0f / length;
                    direction.z = direction.z * inverse;
                    direction.x = direction.x * inverse;
                    direction.y = direction.y * inverse;
                }
                CKSparkNodeFx* spark = static_cast<CKSparkNodeFx*>(m_unk19e8);
                if (PointSparkNodeAlong(spark, &direction) == 0) {
                    static const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};  // 0x00c50d40 (TOC1 +0x28c8)
                    static_cast<CSGMovable*>(spark->m_pNode)->SetOrientationFromAtUp(&direction, &kAxisY);  // 0x000d0918
                }
            }
            PlaceSparkNode(m_unk19e8, HeroWordAsFloat(m_unke44), m_unke48, m_unke4c);
        }
        if (m_unk1164 != nullptr && m_ui8Hero == m_ui8TrackedLeader && m_unk118e == 0) {
            CKVibrationData* vibration = static_cast<CKVibrationData*>(m_unk1164);
            vibration->m_pOwner = this;
            vibration->m_ui8OwnerIndex = 1;
            vibration->m_ui8NumPad = m_ui8Leader;
            static_cast<CKInput*>(g_pEngine->m_input)->PlayVibration(vibration);  // 0x00107d38
        }
        m_unk118e = 1;
    } else {
        ReleaseSpark(m_unk19e8, this);
        m_unk118e = 0;
    }
    if ((m_unkecc & 0x10u) != 0) {
        IKFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(static_cast<CKExplosionFxData*>(m_unk1b24), this);
        if (fx != nullptr) {
            CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(fx);
            CVector3 position;
            static_cast<CSGHotSpot*>(m_apHotSpots[18])->GetWorldPosition(&position);  // +0x48
            explosion->SetTranslation(&position, this);  // 0x001b66e8
            explosion->Trigger(this, 0);                  // 0x001b82a8
            explosion->ReleaseReservation(this);          // vt+0x54
        }
        m_unkecc &= 0xffffffefu;
    }
    CSGMovable* glow = static_cast<CSGMovable*>(m_unk1dc4);
    if ((static_cast<CSGLeaf*>(m_unk1dc4)->m_sgProperties & 4u) == 0) {
        CVector3 spot = {0.0f, 0.0f, 0.0f};
        if (m_ui8Hero == 0 || m_ui8Hero == 1) static_cast<CSGHotSpot*>(m_apHotSpots[5])->GetWorldPosition(&spot);  // +0x14
        const RwV3d& model = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame->modelling.pos;
        RwFrame* frame = glow->m_pRwFrame;
        const float lift = spot.y - m_unk550;
        frame->modelling.pos = {model.x, model.y + lift, model.z};
        frame->modelling.flags &= 0xfffdffffu;
        RwFrame_MarkDirty(frame);  // 0x00010698
    }
    if (m_unk19c8 == nullptr) m_unk19c8 = AcquirePartnerLinkBolt(this, m_unk19c4);
    if (m_unk19d0 == nullptr) m_unk19d0 = AcquirePartnerLinkBolt(this, m_unk19cc);
}

namespace {
// A trail / dust particle node started: shown (bit 9), emitting (bit 10), not pending (bit 19 cleared), the emission
// speed adjustment 0, its emitter's flags 0xa set.
void StartParticleNode(IKSerializable* object) {
    CParticlesNodeFx* node = static_cast<CParticlesNodeFx*>(object);
    if (node == nullptr) return;
    node->m_sgProperties = (node->m_sgProperties | 0x600u) & 0xfff7ffffu;
    node->m_fEmissionSpeedAdjustment = 0.0f;
    node->m_pRpPrtStdEmitter->flag |= 0xau;
}
uint8_t HeroAnimFinished(const CKHkS08Hero* hero, uint16_t animation) {  // 0x003013c8 CKHkS08Hero_IsAnimFinished (inlined copy)
    if (hero->m_i16CurAnimIndex != animation) return 0;
    return static_cast<uint8_t>((hero->m_ui32HeroFlags354 >> 15) & 1u);
}
uint8_t HeroInSpecialAnim(const CKHkS08Hero* hero) {  // 0x00301348 CKHkS08Hero_IsInSpecialAnim_maybe
    switch (static_cast<int16_t>(hero->m_i16CurAnimIndex)) {
    case 0x33: case 0x36: case 0x3a: case 0x3d: case 0x41: case 0x43: case 0x44: return 1;
    default: return 0;
    }
}
}  // namespace

// 0x00336598 CKHkS08Hero_UpdateTrailAndFootstepFx: the landing's dust (particles 10) and sound 0x5f; the two swing
// trails (+0x1ad4 / +0x1ad8) stopped when they end; the surface FX (CKS08GameManager_SpawnSurfaceFx, the surface from the
// climb or the ground's flags) at the feet on the animation marks (+0xedc bits 0..3), at the hero on +0xec4 bit 28 /
// +0xecc bit 3, under the hero (flying dives, slides, climbing); the dust effect and the pad vibration of animations
// 0x63 / 0x67; the particles 14 / 15 when the animations 0x29 / 0x59 end.
void CKHkS08Hero::UpdateTrailAndFootstepFx() {
    const bool leader = m_ui8Hero == m_ui8TrackedLeader;
    bool landing;
    if ((m_ui32HeroFlags358 & 0x10000u) != 0 && leader && (m_ui32HeroFlags354 & 0x1000u) == 0) {
        landing = (m_ui32HeroFlags364 & 0x40u) == 0 || (m_ui32HeroFlags364 & 0x20000000u) != 0;
    } else {
        landing = (m_ui32HeroFlags364 & 0x20000000u) != 0;
    }
    if (landing) {
        StartParticleNode(m_apParticles[10]);  // +0x28
        PlaySoundIfIdle(1.0f, 1.0f, 0x5f, 0, 0);  // 0x00333fc8
    }
    uint32_t* trails[2] = {&m_unk1ad4, &m_unk1ad8};
    const uint8_t active[2] = {m_unk1ad2, m_unk1ad3};
    for (int k = 0; k < 2; ++k) {
        if (*trails[k] == 0xffffffffu) continue;
        CParticlesNodeFx* node = static_cast<CParticlesNodeFx*>(m_apParticles[*trails[k]]);
        if (node == nullptr) continue;
        if (active[k] == 0) {
            if ((node->m_sgProperties & 0x400u) != 0) {
                node->m_sgProperties &= 0xfff7fbffu;
                node->m_pRpPrtStdEmitter->flag &= 0xfffffff7u;
                *trails[k] = 0xffffffffu;
            }
        } else {
            // The swing trail's particles at the middle of its trail's first ribbon's two hot spots (trail A: +0x5c[0],
            // B: +0x5c[2]); when not emitting yet they start with the element's emission (+0x1c70 / +0x1c84, or with a
            // combo of link code 2 +0x1c98 / +0x1cac).
            STrailNodeData* ribbon = static_cast<CTrailNodeFx*>(m_apTrails[k == 0 ? 0 : 2])->m_apTrailData[0];
            CVector3 a;
            CVector3 b;
            if (k == 0) {
                static_cast<CSGHotSpot*>(ribbon->m_pHotSpot1)->GetWorldPosition(&a);  // 0x000ce790
                static_cast<CSGHotSpot*>(ribbon->m_pHotSpot2)->GetWorldPosition(&b);
            } else {
                static_cast<CSGHotSpot*>(ribbon->m_pHotSpot1)->GetWorldPosition(&b);
                static_cast<CSGHotSpot*>(ribbon->m_pHotSpot2)->GetWorldPosition(&a);
            }
            const float kHalf = 0.5f;  // TOC1 +0x2810
            RwFrame* frame = node->m_pRwFrame;
            frame->modelling.pos.z = (a.z + b.z) * kHalf;
            frame->modelling.pos.y = (a.y + b.y) * kHalf;
            frame->modelling.pos.x = (a.x + b.x) * kHalf;
            frame->modelling.flags &= 0xfffdffffu;
            RwFrame_MarkDirty(frame);  // 0x00010698
            if ((node->m_sgProperties & 0x400u) == 0) {
                const int32_t* emit = &m_unk1c70;
                const int32_t* bias = &m_unk1c84;
                if (IsComboKindFlagSet() != 0 &&
                    static_cast<CKS08HeroCombo*>(m_pCurrentComboNode)->GetBlow()->GetLinkCode() == 2) {  // 0x002fc1b0
                    emit = &m_unk1c98;
                    bias = &m_unk1cac;
                }
                RpPrtStdEmitter* emitter = node->m_pRpPrtStdEmitter;
                RpPrtStdEmitterStandard* standard = reinterpret_cast<RpPrtStdEmitterStandard*>(
                    reinterpret_cast<uint8_t*>(emitter) + emitter->emtClass->propTab->propOffset[1]);
                standard->emtPrtEmit = emit[m_unk1cc4];
                node->m_ui8NbEmitParticlesPerPoint = static_cast<uint8_t>(emit[m_unk1cc4]);
                emitter = node->m_pRpPrtStdEmitter;
                standard = reinterpret_cast<RpPrtStdEmitterStandard*>(reinterpret_cast<uint8_t*>(emitter) +
                                                                      emitter->emtClass->propTab->propOffset[1]);
                standard->emtPrtEmitBias = bias[m_unk1cc4];
                node->m_sgProperties = (node->m_sgProperties | 0x400u) & ~0x80000u;
                node->m_fEmissionSpeedAdjustment = 0.0f;
                node->m_pRpPrtStdEmitter->flag |= rpPRTSTDEMITTERFLAGACTIVE | rpPRTSTDEMITTERFLAGEMIT;  // 0xa
            }
        }
    }
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
    const float volume = leader ? 1.0f : group->m_unk204;  // TOC1 +0x2854
    uint32_t surface = 4;
    if (IsClimbingMovementMode2() == 0) {
        const ICollisionMesh* ground;
        if (m_ui8GroundAnimState == 0xb && static_cast<int16_t>(m_i16CurAnimIndex) != 0x27 && static_cast<int16_t>(m_i16CurAnimIndex) != 0x26) {
            ground = static_cast<const ICollisionMesh*>(m_gcContact11FC.m_pGround);
        } else {
            ground = static_cast<const ICollisionMesh*>(GetGroundInfo());  // 0x00361b68
        }
        surface = 0;
        if (ground != nullptr) {
            if (((ground->m_ba16EngineFlags >> 1) & 1u) != 0) {
                surface = 3;
            } else {
                const uint16_t f = ground->m_ui16PropertiesFlags;
                if ((f & 0x800u) != 0) surface = 0;
                else if ((f & 0x1000u) != 0) surface = 1;
                else if ((f & 0x2000u) != 0) surface = 2;
            }
        }
    }
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    CVector3 feet[4];
    const uint8_t spots[4] = {2, 3, 6, 7};
    for (int k = 0; k < 4; ++k) static_cast<CSGHotSpot*>(GetHotSpot(spots[k]))->GetWorldPosition(&feet[k]);  // 0x00361b70
    auto spawn = [&](uint32_t mode, const float* at) { manager->SpawnSurfaceFx(volume, this, surface, mode, at); };
    if ((m_ui32HeroFlags354 & 1u) == 0) {
        for (int k = 0; k < 4; ++k) {
            if ((m_unkedc & (1u << k)) != 0) spawn(0, &feet[k].x);
        }
    }
    if ((m_unkec4 & 0x10000000u) != 0) spawn(1, &m_unk54c);
    if ((m_unkecc & 8u) != 0) spawn(1, &m_unk54c);
    const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(GetGroundInfo());
    uint32_t soft = 1;
    if (ground != nullptr && (ground->m_ui16PropertiesFlags & 0x200u) != 0) soft = (ground->m_ba16EngineFlags >> 1) & 1u;
    if (IsFlyingMovementMode1() != 0 && (m_unkedc & 0x100u) != 0 && HeroInSpecialAnim(this) != 0 &&
        m_gcCurDatasInOut.m_fdH < m_unke3c && soft != 0) {
        spawn(2, &m_unk570);
    }
    if (ground != nullptr && m_unk115c <= 0.0f && (m_ui32HeroFlags354 & 4u) != 0 && (ground->m_ba16EngineFlags & 2u) != 0 &&
        (ground->m_ui16PropertiesFlags & 0x200u) != 0) {
        m_unk115c = 0.5f;  // TOC1 +0x2810
        spawn(1, &m_unk570);
    }
    if (m_unk16f9 != 0 && ShouldStayClimbing() != 0) spawn(1, &m_unk570);
    if (static_cast<int16_t>(m_i16CurAnimIndex) == 0x2a) {
        if ((m_unkedc & 1u) != 0) spawn(0, &feet[0].x);
        if ((m_unkedc & 2u) != 0) spawn(0, &feet[1].x);
    }
    if (m_ui8GroundAnimState == 0xc && m_unk1511 == 0) {
        for (int k = 0; k < 4; ++k) {
            if ((m_unkedc & (1u << k)) != 0) spawn(1, &feet[k].x);
        }
    }
    const int16_t animation = static_cast<int16_t>(m_i16CurAnimIndex);
    bool vibrate = false;
    if (animation == 0x63 || animation == 0x67) {
        if (m_unk19f4 == nullptr) {
            CKParticlesEffectFxData* dust = static_cast<CKParticlesEffectFxData*>(m_unk19f0);
            dust->m_pAttachHotSpot = m_apHotSpots[0];
            dust->m_pAttachOwner = nullptr;
            m_unk19f4 = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(dust, this);
        }
        vibrate = true;
    } else if (m_unk19f4 != nullptr) {
        StopOwnedParticleEffect(static_cast<IKFx*>(m_unk19f4), this);  // 0x001cdde8
        static_cast<IKFx*>(m_unk19f4)->ReleaseReservation(this);       // vt+0x54
        m_unk19f4 = nullptr;
    }
    if (vibrate && m_unk1168 != nullptr && leader) {
        CKVibrationData* data = static_cast<CKVibrationData*>(m_unk1168);
        data->m_pOwner = this;
        data->m_ui8OwnerIndex = 0;
        data->m_ui8NumPad = m_ui8Leader;
        static_cast<CKInput*>(g_pEngine->m_input)->PlayVibration(data);  // 0x00107d38
    }
    if (HeroAnimFinished(this, 0x29) != 0 || HeroAnimFinished(this, 0x59) != 0 || (m_unkecc & 0x2000000u) != 0) {
        if (m_ui8Hero == 0) {
            StartParticleNode(m_apParticles[14]);  // +0x38
            StartParticleNode(m_apParticles[15]);  // +0x3c
        } else if (m_apParticles[15] != nullptr) {
            StartParticleNode(m_apParticles[14]);
            StartParticleNode(m_apParticles[15]);
        }
    }
}

// 0x0033bbe0 CKHkS08Hero_SpawnFuryReleaseFx_maybe: the release explosion (+0x1dd8; the inlined pooled lookup,
// CKSrvFx::AcquireFx) at hot spot 5, dealing the stun damage +0x1ddc as the hero's (category 3, flags 0x28); the fury
// node's movement stopped and the node hidden in its layer (SceneNode_SetVisibleInLayer 1, 0, 0); the charge's mesh pop
// (+0x1df4) let go (vt+0x58).
void CKHkS08Hero::SpawnFuryReleaseFx() {
    IKFxData* data = static_cast<IKFxData*>(m_unk1dd8);
    CSGHotSpot* spot = static_cast<CSGHotSpot*>(m_apHotSpots[5]);
    CKSrvFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);  // TOC +0x282c -> +0x60
    CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(fx->AcquireFx(data, this));
    if (explosion != nullptr) {
        CVector3 position;
        spot->GetWorldPosition(&position);              // 0x000ce790
        explosion->SetTranslation(&position, this);     // 0x001b66e8
        explosion->SetDamageOwner(this, this);          // 0x001b6340
        explosion->SetDamageCategory(3, this);          // 0x001b6318
        explosion->SetDamageFlags(0x28, this);          // 0x001b62f0
        explosion->SetDamage(m_unk1ddc, this);          // 0x001b62c8
        explosion->Trigger(this, 0);                    // 0x001b82a8
        explosion->ReleaseReservation(this);            // vt+0x54
    }
    static_cast<CKMoveCpntUpdater*>(m_unk1de8)->Stop();  // 0x0024dc60
    SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_unk1de0), 1, 0, 0);  // TocBridge 0x0098f340 -> 0x005832a8
    IKFx* pop = static_cast<IKFx*>(m_unk1df4);
    if (pop != nullptr) {
        pop->StopAndRelease(this);  // vt+0x58
        m_unk1df4 = nullptr;
    }
}

// 0x0033bf58 CKHkS08Hero_SpawnFuryChargeFx_maybe: the charge explosion (+0x1dd4) at hot spot 5; the fury node (+0x1de0)
// started: its movement started, shown (+0x10 bit 2 cleared), its geometries faded by its curve at 0, moved under the
// hero's node, set to the identity and moved by a sample. Without a running mesh pop (+0x1df4), one of +0x1df0 (its
// attach references cleared) placed at the hero with a random yaw (one Rand_Int draw) and turned on.
void CKHkS08Hero::SpawnFuryChargeFx() {
    IKFxData* data = static_cast<IKFxData*>(m_unk1dd4);
    CSGHotSpot* spot = static_cast<CSGHotSpot*>(m_apHotSpots[5]);
    CKSrvFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
    // BUG(original): the sample ApplyToNode reads below is the stack slot the hot spot's position goes to here (channels 0-2
    // after the explosion started; the other seven, and all ten without the explosion, whatever the stack held). DOTD: 0
    // there; the next fury frame (ActFuryCoop) sets the node from the identity again.
    float sample[10] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(fx->AcquireFx(data, this));
    if (explosion != nullptr) {
        CVector3 position;
        spot->GetWorldPosition(&position);
        sample[0] = position.x;
        sample[1] = position.y;
        sample[2] = position.z;
        explosion->SetTranslation(&position, this);
        explosion->Trigger(this, 0);
        explosion->ReleaseReservation(this);
    }
    if (m_unk1de0 != nullptr) {
        CKMoveCpntUpdater* updater = static_cast<CKMoveCpntUpdater*>(m_unk1de8);
        updater->Start();  // 0x0024dc98
        CNode* node = static_cast<CNode*>(m_unk1de0);
        node->m_sgProperties &= ~4u;
        SetNodeAlphaFromCurve(node, m_unk1dec, 0.0f);  // TOC +0x2814
        if (node->m_pParent != nullptr) node->m_pParent->RemoveChild(node);  // vt+0x78
        static_cast<CSGBranch*>(m_pKGLObject)->AddChild(node);  // vt+0x70
        node->SetIdentity();  // 0x000d08f0
        updater->ApplyToNode(sample, node);  // 0x0024d9c0
    }
    if (m_unk1df4 != nullptr) return;
    CKMeshPopFxData* popData = static_cast<CKMeshPopFxData*>(m_unk1df0);
    popData->m_unk08 = nullptr;
    popData->m_unk0c = nullptr;
    CKMeshPopNodeFx* pop = static_cast<CKMeshPopNodeFx*>(fx->AcquireFx(popData, this));
    m_unk1df4 = pop;
    if (pop == nullptr) return;
    static const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};  // TOC +0x28c8 -> 0x00c50d40
    pop->PlaceWithRandomYaw(this, &kAxisY, reinterpret_cast<const CVector3*>(&m_unk54c));  // 0x001c9d90
    pop->SetActive(this, 1);  // 0x001cb568
}

// 0x0033c688 CKHkS08Hero_SpawnShockwave: the grab's shockwave at `position` (kind 0: the data +0x1b1c coloured by the
// element's +0x1c48, kind 1: +0x1b20 and +0x1c5c), its damage sphere the hero's (category 3, flags 0x28, the blow's damage).
void CKHkS08Hero::SpawnShockwave(uint8_t kind, const CVector3* position) {
    IKSerializable* data;
    uint32_t color;
    if (kind == 0) {
        color = (&m_unk1c48)[m_unk1cc4];  // the element's colour (+0x1c48)
        data = m_unk1b1c;
    } else if (kind == 1) {
        color = (&m_unk1c5c)[m_unk1cc4];  // (+0x1c5c)
        data = m_unk1b20;
    } else {
        return;
    }
    if (data == nullptr) return;
    std::memcpy(static_cast<CKExplosionFxData*>(data)->m_cColor, &color, sizeof color);  // the data's colour (+0x38)
    IKFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(static_cast<CKExplosionFxData*>(data), this);
    if (fx == nullptr) return;
    CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(fx);
    explosion->SetTranslation(position, this);   // 0x001b66e8
    explosion->SetDamageOwner(this, this);        // 0x001b6340
    explosion->SetDamageCategory(3, this);        // 0x001b6318
    explosion->SetDamageFlags(0x28, this);        // 0x001b62f0
    CKS08HeroCombo* combo = static_cast<CKS08HeroCombo*>(m_pCurrentComboNode);
    if (combo->GetBlow() != nullptr) {
        explosion->SetDamage(reinterpret_cast<IKSerializable*>(combo->GetBlow()->m_pDamage), this);  // vt+0xb0, 0x001b62c8
    }
    explosion->Trigger(this, 0);          // 0x001b82a8
    explosion->ReleaseReservation(this);  // vt+0x54
}

// 0x00333688 ComputeSoundPitchFromAnimSpeed_maybe: 0.5 + speed / 2, kept in [0.5, 2] (TOC +0x2810 / +0x2818).
float CKHkS08Hero::ComputeSoundPitchFromAnimSpeed(float speed) {
    const float pitch = ppc::fmadds(speed, 0.5f, 0.5f);
    if (pitch < 0.5f) return 0.5f;
    if (pitch <= 2.0f) return pitch;
    return 2.0f;
}

// 0x00334450 CKHkS08Hero_SpawnHitExplosionFx: one explosion of the hero's hit FX (+0x1ae4) from the FX pool set off
// at the hit point (+0x1b44).
void CKHkS08Hero::SpawnHitExplosionFx() {
    IKFxData* data = static_cast<IKFxData*>(m_unk1ae4);
    IKFx* effect = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(data, this);  // TOC +0x282c
    if (effect == nullptr) return;
    CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(effect);
    const CVector3 at{m_unk1b44, m_unk1b48, m_unk1b4c};
    explosion->SetTranslation(&at, this);  // 0x001b66e8
    explosion->Trigger(this, 0);           // 0x001b82a8
    explosion->ReleaseReservation(this);   // vt+0x54
}

namespace {
// 0x00b01040 (TOC +0x28b4): per dragon the swing trail's particle index by element (+0x1cc4).
constexpr int8_t kSwingTrailParticle0[5] = {0, 2, 4, 6, 8};
constexpr int8_t kSwingTrailParticle2[8] = {0, 0, 1, 1, 2, 2, 3, 3};
int8_t SwingTrailParticle(uint8_t dragon, uint32_t element) {
    return dragon == 2 ? kSwingTrailParticle2[element] : kSwingTrailParticle0[element];
}
}  // namespace

// 0x00335158 CKHkS08Hero_UpdateSwingTrails. The swing trails on and off with their ribbons' colours (the element's
// +0x1c20 / +0x1c34 entries written into the trails' geometry under RpGeometryLock). Then, for dragons 0 and 1 (the same
// code twice in the original), the flight trails +0x5c[6..9] (ribbon 0; on in flight while +0x12d0 > +0xe18, off out of
// flight or once +0x12d0 < +0xe18) and the animation trails [10..12] (on with animation 0x40, which also starts the blur
// FX +0xee8; [10] off outside 0x40 unless +0xec8 bit 1 or animation 0x55; [11] / [12] on with bit 1 or 0x55, off
// otherwise except in 0x40). A trail's state is its first ribbon's bit 0.
void CKHkS08Hero::UpdateSwingTrails() {
    auto trail = [this](int k) { return static_cast<CTrailNodeFx*>(m_apTrails[k]); };
    // The element's colour (the 4 bytes as stored) into every ribbon of `node` (+0x24) and into its geometry's pre-lit
    // colours (RpGeometryLock 8): each ribbon's two halves of its vertices, a byte counter over the half.
    auto paint = [](CTrailNodeFx* node, uint32_t colour) {
        CGeometry* geometry = static_cast<CGeometry*>(node->m_lGeometryList);
        RpGeometryLock(geometry->m_pRpAtomic->geometry, 8);  // TocBridge 0x98ec90
        RwRGBA* colours = geometry->m_pRpAtomic->geometry->preLitLum;
        for (uint32_t r = 0; r < node->m_ui32NbTrail; ++r) {
            STrailNodeData* ribbon = node->m_apTrailData[r];
            std::memcpy(ribbon->m_cColor, &colour, 4);
            for (uint32_t k = 0; (ribbon->m_ui32NbLineVertex >> 1) > k; k = (k + 1u) & 0xffu) {
                std::memcpy(&colours[r * ribbon->m_ui32NbLineVertex + k], &colour, 4);
                std::memcpy(&colours[r * ribbon->m_ui32NbLineVertex + k + (ribbon->m_ui32NbLineVertex >> 1)], &colour, 4);
            }
        }
        geometry->UnlockGeometry();  // 0x00088530
    };
    // One swing trail (its two ribbon nodes `first` / `first + 1`) on or off.
    auto setTrail = [&](int first, uint8_t on) {
        const uint32_t count = trail(first)->m_ui32NbTrail;
        if (trail(first + 1)->m_ui32NbTrail == count) {
            if (on == 0) {
                for (uint32_t i = 0; i < count; ++i) {
                    trail(first)->SetRibbonActive(i & 0xffu, 0, 0);  // 0x009bdfb8
                    trail(first + 1)->SetRibbonActive(i & 0xffu, 0, 0);
                }
                return;
            }
            for (uint32_t i = 0; i < count; ++i) trail(first)->SetRibbonActive(i & 0xffu, 1, 0);
            paint(trail(first), (&m_unk1c20)[m_unk1cc4]);
            if (IsComboKindFlagSet() != 0 &&
                static_cast<CKS08HeroCombo*>(m_pCurrentComboNode)->GetBlow()->GetLinkCode() == 2) {  // 0x002fc1b0, vt+0x54 / +0x58
                for (uint32_t i = 0; i < count; ++i) trail(first + 1)->SetRibbonActive(i & 0xffu, 1, 0);
                paint(trail(first + 1), (&m_unk1c34)[m_unk1cc4]);
            }
            return;
        }
        for (uint32_t i = 0; i < count; ++i) trail(first)->SetRibbonActive(i & 0xffu, on, 0);
    };
    if ((m_unkedc & 0x20u) == 0) {
        if (m_unk1ad2 != 0) {
            setTrail(0, 0);
            m_unk1ad2 = 0;
        }
    } else if (m_unk1ad2 == 0) {
        setTrail(0, 1);
        m_unk1ad4 = m_unk1ad8 == 0xffffffffu ? static_cast<uint32_t>(static_cast<int32_t>(SwingTrailParticle(m_ui8Hero, m_unk1cc4)))
                                             : m_unk1ad8 - 1u;
        m_unk1ad2 = 1;
    }
    if ((m_unkedc & 0x40u) == 0) {
        if (m_unk1ad3 != 0) {
            setTrail(2, 0);
            m_unk1ad3 = 0;
        }
    } else if (m_unk1ad3 == 0) {
        setTrail(2, 1);
        m_unk1ad8 = m_unk1ad4 == 0xffffffffu ? static_cast<uint32_t>(static_cast<int32_t>(SwingTrailParticle(m_ui8Hero, m_unk1cc4)) + 1)
                                             : m_unk1ad4 + 1u;
        m_unk1ad3 = 1;
    }
    if (m_ui8Hero != 0 && m_ui8Hero != 1) return;
    auto on = [&](int k) { return (trail(k)->m_apTrailData[0]->m_ba8Properties & 1u) != 0; };
    auto set = [&](int k, uint32_t active) { trail(k)->SetRibbonActive(0, active, 0); };  // 0x009bdfb8
    if (GetMovementMode() == 1) {  // 0x003401b8
        if (!on(6)) {
            if (m_unk12d0 > m_unke18) {  // fcmpu, ble skips (NaN stays off)
                for (int k = 6; k <= 9; ++k) set(k, 1);
            }
        } else if (m_unk12d0 < m_unke18) {  // bge skips (NaN stays on)
            for (int k = 6; k <= 9; ++k) set(k, 0);
        }
    } else if (on(6)) {
        for (int k = 6; k <= 9; ++k) set(k, 0);
    }
    const int16_t anim = static_cast<int16_t>(m_i16CurAnimIndex);
    if (anim == 0x40) {
        if (!on(10)) {
            for (int k = 10; k <= 12; ++k) set(k, 1);
            // The FX service's start of the blur data (CKSrvFx::StartEffect inlined: the pooled effect of its class and
            // type, or the unique effect's SetDataAndOwner), owned by the hero.
            static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->StartEffect(static_cast<IKFxData*>(m_unkee8), this);
        }
    } else if ((m_unkec8 & 2u) == 0 && anim != 0x55 && on(10)) {
        for (int k = 10; k <= 12; ++k) set(k, 0);
    }
    if ((m_unkec8 & 2u) != 0 || static_cast<int16_t>(m_i16CurAnimIndex) == 0x55) {
        if (!on(11)) set(11, 1);
        if (!on(12)) set(12, 1);
    } else if (static_cast<int16_t>(m_i16CurAnimIndex) != 0x40) {
        if (on(11)) set(11, 0);
        if (on(12)) set(12, 0);
    }
}

// 0x00338130 CKHkS08Hero_SetSwitchFeedbackFxActive_maybe. The acquire is CKSrvFx_AcquireFx inlined, after the data's bytes
// +0x5c / +0x5e / +0x5f were set (on the screen, its render stage, projected).
void CKHkS08Hero::SetSwitchFeedbackFxActive(uint8_t on) {
    if (on == 0) {
        if (m_unk1a08 == nullptr) return;
        static_cast<CKTargetCursorNodeFx*>(m_unk1a08)->StopForOwnerWithFadeOut(this, 0);  // 0x001d7190
        m_unk1a08 = nullptr;
        return;
    }
    if (m_unk1a08 == nullptr) {
        CKTargetCursorFxData* data = static_cast<CKTargetCursorFxData*>(m_unk1a04);
        if (data != nullptr) {
            data->m_unk5f = 1;
            data->m_unk5e = 1;
            data->m_unk5c = 1;
        }
        m_unk1a08 = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(data, this);
        if (m_unk1a08 == nullptr) return;
    }
    const CVector3 position = {m_unk54c, m_unk550, m_unk554};
    static_cast<CKTargetCursorNodeFx*>(m_unk1a08)->SetPositionForOwner(this, &position);  // 0x001d5ec8
}

// 0x00334138 StaticInitAndDestruction_334138: two file statics (0x00ceae64, 0x00ceae68) set to -1.0f. Nothing in the game
// reads them (their only references are the initialiser's TOC entries).
namespace {
[[maybe_unused]] float s_unkceae64 = -1.0f;
[[maybe_unused]] float s_unkceae68 = -1.0f;
}  // namespace
