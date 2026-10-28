// CKS08GameModule.h - Spyro's module (key 0x78cc, vtable 0xb2b3c8, PS3 size 0x34). Original unit:
// CKS08GameModule.cpp (0x507d58-0x5086f0). GAME.KP3 holds 438. Not in XXL2 (XXL2's CKA2GameModule adds
// one Bool, m_bCountForProgress, like the byte here; the read order cannot tell, so the name stays ours).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKGameModule.h"

class CKS08GameModule : public CKGameModule {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x1e3)
    DOTD_DECLARE_FACTORIES(CKS08GameModule)

    CKS08GameModule() {}            // 0x00508170 CKS08GameModule_Construct: CKGameModule's, then the vtable
    ~CKS08GameModule() override {}  // vt+0x00 / +0x04  0x5085b0 / 0x5086a0

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00507e30 CKS08GameModule_Load
    void SetActivated(uint8_t activated) override;      // vt+0x70 0x005080c8
    uint8_t CanSetFlag2() override;                     // vt+0x90 0x00508358
    // C1.6 gm: the game state filters. Set (+0x30), the activated bit is always saved and is restored only
    // outside the chapter mode (game manager vt+0xc4 == 0); clear, the reverse. Flag 2 always follows the
    // chapter mode.
    uint32_t IsActivated() override;          // vt+0x74 0x00507da8 CKS08GameModule_vf74 (bit 1, as CKGameModule's)
    uint8_t CanSaveActivated() override;      // vt+0x78 0x00508430 CKS08GameModule_vf78
    uint8_t CanRestoreActivated() override;   // vt+0x7c 0x00508530 CKS08GameModule_vf7C
    uint8_t CanRestoreFlag2() override;       // vt+0x88 0x005083d8 CKS08GameModule_vf88
    uint8_t CanSaveFlag2() override;          // vt+0x8c 0x005084b0 CKS08GameModule_vf8C
    void ApplyDone() override;                // vt+0x98 0x00507e08 CKS08GameModule_vf98 (CKGameModule's)

    // +0x30 type-8 block, after CKGameModule's part; set, CanSetFlag2 is 1 without asking the game
    // manager. Name ours.
    uint8_t m_unk30;
};
DOTD_ASSERT_SIZE(CKS08GameModule, 0x34);
DOTD_ASSERT_OFFSET(CKS08GameModule, m_unk30, 0x30);
