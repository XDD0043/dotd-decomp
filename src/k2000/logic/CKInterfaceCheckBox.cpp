// CKInterfaceCheckBox.cpp - reconstructed original translation unit 0x52e458-0x533848 (GAME_TOC1, main_toc1), 32 functions, 31 live.
// Primary class: CKInterfaceCheckBox  key 0xa14c  category Logic  size 0x79c  vtable 0xb2bb70
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x52e458  CKInterfaceCheckBox_Delete
//   [x] 0x52e4a8  CKInterfaceCheckBox_Show
//   [x] 0x52e620  CKInterfaceCheckBox_Hide
//   [x] 0x52e798  CKInterfaceCheckBox_vf80
//   [ ] 0x52e920  RegisterCKInterfaceCheckBoxClass
//   [ ] 0x52e998  _GLOBAL__I_52e998
//   [x] 0x52e9a8  CKInterfaceCheckBox_ApplyStateChange_maybe
//   [x] 0x52ee48  CKInterfaceCheckBox_SetVisualState
//   [x] 0x52fcd0  CKInterfaceCheckBox_LoadOptionValue
//   [x] 0x530080  CKInterfaceCheckBox_AnimatePart
//   [ ] 0x530258  CKInterfaceCheckBox_Save
//   [x] 0x530280  CKInterfaceCheckBox_RecursiveRegistration
//   [x] 0x530628  CKInterfaceCheckBox_Construct_2  (the same code as 0x531238 CKInterfaceCheckBox_Construct)
//   [x] 0x530aa8  CKInterfaceCheckBox_DeleteArray
//   [x] 0x530b48  CKInterfaceCheckBox_BaseDestructor  (the same code as 0x5326d8 CKInterfaceCheckBox_Destructor)
//   [ ] 0x530c48  CKInterfaceCheckBox_ComputeAnimRate_maybe  [dead]
//   [x] 0x530ca0  CKInterfaceCheckBox_SetDisabled
//   [x] 0x530dc8  CKInterfaceCheckBox_SetPosition
//   [x] 0x5310e0  CKInterfaceCheckBox_Update
//   [x] 0x531238  CKInterfaceCheckBox_Construct
//   [x] 0x5316b8  CKInterfaceCheckBox_UpdateVisibility
//   [x] 0x531b18  CKInterfaceCheckBox_StartFadeOut
//   [x] 0x531ba0  CKInterfaceCheckBox_Close
//   [x] 0x531dc8  CKInterfaceCheckBox_SetInteractionState
//   [x] 0x531f20  CKInterfaceCheckBox_PostLoad
//   [x] 0x531f28  CKInterfaceCheckBox_Destroy
//   [x] 0x5320f0  CKInterfaceCheckBox_Open
//   [x] 0x5325c8  CKInterfaceCheckBox_DeletingDestructor  (0x5326d8 CKInterfaceCheckBox_Destructor, then the delete)
//   [x] 0x5326d8  CKInterfaceCheckBox_Destructor
//   [x] 0x5327d8  CKInterfaceCheckBox_CreateArray
//   [x] 0x532d88  CKInterfaceCheckBox_Create
//   [x] 0x533280  CKInterfaceCheckBox_Load
//
//   [x] 0x9c8768  CKInterfaceCheckBox_IsKindOfClass  [inline]
//   [x] 0x9c8798  CKInterfaceCheckBox_GetClassType  [inline]
//   [x] 0x9c87a0  CKInterfaceCheckBox_GetClassID  [inline]
//   [x] 0x9c87a8  CKInterfaceCheckBox_IsFadeOutFinished_maybe  [inline]
//   [x] 0x9c87d0  CKInterfaceCheckBox_vf88  [inline]
//   [x] 0x9c87d8  CKInterfaceCheckBox_vf8C  [inline]
//   [x] 0x9c87e0  CKInterfaceCheckBox_LoadStateVisual_maybe  [inline]
#include "crt/xlround.h"
#include "k2000/logic/CKInterfaceCheckBox.h"

#include <cstring>

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rt2d/Rt2d.h"
#include "Spyro2008/logic/CKMenuBase114c.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "crt/ppc_ops.h"
#include "k2000/components/CKLocTextAccessor.h"
#include "k2000/core/Stub.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/graphical/fx/CBillboard2d.h"
#include "k2000/graphical/system/CKVideoSegment.h"
#include "k2000/graphical/system/IKVideo.h"
#include "k2000/graphical/ui/CFlashHotSpot.h"
#include "k2000/graphical/ui/CText2d.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/system/IKTime.h"

class CKInput;

