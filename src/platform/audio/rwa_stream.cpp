// rwa_stream.cpp - see rwa_stream.h.
#include "platform/audio/rwa_stream.h"

#include <algorithm>
#include <string>
#include <vector>
#ifdef __EMSCRIPTEN__
#include <atomic>
#include <chrono>
#include <memory>
#include <thread>
#endif

#include "platform/audio/mixer.h"
#include "platform/audio/rws.h"
#include "platform/cell/fs.h"
#include "platform/config.h"
#include "platform/hostfs.h"
#include "platform/log.h"

namespace {

// Fitted to RPCS3 (see rwa_stream.h): the 9th frame after SetSource sees STOPPED (8 frame steps after the one that
// takes the request); the position is above 0 after 4 steps of play (some captures: 5); STOPPED 0.029 s after the
// item's blocks have played (between 0.024 and 0.034 for the three items).
constexpr float kOpenSeconds = 7.5f / 60.0f;
constexpr float kPrerollSeconds = 3.5f / 60.0f;
constexpr float kEndSeconds = 0.029f;

struct Item {
    float seconds = 0.0f;  // the whole blocks
};

// An item's samples, read and decoded whole (a music track is 45 MB of PCM, a speech line an ATRAC3 segment).
struct ItemSamples {
    std::vector<int16_t> pcm;
    uint32_t channels = 0;
    uint32_t sampleRate = 0;
    std::string name;
};

bool DecodeItem(const std::string& hostPath, uint32_t item, ItemSamples* out) {
    dotd::audio::RwsFile file;
    if (!file.Open(hostPath) || item >= file.segments.size()) return false;
    bool ok = false;
    if (file.IsAtrac3(0)) {
        ok = file.DecodeAtrac3(item, 0, &out->pcm);
    } else if (file.Select(item, 0)) {
        out->pcm.resize(static_cast<size_t>(file.TotalFrames()) * file.layers[0].channels);
        out->pcm.resize(static_cast<size_t>(file.Read(out->pcm.data(), static_cast<uint32_t>(file.TotalFrames()))) *
                        file.layers[0].channels);
        ok = true;
    }
    if (!ok || out->pcm.empty()) return false;
    out->channels = file.layers[0].channels;
    out->sampleRate = file.layers[0].sampleRate;
    out->name = file.name + "/" + file.segments[item].name;
    return true;
}

#ifdef __EMSCRIPTEN__
// The web build: the item is read (over HTTP) and decoded on a thread of its own, since the frame cannot wait
// half a second for a music track; the voice starts when the samples are there.
struct ItemLoad {
    ItemSamples samples;
    bool ok = false;
    std::atomic<bool> done{false};
};

// The web build, a PCM source (the music: tracks of 30 to 50 MB): not loaded whole but played as it is read, on
// a mixer stream a thread keeps two seconds ahead. The sound starts with the first quarter second read instead
// of after the whole track has come over the network.
struct Feed {
    std::atomic<bool> stop{false};
    int32_t stream = -1;  // the mixer stream; this thread destroys it once the player has stopped the feed
};

void FeedThread(std::shared_ptr<Feed> feed, std::string hostPath, uint32_t item, bool loop) {
    dotd::audio::RwsFile file;
    // The web pack's re-encoded samples (Vorbis, "<file>.OGV": dotd/web/pack_music.py) when the file has them: the
    // pack then holds only the RWS file's header.
    dotd::audio::OgvFile music;
    dotd::platform::hostfs::Info info;
    const bool reencoded = dotd::platform::hostfs::Stat(hostPath + ".OGV", &info) && !info.isDir &&
                           music.Open(hostPath + ".OGV") && music.Select(item);
    if (reencoded || (file.Open(hostPath) && file.Select(item, 0))) {
        const uint32_t channels = reencoded ? music.channels : file.layers[0].channels;
        const uint32_t rate = reencoded ? music.sampleRate : file.layers[0].sampleRate;
        const uint32_t chunk = rate / 4;
        std::vector<int16_t> pcm(static_cast<size_t>(chunk) * channels);
        std::vector<float> samples(pcm.size());
        bool readAny = false;
        bool logged = false;
        const auto start = std::chrono::steady_clock::now();
        while (!feed->stop.load()) {
            if (dotd::audio::StreamQueuedFrames(feed->stream) > rate * 2) {
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                continue;
            }
            const uint32_t got = reencoded ? music.Read(samples.data(), chunk) : file.Read(pcm.data(), chunk);
            if (got == 0) {  // the item's end: again from its start when it loops
                if (!loop || !readAny || !(reencoded ? music.Select(item) : file.Select(item, 0))) break;
                readAny = false;
                continue;
            }
            readAny = true;
            if (!logged) {
                logged = true;
                DOTD_LOG("rwa stream: %s item %u plays as it is read%s (first samples after %.0f ms)", hostPath.c_str(), item,
                         reencoded ? ", re-encoded" : "",
                         std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count());
            }
            if (!reencoded) {
                for (size_t i = 0; i < static_cast<size_t>(got) * channels; ++i) samples[i] = static_cast<float>(pcm[i]) * (1.0f / 32768.0f);
            }
            dotd::audio::StreamPush(feed->stream, samples.data(), got);
        }
    }
    while (!feed->stop.load()) std::this_thread::sleep_for(std::chrono::milliseconds(50));  // (what is queued plays out)
    dotd::audio::StreamDestroy(feed->stream);
}
#endif

}  // namespace

