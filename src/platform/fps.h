// fps.h - the 60 Hz timing calculation behind --fps N (not in the original; off by default).
//
// The original runs one game update per displayed frame at exactly 60 Hz. Gameplay integrates the measured dt
// (IKTime), so most of it keeps its speed at any frame rate, but some systems step a fixed amount per update (the
// CKPx physics service, fixed-step Flash interfaces), turn rate x dt into a whole number every update and drop the
// fraction (byte alpha fades, damage per second), count updates, roll a probability per update, or move through a
// chain of states one update per link (the cinematic scenes' blocs, the sekens lines). With --fps N (N != 60) the game
// still runs one update per displayed frame with the real dt, and those systems ask this module what 60 Hz frames
// this displayed frame stands for:
//   Ticks()     the 60 Hz frames completed during this displayed frame (0..6: a phase accumulator on the real frame
//               time, the clock's 0.1 s clamp as the limit), so frame-counted work runs Ticks() times;
//   Scale()     this displayed frame's length in 60 Hz frames (real delta x 60, at most 6), for fixed steps;
//   Dt60(dt)    a delta taken this frame, as one 60 Hz frame's share of it (dt / Scale());
//   TruncSteps(rate, dt)  what the original's per-update trunc(rate x dt) adds up to over this frame's 60 Hz frames:
//               Ticks() x trunc(rate x Dt60(dt));
//   TickDelta(mode)  the clock's delta (IKTime mode) summed over the displayed frames since the last 60 Hz frame
//               ended, for the services that run whole 60 Hz updates (CKServiceManager::Update);
//   SubStep     while one lives, the code runs as one 60 Hz update: Ticks() = 1, Scale() = 1, Dt60(dt) = dt.
// Off (the default, and --fps 60): Unlocked() is false and the callers keep the original code path; Ticks() = 1,
// Scale() = 1, Dt60(dt) = dt, so nothing changes. Replays and tests run with it off.
#pragma once
#include <cstdint>

namespace dotd::fps {

// --fps N / dotd.ini fps = N (config.h): any N but 60 turns the calculation on.
void Configure(bool unlocked);
bool Unlocked();

// Called by CTimeManager::Update right after the frame clock updates, with this frame's deltas (IKTime
// m_afDeltaTime: scaled game, unscaled game, real). Advances the 60 Hz phase on the real delta. Nothing while locked.
void OnClockUpdate(const float delta[3]);

int32_t Ticks();
// The 60 Hz frames completed since the start (the sum of Ticks(); 0 while locked).
uint32_t TickCount();
float Scale();
float Dt60(float dt);
int64_t TruncSteps(float rate, float dt);
float TickDelta(int32_t mode);

class SubStep {
public:
    SubStep();
    ~SubStep();
    SubStep(const SubStep&) = delete;
    SubStep& operator=(const SubStep&) = delete;
};

}  // namespace dotd::fps
