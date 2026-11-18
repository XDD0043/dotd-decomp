// IKGameObject.h - the game-structure objects (key 0x330c, vtable 0xb14b58, PS3 size 0x18; XXL2:
// K/KCore/Game/IKGameObject.h, our earlier KBase330C / "CKGameDefinition"). Original unit:
// IKGameObject.cpp (0x42da0-0x433f8).
//
// The levels, modules, spawn points, game states and texts of GAME.KP3 derive from it. Their data comes
// in two parts: a game part, the "game-structure block" read with type 8 (DotD's value for XXL2's 7),
// and a level part read with K_LEVEL_PLATEFORMS from the glob records of a level file, which reach the
// GAME object by its GUID. IKGameObject::Load dispatches between them (see IKGameObject.cpp).
//
// XXL2 keeps the object's name (m_szName) after the flags; DotD skips the name in the file and has no
// field for it.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class IKGameObject : public IKSerializable {
public:
    // The game-structure block's ESerializationType (DotD: 8; XXL2: 7).
    static constexpr int32_t kGameStructureBlock = 8;

    IKGameObject();             // 0x00042dc0 IKGameObject_ConstructBase
    ~IKGameObject() override {} // vt+0x00 / +0x04  0x995708 / 0x9956a8

    void DestroyGame() override;                     // vt+0x0c 0x42ed0
    void Destroy() override;                         // vt+0x10 0x42e48
    int32_t GetClassType() override { return 0xc; }  // vt+0x14 0x995698
    int32_t GetClassID() override { return 0xcc; }   // vt+0x18 0x9956a0
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x42f38 IKGameObject_Load
    const uint32_t* GetGuid() override { return m_guidIdentifier; }  // vt+0x44 0x993d60
    void SetGuid(const uint32_t* guid) override;                     // vt+0x48 0x993dc8
    // vt+0x4c 0x42f10 IKGameObject_GetName: ClassRegistry_GetObjectDebugName (0x113e8), the same body as the
    // IKSerializable default (0x990d58: the class manager's GetObjectDebugName), which is used.
    // vt+0x24 0x42e38 RecursiveRegistration, vt+0x28 0x42e30 Save, vt+0x30 0x42e40 PostLoad: 1 (the subclasses call them
    // as their base's); the IKSerializable defaults do the same.

    // vt+0x50 0x993d70 (Ghidra IsPersistent_maybe): bit 0 of the flags. Set, the level files carry no
    // copy of the game-structure block for this object (Load, K_LEVEL_PLATEFORMS).
    virtual uint32_t KUGetSerializationConsistency() { return m_baFlags & 1u; }
    virtual uint8_t GetMatchesThisLevel() { return 0; }  // vt+0x54 0x993d80 (Ghidra IsCurrentLevel)
    virtual void InitializeGameData();                   // vt+0x58 0x42db0 (called by the type-8 Load)
    virtual void InitializeLevelData() {}                // vt+0x5c 0x42d88 (called by the level Load)
    virtual void DestroyLevelData() {}                   // vt+0x60 0x42d90
    virtual void DestroyGameData();                      // vt+0x64 0x42da0 (Ghidra ClearGameData_maybe)
    // vt+0x68 0x42d98 (empty): the game state applied to the level's objects (XXL2 CKGameStage /
    // CKGameModule ApplyGameStateToLevel; IKGameStructure::ApplyGameStateToLevel starts it).
    virtual void ApplyGameStateToLevel() {}
    virtual void Vf6C() {}                               // vt+0x6c 0x993d88 (DotD; empty)

    uint32_t m_guidIdentifier[4];  // +0x04 CGuid: set by the loader (SetGuid) from the file's GUID list
    // +0x14 CBitArray (XXL2). Read whole by the type-8 block (the editor wrote uninitialised bits: GAME.KP3
    // has 0xcdcdcdc9 and 0xcdcdcdcd). Bit 0: KUGetSerializationConsistency. The constructor only clears
    // bit 0.
    uint32_t m_baFlags;
};
DOTD_ASSERT_SIZE(IKGameObject, 0x18);
DOTD_ASSERT_OFFSET(IKGameObject, m_guidIdentifier, 0x04);
DOTD_ASSERT_OFFSET(IKGameObject, m_baFlags, 0x14);

// The test the level unload makes on the entries of the game structure's lists (CKGameLevel_ClearLevelData,
// CKGameState_ClearLevelData_maybe, IKGameStructure_Destroy, CKS08GameLevel_ClearLevelData_maybe): bit 0 of
// the object's flags (+0x14), set for the game's own (GAME.KP3) objects, clear for a level's. DEV: an object
// of a placeholder class (Load not ported) has no such word; placeholders only come from level files, so it
// counts as a level object.
bool IKGameObject_IsGameEntry(const IKSerializable* object);
