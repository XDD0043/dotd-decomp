// CKS08InGameInterfaceLeft.cpp - reconstructed original translation unit 0x5378d8-0x53c360 (GAME_TOC1, main_toc1), 46 functions, 42 live.
// Primary class: CKS08InGameInterfaceLeft  key 0x59cc  category Logic  size 0x294  vtable 0xb2be18
// Other owners: SetSpyroManaGaugeValue (1), SetSpyroHealthGaugeValue (1), SpyroElementHud (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5378d8  CKS08InGameInterfaceLeft_Delete
//   [x] 0x537928  CKS08InGameInterfaceLeft_vf8C
//   [x] 0x537970  CKS08InGameInterfaceLeft_vf90
//   [ ] 0x5379b8  CKS08InGameInterfaceLeft_StepGaugeTowardTarget_maybe
//   [ ] 0x537b28  CKS08InGameInterfaceLeft_UpdateManaGauge_maybe
//   [ ] 0x537c48  CKS08InGameInterfaceLeft_UpdateHealthGauge_maybe
//   [x] 0x537d68  SetSpyroManaGaugeValue
//   [x] 0x537df8  SetSpyroHealthGaugeValue
//   [ ] 0x537e88  CKS08InGameInterfaceLeft_UpdateShake_maybe
//   [ ] 0x538608  CKS08InGameInterfaceLeft_StartShake_maybe
//   [ ] 0x538648  CKS08InGameInterfaceLeft_UpdateComboDisplay_maybe
//   [ ] 0x538880  CKS08InGameInterfaceLeft_UpdateUpgradeText_maybe
//   [ ] 0x538ad8  CKS08InGameInterfaceLeft_Save
//   [ ] 0x538b00  CKS08InGameInterfaceLeft_RecursiveRegistration
//   [ ] 0x538b28  CKS08InGameInterfaceLeft_Destroy
//   [x] 0x538b50  CKS08InGameInterfaceLeft_DeleteArray
//   [ ] 0x538bf0  RegisterCKS08InGameInterfaceLeftType
//   [ ] 0x538c78  _GLOBAL__D_538c78
//   [ ] 0x538c88  _GLOBAL__I_538c88
//   [ ] 0x538c98  CKS08InGameInterfaceLeft_SetPanelElementObject_maybe
//   [x] 0x538cf0  CKS08InGameInterfaceLeft_Construct  [dead]
//   [ ] 0x538da8  CKS08InGameInterfaceLeft_vf58
//   [ ] 0x538e20  SpyroElementHud_SelectElement_maybe
//   [ ] 0x538e68  CKS08InGameInterfaceLeft_Construct_2  [dead]
//   [x] 0x538f20  CKS08InGameInterfaceLeft_ShowUpgradeText_maybe
//   [x] 0x539168  CKS08InGameInterfaceLeft_CreateArray
//   [x] 0x5392d0  CreateCKS08InGameInterfaceLeft
//   [ ] 0x5393d0  FUN_005393d0  [dead]
//   [ ] 0x5395a8  CKS08InGameInterfaceLeft_QueueManaRestoredClip
//   [ ] 0x539780  CKS08InGameInterfaceLeft_QueueHealthRestoredClip
//   [ ] 0x539950  CKS08InGameInterfaceLeft_SetManaShardGauge_maybe
//   [ ] 0x539b88  CKS08InGameInterfaceLeft_SetHealthShardGauge_maybe
//   [ ] 0x539dc0  FUN_00539dc0  [dead]
//   [ ] 0x539f98  CKS08InGameInterfaceLeft_DeletingDestructor
//   [ ] 0x53a0d0  CKS08InGameInterfaceLeft_EndComboDisplay_maybe
//   [ ] 0x53a1c8  CKS08InGameInterfaceLeft_OnComboHit_maybe
//   [x] 0x53a2d8  CKS08InGameInterfaceLeft_HidePanel_maybe
//   [x] 0x53a4b8  CKS08InGameInterfaceLeft_ShowPanelType1_maybe
//   [x] 0x53a5f8  CKS08InGameInterfaceLeft_ShowPanel_maybe
//   [ ] 0x53a738  CKS08InGameInterfaceLeft_CloseTimedPanel_maybe
//   [x] 0x53a840  CKS08InGameInterfaceLeft_Load
//   [ ] 0x53b008  CKS08InGameInterfaceLeft_Destructor
//   [ ] 0x53b140  CKS08InGameInterfaceLeft_Destructor_2
//   [ ] 0x53b278  CKS08InGameInterfaceLeft_OnNewComboHit_maybe
//   [ ] 0x53b468  CKS08InGameInterfaceLeft_Update_maybe
//   [ ] 0x53bec8  CKS08InGameInterfaceLeft_ResetWidgets_maybe
//
//   [x] 0x9c93c8  CKS08InGameInterfaceLeft_IsKindOfClass  [inline]
//   [ ] 0x9c9400  CKS08InGameInterfaceLeft_GetClassType  [inline]
//   [ ] 0x9c9408  CKS08InGameInterfaceLeft_GetClassID  [inline]
//   [x] 0x9c9410  CKS08InGameInterfaceLeft_vfB8  [inline]
//   [x] 0x9c9418  CKS08InGameInterfaceLeft_vfE0  [inline]
//   [x] 0x9c9420  CKS08InGameInterfaceLeft_vfBC  [inline]
//   [x] 0x9c9428  CKS08InGameInterfaceLeft_vfC0  [inline]
//   [x] 0x9c9438  CKS08InGameInterfaceLeft_vfC4  [inline]
//   [x] 0x9c9440  CKS08InGameInterfaceLeft_vfC8  [inline]
//   [x] 0x9c9450  CKS08InGameInterfaceLeft_vfCC  [inline]
//   [x] 0x9c9460  CKS08InGameInterfaceLeft_GetWidgetSlotCount  [inline]
//   [x] 0x9c9468  CKS08InGameInterfaceLeft_GetWidgetSlots  [inline]
//   [x] 0x9c9478  CKS08InGameInterfaceLeft_vf84  [inline]
//   [x] 0x9c9480  CKS08InGameInterfaceLeft_vf88  [inline]
#include "Spyro2008/logic/CKS08InGameInterfaceLeft.h"

