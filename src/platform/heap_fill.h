// heap_fill.h - the heap fill: what new heap blocks hold (new platform code, not in the original).
//
// Every new heap block starts as one byte before the game sees it: the engine's Mem_AllocAligned16 /
// Mem_ReallocateAligned (the bytes past the copied part), RwMalloc, the particle batches and the global operator new /
// new[] (heap_fill.cpp replaces them). The byte is 0 by default, so debug and release builds behave the same: without
// it a field the port never writes reads the debug CRT's 0xCD in debug and malloc leftovers in release (the missing
// fights, the HUD). The PS3's operator new is plain malloc (0x76b9c8 -> 0x6913a0), so the original reads leftovers too;
// zero is what its fresh heap mostly holds.
//
// DOTD_HEAP_FILL=<byte> (hex: 00, ff, 3f, cd, ...) picks another byte; DOTD_HEAP_FILL=off fills nothing (malloc as is).
// Correct code never reads a byte it has not written, so runs with different fills must give the same frames, state
// and rand draws; work/fill_test.py replays the captures that way and reports the first difference: a field the port
// reads before writing (an unported constructor, Load, PostLoad or SetDefaultState).
#pragma once
#include <cstddef>

namespace dotd {
// The fill byte (default 0), or -1 for DOTD_HEAP_FILL=off (read once).
int HeapFillByte();
// Fills size bytes at block with the fill byte; no-op with DOTD_HEAP_FILL=off or for a null block.
void HeapFill(void* block, size_t size);
}  // namespace dotd
