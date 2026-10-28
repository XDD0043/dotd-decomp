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
//   - the speech stream of the sekensor's current sekens answers as the original's did (speech_model::SetReplaySource,
//     see ReplaySpeechAnswer): the third real-time input, which decides when the opening cinematic gives control;
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
// SoundStream's ss_state +0x10 / ss_status +0x18}, "camera" {ltm[16] (the main camera frame's LTM; words 3/7/11/15 are not floats), vw[2], near, far}, "heroes" [{id (KP3
// object id), hero (+0x24), ltm[16] (the hook node's frame), pos (+0x54c), vel (+0x127c), move_mode (+0x1808), flags
// (+0x358), node (its CAnimatedNode's id), states {control, anim, loco, action: [row index, state id]} (IKHkHero +0xac / +0x14c / +0x52c / +0xcc, the ids
// from the sorted rows +0xa0 / +0x140 / +0x520 / +0xc0), layers [{len, left, active, mode, ctrl}] (the blend slots +0x138)}],
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
    bool hasRand = false;
    crt::RandState rand = {};
    bool hasSpeech = false;        // the sekensor had a current sekens
    bool speechHasPlayer = false;  // its stream had a player (+0x0c)
    bool speechFinished = true;    // FUN_0011a538's answer
    uint32_t speechFlags = 0;      // the sekens' flags (+0x14): bit 0x800 once a position > 0 was seen
};

std::vector<ReplayFrame> g_replay;     // by f, from frame 0 (video_end)
int32_t g_replayControl = -1;          // the recording's control frame (since video_end)
int32_t g_replayCurrent = -1;
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
        if (r.f < 0) continue;  // the frames of the video skip: before the replay starts
        const char* bits = ReplayFind(clock, "exact_bits");
        if (bits == nullptr || !ReplayFloats(clock, "current", r.current, 3) || !ReplayFloats(clock, "last", r.last, 3) ||
            !ReplayFloats(clock, "delta", r.delta, 3) || !ReplayInts(clock, "state", &r.clockState, 1) ||
            !ReplayInts(pad, "len", &r.padLen, 1) || !ReplayInts(pad, "w", r.words, 22) || !ReplayInts(pad, "status", &r.padStatus, 1)) {
            std::printf("replay: frame %d is incomplete\n", r.f);
            std::fclose(file);
            return false;
        }
        r.exactBits = static_cast<uint32_t>(std::strtoul(bits + 1, nullptr, 16));
        if (const char* rand = ReplayFind(s, "rand")) {
            uint32_t init = 0;
            r.hasRand = ReplayInts(rand, "seed", &r.rand.seed, 1) && ReplayInts(rand, "init", &init, 1) &&
                        ReplayInts(rand, "last", &r.rand.last, 1) && ReplayInts(rand, "table", r.rand.table, 32);
            r.rand.initialized = static_cast<uint8_t>(init);
        }
        if (const char* speech = ReplayFind(s, "speech")) {
            if (std::strncmp(speech, "null", 4) != 0) {
                uint32_t has = 0, finished = 1;
                r.hasSpeech = ReplayInts(speech, "flags", &r.speechFlags, 1);
                if (ReplayFind(speech, "has") != nullptr) ReplayInts(speech, "has", &has, 1);
                if (ReplayFind(speech, "finished") != nullptr) ReplayInts(speech, "finished", &finished, 1);
                r.speechHasPlayer = has != 0;
                r.speechFinished = finished != 0;
            }
        }
        if (r.f != static_cast<int32_t>(g_replay.size())) {
            std::printf("replay: frame %d out of order (expected %zu)\n", r.f, g_replay.size());
            std::fclose(file);
            return false;
        }
        g_replay.push_back(r);
    }
    std::fclose(file);
    std::printf("replay: %zu frames from %s (video_end .. +%zu), control at +%d\n", g_replay.size(), path, g_replay.size() - 1, g_replayControl);
    return !g_replay.empty();
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

bool ReplayPad(int port, uint16_t words[24]) {
    if (port != 0 || g_replayCurrent < 0 || g_replayCurrent >= static_cast<int32_t>(g_replay.size())) return false;
    const ReplayFrame& r = g_replay[static_cast<size_t>(g_replayCurrent)];
    if (r.padStatus != CELL_PAD_STATUS_CONNECTED) return false;
    words[0] = 0;
    words[1] = 0;
    std::memcpy(words + 2, r.words, sizeof r.words);
    return true;
}

