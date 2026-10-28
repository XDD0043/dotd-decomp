// SoundVoice.cpp - reconstructed original translation unit 0x121be0-0x1225b0 (GAME_TOC1, main_toc1), 14 functions, 11 live.
// Primary owner: SoundVoice (not a registered class)
// Other owners: SoundChannel (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x121be0  SoundVoice_ApplyVolume_maybe  [dead]
//   [x] 0x121cc8  SoundVoice_BindInstance_maybe
//   [x] 0x121d00  SoundVoice_GetPlayPositionSeconds_maybe
//   [x] 0x121d80  SoundVoice_IsPlaying_maybe
//   [x] 0x121dc8  SoundVoice_SetPlayPositionSeconds_maybe
//   [x] 0x121e58  SoundChannel_ResumeVoice_maybe
//   [x] 0x121e90  SoundChannel_PauseVoice_maybe
//   [x] 0x121ec8  SoundVoice_Construct_maybe
//   [ ] 0x121f30  SoundVoice_Construct_2_maybe  [dead]
//   [x] 0x121f98  SoundVoice_Release_maybe
//   [x] 0x122090  SoundVoice_Destroy_maybe
//   [ ] 0x122118  SoundVoice_Destroy_2_maybe  [dead]
//   [x] 0x1221a0  SoundVoice_Start_maybe
//   [x] 0x1222e8  SoundVoice_ApplyParameters_maybe
#include "k2000/sound/SoundVoice.h"

#include "crt/ppc_ops.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/logic/sound/CKWave.h"
#include "k2000/managers/CKSoundManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/sound/CKSoundOutput.h"
#include "k2000/sound/CKSoundStreamManager.h"
#include "k2000/sound/SoundInstance.h"
#include "platform/audio/rwa.h"

namespace {

const float kZeroVector[3] = {0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC -0x4378)
constexpr float kZero = 0.0f;                      // TOC -0x437c
constexpr float kOne = 1.0f;                       // TOC -0x4380

CKWave* WaveOf(SoundInstance* instance) { return instance->m_pSound->GetSample(); }
float SampleRate(SoundInstance* instance) {
    return static_cast<float>(static_cast<double>(WaveOf(instance)->m_ui16SampleRate));
}

// 0x0001e2e0 CKGameLoop_IsRequestedLevelWithGmFlag294_maybe (misc/CKGameLoop.cpp, family gm; not ported):
// 1 while a requested level loads with the game manager's +0x294 flag (and two globals) set: the sounds
// are muted then. STUB(gm): 0 (the front end requests no level; C2 needs the port).
uint32_t CKGameLoop_IsRequestedLevelWithGmFlag294() { return 0; }

}  // namespace

// 0x00121ec8 SoundVoice_Construct_maybe
SoundVoice::SoundVoice() {
    m_pInstance = nullptr;
    m_unk00 = 0;
    m_pRwaVoice = RwaVoice_Create(static_cast<RwaOutput*>(g_pEngine->m_soundManager->m_pOutput->m_rwaOutput));
}

// 0x00122090 SoundVoice_Destroy_maybe
void SoundVoice::Destroy() {
    if (m_pInstance != nullptr) Release();
    RwaVoice_Destroy(m_pRwaVoice);
    m_pInstance = nullptr;
}

// 0x00121cc8 SoundVoice_BindInstance_maybe
void SoundVoice::BindInstance(SoundInstance* instance) {
    m_pInstance = instance;
    instance->SetVoice(this);
}

// 0x00121d00 SoundVoice_GetPlayPositionSeconds_maybe: RWA's sample position / the wave's sample rate.
float SoundVoice::GetPlayPositionSeconds() {
    const uint32_t samples = RwaVoice_GetPlayPosition(m_pRwaVoice);
    return static_cast<float>(static_cast<double>(samples)) / SampleRate(m_pInstance);
}

// 0x00121d80 SoundVoice_IsPlaying_maybe
uint8_t SoundVoice::IsPlaying() { return RwaVoice_IsPlaying(m_pRwaVoice) == 1 ? 1 : 0; }

// 0x00121dc8 SoundVoice_SetPlayPositionSeconds_maybe
void SoundVoice::SetPlayPositionSeconds(float seconds) {
    const double rate = static_cast<double>(WaveOf(m_pInstance)->m_ui16SampleRate);
    RwaVoice_SetPlayPosition(m_pRwaVoice, static_cast<uint32_t>(ppc::fctidz(rate * static_cast<double>(seconds))));
    m_pInstance->m_fRemaining = 0.0f;
}

// 0x00121e58 SoundChannel_ResumeVoice_maybe
void SoundVoice::Resume() {
    if (m_pInstance != nullptr) RwaVoice_SetPlaying(m_pRwaVoice, 1);
}

// 0x00121e90 SoundChannel_PauseVoice_maybe
void SoundVoice::Pause() {
    if (m_pInstance != nullptr) RwaVoice_SetPlaying(m_pRwaVoice, 0);
}

