// CKLoadingManager.cpp - reconstructed original translation unit 0x27e68-0x2b2d0 (GAME_TOC1, main_toc1), 32 functions, 30 live.
// Primary class: CKLoadingManager  key 0x1cc  category Logic  size 0x23c  vtable 0xb13dc8
// Other owners: GetObjectDatabaseInstance (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x27e68  CKLoadingManager_DecodeObjectId
//   [ ] 0x281b8  RegisterCKLoadingManagerClass
//   [ ] 0x28230  _GLOBAL__D_28230
//   [ ] 0x28240  _GLOBAL__I_28240
//   [x] 0x28250  CKLoadingManager_ReadTexture
//   [ ] 0x28308  CKLoadingManager_DeleteArray
//   [x] 0x283a8  CKLoadingManager_UnloadSector
//   [x] 0x28678  CKLoadingManager_UnloadLevel
//   [ ] 0x286a0  CKLoadingManager_Construct
//   [ ] 0x28740  CKLoadingManager_Construct_2
//   [ ] 0x287e0  CKLoadingManager_FileExists_maybe  [dead]
//   [ ] 0x28820  CKLoadingManager_GetObjectRefId
//   [x] 0x28ad8  GetObjectDatabaseInstance
//   [x] 0x28b70  CKLoadingManager_UnloadGameObjects
//   [x] 0x28e30  CKLoadingManager_Destructor
//   [ ] 0x28f08  CKLoadingManager_Destructor_2
//   [ ] 0x28fe0  CKLoadingManager_DeletingDestructor
//   [x] 0x290d0  CKLoadingManager_ReadSectorClassCounts
//   [ ] 0x29280  CKLoadingManager_CreateArray
//   [x] 0x293c0  CKLoadingManager_Create
//   [x] 0x29480  CKLoadingManager_ReadContiguousHandles
//   [x] 0x295d8  CKLoadingManager_ReadHandle
//   [x] 0x29700  CKLoadingManager_ReadLevelClassTable
//   [x] 0x29e00  CKLoadingManager_LoadKp3Stream
//   [x] 0x2a198  CKLoadingManager_LoadLevel
//   [x] 0x2a2b8  CKLoadingManager_LoadSectorFile
//   [x] 0x2a420  CKLoadingManager_LoadSector
//   [ ] 0x2a558  CKLoadingManager_LoadObjectList
//   [ ] 0x2a7c8  CKLoadingManager_LoadSavedObjects_maybe
//   [x] 0x2a868  CKLoadingManager_LoadLocFile
//   [x] 0x2ac30  CKLoadingManager_LoadGameFile
//   [ ] 0x2b2c8  FUN_0002b2c8  [dead]
//
//   [ ] 0x993af8  CKLoadingManager_GetClassID  [inline]
//   [ ] 0x993b00  CKLoadingManager_GetClassType  [inline]
//   [ ] 0x993b08  CKLoadingManager_KUInitialize  [inline]
//   [ ] 0x993b10  CKLoadingManager_KUDestroy  [inline]
//   [ ] 0x993b50  CKLoadingManager_Destroy  [inline]
//   [ ] 0x993b58  CKLoadingManager_IsKindOfClass  [inline]
//   [ ] 0x993b78  IKLoadingInterfaces_DeletingDestructor  [inline]
//   [ ] 0x993ba8  IKLoadingInterfaces_Destructor  [inline]
//   [ ] 0x993bb8  KStub_Nop_993bb8  [inline]
//   [ ] 0x993bc0  KStub_Nop_993bc0  [inline]
//   [ ] 0x993bc8  KStub_Nop_993bc8  [inline]
//   [ ] 0x993bd0  KStub_Nop_993bd0  [inline]
//   [ ] 0x993bd8  KStub_Nop_993bd8  [inline]
//   [ ] 0x993be0  KStub_ReturnM1_993be0  [inline]
#include "k2000/logic/io/CKLoadingManager.h"

#include <cstdio>
#include <vector>

#include "k2000/core/Stub.h"
#include "k2000/io/KFileSystem.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKCoreManager.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/ClassManager.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "platform/log.h"

KLoadProgress g_loadProgress = {};  // 0x00c50f24

