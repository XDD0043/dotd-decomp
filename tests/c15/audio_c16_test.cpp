// audio_c16_test - checkpoint C1.6, family audio: sound out, headless (the platform mixer in capture
// mode: mixed per game frame, every voice and stream start logged with its output frame).
//
//  1. The data: a music stream (MUSIC/0/STRA0.RWS: 48 kHz stereo PCM in 0x8800-byte blocks) decodes, the
//     first 100 ms have the expected sample count and are not silent; LVL000's wave dictionary gives all
//     27 CKWaves their wave (16-bit PCM, the CKWave's sample rate and length).
//  2. The front-end sequence (as boot_sequence_test: copyrights, logos, press start, START, main menu)
//     plays the logo videos' Bink audio tracks (PS3_071, PS3_072) through mixer streams, and the decoded
//     track has sound.
//  3. The main menu's music: CKS08Menu_PlayLoopSounds_maybe (0x5573b0) does SetLoop(1) + Play(0) on the
//     menu dictionary's sounds 0 and 1, music_outgame_l/r.wav. The test makes the same calls (the menu
//     port is family menus) and checks the K path: an instance per sound in the playing state, a voice,
//     the wave started in the mixer, the left wave on the left, the volume (0.35 x the menu volume); then
//     Sound_Stop with the fade-out stops the instances.
#include <cmath>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include "Spyro2008/logic/CKS08GameManager.h"
#include "boot_helper.h"
#include "k2000/dictionaries/CKSoundDictionary.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/logic/sound/CKWave.h"
#include "k2000/managers/CKSoundManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/sound/SoundInstance.h"
#include "k2000/sound/SoundVoice.h"
#include "k2000/sound/SoundVoiceManager.h"
#include "platform/audio/mixer.h"
#include "platform/audio/rwa.h"
#include "platform/audio/rws.h"
#include "platform/cell/fs.h"
#include "platform/cell/pad.h"
#include "platform/video/bink.h"

namespace {

bool g_startHeld = false;

bool TestPad(int port, uint16_t words[24]) {
    if (port != 0) return false;
    std::memset(words, 0, 24 * sizeof(uint16_t));
    words[CELL_PAD_BTN_OFFSET_DIGITAL1] = g_startHeld ? CELL_PAD_CTRL_START : 0;
    for (int i = CELL_PAD_BTN_OFFSET_ANALOG_RIGHT_X; i <= CELL_PAD_BTN_OFFSET_ANALOG_LEFT_Y; ++i) words[i] = 0x80;
    return true;
}

std::string HostPath(const char* usrdirRelative) {
    std::string host;
    bool writable = false;
    const std::string ps3 = std::string("/dev_bdvd/PS3_GAME/USRDIR/") + usrdirRelative;
    if (!dotd::platform::MapPs3Path(ps3.c_str(), &host, &writable)) return std::string();
    return host;
}

struct Peak {
    float left = 0.0f, right = 0.0f;
    double sumLeft = 0.0, sumRight = 0.0;
};
Peak Measure(const std::vector<float>& mix, size_t fromFrame) {
    Peak p;
    for (size_t i = fromFrame * 2; i + 1 < mix.size(); i += 2) {
        p.left = std::max(p.left, std::fabs(mix[i]));
        p.right = std::max(p.right, std::fabs(mix[i + 1]));
        p.sumLeft += std::fabs(mix[i]);
        p.sumRight += std::fabs(mix[i + 1]);
    }
    return p;
}

bool HasEvent(const std::vector<dotd::audio::Event>& events, const char* part, uint64_t* frame) {
    for (const dotd::audio::Event& e : events) {
        if (e.name.find(part) != std::string::npos) {
            if (frame != nullptr) *frame = e.frame;
            return true;
        }
    }
    return false;
}

// 1a. A music RWS: the container and the first 100 ms.
void TestRws() {
    dotd::audio::RwsFile rws;
    const std::string path = HostPath("MUSIC/0/STRA0.RWS");
    C15_CHECK(!path.empty() && rws.Open(path));
    if (rws.segments.empty()) return;
    C15_CHECK(rws.segments.size() == 1 && rws.layers.size() == 1);
    C15_CHECK(rws.IsPcm16(0));
    C15_CHECK(rws.layers[0].sampleRate == 48000 && rws.layers[0].channels == 2);
    C15_CHECK(rws.layers[0].blockSize == 0x8800 && rws.layers[0].blockUsable == 0x801c);
    const uint64_t total = rws.TotalFrames();
    C15_CHECK(total == rws.segments[0].usable[0] / 4);
    std::vector<int16_t> pcm(4800 * 2);
    const uint32_t got = rws.Read(pcm.data(), 4800);
    int peak = 0;
    for (int16_t s : pcm) peak = std::max(peak, std::abs(static_cast<int>(s)));
    std::printf("audio: STRA0.RWS \"%s\": %llu frames (%.1f s), first 100 ms: %u frames, peak %d\n", rws.name.c_str(),
                static_cast<unsigned long long>(total), static_cast<double>(total) / 48000.0, got, peak);
    C15_CHECK(got == 4800);
    C15_CHECK(peak > 100);
    // the block boundary: the read continues across the padding (frames 8199 / 8200 of block 0 / 1)
    std::vector<int16_t> rest(8192 * 2);
    C15_CHECK(rws.Read(rest.data(), 8192) == 8192);
}

// 1b. LVL000's wave dictionary (after the boot): every CKWave has its wave.
void TestWaveDictionary() {
    SoundVoiceManager* vm = g_pEngine->m_soundManager->m_pVoiceManager;
    C15_CHECK(vm->m_ui32NbSoundDictionary >= 1);
    uint32_t waves = 0, matching = 0;
    for (uint32_t d = 0; d < vm->m_ui32NbSoundDictionary; ++d) {
        CKSoundDictionary* dict = static_cast<CKSoundDictionary*>(vm->m_apSoundDictionary[d]);
        if (dict == nullptr || dict->m_pRwSoundDictionary == nullptr) continue;
        std::printf("audio: wave dictionary \"%s\": %u waves, %u CKWaves\n", dict->m_pRwSoundDictionary->name.c_str(),
                    RwaWaveDict_GetWaveCount(dict->m_pRwSoundDictionary), dict->m_ui32NbSound);
        for (uint32_t i = 0; i < dict->m_ui32NbSound; ++i) {
            CKWave* wave = static_cast<CKWave*>(dict->m_apKWave[i]);
            ++waves;
            if (wave->m_pRwaWave == nullptr) continue;
            const RwaWave* w = wave->m_pRwaWave;
            const float length = static_cast<float>(w->frames) / static_cast<float>(w->sampleRate);
            if (w->sampleRate == wave->m_ui16SampleRate && std::fabs(length - wave->m_fLength) < 0.01f) ++matching;
        }
    }
    std::printf("audio: %u CKWaves, %u with a wave of the same rate and length\n", waves, matching);
    C15_CHECK(waves == 27 && matching == 27);
}

CKSound* FindSoundByWave(const char* part) {
    SoundVoiceManager* vm = g_pEngine->m_soundManager->m_pVoiceManager;
    for (uint32_t i = 0; i < vm->m_vpSounds.m_ui32NbUsedElt; ++i) {
        CKSound* s = vm->m_vpSounds.m_pBlock[i];
        if (s->m_pKWave != nullptr && s->m_pKWave->m_pRwaWave != nullptr &&
            s->m_pKWave->m_pRwaWave->name.find(part) != std::string::npos) {
            return s;
        }
    }
    return nullptr;
}

}  // namespace

