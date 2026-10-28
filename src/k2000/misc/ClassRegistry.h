// ClassRegistry.h - free functions over the engine's ClassManager (original unit Str.cpp,
// 0x10b68-0x12158), plus the static class table that replaces the original static constructors.
#pragma once
#include <cstdint>

class IKBaseClass;

// 0x00011498 ClassRegistry_CreateObjectByKey
IKBaseClass* ClassRegistry_CreateObjectByKey(uint32_t key);
// 0x00011458 ClassRegistry_CreateObject
IKBaseClass* ClassRegistry_CreateObject(int32_t category, uint32_t id);
// 0x00011420 ClassRegistry_DestroyObject
void ClassRegistry_DestroyObject(IKBaseClass* object);
// 0x000113e8 ClassRegistry_GetObjectDebugName
const char* ClassRegistry_GetObjectDebugName(IKBaseClass* object);
// 0x000113a8 ClassRegistry_GetClassDebugName
const char* ClassRegistry_GetClassDebugName(uint32_t category, uint32_t id);
// 0x00011368 ClassRegistry_GetClassDebugNameByKey
const char* ClassRegistry_GetClassDebugNameByKey(uint32_t key);
// 0x00011500 Rand_Int: the game's rand().
int32_t Rand_Int();

// ---- registration (replaces the 544 Register<Class>Class static constructors) ------------------
// The original registers every class from a static constructor before main; the first one also
// creates the core singletons (CoreSingletons.cpp). Here RegisterAllClasses() does both, in the order
// of the class table. Classes that are not ported yet are registered with a factory that logs and
// returns null (ClassTable.cpp).
void RegisterAllClasses();

// Class metadata from the binary's registry (work/class-tree.json + class-sizes.json).
struct KClassInfo {
    uint32_t key;
    const char* name;
    uint32_t size;  // PS3 sizeof, 0 = unknown
};
const KClassInfo* FindClassInfo(uint32_t key);
// DEV: whether the class's Load is not ported yet (a generated placeholder from k2000/stubs/Kp3Stubs.h,
// or a hand-registered boot class whose Load is still to do).
bool ClassRegistry_IsLoadPending(uint32_t key);
