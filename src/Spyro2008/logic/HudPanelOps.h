// HudPanelOps.h - the panel show / hide code the two dragon HUD screens (CKS08InGameInterfaceLeft for
// Spyro, CKS08InGameInterfaceRight for Cynder) share: the original has one copy per class with the same
// code (0x53a2d8 / 0x53a4b8 / 0x53a5f8 and 0x540318 / 0x53fe80 / 0x53ffc0), so they are templates here.
// The panel's state is the byte at +0x214 (m_ui8Flags214): bit 2 = the panel is shown. The labels are the widget slots 9 (the normal panel's) and 10 (type 1's).
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKS08GameManager.h"
#include "k2000/graphical/ui/CKFlashMessageOut.h"
#include "k2000/graphical/ui/CText2d.h"

namespace hudpanel {

constexpr uint8_t kShownBit = 0x04;

// ShowPanel (label slot 9) / ShowPanelType1 (label slot 10): when not shown yet, the "show" flash message
// (message out 6) is posted and the state set; the label is shown with `text`.
template <class Hud>
void ShowPanel(Hud* hud, IKSerializable* text, uint32_t labelSlot) {
    if ((hud->m_ui8Flags214 & kShownBit) == 0) {
        IKSerializable* message = hud->VfC0()[6];  // +0x18
        if (message != nullptr) static_cast<CKFlashMessageOut*>(message)->PostFlashMessage();
        hud->m_ui8Flags214 = static_cast<uint8_t>(hud->m_ui8Flags214 | kShownBit);
    }
    CText2d* label = static_cast<CText2d*>(hud->m_aWidgetSlots[labelSlot].m_pElement);
    if (label != nullptr) {
        label->Enable();  // vt+0x64
        label->SetTextById(text);
    }
}

// HidePanel: when shown, the "hide" flash message (message out 7) is posted and the state cleared; both
// labels get the game manager's default text (vt+0x214), and are disabled (Spyro's panel) or, as the
// original has it, enabled (Cynder's: `showLabels`).
template <class Hud>
void HidePanel(Hud* hud, bool showLabels) {
    if ((hud->m_ui8Flags214 & kShownBit) != 0) {
        IKSerializable* message = hud->VfC0()[7];  // +0x1c
        if (message != nullptr) static_cast<CKFlashMessageOut*>(message)->PostFlashMessage();
        hud->m_ui8Flags214 = static_cast<uint8_t>(hud->m_ui8Flags214 & ~kShownBit);
    }
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(hud->m_pGameManager);
    for (uint32_t slot = 9; slot <= 10; ++slot) {
        CText2d* label = static_cast<CText2d*>(hud->m_aWidgetSlots[slot].m_pElement);
        if (label == nullptr) continue;
        if (showLabels) label->Enable(); else label->Disable();
        label->SetTextById(manager->Vf214());
    }
}

}  // namespace hudpanel
