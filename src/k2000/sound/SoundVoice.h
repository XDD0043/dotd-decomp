// SoundVoice.h - one hardware voice of the voice pool (0xc bytes; not a registered class): an RWA voice
// and the SoundInstance it plays. Original unit: SoundVoice.cpp (0x121be0-0x1225b0; Ghidra names it
// SoundVoice_* / SoundChannel_*). SoundVoiceManager_Init_maybe builds the pool (output +0x04 = 0x80
// voices minus the stream players).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"

struct RwaVoice;
class SoundInstance;

class SoundInstance;

// DOTD (replays): the PS3 plays the voices in real time, so the frame in which a voice ends is an input of the
// recording rather than something the frames decide. A replay source answers SoundVoice::IsPlaying for a voice's
// instance: 1 playing, 0 ended, -1 no answer (the mixer's state). nullptr = off.
using VoiceReplaySource = int32_t (*)(const SoundInstance* instance);
void SoundVoice_SetReplaySource(VoiceReplaySource source);

class SoundVoice {
public:
    SoundVoice();                               // 0x00121ec8 SoundVoice_Construct_maybe
    void Destroy();                             // 0x00122090 SoundVoice_Destroy_maybe
    void BindInstance(SoundInstance* instance); // 0x00121cc8 SoundVoice_BindInstance_maybe
    float GetPlayPositionSeconds();             // 0x00121d00 SoundVoice_GetPlayPositionSeconds_maybe
    uint8_t IsPlaying();                        // 0x00121d80 SoundVoice_IsPlaying_maybe
    void SetPlayPositionSeconds(float seconds); // 0x00121dc8 SoundVoice_SetPlayPositionSeconds_maybe
    void Resume();                              // 0x00121e58 SoundChannel_ResumeVoice_maybe
    void Pause();                               // 0x00121e90 SoundChannel_PauseVoice_maybe
    void Release();                             // 0x00121f98 SoundVoice_Release_maybe
    void Start(float startSeconds);             // 0x001221a0 SoundVoice_Start_maybe
    int32_t ApplyParameters();                  // 0x001222e8 SoundVoice_ApplyParameters_maybe

    uint32_t m_unk00;            // +0x00 the constructor sets 0; not read by the front end
    RwaVoice* m_pRwaVoice;       // +0x04 RwaVoice_Create_maybe(the output's driver, 0, 0, 0, 0)
    SoundInstance* m_pInstance;  // +0x08 the instance it plays; null when free
};
DOTD_ASSERT_SIZE(SoundVoice, 0xc);
DOTD_ASSERT_OFFSET(SoundVoice, m_pRwaVoice, 0x04);
DOTD_ASSERT_OFFSET(SoundVoice, m_pInstance, 0x08);
