// newgame_load.inc - C2.8 lvl020-load: the replay player for recordings that start from a saved game (included inside
// newgame_test.cpp's anonymous namespace, after newgame_replay.inc).
//
// work/rpcs3_replay_record.py --load SAVE-N chooses Load game in the main menu instead of New game, answers RPCS3's save
// list with the save, and records from the menu's exit as a New-game recording does (the level load, the level start, the
// level's opening video skipped: frame 0 = video_end; or frame 0 = the level start when the level has no opening video,
// header "sync": "level_start"). Its header names the save ("load": {"save", "index", "list", "copy"}) and the recording
// folder holds the game's save list as RPCS3 had it (<rec dir>/<copy>/BLUS30205-SPYRO08-SAVE-*: the files and the folder
// times, which order the list).
//
// The replay (DOTD_REPLAY=<that rpcs3.rec>, newgame_test's main hands over to RunLoadReplay):
//   - the saves are copied into a fresh temporary folder (never RPCS3's or the user's profile), each folder's time set to
//     the recorded one, so the boot's options auto load (the newest folder, SaveData_ListAutoLoad) and the list load see
//     the same list; DOTD_SAVEDATA_DIR names it, DOTD_SAVEDATA_LOAD the recorded save (platform/cell/savedata.cpp answers
//     the system's list with it, the way the player's choice answered RPCS3's);
//   - press start, the main menu's focus moved to item 1 (Load game: the game manager's menu entry 9, +0x6c), Cross; the
//     load request (game manager +0x64 bit 2) runs until it ends and the save data worker is idle; then Cross through the
//     game menu (Continue, one player) until the loop leaves the front end, as New game;
//   - from there as the New-game replay: the main thread's rand state held at the original's last loading frame
//     (ReplayHoldLoadingRand), the level start, the video's skip (START 300 frames into mode 8, Left, Cross), StartReplay
//     at video_end (or at the level start: then the level start's frame takes the recorded frame-0 dt, the bolt rolls and
//     the animation controllers of frame -1, ArmReplayFrameZero, as video_end's frame does), then the recorded frames to
//     the recording's end (or the level exit). LVL020 (SAVE-4) starts without an opening video: control at +338.
// The frames before frame 0 (the menus, the load, the level load, the video) are not replayed frame for frame: their
// clock / pad / rand are those of dotd's own run (as in the New-game replay); frame 0 sets the clock and the rand state
// from the recording. The save data pacer (ReplaySavePacer) paces the saves after frame 0 as in a New-game recording.
// Checks: the load ended with result 0 and the level the recording names was loaded; the replay gives control on the
// recording's frame; the fed clock equals the recording (FinishReplay). Nothing of the LVL010 opening scene is checked.

std::string g_replayLoadSave;          // the "load" header's "save" (empty: a New-game recording)
std::string g_replayLoadCopy = "savedata";
std::string g_replayPath;              // the recording (its folder holds the save copy)
std::vector<uint32_t> g_loadRelativeShots;  // DOTD_NEWGAME_SHOT_FRAMES: frames after frame 0 to save (load_<n>.png)

// The JSON string value after "key": (python's json.dumps: a space after the colon), or "".
std::string ReplayString(const char* from, const char* key) {
    const char* p = ReplayFind(from, key);
    if (p == nullptr) return std::string();
    while (*p == ' ') ++p;
    if (*p != '"') return std::string();
    const char* end = std::strchr(p + 1, '"');
    return end != nullptr ? std::string(p + 1, end) : std::string();
}

// The header fields of a --load recording (LoadReplay passes the header line).
void ReplayParseLoadHeader(const char* header) {
    if (const char* load = ReplayFind(header, "load")) {
        g_replayLoadSave = ReplayString(load, "save");
        const std::string copy = ReplayString(load, "copy");
        if (!copy.empty()) g_replayLoadCopy = copy;
    }
    g_replaySyncLevelStart = ReplayString(header, "sync") == "level_start";
}

void ReplaySetEnv(const char* name, const std::string& value) {
#ifdef _WIN32
    _putenv_s(name, value.c_str());
#else
    setenv(name, value.c_str(), 1);
#endif
}

