// CKS08HeroAbilityHost.h - the hero's interface for its abilities (unregistered; vtable 0xb24a58, 66 slots; 8 bytes: the
// vtable and the hero). The action state 4 builds it on its first enter (hero +0x1df8) and passes it to the ability's Start;
// the abilities read and change the hero only through it (outputs/ability-analysis/abilities.md, section 5). Name: the
// Ghidra draft's (CKS08HeroAbilityHost_maybe). Original unit: CKS08HeroAbilityHost.cpp.
#pragma once
#include <cstdint>

#include "Spyro2008/misc/CKS08AbilityHostBase.h"
#include "k2000/math/Vec3.h"

class CKHkS08Hero;
class IKSerializable;

class CKS08HeroAbilityHost : public CKS08AbilityHostBase {
public:
    // 0x003f0ec8 CKS08HeroAbilityHost_maybe_Construct: the vtable, and the hero when it is a CKHkS08Hero (vt+0x08, key
    // 0x25c2). DOTD: otherwise null (the original leaves the allocated word as it was).
    explicit CKS08HeroAbilityHost(IKSerializable* hero);
    ~CKS08HeroAbilityHost() override {}

    CKHkS08Hero* GetHero() const { return m_pHero; }  // vt+0x08 0x003ee210
    IKSerializable* GetOwner() override;              // vt+0x08 0x003ee210 (GetHero through the base)
    struct CVector3 GetHeroPosition();  // vt+0x10 0x003ee240: the hero's +0x54c position
    CVector3 GetOwnerPosition() override { return GetHeroPosition(); }  // vt+0x10 (the base's name)
    void SetOwnerPosition(const CVector3* position) override;  // vt+0x0c 0x003ee218 SetHeroPosition: +0x54c
    CVector3 GetOwnerGroundPoint() override;  // vt+0x14 0x003ef6c8 GetHeroVec570_maybe: the ground point +0x570
    // vt+0x98 0x003ef560 GetHeroTargetPoint_maybe: the move request (+0x37c), its weight +0x1378.
    CVector3 GetTargetPoint(float* weight) override;
    // vt+0x24 0x003ef018 Slot24_maybe: the hero's aim direction (CKHkS08Hero_GetHotspot4AimDir_maybe 0x32b138).
    struct CVector3 GetAimDirection(int32_t raw) override;
    // vt+0x38 0x003eef28 CanUseAltLoopAnim_maybe: flying, the horizontal speed (+0x12c4) below +0x964; else neither
    // +0x150c nor +0x150d set.
    uint8_t CanUseAltLoopAnim() override;
    // vt+0x8c 0x003efac0 IsAbilityButtonDown_maybe: button 0 (+0xf44), 1 (+0xf58), 2 (either) or 3 (+0xf1c) in state 1.
    uint8_t IsAbilityButtonDown(int32_t button) override;
    uint8_t GetCollisionGroup() override { return 3; }   // vt+0xb0 0x003ee4c8
    uint16_t GetCollisionMask() override { return 0x2a; }  // vt+0xb4 0x003ee4d0

