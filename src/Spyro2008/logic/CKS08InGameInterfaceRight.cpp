// CKS08InGameInterfaceRight.cpp - reconstructed original translation unit 0x53d330-0x541ff8 (GAME_TOC1, main_toc1), 53 functions, 46 live.
// Primary class: CKS08InGameInterfaceRight  key 0x7ecc  category Logic  size 0x294  vtable 0xb2c028
// Other owners: CKS08MenuArmors (4), SetCynderManaGaugeValue (1), SetCynderHealthGaugeValue (1), CynderElementHud (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x53d330  CKS08InGameInterfaceRight_Delete
//   [x] 0x53d380  CKS08InGameInterfaceRight_vf8C
//   [x] 0x53d3c8  CKS08InGameInterfaceRight_vf90
//   [x] 0x53d410  CKS08InGameInterfaceRight_StepGaugeTowardTarget_maybe
//   [x] 0x53d580  CKS08InGameInterfaceRight_UpdateManaGauge_maybe
//   [x] 0x53d6a0  CKS08InGameInterfaceRight_UpdateHealthGauge_maybe
//   [x] 0x53d7c0  SetCynderManaGaugeValue
//   [x] 0x53d850  SetCynderHealthGaugeValue
//   [x] 0x53d8e0  CKS08InGameInterfaceRight_UpdateShake_maybe
//   [x] 0x53e030  CKS08InGameInterfaceRight_UpdateUpgradeText_maybe
//   [x] 0x53e300  CKS08InGameInterfaceRight_StartShake_maybe
//   [x] 0x53e340  CKS08InGameInterfaceRight_UpdateComboDisplay_maybe
//   [ ] 0x53e578  CKS08InGameInterfaceRight_Save
//   [x] 0x53e5a0  CKS08InGameInterfaceRight_RecursiveRegistration  (inherited: CKMenuBase114c::RecursiveRegistration)
//   [x] 0x53e5c8  CKS08InGameInterfaceRight_Destroy  (inherited: CKMenuBase_114c_maybe_Destroy)
//   [x] 0x53e5f0  CKS08InGameInterfaceRight_DeleteArray
//   [x] 0x53e690  RegisterCKS08InGameInterfaceRightType  (the class registry: Kp3Ported.inc (gen_kp3_stubs.py); its two -1.0 words before the class record are not used)
//   [ ] 0x53e718  _GLOBAL__D_53e718
//   [ ] 0x53e728  _GLOBAL__I_53e728
//   [x] 0x53e738  CKS08InGameInterfaceRight_SetPanelElementObject_maybe
//   [x] 0x53e790  CKS08InGameInterfaceRight_Construct  [dead]
//   [x] 0x53e848  CKS08InGameInterfaceRight_vf58
//   [x] 0x53e8c0  CynderElementHud_SelectElement_maybe
//   [ ] 0x53e908  CKS08InGameInterfaceRight_Construct_2  [dead]
//   [x] 0x53e9c0  CKS08InGameInterfaceRight_OnNewComboHit_maybe
//   [x] 0x53ebb0  CKS08InGameInterfaceRight_CreateArray
//   [x] 0x53ed18  CreateCKS08InGameInterfaceRight
//   [x] 0x53ee18  CKS08InGameInterfaceRight_QueueManaRestoredClip
//   [x] 0x53eff0  CKS08InGameInterfaceRight_QueueHealthRestoredClip
//   [x] 0x53f1c0  CKS08InGameInterfaceRight_SetManaShardGauge_maybe
//   [x] 0x53f3f8  CKS08InGameInterfaceRight_SetHealthShardGauge_maybe
//   [ ] 0x53f630  FUN_0053f630  [dead]
//   [ ] 0x53f808  FUN_0053f808  [dead]
//   [x] 0x53f9e0  CKS08InGameInterfaceRight_DeletingDestructor  (implicit destructor: CKMenuBase114c's inlined)
//   [x] 0x53fb18  CKS08InGameInterfaceRight_Destructor  (~CKMenuBase114c inlined (the same frees, checked against 0x556498))
//   [x] 0x53fc50  CKS08InGameInterfaceRight_Destructor_2  (implicit destructor: CKMenuBase114c's inlined)
//   [x] 0x53fd88  CKS08InGameInterfaceRight_EndComboDisplay_maybe
//   [x] 0x53fe80  CKS08InGameInterfaceRight_ShowPanelType1_maybe
//   [x] 0x53ffc0  CKS08InGameInterfaceRight_ShowPanel_maybe
//   [x] 0x540100  CKS08InGameInterfaceRight_CloseTimedPanel_maybe
//   [x] 0x540208  CKS08InGameInterfaceRight_OnComboHit_maybe
//   [x] 0x540318  CKS08InGameInterfaceRight_HidePanel_maybe
//   [x] 0x5404f8  CKS08InGameInterfaceRight_Load
//   [x] 0x540cc0  CKS08InGameInterfaceRight_ShowUpgradeText_maybe
//   [x] 0x540f08  CKS08InGameInterfaceRight_Update_maybe
//   [x] 0x541838  CKS08InGameInterfaceRight_ResetWidgets_maybe
//   [x] 0x541cc8  CKS08MenuArmors_Delete  (CKS08MenuArmors::Delete, DOTD_DECLARE_FACTORIES)
//   [x] 0x541d18  CKS08MenuArmors_vf8C  (CKS08MenuArmors::Vf8C, ui/CKS08MenuArmors.h)
//   [x] 0x541d30  CKS08MenuArmors_vf90  (CKS08MenuArmors::Vf90, ui/CKS08MenuArmors.h)
//   [x] 0x541d48  CKS08MenuArmors_vfE8  (a nop: CKS08MenuArmors keeps CKMenuBase114c's nop OnItemState)
//   [ ] 0x541d50  FUN_00541d50  [dead]
//   [ ] 0x541db8  FUN_00541db8  [dead]
//   [ ] 0x541f50  FUN_00541f50  [dead]
//
//   [x] 0x9c9550  CKS08InGameInterfaceRight_IsKindOfClass  [inline]
//   [ ] 0x9c9588  CKS08InGameInterfaceRight_GetClassType  [inline]
//   [ ] 0x9c9590  CKS08InGameInterfaceRight_GetClassID  [inline]
//   [x] 0x9c9598  CKS08InGameInterfaceRight_vfB8  [inline]
//   [x] 0x9c95a0  CKS08InGameInterfaceRight_vfE0  [inline]
//   [x] 0x9c95a8  CKS08InGameInterfaceRight_vfBC  [inline]
//   [x] 0x9c95b0  CKS08InGameInterfaceRight_vfC0  [inline]
//   [x] 0x9c95c0  CKS08InGameInterfaceRight_vfC4  [inline]
//   [x] 0x9c95c8  CKS08InGameInterfaceRight_vfC8  [inline]
//   [x] 0x9c95d8  CKS08InGameInterfaceRight_vfCC  [inline]
//   [x] 0x9c95e8  CKS08InGameInterfaceRight_GetWidgetSlotCount  [inline]
//   [x] 0x9c95f0  CKS08InGameInterfaceRight_GetWidgetSlots  [inline]
//   [x] 0x9c9600  CKS08InGameInterfaceRight_vf84  [inline]
//   [x] 0x9c9608  CKS08InGameInterfaceRight_vf88  [inline]
#include "Spyro2008/logic/CKS08InGameInterfaceRight.h"