struct RwaStreamPlayer {
    RwaOutput* output = nullptr;
    uint32_t state = kRwaStreamNoMedia;
    // requests, taken by the next Advance
    bool sourceRequest = false;
    std::string sourcePath;  // empty: close
    uint32_t command = 0;
    bool selectRequest = false;
    RwaStreamPosition select = {};
    // the source
    std::string hostPath;
    std::vector<Item> items;
    float stateSeconds = 0.0f;  // in OPENING
    // playback
    uint32_t item = 0;
    float startOffset = 0.0f;  // seconds into the item where the play starts
    float elapsed = 0.0f;      // seconds since the play started (the preroll included)
    bool loop = false;
    float volume = 1.0f;       // +0x120
    float itemVolume = 1.0f;
    // the mixer
    int32_t voice = -1;
    dotd::audio::PcmWave wave;
    std::vector<int16_t> pcm;
    uint32_t pcmItem = 0xffffffffu;
#ifdef __EMSCRIPTEN__
    std::shared_ptr<ItemLoad> load;  // the item's samples on their way (see ItemLoad)
    std::shared_ptr<Feed> feed;      // a PCM source playing as it is read (see Feed)
    bool pcmSource = false;          // the source's first layer is 16-bit PCM
    uint32_t sourceRate = 0;
    uint32_t sourceChannels = 0;
#endif
};

