// Wcs.cpp - the engine's small string helpers (16-bit wide strings, the K engine's wchar_t).
//
// Reconstructed original translation unit: 0x10558-0x10b68 (GAME_TOC1, main_toc1), 28 functions, 16 live.
// Primary owner: Wcs (not a registered class)
// Other owners: Str (3), WStr (2), Math (1), RwFrame (1), Object (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x10558  __do_global_dtors_aux  [platform]  (the C runtime's static destructor walk (__deregister_frame_info): the host C++ runtime)
//   [ ] 0x105f8  frame_dummy  [platform]  (the C runtime's frame-info registration: the host C++ runtime)
//   [ ] 0x10670  KStub_Return0_10670  [dead]
//   [ ] 0x10678  FUN_00010678  [dead]
//   [x] 0x10688  KStub_Nop_10688  (empty (Cleanup's call): nothing to call)
//   [x] 0x10690  Math_Sqrtf  (C22SpyroShims.h c22spyro::MathSqrtf)
//   [x] 0x10698  RwFrame_MarkDirty
//   [x] 0x106b8  KStub_Nop_106b8
//   [x] 0x106c0  KStub_Nop_106c0
//   [ ] 0x106c8  KStub_Nop_106c8  [dead]
//   [ ] 0x106d0  KStub_Nop_106d0  [dead]
//   [x] 0x106d8  KStub_Nop_106d8  (empty (the debug logs' and the sound update's call): nothing to call)
//   [ ] 0x106e0  KStub_Nop_106e0  [dead]
//   [ ] 0x106e8  KStub_Nop_106e8  [dead]
//   [ ] 0x106f0  Object_DynamicCastByKey_maybe  [dead]
//   [ ] 0x10790  FUN_00010790  [dead]
//   [x] 0x107d8  Str_HashXor4
//   [ ] 0x10838  Str_HashXor2  [dead]
//   [ ] 0x10898  Str_ReplaceChar  [dead]
//   [ ] 0x108e0  Wcs_FindChar_2  [dead]
//   [x] 0x10928  Wcs_FindChar  (TextData.cpp keeps its non-const local copy)
//   [ ] 0x10970  Wcs_FindSubstring  [dead]
//   [x] 0x10a18  Wcs_Length  (CLocManager.cpp keeps a local copy; the other callers count inline)
//   [x] 0x10a40  WStr_CopyReturnEnd
//   [x] 0x10a78  Wcs_Compare
//   [x] 0x10af8  Wcs_ToAscii
//   [x] 0x10b28  WStr_FromAscii
//   [x] 0x10b60  KStub_Nop_10b60  (empty (CKGraphic init's, the loading manager's and the input's call): nothing to call)

#include "k2000/misc/Wcs.h"

// 0x00010a40 WStr_CopyReturnEnd: copies src with its terminator; returns the end of dst (its 0).
uint16_t* WStr_CopyReturnEnd(uint16_t* dst, const uint16_t* src) {
    uint16_t c = *src;
    while (c != 0) {
        *dst = c;
        ++src;
        ++dst;
        c = *src;
    }
    *dst = 0;
    return dst;
}

// 0x00010a78 Wcs_Compare: unsigned 16-bit compare; -1, 0 or 1.
int32_t Wcs_Compare(const uint16_t* a, const uint16_t* b) {
    uint16_t ca = *a;
    while (ca != 0) {
        const uint16_t cb = *b;
        if (cb == 0 || cb < ca) return 1;
        if (cb > ca) return -1;
        ++a;
        ++b;
        ca = *a;
    }
    // 0x10ac8: neg + srawi 31: -1 when b goes on, 0 at the end of both.
    return *b != 0 ? -1 : 0;
}

// 0x00010af8 Wcs_ToAscii: the low byte of every character.
void Wcs_ToAscii(char* dst, const uint16_t* src) {
    uint16_t c = *src;
    while (c != 0) {
        *dst = static_cast<char>(c);
        ++src;
        ++dst;
        c = *src;
    }
    *dst = 0;
}

// 0x00010b28 WStr_FromAscii: every byte zero-extended.
void WStr_FromAscii(uint16_t* dst, const char* src) {
    uint8_t c = static_cast<uint8_t>(*src);
    while (c != 0) {
        *dst = c;
        ++src;
        ++dst;
        c = static_cast<uint8_t>(*src);
    }
    *dst = 0;
}

// 0x000106b8 KStub_Nop_106b8 / 0x000106c0 KStub_Nop_106c0: empty registrations (CKS08GameManager_Init).
void KStub_Nop_106b8(int32_t, const void*) {}
void KStub_Nop_106c0(int32_t, const void*) {}

// 0x000107d8 Str_HashXor4
uint32_t Str_HashXor4(const char* s) {
    uint8_t acc[4] = {0, 0, 0, 0};
    for (uint32_t i = 0; s[i] != 0; ++i) acc[i & 3] ^= static_cast<uint8_t>(s[i]);
    return static_cast<uint32_t>(acc[0]) | (static_cast<uint32_t>(acc[1]) << 8) | (static_cast<uint32_t>(acc[2]) << 16) |
           (static_cast<uint32_t>(acc[3]) << 24);
}

// 0x00010928 Wcs_FindChar
const uint16_t* Wcs_FindChar(const uint16_t* s, uint16_t c) {
    for (uint16_t ch = *s; ch != 0; ch = *++s) {
        if (ch == c) return s;
    }
    return nullptr;
}

// 0x00010a18 Wcs_Length
uint32_t Wcs_Length(const uint16_t* s) {
    uint32_t n = 0;
    while (s[n] != 0) ++n;
    return n;
}
