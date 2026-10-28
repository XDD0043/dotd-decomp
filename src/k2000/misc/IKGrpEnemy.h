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

class IKGrpEnemy : public IKGroup<IKHook> {
public:
    // 0x00265d50 CKGrpS08Enemy_ConstructBase_maybe (the IKGrpEnemy constructor).
    IKGrpEnemy() {
        m_vpFZSectorGrpRoot = {nullptr, 1, 0};
        m_vUnk40 = {nullptr, 1, 0};
        m_vUnk4c = {nullptr, 1, 0};
        m_ui32Priority = 0x80000015u;
        m_activeEnemyCount = 0;
    }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x002667e0 IKGrpEnemy_Load
    // C2.2 spyro: vt+0x50 0x002659d8 IKGrpEnemy_ResetRuntime (Ghidra IKGrpEnemy_Start): clears +0x30.
    void Start() override;
    // Per-kind constants the enemies take from the group (CKGrpS08Enemy returns table entries; names ours).
    virtual uint8_t GetNbAnimLayers(uint8_t kind) = 0;                       // vt+0x108 CKGrpS08Enemy_vf108 (0x00a6fed8)
    virtual uint8_t GetNbTrailNodes(uint8_t kind) = 0;                       // vt+0x128 CKGrpS08Enemy_vf128 (0x00a6ff48)
    virtual uint8_t GetNbAnimLayerSlots(uint8_t kind, uint8_t layer) = 0;    // vt+0x130 CKGrpS08Enemy_vf130 (0x00a6ff68)

    IKSerializable* m_pPoolGrpRoot;                     // +0x2c XXL2 CKCommonBaseGroup* m_pPoolGrpRoot
    uint32_t m_unk30;                                   // +0x30
    TVector<IKSerializable*, 1> m_vpFZSectorGrpRoot;    // +0x34 XXL2 m_vpFZSectorGrpRoot (read after the reference)
    TVector<IKSerializable*, 1> m_vUnk40;               // +0x40 references (DotD only)
    TVector<IKSerializable*, 1> m_vUnk4c;               // +0x4c references, read first (XXL2's m_vDamageTypeConfig place _maybe)
    uint32_t m_unk58[(0x120 - 0x58) / 4];               // +0x58..+0x11c run-time state (not loaded)
    uint32_t m_activeEnemyCount;                        // +0x120 Ghidra dwActiveEnemyCount (AddActiveEncounterEnemy)
};
DOTD_ASSERT_SIZE(IKGrpEnemy, 0x124);
DOTD_ASSERT_OFFSET(IKGrpEnemy, m_pPoolGrpRoot, 0x2c);
DOTD_ASSERT_OFFSET(IKGrpEnemy, m_vpFZSectorGrpRoot, 0x34);
DOTD_ASSERT_OFFSET(IKGrpEnemy, m_vUnk40, 0x40);
DOTD_ASSERT_OFFSET(IKGrpEnemy, m_vUnk4c, 0x4c);
DOTD_ASSERT_OFFSET(IKGrpEnemy, m_activeEnemyCount, 0x120);
