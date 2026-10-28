// PS3_CKSrvNetwork.h - the PS3 network service (key 0x601, vtable 0xb1e2e0, size 0x2c). Original units:
// PS3_CKSrvNetwork.cpp (0x1dfd28-0x1e09e8: Load and the slot stubs) and PS3_CKSrvNetwork_2.cpp
// (0x1e0a70-0x1e1080: constructor and factories). Not in XXL2. It reads nothing.
//
// The constructor goes through an unkeyed abstract base (vtable 0xb1e3e8, every IKUpdatable/IKService
// slot pure): its two vectors at +0x0c and +0x18 are folded into this class.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/services/IKService.h"
#include "k2000/util/TVector.h"

class PS3_CKSrvNetwork : public IKService {
public:
    DOTD_CLASS_KEY(kCategoryService, 0x18)
    DOTD_DECLARE_FACTORIES(PS3_CKSrvNetwork)

    PS3_CKSrvNetwork();  // 0x001e0a70 PS3_CKSrvNetwork_Construct
    ~PS3_CKSrvNetwork() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001e0948 PS3_CKSrvNetwork_Load
    void Start() override {}                            // vt+0x50 0x1e0950 (empty)
    void Stop() override {}                             // vt+0x68 0x1e0958 (empty)
    void Pause() override {}                            // vt+0x70 0x1e0960 (empty)
    void Resume() override {}                           // vt+0x78 0x1e0968 (empty)
    void Update(IKTime*) override {}                    // vt+0x7c 0x1e0970 (empty)
    int32_t InitializeService() override { return 1; }  // vt+0x94 0x1e0920
    void DestroyService() override {}                   // vt+0x98 0x1e0928 (empty)

    // Element types unknown (the base's code is not traced): opaque words.
    TVector<uint32_t, 1> m_unk0c;  // +0x0c the base's constructor: block 0, capacity 1, length 0
    TVector<uint32_t, 1> m_unk18;  // +0x18 the same
    void* m_unk24;                 // +0x24 a heap block on the live dump; not set by the constructor
    void* m_unk28;                 // +0x28 the same
};
DOTD_ASSERT_SIZE(PS3_CKSrvNetwork, 0x2c);
DOTD_ASSERT_OFFSET(PS3_CKSrvNetwork, m_ui32Priority, 0x08);
DOTD_ASSERT_OFFSET(PS3_CKSrvNetwork, m_unk0c, 0x0c);
DOTD_ASSERT_OFFSET(PS3_CKSrvNetwork, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(PS3_CKSrvNetwork, m_unk28, 0x28);
