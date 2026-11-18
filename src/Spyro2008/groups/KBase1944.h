// KBase1944.h - the unregistered base of CKGrpS08SpawnableMushroom (key 0x1944, an IKGroup<IKHook>; vtable
// 0xb266c0). Original unit: KBase1944.cpp (0x4444c8 Load, 0x444040 the constructor, Ghidra
// CKGrpS08SpawnableMushroom_ConstructBase_maybe). A spawner group _maybe (its runtime spawns and recycles
// members: KBase1944_DeactivateAllSpawned_maybe). No XXL2 class with this key.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/groups/IKBaseGroup.h"
#include "k2000/memory/KObjectRefList.h"
#include "k2000/util/TVector.h"

class KBase42C2;
using KBase1944Member = KBase42C2;

class KBase1944 : public IKGroup<IKHook> {
public:
    // 0x00444040 CKGrpS08SpawnableMushroom_ConstructBase_maybe (the KBase1944 constructor).
    KBase1944() {
        m_list.m_pHead = nullptr;
        m_list.m_ui32Count = 0;
        m_list.m_ui32Count2 = 0;
        m_list.m_pBlock = nullptr;
        m_vUnk50 = {nullptr, 1, 0};
        m_ui32Priority = 0x80000009u;
        m_unk4c = 0x14;
        m_unk44 = 0x1.ep+5f;  // 0x42700000 = 60.0f
        m_unk48 = 0;
        m_unk2c = 0;
        m_unk40 = 0;
    }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004444c8 KBase1944_Load
    // vt+0x10 0x004446b8 KBase1944_Destroy: no child groups, no members (vt+0xb0's head), the slot vector (+0x50) freed.
    void Destroy() override;
    // vt+0x30 0x00443c60 KBase1944_PostLoad (CKGrpS08SpawnableMushroom_PostLoad 0x4d7ae8 calls it): IKLife_PostLoad,
    // then for the level type with +0x40 and +0x48 set the sorted slots allocated for +0x4c entries.
    int32_t PostLoad(int32_t type) override;
    // vt+0x1c 0x00444110 CKGrpS08SpawnableMushroom_HandleMessage_Base_maybe: 0x0996 / 0x0997 set / clear
    // m_unk5c, 0x1002 / 0x1003 set bit 5 of m_bitArray, 0x1001 reads the beacons of a beacon set
    // (CKBeaconKluster_Load), 0x1000 writes them (the save path); 0 when handled, else 1.
    int32_t MessageProc(uint16_t message, void* data) override;
    // C2.2 spyro: vt+0x50 0x00443d58 KBase1944_ResetRuntime_maybe.
    void Start() override;
    void Restart() override;  // vt+0x54 0x00444920 KBase1944_ReinitRuntime
    void DeactivateAllSpawned();  // 0x00444740 KBase1944_DeactivateAllSpawned_maybe
    // 0x00443bf0 CKGrpS08SpawnableMushroom_ReleaseMushroom_maybe: `member` put to sleep in this group's bundle, its slot
    // key cleared and given back to the list (the destroyed mushroom's).
    void ReleaseMember(IKSerializable* member);
    virtual uint8_t VfF0() { return 0; }  // vt+0xf0 0x9c3568 KBase1944_vfF0 (CKGrpS08SpawnableMushroom 0x9c6028: the same)

    // 0x00444a08 KBase1944_Update (the group's vt+0x7c through CKGrpS08SpawnableMushroom_Update 0x4d79c8): unless the meca
    // group is off (+0x0c bit 1) or there is no template (+0x34), the members on the beacons of the group's type: the
    // drawn klusters' sets (GatherBeaconsOfType 7: in the frustum, nearest first) give one slot per beacon; with +0x40 the
    // slot must be within +0x44 of the controlled hero (+0x41; else the camera); with Vf104 its sphere (Vf108, raised by
    // Vf10C) in the frustum. A spawned member on the slot stays; else a free slot (Vf100) is taken while members remain
    // (with +0x48 the slots are first sorted by distance, at most +0x4c). Members left over that may go (VfF0) are put
    // to sleep and given back; the new slots get a member each (woken through the core manager).
    void Update(IKTime* clock) override;
    // vt+0xec (pure in the base): the beacon type of spawn kind `kind` (+0x2c).
    virtual uint8_t VfEC(uint32_t /*kind*/) { return 0; }
    virtual uint8_t VfF4() { return 0; }  // vt+0xf4 0x9c3570
    // vt+0xf8 0x00443dd8 CKGrpS08SpawnableMushroom_ForEachCurrentSectorBeacon_maybe: every beacon of the current sector of
    // the type given to VfFC.
    virtual void VfF8();
    virtual void VfFC(const uint16_t* /*slot*/, const uint8_t* /*beacon*/) {}  // vt+0xfc 0x9c3578 (empty)
    virtual uint8_t Vf100(const uint16_t* /*slot*/) { return 1; }               // vt+0x100 0x9c3580: a slot is free
    virtual uint8_t Vf104(uint32_t /*kind*/) { return 0; }                      // vt+0x104 0x9c3588: frustum test
    virtual float Vf108(uint32_t /*kind*/) { return 1.0f; }                     // vt+0x108 0x9c3590 (TOC +0x51b0): radius
    virtual float Vf10C(uint32_t /*kind*/) { return 0.0f; }                     // vt+0x10c 0x9c3598 (TOC +0x51b4): height

    uint32_t m_unk2c;                 // +0x2c (LVL010: 3, 4)
    KObjectRefList m_list;            // +0x30 (LVL010: hook refs of key 0x3342)
    uint8_t m_unk40;                  // +0x40
    uint8_t m_unk41;                  // +0x41 read last; not set by the constructor
    uint8_t m_pad42[2];
    float m_unk44;                    // +0x44 the constructor sets 60.0 (LVL010: 150.0)
    uint8_t m_unk48;                  // +0x48
    uint8_t m_pad49[3];
    uint32_t m_unk4c;                 // +0x4c the constructor sets 20
    // +0x50 runtime (the constructor only): the sorted slots of Update (16 bytes on the PS3: four 16-bit values and the
    // squared distance); DOTD: a native block of SpawnSlot.
    struct SpawnSlot {
        uint16_t m_aui16Key[4];
        float m_fDistance;
        uint32_t m_pad;
    };
    TVector<SpawnSlot, 1> m_vUnk50;
    // +0x5c / +0x5d: MessageProc writes +0x5c, so these two bytes belong here rather than to the derived
    // CKGrpS08SpawnableMushroom (_maybe: the only derived class); neither constructor sets them.
    uint8_t m_unk5c;                  // +0x5c messages 0x0996 (1) / 0x0997 (0)
    uint8_t m_unk5d;                  // +0x5d CKGrpS08SpawnableMushroom_Load reads it
    uint8_t m_pad5e[2];
};
DOTD_ASSERT_SIZE(KBase1944, 0x60);
DOTD_ASSERT_OFFSET(KBase1944, m_unk5c, 0x5c);
DOTD_ASSERT_OFFSET(KBase1944, m_unk2c, 0x2c);
DOTD_ASSERT_OFFSET(KBase1944, m_list, 0x30);
DOTD_ASSERT_OFFSET(KBase1944, m_unk40, 0x40);
DOTD_ASSERT_OFFSET(KBase1944, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(KBase1944, m_unk48, 0x48);
DOTD_ASSERT_OFFSET(KBase1944, m_unk4c, 0x4c);
DOTD_ASSERT_OFFSET(KBase1944, m_vUnk50, 0x50);
