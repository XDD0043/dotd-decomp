// rand.h - the game's libc rand() (Dinkumware, 0x95eac0), bit-exact.
//
// An LCG (x * 1664525 + 1013904223) feeding a 32-entry Bays-Durham shuffle table; the result is the
// low 30 bits of the drawn entry (RAND_MAX 0x3fffffff). The state is thread-local on the PS3 (TLS
// r13-0x7000.., seed 1 from the TLS image) and nothing in the game reseeds it, so every thread has
// its own sequence starting from seed 1. Each host thread gets its own state the same way.
#pragma once
#include <cstdint>

namespace crt {

constexpr int32_t kRandMax = 0x3fffffff;

// 0x0095eac0 rand
int32_t rand();

// The calling thread's state, for save states and tests.
struct RandState {
    uint32_t seed;        // TLS -0x7000 (initial 1)
    uint8_t initialized;  // TLS -0x6fec
    uint32_t last;        // TLS -0x6fe8: previous output word (selects the next table slot)
    uint32_t table[32];   // TLS -0x6fe4
};
RandState& ThreadRandState();

// Platform debug code (the replay's rand log, C2.7): called after every draw when set (all threads).
using RandObserver = void (*)();
void SetRandObserver(RandObserver observer);

}  // namespace crt
