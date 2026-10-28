// CKS08Player.h - Spyro's player (key 0x780c, vtable 0xb2ae70, PS3 size 0x14). Original unit:
// CKS08Player.cpp (0x4f5830-0x4f5d48). The game manager creates the 7 players (GetPlayerClassKey);
// GAME.KP3 loads them as globals (each: its game state). No fields of its own.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/IKPlayer.h"

class CKS08Player : public IKPlayer {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x1e0)
    DOTD_DECLARE_FACTORIES(CKS08Player)

    // The live constructor is inlined in CKS08Player_Create 0x4f5c40 / CreateArray 0x4f5b88
    // (CKS08Player_Construct 0x4f5880 is dead): IKPlayer's, then the vtable.
    CKS08Player() {}
    ~CKS08Player() override {}  // vt+0x00 / +0x04  0x4f5cc0 / 0x4f5d00

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004f5930 CKS08Player_Load
    void CopyPlayerGameData(IKPlayer* other) override;  // vt+0x50 0x004f5908 CKS08Player_vf50
    void InitializeNewGame() override;                  // vt+0x54 0x004f5c98 CKS08Player_vf54
    void CopyGameStructure() override;                  // vt+0x58 0x004f58e0 CKS08Player_vf58
    void Vf60() override {}                             // vt+0x60 0x4f58d8 (empty)
};
DOTD_ASSERT_SIZE(CKS08Player, 0x14);
