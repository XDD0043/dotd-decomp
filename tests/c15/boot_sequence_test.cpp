// boot_sequence_test - checkpoint C1.4, family sequence: the front-end sequence the game manager runs,
// headless, one game frame at a time (1/60 s of the fake clock), with no input until the press-start
// screen, then START through the pad shim (platform/cell/pad: a pad source, as a real pad reports it).
//
// Logged: every change of the game state (CKS08GameManager +0x2f5), the menu shown (+0x30d) and the game
// loop's mode, with the frame number; at the end the frame counts are compared with the 2026-10-18 RPCS3
// timeline (outputs/remake/timeline/timeline-boot_to_menu-20261018-002952.json, 60 fps):
//   gm1 (auto-load) mode 5 -> 7 -> 2 -> 8 -> 5, gm4 (copyrights) at timeline frame 16, gm3 (logos) at frame
//   316 (300 frames of copyrights: 4.0 s + the fade-out), gm5 (press start), gm6 (main menu) 59 frames after
//   the START press (the press at frame 2031, the main menu at 2090).
// The logos run their videos to the end (nothing skipped): 4.0 + 14.0 + 5.0 s of Bink at 25 fps.
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include "Spyro2008/logic/CKS08GameManager.h"
#include "boot_helper.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/CoreSingletons.h"
#include "k2000/misc/Engine.h"
#include "platform/cell/pad.h"

namespace {

bool g_startHeld = false;

// One pad on port 0 (connected), START from g_startHeld; the sticks centred.
bool TestPad(int port, uint16_t words[24]) {
    if (port != 0) return false;
    std::memset(words, 0, 24 * sizeof(uint16_t));
    words[CELL_PAD_BTN_OFFSET_DIGITAL1] = g_startHeld ? CELL_PAD_CTRL_START : 0;
    for (int i = CELL_PAD_BTN_OFFSET_ANALOG_RIGHT_X; i <= CELL_PAD_BTN_OFFSET_ANALOG_LEFT_Y; ++i) words[i] = 0x80;
    return true;
}

struct Change {
    uint32_t frame;
    int gameState;
    int menu;
    int mode;
};

}  // namespace

int main() {
    std::setvbuf(stdout, nullptr, _IONBF, 0);
    dotd::platform::SetPadSource(&TestPad);
    if (!c15::BootToFrontEnd()) {
        std::printf("boot_sequence: no game data configured; skipped\n");
        return 77;
    }
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    CKGameLoop* loop = g_pCKGameLoop;
    std::vector<Change> changes;
    auto record = [&](uint32_t frame) {
        const Change now{frame, manager->m_gameState.m_ui8Current, manager->m_interfaceState.m_ui8Current, loop->m_mode};
        if (changes.empty() || changes.back().gameState != now.gameState || changes.back().menu != now.menu ||
            changes.back().mode != now.mode) {
            changes.push_back(now);
            std::printf("boot_sequence: frame %5u  game state %3d  menu 0x%02x  loop mode %d\n", frame, now.gameState,
                        now.menu, now.mode);
        }
    };
    auto firstFrame = [&](int gameState) -> int64_t {
        for (const Change& c : changes)
            if (c.gameState == gameState) return c.frame;
        return -1;
    };
    record(0);

    // Up to press start (state 5) with no input; cap 3000 frames (50 s).
    uint32_t frame = 0;
    while (frame < 3000 && manager->m_gameState.m_ui8Current != 5) {
        c15::RunFrame();
        record(++frame);
    }
    C15_CHECK(manager->m_gameState.m_ui8Current == 5);
    // The press-start screen idles for a second, then START is pressed for 6 frames.
    for (uint32_t i = 0; i < 60; ++i) {
        c15::RunFrame();
        record(++frame);
    }
    const uint32_t pressFrame = frame + 1;
    g_startHeld = true;
    for (uint32_t i = 0; i < 6; ++i) {
        c15::RunFrame();
        record(++frame);
    }
    g_startHeld = false;
    while (frame < pressFrame + 600 && manager->m_gameState.m_ui8Current != 6) {
        c15::RunFrame();
        record(++frame);
    }
    for (uint32_t i = 0; i < 90; ++i) {
        c15::RunFrame();
        record(++frame);
    }

    const int64_t copyrights = firstFrame(4), logos = firstFrame(3), pressStart = firstFrame(5), mainMenu = firstFrame(6);
    std::printf("boot_sequence: copyrights at frame %lld, logos at %lld (%lld frames of copyrights; RPCS3: 300), press "
                "start at %lld (%lld frames of logos), main menu at %lld (%lld frames after START; RPCS3: 59)\n",
                static_cast<long long>(copyrights), static_cast<long long>(logos), static_cast<long long>(logos - copyrights),
                static_cast<long long>(pressStart), static_cast<long long>(pressStart - logos),
                static_cast<long long>(mainMenu), static_cast<long long>(mainMenu - static_cast<int64_t>(pressFrame)));
    // The order of the original: 1 (auto-load), 0, 4, 0, 3, 0, 5, 0, 6.
    std::vector<int> order;
    for (const Change& c : changes)
        if (order.empty() || order.back() != c.gameState) order.push_back(c.gameState);
    std::printf("boot_sequence: game states:");
    for (int s : order) std::printf(" %d", s);
    std::printf("\n");
    C15_CHECK(copyrights > 0 && logos > copyrights && pressStart > logos && mainMenu > pressStart);
    // The menus each state shows: 4 copyrights (menu 4), 5 press start (0x11), 6 main menu (9).
    bool copyrightsMenu = false, pressStartMenu = false, mainMenuShown = false;
    for (const Change& c : changes) {
        if (c.gameState == 4 && c.menu == 4) copyrightsMenu = true;
        if (c.gameState == 5 && c.menu == 0x11) pressStartMenu = true;
        if (c.gameState == 6 && c.menu == 9) mainMenuShown = true;
    }
    C15_CHECK(copyrightsMenu && pressStartMenu && mainMenuShown);
    // The auto-load went through the game loop's modes 7, 8 and 2 before the copyrights.
    bool sawLoading = false, sawResume = false;
    for (const Change& c : changes) {
        if (c.frame > static_cast<uint32_t>(copyrights)) break;
        if (c.mode == CKGameLoop::kModeLoading) sawLoading = true;
        if (c.mode == CKGameLoop::kModeResume) sawResume = true;
    }
    C15_CHECK(sawLoading && sawResume);
    // Timing against RPCS3 (60 fps): the copyrights last 300 frames there (4.0 s timer + the fade); the
    // main menu follows START by 59 frames (the fade-out). A few frames of slack: the fade's end is the
    // first frame at alpha >= 0xf6.
    C15_CHECK(logos - copyrights >= 290 && logos - copyrights <= 310);
    C15_CHECK(mainMenu - static_cast<int64_t>(pressFrame) >= 50 && mainMenu - static_cast<int64_t>(pressFrame) <= 70);
    C15_CHECK(manager->m_gameState.m_ui8Current == 6 && manager->m_interfaceState.m_ui8Current == 9);

    dotd::platform::SetPadSource(nullptr);
    c15::Shutdown();
    if (c15::g_failures == 0) std::printf("boot_sequence: all tests passed\n");
    return c15::g_failures == 0 ? 0 : 1;
}
