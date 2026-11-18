// CKSrvAvoidance.h - the avoidance service (key 0x241, vtable 0xb19b20, size 0xd8). Original unit:
// CKSrvAvoidance.cpp (0x122a50-0x123350). XXL2: K/KServices/KServiceAvoidance/CKSrvAvoidance.h, the
// same members in the same order. Its Load reads nothing: it clears the subscriber table.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/services/IKService.h"

// One subscriber (XXL2 CKAvoidanceCpnt _maybe; 0x1c bytes on the PS3). The enemies embed one (IKHkEnemy +0x16c).
struct CKAvoidanceAgent {
    float m_fRadius;          // +0x00
    float m_unk04;            // +0x04 the push share (lfs; equal shares push both fully)
    IKSerializable* m_pNode;  // +0x08 the scene node
    CVector3 m_v0c;           // +0x0c AddAgent: the zero vector
    uint32_t m_unk18;         // +0x18 AddAgent: 0
};
DOTD_ASSERT_SIZE(CKAvoidanceAgent, 0x1c);

class CKSrvAvoidance : public IKService {
public:
    DOTD_CLASS_KEY(kCategoryService, 0x9)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9a6e78
        return key == 0x241 || key == 0x1 || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKSrvAvoidance)

    static constexpr uint32_t kMaxSubscribers = 50;

    CKSrvAvoidance();  // inlined in 0x001232e8 CKSrvAvoidance_Create
    ~CKSrvAvoidance() override {}
    // vt+0x24 0x00122ae0 CKSrvAvoidance_RecursiveRegistration: type 0: the service registered.
    void RecursiveRegistration(int32_t type) override;

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001231d8 CKSrvAvoidance_Load
    void Start() override {}                            // vt+0x50 0x122b40 CKSrvAvoidance_Start (empty)
    void Stop() override {}                             // vt+0x68 0x122b48 CKSrvAvoidance_Stop (empty)
    void Pause() override {}                            // vt+0x70 0x122b50 CKSrvAvoidance_Pause (empty)
    void Resume() override {}                           // vt+0x78 0x122b58 CKSrvAvoidance_Resume (empty)
    // vt+0x7c 0x00122df8 UpdateCKSrvAvoidance: with the clock running (state 0), every agent's push (+0x0c) and count
    // (+0x18) cleared, then each pair of agents whose nodes were drawn this frame (or are not CNodes) and closer than
    // 1.5 x their radii pushed apart along their line (the X axis when they coincide), by the overlap past the radii,
    // shared by their weights (+0x04).
    void Update(IKTime* time) override;
    // vt+0x94 0x00122d08 CKSrvAvoidance_InitializeService: the engine's avoidance service (+0x74) set, returns 1.
    int32_t InitializeService() override;
    void DestroyService() override {}                   // vt+0x98 0x122ad8 (empty)
    // 0x00122b60 CKSrvAvoidance_AddAgent_maybe: the agent at the end of the table (no bound check), its vector the zero
    // vector and its word 0.
    void AddAgent(CKAvoidanceAgent* agent);
    // 0x00122bb0 CKSrvAvoidance_RemoveAgent_maybe: the agent found is replaced by the last one.
    void RemoveAgent(CKAvoidanceAgent* agent);

    CKAvoidanceAgent* m_apSubscriber[kMaxSubscribers];  // +0x0c cleared by Load
    uint32_t m_ui32NbSubscriber;                      // +0xd4 cleared by Load
};
DOTD_ASSERT_SIZE(CKSrvAvoidance, 0xd8);
DOTD_ASSERT_OFFSET(CKSrvAvoidance, m_ui32Priority, 0x08);
DOTD_ASSERT_OFFSET(CKSrvAvoidance, m_apSubscriber, 0x0c);
DOTD_ASSERT_OFFSET(CKSrvAvoidance, m_ui32NbSubscriber, 0xd4);
