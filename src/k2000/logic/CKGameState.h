// CKGameState.h - a game state: a snapshot of the progress through the levels and modules (key 0x32cc,
// vtable 0xb14990, PS3 size 0x90). Original unit: CKGameState.cpp (0x3dad8-0x40bd0). XXL2:
// K/KCore/Game/CKGameState.h (m_pGameStructure, m_pGameSpawnPoint, m_vpStages, m_vbCinematicStates,
// m_vpModules, m_vbModuleStates), in the same Load order; DotD adds a second module state, two more
// object lists with a state each, and a reference at +0x8c.
//
// Each list entry in a file is a reference and the entry's end offset, then the entry's state bytes
// (ReadStageData & co.). A level file skips (Seek) the entries whose object the list already has.
#pragma once
#include <cstdint>

#include "Spyro2008/logic/IKGameObject.h"
#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class CKGameLevel;
class CKGameModule;
class CKGameSpawnPoint;
class IKGameStructure;

class CKGameState : public IKGameObject {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xcb)
    DOTD_DECLARE_FACTORIES(CKGameState)

    CKGameState();             // inlined in CKGameState_Create 0x3dd08 / CreateArray
    ~CKGameState() override {} // vt+0x00 / +0x04  0x995290 / 0x9950d0

    // vt+0x60 0x0003e598 CKGameState_ClearLevelData_maybe (XXL2 DestroyLevelData): every entry the level
    // appended (flags bit 0 clear) removed from the four lists, each list from the last entry down.
    void DestroyLevelData() override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0003fd18 CKGameState_Load
    void InitializeGameData() override;                 // vt+0x58 0x0003f2d8 CKGameState_InitGameData
    // vt+0x5c 0x3dbe8 InitLevelData only calls IKGameObject's. Not ported: vt+0x1c 0x3ed78, +0x54 0x3eaf0,
    // +0x60 0x3e598, +0x64 0x3f458, +0x6c 0x3e300, the Remove/Write slots +0x84/+0x8c/+0x94/+0x9c/+0xa0/
    // +0xa8/+0xb0/+0xb8 (STUB(C1.6)).

    // C1.6 gm: the state and the game (XXL2 ApplyToStructure / CopyFromStructure / CopyFromState, two
    // slots later in DotD).
    // vt+0x70 0x0003df80 CKGameState_ApplyStateToObjects_maybe: the module states restored into the
    // modules (where their filters allow); with vt+0xc4, the spawn point made the structure's current one
    // and the stage / +0x5c / +0x74 objects' flag bit 1 restored.
    virtual void ApplyToStructure();
    virtual void Vf74() {}  // vt+0x74 0x9950c8 (empty)
    // vt+0x78 0x0003e7f8 CKGameState_CaptureStateFromObjects_maybe: the reverse (saved where the filters
    // allow; with vt+0xc0, the structure's current spawn point and the flags saved).
    virtual void CopyFromStructure();
    // vt+0x7c 0x0003eb68 CKGameState_CopyFrom_maybe: the spawn point and every list's entries and states
    // copied from `other` (this state's lengths).
    virtual void CopyFromState(const CKGameState* other);

    // The list slots (XXL2 AddGameStage/AddGameModule, ReadStageData/ReadModuleData: the same code; DotD has
    // four lists, each with an Add slot and one after it). Add appends the object and a 0 state, and returns
    // the state's index; Read reads the entry's state byte(s) at that index.
    virtual uint32_t AddGameStage(IKSerializable* stage);    // vt+0x80 0x0003faa8
    virtual void RemoveGameStage(uint32_t index);             // vt+0x84 0x0003dae8 (name ours: the last entry moves in)
    virtual uint32_t AddGameModule(IKSerializable* module);  // vt+0x88 0x0003f8e0
    virtual void RemoveGameModule(uint32_t index);            // vt+0x8c 0x0003e4f0 (name ours)
    virtual uint32_t AddUnk5c(IKSerializable* object);        // vt+0x90 0x0003fbe0 (name ours)
    virtual void RemoveUnk5c(uint32_t index);                 // vt+0x94 0x0003e478 (name ours)
    virtual uint32_t AddUnk74(IKSerializable* object);        // vt+0x98 0x0003f618 (name ours)
    virtual void RemoveUnk74(uint32_t index);                 // vt+0x9c 0x0003e400 (name ours)
    virtual void WriteStageData() {}                                         // vt+0xa0 0x3ed80 (STUB(C1.6); arguments unverified)
    virtual void ReadStageData(IKFile* file, int32_t type, uint32_t index);  // vt+0xa4 0x0003f140
    virtual void WriteModuleData() {}                                        // vt+0xa8 0x3f230 (STUB(C1.6); arguments unverified)
    virtual void ReadModuleData(IKFile* file, int32_t type, uint32_t index); // vt+0xac 0x0003f098
    virtual void WriteUnk5cData() {}                                         // vt+0xb0 0x3f1e0 (STUB(C1.6); arguments unverified)
    virtual void ReadUnk5cData(IKFile* file, int32_t type, uint32_t index);  // vt+0xb4 0x0003f048
    virtual void WriteUnk74Data() {}                                         // vt+0xb8 0x3f190 (STUB(C1.6); arguments unverified)
    virtual void ReadUnk74Data(IKFile* file, int32_t type, uint32_t index);  // vt+0xbc 0x0003eff8
    // C1.6 gm: vt+0xc0 0x3dad8 / vt+0xc4 0x3dae0 (1): whether CopyFromStructure saves and ApplyToStructure
    // restores the spawn point and the object flags. Names ours.
    virtual uint8_t SavesSpawnPoint() { return 1; }
    virtual uint8_t RestoresSpawnPoint() { return 1; }

    IKGameStructure* m_pGameStructure;      // +0x18 type-8 block; InitializeGameData: 0
    CKGameSpawnPoint* m_pGameSpawnPoint;    // +0x1c type-8 block and K_GAME_MEMCARD
    TVector<CKGameLevel*, 8> m_vpStages;    // +0x20 (XXL2 CKGameStage*)
    TVector<uint8_t, 8> m_vbCinematicStates;  // +0x2c one per stage (XXL2 bool)
    TVector<CKGameModule*, 8> m_vpModules;  // +0x38
    TVector<uint8_t, 8> m_vbModuleStates;   // +0x44 one per module
    TVector<uint8_t, 8> m_vbUnk50;          // +0x50 DotD: a second byte per module
    TVector<IKSerializable*, 8> m_vpUnk5c;  // +0x5c DotD list
    TVector<uint8_t, 8> m_vbUnk68;          // +0x68 one per +0x5c entry
    TVector<IKSerializable*, 8> m_vpUnk74;  // +0x74 DotD list
    TVector<uint8_t, 8> m_vbUnk80;          // +0x80 one per +0x74 entry
    IKSerializable* m_pUnk8c;               // +0x8c DotD: type-8 block, last; InitializeGameData: 0
};
DOTD_ASSERT_SIZE(CKGameState, 0x90);
DOTD_ASSERT_OFFSET(CKGameState, m_pGameStructure, 0x18);
DOTD_ASSERT_OFFSET(CKGameState, m_pGameSpawnPoint, 0x1c);
DOTD_ASSERT_OFFSET(CKGameState, m_vpStages, 0x20);
DOTD_ASSERT_OFFSET(CKGameState, m_vbCinematicStates, 0x2c);
DOTD_ASSERT_OFFSET(CKGameState, m_vpModules, 0x38);
DOTD_ASSERT_OFFSET(CKGameState, m_vbModuleStates, 0x44);
DOTD_ASSERT_OFFSET(CKGameState, m_vbUnk50, 0x50);
DOTD_ASSERT_OFFSET(CKGameState, m_vpUnk5c, 0x5c);
DOTD_ASSERT_OFFSET(CKGameState, m_vbUnk68, 0x68);
DOTD_ASSERT_OFFSET(CKGameState, m_vpUnk74, 0x74);
DOTD_ASSERT_OFFSET(CKGameState, m_vbUnk80, 0x80);
DOTD_ASSERT_OFFSET(CKGameState, m_pUnk8c, 0x8c);
