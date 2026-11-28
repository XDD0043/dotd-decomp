// newgame_replay.inc - step 1, the replay player of newgame_test (included inside newgame_test.cpp's anonymous namespace).
//
// DOTD_REPLAY=<rpcs3.rec> (written by work/rpcs3_replay_record.py --skip-video): the run skips the opening video like
// DOTD_NEWGAME_SKIP=1 and, from the video's end (video_end: the first frame after which the loop is in mode 5 again, the
// recording's frame 0), plays the original's frames:
//   - at video_end the frame clock (IKTime: current / last / delta times, last exact time, state) and the main thread's
//     rand state (crt::ThreadRandState, the libc state of 0x95eac0) are set from the recording's frame 0;
//   - every later frame N gets the recorded KGetExactTime value of frame N (CKTime::KGetExactTime through
//     platform::SetExactTimeSource) and the recorded CellPadData words of port 0 (platform::SetPadSource; cellPadGetData
//     keeps its own change tracking, as the PS3's);
//   - the RWA player of the sekensor's current sekens' speech stream answers as the original's did
//     (dotd::audio::RwaStreamPlayer_SetReplaySource, see ReplayStreamAnswer): the third real-time input, which decides
//     when the opening cinematic gives control; while a streamed cinematic follows that speech, its position too (C2.8,
//     ReplayStreamPosition: from the recorded stream frames, so the stream's frames, keys and line ends are the original's);
//   - the run ends with the recording's last frame.
// The recording's frames before video_end (the level load, the level start, the video and its skip; "f" < 0) are not
// played: video_end's state is the same on both sides except what built up before it (see DECOMP_IMPL-2 step 1).
// DOTD_REPLAY_OUT=<dotd.rec> writes the same per-frame state as the recorder (frame 0 .. the last), the format below;
// work/replay_compare.py compares the two files. Platform debug code: nothing of it runs without DOTD_REPLAY.
//
// Format dotd-replay-1 (JSON lines): a header object ({"format", "source", ...}), one object per frame, a footer {"end": true}.
// Per frame: "f" frames since video_end, "counter" the render frame counter (u16 0xc29694), "mode" the loop mode, "gs" the
// game state (GameManager +0x2f5), "clock" {exact, exact_bits (float bits of IKTime +0x28), current[3], last[3], delta[3],
// state, scale (CTimeManager +0x10)}, "pad" {len, w: button[2..23], status (port 0), active (+0x04)}, "rand" {seed, init,
// last, table[32]}, "sector" (CKLevel +0x18), "focus" (hero group +0x66, signed), "blocked" (hero group +0xf8 bit 3),
// "cine" {bands (CKSrvCinematic +0x0c bit 0), scenes: [[index, flags +0x20, the elements' flags +0x14 & 5 as hex digits]] of
// the playing scenes}, "speech" (null without a current sekens, CKSrvSekensor +0x1c) {line +0x28, flags +0x14, state +0x74,
// and with a stream (+0x34): item (+0x1c), has (a player: +0x0c), finished (FUN_0011a538); the recorder also writes the
// SoundStream's ss_state +0x10 / ss_status +0x18}, "cstream" (recorder only, from 2026-11-14; absent without a running stream
// bloc) {time +0x30 (double), frame +0x64, flags +0xfc, sekens (+0xf0 set)} of the running CKCinematicStreamCpnt, "music"
// (C2.8, both sides from 2026-11-14; absent without the music service) {list: the playing play list (CKSrvMusic +0x14) as its
// index in the service's list array (+0x10; -1 none), enable (+0x2e), waiting / deferred: the per-priority slots +0x1c /
// +0x20 as list indices, and with a playing list: track (CKMusicPlayList +0x10, 255 none) and, with a track, has (its
// CKStreamObject's SoundStream +0x0c set), ss_state +0x10, ss_status +0x18}, "bonus" (C2.8, both sides from 2026-11-15; absent
// without the game manager's bonus group +0x10) [{type: the pool's bonus type (+0x2c), b: [{pos (the bonus node's frame
// modelling position), vel (+0x44), n (the ground bounces +0x50), st (the ground contact status +0x68), fly (+0x30 set: flying
// to its hero)}] (the pool's used list +0x40, next +0x20)}] (the group's child pools +0x18 / next +0x14), "camera" {ltm[16] (the main camera frame's LTM; words 3/7/11/15 are not floats), vw[2], near, far}, "heroes" [{id (KP3
// object id), hero (+0x24), ltm[16] (the hook node's frame), pos (+0x54c), vel (+0x127c), move_mode (+0x1808), flags
// (+0x358), node (its CAnimatedNode's id), states {control, anim, loco, action: [row index, state id]} (IKHkHero +0xac / +0x14c / +0x52c / +0xcc, the ids
// from the sorted rows +0xa0 / +0x140 / +0x520 / +0xc0), layers [{len, left, active, mode, ctrl}] (the blend slots +0x138)}],
// "enemies" [{id, npos (the hook node's frame LTM position), pos (+0x134), state (+0x3a0), aware (+0x538), react (+0x558),
// health (+0x258)}] (every CKHkS08Enemy, C2.7), "zones" [{id, n}] (every CKGrpFightZone: n = the enemies with a main state
// other than 0xff whose squad (+0x168) is one of the zone's squads (+0x40 vector)),
// "anim" [{id, posed, ctrl}] (every CAnimatedNode with a controller, by id). A controller is {word (+0x58, the animation set),
// anm (+0x5c, the one the last Evaluate used), time, t, flags} (key frame) or {w, flags, c: [a, b]} (blender), as
// DOTD_BONES_OUT's plus "word".

