// CKGrpTransportableObject.cpp - reconstructed original translation unit 0x4a7460-0x4a8688 (GAME_TOC1, main_toc1), 34 functions, 27 live.
// Primary class: CKGrpTransportableObject  key 0xd44  category Group  size 0x3c  vtable 0xb28730
// Other owners: CKHkTransportableObjectSpawner (5), KeyedPtrList (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4a7460  CKGrpTransportableObject_Delete
//   [ ] 0x4a74b0  CKGrpTransportableObject_Construct  [dead]
//   [ ] 0x4a7528  CKGrpTransportableObject_vfB8
//   [ ] 0x4a7530  KStub_Nop_4a7530  [dead]
//   [ ] 0x4a7538  KeyedPtrList_FindByKey_maybe
//   [ ] 0x4a75b8  CKGrpTransportableObject_Construct_2  [dead]
//   [ ] 0x4a7630  CKGrpTransportableObject_PostLoad
//   [ ] 0x4a7658  RegisterCKGrpTransportableObjectClass
//   [ ] 0x4a76d0  _GLOBAL__I_4a76d0
//   [ ] 0x4a76e0  CKGrpTransportableObject_LoadEntry_maybe  [dead]
//   [x] 0x4a77c0  CKGrpTransportableObject_DeleteArray
//   [ ] 0x4a7868  CKGrpTransportableObject_FreeEntries_maybe  [dead]
//   [ ] 0x4a7940  CKHkTransportableObjectSpawner_TakePooledObject_maybe
//   [ ] 0x4a7a18  CKHkTransportableObjectSpawner_ReturnObjectToPool_maybe
//   [ ] 0x4a7b20  FUN_004a7b20  [dead]
//   [ ] 0x4a7b80  CKGrpTransportableObject_Update
//   [ ] 0x4a7b88  CKGrpTransportableObject_Pause
//   [ ] 0x4a7b90  CKGrpTransportableObject_Resume
//   [ ] 0x4a7b98  CKGrpTransportableObject_Start
//   [ ] 0x4a7ba0  CKGrpTransportableObject_Stop
//   [ ] 0x4a7ba8  CKHkTransportableObjectSpawner_ActivateObjectOfType_maybe
//   [ ] 0x4a7ce0  CKHkTransportableObjectSpawner_ReleaseObject_maybe
//   [ ] 0x4a7e50  CKGrpTransportableObject_Save
//   [ ] 0x4a7e78  CKGrpTransportableObject_RecursiveRegistration
//   [x] 0x4a7ea0  CKGrpTransportableObject_CreateArray
//   [x] 0x4a7f98  CKGrpTransportableObject_Create
//   [ ] 0x4a8028  CKGrpTransportableObject_Destroy
//   [ ] 0x4a8138  CKGrpTransportableObject_Destructor
//   [x] 0x4a81b8  CKGrpTransportableObject_LoadEntries_maybe
//   [x] 0x4a8400  CKGrpTransportableObject_Load
//   [ ] 0x4a8508  CKGrpTransportableObject_Destructor_2  [dead]
//   [ ] 0x4a8588  CKGrpTransportableObject_DeletingDestructor
//   [ ] 0x4a8610  CKHkTransportableObjectSpawner_Delete
//   [ ] 0x4a8660  CKGrpTransportableObject_CompareNullsLast_maybe
//
//   [x] 0x9c4f10  CKGrpTransportableObject_GetClassType  [inline]
//   [x] 0x9c4f18  CKGrpTransportableObject_GetClassID  [inline]
//   [ ] 0x9c4f20  CKGrpTransportableObject_vfCC  [inline]
//   [ ] 0x9c4f70  CKGrpTransportableObject_vfB0  [inline]
//   [ ] 0x9c4f80  CKGrpTransportableObject_vfB4  [inline]
//   [ ] 0x9c4f90  CKGrpTransportableObject_vfBC  [inline]
//   [ ] 0x9c5038  CKGrpTransportableObject_vfE0  [inline]
//   [ ] 0x9c5040  CKGrpTransportableObject_vfE4  [inline]
//   [ ] 0x9c5048  CKGrpTransportableObject_vfE8  [inline]
//   [ ] 0x9c5050  CKGrpTransportableObject_vfDC  [inline]
//   [ ] 0x9c5110  CKGrpTransportableObject_vfD8  [inline]
//   [ ] 0x9c5150  CKGrpTransportableObject_IsKindOfClass  [inline]
#include "k2000/groups/CKGrpTransportableObject.h"

#include "k2000/memory/Mem.h"

// 0x004a81b8 CKGrpTransportableObject_LoadEntries_maybe. A new one-element block (the old one is not freed,
// the count is left alone), then per entry a zeroed entry; for type 0 its list and word are read; then it
// is pushed (the vector grows by 1).
void CKGrpTransportableObject::LoadEntries(IKFile* file, int32_t type) {
    uint32_t count = 0;
    ReadU32LE(file, &count);
    m_vEntries.m_ui32NbElt = 1;
    m_vEntries.m_pBlock = static_cast<Entry**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(Entry*))));
    for (uint32_t i = 0; i < count; ++i) {
        Entry* entry = new Entry;  // OperatorNew(8)
        entry->m_pList = nullptr;
        entry->m_unk04 = 0;
        if (type == K_LEVEL_PLATEFORMS) {
            KObjectRefList* list = new KObjectRefList;  // OperatorNew(0x10)
            list->m_ui32Count = 0;
            list->m_ui32Count2 = 0;
            list->m_pBlock = nullptr;
            list->m_pHead = nullptr;
            entry->m_pList = list;
            list->Load(file, K_LEVEL_PLATEFORMS);
            ReadU32LE(file, &entry->m_unk04);
        }
        if (m_vEntries.m_ui32NbElt == m_vEntries.m_ui32NbUsedElt) {
            uint32_t capacity = m_vEntries.m_ui32NbUsedElt + 1u;
            if (capacity == 0) capacity = 1;
            m_vEntries.m_pBlock = static_cast<Entry**>(
                Mem_ReallocAligned16(m_vEntries.m_pBlock, capacity * static_cast<uint32_t>(sizeof(Entry*))));
            m_vEntries.m_ui32NbElt = capacity;
        }
        m_vEntries.m_pBlock[m_vEntries.m_ui32NbUsedElt] = entry;
        ++m_vEntries.m_ui32NbUsedElt;
    }
}

// 0x004a8400 CKGrpTransportableObject_Load
int32_t CKGrpTransportableObject::Load(IKFile* file, int32_t type) {
    GroupBasicLoad(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    LoadEntries(file, K_LEVEL_PLATEFORMS);
    IKFile_ReadRef(file, &m_pUnk38);
    return 1;
}

