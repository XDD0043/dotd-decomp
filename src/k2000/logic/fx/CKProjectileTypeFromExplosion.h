// CKProjectileTypeFromExplosion.h - a homing projectile pool (key 0x290c, vtable 0xb2e648, size 0x34): the ballistic pool
// whose projectiles first fly toward a target (a hero, the data's hook, or a point ahead of the camera), curling round
// it on a circle of the data's radius, then fall ballistically once inside the data's +0x84 reach, pulled toward the
// target between the radii. Original unit: CKProjectileTypeFromExplosion.cpp (0x59a370-0x59c668). Its data is
// CKProjectileDataTypeFromExplosion. Not in XXL2; names ours. No game file holds the class (C2.8 port-final F04).
//
// It keeps CKProjectileTypeBallisticPFX's MessageProc, PostLoad, UpdateOrientation, LaunchEx, LaunchAtPoint(Ex), vfA8
// and GetProjectileAge slots; its Load replaces the base's 0x88-byte records with 0xc0-byte ones (Record).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKProjectileTypeBallisticPFX.h"

class CKProjectileTypeFromExplosion : public CKProjectileTypeBallisticPFX {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xa4)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9cb928
        return key == 0x290c || key == 0x140c || key == 0x130c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKProjectileTypeFromExplosion)

    // One projectile (0xc0 bytes): the base record, then the target and the homing state.
    struct Record : Projectile {
        // +0x88 the target (+0x88), its hot spot (+0x8c), the byte (+0x94); Load 0. Its +0x10 (+0x98, the damage
        // slot) is never written here.
        ProjectileTarget m_target;
        CVector3 m_vAimPoint;           // +0x9c the point it flies toward (Load (0, 0, 0))
        CVector3 m_vPrevTargetPos;      // +0xa8 the target's position the frame before
        float m_fLastDt;                // +0xb4 the last frame's time step (the launches set 0.02)
        float m_fCruiseSpeed;           // +0xb8 the homing speed (Load 0)
        float m_fOrbitAngle;            // +0xbc the angle round the target (Load 0)
    };

    // The constructor inlined in 0x0059ad58 Create / 0x0059b1b8 CreateArray: IKProjectileType's (+0x18 = 8, +0x14 = 1),
    // then the vtables.
    CKProjectileTypeFromExplosion() {}
    ~CKProjectileTypeFromExplosion() override {}  // 0x009cb970 / 0x009cb990: the vtables only

    void Destroy() override;                            // vt+0x10 0x0059c390: CKProjectileTypeBallisticPFX's
    void RecursiveRegistration(int32_t type) override;  // vt+0x24 0x0059c3c0: CKProjectileTypeBallisticPFX's
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0059c3e8 CKProjectileTypeFromExplosion_Load

    void UpdateMotion(uint8_t index, float dt) override;     // vt+0x50 0x0059bc78
    void UpdateCollision(uint8_t index, float dt) override;  // vt+0x54 0x0059ac58
    uint8_t IsDead(uint8_t index) override;                  // vt+0x58 0x0059ac30
    void OnDeath(uint8_t index) override;                    // vt+0x5c 0x0059ac08
    void KillProjectile(uint8_t index) override;             // vt+0x60 0x0059b0f0 CKProjectileTypeFromExplosion_KillInstance
    uint8_t Launch(IKSerializable* data, const CVector3* pos, const CVector3* dir, float speed, IKSerializable* owner,
                   const RwMatrix* matrix) override;         // vt+0x84 0x0059aeb8
    uint8_t LaunchAtTarget(IKSerializable* data, const CVector3* pos, const CVector3* dir, float speed,
                           IKSerializable* owner, IKSerializable* target,
                           const RwMatrix* matrix) override;  // vt+0x8c 0x0059a868
    uint8_t LaunchAtTargetSpot(IKSerializable* data, const CVector3* pos, const CVector3* dir, float speed,
                               IKSerializable* owner, const ProjectileTarget* target,
                               const RwMatrix* matrix) override;  // vt+0x94 0x0059ab28 (Ghidra LaunchInstance_maybe)
    void ProcessDamageContacts(uint8_t index) override;      // vt+0xa4 0x0059a448
    // vt+0xb0 0x0059adb0 CKProjectileTypeFromExplosion_LaunchAtPoint_maybe (a slot of its own): a projectile toward the
    // point `target`; 1 when one was free.
    virtual uint8_t LaunchTowardPoint(IKSerializable* data, const CVector3* pos, const CVector3* dir, float speed,
                                      IKSerializable* owner, const CVector3* target, const RwMatrix* matrix);

    // 0x0059a4e0 _SpawnInstanceAtPoint_maybe / 0x0059a690 _SpawnInstanceAtTarget_maybe / 0x0059a948
    // _SpawnInstanceAtHook_maybe: the record's target and aim set, its homing speed and angle drawn, then the base's
    // SpawnInstance with the homing speed.
    void SpawnTowardPoint(IKSerializable* data, uint8_t index, const CVector3* pos, const CVector3* dir, float speed,
                          IKSerializable* owner, const CVector3* target, const RwMatrix* matrix);
    void SpawnAtTarget(IKSerializable* data, uint8_t index, const CVector3* pos, const CVector3* dir, float speed,
                       IKSerializable* owner, IKSerializable* target, const RwMatrix* matrix);
    void SpawnAtTargetSpot(IKSerializable* data, uint8_t index, const CVector3* pos, const CVector3* dir, float speed,
                           IKSerializable* owner, const ProjectileTarget* target, const RwMatrix* matrix);
    // 0x0059b270 CKProjectileTypeFromExplosion_ComputeInterceptPoint_maybe: the record's aim point for this frame.
    void ComputeInterceptPoint(Record* record);
};
DOTD_ASSERT_SIZE(CKProjectileTypeFromExplosion, 0x34);
DOTD_ASSERT_SIZE(ProjectileTarget, 0x14);
DOTD_ASSERT_SIZE(CKProjectileTypeFromExplosion::Record, 0xc0);
DOTD_ASSERT_OFFSET(CKProjectileTypeFromExplosion::Record, m_target, 0x88);
DOTD_ASSERT_OFFSET(CKProjectileTypeFromExplosion::Record, m_vAimPoint, 0x9c);
DOTD_ASSERT_OFFSET(CKProjectileTypeFromExplosion::Record, m_vPrevTargetPos, 0xa8);
DOTD_ASSERT_OFFSET(CKProjectileTypeFromExplosion::Record, m_fLastDt, 0xb4);
DOTD_ASSERT_OFFSET(CKProjectileTypeFromExplosion::Record, m_fCruiseSpeed, 0xb8);
DOTD_ASSERT_OFFSET(CKProjectileTypeFromExplosion::Record, m_fOrbitAngle, 0xbc);
