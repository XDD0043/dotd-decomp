// Str.h - the string helpers of the Str unit (Str.cpp, 0x10b68-0x12158) that other units call.
#pragma once
#include <cstdarg>
#include <cstdint>

// 0x000111e0 Str_VFormatBounded: vsnprintf(dst, size - 1, format, args); on a negative result dst[size - 1] = 0.
// Returns vsnprintf's result.
int32_t Str_VFormatBounded(char* dst, int32_t size, const char* format, va_list args);
// 0x00011100 Mem_FreeAlignedAndNull: *block freed (Mem_FreeAligned16) and cleared when not null.
void Mem_FreeAlignedAndNull(char** block);
// 0x00011248 Str_CopyBounded: at most size - 1 characters and a terminator (strncpy when the source does not fit).
// Caller: CKSoundStreamManager_FindOrCreateType_maybe 0x115d60 (not ported).
void Str_CopyBounded(char* dst, const char* src, uint32_t size);
// 0x00011d38 Str_VFormatAlloc: into `buffer` (size `size`) when it is given and the text fits; otherwise a new
// Mem_AllocAligned16 block of at least max(strlen(format), 0x400) bytes, doubled until the text fits (its size into
// *allocated when given).
char* Str_VFormatAlloc(const char* format, va_list args, char* buffer, int32_t size, uint32_t* allocated);
// 0x00011f90 Str_FormatAllocTo: *out = Str_VFormatAlloc(format, ..., no buffer) (the keCThreadPool workers' names).
void Str_FormatAllocTo(char** out, const char* format, ...);
