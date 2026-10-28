// SoundInstance.h - one playing instance of a CKSound (0x54 bytes; not a registered class; Ghidra calls
// it SoundInstance / SoundChannel). Original unit: SoundInstance.cpp (0x11f6c8-0x121be0). The voice
// manager keeps 128 of them on a free list (SoundVoiceManager +0x30) and the playing ones on its active
// list (+0x34); each is also on its sound's instance list (CKSound +0x68).
//
// A small state machine drives it (the table at 0x00c4b194, five member-function pointers called with
// (clock, phase, state): phase 0 updates and returns the next state, 1 enters (the previous state), 2
// leaves (the next state)):
//   0 kStateFadeIn   0x120528 SoundInstance_HandleStartState_maybe   volume ramps up over CKSound +0x18
//   1 kStatePlaying  0x120f18 SoundInstance_HandlePlayingState_maybe
//   2 kStateFadeOut  0x120ab0 SoundInstance_HandleVirtualState_maybe volume ramps down over CKSound +0x1c
//   3 kStateDelay    0x11fe70 SoundInstance_HandleDelayState_maybe   waits CKSound +0x40 seconds
//   4 kStateStopped  0x120a08 SoundInstance_ReleaseVoiceOnStateEntry_maybe
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"

class CKSound;
class IKTime;
class SoundInstance;
class SoundVoice;

// A node of the 8-byte free-list pool (0x00ceaa30 in the original) linking instances into lists.
struct SoundNode {
    SoundInstance* m_pInstance;  // +0x00
    SoundNode* m_pNext;          // +0x04
};
DOTD_ASSERT_SIZE(SoundNode, 0x8);
// The pool's allocation (FreeListPool 0xceaa30 is not ported: a plain allocation).
SoundNode* SoundNode_Alloc();
void SoundNode_Free(SoundNode* node);

class SoundInstance {
public:
    enum : uint8_t {
        kStateFadeIn = 0,
        kStatePlaying = 1,
        kStateFadeOut = 2,
        kStateDelay = 3,
        kStateStopped = 4,
        kStateNone = 0xff,
    };
    enum : uint32_t {
        kFlagVoiceAllowed = 1,  // the priority pass gave it a voice
        kFlagPaused = 2,        // SoundStream_Pause_maybe
        kFlagPausedEnding = 4,  // paused while +0x48 bit 2 (set again by the resume when not paused)
        kFlagStolen = 8,        // faded out to free its slot (SoundBackend_PlaySound_maybe)
    };

    SoundInstance();                                        // OperatorNew(0x54) + 0x00121980 SoundChannel_Reset_maybe
    void Reset();                                           // 0x00121980 SoundChannel_Reset_maybe
    void Initialize(float startSeconds, CKSound* sound);    // 0x001214d8 SoundInstance_Initialize_maybe
    void OnVoiceReleased(float remaining);                  // 0x0011f6c8 SoundInstance_OnVoiceReleased_maybe
    void SetVoice(SoundVoice* voice);                       // 0x0011f6d8 SoundInstance_SetVoice_maybe
    uint32_t IsNotDelayState();                             // 0x0011f6e0 SoundInstance_IsNotDelayState_maybe
    void UpdatePlaybackRate(int32_t force);                 // 0x0011f750 SoundInstance_UpdatePlaybackRate_maybe
    void UpdateRemainingTime(IKTime* clock);                // 0x0011f7a8 SoundInstance_UpdateRemainingTime_maybe
    SoundVoice* AcquireAndStartVoice();                     // 0x0011f8b0 SoundInstance_AcquireAndStartVoice_maybe
    void UpdateFade(IKTime* clock);                         // 0x0011f998 SoundInstance_UpdateFade_maybe
    CVector3* GetWorldPosition(CVector3* out);              // 0x0011f9c8 SoundInstance_GetWorldPosition_maybe
    void UpdatePositionAndVelocity(IKTime* clock);          // 0x0011fb78 SoundInstance_UpdatePositionAndVelocity_maybe
    void Detach();                                          // 0x0011fd28 SoundChannel_Detach_maybe
    void Resume();                                          // 0x0011fe30 SoundStream_Resume_maybe
    void Pause();                                           // 0x00120338 SoundStream_Pause_maybe
    void UpdateState(IKTime* clock);                        // 0x0011ffc8 SoundInstance_UpdateState_maybe
    void ChangeState(uint8_t state);                        // 0x001201c8 SoundInstance_ChangeState_maybe
    void SetVoiceAllowed(uint32_t allowed);                 // 0x00120970 SoundInstance_SetVoiceAllowed_maybe

