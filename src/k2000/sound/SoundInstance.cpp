// SoundInstance.cpp - reconstructed original translation unit 0x11f6c8-0x121be0 (GAME_TOC1, main_toc1), 26 functions, 22 live.
// Primary owner: SoundInstance (not a registered class)
// Other owners: SoundChannel (3), SoundStream (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x11f6c8  SoundInstance_OnVoiceReleased_maybe
//   [x] 0x11f6d8  SoundInstance_SetVoice_maybe
//   [x] 0x11f6e0  SoundInstance_IsNotDelayState_maybe
//   [ ] 0x11f6f8  SoundInstance_SetFadeValue_maybe  [dead]
//   [x] 0x11f750  SoundInstance_UpdatePlaybackRate_maybe
//   [x] 0x11f7a8  SoundInstance_UpdateRemainingTime_maybe
//   [ ] 0x11f838  SoundInstance_SyncRemainingTimeFromVoice_maybe  [dead]
//   [x] 0x11f8b0  SoundInstance_AcquireAndStartVoice_maybe
//   [x] 0x11f998  SoundInstance_UpdateFade_maybe
//   [x] 0x11f9c8  SoundInstance_GetWorldPosition_maybe
//   [x] 0x11fb78  SoundInstance_UpdatePositionAndVelocity_maybe
//   [x] 0x11fd28  SoundChannel_Detach_maybe
//   [x] 0x11fe30  SoundStream_Resume_maybe
//   [x] 0x11fe70  SoundInstance_HandleDelayState_maybe
//   [x] 0x11ffc8  SoundInstance_UpdateState_maybe
//   [x] 0x1201c8  SoundInstance_ChangeState_maybe
//   [x] 0x120338  SoundStream_Pause_maybe
//   [x] 0x120528  SoundInstance_HandleStartState_maybe
//   [x] 0x120970  SoundInstance_SetVoiceAllowed_maybe
//   [x] 0x120a08  SoundInstance_ReleaseVoiceOnStateEntry_maybe
//   [x] 0x120ab0  SoundInstance_HandleVirtualState_maybe
//   [x] 0x120f18  SoundInstance_HandlePlayingState_maybe
//   [ ] 0x1213c8  SoundInstance_ResetFields_maybe  [dead]
//   [x] 0x1214d8  SoundInstance_Initialize_maybe
//   [x] 0x121980  SoundChannel_Reset_maybe
//   [ ] 0x121ab0  SoundChannel_Reset_2_maybe  [dead]
#include "k2000/sound/SoundInstance.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwMatrix.h"
#include "crt/ppc_ops.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/logic/sound/CKWave.h"
#include "k2000/managers/CKSoundManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/sound/CKListener.h"
#include "k2000/sound/SoundVoice.h"
#include "k2000/sound/SoundVoiceManager.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"

