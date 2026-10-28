// Kp3.cpp - reconstructed original translation unit 0x256f8-0x26648 (GAME_TOC1, main_toc1), 8 functions, 7 live.
// Primary owner: Kp3 (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x256f8  Kp3_UnloadClassObjects
//   [x] 0x259b8  Kp3_PostLoadClassObjects
//   [x] 0x25bd0  Kp3_PostLoadCategory
//   [x] 0x25d28  Kp3_UnloadCategory
//   [x] 0x25e80  Kp3_LoadClassObjects
//   [x] 0x26300  Kp3_LoadCategoryObjects
//   [ ] 0x265a0  Kp3_SortObjectListById_maybe  [dead]
//   [ ] 0x265e0  Kp3_CompareObjectIds
#include <algorithm>
#include <cstdio>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "Renderware/rpworld/RpGeometry.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKCoreManager.h"
#include "k2000/logic/io/CKLoadingManager.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "platform/log.h"

namespace {
KLoadCheckStats g_checks = {};
std::vector<KLoadReport> g_reports;
uint32_t g_geometryCursor = 0;  // DEV: the geometry read log's size at the previous report
std::map<std::string, uint32_t> g_skippedByClass;  // class name -> objects skipped to their end
std::map<std::string, uint32_t> g_skippedTotals;   // the same over every file since the start
// DEV: every object the end-offset check saw, in load order, for Kp3_DumpObjects.
std::vector<std::pair<IKSerializable*, uint32_t>> g_loadedObjects;

IKSerializable* ObjectAt(void* instances, uint32_t index, uint16_t stride) {
    return reinterpret_cast<IKSerializable*>(static_cast<uint8_t*>(instances) + static_cast<uint32_t>(index) * stride);
}

bool QuitEntered() { return g_pEngine->m_gameLoop->HasEnteredQuit() != 0; }

// DEV: the class block must end at its end offset.
void CheckClassEnd(IKFile* stream, uint32_t end, const CKIDBundleLoad* record) {
    if (stream->Tell() == end) return;
    ++g_checks.classMismatches;
    const KClassInfo* info = FindClassInfo(record->m_ui32TyIdInst & 0x1ffff);
    DOTD_LOG("load: class %s ends at 0x%x, expected 0x%x", info != nullptr ? info->name : "?", stream->Tell(), end);
}
}  // namespace

KLoadCheckStats& Kp3_LoadCheckStats() { return g_checks; }

const KLoadReport* Kp3_LoadReports(uint32_t* count) {
    *count = static_cast<uint32_t>(g_reports.size());
    return g_reports.data();
}

void Kp3_ForEachSkippedTotal(void (*visit)(const char* className, uint32_t count, void* context), void* context) {
    for (const auto& entry : g_skippedTotals) visit(entry.first.c_str(), entry.second, context);
}

void Kp3_ForgetLoadedObjects(const void* begin, const void* end) {
    const uintptr_t first = reinterpret_cast<uintptr_t>(begin), last = reinterpret_cast<uintptr_t>(end);
    g_loadedObjects.erase(std::remove_if(g_loadedObjects.begin(), g_loadedObjects.end(),
                                         [first, last](const std::pair<IKSerializable*, uint32_t>& entry) {
                                             const uintptr_t address = reinterpret_cast<uintptr_t>(entry.first);
                                             return address >= first && address < last;
                                         }),
                          g_loadedObjects.end());
}

namespace {
uint32_t g_placeholderLoads = 0;           // DEV: Loads of placeholder classes so far
uint32_t g_placeholderLoadsAtLastEnd = 0;  // ... at the previous object's end check
}  // namespace

void Kp3_NotePlaceholderLoad() { ++g_placeholderLoads; }

