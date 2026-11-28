// gm_c16_test - checkpoint C1.6, family gm: the game manager's front end after the boot sequence, headless,
// one game frame at a time (1/60 s of the fake clock), driven through the pad shim (platform/cell/pad).
//
//  1. The "Flash Manager" input mapping (project "Flash Manager", configuration 1): which entries each pad
//     button sets (validate 4, back 5, start 0xe, directions 0-3 / 6-9), as cellPadGetData reports them.
//  2. Press start idles: after 30 s of game time (CKS08MenuPressStart, TOC2 -0x7b98) the demo video
//     (game manager +0x2e0) starts; START ends it and the press-start screen comes back (10 s timer).
//  3. START -> the main menu (game state 6, menu 9).
//  4. The language switch as the options' language item makes it (IKGameManager_CycleLanguageOption):
//     the game loop goes 5 -> 7 -> 8 -> 3 -> 8 -> 5, the GLC/LLC of the new language are loaded
//     (CLocManager +0xb2), the texts change; then back to language 0.
//  5. The load-game flow with no save data (IKGameManager_SetFlag64Bit2_maybe): 5 -> 7 -> 8 -> 2, the
//     system's "There is no saved data." (cellSaveDataListLoad2 then returns CANCEL), OK, back to mode 5
//     on the main menu (IKCommonGameManager_vf240(1)).
//  6. New game as the menus start it (CKS08GameManager_vf2E8): the level of the current spawn point is
//     requested and the game loop leaves the front end (5 -> 9 -> 1, "level load requested").
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "Spyro2008/logic/CKS08GameManager.h"
#include "boot_helper.h"
#include "k2000/graphical/system/IKVideo.h"
#include "k2000/input/CKInputDico.h"
#include "k2000/logic/ui/CKLocText.h"
#include "k2000/logic/ui/CLocManager.h"
#include "k2000/managers/CKInput.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/CoreSingletons.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/IKGameStructure.h"
#include "platform/cell/msgdialog.h"
#include "platform/cell/pad.h"

namespace {

uint16_t g_digital1 = 0;  // CELL_PAD_BTN_OFFSET_DIGITAL1 (start, select, d-pad)
uint16_t g_digital2 = 0;  // CELL_PAD_BTN_OFFSET_DIGITAL2 (cross, circle, ...)

bool TestPad(int port, uint16_t words[24]) {
    if (port != 0) return false;
    std::memset(words, 0, 24 * sizeof(uint16_t));
    words[CELL_PAD_BTN_OFFSET_DIGITAL1] = g_digital1;
    words[CELL_PAD_BTN_OFFSET_DIGITAL2] = g_digital2;
    for (int i = CELL_PAD_BTN_OFFSET_ANALOG_RIGHT_X; i <= CELL_PAD_BTN_OFFSET_ANALOG_LEFT_Y; ++i) words[i] = 0x80;
    return true;
}

CKS08GameManager* Manager() { return static_cast<CKS08GameManager*>(g_pEngine->m_gameManager); }

uint32_t g_frame = 0;
int g_lastMode = -1, g_lastState = -1, g_lastMenu = -1;
std::vector<int> g_modes;  // the game loop's modes in order (changes only)

void Step() {
    c15::RunFrame();
    ++g_frame;
    CKS08GameManager* m = Manager();
    const int mode = g_pCKGameLoop->m_mode, state = m->m_gameState.m_ui8Current, menu = m->m_interfaceState.m_ui8Current;
    if (mode != g_lastMode || state != g_lastState || menu != g_lastMenu) {
        std::printf("gm_c16: frame %5u  loop mode %d  game state %3d  menu 0x%02x\n", g_frame, mode, state, menu);
        if (mode != g_lastMode) g_modes.push_back(mode);
        g_lastMode = mode;
        g_lastState = state;
        g_lastMenu = menu;
    }
}

void Press(uint16_t* word, uint16_t bit, int frames) {
    *word = bit;
    for (int i = 0; i < frames; ++i) Step();
    *word = 0;
}

// The entries of the "Flash Manager" project's configuration 1 that read pressed (0xff).
std::string PressedEntries(int config = 1) {
    CKInput* input = g_pEngine->m_input;
    const int32_t project = input->FindMappingIndexByName("Flash Manager");
    if (project < 0) return "?";
    const CKInputDico* dico = &input->m_aaInputDico[project][config];
    std::string out;
    for (int i = 0; i < dico->m_ui8NbAction; ++i) {
        const uint8_t state = dico->GetButtonState(i);
        if (state != 0) out += (out.empty() ? "" : ",") + std::to_string(i) + (state == 0xff ? "" : "=" + std::to_string(state));
    }
    return out.empty() ? "-" : out;
}

// A text of the loc manager's list as narrow ASCII (others as '?').
std::string TextAt(uint32_t index) {
    CLocManager* loc = g_pEngine->m_locManager;
    if (index >= loc->m_vpTexts.m_ui32NbUsedElt) return "";
    const uint16_t* s = loc->m_vpTexts.m_pBlock[index]->m_pText;
    std::string out;
    for (; s != nullptr && *s != 0 && out.size() < 40; ++s) out += (*s < 0x80) ? static_cast<char>(*s) : '?';
    return out;
}

std::vector<std::u16string> AllTexts() {
    CLocManager* loc = g_pEngine->m_locManager;
    std::vector<std::u16string> out;
    for (uint32_t i = 0; i < loc->m_vpTexts.m_ui32NbUsedElt; ++i) {
        const uint16_t* s = loc->m_vpTexts.m_pBlock[i]->m_pText;
        std::u16string text;
        for (; s != nullptr && *s != 0; ++s) text += static_cast<char16_t>(*s);
        out.push_back(text);
    }
    return out;
}

uint32_t CountChanged(const std::vector<std::u16string>& before) {
    const std::vector<std::u16string> now = AllTexts();
    uint32_t changed = 0;
    for (size_t i = 0; i < before.size() && i < now.size(); ++i) changed += before[i] != now[i] ? 1 : 0;
    return changed;
}

bool Contains(const std::vector<int>& seq, const std::vector<int>& sub) {
    if (sub.empty()) return true;
    for (size_t i = 0; i + sub.size() <= seq.size(); ++i) {
        if (std::equal(sub.begin(), sub.end(), seq.begin() + static_cast<long>(i))) return true;
    }
    return false;
}

}  // namespace

