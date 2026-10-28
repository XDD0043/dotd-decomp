// Uuid.cpp - reconstructed original translation unit 0x245bb8-0x246350 (GAME_TOC1, main_toc1), 18 functions, 11 live.
// Primary owner: Uuid (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x245bb8  Uuid_InitFromTimerMicroseconds_maybe  [dead]
//   [ ] 0x245c98  Uuid_Write
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
//   [ ] 0x246220  StaticInitAndDestruction_246220
//   [ ] 0x246258  _GLOBAL__I_246258
//   [ ] 0x246268  _GLOBAL__D_246268
//   [ ] 0x246278  Uuid_ToString
//   [ ] 0x2462d0  Uuid_ParseHexString_maybe
#include <cstdint>
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

// 0x002461d8 Uuid_IsNull
bool Uuid_IsNull(const uint32_t* uuid) { return uuid[0] == 0 && uuid[1] == 0 && uuid[2] == 0 && uuid[3] == 0; }
