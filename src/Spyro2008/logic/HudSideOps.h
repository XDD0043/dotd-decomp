// HudSideOps.h - the per-frame code of the two dragon HUD screens (CKS08InGameInterfaceLeft for Spyro,
// CKS08InGameInterfaceRight for Cynder). The original has one copy per class; where the two copies are the same
// instruction for instruction (field offsets aside) they are one template here, with the class giving the fields
// that differ (HealthGaugeUpdater / ManaGaugeUpdater / PanelTime / PanelHoldTime). The functions that differ
// (UpdateShake, UpdateUpgradeText, ResetWidgets) are in each class's file.
//
// Widget slots: 0-2 the health gauge, 3-5 the mana gauge, 6 the element bar (a billboard), 7 the upgrade text,
// 8 the combo display (a text), 9 / 10 the label panel, 11-19 the shards. Message outs: 1 the panel up, 2 the panel
// down, 3 / 4 the combo display shown / hidden, 6 / 7 the label panel shown / hidden, 8 the restored clip, 9 the new
// combo, 9 + n the shard clips.
#pragma once
#include <cstdint>
#include <cstring>

#include "Spyro2008/groups/CKGrpS08Enemy.h"
#include "crt/ppc_ops.h"
#include "Spyro2008/groups/CKGrpS08Meca.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "k2000/components/CKGaugeCpntUpdater.h"
#include "k2000/components/CKQuakeCpntUpdater.h"
#include "k2000/components/CKSuperGaugeCpntUpdater.h"
#include "k2000/graphical/fx/CBillboard2d.h"
#include "k2000/graphical/ui/CKFlashMessageOut.h"
#include "k2000/graphical/ui/CText2d.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"
#include "k2000/ui/IKNode2d.h"

