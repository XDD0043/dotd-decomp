// CKMenuMessageBox.h - the "Menu Message Box" screen (key 0x734c, vtable 0xb2ba68, size 0xe4 from 0x52d5e0 CKMenuMessageBox_Create). DotD only.
// Original unit: CKMenuMessageBox.cpp (0x52c700-0x52e458).
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKMenuBase114c.h"
#include "k2000/core/Layout.h"

class CKMenuMessageBox : public CKMenuBase114c {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x1cd)
    DOTD_DECLARE_FACTORIES(CKMenuMessageBox)

    CKMenuMessageBox() { m_iUnkd4 = -1; }  // 0x52d5e0 CKMenuMessageBox_Create / 0x52c750 _Construct: then +0xd4 = -1
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c86b8
        return key == 0x734c || key == 0x114c || key == 0x730c || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;                                   // vt+0x2c 0x52c9e8 CKMenuMessageBox_Load
    uint32_t GetWidgetSlotCount() override { return 1; }                                 // vt+0x68 0x9c8710
    WidgetSlot* GetWidgetSlots() override { return m_aWidgetSlots; }                     // vt+0x6c 0x9c8718
    const char* GetMenuName() override { return "Menu Message Box"; }                    // vt+0xb8 0x9c8700
    uint8_t VfBC() override { return 6; }                                                // vt+0xbc 0x9c8750
    IKSerializable** VfC0() override { return m_apMessageOuts; }                         // vt+0xc0 0x9c8758
    uint8_t VfC4() override { return 6; }                                                // vt+0xc4 0x9c8728
    IKSerializable** VfC8() override { return m_apMessageIns; }                          // vt+0xc8 0x9c8730
    uint8_t* VfCC() override { return m_abMessageInFlags; }                              // vt+0xcc 0x9c8740
    int32_t GetMenuId() override { return 0x0; }                                         // vt+0xe0 0x9c8708
    void OnItemState(uint8_t item, uint8_t state, uint8_t arg) override;                // vt+0xe8 0x52cc28
    // 0x0052d3e0 CFlashMessageBox2d_HideMessage_maybe: the box's interface marked kNeverRender and its hot
    // spots hidden; no message shown (+0xd4 = -1).
    void HideMessage();

    WidgetSlot m_aWidgetSlots[1];                // +0x94
    IKSerializable* m_apMessageIns[6];           // +0x9c
    uint8_t m_abMessageInFlags[6];               // +0xb4 MessageProc sets one per VfC8 entry
    uint8_t m_padba[2];
    IKSerializable* m_apMessageOuts[6];          // +0xbc
    int32_t m_iUnkd4;                            // +0xd4 the constructor sets -1
    uint8_t m_bBlockAnswer;                      // +0xd8 set on the frame a message opens: no answer taken (vfE8)
    uint8_t m_padd9[3];
    float m_fUnkdc;                              // +0xdc read by the Load (1.0 in LVL000)
    float m_fTimer;                              // +0xe0 the message timeout, counted down (UpdateTimer)
};
DOTD_ASSERT_SIZE(CKMenuMessageBox, 0xe4);
DOTD_ASSERT_OFFSET(CKMenuMessageBox, m_aWidgetSlots, 0x94);
DOTD_ASSERT_OFFSET(CKMenuMessageBox, m_apMessageIns, 0x9c);
DOTD_ASSERT_OFFSET(CKMenuMessageBox, m_abMessageInFlags, 0xb4);
DOTD_ASSERT_OFFSET(CKMenuMessageBox, m_apMessageOuts, 0xbc);
DOTD_ASSERT_OFFSET(CKMenuMessageBox, m_iUnkd4, 0xd4);
DOTD_ASSERT_OFFSET(CKMenuMessageBox, m_bBlockAnswer, 0xd8);
DOTD_ASSERT_OFFSET(CKMenuMessageBox, m_fUnkdc, 0xdc);
DOTD_ASSERT_OFFSET(CKMenuMessageBox, m_fTimer, 0xe0);
