// CKInterfaceButton.cpp - reconstructed original translation unit 0x51b9d0-0x51f930 (GAME_TOC1, main_toc1), 29 functions, 29 live.
// Primary class: CKInterfaceButton  key 0x630c  category Logic  size 0x3c0  vtable 0xb2b760
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x51b9d0  CKInterfaceButton_Delete
//   [x] 0x51ba20  CKInterfaceButton_Show
//   [x] 0x51bb30  CKInterfaceButton_Hide
//   [x] 0x51bc40  CKInterfaceButton_vf80
//   [ ] 0x51bd58  RegisterCKInterfaceButtonClass
//   [ ] 0x51bdd0  _GLOBAL__I_51bdd0
//   [x] 0x51bde0  CKInterfaceButton_ApplyStateActions
//   [x] 0x51c1c0  CKInterfaceButton_SetVisualState
//   [ ] 0x51cd98  CKInterfaceButton_Save
//   [x] 0x51cdc0  CKInterfaceButton_RecursiveRegistration
//   [x] 0x51d230  CKInterfaceButton_DeleteArray
//   [x] 0x51d2d8  CKInterfaceButton_BaseDestructor  (the same code as 0x51f4e8)
//   [x] 0x51d428  CKInterfaceButton_SetDisabled
//   [x] 0x51d510  CKInterfaceButton_SetInteractionState
//   [x] 0x51d598  CKInterfaceButton_StartFadeOut
//   [x] 0x51d610  CKInterfaceButton_Open
//   [x] 0x51d7a0  CKInterfaceButton_UpdateVisibility
//   [x] 0x51daf0  CKInterfaceButton_Close
//   [x] 0x51dcc0  CKInterfaceButton_Construct_2  (the same code as 0x51e3b8 CKInterfaceButton_Construct)
//   [x] 0x51e008  CKInterfaceButton_SetPosition
//   [x] 0x51e1b0  CKInterfaceButton_PostLoad  (in the header)
//   [x] 0x51e1b8  CKInterfaceButton_Destroy
//   [x] 0x51e3b8  CKInterfaceButton_Construct
//   [x] 0x51e700  CKInterfaceButton_Update
//   [x] 0x51eba8  CKInterfaceButton_CreateArray
//   [x] 0x51eff0  CKInterfaceButton_Create
//   [x] 0x51f388  CKInterfaceButton_DeletingDestructor  (0x51f4e8 CKInterfaceButton_Destructor, then the delete)
//   [x] 0x51f4e8  CKInterfaceButton_Destructor
//   [x] 0x51f638  CKInterfaceButton_Load
//
//   [x] 0x9c7608  CKInterfaceButton_IsKindOfClass  [inline]
//   [ ] 0x9c7630  CKInterfaceButton_GetClassType  [inline]
//   [ ] 0x9c7638  CKInterfaceButton_GetClassID  [inline]
//   [x] 0x9c7640  CKInterfaceButton_IsFadeOutFinished_maybe  [inline]
//   [x] 0x9c7668  CKInterfaceButton_vf88  [inline]
//   [x] 0x9c7670  CKInterfaceButton_vf8C  [inline]
//   [x] 0x9c7678  CKInterfaceButton_LoadStateVisual_maybe  [inline]
//
// What the player sees per visual state (SetVisualState 0x51c1c0, ApplyStateActions 0x51bde0): each state
// record gives the text's colour and string (a CKLocTextAccessor), and for each of the three billboards a
// texture (kept when null), a colour, a blend byte and a sprite-sheet animation; the four elements' sizes
// animate to the state's three sizes at m_fAnimSpeed (the two other sizes scaled so all arrive together).
// Entering state 2 (focused), 3 or 4 plays sound [0], [1] or [2] of m_pSounds (once the item was updated
// once); a focused state's CParticlesNodeFx is started at the origin. The actions (texts, billboards,
// videos, menu transitions) run for the new state, except on entering 4 (validated) with kFlagHold.
#include "crt/xlround.h"
#include "k2000/logic/CKInterfaceButton.h"

#include <cmath>
#include <cstring>

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rt2d/Rt2d.h"
#include "Renderware/rt2d/Rt2dTypes.h"
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
#include "k2000/logic/sound/CKSound.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/system/IKTime.h"

namespace {

// The TVector sizing the state reader inlines for each table: capacity 1 and a block of one element,
// grown to count + 1 elements when the count is larger, then the count.
template <class T>
void LoadReserve(TVector<T, 1>& v, uint32_t count) {
    v.m_ui32NbElt = 1;
    v.m_pBlock = static_cast<T*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(T))));
    if (v.m_ui32NbElt < count) {
        uint32_t capacity = count + 1;
        uint32_t size = capacity * static_cast<uint32_t>(sizeof(T));
        if (capacity == 0) {
            capacity = 1;
            size = static_cast<uint32_t>(sizeof(T));
        }
        v.m_pBlock = static_cast<T*>(Mem_ReallocAligned16(v.m_pBlock, size));
        v.m_ui32NbElt = capacity;
    }
    v.m_ui32NbUsedElt = count;
}

// One state's own default: the five tables empty with capacity 1 (the constructor's stores).
void ConstructState(CKInterfaceButton::StateVisual& s) {
    s.m_vpUnk64 = {nullptr, 1, 0};
    s.m_vMenuTransitions = {nullptr, 1, 0};
    s.m_vVideos = {nullptr, 1, 0};
    s.m_vTexts = {nullptr, 1, 0};
    s.m_vBillboards = {nullptr, 1, 0};
}

bool ReadsFirstRefs(int32_t type) { return type == 8 || type == K_LEVEL_PLATEFORMS || type == K_GAME_PLATEFORMS; }

