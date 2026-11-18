// CFlashMessageBox2d.h - the Flash message box (key 0xd0d, vtable 0xb2b928, size 0x380). Original unit:
// CFlashMessageBox2d.cpp (0x52a150-0x52c700). DotD's class differs from XXL2's (XXL2 derives from
// IKSerializable and reads nine references); here the base is KBaseE8D and Load reads one reference, the
// "Menu Message Box" screen (CKMenuMessageBox) that holds the interface, the text and the three buttons.
// CMenuManager (+0x08) holds the box; CManager2d (+0xa78) holds the menu manager.
//
// How the game uses it (C1.6):
// - The message queue (misc/MessageBox.cpp, 0x68xxx: MessageBox_Push_maybe 0x69358 / MessageBox_Show_maybe
//   0x695d0 fill an SFlashMessageRequest) calls ProcessRequest (vt+0x90) once per frame
//   (MessageBox_ProcessQueue_maybe 0x68a70, while vt+0x84 IsReady); when the result is not
//   kMsgBoxPending and the request's m_bNotifySender is set, the queue pops it and sends message 0x2d00
//   (data: the result) to the request's sender. MessageBox_TakeResult_maybe 0x685c8 polls a request by sender.
// - CDefaultGameManager_SaveFlowB_State1_maybe 0x14ba0 calls vt+0x58 ShowMessageLoc directly (TRC text
//   0x1c2, type 1, button 0, no interrupt, 1.0, timeout -1).
// - CKS08GameManager_HandleCinematicAndUIMessage_maybe 0x4eee20 (script messages 0x266c..0x2679) calls vt+0x54
//   ShowMessageModal; the answer sets the game manager's flags +0x64 (0x20000 / 0x40000 / 0x80000).
// - CKMenuMessageBox_vfE8 0x52cc28 (the yes/no buttons validated) sends message 0x2301 (data: the item)
//   to the box: MessageProc stores it as the selected button.
// - CManager2d_DrawSystemMessageOverlay_maybe 0x68ef0 calls vt+0x74 Render(engine clock) while vt+0x84.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/graphical/ui/KBaseE8D.h"

class CKMenuMessageBox;
class JobQueue;

// One message (0x354 bytes): a message queue entry (misc/MessageBox.cpp) and the box's current message
// (CFlashMessageBox2d +0x28). Field names from the users; XXL2 has no such struct (its box has the
// arguments of ModalPromptMessage as locals).
struct SFlashMessageRequest {
    IKSerializable* m_pSender;        // +0x000 notified with message 0x2d00 (MessageBox_Show_maybe; Push: 0)
    uint8_t m_bNotifySender;          // +0x004 MessageBox_Show_maybe sets 1 (MessageBox_ProcessQueue_maybe pops)
    uint8_t m_pad005;
    uint16_t m_wszText[0x191];        // +0x006 the text (UTF-16), up to +0x328
    int32_t m_eCombineType;           // +0x328 CFlashMessageBox2d::EMsgBoxCombineType (the buttons)
    int32_t m_eDefaultButton;         // +0x32c CFlashMessageBox2d::EMsgBoxButton: the button focused first
    KBaseE8D::InterruptFn m_pfnInterrupt;  // +0x330 polled every frame; true ends the message (kMsgBoxInterrupt)
    float m_fUnk334;                  // +0x334 the callers pass 1.0; nothing in this unit reads it
    float m_fTimeout;                 // +0x338 seconds; -1 = none (kMsgBoxTimeout when it runs out)
    uint8_t m_bTimer;                 // +0x33c CKMenuMessageBox_Show_maybe's flag: the menu timer from its +0xdc
    uint8_t m_pad33d[3];
    JobQueue* m_pJobQueue;            // +0x340 StateWaitAnswer's enter stores the engine's (not read here)
    IKTime* m_pClock;                 // +0x344 the engine's frame clock (StateWaitAnswer's enter)
    uint8_t m_unk348;                 // +0x348 StateWaitAnswer's enter clears it
    uint8_t m_bInterrupted;           // +0x349 the interrupt callback returned true (or the timeout ran out)
    uint8_t m_bTimedOut;              // +0x34a the timeout ran out
    uint8_t m_pad34b;
    float m_fStartTime;               // +0x34c the clock's system time when the message started
    int32_t m_eResult;                // +0x350 EMsgBoxButton, kMsgBoxPending while unanswered
};
DOTD_ASSERT_SIZE(SFlashMessageRequest, 0x354);
DOTD_ASSERT_OFFSET(SFlashMessageRequest, m_bNotifySender, 0x004);
DOTD_ASSERT_OFFSET(SFlashMessageRequest, m_wszText, 0x006);
DOTD_ASSERT_OFFSET(SFlashMessageRequest, m_eCombineType, 0x328);
DOTD_ASSERT_OFFSET(SFlashMessageRequest, m_eDefaultButton, 0x32c);
DOTD_ASSERT_OFFSET(SFlashMessageRequest, m_pfnInterrupt, 0x330);
DOTD_ASSERT_OFFSET(SFlashMessageRequest, m_fUnk334, 0x334);
DOTD_ASSERT_OFFSET(SFlashMessageRequest, m_fTimeout, 0x338);
DOTD_ASSERT_OFFSET(SFlashMessageRequest, m_bTimer, 0x33c);
DOTD_ASSERT_OFFSET(SFlashMessageRequest, m_pJobQueue, 0x340);
DOTD_ASSERT_OFFSET(SFlashMessageRequest, m_pClock, 0x344);
DOTD_ASSERT_OFFSET(SFlashMessageRequest, m_unk348, 0x348);
DOTD_ASSERT_OFFSET(SFlashMessageRequest, m_bInterrupted, 0x349);
DOTD_ASSERT_OFFSET(SFlashMessageRequest, m_bTimedOut, 0x34a);
DOTD_ASSERT_OFFSET(SFlashMessageRequest, m_fStartTime, 0x34c);
DOTD_ASSERT_OFFSET(SFlashMessageRequest, m_eResult, 0x350);

