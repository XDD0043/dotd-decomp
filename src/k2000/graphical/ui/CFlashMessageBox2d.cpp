// CFlashMessageBox2d.cpp - reconstructed original translation unit 0x52a150-0x52c700 (GAME_TOC1, main_toc1), 34 functions, 31 live.
// Primary class: CFlashMessageBox2d  key 0xd0d  category Graphical  size 0x380  vtable 0xb2b928
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x52a150  CFlashMessageBox2d_Delete
//   [ ] 0x52a1a0  CFlashMessageBox2d_Construct  [dead]
//   [ ] 0x52a1d8  CFlashMessageBox2d_Construct_2  [dead]
//   [ ] 0x52a210  KStub_Return0_52a210  [dead]
//   [x] 0x52a218  CFlashMessageBox2d_vf6C
//   [x] 0x52a2d8  CFlashMessageBox2d_vf78
//   [x] 0x52a2e0  CFlashMessageBox2d_ShowMessageLoc_maybe
//   [x] 0x52a3b8  CFlashMessageBox2d_ShowMessageModalLoc_maybe
//   [x] 0x52a490  CFlashMessageBox2d_SetBoxText_maybe  (no caller: only its OPD)
//   [x] 0x52a4c0  CFlashMessageBox2d_SetButtonLayout_maybe  (no caller: only its OPD)
//   [x] 0x52a4e8  CFlashMessageBox2d_Close_maybe
//   [x] 0x52a600  CFlashMessageBox2d_Show_maybe  (XXL2 StartMessageBox; no caller: only its OPD)
//   [x] 0x52a688  CFlashMessageBox2d_DeleteArray
//   [x] 0x52a730  CFlashMessageBox2d_CloseMessage_maybe
//   [x] 0x52a778  CFlashMessageBox2d_ShowWidget_maybe
//   [ ] 0x52a830  RegisterCFlashMessageBox2dClass
//   [ ] 0x52a8d0  _GLOBAL__D_52a8d0
//   [ ] 0x52a8e0  _GLOBAL__I_52a8e0
//   [x] 0x52a8f0  CFlashMessageBox2d_Draw_maybe
//   [x] 0x52ac48  CFlashMessageBox2d_Save
//   [x] 0x52ac50  CFlashMessageBox2d_Load
//   [x] 0x52ace0  CFlashMessageBox2d_MessageProc
//   [x] 0x52ad38  CFlashMessageBox2d_PostLoad
//   [x] 0x52ae58  CFlashMessageBox2d_RecursiveRegistration
//   [x] 0x52af20  CFlashMessageBox2d_Destroy
//   [x] 0x52af80  CFlashMessageBox2d_CreateArray
//   [x] 0x52b058  CFlashMessageBox2d_Create
//   [x] 0x52b0b8  CFlashMessageBox2d_SetLocText_maybe  (no caller: only its OPD)
//   [x] 0x52b148  CFlashMessageBox2d_StateWaitAnswer_maybe
//   [x] 0x52b678  CFlashMessageBox2d_ShowMessageModal_maybe
//   [x] 0x52ba30  CFlashMessageBox2d_SetText_maybe
//   [x] 0x52bde0  CFlashMessageBox2d_vf7C
//   [x] 0x52c010  CFlashMessageBox2d_ShowMessage_maybe
//   [x] 0x52c398  CFlashMessageBox2d_ProcessRequest_maybe
//
//   [x] 0x9c8530  CFlashMessageBox2d_vf60  [inline]
//   [x] 0x9c8538  KBaseE8D_vf7C  [inline]
//   [x] 0x9c8540  KBaseE8D_vf80  [inline]
//   [x] 0x9c8548  KBaseE8D_vf8C  [inline]
//   [x] 0x9c8550  CFlashMessageBox2d_GetClassType  [inline]
//   [x] 0x9c8558  CFlashMessageBox2d_GetClassID  [inline]
//   [x] 0x9c8560  CFlashMessageBox2d_vf84  [inline]
//   [x] 0x9c8568  CFlashMessageBox2d_vf88  [inline]
//   [x] 0x9c8588  CFlashMessageBox2d_vf8C  [inline]
//   [x] 0x9c85d0  CFlashMessageBox2d_IsKindOfClass  [inline]
//   [x] 0x9c85f8  CFlashMessageBox2d_Destructor  [inline]
//   [x] 0x9c8670  CFlashMessageBox2d_DeletingDestructor  [inline]
#include "k2000/graphical/ui/CFlashMessageBox2d.h"

#include <cfloat>
#include <cstddef>
#include <cstring>

#include "Spyro2008/logic/CKS08GameManager.h"
#include "crt/ppc_ops.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/core/Stub.h"
#include "k2000/graphical/ui/CKFlashManager.h"
#include "k2000/graphical/ui/CKFlashMessageOut.h"
#include "k2000/graphical/ui/CKFlashUI.h"
#include "k2000/graphical/ui/CManager2d.h"
#include "k2000/graphical/ui/CText2d.h"
#include "k2000/input/CKComboManager.h"
#include "k2000/input/KeyboardDevice.h"
#include "k2000/input/MouseDevice.h"
#include "k2000/input/PS3PadDevice.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKInterfaceButton.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/logic/ui/CKLocText.h"
#include "k2000/logic/ui/CKMenuMessageBox.h"
#include "k2000/logic/ui/CKTrcText.h"
#include "k2000/logic/ui/CLocManager.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/managers/CKInput.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/CKInterfaceButtonBase.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Wcs.h"
#include "k2000/render/CRenderer.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"
#include "k2000/ui/IKNode2d.h"

