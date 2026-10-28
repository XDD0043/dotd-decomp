// Wcs.cpp - the engine's small string helpers (16-bit wide strings, the K engine's wchar_t).
//
// Reconstructed original translation unit: 0x10558-0x10b68 (GAME_TOC1, main_toc1), 28 functions, 16 live.
// Primary owner: Wcs (not a registered class)
// Other owners: Str (3), WStr (2), Math (1), RwFrame (1), Object (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x10558  __do_global_dtors_aux
//   [ ] 0x105f8  frame_dummy
//   [ ] 0x10670  KStub_Return0_10670  [dead]
//   [ ] 0x10678  FUN_00010678  [dead]
//   [ ] 0x10688  KStub_Nop_10688
//   [ ] 0x10690  Math_Sqrtf
//   [x] 0x10698  RwFrame_MarkDirty
//   [x] 0x106b8  KStub_Nop_106b8
//   [x] 0x106c0  KStub_Nop_106c0
//   [ ] 0x106c8  KStub_Nop_106c8  [dead]
//   [ ] 0x106d0  KStub_Nop_106d0  [dead]
//   [ ] 0x106d8  KStub_Nop_106d8
//   [ ] 0x106e0  KStub_Nop_106e0  [dead]
//   [ ] 0x106e8  KStub_Nop_106e8  [dead]
//   [ ] 0x106f0  Object_DynamicCastByKey_maybe  [dead]
//   [ ] 0x10790  FUN_00010790  [dead]
//   [ ] 0x107d8  Str_HashXor4
//   [ ] 0x10838  Str_HashXor2  [dead]
//   [ ] 0x10898  Str_ReplaceChar  [dead]
//   [ ] 0x108e0  Wcs_FindChar_2  [dead]
//   [ ] 0x10928  Wcs_FindChar
//   [ ] 0x10970  Wcs_FindSubstring  [dead]
//   [ ] 0x10a18  Wcs_Length
//   [x] 0x10a40  WStr_CopyReturnEnd
//   [x] 0x10a78  Wcs_Compare
//   [x] 0x10af8  Wcs_ToAscii
//   [x] 0x10b28  WStr_FromAscii
//   [ ] 0x10b60  KStub_Nop_10b60

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
