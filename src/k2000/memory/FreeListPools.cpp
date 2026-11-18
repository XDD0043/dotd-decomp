// FreeListPools.cpp - reconstructed original translation unit 0x244a08-0x245038 (GAME_TOC1, main_toc1), 7 functions, 6 live.
// Primary owner: FreeListPools (not a registered class)
// Other owners: PtrArray (2), KObjectRefList (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x244a08  FreeListPools_InitGlobal_maybe  [platform]  (the ten global node pools' setup: replaced by design: the port allocates each pool's nodes with new / delete (the FreeListPool users' notes); BootStubs.cpp's FreeListPools_InitGlobal is empty)
//   [ ] 0x244af0  FreeListPools_FreeAllGlobal_maybe  [platform]  (the ten global node pools' free lists released: replaced by design (new / delete per node); BootStubs.cpp's FreeListPools_FreeAllGlobal is empty)
//   [x] 0x244b90  PtrArray_PopBack_maybe  (KObjectRefList.h)
//   [x] 0x244bc8  KStub_Return1_244bc8  (returns 1, nothing else: its one call is in CKGrpS08Clamp_Save (the Saves are left out))
//   [x] 0x244bd0  KObjectRefList_Load_maybe
//   [x] 0x244dc8  PtrArray_SwapIntoActivePartition_maybe
//   [ ] 0x244ed0  KObjectRefList_LevelResetAll_maybe  [dead]
#include "k2000/memory/KObjectRefList.h"

#include "k2000/core/IKSerializable.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// 0x00244dc8 PtrArray_SwapIntoActivePartition_maybe: from the boundary (+0x0c) on, the first slot that is null or holds
// `object` (the count when none: BUG(original), the swap then reads one past the array) is exchanged with the slot at the
// boundary (three xors), and the boundary moves up one.
void KObjectRefList::SwapIntoActivePartition(IKSerializable* object) {
    const uint32_t boundary = m_ui32Count2;
    uint32_t found = boundary;
    for (uint32_t left = m_ui32Count - boundary; left != 0; --left, ++found) {
        IKSerializable* slot = m_pBlock[found];
        if (slot == nullptr || slot == object) break;
    }
    if (found != boundary) {
        IKSerializable* a = m_pBlock[boundary];
        m_pBlock[boundary] = m_pBlock[found];
        m_pBlock[found] = a;
    }
    m_ui32Count2 = boundary + 1;
}

// 0x00244bd0 KObjectRefList_Load_maybe
int32_t KObjectRefList::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_ui32Count);
    m_ui32Count2 = m_ui32Count;
    IKFile_ReadRef(file, &m_pHead);
    if (m_ui32Count == 0) {
        m_pBlock = nullptr;  // the old block, if any, is not freed
        return 1;
    }
    m_pBlock = static_cast<IKSerializable**>(
        Mem_ReallocAligned16(m_pBlock, m_ui32Count * static_cast<uint32_t>(sizeof(IKSerializable*))));
    IKFile_ReadObjectRefArray(file, m_pBlock, m_ui32Count);
    return 1;
}
