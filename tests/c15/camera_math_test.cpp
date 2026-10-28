// camera_math_test - step 5: the camera's shared math helpers (crt::Asinf, crt::Tanf, crt::FmodfRangeReduce,
// Vec3_GetYawAngleFromZ, Quat_Slerp, Math_ApproachWithAccelDecel, Math_ApproachAngleWithAccelDecel). The exact values
// checked are the ones that follow from the code paths (zero / boundary arguments, the octant constants, the identities
// of odd functions and of t = 0 / 1); the rest is checked against the true function with a tolerance.
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>

#include "crt/xatan.h"
#include "crt/xtanf.h"
#include "k2000/math/Quat.h"
#include "k2000/math/Vec3.h"
#include "k2000/misc/FloatApproach.h"

namespace {
int g_failures = 0;
#define CHECK(cond)                                                      \
    do {                                                                 \
        if (!(cond)) {                                                   \
            std::printf("FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond); \
            ++g_failures;                                                \
        }                                                                \
    } while (0)

uint32_t Bits(float f) {
    uint32_t u;
    std::memcpy(&u, &f, 4);
    return u;
}
bool Near(float a, double b, double tolerance) { return std::fabs(static_cast<double>(a) - b) <= tolerance; }

constexpr double kPi = 3.14159265358979323846;
constexpr uint32_t kHalfPiBits = 0x3fc90fdb;  // the octant constant pi/2 (0xa72850 + 8)
constexpr uint32_t kPiBits = 0x40490fdb;

void TestAsinf() {
    CHECK(Bits(crt::Asinf(0.0f)) == 0);
    CHECK(Bits(crt::Asinf(1.0f)) == kHalfPiBits);
    CHECK(Bits(crt::Asinf(-1.0f)) == (kHalfPiBits | 0x80000000u));
    CHECK(std::isnan(crt::Asinf(1.5f)));
    CHECK(std::isnan(crt::Asinf(-1.5f)));
    CHECK(std::isnan(crt::Asinf(std::nanf(""))));
    for (int i = 1; i < 1000; ++i) {
        const float x = static_cast<float>(i) / 1000.0f;
        const float value = crt::Asinf(x);
        CHECK(Bits(crt::Asinf(-x)) == (Bits(value) ^ 0x80000000u));  // flag 8 negates the result only
        CHECK(Near(value, std::asin(static_cast<double>(x)), 4e-7));
        CHECK(Near(value + crt::Acosf(x), kPi / 2, 1e-6));
    }
}

void TestTanf() {
    CHECK(Bits(crt::Tanf(0.0f)) == 0);
    for (int i = -4000; i <= 4000; ++i) {
        const float x = static_cast<float>(i) * 0.0125f;  // -50 .. 50: both sides of the +-40.7 reduction
        const float value = crt::Tanf(x);
        CHECK(Bits(crt::Tanf(-x)) == (Bits(value) ^ 0x80000000u) || value == 0.0f);  // odd
        const double truth = std::tan(static_cast<double>(x));
        if (std::fabs(truth) < 50.0) CHECK(Near(value, truth, 2e-5 * (1.0 + truth * truth) * (1.0 + std::fabs(x))));
    }
    CHECK(std::isnan(crt::Tanf(std::nanf(""))));
    // _FRteps: below 2^-12 tan r = r.
    CHECK(crt::Tanf(0.0001f) == 0.0001f);
}

void TestFmodf() {
    CHECK(crt::FmodfRangeReduce(7.0f, 2.0f) == 1.0f);
    CHECK(crt::FmodfRangeReduce(-7.0f, 2.0f) == -1.0f);
    CHECK(crt::FmodfRangeReduce(7.0f, -2.0f) == 1.0f);
    CHECK(crt::FmodfRangeReduce(1.5f, 2.0f) == 1.5f);
    CHECK(Bits(crt::FmodfRangeReduce(-1.5f, 2.0f)) == Bits(-1.5f));
    CHECK(crt::FmodfRangeReduce(6.0f, 2.0f) == 0.0f);
    CHECK(crt::FmodfRangeReduce(3.0e8f, 1.0f) == 0.0f);  // q above 2^23: no fraction bits
}

void TestYawFromZ() {
    const CVector3 zero = {0.0f, 0.0f, 0.0f};
    const CVector3 forward = {0.0f, 0.0f, 1.0f};
    const CVector3 back = {0.0f, 0.0f, -1.0f};
    const CVector3 right = {1.0f, 0.0f, 0.0f};
    const CVector3 left = {-1.0f, 0.0f, 0.0f};
    const CVector3 up = {0.0f, 5.0f, 0.0f};
    CHECK(Vec3_GetYawAngleFromZ(&zero) == 0.0f);
    CHECK(Vec3_GetYawAngleFromZ(&forward) == 0.0f);
    CHECK(Bits(Vec3_GetYawAngleFromZ(&back)) == kPiBits);
    CHECK(Bits(Vec3_GetYawAngleFromZ(&right)) == kHalfPiBits);  // acosf(0) = pi/2 exactly (the octant constant)
    float halfPi;
    const uint32_t halfPiBits = kHalfPiBits;
    std::memcpy(&halfPi, &halfPiBits, 4);
    CHECK(Vec3_GetYawAngleFromZ(&left) == 6.28318548202514648f - halfPi);
    CHECK(Bits(Vec3_GetYawAngleFromZ(&up)) == kHalfPiBits);  // (x, z) length 0, z = 0
    for (int i = 0; i < 360; ++i) {
        const double angle = (i + 0.5) * kPi / 180.0;
        const CVector3 v = {static_cast<float>(std::sin(angle) * 3.0), 1.0f, static_cast<float>(std::cos(angle) * 3.0)};
        CHECK(Near(Vec3_GetYawAngleFromZ(&v), angle, 1e-3));  // acos is steep near 0 and pi
    }
}

void TestSlerp() {
    const float a[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    const float b[4] = {0.0f, 0.0f, 0.70710677f, 0.70710677f};  // 90 degrees about z
    float out[4];
    Quat_Slerp(0.0f, out, a, b);
    for (int i = 0; i < 4; ++i) CHECK(Bits(out[i]) == Bits(a[i]));
    Quat_Slerp(1.0f, out, a, b);
    for (int i = 0; i < 4; ++i) CHECK(Bits(out[i]) == Bits(b[i]));
    Quat_Slerp(0.5f, out, a, b);
    CHECK(Near(out[0], 0.0, 0.0) && Near(out[1], 0.0, 0.0));
    CHECK(Near(out[2], std::sin(kPi / 8), 2e-6));
    CHECK(Near(out[3], std::cos(kPi / 8), 2e-6));
    // The short way: -b is the same rotation; t = 1 gives b negated back.
    const float negB[4] = {-b[0], -b[1], -b[2], -b[3]};
    Quat_Slerp(1.0f, out, a, negB);
    for (int i = 0; i < 4; ++i) CHECK(Bits(out[i]) == Bits(b[i]));
    // Nearly equal quaternions: the linear weights (1 - t, t).
    Quat_Slerp(0.25f, out, a, a);
    for (int i = 0; i < 4; ++i) CHECK(Bits(out[i]) == Bits(a[i]));
    // out may be a.
    float c[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    Quat_Slerp(1.0f, c, c, b);
    for (int i = 0; i < 4; ++i) CHECK(Bits(c[i]) == Bits(b[i]));
}

void TestApproach() {
    // {accel, decel, top, current, speed, target, bonus}
    float state[7] = {1.0f, 1.0f, 10.0f, 0.0f, 0.0f, 100.0f, 0.0f};
    CHECK(Math_ApproachWithAccelDecel(1.0f, state) == 1.0f);
    CHECK(state[4] == 1.0f);
    CHECK(Math_ApproachWithAccelDecel(1.0f, state) == 3.0f);
    CHECK(state[4] == 2.0f);
    float previous = state[3];
    float topSpeed = 0.0f;
    for (int i = 0; i < 400; ++i) {
        const float value = Math_ApproachWithAccelDecel(0.1f, state);
        CHECK(value == state[3]);
        CHECK(value >= previous && value <= 100.0f);
        if (state[4] > topSpeed) topSpeed = state[4];
        previous = value;
    }
    CHECK(state[3] == 100.0f);
    CHECK(topSpeed <= 10.0f);
    // On the target with no speed and no bonus: nothing changes.
    float idle[7] = {1.0f, 1.0f, 10.0f, 5.0f, 0.0f, 5.0f, 0.0f};
    CHECK(Math_ApproachWithAccelDecel(1.0f, idle) == 5.0f);
    CHECK(idle[4] == 0.0f);
    // Downwards, up to the first arrival: on the target the code takes the upward branch (`target < current` is
    // false), so a speed still negative there carries the value a little below the target before it settles.
    float down[7] = {2.0f, 2.0f, 4.0f, 10.0f, 0.0f, -10.0f, 0.0f};
    previous = down[3];
    int steps = 0;
    while (down[3] != -10.0f && steps < 400) {
        const float value = Math_ApproachWithAccelDecel(0.1f, down);
        CHECK(value <= previous && value >= -10.0f);
        CHECK(down[4] >= -4.0f && down[4] < 0.0f);
        previous = value;
        ++steps;
    }
    CHECK(down[3] == -10.0f);
    for (int i = 0; i < 100; ++i) Math_ApproachWithAccelDecel(0.1f, down);
    CHECK(Near(down[3], -10.0, 0.01));
}

void TestApproachAngle() {
    // From 6.0 to 0.2 the short way crosses 2 pi upwards.
    float state[7] = {1.0f, 1.0f, 2.0f, 6.0f, 0.0f, 0.2f, 0.0f};
    const float first = Math_ApproachAngleWithAccelDecel(0.1f, state);
    CHECK(first > 6.0f && first == state[3]);
    for (int i = 0; i < 400; ++i) Math_ApproachAngleWithAccelDecel(0.1f, state);
    CHECK(Near(state[3], 0.2, 1e-6));
    // Nothing to do: the wrapped current angle is returned, state[3] stays.
    float idle[7] = {1.0f, 1.0f, 2.0f, 7.0f, 0.0f, 7.0f, 0.0f};
    const float wrapped = Math_ApproachAngleWithAccelDecel(0.1f, idle);
    CHECK(idle[3] == 7.0f);
    CHECK(Near(wrapped, 7.0 - 2.0 * kPi, 2e-6));
    // From 1.0 to 5.0 the short way is downwards (through 0).
    float down[7] = {1.0f, 1.0f, 2.0f, 1.0f, 0.0f, 5.0f, 0.0f};
    Math_ApproachAngleWithAccelDecel(0.1f, down);
    CHECK(down[4] < 0.0f && down[3] < 1.0f);
}
}  // namespace

int main() {
    TestAsinf();
    TestTanf();
    TestFmodf();
    TestYawFromZ();
    TestSlerp();
    TestApproach();
    TestApproachAngle();
    if (g_failures != 0) {
        std::printf("camera_math: %d failures\n", g_failures);
        return 1;
    }
    std::printf("camera_math: all tests passed\n");
    return 0;
}
