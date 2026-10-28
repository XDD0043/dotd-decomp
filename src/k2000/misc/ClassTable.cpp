// ClassTable.cpp - class registration (replaces the 544 Register<Class>Class static constructors).
//
// Every class the EBOOT registers gets a record, as in the original: ported classes with their real
// factories, the others with factories that log "not ported yet" and return null. Creating a class
// through the registry is traced (k2000/core/Stub.h) so the boot order can be compared with the original.
#include <cstdio>

#include "Spyro2008/logic/CKS08GameManager.h"
#include "k2000/core/Stub.h"
#include "k2000/graphical/system/CVideoManager.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/logic/io/CKLoadingManager.h"
#include "k2000/logic/ui/CLocManager.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/managers/CKInput.h"
#include "k2000/managers/CKServiceManager.h"
#include "k2000/managers/CKSoundManager.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/CoreSingletons.h"
#include "k2000/render/CRenderer.h"
#include "k2000/render/CShaderManagerPSGL.h"
#include "k2000/graphical/ui/CManager2d.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/stubs/Kp3Ported.h"
#include "k2000/stubs/Kp3Stubs.h"

namespace {

const KClassInfo kClassInfo[] = {
#define DOTD_CLASS_INFO(key, name, size) {key, name, size},
#include "k2000/misc/ClassTable.inc"
#undef DOTD_CLASS_INFO
};

void TraceCreate(uint32_t key) {
    const KClassInfo* info = FindClassInfo(key);
    char event[96];
    std::snprintf(event, sizeof(event), "create %s (key 0x%x)", info != nullptr ? info->name : "?", key);
    dotd::trace::Boot(event);
}

template <uint32_t Key, IKBaseClass* (*Create)()>
IKBaseClass* TracedCreate() {
    TraceCreate(Key);
    return Create();
}

void LogNotPorted(uint32_t key, const char* what) {
    const KClassInfo* info = FindClassInfo(key);
    DOTD_LOG("class: %s of %s (key 0x%x) is not ported yet", what, info != nullptr ? info->name : "?", key);
}

template <uint32_t Key>
IKBaseClass* NotPortedCreate() {
    LogNotPorted(Key, "Create");
    return nullptr;
}
template <uint32_t Key>
void NotPortedDelete(IKBaseClass*) {
    LogNotPorted(Key, "Delete");
}
template <uint32_t Key>
IKBaseClass* NotPortedCreateArray(uint32_t, uint16_t*) {
    LogNotPorted(Key, "CreateArray");
    return nullptr;
}
template <uint32_t Key>
void NotPortedDeleteArray(IKBaseClass*) {
    LogNotPorted(Key, "DeleteArray");
}

struct Factories {
    uint32_t key;
    ClassManager::CreateFn create;
    ClassManager::DeleteFn destroy;
    ClassManager::CreateArrayFn createArray;
    ClassManager::DeleteArrayFn destroyArray;
};

const Factories kNotPorted[] = {
#define DOTD_CLASS_INFO(key, name, size) \
    {key, &NotPortedCreate<key>, &NotPortedDelete<key>, &NotPortedCreateArray<key>, &NotPortedDeleteArray<key>},
#include "k2000/misc/ClassTable.inc"
#undef DOTD_CLASS_INFO
};

// Ported classes (real or STUB classes with real factories). The array factories of the stand-ins are
// not needed by the boot path yet.
#define DOTD_IMPLEMENTED(Class, key) \
    {key, &TracedCreate<key, &Class::Create>, &Class::Delete, &NotPortedCreateArray<key>, &NotPortedDeleteArray<key>}
const Factories kImplemented[] = {
    {0x4c, &TracedCreate<0x4c, &CKGameLoop::Create>, &CKGameLoop::Delete, &CKGameLoop::CreateArray, &CKGameLoop::DeleteArray},
    DOTD_IMPLEMENTED(CKGraphic, 0x80),
    DOTD_IMPLEMENTED(CRenderer, 0x4d),
    DOTD_IMPLEMENTED(CKInput, 0x100),
    DOTD_IMPLEMENTED(CKSoundManager, 0xc0),
    DOTD_IMPLEMENTED(CKServiceManager, 0x40),
    DOTD_IMPLEMENTED(CKLoadingManager, 0x1cc),
    DOTD_IMPLEMENTED(CKSavingManager, 0x18c),
    DOTD_IMPLEMENTED(CKLevel, 0x14c),
    DOTD_IMPLEMENTED(CLocManager, 0xecc),
    DOTD_IMPLEMENTED(CVideoManager, 0x9cd),
    DOTD_IMPLEMENTED(CShaderManagerPSGL, 0x124d),
    DOTD_IMPLEMENTED(CKS08GameManager, 0x784c),
    DOTD_IMPLEMENTED(CManager2d, 0x40d),
    DOTD_IMPLEMENTED(CKSrvCollision, 0x81),
#define DOTD_KP3_STUB_FACTORIES(Class, key) \
    {key, &TracedCreate<key, &Class::Create>, &Class::Delete, &Class::CreateArray, &Class::DeleteArray},
#include "k2000/stubs/Kp3Stubs.inc"
#undef DOTD_KP3_STUB_FACTORIES
#define DOTD_KP3_PORTED_FACTORIES(Class, key) \
    {key,&TracedCreate<key, &Class::Create>, &Class::Delete, &Class::CreateArray, &Class::DeleteArray},
#include "k2000/stubs/Kp3Ported.inc"
#undef DOTD_KP3_PORTED_FACTORIES
};
#undef DOTD_IMPLEMENTED

// DEV: the classes whose Load is not ported yet, so the loader's checks can tell expected skips from
// broken ports: the placeholders, and the hand-registered boot classes until their Loads are ported
// (remove a key here when its Load is).
const uint32_t kLoadPendingKeys[] = {
#define DOTD_KP3_STUB_FACTORIES(Class, key) key,
#include "k2000/stubs/Kp3Stubs.inc"
#undef DOTD_KP3_STUB_FACTORIES
    0,  // end marker (no class has key 0), so the table is never empty
};

static_assert(sizeof(kClassInfo) / sizeof(kClassInfo[0]) == sizeof(kNotPorted) / sizeof(kNotPorted[0]), "table");

bool g_registered = false;

}  // namespace

bool ClassRegistry_IsLoadPending(uint32_t key) {
    for (uint32_t pending : kLoadPendingKeys) {
        if (pending != 0 && pending == key) return true;
    }
    return false;
}

const KClassInfo* FindClassInfo(uint32_t key) {
    for (const KClassInfo& info : kClassInfo) {
        if (info.key == key) return &info;
    }
    return nullptr;
}

void RegisterAllClasses() {
    if (g_registered) return;
    g_registered = true;
    // The unit's static initialiser (0x252b88 -> 0x252ab0) zeroes the AppConfig; it touches nothing the
    // registrations use, so running it first is equivalent.
    CoreSingletons_StaticInit();
    for (const Factories& entry : kNotPorted) {
        const Factories* use = &entry;
        for (const Factories& implemented : kImplemented) {
            if (implemented.key == entry.key) use = &implemented;
        }
        RegisterClass(static_cast<uint16_t>(ClassKeyCategory(entry.key)), static_cast<uint16_t>(ClassKeyId(entry.key)),
                      use->create, use->destroy, use->createArray, use->destroyArray);
    }
}
