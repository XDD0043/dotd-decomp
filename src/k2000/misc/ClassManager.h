// ClassManager.h - the class registry (k2000). Original unit: ClassManager.cpp (0x1aca0-0x1c1d0).
// One table per category (15); a class's record sits at its id. Registration happens before main
// from each class's static constructor (RegisterClass in CoreSingletons.cpp); objects are created by
// key through ClassRegistry_CreateObjectByKey (k2000/misc/ClassRegistry.h).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

// vtable 0xb137b0. Size 0xb8. Owned by the core singletons (0xceac54) and GameEngineContext +0x20.
class ClassManager {
public:
    typedef IKBaseClass* (*CreateFn)();
    typedef void (*DeleteFn)(IKBaseClass* object);
    // Returns the first element; *elementSize receives the class size when the pointer is not null.
    typedef IKBaseClass* (*CreateArrayFn)(uint32_t count, uint16_t* elementSize);
    typedef void (*DeleteArrayFn)(IKBaseClass* first);

    struct ClassRecord {           // 0x14 bytes on the PS3
        CreateFn create;           // +0x00 null = no class at this id
        DeleteFn destroy;         // +0x04
        CreateArrayFn createArray; // +0x08
        DeleteArrayFn destroyArray; // +0x0c
        uint16_t id;               // +0x10
        uint16_t category;         // +0x12
    };
    struct CategoryTable {         // 0xc bytes
        ClassRecord* records;      // +0x00 Mem_AllocAligned16, grown in steps of 20 records
        uint32_t capacity;         // +0x04
        uint32_t count;            // +0x08 highest registered id + 1
    };

    ClassManager();                                             // 0x0001bea0
    virtual ~ClassManager();                                    // vt+0x00 / +0x04  0x1bbd8 / 0x1b900
    virtual void RegisterClass(uint16_t category, uint16_t id, CreateFn create, DeleteFn destroy,
                               CreateArrayFn createArray, DeleteArrayFn destroyArray);  // vt+0x08 0x1b708

    IKBaseClass* CreateObject(int32_t category, uint32_t id);                                   // 0x1b398
    void DestroyObject(IKBaseClass* object);                                                    // 0x1aca0
    IKBaseClass* CreateObjectArray(int32_t category, uint32_t id, uint32_t count, uint16_t* elementSize);  // 0x1b4d8
    void DestroyObjectArray(IKBaseClass* first);                                                // 0x1b400
    int32_t GetMaxClassId(int32_t category);                                                 // 0x1b548
    const char* GetObjectDebugName(IKBaseClass* object);                                        // 0x1b578
    const char* GetClassDebugName(uint32_t category, uint32_t id);                           // 0x1b670

    CategoryTable m_tables[kCategoryCount];  // +0x04
};
DOTD_ASSERT_SIZE(ClassManager, 0xb8);
DOTD_ASSERT_OFFSET(ClassManager, m_tables, 0x04);
