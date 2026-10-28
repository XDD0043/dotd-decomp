// flash_exit_test - the C1.5 exit harness: the press-start and main-menu movies played as the menus show
// them, frame by frame at 1/60 s, with the labels their timelines send.
//
// The menu logic is C1.6; this test calls the Flash entry points the menus use:
//   - KBase730C_Open 0x514a00 (the menu's vt+0x50, from the game manager's menu switch):
//       CKFlashUI_StartInterface(m_pFlashUI, 1) - here StartInterface on #3 (press start, CKS08MenuPressStart)
//       and later on #0 (CKS08MenuMain);
//   - KBase730C_Close 0x513f88 (the menu's vt+0x5c when the game manager switches to the next menu after
//       start is pressed, CKS08MenuPressStart_OnMenuState 0x5613b8 state 0): CKFlashUI_StopInterface(#3, 1),
//       which sends the movie's restart button and hides it. (The press-start menu has no message out and
//       the movie no input label, so its closing keyframes are never reached, as on the PS3.)
//   - "Flash Manager" input bound first (CKFlashManager_SetInputConfig(1), IKGameManager_ResetRuntimeImpl).
// Every frame (c15::RunFrame: GameLoop -> RenderGameFrame stand-in -> CManager2d_PreUpdate ->
// CKFlashManager_Update -> CKFlashUI_Update) the shown movies advance; the maestros' handler is wrapped to
// log every message before CKFlashManager::HandleMaestroEvent (0x6d180) gets it.
//
// The table: frame, movie, node 0 time and keyframe index, and the getURL labels received. The check: the
// labels each movie sends come in the order its root timeline defines them (the cels' message lists, by
// keyframe index), and the expected press-start and main-menu labels arrive.
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "Renderware/rt2d/Rt2d.h"
#include "Renderware/rt2d/Rt2dDebugDump.h"
#include "Renderware/rt2danim/Rt2dAnim.h"
#include "Renderware/rt2danim/Rt2dAnimPrivate.h"
#include "Renderware/rwcore/RwSList.h"
#include "boot_helper.h"
#include "k2000/graphical/ui/CKFlashManager.h"
#include "k2000/graphical/ui/CKFlashUI.h"
#include "k2000/logic/CKSector.h"
#include "k2000/misc/Engine.h"

