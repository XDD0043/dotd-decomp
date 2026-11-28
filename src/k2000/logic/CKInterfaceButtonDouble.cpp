// CKInterfaceButtonDouble.cpp - reconstructed original translation unit 0x51f930-0x5255c0 (GAME_TOC1, main_toc1), 35 functions, 32 live.
// Primary class: CKInterfaceButtonDouble  key 0x634c  category Logic  size 0x410  vtable 0xb2b7f8
// Other owners: CKInterfaceScrollingMenu (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x51f930  CKInterfaceButtonDouble_Delete
//   [ ] 0x51f980  CKInterfaceButtonDouble_ComputeAnimRate_maybe  [dead]
//   [x] 0x51f9d8  CKInterfaceButtonDouble_Show
//   [x] 0x51fb88  CKInterfaceButtonDouble_Hide
//   [ ] 0x51fd30  RegisterCKInterfaceButtonDoubleClass
//   [ ] 0x51fda8  _GLOBAL__I_51fda8
//   [x] 0x51fdb8  CKInterfaceButtonDouble_RefreshValueText
//   [x] 0x520358  CKInterfaceButtonDouble_LoadOptionValue
//   [x] 0x520810  CKInterfaceButtonDouble_ChangeValue_maybe
//   [x] 0x520d98  CKInterfaceButtonDouble_SetVisualState
//   [ ] 0x521ac0  CKInterfaceButtonDouble_Save
//   [x] 0x521ae8  CKInterfaceButtonDouble_RecursiveRegistration
//   [x] 0x5220d0  CKInterfaceButtonDouble_DeleteArray
//   [x] 0x522178  CKInterfaceButtonDouble_Construct_2  (the same code as 0x522ef8 CKInterfaceButtonDouble_Construct)
//   [x] 0x5222a8  CKInterfaceButtonDouble_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x5222d8  CKInterfaceButtonDouble_SetDisabled
//   [x] 0x5223e0  CKInterfaceButtonDouble_SetInteractionState
//   [x] 0x5224d0  CKInterfaceButtonDouble_SetPosition
//   [x] 0x5228f0  CKInterfaceButtonDouble_UpdateVisibility
//   [x] 0x522e68  CKInterfaceButtonDouble_StartFadeOut
//   [x] 0x522ef8  CKInterfaceButtonDouble_Construct
//   [x] 0x523028  CKInterfaceButtonDouble_Close
//   [x] 0x523280  CKInterfaceButtonDouble_DeletingDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x5232c8  CKInterfaceButtonDouble_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x5232f8  CKInterfaceButtonDouble_PostLoad
//   [x] 0x523300  CKInterfaceButtonDouble_Open
//   [x] 0x523690  CKInterfaceButtonDouble_Destroy
//   [x] 0x5239a8  CKInterfaceButtonDouble_AnimatePart
//   [x] 0x523b48  CKInterfaceButtonDouble_Update
//   [x] 0x523d00  CKInterfaceButtonDouble_CreateArray
//   [x] 0x523f08  CKInterfaceButtonDouble_Create
//   [x] 0x524060  CKInterfaceButtonDouble_Load
//   [x] 0x5252f8  CKInterfaceScrollingMenu_Delete  (DOTD_DECLARE_FACTORIES in CKInterfaceScrollingMenu.h: F05's class)
//   [ ] 0x525348  FUN_00525348  [dead]
//   [ ] 0x525470  FUN_00525470  [dead]
//
//   [x] 0x9c8408  CKInterfaceButtonDouble_IsKindOfClass  [inline]
//   [x] 0x9c8430  CKInterfaceButtonDouble_GetClassType  [inline]
//   [x] 0x9c8438  CKInterfaceButtonDouble_GetClassID  [inline]
//   [x] 0x9c8440  CKInterfaceButtonDouble_IsFadeOutFinished_maybe  [inline]
//   [x] 0x9c8468  CKInterfaceButtonDouble_vf88  [inline]
//   [x] 0x9c8470  CKInterfaceButtonDouble_vf8C  [inline]
#include "crt/xlround.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/logic/CKInterfaceButtonDouble.h"

#include <cmath>
#include <cstdio>
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
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/ui/CLocManager.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/misc/Wcs.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"

class CKSound;

