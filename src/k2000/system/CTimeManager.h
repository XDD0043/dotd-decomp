// CTimeManager.h - owner of the frame clock (k2000). Original unit: CTimeManager.cpp (0x53958-0x53f10).
// Created by InitializeCKGameLoopSubsystems (CKGameLoop +0x30, GameEngineContext +0x48). Its clock
// (+0x04) is the "frame clock" every update receives.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"

class IKTime;

// vtable 0xb153f8 (destructors only). Size 0x18. Also the global g_pTimeManager (0xc5b84c).
// XXL2: K/KBasic/TimeManager/CTimeManager.h, the same fields and methods.
class CTimeManager {
public:
    CTimeManager();           // 0x00053dc8 (twin 0x53958)
    virtual ~CTimeManager();  // vt+0x00 / +0x04  0x53d78 / 0x53d98

    int32_t Initialize();  // 0x00053e08: creates the CKTime and initialises it; 1 = ok (XXL2: KError)
    void Destroy();        // 0x00053998
    // Each of these forwards to the clock's slot of the same name (IKTime).
    void SystemPause();    // 0x00053a30
    void SystemResume();   // 0x00053a78
    void Start();          // 0x00053ac0
    void Restart();        // 0x00053b08
    void Stop();           // 0x00053b50
    void Pause();          // 0x00053b98
    void Resume();         // 0x00053be0
    // 0x00053c28 CTimeManager_Update (XXL2: Update(IKTime*), the argument is unused; GameLoop passes 0).
    // With both m_properties bits set, m_fFixedDt is redrawn from the fixed rate and its inaccuracy;
    // then the clock updates, and m_ui16FrameRate is refreshed every 100 frames.
    void Update(int32_t unused);

    IKTime* m_pTime;                    // +0x04 the frame clock (a CKTime); not set by the constructor
    int16_t m_ui16FrameRate;            // +0x08 100 / (sum of 100 real deltas), refreshed every 100 frames
    uint8_t m_properties;               // +0x0a (XXL2 CBitArray8) bits 0 and 1 together: random fixed dt
    uint8_t m_ui8FixedRate;             // +0x0b frames per second of the fixed rate; constructor sets 50
    uint8_t m_ui8FixedRateInaccuracy;   // +0x0c random spread added to the rate; not set by the constructor
    uint8_t m_pad0d[3];                 // +0x0d
    float m_fTimeScale;                 // +0x10 multiplies dt (constructor: 1.0)
    float m_fFixedDt;                   // +0x14 constructor: 0x3ca3d70a (0.02 = 1/50 s)
};
DOTD_ASSERT_SIZE(CTimeManager, 0x18);
DOTD_ASSERT_OFFSET(CTimeManager, m_pTime, 0x04);
DOTD_ASSERT_OFFSET(CTimeManager, m_ui16FrameRate, 0x08);
DOTD_ASSERT_OFFSET(CTimeManager, m_fTimeScale, 0x10);

// 0x00c5b84c: set by the CTimeManager constructor; IKTime::Update reads it every frame.
extern CTimeManager* g_pTimeManager;
