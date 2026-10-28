// IKCommonGameManager.cpp - reconstructed original translation unit 0x4f4708-0x4f5830 (GAME_TOC1, main_toc1), 11 functions, 11 live.
// Primary owner: IKCommonGameManager (not a registered class)
// Other owners: CKS08GameManager (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4f4708  IKCommonGameManager_State6_maybe
//   [x] 0x4f48d0  IKCommonGameManager_StateHeroDeath_maybe
//   [x] 0x4f48f0  KStub_Return10_4f48f0
//   [x] 0x4f48f8  KStub_Return11_4f48f8
//   [x] 0x4f4900  IKCommonGameManager_vf334
//   [x] 0x4f4928  IKCommonGameManager_State5_maybe
//   [x] 0x4f49a8  IKCommonGameManager_State2_maybe
//   [x] 0x4f4b08  IKCommonGameManager_State3_maybe
//   [x] 0x4f4de0  IKCommonGameManager_State1_maybe
//   [x] 0x4f4fa0  IKCommonGameManager_StateInGame_maybe
//   [x] 0x4f5128  CKS08GameManager_StateMenuCommon_maybe
#include "Spyro2008/logic/CKS08GameManager.h"

#include "Spyro2008/logic/CKMenuBase114c.h"
#include "k2000/core/Stub.h"
#include "k2000/graphical/system/IKVideo.h"
#include "k2000/graphical/system/CKVideoSegment.h"
#include "k2000/graphical/system/CVideoManager.h"
#include "k2000/graphical/system/PS3_CKVideo.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/input/CKInputDico.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/managers/CKInput.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/Engine.h"
#include "k2000/ui/IKNode2d.h"
#include "Spyro2008/logic/CKMenuBase114c.h"
#include "k2000/render/CRenderer.h"
#include "k2000/ui/IKNode2d.h"
#include "k2000/math/CVector2.h"

// 0x004f4708 IKCommonGameManager_State6_maybe. Update: the +0x2a8 billboard placed at player 0's
// position (reset to (-1, -1) through vt+0x31c when vt+0x310(0) is clear) and shown. Leave: both billboards
// hidden.
uint8_t CKS08GameManager::State6Common(int32_t phase, uint8_t /*other*/) {
    if (phase == 0) {
        if (Vf310(0) == 0 || g_pEngine->m_gameLoop->m_unk5c != 0) {
            Vf314(0, 1);
            // vt+0x31c 0x4f6b48: player 0's position (+0x298) = (-1, -1), returned and stored again.
            m_afUnk298[1] = -0x1p+0f;
            m_afUnk298[0] = -0x1p+0f;
        }
        IKNode2d* billboard = static_cast<IKNode2d*>(m_unk2A8[0]);
        CVector2 position;
        position.m_fX = m_afUnk298[0];
        position.m_fY = m_afUnk298[1];
        billboard->SetPos(position);  // vt+0x74
        billboard->Enable();          // vt+0x64
    } else if (phase == 2) {
        static_cast<IKNode2d*>(m_unk2A8[1])->Disable();
        static_cast<IKNode2d*>(m_unk2A8[0])->Disable();
    }
    return 6;
}

// 0x004f48d0 IKCommonGameManager_StateHeroDeath_maybe. STUB(C1.6).
uint8_t CKS08GameManager::StateHeroDeathCommon(int32_t, uint8_t) { return 9; }
// 0x004f48f0 KStub_Return10_4f48f0
uint8_t CKS08GameManager::StateReturn10(int32_t, uint8_t) { return 10; }
// 0x004f48f8 KStub_Return11_4f48f8
uint8_t CKS08GameManager::StateReturn11(int32_t, uint8_t) { return 11; }

// 0x004f4928 IKCommonGameManager_State5_maybe: the skip entry of the "IKCommonGameManager" input
// enabled while the state lasts.
uint8_t CKS08GameManager::State5Common(int32_t phase, uint8_t /*other*/) {
    if (phase == 1) m_pCommonInputDicos->SetActionEnabled(0, 1);
    else if (phase == 2) m_pCommonInputDicos->SetActionEnabled(0, 0);
    return 5;
}

// 0x004f49a8 IKCommonGameManager_State2_maybe: as State5; leaving also stops the interface video.
uint8_t CKS08GameManager::State2Common(int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        m_pCommonInputDicos->SetActionEnabled(0, 1);
        return 2;
    }
    if (phase != 2) return 2;
    if (GetInterfaceVideo() != nullptr && (GetInterfaceVideo()->m_baData & 1) != 0) GetInterfaceVideo()->Stop();
    m_pCommonInputDicos->SetActionEnabled(0, 0);
    return 2;
}

