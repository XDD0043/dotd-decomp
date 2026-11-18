// CKGrpBonusPool.h - a pool of bonus pickups (key 0xf44, size 0x6c). Original units: CKGrpBonusPool.cpp
// and CKGrpBonusPool_2.cpp (TOC2; the Load 0x5b3240 is in the second). XXL2: CKGrpBonusPool
// (IKGroup<IKHkBonus>): its Load reads the same fields in the same order (the type, beacon id, maximum,
// far distance, the four list heads / component as one reference array, the two particle nodes); DotD adds
// a byte after the far distance and a reference, a word and a byte at the end.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/groups/IKBaseGroup.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/math/CMatrix34.h"

class IKTime;

class CKGrpBonusPool : public IKGroup<IKHook> {
public:
    DOTD_CLASS_KEY(kCategoryGroup, 0x3d)
    DOTD_DECLARE_FACTORIES(CKGrpBonusPool)

    CKGrpBonusPool() {}  // 0x005b1788 CKGrpBonusPool_Create: the bases only
    void Destroy() override;  // vt+0x10 0x005b2610 CKGrpBonusPool_Destroy: no child groups, no members

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005b3240 CKGrpBonusPool_Load
    // vt+0x1c 0x005b1fe8 CKGrpBonusPool_vf1C (MessageProc; port-rest R07): 0x0e02 / 0x0e03 the beacons of the current
    // sector marked 0 / 1 (vt+0x10c), 0x0e04 bit 8 from the data byte, 0x1000 / 0x1001 the beacons written / read,
    // 0x1002 / 0x1003 vt+0x110 / +0x114 with the data byte, 0x1004 vt+0x108 then vt+0x118. 0 when handled, else 1.
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x24 0x005b24c8 CKGrpBonusPool_RecursiveRegistration (port-rest R07; Ghidra's checklist name LevelReset):
    // IKBaseGroup's, then outside the types 4..7 the pool registered with the saving manager and the component, the
    // static and the catched particles' registrations (no null tests).
    void RecursiveRegistration(int32_t type) override;
    // vt+0x40 0x005b1fe0 CKGrpBonusPool_vf40 (GetInfo) returns 1: IKSerializable's default.
    // vt+0xb8 0x005b1398 CKGrpBonusPool_vfB8 returns 0x5c: IKBaseGroup models no slot there and nothing ported calls it
    // (CKGrpS08BonusPool's own returns 0x3d).
    int32_t VfB8() { return 0x5c; }
    // vt+0x30 0x005b15b8 CKGrpBonusPool_PostLoad (CKGrpS08BonusPool_PostLoad 0x5afb10 calls it): IKLife_PostLoad 0x19f68, then 1.
    int32_t PostLoad(int32_t type) override {
        PostLoadLife(type);
        return 1;
    }
    // vt+0xec 0x005b1f10 CKGrpBonusPool_ResetPool_maybe (not in the base IKBaseGroup's slots yet): the used and
    // beaconed lists emptied, every pool hook chained into the free list (its +0x20 = the next hook, its
    // +0x24 = its index), the pool's bits 7 and 8 cleared.
    virtual void ResetPool();
    // vt+0xf0 0x005b13a0 CKGrpBonusPool_vfF0 (CKGrpBonus_OnLevelExit_maybe): ReleaseAllActive (vt+0x104).
    virtual void VfF0() { ReleaseAllActive(); }
    // vt+0xf4 0x005b28e8 CKGrpBonusPool_UpdateBonuses_maybe (CKGrpS08BonusPool's 0x5afa90 calls it): the pending
    // collect sounds, the used bonuses updated and collected by the nearest hero in reach, the hidden ones back to the
    // free list, the beaconed ones released and spawned again from the beacons in range.
    virtual void UpdateBonuses(IKTime* frameClock);
    // vt+0xf8 0x005b1eb0 CKGrpBonusPool_vfF8 (CKGrpBonus_ReinitRuntime): ReleaseAllActive (vt+0x104), bit 7 cleared.
    virtual void VfF8() {
        ReleaseAllActive();
        m_bitArray &= 0xffffff7fu;
    }
    // vt+0xfc 0x005b1800 CKGrpBonusPool_SpawnBonus_maybe: the first free bonus moved to the used list and spawned at
    // `position` (vt+0xc4 with the component's life expectancy); with `playSound` the dictionary's sound 1 plays there.
    virtual IKSerializable* SpawnBonus(const CVector3* position, uint8_t playSound);
    virtual void Vf100() {}  // vt+0x100 0x005b13e0 CKGrpBonusPool_vf100 (empty; port-rest R07)
    virtual void ReleaseAllActive();  // vt+0x104 0x005b1c50 CKGrpBonusPool_ReleaseAllActive_maybe
    // vt+0x108 0x005b1b58 CKGrpBonusPool_vf108 (port-rest R07; message 0x1004): the beaconed bonuses released (vt+0xd8)
    // and put in front of the free list.
    virtual void ReleaseBeaconed();
    // vt+0x10c 0x005b1990 CKGrpBonusPool_vf10C (port-rest R07): the persistent bit field of every beacon of the pool's
    // type (the low byte of +0x30) in sector `sector` set to `value`.
    virtual void SetSectorBeaconBits(uint8_t sector, uint8_t value);
    // vt+0x110 0x005b13e8 CKGrpBonusPool_vf110 (message 0x1002): SetSectorBeaconBits(sector, 0) while the life state
    // (bits 5-6) is 1 or 2.
    virtual void Vf110(uint8_t sector) {
        if (((m_bitArray >> 5) & 3u) - 1u > 1u) return;
        SetSectorBeaconBits(sector, 0);  // vt+0x10c
    }
    // vt+0x114 0x005b1e48 CKGrpBonusPool_vf114 (message 0x1003): the same in life state 2 only.
    virtual void Vf114(uint8_t sector) {
        if (((m_bitArray >> 5) & 3u) != 2u) return;
        SetSectorBeaconBits(sector, 0);  // vt+0x10c
    }
    // vt+0x118 0x005b1db8 CKGrpBonusPool_vf118 (message 0x1004): every member's vt+0xdc (the ground contact reset).
    virtual void Vf118();
    // vt+0x120 0x009cc420 CKGrpBonusPool_vf120: whether a bonus may rest on `ground` (a CGround, the ground probe's
    // result in CKHkBasicBonus_SnapToGround_maybe 0x5b50b8): any ground (CKGrpS08BonusPool overrides it). C2.8 port-rest R11.
    virtual int32_t Vf120(IKSerializable* ground) { return ground != nullptr ? 1 : 0; }
    // vt+0x124 0x009cc438 CKGrpBonusPool_vf124: every hero may collect (CKGrpS08BonusPool overrides it).
    virtual uint8_t CanHeroCollect(IKSerializable* /*hero*/) { return 1; }
    // vt+0x128 0x009cc440 CKGrpBonusPool_vf128 (XXL2 IsCatcherChanged(const IKHook*)): the hook that takes over a bonus
    // flying to `catcher`, none here (CKGrpS08BonusPool's 0x5af7f8 returns 0 too). CKHkBasicBonus_Update asks it when
    // the bonus reaches its catcher (port-final F06).
    virtual IKSerializable* IsCatcherChanged(IKSerializable* /*catcher*/) { return nullptr; }
    // vt+0x12c 0x009cc448 CKGrpBonusPool_vf12C (empty; CKGrpS08BonusPool_ApplyBonusToHero_maybe overrides it).
    virtual void ApplyBonusToHero(IKSerializable* /*hero*/, IKSerializable* /*bonus*/) {}
    void ReleaseBonusFx(IKSerializable* effect);  // 0x005b1668 CKGrpBonusPool_ReleaseBonusFx_maybe
    // 0x005b3958 CKGrpBonusPool_AcquireBonusFx_maybe: the static particles' data (+0x50) attached to `node` and a free
    // effect of it taken (reserved, owned by the pool, started); null without a node or a free effect.
    IKSerializable* AcquireBonusFx(IKSerializable* node);
    // 0x005b3bc0 Bonus_TriggerCollectExplosion_maybe: an explosion of the catched particles' data (+0x54) at `position`.
    void TriggerCollectExplosion(const CVector3* position);
    // The trail (+0x58, a CTrailNodeFx: ribbon `index` per bonus) between `position` +- the height (+0x5c) along y or,
    // with +0x60, along `up`: 0x005b1508 CKGrpBonusPool_SetBonusTrailEndpoints_maybe.
    void SetBonusTrailEndpoints(uint32_t index, const CVector3* position, const CVector3* up);
    // 0x005b3ea8 CKGrpBonusPool_ResetBonusTrail_maybe: ribbon `index` off (laid out between its anchors), its endpoints
    // set, then on again (laid out again).
    void ResetBonusTrail(uint32_t index, const CVector3* position, const CVector3* up);
    // 0x005b3e50 CKGrpBonusPool_StopBonusTrail_maybe: ribbon `index` off (its visible count reset), nothing laid out.
    void StopBonusTrail(uint32_t index);

    uint32_t m_ui32BonusType;                     // +0x2c
    uint32_t m_ui32BonusBeaconID;                 // +0x30
    uint32_t m_ui32MaxSimultaneousBonusOnBeacon;  // +0x34
    float m_fFarDistance;                         // +0x38
    uint8_t m_unk3c;                              // +0x3c (DotD only)
    uint8_t m_pad3d[3];
    IKSerializable* m_pFirstUsed;                 // +0x40 XXL2 IKHkBonus*; the four words are one reference array
    IKSerializable* m_pFirstBeaconed;             // +0x44
    IKSerializable* m_pFirstFree;                 // +0x48
    IKSerializable* m_pBonusCpnt;                 // +0x4c XXL2 IKBonusCpnt*
    IKSerializable* m_pStaticParticles;           // +0x50 XXL2 CParticlesNodeFx*
    IKSerializable* m_pCatchedParticles;          // +0x54 XXL2 CParticlesNodeFx*
    IKSerializable* m_pUnk58;                     // +0x58 reference (DotD only): the bonuses' trail (CTrailNodeFx)
    float m_unk5c;                                // +0x5c byte-swapped word (DotD only): the trail's half height
    uint8_t m_unk60;                              // +0x60 (DotD only): the trail along the bonus's up axis
    uint8_t m_pad61[3];
    // +0x64 / +0x68 not set by the constructor or the Load (ResetPool clears them): the time to the next collect sound
    // and the collect sounds still to play (a shared bonus that reaches its hero adds one).
    float m_unk64;
    uint32_t m_unk68;
};
DOTD_ASSERT_SIZE(CKGrpBonusPool, 0x6c);
DOTD_ASSERT_OFFSET(CKGrpBonusPool, m_ui32BonusType, 0x2c);
DOTD_ASSERT_OFFSET(CKGrpBonusPool, m_unk3c, 0x3c);
DOTD_ASSERT_OFFSET(CKGrpBonusPool, m_pFirstUsed, 0x40);
DOTD_ASSERT_OFFSET(CKGrpBonusPool, m_pStaticParticles, 0x50);
DOTD_ASSERT_OFFSET(CKGrpBonusPool, m_unk5c, 0x5c);
DOTD_ASSERT_OFFSET(CKGrpBonusPool, m_unk60, 0x60);