namespace {
const char* const kLevelPrefix = "LVL";   // 0x00ac36a8
const char* const kKp3Extension = ".KP3"; // 0x00ac36b0
const char* const kGameName = "GAME";     // 0x00ac3718
const char* const kGlobalLoc = "GLC";     // 0x00ac36e8
const char* const kLevelLoc = "LLC";      // 0x00ac3708

// 0x00c29610: categories in load order. Dictionaries (9) come first so texture references resolve.
const uint32_t kCategoryLoadOrder[kCategoryCount] = {9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 10, 11, 12, 13, 14};

constexpr uint32_t kErrorFileNotFound = 0x20000;  // what LoadLevel/LoadLocFile/LoadGameFile return

// The class table's record count: the original reads it from the new[] cookie in front of
// m_pIdBundleLoad (UnloadSector); new[] of a trivial type has none here.
uint32_t s_idBundleLoadCount = 0;
// DEV: each record's array length (the class table's total count), for Kp3_ForgetLoadedObjects.
std::vector<uint16_t> s_idBundleTotals;

IKSerializable* ObjectAt(void* instances, uint32_t index, uint16_t stride) {
    return reinterpret_cast<IKSerializable*>(static_cast<uint8_t*>(instances) + static_cast<uint32_t>(index) * stride);
}

// DEV: a Global owner that does not hand its objects over (not in the original, which would crash).
void ReportProviderFailure(int32_t category, uint32_t id, uint32_t count) {
    ++Kp3_LoadCheckStats().providerFailures;
    const KClassInfo* info = FindClassInfo(MakeClassKey(static_cast<uint32_t>(category), id));
    DOTD_LOG("load: no global instance for %s (%d:%u, count %u)", info != nullptr ? info->name : "?", category, id, count);
}
void TraceLoad(const char* path, IKFile* stream) {
    char event[0x140];
    std::snprintf(event, sizeof(event), "load %s%s", path, stream != nullptr ? "" : " (not found)");
    dotd::trace::Boot(event);
}
}  // namespace

// 0x000293c0 CKLoadingManager_Create (the constructor is inlined there)
CKLoadingManager::CKLoadingManager()
    : m_pTypeBundleLoad(nullptr),
      m_pIdBundleLoad(nullptr),
      m_apKGameRegisteredInstances(nullptr),
      m_ui32KGameNbRegisteredInstances(0),
      m_i32NbLoadedInstances(0),
      m_ui32NumPointer(0),
      m_ui8NbStreams(0),
      m_i32NumCurrentLevel(0),
      m_ai8LoadedStream{-1, -1, -1, -1},
      m_eSerializationType(0),
      m_kGameGUID(),
      m_unk238(nullptr) {
    for (int32_t& state : m_aeStreamStates) state = 3;
}

IKBaseClass* CKLoadingManager::Create() {
    CKLoadingManager* manager = new CKLoadingManager();
    Engine_SetLoadingManager(manager);
    return manager;
}

void CKLoadingManager::Delete(IKBaseClass* object) { delete object; }

// 0x00028e30 CKLoadingManager_Destructor: m_unk238 released (an atomic decrement of its +4; the last
// reference calls its deleting destructor).
CKLoadingManager::~CKLoadingManager() {
    Engine_SetLoadingManager(nullptr);
    KRefCounted* object = m_unk238;
    if (object == nullptr) return;
    const uint32_t count = object->m_refCount;  // lwarx/stwcx. loop in the original
    object->m_refCount = count - 1;
    if (count == 1) delete object;  // vt+0x04
}

