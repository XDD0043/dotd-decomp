// CKGameState.cpp - reconstructed original translation unit 0x3da88-0x415f8 (GAME_TOC1, main_toc1), 67 functions, 58 live.
// Primary class: CKGameState  key 0x32cc  category Logic  size 0x90  vtable 0xb14990
// Other owners: CKDefaultGameStructure (14), IKGameStructure (6)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3da88  CKGameState_Delete
//   [x] 0x3dad8  CKGameState_vfC0
//   [x] 0x3dae0  CKGameState_vfC4
//   [x] 0x3dae8  CKGameState_vf84
//   [ ] 0x3db60  RegisterCKGameStateClass
//   [ ] 0x3dbd8  _GLOBAL__I_3dbd8
//   [x] 0x3dbe8  CKGameState_InitLevelData_maybe
//   [ ] 0x3dc10  CKGameState_PostLoad
//   [ ] 0x3dc38  CKGameState_Destroy
//   [x] 0x3dc60  CKGameState_DeleteArray
//   [x] 0x3dd08  CKGameState_Create
//   [ ] 0x3de18  CKGameState_CountCompletedTrackedModules_maybe
//   [ ] 0x3dea0  CKGameState_RecursiveRegistration
//   [x] 0x3df80  CKGameState_ApplyStateToObjects_maybe
//   [ ] 0x3e300  CKGameState_ResetStateFlags_maybe
//   [x] 0x3e400  CKGameState_vf9C
//   [x] 0x3e478  CKGameState_vf94
//   [x] 0x3e4f0  CKGameState_vf8C
//   [x] 0x3e598  CKGameState_ClearLevelData_maybe
//   [x] 0x3e7f8  CKGameState_CaptureStateFromObjects_maybe
//   [ ] 0x3eaf0  CKGameState_IsCurrentLevel
//   [x] 0x3eb68  CKGameState_CopyFrom_maybe
//   [ ] 0x3ed78  CKGameState_MessageProc
//   [ ] 0x3ed80  CKGameState_SaveStateByte_maybe
//   [ ] 0x3edd0  CKGameState_Save
//   [x] 0x3eff8  CKGameState_vfBC
//   [x] 0x3f048  CKGameState_vfB4
//   [x] 0x3f098  CKGameState_ReadModuleValue_maybe
//   [x] 0x3f140  CKGameState_LoadStateByte_maybe
//   [ ] 0x3f190  CKGameState_vfB8
//   [ ] 0x3f1e0  CKGameState_vfB0
//   [ ] 0x3f230  CKGameState_vfA8
//   [x] 0x3f2d8  CKGameState_InitGameData
//   [ ] 0x3f458  CKGameState_ClearGameData_maybe
//   [x] 0x3f618  CKGameState_vf98
//   [x] 0x3f750  CKGameState_CreateArray
//   [x] 0x3f8e0  CKGameState_AddModuleValue_maybe
//   [x] 0x3faa8  CKGameState_AddStageValue_maybe
//   [x] 0x3fbe0  CKGameState_vf90
//   [x] 0x3fd18  CKGameState_Load
//   [ ] 0x40324  FUN_00040324  [dead]
//   [x] 0x40404  CKGameState_Load_SplitTail_40404_maybe
//   [x] 0x40594  CKGameState_Load_SplitTail_40594_maybe
//   [x] 0x405dc  CKGameState_Load_SplitTail_405dc_maybe
//   [ ] 0x40624  FUN_00040624  [dead]
//   [ ] 0x40bd0  IKGameStructure_vf50
//   [ ] 0x40bd8  IKGameStructure_vf54
//   [ ] 0x40be0  KStub_Nop_40be0  [dead]
//   [x] 0x40be8  CKDefaultGameStructure_GetCurrentLevel
//   [ ] 0x40cc8  KStub_Nop_40cc8
//   [x] 0x40cd0  IKGameStructure_vf60
//   [ ] 0x40d18  CKDefaultGameStructure_HasModuleById_Arr48_maybe  [dead]
//   [ ] 0x40dd0  CKDefaultGameStructure_CountTrackedActiveModules_maybe
//   [x] 0x40e68  CKDefaultGameStructure_RefreshModuleTriggerDomains_maybe
//   [ ] 0x40f58  CKDefaultGameStructure_CountTrackedModules_maybe
//   [ ] 0x40ff0  CKDefaultGameStructure_CountModules_Arr3c  [dead]
//   [ ] 0x41098  CKDefaultGameStructure_CountModules_Arr54  [dead]
//   [ ] 0x41140  CKDefaultGameStructure_CountModules_Arr48  [dead]
//   [ ] 0x411e8  CKDefaultGameStructure_CountModules  [dead]
//   [ ] 0x41290  IKGameStructure_vf68
//   [x] 0x41310  IKGameStructure_MarkVideoSeenInAllLevels_maybe
//   [x] 0x413a8  IKGameStructure_SetCurrentSpawnPoint_maybe
//   [ ] 0x413c8  CKDefaultGameStructure_CountLevels
//   [x] 0x41448  CKDefaultGameStructure_vf58
//   [x] 0x414e8  CKDefaultGameStructure_FindLevelById_maybe
//   [ ] 0x41538  CKDefaultGameStructure_HasLevelById_maybe  [dead]
//   [x] 0x41598  CKDefaultGameStructure_vf5C
//
//   [x] 0x9948c8  IKGameStructure_GetSerializationFlags  [inline]
//   [ ] 0x9948d0  IKGameStructure_vf64  [inline]
//   [x] 0x9948d8  IKGameStructure_vf70  [inline]
//   [ ] 0x9948e0  CKDefaultGameStructure_IsKindOfClass  [inline]
//   [ ] 0x994908  CKDefaultGameStructure_GetClassType  [inline]
//   [ ] 0x994910  CKDefaultGameStructure_GetClassID  [inline]
//   [ ] 0x994918  CKDefaultGameStructure_DeletingDestructor  [inline]
//   [ ] 0x9949f0  CKDefaultGameStructure_Destructor  [inline]
//   [ ] 0x995090  CKGameState_IsKindOfClass  [inline]
//   [x] 0x9950b8  CKGameState_GetClassType  [inline]
//   [x] 0x9950c0  CKGameState_GetClassID  [inline]
//   [x] 0x9950c8  CKGameState_vf74  [inline]
//   [ ] 0x9950d0  CKGameState_DeletingDestructor  [inline]
//   [ ] 0x995290  CKGameState_Destructor  [inline]
//   [x] 0x995440  IKGameStructure_vf14  [inline]
//   [x] 0x995448  IKGameStructure_vf18  [inline]
//   [ ] 0x995450  IKGameStructure_vf8  [inline]
//   [ ] 0x995470  IKGameStructure_Destructor  [inline]
//   [ ] 0x995528  IKGameStructure_DeletingDestructor  [inline]
#include "k2000/logic/CKGameState.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/CKGameLevel.h"
#include "k2000/logic/CKGameModule.h"
#include "k2000/logic/CKGameSpawnPoint.h"
#include "k2000/logic/GameVector.h"
#include "k2000/misc/IKGameStructure.h"

