// CKS08MenuSelectSlot.h - the "Menu Select Slot" screen (key 0x824c, vtable 0xb2d2b8, size 0x120 from 0x563c40 CKS08MenuSelectSlot_Create). DotD only.
// Original unit: CKS08MenuSelectSlot.cpp (0x5625a0-0x564680).
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKMenuBase114c.h"
#include "k2000/core/Layout.h"

class CKS08MenuSelectSlot : public CKMenuBase114c {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x209)
    DOTD_DECLARE_FACTORIES(CKS08MenuSelectSlot)

    CKS08MenuSelectSlot() {}  // 0x563c40 CKS08MenuSelectSlot_Create: the CKMenuBase114c part only
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ca2d8
        return key == 0x824c || key == 0x114c || key == 0x730c || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;                                   // vt+0x2c 0x563d28 CKS08MenuSelectSlot_Load
    uint32_t GetWidgetSlotCount() override { return 11; }                                // vt+0x68 0x9ca338
    WidgetSlot* GetWidgetSlots() override { return m_aWidgetSlots; }                     // vt+0x6c 0x9ca340
    const char* GetMenuName() override { return "Menu Select Slot"; }                    // vt+0xb8 0x9ca328
    uint8_t VfBC() override { return 1; }                                                // vt+0xbc 0x9ca378
    IKSerializable** VfC0() override { return m_apMessageOuts; }                         // vt+0xc0 0x9ca380
    uint8_t VfC4() override { return 6; }                                                // vt+0xc4 0x9ca350
    IKSerializable** VfC8() override { return m_apMessageIns; }                          // vt+0xc8 0x9ca358
    uint8_t* VfCC() override { return m_abMessageInFlags; }                              // vt+0xcc 0x9ca368
    int32_t GetMenuId() override { return 0x12; }                                        // vt+0xe0 0x9ca330

    WidgetSlot m_aWidgetSlots[11];               // +0x94
    IKSerializable* m_apMessageIns[6];           // +0xec
    uint8_t m_abMessageInFlags[6];               // +0x104 MessageProc sets one per VfC8 entry
    uint8_t m_pad10a[2];
    IKSerializable* m_apMessageOuts[1];          // +0x10c
    uint32_t m_unk110[3];                        // +0x110
    IKSerializable* m_pText;                     // +0x11c CKLocTextAccessor (file key 0xe46)
};
DOTD_ASSERT_SIZE(CKS08MenuSelectSlot, 0x120);
DOTD_ASSERT_OFFSET(CKS08MenuSelectSlot, m_aWidgetSlots, 0x94);
DOTD_ASSERT_OFFSET(CKS08MenuSelectSlot, m_apMessageIns, 0xec);
DOTD_ASSERT_OFFSET(CKS08MenuSelectSlot, m_abMessageInFlags, 0x104);
DOTD_ASSERT_OFFSET(CKS08MenuSelectSlot, m_apMessageOuts, 0x10c);
DOTD_ASSERT_OFFSET(CKS08MenuSelectSlot, m_pText, 0x11c);
