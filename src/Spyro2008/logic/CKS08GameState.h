// CKS08GameState.h - Spyro's game state (key 0x794c, vtable 0xb2b4f8, PS3 size 0x1e0). Original unit:
// CKS08GameState.cpp (0x5094c8-0x50f190). GAME.KP3 holds 19 (about 13 KB each, most of it the module
// lists of CKGameState). Not in XXL2. Its own part: counters (+0x90..+0x130), a list of references with
// a state byte each (+0xd8), twelve byte lists (+0x134) and single bytes.
//
// The fields are named after their offsets: what they count is not established yet (InitializeGameData
// sets +0x90..+0x9c to 300, like CKS08GameStructure's health and mana bases).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKGameState.h"
#include "k2000/util/TVector.h"

class CKS08GameState : public CKGameState {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x1e5)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c71c0
        return key == 0x794c || key == 0x32cc || key == 0x330c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKS08GameState)

    // +0xd8 entries: 8 bytes on the PS3. Names ours.
    struct ObjectState {
        IKSerializable* m_pObject;  // +0x00
        uint8_t m_ui8State;         // +0x04 K_GAME_MEMCARD; Load sets 0 on adding
        uint8_t m_pad05[3];
    };

    CKS08GameState();             // 0x0050b458 CKS08GameState_Construct
    ~CKS08GameState() override;   // vt+0x00 / +0x04  0x50e928 / 0x50e560
    void RemoveObjectEntryAt(uint32_t index);           // 0x005095e0 CKS08GameState_RemoveObjectEntryAt_maybe
    uint32_t AddObjectEntry(IKSerializable* object);    // 0x00509638 CKS08GameState_AddObjectEntry_maybe

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0050d050 CKS08GameState_Load
    // vt+0x28 0x0050bc78 CKS08GameState_Save (C2.8 save-menu): CKGameState's, then K_GAME_MEMCARD the mirror of Load's.
    int32_t Save(IKFile* file, int32_t type) override;
    void InitializeGameData() override;                 // vt+0x58 0x00509ac0 (Ghidra CKS08GameState_vf58)
    // vt+0x5c 0x509a98 InitLevelData, vt+0x80 0x509740, +0x88 0x509718, +0xa4 0x5097b8 and +0xac 0x509768
    // only call CKGameState's.
    void Destroy() override;              // vt+0x10 0x00509ea0 CKS08GameState_Destroy: CKGameState's (0x3dc38: IKGameObject's)
    void DestroyLevelData() override;     // vt+0x60 0x00509a70 CKS08GameState_ClearLevelData: CKGameState's
    // vt+0x64 0x00509808 CKS08GameState_ClearGameData_maybe: CKGameState's, then the +0xd8 list and the twelve byte
    // lists freed and emptied.
    void DestroyGameData() override;
    // vt+0x6c 0x0050a710 CKS08GameState_ResetStateFlags_maybe: CKGameState's, then the counters back to their new-game
    // values (InitializeGameData's), the twelve byte lists' bytes cleared, the +0xe4 bytes 3, +0x1ca 1, the rest 0.
    void Vf6C() override;
    // vt+0x84 0x0050a2c8 CKS08GameState_vf84: the +0xd8 entries whose object's level (KBase1D0C +0x18) is the stage
    // removed leave the list (the last entry moves in), then CKGameState's.
    void RemoveGameStage(uint32_t index) override;
    void RemoveGameModule(uint32_t index) override;                            // vt+0x8c 0x005096f0: CKGameState's
    void WriteStageData(IKFile* file, int32_t type, uint32_t index) override;   // vt+0xa0 0x005097e0: CKGameState's
    void WriteModuleData(IKFile* file, int32_t type, uint32_t index) override;  // vt+0xa8 0x00509790: CKGameState's
    // vt+0xc8 0x0050a8e0 CKS08GameState_vfC8 / vt+0xcc 0x0050a930 CKS08GameState_vfCC: every +0xd8 entry's object
    // (a CKS08GameLevelCollectible) gets its collected byte (+0x1c) from the entry's state / cleared, from the last
    // entry down. Names ours.
    virtual void ApplyCollectibleStates();
    virtual void ClearCollectibleStates();
    virtual void VfD0() {}  // vt+0xd0 0x00509520 CKS08GameState_vfD0 (empty)
    // C1.6 gm: the state and the game structure (Spyro's counters, the collectibles, the unlock bytes).
    void ApplyToStructure() override;                     // vt+0x70 0x0050a9f0 (Ghidra CKS08GameState_ApplyToGame_maybe)
    void CopyFromStructure() override;                    // vt+0x78 0x0050afc8 (Ghidra CKS08GameState_CaptureFromGame_maybe)
    void CopyFromState(const CKGameState* other) override;  // vt+0x7c 0x0050a388 (Ghidra CKS08GameState_CopyFrom_maybe)
    uint8_t SavesSpawnPoint() override;                   // vt+0xc0 0x0050af70: the game manager's vt+0xc4 == 0
    uint8_t RestoresSpawnPoint() override { return 1; }   // vt+0xc4 0x00509518

    uint32_t m_aUnk90[8];         // +0x90 type-8 block and K_GAME_MEMCARD; InitializeGameData: 300 x4, 0 x4
    uint32_t m_adwSpyroElementXp[5];         // +0xb0 one 20-byte read, five swapped words
    uint32_t m_adwCynderElementXp[5];         // +0xc4 the same
    TVector<ObjectState, 8> m_vObjectStates;  // +0xd8 type-8 block (references); level part adds new ones
    uint8_t m_abEquippedArmor[2][3];       // +0xe4 K_GAME_MEMCARD (each triple from its last byte); InitializeGameData: 3
    uint8_t m_bCynderArmorMeshHidden;              // +0xea K_GAME_MEMCARD
    uint8_t m_bSpyroArmorMeshHidden;              // +0xeb K_GAME_MEMCARD
    uint32_t m_adwEnemyKills[2];         // +0xec K_GAME_MEMCARD
    uint32_t m_adwBestCombo[2];         // +0xf4 K_GAME_MEMCARD
    uint32_t m_adwSpyroElementManaSpent[5];         // +0xfc K_GAME_MEMCARD
    uint32_t m_adwCynderElementManaSpent[5];        // +0x110 K_GAME_MEMCARD
    float m_afUnk124[3];          // +0x124 K_GAME_MEMCARD (Ghidra flUnk124..12c)
    uint32_t m_fPlayer1PlayTime;            // +0x130 K_GAME_MEMCARD
    TVector<uint8_t, 8> m_avObjectiveStates[12];  // +0x134 type-8 block (sized, then read byte by byte)
    uint8_t m_abScriptCounters[6];         // +0x1c4 type-8 block and K_GAME_MEMCARD
    uint8_t m_aUnk1CA[19];        // +0x1ca K_GAME_MEMCARD; InitializeGameData: 1, then 0 x18
    uint8_t m_pad1dd[3];
};
DOTD_ASSERT_SIZE(CKS08GameState::ObjectState, 0x8);
DOTD_ASSERT_SIZE(CKS08GameState, 0x1e0);
DOTD_ASSERT_OFFSET(CKS08GameState, m_aUnk90, 0x90);
DOTD_ASSERT_OFFSET(CKS08GameState, m_adwSpyroElementXp, 0xb0);
DOTD_ASSERT_OFFSET(CKS08GameState, m_adwCynderElementXp, 0xc4);
DOTD_ASSERT_OFFSET(CKS08GameState, m_vObjectStates, 0xd8);
DOTD_ASSERT_OFFSET(CKS08GameState, m_abEquippedArmor, 0xe4);
DOTD_ASSERT_OFFSET(CKS08GameState, m_bCynderArmorMeshHidden, 0xea);
DOTD_ASSERT_OFFSET(CKS08GameState, m_adwEnemyKills, 0xec);
DOTD_ASSERT_OFFSET(CKS08GameState, m_adwSpyroElementManaSpent, 0xfc);
DOTD_ASSERT_OFFSET(CKS08GameState, m_adwCynderElementManaSpent, 0x110);
DOTD_ASSERT_OFFSET(CKS08GameState, m_afUnk124, 0x124);
DOTD_ASSERT_OFFSET(CKS08GameState, m_fPlayer1PlayTime, 0x130);
DOTD_ASSERT_OFFSET(CKS08GameState, m_avObjectiveStates, 0x134);
DOTD_ASSERT_OFFSET(CKS08GameState, m_abScriptCounters, 0x1c4);
DOTD_ASSERT_OFFSET(CKS08GameState, m_aUnk1CA, 0x1ca);

// 0x0050f288 AddDragonPlayTime_maybe / 0x0050f2a8 AddPlayerSlotPlayTime_maybe (CKS08GameState.cpp): the play time
// of dragon `index` (+0x144) / of player slot `index` (+0x14c) in the game structure (CKS08GameStructure) grows by `dt`.
void AddDragonPlayTime(IKSerializable* structure, uint32_t index, float dt);
// 0x0050f238 AddElementManaSpent_maybe (CKS08GameState.cpp): the mana dragon `dragon` (0 Spyro, else Cynder) spent on
// element `element` (Spyro +0x11c, Cynder +0x130, a word each) grows by `amount`.
void AddElementManaSpent(IKSerializable* structure, uint32_t dragon, uint32_t element, uint32_t amount);
void AddPlayerSlotPlayTime(IKSerializable* structure, uint32_t index, float dt);
