// CKS08InGameInterfaceCenter.cpp - reconstructed original translation unit 0x5349a8-0x5378d8 (GAME_TOC1, main_toc1), 30 functions, 25 live.
// Primary class: CKS08InGameInterfaceCenter  key 0x79cc  category Logic  size 0x26c  vtable 0xb2bd10
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x5349a8  CKS08InGameInterfaceCenter_RefreshCounterHud_maybe  [dead]
//   [x] 0x534a88  CKS08InGameInterfaceCenter_SetGaugeMarker_maybe
//   [x] 0x534ad8  CKS08InGameInterfaceCenter_SetGaugeValue_maybe
//   [ ] 0x534b30  CKS08InGameInterfaceCenter_Save
//   [x] 0x534b58  CKS08InGameInterfaceCenter_RecursiveRegistration  (inherited: CKMenuBase114c::RecursiveRegistration)
//   [x] 0x534b80  CKS08InGameInterfaceCenter_Destroy  (inherited: CKMenuBase_114c_maybe_Destroy)
//   [x] 0x534ba8  CKS08InGameInterfaceCenter_DeleteArray
//   [x] 0x534c48  RegisterCKS08InGameInterfaceCenterType  (the class registry: Kp3Ported.inc (gen_kp3_stubs.py); its two -1.0 words before the class record are not used)
//   [ ] 0x534cd0  _GLOBAL__D_534cd0
//   [ ] 0x534ce0  _GLOBAL__I_534ce0
//   [x] 0x534cf0  CKS08InGameInterfaceCenter_Construct  [dead]
//   [ ] 0x534d98  CKS08InGameInterfaceCenter_Construct_2  [dead]
//   [ ] 0x534e40  CKS08InGameInterfaceCenter_RegisterWidgetCat0_maybe  [dead]
//   [x] 0x535010  CKS08InGameInterfaceCenter_CreateArray
//   [x] 0x535150  CKS08InGameInterfaceCenter_Create
//   [x] 0x535238  CKS08InGameInterfaceCenter_HideFuryGauge_maybe
//   [x] 0x5352e8  CKS08InGameInterfaceCenter_ShowFuryGauge_2_maybe
//   [x] 0x5353d0  CKS08InGameInterfaceCenter_ShowFuryGauge_maybe
//   [x] 0x5354c8  CKS08InGameInterfaceCenter_Load
//   [x] 0x535980  CKS08InGameInterfaceCenter_UpdateVisibility_maybe
//   [x] 0x535bc8  CKS08InGameInterfaceCenter_DeletingDestructor  (implicit destructor: CKMenuBase114c's inlined)
//   [x] 0x535d00  CKS08InGameInterfaceCenter_UpdateMessageDisplay_maybe
//   [x] 0x536310  CKS08InGameInterfaceCenter_QueueMessage_maybe
//   [x] 0x5364e0  CKS08InGameInterfaceCenter_ShowOrQueueMessagePair_maybe
//   [x] 0x536628  CKS08InGameInterfaceCenter_Destructor  (~CKMenuBase114c inlined (the same frees, checked against 0x556498))
//   [x] 0x536760  CKS08InGameInterfaceCenter_Destructor_2  (implicit destructor: CKMenuBase114c's inlined)
//   [ ] 0x536898  CKS08InGameInterfaceCenter_ClearWidgetCat1Tables_maybe  [dead]
//   [x] 0x5369b0  CKS08InGameInterfaceCenter_RebuildWidgetCat1Tables_maybe
//   [x] 0x536cf0  CKS08InGameInterfaceCenter_Update_maybe
//   [x] 0x537558  CKS08InGameInterfaceCenter_ResetWidgets_maybe
//
//   [x] 0x9c9300  CKS08InGameInterfaceCenter_IsKindOfClass  [inline]
//   [ ] 0x9c9338  CKS08InGameInterfaceCenter_GetClassType  [inline]
//   [ ] 0x9c9340  CKS08InGameInterfaceCenter_GetClassID  [inline]
//   [x] 0x9c9348  CKS08InGameInterfaceCenter_vfB8  [inline]
//   [x] 0x9c9350  CKS08InGameInterfaceCenter_vfE0  [inline]
//   [x] 0x9c9358  CKS08InGameInterfaceCenter_vfC4  [inline]
//   [x] 0x9c9360  CKS08InGameInterfaceCenter_vfC8  [inline]
//   [x] 0x9c9370  CKS08InGameInterfaceCenter_vfCC  [inline]
//   [x] 0x9c9380  CKS08InGameInterfaceCenter_vfBC  [inline]
//   [x] 0x9c9388  CKS08InGameInterfaceCenter_vfC0  [inline]
//   [x] 0x9c9398  CKS08InGameInterfaceCenter_GetWidgetSlotCount  [inline]
//   [x] 0x9c93a0  CKS08InGameInterfaceCenter_GetWidgetSlots  [inline]
//   [x] 0x9c93b0  CKS08InGameInterfaceCenter_vf84  [inline]
//   [x] 0x9c93b8  CKS08InGameInterfaceCenter_vf88  [inline]
#include "Spyro2008/logic/CKS08InGameInterfaceCenter.h"

