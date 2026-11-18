// CKHkTransportableObjectSpawner.h - spawns transportable objects (key 0x3042, vtable 0xb28920, size 0x78).
// Original unit: CKHkTransportableObjectSpawner.cpp (0x4a8688-0x4ac108). No XXL2 class. Field names are
// placeholders where the code does not say more.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/util/TVector.h"
#include "k2000/groups/CKGrpTransportableObject.h"

class CKHkTransportableObjectSpawner : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xc1)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c5210
        return key == 0x3042 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkTransportableObjectSpawner)

    // One entry of +0x40 (OperatorNew(0xc) in LoadSpawnEntries): a reference and two words set to 0.
    struct SpawnEntry {
        IKSerializable* m_pUnk0;  // +0x0 reference: a CSGHotSpot (TrySpawn hangs the transportable on it)
        float m_unk4;             // +0x4 0: the time since the entry's last spawn
        IKSerializable* m_unk8;   // +0x8 0; the entry's spawned transportable (Restart returns it)
    };

    // 0x004aae38 CKHkTransportableObjectSpawner_Create (inlined constructor, the same as the dead
    // 0x4a8bd0 CKHkTransportableObjectSpawner_Construct): the two vectors, empty with capacity 1.
    CKHkTransportableObjectSpawner() {
        m_vUnk2c.m_pBlock = nullptr;
        m_vUnk2c.m_ui32NbElt = 1;
        m_vUnk2c.m_ui32NbUsedElt = 0;
        m_vSpawnEntries.m_ui32NbElt = 1;
        m_vSpawnEntries.m_ui32NbUsedElt = 0;
        m_vSpawnEntries.m_pBlock = nullptr;
    }
    // 0x004a9e58 CKHkTransportableObjectSpawner_Destructor: the two vectors' blocks freed (Mem_FreeAligned16), their counts
    // and blocks cleared, then CKHkActorBase's.
    ~CKHkTransportableObjectSpawner() override {
        if (m_vSpawnEntries.m_pBlock != nullptr) Mem_FreeAligned16(m_vSpawnEntries.m_pBlock);
        m_vSpawnEntries.m_ui32NbUsedElt = 0;
        m_vSpawnEntries.m_pBlock = nullptr;
        if (m_vUnk2c.m_pBlock != nullptr) Mem_FreeAligned16(m_vUnk2c.m_pBlock);
        m_vUnk2c.m_ui32NbUsedElt = 0;
        m_vUnk2c.m_pBlock = nullptr;
    }

    void Destroy() override;  // vt+0x10 0x004a8d58 CKHkTransportableObjectSpawner_Destroy
    int32_t MessageProc(uint16_t message, void* data) override;  // vt+0x1c 0x004a8a90 CKHkTransportableObjectSpawner_MessageProc
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004aaeb8 CKHkTransportableObjectSpawner_Load
    void SetDefaultState(int32_t flag) override;  // vt+0x38 0x004a87b8 CKHkTransportableObjectSpawner_SetDefaultState
    // vt+0xc8 0x004a8700 CKHkTransportableObjectSpawner_ApplyStatePreset_maybe: spawning on (+0x24) when the preset (0 / 1)
    // equals the loaded byte +0x25, off otherwise. LVL010: the spawner of the upper stone has +0x25 = 1, so the level start
    // (preset 0) switches it off and only the lower stone's spawner puts the weight on its stone.
    void ApplyStatePreset(int32_t state) override {
        m_unk24 = static_cast<uint8_t>((state != 0) == (m_unk25 != 0) ? 1 : 0);
    }
    // vt+0x40 0x004a8a40 CKHkTransportableObjectSpawner_GetInfo: KStub_Return1_3f7140's answer (1) folded: 2 stays 2, 0
    // gives 0, anything else 1.
    int32_t GetInfo(struct IKInfo* info, int32_t request) override;
    void Start() override;                        // vt+0x50 0x004a9950 CKHkTransportableObjectSpawner_Start
    void Restart() override;                      // vt+0x54 0x004a9230 CKHkTransportableObjectSpawner_Restart
    // vt+0x68 0x004a8a18 CKHkTransportableObjectSpawner_Stop: CKHkActorBase_d82_maybe_Stop 0x3f6e50 (empty).
    void Stop() override {}
    void Update(IKTime* clock) override;          // vt+0x7c 0x004ab6d0 CKHkTransportableObjectSpawner_Update
    void VfA0() override;                         // vt+0xa0 0x004a9510 CKHkTransportableObjectSpawner_OnActivate
    void VfA4() override;                         // vt+0xa4 0x004a8fc8 CKHkTransportableObjectSpawner_OnDeactivate
    // 0x004a9b08 CKHkTransportableObjectSpawner_LoadSpawnEntries_maybe
    void LoadSpawnEntries(IKFile* file);
    // 0x004a87f0 CKHkTransportableObjectSpawner_IsPlayerHeroInRange_maybe (inlined by Update and the two tests below): a
    // player-controlled hero closer to the spawn point than +0x74 (any distance when +0x74 is 0).
    uint8_t IsPlayerHeroInRange() const;
    // 0x004ab368 CKHkTransportableObjectSpawner_CanSpawnNow_maybe / 0x004ab500 _CanSpawnAtTime_maybe (no bl caller in
    // callgraph.json: the same tests Update inlines).
    uint8_t CanSpawnNow() const;
    uint8_t CanSpawnAtTime(const SpawnEntry* entry) const;
    // 0x004a9f80 CKHkTransportableObjectSpawner_TrySpawn_maybe: a transportable on a spawn entry's hot spot.
    void TrySpawn(SpawnEntry* entry);
    // 0x004aa490 CKHkTransportableObjectSpawner_TrySpawnOntoReceiver_maybe: a transportable at the spawn point (or put on
    // the receiver +0x20).
    void TrySpawnOntoReceiver();

    IKSerializable* m_unk20;                    // +0x20 reference (LVL010: null or a CKHkPressionStone, key 0x542): the receiver
    // +0x24 spawning on: SetDefaultState 1, then the level start's preset (ApplyStatePreset); messages 0x996 / 0x997 set /
    // clear it.
    uint8_t m_unk24;
    uint8_t m_unk25;                            // +0x25 (LVL010: 0 or 1): the preset that keeps spawning on
    uint8_t m_pad26[2];
    IKSerializable* m_unk28;                    // +0x28 runtime (Start clears it): the spawned transportable
    // +0x2c the live transportables (m_unk4c slots; nulls sorted last by CKGrpTransportableObject_CompareNullsLast_maybe).
    TVector<IKSerializable*, 1> m_vUnk2c;
    CKGrpTransportableObject::Entry* m_pCurrentEntry;  // +0x38 runtime: the group's entry m_unk3c (Start)
    uint32_t m_unk3c;                           // +0x3c (LVL010: 2): the group's entry (pool) index
    TVector<SpawnEntry*, 1> m_vSpawnEntries;    // +0x40 LoadSpawnEntries
    uint32_t m_unk4c;                           // +0x4c (LVL010: 1): the number of live transportables
    float m_unk50;                              // +0x50 (LVL010: 0): the time between spawns
    float m_fSpawnTimer;                        // +0x54 runtime: the time since the last spawn
    uint32_t m_ui32SpawnCount;                  // +0x58 runtime: the number spawned
    IKSerializable* m_unk5c;                    // +0x5c reference
    CMatrix34* m_pMatrix;                       // +0x60 RwMatrixCreate in the Load: the spawn frame_maybe
    IKSerializable* m_unk64;                    // +0x64 reference (LVL010: a CKGrpTransportableObject)
    uint8_t m_unk68;                            // +0x68: at the count, recycle a live one
    uint8_t m_unk69;                            // +0x69 (read last): recycle only one not marked (vt+0x148)
    uint8_t m_pad6a[2];
    IKSerializable* m_unk6c;                    // +0x6c reference: a CKParticlesEffectFxData (the spawner's effect)
    IKSerializable* m_unk70;                    // +0x70 runtime: the effect (Restart releases it, vt+0x58)
    float m_unk74;                              // +0x74: the hero range (0: any distance)
};
DOTD_ASSERT_SIZE(CKHkTransportableObjectSpawner, 0x78);
DOTD_ASSERT_OFFSET(CKHkTransportableObjectSpawner, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkTransportableObjectSpawner, m_unk25, 0x25);
DOTD_ASSERT_OFFSET(CKHkTransportableObjectSpawner, m_vUnk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKHkTransportableObjectSpawner, m_unk3c, 0x3c);
DOTD_ASSERT_OFFSET(CKHkTransportableObjectSpawner, m_vSpawnEntries, 0x40);
DOTD_ASSERT_OFFSET(CKHkTransportableObjectSpawner, m_unk4c, 0x4c);
DOTD_ASSERT_OFFSET(CKHkTransportableObjectSpawner, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKHkTransportableObjectSpawner, m_fSpawnTimer, 0x54);
DOTD_ASSERT_OFFSET(CKHkTransportableObjectSpawner, m_ui32SpawnCount, 0x58);
DOTD_ASSERT_OFFSET(CKHkTransportableObjectSpawner, m_unk5c, 0x5c);
DOTD_ASSERT_OFFSET(CKHkTransportableObjectSpawner, m_pMatrix, 0x60);
DOTD_ASSERT_OFFSET(CKHkTransportableObjectSpawner, m_unk64, 0x64);
DOTD_ASSERT_OFFSET(CKHkTransportableObjectSpawner, m_unk68, 0x68);
DOTD_ASSERT_OFFSET(CKHkTransportableObjectSpawner, m_unk69, 0x69);
DOTD_ASSERT_OFFSET(CKHkTransportableObjectSpawner, m_unk6c, 0x6c);
DOTD_ASSERT_OFFSET(CKHkTransportableObjectSpawner, m_unk74, 0x74);
