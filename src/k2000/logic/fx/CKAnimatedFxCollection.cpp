// CKAnimatedFxCollection.cpp - reconstructed original translation unit 0x5cc298-0x5cdee0 (GAME_TOC2, main_toc2), 25 functions, 20 live.
// Primary class: CKAnimatedFxCollection  key 0xa08c  category Logic  size ?  vtable 0xb30128
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5cc298  CKAnimatedFxCollection_Delete
//   [ ] 0x5cc2e8  CKAnimatedFxCollection_Construct  [dead]
//   [ ] 0x5cc330  CKAnimatedFxCollection_GetEntryPtr_maybe  [dead]
//   [ ] 0x5cc378  CKAnimatedFxCollection_Construct_2  [dead]
//   [ ] 0x5cc3c0  RegisterCKAnimatedFxCollectionClass
//   [ ] 0x5cc438  _GLOBAL__I_5cc438
//   [ ] 0x5cc448  CKAnimatedFxCollection_InitActiveFlagArray_maybe  [dead]
//   [ ] 0x5cc528  CKAnimatedFxCollection_Play
//   [x] 0x5cc750  CKAnimatedFxCollection_DeleteArray
//   [ ] 0x5cc7f0  CKAnimatedFxCollection_SetOrientation_maybe
//   [ ] 0x5cc8c8  CKAnimatedFxCollection_SetPosition
//   [ ] 0x5cc990  CKAnimatedFxCollection_Stop
//   [ ] 0x5cca80  CKAnimatedFxCollection_SetBasisFromRightUp_maybe  [dead]
//   [ ] 0x5ccb58  CKAnimatedFxCollection_RecursiveRegistration
//   [ ] 0x5ccb60  CKAnimatedFxCollection_Destroy
//   [x] 0x5ccb68  CKAnimatedFxCollection_Create
//   [x] 0x5ccbd8  CKAnimatedFxCollection_CreateArray
//   [ ] 0x5cccb0  CKAnimatedFxCollection_Update_maybe
//   [ ] 0x5ccf58  CKAnimatedFxCollection_PostLoad
//   [ ] 0x5cd0a8  CKAnimatedFxCollection_PlayWithOwnRigs_maybe
//   [ ] 0x5cd2d0  CKAnimatedFxCollection_Destructor
//   [ ] 0x5cd388  CKAnimatedFxCollection_Destructor_2
//   [ ] 0x5cd440  CKAnimatedFxCollection_DeletingDestructor
//   [x] 0x5cd510  CKAnimatedFxCollection_Load
//   [ ] 0x5cda30  CKAnimatedFxCollection_Save
//
//   [x] 0x9cd648  CKAnimatedFxCollection_GetClassType  [inline]
//   [x] 0x9cd650  CKAnimatedFxCollection_GetClassID  [inline]
//   [ ] 0x9cd658  CKAnimatedFxCollection_IsKindOfClass  [inline]
#include "k2000/logic/fx/CKAnimatedFxCollection.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// 0x005ccb68 CKAnimatedFxCollection_Create, the inlined constructor, in its store order.
CKAnimatedFxCollection::CKAnimatedFxCollection() {
    m_unk0c.m_pBlock = nullptr;
    m_unk0c.m_ui32NbElt = 1;
    m_unk0c.m_ui32NbUsedElt = 0;
    m_unk18.m_ui32NbElt = 1;
    m_unk18.m_pBlock = nullptr;
    m_unk18.m_ui32NbUsedElt = 0;
    m_unk2c.m_ui32NbElt = 1;
    m_unk2c.m_ui32NbUsedElt = 0;
    m_unk2c.m_pBlock = nullptr;
}

// 0x005cd510 CKAnimatedFxCollection_Load
int32_t CKAnimatedFxCollection::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    m_unk28 = 0;
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count == 0) {
        // The length is left as it was.
        m_unk0c.m_ui32NbElt = 1;
        m_unk0c.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(IKSerializable*))));
    } else {
        m_unk0c.m_ui32NbElt = count;
        m_unk0c.m_pBlock =
            static_cast<IKSerializable**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(IKSerializable*))));
        if (m_unk0c.m_ui32NbElt < count) {  // never true: the capacity was just set to count
            uint32_t capacity = count + 1;
            uint32_t bytes = capacity * static_cast<uint32_t>(sizeof(IKSerializable*));
            if (capacity == 0) {
                capacity = 1;
                bytes = static_cast<uint32_t>(sizeof(IKSerializable*));
            }
            m_unk0c.m_pBlock = static_cast<IKSerializable**>(Mem_ReallocAligned16(m_unk0c.m_pBlock, bytes));
            m_unk0c.m_ui32NbElt = capacity;
        }
        m_unk0c.m_ui32NbUsedElt = count;
    }
    for (uint32_t i = 0; i < count; ++i) IKFile_ReadRef(file, &m_unk0c.m_pBlock[i]);
    ReadU32LE(file, &m_unk08);
    ReadU8(file, &m_unk04);
    ReadU8(file, &m_unk24);
    if (m_unk24 != 0) {
        m_unk18.m_ui32NbElt = 1;
        m_unk18.m_pBlock = static_cast<Entry*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(Entry))));
        const uint32_t n = m_unk08;
        if (m_unk18.m_ui32NbElt < n) {
            uint32_t capacity = n + 1;
            uint32_t bytes = capacity * static_cast<uint32_t>(sizeof(Entry));
            if (capacity == 0) {
                capacity = 1;
                bytes = static_cast<uint32_t>(sizeof(Entry));
            }
            m_unk18.m_pBlock = static_cast<Entry*>(Mem_ReallocAligned16(m_unk18.m_pBlock, bytes));
            m_unk18.m_ui32NbElt = capacity;
        }
        m_unk18.m_ui32NbUsedElt = n;
        for (uint32_t i = 0; i < m_unk08; ++i) {
            Entry& e = m_unk18.m_pBlock[i];
            IKFile_ReadRef(file, &e.m_unk00);
            IKFile_ReadRef(file, &e.m_unk04);
            IKFile_ReadRef(file, &e.m_unk08);
            IKFile_ReadRef(file, &e.m_unk0c);
        }
    }
    return 1;
}