namespace hudside {

template <class Hud>
IKNode2d* Element(Hud* hud, uint32_t slot) {
    return static_cast<IKNode2d*>(hud->m_aWidgetSlots[slot].m_pElement);
}

// Message out `index` posted when there is one.
template <class Hud>
void PostMessage(Hud* hud, uint32_t index) {
    if (hud->VfC0()[index] != nullptr) static_cast<CKFlashMessageOut*>(hud->VfC0()[index])->PostFlashMessage();
}

template <class Hud>
CKS08GameManager* Manager(Hud* hud) {
    return static_cast<CKS08GameManager*>(hud->m_pGameManager);
}

// The enemy group's vt+0xf0: a fight is on (no group: no fight).
inline bool FightOn(CKS08GameManager* manager) {
    CKGrpS08Enemy* enemies = static_cast<CKGrpS08Enemy*>(manager->m_unk04[0]);  // +0x04
    return enemies != nullptr && enemies->IsFightOn() != 0;
}

// The game manager's +0xbe0: the element bar's speed (a float in a word).
inline float BarSpeed(CKS08GameManager* manager) {
    float speed;
    std::memcpy(&speed, &manager->m_unkBE0, 4);
    return speed;
}

template <class Hud>
IKBillboard2d* Bar(Hud* hud) {
    return static_cast<CBillboard2d*>(Element(hud, 6));
}

// 0x00537c48 / 0x00537b28 (Right 0x0053d6a0 / 0x0053d580) Update{Health,Mana}Gauge_maybe: with the three elements of the
// gauge, they are shown and the super gauge ticked onto them.
template <class Hud>
void UpdateGauge(Hud* hud, float dt, IKSerializable* updaterRef, uint32_t first) {
    if (Element(hud, first) == nullptr || Element(hud, first + 1) == nullptr || Element(hud, first + 2) == nullptr) return;
    Element(hud, first)->Enable();
    Element(hud, first + 1)->Enable();
    Element(hud, first + 2)->Enable();
    GaugeSample samples[3];
    CKSuperGaugeCpntUpdater* updater = static_cast<CKSuperGaugeCpntUpdater*>(updaterRef);
    updater->Tick(dt, samples);
    GaugeSamples_ApplyToElements2d(updater, samples, hud, first, first + 1, first + 2);
}

// 0x005379b8 (Right 0x0053d410) StepGaugeTowardTarget_maybe, inlined in the update: the element bar's height approaches
// its target (+0x250 target, +0x254 speed from the game manager, +0x258 current); when it reaches 0 the target goes back
// to the full height, the pending texture is put on and bit 1 is cleared.
template <class Hud>
void StepElementBar(Hud* hud, float dt) {
    IKBillboard2d* bar = Bar(hud);
    if (bar == nullptr) return;
    if (((hud->m_ui8Flags214 >> 1) & 1) == 0 && !(hud->m_fUnk258 != hud->m_fUnk250)) return;
    const float width = bar->m_vBillboardSize.m_fX;
    hud->m_fUnk254 = BarSpeed(Manager(hud));
    const float height = FloatApproach_Step(dt, &hud->m_fUnk250);
    bar->m_vBillboardSize.m_fY = height;
    bar->m_vBillboardSize.m_fX = width;
    if (hud->m_fUnk258 == 0.0f) {  // lfs TOC1+0x7a48 (Right +0x7b5c)
        hud->m_fUnk250 = hud->m_fUnk24c;
        bar->SetTexture(hud->m_pPendingTexture);  // vt+0x3c
        hud->m_ui8Flags214 = static_cast<uint8_t>(hud->m_ui8Flags214 & ~2u);
    }
}

// 0x00538648 (Right 0x0053e340) UpdateComboDisplay_maybe: the combo text (slot 8) back to scale 1, offset 0 and no
// rotation, then the combo gauge (+0x290) and the shake (+0x288) on it; while +0x278 runs its alpha fades from 255 to
// the minimum +0x280, after that it stays at the minimum.
template <class Hud>
void UpdateComboDisplay(Hud* hud, float dt) {
    IKNode2d* node = Element(hud, 8);
    if (node == nullptr) return;
    node->m_v2ConstantScale.m_fY = 1.0f;
    node->m_v2ConstantScale.m_fX = 1.0f;
    hud->SetElementX(0.0f, 8);
    hud->SetElementY(0.0f, 8);
    Element(hud, 8)->m_f32RotateAngle = 0.0f;
    GaugeSample sample;
    static_cast<CKGaugeCpntUpdater*>(hud->m_pGaugeUpdater290)->Update(dt, &sample);
    GaugeSample_ApplyToElement2d(&sample, hud, 8);
    float shake[15];
    static_cast<CKQuakeCpntUpdater*>(hud->m_pQuakeUpdater288)->EvaluateScaled(dt, 1.0f, shake);
    ShakeSample_ApplyToElement2d(shake, hud, 8);
    IKText2d* text = static_cast<CText2d*>(Element(hud, 8));
    uint8_t alpha;
    if (hud->m_fComboTime > 0.0f) {
        const float ratio = hud->m_fComboTime / hud->m_fUnk27c;
        const uint8_t minimum = hud->m_unk280;
        const float range = static_cast<float>(static_cast<uint8_t>(~minimum));  // fcfid + frsp
        alpha = static_cast<uint8_t>(ppc::fctiwz(range * ratio) + minimum);
        text->SetAlpha(alpha);  // vt+0x48
        reinterpret_cast<uint8_t*>(&text->m_VarColor)[3] = alpha;  // the raw colour's alpha byte (+0x6ff)
        hud->m_fComboTime = hud->m_fComboTime - dt;
    } else {
        alpha = hud->m_unk280;
        text->SetAlpha(alpha);
        reinterpret_cast<uint8_t*>(&text->m_VarColor)[3] = hud->m_unk280;
    }
}

// 0x0053b468 (Right 0x00540f08) Update_maybe (vt+0xdc). `hidesGaugesOnLeave`: Spyro's also hides the two gauges on leave.
template <class Hud>
uint8_t OnMenuState(Hud* hud, int32_t phase, bool hidesGaugesOnLeave) {
    if (phase == 1) {
        IKBillboard2d* bar = Bar(hud);
        if (bar != nullptr) {
            const float width = bar->m_vBillboardSize.m_fX;
            hud->m_fUnk24c = width;
            hud->m_fUnk258 = width;
            hud->m_fUnk250 = hud->m_fUnk24c;
            hud->m_fUnk254 = BarSpeed(Manager(hud));
            hud->m_pPendingTexture = nullptr;
            bar->m_vBillboardSize.m_fY = hud->m_fUnk24c;
            bar->m_vBillboardSize.m_fX = width;
        }
        if (Element(hud, 7) != nullptr) {
            Element(hud, 7)->Disable();
            hud->SetElementX(hud->m_fUnk234[0], 7);
            hud->SetElementY(hud->m_fUnk234[1], 7);
        }
        hud->HidePanel();
        hud->m_ui8Flags214 = static_cast<uint8_t>(hud->m_ui8Flags214 & ~3u);
    } else if (phase == 2) {
        IKBillboard2d* bar = Bar(hud);
        if (bar != nullptr) {
            const float width = bar->m_vBillboardSize.m_fX;
            bar->m_vBillboardSize.m_fY = hud->m_fUnk24c;
            bar->m_vBillboardSize.m_fX = width;
        }
        if (Element(hud, 7) != nullptr) {
            Element(hud, 7)->Disable();
            hud->SetElementX(hud->m_fUnk234[0], 7);
            hud->SetElementY(hud->m_fUnk234[1], 7);
        }
        if (hidesGaugesOnLeave) {
            for (uint32_t first = 0; first <= 3; first += 3) {
                if (Element(hud, first) == nullptr || Element(hud, first + 1) == nullptr || Element(hud, first + 2) == nullptr) {
                    continue;
                }
                Element(hud, first)->Disable();
                Element(hud, first + 1)->Disable();
                Element(hud, first + 2)->Disable();
            }
        }
        for (uint32_t group = 0; group < 4; ++group) hud->ClearRefGroup(group);
    } else if (phase == 0) {
        CKS08GameManager* manager = Manager(hud);
        IKTime* clock = g_pEngine->m_timeManager->m_pTime;
        const float scaledDt = clock->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME];
        const float dt = clock->m_afDeltaTime[IKTime::FIXED_GAME_TIME];
        // The meca group's byte +0x4c (a carried object_maybe) keeps the panel up like a fight. The original reads it
        // without a null check.
        CKGrpS08Meca* meca = static_cast<CKGrpS08Meca*>(manager->m_unk04[2]);  // +0x0c
        const bool mecaHold = meca != nullptr && ((meca->m_unk4c >> 24) & 0xffu) != 0;
        if (FightOn(manager) || mecaHold) {
            if ((hud->m_ui8Flags214 & 1) == 0) {
                PostMessage(hud, 1);
                hud->m_ui8Flags214 = static_cast<uint8_t>((hud->m_ui8Flags214 & ~1u) | 1u);
                hud->PanelTime() = 0.0f;
                hud->m_ui8Active215 = 1;
                hud->m_fUnk230 = hud->m_fUnk23c + hud->m_fUnk240;
                static_cast<CKQuakeCpntUpdater*>(hud->m_pQuakeUpdater248)->Start();
            }
        } else if ((hud->m_ui8Flags214 & 1) != 0) {
            hud->PanelTime() = scaledDt + hud->PanelTime();
            if (hud->PanelHoldTime() <= hud->PanelTime()) {
                hud->m_ui8Flags214 = static_cast<uint8_t>(hud->m_ui8Flags214 & ~1u);
                if (!FightOn(manager)) {
                    PostMessage(hud, 2);
                    hud->m_ui8Flags214 = static_cast<uint8_t>(hud->m_ui8Flags214 & ~1u);
                    hud->m_ui8Active215 = 0;
                    return static_cast<uint8_t>(hud->GetMenuId());
                }
            }
        }
        if (hud->m_ui8Active215 != 0) {
            UpdateGauge(hud, dt, hud->HealthGaugeUpdater(), 0);
            UpdateGauge(hud, dt, hud->ManaGaugeUpdater(), 3);
            StepElementBar(hud, dt);
            hud->UpdateUpgradeText(dt);
            UpdateComboDisplay(hud, dt);
            hud->UpdateShake(dt, scaledDt);
        }
    }
    return static_cast<uint8_t>(hud->GetMenuId());
}

