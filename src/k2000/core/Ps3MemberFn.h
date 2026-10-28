// Ps3MemberFn.h - the PS3's pointers to member functions as game tables hold them, and their native targets.
//
// A PS3 pointer to member function is two words: the function descriptor's address and the this-adjust (a
// descriptor word with bit 0 set would be a virtual function: vtable offset + 1). The original keeps such pairs
// in its state tables (the hero's four state machines and locomotion animation sub-machines, the carrier hero,
// the weapon, the transportable key, the electric gauge) and in CKSrvDynamic's entries, and calls them as
// `(this + adjust)->*fn(args)`.
//
// DOTD: game data keep the two words unchanged (the rows' layout, their order and the state id bytes are read
// by game code). A class maps the descriptor to a native pointer to member through a side table of
// Ps3MemberFnEntry (a constant array per class, the original's descriptor -> entry -> function). An entry
// whose function is not ported yet holds null and its name with the checkpoint that ports it; calling it logs
// once and does nothing (the caller supplies the "nothing" result: a state handler returns the state it was
// given, a condition returns false).
#pragma once
#include <cstddef>
#include <cstdint>

#include "platform/log.h"

template <class Fn>
struct Ps3MemberFnEntry {
    uint32_t m_descriptor;  // the original's function descriptor (the first word of the pair)
    Fn m_fn;                // the native member function; null: not ported yet
    const char* m_name;     // the original's name, with the checkpoint for an unported one
    bool m_logged;          // DOTD: the "not ported" line was printed
};

// The entry of `descriptor` in `table`, null if the table does not know it.
template <class Fn, size_t N>
Ps3MemberFnEntry<Fn>* FindPs3MemberFn(Ps3MemberFnEntry<Fn> (&table)[N], uint32_t descriptor) {
    for (size_t i = 0; i < N; ++i) {
        if (table[i].m_descriptor == descriptor) return &table[i];
    }
    return nullptr;
}

// Resolves a pair (descriptor, adjust) through `table`: the native function, or null after logging once why
// there is none (unknown descriptor, a virtual or adjusted pointer, or a function not ported yet).
template <class Fn, size_t N>
Fn ResolvePs3MemberFn(Ps3MemberFnEntry<Fn> (&table)[N], const uint32_t pair[2], const char* what) {
    if ((pair[0] & 1u) != 0 || pair[1] != 0) {
        // None of the tables DotD fills has a virtual or adjusted pointer to member.
        static bool s_logged = false;
        if (!s_logged) {
            s_logged = true;
            DOTD_LOG("ptmf: %s: virtual or adjusted pointer to member %08x/%08x (not supported)", what, pair[0], pair[1]);
        }
        return nullptr;
    }
    Ps3MemberFnEntry<Fn>* entry = FindPs3MemberFn(table, pair[0]);
    if (entry == nullptr) {
        static bool s_logged = false;
        if (!s_logged) {
            s_logged = true;
            DOTD_LOG("ptmf: %s: unknown descriptor %08x", what, pair[0]);
        }
        return nullptr;
    }
    if (entry->m_fn == nullptr && !entry->m_logged) {
        entry->m_logged = true;
        DOTD_LOG("stub: %s (not ported yet)", entry->m_name);
    }
    return entry->m_fn;
}