namespace {

// ---- callees in other units, not ported there yet (local copies; see the C1.6 report's `needs`) ----

// The game manager's edited options (CDefaultGameManager::m_editedOptions, +0xec) by the byte offset the
// original reads: +0xf0 subtitles, +0xf1 tutorial, +0x108/+0x109 pad 1/2 vibration, +0x10a/+0x10b and
// +0x10c/+0x10d two per-player pairs, +0x119/+0x11a pad 1/2 motion sensor. The toggles are the game
// manager's (CDefaultGameManager.cpp).
uint8_t OptionByte(const CDefaultGameManager* manager, uint32_t offset) {
    const SGameOptions& o = manager->m_editedOptions;
    switch (offset) {
    case 0xf0: return o.m_bSubtitles;
    case 0xf1: return o.m_unk05;
    case 0x108: return o.m_abVibration[0];
    case 0x109: return o.m_abVibration[1];
    case 0x10a: return o.m_abUnk1E[0];
    case 0x10b: return o.m_abUnk1E[1];
    case 0x10c: return o.m_abUnk20[0];
    case 0x10d: return o.m_abUnk20[1];
    case 0x119: return o.m_abMotionSensor[0];
    case 0x11a: return o.m_abMotionSensor[1];
    default: return 0;
    }
}

// 0x00514668 KBase730C_CallOwnerVfDCObjectVf78AfterVf308_maybe (KBase730C.cpp, unticked there): the
// interface video stopped, its segment kept as the game manager's interface segment (vt+0x308).
void KBase730C_StopInterfaceVideo(CKMenuBase114c* menu) {
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(menu->m_pGameManager);
    IKVideo* video = manager->GetInterfaceVideo();  // vt+0xdc
    if (video != nullptr) {
        manager->SetInterfaceSegment(video->m_pSegment);  // vt+0x308
        video->Stop();                                    // vt+0x78
    }
}

// 0x0005b098 CBillboard2d_SetAnimTime_maybe: the sprite-sheet animation's duration (+0x74); 0 resets the
// four UVs to the whole texture and applies them (vt+0x34, BillboardBrush_ApplyUV).
void CBillboard2d_SetAnimTime(CBillboard2d* billboard, float duration) { billboard->SetAnimTime(duration); }  // the CBillboard2d port

// 0x0005b118 CBillboard2d_SetSpriteSheetRows_maybe: the cells along u (0 counts as 1); the animation restarts.
void CBillboard2d_SetSpriteSheetRows(CBillboard2d* billboard, uint32_t cells) { billboard->SetSpriteSheetRows(static_cast<int32_t>(cells)); }

// 0x0005b158 CBillboard2d_SetSpriteSheetColumns_maybe: the cells along v (0 counts as 1); the same restart.
void CBillboard2d_SetSpriteSheetColumns(CBillboard2d* billboard, uint32_t cells) { billboard->SetSpriteSheetColumns(static_cast<int32_t>(cells)); }

// 0x00066cb8 BillboardBrush_SetTexture (IKBillboard2d vt+0x3c, not overridden): the brush's texture
// when it differs; 1 when the brush has it afterwards.
uint8_t BillboardBrush_SetTexture(IKBillboard2d* billboard, void* texture) {
    Rt2dBrush* brush = billboard->m_pBrush;
    if (brush == nullptr) return 0;
    if (brush->texture == static_cast<RwTexture*>(texture)) return 1;
    return Rt2dBrushSetTexture(brush, static_cast<RwTexture*>(texture)) != nullptr ? 1 : 0;
}

// 0x009972d0 BillboardBrush_SetSize_maybe (IKBillboard2d vt+0x30, not overridden).
void BillboardBrush_SetSize(IKBillboard2d* billboard, const CVector2& size) {
    billboard->m_vBillboardSize.m_fX = size.m_fX;
    billboard->m_vBillboardSize.m_fY = size.m_fY;
}

// 0x00112bc0 CKSoundDictionaryID_GetSound (no bounds check)
CKSound* CKSoundDictionaryID_GetSound(IKSerializable* dictionary, uint32_t index) {
    return static_cast<CKSoundDictionaryID*>(dictionary)->GetSound(index);  // the audio port
}

// 0x00111818 CKSound_UpdatePan_maybe (CKSound::UpdatePan, k2000/logic/sound/CKSound.cpp).
void CKSound_UpdatePan(CKSound* sound) { sound->UpdatePan(); }  // the audio port

// 0x00111b70 CKSound_ResetPan_maybe: flag 4 (the position from the pan) set to `usePan`, the pan centred.
void CKSound_ResetPan(CKSound* sound, uint32_t usePan) { sound->ResetPan(static_cast<int32_t>(usePan)); }  // the audio port

// 0x00111230 CKSound_Play: SoundBackend_PlaySound_maybe 0x119e50 (engine +0x1c, its +0x08); returns 1.
// The callers here pass f1 = 0.0, which reaches 0x119e50 unchanged (CKSound::Play).
void CKSound_Play(CKSound* sound, float delay) { sound->Play(delay); }  // the audio port

// ---- the class's inlined helpers ----

// 0x00c50d64 g_nullVector (statically and live (0, 0, 0)).
const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};

// The RenderWare PrtStd structures CParticlesNodeFx points to: Renderware/rpprtstd/RpPrtStd.h (the point
// list's +0x10 is the points, RwV3d, 12 bytes each; the emitter's +0x04 its flags).

// Inlined in SetVisualState (0x0052f028; the buttons' SetVisualState inline the same): one emission at
// the null vector: the point appended (64 at most; scene flag 0x2000), the node activated (0x600 set,
// 0x80000 cleared), the speed adjustment 0, the emitter's flags 0xa set.
void ParticlesEmitOnce(CParticlesNodeFx* fx) {
    if (fx->m_ui8NbActivePoints <= 0x3f) {
        RwV3d& point = fx->m_pAdvEmtPointList->pointList[fx->m_ui8NbActivePoints];
        point.x = kNullVector.x;
        point.y = kNullVector.y;
        point.z = kNullVector.z;
        fx->m_sgProperties = (fx->m_sgProperties & ~0x2000u) | 0x2000u;
        fx->m_ui8NbActivePoints = static_cast<uint8_t>(fx->m_ui8NbActivePoints + 1);
    }
    uint32_t properties = fx->m_sgProperties;
    properties = (properties & ~0x200u) | 0x200u;
    properties = (properties & ~0x400u) | 0x400u;
    fx->m_sgProperties = properties & ~0x80000u;
    fx->m_fEmissionSpeedAdjustment = 0.0f;
    fx->m_pRpPrtStdEmitter->flag |= 0xa;
}

// Inlined in Open (0x0053226c): the node deactivated (0x80400 cleared), the emitter's flag 8 cleared.
void ParticlesStop(CParticlesNodeFx* fx) {
    fx->m_sgProperties &= 0xfff7fbffu;
    fx->m_pRpPrtStdEmitter->flag &= ~0x8u;
}

// The string of a CKLocTextAccessor (CKLocTextAccessor *): its list's entry `index` when the list has a
// block, else its single text.
IKSerializable* AccessorText(IKSerializable* accessor, uint32_t index) {
    CKLocTextAccessor* texts = static_cast<CKLocTextAccessor*>(accessor);
    if (texts->m_texts.m_pBlock != nullptr) return texts->m_texts.m_pBlock[index];
    return texts->m_pText;
}

// The sound / state mapping SetVisualState inlines three times (its default 0xff is unreachable there).
uint8_t SoundIndexForState(uint8_t state) {
    switch (state) {
    case 2: return 0;
    case 3: return 1;
    case 6: return 2;
    case 7: return 3;
    case 8: return 4;
    case 9: return 5;
    default: return 0xff;
    }
}