namespace {

template <class T>
void ClearVector(TVector<T, 8>* vector) {
    vector->m_ui32NbElt = 8;
    vector->m_pBlock = nullptr;
    vector->m_ui32NbUsedElt = 0;
}

template <class T>
bool Contains(const TVector<T*, 8>& list, IKSerializable* object) {
    for (uint32_t i = 0; i < list.m_ui32NbUsedElt; ++i) {
        if (static_cast<IKSerializable*>(list.m_pBlock[i]) == object) return true;
    }
    return false;
}

using AddSlot = uint32_t (CKGameState::*)(IKSerializable*);
using ReadSlot = void (CKGameState::*)(IKFile*, int32_t, uint32_t);

// One list of the type-8 block: the count, then per entry its reference and its state bytes.
void LoadGameList(CKGameState* state, IKFile* file, AddSlot add, ReadSlot read) {
    uint32_t count = 0;
    ReadU32LE(file, &count);
    for (uint32_t i = 0; i < count; ++i) {
        IKSerializable* object = nullptr;
        IKFile_ReadObjectRef(file, &object);
        const uint32_t index = (state->*add)(object);
        (state->*read)(file, IKGameObject::kGameStructureBlock, index);
    }
}

// One list of the level part: per entry its reference and its end offset; an entry whose object the
// list already holds is skipped (Seek to the end offset), the others are added and read.
template <class T>
void LoadLevelList(CKGameState* state, IKFile* file, const TVector<T*, 8>& list, AddSlot add, ReadSlot read) {
    uint32_t count = 0;
    ReadU32LE(file, &count);
    while (count-- != 0) {
        IKSerializable* object = nullptr;
        IKFile_ReadObjectRef(file, &object);
        uint32_t end = 0;
        ReadU32LE(file, &end);
        if (Contains(list, object)) {
            file->Seek(static_cast<int32_t>(end), kSeekSet);
            continue;
        }
        const uint32_t index = (state->*add)(object);
        (state->*read)(file, K_LEVEL_PLATEFORMS, index);
    }
}

}  // namespace