namespace {

// 0x00c50d64: the shared zero vector
const CVector3 kZeroVector = {0.0f, 0.0f, 0.0f};
constexpr float kZero = 0.0f;                      // TOC -0x43a4
constexpr float kOne = 1.0f;                       // TOC -0x4394 / -0x10e5
// TOC -0x4398 (0x426fffff): the inverse frame time used when dt is 0
constexpr float kInverseDtWhenStopped = 0x1.dffffep+5f;
// 0x00c4b194: the state table (five pointers to member functions)
const uint32_t kStateTableAddress = 0x00c4b194;

SoundVoiceManager* VoiceManager() { return g_pEngine->m_soundManager->m_pVoiceManager; }
IKTime* EngineClock() { return g_pEngine->m_timeManager->m_pTime; }
float Dt(IKTime* clock) { return clock->m_afDeltaTime[IKTime::FIXED_GAME_TIME]; }  // +0x20

float WaveLength(CKSound* sound) { return sound->GetSample()->m_fLength; }

// The position/velocity block the state handlers inline (as SoundInstance_UpdatePositionAndVelocity_maybe).
void InlineUpdatePositionAndVelocity(SoundInstance* self, IKTime* clock) {
    CKSound* sound = self->m_pSound;
    const float oldX = self->m_position.x, oldY = self->m_position.y, oldZ = self->m_position.z;
    SoundVoiceManager* vm = VoiceManager();
    CVector3 p;
    self->GetWorldPosition(&p);
    self->m_position.x = p.x;
    self->m_position.z = p.z;
    self->m_position.y = p.y;
    if ((sound->m_SoundFlags & CKSound::kFlagPan) != 0) {
        // a panned sound moves with the listener (no Doppler)
        const CVector3& v = vm->m_pListener->m_unk28;
        self->m_velocity.x = v.x;
        const float y = v.y;
        self->m_velocity.z = v.z;
        self->m_velocity.y = y;
        return;
    }
    self->m_velocity.x = p.x - oldX;
    self->m_velocity.y = p.y - oldY;
    self->m_velocity.z = p.z - oldZ;
    const float dt = Dt(clock);
    const float inverse = dt == kZero ? kInverseDtWhenStopped : kOne / dt;
    const float k = inverse * vm->m_fVoiceRatioVelocity;
    self->m_velocity.z = k * self->m_velocity.z;
    self->m_velocity.x = k * self->m_velocity.x;
    self->m_velocity.y = k * self->m_velocity.y;
}

// The "no voice allowed" block the update phases inline: the voice goes, the remaining time runs down
// (and wraps to the wave's length for a looping sound).
void InlineRunWithoutVoice(SoundInstance* self, IKTime* clock) {
    SoundVoice* voice = self->m_pVoice;
    if (voice != nullptr) {
        const float length = WaveLength(self->m_pSound);
        self->m_fRemaining = length - voice->GetPlayPositionSeconds();
        voice->Release();
    }
    self->UpdateRemainingTime(clock);
}

// The volume target of the fade-in/playing states: volume x scale + the random offset, clamped to [0, 1]
// (NaN gives 1).
float VolumeTarget(CKSound* sound, float offset) {
    float t = ppc::fmadds(sound->m_fVolume, sound->m_fVolumeScale, offset);
    if (t < kZero) {
        t = kZero;
    } else if (!(t <= kOne)) {
        t = kOne;
    }
    return t;
}

float AbsF(float x) {
    uint32_t bits;
    std::memcpy(&bits, &x, 4);
    bits &= 0x7fffffffu;  // rlwinm 0,1,31 on the stored word
    std::memcpy(&x, &bits, 4);
    return x;
}

}  // namespace

SoundNode* SoundNode_Alloc() { return new SoundNode(); }
void SoundNode_Free(SoundNode* node) { delete node; }

SoundInstance::SoundInstance() { Reset(); }

// 0x00121980 SoundChannel_Reset_maybe
void SoundInstance::Reset() {
    m_priority = 0x7fffffff;
    m_pNextPriority = nullptr;
    m_stateCount = 0xff;
    m_state = kStateNone;
    m_volumeRamp[2] = 0.0f;
    m_volumeRamp[1] = 0.0f;
    m_volumeRamp[0] = 0.0f;
    m_velocity.x = kZeroVector.x;
    m_velocity.z = kZeroVector.z;
    m_velocity.y = kZeroVector.y;
    m_position.x = kZeroVector.x;
    m_position.z = kZeroVector.z;
    m_position.y = kZeroVector.y;
    m_flags = 0;
    m_pSound = nullptr;
    m_pVoice = nullptr;
    SetVoiceAllowed(0);  // inlined; no voice here
    m_flags &= ~0xfu;    // the rlwimi pair that follows (bits 0-3; already clear)
}

