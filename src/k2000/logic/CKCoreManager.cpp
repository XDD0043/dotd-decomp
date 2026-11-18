// CKCoreManager.cpp - reconstructed original translation unit 0x1c1d0-0x1d808 (GAME_TOC1, main_toc1), 40 functions, 31 live.
// Primary class: CKCoreManager  key 0x24c  category Logic  size 0x18  vtable 0xb137c8
// Other owners: Engine (3), SetObjectLocked (1), SetObjectActiveInContext (1), ShutdownParticleUpdateScheduler (1), SetObjectActive (1), Group (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x1c1d0  CKCoreManager_Delete  [platform] by design: CoreSingletons_Create makes the one instance and FindNonRecreableInstances hands it to the loader; no registry factories (gen_kp3_stubs.py PROVIDED)
//   [x] 0x1c220  CKCoreManager_Construct
//   [x] 0x1c238  CKCoreManager_Destroy
//   [x] 0x1c248  CKCoreManager_DestroyGame  (empty: the root's DestroyGame)
//   [x] 0x1c250  SetObjectLocked
//   [ ] 0x1c2e0  FUN_0001c2e0  [dead]
//   [ ] 0x1c330  FUN_0001c330  [dead]
//   [ ] 0x1c388  FUN_0001c388  [dead]
//   [x] 0x1c408  CKCoreManager_RecursiveRegistration
//   [ ] 0x1c4a0  CKCoreManager_Save
//   [x] 0x1c4a8  CKCoreManager_Load
//   [x] 0x1c550  CKCoreManager_PostLoad  (returns 1: the root's default)
//   [x] 0x1c558  CKCoreManager_vf50  (empty: its own vt+0x50 slot, not declared)
//   [x] 0x1c560  CKCoreManager_vf54  (empty: its own vt+0x54 slot, not declared)
//   [ ] 0x1c568  FUN_0001c568  [dead]
//   [ ] 0x1c570  CKCoreManager_Construct_2  [dead]
//   [ ] 0x1c588  RegisterCKCoreManagerClass
//   [ ] 0x1c600  _GLOBAL__I_1c600
//   [x] 0x1c610  CKCoreManager_FindObjectByUuid
//   [x] 0x1c700  CKCoreManager_RegisterObjectUuid
//   [x] 0x1c838  Engine_UnloadLocalizedData
//   [x] 0x1c988  Engine_ReloadLocalizedData
//   [x] 0x1cb10  SetObjectActiveInContext_maybe
//   [ ] 0x1cb68  FUN_0001cb68  [dead]
//   [x] 0x1cc50  ShutdownParticleUpdateScheduler_maybe
//   [ ] 0x1cd48  CKCoreManager_DeleteArray  [platform] by design: CoreSingletons_Create makes the one instance and FindNonRecreableInstances hands it to the loader; no registry factories (gen_kp3_stubs.py PROVIDED)
//   [x] 0x1cdf0  CKCoreManager_GetObjectByClassKey
//   [x] 0x1ce38  CKCoreManager_Init_maybe
//   [x] 0x1cef8  Engine_ChangeLanguage_maybe
//   [x] 0x1cfb8  CKCoreManager_FindNonRecreableInstances
//   [x] 0x1d1c0  SetObjectActive_maybe
//   [ ] 0x1d208  CKCoreManager_CreateArray  [platform] by design: CoreSingletons_Create makes the one instance and FindNonRecreableInstances hands it to the loader; no registry factories (gen_kp3_stubs.py PROVIDED)
//   [ ] 0x1d2b0  CKCoreManager_Create  [platform] by design: CoreSingletons_Create makes the one instance and FindNonRecreableInstances hands it to the loader; no registry factories (gen_kp3_stubs.py PROVIDED)
//   [x] 0x1d2f8  CKCoreManager_UnregisterObjectUuid
//   [ ] 0x1d460  FUN_0001d460  [dead]
//   [ ] 0x1d518  FUN_0001d518  [dead]
//   [x] 0x1d5c0  Group_TransferHook_maybe  (local copy)
//   [x] 0x1d798  CKCoreManager_DeletingDestructor
//   [x] 0x1d7d8  CKCoreManager_Destructor
//   [ ] 0x1d7f0  CKCoreManager_Destructor_2  [dead]
//
//   [ ] 0x992b90  CKCoreManager_GetClassType  [inline]
//   [ ] 0x992b98  CKCoreManager_GetClassID  [inline]
//   [ ] 0x992ba0  CKCoreManager_GetSerializationFlags  [inline]
//   [ ] 0x992ba8  CKCoreManager_IsKindOfClass  [inline]
#include "k2000/logic/CKCoreManager.h"