class CKGameLoop;

namespace {

// 0x00acb320: the empty string ShowMessage*Loc and SetText use without a text.
const uint16_t kEmptyText[1] = {0};

// ---- callees in other units, not ported there yet (file-local copies named after the originals) ----

// 0x00035d28 LocString_GetText (CKLocText.h) and 0x00037028 CLocManager::GetText are the real ports now.

// 0x001065e8 CKInput_ClearAllStates_maybe is CKInput::ClearAllStates now.

// Local copy of 0x000687a8 Draw2d_FullScreenColorQuad_maybe (misc/MessageBox.cpp): DrawScreenColorQuad with
// the blend 0x00c297ec+4 / 0x00c297fc+4 (5 SRCALPHA / 6 INVSRCALPHA), `color`, the shared white centre
// colour (0x00c50dfc, as CColorizedScreenFx_Render), no raster.
void Draw2d_FullScreenColorQuad(const uint8_t* color) {
    static const uint8_t kWhite[4] = {0xff, 0xff, 0xff, 0xff};
    DrawScreenColorQuad(0.0f, 0.0f, 0, 5, 6, color, kWhite, nullptr);
}

// 0x0001e418 KStub_Return1_1e418: the game loop's modal frame (engine +0x34). XXL2's ModalPromptMessage
// calls CKGameLoop::ModalLoop here, which runs a frame; DotD's is a stub that returns 1.
int32_t KStub_Return1_1e418(CKGameLoop* /*loop*/) { return 1; }

// vt+0x320 0x004f8b50 CKS08GameManager_vf320: the two CKSrvInput input blocks' vt+0x58 with the real dt,
// then a per-player slot for players 0 and 1 (CKS08GameManager_3.cpp).
void CKS08GameManager_Vf320(IKSerializable* manager) {
    static_cast<CKS08GameManager*>(manager)->Vf320();
}

// ---- CKMenuMessageBox's code the box calls (logic/ui/CKMenuMessageBox.cpp, not ported there yet) ----

float MenuTimer(const CKMenuMessageBox* menu) { return menu->m_fTimer; }
void SetMenuTimer(CKMenuMessageBox* menu, float timer) { menu->m_fTimer = timer; }

CKInterfaceButtonBase* MenuButton(CKMenuMessageBox* menu, uint32_t i) {
    return i < menu->m_apButtons.m_ui32NbUsedElt ? static_cast<CKInterfaceButtonBase*>(menu->m_apButtons.m_pBlock[i])
                                                 : nullptr;
}

// The skip flag of a button (bit 4 of +0x08): cleared, then set when `skip`.
// BUG(original): a missing button (fewer than three) is a null pointer here and the PS3 writes address 8.
void SetButtonSkip(CKInterfaceButtonBase* button, bool skip) {
    uint8_t flags = static_cast<uint8_t>(button->m_baFlags & ~CKInterfaceButtonBase::kFlagSkip);
    if (skip) flags = static_cast<uint8_t>(flags | CKInterfaceButtonBase::kFlagSkip);
    button->m_baFlags = flags;
}

// 0x0052c800 CKMenuMessageBox_UpdateTimer_maybe: the timer (+0xe0) counted down by the unscaled dt, or the
// timer flag (bit 4 of +0x04) cleared once it ran out; +0xd8 = `blockAnswer`; while a layout with buttons is
// shown, the game manager's vt+0x320 and the menu's update phase (vt+0xd8(0, 0)).
void CKMenuMessageBox_UpdateTimer(CKMenuMessageBox* menu, uint8_t blockAnswer) {
    const float timer = MenuTimer(menu);
    if (timer <= 0.0f) {
        menu->m_ui32Flags &= ~0x10u;
    } else {
        SetMenuTimer(menu, timer - g_pEngine->m_timeManager->m_pTime->m_afDeltaTime[IKTime::FIXED_GAME_TIME]);
    }
    menu->m_bBlockAnswer = blockAnswer;
    if (static_cast<uint32_t>(menu->m_iUnkd4 + 1) > 1u) {
        CKS08GameManager_Vf320(menu->m_pGameManager);
        menu->HandleStatePhase(0, 0);
    }
}

// 0x0052cb88 CKMenuMessageBox_CallOwnerObjects2A8And2ACVf84_IfActive_maybe: while a layout with buttons is
// shown, the game manager's two pointer billboards (+0x2a8, +0x2ac) drawn (vt+0x84).
void CKMenuMessageBox_CallOwnerObjects2A8And2ACVf84_IfActive(CKMenuMessageBox* menu, IKTime* time) {
    if (static_cast<uint32_t>(menu->m_iUnkd4 + 1) <= 1u) return;
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(menu->m_pGameManager);
    static_cast<IKNode2d*>(manager->m_unk2A8[0])->Render(time);
    static_cast<IKNode2d*>(manager->m_unk2A8[1])->Render(time);
}

// 0x0052ccb8 CKMenuMessageBox_Show_maybe: the interface shown (kNeverRender cleared), the menu reset (vt+0x9c)
// and opened (vt+0x50); with `timer` the timer flag set and the timer (+0xe0) from +0xdc, else both cleared;
// +0x61 = 1.
void CKMenuMessageBox_Show(CKMenuMessageBox* menu, uint8_t timer) {
    if (menu->Vf60() != nullptr) {
        static_cast<CKFlashUI*>(menu->Vf60())->HideInterfaceHierarchy(0);
        CKFlashUI* ui = static_cast<CKFlashUI*>(menu->Vf60());
        ui->m_baFlags &= ~static_cast<uint32_t>(CKFlashUI::kNeverRender);
    }
    menu->Reset();  // vt+0x9c
    menu->Open();   // vt+0x50
    if (timer != 0) {
        menu->m_ui32Flags = (menu->m_ui32Flags & ~0x10u) | 0x10u;
        SetMenuTimer(menu, menu->m_fUnkdc);
    } else {
        menu->m_ui32Flags &= ~0x10u;
        menu->m_fTimer = 0.0f;
    }
    menu->m_unk60[1] = 1;
}

// 0x0052ce60 CKMenuMessageBox_SetText_maybe: the text into the text element (+0x98, a CText2d: vt+0x8c), and
// the three button labels (each button's +0x34 CText2d) from the TRC texts by combine type: 2 OK, 3 Cancel
// (types 0-2: OK/Cancel/Cancel), 0 Yes, 1 No (3 and 5: Yes/No/Cancel), 5 Retry (4: Retry/Cancel/Cancel),
// 4 Abort, 5 Retry, 6 Ignore (6). (Label meanings from the XXL2 combine types _maybe.)
void CKMenuMessageBox_SetText(CKMenuMessageBox* menu, const uint16_t* text, uint32_t type) {
    IKSerializable* element = menu->m_aWidgetSlots[0].m_pElement;
    if (element != nullptr) static_cast<CText2d*>(static_cast<IKNode2d*>(element))->SetTextWide(text);
    // The PS3 code is three chained switches (jump table 0x52cedc, then the bit masks 0x17 / 0x28 / 0x40, then
    // the signed 0..5 / 6 test); for every type each label is written once, in label order, as here.
    // BUG(original): for a type above 6 the three labels are uninitialised stack buffers (here: empty).
    uint16_t labels[3][0x200] = {};
    uint32_t ids[3];
    bool known = true;
    switch (type) {
    case CFlashMessageBox2d::MSGBOX_COMBINE_NO_BUTTON:
    case CFlashMessageBox2d::MSGBOX_COMBINE_OK:
    case CFlashMessageBox2d::MSGBOX_COMBINE_OK_CANCEL:
        ids[0] = 2;
        ids[1] = 3;
        ids[2] = 3;
        break;
    case CFlashMessageBox2d::MSGBOX_COMBINE_YES_NO:
    case CFlashMessageBox2d::MSGBOX_COMBINE_YES_NO_CANCEL:
        ids[0] = 0;
        ids[1] = 1;
        ids[2] = 3;
        break;
    case CFlashMessageBox2d::MSGBOX_COMBINE_RETRY_CANCEL:
        ids[0] = 5;
        ids[1] = 3;
        ids[2] = 3;
        break;
    case CFlashMessageBox2d::MSGBOX_COMBINE_ABORT_RETRY_IGNORE:
        ids[0] = 4;
        ids[1] = 5;
        ids[2] = 6;
        break;
    default:
        known = false;
        break;
    }
    if (known) {
        for (uint32_t i = 0; i < 3; ++i) {
            WStr_CopyReturnEnd(labels[i], ::LocString_GetText(g_pEngine->m_locManager->GetText(ids[i])));
        }
    }
    // Each button's label (+0x34, a CText2d) gets its text (vt+0x8c), the count re-read for each.
    for (uint32_t i = 0; i < 3; ++i) {
        if (menu->m_apButtons.m_ui32NbUsedElt <= i) continue;
        CKInterfaceButton* button = static_cast<CKInterfaceButton*>(menu->m_apButtons.m_pBlock[i]);
        if (button == nullptr || button->m_unk34 == nullptr) continue;
        static_cast<CText2d*>(static_cast<IKNode2d*>(button->m_unk34))->SetTextWide(labels[i]);
    }
}

// 0x0052d3e0 CFlashMessageBox2d_HideMessage_maybe is CKMenuMessageBox::HideMessage (ported there).

// 0x0052d6d0 CKMenuMessageBox_Hide_maybe: the menu's leave phase (vt+0xd8(2, 0)), the interface hidden,
// kNeverRender set and the hot spots hidden, no layout (+0xd4 = -1), the menu closed (vt+0x5c) and its slots
// cleared (vt+0xa8).
void CKMenuMessageBox_Hide(CKMenuMessageBox* menu) {
    menu->HandleStatePhase(2, 0);
    if (menu->Vf60() != nullptr) static_cast<CKFlashUI*>(menu->Vf60())->HideInterfaceHierarchy(1);
    if (menu->Vf60() != nullptr) {
        CKFlashUI* ui = static_cast<CKFlashUI*>(menu->Vf60());
        ui->m_baFlags = (ui->m_baFlags & ~static_cast<uint32_t>(CKFlashUI::kNeverRender)) | CKFlashUI::kNeverRender;
        ui->HideAllHotSpotHierarchy();
    }
    menu->m_iUnkd4 = -1;
    menu->Close();  // vt+0x5c
    menu->VfA8();
}

// 0x0052d858 CKMenuMessageBox_SetButtonLayout_maybe: unless the layout is already `type` (+0xd4), the layout's
// flash message posted (vt+0xc0 entry 2 none, 3 one button, 4 two, 5 three), the unused buttons skipped by
// the navigation and hidden, the used ones shown; the focused button follows `button` (the default
// EMsgBoxButton); then each active player's selection (+0x6c, +0x6d) moved to it (SetItemState 0 on the old,
// 2 on the new). Types above 6 only move the selections (to 0).
void CKMenuMessageBox_SetButtonLayout(CKMenuMessageBox* menu, uint32_t type, int32_t button) {
    if (menu->m_iUnkd4 == static_cast<int32_t>(type)) return;
    uint8_t selection = 0;
    switch (type) {
    case CFlashMessageBox2d::MSGBOX_COMBINE_NO_BUTTON:
    case CFlashMessageBox2d::MSGBOX_COMBINE_OK: {
        const uint32_t message = type == CFlashMessageBox2d::MSGBOX_COMBINE_NO_BUTTON ? 2u : 3u;
        if (menu->VfC0()[message] != nullptr) static_cast<CKFlashMessageOut*>(menu->VfC0()[message])->PostFlashMessage();
        SetButtonSkip(MenuButton(menu, 0), false);
        SetButtonSkip(MenuButton(menu, 1), true);
        SetButtonSkip(MenuButton(menu, 2), true);
        if (type == CFlashMessageBox2d::MSGBOX_COMBINE_NO_BUTTON) {
            MenuButton(menu, 0)->Hide();  // vt+0x70
        } else {
            MenuButton(menu, 0)->Show();  // vt+0x6c
        }
        MenuButton(menu, 1)->Hide();
        MenuButton(menu, 2)->Hide();
        break;
    }
    case CFlashMessageBox2d::MSGBOX_COMBINE_OK_CANCEL:
    case CFlashMessageBox2d::MSGBOX_COMBINE_YES_NO:
    case CFlashMessageBox2d::MSGBOX_COMBINE_RETRY_CANCEL:
        if (menu->VfC0()[4] != nullptr) static_cast<CKFlashMessageOut*>(menu->VfC0()[4])->PostFlashMessage();
        selection = (button == CFlashMessageBox2d::MSGBOX_BUTTON_CANCEL || button == CFlashMessageBox2d::MSGBOX_BUTTON_NO) ? 1 : 0;
        SetButtonSkip(MenuButton(menu, 0), false);
        SetButtonSkip(MenuButton(menu, 1), false);
        SetButtonSkip(MenuButton(menu, 2), true);
        MenuButton(menu, 0)->Show();
        MenuButton(menu, 1)->Show();
        MenuButton(menu, 2)->Hide();
        break;
    case CFlashMessageBox2d::MSGBOX_COMBINE_YES_NO_CANCEL:
    case CFlashMessageBox2d::MSGBOX_COMBINE_ABORT_RETRY_IGNORE:
        if (menu->VfC0()[5] != nullptr) static_cast<CKFlashMessageOut*>(menu->VfC0()[5])->PostFlashMessage();
        if (button == CFlashMessageBox2d::MSGBOX_BUTTON_RETRY || button == CFlashMessageBox2d::MSGBOX_BUTTON_NO) {
            selection = 1;
        } else if (button == CFlashMessageBox2d::MSGBOX_BUTTON_CANCEL || button == CFlashMessageBox2d::MSGBOX_BUTTON_IGNORE) {
            selection = 2;
        }
        SetButtonSkip(MenuButton(menu, 0), false);
        SetButtonSkip(MenuButton(menu, 1), false);
        SetButtonSkip(MenuButton(menu, 2), false);
        MenuButton(menu, 0)->Show();
        MenuButton(menu, 1)->Show();
        MenuButton(menu, 2)->Show();
        break;
    default:
        break;
    }
    CDefaultGameManager* manager = static_cast<CDefaultGameManager*>(menu->m_pGameManager);
    if (manager->IsPlayerActive(0) != 0) {  // vt+0x180
        menu->SetItemState(menu->m_aui8FocusedItem[0], 0, 0);
        menu->m_aui8FocusedItem[0] = selection;
        menu->SetItemState(selection, 2, 0);
    }
    if (manager->IsPlayerActive(1) != 0) {
        menu->SetItemState(menu->m_aui8FocusedItem[1], 0, 0);
        menu->m_aui8FocusedItem[1] = selection;
        menu->SetItemState(selection, 2, 0);
    }
    menu->m_iUnkd4 = static_cast<int32_t>(type);
}

}  // namespace

