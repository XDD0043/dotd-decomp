// CKS08MenuElements.h - the "Menu Elements" screen (key 0x84cc, vtable 0xb2c550, size 0x498 from 0x54c920 CKS08MenuElements_Create). DotD only.
// Original unit: CKS08MenuElements.cpp (0x54ad98-0x553bc8).
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKMenuBase114c.h"
#include "k2000/core/Layout.h"

class CKS08MenuElements : public CKMenuBase114c {
public:
    // A colour blinking towards a target (0x1c bytes, the layout of XXL2's CSmoothedCColorLinear, as
    // CColorizedScreenFx::SmoothedColor): Color_StartBlinkFade_maybe / Color_UpdateBlinkFade_maybe move m_aCurrent
    // towards m_aTarget at m_fSpeed (255 a second per unit).
    struct ColorBlink {
        uint8_t m_aTarget[4];   // +0x00 the colour bytes as stored
        uint8_t m_aCurrent[4];  // +0x04 the colour drawn
        float m_fSpeed;         // +0x08 the distance (0..255 per channel) / the period / 255
        float m_afCurrent[4];   // +0x0c m_aCurrent as floats
    };
    DOTD_CLASS_KEY(kCategoryLogic, 0x213)
    DOTD_DECLARE_FACTORIES(CKS08MenuElements)

    CKS08MenuElements() {  // 0x54c920 CKS08MenuElements_Create: the base part, then three vectors
        m_vUnk248[0] = 0.0f;  // the stores in the original order (lfs TOC1+0x7e20 = 0.0)
        m_vUnk274[0] = 0.0f;
        m_vUnk248[1] = 0.0f;
        m_vUnk248[2] = 0.0f;
        m_vUnk280[0] = 0.0f;
        m_vUnk274[1] = 0.0f;
        m_vUnk274[2] = 0.0f;
        m_vUnk280[1] = 0.0f;
        m_vUnk280[2] = 0.0f;
    }
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c9948
        return key == 0x84cc || key == 0x114c || key == 0x730c || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;                                   // vt+0x2c 0x5514f0 CKS08MenuElements_Load
    void RecursiveRegistration(int32_t type) override;                                  // vt+0x24 0x54bea8 CKS08MenuElements_RecursiveRegistration
    // vt+0x10 0x0054c360 CKS08MenuElements_Destroy: the base's, then the textures +0x2c8..+0x2ac and +0x328..+0x2cc (the
    // last first).
    void Destroy() override;
    uint32_t GetWidgetSlotCount() override { return 44; }                                // vt+0x68 0x9c99e8
    WidgetSlot* GetWidgetSlots() override { return m_aWidgetSlots; }                     // vt+0x6c 0x9c99f0
    const char* GetMenuName() override { return "Menu Elements"; }                       // vt+0xb8 0x9c9998
    uint8_t VfBC() override { return 5; }                                                // vt+0xbc 0x9c99d0
    IKSerializable** VfC0() override { return m_apMessageOuts; }                         // vt+0xc0 0x9c99d8
    uint8_t VfC4() override { return 8; }                                                // vt+0xc4 0x9c99a8
    IKSerializable** VfC8() override { return m_apMessageIns; }                          // vt+0xc8 0x9c99b0
    uint8_t* VfCC() override { return m_abMessageInFlags; }                              // vt+0xcc 0x9c99c0
    int32_t GetMenuId() override { return 0x5; }                                         // vt+0xe0 0x9c99a0
    uint8_t VfF0() override { return 1; }                                                // vt+0xf0 0x9c9a00
    uint8_t VfF4() override { return 8; }                                                // vt+0xf4 0x9c9a08 the back item

    // ---- C2.8 menus-load: the screen (CKS08MenuElements.cpp) ----
    int32_t MessageProc(uint16_t message, void* data) override;                        // vt+0x1c 0x005538d0
    uint8_t OnMenuState(int32_t phase, uint8_t other) override;                         // vt+0xdc 0x00550af8 (Ghidra OnStatePhase)
    void OnItemState(uint8_t item, uint8_t state, uint8_t arg) override;                // vt+0xe8 0x0054e940 (Ghidra OnItemEvent)
    void TransferGemsStep(uint8_t dragon, uint32_t amount, int32_t delayed);           // 0x0054e648
    void CheckElementLevelUp(uint8_t dragon);                                           // 0x0054dd08
    void RefreshElementTexts(uint8_t dragon);                                           // 0x0054ca48
    IKSerializable* GetTotalLevelUpText(uint8_t dragon);                                // 0x0054d6a8
    void SetTotalLevelGaugeTier(uint8_t dragon, uint32_t tier, uint32_t texture, int32_t burst);  // 0x0054c490
    void RefreshTotalLevelGauge(uint8_t dragon);                                        // 0x0054d8f8
    void ToggleActiveDragon();                                                          // 0x005501d0
    void HandleElementSelectInput(uint8_t dragon);                                      // 0x00550610
    void AnimateElementWheel(uint8_t dragon);                                           // 0x0054e2d0
    void UpdateProgressIndicator(uint8_t dragon);                                       // 0x0054d1c8
    // 0x0054b040 CKS08MenuElements_ComputeElementRank_maybe: the total level's tier and the levels above it (both zeroed
    // first; the same loop as TotalLevelTier). No caller in the original (its descriptor is referenced nowhere).
    void ComputeElementRank(uint8_t dragon, uint32_t* rank, uint32_t* rest);
    // 0x0054b160 CKS08MenuElements_UpdateUpgradePointsDisplay_maybe: the gem bar (slot 2 + dragon) scaled to the free gems
    // over those on entering, the count (slot 4 + dragon) as "%d". No caller in the original either.
    void UpdateUpgradePointsDisplay(uint8_t dragon);
    // The visual feedback of a level-up (C2.8 lvl020-misc): 0x0054b3b0 ResetPlayerVisualEffects_maybe,
    // 0x0054eee8 UpdatePlayerVisualEffects_maybe, 0x00552240 PlayLevelUpFeedback_maybe.
    void ResetPlayerVisualEffects(uint8_t dragon);
    void UpdatePlayerVisualEffects(uint8_t dragon);
    void PlayLevelUpFeedback(uint8_t dragon);

