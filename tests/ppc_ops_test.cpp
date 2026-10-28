// Unit tests for src/crt/ppc_ops.h. Expected values follow the PowerPC architecture and RPCS3's
// interpreter for the cases the architecture leaves undefined.
#include "crt/ppc_ops.h"

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <limits>

static int g_failures = 0;
#define CHECK(cond)                                                              \
    do {                                                                         \
        if (!(cond)) {                                                           \
            std::printf("FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond);         \
            ++g_failures;                                                        \
        }                                                                        \
    } while (0)

static uint32_t bits(float f) { uint32_t u; std::memcpy(&u, &f, 4); return u; }

int main() {
    // fused vs. unfused: a*b+c where the exact product needs more than 24 bits
    {
        volatile float a = 1.0f + std::ldexp(1.0f, -23);   // 1 + 2^-23
        volatile float b = 1.0f - std::ldexp(1.0f, -23);   // 1 - 2^-23
        volatile float c = -1.0f;
        // exact a*b = 1 - 2^-46; a*b rounded to float = 1.0 -> unfused result 0, fused = -2^-46
        const float unfused = static_cast<float>(a * b) + c;
        const float fused = ppc::fmadds(a, b, c);
        CHECK(unfused == 0.0f);
        CHECK(fused == -std::ldexp(1.0f, -46));
        CHECK(ppc::fmsubs(a, b, 1.0f) == -std::ldexp(1.0f, -46));
        CHECK(ppc::fnmadds(a, b, c) == std::ldexp(1.0f, -46));
        CHECK(ppc::fnmsubs(a, b, 1.0f) == std::ldexp(1.0f, -46));
    }
    // fctiwz: truncation, saturation, NaN
    CHECK(ppc::fctiwz(1.9) == 1);
    CHECK(ppc::fctiwz(-1.9) == -1);
    CHECK(ppc::fctiwz(3e9) == std::numeric_limits<int32_t>::max());
    CHECK(ppc::fctiwz(-3e9) == std::numeric_limits<int32_t>::min());
    CHECK(ppc::fctiwz(2147483647.9) == 2147483647);
    CHECK(ppc::fctiwz(-2147483648.9) == std::numeric_limits<int32_t>::min());
    CHECK(ppc::fctiwz(std::nan("")) == std::numeric_limits<int32_t>::min());
    CHECK(ppc::fctiwz(INFINITY) == std::numeric_limits<int32_t>::max());
    CHECK(ppc::fctidz(1e19) == std::numeric_limits<int64_t>::max());
    // fctiw: round half to even
    CHECK(ppc::fctiw(2.5) == 2);
    CHECK(ppc::fctiw(3.5) == 4);
    CHECK(ppc::fctiw(-2.5) == -2);
    // division edge cases
    CHECK(ppc::divw(7, 0) == 0);
    CHECK(ppc::divw(std::numeric_limits<int32_t>::min(), -1) == 0);
    CHECK(ppc::divw(-7, 2) == -3);
    CHECK(ppc::divwu(7u, 0u) == 0u);
    CHECK(ppc::divwu(0xffffffffu, 2u) == 0x7fffffffu);
    // shifts by 32..63 shift everything out; the amount uses 6 bits
    CHECK(ppc::slw(1u, 31) == 0x80000000u);
    CHECK(ppc::slw(1u, 32) == 0u);
    CHECK(ppc::slw(1u, 63) == 0u);
    CHECK(ppc::slw(1u, 64) == 1u);  // 64 & 63 == 0
    CHECK(ppc::srw(0x80000000u, 40) == 0u);
    CHECK(ppc::sraw(-8, 2) == -2);
    CHECK(ppc::sraw(-8, 40) == -1);
    CHECK(ppc::sraw(8, 40) == 0);
    // rotate-and-mask (IBM bit order)
    CHECK(ppc::mask32(0, 31) == 0xffffffffu);
    CHECK(ppc::mask32(24, 31) == 0x000000ffu);
    CHECK(ppc::mask32(30, 1) == 0xc0000003u);  // wrap-around mask
    CHECK(ppc::rlwinm(0x12345678u, 8, 24, 31) == 0x12u);  // extract the top byte (srwi 24)
    CHECK(ppc::rlwinm(0x12345678u, 0, 16, 31) == 0x5678u);  // clrlwi 16
    CHECK(ppc::rlwimi(0xffff0000u, 0x1234u, 0, 16, 31) == 0xffff1234u);
    CHECK(ppc::cntlzw(0) == 32);
    CHECK(ppc::cntlzw(1) == 31);
    CHECK(ppc::cntlzw(0x80000000u) == 0);
    // frsp rounds to nearest even
    CHECK(bits(ppc::frsp(1.0 + std::ldexp(1.0, -24))) == bits(1.0f));
    if (g_failures == 0) std::printf("ppc_ops: all tests passed\n");
    return g_failures == 0 ? 0 : 1;
}
