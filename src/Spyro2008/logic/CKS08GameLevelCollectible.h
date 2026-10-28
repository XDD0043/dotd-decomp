// CKS08GameLevelCollectible.h - a collectible of a level (key 0xa8cc, vtable 0xb2aef8, PS3 size 0x24;
// GAME.KP3 holds 165, named like "L110S01/XP Toit du S01 - 03"). Original units:
// CKS08GameLevelCollectible.cpp (0x433f8-0x43480) and CKS08GameLevelCollectible_2.cpp
// (0x4f5d48-0x4f6648). Not in XXL2.
#pragma once
#include <cstdint>

#include "Spyro2008/logic/KBase1D0C.h"
#include "k2000/core/Layout.h"

class CKS08GameLevelCollectible : public KBase1D0C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2a3)
    DOTD_DECLARE_FACTORIES(CKS08GameLevelCollectible)

    CKS08GameLevelCollectible() {}  // CKS08GameLevelCollectible_Create 0x4f6168: KBase1D0C's, then the vtable
    ~CKS08GameLevelCollectible() override {}  // vt+0x00 / +0x04  0x9c6c48 / 0x9c6c68

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004f64f8 CKS08GameLevelCollectible_Load
    void InitializeGameData() override;                 // vt+0x58 0x004f6398
    // vt+0x5c 0x4f5ff8 InitLevelData only calls the base's. Not ported: vt+0x1c 0x4f6268, +0x38 0x4f5d98,
    // +0x40 0x4f63e8, +0x54 0x43160, +0x60, +0x64, +0x68, +0x70 (STUB(C1.6)).

    uint8_t m_unk1c;   // +0x1c InitializeGameData: 0
    uint8_t m_unk1d;   // +0x1d type-8 block; InitializeGameData: 1
    uint8_t m_unk1e;   // +0x1e type-8 block
    uint8_t m_unk1f;   // +0x1f type-8 block
    uint8_t m_unk20;   // +0x20 type-8 block, last
    uint8_t m_pad21[3];
};
DOTD_ASSERT_SIZE(CKS08GameLevelCollectible, 0x24);
DOTD_ASSERT_OFFSET(CKS08GameLevelCollectible, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKS08GameLevelCollectible, m_unk20, 0x20);