void Kp3_CheckObjectEnd(IKFile* stream, uint32_t end, IKSerializable* object) {
    // Placeholder Loads that ran inside this object's Load (a ported Load that hands the stream to objects
    // of classes not ported yet, e.g. CKSrvSekensor's localisation and its CKSekens): its shortfall is theirs.
    const uint32_t nestedPlaceholders = g_placeholderLoads - g_placeholderLoadsAtLastEnd;
    g_placeholderLoadsAtLastEnd = g_placeholderLoads;
    ++g_checks.objects;
    if (object == nullptr) ++g_checks.nullObjects;
    const uint32_t key = object != nullptr ? MakeClassKey(static_cast<uint32_t>(object->GetClassType()),
                                                          static_cast<uint32_t>(object->GetClassID()))
                                           : 0;
    if (object != nullptr) g_loadedObjects.emplace_back(object, key);
    if (stream->Tell() == end) return;
    ++g_checks.objectMismatches;
    const KClassInfo* info = object != nullptr ? FindClassInfo(key) : nullptr;
    const bool ported = object != nullptr && !ClassRegistry_IsLoadPending(key);
    const bool viaPlaceholders = ported && nestedPlaceholders != 0;
    if (ported && !viaPlaceholders) {
        ++g_checks.portedMismatches;
        DOTD_LOG("load: ported class %s (key 0x%x) ends at 0x%x, expected 0x%x", info != nullptr ? info->name : "?",
                 key, stream->Tell(), end);
    }
    const std::string name = std::string(info != nullptr ? info->name : "(null object)") +
                             (viaPlaceholders ? " [PORTED, via placeholders]" : ported ? " [PORTED]" : "");
    ++g_skippedByClass[name];
    ++g_skippedTotals[name];
    stream->Seek(static_cast<int32_t>(end), kSeekSet);
}

void Kp3_ReportLoadChecks(const char* file) {
    DOTD_LOG("load: %s: %u objects, %u skipped to their end offset (%u of ported classes), %u class and %u "
             "category end-offset mismatches",
             file, g_checks.objects, g_checks.objectMismatches, g_checks.portedMismatches, g_checks.classMismatches,
             g_checks.categoryMismatches);
    std::string classes;
    for (const auto& entry : g_skippedByClass) {
        if (!classes.empty()) classes += ", ";
        classes += entry.first + " " + std::to_string(entry.second);
    }
    if (!classes.empty()) DOTD_LOG("load:   skipped: %s", classes.c_str());
    if (g_checks.providerFailures != 0 || g_checks.nullObjects != 0) {
        DOTD_LOG("load:   %u provider failures, %u null objects", g_checks.providerFailures, g_checks.nullObjects);
    }
    KLoadReport report = {};
    std::snprintf(report.file, sizeof(report.file), "%s", file);
    report.stats = g_checks;
    report.geometriesBegin = g_geometryCursor;
    report.geometriesEnd = static_cast<uint32_t>(RpGeometryReadLog().size());
    g_geometryCursor = report.geometriesEnd;
    g_reports.push_back(report);
    g_skippedByClass.clear();
    g_checks = KLoadCheckStats();
}

// DEV: every object the loader saw (and not yet unloaded), in load order, with its class key (C2.4's shader test walks
// the loaded geometries).
void Kp3_ForEachLoadedObject(void (*visit)(IKSerializable* object, uint32_t classKey, void* context), void* context) {
    for (const auto& entry : g_loadedObjects) visit(entry.first, entry.second, context);
}

// DEV: writes the loaded objects in work/live_objects.py's format, for work/objects_diff.py:
//   {"tag", "native_layout", "classes": {name: {"key", "size", "objects": [[address, hexbytes], ...]}},
//    "all": [[address, name], ...]}
// "classes" holds the classes whose Load is ported, with their PS3 sizeof bytes as they are in memory
// (little-endian); "all" lists every loaded object, so pointers can be compared by target. The bytes
// only have the PS3 layout in a 32-bit build (DOTD_PS3_LAYOUT; native_layout says which).
bool Kp3_DumpObjects(const char* path) {
    std::FILE* f = std::fopen(path, "wb");
    if (f == nullptr) return false;
    std::map<std::string, std::vector<IKSerializable*>> byClass;
    std::map<std::string, uint32_t> keys;
    for (const auto& entry : g_loadedObjects) {
        const KClassInfo* info = FindClassInfo(entry.second);
        if (info == nullptr || info->size == 0 || ClassRegistry_IsLoadPending(entry.second)) continue;
        byClass[info->name].push_back(entry.first);
        keys[info->name] = entry.second;
    }
    std::fprintf(f, "{\"tag\": \"native\", \"native_layout\": %s, \"classes\": {", DOTD_PS3_LAYOUT ? "true" : "false");
    bool firstClass = true;
    for (auto& entry : byClass) {
        std::vector<IKSerializable*>& objects = entry.second;
        std::sort(objects.begin(), objects.end());
        objects.erase(std::unique(objects.begin(), objects.end()), objects.end());
        const KClassInfo* info = FindClassInfo(keys[entry.first]);
        std::fprintf(f, "%s\n\"%s\": {\"key\": \"0x%x\", \"size\": %u, \"objects\": [", firstClass ? "" : ",",
                     entry.first.c_str(), info->key, info->size);
        firstClass = false;
        for (size_t i = 0; i < objects.size(); ++i) {
            std::fprintf(f, "%s[\"0x%llx\", \"", i == 0 ? "" : ", ",
                         static_cast<unsigned long long>(reinterpret_cast<uintptr_t>(objects[i])));
            const uint8_t* bytes = reinterpret_cast<const uint8_t*>(objects[i]);
            for (uint32_t b = 0; b < info->size; ++b) std::fprintf(f, "%02x", bytes[b]);
            std::fputs("\"]", f);
        }
        std::fputs("]}", f);
    }
    std::fputs("},\n\"all\": [", f);
    for (size_t i = 0; i < g_loadedObjects.size(); ++i) {
        const KClassInfo* info = FindClassInfo(g_loadedObjects[i].second);
        std::fprintf(f, "%s[\"0x%llx\", \"%s\"]", i == 0 ? "" : ", ",
                     static_cast<unsigned long long>(reinterpret_cast<uintptr_t>(g_loadedObjects[i].first)),
                     info != nullptr ? info->name : "?");
    }
    std::fputs("]}\n", f);
    std::fclose(f);
    return true;
}

