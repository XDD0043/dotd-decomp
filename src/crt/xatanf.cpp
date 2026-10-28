// xatanf.cpp - the game's float arc tangent. See xatanf.h.
#include "crt/xatanf.h"

#include "crt/ppc_ops.h"

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

}  // namespace crt
