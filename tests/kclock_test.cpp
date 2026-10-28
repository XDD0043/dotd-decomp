// Behaviour tests for IKTime / CKTime, from the reading of the PS3 assembly (IKTime_Update
// 0x53fb0). They pin down the speedrun-relevant quirks; the lockstep harness will later confirm the
// same values against RPCS3.
#include <cmath>
#include <cstdint>
#include <cstdio>

#include "k2000/system/IKTime.h"
#include "k2000/system/CTimeManager.h"
#include "platform/cell/sys_time.h"

static int g_failures = 0;
#define CHECK(cond)                                                              \
    do {                                                                         \
        if (!(cond)) {                                                           \
            std::printf("FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond);         \
            ++g_failures;                                                        \
        }                                                                        \
    } while (0)

static int64_t g_ticks = 0;  // fake sys_time_get_system_time (microseconds)
static int64_t FakeTicks() { return g_ticks; }

static const float kZeroDeltaDt = 0x1.47ae16p-7f;  // 0x3c23d70b
static const float kMaxDt = 0x1.99999ap-4f;        // 0.1f

int main() {
    dotd::platform::SetSystemTimeSource(&FakeTicks);
    CTimeManager tm;
    CKTime clock;
    tm.m_pTime = &clock;
    tm.m_fTimeScale = 1.0f;
    g_pTimeManager = &tm;

    // construction state
    CHECK(clock.m_eCurrentState == IKTime::STOPPED);
    CHECK(clock.m_fLastExactTime == -1.0f);
    CHECK(clock.m_eStateBeforeSystemPause == 4);

    g_ticks = 1000000;
    CHECK(clock.Initialize() == 1);
    clock.Restart();
    CHECK(clock.m_eCurrentState == IKTime::RUNNING);

    // first update: the clock samples twice at the same instant -> delta 0 -> both deltas = 0x3c23d70b
    g_ticks = 1016667;
    clock.Update();
    CHECK(clock.m_afDeltaTime[IKTime::SCALABLE_GAME_TIME] == kZeroDeltaDt);
    CHECK(clock.m_afDeltaTime[IKTime::SYSTEM_TIME] == kZeroDeltaDt);
    CHECK(clock.m_afCurrentTime[IKTime::SCALABLE_GAME_TIME] == kZeroDeltaDt);
    CHECK(clock.m_afCurrentTime[IKTime::SYSTEM_TIME] == kZeroDeltaDt);
    const float t0 = clock.m_fLastExactTime;

    // a normal 1/60 s frame
    g_ticks += 16667;
    clock.Update();
    const float expected = static_cast<float>(static_cast<double>(g_ticks - 1000000) * 1e-6) - t0;
    CHECK(clock.m_afDeltaTime[IKTime::SCALABLE_GAME_TIME] == expected);
    CHECK(clock.m_afDeltaTime[IKTime::SYSTEM_TIME] == expected);
    CHECK(clock.m_afLastTime[IKTime::SCALABLE_GAME_TIME] == kZeroDeltaDt);
    CHECK(clock.m_afCurrentTime[IKTime::SCALABLE_GAME_TIME] == kZeroDeltaDt + expected);

    // a 0.5 s hitch: dt is clamped to 0.1, the real delta is not
    const float timeBefore = clock.m_afCurrentTime[IKTime::SCALABLE_GAME_TIME];
    g_ticks += 500000;
    clock.Update();
    CHECK(clock.m_afDeltaTime[IKTime::SCALABLE_GAME_TIME] == kMaxDt);
    CHECK(clock.m_afDeltaTime[IKTime::SYSTEM_TIME] > 0.49f && clock.m_afDeltaTime[IKTime::SYSTEM_TIME] < 0.51f);
    CHECK(clock.m_afCurrentTime[IKTime::SCALABLE_GAME_TIME] == timeBefore + kMaxDt);

    // time scale multiplies dt (single precision)
    tm.m_fTimeScale = 0.5f;
    g_ticks += 16667;
    clock.Update();
    CHECK(clock.m_afDeltaTime[IKTime::SCALABLE_GAME_TIME] == clock.m_afDeltaTime[IKTime::FIXED_GAME_TIME] * 0.5f);
    tm.m_fTimeScale = 1.0f;

    // paused: dt still reported (unclamped), game time frozen, real time keeps running
    clock.Pause();
    const float frozen = clock.m_afCurrentTime[IKTime::SCALABLE_GAME_TIME];
    const float realBefore = clock.m_afCurrentTime[IKTime::SYSTEM_TIME];
    g_ticks += 300000;
    clock.Update();
    CHECK(clock.m_afCurrentTime[IKTime::SCALABLE_GAME_TIME] == frozen);
    CHECK(clock.m_afDeltaTime[IKTime::SCALABLE_GAME_TIME] > 0.29f && clock.m_afDeltaTime[IKTime::SCALABLE_GAME_TIME] < 0.31f);  // not clamped to 0.1 while paused
    CHECK(clock.m_afCurrentTime[IKTime::SYSTEM_TIME] > realBefore);

    // suspended (manager's clock): dt 0 and nothing accumulates; restore returns to paused
    clock.SystemPause();
    CHECK(clock.m_eCurrentState == IKTime::SYSTEM_PAUSED);
    CHECK(clock.m_eStateBeforeSystemPause == IKTime::PAUSED);
    const float realFrozen = clock.m_afCurrentTime[IKTime::SYSTEM_TIME];
    g_ticks += 16667;
    clock.Update();
    CHECK(clock.m_afDeltaTime[IKTime::SCALABLE_GAME_TIME] == 0.0f);
    CHECK(clock.m_afCurrentTime[IKTime::SYSTEM_TIME] == realFrozen);
    clock.SystemResume();
    CHECK(clock.m_eCurrentState == IKTime::PAUSED);

    // stopped: dt 0, real time still accumulates (the manager's clock is not suspended)
    clock.Stop();
    g_ticks += 16667;
    const float realStopped = clock.m_afCurrentTime[IKTime::SYSTEM_TIME];
    clock.Update();
    CHECK(clock.m_afDeltaTime[IKTime::SCALABLE_GAME_TIME] == 0.0f);
    CHECK(clock.m_afCurrentTime[IKTime::SYSTEM_TIME] > realStopped);

    if (g_failures == 0) std::printf("kclock: all tests passed\n");
    return g_failures == 0 ? 0 : 1;
}
