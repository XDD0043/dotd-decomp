// camera_shake_test - step 5 (FX): the camera shake evaluation (Curve_EvaluatePiecewiseLinear, ShakeOscillator_Update,
// CKQuakeCpnt Start / Evaluate, CKQuakeCpntUpdater EvaluateScaled / Stop).
//
// The quake is LVL010's CKQuakeCpnt #141 (work/scratch-fx/quakes.py parses LVL010.KP3): 1 s, entry 0 = curve #181 on
// output 3 (amplitude 0.7), entry 1 = curve #182 on output 5 (amplitude 1.5). It is the shake of the idle recording's
// first fight intro (+585 and +617): a least-squares fit of the recording's pitch / roll from +646 to +676 (the second
// shake alone) gives this quake with a distance attenuation of about 0.5 (residual 5 %), and the shake ends exactly 1 s
// (60 frames) after +617. The exact values checked follow from the code paths (zero before the start, the end frame,
// the curves' key points); the oscillation is checked against a double-precision model of the same formulas.
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>

#include "k2000/components/CKQuakeCpntUpdater.h"
#include "k2000/components/CKSinCurve2DCpnt.h"
#include "k2000/logic/CKQuakeCpnt.h"

namespace {
int g_failures = 0;
#define CHECK(cond)                                                      \
    do {                                                                 \
        if (!(cond)) {                                                   \
            std::printf("FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond); \
            ++g_failures;                                                \
        }                                                                \
    } while (0)

float F(uint32_t bits) {
    float f;
    std::memcpy(&f, &bits, 4);
    return f;
}

using Point = CKCurve2DCpnt::Point;

void SetPoints(TVector<Point, 20>* v, Point* points, uint32_t count) {
    v->m_pBlock = points;
    v->m_ui32NbElt = count;
    v->m_ui32NbUsedElt = count;
}

// The double-precision model of one curve (CKSinCurve2DCpnt_Update_maybe's formulas).
struct Model {
    double time = 0.0, phase = 0.0, value = 0.0;
    bool active = true;
};
double Eval(double t, const Point* p, uint32_t n) {
    if (t <= p[0].m_fX) return p[0].m_fY;
    if (t >= p[n - 1].m_fX) return p[n - 1].m_fY;
    for (uint32_t i = 0; i + 1 < n; ++i) {
        if (t >= p[i].m_fX && t <= p[i + 1].m_fX) {
            const double u = (t - p[i].m_fX) / (p[i + 1].m_fX - p[i].m_fX);
            return (1.0 - u) * p[i].m_fY + u * p[i + 1].m_fY;
        }
    }
    return 0.0;
}
double Step(Model& m, double dt, const CKSinCurve2DCpnt& c, const Point* fc, uint32_t nf, const Point* ac, uint32_t na) {
    if (!m.active) return m.value;
    m.time += dt;
    if (m.time >= c.m_fDuration) {
        m = Model();
        m.active = false;
        return 0.0;
    }
    const double u = m.time / c.m_fDuration;
    m.phase += dt * 2.0 * 3.14159265358979 * c.m_fFrequency * Eval(u, fc, nf);
    m.value = std::sin(m.phase) * c.m_fAmplitude * Eval(u, ac, na);
    return m.value;
}

void TestCurve() {
    Point pts[3] = {{0.0f, 1.0f}, {1.0f, 0.0f}, {2.0f, 4.0f}};
    TVector<Point, 20> v;
    SetPoints(&v, pts, 0);
    CHECK(Curve_EvaluatePiecewiseLinear(0.5f, &v) == 0.0f);
    SetPoints(&v, pts, 1);
    CHECK(Curve_EvaluatePiecewiseLinear(7.0f, &v) == 1.0f);
    SetPoints(&v, pts, 3);
    CHECK(Curve_EvaluatePiecewiseLinear(-1.0f, &v) == 1.0f);   // before the first point
    CHECK(Curve_EvaluatePiecewiseLinear(3.0f, &v) == 4.0f);    // after the last
    CHECK(Curve_EvaluatePiecewiseLinear(1.0f, &v) == 0.0f);    // on a key
    CHECK(Curve_EvaluatePiecewiseLinear(2.0f, &v) == 4.0f);
    CHECK(Curve_EvaluatePiecewiseLinear(0.25f, &v) == 0.75f);  // (1 - 0.25) * 1 + 0.25 * 0, exact
    CHECK(Curve_EvaluatePiecewiseLinear(1.5f, &v) == 2.0f);
    CHECK(Curve_EvaluatePiecewiseLinear(std::nanf(""), &v) == 0.0f);  // no test holds: 0 after the last segment
}

void TestQuake141() {
    // Curve #181: 1 s, 8 Hz, amplitude -1; curve #182: 1 s, 5 Hz, amplitude 1 (the words of LVL010.KP3).
    Point fc181[2] = {{0.0f, 1.0f}, {1.0f, 0.0f}};
    Point ac181[4] = {{0.0f, 1.0f}, {F(0x3e570a3d), F(0x3f0cccce)}, {F(0x3f066666), F(0x3e800002)}, {1.0f, 0.0f}};
    Point fc182[2] = {{0.0f, 1.0f}, {1.0f, 0.0f}};
    Point ac182[4] = {{0.0f, 1.0f}, {F(0x3e6147ae), F(0x3f07ae15)}, {F(0x3f028f5c), F(0x3dccccd0)}, {1.0f, 0.0f}};
    CKSinCurve2DCpnt c181;
    c181.m_fDuration = 1.0f;
    c181.m_fFrequency = 8.0f;
    c181.m_fAmplitude = -1.0f;
    SetPoints(&c181.m_vFrequencyCurve, fc181, 2);
    SetPoints(&c181.m_vAmplitudeCurve, ac181, 4);
    CKSinCurve2DCpnt c182;
    c182.m_fDuration = 1.0f;
    c182.m_fFrequency = 5.0f;
    c182.m_fAmplitude = 1.0f;
    SetPoints(&c182.m_vFrequencyCurve, fc182, 2);
    SetPoints(&c182.m_vAmplitudeCurve, ac182, 4);

    CKQuakeCpnt::Entry entries[2] = {
        {&c181, 0x8, F(0x3e19999a), F(0x3f333333), F(0x3dcccccd), F(0x3dcccccd), 0.0f},
        {&c182, 0x20, 0.5f, 1.5f, F(0x3dcccccd), F(0x3dcccccd), 0.0f},
    };
    CKQuakeCpnt quake;
    quake.m_fDuration = 1.0f;
    quake.m_entries.m_pBlock = entries;
    quake.m_entries.m_ui32NbElt = 2;
    quake.m_entries.m_ui32NbUsedElt = 2;

    CKSinCurve2DCpnt::State states[2];
    std::memset(states, 0xcd, sizeof(states));
    CKQuakeCpntUpdater effect;
    effect.m_pQuake = &quake;
    effect.m_bRunning = 0;
    effect.m_fElapsed = 0.0f;
    effect.m_curveStates.m_pBlock = states;
    effect.m_curveStates.m_ui32NbElt = 2;
    effect.m_curveStates.m_ui32NbUsedElt = 2;

    float out[15];
    effect.EvaluateScaled(1.0f / 60.0f, 0.5f, out);  // not running: all zero, nothing advances
    for (float o : out) CHECK(o == 0.0f);
    CHECK(effect.m_fElapsed == 0.0f);

    effect.Start();
    CHECK(effect.m_bRunning == 1 && effect.m_fElapsed == 0.0f);
    CHECK(states[0].m_bActive == 1 && states[0].m_fTime == 0.0f && states[0].m_fPhase == 0.0f && states[0].m_fValue == 0.0f);
    CHECK(states[1].m_bActive == 1);

    const float dt = 1.0f / 60.0f;
    const float scale = 0.5f;
    // The frame on which the effect stops: the first whose float sum of dt reaches the duration.
    int stopFrame = 0;
    for (float t = 0.0f; t < 1.0f; ++stopFrame) t = dt + t;
    Model m181, m182;
    double maxError = 0.0;
    int frames = 0;
    for (int frame = 1; frame <= 70; ++frame) {
        effect.EvaluateScaled(dt, scale, out);
        for (int c = 0; c < 15; ++c) {
            if (c != 3 && c != 5) CHECK(out[c] == 0.0f);
        }
        if (frame < stopFrame) {
            CHECK(effect.m_bRunning == 1);
            const double v181 = Step(m181, dt, c181, fc181, 2, ac181, 4);
            const double v182 = Step(m182, dt, c182, fc182, 2, ac182, 4);
            const double e3 = std::fabs(out[3] - 0.5 * 0.7 * v181);
            const double e5 = std::fabs(out[5] - 0.5 * 1.5 * v182);
            if (e3 > maxError) maxError = e3;
            if (e5 > maxError) maxError = e5;
            ++frames;
        } else {
            // The stopping frame and after: zero outputs, the states reset.
            CHECK(effect.m_bRunning == 0);
            CHECK(out[3] == 0.0f && out[5] == 0.0f);
            CHECK(effect.m_fElapsed == 0.0f);
            CHECK(states[0].m_bActive == 0 && states[1].m_bActive == 0);
        }
    }
    CHECK(stopFrame == 60 || stopFrame == 61);
    CHECK(frames == stopFrame - 1);
    std::printf("quake #141: stops on frame %d; largest difference to the double model %.3g\n", stopFrame, maxError);
    CHECK(maxError < 2e-5);

    // Restart, then Stop: the running byte and every state cleared.
    effect.Start();
    effect.EvaluateScaled(dt, 1.0f, out);
    CHECK(out[3] != 0.0f && out[5] != 0.0f);
    effect.Stop();
    CHECK(effect.m_bRunning == 0 && effect.m_fElapsed == 0.0f);
    CHECK(states[0].m_bActive == 0 && states[0].m_fValue == 0.0f && states[1].m_fPhase == 0.0f);
    // The curves point at the stack arrays: the destructor (0x24fde0) frees heap blocks only.
    c181.m_vFrequencyCurve.m_pBlock = nullptr;
    c181.m_vAmplitudeCurve.m_pBlock = nullptr;
    c182.m_vFrequencyCurve.m_pBlock = nullptr;
    c182.m_vAmplitudeCurve.m_pBlock = nullptr;
}

}  // namespace

int main() {
    TestCurve();
    TestQuake141();
    if (g_failures != 0) {
        std::printf("camera_shake_test: %d failure(s)\n", g_failures);
        return 1;
    }
    std::printf("camera_shake_test: OK\n");
    return 0;
}
