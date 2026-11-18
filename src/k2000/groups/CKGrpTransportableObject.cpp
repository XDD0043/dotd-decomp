// CKGrpTransportableObject.cpp - reconstructed original translation unit 0x4a7460-0x4a8688 (GAME_TOC1, main_toc1), 34 functions, 27 live.
// Primary class: CKGrpTransportableObject  key 0xd44  category Group  size 0x3c  vtable 0xb28730
// Other owners: CKHkTransportableObjectSpawner (5), KeyedPtrList (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4a7460  CKGrpTransportableObject_Delete
//   [ ] 0x4a74b0  CKGrpTransportableObject_Construct  [dead]
//   [x] 0x4a7528  CKGrpTransportableObject_vfB8  (header)
//   [ ] 0x4a7530  KStub_Nop_4a7530  [dead]
//   [x] 0x4a7538  KeyedPtrList_FindByKey_maybe
//   [ ] 0x4a75b8  CKGrpTransportableObject_Construct_2  [dead]
//   [x] 0x4a7630  CKGrpTransportableObject_PostLoad  (header)
//   [ ] 0x4a7658  RegisterCKGrpTransportableObjectClass
//   [ ] 0x4a76d0  _GLOBAL__I_4a76d0
//   [ ] 0x4a76e0  CKGrpTransportableObject_LoadEntry_maybe  [dead]
//   [x] 0x4a77c0  CKGrpTransportableObject_DeleteArray
//   [ ] 0x4a7868  CKGrpTransportableObject_FreeEntries_maybe  [dead]
//   [x] 0x4a7940  CKHkTransportableObjectSpawner_TakePooledObject_maybe
//   [x] 0x4a7a18  CKHkTransportableObjectSpawner_ReturnObjectToPool_maybe
//   [ ] 0x4a7b20  FUN_004a7b20  [dead]
//   [x] 0x4a7b80  CKGrpTransportableObject_Update  (empty: the IKBaseGroup default)
//   [x] 0x4a7b88  CKGrpTransportableObject_Pause  (empty: the IKBaseGroup default)
//   [x] 0x4a7b90  CKGrpTransportableObject_Resume  (empty: the IKBaseGroup default)
//   [x] 0x4a7b98  CKGrpTransportableObject_Start  (empty: the IKBaseGroup default)
//   [x] 0x4a7ba0  CKGrpTransportableObject_Stop  (empty: the IKBaseGroup default)
//   [x] 0x4a7ba8  CKHkTransportableObjectSpawner_ActivateObjectOfType_maybe
//   [x] 0x4a7ce0  CKHkTransportableObjectSpawner_ReleaseObject_maybe
//   [ ] 0x4a7e50  CKGrpTransportableObject_Save
//   [x] 0x4a7e78  CKGrpTransportableObject_RecursiveRegistration  (inherited: IKGroup_LevelReset 0x12a68, IKBaseGroup.h)
//   [x] 0x4a7ea0  CKGrpTransportableObject_CreateArray
//   [x] 0x4a7f98  CKGrpTransportableObject_Create
//   [x] 0x4a8028  CKGrpTransportableObject_Destroy
//   [x] 0x4a8138  CKGrpTransportableObject_Destructor
//   [x] 0x4a81b8  CKGrpTransportableObject_LoadEntries_maybe
//   [x] 0x4a8400  CKGrpTransportableObject_Load
//   [ ] 0x4a8508  CKGrpTransportableObject_Destructor_2  [dead]
//   [x] 0x4a8588  CKGrpTransportableObject_DeletingDestructor  (the deleting form of the destructor)
//   [x] 0x4a8610  CKHkTransportableObjectSpawner_Delete  (the Delete factory: DOTD_DECLARE_FACTORIES(CKHkTransportableObjectSpawner))
//   [x] 0x4a8660  CKGrpTransportableObject_CompareNullsLast_maybe  (CKHkTransportableObjectSpawner.cpp)
//
//   [x] 0x9c4f10  CKGrpTransportableObject_GetClassType  [inline]
//   [x] 0x9c4f18  CKGrpTransportableObject_GetClassID  [inline]
//   [ ] 0x9c4f20  CKGrpTransportableObject_vfCC  [inline]
//   [x] 0x9c4f70  CKGrpTransportableObject_vfB0  [inline]  (IKGroup GetMemberListHead)
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
#include "Spyro2008/misc/CKHkS08TransportableBase.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKSector.h"
#include "k2000/memory/KObjectRefList.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGSectorRoot.h"

// The inlined block of the transportables' restarts (spawner, key, carrier): the object's node out of its parent (vt+0x78)
// and under sector 0's root (vt+0x70).
void ReparentToBaseSectorRoot(CSGLeaf* node) {
    if (node->m_pParent != nullptr) node->m_pParent->RemoveChild(node);
    CKSector* base = static_cast<CKSector*>(g_pEngine->m_level->m_vpSectors.m_pBlock[0]);
    base->m_pSectorRoot->AddChild(node);
}

