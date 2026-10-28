// TVector.h - the engine's growable array (XXL2: K/KUL/TVector/EUL_TVector.h, TVector<T, Grow, bool>):
// a 16-byte aligned block that grows in steps of Grow elements. Only what the ported code uses so far.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"

template <class T, uint32_t Grow>
struct TVector {
    T* m_pBlock;               // +0x00 Mem_AllocAligned16 / Mem_ReallocAligned16
    uint32_t m_ui32NbElt;      // +0x04 capacity
    uint32_t m_ui32NbUsedElt;  // +0x08 length
};