    // vt+0x30 0x003f0fa0 IsOnGround_maybe: on a ground contact: 0 while +0x13d1 (flying) / +0x1511 (else, "left the
    // ground") is set, else +0xec4 bit 18 clear.
    uint8_t IsOnGround() override;
    // vt+0x3c 0x003eee50 SelectByMovementContext: `flying` while flying (movement mode 1), else `ground` on the ground
    // (vt+0x30), else `air`.
    uint8_t SelectByMovementContext(uint8_t ground, uint8_t air, uint8_t flying) override;
    // vt+0x40 0x003ee270 Slot40Switch_maybe: the hero state test `index`: 0 +0xec4 bit 21, 1 bit 12, 2 bit 11, 3 +0x354
    // bit 11 or else +0x35c bit 1, 4 +0xec4 bit 9, 5 the byte +0x1d11, 6 +0xec8 bit 28, 7 +0x354 bit 6, 8 +0xecc bit 31,
    // 9 +0xec4 bit 13, 10 the ability is 15 (vt+0x50), 11 +0xecc bit 27; 0 past 11.
    uint8_t Vf40(class CKAbilityElement* ability, uint32_t index) override;
    // vt+0x7c 0x003ef1d8 PlayAbilityAnim: the ability's animation of `phase` (0..4) in the movement context's table
    // played (start 0, blend 0.12); 0 without one (no slot for the dragon, 0xffff, or not in the dictionary).
    uint8_t PlayAbilityAnim(class CKAbilityElement* ability, uint32_t phase) override;
    // vt+0x80 0x003f0b48 IsAbilityAnimPhaseDone_maybe: whether that animation is over (or not current); 1 without one.
    uint8_t IsAbilityAnimPhaseDone(class CKAbilityElement* ability, uint32_t phase) override;
    // vt+0x90 0x003efe70 IsAbilityButtonReleased_maybe: button 0 (+0xf44), 1 (+0xf58), 2 (either) or 3 (+0xf1c) in
    // state 2.
    uint8_t IsAbilityButtonReleased(int32_t button) override;
    // vt+0x94 0x003efd80 GetAbilityButtonHoldTime_maybe: whether the button is held (state 3), its hold time in `held`
    // (button 2: the longer of the two).
    uint8_t GetAbilityButtonHoldTime(int32_t button, float* held) override;
    // vt+0x9c 0x003ef098 SetAbilityCooldown: `perSlot` and an ability other than 8, 9, 19, 20: its slot's cooldown,
    // else all ten.
    void SetAbilityCooldown(float cooldown, class CKAbilityElement* ability, uint8_t perSlot) override;
    // vt+0xb8 0x003ef9b8 ConsumeAbilityMana: unless the infinite-mana flag (game manager +0x64 bit 23) is set, `amount`
    // taken from the dragon's mana (ConsumeDragonMana) and counted as spent on the ability's element
    // (AddElementManaSpent); then whether mana is left (1 with the flag).
    uint32_t ConsumeAbilityMana(class CKAbilityElement* ability, uint32_t amount) override;
    int32_t GetAbilityMana() override;          // vt+0xbc 0x003f0f40: the dragon's mana, -1 with the infinite-mana flag
    float GetManaCostScale() override;          // vt+0xc8 0x003ee9f0 (CKHkS08Hero_GetAbilityManaCostScale 0x30b110)
    // vt+0xf4 0x003ef8f0 GetAbilityLevelIndex: the ability's element level as 0 (levels 0, 1), 1 (2) or 2 (3).
    uint8_t GetAbilityLevelIndex(class CKAbilityElement* ability) override;
    // vt+0x100 0x003ee618 IsProjectileChargeHeld_maybe: a projectile ability (family 0x16) and +0xedc bit 8.
    uint8_t IsProjectileChargeHeld(class CKAbilityElement* ability) override;

