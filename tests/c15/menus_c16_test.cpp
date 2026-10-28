// menus_c16_test - checkpoint C1.6, family menus: the front-end menus driven by the pad shim, headless, one
// game frame at a time (1/60 s). From the main menu: Cross (main menu item 0) -> "Menu Game" (6), down x2 to
// item 3 and Cross -> "Menu Option PS3" (0x19); there right on item 0 (the language, a two-part item in mode
// 1) changes the language option; up x2 to item 9 and Cross -> the sound options (0x1c), Circle back; up x2,
// right to item 13 and Cross -> the video options (0xe), Circle back; Circle -> the game menu.
//
// Logged: every change of the shown menu (CKS08GameManager +0x30d) with its frame and the getURL labels the
// Flash movies send. Checked against the RPCS3 capture outputs/remake/maestro/labels-labels-20261018-014910
// (work/flash_labels_live.py; movie #0 main menu, #2 game menu, #28 options PS3, #15 bonus):
//   main menu "close" (validated) -> game menu drawn: 12 frames (5532 -> 5544, 6119 -> 6132: 13);
//   the game menu's opening animation ends (label 3, "onMenu_OpeningAnimEnd") 58 frames after it opens;
//   game menu item 3 -> options drawn with no closing animation (a direct request, 6190 .. 6247);
//   options back ("close" 7025) -> game menu drawn 7042 (17 frames).
// The capture never entered the sound, video or language screens; their order and the items that lead there
// (the buttons' state-4 menu transitions, read live: options item 9 -> 0x1c, item 13 -> 0xe, item 15 -> 6)
// are checked, not their timing.
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rpprtstd/RpPrtStdRuntime.h"
#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rt2d/Rt2d.h"
#include "Renderware/rt2danim/Rt2dAnim.h"
#include "Renderware/rt2danim/Rt2dAnimPrivate.h"
#include "Spyro2008/logic/CKMenuBase114c.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "boot_helper.h"
#include "k2000/graphical/ui/CKFlashManager.h"
#include "k2000/graphical/ui/CKFlashUI.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/render/CRenderer.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/misc/CKInterfaceButtonBase.h"
#include "k2000/misc/Engine.h"
#include "platform/cell/pad.h"
#include "platform/config.h"
#include "platform/gfx/device.h"
#include "platform/sdl/app.h"