struct ReplayFrame {
    int32_t f = 0;
    uint32_t exactBits = 0;
    float current[3] = {}, last[3] = {}, delta[3] = {};
    int32_t clockState = 0;
    int32_t padLen = 0;
    uint16_t words[22] = {};
    uint32_t padStatus = 0;
    bool padOverlayFocus = false;  // C2.8 chase-g7: the RPCS3 overlay module had the pad (ReplayOverlayPadFocus)
    bool hasRand = false;
    crt::RandState rand = {};
    bool hasSpeech = false;        // the sekensor had a current sekens
    bool speechHasPlayer = false;  // its stream had a player (+0x0c)
    bool speechFinished = true;    // FUN_0011a538's answer
    uint32_t speechFlags = 0;      // the sekens' flags (+0x14): bit 0x800 once a position > 0 was seen
    int32_t speechLine = -1;       // the sekens' line (+0x28)
    // C2.8 speech sync: the streamed cinematic's frame in its segment (the 1/60 s frame the stream-driven controllers
    // show: word 0xffffffff, t = a whole number of 1/60 s; the most common nonzero one), -1 without one; the stream's
    // frame since it started, derived from it (ReplayDeriveStreamFrames), -1 where unknown; and the stream time the
    // recorder read directly ("cstream" {time: CKCinematicStreamCpnt +0x30, flags +0xfc}, recordings from 2026-11-14 on).
    int16_t streamFrameInSegment = -1;
    int32_t streamFrame = -1;
    bool hasStreamTime = false;
    double streamTime = 0.0;
    uint32_t streamFlags = 0;
    int32_t loopMode = -1;         // "mode" (C2.8 save-menu: the save data pacer finds the save's frames from it)
    int32_t sector = -100;         // "sector" (C2.8 chase-g2: the sector request pacer), -100 not recorded
    // "music" (C2.8 chase-l20-1: the music track's end, ReplayMusicAnswer): the playing list, its track (-1 none) and
    // the waiting slots (-1 empty); hasMusic false without the music service or the field.
    bool hasMusic = false;
    int32_t musicList = -1;
    int32_t musicTrack = -1;
    bool musicHas = false;  // the track's stream object had its SoundStream ("has")
    int32_t musicWaiting[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
};

std::vector<ReplayFrame> g_replay;     // by f, from frame 0 (video_end)
int32_t g_replayControl = -1;          // the recording's control frame (since video_end)
int32_t g_replayLevelStart = 0;        // the recording's level start frame (since video_end, negative)
bool g_replayLoadingRandValid = false;
crt::RandState g_replayPreRand = {};         // the rand state after the frame before video_end (frame -1)
bool g_replayPreRandValid = false;
crt::RandState g_replayLoadingRand = {};  // the original's rand state after its last loading frame (ReplayHoldLoadingRand)
int32_t g_replayCurrent = -1;
int32_t g_replayLevel = 10;           // the header's "level" (C2.8 lvl020-load)
void ReplayParseLoadHeader(const char* header);  // newgame_load.inc
bool g_replaySyncLevelStart = false;            // header "sync": "level_start" (newgame_load.inc)
bool g_replayLevelExited = false;      // C2.8 chase-g8: the level exit unloaded the level (ReplayAfterFrame)
std::atomic<int32_t> g_replaySaveFrame{-1};  // C2.8 save-menu: g_replayCurrent for the save data pacer (worker thread)
int32_t ReplaySavePacer(int32_t stage);      // below
void ReplayOverlayPadFocus();                // below
int32_t ReplaySectorPacer(int32_t sector, int32_t operation);  // below
int32_t g_replayControlSeen = -1;      // the replay's control frame (since video_end)          // the frame being run (-1: not started)
uint32_t g_replayVideoEnd = 0;         // the loop frame of video_end
std::FILE* g_replayOut = nullptr;

// The value after `"key":` inside [from, line end), or nullptr.
const char* ReplayFind(const char* from, const char* key) {
    const std::string pattern = std::string("\"") + key + "\":";
    const char* p = std::strstr(from, pattern.c_str());
    return p != nullptr ? p + pattern.size() : nullptr;
}
bool ReplayFloats(const char* from, const char* key, float* out, int n) {
    const char* p = ReplayFind(from, key);
    if (p == nullptr || *p != '[') return false;
    ++p;
    for (int i = 0; i < n; ++i) {
        char* end = nullptr;
        out[i] = static_cast<float>(std::strtod(p, &end));  // the shortest repr of a float32 value: exact
        if (end == p) return false;
        p = end + 1;
    }
    return true;
}
template <typename T>
bool ReplayInts(const char* from, const char* key, T* out, int n) {
    const char* p = ReplayFind(from, key);
    if (p == nullptr) return false;
    if (n > 1) {
        if (*p != '[') return false;
        ++p;
    }
    for (int i = 0; i < n; ++i) {
        char* end = nullptr;
        out[i] = static_cast<T>(std::strtoll(p, &end, 0));
        if (end == p) return false;
        p = end + 1;
    }
    return true;
}

// C2.7: the sound instances of recorded frame 0 (the recorder's "sounds": per CKSound id, its instances newest first:
// [state, ramp target, speed, current, remaining, flags, rate, volume offset]). The sounds started before video_end
// (the level's ambient loops and their fade-ins) ran through frames the replay does not drive; StartReplay puts the
// original's states in place (InjectReplaySounds).
struct ReplaySoundInst {
    uint32_t state = 0;
    float ramp[3] = {0.0f, 0.0f, 0.0f};
    float remaining = 0.0f;
    uint32_t flags = 0;
    float rate = 0.0f;
    float offset = 0.0f;
};
struct ReplaySound {
    uint32_t id = 0;
    std::vector<ReplaySoundInst> inst;
};
std::vector<ReplaySound> g_replaySounds0;
// Every recorded frame's instance states per sound id (newest first), for the voices' replay source.
struct ReplaySoundStates {
    uint32_t id = 0;
    std::vector<uint8_t> states;
    std::vector<float> rates;  // each instance's playback rate (+0x4c): tells the instances apart in a full list
};
std::vector<std::vector<ReplaySoundStates>> g_replaySoundStates;
std::string g_replayFrame0Line;  // recorded frame 0 (InjectReplayAnimation)
std::string g_replayPreLine;     // recorded frame -1, before video_end (InjectBoltRolls)
void InjectBoltRolls();
void ReplayParseSoundsInto(const char* s, std::vector<ReplaySound>* out);
void ReplayParseSounds(const char* s) { ReplayParseSoundsInto(s, &g_replaySounds0); }
void ReplayParseSoundStates(const char* s) {
    std::vector<ReplaySound> sounds;
    ReplayParseSoundsInto(s, &sounds);
    std::vector<ReplaySoundStates> states;
    for (const ReplaySound& sound : sounds) {
        ReplaySoundStates entry;
        entry.id = sound.id;
        for (const ReplaySoundInst& in : sound.inst) {
            entry.states.push_back(static_cast<uint8_t>(in.state));
            entry.rates.push_back(in.rate);
        }
        states.push_back(std::move(entry));
    }
    g_replaySoundStates.push_back(std::move(states));
}
void ReplayParseSoundsInto(const char* s, std::vector<ReplaySound>* out) {
    const char* p = ReplayFind(s, "sounds");
    if (p == nullptr || *p != '[') return;
    ++p;
    while (true) {
        const char* id = std::strstr(p, "\"id\":\"");
        const char* close = std::strstr(p, "]}]");  // the end of the sounds list... or of one sound
        if (id == nullptr) break;
        ReplaySound sound;
        sound.id = static_cast<uint32_t>(std::strtoul(id + 6, nullptr, 16));
        const char* q = std::strstr(id, "\"inst\":[");
        if (q == nullptr) break;
        q += 8;
        while (*q == '[') {
            ++q;
            double v[8] = {};
            char* end = nullptr;
            for (int k = 0; k < 8; ++k) {
                v[k] = std::strtod(q, &end);
                q = end;
                if (*q == ',') ++q;
            }
            if (*q == ']') ++q;
            ReplaySoundInst in;
            in.state = static_cast<uint32_t>(v[0]);
            for (int k = 0; k < 3; ++k) in.ramp[k] = static_cast<float>(v[1 + k]);
            in.remaining = static_cast<float>(v[4]);
            in.flags = static_cast<uint32_t>(v[5]);
            in.rate = static_cast<float>(v[6]);
            in.offset = static_cast<float>(v[7]);
            sound.inst.push_back(in);
            if (*q == ',') ++q;
        }
        out->push_back(sound);
        p = q;
        (void)close;
        if (std::strncmp(p, "]}", 2) == 0 && p[2] == ']') break;  // the last sound
        if (std::strncmp(p, "]},", 3) != 0) break;
        p += 3;
    }
}

// C2.8 speech sync (DEBUG (DOTD_REPLAY)): the frame a streamed cinematic (CKCinematicStreamCpnt in its 60 fps mode)
// shows in its segment. The channels it drives play their segment's animation with the word 0xffffffff at t = the
// frame in the segment / 60 (CKCinematicStreamCpnt +0x60); the actors' other controllers with that word stand at t = 0,
// and a stream that follows the frame time instead (no sekens, or not the 60 fps mode) shows times between frames. So:
// the most common nonzero t that is a whole number of 1/60 s, -1 without one (frame 0 of a segment shows as none).
int16_t ReplayStreamFrameInSegment(const char* s) {
    static const char kWord[] = "\"word\":\"0xffffffff\"";
    int32_t counts[64] = {};
    for (const char* p = std::strstr(s, kWord); p != nullptr; p = std::strstr(p + 1, kWord)) {
        const char* close = std::strchr(p, '}');
        const char* t = std::strstr(p, "\"t\":");
        if (t == nullptr || close == nullptr || t > close) continue;
        const double frames = std::strtod(t + 4, nullptr) * 60.0;
        const double whole = std::floor(frames + 0.5);
        if (whole < 1.0 || whole > 63.0 || std::fabs(frames - whole) > 1.0e-3) continue;
        ++counts[static_cast<int32_t>(whole)];
    }
    int16_t best = -1;
    for (int16_t k = 1; k < 64; ++k) {
        if (counts[k] != 0 && (best < 0 || counts[k] > counts[best])) best = k;
    }
    return best;
}

// The stream's frame since it started, for the frames where the sekensor's current sekens has an output (flag 0x800;
// the stream follows its speech, ReplayStreamAnswer): from the first such frame showing a frame in its segment
// (assumed the first segment: the speech starts with the stream, its start-paused voice), each next frame adds the
// step of the frame in the segment modulo the 60 frames of a segment (a frame with none: 0, a segment's first frame);
// a step of more than 4 frames ends it (not the same stream). Not derived where the recorder read the stream time.
void ReplayDeriveStreamFrames() {
    int32_t frame = -1;
    int32_t inSegment = 0;
    int32_t derived = 0;
    bool broken = false;
    int32_t ends = 0;
    for (size_t i = 0; i < g_replay.size(); ++i) {
        ReplayFrame& r = g_replay[i];
        const bool output = r.hasSpeech && (r.speechFlags & 0x800u) != 0;
        if (!output || r.hasStreamTime) {
            // C2.8 chase-g8: the stream's end. A speech that ends with its stream (the sekens gone in frame E: the stream
            // bloc completed, CKCinematicStreamCpnt_Finish stops the sekens) had all its segments played in frame E - 1:
            // the stream time passed the last frame there, while the controllers still show the last frame applied (a
            // segment's frames past its count are not applied). So the frame shown in E - 2 is the last one and the
            // stream's frame in E - 1 is at least the next. Without this the derived frame stood still in E - 1 and
            // the bloc completed a frame late (G +82127: the camera back to the classic track, the FX order).
            if (frame >= 0 && !r.hasSpeech && i >= 2 && g_replay[i - 2].streamFrame >= 0 &&
                g_replay[i - 1].streamFrame <= g_replay[i - 2].streamFrame) {
                g_replay[i - 1].streamFrame = g_replay[i - 2].streamFrame + 1;
                ++ends;
            }
            frame = -1;
            broken = false;
            continue;
        }
        if (broken) continue;
        const int32_t k = r.streamFrameInSegment < 0 ? 0 : r.streamFrameInSegment;
        if (frame < 0) {
            if (r.streamFrameInSegment > 0) {
                frame = k;
                inSegment = k;
            }
        } else {
            const int32_t step = ((k - inSegment) % 60 + 60) % 60;
            if (step > 4) {
                frame = -1;
                broken = true;
                continue;
            }
            frame += step;
            inSegment = k;
        }
        r.streamFrame = frame;
        if (frame >= 0) ++derived;
    }
    if (derived != 0) std::printf("replay: the speech-synced stream's frame derived in %d frame(s), %d stream end(s)\n", derived, ends);
}

bool LoadReplay(const char* path) {
    std::FILE* file = std::fopen(path, "rb");
    if (file == nullptr) {
        std::printf("replay: cannot read %s\n", path);
        return false;
    }
    std::string line;
    int c;
    bool header = true;
    while (true) {
        line.clear();
        while ((c = std::fgetc(file)) != EOF && c != '\n') line.push_back(static_cast<char>(c));
        if (line.empty() && c == EOF) break;
        const char* s = line.c_str();
        if (header) {
            header = false;
            if (std::strstr(s, "\"dotd-replay-1\"") == nullptr) {
                std::printf("replay: %s is not a dotd-replay-1 file\n", path);
                std::fclose(file);
                return false;
            }
            const char* control = ReplayFind(s, "control");
            if (control != nullptr) g_replayControl = std::atoi(control);
            const char* levelStart = ReplayFind(s, "level_start");
            if (levelStart != nullptr) g_replayLevelStart = std::atoi(levelStart);
            const char* level = ReplayFind(s, "level");
            if (level != nullptr && std::atoi(level) > 0) g_replayLevel = std::atoi(level);
            ReplayParseLoadHeader(s);
            continue;
        }
        if (ReplayFind(s, "end") != nullptr && ReplayFind(s, "clock") == nullptr) break;
        ReplayFrame r;
        const char* clock = ReplayFind(s, "clock");
        const char* pad = ReplayFind(s, "pad");
        const char* f = ReplayFind(s, "f");
        if (clock == nullptr || pad == nullptr || f == nullptr) {
            std::printf("replay: a frame without clock / pad / f in %s\n", path);
            std::fclose(file);
            return false;
        }
        r.f = std::atoi(f);
        if (r.f < 0) {
            // The frames before video_end are not played; only the rand state of the last loading frame before the level
            // start (level_start - 2: the next frame leaves the loading mode) is kept, see ReplayHoldLoadingRand.
            if ((g_replayLevelStart != 0 || g_replaySyncLevelStart) && r.f == g_replayLevelStart - 2) {  // lvl020-load: frame 0 may be the level start
                if (const char* rand = ReplayFind(s, "rand")) {
                    uint32_t init = 0;
                    g_replayLoadingRandValid = ReplayInts(rand, "seed", &g_replayLoadingRand.seed, 1) && ReplayInts(rand, "init", &init, 1) &&
                                               ReplayInts(rand, "last", &g_replayLoadingRand.last, 1) &&
                                               ReplayInts(rand, "table", g_replayLoadingRand.table, 32);
                    g_replayLoadingRand.initialized = static_cast<uint8_t>(init);
                }
            }
            if (r.f == -1) {
                g_replayPreLine = line;  // the partner bolts' roll angles (InjectBoltRolls)
                // The rand state after the frame before video_end (DOTD_REPLAY_RANDSYNC: video_end's frame starts from it).
                if (const char* rand = ReplayFind(s, "rand")) {
                    uint32_t init = 0;
                    g_replayPreRandValid = ReplayInts(rand, "seed", &g_replayPreRand.seed, 1) && ReplayInts(rand, "init", &init, 1) &&
                                           ReplayInts(rand, "last", &g_replayPreRand.last, 1) && ReplayInts(rand, "table", g_replayPreRand.table, 32);
                    g_replayPreRand.initialized = static_cast<uint8_t>(init);
                }
            }
            continue;  // the frames of the level load and the video skip: before the replay starts
        }
        const char* bits = ReplayFind(clock, "exact_bits");
        if (bits == nullptr || !ReplayFloats(clock, "current", r.current, 3) || !ReplayFloats(clock, "last", r.last, 3) ||
            !ReplayFloats(clock, "delta", r.delta, 3) || !ReplayInts(clock, "state", &r.clockState, 1) ||
            !ReplayInts(pad, "len", &r.padLen, 1) || !ReplayInts(pad, "w", r.words, 22) || !ReplayInts(pad, "status", &r.padStatus, 1)) {
            std::printf("replay: frame %d is incomplete\n", r.f);
            std::fclose(file);
            return false;
        }
        r.exactBits = static_cast<uint32_t>(std::strtoul(bits + 1, nullptr, 16));
        if (const char* mode = ReplayFind(s, "mode")) r.loopMode = std::atoi(mode);
        if (const char* sector = ReplayFind(s, "sector")) r.sector = std::atoi(sector);
        if (const char* rand = ReplayFind(s, "rand")) {
            uint32_t init = 0;
            r.hasRand = ReplayInts(rand, "seed", &r.rand.seed, 1) && ReplayInts(rand, "init", &init, 1) &&
                        ReplayInts(rand, "last", &r.rand.last, 1) && ReplayInts(rand, "table", r.rand.table, 32);
            r.rand.initialized = static_cast<uint8_t>(init);
            // A torn frame (rpcs3_replay_record.py: the next update had started before the hold) holds part of the next
            // frame's draws: not a frame boundary for DOTD_REPLAY_RANDSYNC.
            if (ReplayFind(s, "torn") != nullptr) r.hasRand = false;
        }
        if (const char* speech = ReplayFind(s, "speech")) {
            if (std::strncmp(speech, "null", 4) != 0) {
                uint32_t has = 0, finished = 1;
                r.hasSpeech = ReplayInts(speech, "flags", &r.speechFlags, 1);
                if (ReplayFind(speech, "has") != nullptr) ReplayInts(speech, "has", &has, 1);
                if (ReplayFind(speech, "finished") != nullptr) ReplayInts(speech, "finished", &finished, 1);
                r.speechHasPlayer = has != 0;
                r.speechFinished = finished != 0;
                ReplayInts(speech, "line", &r.speechLine, 1);
            }
        }
        if (const char* music = ReplayFind(s, "music")) {
            // the music object holds no nested object: its keys end at the first '}'
            const char* end = std::strchr(music, '}');
            if (*music == '{' && end != nullptr) {
                const std::string body(music, end);
                r.hasMusic = ReplayInts(body.c_str(), "list", &r.musicList, 1);
                if (ReplayFind(body.c_str(), "track") != nullptr) ReplayInts(body.c_str(), "track", &r.musicTrack, 1);
                int32_t has = 0;
                if (ReplayFind(body.c_str(), "has") != nullptr) ReplayInts(body.c_str(), "has", &has, 1);
                r.musicHas = has != 0;
                if (const char* w = ReplayFind(body.c_str(), "waiting")) {
                    const char* p = w + 1;
                    for (int i = 0; i < 8 && *w == '[' && *p != ']' && *p != 0; ++i) {
                        char* next = nullptr;
                        r.musicWaiting[i] = static_cast<int32_t>(std::strtol(p, &next, 10));
                        if (next == p) break;
                        p = *next == ',' ? next + 1 : next;
                    }
                }
            }
        }
        r.streamFrameInSegment = ReplayStreamFrameInSegment(s);
        if (const char* cstream = ReplayFind(s, "cstream")) {
            uint32_t sekens = 0;
            const char* time = ReplayFind(cstream, "time");
            if (std::strncmp(cstream, "null", 4) != 0 && time != nullptr && ReplayInts(cstream, "flags", &r.streamFlags, 1) &&
                ReplayInts(cstream, "sekens", &sekens, 1) && sekens != 0) {
                r.hasStreamTime = true;
                r.streamTime = std::strtod(time, nullptr);
            }
        }
        if (r.f != static_cast<int32_t>(g_replay.size())) {
            std::printf("replay: frame %d out of order (expected %zu)\n", r.f, g_replay.size());
            std::fclose(file);
            return false;
        }
        if (r.f == 0) {
            ReplayParseSounds(s);
            g_replayFrame0Line = line;
        }
        ReplayParseSoundStates(s);
        g_replay.push_back(r);
    }
    std::fclose(file);
    ReplayDeriveStreamFrames();
    ReplayOverlayPadFocus();
    std::printf("replay: %zu frames from %s (video_end .. +%zu), control at +%d\n", g_replay.size(), path, g_replay.size() - 1, g_replayControl);
    return !g_replay.empty();
}

// C2.7: the level start's rand draws (the original draws 43 in the frame that leaves the loading mode and 73 in the
// level-start frame: the townsfolk's random start times, ...). Before each frame of the level load (loop mode 1) the main
// thread's rand state is set to the original's after its last loading frame, so the frames that start the level draw from
// the same state. The load thread's own draws (music play lists) use its own state, as on the PS3.
void ReplayHoldLoadingRand(int32_t loopMode) {
    if (g_replayLoadingRandValid && loopMode == 1) crt::ThreadRandState() = g_replayLoadingRand;
}

float ReplayBitsToFloat(uint32_t bits) {
    float value;
    std::memcpy(&value, &bits, sizeof value);
    return value;
}

bool ReplayExactTime(double* seconds) {
    if (g_replayCurrent < 0 || g_replayCurrent >= static_cast<int32_t>(g_replay.size())) return false;
    *seconds = static_cast<double>(ReplayBitsToFloat(g_replay[static_cast<size_t>(g_replayCurrent)].exactBits));
    return true;
}

// The frame that leaves the video (video_end, the first frame in mode 5 again) runs before StartReplay installs the
// recording: its exact time is the native clock's last one plus the recording's frame-0 dt, so that frame's dt (the
// bolts started in it, the heroes' animation times) is the original's. Armed once the video plays (mode 8 seen); a
// value of the native time base stays exact here (the dt is a multiple of the float spacing there).
bool g_frameZeroArmed = false;
bool g_frameZeroHave = false;
double g_frameZeroExact = 0.0;
bool ReplayFrameZeroExactTime(double* seconds) {
    if (!g_frameZeroArmed || g_replay.empty() || g_pCKGameLoop == nullptr || g_pCKGameLoop->m_mode != 5) return false;
    if (!g_frameZeroHave) {
        const float last = g_pEngine->m_timeManager->m_pTime->m_fLastExactTime;
        g_frameZeroExact = static_cast<double>(last + g_replay[0].delta[2]);
        g_frameZeroHave = true;
        InjectBoltRolls();
        // DOTD_REPLAY_RANDSYNC (diagnostics): the frame starts from the original's rand state too.
        if (std::getenv("DOTD_REPLAY_RANDSYNC") != nullptr && g_replayPreRandValid) crt::ThreadRandState() = g_replayPreRand;
    }
    *seconds = g_frameZeroExact;
    return true;
}
void ArmReplayFrameZero() {
    if (g_replay.empty() || g_frameZeroArmed) return;
    g_frameZeroArmed = true;
    dotd::platform::SetExactTimeSource(&ReplayFrameZeroExactTime);
}

// C2.8 chase-g7 (DEBUG (DOTD_REPLAY)): the recordings were made with the project's RPCS3 overlay module
// (imgui-test/ppu/module.cpp, OverlayModule::OnControl), which rewrites the pad device's virtual values after the pad
// poll and before the game reads them, while the recorder reads the device's raw CellPadData: Select never reaches the
// game (the module keeps it for itself), and each Select press toggles the module's menu focus, during which every
// value reaches the game as released (event.consume). G +70654 (Select, the menu takes the pad) .. +71025 (Select
// again): the original's heroes got no input there, and dotd took the raw Select for the pause button (entry 1), which
// opened the pause menu (mode 7 -> 8) and froze the rest of the replay. R3 is also kept by the module while its
// coverage tracer is installed; no recording presses it.
void ReplayOverlayPadFocus() {
    bool focus = false;
    bool selectDown = false;
    int32_t frames = 0;
    for (ReplayFrame& r : g_replay) {
        const bool connected = r.padStatus == CELL_PAD_STATUS_CONNECTED;
        const bool select = connected && (r.words[0] & CELL_PAD_CTRL_SELECT) != 0;
        if (select && !selectDown) focus = !focus;
        selectDown = select;
        if (!connected) focus = false;
        r.padOverlayFocus = focus;
        if (focus) ++frames;
    }
    if (frames != 0) std::printf("replay: the overlay module's menu had the pad in %d frame(s) (no input for the game)\n", frames);
}

bool ReplayPad(int port, uint16_t words[24]) {
    if (port != 0 || g_replayCurrent < 0 || g_replayCurrent >= static_cast<int32_t>(g_replay.size())) return false;
    const ReplayFrame& r = g_replay[static_cast<size_t>(g_replayCurrent)];
    if (r.padStatus != CELL_PAD_STATUS_CONNECTED) return false;
    words[0] = 0;
    words[1] = 0;
    std::memcpy(words + 2, r.words, sizeof r.words);
    words[2] = static_cast<uint16_t>(words[2] & ~CELL_PAD_CTRL_SELECT);  // the module keeps Select (digital 1)
    if (r.padOverlayFocus) {
        // Everything released: no digital buttons, the sticks centred (SplitAxis gives 0 / 0), no pressure values.
        words[2] = 0;
        words[3] = 0;
        for (int i = 4; i < 8; ++i) words[i] = 0x80;
        for (int i = 8; i < 20; ++i) words[i] = 0;
    }
    return true;
}

// The speech stream's RWA player (dotd::audio::RwaStreamPlayer_SetReplaySource), for the player of the sekensor's
// current sekens: the PS3's player runs in real time, so the frames its states are reached in are an input of the
// recording. The K state machine above it (SoundStream) is driven to the recorded frames ("has": the stream object had
// its player, +0x0c, after frame N): in Opening the player has opened the source (STOPPED) in the frame the original's
// object got its player; in Playing it reports STOPPED from the third frame before the original gave the player back
// (the fourth STOPPED ends the item) and PLAYING before; in MediaStopped it has stopped once the original's player was
// given back; in NoMedia it has no media. So the sekens sees the player from the frame after the one it appears in and
// its line ends the frame after the player is released, as in the recording. The output (a position above 0) starts in
// the frame the original's sekens saw one (its flag 0x800 set in frame N). Other players, and the frames without a
// current sekens, keep the platform's model.
//
// C2.8 speech sync (DEBUG (DOTD_REPLAY)): the position. The PS3's player plays on the audio clock, which drifts against
// the frame clock: a streamed cinematic that follows its sekens' speech (CKCinematicStreamCpnt_Update 0x83820: the
// stream time = CKSekens_PollStreamPlaybackPosition 0x1f4558 while it is believable) repeats or skips a 1/60 s frame now
// and then (G +9119 / +9120), and its keys' events and the sekens' line ends (CKSekens_UpdateCurrentLine 0x1f6410:
// the position + 4 frame times reaching the accumulated speech time +0x70) come in the original's frames only with the
// original's position. In the frames where the stream's frame is known (ReplayDeriveStreamFrames, or the recorded
// stream time) the answer is the original's position: within the frame's interval [k / 60, (k + 1) / 60) of the 60 fps
// stream (the Update counts frames while (float)(k + 1) / 60.0f <= the time), on the side of the current line's end
// the recording shows (the line ends in this frame or not), never behind the last answer. Once per frame (the sekens
// may move on to its next line between two polls of the same frame). Elsewhere -1: the player's own position.
int32_t g_streamPositionFrame = -1;
float g_streamPosition = -1.0f;      // the stream's (the frame's) position
float g_streamLinePosition = -1.0f;  // the sekens' line test's, when it differs (see below), else -1
int32_t g_streamPositionConflicts = 0;
int32_t g_streamQueryFrame = -1;
int32_t g_streamQuery = 0;
float ReplayStreamPosition(const CKSekens* sekens, int32_t n) {
    if (n == g_streamPositionFrame) return g_streamPosition;
    g_streamLinePosition = -1.0f;
    const ReplayFrame& now = g_replay[static_cast<size_t>(n)];
    float position = -1.0f;
    double debugSpeechTime = -1.0;
    float debugEnd = -1.0f;
    const int32_t conflictsBefore = g_streamPositionConflicts;
    if (now.hasStreamTime) {
        // The recorder read the stream time: it is the position the stream followed (bit 15: it stopped following).
        if ((now.streamFlags & 0x8000u) == 0 && now.streamTime > 0.0) position = static_cast<float>(now.streamTime);
    } else if (now.streamFrame >= 0) {
        const float lo = static_cast<float>(now.streamFrame) / 60.0f;
        const float hi = std::nextafter(static_cast<float>(now.streamFrame + 1) / 60.0f, 0.0f);  // the last one in the frame
        position = lo + (hi - lo) * 0.5f;
        const ReplayFrame& before = g_replay[static_cast<size_t>(n - 1)];
        if (before.hasSpeech && now.speechLine >= 0 && sekens->m_i32CurrentLine == before.speechLine) {
            // CKSekens_UpdateCurrentLine: a line (not the last) ends once its position + 4 frame times (float steps) reaches
            // the speech time. The last line ends with the stream; there the side chosen changes nothing.
            const double dt = static_cast<double>(g_pEngine->m_timeManager->m_pTime->m_afDeltaTime[IKTime::FIXED_GAME_TIME]);
            const double speechTime = static_cast<double>(sekens->m_fSpeechTime);
            const auto ends = [dt, speechTime](float p) {
                float x = p;
                for (int i = 0; i < 4; ++i) x = static_cast<float>(dt + static_cast<double>(x));
                return !(static_cast<double>(x) < speechTime);
            };
            // the first position of the interval that ends the line (positive floats order as their bits)
            uint32_t a, b;
            std::memcpy(&a, &lo, sizeof a);
            std::memcpy(&b, &hi, sizeof b);
            uint32_t first = b + 1;
            if (ends(hi)) {
                uint32_t l = a, h = b;
                while (l < h) {
                    const uint32_t m = l + (h - l) / 2;
                    float pm;
                    std::memcpy(&pm, &m, sizeof pm);
                    if (ends(pm)) h = m; else l = m + 1;
                }
                first = l;
            }
            float firstEnd;
            std::memcpy(&firstEnd, &first, sizeof firstEnd);
            debugSpeechTime = speechTime;
            debugEnd = first > b ? -1.0f : firstEnd;
            if (now.speechLine != before.speechLine) {
                if (first > b) {
                    // the line ends in this frame although no position of the stream's frame ends it: the sekens polled
                    // a later position than the stream (the PS3's position moves on between the polls of one frame)
                    ++g_streamPositionConflicts;
                    uint32_t l = b + 1, h = b + 0x10000u;
                    while (l < h) {
                        const uint32_t m = l + (h - l) / 2;
                        float pm;
                        std::memcpy(&pm, &m, sizeof pm);
                        if (ends(pm)) h = m; else l = m + 1;
                    }
                    std::memcpy(&g_streamLinePosition, &l, sizeof l);
                } else if (position < firstEnd) {
                    position = firstEnd;
                }
            } else if (first <= b) {
                if (first == a) {
                    // the line goes on although every position of the stream's frame ends it: the sekens polled an
                    // earlier position than the stream (G +9242: the stream skips a frame, the line ends a frame later)
                    ++g_streamPositionConflicts;
                    uint32_t l = a - 0x10000u, h = a;
                    while (l < h) {
                        const uint32_t m = l + (h - l) / 2;
                        float pm;
                        std::memcpy(&pm, &m, sizeof pm);
                        if (ends(pm)) h = m; else l = m + 1;
                    }
                    float lineEnd;
                    std::memcpy(&lineEnd, &l, sizeof lineEnd);
                    g_streamLinePosition = std::nextafter(lineEnd, 0.0f);  // the last position that does not end it
                } else if (!(position < firstEnd)) {
                    position = std::nextafter(firstEnd, 0.0f);
                }
            }
        }
        if (g_streamPositionFrame == n - 1 && g_streamPosition > position && g_streamPosition <= hi) position = g_streamPosition;
    }
    g_streamPositionFrame = n;
    g_streamPosition = position;
    static const bool debug = std::getenv("DOTD_DBG_SPEECHSYNC") != nullptr;
    if (debug && position >= 0.0f) {
        std::printf("speechsync: +%d frame %d position %.9g line %d (recorded %d) speech time %.9g end %.9g%s\n", n, now.streamFrame, static_cast<double>(position),
                    sekens->m_i32CurrentLine, now.speechLine, debugSpeechTime, static_cast<double>(debugEnd),
                    g_streamPositionConflicts != conflictsBefore ? " CONFLICT" : "");
    }
    return position;
}

// C2.8 chase-g7 speech line ends (DEBUG (DOTD_REPLAY)): without a streamed cinematic (no stream frame or time: the answer
// above is -1) the position is the player's own, which runs on the frame time, while the PS3's runs on the audio clock.
// The sekens' line ends (CKSekens_UpdateCurrentLine 0x1f6410: the position + 4 frame times reaching the speech time
// +0x70) then came a frame or two away from the original's, and a cinematic waiting for the line (G +68786: scene 31's
// element 8, so the cinematic's end and the heroes' control two frames late) followed. In the frames where the
// recording shows the current line end (its line changes), a position that does not end it moves up to the first one
// that does; in the frames where the recorded line goes on, a position that ends it moves down to the last one that
// does not. Other positions stay the player's own. Once per frame (the player moves once per frame).
int32_t g_lineEndFrame = -1;
float g_lineEndPosition = -1.0f;
int32_t g_lineEndMoved = 0;
float ReplayLineEndPosition(const CKSekens* sekens, int32_t n, float own) {
    if (n == g_lineEndFrame) return g_lineEndPosition;
    g_lineEndFrame = n;
    g_lineEndPosition = -1.0f;
    const ReplayFrame& now = g_replay[static_cast<size_t>(n)];
    const ReplayFrame& before = g_replay[static_cast<size_t>(n - 1)];
    if (!(own > 0.0f) || !before.hasSpeech || now.speechLine < 0 || sekens->m_i32CurrentLine != before.speechLine) return -1.0f;
    // The last line ends with the stream, whatever its position (UpdateCurrentLine's `last`: no later speech line
    // before an element whose vt+0x58 answers): left alone.
    {
        CKSekens* s = const_cast<CKSekens*>(sekens);
        bool last = true;
        const int32_t count = static_cast<int32_t>(s->m_vBlocks.m_ui32NbUsedElt);
        for (int32_t j = sekens->m_i32CurrentLine + 1; j < count; ++j) {
            CKSekensElement* following = static_cast<CKSekensElement*>(s->m_vBlocks.m_pBlock[j]);
            if (following->Vf58() != 0) break;
            if (following->IsKindOfClass(0x65cc) != 0) {
                last = false;
                break;
            }
        }
        if (last) return -1.0f;
    }
    const double dt = static_cast<double>(g_pEngine->m_timeManager->m_pTime->m_afDeltaTime[IKTime::FIXED_GAME_TIME]);
    const double speechTime = static_cast<double>(sekens->m_fSpeechTime);
    const auto ends = [dt, speechTime](float p) {
        float x = p;
        for (int i = 0; i < 4; ++i) x = static_cast<float>(dt + static_cast<double>(x));
        return !(static_cast<double>(x) < speechTime);
    };
    const auto bitsOf = [](float f) { uint32_t u; std::memcpy(&u, &f, sizeof u); return u; };
    const auto floatOf = [](uint32_t u) { float f; std::memcpy(&f, &u, sizeof f); return f; };
    // the first position (positive floats order as their bits) in [l, h] that ends the line; ends(h) holds
    const auto firstEnd = [&](uint32_t l, uint32_t h) {
        while (l < h) {
            const uint32_t m = l + (h - l) / 2;
            if (ends(floatOf(m))) h = m; else l = m + 1;
        }
        return floatOf(l);
    };
    float position = -1.0f;
    if (now.speechLine != before.speechLine) {
        if (!ends(own)) {
            uint32_t h = bitsOf(static_cast<float>(speechTime));
            while (!ends(floatOf(h))) ++h;
            if (h > bitsOf(own)) position = firstEnd(bitsOf(own), h);
        }
    } else if (ends(own)) {
        position = std::nextafter(firstEnd(0u, bitsOf(own)), 0.0f);  // the last position that does not end it
    }
    if (position >= 0.0f) ++g_lineEndMoved;
    static const bool debug = std::getenv("DOTD_DBG_SPEECHSYNC") != nullptr;
    if (debug && position >= 0.0f) {
        std::printf("speechsync: +%d line end: own %.9g -> %.9g (line %d, recorded %d -> %d, speech time %.9g)\n", n,
                    static_cast<double>(own), static_cast<double>(position), sekens->m_i32CurrentLine, before.speechLine,
                    now.speechLine, speechTime);
    }
    g_lineEndPosition = position;
    return position;
}

// C2.8 chase-l20-1: the frame a video cinematic ends in (dotd::video::SetBinkReplayEndSource). The PS3's Bink plays
// on real time and skips frames to keep up with its audio track, so the end is an input of the recording: the loop
// leaves the video mode (8) for gameplay (5) in the frame after the one the original's CKPlayVideoCinematicBloc
// completed in (lvl020-full: the third video ends at +71943, calls.jsonl: CKPlayVideoCinematicBloc_Complete; the
// platform model showed every frame and ended 14 frames later, the first two videos end on the recorded frames).
// The bloc completes in the frame after the one the last video frame was decoded in (UpdateFrame flags the end,
// StopIfEnded stops the video after the draw): +1 in the recorded frame two before the first mode-5 frame after a
// mode-8 run (the last frame is decoded now), -1 in the earlier mode-8 frames (the last frame waits), 0 elsewhere
// (the platform's timing).
int32_t ReplayBinkEnd() {
    const int32_t n = g_replayCurrent;
    const int32_t last = static_cast<int32_t>(g_replay.size()) - 1;
    if (n < 0 || n + 1 > last || g_replay[static_cast<size_t>(n)].loopMode != 8) return 0;
    const int32_t next = g_replay[static_cast<size_t>(n) + 1].loopMode;
    if (next != 8) return 0;
    if (n + 2 <= last && g_replay[static_cast<size_t>(n) + 2].loopMode == 5) return 1;
    return -1;
}

// C2.8 chase-l20-1: the playing music track's position (the RWA player of the current play list's track stream). The
// PS3's player plays on the audio clock, so the frame a track reaches its end (CKMusicPlayList_UpdatePlayback 0x212af8:
// the position at or past the length less the fade-out) is an input of the recording, as the speech's. In lvl020-full
// the platform model ended tracks up to 84 frames early (+38655 against +38737) and a few frames late (+18402 / +18401).
// The recorded "music" says which frame the original's list or track changed in. While dotd plays the track the
// previous recorded frame shows: if the original's state changed in this frame in the way a track end changes it (the
// same list with another track, or the list given up for one of its waiting slots, or for none), the position is at
// least the end (the track ends now); otherwise it stays below the end. Changes a detector or a script requests
// (another list that was not waiting) keep the platform's position, as do the frames without a recorded music state.
// The platform's player may also run out of media before the original's did (+38655: 82 frames): while the original
// plays the same track in the next frame the player reports PLAYING and has an output, so the K stream keeps it until
// the frame the original's track ended in (it gives the player back four STOPPED answers later).
bool ReplayMusicAnswer(const RwaStreamPlayer* player, dotd::audio::RwaStreamReplayAnswer* answer) {
    const int32_t n = g_replayCurrent;
    const int32_t last = static_cast<int32_t>(g_replay.size()) - 1;
    const ReplayFrame& now = g_replay[static_cast<size_t>(n)];
    const ReplayFrame& prev = g_replay[static_cast<size_t>(n) - 1];
    if (!now.hasMusic || !prev.hasMusic) return false;
    const CKSrvMusic* music = static_cast<const CKSrvMusic*>(g_pEngine->m_srvMusic);
    if (music == nullptr) return false;
    const CKMusicPlayList* playing = static_cast<const CKMusicPlayList*>(music->m_pCurrentPlayListPlaying);
    if (playing == nullptr || playing->m_unk10 == 0xff || playing->m_aPlayingList == nullptr) return false;
    const CKMusicSequence* sequence = playing->m_aPlayingList[playing->m_unk10];
    const CKStreamObject* object = sequence != nullptr ? static_cast<const CKStreamObject*>(sequence->m_pStream) : nullptr;
    if (object == nullptr || object->m_pStream == nullptr || object->m_pStream->m_pPlayer != player) return false;
    int32_t list = -2;
    for (uint32_t i = 0; i < music->m_ui32NbPlayList; ++i)
        if (music->m_apPlayList[i] == playing) list = static_cast<int32_t>(i);
    if (list != prev.musicList || static_cast<int32_t>(playing->m_unk10) != prev.musicTrack) return false;
    const ReplayFrame& ahead = g_replay[static_cast<size_t>(n + 1 < last ? n + 1 : last)];
    const bool held = now.musicList == list && now.musicTrack == prev.musicTrack && ahead.hasMusic && ahead.musicList == list &&
                      ahead.musicTrack == prev.musicTrack;
    if (!answer->positionQuery) {
        if (!held || object->m_pStream->m_ui8State != SoundStream::kPlaying) return false;
        answer->state = static_cast<int32_t>(kRwaStreamPlaying);
        return true;
    }
    const float end = object->GetLength() - object->m_unk14;
    bool ended = false;
    if (now.musicList == prev.musicList) {
        ended = now.musicTrack != prev.musicTrack;
    } else if (now.musicList == -1) {
        ended = true;
    } else {
        for (int32_t w : prev.musicWaiting) ended = ended || (w >= 0 && w == now.musicList);
    }
    const bool changed = now.musicList != prev.musicList || now.musicTrack != prev.musicTrack;
    if (changed && !ended) return false;
    if (!changed && !answer->ownOutput && !held) return false;
    answer->output = true;
    if (ended) answer->position = answer->ownPosition >= end ? answer->ownPosition : end;
    else answer->position = answer->ownPosition < end ? answer->ownPosition : std::nextafter(end, 0.0f);
    return true;
}

bool ReplayStreamAnswer(const RwaStreamPlayer* player, dotd::audio::RwaStreamReplayAnswer* answer) {
    const int32_t last = static_cast<int32_t>(g_replay.size()) - 1;
    if (g_replayCurrent <= 0 || g_replayCurrent > last) return false;
    if (ReplayMusicAnswer(player, answer)) return true;  // C2.8 chase-l20-1
    const CKSrvSekensor* sekensor = static_cast<const CKSrvSekensor*>(g_pEngine->m_srvSekensor);
    const CKSekens* sekens = sekensor != nullptr ? sekensor->GetCurrentSekens() : nullptr;
    const CKStreamObject* object = sekens != nullptr ? sekens->m_pStreamObject : nullptr;
    if (object == nullptr || object->m_pType == nullptr) return false;
    const SoundStream* stream = nullptr;
    const SoundStreamType* type = object->m_pType;
    for (uint32_t i = 0; i < type->m_vpStreams.m_ui32NbUsedElt; ++i) {
        if (type->m_vpStreams.m_pBlock[i]->m_pObject == object) stream = type->m_vpStreams.m_pBlock[i];
    }
    const auto has = [last](int32_t f) {
        const ReplayFrame& r = g_replay[static_cast<size_t>(f < last ? f : last)];
        return r.hasSpeech && r.speechHasPlayer;
    };
    const int32_t n = g_replayCurrent;
    if (stream == nullptr || stream->m_pPlayer != player) {
        // C2.8 chase-g8: the music track of a streamed cinematic that follows its sekens (CKCinematicStreamCpnt_StartStream
        // requests the sekens (flag 0x2000) and the play list's track in the same frame, both start paused). The PS3 opens
        // the two sources one after the other: in G's two such cinematics (+8932, +79408; calls.jsonl) one SoundStream
        // leaves Opening in the frame the speech's object gets its player (the recorded "has") and the other one frame
        // later; the music's Paused state is then reached a frame later too, and the begin bloc, which waits for the
        // music track to be ready (UpdateSyncedMedia, flag 4), completes in the original's frame (+8944, +79420). The
        // platform model opened both together (the begin a frame early: the scene's elements, +79419). So the music
        // player of the Musics type opens (STOPPED) only from the frame after the speech's player came.
        if (!answer->positionQuery && (sekens->m_flags & 0x2000u) != 0 && !has(n - 1)) {
            SoundStreamType* musics = g_pEngine->m_soundManager->m_pSoundStreamManager->FindTypeByName("Musics");
            for (uint32_t i = 0; musics != nullptr && i < musics->m_vpStreams.m_ui32NbUsedElt; ++i) {
                const SoundStream* music = musics->m_vpStreams.m_pBlock[i];
                if (music->m_pPlayer == player && music->m_ui8State == SoundStream::kOpening) {
                    answer->state = static_cast<int32_t>(kRwaStreamOpening);
                    return true;
                }
            }
        }
        return false;
    }
    answer->state = -1;
    switch (stream->m_ui8State) {
        case SoundStream::kNoMedia:
            answer->state = static_cast<int32_t>(kRwaStreamNoMedia);
            break;
        case SoundStream::kOpening:
            answer->state = static_cast<int32_t>(has(n) ? kRwaStreamStopped : kRwaStreamOpening);
            break;
        case SoundStream::kMediaStopped:
            answer->state = static_cast<int32_t>(has(n) ? kRwaStreamStopping : kRwaStreamStopped);
            break;
        case SoundStream::kPlaying:
            answer->state = static_cast<int32_t>(has(n + 3) ? kRwaStreamPlaying : kRwaStreamStopped);
            break;
        default:
            break;
    }
    const ReplayFrame& now = g_replay[static_cast<size_t>(n)];
    answer->output = now.hasSpeech && (now.speechFlags & 0x800u) != 0;
    answer->position = answer->output ? ReplayStreamPosition(sekens, n) : -1.0f;
    if (answer->output && answer->positionQuery && answer->position < 0.0f) {
        answer->position = ReplayLineEndPosition(sekens, n, answer->ownPosition);
    }
    if (answer->output && answer->positionQuery) {
        // the frame's first position query is the sekens' line test (CKSekens_UpdateCurrentLine; the sekensor updates
        // before the cinematics), the next ones the stream's (CKSekens_PollStreamPlaybackPosition from the cinematic)
        g_streamQuery = n == g_streamQueryFrame ? g_streamQuery + 1 : 0;
        g_streamQueryFrame = n;
        if (g_streamQuery == 0 && g_streamLinePosition >= 0.0f) answer->position = g_streamLinePosition;
        static const bool debug = std::getenv("DOTD_DBG_SPEECHSYNC") != nullptr;
        if (debug && answer->position >= 0.0f) {
            std::printf("speechsync: +%d query %d: %.9g (line %d, updates %u)\n", n, g_streamQuery, static_cast<double>(answer->position),
                        sekens->m_i32CurrentLine, sekens->m_unk3c);
        }
    }
    return true;
}

// ---- the state writer (the recorder's Reader.frame) ----------------------------------------------------------------
void ReplayFloat(std::FILE* file, float value) {
    if (std::isnan(value)) std::fputs("NaN", file);
    else if (std::isinf(value)) std::fputs(value > 0 ? "Infinity" : "-Infinity", file);
    else std::fprintf(file, "%.9g", static_cast<double>(value));
}
void ReplayFloatList(std::FILE* file, const float* values, int n) {
    std::fputc('[', file);
    for (int i = 0; i < n; ++i) {
        if (i != 0) std::fputc(',', file);
        ReplayFloat(file, values[i]);
    }
    std::fputc(']', file);
}
void ReplayMatrix(std::FILE* file, const RwMatrix& m) {
    const float v[16] = {m.right.x, m.right.y, m.right.z, 0.0f, m.up.x, m.up.y, m.up.z, 0.0f, m.at.x, m.at.y, m.at.z, 0.0f,
                         m.pos.x, m.pos.y, m.pos.z, 0.0f};
    ReplayFloatList(file, v, 16);
}

void ReplayController(std::FILE* file, IKSerializable* object, int depth) {
    if (object == nullptr || depth > 6) {
        std::fputs("null", file);
        return;
    }
    if (IsClass(object, CKAnmKeyFrameController::kClassKey)) {
        CKAnmKeyFrameController* k = static_cast<CKAnmKeyFrameController*>(object);
        std::fprintf(file, "{\"word\":\"0x%08x\",\"anm\":\"0x%08x\",\"time\":", k->GetAnimWord(), k->GetEvaluatedAnimWord());
        ReplayFloat(file, k->m_unk54);
        std::fputs(",\"t\":", file);
        ReplayFloat(file, k->m_unk50);
        std::fprintf(file, ",\"flags\":%u}", k->m_unk08);
    } else if (IsClass(object, CKBlenderController::kClassKey)) {
        CKBlenderController* b = static_cast<CKBlenderController*>(object);
        std::fputs("{\"w\":", file);
        ReplayFloat(file, b->m_unk58);
        std::fprintf(file, ",\"flags\":%u,\"c\":[", b->m_unk08);
        ReplayController(file, b->m_apControllers[0], depth + 1);
        std::fputc(',', file);
        ReplayController(file, b->m_apControllers[1], depth + 1);
        std::fputs("]}", file);
    } else {
        std::fputs("null", file);
    }
}

void CollectReplaySounds(IKSerializable* object, uint32_t key, void* context);
struct ReplayObjects {
    std::vector<std::pair<uint32_t, IKSerializable*>> heroes, nodes, enemies, zones;
};
void CollectReplayObjects(IKSerializable* object, uint32_t key, void* context) {
    ReplayObjects& o = *static_cast<ReplayObjects*>(context);
    if (key == CKHkS08Hero::kClassKey) o.heroes.emplace_back(Kp3ObjectId(object, key), object);
    if (key == CKHkS08Enemy::kClassKey) o.enemies.emplace_back(Kp3ObjectId(object, key), object);
    if (key == CKGrpFightZone::kClassKey) o.zones.emplace_back(Kp3ObjectId(object, key), object);
    if (key == CAnimatedNode::kClassKey && static_cast<CAnimatedNode*>(object)->m_pController != nullptr)
        o.nodes.emplace_back(Kp3ObjectId(object, key), object);
}

// The state id of a machine's current row: the top byte of the row's last word (byte +0x10 on the PS3), the third
// byte (+0x12) for the animation machine (its rows are sorted by that byte).
void ReplayState(std::FILE* file, const char* name, const SHeroStateRow* rows, uint8_t count, uint8_t index, int shift, bool first) {
    const uint32_t id = (rows != nullptr && index < count) ? ((rows[index].m_key >> shift) & 0xffu) : 0xffu;
    std::fprintf(file, "%s\"%s\":[%u,%u]", first ? "" : ",", name, index, id);
}

// ---- C2.7 step 7: the "hud" group (the recorder's Reader.hud, replay_compare.py's group hud) ----
// The four HUD screens (GetHudInterfaces()[0] Left, [1] Center, [2] Right, [3] Boss) and the two combo counts; written
// once the level's heroes exist, as the recorder does.
void ReplayHudGauge(std::FILE* file, IKSerializable* updaterRef) {
    const CKSuperGaugeCpntUpdater* updater = static_cast<const CKSuperGaugeCpntUpdater*>(updaterRef);
    if (updater == nullptr) {
        std::fputs("null", file);
        return;
    }
    std::fputc('[', file);
    for (int i = 0; i < 3; ++i) {
        if (i != 0) std::fputc(',', file);
        if (updater->m_apUpdaters[i] != nullptr) ReplayFloat(file, updater->m_apUpdaters[i]->m_unk08);
        else std::fputs("null", file);
    }
    std::fputc(',', file);
    if (updater->m_apUpdaters[0] != nullptr) ReplayFloat(file, updater->m_apUpdaters[0]->m_unk10);
    else std::fputs("null", file);
    std::fputc(']', file);
}
void ReplayHudShake(std::FILE* file, IKSerializable* quakeRef) {
    const CKQuakeCpntUpdater* quake = static_cast<const CKQuakeCpntUpdater*>(quakeRef);
    if (quake == nullptr) {
        std::fputs("null", file);
        return;
    }
    std::fprintf(file, "[%u,", quake->m_bRunning);
    ReplayFloat(file, quake->m_fElapsed);
    std::fputc(']', file);
}
void ReplayHudBase(std::FILE* file, const CKMenuBase114c* menu) {
    const CKFlashUI* ui = static_cast<const CKFlashUI*>(menu->m_pFlashUI);
    std::fprintf(file, "{\"menu\":%u,\"hidden\":", menu->m_ui32Flags);
    if (ui != nullptr) std::fprintf(file, "%u", (ui->m_baFlags >> 5) & 1u);
    else std::fputs("null", file);
}
void ReplayHudFloat(std::FILE* file, const char* name, float value) {
    std::fprintf(file, ",\"%s\":", name);
    ReplayFloat(file, value);
}
template <class Hud>
void ReplayHudSide(std::FILE* file, const char* key, Hud* hud) {
    std::fprintf(file, ",\"%s\":", key);
    if (hud == nullptr) {
        std::fputs("null", file);
        return;
    }
    ReplayHudBase(file, hud);
    std::fprintf(file, ",\"state\":%u,\"active\":%u", hud->m_ui8Flags214, hud->m_ui8Active215);
    ReplayHudFloat(file, "panel_t", hud->PanelTime());
    ReplayHudFloat(file, "upgrade_t", hud->m_fUnk230);
    ReplayHudFloat(file, "combo_t", hud->m_fComboTime);
    ReplayHudFloat(file, "shard_t", hud->m_fShardTime);
    std::fprintf(file, ",\"shards\":[%u,%u],\"shake\":", hud->m_ui8ShardsA, hud->m_ui8ShardsB);
    ReplayHudShake(file, hud->m_pQuakeUpdater248);
    std::fputs(",\"health\":", file);
    ReplayHudGauge(file, hud->HealthGaugeUpdater());
    std::fputs(",\"mana\":", file);
    ReplayHudGauge(file, hud->ManaGaugeUpdater());
    std::fputs(",\"combo\":", file);
    const CKGaugeCpntUpdater* combo = static_cast<const CKGaugeCpntUpdater*>(hud->m_pGaugeUpdater290);
    if (combo != nullptr) {
        std::fputc('[', file);
        ReplayFloat(file, combo->m_unk08);
        std::fputc(',', file);
        ReplayFloat(file, combo->m_unk10);
        std::fputc(']', file);
    } else {
        std::fputs("null", file);
    }
    std::fputc('}', file);
}
void WriteReplayHud(std::FILE* file) {
    CKS08GameManager* manager = M();
    IKSerializable** huds = manager->GetHudInterfaces();
    std::fputs(",\"hud\":{\"combo\":", file);
    std::fprintf(file, "[%u,%u]", manager->m_ui32SpyroComboHits, manager->m_ui32CynderComboHits);
    ReplayHudSide(file, "L", static_cast<CKS08InGameInterfaceLeft*>(huds[0]));
    ReplayHudSide(file, "R", static_cast<CKS08InGameInterfaceRight*>(huds[2]));
    std::fputs(",\"C\":", file);
    if (CKS08InGameInterfaceCenter* center = static_cast<CKS08InGameInterfaceCenter*>(huds[1])) {
        ReplayHudBase(file, center);
        std::fprintf(file, ",\"state\":%u,\"fury\":%u", center->m_ui8Flags200, center->m_ui8FuryShown201);
        ReplayHudFloat(file, "fury_t", center->m_fFuryTime208);
        ReplayHudFloat(file, "msg_t", center->m_fUnk240);
        std::fprintf(file, ",\"queue\":%u,\"shake\":", center->m_ui8QueueCount);
        ReplayHudShake(file, center->m_pQuakeUpdater);
        std::fputs(",\"g0\":", file);
        ReplayHudGauge(file, center->m_pGaugeUpdater210);
        std::fputs(",\"g1\":", file);
        ReplayHudGauge(file, center->m_pGaugeUpdater218);
        std::fputc('}', file);
    } else {
        std::fputs("null", file);
    }
    std::fputs(",\"B\":", file);
    if (CKS08InGameInterfaceBoss* boss = static_cast<CKS08InGameInterfaceBoss*>(huds[3])) {
        ReplayHudBase(file, boss);
        std::fprintf(file, ",\"state\":%u", boss->m_baFlagsE0);
        ReplayHudFloat(file, "t", boss->m_fTime);
        std::fputs(",\"gauge\":", file);
        ReplayHudGauge(file, boss->m_pGaugeUpdater);
        std::fputc('}', file);
    } else {
        std::fputs("null", file);
    }
    std::fputc('}', file);
}

void WriteReplayFrame(int32_t f) {
    std::FILE* file = g_replayOut;
    if (file == nullptr) return;
    const IKTime* clock = g_pEngine->m_timeManager->m_pTime;
    std::fprintf(file, "{\"counter\":%u,\"mode\":%d,\"gs\":%d,\"clock\":{\"exact\":", static_cast<unsigned>(g_ui16RenderFrameCounter),
                 g_pCKGameLoop->m_mode, M()->m_gameState.m_ui8Current);
    ReplayFloat(file, clock->m_fLastExactTime);
    uint32_t bits;
    std::memcpy(&bits, &clock->m_fLastExactTime, sizeof bits);
    std::fprintf(file, ",\"exact_bits\":\"0x%08x\",\"current\":", bits);
    ReplayFloatList(file, clock->m_afCurrentTime, 3);
    std::fputs(",\"last\":", file);
    ReplayFloatList(file, clock->m_afLastTime, 3);
    std::fputs(",\"delta\":", file);
    ReplayFloatList(file, clock->m_afDeltaTime, 3);
    std::fprintf(file, ",\"state\":%d,\"scale\":", clock->m_eCurrentState);
    ReplayFloat(file, g_pEngine->m_timeManager->m_fTimeScale);
    const PS3PadDevice& pad = g_pEngine->m_input->m_aPads[0];
    std::fprintf(file, "},\"pad\":{\"len\":%d,\"w\":[", pad.m_padData.len);
    for (int i = 2; i < 24; ++i) std::fprintf(file, "%s%u", i == 2 ? "" : ",", pad.m_padData.button[i]);
    std::fprintf(file, "],\"status\":%u,\"active\":%u},", g_padInfo2.port_status[0], pad.m_bActive);
    const crt::RandState& rand = crt::ThreadRandState();
    std::fprintf(file, "\"rand\":{\"seed\":%u,\"init\":%u,\"last\":%u,\"table\":[", rand.seed, rand.initialized, rand.last);
    for (int i = 0; i < 32; ++i) std::fprintf(file, "%s%u", i == 0 ? "" : ",", rand.table[i]);
    std::fputs("]},", file);
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(M()->m_unk04[1]);
    std::fprintf(file, "\"sector\":%d,", g_pEngine->m_level->m_currentSector);
    if (group != nullptr) {
        std::fprintf(file, "\"focus\":%d,\"blocked\":%u,", static_cast<int8_t>(group->m_ui8FocusedDragon), (group->m_baWorkFlags >> 3) & 1u);
    } else {
        std::fputs("\"focus\":null,\"blocked\":null,", file);
    }
    if (const CKSrvCinematic* service = static_cast<const CKSrvCinematic*>(g_pEngine->m_srvCinematic)) {
        std::fprintf(file, "\"cine\":{\"bands\":%u,\"scenes\":[", service->m_baData & 1u);
        bool first = true;
        // The level exit's unload (CKSrvCinematic_Destroy) frees the scene list and keeps the count: no scenes then (the
        // recorder reads none either).
        const uint32_t sceneCount = service->m_pSceneList != nullptr ? service->m_ui32SceneNumber : 0u;
        for (uint32_t i = 0; i < sceneCount; ++i) {
            const CKCinematicScene* scene = static_cast<const CKCinematicScene*>(service->m_pSceneList[i]);
            if ((scene->m_baData & 1) == 0) continue;
            std::fprintf(file, "%s[%u,%u,\"", first ? "" : ",", i, scene->m_baData);
            // DOTD_DBG_CINE=N: the elements of playing scene N (class key, flags) logged once, and every element flag change.
            if (const char* want = std::getenv("DOTD_DBG_CINE")) {
                static std::vector<uint32_t> s_lastFlags;
                if (static_cast<uint32_t>(std::atoi(want)) == i) {
                    if (s_lastFlags.size() != scene->m_ui32CinematicPointerLength) {
                        s_lastFlags.assign(scene->m_ui32CinematicPointerLength, 0xffffffffu);
                        for (uint32_t k = 0; k < scene->m_ui32CinematicPointerLength; ++k) {
                            IKCinematicElement* e = static_cast<IKCinematicElement*>(scene->m_pCinematicPointerList[k]);
                            std::printf("cine %u element %u key %x start %u interrupt %u count %u\n", i, k,
                                        (static_cast<uint32_t>(e->GetClassID()) << 6) + static_cast<uint32_t>(e->GetClassType()),
                                        e->m_ui16StartElementsFirstIndex, e->m_ui16InterruptElementsFirstIndex, e->m_ui16ElementsNumber);
                        }
                    }
                    for (uint32_t k = 0; k < scene->m_ui32CinematicPointerLength; ++k) {
                        const uint32_t flags = static_cast<const IKCinematicElement*>(scene->m_pCinematicPointerList[k])->m_DataFlags;
                        if (flags != s_lastFlags[k]) {
                            std::printf("cine %u frame %d element %u flags %x -> %x\n", i, g_replayCurrent, k, s_lastFlags[k], flags);
                            s_lastFlags[k] = flags;
                        }
                    }
                }
            }
            for (uint32_t k = 0; k < scene->m_ui32CinematicPointerLength; ++k)
                std::fprintf(file, "%x", static_cast<const IKCinematicElement*>(scene->m_pCinematicPointerList[k])->m_DataFlags & 5u);
            std::fputs("\"]", file);
            first = false;
        }
        std::fputs("]},", file);
    }
    {
        const CKSrvSekensor* sekensor = static_cast<const CKSrvSekensor*>(g_pEngine->m_srvSekensor);
        const CKSekens* sekens = sekensor != nullptr ? sekensor->GetCurrentSekens() : nullptr;
        if (sekens == nullptr) {
            std::fputs("\"speech\":null,", file);
        } else {
            std::fprintf(file, "\"speech\":{\"line\":%d,\"flags\":%u,\"state\":%u", sekens->m_i32CurrentLine, sekens->m_flags, sekens->m_ui32SpeechState);
            if (const CKStreamObject* stream = sekens->m_pStreamObject) {
                std::fprintf(file, ",\"item\":%d,\"has\":%d,\"finished\":%d", stream->m_unk1c, stream->HasPlayer() ? 1 : 0, stream->IsFinished() != 0 ? 1 : 0);
                if (const SoundStream* player = stream->m_pStream) {
                    std::fprintf(file, ",\"ss_state\":%d,\"ss_status\":%u", player->m_i32Request, player->m_ui8State);
                }
            }
            std::fputs("},", file);
        }
    }
    // C2.8 music: the music service's state (see the format notes at the top: "music").
    if (const CKSrvMusic* music = static_cast<const CKSrvMusic*>(g_pEngine->m_srvMusic)) {
        auto indexOf = [music](const IKSerializable* list) -> int32_t {
            if (list == nullptr) return -1;
            for (uint32_t i = 0; i < music->m_ui32NbPlayList; ++i)
                if (music->m_apPlayList[i] == list) return static_cast<int32_t>(i);
            return -2;
        };
        auto slots = [&](const char* key, IKSerializable* const* array) {
            std::fprintf(file, ",\"%s\":[", key);
            for (uint32_t i = 0; i < music->m_ui8NbPriority; ++i)
                std::fprintf(file, "%s%d", i != 0 ? "," : "", array != nullptr ? indexOf(array[i]) : -1);
            std::fputs("]", file);
        };
        const CKMusicPlayList* playing = static_cast<const CKMusicPlayList*>(music->m_pCurrentPlayListPlaying);
        std::fprintf(file, "\"music\":{\"list\":%d,\"enable\":%u", indexOf(playing), music->m_bEnable);
        slots("waiting", music->m_apWaitingPlayList);
        slots("deferred", music->m_unk20);
        if (playing != nullptr) {
            std::fprintf(file, ",\"track\":%u", playing->m_unk10);
            if (playing->m_unk10 != 0xff && playing->m_aPlayingList != nullptr) {
                const CKMusicSequence* sequence = playing->m_aPlayingList[playing->m_unk10];
                const CKStreamObject* stream = sequence != nullptr ? static_cast<const CKStreamObject*>(sequence->m_pStream) : nullptr;
                const SoundStream* player = stream != nullptr ? stream->m_pStream : nullptr;
                std::fprintf(file, ",\"has\":%d", player != nullptr ? 1 : 0);
                if (player != nullptr) std::fprintf(file, ",\"ss_state\":%d,\"ss_status\":%u", player->m_i32Request, player->m_ui8State);
            }
        }
        std::fputs("},", file);
    }
    // C2.8 bonus: the bonus pools' active bonuses (see the format notes at the top: "bonus").
    if (g_pEngine->m_gameManager != nullptr) {
        if (const CKGrpBonus* group = static_cast<const CKGrpBonus*>(g_pEngine->m_gameManager->m_unk04[3])) {
            std::fputs("\"bonus\":[", file);
            uint32_t pools = 0;
            for (const IKBaseGroup* child = group->m_lChilds; child != nullptr && pools < 64; child = child->m_pNextGroup, ++pools) {
                const CKGrpBonusPool* pool = static_cast<const CKGrpBonusPool*>(child);
                std::fprintf(file, "%s{\"type\":%u,\"b\":[", pools != 0 ? "," : "", pool->m_ui32BonusType);
                uint32_t count = 0;
                for (const IKSerializable* item = pool->m_pFirstUsed; item != nullptr && count < 64; ++count) {
                    const CKHkS08Bonus* bonus = static_cast<const CKHkS08Bonus*>(item);
                    const CSGMovable* node = static_cast<const CSGMovable*>(bonus->m_pKGLObject);
                    const RwFrame* frame = node != nullptr ? node->m_pRwFrame : nullptr;
                    std::fprintf(file, "%s{\"pos\":", count != 0 ? "," : "");
                    if (frame != nullptr) {
                        const float pos[3] = {frame->modelling.pos.x, frame->modelling.pos.y, frame->modelling.pos.z};
                        ReplayFloatList(file, pos, 3);
                    } else {
                        std::fputs("null", file);
                    }
                    std::fputs(",\"vel\":", file);
                    const float vel[3] = {bonus->m_v3Velocity.x, bonus->m_v3Velocity.y, bonus->m_v3Velocity.z};
                    ReplayFloatList(file, vel, 3);
                    std::fprintf(file, ",\"n\":%u,\"st\":%u,\"fly\":%d}", bonus->m_ui32BounceCount, bonus->m_GContactInOut.m_eContactStatus,
                                 bonus->m_pCatcher != nullptr ? 1 : 0);
                    item = bonus->m_pNextBonus;
                }
                std::fputs("]}", file);
            }
            std::fputs("],", file);
        }
    }
    const CameraContext* context = static_cast<const CameraContext*>(g_pEngine->m_cameraContext);
    RwCamera* camera = context != nullptr ? context->m_pMainCamera : nullptr;
    if (camera != nullptr) {
        const RwFrame* frame = RwCameraGetFrame(camera);
        std::fputs("\"camera\":{\"ltm\":", file);
        if (frame != nullptr) ReplayMatrix(file, frame->ltm);
        else std::fputs("null", file);
        std::fputs(",\"vw\":", file);
        const float vw[2] = {camera->viewWindow.x, camera->viewWindow.y};
        ReplayFloatList(file, vw, 2);
        std::fputs(",\"near\":", file);
        ReplayFloat(file, camera->nearPlane);
        std::fputs(",\"far\":", file);
        ReplayFloat(file, camera->farPlane);
        std::fputs("},", file);
    }
    // C2.7: the follow camera (the camera service's current camera when a CKCameraClassicTrack3): its position (+0x20),
    // target (+0x2c), previous focus (+0x23c), spring speeds (+0x11c / +0x120) and flags (+0xe8), with the service's
    // flags (+0x46c) and focus copy (+0x490).
    {
        const CKSrvCamera* service = static_cast<const CKSrvCamera*>(g_pEngine->m_srvCamera);
        IKCamera* current = service != nullptr ? service->m_pCurrentCamera : nullptr;
        if (current != nullptr && current->GetClassType() == kCategoryCamera && current->GetClassID() == 0xe) {
            const CKCameraClassicTrack3* track = static_cast<const CKCameraClassicTrack3*>(current);
            const float values[11] = {track->m_WorldPosition.x, track->m_WorldPosition.y, track->m_WorldPosition.z,
                                      track->m_WorldTarget.x,   track->m_WorldTarget.y,   track->m_WorldTarget.z,
                                      track->m_prevFocus.x,     track->m_prevFocus.y,     track->m_prevFocus.z,
                                      track->m_followSpeedXZ,   track->m_followSpeedY};
            const float focus[3] = {service->m_v3FocusPosCopy.x, service->m_v3FocusPosCopy.y, service->m_v3FocusPosCopy.z};
            std::fputs("\"track\":{\"v\":", file);
            ReplayFloatList(file, values, 11);
            std::fprintf(file, ",\"fl\":%u,\"sfl\":%u,\"focus\":", track->m_trackFlags, service->m_baTemporaryFlags);
            ReplayFloatList(file, focus, 3);
            // dotd only (diagnostics): the stack's targets (class key, KP3 id), their +0x24 positions and LTM translations.
            std::fputs(",\"stack\":[", file);
            for (uint32_t i = 0; i < service->m_ui32NbStacked && i < 5; ++i) {
                IKSerializable* target = service->m_aStack[i].m_pTarget;
                const uint32_t key = target != nullptr ? ((target->GetClassID() << 6) | target->GetClassType()) : 0;
                const RwV3d ltm = target != nullptr ? static_cast<CSGLeaf*>(target)->m_pRwFrame->ltm.pos : RwV3d{0, 0, 0};
                const float pos[6] = {service->m_aStack[i].m_unk24[0], service->m_aStack[i].m_unk24[1],
                                      service->m_aStack[i].m_unk24[2], ltm.x, ltm.y, ltm.z};
                std::fprintf(file, "%s{\"key\":%u,\"id\":%u,\"p\":", i ? "," : "", key, target ? Kp3ObjectId(target, key) : 0u);
                ReplayFloatList(file, pos, 6);
                std::fputs("}", file);
            }
            std::fputs("]},", file);
        }
    }
    ReplayObjects objects;
    Kp3_ForEachLoadedObject(CollectReplayObjects, &objects);
    std::sort(objects.heroes.begin(), objects.heroes.end());
    std::sort(objects.nodes.begin(), objects.nodes.end());
    std::fputs("\"heroes\":[", file);
    for (size_t i = 0; i < objects.heroes.size(); ++i) {
        CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(objects.heroes[i].second);
        std::fprintf(file, "%s{\"id\":\"0x%08x\",\"hero\":%u,\"node\":", i == 0 ? "" : ",", objects.heroes[i].first, hero->m_ui8Hero);
        const CSGMovable* node = static_cast<const CSGMovable*>(hero->m_pKGLObject);
        const uint32_t nodeId = node != nullptr && IsClass(hero->m_pKGLObject, CAnimatedNode::kClassKey) ? Kp3ObjectId(node, CAnimatedNode::kClassKey) : 0xffffffffu;
        if (nodeId != 0xffffffffu) std::fprintf(file, "\"0x%08x\",\"ltm\":", nodeId);
        else std::fputs("null,\"ltm\":", file);
        if (node != nullptr && node->m_pRwFrame != nullptr) ReplayMatrix(file, node->m_pRwFrame->ltm);
        else std::fputs("null", file);
        const float pos[3] = {hero->m_unk54c, hero->m_unk550, hero->m_unk554};
        const float vel[3] = {hero->m_unk127c, hero->m_unk1280, hero->m_unk1284};
        std::fputs(",\"pos\":", file);
        ReplayFloatList(file, pos, 3);
        std::fputs(",\"vel\":", file);
        ReplayFloatList(file, vel, 3);
        // DOTD_REPLAY_INPUT=1 (step 4 INPUT checks; off by default, the recorder has no such fields): the hero's
        // input fields: stick +0x370, move direction +0x37c, magnitude +0x394, speed band +0x395, held times +0x388 /
        // +0x38c, the button record states (+0xef4 + 0x14 n), the attack code +0x1a84, +0x1374 / +0x1378, the run
        // direction +0x12b8 and +0x12d0.
        static const bool replayInput = std::getenv("DOTD_REPLAY_INPUT") != nullptr;
        if (replayInput) {
            const float stick[3] = {hero->m_unk370, hero->m_unk374, hero->m_unk378};
            const float move[3] = {hero->m_unk37c, hero->m_unk380, hero->m_unk384};
            const float run[3] = {hero->m_unk12b8, hero->m_unk12bc, hero->m_unk12c0};
            std::fputs(",\"input\":{\"stick\":", file);
            ReplayFloatList(file, stick, 3);
            std::fputs(",\"move\":", file);
            ReplayFloatList(file, move, 3);
            std::fprintf(file, ",\"mag\":%u,\"band\":%u,\"held\":", hero->m_unk394, hero->m_unk395);
            const float held[2] = {hero->m_unk388, hero->m_unk38c};
            ReplayFloatList(file, held, 2);
            std::fprintf(file, ",\"rec\":[%u,%u,%u,%u,%u,%u,%u,%u,%u,%u],\"queue\":%u,\"turn\":", hero->m_unkef4,
                         hero->m_unkf08, hero->m_unkf1c, hero->m_unkf30, hero->m_unkf44, hero->m_unkf58, hero->m_unkf6c,
                         hero->m_unkf80, hero->m_unkf94, hero->m_unkfa8, hero->m_unk1a84);
            ReplayFloat(file, hero->m_unk1374);
            std::fputs(",\"amount\":", file);
            ReplayFloat(file, hero->m_unk1378);
            std::fputs(",\"run\":", file);
            ReplayFloatList(file, run, 3);
            std::fputs(",\"along\":", file);
            ReplayFloat(file, hero->m_unk12d0);
            std::fputc('}', file);
        }
        std::fprintf(file, ",\"move_mode\":%u,\"flags\":%u,\"states\":{", hero->m_ui8MovementMode, hero->m_ui32HeroFlags358);
        ReplayState(file, "control", hero->m_unka0, hero->m_ui8IANbStates, hero->m_ui8IACurrentState, 24, true);
        ReplayState(file, "anim", hero->m_unk140, hero->m_ui8AnimNbStates, hero->m_ui8AnimCurrentState, 8, false);
        ReplayState(file, "loco", hero->m_unk520, hero->m_ui8DynamicNbStates, hero->m_ui8DynamicCurrentState, 24, false);
        ReplayState(file, "action", hero->m_unkc0, hero->m_ui8FightNbStates, hero->m_ui8FightCurrentState, 24, false);
        std::fputs("},\"layers\":[", file);
        const uint32_t layers = hero->m_pAnimBlendSlots != nullptr ? static_cast<IKGrpHero*>(hero->m_pGrpHero)->GetNbAnimBlendSlots(hero->m_ui8Hero) : 0;
        for (uint32_t k = 0; k < layers && k < 8; ++k) {
            const AnimBlendSlot& slot = hero->m_pAnimBlendSlots[k];
            std::fputs(k == 0 ? "{\"len\":" : ",{\"len\":", file);
            ReplayFloat(file, slot.m_unk08);
            std::fputs(",\"left\":", file);
            ReplayFloat(file, slot.m_unk0c);
            std::fprintf(file, ",\"active\":%u,\"mode\":%u,\"ctrl\":", slot.m_unk10, slot.m_unk14);
            ReplayController(file, slot.m_pController, 0);
            std::fputc('}', file);
        }
        // C2.7 the partner link (the recorder's "link"): the alphas, +0x177c, +0xed4, the two bolts' state.
        std::fprintf(file, "],\"link\":{\"a\":[%u,%u],\"t\":", hero->m_unk1194, hero->m_unk1195);
        ReplayFloat(file, hero->m_unk177c);
        std::fprintf(file, ",\"ed4\":%u,\"bolts\":[", hero->m_ui32StatusFlagsED4);
        const IKSerializable* boltSlots[2] = {hero->m_unk19c8, hero->m_unk19d0};
        for (int k = 0; k < 2; ++k) {
            if (k != 0) std::fputc(',', file);
            const CKLightningBoltNodeFx* bolt = static_cast<const CKLightningBoltNodeFx*>(boltSlots[k]);
            if (bolt == nullptr) {
                std::fputs("null", file);
                continue;
            }
            std::fputs("{\"seg\":[", file);
            for (uint32_t s = 0; s < bolt->m_ui32NbSegments && s < 8; ++s) {
                const CKLightningBoltNodeFx::SSegment& sg = bolt->m_segments.m_pBlock[s];
                std::fprintf(file, "%s[%u,", s == 0 ? "" : ",", sg.m_ui32Level);
                ReplayFloat(file, sg.m_fExpiry);
                std::fprintf(file, ",%u,%u]", sg.m_ui32FirstChild, sg.m_ui32NbChildren);
            }
            std::fprintf(file, "],\"flags\":%u,\"time\":", bolt->m_baFxData);
            ReplayFloat(file, bolt->m_fTime);
            std::fputs(",\"roll\":", file);
            ReplayFloat(file, bolt->m_fRollAngle);
            std::fprintf(file, ",\"segs\":%u,\"sfade\":", bolt->m_ui32NbSegments);
            ReplayFloatList(file, bolt->m_afStartFade, 7);
            std::fputs(",\"efade\":", file);
            ReplayFloatList(file, bolt->m_afEndFade, 7);
            const float timers[2] = {bolt->m_fStartFadeTimer, bolt->m_fEndFadeTimer};
            std::fputs(",\"timers\":", file);
            ReplayFloatList(file, timers, 2);
            const float ends[6] = {bolt->m_vStart.x, bolt->m_vStart.y, bolt->m_vStart.z, bolt->m_vEnd.x, bolt->m_vEnd.y, bolt->m_vEnd.z};
            std::fputs(",\"ends\":", file);  // +0x30 the start in the node's space, +0x3c the end in the world
            ReplayFloatList(file, ends, 6);
            // The branches' state (the recorder's "basis" and "sg"): the root direction, right and up (+0x68 / +0x74 /
            // +0x80); per segment its start, end, wiggle speed, acceleration, amplitude, width and expiry.
            const float basis[9] = {bolt->m_vDirection.x, bolt->m_vDirection.y, bolt->m_vDirection.z, bolt->m_vRight.x, bolt->m_vRight.y,
                                    bolt->m_vRight.z,     bolt->m_vUp.x,        bolt->m_vUp.y,        bolt->m_vUp.z};
            std::fputs(",\"basis\":", file);
            ReplayFloatList(file, basis, 9);
            std::fputs(",\"sg\":[", file);
            for (uint32_t s = 0; s < bolt->m_ui32NbSegments && s < 64; ++s) {
                const CKLightningBoltNodeFx::SSegment& sg = bolt->m_segments.m_pBlock[s];
                const float v[11] = {sg.m_afStart[0], sg.m_afStart[1], sg.m_afStart[2], sg.m_afEnd[0], sg.m_afEnd[1], sg.m_afEnd[2],
                                     sg.m_fSpeed,     sg.m_fAccel,     sg.m_fAmplitude, sg.m_fWidth,   sg.m_fExpiry};
                if (s != 0) std::fputc(',', file);
                ReplayFloatList(file, v, 11);
            }
            std::fputc(']', file);
            std::fputc('}', file);
        }
        std::fputs("]},\"idle_t\":", file);
        ReplayFloat(file, hero->m_unk19ac);
        std::fprintf(file, ",\"f354\":%u", hero->m_ui32HeroFlags354);
        // dotd only (diagnostics): the AI's target (+0x124: its KP3 id and health) and the partner attack credits (+0x1a20).
        {
            const CKHkS08Enemy* target = static_cast<const CKHkS08Enemy*>(hero->m_pTargetedEnemy);
            const uint32_t targetId = target != nullptr ? Kp3ObjectId(target, CKHkS08Enemy::kClassKey) : 0;
            std::fprintf(file, ",\"ai\":[%u,%u,", targetId, hero->m_unk1a20);
            ReplayFloat(file, target != nullptr ? target->m_fHealth : 0.0f);
            std::fputs("]", file);
        }
        std::fputs("}", file);
    }
    // ---- C2.7 enemies and fight zones (the recorder's "enemies" / "zones") ----
    std::sort(objects.enemies.begin(), objects.enemies.end());
    std::sort(objects.zones.begin(), objects.zones.end());
    // C2.7 the sounds with playing instances (the recorder's "sounds").
    std::fputs("],\"sounds\":[", file);
    {
        std::vector<std::pair<uint32_t, CKSound*>> sounds;
        Kp3_ForEachLoadedObject(CollectReplaySounds, &sounds);
        std::sort(sounds.begin(), sounds.end());
        bool firstSound = true;
        for (const auto& sp : sounds) {
            if (sp.second->m_pInstances == nullptr) continue;
            std::fprintf(file, "%s{\"id\":\"0x%08x\",\"inst\":[", firstSound ? "" : ",", sp.first);
            firstSound = false;
            int n = 0;
            for (SoundNode* node = sp.second->m_pInstances; node != nullptr && n < 16; node = node->m_pNext) {
                const SoundInstance* in = node->m_pInstance;
                if (in == nullptr) continue;
                std::fprintf(file, "%s[%u,", n == 0 ? "" : ",", in->m_state);
                const float v[7] = {in->m_volumeRamp[0], in->m_volumeRamp[1], in->m_volumeRamp[2], in->m_fRemaining, 0.0f, in->m_fPlaybackRate, in->m_fVolumeOffset};
                for (int k = 0; k < 7; ++k) {
                    if (k == 4) {
                        std::fprintf(file, "%u,", in->m_flags);
                        continue;
                    }
                    ReplayFloat(file, v[k]);
                    if (k != 6) std::fputc(',', file);
                }
                std::fputc(']', file);
                ++n;
            }
            std::fputs("]}", file);
        }
    }
    std::fputs("],\"enemies\":[", file);
    for (size_t i = 0; i < objects.enemies.size(); ++i) {
        const CKHkS08Enemy* enemy = static_cast<const CKHkS08Enemy*>(objects.enemies[i].second);
        std::fprintf(file, "%s{\"id\":\"0x%08x\",\"npos\":", i == 0 ? "" : ",", objects.enemies[i].first);
        const CSGMovable* node = static_cast<const CSGMovable*>(enemy->m_pKGLObject);
        if (node != nullptr && node->m_pRwFrame != nullptr) {
            const RwMatrix& m = *RwFrameGetLTM(node->m_pRwFrame);  // the stored LTM of the original, computed on demand
            const float npos[3] = {m.pos.x, m.pos.y, m.pos.z};
            ReplayFloatList(file, npos, 3);
        } else {
            std::fputs("null", file);
        }
        const float pos[3] = {enemy->m_v3Position.x, enemy->m_v3Position.y, enemy->m_v3Position.z};
        std::fputs(",\"pos\":", file);
        ReplayFloatList(file, pos, 3);
        std::fprintf(file, ",\"state\":%u,\"aware\":%u,\"react\":%u,\"health\":", enemy->m_mainState, enemy->m_awareState,
                     enemy->m_reactState);
        ReplayFloat(file, enemy->m_fHealth);
        std::fputc('}', file);
    }
    std::fputs("],\"zones\":[", file);
    for (size_t i = 0; i < objects.zones.size(); ++i) {
        const CKGrpFightZone* zone = static_cast<const CKGrpFightZone*>(objects.zones[i].second);
        uint32_t n = 0;
        for (const auto& e : objects.enemies) {
            const CKHkS08Enemy* enemy = static_cast<const CKHkS08Enemy*>(e.second);
            if (enemy->m_mainState == 0xff || enemy->m_pGroupSquad == nullptr) continue;
            for (uint32_t k = 0; k < zone->m_vUnk40.m_ui32NbUsedElt; ++k) {
                if (zone->m_vUnk40.m_pBlock[k] == enemy->m_pGroupSquad) {
                    ++n;
                    break;
                }
            }
        }
        std::fprintf(file, "%s{\"id\":\"0x%08x\",\"n\":%u}", i == 0 ? "" : ",", objects.zones[i].first, n);
    }
    std::fputs("],\"anim\":[", file);
    for (size_t i = 0; i < objects.nodes.size(); ++i) {
        CAnimatedNode* node = static_cast<CAnimatedNode*>(objects.nodes[i].second);
        KBase98D* root = static_cast<KBase98D*>(node->m_pController);
        const bool posed = root->GetIfEvaluatedThisFrame() != nullptr;  // vt+0x6c
        std::fprintf(file, "%s{\"id\":\"0x%08x\",\"posed\":%d,\"ctrl\":", i == 0 ? "" : ",", objects.nodes[i].first, posed ? 1 : 0);
        ReplayController(file, root, 0);
        std::fputc('}', file);
    }
    std::fputc(']', file);
    if (!objects.heroes.empty()) WriteReplayHud(file);
    std::fprintf(file, ",\"f\":%d}\n", f);
}

// DOTD_REPLAY_CLIMBZONES=1 (step 6, platform debug code): at video_end every climb zone of the level is listed
// (KP3 id, kind +0x34, flags, the zone node's LTM position and up axis) with its distance to the player hero.
void CollectClimbZones(IKSerializable* object, uint32_t key, void* context) {
    if (key == CKHkClimbZone::kClassKey)
        static_cast<std::vector<std::pair<uint32_t, IKSerializable*>>*>(context)->emplace_back(Kp3ObjectId(object, key), object);
}
void ListClimbZones() {
    if (std::getenv("DOTD_REPLAY_CLIMBZONES") == nullptr) return;
    ReplayObjects heroes;
    Kp3_ForEachLoadedObject(CollectReplayObjects, &heroes);
    float hx = 0.0f, hy = 0.0f, hz = 0.0f;
    if (!heroes.heroes.empty()) {
        const CKHkS08Hero* hero = static_cast<const CKHkS08Hero*>(heroes.heroes[0].second);
        hx = hero->m_unk54c;
        hy = hero->m_unk550;
        hz = hero->m_unk554;
    }
    std::vector<std::pair<uint32_t, IKSerializable*>> zones;
    Kp3_ForEachLoadedObject(CollectClimbZones, &zones);
    std::sort(zones.begin(), zones.end());
    std::printf("replay: %zu climb zones (hero at %.3f %.3f %.3f)\n", zones.size(), static_cast<double>(hx), static_cast<double>(hy),
                static_cast<double>(hz));
    for (const auto& z : zones) {
        const CKHkClimbZone* zone = static_cast<const CKHkClimbZone*>(z.second);
        const CSGMovable* node = static_cast<const CSGMovable*>(zone->m_pKGLObject);
        if (node == nullptr || node->m_pRwFrame == nullptr) {
            std::printf("replay:   zone 0x%08x kind %u flags 0x%08x no node\n", z.first, zone->m_unk34, zone->m_bitArray);
            continue;
        }
        const RwMatrix* m = RwFrameGetLTM(node->m_pRwFrame);
        const double dx = m->pos.x - hx, dy = m->pos.y - hy, dz = m->pos.z - hz;
        std::printf("replay:   zone 0x%08x kind %u flags 0x%08x sector %u pos %.3f %.3f %.3f up %.3f %.3f %.3f range %.3f dist %.1f",
                    z.first, zone->m_unk34, zone->m_bitArray, zone->m_iSectorIndex, static_cast<double>(m->pos.x),
                    static_cast<double>(m->pos.y), static_cast<double>(m->pos.z), static_cast<double>(m->up.x),
                    static_cast<double>(m->up.y), static_cast<double>(m->up.z), static_cast<double>(zone->m_fUnk30),
                    std::sqrt(dx * dx + dy * dy + dz * dz));
        // The zone's volume (+0x20, a CKOBB) carries the placement: its frame's modelling position and axes, and the
        // box's half sizes (+0x24 of the zone, copied into the box by OnActivate).
        const CSGMovable* box = static_cast<const CSGMovable*>(zone->m_pUnk20);
        if (box != nullptr && box->m_pRwFrame != nullptr) {
            const RwMatrix& b = box->m_pRwFrame->modelling;
            const RwMatrix* bl = RwFrameGetLTM(box->m_pRwFrame);
            std::printf(" box %.3f %.3f %.3f at %.3f %.3f %.3f ltm %.3f %.3f %.3f half %.2f %.2f %.2f ground %d",
                        static_cast<double>(b.pos.x), static_cast<double>(b.pos.y), static_cast<double>(b.pos.z),
                        static_cast<double>(b.at.x), static_cast<double>(b.at.y), static_cast<double>(b.at.z),
                        static_cast<double>(bl->pos.x), static_cast<double>(bl->pos.y), static_cast<double>(bl->pos.z),
                        static_cast<double>(zone->m_afUnk24[0]), static_cast<double>(zone->m_afUnk24[1]),
                        static_cast<double>(zone->m_afUnk24[2]), zone->m_pUnk50 != nullptr ? 1 : 0);
            if (zone->m_pUnk50 != nullptr) {
                const float* b = static_cast<const ICollisionMesh*>(zone->m_pUnk50)->m_AABB;
                std::printf(" box %.2f %.2f %.2f .. %.2f %.2f %.2f", static_cast<double>(b[0]), static_cast<double>(b[1]),
                            static_cast<double>(b[2]), static_cast<double>(b[3]), static_cast<double>(b[4]), static_cast<double>(b[5]));
            }
            // The collision service's contacts to test that hold the zone's box (and what the other volume belongs to).
            const CKSrvCollision* collision = static_cast<const CKSrvCollision*>(g_pEngine->m_srvCollision);
            int contacts = 0;
            for (uint32_t i = 0; i < collision->m_ui16NbContactToTest; ++i) {
                const CContactToTest& c = collision->m_aContactToTest[i];
                for (int side = 0; side < 2; ++side) {
                    if (c.m_apBoundingVolume[side] != zone->m_pUnk20) continue;
                    const IKBoundingVolume* other = static_cast<const IKBoundingVolume*>(c.m_apBoundingVolume[1 - side]);
                    if (contacts++ < 4)
                        std::printf(" contact[%u infos 0x%x other owner %s]", i, c.m_ba16Infos,
                                    other != nullptr && other->m_pOwner != nullptr ? typeid(*other->m_pOwner).name() : "-");
                }
            }
            std::printf(" contacts %d boxinfos 0x%x", contacts, static_cast<const IKBoundingVolume*>(zone->m_pUnk20)->m_ba8Infos);
            std::printf(" probe %.3f %.3f %.3f up %.3f %.3f %.3f", static_cast<double>(zone->m_vUnk84.x),
                        static_cast<double>(zone->m_vUnk84.y), static_cast<double>(zone->m_vUnk84.z),
                        static_cast<double>(zone->m_vUnk90.x), static_cast<double>(zone->m_vUnk90.y),
                        static_cast<double>(zone->m_vUnk90.z));
        }
        std::printf("\n");
    }
    // The level's sectors and the boxes (CKSas) through which the hero's position switches them.
    CKLevel* level = g_pEngine->m_level;
    if (level == nullptr) return;
    std::printf("replay: %u sectors, current %d\n", level->m_vpSectors.m_ui32NbUsedElt, level->m_currentSector);
    for (uint32_t s = 0; s < level->m_vpSectors.m_ui32NbUsedElt; ++s) {
        const CKSector* sector = static_cast<const CKSector*>(level->m_vpSectors.m_pBlock[s]);
        for (uint32_t i = 0; i < sector->m_ui32NbSas; ++i) {
            const CKSas* sas = static_cast<const CKSas*>(sector->m_apSasOut[i]);
            std::printf("replay:   sector %u sas %u: A -> %u min %.1f %.1f %.1f max %.1f %.1f %.1f | B -> %u min %.1f %.1f %.1f max %.1f %.1f %.1f\n",
                        s, i, sas->m_ui32SectorA, static_cast<double>(sas->m_boxA.m_vMin[0]),
                        static_cast<double>(sas->m_boxA.m_vMin[1]), static_cast<double>(sas->m_boxA.m_vMin[2]),
                        static_cast<double>(sas->m_boxA.m_vMax[0]), static_cast<double>(sas->m_boxA.m_vMax[1]),
                        static_cast<double>(sas->m_boxA.m_vMax[2]), sas->m_ui32SectorB,
                        static_cast<double>(sas->m_boxB.m_vMin[0]), static_cast<double>(sas->m_boxB.m_vMin[1]),
                        static_cast<double>(sas->m_boxB.m_vMin[2]), static_cast<double>(sas->m_boxB.m_vMax[0]),
                        static_cast<double>(sas->m_boxB.m_vMax[1]), static_cast<double>(sas->m_boxB.m_vMax[2]));
        }
    }
}

// DOTD_REPLAY_TELEPORT=N:x,y,z[;N:x,y,z...] (step 6, platform debug code, synthetic checks only): before recorded
// frame N hero 0 is put at (x, y, z) and hero 1 1.5 units along x from it, through CKHkS08Hero::TeleportTo (0x36a578)
// with the forced warp (+0x35c bit 17, restored after), without a navigation check and keeping their facing. The
// original has no such input: a replay with a teleport has no RPCS3 truth after it.
void ReplayTeleport() {
    static const char* spec = std::getenv("DOTD_REPLAY_TELEPORT");
    if (spec == nullptr || g_pEngine->m_gameManager == nullptr) return;
    for (const char* p = spec; p != nullptr && *p != '\0';) {
        int frame = 0;
        float x = 0.0f, y = 0.0f, z = 0.0f;
        // N:x,y,z:px,py,pz puts hero 1 at (px, py, pz) instead (step 6 CLIMB).
        float px = 0.0f, py = 0.0f, pz = 0.0f;
        const int fields = std::sscanf(p, "%d:%f,%f,%f:%f,%f,%f", &frame, &x, &y, &z, &px, &py, &pz);
        if (fields >= 4 && frame == g_replayCurrent) {
            ReplayObjects objects;
            Kp3_ForEachLoadedObject(CollectReplayObjects, &objects);
            std::sort(objects.heroes.begin(), objects.heroes.end());
            for (const auto& h : objects.heroes) {
                CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(h.second);
                const bool first = hero->m_ui8Hero == 0;
                const CVector3 position = first ? CVector3{x, y, z} : fields == 7 ? CVector3{px, py, pz} : CVector3{x + 1.5f, y, z};
                const CVector3 facing = {hero->m_unk540, hero->m_unk544, hero->m_unk548};
                const uint32_t saved = hero->m_ui32HeroFlags35C;
                hero->m_ui32HeroFlags35C |= 0x20000u;
                const uint8_t done = hero->TeleportTo(&position, &facing, 0, 0, 0, 0);
                hero->m_ui32HeroFlags35C = saved;
                std::printf("replay: frame +%d: hero %u teleported to %.3f %.3f %.3f (%s)\n", g_replayCurrent, hero->m_ui8Hero,
                            static_cast<double>(position.x), static_cast<double>(position.y), static_cast<double>(position.z),
                            done != 0 ? "done" : "refused");
            }
        }
        p = std::strchr(p, ';');
        if (p != nullptr) ++p;
    }
}

// DOTD_REPLAY_GROUNDLOG=1 (platform debug code, diagnosis only): each hero that is not airborne (+0x354 bit 0) and
// not attached has its ground (m_gcCurDatasInOut) recorded per distinct ground object: the first and last frame, the frames
// stood on, the ground's active flag and sector, the lowest and highest hero y over the contact point, and its owner: a loaded
// hook of category 2 that holds the ground's address in its first 0x1c0 bytes (x86 layout), with a CKHkCrumblyZone's state
// (+0x188, flags +0x158) when it is one. The table is printed by FinishReplay. The owner search reads raw object memory and
// is only done with DOTD_REPLAY_GROUNDLOG=2 (it faulted on a flying replay). The 80 first frames of a hero in movement mode 0
// that stands more than 0.5 over its contact are printed with the contact (this found the unported IKHkHero_StartJumpOrFall_maybe).
struct GroundLogEntry {
    IKSerializable* ground = nullptr;
    uint32_t id = 0, key = 0;
    int32_t first = 0, last = 0, frames = 0;
    uint32_t active = 0, sector = 0;
    float minDy = 1e30f, maxDy = -1e30f;
    uint32_t hero = 0;
    std::string owner;
};
std::vector<GroundLogEntry> g_groundLog;
struct OwnerSearch {
    IKSerializable* ground;
    std::string found;
};
void FindGroundOwner(IKSerializable* object, uint32_t key, void* context) {
    OwnerSearch& search = *static_cast<OwnerSearch*>(context);
    if (sizeof(void*) != 4 || (key & 0x3fu) != 2u || object == nullptr) return;
    const uint32_t* words = reinterpret_cast<const uint32_t*>(object);
    const uint32_t target = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(search.ground));
    for (uint32_t i = 1; i < 0x1c0 / 4; ++i) {
        if (words[i] != target) continue;
        char text[160];
        std::snprintf(text, sizeof text, " [hook key 0x%x id 0x%08x +0x%x", key, Kp3ObjectId(object, key), i * 4);
        search.found += text;
        if (key == 0x2ec2u || key == 0x3582u || key == 0x1982u) {
            const CKHkCrumblyZone* zone = static_cast<const CKHkCrumblyZone*>(object);
            std::snprintf(text, sizeof text, " crumbly: state %u flags158 0x%08x safe=%d broken=%d", static_cast<unsigned>(zone->m_unk188),
                          zone->m_flags158, zone->m_pGround == search.ground ? 1 : 0, zone->m_pBrokenGround == search.ground ? 1 : 0);
            search.found += text;
        }
        search.found += "]";
    }
}
void ReplayGroundLog() {
    static const bool enabled = std::getenv("DOTD_REPLAY_GROUNDLOG") != nullptr;
    if (!enabled || g_pEngine->m_gameManager == nullptr) return;
    ReplayObjects objects;
    Kp3_ForEachLoadedObject(CollectReplayObjects, &objects);
    for (const auto& h : objects.heroes) {
        const CKHkS08Hero* hero = static_cast<const CKHkS08Hero*>(h.second);
        if ((hero->m_ui32HeroFlags354 & 1u) != 0 || (hero->m_ui32HeroFlags35C & 0x100u) != 0) continue;
        IKSerializable* ground = hero->m_gcCurDatasInOut.m_pGround;
        if (ground == nullptr) continue;
        const float dy = hero->m_unk550 - hero->m_gcCurDatasInOut.m_ProjectionOnGround.y;
        static int detail = 0;
        if (hero->m_ui8MovementMode == 0 && dy > 0.5f && detail < 80) {
            ++detail;
            std::printf("groundlog: +%d hero %u mode %u pos %.3f %.3f %.3f ground %p face %d status %u proj y %.3f dy %.3f f354 0x%08x f35c 0x%08x vy %.3f\n",
                        g_replayCurrent, hero->m_ui8Hero, static_cast<unsigned>(hero->m_ui8MovementMode), static_cast<double>(hero->m_unk54c),
                        static_cast<double>(hero->m_unk550), static_cast<double>(hero->m_unk554), static_cast<void*>(ground),
                        hero->m_gcCurDatasInOut.m_i32FaceIndex, hero->m_gcCurDatasInOut.m_eContactStatus,
                        static_cast<double>(hero->m_gcCurDatasInOut.m_ProjectionOnGround.y), static_cast<double>(dy), hero->m_ui32HeroFlags354,
                        hero->m_ui32HeroFlags35C, static_cast<double>(hero->m_unk1280));
        }
        GroundLogEntry* entry = nullptr;
        for (GroundLogEntry& e : g_groundLog)
            if (e.ground == ground && e.hero == hero->m_ui8Hero) entry = &e;
        if (entry == nullptr) {
            g_groundLog.emplace_back();
            entry = &g_groundLog.back();
            entry->ground = ground;
            entry->hero = hero->m_ui8Hero;
            entry->first = g_replayCurrent;
            const ICollisionMesh* mesh = static_cast<const ICollisionMesh*>(ground);
            entry->active = mesh->m_ba16EngineFlags & 1u;
            entry->sector = mesh->GetSectorNumber();
            entry->key = IsClass(ground, CGround::kClassKey) ? CGround::kClassKey : CDynamicGround::kClassKey;
            entry->id = Kp3ObjectId(ground, entry->key);
            OwnerSearch search{ground, std::string()};
            static const bool owners = std::getenv("DOTD_REPLAY_GROUNDLOG")[0] == '2';
            if (owners) Kp3_ForEachLoadedObject(FindGroundOwner, &search);
            entry->owner = search.found.empty() ? std::string(owners ? " [no hook holds it]" : " [not searched]") : search.found;
        }
        entry->last = g_replayCurrent;
        ++entry->frames;
        entry->minDy = std::min(entry->minDy, dy);
        entry->maxDy = std::max(entry->maxDy, dy);
    }
}
void PrintGroundLog() {
    for (const GroundLogEntry& e : g_groundLog)
        std::printf("groundlog: hero %u ground key 0x%x id 0x%08x sector %u active %u frames +%d..+%d (%d) dy %.3f..%.3f owner:%s\n", e.hero,
                    e.key, e.id, e.sector, e.active, e.first, e.last, e.frames, static_cast<double>(e.minDy), static_cast<double>(e.maxDy),
                    e.owner.c_str());
}

