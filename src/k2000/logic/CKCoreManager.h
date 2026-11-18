// CKCoreManager.h - the UUID registry, the group root, PTank callbacks and the particle update scheduler
// (key 0x24c, vtable 0xb137c8, size 0x18). Original unit: CKCoreManager.cpp. Created directly by
// CoreSingletons_Create (not through the registry); GameEngineContext +0x2c.
#pragma once
#include <cstdint>

#include "k2000/core/IKUpdatable.h"
#include "k2000/core/Layout.h"
#include "k2000/groups/IKBaseGroup.h"

class CKCoreManager : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 9)

    // A UUID hash node (0x18 bytes, from the free-list pool at 0x00ceaa70).
    struct UuidNode {
        uint32_t uuid[4];   // +0x00
        IKSerializable* object;   // +0x10
        UuidNode* next;     // +0x14
    };

    CKCoreManager();                                 // 0x0001c220 CKCoreManager_Construct
    ~CKCoreManager() override;

    // 0x0001ce38 CKCoreManager_Init_maybe: the UUID hash (97 buckets), PTank callbacks and the
    // ParticleUpdateScheduler ("ParticleUpdateThread") -> GameEngineContext +0xb4.
    void Init();
    // 0x0001cc50 ShutdownParticleUpdateScheduler_maybe (Cleanup)
    void ShutdownParticleUpdateScheduler();
    // 0x0001c610: the object registered with this UUID, or null. Bucket = XOR of the 4 words mod 97.
    IKSerializable* FindObjectByUuid(const uint32_t* uuid);
    // vt+0x58 0x0001cdf0 CKCoreManager_GetObjectByClassKey: the first object of the class with this key in the loaded
    // class table (GetObjectDatabaseInstance(engine +0x4c, key & 0x3f, key >> 6 & 0x7ff, 0)).
    IKSerializable* GetObjectByClassKey(uint32_t key);
    // 0x0001c700: registers object->GetGuid() at the head of its bucket's chain.
    void RegisterObjectUuid(IKSerializable* object);
    // 0x0001d2f8: removes the first node of object->GetGuid()'s bucket with that UUID (whatever object it
    // names) and returns it to the node pool.
    void UnregisterObjectUuid(IKSerializable* object);
    // vt+0x20 0x1cfb8 CKCoreManager_FindNonRecreableInstances: the globals of categories 2, 4 and 12.
    uint8_t FindNonRecreableInstances(int32_t category, uint32_t id, uint32_t count, void* out) override;
    void Destroy() override;  // vt+0x10 0x0001c238 CKCoreManager_Destroy
    // vt+0x24 0x0001c408 CKCoreManager_RecursiveRegistration (C2.8 save-menu): type 0 only, itself and the group root.
    void RecursiveRegistration(int32_t type) override;
    // vt+0x2c 0x0001c4a8 CKCoreManager_Load: the two references +0x10/+0x14 as one contiguous array.
    int32_t Load(IKFile* file, int32_t type) override;

    UuidNode** m_uuidBuckets;   // +0x04 new[97]
    uint32_t m_bucketCount;     // +0x08 97 (0x61)
    uint32_t m_uuidCount;       // +0x0c
    IKSerializable* m_groupRoot;      // +0x10 CKGroupRoot (4:1); XXL2 m_pGroupRoot
    IKSerializable* m_pServiceLife;   // +0x14 XXL2 m_pServiceLife (CKServiceLife_maybe: the file holds key 0x41)
};
DOTD_ASSERT_SIZE(CKCoreManager, 0x18);
DOTD_ASSERT_OFFSET(CKCoreManager, m_groupRoot, 0x10);
DOTD_ASSERT_OFFSET(CKCoreManager, m_pServiceLife, 0x14);

// 0x0001c988 Engine_ReloadLocalizedData (CKCoreManager.cpp)
void Engine_ReloadLocalizedData(CKCoreManager* core, uint8_t reload);
// 0x0001c838 Engine_UnloadLocalizedData (CKCoreManager.cpp): every module's and service's localised data
// released (the argument is not used).
void Engine_UnloadLocalizedData(CKCoreManager* core);
// 0x0001cef8 Engine_ChangeLanguage_maybe (CKCoreManager.cpp; on the load worker, LocLoadRequest kind 3):
// the localised data released, the language's GLC and the current level's LLC loaded, the language made
// current, then every module's localised data rebuilt (reload passed on).
void Engine_ChangeLanguage(CKCoreManager* core, int32_t language, uint8_t reload);


// 0x0001cb10 SetObjectActiveInContext_maybe (CKCoreManager.cpp): in a context group's bundle, `object` is woken
// (active 1) or put to sleep (0) through the life service, when it is not already in that state (its bit 0 is
// "asleep"). Nothing without a context.
void SetObjectActiveInContext(CKCoreManager* core, IKLife* object, uint32_t active, IKBaseGroup* context);
// 0x0001d1c0 SetObjectActive_maybe (CKCoreManager.cpp): `group` is woken (active 1) or put to sleep (0) in its own bundle
// (+0x24) through the life service, when it is not already in that state (its bit 0 is "asleep").
void SetObjectActive(CKCoreManager* core, IKBaseGroup* group, uint32_t active);
// 0x0001c250 SetObjectLocked (CKCoreManager.cpp): OnLock / OnUnlock on the object and bit 1 of its bit array
// follows `locked` (0 or 1).
void SetObjectLocked(CKCoreManager* core, IKLife* object, uint32_t locked);
