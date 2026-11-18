// CKS08InGameInterfaceLeft.cpp - reconstructed original translation unit 0x5378d8-0x53c360 (GAME_TOC1, main_toc1), 46 functions, 42 live.
// Primary class: CKS08InGameInterfaceLeft  key 0x59cc  category Logic  size 0x294  vtable 0xb2be18
// Other owners: SetSpyroManaGaugeValue (1), SetSpyroHealthGaugeValue (1), SpyroElementHud (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5378d8  CKS08InGameInterfaceLeft_Delete
//   [x] 0x537928  CKS08InGameInterfaceLeft_vf8C
//   [x] 0x537970  CKS08InGameInterfaceLeft_vf90
//   [x] 0x5379b8  CKS08InGameInterfaceLeft_StepGaugeTowardTarget_maybe
//   [x] 0x537b28  CKS08InGameInterfaceLeft_UpdateManaGauge_maybe
//   [x] 0x537c48  CKS08InGameInterfaceLeft_UpdateHealthGauge_maybe
//   [x] 0x537d68  SetSpyroManaGaugeValue
//   [x] 0x537df8  SetSpyroHealthGaugeValue
//   [x] 0x537e88  CKS08InGameInterfaceLeft_UpdateShake_maybe
//   [x] 0x538608  CKS08InGameInterfaceLeft_StartShake_maybe
//   [x] 0x538648  CKS08InGameInterfaceLeft_UpdateComboDisplay_maybe
//   [x] 0x538880  CKS08InGameInterfaceLeft_UpdateUpgradeText_maybe
//   [ ] 0x538ad8  CKS08InGameInterfaceLeft_Save
//   [x] 0x538b00  CKS08InGameInterfaceLeft_RecursiveRegistration  (inherited: CKMenuBase114c::RecursiveRegistration)
//   [x] 0x538b28  CKS08InGameInterfaceLeft_Destroy  (inherited: CKMenuBase_114c_maybe_Destroy)
//   [x] 0x538b50  CKS08InGameInterfaceLeft_DeleteArray
//   [x] 0x538bf0  RegisterCKS08InGameInterfaceLeftType  (the class registry: Kp3Ported.inc (gen_kp3_stubs.py); its two -1.0 words before the class record are not used)
//   [ ] 0x538c78  _GLOBAL__D_538c78
//   [ ] 0x538c88  _GLOBAL__I_538c88
//   [x] 0x538c98  CKS08InGameInterfaceLeft_SetPanelElementObject_maybe
//   [x] 0x538cf0  CKS08InGameInterfaceLeft_Construct  [dead]
//   [x] 0x538da8  CKS08InGameInterfaceLeft_vf58
//   [x] 0x538e20  SpyroElementHud_SelectElement_maybe
//   [ ] 0x538e68  CKS08InGameInterfaceLeft_Construct_2  [dead]
//   [x] 0x538f20  CKS08InGameInterfaceLeft_ShowUpgradeText_maybe
//   [x] 0x539168  CKS08InGameInterfaceLeft_CreateArray
//   [x] 0x5392d0  CreateCKS08InGameInterfaceLeft
//   [ ] 0x5393d0  FUN_005393d0  [dead]
//   [x] 0x5395a8  CKS08InGameInterfaceLeft_QueueManaRestoredClip
//   [x] 0x539780  CKS08InGameInterfaceLeft_QueueHealthRestoredClip
//   [x] 0x539950  CKS08InGameInterfaceLeft_SetManaShardGauge_maybe
//   [x] 0x539b88  CKS08InGameInterfaceLeft_SetHealthShardGauge_maybe
//   [ ] 0x539dc0  FUN_00539dc0  [dead]
//   [x] 0x539f98  CKS08InGameInterfaceLeft_DeletingDestructor  (implicit destructor: CKMenuBase114c's inlined)
//   [x] 0x53a0d0  CKS08InGameInterfaceLeft_EndComboDisplay_maybe
//   [x] 0x53a1c8  CKS08InGameInterfaceLeft_OnComboHit_maybe
//   [x] 0x53a2d8  CKS08InGameInterfaceLeft_HidePanel_maybe
//   [x] 0x53a4b8  CKS08InGameInterfaceLeft_ShowPanelType1_maybe
//   [x] 0x53a5f8  CKS08InGameInterfaceLeft_ShowPanel_maybe
//   [x] 0x53a738  CKS08InGameInterfaceLeft_CloseTimedPanel_maybe
//   [x] 0x53a840  CKS08InGameInterfaceLeft_Load
//   [x] 0x53b008  CKS08InGameInterfaceLeft_Destructor  (~CKMenuBase114c inlined (the same frees, checked against 0x556498))
//   [x] 0x53b140  CKS08InGameInterfaceLeft_Destructor_2  (implicit destructor: CKMenuBase114c's inlined)
//   [x] 0x53b278  CKS08InGameInterfaceLeft_OnNewComboHit_maybe
//   [x] 0x53b468  CKS08InGameInterfaceLeft_Update_maybe
//   [x] 0x53bec8  CKS08InGameInterfaceLeft_ResetWidgets_maybe
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
#include "Spyro2008/logic/HudSideOps.h"
#include "crt/ppc_ops.h"