// The TVector destructor the class's destructor and Destroy inline: the block freed, the count and the
// block cleared.
template <class T>
void FreeTable(TVector<T, 1>& v) {
    if (v.m_pBlock != nullptr) {
        Mem_FreeAligned16(v.m_pBlock);
        v.m_pBlock = nullptr;
    }
    v.m_ui32NbUsedElt = 0;
    v.m_pBlock = nullptr;
}

// The element references (the file's classes: CText2d at +0x34, CBillboard2d at +0x38..+0x40).
CText2d* AsText(IKSerializable* object) { return static_cast<CText2d*>(object); }
CBillboard2d* AsBillboard(IKSerializable* object) { return static_cast<CBillboard2d*>(object); }
IKNode2d* AsNode(IKSerializable* object) { return static_cast<IKNode2d*>(object); }

// A raw colour word (RGBA bytes in memory order), as the colour setters take it.
const uint8_t* ColorBytes(const uint32_t& raw) { return reinterpret_cast<const uint8_t*>(&raw); }

float WordAsFloat(uint32_t word) {
    float value;
    std::memcpy(&value, &word, 4);
    return value;
}

// The text a CKLocTextAccessor gives (inlined in SetVisualState and ApplyStateActions): its list's first
// text when it has a list, else its +0x10 text. No null check on the accessor (as the original).
IKSerializable* AccessorText(IKSerializable* accessor) {
    CKLocTextAccessor* a = static_cast<CKLocTextAccessor*>(accessor);
    return a->m_texts.m_pBlock != nullptr ? a->m_texts.m_pBlock[0] : a->m_pText;
}

// 0x0005b098 CBillboard2d_SetAnimTime_maybe (CBillboard2d.cpp; not ported there yet): the sprite-sheet
// duration (+0x74); 0 resets the UVs to the whole texture ((0,1) (1,1) (1,0) (0,0), TOC -0x7198 / -0x7194)
// and applies them (IKBillboard2d vt+0x34 BillboardBrush_ApplyUV, not overridden).
void CBillboard2d_SetAnimTime(CBillboard2d* billboard, float duration) { billboard->SetAnimTime(duration); }  // the CBillboard2d port

// 0x0005b118 CBillboard2d_SetSpriteSheetRows_maybe: the cells along u (+0x7c; 0 counts as 1), the animation
// restarted (+0x70 time, +0x78 frame).
void CBillboard2d_SetSpriteSheetRows(CBillboard2d* billboard, int32_t rows) { billboard->SetSpriteSheetRows(static_cast<int32_t>(rows)); }

// 0x0005b158 CBillboard2d_SetSpriteSheetColumns_maybe: the same for the cells along v (+0x80).
void CBillboard2d_SetSpriteSheetColumns(CBillboard2d* billboard, int32_t columns) { billboard->SetSpriteSheetColumns(static_cast<int32_t>(columns)); }

// 0x00066cb8 BillboardBrush_SetTexture (IKBillboard2d vt+0x3c, not overridden by the front end's
// billboards): the brush's texture when it differs. The result (1 set or unchanged, 0 no brush) is unused
// by this class.
void BillboardBrush_SetTexture(CBillboard2d* billboard, void* texture) {
    Rt2dBrush* brush = billboard->m_pBrush;
    if (brush != nullptr && brush->texture != static_cast<RwTexture*>(texture)) {
        Rt2dBrushSetTexture(brush, static_cast<RwTexture*>(texture));
    }
}

// 0x00514668 KBase730C_CallOwnerVfDCObjectVf78AfterVf308_maybe (the menu's; not ported in KBase730C.cpp):
// the game manager's interface video (vt+0xdc) stopped (vt+0x78), its segment kept as the interface
// segment (vt+0x308) first.
void KBase730C_StopInterfaceVideoKeepSegment(CKMenuBase114c* menu) {
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(menu->m_pGameManager);
    IKVideo* video = manager->GetInterfaceVideo();
    if (video != nullptr) {
        manager->SetInterfaceSegment(video->m_pSegment);
        video->Stop();
    }
}

// 0x00112bc0 CKSoundDictionaryID_GetSound: no bounds check.
CKSound* CKSoundDictionaryID_GetSound(IKSerializable* dictionary, uint32_t index) {
    return static_cast<CKSoundDictionaryID*>(dictionary)->GetSound(index);  // the audio port
}

// 0x00111b70 CKSound_ResetPan_maybe: flag 4 (position from the pan) set to `fromPan`, the pan centred, then
// CKSound_UpdatePan_maybe 0x111818 (CKSound::ResetPan / UpdatePan, k2000/logic/sound/CKSound.cpp).
void CKSound_ResetPan(CKSound* sound, uint32_t fromPan) { sound->ResetPan(static_cast<int32_t>(fromPan)); }  // the audio port

// 0x00111230 CKSound_Play: the sound manager's backend plays it (engine sound manager +8,
// SoundBackend_PlaySound_maybe) with `delay`; returns 1 (CKSound::Play).
void CKSound_Play(CKSound* sound, float delay) { sound->Play(delay); }  // the audio port

// The CParticlesNodeFx start SetVisualState inlines (XXL2 CParticlesNodeFx::AddPointToList(origin) and the
// emitter activation): below 64 points, the origin (0x00c50d64, (0, 0, 0)) appended to the emitter's point
// list (m_pAdvEmtPointList->pointList, 12 bytes each) with property 0x2000; then properties 0x200 | 0x400
// set and 0x80000 cleared, the emission speed adjustment 0, and the RpPrtStdEmitter's flags |= 0xa
// (ACTIVE | EMIT). Both pointers come from CParticlesNodeFx_PostLoad (0xe65f0).
void StartParticlesAtOrigin(CParticlesNodeFx* fx) {
    static const RwV3d kNullVector = {0.0f, 0.0f, 0.0f};  // g_nullVector 0x00c50d64
    if (fx->m_ui8NbActivePoints <= 0x3f) {
        fx->m_pAdvEmtPointList->pointList[fx->m_ui8NbActivePoints] = kNullVector;
        fx->m_sgProperties = (fx->m_sgProperties & ~0x2000u) | 0x2000u;
        fx->m_ui8NbActivePoints = static_cast<uint8_t>(fx->m_ui8NbActivePoints + 1);
    }
    uint32_t properties = fx->m_sgProperties;
    properties = (properties & ~0x200u) | 0x200u;
    properties = (properties & ~0x400u) | 0x400u;
    properties &= ~0x80000u;
    fx->m_sgProperties = properties;
    fx->m_fEmissionSpeedAdjustment = 0.0f;  // stw 0
    fx->m_pRpPrtStdEmitter->flag |= rpPRTSTDEMITTERFLAGACTIVE | rpPRTSTDEMITTERFLAGEMIT;
}