#include "Spyro2008/logic/HudGaugeOps.h"
#include "Spyro2008/logic/HudPanelOps.h"
#include "Spyro2008/logic/HudSideOps.h"
#include "crt/ppc_ops.h"

#include <cstring>
#include "k2000/core/Stub.h"
#include "k2000/graphical/ui/CText2d.h"
#include "k2000/io/IKFile.h"

// 0x0053d380 CKS08InGameInterfaceRight_vf8C: group g's single reference.
IKSerializable** CKS08InGameInterfaceRight::Vf8C(uint32_t group) {
    if (group == 1) return &m_aGroupSlots[1].m_pRef;
    if (group == 0) return &m_aGroupSlots[0].m_pRef;
    if (group == 2) return &m_aGroupSlots[2].m_pRef;
    if (group == 3) return &m_aGroupSlots[3].m_pRef;
    return nullptr;
}

// 0x0053d3c8 CKS08InGameInterfaceRight_vf90: group g's state.
CKMenuBase114c::GroupState* CKS08InGameInterfaceRight::Vf90(uint32_t group) {
    if (group == 1) return &m_aGroupSlots[1].m_state;
    if (group == 0) return &m_aGroupSlots[0].m_state;
    if (group == 2) return &m_aGroupSlots[2].m_state;
    if (group == 3) return &m_aGroupSlots[3].m_state;
    return nullptr;
}