namespace {

std::vector<RwaStreamPlayer*>& Players() {
    static std::vector<RwaStreamPlayer*> players;
    return players;
}
dotd::audio::RwaStreamReplaySource g_replaySource = nullptr;  // DEBUG (DOTD_REPLAY)

// The source path as the PS3 resolves it: a /dev_bdvd or /app_home path through the file system shim, else relative
// to the game's USRDIR (the K data root is empty).
std::string HostPath(const std::string& path) {
    std::string host;
    bool writable = false;
    if (!path.empty() && path[0] == '/' && dotd::platform::MapPs3Path(path.c_str(), &host, &writable)) return host;
    const std::string& root = dotd::platform::GetConfig().usrdir;
    if (root.empty()) return path;
    return root + "/" + path;
}

// The items' lengths: whole blocks of the first layer at its byte rate (ATRAC3: frames of 1024 samples; PCM: 16-bit).
void OpenSource(RwaStreamPlayer* p) {
    p->items.clear();
    p->pcmItem = 0xffffffffu;
    dotd::audio::RwsFile file;
    p->hostPath = HostPath(p->sourcePath);
    if (!file.Open(p->hostPath) || file.layers.empty()) {
        DOTD_LOG("rwa stream: cannot open %s", p->hostPath.c_str());
        return;
    }
    const dotd::audio::RwsLayer& y = file.layers[0];
#ifdef __EMSCRIPTEN__
    p->pcmSource = file.IsPcm16(0);
    p->sourceRate = y.sampleRate;
    p->sourceChannels = y.channels;
#endif
    double bytesPerSecond = 0.0;
    if (file.IsAtrac3(0)) {
        bytesPerSecond = static_cast<double>(y.frameSize) * static_cast<double>(y.sampleRate) / 1024.0;
    } else if (file.IsPcm16(0)) {
        bytesPerSecond = static_cast<double>(y.sampleRate) * 2.0 * static_cast<double>(y.channels);
    }
    for (const dotd::audio::RwsSegment& s : file.segments) {
        Item item;
        if (bytesPerSecond > 0.0 && y.blockUsable != 0) {
            const uint64_t blocks = (static_cast<uint64_t>(s.usable[0]) + y.blockUsable - 1) / y.blockUsable;
            item.seconds = static_cast<float>(static_cast<double>(blocks * y.blockUsable) / bytesPerSecond);
        }
        p->items.push_back(item);
    }
}

float ItemSeconds(const RwaStreamPlayer* p) { return p->item < p->items.size() ? p->items[p->item].seconds : 0.0f; }

void StopVoice(RwaStreamPlayer* p) {
#ifdef __EMSCRIPTEN__
    if (p->feed) {
        dotd::audio::StreamSetPaused(p->feed->stream, true);  // silent at once; the feed's thread removes the stream
        p->feed->stop.store(true);
        p->feed.reset();
    }
#endif
    if (p->voice < 0) return;
    dotd::audio::VoiceStop(p->voice);
    dotd::audio::VoiceDestroy(p->voice);
    p->voice = -1;
}

void PushGain(RwaStreamPlayer* p) {
#ifdef __EMSCRIPTEN__
    if (p->feed) {  // (a mixer stream is not scaled by the voices' master level: applied here)
        dotd::audio::StreamSetGain(p->feed->stream, p->volume * p->itemVolume * dotd::audio::VoiceMasterLevel());
    }
#endif
    if (p->voice < 0) return;
    const float gain = p->volume * p->itemVolume;
    dotd::audio::VoiceSetParams(p->voice, gain, gain, static_cast<float>(p->wave.sampleRate));
}

// The item's samples on a mixer voice from the current output position (decoded once per item).
void StartVoice(RwaStreamPlayer* p) {
    if (p->voice >= 0 || dotd::audio::GetMode() == dotd::audio::Mode::Off) return;
#ifdef __EMSCRIPTEN__
    if (p->feed) {
        PushGain(p);  // (follows the master level)
        return;
    }
    if (p->pcmSource && p->sourceRate != 0) {
        std::shared_ptr<Feed> feed = std::make_shared<Feed>();
        feed->stream = dotd::audio::StreamCreate(p->sourceRate, p->sourceChannels, "music");
        if (feed->stream < 0) return;
        p->feed = feed;
        PushGain(p);
        std::thread(FeedThread, feed, p->hostPath, p->item, p->loop).detach();
        return;
    }
#endif
    if (p->pcmItem != p->item) {
        p->pcmItem = p->item;
        p->pcm.clear();
        p->wave = dotd::audio::PcmWave();
#ifdef __EMSCRIPTEN__
        std::shared_ptr<ItemLoad> load = std::make_shared<ItemLoad>();
        p->load = load;
        std::thread([load, path = p->hostPath, item = p->item]() {
            load->ok = DecodeItem(path, item, &load->samples);
            load->done.store(true);
        }).detach();
#else
        ItemSamples samples;
        if (DecodeItem(p->hostPath, p->item, &samples)) {
            p->pcm.swap(samples.pcm);
            p->wave.samples = p->pcm.data();
            p->wave.channels = samples.channels;
            p->wave.frames = static_cast<uint32_t>(p->pcm.size() / p->wave.channels);
            p->wave.sampleRate = samples.sampleRate;
            p->wave.name = samples.name;
        }
#endif
    }
#ifdef __EMSCRIPTEN__
    if (p->load) {
        if (!p->load->done.load()) return;  // (asked again by the next Step)
        if (p->load->ok) {
            p->pcm.swap(p->load->samples.pcm);
            p->wave.samples = p->pcm.data();
            p->wave.channels = p->load->samples.channels;
            p->wave.frames = static_cast<uint32_t>(p->pcm.size() / p->wave.channels);
            p->wave.sampleRate = p->load->samples.sampleRate;
            p->wave.name = p->load->samples.name;
        }
        p->load.reset();
    }
#endif
    if (p->wave.frames == 0) return;
    p->voice = dotd::audio::VoiceCreate();
    if (p->voice < 0) return;
    PushGain(p);
    dotd::audio::VoicePlay(p->voice, &p->wave, p->loop);
}

// GetCurrentItem's output: the seconds played, once the preroll is over.
bool HasOutput(const RwaStreamPlayer* p) {
    switch (p->state) {
        case kRwaStreamPlaying:
        case kRwaStreamPausing:
        case kRwaStreamPaused:
        case kRwaStreamStarved:
            return p->elapsed > kPrerollSeconds;
        default:
            return false;
    }
}

void TakeRequests(RwaStreamPlayer* p, bool* moved) {
    if (p->sourceRequest) {
        p->sourceRequest = false;
        StopVoice(p);
        p->command = 0;
        if (p->sourcePath.empty()) {
            p->items.clear();
            p->state = kRwaStreamNoMedia;
        } else {
            OpenSource(p);
            p->state = kRwaStreamOpening;
            p->stateSeconds = 0.0f;
        }
        p->item = 0;
        p->elapsed = 0.0f;
        *moved = true;
    }
    if (p->selectRequest && p->state != kRwaStreamOpening && p->state != kRwaStreamNoMedia) {
        p->selectRequest = false;
        p->item = p->select.item;
        p->startOffset = p->select.unit == 2 ? 0.0f : p->select.offset;  // samples are not used by the K code
        if (p->state == kRwaStreamPlaying || p->state == kRwaStreamPaused || p->state == kRwaStreamPausing) {
            StopVoice(p);
            p->elapsed = 0.0f;
        }
    }
    if (p->state == kRwaStreamOpening) return;  // a command waits for the source (a replay may answer STOPPED early)
    const uint32_t command = p->command;
    p->command = 0;
    switch (command) {
        case kRwaStreamCommandPlay:
            if (p->state == kRwaStreamStopped) {
                p->elapsed = 0.0f;
                p->state = kRwaStreamPlaying;
                *moved = true;
            } else if (p->state == kRwaStreamPaused || p->state == kRwaStreamPausing) {
                if (p->voice >= 0) dotd::audio::VoiceSetPaused(p->voice, false);
#ifdef __EMSCRIPTEN__
                if (p->feed) dotd::audio::StreamSetPaused(p->feed->stream, false);
#endif
                p->state = kRwaStreamPlaying;
                *moved = true;
            }
            break;
        case kRwaStreamCommandStop:
            if (p->state == kRwaStreamPlaying || p->state == kRwaStreamPaused || p->state == kRwaStreamPausing ||
                p->state == kRwaStreamStarved) {
                StopVoice(p);
                p->state = kRwaStreamStopping;
                *moved = true;
            }
            break;
        case kRwaStreamCommandPause:
            if (p->state == kRwaStreamPlaying) {
                if (p->voice >= 0) dotd::audio::VoiceSetPaused(p->voice, true);
#ifdef __EMSCRIPTEN__
                if (p->feed) dotd::audio::StreamSetPaused(p->feed->stream, true);
#endif
                p->state = kRwaStreamPausing;
                *moved = true;
            } else if (p->state == kRwaStreamStopped) {
                // A start-paused stream (SoundStream's StartPaused request: Opening -> Paused): the player primes the
                // item and waits paused for Play. Staying STOPPED made SoundStream_StatePaused drop to MediaStopped
                // the next frame, so a cinematic's speech never started (G +8942: the original holds the stream
                // paused, status 4, until the cinematic plays it at +9115).
                p->elapsed = kPrerollSeconds;  // primed while paused: the output starts with Play
                p->state = kRwaStreamPaused;
                *moved = true;
            }
            break;
        default:
            break;
    }
}

void Step(RwaStreamPlayer* p, float seconds) {
    switch (p->state) {
        case kRwaStreamOpening:
            p->stateSeconds += seconds;
            if (p->stateSeconds >= kOpenSeconds) {
                p->state = kRwaStreamStopped;
                p->startOffset = 0.0f;
            }
            break;
        case kRwaStreamStopping:
            p->state = kRwaStreamStopped;
            break;
        case kRwaStreamPausing:
            p->state = kRwaStreamPaused;
            break;
        case kRwaStreamPlaying: {
            p->elapsed += seconds;
            const float length = ItemSeconds(p) - p->startOffset;
            if (p->elapsed >= length + kEndSeconds) {
                if (p->loop && length > 0.0f) {
                    p->elapsed -= length;
                    p->startOffset = 0.0f;
                } else {
                    StopVoice(p);
                    p->state = kRwaStreamStopped;
                    p->startOffset = 0.0f;
                    break;
                }
            }
            if (p->elapsed > kPrerollSeconds) StartVoice(p);
            break;
        }
        default:
            break;
    }
}

}  // namespace

