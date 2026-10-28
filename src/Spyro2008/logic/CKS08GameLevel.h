// CKS08GameLevel.h - Spyro's level (key 0x788c, vtable 0xb2b348, PS3 size 0x9c). Original unit:
// CKS08GameLevel.cpp (0x506e00-0x507c80). GAME.KP3 holds 12. Not in XXL2. It adds a fifth list, the
// level's collectibles, with the same game/level split as CKGameLevel's.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKGameLevel.h"
#include "k2000/util/TVector.h"

class CKS08GameLevelCollectible;

class CKS08GameLevel : public CKGameLevel {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x1e2)
    DOTD_DECLARE_FACTORIES(CKS08GameLevel)

    CKS08GameLevel();             // 0x00507008 CKS08GameLevel_Construct
    ~CKS08GameLevel() override {} // vt+0x00 / +0x04  0x507c38 / 0x507b18

    // vt+0x60 0x00507530 CKS08GameLevel_ClearLevelData_maybe: the collectibles the level appended removed,
    // then CKGameLevel's.
    void DestroyLevelData() override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005075e8 CKS08GameLevel_Load
    void InitializeGameData() override;                 // vt+0x58 0x00506f30 (Ghidra CKS08GameLevel_vf58)
    void InitializeLevelData() override;                // vt+0x5c 0x00506ef8 CKS08GameLevel_InitLevelData
    // Not ported: vt+0x60 0x507530, +0x64 0x506e88 (STUB(C1.6)).
    // C1.6 gm: vt+0x68 0x00507230 CKS08GameLevel_vf68: CKGameLevel's, then the collectibles'
    // ApplyGameStateToLevel (vt+0x68, empty: 0x4f5da8), from the last one down.
    void ApplyGameStateToLevel() override;

    // +0x88 (GAME.KP3: CKS08GameLevelCollectible; CKS08GameLevel_IsArmorPieceCollected_maybe reads it).
    // Names ours.
    TVector<CKS08GameLevelCollectible*, 8> m_vpCollectibles;
    uint32_t m_ui32NbGlobalCollectibles;  // +0x94 type-8 block
    uint32_t m_ui32NbLocalCollectibles;   // +0x98 level part
};
DOTD_ASSERT_SIZE(CKS08GameLevel, 0x9c);
DOTD_ASSERT_OFFSET(CKS08GameLevel, m_vpCollectibles, 0x88);
DOTD_ASSERT_OFFSET(CKS08GameLevel, m_ui32NbGlobalCollectibles, 0x94);
DOTD_ASSERT_OFFSET(CKS08GameLevel, m_ui32NbLocalCollectibles, 0x98);

// 0x00507178 CountStatEntriesByCategory (CKS08GameLevel.cpp).
uint32_t CountStatEntriesByCategory(CKS08GameLevel* level, uint8_t category, int32_t requireFlag);