// DOTD_REPLAY_RANDLOG=<file> (C2.7 step 1, platform debug code): every rand draw of the game loop thread from video_end on,
// with the dotd function behind it (the first caller that is not crt::rand / Rand_Int), one line per frame in draw order,
// runs of the same function merged: {"f": N, "draws": n, "by": [[function, count], ...]}. work/rand_callers.py lines it up
// with the recording's per-frame tracer counts (rpcs3_replay_record.py --calls).
std::FILE* g_randLog = nullptr;
std::thread::id g_randThread;
std::vector<std::pair<const char*, int>> g_randRuns;
int32_t g_randDraws = 0;

void RandLogObserver() {
    if (std::this_thread::get_id() != g_randThread) return;
    void* frames[8];
    const int n = dotd::platform::debugsym::CaptureCallers(0, frames, 8);
    const char* who = "?";
    for (int i = 0; i < n; ++i) {
        const char* name = dotd::platform::debugsym::FunctionName(frames[i]);
        // The port's local rand helpers (an anonymous namespace's RandUnit, a FogRandU16 macro's lambda...) stand for
        // the caller that inlines them in the original: the first named function above them is logged.
        if (std::strcmp(name, "crt::rand") == 0 || std::strcmp(name, "Rand_Int") == 0 || std::strstr(name, "RandLogObserver") != nullptr ||
            std::strstr(name, "anonymous namespace") != nullptr || std::strstr(name, "<lambda") != nullptr) {
            continue;
        }
        who = name;
        break;
    }
    ++g_randDraws;
    if (!g_randRuns.empty() && g_randRuns.back().first == who) {
        ++g_randRuns.back().second;
    } else {
        g_randRuns.emplace_back(who, 1);
    }
}

