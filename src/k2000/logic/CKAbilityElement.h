// CKAbilityElement.h - the hero abilities' abstract base (key 0x90cc, id 579, unregistered; vtable 0xb233e0, 27 slots, its
// +0x50..+0x68 the pure virtual 0x9873c8). The five family bases (Breath 0x914c, Projectile 0x934c, Transform 0x954c, Grab
// 0x9fcc, AttackMove 0x9a0c) derive from it; the abilities reach their user only through its ability host
// (CKS08AbilityHostBase: the hero's CKS08HeroAbilityHost, the enemies' CKS08EnemyAbilityHost)
// (outputs/ability-analysis/abilities.md). Name ours (the brief's CKAbilityElement_maybe): no XXL2 class.
//
// DOTD: the protocol slots have bodies here (the original's are pure; every family overrides them): Update answers 0 (not
// running) and the others do nothing.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Stub.h"

class CKS08AbilityHostBase;

class CKAbilityElement : public IKSerializable {
public:
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x90cc || key == 0xc; }  // vt+0x08 0x9bf800

    virtual uint8_t GetAbilityId() { return 0xff; }  // vt+0x50 the ability id (0..20)
    virtual uint8_t GetFamilyId() { return 0xff; }   // vt+0x54 the family id (21..25)
    // vt+0x58 Start: the ability begins for the user behind `host` (the hero's action state 4, the enemies' attack
    // windup). Pure in the original; every family has its own (Transform: CKTransformElement 0x3dc458).
    virtual void Start(CKS08AbilityHostBase* /*host*/) {}
    virtual void Stop(int32_t /*forced*/) {}         // vt+0x5c the ability cancelled (forced 1: the global cooldown)
    virtual uint8_t Update(float /*dt*/) { return 0; }  // vt+0x60 one step; 0 once it is over
    virtual void End(int32_t /*forced*/) {}          // vt+0x64 the end: the cooldown set
    virtual void ApplyHeroControl(uint8_t /*on*/) {}  // vt+0x68 the hero's movement permissions of the ability
};
