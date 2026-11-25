// gpuprof.h - where a frame's GPU time goes, without GPU timer queries (new platform code, profiling only).
//
// Measured frames (DOTD_GPU_PROF=N: every Nth frame; 0 or absent: off; the page's GPU test sets it at run time): the
// renderer marks the start and end of each render stage (CRenderer.cpp, RenderQueue::Execute) and glFinish is called
// at every mark, so the time from one mark to the next is that segment's whole cost: the CPU's time issuing it, then
// the wait in glFinish for the GPU (and in a browser the GPU process) to finish it. One finish more at the frame's
// first mark takes what the GPU still had of the previous frame ("drain"); a second one right after measures a
// finish's own cost ("finish cost", to subtract per segment). Every kReportEvery measured frames a "gpuprof" line set
// is logged: the segments by total time, with their draws (DOTD_GFX_STATS must be on to count them) and the classes
// of the items the stage drew. On a tile-based GPU (phones) a finish inside a render pass also costs a store and a
// load of the frame buffer, so the absolute numbers are a little high there; the order of the segments holds, and the
// skip switches below give the undistorted difference.
//
// Skip switches (DOTD_SKIP_STAGES=5,9,... or the page at run time): the stages listed are not drawn (their queue is
// emptied unseen). With the resolution scale (device.h, SetResolutionScale) they are the page's A/B test.
#pragma once
#include <cstdint>

namespace dotd::gfx::gpuprof {

constexpr int kStages = 23;

void Init();  // gfx::Init: the environment variables

// The renderer's marks. `items`: the stage's item count (kept for the page whatever the mode).
void FrameStart();                       // RenderGameFrame, before the frame's first stage
void BeginStage(int stage, uint32_t items);
void EndStage(int stage);
void NoteItem(int stage, const char* className);  // measured frames only: one item drawn by the stage
void FrameEnd();                         // EndFrame, before the present
bool Measuring();                        // this frame is measured

// Run-time settings (the page's GPU test): measure every `every` frames (0: off), skip the stages in `mask`.
void SetMeasureEvery(int every);
void SetSkipMask(uint32_t mask);
uint32_t SkipMask();
inline bool StageSkipped(int stage) { return stage >= 0 && stage < kStages && ((SkipMask() >> stage) & 1u) != 0; }
uint32_t StageItems(int stage);  // the stage's item count at its last execution

// Finer switches (the GPU test's second round): the items [from, to) of `stage` in drawing order not drawn; after every
// stage a glFlush (sync 1) or a glFinish (sync 2) in every frame; the items of `stage` described in the measured
// frames' report ("gpuprof item" lines: the renderer's ItemDescription).
void SetSkipItems(int stage, uint32_t from, uint32_t to);
bool ItemSkipped(int stage, uint32_t index);
void SetStageSync(int sync);
void SetDescribedStage(int stage);
bool Describing(int stage);

// The opaque queues' draw experiments (DOTD_OPAQUE=reverse,prepass or the page's fix test): bit 0 draws them near to
// far (the original sorts every sorted queue far to near: the GPU then shades hidden pixels again and again), bit 1
// draws each opaque queue first with the colour writes off (depth only), then as usual (each pixel shaded once).
enum OpaqueMode : int { kOpaqueReverse = 1, kOpaquePrepass = 2 };
void SetOpaqueMode(int mode);
int OpaqueMode();  // a measured frame and the described stage: NoteItemDescription is wanted
void NoteItemDescription(uint32_t index, const char* text);

}  // namespace dotd::gfx::gpuprof
