// IKTime.cpp - reconstructed original translation unit 0x53f10-0x54250 (GAME_TOC1).
// Decompiled from the PPC assembly (not from the decompiler's output, which shows double arithmetic
// where the code uses single-precision fsubs/fmuls/fadds).
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x53f10  IKTime_Construct_maybe
//   [ ] 0x53f60  IKTime_Construct_2_maybe  [dead]
//   [x] 0x53fb0  IKTime_Update
//   [x] 0x54150  IKTime_Stop
//   [x] 0x54160  IKTime_Start
//   [x] 0x541c8  IKTime_Restart
//   [x] 0x541f0  IKTime_Pause
//   [x] 0x54200  IKTime_Resume
//   [x] 0x54210  IKTime_SystemResume
//   [x] 0x54228  IKTime_SystemPause
//   [x] 0x54248  KStub_Nop_54248  (CKTime::Destroy, vt+0x10 of 0xb15448; in CKTime.cpp)
//
//   [x] 0x9961c0  IKTime_DeletingDestructor_maybe  [inline]
//   [x] 0x9961f0  IKTime_Destructor_maybe  [inline]
#include "k2000/system/IKTime.h"

#include "k2000/system/CTimeManager.h"
#include "platform/fps.h"

namespace {
// TOC constants, bit-exact (0x3c23d70b is one ulp above the float nearest to 0.01).
constexpr float kNotSampled = -1.0f;            // 0xbf800000 (TOC 0xc0e6f0)
constexpr float kMaxDt = 0x1.99999ap-4f;        // 0x3dcccccd = 0.1f (TOC 0xc0e6f4)
constexpr float kZeroDeltaDt = 0x1.47ae16p-7f;  // 0x3c23d70b (TOC 0xc0e6f8)
}  // namespace

// 0x00053f10 IKTime_Construct_maybe
IKTime::IKTime()
    : m_afCurrentTime{0.0f, 0.0f, 0.0f},
      m_afLastTime{0.0f, 0.0f, 0.0f},
      m_afDeltaTime{0.0f, 0.0f, 0.0f},
      m_fLastExactTime(kNotSampled),
      m_eCurrentState(STOPPED),
      m_eStateBeforeSystemPause(4) {
    // m_fPauseExactTime is not initialised by the original constructor (the heap content stays).
}

// 0x009961f0 IKTime_Destructor_maybe, 0x009961c0 IKTime_DeletingDestructor_maybe
IKTime::~IKTime() = default;

