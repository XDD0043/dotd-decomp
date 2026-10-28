// CKS08AccessoryManager.h - the level's accessory configs (key 0xa20c, vtable 0xb22900, size 0x58). Original
// unit: CKS08AccessoryManager.cpp (0x2c74d0-0x2c81f0). No XXL2 class of this name. Two inlined growable
// arrays (data, capacity, count) at +0x04 and +0x10; the Load fills the first one.
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKS08AccessoryConfig.h"
#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKS08AccessoryManager : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x288)
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
        m_unk24 = 1;
        m_unk28 = 8;
        m_unk54 = 0;
        m_unk30 = -1;
        m_unk40 = 3;
        m_unk2c = 0;
    }
    ~CKS08AccessoryManager() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x002c7e78 CKS08AccessoryManager_Load
    // vt+0x50 0x002c7b80 CKS08AccessoryManager_ResetRuntime_maybe (vt+0x54 0x2c7b30 is the reinit).
    virtual void ResetRuntime();

    CKS08AccessoryConfig** m_apConfigs;  // +0x04 (Mem_AllocAligned16 / Mem_ReallocAligned16)
    uint32_t m_configCapacity;           // +0x08
    uint32_t m_configCount;              // +0x0c
    void* m_unk10;                       // +0x10 a second array (data, capacity, count), runtime
    uint32_t m_unk14;                    // +0x14
    uint32_t m_unk18;                    // +0x18
    float m_unk1c;                       // +0x1c runtime
    float m_unk20;                       // +0x20 runtime
    int32_t m_unk24;                     // +0x24
    int32_t m_unk28;                     // +0x28
    uint32_t m_unk2c;                    // +0x2c
    int32_t m_unk30;                     // +0x30
    uint32_t m_unk34[3];                 // +0x34..+0x3f runtime
    int32_t m_unk40;                     // +0x40
    uint32_t m_unk44[4];                 // +0x44..+0x53 runtime
    uint8_t m_unk54;                     // +0x54 (+0x55..+0x57 runtime)
    uint8_t m_unk55[3];
};
DOTD_ASSERT_SIZE(CKS08AccessoryManager, 0x58);
DOTD_ASSERT_OFFSET(CKS08AccessoryManager, m_apConfigs, 0x04);
DOTD_ASSERT_OFFSET(CKS08AccessoryManager, m_configCount, 0x0c);
DOTD_ASSERT_OFFSET(CKS08AccessoryManager, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(CKS08AccessoryManager, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKS08AccessoryManager, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CKS08AccessoryManager, m_unk40, 0x40);
DOTD_ASSERT_OFFSET(CKS08AccessoryManager, m_unk54, 0x54);