// ---- the state machine (inlined by the PS3 code at every use) ----
void CFlashMessageBox2d::StateMachine::StartIfIdle() {
    if (m_ui8Current != 0xff) return;
    m_ui8Current = 0;
    Call(0, 1, 0xff);
}

void CFlashMessageBox2d::StateMachine::Switch(uint8_t next) {
    uint8_t previous = m_ui8Current;
    if (previous != 0xff) {
        Call(previous, 2, next);
        previous = m_ui8Current;
    }
    m_ui8Current = next;
    if (next != 0xff) Call(next, 1, previous);
}

void CFlashMessageBox2d::StateMachine::Tick() {
    const uint8_t current = m_ui8Current;
    if (current == 0xff) return;
    const uint8_t next = Call(current, 0, current);
    if (next == m_ui8Current) return;
    Switch(next);
}

// Inlined in 0x0052b058 CFlashMessageBox2d_Create, the stores in its order.
CFlashMessageBox2d::CFlashMessageBox2d() {
    m_stateMachine.m_pOwner = nullptr;
    m_stateMachine.m_ui8Current = 0xff;
    m_stateMachine.m_pTable = nullptr;
    m_stateMachine.m_ui8Count = 0;
    m_pMenu = nullptr;
    m_bReady = 0;
    m_i32ShowCount = 0;
}