// The recording's save list copied into a fresh temporary folder (folder times kept); "" on failure.
std::string PrepareLoadSaves() {
    namespace fs = std::filesystem;
    std::error_code ec;
    const fs::path source = fs::path(g_replayPath).parent_path() / g_replayLoadCopy;
    if (!fs::is_directory(source / g_replayLoadSave, ec)) {
        std::printf("load: %s has no %s (the recorder's copy of the save list)\n", source.string().c_str(), g_replayLoadSave.c_str());
        return std::string();
    }
#ifdef _WIN32
    const long long pid = _getpid();
#else
    const long long pid = getpid();
#endif
    const fs::path root = fs::temp_directory_path() / ("dotd-loadreplay-" + std::to_string(pid));
    fs::remove_all(root, ec);
    fs::create_directories(root, ec);
    int folders = 0;
    for (const fs::directory_entry& entry : fs::directory_iterator(source, ec)) {
        if (!entry.is_directory(ec)) continue;
        const fs::path target = root / entry.path().filename();
        fs::copy(entry.path(), target, fs::copy_options::recursive, ec);
        if (ec) {
            std::printf("load: cannot copy %s: %s\n", entry.path().string().c_str(), ec.message().c_str());
            return std::string();
        }
        fs::last_write_time(target, fs::last_write_time(entry.path(), ec), ec);
        ++folders;
    }
    std::printf("load: %d save folder(s) copied to %s; the load answers %s\n", folders, root.string().c_str(), g_replayLoadSave.c_str());
    return root.string();
}

