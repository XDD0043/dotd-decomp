// Reconstructed original translation unit: 0x333618-0x33ca98 (GAME_TOC1, main_toc1), 30 functions, 28 live.
// Primary class: CKHkS08Hero  key 0x25c2  category Hook  size 0x1e00  vtable 0xb22c98
// Other owners: Math (1), ComputeSoundPitchFromAnimSpeed (1), Vec3 (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x333618  Math_RemapClamped
//   [ ] 0x333688  ComputeSoundPitchFromAnimSpeed_maybe
//   [ ] 0x3336b8  KStub_Nop_3336b8  [dead]
//   [x] 0x3336c0  CKHkS08Hero_GetFootstepSurfaceType
//   [ ] 0x3337c0  CKHkS08Hero_UpdateSecondaryShadowPositions_maybe
//   [ ] 0x333b00  CKHkS08Hero_SetSecondaryShadowsActive
//   [ ] 0x333ea8  FUN_00333ea8  [dead]
//   [x] 0x333fc8  CKHkS08Hero_PlaySoundIfIdle
//   [x] 0x334108  CKHkS08Hero_PlaySoundIfIdleThunk
//   [ ] 0x334110  CKHkS08Hero_PlayFootstepSoundsThunk
//   [ ] 0x334138  StaticInitAndDestruction_334138
//   [ ] 0x334168  _GLOBAL__D_334168
//   [ ] 0x334178  _GLOBAL__I_334178
//   [x] 0x334188  CKHkS08Hero_PlaySound_maybe
//   [ ] 0x3342c0  Vec3_LerpByRangeClamped_maybe
//   [x] 0x3343d8  CKHkS08Hero_StopSound
//   [ ] 0x334450  CKHkS08Hero_SpawnHitExplosionFx
//   [ ] 0x3346d8  CKHkS08Hero_UpdateModelFade_maybe
//   [ ] 0x3349a8  CKHkS08Hero_ReleaseOwnedFx
//   [x] 0x334e20  CKHkS08Hero_DisableSwingTrails_maybe
//   [ ] 0x335158  CKHkS08Hero_UpdateSwingTrails
//   [ ] 0x336598  CKHkS08Hero_UpdateTrailAndFootstepFx
//   [ ] 0x337898  CKHkS08Hero_UpdatePartnerLinkBolt_maybe
//   [ ] 0x338130  CKHkS08Hero_SetSwitchFeedbackFxActive_maybe
//   [ ] 0x338458  CKHkS08Hero_UpdateTriggeredExplosionFxAndVibration_maybe
//   [ ] 0x339050  CKHkS08Hero_UpdatePartnerLinkFx_maybe
//   [ ] 0x33a050  CKHkS08Hero_UpdateShadowsAndFlightFx_maybe
//   [ ] 0x33bbe0  CKHkS08Hero_SpawnFuryReleaseFx_maybe
//   [ ] 0x33bf58  CKHkS08Hero_SpawnFuryChargeFx_maybe
//   [ ] 0x33c688  CKHkS08Hero_SpawnShockwave
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/services/ICollisionMesh.h"
#include "Renderware/rpprtstd/RpPrtStd.h"
#include "k2000/core/Stub.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/scenegraph/CTrailNodeFx.h"
#include "k2000/system/CTimeManager.h"

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
    // The attack effect objects: each one is told about the hero (vt+0x58), then forgotten.
    IKSerializable** effects[6] = {&m_unk1dcc, &m_unk1cf4, &m_unk19b8, &m_unk19c0, &m_unk19c8, &m_unk19d0};
    for (IKSerializable** effect : effects) {
        if (*effect != nullptr) {
            // STUB(C2.7, moved from C2.6: combat): (*effect)->vt+0x58(hero): the effect's own release (not reached before the first attack).
            DOTD_STUB_ONCE("CKHkS08Hero::DisableSwingTrails: effect object release");
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
    const int16_t animation = static_cast<int16_t>(m_unk160);
    if (m_unk1960 == 0xb && animation != 0x27 && animation != 0x26) {
        ground = static_cast<const ICollisionMesh*>(m_unk11fc.m_pGround);
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