// The base's +0x20 fade (target, speed, current) as a FloatApproach.
float* FadeApproach(CKInterfaceButtonBase* button) { return &button->m_fFadeTarget; }

}  // namespace

// 0x0051ba20 CKInterfaceButton_Show: the shown bit, then the elements enabled (vt+0x64): the text, then
// billboards 2, 1, 0.
void CKInterfaceButton::Show() {
    m_baFlags = static_cast<uint8_t>((m_baFlags & ~kFlagShown) | kFlagShown);
    if (m_unk34 != nullptr) AsNode(m_unk34)->Enable();
    if (m_apUnk38[2] != nullptr) AsNode(m_apUnk38[2])->Enable();
    if (m_apUnk38[1] != nullptr) AsNode(m_apUnk38[1])->Enable();
    if (m_apUnk38[0] != nullptr) AsNode(m_apUnk38[0])->Enable();
}

// 0x0051bb30 CKInterfaceButton_Hide: the same with the bit cleared and vt+0x68 (Disable).
void CKInterfaceButton::Hide() {
    m_baFlags = static_cast<uint8_t>(m_baFlags & ~kFlagShown);
    if (m_unk34 != nullptr) AsNode(m_unk34)->Disable();
    if (m_apUnk38[2] != nullptr) AsNode(m_apUnk38[2])->Disable();
    if (m_apUnk38[1] != nullptr) AsNode(m_apUnk38[1])->Disable();
    if (m_apUnk38[0] != nullptr) AsNode(m_apUnk38[0])->Disable();
}

// 0x0051bc40 CKInterfaceButton_vf80: the elements drawn (vt+0x84): billboards 2, 1, 0, then the text.
void CKInterfaceButton::Vf80(IKTime* frameClock) {
    if (m_apUnk38[2] != nullptr) AsNode(m_apUnk38[2])->Render(frameClock);
    if (m_apUnk38[1] != nullptr) AsNode(m_apUnk38[1])->Render(frameClock);
    if (m_apUnk38[0] != nullptr) AsNode(m_apUnk38[0])->Render(frameClock);
    if (m_unk34 != nullptr) AsNode(m_unk34)->Render(frameClock);
}

// 0x0051bde0 CKInterfaceButton_ApplyStateActions: nothing while kSuppressActions. Each table from its last
// entry down (the count read once, the block again for each entry):
// - with kFlagUpdated, the menu transitions (the game manager's vt+0x304 MenuId of each id, then the menu's
//   StartTransitionToMenu: its leaving message and every button's fade-out);
// - the videos: a segment is played in its default mode (Play(3, 0, 0)), else the video started without a
//   segment (vt+0x60), both after the interface video was stopped (0x514668);
// - the texts: the CText2d's string from the accessor (vt+0x88), then its colour (IKText2d vt+0x44);
// - the billboards with a texture: the texture (IKBillboard2d vt+0x3c), then the sprite sheet.
void CKInterfaceButton::ApplyStateActions(uint8_t state) {
    if ((m_baSuppress & kSuppressActions) != 0) return;
    StateVisual& s = m_aStates[state];
    if ((m_baFlags & kFlagUpdated) != 0) {
        CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
        for (uint32_t i = s.m_vMenuTransitions.m_ui32NbUsedElt; i-- != 0;) {
            CKMenuBase114c* menu = static_cast<CKMenuBase114c*>(m_pMenu);
            const uint8_t menuId = manager->MenuId(s.m_vMenuTransitions.m_pBlock[i]);  // vt+0x304
            menu->StartTransitionToMenu(menuId);
        }
    }
    for (uint32_t i = s.m_vVideos.m_ui32NbUsedElt; i-- != 0;) {
        const RefPair& e = s.m_vVideos.m_pBlock[i];
        if (e.m_second != nullptr) {
            KBase730C_StopInterfaceVideoKeepSegment(static_cast<CKMenuBase114c*>(m_pMenu));
            static_cast<CKVideoSegment*>(s.m_vVideos.m_pBlock[i].m_second)->Play(CKVideoSegment::kModeDefault, 0, 0);
        } else if (e.m_first != nullptr) {
            KBase730C_StopInterfaceVideoKeepSegment(static_cast<CKMenuBase114c*>(m_pMenu));
            static_cast<IKVideo*>(s.m_vVideos.m_pBlock[i].m_first)->Start(nullptr);  // vt+0x60
        }
    }
    for (uint32_t i = s.m_vTexts.m_ui32NbUsedElt; i-- != 0;) {
        const RefPairValue& e = s.m_vTexts.m_pBlock[i];
        if (e.m_first == nullptr) continue;
        AsText(e.m_first)->SetTextById(AccessorText(e.m_second));  // vt+0x88
        const RefPairValue& again = s.m_vTexts.m_pBlock[i];
        const uint32_t color = again.m_valueRaw;
        static_cast<IKText2d*>(AsText(again.m_first))->SetColor(ColorBytes(color));  // IKText2d vt+0x44
    }
    for (uint32_t i = s.m_vBillboards.m_ui32NbUsedElt; i-- != 0;) {
        const TextEntry& e = s.m_vBillboards.m_pBlock[i];
        if (e.m_pText == nullptr || e.m_pTexture == nullptr) continue;
        BillboardBrush_SetTexture(AsBillboard(e.m_pText), e.m_pTexture);  // IKBillboard2d vt+0x3c
        const TextEntry& again = s.m_vBillboards.m_pBlock[i];
        CBillboard2d_SetAnimTime(AsBillboard(again.m_pText), WordAsFloat(again.m_unk08));
        CBillboard2d_SetSpriteSheetRows(AsBillboard(again.m_pText), static_cast<int32_t>(again.m_unk0c));
        CBillboard2d_SetSpriteSheetColumns(AsBillboard(again.m_pText), static_cast<int32_t>(again.m_unk10));
    }
}

