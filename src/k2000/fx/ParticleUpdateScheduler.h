// ParticleUpdateScheduler.h - the engine's particle node scheduler (engine +0xb4, 0x80 bytes): the
// particle nodes the render traversal met (work items), prepared before the stages run, and the ones
// ready (active nodes), whose simulation the next frame updates. Original units: ParticleUpdateScheduler.cpp
// (0xed0d0-0xedb08) and CNodeFx.cpp (UpdateParticleNodesSerial, PrepareQueuedParticleNodes).
//
// The PS3 runs the simulation on a worker thread (ParticleUpdateThreadMain 0xed430) when the execution
// concurrency (KStub_Return2_54cd0: 2) is above 1; natively the serial path runs (the same updates, in the
// same order, before the traversal instead of beside it). The mutex, condition and thread are not modelled.
#pragma once
#include <cstdint>

class CParticlesNodeFx;
class IKTime;
class RenderQueue;
struct RwCamera;

// One particle node met by the traversal (0x10 bytes on the PS3).
struct ParticleRenderWorkItem {
    CParticlesNodeFx* node;  // +0x00
    RenderQueue** stages;    // +0x04 the renderer's stage array
    IKTime* frameClock;      // +0x08
    RwCamera* camera;        // +0x0c
};

struct ParticleUpdateScheduler {
    uint32_t generation;               // +0x00 +1 per ScheduleParticleNodeUpdates
    uint32_t executionConcurrency;     // +0x04 natively 1 (see above)
    ParticleRenderWorkItem* workItems; // +0x08
    uint32_t workCapacity;             // +0x0c
    uint32_t workCount;                // +0x10
    CParticlesNodeFx** activeNodes;    // +0x14
    uint32_t activeCapacity;           // +0x18
    uint32_t activeCount;              // +0x1c
    uint32_t workerState;              // +0x20
    IKTime* frameClock;                // +0x24 the worker's frame
};

// 0x000ed0d0 InitializeParticleUpdateScheduler
void InitializeParticleUpdateScheduler(ParticleUpdateScheduler* scheduler);
// 0x000ed328 ScheduleParticleNodeUpdates
void ScheduleParticleNodeUpdates(ParticleUpdateScheduler* scheduler, IKTime* frameClock);
// 0x000ecdd0 UpdateParticleNodesSerial (CNodeFx.cpp)
void UpdateParticleNodesSerial(ParticleUpdateScheduler* scheduler, IKTime* frameClock);
// 0x000ece60 PrepareQueuedParticleNodes (CNodeFx.cpp)
void PrepareQueuedParticleNodes(ParticleUpdateScheduler* scheduler);
// Mem_ReallocAligned16 as the scheduler's arrays grow (ParticleUpdateScheduler.cpp).
void* ParticleScheduler_Realloc(void* block, uint32_t bytes);