// 0x004a7a18 CKHkTransportableObjectSpawner_ReturnObjectToPool_maybe (on the group, Ghidra's `this` is the group): the
// object hidden (its node's bit 2), told (vt+0x108), back into entry `index`'s pool (SwapIntoActivePartition), its +0x25
// set (vt+0x14c), no owner spawner (+0x28: 0x4abfb8), then vt+0x124.
void CKGrpTransportableObject::ReturnObjectToPool(uint32_t index, IKSerializable* object) {
    CKHkS08TransportableBase* item = static_cast<CKHkS08TransportableBase*>(object);
    CSGLeaf* node = static_cast<CSGLeaf*>(item->m_pKGLObject);
    node->m_sgProperties = node->m_sgProperties | 4u;
    item->Vf108();
    m_vEntries.m_pBlock[index]->m_pList->SwapIntoActivePartition(object);
    item->SetUnk25(1);  // vt+0x14c
    item->SetOwnerSpawner(nullptr);  // 0x004abfb8
    item->Vf124();
}

// 0x004a7ce0 CKHkTransportableObjectSpawner_ReleaseObject_maybe (on the group): the object hidden, back into the pool of
// the entry whose class id (+0x04) is the object's (vt+0x18; none: a null list, BUG(original)), +0x25 set, no owner, then
// vt+0x124.
void CKGrpTransportableObject::ReleaseObject(IKSerializable* object) {
    if (object == nullptr) return;
    CKHkS08TransportableBase* item = static_cast<CKHkS08TransportableBase*>(object);
    CSGLeaf* node = static_cast<CSGLeaf*>(item->m_pKGLObject);
    node->m_sgProperties = node->m_sgProperties | 4u;
    const uint32_t id = static_cast<uint32_t>(item->GetClassID());  // vt+0x18
    KObjectRefList* list = nullptr;
    for (uint32_t i = 0; i < m_vEntries.m_ui32NbUsedElt; ++i) {
        if (m_vEntries.m_pBlock[i]->m_unk04 == id) {
            list = m_vEntries.m_pBlock[i]->m_pList;
            break;
        }
    }
    list->SwapIntoActivePartition(object);
    item->SetUnk25(1);  // vt+0x14c
    item->SetOwnerSpawner(nullptr);
    item->Vf124();
}

// 0x004a7940 CKHkTransportableObjectSpawner_TakePooledObject_maybe (on the group)
IKSerializable* CKGrpTransportableObject::TakePooledObject(uint32_t index) {
    IKSerializable* object = m_vEntries.m_pBlock[index]->m_pList->PopBack();  // 0x00244b90
    if (object != nullptr) {
        CKHkS08TransportableBase* item = static_cast<CKHkS08TransportableBase*>(object);
        item->SetUnk25(0);              // vt+0x14c
        item->SetOwnerSpawner(nullptr);  // 0x004abfb8
        CSGLeaf* node = static_cast<CSGLeaf*>(item->m_pKGLObject);
        node->m_sgProperties &= 0xfffffffbu;
        item->Vf120();
    }
    return object;
}

// 0x004a7538 KeyedPtrList_FindByKey_maybe
KObjectRefList* CKGrpTransportableObject::FindListByKey(uint32_t key) const {
    for (uint32_t i = 0; i < m_vEntries.m_ui32NbUsedElt; ++i) {
        if (m_vEntries.m_pBlock[i]->m_unk04 == key) return m_vEntries.m_pBlock[i]->m_pList;
    }
    return nullptr;
}

// 0x004a8028 CKGrpTransportableObject_Destroy
void CKGrpTransportableObject::Destroy() {
    m_lChilds = nullptr;
    *GetMemberListHead() = nullptr;  // vt+0xb0 0x9c4f70: this + 0x28
    for (uint32_t i = 0; i < m_vEntries.m_ui32NbUsedElt; ++i) {
        KObjectRefList* list = m_vEntries.m_pBlock[i]->m_pList;
        if (list != nullptr) {
            if (list->m_pBlock != nullptr) {
                Mem_FreeAligned16(list->m_pBlock);
                list->m_pBlock = nullptr;
            }
            list->m_pHead = nullptr;
            delete list;
        }
        delete m_vEntries.m_pBlock[i];
    }
}

// 0x004a8138 CKGrpTransportableObject_Destructor
CKGrpTransportableObject::~CKGrpTransportableObject() {
    if (m_vEntries.m_pBlock != nullptr) Mem_FreeAligned16(m_vEntries.m_pBlock);
    m_vEntries.m_ui32NbUsedElt = 0;
    m_vEntries.m_pBlock = nullptr;
}

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


// 0x004a7ba8 CKHkTransportableObjectSpawner_ActivateObjectOfType_maybe (on the group)
IKSerializable* CKGrpTransportableObject::ActivateObjectOfType(uint32_t key) {
    KObjectRefList* list = nullptr;
    for (uint32_t i = 0; i < m_vEntries.m_ui32NbUsedElt; ++i) {
        if (m_vEntries.m_pBlock[i]->m_unk04 == key) {
            list = m_vEntries.m_pBlock[i]->m_pList;
            break;
        }
    }
    IKSerializable* object = list->PopBack();  // 0x00244b90; BUG(original): no entry of that key pops from a null list
    if (object != nullptr) {
        CKHkS08TransportableBase* item = static_cast<CKHkS08TransportableBase*>(object);
        item->SetUnk25(0);               // vt+0x14c
        item->SetOwnerSpawner(nullptr);  // 0x004abfb8
        CSGLeaf* node = static_cast<CSGLeaf*>(item->m_pKGLObject);
        node->m_sgProperties &= 0xfffffffbu;
        item->Vf120();
    }
    return object;
}
