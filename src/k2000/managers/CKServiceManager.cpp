// CKServiceManager.cpp - reconstructed original translation unit 0x22cd0-0x23ba8 (GAME_TOC1, main_toc1), 36 functions, 32 live.
// Primary class: CKServiceManager  key 0x40  category Manager  size 0x14  vtable 0xb13b80
// Other owners: UpdateServiceManagerList (1), DeserializeServiceManagerList (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x22cd0  CKServiceManager_Delete
//   [ ] 0x22d20  CKServiceManager_Construct  [dead]
//   [x] 0x22d40  CKServiceManager_GetServiceByClassId
//   [ ] 0x22e20  CKServiceManager_Save
//   [ ] 0x22e28  CKServiceManager_Construct_2  [dead]
//   [ ] 0x22e48  RegisterCKServiceManagerType
//   [ ] 0x22ec0  _GLOBAL__I_22ec0
//   [ ] 0x22ed0  CKServiceManager_DeleteArray
//   [x] 0x22f78  CKServiceManager_InitializeModule
//   [x] 0x230c8  CKServiceManager_Start
//   [x] 0x23130  CKServiceManager_UpdateInitialize
//   [ ] 0x23198  CKServiceManager_RecursiveRegistration
//   [x] 0x23228  UpdateServiceManagerList
//   [x] 0x232a0  CKServiceManager_Stop
//   [x] 0x23308  CKServiceManager_Resume
//   [x] 0x23370  CKServiceManager_Pause
//   [x] 0x233d8  CKServiceManager_vf64
//   [x] 0x23440  CKServiceManager_BroadcastPostReinit_maybe
//   [x] 0x234a8  CKServiceManager_PreRestart
//   [x] 0x23510  CKServiceManager_Restart
//   [ ] 0x23578  CKServiceManager_DestroyModule
//   [ ] 0x23640  CKServiceManager_CreateArray
//   [ ] 0x236f0  CreateCKServiceManager
//   [x] 0x23740  DeserializeServiceManagerList
//   [x] 0x238a8  CKServiceManager_SectorLoaded
//   [x] 0x23920  CKServiceManager_SectorUnload
//   [x] 0x23998  CKServiceManager_PostSectorUnload
//   [ ] 0x23a10  CKServiceManager_PostLoad
//   [x] 0x23a18  CKServiceManager_SetDefaultState
//   [x] 0x23a90  CKServiceManager_PreSectorLoaded
//   [ ] 0x23b08  CKServiceManager_Destroy
//   [ ] 0x23b10  CKServiceManager_Destructor
//   [ ] 0x23b30  CKServiceManager_Destructor_2  [dead]
//   [ ] 0x23b50  CKServiceManager_DeletingDestructor
//   [ ] 0x23b98  KStub_Return0_23b98
//   [ ] 0x23ba0  KStub_Nop_23ba0  [dead]
//
//   [ ] 0x993098  CKServiceManager_DestroyGame  [inline]
//   [ ] 0x9930a0  IKModule_vfA8  [inline]
//   [ ] 0x9930a8  IKModule_vfAC  [inline]
//   [ ] 0x9930b0  IKModule_vfB0  [inline]
//   [ ] 0x9930b8  CKServiceManager_GetClassType  [inline]
//   [ ] 0x9930c0  CKServiceManager_GetClassID  [inline]
//   [ ] 0x9930c8  CKServiceManager_PreUpdate  [inline]
//   [ ] 0x9930d0  CKServiceManager_PostUpdate  [inline]
//   [ ] 0x9930d8  CKServiceManager_IsKindOfClass  [inline]
//   [ ] 0x993110  IKModule_DeletingDestructor  [inline]
//   [ ] 0x993158  IKModule_Destructor  [inline]
#include "k2000/managers/CKServiceManager.h"

#include <cstdio>

#include "k2000/core/Stub.h"
#include "k2000/misc/ClassManager.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/io/IKFile.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/IKService.h"

// 0x00022d40 CKServiceManager_GetServiceByClassId
IKSerializable* CKServiceManager::GetServiceByClassId(uint32_t id) {
    for (uint32_t i = 0; i < m_serviceCount; ++i) {
        if (static_cast<uint32_t>(m_services[i]->GetClassID()) == id) return m_services[i];
    }
    return nullptr;
}

// 0x00022f78 CKServiceManager_InitializeModule: every registered service id, in id order, then its Init.
int32_t CKServiceManager::InitializeModule(void* /*params*/) {
    const int32_t maxId = g_pEngine->m_classManager->GetMaxClassId(kCategoryService);
    m_serviceCount = 0;
    m_maxServiceId = static_cast<uint32_t>(maxId);
    for (uint32_t id = 1; id <= m_maxServiceId && maxId != 0; ++id) {
        if (ClassRegistry_GetClassDebugName(kCategoryService, id) != nullptr) ++m_serviceCount;
    }
    m_services = new IKService*[m_serviceCount];
    uint32_t next = 0;
    for (uint32_t id = 1; id <= m_maxServiceId && maxId != 0; ++id) {
        if (ClassRegistry_GetClassDebugName(kCategoryService, id) == nullptr) continue;
        IKService* service = static_cast<IKService*>(ClassRegistry_CreateObject(kCategoryService, id));
        service->InitializeService();
        m_services[next++] = service;
    }
    char event[64];
    std::snprintf(event, sizeof(event), "CKServiceManager::CreateServices (%u services)", m_serviceCount);
    dotd::trace::Boot(event);  // trace only (not in the original)
    return 1;
}

