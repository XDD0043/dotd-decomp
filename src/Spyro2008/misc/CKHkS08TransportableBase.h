// CKHkS08TransportableBase.h - the unregistered base of the transportable hooks (key 0x3002, vtable
// 0xb28a18, size 0x24; Ghidra CKHkS08TransportableBase_3002_maybe). Original unit:
// CKHkS08TransportableBase.cpp (0x4ac108-0x4ac358). No XXL2 class. Derived: CKHkS08TransportableKey
// (whose Load 0x4aeee8 calls this Load), then CKHkS08TransportableWeight and CKHkS08PowerBucket.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkActorBase.h"

class CKHkS08TransportableBase : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xc0)

    // 0x004ac320 (Ghidra CKHkS08TransportableKey_ConstructBase_maybe; it sets this base's vtable 0xb28a18):
    // the CKHkActorBase part only.
    CKHkS08TransportableBase() {}
    ~CKHkS08TransportableBase() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004ac108 CKHkS08TransportableBase_3002_maybe_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x004ac0c8 KBase3002_PostLoad
    void Start() override;  // vt+0x50 0x004ac060 CKHkS08TransportableBase_3002_maybe_ResetRuntime
    // vt+0x144 0x9c5350 (CKHkS08TransportableKey_vf144 sets the byte at +0x2c; the base's slot is pure in the
    // original). Declared here with the Key's body because Start calls it.
    virtual void SetFlag2C(uint8_t value) { m_unk2C = value; }

    // +0x20 reference (LVL010/LVL040 data: the CKGrpTransportableObject group of the hook_maybe).
    IKSerializable* m_unk20;
    uint8_t m_unk24;                // +0x24 runtime (the derived classes' first run-time words start here)
    uint8_t m_unk25;                // +0x25 runtime (Start: 1)
    uint8_t m_pad26[2];
    uint32_t m_unk28;               // +0x28 runtime (Start: 0)
    uint8_t m_unk2C;                // +0x2c runtime: the flag vt+0x144 sets and vt+0x148 reads (Key)
    uint8_t m_pad2D[3];
    uint32_t m_unk30;               // +0x30 runtime
};
DOTD_ASSERT_SIZE(CKHkS08TransportableBase, 0x34);
DOTD_ASSERT_OFFSET(CKHkS08TransportableBase, m_unk20, 0x20);
