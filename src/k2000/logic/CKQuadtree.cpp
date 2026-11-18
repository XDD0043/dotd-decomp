// CKQuadtree.cpp - reconstructed original translation unit 0x44578-0x45500 (GAME_TOC1, main_toc1), 18 functions, 12 live.
// Primary class: CKQuadtree  key 0x5fcc  category Logic  size 0x64  vtable 0xb14d10
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x44578  CKQuadtree_Delete
//   [ ] 0x445c8  CKQuadtree_Construct  [dead]
//   [ ] 0x44620  CKQuadtree_UpdateRootBoundsIfDirty_maybe  [dead]
//   [ ] 0x44688  RegisterCKQuadtreeClass
//   [ ] 0x44700  _GLOBAL__I_44700
//   [x] 0x44710  CKQuadtree_DeleteArray
//   [ ] 0x447b0  CKQuadtree_Construct_2  [dead]
//   [ ] 0x44808  CKQuadtree_Save
//   [x] 0x44810  CKQuadtree_RecursiveRegistration  (returns 1, registers nothing: the default)
//   [x] 0x44818  CKQuadtree_Destroy
//   [ ] 0x448f8  CKQuadtree_RepositionAgent_maybe  [dead]
//   [ ] 0x44af8  CKQuadtree_RepositionAgentsIfDirty_maybe  [dead]
//   [x] 0x44b40  CKQuadtree_CreateArray
//   [x] 0x44c28  CKQuadtree_Create
//   [x] 0x44ca8  CKQuadtree_Load
//   [x] 0x45248  CKQuadtree_DeletingDestructor  (the destructor; delete)
//   [x] 0x45340  CKQuadtree_Destructor
//   [ ] 0x45420  CKQuadtree_Destructor_2  [dead]
//
//   [ ] 0x995820  CKQuadtree_GetClassType  [inline]
//   [ ] 0x995828  CKQuadtree_GetClassID  [inline]
//   [ ] 0x995830  CKQuadtree_IsKindOfClass  [inline]
#include "k2000/logic/CKQuadtree.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

namespace {
// The arrays' inlined growth: a count above the capacity makes the block count + 1 elements (one element when that
// wraps to 0; Mem_ReallocAligned16); the length is the count either way.
template <class T>
void SetCount(TVector<T, 1>& array, uint32_t count) {
    if (array.m_ui32NbElt < count) {
        uint32_t capacity = count + 1;
        uint32_t bytes = capacity * static_cast<uint32_t>(sizeof(T));
        if (capacity == 0) {
            capacity = 1;
            bytes = static_cast<uint32_t>(sizeof(T));
        }
        array.m_pBlock = static_cast<T*>(Mem_ReallocAligned16(array.m_pBlock, bytes));  // 0x00053190
        array.m_ui32NbElt = capacity;
    }
    array.m_ui32NbUsedElt = count;
}

// An array's block freed, its length and block cleared (the capacity is kept).
template <class T>
void FreeArray(TVector<T, 1>& array) {
    if (array.m_pBlock != nullptr) {
        Mem_FreeAligned16(array.m_pBlock);  // 0x00052fb8
        array.m_pBlock = nullptr;
    }
    array.m_ui32NbUsedElt = 0;
    array.m_pBlock = nullptr;
}

template <class T>
void InitArray(TVector<T, 1>& array) {
    array.m_pBlock = nullptr;
    array.m_ui32NbElt = 1;
    array.m_ui32NbUsedElt = 0;
}
}  // namespace

// Inlined in 0x00044c28 CKQuadtree_Create (and CreateArray 0x44b40, the dead Construct 0x445c8).
CKQuadtree::CKQuadtree() {
    InitArray(m_unk20);
    InitArray(m_unk2c);
    InitArray(m_unk38);
    InitArray(m_unk44);
}

// 0x00045340 CKQuadtree_Destructor
CKQuadtree::~CKQuadtree() {
    FreeArray(m_unk44);
    FreeArray(m_unk38);
    FreeArray(m_unk2c);
    FreeArray(m_unk20);
}

// 0x00044818 CKQuadtree_Destroy
void CKQuadtree::Destroy() {
    FreeArray(m_unk20);
    FreeArray(m_unk2c);
    FreeArray(m_unk38);
    FreeArray(m_unk44);
}

// 0x00044ca8 CKQuadtree_Load
int32_t CKQuadtree::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_unk04);
    IKFile_ReadRef(file, &m_unk08);
    ReadU32LE(file, &m_unk1c);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    SetCount(m_unk20, count);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_unk20.m_pBlock), count * 3);  // one read, then every word swapped
    // BUG(original): the last three arrays read one record's bytes (6, 12, 4) whatever their count, not swapped.
    ReadU32LE(file, &count);
    SetCount(m_unk2c, count);
    ReadRaw(file, m_unk2c.m_pBlock, 6);
    ReadU32LE(file, &count);
    SetCount(m_unk38, count);
    ReadRaw(file, m_unk38.m_pBlock, 12);
    ReadU32LE(file, &count);
    SetCount(m_unk44, count);
    ReadRaw(file, m_unk44.m_pBlock, 4);
    ReadU32LE(file, &m_unk50);
    ReadU32LE(file, &m_unk54);
    ReadU32LE(file, &m_unk58);
    ReadU8(file, &m_unk60);
    ReadU8(file, &m_unk61);
    return 1;
}