// 0x00538da8 (Right 0x0053e848) vf58: the base's Resume, then the combo text shown again while its time runs.
template <class Hud>
void ResumeCombo(Hud* hud) {
    if (0.0f < hud->m_fComboTime && Element(hud, 8) != nullptr) Element(hud, 8)->Enable();
}

// 0x0053b278 (Right 0x0053e9c0) OnNewComboHit_maybe
template <class Hud>
void OnNewComboHit(Hud* hud, float value) {
    hud->AddToRefGroup(hud->VfC0()[9], 3);
    static_cast<CKQuakeCpntUpdater*>(hud->m_pQuakeUpdater288)->Start();
    SetGaugeValue(static_cast<CKGaugeCpntUpdater*>(hud->m_pGaugeUpdater290), value, 1);
    hud->m_fComboTime = hud->m_fUnk27c;
}

// 0x0053a1c8 (Right 0x00540208) OnComboHit_maybe
template <class Hud>
void OnComboHit(Hud* hud, float value) {
    if (Element(hud, 8) == nullptr) return;
    Element(hud, 8)->Enable();
    PostMessage(hud, 3);
    static_cast<CKQuakeCpntUpdater*>(hud->m_pQuakeUpdater288)->Start();
    SetGaugeValue(static_cast<CKGaugeCpntUpdater*>(hud->m_pGaugeUpdater290), value, 1);
    hud->m_fComboTime = hud->m_fUnk27c;
}

