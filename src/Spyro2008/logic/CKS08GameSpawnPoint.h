// CKS08GameSpawnPoint.h - Spyro's spawn point (key 0x790c, vtable 0xb2b470, PS3 size 0xa0). Original
// unit: CKS08GameSpawnPoint.cpp (0x508720-0x5094c8). GAME.KP3 holds 108. Not in XXL2.
//
// Two hero slots (two heroes: Spyro and Cynder, _maybe): each has a beacon accessor at +0x40/+0x48 and a
// 0x24-byte record at +0x50/+0x74, whose position and direction CKS08GameSpawnPoint_ResolveSlotPosition_maybe
// (0x5090a8) computes from the beacon.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKGameSpawnPoint.h"

class CKS08GameSpawnPoint : public CKGameSpawnPoint {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x1e4)
    DOTD_DECLARE_FACTORIES(CKS08GameSpawnPoint)

    // 0x24 bytes. Names ours.
    struct Slot {
        float m_vPosition[3];    // +0x00 ResolveSlotPosition_maybe: the beacon's position / 10
        float m_vDirection[3];   // +0x0c sin(angle), 0, cos(angle) of the beacon's angle byte
        uint8_t m_unk18;         // +0x18 level part
        uint8_t m_unk19;         // +0x19 level part
        uint8_t m_pad1a[2];
        uint32_t m_unk1c;        // +0x1c level part
        uint8_t m_unk20;         // +0x20 level part
        uint8_t m_pad21[3];
    };

    CKS08GameSpawnPoint();             // inlined in CKS08GameSpawnPoint_Create 0x508ff8 / CreateArray 0x508ae0
    ~CKS08GameSpawnPoint() override {} // vt+0x00 / +0x04  0x9c7198 / 0x9c7148

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00508cc8 CKS08GameSpawnPoint_Load
    void InitializeLevelData() override;                // vt+0x5c 0x005087f0 CKS08GameSpawnPoint_InitLevelData
    // 0x005090a8 CKS08GameSpawnPoint_ResolveSlotPosition_maybe: the slot's record from its beacon (null when
    // the slot's accessor is all 0xffff).
    Slot* ResolveSlotPosition(int32_t slot);
    uint16_t Activate() override;  // vt+0x7c 0x00508778 CKS08GameSpawnPoint_Activate_maybe: the base's (0x3cd88)
    // vt+0x58 0x508828 InitGameData only calls the base's. Not ported: vt+0x1c 0x5088a0 MessageProc,
    // +0x60 0x5087c8, +0x64 0x5087a0, +0x78 0x508770, +0x7c 0x508778 (STUB(C1.6)).

    IKSerializable* m_pUnk38;     // +0x38 level part, after the base's; InitializeLevelData: 0
    uint32_t m_unk3c;             // +0x3c not set by the Load or the constructor
    uint16_t m_aBeacons[2][4];    // +0x40 level part (8 half-words, each swapped); the constructor: 0xffff
    Slot m_aSlots[2];             // +0x50 level part fills the records from the last one down
    uint8_t m_unk98;              // +0x98 level part, last
    uint8_t m_unk99;              // +0x99 type-8 block, after the base's
    uint8_t m_pad9a[2];
    void* m_unk9c;                // +0x9c not set by the Load or the constructor
};
DOTD_ASSERT_SIZE(CKS08GameSpawnPoint::Slot, 0x24);
DOTD_ASSERT_SIZE(CKS08GameSpawnPoint, 0xa0);
DOTD_ASSERT_OFFSET(CKS08GameSpawnPoint, m_pUnk38, 0x38);
DOTD_ASSERT_OFFSET(CKS08GameSpawnPoint, m_aBeacons, 0x40);
DOTD_ASSERT_OFFSET(CKS08GameSpawnPoint, m_aSlots, 0x50);
DOTD_ASSERT_OFFSET(CKS08GameSpawnPoint, m_unk98, 0x98);
DOTD_ASSERT_OFFSET(CKS08GameSpawnPoint, m_unk99, 0x99);
DOTD_ASSERT_OFFSET(CKS08GameSpawnPoint, m_unk9c, 0x9c);
