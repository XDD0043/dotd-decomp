// CKInterfaceCheckBox.h - a menu option box with ten visual states (key 0xa14c, vtable 0xb2bb70, size
// 0x79c). Original unit: CKInterfaceCheckBox.cpp. DotD only: no XXL2 class of this name, so the member
// names are descriptive. Base: CKInterfaceButtonBase (0x63cc).
//
// The options menus ("Menu Option PS3", menu ids 0x17 and 0x19 live) hold one per on/off option: the
// option (m_ui8Option & 0xf) is a game-manager option byte (Open reads it, a validation toggles it), the
// box shows it with ten visual states:
//   0..7 = (unchecked ? 4 : 0) + (focused ? 2 : 0) + (disabled ? 1 : 0); 8 just checked, 9 just unchecked.
// Each state gives the two texts (+0x34 the label, +0x38 the value "On"/"Off") their strings and colours,
// and the four billboards (+0x3c..+0x48) a size (ramped), a colour, a texture, a blend mode and a
// sprite-sheet animation; the focused states (2, 3, 6..9) play a sound (+0x78c).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKInterfaceButton.h"
#include "k2000/math/CVector2.h"
#include "k2000/misc/CKInterfaceButtonBase.h"
#include "k2000/util/TVector.h"

class CKInterfaceCheckBox : public CKInterfaceButtonBase {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x285)
    DOTD_DECLARE_FACTORIES(CKInterfaceCheckBox)

    // m_baCheckFlags (+0x31; read from the file, Open clears bits 0, 2, 3 and 4).
    enum : uint8_t {
        kCheckFocused = 0x01,       // SetInteractionState: 2 sets it, every other state clears it
        kCheckChecked = 0x02,       // the option's value (LoadOptionValue) or the toggled one (state 1)
        kCheckKeepLabelText = 0x04, // SetVisualState leaves the +0x34 text's string
        kCheckKeepValueText = 0x08, // SetVisualState leaves the +0x38 text's string
        kCheckNoActions = 0x10,     // ApplyStateChange does nothing (no option toggle, no state actions)
    };

    // One visual state (0xa8 bytes), read by 0x009c87e0 CKInterfaceCheckBox_LoadStateVisual_maybe. Its
    // tables have the entries of CKInterfaceButton's states (the same readers).
    struct StateVisual {
        uint32_t m_labelColorRaw;      // +0x00 the +0x34 text's colour (4 file bytes, seen big-endian by the PS3)
        uint32_t m_valueColorRaw;      // +0x04 the +0x38 text's colour
        // +0x08 CKLocTextAccessor: its list's [0] is the +0x34 text's string, [1] the +0x38 text's; its
        // single text (+0x10) both when the list is empty.
        IKSerializable* m_pTexts;
        uint8_t m_aBlendModes[4];      // +0x0c per billboard: its IKBillboard2d::m_bUseAlpha (read raw, 4 bytes)
        // +0x10 per billboard: the size SetVisualState ramps it to (width, height). Live: (0.1, 0.1),
        // (0.48, 0.075) ((0.5, 0.08) focused), (0.1, 0.1), (0.05, 0.05). One 0x20-byte read, words swapped.
        CVector2 m_avSizes[4];
        void* m_apTextures[4];         // +0x30 per billboard: RwTexture (read from the last down; resolved)
        uint32_t m_aColorsRaw[4];      // +0x40 per billboard: the colour (16 file bytes, read raw)
        float m_afAnimDurations[4];    // +0x50 per billboard: CBillboard2d_SetAnimTime_maybe (+0x74)
        uint32_t m_aSheetCellsU[4];    // +0x60 per billboard: CBillboard2d_SetSpriteSheetRows_maybe (+0x7c)
        uint32_t m_aSheetCellsV[4];    // +0x70 per billboard: CBillboard2d_SetSpriteSheetColumns_maybe (+0x80)
        IKSerializable* m_pParticles;  // +0x80 CParticlesNodeFx: emits once when the state is entered; read last
        // +0x84 (IKVideo, CKVideoSegment): ApplyStateChange plays the segment (mode 3), else starts the
        // video; Close stops the videos.
        TVector<CKInterfaceButton::RefPair, 1> m_aVideos;
        // +0x90 (CText2d, CKLocTextAccessor, colour): ApplyStateChange sets the text's string and colour.
        TVector<CKInterfaceButton::RefPairValue, 1> m_aTexts;
        // +0x9c (CBillboard2d, RwTexture, duration as a float word, cells u, cells v): ApplyStateChange
        // sets the billboard's texture and sprite-sheet animation.
        TVector<CKInterfaceButton::TextEntry, 1> m_aBillboards;
    };

    CKInterfaceCheckBox();  // inlined in 0x00532d88 CKInterfaceCheckBox_Create (copy 0x531238)
    // 0x005326d8 CKInterfaceCheckBox_Destructor (0x00530b48 BaseDestructor: the same code; 0x005325c8
    // DeletingDestructor: then the delete): per state from the last down its billboard, text and video tables freed.
    ~CKInterfaceCheckBox() override;
    // vt+0x24 0x00530280 CKInterfaceCheckBox_RecursiveRegistration: the base's, then per state from the last down its
    // text accessor (unchecked), its particles, its texts (the accessor unchecked) and its billboards (its videos are
    // not visited); then the two texts, billboards 3..0 and the sound dictionary (unchecked). Null references are
    // skipped unless said otherwise.
    void RecursiveRegistration(int32_t type) override;
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c8768
        return key == 0xa14c || key == 0x63cc || key == 0xc;
    }
    void Destroy() override;                            // vt+0x10 0x00531f28 CKInterfaceCheckBox_Destroy
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00533280 CKInterfaceCheckBox_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x00531f20 CKInterfaceCheckBox_PostLoad

    // The button slots (CKInterfaceButtonBase.h).
    void Open(uint8_t focused) override;            // vt+0x50 0x005320f0 CKInterfaceCheckBox_Open
    void Close() override;                          // vt+0x54 0x00531ba0 CKInterfaceCheckBox_Close
    void Update(IKTime* frameClock) override;       // vt+0x58 0x005310e0 CKInterfaceCheckBox_Update
    void SetInteractionState(int32_t state) override;  // vt+0x5c 0x00531dc8 CKInterfaceCheckBox_SetInteractionState
    void SetPosition(const CVector2& position) override;  // vt+0x60 0x00530dc8 CKInterfaceCheckBox_SetPosition
    void UpdateVisibility(uint8_t fadeIn) override;  // vt+0x68 0x005316b8 CKInterfaceCheckBox_UpdateVisibility
    void Show() override;                           // vt+0x6c 0x0052e4a8 CKInterfaceCheckBox_Show
    void Hide() override;                           // vt+0x70 0x0052e620 CKInterfaceCheckBox_Hide
    void StartFadeOut() override;                   // vt+0x74 0x00531b18 CKInterfaceCheckBox_StartFadeOut
    // vt+0x78 0x9c87a8 (lfs TOC +0x78c8 = 0.0)
    uint8_t IsFadeOutFinished() override { return m_fFadeOutTime <= 0.0f ? 1 : 0; }
    void Vf80(IKTime* frameClock) override;         // vt+0x80 0x0052e798 CKInterfaceCheckBox_vf80
    void SetDisabled(uint8_t disabled) override;    // vt+0x84 0x00530ca0 CKInterfaceCheckBox_SetDisabled
    float Vf88() override { return m_fFadeOutDuration; }     // vt+0x88 0x9c87d0
    void Vf8C(float value) override { m_fFadeOutDuration = value; }  // vt+0x8c 0x9c87d8

    // 0x0052e9a8 CKInterfaceCheckBox_ApplyStateChange_maybe: the option toggled (m_ui8Option), then state
    // `state`'s videos, texts and billboards (nothing at all with kCheckNoActions).
    void ApplyStateChange(uint8_t state);
    // 0x0052ee48 CKInterfaceCheckBox_SetVisualState
    void SetVisualState(uint8_t state);
    // 0x0052fcd0 CKInterfaceCheckBox_LoadOptionValue: kCheckChecked from the option's byte, the player-2
    // options disabled with one player (outside the main menu), then the matching state.
    void LoadOptionValue();
    // 0x00530080 CKInterfaceCheckBox_AnimatePart: one element's size ramps (width, height) advanced and
    // applied (a text's box, or a billboard's size).
    void AnimatePart(IKSerializable* element, float* widthRamp, float* heightRamp, IKTime* frameClock,
                     uint8_t isBillboard);

    // +0x30: bits 0-3 the option (the switches in LoadOptionValue / ApplyStateChange: 1 subtitles, 2 both
    // pads' vibration, 3/4 pad 1/2 vibration, 5/6/7 the +0x10a/+0x10b pair (both, P1, P2), 8/9/10 the
    // +0x10c/+0x10d pair, 11/12/13 the motion sensor, 14 tutorial; 0 none). Bits 6-7 are set in every live
    // one (0xc0) and not read by this class.
    uint8_t m_ui8Option;
    uint8_t m_baCheckFlags;           // +0x31 kCheck* (+0x32..+0x33: padding the original never writes)
    uint8_t m_pad32[2];
    IKSerializable* m_unk34;          // +0x34 CText2d: the label ("Subtitles", "P1", ...)
    IKSerializable* m_unk38;          // +0x38 CText2d: the value ("On" / "Off")
    IKSerializable* m_apUnk3c[4];     // +0x3c four CBillboard2d (one array read); index i uses the states' [i]
    float m_fAnimSpeed;               // +0x4c the size ramps' speed and the fade's (4.5 live)
    float m_fLabelOffsetX;            // +0x50 SetPosition: the +0x34 text's x offset (-0.075 live)
    float m_fValueOffsetX;            // +0x54 SetPosition: the +0x38 text's x offset (0.18 live)
    float m_fBillboard3OffsetX;       // +0x58 SetPosition: the +0x48 billboard's x offset (0.1 live)
    float m_vUnk5c[2];                // +0x5c one 8-byte read, both words swapped
    float m_vUnk64[2];                // +0x64
    // +0x6c per billboard: the width and height ramps ({target, speed, current}, FloatApproach_Step), then
    // four more that Open resets and StartFadeOut zeroes (targets 0 and 2) but nothing in this class
    // advances. The constructor sets all 0; not read.
    float m_aWidthRamps[4][3];        // +0x6c
    float m_aHeightRamps[4][3];       // +0x9c
    float m_aUnkRamps[4][3];          // +0xcc
    StateVisual m_aStates[10];        // +0xfc read from the last down
    IKSerializable* m_pSounds;        // +0x78c CKSoundDictionaryID: the sounds of states 2, 3, 6, 7, 8, 9
    uint8_t m_unk790;                 // +0x790 (+0x791..+0x793: not written)
    uint8_t m_pad791[3];
    float m_fFadeOutTime;             // +0x794 StartFadeOut / Open copy +0x798; vt+0x78 tests it <= 0
    float m_fFadeOutDuration;         // +0x798 (vt+0x88 / +0x8c)
};
DOTD_ASSERT_SIZE(CKInterfaceCheckBox::StateVisual, 0xa8);
DOTD_ASSERT_OFFSET(CKInterfaceCheckBox::StateVisual, m_valueColorRaw, 0x04);
DOTD_ASSERT_OFFSET(CKInterfaceCheckBox::StateVisual, m_pTexts, 0x08);
DOTD_ASSERT_OFFSET(CKInterfaceCheckBox::StateVisual, m_aBlendModes, 0x0c);
DOTD_ASSERT_OFFSET(CKInterfaceCheckBox::StateVisual, m_avSizes, 0x10);
DOTD_ASSERT_OFFSET(CKInterfaceCheckBox::StateVisual, m_apTextures, 0x30);
DOTD_ASSERT_OFFSET(CKInterfaceCheckBox::StateVisual, m_aColorsRaw, 0x40);
DOTD_ASSERT_OFFSET(CKInterfaceCheckBox::StateVisual, m_afAnimDurations, 0x50);
DOTD_ASSERT_OFFSET(CKInterfaceCheckBox::StateVisual, m_aSheetCellsU, 0x60);
DOTD_ASSERT_OFFSET(CKInterfaceCheckBox::StateVisual, m_aSheetCellsV, 0x70);
DOTD_ASSERT_OFFSET(CKInterfaceCheckBox::StateVisual, m_pParticles, 0x80);
DOTD_ASSERT_OFFSET(CKInterfaceCheckBox::StateVisual, m_aVideos, 0x84);
DOTD_ASSERT_OFFSET(CKInterfaceCheckBox::StateVisual, m_aTexts, 0x90);
DOTD_ASSERT_OFFSET(CKInterfaceCheckBox::StateVisual, m_aBillboards, 0x9c);
DOTD_ASSERT_SIZE(CKInterfaceCheckBox, 0x79c);
DOTD_ASSERT_OFFSET(CKInterfaceCheckBox, m_ui8Option, 0x30);
DOTD_ASSERT_OFFSET(CKInterfaceCheckBox, m_baCheckFlags, 0x31);
DOTD_ASSERT_OFFSET(CKInterfaceCheckBox, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKInterfaceCheckBox, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKInterfaceCheckBox, m_apUnk3c, 0x3c);
DOTD_ASSERT_OFFSET(CKInterfaceCheckBox, m_fAnimSpeed, 0x4c);
DOTD_ASSERT_OFFSET(CKInterfaceCheckBox, m_fLabelOffsetX, 0x50);
DOTD_ASSERT_OFFSET(CKInterfaceCheckBox, m_fValueOffsetX, 0x54);
DOTD_ASSERT_OFFSET(CKInterfaceCheckBox, m_fBillboard3OffsetX, 0x58);
DOTD_ASSERT_OFFSET(CKInterfaceCheckBox, m_vUnk5c, 0x5c);
DOTD_ASSERT_OFFSET(CKInterfaceCheckBox, m_vUnk64, 0x64);
DOTD_ASSERT_OFFSET(CKInterfaceCheckBox, m_aWidthRamps, 0x6c);
DOTD_ASSERT_OFFSET(CKInterfaceCheckBox, m_aHeightRamps, 0x9c);
DOTD_ASSERT_OFFSET(CKInterfaceCheckBox, m_aUnkRamps, 0xcc);
DOTD_ASSERT_OFFSET(CKInterfaceCheckBox, m_aStates, 0xfc);
DOTD_ASSERT_OFFSET(CKInterfaceCheckBox, m_pSounds, 0x78c);
DOTD_ASSERT_OFFSET(CKInterfaceCheckBox, m_unk790, 0x790);
DOTD_ASSERT_OFFSET(CKInterfaceCheckBox, m_fFadeOutTime, 0x794);
DOTD_ASSERT_OFFSET(CKInterfaceCheckBox, m_fFadeOutDuration, 0x798);
