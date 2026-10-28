// rwa.h - the RenderWare Audio (RWA 3.x) calls the K sound code makes, re-implemented on the platform
// mixer (no RWA source exists; the PS3 build links RWA at 0x6be000-0x6f0000 and reaches it through
// TocBridge_Rwa* stubs, below it MultiStream on the SPUs). Platform code, not a port, except where the
// PPU side of RWA is read from the EBOOT and reproduced (marked with the address).
//
// What the K code sees is kept: voice properties are set (dirty flags) and take effect when the update
// bracket closes (Rwa_EndUpdate commits every voice: RwaVoice_CommitChanges_maybe 0x6ebeec), except
// IsPlaying, which reads the pending play request or the live stream state as RWA does.
//
// Data: the level's wave dictionary (RW chunk 0x809, RwaWaveDict_StreamRead_maybe 0x6e2350): one 0x80a
// header (name), then 0x80c: a big-endian count and per wave a 0x802 chunk holding a 0x803 header
// (big-endian: flags, sample rate, ?, data bytes, bits (+0x10), channels (+0x11), codec GUID (+0x20); the format again (+0x30);
// the wave GUID (+0x60); the source file name (+0x70)) and a 0x804 chunk with the data. Every wave of the game uses the
// PCM codec {D01BD217-3587-4EED-B9D9-B8E86EA9B995}: 16-bit big-endian; others are refused.
#pragma once
#include <cstdint>
#include <string>
#include <vector>

#include "platform/audio/mixer.h"

struct RwaWave {
    uint32_t flags = 0;          // header word 0 (0x0f in the game's data); bit 1: positional (3D)
    uint32_t sampleRate = 0;
    uint32_t channels = 0;
    uint32_t dataBytes = 0;
    uint32_t frames = 0;
    std::string name;            // the source .wav path the tools recorded
    dotd::audio::PcmWave pcm;    // native-endian samples (converted in place in the dictionary's buffer)
};

struct RwaWaveDict {
    std::string name;            // the 0x80a header's name ("Dico secteur commun")
    std::vector<RwaWave> waves;
    std::vector<uint8_t> data;   // the chunk payload; the waves' samples point into it
};

// Parses the payload of a 0x809 chunk (taking the buffer). Null when the data is not a wave dictionary
// or uses a codec this build does not decode.
RwaWaveDict* RwaWaveDict_StreamRead(std::vector<uint8_t>&& payload);
void RwaWaveDict_Destroy(RwaWaveDict* dict);
uint32_t RwaWaveDict_GetWaveCount(const RwaWaveDict* dict);
RwaWave* RwaWaveDict_GetWave(RwaWaveDict* dict, uint32_t index);

// The listener (RwaListener, InitDefaults 0x6be1b8): world position, velocity, the orientation rows of
// the camera matrix, the rolloff factor (+0x7c, default 10), the Doppler factor (+0x80, 1) and the
// distance scale (+0x84, 1).
struct RwaListener {
    float position[3] = {0, 0, 0};
    float velocity[3] = {0, 0, 0};
    float up[3] = {0, 1, 0};
    float at[3] = {0, 0, 1};
    float right[3] = {1, 0, 0};
    float rolloff = 10.0f;
    float doppler = 1.0f;
    float scale = 1.0f;
};

// The output (RwaPS3Driver): the port level and the listener.
struct RwaOutput {
    float portLevel = 1.0f;
    RwaListener* listener = nullptr;
    const void* outputEffect = nullptr;
};

struct RwaVoice {
    uint32_t flags = 0;          // +0x28 dirty/pending bits as RWA keeps them (2 3D, 8 pitch, 0x10 volume,
                                 // 0x40 play state change, 0x80 play, 0x100 seek, 0x200 loop)
    float pitch = 0.0f;          // +0x2c Hz
    float volume = 1.0f;         // +0x30
    RwaWave* wave = nullptr;     // +0x3c
    uint32_t playPosition = 0;   // +0x40 samples (refreshed by the commit)
    float position[3] = {0, 0, 0};  // +0x54
    float velocity[3] = {0, 0, 0};  // +0x60
    float minDistance = 0.0f;    // +0x6c
    float maxDistance = 0.0f;    // +0x70
    RwaOutput* output = nullptr;
    int32_t mixerVoice = -1;
    float gainLeft = 0.0f, gainRight = 0.0f, dopplerPitch = 1.0f;  // the last 3D result
};

RwaOutput* RwaPS3Driver_Create();
void RwaPS3Driver_SetListener(RwaOutput* output, RwaListener* listener);
// 0x6eab4c RwaPS3_SetPortLevel: cellAudioSetPortLevel on the RWA port.
void RwaPS3_SetPortLevel(float level, RwaOutput* output);
// 0x6eac70 RwaPS3Driver_SetOutputEffect_maybe: the I3DL2 reverb environment (MultiStream DSP). Kept only:
// the platform mixer has no reverb.
void RwaPS3Driver_SetOutputEffect(RwaOutput* output, const void* environment);

RwaListener* RwaListener_Create();

RwaVoice* RwaVoice_Create(RwaOutput* output);
void RwaVoice_Destroy(RwaVoice* voice);
void RwaVoice_SetWave(RwaVoice* voice, RwaWave* wave);
RwaWave* RwaVoice_GetWave(const RwaVoice* voice);
void RwaVoice_SetPlaying(RwaVoice* voice, int32_t playing);
int32_t RwaVoice_IsPlaying(const RwaVoice* voice);
void RwaVoice_SetPlayPosition(RwaVoice* voice, uint32_t samples);
uint32_t RwaVoice_GetPlayPosition(const RwaVoice* voice);
void RwaVoice_SetLoop(RwaVoice* voice, int32_t loop);
int32_t RwaVoice_GetLoop(const RwaVoice* voice);
void RwaVoice_SetVolume(float volume, RwaVoice* voice);
void RwaVoice_SetPitch(float pitch, RwaVoice* voice);
float RwaVoice_GetPitch(const RwaVoice* voice);
// Ghidra: RwaVoice_SetVelocityOrDirection_maybe 0x6ec4bc (+0x54, sent to MultiStream as the position)
void RwaVoice_SetPosition(RwaVoice* voice, const float* position);
// Ghidra: RwaVoice_SetPosition_maybe 0x6ec580 (+0x60, sent to MultiStream as the velocity)
void RwaVoice_SetVelocity(RwaVoice* voice, const float* velocity);
void RwaVoice_SetMinDistance(float distance, RwaVoice* voice);
void RwaVoice_SetMaxDistance(float distance, RwaVoice* voice);

// The update bracket (Rwa_BeginUpdate_maybe 0x6c8e20 / Rwa_EndUpdate_maybe 0x6c8d20 / Rwa_IsUpdating_maybe).
void Rwa_BeginUpdate();
void Rwa_EndUpdate();
int32_t Rwa_IsUpdating();

namespace dotd::audio {
// 0x006be7d8 RwaListener_CalcEmitterAttenuationAndDoppler_maybe: out[0] the distance gain, out[1] the
// Doppler pitch factor, out[2]/out[3] the direction against the listener's right/at rows mapped to
// [0, 1] (0.5 - 0.5 dot), out[4]/out[5] the same for the relative velocity. emitter: position[3],
// velocity[3], min distance, max distance.
void RwaCalcEmitterAttenuation(const RwaListener* listener, const float* emitter, float* out, int32_t speakerMode);
// Rwa_Vec3Length_Approx_maybe 0x6cbf00: the table square root of the squared length.
float RwaVec3LengthApprox(const float* v);
}  // namespace dotd::audio