// fabs as the original does it: the sign bit cleared in memory (clrlwi 1).
float ClearSign(float x) {
    uint32_t bits;
    std::memcpy(&bits, &x, 4);
    bits &= 0x7fffffffu;
    std::memcpy(&x, &bits, 4);
    return x;
}

// A raw colour with its alpha (the word's 4th byte in memory) scaled by `fade`: the byte through fcfid /
// frsp, fmuls, fctiwz, stored back as a byte.
void FadedColor(uint32_t raw, float fade, uint8_t out[4]) {
    std::memcpy(out, &raw, 4);
    out[3] = static_cast<uint8_t>(ppc::fctiwz(static_cast<float>(out[3]) * fade));
}

// SetPosition's search: the hot spot's 2D entry for `node`, from the last.
SAttached2dObject* FindAttached2d(CFlashHotSpot* hotSpot, IKSerializable* node) {
    for (uint32_t i = hotSpot->m_vp2dObject.m_ui32NbUsedElt; i-- != 0;) {
        SAttached2dObject* entry = &hotSpot->m_vp2dObject.m_pBlock[i];
        if (entry->m_pNode == static_cast<IKNode2d*>(node)) return entry;
    }
    return nullptr;
}

void SetAttachedOffset(CFlashHotSpot* hotSpot, IKSerializable* node, float x, float y) {
    if (SAttached2dObject* entry = FindAttached2d(hotSpot, node)) entry->m_vPosOffset.m_fX = x;
    if (SAttached2dObject* entry = FindAttached2d(hotSpot, node)) entry->m_vPosOffset.m_fY = y;
}

IKNode2d* Node(IKSerializable* object) { return static_cast<IKNode2d*>(object); }

}  // namespace

// 0x0052e4a8 CKInterfaceCheckBox_Show: the shown bit, then every element's Enable (vt+0x64).
void CKInterfaceCheckBox::Show() {
    m_baFlags = static_cast<uint8_t>(m_baFlags | kFlagShown);
    if (m_unk34 != nullptr) Node(m_unk34)->Enable();
    if (m_unk38 != nullptr) Node(m_unk38)->Enable();
    for (uint32_t i = 4; i-- != 0;) {
        if (m_apUnk3c[i] != nullptr) Node(m_apUnk3c[i])->Enable();
    }
}

// 0x0052e620 CKInterfaceCheckBox_Hide: the shown bit cleared, then every element's Disable (vt+0x68).
void CKInterfaceCheckBox::Hide() {
    m_baFlags = static_cast<uint8_t>(m_baFlags & ~kFlagShown);
    if (m_unk34 != nullptr) Node(m_unk34)->Disable();
    if (m_unk38 != nullptr) Node(m_unk38)->Disable();
    for (uint32_t i = 4; i-- != 0;) {
        if (m_apUnk3c[i] != nullptr) Node(m_apUnk3c[i])->Disable();
    }
}

// 0x0052e798 CKInterfaceCheckBox_vf80: every element's vt+0x84 (Render) with the argument, billboards first.
void CKInterfaceCheckBox::Vf80(IKTime* frameClock) {
    for (uint32_t i = 4; i-- != 0;) {
        if (m_apUnk3c[i] != nullptr) Node(m_apUnk3c[i])->Render(frameClock);
    }
    if (m_unk38 != nullptr) Node(m_unk38)->Render(frameClock);
    if (m_unk34 != nullptr) Node(m_unk34)->Render(frameClock);
}

// 0x0052e9a8 CKInterfaceCheckBox_ApplyStateChange_maybe
void CKInterfaceCheckBox::ApplyStateChange(uint8_t state) {
    if ((m_baCheckFlags & kCheckNoActions) != 0) return;
    CDefaultGameManager* manager = g_pEngine->m_gameManager;
    switch (m_ui8Option & 0xf) {
    case 1: manager->ToggleSubtitlesOption(); break;
    case 2: manager->ToggleVibrationBothPlayers(); break;
    case 3: manager->TogglePlayerVibration(0); break;
    case 4: manager->TogglePlayerVibration(1); break;
    case 5: manager->TogglePerPlayerOption1EBothPlayers(); break;
    case 6: manager->TogglePerPlayerOption1E(0); break;
    case 7: manager->TogglePerPlayerOption1E(1); break;
    case 8: manager->TogglePerPlayerOption20BothPlayers(); break;
    case 9: manager->TogglePerPlayerOption20(0); break;
    case 10: manager->TogglePerPlayerOption20(1); break;
    case 11: manager->ToggleMotionSensorBothPlayersOption(); break;
    case 12: manager->ToggleMotionSensorOption(0); break;
    case 13: manager->ToggleMotionSensorOption(1); break;
    case 14: manager->ToggleOption05(); break;
    default: break;
    }

    StateVisual& visual = m_aStates[state];
    // The videos, from the last: a segment plays in its default mode; without one the video starts. The
    // interface video is stopped first either way.
    for (uint32_t i = visual.m_aVideos.m_ui32NbUsedElt; i-- != 0;) {
        CKInterfaceButton::RefPair& entry = visual.m_aVideos.m_pBlock[i];
        if (entry.m_second != nullptr) {
            KBase730C_StopInterfaceVideo(static_cast<CKMenuBase114c*>(m_pMenu));
            static_cast<CKVideoSegment*>(visual.m_aVideos.m_pBlock[i].m_second)->Play(CKVideoSegment::kModeDefault, 0, 0);
        } else if (entry.m_first != nullptr) {
            KBase730C_StopInterfaceVideo(static_cast<CKMenuBase114c*>(m_pMenu));
            static_cast<IKVideo*>(visual.m_aVideos.m_pBlock[i].m_first)->Start(nullptr);  // vt+0x60
        }
    }
    // The texts, from the last: the accessor's first string, then the colour.
    for (uint32_t i = visual.m_aTexts.m_ui32NbUsedElt; i-- != 0;) {
        CKInterfaceButton::RefPairValue& entry = visual.m_aTexts.m_pBlock[i];
        if (entry.m_first == nullptr) continue;
        CText2d* text = static_cast<CText2d*>(entry.m_first);
        text->SetTextById(AccessorText(entry.m_second, 0));  // vt+0x88
        const uint32_t color = visual.m_aTexts.m_pBlock[i].m_valueRaw;
        static_cast<IKText2d*>(static_cast<CText2d*>(visual.m_aTexts.m_pBlock[i].m_first))
            ->SetColor(reinterpret_cast<const uint8_t*>(&color));  // IKText2d vt+0x44
    }
    // The billboards, from the last: texture, then the sprite-sheet animation.
    for (uint32_t i = visual.m_aBillboards.m_ui32NbUsedElt; i-- != 0;) {
        CKInterfaceButton::TextEntry& entry = visual.m_aBillboards.m_pBlock[i];
        if (entry.m_pText == nullptr || entry.m_pTexture == nullptr) continue;
        CBillboard2d* billboard = static_cast<CBillboard2d*>(entry.m_pText);
        BillboardBrush_SetTexture(billboard, entry.m_pTexture);  // IKBillboard2d vt+0x3c
        float duration;
        std::memcpy(&duration, &entry.m_unk08, 4);  // lfs: the word is a float
        CBillboard2d_SetAnimTime(billboard, duration);
        CBillboard2d_SetSpriteSheetRows(billboard, entry.m_unk0c);
        CBillboard2d_SetSpriteSheetColumns(billboard, entry.m_unk10);
    }
}

