// IKGrpEnemy.h - the unregistered base of the enemy groups (key 0x9c4, vtable 0xb21478, size 0x124).
// Original units: IKGrpEnemy.cpp (k2000/misc: 0x2667e0 Load; Spyro2008/groups: the runtime) and
// CKGrpS08Enemy.cpp (0x265d50 the constructor, Ghidra CKGrpS08Enemy_ConstructBase_maybe). XXL2:
// Commun/K/KEnemy/IKGrpEnemy.h (m_pPoolGrpRoot, m_vpFZSectorGrpRoot, m_vDamageTypeConfig, m_apEnemies).
// DotD's Load reads three reference vectors (XXL2: one vector of SEnemyDamageType, then a reference and a
// reference vector), so only the reference and the vector XXL2 reads after it keep XXL2's names.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/groups/IKBaseGroup.h"
#include "k2000/util/TVector.h"

class CKGrpFightZone;
struct CVector3;

class IKGrpEnemy : public IKGroup<IKHook> {
public:
    // 0x00265d50 CKGrpS08Enemy_ConstructBase_maybe (the IKGrpEnemy constructor).
    IKGrpEnemy() {
        m_vpFZSectorGrpRoot = {nullptr, 1, 0};
        m_vUnk40 = {nullptr, 1, 0};
        m_vUnk4c = {nullptr, 1, 0};
        m_ui32Priority = 0x80000015u;
        m_ui32NbActiveEnemies = 0;
    }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x002667e0 IKGrpEnemy_Load
    // C2.2 spyro: vt+0x50 0x002659d8 IKGrpEnemy_ResetRuntime (Ghidra IKGrpEnemy_Start): clears +0x30.
    void Start() override;
    // vt+0x54 0x002659f8 IKGrpEnemy_ReinitRuntime: the same (+0x30 cleared).
    void Restart() override;
    int32_t PostLoad(int32_t type) override;  // vt+0x30 0x00265b08 IKGrpEnemy_PostLoad
    void Destroy() override;  // vt+0x10 0x00266240 IKGrpEnemy_ClearReferences (IKGrpEnemy_2.cpp)
    // port-all P22 (IKGrpEnemy.cpp / IKGrpEnemy_2.cpp):
    // vt+0x1c 0x00265ee0 IKGrpEnemy_HandleMessage: the beacons' save (0x1000) and load (0x1001) through the beacon
    // message (CKSrvBeacon::SKBeaconMsg): per beacon three little-endian halves and a raw one, the accessor's +0x1e
    // counted up; 0 for them, 1 for the others.
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x24 0x002661f0 IKGrpEnemy_LevelReset: IKGroup's (0x12a68) only, IKBaseGroup's inherited.
    // vt+0x7c 0x002659f0 IKGrpEnemy_vf7C: empty (IKBaseGroup's Update). vt+0xb8 0x002659d0 IKGrpEnemy_vfB8 and vt+0x150
    // 0x00265a08 IKGrpEnemy_vf150 return 1, KStub_Return0_265a18 (another slot, also reached through a TOC bridge) 0:
    // CKGrpS08Enemy overrides them or nothing ported calls them (see CKGrpS08Enemy.h; CKProjectileTypeBallisticPFX.cpp
    // has 0x265a18 inline as EnemyGroupHazardSource).
    // The save record of the group (vt+0x168 / +0x16c / +0x170; no ported caller yet): the record allocated zeroed
    // (0x28 bytes), saved (its floats +0x08, +0x0c, +0x10 little-endian, then the byte +0x24) and loaded the same way.
    struct SSaveRecord {
        uint32_t m_unk00[2];  // +0x00
        float m_unk08;        // +0x08
        float m_unk0c;        // +0x0c
        float m_unk10;        // +0x10
        uint32_t m_unk14[4];  // +0x14
        uint8_t m_unk24;      // +0x24
        uint8_t m_pad25[3];
    };
    virtual void* AllocSaveRecord();                                     // 0x00265b48 IKGrpEnemy_vf168
    virtual void SaveRecord(IKFile* file, void* unused, void* record);   // 0x00266468 IKGrpEnemy_vf16C
    virtual void LoadRecord(IKFile* file, void* unused, void* record);   // 0x00266320 IKGrpEnemy_vf170
    // Per-kind constants the enemies take from the group (CKGrpS08Enemy returns table entries; names ours).
    virtual uint8_t GetNbAnimLayers(uint8_t kind) = 0;                       // vt+0x108 CKGrpS08Enemy_vf108 (0x00a6fed8)
    virtual uint8_t GetNbTrailNodes(uint8_t kind) = 0;                       // vt+0x128 CKGrpS08Enemy_vf128 (0x00a6ff48)
    virtual uint8_t GetNbAnimLayerSlots(uint8_t kind, uint8_t layer) = 0;    // vt+0x130 CKGrpS08Enemy_vf130 (0x00a6ff68)
    // vt+0xec (pure here; CKGrpS08Enemy 0x9bb648): a fight zone is current and its flag bit 0 is set.
    virtual uint8_t IsInFight() = 0;
    // vt+0xf0 (pure here; CKGrpS08Enemy 0x9bb668): a fight zone is current and its flag bit 1 is set ("a fight is on":
    // IKGrpHero_Update's +0xf8 bit 10).
    virtual uint8_t IsFightOn() = 0;
    virtual uint8_t GetNbEnemyKinds() = 0;     // vt+0xf4 (pure here; CKGrpS08Enemy 0x9bb4e0: 9)
    virtual uint8_t GetSpawnFlagBits() = 0;    // vt+0x158 (pure here; CKGrpS08Enemy 0x9bb608: 2; the fight zone masks its spawn flags with it)
    // vt+0x15c 0x00265a20 IKGrpEnemy_vf15C: the zone becomes the current one unless one is.
    virtual void SetCurrentFightZone(CKGrpFightZone* zone) {
        if (m_pCurrentFightZone == nullptr) m_pCurrentFightZone = zone;
    }
    // vt+0x160 0x00265a38 IKGrpEnemy_vf160: the current zone is cleared when it is `zone`.
    virtual void ClearCurrentFightZone(CKGrpFightZone* zone) {
        if (m_pCurrentFightZone == zone) m_pCurrentFightZone = nullptr;
    }
    // 0x00265a50 AddActiveEncounterEnemy: appended to the active enemies (no bound check, as the original).
    void AddActiveEnemy(IKSerializable* enemy) { m_apActiveEnemies[m_ui32NbActiveEnemies++] = enemy; }
    // 0x00265a78 RemoveActiveEncounterEnemy: removed from the active enemies, the last one taking its place.
    void RemoveActiveEnemy(IKSerializable* enemy);
    // 0x002665a0 IKGrpEnemy_IsAnyEnemyInCone_maybe: 1 when an active enemy (the last first) is nearer than `maxDistance`
    // to `position` (not less: NaN skips) and the cosine of its direction (normalised unless zero) with `direction` is not
    // below cos(`angle`) (the game's inlined cosine, the library's for a negative angle). Callers:
    // CKHkPushObstacle_UpdateHeroInteraction_maybe / _CanPushInDirection_maybe (not ported).
    uint8_t IsAnyEnemyInCone(float angle, float maxDistance, const CVector3* position, const CVector3* direction);

