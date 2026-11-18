// CKProjectileTypeTargetLock.h - a homing projectile pool (key 0x248c, vtable 0xb2e478, size 0x44): the ballistic pool
// whose projectiles, while locked on a target (a hook, or a hot spot of it), turn toward its aim point at a rate that
// grows as they close in (+0x34 at the range +0x3c and beyond, +0x38 at the target), and fall ballistically once the
// lock is lost (the target refuses message 0x402, dies, hides, or is hit). Original unit: CKProjectileTypeTargetLock.cpp
// (0x596240-0x597580). Not in XXL2; names ours. No game file holds the class (C2.8 port-last Z4: read, not replayed).
//
// It keeps CKProjectileTypeBallisticPFX's MessageProc, PostLoad, UpdateOrientation, LaunchEx, LaunchAtPoint(Ex), vfA8
// and GetProjectileAge slots; its Load replaces the base's 0x88-byte records with 0x9c-byte ones (Record).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKProjectileTypeBallisticPFX.h"

class CKProjectileTypeTargetLock : public CKProjectileTypeBallisticPFX {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x92)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9cb6b0
        return key == 0x248c || key == 0x140c || key == 0x130c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKProjectileTypeTargetLock)

    // One projectile (0x9c bytes): the base record, then the lock target.
    struct Record : Projectile {
        // +0x88 the target (+0x88), its hot spot (+0x8c), the hot spot index (+0x94); the Load clears them. +0x90 and the
        // damage slot (+0x98) are never written.
        ProjectileTarget m_target;
    };

    // The constructor inlined in 0x00596580 Create / 0x00596998 CreateArray: IKProjectileType's (+0x18 = 8, +0x14 = 1),
    // then the vtables.
    CKProjectileTypeTargetLock() {}
    ~CKProjectileTypeTargetLock() override {}  // 0x009cb6f8 / 0x009cb718: the vtables only

    void Destroy() override;                            // vt+0x10 0x00597200: CKProjectileTypeBallisticPFX's
    void RecursiveRegistration(int32_t type) override;  // vt+0x24 0x00597230: CKProjectileTypeBallisticPFX's
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00597258 CKProjectileTypeTargetLock_Load
    // (vt+0x28 0x597228 CKProjectileTypeTargetLock_Save returns 1.)

    void UpdateMotion(uint8_t index, float dt) override;     // vt+0x50 0x00596a58
    void UpdateCollision(uint8_t index, float dt) override;  // vt+0x54 0x00596480
    uint8_t IsDead(uint8_t index) override;                  // vt+0x58 0x00596828
    void OnDeath(uint8_t index) override;                    // vt+0x5c 0x00596458
    void KillProjectile(uint8_t index) override;             // vt+0x60 0x00596770 CKProjectileTypeTargetLock_KillInstance
    uint8_t Launch(IKSerializable* data, const CVector3* pos, const CVector3* dir, float speed, IKSerializable* owner,
                   const RwMatrix* matrix) override;         // vt+0x84 0x00596290 (Ghidra _vf84)
    uint8_t LaunchAtTarget(IKSerializable* data, const CVector3* pos, const CVector3* dir, float speed,
                           IKSerializable* owner, IKSerializable* target,
                           const RwMatrix* matrix) override;  // vt+0x8c 0x005970c8
    uint8_t LaunchAtTargetSpot(IKSerializable* data, const CVector3* pos, const CVector3* dir, float speed,
                               IKSerializable* owner, const ProjectileTarget* target,
                               const RwMatrix* matrix) override;  // vt+0x94 0x00596f98 (Ghidra _LaunchAtTargetInfo)
    void ProcessDamageContacts(uint8_t index) override;      // vt+0xa4 0x005965d8

    // 0x00596370 _SpawnWithTarget_maybe / 0x005963d8 _SpawnInstanceSetTarget_maybe: the record's target set, then the
    // base's SpawnInstance (no matrix; the info's damage object). No caller in the original (the launches inline them;
    // their descriptors are unreferenced).
    void SpawnWithTarget(IKSerializable* data, uint8_t index, const CVector3* pos, const CVector3* dir, float speed,
                         IKSerializable* owner, IKSerializable* target);
    void SpawnWithTargetInfo(IKSerializable* data, uint8_t index, const CVector3* pos, const CVector3* dir, float speed,
                             IKSerializable* owner, const ProjectileTarget* target);

    float m_fTurnRateAtRange;       // +0x34 (Load, a word) the homing turn rate at the range and beyond
    float m_fTurnRateAtTarget;      // +0x38 (Load) the turn rate at distance 0 (lerped by (range - distance) / range)
    float m_fTurnRange;             // +0x3c (Load) the range of that lerp
    uint8_t m_bCollideWhileLocked;  // +0x40 (Load) the base's ground collision also while locked
    uint8_t m_pad41[3];
};
DOTD_ASSERT_SIZE(CKProjectileTypeTargetLock, 0x44);
DOTD_ASSERT_SIZE(CKProjectileTypeTargetLock::Record, 0x9c);
DOTD_ASSERT_OFFSET(CKProjectileTypeTargetLock::Record, m_target, 0x88);
DOTD_ASSERT_OFFSET(CKProjectileTypeTargetLock, m_fTurnRateAtRange, 0x34);
DOTD_ASSERT_OFFSET(CKProjectileTypeTargetLock, m_fTurnRange, 0x3c);
DOTD_ASSERT_OFFSET(CKProjectileTypeTargetLock, m_bCollideWhileLocked, 0x40);
