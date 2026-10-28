// rand.cpp - see rand.h. Ported from the assembly of 0x95eac0.
#include "crt/rand.h"

namespace crt {

namespace {
constexpr uint32_t kMul = 0x19660d;    // 1664525
constexpr uint32_t kAdd = 0x3c6ef35f;  // 1013904223 (addis 0x3c6f, subi 0xca1)

thread_local RandState t_state = {1u, 0u, 0u, {}};
RandObserver g_observer = nullptr;
}  // namespace

RandState& ThreadRandState() { return t_state; }

void SetRandObserver(RandObserver observer) { g_observer = observer; }

// 0x0095eac0 rand
int32_t rand() {
    RandState& st = t_state;
    if (st.initialized == 0) {
        uint32_t x = st.seed;
        for (int i = 0; i < 8; ++i) x = x * kMul + kAdd;  // warm-up
        st.seed = x;
        for (int i = 0; i < 32; ++i) {
            x = x * kMul + kAdd;
            st.table[i] = x;
        }
        st.initialized = 1;
        st.seed = x;
        st.last = st.table[31];
    }
    st.seed = st.seed * kMul + kAdd;
    const uint32_t slot = st.last & 31u;  // rlwinm r9,last,2,25,29 (byte offset slot * 4)
    const uint32_t drawn = st.table[slot];
    st.last = drawn;
    st.table[slot] = st.seed;
    if (g_observer != nullptr) g_observer();
    return static_cast<int32_t>(drawn & 0x3fffffffu);
}

}  // namespace crt
