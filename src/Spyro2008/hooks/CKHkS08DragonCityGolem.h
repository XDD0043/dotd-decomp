// CKHkS08DragonCityGolem.h - the Dragon City golem's hook (key 0x31c2, vtable 0xb29df0, size 0xe0). Original
// unit: CKHkS08DragonCityGolem.cpp. No XXL2 class. Its Load is CKHkGolem's.
//
// The heroes' damage volumes that touch the golem's attack volumes (ProcessDamageContacts, the attack's vt+0xa0) hurt
// it: a one-shot damage once per contact (the contact histories +0x20 and +0xc0), a continuous one (+0x0c set) kept
// per dragon (+0xc4 / +0xc8) and applied each frame (ApplyPendingDamage). The damage is scaled by the kind's factor
// (+0x94..) and gathered per dragon (+0xcc / +0xd0) until a whole point is reached.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/CKHkGolem.h"

class CKS08Damage;
class CKGolemAttackCommon;

class CKHkS08DragonCityGolem : public CKHkGolem {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xc7)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c5ec8
        return key == 0x31c2 || key == 0x3182 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe ||
               key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkS08DragonCityGolem)

    // 0x004d6468 CKHkS08DragonCityGolem_Create (inlined constructor): CKHkGolem's, then +0xc0 = 0.
    CKHkS08DragonCityGolem() { m_unkC0 = nullptr; }
    // 0x004d5f98 CKHkS08DragonCityGolem_DeletingDestructor (CKHkS08DragonCityGolem.cpp): the contacts (+0xc0) back to
    // their pool (ContactHistory_FreeNode), the list cleared, then CKHkGolem's.
    ~CKHkS08DragonCityGolem() override;

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004d5c38 CKHkS08DragonCityGolem_Load
    int32_t PostLoad(int32_t type) override;  // vt+0x30 0x004d5c10 CKHkS08DragonCityGolem_PostLoad
    void Start() override;  // vt+0x50 0x004d5bb8 CKHkS08DragonCityGolem_Start (C2.2)
    void Restart() override;  // vt+0x54 0x004d5b38 CKHkS08DragonCityGolem_Restart
    void Stop() override { CKHkGolem::Stop(); }  // vt+0x68 0x004d5b90 CKHkS08DragonCityGolem_Stop
    void Update(IKTime* clock) override;  // vt+0x7c 0x004d5a78 CKHkS08DragonCityGolem_Update
    uint32_t GetMaxExplosionMark() override { return 100; }  // vt+0x100 0x004d5468
    uint32_t GetMaxParticleMark() override { return 0x1b; }  // vt+0x104 0x004d5470
    uint32_t GetMaxLauncherMark() override { return 1; }     // vt+0x108 0x004d5478
    // vt+0x120 0x004d64c8 CKHkS08DragonCityGolem_ProcessDamageContacts_maybe (the attack's volumes, +0x08)
    void ProcessContacts(IKTime* clock, CKGolemAttackCommon* attack) override;
    // 0x004d6020 CKHkS08DragonCityGolem_GetNearestAimVolume_maybe: the point of the current attack phase's aim volumes
    // nearest to `from` into `out` and its squared distance; without an attack phase the "no point" and FLT_MAX.
    float GetNearestAimVolume(struct CVector3* out, const struct CVector3* from);
    // 0x004d5480 CKHkS08DragonCityGolem_AccumulateDamage_maybe: `amount` scaled by the damage's kind into dragon
    // `slot`'s pending damage; its whole part, when there is one, is applied (ApplyDamagePoints).
    void AccumulateDamage(float amount, CKS08Damage* damage, uint32_t slot);
    // 0x004d5728 CKHkS08DragonCityGolem_ApplyPendingDamage_maybe: the dragons' continuous damages of this frame.
    void ApplyPendingDamage(IKTime* clock);

    ContactHistoryNode* m_unkC0;  // +0xc0 constructor 0: the contacts of the damages with +0x26 set
    CKS08Damage* m_unkC4[2];      // +0xc4 runtime: each dragon's continuous damage this frame
    float m_unkCC[2];             // +0xcc runtime: each dragon's pending damage (below one point)
    uint8_t m_unkD4[2];           // +0xd4 runtime: each dragon's continuous damage runs
    uint8_t m_padD6[2];
    float m_unkD8[2];             // +0xd8 runtime: each dragon's time since its last hit count (OnNewHitW_2)
};
DOTD_ASSERT_SIZE(CKHkS08DragonCityGolem, 0xe0);
DOTD_ASSERT_OFFSET(CKHkS08DragonCityGolem, m_unkC0, 0xc0);
DOTD_ASSERT_OFFSET(CKHkS08DragonCityGolem, m_unkC4, 0xc4);
DOTD_ASSERT_OFFSET(CKHkS08DragonCityGolem, m_unkCC, 0xcc);
DOTD_ASSERT_OFFSET(CKHkS08DragonCityGolem, m_unkD4, 0xd4);
DOTD_ASSERT_OFFSET(CKHkS08DragonCityGolem, m_unkD8, 0xd8);
