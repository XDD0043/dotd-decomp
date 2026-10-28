// CKMarkedFX.h - effects fired on animation marks (key 0xab4c, vtable 0xb301e0, size 0x2c). Original unit:
// CKMarkedFX.cpp (0x5ceb68-0x5d1700). Derived straight from IKSerializable. Not in XXL2; names ours.
//
// Two lists of heap records, each a TVector growing by one: FX entries (+0x10), each with its mark records,
// and channel tables (+0x1c), each with its channel entries. The record layouts come from their Load
// helpers (0x5d0a20, 0x5d0bb8, 0x5d0da8, 0x5d0f28); no constructors are called for them.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class CKMarkedFX : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2ad)
    DOTD_DECLARE_FACTORIES(CKMarkedFX)

    // operator new(0x10), not initialised.
    struct MarkRecord {
        uint32_t m_unk00;          // +0x00
        uint32_t m_unk04;          // +0x04 read last
        IKSerializable* m_unk08;   // +0x08
        IKSerializable* m_unk0c;   // +0x0c
        // 0x005d0a20 CKMarkedFX_LoadFxMarkRecord_maybe (the owner is passed too and not used)
        void Load(IKFile* file, int32_t type);
    };
    // operator new(0x10); the caller sets +0x08 = 1, +0x04 = 0, +0x0c = 0 before Load.
    struct FxEntry {
        IKSerializable* m_unk00;              // +0x00
        TVector<MarkRecord*, 1> m_marks;      // +0x04
        // 0x005d0bb8 CKMarkedFX_LoadFxEntry_maybe
        void Load(IKFile* file, int32_t type, CKMarkedFX* owner);
    };
    // operator new(0x14), not initialised.
    struct ChannelEntry {
        uint32_t m_unk00;          // +0x00 not read
        uint32_t m_unk04;          // +0x04
        uint32_t m_unk08;          // +0x08 read after +0x0c
        IKSerializable* m_unk0c;   // +0x0c
        uint8_t m_unk10;           // +0x10
        uint8_t m_pad11[3];
        // 0x005d0da8 CKMarkedFX_LoadChannelEntry_maybe (the owner is passed too and not used)
        void Load(IKFile* file, int32_t type);
    };
    // operator new(0x10); the caller sets +0x08 = 1, +0x04 = 0, +0x0c = 0 before Load.
    struct ChannelTable {
        IKSerializable* m_unk00;              // +0x00
        TVector<ChannelEntry*, 1> m_entries;  // +0x04
        // 0x005d0f28 CKMarkedFX_LoadChannelTable_maybe
        void Load(IKFile* file, int32_t type, CKMarkedFX* owner);
    };

    CKMarkedFX();  // inlined in 0x005cf5a8 CKMarkedFX_Create (also 0x5cebb8)

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005d1118 CKMarkedFX_Load
    // vt+0x30 PostLoad 0x5cf268 (stays the default in C2.1).

    IKSerializable* m_unk04;                  // +0x04 an object reference (read first)
    IKSerializable* m_unk08;                  // +0x08 an object reference
    IKSerializable* m_unk0c;                  // +0x0c an object reference (read last)
    TVector<FxEntry*, 1> m_fxEntries;         // +0x10
    TVector<ChannelTable*, 1> m_channels;     // +0x1c
    uint32_t m_unk28;                         // +0x28 not set by the constructor or Load
};
static_assert(CKMarkedFX::kClassKey == 0xab4c, "key");
DOTD_ASSERT_SIZE(CKMarkedFX::MarkRecord, 0x10);
DOTD_ASSERT_SIZE(CKMarkedFX::FxEntry, 0x10);
DOTD_ASSERT_SIZE(CKMarkedFX::ChannelEntry, 0x14);
DOTD_ASSERT_SIZE(CKMarkedFX::ChannelTable, 0x10);
DOTD_ASSERT_SIZE(CKMarkedFX, 0x2c);
DOTD_ASSERT_OFFSET(CKMarkedFX, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(CKMarkedFX, m_unk0c, 0x0c);
DOTD_ASSERT_OFFSET(CKMarkedFX, m_fxEntries, 0x10);
DOTD_ASSERT_OFFSET(CKMarkedFX, m_channels, 0x1c);