#include "k2000/core/Stub.h"
#include "k2000/fx/ParticleUpdateScheduler.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/managers/CKInput.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/managers/CKServiceManager.h"
#include "k2000/managers/CKSoundManager.h"
#include "k2000/services/IKService.h"
#include "k2000/logic/io/CKLoadingManager.h"
#include "k2000/logic/ui/CLocManager.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKServiceLife.h"
#include "k2000/logic/CKBundle.h"

// 0x0001c220 CKCoreManager_Construct (m_bucketCount, m_uuidCount and +0x14 are not initialised)
CKCoreManager::CKCoreManager() : m_uuidBuckets(nullptr), m_groupRoot(nullptr) {
    dotd::trace::Boot("create CKCoreManager (core singleton)");  // trace only (not in the original)
}

// 0x0001d7d8 CKCoreManager_Destructor (0x1d798 the deleting one): the vtables only (the UUID hash table and its
// nodes are not released here).
CKCoreManager::~CKCoreManager() {}

// 0x0001c238 CKCoreManager_Destroy: the group root (a level object) forgotten.
void CKCoreManager::Destroy() {
    m_groupRoot = nullptr;
}

// 0x0001c4a8 CKCoreManager_Load: every type reads the same two references (vt+0x28 of the loading
// interfaces with count 2, else a raw 8-byte Read).
int32_t CKCoreManager::Load(IKFile* file, int32_t /*type*/) {
    IKFile_ReadObjectRefArray(file, &m_groupRoot, 2);
    return 1;
}

// 0x0001ce38 CKCoreManager_Init_maybe
void CKCoreManager::Init() {
    m_uuidCount = 0;
    m_bucketCount = 0x61;
    m_uuidBuckets = new UuidNode*[0x61];
    for (uint32_t i = 0; i < 0x61; ++i) m_uuidBuckets[i] = nullptr;
    // RpPTank_InitCallbacks_maybe(PTank_InstanceAtomic 0x8bb78, PTank_SetupInstanceFormat 0x8b918): the
    // PTank render path's callbacks are fixed natively (Renderware/rpptank/RpPTankRender.cpp).
    ParticleUpdateScheduler* scheduler = new ParticleUpdateScheduler();  // operator new(0x80)
    InitializeParticleUpdateScheduler(scheduler);
    Engine_SetParticleScheduler(scheduler);
    dotd::trace::Boot("CKCoreManager::Init (UUID hash, particle scheduler: serial)");
}

// 0x0001cc50 ShutdownParticleUpdateScheduler_maybe (Cleanup): Init's counterpart. The UUID buckets, last first (the
// array's own count, 0x61): each bucket's nodes back to their pool (0x00ceaa70: here the host heap), the bucket
// cleared; the bucket array deleted; then the particle scheduler destroyed and the engine's slot cleared.
void CKCoreManager::ShutdownParticleUpdateScheduler() {
    if (m_uuidBuckets != nullptr) {
        for (uint32_t i = 0x61; i-- > 0;) {
            for (UuidNode* node = m_uuidBuckets[i]; node != nullptr;) {
                UuidNode* next = node->next;
                delete node;
                node = next;
            }
            m_uuidBuckets[i] = nullptr;
        }
        delete[] m_uuidBuckets;  // OperatorDeleteArray
    }
    m_uuidBuckets = nullptr;
    ParticleUpdateScheduler* scheduler = g_pEngine->m_particleScheduler;
    if (scheduler != nullptr) {
        ParticleUpdateScheduler_DestructBody(scheduler);  // 0xed978
        delete scheduler;                                 // OperatorDelete_Bridge
    }
    Engine_SetParticleScheduler(nullptr);
}

