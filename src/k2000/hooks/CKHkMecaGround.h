// CKHkMecaGround.h - a mechanism's ground hook (key 0x2dc2, vtable 0xb2a568, size 0x2c). Original unit:
// CKHkMecaGround.cpp. No XXL2 class.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkActorBase.h"

class CKHkMecaGround : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xb7)
    DOTD_DECLARE_FACTORIES(CKHkMecaGround)

    // A node of the +0x28 reference list (8 bytes, FreeListPool at 0x00ceaa20 in the original).
    struct RefNode {
        IKSerializable* m_pObject;  // +0x00
        RefNode* m_pNext;           // +0x04
    };

    // 0x004e12f8 CKHkMecaGround_Create (Construct 0x4e0fe0): the CKHkActorBase defaults, then +0x28 = 0.
    CKHkMecaGround() { m_pRefList = nullptr; }
    ~CKHkMecaGround() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004e1358 CKHkMecaGround_Load

    IKSerializable* m_unk20;  // +0x20
    uint32_t m_unk24;         // +0x24 runtime (not set by Create or Load)
    RefNode* m_pRefList;      // +0x28 the list head: Load pushes each read reference at the head
};
DOTD_ASSERT_SIZE(CKHkMecaGround, 0x2c);
DOTD_ASSERT_OFFSET(CKHkMecaGround, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkMecaGround, m_pRefList, 0x28);