#include "Spyro2008/logic/HudGaugeOps.h"
#include "Spyro2008/logic/HudSideOps.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "k2000/graphical/system/CVideoManager.h"
#include "k2000/graphical/ui/CKFlashUI.h"
#include "crt/ppc_ops.h"
#include "k2000/graphical/ui/CKFlashMessageOut.h"
#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"

// 0x005354c8 CKS08InGameInterfaceCenter_Load: no type test of its own, so its fields are read whatever the type.
int32_t CKS08InGameInterfaceCenter::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    ReadF32LE(file, &m_fUnk254);
    ReadF32LE(file, &m_fUnk258);
    ReadF32LE(file, &m_fUnk25c);
    IKFile_ReadRef(file, &m_pQuake);
    IKFile_ReadRef(file, &m_pQuakeUpdater);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_fUnk244), 2);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_fUnk24c), 2);
    IKFile_ReadRef(file, &m_pGauge20c);
    IKFile_ReadRef(file, &m_pGaugeUpdater210);
    IKFile_ReadRef(file, &m_pGauge214);
    IKFile_ReadRef(file, &m_pGaugeUpdater218);
    ReadF32LE(file, &m_fUnk204);
    return 1;
}

// 0x00534ad8 CKS08InGameInterfaceCenter_SetGaugeValue_maybe
void CKS08InGameInterfaceCenter::SetGaugeValue(float value, int32_t index) {
    hudgauge::SuperGaugeSetValue(value, static_cast<CKSuperGaugeCpntUpdater*>(index == 0 ? m_pGaugeUpdater210 : m_pGaugeUpdater218), 1);
}

// 0x00534a88 CKS08InGameInterfaceCenter_SetGaugeMarker_maybe
void CKS08InGameInterfaceCenter::SetGaugeMarker(float ratio, int32_t index) {
    hudgauge::SuperGaugeSetMarker(ratio, static_cast<CKSuperGaugeCpntUpdater*>(index == 0 ? m_pGaugeUpdater210 : m_pGaugeUpdater218));
}

// 0x00535238 CKS08InGameInterfaceCenter_HideFuryGauge_maybe
void CKS08InGameInterfaceCenter::HideFuryGauge() {
    IKSerializable* message = VfC0()[13];  // +0x34
    if (message != nullptr) static_cast<CKFlashMessageOut*>(message)->PostFlashMessage();
    m_ui8FuryShown201 = 0;
}

namespace {
CText2d* Text(CKS08InGameInterfaceCenter* hud, uint32_t slot) {
    return static_cast<CText2d*>(static_cast<IKNode2d*>(hud->m_aWidgetSlots[slot].m_pElement));
}
CKS08GameManager* Manager(CKS08InGameInterfaceCenter* hud) { return static_cast<CKS08GameManager*>(hud->m_pGameManager); }
}  // namespace

// The message shown (both texts set, the time = +0x254 + +0x258 + +0x25c, the shake started); the original inlines it.
static void ShowMessagePair(CKS08InGameInterfaceCenter* hud, IKSerializable* first, IKSerializable* second) {
    Manager(hud)->UpdateCounterTextVariables();  // 0x502a80
    if (Text(hud, 4) != nullptr) Text(hud, 4)->SetTextById(first);  // vt+0x88
    if (Text(hud, 5) != nullptr) Text(hud, 5)->SetTextById(second);
    hud->m_fUnk240 = hud->m_fUnk254 + hud->m_fUnk258 + hud->m_fUnk25c;
    static_cast<CKQuakeCpntUpdater*>(hud->m_pQuakeUpdater)->Start();
}

// 0x00536310 CKS08InGameInterfaceCenter_QueueMessage_maybe (0.0 is TOC1+0x7a2c)
void CKS08InGameInterfaceCenter::QueueMessage(IKSerializable* text) {
    if (m_fUnk240 <= 0.0f) {
        IKSerializable* title = Manager(this)->Vf214();  // vt+0x214
        ShowMessagePair(this, title, text);
        return;
    }
    const uint8_t count = m_ui8QueueCount;
    if (count > 3) return;
    m_apQueue[count][0] = Manager(this)->Vf214();
    m_apQueue[count][1] = text;
    m_ui8QueueCount = static_cast<uint8_t>(m_ui8QueueCount + 1);
}