// The constructor inlined in CKGameState_Create 0x3dd08: +0x18, +0x1c, the nine lists, +0x8c.
CKGameState::CKGameState() {
    m_pGameStructure = nullptr;
    m_pGameSpawnPoint = nullptr;
    ClearVector(&m_vpStages);
    ClearVector(&m_vbCinematicStates);
    ClearVector(&m_vpModules);
    ClearVector(&m_vbModuleStates);
    ClearVector(&m_vbUnk50);
    ClearVector(&m_vpUnk5c);
    ClearVector(&m_vbUnk68);
    ClearVector(&m_vpUnk74);
    ClearVector(&m_vbUnk80);
    m_pUnk8c = nullptr;
}

// 0x0003f2d8 CKGameState_InitGameData. The old blocks are not freed; the lengths are not reset.
void CKGameState::InitializeGameData() {
    IKGameObject::InitializeGameData();
    m_pGameStructure = nullptr;
    GameVector_Reserve(&m_vpStages);
    GameVector_Reserve(&m_vbCinematicStates);
    GameVector_Reserve(&m_vpModules);
    GameVector_Reserve(&m_vbModuleStates);
    GameVector_Reserve(&m_vbUnk50);
    GameVector_Reserve(&m_vpUnk5c);
    GameVector_Reserve(&m_vbUnk68);
    GameVector_Reserve(&m_vpUnk74);
    GameVector_Reserve(&m_vbUnk80);
    m_baFlags = (m_baFlags & ~0xeu) | 2u;  // bits 1..3: 1, 0, 0
    m_pUnk8c = nullptr;
}

// 0x0003faa8 CKGameState_AddStageValue_maybe
uint32_t CKGameState::AddGameStage(IKSerializable* stage) {
    GameVector_Add(&m_vpStages, static_cast<CKGameLevel*>(stage));
    const uint32_t index = m_vbCinematicStates.m_ui32NbUsedElt;
    GameVector_Add(&m_vbCinematicStates, static_cast<uint8_t>(0));
    return index;
}

// 0x0003f8e0 CKGameState_AddModuleValue_maybe: the module, then its +0x50 and +0x44 states.
uint32_t CKGameState::AddGameModule(IKSerializable* module) {
    GameVector_Add(&m_vpModules, static_cast<CKGameModule*>(module));
    GameVector_Add(&m_vbUnk50, static_cast<uint8_t>(0));
    const uint32_t index = m_vbModuleStates.m_ui32NbUsedElt;
    GameVector_Add(&m_vbModuleStates, static_cast<uint8_t>(0));
    return index;
}

// 0x0003fbe0 CKGameState_vf90
uint32_t CKGameState::AddUnk5c(IKSerializable* object) {
    GameVector_Add(&m_vpUnk5c, object);
    const uint32_t index = m_vbUnk68.m_ui32NbUsedElt;
    GameVector_Add(&m_vbUnk68, static_cast<uint8_t>(0));
    return index;
}

