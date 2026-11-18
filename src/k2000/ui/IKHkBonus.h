// IKHkBonus.h - the base of a bonus pool's members (abstract, no registered key; XXL2: Commun/K/KBonus/IKHkBonus.h,
// IKHook + m_pNextBonus). DotD's CKHkBasicBonus (key 0x1c82) and CKHkS08Bonus (key 0x3302) both derive from it, and
// CKGrpBonusPool calls its members through these slots (vt+0xc0..+0xe4, every call a bctrl in the original). The slot
// names are XXL2's (IKHkBonus / CKHkBasicBonus: Despawn, Spawn, Catched, IsCatched, FastSpawn x2, FastDespawn,
// OnSectorUnload, InitSpeedAndLanding, InitSpeedAndTarget; XXL2's slots 45..53 + 0x14 = DotD's +0xc0..+0xe4); the C++
// names are the ones the port gave CKHkS08Bonus first. port-final F06.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/math/CMatrix34.h"

class IKHkBonus : public IKHook {
public:
    IKHkBonus() {}
    ~IKHkBonus() override {}

    virtual void ReturnToPool() = 0;                                         // vt+0xc0 XXL2 Despawn
    virtual void SpawnAt(float lifeExpectancy, const CVector3* position) = 0;  // vt+0xc4 XXL2 Spawn(pos, f)
    // vt+0xc8 XXL2 Catched(IKHook* catcher, CKBeaconAccessor* accessor)
    virtual void Collect(IKSerializable* hero, const uint16_t* accessor) = 0;
    virtual uint8_t IsCollected() const = 0;                       // vt+0xcc XXL2 IsCatched
    virtual void SpawnAtBeacon(const uint16_t* accessor) = 0;      // vt+0xd0 XXL2 FastSpawn(CKBeaconAccessor&)
    virtual void SpawnAtPosition(const CVector3* position) = 0;    // vt+0xd4 XXL2 FastSpawn(const CVector3&)
    virtual void DisableAndReleaseFx() = 0;                        // vt+0xd8 XXL2 FastDespawn
    virtual void VfDC() = 0;                                       // vt+0xdc XXL2 OnSectorUnload
    // vt+0xe0 XXL2 InitSpeedAndLanding(const CVector3&, const CGroundContactDatasInOut*)
    virtual void SetLaunchVelocity(const CVector3* velocity, const CGroundContactDatasInOut* contact) = 0;
    // vt+0xe4 XXL2 InitSpeedAndTarget(const CVector3&, const IKHook*)
    virtual void VfE4(const CVector3* velocity, IKSerializable* hero) = 0;

    IKSerializable* m_pUnk20;  // +0x20 XXL2 m_pNextBonus: the next bonus in the pool's list (a reference in both Loads)
    uint32_t m_unk24;          // +0x24 (DotD) runtime (not set by Create or Load): the index in the pool (ResetPool)
};
DOTD_ASSERT_SIZE(IKHkBonus, 0x28);
DOTD_ASSERT_OFFSET(IKHkBonus, m_pUnk20, 0x20);
DOTD_ASSERT_OFFSET(IKHkBonus, m_unk24, 0x24);