// 0x004f4b08 IKCommonGameManager_State3_maybe: the logo videos (+0x2d0) one after another; skip
// (CKInput_IsMenuSkipPressed_maybe) ends the current one. State 0 after the last.
uint8_t CKS08GameManager::State3(int32_t phase, uint8_t /*other*/) {
    IKVideo** logos = reinterpret_cast<IKVideo**>(m_unk2D0.m_pBlock);
    const int32_t count = static_cast<int32_t>(m_unk2D0.m_ui32NbUsedElt);
    if (phase == 1) {
        if (count == 0) {
            m_i32CurrentLogo = -1;
        } else {
            g_pEngine->m_input->SetMappingEnabled(0, 1);
            m_i32CurrentLogo = 0;
            logos[0]->Start(nullptr);
        }
        m_pCommonInputDicos->SetActionEnabled(0, 1);
        return 3;
    }
    if (phase == 2) {
        const int32_t current = m_i32CurrentLogo;
        if (current >= 0 && current < count) logos[current]->Stop();
        m_pCommonInputDicos->SetActionEnabled(0, 0);
        return 3;
    }
    if (phase != 0) return 3;
    int32_t current = m_i32CurrentLogo;
    if (current == -1) return 0;
    // Every logo frame: the renderer's camera context's clear colour (engine +4 -> CKGraphic +4 ->
    // CRenderer +0x28 -> +0x44) = the shared black CColor at 0x00c50df8 (0, 0, 0, 0xff: the Str.cpp static
    // initialiser) with its alpha byte replaced by 0 (the stb of the phase, 0, into the copy's low byte),
    // written only when it differs. ClearRendererCamera (0xa4278) clears with it.
    {
        const uint32_t kSharedBlack = 0x000000ffu;  // 0x00c50df8 as the PS3 word (STUB: a local copy)
        const uint32_t clear = (kSharedBlack & 0xffffff00u) | static_cast<uint32_t>(phase & 0xff);
        CameraContext* context = g_pEngine->m_graphic->m_renderer->m_cameraContext;
        if (context->m_clearColor != clear) context->m_clearColor = clear;
    }
    if (logos[current]->m_state != 0 && !g_pEngine->m_input->IsMenuSkipPressed()) return 3;
    logos[m_i32CurrentLogo]->Stop();
    current = m_i32CurrentLogo + 1;
    m_i32CurrentLogo = current;
    if (current < count) {
        logos[current]->Start(nullptr);
        return 3;
    }
    return 0;
}

// 0x004f4de0 IKCommonGameManager_State1_maybe: the auto-load. Enter: flags +0x64 bits 22 and 27 cleared,
// bit 6 set. Update: the first frame clears bit 6; on the front-end level the request (bits 22 and 5: the
// save-data flow, GameLoop modes 7 / 2 / 8) is made once; when it is done (bit 5 cleared) bit 27 is set,
// and the state ends (0) once the game loop is back in mode 5 without a pending exit (+0x290).
uint8_t CKS08GameManager::State1(int32_t phase, uint8_t /*other*/) {
    if (phase == 0) {
        const uint32_t flags = m_flags64;
        if ((flags & 0x8000000) == 0) {
            if ((flags & 0x40) != 0) {
                m_flags64 = flags & ~0x40u;
                return 1;
            }
            if (IsFrontEndLevel() != 0) {
                if ((m_flags64 & 0x400000) == 0) m_flags64 = m_flags64 | 0x400000 | 0x20;
                else if ((m_flags64 & 0x20) == 0) m_flags64 = (m_flags64 & ~0x8000000u) | 0x8000000;
            }
        } else if (g_pEngine->m_gameManager->m_unk290 == -1) {
            return g_pEngine->m_gameLoop->m_mode != CKGameLoop::kModeLevel ? 1 : 0;
        }
        return 1;
    }
    if (phase == 1) {
        m_flags64 = (m_flags64 & ~0x08400040u) | 0x40;
        return 1;
    }
    return 1;
}

// 0x004f4fa0 IKCommonGameManager_StateInGame_maybe: game state 7 stays (returns 7). Every frame (phase 0) each
// HUD screen that is shown (flag bit 1) gets its state update (vt+0xd8 with 0, 0); on enter (phase 1) the
// two cursor billboards of the second player and the first (+0x2ac, +0x2a8) are hidden.
uint8_t CKS08GameManager::StateInGameCommon(int32_t phase, uint8_t) {
    if (phase == 0) {
        for (uint32_t i = Vf348(); i != 0; --i) {
            CKMenuBase114c* hud = static_cast<CKMenuBase114c*>(GetHudInterfaces()[i - 1]);
            if (hud != nullptr && (hud->m_ui32Flags & 2) != 0) hud->HandleStatePhase(0, 0);
        }
    } else if (phase == 1) {
        static_cast<IKNode2d*>(m_unk2A8[1])->Disable();
        static_cast<IKNode2d*>(m_unk2A8[0])->Disable();
        return 7;
    }
    return 7;
}
// 0x004f5128 CKS08GameManager_StateMenuCommon_maybe. STUB(C1.6): the pause menu.
uint8_t CKS08GameManager::StateMenuCommon(int32_t, uint8_t) { return 8; }
