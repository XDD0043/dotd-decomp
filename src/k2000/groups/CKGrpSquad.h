// CKGrpSquad.h - a squad of enemies with its states, spawn data and triggers (key 0x604, vtable 0xb212b0,
// size 0xd0). Original unit: CKGrpSquad.cpp. XXL2: K/KSquad/CKGrpSquad.h; DotD's layout and Load differ
// (more vectors, five trigger starters), so only the first vector keeps XXL2's name (m_vStates: XXL2's Load
// reads it first, each state with its CMatrix34) and the current matrix (m_pCurrentMatrix, a copy of the
// first state's). The other names are placeholders.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/groups/IKBaseGroup.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/memory/Mem.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/util/TVector.h"

class IKHook;
// 0x0001d5c0 Group_TransferHook_maybe (CKGrpSquad.cpp; for the pools', squads' and weapon pools' member lists).
int32_t Group_TransferHook(IKHook* hook, IKBaseGroup* to, IKBaseGroup* from);

// The enemy's formation block: CKHkS08Enemy +0x1c4, what its vt+0xec returns (pointer-free, so the view holds on
// every build). The squads and fight zones write the formation position and direction, the slot, the type and flags.
struct SEnemyFormation {
    CVector3 m_vPos;     // +0x00 (enemy +0x1c4)
    CVector3 m_vDir;     // +0x0c (enemy +0x1d0)
    float m_unk18[3];    // +0x18
    int32_t m_slot;      // +0x24 (enemy +0x1e8) the choreography key slot, -1: none
    uint8_t m_type;      // +0x28 (enemy +0x1ec) the enemy type (the fight zone's +0x4c index)
    uint8_t m_bMoving;   // +0x29 (enemy +0x1ed) UpdateChoreography: the key changed this frame
    uint8_t m_unk2a;     // +0x2a (enemy +0x1ee) AssignFormationSlot: take a priority-0 slot only
    uint8_t m_unk2b;
    uint32_t m_flags;    // +0x2c (enemy +0x1f0) bits 0-1: the key's flags (AssignFormationSlot), SpawnMember sets 1
};
static_assert(sizeof(SEnemyFormation) == 0x30, "the enemy's +0x1c4 block");
// The enemy's vt+0xec (IKHkEnemy::VfEC): its formation block.
SEnemyFormation* FormationOf(IKSerializable* enemy);

