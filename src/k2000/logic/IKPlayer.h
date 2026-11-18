// IKPlayer.h - a player's game data (key 0x180c, vtable 0xb133b8, PS3 size 0x14; XXL2:
// K/KCore/Interfaces/IKPlayer.h, our earlier KBase180C). Its Load (IKPlayer_Load 0x1a290) sits in the
// CKDefaultPlayer unit (0x1a0d8-0x1a468). The game manager owns 7 players (CDefaultGameManager_InitImpl:
// CreateObjectArray of GetPlayerClassKey()); GAME.KP3 loads them as globals.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKGameState;

class IKPlayer : public IKSerializable {
public:
    // Inlined in every subclass constructor (CKS08Player_Create 0x4f5c40): +0x0c, +0x04, +0x08, as in
    // XXL2's (CreateCKDefaultPlayer); +0x10 is left as it is.
    IKPlayer() {
        m_pGameState = nullptr;
        m_baLevelSaved = 0;
        m_bUsed = 0;
    }
    ~IKPlayer() override {}  // vt+0x00 / +0x04  0x992898 / 0x992830

    int32_t GetClassType() override { return 0xc; }    // vt+0x14 0x9927d8
    int32_t GetClassID() override { return 0x60; }     // vt+0x18 0x9927e0
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0001a290 IKPlayer_Load
    int32_t GetSerializationFlags() override { return 0; }  // vt+0x34 0x9927e8

    // vt+0x50 / +0x54: pure in IKPlayer (XXL2 CopyPlayerGameData(IKPlayer*) / InitializeNewGame(); the PS3
    // passes the other player in r4: CKDefaultPlayer_vf50Impl 0x1a220).
    virtual void CopyPlayerGameData(IKPlayer* other) = 0;
    virtual void InitializeNewGame() = 0;
    // C1.6 gm: vt+0x58 0x0001a0d8 (Ghidra CKDefaultPlayer_vf58; IKPlayer's slot, XXL2 IKPlayer::
    // CopyGameStructure): the game state takes the game structure's progress (CKGameState vt+0x78).
    virtual void CopyGameStructure();
    // C1.6 gm: vt+0x60 0x9927f8 (empty; CKS08Player's 0x4f58d8 too). vt+0x5c, +0x64.. are not declared yet.
    virtual void Vf60() {}

    // C1.6 gm: CKDefaultPlayer's code (CKDefaultPlayer.cpp), which CKS08Player's slots call.
    // 0x0001a220 CKDefaultPlayer_vf50Impl: +0x04 and +0x10 copied, the game state copied (vt+0x7c).
    void CopyPlayerGameDataImpl(IKPlayer* other);
    // 0x0001a120 CKDefaultPlayer_vf54Impl: +0x09, +0x10, +0x04 and +0x08 cleared.
    void InitializeNewGameImpl();
    // C2.8 save-menu. 0x00019f98 CKDefaultPlayer_SaveImpl (CDefaultGameManager.cpp): K_GAME_MEMCARD writes the saved-level
    // bits and +0x10 (little-endian words) around the used byte (Load's mirror); 1.
    int32_t SaveImpl(IKFile* file, int32_t type);
    // 0x0001a140 CKDefaultPlayer_LevelResetImpl (CKDefaultPlayer.cpp; XXL2 RecursiveRegistration): types 0, 1 and 4
    // register the player, K_GAME_MEMCARD the player and its game state; 1.
    int32_t LevelResetImpl(int32_t type);

    uint32_t m_baLevelSaved;     // +0x04 CBitArray (XXL2); read in K_GAME_MEMCARD (mode 5)
    uint8_t m_bUsed;             // +0x08 Bool (XXL2); mode 5
    uint8_t m_unk09;             // +0x09 C1.6 gm: CKDefaultPlayer_vf54Impl clears it (not otherwise known)
    uint8_t m_pad0a[2];
    CKGameState* m_pGameState;   // +0x0c read in K_GAME_PLATEFORMS
    uint32_t m_unk10;            // +0x10 DotD only: mode 5, after m_bUsed (XXL2 reads m_pGameState there)
};
DOTD_ASSERT_SIZE(IKPlayer, 0x14);
DOTD_ASSERT_OFFSET(IKPlayer, m_baLevelSaved, 0x04);
DOTD_ASSERT_OFFSET(IKPlayer, m_bUsed, 0x08);
DOTD_ASSERT_OFFSET(IKPlayer, m_pGameState, 0x0c);
DOTD_ASSERT_OFFSET(IKPlayer, m_unk10, 0x10);