// 0x000256f8 Kp3_UnloadClassObjects: every object's Destroy (vt+0x10). Global classes: the object or
// the pointer array (the level count); the level (-1): the level's objects (UUIDs unregistered first when
// the class has them), then the GAME objects the level added data to; a sector: its objects, counting
// *loaded down (it stops when *loaded was 0).
void Kp3_UnloadClassObjects(CKIDBundleLoad* record, int8_t sector, uint32_t* loaded) {
    if (record->m_ui8StreamType == CKIDBundleLoad::kGlobal) {
        const uint32_t count = record->m_ui16NbCommunInst;
        if (count == 0) return;  // (the original reads the array's first pointer before this test)
        IKSerializable* object = count == 1 ? static_cast<IKSerializable*>(record->instances)
                                            : static_cast<IKSerializable**>(record->instances)[0];
        uint32_t i = 0;
        do {
            ++i;
            object->Destroy();
            // BUG(original): with one object the next "pointer" read is the object's second word (unused).
            if (count != 1 && i < count) object = static_cast<IKSerializable**>(record->instances)[i];
        } while (i < count);
        return;
    }
    if (sector == -1) {
        uint32_t remaining = record->m_ui16NbCommunInst;
        IKSerializable* object = static_cast<IKSerializable*>(record->instances);
        if (remaining != 0) {
            for (;;) {
                --remaining;
                if (record->m_bIsGUID != 0) g_pEngine->m_coreManager->UnregisterObjectUuid(object);
                object->Destroy();
                if (remaining == 0) break;
                object = reinterpret_cast<IKSerializable*>(reinterpret_cast<uint8_t*>(object) + record->m_ui16SizeOfClass);
            }
        }
        IKSerializable** globs = record->m_apGameRecreableInstances;
        for (uint32_t k = record->m_ui16NbGameInst; k != 0; --k) (*globs++)->Destroy();
        return;
    }
    uint32_t remaining = record->m_ui32TyIdInst >> 17;
    if (remaining == 0) return;
    IKSerializable* object = ObjectAt(record->instances, record->m_ui16NbInstOffset, record->m_ui16SizeOfClass);
    // DEV: the sector's objects are no longer loaded (Kp3_DumpObjects leaves them out).
    Kp3_ForgetLoadedObjects(object, reinterpret_cast<uint8_t*>(object) + remaining * static_cast<uint32_t>(record->m_ui16SizeOfClass));
    int32_t before = static_cast<int32_t>((*loaded)--);
    while (before > 0) {
        --remaining;
        object->Destroy();
        object = reinterpret_cast<IKSerializable*>(reinterpret_cast<uint8_t*>(object) + record->m_ui16SizeOfClass);
        if (remaining == 0) return;
        before = static_cast<int32_t>((*loaded)--);
    }
}

// 0x00025d28 Kp3_UnloadCategory. Returns 0 when a sector's objects ran out (*loaded < 1).
int32_t Kp3_UnloadCategory(CKTypeBundleLoad* group, int8_t sector, uint32_t* loaded) {
    if (sector == -1) {
        // As the load loop: the count is of the classes with objects; records without any are passed.
        uint32_t done = 0;
        CKIDBundleLoad* record = group->m_pID;
        while (done < group->m_ui16NbCommunReadID) {
            if (record->m_ui16NbCommunInst != 0 || record->m_ui16NbGameInst != 0) {
                Kp3_UnloadClassObjects(record, -1, loaded);
                ++done;
            }
            ++record;
        }
        return 1;
    }
    uint32_t done = 0;
    CKIDBundleLoad* record = group->m_pID;
    while (done < group->m_ui16NbReadID) {
        CKIDBundleLoad* current = record++;
        if ((current->m_ui32TyIdInst >> 17) == 0 || current->m_ui8StreamType == CKIDBundleLoad::kGlobal) continue;
        Kp3_UnloadClassObjects(current, sector, loaded);
        ++done;
        if (static_cast<int32_t>(*loaded) < 1) return 0;
    }
    return 1;
}