// 0x0051c1c0 CKInterfaceButton_SetVisualState. Nothing when the state does not change. Otherwise:
// 1. The size animations: the targets become the new state's three sizes. Size 1's x moves at
//    m_fAnimSpeed; every other component's speed is m_fAnimSpeed x |its distance / size 1's x distance| (the
//    distances from the previous targets), so all arrive together. When size 1's x does not change, every
//    speed is m_fAnimSpeed.
// 2. The text (m_unk34): its string from the state's accessor (unless kSuppressText) and the state's text
//    colour. Billboards 2, 1, 0: the state's texture (when not null), colour and blend byte; with a
//    sprite-sheet duration > 0, the duration, rows and columns (the animation restarts).
// 3. With kFlagUpdated, entering 2 / 3 / 4 plays m_pSounds [0] / [1] / [2] (pan centred, no delay).
// 4. The state's particle effect (+0x60) started at the origin.
// 5. The state's actions (ApplyStateActions): see the end.
void CKInterfaceButton::SetVisualState(uint8_t state) {
    const uint8_t previous = m_ui8State;
    if (previous == state) return;
    m_ui8State = state;
    m_baFlags = static_cast<uint8_t>((m_baFlags & ~kFlagFading) | kFlagFading);

    const StateVisual& s = m_aStates[m_ui8State];
    const float dx = s.m_afSize[0] - m_afSizeAnimX[1][0];  // fsubs
    m_afSizeAnimX[1][1] = m_fAnimSpeed;
    if (dx == 0.0f) {
        m_afSizeAnimY[1][1] = m_fAnimSpeed;
        m_afSizeAnimX[2][1] = m_fAnimSpeed;
        m_afSizeAnimY[2][1] = m_fAnimSpeed;
        m_afSizeAnimX[2][0] = s.m_afSize2[0];
        m_afSizeAnimY[2][0] = s.m_afSize2[1];
        m_afSizeAnimX[1][0] = s.m_afSize[0];
        m_afSizeAnimY[1][0] = s.m_afSize[1];
        m_afSizeAnimX[0][1] = m_fAnimSpeed;
        m_afSizeAnimY[0][1] = m_fAnimSpeed;
        m_afSizeAnimX[0][0] = s.m_afSize0[0];
        m_afSizeAnimY[0][0] = s.m_afSize0[1];
    } else {
        // fsubs, fdivs, the sign bit cleared in memory, fmuls
        m_afSizeAnimY[1][1] = m_fAnimSpeed * std::fabs((s.m_afSize[1] - m_afSizeAnimY[1][0]) / dx);
        const float* sizes[3] = {s.m_afSize0, s.m_afSize, s.m_afSize2};
        for (int i = 2; i >= 0; i -= 2) {  // the loop runs 2 then 0; at 1 it sets size 1's targets
            m_afSizeAnimX[i][1] = m_fAnimSpeed * std::fabs((sizes[i][0] - m_afSizeAnimX[i][0]) / dx);
            m_afSizeAnimY[i][1] = m_fAnimSpeed * std::fabs((sizes[i][1] - m_afSizeAnimY[i][0]) / dx);
            m_afSizeAnimX[i][0] = sizes[i][0];
            m_afSizeAnimY[i][0] = sizes[i][1];
            if (i == 2) {
                m_afSizeAnimX[1][0] = s.m_afSize[0];
                m_afSizeAnimY[1][0] = s.m_afSize[1];
            }
        }
    }

    if (m_unk34 != nullptr) {
        CText2d* text = AsText(m_unk34);
        if ((m_baSuppress & kSuppressText) == 0) {
            text->SetTextById(AccessorText(m_aStates[m_ui8State].m_pTextAccessor));  // vt+0x88
            text = AsText(m_unk34);
        }
        const uint32_t color = m_aStates[m_ui8State].m_textColorRaw;
        static_cast<IKText2d*>(text)->SetColor(ColorBytes(color));  // IKText2d vt+0x44
    }
    for (int i = 2; i >= 0; --i) {
        if (m_apUnk38[i] == nullptr) continue;
        if (m_aStates[m_ui8State].m_apTextures[i] != nullptr) {
            BillboardBrush_SetTexture(AsBillboard(m_apUnk38[i]), m_aStates[m_ui8State].m_apTextures[i]);  // vt+0x3c
        }
        const uint32_t color = m_aStates[m_ui8State].m_aBillboardColorsRaw[i];
        AsBillboard(m_apUnk38[i])->SetColor(ColorBytes(color));  // IKBillboard2d vt+0x28
        AsBillboard(m_apUnk38[i])->m_bUseAlpha = m_aStates[m_ui8State].m_abUseAlpha[i];
        const float duration = m_aStates[m_ui8State].m_afAnimDurations[i];
        if (duration > 0.0f) {  // TOC +0x76ec
            CBillboard2d_SetAnimTime(AsBillboard(m_apUnk38[i]), m_aStates[m_ui8State].m_afAnimDurations[i]);
            CBillboard2d_SetSpriteSheetRows(AsBillboard(m_apUnk38[i]),
                                            static_cast<int32_t>(m_aStates[m_ui8State].m_aui32SheetRows[i]));
            CBillboard2d_SetSpriteSheetColumns(AsBillboard(m_apUnk38[i]),
                                               static_cast<int32_t>(m_aStates[m_ui8State].m_aui32SheetColumns[i]));
        }
    }

    // The sound: the original tests the dictionary entry, then fetches it twice more (pan reset, play);
    // its fall-back index 0xff is unreachable (the state is 2, 3 or 4 there).
    if ((m_baFlags & kFlagUpdated) != 0 && (state == 2 || state == 3 || state == 4)) {
        const uint32_t index = state == 3 ? 1u : state == 4 ? 2u : 0u;
        if (CKSoundDictionaryID_GetSound(m_pSounds, index) != nullptr) {
            CKSound_ResetPan(CKSoundDictionaryID_GetSound(m_pSounds, index), 1);
            CKSound_Play(CKSoundDictionaryID_GetSound(m_pSounds, index), 0.0f);  // TOC +0x76ec
        }
    }

    if (m_aStates[state].m_pFx != nullptr) StartParticlesAtOrigin(static_cast<CParticlesNodeFx*>(m_aStates[state].m_pFx));

    // The actions. Without kFlagHold: entering 4 applies state 4's, then (when the state is no longer 4)
    // the new state's. With kFlagHold (an item validated while held): entering 4 applies none; leaving 4
    // applies the new state's twice.
    // BUG(original)_maybe: the double application when a held item leaves state 4.
    if ((m_baFlags & kFlagHold) == 0) {
        if (m_ui8State == 4) {
            ApplyStateActions(4);
            if (m_ui8State == 4) return;
        }
    } else {
        if (previous == 4) ApplyStateActions(m_ui8State);
        if (m_ui8State == 4) return;
    }
    ApplyStateActions(state);
}

