// CKSrvAvoidance.cpp - reconstructed original translation unit 0x122a50-0x123350 (GAME_TOC1, main_toc1), 21 functions, 19 live.
// Primary class: CKSrvAvoidance  key 0x241  category Service  size 0xd8  vtable 0xb19b20
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x122a50  CKSrvAvoidance_Delete
//   [ ] 0x122aa0  CKSrvAvoidance_Construct  [dead]
//   [x] 0x122ad8  CKSrvAvoidance_DestroyService
//   [x] 0x122ae0  CKSrvAvoidance_RecursiveRegistration
//   [x] 0x122b40  CKSrvAvoidance_Start
//   [x] 0x122b48  CKSrvAvoidance_Stop
//   [x] 0x122b50  CKSrvAvoidance_Pause
//   [x] 0x122b58  CKSrvAvoidance_Resume
//   [x] 0x122b60  CKSrvAvoidance_AddAgent_maybe
//   [x] 0x122bb0  CKSrvAvoidance_RemoveAgent_maybe
//   [ ] 0x122c48  CKSrvAvoidance_Construct_2  [dead]
//   [ ] 0x122c80  RegisterCKSrvAvoidanceClass
//   [ ] 0x122cf8  _GLOBAL__I_122cf8
//   [x] 0x122d08  CKSrvAvoidance_InitializeService
//   [x] 0x122d30  CKSrvAvoidance_Destroy  (inherited: IKService_Destroy)
//   [x] 0x122d58  CKSrvAvoidance_DeleteArray
//   [x] 0x122df8  UpdateCKSrvAvoidance
//   [x] 0x1231d8  CKSrvAvoidance_Load
//   [ ] 0x123218  CKSrvAvoidance_Save
//   [x] 0x123220  CKSrvAvoidance_CreateArray
//   [x] 0x1232e8  CKSrvAvoidance_Create
//
//   [ ] 0x9a6e78  CKSrvAvoidance_IsKindOfClass  [inline]
//   [ ] 0x9a6eb0  CKSrvAvoidance_GetClassType  [inline]
//   [ ] 0x9a6eb8  CKSrvAvoidance_GetClassID  [inline]
//   [ ] 0x9a6ec0  CKSrvAvoidance_DeletingDestructor  [inline]
//   [ ] 0x9a6f08  CKSrvAvoidance_Destructor  [inline]
#include "k2000/services/CKSrvAvoidance.h"

#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/render/CRenderer.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/system/IKTime.h"
#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include <cmath>

// Inlined in 0x001232e8 CKSrvAvoidance_Create (0x122aa0 CKSrvAvoidance_Construct is an unreferenced
// copy): only the IKService part and the priority.
CKSrvAvoidance::CKSrvAvoidance() { m_ui32Priority = 0xaa; }

// 0x001231d8 CKSrvAvoidance_Load: for a level, the count first, then the 50 slots.
int32_t CKSrvAvoidance::Load(IKFile* /*file*/, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        m_ui32NbSubscriber = 0;
        for (uint32_t i = 0; i < kMaxSubscribers; ++i) m_apSubscriber[i] = nullptr;
    }
    return 1;
}

// 0x00122d08 CKSrvAvoidance_InitializeService
int32_t CKSrvAvoidance::InitializeService() {
    Engine_SetAvoidanceService(this);  // 0x24c10
    return 1;
}

// 0x00122b60 CKSrvAvoidance_AddAgent_maybe
void CKSrvAvoidance::AddAgent(CKAvoidanceAgent* agent) {
    m_apSubscriber[m_ui32NbSubscriber] = agent;
    agent->m_v0c = CVector3{0.0f, 0.0f, 0.0f};  // the zero vector 0x00c50d64 (TOC1 -0x4340)
    agent->m_unk18 = 0;
    m_ui32NbSubscriber = m_ui32NbSubscriber + 1;
}

// 0x00122bb0 CKSrvAvoidance_RemoveAgent_maybe
void CKSrvAvoidance::RemoveAgent(CKAvoidanceAgent* agent) {
    const uint32_t count = m_ui32NbSubscriber;
    if (count == 0) return;
    uint32_t i = 0;
    while (m_apSubscriber[i] != agent) {
        if (++i == count) return;
    }
    const uint32_t last = count - 1;
    if (i < last) m_apSubscriber[i] = m_apSubscriber[last];
    m_ui32NbSubscriber = last;
}

