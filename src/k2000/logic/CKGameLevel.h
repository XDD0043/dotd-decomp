// CKGameLevel.h - a level of the game structure (key 0x584c, vtable 0xb14768, PS3 size 0x88). Original
// unit: CKGameLevel.cpp (0x39190-0x3b4e8). XXL2's CKGameStage (K/KCore/Game/CKGameStage.h): the same
// members in the same Load order, plus two DotD lists (+0x48, +0x54) and a DotD reference (+0x84).
//
// Each list has a game part (type-8 block, GAME.KP3: the first m_ui32NbGlobal* entries) and a level
// part that the level file appends (K_LEVEL_PLATEFORMS: m_ui32NbLocal* more).
#pragma once
#include <cstdint>

#include "Spyro2008/logic/IKGameObject.h"
#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class CKGameModule;
class CKGameSpawnPoint;
class IKGameStructure;

class CKGameLevel : public IKGameObject {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x161)
    DOTD_DECLARE_FACTORIES(CKGameLevel)

    CKGameLevel();             // 0x00039738 (Ghidra CKS08GameLevel_ConstructBase_maybe)
    ~CKGameLevel() override {} // vt+0x00 / +0x04  0x994b00 / 0x994bf0

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0003a970 CKGameLevel_Load
    void InitializeGameData() override;                 // vt+0x58 0x00039458 CKGameLevel_InitGameData
    void InitializeLevelData() override;                // vt+0x5c 0x00039410 CKGameLevel_InitLevelData_maybe
    // vt+0x54 0x00039558 CKGameLevel_IsCurrentLevel: its GUID is the loaded level's.
    uint8_t GetMatchesThisLevel() override;
    // vt+0x60 0x0003a3e0 CKGameLevel_ClearLevelData (XXL2 DestroyLevelData): the level-appended entries
    // removed from the four lists. Not ported: +0x64 0x39310 (STUB(C1.6)).
    void DestroyLevelData() override;
    // C1.6 gm: vt+0x68 0x00039d28 CKGameLevel_vf68 (XXL2 CKGameStage::ApplyGameStateToLevel): the modules',
    // then the +0x48 and +0x54 objects' ApplyGameStateToLevel, each list from the last entry down.
    void ApplyGameStateToLevel() override;
    // C1.6 gm: vt+0x70 0x0003a190 CKGameLevel_vf70: every module activated (vt+0x70 with 1) and the +0x48 /
    // +0x54 objects' flag bit 1 set, each list from the last entry down (IKGameStructure's vt+0x58).
    virtual void Vf70();
    // C1.6 gm: 0x00039ba8 CKGameLevel_CountModules: the module count; with a filter, the modules whose flag
    // bit 0 equals *filter.
    uint32_t CountModules(const uint8_t* filter);
    // 0x0003a2f8 CKGameLevel_MarkVideoSeen_maybe: the game video of the +0x48 list (last to first) whose video
    // reference (+0x1c) is `video` gets bit 1 of its flags set ("seen"); 1 when there is one.
    uint8_t SetModuleFlag2ById(const void* video);
    // 0x00039c28 CKGameLevel_MarkSekensSeen_maybe: the same on the +0x54 list (the game sekens), whose entries' +0x1c is a
    // sekens.
    uint8_t MarkSekensSeen(const void* sekens);

    IKGameStructure* m_pGameStructure;  // +0x18 (GAME.KP3: the CKS08GameStructure); InitializeGameData: 0
    int32_t m_i32StageIndex;            // +0x1c the level number (N040_Niv_Dragon_City: 40); InitializeGameData: -1
    uint32_t m_guidLevelIdentifier[4];  // +0x20 CGuid (Uuid_Read)
    TVector<CKGameModule*, 8> m_vpModules;          // +0x30 (GAME.KP3: CKS08GameModule)
    TVector<CKGameSpawnPoint*, 8> m_vpSpawnPoints;  // +0x3c (GAME.KP3: CKS08GameSpawnPoint)
    // +0x48 / +0x54 DotD only, empty in GAME.KP3; modules _maybe (the dead CKGameLevel_*_Arr48/_Arr54
    // helpers test module flags). Names ours.
    TVector<IKSerializable*, 8> m_vpUnk48;
    TVector<IKSerializable*, 8> m_vpUnk54;
    uint32_t m_ui32NbGlobalModules;      // +0x60
    uint32_t m_ui32NbLocalModules;       // +0x64
    uint32_t m_ui32NbGlobalSpawnPoints;  // +0x68
    uint32_t m_ui32NbLocalSpawnPoints;   // +0x6c
    uint32_t m_ui32NbGlobalUnk48;        // +0x70
    uint32_t m_ui32NbLocalUnk48;         // +0x74
    uint32_t m_ui32NbGlobalUnk54;        // +0x78
    uint32_t m_ui32NbLocalUnk54;         // +0x7c
    IKSerializable* m_pCinematicScene;   // +0x80 read last by the level part, as XXL2's (null in LVL000)
    IKSerializable* m_pUnk84;            // +0x84 DotD: read last by the type-8 block (GAME.KP3: a PS3_CKVideo)
};
DOTD_ASSERT_SIZE(CKGameLevel, 0x88);
DOTD_ASSERT_OFFSET(CKGameLevel, m_pGameStructure, 0x18);
DOTD_ASSERT_OFFSET(CKGameLevel, m_i32StageIndex, 0x1c);
DOTD_ASSERT_OFFSET(CKGameLevel, m_guidLevelIdentifier, 0x20);
DOTD_ASSERT_OFFSET(CKGameLevel, m_vpModules, 0x30);
DOTD_ASSERT_OFFSET(CKGameLevel, m_vpSpawnPoints, 0x3c);
DOTD_ASSERT_OFFSET(CKGameLevel, m_vpUnk48, 0x48);
DOTD_ASSERT_OFFSET(CKGameLevel, m_vpUnk54, 0x54);
DOTD_ASSERT_OFFSET(CKGameLevel, m_ui32NbGlobalModules, 0x60);
DOTD_ASSERT_OFFSET(CKGameLevel, m_ui32NbLocalUnk54, 0x7c);
DOTD_ASSERT_OFFSET(CKGameLevel, m_pCinematicScene, 0x80);
DOTD_ASSERT_OFFSET(CKGameLevel, m_pUnk84, 0x84);