void RandLogFrame(int32_t f) {
    if (g_randLog == nullptr) return;
    std::fprintf(g_randLog, "{\"f\":%d,\"draws\":%d,\"by\":[", f, g_randDraws);
    for (size_t i = 0; i < g_randRuns.size(); ++i)
        std::fprintf(g_randLog, "%s[\"%s\",%d]", i == 0 ? "" : ",", g_randRuns[i].first, g_randRuns[i].second);
    std::fputs("]}\n", g_randLog);
    g_randRuns.clear();
    g_randDraws = 0;
}

// The recording's frame-0 animation controllers (C2.7): the heroes' blend layers and every animated node's tree, parsed
// from the frame's line ({word, anm, time, t, flags} / {w, flags, c: [a, b]} / null). Their times ran through the
// frames before video_end the replay does not drive; InjectReplayAnimation puts the key frame times (+0x50 t, +0x54
// time) on the port's controllers where the animation word matches, and the heroes' idle timer (+0x19ac) and +0x354.
struct ReplayCtrl {
    int kind = 0;  // 0 null, 1 key frame, 2 blender
    uint32_t word = 0;
    float time = 0.0f, t = 0.0f;
    std::vector<ReplayCtrl> c;
};
void ReplaySkipSpaces(const char*& p) {
    while (*p == ' ') ++p;
}
bool ReplayParseCtrl(const char*& p, ReplayCtrl& out) {
    if (std::strncmp(p, "null", 4) == 0) {
        p += 4;
        return true;
    }
    if (*p != '{') return false;
    const char* end = p;
    if (std::strncmp(p, "{\"word\":\"", 9) == 0) {
        out.kind = 1;
        out.word = static_cast<uint32_t>(std::strtoul(p + 9, nullptr, 16));
        const char* q = std::strstr(p, "\"time\":");
        const char* r = std::strstr(p, "\"t\":");
        if (q == nullptr || r == nullptr) return false;
        out.time = static_cast<float>(std::strtod(q + 7, nullptr));
        out.t = static_cast<float>(std::strtod(r + 4, nullptr));
        end = std::strchr(p, '}');
        if (end == nullptr) return false;
        p = end + 1;
        return true;
    }
    if (std::strncmp(p, "{\"w\":", 5) == 0) {
        out.kind = 2;
        const char* q = std::strstr(p, "\"c\":[");
        if (q == nullptr) return false;
        p = q + 5;
        out.c.resize(2);
        if (!ReplayParseCtrl(p, out.c[0])) return false;
        if (*p == ',') ++p;
        if (!ReplayParseCtrl(p, out.c[1])) return false;
        if (std::strncmp(p, "]}", 2) != 0) return false;
        p += 2;
        return true;
    }
    return false;
}
int ReplayApplyCtrl(IKSerializable* object, const ReplayCtrl& rec, int depth) {
    if (object == nullptr || depth > 6) return 0;
    if (rec.kind == 1 && IsClass(object, CKAnmKeyFrameController::kClassKey)) {
        CKAnmKeyFrameController* k = static_cast<CKAnmKeyFrameController*>(object);
        if (k->GetAnimWord() != rec.word) return 0;
        k->m_unk50 = rec.t;
        k->m_unk54 = rec.time;
        return 1;
    }
    if (rec.kind == 2 && IsClass(object, CKBlenderController::kClassKey)) {
        CKBlenderController* b = static_cast<CKBlenderController*>(object);
        return ReplayApplyCtrl(b->m_apControllers[0], rec.c[0], depth + 1) + ReplayApplyCtrl(b->m_apControllers[1], rec.c[1], depth + 1);
    }
    return 0;
}
void InjectReplayAnimation(const ReplayObjects& objects, const char* line) {
    if (*line == '\0') return;
    int set = 0;
    char key[64];
    for (const auto& h : objects.heroes) {
        CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(h.second);
        std::snprintf(key, sizeof key, "{\"id\":\"0x%08x\",\"hero\":", h.first);
        const char* p = std::strstr(line, key);
        if (p == nullptr) continue;
        const char* layers = std::strstr(p, "\"layers\":[");
        if (layers != nullptr && hero->m_pAnimBlendSlots != nullptr) {
            const uint32_t n = static_cast<IKGrpHero*>(hero->m_pGrpHero)->GetNbAnimBlendSlots(hero->m_ui8Hero);
            const char* q = layers + 10;
            for (uint32_t k = 0; k < n && k < 8; ++k) {
                const char* c = std::strstr(q, "\"ctrl\":");
                if (c == nullptr) break;
                c += 7;
                ReplayCtrl rec;
                if (!ReplayParseCtrl(c, rec)) break;
                set += ReplayApplyCtrl(hero->m_pAnimBlendSlots[k].m_pController, rec, 0);
                q = c;
            }
        }
        if (const char* idle = std::strstr(p, "\"idle_t\":")) hero->m_unk19ac = static_cast<float>(std::strtod(idle + 9, nullptr));
        if (const char* f354 = std::strstr(p, "\"f354\":")) hero->m_ui32HeroFlags354 = static_cast<uint32_t>(std::strtoul(f354 + 7, nullptr, 10));
    }
    const char* anim = std::strstr(line, "],\"anim\":[{\"id\":");
    for (const auto& nd : objects.nodes) {
        if (anim == nullptr) break;
        std::snprintf(key, sizeof key, "{\"id\":\"0x%08x\",\"posed\":", nd.first);
        const char* p = std::strstr(anim, key);
        if (p == nullptr) continue;
        const char* c = std::strstr(p, "\"ctrl\":");
        if (c == nullptr) continue;
        c += 7;
        ReplayCtrl rec;
        if (!ReplayParseCtrl(c, rec)) continue;
        set += ReplayApplyCtrl(static_cast<CAnimatedNode*>(nd.second)->m_pController, rec, 0);
    }
    std::printf("replay: %d animation controllers set from the recording\n", set);
}

