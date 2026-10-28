// CKQuakeCpntUpdater.h - plays a CKQuakeCpnt (key 0x986, vtable 0xb20f50, size 0x20). Original unit:
// CKQuakeCpntUpdater.cpp (0x24ebb8-0x24fba0). No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"
#include "k2000/components/CKSinCurve2DCpnt.h"
#include "k2000/logic/CKQuakeCpnt.h"
#include "k2000/util/TVector.h"

class CKQuakeCpntUpdater : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x26)
    DOTD_DECLARE_FACTORIES(CKQuakeCpntUpdater)

    // One 16-byte state per quake entry (CKQuakeCpntUpdater_AllocCurveStates_maybe 0x24fa00 allocates as many as the
    // quake has entries): the entry's oscillator state.
    using CurveState = CKSinCurve2DCpnt::State;

    CKQuakeCpntUpdater();  // 0x0024f848 CKQuakeCpntUpdater_Create (the constructor is inlined there)

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0024f958 CKQuakeCpntUpdater_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x0024fb60 CKQuakeCpntUpdater_PostLoad

    // 0x0024fa00 CKQuakeCpntUpdater_AllocCurveStates_maybe: one state per entry of the quake (one unused state
    // without a quake or entries); the old block freed.
    void AllocCurveStates();
    // The ShakeEffect_* functions (step 5, FX): this updater is the running instance of its quake.
    // 0x0024f770 CKQuakeCpntUpdater_Start / 0x0024f738 CKQuakeCpntUpdater_Stop: the quake's StartEffect / StopEffect.
    void Start();
    void Stop();
    // 0x0024f5c8 CKQuakeCpntUpdater_EvaluateScaled: the quake's Evaluate, every output times `scale`; zero outputs
    // without a quake.
    void EvaluateScaled(float dt, float scale, float out[15]);

    CKQuakeCpnt* m_pQuake;                 // +0x04 (Ghidra draft: CKQuakeCpnt*)
    uint8_t m_bRunning;                    // +0x08 StartEffect 1; PostLoad, StopEffect and the end of Evaluate 0
    uint8_t m_pad09[3];
    float m_fElapsed;                      // +0x0c seconds since the start; PostLoad sets 0
    uint32_t m_unk10;                      // +0x10 runtime
    TVector<CurveState, 1> m_curveStates;  // +0x14 the constructor: null, 1, 0; PostLoad allocates it
};
DOTD_ASSERT_SIZE(CKQuakeCpntUpdater::CurveState, 0x10);
DOTD_ASSERT_SIZE(CKQuakeCpntUpdater, 0x20);
DOTD_ASSERT_OFFSET(CKQuakeCpntUpdater, m_pQuake, 0x04);
DOTD_ASSERT_OFFSET(CKQuakeCpntUpdater, m_curveStates, 0x14);
