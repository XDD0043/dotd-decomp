// CKInterfaceButtonDouble.h - a menu item holding a value the player changes with left/right (key 0x634c,
// vtable 0xb2b7f8, size 0x410): the options' choices and sliders (language, brightness, volumes, sound
// output, aspect ratio, vibration, ...). Original unit: CKInterfaceButtonDouble.cpp. DotD only: no XXL2
// class of this name, so the member names are descriptive. Base: CKInterfaceButtonBase (0x63cc). Its Load
// (0x524060) inlines its own two record readers and a table of entries with CKInterfaceButton's state tables.
//
// The item: a label (m_pLabel, its text m_pLabelText), the value's text (m_pValueText) and image
// (m_pValueImage), two arrows (m_apUnk50: [0] left / decrease, [1] right / increase) and two more parts
// (m_apUnk58). The value is m_ui8Value, an index into m_aEntries (one entry per value: its text, image,
// videos). m_ui8Mode & 0x1f says which game option the value mirrors: LoadOptionValue reads it from the game
// manager's edited options block (+0xec) when the item opens, ChangeValue steps it (state 4, direction
// m_bDecrease) and calls the game manager's option setter.
//
// The visual states (m_ui8State, SetVisualState): 0 normal, 1 disabled, 2 focused, 3 focused while disabled_maybe,
// 4 changing (left/right held), 5 validated. RecordA is per state (states 4 and 5 use RecordA[2]), RecordB
// per state for the two arrows (the arrow of the direction being changed uses RecordB[4], the other
// RecordB[2] while changing). The sizes and the positions animate through m_aRamps (FloatApproach).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKInterfaceButton.h"
#include "k2000/math/CVector2.h"
#include "k2000/misc/CKInterfaceButtonBase.h"
#include "k2000/util/TVector.h"

class IKTime;

