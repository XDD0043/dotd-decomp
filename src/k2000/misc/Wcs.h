// Wcs.h - the engine's 16-bit wide-string helpers (Wcs.cpp, 0x10558-0x10b68). The K engine's wchar_t
// is 16 bits on the PS3: the strings are uint16_t here.
#pragma once
#include <cstdint>

// 0x00010a40 WStr_CopyReturnEnd: copies src with its terminator; returns the end of dst (its 0).
uint16_t* WStr_CopyReturnEnd(uint16_t* dst, const uint16_t* src);
// 0x00010a78 Wcs_Compare: unsigned 16-bit compare; -1, 0 or 1.
int32_t Wcs_Compare(const uint16_t* a, const uint16_t* b);
// 0x00010af8 Wcs_ToAscii: the low byte of every character.
void Wcs_ToAscii(char* dst, const uint16_t* src);
// 0x00010b28 WStr_FromAscii: every byte zero-extended.
void WStr_FromAscii(uint16_t* dst, const char* src);
// 0x000107d8 Str_HashXor4: the bytes XORed into four accumulators in turn, returned as a little-endian word.
// (CKInput.cpp, CKInputBlockSingleAction.cpp and CLocManager.cpp keep local copies.)
uint32_t Str_HashXor4(const char* s);
// 0x00010928 Wcs_FindChar: the first `c` of `s`, or null.
const uint16_t* Wcs_FindChar(const uint16_t* s, uint16_t c);
// 0x00010a18 Wcs_Length: the characters before the terminator. (CLocManager.cpp keeps a local copy; the others count
// inline.)
uint32_t Wcs_Length(const uint16_t* s);
