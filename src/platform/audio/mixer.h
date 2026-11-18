// mixer.h - the sound output that replaces MultiStream and cellAudio: a software mixer of PCM voices
// and streamed tracks into 48 kHz stereo. Platform code (new code, not a port). RWA's voices
// (platform/audio/rwa.h) and Bink's audio tracks (platform/video/bink.cpp) play through it.
//
// Two ways to run:
//   - Device: an SDL3 audio stream pulls the mix from the audio thread (real time).
//   - Capture: no device; the mix advances only when Advance() is called (headless runs and tests: the
//     game's sound manager calls dotd::audio::OnGameFrame(dt) once per frame). The mix can be kept for
//     inspection (SetCapture) and every voice or stream start is logged (TakeEvents).
// The mode comes from SetMode() or the environment variable DOTD_AUDIO (device, capture, off); the
// default is Device when SDL video is up (the game's window) and Capture otherwise (tests, --headless),
// and Capture when no audio device opens.
//
// Resampling is linear interpolation in 32.32 fixed point (deterministic); MultiStream's own resampler
// is not reproduced. Voices hold native-endian int16 PCM; streams take float frames.
#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace dotd::audio {

constexpr uint32_t kOutputRate = 48000;

enum class Mode { Off, Device, Capture };

// A block of PCM a voice plays from: native int16, interleaved when stereo. Owned by the caller; it must
// outlive every voice that plays it.
struct PcmWave {
    const int16_t* samples = nullptr;
    uint32_t frames = 0;
    uint32_t channels = 1;
    uint32_t sampleRate = 44100;
    std::string name;
};

void SetMode(Mode mode);  // before the first use (later calls reopen)
Mode GetMode();
void Init();              // idempotent; also done by the first call that needs it
void Shutdown();

// The port level (RwaPS3_SetPortLevel): scales the whole voice mix (not the streams: Bink has its own port).
void SetVoiceMasterLevel(float level);
float VoiceMasterLevel();

// ---- voices (one per RWA voice) -----------------------------------------------------------------
int32_t VoiceCreate();              // -1 when the table is full
void VoiceDestroy(int32_t voice);
// Starts `wave` from its first frame (loop: wraps forever). Stops what the voice played before.
void VoicePlay(int32_t voice, const PcmWave* wave, bool loop);
void VoiceStop(int32_t voice);      // the stream is closed (RwaPS3Voice_Stop)
void VoiceSetPaused(int32_t voice, bool paused);
bool VoiceIsPaused(int32_t voice);
// Playing: started, not paused, not past the end.
bool VoiceIsPlaying(int32_t voice);
uint32_t VoiceGetPosition(int32_t voice);  // frames into the wave
// gains per output channel (0..), playback rate in Hz (the wave's frames per second)
void VoiceSetParams(int32_t voice, float gainLeft, float gainRight, float rateHz);

// ---- streams (one per Bink audio track) ---------------------------------------------------------
int32_t StreamCreate(uint32_t sampleRate, uint32_t channels, const char* name);
void StreamDestroy(int32_t stream);
void StreamPush(int32_t stream, const float* interleaved, uint32_t frames);
uint32_t StreamQueuedFrames(int32_t stream);
void StreamSetGain(int32_t stream, float gain);
void StreamSetPaused(int32_t stream, bool paused);
void StreamClear(int32_t stream);

// ---- headless and tests ---------------------------------------------------------------------------
// Capture mode: mixes `frames` output frames now (no-op in the other modes).
void Advance(uint32_t frames);
// Called once per game frame by the sound manager (host hook, not in the original): in Capture mode
// advances the mix by dt seconds (fractions carried over).
void OnGameFrame(float dt);
// Keep the mixed output (interleaved stereo float) in `out` (null stops).
void SetCapture(std::vector<float>* out);
uint64_t MixedFrames();  // output frames mixed since Init

struct Event {
    uint64_t frame;   // output frame (MixedFrames) when the start was requested
    bool stream;      // false: a voice started a wave; true: a stream received its first data
    std::string name;
};
std::vector<Event> TakeEvents();

}  // namespace dotd::audio
