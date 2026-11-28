// CKS08GameStructure.h - Spyro's game structure (key 0x798c, vtable 0xb2b5d8, PS3 size 0x254). Original
// unit: CKS08GameStructure.cpp (0x50f2c8-0x512290), with the head in CKS08GameState.cpp
// (0x50ece8-0x50f2c8). It derives from IKGameStructure directly (not CKDefaultGameStructure). The game
// manager creates the one instance (GetGameStructureClassKey); GAME.KP3 and the level files load it
// as a global. Not in XXL2 (CKA2GameStructure keeps the health and shield points here too).
//
// The Load reads the health and mana parameters (names from the Ghidra struct) and sizes twelve byte
// lists (one per level _maybe; their bytes are not in the file). Everything else is run-time state:
// declared as raw bytes until its users are ported.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKGameStructure.h"
#include "k2000/util/TVector.h"

class CKS08GameStructure : public IKGameStructure {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x1e6)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c7208
        return key == 0x798c || key == 0x3b4c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKS08GameStructure)

    CKS08GameStructure();             // 0x0050fdd8 CKS08GameStructure_Construct
    ~CKS08GameStructure() override;   // vt+0x00 / +0x04  0x510da0 / 0x511d70
    // 0x00510158 CKS08GameStructure_CountCollectedOfTypeInLevel_maybe: the uncollected items of `category` in main
    // level `mainLevel` (CKS08GameLevel::CountCollectedOfType of the last matching stage), 0 without one.
    uint32_t CountCollectedOfTypeInLevel(uint8_t category, int32_t mainLevel);

    void Destroy() override;                            // vt+0x10 0x0050fc58: IKGameStructure's
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005108d0 CKS08GameStructure_Load
    // 0x0050f2c8 CKS08GameStructure_ResetProgress_maybe: a new game's progress: health and mana from their
    // bases, the run-time counters cleared, the twelve byte lists zeroed, no spawn point, every unlock byte
    // (+0x23f..+0x250: the story-over flag +0x24a, the bonus items +0x24b..+0x250) cleared.
    void ResetProgress();
    // 0x00510640 CKS08GameStructure_RecordBestCombo_maybe: the best combo of dragon `dragon` (the word at
    // +0x114 + dragon * 4) raised to `combo`; the first combo above 149 hits shows the centre message 2 (once:
    // the byte +0x24d).
    void RecordBestCombo(int32_t dragon, uint32_t combo);
    // 0x0050f218 CKS08GameStructure_AddEnemyKill_maybe: the kill counter of `index` (the word at +0x10c + index * 4)
    // counts one more.
    void AddEnemyKill(uint32_t index) { SetRtWord(0x10c + index * 4, RtWord(0x10c + index * 4) + 1); }
    // The statistics screen's getters (CKS08GameState.cpp): 0x0050f0b8 the kills of `index`, 0x0050f0d0 the best combo
    // of dragon `index`, 0x0050f200 the play time of dragon `index`, 0x0050f0e8 the element dragon `dragon` used most.
    uint32_t GetEnemyKills(uint32_t index) const;
    uint32_t GetBestCombo(uint32_t index) const;
    float GetDragonPlayTime(uint32_t index) const;
    uint32_t GetMostUsedElement(int32_t dragon) const;
    // 0x005102e0 CKS08GameStructure_AreInfoPopupsEnabled_maybe: the game manager's edited option +0x05 (+0xf1).
    uint8_t AreInfoPopupsEnabled() const;
    // 0x005106c0 CKS08GameStructure_SetUnlockFlagByte_maybe: the unlock byte +0x23f + index; unlocking index 9 the
    // first time (+0x24f) shows the centre message 4.
    void SetUnlockFlagByte(int32_t index, uint8_t value);
    // 0x00510748 PlayerProgress_AddElementGems_maybe (C2.8 save-menu; the elements menu's gem transfer): `amount` added to
    // element `element`'s gems (kind 0: +0x8c, kind 1: +0xa0); element 0 reaching the game manager's cap (+0xc50 /
    // +0xc8c records) shows the centre message 0 / 1 once (+0x24b / +0x24c).
    void AddElementGems(uint8_t kind, uint8_t element, int32_t amount);
    // C1.6 gm: 0x0050ed60 CKS08GameStructure_SaveCheckpointSnapshot_maybe (in CKS08GameState.cpp): health,
    // mana and the counters (+0x4c..+0xb0) and the six bytes +0xb4..+0xb9 copied to their checkpoint copies
    // (+0x1f0..+0x234, +0x238..+0x23d).
    void SaveCheckpointSnapshot();
    // 0x0050eec0 CKS08GameStructure_RestoreCheckpointSnapshot_maybe (in CKS08GameState.cpp): the reverse.
    void RestoreCheckpointSnapshot();
    // C1.6 gm: vt+0x58 0x0050f958 / vt+0x5c 0x0050f980: IKGameStructure's (0x41448 / 0x41598).
    void Vf58() override;
    void ApplyGameStateToLevel() override;

    // C1.6 gm: the run-time words and bytes at their PS3 offsets in the raw ranges (+0x84..+0x153,
    // +0x1e4..+0x1eb, +0x1f0..+0x253), words in host order like the other members.
    uint32_t RtWord(uint32_t offset) const;
    void SetRtWord(uint32_t offset, uint32_t value);
    uint8_t& RtByte(uint32_t offset);
    // vt+0x0c 0x0050fa20 CKS08GameStructure_DestroyGame: IKGameStructure's (0x41888), then the twelve byte lists freed
    // and emptied.
    void DestroyGame() override;
    void RecursiveRegistration(int32_t type) override;  // vt+0x24 0x0050f9f8: IKGameStructure's (0x416c0)
    int32_t Save(IKFile* file, int32_t type) override;                // vt+0x28 0x0050f9d0: IKGameStructure's (0x416b8), 1
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x0050f9a8: IKGameStructure's (0x41aa0)
    // 0x0050f590 CKS08GameStructure_ShowCenterMessageOnce_maybe: the byte +0x24b + index = value; a non-zero value
    // that finds it clear first shows the game manager's centre message `index` (0x501860).
    void ShowCenterMessageOnce(uint32_t index, uint8_t value);
    // 0x0050f730 CKS08GameStructure_CountItemsByCategory_maybe / 0x0050ed40 ..._InvalidateCategoryCount_maybe: the
    // collectible counts per category over the levels, cached (CKS08GameStructure.cpp).
    uint32_t CountItemsByCategory(uint8_t category, uint8_t collected);
    // 0x0050f638 CKS08GameStructure_CountLevelItemsByCategory_maybe (C2.8 menus-load): the collectibles of `category` in the
    // main level `mainLevel` (the last stage whose Level_GetMainLevelIndex matches; 0 without one).
    uint32_t CountLevelItemsByCategory(uint8_t category, int32_t mainLevel, uint8_t collected);
    void InvalidateCategoryCount(uint8_t category);
    // 0x00510078 CKS08GameStructure_IsArmorPieceCollected_maybe (C2.8 live-fixes): armour `armor` (0..2) for `slot` (0..2)
    // of `dragon` collected in a stage (CKS08GameLevel_IsArmorPieceCollected_maybe 0x5073a0).
    uint8_t IsArmorPieceCollected(uint8_t dragon, uint8_t armor, uint8_t slot);

    // +0x45 / +0x46: the PS3 puts these first members in IKGameStructure's tail padding (see
    // IKGameStructure::m_aSubclassTail). Ghidra bHealthDivisor0 / bHealthDivisor1.
    uint8_t& HealthDivisor0() { return m_aSubclassTail[0]; }
    uint8_t& HealthDivisor1() { return m_aSubclassTail[1]; }

    uint32_t m_dwHealthMultiplier;  // +0x48 GAME.KP3 (live: 100)
    uint32_t m_dwSpyroHealth;               // +0x4c run time (live: 300)
    uint32_t m_dwHealthBase;        // +0x50 GAME.KP3 (live: 300)
    uint32_t m_dwCynderHealth;               // +0x54 run time
    uint32_t m_dwCynderStartHealth;               // +0x58 GAME.KP3 (Ghidra field_0x58)
    uint8_t m_bManaDivisor0;        // +0x5c GAME.KP3
    uint8_t m_bManaDivisor1;        // +0x5d GAME.KP3
    uint8_t m_pad5e[2];
    uint32_t m_dwManaMultiplier;    // +0x60 GAME.KP3
    uint32_t m_dwSpyroMana;               // +0x64 run time
    uint32_t m_dwManaBase;          // +0x68 GAME.KP3
    uint32_t m_dwCynderMana;               // +0x6c run time
    uint32_t m_dwCynderStartMana;               // +0x70 GAME.KP3 (Ghidra field_0x70)
    uint32_t m_dwSpyroFury;               // +0x74 run time
    uint32_t m_dwCynderFury;               // +0x78 run time
    uint32_t m_dwMaxTotalFury;               // +0x7c GAME.KP3, read after +0x80 (live: 4000)
    uint32_t m_dwSharedBonusPoints;               // +0x80 GAME.KP3
    uint8_t m_unk84[0xd0];          // +0x84..+0x153 run time
    TVector<uint8_t, 8> m_avObjectiveStates[12];  // +0x154 sized by GAME.KP3 (contents not in the file)
    uint8_t m_unk1e4[8];            // +0x1e4 run time
    uint32_t m_dwCheckpointMinHealth;              // +0x1ec GAME.KP3 (Ghidra field_0x1ec)
    uint8_t m_unk1f0[0x64];         // +0x1f0..+0x253 run time
};
DOTD_ASSERT_SIZE(CKS08GameStructure, 0x254);
DOTD_ASSERT_OFFSET(CKS08GameStructure, m_dwHealthMultiplier, 0x48);
DOTD_ASSERT_OFFSET(CKS08GameStructure, m_dwHealthBase, 0x50);
DOTD_ASSERT_OFFSET(CKS08GameStructure, m_dwCynderStartHealth, 0x58);
DOTD_ASSERT_OFFSET(CKS08GameStructure, m_bManaDivisor0, 0x5c);
DOTD_ASSERT_OFFSET(CKS08GameStructure, m_dwManaMultiplier, 0x60);
DOTD_ASSERT_OFFSET(CKS08GameStructure, m_dwManaBase, 0x68);
DOTD_ASSERT_OFFSET(CKS08GameStructure, m_dwCynderStartMana, 0x70);
DOTD_ASSERT_OFFSET(CKS08GameStructure, m_dwMaxTotalFury, 0x7c);
DOTD_ASSERT_OFFSET(CKS08GameStructure, m_dwSharedBonusPoints, 0x80);
DOTD_ASSERT_OFFSET(CKS08GameStructure, m_avObjectiveStates, 0x154);
DOTD_ASSERT_OFFSET(CKS08GameStructure, m_dwCheckpointMinHealth, 0x1ec);

