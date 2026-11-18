// mixer.cpp - see mixer.h.
#include "platform/audio/mixer.h"

#include <SDL3/SDL.h>

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <mutex>

#include "platform/log.h"

namespace dotd::audio {
namespace {

constexpr int32_t kMaxVoices = 256;
constexpr int32_t kMaxStreams = 32;
constexpr uint32_t kChunk = 512;  // output frames mixed per step

struct Voice {
    bool used = false;
    const PcmWave* wave = nullptr;
    bool open = false;     // a wave is set (MultiStream: the stream is open)
    bool started = false;  // played since the last Play
    bool paused = false;
    bool ended = false;    // a one-shot reached its end
    bool loop = false;
    uint64_t pos = 0;      // 32.32 fixed point frames
    float gainL = 0.0f, gainR = 0.0f;
    float rateHz = 0.0f;
};

struct Stream {
    bool used = false;
    uint32_t rate = 44100;
    uint32_t channels = 2;
    std::deque<float> queue;  // interleaved frames
    uint64_t frac = 0;        // 32.32 position within the queue's first frame
    float gain = 1.0f;
    bool paused = false;
    bool announced = false;
    std::string name;
};

struct State {
    std::mutex mutex;
    Mode mode = Mode::Device;
    bool modeForced = false;
    bool initialised = false;
    SDL_AudioStream* device = nullptr;
    Voice voices[kMaxVoices];
    Stream streams[kMaxStreams];
    float voiceLevel = 1.0f;
    uint64_t mixed = 0;
    double carry = 0.0;
    std::vector<float>* capture = nullptr;
    std::vector<Event> events;
    std::vector<float> scratch;
};

State& S() {
    static State* state = new State();  // never destroyed: the audio thread may outlive static destructors
    return *state;
}

bool ValidVoice(int32_t v) { return v >= 0 && v < kMaxVoices && S().voices[v].used; }
bool ValidStream(int32_t s) { return s >= 0 && s < kMaxStreams && S().streams[s].used; }

// Reads frame `index` (clamped/wrapped by the caller) of the wave as left/right floats.
inline void WaveFrame(const PcmWave* w, uint32_t index, float* l, float* r) {
    constexpr float kScale = 1.0f / 32768.0f;
    if (w->channels >= 2) {
        *l = static_cast<float>(w->samples[2u * index]) * kScale;
        *r = static_cast<float>(w->samples[2u * index + 1u]) * kScale;
    } else {
        *l = *r = static_cast<float>(w->samples[index]) * kScale;
    }
}

void MixVoice(Voice& v, float* out, uint32_t frames, float level) {
    if (!v.open || !v.started || v.paused || v.ended || v.wave == nullptr || v.wave->frames == 0) return;
    const PcmWave* w = v.wave;
    const uint64_t step = static_cast<uint64_t>(static_cast<double>(v.rateHz) / kOutputRate * 4294967296.0);
    const uint64_t end = static_cast<uint64_t>(w->frames) << 32;
    const float gl = v.gainL * level, gr = v.gainR * level;
    for (uint32_t i = 0; i < frames; ++i) {
        if (v.pos >= end) {
            if (!v.loop) {
                v.ended = true;
                return;
            }
            v.pos %= end;
        }
        const uint32_t i0 = static_cast<uint32_t>(v.pos >> 32);
        uint32_t i1 = i0 + 1;
        if (i1 >= w->frames) i1 = v.loop ? 0 : i0;
        const float t = static_cast<float>(static_cast<uint32_t>(v.pos)) * (1.0f / 4294967296.0f);
        float l0, r0, l1, r1;
        WaveFrame(w, i0, &l0, &r0);
        WaveFrame(w, i1, &l1, &r1);
        out[2 * i] += (l0 + (l1 - l0) * t) * gl;
        out[2 * i + 1] += (r0 + (r1 - r0) * t) * gr;
        v.pos += step;
    }
}

void MixStream(Stream& s, float* out, uint32_t frames) {
    if (s.paused || s.queue.empty()) return;
    const uint32_t ch = s.channels;
    const uint64_t step = (static_cast<uint64_t>(s.rate) << 32) / kOutputRate;
    for (uint32_t i = 0; i < frames; ++i) {
        const size_t have = s.queue.size() / ch;
        if (have < 2) break;  // keep one frame for the interpolation
        const float t = static_cast<float>(static_cast<uint32_t>(s.frac)) * (1.0f / 4294967296.0f);
        const float l0 = s.queue[0], l1 = s.queue[ch];
        const float r0 = ch >= 2 ? s.queue[1] : l0, r1 = ch >= 2 ? s.queue[ch + 1] : l1;
        out[2 * i] += (l0 + (l1 - l0) * t) * s.gain;
        out[2 * i + 1] += (r0 + (r1 - r0) * t) * s.gain;
        s.frac += step;
        while ((s.frac >> 32) != 0 && s.queue.size() / ch >= 2) {
            for (uint32_t c = 0; c < ch; ++c) s.queue.pop_front();
            s.frac -= 1ull << 32;
        }
    }
}

// Mixes `frames` frames into out (zeroed here). The mutex is held by the caller.
void MixLocked(float* out, uint32_t frames) {
    State& st = S();
    std::memset(out, 0, sizeof(float) * 2 * frames);
    for (Voice& v : st.voices) {
        if (v.used) MixVoice(v, out, frames, st.voiceLevel);
    }
    for (Stream& s : st.streams) {
        if (s.used) MixStream(s, out, frames);
    }
    for (uint32_t i = 0; i < 2 * frames; ++i) out[i] = std::clamp(out[i], -1.0f, 1.0f);
    st.mixed += frames;
    if (st.capture != nullptr) st.capture->insert(st.capture->end(), out, out + 2 * frames);
}

void SDLCALL DeviceCallback(void*, SDL_AudioStream* stream, int additional, int) {
    State& st = S();
    uint32_t frames = static_cast<uint32_t>(additional) / 8u;
    std::lock_guard<std::mutex> lock(st.mutex);
    while (frames > 0) {
        const uint32_t n = std::min(frames, kChunk);
        st.scratch.resize(2 * n);
        MixLocked(st.scratch.data(), n);
        SDL_PutAudioStreamData(stream, st.scratch.data(), static_cast<int>(n * 8));
        frames -= n;
    }
}

void InitLocked() {
    State& st = S();
    if (st.initialised) return;
    st.initialised = true;
    if (!st.modeForced) {
        // with a window (the game) a device, headless (tests, --headless) the capture sink
        st.mode = SDL_WasInit(SDL_INIT_VIDEO) != 0 ? Mode::Device : Mode::Capture;
        const char* env = std::getenv("DOTD_AUDIO");
        if (env != nullptr) {
            if (std::strcmp(env, "capture") == 0) st.mode = Mode::Capture;
            else if (std::strcmp(env, "off") == 0) st.mode = Mode::Capture;  // silent: mixed, never heard
            else st.mode = Mode::Device;
        }
    }
    if (st.mode == Mode::Off) st.mode = Mode::Capture;
    if (st.mode != Mode::Device) return;
    if (!SDL_InitSubSystem(SDL_INIT_AUDIO)) {
        DOTD_LOG("audio: SDL audio unavailable (%s): capture mode", SDL_GetError());
        st.mode = Mode::Capture;
        return;
    }
    SDL_AudioSpec spec{SDL_AUDIO_F32, 2, static_cast<int>(kOutputRate)};
    st.device = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, DeviceCallback, nullptr);
    if (st.device == nullptr) {
        DOTD_LOG("audio: no audio device (%s): capture mode", SDL_GetError());
        st.mode = Mode::Capture;
        return;
    }
    SDL_ResumeAudioStreamDevice(st.device);
    DOTD_LOG("audio: device open, 48000 Hz stereo");
}

struct Lock {
    std::unique_lock<std::mutex> lock;
    Lock() : lock(S().mutex) { InitLocked(); }
};

}  // namespace

