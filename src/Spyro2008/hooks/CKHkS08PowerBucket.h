// CKHkS08PowerBucket.h - a power bucket hook (key 0x30c2, vtable 0xb29c50, size 0x20c). Original unit:
// CKHkS08PowerBucket.cpp. No XXL2 class. Derives from CKHkS08TransportableWeight (its Load 0x4d4018 calls
// CKHkS08TransportableWeight_Load first). Field names are placeholders.
#pragma once
#include <cstdint>

#include "Spyro2008/hooks/CKHkS08TransportableWeight.h"
#include "k2000/core/Layout.h"

class CKHkS08PowerBucket : public CKHkS08TransportableWeight {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xc3)
    DOTD_DECLARE_FACTORIES(CKHkS08PowerBucket)

    // 0x004d3fc0 CKHkS08PowerBucket_Create: the CKHkS08TransportableWeight constructor (0x4b4a98), then
    // this vtable; nothing of its own.
    CKHkS08PowerBucket() {}
    ~CKHkS08PowerBucket() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004d4018 CKHkS08PowerBucket_Load

    // +0x1cc reference (LVL040: a CSGHotSpot). PostLoad 0x4d3670 stores it at +0x14 of the +0x1e0 object
    // (and clears that object's +0x10) when it is set.
    IKSerializable* m_unk1cc;
    IKSerializable* m_unk1d0;   // +0x1d0 reference (LVL040: a CKSoundDictionaryID)
    IKSerializable* m_unk1d4;   // +0x1d4 reference (LVL040: a CKExplosionFxData)
    IKSerializable* m_unk1d8;   // +0x1d8 reference
    uint32_t m_unk1dc;          // +0x1dc (LVL040: 0)
    IKSerializable* m_unk1e0;   // +0x1e0 reference
    uint32_t m_unk1e4[2];       // +0x1e4 runtime
    float m_unk1ec;             // +0x1ec
    uint32_t m_unk1f0;          // +0x1f0 runtime
    float m_unk1f4;             // +0x1f4
    float m_unk1f8;             // +0x1f8
    uint32_t m_unk1fc[4];       // +0x1fc..+0x20b runtime
};
DOTD_ASSERT_SIZE(CKHkS08PowerBucket, 0x20c);
DOTD_ASSERT_OFFSET(CKHkS08PowerBucket, m_unk1cc, 0x1cc);
DOTD_ASSERT_OFFSET(CKHkS08PowerBucket, m_unk1d0, 0x1d0);
DOTD_ASSERT_OFFSET(CKHkS08PowerBucket, m_unk1d4, 0x1d4);
DOTD_ASSERT_OFFSET(CKHkS08PowerBucket, m_unk1d8, 0x1d8);
DOTD_ASSERT_OFFSET(CKHkS08PowerBucket, m_unk1dc, 0x1dc);
DOTD_ASSERT_OFFSET(CKHkS08PowerBucket, m_unk1e0, 0x1e0);
DOTD_ASSERT_OFFSET(CKHkS08PowerBucket, m_unk1ec, 0x1ec);
DOTD_ASSERT_OFFSET(CKHkS08PowerBucket, m_unk1f4, 0x1f4);
DOTD_ASSERT_OFFSET(CKHkS08PowerBucket, m_unk1f8, 0x1f8);
