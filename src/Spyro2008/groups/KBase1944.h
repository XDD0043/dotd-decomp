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
    // vt+0x1c 0x00444110 CKGrpS08SpawnableMushroom_HandleMessage_Base_maybe: 0x0996 / 0x0997 set / clear
    // m_unk5c, 0x1002 / 0x1003 set bit 5 of m_bitArray, 0x1001 reads the beacons of a beacon set
    // (CKBeaconKluster_Load), 0x1000 writes them (STUB(C2.2)); 0 when handled, else 1.
    int32_t MessageProc(uint16_t message, void* data) override;
    // C2.2 spyro: vt+0x50 0x00443d58 KBase1944_ResetRuntime_maybe.
    void Start() override;
    virtual uint8_t VfF0() { return 0; }  // vt+0xf0 0x9c3568 KBase1944_vfF0 (CKGrpS08SpawnableMushroom 0x9c6028: the same)

    uint32_t m_unk2c;                 // +0x2c (LVL010: 3, 4)
    KObjectRefList m_list;            // +0x30 (LVL010: hook refs of key 0x3342)
    uint8_t m_unk40;                  // +0x40
    uint8_t m_unk41;                  // +0x41 read last; not set by the constructor
    uint8_t m_pad42[2];
    float m_unk44;                    // +0x44 the constructor sets 60.0 (LVL010: 150.0)
    uint8_t m_unk48;                  // +0x48
    uint8_t m_pad49[3];
    uint32_t m_unk4c;                 // +0x4c the constructor sets 20
    TVector<uint32_t, 1> m_vUnk50;    // +0x50 runtime (the constructor only)
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