void SetMode(Mode mode) {
    State& st = S();
    SDL_AudioStream* device = nullptr;
    {
        std::lock_guard<std::mutex> lock(st.mutex);
        st.mode = mode;
        st.modeForced = true;
        device = st.device;
        st.device = nullptr;
        st.initialised = false;
    }
    if (device != nullptr) SDL_DestroyAudioStream(device);  // outside the lock: the callback takes it
}

Mode GetMode() {
    Lock l;
    return S().mode;
}

void Init() { Lock l; }

void Shutdown() {
    State& st = S();
    SDL_AudioStream* device = nullptr;
    {
        std::lock_guard<std::mutex> lock(st.mutex);
        device = st.device;
        st.device = nullptr;
    }
    if (device != nullptr) SDL_DestroyAudioStream(device);
}

void SetVoiceMasterLevel(float level) {
    Lock l;
    S().voiceLevel = level;
}

float VoiceMasterLevel() {
    Lock l;
    return S().voiceLevel;
}

int32_t VoiceCreate() {
    Lock l;
    for (int32_t i = 0; i < kMaxVoices; ++i) {
        if (!S().voices[i].used) {
            S().voices[i] = Voice();
            S().voices[i].used = true;
            return i;
        }
    }
    return -1;
}

void VoiceDestroy(int32_t voice) {
    Lock l;
    if (ValidVoice(voice)) S().voices[voice] = Voice();
}

