// IKTime.h - the engine's frame clock (k2000). Original units: IKTime.cpp (0x53f10-0x54250),
// CKTime.cpp (0x54250-...). Owned by CTimeManager (GameEngineContext +0x48).
//
// One CKTime produces the frame time (dt) that all gameplay integrates. Its quirks are
// speedrun-relevant and must stay exactly as they are:
//  - dt is the measured wall-clock delta, clamped to 0.1 s while running;
//  - a delta of exactly 0 becomes 0x3c23d70b (~0.01 s) in BOTH dt and the real delta;
//  - paused (state 1): dt is still produced, unclamped, but game time does not advance;
//  - stopped (2) / suspended (3): dt is 0; while the manager's clock is suspended nothing accumulates.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"

// vtables: IKTime 0xb15408 (abstract), CKTime 0xb15448. XXL2: K/KBasic/TimeManager/IKTime.h and
// O/O_CKTime.h, same slots and fields (outputs/remake/research/xxl2-symbols.md).
class IKTime {
public:
    enum ECurrentState : int32_t { RUNNING = 0, PAUSED = 1, STOPPED = 2, SYSTEM_PAUSED = 3, MAX_TIME_STATES = 4 };
    // The three times the clock keeps (XXL2 ETimeMode): scaled game time, unscaled game time, system time.
    enum ETimeMode : int32_t { SCALABLE_GAME_TIME = 0, FIXED_GAME_TIME = 1, SYSTEM_TIME = 2, NB_TIME_MODE = 3 };

    IKTime();
    virtual ~IKTime();                   // vt+0x00 / +0x04
    virtual double KGetExactTime() = 0;  // vt+0x08  seconds since Initialize (double)
    virtual int32_t Initialize() = 0;    // vt+0x0c  1 = ok (XXL2: KError)
    virtual void Destroy() = 0;          // vt+0x10  called before delete when Initialize fails
    virtual void Update();               // vt+0x14
    virtual void Stop();                 // vt+0x18
    virtual void Start();                // vt+0x1c
    virtual void Restart();              // vt+0x20
    virtual void Pause();                // vt+0x24
    virtual void Resume();               // vt+0x28
    virtual void SystemPause();          // vt+0x2c
    virtual void SystemResume();         // vt+0x30

    // +0x04 accumulated time per ETimeMode: [SCALABLE_GAME_TIME] adds the scaled dt while running,
    // [FIXED_GAME_TIME] the unscaled dt while running, [SYSTEM_TIME] the real delta unless the manager's
    // clock is system-paused (also while paused).
    float m_afCurrentTime[NB_TIME_MODE];
    float m_afLastTime[NB_TIME_MODE];   // +0x10 m_afCurrentTime before this Update
    // +0x1c this frame's delta per ETimeMode: [SCALABLE_GAME_TIME] = dt x CTimeManager::m_fTimeScale (what
    // gameplay reads), [SYSTEM_TIME] = the sample delta, 0x3c23d70b when the sample did not move.
    float m_afDeltaTime[NB_TIME_MODE];
    float m_fLastExactTime;             // +0x28 last KGetExactTime() as float; -1 = not sampled yet
    uint32_t m_fPauseExactTime;         // +0x2c never initialised or used by DotD's clock (a float in XXL2)
    int32_t m_eCurrentState;            // +0x30 ECurrentState
    int32_t m_eStateBeforeSystemPause;  // +0x34 state saved by SystemPause (the constructor sets 4)
};
DOTD_ASSERT_SIZE(IKTime, 0x38);
DOTD_ASSERT_OFFSET(IKTime, m_afCurrentTime, 0x04);
DOTD_ASSERT_OFFSET(IKTime, m_afDeltaTime, 0x1c);
DOTD_ASSERT_OFFSET(IKTime, m_fLastExactTime, 0x28);
DOTD_ASSERT_OFFSET(IKTime, m_eCurrentState, 0x30);

class CKTime : public IKTime {
public:
    CKTime();
    ~CKTime() override;
    double KGetExactTime() override;  // vt+0x08
    int32_t Initialize() override;    // vt+0x0c
    void Destroy() override;          // vt+0x10

    double m_fFrequency;          // +0x38 seconds per tick, 1e-6: sys_time_get_system_time() counts microseconds
    int64_t m_i64InitialCounter;  // +0x40 tick count at Initialize
};
DOTD_ASSERT_SIZE(CKTime, 0x48);
DOTD_ASSERT_OFFSET(CKTime, m_fFrequency, 0x38);
DOTD_ASSERT_OFFSET(CKTime, m_i64InitialCounter, 0x40);
