// CKGameLevel.cpp - reconstructed original translation unit 0x39190-0x3b4f0 (GAME_TOC1, main_toc1), 39 functions, 28 live.
// Primary class: CKGameLevel  key 0x584c  category Logic  size 0x88  vtable 0xb14768
// Other owners: CKS08GameLevel (2), CKGameModule (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x39190  CKGameLevel_Delete
//   [ ] 0x391e0  CKGameLevel_GetGameManager_maybe
//   [ ] 0x39200  RegisterCKGameLevelClass
//   [ ] 0x39278  _GLOBAL__I_39278
//   [ ] 0x39288  CKGameLevel_PlayLaunchScene
//   [ ] 0x39310  CKGameLevel_ClearGameData_maybe
//   [x] 0x39410  CKGameLevel_InitLevelData_maybe
//   [x] 0x39458  CKGameLevel_InitGameData
//   [x] 0x39558  CKGameLevel_IsCurrentLevel
//   [ ] 0x39600  CKGameLevel_PostLoad
//   [ ] 0x39628  CKGameLevel_Save
//   [ ] 0x39650  CKGameLevel_Destroy
//   [ ] 0x39678  CKS08GameLevel_ConstructBase_2_maybe  [dead]
//   [x] 0x39738  CKS08GameLevel_ConstructBase_maybe
//   [x] 0x397f8  CKGameLevel_DeleteArray
//   [ ] 0x398a0  CKGameLevel_RecursiveRegistration
//   [ ] 0x39aa8  CKGameLevel_CountModules_Arr48  [dead]
//   [ ] 0x39b28  CKGameLevel_CountModules_Arr54  [dead]
//   [x] 0x39ba8  CKGameLevel_CountModules
//   [x] 0x39c28  CKGameLevel_MarkSekensSeen_maybe
//   [ ] 0x39ca8  CKGameLevel_CountModules_Arr3c  [dead]
//   [x] 0x39d28  CKGameLevel_vf68
//   [ ] 0x39e90  CKGameLevel_CountTrackedActiveModules_maybe
//   [ ] 0x39f70  CKGameLevel_HasModuleById_Arr48_maybe  [dead]
//   [ ] 0x39fd0  CKGameLevel_IsModuleFlag2SetById_Arr48_maybe  [dead]
//   [ ] 0x3a030  CKGameLevel_IsModuleFlag2SetById_Arr54_maybe  [dead]
//   [ ] 0x3a090  CKGameLevel_CountModules_Arr48_2  [dead]
//   [ ] 0x3a110  CKGameLevel_CountModules_Arr54_2  [dead]
//   [x] 0x3a190  CKGameLevel_vf70
//   [x] 0x3a2f8  CKGameLevel_MarkVideoSeen_maybe
//   [ ] 0x3a378  CKGameLevel_CountTrackedModules_maybe
//   [x] 0x3a3e0  CKGameLevel_ClearLevelData
//   [x] 0x3a718  CKGameLevel_CreateArray
//   [x] 0x3a898  CKGameLevel_Create
//   [x] 0x3a970  CKGameLevel_Load
//   [x] 0x3b410  CKGameModule_Delete
//   [ ] 0x3b460  CKGameModule_IsCurrentLevel
//   [ ] 0x3b4c8  FUN_0003b4c8  [dead]
//   [ ] 0x3b4e8  FUN_0003b4e8  [dead]
//
//   [ ] 0x994ac8  CKGameLevel_IsKindOfClass  [inline]
//   [x] 0x994af0  CKGameLevel_GetClassType  [inline]
//   [x] 0x994af8  CKGameLevel_GetClassID  [inline]
//   [ ] 0x994b00  CKGameLevel_Destructor  [inline]
//   [ ] 0x994bf0  CKGameLevel_DeletingDestructor  [inline]
#include "k2000/logic/CKGameLevel.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/logic/GameVector.h"
#include "k2000/misc/IKGameStructure.h"

