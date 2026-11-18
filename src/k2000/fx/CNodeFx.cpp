// CNodeFx.cpp - reconstructed original translation unit 0xec920-0xed0d0 (GAME_TOC1, main_toc1), 9 functions, 9 live.
// Primary owner: CNodeFx (not a registered class)
// Other owners: INodeFx (2), NodeFx (1), UpdateParticleNodesSerial (1), PrepareQueuedParticleNodes (1), ShutdownParticleUpdateScheduler (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xec920  NodeFx_EnqueueBase_maybe
//   [x] 0xeca50  INodeFx_LevelReset  (RecursiveRegistration: CNode's 0xcbaa8, inherited)
//   [x] 0xeca78  CNodeFx_PostLoadBase_maybe
//   [x] 0xecbd8  INodeFx_GetInfo  (returns 1: the default, inherited)
//   [ ] 0xecbe0  CNodeFx_Save
//   [x] 0xeccd8  CNodeFx_Load
//   [x] 0xecdd0  UpdateParticleNodesSerial
//   [x] 0xece60  PrepareQueuedParticleNodes
//   [x] 0xed028  ShutdownParticleUpdateScheduler
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

#include "k2000/geometry/CGeometry.h"
#include "k2000/io/IKFile.h"
#include "k2000/render/CRenderer.h"

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

// 0x000eca78 INodeFx_PostLoad. As in CGeometry_Load, a byte above 1 also sets the bits above its own
// (rlwinm/or: the byte shifted to the bit, masked to the bits from the top).
int32_t INodeFx::PostLoad(int32_t type) {
    if (type == 0) {
        for (CGeometry* geometry = static_cast<CGeometry*>(m_lGeometryList); geometry != nullptr;
             geometry = geometry->m_pNext) {
            uint32_t flags = geometry->m_BitProperties;
            flags = (flags & ~0x400000u) | ((static_cast<uint32_t>(m_unk28) << 22) & 0xffc00000u);
            geometry->m_BitProperties = flags;
            flags = (flags & ~0x800000u) | ((static_cast<uint32_t>(m_unk29) << 23) & 0xff800000u);
            geometry->m_BitProperties = flags;
            flags = (flags & ~0x2000000u) | ((static_cast<uint32_t>(m_unk2a) << 25) & 0xfe000000u);
            geometry->m_BitProperties = flags;
        }
    }
    for (CGeometry* geometry = static_cast<CGeometry*>(m_lGeometryList); geometry != nullptr;
         geometry = geometry->m_pNext) {
        geometry->Vf80((geometry->m_BitProperties & 0x80000) != 0 ? 0 : 2);  // vt+0x80
    }
    return CNode::PostLoad(type);
}

// 0x000ec920 NodeFx_EnqueueBase_maybe
void INodeFx::EnqueueBase(RenderQueue** stages, IKTime* frameClock, RwCamera* camera) {
    if ((m_sgProperties & 4) != 0) return;
    if ((CullAndEnqueueGeometry(stages, frameClock, camera) & 0xff) != 0) m_ui16LastRenderedFrame = g_ui16RenderFrameCounter;
    for (CSGLeaf* child = m_lChildList; child != nullptr; child = child->m_pNext) {
        child->UpdateAndExtract(0.0f, stages, frameClock, camera, 0);  // vt+0x58
    }
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

// 0x000ed028 ShutdownParticleUpdateScheduler. With a worker (not natively, see ParticleUpdateScheduler.h) the worker
// state becomes 2 under the mutex, the condition is signalled and the thread joined.
void ShutdownParticleUpdateScheduler(ParticleUpdateScheduler* scheduler) {
    if (scheduler->shutdownRequested != 0) return;
    scheduler->shutdownRequested = 1;
    if (scheduler->executionConcurrency > 1) scheduler->workerState = 2;
}
