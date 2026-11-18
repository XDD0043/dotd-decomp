// CKS08InGameInterfaceProtect.h - the protection HUD ("Interface InGame Protection") (key 0xa38c, vtable 0xb2bf20, size 0x100 from 0x53c900 CKS08InGameInterfaceProtect_Create). DotD only.
// Original unit: CKS08InGameInterfaceProtect.cpp (0x53c360-0x53d330).
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKMenuBase114c.h"
#include "k2000/core/Layout.h"

class CKS08InGameInterfaceProtect : public CKMenuBase114c {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x28e)
    DOTD_DECLARE_FACTORIES(CKS08InGameInterfaceProtect)

    // 0x53c900 CKS08InGameInterfaceProtect_Create: the CKMenuBase114c part only. +0xe0 and +0xf0 are read (the vt+0xdc
    // update) before any write: the original reads its fresh heap's 0 (as CKS08InGameInterfaceBoss).
    CKS08InGameInterfaceProtect() {
        m_baFlagsE0 = 0;
        m_fTime = 0.0f;
    }
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c9490
        return key == 0xa38c || key == 0x114c || key == 0x730c || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;                                   // vt+0x2c 0x53c9e8 CKS08InGameInterfaceProtect_Load
    // vt+0xdc 0x0053cc28 CKS08InGameInterfaceProtect_OnMenuState_maybe: the timed panel (bit 0 of +0xe0 for +0xec seconds,
    // then message out 2), the gauge value +0xf4 / +0xfc and marker +0xf8 / +0xfc set when they changed, ticked onto
    // slots 0-2.
    uint8_t OnMenuState(int32_t phase, uint8_t other) override;
    void ResetWidgets() override;  // vt+0x98 0x0053c520 CKS08InGameInterfaceProtect_ResetWidgets_maybe
    // The gauge syncs of 0x53c458 / 0x53c4b8 / 0x53cb90 (no caller in the original: their descriptors are referenced
    // nowhere; the vt+0xdc update inlines the same code).
    void SyncGaugeMarker();  // 0x0053c458 CKS08InGameInterfaceProtect_SyncGaugeMarker_maybe
    void SyncGaugeValue();   // 0x0053c4b8 CKS08InGameInterfaceProtect_SyncGaugeValue_maybe
    void UpdateGauge();      // 0x0053cb90 CKS08InGameInterfaceProtect_UpdateGauge_maybe
    uint32_t GetWidgetSlotCount() override { return 3; }                                 // vt+0x68 0x9c9530
    WidgetSlot* GetWidgetSlots() override { return m_aWidgetSlots; }                     // vt+0x6c 0x9c9538
    uint8_t Vf84() override { return 0; }                                                // vt+0x84 0x9c9548
    const char* GetMenuName() override { return "Interface InGame Protection"; }         // vt+0xb8 0x9c94e0
    uint8_t VfBC() override { return 3; }                                                // vt+0xbc 0x9c94f0
    IKSerializable** VfC0() override { return m_apMessageOuts; }                         // vt+0xc0 0x9c94f8
    uint8_t VfC4() override { return 8; }                                                // vt+0xc4 0x9c9508
    IKSerializable** VfC8() override { return m_apMessageIns; }                          // vt+0xc8 0x9c9510
    uint8_t* VfCC() override { return m_abMessageInFlags; }                              // vt+0xcc 0x9c9520
    int32_t GetMenuId() override { return 0x0; }                                         // vt+0xe0 0x9c94e8

    WidgetSlot m_aWidgetSlots[3];                // +0x94
    IKSerializable* m_apMessageIns[8];           // +0xac
    uint8_t m_abMessageInFlags[8];               // +0xcc MessageProc sets one per VfC8 entry
    IKSerializable* m_apMessageOuts[3];          // +0xd4
    uint8_t m_baFlagsE0;                         // +0xe0 bit 0: the panel is timed (cleared on enter and after +0xec seconds)
    uint8_t m_padE1[3];
    IKSerializable* m_pGauge;                    // +0xe4 CKSuperGaugeCpnt (file key 0xa94c)
    IKSerializable* m_pGaugeUpdater;             // +0xe8 CKSuperGaugeCpntUpdater (file key 0x14c6)
    float m_fUnkec;                              // +0xec read by the Load (15.0 in LVL000)
    float m_fTime;                               // +0xf0 ResetWidgets_maybe (vt+0x98) sets 0, the vt+0xdc update adds the frame time
    float m_fUnkf4;                              // +0xf4 the Load sets 5.0
    float m_fUnkf8;                              // +0xf8 the Load sets 8.0
    float m_fUnkfc;                              // +0xfc the Load sets 10.0
};
DOTD_ASSERT_SIZE(CKS08InGameInterfaceProtect, 0x100);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceProtect, m_aWidgetSlots, 0x94);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceProtect, m_apMessageIns, 0xac);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceProtect, m_abMessageInFlags, 0xcc);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceProtect, m_apMessageOuts, 0xd4);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceProtect, m_pGauge, 0xe4);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceProtect, m_pGaugeUpdater, 0xe8);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceProtect, m_fUnkec, 0xec);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceProtect, m_fUnkf4, 0xf4);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceProtect, m_fUnkf8, 0xf8);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceProtect, m_fUnkfc, 0xfc);
