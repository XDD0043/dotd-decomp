// xpowfast.cpp - see xpowfast.h. Constants from the library TOC (0xc25974 - 0x2a04 .. - 0x29c4).
#include "crt/xpowfast.h"

#include <cstdint>
#include <cstring>

#include "crt/ppc_ops.h"

namespace crt {

namespace {

float FromBits(uint32_t bits) {
    float f;
    std::memcpy(&f, &bits, 4);
    return f;
}
uint32_t ToBits(float f) {
    uint32_t bits;
    std::memcpy(&bits, &f, 4);
    return bits;
}

}  // namespace

// 0x007814c8 Math_Log2Fast_maybe
float Log2Fast(float x) {
    const uint32_t bits = ToBits(x);
    const int32_t exponent = static_cast<int32_t>((bits >> 23) & 0xffu) - 127;
    const float mantissa = FromBits(bits - (static_cast<uint32_t>(exponent) << 23 & 0xff800000u));
    const float e = static_cast<float>(static_cast<double>(exponent));  // extsw, fcfid, frsp
    const float m = mantissa - 1.0f;                                     // TOC2 -0x2a04
    float a = ppc::fmadds(m, FromBits(0xbc188b0du), FromBits(0x3d5541c9u));  // -0x29f4, -0x29f0
    float m2 = m * m;
    float b = ppc::fmsubs(m, FromBits(0x3ef5162du), FromBits(0x3f389e54u));  // -0x2a00, -0x29fc
    a = ppc::fmsubs(m, a, FromBits(0x3e0cd4fdu));                            // -0x29ec
    m2 = m2 * m2;
    b = ppc::fmadds(m, b, FromBits(0x3fb8aa10u));                            // -0x29f8 (1/ln 2)
    a = ppc::fmadds(m, a, FromBits(0x3e77adbdu));                            // -0x29e8
    a = ppc::fmsubs(m, a, FromBits(0x3eb1d206u));                            // -0x29e4
    m2 = m2 * a;
    return ppc::fmadds(m, b, m2) + e;
}

// 0x00781558 Math_Exp2Fast_maybe
float Exp2Fast(float x) {
    // 0x3f7fffff unless x is negative (srawi of the sign, andc).
    const uint32_t sign = static_cast<uint32_t>(static_cast<int32_t>(ToBits(x)) >> 31);
    const float bias = FromBits(0x3f7fffffu & ~sign);
    const int32_t k = ppc::fctiwz(x + bias);
    const uint32_t scaleBits = static_cast<uint32_t>(k + 127) << 23 & 0xff800000u;
    float f = static_cast<float>(static_cast<double>(k)) - x;
    f = f * FromBits(0x3f317218u);                                            // -0x29e0 ln 2
    float a = ppc::fmadds(f, FromBits(0xbe2aaa4fu), FromBits(0x3efffffdu));   // -0x29dc, -0x29d8
    float b = ppc::fmadds(f, FromBits(0xb9142e40u), FromBits(0x3aae4f6fu));   // -0x29d0, -0x29cc
    float f2 = f * f;
    a = ppc::fmsubs(f, a, 1.0f);                                              // -0x29d4
    b = ppc::fmsubs(f, b, FromBits(0x3c08026du));                             // -0x29c8
    f2 = f2 * f2;
    a = ppc::fmadds(f, a, 1.0f);
    b = ppc::fmadds(f, b, FromBits(0x3d2aa0e5u));                             // -0x29c4
    const float p = ppc::fmadds(f2, b, a);
    const uint32_t pBits = ToBits(p);
    uint32_t result = ToBits(p * FromBits(scaleBits));
    const uint32_t exponent = ((pBits >> 23) & 0x1ffu) + static_cast<uint32_t>(k);
    if (exponent > 0xffu) result = static_cast<uint32_t>(static_cast<int32_t>(~exponent) >> 31) & 0x7f800000u;
    return FromBits(result);
}

// 0x00780c50 Math_PowFast_maybe
float PowFast(float x, float y) { return Exp2Fast(Log2Fast(x) * y); }

}  // namespace crt
