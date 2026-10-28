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
    DOTD_DECLARE_FACTORIES(CKS08GameStructure)

    CKS08GameStructure();             // 0x0050fdd8 CKS08GameStructure_Construct
    ~CKS08GameStructure() override {} // vt+0x00 / +0x04  0x510da0 / 0x511d70

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
    // 0x005102e0 CKS08GameStructure_AreInfoPopupsEnabled_maybe: the game manager's edited option +0x05 (+0xf1).
    uint8_t AreInfoPopupsEnabled() const;
    // 0x005106c0 CKS08GameStructure_SetUnlockFlagByte_maybe: the unlock byte +0x23f + index; unlocking index 9 the
    // first time (+0x24f) shows the centre message 4.
    void SetUnlockFlagByte(int32_t index, uint8_t value);
    // C1.6 gm: 0x0050ed60 CKS08GameStructure_SaveCheckpointSnapshot_maybe (in CKS08GameState.cpp): health,
    // mana and the counters (+0x4c..+0xb0) and the six bytes +0xb4..+0xb9 copied to their checkpoint copies
    // (+0x1f0..+0x234, +0x238..+0x23d).
    void SaveCheckpointSnapshot();
    // C1.6 gm: vt+0x58 0x0050f958 / vt+0x5c 0x0050f980: IKGameStructure's (0x41448 / 0x41598).
    void Vf58() override;
    void ApplyGameStateToLevel() override;

    // C1.6 gm: the run-time words and bytes at their PS3 offsets in the raw ranges (+0x84..+0x153,
    // +0x1e4..+0x1eb, +0x1f0..+0x253), words in host order like the other members.
    uint32_t RtWord(uint32_t offset) const;
    void SetRtWord(uint32_t offset, uint32_t value);
    uint8_t& RtByte(uint32_t offset);
    // Not ported: vt+0x0c 0x50fa20, +0x10 0x50fc58, +0x24, +0x28, +0x30 0x50f9a8 PostLoad (STUB(C1.6)).

    // +0x45 / +0x46: the PS3 puts these first members in IKGameStructure's tail padding (see
    // IKGameStructure::m_aSubclassTail). Ghidra bHealthDivisor0 / bHealthDivisor1.
    uint8_t& HealthDivisor0() { return m_aSubclassTail[0]; }
    uint8_t& HealthDivisor1() { return m_aSubclassTail[1]; }

    uint32_t m_dwHealthMultiplier;  // +0x48 GAME.KP3 (live: 100)
    uint32_t m_unk4c;               // +0x4c run time (live: 300)
    uint32_t m_dwHealthBase;        // +0x50 GAME.KP3 (live: 300)
    uint32_t m_unk54;               // +0x54 run time
    uint32_t m_unk58;               // +0x58 GAME.KP3 (Ghidra field_0x58)
    uint8_t m_bManaDivisor0;        // +0x5c GAME.KP3
    uint8_t m_bManaDivisor1;        // +0x5d GAME.KP3
    uint8_t m_pad5e[2];
    uint32_t m_dwManaMultiplier;    // +0x60 GAME.KP3
    uint32_t m_unk64;               // +0x64 run time
    uint32_t m_dwManaBase;          // +0x68 GAME.KP3
    uint32_t m_unk6c;               // +0x6c run time
    uint32_t m_unk70;               // +0x70 GAME.KP3 (Ghidra field_0x70)
    uint32_t m_unk74;               // +0x74 run time
    uint32_t m_unk78;               // +0x78 run time
    uint32_t m_unk7c;               // +0x7c GAME.KP3, read after +0x80 (live: 4000)
    uint32_t m_unk80;               // +0x80 GAME.KP3
    uint8_t m_unk84[0xd0];          // +0x84..+0x153 run time
    TVector<uint8_t, 8> m_avbUnk154[12];  // +0x154 sized by GAME.KP3 (contents not in the file)
    uint8_t m_unk1e4[8];            // +0x1e4 run time
    uint32_t m_unk1ec;              // +0x1ec GAME.KP3 (Ghidra field_0x1ec)
    uint8_t m_unk1f0[0x64];         // +0x1f0..+0x253 run time
};
DOTD_ASSERT_SIZE(CKS08GameStructure, 0x254);
DOTD_ASSERT_OFFSET(CKS08GameStructure, m_dwHealthMultiplier, 0x48);
DOTD_ASSERT_OFFSET(CKS08GameStructure, m_dwHealthBase, 0x50);
DOTD_ASSERT_OFFSET(CKS08GameStructure, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKS08GameStructure, m_bManaDivisor0, 0x5c);
DOTD_ASSERT_OFFSET(CKS08GameStructure, m_dwManaMultiplier, 0x60);
DOTD_ASSERT_OFFSET(CKS08GameStructure, m_dwManaBase, 0x68);
DOTD_ASSERT_OFFSET(CKS08GameStructure, m_unk70, 0x70);
DOTD_ASSERT_OFFSET(CKS08GameStructure, m_unk7c, 0x7c);
DOTD_ASSERT_OFFSET(CKS08GameStructure, m_unk80, 0x80);
DOTD_ASSERT_OFFSET(CKS08GameStructure, m_avbUnk154, 0x154);
DOTD_ASSERT_OFFSET(CKS08GameStructure, m_unk1ec, 0x1ec);

// 0x00511060 / 0x005111a0 / 0x005115d0 / 0x00511710 (CKS08GameStructure.cpp): the health and mana capacities;
// include != 0 counts every matching collectible, 0 only the flagged ones.
int32_t ComputeCynderHealthCapacity(CKS08GameStructure* structure, uint8_t include);
int32_t ComputeSpyroHealthCapacity(CKS08GameStructure* structure, uint8_t include);
int32_t ComputeCynderManaCapacity(CKS08GameStructure* structure, uint8_t include);
int32_t ComputeSpyroManaCapacity(CKS08GameStructure* structure, uint8_t include);

// 0x0050f050 GetDragonTotalUpgradePoints_maybe (CKS08GameState.cpp).
uint32_t GetDragonTotalUpgradePoints(CKS08GameStructure* structure, int32_t dragon);
