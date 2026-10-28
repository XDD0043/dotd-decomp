// Ps3Qsort.h - the PS3 libc's qsort (0x95eab0 qsort -> 0x95e4b8 Sort_IntroSort), ported so that items with equal sort keys
// end up in the same order as in the original. The algorithm is an introsort: an insertion sort up to 32 elements, a
// three-way partition around a median of three (nine for large ranges) whose recursion budget starts at the element count
// and shrinks by 3/4 per level, and a heap sort when the budget is spent. It is not stable.
#pragma once
#include <cstdint>

// 0x0095eab0 qsort: `compare` gets pointers to two elements and returns <0, 0 or >0.
void Ps3Qsort(void* base, uint32_t count, uint32_t size, int (*compare)(const void*, const void*));
