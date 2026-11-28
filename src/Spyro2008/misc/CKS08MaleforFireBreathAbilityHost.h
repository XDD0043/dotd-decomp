// CKS08MaleforFireBreathAbilityHost.h - the user of Malefor's fire breath ability (unregistered; vtable 0xb2a9a0, 66
// slots; 8 bytes: the vtable and the breath attack). CKS08MaleforFireBreath's PostLoad (type 0) builds it
// (OperatorNew(8) + 0x4eb810 into +0x118) and its Update starts the breath ability (+0x12c) with it. The owner it
// answers is the attack's golem (the attack's +0x04). Name: the Ghidra draft's (CKS08MaleforFireBreathAbilityHost_maybe).
// Original unit: CKS08MaleforFireBreathAbilityHost.cpp (0x4eafb0-0x4eb8c8).
#pragma once
#include <cstdint>

#include "Spyro2008/misc/CKS08AbilityHostBase.h"

class CKS08MaleforFireBreath;

class CKS08MaleforFireBreathAbilityHost : public CKS08AbilityHostBase {
public:
    // 0x004eb810 CKS08MaleforFireBreathAbilityHost_maybe_Construct (and its twin 0x4eafb0): the vtable, and the attack
    // when it is a CKS08MaleforFireBreath (vt+0x08, key 0xac4c). DOTD: otherwise null (the original leaves the
    // allocated word as it was).
    explicit CKS08MaleforFireBreathAbilityHost(IKSerializable* attack);
    // vt+0x00 0x004eb8b8 _Destructor / vt+0x04 0x004eb888 _DeletingDestructor: the base's vtable (0xb22798), then
    // OperatorDelete.
    ~CKS08MaleforFireBreathAbilityHost() override {}

