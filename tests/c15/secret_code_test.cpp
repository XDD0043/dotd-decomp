// secret_code_test - the "Menu Game" secret code (CKS08MenuGame_UpdateSecretCodeInput_maybe 0x554de8). The original
// never calls it; dotd runs it in the menu's update phase (outputs/hidden-debug-features.md section 3). Headless, one
// game frame at a time, driven through the pad shim:
//  1. boot, START at press start, the main menu (menu 9), then Cross until "Menu Game" (menu 6) is open;
//  2. a wrong code (hold L1, left stick left, then up) changes nothing;
//  3. hold L1, left stick left, right, right, up, up (each held 3 frames, 0.4 s apart): the twelve unlock bytes of the
//     game structure (+0x23f..+0x24a) are set and items 0 and 1 are enabled.
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "Spyro2008/logic/CKS08GameManager.h"
#include "Spyro2008/logic/CKS08GameStructure.h"
#include "Spyro2008/logic/ui/CKS08MenuGame.h"
#include "boot_helper.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/CKInterfaceButtonBase.h"
#include "k2000/misc/CoreSingletons.h"
#include "k2000/misc/Engine.h"
#include "platform/cell/pad.h"

namespace {

uint16_t g_digital1 = 0;  // start, select, L3, R3, d-pad
uint16_t g_digital2 = 0;  // L2, R2, L1, R1, triangle, circle, cross, square
uint16_t g_leftX = 0x80, g_leftY = 0x80;

bool TestPad(int port, uint16_t words[24]) {
    if (port != 0) return false;
    std::memset(words, 0, 24 * sizeof(uint16_t));
    words[CELL_PAD_BTN_OFFSET_DIGITAL1] = g_digital1;
    words[CELL_PAD_BTN_OFFSET_DIGITAL2] = g_digital2;
    words[CELL_PAD_BTN_OFFSET_ANALOG_RIGHT_X] = 0x80;
    words[CELL_PAD_BTN_OFFSET_ANALOG_RIGHT_Y] = 0x80;
    words[CELL_PAD_BTN_OFFSET_ANALOG_LEFT_X] = g_leftX;
    words[CELL_PAD_BTN_OFFSET_ANALOG_LEFT_Y] = g_leftY;
    return true;
}

CKS08GameManager* Manager() { return static_cast<CKS08GameManager*>(g_pEngine->m_gameManager); }
uint32_t g_frame = 0;
int g_lastMenu = -1, g_lastState = -1;

void Step() {
    c15::RunFrame();
    ++g_frame;
    CKS08GameManager* m = Manager();
    const int state = m->m_gameState.m_ui8Current, menu = m->m_interfaceState.m_ui8Current;
    if (state != g_lastState || menu != g_lastMenu) {
        std::printf("secret_code: frame %5u  loop mode %d  game state %3d  menu 0x%02x\n", g_frame,
                    g_pCKGameLoop->m_mode, state, menu);
        g_lastState = state;
        g_lastMenu = menu;
    }
}

void Steps(int n) {
    for (int i = 0; i < n; ++i) Step();
}

void PressDigital(uint16_t* word, uint16_t bit, int frames) {
    *word = static_cast<uint16_t>(*word | bit);
    Steps(frames);
    *word = static_cast<uint16_t>(*word & ~bit);
}

// The left stick pushed fully one way for 3 frames, then centred for 21 (0.4 s per step; the code waits 0.3 s).
void Stick(char dir) {
    if (dir == 'L') g_leftX = 0x00;
    if (dir == 'R') g_leftX = 0xff;
    if (dir == 'U') g_leftY = 0x00;
    if (dir == 'D') g_leftY = 0xff;
    Steps(3);
    g_leftX = g_leftY = 0x80;
    Steps(21);
}

uint8_t UnlockByte(int index) {
    CKS08GameStructure* s = static_cast<CKS08GameStructure*>(Manager()->m_gameStructure);
    return s->RtByte(static_cast<uint32_t>(0x23f + index));
}

int UnlockCount() {
    int n = 0;
    for (int i = 0; i < 12; ++i) n += UnlockByte(i) != 0;
    return n;
}

}  // namespace

