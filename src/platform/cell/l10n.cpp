#include "platform/cell/l10n.h"

int32_t UCS2stoUTF8s(const uint16_t* src, size_t* src_len, uint8_t* dst, size_t* dst_len) {
    if (!src || !src_len || !dst_len) return SRCIllegal;
    const size_t inCount = *src_len;
    const size_t capacity = *dst_len;
    size_t out = 0;
    size_t i = 0;
    int32_t result = ConversionOK;
    for (; i < inCount; ++i) {
        const uint32_t c = src[i];
        if (c >= 0xD800 && c <= 0xDFFF) {  // surrogates are not valid UCS-2
            result = SRCIllegal;
            break;
        }
        uint8_t buf[3];
        size_t n;
        if (c < 0x80) {
            buf[0] = static_cast<uint8_t>(c);
            n = 1;
        } else if (c < 0x800) {
            buf[0] = static_cast<uint8_t>(0xC0 | (c >> 6));
            buf[1] = static_cast<uint8_t>(0x80 | (c & 0x3F));
            n = 2;
        } else {
            buf[0] = static_cast<uint8_t>(0xE0 | (c >> 12));
            buf[1] = static_cast<uint8_t>(0x80 | ((c >> 6) & 0x3F));
            buf[2] = static_cast<uint8_t>(0x80 | (c & 0x3F));
            n = 3;
        }
        if (dst) {
            if (out + n > capacity) {
                result = DSTExhausted;
                break;
            }
            for (size_t k = 0; k < n; ++k) dst[out + k] = buf[k];
        }
        out += n;
    }
    *src_len = i;
    *dst_len = out;
    return result;
}