// 0x00122df8 UpdateCKSrvAvoidance
void CKSrvAvoidance::Update(IKTime* time) {
    if (time->m_eCurrentState != 0) return;
    if (m_ui32NbSubscriber == 0) return;
    const CVector3 kNull{0.0f, 0.0f, 0.0f};   // TOC1 -0x4340: 0x00c50d64
    const CVector3 kAxisX{1.0f, 0.0f, 0.0f};  // TOC1 -0x4310: 0x00c50d34
    for (uint32_t i = 0; m_ui32NbSubscriber > i; ++i) {
        CKAvoidanceAgent* agent = m_apSubscriber[i];
        agent->m_v0c = kNull;
        agent->m_unk18 = 0;
    }
    // A CNode's agent takes part only while its node was drawn this frame.
    auto active = [](IKSerializable* node) {
        return node->IsKindOfClass(CNode::kClassKey) == 0 ||
               static_cast<const CSGLeaf*>(node)->m_ui16LastRenderedFrame == g_ui16RenderFrameCounter;  // 0x00c29694
    };
    for (uint32_t i = 0; m_ui32NbSubscriber > i; ++i) {
        CKAvoidanceAgent* a = m_apSubscriber[i];
        if (!active(a->m_pNode)) continue;
        for (uint32_t j = i + 1; m_ui32NbSubscriber > j; ++j) {
            CKAvoidanceAgent* b = m_apSubscriber[j];
            if (!active(b->m_pNode)) continue;
            const RwV3d& posB = FrameLtm(static_cast<CSGMovable*>(b->m_pNode)->m_pRwFrame)->pos;
            const RwV3d& posA = FrameLtm(static_cast<CSGMovable*>(a->m_pNode)->m_pRwFrame)->pos;
            const float radii = a->m_fRadius + b->m_fRadius;
            const float dy = posB.y - posA.y;
            const float dx = posB.x - posA.x;
            const float reach = radii * 1.5f;  // TOC1 -0x4318
            const float dz = posB.z - posA.z;
            const float squared = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
            if (reach * reach <= squared) continue;
            const float distance = std::sqrt(squared);  // Math_Sqrtf
            float nx, ny, nz;
            if (distance <= 0.0f) {
                nx = kAxisX.x;
                ny = kAxisX.y;
                nz = kAxisX.z;
            } else {
                const float k = 1.0f / distance;
                nz = dz * k;
                nx = dx * k;
                ny = dy * k;
                if (radii < distance) {
                    // Between the radii and the reach: the push falls off to 0.
                    const float scale = (reach - distance) / (reach - radii);
                    nz = nz * scale;
                    nx = nx * scale;
                    ny = ny * scale;
                }
            }
            float shareB;
            float shareA;
            if (a->m_unk04 == b->m_unk04) {
                shareB = 1.0f;
                shareA = -1.0f;
            } else if (a->m_unk04 <= b->m_unk04) {
                shareB = 1.0f;
                shareA = -(a->m_unk04 / b->m_unk04);
            } else {
                shareB = b->m_unk04;  // as the original (the register still holds b's share)
                shareA = -1.0f;
            }
            b->m_v0c.x = ppc::fmadds(shareB, nx, b->m_v0c.x);
            b->m_v0c.y = ppc::fmadds(shareB, ny, b->m_v0c.y);
            b->m_v0c.z = ppc::fmadds(nz, shareB, b->m_v0c.z);
            b->m_unk18 = b->m_unk18 + 1;
            a->m_v0c.x = ppc::fmadds(shareA, nx, a->m_v0c.x);
            a->m_v0c.y = ppc::fmadds(shareA, ny, a->m_v0c.y);
            a->m_v0c.z = ppc::fmadds(nz, shareA, a->m_v0c.z);
            a->m_unk18 = a->m_unk18 + 1;
        }
    }
}

// 0x00122ae0 CKSrvAvoidance_RecursiveRegistration: type 0: the service registered (CKSavingManager vt+0x24).
void CKSrvAvoidance::RecursiveRegistration(int32_t type) {
    if (type == 0) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
}
