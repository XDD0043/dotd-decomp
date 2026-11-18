// CKHkS08Enemy.h - Spyro's enemy hook (key 0x26c2, vtable 0xb22078, size 0x8f8). Original units:
// CKHkS08Enemy.cpp (constructor, IKHkEnemy) and CKHkS08Enemy_2.cpp..CKHkS08Enemy_16.cpp (Load in _9). No XXL2
// class of this name; derives from IKHkEnemy.
//
// A second base sits at +0x1c0 (vtable 0xb21458: destructors, a no-op, Save 0x265550, Load 0x265870; Ghidra
// Vt_b21458_*): not modelled yet, its vtable word is a plain field. An embedded CKS08Damage sits at +0x8bc
// (CKS08Damage_Construct 0x4ebc70, the combat family's class).
#pragma once
#include <cstdint>

#include "Spyro2008/hooks/IKHkEnemy.h"
#include "Spyro2008/logic/CKS08Damage.h"
#include "k2000/core/Layout.h"
#include "k2000/memory/Mem.h"
#include "k2000/util/TVector.h"

class CKDamage;
class CSGHotSpot;

class CKS08EnemyCpnt;
class CKS08GameManager;
class ICollision;
class IKBoundingVolume;

// One recent attacker of an enemy (+0x208, 0xc bytes).
struct SEnemyHitAttacker {
    IKSerializable* m_pAttacker;  // +0x00
    uint8_t m_bTouching;          // +0x04
    uint8_t m_pad05[3];
    float m_fCooldown;            // +0x08
};
DOTD_ASSERT_SIZE(SEnemyHitAttacker, 0xc);

