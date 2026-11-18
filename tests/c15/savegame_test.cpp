// savegame_test.cpp - C2.8 menus-load: a save written by the ported save flow loads back (Load game).
//
// The test runs itself twice, in a fresh temporary save folder (DOTD_SAVEDATA_DIR), so the load starts from a booted
// game as in dotd.exe:
// - phase "save": New game through the menus to LVL010 in game; a test hook makes another spawn point of the level the
//   current one (as a save point's message 0x204 does) and asks for a save (the game manager's vt+0x104 (0, 0)); the save
//   flow writes BLUS30205-SPYRO08-SAVE-1. The chosen spawn point and its hero start records go to an info file.
// - phase "load": through the menus to the main menu, Load game (item 1): the load flow reads the save (cellSaveDataListLoad2
//   and the game's callbacks, CKLoadingManager_LoadSavedObjects_maybe). Checks: the flow ends with result 0; the objects saved
//   again from the loaded state (SaveObjects in K_GAME_MEMCARD / K_OPTIONS_MEMCARD) equal SYS-DATA and USR-DATA byte for
//   byte (the game state, the player's statistics and play time, the options); then Continue (game menu item 0, single
//   player) loads the level: the structure's current spawn point is the saved one and each hero starts at its record
//   (x and z; y on the ground below it).
// Exit 77 (skipped) without the game data.
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <string>
#include <system_error>
#include <vector>
// #define SAVEGAME_HEAPCHECK 1  // debugging: the CRT heap checked at every allocation after the boot
#ifdef _WIN32
#include <crtdbg.h>
#include <process.h>
#include <stdlib.h>
#endif

#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "Spyro2008/logic/CKS08GameSpawnPoint.h"
#include "boot_helper.h"
#include "k2000/io/IKFile.h"
#include "k2000/io/KFileSystem.h"
#include "k2000/io/SaveData.h"
#include "k2000/logic/CKGameLevel.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/logic/IKPlayer.h"
#include "k2000/logic/io/CKLoadingManager.h"
#include "k2000/memory/KMemBuffer.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/CoreSingletons.h"
#include "Renderware/rwcore/RwCamera.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/IKGameStructure.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "platform/cell/pad.h"
#include "platform/cell/savedata.h"