    WidgetSlot m_aWidgetSlots[44];               // +0x94
    IKSerializable* m_apMessageIns[8];           // +0x1f4
    uint8_t m_abMessageInFlags[8];               // +0x214 MessageProc sets one per VfC8 entry
    IKSerializable* m_apMessageOuts[5];          // +0x21c
    uint32_t m_aGemsAtOpen[2];                   // +0x230 per dragon: the free gems (the structure's +0x84 / +0x88) on entering
    uint32_t m_aGemsLeft[2];                     // +0x238 per dragon: the free gems not given yet (the transfer counts them down)
    uint8_t m_unk240;                            // +0x240 the Load clears it; entering sets 1, the dragon's message in (VfCC [6 + dragon]) 0
    uint8_t m_ui8Dragon;                         // +0x241 the dragon shown (0 Spyro, 1 Cynder)
    uint8_t m_ui8Player;                         // +0x242 the player that controls the screen (two players: the dragon's)
    uint8_t m_pad243;
    uint32_t m_unk244;                           // +0x244 read by the Load: the gems one transfer step gives
    float m_vUnk248[3];                          // +0x248 the constructor sets 0; the transfer delay (FloatApproach {target, speed, current})
    float m_fTransferTime;                       // +0x254 time since the last transfer step
    float m_fTransferSoundTime;                  // +0x258 time since the last transfer sound
    float m_afUnk25c[6];                         // +0x25c read by the Load
    // +0x274 / +0x280 the constructor sets 0: the dragons' element wheels (FloatApproach {target, speed, current}, degrees:
    // +0x28c steps of 360 a turn).
    float m_vUnk274[3];
    float m_vUnk280[3];
    uint8_t m_unk28c;                            // +0x28c read by the Load (1 byte)
    uint8_t m_unk28d[3];
    float m_fUnk290;                             // +0x290 read by the Load
    float m_fUnk294;                             // +0x294 read by the Load
    uint8_t m_aui8Element[2];                    // +0x298 per dragon: the element selected (0..3)
    uint8_t m_aui8PrevElement[2];                // +0x29a per dragon: the element before the last turn
    uint32_t m_ui32ElementLevel;                 // +0x29c the selected element's level when last checked
    IKSerializable* m_pText2a0;                  // +0x2a0 CKLocTextAccessor (struct draft)
    IKSerializable* m_pText2a4;                  // +0x2a4 CKLocTextAccessor (struct draft)
    uint32_t m_unk2a8;                           // +0x2a8
    void* m_apTextures2ac[8];                    // +0x2ac IKFile_ReadTextureRef, the last first
    void* m_apTextures2cc[24];                   // +0x2cc IKFile_ReadTextureRef, the last first
    uint8_t m_unk32c;                            // +0x32c the Load clears it
    uint8_t m_unk32d[3];
    IKSerializable* m_pFlashFx;                  // +0x330 CKFlashFxData (struct draft)
    float m_fBadgeShakeTime;                     // +0x334 the badge's (slot 0 + dragon) shake time (quake +0x338)
    IKSerializable* m_pQuake338;                 // +0x338 CKQuakeCpnt (struct draft)
    IKSerializable* m_pQuakeUpdater33c;          // +0x33c CKQuakeCpntUpdater (struct draft)
    float m_fBadgeX;                             // +0x340 the badge's position before the shake
    float m_fBadgeY;                             // +0x344
    float m_fTitleShakeTime;                     // +0x348 the title's (slot 12 + dragon) shake time (quake +0x34c)
    IKSerializable* m_pQuake34c;                 // +0x34c CKQuakeCpnt (struct draft)
    IKSerializable* m_pQuakeUpdater350;          // +0x350 CKQuakeCpntUpdater (struct draft)
    float m_fTitleHeight;                        // +0x354 the title's text size before the shake (slot 13's: BUG(original))
    float m_fTitleX;                             // +0x358 the title's position before the shake
    float m_fTitleY;                             // +0x35c
    ColorBlink m_badgeBlink;                     // +0x360 the badge's colour blink
    uint8_t m_aBadgeColor[4];                    // +0x37c the badge's colour before the blink
    uint8_t m_unk380[4];                         // +0x380 read raw: the badge's blink colour
    float m_unk384;                              // +0x384 read by the Load: the badge's blink period (seconds)
    float m_unk388;                              // +0x388 read by the Load: the badge's blink duration
    float m_fBadgeBlinkTime;                     // +0x38c the time in the period
    float m_fBadgeBlinkTotal;                    // +0x390 the time since the start
    uint8_t m_ui8BadgeBlinkOn;                   // +0x394 the blink's phase (1 towards the blink colour)
    uint8_t m_pad395[3];
    ColorBlink m_titleBlink;                     // +0x398 the title's colour blink
    uint8_t m_aTitleColor[4];                    // +0x3b4 the title's colour before the blink
    uint8_t m_unk3b8[4];                         // +0x3b8 read raw: the title's blink colour
    float m_fUnk3bc;                             // +0x3bc read by the Load: the title's blink period
    float m_fUnk3c0;                             // +0x3c0 read by the Load: the title's blink duration
    float m_fTitleBlinkTime;                     // +0x3c4
    float m_fTitleBlinkTotal;                    // +0x3c8
    uint8_t m_ui8TitleBlinkOn;                   // +0x3cc
    uint8_t m_pad3cd[3];
    // +0x3d0 the description texts' blinks (slots 16, 20, 18, 22 + dragon, in that order), their colours before
    // (+0x440), the common blink colour, period and duration (+0x450..), the period times, the time since the start
    // and the phases.
    ColorBlink m_aTextBlink[4];
    uint8_t m_aaTextColor[4][4];                 // +0x440
    uint8_t m_unk450[4];                         // +0x450 read raw
    float m_fUnk454;                             // +0x454 read by the Load: the period
    float m_fUnk458;                             // +0x458 read by the Load: the duration
    float m_afTextBlinkTime[4];                  // +0x45c
    float m_fTextBlinkTotal;                     // +0x46c
    uint8_t m_aui8TextBlinkOn[4];                // +0x470
    uint32_t m_unk474;                           // +0x474 read raw (no swap)
    float m_fUnk478;                             // +0x478 read by the Load
    float m_fUnk47c;                             // +0x47c read by the Load
    uint32_t m_unk480[2];                        // +0x480
    uint8_t m_unk488;                            // +0x488 read by the Load (1 byte)
    uint8_t m_unk489;                            // +0x489 read by the Load (1 byte)
    uint8_t m_unk48a[2];
    float m_fUnk48c;                             // +0x48c read by the Load
    IKSerializable* m_pSound;                    // +0x490 CKSoundDictionaryID (struct draft)
    uint8_t m_ui8LevelUpStep;                    // +0x494 the level-up message boxes: 1 the element's shown, 2 the total level's
    uint8_t m_pad495[3];
};
DOTD_ASSERT_SIZE(CKS08MenuElements, 0x498);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_aWidgetSlots, 0x94);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_apMessageIns, 0x1f4);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_abMessageInFlags, 0x214);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_apMessageOuts, 0x21c);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_unk240, 0x240);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_unk244, 0x244);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_vUnk248, 0x248);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_afUnk25c, 0x25c);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_vUnk274, 0x274);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_vUnk280, 0x280);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_unk28c, 0x28c);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_fUnk290, 0x290);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_fUnk294, 0x294);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_pText2a0, 0x2a0);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_pText2a4, 0x2a4);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_apTextures2ac, 0x2ac);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_apTextures2cc, 0x2cc);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_unk32c, 0x32c);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_pFlashFx, 0x330);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_fBadgeShakeTime, 0x334);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_pQuake338, 0x338);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_fBadgeX, 0x340);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_fTitleShakeTime, 0x348);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_fTitleHeight, 0x354);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_badgeBlink, 0x360);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_aBadgeColor, 0x37c);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_fBadgeBlinkTime, 0x38c);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_ui8BadgeBlinkOn, 0x394);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_titleBlink, 0x398);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_aTitleColor, 0x3b4);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_fTitleBlinkTime, 0x3c4);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_ui8TitleBlinkOn, 0x3cc);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_aTextBlink, 0x3d0);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_aaTextColor, 0x440);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_afTextBlinkTime, 0x45c);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_fTextBlinkTotal, 0x46c);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_aui8TextBlinkOn, 0x470);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_pQuakeUpdater33c, 0x33c);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_pQuake34c, 0x34c);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_pQuakeUpdater350, 0x350);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_unk380, 0x380);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_unk384, 0x384);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_unk388, 0x388);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_unk3b8, 0x3b8);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_fUnk3bc, 0x3bc);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_fUnk3c0, 0x3c0);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_unk450, 0x450);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_fUnk454, 0x454);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_fUnk458, 0x458);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_unk474, 0x474);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_fUnk478, 0x478);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_fUnk47c, 0x47c);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_unk488, 0x488);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_unk489, 0x489);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_fUnk48c, 0x48c);
DOTD_ASSERT_OFFSET(CKS08MenuElements, m_pSound, 0x490);