void Uuid_Clear(uint8_t* uuid);  // 0x002461c0 (k2000/misc/Uuid.cpp)

namespace {

// One list of the type-8 block: the game count, then that many references from the start.
template <class T>
void LoadGlobalList(IKFile* file, TVector<T*, 8>* list, uint32_t* globalCount) {
    ReadU32LE(file, globalCount);
    const uint32_t count = *globalCount;
    if (count == 0) return;
    GameVector_Resize(list, count);
    IKFile_ReadObjectRefArray(file, reinterpret_cast<IKSerializable**>(list->m_pBlock), *globalCount);
}

// One list of the level part: the level count, then that many references after the game ones.
template <class T>
void LoadLocalList(IKFile* file, TVector<T*, 8>* list, uint32_t globalCount, uint32_t* localCount) {
    ReadU32LE(file, localCount);
    if (*localCount == 0) return;
    GameVector_Resize(list, *localCount + globalCount);
    IKFile_ReadObjectRefArray(file, reinterpret_cast<IKSerializable**>(list->m_pBlock + globalCount), *localCount);
}

}  // namespace

// 0x00039738 (Ghidra CKS08GameLevel_ConstructBase_maybe; CKGameLevel_Create 0x3a898 inlines the same).
// +0x18, +0x1c, +0x80 and +0x84 are left as they are.
CKGameLevel::CKGameLevel() {
    m_guidLevelIdentifier[0] = 0;
    m_guidLevelIdentifier[3] = 0;
    m_guidLevelIdentifier[1] = 0;
    m_guidLevelIdentifier[2] = 0;
    m_vpModules.m_ui32NbElt = 8;
    m_vpModules.m_pBlock = nullptr;
    m_vpModules.m_ui32NbUsedElt = 0;
    m_vpSpawnPoints.m_ui32NbElt = 8;
    m_vpSpawnPoints.m_pBlock = nullptr;
    m_vpSpawnPoints.m_ui32NbUsedElt = 0;
    m_vpUnk48.m_ui32NbElt = 8;
    m_vpUnk48.m_pBlock = nullptr;
    m_vpUnk48.m_ui32NbUsedElt = 0;
    m_vpUnk54.m_ui32NbElt = 8;
    m_vpUnk54.m_pBlock = nullptr;
    m_vpUnk54.m_ui32NbUsedElt = 0;
    m_ui32NbLocalUnk54 = 0;
    m_ui32NbGlobalModules = 0;
    m_ui32NbLocalModules = 0;
    m_ui32NbGlobalSpawnPoints = 0;
    m_ui32NbLocalSpawnPoints = 0;
    m_ui32NbGlobalUnk48 = 0;
    m_ui32NbLocalUnk48 = 0;
    m_ui32NbGlobalUnk54 = 0;
}

// 0x00039410 CKGameLevel_InitLevelData_maybe
void CKGameLevel::InitializeLevelData() {
    IKGameObject::InitializeLevelData();
    m_pCinematicScene = nullptr;
    m_ui32NbLocalModules = 0;
    m_ui32NbLocalSpawnPoints = 0;
    m_ui32NbLocalUnk48 = 0;
    m_ui32NbLocalUnk54 = 0;
}

namespace {
// The level part of one list removed (each removed entry replaced by the last one), the local count
// decreased per entry; with shrink, the block shrinks by 8 whenever the length falls 8 below the capacity.
template <class T>
void RemoveLevelEntries(TVector<T*, 8>* list, uint32_t* localCount, bool shrink) {
    for (uint32_t i = list->m_ui32NbUsedElt; i != 0; --i) {
        T** entry = &list->m_pBlock[i - 1];
        if (IKGameObject_IsGameEntry(reinterpret_cast<IKSerializable*>(*entry))) continue;  // single inheritance from IKGameObject
        const uint32_t last = --list->m_ui32NbUsedElt;
        if (i - 1 != last) *entry = list->m_pBlock[last];
        if (shrink) {
            int32_t capacity = static_cast<int32_t>(list->m_ui32NbElt) - 8;
            if (static_cast<int32_t>(list->m_ui32NbUsedElt) <= capacity) {
                if (capacity == 0) capacity = 8;
                list->m_pBlock = static_cast<T**>(
                    Mem_ReallocAligned16(list->m_pBlock, static_cast<uint32_t>(capacity) * static_cast<uint32_t>(sizeof(T*))));
                list->m_ui32NbElt = static_cast<uint32_t>(capacity);
            }
        }
        --*localCount;
    }
}
}  // namespace

