// xatan.cpp - the game's float arc cosine and arc sine. See xatan.h.
//
// Math_Acosf 0x00780c90 reduces to _FAtan_maybe 0x0077fe18 (the Dinkumware float atan: argument
// reduction by tan(pi/12), a rational approximation, then the octant constant and sign). Everything is
// single precision. The constants are library TOC slots (0xc25974 -0x2cbc..-0x2ca4, -0x2a54, -0x2a50), the
// threshold _FRteps at 0xc4ade0 (2^-12), the octant table at 0xa72850 and the NaN at 0xc4adc0.
#include "crt/xatan.h"

#include <cmath>
#include <cstring>

#include "crt/ppc_ops.h"

namespace crt {

namespace {

float FromBits(uint32_t bits) {
    float value;
    std::memcpy(&value, &bits, 4);
    return value;
}

const float kTan15 = FromBits(0x3e8930a3);     // tan(pi/12)
const float kSqrt3 = FromBits(0x3fddb3d7);
constexpr float kOne = 1.0f;
const float kRteps = FromBits(0x39800000);     // 0xc4ade0, 2^-12
const float kAtanA = FromBits(0x3f03d56a);     // 0.5149751901626587
const float kAtanB = FromBits(0x3da9942b);     // 0.08280213922262192
const float kAtanC = FromBits(0x3f592ab8);     // 0.8483080863952637
const float kInvSqrtHalf = FromBits(0x3f3504f3);  // 0.7071067690849304

// 0xa72850: the octant constants, indexed by the flag word & 7 (bits: 1 reduced, 2 negate, 4 / 8 combine).
constexpr uint32_t kOctantBits[8] = {0x00000000, 0x3f060a92, 0x3fc90fdb, 0x3f860a92,
                                     0x3fc90fdb, 0x40060a92, 0x40490fdb, 0x40278d36};

float OctantConstant(uint32_t index) { return FromBits(kOctantBits[index]); }

// 0x0077fe18 _FAtan_maybe
float FAtan(float x, uint32_t flags) {
    if (x > kTan15) {
        flags |= 1;
        const float sum = x + kSqrt3;
        const float numerator = ppc::fmsubs(x, kSqrt3, kOne);
        x = numerator / sum;
    }
    if (!(-kRteps > x) && !(x > kRteps)) {
        // small: no polynomial
    } else {
        const float x2 = x * x;
        const float x3 = x * x2;
        const float q = ppc::fmadds(x2, kAtanB, kAtanC);
        const float num = ppc::fmadds(x3, kAtanA, x);
        const float den = ppc::fmadds(x2, q, kOne);
        x = num / den;
    }
    if ((flags & 2) != 0) x = -x;
    const float result = x + OctantConstant(flags & 7);
    return (flags & 8) != 0 ? -result : result;
}

}  // namespace

// 0x00780c90 Math_Acosf
float Acosf(float x) {
    uint32_t sign = 2;
    if (x < 0.0f) {
        x = -x;
        sign = 4;
    }
    if (x <= kInvSqrtHalf) {
        const float sum = x + kOne;
        const float diff = kOne - x;
        const float root = std::sqrt(diff * sum);  // fsqrts
        return FAtan(x / root, sign & 6);
    }
    if (x <= kOne) {
        const float diff = kOne - x;
        const float root = std::sqrt(ppc::fmadds(x, diff, diff));  // fsqrts
        return FAtan(root / x, (sign ^ 2) & 6);
    }
    return FromBits(0x7fc00000);  // 0xc4adc0
}

// 0x00780d70 Math_Asinf: the same reduction with the other octant flags (library TOC -0x2a38..-0x2a3c at
// 0xc22f30..0xc22f3c: 0, sqrt(1/2), 1, the NaN pointer 0xc4adc0). A negative argument sets flag 8 (the result
// negated); up to sqrt(1/2) _FAtan(x / sqrtf((1 - x) * (x + 1)), flags), up to 1 _FAtan(sqrtf(x * (1 - x) +
// (1 - x)) / x, (flags ^ 2) & 0xa) (Math_Sqrtf_2 0x007814c0 = fsqrts); NaN above 1 and for NaN.
float Asinf(float x) {
    uint32_t sign = 0;
    if (x < 0.0f) {
        x = -x;
        sign = 8;
    }
    if (x <= kInvSqrtHalf) {
        const float sum = x + kOne;
        const float diff = kOne - x;
        const float root = std::sqrt(diff * sum);  // fsqrts
        return FAtan(x / root, sign & 0xffff);
    }
    if (x <= kOne) {
        const float diff = kOne - x;
        const float root = std::sqrt(ppc::fmadds(x, diff, diff));  // fsqrts
        return FAtan(root / x, (sign ^ 2) & 0xa);
    }
    return FromBits(0x7fc00000);  // 0xc4adc0
}

}  // namespace crt
