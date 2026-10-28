// CKHkS08TransportableKey.h - a transportable key hook (key 0x3082, vtable 0xb28c08, size 0x130).
// Original unit: CKHkS08TransportableKey.cpp (0x4ac580-0x4b08d8). No XXL2 class. Base of
// CKHkS08TransportableWeight. Field names are placeholders (C2.1 ports the constructor and Load only).
#pragma once
#include <cstdint>

#include "Spyro2008/misc/CKHkS08TransportableBase.h"
#include "k2000/core/Layout.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/math/CMatrix34.h"

class CKHkS08TransportableKey : public CKHkS08TransportableBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xc2)
    DOTD_DECLARE_FACTORIES(CKHkS08TransportableKey)

    // 0x004ad128 (Ghidra CKHkS08TransportableWeight_ConstructBase_maybe; it sets this class's vtable
    // 0xb28c08), inlined in 0x004aebf8 CKHkS08TransportableKey_Create: the ground-contact defaults at
    // +0x4c (no CGroundContactDatasIn before it: +0x44 is a loaded reference) and +0x114/+0x115 = 0xff.
    CKHkS08TransportableKey() {
        m_unk115 = 0xff;
        m_unk114 = 0xff;
    }
    ~CKHkS08TransportableKey() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004aeee8 CKHkS08TransportableKey_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x004acfe0 CKHkS08TransportableKey_PostLoad
    void Start() override;  // vt+0x50 0x004af358 CKHkS08TransportableKey_Start (C2.2)
    // The state engine's handler signature (clock, phase 0 tick / 1 enter / 2 leave, the other state) -> next state.
    using StateFn = uint8_t (CKHkS08TransportableKey::*)(IKTime* clock, int32_t phase, uint8_t other);
    // A handler pair of the table at +0x118 (descriptor, adjust) called natively; not ported: the state as given.
    uint8_t CallState(const uint32_t pair[2], IKTime* clock, int32_t phase, uint8_t other);

    // +0x24..+0x33 runtime: now CKHkS08TransportableBase's m_unk24..m_unk30 (Start writes +0x25 and +0x28).
    IKSerializable* m_unk34;                   // +0x34 reference (LVL010: a CSGHotSpot or null)
    IKSerializable* m_unk38;                   // +0x38 reference (LVL010/LVL040: a CNode or null)
    IKSerializable* m_unk3c;                   // +0x3c reference
    uint32_t m_unk40;                          // +0x40 runtime (PostLoad 0x4acfe0 clears it)
    IKSerializable* m_unk44;                   // +0x44 reference (LVL010: a CKSoundDictionaryID)
    uint32_t m_unk48;                          // +0x48 runtime
    CGroundContactDatasInOut m_GContactInOut;  // +0x4c
    float m_unk78;                             // +0x78
    float m_unk7c;                             // +0x7c
    uint32_t m_unk80[6];                       // +0x80..+0x97 runtime
    CVector3 m_unk98;                          // +0x98 one 12-byte read (LVL010: 0, -20, 0: a gravity_maybe)
    uint32_t m_unkA4[4];                       // +0xa4..+0xb3 runtime
    float m_unkB4;                             // +0xb4
    float m_unkB8;                             // +0xb8
    uint32_t m_unkBC[11];                      // +0xbc..+0xe7 runtime
    float m_unkE8;                             // +0xe8
    void* m_unkEC;                             // +0xec runtime (PostLoad: an RwMatrix)
    float m_unkF0;                             // +0xf0
    float m_unkF4;                             // +0xf4
    float m_unkF8;                             // +0xf8
    uint32_t m_unkFC[3];                       // +0xfc..+0x107 runtime
    void* m_unk108;                            // +0x108 runtime (PostLoad: an RwMatrix)
    uint32_t m_unk10C;                         // +0x10c runtime: byte 0 = 0 (Start)
    void* m_pUnk110;                           // +0x110 Start: points to the state table at +0x118
    uint8_t m_unk114;                          // +0x114 constructor 0xff
    uint8_t m_unk115;                          // +0x115 constructor 0xff
    uint8_t m_pad116[2];
    uint32_t m_unk118[6];                      // +0x118..+0x12f runtime
};
DOTD_ASSERT_SIZE(CKHkS08TransportableKey, 0x130);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_unk3c, 0x3c);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_GContactInOut, 0x4c);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_unk78, 0x78);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_unk7c, 0x7c);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_unk98, 0x98);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_unkB4, 0xb4);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_unkB8, 0xb8);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_unkE8, 0xe8);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_unkF0, 0xf0);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_unkF4, 0xf4);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_unkF8, 0xf8);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_unk114, 0x114);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_unk115, 0x115);