// 0x0052ee48 CKInterfaceCheckBox_SetVisualState
void CKInterfaceCheckBox::SetVisualState(uint8_t state) {
    const uint8_t previous = m_ui8State;
    if (previous == state) return;
    m_ui8State = state;
    m_baFlags = static_cast<uint8_t>(m_baFlags | kFlagFading);

    // The size ramps towards the state's sizes. The width of billboard 1 moves at m_fAnimSpeed; when it
    // changes, every other ramp's speed is scaled so that all of them arrive together.
    const StateVisual& target = m_aStates[m_ui8State];
    const float dx = target.m_avSizes[1].m_fX - m_aWidthRamps[1][0];
    m_aWidthRamps[1][1] = m_fAnimSpeed;
    if (dx == 0.0f) {  // TOC +0x78c8
        for (uint32_t i = 4; i-- != 0;) {
            if (i != 1) m_aWidthRamps[i][1] = m_fAnimSpeed;
            m_aHeightRamps[i][1] = m_fAnimSpeed;
            m_aWidthRamps[i][0] = m_aStates[m_ui8State].m_avSizes[i].m_fX;
            m_aHeightRamps[i][0] = m_aStates[m_ui8State].m_avSizes[i].m_fY;
        }
    } else {
        m_aHeightRamps[1][1] = m_fAnimSpeed * ClearSign((target.m_avSizes[1].m_fY - m_aHeightRamps[1][0]) / dx);
        for (uint32_t i = 4; i-- != 0;) {
            const CVector2& size = m_aStates[m_ui8State].m_avSizes[i];
            if (i != 1) {
                m_aWidthRamps[i][1] = m_fAnimSpeed * ClearSign((size.m_fX - m_aWidthRamps[i][0]) / dx);
                m_aHeightRamps[i][1] = m_fAnimSpeed * ClearSign((size.m_fY - m_aHeightRamps[i][0]) / dx);
            }
            m_aWidthRamps[i][0] = size.m_fX;
            m_aHeightRamps[i][0] = size.m_fY;
        }
    }

    // The texts: string (unless kept) and colour. With a value text, the label's colour is set again.
    if (m_unk34 != nullptr) {
        CText2d* label = static_cast<CText2d*>(m_unk34);
        if ((m_baCheckFlags & kCheckKeepLabelText) == 0) label->SetTextById(AccessorText(m_aStates[m_ui8State].m_pTexts, 0));
        const uint32_t color = m_aStates[m_ui8State].m_labelColorRaw;
        static_cast<IKText2d*>(static_cast<CText2d*>(m_unk34))->SetColor(reinterpret_cast<const uint8_t*>(&color));
    }
    if (m_unk38 != nullptr) {
        CText2d* value = static_cast<CText2d*>(m_unk38);
        if ((m_baCheckFlags & kCheckKeepValueText) == 0) value->SetTextById(AccessorText(m_aStates[m_ui8State].m_pTexts, 1));
        // BUG(original): the label (+0x34) is not tested here (every live box has both texts).
        const uint32_t labelColor = m_aStates[m_ui8State].m_labelColorRaw;
        static_cast<IKText2d*>(static_cast<CText2d*>(m_unk34))->SetColor(reinterpret_cast<const uint8_t*>(&labelColor));
        const uint32_t valueColor = m_aStates[m_ui8State].m_valueColorRaw;
        static_cast<IKText2d*>(static_cast<CText2d*>(m_unk38))->SetColor(reinterpret_cast<const uint8_t*>(&valueColor));
    }

    // The billboards, the last first: texture (when the state has one), colour, blend mode, animation.
    for (uint32_t i = 4; i-- != 0;) {
        if (m_apUnk3c[i] == nullptr) continue;
        CBillboard2d* billboard = static_cast<CBillboard2d*>(m_apUnk3c[i]);
        if (m_aStates[m_ui8State].m_apTextures[i] != nullptr) {
            BillboardBrush_SetTexture(billboard, m_aStates[m_ui8State].m_apTextures[i]);  // IKBillboard2d vt+0x3c
        }
        const uint32_t color = m_aStates[m_ui8State].m_aColorsRaw[i];
        static_cast<IKBillboard2d*>(static_cast<CBillboard2d*>(m_apUnk3c[i]))
            ->SetColor(reinterpret_cast<const uint8_t*>(&color));  // IKBillboard2d vt+0x28
        static_cast<CBillboard2d*>(m_apUnk3c[i])->m_bUseAlpha = m_aStates[m_ui8State].m_aBlendModes[i];
        CBillboard2d_SetAnimTime(static_cast<CBillboard2d*>(m_apUnk3c[i]), m_aStates[m_ui8State].m_afAnimDurations[i]);
        CBillboard2d_SetSpriteSheetRows(static_cast<CBillboard2d*>(m_apUnk3c[i]), m_aStates[m_ui8State].m_aSheetCellsU[i]);
        CBillboard2d_SetSpriteSheetColumns(static_cast<CBillboard2d*>(m_apUnk3c[i]), m_aStates[m_ui8State].m_aSheetCellsV[i]);
    }

    // The focused states' sound (only once the box has been updated, i.e. not while it opens).
    if ((m_baFlags & kFlagUpdated) != 0 && state <= 9) {
        const uint8_t sound = SoundIndexForState(state);
        if (sound != 0xff && CKSoundDictionaryID_GetSound(m_pSounds, sound & 7) != nullptr) {
            CKSound_ResetPan(CKSoundDictionaryID_GetSound(m_pSounds, sound), 1);
            CKSound_Play(CKSoundDictionaryID_GetSound(m_pSounds, sound), 0.0f);  // f1 = TOC +0x78c8
        }
    }

    // The state's particles emit once.
    if (m_aStates[state].m_pParticles != nullptr) {
        ParticlesEmitOnce(static_cast<CParticlesNodeFx*>(m_aStates[state].m_pParticles));
    }

    // The option toggles on the transition states: a plain box when it enters 8 while checked or 9
    // while unchecked (the toggle SetInteractionState(1) just made); a hold box when it leaves 8 while
    // unchecked or 9 while checked.
    if ((m_baFlags & kFlagHold) == 0) {
        if ((m_baCheckFlags & kCheckChecked) != 0) {
            if (m_ui8State == 8) ApplyStateChange(m_ui8State);
        } else if (m_ui8State == 9) {
            ApplyStateChange(m_ui8State);
        }
    } else if ((m_baCheckFlags & kCheckChecked) == 0) {
        if (previous == 8) ApplyStateChange(m_ui8State);
    } else if (previous == 9) {
        ApplyStateChange(m_ui8State);
    }
    // A box without an option runs every other state's actions.
    if (static_cast<uint8_t>(m_ui8State - 8) > 1 && (m_ui8Option & 0xf) == 0) ApplyStateChange(state);
}