// 0x0052a218 CFlashMessageBox2d_vf6C (XXL2 IsMessageBoxShown): the interface exists and is not kNeverRender.
int32_t CFlashMessageBox2d::IsMessageBoxShown() {
    CKMenuMessageBox* menu = m_pMenu;
    if (menu == nullptr || menu->Vf60() == nullptr) return 0;
    const uint32_t flags = static_cast<CKFlashUI*>(m_pMenu->Vf60())->m_baFlags;
    return static_cast<int32_t>(((flags >> 5) & 1u) ^ 1u);
}

// 0x0052a2e0 CFlashMessageBox2d_ShowMessageLoc_maybe
int32_t CFlashMessageBox2d::ShowMessageLoc(CKLocText* text, int32_t type, int32_t button, InterruptFn interrupt,
                                           float unk, float timeout) {
    const uint16_t* wide = text != nullptr ? ::LocString_GetText(text) : kEmptyText;
    return ShowMessage(wide, type, button, interrupt, unk, timeout, 0);  // vt+0x5c
}

// 0x0052a3b8 CFlashMessageBox2d_ShowMessageModalLoc_maybe
int32_t CFlashMessageBox2d::ShowMessageModalLoc(CKLocText* text, int32_t type, int32_t button, InterruptFn interrupt,
                                                float unk, float timeout) {
    const uint16_t* wide = text != nullptr ? ::LocString_GetText(text) : kEmptyText;
    return ShowMessageModal(wide, type, button, interrupt, unk, timeout, 0);  // vt+0x54
}

