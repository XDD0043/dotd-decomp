// MessageBox.cpp - the system message queue and its overlay. See MessageBox.h.
//
// Reconstructed original translation unit: 0x683d8-0x69848 (GAME_TOC1, main_toc1), 27 functions, 13 live.
// Primary owner: MessageBox (not a registered class)
// Other owners: CManager2d (4), SystemMessage (1), Draw2d (1), LocText (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x683d8  SystemMessage_SetCurrentId_maybe  [dead]
//   [ ] 0x68418  KStub_Nop_68418  [dead]
//   [ ] 0x68420  KStub_Return0_68420  [dead]
//   [ ] 0x68428  KStub_Nop_68428  [dead]
//   [ ] 0x68430  MessageBox_ResetAll_maybe  [dead]
//   [ ] 0x68510  MessageBox_PushJobMessageEntry_maybe
//   [x] 0x68540  StaticInitAndDestruction_68540 (the state's zero initialisation)
//   [ ] 0x685a8  _GLOBAL__I_685a8
//   [ ] 0x685b8  _GLOBAL__D_685b8
//   [x] 0x685c8  MessageBox_TakeResult_maybe
//   [ ] 0x68680  MessageBox_PushWideTextReturnEntry_maybe  [dead]
//   [x] 0x687a8  Draw2d_FullScreenColorQuad_maybe
//   [ ] 0x68808  CManager2d_UpdatePulseValue_maybe  [dead]
//   [ ] 0x68920  LocText_GetOrDefault_maybe
//   [ ] 0x689a8  MessageBox_ClearJobMessageEntries_maybe
//   [ ] 0x689b8  MessageBox_RefreshFirstEntryTimestamp_maybe  [dead]
//   [ ] 0x689d8  KStub_Nop_689d8  [dead]
//   [ ] 0x689e0  MessageBox_RemoveById_maybe  [dead]
//   [x] 0x68a70  MessageBox_ProcessQueue_maybe
//   [ ] 0x68ba8  MessageBox_RemoveAnsweredById_maybe  [dead]
//   [ ] 0x68c68  CManager2d_GetPulsingTextGray_maybe  [dead]
//   [x] 0x68de0  CManager2d_GetPulsingTextColor_maybe
//   [x] 0x68ef0  CManager2d_DrawSystemMessageOverlay_maybe (the loc lookup of a queued message: STUB(C2))
//   [x] 0x69358  MessageBox_Push_maybe
//   [ ] 0x694a0  MessageBox_ShowWideText_maybe  [dead]
//   [x] 0x695d0  MessageBox_Show_maybe
//   [ ] 0x69728  MessageBox_PushWideText_maybe  [dead]
#include <cstring>

#include "k2000/misc/MessageBox.h"

#include "Spyro2008/logic/CKS08GameManager.h"
#include "crt/ppc_ops.h"
#include "crt/xlround.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/graphical/system/CVideoManager.h"
#include "k2000/graphical/ui/CFlashMessageBox2d.h"
#include "k2000/graphical/ui/CManager2d.h"
#include "k2000/graphical/ui/CMenuManager.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"
#include "k2000/misc/Wcs.h"
#include "k2000/logic/ui/CKLocText.h"
#include "k2000/misc/JobQueue.h"

namespace {

// 0x00c5b918: the system message state (zeroed by the static initialiser 0x68540). +0x00..+0x08 the
// pulse (FloatApproach {target, speed, current}), +0x0c the time held at 1, +0x10 the real time of the
// last step; +0xd68 the queue's entries (0x10 bytes, the message id first), +0xda8 (0x00c5c6c0) their
// count. The bytes between (+0x14..+0xd67: the job message entries) are not used by the overlay.
struct SystemMessageEntry {
    uint32_t m_id;      // +0x00 the loc text id (or 200..203: CManager2d's cached strings)
    uint32_t m_unk04[3];
};
struct SystemMessageState {
    float m_afPulse[3];             // +0x00 target, speed, current
    float m_fPulseHold;             // +0x0c
    float m_fPulseLastTime;         // +0x10
    SystemMessageEntry m_entries[4];  // +0xd68
    uint32_t m_count;               // +0xda8 (0x00c5c6c0)
};
SystemMessageState s_state = {};

// 0x00c296a4 (.data, initial -1): the id of the message the overlay shows.
int32_t s_currentId = -1;

// 0x00c2966e the UTF-16 " " (TOC1 -0x6e90); 0x00c50df8 the shared black CColor (TOC1 -0x6e78) and
// 0x00c50dfc the shared white (TOC1 -0x6e9c), from Str.cpp's static initialiser (local copies).
const uint16_t kSpaceW[] = {0x20, 0};
const uint8_t kBlack[4] = {0x00, 0x00, 0x00, 0xff};
const uint8_t kWhite[4] = {0xff, 0xff, 0xff, 0xff};
// 0x00c297ec / 0x00c297fc: blend table entries; their +4 words are the source and destination blends.
const int32_t kBlendSrcAlpha = 5;     // 0x00c297f0
const int32_t kBlendInvSrcAlpha = 6;  // 0x00c29800

// Local copy of 0x00010a18 Wcs_Length (misc/Wcs.cpp, not ported yet; TextData.cpp and CLocManager.cpp
// keep copies too).
uint32_t Wcs_Length(const uint16_t* s) {
    uint32_t n = 0;
    while (s[n] != 0) ++n;
    return n;
}

// The pulse restarts at 1 (target 1, speed 1.2 per second, TOC1 -0x6ebc / -0x6eb8), the store order of
// both reset sites.
void ResetPulse() {
    s_state.m_afPulse[2] = 0x1p+0f;
    s_state.m_afPulse[1] = 0x1.333334p+0f;  // 1.2f (0x3f99999a)
    s_state.m_fPulseLastTime = 0.0f;
    s_state.m_afPulse[0] = 0x1p+0f;
    s_state.m_fPulseHold = 0.0f;
}

}  // namespace