#include <cstring>
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
    // Not written by the original's Create, Load or ResetWidgets: the combo display's time is heap leftovers there (RPCS3
    // reads 8.4e-8 on Spyro's side, 0 on Cynder's) until the first combo hit. UpdateComboDisplay and vf58 test it (> 0), so
    // it is set to 0 here instead of depending on the heap (found by work/fill_test.py).
    m_fComboTime = 0.0f;
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
    static_cast<CKQuakeCpntUpdater*>(m_pQuakeUpdater248)->Start();  // 0x24f770
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

// ---- C2.7 step 7: the per-frame part (shared code in HudSideOps.h) ----

// 0x0053b468 CKS08InGameInterfaceLeft_Update_maybe (vt+0xdc)
uint8_t CKS08InGameInterfaceLeft::OnMenuState(int32_t phase, uint8_t /*other*/) { return hudside::OnMenuState(this, phase, true); }

// 0x00538da8 CKS08InGameInterfaceLeft_vf58 (vt+0x58)
void CKS08InGameInterfaceLeft::Resume() {
    CKMenuBase114c::Resume();  // 0x00513700 KBase730C_Open_maybe
    hudside::ResumeCombo(this);
}

// 0x0053b278 CKS08InGameInterfaceLeft_OnNewComboHit_maybe
void CKS08InGameInterfaceLeft::OnNewComboHit(float value) { hudside::OnNewComboHit(this, value); }

// 0x0053a1c8 CKS08InGameInterfaceLeft_OnComboHit_maybe
void CKS08InGameInterfaceLeft::OnComboHit(float value) { hudside::OnComboHit(this, value); }

// 0x0053a0d0 CKS08InGameInterfaceLeft_EndComboDisplay_maybe
void CKS08InGameInterfaceLeft::EndComboDisplay() { hudside::EndComboDisplay(this); }

// 0x0053a738 CKS08InGameInterfaceLeft_CloseTimedPanel_maybe
void CKS08InGameInterfaceLeft::CloseTimedPanel() { hudside::CloseTimedPanel(this); }

// 0x00538c98 CKS08InGameInterfaceLeft_SetPanelElementObject_maybe
void CKS08InGameInterfaceLeft::SetPanelElementObject(RwTexture* texture) { hudside::SetPanelElementObject(this, texture); }

// 0x00538e20 SpyroElementHud_SelectElement_maybe
void CKS08InGameInterfaceLeft::SelectElement(RwTexture* texture) { hudside::SelectElement(this, texture); }

// 0x005395a8 CKS08InGameInterfaceLeft_QueueManaRestoredClip: the restored clip (message out 8) in group 1.
void CKS08InGameInterfaceLeft::QueueManaRestoredClip() { AddToRefGroup(VfC0()[8], 1); }

// 0x00539780 CKS08InGameInterfaceLeft_QueueHealthRestoredClip: the same in group 0.
void CKS08InGameInterfaceLeft::QueueHealthRestoredClip() { AddToRefGroup(VfC0()[8], 0); }

// 0x00539950 CKS08InGameInterfaceLeft_SetManaShardGauge_maybe: the second row (5 shards), group 1.
void CKS08InGameInterfaceLeft::SetManaShardGauge(uint8_t count, uint8_t shake) { hudside::SetShardGauge(this, count, shake, false, 5, 1); }

