// kside_test - C1.5 family D: the K engine's Flash classes on the real front-end data.
//
// Until the Rt2d (B) and Rt2dAnim (C) ports land, every CKFlashUI's maestro is null (Rt2dMaestroStreamRead
// is a stub), so the checks cover what the PostLoads and the frame functions do without a movie: the
// interface state bits, the hot spots' anchor reset, the message box's state callback, the texts that need
// no id, the per-frame CManager2d / CKFlashManager calls, and the interface state machine (with the
// sector's loaded bit set by the test: the sector activation is not ported yet).
#include <cfloat>
#include <cstdio>
#include <cstring>

#include "boot_helper.h"
#include "k2000/components/CKLocTextAccessor.h"
#include "k2000/graphical/ui/CFlashHotSpot.h"
#include "k2000/graphical/ui/CFlashMessageBox2d.h"
#include "k2000/graphical/ui/CKFlashManager.h"
#include "k2000/graphical/ui/CKFlashText.h"
#include "k2000/graphical/ui/CKFlashUI.h"
#include "k2000/graphical/ui/CManager2d.h"
#include "k2000/graphical/ui/CMenuManager.h"
#include "k2000/logic/CKSector.h"
#include "k2000/logic/ui/CKMenuMessageBox.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/CTimeManager.h"