    IKSerializable* GetOwner() override;                       // vt+0x08 0x004eb028 GetOwnerHook: the attack's +0x04
    void SetOwnerPosition(const CVector3*) override {}         // vt+0x0c 0x004eb038 (empty)
    CVector3 GetOwnerPosition() override;                      // vt+0x10 0x004eb710: the owner's node LTM pos
    CVector3 GetOwnerGroundPoint() override;                   // vt+0x14 0x004eb458: the null vector
    CVector3 GetHeroForward() override;                        // vt+0x18 0x004eb580 GetOwnerForward: the LTM's at
    CVector3 GetHeroVec135c() override;                        // vt+0x1c 0x004eb040: vt+0x18
    CVector3 Vf20() override;                                  // vt+0x20 0x004eb098: vt+0x18
    CVector3 GetAimDirection(int32_t raw) override;            // vt+0x24 0x004eb0f0: vt+0x18
    CVector3 GetOwnerRight() override;                         // vt+0x28 0x004eb500: the LTM's right
    CVector3 GetOwnerUp() override;                            // vt+0x2c 0x004eb480: the LTM's up
    uint8_t IsOnGround() override { return 1; }                // vt+0x30 0x004eb148
    uint8_t CanUseAltLoopAnim() override { return 1; }         // vt+0x38 0x004eb150
    // vt+0x3c 0x004eb158: `air` (r5).
    uint8_t SelectByMovementContext(uint8_t /*ground*/, uint8_t air, uint8_t /*flying*/) override { return air; }
    uint8_t Vf40(CKAbilityElement* /*ability*/, uint32_t /*index*/) override { return 1; }  // vt+0x40 0x004eb160
    void SetHeroActionPermission(uint32_t, uint8_t, uint8_t, uint8_t) override {}  // vt+0x44 0x004eb168 (empty)
    float GetHeroSpeedForAbility() override { return 0.0f; }  // vt+0x48 0x004eb190 (TOC +0x6f38 0.0)
    CVector3 GetOwnerVelocity() override;                      // vt+0x4c 0x004eb430: the null vector
    void SetAbilityMoveSpeed(float, float, float) override {}  // vt+0x50 0x004eb170 (empty)
    void SetAbilityMoveSpeedEnabled(uint8_t) override {}       // vt+0x54 0x004eb178 (empty)
    // vt+0x58 0x004eb790 ComputeAimDirection_maybe: the owner's LTM at.
    CVector3 ComputeAimDirection(float cone, CKAbilityElement* ability, IKSerializable* aimCone) override;
    void SetAbilityImpulse(CKAbilityElement*, float, float, const CVector3*) override {}  // vt+0x5c 0x004eb180 (empty)
    void ClearAbilityImpulse(CKAbilityElement*) override {}    // vt+0x60 0x004eb188 (empty)
    void SetAbilityTurnParams(float, float, float, float, float, float, uint8_t, uint8_t, uint8_t) override {}  // vt+0x64 0x004eb198
    void SetAbilityParam11f8(float, float, float, uint8_t, uint8_t, uint8_t) override {}  // vt+0x68 0x004eb1a0 (empty)
    void SetHeroEc4Bit27(uint32_t) override {}                 // vt+0x6c 0x004eb1b8 (empty)
    void SetAbilityHeroMode(CKAbilityElement*, uint8_t) override {}  // vt+0x70 0x004eb1a8 (empty)
    float GetOwnerConfig74() override { return 30.0f; }        // vt+0x74 0x004eb1b0 (TOC +0x6f3c 30.0)
    void SetHeroEd4Bit0(CKAbilityElement*, uint8_t, float) override {}  // vt+0x78 0x004eb1c0 (empty)
    // vt+0x7c 0x004eb1c8 PlayAbilityAnim: phases 1 and 2 (unsigned phase - 1 not above 1).
    uint8_t PlayAbilityAnim(CKAbilityElement* /*ability*/, uint32_t phase) override { return phase - 1u <= 1u ? 1 : 0; }
    // vt+0x80 0x004eb1e8 IsAbilityAnimPhaseDone_maybe: every phase but 1 and 2.
    uint8_t IsAbilityAnimPhaseDone(CKAbilityElement* /*ability*/, uint32_t phase) override {
        return phase - 1u <= 1u ? 0 : 1;
    }
    void SetHero1d20(float) override {}                        // vt+0x84 0x004eb208 (empty)
    void SetHero1d11(uint8_t) override {}                      // vt+0x88 0x004eb210 (empty)
    // vt+0x8c 0x004eb218 IsAbilityButtonDown_maybe: the sign bit of (button ^ 1) - 1 (button 1, or a negative button
    // other than 0x80000001).
    uint8_t IsAbilityButtonDown(int32_t button) override {
        return static_cast<int32_t>((static_cast<uint32_t>(button) ^ 1u) - 1u) < 0 ? 1 : 0;
    }
    uint8_t IsAbilityButtonReleased(int32_t /*button*/) override { return 0; }  // vt+0x90 0x004eb230
    // vt+0x94 0x004eb238: vt+0x8c's test; `held` untouched.
    uint8_t GetAbilityButtonHoldTime(int32_t button, float* /*held*/) override {
        return static_cast<int32_t>((static_cast<uint32_t>(button) ^ 1u) - 1u) < 0 ? 1 : 0;
    }
    CVector3 GetTargetPoint(float* weight) override;           // vt+0x98 0x004eb408: the null vector (`weight` untouched)
    void SetAbilityCooldown(float, CKAbilityElement*, uint8_t) override {}  // vt+0x9c 0x004eb250 (empty)
    void VfA0() override {}                                    // vt+0xa0 0x004eb258 (empty)
    void VfA4() override {}                                    // vt+0xa4 0x004eb260 (empty)
    void VfA8() override {}                                    // vt+0xa8 0x004eb268 (empty)
    uint8_t VfAC() override { return 0; }                      // vt+0xac 0x004eb270
    uint8_t GetCollisionGroup() override { return 1; }         // vt+0xb0 0x004eb278
    uint16_t GetCollisionMask() override { return 0x200; }     // vt+0xb4 0x004eb280
    uint32_t ConsumeAbilityMana(CKAbilityElement*, uint32_t) override { return 1; }  // vt+0xb8 0x004eb288
    int32_t GetAbilityMana() override { return 100000; }       // vt+0xbc 0x004eb290
    float GetDamageScale() override { return 1.0f; }           // vt+0xc0 0x004eb2a0 (TOC +0x6f30 1.0)
    float GetEffectScale() override { return 1.0f; }           // vt+0xc4 0x004eb2a8
    // vt+0xcc 0x004eb2b0 GetHotspot: the owner golem's reference 11 (its vt+0xf8), whatever the index.
    IKSerializable* GetHotspot(uint32_t index) override;
    // vt+0xd0 0x004eb600 GetHotspotPosition: GetHotspot's (vt+0xcc) world position, else the owner's node LTM pos.
    CVector3 GetHotspotPosition(uint32_t index) override;
    IKSerializable* GetLockedTarget() override { return nullptr; }  // vt+0xd4 0x004eb320
    IKSerializable* AimAtTarget(CKAbilityElement*, IKSerializable*) override { return nullptr; }  // vt+0xd8 0x004eb328
    CVector3 GetTargetAimPoint(int32_t fromHotSpot, uint8_t clampHeight) override;  // vt+0xdc 0x004eb3e0: the null vector
    IKSerializable* GetGrabHotspot(CKAbilityElement*) override { return nullptr; }  // vt+0xe4 0x004eb330
    float GetGrabPullRatio(CKAbilityElement*) override { return 0.0f; }             // vt+0xe8 0x004eb338 (TOC +0x6f38)
    uint8_t GrabEnemy(CKAbilityElement*, uint8_t, uint8_t, const CVector3*, IKSerializable*, IKSerializable*) override {
        return 0;
    }                                                          // vt+0xec 0x004eb340
    uint8_t VfF0() override { return 0; }                      // vt+0xf0 0x004eb348
    uint8_t GetAbilityLevelIndex(CKAbilityElement*) override { return 2; }  // vt+0xf4 0x004eb350
    uint8_t VfF8() override { return 0; }                      // vt+0xf8 0x004eb358
    void SetAbilityAttackSpheres(CKAbilityElement*, uint8_t, float, IKSerializable*, float, IKSerializable*) override {}  // vt+0xfc 0x004eb360
    uint8_t IsProjectileChargeHeld(CKAbilityElement*) override { return 0; }  // vt+0x100 0x004eb368
    // vt+0x104 0x004eb370 GetAttachmentSets: the attack's eight reference groups (+0x98).
    IKSerializable* GetAttachmentSets() override;

    CKS08MaleforFireBreath* m_pAttack = nullptr;  // +0x04
};
