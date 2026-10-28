// rwa.cpp - see rwa.h.
#include "platform/audio/rwa.h"

#include <algorithm>
#include <cmath>
#include <cstring>

#include "platform/log.h"

namespace {

// {D01BD217-3587-4EED-B9D9-B8E86EA9B995}: RWA's PCM codec (16-bit, the platform's byte order: big-endian here)
const uint8_t kPcmGuid[16] = {0xd0, 0x1b, 0xd2, 0x17, 0x35, 0x87, 0x4e, 0xed,
                              0xb9, 0xd9, 0xb8, 0xe8, 0x6e, 0xa9, 0xb9, 0x95};

uint32_t LE32(const uint8_t* p) {
    return static_cast<uint32_t>(p[0]) | (static_cast<uint32_t>(p[1]) << 8) | (static_cast<uint32_t>(p[2]) << 16) |
           (static_cast<uint32_t>(p[3]) << 24);
}
uint32_t BE32(const uint8_t* p) {
    return (static_cast<uint32_t>(p[0]) << 24) | (static_cast<uint32_t>(p[1]) << 16) | (static_cast<uint32_t>(p[2]) << 8) |
           static_cast<uint32_t>(p[3]);
}

// A RenderWare chunk header inside the payload: type, size, version (little-endian).
struct Chunk {
    uint32_t type, size, offset;  // offset: the chunk's data
};
bool ReadChunk(const std::vector<uint8_t>& d, uint32_t at, Chunk* c) {
    if (at + 12 > d.size()) return false;
    c->type = LE32(&d[at]);
    c->size = LE32(&d[at + 4]);
    c->offset = at + 12;
    return c->offset + c->size <= d.size();
}

std::vector<RwaVoice*>& Voices() {
    static std::vector<RwaVoice*> voices;
    return voices;
}
bool g_updating = false;

// The 3D part of a commit: distance gain and Doppler from RWA's listener model, a constant-power pan from
// the direction against the listener's right row. Platform choice: MultiStream's surround panner (SPU
// side, source params 0x1004/0x1006/0x1020/0x1021/0x1023 from RwaPS3Voice_Update3DParams_maybe 0x6eef78)
// is not reproduced. RW's camera "right" row points to the screen's left, so a source along +right is
// heard on the left.
void Update3D(RwaVoice* v) {
    const RwaListener* l = v->output != nullptr ? v->output->listener : nullptr;
    v->dopplerPitch = 1.0f;
    if (l == nullptr || v->wave == nullptr || (v->wave->flags & 2u) == 0) {
        v->gainLeft = v->gainRight = 1.0f;
        return;
    }
    const float emitter[8] = {v->position[0], v->position[1], v->position[2], v->velocity[0],
                              v->velocity[1], v->velocity[2], v->minDistance, v->maxDistance};
    float out[6];
    dotd::audio::RwaCalcEmitterAttenuation(l, emitter, out, 0);
    float dir[3] = {v->position[0] - l->position[0], v->position[1] - l->position[1], v->position[2] - l->position[2]};
    const float len = std::sqrt(dir[0] * dir[0] + dir[1] * dir[1] + dir[2] * dir[2]);
    float right = 0.0f;
    if (len > 0.0f) right = (dir[0] * l->right[0] + dir[1] * l->right[1] + dir[2] * l->right[2]) / len;
    const float w = std::clamp(0.5f - 0.5f * right, 0.0f, 1.0f);  // weight of the right speaker
    v->gainLeft = out[0] * std::sqrt(1.0f - w);
    v->gainRight = out[0] * std::sqrt(w);
    v->dopplerPitch = out[1];
}

void PushParams(RwaVoice* v) {
    if (v->mixerVoice < 0) return;
    dotd::audio::VoiceSetParams(v->mixerVoice, v->volume * v->gainLeft, v->volume * v->gainRight,
                                v->pitch * v->dopplerPitch);
}

// 0x006ebeec RwaVoice_CommitChanges_maybe, on the mixer.
void Commit(RwaVoice* v) {
    using namespace dotd::audio;
    uint32_t& f = v->flags;
    if (v->wave == nullptr) {
        f &= 0xfffffe81u;
        v->playPosition = 0;
        return;
    }
    Update3D(v);
    f &= ~0x2u;
    f &= ~0x18u;  // pitch, volume
    PushParams(v);
    bool playing = VoiceIsPlaying(v->mixerVoice);
    if ((f & 0x40u) != 0) {
        if (playing) {
            VoiceSetPaused(v->mixerVoice, true);  // RwaPS3Voice_SetPause_maybe(1)
            playing = false;
        }
        if ((f & 0x80u) != 0) {
            // RwaPS3Voice_Play_maybe 0x6ee85c: a paused stream resumes; otherwise it starts from the
            // wave's first byte (the start offset is not passed on), looping when 0x200 is set.
            if (VoiceIsPaused(v->mixerVoice)) {
                VoiceSetPaused(v->mixerVoice, false);
            } else {
                VoicePlay(v->mixerVoice, &v->wave->pcm, (f & 0x200u) != 0);
            }
            playing = true;
            f &= ~0x100u;
        }
        f &= ~0x80u;
        f &= ~0x40u;
    }
    f &= ~0x100u;  // a seek while playing does nothing (KStub_Return0_6eeb08)
    v->playPosition = playing ? VoiceGetPosition(v->mixerVoice) : 0;
}

}  // namespace

