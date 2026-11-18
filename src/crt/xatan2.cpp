// xatan2.cpp - the double atan2 and the float logarithm of the game's Dinkumware libm. See xatan2.h. (atan2f is in
// xatanf.cpp, next to the _FAtan it shares.)
#include "crt/xatan2.h"

#include <cstring>

#include "crt/ppc_ops.h"

namespace crt {

namespace {

double FromBits64(uint64_t bits) {
    double value;
    std::memcpy(&value, &bits, 8);
    return value;
}
float FromBits32(uint32_t bits) {
    float value;
    std::memcpy(&value, &bits, 4);
    return value;
}

// 0x0077fbe8 _Dtest: the class of a double from its four halves: 2 NaN, 1 infinity, 0 zero, -1 finite.
int32_t Dtest(double x) {
    uint64_t bits;
    std::memcpy(&bits, &x, 8);
    const uint32_t h0 = static_cast<uint32_t>(bits >> 48) & 0xffffu;
    const uint32_t h1 = static_cast<uint32_t>(bits >> 32) & 0xffffu;
    const uint32_t h2 = static_cast<uint32_t>(bits >> 16) & 0xffffu;
    const uint32_t h3 = static_cast<uint32_t>(bits) & 0xffffu;
    if ((h0 & 0x7ff0u) == 0x7ff0u) {
        if ((h0 & 0xfu) != 0 || h1 != 0 || h2 != 0 || h3 != 0) return 2;
        return 1;
    }
    if ((h0 & 0x7fffu) != 0 || h1 != 0 || h2 != 0 || h3 != 0) return -1;
    return 0;
}
bool DSignBit(double x) {
    uint64_t bits;
    std::memcpy(&bits, &x, 8);
    return (bits >> 63) != 0;
}

// 0x0077f990 _Atan_maybe (library TOC -0x2d84..-0x2d3c; the threshold 0x00c4ae60 = 2^-27; the octants 0x00a727e0).
double DAtan(double x, uint32_t mode) {
    static const uint64_t kOctantBits[8] = {0x0000000000000000ull, 0x3fe0c152382d7366ull, 0x3ff921fb54442d18ull,
                                            0x3ff0c152382d7366ull, 0x3ff921fb54442d18ull, 0x4000c152382d7366ull,
                                            0x400921fb54442d18ull, 0x4004f1a6c638d03full};
    const double tan15 = FromBits64(0x3fd126145e9ecd56ull);
    const double sqrt3 = FromBits64(0x3ffbb67ae8584caaull);
    const double one = 1.0;  // lfs -0x2d74
    if (x > tan15) {         // ble: a NaN is not reduced
        mode |= 1;
        const double denominator = x + sqrt3;
        const double numerator = ppc::fmsub(x, sqrt3, one);
        x = numerator / denominator;
    }
    const double eps = FromBits64(0x3e40000000000000ull);
    if (-eps > x || x > eps) {
        const double w = x * x;
        double p = ppc::fmadd(w, FromBits64(0x3f74c0c78f0239deull), FromBits64(0x3fc80c008312ab8aull));
        double q = ppc::fmadd(w, FromBits64(0x3fb0574b13575d84ull), FromBits64(0x3fe45eed194c93b2ull));
        double cube = x * w;
        p = ppc::fmadd(w, p, FromBits64(0x3ff0d8b608e5d724ull));
        q = ppc::fmadd(w, q, FromBits64(0x3ff84002b902debeull));
        p = ppc::fmadd(w, p, FromBits64(0x3ffd95580e58340full));
        cube = ppc::fmadd(cube, q, x);
        const double denominator = ppc::fmadd(w, p, one);
        x = cube / denominator;
    }
    if ((mode & 2) != 0) x = -x;
    x = x + FromBits64(kOctantBits[mode & 7]);
    if ((mode & 8) != 0) x = -x;
    return x;
}

// 0x0096ae60 _FDnorm_maybe: a denormal's fraction shifted up to the hidden bit (the halves of the float, big-endian
// order: hi = sign, exponent, top 7 fraction bits); the exponent it implies (1 for a zero).
int16_t FDnorm(uint16_t* hi, uint16_t* lo) {
    const uint16_t sign = *hi;
    int16_t xchar = 1;
    *hi = static_cast<uint16_t>(*hi & 0x7fu);
    if (*hi != 0 || *lo != 0) {
        if (*hi == 0) {
            *hi = *lo;
            *lo = 0;
            xchar = static_cast<int16_t>(xchar - 16);
        }
        for (; *hi < 0x80u; --xchar) {
            *hi = static_cast<uint16_t>((*hi << 1) | (*lo >> 15));
            *lo = static_cast<uint16_t>(*lo << 1);
        }
        for (; 0x100u <= *hi; ++xchar) {
            *lo = static_cast<uint16_t>((*lo >> 1) | (*hi << 15));
            *hi = static_cast<uint16_t>(*hi >> 1);
        }
        *hi = static_cast<uint16_t>(*hi & 0x7fu);
    }
    *hi = static_cast<uint16_t>(*hi | (sign & 0x8000u));
    return xchar;
}

// 0x00960a78 _FDunscale_maybe: *x brought into [1/2, 1) and *exponent the power of 2 taken out; returns 2 NaN,
// 1 infinity, 0 zero (exponent 0), -1 finite.
int32_t FDunscale(int16_t* exponent, float* x) {
    uint32_t bits;
    std::memcpy(&bits, x, 4);
    uint16_t hi = static_cast<uint16_t>(bits >> 16);
    uint16_t lo = static_cast<uint16_t>(bits);
    int16_t xchar = static_cast<int16_t>((hi >> 7) & 0xffu);
    if (xchar == 0xff) {
        *exponent = 0;
        return ((hi & 0x7fu) != 0 || lo != 0) ? 2 : 1;
    }
    if (0 < xchar || (xchar = FDnorm(&hi, &lo)) <= 0) {
        hi = static_cast<uint16_t>((hi & 0x807fu) | 0x3f00u);
        *exponent = static_cast<int16_t>(xchar - 0x7e);
        bits = (static_cast<uint32_t>(hi) << 16) | lo;
        std::memcpy(x, &bits, 4);
        return -1;
    }
    bits = (static_cast<uint32_t>(hi) << 16) | lo;
    std::memcpy(x, &bits, 4);
    *exponent = 0;
    return 0;
}

bool FSign(float x) {
    uint32_t bits;
    std::memcpy(&bits, &x, 4);
    return (bits >> 31) != 0;
}

}  // namespace

// 0x0077e868 atan2 (library TOC -0x2e8c = 0.0 (double), -0x2e84 = 1.0 (float)).
double Atan2(double y, double x) {
    const int32_t xClass = Dtest(x);  // the first _Dtest is of x
    const int32_t yClass = Dtest(y);
    if (xClass <= 0 && yClass <= 0) {
        uint32_t mode = 0;
        if (DSignBit(y)) {
            y = -y;
            mode = 8;
        }
        if (DSignBit(x)) {
            x = -x;
            mode ^= 6;
        }
        double ratio;
        if (!(x >= y)) {
            mode ^= 2;
            ratio = x / y;
        } else {
            ratio = xClass == 0 ? 0.0 : y / x;
        }
        return DAtan(ratio, mode);
    }
    if (yClass == 2) return y;
    if (xClass == 2) return x;
    const double ratio = xClass == yClass ? 1.0 : 0.0;
    uint32_t mode = DSignBit(y) ? 8u : 0u;
    if (DSignBit(x)) mode |= 6;
    if (yClass == 1) mode ^= 2;
    return DAtan(ratio, mode);
}

// 0x00780270 _FLog_maybe (library TOC -0x2c5c..-0x2c24; +infinity 0x00c4adb0, the NaN 0x00c4adc0).
float FLog(float x, int32_t base) {
    const float infinity = FromBits32(0x7f800000u);
    const float nan = FromBits32(0x7fc00000u);
    int16_t exponent = 0;
    switch (FDunscale(&exponent, &x)) {
    case 2:
        return x;
    case 1:
        if (!FSign(x)) return x;
        return nan;  // _Feraise(0x2000000): invalid
    case 0:
        return -infinity;  // _Feraise(0x4000000): division by zero
    default:
        break;
    }
    if (FSign(x)) return nan;  // _Feraise(0x2000000)
    float z = x;
    if (!(z >= FromBits32(0x3f3504f3u))) {  // bge sqrt(1/2)
        z = z + z;
        exponent = static_cast<int16_t>(exponent - 1);
    }
    const float one = 1.0f;
    const float zm1 = z - one;
    const float zp1 = z + one;
    const float e = static_cast<float>(exponent);
    const float t = zm1 / zp1;
    const float w = t * t;
    float p = ppc::fmadds(w, FromBits32(0x3e990215u), FromBits32(0x3eccae11u));
    p = ppc::fmadds(w, p, FromBits32(0x3f2aaac0u));
    const float r = t * (zm1 - w * p);
    if (base == 0) {
        const float c = ppc::fmadds(e, FromBits32(0xb3fbe8e8u), r);
        return ppc::fmadds(e, FromBits32(0x3f317216u), zm1 - c);
    }
    if (base > 0) {
        const float lo = e * FromBits32(0xb3a13ef4u);
        const float a = ppc::fmadds(r, FromBits32(0x3ede5bd9u), lo);
        const float b = ppc::fmsubs(zm1, FromBits32(0x32a93728u), a);
        const float c = ppc::fmadds(zm1, FromBits32(0x3ede5bd8u), b);
        return ppc::fmadds(e, FromBits32(0x3e9a2098u), c);
    }
    const float a = r * FromBits32(0xbfb8aa3bu);
    const float b = ppc::fmadds(zm1, FromBits32(0x32a57060u), a);
    const float c = ppc::fmadds(zm1, FromBits32(0x3fb8aa3bu), b);
    return e + c;
}

}  // namespace crt