// 0x0002ac30 CKLoadingManager_LoadGameFile
uint32_t CKLoadingManager::LoadGameFile() {
    m_eSerializationType = K_GAME_PLATEFORMS;
    void* slot = nullptr;  // local_17c: the list cursor of a UUID group, or the out slot of a singleton
    char path[0x108];
    std::snprintf(path, sizeof(path), "%s%s", kGameName, kKp3Extension);
    KFileSystem* fileSystem = g_pEngine->m_fileSystem;
    KFileSystem_ConvertBackslashes(fileSystem, path);
    IKFile* stream = fileSystem->OpenFile(path, 0, KFileSystem::kDeviceDisc, KFileSystem::kRootData, 1, -1, 0);
    TraceLoad(path, stream);  // trace only (not in the original)
    if (stream == nullptr) return kErrorFileNotFound;  // KStub_Nop_10b60(0x20000, ...) passes it through

    uint8_t aborted = 0;
    ReadU32LE(stream, &m_ui32KGameNbRegisteredInstances);
    Uuid_Read(m_kGameGUID, stream);
    uint32_t managerId = 0;
    ReadU32LE(stream, &managerId);
    CDefaultGameManager* manager =
        static_cast<CDefaultGameManager*>(ClassRegistry_CreateObject(kCategoryLogic, managerId));
    manager->Init();  // vt+0xa0
    g_pEngine->m_gameLoop->SetGameManager(manager);
    manager->VfA4();  // vt+0xa4
    m_apKGameRegisteredInstances = static_cast<IKSerializable**>(Mem_AllocAligned16(m_ui32KGameNbRegisteredInstances * static_cast<uint32_t>(sizeof(IKSerializable*))));
    if (m_ui32KGameNbRegisteredInstances == 0) {
        fileSystem->CloseFile(stream);
        return 1;
    }

    // The object groups: UUID classes are created here; the others are globals handed over.
    uint32_t index = 0;
    do {
        if (aborted != 0 || g_pEngine->m_gameLoop->IsExitRequested() != 0) {
            m_apKGameRegisteredInstances[index] = nullptr;
            aborted = 1;
            index += 1;
            continue;
        }
        uint32_t key = 0, count = 0;
        uint8_t hasUuid = 0;
        ReadU32LE(stream, &key);
        ReadU32LE(stream, &count);
        ReadU8(stream, &hasUuid);
        const int32_t category = static_cast<int32_t>(key & 0x3f);
        const uint32_t id = (key >> 6) & 0x7ff;
        if (hasUuid != 0) {
            IKSerializable** cursor = &m_apKGameRegisteredInstances[index];
            uint16_t stride = 0;
            IKSerializable* first =
                static_cast<IKSerializable*>(g_pEngine->m_classManager->CreateObjectArray(category, id, count, &stride));
            for (uint32_t k = 0; k < count; ++k) {
                IKSerializable* object = ObjectAt(first, k, stride);
                uint32_t uuid[4] = {};
                Uuid_Read(uuid, stream);
                object->SetGuid(uuid);
                g_pEngine->m_coreManager->RegisterObjectUuid(object);
                *cursor++ = object;
            }
            slot = cursor;
            index += count;
        } else if (count == 1) {
            if (Engine_GetGlobalInstances(g_pEngine, category, id, 1, &slot) == 0) ReportProviderFailure(category, id, 1);
            // BUG(original): when the owner does not provide the object, the slot keeps its previous value.
            m_apKGameRegisteredInstances[index] = static_cast<IKSerializable*>(slot);
            index += 1;
        } else {
            slot = &m_apKGameRegisteredInstances[index];
            if (Engine_GetGlobalInstances(g_pEngine, category, id, count, &slot) == 0) ReportProviderFailure(category, id, count);
            index += count;
        }
    } while (index < m_ui32KGameNbRegisteredInstances);

    // Load every object, in list order.
    for (uint32_t i = 0; i < m_ui32KGameNbRegisteredInstances; ++i) {
        if (aborted != 0) continue;
        if (g_pEngine->m_gameLoop->IsExitRequested() != 0) {
            aborted = 1;
            continue;
        }
        IKSerializable* object = m_apKGameRegisteredInstances[i];
        uint32_t end = 0;
        ReadU32LE(stream, &end);  // original: Seek(4, SEEK_CUR) over the end offset
        ++g_loadProgress.nesting;
        if (object != nullptr) object->Load(stream, K_GAME_PLATEFORMS);  // DEV: null only after a provider failure
        --g_loadProgress.nesting;
        Kp3_CheckObjectEnd(stream, end, object);  // DEV
    }
    // Then PostLoad every object, in the same order.
    for (uint32_t i = 0; i < m_ui32KGameNbRegisteredInstances; ++i) {
        if (aborted != 0) continue;
        if (g_pEngine->m_gameLoop->IsExitRequested() != 0) {
            aborted = 1;
            continue;
        }
        if (m_apKGameRegisteredInstances[i] != nullptr) m_apKGameRegisteredInstances[i]->PostLoad(K_GAME_PLATEFORMS);
    }
    fileSystem->CloseFile(stream);
    Kp3_ReportLoadChecks(path);  // DEV
    return aborted ^ 1u;
}

// 0x0002a198 CKLoadingManager_LoadLevel
uint32_t CKLoadingManager::LoadLevel(int32_t level) {
    m_i32NumCurrentLevel = level;
    if (m_ai8LoadedStream[0] != -1) return 0;
    m_ai8LoadedStream[0] = -1;
    m_eSerializationType = K_LEVEL_PLATEFORMS;
    char path[0x108];
    std::snprintf(path, sizeof(path), "%s%03d\\%s%03d%s", kLevelPrefix, level, kLevelPrefix, level, kKp3Extension);
    KFileSystem* fileSystem = g_pEngine->m_fileSystem;
    IKFile* stream = fileSystem->OpenFile(path, 0, KFileSystem::kDeviceDisc, KFileSystem::kRootData, 1, -1, 0);
    TraceLoad(path, stream);  // trace only (not in the original)
    if (stream == nullptr) return kErrorFileNotFound;
    LoadKp3Stream(stream, -1);
    fileSystem->CloseFile(stream);
    Kp3_ReportLoadChecks(path);  // DEV
    g_loadProgress.stream = nullptr;
    return 1;
}

