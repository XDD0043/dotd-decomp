// CKS08GameLevelCollectible.h - a collectible of a level (key 0xa8cc, vtable 0xb2aef8, PS3 size 0x24;
// GAME.KP3 holds 165, named like "L110S01/XP Toit du S01 - 03"). Original units:
// CKS08GameLevelCollectible.cpp (0x433f8-0x43480) and CKS08GameLevelCollectible_2.cpp
// (0x4f5d48-0x4f6648). Not in XXL2.
#pragma once
#include <cstdint>

#include "Spyro2008/logic/KBase1D0C.h"
#include "k2000/core/Layout.h"

struct IKInfo;

class CKS08GameLevelCollectible : public KBase1D0C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2a3)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c6bf0
        return key == 0xa8cc || key == 0x1d0c || key == 0x330c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKS08GameLevelCollectible)

    CKS08GameLevelCollectible() {}  // CKS08GameLevelCollectible_Create 0x4f6168: KBase1D0C's, then the vtable
    ~CKS08GameLevelCollectible() override {}  // vt+0x00 / +0x04  0x9c6c48 / 0x9c6c68

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004f64f8 CKS08GameLevelCollectible_Load
    void InitializeGameData() override;                 // vt+0x58 0x004f6398
    // vt+0x5c 0x4f5ff8 InitLevelData only calls the base's; vt+0x54 0x43160 and vt+0x70 0x431d0 are KBase1D0C's.
    // vt+0x1c 0x004f6268 CKS08GameLevelCollectible_MessageProc: 0x20a (the data a byte) collects it (ApplyCollect) or
    // forgets it (+0x1c = 0), answering 0; the base's answer otherwise (KBase1D0C: 1).
    int32_t MessageProc(uint16_t message, void* data) override;
    void SetDefaultState(int32_t) override { m_bCollected = 0; }  // vt+0x38 0x004f5d98 CKS08GameLevelCollectible_SetDefaultState
    // vt+0x40 0x004f63e8 CKS08GameLevelCollectible_GetInfo: value 0x14 (a byte): collected (+0x1c; 0x9c6c40).
    int32_t GetInfo(IKInfo* info, int32_t request) override;
    void Destroy() override { KBase1D0C::Destroy(); }                  // vt+0x10 0x004f6098
    void RecursiveRegistration(int32_t type) override { KBase1D0C::RecursiveRegistration(type); }  // vt+0x24 0x004f6070
    int32_t Save(IKFile* file, int32_t type) override { return KBase1D0C::Save(file, type); }  // vt+0x28 0x004f6048
    int32_t PostLoad(int32_t type) override { return KBase1D0C::PostLoad(type); }  // vt+0x30 0x004f6020
    void DestroyLevelData() override { KBase1D0C::DestroyLevelData(); }  // vt+0x60 0x004f5fd0
    void DestroyGameData() override { KBase1D0C::DestroyGameData(); }    // vt+0x64 0x004f5fa8
    void ApplyGameStateToLevel() override {}                              // vt+0x68 0x004f5da8 (empty)
    // 0x004f5db0 CKS08GameLevelCollectible_ApplyCollect_maybe: collected (+0x1c = 1), its category's count invalidated,
    // the pickup music; by category (+0x1d): 0 the item message (+0x1e, +0x20, +0x1f) and, for the first one, the
    // info page; 4 a message; 1 the stat displays and the health shards; 2 the stat displays and the mana shards.
    void ApplyCollect();

    uint8_t m_bCollected;   // +0x1c InitializeGameData: 0
    uint8_t m_ui8Category;   // +0x1d type-8 block; InitializeGameData: 1
    uint8_t m_ui8DragonIndex;   // +0x1e type-8 block
    uint8_t m_ui8ArmorSet;   // +0x1f type-8 block
    uint8_t m_ui8ArmorSlot;   // +0x20 type-8 block, last
    uint8_t m_pad21[3];
};
DOTD_ASSERT_SIZE(CKS08GameLevelCollectible, 0x24);
DOTD_ASSERT_OFFSET(CKS08GameLevelCollectible, m_bCollected, 0x1c);
DOTD_ASSERT_OFFSET(CKS08GameLevelCollectible, m_ui8ArmorSlot, 0x20);