// The speech stream's answers (speech_model::SetReplaySource) for the stream of the sekensor's current sekens: the stream
// state the original had when frame N's update asked, i.e. after frame N - 1 (the recording: the player is there from the
// frame after the one it appears in, and the line ends the frame after the player is released), "no player" when the
// original had no current sekens then (its stream was just started); a position from the frame the original's sekens
// saw one (its flag 0x800 set in frame N). Other streams keep the model.
bool ReplaySpeechAnswer(const CKStreamObject* stream, speech_model::ReplayAnswer* answer) {
    if (g_replayCurrent <= 0 || g_replayCurrent >= static_cast<int32_t>(g_replay.size())) return false;
    const CKSrvSekensor* sekensor = static_cast<const CKSrvSekensor*>(g_pEngine->m_srvSekensor);
    const CKSekens* sekens = sekensor != nullptr ? sekensor->GetCurrentSekens() : nullptr;
    if (sekens == nullptr || sekens->m_pStreamObject != stream) return false;
    const ReplayFrame& before = g_replay[static_cast<size_t>(g_replayCurrent - 1)];
    const ReplayFrame& now = g_replay[static_cast<size_t>(g_replayCurrent)];
    answer->hasPlayer = before.hasSpeech && before.speechHasPlayer;
    answer->finished = !before.hasSpeech || before.speechFinished;
    answer->positionStarted = now.hasSpeech && (now.speechFlags & 0x800u) != 0;
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

struct ReplayObjects {
    std::vector<std::pair<uint32_t, IKSerializable*>> heroes, nodes;
};
void CollectReplayObjects(IKSerializable* object, uint32_t key, void* context) {
    ReplayObjects& o = *static_cast<ReplayObjects*>(context);
    if (key == CKHkS08Hero::kClassKey) o.heroes.emplace_back(Kp3ObjectId(object, key), object);
    if (key == CAnimatedNode::kClassKey && static_cast<CAnimatedNode*>(object)->m_pController != nullptr)
        o.nodes.emplace_back(Kp3ObjectId(object, key), object);
}

// The state id of a machine's current row: the top byte of the row's last word (byte +0x10 on the PS3), the third
// byte (+0x12) for the animation machine (its rows are sorted by that byte).
void ReplayState(std::FILE* file, const char* name, const SHeroStateRow* rows, uint8_t count, uint8_t index, int shift, bool first) {
    const uint32_t id = (rows != nullptr && index < count) ? ((rows[index].m_key >> shift) & 0xffu) : 0xffu;
    std::fprintf(file, "%s\"%s\":[%u,%u]", first ? "" : ",", name, index, id);
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
        std::fprintf(file, "\"focus\":%d,\"blocked\":%u,", static_cast<int8_t>(group->m_unk66), (group->m_unkf8 >> 3) & 1u);
    } else {
        std::fputs("\"focus\":null,\"blocked\":null,", file);
    }
    if (const CKSrvCinematic* service = static_cast<const CKSrvCinematic*>(g_pEngine->m_srvCinematic)) {
        std::fprintf(file, "\"cine\":{\"bands\":%u,\"scenes\":[", service->m_baData & 1u);
        bool first = true;
        for (uint32_t i = 0; i < service->m_ui32SceneNumber; ++i) {
            const CKCinematicScene* scene = static_cast<const CKCinematicScene*>(service->m_pSceneList[i]);
            if ((scene->m_baData & 1) == 0) continue;
            std::fprintf(file, "%s[%u,%u,\"", first ? "" : ",", i, scene->m_baData);
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
            }
            std::fputs("},", file);
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
        std::fprintf(file, ",\"move_mode\":%u,\"flags\":%u,\"states\":{", hero->m_unk1808, hero->m_unk358);
        ReplayState(file, "control", hero->m_unka0, hero->m_unkAD, hero->m_unkAC, 24, true);
        ReplayState(file, "anim", hero->m_unk140, hero->m_unk14d, hero->m_unk14c, 8, false);
        ReplayState(file, "loco", hero->m_unk520, hero->m_unk52d, hero->m_unk52c, 24, false);
        ReplayState(file, "action", hero->m_unkc0, hero->m_unkCD, hero->m_unkCC, 24, false);
        std::fputs("},\"layers\":[", file);
        const uint32_t layers = hero->m_unk138 != nullptr ? static_cast<IKGrpHero*>(hero->m_pGrpHero)->GetNbAnimBlendSlots(hero->m_ui8Hero) : 0;
        for (uint32_t k = 0; k < layers && k < 8; ++k) {
            const AnimBlendSlot& slot = hero->m_unk138[k];
            std::fputs(k == 0 ? "{\"len\":" : ",{\"len\":", file);
            ReplayFloat(file, slot.m_unk08);
            std::fputs(",\"left\":", file);
            ReplayFloat(file, slot.m_unk0c);
            std::fprintf(file, ",\"active\":%u,\"mode\":%u,\"ctrl\":", slot.m_unk10, slot.m_unk14);
            ReplayController(file, slot.m_pController, 0);
            std::fputc('}', file);
        }
        std::fputs("]}", file);
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
    std::fprintf(file, "],\"f\":%d}\n", f);
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
                const uint32_t saved = hero->m_unk35c;
                hero->m_unk35c |= 0x20000u;
                const uint8_t done = hero->TeleportTo(&position, &facing, 0, 0, 0, 0);
                hero->m_unk35c = saved;
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
        if ((hero->m_unk354 & 1u) != 0 || (hero->m_unk35c & 0x100u) != 0) continue;
        IKSerializable* ground = hero->m_gcCurDatasInOut.m_pGround;
        if (ground == nullptr) continue;
        const float dy = hero->m_unk550 - hero->m_gcCurDatasInOut.m_ProjectionOnGround.y;
        static int detail = 0;
        if (hero->m_unk1808 == 0 && dy > 0.5f && detail < 80) {
            ++detail;
            std::printf("groundlog: +%d hero %u mode %u pos %.3f %.3f %.3f ground %p face %d status %u proj y %.3f dy %.3f f354 0x%08x f35c 0x%08x vy %.3f\n",
                        g_replayCurrent, hero->m_ui8Hero, static_cast<unsigned>(hero->m_unk1808), static_cast<double>(hero->m_unk54c),
                        static_cast<double>(hero->m_unk550), static_cast<double>(hero->m_unk554), static_cast<void*>(ground),
                        hero->m_gcCurDatasInOut.m_i32FaceIndex, hero->m_gcCurDatasInOut.m_eContactStatus,
                        static_cast<double>(hero->m_gcCurDatasInOut.m_ProjectionOnGround.y), static_cast<double>(dy), hero->m_unk354,
                        hero->m_unk35c, static_cast<double>(hero->m_unk1280));
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
        if (std::strcmp(name, "crt::rand") == 0 || std::strcmp(name, "Rand_Int") == 0 || std::strstr(name, "RandLogObserver") != nullptr) continue;
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
    dotd::platform::SetExactTimeSource(&ReplayExactTime);
    dotd::platform::SetPadSource(&ReplayPad);
    speech_model::SetReplaySource(&ReplaySpeechAnswer);
    if (const char* out = std::getenv("DOTD_REPLAY_OUT")) {
        g_replayOut = std::fopen(out, "wb");
        if (g_replayOut == nullptr) {
            std::printf("replay: cannot write %s\n", out);
        } else {
            std::fprintf(g_replayOut, "{\"format\":\"dotd-replay-1\",\"source\":\"dotd\",\"build\":\"%s\",\"level\":10,\"video_skipped\":true,"
                                      "\"video_end_loop_frame\":%u}\n", sizeof(void*) == 4 ? "x86-parity" : "x64", videoEndFrame);
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
    ListClimbZones();
    WriteReplayFrame(0);
}

// Before the loop frame `frame` runs: the recorded frame it is (false once the recording is over).
bool ReplayBeforeFrame(uint32_t frame) {
    if (g_replayCurrent < 0) return true;
    g_replayCurrent = static_cast<int32_t>(frame - g_replayVideoEnd);
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
    WriteReplayFrame(g_replayCurrent);
}

// True when the next frame is past the recording's last.
bool ReplayOver() { return g_replayCurrent >= 0 && g_replayCurrent + 1 >= static_cast<int32_t>(g_replay.size()); }

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
    dotd::platform::SetExactTimeSource(nullptr);
    speech_model::SetReplaySource(nullptr);
    return failures;
}