// 0x00029e00 CKLoadingManager_LoadKp3Stream
uint32_t CKLoadingManager::LoadKp3Stream(IKFile* stream, int8_t sector) {
    const int32_t mode = m_eSerializationType;
    stream->Seek(0, kSeekSet);
    m_i32NbLoadedInstances = 0;
    const int32_t size = static_cast<int32_t>(stream->GetSize());
    g_loadProgress.scale = 100.0f / static_cast<float>(static_cast<int64_t>(size));  // fcfid, frsp, fdivs
    if (sector == -1) {
        ReadLevelClassTable(stream);
        uint32_t skipped[2];
        stream->Read(&skipped[1], 4);
        stream->Read(&skipped[0], 4);
    } else {
        ReadSectorClassCounts(stream);
    }

    const uint32_t* order = kCategoryLoadOrder;
    for (;;) {
        Thread_YieldDuringLoad(1);
        if (g_pEngine->m_gameLoop->IsExitRequested() != 0) return 0;
        CKTypeBundleLoad& group = m_pTypeBundleLoad[*order];
        ReadU16LE(stream, sector == -1 ? &group.m_ui16NbCommunReadID : &group.m_ui16NbReadID);
        ReadU32LE(stream, &group.m_i32Seek);
        const int32_t ok = Kp3_LoadCategoryObjects(&group, stream, mode, sector, &m_i32NbLoadedInstances);
        // DEV: the category must end at its end offset.
        if (stream->Tell() != group.m_i32Seek) {
            ++Kp3_LoadCheckStats().categoryMismatches;
            DOTD_LOG("load: category %u ends at 0x%x, expected 0x%x", *order, stream->Tell(), group.m_i32Seek);
        }
        ++order;
        if (ok == 0 || order == kCategoryLoadOrder + kCategoryCount) break;
    }
    for (const uint32_t* category = kCategoryLoadOrder; category != kCategoryLoadOrder + kCategoryCount; ++category) {
        Thread_YieldDuringLoad(1);
        if (g_pEngine->m_gameLoop->IsExitRequested() != 0) return 0;
        Kp3_PostLoadCategory(&m_pTypeBundleLoad[*category], mode, sector);
    }
    return 1;
}

// 0x00029700 CKLoadingManager_ReadLevelClassTable
void CKLoadingManager::ReadLevelClassTable(IKFile* stream) {
    uint32_t headerEnd = 0;
    ReadU32LE(stream, &headerEnd);  // original: Seek(4, SEEK_CUR)
    ++g_loadProgress.nesting;
    stream->Read(&m_ui8NbStreams, 1);
    uint32_t gameUuid[4];
    Uuid_Read(gameUuid, stream);
    uint32_t classCount = 0;
    ReadU32LE(stream, &classCount);

    // The original leaves the groups' counts and the records' other fields uninitialised; they are
    // read from the file before use (the Global records' startId/stride are never used).
    m_pTypeBundleLoad = new CKTypeBundleLoad[kCategoryCount];
    for (uint32_t c = 0; c < kCategoryCount; ++c) m_pTypeBundleLoad[c].m_pID = nullptr;
    CKIDBundleLoad* cursor = new CKIDBundleLoad[classCount];
    for (uint32_t i = 0; i < classCount; ++i) {
        cursor[i].m_apGameRecreableInstances = nullptr;
        cursor[i].instances = nullptr;
    }
    m_pIdBundleLoad = cursor;
    s_idBundleLoadCount = classCount;  // the new[] count cookie in the original
    s_idBundleTotals.assign(classCount, 0);  // DEV

    ClassManager* classManager = g_pEngine->m_classManager;
    for (uint32_t category = 0; category < kCategoryCount; ++category) {
        uint16_t classesInCategory = 0;
        ReadU16LE(stream, &classesInCategory);
        if (classesInCategory == 0) continue;
        m_pTypeBundleLoad[category].m_pID = cursor;
        cursor += classesInCategory;
        for (uint32_t id = 0; id < classesInCategory; ++id) {
            CKIDBundleLoad& record = m_pTypeBundleLoad[category].m_pID[id];
            uint16_t totalCount = 0, levelCount = 0, globCount = 0;
            ReadU16LE(stream, &totalCount);
            ReadU16LE(stream, &levelCount);
            ReadU16LE(stream, &globCount);
            stream->Read(&record.m_bIsGUID, 1);
            record.m_ui16NbCommunInst = levelCount;
            record.m_ui16NbGameInst = globCount;
            record.m_ui32TyIdInst = category + id * 0x40u + static_cast<uint32_t>(levelCount) * 0x20000u;
            stream->Read(&record.m_ui8StreamType, 1);
            if ((levelCount == 0 && totalCount == 0 && globCount == 0) || record.instances != nullptr) continue;

            if (record.m_ui8StreamType == CKIDBundleLoad::kGlobal) {
                if (levelCount != 1) record.instances = Mem_AllocAligned16(levelCount * static_cast<uint32_t>(sizeof(IKSerializable*)));
                if (Engine_GetGlobalInstances(g_pEngine, static_cast<int32_t>(category), id, levelCount, &record.instances) == 0) {
                    ReportProviderFailure(static_cast<int32_t>(category), id, levelCount);
                }
                continue;
            }
            if (totalCount != 0) {
                s_idBundleTotals[static_cast<size_t>(&record - m_pIdBundleLoad)] = totalCount;  // DEV
                record.instances = classManager->CreateObjectArray(static_cast<int32_t>(category), id, totalCount, &record.m_ui16SizeOfClass);
            }
            if (record.m_bIsGUID == 0) continue;
            record.m_apGameRecreableInstances = static_cast<IKSerializable**>(Mem_AllocAligned16(globCount * static_cast<uint32_t>(sizeof(IKSerializable*))));
            for (uint32_t k = 0; k < record.m_ui16NbGameInst; ++k) {
                uint32_t uuid[4];
                Uuid_Read(uuid, stream);
                record.m_apGameRecreableInstances[k] = g_pEngine->m_coreManager->FindObjectByUuid(uuid);
            }
            for (uint32_t k = 0; k < levelCount; ++k) {
                IKSerializable* object = ObjectAt(record.instances, k, record.m_ui16SizeOfClass);
                uint32_t uuid[4];
                Uuid_Read(uuid, stream);
                object->SetGuid(uuid);
                g_pEngine->m_coreManager->RegisterObjectUuid(object);
            }
        }
    }
    --g_loadProgress.nesting;
    if (stream->Tell() != headerEnd) {  // DEV
        ++Kp3_LoadCheckStats().categoryMismatches;
        DOTD_LOG("load: class table ends at 0x%x, expected 0x%x", stream->Tell(), headerEnd);
    }
}

