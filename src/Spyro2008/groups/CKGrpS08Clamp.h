// CKGrpS08Clamp.h - the clamp group (key 0xc04, vtable 0xb27fe0, size 0x4c). Original unit:
// CKGrpS08Clamp.cpp. No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/groups/IKBaseGroup.h"
#include "k2000/memory/KObjectRefList.h"

class CKGrpS08Clamp : public IKGroup<IKHook> {
public:
    DOTD_CLASS_KEY(kCategoryGroup, 0x30)
    DOTD_DECLARE_FACTORIES(CKGrpS08Clamp)

    // 0x00491f78 CKGrpS08Clamp_Create (the constructor 0x491748 inlined): the list zeroed.
    CKGrpS08Clamp() {
        m_list.m_pBlock = nullptr;
        m_list.m_pHead = nullptr;
        m_list.m_ui32Count = 0;
        m_list.m_ui32Count2 = 0;
    }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00492170 CKGrpS08Clamp_Load
    void Start() override;  // vt+0x50 0x00491cf0 CKGrpS08Clamp_Start (C2.2)

    KObjectRefList m_list;     // +0x2c (LVL010: hook refs of key 0x2c82)
    uint32_t m_unk3c;          // +0x3c not set by the constructor or the Load
    IKSerializable* m_pUnk40;  // +0x40 reference
    IKSerializable* m_pUnk44;  // +0x44 reference
    IKSerializable* m_pUnk48;  // +0x48 reference
};
DOTD_ASSERT_SIZE(CKGrpS08Clamp, 0x4c);
DOTD_ASSERT_OFFSET(CKGrpS08Clamp, m_list, 0x2c);
DOTD_ASSERT_OFFSET(CKGrpS08Clamp, m_pUnk40, 0x40);
DOTD_ASSERT_OFFSET(CKGrpS08Clamp, m_pUnk48, 0x48);
