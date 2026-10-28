// CKLocTextAccessor.cpp - reconstructed original translation unit 0x35e70-0x36500 (GAME_TOC1, main_toc1), 15 functions, 13 live.
// Primary class: CKLocTextAccessor  key 0xe46  category Component  size 0x14  vtable 0xb14520
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x35e70  CKLocTextAccessor_Delete
//   [ ] 0x35ec0  CKLocTextAccessor_Construct  [dead]
//   [ ] 0x35ee8  CKLocTextAccessor_Construct_2  [dead]
//   [ ] 0x35f10  RegisterCKLocTextAccessorClass
//   [ ] 0x35f88  _GLOBAL__I_35f88
//   [ ] 0x35f98  CKLocTextAccessor_Destructor_2
//   [x] 0x35ff0  CKLocTextAccessor_DeleteArray
//   [ ] 0x36098  CKLocTextAccessor_Save
//   [ ] 0x360a0  CKLocTextAccessor_RecursiveRegistration
//   [x] 0x360a8  CKLocTextAccessor_CreateArray
//   [x] 0x36170  CKLocTextAccessor_Create
//   [ ] 0x361c0  CKLocTextAccessor_Destroy
//   [ ] 0x36210  CKLocTextAccessor_DeletingDestructor
//   [ ] 0x36270  CKLocTextAccessor_Destructor
//   [x] 0x362c8  CKLocTextAccessor_Load
//
//   [ ] 0x994518  CKLocTextAccessor_IsKindOfClass  [inline]
//   [x] 0x994540  CKLocTextAccessor_GetClassType  [inline]
//   [x] 0x994548  CKLocTextAccessor_GetClassID  [inline]
#include "k2000/components/CKLocTextAccessor.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// 0x00036170 CKLocTextAccessor_Create, the inlined constructor (0x35ec0 CKLocTextAccessor_Construct is a
// dead copy).
CKLocTextAccessor::CKLocTextAccessor() {
    m_texts.m_pBlock = nullptr;
    m_texts.m_ui32NbElt = 10;
    m_texts.m_ui32NbUsedElt = 0;
    m_pText = nullptr;
}

// 0x000362c8 CKLocTextAccessor_Load
int32_t CKLocTextAccessor::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count <= 1) {  // one text (or none): a single reference
        IKFile_ReadRef(file, &m_pText);
        return 1;
    }
    // The capacity is set to count before the block is allocated (the old block, if any, is not freed).
    m_texts.m_ui32NbElt = count;
    m_texts.m_pBlock =
        static_cast<IKSerializable**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(IKSerializable*))));
    for (uint32_t i = 0; i < count; ++i) {
        // A null slot is pushed (the list grows by 10 when full), then the reference is read into it.
        if (m_texts.m_ui32NbElt == m_texts.m_ui32NbUsedElt) {
            uint32_t capacity = m_texts.m_ui32NbUsedElt + 10;
            uint32_t bytes = capacity * static_cast<uint32_t>(sizeof(IKSerializable*));
            if (capacity == 0) {
                capacity = 10;
                bytes = 10 * static_cast<uint32_t>(sizeof(IKSerializable*));
            }
            m_texts.m_pBlock = static_cast<IKSerializable**>(Mem_ReallocAligned16(m_texts.m_pBlock, bytes));
            m_texts.m_ui32NbElt = capacity;
        }
        m_texts.m_pBlock[m_texts.m_ui32NbUsedElt] = nullptr;
        IKSerializable** slot = &m_texts.m_pBlock[m_texts.m_ui32NbUsedElt++];
        IKFile_ReadRef(file, slot);
    }
    return 1;
}