namespace {

struct Received {
    uint32_t frame;
    int32_t movie;
    std::string label;
    int32_t keyframe;  // node 0's keyframe index when the message arrived
};

std::vector<Received> g_received;
uint32_t g_frame = 0;

int32_t MovieOf(Rt2dMaestro* maestro) {
    CKFlashManager* manager = g_pEngine->m_flashManager;
    for (uint32_t i = 0; i < manager->m_ui32NbFlashUI; ++i)
        if (manager->GetInterfaceByIndex(i)->m_pMaestro == maestro) return static_cast<int32_t>(i);
    return -1;
}

Rt2dAnimNode* Node0(Rt2dMaestro* maestro) {
    if (maestro == nullptr || maestro->animations == nullptr || _rwSListGetNumEntries(maestro->animations) == 0)
        return nullptr;
    return _rt2dMaestroGetAnimNodeByIndex(maestro, 0);
}

std::string LabelName(Rt2dMaestro* maestro, RwInt32 index) {
    Rt2dStringLabel* label = Rt2dMaestroGetStringLabelByIndex(maestro, index);
    if (label == nullptr) return "?";
    const RwChar* name = Rt2dMaestroGetStringLabelName(maestro, label);
    return name != nullptr ? name : "?";
}

// The logging wrapper around the engine's handler (installed on every maestro).
bool g_logAll = false;

Rt2dMessage* LoggingHandler(Rt2dMaestro* maestro, Rt2dMessage* message) {
    if (g_logAll)
        std::printf("flash_exit: frame %u #%d message type %u index %d params %d %d\n", g_frame, MovieOf(maestro),
                    message->messageType, message->index, message->intParam1, message->intParam2);
    if (message->messageType == rt2dMESSAGETYPEGETURL) {
        Rt2dAnimNode* node = Node0(maestro);
        g_received.push_back(Received{g_frame, MovieOf(maestro), LabelName(maestro, message->intParam1),
                                      node != nullptr ? Rt2dAnimGetPrevFrameIndex(&node->anim) : -1});
    }
    return CKFlashManager::HandleMaestroEvent(maestro, message);
}

// The getURL labels node 0's timeline sends, in keyframe order (each cel's message list).
std::vector<std::pair<int32_t, std::string>> DefinedLabels(Rt2dMaestro* maestro) {
    std::vector<std::pair<int32_t, std::string>> labels;
    Rt2dAnimNode* node = Node0(maestro);
    if (node == nullptr || node->celList == nullptr || node->celList->cel == nullptr) return labels;
    const RwInt32 cels = _rwSListGetNumEntries(node->celList->cel);
    for (RwInt32 c = 0; c < cels; ++c) {
        const Rt2dCel* cel = RwSListEntry<Rt2dCel>(node->celList->cel, c);
        if (cel->messageListIndex < 0) continue;
        RwInt32 m = RwSListArray<RwInt32>(maestro->messageList)[cel->messageListIndex];
        for (;; ++m) {
            const Rt2dMessage* message = RwSListEntry<Rt2dMessage>(maestro->messageStore, m);
            if (message->messageType == rt2dMESSAGETYPENULL) break;
            if (message->messageType == rt2dMESSAGETYPEGETURL) labels.emplace_back(c, LabelName(maestro, message->intParam1));
        }
    }
    return labels;
}

void PrintFrame(const std::vector<int32_t>& movies) {
    CKFlashManager* manager = g_pEngine->m_flashManager;
    std::printf("%5u", g_frame);
    for (int32_t movie : movies) {
        CKFlashUI* ui = manager->GetInterfaceByIndex(static_cast<uint32_t>(movie));
        Rt2dAnimNode* node = Node0(ui->m_pMaestro);
        if (node == nullptr) continue;
        std::printf("  #%d t=%8.4f kf=%3d", movie, static_cast<double>(Rt2dAnimGetCurrentTime(&node->anim)),
                    Rt2dAnimGetPrevFrameIndex(&node->anim));
    }
    for (const Received& r : g_received)
        if (r.frame == g_frame) std::printf("  <#%d %s>", r.movie, r.label.c_str());
    std::printf("\n");
}

void Step(const std::vector<int32_t>& movies, uint32_t frames, bool printAll) {
    for (uint32_t i = 0; i < frames; ++i) {
        ++g_frame;
        const size_t before = g_received.size();
        c15::RunFrame();
        if (printAll || g_received.size() != before || (g_frame % 30) == 0) PrintFrame(movies);
    }
}

bool InDefinedOrder(int32_t movie, Rt2dMaestro* maestro) {
    const auto defined = DefinedLabels(maestro);
    int32_t lastKeyframe = -1;
    bool ok = true;
    for (const Received& r : g_received) {
        if (r.movie != movie) continue;
        int32_t keyframe = -1;
        for (const auto& d : defined)
            if (d.second == r.label) keyframe = d.first;
        if (keyframe < 0) continue;  // a clip's label, not the root timeline's
        if (keyframe < lastKeyframe) {
            std::printf("flash_exit: #%d %s (keyframe %d) after keyframe %d\n", movie, r.label.c_str(), keyframe, lastKeyframe);
            ok = false;
        }
        lastKeyframe = keyframe;
    }
    return ok;
}

// The frame a label first arrived from a movie, or 0.
uint32_t FrameOf(int32_t movie, const char* label) {
    for (const ::Received& r : g_received)
        if (r.movie == movie && r.label == label) return r.frame;
    return 0;
}

float Node0Time(CKFlashUI* ui) {
    Rt2dAnimNode* node = Node0(ui->m_pMaestro);
    return node != nullptr ? Rt2dAnimGetCurrentTime(&node->anim) : -1.0f;
}

int32_t Node0Keyframe(CKFlashUI* ui) {
    Rt2dAnimNode* node = Node0(ui->m_pMaestro);
    return node != nullptr ? Rt2dAnimGetPrevFrameIndex(&node->anim) : -2;
}

}  // namespace