// 0x00121f98 SoundVoice_Release_maybe: stopped, its wave removed, the instance keeps the time it had left.
void SoundVoice::Release() {
    RwaVoice_SetPlaying(m_pRwaVoice, 0);
    const float length = WaveOf(m_pInstance)->m_fLength;
    const uint32_t samples = RwaVoice_GetPlayPosition(m_pRwaVoice);
    const float position = static_cast<float>(static_cast<double>(samples)) / SampleRate(m_pInstance);
    RwaVoice_SetWave(m_pRwaVoice, nullptr);
    m_pInstance->OnVoiceReleased(length - position);
    m_pInstance = nullptr;
}

// 0x001221a0 SoundVoice_Start_maybe. BUG(original): the start position is set, then set to 0 again
// before the voice plays, so every voice starts at the wave's beginning (RWA ignores the offset anyway).
void SoundVoice::Start(float startSeconds) {
    CKSound* sound = m_pInstance->m_pSound;
    RwaVoice_SetWave(m_pRwaVoice, static_cast<RwaWave*>(sound->GetSample()->m_pRwaWave));
    if (startSeconds != kZero) {
        const float rate = SampleRate(m_pInstance);
        RwaVoice_SetPlayPosition(m_pRwaVoice, static_cast<uint32_t>(ppc::fctidz(startSeconds * rate)));
        m_pInstance->m_fRemaining = kZero;
    }
    int32_t loop = 0;
    if ((sound->m_SoundFlags & CKSound::kFlagLoop) != 0) loop = sound->m_fPauseTime == kZero ? 1 : 0;
    RwaVoice_SetLoop(m_pRwaVoice, loop);
    RwaVoice_SetPlayPosition(m_pRwaVoice, 0);
    RwaVoice_SetVelocity(m_pRwaVoice, kZeroVector);  // Ghidra: TocBridge_RwaVoice_SetPosition_maybe
    RwaVoice_SetPlaying(m_pRwaVoice, 1);
}

// 0x001222e8 SoundVoice_ApplyParameters_maybe: the instance's volume (x the effects or music volumes),
// position, velocity, loop, pitch and distances to RWA. 0 without an instance or while it is paused.
int32_t SoundVoice::ApplyParameters() {
    SoundInstance* instance = m_pInstance;
    if (instance == nullptr || (instance->m_flags & SoundInstance::kFlagPaused) != 0) return 0;
    CKSound* sound = instance->m_pSound;
    if (instance->m_fRemaining != kZero) {
        const float played = sound->GetSample()->m_fLength - instance->m_fRemaining;
        const float rate = SampleRate(m_pInstance);
        RwaVoice_SetPlayPosition(m_pRwaVoice, static_cast<uint32_t>(ppc::fctidz(played * rate)));
        m_pInstance->m_fRemaining = kZero;
        instance = m_pInstance;
    }
    CKSoundManager* manager = g_pEngine->m_soundManager;
    float volume;
    if ((instance->m_pSound->m_SoundFlags & CKSound::kFlagMusic) == 0) {
        // the sound-effects volume: the manager's volume x GAME.KP3's x 00GLC's third values
        volume = (manager->m_fSoundsVolume * manager->m_unk34[2]) * manager->m_unk28[2];
    } else {
        const float music = manager->m_pSoundStreamManager->GetMusicCurrentVolume();
        volume = (music * manager->m_unk34[0]) * manager->m_unk28[0];
    }
    if ((CKGameLoop_IsRequestedLevelWithGmFlag294() & 0xff) != 0) volume = kZero;
    float gain = volume * m_pInstance->m_volumeRamp[2];
    if (gain > kOne) gain = kOne;
    RwaVoice_SetVolume(gain, m_pRwaVoice);
    RwaVoice_SetPosition(m_pRwaVoice, &m_pInstance->m_position.x);  // Ghidra: TocBridge_RwaVoice_SetVelocityOrDirection_maybe
    RwaVoice_SetVelocity(m_pRwaVoice, &m_pInstance->m_velocity.x);  // Ghidra: TocBridge_RwaVoice_SetPosition_maybe
    int32_t loop = 0;
    if ((sound->m_SoundFlags & CKSound::kFlagLoop) != 0) loop = sound->m_fPauseTime == kZero ? 1 : 0;
    if (RwaVoice_GetLoop(m_pRwaVoice) != loop) RwaVoice_SetLoop(m_pRwaVoice, loop);
    if (RwaVoice_GetPitch(m_pRwaVoice) != m_pInstance->m_fPlaybackRate) RwaVoice_SetPitch(m_pInstance->m_fPlaybackRate, m_pRwaVoice);
    RwaVoice_SetMinDistance(sound->m_fDistanceMin, m_pRwaVoice);
    RwaVoice_SetMaxDistance(sound->m_fDistanceMax, m_pRwaVoice);
    return 1;
}