uint32_t SystemMessage_GetCount() { return s_state.m_count; }

// 0x000687a8 Draw2d_FullScreenColorQuad_maybe (centre 0, 0: TOC1 -0x6e98)
void Draw2d_FullScreenColorQuad(const uint8_t* color) {
    DrawScreenColorQuad(0.0f, 0.0f, 0, kBlendSrcAlpha, kBlendInvSrcAlpha, color, kWhite, nullptr);
}

// 0x00068de0 CManager2d_GetPulsingTextColor_maybe (from the assembly). The frame clock's system time
// (IKTime +0x0c) gates the step; its system delta (+0x24) is the step and the hold increment.
void CManager2d_GetPulsingTextColor(uint8_t* color) {
    IKTime* clock = g_pEngine->m_timeManager->m_pTime;
    const float now = clock->m_afCurrentTime[IKTime::SYSTEM_TIME];
    const float dt = clock->m_afDeltaTime[IKTime::SYSTEM_TIME];
    if (now != s_state.m_fPulseLastTime) {
        s_state.m_fPulseLastTime = now;
        FloatApproach_Step(dt, s_state.m_afPulse);
        const float current = s_state.m_afPulse[2];
        if (current == 0x1p+0f) {
            if (s_state.m_fPulseHold < 0x1.8p+1f) {  // 3.0f (TOC1 -0x6e94)
                s_state.m_fPulseHold = dt + s_state.m_fPulseHold;
            } else {
                s_state.m_afPulse[0] = 0.0f;  // the word 0
            }
        } else if (current == 0.0f) {
            s_state.m_afPulse[0] = 0x1p+0f;
            s_state.m_fPulseHold = 0.0f;  // the word 0
        }
    }
    // 40 + 215 x pulse (TOC1 -0x6e7c 40.0f, -0x6e80 215.0f), lroundf (bridge 0x98d3a0), the low byte.
    const uint8_t grey = static_cast<uint8_t>(crt::lroundf(ppc::fmadds(s_state.m_afPulse[2], 0x1.aep+7f, 0x1.4p+5f)));
    color[3] = 0xff;
    color[2] = grey;
    color[0] = grey;
    color[1] = grey;
}

// 0x00068ef0 CManager2d_DrawSystemMessageOverlay_maybe (from the assembly).
void CManager2d_DrawSystemMessageOverlay() {
    CManager2d* manager = g_pEngine->m_manager2d;
    CVideoManager* video = g_pEngine->m_videoManager;
    CFlashMessageBox2d* box = nullptr;
    if (manager != nullptr && manager->m_menuManager != nullptr) {
        box = static_cast<CFlashMessageBox2d*>(static_cast<CMenuManager*>(manager->m_menuManager)->m_pFlashMessageBox);
        // vt+0x84 (0x9c8560, CFlashMessageBox2d's only implementation: the active byte +0x37c).
        if (box != nullptr && box->IsReady() == 0) box = nullptr;
    }
    // The shown id follows the newest queued message; the pulse restarts when it changes.
    if (s_state.m_count != 0) {
        const int32_t id = static_cast<int32_t>(s_state.m_entries[s_state.m_count - 1].m_id);
        if (id != s_currentId) {
            s_currentId = id;
            ResetPulse();
        }
    } else if (s_currentId != -1) {
        s_currentId = -1;
        ResetPulse();
    }
    if (g_bootLocLoaded == 0) return;
    CDefaultGameManager* gameManager = g_pEngine->m_gameManager;
    // A save-data request (vt+0x108): the screen dimmed with the shared black (opaque).
    if (gameManager->Vf108() != 0) Draw2d_FullScreenColorQuad(kBlack);
    if (s_state.m_count != 0) {
        Draw2d_FullScreenColorQuad(kBlack);
        const SystemMessageEntry* entry = &s_state.m_entries[s_state.m_count - 1];
        if (gameManager->m_unk290 == -1) {
            const uint16_t* text = kSpaceW;
            // STUB(C2): with the loc data loaded, CLocManager_GetText(engine loc manager, id) (0x37028) and,
            // when it has the text, LocString_GetText (0x35d28) give the message. The queue is empty until
            // MessageBox_Push (0x69358) is ported, so this branch is not reached yet.
            manager->DrawSystemText(text, 1, 1);
        } else {
            manager->DrawSystemText(manager->GetSystemMessageString(entry->m_id), 1, 0);
        }
        return;
    }
    if (!video->IsLoadingVideoActive()) {
        // vt+0x74 0x52a8f0 CFlashMessageBox2d_Draw_maybe (Render) with the engine clock.
        if (box != nullptr) box->Render(g_pEngine->m_timeManager->m_pTime);
        return;
    }
    // The loading video's two texts: CKS08GameManager vt+0x228 (0x4ec928, +0x4e4) at the top and vt+0x22c
    // (0x4ec938, +0x6e4) at the bottom, when not empty. (The slots are not declared on the game manager
    // yet, C1.6 gm; their only implementations return these members.)
    CKS08GameManager* s08 = static_cast<CKS08GameManager*>(gameManager);
    const uint16_t* top = reinterpret_cast<const uint16_t*>(s08->m_unk4E4);
    if (Wcs_Length(top) != 0) manager->DrawSystemText(top, 0, 0);
    const uint16_t* bottom = reinterpret_cast<const uint16_t*>(s08->m_unk6E4);
    if (Wcs_Length(bottom) != 0) manager->DrawSystemText(bottom, 2, 0);
}