#include "Spyro2008/logic/HudGaugeOps.h"
#include "Spyro2008/logic/HudPanelOps.h"
#include "k2000/core/Stub.h"
#include "k2000/graphical/ui/CText2d.h"
#include "k2000/io/IKFile.h"

// 0x00537928 CKS08InGameInterfaceLeft_vf8C: group g's single reference.
IKSerializable** CKS08InGameInterfaceLeft::Vf8C(uint32_t group) {
    if (group == 1) return &m_aGroupSlots[1].m_pRef;
    if (group == 0) return &m_aGroupSlots[0].m_pRef;
    if (group == 2) return &m_aGroupSlots[2].m_pRef;
    if (group == 3) return &m_aGroupSlots[3].m_pRef;
    return nullptr;
}

// 0x00537970 CKS08InGameInterfaceLeft_vf90: group g's state.
CKMenuBase114c::GroupState* CKS08InGameInterfaceLeft::Vf90(uint32_t group) {
    if (group == 1) return &m_aGroupSlots[1].m_state;
    if (group == 0) return &m_aGroupSlots[0].m_state;
    if (group == 2) return &m_aGroupSlots[2].m_state;
    if (group == 3) return &m_aGroupSlots[3].m_state;
    return nullptr;
}

// 0x005392d0 CreateCKS08InGameInterfaceLeft: after the CKMenuBase114c part, three floats set to 0.0
// (lfs TOC1+0x7a48), in the original's store order.
CKS08InGameInterfaceLeft::CKS08InGameInterfaceLeft() {
    m_fUnk250 = 0.0f;
    m_fUnk258 = 0.0f;
    m_fUnk254 = 0.0f;
}

