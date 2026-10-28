// CKParticlesCpnt.cpp - reconstructed original translation unit 0x1d9080-0x1dab88 (GAME_TOC1, main_toc1), 25 functions, 22 live.
// Primary class: CKParticlesCpnt  key 0x646  category Component  size 0x6c  vtable 0xb1df00
// Other owners: ApplyParticleComponentParameters (2), QueueParticleComponentEmission (2), TriggerParticleNodeEmission (1), ApplyParticleComponentOverrides (1), ProcessParticleComponentEmissionQueue (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1d9080  CKParticlesCpnt_Delete
//   [ ] 0x1d90d0  CKParticlesCpnt_Construct  [dead]
//   [x] 0x1d90e8  CKParticlesCpnt_FlushEmissionRequests
//   [ ] 0x1d9128  RegisterCKParticlesCpntClass
//   [ ] 0x1d91a0  _GLOBAL__I_1d91a0
//   [ ] 0x1d91b0  TriggerParticleNodeEmission
//   [x] 0x1d9340  CKParticlesCpnt_DeleteArray
//   [ ] 0x1d93e0  CKParticlesCpnt_Destructor_2
//   [ ] 0x1d9458  CKParticlesCpnt_Construct_2  [dead]
//   [ ] 0x1d9470  CKParticlesCpnt_DeletingDestructor
//   [ ] 0x1d94f8  CKParticlesCpnt_Destructor
//   [x] 0x1d9570  CKParticlesCpnt_CreateArray
//   [x] 0x1d9610  CKParticlesCpnt_Create
//   [ ] 0x1d9650  CKParticlesCpnt_Save
//   [x] 0x1d9658  CKParticlesCpnt_Load
//   [ ] 0x1d96e8  CKParticlesCpnt_RecursiveRegistration
//   [ ] 0x1d96f0  CKParticlesCpnt_Destroy
//   [ ] 0x1d96f8  CKParticlesCpnt_CachePropertyValuesFromEmitter_maybe
//   [ ] 0x1d9b78  CKParticlesCpnt_CachePropertyValuesFromEmitter_Thunk_maybe
//   [ ] 0x1d9b80  ApplyParticleComponentOverrides
//   [ ] 0x1da1a8  ProcessParticleComponentEmissionQueue
//   [ ] 0x1da328  ApplyParticleComponentParameters
//   [ ] 0x1da838  ApplyParticleComponentParameters
//   [ ] 0x1da840  QueueParticleComponentEmission
//   [ ] 0x1dab78  QueueParticleComponentEmission_NoDirection  [dead]
//
//   [ ] 0x9adb30  CKParticlesCpnt_IsKindOfClass  [inline]
//   [x] 0x9adb58  CKParticlesCpnt_GetClassType  [inline]
//   [x] 0x9adb60  CKParticlesCpnt_GetClassID  [inline]
#include "k2000/components/CKParticlesCpnt.h"

#include "k2000/io/IKFile.h"

// 0x001d9610 CKParticlesCpnt_Create, the inlined constructor (0x1d90d0 CKParticlesCpnt_Construct is a
// dead copy): +0x08 only.
CKParticlesCpnt::CKParticlesCpnt() { m_pEmissionQueueHead = nullptr; }

// 0x001d9658 CKParticlesCpnt_Load
int32_t CKParticlesCpnt::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pParticleNode);
    return 1;
}

// 0x001d90e8 CKParticlesCpnt_FlushEmissionRequests
void CKParticlesCpnt::FlushEmissionRequests() {
    ParticleEmitRequest* request = m_pEmissionQueueHead;
    while (request != nullptr) {
        ParticleEmitRequest* next = request->m_pNext;
        delete request;  // back to the FreeListPool 0x00ceaa94 in the original
        request = next;
    }
    m_pEmissionQueueHead = nullptr;
}
