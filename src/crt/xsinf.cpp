// xsinf.cpp - the game's float sine and cosine. See xsinf.h.
//
// Constants are the game TOC floats (TOC1 -0x290 4/pi, -0x28c..-0x280 the sine polynomial, -0x27c..-0x270
// the cosine polynomial); the library TOC holds the same values (the library functions use the immediates
// of the same polynomial).
#include "crt/xsinf.h"

#include <cstring>

#include "crt/ppc_ops.h"

namespace crt {

namespace {

constexpr float kFourOverPi = 0x1.45f306p+0f;       // 0x3fa2f983
constexpr float kSin0 = -0x1.2d92fap-15f;           // 0xb816c97d
constexpr float kSin1 = 0x1.465e92p-9f;             // 0x3b232f49
constexpr float kSin2 = 0x1.4abbbap-4f;             // 0x3da55ddd
constexpr float kSin3 = 0x1.921fb6p-1f;             // 0x3f490fdb
constexpr float kCos0 = -0x1.4e35dap-12f;           // 0xb9a71aed
constexpr float kCos1 = 0x1.03ae64p-6f;             // 0x3c81d732
constexpr float kCos2 = 0x1.3bd38cp-2f;             // 0x3e9de9c6
constexpr float kCos3 = 0x1.fffffep-1f;             // 0x3f7fffff

float SinPoly(float f) {
    float t = f * kSin0;
    t = ppc::fmadds(f, t, kSin1);
    t = f * t;
    t = ppc::fmsubs(f, t, kSin2);
    t = f * t;
    t = ppc::fmadds(f, t, kSin3);
    return f * t;
}

float CosPoly(float f) {
    float t = f * kCos0;
    t = ppc::fmadds(f, t, kCos1);
    t = f * t;
    t = ppc::fmsubs(f, t, kCos2);
    t = f * t;
    return ppc::fmadds(f, t, kCos3);
}

// scaled: x * 4/pi already rounded to a float (the inline form) or the double product (the library form,
// which rounds it to a float only for the fraction).
float Fraction(double scaled, float scaledAsFloat, int32_t* q) {
    *q = ppc::fctiwz(scaled);
    float f = scaledAsFloat - static_cast<float>(static_cast<double>(*q));
    if ((*q & 1) != 0) f = 1.0f - f;
    return f;
}

float CosOfNonNegative(float x, bool libraryProduct) {
    int32_t q;
    float f;
    if (libraryProduct) {
        const double product = static_cast<double>(x) * static_cast<double>(kFourOverPi);
        f = Fraction(product, static_cast<float>(product), &q);
    } else {
        const float product = x * kFourOverPi;
        f = Fraction(product, product, &q);
    }
    float r = ((q + 1) & 2) != 0 ? SinPoly(f) : CosPoly(f);
    if (((q + 2) & 7) > 3) r = -r;
    return r;
}

float SinOfNonNegative(float x, bool libraryProduct) {
    int32_t q;
    float f;
    if (libraryProduct) {
        const double product = static_cast<double>(x) * static_cast<double>(kFourOverPi);
        f = Fraction(product, static_cast<float>(product), &q);
    } else {
        const float product = x * kFourOverPi;
        f = Fraction(product, product, &q);
    }
    float r = ((q + 1) & 2) != 0 ? CosPoly(f) : SinPoly(f);
    if ((q & 7) > 3) r = -r;
    return r;
}

bool SignBit(float x) {
    int32_t bits;
    std::memcpy(&bits, &x, 4);
    return bits < 0;
}

}  // namespace

float InlineCosf(float x) { return CosOfNonNegative(x, false); }
float InlineSinf(float x) { return SinOfNonNegative(x, false); }

// 0x009a11d8 cosf: the cosine of the argument with its sign bit cleared.
float LibCosf(float x) { return CosOfNonNegative(SignBit(x) ? -x : x, true); }

// 0x009a1390 sinf: odd; a negative argument gives the negated sine of its magnitude.
float LibSinf(float x) {
    if (!SignBit(x)) return SinOfNonNegative(x, true);
    return -SinOfNonNegative(-x, true);
}

}  // namespace crt