// 0x0002a868 CKLoadingManager_LoadLocFile
uint32_t CKLoadingManager::LoadLocFile(int32_t language, int32_t mode, int32_t level) {
    m_eSerializationType = mode;
    char path[0x108] = {};
    if (mode == K_GAME_LOCALIZATION) {
        std::snprintf(path, sizeof(path), "%02d%s%s", language, kGlobalLoc, kKp3Extension);
    } else if (mode == K_LEVEL_LOCALIZATION) {
        std::snprintf(path, sizeof(path), "%s%03d\\%02d%s%03d%s", kLevelPrefix, level, language, kLevelLoc, level,
                      kKp3Extension);
    }
    KFileSystem* fileSystem = g_pEngine->m_fileSystem;
    KFileSystem_ConvertBackslashes(fileSystem, path);
    IKFile* stream = fileSystem->OpenFile(path, 0, KFileSystem::kDeviceDisc, KFileSystem::kRootData, 1, -1, 0);
    TraceLoad(path, stream);  // trace only (not in the original)
    if (stream == nullptr) return kErrorFileNotFound;

    uint32_t aborted = 0;
    uint32_t count = 0;
    void* object = nullptr;  // local_160: not cleared between entries
    ReadU32LE(stream, &count);
    IKSerializable** objects = static_cast<IKSerializable**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(IKSerializable*))));
    for (uint32_t i = 0; i < count; ++i) {
        Thread_YieldDuringLoad(1);
        if (aborted == 0 && g_pEngine->m_gameLoop->IsExitRequested() == 0) {
            uint32_t category = 0, id = 0;
            ReadU32LE(stream, &category);
            ReadU32LE(stream, &id);
            if (Engine_GetGlobalInstances(g_pEngine, static_cast<int32_t>(category), id, 1, &object) == 0) {
                ReportProviderFailure(static_cast<int32_t>(category), id, 1);
            }
            objects[i] = static_cast<IKSerializable*>(object);
            uint32_t end = 0;
            ReadU32LE(stream, &end);  // original: Seek(4, SEEK_CUR)
            ++g_loadProgress.nesting;
            if (objects[i] != nullptr) objects[i]->Load(stream, mode);  // DEV: null only after a provider failure
            --g_loadProgress.nesting;
            Kp3_CheckObjectEnd(stream, end, objects[i]);  // DEV
            aborted = 0;
            continue;
        }
        objects[i] = nullptr;
        aborted = 1;
    }
    for (uint32_t i = 0; i < count; ++i) {
        Thread_YieldDuringLoad(1);
        if (aborted != 0) continue;
        if (g_pEngine->m_gameLoop->IsExitRequested() != 0) {
            aborted = 1;
            continue;
        }
        if (objects[i] != nullptr) objects[i]->PostLoad(mode);
    }
    Mem_FreeAligned16(objects);
    fileSystem->CloseFile(stream);
    Kp3_ReportLoadChecks(path);  // DEV
    return aborted ^ 1u;
}

