// CKGrpTransportableObject.h - the group of objects the hero can carry (key 0xd44, vtable 0xb28730, size
// 0x3c). Original unit: CKGrpTransportableObject.cpp. No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/groups/IKBaseGroup.h"
#include "k2000/memory/KObjectRefList.h"
#include "k2000/util/TVector.h"

class CKGrpTransportableObject : public IKGroup<IKHook> {
public:
    DOTD_CLASS_KEY(kCategoryGroup, 0x35)
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
    // 0x004a81b8 CKGrpTransportableObject_LoadEntries_maybe
    void LoadEntries(IKFile* file, int32_t type);

    TVector<Entry*, 1> m_vEntries;  // +0x2c
    IKSerializable* m_pUnk38;       // +0x38 reference
};
DOTD_ASSERT_SIZE(CKGrpTransportableObject::Entry, 0x8);
DOTD_ASSERT_SIZE(CKGrpTransportableObject, 0x3c);
DOTD_ASSERT_OFFSET(CKGrpTransportableObject, m_vEntries, 0x2c);
DOTD_ASSERT_OFFSET(CKGrpTransportableObject, m_pUnk38, 0x38);
