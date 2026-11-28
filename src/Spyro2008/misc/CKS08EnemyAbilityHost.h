// CKS08EnemyAbilityHost.h - the enemies' interface for their abilities (unregistered; vtable 0xb22688, 66 slots; 8
// bytes: the vtable and the enemy). The attack windup (CKHkS08Enemy main state 0xd) builds it for the kind's last
// attack (OperatorNew(8) + 0x2c6878 into +0x780) and passes it to the ability's Start (+0x784: a CKElectricalGrapple for
// LVL010's kind-0 enemies); the attack states and Update delete it once the ability's Update answers 0. Name: the
// Ghidra draft's (CKS08EnemyAbilityHost_maybe). Original unit: CKS08EnemyAbilityHost.cpp (0x2c5e00-0x2c6d50).
#pragma once
#include <cstdint>

#include "Spyro2008/misc/CKS08AbilityHostBase.h"

class CKHkS08Enemy;

class CKS08EnemyAbilityHost : public CKS08AbilityHostBase {
public:
    // 0x002c6878 CKS08EnemyAbilityHost_maybe_Construct (and its twin 0x2c5e00): the vtable, and the enemy when it is a
    // CKHkS08Enemy (vt+0x08, key 0x26c2). DOTD: otherwise null (the original leaves the allocated word as it was).
    explicit CKS08EnemyAbilityHost(IKSerializable* enemy);
    // vt+0x00 0x002c6090 CKS08EnemyAbilityHost_maybe_Destructor / vt+0x04 0x002c6a50 _DeletingDestructor: the base's
    // vtable (0xb22798), then OperatorDelete.
    ~CKS08EnemyAbilityHost() override {}

