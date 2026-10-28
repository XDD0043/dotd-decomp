// CKS08MenuStartPlayer.h - the "Menu Start Nb Player" screen (key 0xb0cc, vtable 0xb2d3c0, size 0xb8 from 0x564ce0 CKS08MenuStartPlayer_Create). DotD only.
// Original unit: CKS08MenuStartPlayer.cpp (0x564680-0x565218).
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKMenuBase114c.h"
#include "k2000/core/Layout.h"

class CKS08MenuStartPlayer : public CKMenuBase114c {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2c3)
    DOTD_DECLARE_FACTORIES(CKS08MenuStartPlayer)

    CKS08MenuStartPlayer() {}  // 0x564ce0 CKS08MenuStartPlayer_Create: the CKMenuBase114c part only
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ca3a8
        return key == 0xb0cc || key == 0x114c || key == 0x730c || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;                                   // vt+0x2c 0x5647c0 CKS08MenuStartPlayer_Load
    const char* GetMenuName() override { return "Menu Start Nb Player"; }                // vt+0xb8 0x9ca3f8
    uint8_t VfBC() override { return 1; }                                                // vt+0xbc 0x9ca430
    IKSerializable** VfC0() override { return m_apMessageOuts; }                         // vt+0xc0 0x9ca438
    uint8_t VfC4() override { return 6; }                                                // vt+0xc4 0x9ca408
    IKSerializable** VfC8() override { return m_apMessageIns; }                          // vt+0xc8 0x9ca410
    uint8_t* VfCC() override { return m_abMessageInFlags; }                              // vt+0xcc 0x9ca420
    uint8_t OnMenuState(int32_t phase, uint8_t other) override;                          // vt+0xdc 0x00564778 CKS08MenuStartPlayer_vfDC
    int32_t GetMenuId() override { return 0x23; }                                        // vt+0xe0 0x9ca400
    // vt+0xe8 0x005649a8 CKS08MenuStartPlayer_vfE8: items 0/1 validated: one/two players (+0x270) and the new
    // game started (vt+0x2e8); item 2 (back): the chapter menu (3) or the game menu (6).
    void OnItemState(uint8_t item, uint8_t state, uint8_t phase) override;
    uint8_t VfF0() override { return 1; }                                                // vt+0xf0 0x9ca448
    uint8_t VfF4() override { return 2; }                                                // vt+0xf4 0x9ca450 the back item

    IKSerializable* m_apMessageIns[6];           // +0x94
    uint8_t m_abMessageInFlags[6];               // +0xac MessageProc sets one per VfC8 entry
    uint8_t m_padb2[2];
    IKSerializable* m_apMessageOuts[1];          // +0xb4
};
DOTD_ASSERT_SIZE(CKS08MenuStartPlayer, 0xb8);
DOTD_ASSERT_OFFSET(CKS08MenuStartPlayer, m_apMessageIns, 0x94);
DOTD_ASSERT_OFFSET(CKS08MenuStartPlayer, m_abMessageInFlags, 0xac);
DOTD_ASSERT_OFFSET(CKS08MenuStartPlayer, m_apMessageOuts, 0xb4);