// 0x001214d8 SoundInstance_Initialize_maybe: reset, linked on the sound's instances, then the first
// state: the delay (flag 0x100 with a pause time), the fade-in (a fade-in time) or playing.
void SoundInstance::Initialize(float startSeconds, CKSound* sound) {
    m_volumeRamp[2] = 0.0f;
    m_volumeRamp[1] = 0.0f;
    m_volumeRamp[0] = 0.0f;
    m_velocity.x = kZeroVector.x;
    m_velocity.z = kZeroVector.z;
    m_velocity.y = kZeroVector.y;
    m_position.x = kZeroVector.x;
    m_position.z = kZeroVector.z;
    m_position.y = kZeroVector.y;
    m_flags = 0;
    m_pSound = nullptr;
    m_pVoice = nullptr;
    SetVoiceAllowed(0);
    m_flags &= ~0xfu;
    m_pSound = sound;
    SoundNode* node = SoundNode_Alloc();
    node->m_pNext = nullptr;
    node->m_pInstance = this;
    node->m_pNext = sound->m_pInstances;
    sound->m_pInstances = node;
    m_state = kStateNone;
    m_stateCount = 5;
    m_pStateTable = reinterpret_cast<const void*>(static_cast<uintptr_t>(kStateTableAddress));
    m_unk38 = 1;
    m_fRemaining = static_cast<float>(static_cast<double>(WaveLength(m_pSound)) - static_cast<double>(startSeconds));
    uint8_t first;
    if ((sound->m_SoundFlags & CKSound::kFlagDelayFirst) == 0 || sound->m_fPauseTime == kZero) {
        first = m_pSound->m_fFadeInTime != kZero ? kStateFadeIn : kStatePlaying;
    } else {
        first = kStateDelay;
    }
    ChangeState(first);  // inlined: the leave of kStateNone is skipped
    m_fPlaybackRate = m_pSound->ComputePlaybackRate();
}

// 0x0011f6c8 SoundInstance_OnVoiceReleased_maybe
void SoundInstance::OnVoiceReleased(float remaining) {
    m_fRemaining = remaining;
    m_pVoice = nullptr;
}

// 0x0011f6d8 SoundInstance_SetVoice_maybe
void SoundInstance::SetVoice(SoundVoice* voice) { m_pVoice = voice; }

// 0x0011f6e0 SoundInstance_IsNotDelayState_maybe
uint32_t SoundInstance::IsNotDelayState() { return (0u - (static_cast<uint32_t>(m_state) ^ 3u)) >> 31; }

// 0x0011f750 SoundInstance_UpdatePlaybackRate_maybe
void SoundInstance::UpdatePlaybackRate(int32_t force) {
    if (m_pSound->m_fRandomPitch == 0.0f || force != 0) m_fPlaybackRate = m_pSound->ComputePlaybackRate();
}

// 0x0011f7a8 SoundInstance_UpdateRemainingTime_maybe
void SoundInstance::UpdateRemainingTime(IKTime* clock) {
    CKSound* sound = m_pSound;
    const float length = WaveLength(sound);
    const float f = m_fRemaining - Dt(clock);
    m_fRemaining = f;
    if (f < kZero) {
        m_fRemaining = kZero;
    } else if (f != kZero) {
        return;
    }
    if ((sound->m_SoundFlags & CKSound::kFlagLoop) != 0) m_fRemaining = length;
}

// 0x0011f8b0 SoundInstance_AcquireAndStartVoice_maybe
SoundVoice* SoundInstance::AcquireAndStartVoice() {
    SoundVoice* voice = m_pVoice;
    if (voice == nullptr) {
        voice = VoiceManager()->FindFreeVoice();
        const float length = WaveLength(m_pSound);
        if (voice != nullptr) {
            voice->BindInstance(this);
            voice->Start(length - m_fRemaining);
            return m_pVoice;
        }
        voice = m_pVoice;
    }
    return voice;
}

// 0x0011f998 SoundInstance_UpdateFade_maybe
void SoundInstance::UpdateFade(IKTime* clock) { FloatApproach_Step(Dt(clock), m_volumeRamp); }

