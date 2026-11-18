// IKService.h - base of the services (key 0x1; XXL2: K/KCore/Interfaces/IKService.h). Slots +0x94..+0xa4
// are XXL2's 31..35. CKServiceManager_InitializeModule creates every registered category-1 class and calls
// InitializeService (vt+0x94).
#pragma once
#include <cstdint>

#include "k2000/core/IKUpdatable.h"

class IKService : public IKUpdatable {
public:
    // 0x00992930 IKService_DeletingDestructor / 0x00992978 IKService_Destructor: the vtables only (implicit).
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x992908 IKService_IsKindOf
        return key == 0x1 || key == 0x3fe || key == 0xc;
    }
    // XXL2: IKService also derives from CSPriorityBaseNode<IKService*>, the services' update list.
    // Every service constructor stores these first (CKSrvTrigger_Construct 0x235368: 0, 0x7fffffff,
    // then its own priority 0x82).
    IKService* m_pNext = nullptr;          // +0x04
    uint32_t m_ui32Priority = 0x7fffffff;  // +0x08

    int32_t GetSerializationFlags() override { return 0; }  // vt+0x34 0x9928e8 (KStub_Return0)

    // vt+0x94 (CKSrvCollision_InitializeService 0x191c50, CKServiceLife_InitializeService 0x1dec50, ...).
    // XXL2 returns a KError.
    virtual int32_t InitializeService() = 0;
    virtual void DestroyService() = 0;     // vt+0x98
    virtual void UpdateInitialize() {}     // vt+0x9c 0x9928e0 (empty)
    virtual void UpdateLocalizedData() {}  // vt+0xa0 (XXL2: Bool, CKUErrorReporting*; PS3 default and arguments unverified)
    virtual void DestroyLocalizedData() {} // vt+0xa4 (PS3 default unverified)
};
