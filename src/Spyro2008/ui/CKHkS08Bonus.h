// CKHkS08Bonus.h - a bonus gem/orb hook (key 0x3302, vtable 0xb2f518, size 0xb8; library-TOC code).
// Original unit: Spyro2008/ui/CKHkS08Bonus.cpp. No XXL2 class.
//
// A pool's bonus (CKGrpBonusPool: +0x20 links it into the pool's free / used / beaconed lists, +0x24 is its index and
// its trail ribbon). Spawned with a launch velocity it falls (the component's gravity), bounces off walls and grounds
// (a few times, with rand jitter) and spins; collected by a hero it flies to him on a cubic Bezier curve, shrinking,
// and is applied (the pool's ApplyBonusToHero) when the flight time is over.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/ui/IKHkBonus.h"

class IKTime;

// port-final F06: derives from IKHkBonus (XXL2's base, shared with CKHkBasicBonus), which holds +0x20 / +0x24 and
// makes the pool's slots vt+0xc0..+0xe4 virtual as in the original.
class CKHkS08Bonus : public IKHkBonus {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xcc)
    DOTD_DECLARE_FACTORIES(CKHkS08Bonus)

    // 0x005b7580 CKHkS08Bonus_Create (inlined constructor): the IKLife/IKHook defaults, the ground-contact
    // InOut defaults at +0x54 (sector byte, status 3, ground 0, face -1), then the four halfwords at
    // +0xb0..+0xb7 = 0xffff (stored in the order +0xb0, +0xb6, +0xb2, +0xb4). No CGroundContactDatasIn.
    CKHkS08Bonus() {
        m_unkB0[0] = 0xffff;
        m_unkB0[3] = 0xffff;
        m_unkB0[1] = 0xffff;
        m_unkB0[2] = 0xffff;
    }
    ~CKHkS08Bonus() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005b7bf0 CKHkS08Bonus_Load
    // vt+0x24 0x005b7b60 CKHkS08Bonus_LevelReset (port-all P22): outside the types 4..7 the bonus registered with the
    // saving manager, then IKHook's. vt+0x10 0x005b7a58 (Ghidra _ClearReferences / _Destroy): empty (IKBaseClass's).
    void RecursiveRegistration(int32_t type) override;
    // vt+0x7c 0x005b9c28 CKHkS08Bonus_Update: the age advanced; collected: the flight to the hero; else past its seek
    // time it looks for a hero (SeekNearestHero, nothing more this frame), or while bounces are left it falls, moves
    // (ResolveBounceCollision) and spins. Then the trail follows.
    void Update(IKTime* frameClock) override;

    // The pool's slots (IKHkBonus's, called virtually by the pool).
    // vt+0xc0 0x005b7470 CKHkS08Bonus_ReturnToPool_maybe: hidden, its effect released, its trail stopped.
    void ReturnToPool() override;
    // vt+0xc4 0x005b8178 CKHkS08Bonus_SpawnAt_maybe: the state reset (seek time `seekTime`, a random spin speed, no
    // velocity), a random orientation (three rand draws) unless the component keeps it upright, placed at `position`,
    // shown, its effect taken and its trail reset.
    void SpawnAt(float seekTime, const CVector3* position) override;
    // vt+0xc8 0x005b8900 BonusGem_Collect: collected by `hero` once old enough (or never seeking): its beacon's bit
    // set (`accessor`, the beaconed bonuses), the collect explosion, the flight to the hero prepared, the hero's HUD
    // refreshed.
    void Collect(IKSerializable* hero, const uint16_t* accessor) override;
    // vt+0xcc 0x009cc860 CKHkS08Bonus_vfCC: collected (+0x30 set).
    uint8_t IsCollected() const override { return m_pUnk30 != nullptr ? 1 : 0; }
    // vt+0xd0 0x005b78f8 CKHkS08Bonus_SetVisible (Ghidra name; it spawns the bonus at a beacon: SpawnAtBeacon_maybe): the
    // beacon's position (three 16-bit tenths) given to SpawnAtPosition.
    void SpawnAtBeacon(const uint16_t* accessor) override;
    // vt+0xd4 0x005b7f88 CKHkS08Bonus_SpawnAtPosition_maybe: as SpawnAt for a placed (beaconed) bonus: no seek time
    // (-1), the rotation of zero angles, one rand draw (the spin speed).
    void SpawnAtPosition(const CVector3* position) override;
    void DisableAndReleaseFx() override;  // vt+0xd8 0x005b7890 CKHkS08Bonus_DisableAndReleaseFx_maybe
    // vt+0xdc 0x005b7010 CKHkS08Bonus_vfDC (port-all P19; its caller is the pool's vt+0x118 0x5b1db8, P21): the ground
    // contact back to its defaults (no ground, sector 0, no face, status 3).
    void VfDC() override {
        m_GContactInOut.m_pGround = nullptr;
        m_GContactInOut.m_ui8SectorNumber = 0;
        m_GContactInOut.m_i32FaceIndex = -1;
        m_GContactInOut.m_eContactStatus = 3;
    }
    // vt+0xe0 0x005b7758 CKHkS08Bonus_SetLaunchVelocity_maybe: the velocity `velocity` scaled by a random factor (one
    // rand draw); with `contact`, the ground contact copied.
    void SetLaunchVelocity(const CVector3* velocity, const CGroundContactDatasInOut* contact) override;
    // vt+0xe4 0x005b76d0 CKHkS08Bonus_vfE4: shared with the other hero: the velocity `velocity`, old enough to collect,
    // collected by `hero` (vt+0xc8) and marked shared (+0x34).
    void VfE4(const CVector3* velocity, IKSerializable* hero) override;

    // 0x005b7098 CKHkS08Bonus_SeekNearestHero_maybe: a gem (pool types 3..5) is collected by the nearest controlled
    // hero; anything else, or no hero, goes back to the pool (vt+0xc0).
    void SeekNearestHero();
    // 0x005b9428 CKHkS08Bonus_ResolveBounceCollision_maybe: the move to `position` against the walls (a bounce with
    // three rand draws) and the ground below (a bounce with three more while bounces are left, else it rests).
    void ResolveBounceCollision(CVector3* position);
    // 0x005b8590 CKHkS08Bonus_InitFlyToHeroCurve_maybe: the flight's start and its two random tangents (four draws).
    void InitFlyToHeroCurve();
    // 0x005b8cf8 CKHkS08Bonus_UpdateFlyToHero_maybe: along the curve to the hero (his hot spot 5 for Spyro's family),
    // spinning and shrinking; at the end applied to the hero, shared with his partner, its collect effect played and
    // back to the pool.
    void UpdateFlyToHero(IKTime* frameClock);

    // +0x20 m_pUnk20 (reference (Load): the next bonus in the pool's list) and +0x24 m_unk24 (the index in the pool):
    // IKHkBonus's.
    IKSerializable* m_pUnk28;                 // +0x28 reference (Load): the pool (CKGrpBonusPool)
    IKSerializable* m_pUnk2C;                  // +0x2c reference (Load): the parameters (CKS08BonusCpnt)
    IKSerializable* m_pUnk30;                  // +0x30 runtime: the hero that collected it
    uint8_t m_unk34;                           // +0x34 runtime: shared with the other hero (vfE4)
    uint8_t m_unk35;                           // +0x35 runtime: SpawnAt sets 1 (its arrival adds a collect sound)
    uint8_t m_pad36[2];
    float m_unk38;                             // +0x38 runtime: the spin speed (radians per second)
    float m_unk3c;                             // +0x3c runtime: the age
    float m_unk40;                             // +0x40 runtime: the age at which it seeks a hero (-1: never)
    CVector3 m_unk44;                          // +0x44 runtime: the velocity
    uint32_t m_unk50;                          // +0x50 runtime: the ground bounces so far
    CGroundContactDatasInOut m_GContactInOut;  // +0x54
    IKSerializable* m_pUnk80;                  // +0x80 runtime: the bonus's effect (AcquireBonusFx)
    float m_unk84;                             // +0x84 runtime: the flight's time
    CVector3 m_unk88;                          // +0x88 runtime: the flight's start
    CVector3 m_unk94;                          // +0x94 runtime: the flight's start tangent
    CVector3 m_unkA0;                          // +0xa0 runtime: the flight's end tangent
    uint32_t m_unkAC;                          // +0xac not written
    uint16_t m_unkB0[4];                       // +0xb0 constructor 0xffff each: the beacon accessor (Collect)
};
DOTD_ASSERT_SIZE(CKHkS08Bonus, 0xb8);
DOTD_ASSERT_OFFSET(CKHkS08Bonus, m_pUnk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkS08Bonus, m_pUnk28, 0x28);
DOTD_ASSERT_OFFSET(CKHkS08Bonus, m_pUnk2C, 0x2c);
DOTD_ASSERT_OFFSET(CKHkS08Bonus, m_pUnk30, 0x30);
DOTD_ASSERT_OFFSET(CKHkS08Bonus, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKHkS08Bonus, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(CKHkS08Bonus, m_GContactInOut, 0x54);
DOTD_ASSERT_OFFSET(CKHkS08Bonus, m_pUnk80, 0x80);
DOTD_ASSERT_OFFSET(CKHkS08Bonus, m_unk88, 0x88);
DOTD_ASSERT_OFFSET(CKHkS08Bonus, m_unkA0, 0xa0);
DOTD_ASSERT_OFFSET(CKHkS08Bonus, m_unkB0, 0xb0);