namespace {

uint16_t g_digital1 = 0, g_digital2 = 0;
uint32_t g_frame = 0;

bool TestPad(int port, uint16_t words[24]) {
    if (port != 0) return false;
    std::memset(words, 0, 24 * sizeof(uint16_t));
    words[CELL_PAD_BTN_OFFSET_DIGITAL1] = g_digital1;
    words[CELL_PAD_BTN_OFFSET_DIGITAL2] = g_digital2;
    for (int i = CELL_PAD_BTN_OFFSET_ANALOG_RIGHT_X; i <= CELL_PAD_BTN_OFFSET_ANALOG_LEFT_Y; ++i) words[i] = 0x80;
    return true;
}

struct Received {
    uint32_t frame;
    int32_t movie;
    std::string label;
};
std::vector<Received> g_received;

int32_t MovieOf(Rt2dMaestro* maestro) {
    CKFlashManager* manager = g_pEngine->m_flashManager;
    for (uint32_t i = 0; i < manager->m_ui32NbFlashUI; ++i)
        if (manager->GetInterfaceByIndex(i)->m_pMaestro == maestro) return static_cast<int32_t>(i);
    return -1;
}

Rt2dMessage* LoggingHandler(Rt2dMaestro* maestro, Rt2dMessage* message) {
    if (message->messageType == rt2dMESSAGETYPEGETURL) {
        Rt2dStringLabel* label = Rt2dMaestroGetStringLabelByIndex(maestro, message->intParam1);
        const RwChar* name = label != nullptr ? Rt2dMaestroGetStringLabelName(maestro, label) : nullptr;
        g_received.push_back(Received{g_frame, MovieOf(maestro), name != nullptr ? name : "?"});
        std::printf("menus: frame %5u  #%-2d %s\n", g_frame, MovieOf(maestro), name != nullptr ? name : "?");
    }
    return CKFlashManager::HandleMaestroEvent(maestro, message);
}

CKS08GameManager* Manager() { return static_cast<CKS08GameManager*>(g_pEngine->m_gameManager); }
uint8_t Menu() { return Manager()->m_interfaceState.m_ui8Current; }
CKMenuBase114c* MenuObject(uint8_t id) { return static_cast<CKMenuBase114c*>(Manager()->Vf344()[id]); }

struct Change {
    uint32_t frame;
    int menu;
};
std::vector<Change> g_changes;

void Step() {
    c15::RunFrame();
    ++g_frame;
    if (g_changes.empty() || g_changes.back().menu != Menu()) {
        g_changes.push_back(Change{g_frame, Menu()});
        std::printf("menus: frame %5u  menu 0x%02x  (game state %d)\n", g_frame, Menu(), Manager()->m_gameState.m_ui8Current);
    }
}

void Run(uint32_t frames) {
    for (uint32_t i = 0; i < frames; ++i) Step();
}

// Holds the buttons for `frames` frames, then releases them for one frame.
void Press(uint16_t digital1, uint16_t digital2, uint32_t frames = 4) {
    g_digital1 = digital1;
    g_digital2 = digital2;
    Run(frames);
    g_digital1 = g_digital2 = 0;
    Step();
}

// Runs until menu `id` is shown and accepts input (opening animation ended, open delay over), at most `limit`
// frames. Returns the frame it was shown at, or 0.
uint32_t WaitMenuReady(uint8_t id, uint32_t limit) {
    uint32_t shown = 0;
    for (uint32_t i = 0; i < limit; ++i) {
        if (Menu() == id && shown == 0) shown = g_frame;
        // Ready: the opening animation ended (+0x61) and the 0.5 s open delay (+0x7c) ran out.
        if (Menu() == id && MenuObject(id)->m_unk60[1] != 0 && MenuObject(id)->m_fUnk7c <= 0.0f) return shown;
        Step();
    }
    return Menu() == id ? shown : 0;
}

uint8_t Focus(uint8_t id) { return MenuObject(id)->m_unk6c[0]; }

void PrintButtons(uint8_t id) {
    CKMenuBase114c* menu = MenuObject(id);
    std::printf("menus: menu 0x%02x focus %d, buttons:", id, menu->m_unk6c[0]);
    for (uint32_t i = 0; i < menu->m_apButtons.m_ui32NbUsedElt; ++i) {
        auto* b = static_cast<CKInterfaceButtonBase*>(menu->m_apButtons.m_pBlock[i]);
        if (b != nullptr) std::printf(" [%u state %d flags %02x]", i, b->m_ui8State, b->m_baFlags);
    }
    std::printf("\n");
}

// The menus' particle nodes (the renderer's secondary root): of the shown ones (not hidden), how many emit,
// their live particles and the PTank particles written this frame.
struct ParticleCensus {
    uint32_t nodes = 0, active = 0, live = 0, ptank = 0;
};
ParticleCensus CountParticles(bool print = true) {
    ParticleCensus census;
    CRenderer* renderer = g_pEngine->m_graphic->m_renderer;
    auto* root = static_cast<CSGBranch*>(renderer->m_pSecondaryRootNode);
    if (root == nullptr) return census;
    for (CSGLeaf* leaf = root->m_lChildList; leaf != nullptr; leaf = leaf->m_pNext) {
        if (((leaf->GetClassID() << 6) | leaf->GetClassType()) != CParticlesNodeFx::kClassKey) continue;
        RpPrtStdEmitter* emitter = static_cast<CParticlesNodeFx*>(leaf)->m_pRpPrtStdEmitter;
        ++census.nodes;
        if (emitter == nullptr || (leaf->m_sgProperties & 4) != 0) continue;  // hidden nodes are not drawn
        if (emitter->prtActive > 0) ++census.active;
        census.live += static_cast<uint32_t>(emitter->prtActive > 0 ? emitter->prtActive : 0);
        const int32_t offset = RpPrtStdPropTabGetPropOffset(emitter->emtClass->propTab, 6);
        if (offset < 0) continue;
        auto* ptank = reinterpret_cast<RpPrtStdEmitterPTank*>(reinterpret_cast<uint8_t*>(emitter) + offset);
        if (ptank->pTank != nullptr) census.ptank += ptank->pTank->ptank->numPrt;
    }
    if (print) std::printf("menus: particles: %u nodes, %u emitting, %u live, %u in PTanks\n", census.nodes, census.active,
                census.live, census.ptank);
    return census;
}

// Optional screenshots (DOTD_GFX_OUT = a directory): the menus drawn through the GL backend, for the
// comparison with RPCS3 captures (work/frame_compare.py). Without it the test stays headless.
bool g_shots = false;
void Shot(const char* name) {
    if (!g_shots) return;
    const std::string path = std::string(std::getenv("DOTD_GFX_OUT")) + "/" + name;
    std::printf("menus: %s%s\n", path.c_str(), dotd::gfx::SaveScreenshot(path.c_str()) ? "" : " (NOT SAVED)");
}

}  // namespace