// 0x000295d8 CKLoadingManager_ReadHandle
uint32_t CKLoadingManager::ReadHandle(IKFile* stream, IKSerializable** object) {
    uint32_t id = 0;
    const uint32_t got = ReadU32LE(stream, &id);
    if (id != 0xfffffffdu) {
        *object = DecodeObjectId(id);
        return got;
    }
    uint32_t uuid[4];
    Uuid_Read(uuid, stream);
    *object = g_pEngine->m_coreManager->FindObjectByUuid(uuid);
    return got;
}

// 0x00029480 CKLoadingManager_ReadContiguousHandles
uint32_t CKLoadingManager::ReadContiguousHandles(IKFile* stream, IKSerializable** objects, uint32_t count) {
    uint32_t got = 0;
    for (uint32_t i = 0; i < count; ++i) {
        uint32_t id = 0;
        got += ReadU32LE(stream, &id);
        if (id == 0xfffffffdu) {
            uint32_t uuid[4];
            Uuid_Read(uuid, stream);
            objects[i] = g_pEngine->m_coreManager->FindObjectByUuid(uuid);
        } else {
            objects[i] = DecodeObjectId(id);
        }
    }
    return got;
}

// 0x00028250 CKLoadingManager_ReadTexture
uint32_t CKLoadingManager::ReadTexture(IKFile* stream, void** texture) {
    char name[0x28];
    const uint32_t got = IKFile_ReadLengthPrefixedString(stream, name, 0x20);
    if (name[0] == 0) {
        *texture = nullptr;
        return got;
    }
    *texture = FindTextureByName(name);
    if (*texture != nullptr) TextureRef_Release(*texture);  // RwTextureDestroy: undo the lookup's reference
    return got;
}

// 0x000283a8 CKLoadingManager_UnloadSector
uint8_t CKLoadingManager::UnloadSector(int8_t sector) {
    if (m_pTypeBundleLoad == nullptr) return 1;
    if (sector == -1) {
        if (m_ai8LoadedStream[0] != -1) UnloadSector(m_ai8LoadedStream[0]);
    } else {
        m_aeStreamStates[sector] = 2;  // UNLOADING
        if (m_i32NbLoadedInstances == 0) {
            m_ai8LoadedStream[0] = -1;
            m_aeStreamStates[sector] = 3;  // UNLOADED
            return 1;
        }
    }
    for (uint32_t category = 0; category < kCategoryCount; ++category) {
        if (Kp3_UnloadCategory(&m_pTypeBundleLoad[category], sector, &m_i32NbLoadedInstances) == 0) break;
    }
    m_ai8LoadedStream[0] = -1;
    if (sector != -1) {
        m_aeStreamStates[sector] = 3;
        return 1;
    }

    // The level: every class's array freed, from the last record to the first, then the class table.
    if (m_pIdBundleLoad != nullptr) {
        ClassManager* classManager = g_pEngine->m_classManager;
        CKIDBundleLoad* record = m_pIdBundleLoad + s_idBundleLoadCount;
        while (record != m_pIdBundleLoad) {
            --record;
            if (record->instances != nullptr) {
                if (record->m_ui8StreamType != CKIDBundleLoad::kGlobal) {
                    const size_t index = static_cast<size_t>(record - m_pIdBundleLoad);  // DEV
                    const uint32_t total = index < s_idBundleTotals.size() ? s_idBundleTotals[index] : 0;
                    Kp3_ForgetLoadedObjects(record->instances, static_cast<uint8_t*>(record->instances) +
                                                                   total * static_cast<uint32_t>(record->m_ui16SizeOfClass));
                    classManager->DestroyObjectArray(static_cast<IKBaseClass*>(record->instances));
                } else if ((record->m_ui32TyIdInst >> 17) != 1) {
                    Mem_FreeAligned16(record->instances);  // the Global pointer array
                }
                record->instances = nullptr;
            }
            if (record->m_apGameRecreableInstances != nullptr) {
                Mem_FreeAligned16(record->m_apGameRecreableInstances);
                record->m_apGameRecreableInstances = nullptr;
            }
        }
        // BUG(original): m_pIdBundleLoad keeps the freed pointer (the next ReadLevelClassTable replaces it).
        delete[] m_pIdBundleLoad;
    }
    if (m_pTypeBundleLoad != nullptr) {
        for (uint32_t category = kCategoryCount; category != 0; --category) m_pTypeBundleLoad[category - 1].m_pID = nullptr;
        delete[] m_pTypeBundleLoad;
    }
    m_pTypeBundleLoad = nullptr;
    Rw_PurgeFreeLists(g_pEngine->m_graphic);
    return 1;
}

// 0x00028678 CKLoadingManager_UnloadLevel
uint8_t CKLoadingManager::UnloadLevel() { return UnloadSector(-1); }

