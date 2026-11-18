// CKGrpTransportableObject.h - the group of objects the hero can carry (key 0xd44, vtable 0xb28730, size
// 0x3c). Original unit: CKGrpTransportableObject.cpp. No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/groups/IKBaseGroup.h"
#include "k2000/memory/KObjectRefList.h"
#include "k2000/util/TVector.h"

class CSGLeaf;
// The transportables' restarts' inlined block (CKGrpTransportableObject.cpp): the node under sector 0's root.
void ReparentToBaseSectorRoot(CSGLeaf* node);

class CKGrpTransportableObject : public IKGroup<IKHook> {
public:
    DOTD_CLASS_KEY(kCategoryGroup, 0x35)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c5150
        return key == 0xd44 || key == 0x17e || key == 0x4 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKGrpTransportableObject)

    // OperatorNew(8), zeroed: a reference list (OperatorNew(0x10), zeroed, type 0 only) and a word.
    struct Entry {
        KObjectRefList* m_pList;  // +0x00
        uint32_t m_unk04;         // +0x04 byte-swapped (LVL010: 0xc2, 0xc3, 0xc5)
    };

    // 0x004a7f98 CKGrpTransportableObject_Create (the constructor 0x4a74b0 inlined): null, 1, 0.
    CKGrpTransportableObject() {
        m_vEntries.m_pBlock = nullptr;
        m_vEntries.m_ui32NbElt = 1;
        m_vEntries.m_ui32NbUsedElt = 0;
    }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004a8400 CKGrpTransportableObject_Load
    // vt+0x30 0x004a7630 CKGrpTransportableObject_PostLoad: IKLife_PostLoad 0x19f68, then 1.
    int32_t PostLoad(int32_t type) override {
        PostLoadLife(type);
        return 1;
    }
    // 0x004a81b8 CKGrpTransportableObject_LoadEntries_maybe
    void LoadEntries(IKFile* file, int32_t type);
    // 0x004a7a18 / 0x004a7ce0 (Ghidra CKHkTransportableObjectSpawner_ReturnObjectToPool_maybe / _ReleaseObject_maybe):
    // a transportable back into its entry's pool (by index, or by its class id).
    void ReturnObjectToPool(uint32_t index, IKSerializable* object);
    void ReleaseObject(IKSerializable* object);
    // 0x004a7940 CKHkTransportableObjectSpawner_TakePooledObject_maybe (on the group): the last pooled object of entry
    // `index` (PtrArray_PopBack_maybe 0x244b90), out of the pool (vt+0x14c with 0), no owner spawner, shown (its node's
    // bit 2 cleared), then vt+0x120. Null when the pool is empty.
    IKSerializable* TakePooledObject(uint32_t index);
    // 0x004a7538 KeyedPtrList_FindByKey_maybe: the list of the entry whose word (+0x04) is `key`; null when none.
    KObjectRefList* FindListByKey(uint32_t key) const;
    // 0x004a7ba8 CKHkTransportableObjectSpawner_ActivateObjectOfType_maybe (on the group; the crystal key, emitter and
    // receiver call it): the last pooled object of the entry whose class id (+0x04) is `key` taken (PopBack), its +0x25
    // cleared (vt+0x14c), no owner spawner, its node shown (bit 2 cleared), then vt+0x120; null when the pool is empty.
    IKSerializable* ActivateObjectOfType(uint32_t key);
    // vt+0x10 0x004a8028 CKGrpTransportableObject_Destroy: no child groups (+0x18), no members (vt+0xb0's head), each entry's
    // list (its block freed) and the entry deleted.
    void Destroy() override;
    // 0x004a8138 CKGrpTransportableObject_Destructor: the entry block freed (Mem_FreeAligned16), its count and pointer
    // cleared, then the base vtables (nothing else).
    ~CKGrpTransportableObject() override;

    TVector<Entry*, 1> m_vEntries;  // +0x2c
    IKSerializable* m_pUnk38;       // +0x38 reference
};
DOTD_ASSERT_SIZE(CKGrpTransportableObject::Entry, 0x8);
DOTD_ASSERT_SIZE(CKGrpTransportableObject, 0x3c);
DOTD_ASSERT_OFFSET(CKGrpTransportableObject, m_vEntries, 0x2c);
DOTD_ASSERT_OFFSET(CKGrpTransportableObject, m_pUnk38, 0x38);
