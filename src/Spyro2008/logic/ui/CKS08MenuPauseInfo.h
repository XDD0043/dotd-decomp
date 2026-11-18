// CKS08MenuPauseInfo.h - the "Menu Pause Info" screen (key 0x960c, vtable 0xb2d0a8, size 0xf4 from 0x560920 CKS08MenuPauseInfo_Create). DotD only.
// Original unit: CKS08MenuPauseInfo.cpp (0x55f7a0-0x560f38).
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKMenuBase114c.h"
#include "k2000/core/Layout.h"

class CKS08MenuPauseInfo : public CKMenuBase114c {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x258)
    DOTD_DECLARE_FACTORIES(CKS08MenuPauseInfo)

    CKS08MenuPauseInfo() {  // 0x560920 CKS08MenuPauseInfo_Create: the base part, then the page vector
        m_aPageTextIds.m_ui32NbElt = 3;
        m_aPageTextIds.m_ui32NbUsedElt = 0;
        m_aPageTextIds.m_pBlock = nullptr;
    }
    ~CKS08MenuPauseInfo() override;  // vt+0x00 0x560c88 CKS08MenuPauseInfo_Destructor
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ca168
        return key == 0x960c || key == 0x114c || key == 0x730c || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;                                   // vt+0x2c 0x560648 CKS08MenuPauseInfo_Load
    void RecursiveRegistration(int32_t type) override;                                  // vt+0x24 0x55fa18 CKS08MenuPauseInfo_RecursiveRegistration
    uint32_t GetWidgetSlotCount() override { return 3; }                                 // vt+0x68 0x9ca1c8
    WidgetSlot* GetWidgetSlots() override { return m_aWidgetSlots; }                     // vt+0x6c 0x9ca1d0
    const char* GetMenuName() override { return "Menu Pause Info"; }                     // vt+0xb8 0x9ca1b8
    uint8_t VfBC() override { return 1; }                                                // vt+0xbc 0x9ca208
    IKSerializable** VfC0() override { return m_apMessageOuts; }                         // vt+0xc0 0x9ca210
    uint8_t VfC4() override { return 6; }                                                // vt+0xc4 0x9ca1e0
    IKSerializable** VfC8() override { return m_apMessageIns; }                          // vt+0xc8 0x9ca1e8
    uint8_t* VfCC() override { return m_abMessageInFlags; }                              // vt+0xcc 0x9ca1f8
    int32_t GetMenuId() override { return 0x10; }                                        // vt+0xe0 0x9ca1c0
    // vt+0xdc 0x0055fe00 CKS08MenuPauseInfo_OnStatePhase: enter (1): both players' input on (the second with two
    // players), the slow motion started (m_pTimeScalingFx through the FX service, the menu as owner) with the heroes'
    // input blocked and the first button shown, or without it the page timer started and the button hidden; the
    // title (or its background) shown or hidden; the first page. Tick (0): without the slow motion the pages flip on
    // the timer; the continue input. Exit (2): the pages dropped, the slow motion stopped, the input given back,
    // the game manager's "info pages pending" flag (+0xafc bit 7) cleared. Returns the menu id.
    uint8_t OnMenuState(int32_t phase, uint8_t other) override;
    // vt+0xe8 0x0055fdd0 CKS08MenuPauseInfo_OnItemEvent: item 0 validated (state 4, arg 2) with the slow motion on
    // flips the page.
    void OnItemState(uint8_t item, uint8_t state, uint8_t arg) override;
    // 0x0055fbf8 CKS08MenuPauseInfo_SetTitleText_maybe (the game manager's message 0x26c9): the title text (+0x91 set).
    void SetTitleText(IKSerializable* text);
    // 0x0055fc60 CKS08MenuPauseInfo_ShowNextPage_maybe: the next page's text and timer; after the last page the title
    // and the page cleared and the game manager's +0xafc bit 7 cleared (the menu closes on the next tick).
    void ShowNextPage();
    // 0x0055f8b8 CKS08MenuPauseInfo_CheckContinueInput_maybe: an active player's action 0xe (+ 0x14 per player) of
    // the "Flash Manager" input validates item 0 (SetItemState(0, 1, 0)).
    void CheckContinueInput();

    TVector<IKSerializable*, 3> m_aPageTextIds;  // +0x94 the pages' texts (the game manager's message 0x26ca adds one; ShowNextPage_maybe 0x55fc60 hands them to CText2d_SetTextById)
    uint32_t m_ui32Page;                         // +0xa0 the next page (ShowNextPage_maybe); the Load sets 0
    WidgetSlot m_aWidgetSlots[3];                // +0xa4
    IKSerializable* m_apMessageIns[6];           // +0xbc
    uint8_t m_abMessageInFlags[6];               // +0xd4 MessageProc sets one per VfC8 entry
    uint8_t m_unkda[2];
    IKSerializable* m_apMessageOuts[1];          // +0xdc
    float m_fPageDuration;                       // +0xe0 read (3.0 in LVL000); ShowNextPage_maybe copies it to +0xe4
    float m_fPageTimer;                          // +0xe4 run time (OnStatePhase 0x55fe00 counts it down)
    uint8_t m_bTimeScaling;                      // +0xe8 the Load sets 1 (OnStatePhase: start m_pTimeScalingFx)
    uint8_t m_unke9[3];
    IKSerializable* m_pTimeScalingFx;            // +0xec CKTimeScalingFxData (file key 0x264c)
    IKSerializable* m_pTimeScalingNode;          // +0xf0 CKTimeScalingNodeFx at run time (OnStatePhase); the Load sets null
};
DOTD_ASSERT_SIZE(CKS08MenuPauseInfo, 0xf4);
DOTD_ASSERT_OFFSET(CKS08MenuPauseInfo, m_aPageTextIds, 0x94);
DOTD_ASSERT_OFFSET(CKS08MenuPauseInfo, m_ui32Page, 0xa0);
DOTD_ASSERT_OFFSET(CKS08MenuPauseInfo, m_aWidgetSlots, 0xa4);
DOTD_ASSERT_OFFSET(CKS08MenuPauseInfo, m_apMessageIns, 0xbc);
DOTD_ASSERT_OFFSET(CKS08MenuPauseInfo, m_abMessageInFlags, 0xd4);
DOTD_ASSERT_OFFSET(CKS08MenuPauseInfo, m_apMessageOuts, 0xdc);
DOTD_ASSERT_OFFSET(CKS08MenuPauseInfo, m_fPageDuration, 0xe0);
DOTD_ASSERT_OFFSET(CKS08MenuPauseInfo, m_fPageTimer, 0xe4);
DOTD_ASSERT_OFFSET(CKS08MenuPauseInfo, m_bTimeScaling, 0xe8);
DOTD_ASSERT_OFFSET(CKS08MenuPauseInfo, m_pTimeScalingFx, 0xec);
DOTD_ASSERT_OFFSET(CKS08MenuPauseInfo, m_pTimeScalingNode, 0xf0);