class CKGrpSquad : public IKGroup<IKHook> {
public:
    DOTD_CLASS_KEY(kCategoryGroup, 0x18)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ba9c0
        return key == 0x604 || key == 0x17e || key == 0x4 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKGrpSquad)

    // XXL2 SGrpSquadState (_maybe): 0x6c bytes. CKGrpSquad_Phase_Init (0x263530) sets the vector only.
    struct SState {
        SState() {  // 0x00263530 CKGrpSquad_Phase_Init
            m_vUnk5c.m_pBlock = nullptr;
            m_vUnk5c.m_ui32NbElt = 1;
            m_vUnk5c.m_ui32NbUsedElt = 0;
        }
        // 0x002638e8 CKGrpSquad_Phase_Release (the state's destructor; the Load and the squad's destructors call it): the
        // per-type kill vector's block freed when there is one.
        void Release() {
            if (m_vUnk5c.m_pBlock != nullptr) Mem_FreeAligned16(m_vUnk5c.m_pBlock);
        }
        CMatrix34* m_pMatrix;        // +0x00 RwMatrixCreate + CMatrix34_LoadMatrix
        uint8_t m_unk04;             // +0x04
        uint8_t m_pad05[3];
        IKSerializable* m_pUnk08;    // +0x08 reference
        uint8_t m_unk0c;             // +0x0c the hero index for the enemy group's GetHeroMatrix (anchor modes)
        uint8_t m_pad0d[3];
        uint32_t m_unk10;            // +0x10 the anchor mode (UpdateAnchorFromPhase: 0..6)
        uint8_t m_unk14;             // +0x14
        uint8_t m_pad15[3];
        float m_unk18;               // +0x18 the anchor's squared distance threshold (UpdateAnchorFromPhase)
        uint8_t m_unk1c;             // +0x1c the member list (+0x44 index) ScheduleRespawns reads; 0xff: none
        uint8_t m_pad1d[3];
        float m_unk20[3];            // +0x20 one 0xc-byte read, three swaps
        IKSerializable* m_pUnk2c;    // +0x2c reference
        uint8_t m_unk30;             // +0x30
        uint8_t m_pad31[3];
        IKSerializable* m_pUnk34;    // +0x34 reference
        uint8_t m_unk38;             // +0x38
        uint8_t m_unk39;             // +0x39
        uint8_t m_unk3a;             // +0x3a
        uint8_t m_pad3b;
        IKSerializable* m_pUnk3c;    // +0x3c reference
        float m_unk40[5];            // +0x40 the spawn camera time (+0x40), its switch time (+0x44), +0x48, the spawn
                                     // delay (+0x4c, against the squad's +0x98) and the phase duration (+0x50)
        float m_unk54;               // +0x54 not read; the phase's time left (from +0x50; Update counts it down)
        int32_t m_unk58;             // +0x58 the kill count that ends the phase (Update)
        TVector<uint32_t, 1> m_vUnk5c;  // +0x5c per enemy type, the kill count that ends the phase (read as signed)
        uint8_t m_unk68;             // +0x68
        uint8_t m_unk69;             // +0x69 Update: the phase does not end on kills
        uint8_t m_unk6a;             // +0x6a Update: every per-type kill count must be reached (else one)
        uint8_t m_pad6b;
    };
    // 0x20 bytes: two bytes, two word vectors and a word.
    struct SMemberEntry {
        uint8_t m_unk00;                  // +0x00
        uint8_t m_unk01;                  // +0x01
        uint8_t m_pad02[2];
        TVector<uint32_t, 1> m_vUnk04;    // +0x04
        TVector<uint32_t, 1> m_vUnk10;    // +0x10
        uint32_t m_unk1c;                 // +0x1c
    };
    // 4 bytes per enemy type: two bytes the Load clears and two run-time counters.
    struct SFlags {
        uint8_t m_unk00;   // +0x00 the members of the type (spawned or transferred in)
        uint8_t m_unk01;   // +0x01
        uint8_t m_unk02;   // +0x02 the type's pending spawns (CKGrpFightZone_TrySpawnRequest_maybe)
        uint8_t m_unk03;   // +0x03 the type's pending transfers (CKGrpFightZone_ProcessSquadTransfers_maybe)
    };

    // 0x0025b4c0 CKGrpSquad_Create (the constructor 0x25aa10 inlined): the vectors null, 1, 0; +0x50 = 0;
    // the priority word 0x80000013.
    CKGrpSquad() {
        m_vUnk2c.m_pBlock = nullptr;
        m_vUnk2c.m_ui32NbElt = 1;
        m_vUnk2c.m_ui32NbUsedElt = 0;
        m_vUnk38.m_pBlock = nullptr;
        m_vUnk38.m_ui32NbElt = 1;
        m_vUnk38.m_ui32NbUsedElt = 0;
        m_vUnk44.m_pBlock = nullptr;
        m_vUnk44.m_ui32NbElt = 1;
        m_vUnk44.m_ui32NbUsedElt = 0;
        m_unk50 = nullptr;
        m_vStates.m_pBlock = nullptr;
        m_vStates.m_ui32NbElt = 1;
        m_vStates.m_ui32NbUsedElt = 0;
        m_vUnka8.m_pBlock = nullptr;
        m_vUnka8.m_ui32NbElt = 1;
        m_vUnka8.m_ui32NbUsedElt = 0;
        m_vUnkb4.m_pBlock = nullptr;
        m_vUnkb4.m_ui32NbElt = 1;
        m_vUnkb4.m_ui32NbUsedElt = 0;
        m_vUnkc0.m_pBlock = nullptr;
        m_vUnkc0.m_ui32NbElt = 1;
        m_vUnkc0.m_ui32NbUsedElt = 0;
        m_ui32Priority = 0x80000013u;
    }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0025e4f0 CKGrpSquad_Load
    // vt+0x10 0x0025e430 CKGrpSquad_Destroy: no child groups (+0x18), no members (vt+0xb0's head), each state's matrix
    // and the current matrix (+0x64) destroyed (RwMatrixDestroy_Thunk; the pointers are kept).
    void Destroy() override;
    void Start() override;  // vt+0x50 0x0025d6c8 CKGrpSquad_Start
    // vt+0x54 0x0025d698 CKGrpSquad_Restart: the spawn camera off (+0x94), the current state's time left back to its
    // duration (+0x54 = +0x50), the spawn camera not started (+0xcc).
    void Restart() override {
        const uint8_t current = m_unk55;
        m_unk94 = 0;
        m_vStates.m_pBlock[current].m_unk54 = m_vStates.m_pBlock[current].m_unk40[4];
        m_unkcc = 0;
    }
    // vt+0x38 0x0025d650 CKGrpSquad_SetDefaultState: the stored phase (+0x54) 0.
    void SetDefaultState(int32_t /*flag*/) override { m_unk54 = 0; }
    // vt+0x3c 0x0025d660 CKGrpSquad_SetGameState: info 9 only (0 otherwise): the stored phase (+0x54) = the state's
    // low byte; 1.
    int32_t SetGameState(const SApplyGameState* state) override {
        if (state->m_ui32InfoId != 9) return 0;
        m_unk54 = static_cast<uint8_t>(state->m_ui32GameStateId);
        return 1;
    }
    // vt+0x24 0x0025e2b0 CKGrpSquad_RecursiveRegistration: IKGroup_LevelReset 0x12a68, then for a level file (type 0)
    // every state's choreography (+0x34, type 0; not tested for null) and the squad registered with the saving manager;
    // the five trigger starters register nothing (KStub_Return1_2361b0).
    void RecursiveRegistration(int32_t type) override;
    int32_t PostLoad(int32_t type) override;  // vt+0x30 0x0025e008 CKGrpSquad_PostLoad
    // 0x0025afe0 CKGrpSquad_ResetMemberSlots_maybe (not virtual): the member-position vector (+0xa8) is zeroed and
    // grown to one slot per member of the parent enemy group (its +0x54 count, low byte).
    void ResetMemberSlots();
    void Update(IKTime* clock) override;                       // vt+0x7c 0x0025d940 UpdateCKGrpSquad
    int32_t MessageProc(uint16_t message, void* data) override;  // vt+0x1c 0x0025de60 CKGrpSquad_MessageProc
    void Vf94() override;                                      // vt+0x94 0x0025d7b0 CKGrpSquad_vf94 (woken)
    void Vf98() override;                                      // vt+0x98 0x0025ddf0 CKGrpSquad_StopFight_maybe (put to sleep)
    void OnLock() override;                                    // vt+0xa8 0x0025d718 CKGrpSquad_vfA8
    void OnUnlock() override;                                  // vt+0xac 0x0025d8a8 CKGrpSquad_vfAC
    class CKGrpFightZone* GetFightZone();      // 0x0025ab50 CKGrpSquad_GetFightZone: the parent group
    class CKChoreoKey* CurrentKey();           // CKChoreography_GetCurrentKey_maybe 0x2649e8 of the phase's choreography
    void ActivateSpawnCamera();                // 0x0025b160 CKGrpSquad_ActivateSpawnCamera_maybe
    void UpdateChoreography(IKTime* clock);    // 0x0025b600 CKGrpSquad_UpdateChoreography_maybe
    void AssignFormationSlot(IKSerializable* member);  // 0x0025bd50 CKGrpSquad_AssignFormationSlot_maybe
    void SetPhase(uint8_t phase);              // 0x0025c278 CKGrpSquad_SetPhase_maybe
    void ApplyPendingChoreography();           // 0x0025ca10 CKGrpSquad_ApplyPendingChoreography_maybe
    void AssignAllFormationSlots();            // 0x0025cc48 CKGrpSquad_AssignAllFormationSlots_maybe
    void FaceNearestHero();                    // 0x0025ccd8 CKGrpSquad_FaceNearestHero_maybe
    void UpdateAnchorFromPhase(IKTime* clock); // 0x0025ceb8 CKGrpSquad_UpdateAnchorFromPhase_maybe
    void SetStoredPhase(uint8_t phase);        // 0x0025aca8 CKGrpSquad_SetStoredPhase_maybe
    uint8_t HasSpawnRequest();                 // 0x002604c0 CKGrpSquad_HasSpawnRequest_maybe
    void ClearSpawnCountsAndRespawnQueue();    // 0x00260568 CKGrpSquad_ClearSpawnCountsAndRespawnQueue_maybe
    void ReturnEnemyToFightZonePool(uint8_t type, IKSerializable* enemy);  // 0x00260668
    void ReleaseMember(IKSerializable* member);  // 0x00260748 CKGrpSquad_ReleaseMember_maybe
    IKSerializable* TakeEnemyFromFightZonePool(uint8_t type);  // 0x002608c8
    void ProcessDeadMembers();                 // 0x00260a88 CKGrpSquad_ProcessDeadMembers_maybe
    void ReleaseAllMembers();                  // 0x00260db0 CKGrpSquad_ReleaseAllMembers_maybe
    // 0x00260f38 CKGrpSquad_SpawnMember_maybe: an enemy of `type` taken from the fight zone's pool and made a member,
    // or null.
    IKSerializable* SpawnMember(uint8_t type);
    void QueueSpawnsToFillFormation(uint32_t type);  // 0x00261280 CKGrpSquad_QueueSpawnsToFillFormation_maybe
    void SpawnPendingMembers();                // 0x00261928 CKGrpSquad_SpawnPendingMembers_maybe
    void SpawnFullFormation();                 // 0x00261e00 CKGrpSquad_SpawnFullFormation_maybe (0x2620e8 jumps to it)
    void ProcessRespawnTimers(IKTime* clock);  // 0x002620f0 CKGrpSquad_ProcessRespawnTimers_maybe
    void ScheduleRespawns();                   // 0x002623d8 CKGrpSquad_ScheduleRespawns_maybe
    // vt+0x40 0x0025fda0 CKGrpSquad_GetInfo: the trigger values 0 (in phase `arg`), 1 (the members of type `arg`), 2 (all
    // members), 3 (the current key's slots of type `arg`), 4 (the nearest controlled hero's horizontal distance), 0xd (the
    // horizontal distance to the zone's point `arg`), 0x10 (the current phase's key index).
    int32_t GetInfo(IKInfo* info, int32_t request) override;
    // 0x00260008 CKGrpSquad_GetTypeCountTotal_maybe: the four per-type counters summed (a signed byte).
    int8_t GetTypeCountTotal(uint32_t type) const {
        const SFlags& flags = m_vUnk2c.m_pBlock[type];
        return static_cast<int8_t>(flags.m_unk00 + flags.m_unk01 + flags.m_unk02 + flags.m_unk03);
    }
    // 0x002600f0 CKGrpSquad_CountChoreoSlotsOfType_maybe: the current key's positions of `type` (0 without a key).
    uint32_t CountChoreoSlotsOfType(uint8_t type);
    // 0x00261818 CKGrpSquad_GetMissingSpawnCountForType_maybe: the current key's positions of `type` minus the type's
    // members and pending counts, when not negative (else 0).
    uint8_t GetMissingSpawnCountForType(uint32_t type);

    TVector<SFlags, 1> m_vUnk2c;                      // +0x2c
    TVector<uint8_t, 1> m_vUnk38;                     // +0x38
    TVector<TVector<SMemberEntry, 1>, 1> m_vUnk44;    // +0x44
    // A queued respawn (16 bytes, FreeListPool 0x00ceaa20's 16-byte pool in the original; list +0x50).
    struct SRespawnNode {
        uint8_t m_kind;              // +0x00 1: QueueSpawnsToFillFormation, 2: one more pending, 3: +0x08 more pending
        uint8_t m_type;              // +0x01
        uint8_t m_pad02[2];
        float m_fTimer;              // +0x04
        uint32_t m_count;            // +0x08 kind 3's count (kinds 1 and 2 store the squad's address there; unread)
        SRespawnNode* m_pNext;       // +0x0c
    };
    SRespawnNode* m_unk50;                            // +0x50 the queued respawns (ScheduleRespawns)
    uint8_t m_unk54;                                  // +0x54 not set; the phase the squad restarts in (SetStoredPhase)
    uint8_t m_unk55;                                  // +0x55 the Load clears it
    uint8_t m_pad56[2];
    TVector<SState, 1> m_vStates;                     // +0x58
    CMatrix34* m_pCurrentMatrix;                      // +0x64 a copy of the first state's matrix
    CTriggerStarter m_tsUnk68;                        // +0x68
    CTriggerStarter m_tsUnk70;                        // +0x70
    CTriggerStarter m_tsUnk78;                        // +0x78
    CTriggerStarter m_tsUnk80;                        // +0x80
    CTriggerStarter m_tsUnk88;                        // +0x88
    float m_unk90;                                    // +0x90 not set; the spawn camera's time (Update)
    uint8_t m_unk94;                                  // +0x94 runtime (Start: 0): the spawn camera runs
    uint8_t m_pad95[3];
    float m_unk98;                                    // +0x98 the time in the phase (up to the state's +0x4c)
    SState* m_pStartState;                            // +0x9c &m_vStates[index] for a file index >= 1, else 0
    uint8_t m_unka0;                                  // +0xa0
    uint8_t m_pada1[3];
    int32_t m_unka4;                                  // +0xa4 not set; the members killed in this phase
    TVector<uint32_t, 1> m_vUnka8;                    // +0xa8 runtime (constructor only): kills per enemy type
    TVector<uint8_t, 1> m_vUnkb4;                     // +0xb4 runtime: per enemy type, the first spawn is still to come
    TVector<uint8_t, 1> m_vUnkc0;                     // +0xc0 runtime: per enemy type, its pending spawns are done
    uint8_t m_unkcc;                                  // +0xcc runtime (Start: 0): the spawn camera was started
    uint8_t m_padcd[3];
};
DOTD_ASSERT_SIZE(CKGrpSquad::SState, 0x6c);
DOTD_ASSERT_OFFSET(CKGrpSquad::SState, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKGrpSquad::SState, m_pUnk3c, 0x3c);
DOTD_ASSERT_OFFSET(CKGrpSquad::SState, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKGrpSquad::SState, m_vUnk5c, 0x5c);
DOTD_ASSERT_OFFSET(CKGrpSquad::SState, m_unk68, 0x68);
DOTD_ASSERT_SIZE(CKGrpSquad::SMemberEntry, 0x20);
DOTD_ASSERT_OFFSET(CKGrpSquad::SMemberEntry, m_vUnk10, 0x10);
DOTD_ASSERT_SIZE(CKGrpSquad, 0xd0);
DOTD_ASSERT_OFFSET(CKGrpSquad, m_vUnk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKGrpSquad, m_vUnk38, 0x38);
DOTD_ASSERT_OFFSET(CKGrpSquad, m_vUnk44, 0x44);
DOTD_ASSERT_OFFSET(CKGrpSquad, m_unk55, 0x55);
DOTD_ASSERT_OFFSET(CKGrpSquad, m_vStates, 0x58);
DOTD_ASSERT_OFFSET(CKGrpSquad, m_pCurrentMatrix, 0x64);
DOTD_ASSERT_OFFSET(CKGrpSquad, m_tsUnk68, 0x68);
DOTD_ASSERT_OFFSET(CKGrpSquad, m_tsUnk88, 0x88);
DOTD_ASSERT_OFFSET(CKGrpSquad, m_pStartState, 0x9c);
DOTD_ASSERT_OFFSET(CKGrpSquad, m_unka0, 0xa0);
DOTD_ASSERT_OFFSET(CKGrpSquad, m_vUnkc0, 0xc0);