// 0x0051d428 CKInterfaceButton_SetDisabled: nothing when bit 1 already equals `disabled`. Else the bit
// (disabled << 1, unmasked as the original), then the visual state again from the current one and the new
// bit: 0/1 -> 0 or 1, 2/3 -> 2 or 3, 4 -> 4 or 3 (a jump table, TOC +0x7720; > 4 nothing).
void CKInterfaceButton::SetDisabled(uint8_t disabled) {
    if (disabled == ((m_baFlags >> 1) & 1)) return;
    m_baFlags = static_cast<uint8_t>((m_baFlags & ~kFlagDisabled) | static_cast<uint32_t>(disabled << 1));
    const bool isDisabled = ((m_baFlags >> 1) & 1) != 0;
    switch (m_ui8State) {
        case 0:
        case 1:
            SetVisualState(isDisabled ? 1 : 0);
            break;
        case 2:
        case 3:
            SetVisualState(isDisabled ? 3 : 2);
            break;
        case 4:
            SetVisualState(isDisabled ? 3 : 4);
            break;
        default:
            break;
    }
}

// 0x0051d510 CKInterfaceButton_SetInteractionState: the menu's item state to a visual state:
// 0 normal -> 0 (1 when disabled), 1 validated -> 4 (3), 2 focused -> 2 (3); other states nothing.
void CKInterfaceButton::SetInteractionState(int32_t state) {
    const bool isDisabled = ((m_baFlags >> 1) & 1) != 0;
    if (state == 1) {
        SetVisualState(isDisabled ? 3 : 4);
    } else if (state == 0) {
        SetVisualState(isDisabled ? 1 : 0);
    } else if (state == 2) {
        SetVisualState(isDisabled ? 3 : 2);
    }
}

// 0x0051d598 CKInterfaceButton_StartFadeOut: the fading bit, the fade-out timer (+0x3bc), every size target
// 0 (the elements shrink at their current speeds), then the fade from 1 down to 0 (TOC +0x7724 = 1.0).
void CKInterfaceButton::StartFadeOut() {
    m_baFlags = static_cast<uint8_t>((m_baFlags & ~kFlagFading) | kFlagFading);
    m_afSizeAnimY[0][0] = 0.0f;  // stw 0
    m_fFadeOutTime = m_fUnk3bc;
    m_afSizeAnimX[2][0] = 0.0f;
    m_afSizeAnimY[2][0] = 0.0f;
    m_afSizeAnimX[1][0] = 0.0f;
    m_afSizeAnimY[1][0] = 0.0f;
    m_afSizeAnimX[0][0] = 0.0f;
    StartFade(0x1p+0f, m_fAnimSpeed, 0);
}

// 0x0051d610 CKInterfaceButton_Open: the state reset (0xff), the menu's vt+0xec with the button, the base
// Open (position (0, 0), fade 0 -> 1, shown, UpdateVisibility(1)) between the two kSuppress clears, Show,
// the size animations reset (targets and currents 0, speeds m_fAnimSpeed), the fade-out timer, the visual
// state (2 focused, else 0), the fade from 0 to 1 at m_fAnimSpeed, then UpdateVisibility(0).
void CKInterfaceButton::Open(uint8_t focused) {
    m_ui8State = 0xff;
    static_cast<CKMenuBase114c*>(m_pMenu)->VfEC(this);  // vt+0xec(menu, this)
    m_baSuppress = static_cast<uint8_t>(m_baSuppress & ~kSuppressActions);
    CKInterfaceButtonBase::Open(focused);
    m_baSuppress = static_cast<uint8_t>(m_baSuppress & ~kSuppressText);
    Show();  // vt+0x6c
    const float speed = m_fAnimSpeed;
    const float duration = m_fUnk3bc;
    m_afSizeAnimY[0][1] = speed;
    m_fFadeOutTime = duration;
    m_afSizeAnimY[0][0] = 0.0f;
    m_afSizeAnimX[2][2] = 0.0f;
    m_afSizeAnimX[2][1] = speed;
    m_afSizeAnimX[2][0] = 0.0f;
    m_afSizeAnimY[2][2] = 0.0f;
    m_afSizeAnimY[2][1] = speed;
    m_afSizeAnimY[2][0] = 0.0f;
    m_afSizeAnimX[1][2] = 0.0f;
    m_afSizeAnimX[1][1] = speed;
    m_afSizeAnimX[1][0] = 0.0f;
    m_afSizeAnimY[1][2] = 0.0f;
    m_afSizeAnimY[1][1] = speed;
    m_afSizeAnimY[1][0] = 0.0f;
    m_afSizeAnimX[0][2] = 0.0f;
    m_afSizeAnimX[0][1] = speed;
    m_afSizeAnimX[0][0] = 0.0f;
    m_afSizeAnimY[0][2] = 0.0f;
    SetVisualState(focused != 0 ? 2 : 0);
    StartFade(0x1p+0f, m_fAnimSpeed, 1);  // TOC +0x7724
    UpdateVisibility(0);                  // vt+0x68
}

