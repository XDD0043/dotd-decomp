// CKS08InGameInterfaceBoss.h - the boss HUD ("Interface InGame Boss") (key 0xa3cc, vtable 0xb2bc08, size 0x100 from 0x533d90 CKS08InGameInterfaceBoss_Create). DotD only.
// Original unit: CKS08InGameInterfaceBoss.cpp (0x533848-0x5349a8).
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKMenuBase114c.h"
#include "k2000/core/Layout.h"

class CKS08InGameInterfaceBoss : public CKMenuBase114c {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x28f)
    DOTD_DECLARE_FACTORIES(CKS08InGameInterfaceBoss)

    CKS08InGameInterfaceBoss() {}  // 0x533d90 CKS08InGameInterfaceBoss_Create: the CKMenuBase114c part only
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c9240
        return key == 0xa3cc || key == 0x114c || key == 0x730c || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;                                   // vt+0x2c 0x5341f0 CKS08InGameInterfaceBoss_Load
    uint32_t GetWidgetSlotCount() override { return 3; }                                 // vt+0x68 0x9c92e0
    WidgetSlot* GetWidgetSlots() override { return m_aWidgetSlots; }                     // vt+0x6c 0x9c92e8
    uint8_t Vf84() override { return 0; }                                                // vt+0x84 0x9c92f8
    const char* GetMenuName() override { return "Interface InGame Boss"; }               // vt+0xb8 0x9c9290
    uint8_t VfBC() override { return 3; }                                                // vt+0xbc 0x9c92a0
    IKSerializable** VfC0() override { return m_apMessageOuts; }                         // vt+0xc0 0x9c92a8
    uint8_t VfC4() override { return 8; }                                                // vt+0xc4 0x9c92b8
    IKSerializable** VfC8() override { return m_apMessageIns; }                          // vt+0xc8 0x9c92c0
    uint8_t* VfCC() override { return m_abMessageInFlags; }                              // vt+0xcc 0x9c92d0
    int32_t GetMenuId() override { return 0x0; }                                         // vt+0xe0 0x9c9298

    WidgetSlot m_aWidgetSlots[3];                // +0x94
    IKSerializable* m_apMessageIns[8];           // +0xac
    uint8_t m_abMessageInFlags[8];               // +0xcc MessageProc sets one per VfC8 entry
    IKSerializable* m_apMessageOuts[3];          // +0xd4
    uint8_t m_baFlagsE0;                         // +0xe0 bit 0 cleared by the game manager's boss messages 0x2650 / 0x2652
    uint8_t m_padE1[3];
    IKSerializable* m_pGauge;                    // +0xe4 CKSuperGaugeCpnt (file key 0xa94c)
    IKSerializable* m_pGaugeUpdater;             // +0xe8 CKSuperGaugeCpntUpdater (file key 0x14c6)
    float m_fUnkec;                              // +0xec read by the Load (8.0 in LVL000)
    float m_fTime;                               // +0xf0 ResetWidgets_maybe (vt+0x98) sets 0, the vt+0xdc update adds the frame time
    float m_fUnkf4;                              // +0xf4 the Load sets 5.0
    float m_fUnkf8;                              // +0xf8 the Load sets 8.0
    float m_fUnkfc;                              // +0xfc the Load sets 10.0
};
DOTD_ASSERT_SIZE(CKS08InGameInterfaceBoss, 0x100);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceBoss, m_aWidgetSlots, 0x94);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceBoss, m_apMessageIns, 0xac);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceBoss, m_abMessageInFlags, 0xcc);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceBoss, m_apMessageOuts, 0xd4);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceBoss, m_pGauge, 0xe4);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceBoss, m_pGaugeUpdater, 0xe8);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceBoss, m_fUnkec, 0xec);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceBoss, m_fUnkf4, 0xf4);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceBoss, m_fUnkf8, 0xf8);
DOTD_ASSERT_OFFSET(CKS08InGameInterfaceBoss, m_fUnkfc, 0xfc);