// 0x00053fb0 IKTime_Update
void IKTime::Update() {
    if (m_fLastExactTime < 0.0f) {  // fcmpu + blt against the TOC 0.0f (false for NaN)
        m_fLastExactTime = static_cast<float>(KGetExactTime());  // frsp
    }
    const double exact = KGetExactTime();
    const float now = static_cast<float>(exact);  // frsp
    float realDt = now - m_fLastExactTime;        // fsubs
    if (dotd::fps::Unlocked()) {
        // --fps N (not in the original): the delta from the exact (double) times. The float times are 1 ms apart after
        // 2.3 hours, so at hundreds of frames per second two samples could round to the same float, and a delta of 0
        // becomes 0.01 s below (the game would run fast). Only when the last sample is the one this clock stored.
        static double s_lastExact = -1.0;
        if (s_lastExact >= 0.0 && static_cast<float>(s_lastExact) == m_fLastExactTime && exact >= s_lastExact) {
            realDt = static_cast<float>(exact - s_lastExact);
        }
        s_lastExact = exact;
    }
    float dt;
    if (m_eCurrentState == RUNNING) {
        // fcmpu + ble / bne: both branch on "unordered", so a NaN delta is passed through unchanged.
        if (realDt > kMaxDt) {
            dt = kMaxDt;
        } else if (realDt == 0.0f) {
            realDt = kZeroDeltaDt;  // BUG(original)?: the substitute also lands in m_afDeltaTime[SYSTEM_TIME] / m_afCurrentTime[SYSTEM_TIME]
            dt = kZeroDeltaDt;
        } else {
            dt = realDt;
        }
    } else if (m_eCurrentState == PAUSED) {
        dt = realDt;  // paused: reported unclamped, but no time accumulates below
    } else {
        dt = 0.0f;  // stopped / suspended
    }

    // The original re-reads g_pTimeManager->m_pTime->m_eCurrentState before each of the three blocks; nothing
    // in between can change it, so reading it once is equivalent.
    const bool managerSuspended = g_pTimeManager->m_pTime->m_eCurrentState == SYSTEM_PAUSED;

    const float time = m_afCurrentTime[SCALABLE_GAME_TIME];
    m_afDeltaTime[SCALABLE_GAME_TIME] = dt;
    m_afLastTime[SCALABLE_GAME_TIME] = time;
    if (!managerSuspended) {
        m_afDeltaTime[SCALABLE_GAME_TIME] = dt * g_pTimeManager->m_fTimeScale;  // fmuls
        if (m_eCurrentState == RUNNING) {
            m_afCurrentTime[SCALABLE_GAME_TIME] = time + m_afDeltaTime[SCALABLE_GAME_TIME];  // fadds
        }
    }

    const float unscaledTime = m_afCurrentTime[FIXED_GAME_TIME];
    m_afDeltaTime[FIXED_GAME_TIME] = dt;
    m_afLastTime[FIXED_GAME_TIME] = unscaledTime;
    if (!managerSuspended && m_eCurrentState == RUNNING) {
        m_afCurrentTime[FIXED_GAME_TIME] = unscaledTime + dt;  // fadds
    }

    const float realTime = m_afCurrentTime[SYSTEM_TIME];
    m_afDeltaTime[SYSTEM_TIME] = realDt;
    m_afLastTime[SYSTEM_TIME] = realTime;
    if (!managerSuspended) {
        m_afCurrentTime[SYSTEM_TIME] = realTime + realDt;  // fadds: no running check (real time also runs while paused)
    }

    m_fLastExactTime = now;
}

// 0x00054150 IKTime_Stop
void IKTime::Stop() { m_eCurrentState = STOPPED; }

// 0x00054160 IKTime_Start
void IKTime::Start() {
    m_eCurrentState = RUNNING;
    m_afCurrentTime[FIXED_GAME_TIME] = 0.0f;
    m_afCurrentTime[SCALABLE_GAME_TIME] = 0.0f;
    m_fLastExactTime = static_cast<float>(KGetExactTime());  // frsp
}

// 0x000541c8 IKTime_Restart
void IKTime::Restart() {
    m_fLastExactTime = kNotSampled;
    m_afDeltaTime[FIXED_GAME_TIME] = 0.0f;
    m_eCurrentState = RUNNING;
    m_afCurrentTime[SCALABLE_GAME_TIME] = 0.0f;
    m_afDeltaTime[SCALABLE_GAME_TIME] = 0.0f;
    m_afCurrentTime[FIXED_GAME_TIME] = 0.0f;
}

// 0x000541f0 IKTime_Pause
void IKTime::Pause() { m_eCurrentState = PAUSED; }

// 0x00054200 IKTime_Resume
void IKTime::Resume() { m_eCurrentState = RUNNING; }

// 0x00054228 IKTime_SystemPause
void IKTime::SystemPause() {
    if (m_eCurrentState == SYSTEM_PAUSED) return;
    m_eStateBeforeSystemPause = m_eCurrentState;
    m_eCurrentState = SYSTEM_PAUSED;
}

// 0x00054210 IKTime_SystemResume
void IKTime::SystemResume() {
    if (m_eCurrentState != SYSTEM_PAUSED) return;
    m_eCurrentState = m_eStateBeforeSystemPause;
}