// 0x0052a490 CFlashMessageBox2d_SetBoxText_maybe (no caller in the binary)
void CFlashMessageBox2d::SetBoxText(const uint16_t* text, int32_t /*unused*/, uint32_t type) {
    CKMenuMessageBox_SetText(m_pMenu, text, type);  // 0x52ce60
}

// 0x0052a4c0 CFlashMessageBox2d_SetButtonLayout_maybe (no caller in the binary)
void CFlashMessageBox2d::SetButtonLayout(uint32_t type, int32_t button) {
    CKMenuMessageBox_SetButtonLayout(m_pMenu, type, button);  // 0x52d858
}

// 0x0052a600 CFlashMessageBox2d_Show_maybe (XXL2 StartMessageBox; no caller in the binary)
void CFlashMessageBox2d::StartMessageBox(uint8_t timer) {
    g_pEngine->m_input->SetMappingEnabled(1, 1);  // 0x107618
    g_pEngine->m_flashManager->m_bLockInputUpdate = 1;
    if (m_pMenu != nullptr) CKMenuMessageBox_Show(m_pMenu, timer);  // 0x52ccb8
}

// 0x0052b0b8 CFlashMessageBox2d_SetLocText_maybe (no caller in the binary)
void CFlashMessageBox2d::SetLocText(CKLocText* text, int32_t /*unused*/, uint32_t type) {
    static const uint16_t kNoTrc[] = {'-', 'N', 'O', ' ', 'T', 'R', 'C', ' ', 'D', 'E', 'F', 'I', 'N', 'E', 'D', '-', 0};  // 0x00c2964c
    if (text != nullptr) {
        CKMenuMessageBox_SetText(m_pMenu, ::LocString_GetText(text), type);  // 0x35d28, 0x52ce60
        return;
    }
    CKMenuMessageBox_SetText(m_pMenu, kNoTrc, type);
}

// 0x0052a4e8 CFlashMessageBox2d_Close_maybe (XXL2 StopMessageBox): with a CKS08GameManager (0x3b0c) its two
// pointer billboards disabled (+0x2ac, then +0x2a8: vt+0x68); the menu hidden; the Flash input unlocked;
// with `resetFade` the darkening cleared (alpha 0, start time = the word at 0x00c4acb8 + 0x28: FLT_MAX).
void CFlashMessageBox2d::StopMessageBox(int32_t resetFade) {
    CDefaultGameManager* manager = g_pEngine->m_gameManager;
    if (static_cast<uint8_t>(manager->IsKindOfClass(0x3b0c)) != 0) {
        CKS08GameManager* game = static_cast<CKS08GameManager*>(manager);
        static_cast<IKNode2d*>(game->m_unk2A8[1])->Disable();
        static_cast<IKNode2d*>(game->m_unk2A8[0])->Disable();
    }
    if (m_pMenu != nullptr) CKMenuMessageBox_Hide(m_pMenu);
    g_pEngine->m_flashManager->m_bLockInputUpdate = 0;
    if (resetFade != 0) {
        m_fFadeAlpha = 0.0f;
        m_fFadeStartTime = FLT_MAX;  // TOC1 +0x7814 -> 0x00c4acb8, +0x28 (as PostLoad)
    }
}

// 0x0052a730 CFlashMessageBox2d_CloseMessage_maybe (XXL2 HideMessageBox)
void CFlashMessageBox2d::HideMessageBox() {
    if (m_pMenu != nullptr) m_pMenu->HideMessage();
    g_pEngine->m_flashManager->m_bLockInputUpdate = 0;
}

// 0x0052a778 CFlashMessageBox2d_ShowWidget_maybe (XXL2 ShowMessageBox): kNeverRender cleared, the Flash input
// locked to the box.
void CFlashMessageBox2d::ShowMessageBox() {
    CKMenuMessageBox* menu = m_pMenu;
    if (menu != nullptr && menu->Vf60() != nullptr) {
        CKFlashUI* ui = static_cast<CKFlashUI*>(m_pMenu->Vf60());
        ui->m_baFlags &= ~static_cast<uint32_t>(CKFlashUI::kNeverRender);
    }
    g_pEngine->m_flashManager->m_bLockInputUpdate = 1;
}

