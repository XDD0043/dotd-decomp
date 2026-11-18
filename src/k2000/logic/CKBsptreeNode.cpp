// Reconstructed original translation unit: 0x43948-0x443d8 (GAME_TOC1, main_toc1), 16 functions, 12 live.
// Primary class: CKBsptreeNode  key 0x76cc  category Logic  size 0x4c  vtable 0xb14ca8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x43948  CKBsptreeNode_Delete  (registry factory: DOTD_DECLARE_FACTORIES)
//   [ ] 0x43998  RegisterCKBsptreeNodeClass
//   [ ] 0x43a10  _GLOBAL__I_43a10
//   [ ] 0x43a20  CKBsptreeNode_Construct  [dead]
//   [ ] 0x43aa0  CKBsptreeNode_Construct_2  [dead]
//   [x] 0x43b20  CKBsptreeNode_DeleteArray  (registry factory: DOTD_DECLARE_FACTORIES)
//   [ ] 0x43bc0  CKBsptreeNode_Save
//   [x] 0x43bc8  CKBsptreeNode_RecursiveRegistration  (returns 1: the root's empty slot)
//   [x] 0x43bd0  CKBsptreeNode_Destroy
//   [x] 0x43c90  CKBsptreeNode_Load
//   [x] 0x43f58  CKBsptreeNode_CreateArray  (registry factory: DOTD_DECLARE_FACTORIES (the constructor))
//   [x] 0x44060  CKBsptreeNode_Create  (registry factory: DOTD_DECLARE_FACTORIES (the constructor))
//   [x] 0x440f8  CKBsptreeNode_DeletingDestructor  (C++ deleting destructor)
//   [x] 0x441e8  CKBsptreeNode_Destructor
//   [ ] 0x442d0  CKBsptreeNode_Destructor_2  [dead]
//   [ ] 0x443b8  CKBsptreeNode_ConstructBase_2_maybe  [dead]
//
//   [ ] 0x9957f0  CKBsptreeNode_GetClassType  [inline]
//   [ ] 0x9957f8  CKBsptreeNode_GetClassID  [inline]
//   [ ] 0x995800  CKBsptreeNode_IsKindOfClass  [inline]
#include "k2000/logic/CKBsptreeNode.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// 0x00044450 Vt_b14d00_Load_maybe (k2000/misc/Vt.cpp's unit)
void CKBsptreeNode::Part::Load(IKFile* file, int32_t type) {
    if (type != 0) return;
    ReadU32LEWords(file, m_unk04, 2);
    ReadU32LE(file, &m_unk0c);
    ReadU8(file, &m_unk10);
}

// 0x00044060 CKBsptreeNode_Create (the constructor inlined; 0x00044430 CKBsptreeNode_ConstructBase_maybe for the part)
CKBsptreeNode::CKBsptreeNode() {
    m_part.m_unk10 = 8;
    m_part.m_unk0c = 0;
    for (TVector<uint16_t, 1>& array : m_aUnk28) {
        array.m_pBlock = nullptr;
        array.m_ui32NbElt = 1;
        array.m_ui32NbUsedElt = 0;
    }
}

// 0x000441e8 CKBsptreeNode_Destructor
CKBsptreeNode::~CKBsptreeNode() {
    for (int32_t i = 2; i >= 0; --i) {
        if (m_aUnk28[i].m_pBlock != nullptr) Mem_FreeAligned16(m_aUnk28[i].m_pBlock);  // 0x00052fb8
        m_aUnk28[i].m_pBlock = nullptr;
        m_aUnk28[i].m_ui32NbUsedElt = 0;
    }
}

// 0x00043bd0 CKBsptreeNode_Destroy
void CKBsptreeNode::Destroy() {
    for (TVector<uint16_t, 1>& array : m_aUnk28) {
        if (array.m_pBlock != nullptr) {
            Mem_FreeAligned16(array.m_pBlock);
            array.m_pBlock = nullptr;
        }
        array.m_pBlock = nullptr;
        array.m_ui32NbUsedElt = 0;
    }
}

// 0x00043c90 CKBsptreeNode_Load
int32_t CKBsptreeNode::Load(IKFile* file, int32_t type) {
    if (type != 0) return 1;
    m_part.Load(file, 0);  // 0x00044450
    IKFile_ReadRef(file, &m_unk18);
    IKFile_ReadRef(file, &m_unk1c);
    IKFile_ReadObjectRefArray(file, m_unk20, 2);
    for (TVector<uint16_t, 1>& array : m_aUnk28) {
        uint32_t count = 0;
        ReadU32LE(file, &count);
        if (array.m_ui32NbElt < count) {
            uint32_t capacity = count + 1u;
            uint32_t bytes = capacity * 2u;
            if (capacity == 0) {
                capacity = 1;
                bytes = 2;
            }
            array.m_pBlock = static_cast<uint16_t*>(Mem_ReallocAligned16(array.m_pBlock, bytes));  // 0x00053190
            array.m_ui32NbElt = capacity;
        }
        array.m_ui32NbUsedElt = count;
        ReadRaw(file, array.m_pBlock, count * 2u);
        for (uint32_t i = 0; i < count; ++i) {
            const uint16_t v = array.m_pBlock[i];
            array.m_pBlock[i] = static_cast<uint16_t>((v >> 8) | (v << 8));
        }
    }
    return 1;
}
