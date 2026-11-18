// level_load_test - checkpoint C2.0: every gameplay level and its sectors load headless.
//
// Boots to the front end, then for each level requests it as the menus do (the level's first spawn point
// made current, CKS08GameManager_vf2E8 RequestSpawnPointLevel: modes 5 -> 9 -> 1 -> 4 -> 5) and steps
// frames until the game loop is back in mode 5 with that level current. Then every other sector of the
// level is streamed in through CKLevel_SwitchToSector (the current one unloaded first). For every file
// loaded on the way (LVLnnn, STRnnnss, nnLLCnnn) the loader's checks must show no ported class reading past
// or short of an object's end, no class or category end-offset mismatch, no null object and no missing
// global. Objects of classes whose Load is not ported yet (placeholders) are skipped to their end offset;
// their totals per class are C2.1's work list.
//
// Arguments: level numbers, loaded one after the other in this process. Without arguments every level
// (10 20 30 40 50 60 80 90 100 110 120), three per child process (RunLevelGroups).
// DOTD_LEVEL_LOAD_JSON=path writes the per-level results and the skipped classes as JSON;
// DOTD_DUMP_LEVEL_OBJECTS=pattern (with %03d for the level) each level's objects for work/objects_diff.py.
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <string>
#include <vector>

#include "Spyro2008/logic/CKS08GameManager.h"
#include "boot_helper.h"
#include "k2000/logic/CKGameLevel.h"
#include "k2000/logic/CKGameSpawnPoint.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/io/CKLoadingManager.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/managers/CKSoundManager.h"
#include "k2000/sound/SoundVoiceManager.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/CoreSingletons.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/IKGameStructure.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <psapi.h>
#endif

