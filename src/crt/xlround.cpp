// xlround.cpp - Dinkumware lroundf as the PS3 build computes it. See xlround.h. (Moved from the local
// copy in k2000/ui/TextData.cpp when CManager2d_GetPulsingTextColor_maybe needed it too.)
#include "crt/xlround.h"

#include <cstring>

#include "crt/ppc_ops.h"

namespace crt {

// 0x0077ed68 lroundf_maybe
int32_t lroundf(float x) {
    uint32_t bits;
    std::memcpy(&bits, &x, sizeof(bits));
    if (((bits >> 23) & 0xff) == 0xff) return 0;
    if ((bits & 0x7fffffffu) == 0) return 0;
    if (x < 0.0f) {
        x = x - 0x1p-1f;
    } else {
        x = x + 0x1p-1f;
    }
    std::memcpy(&bits, &x, sizeof(bits));
    const int32_t shift = 0x96 - static_cast<int32_t>((bits >> 23) & 0xff);
    if (shift > 0) {
        if (shift > 23) {
            bits &= 0x80000000u;
        } else {
            bits &= ~((1u << shift) - 1u);
        }
    }
    std::memcpy(&x, &bits, sizeof(x));
    return ppc::fctiwz(x);
}

// 0x0077f4c0 roundf
float roundf(float x) {
    uint32_t bits;
    std::memcpy(&bits, &x, sizeof(bits));
    if (((bits >> 23) & 0xff) == 0xff) return x;
    if ((bits & 0x7fffffffu) == 0) return x;
    if (x < 0.0f) {
        x = x - 0x1p-1f;
    } else {
        x = x + 0x1p-1f;
    }
    std::memcpy(&bits, &x, sizeof(bits));
    const int32_t shift = 0x96 - static_cast<int32_t>((bits >> 23) & 0xff);
    if (shift > 0) {
        if (shift > 23) {
            bits &= 0x80000000u;
        } else {
            bits &= ~((1u << shift) - 1u);
        }
    }
    std::memcpy(&x, &bits, sizeof(x));
    return x;
}

}  // namespace crt