// 0x0052fcd0 CKInterfaceCheckBox_LoadOptionValue
void CKInterfaceCheckBox::LoadOptionValue() {
    CDefaultGameManager* manager = g_pEngine->m_gameManager;
    bool known = true;
    bool checked = false;
    switch (m_ui8Option & 0xf) {
    case 1: checked = OptionByte(manager, 0xf0) != 0; break;
    case 2:  // BUG(original)_maybe: "both pads" shows pad 1's vibration only (the same table entry as 3)
    case 3: checked = OptionByte(manager, 0x108) != 0; break;
    case 4: checked = OptionByte(manager, 0x109) != 0; break;
    case 5: checked = OptionByte(manager, 0x10a) != 0 && OptionByte(manager, 0x10b) != 0; break;
    case 6: checked = OptionByte(manager, 0x10a) != 0; break;
    case 7: checked = OptionByte(manager, 0x10b) != 0; break;
    case 8: checked = OptionByte(manager, 0x10c) != 0 && OptionByte(manager, 0x10d) != 0; break;
    case 9: checked = OptionByte(manager, 0x10c) != 0; break;
    case 10: checked = OptionByte(manager, 0x10d) != 0; break;
    case 11: checked = OptionByte(manager, 0x119) != 0 && OptionByte(manager, 0x11a) != 0; break;
    case 12: checked = OptionByte(manager, 0x119) != 0; break;
    case 13: checked = OptionByte(manager, 0x11a) != 0; break;
    case 14: checked = OptionByte(manager, 0xf1) != 0; break;
    default: known = false; break;  // 0 and 15: the checked bit is kept
    }
    if (known) {
        m_baCheckFlags = static_cast<uint8_t>((m_baCheckFlags & ~kCheckChecked) | (checked ? kCheckChecked : 0));
    }
    // Pad 2's options (4, 7, 10, 13) are disabled with one player, except in the main menu (state 6).
    const uint32_t option = m_ui8Option & 0xf;
    if (option <= 0xd && ((1u << option) & 0x2490u) != 0 &&
        static_cast<CKS08GameManager*>(manager)->m_gameState.m_ui8Current != 6) {
        SetDisabled(manager->GetPlayerCount() <= 1 ? 1 : 0);  // vt+0x84, vt+0x154
    }
    uint8_t visual = (m_baCheckFlags & kCheckChecked) != 0 ? 0 : 4;
    if ((m_baFlags & kFlagDisabled) != 0) visual = static_cast<uint8_t>(visual + 1);
    if ((m_baCheckFlags & kCheckFocused) != 0) visual = static_cast<uint8_t>(visual + 2);
    SetVisualState(visual);
}

// 0x00530080 CKInterfaceCheckBox_AnimatePart
void CKInterfaceCheckBox::AnimatePart(IKSerializable* element, float* widthRamp, float* heightRamp,
                                      IKTime* frameClock, uint8_t isBillboard) {
    CVector2 size = {0.0f, 0.0f};
    if (m_fFadeOutTime <= 0.0f) {
        // A ramp without speed jumps to its target.
        if (widthRamp[1] <= 0.0f) widthRamp[2] = widthRamp[0];
        if (heightRamp[1] <= 0.0f) heightRamp[2] = heightRamp[0];
        const float dt = frameClock->m_afDeltaTime[IKTime::FIXED_GAME_TIME];
        size.m_fX = FloatApproach_Step(dt, widthRamp);
        size.m_fY = FloatApproach_Step(frameClock->m_afDeltaTime[IKTime::FIXED_GAME_TIME], heightRamp);
    } else {
        size.m_fX = widthRamp[2];
        size.m_fY = heightRamp[2];
    }
    if (element != nullptr) {
        if (isBillboard == 0) {
            IKText2d* text = static_cast<IKText2d*>(static_cast<CText2d*>(element));
            text->m_vBoxSize.m_fY = size.m_fY;
            text->m_bAutoSize = 0;
            text->m_vBoxSize.m_fX = size.m_fX;
            text->ComputeLayout();
            // 0x0006a0b0 KStub_Nop_6a0b0(text): empty.
        } else {
            BillboardBrush_SetSize(static_cast<CBillboard2d*>(element), size);  // IKBillboard2d vt+0x30
        }
    }
    if (widthRamp[2] != widthRamp[0] || heightRamp[2] != heightRamp[0] || m_fFadeOutTime > 0.0f) {
        m_baFlags = static_cast<uint8_t>(m_baFlags | kFlagFading);
    }
}

