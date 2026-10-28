// CNodeFx.cpp - reconstructed original translation unit 0xec920-0xed0d0 (GAME_TOC1, main_toc1), 9 functions, 9 live.
// Primary owner: CNodeFx (not a registered class)
// Other owners: INodeFx (2), NodeFx (1), UpdateParticleNodesSerial (1), PrepareQueuedParticleNodes (1), ShutdownParticleUpdateScheduler (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0xec920  NodeFx_EnqueueBase_maybe
//   [ ] 0xeca50  INodeFx_LevelReset
//   [ ] 0xeca78  CNodeFx_PostLoadBase_maybe
//   [ ] 0xecbd8  INodeFx_GetInfo
//   [ ] 0xecbe0  CNodeFx_Save
//   [x] 0xeccd8  CNodeFx_Load
//   [x] 0xecdd0  UpdateParticleNodesSerial
//   [x] 0xece60  PrepareQueuedParticleNodes
//   [ ] 0xed028  ShutdownParticleUpdateScheduler
//
//   [ ] 0x9a5730  INodeFx_IsKindOf  [inline]
//   [x] 0x9a5788  INodeFx_GetClassGroup  [inline]
//   [x] 0x9a5790  INodeFx_GetClassId  [inline]
//   [ ] 0x9a5798  INodeFx_DeletingDestructor  [inline]
//   [ ] 0x9a57e0  INodeFx_Destructor  [inline]
//   [ ] 0x9a5810  KStub_Return0_9a5810  [inline]
//   [ ] 0x9a5818  KStub_Return0_9a5818  [inline]
//   [ ] 0x9a5820  KStub_Return0_9a5820  [inline]
//   [ ] 0x9a5828  KStub_Return0_9a5828  [inline]
//   [ ] 0x9a5830  KStub_Return0_9a5830  [inline]
//   [ ] 0x9a5838  KStub_Return0_9a5838  [inline]
//   [ ] 0x9a5840  KStub_Return0_9a5840  [inline]
//   [ ] 0x9a5848  KStub_Return0_9a5848  [inline]
#include "k2000/fx/INodeFx.h"

#include "k2000/fx/ParticleUpdateScheduler.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"

#include "k2000/io/IKFile.h"

// 0x000eccd8 CNodeFx_Load: the three bytes only in level files.
int32_t INodeFx::Load(IKFile* file, int32_t type) {
    CNode::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        ReadU8(file, &m_unk28);
        ReadU8(file, &m_unk29);
        ReadU8(file, &m_unk2a);
    }
    return 1;
}

// ---- the particle scheduler's serial and preparing halves (ParticleUpdateScheduler.h) ----------------------

// 0x000ecdd0 UpdateParticleNodesSerial
void UpdateParticleNodesSerial(ParticleUpdateScheduler* scheduler, IKTime* frameClock) {
    const uint32_t count = scheduler->activeCount;
    ++scheduler->generation;
    for (uint32_t i = 0; static_cast<int32_t>(count) > 0 && i != count; ++i) {
        UpdateParticleNodeSimulation(scheduler->activeNodes[i], frameClock);
    }
}

// 0x000ece60 PrepareQueuedParticleNodes: (after the worker, when threaded) every queued node prepared; the
// ready ones become the active nodes (the array grows by 32), stamped with the generation. The queue empties.
void PrepareQueuedParticleNodes(ParticleUpdateScheduler* scheduler) {
    const uint32_t count = scheduler->workCount;
    scheduler->activeCount = 0;
    for (uint32_t i = 0; static_cast<int32_t>(count) > 0 && i != count; ++i) {
        ParticleRenderWorkItem* item = &scheduler->workItems[i];
        CParticlesNodeFx* node = item->node;
        PrepareParticleNodeForRendering(node, item->stages, item->frameClock, item->camera);
        if (node->m_bReadyForWorkerUpdate == 0) continue;
        if (scheduler->activeCapacity == scheduler->activeCount) {
            uint32_t capacity = scheduler->activeCount + 0x20;
            if (capacity == 0) capacity = 0x20;
            scheduler->activeNodes = static_cast<CParticlesNodeFx**>(
                ParticleScheduler_Realloc(scheduler->activeNodes, capacity * sizeof(CParticlesNodeFx*)));
            scheduler->activeCapacity = capacity;
        }
        scheduler->activeNodes[scheduler->activeCount] = node;
        ++scheduler->activeCount;
        node->m_ui32LastUpdateGeneration = scheduler->generation;
    }
    scheduler->workCount = 0;
}