// 0x005364e0 CKS08InGameInterfaceCenter_ShowOrQueueMessagePair_maybe
void CKS08InGameInterfaceCenter::ShowOrQueueMessagePair(IKSerializable* first, IKSerializable* second) {
    if (m_fUnk240 <= 0.0f) {
        ShowMessagePair(this, first, second);
        return;
    }
    const uint8_t count = m_ui8QueueCount;
    if (count > 3) return;
    m_apQueue[count][1] = second;
    m_apQueue[count][0] = first;
    m_ui8QueueCount = static_cast<uint8_t>(m_ui8QueueCount + 1);
}

// 0x00534810 CKS08InGameInterfaceCenter_RefreshTextElementsB8C0_maybe (CKS08InGameInterfaceBoss.cpp's range)
void CKS08InGameInterfaceCenter::RefreshTextElements() {
    if (Text(this, 5) != nullptr) {
        Text(this, 5)->SetTextById(Manager(this)->Vf214());
        Text(this, 5)->Disable();
    }
    if (Text(this, 4) != nullptr) {
        Text(this, 4)->SetTextById(Manager(this)->Vf214());
        Text(this, 4)->Disable();
    }
}

// 0x005353d0 CKS08InGameInterfaceCenter_ShowFuryGauge_maybe
void CKS08InGameInterfaceCenter::ShowFuryGauge() {
    if (m_ui8Visible268 == 0) return;
    hudside::PostMessage(this, 12);
    m_ui8FuryShown201 = 1;
    m_ui8Flags200 = static_cast<uint8_t>((m_ui8Flags200 & ~1u) | 1u);
    m_fFuryTime208 = 0.0f;
}

// 0x005352e8 CKS08InGameInterfaceCenter_ShowFuryGauge_2_maybe
void CKS08InGameInterfaceCenter::ShowFuryGauge2() {
    if (m_ui8Visible268 == 0) return;
    hudside::PostMessage(this, 12);
    m_ui8FuryShown201 = 1;
    m_ui8Flags200 = static_cast<uint8_t>(m_ui8Flags200 & ~1u);
}

// 0x00535980 CKS08InGameInterfaceCenter_UpdateVisibility_maybe (vt+0xb0)
uint8_t CKS08InGameInterfaceCenter::SetVisible(uint8_t visible) {
    m_ui8Visible268 = visible;
    bool hide = false;
    if (visible == 0) {
        CKS08GameManager* manager = Manager(this);
        hide = manager->m_gameState.m_ui8Current != 7 || g_pEngine->m_timeManager->m_pTime->m_eCurrentState != 0 ||
               g_pEngine->m_videoManager->HasVideoWithoutFlag40() || (manager->m_flags64 & 0x04000000u) != 0;
    }
    CKFlashUI* ui = static_cast<CKFlashUI*>(m_pFlashUI);
    if (ui == nullptr || (ui->m_baFlags & CKFlashUI::kStateMask) != 2) return 0;
    if (hide) {
        if ((ui->m_baFlags & CKFlashUI::kNeverRender) != 0) return 0;
        ui->m_baFlags |= CKFlashUI::kNeverRender;
        ui->HideAllHotSpotHierarchy();
        return 1;
    }
    if (m_ui8Visible268 == 0 && m_ui8FuryShown201 != 0) {
        hudside::PostMessage(this, 13);
        m_ui8FuryShown201 = m_ui8Visible268;
        ui = static_cast<CKFlashUI*>(m_pFlashUI);
        if (ui == nullptr) return 0;
    }
    if ((ui->m_baFlags & CKFlashUI::kNeverRender) == 0) return 0;
    ui->m_baFlags &= ~CKFlashUI::kNeverRender;
    return 1;
}