// 0x0053a0d0 (Right 0x0053fd88) EndComboDisplay_maybe
template <class Hud>
void EndComboDisplay(Hud* hud) {
    if (Element(hud, 8) == nullptr) return;
    Element(hud, 8)->Disable();
    PostMessage(hud, 4);
    static_cast<CKQuakeCpntUpdater*>(hud->m_pQuakeUpdater288)->Stop();
    SetGaugeValue(static_cast<CKGaugeCpntUpdater*>(hud->m_pGaugeUpdater290), 0.0f, 1);
}

// 0x0053a738 (Right 0x00540100) CloseTimedPanel_maybe
template <class Hud>
void CloseTimedPanel(Hud* hud) {
    if (FightOn(Manager(hud))) return;
    PostMessage(hud, 2);
    hud->m_ui8Flags214 = static_cast<uint8_t>(hud->m_ui8Flags214 & ~1u);
    hud->m_ui8Active215 = 0;
}

// 0x00538c98 (Right 0x0053e738) SetPanelElementObject_maybe
template <class Hud>
void SetPanelElementObject(Hud* hud, RwTexture* texture) {
    if (Bar(hud) != nullptr) Bar(hud)->SetTexture(texture);
}

// 0x00538e20 SpyroElementHud_SelectElement_maybe (Right 0x0053e8c0 CynderElementHud_SelectElement_maybe): the bar runs
// down from its current height (+0x40) to 0, then the texture goes on.
template <class Hud>
void SelectElement(Hud* hud, RwTexture* texture) {
    if (Element(hud, 6) == nullptr) return;
    hud->m_pPendingTexture = texture;
    hud->m_fUnk258 = Bar(hud)->m_vBillboardSize.m_fY;
    hud->m_fUnk250 = 0.0f;
    hud->m_ui8Flags214 = static_cast<uint8_t>((hud->m_ui8Flags214 & ~2u) | 2u);
}

