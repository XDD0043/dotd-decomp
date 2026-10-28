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
    uint32_t GetWidgetSlotCount() override { return 5; }                                 // vt+0x68 0x9c9b68
    WidgetSlot* GetWidgetSlots() override { return m_aWidgetSlots; }                     // vt+0x6c 0x9c9b70
    const char* GetMenuName() override { return "Menu Hits"; }                           // vt+0xb8 0x9c9b18
    uint8_t VfBC() override { return 1; }                                                // vt+0xbc 0x9c9b50
    IKSerializable** VfC0() override { return m_apMessageOuts; }                         // vt+0xc0 0x9c9b58
    uint8_t VfC4() override { return 6; }                                                // vt+0xc4 0x9c9b28
    IKSerializable** VfC8() override { return m_apMessageIns; }                          // vt+0xc8 0x9c9b30
    uint8_t* VfCC() override { return m_abMessageInFlags; }                              // vt+0xcc 0x9c9b40
    int32_t GetMenuId() override { return 0x7; }                                         // vt+0xe0 0x9c9b20

    WidgetSlot m_aWidgetSlots[5];                // +0x94
    IKSerializable* m_apMessageIns[6];           // +0xbc
    uint8_t m_abMessageInFlags[6];               // +0xd4 MessageProc sets one per VfC8 entry
    uint8_t m_padda[2];
    IKSerializable* m_apMessageOuts[1];          // +0xdc
    IKSerializable* m_pTextE0;                   // +0xe0 CKLocTextAccessor (file key 0xe46)
    IKSerializable* m_pTextE4;                   // +0xe4 CKLocTextAccessor
    IKSerializable* m_pTextE8;                   // +0xe8 CKLocTextAccessor
    uint32_t m_unkec;                            // +0xec
};
DOTD_ASSERT_SIZE(CKS08MenuHits, 0xf0);
DOTD_ASSERT_OFFSET(CKS08MenuHits, m_aWidgetSlots, 0x94);
DOTD_ASSERT_OFFSET(CKS08MenuHits, m_apMessageIns, 0xbc);
DOTD_ASSERT_OFFSET(CKS08MenuHits, m_abMessageInFlags, 0xd4);
DOTD_ASSERT_OFFSET(CKS08MenuHits, m_apMessageOuts, 0xdc);
DOTD_ASSERT_OFFSET(CKS08MenuHits, m_pTextE0, 0xe0);
DOTD_ASSERT_OFFSET(CKS08MenuHits, m_pTextE4, 0xe4);
DOTD_ASSERT_OFFSET(CKS08MenuHits, m_pTextE8, 0xe8);