// 0x0011f9c8 SoundInstance_GetWorldPosition_maybe: an attached sound follows its node, a panned one
// sits on its circle in the listener's frame, the others at their position.
CVector3* SoundInstance::GetWorldPosition(CVector3* out) {
    CKSound* sound = m_pSound;
    const CMatrix34* listener = VoiceManager()->m_pListener->GetMatrix();
    out->x = kZeroVector.x;
    out->y = kZeroVector.y;
    out->z = kZeroVector.z;
    if ((sound->m_SoundFlags & CKSound::kFlagAttached) != 0) {
        IKSerializable* node = sound->GetAttachedNode();
        if ((sound->m_SoundFlags & CKSound::kFlagPan) != 0) sound->UpdatePan();
        const CVector3* local = sound->GetPosition();
        RwFrame* frame = static_cast<CSGMovable*>(node)->m_pRwFrame;
        if (frame != nullptr) {
            // the node's frame LTM (RwFrame +0x50)
            const CMatrix34* ltm = reinterpret_cast<const CMatrix34*>(reinterpret_cast<const uint8_t*>(frame) + 0x50);
            CVector3 p;
            Mat4_TransformPoints(ltm, &p, local, 1);
            *out = p;
        } else {
            *out = *local;  // STUB(RW): no RwFrame hierarchy yet (CSGMovable +0x04 is null)
        }
        return out;
    }
    if ((sound->m_SoundFlags & CKSound::kFlagPan) != 0) {
        Mat4_TransformPoints(listener, out, sound->GetPosition(), 1);
        return out;
    }
    const CVector3* p = sound->GetPosition();
    const float z = p->z, y = p->y;
    out->x = p->x;
    out->y = y;
    out->z = z;
    return out;
}

// 0x0011fb78 SoundInstance_UpdatePositionAndVelocity_maybe
void SoundInstance::UpdatePositionAndVelocity(IKTime* clock) { InlineUpdatePositionAndVelocity(this, clock); }

// 0x0011fd28 SoundChannel_Detach_maybe: the voice goes and the instance leaves its sound's list.
void SoundInstance::Detach() {
    if (m_pVoice != nullptr) m_pVoice->Release();
    SoundNode** list = &m_pSound->m_pInstances;
    SoundNode* head = *list;
    if (head != nullptr) {
        if (head->m_pInstance == this) {
            *list = head->m_pNext;
            SoundNode_Free(head);
        } else {
            SoundNode* prev = head;
            for (SoundNode* node = head->m_pNext; node != nullptr; prev = node, node = node->m_pNext) {
                if (node->m_pInstance == this) {
                    prev->m_pNext = node->m_pNext;
                    SoundNode_Free(node);
                    break;
                }
            }
        }
    }
    m_pSound = nullptr;
}

// 0x0011fe30 SoundStream_Resume_maybe (an instance method despite the name)
void SoundInstance::Resume() {
    if ((m_flags & kFlagPaused) == 0) m_flags = (m_flags & ~kFlagPausedEnding) | kFlagPausedEnding;
    m_flags &= ~kFlagPaused;
}

// 0x00120338 SoundStream_Pause_maybe (an instance method): after a resume without a pause the instance
// stops; otherwise its remaining time is kept and it is marked paused.
void SoundInstance::Pause() {
    if ((m_flags & kFlagPausedEnding) != 0) {
        ChangeState(kStateStopped);  // inlined (state table +0x20)
        return;
    }
    if (m_pVoice != nullptr) m_fRemaining = WaveLength(m_pSound) - m_pVoice->GetPlayPositionSeconds();
    m_flags = (m_flags & ~kFlagPaused) | kFlagPaused;
}

uint8_t SoundInstance::CallState(uint8_t state, IKTime* clock, int32_t phase, int32_t other) {
    switch (state) {
    case kStateFadeIn: return HandleFadeInState(clock, phase, other);
    case kStatePlaying: return HandlePlayingState(clock, phase, other);
    case kStateFadeOut: return HandleFadeOutState(clock, phase, other);
    case kStateDelay: return HandleDelayState(clock, phase, other);
    case kStateStopped: return HandleStoppedState(clock, phase, other);
    default: return state;
    }
}

// 0x0011ffc8 SoundInstance_UpdateState_maybe
void SoundInstance::UpdateState(IKTime* clock) {
    const uint8_t state = m_state;
    if (state == kStateNone) return;
    const uint8_t next = CallState(state, clock, 0, state);
    const uint8_t current = m_state;
    if (next == current) return;
    if (current != kStateNone) CallState(current, clock, 2, next);
    m_state = next;
    if (next != kStateNone) CallState(next, clock, 1, current);
}

