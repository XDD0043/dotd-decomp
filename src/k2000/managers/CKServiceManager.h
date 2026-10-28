// CKServiceManager.h - owner of the services (key 0x40, vtable 0xb13b80, size 0x14). Original unit:
// CKServiceManager.cpp. Init creates every registered service (CreateServices, ported). Update is
// UpdateServiceManagerList (ported): every service's Update, most of which are still empty (C2).
#pragma once
#include "k2000/core/Layout.h"
#include "k2000/managers/IKModule.h"

class CKServiceManager : public IKModule {
public:
    DOTD_CLASS_KEY(kCategoryManager, 1)

    CKServiceManager();  // 0x00022d20 CKServiceManager_Construct
    ~CKServiceManager() override;

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00023740 DeserializeServiceManagerList

    static IKBaseClass* Create();
    static void Delete(IKBaseClass* object);

    void SetDefaultState(int32_t flag) override;       // vt+0x38 0x23a18 CKServiceManager_SetDefaultState
    void Start() override;                             // vt+0x50 0x230c8 CKServiceManager_Start
    void Restart() override;                           // vt+0x54 0x23510 CKServiceManager_Restart
    void PreRestart() override;                        // vt+0x5c 0x234a8 CKServiceManager_PreRestart
    void Vf60() override;                              // vt+0x60 0x23440 CKServiceManager_BroadcastPostReinit_maybe
    void Vf64() override;                              // vt+0x64 0x233d8 CKServiceManager_vf64
    void Stop() override;                         // vt+0x68 0x232a0
    void Pause() override;                           // vt+0x70 0x23370 CKServiceManager_Pause
    void Resume() override;                          // vt+0x78 0x23308 CKServiceManager_Resume
    void Update(IKTime* frameClock) override;        // vt+0x7c 0x23228 UpdateServiceManagerList
    int32_t InitializeModule(void* params) override;     // vt+0x94 0x22f78 CKServiceManager_InitializeModule
    void DestroyModule() override {}                      // vt+0x98 0x23578 CKServiceManager_DestroyModule
    void PreUpdate(IKTime*) override {}              // vt+0x9c 0x9930c8 (empty)
    void PostUpdate(IKTime*) override {}             // vt+0xa0 0x9930d0 (empty)
    void UpdateInitialize() override;                  // vt+0xa4 0x23130
    void PreSectorLoaded(int32_t sector) override;     // vt+0x84 0x23a90
    void SectorLoaded(int32_t sector) override;        // vt+0x88 0x238a8
    void SectorUnload(int32_t sector) override;        // vt+0x8c 0x23920
    void PostSectorUnload(int32_t sector) override;    // vt+0x90 0x23998

    // 0x00022d40 CKServiceManager_GetServiceByClassId: linear search by GetClassID.
    IKSerializable* GetServiceByClassId(uint32_t id);

    // +0x04 XXL2 m_lServiceList: the update order, linked through IKService::m_pNext (+0x04). The Load
    // rebuilds it from the file's service references, in file order.
    class IKService* m_lServiceList;
    uint32_t m_maxServiceId;           // +0x08 ClassManager_GetMaxClassId(1)
    class IKService** m_services;      // +0x0c new[], in id order
    uint32_t m_serviceCount;           // +0x10
};
DOTD_ASSERT_SIZE(CKServiceManager, 0x14);
DOTD_ASSERT_OFFSET(CKServiceManager, m_lServiceList, 0x04);

inline IKSerializable* CKServiceManager_GetServiceByClassId(CKServiceManager* manager, uint32_t id) {
    return manager->GetServiceByClassId(id);
}
