// CKHkS08TransportableBase.h - the unregistered base of the transportable hooks (key 0x3002, vtable
// 0xb28a18, size 0x24; Ghidra CKHkS08TransportableBase_3002_maybe). Original unit:
// CKHkS08TransportableBase.cpp (0x4ac108-0x4ac358). No XXL2 class. Derived: CKHkS08TransportableKey
// (whose Load 0x4aeee8 calls this Load), then CKHkS08TransportableWeight and CKHkS08PowerBucket.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkActorBase.h"

class CSGHotSpot;
class IKTime;
struct CGroundContactDatasInOut;
struct CVector3;

class CKHkS08TransportableBase : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xc0)
    // vt+0x08 0x9c5278 CKHkS08TransportableBase_3002_maybe_IsKindOf: 0x3002, then CKHkActorBase's.
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x3002 || CKHkActorBase::IsKindOfClass(key); }

    // 0x004ac320 (Ghidra CKHkS08TransportableKey_ConstructBase_maybe; it sets this base's vtable 0xb28a18):
    // the CKHkActorBase part only.
    CKHkS08TransportableBase() {}
    // 0x004ac2b8 CKHkS08TransportableBase_3002_maybe_BaseDestructor: the base's vtable, then CKHkActorBase's (nothing to
    // free).
    ~CKHkS08TransportableBase() override {}

    // vt+0x10 0x004ac218 CKHkS08TransportableBase_3002_maybe_Destroy (Ghidra _ClearReferences): CKHkActorBase_d82_maybe_Destroy
    // 0x3f6e40 (empty).
    void Destroy() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004ac108 CKHkS08TransportableBase_3002_maybe_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x004ac0c8 KBase3002_PostLoad
    void Start() override;  // vt+0x50 0x004ac060 CKHkS08TransportableBase_3002_maybe_ResetRuntime
    // vt+0x68 0x004ac038 CKHkS08TransportableBase_3002_maybe_OnLevelExit (the base's Stop): CKHkActorBase_d82_maybe_Stop
    // 0x3f6e50 (empty).
    void Stop() override {}

    // The transportable slots (vt+0xec..+0x18c, from CKHkS08TransportableKey's vtable 0xb28c08 and the Weight's 0xb28e28;
    // pure or empty in this base). The defaults below are the base's slot when it has one, else harmless (no
    // instance of the base exists).
    // vt+0xec: CKHkActorBase::VfEC (Key: KStub_Return0; Weight 0x4b4bf0).
    virtual uint8_t VfF0(IKSerializable* /*carrier*/) { return 0; }     // vt+0xf0: a carrier picks it up
    virtual uint8_t VfF4(IKSerializable* /*carrier*/) { return 0; }     // vt+0xf4: can be picked up
    // vt+0xf8: thrown / dropped with `velocity` (1 when the carrier let it go): the Key's 0x4af9a8, the Weight's 0x4b4d18.
    virtual uint8_t VfF8(IKSerializable* /*carrier*/, const CVector3* /*velocity*/) { return 0; }
    virtual uint8_t VfFC(IKSerializable* /*carrier*/) { return 0; }     // vt+0xfc
    virtual uint8_t Vf100() { return 0; }                                // vt+0x100: carried (+0x48 set)
    virtual float Vf104() { return 0.0f; }                               // vt+0x104
    // vt+0x108 / vt+0x11c: pure in the base (the Key's 0x4af670 / 0x4af8e8 leave the state machine).
    virtual void Vf108() {}
    virtual void Vf10C() {}                                              // vt+0x10c: the state machine started (state 1)
    virtual uint8_t Vf110() { return 0; }                                // vt+0x110: in a state (+0x114 != 0xff)
    virtual IKSerializable* Vf114() { return nullptr; }                  // vt+0x114: the carrier (+0x48)
    virtual CSGHotSpot* Vf118() { return nullptr; }                      // vt+0x118: the hot spot it is held by
    virtual void ResetStateMachine() {}
    // vt+0x120 0x9c52e0 CKHkS08TransportableBase_3002_maybe_vf120 (empty here): taken from the pool.
    virtual void Vf120() {}
    // vt+0x124 0x9c52e8 CKHkS08TransportableBase_3002_maybe_vf124: empty (the Key's 0x4ac580, the Weight's 0x4b5d78).
    virtual void Vf124() {}
    // vt+0x128 0x9c52f0 CKHkS08TransportableBase_3002_maybe_vf128 (empty here; the Key's 0x4ac500): placed / not placed.
    virtual void Vf128(uint8_t /*placed*/) {}
    virtual uint8_t Vf12C() { return m_unk24; }                          // vt+0x12c 0x9c52f8: placed (+0x24)
    virtual IKSerializable* Vf130() { return m_unk20; }                  // vt+0x130 0x9c5300: the group (+0x20)
    virtual void Vf134(IKSerializable* /*receiver*/) {}                  // vt+0x134: put on a receiver
    virtual void Vf138(uint8_t /*value*/) {}                             // vt+0x138: the byte +0xbd (Key)
    virtual uint8_t Vf13C() { return 0; }                                // vt+0x13c: the byte +0xbd (Key)
    virtual uint8_t Vf140() { return Vf150(); }                          // vt+0x140 0x9c5308: vt+0x150
    // vt+0x144 0x9c5350 (CKHkS08TransportableKey_vf144 sets the byte at +0x2c; the base's slot is pure in the
    // original). Declared here with the Key's body because Start calls it.
    virtual void SetFlag2C(uint8_t value) { m_unk2C = value; }
    virtual uint8_t Vf148() { return m_unk2C; }                          // vt+0x148 0x9c5358: the byte +0x2c
    // vt+0x14c 0x9c5360 CKHkS08TransportableKey_vf14C (the base's slot too): the byte +0x25.
    virtual void SetUnk25(uint8_t value) { m_unk25 = value; }
    virtual uint8_t Vf150() { return m_unk25; }                          // vt+0x150 0x9c5368: the byte +0x25 (in the pool)
    virtual void Vf154(const CGroundContactDatasInOut* /*contact*/) {}   // vt+0x154: landed on a ground
    virtual void Vf158(uint8_t /*value*/) {}                             // vt+0x158: the byte +0x10c (Key)
    virtual uint8_t Vf15C() { return 0; }                                // vt+0x15c: the byte +0x10c (Key)
    virtual uint8_t Vf160(IKTime* /*clock*/) { return 0; }               // vt+0x160: the fall's step (Key, Weight)
    virtual void Vf164(CVector3* /*out*/, const CVector3* /*velocity*/, const CVector3* /*normal*/) {}  // vt+0x164
    virtual void Vf168() {}                                              // vt+0x168: the impact feedback
    virtual void Vf17C() {}                                              // vt+0x17c: the effect acquired
    virtual void Vf180() {}                                              // vt+0x180: the effect released
    virtual uint8_t Vf184() { return 1; }                                // vt+0x184
    virtual void Vf188(float /*dt*/) {}  // vt+0x188 (Weight 0x4b5860: the carried weight's swing)
    virtual void Vf18C() {}  // vt+0x18c (Weight: SpawnAltImpactFx 0x4b7038; the spawner calls it for class ids 0xc3 / 0xc5)

    // 0x004abfb0 CKHkS08TransportableBase_3002_maybe_GetOwnerSpawner_maybe (in the spawner's unit): +0x28.
    IKSerializable* GetOwnerSpawner() const { return m_unk28; }
    // 0x004abfb8 CKHkS08TransportableBase_3002_maybe_SetOwnerSpawner_maybe (in the spawner's unit): +0x28.
    void SetOwnerSpawner(IKSerializable* spawner) { m_unk28 = spawner; }

    // +0x20 reference (LVL010/LVL040 data: the CKGrpTransportableObject group of the hook_maybe).
    IKSerializable* m_unk20;
    uint8_t m_unk24;                // +0x24 runtime: placed on a receiver (vt+0x128 / vt+0x12c)
    uint8_t m_unk25;                // +0x25 runtime (Start: 1): in its group's pool (vt+0x14c / vt+0x150)
    uint8_t m_pad26[2];
    IKSerializable* m_unk28;        // +0x28 runtime (Start, PostLoad: 0): the spawner that spawned it (0x4abfb8)
    uint8_t m_unk2C;                // +0x2c runtime: the flag vt+0x144 sets and vt+0x148 reads (Key)
    uint8_t m_unk2D;                // +0x2d runtime (Key Start / Restart: 0; vt+0x134: 1)
    uint8_t m_pad2E[2];
    IKSerializable* m_unk30;        // +0x30 runtime: the receiver it was put on (vt+0x134)
};
DOTD_ASSERT_SIZE(CKHkS08TransportableBase, 0x34);
DOTD_ASSERT_OFFSET(CKHkS08TransportableBase, m_unk20, 0x20);
