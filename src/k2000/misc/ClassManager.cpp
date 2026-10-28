// ClassManager.cpp - reconstructed original translation unit 0x1aca0-0x1c1d0 (GAME_TOC1, main_toc1), 14 functions, 11 live.
// Primary owner: ClassManager (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1aca0  ClassManager_DestroyObject
//   [ ] 0x1ad78  ClassManager_GetGroupRecord_maybe  [dead]
//   [ ] 0x1ada0  ClassManager_Destructor_2  [dead]
//   [ ] 0x1b068  ClassManager_Construct_2  [dead]
//   [x] 0x1b398  ClassManager_CreateObject
//   [x] 0x1b400  ClassManager_DestroyObjectArray
//   [x] 0x1b4d8  ClassManager_CreateObjectArray
//   [x] 0x1b548  ClassManager_GetMaxClassId
//   [x] 0x1b578  ClassManager_GetObjectDebugName
//   [x] 0x1b670  ClassManager_GetClassDebugName
//   [x] 0x1b708  ClassManager_RegisterClass
//   [x] 0x1b900  ClassManager_DeletingDestructor
//   [x] 0x1bbd8  ClassManager_Destructor
//   [x] 0x1bea0  ClassManager_Construct
#include "k2000/misc/ClassManager.h"

#include <cstdio>

#include "k2000/memory/Mem.h"

namespace {
constexpr uint32_t kTableGrowStep = 20;  // records per allocation step (0x14)
char s_objectDebugName[0x68];            // 0x00c50e28
char s_classDebugName[0x6c];             // 0x00c50e90
}  // namespace

// 0x0001bea0 ClassManager_Construct
ClassManager::ClassManager() {
    for (CategoryTable& table : m_tables) {
        table.records = nullptr;
        table.count = 0;
        table.capacity = kTableGrowStep;
    }
    for (CategoryTable& table : m_tables) {
        table.capacity = kTableGrowStep;
        table.records = static_cast<ClassRecord*>(Mem_AllocAligned16(kTableGrowStep * sizeof(ClassRecord)));
    }
}

// 0x0001bbd8 ClassManager_Destructor, 0x0001b900 ClassManager_DeletingDestructor
// Frees the tables from the last category down; the capacity fields are left as they were.
ClassManager::~ClassManager() {
    for (int32_t category = kCategoryCount - 1; category >= 0; --category) {
        CategoryTable& table = m_tables[category];
        if (table.records != nullptr) Mem_FreeAligned16(table.records);
        table.records = nullptr;
        table.count = 0;
    }
}

// 0x0001b708 ClassManager_RegisterClass
void ClassManager::RegisterClass(uint16_t category, uint16_t id, CreateFn create, DeleteFn destroy,
                                 CreateArrayFn createArray, DeleteArrayFn destroyArray) {
    CategoryTable& table = m_tables[category];
    const uint32_t oldCount = table.count;
    if (oldCount <= id) {
        const uint32_t newCount = static_cast<uint32_t>(id) + 1;
        if (table.capacity < newCount) {
            const uint32_t capacity = (newCount / kTableGrowStep) * kTableGrowStep + kTableGrowStep;
            table.records = static_cast<ClassRecord*>(
                Mem_ReallocAligned16(table.records, capacity * static_cast<uint32_t>(sizeof(ClassRecord))));
            table.capacity = capacity;
        }
        table.count = newCount;
        // BUG(original): only the create pointer of the new gap records is cleared; the rest keeps
        // whatever the reallocated block held. Lookups only test the create pointer.
        for (uint32_t i = oldCount; i < table.count; ++i) table.records[i].create = nullptr;
    }
    ClassRecord& record = table.records[id];
    record.destroyArray = destroyArray;
    record.category = category;
    record.id = id;
    record.create = create;
    record.destroy = destroy;
    record.createArray = createArray;
}

// 0x0001b398 ClassManager_CreateObject. No bounds or null check, as in the original.
IKBaseClass* ClassManager::CreateObject(int32_t category, uint32_t id) { return m_tables[category].records[id].create(); }

// 0x0001aca0 ClassManager_DestroyObject
void ClassManager::DestroyObject(IKBaseClass* object) {
    const int32_t category = object->GetClassType();
    const int32_t id = object->GetClassID();
    m_tables[category].records[id].destroy(object);
}

// 0x0001b4d8 ClassManager_CreateObjectArray
IKBaseClass* ClassManager::CreateObjectArray(int32_t category, uint32_t id, uint32_t count, uint16_t* elementSize) {
    return m_tables[category].records[id].createArray(count, elementSize);
}

// 0x0001b400 ClassManager_DestroyObjectArray
void ClassManager::DestroyObjectArray(IKBaseClass* first) {
    const int32_t category = first->GetClassType();
    const int32_t id = first->GetClassID();
    m_tables[category].records[id].destroyArray(first);
}

// 0x0001b548 ClassManager_GetMaxClassId
int32_t ClassManager::GetMaxClassId(int32_t category) {
    const uint32_t count = m_tables[category].count;
    return count != 0 ? static_cast<int32_t>(count) - 1 : 0;
}

// 0x0001b578 ClassManager_GetObjectDebugName
const char* ClassManager::GetObjectDebugName(IKBaseClass* object) {
    const uint32_t category = static_cast<uint32_t>(object->GetClassType());
    const uint32_t id = static_cast<uint32_t>(object->GetClassID());
    const CategoryTable& table = m_tables[category];
    if (id < table.count && table.records[id].create != nullptr) {
        std::snprintf(s_objectDebugName, sizeof(s_objectDebugName), "Type '%d', Id '%d'", category, id);
        return s_objectDebugName;
    }
    return nullptr;
}

// 0x0001b670 ClassManager_GetClassDebugName
const char* ClassManager::GetClassDebugName(uint32_t category, uint32_t id) {
    const CategoryTable& table = m_tables[category];
    if (id < table.count && table.records[id].create != nullptr) {
        std::snprintf(s_classDebugName, sizeof(s_classDebugName), "Type '%d', Id '%d'", category, id);
        return s_classDebugName;
    }
    return nullptr;
}