// Before the video_end frame runs: the partner link's two bolts take the original's roll angle (+0x50) of the frame
// before. SetActiveForOwner does not reset it when the link's bolts start (in the video_end frame), so it carries what
// the frames before video_end (the front end, the level start, the video: not replayed) accumulated, and the bolts'
// start points (x / y in the node's space), their basis (m_vUp / m_vRight, from the first direction on) and through it
// the branches turn with it.
void InjectBoltRolls() {
    const char* line = g_replayPreLine.c_str();
    if (*line == '\0') return;
    ReplayObjects objects;
    Kp3_ForEachLoadedObject(CollectReplayObjects, &objects);
    int set = 0;
    char key[64];
    for (const auto& h : objects.heroes) {
        CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(h.second);
        std::snprintf(key, sizeof key, "{\"id\":\"0x%08x\",\"hero\":", h.first);
        const char* p = std::strstr(line, key);
        if (p == nullptr) continue;
        const char* bolts = std::strstr(p, "\"bolts\":[");
        const char* boltsEnd = std::strstr(p, "\"idle_t\":");
        if (bolts == nullptr || boltsEnd == nullptr || bolts > boltsEnd) continue;
        const IKSerializable* boltSlots[2] = {hero->m_unk19c8, hero->m_unk19d0};
        const char* q = bolts;
        for (int k = 0; k < 2; ++k) {
            const char* roll = std::strstr(q, "\"roll\":");
            if (roll == nullptr || roll > boltsEnd) break;
            if (boltSlots[k] != nullptr) {
                CKLightningBoltNodeFx* bolt = const_cast<CKLightningBoltNodeFx*>(static_cast<const CKLightningBoltNodeFx*>(boltSlots[k]));
                bolt->m_fRollAngle = static_cast<float>(std::strtod(roll + 7, nullptr));
                ++set;
            }
            q = roll + 7;
        }
    }
    std::printf("replay: %d bolt roll angles set from the frame before video_end\n", set);
    // The animation controllers too: the video_end frame's render poses the bones from them, and the next frame's
    // update reads those bones' LTMs (the link bolts' source and target hot spots). Set again after the frame
    // (StartReplay) from the recorded frame 0.
    InjectReplayAnimation(objects, line);
}