// 0x0001cdf0 CKCoreManager_GetObjectByClassKey
IKSerializable* CKCoreManager::GetObjectByClassKey(uint32_t key) {
    return static_cast<IKSerializable*>(GetObjectDatabaseInstance(g_pEngine->m_objectDatabase, key & 0x3f, (key >> 6) & 0x7ff, 0));
}

// 0x0001c610 CKCoreManager_FindObjectByUuid
IKSerializable* CKCoreManager::FindObjectByUuid(const uint32_t* uuid) {
    const uint32_t hash = uuid[0] ^ uuid[1] ^ uuid[2] ^ uuid[3];
    for (UuidNode* node = m_uuidBuckets[hash % m_bucketCount]; node != nullptr; node = node->next) {
        if (Uuid_Equals(node->uuid, uuid)) return node->object;
    }
    return nullptr;
}

// 0x0001c700 CKCoreManager_RegisterObjectUuid
void CKCoreManager::RegisterObjectUuid(IKSerializable* object) {
    const uint32_t* uuid = object->GetGuid();
    const uint32_t hash = uuid[0] ^ uuid[1] ^ uuid[2] ^ uuid[3];
    UuidNode** bucket = &m_uuidBuckets[hash % m_bucketCount];
    UuidNode* node = new UuidNode();  // FreeListPool at 0x00ceaa70 in the original
    node->next = nullptr;
    node->object = object;
    node->uuid[3] = uuid[3];
    node->uuid[2] = uuid[2];
    node->uuid[1] = uuid[1];
    node->uuid[0] = uuid[0];
    node->next = *bucket;
    *bucket = node;
    ++m_uuidCount;
}

// 0x0001d2f8 CKCoreManager_UnregisterObjectUuid
void CKCoreManager::UnregisterObjectUuid(IKSerializable* object) {
    const uint32_t* uuid = object->GetGuid();  // vt+0x44
    const uint32_t hash = uuid[0] ^ uuid[1] ^ uuid[2] ^ uuid[3];
    UuidNode** bucket = &m_uuidBuckets[hash % m_bucketCount];
    UuidNode* previous = nullptr;
    for (UuidNode* node = *bucket; node != nullptr; previous = node, node = node->next) {
        if (!Uuid_Equals(node->uuid, uuid)) continue;
        if (*bucket == node) {
            *bucket = node->next;
        } else {
            previous->next = node->next;
        }
        delete node;  // back to the FreeListPool at 0x00ceaa70 in the original
        --m_uuidCount;
        return;
    }
}

// 0x0001cfb8 CKCoreManager_FindNonRecreableInstances
uint8_t CKCoreManager::FindNonRecreableInstances(int32_t category, uint32_t id, uint32_t count, void* out) {
    IKSerializable** slot = static_cast<IKSerializable**>(out);
    if (category == kCategoryGroup) {
        if (id == 1) {
            *slot = m_groupRoot;
            return 1;
        }
        return 0;
    }
    if (category != kCategoryLogic) return 0;
    if (id == 5) {
        *slot = g_pEngine->m_level;
        return 1;
    }
    if (id < 6) {
        if (id == 4) return g_pEngine->m_level->FindNonRecreableInstances(kCategoryLogic, 4, count, out);
    } else {
        if (id == 9) {
            *slot = this;
            return 1;
        }
        if (id == 0x3b) {
            *slot = g_pEngine->m_locManager;
            return 1;
        }
    }
    CDefaultGameManager* manager = g_pEngine->m_gameLoop->m_gameManager;
    const int32_t managerKey = manager->GetClassID() * 0x40 + manager->GetClassType();
    if (managerKey != static_cast<int32_t>(id * 0x40 + kCategoryLogic)) {
        return manager->FindNonRecreableInstances(kCategoryLogic, id, count, out);
    }
    *slot = manager;
    return 1;
}