// 0x00539b88 CKS08InGameInterfaceLeft_SetHealthShardGauge_maybe: the first row (4 shards), group 0.
void CKS08InGameInterfaceLeft::SetHealthShardGauge(uint8_t count, uint8_t shake) { hudside::SetShardGauge(this, count, shake, true, 4, 0); }

// 0x00537e88 CKS08InGameInterfaceLeft_UpdateShake_maybe: the shard rows (slots 11-14 with +0x264, 15-19 with +0x265),
// all nine billboards needed. `dt` is the quakes' time, `scaledDt` the rows' clock.
void CKS08InGameInterfaceLeft::UpdateShake(float dt, float scaledDt) {
    for (uint32_t slot = 11; slot <= 19; ++slot) {
        if (hudside::Element(this, slot) == nullptr) return;
    }
    hudside::UpdateShardRow(this, m_ui8ShardsA, 11, 4, dt, scaledDt);
    hudside::UpdateShardRow(this, m_ui8ShardsB, 15, 5, dt, scaledDt);
}

// 0x00538880 CKS08InGameInterfaceLeft_UpdateUpgradeText_maybe: the upgrade text (slot 7) at scale 1, its offset
// (+0x234) and no rotation; while +0x230 runs it is shown with its colour, alpha 255 until the last +0x240 seconds then
// fading, and the shake (+0x248) added; else hidden.
void CKS08InGameInterfaceLeft::UpdateUpgradeText(float dt) {
    IKNode2d* node = hudside::Element(this, 7);
    if (node == nullptr) return;
    IKText2d* text = static_cast<CText2d*>(node);
    uint8_t color[4];
    std::memcpy(color, &text->m_Color, 4);
    node->m_v2ConstantScale.m_fX = 1.0f;
    node->m_v2ConstantScale.m_fY = 1.0f;
    SetElementX(m_fUnk234[0], 7);
    SetElementY(m_fUnk234[1], 7);
    hudside::Element(this, 7)->m_f32RotateAngle = 0.0f;
    if (!(m_fUnk230 > 0.0f)) {
        hudside::Element(this, 7)->Disable();
        return;
    }
    hudside::Element(this, 7)->Enable();
    if (m_fUnk230 > m_fUnk240) {
        color[3] = 0xff;
    } else {
        color[3] = static_cast<uint8_t>(ppc::fctiwz(m_fUnk230 * 255.0f / m_fUnk240));  // TOC1+0x7a4c
    }
    static_cast<CText2d*>(hudside::Element(this, 7))->SetColor(color);  // IKText2d vt+0x44
    float shake[15];
    static_cast<CKQuakeCpntUpdater*>(m_pQuakeUpdater248)->EvaluateScaled(dt, 1.0f, shake);
    ShakeSample_ApplyToElement2d(shake, this, 7);
    m_fUnk230 = m_fUnk230 - dt;
}

// 0x0053bec8 CKS08InGameInterfaceLeft_ResetWidgets_maybe (vt+0x98): the base's, the label panel's bit, the shard rows,
// the panel and upgrade timers cleared, the four reference groups cleared and their +0x0c bytes set.
void CKS08InGameInterfaceLeft::ResetWidgets() {
    CKMenuBase114c::ResetWidgets();
    m_ui8Flags214 = static_cast<uint8_t>(m_ui8Flags214 & ~4u);
    m_ui8ShardShake = 0;
    m_fShardTime = 0.0f;
    m_fUnk21c = 0.0f;
    m_ui8Active215 = 0;
    m_fUnk230 = 0.0f;
    m_ui8ShardsA = 0;
    m_ui8ShardsB = 0;
    for (uint32_t group = 0; group < 4; ++group) ClearRefGroup(group);
    for (uint32_t group = 0; group < 4; ++group) Vf88()[group].m_unk0c = 1;
}

// 0x00538608 CKS08InGameInterfaceLeft_StartShake_maybe
void CKS08InGameInterfaceLeft::StartShake() {
    m_fUnk230 = m_fUnk23c + m_fUnk240;
    static_cast<CKQuakeCpntUpdater*>(m_pQuakeUpdater248)->Start();  // 0x24f770
}
