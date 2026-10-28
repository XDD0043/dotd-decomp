// CKSrvAvoidance.h - the avoidance service (key 0x241, vtable 0xb19b20, size 0xd8). Original unit:
// CKSrvAvoidance.cpp (0x122a50-0x123350). XXL2: K/KServices/KServiceAvoidance/CKSrvAvoidance.h, the
// same members in the same order. Its Load reads nothing: it clears the subscriber table.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/services/IKService.h"

class CKSrvAvoidance : public IKService {
public:
    DOTD_CLASS_KEY(kCategoryService, 0x9)
    DOTD_DECLARE_FACTORIES(CKSrvAvoidance)

    static constexpr uint32_t kMaxSubscribers = 50;

    CKSrvAvoidance();  // inlined in 0x001232e8 CKSrvAvoidance_Create
    ~CKSrvAvoidance() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001231d8 CKSrvAvoidance_Load
    void Start() override {}                            // vt+0x50 0x122b40  STUB(C1.6)
    void Stop() override {}                             // vt+0x68 0x122b48  STUB(C1.6)
    void Pause() override {}                            // vt+0x70 0x122b50  STUB(C1.6)
    void Resume() override {}                           // vt+0x78 0x122b58  STUB(C1.6)
    void Update(IKTime*) override {}                    // vt+0x7c 0x122df8 UpdateCKSrvAvoidance  STUB(C1.6)
    // vt+0x94 0x122d08. STUB(C1.6): the original calls Engine_SetAvoidanceService(this), returns 1.
    int32_t InitializeService() override { return 1; }
    void DestroyService() override {}                   // vt+0x98 0x122ad8 (empty)

    IKSerializable* m_apSubscriber[kMaxSubscribers];  // +0x0c CKAvoidanceCpnt*; cleared by Load
    uint32_t m_ui32NbSubscriber;                      // +0xd4 cleared by Load
};
DOTD_ASSERT_SIZE(CKSrvAvoidance, 0xd8);
DOTD_ASSERT_OFFSET(CKSrvAvoidance, m_ui32Priority, 0x08);
DOTD_ASSERT_OFFSET(CKSrvAvoidance, m_apSubscriber, 0x0c);
DOTD_ASSERT_OFFSET(CKSrvAvoidance, m_ui32NbSubscriber, 0xd4);