class CKInterfaceButtonDouble : public CKInterfaceButtonBase {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x18d)  // vt+0x14 / +0x18  0x9c8430 / 0x9c8438
    DOTD_DECLARE_FACTORIES(CKInterfaceButtonDouble)

    // +0x60, four 0x54-byte records (read from the last down), one per visual state (states 4 and 5: [2]).
    // The colours are 4 file bytes (RGBA) read raw; SetVisualState hands them to SetColor, UpdateVisibility
    // with the alpha scaled by the fade.
    struct RecordA {
        uint32_t m_labelColorRaw;      // +0x00 m_pLabel's colour
        uint32_t m_valueTextColorRaw;  // +0x04 m_pValueText's colour
        uint32_t m_valueImageColorRaw; // +0x08 m_pValueImage's colour
        uint8_t m_ui8ValueImageBlend;  // +0x0c m_pValueImage's blend (IKBillboard2d::m_bUseAlpha) (+0x0d..+0x0f: padding)
        uint8_t m_pad0d[3];
        CVector2 m_vValueImageSize;    // +0x10 m_pValueImage's size (ramps 10/11)
        uint8_t m_aui8PartBlend[2];    // +0x18 m_apUnk58[0] / [1] blend; read raw, after +0x1c..+0x2b (+0x1a..+0x1b: padding)
        uint8_t m_pad1a[2];
        // +0x1c [0..1] m_apUnk58[0]'s size (ramps 0/2), [2..3] m_apUnk58[1]'s (ramps 1/3).
        float m_vUnk1c[4];
        void* m_apTextures[2];         // +0x2c m_apUnk58[0] / [1] textures (+0x30 read first; resolved)
        uint8_t m_aPartColors[8];      // +0x34 m_apUnk58[0] / [1] colours (RGBA each); read raw
        float m_vUnk3c[2];             // +0x3c
        float m_vUnk44[2];             // +0x44
        float m_vUnk4c[2];             // +0x4c
    };
    // +0x1b0, six 0x40-byte records (read from the last down), one per visual state: the two arrows.
    struct RecordB {
        uint8_t m_aui8ArrowBlend[2];   // +0x00 [0] left, [1] right; read raw, after +0x04..+0x13 (+0x02..+0x03: padding)
        uint8_t m_pad02[2];
        float m_vUnk04[4];             // +0x04 [0..1] the left arrow's size (ramps 4/6), [2..3] the right's (ramps 5/7)
        void* m_apTextures[2];         // +0x14 [0] left, [1] right (+0x18 read first; resolved)
        uint8_t m_aArrowColors[8];     // +0x1c [0..3] left, [4..7] right (RGBA); read raw
        float m_vUnk24[2];             // +0x24
        float m_vUnk2c[2];             // +0x2c
        float m_vUnk34[2];             // +0x34
        // +0x3c a reference (read before the textures), null in every front-end item: an effect started on
        // entering the state (SetVisualState) and reset by Open; its class is not identified (_maybe an
        // emitter: +0x10 flags, +0x4c, +0x50 a count < 0x40 of positions in +0x54's +0x10 table, +0x58).
        IKSerializable* m_unk3c;
    };
    // +0x334, one per value (0x2c bytes; OperatorNewArray with a count word before them).
    struct Entry {
        Entry();
        IKSerializable* m_pText;                               // +0x00 the value's text (a CKLocTextAccessor)
        void* m_pTexture;                                      // +0x04 m_pValueImage's texture (resolved)
        // +0x08 (IKVideo, CKVideoSegment) pairs: RefreshValueText plays the segment (else starts the video),
        // Close stops the videos. The first references are read for K_LEVEL/K_GAME_PLATEFORMS and type 8 only.
        TVector<CKInterfaceButton::RefPair, 1> m_vVideos;
        // +0x14 (CText2d, CKLocTextAccessor) pairs: RefreshValueText sets each text.
        TVector<CKInterfaceButton::RefPair, 1> m_vTexts;
        // +0x20 (CBillboard2d, texture, sprite-sheet duration (a float read as a word), rows, columns).
        TVector<CKInterfaceButton::TextEntry, 1> m_vImages;
    };
    // A FloatApproach ramp (k2000/misc/FloatApproach.h): the current value moves to the target at the speed.
    struct Ramp {
        float m_fTarget;
        float m_fSpeed;
        float m_fCurrent;
    };
    // The ramps of m_aRamps (sizes; Update applies them through AnimatePart).
    enum : uint32_t {
        kRampPart0X = 0, kRampPart1X = 1, kRampPart0Y = 2, kRampPart1Y = 3,
        kRampLeftX = 4, kRampRightX = 5, kRampLeftY = 6, kRampRightY = 7,
        kRampValueImageX = 10, kRampValueImageY = 11,  // 8, 9, 12, 13: reset by Open (8, 12 by StartFadeOut) only
        kNbRamps = 14,
    };
    // m_baOptions (+0x40d)
    enum : uint8_t {
        kOptionWrap = 0x01,        // ChangeValue wraps around at both ends
        kOptionHideArrows = 0x02,  // the arrow towards an end is hidden at that end
    };

    CKInterfaceButtonDouble();  // inlined in 0x00523f08 CKInterfaceButtonDouble_Create (copy 0x522ef8)
    ~CKInterfaceButtonDouble() override {}
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c8408
        return key == 0x634c || key == 0x63cc || key == 0xc;
    }
    // vt+0x10 0x00523690 CKInterfaceButtonDouble_Destroy: the texture references released, the entries freed.
    void Destroy() override;
    // vt+0x24 0x00521ae8 CKInterfaceButtonDouble_RecursiveRegistration: the base's, the state effects (RecordB +0x3c, from
    // the last), the label text (unchecked), the label, the value text and image, the arrows and parts (each from the
    // last), the sound dictionary (unchecked); then per entry from the last its text (unchecked), videos, texts (the
    // accessor unchecked) and images. Null references are skipped unless said otherwise.
    void RecursiveRegistration(int32_t type) override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00524060 CKInterfaceButtonDouble_Load
    int32_t PostLoad(int32_t /*type*/) override { return 1; }  // vt+0x30 0x5232f8

    // The button slots (CKInterfaceButtonBase.h). C1.6.
    void Open(uint8_t focused) override;            // vt+0x50 0x00523300 CKInterfaceButtonDouble_Open
    void Close() override;                          // vt+0x54 0x00523028 CKInterfaceButtonDouble_Close
    void Update(IKTime* frameClock) override;       // vt+0x58 0x00523b48 CKInterfaceButtonDouble_Update
    // vt+0x5c 0x005223e0: 0 normal, 1 validated, 2 focused, 3 decrease (left), 4 increase (right).
    void SetInteractionState(int32_t state) override;
    void SetPosition(const CVector2& position) override;  // vt+0x60 0x005224d0 CKInterfaceButtonDouble_SetPosition
    void UpdateVisibility(uint8_t fadeIn) override;  // vt+0x68 0x005228f0 CKInterfaceButtonDouble_UpdateVisibility
    void Show() override;                           // vt+0x6c 0x0051f9d8 CKInterfaceButtonDouble_Show
    void Hide() override;                           // vt+0x70 0x0051fb88 CKInterfaceButtonDouble_Hide
    void StartFadeOut() override;                   // vt+0x74 0x00522e68 CKInterfaceButtonDouble_StartFadeOut
    // vt+0x78 0x9c8440 (lfs TOC +0x7740 = 0.0)
    uint8_t IsFadeOutFinished() override { return m_fFadeOutTime <= 0.0f ? 1 : 0; }
    void SetDisabled(uint8_t disabled) override;    // vt+0x84 0x005222d8 CKInterfaceButtonDouble_SetDisabled
    float Vf88() override { return m_fFadeOutDuration; }     // vt+0x88 0x9c8468
    void Vf8C(float value) override { m_fFadeOutDuration = value; }  // vt+0x8c 0x9c8470

    // 0x0051fdb8 CKInterfaceButtonDouble_RefreshValueText: the value's text and image, then the entry's
    // videos, texts and images.
    void RefreshValueText();
    // 0x00520358 CKInterfaceButtonDouble_LoadOptionValue: m_ui8Value from the game manager's edited options
    // (clamped to the entries), then RefreshValueText; the second-player options are disabled with one
    // player. Also called by KBase730C_RefreshOptionWidgets_maybe (0x513eb0).
    void LoadOptionValue();
    // 0x00520810 CKInterfaceButtonDouble_ChangeValue_maybe: state 4 steps the value (m_bDecrease: down) and
    // calls the option's setter; then (any state) RefreshValueText.
    void ChangeValue(int32_t state);
    // 0x00520d98 CKInterfaceButtonDouble_SetVisualState (SetInteractionState and SetDisabled tail-call it).
    void SetVisualState(uint8_t state);
    // 0x005239a8 CKInterfaceButtonDouble_AnimatePart: a part's size from two ramps (stepped unless the fade-out
    // runs); a billboard's size, or a text's box (laid out again).
    void AnimatePart(IKSerializable* node, Ramp* rampX, Ramp* rampY, IKTime* frameClock, uint8_t isBillboard);

    IKSerializable* m_pLabelText;     // +0x30 the label's text (a CKLocTextAccessor; a reference)
    IKSerializable* m_pLabel;         // +0x34 the label (a CText2d; a reference)
    float m_vUnk38[2];                // +0x38
    IKSerializable* m_pValueText;     // +0x40 the value's text (a CText2d; a reference)
    float m_vUnk44[2];                // +0x44
    IKSerializable* m_pValueImage;    // +0x4c the value's image (a CBillboard2d; a reference)
    // +0x50 the arrows (CBillboard2d references, one array read): [0] left (decrease), [1] right (increase).
    IKSerializable* m_apUnk50[2];
    // +0x58 two more parts (CBillboard2d references, one array read): sizes, blends, textures and colours
    // from RecordA (+0x18, +0x1c, +0x2c, +0x34); placed at the item's position.
    IKSerializable* m_apUnk58[2];
    RecordA m_aRecordsA[4];           // +0x60
    RecordB m_aRecordsB[6];           // +0x1b0
    uint8_t m_ui8NbEntries;           // +0x330 (+0x331..+0x333: padding)
    uint8_t m_pad331[3];
    Entry* m_aEntries;                // +0x334
    uint8_t m_ui8Value;               // +0x338 the entry shown; Open sets 0 (+0x339..+0x33b: never written)
    uint8_t m_pad339[3];
    float m_fLabelOffsetX;            // +0x33c the label's x offset (SetPosition)
    CVector2 m_vValueTextOffset;      // +0x340 the value text's offset
    float m_fValueOffsetX;            // +0x348 the value image's x offset; the arrows sit around it
    float m_fArrowSpacing;            // +0x34c the arrows' x distance from m_fValueOffsetX
    // +0x350 the direction of state 4: SetInteractionState(3) sets 1 (decrease), (4) sets 0 (increase).
    // Not written by the constructor or Load (+0x351..+0x353: never written).
    uint8_t m_bDecrease;
    uint8_t m_pad351[3];
    Ramp m_aRamps[kNbRamps];          // +0x354 the constructor sets 0; Open sets {0, m_fAnimSpeed, 0}
    float m_fAnimSpeed;               // +0x3fc the ramps' and the fade's speed
    IKSerializable* m_pSounds;        // +0x400 a CKSoundDictionaryID (a reference): 0 focus, 1 disabled_maybe, 2 change, 3 validate
    float m_fFadeOutTime;             // +0x404 vt+0x78 tests it <= 0; Open and StartFadeOut copy +0x408
    float m_fFadeOutDuration;         // +0x408 (vt+0x88 / +0x8c)
    uint8_t m_ui8Mode;                // +0x40c bits 0..4: the option (LoadOptionValue, ChangeValue); read after +0x40d
    uint8_t m_baOptions;              // +0x40d kOption* (+0x40e..+0x40f: padding)
    uint8_t m_pad40e[2];
};
DOTD_ASSERT_SIZE(CKInterfaceButtonDouble::RecordA, 0x54);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble::RecordA, m_valueImageColorRaw, 0x08);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble::RecordA, m_ui8ValueImageBlend, 0x0c);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble::RecordA, m_vValueImageSize, 0x10);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble::RecordA, m_aui8PartBlend, 0x18);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble::RecordA, m_vUnk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble::RecordA, m_apTextures, 0x2c);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble::RecordA, m_aPartColors, 0x34);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble::RecordA, m_vUnk4c, 0x4c);
DOTD_ASSERT_SIZE(CKInterfaceButtonDouble::RecordB, 0x40);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble::RecordB, m_vUnk04, 0x04);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble::RecordB, m_apTextures, 0x14);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble::RecordB, m_aArrowColors, 0x1c);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble::RecordB, m_unk3c, 0x3c);
DOTD_ASSERT_SIZE(CKInterfaceButtonDouble::Entry, 0x2c);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble::Entry, m_pTexture, 0x04);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble::Entry, m_vVideos, 0x08);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble::Entry, m_vTexts, 0x14);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble::Entry, m_vImages, 0x20);
DOTD_ASSERT_SIZE(CKInterfaceButtonDouble::Ramp, 0xc);
DOTD_ASSERT_SIZE(CKInterfaceButtonDouble, 0x410);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble, m_pLabelText, 0x30);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble, m_pLabel, 0x34);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble, m_vUnk38, 0x38);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble, m_pValueText, 0x40);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble, m_pValueImage, 0x4c);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble, m_apUnk50, 0x50);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble, m_apUnk58, 0x58);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble, m_aRecordsA, 0x60);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble, m_aRecordsB, 0x1b0);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble, m_ui8NbEntries, 0x330);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble, m_aEntries, 0x334);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble, m_ui8Value, 0x338);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble, m_fLabelOffsetX, 0x33c);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble, m_vValueTextOffset, 0x340);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble, m_fValueOffsetX, 0x348);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble, m_fArrowSpacing, 0x34c);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble, m_bDecrease, 0x350);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble, m_aRamps, 0x354);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble, m_fAnimSpeed, 0x3fc);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble, m_pSounds, 0x400);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble, m_fFadeOutTime, 0x404);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble, m_fFadeOutDuration, 0x408);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble, m_ui8Mode, 0x40c);
DOTD_ASSERT_OFFSET(CKInterfaceButtonDouble, m_baOptions, 0x40d);