int main() {
    std::setvbuf(stdout, nullptr, _IONBF, 0);
    if (const char* out = std::getenv("DOTD_GFX_OUT"); out != nullptr && *out != 0) {
        dotd::platform::Config& config = dotd::platform::MutableConfig();
        dotd::platform::LoadConfig(0, nullptr, config);
        config.hiddenWindow = true;
        config.vsync = false;
        config.frameRate = 0;
        g_shots = dotd::platform::sdl::Init(config) && dotd::gfx::Init(1280, 720);
    }
    dotd::platform::SetPadSource(&TestPad);
    if (!c15::BootToFrontEnd()) {
        std::printf("menus: no game data configured; skipped\n");
        return 77;
    }
    CKFlashManager* flash = g_pEngine->m_flashManager;
    for (uint32_t i = 0; i < flash->m_ui32NbFlashUI; ++i) {
        CKFlashUI* ui = flash->GetInterfaceByIndex(i);
        if (ui->m_pMaestro != nullptr) Rt2dMaestroSetMessageHandler(ui->m_pMaestro, LoggingHandler);
    }

    // Boot sequence to press start, START, the main menu ready.
    while (g_frame < 3000 && Manager()->m_gameState.m_ui8Current != 5) Step();
    C15_CHECK(Manager()->m_gameState.m_ui8Current == 5);
    Run(30);
    Press(CELL_PAD_CTRL_START, 0, 6);
    const uint32_t mainShown = WaitMenuReady(9, 600);
    C15_CHECK(mainShown != 0);
    PrintButtons(9);
    C15_CHECK(Focus(9) == 0);
    Run(60);
    Shot("c16_main_menu.png");
    // The main menu's sparkles: moving the cursor puts the newly focused button's particle node (placed on
    // its Flash hot spot) into a burst; a few frames later its particles are live in its PTank. Back up again.
    {
        Press(CELL_PAD_CTRL_DOWN, 0, 2);
        Run(8);
        Shot("c16_main_menu_sparkles.png");
        const ParticleCensus census = CountParticles();
        C15_CHECK(census.nodes == 47);
        C15_CHECK(census.active > 0 && census.live > 0 && census.ptank > 0);
        Press(CELL_PAD_CTRL_UP, 0, 2);
        Run(60);
    }

    // Main menu item 0 (Cross): the game menu.
    const uint32_t pressMain = g_frame + 1;
    Press(0, CELL_PAD_CTRL_CROSS);
    const uint32_t gameShown = WaitMenuReady(6, 600);
    std::printf("menus: main menu validated at %u, game menu shown at %u (%d frames)\n", pressMain, gameShown,
                static_cast<int>(gameShown - pressMain));
    C15_CHECK(gameShown != 0);
    // RPCS3: 12 frames from the main menu's "close" to the game menu drawn.
    C15_CHECK(gameShown - pressMain >= 11 && gameShown - pressMain <= 13);
    // The game menu's opening animation: label 3 (onMenu_OpeningAnimEnd) 58 frames after its open labels.
    {
        uint32_t open = 0, end = 0;
        for (const Received& r : g_received) {
            if (r.movie == 2 && r.label == "onMenu_Video#1_Open" && open == 0) open = r.frame;
            if (r.movie == 2 && r.label == "onMenu_OpeningAnimEnd" && end == 0) end = r.frame;
        }
        std::printf("menus: game menu open labels at %u, opening animation end at %u (%d frames; RPCS3 58)\n", open, end,
                    static_cast<int>(end - open));
        C15_CHECK(open != 0 && end - open == 58);
    }
    Run(90);
    Shot("c16_game_menu.png");
    PrintButtons(6);
    // A new game's progress (CKS08GameStructure_ResetProgress 0x50f2c8, all unlock bytes 0): item 0 (start
    // story mode) enabled and focused, item 1 (chapter, +0x23f) disabled (navigation passes over it), as RPCS3 shows them.
    C15_CHECK(Focus(6) == 0);
    {
        auto* chapter = static_cast<CKInterfaceButtonBase*>(MenuObject(6)->m_apButtons.m_pBlock[1]);
        auto* start = static_cast<CKInterfaceButtonBase*>(MenuObject(6)->m_apButtons.m_pBlock[0]);
        C15_CHECK((chapter->m_baFlags & CKInterfaceButtonBase::kFlagDisabled) != 0);
        C15_CHECK((start->m_baFlags & CKInterfaceButtonBase::kFlagDisabled) == 0);
    }

    // Down to item 3 (options), Cross: 0 -> 2 -> 3 (item 1 skipped); stepped until the focus is there.
    bool gameSparkles = false;
    int burstFrame = -1;
    for (int i = 0; i < 6 && Focus(6) != 3; ++i) {
        Press(CELL_PAD_CTRL_DOWN, 0, 2);
        for (int k = 0; k < 14; ++k) {
            Step();
            if (!gameSparkles && burstFrame < 0 && Focus(6) != 0 && CountParticles(false).live > 0) burstFrame = k;
            if (!gameSparkles && burstFrame >= 0 && k == burstFrame + 4) {
                // The newly focused item's burst (started with its state transition, a few frames after the
                // focus moved), 4 frames in.
                gameSparkles = true;
                Shot("c16_game_menu_sparkles.png");
                const ParticleCensus census = CountParticles();
                C15_CHECK(census.active > 0 && census.live > 0 && census.ptank > 0);
            }
        }
    }
    PrintButtons(6);
    C15_CHECK(Focus(6) == 3);
    C15_CHECK(gameSparkles);
    Press(0, CELL_PAD_CTRL_CROSS);
    const uint32_t optionsShown = WaitMenuReady(0x19, 600);
    C15_CHECK(optionsShown != 0);
    Run(90);
    Shot("c16_options.png");
    // The game menu's item 3 asks for the options directly (CKS08MenuGame_OnItemEvent): no closing animation,
    // as in the RPCS3 capture (movie #2 sends no onMenu_ClosingAnimEnd before #28 opens).
    for (const Received& r : g_received)
        if (r.movie == 2 && r.label == "onMenu_ClosingAnimEnd" && r.frame > gameShown && r.frame < optionsShown)
            C15_CHECK(!"game menu closing animation before the options");
    PrintButtons(0x19);

    // The language: options item 0 is a CKInterfaceButtonDouble in mode 1 (CycleLanguageOption 0x17400 on the
    // game manager's edited options, +0xec). Right once: the language index steps (wrapping over the
    // CLocManager's languages).
    CDefaultGameManager* gm = Manager();
    const uint32_t languageBefore = gm->m_editedOptions.m_ui32Language;
    C15_CHECK(Focus(0x19) == 0);
    Press(CELL_PAD_CTRL_RIGHT, 0, 2);
    Run(20);
    const uint32_t languageAfter = gm->m_editedOptions.m_ui32Language;
    if (g_shots) {  // the reload done: the texts and the flag (the LLC TextureBank image) in the new language
        Run(400);
        Shot("c16_options_after_language.png");
    }
    std::printf("menus: options language %u -> %u\n", languageBefore, languageAfter);
    C15_CHECK(languageAfter != languageBefore);
    PrintButtons(0x19);

    // Up twice (0 -> 10 -> 9), Cross: the sound options (item 9's state-4 transition 0x1c); Circle back.
    Press(CELL_PAD_CTRL_UP, 0, 2);
    Run(14);
    Press(CELL_PAD_CTRL_UP, 0, 2);
    Run(14);
    C15_CHECK(Focus(0x19) == 9);
    Press(0, CELL_PAD_CTRL_CROSS);
    const uint32_t soundShown = WaitMenuReady(0x1c, 600);
    C15_CHECK(soundShown != 0);
    Run(90);
    Shot("c16_options_sound.png");
    PrintButtons(0x1c);
    Press(0, CELL_PAD_CTRL_CIRCLE);
    C15_CHECK(WaitMenuReady(0x19, 600) != 0);

    // Up twice and right (9 -> 13), Cross: the video options (0xe); Circle back.
    Press(CELL_PAD_CTRL_UP, 0, 2);
    Run(14);
    Press(CELL_PAD_CTRL_UP, 0, 2);
    Run(14);
    Press(CELL_PAD_CTRL_RIGHT, 0, 2);
    Run(14);
    C15_CHECK(Focus(0x19) == 13);
    Press(0, CELL_PAD_CTRL_CROSS);
    const uint32_t videoShown = WaitMenuReady(0x0e, 600);
    C15_CHECK(videoShown != 0);
    Run(90);
    Shot("c16_options_video.png");
    PrintButtons(0x0e);
    Press(0, CELL_PAD_CTRL_CIRCLE);
    C15_CHECK(WaitMenuReady(0x19, 600) != 0);

    // Circle: back to the game menu (the options' back item 15).
    const uint32_t pressBack = g_frame + 1;
    Press(0, CELL_PAD_CTRL_CIRCLE);
    const uint32_t gameAgain = WaitMenuReady(6, 600);
    std::printf("menus: options back at %u, game menu shown at %u (%d frames)\n", pressBack, gameAgain,
                static_cast<int>(gameAgain - pressBack));
    C15_CHECK(gameAgain != 0);
    // RPCS3: options "close" 7025 -> game menu drawn 7042 (17 frames).
    C15_CHECK(gameAgain - pressBack >= 16 && gameAgain - pressBack <= 18);
    // The order of the screens: main, game, options, game.
    {
        std::vector<int> order;
        for (const Change& c : g_changes)
            if (c.menu != 0x24 && (order.empty() || order.back() != c.menu)) order.push_back(c.menu);
        const std::vector<int> expected = {0x04, 0x11, 0x09, 0x06, 0x19, 0x1c, 0x19, 0x0e, 0x19, 0x06};
        C15_CHECK(order == expected);
    }

    std::printf("menus: menus shown:");
    for (const Change& c : g_changes) std::printf(" %u:0x%02x", c.frame, c.menu);
    std::printf("\n");

    dotd::platform::SetPadSource(nullptr);
    c15::Shutdown();
    if (c15::g_failures == 0) std::printf("menus: all tests passed\n");
    return c15::g_failures == 0 ? 0 : 1;
}
