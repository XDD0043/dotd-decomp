// boot_test - checkpoint C1.1 exit test, headless.
//  1. The boot creates and initialises the subsystems in the order measured in the original
//     (outputs/remake/research/boot-and-platform.md section 1.5, then Main_InitGame's tail).
//  2. The mode machine walks 0 -> 1 -> 4 -> 5 and stays in 5 (the front end) with the stand-in loads.
//  3. IKTime produces dt from sys_time_get_system_time: 0 while the clock is stopped (modes 0 and 1),
//     the frame time once mode 4 has restarted it.
// The game's main loop is not used (it ends in exit(0)); the test runs main's setup, then Run().
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "k2000/core/Stub.h"
#include "k2000/io/KFileSystem.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/io/CKLoadingManager.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/CoreSingletons.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/IKTime.h"
#include "k2000/system/CTimeManager.h"
#include "platform/cell/sys_time.h"
#include "platform/config.h"

static int g_failures = 0;
#define CHECK(cond)                                                              \
    do {                                                                         \
        if (!(cond)) {                                                           \
            std::printf("FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond);         \
            ++g_failures;                                                        \
        }                                                                        \
    } while (0)

static int64_t g_now = 1000000;  // microseconds; advanced by 1/60 s per frame
static int64_t FakeTime() { return g_now; }

// Index of the first trace entry that starts with prefix, at or after start; -1 if none.
static int Find(const std::vector<std::string>& trace, const char* prefix, int start = 0) {
    for (int i = start; i < static_cast<int>(trace.size()); ++i) {
        if (trace[i].compare(0, std::strlen(prefix), prefix) == 0) return i;
    }
    return -1;
}

int main() {
    // The boot now loads GAME.KP3, 00GLC, LVL000 and 00LLC000: it needs the game data (dotd.ini or
    // DOTD_USRDIR). Without it the test is skipped, like fs_selftest.
    dotd::platform::Config config;
    dotd::platform::LoadConfig(0, nullptr, config);
    if (config.usrdir.empty()) {
        std::printf("boot: no game data configured (DOTD_USRDIR or dotd.ini); skipped\n");
        return 77;
    }
    dotd::platform::SetSystemTimeSource(&FakeTime);
    RegisterAllClasses();

    // GameMain's setup (k2000/system/CellSysutilCallback.cpp), without its loop.
    CoreSingletons_EnsureCreated();
    g_pEngine->m_fileSystem->SetExecutablePath("/dev_bdvd/PS3_GAME/USRDIR/EBOOT.BIN");
    const char* const argv[] = {"/dev_bdvd/PS3_GAME/USRDIR/EBOOT.BIN"};
    HandleParameters(1, argv);
    CHECK(std::strcmp(g_appConfig.gameName, "Spyro 2008") == 0);
    CHECK(std::strcmp(g_appConfig.titleId, "BLUS-30205") == 0);
    CHECK(g_appConfig.performanceAnalysis == 0);
    g_appConfig.width = 640;  // GameMain's start-up config (the renderer sizes its rasters from it)
    g_appConfig.unk20 = 0;
    g_appConfig.height = 480;
    g_appConfig.flag14 = 1;
    g_appConfig.bitsPerPixel = 0;
    g_appConfig.unk18 = 0;
    CHECK(Main_InitGame() == 1);

    // 1. creation order
    const std::vector<std::string> expected = {
        "create CKCoreManager",       // core singletons (first RegisterClass)
        "create KFileSystem",
        "create CKGameLoop",          // Main_InitGame
        "create JobQueue",            // InitializeCKGameLoopSubsystems, in order
        "create CKErrorTable",
        "create CTimeManager",
        "create CKGraphic",
        "CKGraphic::Init",
        "create CShaderManagerPSGL",  // inside CKGraphic_InitializeModule (key 0x124d)
        "create CRenderer",
        "CRenderer::InitializeStages",
        "create CVideoManager",
        "create CKInput",
        "create KHostFS",
        "KHostFS::Init",
        "create CKSoundManager",
        "CKSoundManager::Init",
        "CVideoManager_InitRenderer",
        "create CKServiceManager",
        "CKServiceManager::CreateServices",
        "KFileSystem_InitSaveDevice",
        "create CKLoadingManager",
        "create CKSavingManager",
        "create CKLevel",
        "CShaderManagerPSGL::Start",
        "CKCoreManager::Init",        // Main_InitGame's tail
        "create CLocManager",
    };
    const std::vector<std::string>& trace = dotd::trace::BootTrace();
    int at = 0;
    for (const std::string& step : expected) {
        const int found = Find(trace, step.c_str(), at);
        if (found < 0) std::printf("missing or out of order: %s\n", step.c_str());
        CHECK(found >= 0);
        if (found >= 0) at = found + 1;
    }

    // 2 + 3. frames
    CKGameLoop* loop = g_pCKGameLoop;
    IKTime* clock = loop->m_timeManager->m_pTime;
    std::vector<int> modes;
    bool zeroWhileStopped = true;
    bool frameDtSeen = false;
    // The loads run on the loader thread while the loading frames sleep 5 ms each (Sys_UsleepMs, as on the
    // PS3), so how many frames the boot takes depends on the machine's load: step until 10 frames after
    // mode 5 is reached (about 20 frames on an idle machine), with a generous cap.
    int framesInFrontEnd = 0;
    for (int frame = 0; frame < 600 && framesInFrontEnd < 10; ++frame) {
        if (loop->m_mode == CKGameLoop::kModeLevel) ++framesInFrontEnd;
        g_now += 16667;
        const uint8_t modeBefore = loop->m_mode;
        CHECK(Run() == 1);
        if (modes.empty() || modes.back() != loop->m_mode) modes.push_back(loop->m_mode);
        if (modeBefore <= CKGameLoop::kModeInit && loop->m_mode <= CKGameLoop::kModeInit && clock->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME] != 0.0f) {
            zeroWhileStopped = false;
        }
        if (modeBefore == CKGameLoop::kModeLevel && loop->m_mode == CKGameLoop::kModeLevel) {
            // IKTime samples seconds as float: the difference of two floats near 1.0 s, not exactly 1/60.
            if (std::fabs(clock->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME] - 0.016667f) < 1e-4f) frameDtSeen = true;
            CHECK(clock->m_eCurrentState == IKTime::RUNNING);
        }
    }
    std::printf("modes:");
    for (int m : modes) std::printf(" %d", m);
    std::printf("\n");
    // C1.4 (sequence): the game manager's first state (1, the auto-load) asks for the save data on its
    // second frame: mode 5 -> 7 (the loop paused) -> 8 -> 2 (the save-data request) -> 8 -> 5, as the
    // 2026-10-18 RPCS3 timeline (gm1-mode7, gm1-mode2, gm4-mode5).
    CHECK((modes == std::vector<int>{0, 1, 4, 5, 7, 8, 2, 8, 5}));
    CHECK(loop->m_mode == CKGameLoop::kModeLevel);
    CHECK(zeroWhileStopped);
    CHECK(frameDtSeen);
    CHECK(Find(trace, "mode 0 -> 1") >= 0 && Find(trace, "mode 1 -> 4") > Find(trace, "mode 0 -> 1") &&
          Find(trace, "mode 4 -> 5") > Find(trace, "mode 1 -> 4"));
    // C1.2: the four files load in the original order through the worker thread, every object is created
    // (counts from work/scratch-impl1-loading, kp3_parse.py), every reference and global resolves, and
    // every class block and category ends exactly at its end offset.
    CHECK(Find(trace, "load GAME.KP3") >= 0);
    CHECK(Find(trace, "load GAME.KP3") < Find(trace, "load 00GLC.KP3"));
    CHECK(Find(trace, "load 00GLC.KP3") < Find(trace, "boot load:"));
    CHECK(Find(trace, "boot load:") < Find(trace, "mode 0 -> 1"));
    CHECK(Find(trace, "load LVL000\\LVL000.KP3") > Find(trace, "mode 0 -> 1"));
    CHECK(Find(trace, "load LVL000/00LLC000.KP3") > Find(trace, "load LVL000\\LVL000.KP3"));
    struct Expected {
        const char* file;
        uint32_t objects;
    };
    const Expected expectedFiles[] = {
        {"GAME.KP3", 2668}, {"00GLC.KP3", 5}, {"LVL000\\LVL000.KP3", 5923}, {"LVL000/00LLC000.KP3", 6}};
    uint32_t reportCount = 0;
    const KLoadReport* reports = Kp3_LoadReports(&reportCount);
    CHECK(reportCount == 4);
    for (uint32_t i = 0; i < reportCount && i < 4; ++i) {
        const KLoadCheckStats& st = reports[i].stats;
        std::printf("%-22s %5u objects, %u skipped (%u ported), %u class / %u category mismatches, %u provider "
                    "failures, %u null\n",
                    reports[i].file, st.objects, st.objectMismatches, st.portedMismatches, st.classMismatches,
                    st.categoryMismatches, st.providerFailures, st.nullObjects);
        CHECK(std::strcmp(reports[i].file, expectedFiles[i].file) == 0);
        CHECK(st.objects == expectedFiles[i].objects);
        CHECK(st.classMismatches == 0 && st.categoryMismatches == 0);
        CHECK(st.providerFailures == 0 && st.nullObjects == 0);
        CHECK(st.portedMismatches == 0);  // every ported Load reads exactly its object's data
    }
    // The game manager came from GAME.KP3: its first field (the requested level, 0 = LVL000) was read
    // and consumed by Mode1_Init. Its 7 player references (GAME.KP3 bytes: 0x000c780c, 0x0008780c, ...)
    // are CKS08Player indices 6, 4, 3, 2, 1, 0, 5, resolved by DecodeObjectId's GAME-list search.
    CDefaultGameManager* manager = g_pEngine->m_gameManager;
    CHECK(manager != nullptr && manager->GetClassID() == 0x1e1);
    if (manager != nullptr) {
        CHECK(manager->m_currentLevel == 0 && manager->m_requestedLevel == -1);
        const int playerIndex[7] = {6, 4, 3, 2, 1, 0, 5};
        for (int i = 0; i < 7; ++i) {
            IKSerializable* player = reinterpret_cast<IKSerializable*>(reinterpret_cast<uint8_t*>(manager->m_playerArray) +
                                                           manager->m_playerStride * playerIndex[i]);
            CHECK(manager->m_players[i] == player);
        }
        CHECK(manager->m_pBootingVideo != nullptr);  // a UUID reference (fdffffff + UUID) into the GAME objects
    }

    // DEV: DOTD_DUMP_OBJECTS=path writes the loaded objects for work/objects_diff.py (use the x86 parity
    // build, where the classes have the PS3 layout).
    if (const char* dumpPath = std::getenv("DOTD_DUMP_OBJECTS")) {
        CHECK(Kp3_DumpObjects(dumpPath));
        std::printf("boot: objects dumped to %s\n", dumpPath);
    }

    Cleanup();
    CHECK(g_pEngine == nullptr);

    if (g_failures == 0) std::printf("boot: all tests passed\n");
    return g_failures == 0 ? 0 : 1;
}
