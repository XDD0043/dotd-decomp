// CKBlurFxData.h - the data of a blur effect (key 0x28c, vtable 0xb2dd18, size 0x20). Original unit:
// CKBlurFxData.cpp; Create (0x56ef20) sits in another unit. Its node is CKBlurNodeFx (0x30c). Not in XXL2;
// names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/IKFxData.h"

class CKBlurFxData : public IKFxData {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xa)
    DOTD_DECLARE_FACTORIES(CKBlurFxData)

    // Two byte-swapped words. The PS3 allocates the array with operator new[] and a 4-byte count cookie.
    struct Key {
        float m_unk00;
        float m_unk04;
    };

    CKBlurFxData() {}  // inlined in 0x0056ef20 CKBlurFxData_Create: the vtables only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005717e0 CKBlurFxData_Load
    // vt+0x30 PostLoad 0x5713c0 (stays the default in C2.1).
    uint32_t GetAssociatedFxClassIdentifier() override { return 0x30c; }  // vt+0x54 0x5712a0

    IKSerializable* m_unk08;  // +0x08 an object reference (LVL010: class 0x28d)
    uint8_t m_unk0c;          // +0x0c
    uint8_t m_pad0d[3];
    float m_unk10;            // +0x10
    Key* m_unk14;             // +0x14 new[] of m_unk18 keys
    uint8_t m_unk18;          // +0x18 the number of keys (one byte)
    uint8_t m_pad19[3];
    uint32_t m_unk1c;         // +0x1c Load sets 0 (every type)
};
static_assert(CKBlurFxData::kClassKey == 0x28c, "key");
DOTD_ASSERT_SIZE(CKBlurFxData::Key, 0x8);
DOTD_ASSERT_SIZE(CKBlurFxData, 0x20);
DOTD_ASSERT_OFFSET(CKBlurFxData, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(CKBlurFxData, m_unk0c, 0x0c);
DOTD_ASSERT_OFFSET(CKBlurFxData, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(CKBlurFxData, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKBlurFxData, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CKBlurFxData, m_unk1c, 0x1c);