// 0x00535d00 CKS08InGameInterfaceCenter_UpdateMessageDisplay_maybe. 255.0 / 1.0 / 0.01 / 0.0 are TOC1+0x7a20..+0x7a2c.
void CKS08InGameInterfaceCenter::UpdateMessageDisplay(float dt) {
    CText2d* title = Text(this, 4);
    CText2d* text = Text(this, 5);
    if (title == nullptr || text == nullptr) return;
    uint8_t color[4];
    std::memcpy(color, &static_cast<IKText2d*>(text)->m_Color, 4);
    if (m_fUnk240 > 0.0f) {
        title->Enable();
        Text(this, 5)->Enable();
        const float tail = m_fUnk25c + m_fUnk258;
        const float time = m_fUnk240;
        if (time > tail) {
            // Fading in over +0x254: 255 - (time - tail) x 255 / +0x254.
            color[3] = static_cast<uint8_t>(~ppc::fctiwz((time - tail) * 255.0f / m_fUnk254));
        } else if (time > m_fUnk25c) {
            color[3] = 0xff;
        } else {
            color[3] = static_cast<uint8_t>(ppc::fctiwz(time * 255.0f / m_fUnk25c));  // fading out
        }
        static_cast<IKText2d*>(Text(this, 4))->SetColor(color);
        static_cast<IKText2d*>(Text(this, 5))->SetColor(color);
        float shake[15];
        static_cast<CKQuakeCpntUpdater*>(m_pQuakeUpdater)->EvaluateScaled(dt, 1.0f, shake);
        float sx = shake[6] + 1.0f;
        if (!(sx >= 0.01f)) sx = 0.01f;
        float sy = shake[7] + 1.0f;
        if (!(sy >= 0.01f)) sy = 0.01f;
        Text(this, 4)->m_v2ConstantScale.m_fX = sx;
        Text(this, 4)->m_v2ConstantScale.m_fY = sy;
        Text(this, 5)->m_v2ConstantScale.m_fX = sx;
        Text(this, 5)->m_v2ConstantScale.m_fY = sy;
        SetElementX(shake[0] + m_fUnk244[0], 4);
        SetElementY(shake[1] + m_fUnk244[1], 4);
        SetElementX(shake[0] + m_fUnk24c[0], 5);
        SetElementY(shake[1] + m_fUnk24c[1], 5);
        m_fUnk240 = m_fUnk240 - dt;
        return;
    }
    title->m_v2ConstantScale.m_fX = 1.0f;
    title->m_v2ConstantScale.m_fY = 1.0f;
    Text(this, 5)->m_v2ConstantScale.m_fX = 1.0f;
    Text(this, 5)->m_v2ConstantScale.m_fY = 1.0f;
    SetElementX(m_fUnk244[0], 4);
    SetElementY(m_fUnk244[1], 4);
    SetElementX(m_fUnk24c[0], 5);
    SetElementY(m_fUnk24c[1], 5);
    Text(this, 4)->SetTextById(Manager(this)->Vf214());
    Text(this, 4)->Disable();
    Text(this, 5)->SetTextById(Manager(this)->Vf214());
    Text(this, 5)->Disable();
    if (m_ui8QueueCount == 0) return;
    ShowMessagePair(this, m_apQueue[0][0], m_apQueue[0][1]);
    uint8_t count = m_ui8QueueCount;
    if (count > 1) {
        int32_t i = 1;
        do {
            m_apQueue[i - 1][1] = m_apQueue[i][1];
            m_apQueue[i - 1][0] = m_apQueue[i][0];
            count = m_ui8QueueCount;
            ++i;
        } while (static_cast<int32_t>(count) > i);
    }
    m_ui8QueueCount = static_cast<uint8_t>(count - 1);
}

// 0x005369b0 CKS08InGameInterfaceCenter_RebuildWidgetCat1Tables_maybe: for i = 10 down to 0, mark i x 0.1 (TOC1+0x7a34)
// is lit when the first gauge's displayed value reaches it or the second's (counted from the other end, 1.0 - value)
// is at or below it; its message out (1 + i) goes in group 1.
void CKS08InGameInterfaceCenter::RebuildFuryMarks() {
    ClearRefGroup(1);
    CKSuperGaugeCpntUpdater* first = static_cast<CKSuperGaugeCpntUpdater*>(m_pGaugeUpdater210);
    CKSuperGaugeCpntUpdater* second = static_cast<CKSuperGaugeCpntUpdater*>(m_pGaugeUpdater218);
    const float a = first->m_apUpdaters[0]->m_unk08;         // 0x250b18 CKGaugeCpnt_GetDisplayedValue_maybe
    const float b = 1.0f - second->m_apUpdaters[0]->m_unk08;
    for (int32_t i = 10; i >= 0; --i) {
        const float mark = static_cast<float>(i) * 0x1.99999ap-4f;  // fcfid, frsp, fmuls 0.1f
        if (!(a >= mark) && !(b <= mark)) continue;
        AddToRefGroup(VfC0()[1 + i], 1);
    }
}

