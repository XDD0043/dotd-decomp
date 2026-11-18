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
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9bbfe8
        return key == 0x17c4 || key == 0x17e || key == 0x4 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKGrpFightZone)

    struct SEntry4c {                // 0x10 bytes
        IKSerializable* m_pRef;      // +0x00
        uint8_t m_unk04;             // +0x04
        uint8_t m_pad05;
        int16_t m_unk06;             // +0x06 byte-swapped; the type's spawn cap (-1: none)
        uint16_t m_unk08;            // +0x08 not read; the type's spawned count (TrySpawnRequest, AddSpawnedCount)
        uint16_t m_unk0a;            // +0x0a not read
        uint32_t m_unk0c;            // +0x0c not read; cleared with +0x08 (ResetEnemyTypeCounts)
    };
    struct SEntry64 {                // 0x20 bytes
        CVector3 m_v00;              // +0x00 one 0xc-byte read, three swaps
        CVector3 m_v0c;              // +0x0c
        uint8_t m_unk18;             // +0x18
        uint8_t m_pad19[3];
        float m_fCooldown;           // +0x1c the Load sets 0; SpawnAtSpawnPoint adds 3, TickSpawnPointCooldowns counts down to 0
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
    // The run-time lists' nodes (FreeListPool 0x00ceaa20 in the original: the 8-, 12- and 16-byte pools at +0x14 /
    // +0x24 / +0x34; here a free list per node type, see the .cpp).
    // A spawn point candidate (8 bytes): SelectSpawnPoints fills the list +0x7c, SpawnAtSpawnPoint picks from it.
    struct SSpawnPointNode {
        uint8_t m_index;             // +0x00 index into +0x64
        uint8_t m_pad01[3];
        SSpawnPointNode* m_pNext;    // +0x04
    };
    // A spawn request (12 bytes; list +0x80): `count` enemies of type `type` for `squad` at the +0x70 entry `entry`.
    struct SSpawnRequest {
        uint8_t m_entry;             // +0x00 index into +0x70
        uint8_t m_type;              // +0x01 index into +0x4c (and the squad's per-type counters)
        uint8_t m_count;             // +0x02 still to spawn
        uint8_t m_pad03;
        IKSerializable* m_pSquad;    // +0x04 a CKGrpSquad
        SSpawnRequest* m_pNext;      // +0x08
    };
    // A squad transfer (16 bytes; list +0x98): `count` enemies of type `type` moved from one squad to another.
    struct STransferNode {
        uint8_t m_type;              // +0x00
        uint8_t m_count;             // +0x01
        uint8_t m_pad02[2];
        IKSerializable* m_pFrom;     // +0x04 a CKGrpSquad
        IKSerializable* m_pTo;       // +0x08 a CKGrpSquad
        STransferNode* m_pNext;      // +0x0c
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
        m_unk7c = nullptr;
        m_unk80 = nullptr;
        m_vUnk8c = {nullptr, 1, 0};
        m_unk98 = nullptr;
        m_vUnk9c = {nullptr, 5, 0};
        m_ui32Priority = 0x80000014u;
    }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0026f108 CKGrpFightZone_Load
    // vt+0x10 0x0026eca8 CKGrpFightZone_Destroy: no child groups (+0x18), no members (vt+0xb0's head).
    void Destroy() override { DestroyGroupLists(); }
    // vt+0xa8 0x0026e7d0 CKGrpFightZone_EnableMembers / vt+0xac 0x0026e968 DisableMembers (OnLock / OnUnlock): every child group
    // locked / unlocked (SetObjectLocked 0x1c250).
    void OnLock() override;
    void OnUnlock() override;
    // vt+0x24 0x0026eab8 CKGrpFightZone_RecursiveRegistration: IKGroup_LevelReset 0x12a68, then for a level file
    // (type 0) the zone registered with the saving manager and its component's registration (type 0; not tested for
    // null); the twelve trigger starters register nothing (KStub_Return1_2361b0).
    void RecursiveRegistration(int32_t type) override;
    void Start() override;  // vt+0x50 0x0026ed08 CKGrpFightZone_Start
    void Restart() override;  // vt+0x54 0x0026eda8 CKGrpFightZone_Restart (Start's body)
    // 0x0026e398 CKGrpFightZone_ForceEndFight_maybe: the fight's end at once (see the .cpp).
    void ForceEndFight();
    // vt+0x98 0x00270d80 CKGrpFightZone_StopFight (the zone put to sleep, e.g. its sector unloaded): a running fight
    // (+0x0c bit 5) ends as ForceEndFight does, its flag cleared first.
    void Vf98() override;
    int32_t PostLoad(int32_t type) override;  // vt+0x30 0x0026e4e8 CKGrpFightZone_PostLoad
    // vt+0x38 0x0026e148 CKGrpFightZone_SetDefaultState: the zone may arm (+0x10e = 1).
    void SetDefaultState(int32_t flag) override;
    // vt+0x3c 0x0026e158 CKGrpFightZone_SetGameState: infos 0x2a and 0x2c only (0 otherwise): the zone may arm
    // (+0x10e) when the state is 0. Returns 1 for those infos.
    int32_t SetGameState(const SApplyGameState* state) override;
    // vt+0x40 0x00271e68 CKGrpFightZone_GetInfo: the trigger values 1-0xb, 0x1b, 0x1c, 0x1f, 0x20, 0x27-0x29 and 0x2e
    // (the detectors, the squads' and types' counts, caps, kills, a hero's distance, the component's objectives).
    int32_t GetInfo(IKInfo* info, int32_t request) override;
    // 0x00272cd0 CKGrpFightZone_ClearTriggerStates_maybe: the +0x1c word of each +0x64 entry cleared.
    void ClearTriggerStates();
    // 0x00272d10 CKGrpFightZone_ResetEnemyTypeCounts_maybe: the +0x08 halfword and +0x0c word of each +0x4c entry
    // cleared, and +0x88.
    void ResetEnemyTypeCounts();

    void Update(IKTime* clock) override;                      // vt+0x7c 0x00270c18 UpdateCKGrpFightZone
    int32_t MessageProc(uint16_t message, void* data) override;  // vt+0x1c 0x00270ef0 CKGrpFightZone_MessageProc
    void UpdateZoneTriggers();                 // 0x002703d8 CKGrpFightZone_UpdateZoneTriggers_maybe
    void TickSpawnPointCooldowns(IKTime* clock);  // 0x00272ac0 CKGrpFightZone_TickSpawnPointCooldowns_maybe
    void SpawnAllSquadsFullFormation();        // 0x00272b40 CKGrpFightZone_SpawnAllSquadsFullFormation_maybe
    void QueueSpawnsForAllSquads(uint32_t count);  // 0x00272b90 CKGrpFightZone_QueueSpawnsForAllSquads_maybe
    uint8_t AnySquadWantsSpawn();              // 0x00272bf0 CKGrpFightZone_AnySquadWantsSpawn_maybe
    void ScheduleSquadRespawns();              // 0x00272c80 CKGrpFightZone_ScheduleSquadRespawns_maybe
    // 0x00272dd8 CKGrpFightZone_SpawnAtSpawnPoint_maybe: 1 when `enemy` was placed at a candidate spawn point.
    int32_t SpawnAtSpawnPoint(IKSerializable* enemy);
    uint8_t TrySpawnRequest(SSpawnRequest* request);  // 0x00272ff8 CKGrpFightZone_TrySpawnRequest_maybe
    void ProcessSpawnRequests();               // 0x002732a8 CKGrpFightZone_ProcessSpawnRequests_maybe
    void SelectSpawnPoints();                  // 0x00273398 CKGrpFightZone_SelectSpawnPoints_maybe
    void ProcessSquadTransfers();              // 0x002739a0 CKGrpFightZone_ProcessSquadTransfers_maybe
    // 0x00272478 CKGrpFightZone_AddSpawnedCount_maybe: the counts of `type` and of the zone raised by `count`, clamped
    // to their caps; returns how many of them fit.
    uint32_t AddSpawnedCount(uint8_t type, uint32_t count);
    // 0x00272708 CKGrpFightZone_TransferEnemyToSquad_maybe
    uint8_t TransferEnemyToSquad(IKSerializable* from, IKSerializable* to, uint8_t type);
    void QueueTransfersForRequest(uint8_t request);  // 0x00273b68 CKGrpFightZone_QueueTransfersForRequest_maybe
    void QueueEntrySpawns(uint8_t entry);      // 0x00274698 CKGrpFightZone_QueueEntrySpawns_maybe
    // DOTD: the squads put to sleep and the request / transfer lists emptied (inlined in UpdateZoneTriggers and
    // MessageProc wherever the fight stops or restarts).
    void SleepSquadsAndClearQueues();
    void SetCompleted(uint8_t completed);      // 0x0026e348 CKGrpFightZone_SetCompleted_maybe
    int32_t GetTotalKilledCount();             // 0x00271bb8 CKGrpFightZone_GetTotalKilledCount_maybe
    // 0x0026e120 CKGrpFightZone_IsSpawningAllowed_maybe: the detectors hold (+0x10c) and the zone is not completed.
    uint8_t IsSpawningAllowed() { return m_unk10c != 0 ? static_cast<uint8_t>(m_unk10d == 0) : 0; }
    // 0x002723c8 CKGrpFightZone_IsSpawnCapReached_maybe: the zone's total cap, else the type's cap, is reached.
    uint8_t IsSpawnCapReached(uint8_t type) {
        const SEntry4c& kind = m_vUnk4c.m_pBlock[type];
        const bool typeFull = kind.m_unk06 >= 0 && static_cast<int32_t>(kind.m_unk08) >= kind.m_unk06;
        if (m_unk84 >= 0 && m_unk88 >= m_unk84) return 1;
        return typeFull ? 1 : 0;
    }

    CKS08FightZoneCpnt* m_pFightZoneCpnt;   // +0x2c its CKS08FightZoneCpnt (told its zone in the Load)
    IKSerializable* m_pUnk30;               // +0x30 reference
    IKSerializable* m_pUnk34;               // +0x34 reference
    IKSerializable* m_pUnk38;               // +0x38 reference
    uint32_t m_unk3c;                       // +0x3c
    TVector<IKSerializable*, 1> m_vUnk40;   // +0x40 references (_maybe the squads)
    TVector<SEntry4c, 1> m_vUnk4c;          // +0x4c
    uint32_t m_unk58;                       // +0x58
    uint32_t m_unk5c;                       // +0x5c
    uint32_t m_unk60;                       // +0x60 not set; run-time counter (MessageProc 0xd08..0xd0c, from +0x5c / +0x58)
    TVector<SEntry64, 1> m_vUnk64;          // +0x64
    TVector<SEntry70, 1> m_vUnk70;          // +0x70
    SSpawnPointNode* m_unk7c;               // +0x7c the constructor sets 0; spawn point candidates (SelectSpawnPoints)
    SSpawnRequest* m_unk80;                 // +0x80 the constructor sets 0; spawn requests
    int32_t m_unk84;                        // +0x84 the zone's spawn cap (-1: none)
    int32_t m_unk88;                        // +0x88 not set; the zone's spawned count
    TVector<SEntry8c, 1> m_vUnk8c;          // +0x8c
    STransferNode* m_unk98;                 // +0x98 the constructor sets 0; squad transfers
    TVector<CVector3, 5> m_vUnk9c;          // +0x9c
    uint8_t m_unka8;                        // +0xa8
    uint8_t m_pada9[3];
    CTriggerStarter m_aTriggers[12];        // +0xac..+0x10b (read order: +0xac..+0xdc, +0xf4..+0x104, +0xe4, +0xec)
    uint8_t m_unk10c;                       // +0x10c not set; UpdateZoneTriggers: 1 while the zone's detectors hold
    uint8_t m_unk10d;                       // +0x10d not set; MessageProc 0xd13 sets it
    uint8_t m_unk10e;                       // +0x10e may arm: SetDefaultState 1, SetGameState, MessageProc 0xd11 / 0xd12
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