// The recording's frame-0 sound instances put on the port's (per sound by id, in list order, when the counts match).
void CollectReplaySounds(IKSerializable* object, uint32_t key, void* context) {
    if (key == CKSound::kClassKey) {
        static_cast<std::vector<std::pair<uint32_t, CKSound*>>*>(context)->emplace_back(Kp3ObjectId(object, key), static_cast<CKSound*>(object));
    }
}
void InjectReplaySounds() {
    if (g_replaySounds0.empty()) return;
    std::vector<std::pair<uint32_t, CKSound*>> sounds;
    Kp3_ForEachLoadedObject(CollectReplaySounds, &sounds);
    int set = 0, mismatched = 0;
    for (const ReplaySound& rec : g_replaySounds0) {
        CKSound* sound = nullptr;
        for (const auto& s : sounds) {
            if (s.first == rec.id) sound = s.second;
        }
        std::vector<SoundInstance*> instances;
        for (SoundNode* node = sound != nullptr ? sound->m_pInstances : nullptr; node != nullptr; node = node->m_pNext) {
            if (node->m_pInstance != nullptr) instances.push_back(node->m_pInstance);
        }
        if (instances.size() != rec.inst.size()) {
            ++mismatched;
            std::printf("replay: sound 0x%08x has %zu instances (recorded %zu): not set\n", rec.id, instances.size(), rec.inst.size());
            continue;
        }
        for (size_t k = 0; k < instances.size(); ++k) {
            SoundInstance* in = instances[k];
            const ReplaySoundInst& r = rec.inst[k];
            if (in->m_state != r.state) std::printf("replay: sound 0x%08x instance %zu: state %u (recorded %u)\n", rec.id, k, in->m_state, r.state);
            in->m_state = static_cast<uint8_t>(r.state);
            for (int j = 0; j < 3; ++j) in->m_volumeRamp[j] = r.ramp[j];
            in->m_fRemaining = r.remaining;
            in->m_flags = r.flags;
            in->m_fPlaybackRate = r.rate;
            in->m_fVolumeOffset = r.offset;
            ++set;
        }
    }
    std::printf("replay: %d sound instances set from the recording, %d sounds not matched\n", set, mismatched);
}