// 0x0003f618 CKGameState_vf98
uint32_t CKGameState::AddUnk74(IKSerializable* object) {
    GameVector_Add(&m_vpUnk74, object);
    const uint32_t index = m_vbUnk80.m_ui32NbUsedElt;
    GameVector_Add(&m_vbUnk80, static_cast<uint8_t>(0));
    return index;
}

// 0x0003f140 CKGameState_LoadStateByte_maybe
void CKGameState::ReadStageData(IKFile* file, int32_t, uint32_t index) {
    ReadRaw(file, m_vbCinematicStates.m_pBlock + index, 1);
}

// 0x0003f098 CKGameState_ReadModuleValue_maybe
void CKGameState::ReadModuleData(IKFile* file, int32_t, uint32_t index) {
    ReadRaw(file, m_vbModuleStates.m_pBlock + index, 1);
    ReadRaw(file, m_vbUnk50.m_pBlock + index, 1);
}

// 0x0003f048 CKGameState_vfB4
void CKGameState::ReadUnk5cData(IKFile* file, int32_t, uint32_t index) { ReadRaw(file, m_vbUnk68.m_pBlock + index, 1); }

// 0x0003eff8 CKGameState_vfBC
void CKGameState::ReadUnk74Data(IKFile* file, int32_t, uint32_t index) { ReadRaw(file, m_vbUnk80.m_pBlock + index, 1); }

namespace {
// The last entry of a parallel list moves into slot `index`; the length drops by one.
template <class T>
void RemoveSwapLast(TVector<T, 8>* list, uint32_t index) {
    const uint32_t last = --list->m_ui32NbUsedElt;
    if (index != last) list->m_pBlock[index] = list->m_pBlock[last];
}

bool IsGameEntry(const void* object) { return IKGameObject_IsGameEntry(static_cast<const IKSerializable*>(object)); }
}  // namespace

// 0x0003dae8 CKGameState_vf84
void CKGameState::RemoveGameStage(uint32_t index) {
    RemoveSwapLast(&m_vpStages, index);
    RemoveSwapLast(&m_vbCinematicStates, index);
}

// 0x0003e4f0 CKGameState_vf8C
void CKGameState::RemoveGameModule(uint32_t index) {
    RemoveSwapLast(&m_vpModules, index);
    RemoveSwapLast(&m_vbModuleStates, index);
    RemoveSwapLast(&m_vbUnk50, index);
}

// 0x0003e478 CKGameState_vf94
void CKGameState::RemoveUnk5c(uint32_t index) {
    RemoveSwapLast(&m_vpUnk5c, index);
    RemoveSwapLast(&m_vbUnk68, index);
}

// 0x0003e400 CKGameState_vf9C
void CKGameState::RemoveUnk74(uint32_t index) {
    RemoveSwapLast(&m_vpUnk74, index);
    RemoveSwapLast(&m_vbUnk80, index);
}

// 0x0003e598 CKGameState_ClearLevelData_maybe
void CKGameState::DestroyLevelData() {
    for (uint32_t i = m_vpStages.m_ui32NbUsedElt; i != 0; --i) {
        if (!IsGameEntry(m_vpStages.m_pBlock[i - 1])) RemoveGameStage(i - 1);  // vt+0x84
    }
    for (uint32_t i = m_vpModules.m_ui32NbUsedElt; i != 0; --i) {
        if (!IsGameEntry(m_vpModules.m_pBlock[i - 1])) RemoveGameModule(i - 1);  // vt+0x8c
    }
    for (uint32_t i = m_vpUnk5c.m_ui32NbUsedElt; i != 0; --i) {
        if (!IsGameEntry(m_vpUnk5c.m_pBlock[i - 1])) RemoveUnk5c(i - 1);  // vt+0x94
    }
    for (uint32_t i = m_vpUnk74.m_ui32NbUsedElt; i != 0; --i) {
        if (!IsGameEntry(m_vpUnk74.m_pBlock[i - 1])) RemoveUnk74(i - 1);  // vt+0x9c
    }
    IKGameObject::DestroyLevelData();  // 0x42d90
}