int main() {
    if (!c15::BootToFrontEnd()) {
        std::printf("kside: no game data configured; skipped\n");
        return 77;
    }
    CKFlashManager* manager = g_pEngine->m_flashManager;
    C15_CHECK(manager != nullptr);
    C15_CHECK(manager->m_ui32NbFlashUI == 29);

    // CKFlashUI_PostLoad: every interface stopped (state bits clear); the Load cleared kNeverRender, which
    // only the message box's interface (#4) gets back (CFlashMessageBox2d_PostLoad -> HideMessage; live 0x60).
    // Since CKLevel_Start is ported (the base sector announced at the level start), interfaces #19 and #24 are
    // already started at this point (0x62), as the front-end gate's live dump has them.
    uint32_t texts = 0, hotSpots = 0, messagesIn = 0, messagesOut = 0;
    for (uint32_t i = 0; i < manager->m_ui32NbFlashUI; ++i) {
        CKFlashUI* ui = manager->GetInterfaceByIndex(i);
        if (i == 19 || i == 24) {
            C15_CHECK(ui->m_baFlags == 0x62);
        } else {
            C15_CHECK((ui->m_baFlags & CKFlashUI::kStateMask) == 0);
            C15_CHECK(((ui->m_baFlags & CKFlashUI::kNeverRender) != 0) == (i == 4));
        }
        C15_CHECK(ui->m_pSector != nullptr);
        C15_CHECK(ui->m_mMap.m_ui32HashSize == 0x25);
        texts += ui->m_ui32FlashTextNb;
        hotSpots += ui->m_ui32HotSpotNb;
        messagesIn += ui->m_ui32FlashMessageInNb;
        messagesOut += ui->m_ui32FlashMessageOutNb;
        // CFlashHotSpot_PostLoad: the anchor reset (live: 0, (1, 1), white before the first anchor).
        for (uint32_t h = 0; h < ui->m_ui32HotSpotNb; ++h) {
            CFlashHotSpot* hotSpot = static_cast<CFlashHotSpot*>(ui->m_apHotSpot[h]);
            C15_CHECK(hotSpot->m_bVisibilityTest == 0);
            C15_CHECK(hotSpot->m_v2Size_maybe.m_fX == 1.0f && hotSpot->m_v2Size_maybe.m_fY == 1.0f);
            C15_CHECK(hotSpot->m_aColor_maybe[0] == 0xff && hotSpot->m_aColor_maybe[3] == 0xff);
            for (uint32_t n = 0; n < hotSpot->m_vp2dObject.m_ui32NbUsedElt; ++n)
                C15_CHECK((hotSpot->m_vp2dObject.m_pBlock[n].m_pNode->m_baFlags & 2) == 0);  // disabled
        }
        // CKFlashText_PostLoad: a text that needs no id has no loc text.
        for (uint32_t t = 0; t < ui->m_ui32FlashTextNb; ++t) {
            CKFlashText* text = static_cast<CKFlashText*>(ui->m_apFlashText[t]);
            if (text->m_bNoTextIdNeeded == 0) continue;
            CKLocTextAccessor* accessor = text->m_pTextAccessor;
            C15_CHECK(accessor->m_texts.m_pBlock != nullptr ? accessor->m_texts.m_pBlock[0] == nullptr
                                                            : accessor->m_pText == nullptr);
        }
    }
    // LVL000's counts (research: 319 texts, 316 hot spots, 61 messages in, 39 out).
    C15_CHECK(texts == 319);
    C15_CHECK(hotSpots == 316);
    C15_CHECK(messagesIn == 61);
    C15_CHECK(messagesOut == 39);

    // CFlashMessageBox2d_PostLoad: the state callback and the two flags; CKMenuMessageBox +0xd4 = -1.
    CManager2d* manager2d = g_pEngine->m_manager2d;
    CMenuManager* menus = static_cast<CMenuManager*>(manager2d->m_menuManager);
    CFlashMessageBox2d* box = static_cast<CFlashMessageBox2d*>(menus->m_pFlashMessageBox);
    C15_CHECK(box != nullptr);
    if (box != nullptr) {
        C15_CHECK(box->m_stateMachine.m_pOwner == box);
        C15_CHECK(box->m_stateMachine.m_pTable != nullptr &&
                  box->m_stateMachine.m_pTable[0] == &CFlashMessageBox2d::StateWaitAnswer);
        C15_CHECK(box->m_stateMachine.m_ui8Count == 1 && box->m_stateMachine.m_ui8Current == 0xff);
        C15_CHECK(box->m_bReady == 1 && box->IsReady() == 1);
        C15_CHECK(box->m_fFadeStartTime == FLT_MAX && box->m_fFadeAlpha == 0.0f && box->IsFading() == 0);
        C15_CHECK(box->m_i32ShowCount == 0);
        C15_CHECK(box->m_pMenu != nullptr && box->m_pMenu->m_iUnkd4 == -1);
        // Nothing is shown at the front end: the interface is kNeverRender (vt+0x6c), and a frame with no
        // message running does nothing (vt+0x7c).
        C15_CHECK(box->IsMessageBoxShown() == 0);
        C15_CHECK(box->GetFlashInterface() == box->m_pMenu->m_pFlashUI);
        C15_CHECK(box->UpdateMessage() == 1);
    }

    // The frame functions run on the loaded front end (no movie yet: they only walk the lists).
    IKTime* clock = g_pEngine->m_gameLoop->m_timeManager->m_pTime;
    manager2d->m_bUpdateScreen = 1;
    C15_CHECK(manager2d->UpdateScreen() == 1);
    C15_CHECK(manager2d->m_bUpdateScreen == 0);
    C15_CHECK(manager2d->m_ui32PendingEvents_maybe == 2);
    C15_CHECK(manager2d->m_fAspect == 0x1.c71c72p+0f);  // live CManager2d +0x18: 1.7777778 (0x3fe38e39)
    manager2d->PreUpdate(clock);
    C15_CHECK(manager2d->m_ui32PendingEvents_maybe == 0);
    manager2d->UpdateAndExtract(0.0f, nullptr, nullptr, nullptr, 0);
    manager2d->Render();
    C15_CHECK(manager2d->RenderMsgBox() == 1);
    for (int i = 0; i < 5; ++i) c15::RunFrame();

    // The interface state machine on the main menu's movie (#0), its sector marked loaded.
    CKFlashUI* mainMenu = manager->GetInterfaceByIndex(0);
    const uint16_t sectorBits = mainMenu->m_pSector->m_ba16Properties;
    mainMenu->m_pSector->m_ba16Properties = static_cast<uint16_t>(sectorBits | 1);
    mainMenu->m_cColorMult_maybe.alpha = 0.5f;
    mainMenu->StartInterface(1);
    C15_CHECK((mainMenu->m_baFlags & CKFlashUI::kStateMask) == 2);
    C15_CHECK((mainMenu->m_baFlags & 0x40) != 0 && (mainMenu->m_baFlags & 0x100) == 0);
    C15_CHECK(mainMenu->m_cColorMult_maybe.alpha == -1.0f);  // live +0x228 of the started movie: -1.0
    mainMenu->PauseInterface();
    C15_CHECK((mainMenu->m_baFlags & CKFlashUI::kStateMask) == 1);
    mainMenu->ResumeInterface();
    C15_CHECK((mainMenu->m_baFlags & CKFlashUI::kStateMask) == 2);
    // A getURL label queues the matching message in (the first one's label id is its index after
    // BindSceneObjects; without a maestro the ids stay as loaded).
    if (mainMenu->m_ui32FlashMessageInNb != 0) {
        IKFlashObject* message = static_cast<IKFlashObject*>(mainMenu->m_apFlashMessageIn[0]);
        mainMenu->TranslateMessageIn(static_cast<int32_t>(message->m_ui32LabelId));
        C15_CHECK(mainMenu->m_ui32FlashMessageInQueuedNb == 1);
        mainMenu->m_ui32FlashMessageInQueuedNb = 0;
    }
    manager->Stop();
    C15_CHECK((mainMenu->m_baFlags & CKFlashUI::kStateMask) == 0);
    mainMenu->m_pSector->m_ba16Properties = sectorBits;

    c15::Shutdown();
    if (c15::g_failures == 0) std::printf("kside: all tests passed\n");
    return c15::g_failures == 0 ? 0 : 1;
}