// 0x0053a840 CKS08InGameInterfaceLeft_Load: no type test of its own, so its fields are read whatever the type.
int32_t CKS08InGameInterfaceLeft::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    ReadF32LE(file, &m_fUnk218);
    ReadF32LE(file, &m_fUnk23c);
    ReadF32LE(file, &m_fUnk240);
    IKFile_ReadRef(file, &m_pQuake244);
    IKFile_ReadRef(file, &m_pQuakeUpdater248);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_fUnk234), 2);
    IKFile_ReadRef(file, &m_pGauge220);
    IKFile_ReadRef(file, &m_pGaugeUpdater224);
    IKFile_ReadRef(file, &m_pGauge228);
    IKFile_ReadRef(file, &m_pGaugeUpdater22c);
    ReadF32LE(file, &m_fUnk268);
    ReadF32LE(file, &m_fUnk26c);
    IKFile_ReadRef(file, &m_pQuake270);
    IKFile_ReadRef(file, &m_pQuakeUpdater274);
    ReadF32LE(file, &m_fUnk27c);
    ReadU8(file, &m_unk280);
    IKFile_ReadRef(file, &m_pQuake284);
    IKFile_ReadRef(file, &m_pQuakeUpdater288);
    IKFile_ReadRef(file, &m_pGauge28c);
    IKFile_ReadRef(file, &m_pGaugeUpdater290);
    return 1;
}

// 0x00537d68 SetSpyroManaGaugeValue: the mana gauge (+0x22c) to the value; the auxiliary value is cleared
// when the value does not rise.
void SetSpyroManaGaugeValue(double requestedValue, CKS08InGameInterfaceLeft* hud) {
    hudgauge::SetHudGaugeValue(requestedValue, hud->m_pGaugeUpdater22c);
}

// 0x00537df8 SetSpyroHealthGaugeValue: the same on the health gauge (+0x224).
void SetSpyroHealthGaugeValue(double requestedValue, CKS08InGameInterfaceLeft* hud) {
    hudgauge::SetHudGaugeValue(requestedValue, hud->m_pGaugeUpdater224);
}

// 0x00538f20 CKS08InGameInterfaceLeft_ShowUpgradeText_maybe: the text of the widget at +0xd0 set to `text`;
// with `shake` the panel's shake (+0x230 = +0x23c + +0x240, the quake updater started) and the panel's
// message out 8 (VfC0 +0x20) registered in the first free (or already holding it) reference of group 2.
void CKS08InGameInterfaceLeft::ShowUpgradeText(const char* text, int32_t shake) {
    CText2d* label = static_cast<CText2d*>(m_aWidgetSlots[7].m_pElement);
    if (label != nullptr) {
        label->SetTextAscii(text);  // vt+0x90 CText2d_SetTextAscii 0x66300
    }
    if (shake == 0) return;
    m_fUnk230 = m_fUnk23c + m_fUnk240;
    // CKQuakeCpntUpdater_Start(m_pQuakeUpdater248) 0x24f770 (k2000/components/CKQuakeCpntUpdater.cpp, hooks
    // family): STUB(C2.7 HUD), the HUD shake animation state (a quake component's playback, not rendering).
    DOTD_STUB_ONCE("CKS08InGameInterfaceLeft_ShowUpgradeText_maybe: CKQuakeCpntUpdater_Start (C2.7 HUD)");
    IKSerializable* message = VfC0()[8];
    RefGroup* groups = Vf88();
    IKSerializable** references = Vf8C(2);
    GroupState* states = Vf90(2);
    if (message == nullptr) return;
    for (uint32_t i = groups[2].m_unk04; i < groups[2].m_unk08; ++i) {
        if (references[i] != message && references[i] != nullptr) continue;
        references[i] = message;
        if (states != nullptr) {
            states[i].m_unk04 = 0;
            states[i].m_unk00 = 0;
        }
        return;
    }
}

// 0x0053a2d8 CKS08InGameInterfaceLeft_HidePanel_maybe
void CKS08InGameInterfaceLeft::HidePanel() { hudpanel::HidePanel(this, false); }

// 0x0053a5f8 CKS08InGameInterfaceLeft_ShowPanel_maybe: the label of widget slot 9.
void CKS08InGameInterfaceLeft::ShowPanel(IKSerializable* text) { hudpanel::ShowPanel(this, text, 9); }

// 0x0053a4b8 CKS08InGameInterfaceLeft_ShowPanelType1_maybe: the label of widget slot 10.
void CKS08InGameInterfaceLeft::ShowPanelType1(IKSerializable* text) { hudpanel::ShowPanel(this, text, 10); }