// 0x0052a8f0 CFlashMessageBox2d_Draw_maybe (XXL2 Render): while the interface is started and shown the screen
// darkening is held at 225 (it fades from 0.25 s after it was last held, at 900 per second of the system
// clock's dt, at most 1/60 s a frame); while it is above 0 the interface is updated, the darkening drawn,
// then the interface, the buttons (last first: vt+0x80), the text (vt+0x84) and the pointer billboards.
void CFlashMessageBox2d::Render(IKTime* time) {
    CKMenuMessageBox* menu = m_pMenu;
    if (menu == nullptr || menu->Vf60() == nullptr) return;
    GameEngineContext* engine = g_pEngine;
    IKTime* clock = engine->m_timeManager->m_pTime;
    CRenderer* renderer = engine->m_graphic->m_renderer;
    float dt = clock->m_afDeltaTime[IKTime::SYSTEM_TIME];
    const float now = clock->m_afCurrentTime[IKTime::SYSTEM_TIME];
    if (!(dt < 0x1.111112p-6f)) dt = 0x1.111112p-6f;  // TOC1 +0x7834 (bge: also a NaN dt)
    menu = m_pMenu;
    if ((static_cast<CKFlashUI*>(menu->m_pFlashUI)->m_baFlags & CKFlashUI::kStateMask) == 2 &&
        (static_cast<CKFlashUI*>(menu->Vf60())->m_baFlags & CKFlashUI::kNeverRender) == 0) {
        m_fFadeAlpha = 225.0f;           // TOC1 +0x7838
        m_fFadeStartTime = now + 0.25f;  // TOC1 +0x783c
    }
    if (!(m_fFadeAlpha > 0.0f)) return;  // TOC1 +0x77fc (ble: also a NaN alpha)
    static_cast<CKFlashUI*>(m_pMenu->Vf60())->Update(time);
    const uint8_t color[4] = {0, 0, 0, static_cast<uint8_t>(ppc::fctiwz(m_fFadeAlpha))};
    Draw2d_FullScreenColorQuad(color);
    if (m_fFadeStartTime <= now) {
        const float alpha = ppc::fmadds(dt, -900.0f, m_fFadeAlpha);  // TOC1 +0x7840
        m_fFadeAlpha = alpha < 0.0f ? 0.0f : alpha;
    }
    PushRenderStates(renderer);
    SetUIOverlayRenderStates();  // (engine +0x38)
    static_cast<CKFlashUI*>(m_pMenu->Vf60())->Render(time);
    menu = m_pMenu;
    uint32_t i = menu->m_apButtons.m_ui32NbUsedElt;
    while (i != 0) {
        --i;
        MenuButton(menu, i)->Vf80(time);
        menu = m_pMenu;
    }
    IKSerializable* element = menu->m_aWidgetSlots[0].m_pElement;
    if (element != nullptr) {
        static_cast<IKNode2d*>(element)->Render(time);  // vt+0x84
        menu = m_pMenu;
    }
    CKMenuMessageBox_CallOwnerObjects2A8And2ACVf84_IfActive(menu, time);
    PopRenderStates(renderer);
}

// 0x0052ac50 CFlashMessageBox2d_Load
int32_t CFlashMessageBox2d::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pMenu);
    return 1;
}

// 0x0052ace0 CFlashMessageBox2d_MessageProc: message 0x2301 (CKMenuMessageBox_vfE8: a button validated; the
// data is the item) selects the answer and clears the input states.
int32_t CFlashMessageBox2d::MessageProc(uint16_t message, void* data) {
    if (message != 0x2301) return 1;
    m_i32SelectedButton = static_cast<int32_t>(reinterpret_cast<uintptr_t>(data));
    g_pEngine->m_input->ClearAllStates();
    return 1;
}

// 0x0052ad38 CFlashMessageBox2d_PostLoad: the message box's interface hidden and its message cleared;
// the state machine (StateWaitAnswer on this) installed; ready.
int32_t CFlashMessageBox2d::PostLoad(int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    CKMenuMessageBox* menu = m_pMenu;
    if (menu != nullptr && menu->Vf60() != nullptr) {
        static_cast<CKFlashUI*>(menu->Vf60())->HideInterfaceHierarchy(1);
        menu->HideMessage();
        m_fFadeAlpha = 0.0f;
        m_fFadeStartTime = FLT_MAX;  // TOC1 +0x7814 -> 0x00c4acb8, +0x28: FLT_MAX statically (as CKSrvCamera reads it)
    }
    m_stateMachine.m_pOwner = this;
    StateHandler* table = static_cast<StateHandler*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(StateHandler))));
    m_stateMachine.m_pTable = table;
    table[0] = &CFlashMessageBox2d::StateWaitAnswer;  // TOC1 +0x7844 -> 0x00bd7bf0 (adjustment 0)
    m_stateMachine.m_ui8Count = 1;
    m_bReady = 1;
    return 1;
}

// 0x0052ae58 CFlashMessageBox2d_RecursiveRegistration: type 0 registers the box (the saving manager's vt+0x24),
// then the menu when it has an interface.
void CFlashMessageBox2d::RecursiveRegistration(int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return;
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
    CKMenuMessageBox* menu = m_pMenu;
    if (menu != nullptr && menu->m_pFlashUI != nullptr) menu->RecursiveRegistration(K_LEVEL_PLATEFORMS);
}