// 0x0003a3e0 CKGameLevel_ClearLevelData (vt+0x60, IKGameObject_Destroy calls it at the level unload): the
// entries the level appended leave the four lists (the modules' block keeps its size), then IKGameObject's
// (empty).
void CKGameLevel::DestroyLevelData() {
    RemoveLevelEntries(&m_vpModules, &m_ui32NbLocalModules, false);
    RemoveLevelEntries(&m_vpSpawnPoints, &m_ui32NbLocalSpawnPoints, true);
    RemoveLevelEntries(&m_vpUnk48, &m_ui32NbLocalUnk48, true);
    RemoveLevelEntries(&m_vpUnk54, &m_ui32NbLocalUnk54, true);
    IKGameObject::DestroyLevelData();  // 0x42d90
}

// 0x00039458 CKGameLevel_InitGameData. The old blocks are not freed; the lengths are not reset.
void CKGameLevel::InitializeGameData() {
    IKGameObject::InitializeGameData();
    m_i32StageIndex = -1;
    m_pGameStructure = nullptr;
    Uuid_Clear(reinterpret_cast<uint8_t*>(m_guidLevelIdentifier));
    GameVector_Reserve(&m_vpModules);
    GameVector_Reserve(&m_vpSpawnPoints);
    GameVector_Reserve(&m_vpUnk48);
    GameVector_Reserve(&m_vpUnk54);
    m_ui32NbGlobalUnk54 = 0;
    m_pUnk84 = nullptr;
    m_ui32NbGlobalModules = 0;
    m_ui32NbGlobalSpawnPoints = 0;
    m_ui32NbGlobalUnk48 = 0;
}

// 0x0003a970 CKGameLevel_Load
int32_t CKGameLevel::Load(IKFile* file, int32_t type) {
    IKGameObject::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        LoadLocalList(file, &m_vpModules, m_ui32NbGlobalModules, &m_ui32NbLocalModules);
        LoadLocalList(file, &m_vpSpawnPoints, m_ui32NbGlobalSpawnPoints, &m_ui32NbLocalSpawnPoints);
        LoadLocalList(file, &m_vpUnk48, m_ui32NbGlobalUnk48, &m_ui32NbLocalUnk48);
        LoadLocalList(file, &m_vpUnk54, m_ui32NbGlobalUnk54, &m_ui32NbLocalUnk54);
        IKFile_ReadRef(file, &m_pCinematicScene);
        return 1;
    }
    if (type != kGameStructureBlock) return 1;
    IKFile_ReadRef(file, &m_pGameStructure);
    ReadS32LE(file, &m_i32StageIndex);
    Uuid_Read(m_guidLevelIdentifier, file);
    LoadGlobalList(file, &m_vpModules, &m_ui32NbGlobalModules);
    LoadGlobalList(file, &m_vpSpawnPoints, &m_ui32NbGlobalSpawnPoints);
    LoadGlobalList(file, &m_vpUnk48, &m_ui32NbGlobalUnk48);
    LoadGlobalList(file, &m_vpUnk54, &m_ui32NbGlobalUnk54);
    IKFile_ReadRef(file, &m_pUnk84);
    return 1;
}

#include "k2000/logic/CKLevel.h"
#include "k2000/misc/Engine.h"

