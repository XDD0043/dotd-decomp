// CKAnchor.cpp - reconstructed original translation unit 0x2050c0-0x205290 (GAME_TOC1, main_toc1), 12 functions, 11 live.
// Primary owner: CKAnchor (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x2050c0  CKAnchor_610c_maybe_ConstructBase_2  [dead]
//   [x] 0x2050d0  StaticInitAndDestruction_2050d0  (the two file statics below)
//   [ ] 0x205100  _GLOBAL__I_205100
//   [ ] 0x205110  _GLOBAL__D_205110
//   [x] 0x205120  CKAnchor_610c_maybe_ConstructBase
//   [x] 0x205130  CKAnchor_LoadBase_maybe
//   [x] 0x205208  CKAnchor_610c_maybe_vf28  (Save: returns 1, the default slot)
//   [x] 0x205210  CKAnchor_610c_maybe_vf24  (RecursiveRegistration: returns 1, the default slot)
//   [x] 0x205218  KStub_Nop_205218  (empty)
//   [x] 0x205220  CKAnchor_610c_maybe_vf0  (C++ destructor chain: vtable stores only)
//   [x] 0x205238  CKAnchor_610c_maybe_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x205250  CKAnchor_610c_maybe_DeletingDestructor  (the destructor; delete)
//
//   [ ] 0x9b1720  CKAnchor_610c_maybe_vf14  [inline]
//   [ ] 0x9b1728  CKAnchor_610c_maybe_vf18  [inline]
//   [ ] 0x9b1730  CKAnchor_610c_maybe_vf8  [inline]
//   [ ] 0x9b1750  KStub_Return0_9b1750  [inline]
#include "k2000/misc/KBase610C.h"

#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// 0x00205130 CKAnchor_LoadBase_maybe
int32_t KBase610C::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pBlock);
    ReadRaw(file, &m_unk08, 1);
    return 1;
}

void KAnchor_LoadRefVector(IKFile* file, TVector<IKSerializable*, 1>* vector) {
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count == 0) {
        vector->m_ui32NbElt = 1;
        vector->m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(IKSerializable*))));
    } else {
        vector->m_ui32NbElt = count;
        vector->m_pBlock =
            static_cast<IKSerializable**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(IKSerializable*))));
    }
    if (vector->m_ui32NbElt < count) {  // as in the original: cannot happen
        uint32_t capacity = count + 1;
        if (capacity == 0) capacity = 1;
        vector->m_pBlock = static_cast<IKSerializable**>(
            Mem_ReallocAligned16(vector->m_pBlock, capacity * static_cast<uint32_t>(sizeof(IKSerializable*))));
        vector->m_ui32NbElt = capacity;
    }
    vector->m_ui32NbUsedElt = count;
    IKFile_ReadObjectRefArray(file, vector->m_pBlock, count);
}

void KAnchor_PushBack(TVector<KBase610C*, 1>* vector, KBase610C* anchor) {
    if (vector->m_ui32NbElt == vector->m_ui32NbUsedElt) {
        uint32_t capacity = vector->m_ui32NbUsedElt + 1;
        if (capacity == 0) capacity = 1;
        vector->m_pBlock = static_cast<KBase610C**>(
            Mem_ReallocAligned16(vector->m_pBlock, capacity * static_cast<uint32_t>(sizeof(KBase610C*))));
        vector->m_ui32NbElt = capacity;
    }
    vector->m_pBlock[vector->m_ui32NbUsedElt] = anchor;
    vector->m_ui32NbUsedElt += 1;
}

// 0x002050d0 StaticInitAndDestruction_2050d0 (_GLOBAL__I_205100): two file statics (0x00cea960, 0x00cea964) set to
// -1.0f. Nothing in the game reads them.
namespace {
[[maybe_unused]] float s_unkcea960 = -1.0f;
[[maybe_unused]] float s_unkcea964 = -1.0f;
}  // namespace