    IKSerializable* m_pPoolGrpRoot;                     // +0x2c XXL2 CKCommonBaseGroup* m_pPoolGrpRoot
    CKGrpFightZone* m_pCurrentFightZone;                // +0x30 the fight zone whose fight runs (vt+0x15c / +0x160)
    TVector<IKSerializable*, 1> m_vpFZSectorGrpRoot;    // +0x34 XXL2 m_vpFZSectorGrpRoot (read after the reference)
    TVector<IKSerializable*, 1> m_vUnk40;               // +0x40 references (DotD only)
    TVector<IKSerializable*, 1> m_vUnk4c;               // +0x4c references, read first (XXL2's m_vDamageTypeConfig place _maybe)
    IKSerializable* m_apActiveEnemies[50];              // +0x58..+0x11c the active enemies (AddActiveEncounterEnemy; not loaded)
    uint32_t m_ui32NbActiveEnemies;                        // +0x120 Ghidra dwActiveEnemyCount (AddActiveEncounterEnemy)
};
DOTD_ASSERT_SIZE(IKGrpEnemy, 0x124);
DOTD_ASSERT_OFFSET(IKGrpEnemy, m_pPoolGrpRoot, 0x2c);
DOTD_ASSERT_OFFSET(IKGrpEnemy, m_vpFZSectorGrpRoot, 0x34);
DOTD_ASSERT_OFFSET(IKGrpEnemy, m_vUnk40, 0x40);
DOTD_ASSERT_OFFSET(IKGrpEnemy, m_vUnk4c, 0x4c);
DOTD_ASSERT_OFFSET(IKGrpEnemy, m_pCurrentFightZone, 0x30);
DOTD_ASSERT_OFFSET(IKGrpEnemy, m_apActiveEnemies, 0x58);
DOTD_ASSERT_OFFSET(IKGrpEnemy, m_ui32NbActiveEnemies, 0x120);
