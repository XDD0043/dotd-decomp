// xtanf.cpp - the game's float tangent. See xtanf.h.
//
// tanf 0x00780a90 (library TOC 0xc25974): outside +-40.7 (doubles at 0xc22ee0 / 0xc22ee8, compared in double
// precision) the argument is first reduced by _Fmodf_RangeReduce_maybe 0x00780bf0 with 2 pi; then
// n = fctiwz(x * 2/pi +- 0.5), r = x - n * pi/2 in two fused steps (Cody-Waite, 0xc22efc / 0xc22f00), and the
// rational approximation (0xc22f0c..0xc22f18) gives tan r, or -1 / tan r for an odd n. |r| below _FRteps (2^-12,
// the pointer at 0xc22f04 -> 0xc4ade0) skips the polynomial.
#include "crt/xtanf.h"

#include <cmath>
#include <cstdint>
#include <cstring>

#include "crt/ppc_ops.h"

namespace crt {

namespace {

constexpr double kReduceAbove = 40.7;          // 0xc22ee8 (0x404459999999999a); -40.7 at 0xc22ee0
constexpr float kTwoPi = 6.2831854820251465f;  // 0xc22ef0 (0x40c90fdb)
constexpr float kTwoOverPi = 0.6366197466850281f;  // 0xc22ef4 (0x3f22f983)
constexpr float kHalf = 0.5f;                      // 0xc22ef8
constexpr float kPiOver2Hi = -1.570796251296997f;  // 0xc22efc (0xbfc90fda)
constexpr float kPiOver2Lo = -7.549790126404332e-08f;  // 0xc22f00 (0xb3a22169)
constexpr float kRteps = 0.000244140625f;      // *0xc22f04 = 0xc4ade0 (0x39800000)
constexpr float kMinusOne = -1.0f;             // 0xc22f08
constexpr float kP0 = 0.009709936566650867f;   // 0xc22f0c (0x3c1f166d)
constexpr float kP1 = 0.4291161894798279f;     // 0xc22f10 (0x3edbb51e)
constexpr float kOne = 1.0f;                   // 0xc22f14
constexpr float kQ0 = -0.09578230232000351f;   // 0xc22f18 (0xbdc42983)

// The truncation toward zero through the float's bits (rldicl / subfic / sraw / nor / and): shift = 127 - exponent;
// below 1 (shift >= 1) every bit is cleared (+0, the sign too); otherwise the fraction bits 0x7fffff >> -shift are
// cleared (none from shift <= -31 on).
float TruncateByExponentMask(float x) {
    uint32_t bits;
    std::memcpy(&bits, &x, 4);
    const int32_t shift = 127 - static_cast<int32_t>((bits >> 23) & 0xffu);
    const int32_t below = ~ppc::sraw(shift - 1, 31);
    int32_t fraction = 0;
    if (shift > -31) fraction = ppc::sraw(0x007fffff, static_cast<uint32_t>(-shift));
    bits &= ~(static_cast<uint32_t>(fraction) | static_cast<uint32_t>(below));
    std::memcpy(&x, &bits, 4);
    return x;
}

}  // namespace

// 0x00780bf0 _Fmodf_RangeReduce_maybe: |y| * (q - trunc(q)) with q = x / |y| (fabs, fdivs, the truncation by the
// exponent mask, fsubs, fmuls): the remainder of x by y with x's sign.
float FmodfRangeReduce(float x, float y) {
    y = std::fabs(y);
    const float quotient = x / y;
    return y * (quotient - TruncateByExponentMask(quotient));
}

// 0x00780a90 tanf
float Tanf(float x) {
    if (static_cast<double>(x) < -kReduceAbove || static_cast<double>(x) > kReduceAbove) {
        x = FmodfRangeReduce(x, kTwoPi);
    }
    const float scaled = x * kTwoOverPi;
    const int32_t n = scaled > 0.0f ? ppc::fctiwz(scaled + kHalf) : ppc::fctiwz(scaled - kHalf);
    const float nf = ppc::frsp(static_cast<double>(static_cast<int64_t>(n)));  // extsw, fcfid, frsp
    const float partial = ppc::fmadds(nf, kPiOver2Hi, x);
    const float r = ppc::fmadds(nf, kPiOver2Lo, partial);
    if (-kRteps < r && r < kRteps) {
        if ((n & 1) == 0) return r;
        return kMinusOne / r;
    }
    const float r2 = r * r;
    float denominator = ppc::fmsubs(r2, kP0, kP1);
    const float r3 = r * r2;
    denominator = ppc::fmadds(r2, denominator, kOne);
    const float numerator = ppc::fmadds(r3, kQ0, r);
    if ((n & 1) != 0) return -denominator / numerator;
    return numerator / denominator;
}

}  // namespace crt
