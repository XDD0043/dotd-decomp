// GameVector.h - the TVector growth the game-structure Loads inline (CKGameLevel_Load 0x3a970,
// CKGameModule_Load 0x3bf18, CKS08GameLevel_Load 0x5075e8, ...). Family-local until TVector.h has it.
#pragma once
#include <cstdint>

#include "k2000/memory/Mem.h"
#include "k2000/util/TVector.h"

// Sets the length to count. When the capacity is smaller, the block grows to the next multiple of Grow
// above count ((count & ~(Grow - 1)) + Grow, Grow elements if that wraps to 0) with
// Mem_ReallocAligned16; the new elements are not initialised.
template <class T, uint32_t Grow>
inline void GameVector_Resize(TVector<T, Grow>* vector, uint32_t count) {
    if (vector->m_ui32NbElt < count) {
        uint32_t capacity = (count & ~(Grow - 1)) + Grow;
        if (capacity == 0) capacity = Grow;
        T* block = static_cast<T*>(
            Mem_ReallocAligned16(vector->m_pBlock, capacity * static_cast<uint32_t>(sizeof(T))));
        vector->m_ui32NbElt = capacity;
        vector->m_pBlock = block;
    }
    vector->m_ui32NbUsedElt = count;
}

// A fresh block of exactly count elements (one when count is 0); the old block is not freed and the
// length is left as it is (IKGameStructure's Load 0x41f90, CKS08GameStructure_Load 0x5108d0).
template <class T, uint32_t Grow>
inline void GameVector_Allocate(TVector<T, Grow>* vector, uint32_t count) {
    const uint32_t capacity = count == 0 ? 1u : count;
    vector->m_ui32NbElt = capacity;
    vector->m_pBlock = static_cast<T*>(Mem_AllocAligned16(capacity * static_cast<uint32_t>(sizeof(T))));
}

// Appends value. When full, the capacity grows by Grow (Grow elements if that wraps to 0) with
// Mem_ReallocAligned16 (CKGameState_AddStageValue_maybe 0x3faa8 and its siblings).
template <class T, uint32_t Grow>
inline void GameVector_Add(TVector<T, Grow>* vector, const T& value) {
    if (vector->m_ui32NbElt == vector->m_ui32NbUsedElt) {
        uint32_t capacity = vector->m_ui32NbUsedElt + Grow;
        if (capacity == 0) capacity = Grow;
        vector->m_pBlock = static_cast<T*>(
            Mem_ReallocAligned16(vector->m_pBlock, capacity * static_cast<uint32_t>(sizeof(T))));
        vector->m_ui32NbElt = capacity;
    }
    vector->m_pBlock[vector->m_ui32NbUsedElt] = value;
    ++vector->m_ui32NbUsedElt;
}

// The InitializeGameData/InitializeLevelData reset: capacity Grow, a fresh block (the old one is not
// freed), the length left as it is.
template <class T, uint32_t Grow>
inline void GameVector_Reserve(TVector<T, Grow>* vector) {
    vector->m_ui32NbElt = Grow;
    vector->m_pBlock = static_cast<T*>(Mem_AllocAligned16(Grow * static_cast<uint32_t>(sizeof(T))));
}
