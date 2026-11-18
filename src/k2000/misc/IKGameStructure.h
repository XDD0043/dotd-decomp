// IKGameStructure.h - the game structure: the levels and game states of the game (key 0x3b4c, vtable
// 0xb14a60, PS3 size 0x48; XXL2: K/KCore/Game/CKGameStructure.h). Original units: IKGameStructure.cpp
// (0x415f8-0x41714: the constructor) and CKDefaultGameStructure_2.cpp (0x41714-0x42700: its Load,
// 0x41f90, which Ghidra calls CKDefaultGameStructure_LoadImpl; it sits in IKGameStructure's vtable).
// XXL2's members in the same Load order, plus a DotD list at +0x24 (level part only).
//
// The game manager creates the one instance (CDefaultGameManager_InitImpl: GetGameStructureClassKey) and
// hands it to the loader as a global of GAME.KP3 and the level files.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class CDefaultGameManager;
class CKGameLevel;
class CKGameModule;
class CKGameSpawnPoint;
class CKGameState;
class IKPlayer;

class IKGameStructure : public IKSerializable {
public:
    IKGameStructure();             // 0x000415f8 IKGameStructure_Construct
    ~IKGameStructure() override;   // vt+0x00 / +0x04  0x995470 / 0x995528 (CKGameState.cpp)

    int32_t GetClassType() override { return 0xc; }          // vt+0x14 0x995440
    int32_t GetClassID() override { return 0xed; }           // vt+0x18 0x995448
    // vt+0x10 0x00041910 IKGameStructure_Destroy (Ghidra ..._ClearReferences; the level unload): the stages and
    // game states the level appended leave their lists, its +0x24 list is freed, and a current spawn point
    // that is not a game one is forgotten.
    void Destroy() override;
    int32_t Load(IKFile* file, int32_t type) override;       // vt+0x2c 0x00041f90
    int32_t GetSerializationFlags() override { return 0; }   // vt+0x34 0x9948c8
    // vt+0x30 0x00041aa0 CKDefaultGameStructure_PostLoad (CKS08GameStructure's 0x50f9a8 calls it): the level part (type 0)
    // gives each module its trigger synchro (the +0x24 list: synchro -> module). GAME.KP3 (type 1): the start game state
    // (+0x40) is the boot configuration's (-GameState: the state with that GUID, else the state at its index +0xac
    // when that is in range; the file's otherwise); it is applied to the structure (vt+0x70) and the game manager's
    // requested level and sector are those of the current spawn point; without a start state no spawn point is current.
    int32_t PostLoad(int32_t type) override;
    // vt+0x0c 0x00041888 CKDefaultGameStructure_DestroyGame (IKGameStructure's slot; Ghidra names it after the class):
    // the game states' list freed and emptied, then the stages' block freed (its length cleared only then).
    void DestroyGame() override;
    // vt+0x24 0x000416c0 IKGameStructure_vf24 (XXL2 RecursiveRegistration): below type 2 the structure registers with
    // the saving manager (CKSavingManager_RegisterSerializableObject 0x2bdb8, vt+0x24), then its
    // stages and game states register (first to last), type 0 also the +0x24 synchros.
    void RecursiveRegistration(int32_t type) override;
    int32_t Save(IKFile*, int32_t) override { return 1; }  // vt+0x28 0x000416b8 IKGameStructure_vf28
    virtual void Vf50() {}  // vt+0x50 0x00040bd0 IKGameStructure_vf50 (empty)
    virtual void Vf54() {}  // vt+0x54 0x00040bd8 IKGameStructure_vf54 (empty)
    // C1.6 gm: vt+0x58 0x00041448 (Ghidra CKDefaultGameStructure_vf58; it is IKGameStructure's slot): every
    // stage's vt+0x70 (CKGameLevel::Vf70: all its modules activated), from the last stage down.
    virtual void Vf58();
    // C1.6 gm: vt+0x5c 0x00041598 (Ghidra CKDefaultGameStructure_vf5C; XXL2 IKGameStructure::
    // ApplyGameStateToLevel): the current spawn point's stage's ApplyGameStateToLevel (vt+0x68).
    virtual void ApplyGameStateToLevel();
    // C1.6 gm: vt+0x60 0x00040cd0 IKGameStructure_vf60: the player's game state (+0x0c) applied to the
    // structure (CKGameState vt+0x70). Name ours.
    virtual void ApplyPlayerGameState(IKPlayer* player);
    virtual uint8_t Vf64() { return 0; }  // vt+0x64 0x009948d0 IKGameStructure_vf64
    // vt+0x68 0x00041290 IKGameStructure_vf68: the game states' count; with a filter, the states whose flag bit 0
    // equals *filter (counted from the last). Name ours.
    virtual uint32_t CountGameStates(const uint8_t* filter);
    // 0x000413c8 CKDefaultGameStructure_CountLevels (in CKGameState.cpp's unit): the same for the stages. Name Ghidra's.
    uint32_t CountLevels(const uint8_t* filter);
    // C1.6 gm: vt+0x6c 0x000413a8 IKGameStructure_SetCurrentSpawnPoint_maybe: +0x08, and +0x44 = its flags'
    // bit 0 (CKS08GameManager_vf2E8).
    virtual void SetCurrentSpawnPoint(CKGameSpawnPoint* spawnPoint);
    // vt+0x70 0x9948d8: +0x04 = manager (CDefaultGameManager_InitImpl calls it). XXL2 SetGameManager.
    virtual void SetGameManager(CDefaultGameManager* manager) { m_pGameManager = manager; }
    // 0x00040be8 CKDefaultGameStructure_GetCurrentLevel: the last stage whose vt+0x54 says it is the loaded
    // level; null when none.
    CKGameLevel* GetCurrentLevel();
    // 0x000414e8 CKDefaultGameStructure_FindLevelById_maybe: the last stage whose level number (+0x1c) is `id`.
    CKGameLevel* FindLevelById(int32_t id);
    // C1.6 gm: 0x00040e68 CKDefaultGameStructure_RefreshModuleTriggerDomains_maybe: every stage's modules'
    // trigger domains (CKGameModule::UpdateTriggerDomains), stages and modules from the last down.
    void RefreshModuleTriggerDomains();
    // 0x00041310 IKGameStructure_MarkVideoSeenInAllLevels_maybe: SetModuleFlag2ById(video) on every stage, last to first.
    void SetModuleFlag2InAllLevels(const void* video);
    // 0x00041da8 CKDefaultGameStructure_MarkSekensSeenInCurrentLevel_maybe: the last stage that is the loaded level
    // (vt+0x54) marks the sekens seen (CKGameLevel_MarkSekensSeen_maybe).
    void MarkSekensSeenInCurrentLevel(const void* sekens);
    // 0x00040dd0 CKDefaultGameStructure_CountTrackedActiveModules_maybe / 0x00040f58 ..._CountTrackedModules_maybe:
    // the stages' (from the last) CKGameLevel counts summed.
    uint32_t CountTrackedActiveModules();
    uint32_t CountTrackedModules();