RwaWaveDict* RwaWaveDict_StreamRead(std::vector<uint8_t>&& payload) {
    RwaWaveDict* dict = new RwaWaveDict();
    dict->data = std::move(payload);
    std::vector<uint8_t>& d = dict->data;
    Chunk header, list;
    if (!ReadChunk(d, 0, &header) || header.type != 0x80a || !ReadChunk(d, header.offset + header.size, &list) ||
        list.type != 0x80c || list.size < 4) {
        DOTD_LOG("rwa: not a wave dictionary");
        delete dict;
        return nullptr;
    }
    // the header's name at +0x34 (after the fields and the dictionary GUID)
    if (header.size > 0x34) {
        const char* name = reinterpret_cast<const char*>(&d[header.offset + 0x34]);
        dict->name.assign(name, strnlen(name, header.size - 0x34));
    }
    const uint32_t count = BE32(&d[list.offset]);
    dict->waves.resize(count);
    uint32_t at = list.offset + 4;
    for (uint32_t i = 0; i < count; ++i) {
        Chunk wave, info, data;
        if (!ReadChunk(d, at, &wave) || wave.type != 0x802 || !ReadChunk(d, wave.offset, &info) || info.type != 0x803 ||
            info.size < 0x70 || !ReadChunk(d, info.offset + info.size, &data) || data.type != 0x804) {
            DOTD_LOG("rwa: wave %u: bad chunks", i);
            delete dict;
            return nullptr;
        }
        const uint8_t* h = &d[info.offset];
        RwaWave& w = dict->waves[i];
        w.flags = BE32(h);
        w.sampleRate = BE32(h + 4);
        w.dataBytes = BE32(h + 0xc);
        const uint32_t bits = h[0x10];
        w.channels = h[0x11];
        const char* name = reinterpret_cast<const char*>(h + 0x70);  // after the wave GUID (+0x60)
        w.name.assign(name, strnlen(name, info.size - 0x70));
        if (std::memcmp(h + 0x20, kPcmGuid, 16) != 0 || bits != 16 || w.channels == 0 || w.dataBytes > data.size) {
            DOTD_LOG("rwa: wave %u (%s): codec not supported", i, w.name.c_str());
            delete dict;
            return nullptr;
        }
        // big-endian 16-bit PCM -> native, in place (the data is 2-byte aligned within the payload or not:
        // go through bytes)
        uint8_t* p = &d[data.offset];
        const uint32_t samples = w.dataBytes / 2;
        for (uint32_t s = 0; s < samples; ++s) std::swap(p[2 * s], p[2 * s + 1]);
        w.frames = samples / w.channels;
        w.pcm.samples = reinterpret_cast<const int16_t*>(p);
        w.pcm.frames = w.frames;
        w.pcm.channels = w.channels;
        w.pcm.sampleRate = w.sampleRate;
        w.pcm.name = w.name;
        at = wave.offset + wave.size;
    }
    return dict;
}

void RwaWaveDict_Destroy(RwaWaveDict* dict) { delete dict; }
uint32_t RwaWaveDict_GetWaveCount(const RwaWaveDict* dict) {
    return dict != nullptr ? static_cast<uint32_t>(dict->waves.size()) : 0u;
}
RwaWave* RwaWaveDict_GetWave(RwaWaveDict* dict, uint32_t index) {
    return dict != nullptr && index < dict->waves.size() ? &dict->waves[index] : nullptr;
}

RwaOutput* RwaPS3Driver_Create() {
    dotd::audio::Init();
    return new RwaOutput();
}
void RwaPS3Driver_SetListener(RwaOutput* output, RwaListener* listener) {
    if (output != nullptr) output->listener = listener;
}
void RwaPS3_SetPortLevel(float level, RwaOutput* output) {
    if (output != nullptr) output->portLevel = level;
    dotd::audio::SetVoiceMasterLevel(level);
}

void RwaPS3Driver_SetOutputEffect(RwaOutput* output, const void* environment) {
    if (output != nullptr) output->outputEffect = environment;
}

