// CKCrumblyZoneCpnt.cpp - reconstructed original translation unit 0x401850-0x402430 (GAME_TOC1, main_toc1), 19 functions, 17 live.
// Primary class: CKCrumblyZoneCpnt  key 0xc6  category Component  size 0x10  vtable 0xb25690
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x401850  RegisterCKCrumblyZoneCpntClass
//   [ ] 0x4018c8  _GLOBAL__I_4018c8
//   [x] 0x4018d8  CKCrumblyZoneCpnt_PostLoad  (inline in the header)
//   [ ] 0x401900  CKCrumblyZoneCpnt_Save
//   [x] 0x401928  CKCrumblyZoneCpnt_RecursiveRegistration  (the base's 0x3f7a70 (returns 1, registers nothing): the default)
//   [x] 0x401950  CKCrumblyZoneCpnt_Destroy
//   [x] 0x401a18  CKCrumblyZoneCpnt_DeleteArray
//   [x] 0x401ab8  CKCrumblyZoneCpnt_DeletingDestructor  (the deleting form of the implicit destructor)
//   [x] 0x401b00  CKCrumblyZoneCpnt_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x401b30  CKCrumblyZoneCpnt_DestructBody  (C++ destructor chain: vtable stores only)
//   [ ] 0x401b60  CKCrumblyZoneCpnt_Construct  [dead]
//   [ ] 0x401b98  CKCrumblyZoneCpnt_Construct_2  [dead]
//   [x] 0x401bd0  CKCrumblyZoneCpnt_QueueInstanceTransform_maybe
//   [x] 0x401d18  CKCrumblyZoneCpnt_GetInfo  (returns 1: the default)
//   [x] 0x401d20  CKCrumblyZoneCpnt_MessageProc
//   [x] 0x401e58  CKCrumblyZoneCpnt_vf60
//   [x] 0x4021a0  CKCrumblyZoneCpnt_CreateArray
//   [x] 0x402250  CKCrumblyZoneCpnt_Create
//   [x] 0x4022a8  CKCrumblyZoneCpnt_Load
//
//   [ ] 0x9c1098  CKCrumblyZoneCpnt_IsKindOfClass  [inline]
//   [x] 0x9c10d0  CKCrumblyZoneCpnt_GetClassType  [inline]
//   [x] 0x9c10d8  CKCrumblyZoneCpnt_GetClassID  [inline]
//   [x] 0x9c10e0  CKCrumblyZoneCpnt_vf50  [inline]
//   [x] 0x9c10e8  CKCrumblyZoneCpnt_vf54  [inline]  (CKCrumblyZoneCpnt.h Vf54)
//   [ ] 0x9c10f0  CKCrumblyZoneCpnt_vf58  [inline]
//   [x] 0x9c1100  CKCrumblyZoneCpnt_vf5C  [inline]
#include "k2000/components/CKCrumblyZoneCpnt.h"

#include "k2000/hooks/CKHkCrumblyZone.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/misc/CKGrpMeca.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rpprtstd/RpPrtStdRuntime.h"
#include "Renderware/rwcore/RwCamera.h"

namespace {
// 0x00c50d40 / 0x00c50d64 (TOC1 +0x4880 / +0x487c): the shared Y axis and the null vector (static initialisers).
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};
const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};
bool IsNull(const CVector3& v) { return v.x == kNullVector.x && v.y == kNullVector.y && v.z == kNullVector.z; }
}  // namespace

// 0x00401bd0 CKCrumblyZoneCpnt_QueueInstanceTransform_maybe. (The original first reads a halfword of the graphic
// module's init parameters, 0x596b0, and drops it.)
void CKCrumblyZoneCpnt::QueueInstanceTransform(float speed, int32_t index, const CVector3* position,
                                               const CVector3* direction, const CVector3* emitterSize) {
    if (index < 0 || m_apImpulseEmitters[index].m_pImpulsePart == nullptr) return;
    ImpulseRequest* request = new ImpulseRequest;  // FreeListPool 0x00ceaab4 (FreeListPool_Grow when empty)
    request->m_pNext = m_apImpulseEmitters[index].m_pRequests;
    m_apImpulseEmitters[index].m_pRequests = request;
    request->m_position = *position;
    request->m_direction = *direction;
    request->m_emitterSize = *emitterSize;
    request->m_fSpeed = speed;
}