// 0x0052af20 CFlashMessageBox2d_Destroy
void CFlashMessageBox2d::Destroy() {
    m_pMenu = nullptr;
    m_bReady = 0;
    m_stateMachine.m_pOwner = nullptr;
    Mem_FreeAligned16(m_stateMachine.m_pTable);
    m_stateMachine.m_ui8Count = 0;
    m_stateMachine.m_ui8Current = 0xff;
    m_stateMachine.m_pTable = nullptr;
}

// 0x0052b148 CFlashMessageBox2d_StateWaitAnswer_maybe: the message state.
// Enter (1): the answer and the flags cleared, the clock and its start time taken, the input mapping 1 and
// the Flash input lock on, the menu shown with the text and the buttons. Every frame (0): the text and the
// buttons again, the interrupt callback and the timeout polled; leaves (0xff) on an answer. Leave (2): the
// box stopped when no message is left, the result from the answer and the combine type (XXL2's table); a
// CKS08GameManager also gets flag 0x20000 / 0x40000 / 0x80000 (+0x64) for answer 0 / 1 / 2.
uint8_t CFlashMessageBox2d::StateWaitAnswer(int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        const uint8_t timer = m_request.m_bTimer;
        m_i32SelectedButton = -1;
        m_request.m_pJobQueue = g_pEngine->m_jobQueue;
        IKTime* clock = g_pEngine->m_timeManager->m_pTime;
        m_request.m_bTimedOut = 0;
        m_request.m_pClock = clock;
        m_request.m_unk348 = 0;
        m_request.m_bInterrupted = 0;
        m_request.m_fStartTime = clock->m_afCurrentTime[IKTime::SYSTEM_TIME];
        g_pEngine->m_input->SetMappingEnabled(1, 1);
        g_pEngine->m_flashManager->m_bLockInputUpdate = static_cast<uint8_t>(phase);
        if (m_pMenu != nullptr) CKMenuMessageBox_Show(m_pMenu, timer);
        ShowMessageBox();  // vt+0x64
        CKMenuMessageBox_SetText(m_pMenu, m_request.m_wszText, static_cast<uint32_t>(m_request.m_eCombineType));
        CKMenuMessageBox_SetButtonLayout(m_pMenu, static_cast<uint32_t>(m_request.m_eCombineType), m_request.m_eDefaultButton);
        if (m_pMenu != nullptr) CKMenuMessageBox_UpdateTimer(m_pMenu, 1);
        ++m_i32ShowCount;
    } else if (phase == 2) {
        if (--m_i32ShowCount == 0) StopMessageBox(0);  // vt+0x70
        const uint8_t timedOut = m_request.m_bTimedOut;
        const int32_t answer = m_i32SelectedButton;
        m_i32SelectedButton = -1;
        if (timedOut != 0) {
            m_request.m_eResult = kMsgBoxTimeout;
            return 0xff;
        }
        if (m_request.m_bInterrupted != 0) {
            m_request.m_eResult = kMsgBoxInterrupt;
            return 0xff;
        }
        CDefaultGameManager* manager = g_pEngine->m_gameManager;
        if (static_cast<uint8_t>(manager->IsKindOfClass(0x3b0c)) != 0) {
            if (answer == 1) {
                manager->m_flags64 = (manager->m_flags64 & ~0x40000u) | 0x40000u;
            } else if (answer == 2) {
                manager->m_flags64 = (manager->m_flags64 & ~0x80000u) | 0x80000u;
            } else if (answer == 0) {
                manager->m_flags64 = (manager->m_flags64 & ~0x20000u) | 0x20000u;
            }
        }
        // The answer table (jump table 0x52b554): the selected item -> EMsgBoxButton per combine type.
        int32_t result;
        switch (static_cast<uint32_t>(m_request.m_eCombineType)) {
        case MSGBOX_COMBINE_OK:
            result = MSGBOX_BUTTON_OK;
            break;
        case MSGBOX_COMBINE_OK_CANCEL:
            result = answer == 0 ? MSGBOX_BUTTON_OK : MSGBOX_BUTTON_CANCEL;
            break;
        case MSGBOX_COMBINE_YES_NO:
            result = answer == 0 ? MSGBOX_BUTTON_YES : MSGBOX_BUTTON_NO;
            break;
        case MSGBOX_COMBINE_RETRY_CANCEL:
            result = answer == 0 ? MSGBOX_BUTTON_RETRY : MSGBOX_BUTTON_CANCEL;
            break;
        case MSGBOX_COMBINE_YES_NO_CANCEL:
            result = answer == 0 ? MSGBOX_BUTTON_YES : answer == 1 ? MSGBOX_BUTTON_NO : MSGBOX_BUTTON_CANCEL;
            break;
        case MSGBOX_COMBINE_ABORT_RETRY_IGNORE:
            result = answer == 0 ? MSGBOX_BUTTON_ABORT : answer == 1 ? MSGBOX_BUTTON_RETRY : MSGBOX_BUTTON_IGNORE;
            break;
        default:  // MSGBOX_COMBINE_NO_BUTTON and the types above 6
            result = kMsgBoxPending;
            break;
        }
        m_request.m_eResult = result;
        return 0xff;
    } else if (phase == 0) {
        ShowMessageBox();  // vt+0x64
        CKMenuMessageBox_SetText(m_pMenu, m_request.m_wszText, static_cast<uint32_t>(m_request.m_eCombineType));
        CKMenuMessageBox_SetButtonLayout(m_pMenu, static_cast<uint32_t>(m_request.m_eCombineType), m_request.m_eDefaultButton);
        m_unk0c = 0;
        if (m_pMenu != nullptr) CKMenuMessageBox_UpdateTimer(m_pMenu, 0);
        if (m_request.m_pfnInterrupt != nullptr && m_request.m_pfnInterrupt() != 0) m_request.m_bInterrupted = 1;
        const float timeout = m_request.m_fTimeout;
        if (timeout != -1.0f) {  // TOC1 +0x7858 (bne: also a NaN timeout)
            if (m_request.m_pClock->m_afCurrentTime[IKTime::SYSTEM_TIME] - m_request.m_fStartTime >= timeout) {
                m_request.m_bInterrupted = 1;
                m_request.m_bTimedOut = 1;
                return 0xff;
            }
        }
        if (m_request.m_bInterrupted != 0 || m_i32SelectedButton != -1) return 0xff;
    }
    m_request.m_eResult = kMsgBoxPending;
    return 0;
}

