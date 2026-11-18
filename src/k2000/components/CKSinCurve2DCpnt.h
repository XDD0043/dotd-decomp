// CKSinCurve2DCpnt.h - a sine curve with two point lists (key 0x886, vtable 0xb20fa8, size 0x28). Original
// unit: CKSinCurve2DCpnt.cpp (0x24fba0-0x2501e0). No XXL2 class of this name.
//
// Both point lists go through 0x246e88 (Ghidra CKSinCurve2DCpnt_LoadKeys_maybe, in Mat4_2.cpp): a word
// that is dropped, a count, then the points.
#pragma once
#include <cstdint>

#include "k2000/components/CKCurve2DCpnt.h"
#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class CKSinCurve2DCpnt : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x22)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ba388
        return key == 0x886 || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKSinCurve2DCpnt)

    using Point = CKCurve2DCpnt::Point;

    CKSinCurve2DCpnt();  // 0x0024ffb0 CKSinCurve2DCpnt_Create (the constructor is inlined there)
    // 0x0024fde0 CKSinCurve2DCpnt_Destructor (0x24fe58 Destructor_2 the same, 0x250158 DeletingDestructor + delete): the
    // amplitude then the frequency curve blocks freed (the fields left as they are). vt+0x10 0x24fed0 Destroy (empty)
    // and vt+0x24 0x24fdd8 RecursiveRegistration (returns 1) are the defaults.
    ~CKSinCurve2DCpnt() override;

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00250010 CKSinCurve2DCpnt_Load

    // The playback state of one quake entry (16 bytes; CKQuakeCpntUpdater +0x14 holds one per entry).
    struct State {
        uint8_t m_bActive;    // +0x00 ShakeEffectState_Start 1, the end of the oscillation 0
        uint8_t m_pad01[3];
        float m_fTime;        // +0x04 seconds since the entry began oscillating
        float m_fPhase;       // +0x08 radians
        float m_fValue;       // +0x0c the last output
    };

    // 0x0024fc28 CKSinCurve2DCpnt_StartState_maybe / 0x0024fc48 CKSinCurve2DCpnt_ResetState_maybe: `state` zeroed with the active
    // byte 1 / 0 (the curve itself is not read).
    void StartState(State* state) const;
    void ResetState(State* state) const;

    // The names: CKSinCurve2DCpnt_Update_maybe 0x2501e0 reads them as below (_maybe: the curves' meaning from that code).
    float m_fDuration;                   // +0x04 the oscillation's length (s)
    float m_fFrequency;                  // +0x08 Hz (dt * 2pi * frequency * curve is the phase step)
    float m_fAmplitude;                  // +0x0c
    TVector<Point, 20> m_vFrequencyCurve;  // +0x10 frequency factor over the normalised time; constructor null, 20, 0
    TVector<Point, 20> m_vAmplitudeCurve;  // +0x1c amplitude envelope over the normalised time; constructor null, 20, 0
};
DOTD_ASSERT_SIZE(CKSinCurve2DCpnt::State, 0x10);
DOTD_ASSERT_SIZE(CKSinCurve2DCpnt, 0x28);
DOTD_ASSERT_OFFSET(CKSinCurve2DCpnt, m_fDuration, 0x04);
DOTD_ASSERT_OFFSET(CKSinCurve2DCpnt, m_fFrequency, 0x08);
DOTD_ASSERT_OFFSET(CKSinCurve2DCpnt, m_fAmplitude, 0x0c);
DOTD_ASSERT_OFFSET(CKSinCurve2DCpnt, m_vFrequencyCurve, 0x10);
DOTD_ASSERT_OFFSET(CKSinCurve2DCpnt, m_vAmplitudeCurve, 0x1c);

// 0x00246e88 CKSinCurve2DCpnt_LoadKeys_maybe (Mat4_2.cpp): u32 dropped, u32 count; with a count, the list
// is sized to exactly count points, then count points are read in one block and byte-swapped. A count of
// 0 leaves the list untouched.
void CKSinCurve2DCpnt_LoadKeys(TVector<CKCurve2DCpnt::Point, 20>* points, IKFile* file);

// 0x00246bb8 Curve_EvaluatePiecewiseLinear (Mat4_2.cpp): the value at `t` of the points (x ascending): 0 without
// points, the first point's y with one, the end values outside the x range, the point's y at an x, the linear
// interpolation inside a segment (and 0 when t is none of these, e.g. NaN).
float Curve_EvaluatePiecewiseLinear(float t, const TVector<CKCurve2DCpnt::Point, 20>* points);

// 0x002501e0 CKSinCurve2DCpnt_Update_maybe (ShakeOscillator.cpp): one step of a quake entry's oscillation: while
// `state` is active its time advances by dt; past the curve's duration the state is cleared, otherwise the phase
// advances by dt * 2pi * frequency * frequency curve and the value is sin(phase) * amplitude * amplitude curve.
// Returns the state's value.
float ShakeOscillator_Update(float dt, const CKSinCurve2DCpnt* curve, CKSinCurve2DCpnt::State* state);