// 0x0053ed18 CreateCKS08InGameInterfaceRight: after the CKMenuBase114c part, three floats set to 0.0
// (lfs TOC1+0x7b5c), in the original's store order.
CKS08InGameInterfaceRight::CKS08InGameInterfaceRight() {
    m_fUnk250 = 0.0f;
    m_fUnk258 = 0.0f;
    m_fUnk254 = 0.0f;
    // Not written by the original's Create, Load or ResetWidgets: the combo display's time is heap leftovers there (RPCS3
    // reads 8.4e-8 on Spyro's side, 0 on Cynder's) until the first combo hit. UpdateComboDisplay and vf58 test it (> 0), so
    // it is set to 0 here instead of depending on the heap (found by work/fill_test.py).
    m_fComboTime = 0.0f;
}

// 0x005404f8 CKS08InGameInterfaceRight_Load: no type test of its own, so its fields are read whatever the type.
int32_t CKS08InGameInterfaceRight::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    ReadF32LE(file, &m_fUnk228);
    ReadF32LE(file, &m_fUnk23c);
    ReadF32LE(file, &m_fUnk240);
    IKFile_ReadRef(file, &m_pQuake244);
    IKFile_ReadRef(file, &m_pQuakeUpdater248);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_fUnk234), 2);
    IKFile_ReadRef(file, &m_pGauge218);
    IKFile_ReadRef(file, &m_pGaugeUpdater21c);
    IKFile_ReadRef(file, &m_pGauge220);
    IKFile_ReadRef(file, &m_pGaugeUpdater224);
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

// 0x0053d7c0 SetCynderManaGaugeValue: the mana gauge (+0x224) to the value; the auxiliary value is cleared
// when the value does not rise.
void SetCynderManaGaugeValue(double requestedValue, CKS08InGameInterfaceRight* hud) {
    hudgauge::SetHudGaugeValue(requestedValue, hud->m_pGaugeUpdater224);
}

// 0x0053d850 SetCynderHealthGaugeValue: the same on the health gauge (+0x21c).
void SetCynderHealthGaugeValue(double requestedValue, CKS08InGameInterfaceRight* hud) {
    hudgauge::SetHudGaugeValue(requestedValue, hud->m_pGaugeUpdater21c);
}