namespace {

// The process's private bytes in MB (Windows; 0 elsewhere): the unload does not free everything yet (the
// destructors of most level classes are not ported), so a 32-bit process runs out after some levels.
uint32_t PrivateMegabytes() {
#ifdef _WIN32
    PROCESS_MEMORY_COUNTERS_EX counters = {};
    if (GetProcessMemoryInfo(GetCurrentProcess(), reinterpret_cast<PROCESS_MEMORY_COUNTERS*>(&counters),
                             sizeof(counters))) {
        return static_cast<uint32_t>(counters.PrivateUsage >> 20);
    }
#endif
    return 0;
}

struct FileResult {
    std::string file;
    KLoadCheckStats stats;
};

struct LevelResult {
    int level = 0;
    int spawnSector = -2;
    uint32_t frames = 0;
    bool reached = false;
    uint32_t sectors = 0;
    std::vector<FileResult> files;
};

CKS08GameManager* Manager() { return static_cast<CKS08GameManager*>(g_pEngine->m_gameManager); }

// The level's first spawn point in the game structure (GAME.KP3), or null.
CKGameSpawnPoint* FirstSpawnPoint(int level) {
    IKGameStructure* structure = static_cast<IKGameStructure*>(Manager()->m_gameStructure);
    for (uint32_t i = 0; i < structure->m_vpStages.m_ui32NbUsedElt; ++i) {
        CKGameLevel* stage = structure->m_vpStages.m_pBlock[i];
        if (stage == nullptr || stage->m_i32StageIndex != level) continue;
        if (stage->m_vpSpawnPoints.m_ui32NbUsedElt == 0) return nullptr;
        return stage->m_vpSpawnPoints.m_pBlock[0];
    }
    return nullptr;
}

uint32_t ReportCount() {
    uint32_t count = 0;
    Kp3_LoadReports(&count);
    return count;
}

void CollectReports(uint32_t from, LevelResult& result) {
    uint32_t count = 0;
    const KLoadReport* reports = Kp3_LoadReports(&count);
    for (uint32_t i = from; i < count; ++i) result.files.push_back({reports[i].file, reports[i].stats});
}

bool Clean(const KLoadCheckStats& s) {
    return s.portedMismatches == 0 && s.classMismatches == 0 && s.categoryMismatches == 0 && s.nullObjects == 0 &&
           s.providerFailures == 0;
}

// From mode 4, the level exit the game takes from mode 5 (5 -> 9 when a level is requested), without the
// gameplay frame in between: mode 4 left and mode 9 entered (the level told to stop), as the mode machine
// does in CKGameLoop_GameLoop. The next frames then run modes 9 and 1 for the requested level.
void LeaveStartedLevel() {
    CKGameLoop* loop = g_pCKGameLoop;
    IKTime* clock = nullptr;  // the mode handlers' frame clock is not used by modes 4 and 9
    (loop->*CKGameLoop::kModeHandlers[CKGameLoop::kModeStartLevel])(clock, CKGameLoop::kPhaseLeave,
                                                                    CKGameLoop::kModeLevelExit);
    loop->m_mode = CKGameLoop::kModeLevelExit;
    (loop->*CKGameLoop::kModeHandlers[CKGameLoop::kModeLevelExit])(clock, CKGameLoop::kPhaseEnter,
                                                                   CKGameLoop::kModeStartLevel);
}

bool LoadLevel(int level, LevelResult& result) {
    result.level = level;
    const uint32_t firstReport = ReportCount();
    CKS08GameManager* manager = Manager();
    CKGameSpawnPoint* spawnPoint = FirstSpawnPoint(level);
    if (spawnPoint != nullptr) {
        static_cast<IKGameStructure*>(manager->m_gameStructure)->m_pCurrentSpawnPoint = spawnPoint;
        result.spawnSector = spawnPoint->m_iSectorIndex;
        manager->RequestSpawnPointLevel();  // vt+0x2e8, as the menus' New game
    } else {
        manager->RequestLevelChange(level, -2);  // the level's default sector
    }
    if (g_pCKGameLoop->m_mode == CKGameLoop::kModeStartLevel) LeaveStartedLevel();  // after the previous level
    std::printf("level_load: LVL%03d: requested (spawn sector %d)\n", level, result.spawnSector);
    std::fflush(stdout);
    // Until mode 4 (StartLevel: mode 1 has loaded the level, its sector and its LLC, and Start ran). The
    // next frame would be the level's first gameplay frame (mode 5), which needs the level-start runtime of
    // C2.2: the test stops before it.
    for (uint32_t frame = 0; frame < 20000; ++frame) {
        c15::RunFrame();
        ++result.frames;
        if (g_pCKGameLoop->m_mode == CKGameLoop::kModeStartLevel && manager->m_currentLevel == level) {
            result.reached = true;
            break;
        }
        if (g_pCKGameLoop->m_mode == CKGameLoop::kModeQuit) break;
    }
    CKLevel* ckLevel = g_pEngine->m_level;
    result.sectors = ckLevel->m_ui32NbSectors;
    std::printf("level_load: LVL%03d: %s after %u frames, sector %d of %u\n", level,
                result.reached ? "loaded (mode 4)" : "NOT REACHED", result.frames, ckLevel->m_currentSector, result.sectors);
    std::fflush(stdout);
    if (result.reached) {
        // DEV: DOTD_DUMP_LEVEL_OBJECTS=pattern (a printf pattern with the level number, e.g.
        // work/native-objects-lvl%03d.json) writes the loaded objects (GAME, the level, its start sector) for
        // work/objects_diff.py against an RPCS3 dump of that level (live_objects.py --level N).
        if (const char* pattern = std::getenv("DOTD_DUMP_LEVEL_OBJECTS")) {
            // DOTD_DUMP_LEVEL_SECTOR=n: that sector made current first; 0: the current sector unloaded (the
            // level's objects only: in LVL010's in-game RPCS3 dump the sector slots of the level's arrays
            // hold no loaded objects).
            if (const char* sectorText = std::getenv("DOTD_DUMP_LEVEL_SECTOR")) {
                const int32_t sector = std::atoi(sectorText);
                if (sector == 0) {
                    ckLevel->UnloadCurrentSector(0);
                } else if (sector != ckLevel->m_currentSector) {
                    ckLevel->SwitchToSector(sector, 1);
                }
                std::printf("level_load: LVL%03d: dump in sector %d\n", level, ckLevel->m_currentSector);
            }
            char path[512];
            std::snprintf(path, sizeof(path), pattern, level);
            if (!Kp3_DumpObjects(path)) std::printf("level_load: could not write %s\n", path);
        }
        // Every other sector, streamed in as a sector change does (the current one unloaded first).
        const int32_t start = ckLevel->m_currentSector;
        for (uint32_t sector = 1; sector < result.sectors; ++sector) {
            if (static_cast<int32_t>(sector) == start) continue;
            ckLevel->SwitchToSector(static_cast<int32_t>(sector), 1);
            if (ckLevel->m_currentSector != static_cast<int32_t>(sector)) {
                std::printf("level_load: LVL%03d: sector %u not current after the switch (%d)\n", level, sector,
                            ckLevel->m_currentSector);
                ++c15::g_failures;
            }
            // CKSound_Destroy (SoundList_Remove): the unloaded sectors' sounds have left the voice manager's sound
            // list, so StopSectorSounds / PlaySectorAutoSounds never reach a destroyed sound (C2.8 unload).
            const TVector<CKSound*, 100>& sounds = g_pEngine->m_soundManager->m_pVoiceManager->m_vpSounds;
            for (uint32_t i = 0; i < sounds.m_ui32NbUsedElt; ++i) {
                const int32_t soundSector = static_cast<int32_t>(sounds.m_pBlock[i]->m_iSectorIndex);
                if (soundSector > 0 && soundSector != ckLevel->m_currentSector) {
                    std::printf("level_load: LVL%03d: a sound of the unloaded sector %d is still in the sound list\n",
                                level, soundSector);
                    ++c15::g_failures;
                    break;
                }
            }
        }
    }
    CollectReports(firstReport, result);
    return result.reached;
}

// A JSON string's contents (the loader's file names have backslashes).
std::string JsonEscape(const std::string& text) {
    std::string out;
    for (char c : text) {
        if (c == '\\' || c == '"') out += '\\';
        out += c;
    }
    return out;
}

void WriteJson(const char* path, const std::vector<LevelResult>& results) {
    std::FILE* f = std::fopen(path, "wb");
    if (f == nullptr) return;
    std::fprintf(f, "{\"levels\": [");
    for (size_t i = 0; i < results.size(); ++i) {
        const LevelResult& r = results[i];
        std::fprintf(f, "%s\n {\"level\": %d, \"spawn_sector\": %d, \"reached\": %s, \"frames\": %u, \"sectors\": %u, \"files\": [",
                     i == 0 ? "" : ",", r.level, r.spawnSector, r.reached ? "true" : "false", r.frames, r.sectors);
        for (size_t k = 0; k < r.files.size(); ++k) {
            const KLoadCheckStats& s = r.files[k].stats;
            std::fprintf(f,
                         "%s\n  {\"file\": \"%s\", \"objects\": %u, \"skipped\": %u, \"ported_mismatches\": %u, "
                         "\"class_mismatches\": %u, \"category_mismatches\": %u, \"null_objects\": %u, "
                         "\"provider_failures\": %u}",
                         k == 0 ? "" : ",", JsonEscape(r.files[k].file).c_str(), s.objects, s.objectMismatches, s.portedMismatches,
                         s.classMismatches, s.categoryMismatches, s.nullObjects, s.providerFailures);
        }
        std::fprintf(f, "]}");
    }
    std::fprintf(f, "],\n\"skipped_by_class\": {");
    struct Ctx {
        std::FILE* f;
        bool first;
    } ctx = {f, true};
    Kp3_ForEachSkippedTotal(
        [](const char* name, uint32_t count, void* context) {
            Ctx* c = static_cast<Ctx*>(context);
            std::fprintf(c->f, "%s\n \"%s\": %u", c->first ? "" : ",", name, count);
            c->first = false;
        },
        &ctx);
    std::fprintf(f, "}}\n");
    std::fclose(f);
}

}  // namespace