namespace {
uint16_t g_d1 = 0, g_d2 = 0;
bool TestPad(int port, uint16_t words[24]) {
    if (port != 0) return false;
    std::memset(words, 0, 24 * sizeof(uint16_t));
    words[CELL_PAD_BTN_OFFSET_DIGITAL1] = g_d1;
    words[CELL_PAD_BTN_OFFSET_DIGITAL2] = g_d2;
    for (int i = CELL_PAD_BTN_OFFSET_ANALOG_RIGHT_X; i <= CELL_PAD_BTN_OFFSET_ANALOG_LEFT_Y; ++i) words[i] = 0x80;
    return true;
}
CKS08GameManager* M() { return static_cast<CKS08GameManager*>(g_pEngine->m_gameManager); }
uint32_t g_frame = 0;
int g_last = -1;
int g_failures = 0;

void Step() {
    c15::RunFrame();
    ++g_frame;
    const int key = g_pCKGameLoop->m_mode * 1000 + M()->m_gameState.m_ui8Current;
    if (key != g_last) {
        std::printf("probe: frame %u mode %d state %d menu 0x%02x\n", g_frame, g_pCKGameLoop->m_mode,
                    M()->m_gameState.m_ui8Current, M()->m_interfaceState.m_ui8Current);
        g_last = key;
    }
}
void Press(uint16_t* word, uint16_t button, int wait) {
    *word = button;
    for (int i = 0; i < 4; ++i) Step();
    *word = 0;
    for (int i = 0; i < wait; ++i) Step();
}
void Expect(bool ok, const char* what) {
    std::printf("savegame: %s %s\n", ok ? "ok  " : "FAIL", what);
    if (!ok) ++g_failures;
}

// Press start, then the main menu (game state 6).
bool ToMainMenu() {
    for (int i = 0; i < 3000 && M()->m_gameState.m_ui8Current != 5; ++i) Step();
    for (int i = 0; i < 60; ++i) Step();
    Press(&g_d1, CELL_PAD_CTRL_START, 0);
    for (int i = 0; i < 600 && M()->m_gameState.m_ui8Current != 6; ++i) Step();
    for (int i = 0; i < 90; ++i) Step();
    return M()->m_gameState.m_ui8Current == 6;
}
// Cross until the level runs in game (mode 5, game state 7).
bool CrossIntoGame() {
    for (int k = 0; k < 6 && g_pCKGameLoop->m_mode == 5 && M()->m_gameState.m_ui8Current != 7; ++k) {
        std::printf("probe: Cross in menu 0x%02x\n", M()->m_interfaceState.m_ui8Current);
        Press(&g_d2, CELL_PAD_CTRL_CROSS, 0);
        for (int i = 0; i < 150 && g_pCKGameLoop->m_mode == 5; ++i) Step();
    }
    for (int i = 0; i < 3000 && !(g_pCKGameLoop->m_mode == 5 && M()->m_gameState.m_ui8Current == 7); ++i) Step();
    return g_pCKGameLoop->m_mode == 5 && M()->m_gameState.m_ui8Current == 7;
}

struct Info {
    int32_t level = -1;  // the stage index of the chosen spawn point
    int32_t spawn = -1;  // its index in the stage's spawn point list
    float slots[2][3] = {};
    int32_t hasSlot[2] = {};
};

int PhaseSave(const std::string& infoPath) {
    if (!c15::BootToFrontEnd()) return 77;
    if (!ToMainMenu()) {
        Expect(false, "the main menu");
        return 1;
    }
    Expect(CrossIntoGame(), "New game reaches LVL010 in game");
    for (int i = 0; i < 30; ++i) Step();
    // The test hook: another spawn point of the current level with a start record for hero 0 becomes the current one.
    IKGameStructure* structure = static_cast<IKGameStructure*>(M()->m_gameStructure);
    CKGameLevel* level = structure->GetCurrentLevel();
    Info info;
    if (level != nullptr) {
        for (uint32_t i = 0; i < level->m_vpSpawnPoints.m_ui32NbUsedElt && info.spawn < 0; ++i) {
            CKS08GameSpawnPoint* spawn = static_cast<CKS08GameSpawnPoint*>(level->m_vpSpawnPoints.m_pBlock[i]);
            if (spawn == nullptr || spawn == structure->m_pCurrentSpawnPoint) continue;
            if (spawn->m_iSectorIndex != structure->m_pCurrentSpawnPoint->m_iSectorIndex) continue;
            if (spawn->ResolveSlotPosition(0) == nullptr) continue;
            info.level = level->m_i32StageIndex;
            info.spawn = static_cast<int32_t>(i);
            for (int h = 0; h < 2; ++h) {
                const CKS08GameSpawnPoint::Slot* slot = spawn->ResolveSlotPosition(h);
                info.hasSlot[h] = slot != nullptr;
                if (slot != nullptr) std::memcpy(info.slots[h], slot->m_vPosition, sizeof(info.slots[h]));
            }
            structure->SetCurrentSpawnPoint(spawn);  // vt+0x6c
        }
    }
    Expect(info.spawn >= 0, "another spawn point of the level with a hero start record");
    if (info.spawn < 0) return 1;
    std::printf("savegame: spawn point %d of stage %d: hero 0 at (%.3f, %.3f, %.3f)\n", info.spawn, info.level,
                info.slots[0][0], info.slots[0][1], info.slots[0][2]);
    M()->RequestSave(0, 0);  // vt+0x104, as a save point's 0x93f
    int frames = 0;
    for (; frames < 2000; ++frames) {
        Step();
        if ((M()->m_flags64 & 2u) == 0 && dotd::platform::SaveDataWorkerIdle()) break;
    }
    std::printf("savegame: the save flow took %d frames\n", frames);
    const std::filesystem::path folder = std::filesystem::path(dotd::platform::SaveDataRoot()) / "BLUS30205-SPYRO08-SAVE-1";
    std::error_code ec;
    Expect(std::filesystem::file_size(folder / "SYS-DATA", ec) == 0x4000, "SYS-DATA written (0x4000 bytes)");
    Expect(std::filesystem::file_size(folder / "USR-DATA", ec) == 0x400, "USR-DATA written (0x400 bytes)");
    std::ofstream out(infoPath, std::ios::binary);
    out.write(reinterpret_cast<const char*>(&info), sizeof(info));
    c15::Shutdown();
    return g_failures == 0 ? 0 : 1;
}

// The objects of a save type written again into a memory buffer, compared with the file.
void CompareResave(int32_t type, uint32_t size, const std::filesystem::path& file, const char* what) {
    std::vector<char> expected(size);
    std::ifstream in(file, std::ios::binary);
    in.read(expected.data(), size);
    KMemBuffer buffer;
    buffer.Init(static_cast<int32_t>(size), 0);
    buffer.Resize(static_cast<int32_t>(size));
    IKFile* stream = g_pEngine->m_fileSystem->OpenFile(reinterpret_cast<const char*>(&buffer), 2, KFileSystem::kDeviceMemory,
                                                       KFileSystem::kRootNone, 0, -1, 0);
    bool same = false;
    if (stream != nullptr) {
        g_pEngine->m_pSavingManager->SaveObjects(stream, type, size);
        same = std::memcmp(buffer.m_pData, expected.data(), size) == 0;
        uint32_t differences = 0, first = 0xffffffffu;
        for (uint32_t i = 0; i < size; ++i) {
            if (buffer.m_pData[i] == static_cast<uint8_t>(expected[i])) continue;
            if (differences++ == 0) first = i;
        }
        if (differences != 0) std::printf("savegame: %s: %u bytes differ, the first at +0x%x\n", what, differences, first);
        g_pEngine->m_fileSystem->CloseFile(stream);
    }
    buffer.Free();
    Expect(same, what);
}

int PhaseLoad(const std::string& infoPath) {
    Info info;
    std::ifstream infoFile(infoPath, std::ios::binary);
    infoFile.read(reinterpret_cast<char*>(&info), sizeof(info));
    // Without the save phase's info (a save from elsewhere, e.g. RPCS3's copied in): no spawn point or start checks, the
    // loaded spawn point and the heroes are printed.
    const bool haveInfo = static_cast<bool>(infoFile);
    if (!haveInfo) info = Info();
    if (!c15::BootToFrontEnd()) return 77;
#if defined(_DEBUG) && defined(SAVEGAME_HEAPCHECK)
    _CrtSetReportHook([](int, char*, int*) -> int { __debugbreak(); return 0; });
    _CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_CHECK_ALWAYS_DF);
#endif
    if (!ToMainMenu()) {
        Expect(false, "the main menu");
        return 1;
    }
    // Load game: Down to item 1, Cross.
    Press(&g_d1, CELL_PAD_CTRL_DOWN, 30);
    Press(&g_d2, CELL_PAD_CTRL_CROSS, 0);
    bool started = false;
    int frames = 0;
    for (; frames < 2000; ++frames) {
        Step();
        if ((M()->m_flags64 & 4u) != 0) started = true;
        if (started && (M()->m_flags64 & 4u) == 0 && dotd::platform::SaveDataWorkerIdle()) break;
    }
    Expect(started, "the main menu's item 1 starts the load flow");
    std::printf("savegame: the load flow took %d frames, result 0x%x\n", frames, static_cast<uint32_t>(g_saveDataResult));
    Expect(g_saveDataResult == 0, "the list load succeeded (result 0)");
    // The save folder (the only one in the test's folder).
    std::filesystem::path folder;
    std::error_code ec;
    for (const auto& entry : std::filesystem::directory_iterator(dotd::platform::SaveDataRoot(), ec)) {
        if (entry.is_directory(ec)) folder = entry.path();
    }
    std::printf("savegame: loaded from %s\n", folder.filename().string().c_str());
    CompareResave(K_GAME_MEMCARD, 0x4000, folder / "SYS-DATA", "the loaded game saves again as SYS-DATA");
    CompareResave(K_OPTIONS_MEMCARD, 0x400, folder / "USR-DATA", "the loaded options save again as USR-DATA");
    for (int i = 0; i < 90; ++i) Step();
    Expect(CrossIntoGame(), "Continue reaches the level in game");
    IKGameStructure* structure = static_cast<IKGameStructure*>(M()->m_gameStructure);
    CKGameLevel* level = structure->GetCurrentLevel();
    CKGameSpawnPoint* expected = nullptr;
    if (level != nullptr && level->m_i32StageIndex == info.level && info.spawn < static_cast<int32_t>(level->m_vpSpawnPoints.m_ui32NbUsedElt))
        expected = level->m_vpSpawnPoints.m_pBlock[info.spawn];
    if (level != nullptr) {
        for (uint32_t i = 0; i < level->m_vpSpawnPoints.m_ui32NbUsedElt; ++i) {
            if (level->m_vpSpawnPoints.m_pBlock[i] == structure->m_pCurrentSpawnPoint)
                std::printf("savegame: in game at spawn point %u of stage %d\n", i, level->m_i32StageIndex);
        }
    }
    if (haveInfo)
        Expect(expected != nullptr && structure->m_pCurrentSpawnPoint == expected, "the current spawn point is the saved one");
    // The heroes at their start records (each hero's frame position on the first in-game frame).
    struct Heroes {
        std::vector<CKHkS08Hero*> list;
    } heroes;
    Kp3_ForEachLoadedObject(
        [](IKSerializable* object, uint32_t key, void* context) {
            if (key == CKHkS08Hero::kClassKey) static_cast<Heroes*>(context)->list.push_back(static_cast<CKHkS08Hero*>(object));
        },
        &heroes);
    int checked = 0;
    for (CKHkS08Hero* hero : heroes.list) {
        const uint8_t index = hero->m_ui8Hero;
        const CSGMovable* node = static_cast<const CSGMovable*>(hero->m_pKGLObject);
        if (node == nullptr || node->m_pRwFrame == nullptr) continue;
        const RwV3d& pos = node->m_pRwFrame->modelling.pos;
        if (!haveInfo) std::printf("savegame: hero %u at (%.3f, %.3f, %.3f)\n", index, pos.x, pos.y, pos.z);
        if (index > 1 || info.hasSlot[index] == 0) continue;
        // The record's x and z exactly; y within half a unit (the start puts the hero on the ground below the record).
        const float dx = pos.x - info.slots[index][0], dz = pos.z - info.slots[index][2];
        const float d = std::sqrt(dx * dx + dz * dz), dy = pos.y - info.slots[index][1];
        std::printf("savegame: hero %u at (%.3f, %.3f, %.3f), start record (%.3f, %.3f, %.3f)\n", index, pos.x, pos.y, pos.z,
                    info.slots[index][0], info.slots[index][1], info.slots[index][2]);
        Expect(d < 0.001f && std::fabs(dy) < 0.5f, "the hero starts at the saved spawn point's record");
        ++checked;
    }
    if (haveInfo) Expect(checked > 0, "at least one hero checked");
    c15::Shutdown();
    return g_failures == 0 ? 0 : 1;
}
}  // namespace