// 0x0001c838 Engine_UnloadLocalizedData: the modules' DestroyLocalizedData (vt+0xac: the 2D manager's
// level fonts; empty for the input and sound managers), the loc manager's text blocks (vt+0x54), then
// every service's DestroyLocalizedData (vt+0xa4) by class id.
void Engine_UnloadLocalizedData(CKCoreManager* /*core*/) {
    g_pEngine->m_graphic->DestroyLocalizedData();
    g_pEngine->m_input->DestroyLocalizedData();
    g_pEngine->m_soundManager->DestroyLocalizedData();
    g_pEngine->m_locManager->UnloadLocalizedData();
    CKServiceManager* services = g_pEngine->m_serviceManager;
    const uint32_t maxId = services->m_maxServiceId;
    if (maxId != 0xffffffffu) {
        for (uint32_t id = 0; id != maxId + 1; ++id) {
            IKService* service = static_cast<IKService*>(services->GetServiceByClassId(id));
            if (service != nullptr) service->DestroyLocalizedData();
        }
    }
}

// 0x0001cef8 Engine_ChangeLanguage_maybe
void Engine_ChangeLanguage(CKCoreManager* core, int32_t language, uint8_t reload) {
    CDefaultGameManager* manager = g_pEngine->m_gameManager;
    CLocManager* locManager = g_pEngine->m_locManager;
    Engine_UnloadLocalizedData(core);
    g_pEngine->m_objectDatabase->LoadLocFile(language, K_GAME_LOCALIZATION, -1);
    g_pEngine->m_objectDatabase->LoadLocFile(language, K_LEVEL_LOCALIZATION, manager->m_currentLevel);
    locManager->m_languageIndex = static_cast<uint16_t>(language);
    Engine_ReloadLocalizedData(core, reload);
}

// 0x0001c988 Engine_ReloadLocalizedData: every module and service rereads its localised data. The first
// argument (the core manager) is unused; reload is passed on to each module (XXL2 Bool) with 0.
void Engine_ReloadLocalizedData(CKCoreManager* /*core*/, uint8_t /*reload*/) {
    g_pEngine->m_locManager->UpdateLocalizedData();  // vt+0x50 0x36fb8 (empty)
    g_pEngine->m_graphic->UpdateLocalizedData();
    g_pEngine->m_input->UpdateLocalizedData();
    g_pEngine->m_soundManager->UpdateLocalizedData();
    CKServiceManager* services = g_pEngine->m_serviceManager;
    const uint32_t maxId = services->m_maxServiceId;
    if (maxId != 0xffffffffu) {
        for (uint32_t id = 0; id != maxId + 1; ++id) {
            IKService* service = static_cast<IKService*>(services->GetServiceByClassId(id));
            if (service != nullptr) service->UpdateLocalizedData();
        }
    }
}


// 0x0001c250 SetObjectLocked: the object's OnLock (vt+0xa8) or OnUnlock (vt+0xac), then bit 1 of its bit array.
void SetObjectLocked(CKCoreManager* /*core*/, IKLife* object, uint32_t locked) {
    if (locked == 0) {
        object->OnUnlock();
    } else {
        object->OnLock();
    }
    object->m_bitArray = (object->m_bitArray & 0xfffffffdu) | (locked << 1);
}

// 0x0001cb10 SetObjectActiveInContext_maybe
// 0x0001d1c0 SetObjectActive_maybe
void SetObjectActive(CKCoreManager* core, IKBaseGroup* group, uint32_t active) {
    if ((active & 0xff) != ((group->m_bitArray ^ 1u) & 1u)) {
        static_cast<CKServiceLife*>(core->m_pServiceLife)
            ->SetObjectActive(group, active & 0xff, static_cast<CKBundle*>(group->m_pKBundle));
    }
}

void SetObjectActiveInContext(CKCoreManager* core, IKLife* object, uint32_t active, IKBaseGroup* context) {
    if (context == nullptr) return;
    if ((active & 0xff) != (((object->m_bitArray ^ 1u) & 1u))) {
        static_cast<CKServiceLife*>(core->m_pServiceLife)
            ->SetObjectActive(object, active & 0xff, static_cast<CKBundle*>(context->m_pKBundle));
    }
}

// 0x0001c408 CKCoreManager_RecursiveRegistration (C2.8 save-menu)
#include "k2000/logic/CKSavingManager.h"
void CKCoreManager::RecursiveRegistration(int32_t type) {
    if (type != 0) return;
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
    m_groupRoot->RecursiveRegistration(0);
}