// 0x00026300 Kp3_LoadCategoryObjects. Returns 0 when a class failed after the quit request.
int32_t Kp3_LoadCategoryObjects(CKTypeBundleLoad* group, IKFile* stream, int32_t mode, int8_t sector, uint32_t* loaded) {
    if (sector == -1) {
        if (group->m_ui16NbCommunReadID == 0) return 1;
        uint32_t done = 0;
        CKIDBundleLoad* record = group->m_pID;
        do {
            Thread_YieldDuringLoad(0);
            if (record->m_ui16NbCommunInst != 0 || record->m_ui16NbGameInst != 0) {
                uint32_t classEnd = 0;
                ReadU32LE(stream, &classEnd);  // original: Seek(4, SEEK_CUR)
                ++g_loadProgress.nesting;
                const int32_t result = Kp3_LoadClassObjects(record, stream, mode, -1, loaded);
                done += static_cast<uint32_t>(result);
                if (result == -1) {
                    --g_loadProgress.nesting;
                    return 0;
                }
                --g_loadProgress.nesting;
                CheckClassEnd(stream, classEnd, record);  // DEV
            }
            ++record;
        } while (done < group->m_ui16NbCommunReadID);
        return 1;
    }
    if (group->m_ui16NbReadID == 0) return 1;
    uint32_t done = 0;
    CKIDBundleLoad* record = group->m_pID;
    do {
        Thread_YieldDuringLoad(1);
        if ((record->m_ui32TyIdInst >> 17) != 0 && record->m_ui8StreamType != CKIDBundleLoad::kGlobal) {
            uint32_t classEnd = 0;
            ReadU32LE(stream, &classEnd);  // original: Seek(4, SEEK_CUR)
            ++g_loadProgress.nesting;
            const int32_t result = Kp3_LoadClassObjects(record, stream, mode, sector, loaded);
            done += static_cast<uint32_t>(result);
            if (result == -1) {
                --g_loadProgress.nesting;
                return 0;
            }
            --g_loadProgress.nesting;
            CheckClassEnd(stream, classEnd, record);  // DEV
            ++record;
            if (group->m_ui16NbReadID <= done) return 1;
            continue;
        }
        ++record;
    } while (done < group->m_ui16NbReadID);
    return 1;
}

// 0x00025e80 Kp3_LoadClassObjects. Returns 1 when objects (or globs) were loaded, 0 when there was
// nothing, -1 when a Load failed after the quit request.
int32_t Kp3_LoadClassObjects(CKIDBundleLoad* record, IKFile* stream, int32_t mode, int8_t sector, uint32_t* loaded) {
    const uint32_t count = record->m_ui32TyIdInst >> 17;
    if (record->m_ui8StreamType == CKIDBundleLoad::kGlobal) {
        // Global: the object itself (count 1) or a pointer array. Globals do not count as loaded.
        if (count == 0) return 0;
        for (uint32_t i = 0; i < count; ++i) {
            IKSerializable* object = count == 1 ? static_cast<IKSerializable*>(record->instances)
                                          : static_cast<IKSerializable**>(record->instances)[i];
            Thread_YieldDuringLoad(1);
            uint32_t end = 0;
            ReadU32LE(stream, &end);  // original: Seek(4, SEEK_CUR)
            ++g_loadProgress.nesting;
            const int32_t result = object != nullptr ? object->Load(stream, mode) : 1;  // DEV: null after a provider failure
            if (result != 1 && QuitEntered()) return -1;
            --g_loadProgress.nesting;
            Kp3_CheckObjectEnd(stream, end, object);  // DEV
        }
        return 1;
    }

    int32_t result = 0;
    if (sector == -1) {
        ReadU16LE(stream, &record->m_ui16NbGameInst);
        uint32_t remaining = record->m_ui16NbGameInst;
        if (remaining != 0) {
            // GAME objects that this level adds data to.
            IKSerializable** globs = record->m_apGameRecreableInstances;
            do {
                --remaining;
                Thread_YieldDuringLoad(1);
                uint32_t end = 0;
                ReadU32LE(stream, &end);  // original: Seek(4, SEEK_CUR)
                ++g_loadProgress.nesting;
                IKSerializable* object = *globs++;
                const int32_t loadResult = object != nullptr ? object->Load(stream, mode) : 1;  // DEV: null = UUID miss
                // BUG(original): this return skips the nesting decrement.
                if (loadResult != 1 && QuitEntered()) return -1;
                --g_loadProgress.nesting;
                ++*loaded;
                Kp3_CheckObjectEnd(stream, end, object);  // DEV
            } while (remaining != 0);
            result = 1;
        }
    }
    ReadU16LE(stream, &record->m_ui16NbInstOffset);
    if (count == 0) return result;
    if (record->instances == nullptr) {  // DEV: a class without a factory (the PS3 would crash here too)
        DOTD_LOG("load: class 0x%x has %u objects but no instances (no factory?)", record->m_ui32TyIdInst & 0x1ffff,
                 count);
        return -1;
    }
    IKSerializable* object = ObjectAt(record->instances, record->m_ui16NbInstOffset, record->m_ui16SizeOfClass);
    for (uint32_t i = 1;; ++i) {
        Thread_YieldDuringLoad(1);
        uint32_t end = 0;
        ReadU32LE(stream, &end);  // original: Seek(4, SEEK_CUR)
        ++g_loadProgress.nesting;
        const int32_t loadResult = object->Load(stream, mode);
        if (loadResult != 1 && QuitEntered()) return -1;  // BUG(original): skips the nesting decrement
        --g_loadProgress.nesting;
        ++*loaded;
        Kp3_CheckObjectEnd(stream, end, object);  // DEV
        if (i == count) return 1;
        object = reinterpret_cast<IKSerializable*>(reinterpret_cast<uint8_t*>(object) + record->m_ui16SizeOfClass);
    }
}