int main() {
    std::setvbuf(stdout, nullptr, _IONBF, 0);
    dotd::platform::SetPadSource(&TestPad);
    if (!c15::BootToFrontEnd()) {
        std::printf("gm_c16: no game data configured; skipped\n");
        return 77;
    }
    CKS08GameManager* manager = Manager();

    // Up to press start with no input.
    while (g_frame < 3000 && manager->m_gameState.m_ui8Current != 5) Step();
    C15_CHECK(manager->m_gameState.m_ui8Current == 5);
    const uint32_t pressStartFrame = g_frame;  // the frame the press-start menu opened (its idle timer: 30 s)

    // 1. The mapping, one button at a time (held for 2 frames: the actions update in PreUpdate).
    struct Button {
        const char* name;
        uint16_t* word;
        uint16_t bit;
        std::string entries;
    } buttons[] = {
        {"cross", &g_digital2, CELL_PAD_CTRL_CROSS, ""},      {"circle", &g_digital2, CELL_PAD_CTRL_CIRCLE, ""},
        {"triangle", &g_digital2, CELL_PAD_CTRL_TRIANGLE, ""}, {"square", &g_digital2, CELL_PAD_CTRL_SQUARE, ""},
        {"up", &g_digital1, CELL_PAD_CTRL_UP, ""},            {"down", &g_digital1, CELL_PAD_CTRL_DOWN, ""},
        {"left", &g_digital1, CELL_PAD_CTRL_LEFT, ""},        {"right", &g_digital1, CELL_PAD_CTRL_RIGHT, ""},
    };
    for (Button& b : buttons) {
        *b.word = b.bit;
        std::string frames;
        for (int i = 0; i < 3; ++i) {
            Step();
            const std::string now = PressedEntries();
            if (b.entries.empty() && now != "-") b.entries = now;
            frames += " [" + now + " | config 0: " + PressedEntries(0) + "]";
        }
        *b.word = 0;
        Step();
        frames += " release [" + PressedEntries() + "]";
        Step();
        if (b.entries.empty()) b.entries = "-";
        std::printf("gm_c16: mapping: %-8s ->%s\n", b.name, frames.c_str());
    }
    // Cross sets validate (4) and Circle back (5) for one frame (with their one-frame twins 18 / 19); the
    // d-pad sets 8 up, 9 down, 6 left, 7 right while held.
    C15_CHECK(buttons[0].entries == "4,18");
    C15_CHECK(buttons[1].entries == "5,19");
    C15_CHECK(buttons[4].entries == "8" && buttons[5].entries == "9" && buttons[6].entries == "6" &&
              buttons[7].entries == "7");

    // 2. The idle timer: no input until the demo video plays.
    IKVideo* demo = manager->GetDemoVideo();
    C15_CHECK(demo != nullptr);
    while (g_frame < pressStartFrame + 2400 && demo != nullptr && (demo->m_baData & 1) == 0) Step();
    const uint32_t demoFrame = g_frame;
    C15_CHECK(demo != nullptr && (demo->m_baData & 1) != 0);
    std::printf("gm_c16: demo video started %u frames after the press-start screen opened\n", demoFrame - pressStartFrame);
    C15_CHECK(demoFrame - pressStartFrame >= 1795 && demoFrame - pressStartFrame <= 1805);  // 30 s at 60 fps
    for (int i = 0; i < 120; ++i) Step();
    C15_CHECK((demo->m_baData & 1) != 0);
    // START ends the demo (CKInput_IsMenuSkipPressed_maybe: validate or start).
    Press(&g_digital1, CELL_PAD_CTRL_START, 4);
    for (int i = 0; i < 4; ++i) Step();
    C15_CHECK((demo->m_baData & 1) == 0);
    C15_CHECK(manager->m_gameState.m_ui8Current == 5);
    std::printf("gm_c16: demo stopped by START at frame %u (game state %d)\n", g_frame, manager->m_gameState.m_ui8Current);
    for (int i = 0; i < 60; ++i) Step();

    // 3. START -> the main menu.
    const uint32_t startFrame = g_frame + 1;
    Press(&g_digital1, CELL_PAD_CTRL_START, 6);
    while (g_frame < startFrame + 600 && manager->m_gameState.m_ui8Current != 6) Step();
    for (int i = 0; i < 90; ++i) Step();
    C15_CHECK(manager->m_gameState.m_ui8Current == 6 && manager->m_interfaceState.m_ui8Current == 9);

    // The options in use at the main menu (the defaults RestoreDefaultOptions applied in mode 4) as RPCS3
    // shows them at press start (live read 2026-10-18): language 0, no subtitles, +0x05 1, sound output 4,
    // 4:3, volumes 1.0, vibration on, no screen offset, autosave on, brightness 5.
    {
        const SGameOptions& o = manager->m_currentOptions;
        C15_CHECK(o.m_ui32Language == 0 && o.m_bSubtitles == 0 && o.m_bTutorialInfoPopups == 1 && o.m_ui32SoundOutput == 4 &&
                  o.m_ui32AspectRatio == 0);
        C15_CHECK(o.m_afVolumes[0] == 1.0f && o.m_afVolumes[1] == 1.0f && o.m_afVolumes[2] == 1.0f);
        C15_CHECK(o.m_abVibration[0] == 1 && o.m_abVibration[1] == 1 && o.m_i32ScreenOffsetX == 0 &&
                  o.m_i32ScreenOffsetY == 0 && o.m_bAutosave == 1 && o.m_ui32Brightness == 5);
    }

    // 4. The language switch.
    CLocManager* loc = g_pEngine->m_locManager;
    const std::vector<std::u16string> beforeTexts = AllTexts();
    const uint32_t probe = 0x24;  // an example text printed before and after
    const std::string before = TextAt(probe);
    std::printf("gm_c16: languages %u, current %u; text %u: \"%s\"\n", loc->m_ui16NbLanguage, loc->m_languageIndex, probe,
                before.c_str());
    manager->BackupOptions();  // the options menu opening (GameManager_BackupOptions_maybe)
    g_modes.clear();
    g_modes.push_back(g_pCKGameLoop->m_mode);
    const uint32_t switchFrame = g_frame;
    manager->CycleLanguageOption(0);
    C15_CHECK(manager->m_i32RequestedLanguage == 1);
    uint32_t back = 0;
    while (g_frame < switchFrame + 1200) {
        Step();
        if (g_pCKGameLoop->m_mode == CKGameLoop::kModeLevel && manager->m_i32RequestedLanguage == -1) {
            back = g_frame;
            break;
        }
    }
    const std::string after = TextAt(probe);
    std::printf("gm_c16: language switch: back in mode 5 after %u frames; language %u; text %u: \"%s\"\n",
                back - switchFrame, loc->m_languageIndex, probe, after.c_str());
    C15_CHECK(back != 0);
    C15_CHECK(loc->m_languageIndex == 1 && loc->m_bGameLocalizedDataValid == 1);
    C15_CHECK(Contains(g_modes, {CKGameLoop::kModeLevel, CKGameLoop::kModeLoading, CKGameLoop::kModeInGame,
                                 CKGameLoop::kModePauseMenu, CKGameLoop::kModeInGame, CKGameLoop::kModeLevel}));
    const uint32_t changed = CountChanged(beforeTexts);
    std::printf("gm_c16: %u of %u texts differ in language 1\n", changed, static_cast<uint32_t>(beforeTexts.size()));
    C15_CHECK(changed > beforeTexts.size() / 2);
    for (int i = 0; i < 30; ++i) Step();
    C15_CHECK(manager->m_gameState.m_ui8Current == 6 && manager->m_interfaceState.m_ui8Current == 9);
    // Back to language 0.
    manager->CycleLanguageOption(1);
    const uint32_t switchBack = g_frame;
    while (g_frame < switchBack + 1200 && !(g_pCKGameLoop->m_mode == CKGameLoop::kModeLevel && manager->m_i32RequestedLanguage == -1)) Step();
    C15_CHECK(loc->m_languageIndex == 0 && TextAt(probe) == before && CountChanged(beforeTexts) == 0);
    manager->CommitEditedOptions();
    for (int i = 0; i < 30; ++i) Step();

    // 5. Load game with no save data: the system's message, answered with Cross (OK).
    g_modes.clear();
    g_modes.push_back(g_pCKGameLoop->m_mode);
    manager->SetFlag64Bit2();
    uint32_t dialogFrame = 0;
    for (uint32_t i = 0; i < 300 && dialogFrame == 0; ++i) {
        Step();
        if (dotd::platform::MsgDialogText() != nullptr) dialogFrame = g_frame;
    }
    C15_CHECK(dialogFrame != 0);
    std::printf("gm_c16: load game: dialog \"%s\" at frame %u\n",
                dotd::platform::MsgDialogText() != nullptr ? dotd::platform::MsgDialogText() : "", dialogFrame);
    for (int i = 0; i < 30; ++i) Step();
    C15_CHECK(g_pCKGameLoop->m_mode == CKGameLoop::kModeResume);
    C15_CHECK(dotd::platform::MsgDialogText() != nullptr && std::string(dotd::platform::MsgDialogText()) == "There is no saved data.");
    Press(&g_digital2, CELL_PAD_CTRL_CROSS, 3);  // OK
    for (int i = 0; i < 60 && g_pCKGameLoop->m_mode != CKGameLoop::kModeLevel; ++i) Step();
    C15_CHECK(g_pCKGameLoop->m_mode == CKGameLoop::kModeLevel && (manager->m_flags64 & 4) == 0);
    C15_CHECK(Contains(g_modes, {CKGameLoop::kModeLevel, CKGameLoop::kModeLoading, CKGameLoop::kModeInGame,
                                 CKGameLoop::kModeResume, CKGameLoop::kModeInGame, CKGameLoop::kModeLevel}));
    for (int i = 0; i < 10; ++i) Step();

    // 6. New game: the spawn point's level requested; the game loop leaves the front end.
    // The game structure's current spawn point is set by CKS08GameManager_ResetGameProgress_maybe (0x4f80f8,
    // the players' game states; not ported): RPCS3 has LVL010 sector 1 there at the front end (live read
    // 2026-10-18). Without it the request is made as vf2E8 makes it, with those values.
    IKGameStructure* structure = static_cast<IKGameStructure*>(manager->m_gameStructure);
    {
        g_modes.clear();
        g_modes.push_back(g_pCKGameLoop->m_mode);
        if (structure->m_pCurrentSpawnPoint != nullptr) manager->RequestSpawnPointLevel();
        else manager->RequestLevelChange(10, 1);
        std::printf("gm_c16: new game: level %d sector %d requested\n", manager->m_requestedLevel, manager->m_requestedSector);
        C15_CHECK(manager->m_requestedLevel == 10 && manager->m_i32FrontEndEntryMenu == 2);
        for (int i = 0; i < 120 && g_pCKGameLoop->m_mode != CKGameLoop::kModeInit; ++i) Step();
        C15_CHECK(Contains(g_modes, {CKGameLoop::kModeLevel, CKGameLoop::kModeLevelExit, CKGameLoop::kModeInit}));
    }

    dotd::platform::SetPadSource(nullptr);
    std::fflush(stdout);
    if (c15::g_failures == 0) std::printf("gm_c16: all tests passed\n");
    // The level load itself (mode 1 with LVL010) is C2: leave without the game's cleanup.
    std::_Exit(c15::g_failures == 0 ? 0 : 1);
}
