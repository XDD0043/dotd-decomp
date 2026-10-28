// TVectorPush.h - the TVector<T, 1> operations the group and component Loads inline (CKS08FightZoneCpnt_Load
// 0x2758c0, CKGrpFightZone_Load 0x26f108): grow-by-one before a push, and the reference read into slot i.
#pragma once
#include <cstdint>

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/util/TVector.h"

// Grows the block by one element when it is full (Mem_ReallocAligned16 of (capacity + 1) elements).
template <class T, uint32_t Grow>
inline void TVector_GrowIfFull(TVector<T, Grow>& v) {
    if (v.m_ui32NbElt == v.m_ui32NbUsedElt) {
        uint32_t capacity = v.m_ui32NbUsedElt + Grow;
        if (capacity == 0) capacity = Grow;
        v.m_pBlock = static_cast<T*>(Mem_ReallocAligned16(v.m_pBlock, capacity * static_cast<uint32_t>(sizeof(T))));
        v.m_ui32NbElt = capacity;
    }
}

// The "resize to count" the Loads inline (CKGrpFightZone_Load, CKGrpSquad_Load): without elements the capacity
// is Grow and a Grow-element block is allocated, the used count is left alone; otherwise the capacity is set
// to the count before a count-element block is allocated (the old block is not freed), so the reserve that
// follows (to the next multiple of Grow above the count) never runs, and the used count becomes the count.
// The elements are not constructed: the callers do what the original does with them.
template <class T, uint32_t Grow>
inline void TVector_ResizeForLoad(TVector<T, Grow>& v, uint32_t count) {
    if (count == 0) {
        v.m_ui32NbElt = Grow;
        v.m_pBlock = static_cast<T*>(Mem_AllocAligned16(Grow * static_cast<uint32_t>(sizeof(T))));
        return;
    }
    v.m_ui32NbElt = count;
    v.m_pBlock = static_cast<T*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(T))));
    if (v.m_ui32NbElt < count) {
        uint32_t capacity = (count / Grow) * Grow + Grow;
        if (capacity == 0) capacity = Grow;
        v.m_pBlock = static_cast<T*>(Mem_ReallocAligned16(v.m_pBlock, capacity * static_cast<uint32_t>(sizeof(T))));
        v.m_ui32NbElt = capacity;
    }
    v.m_ui32NbUsedElt = count;
}

// The reference-list read of CKS08FightZoneCpnt: a one-element block when the vector has none, then per
// reference the vector grows and counts it first, and the reference is read into slot i (the loop index,
// not the used count).
template <class T>
inline void TVector_LoadRefsCounted(TVector<T*, 1>& v, IKFile* file) {
    if (v.m_pBlock == nullptr) {
        v.m_ui32NbElt = 1;
        v.m_pBlock = static_cast<T**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(T*))));
    }
    uint32_t count = 0;
    ReadU32LE(file, &count);
    for (uint32_t i = 0; i < count; ++i) {
        TVector_GrowIfFull(v);
        ++v.m_ui32NbUsedElt;
        IKFile_ReadRef(file, &v.m_pBlock[i]);
    }
}

// The byte-list read: always a new one-byte block (the old one is not freed, the used count is kept), then
// per byte: read, grow if full, push.
inline void TVector_LoadBytes(TVector<uint8_t, 1>& v, IKFile* file) {
    v.m_ui32NbElt = 1;
    v.m_pBlock = static_cast<uint8_t*>(Mem_AllocAligned16(1));
    uint32_t count = 0;
    ReadU32LE(file, &count);
    for (uint32_t i = 0; i < count; ++i) {
        uint8_t value = 0;
        ReadU8(file, &value);
        TVector_GrowIfFull(v);
        v.m_pBlock[v.m_ui32NbUsedElt++] = value;
    }
}