RwaStreamPlayer* RwaStreamPlayer_Create(RwaOutput* output) {
    RwaStreamPlayer* p = new RwaStreamPlayer();
    p->output = output;
    Players().push_back(p);
    return p;
}

void RwaStreamPlayer_Destroy(RwaStreamPlayer* player) {
    if (player == nullptr) return;
    StopVoice(player);
    std::vector<RwaStreamPlayer*>& players = Players();
    players.erase(std::remove(players.begin(), players.end(), player), players.end());
    delete player;
}

uint32_t RwaStreamPlayer_GetState(const RwaStreamPlayer* player) {
    dotd::audio::RwaStreamReplayAnswer answer = {-1, false, -1.0f, false, 0.0f, false};
    if (g_replaySource != nullptr && g_replaySource(player, &answer) && answer.state >= 0) {  // DEBUG (DOTD_REPLAY)
        return static_cast<uint32_t>(answer.state);
    }
    return player->state;
}

void RwaStreamPlayer_SetCommand(RwaStreamPlayer* player, uint32_t command) { player->command = command; }

void RwaStreamPlayer_SetSource(RwaStreamPlayer* player, const RwaStreamSource* source) {
    player->sourceRequest = true;
    player->sourcePath = source != nullptr && source->path != nullptr ? source->path : "";
    player->selectRequest = false;
}

