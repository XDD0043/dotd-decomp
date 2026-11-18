// CKHkS08Weapon.h - an enemy's weapon hook (key 0x2902, vtable 0xb223f8, size 0xd0). Original unit:
// CKHkS08Weapon.cpp. No XXL2 class.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/math/Vec3.h"

class CKHkS08Weapon : public IKHook {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xa4)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9bcaa0
        return key == 0x2902 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkS08Weapon)

    // 0x002b1198 CKHkS08Weapon_Create (inlined constructor): the ground-contact defaults and the two bytes
    // at +0xbc/+0xbd = 0xff.
    CKHkS08Weapon() {
        m_unkBD = 0xff;
        m_unkBC = 0xff;
    }
    ~CKHkS08Weapon() override {}

    // vt+0x10 0x002b10b0 CKHkS08Weapon_Destroy: the reference block +0xac freed (Mem_FreeAligned16) and cleared.
    // vt+0x1c 0x002b1748 MessageProc: 1; vt+0x24 0x002b1088 RecursiveRegistration: IKHook's (the defaults).
    void Destroy() override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x002b1870 CKHkS08Weapon_Load
    // vt+0x30 0x002b1500 CKHkS08Weapon_PostLoad: IKLife's (the level bit), the node hidden (flag 4).
    int32_t PostLoad(int32_t type) override;
    void Start() override;  // vt+0x50 0x002b1be8 CKHkS08Weapon_Start (C2.2)
    // vt+0x68 0x002b1688 CKHkS08Weapon_Stop: the node back under the dynamic scene root (engine +0x14) when it is not
    // there (out of its parent, vt+0x78; then the root's AddChild, vt+0x70).
    void Stop() override;
    void Pause() override {}   // vt+0x70 0x002b0ef0 (empty)
    void Resume() override {}  // vt+0x78 0x002b0ef8 (empty)
    // vt+0x7c 0x002b2870 CKHkS08Weapon_Update: the state engine (+0xb8 rows, +0xbc state): the state's tick, and on
    // a new state the leave of the old one and the enter of the new one, with the frame clock.
    void Update(IKTime* frameClock) override;
    // 0x002b1c70 CKHkS08Weapon_State0 (ejected: the flight): enter: the position from the node, the spin axis the
    // node's right, no velocity, the eject velocity's y inverted; leave: not ejected (+0xaa); tick: out of the fight
    // zone's detector group or a kind without two hot spots back to the pool (0xff); a hot spot on the ground lands it
    // (+0xab, state 1); else the flight step (the push while +0x58 < +0x68, gravity, the three spins).
    uint8_t State0(IKTime* clock, int32_t phase, uint8_t other);
    // 0x002b24e0 CKHkS08Weapon_State1 (landed): enter: put on the ground, laid flat (right = y), the ground timer
    // cleared; tick: back to the pool when picked up (+0xa8, 0xff without the pool call), when the pool has more
    // grounded weapons than its limit (+0x194) or after the pool's +0x44 seconds.
    uint8_t State1(IKTime* clock, int32_t phase, uint8_t other);
    // 0x002b2218 CKHkS08Weapon_SetEjectVelocity_maybe: the eject velocity (+0x5c) from `direction`, kept within the
    // kind pool's cone (+0x40 radians above the flat direction: turned by Mat4_RotateLocalXDeg), at the pool's speed
    // (+0x48, backwards), and the push time (+0x68) the pool's +0x4c.
    void SetEjectVelocity(const CVector3* direction);
    // The state engine's handler signature (clock, phase 0 tick / 1 enter / 2 leave, the other state) -> next state.
    using StateFn = uint8_t (CKHkS08Weapon::*)(IKTime* clock, int32_t phase, uint8_t other);
    // A handler pair of the table at +0xc0 (descriptor, adjust) called natively; not ported: the state as given.
    uint8_t CallState(const uint32_t pair[2], IKTime* clock, int32_t phase, uint8_t other);
    // DOTD: the inlined state change of the table at +0xb8 (leave the current row, enter `next`; clock null).
    void SwitchState(uint8_t next);

    virtual void VfC0() {}       // vt+0xc0 0x002b0f00 CKHkS08Weapon_vfC0 (empty)
    // vt+0xc4 0x002b12f8 CKHkS08Weapon_TakeFromPool_maybe: out of the enemy group's pool of its kind into the weapon
    // group (+0x190), in hand (+0xa8 = 1), no state, woken in the weapon group, its node shown.
    virtual void TakeFromPool();
    // vt+0xc8 0x002b1558 CKHkS08Weapon_ReturnToPool_maybe: inactive in the weapon group (+0x190), back in the enemy
    // group's pool of its kind (+0x180[+0x20]) when it is there, its node hidden, +0xab / +0xaa cleared.
    virtual void ReturnToPool();
    virtual void VfCC() {}       // vt+0xcc 0x002b0f08 CKHkS08Weapon_vfCC (empty)
    void SetLanded(uint8_t landed);    // 0x002b2a70 CKHkS08Weapon_SetLanded_maybe (+0xab; 1: state 1)
    void SetEjected(uint8_t ejected);  // 0x002b2bc0 CKHkS08Weapon_SetEjected_maybe (+0xaa; 1: state 0)

    // +0x20 the weapon kind_maybe: indexes the per-kind reference counts (kWeaponRefCount, 0xc4092c).
    // Read for every serialization type.
    uint32_t m_unk20;
    // The flight (runtime, not set by Create or Load).
    CVector3 m_v3Position;                     // +0x24 the position (State0 / State1)
    float m_unk30;                             // +0x30 State0's enter: 0
    CVector3 m_v3SpinAxis;                     // +0x34 State0's enter: the cross product with y, then the node's right
    CVector3 m_v3Accel;                        // +0x40
    CVector3 m_v3Velocity;                     // +0x4c
    float m_fFlightTime;                       // +0x58
    CVector3 m_v3EjectVelocity;                // +0x5c SetEjectVelocity
    float m_fPushTime;                         // +0x68 the push lasts while the flight time is below it
    CGroundContactDatasIn m_GContactIn;        // +0x6c
    CGroundContactDatasInOut m_GContactInOut;  // +0x7c
    uint8_t m_inHandA8;                        // +0xa8 held by an enemy (AttachRandomWeapon, TakeFromPool)
    uint8_t m_unkA9;                           // +0xa9
    uint8_t m_ejectedAA;                       // +0xaa SetEjected
    uint8_t m_landedAB;                        // +0xab SetLanded
    IKSerializable** m_apUnkAC;                // +0xac references, sized by the weapon kind (Load)
    float m_fGroundTime;                       // +0xb0 State1: the time on the ground
    IKSerializable* m_pOwnerB4;                // +0xb4 the enemy holding it (AttachRandomWeapon, EquipWeapon)
    void* m_unkB8;                             // +0xb8 runtime: points into +0xc0 (live dump)
    uint8_t m_unkBC;                           // +0xbc constructor 0xff
    uint8_t m_unkBD;                           // +0xbd constructor 0xff
    uint8_t m_padBE[2];
    uint32_t m_unkC0[4];                       // +0xc0 runtime
};
DOTD_ASSERT_SIZE(CKHkS08Weapon, 0xd0);
DOTD_ASSERT_OFFSET(CKHkS08Weapon, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkS08Weapon, m_v3Position, 0x24);
DOTD_ASSERT_OFFSET(CKHkS08Weapon, m_v3SpinAxis, 0x34);
DOTD_ASSERT_OFFSET(CKHkS08Weapon, m_v3Accel, 0x40);
DOTD_ASSERT_OFFSET(CKHkS08Weapon, m_v3Velocity, 0x4c);
DOTD_ASSERT_OFFSET(CKHkS08Weapon, m_fFlightTime, 0x58);
DOTD_ASSERT_OFFSET(CKHkS08Weapon, m_v3EjectVelocity, 0x5c);
DOTD_ASSERT_OFFSET(CKHkS08Weapon, m_fPushTime, 0x68);
DOTD_ASSERT_OFFSET(CKHkS08Weapon, m_GContactIn, 0x6c);
DOTD_ASSERT_OFFSET(CKHkS08Weapon, m_fGroundTime, 0xb0);
DOTD_ASSERT_OFFSET(CKHkS08Weapon, m_GContactInOut, 0x7c);
DOTD_ASSERT_OFFSET(CKHkS08Weapon, m_apUnkAC, 0xac);
DOTD_ASSERT_OFFSET(CKHkS08Weapon, m_inHandA8, 0xa8);
DOTD_ASSERT_OFFSET(CKHkS08Weapon, m_landedAB, 0xab);
DOTD_ASSERT_OFFSET(CKHkS08Weapon, m_pOwnerB4, 0xb4);
DOTD_ASSERT_OFFSET(CKHkS08Weapon, m_unkBC, 0xbc);