// The voices' replay source (SoundVoice_SetReplaySource): a voiced instance of a recorded sound plays on while the
// original's same instance (matched by its place from the oldest, the lists being newest first) is still fading in,
// playing or fading out after frame N, and has ended when it went to the delay or the stop. No answer when the lists
// do not line up (instances removed, or a sound the recording does not list).
std::vector<std::pair<const CKSound*, uint32_t>> g_replaySoundIds;
int32_t ReplayVoiceAnswer(const SoundInstance* instance) {
    const int32_t f = g_replayCurrent;
    if (f <= 0 || f >= static_cast<int32_t>(g_replaySoundStates.size())) return -1;
    const CKSound* sound = instance->m_pSound;
    if (sound == nullptr) return -1;
    uint32_t id = 0;
    bool known = false;
    for (const auto& p : g_replaySoundIds) {
        if (p.first == sound) {
            id = p.second;
            known = true;
            break;
        }
    }
    if (!known) return -1;
    size_t n = 0, place = 0;
    bool seen = false;
    for (const SoundNode* node = sound->m_pInstances; node != nullptr; node = node->m_pNext) {
        if (node->m_pInstance == instance) {
            place = n;
            seen = true;
        }
        ++n;
    }
    if (!seen) return -1;
    const size_t fromOldest = n - 1 - place;
    auto entryOf = [id](const std::vector<ReplaySoundStates>& frame) -> const ReplaySoundStates* {
        for (const ReplaySoundStates& e : frame) {
            if (e.id == id) return &e;
        }
        return nullptr;
    };
    const ReplaySoundStates* beforeEntry = entryOf(g_replaySoundStates[static_cast<size_t>(f - 1)]);
    const ReplaySoundStates* nowEntry = entryOf(g_replaySoundStates[static_cast<size_t>(f)]);
    // A full list (the recorders keep the 16 newest instances) does not hold the oldest ones: its places from the oldest
    // are not the dotd list's. The instances are then matched by their playback rate (random per instance): one listed
    // before and still listed answers by its state; one gone from the list ended unless the instances added in frame N
    // pushed it out of the 16 (no answer); one not listed before (older than the 16) has no answer.
    constexpr size_t kRecordedInstances = 16;
    if (beforeEntry != nullptr && nowEntry != nullptr &&
        (beforeEntry->states.size() >= kRecordedInstances || nowEntry->states.size() >= kRecordedInstances)) {
        auto find = [](const ReplaySoundStates* e, float rate) -> int32_t {
            int32_t at = -1;
            for (size_t i = 0; i < e->rates.size(); ++i) {
                if (e->rates[i] == rate) {
                    if (at >= 0) return -2;  // two instances with the same rate: not told apart
                    at = static_cast<int32_t>(i);
                }
            }
            return at;
        };
        const int32_t was = find(beforeEntry, instance->m_fPlaybackRate);
        if (was < 0 || beforeEntry->states[static_cast<size_t>(was)] > 2) return -1;
        const int32_t is = find(nowEntry, instance->m_fPlaybackRate);
        if (is == -2) return -1;
        if (is >= 0) {
            const uint8_t state = nowEntry->states[static_cast<size_t>(is)];
            return (state == 3 || state == 4) ? 0 : 1;
        }
        size_t added = 0;
        for (float rate : nowEntry->rates) {
            if (find(beforeEntry, rate) == -1) ++added;
        }
        return static_cast<size_t>(was) + added >= kRecordedInstances ? -1 : 0;
    }
    const std::vector<uint8_t>* before = beforeEntry != nullptr ? &beforeEntry->states : nullptr;
    const std::vector<uint8_t>* now = nowEntry != nullptr ? &nowEntry->states : nullptr;
    if (before == nullptr || now == nullptr || n < before->size() || fromOldest >= before->size() || now->size() < before->size()) {
        return -1;
    }
    const uint8_t was = (*before)[before->size() - 1 - fromOldest];
    if (was > 2) return -1;
    const uint8_t is = (*now)[now->size() - 1 - fromOldest];
    return (is == 3 || is == 4) ? 0 : 1;
}

