// CKHkS08TransportableWeight.h - a transportable weight hook (key 0x3142, vtable 0xb28e28, size 0x1cc).
// Original unit: CKHkS08TransportableWeight.cpp. No XXL2 class. Derives from CKHkS08TransportableKey (its
// Load 0x4b6500 calls CKHkS08TransportableKey_Load first; the class tree's 0x3002 parent is the Key's own
// base). Base of CKHkS08PowerBucket. Field names are placeholders.
#pragma once
#include <cstdint>

#include "Spyro2008/hooks/CKHkS08TransportableKey.h"
#include "k2000/core/Layout.h"

class CKHkS08TransportableWeight : public CKHkS08TransportableKey {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xc5)
    DOTD_DECLARE_FACTORIES(CKHkS08TransportableWeight)

    // 0x004b4a98 (Ghidra CKHkS08PowerBucket_ConstructBase_maybe; it sets this class's vtable 0xb28e28),
    // inlined in 0x004b5808 CKHkS08TransportableWeight_Create: the CKHkS08TransportableKey part only.
    CKHkS08TransportableWeight() {}
    ~CKHkS08TransportableWeight() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004b6500 CKHkS08TransportableWeight_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x004b48c0 CKHkS08TransportableWeight_PostLoad
    void Start() override;  // vt+0x50 0x004b4880 CKHkS08TransportableWeight_Start (C2.2)

    IKSerializable* m_unk130;   // +0x130 reference (LVL010: a CKSoundDictionaryID)
    IKSerializable* m_unk134;   // +0x134 reference
    uint32_t m_unk138;          // +0x138 runtime (PostLoad 0x4b48c0 clears it)
    IKSerializable* m_unk13c;   // +0x13c reference (LVL010: a CKExplosionFxData)
    IKSerializable* m_unk140;   // +0x140 reference (LVL010: a CSGHotSpot)
    IKSerializable* m_unk144;   // +0x144 reference (LVL010: a CSGHotSpot)
    float m_unk148;             // +0x148
    float m_unk14c;             // +0x14c
    uint32_t m_unk150[6];       // +0x150..+0x167 runtime
    float m_unk168;             // +0x168
    float m_unk16c;             // +0x16c
    float m_unk170;             // +0x170
    float m_unk174;             // +0x174
    float m_unk178;             // +0x178
    uint32_t m_unk17c[3];       // +0x17c..+0x187 runtime
    float m_unk188;             // +0x188
    float m_unk18c;             // +0x18c
    uint32_t m_unk190[3];       // +0x190..+0x19b runtime
    float m_unk19c;             // +0x19c
    uint32_t m_unk1a0[4];       // +0x1a0..+0x1af runtime
    IKSerializable* m_unk1b0;   // +0x1b0 reference (LVL010: a CKExplosionFxData)
    uint32_t m_unk1b4[6];       // +0x1b4..+0x1cb runtime
};
DOTD_ASSERT_SIZE(CKHkS08TransportableWeight, 0x1cc);
DOTD_ASSERT_OFFSET(CKHkS08TransportableWeight, m_unk130, 0x130);
DOTD_ASSERT_OFFSET(CKHkS08TransportableWeight, m_unk134, 0x134);
DOTD_ASSERT_OFFSET(CKHkS08TransportableWeight, m_unk13c, 0x13c);
DOTD_ASSERT_OFFSET(CKHkS08TransportableWeight, m_unk140, 0x140);
DOTD_ASSERT_OFFSET(CKHkS08TransportableWeight, m_unk144, 0x144);
DOTD_ASSERT_OFFSET(CKHkS08TransportableWeight, m_unk148, 0x148);
DOTD_ASSERT_OFFSET(CKHkS08TransportableWeight, m_unk14c, 0x14c);
DOTD_ASSERT_OFFSET(CKHkS08TransportableWeight, m_unk168, 0x168);
DOTD_ASSERT_OFFSET(CKHkS08TransportableWeight, m_unk16c, 0x16c);
DOTD_ASSERT_OFFSET(CKHkS08TransportableWeight, m_unk170, 0x170);
DOTD_ASSERT_OFFSET(CKHkS08TransportableWeight, m_unk174, 0x174);
DOTD_ASSERT_OFFSET(CKHkS08TransportableWeight, m_unk178, 0x178);
DOTD_ASSERT_OFFSET(CKHkS08TransportableWeight, m_unk188, 0x188);
DOTD_ASSERT_OFFSET(CKHkS08TransportableWeight, m_unk18c, 0x18c);
DOTD_ASSERT_OFFSET(CKHkS08TransportableWeight, m_unk19c, 0x19c);
DOTD_ASSERT_OFFSET(CKHkS08TransportableWeight, m_unk1b0, 0x1b0);
