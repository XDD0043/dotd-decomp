// CTimeManager.cpp - reconstructed original translation unit 0x53958-0x53f10 (GAME_TOC1).
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
//   [x] 0x53958  CTimeManager_Construct_2_maybe  (same body as 0x53dc8)
//   [x] 0x53998  CTimeManager_Destroy
//   [x] 0x53a30  CTimeManager_SystemPause
//   [x] 0x53a78  CTimeManager_SystemResume
//   [x] 0x53ac0  CTimeManager_Start
//   [x] 0x53b08  CTimeManager_Restart
//   [x] 0x53b50  CTimeManager_Stop
//   [x] 0x53b98  CTimeManager_Pause
//   [x] 0x53be0  CTimeManager_Resume
//   [x] 0x53c28  CTimeManager_Update
//   [x] 0x53d78  CTimeManager_Destructor_maybe
//   [x] 0x53d88  CTimeManager_Destructor_2_maybe
//   [x] 0x53d98  CTimeManager_DeletingDestructor_maybe
//   [x] 0x53dc8  CTimeManager_Construct_maybe
//   [x] 0x53e08  CTimeManager_Initialize
#include "k2000/system/CTimeManager.h"

#include "crt/ppc_ops.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/system/IKTime.h"
#include "platform/fps.h"

// 0x00c5b84c g_pTimeManager (written by CTimeManager_Construct_maybe)
CTimeManager* g_pTimeManager = nullptr;

namespace {
// The frame-rate statistic lives in the two words after g_pTimeManager.
uint32_t s_fpsFrameCount = 0;  // 0x00c5b850
float s_fpsTimeSum = 0.0f;     // 0x00c5b854 sum of the clock's real deltas

constexpr float kDefaultFrameDuration = 0x1.47ae14p-6f;  // 0x3ca3d70a (0.02f)
constexpr float kOne = 1.0f;                             // TOC 0xc0e6e8
}  // namespace

// 0x00053dc8 CTimeManager_Construct_maybe. m_pTime and m_ui8FixedRateInaccuracy are not initialised.
CTimeManager::CTimeManager() {
    g_pTimeManager = this;
    m_properties = 0;
    m_fTimeScale = 1.0f;
    m_fFixedDt = kDefaultFrameDuration;
    m_ui16FrameRate = 0;
    m_ui8FixedRate = 50;
}

// 0x00053d78 CTimeManager_Destructor_maybe, 0x00053d98 CTimeManager_DeletingDestructor_maybe.
// The clock is not deleted here (Destroy does that).
CTimeManager::~CTimeManager() {}

// 0x00053e08 CTimeManager_Initialize
int32_t CTimeManager::Initialize() {
    m_pTime = new CKTime();
    if (m_pTime->Initialize() == 1) return 1;
    if (m_pTime != nullptr) {
        m_pTime->Destroy();
        delete m_pTime;  // vt+0x04
        m_pTime = nullptr;
    }
    return 0;
}

// 0x00053998 CTimeManager_Destroy
void CTimeManager::Destroy() {
    if (m_pTime == nullptr) return;
    m_pTime->Destroy();
    delete m_pTime;
    m_pTime = nullptr;
}

// 0x00053a30 .. 0x00053be0: forwarders to the clock's state methods.
void CTimeManager::SystemPause() { m_pTime->SystemPause(); }
void CTimeManager::SystemResume() { m_pTime->SystemResume(); }
void CTimeManager::Start() { m_pTime->Start(); }
void CTimeManager::Restart() { m_pTime->Restart(); }
void CTimeManager::Stop() { m_pTime->Stop(); }
void CTimeManager::Pause() { m_pTime->Pause(); }
void CTimeManager::Resume() { m_pTime->Resume(); }

// 0x00053c28 CTimeManager_Update
void CTimeManager::Update(int32_t /*unused*/) {
    const float savedFrameDuration = m_fFixedDt;
    if ((m_properties & 1) != 0 && (m_properties & 2) != 0) {
        // Debug: a random frame duration for this update (never enabled in the shipped game).
        const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
        const uint32_t fps = ((r * m_ui8FixedRateInaccuracy) >> 16) + (static_cast<uint32_t>(m_ui8FixedRate) + 1u);
        m_fFixedDt = kOne / static_cast<float>(static_cast<double>(fps));  // fcfid, frsp, fdivs
    }
    m_pTime->Update();
    // --fps N (not in the original; nothing while off): the 60 Hz frames this displayed frame stands for.
    dotd::fps::OnClockUpdate(m_pTime->m_afDeltaTime);
    if (s_fpsFrameCount > 99) {
        // fcfid + frsp of the count (100), fdivs, fctidz, then sth of the low 16 bits.
        const float fps = static_cast<float>(static_cast<double>(s_fpsFrameCount)) / s_fpsTimeSum;
        m_ui16FrameRate = static_cast<int16_t>(ppc::fctidz(fps));
        s_fpsFrameCount = 0;
        s_fpsTimeSum = 0.0f;
    } else {
        s_fpsFrameCount = s_fpsFrameCount + 1;
        s_fpsTimeSum = s_fpsTimeSum + m_pTime->m_afDeltaTime[IKTime::SYSTEM_TIME];  // fadds
    }
    m_fFixedDt = savedFrameDuration;
}
