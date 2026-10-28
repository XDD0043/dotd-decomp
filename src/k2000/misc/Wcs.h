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