int main(int argc, char** argv) {
    std::setvbuf(stdout, nullptr, _IONBF, 0);
    dotd::platform::SetPadSource(&TestPad);
    const char* phase = std::getenv("DOTD_SAVEGAME_PHASE");
    const char* infoPath = std::getenv("DOTD_SAVEGAME_INFO");
    if (phase != nullptr && infoPath != nullptr) {
        if (std::strcmp(phase, "save") == 0) return PhaseSave(infoPath);
        if (std::strcmp(phase, "load") == 0) return PhaseLoad(infoPath);
        return 2;
    }
    (void)argc;
    // The driver: a fresh temporary save folder for both phases (never the user's profile).
    const std::filesystem::path root =
        std::filesystem::temp_directory_path() / ("dotd-savegame-test-" + std::to_string(static_cast<long long>(_getpid())));
    std::error_code ec;
    std::filesystem::remove_all(root, ec);
    std::filesystem::create_directories(root, ec);
    const std::string info = (root / "info.bin").string();
    const std::string saves = (root / "savedata").string();
    _putenv_s("DOTD_SAVEDATA_DIR", saves.c_str());
    _putenv_s("DOTD_SAVEGAME_INFO", info.c_str());
    int code = 0;
    for (const char* name : {"save", "load"}) {
        _putenv_s("DOTD_SAVEGAME_PHASE", name);
        std::printf("savegame: phase %s\n", name);
        const char* args[] = {argv[0], nullptr};
        const intptr_t result = _spawnv(_P_WAIT, argv[0], args);
        std::printf("savegame: phase %s exit %d\n", name, static_cast<int>(result));
        if (result == 77) {
            code = 77;
            break;
        }
        if (result != 0) {
            code = 1;
            break;
        }
    }
    std::filesystem::remove_all(root, ec);
    return code;
}