    IKSerializable* GetOwner() override;                     // vt+0x08 0x002c5e78: the enemy
    void SetOwnerPosition(const CVector3* position) override;  // vt+0x0c 0x002c6110: CKHkS08Enemy_SetPosition
    CVector3 GetOwnerPosition() override;                    // vt+0x10 0x002c5e80: the enemy's +0x134
    CVector3 GetOwnerGroundPoint() override;                 // vt+0x14 0x002c60a0: CKHkS08Enemy_ComputeGroundPoint
    CVector3 GetHeroForward() override;                      // vt+0x18 0x002c62a0 GetOwnerForward: the node's LTM at
    CVector3 GetHeroVec135c() override;                      // vt+0x1c 0x002c67c8 GetOwnerFlatForward: at, y 0, unit
    CVector3 Vf20() override { return CVector3{1.0f, 0.0f, 1.0f}; }  // vt+0x20 0x002c5eb0 (TOC +0x1964 1.0, a zero word)
    CVector3 GetAimDirection(int32_t raw) override;          // vt+0x24 0x002c5ed0 vf24: GetHeroForward (vt+0x18)
    CVector3 GetOwnerRight() override;                       // vt+0x28 0x002c6458: the node's LTM right
    CVector3 GetOwnerUp() override;                          // vt+0x2c 0x002c6420: the node's LTM up
    uint8_t IsOnGround() override;                           // vt+0x30 0x002c60e0 IsOnGround_maybe: CKHkS08Enemy_IsOnGround
    uint8_t CanUseAltLoopAnim() override { return 0; }       // vt+0x38 0x002c5f28
    // vt+0x3c 0x002c5f30: `air`.
    uint8_t SelectByMovementContext(uint8_t /*ground*/, uint8_t air, uint8_t /*flying*/) override { return air; }
    uint8_t Vf40(CKAbilityElement* /*ability*/, uint32_t /*index*/) override { return 0; }  // vt+0x40 0x002c5f38
    void SetHeroActionPermission(uint32_t, uint8_t, uint8_t, uint8_t) override {}  // vt+0x44 0x002c5f40 (empty)
    float GetHeroSpeedForAbility() override { return 0.0f; }  // vt+0x48 0x002c5f68 (TOC +0x196c 0.0)
    CVector3 GetOwnerVelocity() override;                    // vt+0x4c 0x002c6250: the null vector (0x00c50d64)
    void SetAbilityMoveSpeed(float, float, float) override {}  // vt+0x50 0x002c5f48 (empty)
    void SetAbilityMoveSpeedEnabled(uint8_t) override {}     // vt+0x54 0x002c5f50 (empty)
    // vt+0x58 0x002c6278: the null vector.
    CVector3 ComputeAimDirection(float cone, CKAbilityElement* ability, IKSerializable* aimCone) override;
    void SetAbilityImpulse(CKAbilityElement*, float, float, const CVector3*) override {}      // vt+0x5c 0x002c5f58 (empty)
    void ClearAbilityImpulse(CKAbilityElement*) override {}                   // vt+0x60 0x002c5f60 (empty)
    void SetAbilityTurnParams(float, float, float, float, float, float, uint8_t, uint8_t, uint8_t) override {}  // vt+0x64 0x002c5f70
    void SetAbilityParam11f8(float, float, float, uint8_t, uint8_t, uint8_t) override {}  // vt+0x68 0x002c5f78 (empty)
    void SetHeroEc4Bit27(uint32_t) override {}               // vt+0x6c 0x002c5f98 (empty)
    void SetAbilityHeroMode(CKAbilityElement*, uint8_t) override {}  // vt+0x70 0x002c5f80 (empty)
    float GetOwnerConfig74() override;                       // vt+0x74 0x002c5f88: the kind component's (+0x188) +0x1d4
    void SetHeroEd4Bit0(CKAbilityElement*, uint8_t, float) override {}  // vt+0x78 0x002c5fa0 (empty)
    // vt+0x7c 0x002c68f0 PlayAbilityAnim: nothing played; phases 0 / 3: in the windup (main state 0xd); 1 / 2 / 4: in
    // the strike (0xe) or the recovery (0xf); other phases 1.
    uint8_t PlayAbilityAnim(CKAbilityElement* ability, uint32_t phase) override;
    // vt+0x80 0x002c6978 IsAbilityAnimPhaseDone_maybe: phase 0: a kind 0 / 7 out of the windup (others 1); 1 / 2 / 4:
    // out of the recovery and not in the strike; 3: out of the windup; other phases 0.
    uint8_t IsAbilityAnimPhaseDone(CKAbilityElement* ability, uint32_t phase) override;
    void SetHero1d20(float) override {}                      // vt+0x84 0x002c5fa8 (empty)
    void SetHero1d11(uint8_t) override {}                    // vt+0x88 0x002c5fb0 (empty)
    // vt+0x8c 0x002c65f8 IsAbilityButtonDown_maybe: 1 unless an attack is on: its type 2 for kinds 3 / 8 answers +0x7cc,
    // kind 4 whether GetAbilityInputFlags is non-zero.
    uint8_t IsAbilityButtonDown(int32_t button) override;
    uint8_t IsAbilityButtonReleased(int32_t /*button*/) override { return 0; }  // vt+0x90 0x002c5fb8
    // vt+0x94 0x002c6328 GetAbilityButtonHoldTime_maybe: kind 5 1 (`held` untouched); kind 2 1 (held 1.0); kinds 0 / 7
    // held while not in the windup, the others while in it (held 1.0).
    uint8_t GetAbilityButtonHoldTime(int32_t button, float* held) override;
    // vt+0x98 0x002c63a0 GetTargetPoint_maybe: kind 5: weight 1, the node's modelling at; else weight 0, the null vector.
    CVector3 GetTargetPoint(float* weight) override;
    void SetAbilityCooldown(float, CKAbilityElement*, uint8_t) override {}  // vt+0x9c 0x002c5fc0 (empty)
    void VfA0() override {}                                  // vt+0xa0 0x002c5fc8 (empty)
    void VfA4() override {}                                  // vt+0xa4 0x002c5fd0 (empty)
    void VfA8() override {}                                  // vt+0xa8 0x002c5fd8 (empty)
    uint8_t VfAC() override { return 0; }                    // vt+0xac 0x002c5fe0
    uint8_t GetCollisionGroup() override { return 2; }       // vt+0xb0 0x002c5fe8 (an enemy's volumes)
    uint16_t GetCollisionMask() override { return 0x208; }   // vt+0xb4 0x002c5ff0
    // vt+0xb8 0x002c6238 ConsumeAbilityMana: nothing spent; whether the enemy is of kind 1.
    uint32_t ConsumeAbilityMana(CKAbilityElement* ability, uint32_t amount) override;
    int32_t GetAbilityMana() override { return -1; }         // vt+0xbc 0x002c5ff8 (infinite)
    float GetDamageScale() override { return 1.0f; }         // vt+0xc0 0x002c6008
    float GetEffectScale() override { return 1.0f; }         // vt+0xc4 0x002c6010
    // vt+0xcc 0x002c6490 GetHotspot: the enemy's hot spot for the ability's logical one (0..6).
    IKSerializable* GetHotspot(uint32_t index) override;
    // vt+0xd0 0x002c6a80 GetHotspotPosition: kind 6 between hot spots 9 and 10 at the ground + 0.3; kind 4 the weapon's
    // hot spot at the ground + 0.3; kind 5 the weapon's hot spot; else GetHotspot's world position (null: the null vector).
    CVector3 GetHotspotPosition(uint32_t index) override;
    // vt+0xd4 0x002c61f8 GetLockedTarget: the target (+0x330) of kinds 0, 3, 4, 7, else none.
    IKSerializable* GetLockedTarget() override;
    // vt+0xd8 0x002c6018 (through vt+0xd4)
    IKSerializable* AimAtTarget(CKAbilityElement* /*ability*/, IKSerializable* /*aim*/) override { return GetLockedTarget(); }
    // vt+0xdc 0x002c6758 GetTargetAimPoint_maybe: the target's node LTM position, else the null vector.
    CVector3 GetTargetAimPoint(int32_t fromHotSpot, uint8_t clampHeight) override;
    // vt+0xe4 0x002c6160 GetGrabHotspot_maybe: kinds 0 / 7: the target hero's hot spot 5 (CKHkS08Hero_GetHotSpot), else
    // none.
    IKSerializable* GetGrabHotspot(CKAbilityElement* ability) override;
    float GetGrabPullRatio(CKAbilityElement*) override { return 0.0f; }  // vt+0xe8 0x002c6060
    // vt+0xec 0x002c6138 CanGrab_maybe: nothing grabbed; whether the enemy is of kind 0 or 7.
    uint8_t GrabEnemy(CKAbilityElement* ability, uint8_t grab, uint8_t mode, const CVector3* direction,
                      IKSerializable* damage, IKSerializable* target) override;
    uint8_t VfF0() override { return 0; }                    // vt+0xf0 0x002c6068
    uint8_t GetAbilityLevelIndex(CKAbilityElement*) override { return 2; }  // vt+0xf4 0x002c6070
    uint8_t VfF8() override { return 0; }                    // vt+0xf8 0x002c6078
    void SetAbilityAttackSpheres(CKAbilityElement*, uint8_t, float, IKSerializable*, float, IKSerializable*) override {}               // vt+0xfc 0x002c6080 (empty)
    // vt+0x100 0x002c6690 IsProjectileChargeHeld_maybe: by kind (see the .cpp).
    uint8_t IsProjectileChargeHeld(CKAbilityElement* ability) override;
    IKSerializable* GetAttachmentSets() override { return nullptr; }  // vt+0x104 0x002c6088

    CKHkS08Enemy* m_pEnemy = nullptr;  // +0x04
};