// 0x001201c8 SoundInstance_ChangeState_maybe (with the engine clock)
void SoundInstance::ChangeState(uint8_t state) {
    const uint8_t previous = m_state;
    IKTime* clock = EngineClock();
    if (previous != kStateNone) CallState(previous, clock, 2, state);
    m_state = state;
    if (state != kStateNone) CallState(state, clock, 1, previous);
}

// 0x00120970 SoundInstance_SetVoiceAllowed_maybe
void SoundInstance::SetVoiceAllowed(uint32_t allowed) {
    m_flags = (m_flags & ~kFlagVoiceAllowed) | allowed;
    if ((m_flags & kFlagVoiceAllowed) == 0 && m_pVoice != nullptr) {
        SoundVoice* voice = m_pVoice;
        m_fRemaining = WaveLength(m_pSound) - voice->GetPlayPositionSeconds();
        voice->Release();
    }
}

// 0x0011fe70 SoundInstance_HandleDelayState_maybe: waits the sound's pause time, then fades in or plays.
uint8_t SoundInstance::HandleDelayState(IKTime* clock, int32_t phase, int32_t) {
    CKSound* sound = m_pSound;
    if (phase == 1) {
        m_fRemaining = sound->m_fPauseTime;
        return kStateDelay;
    }
    if (phase != 0) return kStateDelay;
    const float f = m_fRemaining - Dt(clock);
    m_fRemaining = f;
    if (f < 0.0f) {
        m_fRemaining = 0.0f;
    } else if (f != 0.0f) {
        return kStateDelay;
    }
    m_fRemaining = WaveLength(sound);
    m_volumeRamp[0] = 0.0f;
    m_volumeRamp[2] = 0.0f;
    if (static_cast<double>(m_pSound->m_fRandomPitch) == 0.0) m_fPlaybackRate = m_pSound->ComputePlaybackRate();
    return static_cast<double>(sound->m_fFadeInTime) == 0.0 ? kStatePlaying : kStateFadeIn;
}

// 0x00120528 SoundInstance_HandleStartState_maybe: the fade-in.
uint8_t SoundInstance::HandleFadeInState(IKTime* clock, int32_t phase, int32_t) {
    if (phase == 1) {
        CVector3 p;
        GetWorldPosition(&p);
        m_position.x = p.x;
        m_position.z = p.z;
        m_position.y = p.y;
        CKSound* sound = m_pSound;
        const float offset = sound->GetRandomVolumeOffset();
        m_fVolumeOffset = offset;
        const float target = VolumeTarget(sound, offset);
        m_volumeRamp[1] = AbsF((m_volumeRamp[2] - target) / sound->m_fFadeInTime);
        m_volumeRamp[0] = target;
        return kStateFadeIn;
    }
    if (phase != 0) return kStateFadeIn;
    InlineUpdatePositionAndVelocity(this, clock);
    FloatApproach_Step(Dt(clock), m_volumeRamp);
    if (m_pSound->m_fRandomPitch == kZero) m_fPlaybackRate = m_pSound->ComputePlaybackRate();
    if ((m_flags & kFlagVoiceAllowed) == 0) {
        InlineRunWithoutVoice(this, clock);
    } else if (m_pVoice == nullptr) {
        AcquireAndStartVoice();  // inlined
    }
    return m_volumeRamp[2] == m_volumeRamp[0] ? kStatePlaying : kStateFadeIn;
}

// 0x00120a08 SoundInstance_ReleaseVoiceOnStateEntry_maybe: stopped; the voice goes on entry.
uint8_t SoundInstance::HandleStoppedState(IKTime*, int32_t phase, int32_t) {
    if (phase == 1 && m_pVoice != nullptr) {
        SoundVoice* voice = m_pVoice;
        m_fRemaining = WaveLength(m_pSound) - voice->GetPlayPositionSeconds();
        voice->Release();
    }
    return kStateStopped;
}