// Without arguments: every level, three per child process (this executable again with the levels as
// arguments), so the level-to-level unload runs between them while a 32-bit process stays far from its
// address-space limit (the unload frees the class arrays, but most level classes' destructors, the texture
// dictionaries' among them, are not ported yet: about 150-200 MB stay behind per level).
int RunLevelGroups(const char* self) {
    const char* const groups[] = {"10 20 30", "40 50 60", "80 90 100", "110 120"};
    int failures = 0;
    for (const char* group : groups) {
        const std::string command = std::string("\"\"") + self + "\" " + group + "\"";
        std::printf("level_load: levels %s in a child process\n", group);
        std::fflush(stdout);
        const int status = std::system(command.c_str());
        if (status == 77) return 77;  // no game data
        if (status != 0) {
            std::printf("FAIL level_load: levels %s: exit status %d\n", group, status);
            ++failures;
        }
    }
    if (failures == 0) std::printf("level_load: all level groups passed\n");
    return failures == 0 ? 0 : 1;
}

int main(int argc, char** argv) {
    std::vector<int> levels;
    for (int i = 1; i < argc; ++i) levels.push_back(std::atoi(argv[i]));
    if (levels.empty()) return RunLevelGroups(argv[0]);

    if (!c15::BootToFrontEnd()) {
        std::printf("level_load: no game data configured: skipped\n");
        return 77;
    }
    // The front end's own sequence (copyrights, logos, press start...) is not needed: no menu opens.
    c15::ParkFrontEndSequence();

    std::vector<LevelResult> results;
    for (int level : levels) {
        LevelResult result;
        const bool reached = LoadLevel(level, result);
        C15_CHECK(reached);
        uint32_t objects = 0, skipped = 0;
        for (const FileResult& file : result.files) {
            objects += file.stats.objects;
            skipped += file.stats.objectMismatches;
            std::printf("level_load:   %-28s %6u objects, %5u skipped, %u ported mismatches, %u class / %u category "
                        "mismatches, %u null, %u provider failures\n",
                        file.file.c_str(), file.stats.objects, file.stats.objectMismatches, file.stats.portedMismatches,
                        file.stats.classMismatches, file.stats.categoryMismatches, file.stats.nullObjects,
                        file.stats.providerFailures);
            if (!Clean(file.stats)) {
                std::printf("FAIL level_load: LVL%03d: %s has load errors\n", level, file.file.c_str());
                ++c15::g_failures;
            }
        }
        std::printf("level_load: LVL%03d: %u files, %u objects, %u skipped (placeholders); %u MB private\n", level,
                    static_cast<uint32_t>(result.files.size()), objects, skipped, PrivateMegabytes());
        std::fflush(stdout);
        results.push_back(result);
        if (!reached) break;  // the game loop is not in a known state any more
    }
    if (const char* json = std::getenv("DOTD_LEVEL_LOAD_JSON")) WriteJson(json, results);

    std::fflush(stdout);
    if (c15::g_failures == 0) std::printf("level_load: all tests passed\n");
    // The game's Cleanup is not run: the shutdown of a gameplay level is not ported.
    std::fflush(stdout);
    std::_Exit(c15::g_failures == 0 ? 0 : 1);
}