int main() {
    std::setvbuf(stdout, nullptr, _IONBF, 0);
    dotd::audio::SetMode(dotd::audio::Mode::Capture);
    std::vector<float> mix;
    dotd::audio::SetCapture(&mix);
    dotd::platform::SetPadSource(&TestPad);
    if (!c15::BootToFrontEnd()) {
        std::printf("audio_c16: no game data configured; skipped\n");
        return 77;
    }
    TestRws();
    TestWaveDictionary();

    // 2. The front-end sequence with its videos' audio.
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    uint32_t frame = 0;
    std::vector<dotd::audio::Event> events;
    while (frame < 3000 && manager->m_gameState.m_ui8Current != 5) {
        c15::RunFrame();
        ++frame;
    }
    for (uint32_t i = 0; i < 60; ++i, ++frame) c15::RunFrame();
    g_startHeld = true;
    for (uint32_t i = 0; i < 6; ++i, ++frame) c15::RunFrame();
    g_startHeld = false;
    for (uint32_t i = 0; i < 600 && manager->m_gameState.m_ui8Current != 6; ++i, ++frame) c15::RunFrame();
    for (uint32_t i = 0; i < 30; ++i, ++frame) c15::RunFrame();
    for (const dotd::audio::Event& e : dotd::audio::TakeEvents()) events.push_back(e);
    for (const dotd::audio::Event& e : events) {
        std::printf("audio: %s \"%s\" starts at output frame %llu (%.2f s)\n", e.stream ? "stream" : "voice", e.name.c_str(),
                    static_cast<unsigned long long>(e.frame), static_cast<double>(e.frame) / 48000.0);
    }
    uint64_t logo1 = 0, logo2 = 0;
    C15_CHECK(manager->m_gameState.m_ui8Current == 6);
    C15_CHECK(HasEvent(events, "PS3_071.VID#0", &logo1));
    C15_CHECK(HasEvent(events, "PS3_072.VID#0", &logo2));
    C15_CHECK(logo2 > logo1);
    // the logos' audio is not silent and the whole mix stayed in range
    const Peak videoPeak = Measure(mix, static_cast<size_t>(logo1));
    std::printf("audio: mix since PS3_071: peak L %.3f R %.3f, %zu frames mixed\n", videoPeak.left, videoPeak.right,
                mix.size() / 2);
    C15_CHECK(videoPeak.left > 0.01f && videoPeak.right > 0.01f && videoPeak.left <= 1.0f);
    C15_CHECK(mix.size() / 2 + 2000 > static_cast<size_t>(frame) * 800);  // 800 output frames per 1/60 s

    // 3. The main menu's music loops, as CKS08Menu_PlayLoopSounds_maybe plays them.
    CKSound* left = FindSoundByWave("music_outgame_l");
    CKSound* right = FindSoundByWave("music_outgame_r");
    C15_CHECK(left != nullptr && right != nullptr);
    if (left != nullptr && right != nullptr) {
        std::printf("audio: music_outgame_l: flags 0x%x pan %.2f volume %.2f fade in %.2f out %.2f pos (%.2f %.2f %.2f)\n",
                    left->m_SoundFlags, left->m_fPan, left->m_fVolume, left->m_fFadeInTime, left->m_fFadeOutTime,
                    left->m_v3LeafPosition.x, left->m_v3LeafPosition.y, left->m_v3LeafPosition.z);
        for (CKSound* s : {left, right}) {
            if (CKSound_IsPlaying(s) == 0) {
                CKSound_SetLoop(s, 1);
                CKSound_Play(0.0f, s);
            }
        }
        C15_CHECK(left->CountInstances() == 1 && right->CountInstances() == 1);
        const size_t before = mix.size() / 2;
        for (uint32_t i = 0; i < 120; ++i, ++frame) c15::RunFrame();
        std::vector<dotd::audio::Event> later = dotd::audio::TakeEvents();
        // The main menu starts them itself now (CKS08Menu_PlayLoopSounds_maybe, C1.6 menus): their start events
        // are then among the earlier ones and the Play above was skipped (already playing).
        C15_CHECK((HasEvent(later, "music_outgame_l.wav", nullptr) || HasEvent(events, "music_outgame_l.wav", nullptr)) &&
                  (HasEvent(later, "music_outgame_r.wav", nullptr) || HasEvent(events, "music_outgame_r.wav", nullptr)));
        SoundInstance* il = left->GetInstanceAt(0);
        SoundInstance* ir = right->GetInstanceAt(0);
        C15_CHECK(il != nullptr && ir != nullptr);
        if (il != nullptr && ir != nullptr) {
            std::printf("audio: instances: state %d/%d, voice %p/%p, volume %.3f/%.3f, rate %.0f Hz\n", il->m_state, ir->m_state,
                        static_cast<void*>(il->m_pVoice), static_cast<void*>(ir->m_pVoice), il->m_volumeRamp[2],
                        ir->m_volumeRamp[2], il->m_fPlaybackRate);
            C15_CHECK(il->m_state == SoundInstance::kStatePlaying && ir->m_state == SoundInstance::kStatePlaying);
            C15_CHECK(il->m_pVoice != nullptr && ir->m_pVoice != nullptr);
            C15_CHECK(il->m_fPlaybackRate == 44100.0f);
            C15_CHECK(CKSound_IsPlaying(left) == 1);
            if (il->m_pVoice != nullptr && ir->m_pVoice != nullptr) {
                // pan -1 sits on the listener's right row (RenderWare's "right" points to the screen's left)
                const RwaVoice* vl = il->m_pVoice->m_pRwaVoice;
                const RwaVoice* vr = ir->m_pVoice->m_pRwaVoice;
                std::printf("audio: RWA voices: l gains %.3f/%.3f vol %.3f, r gains %.3f/%.3f vol %.3f\n", vl->gainLeft,
                            vl->gainRight, vl->volume, vr->gainLeft, vr->gainRight, vr->volume);
                C15_CHECK(vl->gainLeft > 0.99f && vl->gainRight < 0.01f);
                C15_CHECK(vr->gainRight > 0.99f && vr->gainLeft < 0.01f);
                // music-flagged: the Musics type's current volume x GAME's 0.35 x 00GLC's 1.0 x the ramp
                C15_CHECK(std::fabs(vl->volume - 0.35f) < 0.001f);
            }
        }
        // only the music plays now: the left wave on the left, the right one on the right, both heard
        const Peak music = Measure(mix, before + 4800);
        std::printf("audio: music mix: peak L %.3f R %.3f, mean L %.4f R %.4f\n", music.left, music.right,
                    music.sumLeft / ((mix.size() / 2) - before), music.sumRight / ((mix.size() / 2) - before));
        C15_CHECK(music.left > 0.01f && music.right > 0.01f);
        // Stop with the fade-out (CKSound_MessageProc 0x101 / Sound_Stop(0)): fade-out state, then stopped and
        // detached within the fade-out time.
        Sound_Stop(left, 0);
        Sound_Stop(right, 0);
        const float fade = std::max(left->m_fFadeOutTime, right->m_fFadeOutTime);
        for (uint32_t i = 0; i < static_cast<uint32_t>(fade * 60.0f) + 10; ++i, ++frame) c15::RunFrame();
        C15_CHECK(left->CountInstances() == 0 && right->CountInstances() == 0);
        C15_CHECK(CKSound_IsPlaying(left) == 0);
    }

    dotd::platform::SetPadSource(nullptr);
    dotd::audio::SetCapture(nullptr);
    c15::Shutdown();
    if (c15::g_failures == 0) std::printf("audio_c16: all tests passed\n");
    return c15::g_failures == 0 ? 0 : 1;
}