RwaListener* RwaListener_Create() { return new RwaListener(); }

RwaVoice* RwaVoice_Create(RwaOutput* output) {
    RwaVoice* v = new RwaVoice();
    v->output = output;
    v->mixerVoice = dotd::audio::VoiceCreate();
    Voices().push_back(v);
    return v;
}
void RwaVoice_Destroy(RwaVoice* voice) {
    if (voice == nullptr) return;
    dotd::audio::VoiceDestroy(voice->mixerVoice);
    auto& list = Voices();
    list.erase(std::remove(list.begin(), list.end(), voice), list.end());
    delete voice;
}

// 0x006ecbb8 RwaVoice_SetWave_maybe
void RwaVoice_SetWave(RwaVoice* voice, RwaWave* wave) {
    if (RwaVoice_IsPlaying(voice) != 0) RwaVoice_SetPlaying(voice, 0);
    if (wave != nullptr) {
        voice->pitch = static_cast<float>(wave->sampleRate);
        voice->flags |= 8u;
    }
    voice->flags |= 0x400u;
    voice->wave = wave;
    if (wave == nullptr) dotd::audio::VoiceStop(voice->mixerVoice);  // RwaPS3Voice_Stop_maybe
}
RwaWave* RwaVoice_GetWave(const RwaVoice* voice) { return voice->wave; }

// 0x006ec864 RwaVoice_SetPlaying_maybe
void RwaVoice_SetPlaying(RwaVoice* voice, int32_t playing) {
    if (playing == 0) {
        voice->flags &= ~0x80u;
    } else {
        voice->flags |= 0x80u;
    }
    voice->flags |= 0x40u;
}
// 0x006ec8f8 RwaVoice_IsPlaying_maybe: the pending request, else the stream's state.
int32_t RwaVoice_IsPlaying(const RwaVoice* voice) {
    if ((voice->flags & 0x40u) != 0) return (voice->flags & 0x80u) != 0 ? 1 : 0;
    if (voice->wave == nullptr) return 0;
    return dotd::audio::VoiceIsPlaying(voice->mixerVoice) ? 1 : 0;
}
// 0x006ec9d4 RwaVoice_SetPlayPosition_maybe
void RwaVoice_SetPlayPosition(RwaVoice* voice, uint32_t samples) {
    voice->playPosition = samples;
    voice->flags |= 0x100u;
}
// 0x006ecab8 RwaVoice_GetPlayPosition_maybe
uint32_t RwaVoice_GetPlayPosition(const RwaVoice* voice) { return voice->playPosition; }
// 0x006ecaf0 RwaVoice_SetLoop_maybe
void RwaVoice_SetLoop(RwaVoice* voice, int32_t loop) {
    if (loop == 0) {
        voice->flags &= ~0x200u;
    } else {
        voice->flags |= 0x200u;
    }
}
int32_t RwaVoice_GetLoop(const RwaVoice* voice) { return (voice->flags & 0x200u) != 0 ? 1 : 0; }
// 0x006ec7dc RwaVoice_SetVolume_maybe
void RwaVoice_SetVolume(float volume, RwaVoice* voice) {
    voice->volume = volume;
    voice->flags |= 0x10u;
}
// 0x006ec754 RwaVoice_SetPitch_maybe
void RwaVoice_SetPitch(float pitch, RwaVoice* voice) {
    voice->pitch = pitch;
    voice->flags |= 8u;
}
float RwaVoice_GetPitch(const RwaVoice* voice) { return voice->pitch; }
void RwaVoice_SetPosition(RwaVoice* voice, const float* position) {
    std::memcpy(voice->position, position, sizeof(voice->position));
    voice->flags |= 2u;
}
void RwaVoice_SetVelocity(RwaVoice* voice, const float* velocity) {
    std::memcpy(voice->velocity, velocity, sizeof(voice->velocity));
    voice->flags |= 2u;
}
// 0x006ec644 RwaVoice_SetMinDistance_maybe
void RwaVoice_SetMinDistance(float distance, RwaVoice* voice) {
    voice->flags |= 2u;
    voice->minDistance = distance;
}
void RwaVoice_SetMaxDistance(float distance, RwaVoice* voice) {
    voice->flags |= 2u;
    voice->maxDistance = distance;
}

void Rwa_BeginUpdate() { g_updating = true; }
void Rwa_EndUpdate() {
    for (RwaVoice* v : Voices()) Commit(v);
    g_updating = false;
}
int32_t Rwa_IsUpdating() { return g_updating ? 1 : 0; }