// 0x00530ca0 CKInterfaceCheckBox_SetDisabled: on a change, the disabled bit, then the state's disabled
// twin (the transition states fall back to the focused ones: 8 -> 3, 9 -> 7).
void CKInterfaceCheckBox::SetDisabled(uint8_t disabled) {
    if (disabled == ((m_baFlags >> 1) & 1)) return;
    m_baFlags = static_cast<uint8_t>((m_baFlags & ~kFlagDisabled) | static_cast<uint8_t>(disabled << 1));
    switch (m_ui8State) {
    case 0:
    case 1: SetVisualState(disabled == 0 ? 0 : 1); break;
    case 2:
    case 3: SetVisualState(disabled == 0 ? 2 : 3); break;
    case 4:
    case 5: SetVisualState(disabled == 0 ? 4 : 5); break;
    case 6:
    case 7: SetVisualState(disabled == 0 ? 6 : 7); break;
    case 8: SetVisualState(disabled == 0 ? 8 : 3); break;
    case 9: SetVisualState(disabled == 0 ? 9 : 7); break;
    default: break;
    }
}

// 0x00530dc8 CKInterfaceCheckBox_SetPosition: the position, then the elements' offsets in the hot spot
// (+0x2c, CFlashHotSpot): the billboards at the position, the texts and the last billboard shifted in x.
void CKInterfaceCheckBox::SetPosition(const CVector2& position) {
    m_vPosition.m_fX = position.m_fX;
    m_vPosition.m_fY = position.m_fY;
    CFlashHotSpot* hotSpot = static_cast<CFlashHotSpot*>(m_unk2c);
    for (uint32_t i = 4; i-- != 0;) {
        if (m_apUnk3c[i] != nullptr) SetAttachedOffset(hotSpot, m_apUnk3c[i], position.m_fX, position.m_fY);
    }
    if (m_unk34 != nullptr) SetAttachedOffset(hotSpot, m_unk34, position.m_fX + m_fLabelOffsetX, position.m_fY);
    if (m_unk38 != nullptr) SetAttachedOffset(hotSpot, m_unk38, position.m_fX + m_fValueOffsetX, position.m_fY);
    if (m_apUnk3c[3] != nullptr) {
        SetAttachedOffset(hotSpot, m_apUnk3c[3], position.m_fX + m_fBillboard3OffsetX, position.m_fY);
    }
}

// 0x005310e0 CKInterfaceCheckBox_Update: updated (fading cleared), the four billboards' size ramps, the
// fade, the visibility, the fade-out countdown.
void CKInterfaceCheckBox::Update(IKTime* frameClock) {
    m_baFlags = static_cast<uint8_t>((m_baFlags | kFlagUpdated) & ~kFlagFading);
    for (uint32_t i = 4; i-- != 0;) AnimatePart(m_apUnk3c[i], m_aWidthRamps[i], m_aHeightRamps[i], frameClock, 1);
    float fade[3] = {m_fFadeTarget, m_fFadeSpeed, m_fFade};  // FloatApproach_Step(dt, &+0x20)
    FloatApproach_Step(frameClock->m_afDeltaTime[IKTime::FIXED_GAME_TIME], fade);
    m_fFade = fade[2];
    UpdateVisibility(0);  // vt+0x68
    if (m_fFadeOutTime > 0.0f) m_fFadeOutTime = m_fFadeOutTime - frameClock->m_afDeltaTime[IKTime::FIXED_GAME_TIME];
}

// 0x005316b8 CKInterfaceCheckBox_UpdateVisibility: every element's colour with its alpha scaled by the
// fade (fadeIn: state 0's colours, else the current state's), then shown while the fade is not 0.
// BUG(original): with fadeIn 0 before any state was set (m_ui8State 0xff), state 255 is read past the
// array; Open sets a state before its UpdateVisibility(1), so it does not happen in practice.
void CKInterfaceCheckBox::UpdateVisibility(uint8_t fadeIn) {
    const uint8_t s = fadeIn != 0 ? 0 : m_ui8State;
    uint8_t color[4];
    if (m_unk34 != nullptr) {
        FadedColor(m_aStates[s].m_labelColorRaw, m_fFade, color);
        static_cast<IKText2d*>(static_cast<CText2d*>(m_unk34))->SetColor(color);
    }
    if (m_unk38 != nullptr) {
        FadedColor(m_aStates[s].m_valueColorRaw, m_fFade, color);
        static_cast<IKText2d*>(static_cast<CText2d*>(m_unk38))->SetColor(color);
    }
    for (uint32_t i = 4; i-- != 0;) {
        if (m_apUnk3c[i] == nullptr) continue;
        FadedColor(m_aStates[s].m_aColorsRaw[i], m_fFade, color);
        static_cast<IKBillboard2d*>(static_cast<CBillboard2d*>(m_apUnk3c[i]))->SetColor(color);
    }
    if (m_fFadeTarget != m_fFade) m_baFlags = static_cast<uint8_t>(m_baFlags | kFlagFading);
    if (m_fFade != 0.0f) {
        Show();  // vt+0x6c
    } else {
        Hide();  // vt+0x70
    }
}

// 0x00531b18 CKInterfaceCheckBox_StartFadeOut: the fade-out timer, the size ramps' targets 0, the fade to
// 0 from 1 at m_fAnimSpeed.
void CKInterfaceCheckBox::StartFadeOut() {
    m_baFlags = static_cast<uint8_t>(m_baFlags | kFlagFading);
    m_aUnkRamps[2][0] = 0.0f;
    m_fFadeOutTime = m_fFadeOutDuration;
    for (uint32_t i = 4; i-- != 0;) {
        m_aWidthRamps[i][0] = 0.0f;
        m_aHeightRamps[i][0] = 0.0f;
    }
    m_aUnkRamps[0][0] = 0.0f;
    StartFade(0x1p+0f, m_fAnimSpeed, 0);  // TOC +0x7914
}