// 0x00539950 / 0x00539b88 (Right 0x0053f1c0 / 0x0053f3f8) Set{Mana,Health}ShardGauge_maybe: one row's count from the
// shards left (`size` - count, 0 -> `size`), the other row cleared, the rows' time restarted; with `shake` the last
// shard's quake started and its clip (message out 9 + count) put in group `group`.
template <class Hud>
void SetShardGauge(Hud* hud, uint8_t count, uint8_t shake, bool rowA, uint8_t size, uint32_t group) {
    hud->m_ui8ShardShake = shake;
    uint8_t& row = rowA ? hud->m_ui8ShardsA : hud->m_ui8ShardsB;
    uint8_t& other = rowA ? hud->m_ui8ShardsB : hud->m_ui8ShardsA;
    other = 0;
    row = static_cast<uint8_t>(size - count);
    if (row == 0) row = size;
    hud->m_fShardTime = hud->m_fUnk268 + hud->m_fUnk26c;
    if (hud->m_ui8ShardShake == 0) return;
    static_cast<CKQuakeCpntUpdater*>(hud->m_pQuakeUpdater274)->Start();
    hud->AddToRefGroup(hud->VfC0()[static_cast<uint8_t>(row + 9)], group);
}

// One shard row of UpdateShake (0x00537e88 / Right 0x0053d8e0): while its count and the time run, each shard billboard
// is shown, white up to the count (grey 0x40 with alpha 0xc8 past it; the last one counts only while it shakes), fading
// over the last +0x26c seconds; the last shard shakes (quake +0x274: offset and scale). After the row the time is
// decreased by `scaledDt`. Otherwise the count is cleared and the billboards hidden.
template <class Hud>
void UpdateShardRow(Hud* hud, uint8_t& count, uint32_t first, uint32_t n, float dt, float scaledDt) {
    if (count == 0 || !(hud->m_fShardTime > 0.0f)) {
        count = 0;
        for (uint32_t i = 0; i < n; ++i) Element(hud, first + i)->Disable();
        return;
    }
    for (uint32_t i = 0; i < n; ++i) {
        IKNode2d* node = Element(hud, first + i);
        node->Enable();
        const uint8_t lit = static_cast<uint8_t>(count - (hud->m_ui8ShardShake == 0 ? 1 : 0));
        uint8_t color[4];
        const bool dim = lit <= i;
        color[0] = color[1] = color[2] = dim ? 0x40 : 0xff;
        if (hud->m_fShardTime > hud->m_fUnk26c) {
            color[3] = dim ? 0xc8 : 0xff;
        } else {
            const float scale = dim ? 200.0f : 255.0f;  // TOC1+0x7a50 / +0x7a4c (Right +0x7b64 / +0x7b60)
            color[3] = static_cast<uint8_t>(ppc::fctiwz(hud->m_fShardTime * scale / hud->m_fUnk26c));
        }
        static_cast<CBillboard2d*>(node)->SetColor(color);  // IKBillboard2d vt+0x28
        if (static_cast<int32_t>(count) - 1 != static_cast<int32_t>(i) || hud->m_ui8ShardShake == 0) continue;
        float shake[15];
        static_cast<CKQuakeCpntUpdater*>(hud->m_pQuakeUpdater274)->EvaluateScaled(dt, 1.0f, shake);
        float sx = shake[6] + 1.0f;
        if (!(sx >= 0.01f)) sx = 0.01f;
        float sy = shake[7] + 1.0f;
        if (!(sy >= 0.01f)) sy = 0.01f;
        node->m_v2ConstantScale.m_fY = sy;
        node->m_v2ConstantScale.m_fX = sx;
        hud->SetElementX(shake[0], first + i);
        hud->SetElementY(shake[1], first + i);
    }
    hud->m_fShardTime = hud->m_fShardTime - scaledDt;
}

}  // namespace hudside
