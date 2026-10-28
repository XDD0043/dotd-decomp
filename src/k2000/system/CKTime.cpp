// CKTime.cpp - reconstructed original translation unit 0x54250-0x543d8 (GAME_TOC1).
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
//   [x] 0x54250  CKTime_KGetExactTime
//   [x] 0x542d8  CKTime_Initialize
//   [x] 0x54318  CKTime_Destructor_maybe
//   [x] 0x54328  CKTime_Construct_maybe
//   [ ] 0x54360  CKTime_Construct_2_maybe  (second compilation of the constructor)
//   [ ] 0x54398  CKTime_Destructor_2_maybe  (second compilation of the destructor)
//   [x] 0x543a8  CKTime_DeletingDestructor_maybe
//   [x] 0x54248  KStub_Nop_54248  (vt+0x10, emitted just before this unit)
#include "k2000/system/IKTime.h"
#include "platform/cell/sys_time.h"

namespace {
constexpr double kSecondsPerTick = 0x1.0c6f7a0b5ed8dp-20;  // 1e-6, TOC 0xc0e708 = 0x3eb0c6f7a0b5ed8d
}

// 0x00054328 CKTime_Construct_maybe
// Like the original, leaves m_fFrequency / m_i64InitialCounter unset: Initialize sets them, and
// CTimeManager_Initialize always calls Initialize right after construction.
CKTime::CKTime() {}

// 0x00054318 CKTime_Destructor_maybe, 0x000543a8 CKTime_DeletingDestructor_maybe
CKTime::~CKTime() = default;

// 0x00054250 CKTime_KGetExactTime
double CKTime::KGetExactTime() {
    double replayed;
    if (dotd::platform::ReadExactTimeOverride(&replayed)) return replayed;  // DEBUG (DOTD_REPLAY), not in the original
    const int64_t ticks = sys_time_get_system_time() - m_i64InitialCounter;  // subf. (64-bit)
    if (ticks >= 0) {
        return static_cast<double>(ticks) * m_fFrequency;  // fcfid, fmul
    }
    // A negative difference is converted as an unsigned 64-bit value: halve keeping the low bit as a
    // sticky bit, convert, double (rldicl/or, fcfid, fadd). Only reachable if the clock goes backwards.
    const uint64_t u = static_cast<uint64_t>(ticks);
    const double half = static_cast<double>(static_cast<int64_t>((u >> 1) | (u & 1)));
    return (half + half) * m_fFrequency;
}

// 0x000542d8 CKTime_Initialize
int32_t CKTime::Initialize() {
    m_fFrequency = kSecondsPerTick;
    m_i64InitialCounter = sys_time_get_system_time();
    return 1;
}

// 0x00054248 KStub_Nop_54248
void CKTime::Destroy() {}
