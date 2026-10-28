// CKGrpFightZone.h - a fight zone: its squads, areas, spawn data and triggers (key 0x17c4, vtable 0xb21d30,
// size 0x114). Original unit: CKGrpFightZone.cpp (also KBaseDC6's functions). XXL2: K/KSquad/CKGrpFightZone.h
// (two bounding boxes and a sector); DotD's Load is much longer, so the names are placeholders.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/groups/IKBaseGroup.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/util/TVector.h"

class CKS08FightZoneCpnt;

class CKGrpFightZone : public IKGroup<IKHook> {
public:
    DOTD_CLASS_KEY(kCategoryGroup, 0x5f)
    DOTD_DECLARE_FACTORIES(CKGrpFightZone)

    struct SEntry4c {                // 0x10 bytes
        IKSerializable* m_pRef;      // +0x00
        uint8_t m_unk04;             // +0x04
        uint8_t m_pad05;
        uint16_t m_unk06;            // +0x06 byte-swapped
        uint32_t m_unk08;            // +0x08 not read
        uint32_t m_unk0c;            // +0x0c not read
    };
    struct SEntry64 {                // 0x20 bytes
        CVector3 m_v00;              // +0x00 one 0xc-byte read, three swaps
        CVector3 m_v0c;              // +0x0c
        uint8_t m_unk18;             // +0x18
        uint8_t m_pad19[3];
        uint32_t m_unk1c;            // +0x1c the Load sets 0
    };
    struct SEntry70 {                // 0x24 bytes
        CVector3 m_v00;              // +0x00
        CVector3 m_v0c;              // +0x0c
        uint8_t m_unk18;             // +0x18
        uint8_t m_unk19;             // +0x19
        uint8_t m_unk1a;             // +0x1a
        uint8_t m_pad1b;
        IKSerializable* m_pRef;      // +0x1c reference, read after +0x20
        uint8_t m_unk20;             // +0x20
        uint8_t m_pad21[3];
    };
    struct SEntry8c {                // 0xc bytes
        uint8_t m_unk00;             // +0x00
        uint8_t m_unk01;             // +0x01
        uint8_t m_unk02;             // +0x02
        uint8_t m_pad03;
        IKSerializable* m_pRef04;    // +0x04
        IKSerializable* m_pRef08;    // +0x08
    };

    // 0x0026efd0 CKGrpFightZone_Create (the constructor 0x26dfb0 inlined).
    CKGrpFightZone() {
        m_vUnk40 = {nullptr, 1, 0};
        m_vUnk4c = {nullptr, 1, 0};
        m_vUnk64 = {nullptr, 1, 0};
        m_vUnk70 = {nullptr, 1, 0};
        m_unk7c = 0;
        m_unk80 = 0;
        m_vUnk8c = {nullptr, 1, 0};
        m_unk98 = 0;
        m_vUnk9c = {nullptr, 5, 0};
        m_ui32Priority = 0x80000014u;
    }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0026f108 CKGrpFightZone_Load
    void Start() override;  // vt+0x50 0x0026ed08 CKGrpFightZone_Start
    // 0x00272cd0 CKGrpFightZone_ClearTriggerStates_maybe: the +0x1c word of each +0x64 entry cleared.
    void ClearTriggerStates();
    // 0x00272d10 CKGrpFightZone_ResetEnemyTypeCounts_maybe: the +0x08 halfword and +0x0c word of each +0x4c entry
    // cleared, and +0x88.
    void ResetEnemyTypeCounts();

    CKS08FightZoneCpnt* m_pFightZoneCpnt;   // +0x2c its CKS08FightZoneCpnt (told its zone in the Load)
    IKSerializable* m_pUnk30;               // +0x30 reference
    IKSerializable* m_pUnk34;               // +0x34 reference
    IKSerializable* m_pUnk38;               // +0x38 reference
    uint32_t m_unk3c;                       // +0x3c
    TVector<IKSerializable*, 1> m_vUnk40;   // +0x40 references (_maybe the squads)
    TVector<SEntry4c, 1> m_vUnk4c;          // +0x4c
    uint32_t m_unk58;                       // +0x58
    uint32_t m_unk5c;                       // +0x5c
    uint32_t m_unk60;                       // +0x60 not set
    TVector<SEntry64, 1> m_vUnk64;          // +0x64
    TVector<SEntry70, 1> m_vUnk70;          // +0x70
    uint32_t m_unk7c;                       // +0x7c the constructor sets 0
    uint32_t m_unk80;                       // +0x80 the constructor sets 0
    uint32_t m_unk84;                       // +0x84
    uint32_t m_unk88;                       // +0x88 not set
    TVector<SEntry8c, 1> m_vUnk8c;          // +0x8c
    uint32_t m_unk98;                       // +0x98 the constructor sets 0
    TVector<CVector3, 5> m_vUnk9c;          // +0x9c
    uint8_t m_unka8;                        // +0xa8
    uint8_t m_pada9[3];
    CTriggerStarter m_aTriggers[12];        // +0xac..+0x10b (read order: +0xac..+0xdc, +0xf4..+0x104, +0xe4, +0xec)
    uint8_t m_unk10c[3];                    // +0x10c not set
    uint8_t m_unk10f;                       // +0x10f read last
    uint8_t m_unk110;                       // +0x110 runtime (Start: 0)
    uint8_t m_pad111[3];
};
DOTD_ASSERT_SIZE(CKGrpFightZone::SEntry4c, 0x10);
DOTD_ASSERT_SIZE(CKGrpFightZone::SEntry64, 0x20);
DOTD_ASSERT_SIZE(CKGrpFightZone::SEntry70, 0x24);
DOTD_ASSERT_OFFSET(CKGrpFightZone::SEntry70, m_pRef, 0x1c);
DOTD_ASSERT_SIZE(CKGrpFightZone::SEntry8c, 0xc);
DOTD_ASSERT_SIZE(CKGrpFightZone, 0x114);
DOTD_ASSERT_OFFSET(CKGrpFightZone, m_pFightZoneCpnt, 0x2c);
DOTD_ASSERT_OFFSET(CKGrpFightZone, m_unk3c, 0x3c);
DOTD_ASSERT_OFFSET(CKGrpFightZone, m_vUnk40, 0x40);
DOTD_ASSERT_OFFSET(CKGrpFightZone, m_vUnk4c, 0x4c);
DOTD_ASSERT_OFFSET(CKGrpFightZone, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKGrpFightZone, m_vUnk64, 0x64);
DOTD_ASSERT_OFFSET(CKGrpFightZone, m_vUnk70, 0x70);
DOTD_ASSERT_OFFSET(CKGrpFightZone, m_unk84, 0x84);
DOTD_ASSERT_OFFSET(CKGrpFightZone, m_vUnk8c, 0x8c);
DOTD_ASSERT_OFFSET(CKGrpFightZone, m_vUnk9c, 0x9c);
DOTD_ASSERT_OFFSET(CKGrpFightZone, m_unka8, 0xa8);
DOTD_ASSERT_OFFSET(CKGrpFightZone, m_aTriggers, 0xac);
DOTD_ASSERT_OFFSET(CKGrpFightZone, m_unk10f, 0x10f);