// 0x0051d7a0 CKInterfaceButton_UpdateVisibility: the colours of state (fadeIn ? 0 : the current state), each
// with its alpha byte (the 4th) x the fade (fcfid/frsp, fmuls, fctiwz, the low byte): the text, then
// billboards 2, 1, 0; the fading bit while the fade runs; then hidden at fade 0, else shown.
void CKInterfaceButton::UpdateVisibility(uint8_t fadeIn) {
    const uint8_t s = fadeIn != 0 ? 0 : m_ui8State;  // (fadeIn - 1) >> 31 masks the state
    if (m_unk34 != nullptr) {
        uint8_t color[4];
        std::memcpy(color, &m_aStates[s].m_textColorRaw, 4);
        color[3] = static_cast<uint8_t>(ppc::fctiwz(static_cast<float>(color[3]) * m_fFade));
        static_cast<IKText2d*>(AsText(m_unk34))->SetColor(color);  // IKText2d vt+0x44
    }
    for (int i = 2; i >= 0; --i) {
        if (m_apUnk38[i] == nullptr) continue;
        uint8_t color[4];
        std::memcpy(color, &m_aStates[s].m_aBillboardColorsRaw[i], 4);
        color[3] = static_cast<uint8_t>(ppc::fctiwz(static_cast<float>(color[3]) * m_fFade));
        AsBillboard(m_apUnk38[i])->SetColor(color);  // IKBillboard2d vt+0x28
    }
    if (m_fFadeTarget != m_fFade) m_baFlags = static_cast<uint8_t>((m_baFlags & ~kFlagFading) | kFlagFading);
    if (m_fFade == 0.0f) {
        Hide();  // vt+0x70
    } else {
        Show();  // vt+0x6c
    }
}

// 0x0051daf0 CKInterfaceButton_Close: the base Close, the elements disabled (vt+0x68: the text, billboards
// 2, 1, 0), then every state's videos stopped (vt+0x78), states 4 down to 0, each table from the last.
void CKInterfaceButton::Close() {
    CKInterfaceButtonBase::Close();
    if (m_unk34 != nullptr) AsNode(m_unk34)->Disable();
    if (m_apUnk38[2] != nullptr) AsNode(m_apUnk38[2])->Disable();
    if (m_apUnk38[1] != nullptr) AsNode(m_apUnk38[1])->Disable();
    if (m_apUnk38[0] != nullptr) AsNode(m_apUnk38[0])->Disable();
    for (int k = 4; k >= 0; --k) {
        TVector<RefPair, 1>& videos = m_aStates[k].m_vVideos;
        for (uint32_t i = videos.m_ui32NbUsedElt; i-- != 0;) {
            IKSerializable* video = videos.m_pBlock[i].m_first;
            if (video != nullptr) static_cast<IKVideo*>(video)->Stop();
        }
    }
}

namespace {

// SetPosition's search (inlined four times per element): the last attachment of the hot spot (m_unk2c)
// whose node is `node`.
SAttached2dObject* FindAttachment(IKSerializable* hotSpot, IKSerializable* node) {
    TVector<SAttached2dObject, 2>& v = static_cast<CFlashHotSpot*>(hotSpot)->m_vp2dObject;
    for (uint32_t i = v.m_ui32NbUsedElt; i-- != 0;) {
        if (v.m_pBlock[i].m_pNode == AsNode(node)) return &v.m_pBlock[i];
    }
    return nullptr;
}

}  // namespace

// 0x0051e008 CKInterfaceButton_SetPosition: the position, then the offset of each element's attachment in
// the hot spot (m_unk2c, a CFlashHotSpot): the text, then billboards 2, 1, 0 (x and y found separately).
void CKInterfaceButton::SetPosition(const CVector2& position) {
    m_vPosition.m_fX = position.m_fX;
    m_vPosition.m_fY = position.m_fY;
    if (m_unk34 != nullptr) {
        if (SAttached2dObject* a = FindAttachment(m_unk2c, m_unk34)) a->m_vPosOffset.m_fX = position.m_fX;
        if (SAttached2dObject* a = FindAttachment(m_unk2c, m_unk34)) a->m_vPosOffset.m_fY = position.m_fY;
    }
    for (int i = 2; i >= 0; --i) {
        if (m_apUnk38[i] == nullptr) continue;
        if (SAttached2dObject* a = FindAttachment(m_unk2c, m_apUnk38[i])) a->m_vPosOffset.m_fX = position.m_fX;
        if (SAttached2dObject* a = FindAttachment(m_unk2c, m_apUnk38[i])) a->m_vPosOffset.m_fY = position.m_fY;
    }
}

