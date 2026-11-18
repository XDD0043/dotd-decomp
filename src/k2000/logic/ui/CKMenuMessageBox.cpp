// CKMenuMessageBox.cpp - reconstructed original translation unit 0x52c700-0x52e458 (GAME_TOC1, main_toc1), 27 functions, 25 live.
// Primary class: CKMenuMessageBox  key 0x734c  category Logic  size 0xe4  vtable 0xb2ba68
// Other owners: CFlashMessageBox2d (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x52c700  CKMenuMessageBox_Delete
//   [ ] 0x52c750  CKMenuMessageBox_Construct  [dead]
//   [x] 0x52c800  CKMenuMessageBox_UpdateTimer_maybe  (k2000/graphical/ui/CFlashMessageBox2d.cpp, next to its caller)
//   [ ] 0x52c8e8  RegisterCKMenuMessageBoxClass
//   [ ] 0x52c960  _GLOBAL__I_52c960
//   [x] 0x52c970  CKMenuMessageBox_vf58  (only calls 0x513700, CKMenuBase114c::Resume: inherited)
//   [x] 0x52c998  CKMenuMessageBox_vf54  (only calls 0x5139a0, CKMenuBase114c::Pause: inherited)
//   [x] 0x52c9c0  CKMenuMessageBox_Close
//   [x] 0x52c9e8  CKMenuMessageBox_Load
//   [ ] 0x52ca70  CKMenuMessageBox_Save
//   [x] 0x52ca98  CKMenuMessageBox_RecursiveRegistration  (only calls 0x513c38 (KBase730C.cpp, package P13): inherited)
//   [x] 0x52cac0  CKMenuMessageBox_Destroy  (inherited: CKMenuBase_114c_maybe_Destroy)
//   [x] 0x52cae8  CKMenuMessageBox_DeleteArray
//   [x] 0x52cb88  CKMenuMessageBox_CallOwnerObjects2A8And2ACVf84_IfActive_maybe
//   [x] 0x52cc28  CKMenuMessageBox_vfE8
//   [x] 0x52ccb8  CKMenuMessageBox_Show_maybe
//   [x] 0x52ce60  CKMenuMessageBox_SetText_maybe
//   [x] 0x52d1f8  CKMenuMessageBox_Open
//   [ ] 0x52d330  CKMenuMessageBox_Construct_2  [dead]
//   [x] 0x52d3e0  CFlashMessageBox2d_HideMessage_maybe
//   [x] 0x52d490  CKMenuMessageBox_CreateArray
//   [x] 0x52d5e0  CKMenuMessageBox_Create
//   [x] 0x52d6d0  CKMenuMessageBox_Hide_maybe
//   [x] 0x52d858  CKMenuMessageBox_SetButtonLayout_maybe
//   [x] 0x52e0b0  CKMenuMessageBox_Destructor  (~CKMenuBase114c inlined (the same frees, checked against 0x556498))
//   [x] 0x52e1e8  CKMenuMessageBox_Destructor_2  (the same as 0x52e0b0 CKMenuMessageBox_Destructor)
//   [x] 0x52e320  CKMenuMessageBox_DeletingDestructor  (the deleting form of 0x52e0b0)
//
//   [x] 0x9c86b8  CKMenuMessageBox_IsKindOfClass  [inline]
//   [x] 0x9c86f0  CKMenuMessageBox_GetClassType  [inline]
//   [x] 0x9c86f8  CKMenuMessageBox_GetClassID  [inline]
//   [x] 0x9c8700  CKMenuMessageBox_vfB8  [inline]
//   [x] 0x9c8708  CKMenuMessageBox_vfE0  [inline]
//   [x] 0x9c8710  CKMenuMessageBox_GetWidgetSlotCount  [inline]
//   [x] 0x9c8718  CKMenuMessageBox_GetWidgetSlots  [inline]
//   [x] 0x9c8728  CKMenuMessageBox_vfC4  [inline]
//   [x] 0x9c8730  CKMenuMessageBox_vfC8  [inline]
//   [x] 0x9c8740  CKMenuMessageBox_vfCC  [inline]
//   [x] 0x9c8750  CKMenuMessageBox_vfBC  [inline]
//   [x] 0x9c8758  CKMenuMessageBox_vfC0  [inline]
#include "k2000/logic/ui/CKMenuMessageBox.h"

#include "k2000/graphical/ui/CKFlashUI.h"
#include "k2000/graphical/ui/CManager2d.h"
#include "k2000/graphical/ui/CMenuManager.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKInterfaceButton.h"
#include "k2000/misc/Engine.h"

// 0x0052c9e8 CKMenuMessageBox_Load: no type test of its own, so its fields are read whatever the type.
int32_t CKMenuMessageBox::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    ReadF32LE(file, &m_fUnkdc);
    return 1;
}

// 0x0052d1f8 CKMenuMessageBox_Open (from the assembly): the menus' Open (KBase730C_Open 0x514a00), then, when the box has
// three buttons, each one's text suppressed again (bit 0 of +0x30, which the buttons' Open cleared: the box sets the
// texts itself, SetText_maybe); then +0x6d = 0, answers blocked for this frame (+0xd8 = 1), +0x6c = 0. BUG(original): the
// count is read again before the second and third stores, which would write address 0x30 with fewer buttons (never: the
// three were tested first).
void CKMenuMessageBox::Open() {
    CKMenuBase114c::Open();
    const uint32_t count = m_apButtons.m_ui32NbUsedElt;
    IKSerializable** const buttons = m_apButtons.m_pBlock;
    if (count != 0 && buttons[0] != nullptr && count > 1 && buttons[1] != nullptr && count > 2 && buttons[2] != nullptr) {
        for (uint32_t i = 0; i < 3; ++i) {
            CKInterfaceButton* button = static_cast<CKInterfaceButton*>(buttons[i]);
            button->m_baSuppress = static_cast<uint8_t>((button->m_baSuppress & 0xfe) | CKInterfaceButton::kSuppressText);
        }
    }
    m_unk6c[1] = 0;
    m_bBlockAnswer = 1;
    m_unk6c[0] = 0;
}

// 0x0052c9c0 CKMenuMessageBox_Close: the menus' Close (KBase730C_Close 0x513f88), nothing else.
void CKMenuMessageBox::Close() { CKMenuBase114c::Close(); }

// 0x0052d3e0 CFlashMessageBox2d_HideMessage_maybe
void CKMenuMessageBox::HideMessage() {
    if (Vf60() != nullptr) {
        CKFlashUI* flashUI = static_cast<CKFlashUI*>(Vf60());
        flashUI->m_baFlags = (flashUI->m_baFlags & ~CKFlashUI::kNeverRender) | CKFlashUI::kNeverRender;
        flashUI->HideAllHotSpotHierarchy();
    }
    m_iUnkd4 = -1;
}

// 0x0052cc28 CKMenuMessageBox_vfE8 (OnItemState): a button validated (state 4, second call) while a layout
// with buttons is shown and answers are not blocked: the item goes to the Flash message box (message 0x2301,
// stored as its selected button).
void CKMenuMessageBox::OnItemState(uint8_t item, uint8_t state, uint8_t arg) {
    if (arg != 1 || state != 4 || m_bBlockAnswer != 0) return;
    if (static_cast<uint32_t>(m_iUnkd4 + 1) <= 1u) return;
    CMenuManager* menuManager = static_cast<CMenuManager*>(g_pEngine->m_manager2d->m_menuManager);
    menuManager->m_pFlashMessageBox->MessageProc(0x2301, reinterpret_cast<void*>(static_cast<uintptr_t>(item)));
}
