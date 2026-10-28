// ShakeOscillator.cpp - reconstructed original translation unit 0x2501e0-0x2503e8 (GAME_TOC1, main_toc1), 1 functions, 1 live.
// Primary owner: ShakeOscillator (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2501e0  CKSinCurve2DCpnt_Update_maybe
#include <cmath>

#include "k2000/components/CKSinCurve2DCpnt.h"
#include "crt/ppc_ops.h"
#include "crt/xsinf.h"

// 0x002501e0 CKSinCurve2DCpnt_Update_maybe (step 5, FX): a CKSinCurve2DCpnt driven by its state. The sine of a
// phase with the sign bit clear is the game's inlined polynomial (TOC1 +0xb4.. the same constants as crt::InlineSinf);
// a negative phase goes to the library's sinf 0x9a1390 with -phase and the result is negated.
float ShakeOscillator_Update(float dt, const CKSinCurve2DCpnt* curve, CKSinCurve2DCpnt::State* state) {
    if (state->m_bActive == 0) return state->m_fValue;
    const float time = dt + state->m_fTime;
    state->m_fTime = time;
    if (!(time < curve->m_fDuration)) {
        state->m_fPhase = 0.0f;
        state->m_bActive = 0;
        state->m_fTime = 0.0f;
        state->m_fValue = 0.0f;
        return state->m_fValue;
    }
    const float u = time / curve->m_fDuration;
    const float phase0 = state->m_fPhase;
    const float step = dt * 6.2831855f * curve->m_fFrequency;  // two fmuls: dt * 2pi, then * frequency
    const float phase = ppc::fmadds(step, Curve_EvaluatePiecewiseLinear(u, &curve->m_vFrequencyCurve), phase0);
    state->m_fPhase = phase;
    float sine;
    if (std::signbit(phase)) {
        sine = -crt::LibSinf(-phase);
    } else {
        sine = crt::InlineSinf(phase);
    }
    const float scaled = sine * curve->m_fAmplitude;
    state->m_fValue = scaled * Curve_EvaluatePiecewiseLinear(u, &curve->m_vAmplitudeCurve);
    return state->m_fValue;
}