int main() {
    std::setvbuf(stdout, nullptr, _IONBF, 0);
    dotd::platform::SetPadSource(&TestPad);
    if (!c15::BootToFrontEnd()) {
        std::printf("secret_code: no game data configured; skipped\n");
        return 77;
    }
    CKS08GameManager* manager = Manager();
    while (g_frame < 3000 && manager->m_gameState.m_ui8Current != 5) Step();
    C15_CHECK(manager->m_gameState.m_ui8Current == 5);
    Steps(60);
    PressDigital(&g_digital1, CELL_PAD_CTRL_START, 6);
    for (uint32_t end = g_frame + 600; g_frame < end && manager->m_interfaceState.m_ui8Current != 9;) Step();
    Steps(90);
    C15_CHECK(manager->m_interfaceState.m_ui8Current == 9);

    // Cross until "Menu Game" (6) opens; each Cross held 3 frames, then 90 frames to settle.
    for (int tries = 0; tries < 8 && manager->m_interfaceState.m_ui8Current != 6; ++tries) {
        PressDigital(&g_digital2, CELL_PAD_CTRL_CROSS, 3);
        for (int i = 0; i < 90 && manager->m_interfaceState.m_ui8Current != 6; ++i) Step();
    }
    Steps(90);
    std::printf("secret_code: menu 0x%02x, unlock bytes set before: %d of 12\n", manager->m_interfaceState.m_ui8Current,
                UnlockCount());
    C15_CHECK(manager->m_interfaceState.m_ui8Current == 6);
    const int before = UnlockCount();

    // 2. A wrong code.
    g_digital2 = CELL_PAD_CTRL_L1;
    Steps(10);
    Stick('L');
    Stick('U');
    Stick('U');
    Stick('U');
    Stick('U');
    g_digital2 = 0;
    Steps(30);
    std::printf("secret_code: after a wrong code: %d of 12\n", UnlockCount());
    C15_CHECK(UnlockCount() == before);

    // 3. The code.
    g_digital2 = CELL_PAD_CTRL_L1;
    Steps(10);
    for (const char* dir = "LRRUU"; *dir != 0; ++dir) Stick(*dir);
    g_digital2 = 0;
    Steps(30);
    std::printf("secret_code: after the code: %d of 12\n", UnlockCount());
    C15_CHECK(UnlockCount() == 12);
    C15_CHECK(manager->m_interfaceState.m_ui8Current == 6);

    // 4. (report only) Circle back, Cross into Menu Game again: the items' disabled flags and the bytes.
    PressDigital(&g_digital2, CELL_PAD_CTRL_CIRCLE, 3);
    Steps(120);
    std::printf("secret_code: after circle: menu 0x%02x\n", manager->m_interfaceState.m_ui8Current);
    for (int tries = 0; tries < 4 && manager->m_interfaceState.m_ui8Current != 6; ++tries) {
        PressDigital(&g_digital2, CELL_PAD_CTRL_CROSS, 3);
        for (int i = 0; i < 90 && manager->m_interfaceState.m_ui8Current != 6; ++i) Step();
    }
    Steps(90);
    if (manager->m_interfaceState.m_ui8Current == 6) {
        CKS08MenuGame* menu = static_cast<CKS08MenuGame*>(manager->Vf344()[6]);
        for (uint32_t i = 0; i < menu->m_apButtons.m_ui32NbUsedElt; ++i) {
            CKInterfaceButtonBase* b = static_cast<CKInterfaceButtonBase*>(menu->m_apButtons.m_pBlock[i]);
            std::printf("secret_code: re-entered Menu Game: item %u disabled %d\n", i,
                        (b->m_baFlags & CKInterfaceButtonBase::kFlagDisabled) != 0);
        }
    }
    std::printf("secret_code: re-entered: menu 0x%02x, %d of 12\n", manager->m_interfaceState.m_ui8Current, UnlockCount());

    dotd::platform::SetPadSource(nullptr);
    std::fflush(stdout);
    if (c15::g_failures == 0) std::printf("secret_code: all tests passed\n");
    std::_Exit(c15::g_failures == 0 ? 0 : 1);
}