// 0x00039558 CKGameLevel_IsCurrentLevel
uint8_t CKGameLevel::GetMatchesThisLevel() {
    CKLevel* level = g_pEngine->m_level;
    if (Uuid_IsNull(m_guidLevelIdentifier) || level == nullptr) return 0;
    return Uuid_Equals(m_guidLevelIdentifier, level->GetGuid()) ? 1 : 0;  // vt+0x44
}

// ---- C1.6 gm: the game state applied to the level ----
#include "k2000/logic/CKGameModule.h"

// 0x00039d28 CKGameLevel_vf68 (XXL2 CKGameStage::ApplyGameStateToLevel)
void CKGameLevel::ApplyGameStateToLevel() {
    for (uint32_t i = m_vpModules.m_ui32NbUsedElt; i != 0; --i) m_vpModules.m_pBlock[i - 1]->ApplyGameStateToLevel();
    for (uint32_t i = m_vpUnk48.m_ui32NbUsedElt; i != 0; --i)
        static_cast<IKGameObject*>(m_vpUnk48.m_pBlock[i - 1])->ApplyGameStateToLevel();
    for (uint32_t i = m_vpUnk54.m_ui32NbUsedElt; i != 0; --i)
        static_cast<IKGameObject*>(m_vpUnk54.m_pBlock[i - 1])->ApplyGameStateToLevel();
}

// 0x0003a190 CKGameLevel_vf70
void CKGameLevel::Vf70() {
    for (uint32_t i = m_vpModules.m_ui32NbUsedElt; i != 0; --i) m_vpModules.m_pBlock[i - 1]->SetActivated(1);
    for (uint32_t i = m_vpUnk48.m_ui32NbUsedElt; i != 0; --i) {
        IKGameObject* object = static_cast<IKGameObject*>(m_vpUnk48.m_pBlock[i - 1]);
        object->m_baFlags = (object->m_baFlags & ~2u) | 2u;
    }
    for (uint32_t i = m_vpUnk54.m_ui32NbUsedElt; i != 0; --i) {
        IKGameObject* object = static_cast<IKGameObject*>(m_vpUnk54.m_pBlock[i - 1]);
        object->m_baFlags = (object->m_baFlags & ~2u) | 2u;
    }
}

// 0x00039ba8 CKGameLevel_CountModules
uint32_t CKGameLevel::CountModules(const uint8_t* filter) {
    if (filter == nullptr) return m_vpModules.m_ui32NbUsedElt;
    uint32_t count = 0;
    for (uint32_t i = m_vpModules.m_ui32NbUsedElt; i != 0; --i) {
        if ((m_vpModules.m_pBlock[i - 1]->m_baFlags & 1u) == *filter) ++count;
    }
    return count;
}

#include "k2000/logic/system/CKGameVideo.h"

// 0x0003a2f8 CKGameLevel_MarkVideoSeen_maybe
uint8_t CKGameLevel::SetModuleFlag2ById(const void* video) {
    for (uint32_t i = m_vpUnk48.m_ui32NbUsedElt; i != 0; --i) {
        CKGameVideo* entry = static_cast<CKGameVideo*>(m_vpUnk48.m_pBlock[i - 1]);
        if (entry->m_unk1c != video) continue;
        entry->m_baFlags = (entry->m_baFlags & 0xfffffffdu) | 2;
        return 1;
    }
    return 0;
}

// 0x00039c28 CKGameLevel_MarkSekensSeen_maybe. The +0x54 entries (CKGameSekens, a placeholder class here) are IKGameObjects
// whose +0x1c reference is the sekens; CKGameVideo has the same layout up to there.
uint8_t CKGameLevel::MarkSekensSeen(const void* sekens) {
    for (uint32_t i = m_vpUnk54.m_ui32NbUsedElt; i != 0; --i) {
        CKGameVideo* entry = static_cast<CKGameVideo*>(m_vpUnk54.m_pBlock[i - 1]);
        if (entry->m_unk1c != sekens) continue;
        entry->m_baFlags = (entry->m_baFlags & 0xfffffffdu) | 2;
        return 1;
    }
    return 0;
}
