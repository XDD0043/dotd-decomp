// l10n.h - cellL10n: the one conversion the game uses (save-data flows).
// Input is native-endian UCS-2 (the remake keeps strings in host order).
#pragma once
#include <cstddef>
#include <cstdint>

enum : int32_t { ConversionOK = 0, SRCIllegal = 1, DSTExhausted = 2 };

// Converts *src_len UCS-2 characters. On return *dst_len is the number of bytes written (or needed
// when dst is null) and *src_len the number of characters consumed.
int32_t UCS2stoUTF8s(const uint16_t* src, size_t* src_len, uint8_t* dst, size_t* dst_len);