// 0x0003fd18 CKGameState_Load
int32_t CKGameState::Load(IKFile* file, int32_t type) {
    IKGameObject::Load(file, type);
    if (type == K_GAME_MEMCARD) {
        IKFile_ReadRef(file, &m_pGameSpawnPoint);
        ReadRaw(file, m_vbModuleStates.m_pBlock, m_vbModuleStates.m_ui32NbUsedElt);
        ReadRaw(file, m_vbUnk50.m_pBlock, m_vbUnk50.m_ui32NbUsedElt);
        ReadRaw(file, m_vbUnk68.m_pBlock, m_vbUnk68.m_ui32NbUsedElt);
        ReadRaw(file, m_vbUnk80.m_pBlock, m_vbUnk80.m_ui32NbUsedElt);
        ReadRaw(file, m_vbCinematicStates.m_pBlock, m_vbCinematicStates.m_ui32NbUsedElt);
        return 1;
    }
    if (type == kGameStructureBlock) {
        IKFile_ReadRef(file, &m_pGameStructure);
        IKFile_ReadRef(file, &m_pGameSpawnPoint);
        LoadGameList(this, file, &CKGameState::AddGameStage, &CKGameState::ReadStageData);
        LoadGameList(this, file, &CKGameState::AddGameModule, &CKGameState::ReadModuleData);
        LoadGameList(this, file, &CKGameState::AddUnk5c, &CKGameState::ReadUnk5cData);
        LoadGameList(this, file, &CKGameState::AddUnk74, &CKGameState::ReadUnk74Data);
        IKFile_ReadRef(file, &m_pUnk8c);
        return 1;
    }
    if (type != K_LEVEL_PLATEFORMS) return 1;
    LoadLevelList(this, file, m_vpStages, &CKGameState::AddGameStage, &CKGameState::ReadStageData);
    LoadLevelList(this, file, m_vpModules, &CKGameState::AddGameModule, &CKGameState::ReadModuleData);
    LoadLevelList(this, file, m_vpUnk5c, &CKGameState::AddUnk5c, &CKGameState::ReadUnk5cData);
    LoadLevelList(this, file, m_vpUnk74, &CKGameState::AddUnk74, &CKGameState::ReadUnk74Data);
    return 1;
}

// 0x000413a8 IKGameStructure_SetCurrentSpawnPoint_maybe
void IKGameStructure::SetCurrentSpawnPoint(CKGameSpawnPoint* spawnPoint) {
    m_pCurrentSpawnPoint = spawnPoint;
    if (spawnPoint == nullptr) return;
    m_bCurrentSpawnPointGlobal = static_cast<uint8_t>(spawnPoint->m_baFlags & 1);
}

// 0x00040be8 CKDefaultGameStructure_GetCurrentLevel
CKGameLevel* IKGameStructure::GetCurrentLevel() {
    for (uint32_t i = m_vpStages.m_ui32NbUsedElt; i != 0; --i) {
        CKGameLevel* stage = m_vpStages.m_pBlock[i - 1];
        if (stage->GetMatchesThisLevel() != 0) return stage;
    }
    return nullptr;
}

// 0x000414e8 CKDefaultGameStructure_FindLevelById_maybe
CKGameLevel* IKGameStructure::FindLevelById(int32_t id) {
    for (uint32_t i = m_vpStages.m_ui32NbUsedElt; i != 0; --i) {
        CKGameLevel* stage = m_vpStages.m_pBlock[i - 1];
        if (stage->m_i32StageIndex == id) return stage;
    }
    return nullptr;
}

// ---- C1.6 gm: the game state and the game ----
#include "k2000/logic/IKPlayer.h"