// 0x00531ba0 CKInterfaceCheckBox_Close: the base's, every element disabled, every state's videos stopped.
void CKInterfaceCheckBox::Close() {
    CKInterfaceButtonBase::Close();
    if (m_unk34 != nullptr) Node(m_unk34)->Disable();
    if (m_unk38 != nullptr) Node(m_unk38)->Disable();
    for (uint32_t i = 4; i-- != 0;) {
        if (m_apUnk3c[i] != nullptr) Node(m_apUnk3c[i])->Disable();
    }
    for (uint32_t s = 10; s-- != 0;) {
        StateVisual& visual = m_aStates[s];
        for (uint32_t i = visual.m_aVideos.m_ui32NbUsedElt; i-- != 0;) {
            IKSerializable* video = visual.m_aVideos.m_pBlock[i].m_first;
            if (video != nullptr) static_cast<IKVideo*>(video)->Stop();  // vt+0x78
        }
    }
}

// 0x00531dc8 CKInterfaceCheckBox_SetInteractionState: 0 normal, 1 validated (toggles the checked bit:
// state 8 checked, 9 unchecked; a disabled box only shows its focused disabled state), 2 focused. Other
// values only clear the focused bit.
void CKInterfaceCheckBox::SetInteractionState(int32_t state) {
    const uint8_t flags = m_baCheckFlags;
    m_baCheckFlags = static_cast<uint8_t>(flags & ~kCheckFocused);
    const bool disabled = ((m_baFlags >> 1) & 1) != 0;
    if (state == 1) {
        if (disabled) {
            SetVisualState((m_baCheckFlags & kCheckChecked) != 0 ? 3 : 7);
        } else if ((m_baCheckFlags & kCheckChecked) != 0) {
            m_baCheckFlags = static_cast<uint8_t>(flags & ~(kCheckFocused | kCheckChecked));
            SetVisualState(9);
        } else {
            m_baCheckFlags = static_cast<uint8_t>((flags & ~(kCheckFocused | kCheckChecked)) | kCheckChecked);
            SetVisualState(8);
        }
    } else if (static_cast<uint32_t>(state) < 1) {
        if (disabled) {
            SetVisualState((m_baCheckFlags & kCheckChecked) != 0 ? 1 : 5);
        } else {
            SetVisualState((m_baCheckFlags & kCheckChecked) != 0 ? 0 : 4);
        }
    } else if (state == 2) {
        m_baCheckFlags = static_cast<uint8_t>(flags | kCheckFocused);
        if (disabled) {
            SetVisualState((m_baCheckFlags & kCheckChecked) != 0 ? 3 : 7);
        } else {
            SetVisualState((m_baCheckFlags & kCheckChecked) != 0 ? 2 : 6);
        }
    }
}

// 0x00531f20 CKInterfaceCheckBox_PostLoad
int32_t CKInterfaceCheckBox::PostLoad(int32_t /*type*/) { return 1; }

// 0x00531f28 CKInterfaceCheckBox_Destroy: the base's (0x67ff0, empty), then per state from the last: the
// four textures released (the pointers kept), the three tables freed (block and count 0; the capacity
// kept), the billboard entries' textures released first.
void CKInterfaceCheckBox::Destroy() {
    CKInterfaceButtonBase::Destroy();  // 0x00067ff0 CKInterfaceObject_ClearReferences_BaseNop_maybe
    for (uint32_t s = 10; s-- != 0;) {
        StateVisual& visual = m_aStates[s];
        for (uint32_t i = 4; i-- != 0;) {
            if (visual.m_apTextures[i] != nullptr) TextureRef_Release(visual.m_apTextures[i]);  // RwTextureDestroy
        }
        if (visual.m_aVideos.m_pBlock != nullptr) {
            Mem_FreeAligned16(visual.m_aVideos.m_pBlock);
            visual.m_aVideos.m_pBlock = nullptr;
        }
        visual.m_aVideos.m_ui32NbUsedElt = 0;
        visual.m_aVideos.m_pBlock = nullptr;
        if (visual.m_aTexts.m_pBlock != nullptr) {
            Mem_FreeAligned16(visual.m_aTexts.m_pBlock);
            visual.m_aTexts.m_pBlock = nullptr;
        }
        visual.m_aTexts.m_ui32NbUsedElt = 0;
        visual.m_aTexts.m_pBlock = nullptr;
        for (uint32_t i = visual.m_aBillboards.m_ui32NbUsedElt; i-- != 0;) {
            void* texture = visual.m_aBillboards.m_pBlock[i].m_pTexture;
            if (texture != nullptr) TextureRef_Release(texture);
        }
        if (visual.m_aBillboards.m_pBlock != nullptr) {
            Mem_FreeAligned16(visual.m_aBillboards.m_pBlock);
            visual.m_aBillboards.m_pBlock = nullptr;
        }
        visual.m_aBillboards.m_ui32NbUsedElt = 0;
        visual.m_aBillboards.m_pBlock = nullptr;
    }
}

// 0x005320f0 CKInterfaceCheckBox_Open
void CKInterfaceCheckBox::Open(uint8_t focused) {
    m_ui8State = 0xff;
    static_cast<CKMenuBase114c*>(m_pMenu)->VfEC(this);  // vt+0xec(menu, this)
    m_baCheckFlags = static_cast<uint8_t>(m_baCheckFlags & ~kCheckNoActions);
    CKInterfaceButtonBase::Open(focused);
    m_baCheckFlags = static_cast<uint8_t>(m_baCheckFlags & 0xf2);
    Show();  // vt+0x6c
    m_fFadeOutTime = m_fFadeOutDuration;
    // Every ramp {0, m_fAnimSpeed, 0} (the stores are independent; their order is not kept).
    for (uint32_t i = 0; i < 4; ++i) {
        for (float (*ramps)[3] : {m_aWidthRamps, m_aHeightRamps, m_aUnkRamps}) {
            ramps[i][0] = 0.0f;
            ramps[i][1] = m_fAnimSpeed;
            ramps[i][2] = 0.0f;
        }
    }
    for (uint32_t s = 10; s-- != 0;) {
        if (m_aStates[s].m_pParticles != nullptr) ParticlesStop(static_cast<CParticlesNodeFx*>(m_aStates[s].m_pParticles));
    }
    LoadOptionValue();
    if (focused != 0) {
        SetVisualState((m_baCheckFlags & kCheckChecked) != 0 ? 2 : 6);
    } else {
        SetVisualState((m_baCheckFlags & kCheckChecked) != 0 ? 0 : 4);
    }
    StartFade(0x1p+0f, m_fAnimSpeed, 1);  // TOC +0x7914
    UpdateVisibility(0);                  // vt+0x68
}

