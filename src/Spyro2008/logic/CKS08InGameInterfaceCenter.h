// CKS08InGameInterfaceCenter.h - the centre HUD ("Interface InGame Centre") (key 0x79cc, vtable 0xb2bd10, size 0x26c from 0x535150 CKS08InGameInterfaceCenter_Create). DotD only.
// Original unit: CKS08InGameInterfaceCenter.cpp (0x5349a8-0x5378d8); its Delete and vt+0x8c / vt+0x90 sit at the end of
// CKS08InGameInterfaceBoss.cpp's range (0x534740 / 0x534790 / 0x5347d0).
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKMenuBase114c.h"
#include "k2000/core/Layout.h"

class CKS08InGameInterfaceCenter : public CKMenuBase114c {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x1e7)
    DOTD_DECLARE_FACTORIES(CKS08InGameInterfaceCenter)

    CKS08InGameInterfaceCenter() {}  // 0x535150 CKS08InGameInterfaceCenter_Create: the CKMenuBase114c part only
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c9300
        return key == 0x79cc || key == 0x114c || key == 0x730c || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;                                   // vt+0x2c 0x5354c8 CKS08InGameInterfaceCenter_Load
    // 0x00536310 CKS08InGameInterfaceCenter_QueueMessage_maybe: `text` under the default title (game manager vt+0x214),
    // shown now when no message is (+0x240 not positive), else queued (at most 4). 0x005364e0
    // ShowOrQueueMessagePair_maybe: the same with both texts given.
    void QueueMessage(IKSerializable* text);
    void ShowOrQueueMessagePair(IKSerializable* first, IKSerializable* second);
    // ---- C2.7 step 7 ----
    uint8_t OnMenuState(int32_t phase, uint8_t other) override;  // vt+0xdc 0x00536cf0 CKS08InGameInterfaceCenter_Update_maybe
    void ResetWidgets() override;                                 // vt+0x98 0x00537558 CKS08InGameInterfaceCenter_ResetWidgets_maybe
    // vt+0xb0 0x00535980 CKS08InGameInterfaceCenter_UpdateVisibility_maybe: the base's SetVisible, hidden also outside
    // game state 7, while the clock or a video holds, or with the game manager's +0x64 bit 26; a shown screen after a
    // fight takes the fury gauge down.
    uint8_t SetVisible(uint8_t visible) override;
    // 0x00535d00 CKS08InGameInterfaceCenter_UpdateMessageDisplay_maybe: the two message texts (slots 4 / 5) shown and
    // faded in / out over +0x254 / +0x25c with the shake +0x264; when the time is up the next queued pair is shown.
    void UpdateMessageDisplay(float dt);
    // 0x005369b0 CKS08InGameInterfaceCenter_RebuildWidgetCat1Tables_maybe: group 1 rebuilt with the fury marks (message
    // outs 1..11) the two gauges' displayed values reach.
    void RebuildFuryMarks();
    // 0x00534810 CKS08InGameInterfaceCenter_RefreshTextElementsB8C0_maybe: both message texts given the default text
    // and hidden.
    void RefreshTextElements();
    // 0x005353d0 / 0x005352e8 CKS08InGameInterfaceCenter_ShowFuryGauge(_2)_maybe: while visible (+0x268), message out 12
    // posted and the fury gauge shown (the first also sets the timed bit and restarts +0x208).
    void ShowFuryGauge();
    void ShowFuryGauge2();
    uint32_t GetWidgetSlotCount() override { return 6; }                                 // vt+0x68 0x9c9398
    WidgetSlot* GetWidgetSlots() override { return m_aWidgetSlots; }                     // vt+0x6c 0x9c93a0
    uint8_t Vf84() override { return 3; }                                                // vt+0x84 0x9c93b0
    RefGroup* Vf88() override { return m_aRefGroups; }                                   // vt+0x88 0x9c93b8
    // vt+0x8c 0x534790 CKS08InGameInterfaceCenter_vf8C (in CKS08InGameInterfaceBoss.cpp's range)
    IKSerializable** Vf8C(uint32_t group) override {
        if (group == 1) return m_apGroup1Refs;
        if (group == 0) return m_apGroup0Refs;
        if (group == 2) return m_apGroup2Refs;
        return nullptr;
    }
    // vt+0x90 0x5347d0 CKS08InGameInterfaceCenter_vf90 (in CKS08InGameInterfaceBoss.cpp's range)
    GroupState* Vf90(uint32_t group) override {
        if (group == 1) return m_aGroup1States;
        if (group == 0) return m_aGroup0States;
        if (group == 2) return m_aGroup2States;
        return nullptr;
    }
    const char* GetMenuName() override { return "Interface InGame Centre"; }             // vt+0xb8 0x9c9348 (TOC1+0x79b0)
    uint8_t VfBC() override { return 15; }                                               // vt+0xbc 0x9c9380
    IKSerializable** VfC0() override { return m_apMessageOuts; }                         // vt+0xc0 0x9c9388
    uint8_t VfC4() override { return 10; }                                               // vt+0xc4 0x9c9358
    IKSerializable** VfC8() override { return m_apMessageIns; }                          // vt+0xc8 0x9c9360
    uint8_t* VfCC() override { return m_abMessageInFlags; }                              // vt+0xcc 0x9c9370
    int32_t GetMenuId() override { return 0x0; }                                         // vt+0xe0 0x9c9350

    // 0x00534ad8 / 0x00534a88: the twin gauge `index`'s value and its capacity marker (index 0: the gauge at
    // +0x210, else +0x218).
    void SetGaugeValue(float value, int32_t index);
    void SetGaugeMarker(float ratio, int32_t index);
    // 0x00535238 CKS08InGameInterfaceCenter_HideFuryGauge_maybe: the "hide" flash message (message out 13), the
    // shown byte (+0x201, bits 16-23 of the word at +0x200) cleared. IsFuryGaugeShown: that byte.
    void HideFuryGauge();
    bool IsFuryGaugeShown() const { return m_ui8FuryShown201 != 0; }

    WidgetSlot m_aWidgetSlots[6];                // +0x94
    IKSerializable* m_apMessageIns[10];          // +0xc4 CKFlashMessageIn
    uint8_t m_abMessageInFlags[10];              // +0xec MessageProc sets one per VfC8 entry
    uint8_t m_padF6[2];
    IKSerializable* m_apMessageOuts[15];         // +0xf8 CKFlashText / CKFlashMessageOut (struct draft)
    RefGroup m_aRefGroups[3];                    // +0x134 m_pObject: CParticlesNodeFx (struct draft)
    IKSerializable* m_apGroup0Refs[1];           // +0x164
    GroupState m_aGroup0States[1];               // +0x168
    IKSerializable* m_apGroup1Refs[11];          // +0x170
    GroupState m_aGroup1States[11];              // +0x19c
    IKSerializable* m_apGroup2Refs[1];           // +0x1f4
    GroupState m_aGroup2States[1];               // +0x1f8
    uint8_t m_ui8Flags200;                       // +0x200 bit 0 the fury gauge is up for a fight (timed by +0x204)
    uint8_t m_ui8FuryShown201;                   // +0x201 the fury gauge is shown
    uint8_t m_pad202[2];
    float m_fUnk204;                             // +0x204 read by the Load
    float m_fFuryTime208;                        // +0x208 the time without a fight
    IKSerializable* m_pGauge20c;                 // +0x20c CKSuperGaugeCpnt (struct draft)
    IKSerializable* m_pGaugeUpdater210;          // +0x210 CKSuperGaugeCpntUpdater
    IKSerializable* m_pGauge214;                 // +0x214 CKSuperGaugeCpnt
    IKSerializable* m_pGaugeUpdater218;          // +0x218 CKSuperGaugeCpntUpdater
    IKSerializable* m_apQueue[4][2];             // +0x21c the queued message pairs (title, text)
    uint8_t m_ui8QueueCount;                     // +0x23c
    uint8_t m_pad23d[3];
    float m_fUnk240;                             // +0x240 the message's time (+0x254 + +0x258 + +0x25c when shown)
    float m_fUnk244[2];                          // +0x244 one 8-byte read, both words swapped
    float m_fUnk24c[2];                          // +0x24c one 8-byte read, both words swapped
    float m_fUnk254;                             // +0x254
    float m_fUnk258;                             // +0x258
    float m_fUnk25c;                             // +0x25c
    IKSerializable* m_pQuake;                    // +0x260 CKQuakeCpnt (struct draft)
    IKSerializable* m_pQuakeUpdater;             // +0x264 CKQuakeCpntUpdater
    uint8_t m_ui8Visible268;                     // +0x268 SetVisible's argument
    uint8_t m_pad269[3];
};
DOTD_ASSERT_SIZE(CKS08InGameInterfaceCenter, 0x26c);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceCenter, m_aWidgetSlots, 0x94);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceCenter, m_apMessageIns, 0xc4);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceCenter, m_abMessageInFlags, 0xec);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceCenter, m_apMessageOuts, 0xf8);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceCenter, m_aRefGroups, 0x134);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceCenter, m_apGroup0Refs, 0x164);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceCenter, m_aGroup0States, 0x168);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceCenter, m_apGroup1Refs, 0x170);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceCenter, m_aGroup1States, 0x19c);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceCenter, m_apGroup2Refs, 0x1f4);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceCenter, m_aGroup2States, 0x1f8);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceCenter, m_fUnk204, 0x204);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceCenter, m_pGauge20c, 0x20c);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceCenter, m_pGaugeUpdater210, 0x210);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceCenter, m_pGauge214, 0x214);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceCenter, m_pGaugeUpdater218, 0x218);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceCenter, m_fUnk244, 0x244);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceCenter, m_fUnk24c, 0x24c);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceCenter, m_fUnk254, 0x254);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceCenter, m_fUnk258, 0x258);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceCenter, m_fUnk25c, 0x25c);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceCenter, m_pQuake, 0x260);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceCenter, m_pQuakeUpdater, 0x264);
