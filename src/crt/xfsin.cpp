// xfsin.cpp - the library's float _FSin and sqrtf. See xfsin.h.
//
// Constants are library TOC slots (0xc25974 -0x2c1c..-0x2bd4 for _FSin, -0x2de4..-0x2dd4 for sqrtf), compared by
// their bits.
#include "crt/xfsin.h"

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

uint32_t ToBits(float value) {
    uint32_t bits;
    std::memcpy(&bits, &value, 4);
    return bits;
}

const float kNaN = FromBits(0x7fc00000);          // *0xc4adc0
const float kTwoPi = FromBits(0x40c90fdb);        // -0x2c04
const float kTwoOverPi = FromBits(0x3f22f983);    // -0x2c00
const float kHalf = FromBits(0x3f000000);         // -0x2bfc
const float kPiHalfHi = FromBits(0xbfc90fda);     // -0x2bf8 (negated)
const float kPiHalfLo = FromBits(0xb3a22169);     // -0x2bf4 (negated)
const float kRteps = FromBits(0x39800000);        // *0xc4ade0 (_FRteps, 2^-12)
const float kOne = FromBits(0x3f800000);          // -0x2c1c
const float kCos0 = FromBits(0xbab24993);         // -0x2bec
const float kCos1 = FromBits(0x3d2aa036);         // -0x2be8
const float kCos2 = FromBits(0x3effffdf);         // -0x2be4
const float kSin0 = FromBits(0xb94c8c6e);         // -0x2be0
const float kSin1 = FromBits(0x3c088342);         // -0x2bdc
const float kSin2 = FromBits(0x3e2aaaa1);         // -0x2bd8
constexpr double kReduceLimit = 40.7;             // -0x2c14 / -0x2c0c (doubles)

const float kSqrtA = FromBits(0xbdcc5437);        // -0x2de0
const float kSqrtB = FromBits(0x3f35d97f);        // -0x2ddc
const float kSqrtC = FromBits(0x3ec5f06f);        // -0x2dd8
const float kQuarter = FromBits(0x3e800000);      // -0x2dd4

}  // namespace

// 0x00780470 _FSin_maybe
float FSinf(float x, uint32_t qoff) {
    const uint32_t bits = ToBits(x);
    if ((bits & 0x7f800000u) == 0x7f800000u) {
        if ((bits & 0x007fffffu) != 0) return x;  // _FDtest 2: NaN
        return kNaN;                              // _FDtest 1: infinity (_Feraise 0x20000000)
    }
    if ((bits & 0x7fffffffu) == 0) return qoff != 0 ? kOne : x;  // _FDtest 0
    if (static_cast<double>(x) < -kReduceLimit || static_cast<double>(x) > kReduceLimit) {
        x = std::fmod(x, kTwoPi);  // fmodf_maybe 0x781278 (exact)
    }
    const float scaled = x * kTwoOverPi;
    const int32_t q = scaled <= 0.0f ? ppc::fctiwz(scaled - kHalf) : ppc::fctiwz(scaled + kHalf);
    const float qf = static_cast<float>(static_cast<double>(q));
    const uint32_t k = (static_cast<uint32_t>(q) & 3u) + qoff;
    float r = ppc::fmadds(qf, kPiHalfHi, x);
    r = ppc::fmadds(qf, kPiHalfLo, r);
    if (!(-kRteps < r) || !(r < kRteps)) {  // bge, bge
        const float w = r * r;
        if ((k & 1u) != 0) {
            float t = ppc::fmadds(w, kCos0, kCos1);
            t = ppc::fmsubs(w, t, kCos2);
            r = ppc::fmadds(w, t, kOne);
        } else {
            const float rw = r * w;
            float t = ppc::fmadds(w, kSin0, kSin1);
            t = ppc::fmsubs(w, t, kSin2);
            r = ppc::fmadds(rw, t, r);
        }
    } else if ((k & 1u) != 0) {
        r = kOne;
    }
    return (k & 2u) != 0 ? -r : r;
}

// 0x0077f6b8 sqrtf_maybe
float Sqrtf(float x) {
    const uint32_t bits = ToBits(x);
    if ((bits & 0x7f800000u) == 0x7f800000u) {
        if ((bits & 0x007fffffu) != 0) return x;   // NaN
        if ((bits & 0x80000000u) == 0) return x;   // +infinity
        return kNaN;                               // -infinity (_Feraise 0x20000000)
    }
    if ((bits & 0x7fffffffu) == 0) return x;       // zero
    if ((bits & 0x80000000u) != 0) return kNaN;    // negative (_Feraise 0x20000000)
    int exponent = 0;
    float m = std::frexp(x, &exponent);            // _FDunscale_maybe 0x960a78
    int16_t e = static_cast<int16_t>(exponent);
    if ((e & 1) != 0) {
        m = m + m;
        e = static_cast<int16_t>(e - 1);
    }
    float y = ppc::fmadds(m, kSqrtA, kSqrtB);
    y = ppc::fmadds(m, y, kSqrtC);
    y = y + m / y;
    y = ppc::fmadds(y, kQuarter, m / y);
    return std::ldexp(y, e / 2);                   // _FDscale_maybe 0x960898 (srawi / addze: toward zero)
}

}  // namespace crt