    // the states (phase: 0 update, 1 enter, 2 leave); return the next state
    uint8_t HandleDelayState(IKTime* clock, int32_t phase, int32_t other);    // 0x0011fe70
    uint8_t HandleFadeInState(IKTime* clock, int32_t phase, int32_t other);   // 0x00120528
    uint8_t HandleStoppedState(IKTime* clock, int32_t phase, int32_t other);  // 0x00120a08
    uint8_t HandleFadeOutState(IKTime* clock, int32_t phase, int32_t other);  // 0x00120ab0
    uint8_t HandlePlayingState(IKTime* clock, int32_t phase, int32_t other);  // 0x00120f18
    uint8_t CallState(uint8_t state, IKTime* clock, int32_t phase, int32_t other);

    SoundInstance* m_pNextPriority;  // +0x00 the voice manager's priority list (+0x00), rebuilt every frame
    uint32_t m_priority;             // +0x04 SoundEngine_InsertByPriority_maybe; reset 0x7fffffff
    CKSound* m_pSound;               // +0x08
    CVector3 m_position;             // +0x0c world position (SoundInstance_GetWorldPosition_maybe)
    CVector3 m_velocity;             // +0x18 position change x 1/dt x the voice manager's velocity ratio
    SoundVoice* m_pVoice;            // +0x24
    // +0x28 the volume ramp (FloatApproach {target, speed, current}): FloatApproach_Step moves +0x30
    // towards +0x28 at +0x2c per second
    float m_volumeRamp[3];
    float m_fRemaining;              // +0x34 seconds left to play (or to wait in the delay state)
    uint32_t m_unk38;                // +0x38 Initialize sets 1 (the state machine's)
    const void* m_pStateTable;       // +0x3c 0x00c4b194 (Initialize). Here: unused (CallState switches)
    uint8_t m_state;                 // +0x40
    uint8_t m_stateCount;            // +0x41 5
    uint8_t m_pad42[6];
    uint32_t m_flags;                // +0x48 kFlag*
    float m_fPlaybackRate;           // +0x4c Hz (SoundInstance_ComputePlaybackRate_maybe)
    float m_fVolumeOffset;           // +0x50 CKSound_GetRandomVolumeOffset_maybe, drawn on entering fade-in/playing
};
DOTD_ASSERT_SIZE(SoundInstance, 0x54);
DOTD_ASSERT_OFFSET(SoundInstance, m_pSound, 0x08);
DOTD_ASSERT_OFFSET(SoundInstance, m_position, 0x0c);
DOTD_ASSERT_OFFSET(SoundInstance, m_velocity, 0x18);
DOTD_ASSERT_OFFSET(SoundInstance, m_pVoice, 0x24);
DOTD_ASSERT_OFFSET(SoundInstance, m_volumeRamp, 0x28);
DOTD_ASSERT_OFFSET(SoundInstance, m_fRemaining, 0x34);
DOTD_ASSERT_OFFSET(SoundInstance, m_state, 0x40);
DOTD_ASSERT_OFFSET(SoundInstance, m_flags, 0x48);
DOTD_ASSERT_OFFSET(SoundInstance, m_fPlaybackRate, 0x4c);
DOTD_ASSERT_OFFSET(SoundInstance, m_fVolumeOffset, 0x50);