    CDefaultGameManager* m_pGameManager;      // +0x04 (XXL2 IKGameManager*) GAME.KP3: the CKS08GameManager
    CKGameSpawnPoint* m_pCurrentSpawnPoint;   // +0x08 set at run time (0x413a8)
    TVector<CKGameLevel*, 8> m_vpStages;      // +0x0c (GAME.KP3: the 12 CKS08GameLevels)
    TVector<CKGameState*, 8> m_vpStates;      // +0x18 (GAME.KP3: the 19 CKS08GameStates)
    // +0x24 DotD: level part only, a new block per level file (LVL000: 438 references, as many as
    // GAME.KP3 has CKS08GameModules). Name ours.
    TVector<CKGameModule*, 8> m_vpUnk24;
    uint32_t m_ui32NbGlobalStages;            // +0x30
    uint32_t m_ui32NbLocalStages;             // +0x34
    uint32_t m_ui32NbGlobalStates;            // +0x38
    uint32_t m_ui32NbLocalStates;             // +0x3c
    CKGameState* m_pStartGameState;           // +0x40
    uint8_t m_bCurrentSpawnPointGlobal;       // +0x44 set at run time (0x413a8: the spawn point's flag bit 0)
    // +0x45..+0x47: the PS3 (Itanium C++ ABI) puts a subclass's first members in this tail padding
    // (CKS08GameStructure's two bytes at +0x45/+0x46); MSVC never does, so they are declared here.
    uint8_t m_aSubclassTail[3];
};
DOTD_ASSERT_SIZE(IKGameStructure, 0x48);
DOTD_ASSERT_OFFSET(IKGameStructure, m_pGameManager, 0x04);
DOTD_ASSERT_OFFSET(IKGameStructure, m_vpStages, 0x0c);
DOTD_ASSERT_OFFSET(IKGameStructure, m_vpStates, 0x18);
DOTD_ASSERT_OFFSET(IKGameStructure, m_vpUnk24, 0x24);
DOTD_ASSERT_OFFSET(IKGameStructure, m_ui32NbGlobalStages, 0x30);
DOTD_ASSERT_OFFSET(IKGameStructure, m_ui32NbLocalStates, 0x3c);
DOTD_ASSERT_OFFSET(IKGameStructure, m_pStartGameState, 0x40);
DOTD_ASSERT_OFFSET(IKGameStructure, m_bCurrentSpawnPointGlobal, 0x44);
DOTD_ASSERT_OFFSET(IKGameStructure, m_aSubclassTail, 0x45);