// 0x0051e1b8 CKInterfaceButton_Destroy: the base's (0x67ff0, empty), then states 4 down to 0: the three
// textures released (2, 1, 0), the tables freed (+0x64, +0x70, +0x7c, +0x88), the billboard entries'
// textures released (from the last) and that table freed.
void CKInterfaceButton::Destroy() {
    for (int k = 4; k >= 0; --k) {
        StateVisual& s = m_aStates[k];
        for (int i = 2; i >= 0; --i) {
            if (s.m_apTextures[i] != nullptr) TextureRef_Release(s.m_apTextures[i]);
        }
        FreeTable(s.m_vpUnk64);
        FreeTable(s.m_vMenuTransitions);
        FreeTable(s.m_vVideos);
        FreeTable(s.m_vTexts);
        for (uint32_t i = s.m_vBillboards.m_ui32NbUsedElt; i-- != 0;) {
            void* texture = s.m_vBillboards.m_pBlock[i].m_pTexture;
            if (texture != nullptr) TextureRef_Release(texture);
        }
        FreeTable(s.m_vBillboards);
    }
}

// 0x0051eff0 CKInterfaceButton_Create (the constructor inlined; the same stores as 0x51e3b8): the base,
// then +0x48..+0x8f = 0 and every state's tables empty (block 0, capacity 1, count 0). The stores are
// independent; their interleaving is not kept.
CKInterfaceButton::CKInterfaceButton() {
    for (auto& group : m_afSizeAnimX) {
        for (float& f : group) f = 0.0f;
    }
    for (auto& group : m_afSizeAnimY) {
        for (float& f : group) f = 0.0f;
    }
    for (StateVisual& s : m_aStates) ConstructState(s);
}

// 0x0051e700 CKInterfaceButton_Update (vt+0x58), every frame with the frame clock (dt = its
// FIXED_GAME_TIME delta, +0x20). The updated bit set and the fading bit cleared, then per element (billboard
// 2, billboard 1 with the text, billboard 0): unless the fade-out runs, the size animation stepped (a speed
// <= 0 jumps to the target); the element sized (IKBillboard2d vt+0x30) with the stepped values, or the
// current ones during the fade-out; the fading bit while the animation has not arrived or the fade-out runs.
// Then the fade stepped, UpdateVisibility(0), and the fade-out timer counted down.
void CKInterfaceButton::Update(IKTime* frameClock) {
    m_baFlags = static_cast<uint8_t>((m_baFlags & ~kFlagUpdated) | kFlagUpdated);
    m_baFlags = static_cast<uint8_t>(m_baFlags & ~kFlagFading);
    const int32_t order[3] = {2, 1, 0};
    for (int32_t i : order) {
        float* ax = m_afSizeAnimX[i];
        float* ay = m_afSizeAnimY[i];
        CVector2 size;
        if (m_fFadeOutTime <= 0.0f) {  // TOC +0x76ec
            if (ax[1] <= 0.0f) ax[2] = ax[0];
            if (ay[1] <= 0.0f) ay[2] = ay[0];
            size.m_fX = FloatApproach_Step(frameClock->m_afDeltaTime[IKTime::FIXED_GAME_TIME], ax);
            size.m_fY = FloatApproach_Step(frameClock->m_afDeltaTime[IKTime::FIXED_GAME_TIME], ay);
        } else {
            size.m_fX = ax[2];
            size.m_fY = ay[2];
        }
        if (i == 1 && m_unk34 != nullptr) {
            // The text box takes size 1's targets, not the stepped values (before billboard 1 is sized).
            // BUG(original)_maybe: the label's box jumps to the new size while the billboards animate.
            IKText2d* text = AsText(m_unk34);
            text->m_bAutoSize = 0;
            text->m_vBoxSize.m_fY = m_afSizeAnimY[1][0];
            text->m_vBoxSize.m_fX = m_afSizeAnimX[1][0];
            text->ComputeLayout();  // 0x6a468
            // then 0x6a0b0 KStub_Nop_6a0b0
        }
        if (m_apUnk38[i] != nullptr) {
            AsBillboard(m_apUnk38[i])->m_vBillboardSize = size;  // vt+0x30 0x9972d0 BillboardBrush_SetSize_maybe
        }
        if (ax[2] != ax[0] || ay[2] != ay[0] || m_fFadeOutTime > 0.0f) {
            m_baFlags = static_cast<uint8_t>((m_baFlags & ~kFlagFading) | kFlagFading);
        }
    }
    FloatApproach_Step(frameClock->m_afDeltaTime[IKTime::FIXED_GAME_TIME], FadeApproach(this));
    UpdateVisibility(0);  // vt+0x68
    if (m_fFadeOutTime > 0.0f) m_fFadeOutTime = m_fFadeOutTime - frameClock->m_afDeltaTime[IKTime::FIXED_GAME_TIME];
}

// 0x0051f4e8 CKInterfaceButton_Destructor (0x51d2d8 is the same code): states 4 down to 0, each state's
// tables last first (+0x94, +0x88, +0x7c, +0x70, +0x64), then the base destructor.
CKInterfaceButton::~CKInterfaceButton() {
    for (int k = 4; k >= 0; --k) {
        StateVisual& s = m_aStates[k];
        FreeTable(s.m_vBillboards);
        FreeTable(s.m_vTexts);
        FreeTable(s.m_vVideos);
        FreeTable(s.m_vMenuTransitions);
        FreeTable(s.m_vpUnk64);
    }
}