int RunLoadReplay() {
    int failures = 0;
    auto expect = [&failures](bool ok, const char* what) {
        if (!ok) {
            std::printf("newgame: FAIL %s\n", what);
            ++failures;
        }
    };
    const std::string saves = PrepareLoadSaves();
    if (saves.empty()) return 1;
    ReplaySetEnv("DOTD_SAVEDATA_DIR", saves);
    ReplaySetEnv("DOTD_SAVEDATA_LOAD", g_replayLoadSave);
    auto cleanup = [&saves]() {
        std::error_code ec;
        std::filesystem::remove_all(saves, ec);
    };
    if (!c15::BootToFrontEnd()) {
        cleanup();
        return 77;
    }
    // DOTD_NO_POST=1: the graphic caps' post-effect bit 0x400 cleared (before / after pictures, as main's).
    if (std::getenv("DOTD_NO_POST") != nullptr) g_pEngine->m_graphic->m_baHardwareCaps &= ~0x400u;
    for (int i = 0; i < 3000 && M()->m_gameState.m_ui8Current != 5; ++i) Step();
    for (int i = 0; i < 60; ++i) Step();
    g_d1 = CELL_PAD_CTRL_START;
    for (int i = 0; i < 6; ++i) Step();
    g_d1 = 0;
    for (int i = 0; i < 600 && M()->m_gameState.m_ui8Current != 6; ++i) Step();
    for (int i = 0; i < 90; ++i) Step();
    // Load game: the main menu's focus to item 1, Cross.
    CKMenuBase114c* mainMenu = static_cast<CKMenuBase114c*>(M()->Vf344()[9]);
    for (int k = 0; k < 4 && mainMenu != nullptr && mainMenu->m_aui8FocusedItem[0] != 1; ++k) {
        g_d1 = CELL_PAD_CTRL_DOWN;
        for (int i = 0; i < 4; ++i) Step();
        g_d1 = 0;
        for (int i = 0; i < 30; ++i) Step();
    }
    expect(mainMenu != nullptr && mainMenu->m_aui8FocusedItem[0] == 1, "the main menu's focus on Load game (item 1)");
    g_d2 = CELL_PAD_CTRL_CROSS;
    for (int i = 0; i < 4; ++i) Step();
    g_d2 = 0;
    bool started = false;
    int frames = 0;
    for (; frames < 3000; ++frames) {
        Step();
        if ((M()->m_flags64 & 4u) != 0) started = true;
        if (started && (M()->m_flags64 & 4u) == 0 && dotd::platform::SaveDataWorkerIdle()) break;
    }
    std::printf("load: the load flow took %d frames, result 0x%x\n", frames, static_cast<uint32_t>(g_saveDataResult));
    expect(started && g_saveDataResult == 0, "Load game loaded the save (result 0)");
    for (int i = 0; i < 90; ++i) Step();
    // Continue (game menu item 0), one player: Cross until the loop leaves the front end.
    for (int k = 0; k < 6 && g_pCKGameLoop->m_mode == 5; ++k) {
        std::printf("probe: Cross in menu 0x%02x\n", M()->m_interfaceState.m_ui8Current);
        g_d2 = CELL_PAD_CTRL_CROSS;
        for (int i = 0; i < 4; ++i) Step();
        g_d2 = 0;
        for (int i = 0; i < 150 && g_pCKGameLoop->m_mode == 5; ++i) Step();
    }
    // Frame 0 at the level start (no opening video): its frame takes the recording's frame-0 dt, the partner bolts' roll
    // and the animation controllers of the frame before, as video_end's does (ReplayFrameZeroExactTime answers in the
    // next mode-5 frame, which is the level start once the front end is left).
    if (g_replaySyncLevelStart && g_pCKGameLoop->m_mode != 5) ArmReplayFrameZero();
    // The level start: mode 5 with the game state 7.
    for (int i = 0; i < 6000 && !(g_pCKGameLoop->m_mode == 5 && M()->m_gameState.m_ui8Current == 7); ++i) {
        ReplayHoldLoadingRand(g_pCKGameLoop->m_mode);
        Step();
    }
    const bool inGame = g_pCKGameLoop->m_mode == 5 && M()->m_gameState.m_ui8Current == 7;
    expect(inGame, "the loaded game's level starts (mode 5, game state 7)");
    std::printf("load: current level %d (recorded %d)\n", M()->m_currentLevel, g_replayLevel);
    expect(M()->m_currentLevel == g_replayLevel, "the save's level is the recording's (game manager +0x27c)");
    const CKGameLevel* level = static_cast<IKGameStructure*>(M()->m_gameStructure)->GetCurrentLevel();
    std::printf("load: level start at loop frame %u, stage %d, sector %d\n", g_frame, level != nullptr ? level->m_i32StageIndex : -1,
                g_pEngine->m_level != nullptr ? g_pEngine->m_level->m_currentSector : -1);
    if (!inGame) {
        cleanup();
        return 1;
    }
    uint32_t frameZero = g_frame;
    if (!g_replaySyncLevelStart) {
        // The opening video and its skip, as the New-game replay: START 300 frames into mode 8, Left, Cross.
        uint32_t modeEightFrame = 0, phaseFrame = 0, modeFiveAgainFrame = 0;
        int phase = 0;
        for (int i = 0; i < 40000; ++i) {
            Step();
            if (modeEightFrame != 0) {
                const uint32_t since = g_frame - modeEightFrame;
                if (phase == 0 && since == 300) { g_d1 = CELL_PAD_CTRL_START; phase = 1; phaseFrame = g_frame; }
                else if (phase == 1 && g_frame - phaseFrame == 4) { g_d1 = 0; phase = 2; phaseFrame = g_frame; }
                else if (phase == 2 && g_frame - phaseFrame == 120) { g_d1 = CELL_PAD_CTRL_LEFT; phase = 3; phaseFrame = g_frame; }
                else if (phase == 3 && g_frame - phaseFrame == 4) { g_d1 = 0; g_d2 = CELL_PAD_CTRL_CROSS; phase = 4; phaseFrame = g_frame; }
                else if (phase == 4 && g_frame - phaseFrame == 4) { g_d2 = 0; phase = 5; phaseFrame = g_frame; }
            }
            if (g_pCKGameLoop->m_mode == 8 && modeEightFrame == 0) {
                modeEightFrame = g_frame;
                ArmReplayFrameZero();
            }
            if (modeEightFrame != 0 && g_pCKGameLoop->m_mode == 5) {
                modeFiveAgainFrame = g_frame;
                break;
            }
        }
        std::printf("load: the opening video from loop frame %u, mode 5 again at %u\n", modeEightFrame, modeFiveAgainFrame);
        expect(modeEightFrame != 0 && modeFiveAgainFrame != 0, "the level's opening video played and was skipped");
        if (modeFiveAgainFrame == 0) {
            cleanup();
            return 1;
        }
        frameZero = modeFiveAgainFrame;
    }
    StartReplay(frameZero);
    // C2.8 gate-l20: DOTD_DUMP_LEVEL_OBJECTS=<pattern with %03d> writes the loaded objects DOTD_DUMP_LEVEL_AFTER_CONTROL
    // frames (default 0) after control, the moment of capture I (live_objects.py at LVL020's control) for objects_diff.py.
    const char* dumpPattern = std::getenv("DOTD_DUMP_LEVEL_OBJECTS");
    const char* dumpAfterText = std::getenv("DOTD_DUMP_LEVEL_AFTER_CONTROL");
    const int32_t dumpAfter = dumpAfterText != nullptr ? std::atoi(dumpAfterText) : 0;
    bool dumped = false;
    // The recorded frames; control is the first frame with the input free after a blocked one. As the recorder
    // (rpcs3_replay_record.py, NO_VIDEO_FRAMES): a level-start recording never blocked in its first 240 frames is a save
    // that starts in play (LVL030's Valley of Avalar save, lvl030-full): control at +0.
    constexpr int32_t kNoVideoFrames = 240;
    bool wasBlocked = false;
    while (!ReplayOver()) {
        Step();
        if (g_replayLevelExited) break;
        const int32_t since = static_cast<int32_t>(g_frame - frameZero);
        if (g_shotsDir != nullptr) {
            for (uint32_t wanted : g_loadRelativeShots) {
                if (wanted != g_frame - frameZero) continue;
                char path[512];
                std::snprintf(path, sizeof path, "%s/load_%u.png", g_shotsDir, wanted);
                std::printf("shot: %s (+%u, loop frame %u, mode %d)\n", path, wanted, g_frame, g_pCKGameLoop->m_mode);
                dotd::gfx::SaveScreenshot(path);
            }
            // DOTD_NEWGAME_SHOT_STOP=1: the run ends after the last shot (looking at pictures, not a replay check).
            static const bool s_stop = std::getenv("DOTD_NEWGAME_SHOT_STOP") != nullptr;
            if (s_stop && !g_loadRelativeShots.empty() &&
                g_frame - frameZero >= *std::max_element(g_loadRelativeShots.begin(), g_loadRelativeShots.end())) {
                break;
            }
        }
        if (M()->IsInputBlocked() != 0) {
            wasBlocked = true;
        } else if (wasBlocked && g_replayControlSeen < 0) {
            g_replayControlSeen = since;
        } else if (!wasBlocked && g_replayControlSeen < 0 && g_replaySyncLevelStart && since >= kNoVideoFrames) {
            g_replayControlSeen = 0;
        }
        if (dumpPattern != nullptr && !dumped && g_replayControlSeen >= 0 &&
            static_cast<int32_t>(g_frame - frameZero) >= g_replayControlSeen + dumpAfter) {
            char path[512];
            std::snprintf(path, sizeof(path), dumpPattern, static_cast<int>(M()->m_currentLevel));
            std::printf("load: objects dumped at +%d (control +%d) to %s\n", static_cast<int>(g_frame - frameZero),
                        g_replayControlSeen, path);
            if (!Kp3_DumpObjects(path)) std::printf("load: could not write %s\n", path);
            dumped = true;
        }
    }
    std::printf("replay: control +%d, recorded +%d\n", g_replayControlSeen, g_replayControl);
    expect(g_replayControlSeen == g_replayControl, "the replay gives control on the recording's frame");
    failures += FinishReplay(g_replayControlSeen);
    std::printf("probe: %d frames in total, mode %d state %d, %d failure(s)\n", static_cast<int>(g_frame), g_pCKGameLoop->m_mode,
                M()->m_gameState.m_ui8Current, failures);
    cleanup();
    return failures != 0 ? 1 : 0;
}