// 0x00511060 / 0x005111a0 / 0x005115d0 / 0x00511710 (CKS08GameStructure.cpp): the health and mana capacities;
// include != 0 counts every matching collectible, 0 only the flagged ones.
int32_t ComputeCynderHealthCapacity(CKS08GameStructure* structure, uint8_t include);
int32_t ComputeSpyroHealthCapacity(CKS08GameStructure* structure, uint8_t include);
int32_t ComputeCynderManaCapacity(CKS08GameStructure* structure, uint8_t include);
int32_t ComputeSpyroManaCapacity(CKS08GameStructure* structure, uint8_t include);
// 0x005112e0 / 0x00511458 / 0x00511850 / 0x00511980 (CKS08GameStructure.cpp): the upgrades earned and the items toward
// the next one (the statistics and upgrade screens).
uint32_t CountManaUpgradesEarned(CKS08GameStructure* structure, int32_t dragon, uint8_t flagged);
uint32_t CountHealthUpgradesEarned(CKS08GameStructure* structure, int32_t dragon, uint8_t flagged);
uint32_t GetManaItemsTowardNextUpgrade(CKS08GameStructure* structure, int32_t dragon);
uint32_t GetHealthItemsTowardNextUpgrade(CKS08GameStructure* structure, int32_t dragon);

// 0x0050f050 GetDragonTotalUpgradePoints_maybe (CKS08GameState.cpp).
uint32_t GetDragonTotalUpgradePoints(CKS08GameStructure* structure, int32_t dragon);

class CKGameLevel;
// 0x00506ba8 Level_GetMainLevelIndex (k2000/misc/Level.cpp): 0..11 for the level numbers 10..120, else 99.
int32_t Level_GetMainLevelIndex(const CKGameLevel* level);