class CKHkS08Enemy : public IKHkEnemy {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x9b)
    DOTD_DECLARE_FACTORIES(CKHkS08Enemy)

    // vt+0x08 0x009bc930 CKHkS08Enemy_IsKindOfClass: 0x26c2, then IKHkEnemy's.
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x26c2 || IKHkEnemy::IsKindOfClass(key); }

    CKHkS08Enemy();  // 0x0027d548 CKHkS08Enemy_Construct (inlined in CKHkS08Enemy_Create 0x27e408)
    // 0x0027ea88 CKHkS08Enemy_Destructor: the five vectors' blocks freed (+0x514 first; the embedded CKS08Damage's and
    // the bases' destructors are vtable-only).
    ~CKHkS08Enemy() override {
        if (m_unk514.m_pBlock != nullptr) Mem_FreeAligned16(m_unk514.m_pBlock);
        if (m_unk508.m_pBlock != nullptr) Mem_FreeAligned16(m_unk508.m_pBlock);
        if (m_unk4FC.m_pBlock != nullptr) Mem_FreeAligned16(m_unk4FC.m_pBlock);
        if (m_unk4F0.m_pBlock != nullptr) Mem_FreeAligned16(m_unk4F0.m_pBlock);
        if (m_unk4E4.m_pBlock != nullptr) Mem_FreeAligned16(m_unk4E4.m_pBlock);
    }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x002951a0 CKHkS08Enemy_Load
    void Start() override;  // vt+0x50 0x00294a78 CKHkS08Enemy_Start (C2.2)
    int32_t PostLoad(int32_t type) override;  // vt+0x30 0x00294aa0 CKHkS08Enemy_PostLoad
    void ResetRuntimeState() override;        // vt+0xc4 0x00291e88 CKHkS08Enemy_ResetRuntimeState_maybe
    // IKHkEnemy's slots CKHkS08Enemy overrides.
    void Update(IKTime* clock) override;                       // vt+0x7c 0x002962b8 CKHkS08Enemy_Update
    void VfC8() override;                                      // vt+0xc8 0x00291e60 CKHkS08Enemy_vfC8 (calls the base)
    void Activate() override;                                  // vt+0xcc 0x00292e60 CKHkS08Enemy_Activate
    void Deactivate() override;                                // vt+0xd0 0x00293cb0 CKHkS08Enemy_Deactivate
    void VfD4() override {}                                    // vt+0xd4 0x00291478 CKHkS08Enemy_vfD4 (empty)
    uint8_t CanSpawnFromSquad(IKSerializable* squad) override; // vt+0xd8 0x002923c8 CKHkS08Enemy_CanSpawnFromSquad_maybe
    void SpawnAtPosition(const CVector3* position, const CVector3* direction, uint32_t flags) override;  // vt+0xdc 0x002937c8
    uint32_t ConstrainToGroundAndNavMesh() override;           // vt+0xe0 0x00292058 CKHkS08Enemy_ConstrainToGroundAndNavMesh_maybe
    void* VfEC() override { return &m_unk1c4; }                // vt+0xec 0x009bc998 CKHkS08Enemy_vfEC: this + 0x1c4
    void ForceState16() override;                              // vt+0x124 0x002820e8 CKHkS08Enemy_ForceState16_maybe

    // CKHkS08Enemy's own slots (vt+0x128..+0x240). The state handlers of the four state machines take
    // (clock, phase, other): phase 0 runs the state and returns the next one, phase 1 enters it (other: the state left),
    // phase 2 leaves it (other: the state entered). Their names carry the row of their machine (MainStateNN = row NN of
    // m_aMainStates, whose descriptor is this slot's vtable offset + 1).
    virtual uint8_t ProcessDamageStateTransitions(IKTime* clock);  // vt+0x128 (Update tests r3) 0x002a6d40 CKHkS08Enemy_ProcessDamageStateTransitions_maybe
    virtual void UpdateTargetAndDestination(IKTime* clock);  // vt+0x12c 0x0029dfd8 CKHkS08Enemy_UpdateTargetAndDestination
    virtual void UpdateTimers(IKTime* clock);  // vt+0x130 0x0029e028 CKHkS08Enemy_UpdateTimers_maybe
    virtual void ProcessContacts(IKTime* clock);  // vt+0x134 0x002824d0 CKHkS08Enemy_ProcessContacts
    virtual void UpdateAttackerHitCooldowns(IKTime* clock);  // vt+0x138 0x0027d9b8 CKHkS08Enemy_UpdateAttackerHitCooldowns_maybe
    virtual void ResolveGroundAndApplyTransform(IKTime* clock);  // vt+0x13c 0x00283b08 CKHkS08Enemy_ResolveGroundAndApplyTransform_maybe
    virtual void UpdateShadowAndAuraFx();  // vt+0x140 0x0028bfc0 CKHkS08Enemy_UpdateShadowAndAuraFx_maybe
    virtual void AdvanceAnimation(IKTime* clock);  // vt+0x144 0x002866d0 CKHkS08Enemy_AdvanceAnimation_maybe
    virtual void TickAttackCooldowns();  // vt+0x148 0x0027d138 CKHkS08Enemy_vf148
    virtual uint8_t MainState00_Spawn(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x14c 0x002a0810 CKHkS08Enemy_State00_Spawn_maybe
    virtual uint8_t MainState01(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x150 0x002a4190 CKHkS08Enemy_State01
    virtual uint8_t MainState02_Combat(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x154 0x002aba20 CKHkS08Enemy_State02_Combat_maybe
    virtual uint8_t MainState03(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x158 0x0029dd98 CKHkS08Enemy_vf158
    virtual uint8_t MainState04(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x15c 0x0029dda0 CKHkS08Enemy_vf15C
    virtual uint8_t MainState05_Guard(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x160 0x002a1db8 CKHkS08Enemy_State05_Guard_maybe
    // DOTD: State05_Guard's inlined pieces (the facing away from the target, the weapon knocked out by the stun).
    void GuardFaceAwayFromTarget();
    bool GuardEjectWeapon();
    virtual uint8_t MainState06_Dodge(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x164 0x0029ec08 CKHkS08Enemy_State06_Dodge_maybe
    virtual uint8_t MainState0B(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x168 0x0029dda8 CKHkS08Enemy_vf168
    virtual uint8_t MainState0C(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x16c 0x0029ddb0 CKHkS08Enemy_vf16C
    virtual uint8_t MainState0D_AttackWindup(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x170 0x002a3278 CKHkS08Enemy_State0D_AttackWindup_maybe
    virtual uint8_t MainState0E_AttackStrike(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x174 0x002a2530 CKHkS08Enemy_State0E_AttackStrike_maybe
    virtual uint8_t MainState0F_AttackRecover(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x178 0x002aab10 CKHkS08Enemy_State0F_AttackRecover_maybe
    virtual uint8_t MainState12(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x17c 0x0029ddb8 CKHkS08Enemy_vf17C
    virtual uint8_t MainState13(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x180 0x0029ddc0 CKHkS08Enemy_vf180
    virtual uint8_t MainState14(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x184 0x0029ddc8 CKHkS08Enemy_vf184
    virtual uint8_t MainState15_Dying(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x188 0x0029f3c0 CKHkS08Enemy_State21_Dying
    virtual uint8_t MainState16(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x18c 0x0029e988 CKHkS08Enemy_vf18C
    virtual uint8_t MainState17(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x190 0x002a14a0 CKHkS08Enemy_State17
    virtual uint8_t MainState18(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x194 0x002a0260 CKHkS08Enemy_State18
    virtual uint8_t MainState19_OneShotAnim(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x198 0x0029df18 CKHkS08Enemy_State19_OneShotAnim_maybe
    virtual uint8_t MainState07_Grabbed(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x19c 0x002aa410 CKHkS08Enemy_State07_Grabbed
    virtual uint8_t MainState08(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x1a0 0x0029ddd0 CKHkS08Enemy_vf1A0
    virtual uint8_t MainState0A_HitReaction(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x1a4 0x002a9bc0 CKHkS08Enemy_State0A_HitReaction_maybe
    virtual uint8_t MainState1A_Burning(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x1a8 0x0029fba0 CKHkS08Enemy_State26_Burning
    virtual uint8_t MainState1B(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x1ac 0x002ab050 CKHkS08Enemy_vf1AC
    virtual uint8_t MainState1C(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x1b0 0x002a7820 CKHkS08Enemy_vf1B0
    virtual uint8_t MainState1D_WindCaught(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x1b4 0x002a91a0 CKHkS08Enemy_State1D_WindCaught_maybe
    virtual uint8_t MainState1E_WaitWindGaugeEmpty(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x1b8 0x002a8fa8 CKHkS08Enemy_State1E_WaitWindGaugeEmpty_maybe
    virtual uint8_t MainState1F_Stunned(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x1bc 0x002a8748 CKHkS08Enemy_State1F_Stunned_maybe
    virtual uint8_t MainState20_Alerted(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x1c0 0x0029e2c8 CKHkS08Enemy_State0x20_Alerted_maybe
    virtual uint8_t MainState21_DropEquipment(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x1c4 0x0029e6e8 CKHkS08Enemy_State0x21_DropEquipment_maybe
    virtual uint8_t MainState22_BlockAndCounter(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x1c8 0x0029f0a0 CKHkS08Enemy_State0x22_BlockAndCounter_maybe
    virtual uint8_t MainState23(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x1cc 0x0029ddd8 CKHkS08Enemy_vf1CC
    virtual uint8_t MainState24_Feared(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x1d0 0x002a81f0 CKHkS08Enemy_State0x24_Feared_maybe
    virtual uint8_t MainState25(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x1d4 0x0029e470 CKHkS08Enemy_vf1D4
    virtual uint8_t MainState26_OnFireWait(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x1d8 0x0029dde0 CKHkS08Enemy_State0x26_OnFireWait_maybe
    virtual uint8_t MainState27_Fall(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x1dc 0x002a7eb0 CKHkS08Enemy_State27_Fall_maybe
    virtual uint8_t AwareState00_WatchForTarget(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x1e0 0x002886d8 CKHkS08Enemy_AwareSM00_WatchForTarget_maybe
    virtual uint8_t AwareState01_PlayAlertAnim(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x1e4 0x002885c8 CKHkS08Enemy_AwareSM01_PlayAlertAnim_maybe
    virtual uint8_t AwareState02(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x1e8 0x002884b0 CKHkS08Enemy_vf1E8
    virtual uint8_t ReactState00_DispatchHit(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x1ec 0x00298e08 CKHkS08Enemy_ReactSM00_DispatchHit_maybe
    virtual uint8_t ReactState01_Burning(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x1f0 0x002977c0 CKHkS08Enemy_ReactSM01_Burning_maybe
    virtual uint8_t ReactState02_Hurt(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x1f4 0x002998d0 CKHkS08Enemy_ReactSM02_Hurt_maybe
    virtual uint8_t ReactState03_HurtCheckStun(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x1f8 0x00299708 CKHkS08Enemy_ReactSM03_HurtCheckStun_maybe
    virtual uint8_t ReactState06_Airborne(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x1fc 0x002993e8 CKHkS08Enemy_ReactSM06_Airborne_maybe
    virtual uint8_t ReactState07_Knockdown(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x200 0x0029c998 CKHkS08Enemy_ReactSM07_Knockdown_maybe
    virtual uint8_t ReactState04_StunGaugeDrain(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x204 0x00299188 CKHkS08Enemy_ReactSM04_StunGaugeDrain_maybe
    virtual uint8_t ReactState05_Stunned(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x208 0x00298ff0 CKHkS08Enemy_ReactSM05_Stunned_maybe
    virtual uint8_t ReactState08_Launched(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x20c 0x0029c350 CKHkS08Enemy_ReactSM08_Launched_maybe
    virtual uint8_t ReactState09(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x210 0x00297160 CKHkS08Enemy_vf210
    virtual uint8_t ReactState0A(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x214 0x00297168 CKHkS08Enemy_vf214
    virtual uint8_t ReactState0B_GetUp(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x218 0x00297568 CKHkS08Enemy_ReactSM0B_GetUp_maybe
    virtual uint8_t ReactState0C(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x21c 0x00297458 CKHkS08Enemy_vf21C
    virtual uint8_t ReactState0D(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x220 0x0029c018 CKHkS08Enemy_ReactSM0D_maybe
    virtual uint8_t ReactState0E_FallUntilGrounded(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x224 0x0029c148 CKHkS08Enemy_ReactSM0E_FallUntilGrounded_maybe
    virtual uint8_t ReactState0F_DeathAnim(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x228 0x0029bd40 CKHkS08Enemy_ReactSM0F_DeathAnim_maybe
    virtual uint8_t ReactState10_KnockbackAnim(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x22c 0x00298d68 CKHkS08Enemy_ReactSM10_KnockbackAnim_maybe
    virtual uint8_t AuxState00_PlayStartAnim(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x230 0x0029d290 CKHkS08Enemy_AuxSM00_PlayStartAnim_maybe
    virtual uint8_t AuxState01_SeekWeapon(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x234 0x0029d548 CKHkS08Enemy_AuxSM01_SeekWeapon_maybe
    virtual uint8_t AuxState02_ClaimWeapon(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x238 0x0029d760 CKHkS08Enemy_AuxSM02_ClaimWeapon_maybe
    virtual uint8_t AuxState03(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x23c 0x0029db70 CKHkS08Enemy_vf23C
    virtual uint8_t AuxState04_PickUpWeapon(IKTime* clock, int32_t phase, uint8_t other);  // vt+0x240 0x0029d818 CKHkS08Enemy_AuxSM04_PickUpWeapon_maybe

    // The state machines' dispatch (the inlined pointer-to-member calls of the original): the row's PS3 descriptor
    // (a virtual one: vtable offset + 1) mapped to the native slot. CallMainState etc. call row `state` with
    // (clock, phase, other); 0xff calls nothing.
    uint8_t CallStateRow(const uint32_t pair[2], IKTime* clock, int32_t phase, uint8_t other);
    uint8_t CallMainState(uint8_t state, IKTime* clock, int32_t phase, uint8_t other) {
        return CallStateRow(m_pMainStates + state * 2, clock, phase, other);
    }
    uint8_t CallAwareState(uint8_t state, IKTime* clock, int32_t phase, uint8_t other) {
        return CallStateRow(m_pAwareStates + state * 2, clock, phase, other);
    }
    uint8_t CallReactState(uint8_t state, IKTime* clock, int32_t phase, uint8_t other) {
        return CallStateRow(m_pReactStates + state * 2, clock, phase, other);
    }
    uint8_t CallAuxState(uint8_t state, IKTime* clock, int32_t phase, uint8_t other) {
        return CallStateRow(m_pAuxStates + state * 2, clock, phase, other);
    }
    // ==== [fork B: spawn path, states, targeting] non-virtual methods ====
    // DOTD: the enemy's kind parameters (+0x884, a CKS08EnemyCpnt; Activate copies IKHkEnemy's +0x188 reference there).
    class CKS08EnemyCpnt* Cfg() const;
    // DOTD: the inlined main state change (leave the current row with phase 2, enter `next` with phase 1).
    void SwitchMainState(uint8_t next, IKTime* clock);
    // DOTD: the inlined reaction state change (+0x554), as SwitchMainState.
    void SwitchReactState(uint8_t next, IKTime* clock);
    void ApplyPendingDamage(IKTime* clock);  // 0x00299f30 CKHkS08Enemy_ApplyPendingDamage
    void AttachRandomAccessories();    // 0x002917e0 CKHkS08Enemy_AttachRandomAccessories_maybe
    void AttachRandomShield();         // 0x00292710 CKHkS08Enemy_AttachRandomShield
    void EquipWeapon(IKSerializable* weapon);  // 0x00292a10 CKHkS08Enemy_EquipWeapon_maybe
    void AttachRandomWeapon();         // 0x00292b40 CKHkS08Enemy_AttachRandomWeapon
    class CKHkS08Weapon* FindFreeWeapon();  // 0x0029d078 CKHkS08Enemy_FindFreeWeapon
    void DropWeaponOrShield();         // 0x0029d390 CKHkS08Enemy_DropWeaponOrShield_maybe
    void DropShield();                 // 0x002915e8 CKHkS08Enemy_DropShield
    void DetachWeapon();               // 0x002916f0 CKHkS08Enemy_DetachWeapon_maybe
    void SetFireLoopSoundActive(uint32_t on);  // 0x002aeb48 CKHkS08Enemy_SetFireLoopSoundActive_maybe
    void SetBurning(uint8_t on);       // 0x002aec30 CKHkS08Enemy_SetBurning
    void SpreadPoisonToNearby(float amount, float radiusSquared);  // 0x002afff0 CKHkS08Enemy_SpreadPoisonToNearby
    void SpreadStunToNearby(float amount, float radiusSquared);    // 0x002ae5e8 CKHkS08Enemy_SpreadStunToNearby
    void UpdateTargetingAndAwareness(IKTime* clock);  // 0x0028fcd0 CKHkS08Enemy_UpdateTargetingAndAwareness_maybe
    void SelectTarget();                              // 0x0028f290 CKHkS08Enemy_SelectTarget
    float ScoreHeroTarget(uint32_t dragon, uint32_t dragon0, uint32_t dragon1);      // 0x0028f090
    float ScoreTargetCrowding(uint32_t dragon, uint32_t dragon0, uint32_t dragon1);  // 0x0028e048
    void UpdateMoveDestination(IKTime* clock);        // 0x00290338 CKHkS08Enemy_UpdateMoveDestination_maybe
    void UpdateBehaviourMode(IKTime* clock);          // 0x0028f928 CKHkS08Enemy_UpdateBehaviourMode
    void SelectAttack();                              // 0x0028ed10 CKHkS08Enemy_SelectAttack
    float ScoreAttack(uint32_t index);                // 0x0028e758 CKHkS08Enemy_ScoreAttack
    // State01's alerted stance (CKHkS08Enemy_11.cpp): the next state, or -1 for the stance's tail.
    int32_t AlertedStance(IKTime* clock);
    void UpdateKind1Wander(IKTime* clock);
    void SteerGround(CVector3* position, float* yaw, CVector3* velocity, const CVector3* target, const CVector3* direction,
                     uint8_t keepPath);
    void SteerFlying(CVector3* position, float* yaw, CVector3* velocity, const CVector3* target, const CVector3* direction,
                     uint8_t mode, uint8_t keepPath, uint8_t staticForce);
    uint8_t CarrierAcceptsTransportable(IKSerializable* transportable);
    void EmitWeaponSparks(uint8_t anim);  // State0D (CKHkS08Enemy_11.cpp)
    void EmitStrikeEffects(uint8_t anim);  // State0E
    void SetAttackTrailActive(uint32_t trail, uint8_t active, uint8_t update);  // 0x0028b960
    void ComputeAttackApproachPoint();                // 0x00280e30 CKHkS08Enemy_ComputeAttackApproachPoint_maybe
    uint8_t IsWithinHeroRangeOfCameraFocus(float range);  // 0x0027dc70 CKHkS08Enemy_IsWithinHeroRangeOfCameraFocus_maybe
    // xfork: owned by fork C, signature assumed from the asm.
    CVector3 PickAttackSpotNearHero();         // 0x00280190 CKHkS08Enemy_PickAttackSpotNearHero_maybe (r3: the result)
    void UnregisterShadowCaster();             // 0x002773e0 CKHkS08Enemy_UnregisterShadowCaster_maybe
    void DropCarriedTransportableAtHand();     // inlined in Deactivate 0x2945bc / State21_Dying 0x29f928 (Enemy_8.cpp)
    void SetMeshPopFxActive(int32_t active, int32_t positionOnly);  // 0x0028c838 CKHkS08Enemy_SetMeshPopFxActive_maybe
    // 0x0028cb88 CKHkS08Enemy_SetFreezeFxActive_maybe: off: the held freeze pop (+0x878) stopped and released (vt+0x58);
    // on (none held): the kind's freeze pop data (+0x4f0) bound to the hot spot `hotSpot` (1 when negative), a pooled pop
    // acquired into +0x878 and triggered (TriggerPop, child 0).
    void SetFreezeFxActive(int32_t active, int32_t hotSpot);
    CVector3 ChooseMoveTarget();               // 0x002808e8 CKHkS08Enemy_ChooseMoveTarget_maybe (r3: the result)
    // 0x0027d208 CKHkS08Enemy_PickSpotAlongTargetAim_maybe and 0x0027e520 CKHkS08Enemy_PickAttackSpotNearHeroAnyAngle_maybe
    // (ChooseMoveTarget with +0x7dd / +0x7f9).
    CVector3 PickSpotAlongTargetAim();
    CVector3 PickAttackSpotNearHeroAnyAngle();
    void SetPartsFlagForCategory(int32_t category);    // 0x0027cf30 CKHkS08Enemy_SetPartsFlagForCategory_maybe
    void ClearPartsFlagForCategory(int32_t category);  // 0x0027d018 CKHkS08Enemy_ClearPartsFlagForCategory_maybe
    // xfork: owned by fork D, signature assumed from the asm.
    // DOTD helper (inlined in the states): the animation time (+0x54) of the controller a layer slot plays (the slot's
    // AnimBlendSlot +0x04: controller array +0x04, index +0x10, the controller at +0x50 + index * 4).
    float LayerSlotAnimTime(int32_t layer, int32_t slot);

    // ==== end fork B ====
    //
    // ==== [fork C: base, ground, volumes, contacts, sector nodes, sounds] non-virtual methods ====
    // 0x002771c0 CKHkS08Enemy_GetSectorIndex_maybe: the variant of the enemy's sector components (m_unk18C): 0 for a kind
    // the group flags (vt+0x104), else the index of the squad's fight zone (+0x3c).
    int32_t GetSectorIndex();
    CKEnemySectorCpnt* GetSectorCpnt();  // DOTD: m_unk18C[GetSectorIndex()] (the original inlines the lookup)
    // 0x0027ad40 CKHkS08Enemy_AttachSectorNode_maybe: the node leaves its parent, then by `mode`: 0 the dynamic scene root,
    // 1 the enemy's node, 2 / 3 the sector component's animated node / collision volume `index` (each after
    // CSGMovable_SetIdentity), 4 the hot spot `index` (CSGHotSpot_AttachVolume); other modes: nowhere.
    void AttachSectorNode(IKSerializable* node, uint8_t mode, uint8_t index);
    // 0x0027aac0 CKHkS08Enemy_BindAttachmentToNode_maybe
    void BindAttachmentToNode(IKSerializable* attachment, uint8_t mode, uint8_t index);
    void AttachSectorNodesToBones();    // 0x0027b048 CKHkS08Enemy_AttachSectorNodesToBones_maybe
    void DetachSectorNode(IKSerializable* node);  // 0x00279268 CKHkS08Enemy_DetachSectorNode_maybe
    void DetachSectorNodesFromBones();  // 0x0027a1b0 CKHkS08Enemy_DetachSectorNodesFromBones_maybe
    // 0x002795c0 CKHkS08Enemy_PlaySound: sound `sound` of the sector component's dictionary attached to `node` (null: the
    // enemy's node), looped or not, played from 0. The original's r5 and r7 arguments are not read.
    void PlaySound(uint8_t sound, uint8_t loop, IKSerializable* node);
    void StopSound(uint8_t sound);      // 0x002794f0 CKHkS08Enemy_StopSound
    void StopAllSounds();               // 0x00279400 CKHkS08Enemy_StopAllSounds_maybe
    void ApplyHitToArmourParts(IKBoundingVolume* other);  // DOTD: ProcessContacts' armour (0x0028317c)
    // 0x0027ed08 CKHkS08Enemy_BreakArmourPart (CKHkS08Enemy.cpp): a part with no health thrown off: its node (when
    // parented) kept where it is under the dynamic scene root and launched from `hitPoint`, the part put in the
    // accessory manager's flying list, the break FX 0x1c (no element: pool type -1 or 8) or 0x22 at the node.
    void BreakArmourPart(class CKS08EnemyElement* part, uint32_t index, const CVector3* hitPoint);
    void ResetAttackCooldowns();        // 0x0027ce18 CKHkS08Enemy_ResetAttackCooldowns_maybe
    uint8_t IsInDeathStates() const;    // 0x0027ce50 IsEnemyInDeathStates_maybe: main state 13, 14 or 15
    void AddBurnGauge(float amount);    // 0x0027ce90 CKHkS08Enemy_AddBurnGauge
    void AddPoisonGauge(float amount);  // 0x0027ceb8 CKHkS08Enemy_AddPoisonGauge
    void AddStunGauge(float amount);    // 0x0027cee0 CKHkS08Enemy_AddStunGauge
    void AddWindGauge(float amount);    // 0x0027cf08 CKHkS08Enemy_AddWindGauge_maybe
    // 0x0027d100 CKHkS08Enemy_GetAttackSlotCategory_maybe: 1 for 1, 2 for 2, else 0.
    static int32_t GetAttackSlotCategory(int32_t kind);
    void ForceAlerted(IKTime* clock);   // 0x00282228 CKHkS08Enemy_ForceAlerted_maybe
    void UpdateOffNavFlag();            // 0x00280ca0 CKHkS08Enemy_UpdateOffNavFlag_maybe
    uint32_t GetGroundSurfaceType() const;  // 0x0027d948 CKHkS08Enemy_GetGroundSurfaceType_maybe

    // CKHkS08Enemy_5.cpp (queries, grab state).
    void SetGrabbedBy(IKSerializable* hero);           // 0x00288c58 CKHkS08Enemy_SetGrabbedBy
    void ClearGrabber(IKSerializable* hero);           // 0x00288c98 CKHkS08Enemy_ClearGrabber
    int32_t GetPairedGrabAnim(uint32_t index) const;   // 0x00288dc8 CKHkS08Enemy_GetPairedGrabAnim
    uint32_t GetAbilityInputFlags() const;             // 0x00288fc8 CKHkS08Enemy_GetAbilityInputFlags_maybe
    IKSerializable* GetGrabbingHero() const;           // 0x00288fd0 CKHkS08Enemy_GetGrabbingHero
    IKSerializable* GetTargetHero() const;             // 0x00289060 CKHkS08Enemy_GetTargetHero
    IKSerializable* GetTargetRaw() const;              // 0x002890f0 CKHkS08Enemy_GetTargetRaw
    void AddPoisonGauge2(float amount);                // 0x002890f8 CKHkS08Enemy_AddPoisonGauge_2
    void ClearAttackSlotReservation();                 // 0x00289120 CKHkS08Enemy_ClearAttackSlotReservation_maybe
    uint8_t IsValidCombatTarget() const;               // 0x00289278 CKHkS08Enemy_IsValidCombatTarget_maybe
    CSGHotSpot* GetHotSpot(int32_t index);             // 0x002892e8 CKHkS08Enemy_GetHotSpot
    // 0x0027d1b8 CKHkS08Enemy_SpawnBonusDrop_maybe: the kind's bonus data (+0x4b4) dropped by the bonus service at
    // `pos` around `dir` (velocities from `pos`), only its count mode 1 entries with `onlyMode1`.
    void SpawnBonusDrop(const CVector3* pos, const CVector3* dir, int32_t onlyMode1);
    static int32_t GetAttackSlotCategoryThunk(int32_t kind);  // 0x00289370
    uint8_t IsGrabbedState() const;                    // 0x002896b8 CKHkS08Enemy_IsGrabbedState_maybe
    void SetPosition(const CVector3* position);        // 0x00289718 CKHkS08Enemy_SetPosition
    void TeleportToPosition(const CVector3* position); // 0x00289750 CKHkS08Enemy_TeleportTo_maybe
    uint8_t IsOnGround();                              // 0x00289a98 CKHkS08Enemy_IsOnGround_maybe
    CVector3 ComputeGroundPoint();                     // 0x00289e60 CKHkS08Enemy_ComputeGroundPoint_maybe
    void SetHeldFlag(uint32_t value);                  // 0x00289f08 CKHkS08Enemy_SetHeldFlag
    IKSerializable* GetSectorHotSpot(uint32_t index);  // 0x0028a160 CKHkS08Enemy_GetSectorHotSpot
    IKSerializable* GetGrabHotSpot();                  // 0x0028a1c8 CKHkS08Enemy_GetGrabHotSpot_maybe
    void GetSectorHotSpotPosition(CVector3* out);      // 0x0028a268 CKHkS08Enemy_GetSectorHotSpotPosition (hidden-pointer return)
    void ResetMainStateMachine();                      // 0x0028aa70 CKHkS08Enemy_ResetMainStateMachine_maybe
    void EnterReleasedState(uint8_t value);            // 0x0028ab48 CKHkS08Enemy_EnterReleasedState_maybe

    // xfork: owned by fork D (the layer slots), signature assumed from RegisterActive 0x27b590: the slot's AnimBlendSlot
    // (+0x04) initialised with `controller` (AnimBlendSlot_InitThunk 0x79ff0), then +0x1c, +0x20 = 0 and the bytes
    // +0x24..+0x27 = 0.
    void InitAnimLayerSlot(SEnemyAnimLayerSlot* slot, IKSerializable* controller);

    // ==== end fork C ====
    //
    // ==== [fork D: animation layers, marks, status effects, Update, hit reactions] non-virtual methods ====
    // The animation layers (CKHkS08Enemy_2.cpp). Layer slots are m_unk164[layer][slot]; rows index the kind's
    // CAnimationDictionary of a sector (column = slot).
    static class CKAnmKeyFrameController* ActiveTrack(SEnemyAnimLayerSlot& slot);
    class CAnimationDictionary* AnimDictionary(uint32_t sector, uint32_t layer) const;
    float AnimEntryDuration(uint32_t sector, uint32_t layer, uint32_t index) const;
    float ScaleRateInState1(float rate);
    void RequestAnim(uint8_t anim, uint8_t restart, uint32_t layer, uint32_t slot, float blend, float start);  // 0x00285340
    float GetAnimLayerTime(uint32_t layer, uint32_t slot);               // 0x00285388
    uint8_t GetCurrentAnim(uint32_t layer, uint32_t slot);               // 0x00285408
    float GetLayerSlotAnimDuration(uint32_t layer, uint32_t slot);       // 0x002854f8
    bool IsAnimEndReached(float dt, uint32_t layer, uint32_t slot);      // 0x00285558
    float GetAnimDuration(uint8_t anim, uint32_t layer, uint32_t slot);  // 0x00285638
    void ResetLayer0Slot0StateByMode();                                  // 0x002857b8
    void ForceAnimSlot(uint8_t anim, uint8_t request, uint32_t layer, uint32_t slot);  // 0x00285b98
    void SetSignedBlendAnimPair(float start, float weight, uint32_t a, uint32_t b, uint32_t c);  // 0x00285c10
    float GetAnimSpeedScale(uint32_t layer, uint32_t slot);              // 0x00285d88
    void AdvanceTrackTime(uint32_t layer, uint32_t slot);                // 0x00285ec8
    void AdvanceBlendSlotTime(uint32_t layer, uint32_t slot);            // 0x00286060
    void AdvanceAnimLayer(uint8_t state, uint32_t sector, uint32_t layer, uint32_t slot);  // 0x00286220
    // The anim marks (CKHkS08Enemy_3.cpp): (t0, t1) = layer 0 slot 0's evaluated time and its time now.
    struct RtAnimAnimation* CurrentLayer0Animation();
    void MoveForwardByAnimMarks(float t0, float t1);   // 0x002867b8
    void PlayAnimMarkSounds(float t0, float t1);       // 0x00286c08
    void SnapToGround();                               // 0x00286ee0
    // The hurt reaction's pieces (CKHkS08Enemy_12.cpp).
    void PlayDirectionalHurtAnim();                    // 0x00297950 CKHkS08Enemy_PlayDirectionalHurtAnim_maybe
    void UpdateHurtAnimPlayback(IKTime* clock);        // 0x00298430 CKHkS08Enemy_UpdateHurtAnimPlayback_maybe
    void IntegrateKnockbackMotion(IKTime* clock);      // 0x002987c8 CKHkS08Enemy_IntegrateKnockbackMotion_maybe
    // ProcessContacts 0x002824d0 and its pieces (CKHkS08Enemy.cpp).
    void ProcessDamageContact(ICollision* contact, IKBoundingVolume* other, uint8_t* canBeHit);  // DOTD (inlined)
    // ResolveGroundAndApplyTransform 0x00283b08 and its pieces (CKHkS08Enemy.cpp).
    uint8_t ClampToNavSectors();                       // 0x0027f2d8 CKHkS08Enemy_ClampToNavSectors_maybe
    bool IsReachablePoint(const CVector3* point);      // 0x0027f8c0 CKHkS08Enemy_IsReachablePoint_maybe
    CVector3 PickRandomReachablePoint();               // 0x0027fce8 CKHkS08Enemy_PickRandomReachablePoint_maybe (r3: the result)
    bool IsHeldByWindBeam();                           // DOTD (inlined)
    void RememberSafePoint(const CVector3& point);     // DOTD (inlined twice)
    void UpdateFlyingHeight();                         // DOTD (inlined)
    void UpdateAttackHitWindow(float t0, float t1);    // 0x002871f0
    void HandleAnimMarkEvents(float t0, float t1);     // 0x002878f0
    void ProcessAnimMarks();                           // 0x00288420
    // The status effects (CKHkS08Enemy_4.cpp, _12.._16.cpp).
    void UpdateStatusEffects(IKTime* clock);           // 0x00288a38
    void UpdateStunStatus(IKTime* clock);              // 0x002ae370
    void UpdateShadowStatus(IKTime* clock);            // 0x002ae718
    void UpdateStatus0Dot(IKTime* clock);              // 0x002aeec8
    void UpdateFreezeStatus(IKTime* clock);            // 0x002af780
    void UpdatePoisonStatus(IKTime* clock);            // 0x002b0170
    void UpdateWindStatus(IKTime* clock);              // 0x002b0a20
    float HeroStatusDecayRate(uint32_t dragon);        // DOTD: GetHeroByDragonIndex 0x2ca080 + CKHkS08Hero_GetStatusDecayRate_maybe 0x32a3d0
    bool PendingElementDamageIs(int32_t element);      // DOTD: +0x239 and the pending damage a CKS08ElementDamage of that +0x20
    // Update and the hit reactions (CKHkS08Enemy_9.cpp).
    uint8_t PendingDamageCausesHitReaction();          // 0x00297170
    int32_t MessageProc(uint16_t message, void* data) override;  // vt+0x1c 0x00294b68 CKHkS08Enemy_MessageProc
    // xfork: owned by fork C (CKHkS08Enemy.cpp / _5.cpp), signatures assumed from the asm; stubs in CKHkS08Enemy_xforkD.cpp.
    uint8_t EvalRampHoldRampDown(float t, float rampEnd, float hold, float down, float base, float slope, float downSlope,
                                 float* out);          // xfork C: 0x0027cda8 EvalRampHoldRampDown_maybe
    void EnableAttackVolumes();                        // xfork C: 0x0027d708 CKHkS08Enemy_EnableAttackVolumes_maybe
    float AngleBetween(CVector3* a, CVector3* b);  // xfork C: 0x0027eb88 Vec3_AngleBetween_maybe
    uint8_t CanBeHeldAtPosition();                                // 0x00289b38 CKHkS08Enemy_CanBeHeldAtPosition_maybe
    uint8_t CanBeGrabbed(uint8_t windBeam);                       // 0x002898b0 CKHkS08Enemy_CanBeGrabbed_maybe
    // 0x0028a2e0 CKHkS08Enemy_CrossfadeAnimFromDictionary_maybe
    uint32_t CrossfadeAnimFromDictionary(uint32_t anim, uint32_t mode, float blend, float start, uint32_t layer, uint32_t slot);
    void AdvanceGrabbedAnimTime(float dt, uint32_t layer, uint32_t slot);  // 0x00289df8 CKHkS08Enemy_AdvanceGrabbedAnimTime_maybe
    void SetAttackSpheresActive(uint8_t on, IKSerializable* damage);  // 0x00288e08 CKHkS08Enemy_SetAttackSpheresActive
    void ApplyThrowImpactDamage(IKSerializable* damage, const CVector3* along);  // 0x0028ac90 (CKHkS08Enemy_5.cpp)
    void ReceiveDamage(IKSerializable* damage, IKSerializable* source);  // 0x0028a6e0 CKHkS08Enemy_ReceiveDamage
    void IKHkEnemyUpdate(IKTime* clock);               // xfork C: 0x00277650 IKHkEnemy_Update
    void EmitParticleAt(uint32_t fx, const CVector3* position, const CVector3* direction, uint32_t local);  // 0x00278028
    void EmitKind7HotspotParticles();  // 0x0028b500 CKHkS08Enemy_EmitKind7HotspotParticles_maybe
    void SpawnShieldDropFx();          // 0x0028cec0 CKHkS08Enemy_SpawnShieldDropFx_maybe
    void SetStunFxActive(uint8_t on);  // 0x0028d1b8 CKHkS08Enemy_SetStunFxActive_maybe
    // 0x0028c0a0 CKHkS08Enemy_SpawnHitFx: the hit explosion of the pending damage (CKHkS08Enemy_12.cpp).
    void SpawnHitFx();
    // ApplyPendingDamage's pieces (CKHkS08Enemy_12.cpp).
    float ApplyElementResistance(float amount);        // 0x00288b18
    void PlayFxOnAllHotspots(uint32_t fx);             // 0x0028da80 CKHkS08Enemy_PlayFxOnAllHotspots_maybe
    void SpawnHitFxAt(uint32_t fx, const CVector3* at);  // 0x0028c590 CKHkS08Enemy_SpawnHitFx_maybe
    void ApplyElementGauges(IKTime* clock);            // DOTD (inlined)
    void PlayHitSounds();                              // DOTD (inlined)
    void CountHitStats();                              // DOTD (inlined)
    void CountHeldElementHit(CKS08GameManager* manager, const CVector3* point);  // DOTD (inlined)
    void AccumulateBonusDamage();                      // DOTD (inlined)
    void PlayFxAtHotspot1(uint32_t fx);                // 0x0028d4a8 CKHkS08Enemy_PlayFxAtHotspot1_maybe
    void CallCarrierUpdate(IKTime* clock);             // xfork B: the carrier +0x734's vt+0x74 (0x4c93e8)
    // xfork: owned by fork A (the groups), wrapped here.
    void SignalEnemyGroupAlert();                      // xfork A: 0x00268178 CKGrpS08Enemy_SignalAlert_maybe (enemy group)
    void ApplySquadPendingChoreography();              // xfork A: 0x0025ca10 CKGrpSquad_ApplyPendingChoreography_maybe (+0x168)

    // ==== end fork D ====
    //
    void InitMainStateMachine();       // 0x00294878 CKHkS08Enemy_InitMainStateMachine
    void InitAwarenessStateMachine();  // 0x002884b8 CKHkS08Enemy_InitAwarenessStateMachine_maybe
    void InitHitReactionStateMachine();  // 0x00297250 CKHkS08Enemy_InitHitReactionStateMachine_maybe
    void InitAuxStateMachine();        // 0x0029dd38 CKHkS08Enemy_InitAuxStateMachine_maybe


    uint32_t m_unk1b4;  // +0x1b4 Ghidra dwDw_1b4; w16 (the enemy type index: fight-zone per-type vectors, eggs)
    float m_unk1b8;  // +0x1b8 f1
    uint8_t m_unk1bc;  // +0x1bc b9f2
    uint8_t m_unk1bd;  // +0x1bd
    uint8_t m_unk1be;  // +0x1be
    uint8_t m_unk1bf;  // +0x1bf
    void* m_pSecondVtable1C0;               // +0x1c0 the second base vtable (0xb21458); null here
    float m_unk1c4;  // +0x1c4 f10
    float m_unk1c8;  // +0x1c8 (with +0x1c4 / +0x1cc: a vector SpawnAtPosition copies to +0x37c)
    float m_unk1cc;  // +0x1cc f1
    float m_unk1d0;  // +0x1d0 f7
    float m_unk1d4;  // +0x1d4 f3
    float m_unk1d8;  // +0x1d8 f1
    float m_unk1dc;  // +0x1dc f3
    float m_unk1e0;  // +0x1e0 f2
    float m_unk1e4;  // +0x1e4 f3
    uint8_t m_unk1e8;  // +0x1e8 b2f1
    uint8_t m_unk1e9;  // +0x1e9
    uint8_t m_unk1ea;  // +0x1ea
    uint8_t m_unk1eb;  // +0x1eb
    uint8_t m_unk1ec;  // +0x1ec f1w1
    uint8_t m_unk1ed;  // +0x1ed
    uint8_t m_unk1ee;  // +0x1ee Ghidra bB_1ee; b1
    uint8_t m_unk1ef;  // +0x1ef
    float m_unk1f0;  // +0x1f0 f12w1
    float m_unk1f4;  // +0x1f4 f6
    uint8_t m_unk1f8;  // +0x1f8 b4
    uint8_t m_unk1f9;  // +0x1f9 b5
    uint8_t m_unk1fa;  // +0x1fa
    uint8_t m_unk1fb;  // +0x1fb
    float m_unk1fc;  // +0x1fc Ghidra flFl_1fc: the frame dt (clock +0x1c) x the time scale +0x200 (Update)
    float m_unk200;  // +0x200 Ghidra dwDw_200; f7w4
    float m_unk204;  // +0x204 f13w1
    // +0x208 the recent attackers (m_unk238 of them, newest last): the attacker, a "still touching" byte and a
    // cooldown counted down by UpdateAttackerHitCooldowns 0x27d9b8 while the attacker no longer touches.
    SEnemyHitAttacker m_unk208[4];  // +0x208
    uint8_t m_unk238;  // +0x238 Ghidra bHitByCount; b15
    uint8_t m_unk239;  // +0x239 Ghidra bPendingHit; b41
    uint8_t m_unk23a;  // +0x23a b1
    uint8_t m_unk23b;  // +0x23b
    float m_unk23c[3];  // +0x23c Ghidra aHitPos; f7
    float m_unk248;  // +0x248 f11
    float m_unk24c;  // +0x24c f7
    float m_unk250;  // +0x250 f2
    float m_unk254;  // +0x254 Ghidra flFl_254; f21w1
    float m_unk258;  // +0x258 Ghidra flHealth; f51w2
    float m_unk25c;  // +0x25c Ghidra dwStunGauge; f24w1
    float m_unk260;  // +0x260 Ghidra flFl_260; f10w1
    uint8_t m_unk264;  // +0x264 Ghidra bB_264; b1f2w2
    uint8_t m_unk265;  // +0x265
    uint8_t m_unk266;  // +0x266
    uint8_t m_unk267;  // +0x267
    float m_unk268;  // +0x268 f2
    float m_unk26c;  // +0x26c f1
    float m_unk270;  // +0x270 Ghidra flKnockbackSpeed; f5
    float m_unk274;  // +0x274 Ghidra flKnockbackLift; f10w1
    float m_unk278;  // +0x278 Ghidra flGauge2; f27w2
    CKS08Damage* m_unk27c;  // +0x27c Ghidra dwPendingDamage: the damage taken this frame (a CKS08ElementDamage 0x99cc for the statuses)
    float m_unk280;  // +0x280 f1
    float m_unk284;  // +0x284 f2
    float m_unk288;  // +0x288 f2
    uint8_t m_unk28c;  // +0x28c b2f1
    uint8_t m_unk28d;  // +0x28d
    uint8_t m_unk28e;  // +0x28e
    uint8_t m_unk28f;  // +0x28f
    uint8_t m_unk290;  // +0x290 Ghidra bB_290; b6f3
    uint8_t m_unk291;  // +0x291
    uint8_t m_unk292;  // +0x292
    uint8_t m_unk293;  // +0x293
    IKSerializable* m_unk294;  // +0x294 Ghidra dwGrabbingHero: the hero holding the enemy (SetGrabbedBy)
    IKSerializable* m_unk298;  // +0x298 the last hero that grabbed the enemy (SetGrabbedBy)
    uint32_t m_unk29c;  // +0x29c
    float m_unk2a0;  // +0x2a0 f2
    float m_unk2a4;  // +0x2a4 Ghidra dwDw_2a4; f2w2 (State0D: the attack animation's length)
    float m_unk2a8;  // +0x2a8 Ghidra dwDw_2a8; f2w1
    float m_unk2ac;  // +0x2ac Ghidra flFl_2ac; f6w2
    float m_unk2b0[30];                     // +0x2b0 timers counted down by TickAttackCooldowns (vt+0x148: the first +0x884 +0x124 of them); ResetRuntimeState clears all thirty
    uint8_t m_unk328;  // +0x328 Ghidra bB_328; b7
    uint8_t m_unk329;  // +0x329
    uint8_t m_unk32a;  // +0x32a
    uint8_t m_unk32b;  // +0x32b
    uint32_t m_unk32c;  // +0x32c Ghidra dwDw_32c; w14
    IKHook* m_unk330;  // +0x330 Ghidra dwDw_330: the target (a hero; node +0x1c)
    uint32_t m_unk334;  // +0x334
    CVector3 m_unk338;  // +0x338 the position kept when the enemy stands facing its target (UpdateMoveDestination)
    float m_unk344;  // +0x344 Ghidra flFl_344; f19w2
    uint32_t m_unk348;  // +0x348 Ghidra dwDw_348; w3
    float m_unk34c;  // +0x34c f3w2
    float m_unk350;  // +0x350 f3w2
    uint8_t m_unk354;  // +0x354 b5f1
    uint8_t m_unk355;  // +0x355
    uint8_t m_unk356;  // +0x356
    uint8_t m_unk357;  // +0x357
    uint8_t m_unk358;  // +0x358 Ghidra bB_358; b1f1
    uint8_t m_unk359;  // +0x359
    uint8_t m_unk35a;  // +0x35a
    uint8_t m_unk35b;  // +0x35b
    uint32_t m_unk35c;  // +0x35c Ghidra dwDw_35c; f1w1
    float m_unk360;  // +0x360 f3
    float m_unk364;  // +0x364 Ghidra flFl_364; f5
    float m_unk368;  // +0x368 f1
    float m_unk36c;  // +0x36c f3
    float m_unk370;  // +0x370 Ghidra flFl_370; f1w1
    uint32_t m_unk374;  // +0x374
    uint32_t m_unk378;  // +0x378
    float m_unk37c;  // +0x37c Ghidra flFl_37c; f20
    float m_unk380;  // +0x380 f4
    float m_unk384;  // +0x384
    float m_unk388;  // +0x388 Ghidra flFl_388; f18
    float m_unk38c;  // +0x38c Ghidra flFl_38c; f6
    float m_unk390;  // +0x390 the move direction z (+0x388 x, +0x38c y)
    uint8_t m_unk394;  // +0x394 Ghidra dwDw_394; w6
    uint8_t m_unk395;  // +0x395
    uint8_t m_unk396;  // +0x396
    uint8_t m_unk397;  // +0x397 b9
    uint8_t m_unk398;  // +0x398 Ghidra bB_398; b11
    uint8_t m_unk399;  // +0x399
    uint8_t m_unk39a;  // +0x39a
    uint8_t m_unk39b;  // +0x39b
    uint32_t* m_pMainStates;                // +0x39c Ghidra dwDw_39c: &m_aMainStates (InitMainStateMachine 0x294878)
    uint8_t m_mainState;                    // +0x3a0 Ghidra bState: the main state (0xff: none)
    uint8_t m_mainStateCount;               // +0x3a1 0x28
    uint8_t m_pad3a2[2];
    // The main state machine: 40 PS3 pointers to member (descriptor, adjust); the descriptors are virtual
    // (vtable offset + 1: 0x14d = vt+0x14c). Rows 9, 16, 17 and 20 are never set (0 from the allocation).
    uint32_t m_aMainStates[40][2];          // +0x3a4
    // Four reference vectors sized by the kind's count (kEnemyRefCount[m_ui8EnemyClassType]), and one word
    // vector that gets a zero per +0x4e4 entry (Load). Constructor: no block, capacity 1, nothing used.
    TVector<IKSerializable*, 1> m_unk4E4;   // +0x4e4
    TVector<IKSerializable*, 1> m_unk4F0;   // +0x4f0
    TVector<IKSerializable*, 1> m_unk4FC;   // +0x4fc
    TVector<IKSerializable*, 1> m_unk508;   // +0x508
    TVector<void*, 1> m_unk514;             // +0x514 (Ghidra dwArmorParts, +0x51c dwArmorPartCount: unverified)
    class CKHkS08Weapon* m_unk520;  // +0x520 Ghidra dwDw_520: the held weapon
    IKSerializable* m_unk524;  // +0x524 w17 (the shield, AttachRandomShield)
    uint32_t m_unk528;  // +0x528 w11
    uint32_t m_unk52c;  // +0x52c w5
    float m_unk530;  // +0x530 Ghidra flFl_530; f3w2
    uint32_t* m_pAwareStates;               // +0x534 &m_aAwareStates (InitAwarenessStateMachine 0x2884b8)
    uint8_t m_awareState;                   // +0x538 Ghidra bB_538 (constructor 0xff)
    uint8_t m_awareStateCount;              // +0x539 3 (constructor 0xff)
    uint8_t m_pad53a[2];
    uint32_t m_aAwareStates[3][2];          // +0x53c vt+0x1e0..+0x1e8
    uint32_t* m_pReactStates;               // +0x554 &m_aReactStates (InitHitReactionStateMachine 0x297250)
    uint8_t m_reactState;                   // +0x558 Ghidra bB_558 (constructor 0xff)
    uint8_t m_reactStateCount;              // +0x559 0x11 (constructor 0xff)
    uint8_t m_pad55a[2];
    uint32_t m_aReactStates[17][2];         // +0x55c vt+0x1ec..+0x22c
    uint32_t* m_pAuxStates;                 // +0x5e4 &m_aAuxStates (InitAuxStateMachine 0x29dd38)
    uint8_t m_auxState;                     // +0x5e8 Ghidra bB_5e8 (constructor 0xff)
    uint8_t m_auxStateCount;                // +0x5e9 5 (constructor 0xff)
    uint8_t m_pad5ea[2];
    uint32_t m_aAuxStates[5][2];            // +0x5ec vt+0x230..+0x240
    uint32_t m_unk614;  // +0x614
    uint32_t m_unk618;  // +0x618
    uint32_t m_unk61c;  // +0x61c
    uint32_t m_unk620;  // +0x620
    uint32_t m_unk624;  // +0x624
    uint32_t m_unk628;  // +0x628
    uint32_t m_unk62c;  // +0x62c
    uint32_t m_unk630;  // +0x630
    uint32_t m_unk634;  // +0x634
    uint32_t m_unk638;  // +0x638
    uint32_t m_unk63c;  // +0x63c
    uint32_t m_unk640;  // +0x640
    uint32_t m_unk644;  // +0x644
    uint32_t m_unk648;  // +0x648
    uint32_t m_unk64c;  // +0x64c
    uint32_t m_unk650;  // +0x650
    uint32_t m_unk654;  // +0x654
    uint32_t m_unk658;  // +0x658
    uint32_t m_unk65c;  // +0x65c
    uint32_t m_unk660;  // +0x660
    uint32_t m_unk664;  // +0x664
    uint32_t m_unk668;  // +0x668
    uint32_t m_unk66c;  // +0x66c
    uint32_t m_unk670;  // +0x670
    class CKHkS08Weapon* m_unk674;  // +0x674 Ghidra dwDw_674: the free weapon claimed (AuxSM01 / 02; its +0xb4 = this)
    uint8_t m_unk678;  // +0x678 the claimed weapon picked up (AuxSM04's mark 0x15)
    uint8_t m_unk679;  // +0x679
    uint8_t m_unk67a;  // +0x67a
    uint8_t m_unk67b;  // +0x67b
    float m_unk67c;  // +0x67c Ghidra flFl_67c; f5w2
    IKSerializable* m_unk680;  // +0x680 w7 (the egg the enemy hatches from, CKHkS08Egg_AssignEnemy)
    float m_unk684;  // +0x684 f4w1
    uint32_t m_unk688;  // +0x688 w1
    uint8_t m_unk68c;  // +0x68c b3
    uint8_t m_unk68d;  // +0x68d
    uint8_t m_unk68e;  // +0x68e
    uint8_t m_unk68f;  // +0x68f
    uint32_t m_unk690;  // +0x690
    void* m_unk694;  // +0x694 Ghidra pLastAttacker; w33
    float m_unk698;  // +0x698 f2
    float m_unk69c;  // +0x69c f1
    uint32_t m_unk6a0;  // +0x6a0
    float m_unk6a4;  // +0x6a4 Ghidra flFl_6a4; f2w1
    float m_unk6a8;  // +0x6a8 f2w1
    uint8_t m_unk6ac;  // +0x6ac b4
    uint8_t m_unk6ad;  // +0x6ad b2
    uint8_t m_unk6ae;  // +0x6ae
    uint8_t m_unk6af;  // +0x6af
    float m_unk6b0;  // +0x6b0 f4w2
    uint32_t m_unk6b4;  // +0x6b4
    float m_unk6b8;  // +0x6b8 Ghidra flStatus0Gauge; f36w3
    float m_unk6bc;  // +0x6bc f1w1 (ReactSM08_Launched compares it with the kind's +0x2d4)
    float m_unk6c0;  // +0x6c0 Ghidra flStatus4Gauge; f30w1
    float m_unk6c4;  // +0x6c4 Ghidra flStatus5Gauge; f18w1
    float m_unk6c8;  // +0x6c8 Ghidra flStatus1Gauge; f30w1
    float m_unk6cc;  // +0x6cc Ghidra flStatus6Gauge; f20w1
    float m_unk6d0;  // +0x6d0 Ghidra flStatus7Gauge; f27w6
    float m_unk6d4;  // +0x6d4 Ghidra flStatus3Gauge; f25w3
    float m_unk6d8;  // +0x6d8 f8w4: the burning run's timer (State26_Burning: a new point past the kind's +0x27c)
    CVector3 m_unk6dc;  // +0x6dc the burning run's point (State26_Burning, PickRandomReachablePoint)
    CVector3 m_unk6e8;  // +0x6e8 the burning run's flat direction toward it
    float m_unk6f4;  // +0x6f4 f3
    float m_unk6f8;  // +0x6f8 f8w1
    uint8_t m_unk6fc;  // +0x6fc Ghidra bB_6fc; b5
    uint8_t m_unk6fd;  // +0x6fd
    uint8_t m_unk6fe;  // +0x6fe
    uint8_t m_unk6ff;  // +0x6ff
    uint32_t m_unk700;  // +0x700
    float m_unk704;  // +0x704 f1
    uint8_t m_unk708;  // +0x708 Ghidra bB_708; b5
    uint8_t m_unk709;  // +0x709 b16
    uint8_t m_unk70a;  // +0x70a
    uint8_t m_unk70b;  // +0x70b
    uint32_t m_unk70c;  // +0x70c
    uint8_t m_unk710;  // +0x710 Ghidra bB_710; b2
    uint8_t m_unk711;  // +0x711
    uint8_t m_unk712;  // +0x712
    uint8_t m_unk713;  // +0x713
    float m_unk714;  // +0x714 Ghidra flFl_714; f4w2
    float m_unk718;  // +0x718 Ghidra flFl_718; f4w2
    float m_unk71c;  // +0x71c f4
    float m_unk720;  // +0x720 f3
    uint8_t m_unk724;  // +0x724 b3
    uint8_t m_unk725;  // +0x725
    uint8_t m_unk726;  // +0x726
    uint8_t m_unk727;  // +0x727
    float m_unk728;  // +0x728 f3w1
    uint32_t m_unk72c;  // +0x72c w14
    uint8_t m_unk730;                       // +0x730 read (one byte)
    uint8_t m_unk731;                       // +0x731
    uint8_t m_unk732;                       // +0x732
    uint8_t m_unk733;                       // +0x733
    IKSerializable* m_unk734;               // +0x734 reference (live: a CKS08CarrierEnemy; Ghidra pCarrierEnemy)
    IKSerializable* m_unk738;  // +0x738 w18 (the carried transportable given at spawn: MainState00_Spawn)
    class CKS08EnemyAttack* m_unk73c;  // +0x73c Ghidra dwDw_73c: the current attack
    float m_unk740;  // +0x740 f4
    uint8_t m_unk744;  // +0x744 b4
    uint8_t m_unk745;  // +0x745
    uint8_t m_unk746;  // +0x746
    uint8_t m_unk747;  // +0x747
    uint32_t m_unk748;  // +0x748 w1
    uint32_t m_unk74c;  // +0x74c w1
    uint8_t m_unk750;  // +0x750 Ghidra bB_750; b13
    uint8_t m_unk751;  // +0x751
    uint8_t m_unk752;  // +0x752
    uint8_t m_unk753;  // +0x753
    uint32_t m_unk754;  // +0x754 w15
    uint32_t m_unk758;  // +0x758 w5
    uint32_t m_unk75c;  // +0x75c w17
    float m_unk760;  // +0x760 f6
    float m_unk764;  // +0x764 f4w1
    uint32_t m_unk768;  // +0x768 w7
    uint32_t m_unk76c;  // +0x76c w10
    uint32_t m_unk770;  // +0x770 w1
    float m_unk774;  // +0x774 Ghidra flFl_774; f55w4
    float m_unk778;  // +0x778 f5
    uint32_t m_unk77c;  // +0x77c w3
    class CKS08EnemyAbilityHost* m_unk780;  // +0x780 Ghidra dwDw_780: the ability host while +0x784 runs (OperatorNew(8))
    IKSerializable* m_unk784;               // +0x784 reference: the ability of the kind's last attack (LVL010: a CKElectricalGrapple for all ten enemies, census lvl010_ingame)
    uint32_t m_unk788;  // +0x788
    float m_unk78c;  // +0x78c f3w1
    uint32_t m_unk790;  // +0x790
    float m_unk794;  // +0x794 f3w1
    float m_unk798;  // +0x798 f7
    float m_unk79c;  // +0x79c f5
    float m_unk7a0;  // +0x7a0 the kind 1 target position (y; +0x79c x, +0x7a4 z: Update moves +0x7a8 towards it)
    float m_unk7a4;  // +0x7a4
    float m_unk7a8;  // +0x7a8 f4
    float m_unk7ac;  // +0x7ac
    float m_unk7b0;  // +0x7b0
    uint8_t m_unk7b4;  // +0x7b4 Ghidra bB_7b4; b40
    uint8_t m_unk7b5;  // +0x7b5 b7
    uint8_t m_unk7b6;  // +0x7b6 b5
    uint8_t m_unk7b7;  // +0x7b7 b6
    uint8_t m_unk7b8;  // +0x7b8 b5
    uint8_t m_unk7b9;  // +0x7b9
    uint8_t m_unk7ba;  // +0x7ba
    uint8_t m_unk7bb;  // +0x7bb
    uint32_t m_unk7bc;  // +0x7bc w1
    float m_unk7c0;  // +0x7c0 f2w2: the time held (State07_Grabbed)
    uint8_t m_unk7c4;  // +0x7c4 b8
    uint8_t m_unk7c5;  // +0x7c5
    uint8_t m_unk7c6;  // +0x7c6
    uint8_t m_unk7c7;  // +0x7c7
    uint32_t m_unk7c8;  // +0x7c8 w2
    uint8_t m_unk7cc;  // +0x7cc b3
    uint8_t m_unk7cd;  // +0x7cd b4
    uint8_t m_unk7ce;  // +0x7ce b3
    uint8_t m_unk7cf;  // +0x7cf
    float m_unk7d0;  // +0x7d0 Ghidra flFl_7d0; f2w1
    uint8_t m_unk7d4;  // +0x7d4 b6
    uint8_t m_unk7d5;  // +0x7d5
    uint8_t m_unk7d6;  // +0x7d6
    uint8_t m_unk7d7;  // +0x7d7
    int32_t m_unk7d8;  // +0x7d8 w20 (ClearAttackSlotReservation: -1)

    uint8_t m_unk7dc;  // +0x7dc Ghidra bB_7dc; b9
    uint8_t m_unk7dd;  // +0x7dd b6
    uint8_t m_unk7de;  // +0x7de
    uint8_t m_unk7df;  // +0x7df
    float m_unk7e0;  // +0x7e0 f3w2
    float m_unk7e4;  // +0x7e4 f6
    float m_unk7e8;  // +0x7e8 f2w1
    float m_unk7ec;  // +0x7ec f2
    float m_unk7f0;  // +0x7f0 f1
    float m_unk7f4;  // +0x7f4 (+0x7ec..+0x7f4: the position when grabbed, SetGrabbedBy)
    uint8_t m_unk7f8;  // +0x7f8 Ghidra bB_7f8; b5
    uint8_t m_unk7f9;  // +0x7f9 Ghidra bB_7f9; b7
    uint8_t m_unk7fa;  // +0x7fa
    uint8_t m_unk7fb;  // +0x7fb
    float m_unk7fc;  // +0x7fc f4
    float m_unk800;  // +0x800 f4w2
    float m_unk804;  // +0x804 f2w1
    float m_unk808;  // +0x808 f6w2
    float m_unk80c;  // +0x80c f4w2
    uint32_t m_unk810;  // +0x810
    uint32_t m_unk814;  // +0x814
    uint8_t m_unk818;  // +0x818 Ghidra bB_818; b7
    uint8_t m_unk819;  // +0x819 Ghidra bB_819; b7
    uint8_t m_unk81a;  // +0x81a b4
    uint8_t m_unk81b;  // +0x81b
    float m_unk81c;  // +0x81c Ghidra flFl_81c; f3: the wind's height above the ground (State1D_WindCaught)
    float m_unk820;  // +0x820 Ghidra flFl_820; f5: the wind's angle about +0x824 (State1D_WindCaught)
    CVector3 m_unk824;  // +0x824 the point the wind whirls the enemy about (State1D_WindCaught)
    IKSerializable* m_unk830;  // +0x830 the previous target (SelectTarget)
    uint8_t m_unk834;  // +0x834 b4
    uint8_t m_unk835;  // +0x835
    uint8_t m_unk836;  // +0x836
    uint8_t m_unk837;  // +0x837
    class CKHkS08Weapon* m_unk838;  // +0x838 the weapon held when the drop state (0x21) began
    float m_unk83c;  // +0x83c f4
    float m_unk840;  // +0x840
    float m_unk844;  // +0x844
    float m_unk848;  // +0x848 f2w1
    float m_unk84c;  // +0x84c f8w3
    float m_unk850;  // +0x850 the burrow's hidden point (State17: from the position, moving toward +0x85c)
    float m_unk854;  // +0x854 f4
    float m_unk858;  // +0x858
    float m_unk85c;  // +0x85c f2
    float m_unk860;  // +0x860
    float m_unk864;  // +0x864
    IKSerializable* m_unk868;  // +0x868 w8 (the spawn explosion, an IKFx node: MainState00_Spawn)
    uint8_t m_unk86c;  // +0x86c b6
    uint8_t m_unk86d;  // +0x86d b5
    uint8_t m_unk86e;  // +0x86e b2
    uint8_t m_unk86f;  // +0x86f b5
    float m_unk870;  // +0x870 Ghidra flFl_870; f4w1
    uint8_t m_unk874;  // +0x874 Ghidra bB_874; b5
    uint8_t m_unk875;  // +0x875
    uint8_t m_unk876;  // +0x876
    uint8_t m_unk877;  // +0x877
    class CKMeshPopNodeFx* m_unk878;  // +0x878 the freeze FX pop (SetFreezeFxActive)
    class CKMeshPopNodeFx* m_unk87c;  // +0x87c the burrow's mesh pop (SetMeshPopFxActive)
    class CKParticlesEffectNodeFx* m_unk880;  // +0x880 the burrow's dust trail (State17)
    class CKS08EnemyCpnt* m_unk884;  // +0x884 Ghidra dwTypeConfig: the kind config (Activate copies IKHkEnemy +0x188)
    uint8_t m_unk888;  // +0x888 b8
    uint8_t m_unk889;  // +0x889
    uint8_t m_unk88a;  // +0x88a
    uint8_t m_unk88b;  // +0x88b
    IKSerializable* m_unk88C;               // +0x88c reference (live: a CGlowNodeFx)
    uint8_t m_unk890;  // +0x890 b4
    uint8_t m_unk891;  // +0x891 b16
    uint8_t m_unk892;  // +0x892
    uint8_t m_unk893;  // +0x893
    float m_unk894;  // +0x894 f2
    uint8_t m_unk898;  // +0x898 Ghidra bB_898; b15
    uint8_t m_unk899;  // +0x899 Ghidra bB_899; b3
    uint8_t m_unk89a;  // +0x89a
    uint8_t m_unk89b;  // +0x89b
    IKSerializable* m_unk89c;  // +0x89c the volume that hit last (ProcessContacts, a golem damage without +0x28)
    IKSerializable* m_unk8a0;  // +0x8a0 the volume of a held hit (ProcessContacts; cleared once +0x8a4 runs out)
    float m_unk8a4;  // +0x8a4 f3w1
    uint8_t m_unk8a8;  // +0x8a8 b4
    uint8_t m_unk8a9;  // +0x8a9
    uint8_t m_unk8aa;  // +0x8aa
    uint8_t m_unk8ab;  // +0x8ab
    uint32_t m_unk8ac;  // +0x8ac
    uint8_t m_unk8b0;  // +0x8b0 b7
    uint8_t m_unk8b1;  // +0x8b1
    uint8_t m_unk8b2;  // +0x8b2
    uint8_t m_unk8b3;  // +0x8b3
    float m_unk8b4;  // +0x8b4 f3w2
    float m_unk8b8;  // +0x8b8 f7
    CKS08Damage m_damage8BC;                // +0x8bc embedded CKS08Damage (0x28 bytes; CKS08Damage_Construct 0x4ebc70)
    float m_unk8e4;  // +0x8e4 f5
    float m_unk8e8;  // +0x8e8
    float m_unk8ec;  // +0x8ec
    float m_unk8f0;  // +0x8f0 f4w1
    uint8_t m_unk8f4;  // +0x8f4 b6
    uint8_t m_unk8f5;  // +0x8f5
    uint8_t m_unk8f6;  // +0x8f6
    uint8_t m_unk8f7;  // +0x8f7
};
DOTD_ASSERT_SIZE(CKHkS08Enemy, 0x8f8);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_pSecondVtable1C0, 0x1c0);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_pMainStates, 0x39c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_mainState, 0x3a0);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_aMainStates, 0x3a4);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk4E4, 0x4e4);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk4F0, 0x4f0);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk4FC, 0x4fc);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk508, 0x508);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk514, 0x514);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_pAwareStates, 0x534);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_aAwareStates, 0x53c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_pReactStates, 0x554);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_aReactStates, 0x55c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_pAuxStates, 0x5e4);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_aAuxStates, 0x5ec);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk730, 0x730);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk734, 0x734);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk784, 0x784);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk88C, 0x88c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_damage8BC, 0x8bc);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk1b4, 0x1b4);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk1b8, 0x1b8);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk1bc, 0x1bc);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk1bd, 0x1bd);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk1be, 0x1be);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk1bf, 0x1bf);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk1c4, 0x1c4);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk1c8, 0x1c8);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk1cc, 0x1cc);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk1d0, 0x1d0);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk1d4, 0x1d4);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk1d8, 0x1d8);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk1dc, 0x1dc);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk1e0, 0x1e0);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk1e4, 0x1e4);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk1e8, 0x1e8);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk1e9, 0x1e9);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk1ea, 0x1ea);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk1eb, 0x1eb);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk1ec, 0x1ec);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk1ed, 0x1ed);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk1ee, 0x1ee);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk1ef, 0x1ef);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk1f0, 0x1f0);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk1f4, 0x1f4);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk1f8, 0x1f8);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk1f9, 0x1f9);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk1fa, 0x1fa);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk1fb, 0x1fb);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk1fc, 0x1fc);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk200, 0x200);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk204, 0x204);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk208, 0x208);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk238, 0x238);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk239, 0x239);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk23a, 0x23a);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk23b, 0x23b);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk23c, 0x23c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk248, 0x248);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk24c, 0x24c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk250, 0x250);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk254, 0x254);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk258, 0x258);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk25c, 0x25c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk260, 0x260);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk264, 0x264);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk265, 0x265);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk266, 0x266);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk267, 0x267);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk268, 0x268);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk26c, 0x26c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk270, 0x270);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk274, 0x274);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk278, 0x278);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk27c, 0x27c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk280, 0x280);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk284, 0x284);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk288, 0x288);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk28c, 0x28c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk28d, 0x28d);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk28e, 0x28e);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk28f, 0x28f);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk290, 0x290);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk291, 0x291);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk292, 0x292);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk293, 0x293);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk294, 0x294);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk298, 0x298);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk29c, 0x29c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk2a0, 0x2a0);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk2a4, 0x2a4);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk2a8, 0x2a8);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk2ac, 0x2ac);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk328, 0x328);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk329, 0x329);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk32a, 0x32a);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk32b, 0x32b);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk32c, 0x32c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk330, 0x330);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk334, 0x334);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk338, 0x338);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk344, 0x344);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk348, 0x348);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk34c, 0x34c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk350, 0x350);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk354, 0x354);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk355, 0x355);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk356, 0x356);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk357, 0x357);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk358, 0x358);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk359, 0x359);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk35a, 0x35a);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk35b, 0x35b);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk35c, 0x35c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk360, 0x360);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk364, 0x364);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk368, 0x368);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk36c, 0x36c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk370, 0x370);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk374, 0x374);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk378, 0x378);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk37c, 0x37c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk380, 0x380);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk384, 0x384);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk388, 0x388);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk38c, 0x38c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk390, 0x390);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk394, 0x394);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk395, 0x395);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk396, 0x396);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk397, 0x397);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk398, 0x398);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk399, 0x399);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk39a, 0x39a);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk39b, 0x39b);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk520, 0x520);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk524, 0x524);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk528, 0x528);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk52c, 0x52c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk530, 0x530);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk614, 0x614);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk618, 0x618);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk61c, 0x61c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk620, 0x620);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk624, 0x624);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk628, 0x628);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk62c, 0x62c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk630, 0x630);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk634, 0x634);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk638, 0x638);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk63c, 0x63c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk640, 0x640);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk644, 0x644);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk648, 0x648);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk64c, 0x64c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk650, 0x650);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk654, 0x654);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk658, 0x658);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk65c, 0x65c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk660, 0x660);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk664, 0x664);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk668, 0x668);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk66c, 0x66c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk670, 0x670);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk674, 0x674);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk678, 0x678);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk679, 0x679);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk67a, 0x67a);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk67b, 0x67b);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk67c, 0x67c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk680, 0x680);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk684, 0x684);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk688, 0x688);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk68c, 0x68c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk68d, 0x68d);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk68e, 0x68e);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk68f, 0x68f);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk690, 0x690);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk694, 0x694);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk698, 0x698);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk69c, 0x69c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk6a0, 0x6a0);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk6a4, 0x6a4);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk6a8, 0x6a8);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk6ac, 0x6ac);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk6ad, 0x6ad);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk6ae, 0x6ae);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk6af, 0x6af);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk6b0, 0x6b0);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk6b4, 0x6b4);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk6b8, 0x6b8);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk6bc, 0x6bc);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk6c0, 0x6c0);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk6c4, 0x6c4);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk6c8, 0x6c8);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk6cc, 0x6cc);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk6d0, 0x6d0);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk6d4, 0x6d4);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk6d8, 0x6d8);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk6dc, 0x6dc);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk6e8, 0x6e8);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk6f4, 0x6f4);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk6f8, 0x6f8);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk6fc, 0x6fc);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk6fd, 0x6fd);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk6fe, 0x6fe);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk6ff, 0x6ff);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk700, 0x700);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk704, 0x704);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk708, 0x708);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk709, 0x709);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk70a, 0x70a);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk70b, 0x70b);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk70c, 0x70c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk710, 0x710);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk711, 0x711);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk712, 0x712);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk713, 0x713);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk714, 0x714);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk718, 0x718);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk71c, 0x71c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk720, 0x720);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk724, 0x724);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk725, 0x725);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk726, 0x726);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk727, 0x727);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk728, 0x728);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk72c, 0x72c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk738, 0x738);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk73c, 0x73c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk740, 0x740);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk744, 0x744);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk745, 0x745);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk746, 0x746);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk747, 0x747);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk748, 0x748);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk74c, 0x74c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk750, 0x750);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk751, 0x751);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk752, 0x752);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk753, 0x753);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk754, 0x754);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk758, 0x758);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk75c, 0x75c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk760, 0x760);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk764, 0x764);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk768, 0x768);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk76c, 0x76c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk770, 0x770);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk774, 0x774);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk778, 0x778);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk77c, 0x77c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk780, 0x780);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk788, 0x788);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk78c, 0x78c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk790, 0x790);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk794, 0x794);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk798, 0x798);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk79c, 0x79c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7a0, 0x7a0);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7a4, 0x7a4);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7a8, 0x7a8);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7ac, 0x7ac);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7b0, 0x7b0);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7b4, 0x7b4);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7b5, 0x7b5);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7b6, 0x7b6);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7b7, 0x7b7);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7b8, 0x7b8);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7b9, 0x7b9);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7ba, 0x7ba);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7bb, 0x7bb);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7bc, 0x7bc);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7c0, 0x7c0);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7c4, 0x7c4);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7c5, 0x7c5);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7c6, 0x7c6);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7c7, 0x7c7);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7c8, 0x7c8);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7cc, 0x7cc);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7cd, 0x7cd);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7ce, 0x7ce);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7cf, 0x7cf);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7d0, 0x7d0);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7d4, 0x7d4);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7d5, 0x7d5);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7d6, 0x7d6);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7d7, 0x7d7);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7d8, 0x7d8);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7dc, 0x7dc);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7dd, 0x7dd);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7de, 0x7de);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7df, 0x7df);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7e0, 0x7e0);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7e4, 0x7e4);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7e8, 0x7e8);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7ec, 0x7ec);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7f0, 0x7f0);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7f4, 0x7f4);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7f8, 0x7f8);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7f9, 0x7f9);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7fa, 0x7fa);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7fb, 0x7fb);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk7fc, 0x7fc);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk800, 0x800);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk804, 0x804);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk808, 0x808);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk80c, 0x80c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk810, 0x810);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk814, 0x814);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk818, 0x818);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk819, 0x819);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk81a, 0x81a);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk81b, 0x81b);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk81c, 0x81c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk820, 0x820);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk824, 0x824);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk830, 0x830);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk834, 0x834);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk835, 0x835);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk836, 0x836);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk837, 0x837);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk838, 0x838);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk83c, 0x83c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk840, 0x840);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk844, 0x844);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk848, 0x848);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk84c, 0x84c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk850, 0x850);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk854, 0x854);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk858, 0x858);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk85c, 0x85c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk860, 0x860);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk864, 0x864);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk868, 0x868);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk86c, 0x86c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk86d, 0x86d);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk86e, 0x86e);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk86f, 0x86f);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk870, 0x870);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk874, 0x874);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk875, 0x875);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk876, 0x876);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk877, 0x877);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk878, 0x878);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk87c, 0x87c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk880, 0x880);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk884, 0x884);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk888, 0x888);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk889, 0x889);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk88a, 0x88a);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk88b, 0x88b);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk890, 0x890);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk891, 0x891);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk892, 0x892);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk893, 0x893);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk894, 0x894);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk898, 0x898);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk899, 0x899);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk89a, 0x89a);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk89b, 0x89b);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk89c, 0x89c);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk8a0, 0x8a0);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk8a4, 0x8a4);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk8a8, 0x8a8);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk8a9, 0x8a9);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk8aa, 0x8aa);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk8ab, 0x8ab);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk8ac, 0x8ac);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk8b0, 0x8b0);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk8b1, 0x8b1);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk8b2, 0x8b2);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk8b3, 0x8b3);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk8b4, 0x8b4);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk8b8, 0x8b8);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk8e4, 0x8e4);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk8e8, 0x8e8);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk8ec, 0x8ec);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk8f0, 0x8f0);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk8f4, 0x8f4);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk8f5, 0x8f5);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk8f6, 0x8f6);
DOTD_ASSERT_OFFSET(CKHkS08Enemy, m_unk8f7, 0x8f7);