namespace dotd::audio {

// 0x006cbf00 Rwa_Vec3Length_Approx_maybe. The table at 0xc45200 holds the top 7 mantissa bits of the
// square root of each mantissa class: entry i = floor((sqrt((1 + (i & 127) / 128) * (i < 128 ? 1 : 2)) - 1) * 128)
// (checked against all 256 entries of the EBOOT's table).
float RwaVec3LengthApprox(const float* v) {
    static uint16_t table[256];
    static bool built = false;
    if (!built) {
        for (int i = 0; i < 256; ++i) {
            const double m = (1.0 + (i & 127) / 128.0) * (i < 128 ? 1.0 : 2.0);
            table[i] = static_cast<uint16_t>(std::floor((std::sqrt(m) - 1.0) * 128.0));
        }
        built = true;
    }
    const float sq = v[2] * v[2] + v[0] * v[0] + v[1] * v[1];
    if (sq == 0.0f) return sq;
    uint32_t bits;
    std::memcpy(&bits, &sq, 4);
    const uint32_t e = (bits >> 23) - 0x7f;
    const uint32_t exponent = static_cast<uint32_t>((static_cast<int32_t>(static_cast<int16_t>(e)) >> 1) + 0x7f) << 23;
    uint32_t mant = bits & 0x7fffff;
    if ((e & 1u) != 0) mant |= 0x800000u;
    const uint32_t result = (static_cast<uint32_t>(table[mant >> 16]) << 16) | exponent;
    float out;
    std::memcpy(&out, &result, 4);
    return out;
}

namespace {
void Normalize(float* v) {
    const float len = std::sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    if (len > 0.0f) {
        const float inv = 1.0f / len;
        v[0] *= inv;
        v[1] *= inv;
        v[2] *= inv;
    }
}
}  // namespace

// 0x006be7d8 RwaListener_CalcEmitterAttenuationAndDoppler_maybe. The float order follows the decompiler;
// the fused multiply-adds were not checked against the assembly (this only shapes output gains). RwV3dNormalize
// is approximated by a plain normalisation.
void RwaCalcEmitterAttenuation(const RwaListener* l, const float* e, float* out, int32_t speakerMode) {
    const float scale = l->scale, rolloff = l->rolloff, doppler = l->doppler;
    // the relative position one velocity step ago, and now
    float prev[3] = {(e[0] - e[3]) - (l->position[0] - l->velocity[0]), (e[1] - e[4]) - (l->position[1] - l->velocity[1]),
                     (e[2] - e[5]) - (l->position[2] - l->velocity[2])};
    const float prevDist = RwaVec3LengthApprox(prev);
    float rel[3] = {e[0] - l->position[0], e[1] - l->position[1], e[2] - l->position[2]};
    const float dist = RwaVec3LengthApprox(rel);
    const float dv = std::clamp(dist - prevDist, -150.0f, 150.0f);
    out[1] = (scale * 340.0f - dv * doppler) / (scale * 340.0f);
    if (dist <= e[7]) {
        if (dist < e[6]) {
            out[0] = 1.0f;
        } else {
            const float range = e[7] - e[6];
            out[0] = (range - (dist - e[6])) / (rolloff * (dist - e[6]) + range);
        }
    } else {
        out[0] = 0.0f;
    }
    // a direction: the listener's at row for a zero vector, else normalised with |y| < 7 lifted to 7
    // (as the code does)
    auto direction = [&](float* d) {
        if (d[0] == 0.0f && d[1] == 0.0f && d[2] == 0.0f) {
            d[0] = l->at[0];
            d[1] = l->at[1];
            d[2] = l->at[2];
            return;
        }
        if (-7.0f < d[1] && d[1] < 7.0f) d[1] = 7.0f;
        Normalize(d);
    };
    direction(rel);
    direction(prev);
    auto map = [](float dot) { return std::clamp(dot * -0.5f + 0.5f, 0.0f, 1.0f); };
    out[2] = map(rel[2] * l->right[2] + rel[0] * l->right[0] + rel[1] * l->right[1]);
    out[3] = map(rel[2] * l->at[2] + rel[0] * l->at[0] + rel[1] * l->at[1]);
    out[4] = map(prev[2] * l->right[2] + prev[0] * l->right[0] + prev[1] * l->right[1]);
    out[5] = map(prev[2] * l->at[2] + prev[0] * l->at[0] + prev[1] * l->at[1]);
    if (speakerMode == 2) {
        out[2] = (out[2] - 0.5f) * 0.0f + 0.5f;
        out[4] = (out[4] - 0.5f) * 0.0f + 0.5f;
    } else if (speakerMode == 3) {
        out[2] = (out[2] - 0.5f) * 0.5f + 0.5f;
        out[4] = (out[4] - 0.5f) * 0.5f + 0.5f;
    }
}

}  // namespace dotd::audio