// 0x00401e58 CKCrumblyZoneCpnt_vf60
void CKCrumblyZoneCpnt::Vf60(IKTime* /*clock*/) {
    const uint32_t count = m_ui32NbImpEmitters & 0xffu;
    for (uint32_t i = 0; i != count; ++i) {
        SImpulsePart& part = m_apImpulseEmitters[i & 0xffu];
        ImpulseRequest* request = part.m_pRequests;
        if (request == nullptr) continue;
        CParticlesNodeFx* node = static_cast<CParticlesNodeFx*>(part.m_pImpulsePart);
        RwFrame* frame = node->m_pRwFrame;
        frame->modelling.pos.z = request->m_position.z;
        frame->modelling.pos.x = request->m_position.x;
        frame->modelling.pos.y = request->m_position.y;
        frame->modelling.flags &= 0xfffdffffu;
        RwFrame_MarkDirty(frame);  // 0x00010698
        auto standard = [node]() {
            RpPrtStdEmitter* emitter = node->m_pRpPrtStdEmitter;
            return reinterpret_cast<RpPrtStdEmitterStandard*>(reinterpret_cast<uint8_t*>(emitter) +
                                                              emitter->emtClass->propTab->propOffset[1]);
        };
        if (!IsNull(request->m_direction)) {
            CVector3 along = request->m_direction;
            node->SetOrientationFromAtUp(&along, &kAxisY);  // 0x000d0918
            const float speed = request->m_fSpeed;
            if (speed > 0.0f) {  // ble: !(speed > 0) skips
                along.x = along.x * speed;
                along.z = along.z * speed;
                along.y = along.y * speed;
                RpPrtStdEmitterStandard* s = standard();
                s->force.x = along.x;
                s->force.y = along.y;
                s->force.z = along.z;
            }
        }
        if (!IsNull(request->m_emitterSize)) {
            RpPrtStdEmitterStandard* s = standard();
            s->emtSize.x = request->m_emitterSize.x;
            s->emtSize.y = request->m_emitterSize.y;
            s->emtSize.z = request->m_emitterSize.z;
        }
        node->m_sgProperties = (node->m_sgProperties | 0x200u | 0x400u) & ~0x80000u;
        node->m_fEmissionSpeedAdjustment = 0.0f;  // TOC1 +0x4884
        node->m_pRpPrtStdEmitter->flag |= rpPRTSTDEMITTERFLAGACTIVE | rpPRTSTDEMITTERFLAGEMIT;  // 0xa
        part.m_pRequests = request->m_pNext;
        delete request;  // back to the FreeListPool 0x00ceaab4
    }
    // The path-blocking step (ResetStageRecursive sets 1 or 3).
    const int8_t step = static_cast<int8_t>(m_unk0d);
    if (step == 1 || step == 3) {
        m_unk0d = 2;
    } else if (step == 2) {
        m_unk0d = 0;
    }
}

// 0x004022a8 CKCrumblyZoneCpnt_Load
int32_t CKCrumblyZoneCpnt::Load(IKFile* file, int32_t type) {
    IKMecaCpnt::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        ReadU32LE(file, &m_ui32NbImpEmitters);
        m_apImpulseEmitters = new SImpulsePart[m_ui32NbImpEmitters];  // OperatorNewArray(n * 8 + 4)
        for (uint32_t i = 0; i < m_ui32NbImpEmitters; ++i) IKFile_ReadRef(file, &m_apImpulseEmitters[i].m_pImpulsePart);
    }
    return 1;
}

// 0x00401950 CKCrumblyZoneCpnt_Destroy (the count from the array's cookie: m_ui32NbImpEmitters, its size at the Load)
void CKCrumblyZoneCpnt::Destroy() {
    IKMecaCpnt::Destroy();  // 0x003f7a78
    if (m_apImpulseEmitters != nullptr) {
        for (uint32_t i = m_ui32NbImpEmitters; i != 0; --i) {
            SImpulsePart& part = m_apImpulseEmitters[i - 1];
            for (ImpulseRequest* request = part.m_pRequests; request != nullptr;) {
                ImpulseRequest* next = request->m_pNext;  // +0x28
                delete request;  // back to the FreeListPool 0x00ceaab4
                request = next;
            }
            part.m_pRequests = nullptr;
        }
        delete[] m_apImpulseEmitters;  // TocBridge_OperatorDeleteArray
    }
    m_apImpulseEmitters = nullptr;
}

// 0x00401d20 CKCrumblyZoneCpnt_MessageProc
int32_t CKCrumblyZoneCpnt::MessageProc(uint16_t message, void* /*data*/) {
    if (message != 0x902) return 1;
    CKGrpMeca* meca = static_cast<CKGrpMeca*>(g_pEngine->m_gameManager->m_unk04[2]);  // the game manager's +0x0c
    for (IKHook* hook = *reinterpret_cast<IKHook**>(meca->GetMemberListHead()); hook != nullptr;  // vt+0xb0
         hook = hook->m_pNextHook) {
        const int32_t id = hook->GetClassID();                 // vt+0x18
        const int32_t key = (id << 6) + hook->GetClassType();  // vt+0x14
        if (key != 0x1982 || hook->m_iSectorIndex != 0) continue;
        static_cast<CKHkCrumblyZone*>(hook)->ResetStageRecursive();  // 0x004082f8
    }
    return 0;
}