void VoicePlay(int32_t voice, const PcmWave* wave, bool loop) {
    Lock l;
    if (!ValidVoice(voice)) return;
    Voice& v = S().voices[voice];
    v.wave = wave;
    v.open = wave != nullptr;
    v.started = wave != nullptr;
    v.paused = false;
    v.ended = false;
    v.loop = loop;
    v.pos = 0;
    if (wave != nullptr) S().events.push_back(Event{S().mixed, false, wave->name});
}

void VoiceStop(int32_t voice) {
    Lock l;
    if (!ValidVoice(voice)) return;
    Voice& v = S().voices[voice];
    v.open = v.started = v.paused = v.ended = false;
    v.wave = nullptr;
    v.pos = 0;
}

void VoiceSetPaused(int32_t voice, bool paused) {
    Lock l;
    if (ValidVoice(voice)) S().voices[voice].paused = paused;
}

bool VoiceIsPaused(int32_t voice) {
    Lock l;
    return ValidVoice(voice) && S().voices[voice].open && S().voices[voice].paused;
}

bool VoiceIsPlaying(int32_t voice) {
    Lock l;
    if (!ValidVoice(voice)) return false;
    const Voice& v = S().voices[voice];
    return v.open && v.started && !v.paused && !v.ended;
}

uint32_t VoiceGetPosition(int32_t voice) {
    Lock l;
    if (!ValidVoice(voice)) return 0;
    const Voice& v = S().voices[voice];
    if (v.wave == nullptr) return 0;
    const uint32_t frame = static_cast<uint32_t>(v.pos >> 32);
    return std::min(frame, v.wave->frames);
}

void VoiceSetParams(int32_t voice, float gainLeft, float gainRight, float rateHz) {
    Lock l;
    if (!ValidVoice(voice)) return;
    Voice& v = S().voices[voice];
    v.gainL = gainLeft;
    v.gainR = gainRight;
    v.rateHz = rateHz;
}

int32_t StreamCreate(uint32_t sampleRate, uint32_t channels, const char* name) {
    Lock l;
    for (int32_t i = 0; i < kMaxStreams; ++i) {
        Stream& s = S().streams[i];
        if (!s.used) {
            s = Stream();
            s.used = true;
            s.rate = sampleRate;
            s.channels = channels == 0 ? 1 : channels;
            s.name = name != nullptr ? name : "";
            return i;
        }
    }
    return -1;
}

void StreamDestroy(int32_t stream) {
    Lock l;
    if (ValidStream(stream)) S().streams[stream] = Stream();
}

void StreamPush(int32_t stream, const float* interleaved, uint32_t frames) {
    Lock l;
    if (!ValidStream(stream) || frames == 0) return;
    Stream& s = S().streams[stream];
    s.queue.insert(s.queue.end(), interleaved, interleaved + static_cast<size_t>(frames) * s.channels);
    if (!s.announced) {
        s.announced = true;
        S().events.push_back(Event{S().mixed, true, s.name});
    }
}

uint32_t StreamQueuedFrames(int32_t stream) {
    Lock l;
    if (!ValidStream(stream)) return 0;
    return static_cast<uint32_t>(S().streams[stream].queue.size() / S().streams[stream].channels);
}

void StreamSetGain(int32_t stream, float gain) {
    Lock l;
    if (ValidStream(stream)) S().streams[stream].gain = gain;
}

void StreamSetPaused(int32_t stream, bool paused) {
    Lock l;
    if (ValidStream(stream)) S().streams[stream].paused = paused;
}

void StreamClear(int32_t stream) {
    Lock l;
    if (!ValidStream(stream)) return;
    S().streams[stream].queue.clear();
    S().streams[stream].frac = 0;
}

void Advance(uint32_t frames) {
    Lock l;
    State& st = S();
    if (st.mode != Mode::Capture) return;
    while (frames > 0) {
        const uint32_t n = std::min(frames, kChunk);
        st.scratch.resize(2 * n);
        MixLocked(st.scratch.data(), n);
        frames -= n;
    }
}

void OnGameFrame(float dt) {
    uint32_t frames = 0;
    {
        Lock l;
        State& st = S();
        if (st.mode != Mode::Capture || !(dt > 0.0f)) return;
        st.carry += static_cast<double>(dt) * kOutputRate;
        frames = static_cast<uint32_t>(st.carry);
        st.carry -= frames;
    }
    Advance(frames);
}

void SetCapture(std::vector<float>* out) {
    Lock l;
    S().capture = out;
}

uint64_t MixedFrames() {
    Lock l;
    return S().mixed;
}

std::vector<Event> TakeEvents() {
    Lock l;
    std::vector<Event> out;
    out.swap(S().events);
    return out;
}

}  // namespace dotd::audio
