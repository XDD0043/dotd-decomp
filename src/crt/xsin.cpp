// xsin.cpp - Dinkumware _Sin as the PS3 build computes it. See xsin.h.
//
// Constants are the TOC doubles (TOC2 slots 0xc22e40..0xc22ed8, _Rteps at 0xc4ae60, _Nan at 0xc4ae40),
// written as hex floats. The reduction constant c1 is loaded with lfs (a float widened to double).
#include "crt/xsin.h"

#include <cmath>
#include <cstring>

#include "crt/ppc_ops.h"

namespace crt {

namespace {

constexpr double kHugeRad = 0x1.4570fdp+31;            // 2730000000.0: beyond it, fmod(x, 2pi) first
constexpr double kTwoPi = 0x1.921fb54442d18p+2;
constexpr double kTwoByPi = 0x1.45f306dc9c883p-1;
constexpr float kC1 = -0x1.921fb4p+0f;                  // lfs: -pi/2 high part (0xbfc90fda)
constexpr double kC2 = -0x1.4442d18469899p-24;          // -pi/2 low part
constexpr double kRteps = 0x1p-27;                      // _Rteps (0xc4ae60)

// cos polynomial (qoff odd)
constexpr double kC[6] = {0x1.1ba39100a2609p-29, 0x1.27df9c661a83bp-22, 0x1.a019f9030ac63p-16,
                          0x1.6c16c1651fbf6p-10, 0x1.55555555502b1p-5, 0x1.fffffffffffaep-2};
// sin polynomial (qoff even)
constexpr double kS[6] = {0x1.5d810c32f8fb0p-33, 0x1.ae5e1a1730c8fp-26, 0x1.71de34fe4ad4dp-19,
                          0x1.a01a019b5e33ep-13, 0x1.111111110f0fap-7, 0x1.5555555555542p-3};

// 0x0077fbe8 _Dtest: 0 zero, 1 infinity, 2 NaN, -1 any other finite value (denormals included).
int16_t Dtest(double x) {
    uint64_t bits;
    std::memcpy(&bits, &x, sizeof bits);
    const uint64_t exponent = (bits >> 52) & 0x7ff;
    const uint64_t mantissa = bits & 0xfffffffffffffull;
    if (exponent == 0x7ff) return mantissa != 0 ? 2 : 1;
    if (exponent == 0 && mantissa == 0) return 0;
    return -1;
}

double Nan() {
    const uint64_t bits = 0x7ff8000000000000ull;  // _Nan (0xc4ae40)
    double d;
    std::memcpy(&d, &bits, sizeof d);
    return d;
}

}  // namespace

// 0x00780880 _Sin_maybe
double Sin(double x, uint32_t qoff) {
    switch (Dtest(x)) {
        case 2:  // NaN
            return x;
        case 1:  // infinity: _Feraise(FE_INVALID) (0x780048), then _Nan
            return Nan();
        case 0:  // zero
            return qoff != 0 ? 1.0 : x;
        default:
            break;
    }
    if (x < -kHugeRad || kHugeRad < x) {
        // 0x00781030 fmod_maybe. fmod is exact (its result is always representable), so any correct
        // implementation gives the PS3's bits; this branch needs |x| > 2.73e9 rad.
        x = std::fmod(x, kTwoPi);
    }
    const double g = x * kTwoByPi;  // fmul
    int32_t quad;
    if (g > 0.0) {
        quad = ppc::fctiwz(g + 0.5);  // fadd with the lfs 0.5f
    } else {
        quad = ppc::fctiwz(g - 0.5);
    }
    qoff += static_cast<uint32_t>(quad) & 3u;
    const double gq = static_cast<double>(static_cast<int64_t>(quad));  // extsw + fcfid
    x = ppc::fmadd(gq, static_cast<double>(kC1), x);
    x = ppc::fmadd(gq, kC2, x);
    if (-kRteps < x && x < kRteps) {
        if ((qoff & 1u) != 0) x = 1.0;
    } else {
        const double w = x * x;
        if ((qoff & 1u) != 0) {
            double p = ppc::fmsub(w, kC[0], kC[1]);
            p = ppc::fmadd(w, p, kC[2]);
            p = ppc::fmsub(w, p, kC[3]);
            p = ppc::fmadd(w, p, kC[4]);
            p = ppc::fmsub(w, p, kC[5]);
            x = ppc::fmadd(w, p, 1.0);
        } else {
            const double xw = x * w;
            double p = ppc::fmsub(w, kS[0], kS[1]);
            p = ppc::fmadd(w, p, kS[2]);
            p = ppc::fmsub(w, p, kS[3]);
            p = ppc::fmadd(w, p, kS[4]);
            p = ppc::fmsub(w, p, kS[5]);
            x = ppc::fmadd(xw, p, x);
        }
    }
    if ((qoff & 2u) != 0) x = -x;
    return x;
}

}  // namespace crt