// 0x009c7678 CKInterfaceButton_LoadStateVisual_maybe. Every table is read from its last element down.
void CKInterfaceButton_LoadStateVisual(CKInterfaceButton::StateVisual* s, IKFile* file, int32_t type) {
    ReadRaw(file, &s->m_textColorRaw, 4);
    IKFile_ReadRef(file, &s->m_pTextAccessor);
    // one 0x18-byte read, then every word swapped
    ReadF32LE(file, &s->m_afSize0[0]);
    ReadF32LE(file, &s->m_afSize0[1]);
    ReadF32LE(file, &s->m_afSize[0]);
    ReadF32LE(file, &s->m_afSize[1]);
    ReadF32LE(file, &s->m_afSize2[0]);
    ReadF32LE(file, &s->m_afSize2[1]);
    ReadRaw(file, s->m_abUseAlpha, 3);
    ReadRaw(file, s->m_aBillboardColorsRaw, 12);
    for (float& f : s->m_afAnimDurations) ReadF32LE(file, &f);
    for (uint32_t& w : s->m_aui32SheetRows) ReadU32LE(file, &w);
    for (uint32_t& w : s->m_aui32SheetColumns) ReadU32LE(file, &w);
    for (uint32_t i = 3; i-- != 0;) IKFile_ReadTextureRef(file, &s->m_apTextures[i], 1);

    uint32_t count = 0;
    ReadU32LE(file, &count);
    LoadReserve(s->m_vpUnk64, count);
    if (ReadsFirstRefs(type)) {
        for (uint32_t i = count; i-- != 0;) IKFile_ReadRef(file, &s->m_vpUnk64.m_pBlock[i]);
    }

    ReadU32LE(file, &count);
    LoadReserve(s->m_vMenuTransitions, count);
    for (uint32_t i = count; i-- != 0;) ReadU8(file, &s->m_vMenuTransitions.m_pBlock[i]);

    CKInterfaceButton_LoadRefPairs(&s->m_vVideos, file, type);
    CKInterfaceButton_LoadRefPairValues(&s->m_vTexts, file);
    CKInterfaceButton_LoadTextEntries(&s->m_vBillboards, file);
    IKFile_ReadRef(file, &s->m_pFx);
}

// The three tables both state readers share (count, LoadReserve, the entries from the last down).
void CKInterfaceButton_LoadRefPairs(TVector<CKInterfaceButton::RefPair, 1>* v, IKFile* file, int32_t type) {
    uint32_t count = 0;
    ReadU32LE(file, &count);
    LoadReserve(*v, count);
    for (uint32_t i = count; i-- != 0;) {
        if (ReadsFirstRefs(type)) IKFile_ReadRef(file, &v->m_pBlock[i].m_first);
        IKFile_ReadRef(file, &v->m_pBlock[i].m_second);
    }
}

void CKInterfaceButton_LoadRefPairValues(TVector<CKInterfaceButton::RefPairValue, 1>* v, IKFile* file) {
    uint32_t count = 0;
    ReadU32LE(file, &count);
    LoadReserve(*v, count);
    for (uint32_t i = count; i-- != 0;) {
        CKInterfaceButton::RefPairValue& e = v->m_pBlock[i];
        IKFile_ReadRef(file, &e.m_first);
        IKFile_ReadRef(file, &e.m_second);
        ReadRaw(file, &e.m_valueRaw, 4);
    }
}

void CKInterfaceButton_LoadTextEntries(TVector<CKInterfaceButton::TextEntry, 1>* v, IKFile* file) {
    uint32_t count = 0;
    ReadU32LE(file, &count);
    LoadReserve(*v, count);
    for (uint32_t i = count; i-- != 0;) {
        CKInterfaceButton::TextEntry& e = v->m_pBlock[i];
        IKFile_ReadRef(file, &e.m_pText);
        IKFile_ReadTextureRef(file, &e.m_pTexture, 1);
        ReadU32LE(file, &e.m_unk08);
        ReadU32LE(file, &e.m_unk0c);
        ReadU32LE(file, &e.m_unk10);
    }
}

// 0x0051f638 CKInterfaceButton_Load: no type test of its own (the base and the state reader test it).
int32_t CKInterfaceButton::Load(IKFile* file, int32_t type) {
    CKInterfaceButtonBase::Load(file, type);
    ReadF32LE(file, &m_fAnimSpeed);
    ReadU8(file, &m_unk3b4);
    for (uint32_t i = 5; i-- != 0;) CKInterfaceButton_LoadStateVisual(&m_aStates[i], file, type);
    ReadF32LE(file, &m_fUnk3bc);
    IKFile_ReadRef(file, &m_unk34);
    IKFile_ReadObjectRefArray(file, m_apUnk38, 3);
    IKFile_ReadRef(file, &m_pSounds);
    return 1;
}

namespace {
void RegisterIf(IKSerializable* object, int32_t type) {
    if (object != nullptr) object->RecursiveRegistration(type);  // vt+0x24
}
}  // namespace

// 0x0051cdc0 CKInterfaceButton_RecursiveRegistration (each table from its last element down)
void CKInterfaceButton::RecursiveRegistration(int32_t type) {
    CKInterfaceButtonBase::RecursiveRegistration(type);  // 0x00067fe8
    for (int k = 4; k >= 0; --k) {
        StateVisual& s = m_aStates[k];
        s.m_pTextAccessor->RecursiveRegistration(type);
        for (uint32_t i = s.m_vpUnk64.m_ui32NbUsedElt; i != 0; --i) RegisterIf(s.m_vpUnk64.m_pBlock[i - 1], type);
        for (uint32_t i = s.m_vVideos.m_ui32NbUsedElt; i != 0; --i) {
            RegisterIf(s.m_vVideos.m_pBlock[i - 1].m_first, type);
            RegisterIf(s.m_vVideos.m_pBlock[i - 1].m_second, type);
        }
        for (uint32_t i = s.m_vTexts.m_ui32NbUsedElt; i != 0; --i) {
            s.m_vTexts.m_pBlock[i - 1].m_second->RecursiveRegistration(type);
            RegisterIf(s.m_vTexts.m_pBlock[i - 1].m_first, type);
        }
        for (uint32_t i = s.m_vBillboards.m_ui32NbUsedElt; i != 0; --i) RegisterIf(s.m_vBillboards.m_pBlock[i - 1].m_pText, type);
        RegisterIf(s.m_pFx, type);
    }
    RegisterIf(m_unk34, type);
    RegisterIf(m_apUnk38[2], type);
    RegisterIf(m_apUnk38[1], type);
    RegisterIf(m_apUnk38[0], type);
    m_pSounds->RecursiveRegistration(type);
}
