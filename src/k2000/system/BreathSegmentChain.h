// BreathSegmentChain.h - 0x009bef38 BreathSegmentChain_Free_maybe (original unit LwMutex.cpp, the COMDAT tail): a chain of
// blocks linked through the word +0x2c, freed from the node after `node` to the end, the deepest first (the original
// unrolls the recursion nine levels; the order of the frees is the same). `node` itself is not freed. Its only live
// caller is 0x00371608 KBaseC_vf80 (CKS08HeroElement.cpp, R10), whose segment type gives Node; Node needs a pointer
// member m_pNext at +0x2c.
#pragma once

#include "k2000/memory/Mem.h"

template <class Node>
void BreathSegmentChain_Free(Node* node) {
    Node* next = node->m_pNext;  // +0x2c
    if (next == nullptr) return;
    BreathSegmentChain_Free(next);
    Mem_FreeAligned16(node->m_pNext);  // 0x00052fb8 (reloaded)
}