// 0x00120ab0 SoundInstance_HandleVirtualState_maybe: the fade-out (Stop with a fade-out time, the end of
// a one-shot, a stolen slot). A looping sound that was not stolen starts again afterwards.
uint8_t SoundInstance::HandleFadeOutState(IKTime* clock, int32_t phase, int32_t other) {
    if (phase == 1) {
        if (other == kStateFadeOut) return kStateFadeOut;
        m_volumeRamp[1] = AbsF(m_volumeRamp[2] / m_pSound->m_fFadeOutTime);
        m_volumeRamp[0] = 0.0f;
        return kStateFadeOut;
    }
    if (phase != 0) return kStateFadeOut;
    CKSound* sound = m_pSound;
    InlineUpdatePositionAndVelocity(this, clock);
    FloatApproach_Step(Dt(clock), m_volumeRamp);
    if (static_cast<double>(m_pSound->m_fRandomPitch) == 0.0) m_fPlaybackRate = m_pSound->ComputePlaybackRate();
    if ((m_flags & kFlagVoiceAllowed) == 0) {
        InlineRunWithoutVoice(this, clock);
    } else if (m_pVoice == nullptr) {
        AcquireAndStartVoice();  // inlined
    }
    if (m_volumeRamp[2] != m_volumeRamp[0] && m_fRemaining != kZero) return kStateFadeOut;
    if ((sound->m_SoundFlags & CKSound::kFlagLoop) != 0 && (m_flags & kFlagStolen) == 0) {
        if (sound->m_fPauseTime == kZero) return sound->m_fFadeInTime == kZero ? kStatePlaying : kStateFadeIn;
        if (m_pVoice != nullptr) {
            SoundVoice* voice = m_pVoice;
            m_fRemaining = WaveLength(m_pSound) - voice->GetPlayPositionSeconds();
            voice->Release();
        }
        return kStateDelay;
    }
    return kStateStopped;
}

// 0x00120f18 SoundInstance_HandlePlayingState_maybe
uint8_t SoundInstance::HandlePlayingState(IKTime* clock, int32_t phase, int32_t) {
    if (phase == 1) {
        CVector3 p;
        GetWorldPosition(&p);
        m_position.x = p.x;
        m_position.z = p.z;
        m_position.y = p.y;
        CKSound* sound = m_pSound;
        const float offset = sound->GetRandomVolumeOffset();
        m_fVolumeOffset = offset;
        const float target = VolumeTarget(sound, offset);
        m_volumeRamp[0] = target;
        m_volumeRamp[2] = target;
        return kStatePlaying;
    }
    if (phase != 0) return kStatePlaying;
    CKSound* sound = m_pSound;
    const float length = WaveLength(sound);
    InlineUpdatePositionAndVelocity(this, clock);
    if (m_pSound->m_fRandomPitch == kZero) m_fPlaybackRate = m_pSound->ComputePlaybackRate();
    const float target = VolumeTarget(sound, m_fVolumeOffset);
    m_volumeRamp[0] = target;
    m_volumeRamp[2] = target;
    FloatApproach_Step(Dt(clock), m_volumeRamp);
    bool ended;
    float position;
    if ((m_flags & kFlagVoiceAllowed) != 0) {
        SoundVoice* voice = AcquireAndStartVoice();  // inlined
        // BUG(original): without a free voice the PS3 reads the null voice's RWA voice (address 4); the
        // allowed instances never outnumber the voices, so it does not happen.
        ended = voice == nullptr || voice->IsPlaying() == 0;
        position = m_pVoice != nullptr ? m_pVoice->GetPlayPositionSeconds() : 0.0f;
    } else {
        InlineRunWithoutVoice(this, clock);
        ended = static_cast<double>(m_fRemaining) == 0.0;
        position = length - m_fRemaining;
    }
    if (!ended) {
        if ((sound->m_SoundFlags & CKSound::kFlagLoop) == 0 && static_cast<double>(sound->m_fFadeOutTime) != 0.0 &&
            length - sound->m_fFadeOutTime < position) {
            return kStateFadeOut;
        }
        return kStatePlaying;
    }
    if ((sound->m_SoundFlags & CKSound::kFlagLoop) == 0) return kStateStopped;
    if (m_pVoice != nullptr) {
        SoundVoice* voice = m_pVoice;
        m_fRemaining = WaveLength(m_pSound) - voice->GetPlayPositionSeconds();
        voice->Release();
    }
    return kStateDelay;
}