// 0x00028ad8 GetObjectDatabaseInstance. DEV guard: without a class table, outside the category's classes (the categories'
// records lie one after the other in m_pIdBundleLoad) or without objects (the original reads through a null array
// there) the result is null.
void* GetObjectDatabaseInstance(CKLoadingManager* database, uint32_t category, uint32_t classIndex, uint32_t instance) {
    if (database == nullptr || database->m_pTypeBundleLoad == nullptr || category >= kCategoryCount) return nullptr;
    const CKTypeBundleLoad& group = database->m_pTypeBundleLoad[category];
    if (group.m_pID == nullptr) return nullptr;
    const CKIDBundleLoad* end = database->m_pIdBundleLoad + s_idBundleLoadCount;
    for (uint32_t next = category + 1; next < kCategoryCount; ++next) {
        if (database->m_pTypeBundleLoad[next].m_pID != nullptr) {
            end = database->m_pTypeBundleLoad[next].m_pID;
            break;
        }
    }
    if (group.m_pID + classIndex >= end) return nullptr;
    const CKIDBundleLoad& record = group.m_pID[classIndex];
    if (record.instances == nullptr) return nullptr;
    if (record.m_ui8StreamType != 0) return static_cast<uint8_t*>(record.instances) + instance * record.m_ui16SizeOfClass;
    if ((record.m_ui32TyIdInst >> 17) != 1) return static_cast<void**>(record.instances)[instance];
    return record.instances;
}

// 0x00028b70 CKLoadingManager_UnloadGameObjects: every GAME.KP3 object's DestroyGame (vt+0x0c), then each
// run of one class: the UUIDs of the objects whose vt+0x34 is set unregistered, and the run's array
// destroyed when its first object's vt+0x34 is set.
uint8_t CKLoadingManager::UnloadGameObjects() {
    if (m_ui32KGameNbRegisteredInstances == 0) return 1;
    for (uint32_t i = 0; i < m_ui32KGameNbRegisteredInstances; ++i) m_apKGameRegisteredInstances[i]->DestroyGame();
    uint32_t i = 0;
    while (i < m_ui32KGameNbRegisteredInstances) {
        IKSerializable* first = m_apKGameRegisteredInstances[i];
        const int32_t category = first->GetClassType();
        const int32_t id = first->GetClassID();
        for (;;) {
            IKSerializable* object = m_apKGameRegisteredInstances[i];
            ++i;
            if ((object->GetSerializationFlags() & 0xff) != 0) g_pEngine->m_coreManager->UnregisterObjectUuid(object);
            if (i >= m_ui32KGameNbRegisteredInstances) break;
            IKSerializable* next = m_apKGameRegisteredInstances[i];
            if (next->GetClassType() != category || next->GetClassID() != id) break;
        }
        if ((first->GetSerializationFlags() & 0xff) != 0) {
            Kp3_ForgetLoadedObjects(first, reinterpret_cast<const uint8_t*>(m_apKGameRegisteredInstances[i - 1]) + 1);  // DEV
            g_pEngine->m_classManager->DestroyObjectArray(first);
        }
    }
    Mem_FreeAligned16(m_apKGameRegisteredInstances);
    m_ui32KGameNbRegisteredInstances = 0;
    m_apKGameRegisteredInstances = nullptr;
    return 1;
}

// 0x000290d0 CKLoadingManager_ReadSectorClassCounts: per category (in category order) the class count,
// then per class of the level's table its object count in this sector (Global classes: 2 bytes skipped).
void CKLoadingManager::ReadSectorClassCounts(IKFile* stream) {
    for (uint32_t category = 0; category < kCategoryCount; ++category) {
        uint16_t classCount = 0;
        ReadU16LE(stream, &classCount);
        if (classCount == 0) continue;
        CKIDBundleLoad* record = m_pTypeBundleLoad[category].m_pID;
        for (uint32_t k = 0; k < classCount; ++k, ++record) {
            if (record->m_ui8StreamType == CKIDBundleLoad::kGlobal) {
                stream->Seek(2, kSeekCur);
                continue;
            }
            uint16_t count = 0;
            ReadU16LE(stream, &count);
            record->m_ui32TyIdInst = (record->m_ui32TyIdInst & 0x1ffff) | (static_cast<uint32_t>(count) << 17);
        }
    }
}