// 0x00022d20 CKServiceManager_Construct (inlined in CreateCKServiceManager 0x236f0)
CKServiceManager::CKServiceManager() {
    m_services = nullptr;
    m_lServiceList = nullptr;
}

// 0x00023740 DeserializeServiceManagerList: the service priority list (type 0 only). Each reference
// is linked after the previous one (the first becomes the head).
int32_t CKServiceManager::Load(IKFile* file, int32_t type) {
    if (type != 0) return 1;
    uint32_t count = 0;
    ReadU32LE(file, &count);
    m_lServiceList = nullptr;
    IKService* previous = nullptr;
    while (count != 0) {
        --count;
        IKService* service = nullptr;
        IKFile_ReadRef(file, &service);
        if (previous == nullptr) {
            service->m_pNext = m_lServiceList;
            m_lServiceList = service;
        } else {
            service->m_pNext = previous->m_pNext;
            previous->m_pNext = service;
        }
        previous = service;
    }
    return 1;
}

// 0x000232a0 CKServiceManager_Stop, 0x000233d8 CKServiceManager_vf64, 0x00023920 CKServiceManager_SectorUnload and
// 0x00023998 CKServiceManager_PostSectorUnload: every service's vt+0x68 / +0x64 / +0x8c / +0x90, in list order.
void CKServiceManager::Stop() {
    for (IKService* service = m_lServiceList; service != nullptr; service = service->m_pNext) service->Stop();
}
void CKServiceManager::Vf64() {
    for (IKService* service = m_lServiceList; service != nullptr; service = service->m_pNext) service->Vf64();
}
void CKServiceManager::SectorUnload(int32_t sector) {
    for (IKService* service = m_lServiceList; service != nullptr; service = service->m_pNext) service->SectorUnload(sector);
}
void CKServiceManager::PostSectorUnload(int32_t sector) {
    for (IKService* service = m_lServiceList; service != nullptr; service = service->m_pNext) service->PostSectorUnload(sector);
}

// The broadcasts below call the same slot on every service, in list order.
// 0x00023a18 CKServiceManager_SetDefaultState (vt+0x38)
void CKServiceManager::SetDefaultState(int32_t flag) {
    for (IKService* service = m_lServiceList; service != nullptr; service = service->m_pNext) {
        service->SetDefaultState(flag);
    }
}
// 0x00023130 CKServiceManager_UpdateInitialize (vt+0xa4): every service's vt+0x9c, in list order.
void CKServiceManager::UpdateInitialize() {
    for (IKService* service = m_lServiceList; service != nullptr; service = service->m_pNext) service->UpdateInitialize();
}
// 0x000230c8 CKServiceManager_Start (vt+0x50)
void CKServiceManager::Start() {
    for (IKService* service = m_lServiceList; service != nullptr; service = service->m_pNext) service->Start();
}
// 0x00023510 CKServiceManager_Restart (vt+0x54)
void CKServiceManager::Restart() {
    for (IKService* service = m_lServiceList; service != nullptr; service = service->m_pNext) service->Restart();
}
// 0x000234a8 CKServiceManager_PreRestart (vt+0x5c)
void CKServiceManager::PreRestart() {
    for (IKService* service = m_lServiceList; service != nullptr; service = service->m_pNext) service->PreRestart();
}
// 0x00023440 CKServiceManager_BroadcastPostReinit_maybe (vt+0x60)
void CKServiceManager::Vf60() {
    for (IKService* service = m_lServiceList; service != nullptr; service = service->m_pNext) service->Vf60();
}
// 0x00023370 CKServiceManager_Pause (vt+0x70)
void CKServiceManager::Pause() {
    for (IKService* service = m_lServiceList; service != nullptr; service = service->m_pNext) service->Pause();
}
// 0x00023308 CKServiceManager_Resume (vt+0x78)
void CKServiceManager::Resume() {
    for (IKService* service = m_lServiceList; service != nullptr; service = service->m_pNext) service->Resume();
}

// 0x00023228 UpdateServiceManagerList: every service's Update (vt+0x7c), in list order.
void CKServiceManager::Update(IKTime* frameClock) {
    for (IKService* service = m_lServiceList; service != nullptr; service = service->m_pNext) service->Update(frameClock);
}

// 0x00023a90 CKServiceManager_PreSectorLoaded and 0x000238a8 CKServiceManager_SectorLoaded: every service's
// vt+0x84 / +0x88, in list order.
void CKServiceManager::PreSectorLoaded(int32_t sector) {
    for (IKService* service = m_lServiceList; service != nullptr; service = service->m_pNext) service->PreSectorLoaded(sector);
}
void CKServiceManager::SectorLoaded(int32_t sector) {
    for (IKService* service = m_lServiceList; service != nullptr; service = service->m_pNext) service->SectorLoaded(sector);
}
