// Reconstructed original translation unit: 0x46ab8-0x478b0 (GAME_TOC1, main_toc1), 20 functions, 12 live.
// Primary class: CKQuadtreeCell  key 0x5f8c  category Logic  size 0x5c  vtable 0xb14e28
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x46ab8  CKQuadtreeCell_Delete  (DOTD_DECLARE_FACTORIES Delete)
//   [ ] 0x46b08  CKQuadtreeCell_MoveAgent_maybe  [dead]
//   [ ] 0x46bd8  CKQuadtreeCell_AddAgent_maybe  [dead]
//   [ ] 0x46c00  RegisterCKQuadtreeCellClass
//   [ ] 0x46c78  _GLOBAL__I_46c78
//   [ ] 0x46c88  CKQuadtreeCell_Construct  [dead]
//   [ ] 0x46d18  CKQuadtreeCell_Construct_2  [dead]
//   [x] 0x46da8  CKQuadtreeCell_DeleteArray  (DOTD_DECLARE_FACTORIES DeleteArray)
//   [ ] 0x46e48  CKQuadtreeCell_RemoveAgent_maybe  [dead]
//   [ ] 0x46ed8  CKQuadtreeCell_Save
//   [x] 0x46ee0  CKQuadtreeCell_RecursiveRegistration  (IKSerializable's empty default)
//   [x] 0x46ee8  CKQuadtreeCell_Destroy
//   [ ] 0x46fa8  CKQuadtreeCell_MoveAllAgentsTo_maybe  [dead]
//   [x] 0x470a8  CKQuadtreeCell_Load
//   [x] 0x47420  CKQuadtreeCell_CreateArray  (DOTD_DECLARE_FACTORIES CreateArray)
//   [x] 0x47538  CKQuadtreeCell_Create  (DOTD_DECLARE_FACTORIES Create)
//   [x] 0x475e8  CKQuadtreeCell_DeletingDestructor  (the deleting form of 0x476d8)
//   [x] 0x476d8  CKQuadtreeCell_Destructor
//   [ ] 0x477c0  CKQuadtreeCell_Destructor_2  [dead]
//   [ ] 0x478a8  KStub_Return1_478a8  [dead]
//
//   [ ] 0x9958d0  CKQuadtreeCell_GetClassType  [inline]
//   [ ] 0x9958d8  CKQuadtreeCell_GetClassID  [inline]
//   [ ] 0x9958e0  CKQuadtreeCell_IsKindOfClass  [inline]
#include "k2000/logic/system/CKQuadtreeCell.h"

#include "k2000/memory/Mem.h"

namespace {
template <class T>
void InitArray(TVector<T, 1>& array) {
    array.m_ui32NbElt = 1;
    array.m_pBlock = nullptr;
    array.m_ui32NbUsedElt = 0;
}

// An array's block freed, its length and block cleared (the capacity is kept).
template <class T>
void FreeArray(TVector<T, 1>& array) {
    if (array.m_pBlock != nullptr) {
        Mem_FreeAligned16(array.m_pBlock);  // 0x00052fb8
        array.m_pBlock = nullptr;
    }
    array.m_pBlock = nullptr;
    array.m_ui32NbUsedElt = 0;
}
}  // namespace

// Inlined in 0x00047538 CKQuadtreeCell_Create: the references +0x04 / +0x08, the rectangle, the three arrays (null, 1, 0).
CKQuadtreeCell::CKQuadtreeCell() : m_unk04(nullptr), m_unk08(nullptr) {
    InitArray(m_unk38);
    InitArray(m_unk44);
    InitArray(m_unk50);
}

// 0x000476d8 CKQuadtreeCell_Destructor
CKQuadtreeCell::~CKQuadtreeCell() {
    FreeArray(m_unk50);
    FreeArray(m_unk44);
    FreeArray(m_unk38);
}

// 0x00046ee8 CKQuadtreeCell_Destroy
void CKQuadtreeCell::Destroy() {
    FreeArray(m_unk38);
    FreeArray(m_unk44);
    FreeArray(m_unk50);
}

// 0x000470a8 CKQuadtreeCell_Load: two references, the rectangle, two references, the four children (one contiguous read
// through the resolver, else 16 raw bytes), then three arrays: a count, the block grown to count + 1 units when the
// capacity is smaller (one unit when that wraps; Mem_ReallocAligned16), count * 2 bytes read, each unit swapped.
int32_t CKQuadtreeCell::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_unk04);
    IKFile_ReadRef(file, &m_unk08);
    m_rect.Load(file, K_LEVEL_PLATEFORMS);  // 0x00047c18
    IKFile_ReadRef(file, &m_unk20);
    IKFile_ReadRef(file, &m_unk24);
    IKFile_ReadObjectRefArray(file, m_apChildren, 4);
    TVector<uint16_t, 1>* arrays[3] = {&m_unk38, &m_unk44, &m_unk50};
    for (TVector<uint16_t, 1>* array : arrays) {
        uint32_t count = 0;
        ReadU32LE(file, &count);
        if (array->m_ui32NbElt < count) {
            uint32_t capacity = count + 1;
            uint32_t bytes = capacity * 2;
            if (capacity == 0) {
                capacity = 1;
                bytes = 2;
            }
            array->m_pBlock = static_cast<uint16_t*>(Mem_ReallocAligned16(array->m_pBlock, bytes));  // 0x00053190
            array->m_ui32NbElt = capacity;
        }
        array->m_ui32NbUsedElt = count;
        uint16_t* units = array->m_pBlock;
        file->Read(units, count * 2);
        for (uint32_t i = 0; i < count; ++i) {
            const uint8_t* b = reinterpret_cast<const uint8_t*>(&units[i]);
            units[i] = static_cast<uint16_t>(b[0] | (b[1] << 8));
        }
    }
    return 1;
}
