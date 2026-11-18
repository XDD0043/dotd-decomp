// Uuid.cpp - reconstructed original translation unit 0x245bb8-0x246350 (GAME_TOC1, main_toc1), 18 functions, 11 live.
// Primary owner: Uuid (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x245bb8  Uuid_InitFromTimerMicroseconds_maybe  [dead]
//   [x] 0x245c98  Uuid_Write
//   [x] 0x245e08  Uuid_Read
//   [ ] 0x245ea8  Uuid_SkipInStream_maybe  [dead]
//   [x] 0x245ef8  Uuid_Equals
//   [ ] 0x245f60  Uuid_NotEquals  [dead]
//   [ ] 0x245fc0  Uuid_LessThan  [dead]
//   [ ] 0x246030  Uuid_LessOrEqual  [dead]
//   [ ] 0x2460a8  Uuid_GreaterThan  [dead]
//   [ ] 0x246120  Uuid_GreaterOrEqual  [dead]
//   [x] 0x246190  Uuid_Copy
//   [x] 0x2461c0  Uuid_Clear
//   [x] 0x2461d8  Uuid_IsNull
//   [x] 0x246220  StaticInitAndDestruction_246220  (g_nullUuid (zero-initialised))
//   [ ] 0x246258  _GLOBAL__I_246258
//   [ ] 0x246268  _GLOBAL__D_246268
//   [x] 0x246278  Uuid_ToString  (no caller in the original either)
//   [x] 0x2462d0  Uuid_ParseHexString_maybe  (its caller HandleParametersInternal (the command line) is not ported)
#include <cstdint>
#include <cstdio>
#include <cstring>

// 0x002461c0 Uuid_Clear: four zero words (+0x0c first).
void Uuid_Clear(uint8_t* uuid) { std::memset(uuid, 0, 16); }

#include "k2000/io/IKFile.h"

// 0x00245e08 Uuid_Read
uint32_t Uuid_Read(uint32_t* uuid, IKFile* stream) {
    uint8_t b[16];
    const uint32_t got = stream->Read(b, 16);
    for (int i = 0; i < 4; ++i) {
        uuid[i] = static_cast<uint32_t>(b[i * 4]) | (static_cast<uint32_t>(b[i * 4 + 1]) << 8) |
                  (static_cast<uint32_t>(b[i * 4 + 2]) << 16) | (static_cast<uint32_t>(b[i * 4 + 3]) << 24);
    }
    return got;
}

// 0x00245c98 Uuid_Write (C2.8 save-menu): the four words little-endian (Uuid_Read's mirror); the sum of the writes.
uint32_t Uuid_Write(const uint32_t* uuid, IKFile* stream) {
    const uint32_t a = WriteU32LE(stream, uuid[0]);
    const uint32_t b = WriteU32LE(stream, uuid[1]);
    const uint32_t c = WriteU32LE(stream, uuid[2]);
    const uint32_t d = WriteU32LE(stream, uuid[3]);
    return d + a + b + c;
}

// 0x00245ef8 Uuid_Equals
bool Uuid_Equals(const uint32_t* a, const uint32_t* b) {
    return a[0] == b[0] && a[1] == b[1] && a[2] == b[2] && a[3] == b[3];
}

// 0x00246190 Uuid_Copy
void Uuid_Copy(uint32_t* dst, const uint32_t* src) {
    const uint32_t w1 = src[1], w2 = src[2], w3 = src[3];
    dst[0] = src[0];
    dst[3] = w3;
    dst[1] = w1;
    dst[2] = w2;
}

// 0x00ceaac8 the null UUID (StaticInitAndDestruction_246220 clears its four words at startup) and 0x00ceaad8 the buffer
// Uuid_ToString formats into (its size is not known: 0x80 here).
uint32_t g_nullUuid[4] = {0, 0, 0, 0};
namespace {
char g_uuidText[0x80];
}  // namespace

// 0x00246278 Uuid_ToString (FormatString 0x98d3b0, sprintf). No caller.
const char* Uuid_ToString(const uint32_t* uuid) {
    std::snprintf(g_uuidText, sizeof(g_uuidText), "0x%08x, 0x%08x, 0x%08x, 0x%08x", uuid[0], uuid[1], uuid[2], uuid[3]);
    return g_uuidText;
}

// 0x002462d0 Uuid_ParseHexString_maybe (sscanf through its TocBridge): four words, or the null UUID and 0 (caller:
// HandleParametersInternal 0x253320, the command line; not ported).
bool Uuid_ParseHexString(uint32_t* uuid, const char* text) {
    const int count = std::sscanf(text, "0x%x, 0x%x, 0x%x, 0x%x", &uuid[0], &uuid[1], &uuid[2], &uuid[3]);
    if (count != 4) {
        uuid[3] = 0;
        uuid[0] = 0;
        uuid[1] = 0;
        uuid[2] = 0;
    }
    return count == 4;
}

// 0x002461d8 Uuid_IsNull
bool Uuid_IsNull(const uint32_t* uuid) { return uuid[0] == 0 && uuid[1] == 0 && uuid[2] == 0 && uuid[3] == 0; }