namespace {
// 0x00c5b92c: the message box requests (four, 0x354 bytes each) and 0x00c5c67c their count.
SFlashMessageRequest s_requests[4];
uint32_t s_requestCount = 0;
const uint16_t kEmptyWide[] = {0};  // 0x00ac3fc0
}  // namespace

// 0x00c5c67c: the queue's count (GameLoop's inhibit flag +0x1c).
int32_t MessageBox_GetQueuedCount() { return static_cast<int32_t>(s_requestCount); }

// 0x00069358 MessageBox_Push_maybe
void MessageBox_Push(float x, float y, IKSerializable* sender, const CKLocText* text, int32_t combineType, int32_t defaultButton,
                     uint8_t (*interrupt)()) {
    const uint16_t* wide = text == nullptr ? kEmptyWide : LocString_GetText(text);
    if (sender == nullptr && s_requestCount == 1) {
        s_requests[0].m_fStartTime = g_pEngine->m_timeManager->m_pTime->m_afCurrentTime[IKTime::SYSTEM_TIME];
        return;
    }
    SFlashMessageRequest* request = &s_requests[s_requestCount];
    ++s_requestCount;
    request->m_pSender = sender;
    request->m_bNotifySender = 0;
    WStr_CopyReturnEnd(request->m_wszText, wide);
    request->m_fUnk334 = x;
    request->m_eCombineType = combineType;
    request->m_eDefaultButton = defaultButton;
    request->m_pfnInterrupt = interrupt;
    request->m_fTimeout = y;
    request->m_bTimer = 0;
    request->m_fStartTime = g_pEngine->m_timeManager->m_pTime->m_afCurrentTime[IKTime::SYSTEM_TIME];
    request->m_eResult = CFlashMessageBox2d::kMsgBoxPending;
}

// 0x000695d0 MessageBox_Show_maybe
void MessageBox_Show(float x, float y, IKSerializable* sender, const CKLocText* text, int32_t combineType, int32_t defaultButton) {
    MessageBox_Push(x, y, sender, text, combineType, defaultButton, nullptr);
    s_requests[s_requestCount - 1].m_bNotifySender = 1;
}

// 0x000685c8 MessageBox_TakeResult_maybe
int32_t MessageBox_TakeResult(const IKSerializable* sender) {
    for (uint32_t i = s_requestCount; i != 0; --i) {
        SFlashMessageRequest* request = &s_requests[i - 1];
        if (request->m_pSender != sender) continue;
        const int32_t result = request->m_eResult;
        if (result != CFlashMessageBox2d::kMsgBoxPending) {
            --s_requestCount;
            std::memmove(request, request + 1, (s_requestCount - (i - 1)) * sizeof(SFlashMessageRequest));
        }
        return result;
    }
    return CFlashMessageBox2d::kMsgBoxPending;
}

// 0x00068a70 MessageBox_ProcessQueue_maybe: the newest request is handed to the Flash message box (once it is ready); an
// answered request that asked to notify its sender (MessageBox_Show) leaves the queue and the sender gets message 0x2d00.
void MessageBox_ProcessQueue() {
    if (s_requestCount == 0 || g_pEngine->m_manager2d == nullptr) return;
    CMenuManager* menus = static_cast<CMenuManager*>(g_pEngine->m_manager2d->m_menuManager);
    if (menus == nullptr) return;
    CFlashMessageBox2d* box = static_cast<CFlashMessageBox2d*>(menus->m_pFlashMessageBox);
    if (box == nullptr || box->IsReady() == 0) return;
    SFlashMessageRequest* request = &s_requests[s_requestCount - 1];
    const int32_t result = box->ProcessRequest(request);  // vt+0x90
    if (request->m_bNotifySender != 0 && result != CFlashMessageBox2d::kMsgBoxPending) {
        --s_requestCount;
        request->m_pSender->MessageProc(0x2d00, reinterpret_cast<void*>(static_cast<intptr_t>(result)));
    }
}