// 0x00025bd0 Kp3_PostLoadCategory
void Kp3_PostLoadCategory(CKTypeBundleLoad* group, int32_t mode, int8_t sector) {
    if (sector == -1) {
        if (group->m_ui16NbCommunReadID == 0) return;
        uint32_t done = 0;
        CKIDBundleLoad* record = group->m_pID;
        do {
            Thread_YieldDuringLoad(1);
            if (record->m_ui16NbCommunInst != 0 || record->m_ui16NbGameInst != 0) {
                ++done;
                Kp3_PostLoadClassObjects(record, mode, -1);
            }
            ++record;
        } while (done < group->m_ui16NbCommunReadID);
        return;
    }
    if (group->m_ui16NbReadID == 0) return;
    uint32_t done = 0;
    CKIDBundleLoad* record = group->m_pID;
    do {
        Thread_YieldDuringLoad(1);
        if ((record->m_ui32TyIdInst >> 17) != 0 && record->m_ui8StreamType != CKIDBundleLoad::kGlobal) {
            Kp3_PostLoadClassObjects(record, mode, sector);
            ++done;
        } else if (group->m_ui16NbReadID <= done) {
            return;
        }
        ++record;
    } while (done < group->m_ui16NbReadID);
}

// 0x000259b8 Kp3_PostLoadClassObjects
void Kp3_PostLoadClassObjects(CKIDBundleLoad* record, int32_t mode, int8_t sector) {
    const uint32_t count = record->m_ui32TyIdInst >> 17;
    if (record->m_ui8StreamType == CKIDBundleLoad::kGlobal) {
        if (count == 0) return;
        for (uint32_t i = 0; i < count; ++i) {
            IKSerializable* object = count == 1 ? static_cast<IKSerializable*>(record->instances)
                                          : static_cast<IKSerializable**>(record->instances)[i];
            Thread_YieldDuringLoad(1);
            if (object != nullptr) object->PostLoad(mode);  // DEV: null after a provider failure
        }
        return;
    }
    if (sector == -1) {
        uint32_t remaining = record->m_ui16NbGameInst;
        IKSerializable** globs = record->m_apGameRecreableInstances;
        while (remaining != 0) {
            --remaining;
            Thread_YieldDuringLoad(1);
            if (*globs != nullptr) (*globs)->PostLoad(mode);  // DEV: null = UUID miss
            ++globs;
        }
    }
    if (count == 0) return;
    IKSerializable* object = ObjectAt(record->instances, record->m_ui16NbInstOffset, record->m_ui16SizeOfClass);
    for (uint32_t i = 0; i < count; ++i) {
        Thread_YieldDuringLoad(1);
        object->PostLoad(mode);
        object = reinterpret_cast<IKSerializable*>(reinterpret_cast<uint8_t*>(object) + record->m_ui16SizeOfClass);
    }
}