// 0x0003df80 CKGameState_ApplyStateToObjects_maybe (XXL2 ApplyToStructure)
void CKGameState::ApplyToStructure() {
    for (uint32_t i = m_vpModules.m_ui32NbUsedElt; i != 0; --i) {
        CKGameModule* module = m_vpModules.m_pBlock[i - 1];
        if (module->CanRestoreActivated() != 0) module->SetActivated(m_vbModuleStates.m_pBlock[i - 1]);  // vt+0x7c, +0x70
        if (module->CanRestoreFlag2() != 0) module->SetFlag2(m_vbUnk50.m_pBlock[i - 1]);  // vt+0x88, +0x80
    }
    if (RestoresSpawnPoint() == 0) return;  // vt+0xc4
    m_pGameStructure->SetCurrentSpawnPoint(m_pGameSpawnPoint);  // vt+0x6c
    for (uint32_t i = m_vpUnk5c.m_ui32NbUsedElt; i != 0; --i) {
        IKGameObject* object = static_cast<IKGameObject*>(m_vpUnk5c.m_pBlock[i - 1]);
        object->m_baFlags = (object->m_baFlags & ~2u) | (static_cast<uint32_t>(m_vbUnk68.m_pBlock[i - 1]) << 1);
    }
    for (uint32_t i = m_vpUnk74.m_ui32NbUsedElt; i != 0; --i) {
        IKGameObject* object = static_cast<IKGameObject*>(m_vpUnk74.m_pBlock[i - 1]);
        object->m_baFlags = (object->m_baFlags & ~2u) | (static_cast<uint32_t>(m_vbUnk80.m_pBlock[i - 1]) << 1);
    }
    for (uint32_t i = m_vpStages.m_ui32NbUsedElt; i != 0; --i) {
        IKGameObject* stage = m_vpStages.m_pBlock[i - 1];
        stage->m_baFlags = (stage->m_baFlags & ~2u) | (static_cast<uint32_t>(m_vbCinematicStates.m_pBlock[i - 1]) << 1);
    }
}

// 0x0003e7f8 CKGameState_CaptureStateFromObjects_maybe (XXL2 CopyFromStructure)
void CKGameState::CopyFromStructure() {
    for (uint32_t i = m_vpModules.m_ui32NbUsedElt; i != 0; --i) {
        CKGameModule* module = m_vpModules.m_pBlock[i - 1];
        if (module->CanSaveActivated() != 0) m_vbModuleStates.m_pBlock[i - 1] = static_cast<uint8_t>(module->IsActivated());  // vt+0x78, +0x74
        if (module->CanSaveFlag2() != 0) m_vbUnk50.m_pBlock[i - 1] = static_cast<uint8_t>(module->GetFlag2());  // vt+0x8c, +0x84
    }
    if (SavesSpawnPoint() == 0) return;  // vt+0xc0
    m_pGameSpawnPoint = m_pGameStructure->m_pCurrentSpawnPoint;
    for (uint32_t i = m_vpUnk5c.m_ui32NbUsedElt; i != 0; --i)
        m_vbUnk68.m_pBlock[i - 1] = static_cast<uint8_t>((static_cast<IKGameObject*>(m_vpUnk5c.m_pBlock[i - 1])->m_baFlags >> 1) & 1u);
    for (uint32_t i = m_vpUnk74.m_ui32NbUsedElt; i != 0; --i)
        m_vbUnk80.m_pBlock[i - 1] = static_cast<uint8_t>((static_cast<IKGameObject*>(m_vpUnk74.m_pBlock[i - 1])->m_baFlags >> 1) & 1u);
    for (uint32_t i = m_vpStages.m_ui32NbUsedElt; i != 0; --i)
        m_vbCinematicStates.m_pBlock[i - 1] = static_cast<uint8_t>((m_vpStages.m_pBlock[i - 1]->m_baFlags >> 1) & 1u);
}

