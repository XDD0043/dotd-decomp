// CKS08MenuHits.h - the "Menu Hits" screen (key 0xa74c, vtable 0xb2c760, size 0xf0 from 0x555fa8 CKS08MenuHits_Create). DotD only.
// Original unit: CKS08MenuHits.cpp (0x5554c8-0x556840).
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKMenuBase114c.h"
#include "k2000/core/Layout.h"

class CKS08MenuHits : public CKMenuBase114c {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x29d)
    DOTD_DECLARE_FACTORIES(CKS08MenuHits)

    CKS08MenuHits() {}  // 0x555fa8 CKS08MenuHits_Create: the CKMenuBase114c part only
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c9ac8
        return key == 0xa74c || key == 0x114c || key == 0x730c || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;                                   // vt+0x2c 0x556090 CKS08MenuHits_Load
    void RecursiveRegistration(int32_t type) override;                                  // vt+0x24 0x555b78 CKS08MenuHits_RecursiveRegistration
    uint32_t GetWidgetSlotCount() override { return 5; }                                 // vt+0x68 0x9c9b68
    WidgetSlot* GetWidgetSlots() override { return m_aWidgetSlots; }                     // vt+0x6c 0x9c9b70
    const char* GetMenuName() override { return "Menu Hits"; }                           // vt+0xb8 0x9c9b18
    uint8_t VfBC() override { return 1; }                                                // vt+0xbc 0x9c9b50
    IKSerializable** VfC0() override { return m_apMessageOuts; }                         // vt+0xc0 0x9c9b58
    uint8_t VfC4() override { return 6; }                                                // vt+0xc4 0x9c9b28
    IKSerializable** VfC8() override { return m_apMessageIns; }                          // vt+0xc8 0x9c9b30
    uint8_t* VfCC() override { return m_abMessageInFlags; }                              // vt+0xcc 0x9c9b40
    int32_t GetMenuId() override { return 0x7; }                                         // vt+0xe0 0x9c9b20
    uint8_t GetSelection(uint8_t /*player*/) override { return 0xff; }                   // vt+0xe4 0x9c9b90
    uint8_t VfF0() override { return 1; }                                                // vt+0xf0 0x9c9b80
    uint8_t VfF4() override { return 2; }                                                // vt+0xf4 0x9c9b88 the back item
    // vt+0xdc 0x00555a70 CKS08MenuHits_OnStatePhase: 1 enter (page 0, the texts), 0 update (the paging buttons).
    uint8_t OnMenuState(int32_t phase, uint8_t other) override;
    // vt+0xe8 0x00555800 CKS08MenuHits_OnItemEvent: item 0 (previous) / 1 (next) validated turns the page (32, wrapping).
    void OnItemState(uint8_t item, uint8_t state, uint8_t arg) override;

    // 0x005555c0 CKS08MenuHits_RefreshPageTexts: the page's texts (title, description, controls) and the neighbours' titles.
    void RefreshPageTexts();
    // 0x00555888 CKS08MenuHits_HandlePagingButtons: per active player, "Flash Manager" action 9 validates the next item (1),
    // else action 8 the previous item (0).
    void HandlePagingButtons();

    WidgetSlot m_aWidgetSlots[5];                // +0x94
    IKSerializable* m_apMessageIns[6];           // +0xbc
    uint8_t m_abMessageInFlags[6];               // +0xd4 MessageProc sets one per VfC8 entry
    uint8_t m_padda[2];
    IKSerializable* m_apMessageOuts[1];          // +0xdc
    IKSerializable* m_pTextE0;                   // +0xe0 CKLocTextAccessor (file key 0xe46): the pages' titles (widget slots 0, 3, 4)
    IKSerializable* m_pTextE4;                   // +0xe4 CKLocTextAccessor: the pages' texts for widget slot 1
    IKSerializable* m_pTextE8;                   // +0xe8 CKLocTextAccessor: the pages' texts for widget slot 2
    uint32_t m_ui32Page;                         // +0xec the page shown (0..31; OnStatePhase sets 0 on entering)
};
DOTD_ASSERT_SIZE(CKS08MenuHits, 0xf0);
DOTD_ASSERT_OFFSET(CKS08MenuHits, m_aWidgetSlots, 0x94);
DOTD_ASSERT_OFFSET(CKS08MenuHits, m_apMessageIns, 0xbc);
DOTD_ASSERT_OFFSET(CKS08MenuHits, m_abMessageInFlags, 0xd4);
DOTD_ASSERT_OFFSET(CKS08MenuHits, m_apMessageOuts, 0xdc);
DOTD_ASSERT_OFFSET(CKS08MenuHits, m_pTextE0, 0xe0);
DOTD_ASSERT_OFFSET(CKS08MenuHits, m_pTextE4, 0xe4);
DOTD_ASSERT_OFFSET(CKS08MenuHits, m_pTextE8, 0xe8);
