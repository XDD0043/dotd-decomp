// xatanf.cpp - the game's float arc tangent. See xatanf.h.
#include "crt/xatanf.h"

#include <cstring>

#include "crt/ppc_ops.h"
#include "crt/xatan2.h"

namespace crt {

namespace {

// _FAtan_maybe 0x0077fe18 (library TOC -0x2cbc..-0x2ca4): all single-precision instructions.
constexpr float kTan15 = 0.2679491937160492f;      // 0x3e8930a3  tan(pi / 12)
constexpr float kSqrt3 = 1.7320507764816284f;      // 0x3fddb3d7
constexpr float kOne = 1.0f;
constexpr float kA = 0.08280213922262192f;         // 0x3da9942b
constexpr float kB = 0.8483080863952637f;          // 0x3f592ab8
constexpr float kC = 0.5149751901626587f;          // 0x3f03d56a
constexpr float kEpsilon = 0.000244140625f;        // 0x00c4ade0
// 0x00a72850: the octant offsets added to the reduced angle, indexed by the low three bits of the mode.
constexpr float kOctant[8] = {0.0f,
                              0.5235987901687622f,
                              1.5707963705062866f,
                              1.0471975803375244f,
                              1.5707963705062866f,
                              2.094395160675049f,
                              3.1415927410125732f,
                              2.6179938316345215f};

float FAtan(float x, uint32_t mode) {
    if (x > kTan15) {
        mode |= 1;
        const float denominator = x + kSqrt3;
        const float numerator = ppc::fmsubs(x, kSqrt3, kOne);
        x = numerator / denominator;
    }
    if (-kEpsilon > x || x > kEpsilon) {
        const float square = x * x;
        const float cube = x * square;
        const float inner = ppc::fmadds(square, kA, kB);
        const float numerator = ppc::fmadds(cube, kC, x);
        const float denominator = ppc::fmadds(square, inner, kOne);
        x = numerator / denominator;
    }
    if ((mode & 2) != 0) x = -x;
    x = x + kOctant[mode & 7];
    if ((mode & 8) != 0) x = -x;
    return x;
}

}  // namespace

float Atanf(float x) {
    if (x == 0.0f) return x;
    uint32_t mode = 0;
    if (x < 0.0f) {
        x = -x;
        mode = 8;
    }
    if (1.0f < x) {
        mode ^= 2;
        x = 1.0f / x;
    }
    return FAtan(x, mode);
}

namespace {
// 0x0077ffd8 _FDtest_maybe: the class of a float from its two halves: 2 NaN, 1 infinity, 0 zero, -1 finite (a
// denormal included).
int32_t FDtest(float x) {
    uint32_t bits;
    std::memcpy(&bits, &x, 4);
    const uint32_t hi = bits >> 16;
    const uint32_t lo = bits & 0xffffu;
    if ((hi & 0x7f80u) == 0x7f80u) {
        if ((hi & 0x7fu) != 0) return 2;
        return lo == 0 ? 1 : 2;
    }
    if ((hi & 0x7fffu) != 0) return -1;
    return lo == 0 ? 0 : -1;
}
bool FSignBit(float x) {
    uint32_t bits;
    std::memcpy(&bits, &x, 4);
    return (bits >> 31) != 0;
}
}  // namespace

// 0x0077e9f0 atan2f (library TOC -0x2e78 = 0, -0x2e7c = 1).
float Atan2f(float y, float x) {
    const int32_t xClass = FDtest(x);  // the first _FDtest is of x (the stack copy of f2)
    const int32_t yClass = FDtest(y);
    if (xClass <= 0 && yClass <= 0) {
        uint32_t mode = 0;
        if (FSignBit(y)) {
            y = -y;
            mode = 8;
        }
        if (FSignBit(x)) {
            x = -x;
            mode ^= 6;
        }
        float ratio;
        if (!(x >= y)) {  // bge: a NaN cannot reach here
            mode ^= 2;
            ratio = x / y;
        } else {
            ratio = xClass == 0 ? 0.0f : y / x;
        }
        return FAtan(ratio, mode);
    }
    if (yClass == 2) return y;
    if (xClass == 2) return x;
    const float ratio = xClass == yClass ? 1.0f : 0.0f;  // both infinite: 1
    uint32_t mode = FSignBit(y) ? 8u : 0u;
    if (FSignBit(x)) mode |= 6;
    if (yClass == 1) mode ^= 2;
    return FAtan(ratio, mode);
}

}  // namespace crt