// 0x0003eb68 CKGameState_CopyFrom_maybe (XXL2 CopyFromState): by this state's lengths, each entry and its
// state(s) copied from the last entry down.
void CKGameState::CopyFromState(const CKGameState* other) {
    m_pGameSpawnPoint = other->m_pGameSpawnPoint;
    for (uint32_t i = m_vpStages.m_ui32NbUsedElt; i != 0; --i) {
        m_vpStages.m_pBlock[i - 1] = other->m_vpStages.m_pBlock[i - 1];
        m_vbCinematicStates.m_pBlock[i - 1] = other->m_vbCinematicStates.m_pBlock[i - 1];
    }
    for (uint32_t i = m_vpModules.m_ui32NbUsedElt; i != 0; --i) {
        m_vpModules.m_pBlock[i - 1] = other->m_vpModules.m_pBlock[i - 1];
        m_vbModuleStates.m_pBlock[i - 1] = other->m_vbModuleStates.m_pBlock[i - 1];
        m_vbUnk50.m_pBlock[i - 1] = other->m_vbUnk50.m_pBlock[i - 1];
    }
    for (uint32_t i = m_vpUnk5c.m_ui32NbUsedElt; i != 0; --i) {
        m_vpUnk5c.m_pBlock[i - 1] = other->m_vpUnk5c.m_pBlock[i - 1];
        m_vbUnk68.m_pBlock[i - 1] = other->m_vbUnk68.m_pBlock[i - 1];
    }
    for (uint32_t i = m_vpUnk74.m_ui32NbUsedElt; i != 0; --i) {
        m_vpUnk74.m_pBlock[i - 1] = other->m_vpUnk74.m_pBlock[i - 1];
        m_vbUnk80.m_pBlock[i - 1] = other->m_vbUnk80.m_pBlock[i - 1];
    }
}

// 0x00041448 CKDefaultGameStructure_vf58 (IKGameStructure's vt+0x58)
void IKGameStructure::Vf58() {
    for (uint32_t i = m_vpStages.m_ui32NbUsedElt; i != 0; --i) m_vpStages.m_pBlock[i - 1]->Vf70();
}

// 0x00041598 CKDefaultGameStructure_vf5C (IKGameStructure's vt+0x5c; XXL2 ApplyGameStateToLevel)
void IKGameStructure::ApplyGameStateToLevel() {
    if (m_pCurrentSpawnPoint == nullptr) return;
    CKGameLevel* stage = m_pCurrentSpawnPoint->m_pGameStage;
    if (stage != nullptr) stage->ApplyGameStateToLevel();  // vt+0x68
}

// 0x00040cd0 IKGameStructure_vf60
void IKGameStructure::ApplyPlayerGameState(IKPlayer* player) { player->m_pGameState->ApplyToStructure(); }

// 0x00040e68 CKDefaultGameStructure_RefreshModuleTriggerDomains_maybe
void IKGameStructure::RefreshModuleTriggerDomains() {
    for (uint32_t i = m_vpStages.m_ui32NbUsedElt; i != 0; --i) {
        CKGameLevel* stage = m_vpStages.m_pBlock[i - 1];
        const uint32_t count = stage->CountModules(nullptr);
        for (uint32_t j = count; j != 0; --j) stage->m_vpModules.m_pBlock[j - 1]->UpdateTriggerDomains();
    }
}

// 0x00041310 IKGameStructure_MarkVideoSeenInAllLevels_maybe
void IKGameStructure::SetModuleFlag2InAllLevels(const void* video) {
    for (uint32_t i = m_vpStages.m_ui32NbUsedElt; i != 0; --i) {
        CKGameLevel* stage = m_vpStages.m_pBlock[i - 1];
        if (stage == nullptr) continue;
        stage->SetModuleFlag2ById(video);
    }
}

// 0x00041da8 CKDefaultGameStructure_MarkSekensSeenInCurrentLevel_maybe
void IKGameStructure::MarkSekensSeenInCurrentLevel(const void* sekens) {
    for (uint32_t i = m_vpStages.m_ui32NbUsedElt; i != 0; --i) {
        CKGameLevel* stage = m_vpStages.m_pBlock[i - 1];
        if (stage->GetMatchesThisLevel() == 0) continue;
        if (stage != nullptr) stage->MarkSekensSeen(sekens);
        return;
    }
}
