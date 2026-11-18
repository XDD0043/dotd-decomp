// CKGrpS08BonusPool.h - Spyro's bonus pool (key 0x7c4, size 0x70). Original unit: CKGrpS08BonusPool.cpp
// (0x5af6a8-0x5b0c58, TOC2). A CKGrpBonusPool with one more reference.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/memory/CKGrpBonusPool.h"

class CKGrpS08BonusPool : public CKGrpBonusPool {
public:
    DOTD_CLASS_KEY(kCategoryGroup, 0x1f)
    DOTD_DECLARE_FACTORIES(CKGrpS08BonusPool)

    CKGrpS08BonusPool() {}  // 0x005b0640 CKGrpS08BonusPool_Create: the bases only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005b08b0 CKGrpS08BonusPool_Load
    // vt+0x50 0x005b0560 CKGrpS08BonusPool_vf50: empty (IKBaseGroup's Start). (0x005b0bc8 CKGrpBonus_ResetRuntime is
    // CKGrpBonus's Start.)
    // vt+0xf4 0x005afa90 CKGrpS08BonusPool_UpdateBonuses_maybe: CKGrpBonusPool's (0x5b28e8).
    void UpdateBonuses(IKTime* frameClock) override { CKGrpBonusPool::UpdateBonuses(frameClock); }
    // vt+0x124 0x005afd78 CKGrpS08BonusPool_CanHeroCollect_maybe: a hero the player does not control takes a health /
    // mana bonus (types 1 / 2) only while his gauge is below his partner's and the partner's is at least 65% full, no
    // gem (3..6); Spyro's elemental bonuses (7..9) only Spyro, Cynder's (10..12) only Cynder.
    // vt+0x120 0x005af7d0 CKGrpS08BonusPool_vf120: a ground none of whose property bits 2..4 (0x1c) is set.
    int32_t Vf120(IKSerializable* ground) override;
    uint8_t CanHeroCollect(IKSerializable* hero) override;
    // vt+0x12c 0x005affd0 CKGrpS08BonusPool_ApplyBonusToHero_maybe: the pool type's effect on the game manager's stats
    // (health, mana, gems / upgrade points, the shards' HUD, the shared upgrade points).
    void ApplyBonusToHero(IKSerializable* hero, IKSerializable* bonus) override;
    // port-all P22:
    // vt+0x1c 0x005afab8 CKGrpS08BonusPool_vf1C (MessageProc): CKGrpBonusPool's, its result kept when 2 or 3, else 1 for
    // any non-zero result and 0 for 0.
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x24 0x005afb38 CKGrpS08BonusPool_LevelReset: CKGrpBonusPool's, then outside the types 4..7 the pool registered
    // with the saving manager and +0x6c's registration.
    void RecursiveRegistration(int32_t type) override;
    // vt+0x7c 0x005b0540 UpdateCKGrpS08BonusPool, vt+0x68 0x005b0550 vf68, vt+0x70 0x005b0558 vf70, vt+0x78 0x005b0548
    // vf78: empty (IKBaseGroup's Update / Stop / Pause / Resume). vt+0xb8 0x005af7c8 vfB8 returns 0x3d: IKBaseGroup models
    // no slot there and no ported code calls it. vt+0x128 0x005af7f8 vf128 returns 0 (CKGrpBonusPool::IsCatcherChanged's answer, inherited).
    // 0x005b0a58 _DeletingDestructor: the implicit destructor. 0x005af6a8 (Ghidra _Destroy): the Delete factory.
    // 0x005af800 CKGrpBonusPool_PlayCollectFx_maybe: an explosion of +0x6c's data at `position`.
    void PlayCollectFx(const CVector3* position);

    IKSerializable* m_pUnk6c;  // +0x6c reference: the collect explosion's data
};
DOTD_ASSERT_SIZE(CKGrpS08BonusPool, 0x70);
DOTD_ASSERT_OFFSET(CKGrpS08BonusPool, m_pUnk6c, 0x6c);