// 0x0052b678 CFlashMessageBox2d_ShowMessageModal_maybe: the message set (no sender), then the game loop's
// modal frame and one frame of the message until it is answered.
// BUG(original): DotD's modal frame (0x1e418) is a stub that returns 1, so nothing runs between the frames
// of the message (no input, no clock): it only ends through the interrupt callback, or an answer or a
// timeout already there. CKS08GameManager_HandleCinematicAndUIMessage_maybe's calls (no callback, no timeout) never
// return on the PS3.
int32_t CFlashMessageBox2d::ShowMessageModal(const uint16_t* text, int32_t type, int32_t button, InterruptFn interrupt,
                                             float unk, float timeout, uint8_t timer) {
    m_request.m_pSender = nullptr;
    WStr_CopyReturnEnd(m_request.m_wszText, text);
    m_request.m_fUnk334 = unk;
    m_request.m_eCombineType = type;
    m_request.m_eDefaultButton = button;
    m_request.m_pfnInterrupt = interrupt;
    m_request.m_fTimeout = timeout;
    m_request.m_bTimer = timer;
    do {
        KStub_Return1_1e418(g_pEngine->m_gameLoop);
        m_stateMachine.StartIfIdle();
        m_stateMachine.Tick();
    } while (m_request.m_eResult == kMsgBoxPending);
    return m_request.m_eResult;
}

// 0x0052ba30 CFlashMessageBox2d_SetText_maybe: the same text restarts the timeout of a running message
// (returns 1 when no message runs or it has no timeout); another text starts a message when none runs.
// Either way, a running message gets one frame. Returns 0 then.
// BUG(original): another text while a message runs is not copied (the frame runs with the old one); and
// with no message started yet the clock pointer (+0x36c) is uninitialised.
uint8_t CFlashMessageBox2d::SetMessageText(CKLocText* text) {
    const uint16_t* wide = text != nullptr ? ::LocString_GetText(text) : kEmptyText;
    if (Wcs_Compare(wide, m_request.m_wszText) == 0) {
        if (m_stateMachine.m_ui8Current == 0xff) return 1;
        if (m_request.m_fTimeout == -1.0f) return 1;  // TOC1 +0x7858
        m_request.m_fStartTime = m_request.m_pClock->m_afCurrentTime[IKTime::SYSTEM_TIME];
        m_stateMachine.Tick();
        return 0;
    }
    if (m_stateMachine.m_ui8Current == 0xff) {
        WStr_CopyReturnEnd(m_request.m_wszText, wide);
        m_request.m_fStartTime = m_request.m_pClock->m_afCurrentTime[IKTime::SYSTEM_TIME];
        m_stateMachine.Switch(0);
        return 0;
    }
    m_stateMachine.Tick();
    return 0;
}

// 0x0052bde0 CFlashMessageBox2d_vf7C: one frame of the running message; 1 when none runs.
uint8_t CFlashMessageBox2d::UpdateMessage() {
    if (m_stateMachine.m_ui8Current == 0xff) return 1;
    m_stateMachine.Tick();
    return 0;
}

// 0x0052c010 CFlashMessageBox2d_ShowMessage_maybe: the message set (the sender, its flag and the result are
// left as they are), started when none runs, one frame; returns the result.
int32_t CFlashMessageBox2d::ShowMessage(const uint16_t* text, int32_t type, int32_t button, InterruptFn interrupt,
                                        float unk, float timeout, uint8_t timer) {
    WStr_CopyReturnEnd(m_request.m_wszText, text);
    m_request.m_eCombineType = type;
    m_request.m_fUnk334 = unk;
    m_request.m_eDefaultButton = button;
    m_request.m_pfnInterrupt = interrupt;
    m_request.m_fTimeout = timeout;
    m_request.m_bTimer = timer;
    m_stateMachine.StartIfIdle();
    m_stateMachine.Tick();
    return m_request.m_eResult;
}

// 0x0052c398 CFlashMessageBox2d_ProcessRequest_maybe: the queue entry copied in, started when no message runs,
// one frame, copied back; returns its result (MessageBox_ProcessQueue_maybe).
int32_t CFlashMessageBox2d::ProcessRequest(SFlashMessageRequest* request) {
    std::memcpy(&m_request, request, sizeof(SFlashMessageRequest));
    m_stateMachine.StartIfIdle();
    m_stateMachine.Tick();
    std::memcpy(request, &m_request, sizeof(SFlashMessageRequest));
    return request->m_eResult;
}

// 0x009c8588 CFlashMessageBox2d_vf8C: the menu's interface (vt+0x60). (Out of line here: the header does not
// include CKMenuMessageBox.h.)
IKSerializable* CFlashMessageBox2d::GetFlashInterface() { return m_pMenu->Vf60(); }