class CFlashMessageBox2d : public KBaseE8D {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x34)
    DOTD_DECLARE_FACTORIES(CFlashMessageBox2d)

    // XXL2 CFlashMessageBox2d::EMsgBoxCombineType (the same values: StateWaitAnswer's answer table).
    enum EMsgBoxCombineType : int32_t {
        MSGBOX_COMBINE_NO_BUTTON = 0,
        MSGBOX_COMBINE_OK = 1,
        MSGBOX_COMBINE_OK_CANCEL = 2,
        MSGBOX_COMBINE_YES_NO = 3,
        MSGBOX_COMBINE_RETRY_CANCEL = 4,
        MSGBOX_COMBINE_YES_NO_CANCEL = 5,
        MSGBOX_COMBINE_ABORT_RETRY_IGNORE = 6,
    };
    // XXL2 CFlashMessageBox2d::EMsgBoxButton for 0..6; DotD's values past 6 differ from XXL2's
    // (MSGBOX_INTERRUPT 7, MSGBOX_BUTTON_UNDEFINED 8), so those names are ours (_maybe).
    enum EMsgBoxButton : int32_t {
        MSGBOX_BUTTON_OK = 0,
        MSGBOX_BUTTON_CANCEL = 1,
        MSGBOX_BUTTON_ABORT = 2,
        MSGBOX_BUTTON_RETRY = 3,
        MSGBOX_BUTTON_IGNORE = 4,
        MSGBOX_BUTTON_YES = 5,
        MSGBOX_BUTTON_NO = 6,
        kMsgBoxInterrupt = 8,   // _maybe: the interrupt callback returned true
        kMsgBoxTimeout = 0xa,   // _maybe: the timeout ran out
        kMsgBoxPending = 0xb,   // _maybe: no answer yet (also an unknown combine type)
    };

    // The box's state machine (the same shape as CKS08GameManager's, a pointer to member function: the PS3
    // stores {OPD, this adjustment} pairs): phase 1 on enter (the previous state), 2 on leave (the next
    // state), 0 every frame (returns the next state). PostLoad installs one state, StateWaitAnswer.
    typedef uint8_t (CFlashMessageBox2d::*StateHandler)(int32_t phase, uint8_t other);
    struct StateMachine {
        CFlashMessageBox2d* m_pOwner;  // +0x00 PostLoad: the box
        StateHandler* m_pTable;        // +0x04 PostLoad: Mem_AllocAligned16, one entry
        uint8_t m_ui8Count;            // +0x08 PostLoad: 1
        uint8_t m_ui8Current;          // +0x09 0xff: none (the constructor and Destroy)
        uint8_t m_pad0a[2];
        uint8_t Call(uint8_t state, int32_t phase, uint8_t other) { return (m_pOwner->*m_pTable[state])(phase, other); }
        // The inlined start: state 0 entered when no state runs (the store before the call).
        void StartIfIdle();
        // The inlined switch: leave the current state, store the next one, enter it with the previous one.
        void Switch(uint8_t next);
        // The inlined frame: the current state's update, then the switch when it returns another state.
        void Tick();
    };

    CFlashMessageBox2d();  // inlined in 0x0052b058 CFlashMessageBox2d_Create (copy 0x52a1a0 unreferenced)
    ~CFlashMessageBox2d() override {}                                       // vt+0x00 / +0x04  0x9c85f8 / 0x9c8670
    int32_t IsKindOfClass(uint32_t key) override {                          // vt+0x08 0x9c85d0
        return key == 0xd0d || key == 0xe8d || key == 0xc;
    }
    void Destroy() override;                                                // vt+0x10 0x0052af20 CFlashMessageBox2d_Destroy
    int32_t MessageProc(uint16_t message, void* data) override;            // vt+0x1c 0x0052ace0 CFlashMessageBox2d_MessageProc
    void RecursiveRegistration(int32_t type) override;                      // vt+0x24 0x0052ae58 CFlashMessageBox2d_RecursiveRegistration
    int32_t Save(IKFile* /*file*/, int32_t /*type*/) override { return 1; }                   // vt+0x28 0x0052ac48 CFlashMessageBox2d_Save
    int32_t Load(IKFile* file, int32_t type) override;                      // vt+0x2c 0x0052ac50 CFlashMessageBox2d_Load
    int32_t PostLoad(int32_t type) override;                                // vt+0x30 0x0052ad38 CFlashMessageBox2d_PostLoad

    // vt+0x50 0x0052a3b8 CFlashMessageBox2d_ShowMessageModalLoc_maybe (XXL2 ModalPromptMessage(UInt32, ...)):
    // the text's string (or "") through vt+0x54 with timer 0.
    int32_t ShowMessageModalLoc(CKLocText* text, int32_t type, int32_t button, InterruptFn interrupt, float unk,
                                float timeout) override;
    // vt+0x54 0x0052b678 CFlashMessageBox2d_ShowMessageModal_maybe (XXL2 ModalPromptMessage(const WChar*, ...)):
    // runs the message until it is answered. BUG(original): see the .cpp (the PS3's modal loop is a stub).
    int32_t ShowMessageModal(const uint16_t* text, int32_t type, int32_t button, InterruptFn interrupt, float unk,
                             float timeout, uint8_t timer) override;
    // vt+0x58 0x0052a2e0 CFlashMessageBox2d_ShowMessageLoc_maybe: the text's string (or "") through vt+0x5c.
    int32_t ShowMessageLoc(CKLocText* text, int32_t type, int32_t button, InterruptFn interrupt, float unk,
                           float timeout) override;
    // vt+0x5c 0x0052c010 CFlashMessageBox2d_ShowMessage_maybe: one frame of the message; returns its result
    // (kMsgBoxPending while unanswered). The caller calls it again every frame.
    int32_t ShowMessage(const uint16_t* text, int32_t type, int32_t button, InterruptFn interrupt, float unk,
                        float timeout, uint8_t timer) override;
    // vt+0x60 0x9c8530 KBaseE8D's (0xb).
    void ShowMessageBox() override;            // vt+0x64 0x0052a778 CFlashMessageBox2d_ShowWidget_maybe (XXL2 ShowMessageBox)
    void HideMessageBox() override;            // vt+0x68 0x0052a730 CFlashMessageBox2d_CloseMessage_maybe (XXL2 HideMessageBox)
    int32_t IsMessageBoxShown() override;      // vt+0x6c 0x0052a218 CFlashMessageBox2d_vf6C (XXL2 IsMessageBoxShown)
    void StopMessageBox(int32_t resetFade) override;  // vt+0x70 0x0052a4e8 CFlashMessageBox2d_Close_maybe (XXL2 StopMessageBox)
    void Render(IKTime* time) override;        // vt+0x74 0x0052a8f0 CFlashMessageBox2d_Draw_maybe (XXL2 Render)
    void Vf78() override {}                    // vt+0x78 0x0052a2d8 CFlashMessageBox2d_vf78 (empty)
    uint8_t UpdateMessage() override;          // vt+0x7c 0x0052bde0 CFlashMessageBox2d_vf7C
    uint8_t SetMessageText(CKLocText* text) override;  // vt+0x80 0x0052ba30 CFlashMessageBox2d_SetText_maybe
    uint8_t IsReady() override { return m_bReady; }    // vt+0x84 0x9c8560 CFlashMessageBox2d_vf84
    uint8_t IsFading() override { return m_fFadeAlpha != 0.0f ? 1 : 0; }  // vt+0x88 0x9c8568 CFlashMessageBox2d_vf88 (bne: NaN is 1)
    IKSerializable* GetFlashInterface() override;      // vt+0x8c 0x9c8588 CFlashMessageBox2d_vf8C
    int32_t ProcessRequest(SFlashMessageRequest* request) override;  // vt+0x90 0x0052c398 CFlashMessageBox2d_ProcessRequest_maybe

    // 0x0052b148 CFlashMessageBox2d_StateWaitAnswer_maybe: the only state (installed by PostLoad).
    uint8_t StateWaitAnswer(int32_t phase, uint8_t other);

    // ---- C2.8 port-rest R03: four helpers nothing in the binary calls (only their OPDs exist, no vtable slot) ----
    // 0x0052a490 CFlashMessageBox2d_SetBoxText_maybe: the menu's text (the third argument, r6, is the type; r5 unused).
    void SetBoxText(const uint16_t* text, int32_t unused, uint32_t type);
    // 0x0052a4c0 CFlashMessageBox2d_SetButtonLayout_maybe: the menu's buttons.
    void SetButtonLayout(uint32_t type, int32_t button);
    // 0x0052a600 CFlashMessageBox2d_Show_maybe (XXL2 StartMessageBox): input configuration 1 on, the Flash input
    // locked, the menu shown.
    void StartMessageBox(uint8_t timer);
    // 0x0052b0b8 CFlashMessageBox2d_SetLocText_maybe: the text's string (or "-NO TRC DEFINED-") as the menu's text.
    void SetLocText(CKLocText* text, int32_t unused, uint32_t type);

    CKMenuMessageBox* m_pMenu;      // +0x04 a reference: the "Menu Message Box" screen (CKMenuMessageBox, 0x734c)
    int32_t m_i32SelectedButton;    // +0x08 XXL2 m_i32SelectedButton: the button the menu validated (MessageProc 0x2301), -1 none
    uint32_t m_unk0c;               // +0x0c StateWaitAnswer's update sets 0; nothing reads it here
    float m_fFadeAlpha;             // +0x10 the screen darkening's alpha (Render: 225 while shown, then -900/s)
    float m_fFadeStartTime;         // +0x14 when the darkening starts to fade (Render: the time + 0.25)
    int32_t m_i32ShowCount;         // +0x18 StateWaitAnswer's enter +1, leave -1 (StopMessageBox at 0) _maybe
    StateMachine m_stateMachine;    // +0x1c
    SFlashMessageRequest m_request; // +0x28 the current message (ProcessRequest copies the queue entry in and out)
    uint8_t m_bReady;               // +0x37c PostLoad sets 1, Destroy 0 (vt+0x84) (+0x37d..+0x37f: padding)
};
DOTD_ASSERT_SIZE(CFlashMessageBox2d, 0x380);
DOTD_ASSERT_OFFSET(CFlashMessageBox2d, m_pMenu, 0x04);
DOTD_ASSERT_OFFSET(CFlashMessageBox2d, m_i32SelectedButton, 0x08);
DOTD_ASSERT_OFFSET(CFlashMessageBox2d, m_unk0c, 0x0c);
DOTD_ASSERT_OFFSET(CFlashMessageBox2d, m_fFadeAlpha, 0x10);
DOTD_ASSERT_OFFSET(CFlashMessageBox2d, m_fFadeStartTime, 0x14);
DOTD_ASSERT_OFFSET(CFlashMessageBox2d, m_i32ShowCount, 0x18);
DOTD_ASSERT_OFFSET(CFlashMessageBox2d, m_stateMachine, 0x1c);
DOTD_ASSERT_OFFSET(CFlashMessageBox2d, m_request, 0x28);
DOTD_ASSERT_OFFSET(CFlashMessageBox2d, m_bReady, 0x37c);
