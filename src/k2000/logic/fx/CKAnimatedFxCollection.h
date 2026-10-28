// CKAnimatedFxCollection.h - a group of animated effects (key 0xa08c, vtable 0xb30128, size 0x40). Original
// unit: CKAnimatedFxCollection.cpp (0x5cc298-0x5cdb00). Derived straight from IKSerializable. Not in XXL2;
// names ours. The three lists are the engine's TVector growing by one element.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class CKAnimatedFxCollection : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x282)
    DOTD_DECLARE_FACTORIES(CKAnimatedFxCollection)

    // Four object references read one after the other (16 bytes on the PS3).
    struct Entry {
        IKSerializable* m_unk00;
        IKSerializable* m_unk04;
        IKSerializable* m_unk08;
        IKSerializable* m_unk0c;
    };

    CKAnimatedFxCollection();  // inlined in 0x005ccb68 CKAnimatedFxCollection_Create (also 0x5cc2e8)

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005cd510 CKAnimatedFxCollection_Load
    // vt+0x30 PostLoad 0x5ccf58 (stays the default in C2.1).

    uint8_t m_unk04;                    // +0x04
    uint8_t m_pad05[3];
    uint32_t m_unk08;                   // +0x08 the number of entries in +0x18 (when +0x24 is set)
    TVector<IKSerializable*, 1> m_unk0c;  // +0x0c object references (LVL010: CKAnimatedFx)
    TVector<Entry, 1> m_unk18;          // +0x18
    uint8_t m_unk24;                    // +0x24 non-zero: the +0x18 entries follow in the file
    uint8_t m_pad25[3];
    uint32_t m_unk28;                   // +0x28 Load (type 0) sets 0
    TVector<IKSerializable*, 1> m_unk2c;  // +0x2c not read by Load
    uint32_t m_unk38;                   // +0x38 not set
    uint32_t m_unk3c;                   // +0x3c not set
};
static_assert(CKAnimatedFxCollection::kClassKey == 0xa08c, "key");
DOTD_ASSERT_SIZE(CKAnimatedFxCollection::Entry, 0x10);
DOTD_ASSERT_SIZE(CKAnimatedFxCollection, 0x40);
DOTD_ASSERT_OFFSET(CKAnimatedFxCollection, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(CKAnimatedFxCollection, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(CKAnimatedFxCollection, m_unk0c, 0x0c);
DOTD_ASSERT_OFFSET(CKAnimatedFxCollection, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CKAnimatedFxCollection, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKAnimatedFxCollection, m_unk28, 0x28);
DOTD_ASSERT_OFFSET(CKAnimatedFxCollection, m_unk2c, 0x2c);
