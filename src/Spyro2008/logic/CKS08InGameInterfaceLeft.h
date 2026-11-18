// CKS08InGameInterfaceLeft.h - Spyro's HUD panel ("Interface InGame Gauche") (key 0x59cc, vtable 0xb2be18, size 0x294 from 0x5392d0 CreateCKS08InGameInterfaceLeft). DotD only.
// Original unit: CKS08InGameInterfaceLeft.cpp (0x5378d8-0x53c360). CKS08InGameInterfaceRight is the same layout for Cynder.
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKMenuBase114c.h"
#include "k2000/core/Layout.h"

struct RwTexture;

class CKS08InGameInterfaceLeft : public CKMenuBase114c {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x167)
    DOTD_DECLARE_FACTORIES(CKS08InGameInterfaceLeft)

    // One reference group's single reference and its state (vt+0x8c / vt+0x90 point into it).
    struct GroupSlot {
        IKSerializable* m_pRef;  // +0x00
        GroupState m_state;      // +0x04
    };

    CKS08InGameInterfaceLeft();  // 0x5392d0 CreateCKS08InGameInterfaceLeft
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c93c8
        return key == 0x59cc || key == 0x114c || key == 0x730c || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;                                   // vt+0x2c 0x53a840 CKS08InGameInterfaceLeft_Load
    // 0x00538f20 CKS08InGameInterfaceLeft_ShowUpgradeText_maybe (CKS08InGameInterfaceLeft.cpp).
    void ShowUpgradeText(const char* text, int32_t shake);
    // 0x0053a2d8 / 0x0053a5f8 / 0x0053a4b8 (Right: 0x00540318 / 0x0053ffc0 / 0x0053fe80): the dragon's panel.
    void HidePanel();
    void ShowPanel(IKSerializable* text);
    void ShowPanelType1(IKSerializable* text);
    // ---- C2.7 step 7 (the per-frame part; Left / Right share the code through HudSideOps.h) ----
    // vt+0xdc: the update (phase 0 every frame while shown, 1 enter, 2 leave). Returns the menu id.
    uint8_t OnMenuState(int32_t phase, uint8_t other) override;
    void ResetWidgets() override;  // vt+0x98
    void Resume() override;        // vt+0x58 (the base's, then the combo display shown again while it runs)
    // The combo display (widget slot 8, its gauge +0x290, its shake +0x288, the time +0x278 of +0x27c).
    void OnNewComboHit(float value);
    void OnComboHit(float value);
    void EndComboDisplay();
    // The panel closed when no fight is on (message out 2).
    void CloseTimedPanel();
    // The element billboard (widget slot 6): its texture now (SetPanelElementObject) or after the bar shrank (SelectElement).
    void SetPanelElementObject(RwTexture* texture);
    void SelectElement(RwTexture* texture);
    // The restored clips (message out 8 in group 1 / 0) and the shard rows (+0x264 / +0x265 / +0x266, time +0x260).
    void QueueManaRestoredClip();
    void QueueHealthRestoredClip();
    void SetManaShardGauge(uint8_t count, uint8_t shake);
    void SetHealthShardGauge(uint8_t count, uint8_t shake);
    void UpdateShake(float dt, float scaledDt);
    // 0x00538608 CKS08InGameInterfaceLeft_StartShake_maybe: +0x230 = +0x23c + +0x240, the quake updater started (no caller
    // in the original: its descriptor is referenced nowhere; ShowUpgradeText inlines the same two statements).
    void StartShake();
    void UpdateUpgradeText(float dt);
    // The gauge updaters and the panel timer under the names HudSideOps.h uses.
    IKSerializable* HealthGaugeUpdater() { return m_pGaugeUpdater224; }
    IKSerializable* ManaGaugeUpdater() { return m_pGaugeUpdater22c; }
    float& PanelTime() { return m_fUnk21c; }
    float PanelHoldTime() const { return m_fUnk218; }
    uint32_t GetWidgetSlotCount() override { return 20; }                                // vt+0x68 0x9c9460
    WidgetSlot* GetWidgetSlots() override { return m_aWidgetSlots; }                     // vt+0x6c 0x9c9468
    uint8_t Vf84() override { return 4; }                                                // vt+0x84 0x9c9478
    RefGroup* Vf88() override { return m_aRefGroups; }                                   // vt+0x88 0x9c9480
    IKSerializable** Vf8C(uint32_t group) override;                                      // vt+0x8c 0x537928 CKS08InGameInterfaceLeft_vf8C
    GroupState* Vf90(uint32_t group) override;                                           // vt+0x90 0x537970 CKS08InGameInterfaceLeft_vf90
    const char* GetMenuName() override { return "Interface InGame Gauche"; }             // vt+0xb8 0x9c9410 (TOC1+0x7a38)
    uint8_t VfBC() override { return 15; }                                               // vt+0xbc 0x9c9420
    IKSerializable** VfC0() override { return m_apMessageOuts; }                         // vt+0xc0 0x9c9428
    uint8_t VfC4() override { return 10; }                                               // vt+0xc4 0x9c9438
    IKSerializable** VfC8() override { return m_apMessageIns; }                          // vt+0xc8 0x9c9440
    uint8_t* VfCC() override { return m_abMessageInFlags; }                              // vt+0xcc 0x9c9450
    int32_t GetMenuId() override { return 0x0; }                                         // vt+0xe0 0x9c9418

    WidgetSlot m_aWidgetSlots[20];               // +0x94
    IKSerializable* m_apMessageIns[10];          // +0x134 CKFlashMessageIn
    uint8_t m_abMessageInFlags[10];              // +0x15c MessageProc sets one per VfC8 entry
    uint8_t m_pad166[2];
    IKSerializable* m_apMessageOuts[15];         // +0x168 CKFlashMessageOut / CKFlashText (struct draft)
    RefGroup m_aRefGroups[4];                    // +0x1a4 m_pObject: CParticlesNodeFx (struct draft)
    GroupSlot m_aGroupSlots[4];                  // +0x1e4
    // +0x214 bit 0 the panel is up (a fight), bit 1 the element bar runs, bit 2 the label panel is shown (HudPanelOps.h).
    uint8_t m_ui8Flags214;
    uint8_t m_ui8Active215;                      // +0x215 the gauges, texts and shards update
    uint8_t m_pad216[2];
    float m_fUnk218;                             // +0x218 read by the Load
    float m_fUnk21c;                             // +0x21c the panel's time without a fight (closes at +0x218)
    IKSerializable* m_pGauge220;                 // +0x220 CKSuperGaugeCpnt (struct draft)
    IKSerializable* m_pGaugeUpdater224;          // +0x224 CKSuperGaugeCpntUpdater
    IKSerializable* m_pGauge228;                 // +0x228 CKSuperGaugeCpnt
    IKSerializable* m_pGaugeUpdater22c;          // +0x22c CKSuperGaugeCpntUpdater
    float m_fUnk230;                             // +0x230 the upgrade text's time (shown while positive)
    float m_fUnk234[2];                          // +0x234 one 8-byte read, both words swapped
    float m_fUnk23c;                             // +0x23c
    float m_fUnk240;                             // +0x240
    IKSerializable* m_pQuake244;                 // +0x244 CKQuakeCpnt (struct draft)
    IKSerializable* m_pQuakeUpdater248;          // +0x248 CKQuakeCpntUpdater
    float m_fUnk24c;                             // +0x24c the element bar's full height (its width at enter)
    float m_fUnk250;                             // +0x250 the Create sets 0.0
    float m_fUnk254;                             // +0x254 the Create sets 0.0
    float m_fUnk258;                             // +0x258 the Create sets 0.0
    RwTexture* m_pPendingTexture;                // +0x25c the element texture set when the bar is down (SelectElement)
    float m_fShardTime;                          // +0x260 the shard rows' time
    uint8_t m_ui8ShardsA;                        // +0x264 the first row's count (Spyro: health, 4 shards)
    uint8_t m_ui8ShardsB;                        // +0x265 the second row's count (Spyro: mana, 5 shards)
    uint8_t m_ui8ShardShake;                     // +0x266 the last shard shakes (quake +0x274)
    uint8_t m_pad267;
    float m_fUnk268;                             // +0x268
    float m_fUnk26c;                             // +0x26c
    IKSerializable* m_pQuake270;                 // +0x270 CKQuakeCpnt
    IKSerializable* m_pQuakeUpdater274;          // +0x274 CKQuakeCpntUpdater
    float m_fComboTime;                          // +0x278 the combo display's fade time (from +0x27c)
    float m_fUnk27c;                             // +0x27c
    uint8_t m_unk280;                            // +0x280 one byte read
    uint8_t m_pad281[3];
    IKSerializable* m_pQuake284;                 // +0x284 CKQuakeCpnt
    IKSerializable* m_pQuakeUpdater288;          // +0x288 CKQuakeCpntUpdater
    IKSerializable* m_pGauge28c;                 // +0x28c CKGaugeCpnt
    IKSerializable* m_pGaugeUpdater290;          // +0x290 CKGaugeCpntUpdater
};
DOTD_ASSERT_SIZE(CKS08InGameInterfaceLeft, 0x294);
DOTD_ASSERT_SIZE(CKS08InGameInterfaceLeft::GroupSlot, 0xc);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceLeft, m_aWidgetSlots, 0x94);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceLeft, m_apMessageIns, 0x134);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceLeft, m_abMessageInFlags, 0x15c);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceLeft, m_apMessageOuts, 0x168);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceLeft, m_aRefGroups, 0x1a4);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceLeft, m_aGroupSlots, 0x1e4);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceLeft, m_fUnk218, 0x218);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceLeft, m_pGauge220, 0x220);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceLeft, m_pGaugeUpdater224, 0x224);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceLeft, m_pGauge228, 0x228);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceLeft, m_pGaugeUpdater22c, 0x22c);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceLeft, m_fUnk234, 0x234);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceLeft, m_fUnk23c, 0x23c);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceLeft, m_fUnk240, 0x240);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceLeft, m_pQuake244, 0x244);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceLeft, m_pQuakeUpdater248, 0x248);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceLeft, m_fUnk250, 0x250);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceLeft, m_fUnk254, 0x254);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceLeft, m_fUnk258, 0x258);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceLeft, m_fUnk268, 0x268);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceLeft, m_fUnk26c, 0x26c);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceLeft, m_pQuake270, 0x270);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceLeft, m_pQuakeUpdater274, 0x274);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceLeft, m_fUnk27c, 0x27c);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceLeft, m_unk280, 0x280);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceLeft, m_pQuake284, 0x284);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceLeft, m_pQuakeUpdater288, 0x288);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceLeft, m_pGauge28c, 0x28c);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceLeft, m_pGaugeUpdater290, 0x290);

// 0x00537d68 / 0x00537df8 (CKS08InGameInterfaceLeft.cpp): the mana and health gauges.
void SetSpyroManaGaugeValue(double requestedValue, CKS08InGameInterfaceLeft* hud);
void SetSpyroHealthGaugeValue(double requestedValue, CKS08InGameInterfaceLeft* hud);
