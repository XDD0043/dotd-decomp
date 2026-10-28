// TVectorLoad.h - the reference-vector read that the component and group Loads inline (CKGroundCpnt_Load
// 0x191268, CKBoundingCpnt_Load 0x190c98, CKSekensLauncherCpnt_Load 0x1f7d20, ...): one u32 count, the
// capacity set to the count, a new block of count references (the old block, if any, is not freed), then
// for each reference a null slot pushed (the vector grows by Grow elements when full, which never happens
// here since the capacity is the count) and the reference read into it. The used count is not reset first:
// it continues from the constructor's 0.
#pragma once
#include <cstdint>

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/util/TVector.h"

template <class T, uint32_t Grow>
inline void TVector_LoadRefs(TVector<T*, Grow>& vector, IKFile* file) {
    uint32_t count = 0;
    ReadU32LE(file, &count);
    vector.m_ui32NbElt = count;
    vector.m_pBlock = static_cast<T**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(T*))));
    for (uint32_t i = 0; i < count; ++i) {
        if (vector.m_ui32NbElt == vector.m_ui32NbUsedElt) {
            uint32_t capacity = vector.m_ui32NbUsedElt + Grow;
            if (capacity == 0) capacity = Grow;
            vector.m_pBlock = static_cast<T**>(
                Mem_ReallocAligned16(vector.m_pBlock, capacity * static_cast<uint32_t>(sizeof(T*))));
            vector.m_ui32NbElt = capacity;
        }
        vector.m_pBlock[vector.m_ui32NbUsedElt] = nullptr;
        T** slot = &vector.m_pBlock[vector.m_ui32NbUsedElt++];
        IKFile_ReadRef(file, slot);
    }
}
