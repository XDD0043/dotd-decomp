// KObjectRefList.h - a reference array with a separate head reference (0x10 bytes; Ghidra
// KObjectRefList_maybe). Its Load (0x244bd0) sits in the FreeListPools.cpp unit; CKGrpS08Clamp (+0x2c) and
// CKGrpTransportableObject's entries hold one. The name and the role of the fields are inferences.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"

class IKFile;
class IKSerializable;

struct KObjectRefList {
    // 0x00244bd0 KObjectRefList_Load_maybe. Type 0 only: the count (stored twice), the head reference,
    // then the block reallocated to count references (0 without any) and read as one reference array.
    int32_t Load(IKFile* file, int32_t type);

    IKSerializable** m_pBlock;  // +0x00 Mem_ReallocAligned16(count * 4); 0 when the count is 0
    IKSerializable* m_pHead;    // +0x04 a reference read before the array (_maybe)
    uint32_t m_ui32Count;       // +0x08
    uint32_t m_ui32Count2;      // +0x0c the Load copies the count here (_maybe the used count)
};
DOTD_ASSERT_SIZE(KObjectRefList, 0x10);