// video_end: the original's clock and rand state are put in place, then the recorded time and pad take over.
void StartReplay(uint32_t videoEndFrame) {
    if (g_replay.empty()) return;
    g_replayVideoEnd = videoEndFrame;
    const ReplayFrame& r = g_replay[0];
    IKTime* clock = g_pEngine->m_timeManager->m_pTime;
    std::memcpy(clock->m_afCurrentTime, r.current, sizeof r.current);
    std::memcpy(clock->m_afLastTime, r.last, sizeof r.last);
    std::memcpy(clock->m_afDeltaTime, r.delta, sizeof r.delta);
    clock->m_fLastExactTime = ReplayBitsToFloat(r.exactBits);
    std::printf("replay: video_end at loop frame %u: clock state %d (recorded %d) set to exact %.9g, scalable time %.9g\n", videoEndFrame,
                clock->m_eCurrentState, r.clockState, static_cast<double>(clock->m_fLastExactTime), static_cast<double>(r.current[0]));
    if (r.hasRand) {
        crt::ThreadRandState() = r.rand;
    } else {
        std::printf("replay: the recording has no rand state\n");
    }
    g_replayCurrent = 0;
    g_replaySaveFrame.store(0);
    dotd::platform::SetSaveDataPacer(&ReplaySavePacer);  // C2.8 save-menu
    SectorRequest_SetPacer(&ReplaySectorPacer);          // C2.8 chase-g2
    dotd::platform::SetExactTimeSource(&ReplayExactTime);
    dotd::platform::SetPadSource(&ReplayPad);
    dotd::audio::RwaStreamPlayer_SetReplaySource(&ReplayStreamAnswer);
    dotd::video::SetBinkReplayEndSource(&ReplayBinkEnd);  // C2.8 chase-l20-1
    if (std::getenv("DOTD_REPLAY_NOVOICE") == nullptr) {
        g_replaySoundIds.clear();
        std::vector<std::pair<uint32_t, CKSound*>> sounds;
        Kp3_ForEachLoadedObject(CollectReplaySounds, &sounds);
        for (const auto& s : sounds) g_replaySoundIds.emplace_back(s.second, s.first);
        SoundVoice_SetReplaySource(&ReplayVoiceAnswer);
    }
    if (const char* out = std::getenv("DOTD_REPLAY_OUT")) {
        g_replayOut = std::fopen(out, "wb");
        if (g_replayOut == nullptr) {
            std::printf("replay: cannot write %s\n", out);
        } else {
            std::fprintf(g_replayOut, "{\"format\":\"dotd-replay-1\",\"source\":\"dotd\",\"build\":\"%s\",\"level\":%d,\"video_skipped\":true,"
                                      "\"video_end_loop_frame\":%u}\n", sizeof(void*) == 4 ? "x86-parity" : "x64", g_replayLevel, videoEndFrame);
        }
    }
    if (const char* randLog = std::getenv("DOTD_REPLAY_RANDLOG")) {
        g_randLog = std::fopen(randLog, "wb");
        if (g_randLog != nullptr) {
            g_randThread = std::this_thread::get_id();
            crt::SetRandObserver(&RandLogObserver);
        } else {
            std::printf("replay: cannot write %s\n", randLog);
        }
    }
    InjectReplaySounds();
    {
        ReplayObjects objects;
        Kp3_ForEachLoadedObject(CollectReplayObjects, &objects);
        InjectReplayAnimation(objects, g_replayFrame0Line.c_str());
    }
    ListClimbZones();
    WriteReplayFrame(0);
}

// C2.8 save-menu: the save data pacer (platform/cell/savedata.h). The recording's save is its loop mode 2 run: the flow
// posts its request in the run's second frame and sees it done in the run's last frame C. The PS3's system UI (the save
// list the player answered, the write) put the stat callback at C - 32 and the file callbacks at C - 31 in each of G's
// three saves (calls.jsonl: 18453 / 18454 / 18485, 67217 / 67218 / 67249, 82385 / 82386 / 82417); the end at C.
int32_t ReplaySavePacer(int32_t stage) {
    const int32_t at = g_replaySaveFrame.load();
    const int32_t count = static_cast<int32_t>(g_replay.size());
    if (at < 0 || at >= count) return -1;
    int32_t i = -1;
    for (int32_t d = 0; d <= 4 && i < 0; ++d) {  // dotd's save may start a few frames off the recording's
        if (at + d < count && g_replay[static_cast<size_t>(at + d)].loopMode == 2) i = at + d;
        else if (at - d >= 0 && g_replay[static_cast<size_t>(at - d)].loopMode == 2) i = at - d;
    }
    if (i < 0) return -1;
    while (i + 1 < count && g_replay[static_cast<size_t>(i + 1)].loopMode == 2) ++i;
    const int32_t end = g_replay[static_cast<size_t>(i)].f;
    if (stage == dotd::platform::kSaveDataStageStat) return end - 32;
    if (stage == dotd::platform::kSaveDataStageFile) return end - 31;
    return end;
}

// C2.8 chase-g2: the sector request pacer (k2000/misc/SectorRequest.h). A posted sector load commits (CKLevel +0x18, the
// recording's "sector", becomes the sector) in the frame where the recording shows it: G's sector 2 load is posted at +11505
// and committed at +11514 on the PS3, dotd's worker is done a frame or two after the post. Without the sector in the
// recording's next 600 frames there is no answer (native timing).
int32_t ReplaySectorPacer(int32_t sector, int32_t operation) {
    if (operation != SectorRequest::kLoad) return -1;
    const int32_t at = g_replayCurrent;
    const int32_t count = static_cast<int32_t>(g_replay.size());
    if (at < 0 || at >= count || g_replay[static_cast<size_t>(at)].sector == -100) return -1;
    if (g_replay[static_cast<size_t>(at)].sector == sector) return 1;
    for (int32_t i = at + 1; i < count && i <= at + 600; ++i) {
        if (g_replay[static_cast<size_t>(i)].sector == sector) return 0;
    }
    return -1;
}

void LtmWatchBeforeFrame();  // newgame_ltmwatch.inc (DOTD_DBG_LTMWATCH)

// Before the loop frame `frame` runs: the recorded frame it is (false once the recording is over).
bool ReplayBeforeFrame(uint32_t frame) {
    if (g_replayCurrent < 0) return true;
    g_replayCurrent = static_cast<int32_t>(frame - g_replayVideoEnd);
    LtmWatchBeforeFrame();
    // C2.8 save-menu: the save data worker released up to this frame and settled (savedata.h SaveDataAdvance).
    g_replaySaveFrame.store(g_replayCurrent);
    dotd::platform::SaveDataAdvance(g_replayCurrent);
    if (g_pCKGameLoop != nullptr) g_pCKGameLoop->m_saveDataRequest.SettleForReplay();
    // DOTD_REPLAY_SAVEAT=F1,F2,... (C2.8 save-menu, diagnostics only): before recorded frame F the game manager is asked for
    // a save (vt+0x104 (0, 0), as a save point's 0x93f does), so the save buffer can be compared with the original's when
    // the replay's heroes no longer reach the save point. The save goes to DOTD_SAVEDATA_DIR (or the test's temp folder).
    static const char* saveAt = std::getenv("DOTD_REPLAY_SAVEAT");
    if (saveAt != nullptr && g_pEngine->m_gameManager != nullptr) {
        for (const char* p = saveAt; *p != 0;) {
            if (std::atoi(p) == g_replayCurrent) {
                std::printf("replay: +%d save requested (DOTD_REPLAY_SAVEAT)\n", g_replayCurrent);
                g_pEngine->m_gameManager->RequestSave(0, 0);
            }
            while (*p != 0 && *p != ',') ++p;
            if (*p == ',') ++p;
        }
    }
    // DOTD_REPLAY_RANDSYNC=1 (C2.7 step 1, diagnostics only): every frame starts from the original's rand state after the
    // previous frame, so a frame's draw count can be compared on its own (a missing caller shows in its frame only).
    static const bool randSync = std::getenv("DOTD_REPLAY_RANDSYNC") != nullptr;
    if (randSync && g_replayCurrent >= 1 && g_replayCurrent < static_cast<int32_t>(g_replay.size()) &&
        g_replay[static_cast<size_t>(g_replayCurrent - 1)].hasRand) {
        crt::ThreadRandState() = g_replay[static_cast<size_t>(g_replayCurrent - 1)].rand;
    }
    // DOTD_REPLAY_UNBLOCK=N (step 4 INPUT, synthetic checks only): from recorded frame N on the hero group's
    // input block (+0xf8 bit 3, set by the cinematic scene that starts at control + 1) is lifted before each frame, so a
    // synthetic pad reaches the heroes before the first fight. The original keeps the block there.
    static const char* unblock = std::getenv("DOTD_REPLAY_UNBLOCK");
    if (unblock != nullptr && g_replayCurrent >= std::atoi(unblock) && g_pEngine->m_gameManager != nullptr) {
        g_pEngine->m_gameManager->SetInputBlocked(0);  // vt+0x1e8
    }
    // DOTD_REPLAY_SECTOR=N:s (step 6 CLIMB, platform debug code, synthetic checks only): before recorded frame N the
    // level switches to sector s and waits for it (CKLevel::SwitchToSector 0x30908 with wait; LVL010's climb zones are in
    // sector 3, which a script loads later in the level), then the climb zones are listed again.
    static const char* sector = std::getenv("DOTD_REPLAY_SECTOR");
    int sectorFrame = 0, sectorIndex = 0;
    if (sector != nullptr && std::sscanf(sector, "%d:%d", &sectorFrame, &sectorIndex) == 2 && sectorFrame == g_replayCurrent &&
        g_pEngine->m_level != nullptr) {
        // The current sector is first marked inactive, so its unload skips the game loop's sector notifications: the
        // sound manager's PostSectorUnload (SoundVoiceManager::StopSectorSounds) crashes natively on a sound of sector 1
        // (an instance list that is not a list; the unload path, C2.8).
        CKLevel* level = g_pEngine->m_level;
        if (level->m_currentSector > 0) static_cast<CKSector*>(level->m_vpSectors.m_pBlock[level->m_currentSector])->SetActive(0);
        level->SwitchToSector(sectorIndex, 1);
        std::printf("replay: frame +%d: switched to sector %d (current %d)\n", g_replayCurrent, sectorIndex,
                    g_pEngine->m_level->m_currentSector);
        ListClimbZones();
    }
    ReplayTeleport();
    return g_replayCurrent < static_cast<int32_t>(g_replay.size());
}

// The frame clock each replayed frame produced against the recording's, bit for bit. The fed clock: the exact time
// (IKTime +0x28) and the unscaled and system deltas / times ([1], [2]), which depend only on the recorded KGetExactTime
// values: a difference is a failure. The scaled dt and game time ([0]) also depend on CTimeManager's time scale, which
// game logic sets (in LVL010 the first fight's slow motion, after control): counted and reported, not a failure.
int32_t g_replayClockMismatches = 0;
int32_t g_replayFirstClockMismatch = -1;
int32_t g_replayScaledMismatches = 0;
int32_t g_replayFirstScaledMismatch = -1;
void ReplayAfterFrame() {
    if (g_replayCurrent <= 0 || g_replayCurrent >= static_cast<int32_t>(g_replay.size())) return;
    const ReplayFrame& r = g_replay[static_cast<size_t>(g_replayCurrent)];
    const IKTime* clock = g_pEngine->m_timeManager->m_pTime;
    uint32_t exact;
    std::memcpy(&exact, &clock->m_fLastExactTime, sizeof exact);
    if (std::memcmp(clock->m_afDeltaTime + 1, r.delta + 1, 2 * sizeof(float)) != 0 ||
        std::memcmp(clock->m_afCurrentTime + 1, r.current + 1, 2 * sizeof(float)) != 0 || exact != r.exactBits ||
        clock->m_eCurrentState != r.clockState) {
        if (g_replayClockMismatches++ == 0) {
            g_replayFirstClockMismatch = g_replayCurrent;
            std::printf("replay: frame +%d: the fed clock differs: exact 0x%08x (recorded 0x%08x), system dt %.9g (recorded %.9g), state %d (recorded %d)\n",
                        g_replayCurrent, exact, r.exactBits, static_cast<double>(clock->m_afDeltaTime[2]), static_cast<double>(r.delta[2]),
                        clock->m_eCurrentState, r.clockState);
        }
    }
    if (std::memcmp(&clock->m_afDeltaTime[0], &r.delta[0], sizeof(float)) != 0 || std::memcmp(&clock->m_afCurrentTime[0], &r.current[0], sizeof(float)) != 0) {
        if (g_replayScaledMismatches++ == 0) {
            g_replayFirstScaledMismatch = g_replayCurrent;
            std::printf("replay: frame +%d: the scaled dt %.9g (recorded %.9g), game time %.9g (recorded %.9g): the time scale is %.9g here\n",
                        g_replayCurrent, static_cast<double>(clock->m_afDeltaTime[0]), static_cast<double>(r.delta[0]),
                        static_cast<double>(clock->m_afCurrentTime[0]), static_cast<double>(r.current[0]),
                        static_cast<double>(g_pEngine->m_timeManager->m_fTimeScale));
        }
    }
    ReplayGroundLog();
    RandLogFrame(g_replayCurrent);
    // C2.8 chase-g8: the level exit. In the loop's second mode 9 frame everything is stopped (CKGameLoop_Mode9_LevelExit
    // once the level agrees: CKGameLoop::Stop, the level, the game manager (its state back to 0), the services (the
    // cinematic service's scene list freed), ...). The recorder went on reading the freed memory there (G +82421, game
    // state 0) and then the next level's load (+82422 ..), which are not LVL010's frames. The replay ends before that
    // frame is written: the writer, the test's own per-frame code and its end-state checks read the level's objects.
    if (g_pCKGameLoop->m_mode == 9) {
        if (M()->m_gameState.m_ui8Current == 0) {
            g_replayLevelExited = true;
            std::printf("replay: +%d the level exit unloaded the level (mode 9): the replay ends with the frame before\n", g_replayCurrent);
            --g_replayCurrent;  // the frames replayed (FinishReplay)
            return;
        }
    }
    WriteReplayFrame(g_replayCurrent);
}

// True when the next frame is past the recording's last, or the level exit unloaded the level.
bool ReplayOver() {
    return g_replayLevelExited || (g_replayCurrent >= 0 && g_replayCurrent + 1 >= static_cast<int32_t>(g_replay.size()));
}

// The end of the replay: the clock check's result (failures), the output closed, the time source off.
int FinishReplay(int32_t controlSince) {
    int failures = 0;
    PrintGroundLog();
    if (g_replayClockMismatches != 0) {
        std::printf("replay: FAIL the fed clock differs from the recording in %d frame(s), the first +%d\n", g_replayClockMismatches,
                    g_replayFirstClockMismatch);
        ++failures;
    } else {
        std::printf("replay: the fed clock (exact time, unscaled and system dt and times, state) equals the recording in all %d frames\n", g_replayCurrent);
    }
    if (g_replayScaledMismatches != 0) {
        std::printf("replay: the scaled dt equals the recording up to +%d; it differs in %d frame(s) from there (the time scale: game logic)\n",
                    g_replayFirstScaledMismatch - 1, g_replayScaledMismatches);
    } else {
        std::printf("replay: the scaled dt equals the recording in all %d frames\n", g_replayCurrent);
    }
    if (g_replayOut != nullptr) {
        std::fprintf(g_replayOut, "{\"end\":true,\"frames\":%d,\"control\":%d}\n", g_replayCurrent + 1, controlSince);
        std::fclose(g_replayOut);
        g_replayOut = nullptr;
    }
    std::printf("replay: %d frames replayed, control at +%d (recording +%d)\n", g_replayCurrent, controlSince, g_replayControl);
    if (g_streamPositionConflicts != 0) {
        std::printf("replay: the speech-synced stream's position could not keep the recorded line ends in %d frame(s)\n",
                    g_streamPositionConflicts);
    }
    if (g_lineEndMoved != 0) {
        std::printf("replay: the speech player's own position was moved to the recorded line ends in %d frame(s)\n", g_lineEndMoved);
    }
    dotd::platform::SetExactTimeSource(nullptr);
    dotd::audio::RwaStreamPlayer_SetReplaySource(nullptr);
    dotd::video::SetBinkReplayEndSource(nullptr);
    return failures;
}