namespace {

using Ramp = CKInterfaceButtonDouble::Ramp;

CText2d* AsText(IKSerializable* node) { return static_cast<CText2d*>(node); }
CBillboard2d* AsBillboard(IKSerializable* node) { return static_cast<CBillboard2d*>(node); }
float DeltaTime(const IKTime* frameClock) { return frameClock->m_afDeltaTime[IKTime::FIXED_GAME_TIME]; }  // +0x20

// The text of a CKLocTextAccessor as the buttons inline it: the list's first text when it has a list,
// else +0x10 (no null check on the accessor).
IKSerializable* AccessorText(IKSerializable* accessor) {
    CKLocTextAccessor* a = static_cast<CKLocTextAccessor*>(accessor);
    return a->m_texts.m_pBlock != nullptr ? a->m_texts.m_pBlock[0] : a->m_pText;
}

// A colour of a record: its 4 file bytes (RGBA), as the original copies the word to the stack for SetColor.
void CopyColor(uint8_t* out, const void* raw) { std::memcpy(out, raw, 4); }

// ---- The game manager's edited options (CDefaultGameManager::m_editedOptions, +0xec) by the byte offset
// the original reads (+0xec language, +0xf0 subtitles, +0xf1 tutorial, +0xf4 sound output, +0xf8 aspect,
// +0xfc/+0x100/+0x104 the volumes, +0x108.. the per-player bytes, +0x119/+0x11a motion sensor, +0x11c
// brightness). The setters are the game manager's (CDefaultGameManager.cpp).
uint32_t OptionWord(const CDefaultGameManager* gm, uint32_t offset) {
    const SGameOptions& o = gm->m_editedOptions;
    switch (offset) {
    case 0xec: return o.m_ui32Language;
    case 0xf4: return o.m_ui32SoundOutput;
    case 0xf8: return o.m_ui32AspectRatio;
    case 0x11c: return o.m_ui32Brightness;
    default: return 0;
    }
}
uint8_t OptionByte(const CDefaultGameManager* gm, uint32_t offset) {
    const SGameOptions& o = gm->m_editedOptions;
    switch (offset) {
    case 0xf0: return o.m_bSubtitles;
    case 0xf1: return o.m_bTutorialInfoPopups;
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
float& OptionFloatRef(CDefaultGameManager* gm, uint32_t offset) {
    return gm->m_editedOptions.m_afVolumes[(offset - 0xfc) / 4];  // +0xfc, +0x100, +0x104
}
float OptionFloat(CDefaultGameManager* gm, uint32_t offset) { return OptionFloatRef(gm, offset); }
void SetOptionFloat(CDefaultGameManager* gm, uint32_t offset, float value) { OptionFloatRef(gm, offset) = value; }
// +0x32c (CKS08GameManager) the video mode index; -1 none.
int32_t VideoModeIndex(CDefaultGameManager* gm) { return static_cast<int32_t>(static_cast<CKS08GameManager*>(gm)->m_unk32C[0]); }

// The game manager's option setters, under their Ghidra names (the ports are CDefaultGameManager members).
void IKGameManager_ApplyEditedOptions(CDefaultGameManager* gm) { gm->ApplyEditedOptions(); }  // 0x13c18 (and _2/_3/_4)
void CDefaultGameManager_TogglePlayerVibration(CDefaultGameManager* gm, int32_t player) { gm->TogglePlayerVibration(player); }
void CDefaultGameManager_ToggleVibrationBothPlayers(CDefaultGameManager* gm) { gm->ToggleVibrationBothPlayers(); }
void IKGameManager_ToggleSubtitlesOption(CDefaultGameManager* gm) { gm->ToggleSubtitlesOption(); }
void IKGameManager_CycleLanguageOption(CDefaultGameManager* gm, uint8_t down) { gm->CycleLanguageOption(down); }
void IKGameManager_ToggleMotionSensorOption(CDefaultGameManager* gm, uint8_t player) { gm->ToggleMotionSensorOption(player); }
void IKGameManager_ToggleAspectRatioOption(CDefaultGameManager* gm, uint8_t down) { gm->ToggleAspectRatioOption(down); }
void IKGameManager_StepBrightnessOption(CDefaultGameManager* gm, uint8_t down) { gm->StepBrightnessOption(down); }
void IKGameManager_CycleSoundOutputOption(CDefaultGameManager* gm, uint8_t down) { gm->CycleSoundOutputOption(down); }
void IKGameManager_ToggleOptionF1(CDefaultGameManager* gm) { gm->ToggleOption05(); }
void IKGameManager_ToggleMotionSensorBothPlayersOption(CDefaultGameManager* gm) { gm->ToggleMotionSensorBothPlayersOption(); }
void IKGameManager_TogglePerPlayerOption10CBothPlayers(CDefaultGameManager* gm) { gm->TogglePerPlayerOption20BothPlayers(); }
void IKGameManager_TogglePerPlayerOption10ABothPlayers(CDefaultGameManager* gm) { gm->TogglePerPlayerOption1EBothPlayers(); }

// 0x00a6f380: the sound output modes' text index (+6 into the game manager's +0x144 text list).
const int32_t kSoundOutputTextIndex[5] = {0, 1, 3, 4, 5};

// The sound output's text (mode 8): the game manager's +0x144 accessor, its list's entry
// kSoundOutputTextIndex[+0xf4] + 6, else its single text.
IKSerializable* SoundOutputText(CDefaultGameManager* gm) {
    CKLocTextAccessor* texts = static_cast<CKLocTextAccessor*>(gm->m_pPromptTextAccessor);
    const uint32_t mode = OptionWord(gm, 0xf4);  // CycleSoundOutputOption keeps it in [0, 4]
    if (texts->m_texts.m_pBlock == nullptr) return texts->m_pText;
    return texts->m_texts.m_pBlock[kSoundOutputTextIndex[mode] + 6];
}

// 0x00059618 KStub_Nop_59618 (CKGraphic vt: the video mode's resolution): empty on the PS3.
// BUG(original): the callers then format the stack words it should have filled ("%dx%d"); here they are 0.
void CKGraphic_GetVideoModeResolution(int32_t /*mode*/, int32_t* width, int32_t* height, int32_t* rate) {
    *width = 0;
    *height = 0;
    *rate = 0;
}

// 0x00059a88 Graphics_GetNumVideoModes_maybe: RwEngineGetNumVideoModes 0x74a388 (through 0x98d6f0), the
// PSGL device system's request 5 (RwPSGLDeviceSystem_maybe 0x739050): the count its open (request 0) sets at
// 0x00c45990, 1 (the one mode of the device it creates).
int32_t Graphics_GetNumVideoModes() { return 1; }

// 0x00a6f394: the aspect ratios by the aspect option (0: 4/3 0x3faaaaab, 1: 16/9 0x3fe38e39; the option is 0 or 1).
const float kAspectRatios[2] = {0x1.555556p+0f, 0x1.c71c72p+0f};

// 0x00015240 FindVideoModeMatchingAspect_maybe (a CDefaultGameManager method, vtable 0xb35840): from `index`,
// stepping down (`down`) or up, the first video mode of depth 32, more than 600 pixels wide, whose
// lroundf(width / height x 1000) equals lroundf(the aspect's ratio x 1000); 1 and *found (when not null) then,
// 0 past the ends. The mode's width, height and depth come from CKGraphic_GetVideoModeInfos 0x59618, empty on
// the PS3: BUG(original) the stack words it should fill are read as they are (0 here, as above: no mode
// matches).
uint8_t FindVideoModeMatchingAspect(CDefaultGameManager* /*gm*/, uint8_t down, int32_t index, uint8_t aspect,
                                    int32_t* found) {
    const int32_t count = Graphics_GetNumVideoModes();
    if (down == 0) {
        if (!(count > index)) return 0;
    } else if (index < 0) {
        return 0;
    }
    for (;;) {
        int32_t width;
        int32_t height;
        int32_t depth;
        CKGraphic_GetVideoModeResolution(index, &width, &height, &depth);
        const float ratio = static_cast<float>(static_cast<double>(width)) / static_cast<float>(static_cast<double>(height));
        const int32_t rounded = crt::lroundf(ratio * 1000.0f);  // TOC1 -0x7ecc; lroundf_maybe 0x77ed68
        if (depth == 0x20 && width > 600 && rounded == crt::lroundf(kAspectRatios[aspect] * 1000.0f)) {
            if (found != nullptr) *found = index;
            return 1;
        }
        if (down == 0) {
            ++index;
            if (!(count > index)) return 0;
        } else {
            --index;
            if (index < 0) return 0;
        }
    }
}

// ---- Callees in other classes that are not ported yet (local copies).

// 0x00066cb8 BillboardBrush_SetTexture (IKBillboard2d vt+0x3c): the brush's texture when it differs.
void BillboardBrush_SetTexture(IKSerializable* node, void* texture) {
    IKBillboard2d* part = AsBillboard(node);
    Rt2dBrush* brush = part->m_pBrush;
    if (brush == nullptr) return;
    if (brush->texture != texture) Rt2dBrushSetTexture(brush, static_cast<RwTexture*>(texture));
}
// 0x009972d0 BillboardBrush_SetSize_maybe (IKBillboard2d vt+0x30)
void BillboardBrush_SetSize(IKSerializable* node, const float* size) {
    IKBillboard2d* part = AsBillboard(node);
    part->m_vBillboardSize.m_fX = size[0];
    part->m_vBillboardSize.m_fY = size[1];
}
// 0x0005b098 CBillboard2d_SetAnimTime_maybe: the sprite-sheet duration; 0 resets the UVs to the whole
// texture (u0 0, v0 1, u1 1, v1 1, u2 1, v2 0, u3 0, v3 0) and applies them (IKBillboard2d vt+0x34).
void CBillboard2d_SetAnimTime(CBillboard2d* billboard, float duration) { billboard->SetAnimTime(duration); }  // the CBillboard2d port
// 0x0005b118 CBillboard2d_SetSpriteSheetRows_maybe (0 counts as 1); the animation restarts.
void CBillboard2d_SetSpriteSheetRows(CBillboard2d* billboard, int32_t rows) { billboard->SetSpriteSheetRows(static_cast<int32_t>(rows)); }
// 0x0005b158 CBillboard2d_SetSpriteSheetColumns_maybe
void CBillboard2d_SetSpriteSheetColumns(CBillboard2d* billboard, int32_t columns) { billboard->SetSpriteSheetColumns(static_cast<int32_t>(columns)); }

// 0x00066300 CText2d_SetTextAscii (CText2d vt+0x90): the CText2d port (through the linked text, else
// TextData_SetTextAscii 0x6b1b8, whose strings of 400 characters or more become the TOC string "text too big").
void CText2d_SetTextAscii(CText2d* text, const char* ascii) { text->SetTextAscii(ascii); }

// 0x00514668 KBase730C_CallOwnerVfDCObjectVf78AfterVf308_maybe: the menus' interface video stopped, its
// segment kept as the current one (game manager vt+0xdc, vt+0x308, the video's vt+0x78).
void KBase730C_StopInterfaceVideo(IKSerializable* menu) {
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(static_cast<CKMenuBase114c*>(menu)->m_pGameManager);
    IKVideo* video = manager->GetInterfaceVideo();
    if (video == nullptr) return;
    manager->SetInterfaceSegment(video->m_pSegment);
    video->Stop();
}

// 0x00112bc0 CKSoundDictionaryID_GetSound (no bounds check)
CKSound* CKSoundDictionaryID_GetSound(IKSerializable* dictionary, uint32_t index) {
    return static_cast<CKSoundDictionaryID*>(dictionary)->GetSound(index);  // the audio port
}
// 0x00111b70 CKSound_ResetPan_maybe / 0x00111230 CKSound_Play (CKSound::ResetPan / Play, k2000/logic/sound/CKSound.cpp).
void CKSound_ResetPan(CKSound* sound, uint8_t pan) { sound->ResetPan(static_cast<int32_t>(pan)); }  // the audio port
void CKSound_Play(CKSound* sound, float delay) { sound->Play(delay); }  // the audio port

// RecordB::m_unk3c: a CParticlesNodeFx (the fields the two inlined blocks touch are CParticlesNodeFx's, the
// same blocks as CKInterfaceButton's and CKInterfaceCheckBox's state effects; null in every front-end item).
// SetVisualState (0x5215c8): below 64 points, the null vector (0x00c50d64, (0, 0, 0)) appended to the
// emitter's point list (m_pAdvEmtPointList->pointList, 12 bytes each) with property 0x2000; then properties
// 0x200 | 0x400 set and 0x80000 cleared, the emission speed adjustment 0, the RpPrtStdEmitter's flags |= 0xa
// (ACTIVE | EMIT).
void StateEffect_Start(IKSerializable* effect) {
    if (effect == nullptr) return;
    static const RwV3d kNullVector = {0.0f, 0.0f, 0.0f};  // g_nullVector 0x00c50d64
    CParticlesNodeFx* fx = static_cast<CParticlesNodeFx*>(effect);
    if (fx->m_ui8NbActivePoints <= 0x3f) {
        fx->m_pAdvEmtPointList->pointList[fx->m_ui8NbActivePoints] = kNullVector;
        fx->m_sgProperties = (fx->m_sgProperties & ~0x2000u) | 0x2000u;
        fx->m_ui8NbActivePoints = static_cast<uint8_t>(fx->m_ui8NbActivePoints + 1);
    }
    uint32_t properties = fx->m_sgProperties;
    properties = (properties & ~0x200u) | 0x200u;
    properties = (properties & ~0x400u) | 0x400u;
    fx->m_sgProperties = properties & ~0x80000u;
    fx->m_fEmissionSpeedAdjustment = 0.0f;  // stw 0
    fx->m_pRpPrtStdEmitter->flag |= rpPRTSTDEMITTERFLAGACTIVE | rpPRTSTDEMITTERFLAGEMIT;
}
// Open (0x5234a4): properties 0x80400 cleared, the emitter's EMIT flag (8) cleared.
void StateEffect_Reset(IKSerializable* effect) {
    if (effect == nullptr) return;
    CParticlesNodeFx* fx = static_cast<CParticlesNodeFx*>(effect);
    fx->m_sgProperties &= 0xfff7fbffu;
    fx->m_pRpPrtStdEmitter->flag &= ~static_cast<uint32_t>(rpPRTSTDEMITTERFLAGEMIT);
}

// Local copy of 0x0077ed68 lroundf_maybe (bridge 0x0098d3a0; the same body as TextData.cpp's copy: src/crt
// has no port yet).
int32_t LRoundF(float x) { return crt::lroundf(x); }  // src/crt/xlround

// A ramp's speed so that it arrives with the reference ramp: speed x |(new target - old target) / delta|
// (fdivs, the sign cleared through the stack, fmuls); the plain speed when the reference does not move.
float RampSpeed(float speed, float target, const Ramp& ramp, float delta) {
    if (delta == 0.0f) return speed;
    return speed * std::fabs((target - ramp.m_fTarget) / delta);
}

// The arrows' visibility with kOptionHideArrows (inlined in ChangeValue and SetVisualState): the left one
// hidden at the first value, the right one at the last (the first wins with one value).
void UpdateArrows(CKInterfaceButtonDouble* button) {
    IKNode2d* left = static_cast<IKNode2d*>(button->m_apUnk50[0]);
    IKNode2d* right = static_cast<IKNode2d*>(button->m_apUnk50[1]);
    const uint8_t value = button->m_ui8Value;
    if (value == 0) {
        left->Disable();   // vt+0x68
        right->Enable();   // vt+0x64
    } else if (value == button->m_ui8NbEntries - 1) {
        left->Enable();
        right->Disable();
    } else {
        left->Enable();
        right->Enable();
    }
}

// The fade applied to a colour (UpdateVisibility): alpha = fctiwz(alpha x fade) (fmuls), stored as a byte.
void FadedColor(uint8_t* out, const void* raw, float fade) {
    CopyColor(out, raw);
    out[3] = static_cast<uint8_t>(ppc::fctiwz(static_cast<float>(out[3]) * fade));
}

}  // namespace

// The element constructor of the entry array (inlined in the Load's OperatorNewArray loop): the three
// tables empty (block 0, capacity 1, count 0); +0x00 and +0x04 are left as they are.
CKInterfaceButtonDouble::Entry::Entry() {
    m_vVideos = {nullptr, 1, 0};
    m_vTexts = {nullptr, 1, 0};
    m_vImages = {nullptr, 1, 0};
}

// 0x0051f9d8 CKInterfaceButtonDouble_Show: the shown bit, then every element enabled (vt+0x64).
void CKInterfaceButtonDouble::Show() {
    m_baFlags = static_cast<uint8_t>(m_baFlags | kFlagShown);
    IKSerializable* const nodes[] = {m_pLabel, m_pValueText, m_pValueImage, m_apUnk50[1], m_apUnk50[0], m_apUnk58[1], m_apUnk58[0]};
    for (IKSerializable* node : nodes) {
        if (node != nullptr) static_cast<IKNode2d*>(node)->Enable();
    }
}

// 0x0051fb88 CKInterfaceButtonDouble_Hide: the shown bit cleared, every element disabled (vt+0x68).
void CKInterfaceButtonDouble::Hide() {
    m_baFlags = static_cast<uint8_t>(m_baFlags & ~kFlagShown);
    IKSerializable* const nodes[] = {m_pLabel, m_pValueText, m_pValueImage, m_apUnk50[1], m_apUnk50[0], m_apUnk58[1], m_apUnk58[0]};
    for (IKSerializable* node : nodes) {
        if (node != nullptr) static_cast<IKNode2d*>(node)->Disable();
    }
}

// 0x0051fdb8 CKInterfaceButtonDouble_RefreshValueText
void CKInterfaceButtonDouble::RefreshValueText() {
    CDefaultGameManager* gm = g_pEngine->m_gameManager;
    const uint8_t mode = static_cast<uint8_t>(m_ui8Mode & 0x1f);
    CText2d* valueText = AsText(m_pValueText);
    bool entryText = false;
    char ascii[0x48];
    if (mode == 8) {
        // the sound output: its own text list
        if (valueText != nullptr) valueText->SetTextById(SoundOutputText(gm));
    } else if (mode == 0x12) {
        // the video mode: "%dx%d" (TOC1 +0x7768) unless there is none
        if (valueText != nullptr) {
            const int32_t videoMode = VideoModeIndex(gm);
            if (videoMode == -1) {
                entryText = true;
            } else {
                int32_t width;
                int32_t height;
                int32_t rate;
                CKGraphic_GetVideoModeResolution(videoMode, &width, &height, &rate);
                std::snprintf(ascii, sizeof(ascii), "%dx%d", width, height);  // FormatString 0x98d3b0
                CText2d_SetTextAscii(AsText(m_pValueText), ascii);              // vt+0x90
            }
        }
    } else if (mode == 2) {
        // the brightness: "%d" (TOC1 +0x776c) of +0x11c
        if (valueText != nullptr) {
            std::snprintf(ascii, sizeof(ascii), "%d", static_cast<int32_t>(OptionWord(gm, 0x11c)));
            CText2d_SetTextAscii(AsText(m_pValueText), ascii);
        }
    } else {
        entryText = valueText != nullptr;
    }
    if (entryText) valueText->SetTextById(AccessorText(m_aEntries[m_ui8Value].m_pText));  // vt+0x88

    if (m_pValueImage != nullptr) {
        void* texture = m_aEntries[m_ui8Value].m_pTexture;
        if (texture != nullptr) BillboardBrush_SetTexture(m_pValueImage, texture);
    }

    // The entry's videos, unless the clock is stopped: a segment is played (mode 3), else its video started.
    if (g_pEngine->m_timeManager->m_pTime->m_eCurrentState != IKTime::STOPPED) {
        for (uint32_t i = m_aEntries[m_ui8Value].m_vVideos.m_ui32NbUsedElt; i-- != 0;) {
            const CKInterfaceButton::RefPair& pair = m_aEntries[m_ui8Value].m_vVideos.m_pBlock[i];
            if (pair.m_second != nullptr) {
                KBase730C_StopInterfaceVideo(m_pMenu);
                static_cast<CKVideoSegment*>(m_aEntries[m_ui8Value].m_vVideos.m_pBlock[i].m_second)->Play(3, 0, 0);
            } else if (pair.m_first != nullptr) {
                KBase730C_StopInterfaceVideo(m_pMenu);
                static_cast<IKVideo*>(m_aEntries[m_ui8Value].m_vVideos.m_pBlock[i].m_first)->Start(nullptr);  // vt+0x60
            }
        }
    }
    // The entry's texts: each CText2d gets its accessor's text.
    for (uint32_t i = m_aEntries[m_ui8Value].m_vTexts.m_ui32NbUsedElt; i-- != 0;) {
        const CKInterfaceButton::RefPair& pair = m_aEntries[m_ui8Value].m_vTexts.m_pBlock[i];
        if (pair.m_first != nullptr) AsText(pair.m_first)->SetTextById(AccessorText(pair.m_second));  // vt+0x88
    }
    // The entry's images: texture, sprite-sheet duration (a float in the word), rows and columns.
    for (uint32_t i = m_aEntries[m_ui8Value].m_vImages.m_ui32NbUsedElt; i-- != 0;) {
        const CKInterfaceButton::TextEntry& image = m_aEntries[m_ui8Value].m_vImages.m_pBlock[i];
        if (image.m_pText == nullptr || image.m_pTexture == nullptr) continue;
        BillboardBrush_SetTexture(image.m_pText, image.m_pTexture);
        float duration;
        std::memcpy(&duration, &image.m_unk08, sizeof(duration));
        CBillboard2d_SetAnimTime(AsBillboard(image.m_pText), duration);
        CBillboard2d_SetSpriteSheetRows(AsBillboard(image.m_pText), static_cast<int32_t>(image.m_unk0c));
        CBillboard2d_SetSpriteSheetColumns(AsBillboard(image.m_pText), static_cast<int32_t>(image.m_unk10));
    }
}

// 0x00520358 CKInterfaceButtonDouble_LoadOptionValue. The modes not listed keep the value (Open sets 0).
void CKInterfaceButtonDouble::LoadOptionValue() {
    CDefaultGameManager* gm = g_pEngine->m_gameManager;
    int32_t value = m_ui8Value;
    char ascii[0x58];
    switch (m_ui8Mode & 0x1f) {
    case 2:  // brightness (+0x11c), also shown as "%d"
        value = static_cast<int32_t>(OptionWord(gm, 0x11c));
        if (m_pValueText != nullptr) {
            std::snprintf(ascii, sizeof(ascii), "%d", value);
            CText2d_SetTextAscii(AsText(m_pValueText), ascii);  // vt+0x90
        }
        break;
    case 4: value = OptionByte(gm, 0xf0) ^ 1; break;
    case 5:
    case 6: value = OptionByte(gm, 0x108) ^ 1; break;
    case 7: value = OptionByte(gm, 0x109) ^ 1; break;
    case 8:  // sound output (+0xf4), with its own text
        value = static_cast<int32_t>(OptionWord(gm, 0xf4));
        if (m_pValueText != nullptr) AsText(m_pValueText)->SetTextById(SoundOutputText(gm));  // vt+0x88
        break;
    // the volumes: lroundf(entries x volume) (fmuls)
    case 9: value = LRoundF(static_cast<float>(m_ui8NbEntries) * OptionFloat(gm, 0x104)); break;
    case 10: value = LRoundF(static_cast<float>(m_ui8NbEntries) * OptionFloat(gm, 0x100)); break;
    case 11: value = LRoundF(static_cast<float>(m_ui8NbEntries) * OptionFloat(gm, 0xfc)); break;
    case 12: value = OptionByte(gm, 0x10a) == 0 ? 1 : (OptionByte(gm, 0x10b) == 0 ? 1 : 0); break;
    case 13: value = OptionByte(gm, 0x10a) ^ 1; break;
    case 14: value = OptionByte(gm, 0x10b) ^ 1; break;
    case 15: value = OptionByte(gm, 0x10c) == 0 ? 1 : (OptionByte(gm, 0x10d) == 0 ? 1 : 0); break;
    case 16: value = OptionByte(gm, 0x10c) ^ 1; break;
    case 17: value = OptionByte(gm, 0x10d) ^ 1; break;
    case 0x12: {  // the video mode (+0x32c), shown as "%dx%d"
        const int32_t videoMode = VideoModeIndex(gm);
        if (videoMode == -1) break;
        value = videoMode;
        if (m_pValueText != nullptr) {
            int32_t width;
            int32_t height;
            int32_t rate;
            CKGraphic_GetVideoModeResolution(videoMode, &width, &height, &rate);
            std::snprintf(ascii, sizeof(ascii), "%dx%d", width, height);
            CText2d_SetTextAscii(AsText(m_pValueText), ascii);
        }
        break;
    }
    case 0x13: value = static_cast<int32_t>(OptionWord(gm, 0xf8)); break;  // aspect ratio
    case 0x16: value = OptionByte(gm, 0x119) == 0 ? 1 : (OptionByte(gm, 0x11a) == 0 ? 1 : 0); break;
    case 0x17: value = OptionByte(gm, 0x119) ^ 1; break;
    case 0x18: value = OptionByte(gm, 0x11a) ^ 1; break;
    case 0x19: value = OptionByte(gm, 0xf1) ^ 1; break;
    default: break;  // 0, 1 (language: not read back), 3, 0x14, 0x15 and above
    }
    if (value < 0) {
        m_ui8Value = 0;
    } else if (m_ui8NbEntries - 1 < value) {
        m_ui8Value = static_cast<uint8_t>(m_ui8NbEntries - 1);
    } else {
        m_ui8Value = static_cast<uint8_t>(value);
    }
    RefreshValueText();
    // Modes 7, 14, 17, 21 and 24 (the second player's options) are disabled with fewer than two players.
    const uint32_t mode = m_ui8Mode & 0x1fu;
    if (mode <= 0x18 && ((1u << mode) & 0x1224080u) != 0) {
        SetDisabled(gm->GetPlayerCount() <= 1 ? 1 : 0);  // vt+0x84, game manager vt+0x154
    }
}

// 0x00520810 CKInterfaceButtonDouble_ChangeValue_maybe
void CKInterfaceButtonDouble::ChangeValue(int32_t state) {
    CDefaultGameManager* gm = g_pEngine->m_gameManager;
    if (state == 4) {
        uint8_t changed = 0;
        if (m_bDecrease != 0) {
            if (m_ui8Value != 0) {
                m_ui8Value = static_cast<uint8_t>(m_ui8Value - 1);
                changed = 1;
            } else if ((m_baOptions & kOptionWrap) != 0) {
                m_ui8Value = static_cast<uint8_t>(m_ui8NbEntries - 1);
                changed = 1;
            }
        } else {
            if (static_cast<int32_t>(m_ui8Value) < m_ui8NbEntries - 1) {
                m_ui8Value = static_cast<uint8_t>(m_ui8Value + 1);
                changed = 1;
            } else if ((m_baOptions & kOptionWrap) != 0) {
                m_ui8Value = 0;
                changed = 1;
            }
        }
        if ((m_baOptions & kOptionHideArrows) != 0) UpdateArrows(this);
        // The value as a fraction of the entries (the volumes): fcfid + frsp of both bytes, fdivs.
        const float ratio = static_cast<float>(m_ui8Value) / static_cast<float>(m_ui8NbEntries);
        const uint8_t down = m_bDecrease;
        switch (m_ui8Mode & 0x1f) {
        case 1: IKGameManager_CycleLanguageOption(gm, down); break;  // every time, even unchanged
        case 2:
            if (changed) IKGameManager_StepBrightnessOption(gm, down);
            break;
        case 4:
            if (changed) IKGameManager_ToggleSubtitlesOption(gm);
            break;
        case 5:
            if (changed) {
                CDefaultGameManager_ToggleVibrationBothPlayers(gm);
                IKGameManager_ApplyEditedOptions(gm);
            }
            break;
        case 6:
            if (changed) {
                CDefaultGameManager_TogglePlayerVibration(gm, 0);
                IKGameManager_ApplyEditedOptions(gm);
            }
            break;
        case 7:
            if (changed) {
                CDefaultGameManager_TogglePlayerVibration(gm, 1);
                IKGameManager_ApplyEditedOptions(gm);
            }
            break;
        case 8: IKGameManager_CycleSoundOutputOption(gm, down); break;  // every time, even unchanged
        case 9:  // the volumes: the fraction stored, then 0x173e8 / 0x175a8 / 0x174d8 (ApplyEditedOptions_2/4/3)
            if (changed) {
                SetOptionFloat(gm, 0x104, ratio);
                gm->ApplyEditedOptions2();
            }
            break;
        case 10:
            if (changed) {
                SetOptionFloat(gm, 0x100, ratio);
                gm->ApplyEditedOptions4();
            }
            break;
        case 11:
            if (changed) {
                SetOptionFloat(gm, 0xfc, ratio);
                gm->ApplyEditedOptions3();
            }
            break;
        case 12:
            if (changed) IKGameManager_TogglePerPlayerOption10ABothPlayers(gm);
            break;
        case 15:
            if (changed) IKGameManager_TogglePerPlayerOption10CBothPlayers(gm);
            break;
        case 0x12: {  // the video mode: the next one with the aspect (+0xfb, the low byte of +0xf8)
            const int32_t videoMode = VideoModeIndex(gm);
            if (videoMode == -1) break;
            int32_t found;
            const uint8_t aspect = static_cast<uint8_t>(OptionWord(gm, 0xf8));
            const uint8_t ok = down != 0 ? FindVideoModeMatchingAspect(gm, 1, videoMode - 1, aspect, &found)
                                         : FindVideoModeMatchingAspect(gm, 0, videoMode + 1, aspect, &found);
            if (ok != 0) static_cast<CKS08GameManager*>(gm)->m_unk32C[0] = static_cast<uint32_t>(found);
            break;
        }
        case 0x13:  // the aspect ratio, read back as the value
            IKGameManager_ToggleAspectRatioOption(gm, down != 0 ? 1 : 0);
            m_ui8Value = static_cast<uint8_t>(OptionWord(gm, 0xf8));
            break;
        // 0x16..0x18 (motion sensor) test the direction instead of the change: only a decrease toggles.
        case 0x16:
            if (down != 0) IKGameManager_ToggleMotionSensorBothPlayersOption(gm);
            break;
        case 0x17:
            if (down != 0) IKGameManager_ToggleMotionSensorOption(gm, 0);
            break;
        case 0x18:
            if (down != 0) IKGameManager_ToggleMotionSensorOption(gm, 1);
            break;
        case 0x19:
            if (changed) IKGameManager_ToggleOptionF1(gm);
            break;
        default: break;  // 0, 3, 13, 14, 16, 17, 0x14, 0x15; above 0x19 the jump table is skipped
        }
    }
    RefreshValueText();
}

// 0x00520d98 CKInterfaceButtonDouble_SetVisualState: the parts' target sizes (ramps, with speeds scaled so
// that they all arrive with part 0's width), blends, textures and colours of the state; the arrows; the
// state's sound and effect; then the value change (state 4).
void CKInterfaceButtonDouble::SetVisualState(uint8_t state) {
    const uint8_t previous = m_ui8State;
    if (state == previous) return;
    m_ui8State = state;
    m_baFlags = static_cast<uint8_t>(m_baFlags | kFlagFading);
    const uint8_t s = m_ui8State;
    const uint32_t a = s <= 3 ? s : 2;
    const RecordA& ra = m_aRecordsA[a];
    const float speed = m_fAnimSpeed;

    // The two parts (+0x58, +0x5c): part 0's width is the reference.
    Ramp* ramps = m_aRamps;
    const float delta = ra.m_vUnk1c[0] - ramps[kRampPart0X].m_fTarget;
    ramps[kRampPart0X].m_fSpeed = m_fAnimSpeed;
    ramps[kRampPart0Y].m_fSpeed = RampSpeed(speed, ra.m_vUnk1c[1], ramps[kRampPart0Y], delta);
    ramps[kRampPart1X].m_fSpeed = RampSpeed(speed, ra.m_vUnk1c[2], ramps[kRampPart1X], delta);
    ramps[kRampPart1Y].m_fSpeed = RampSpeed(m_fAnimSpeed, ra.m_vUnk1c[3], ramps[kRampPart1Y], delta);
    ramps[kRampPart1X].m_fTarget = ra.m_vUnk1c[2];
    ramps[kRampPart1Y].m_fTarget = ra.m_vUnk1c[3];
    ramps[kRampPart0X].m_fTarget = ra.m_vUnk1c[0];
    ramps[kRampPart0Y].m_fTarget = ra.m_vUnk1c[1];

    // The right arrow: RecordB[4] while increasing (state 4), else the state's (2 for 4 and 5).
    const RecordB& rr = m_aRecordsB[(s == 4 && m_bDecrease == 0) ? 4 : a];
    ramps[kRampRightX].m_fSpeed = RampSpeed(m_fAnimSpeed, rr.m_vUnk04[2], ramps[kRampRightX], delta);
    ramps[kRampRightY].m_fSpeed = RampSpeed(m_fAnimSpeed, rr.m_vUnk04[3], ramps[kRampRightY], delta);
    ramps[kRampRightX].m_fTarget = rr.m_vUnk04[2];
    ramps[kRampRightY].m_fTarget = rr.m_vUnk04[3];
    uint8_t color[4];
    if (m_apUnk50[1] != nullptr) {
        static_cast<IKBillboard2d*>(AsBillboard(m_apUnk50[1]))->m_bUseAlpha = rr.m_aui8ArrowBlend[1];
        BillboardBrush_SetTexture(m_apUnk50[1], rr.m_apTextures[1]);                      // vt+0x3c
        CopyColor(color, &rr.m_aArrowColors[4]);
        static_cast<IKBillboard2d*>(AsBillboard(m_apUnk50[1]))->SetColor(color);          // vt+0x28
    }
    // The left arrow: RecordB[4] while decreasing.
    const RecordB& rl = m_aRecordsB[(s == 4 && m_bDecrease != 0) ? 4 : a];
    ramps[kRampLeftX].m_fSpeed = RampSpeed(m_fAnimSpeed, rl.m_vUnk04[0], ramps[kRampLeftX], delta);
    ramps[kRampLeftY].m_fSpeed = RampSpeed(m_fAnimSpeed, rl.m_vUnk04[1], ramps[kRampLeftY], delta);
    ramps[kRampLeftX].m_fTarget = rl.m_vUnk04[0];
    ramps[kRampLeftY].m_fTarget = rl.m_vUnk04[1];
    if (m_apUnk50[0] != nullptr) {
        static_cast<IKBillboard2d*>(AsBillboard(m_apUnk50[0]))->m_bUseAlpha = rl.m_aui8ArrowBlend[0];
        BillboardBrush_SetTexture(m_apUnk50[0], rl.m_apTextures[0]);
        CopyColor(color, &rl.m_aArrowColors[0]);
        static_cast<IKBillboard2d*>(AsBillboard(m_apUnk50[0]))->SetColor(color);
    }
    if ((m_baOptions & kOptionHideArrows) != 0) UpdateArrows(this);

    // The value's image size.
    ramps[kRampValueImageX].m_fSpeed = RampSpeed(m_fAnimSpeed, ra.m_vValueImageSize.m_fX, ramps[kRampValueImageX], delta);
    ramps[kRampValueImageY].m_fSpeed = RampSpeed(m_fAnimSpeed, ra.m_vValueImageSize.m_fY, ramps[kRampValueImageY], delta);
    ramps[kRampValueImageX].m_fTarget = ra.m_vValueImageSize.m_fX;
    ramps[kRampValueImageY].m_fTarget = ra.m_vValueImageSize.m_fY;

    if (m_pLabel != nullptr) {
        AsText(m_pLabel)->SetTextById(AccessorText(m_pLabelText));  // vt+0x88
        CopyColor(color, &ra.m_labelColorRaw);
        static_cast<IKText2d*>(AsText(m_pLabel))->SetColor(color);  // text part vt+0x44
    }
    if (m_pValueText != nullptr) {
        CopyColor(color, &ra.m_valueTextColorRaw);
        static_cast<IKText2d*>(AsText(m_pValueText))->SetColor(color);
    }
    if (m_pValueImage != nullptr) {
        static_cast<IKBillboard2d*>(AsBillboard(m_pValueImage))->m_bUseAlpha = ra.m_ui8ValueImageBlend;
        CopyColor(color, &ra.m_valueImageColorRaw);
        static_cast<IKBillboard2d*>(AsBillboard(m_pValueImage))->SetColor(color);
    }
    if (m_apUnk58[1] != nullptr) {
        static_cast<IKBillboard2d*>(AsBillboard(m_apUnk58[1]))->m_bUseAlpha = ra.m_aui8PartBlend[1];
        BillboardBrush_SetTexture(m_apUnk58[1], ra.m_apTextures[1]);
        CopyColor(color, &ra.m_aPartColors[4]);
        static_cast<IKBillboard2d*>(AsBillboard(m_apUnk58[1]))->SetColor(color);
    }
    if (m_apUnk58[0] != nullptr) {
        static_cast<IKBillboard2d*>(AsBillboard(m_apUnk58[0]))->m_bUseAlpha = ra.m_aui8PartBlend[0];
        BillboardBrush_SetTexture(m_apUnk58[0], ra.m_apTextures[0]);
        CopyColor(color, &ra.m_aPartColors[0]);
        static_cast<IKBillboard2d*>(AsBillboard(m_apUnk58[0]))->SetColor(color);
    }

    // The state's sound once the item has been updated (0 focused, 1 focused while disabled, 2 changing,
    // 3 validated): pan reset, played at once.
    if ((m_baFlags & kFlagUpdated) != 0) {
        uint32_t sound = 0xff;
        switch (state) {
        case 2: sound = 0; break;
        case 3: sound = 1; break;
        case 4: sound = 2; break;
        case 5: sound = 3; break;
        default: break;
        }
        if (sound != 0xff && CKSoundDictionaryID_GetSound(m_pSounds, sound & 3) != nullptr) {
            CKSound_ResetPan(CKSoundDictionaryID_GetSound(m_pSounds, sound), 1);
            CKSound_Play(CKSoundDictionaryID_GetSound(m_pSounds, sound), 0.0f);  // TOC1 +0x7740
        }
    }
    StateEffect_Start(m_aRecordsB[state].m_unk3c);

    // The value change: on entering state 4, or with kFlagHold on leaving state 4/5 (ChangeValue with a
    // state other than 4 only refreshes the text); outside 4/5, mode 0 refreshes it again.
    if ((m_baFlags & kFlagHold) != 0) {
        if (static_cast<uint8_t>(previous - 4) <= 1) ChangeValue(m_ui8State);
    } else if (static_cast<uint8_t>(m_ui8State - 4) <= 1) {
        ChangeValue(m_ui8State);
    }
    if (static_cast<uint8_t>(m_ui8State - 4) <= 1) return;
    if ((m_ui8Mode & 0x1f) == 0) ChangeValue(state);
}

// 0x005222d8 CKInterfaceButtonDouble_SetDisabled: the bit, then the visual state with it.
void CKInterfaceButtonDouble::SetDisabled(uint8_t disabled) {
    if (disabled == ((m_baFlags >> 1) & 1)) return;
    m_baFlags = static_cast<uint8_t>((m_baFlags & ~kFlagDisabled) | static_cast<uint8_t>(disabled << 1));
    const bool isDisabled = ((m_baFlags >> 1) & 1) != 0;
    switch (m_ui8State) {
    case 0:
    case 1: SetVisualState(isDisabled ? 1 : 0); break;
    case 2:
    case 3: SetVisualState(isDisabled ? 3 : 2); break;
    case 4: SetVisualState(isDisabled ? 3 : 4); break;
    case 5: SetVisualState(isDisabled ? 3 : 5); break;
    default: break;
    }
}

// 0x005223e0 CKInterfaceButtonDouble_SetInteractionState: the menu's item state -> the visual state
// (disabled: 1 when normal, else 3); 3 and 4 both enter state 4, with the direction.
void CKInterfaceButtonDouble::SetInteractionState(int32_t state) {
    const bool isDisabled = ((m_baFlags >> 1) & 1) != 0;
    switch (static_cast<uint32_t>(state)) {
    case 0: SetVisualState(isDisabled ? 1 : 0); break;
    case 1: SetVisualState(isDisabled ? 3 : 5); break;
    case 2: SetVisualState(isDisabled ? 3 : 2); break;
    case 3:
        if (isDisabled) {
            SetVisualState(3);
        } else {
            m_bDecrease = 1;
            SetVisualState(4);
        }
        break;
    case 4:
        if (isDisabled) {
            SetVisualState(3);
        } else {
            m_bDecrease = 0;
            SetVisualState(4);
        }
        break;
    default: break;
    }
}

namespace {

// The hot spot's 2D object entry of `node`, searched from the last (SetPosition inlines one search per
// coordinate); nothing when it is not attached.
SAttached2dObject* FindAttached(IKSerializable* hotSpot, IKSerializable* node) {
    TVector<SAttached2dObject, 2>& objects = static_cast<CFlashHotSpot*>(hotSpot)->m_vp2dObject;
    for (uint32_t i = objects.m_ui32NbUsedElt; i-- != 0;) {
        if (static_cast<IKSerializable*>(objects.m_pBlock[i].m_pNode) == node) return &objects.m_pBlock[i];
    }
    return nullptr;
}
void SetAttachedOffset(IKSerializable* hotSpot, IKSerializable* node, float x, float y) {
    if (SAttached2dObject* entry = FindAttached(hotSpot, node)) entry->m_vPosOffset.m_fX = x;
    if (SAttached2dObject* entry = FindAttached(hotSpot, node)) entry->m_vPosOffset.m_fY = y;
}

}  // namespace

// 0x005224d0 CKInterfaceButtonDouble_SetPosition: the position, then each element's offset in the base's
// hot spot (+0x2c, a CFlashHotSpot): label, value text and image at their offsets, the arrows either side
// of the value image, the two parts at the position.
void CKInterfaceButtonDouble::SetPosition(const CVector2& position) {
    m_vPosition = position;
    if (m_pLabel != nullptr) SetAttachedOffset(m_unk2c, m_pLabel, position.m_fX + m_fLabelOffsetX, position.m_fY);
    if (m_pValueText != nullptr) {
        SetAttachedOffset(m_unk2c, m_pValueText, position.m_fX + m_vValueTextOffset.m_fX,
                          position.m_fY + m_vValueTextOffset.m_fY);
    }
    if (m_pValueImage != nullptr) SetAttachedOffset(m_unk2c, m_pValueImage, m_fValueOffsetX + position.m_fX, position.m_fY);
    for (int32_t i = 1; i >= 0; --i) {
        if (m_apUnk50[i] == nullptr) continue;
        const float offset = i == 0 ? m_fValueOffsetX - m_fArrowSpacing : m_fValueOffsetX + m_fArrowSpacing;
        SetAttachedOffset(m_unk2c, m_apUnk50[i], offset + position.m_fX, position.m_fY);
    }
    for (int32_t i = 1; i >= 0; --i) {
        if (m_apUnk58[i] != nullptr) SetAttachedOffset(m_unk2c, m_apUnk58[i], position.m_fX, position.m_fY);
    }
}

// 0x005228f0 CKInterfaceButtonDouble_UpdateVisibility: every element's colour of the current state (state 0
// with fadeIn) with its alpha scaled by the fade (+0x28); while changing, the arrow of the direction uses
// the state's RecordB (4 or 5), the other one RecordB[2].
void CKInterfaceButtonDouble::UpdateVisibility(uint8_t fadeIn) {
    uint32_t s = m_ui8State;
    uint32_t a = s <= 3 ? s : 2;
    if (fadeIn != 0) {
        s = 0;
        a = 0;
    }
    const RecordA& ra = m_aRecordsA[a];
    uint8_t color[4];
    if (m_pLabel != nullptr) {
        FadedColor(color, &ra.m_labelColorRaw, m_fFade);
        static_cast<IKText2d*>(AsText(m_pLabel))->SetColor(color);
    }
    if (m_pValueText != nullptr) {
        FadedColor(color, &ra.m_valueTextColorRaw, m_fFade);
        static_cast<IKText2d*>(AsText(m_pValueText))->SetColor(color);
    }
    if (m_pValueImage != nullptr) {
        FadedColor(color, &ra.m_valueImageColorRaw, m_fFade);
        static_cast<IKBillboard2d*>(AsBillboard(m_pValueImage))->SetColor(color);
    }
    if (static_cast<uint8_t>(s - 4) <= 1) {
        for (int32_t i = 1; i >= 0; --i) {
            if (m_apUnk50[i] == nullptr) continue;
            const uint32_t b = m_bDecrease == (i == 0 ? 1u : 0u) ? s : a;
            FadedColor(color, &m_aRecordsB[b].m_aArrowColors[4 * i], m_fFade);
            static_cast<IKBillboard2d*>(AsBillboard(m_apUnk50[i]))->SetColor(color);
        }
    } else {
        if (m_apUnk50[1] != nullptr) {
            FadedColor(color, &m_aRecordsB[a].m_aArrowColors[4], m_fFade);
            static_cast<IKBillboard2d*>(AsBillboard(m_apUnk50[1]))->SetColor(color);
        }
        if (m_apUnk50[0] != nullptr) {
            FadedColor(color, &m_aRecordsB[a].m_aArrowColors[0], m_fFade);
            static_cast<IKBillboard2d*>(AsBillboard(m_apUnk50[0]))->SetColor(color);
        }
    }
    if (m_apUnk58[1] != nullptr) {
        FadedColor(color, &ra.m_aPartColors[4], m_fFade);
        static_cast<IKBillboard2d*>(AsBillboard(m_apUnk58[1]))->SetColor(color);
    }
    if (m_apUnk58[0] != nullptr) {
        FadedColor(color, &ra.m_aPartColors[0], m_fFade);
        static_cast<IKBillboard2d*>(AsBillboard(m_apUnk58[0]))->SetColor(color);
    }
    if (m_fFadeTarget != m_fFade) m_baFlags = static_cast<uint8_t>(m_baFlags | kFlagFading);
}

// 0x00522e68 CKInterfaceButtonDouble_StartFadeOut: the fade-out timer, the size targets to 0 (ramps 8 and
// 12 too, not 9 and 13), the fade from 1 down to 0.
void CKInterfaceButtonDouble::StartFadeOut() {
    m_baFlags = static_cast<uint8_t>(m_baFlags | kFlagFading);
    m_aRamps[kRampLeftY].m_fTarget = 0.0f;
    m_fFadeOutTime = m_fFadeOutDuration;
    m_aRamps[12].m_fTarget = 0.0f;
    m_aRamps[8].m_fTarget = 0.0f;
    m_aRamps[kRampValueImageX].m_fTarget = 0.0f;
    m_aRamps[kRampValueImageY].m_fTarget = 0.0f;
    m_aRamps[kRampPart1X].m_fTarget = 0.0f;
    m_aRamps[kRampPart1Y].m_fTarget = 0.0f;
    m_aRamps[kRampPart0X].m_fTarget = 0.0f;
    m_aRamps[kRampPart0Y].m_fTarget = 0.0f;
    m_aRamps[kRampRightX].m_fTarget = 0.0f;
    m_aRamps[kRampRightY].m_fTarget = 0.0f;
    m_aRamps[kRampLeftX].m_fTarget = 0.0f;
    StartFade(0x1p+0f, m_fAnimSpeed, 0);  // TOC1 +0x7790
}

// 0x00523028 CKInterfaceButtonDouble_Close: the base's, every element disabled, every entry's videos
// stopped (vt+0x78).
void CKInterfaceButtonDouble::Close() {
    CKInterfaceButtonBase::Close();
    IKSerializable* const nodes[] = {m_pLabel, m_pValueText, m_pValueImage, m_apUnk50[1], m_apUnk50[0], m_apUnk58[1], m_apUnk58[0]};
    for (IKSerializable* node : nodes) {
        if (node != nullptr) static_cast<IKNode2d*>(node)->Disable();
    }
    for (uint32_t e = m_ui8NbEntries; e-- != 0;) {
        for (uint32_t i = m_aEntries[e].m_vVideos.m_ui32NbUsedElt; i-- != 0;) {
            IKSerializable* video = m_aEntries[e].m_vVideos.m_pBlock[i].m_first;
            if (video != nullptr) static_cast<IKVideo*>(video)->Stop();
        }
    }
}

// 0x00523300 CKInterfaceButtonDouble_Open
void CKInterfaceButtonDouble::Open(uint8_t focused) {
    m_ui8State = 0xff;
    m_ui8Value = 0;
    static_cast<CKMenuBase114c*>(m_pMenu)->VfEC(this);  // vt+0xec(menu, this)
    CKInterfaceButtonBase::Open(focused);
    Show();  // vt+0x6c
    LoadOptionValue();
    m_fFadeOutTime = m_fFadeOutDuration;
    for (Ramp& ramp : m_aRamps) {
        ramp.m_fCurrent = 0.0f;
        ramp.m_fSpeed = m_fAnimSpeed;
        ramp.m_fTarget = 0.0f;
    }
    for (uint32_t i = 6; i-- != 0;) StateEffect_Reset(m_aRecordsB[i].m_unk3c);
    SetVisualState(focused != 0 ? 2 : 0);
    StartFade(0x1p+0f, m_fAnimSpeed, 1);  // TOC1 +0x7790
    UpdateVisibility(0);                  // vt+0x68
}

// 0x00523690 CKInterfaceButtonDouble_Destroy: the base's (0x67ff0, empty), every texture reference
// released (RwTextureDestroy), the entries' tables freed, then the entry array (its element destructors
// free the already emptied tables again). m_aEntries is not cleared.
void CKInterfaceButtonDouble::Destroy() {
    CKInterfaceButtonBase::Destroy();
    for (uint32_t i = 4; i-- != 0;) {
        if (m_aRecordsA[i].m_apTextures[1] != nullptr) TextureRef_Release(m_aRecordsA[i].m_apTextures[1]);
        if (m_aRecordsA[i].m_apTextures[0] != nullptr) TextureRef_Release(m_aRecordsA[i].m_apTextures[0]);
    }
    for (uint32_t i = 6; i-- != 0;) {
        if (m_aRecordsB[i].m_apTextures[1] != nullptr) TextureRef_Release(m_aRecordsB[i].m_apTextures[1]);
        if (m_aRecordsB[i].m_apTextures[0] != nullptr) TextureRef_Release(m_aRecordsB[i].m_apTextures[0]);
    }
    for (uint32_t e = m_ui8NbEntries; e-- != 0;) {
        Entry& entry = m_aEntries[e];
        if (entry.m_pTexture != nullptr) TextureRef_Release(entry.m_pTexture);
        if (entry.m_vVideos.m_pBlock != nullptr) Mem_FreeAligned16(entry.m_vVideos.m_pBlock);
        entry.m_vVideos.m_ui32NbUsedElt = 0;
        entry.m_vVideos.m_pBlock = nullptr;
        if (entry.m_vTexts.m_pBlock != nullptr) Mem_FreeAligned16(entry.m_vTexts.m_pBlock);
        entry.m_vTexts.m_ui32NbUsedElt = 0;
        entry.m_vTexts.m_pBlock = nullptr;
        for (uint32_t i = entry.m_vImages.m_ui32NbUsedElt; i-- != 0;) {
            void* texture = entry.m_vImages.m_pBlock[i].m_pTexture;
            if (texture != nullptr) TextureRef_Release(texture);
        }
        if (entry.m_vImages.m_pBlock != nullptr) Mem_FreeAligned16(entry.m_vImages.m_pBlock);
        entry.m_vImages.m_ui32NbUsedElt = 0;
        entry.m_vImages.m_pBlock = nullptr;
    }
    if (m_aEntries != nullptr) delete[] m_aEntries;  // OperatorDeleteArray; the tables are empty by now
}

// 0x005239a8 CKInterfaceButtonDouble_AnimatePart
void CKInterfaceButtonDouble::AnimatePart(IKSerializable* node, Ramp* rampX, Ramp* rampY, IKTime* frameClock,
                                          uint8_t isBillboard) {
    float size[2] = {0.0f, 0.0f};
    if (m_fFadeOutTime <= 0.0f) {
        size[0] = FloatApproach_Step(DeltaTime(frameClock), &rampX->m_fTarget);
        size[1] = FloatApproach_Step(DeltaTime(frameClock), &rampY->m_fTarget);
    } else {
        size[0] = rampX->m_fCurrent;
        size[1] = rampY->m_fCurrent;
    }
    if (node != nullptr) {
        if (isBillboard == 0) {
            IKText2d* text = AsText(node);
            text->m_vBoxSize.m_fY = size[1];
            text->m_bAutoSize = 0;
            text->m_vBoxSize.m_fX = size[0];
            text->ComputeLayout();  // 0x6a468, then 0x6a0b0 KStub_Nop_6a0b0
        } else {
            BillboardBrush_SetSize(node, size);  // billboard part vt+0x30
        }
    }
    if (rampX->m_fCurrent != rampX->m_fTarget || rampY->m_fCurrent != rampY->m_fTarget || m_fFadeOutTime > 0.0f) {
        m_baFlags = static_cast<uint8_t>(m_baFlags | kFlagFading);
    }
}

// 0x00523b48 CKInterfaceButtonDouble_Update: the updated bit; while fading or fading out, the sizes and the
// fade step, the colours follow, and the fade-out timer runs down.
void CKInterfaceButtonDouble::Update(IKTime* frameClock) {
    const uint8_t flags = static_cast<uint8_t>(m_baFlags | kFlagUpdated);
    m_baFlags = flags;
    if ((flags & kFlagFading) == 0 && m_fFadeOutTime <= 0.0f) return;
    m_baFlags = static_cast<uint8_t>(flags & ~kFlagFading);
    AnimatePart(m_apUnk58[1], &m_aRamps[kRampPart1X], &m_aRamps[kRampPart1Y], frameClock, 1);
    AnimatePart(m_apUnk58[0], &m_aRamps[kRampPart0X], &m_aRamps[kRampPart0Y], frameClock, 1);
    AnimatePart(m_apUnk50[1], &m_aRamps[kRampRightX], &m_aRamps[kRampRightY], frameClock, 1);
    AnimatePart(m_apUnk50[0], &m_aRamps[kRampLeftX], &m_aRamps[kRampLeftY], frameClock, 1);
    AnimatePart(m_pValueImage, &m_aRamps[kRampValueImageX], &m_aRamps[kRampValueImageY], frameClock, 1);
    FloatApproach_Step(DeltaTime(frameClock), &m_fFadeTarget);
    UpdateVisibility(0);  // vt+0x68
    if (m_fFadeOutTime > 0.0f) m_fFadeOutTime = m_fFadeOutTime - DeltaTime(frameClock);
}

// 0x00523f08 CKInterfaceButtonDouble_Create (the constructor inlined; the same stores as 0x522ef8): the
// base, then +0x354..+0x3fb = 0. The stores are independent; their interleaving is not kept.
CKInterfaceButtonDouble::CKInterfaceButtonDouble() {
    for (Ramp& ramp : m_aRamps) ramp = {0.0f, 0.0f, 0.0f};
}

namespace {

void LoadRecordA(CKInterfaceButtonDouble::RecordA* r, IKFile* file) {
    ReadRaw(file, &r->m_labelColorRaw, 4);
    ReadRaw(file, &r->m_valueTextColorRaw, 4);
    ReadRaw(file, &r->m_valueImageColorRaw, 4);
    ReadU8(file, &r->m_ui8ValueImageBlend);
    ReadF32LE(file, &r->m_vValueImageSize.m_fX);  // one read per vector, every word swapped
    ReadF32LE(file, &r->m_vValueImageSize.m_fY);
    for (float& f : r->m_vUnk1c) ReadF32LE(file, &f);
    ReadRaw(file, r->m_aui8PartBlend, 2);
    ReadRaw(file, r->m_aPartColors, 8);
    for (float& f : r->m_vUnk3c) ReadF32LE(file, &f);
    for (float& f : r->m_vUnk44) ReadF32LE(file, &f);
    for (float& f : r->m_vUnk4c) ReadF32LE(file, &f);
    IKFile_ReadTextureRef(file, &r->m_apTextures[1], 1);
    IKFile_ReadTextureRef(file, &r->m_apTextures[0], 1);
}

void LoadRecordB(CKInterfaceButtonDouble::RecordB* r, IKFile* file) {
    for (float& f : r->m_vUnk04) ReadF32LE(file, &f);
    ReadRaw(file, r->m_aui8ArrowBlend, 2);
    ReadRaw(file, r->m_aArrowColors, 8);
    for (float& f : r->m_vUnk24) ReadF32LE(file, &f);
    for (float& f : r->m_vUnk2c) ReadF32LE(file, &f);
    for (float& f : r->m_vUnk34) ReadF32LE(file, &f);
    IKFile_ReadRef(file, &r->m_unk3c);
    IKFile_ReadTextureRef(file, &r->m_apTextures[1], 1);
    IKFile_ReadTextureRef(file, &r->m_apTextures[0], 1);
}

}  // namespace

// 0x00524060 CKInterfaceButtonDouble_Load: no type test of its own (the base and the tables test it).
int32_t CKInterfaceButtonDouble::Load(IKFile* file, int32_t type) {
    CKInterfaceButtonBase::Load(file, type);
    for (uint32_t i = 4; i-- != 0;) LoadRecordA(&m_aRecordsA[i], file);
    for (uint32_t i = 6; i-- != 0;) LoadRecordB(&m_aRecordsB[i], file);
    ReadF32LE(file, &m_fAnimSpeed);
    ReadF32LE(file, &m_vUnk38[0]);  // one 8-byte read per vector, both words swapped
    ReadF32LE(file, &m_vUnk38[1]);
    ReadF32LE(file, &m_vUnk44[0]);
    ReadF32LE(file, &m_vUnk44[1]);
    ReadF32LE(file, &m_fLabelOffsetX);
    ReadF32LE(file, &m_vValueTextOffset.m_fX);
    ReadF32LE(file, &m_vValueTextOffset.m_fY);
    ReadF32LE(file, &m_fValueOffsetX);
    ReadF32LE(file, &m_fArrowSpacing);  // one word, swapped
    ReadU8(file, &m_baOptions);
    ReadU8(file, &m_ui8Mode);
    IKFile_ReadRef(file, &m_pLabelText);
    ReadF32LE(file, &m_fFadeOutDuration);
    IKFile_ReadRef(file, &m_pLabel);
    IKFile_ReadRef(file, &m_pValueText);
    IKFile_ReadRef(file, &m_pValueImage);
    IKFile_ReadObjectRefArray(file, m_apUnk50, 2);
    IKFile_ReadObjectRefArray(file, m_apUnk58, 2);
    IKFile_ReadRef(file, &m_pSounds);
    ReadU8(file, &m_ui8NbEntries);
    m_aEntries = new Entry[m_ui8NbEntries];  // OperatorNewArray(count * 0x2c + 4): the count, then the entries
    for (uint32_t i = m_ui8NbEntries; i-- != 0;) {
        Entry& e = m_aEntries[i];
        IKFile_ReadRef(file, &e.m_pText);
        IKFile_ReadTextureRef(file, &e.m_pTexture, 1);
        CKInterfaceButton_LoadRefPairs(&e.m_vVideos, file, type);
        // Both references in every type: the same reader as a K_LEVEL_PLATEFORMS one.
        CKInterfaceButton_LoadRefPairs(&e.m_vTexts, file, K_LEVEL_PLATEFORMS);
        CKInterfaceButton_LoadTextEntries(&e.m_vImages, file);
    }
    return 1;
}

namespace {
void RegisterIfDouble(IKSerializable* object, int32_t type) {
    if (object != nullptr) object->RecursiveRegistration(type);  // vt+0x24
}
}  // namespace

// 0x00521ae8 CKInterfaceButtonDouble_RecursiveRegistration (each table from its last element down)
void CKInterfaceButtonDouble::RecursiveRegistration(int32_t type) {
    CKInterfaceButtonBase::RecursiveRegistration(type);  // 0x00067fe8
    for (int k = 5; k >= 0; --k) RegisterIfDouble(m_aRecordsB[k].m_unk3c, type);
    m_pLabelText->RecursiveRegistration(type);
    RegisterIfDouble(m_pLabel, type);
    RegisterIfDouble(m_pValueText, type);
    RegisterIfDouble(m_pValueImage, type);
    RegisterIfDouble(m_apUnk50[1], type);
    RegisterIfDouble(m_apUnk50[0], type);
    RegisterIfDouble(m_apUnk58[1], type);
    RegisterIfDouble(m_apUnk58[0], type);
    m_pSounds->RecursiveRegistration(type);
    for (uint32_t k = m_ui8NbEntries; k != 0; --k) {
        Entry& e = m_aEntries[k - 1];
        e.m_pText->RecursiveRegistration(type);
        for (uint32_t i = e.m_vVideos.m_ui32NbUsedElt; i != 0; --i) {
            RegisterIfDouble(e.m_vVideos.m_pBlock[i - 1].m_first, type);
            RegisterIfDouble(e.m_vVideos.m_pBlock[i - 1].m_second, type);
        }
        for (uint32_t i = e.m_vTexts.m_ui32NbUsedElt; i != 0; --i) {
            e.m_vTexts.m_pBlock[i - 1].m_second->RecursiveRegistration(type);
            RegisterIfDouble(e.m_vTexts.m_pBlock[i - 1].m_first, type);
        }
        for (uint32_t i = e.m_vImages.m_ui32NbUsedElt; i != 0; --i) RegisterIfDouble(e.m_vImages.m_pBlock[i - 1].m_pText, type);
    }
}