// 0x00537558 CKS08InGameInterfaceCenter_ResetWidgets_maybe (vt+0x98)
void CKS08InGameInterfaceCenter::ResetWidgets() {
    CKMenuBase114c::ResetWidgets();
    m_ui8FuryShown201 = 0;
    m_ui8Flags200 = static_cast<uint8_t>(m_ui8Flags200 & ~1u);
    ClearRefGroup(0);
    ClearRefGroup(1);
    ClearRefGroup(2);
    Vf88()[0].m_unk0c = 1;
    Vf88()[1].m_unk0c = 0;
    Vf88()[2].m_unk0c = 1;
}

// 0x00536cf0 CKS08InGameInterfaceCenter_Update_maybe (vt+0xdc): the fury gauges (slots 0-1 and 2-3) ticked, their
// marks, the messages.
uint8_t CKS08InGameInterfaceCenter::OnMenuState(int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        if (Text(this, 4) != nullptr) {
            Text(this, 4)->Disable();
            SetElementX(m_fUnk244[0], 4);
            SetElementY(m_fUnk244[1], 4);
        }
        if (Text(this, 5) != nullptr) {
            Text(this, 5)->Disable();
            SetElementX(m_fUnk24c[0], 5);
            SetElementY(m_fUnk24c[1], 5);
        }
        RefreshTextElements();
        m_fFuryTime208 = 0.0f;
        m_ui8QueueCount = 0;
        m_fUnk240 = 0.0f;
    } else if (phase == 2) {
        for (uint32_t first = 0; first <= 2; first += 2) {
            if (hudside::Element(this, first) == nullptr || hudside::Element(this, first + 1) == nullptr) continue;
            hudside::Element(this, first)->Disable();
            hudside::Element(this, first + 1)->Disable();
        }
        if (Text(this, 4) != nullptr) {
            Text(this, 4)->Disable();
            SetElementX(m_fUnk244[0], 4);
            SetElementY(m_fUnk244[1], 4);
        }
        if (Text(this, 5) != nullptr) {
            Text(this, 5)->Disable();
            SetElementX(m_fUnk24c[0], 5);
            SetElementY(m_fUnk24c[1], 5);
        }
    } else if (phase == 0) {
        CKS08GameManager* manager = Manager(this);
        const float dt = g_pEngine->m_timeManager->m_pTime->m_afDeltaTime[IKTime::FIXED_GAME_TIME];
        if (hudside::FightOn(manager)) {
            if ((m_ui8Flags200 & 1) == 0 && m_ui8Visible268 != 0) {
                hudside::PostMessage(this, 12);
                m_ui8FuryShown201 = 1;
                m_ui8Flags200 = static_cast<uint8_t>((m_ui8Flags200 & ~1u) | 1u);
                m_fFuryTime208 = 0.0f;
            }
        } else if ((m_ui8Flags200 & 1) != 0) {
            m_fFuryTime208 = dt + m_fFuryTime208;
            if (m_fUnk204 <= m_fFuryTime208) {
                m_ui8Flags200 = static_cast<uint8_t>(m_ui8Flags200 & ~1u);
                hudside::PostMessage(this, 13);
                m_ui8FuryShown201 = 0;
            }
        }
        IKSerializable* updaters[2] = {m_pGaugeUpdater210, m_pGaugeUpdater218};
        for (uint32_t g = 0; g < 2; ++g) {
            const uint32_t first = g * 2;
            if (hudside::Element(this, first) == nullptr || hudside::Element(this, first + 1) == nullptr) continue;
            hudside::Element(this, first)->Enable();
            hudside::Element(this, first + 1)->Enable();
            CKSuperGaugeCpntUpdater* updater = static_cast<CKSuperGaugeCpntUpdater*>(updaters[g]);
            updater->SetFullFlag(manager->IsFuryGaugeFull2() != 0 ? 1 : 0);  // 0x4fd438
            GaugeSample samples[3];
            updater->Tick(dt, samples);
            GaugeSamples_ApplyToElements2d(updater, samples, this, static_cast<int32_t>(first), -1,
                                           static_cast<int32_t>(first + 1));
        }
        const uint32_t heroFlags = static_cast<CKGrpS08Hero*>(manager->m_unk04[1])->m_ui32PairStateFlags;  // +0x08 the hero group
        if ((heroFlags & 0x200u) != 0 || (heroFlags & 0x100u) != 0) {
            RebuildFuryMarks();
        } else {
            ClearRefGroup(1);
        }
        UpdateMessageDisplay(dt);
    }
    return static_cast<uint8_t>(GetMenuId());
}
