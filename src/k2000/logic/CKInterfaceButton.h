// CKInterfaceButton.h - a menu button with five visual states (key 0x630c, vtable 0xb2b760, size 0x3c0).
// Original unit: CKInterfaceButton.cpp (0x51b9d0-0x51f7e0). DotD only: no XXL2 class of this name, so
// the member names are descriptive. Base: CKInterfaceButtonBase (0x63cc).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKInterfaceButtonBase.h"
#include "k2000/util/TVector.h"

class CKInterfaceButton : public CKInterfaceButtonBase {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x18c)
    DOTD_DECLARE_FACTORIES(CKInterfaceButton)

    // An entry of a state's +0x7c table (8 bytes on the PS3), shared with CKInterfaceButtonDouble and
    // CKInterfaceCheckBox (the field names stay generic for them). In CKInterfaceButton's states it is a
    // video to play when the state's actions run (ApplyStateActions 0x51bde0, Close 0x51daf0):
    struct RefPair {
        // +0x00 read for K_LEVEL_PLATEFORMS, K_GAME_PLATEFORMS and type 8 only. An IKVideo: started with no
        // segment (vt+0x60 Start(0)) when m_second is null; Close stops it (vt+0x78).
        IKSerializable* m_first;
        IKSerializable* m_second;  // +0x04 a CKVideoSegment, played with Play(3, 0, 0) (its default mode)
    };
    // An entry of a state's +0x88 table (0xc bytes): a text set and coloured when the state's actions run.
    struct RefPairValue {
        IKSerializable* m_first;   // +0x00 a CText2d (vt+0x88 SetTextById; its IKText2d part's SetColor)
        IKSerializable* m_second;  // +0x04 a CKLocTextAccessor (its list's first text, else its +0x10 text)
        uint32_t m_valueRaw;       // +0x08 the text's colour, read raw (4 file bytes, RGBA in memory order)
    };
    // An entry of a state's +0x94 table (0x14 bytes): a billboard re-textured when the state's actions run.
    struct TextEntry {
        IKSerializable* m_pText;   // +0x00 a reference: a CBillboard2d (IKBillboard2d vt+0x3c SetTexture)
        void* m_pTexture;          // +0x04 a texture reference (resolved, one count held)
        // +0x08 a float (lfs; CBillboard2d_SetAnimTime_maybe 0x5b098, its sprite-sheet duration), read as a
        // raw word: the file bytes are the same.
        uint32_t m_unk08;
        uint32_t m_unk0c;          // +0x0c the sprite sheet's rows (CBillboard2d_SetSpriteSheetRows_maybe)
        uint32_t m_unk10;          // +0x10 the sprite sheet's columns (CBillboard2d_SetSpriteSheetColumns_maybe)
    };
    // One visual state (0xa0 bytes), read by 0x009c7678 CKInterfaceButton_LoadStateVisual_maybe. The states:
    // 0 normal, 1 disabled, 2 focused, 3 focused or validated while disabled, 4 validated (SetInteractionState).
    // Element i of the three billboards m_apUnk38[i] takes the textures, colours, blends, sizes and
    // sprite-sheet settings [i]; the text m_unk34 takes the text colour, the accessor's text and size 1.
    struct StateVisual {
        // +0x00 the text's colour, read raw (4 file bytes, RGBA in memory order; UpdateVisibility scales
        // the last byte, the alpha, by the fade)
        uint32_t m_textColorRaw;
        IKSerializable* m_pTextAccessor;  // +0x04 a CKLocTextAccessor reference: the text (SetVisualState)
        uint8_t m_abUseAlpha[3];       // +0x08 read raw; the billboards' IKBillboard2d::m_bUseAlpha (blend table index)
        uint8_t m_pad0b;
        // +0x0c one 0x18-byte read, every word swapped: three sizes (x, y), the targets of the size
        // animations (SetVisualState). [0] billboard 0, [1] billboard 1 and the text box, [2] billboard 2.
        float m_afSize0[2];            // +0x0c
        // +0x14 the item's size: billboard 1 and the text box (KBase730C_FindItemUnderCursor 0x515f20 hit
        // test: half of it around the element's position)
        float m_afSize[2];
        float m_afSize2[2];            // +0x1c
        void* m_apTextures[3];         // +0x24 texture references (read from the last down; resolved)
        uint32_t m_aBillboardColorsRaw[3];  // +0x30 the billboards' colours, read raw (12 bytes, RGBA in memory order)
        float m_afAnimDurations[3];    // +0x3c the billboards' sprite-sheet durations (> 0: animated)
        uint32_t m_aui32SheetRows[3];  // +0x48 the sprite sheets' rows (read as words; the file bytes are the same)
        uint32_t m_aui32SheetColumns[3];  // +0x54 the sprite sheets' columns
        // +0x60 a reference, read last: a CParticlesNodeFx started at the origin on entering the state
        // (only focused states have one in the front end)
        IKSerializable* m_pFx;
        TVector<IKSerializable*, 1> m_vpUnk64;  // +0x64 references (K_LEVEL/K_GAME_PLATEFORMS and type 8 only); not used at run time
        // +0x70 menu ids: with kFlagUpdated, ApplyStateActions starts the transition to each (the game
        // manager's vt+0x304 MenuId, then the menu's StartTransitionToMenu)
        TVector<uint8_t, 1> m_vMenuTransitions;
        TVector<RefPair, 1> m_vVideos;          // +0x7c videos started by the actions (RefPair)
        TVector<RefPairValue, 1> m_vTexts;      // +0x88 texts set by the actions (RefPairValue)
        TVector<TextEntry, 1> m_vBillboards;    // +0x94 billboards re-textured by the actions (TextEntry)
    };
    // m_baSuppress (+0x30) bits: set from construction (never initialised: the PS3 heap fill 0x33 has both
    // bits set), cleared by Open (bit 1 before the base Open, bit 0 after it). Names ours.
    enum : uint8_t {
        kSuppressText = 0x01,     // SetVisualState does not set the text from the state's accessor
        kSuppressActions = 0x02,  // ApplyStateActions does nothing
    };

    CKInterfaceButton();  // inlined in 0x0051eff0 CKInterfaceButton_Create (copy 0x51e3b8)
    ~CKInterfaceButton() override;  // vt+0x00 0x0051f4e8 CKInterfaceButton_Destructor (copy 0x51d2d8)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c7608
        return key == 0x630c || key == 0x63cc || key == 0xc;
    }
    void Destroy() override;  // vt+0x10 0x0051e1b8 CKInterfaceButton_Destroy
    // vt+0x24 0x0051cdc0 CKInterfaceButton_RecursiveRegistration: the base's, then per state from the last down its text
    // accessor, its +0x64 references, its videos, its texts (the accessor unchecked), its billboards and its particles;
    // then the label, billboards 2, 1, 0 and the sound dictionary (unchecked). Null references are skipped unless
    // said otherwise.
    void RecursiveRegistration(int32_t type) override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0051f638 CKInterfaceButton_Load
    int32_t PostLoad(int32_t /*type*/) override { return 1; }  // vt+0x30 0x0051e1b0 CKInterfaceButton_PostLoad

    // The button slots (CKInterfaceButtonBase.h). C1.6.
    void Open(uint8_t focused) override;            // vt+0x50 0x0051d610 CKInterfaceButton_Open
    void Close() override;                          // vt+0x54 0x0051daf0 CKInterfaceButton_Close
    void Update(IKTime* frameClock) override;       // vt+0x58 0x0051e700 CKInterfaceButton_Update
    void SetInteractionState(int32_t state) override;  // vt+0x5c 0x0051d510 CKInterfaceButton_SetInteractionState
    void SetPosition(const CVector2& position) override;  // vt+0x60 0x0051e008 CKInterfaceButton_SetPosition
    void UpdateVisibility(uint8_t fadeIn) override;  // vt+0x68 0x0051d7a0 CKInterfaceButton_UpdateVisibility
    void Show() override;                           // vt+0x6c 0x0051ba20 CKInterfaceButton_Show
    void Hide() override;                           // vt+0x70 0x0051bb30 CKInterfaceButton_Hide
    void StartFadeOut() override;                   // vt+0x74 0x0051d598 CKInterfaceButton_StartFadeOut
    // vt+0x78 0x9c7640 (lfs TOC +0x76ec = 0.0)
    uint8_t IsFadeOutFinished() override { return m_fFadeOutTime <= 0.0f ? 1 : 0; }
    // vt+0x80 0x0051bc40 CKInterfaceButton_vf80: the elements' vt+0x84 Render (billboards 2, 1, 0, then the text).
    void Vf80(IKTime* frameClock) override;
    void SetDisabled(uint8_t disabled) override;    // vt+0x84 0x0051d428 CKInterfaceButton_SetDisabled
    float Vf88() override { return m_fUnk3bc; }     // vt+0x88 0x9c7668
    void Vf8C(float value) override { m_fUnk3bc = value; }  // vt+0x8c 0x9c7670

    // 0x0051c1c0 CKInterfaceButton_SetVisualState (from SetInteractionState: 0 normal, 1 disabled, 2 focused,
    // 3 focused or validated while disabled, 4 validated).
    void SetVisualState(uint8_t state);
    // 0x0051bde0 CKInterfaceButton_ApplyStateActions
    void ApplyStateActions(uint8_t state);

    uint8_t m_baSuppress;             // +0x30 kSuppress* (not written by the constructor or Load)
    uint8_t m_pad31[3];               // never written
    IKSerializable* m_unk34;          // +0x34 a reference: the CText2d (the item's label)
    // +0x38 three references (one array read): CBillboard2d [0] (+0x38), [1] (+0x3c), [2] (+0x40); each takes
    // the state's [i] texture, colour, blend, size and sprite sheet
    IKSerializable* m_apUnk38[3];
    float m_fAnimSpeed;               // +0x44 the size animations' speed (and the fades'); Load reads it first
    // +0x48 / +0x6c the size animations (FloatApproach {target, speed, current}), x and y, per element:
    // [0] billboard 0, [1] billboard 1 and the text box, [2] billboard 2. The constructor sets 0; Open
    // resets them; SetVisualState sets the targets (the state's sizes) and speeds; Update steps them.
    float m_afSizeAnimX[3][3];
    float m_afSizeAnimY[3][3];
    StateVisual m_aStates[5];         // +0x90 read from the last down
    // +0x3b0 a CKSoundDictionaryID reference: [0] played on entering state 2 (focused), [1] state 3, [2] state 4
    IKSerializable* m_pSounds;
    uint8_t m_unk3b4;                 // +0x3b4 the shortcut action (HandleShortcutButtons 0x512d68; 0xff none)
    uint8_t m_pad3b5[3];
    float m_fFadeOutTime;             // +0x3b8 StartFadeOut / Open copy +0x3bc; vt+0x78 tests it <= 0
    float m_fUnk3bc;                  // +0x3bc the fade-out duration (vt+0x88 / +0x8c)
};
DOTD_ASSERT_SIZE(CKInterfaceButton::RefPair, 0x8);
DOTD_ASSERT_SIZE(CKInterfaceButton::RefPairValue, 0xc);
DOTD_ASSERT_SIZE(CKInterfaceButton::TextEntry, 0x14);
DOTD_ASSERT_SIZE(CKInterfaceButton::StateVisual, 0xa0);
DOTD_ASSERT_OFFSET(CKInterfaceButton::StateVisual, m_pTextAccessor, 0x04);
DOTD_ASSERT_OFFSET(CKInterfaceButton::StateVisual, m_abUseAlpha, 0x08);
DOTD_ASSERT_OFFSET(CKInterfaceButton::StateVisual, m_afSize0, 0x0c);
DOTD_ASSERT_OFFSET(CKInterfaceButton::StateVisual, m_afSize, 0x14);
DOTD_ASSERT_OFFSET(CKInterfaceButton::StateVisual, m_afSize2, 0x1c);
DOTD_ASSERT_OFFSET(CKInterfaceButton::StateVisual, m_apTextures, 0x24);
DOTD_ASSERT_OFFSET(CKInterfaceButton::StateVisual, m_aBillboardColorsRaw, 0x30);
DOTD_ASSERT_OFFSET(CKInterfaceButton::StateVisual, m_afAnimDurations, 0x3c);
DOTD_ASSERT_OFFSET(CKInterfaceButton::StateVisual, m_aui32SheetRows, 0x48);
DOTD_ASSERT_OFFSET(CKInterfaceButton::StateVisual, m_aui32SheetColumns, 0x54);
DOTD_ASSERT_OFFSET(CKInterfaceButton::StateVisual, m_pFx, 0x60);
DOTD_ASSERT_OFFSET(CKInterfaceButton::StateVisual, m_vpUnk64, 0x64);
DOTD_ASSERT_OFFSET(CKInterfaceButton::StateVisual, m_vMenuTransitions, 0x70);
DOTD_ASSERT_OFFSET(CKInterfaceButton::StateVisual, m_vVideos, 0x7c);
DOTD_ASSERT_OFFSET(CKInterfaceButton::StateVisual, m_vTexts, 0x88);
DOTD_ASSERT_OFFSET(CKInterfaceButton::StateVisual, m_vBillboards, 0x94);
DOTD_ASSERT_SIZE(CKInterfaceButton, 0x3c0);
DOTD_ASSERT_OFFSET(CKInterfaceButton, m_baSuppress, 0x30);
DOTD_ASSERT_OFFSET(CKInterfaceButton, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKInterfaceButton, m_apUnk38, 0x38);
DOTD_ASSERT_OFFSET(CKInterfaceButton, m_fAnimSpeed, 0x44);
DOTD_ASSERT_OFFSET(CKInterfaceButton, m_afSizeAnimX, 0x48);
DOTD_ASSERT_OFFSET(CKInterfaceButton, m_afSizeAnimY, 0x6c);
DOTD_ASSERT_OFFSET(CKInterfaceButton, m_aStates, 0x90);
DOTD_ASSERT_OFFSET(CKInterfaceButton, m_pSounds, 0x3b0);
DOTD_ASSERT_OFFSET(CKInterfaceButton, m_unk3b4, 0x3b4);
DOTD_ASSERT_OFFSET(CKInterfaceButton, m_fFadeOutTime, 0x3b8);
DOTD_ASSERT_OFFSET(CKInterfaceButton, m_fUnk3bc, 0x3bc);

// 0x009c7678 CKInterfaceButton_LoadStateVisual_maybe (an out-of-line copy of an inline reader; the
// other button classes inline it as well).
void CKInterfaceButton_LoadStateVisual(CKInterfaceButton::StateVisual* state, IKFile* file, int32_t type);
// The tables the state readers (this one and CKInterfaceCheckBox's) share: the count, the block sized as
// the original sizes it (capacity 1, grown to count + 1), then the entries from the last down. The first
// reference of a RefPair is read for K_LEVEL_PLATEFORMS, K_GAME_PLATEFORMS and type 8 only.
void CKInterfaceButton_LoadRefPairs(TVector<CKInterfaceButton::RefPair, 1>* v, IKFile* file, int32_t type);
void CKInterfaceButton_LoadRefPairValues(TVector<CKInterfaceButton::RefPairValue, 1>* v, IKFile* file);
void CKInterfaceButton_LoadTextEntries(TVector<CKInterfaceButton::TextEntry, 1>* v, IKFile* file);