uint32_t RwaStreamPlayer_GetItemCount(const RwaStreamPlayer* player) {
    return player->state == kRwaStreamOpening || player->state == kRwaStreamNoMedia ? 0u
                                                                                     : static_cast<uint32_t>(player->items.size());
}

void RwaStreamPlayer_SelectItem(RwaStreamPlayer* player, const RwaStreamSelect* select) {
    player->select = *select->position;
    player->selectRequest = true;
}

void RwaStreamPlayer_GetCurrentItem(const RwaStreamPlayer* player, RwaStreamPosition* position) {
    bool output = HasOutput(player);
    float seconds = player->startOffset + (player->elapsed - kPrerollSeconds);
    if (!(seconds > 0.0f)) seconds = 1.0e-3f;  // DEBUG (DOTD_REPLAY): an output the replay started early
    dotd::audio::RwaStreamReplayAnswer answer = {-1, false, -1.0f, true, seconds, output};
    const bool replayed = g_replaySource != nullptr && g_replaySource(player, &answer);  // DEBUG (DOTD_REPLAY)
    if (replayed) output = answer.output;
    if (!output) {
        position->item = 0;
        position->offset = 0.0f;
        return;
    }
    if (replayed && answer.position >= 0.0f) seconds = answer.position;  // DEBUG (DOTD_REPLAY): the original's position
    if (position->unit == 1) {
        position->offset = seconds;
    } else if (position->unit == 2) {
        position->offset = seconds * 48000.0f;
    }
    if (position->by == 3) position->item = player->item;
}

float RwaStreamPlayer_GetVolume(const RwaStreamPlayer* player) { return player->volume; }

void RwaStreamPlayer_SetVolume(float volume, RwaStreamPlayer* player) {
    player->volume = volume;
    PushGain(player);
}

void RwaStreamPlayer_SetItemVolume(RwaStreamPlayer* player, const RwaStreamItemVolume* volume) {
    player->itemVolume = volume->volume;
    PushGain(player);
}

void RwaStreamPlayer_SetLoop(RwaStreamPlayer* player, uint8_t loop) { player->loop = loop != 0; }

namespace dotd::audio {

void RwaStreamPlayers_Advance(float seconds) {
    for (RwaStreamPlayer* p : Players()) {
        bool moved = false;
        TakeRequests(p, &moved);
        if (!moved) Step(p, seconds);
    }
}

void RwaStreamPlayer_SetReplaySource(RwaStreamReplaySource source) { g_replaySource = source; }

}  // namespace dotd::audio