// 0x00540cc0 CKS08InGameInterfaceRight_ShowUpgradeText_maybe: the text of the widget at +0xd0 set to `text`;
// with `shake` the panel's shake (+0x230 = +0x23c + +0x240, the quake updater started) and the panel's
// message out 8 (VfC0 +0x20) registered in the first free (or already holding it) reference of group 2.
void CKS08InGameInterfaceRight::ShowUpgradeText(const char* text, int32_t shake) {
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

// 0x00540318 CKS08InGameInterfaceRight_HidePanel_maybe (the labels are enabled here, as the original has it)
void CKS08InGameInterfaceRight::HidePanel() { hudpanel::HidePanel(this, true); }

// 0x0053ffc0 CKS08InGameInterfaceRight_ShowPanel_maybe: the label of widget slot 9.
void CKS08InGameInterfaceRight::ShowPanel(IKSerializable* text) { hudpanel::ShowPanel(this, text, 9); }

// 0x0053fe80 CKS08InGameInterfaceRight_ShowPanelType1_maybe: the label of widget slot 10.
void CKS08InGameInterfaceRight::ShowPanelType1(IKSerializable* text) { hudpanel::ShowPanel(this, text, 10); }

// ---- C2.7 step 7: the per-frame part (shared code in HudSideOps.h) ----

// 0x00540f08 CKS08InGameInterfaceRight_Update_maybe (vt+0xdc)
uint8_t CKS08InGameInterfaceRight::OnMenuState(int32_t phase, uint8_t /*other*/) { return hudside::OnMenuState(this, phase, false); }

// 0x0053e848 CKS08InGameInterfaceRight_vf58 (vt+0x58)
void CKS08InGameInterfaceRight::Resume() {
    CKMenuBase114c::Resume();  // 0x00513700 KBase730C_Open_maybe
    hudside::ResumeCombo(this);
}

// 0x0053e9c0 CKS08InGameInterfaceRight_OnNewComboHit_maybe
void CKS08InGameInterfaceRight::OnNewComboHit(float value) { hudside::OnNewComboHit(this, value); }

// 0x00540208 CKS08InGameInterfaceRight_OnComboHit_maybe
void CKS08InGameInterfaceRight::OnComboHit(float value) { hudside::OnComboHit(this, value); }

// 0x0053fd88 CKS08InGameInterfaceRight_EndComboDisplay_maybe
void CKS08InGameInterfaceRight::EndComboDisplay() { hudside::EndComboDisplay(this); }

// 0x00540100 CKS08InGameInterfaceRight_CloseTimedPanel_maybe
void CKS08InGameInterfaceRight::CloseTimedPanel() { hudside::CloseTimedPanel(this); }

// 0x0053e738 CKS08InGameInterfaceRight_SetPanelElementObject_maybe
void CKS08InGameInterfaceRight::SetPanelElementObject(RwTexture* texture) { hudside::SetPanelElementObject(this, texture); }

// 0x0053e8c0 CynderElementHud_SelectElement_maybe
void CKS08InGameInterfaceRight::SelectElement(RwTexture* texture) { hudside::SelectElement(this, texture); }

// 0x0053ee18 CKS08InGameInterfaceRight_QueueManaRestoredClip: the restored clip (message out 8) in group 1.
void CKS08InGameInterfaceRight::QueueManaRestoredClip() { AddToRefGroup(VfC0()[8], 1); }

// 0x0053eff0 CKS08InGameInterfaceRight_QueueHealthRestoredClip: the same in group 0.
void CKS08InGameInterfaceRight::QueueHealthRestoredClip() { AddToRefGroup(VfC0()[8], 0); }

// 0x0053f1c0 CKS08InGameInterfaceRight_SetManaShardGauge_maybe: the second row (4 shards), group 1.
void CKS08InGameInterfaceRight::SetManaShardGauge(uint8_t count, uint8_t shake) { hudside::SetShardGauge(this, count, shake, false, 4, 1); }

// 0x0053f3f8 CKS08InGameInterfaceRight_SetHealthShardGauge_maybe: the first row (5 shards), group 0.
void CKS08InGameInterfaceRight::SetHealthShardGauge(uint8_t count, uint8_t shake) { hudside::SetShardGauge(this, count, shake, true, 5, 0); }

// 0x0053d8e0 CKS08InGameInterfaceRight_UpdateShake_maybe: the shard rows (slots 11-15 with +0x264, 16-19 with +0x265).
// BUG(original): only slots 11-15 are checked; the second row's billboards are used unchecked.
void CKS08InGameInterfaceRight::UpdateShake(float dt, float scaledDt) {
    for (uint32_t slot = 11; slot <= 15; ++slot) {
        if (hudside::Element(this, slot) == nullptr) return;
    }
    hudside::UpdateShardRow(this, m_ui8ShardsA, 11, 5, dt, scaledDt);
    hudside::UpdateShardRow(this, m_ui8ShardsB, 16, 4, dt, scaledDt);
}

// 0x0053e030 CKS08InGameInterfaceRight_UpdateUpgradeText_maybe: unlike Spyro's, the shake is applied here (its scale at
// least 0.01, its offset added to +0x234), the rotation is left alone, and the hidden text gets scale 1 and its offset.
void CKS08InGameInterfaceRight::UpdateUpgradeText(float dt) {
    IKNode2d* node = hudside::Element(this, 7);
    if (node == nullptr) return;
    IKText2d* text = static_cast<CText2d*>(node);
    uint8_t color[4];
    std::memcpy(color, &text->m_Color, 4);
    if (!(m_fUnk230 > 0.0f)) {
        node->m_v2ConstantScale.m_fX = 1.0f;
        node->m_v2ConstantScale.m_fY = 1.0f;
        SetElementX(m_fUnk234[0], 7);
        SetElementY(m_fUnk234[1], 7);
        hudside::Element(this, 7)->Disable();
        return;
    }
    node->Enable();
    if (m_fUnk230 > m_fUnk240) {
        color[3] = 0xff;
    } else {
        color[3] = static_cast<uint8_t>(ppc::fctiwz(m_fUnk230 * 255.0f / m_fUnk240));  // TOC1+0x7b60
    }
    static_cast<CText2d*>(hudside::Element(this, 7))->SetColor(color);  // IKText2d vt+0x44
    float shake[15];
    static_cast<CKQuakeCpntUpdater*>(m_pQuakeUpdater248)->EvaluateScaled(dt, 1.0f, shake);
    float sx = shake[6] + 1.0f;
    if (!(sx >= 0.01f)) sx = 0.01f;
    float sy = shake[7] + 1.0f;
    if (!(sy >= 0.01f)) sy = 0.01f;
    IKNode2d* shaken = hudside::Element(this, 7);
    shaken->m_v2ConstantScale.m_fX = sx;
    shaken->m_v2ConstantScale.m_fY = sy;
    SetElementX(shake[0] + m_fUnk234[0], 7);
    SetElementY(shake[1] + m_fUnk234[1], 7);
    m_fUnk230 = m_fUnk230 - dt;
}

// 0x00541838 CKS08InGameInterfaceRight_ResetWidgets_maybe (vt+0x98): as Spyro's, except that the shake byte (+0x266)
// is not cleared.
void CKS08InGameInterfaceRight::ResetWidgets() {
    CKMenuBase114c::ResetWidgets();
    m_ui8Flags214 = static_cast<uint8_t>(m_ui8Flags214 & ~4u);
    m_ui8ShardsB = 0;
    m_fShardTime = 0.0f;
    m_fUnk22c = 0.0f;
    m_ui8Active215 = 0;
    m_fUnk230 = 0.0f;
    m_ui8ShardsA = 0;
    for (uint32_t group = 0; group < 4; ++group) ClearRefGroup(group);
    for (uint32_t group = 0; group < 4; ++group) Vf88()[group].m_unk0c = 1;
}

// 0x0053e300 CKS08InGameInterfaceRight_StartShake_maybe
void CKS08InGameInterfaceRight::StartShake() {
    m_fUnk230 = m_fUnk23c + m_fUnk240;
    static_cast<CKQuakeCpntUpdater*>(m_pQuakeUpdater248)->Start();  // 0x24f770
}
