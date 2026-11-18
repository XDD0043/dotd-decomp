// CKS08AccessoryManager.h - the level's accessory configs (key 0xa20c, vtable 0xb22900, size 0x58). Original
// unit: CKS08AccessoryManager.cpp (0x2c74d0-0x2c81f0). No XXL2 class of this name. Two inlined growable
// arrays (data, capacity, count) at +0x04 and +0x10; the Load fills the first one.
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKS08AccessoryConfig.h"
#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/memory/Mem.h"

class CKS08EnemyElement;

class CKS08AccessoryManager : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x288)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0xa20c || key == 0xc; }  // vt+0x08 0x9bd0f0
    DOTD_DECLARE_FACTORIES(CKS08AccessoryManager)

    // inlined in 0x002c7df0 CKS08AccessoryManager_Create (it does not call 0x2c79b0
    // CKS08AccessoryManager_Construct, which also allocates both arrays' first blocks).
    CKS08AccessoryManager() {
        m_apConfigs = nullptr;
        m_configCapacity = 1;
        m_configCount = 0;
        m_unk14 = 1;
        m_unk10 = nullptr;
        m_unk18 = 0;
        // The probe's masks {1, 8}, sector 0, face -1, status 3 and no ground come from the embedded types' constructors;
        // the delta and the height (+0x1c / +0x20) are left to PostLoad.
    }
    // 0x002c8060 CKS08AccessoryManager_Destructor: the flying accessory block and the config array freed.
    ~CKS08AccessoryManager() override {
        if (m_unk10 != nullptr) Mem_FreeAligned16(m_unk10);
        if (m_apConfigs != nullptr) Mem_FreeAligned16(m_apConfigs);
    }
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x002c7e78 CKS08AccessoryManager_Load
    // vt+0x30 0x002c7ad0 CKS08AccessoryManager_PostLoad: the ground probe reset: delta 0.2, height 2 (TOC +0x1a44 /
    // +0x1a48), masks {1, 8}, no ground, face -1, status 3, sector 0; whatever the type.
    int32_t PostLoad(int32_t type) override;
    // vt+0x50 0x002c7b80 CKS08AccessoryManager_ResetRuntime_maybe (vt+0x54 0x2c7b30 is the reinit).
    virtual void ResetRuntime();
    virtual void ReinitRuntime();  // vt+0x54 0x002c7b30 CKS08AccessoryManager_ReinitRuntime
    // 0x002c75f0 CKS08AccessoryManager_AddActiveItem_maybe: `item` appended to the flying list (+0x10), the block grown
    // to the count + 1 (at least 1) when full.
    void AddActiveItem(CKS08EnemyElement* item);
    // vt+0x58 0x002c7818 CKS08AccessoryManager_ClearAccessories_maybe (non-virtual here; CKGrpS08Enemy_Stop): each flying
    // accessory (+0x10, +0x18 of them; null entries skipped) back to the enemy group (CKS08EnemyElement vt+0x50), the
    // block freed, the count and the block cleared (the capacity kept).
    void ClearAccessories();
    // 0x002c7598 CKS08AccessoryManager_ProbeGround_maybe: the ground under `point` (GroundProbePoints with +0x1c into
    // +0x2c, one point); returns the contact.
    const CGroundContactDatasInOut* ProbeGround(const CVector3* point);

    CKS08AccessoryConfig** m_apConfigs;  // +0x04 (Mem_AllocAligned16 / Mem_ReallocAligned16)
    uint32_t m_configCapacity;           // +0x08
    uint32_t m_configCount;              // +0x0c
    void* m_unk10;                       // +0x10 the flying accessories (data, capacity, count), runtime
    uint32_t m_unk14;                    // +0x14
    uint32_t m_unk18;                    // +0x18
    CGroundContactDatasIn m_groundIn;    // +0x1c ProbeGround's query
    CGroundContactDatasInOut m_groundContact;  // +0x2c ProbeGround's answer
};
DOTD_ASSERT_SIZE(CKS08AccessoryManager, 0x58);
DOTD_ASSERT_OFFSET(CKS08AccessoryManager, m_apConfigs, 0x04);
DOTD_ASSERT_OFFSET(CKS08AccessoryManager, m_configCount, 0x0c);
DOTD_ASSERT_OFFSET(CKS08AccessoryManager, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(CKS08AccessoryManager, m_groundIn, 0x1c);
DOTD_ASSERT_OFFSET(CKS08AccessoryManager, m_groundContact, 0x2c);