namespace {
// 0x00c50f30: the sector load in progress (LoadSector fills it, LoadSectorFile reads it).
struct SectorLoadJob {
    IKFile* stream;                      // +0x00
    CKLoadingManager* manager;           // +0x04
    uint32_t unk08;                      // +0x08
    uint8_t ok;                          // +0x0c LoadKp3Stream's result
    int8_t sector;                       // +0x0d
    void* context;                       // +0x10
    CKLoadingManager::SectorLoadedFn callback;  // +0x14
};
SectorLoadJob s_sectorLoad = {};
const char* const kSectorPrefix = "STR";  // 0x00ac36d0

// 0x0002a2b8 CKLoadingManager_LoadSectorFile: LVLlll\STRlllss.KP3. Returns 0.
uint32_t LoadSectorFile(SectorLoadJob* job) {
    const int32_t level = job->manager->m_i32NumCurrentLevel;
    char path[0x108];
    std::snprintf(path, sizeof(path), "%s%03d\\%s%03d%02d%s", kLevelPrefix, level, kSectorPrefix, level, job->sector,
                  kKp3Extension);
    KFileSystem* fileSystem = g_pEngine->m_fileSystem;
    job->stream = fileSystem->OpenFile(path, 0, KFileSystem::kDeviceDisc, KFileSystem::kRootData, 1, -1, 0);
    TraceLoad(path, job->stream);  // trace only (not in the original)
    g_loadProgress.stream = job->stream;
    if (job->stream == nullptr) {
        if (job->sector != -1) job->manager->m_aeStreamStates[job->sector] = 3;
        return 0;
    }
    job->manager->m_eSerializationType = K_LEVEL_PLATEFORMS;
    job->ok = static_cast<uint8_t>(job->manager->LoadKp3Stream(job->stream, job->sector));
    fileSystem->CloseFile(job->stream);
    Kp3_ReportLoadChecks(path);  // DEV
    g_loadProgress.stream = nullptr;
    job->stream = nullptr;
    return 0;
}
}  // namespace

// 0x0002a420 CKLoadingManager_LoadSector
uint32_t CKLoadingManager::LoadSector(int8_t sector, int32_t synchronous, void* context, SectorLoadedFn callback) {
    if (sector == -1 || m_aeStreamStates[sector] != 3 || m_ai8LoadedStream[0] != -1) return 0;
    s_sectorLoad.ok = 0;
    s_sectorLoad.manager = this;
    s_sectorLoad.sector = sector;
    s_sectorLoad.context = context;
    s_sectorLoad.callback = callback;
    m_aeStreamStates[sector] = 0;  // LOADING
    m_ai8LoadedStream[0] = sector;
    if (synchronous == 0) return 1;
    LoadSectorFile(&s_sectorLoad);
    const uint8_t ok = s_sectorLoad.ok;
    if (ok != 0 && s_sectorLoad.sector != -1) s_sectorLoad.manager->m_aeStreamStates[s_sectorLoad.sector] = 1;  // LOADED
    if (s_sectorLoad.callback != nullptr) s_sectorLoad.callback(s_sectorLoad.context, s_sectorLoad.sector, ok);
    return 1;
}

// 0x00027e68 CKLoadingManager_DecodeObjectId (ported from the assembly)
IKSerializable* CKLoadingManager::DecodeObjectId(uint32_t id) {
    if (id == 0xffffffffu) return nullptr;
    int kind = 1;  // r27: 1 = search the GAME list only, 2 = a Global record
    CKIDBundleLoad* record = nullptr;
    if (m_eSerializationType != K_GAME_PLATEFORMS) {
        record = &m_pTypeBundleLoad[id & 0x3f].m_pID[(id >> 6) & 0x7ff];
        if (record->m_ui8StreamType != CKIDBundleLoad::kGlobal) {
            // No bounds or load-state check: the array exists before any object is loaded.
            return reinterpret_cast<IKSerializable*>(static_cast<uint8_t*>(record->instances) +
                                               (id >> 17) * static_cast<uint32_t>(record->m_ui16SizeOfClass));
        }
        kind = 2;
        if ((record->m_ui32TyIdInst >> 17) == 1) return static_cast<IKSerializable*>(record->instances);
    }
    // The GAME list: the n-th object of a contiguous run of one class.
    if (m_ui32KGameNbRegisteredInstances != 0) {
        int32_t runGroup = -1, runId = -1;
        uint32_t runIndex = 0;
        for (uint32_t i = 0; i < m_ui32KGameNbRegisteredInstances;) {
            IKSerializable* object = m_apKGameRegisteredInstances[i];
            ++i;
            ++runIndex;
            const int32_t group = object->GetClassType();
            const bool sameGroup = group == runGroup;
            runGroup = group;
            if (!sameGroup || object->GetClassID() != runId) {
                runIndex = 0;
                runGroup = object->GetClassType();
                runId = object->GetClassID();
            }
            if (static_cast<int32_t>(id & 0x3f) == runGroup && static_cast<int32_t>((id >> 6) & 0x7ff) == runId &&
                (id >> 17) == runIndex) {
                return object;
            }
        }
    }
    if (kind <= 1) return nullptr;
    if ((record->m_ui32TyIdInst >> 17) == 1) return static_cast<IKSerializable*>(record->instances);
    return static_cast<IKSerializable**>(record->instances)[id >> 17];
}