// 0x00532d88 CKInterfaceCheckBox_Create (the constructor inlined; the same stores as 0x531238): the
// base, then +0x6c..+0xfb = 0 and every state's three tables empty (block 0, capacity 1, count 0). The
// stores are independent; their interleaving is not kept.
CKInterfaceCheckBox::CKInterfaceCheckBox() {
    for (uint32_t i = 0; i < 4; ++i) {
        for (uint32_t k = 0; k < 3; ++k) {
            m_aWidthRamps[i][k] = 0.0f;
            m_aHeightRamps[i][k] = 0.0f;
            m_aUnkRamps[i][k] = 0.0f;
        }
    }
    for (StateVisual& s : m_aStates) {
        s.m_aVideos = {nullptr, 1, 0};
        s.m_aTexts = {nullptr, 1, 0};
        s.m_aBillboards = {nullptr, 1, 0};
    }
}

namespace {

// 0x009c87e0 CKInterfaceCheckBox_LoadStateVisual_maybe.
void LoadStateVisual(CKInterfaceCheckBox::StateVisual* s, IKFile* file, int32_t type) {
    ReadRaw(file, &s->m_labelColorRaw, 4);
    ReadRaw(file, &s->m_valueColorRaw, 4);
    IKFile_ReadRef(file, &s->m_pTexts);
    for (CVector2& v : s->m_avSizes) {  // one 0x20-byte read, every word swapped
        ReadF32LE(file, &v.m_fX);
        ReadF32LE(file, &v.m_fY);
    }
    ReadRaw(file, s->m_aBlendModes, 4);
    ReadRaw(file, s->m_aColorsRaw, 16);
    for (float& f : s->m_afAnimDurations) ReadF32LE(file, &f);  // one 0x10-byte read, every word swapped
    ReadU32LEWords(file, s->m_aSheetCellsU, 4);
    ReadU32LEWords(file, s->m_aSheetCellsV, 4);
    for (uint32_t i = 4; i-- != 0;) IKFile_ReadTextureRef(file, &s->m_apTextures[i], 1);
    CKInterfaceButton_LoadRefPairs(&s->m_aVideos, file, type);
    CKInterfaceButton_LoadRefPairValues(&s->m_aTexts, file);
    CKInterfaceButton_LoadTextEntries(&s->m_aBillboards, file);
    IKFile_ReadRef(file, &s->m_pParticles);
}

}  // namespace

// 0x00533280 CKInterfaceCheckBox_Load: no type test of its own (the base and the state reader test it).
int32_t CKInterfaceCheckBox::Load(IKFile* file, int32_t type) {
    CKInterfaceButtonBase::Load(file, type);
    ReadF32LE(file, &m_fAnimSpeed);
    ReadU8(file, &m_unk790);
    ReadF32LE(file, &m_fLabelOffsetX);
    ReadF32LE(file, &m_fValueOffsetX);
    ReadF32LE(file, &m_fBillboard3OffsetX);
    for (uint32_t i = 10; i-- != 0;) LoadStateVisual(&m_aStates[i], file, type);
    ReadF32LE(file, &m_fFadeOutDuration);
    ReadU8(file, &m_baCheckFlags);
    ReadU8(file, &m_ui8Option);
    IKFile_ReadRef(file, &m_unk34);
    IKFile_ReadRef(file, &m_unk38);
    IKFile_ReadObjectRefArray(file, m_apUnk3c, 4);
    IKFile_ReadRef(file, &m_pSounds);
    ReadF32LE(file, &m_vUnk5c[0]);  // one 8-byte read, both words swapped
    ReadF32LE(file, &m_vUnk5c[1]);
    ReadF32LE(file, &m_vUnk64[0]);
    ReadF32LE(file, &m_vUnk64[1]);
    return 1;
}

namespace {
template <class T>
void FreeCheckBoxTable(TVector<T, 1>& v) {
    if (v.m_pBlock != nullptr) Mem_FreeAligned16(v.m_pBlock);
    v.m_ui32NbUsedElt = 0;
    v.m_pBlock = nullptr;
}

void RegisterIfCheckBox(IKSerializable* object, int32_t type) {
    if (object != nullptr) object->RecursiveRegistration(type);  // vt+0x24
}
}  // namespace

// 0x005326d8 CKInterfaceCheckBox_Destructor
CKInterfaceCheckBox::~CKInterfaceCheckBox() {
    for (int k = 9; k >= 0; --k) {
        StateVisual& s = m_aStates[k];
        FreeCheckBoxTable(s.m_aBillboards);
        FreeCheckBoxTable(s.m_aTexts);
        FreeCheckBoxTable(s.m_aVideos);
    }
}

// 0x00530280 CKInterfaceCheckBox_RecursiveRegistration (each table from its last element down)
void CKInterfaceCheckBox::RecursiveRegistration(int32_t type) {
    CKInterfaceButtonBase::RecursiveRegistration(type);  // 0x00067fe8
    for (int k = 9; k >= 0; --k) {
        StateVisual& s = m_aStates[k];
        s.m_pTexts->RecursiveRegistration(type);
        RegisterIfCheckBox(s.m_pParticles, type);
        for (uint32_t i = s.m_aTexts.m_ui32NbUsedElt; i != 0; --i) {
            s.m_aTexts.m_pBlock[i - 1].m_second->RecursiveRegistration(type);
            RegisterIfCheckBox(s.m_aTexts.m_pBlock[i - 1].m_first, type);
        }
        for (uint32_t i = s.m_aBillboards.m_ui32NbUsedElt; i != 0; --i) RegisterIfCheckBox(s.m_aBillboards.m_pBlock[i - 1].m_pText, type);
    }
    RegisterIfCheckBox(m_unk34, type);
    RegisterIfCheckBox(m_unk38, type);
    RegisterIfCheckBox(m_apUnk3c[3], type);
    RegisterIfCheckBox(m_apUnk3c[2], type);
    RegisterIfCheckBox(m_apUnk3c[1], type);
    RegisterIfCheckBox(m_apUnk3c[0], type);
    m_pSounds->RecursiveRegistration(type);
}