int main() {
    std::setvbuf(stdout, nullptr, _IONBF, 0);
    if (!c15::BootToFrontEnd()) {
        std::printf("flash_exit: no game data configured; skipped\n");
        return 77;
    }
    c15::ParkFrontEndSequence();  // this harness drives the movies / videos itself
    CKFlashManager* manager = g_pEngine->m_flashManager;
    C15_CHECK(manager != nullptr && manager->m_ui32NbFlashUI == 29);
    if (manager == nullptr || manager->m_ui32NbFlashUI < 29) {
        c15::Shutdown();
        return 1;
    }
    for (uint32_t i = 0; i < manager->m_ui32NbFlashUI; ++i) {
        CKFlashUI* ui = manager->GetInterfaceByIndex(i);
        if (ui->m_pMaestro != nullptr) Rt2dMaestroSetMessageHandler(ui->m_pMaestro, LoggingHandler);
    }
    CKFlashUI* pressStart = manager->GetInterfaceByIndex(3);
    CKFlashUI* mainMenu = manager->GetInterfaceByIndex(0);
    // CKLevel_PostLoad made the level's sector active (the interfaces run only then).
    C15_CHECK(pressStart->m_pSector != nullptr && (pressStart->m_pSector->m_ba16Properties & 1) != 0);

    // The labels each movie's root timeline defines.
    for (int32_t movie : {3, 0}) {
        std::printf("flash_exit: #%d root timeline labels:", movie);
        for (const auto& d : DefinedLabels(manager->GetInterfaceByIndex(static_cast<uint32_t>(movie))->m_pMaestro))
            std::printf(" [kf %d] %s", d.first, d.second.c_str());
        std::printf("\n");
    }

    // IKGameManager_ResetRuntimeImpl (0x4f12cc, C1.6) binds the "Flash Manager" input: SetInputConfig(1).
    manager->SetInputConfig(1);
    C15_CHECK(manager->GetInputDico() != nullptr);

    // Press start: the menu opens (KBase730C_Open -> StartInterface(#3, 1)).
    std::printf("flash_exit: frame %u: StartInterface #3 (press start)\n", g_frame);
    pressStart->StartInterface(1);
    C15_CHECK((pressStart->m_baFlags & CKFlashUI::kStateMask) == 2);
    Step({3}, 240, false);

    // Press start opened at frame 1 (its two labels), then its timeline stops at keyframe 3 (t = 0.12),
    // waiting on the screen.
    C15_CHECK(Node0Time(pressStart) == 0x1.eb851ep-4f && Node0Keyframe(pressStart) == 3);  // 0.12
    // RPCS3 idling on press start (work/flash_labels_live.py, 2026-10-18 01:42, 7196 frames): node 0 at
    // keyframe 3, time bits 3df5c28f, node 1 at keyframe 0; the queue's last batch (entries 0 and 1 of its
    // array, top = bot = 0) was STOP (index 0) then GETURL (index 0, intParam1 3), and nothing after.
    {
        const Rt2dMessageQueue* queue = pressStart->m_pMaestro->messageQueue;
        C15_CHECK(queue->messageTop == 0 && queue->messageBot == 0);
        C15_CHECK(queue->messageQueue[0].messageType == rt2dMESSAGETYPESTOP && queue->messageQueue[0].index == 0);
        C15_CHECK(queue->messageQueue[1].messageType == rt2dMESSAGETYPEGETURL && queue->messageQueue[1].index == 0 &&
                  queue->messageQueue[1].intParam1 == 3);
    }

    // Start pressed: CKS08MenuPressStart_OnMenuState (state 0) plays the start sound and lets the game
    // manager switch menus; the switch closes the menu (KBase730C_Close 0x513f88: StopInterface(#3, 1),
    // which sends the movie's restart button (+0xe8) and hides it) and opens the main menu
    // (KBase730C_Open: StartInterface(#0, 1)).
    std::printf("flash_exit: frame %u: StopInterface #3 (KBase730C_Close), StartInterface #0 (main menu)\n", g_frame);
    g_logAll = true;
    pressStart->StopInterface(1);
    g_logAll = false;
    C15_CHECK((pressStart->m_baFlags & CKFlashUI::kStateMask) == 0);
    mainMenu->StartInterface(1);
    C15_CHECK((mainMenu->m_baFlags & CKFlashUI::kStateMask) == 2);
    const uint32_t mainOpened = g_frame;
    Step({0, 3}, 360, false);
    // The restart button (+0xe8, label 4) sent #3 back to keyframe 0 (goto frame 0, play) before hiding it.
    C15_CHECK(Node0Keyframe(pressStart) == 0 && Rt2dObjectIsVisible(Rt2dMaestroGetScene(pressStart->m_pMaestro)) == 0);
    // The main menu: the opening animation ends at keyframe 51 (t = 1.02), on the 62nd frame after the open, and
    // stops there; RPCS3 at the main menu holds the same node 0 state (keyframe 51, time bits 3f828f59:
    // the sum of the frame steps, not 1.02f), work/flash_labels_live.py 2026-10-18.
    float mainTime = Node0Time(mainMenu);
    uint32_t mainBits = 0;
    std::memcpy(&mainBits, &mainTime, 4);
    std::printf("flash_exit: #0 node 0 at the end: keyframe %d time %08x (RPCS3: 51, 3f828f59)\n", Node0Keyframe(mainMenu), mainBits);
    C15_CHECK(Node0Keyframe(mainMenu) == 51 && mainBits == 0x3f828f59u);
    // RPCS3 from press start to the main menu (work/flash_labels_live.py, 2026-10-18 01:49): #3 hidden and #0's
    // first update on game frame 2597 with GETURL labels 0 and 1, then GETURL label 4 + STOP on frame 2658
    // (keyframe 51, time 3f828f59): 61 frames, as here (the frame after the open, then 61 more).
    C15_CHECK(FrameOf(0, "onMenu_OpeningAnimEnd") == FrameOf(0, "onMenu_Video#1_Open") + 61);
    C15_CHECK(FrameOf(0, "onMenu_Video#1_Open") == mainOpened + 1);
    C15_CHECK(FrameOf(0, "onSnd_OpenMenu") == mainOpened + 1);
    C15_CHECK(FrameOf(0, "onMenu_OpeningAnimEnd") == mainOpened + 62);
    C15_CHECK(FrameOf(3, "onPressStart_Open") == 1 && FrameOf(3, "onMenu_OpeningAnimEnd") == 1);
    // The press-start movie's close labels (keyframes 4 and 20) never fire: the menu is closed by
    // StopInterface (restart + hide), as on the PS3 (CKFlashUI_PostMessage 0x6dce0 never runs before the
    // main menu in the 2026-10-18 boot timeline).
    C15_CHECK(FrameOf(3, "onPressStart_Close") == 0);

    std::printf("flash_exit: %zu getURL messages\n", g_received.size());
    for (const ::Received& r : g_received) std::printf("  frame %4u  #%d  kf %3d  %s\n", r.frame, r.movie, r.keyframe, r.label.c_str());
    C15_CHECK(InDefinedOrder(3, pressStart->m_pMaestro));
    C15_CHECK(InDefinedOrder(0, mainMenu->m_pMaestro));

    // DOTD_DUMP_MAESTRO=path: every movie's state at the end (the main menu, idle), for
    // work/maestro_diff.py against a live dump of RPCS3 at the main menu.
    if (const char* dumpPath = std::getenv("DOTD_DUMP_MAESTRO")) {
        CKFlashManager* manager = g_pEngine->m_flashManager;
        std::vector<Rt2dDebugDumpUI> uis;
        for (uint32_t i = 0; i < manager->m_ui32NbFlashUI; ++i) {
            CKFlashUI* ui = static_cast<CKFlashUI*>(manager->m_apFlashUI[i]);
            Rt2dDebugDumpUI entry = {static_cast<int32_t>(i), ui->m_baFlags, false, false, ui->m_pMaestro};
            entry.sceneVisible = Rt2dDebugDumpSceneVisible(ui->m_pMaestro);
            const bool active = ui->m_pSector != nullptr &&
                                (ui->m_pSector->m_ba16Properties & 1) != 0;
            entry.drawn = active && entry.sceneVisible && (ui->m_baFlags & 0x20) == 0;
            uis.push_back(entry);
        }
        C15_CHECK(Rt2dDebugDumpWrite(dumpPath, "flash_exit_main_menu", c15::FrameCount(), uis.data(),
                                     static_cast<int32_t>(uis.size())));
        std::printf("flash_exit: maestros dumped to %s\n", dumpPath);
    }
    c15::Shutdown();
    if (c15::g_failures == 0) std::printf("flash_exit: all tests passed\n");
    return c15::g_failures == 0 ? 0 : 1;
}
