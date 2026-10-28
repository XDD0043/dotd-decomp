// IKGameObject.cpp - reconstructed original translation unit 0x42da0-0x433f8 (GAME_TOC1, main_toc1), 23 functions, 22 live.
// Primary owner: IKGameObject (not a registered class)
// Other owners: KBase1D0C (9), CKS08GameLevelCollectible (3)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x42da0  IKGameObject_ClearGameData_maybe
//   [x] 0x42db0  IKGameObject_InitGameData
//   [x] 0x42dc0  IKGameObject_ConstructBase
//   [ ] 0x42df8  IKGameObject_ConstructBase_2  [dead]
//   [ ] 0x42e30  KStub_Return1_42e30
//   [ ] 0x42e38  IKGameObject_vf24
//   [ ] 0x42e40  IKGameObject_PostLoad
//   [x] 0x42e48  IKGameObject_Destroy
//   [x] 0x42ed0  IKGameObject_DestroyGame
//   [ ] 0x42f10  IKGameObject_GetName
//   [x] 0x42f38  IKGameObject_Load
//   [ ] 0x43160  CKS08GameLevelCollectible_IsCurrentLevel
//   [ ] 0x431c8  KBase1D0C_vf68
//   [ ] 0x431d0  CKS08GameLevelCollectible_vf70
//   [ ] 0x431d8  KBase1D0C_vf64
//   [ ] 0x43200  KBase1D0C_ClearLevelData
//   [x] 0x43228  KBase1D0C_InitLevelData
//   [x] 0x43250  KBase1D0C_InitGameData
//   [ ] 0x43278  KBase1D0C_PostLoad
//   [x] 0x432a0  CKS08GameLevelCollectible_LoadBase_maybe
//   [ ] 0x43380  KBase1D0C_vf28
//   [ ] 0x433a8  KBase1D0C_vf24
//   [ ] 0x433d0  KBase1D0C_ClearReferences
//
//   [x] 0x993d60  IKGameObject_GetGuid  [inline]
//   [x] 0x993d70  IKGameObject_IsPersistent_maybe  [inline]
//   [x] 0x993d80  KStub_Return0_993d80  [inline]
//   [x] 0x993d88  KStub_Nop_993d88  [inline]
//   [x] 0x993dc8  IKGameObject_SetGuid  [inline]
//   [x] 0x995698  IKGameObject_vf14  [inline]
//   [x] 0x9956a0  IKGameObject_vf18  [inline]
//   [ ] 0x9956a8  IKGameObject_DeletingDestructor  [inline]
//   [ ] 0x9956e8  IKGameObject_vf8  [inline]
//   [ ] 0x995708  IKGameObject_vf0  [inline]
//   [ ] 0x995720  KBase1D0C_vf8  [inline]
//   [x] 0x995748  KBase1D0C_vf14  [inline]
//   [x] 0x995750  KBase1D0C_vf18  [inline]
//   [ ] 0x995758  KBase1D0C_DeletingDestructor  [inline]
//   [ ] 0x9957a0  KBase1D0C_vf0  [inline]
#include "Spyro2008/logic/IKGameObject.h"

#include "k2000/io/IKFile.h"
#include "k2000/misc/ClassRegistry.h"

bool IKGameObject_IsGameEntry(const IKSerializable* object) {
    IKSerializable* mutableObject = const_cast<IKSerializable*>(object);
    const uint32_t key = MakeClassKey(static_cast<uint32_t>(mutableObject->GetClassType()),
                                      static_cast<uint32_t>(mutableObject->GetClassID()));
    if (ClassRegistry_IsLoadPending(key)) return false;
    return (static_cast<const IKGameObject*>(object)->m_baFlags & 1u) != 0;
}

// 0x00042dc0 IKGameObject_ConstructBase: the GUID words in the original's order (+0x04, +0x10, +0x08,
// +0x0c), then bit 0 of the flags; the other flag bits are left as they are.
IKGameObject::IKGameObject() {
    m_guidIdentifier[0] = 0;
    m_guidIdentifier[3] = 0;
    m_guidIdentifier[1] = 0;
    m_guidIdentifier[2] = 0;
    m_baFlags &= ~1u;
}

// 0x00993dc8 IKGameObject_SetGuid
void IKGameObject::SetGuid(const uint32_t* guid) { Uuid_Copy(m_guidIdentifier, guid); }

// 0x00042db0 IKGameObject_InitGameData (XXL2 InitializeGameData)
void IKGameObject::InitializeGameData() { m_baFlags &= ~1u; }

// 0x00042da0 IKGameObject_ClearGameData_maybe (XXL2 DestroyGameData)
void IKGameObject::DestroyGameData() { m_baFlags &= ~1u; }

// 0x00042e48 IKGameObject_Destroy
void IKGameObject::Destroy() {
    DestroyLevelData();
    if ((m_baFlags & 1u) == 0) DestroyGameData();
}

// 0x00042ed0 IKGameObject_DestroyGame
void IKGameObject::DestroyGame() { DestroyGameData(); }

// 0x00042f38 IKGameObject_Load. GAME.KP3 (K_GAME_PLATEFORMS) holds the game-structure block: the object's
// own Load is called again with type 8, so every class reads its type-8 part there. A level file
// (K_LEVEL_PLATEFORMS) repeats the block when bit 0 of the flags is clear, then the level part follows.
int32_t IKGameObject::Load(IKFile* file, int32_t type) {
    if (type == K_GAME_PLATEFORMS) {
        Load(file, kGameStructureBlock);  // vt+0x2c
        return 1;
    }
    if (type == kGameStructureBlock) {
        InitializeGameData();  // vt+0x58
        // The name (XXL2 m_szName): s16 length + bytes, skipped. Ghidra's decompiler drops this block
        // (it assumes the length stays 0); the assembly seeks over it (0x430a4).
        int16_t nameLength = 0;
        ReadS16LE(file, &nameLength);
        if (nameLength > 0) file->Seek(nameLength, kSeekCur);
        ReadU32LE(file, &m_baFlags);
        return 1;
    }
    if (type == K_LEVEL_PLATEFORMS) {
        if ((m_baFlags & 1u) == 0) Load(file, kGameStructureBlock);  // vt+0x2c
        InitializeLevelData();  // vt+0x5c
    }
    return 1;
}
#include "Spyro2008/logic/KBase1D0C.h"

#include "Spyro2008/logic/CKS08GameLevel.h"
#include "k2000/io/IKFile.h"

// 0x000432a0 (Ghidra CKS08GameLevelCollectible_LoadBase_maybe): KBase1D0C's Load.
int32_t KBase1D0C::Load(IKFile* file, int32_t type) {
    IKGameObject::Load(file, type);
    if (type != kGameStructureBlock) return 1;
    IKFile_ReadRef(file, &m_pLevel);
    return 1;
}