    // vt+0x18 0x003ef690: the hero node's modelling at row (its frame +0x30).
    struct CVector3 GetHeroForward() override;
    struct CVector3 GetHeroVec135c() override;  // vt+0x1c 0x003ef660: the hero's +0x135c vector
    struct CVector3 GetHeroRight();    // vt+0x28 0x003ef8b8: the hero node's modelling right row
    CVector3 GetOwnerRight() override { return GetHeroRight(); }  // vt+0x28 (the base's name)
    // vt+0x58 0x003f1ea8 ComputeAimDirection_maybe: the direction the ability aims at (see the definition); the "no
    // point" vector (FLT_MAX) when it takes no target. `aim` is the ability's CKAimCamembert (may be null).
    struct CVector3 ComputeAimDirection(float maxTurn, class CKAbilityElement* ability, IKSerializable* aim) override;
    // vt+0xdc 0x003efb48 GetTargetAimPoint_maybe: the held enemy's (+0x124) aim point (from the hot spot 1 with
    // `fromHotSpot`, else its node's position), else the hook's (+0x12c), else the "no point" vector.
    struct CVector3 GetTargetAimPoint(int32_t fromHotSpot, uint8_t clampHeight) override;
    // vt+0x44 0x003f18f8 SetHeroActionPermission: action `index` (0..12) allowed or not by the movement context
    // (`ground` on the ground, `flying` in movement mode 1, `air` in the air): the hero's state bits; a flying hero
    // on a ground contact is put in movement mode 0 first.
    void SetHeroActionPermission(uint32_t index, uint8_t ground, uint8_t flying, uint8_t air) override;
    // vt+0x48 0x003efcb0: +0x12c4, negative when the velocity points backwards.
    float GetHeroSpeedForAbility() override;
    void SetAbilityMoveSpeed(float ground, float flying, float air) override;  // vt+0x50 0x003eed48: +0x1d14 by context
    void SetAbilityMoveSpeedEnabled(uint8_t on) override;  // vt+0x54 0x003ee3e0: +0x1d10
    // vt+0x64 0x003eeaf8 SetAbilityTurnParams_maybe: the turn pair (+0x1d04 / +0x1d08) of the context whose gate is
    // set, +0x1d0c the first and +0x1dfc set; else +0x1d0c from +0xaf8 and +0x1dfc cleared.
    void SetAbilityTurnParams(float groundA, float groundB, float flyA, float flyB, float airA, float airB, uint8_t gateGround,
                              uint8_t gateFly, uint8_t gateAir) override;
    // vt+0x68 0x003efef8 SetAbilityParam11f8_maybe: +0x11f8 of the gated context and +0xec8 bit 26, else bit 26 cleared.
    void SetAbilityParam11f8(float ground, float flying, float air, uint8_t gateGround, uint8_t gateFly,
                             uint8_t gateAir) override;
    // vt+0x4c 0x003ef5a0 CKS08HeroAbilityHost_maybe_GetHeroVelocity_maybe: the hero's +0x127c vector.
    CVector3 GetOwnerVelocity() override;
    // vt+0x78 0x003ee460 CKS08HeroAbilityHost_maybe_SetHeroEd4Bit0_maybe: +0xed4 bit 0 = `on`, +0x1b2c = `value`.
    void SetHeroEd4Bit0(class CKAbilityElement* ability, uint8_t on, float value) override;
    void SetHeroEc4Bit27(uint32_t value) override;  // vt+0x6c 0x003ee438
    // vt+0x70 0x003f1040 SetAbilityHeroMode: the hero's mode bits for the ability (ids 6, 10, 5; the breath and
    // projectile families while flying) on, or all of them off.
    void SetAbilityHeroMode(class CKAbilityElement* ability, uint8_t on) override;
    void SetHero1d20(float value) override;  // vt+0x84 0x003ee488
    void SetHero1d11(uint8_t value) override;  // vt+0x88 0x003ee498
    float GetDamageScale() override;  // vt+0xc0 0x003eea68 (0x0030b0d0: +0xe80 with +0xed0 bit 12, else 1)
    float GetEffectScale() override;  // vt+0xc4 0x003eea18 (with +0xed0 bit 4: 0x0030b0f0 +0xe78 with bit 7, else 1)
    // vt+0xcc 0x003ef6f8 GetHotspot: the logical hot spot (0..9) of the dragon (Spyro 0, 5, 18, 26, 28, 1, -, 3, 2, 32;
    // Cynder 0, 5, 18, 0, -, 1, 20, 3, 2, 28 into +0x4c); null for the others.
    IKSerializable* GetHotspot(uint32_t index) override;
    // vt+0xd0 0x003f0a80: its world position, else the null vector.
    struct CVector3 GetHotspotPosition(uint32_t index) override;
    IKSerializable* GetLockedTarget() override;  // vt+0xd4 0x003ee4d8: +0x124, else +0x12c
    // vt+0xd8 0x003f0808 AimAtTarget_maybe: with an aim cone, a target taken (AcquireAbilityTarget 2.0 / 1.0, mask 3)
    // along hot spot 2's (ability 9) or hot spot 6's (ability 0x10) world position, else along the move request (+0x37c;
    // the null one: vt+0x20); then the locked target (vt+0xd4).
    IKSerializable* AimAtTarget(class CKAbilityElement* ability, IKSerializable* aim) override;
    // vt+0x20 0x003ef058 Slot20_maybe: CKHkS08Hero_GetHotspot4FlatDir_maybe 0x32ba68.
    CVector3 Vf20() override;
    // vt+0x74 0x003eea90 GetHeroA78_maybe: +0x8a4 while flying (movement mode 1), else +0xa78.
    float GetOwnerConfig74() override;
    void VfA0() override {}                 // vt+0xa0 0x003ee4a8 (empty)
    void VfA4() override {}                 // vt+0xa4 0x003ee4b0 (empty)
    void VfA8() override {}                 // vt+0xa8 0x003ee4b8 (empty)
    uint8_t VfAC() override { return 0; }   // vt+0xac 0x003ee4c0
    uint8_t VfF8() override { return 0; }   // vt+0xf8 0x003ee610
    // vt+0x104 0x003ee6a0 GetHeroAttachmentSets: the hero's +0x1070.
    IKSerializable* GetAttachmentSets() override;
    // The attack moves' slots (hero-abilities-3).
    CVector3 GetOwnerUp() override;  // vt+0x2c 0x003ef880 GetHeroUp_maybe: the hero node's modelling up row (frame +0x20)
    float Vf34() override;           // vt+0x34 0x003eeff0 GetHero4dc_maybe: CKHkS08Hero_GetHeightAboveGround_maybe
    // vt+0x5c 0x003ef5d0 SetAbilityImpulse_maybe: the hero's timed impulse (+0x1d3c..+0x1d58: `strength`, `duration`,
    // active, `direction`, the time left = `duration`, 0).
    void SetAbilityImpulse(CKAbilityElement* ability, float strength, float duration, const CVector3* direction) override;
    // vt+0x60 0x003ee3f0 ClearAbilityImpulse_maybe: the impulse's direction the null vector, inactive, no time.
    void ClearAbilityImpulse(CKAbilityElement* ability) override;
    uint8_t VfF0() override;  // vt+0xf0 0x003ee600 GetHeroEccBit1: the hero's +0xecc bit 1 (the hit confirmed)
    // vt+0xfc 0x003f1410 SetAbilityAttackSpheres: by the ability id, the hero's attack spheres on / off (sphere 0 with
    // `radius0` / `damage0`, sphere 1 with `radius1` / `damage1`) under the id's hot spots.
    void SetAbilityAttackSpheres(CKAbilityElement* ability, uint8_t on, float radius0, IKSerializable* damage0,
                                 float radius1, IKSerializable* damage1) override;
    // vt+0xe0 0x003ee890 CanGrabTarget_maybe: no target: 0; the wind beam (id 0x12) on an enemy: the enemy must be
    // holdable and `position` inside its fight zone's detectors, then it is moved there; else 1.
    uint8_t CanGrabTarget(class CKAbilityElement* ability, IKSerializable* target, const CVector3* position) override;
    // vt+0xe4 0x003ee6c0 GetGrabState_maybe: the held enemy's (+0x124) hot spot (ability 7: its shield's grab hot spot,
    // else its weapon's hot spot 2, else the sector hot spot 1), else the hook's (+0x12c: an electric gauge's +0x30,
    // Malefor's reference 6), else none.
    IKSerializable* GetGrabHotspot(class CKAbilityElement* ability) override;
    // vt+0xe8 0x003ee500 GetGrabPullRatio_maybe: the wind beam (id 0x12) on an enemy target: its wind gauge (+0x6d0)
    // over its kind's +0x25c; else 0.
    float GetGrabPullRatio(class CKAbilityElement* ability) override;
    // vt+0xec 0x003f00c8 GrabEnemy_maybe: the grab (`grab` 1) or the release (0) of the target (none: the locked one) by
    // the ability (see the definition: ability 7 on an enemy, an electric gauge, Malefor or 0x31c2; the wind beam 0x12
    // on an enemy: hold, keep while within 1.5 x the aim cone's +0x0c, throw along `direction` with `damage` or drop).
    uint8_t GrabEnemy(class CKAbilityElement* ability, uint8_t grab, uint8_t mode, const CVector3* direction,
                      IKSerializable* damage, IKSerializable* target) override;

    CKHkS08Hero* m_pHero = nullptr;  // +0x04
};
