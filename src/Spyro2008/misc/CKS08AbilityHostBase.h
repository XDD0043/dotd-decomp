// CKS08AbilityHostBase.h - the abilities' interface to their user (unregistered; vtable 0xb22798, 66 slots, all pure
// except +0x34 / +0xc8 (KStub_ReturnFloat1 0x9bd050 / 0x9bd058) and +0xe0 (KStub_Return1 0x9bd060)). The ability
// elements (CKAbilityElement and its families) read and drive their user only through these slots; the hero's
// CKS08HeroAbilityHost (vtable 0xb24a58) and the enemies' CKS08EnemyAbilityHost (vtable 0xb22688) implement them. Name:
// the Ghidra draft's (CKS08AbilityHostBase_maybe). The slot names are the hero host's where that one is ported (its
// callers use them), the enemy host's otherwise.
//
// DOTD: the original's pure slots have bodies here that log and answer 0, so that a host whose slot is not ported
// yet (some of the hero's) still builds; every slot the enemy host has is ported there.
#pragma once
#include <cstdint>

#include "k2000/core/Stub.h"
#include "k2000/math/Vec3.h"

class CKAbilityElement;
class IKSerializable;

class CKS08AbilityHostBase {
public:
    // vt+0x00 0x009bd098 CKS08AbilityHostBase_maybe_Destructor / vt+0x04 0x009bd068 _DeletingDestructor: the vtable.
    virtual ~CKS08AbilityHostBase() {}

