// Reconstructed original translation unit: 0xed0d0-0xedb08 (GAME_TOC1, main_toc1), 6 functions, 6 live.
// Primary owner: ParticleUpdateScheduler (not a registered class)
// Other owners: InitializeParticleUpdateScheduler (1), ScheduleParticleNodeUpdates (1), ParticleUpdateThreadMain (1), InitializeParticleUpdateSchedulerAlternate (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xed0d0  InitializeParticleUpdateScheduler (the serial configuration)
//   [x] 0xed328  ScheduleParticleNodeUpdates
//   [ ] 0xed430  ParticleUpdateThreadMain
//   [ ] 0xed590  InitializeParticleUpdateSchedulerAlternate
//   [ ] 0xed7e8  ParticleUpdateScheduler_DestructBody_2_maybe
//   [ ] 0xed978  ParticleUpdateScheduler_DestructBody_maybe
#include "k2000/fx/ParticleUpdateScheduler.h"

#include <cstdlib>

#include "k2000/scenegraph/CParticlesNodeFx.h"

void* ParticleScheduler_Realloc(void* block, uint32_t bytes) { return std::realloc(block, bytes); }

// 0x000ed0d0 InitializeParticleUpdateScheduler: generation 0, the concurrency (KStub_Return2_54cd0: 2 on the
// PS3, which also creates the condition, the mutex and ParticleUpdateThread; natively 1, see the header),
// 32 work items (0x200 bytes) and 32 active nodes (0x80 bytes).
void InitializeParticleUpdateScheduler(ParticleUpdateScheduler* scheduler) {
    scheduler->generation = 0;
    scheduler->executionConcurrency = 1;
    scheduler->workCount = 0;
    scheduler->workCapacity = 0x20;
    scheduler->workItems = static_cast<ParticleRenderWorkItem*>(std::calloc(0x20, sizeof(ParticleRenderWorkItem)));
    scheduler->activeCapacity = 0x20;
    scheduler->activeCount = 0;
    scheduler->activeNodes = static_cast<CParticlesNodeFx**>(std::calloc(0x20, sizeof(CParticlesNodeFx*)));
    scheduler->workerState = 0;
    scheduler->frameClock = nullptr;
}

// 0x000ed328 ScheduleParticleNodeUpdates: serially (concurrency < 2) the generation goes up and every
// active node's simulation is updated; the threaded path hands the frame to the worker.
void ScheduleParticleNodeUpdates(ParticleUpdateScheduler* scheduler, IKTime* frameClock) {
    if (scheduler->executionConcurrency < 2) {
        const uint32_t count = scheduler->activeCount;
        ++scheduler->generation;
        for (uint32_t i = 0; static_cast<int32_t>(count) > 0 && i != count; ++i) {
            UpdateParticleNodeSimulation(scheduler->activeNodes[i], frameClock);
        }
        return;
    }
    scheduler->frameClock = frameClock;  // under the mutex, then the condition signalled (not modelled)
    scheduler->workerState = 1;
}
