// SpeechStreamModel.cpp - see SpeechStreamModel.h.
#include "k2000/sound/SpeechStreamModel.h"

#include <cstdio>
#include <map>
#include <string>
#include <vector>

#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/io/CKStreamObject.h"
#include "k2000/logic/ui/CLocManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"
#include "platform/audio/mixer.h"
#include "platform/audio/rws.h"
#include "platform/config.h"
#include "platform/log.h"

namespace speech_model {
namespace {

// Seconds from CKStreamObject_Play to the first sample played (the stream prepares: opens the file, fills the buffers)
// and from the end of the item to the player reporting the end. Fitted to the capture of LVL010's opening scene
// (outputs/remake/timeline/timeline-lvl010_cutscene_only-20261024-150606.json): the sekensor bloc that starts at
// frame 13409 completes at 13663; its single line is item 1, 3.627 s.
constexpr float kStartSeconds = 7.0f / 60.0f;
constexpr float kFinishSeconds = 25.0f / 60.0f;

struct Player {
    float playClock;     // the fixed game time CKStreamObject_Play was called at
    int32_t voice = -1;  // the mixer voice the item's decoded speech plays on, once the clock has started
};
std::map<const CKStreamObject*, Player> g_players;
ReplaySource g_replaySource = nullptr;  // DEBUG (DOTD_REPLAY)

float Now() { return g_pEngine->m_timeManager->m_pTime->m_afCurrentTime[IKTime::FIXED_GAME_TIME]; }

// The usable bytes of every segment of the speech file in use, read once per (level, voice).
struct SpeechFile {
    int32_t level = -1;
    int32_t voice = -1;
    std::map<int32_t, float> seconds;
    std::map<int32_t, dotd::audio::PcmWave> waves;  // decoded items (ATRAC3), on first use
    std::map<int32_t, std::vector<int16_t>> pcm;
};
SpeechFile g_file;

std::string SpeechPath(int32_t level, int32_t voice) {
    char path[512];
    std::snprintf(path, sizeof(path), "%s/LVL%03d/SPEECH/%d_PS30.RWS", dotd::platform::GetConfig().usrdir.c_str(), level, voice);
    return path;
}

// The decoded item of the file in use (null when it cannot be decoded). ItemSeconds has selected the file.
const dotd::audio::PcmWave* ItemWave(int32_t item) {
    const auto it = g_file.waves.find(item);
    if (it != g_file.waves.end()) return it->second.frames != 0 ? &it->second : nullptr;
    dotd::audio::PcmWave& wave = g_file.waves[item];
    dotd::audio::RwsFile file;
    std::vector<int16_t>& pcm = g_file.pcm[item];
    if (item >= 0 && file.Open(SpeechPath(g_file.level, g_file.voice)) && file.DecodeAtrac3(static_cast<uint32_t>(item), 0, &pcm) &&
        !pcm.empty()) {
        wave.samples = pcm.data();
        wave.channels = file.layers[0].channels;
        wave.frames = static_cast<uint32_t>(pcm.size() / wave.channels);
        wave.sampleRate = file.layers[0].sampleRate;
        wave.name = file.name + "/" + file.segments[static_cast<size_t>(item)].name;
        DOTD_LOG("speech: %s decoded (ATRAC3, %u frames at %u Hz)", wave.name.c_str(), wave.frames, wave.sampleRate);
    }
    return wave.frames != 0 ? &wave : nullptr;
}

void StopVoice(Player* player) {
    if (player->voice < 0) return;
    dotd::audio::VoiceStop(player->voice);
    dotd::audio::VoiceDestroy(player->voice);
    player->voice = -1;
}

// The decoded speech starts when the clock reaches the item's first sample (kStartSeconds after Play).
void StartVoiceIfDue(const CKStreamObject* stream, Player* player, float played) {
    if (player->voice >= 0 || played < 0.0f || played >= ItemSeconds(stream->m_unk1c)) return;
    const dotd::audio::PcmWave* wave = ItemWave(stream->m_unk1c);
    if (wave == nullptr) return;
    player->voice = dotd::audio::VoiceCreate();
    if (player->voice < 0) return;
    dotd::audio::VoiceSetParams(player->voice, 1.0f, 1.0f, static_cast<float>(wave->sampleRate));
    dotd::audio::VoicePlay(player->voice, wave, false);
}

}  // namespace

float ItemSeconds(int32_t item) {
    const int32_t level = g_pEngine->m_gameManager->m_currentLevel;
    const int32_t voice = static_cast<int32_t>(g_pEngine->m_locManager->GetVoiceLanguageIndex());
    if (g_file.level != level || g_file.voice != voice) {
        g_file = SpeechFile();
        g_file.level = level;
        g_file.voice = voice;
        dotd::audio::RwsFile file;
        if (file.Open(SpeechPath(level, voice)) && !file.layers.empty()) {
            const dotd::audio::RwsLayer& layer = file.layers[0];
            const double frameBytes = layer.frameSize != 0 ? layer.frameSize : 152;
            const double rate = layer.sampleRate != 0 ? layer.sampleRate : 48000;
            for (size_t s = 0; s < file.segments.size(); ++s) {
                g_file.seconds[static_cast<int32_t>(s)] =
                    static_cast<float>(static_cast<double>(file.segments[s].usable[0]) / frameBytes * 1024.0 / rate);
            }
        }
    }
    const auto it = g_file.seconds.find(item);
    return it != g_file.seconds.end() ? it->second : 0.0f;
}

void Play(const CKStreamObject* stream) {
    const auto it = g_players.find(stream);
    if (it != g_players.end()) StopVoice(&it->second);
    g_players[stream] = Player{Now()};
}

void Stop(const CKStreamObject* stream) {
    const auto it = g_players.find(stream);
    if (it == g_players.end()) return;
    StopVoice(&it->second);
    g_players.erase(it);
}

void SetReplaySource(ReplaySource source) { g_replaySource = source; }

bool HasPlayer(const CKStreamObject* stream) {
    ReplayAnswer answer;
    if (g_replaySource != nullptr && g_replaySource(stream, &answer)) return answer.hasPlayer;  // DEBUG (DOTD_REPLAY)
    return g_players.find(stream) != g_players.end();
}

void GetPlayback(const CKStreamObject* stream, int32_t* item, float* position) {
    ReplayAnswer answer;
    if (g_replaySource != nullptr && g_replaySource(stream, &answer) && (!answer.hasPlayer || !answer.positionStarted)) {
        *item = answer.hasPlayer ? 0xff : -1;  // DEBUG (DOTD_REPLAY): no player / preparing
        *position = 0.0f;
        return;
    }
    const auto it = g_players.find(stream);
    if (it == g_players.end()) {
        *item = -1;
        *position = 0.0f;
        return;
    }
    const float played = Now() - it->second.playClock - kStartSeconds;
    if (played < 0.0f) {
        *item = 0xff;
        *position = 0.0f;
        return;
    }
    StartVoiceIfDue(stream, &it->second, played);
    *item = stream->m_unk1c;
    *position = played;
}

bool IsFinished(const CKStreamObject* stream) {
    ReplayAnswer answer;
    if (g_replaySource != nullptr && g_replaySource(stream, &answer)) return answer.finished;  // DEBUG (DOTD_REPLAY)
    const auto it = g_players.find(stream);
    if (it == g_players.end()) return true;
    const float played = Now() - it->second.playClock - kStartSeconds;
    return played >= ItemSeconds(stream->m_unk1c) + kFinishSeconds;
}

}  // namespace speech_model