    // vt+0x08 the user (the hero, the enemy).
    virtual IKSerializable* GetOwner() { return Unported<IKSerializable*>("GetOwner vt+0x08"); }
    // vt+0x0c the user's position set.
    virtual void SetOwnerPosition(const CVector3* /*position*/) { Unported<int>("SetOwnerPosition vt+0x0c"); }
    // vt+0x10 the user's position.
    virtual CVector3 GetOwnerPosition() { return Unported<CVector3>("GetOwnerPosition vt+0x10"); }
    // vt+0x14 the point under the user (enemy: CKHkS08Enemy_ComputeGroundPoint; hero: +0x570).
    virtual CVector3 GetOwnerGroundPoint() { return Unported<CVector3>("GetOwnerGroundPoint vt+0x14"); }
    // vt+0x18 the user's forward (the node's at row).
    virtual CVector3 GetHeroForward() { return Unported<CVector3>("GetHeroForward vt+0x18"); }
    // vt+0x1c the hero's +0x135c vector; the enemy's flat forward.
    virtual CVector3 GetHeroVec135c() { return Unported<CVector3>("GetHeroVec135c vt+0x1c"); }
    virtual CVector3 Vf20() { return Unported<CVector3>("vt+0x20"); }  // vt+0x20
    // vt+0x24 the aim direction (the hero: CKHkS08Hero_GetHotspot4AimDir_maybe with `raw`; the enemy: its forward).
    virtual CVector3 GetAimDirection(int32_t /*raw*/) { return Unported<CVector3>("GetAimDirection vt+0x24"); }
    virtual CVector3 GetOwnerRight() { return Unported<CVector3>("GetOwnerRight vt+0x28"); }  // vt+0x28
    virtual CVector3 GetOwnerUp() { return Unported<CVector3>("GetOwnerUp vt+0x2c"); }        // vt+0x2c
    // vt+0x30 IsOnGround: the hero on a ground contact (0x3f0fa0), the enemy CKHkS08Enemy_IsOnGround, Malefor 1; the
    // elements keep its negation as their in-air byte, and the host setters take their first argument when it is set.
    virtual uint8_t IsOnGround() { return Unported<uint8_t>("IsOnGround vt+0x30"); }
    virtual float Vf34() { return 1.0f; }  // vt+0x34 0x009bd050 KStub_ReturnFloat1 (the hero: +0x4dc)
    // vt+0x38 the alternative loop animation may be used (the grab's flying / airborne variant, phase 2).
    virtual uint8_t CanUseAltLoopAnim() { return Unported<uint8_t>("CanUseAltLoopAnim vt+0x38"); }
    // vt+0x3c `flying` while flying, else `ground` on the ground (vt+0x30), else `air` (the enemy: `air`).
    virtual uint8_t SelectByMovementContext(uint8_t /*ground*/, uint8_t /*air*/, uint8_t /*flying*/) {
        return Unported<uint8_t>("SelectByMovementContext vt+0x3c");
    }
    // vt+0x40 one of the owner's state tests `index` (0..11) for `ability` (the hero: Slot40Switch_maybe).
    virtual uint8_t Vf40(CKAbilityElement* /*ability*/, uint32_t /*index*/) { return Unported<uint8_t>("vt+0x40"); }
    // vt+0x44 action `index` allowed by movement context.
    virtual void SetHeroActionPermission(uint32_t /*index*/, uint8_t /*ground*/, uint8_t /*flying*/, uint8_t /*air*/) {
        Unported<int>("SetHeroActionPermission vt+0x44");
    }
    virtual float GetHeroSpeedForAbility() { return Unported<float>("GetHeroSpeedForAbility vt+0x48"); }  // vt+0x48
    virtual CVector3 GetOwnerVelocity() { return Unported<CVector3>("GetOwnerVelocity vt+0x4c"); }       // vt+0x4c
    virtual void SetAbilityMoveSpeed(float /*ground*/, float /*flying*/, float /*air*/) {  // vt+0x50
        Unported<int>("SetAbilityMoveSpeed vt+0x50");
    }
    virtual void SetAbilityMoveSpeedEnabled(uint8_t /*on*/) { Unported<int>("SetAbilityMoveSpeedEnabled vt+0x54"); }
    // vt+0x58 the aim direction within `cone` radians (the grab passes pi/2 and its aim cone, a CKAimCamembert; the
    // original's r6 is not set by the callers and not read).
    virtual CVector3 ComputeAimDirection(float /*cone*/, CKAbilityElement* /*ability*/, IKSerializable* /*aimCone*/) {
        return Unported<CVector3>("ComputeAimDirection vt+0x58");
    }
    virtual void SetAbilityImpulse(CKAbilityElement* /*ability*/, float /*strength*/, float /*duration*/,
                                   const CVector3* /*direction*/) { Unported<int>("SetAbilityImpulse vt+0x5c"); }  // vt+0x5c
    virtual void ClearAbilityImpulse(CKAbilityElement* /*ability*/) { Unported<int>("ClearAbilityImpulse vt+0x60"); }                        // vt+0x60
    virtual void SetAbilityTurnParams(float /*groundA*/, float /*groundB*/, float /*flyA*/, float /*flyB*/, float /*airA*/,
                                      float /*airB*/, uint8_t /*gateGround*/, uint8_t /*gateFly*/,
                                      uint8_t /*gateAir*/) {  // vt+0x64
        Unported<int>("SetAbilityTurnParams vt+0x64");
    }
    virtual void SetAbilityParam11f8(float /*ground*/, float /*flying*/, float /*air*/, uint8_t /*gateGround*/,
                                     uint8_t /*gateFly*/, uint8_t /*gateAir*/) {  // vt+0x68
        Unported<int>("SetAbilityParam11f8 vt+0x68");
    }
    virtual void SetHeroEc4Bit27(uint32_t /*value*/) { Unported<int>("SetHeroEc4Bit27 vt+0x6c"); }  // vt+0x6c
    virtual void SetAbilityHeroMode(CKAbilityElement* /*ability*/, uint8_t /*on*/) {             // vt+0x70
        Unported<int>("SetAbilityHeroMode vt+0x70");
    }
    virtual float GetOwnerConfig74() { return Unported<float>("vt+0x74"); }  // vt+0x74 (enemy: its kind's +0x1d4)
    // vt+0x78 the hero: +0xed4 bit 0 = `on`, +0x1b2c = `value` (CKS08HeroAbilityHost_maybe_SetHeroEd4Bit0_maybe
    // 0x3ee460; the earth boulder's per-level value); the enemy: nothing.
    virtual void SetHeroEd4Bit0(CKAbilityElement* /*ability*/, uint8_t /*on*/, float /*value*/) {
        Unported<int>("SetHeroEd4Bit0 vt+0x78");
    }
    // vt+0x7c the ability's animation of `phase` (0..4) played; 0 without one.
    virtual uint8_t PlayAbilityAnim(CKAbilityElement* /*ability*/, uint32_t /*phase*/) {
        return Unported<uint8_t>("PlayAbilityAnim vt+0x7c");
    }
    // vt+0x80 that animation is over.
    virtual uint8_t IsAbilityAnimPhaseDone(CKAbilityElement* /*ability*/, uint32_t /*phase*/) {
        return Unported<uint8_t>("IsAbilityAnimPhaseDone vt+0x80");
    }
    virtual void SetHero1d20(float /*value*/) { Unported<int>("SetHero1d20 vt+0x84"); }     // vt+0x84
    virtual void SetHero1d11(uint8_t /*value*/) { Unported<int>("SetHero1d11 vt+0x88"); }   // vt+0x88
    // vt+0x8c the ability's button is down (the enemies: whether the attack goes on).
    virtual uint8_t IsAbilityButtonDown(int32_t /*button*/) { return Unported<uint8_t>("IsAbilityButtonDown vt+0x8c"); }
    virtual uint8_t IsAbilityButtonReleased(int32_t /*button*/) {  // vt+0x90
        return Unported<uint8_t>("IsAbilityButtonReleased vt+0x90");
    }
    virtual uint8_t GetAbilityButtonHoldTime(int32_t /*button*/, float* /*held*/) {  // vt+0x94
        return Unported<uint8_t>("GetAbilityButtonHoldTime vt+0x94");
    }
    // vt+0x98 the target point, `weight` its weight (the enemy: the node's at row for kind 5).
    virtual CVector3 GetTargetPoint(float* /*weight*/) { return Unported<CVector3>("GetTargetPoint vt+0x98"); }
    virtual void SetAbilityCooldown(float /*cooldown*/, CKAbilityElement* /*ability*/, uint8_t /*perSlot*/) {  // vt+0x9c
        Unported<int>("SetAbilityCooldown vt+0x9c");
    }
    virtual void VfA0() { Unported<int>("vt+0xa0"); }  // vt+0xa0
    virtual void VfA4() { Unported<int>("vt+0xa4"); }  // vt+0xa4
    virtual void VfA8() { Unported<int>("vt+0xa8"); }  // vt+0xa8
    virtual uint8_t VfAC() { return Unported<uint8_t>("vt+0xac"); }  // vt+0xac
    // vt+0xb0 / +0xb4 the owner type and the property flags of the ability's volumes (enemy: 2 / 0x208).
    virtual uint8_t GetCollisionGroup() { return Unported<uint8_t>("GetCollisionGroup vt+0xb0"); }
    virtual uint16_t GetCollisionMask() { return Unported<uint16_t>("GetCollisionMask vt+0xb4"); }
    virtual uint32_t ConsumeAbilityMana(CKAbilityElement* /*ability*/, uint32_t /*amount*/) {  // vt+0xb8
        return Unported<uint32_t>("ConsumeAbilityMana vt+0xb8");
    }
    virtual int32_t GetAbilityMana() { return Unported<int32_t>("GetAbilityMana vt+0xbc"); }  // vt+0xbc (-1 infinite)
    virtual float GetDamageScale() { return Unported<float>("GetDamageScale vt+0xc0"); }      // vt+0xc0
    virtual float GetEffectScale() { return Unported<float>("GetEffectScale vt+0xc4"); }      // vt+0xc4
    virtual float GetManaCostScale() { return 1.0f; }  // vt+0xc8 0x009bd058 KStub_ReturnFloat1
    virtual IKSerializable* GetHotspot(uint32_t /*index*/) { return Unported<IKSerializable*>("GetHotspot vt+0xcc"); }
    virtual CVector3 GetHotspotPosition(uint32_t /*index*/) {  // vt+0xd0
        return Unported<CVector3>("GetHotspotPosition vt+0xd0");
    }
    virtual IKSerializable* GetLockedTarget() { return Unported<IKSerializable*>("GetLockedTarget vt+0xd4"); }
    // vt+0xd8 a target taken for `ability` in the aim cone `aim` (may be null), then the locked one (the hero: its
    // AcquireAbilityTarget; the others: vt+0xd4 or none).
    virtual IKSerializable* AimAtTarget(CKAbilityElement* /*ability*/, IKSerializable* /*aim*/) {
        return Unported<IKSerializable*>("AimAtTarget vt+0xd8");
    }
    // vt+0xdc the target's aim point (the hero: from its hot spot 1 with `fromHotSpot`, the height clamped with
    // `clampHeight`; the enemy: its target's node position).
    virtual CVector3 GetTargetAimPoint(int32_t /*fromHotSpot*/, uint8_t /*clampHeight*/) {
        return Unported<CVector3>("GetTargetAimPoint vt+0xdc");
    }
    // vt+0xe0 0x009bd060 KStub_Return1: `target` may be grabbed at `position` (the hero: a wind beam's enemy is moved
    // there).
    virtual uint8_t CanGrabTarget(CKAbilityElement* /*ability*/, IKSerializable* /*target*/,
                                  const CVector3* /*position*/) {
        return 1;
    }
    // vt+0xe4 the grabbed target's hot spot (enemy: the target hero's hot spot 5).
    virtual IKSerializable* GetGrabHotspot(CKAbilityElement* /*ability*/) {
        return Unported<IKSerializable*>("GetGrabHotspot vt+0xe4");
    }
    // vt+0xe8 how far the grabbed target is pulled (the hero's wind beam: the enemy's wind gauge over its limit).
    virtual float GetGrabPullRatio(CKAbilityElement* /*ability*/) { return Unported<float>("GetGrabPullRatio vt+0xe8"); }
    // vt+0xec the grab tried (`grab` 1) or let go (0) on `target` with the damage object; whether it holds.
    virtual uint8_t GrabEnemy(CKAbilityElement* /*ability*/, uint8_t /*grab*/, uint8_t /*mode*/,
                              const CVector3* /*direction*/, IKSerializable* /*damage*/, IKSerializable* /*target*/) {
        return Unported<uint8_t>("GrabEnemy vt+0xec");
    }
    virtual uint8_t VfF0() { return Unported<uint8_t>("vt+0xf0"); }  // vt+0xf0
    virtual uint8_t GetAbilityLevelIndex(CKAbilityElement* /*ability*/) {  // vt+0xf4
        return Unported<uint8_t>("GetAbilityLevelIndex vt+0xf4");
    }
    virtual uint8_t VfF8() { return Unported<uint8_t>("vt+0xf8"); }  // vt+0xf8
    virtual void SetAbilityAttackSpheres(CKAbilityElement* /*ability*/, uint8_t /*on*/, float /*radius0*/,
                                         IKSerializable* /*damage0*/, float /*radius1*/, IKSerializable* /*damage1*/) {
        Unported<int>("SetAbilityAttackSpheres vt+0xfc");
    }  // vt+0xfc
    virtual uint8_t IsProjectileChargeHeld(CKAbilityElement* /*ability*/) {  // vt+0x100
        return Unported<uint8_t>("IsProjectileChargeHeld vt+0x100");
    }
    virtual IKSerializable* GetAttachmentSets() { return Unported<IKSerializable*>("GetAttachmentSets vt+0x104"); }

private:
    template <typename T>
    static T Unported(const char* slot) {
        DOTD_LOG("stub: CKS08AbilityHostBase %s (not ported for this host)", slot);
        return T{};
    }
};
