// CKS08GameManager_6.cpp - reconstructed original translation unit 0x5043a8-0x506400 (GAME_TOC1, main_toc1), 9 functions, 6 live.
// Primary class: CKS08GameManager  key 0x784c  category Logic  size 0xf2c  vtable 0xb2af78
// Other owners: CKS08ObjectiveList (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5043a8  CKS08GameManager_StateInGame_maybe
//   [x] 0x5044e0  CKS08GameManager_State4_maybe
//   [x] 0x504750  CKS08GameManager_State5_maybe
//   [x] 0x504990  CKS08GameManager_StateMenuPause
//   [x] 0x504c88  CKS08GameManager_StateHeroDeath_maybe
//   [ ] 0x506348  CKS08ObjectiveList_Delete
//   [ ] 0x506398  KStub_Nop_506398  [dead]
//   [ ] 0x5063a0  FUN_005063a0  [dead]
//   [ ] 0x5063f8  KStub_Nop_5063f8  [dead]
#include "Spyro2008/logic/CKS08GameManager.h"

#include "Spyro2008/logic/CKMenuBase114c.h"
#include "k2000/core/Stub.h"
#include "k2000/graphical/system/IKVideo.h"
#include "k2000/graphical/system/CKVideoSegment.h"
#include "k2000/graphical/system/CVideoManager.h"
#include "k2000/graphical/system/PS3_CKVideo.h"
#include "k2000/input/CKInputDico.h"
#include "k2000/managers/CKInput.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"
#include "k2000/ui/IKNode2d.h"

// 0x005043a8 CKS08GameManager_StateInGame_maybe: game state 7 stays. While the clock runs: the common state;
// on its tick (phase 0) the interface asks for menu 0x10 when flags +0xafc bit 7 is set (one request on the
// stack, depth 1), else no menu (0x24); on enter (phase 1) bits 2-4 of +0xafc are cleared and bit 4 set.
uint8_t CKS08GameManager::StateInGame(int32_t phase, uint8_t other) {
    if (g_pEngine->m_timeManager->m_pTime->m_eCurrentState == IKTime::RUNNING) {
        const uint8_t state = StateInGameCommon(phase, other);
        if (state != 7) return state;
        if (phase == 0) {
            m_aMenuStack[0] = (m_unkAFC & 0x80) != 0 ? 0x10 : 0x24;
            m_ui32MenuStackDepth = 1;
            return 7;
        }
        if (phase == 1) {
            m_unkAFC = (m_unkAFC & 0xffffffe3u) | 0x10;
            return 7;
        }
    }
    return 7;
}

// 0x005044e0 CKS08GameManager_State4_maybe: the copyrights screen (menu 4). Enter: the interface video
// stopped if it plays; with the menu: flag bit 0 cleared, menu 4; without: flag bit 0 set. Update: once the
// flag is set (the menu's end) or without the menu, no menu and state 0.
uint8_t CKS08GameManager::State4(int32_t phase, uint8_t other) {
    const uint8_t state = StateReturn4(phase, other);
    if (state != 4) return state;
    if (phase == 0) {
        if (Vf344()[4] != nullptr && (m_unkAFC & 1) == 0) return 4;
        m_aMenuStack[0] = 0x24;
        m_ui32MenuStackDepth = 1;
        return 0;
    }
    if (phase != 1) return 4;
    if (GetInterfaceVideo() != nullptr && (GetInterfaceVideo()->m_baData & 1) != 0) GetInterfaceVideo()->Stop();
    if (Vf344()[4] != nullptr) {
        m_unkAFC &= ~1u;
        m_aMenuStack[0] = 4;
        m_ui32MenuStackDepth = 1;
        return 4;
    }
    m_unkAFC = (m_unkAFC & ~1u) | 1;
    return 4;
}

// 0x00504750 CKS08GameManager_State5_maybe: the press-start screen (menu 0x11), as State4. The update leaves
// once the flag is set (KStub_Return1_4ec918: always).
uint8_t CKS08GameManager::State5(int32_t phase, uint8_t other) {
    const uint8_t state = State5Common(phase, other);
    if (state != 5) return state;
    if (phase == 0) {
        if ((m_unkAFC & 1) != 0) return 0;  // and 0x4ec918 KStub_Return1_4ec918 returned 1
        return 5;
    }
    if (phase != 1) return 5;
    if (GetInterfaceVideo() != nullptr && (GetInterfaceVideo()->m_baData & 1) != 0) GetInterfaceVideo()->Stop();
    if (Vf344()[0x11] != nullptr) {
        m_unkAFC &= ~1u;
        m_aMenuStack[0] = 0x11;
        m_ui32MenuStackDepth = 1;
        return 5;
    }
    m_unkAFC = (m_unkAFC & ~1u) | 1;
    return 5;
}

// 0x00504990 CKS08GameManager_StateMenuPause. STUB(C1.6): the pause menu.
// PORT (stand-in until the pause menu, C2.8): the menu is not drawn, so START pressed again (the pause button, input
// entry 0, just pressed) goes back to the game state 7 instead of leaving the game paused for good.
uint8_t CKS08GameManager::StateMenuPause(int32_t phase, uint8_t other) {
    DOTD_STUB_ONCE("CKS08GameManager_StateMenuPause (C1.6): START resumes (stand-in)");
    if (phase == 0 && m_pCommonInputDicos != nullptr && m_pCommonInputDicos->GetButtonState(0) == 0xff) return 7;
    return StateMenuCommon(phase, other);
}

// 0x00504c88 CKS08GameManager_StateHeroDeath_maybe. STUB(C1.6): hero death.
uint8_t CKS08GameManager::StateHeroDeath(int32_t phase, uint8_t other) {
    DOTD_STUB_ONCE("CKS08GameManager_StateHeroDeath_maybe (C1.6)");
    return StateHeroDeathCommon(phase, other);
}
